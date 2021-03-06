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
#ifndef __METAL_TRADINGADAPTER_H
#define __METAL_TRADINGADAPTER_H

#include <string>
#include <chrono>
#include <thread>

#include <netlink/socket.h>

#include "Adapter.h"
#include "metal.h"
#include "Mapper.h"
#include "Message.h"
#include "KeepAlive.h"

namespace Metal {

/**
 * TradingAdapter responsibility<br>
 * 1) Send New Orders, Receive execution reports
 */
class TradingAdapter : public Adapter {
	public:
		/**
		 * @param name Whatever should be used to identify this adapter.
		 * @param uuid a unique identifier. Check out http://www.famkruithof.net/uuid/uuidgen to create your own
		 * @param heartBeatInterval number of seconds between heartbeats. Defaults to 30 seconds.
		 * @param retryInterval number of seconds between retries when connection is lost. Defaults to 5 seconds.
		 * Subclasses will perform mapping, encoding then write to the active session
		 */
		TradingAdapter( const std::string& name, const std::string& uuid, int heartBeatInterval = 30, int retryInterval = 5);

		/**
		 * This is invoked for every new message
		 * It should be overriden for custom processing
		 */
		virtual void onMessage(Message &msg){};

		/**
		 * This method will invoked upon receiving a normalized execution report<br>
		 * Subclasses should override this method to capture execution reports in generic format<br>
		 * @param ExecutionReport incomming execution report
		 */
		virtual void onMessage(const ExecutionReport &er){};

		/**
		 * This method is invoked once the socket is connected<br>
		 * The default behavior is to send a Logon message. Which you may want to override.
		 */
		virtual void onPhysicalConnection();

		/**
		 * This method will be called by users to send new orders<br>
		 * It should map from generic to specific format then encode and send<br>
		 * @param NewOrderSingle Inbound order in unified format @see NewOrderSingle
		 */
		virtual void sendNewOrder( const NewOrderSingle &) = 0;

	protected:
		~TradingAdapter();

		/**
		 * Formats and sends a Heart Beat message
		 */
		virtual void sendHeartBeat() = 0;

		/**
		 * Sends a logon message to initiate the session
		 */
		virtual void sendLogon() = 0;




};

} // namespace Metal

#endif //__METAL_TRADINGADAPTER_H
