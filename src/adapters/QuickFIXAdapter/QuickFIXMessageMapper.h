#ifndef __QUICKFIXMESSAGEMAPPER_H
#define __QUICKFIXMESSAGEMAPPER_H

#include "../metal.h"
#include "../MessageMapper.h"
#include "quickfix/fix44/NewOrderSingle.h"
#include "quickfix/fix44/ExecutionReport.h"
#include "quickfix/fix42/NewOrderSingle.h"
#include "quickfix/fix42/ExecutionReport.h"

namespace Metal {

class QuickFIXMessageMapper : public MessageMapper {
	public:
        // FIX to MeTAL
		static void map( const FIX44::NewOrderSingle&, NewOrderSingle&);
		static void map( const FIX44::ExecutionReport&, ExecutionReport&);
        // MeTAL to FIX
		static void map( const NewOrderSingle&, FIX::Message&);
};

}

#endif // __QUICKFIXMESSAGEMAPPER_H
