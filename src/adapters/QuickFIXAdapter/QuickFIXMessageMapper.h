#ifndef __QUICKFIXMESSAGEMAPPER_H
#define __QUICKFIXMESSAGEMAPPER_H

#include "quickfix/fix44/NewOrderSingle.h"
#include "quickfix/fix42/ExecutionReport.h"
#include "singlegeneralorderhandling.pb.h"

class QuickFIXMessageMapper {
	public:
		static void map( const FIX44::NewOrderSingle&, SingleGeneralOrderHandling::NewOrderSingle&);
		static void map( const FIX42::ExecutionReport&, SingleGeneralOrderHandling::ExecutionReport&);
};

#endif // __QUICKFIXMESSAGEMAPPER_H
