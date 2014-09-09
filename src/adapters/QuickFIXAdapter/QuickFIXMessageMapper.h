#ifndef __QUICKFIXMESSAGEMAPPER_H
#define __QUICKFIXMESSAGEMAPPER_H

#include "quickfix/fix44/NewOrderSingle.h"
#include "quickfix/fix42/ExecutionReport.h"
#include "quickfix/fix42/NewOrderSingle.h"
#include "singlegeneralorderhandling.pb.h"

class QuickFIXMessageMapper {
	public:
        // FIX to protobuf
		static void map( const FIX44::NewOrderSingle&, SingleGeneralOrderHandling::NewOrderSingle&);
		static void map( const FIX42::ExecutionReport&, SingleGeneralOrderHandling::ExecutionReport&);
        // protobuf to FIX
		static void map( const SingleGeneralOrderHandling::NewOrderSingle&, FIX42::NewOrderSingle&);
        static void mapSide( const SingleGeneralOrderHandling::SideEnum& from, FIX::Side& to);
};

#endif // __QUICKFIXMESSAGEMAPPER_H
