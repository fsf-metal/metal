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

		// messaging
		void send( const NewOrderSingle &nos);
		virtual void recv( const ExecutionReport &er);

		// life cycle
		void start();
		void stop();

		/**
		 * @see TradingAdapter#benchmark
		 */
		void benchmark( std::vector<Metal::NewOrderSingle> &);

		/**
		* @see TradingAdapter#benchmark
		*/
		void benchmark(std::vector<Metal::OrderCancelRequest> &);

		virtual ~MilleniumAdapter(){};

};

} // LSE
} // namespace Metal

#endif // __METAL_LSETRADINGADAPTER_H


