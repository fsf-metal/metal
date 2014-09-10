#ifndef __QUICKFIXADAPTER_H
#define __QUICKFIXADAPTER_H

#include "../TradingAdapter.h"
#include "quickfix/SocketInitiator.h"

class QuickFIXAdapter : public TradingAdapter {
	public:
		QuickFIXAdapter();

		// messaging
		void send( const SingleGeneralOrderHandling::NewOrderSingle &nos);
		void recv( const SingleGeneralOrderHandling::ExecutionReport &er);

		// life cycle
		void start();
		void stop();

	protected:
		~QuickFIXAdapter(){};

	private:
        FIX::SocketInitiator *initiator;
        FIX::Session *session;
};

#endif // __QUICKFIXADAPTER_H


