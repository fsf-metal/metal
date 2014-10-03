#ifndef __METAL___NAMESPACE__ADAPTER_H
#define __METAL___NAMESPACE__ADAPTER_H

#include <metal/TradingAdapter.h>
#include "NewOrder.h"
#include "OrderCancelRequest.h"

namespace Metal {
namespace __namespace__ { 

class __namespace__Adapter : public TradingAdapter {
	public:
		__namespace__Adapter();

		void encode( const NewOrderSingle &nos, Message &msg);
		void encodeLogon( Message &msg);

		virtual void recv( const ExecutionReport &er);

		virtual ~__namespace__Adapter(){};
};

} // namespace __namespace__
} // namespace Metal

#endif // __METAL___NAMESPACE__ADAPTER_H
