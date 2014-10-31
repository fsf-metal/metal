/*
    MeTAL: My Electronic Trading Adapters Library
    Copyright 2014 Jean-Cedric JOLLANT (jc@jollant.net)

    This file is part of MeTAL.

	MeTAL is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	MeTAL is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with MeTAL source code. If not, see <http://www.gnu.org/licenses/>.

*/

#include <thread>
#include <iostream>

#include <metal/Adapter.h>
#include <metal/Message.h>

using namespace std;

namespace Metal {
	Adapter::Adapter(const std::string& nameParam, const std::string& uuidParam, Codec * codec, int heartBeatInterval, int retryInterval) 
		:name(name), uuid(uuidParam), heartBeatIntervalInSeconds(heartBeatInterval), retryIntervalInSeconds(retryInterval) {

		this->keepAlive = false;
		this->keepAliveThread = NULL;
		this->listenning = false;
		this->listennerThread = NULL;
		this->codec = codec;

		// Half the smallest
		this->granularity = chrono::seconds(min(heartBeatInterval, retryInterval) / 2);

		this->socket = NULL;

		setRemoteHost("", 0);
	}

	Adapter::~Adapter() {
	}

	void Adapter::changeStatus(Status newStatus) {
		//	string statusName;
		//	cout << "Adapter: Changing status to " << getStatusName( newStatus, statusName).c_str() << endl;

		this->statusMutex.lock();
		this->status = newStatus;
		this->statusMutex.unlock();
	}

	void Adapter::closeSocket(int delayMillis) {
		//cout << "Adapter: Closing socket" << endl;
		if (this->socket != NULL) {
			// should we wait?
			if (delayMillis > 0) {
				std::chrono::milliseconds dura(delayMillis);
				std::this_thread::sleep_for(dura);
			}
			this->socket->disconnect();

			delete this->socket;
			this->socket = NULL;
		}
		//cout << "Adapter: socket closed" << endl;
	}

	const Adapter::Status Adapter::getStatus() {

		this->statusMutex.lock();
		Status output = this->status;
		this->statusMutex.unlock();

		return output;
	}

	string Adapter::getStatusName(const Status &status, string &output) {
		switch (status) {
		case IDLE: output = "Idle"; break;
		case CONNECTED: output = "Connected"; break;
		case RETRYING: output = "Retrying"; break;
		case STOPPING: output = "Stopping"; break;
//		case KILLED: output = "Killed"; break;
		default: output = "?";
		}

		return output;
	}

	void Adapter::keepAliveLoop() {
		//cout << "Adapter: keep alive is running" << endl;
		chrono::time_point<chrono::system_clock> lastBeat, lastRetry;
		lastBeat = chrono::system_clock::now();
		lastRetry = lastBeat;

		Message msg;

		while ( this->keepAlive) {
			this_thread::sleep_for( this->granularity);

			//string output;
			//cout << "KeepAlive: " << getStatusName( getStatus(), output) << endl;
			switch ( getStatus()) {
			case IDLE:
				// Watchout, this can be quite verbose
				// cout << "KeepAlive: Idle" << endl;
				break;

			case CONNECTING:
				// Just wait for connection
				break;

			case CONNECTED: { // send the heatbeat if we have waited long enough
				// cout << "Adapter: Heartbeat" << endl;
				using namespace chrono;
				time_point<system_clock> now = system_clock::now();
				duration<double> elapsed = now - lastBeat;
				if (elapsed.count() > this->heartBeatIntervalInSeconds) {
					this->codec->encodeHeartBeat(msg);
					send(msg);
					lastBeat = now;
				}
			}
				break;

			case RETRYING: { // retry the connection if we have waited long enough
				//cout << "Adapter: Retry" << endl;
				using namespace chrono;
				time_point<system_clock> now = system_clock::now();
				duration<double> elapsed = now - lastRetry;
				if (elapsed.count() > this->retryIntervalInSeconds) {
					openSocket();
					lastRetry = now;
				}
			}
				break;

			}
		}
		//cout << "Adapter: keep alive terminated" << endl;
	}


