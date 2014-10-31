#ifndef __METAL_AQUIS_ADAPTER_H
#define __METAL_AQUIS_ADAPTER_H

#include <metal/TradingAdapter.h>

// TODO generate your own from
// http://www.famkruithof.net/uuid/uuidgen
#define UUID "874bd640-47e3-11e4-916c-0800200c9a66"

namespace Metal {
namespace Aquis {

class Adapter : public TradingAdapter {
	public:
		Adapter();

		void encode( const NewOrderSingle &nos, Message &msg);
		void encodeLogon( Message &msg);

		virtual void recv( const ExecutionReport &er);

		virtual ~Adapter(){};
};

} // Aquis
} // namespace Metal

#endif // __METAL_AQUIS_ADAPTER_H
