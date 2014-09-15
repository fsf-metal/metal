#ifndef __METAL_LSETRADINGADAPTER_H
#define __METAL_LSETRADINGADAPTER_H

#include "../TradingAdapter.h"

namespace Metal {

class LSETradingAdapter : public TradingAdapter {
	public:
		LSETradingAdapter();

		// messaging
		void send( const NewOrderSingle &nos);
		virtual void recv( const ExecutionReport &er);

		// life cycle
		void start();
		void stop();

		// for benchmarking
		MessageMapper* getMessageMapper();

		virtual ~LSETradingAdapter(){};

};

} // namespace Metal

#endif // __METAL_LSETRADINGADAPTER_H


