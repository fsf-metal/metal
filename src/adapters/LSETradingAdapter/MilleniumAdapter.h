#ifndef __METAL_LSETRADINGADAPTER_H
#define __METAL_LSETRADINGADAPTER_H

#include <metal/TradingAdapter.h>
#include "NewOrder.h"
#include "OrderCancelRequest.h"
#include "MilleniumCodec.h"

namespace Metal {
namespace LSE {

class MilleniumAdapter : public TradingAdapter {
	public:
		MilleniumAdapter();

		/**
		 * @see TradingAdapter#benchmark
		 */
		void benchmark(const std::vector<Metal::NewOrderSingle> &,
			std::chrono::milliseconds& mappingDuration,
			std::chrono::milliseconds& encodingDuration);

		/**
		 * @see TradingAdapter#benchmark
		 */
		void benchmark(const std::vector<Metal::OrderCancelRequest> &,
			std::chrono::milliseconds &,
			std::chrono::milliseconds &);

		void encodeHeartBeat(Message &msg);

		/**
		 * Native Execution Report
		 */
		virtual void onMessage(const Metal::LSE::ExecutionReport &er);

		/**
		 * Normalized Execution Report
		 */
		virtual void onMessage(const Metal::ExecutionReport &er){};

		/**
		 * LSE specific implementation of data processing
		 */
		virtual int processData(const char * data, int size);

		/**
		 * Sends a logon message
		 */
		void sendLogon();

		/**
		 * Sends a normalized new order
		 */
		void sendNewOrder(const Metal::NewOrderSingle &nos);


		virtual ~MilleniumAdapter(){};

	protected:
		MilleniumCodec *mCodec;
		std::string userName;
		std::string password;
};

} // LSE
} // namespace Metal

#endif // __METAL_LSETRADINGADAPTER_H


