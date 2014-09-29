#ifndef __METAL_LSETRADINGADAPTER_H
#define __METAL_LSETRADINGADAPTER_H

#include <metal/TradingAdapter.h>
#include "NewOrder.h"
#include "OrderCancelRequest.h"

namespace Metal {
namespace LSE {

class MilleniumAdapter : public TradingAdapter {
	public:
		MilleniumAdapter();

		/**
		 * @see TradingAdapter#encode( const NewOrderSingle&, Message&)
		 */
		void encode( const NewOrderSingle& nos, Message &msg);

		virtual void recv( const ExecutionReport &er);

		// life cycle
		void start();
		void stop();

		// Send a logon message
		void sendLogon();

		/**
		 * @see TradingAdapter#benchmark
		 */
		void benchmark( const std::vector<Metal::NewOrderSingle> &,
				std::chrono::milliseconds& mappingDuration,
				std::chrono::milliseconds& encodingDuration);

		/**
		* @see TradingAdapter#benchmark
		*/
		void benchmark( const std::vector<Metal::OrderCancelRequest> &,
				std::chrono::milliseconds &,
				std::chrono::milliseconds &);

		virtual ~MilleniumAdapter(){};

	protected:
		std::string userName;
		std::string password;
};

} // LSE
} // namespace Metal

#endif // __METAL_LSETRADINGADAPTER_H


