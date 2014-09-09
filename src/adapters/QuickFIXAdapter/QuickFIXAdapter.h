#ifndef __QUICKFIXADAPTER_H
#define __QUICKFIXADAPTER_H

#include "../TradingAdapter.h"
#include "quickfix/SocketInitiator.h"

class QuickFIXAdapter : public TradingAdapter {
	public:
		QuickFIXAdapter();
		~QuickFIXAdapter();
		void send( const SingleGeneralOrderHandling::NewOrderSingle &nos);
		void start();
		void stop();
		void recv( const SingleGeneralOrderHandling::ExecutionReport &er);

	private:
        FIX::SocketInitiator *initiator;
        FIX::Session *session;
};

#endif // __QUICKFIXADAPTER_H


