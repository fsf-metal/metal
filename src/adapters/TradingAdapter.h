#ifndef __METAL_TRADINGADAPTER_H
#define __METAL_TRADINGADAPTER_H

#include "Adapter.h"
#include "metal.h"

namespace Metal {
class TradingAdapter : public Adapter {
	public:
		TradingAdapter();
		virtual void send( const NewOrderSingle &) = 0;
		virtual void recv( const ExecutionReport &er) = 0;
	protected:
		~TradingAdapter();
};

} // namespace Metal

#endif //__METAL_TRADINGADAPTER_H
