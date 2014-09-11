#ifndef __METAL_QUICKFIXADAPTER_H
#define __METAL_QUICKFIXADAPTER_H

#include "../TradingAdapter.h"
#include "quickfix/SocketInitiator.h"

namespace Metal {

class QuickFIXAdapter : public TradingAdapter {
	public:
		QuickFIXAdapter();

		// messaging
		void send( const NewOrderSingle &nos);
		void recv( const ExecutionReport &er);

		// life cycle
		void start();
		void stop();

	protected:
		~QuickFIXAdapter(){};

	private:
        FIX::SocketInitiator *initiator;
        FIX::Session *session;
};

} // namespace Metal

#endif // __METAL_QUICKFIXADAPTER_H


