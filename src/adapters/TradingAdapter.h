#ifndef __TRADINGADAPTER_H
#define __TRADINGADAPTER_H

#include "Adapter.h"
#include "metal.h"

class TradingAdapter : public Adapter {
	public:
		TradingAdapter();
		virtual void send( const NewOrderSingle &) = 0;
		void start();
		void stop();
		virtual void recv( const ExecutionReport &er) = 0;
	protected:
		~TradingAdapter();
};

#endif //__TRADINGADAPTER_H
