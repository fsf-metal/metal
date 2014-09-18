#ifndef __METAL_TRADINGADAPTER_H
#define __METAL_TRADINGADAPTER_H

#include <string>
#include "Adapter.h"
#include "metal.h"
#include "MessageMapper.h"

namespace Metal {
class TradingAdapter : public Adapter {
	public:
		TradingAdapter( const std::string& name) : Adapter( name){};
		virtual void send( const NewOrderSingle &) = 0;
		virtual void recv( const ExecutionReport &er) = 0;

		// The following set of methods should be implemented by all adapters
		// The purpose is to measure Mapping and Encoding speed
		virtual void benchmark( std::vector<NewOrderSingle> &) = 0;
//		virtual void benchmark( std::vector<OrderCancelRequest> &) = 0;

	protected:
		~TradingAdapter();
};

} // namespace Metal

#endif //__METAL_TRADINGADAPTER_H
