#include "QuickFIXMessageMapper.h"

namespace Metal {
/**
 * Translate FIX NewOrderSingle into Metal representation
 */
void QuickFIXMessageMapper::map( const FIX44::NewOrderSingle &message, 
                                 NewOrderSingle &nos){
	std::cout << "QuickFIXMessageMapper: NewOrderSingle map invoked (FIX44->MeTAL) but not implemented" << std::endl;

}

/**
 * Execution Report FIX -> MeTAL
 */
void QuickFIXMessageMapper::map( const FIX42::ExecutionReport &, 
                                 ExecutionReport &){
	std::cout << "QuickFIXMessageMapper: ExecutionReport map invoked but not implemented" << std::endl;
}

/**
 * NewOrderSingle MeTAL -> FIX50sp2
 */
void QuickFIXMessageMapper::map( const NewOrderSingle &nos, 
                                 FIX::Message &message) {
	// Client Order ID
	FIX::ClOrdID clOrdID;
	nos.getField( clOrdID);
	message.setField( clOrdID);

	// Symbol
	FIX::Symbol symbol;
	nos.getField( symbol);
	message.setField( symbol);

	// Side
	FIX::Side side;
	message.setField( nos.getField( side), true);

	// Transaction Time
	FIX::TransactTime transactTime;
	message.setField( nos.getField( transactTime), true);

	// Order Quantity
	FIX::OrderQty ordQty;
	message.setField( nos.getField( ordQty), true);

	// Order Type
	FIX::OrdType ordType;
	message.setField( nos.getField( ordType), true);

	// Price if needed
	if( ordType == FIX::OrdType_LIMIT) {
		FIX::Price price;
		message.setField( nos.getField( price), true);
	}

}


}
