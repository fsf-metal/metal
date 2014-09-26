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

		/**
		 * Our identity<br>
		 * @see Adapter#getUUID() for tips.
		 */
		virtual std::string getUUID() { return "acba8ab0-4564-11e4-916c-0800200c9a66";}


		// life cycle
		void start();
		void stop();

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

};

} // LSE
} // namespace Metal

#endif // __METAL_LSETRADINGADAPTER_H


