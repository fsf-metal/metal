#ifndef __LSEMESSAGEMAPPER_H
#define __LSEMESSAGEMAPPER_H

#include "../metal.h"
#include "../MessageMapper.h"

namespace Metal {

typedef char LSENewOrder[89];
typedef char LSEExecutionReport[151];

class LSEMessageMapper : public MessageMapper {
	public:
        // LSE to MeTAL
		static void map( const LSENewOrder&, NewOrderSingle&);
        // MeTAL to LSE
		static void map( const NewOrderSingle&, LSENewOrder&);

        // only used by benchmarker
		void benchmark( std::vector<NewOrderSingle> &);
};

}

namespace LSE {
	const char OrdType_MARKET = 1;
	const char OrdType_LIMIT = 2;
	const char OrdType_STOP = 3;
	const char OrdType_STOP_LIMIT = 4;

	const char TimeInForce_DAY = 0;
	const char TimeInForce_IMMEDIATE_OR_CANCEL = 3;
	const char TimeInForce_FILL_OR_KILL = 4;
	const char TimeInForce_AT_THE_OPENING = 5;
	const char TimeInForce_GOOD_TILL_DATE = 6;
	const char TimeInForce_GOOD_TILL_TIME = 8;
	const char TimeInForce_AT_THE_CLOSE = 10;
	const char TimeInForce_GOOD_FOR_AUCTION = 50;
	const char TimeInForce_GOOD_FOR_INTRADAY_AUCTION = 51;
}

#endif // __LSEMESSAGEMAPPER_H
