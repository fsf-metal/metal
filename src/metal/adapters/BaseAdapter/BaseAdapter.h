#ifndef __METAL_BASEADAPTER_H
#define __METAL_BASEADAPTER_H

#include <metal/TradingAdapter.h>
#include "NewOrder.h"
#include "OrderCancelRequest.h"

// TODO generate your own from
// http://www.famkruithof.net/uuid/uuidgen
#define UUID "f3fc9d30-47e1-11e4-916c-0800200c9a66"

namespace Metal {
namespace Base { // TODO Replace Base with your own namespace

class BaseAdapter : public TradingAdapter {
	public:
		BaseAdapter();

		void encode( const NewOrderSingle &nos, Message &msg);
		void encodeLogon( Message &msg);

		virtual void recv( const ExecutionReport &er);

		virtual ~BaseAdapter(){};
};

} // LSE TODO replace with your own namespace
} // namespace Metal

#endif // __METAL_BASEADAPTER_H
