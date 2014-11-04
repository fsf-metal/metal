#ifndef __METAL_LSETRADINGADAPTER_H
#define __METAL_LSETRADINGADAPTER_H

#include <metal/TradingAdapter.h>
#include <metal/NormalizedTrading.h>
#include "NewOrder.h"
#include "OrderCancelRequest.h"
#include "MilleniumCodec.h"

namespace Metal {
namespace LSE {

class MilleniumAdapter : public TradingAdapter, public NormalizedTrading {
	public:

		static const std::string NAME;
		static const std::string UUID;

		MilleniumAdapter();

		/**
		 * Invoked when a native execution report has been received
		 */
		void onMessage(const Metal::LSE::ExecutionReport &nativeER);
			
		/**
		 * LSE specific implementation of data processing
		 */
		virtual int processData(const char * data, int size);

		/**
		 * Sends a normalized cancel
		 */
		void sendCancel(const Metal::OrderCancelRequest& ocr);

		/**
		 * Sends a normalized new order
		 */
		void sendNewOrder(const Metal::NewOrderSingle &nos);

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

#endif // __METAL_LSETRADINGADAPTER_H


