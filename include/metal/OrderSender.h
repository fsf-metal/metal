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
#ifndef METAL_ORDERSENDER_H
#define METAL_ORDERSENDER_H

#include <string>

#include <metal/metal.h>

namespace Metal {

/**
 * OrderSender virtual class describes normalized services for trading<br>
 * This class should be the parent to all normalized order senders adapters<br>
 * 1) Send New Orders
 * 2) Send cancel request
 * 3) Notify client of execution reports
 */
class OrderSender {
	public:
		OrderSender(){
			observer = NULL;
		};

		/**
		 * Formats and sends a normalized Order Cancel Request
		 */
		virtual void sendCancel( const OrderCancelRequest&) = 0;

		/**
		 * This method will be called by users to send new orders<br>
		 * It should map from generic to specific format then encode and send<br>
		 * @param NewOrderSingle Inbound order in unified format @see NewOrderSingle
		 */
		virtual void sendNewOrder( const NewOrderSingle &) = 0;

		/**
		 * Register the observer that will receive notifications
		 */
		void setObserver( const OrderSenderObserver&);

	protected:
		~OrderSender(){};

		OrderSenderObserver* observer;

};

} // namespace Metal

#endif
