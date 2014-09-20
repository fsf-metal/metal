#ifndef __METAL_LSETRADINGADAPTER_H
#define __METAL_LSETRADINGADAPTER_H

#include <metal/TradingAdapter.h>

namespace Metal {
namespace LSE {

class LSETradingAdapter : public TradingAdapter {
	public:
		LSETradingAdapter();

		// messaging
		void send( const NewOrderSingle &nos);
		virtual void recv( const ExecutionReport &er);

		// life cycle
		void start();
		void stop();

		/**
		 * @see TradingAdapter#benchmark
		 */
		void benchmark( std::vector<NewOrderSingle> &);

		/**
		* @see TradingAdapter#benchmark
		*/
		void benchmark(std::vector<OrderCancelRequest> &);

		virtual ~LSETradingAdapter(){};

};

} // LSE
} // namespace Metal

#endif // __METAL_LSETRADINGADAPTER_H


