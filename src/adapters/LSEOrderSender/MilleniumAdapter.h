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

#ifndef METAL_LSE_TRADINGADAPTER_H
#define METAL_LSE_TRADINGADAPTER_H

#include <metal/TradingAdapter.h>
#include <metal/OrderSender.h>
#include "NewOrder.h"
#include "OrderCancelRequest.h"
#include "MilleniumCodec.h"

namespace Metal {
namespace LSE {

class MilleniumAdapter : public TradingAdapter {
	public:

		static const std::string NAME;
		static const std::string UUID;

		MilleniumAdapter( std::string userName, std::string password);

		/**
		 * Invoked when a native execution report has been received
		 */
		virtual void onMessage(const Metal::LSE::ExecutionReport &nativeER) = 0;
			
		/**
		 * LSE specific implementation of data processing
		 */
		virtual int processData(const char * data, int size);

		virtual ~MilleniumAdapter(){};

	protected:
		MilleniumCodec *codec;
		std::string userName;
		std::string password;

		void sendHeartBeat();

		/**
		 * Sends a logon message
		 */
		void sendLogon();

};

} // LSE
} // namespace Metal

#endif // METAL_LSE_TRADINGADAPTER_H


