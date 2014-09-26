#include <iostream>
#include <netlink/socket.h>
#include "TradingAdapter.h"

namespace Metal {

TradingAdapter::TradingAdapter( const std::string& name, const std::string& uuid) : Adapter(name, uuid) {
	this->socket = NULL;
	this->remoteHost = "Undefined";
	this->remotePort = 0;
}

TradingAdapter::~TradingAdapter() {
	if (this->socket != NULL) {
		delete this->socket;
		this->socket = NULL;
	}
};

void TradingAdapter::setRemoteHost(const std::string & hostName, unsigned int portNumber) {
	this->remoteHost = hostName;
	this->remotePort = portNumber;
}

void TradingAdapter::start() {
	std::cout << "TradingAdapter: started" << std::endl;

	// open connection to remote host
	this->socket = new NL::Socket( this->remoteHost, this->remotePort);
}


}
