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
void QuickFIXMessageMapper::map( const FIX44::ExecutionReport &message,
                                 ExecutionReport &er){
	std::vector<int> fields = { 6, // AvgPx
			                    11, // ClOrdID
			                    14, // CumQty
			                    17, // ExecID
			                    31, // LastPx
			                    32, // LastQty
			                    37, // OrderID
			                    39, // OrdStatus
			                    54, // Side
			                    150, // ExecType
			                    151}; // LeavesQty

	// Copy all fields
	for( std::vector<int>::iterator fieldIterator = fields.begin(); fieldIterator != fields.end(); ++fieldIterator) {
		std::cout << "Mapping:" << *fieldIterator << std::endl;
		er.setField( *fieldIterator, message.getField( *fieldIterator));
	}
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

/**
 * This is just a dumb loop that maps all incoming NewOrderSingle.
 * It has no other function than measuring mapping speed
 */
void QuickFIXMessageMapper::benchmark( std::vector<NewOrderSingle> &allOrders) {
	FIX44::NewOrderSingle nos44;

	for( std::vector<NewOrderSingle>::iterator iter = allOrders.begin(); iter != allOrders.end(); ++iter) {
		map( *iter, nos44);
	}
}


}
