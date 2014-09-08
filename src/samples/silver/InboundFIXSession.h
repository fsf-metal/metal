#ifndef __INBOUNDFIXSESSION_H
#define __INBOUNDFIXSESSION_H

#include "quickfix/SocketAcceptor.h"
#include "TradingAdapter.h"

/**
 * This class wraps QuickFIX for inbound client session
 */

class InboundFIXSession {
	public:
		InboundFIXSession();
		void start();
		void stop();
		void setTradingAdapter( TradingAdapter *pta);

	private:
		FIX::SocketAcceptor *acceptor;
		TradingAdapter *tradingAdapter;
};

#endif // __INBOUNDFIXSESSION_H
