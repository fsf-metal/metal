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

		//
		inline static void encodeInt32( const int value, char *message, int position) {

};

}

namespace LSE {
	const char Anonymity_ANONYMOUS = 0;
	const char Anonymity_NAMED = 1;

	const char AutoCancel_DO_NOT_CANCEL = 0;
	const char AutoCancel_CHECK_SYSTEM_CONFIGURATION = 1;

	const char Capacity_RISKLESS_PRINCIPAL = 1;
	const char Capacity_PRINCIPAL = 2;
	const char Capacity_AGENCY = 3;
	const char Capacity_CFD_GIVE_UP = 4;

	const char ClearingAccount_CLIENT = 1;
	const char ClearingAccount_HOUSE = 3;

	const char OrderSubType_ORDER = 0;
	const char OrderSubType_PEGGED_ORDER = 5;
	const char OrderSubType_RANDOM_PEEK_SIZE = 51;

	const char OrdType_MARKET = 1;
	const char OrdType_LIMIT = 2;
	const char OrdType_STOP = 3;
	const char OrdType_STOP_LIMIT = 4;

	const char PassiveOnlyOrder_NO_CONSTRAINT = 0;
	const char PassiveOnlyOrder_IF_NOT_MATCH_WITH_VISIBLE_CONTRA = 99;
	const char PassiveOnlyOrder_IF_SETTING_NEW_VISIBLE_BBO = 100;
	const char PassiveOnlyOrder_SETTING_NEW_BBO_OR_JOINING_EXISTING_BBO = 1;
	const char PassiveOnlyOrder_IF_AT_BBO_OR_WITHIN_ONE_PRICE_POINT = 2;
	const char PassiveOnlyOrder_IF_AT_BBO_OR_WITHIN_TWO_PRICE_POINTS = 3;

	const char Side_BUY = 1;
	const char Side_SELL = 2;

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
