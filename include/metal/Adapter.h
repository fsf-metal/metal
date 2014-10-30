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

#ifndef __METAL_ADAPTER_H
#define __METAL_ADAPTER_H

#include <string>
#include <thread>
#include <mutex>

#include <netlink/socket.h>
#include <netlink/socket_group.h>
#include <metal/Codec.h>

namespace Metal {
	using namespace std;

	/**
	 * <h1>Adapter class Responsibility<h1>
	 * 1) Session Life Cycle: Physical connection, reconnections, logon and heartbeats
	 * 2) grouping inbound data into messages<br>
	 * It is also storing basic ID about the adapter<br>
	 * Inbound data is read in a separate thread which entry point is Adapter#listennerLoop()
	 */
	class Adapter {
	public:
		/**
		 * Constructor
		 * @param nameParam the actual adapter name in english
		 * @param uuidParam a unique adapter identifier. checkout http://www.famkruithof.net/uuid/uuidgen to create your own.
		 * @param codec
		 * @param heartBeatInterval Number of seconds between heartbeats. Set to 0 to disable heartbeats
		 * @param retryInterval Number of seconds between retries. Set to 0 to disable retries.
		 */
		Adapter(const string& nameParam, const string& uuidParam, Codec *codec = NULL, int heartBeatInterval = 0, int retryInterval = 0);

		/**
		 * Here are the possible statuses for Adapter session.<br>
		 */
		enum Status { IDLE, CONNECTING, CONNECTED, RETRYING, STOPPING };

		/**
		 * Thread safe function to change adapter status
		 */
		void changeStatus(Status newStatus);

		/**
		 * Find out Adapter name
		 * @return Current adapter name
		 */
		const string & getName() { return this->name; };

		/**
		 * Thread safe method to get current status
		 */
		const Status getStatus();

		/** utility */
		static std::string getStatusName(const Status &status, std::string &output);

		/**
		 * Retrieve Adapter Unique ID
		 * For example, this is used by benchmarking to report results<br>
		 * This is also used on the web site to identify adapters.
		 */
		const string & getUUID() { return this->uuid; };

		/**
		 * This is the entry point for all new messages
		 * @param msg Contains incomming message data
		 */
		virtual void onMessage(Message &msg) = 0;

		/**
		 * This method is invoked when we have established a physical connection (socket is up)
		 */
		virtual void onPhysicalConnection(){};

		/**
		 * This methods sends an message in native format.
		 * @param msg Whatever should be sent
		 * @return Success flag.
		 */
		bool send(Message& msg);

		/**
		 * This method should be invoked before starting the adapter to set remote host properties
		 * @param hostName name of the remote host
		 * @param portNumber remote port number
		 */
		void setRemoteHost(const std::string &hostName, unsigned int portNumber);

		/**
		 * Starts the listenner thread
		 */
		virtual void start();

		/**
		 * Stops the listenner thread
		 * @param reason
		 */
		virtual void stop( string reason);

	protected:
		~Adapter();
		string name;
		string uuid;

		/**
		 * This is the active socket
		 */
		NL::Socket *socket;
		Codec *codec;

	private:
		/**
		 * How often should we look at the watch. This will be set to the 
		 */
		std::chrono::seconds granularity;

		/** how often should we send heartbeats */
		int heartBeatIntervalInSeconds;

		/** flag used to terminate keep alive thread */
		bool keepAlive;

		/** This threads will keep the session alive */
		thread *keepAliveThread;

		/** This thread will read inbound data */
		thread *listennerThread;

		/** Flag used to terminate the listenning thread */
		bool listenning;

		/**
		 * Remote party address
		 */
		std::string remoteHost;
		/**
		 * Remote party port
		 */
		unsigned int remotePort;

		/** how often should we retry to revive the connection */
		int retryIntervalInSeconds;

		/**
		 * Stores the current status
		 */
		Status status;

		/**
		 * Used for status synchronization
		 */
		std::mutex statusMutex;

		/**
		 * This will terminate the physical connection if need be
		 * @param delay in milliseconds if we should wait before closing
		 */
		void closeSocket(int delay = 0);

		/**
		 * This is the keep alive thread loop
		 */
		void keepAliveLoop();

		/**
		 * This method is meant to be used at the thread entry point
		 */
		void listennerLoop();

		/**
		 * Send a heartbeat to the remote party
		 */
		void heartBeat();

		/**
		 * Performs connection
		 */
		void openSocket();

		/**
		 * Stops the keep alive thread if running
		 */
		void stopKeepAlive();

		/**
		 * Stops the listenner thread if running
		 */
		void stopListenner();

	};
}

#endif // __METAL_ADAPTER_H
