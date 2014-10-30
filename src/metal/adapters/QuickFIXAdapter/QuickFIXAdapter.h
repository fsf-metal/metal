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

		virtual void onMessage( const ExecutionReport &er);

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

		/**
		 * We don't need to provide Logon Encoding because QuickFIX provides its own session management
		 */
		virtual void encodeLogon(Message &msg){};
		virtual void encodeHeartBeat(Message &msg){};

		virtual ~QuickFIXAdapter(){};

	private:
        FIX::SocketInitiator *initiator;
        FIX::Session *session;
};

} // namespace QuickFIX
} // namespace Metal

#endif // __METAL_QUICKFIXADAPTER_H

