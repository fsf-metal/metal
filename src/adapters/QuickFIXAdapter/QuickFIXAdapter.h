#ifndef __METAL_QUICKFIXADAPTER_H
#define __METAL_QUICKFIXADAPTER_H

#include <metal/TradingAdapter.h>
#include <quickfix/SocketInitiator.h>

namespace Metal {
namespace QuickFIX {

class QuickFIXAdapter : public TradingAdapter {
	public:
		static const std::string NAME;
		static const std::string UUID;

		QuickFIXAdapter();

		//----------
		// Messaging
		//----------

		/**
		 * We override this method to leverage QuickFIX sending capacity
		 */
		void sendNewOrder( const NewOrderSingle &nos);

		virtual void onMessage( const ExecutionReport &er);

		//-----------
		// life cycle
		//-----------
		void start();
		void stop();

		/**
		 * We don't need to provide Logon Encoding because QuickFIX provides its own session management
		 */
		virtual void encodeLogon(Message &msg){};
		virtual void encodeHeartBeat(Message &msg){};

		virtual ~QuickFIXAdapter(){};

	protected:
		/**
		 * We don't implement a real data processor because we are leveraging QuickFIX parsing ability
		 */
		int processData(const char *data, int length) { throw new std::runtime_error("QuickFIX adapters should leverage QuickFIX session to read data"); }

		void sendHeartBeat() { throw new std::runtime_error("QuickFIX adapters should leverage QuickFIX engine to send heartbeats"); }
		void sendLogon() { throw new std::runtime_error( "QuickFIX adapters should leverage QuickFIX engine to send logons"); }

	private:
        FIX::SocketInitiator *initiator;
        FIX::Session *session;
};

} // namespace QuickFIX
} // namespace Metal

#endif // __METAL_QUICKFIXADAPTER_H


