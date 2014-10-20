#include <iostream>
#include <thread>

#include <netlink/socket.h>

#include <metal/TradingAdapter.h>
#include <metal/MetalExceptions.h>

namespace Metal {

TradingAdapter::TradingAdapter( const std::string& name, const std::string& uuid, int heartBeatInterval) :
		Adapter(name, uuid),
		Session( heartBeatInterval, 0) {
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
	encodeHeartBeat( msg);
	send(msg);
}

void TradingAdapter::onPhysicalConnection() {
	Message logon;
	this->encodeLogon( logon);
	this->send( logon);
}

void TradingAdapter::send( Message &msg) {
	try {
		this->socket->send(msg.getData(), msg.getLength());
	}
	catch (std::exception &e) {
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
	std::cout << "TradingAdapter: starting" << std::endl;

	if (this->remoteHost.length() == 0 || this->remotePort == 0) {
		std::cerr << "Remote host and port are required and missing [" << this->remoteHost << ":" << this->remotePort << "]" << std::endl;
		return;
	}

	// open connection to remote host
	try {
		this->socket = new NL::Socket(this->remoteHost, this->remotePort);
//		this->onPhysicalConnection();
		// Resume heartbeats
		resumeHeartBeats();
		std::cout << "TradingAdapter: started" << std::endl;
	} catch (NL::Exception &e) {
		std::cerr << "Could not connect to remote host because " << e.what() << std::endl;
	}


}

void TradingAdapter::stop() {
	//std::cout << "TradingAdapter: Stopping" << std::endl;
	// Suspend heartbeats
	suspendHeartBeats();
	// TODO send logout
	closeSocket( 1000);
	//std::cout << "TradingAdapter: Stopped" << std::endl;
}

}
