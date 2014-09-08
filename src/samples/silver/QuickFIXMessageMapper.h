#ifndef __QUICKFIXMESSAGEMAPPER_H
#define __QUICKFIXMESSAGEMAPPER_H

#include "quickfix/fix44/NewOrderSingle.h"
#include "singlegeneralorderhandling.pb.h"

class QuickFIXMessageMapper {
	public:
		static void map( FIX44::NewOrderSingle, SingleGeneralOrderHandling::NewOrderSingle);
};

#endif // __QUICKFIXMESSAGEMAPPER_H
