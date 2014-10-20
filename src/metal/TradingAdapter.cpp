#include <iostream>
#include <thread>

#include <netlink/socket.h>

#include <metal/TradingAdapter.h>
#include <metal/MetalExceptions.h>

namespace Metal {

TradingAdapter::TradingAdapter( const std::string& name, const std::string& uuid, int heartBeatInterval, int retryInterval) :
		Adapter(name, uuid),
		KeepAlive( heartBeatInterval, retryInterval) {
	this->socket = NULL;
	this->remoteHost = "";
	this->remotePort = 0;
}

TradingAdapter::~TradingAdapter() {
	closeSocket();
};

void TradingAdapter::closeSocket( int delayMillis) {
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
}

/**
 * This is a placeholder because bsubclasses have the choice between implementing encode() or send()
 */
void TradingAdapter::encode( const NewOrderSingle& nos, Message & msg) {
	throw MissingImplementationException( "encode NewOrderSingle");
}

void TradingAdapter::encodeHeartBeat(Message &msg) {
	throw MissingImplementationException("TradingAdapter: encodeHeartBeat is invoked but not implemented");
}

void TradingAdapter::encodeLogon(Message &msg) {
	throw MissingImplementationException( "TradingAdapter: encodeLogon is invoked but not implemented");
}

void TradingAdapter::heartBeat() {

	Message msg;
	this->encodeHeartBeat( msg);
	send(msg);
}

/**
 * We just managed to connect physically<br>
 * We should send a long
 */
void TradingAdapter::onPhysicalConnection() {
//	std::cout << "TradingAdapter: Physical connection" << std::endl;
	// Change status to IDLE to stop retries
	changeStatus( IDLE);

	try {
		Message logon;
		this->encodeLogon(logon);
		this->send(logon);
		changeStatus(HEARTBEATING);
	} catch ( std::exception &e) {
		changeStatus(RETRYING);
		std::cerr << "TradingAdapter: Could not send logon because " << e.what() << std::endl;
	}
}

/**
 * Invoked by KeepAlive when you need to reconnect
 */
void TradingAdapter::retryConnection() {
	start();
}

void TradingAdapter::send( Message &msg) {
	try {
		this->socket->send(msg.getData(), msg.getLength());
		std::cout << "TradingAdapter: sent " << msg.getLength() << " bytes" << std::endl;
	} catch (std::exception &e) {
		// change the status so we can retry a connection
		changeStatus(KeepAlive::Status::RETRYING);

		SendMessageException sme( e.what());
		throw sme;
	}
}

void TradingAdapter::send( const NewOrderSingle& nos) {
	Message msg;
	encode( nos, msg);
	send( msg);
}

void TradingAdapter::setRemoteHost(const std::string & hostName, unsigned int portNumber) {
	this->remoteHost = hostName;
	this->remotePort = portNumber;
}

void TradingAdapter::start() {
//	std::cout << "TradingAdapter: starting. HBint=" << getHeartBeatInterval() << ", RetryInt=" << getRetryInterval() << std::endl;

	if (this->remoteHost.length() == 0 || this->remotePort == 0) {
		std::cerr << "Remote host and port are required and missing [" << this->remoteHost << ":" << this->remotePort << "]" << std::endl;
		return;
	}

	// open connection to remote host
	try {
		std::cout << "Connecting to " << this->remoteHost << ":" << this->remotePort << std::endl;
		this->socket = new NL::Socket(this->remoteHost, this->remotePort);
		this->onPhysicalConnection();

		std::cout << "TradingAdapter: started" << std::endl;
	} catch (NL::Exception &e) {
		changeStatus(RETRYING);
		std::cerr << "Could not connect to remote host because " << e.what() << e.nativeErrorCode() << std::endl;
	}


}

void TradingAdapter::stop() {
	//std::cout << "TradingAdapter: Stopping" << std::endl;
	// Suspend heartbeats
	changeStatus(KeepAlive::Status::IDLE);

	// TODO send logout
	closeSocket( 1000);
	//std::cout << "TradingAdapter: Stopped" << std::endl;
}

}
