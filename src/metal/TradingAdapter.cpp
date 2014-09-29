#include <iostream>
#include <thread>
#include <netlink/socket.h>

#include "TradingAdapter.h"
#include "MetalExceptions.h"

namespace Metal {

TradingAdapter::TradingAdapter( const std::string& name, const std::string& uuid) : Adapter(name, uuid) {
	this->socket = NULL;
	this->remoteHost = "Undefined";
	this->remotePort = 0;
}

TradingAdapter::~TradingAdapter() {
	closeSocket();
};

void TradingAdapter::setRemoteHost(const std::string & hostName, unsigned int portNumber) {
	this->remoteHost = hostName;
	this->remotePort = portNumber;
}

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

void TradingAdapter::onPhysicalConnection() {
	this->sendLogon();
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

void TradingAdapter::start() {
	std::cout << "TradingAdapter: starting" << std::endl;

	// open connection to remote host
	this->socket = new NL::Socket( this->remoteHost, this->remotePort);

	this->onPhysicalConnection();

	std::cout << "TradingAdapter: started" << std::endl;
}

void TradingAdapter::stop() {
	std::cout << "TradingAdapter: Stopping" << std::endl;
	// TODO send logout
	closeSocket( 1000);
	std::cout << "TradingAdapter: Stopped" << std::endl;
}

}