	void Adapter::listennerLoop() {
		//cout << "Adapter: Listenner is running" << endl;
		chrono::seconds granularity = chrono::seconds(5);
		int readSize = 0;
		int offset;
		int msgLength = 0;
		Message msg;
		char * buffer = msg.getData();
		size_t size = Message::MAX_LENGTH;

		/**
		 * The purpose of this loop is to transform network bytes into messages and detect connection problems
		 */
		while (this->listenning) {
			try {
				if (this->socket != NULL && getStatus() == CONNECTED) {
					offset = 0;

					// this loop will scan for data for the duration of the current physical session
					while ( (readSize = this->socket->read(&buffer[offset], size - offset)) > 0) {
						offset += readSize;
						//cout << "Adapter: received " << readSize << " bytes, offset=" << offset << endl;
						//cout << Codec::formatHex(buffer, offset) << endl;
						// do we have a complete message?
						while ((msgLength = this->codec->getMessageLength(buffer, offset)) != 0) {
							offset -= msgLength;
							//cout << "Adapter: Message Received. Len=" << msgLength << ", Offset=" << offset << endl;

							onMessage(msg);

							// do we have leftovers?
							if (offset > 0) { // if so move them at the beginning of the buffer
								memcpy(buffer, &buffer[msgLength], offset);
							}
						}
					}
				}

			} catch (NL::Exception e) {
				// Network exception
//				stop( string("Network Exception ") + e.what());
			} catch ( std::runtime_error e) {
				cout << "Adapter: Closing socket because " << e.what() << endl;
				// Data exception
				closeSocket();
			}

			// wait for reconnection
			this_thread::sleep_for(granularity);
		}

		//cout << "Adapter: listenner terminated" << endl;
	}

	void Adapter::openSocket() {

		// open connection to remote host
		try {
			std::cout << "Connecting to " << this->remoteHost << ":" << this->remotePort << std::endl;
			changeStatus(CONNECTING);
			this->socket = new NL::Socket(this->remoteHost, this->remotePort);
			changeStatus(CONNECTED);
			std::cout << "Connected." << std::endl;

			// propagate physical connection
			onPhysicalConnection();

		} catch (NL::Exception &e) {
			// Connection failed. Do we still need to try?
			std::cerr << "Could not connect to remote host because " << e.what() << " " << e.nativeErrorCode() << std::endl;
			if (CONNECTING == getStatus()){
				changeStatus(RETRYING);
			}
		}

	}
	/**
	 * Write a message to the socket
	 */
	bool Adapter::send(Message &msg) {
		try {
			if (this->socket != NULL) {
				this->socket->send(msg.getData(), msg.getLength());
				// cout << "Adapter: sent " << msg.getLength() << " bytes" << std::endl;
				return true;
			}
		} catch (std::exception &e) {
			std::cerr << "Adapter: Could not send message, " << e.what() << std::endl;
		} catch (...) {
			std::cerr << "Adapter: Could not send message" << std::endl;
		}
		// change the status so we can retry a connection
		changeStatus(RETRYING);
		return false;
	}

	void Adapter::setRemoteHost(const std::string & hostName, unsigned int portNumber) {
		this->remoteHost = hostName;
		this->remotePort = portNumber;
	}

	void Adapter::start() {
		// Prevent Duplicates
		stop( "Prevent duplicates");

		if (this->remoteHost.length() == 0 || this->remotePort == 0) {
			std::cerr << "Remote host and port are required and missing [" << this->remoteHost << ":" << this->remotePort << "]" << std::endl;
			return;
		}

		// restart threads
		this->listenning = true;
		this->listennerThread = new thread(&Adapter::listennerLoop, this);
		this->keepAlive = true;
		this->keepAliveThread = new thread(&Adapter::keepAliveLoop, this);

		openSocket();
	}

	void Adapter::stop( string reason) {
		// cout << "Adapter: stopping because=" << reason << endl;

		// Prevent encapsulated termination
		// This may happen when we close the socket
		if (getStatus() == STOPPING) return;
		changeStatus(STOPPING);

		this->keepAlive = false;
		this->listenning = false;

		// Wait for thread if it is not the invoker
		if (this->keepAliveThread != NULL && this_thread::get_id() != this->keepAliveThread->get_id()){
			this->keepAliveThread->join();
			this->keepAliveThread = NULL;
		}

		// we must close the socket before waiting the listenner
		// which is otherwise blocked on read() call
		closeSocket();

		// Wait for thread if it is not the invoker
		if (this->listennerThread != NULL && this_thread::get_id() != this->listennerThread->get_id()){
			this->listennerThread->join();
			this->listennerThread = NULL;
		}

		cout << "Adapter: Stopped. Reason=" << reason << endl;
	}

}