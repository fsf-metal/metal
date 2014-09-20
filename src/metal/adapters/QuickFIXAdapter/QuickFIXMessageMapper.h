#ifndef __QUICKFIXMESSAGEMAPPER_H
#define __QUICKFIXMESSAGEMAPPER_H

#include <metal/metal.h>
#include <metal/MessageMapper.h>
#include <quickfix/fix44/NewOrderSingle.h>
#include <quickfix/fix44/ExecutionReport.h>
#include <quickfix/fix44/OrderCancelRequest.h>

namespace Metal {

class QuickFIXMessageMapper : public MessageMapper {
	public:
        // FIX to MeTAL
		static void map( const FIX44::NewOrderSingle&, NewOrderSingle&);
		static void map( const FIX44::ExecutionReport&, ExecutionReport&);

		/**
		 * MeTAL to FIX44 transformation for NewOrderSingle
		 */
		static void map( const NewOrderSingle&, FIX::Message&);

		/**
		* MeTAL to FIX44 transformation for OrderCancelRequest
		*/
		static void map(const OrderCancelRequest&, FIX::Message &);
};

}

#endif // __QUICKFIXMESSAGEMAPPER_H
