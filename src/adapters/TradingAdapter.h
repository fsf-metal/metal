#ifndef __TRADINGADAPTER_H
#define __TRADINGADAPTER_H

#include "Adapter.h"
#include "singlegeneralorderhandling.pb.h"

class TradingAdapter : public Adapter {
	public:
		TradingAdapter();
		~TradingAdapter();
		virtual void send( const SingleGeneralOrderHandling::NewOrderSingle &) = 0;
		void start();
		void stop();
		virtual void recv( const SingleGeneralOrderHandling::ExecutionReport &er) = 0;
};

#endif //__TRADINGADAPTER_H
