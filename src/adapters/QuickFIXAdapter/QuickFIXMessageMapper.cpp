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
		er.setField( *fieldIterator, message.getField( *fieldIterator));
	}
}

/**
 * NewOrderSingle MeTAL -> FIX50sp2
 */
void QuickFIXMessageMapper::map( const NewOrderSingle &nos, 
                                 FIX::Message &message) {
	int fields[6] = { 
		FIX::FIELD::ClOrdID,
		55, // Symbol
		54, // Side
		60, // TransactTime
		38, // OrdQty
		40 }; // OrdType

	for (int index = 0; index < 6; ++index) {
		int field = fields[index];
		message.setField( field, nos.getField( field));
	}

	// Price if needed
	try {
		message.setField(FIX::FIELD::Price, nos.getField(FIX::FIELD::Price));
	} catch (FIX::FieldNotFound &) { }

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
