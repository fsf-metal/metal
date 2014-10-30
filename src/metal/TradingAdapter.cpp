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

#include <iostream>
#include <thread>

#include <netlink/socket.h>

#include <metal/TradingAdapter.h>
#include <metal/MetalExceptions.h>
#include <metal/Codec.h>

namespace Metal {

TradingAdapter::TradingAdapter( const std::string& name, const std::string& uuid, Codec * codec, int heartBeatInterval, int retryInterval) :
		Adapter(name, uuid, codec, heartBeatInterval, retryInterval) {
	this->socket = NULL;
}

TradingAdapter::~TradingAdapter() {
};


/**
 * We just managed to connect physically<br>
 * We should send a long
 */
void TradingAdapter::onPhysicalConnection() {
//	std::cout << "TradingAdapter: Physical connection" << std::endl;
	// Change status to IDLE to stop retries
/*	changeStatus( IDLE);

	try {
		// 
		Message logon;
		this->encodeLogon(logon);
		this->send(logon);
		changeStatus(HEARTBEATING);
	} catch ( std::exception &e) {
		changeStatus(RETRYING);
		std::cerr << "TradingAdapter: Could not send logon because " << e.what() << std::endl;
	}*/
}

}
