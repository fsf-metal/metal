#ifndef __METAL_QUICKFIXADAPTER_H
#define __METAL_QUICKFIXADAPTER_H

#include <metal/TradingAdapter.h>
#include <quickfix/SocketInitiator.h>

namespace Metal {
namespace QuickFIX {

class QuickFIXAdapter : public TradingAdapter {
	public:
		QuickFIXAdapter();

		//----------
		// Messaging
		//----------

		/**
		 * We override this method to leverage QuickFIX sending capacity
		 */
		void send( const NewOrderSingle &nos);

		virtual void recv( const ExecutionReport &er);

		//-----------
		// life cycle
		//-----------
		void start();
		void stop();

		/**
		* @see TradingAdapter#benchmark
		*/
		void benchmark( const std::vector<NewOrderSingle> &, std::chrono::milliseconds &, std::chrono::milliseconds &);

		/**
		* @see TradingAdapter#benchmark
		*/
		void benchmark( const std::vector<OrderCancelRequest> &, std::chrono::milliseconds &, std::chrono::milliseconds &);

		virtual ~QuickFIXAdapter(){};

	private:
        FIX::SocketInitiator *initiator;
        FIX::Session *session;
};

} // namespace QuickFIX
} // namespace Metal

#endif // __METAL_QUICKFIXADAPTER_H


