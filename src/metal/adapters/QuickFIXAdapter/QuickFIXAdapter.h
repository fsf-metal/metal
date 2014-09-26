#ifndef __METAL_QUICKFIXADAPTER_H
#define __METAL_QUICKFIXADAPTER_H

#include <metal/TradingAdapter.h>
#include <quickfix/SocketInitiator.h>

namespace Metal {
namespace QuickFIX {

class QuickFIXAdapter : public TradingAdapter {
	public:
		QuickFIXAdapter();

		// messaging
		void send( const NewOrderSingle &nos);
		virtual void recv( const ExecutionReport &er);

		/**
		 * Our identity<br>
		 * @see Adapter#getUUID() for tips.
		 */
		virtual std::string getUUID() { return "e32cd5d0-4564-11e4-916c-0800200c9a66";}

		// life cycle
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


