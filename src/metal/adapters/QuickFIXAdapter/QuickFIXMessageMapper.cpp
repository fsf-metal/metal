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
 * NewOrderSingle MeTAL -> FIX44
 */
void QuickFIXMessageMapper::map( const NewOrderSingle &nos,
                                 FIX::Message &message) {
	message.setField( FIX::FIELD::ClOrdID, nos.getField( FIX::FIELD::ClOrdID));
	message.setField( FIX::FIELD::Symbol, nos.getField( FIX::FIELD::Symbol));
	message.setField( FIX::FIELD::Side, nos.getField( FIX::FIELD::Side));
	message.setField( FIX::FIELD::TransactTime, nos.getField( FIX::FIELD::TransactTime));
	message.setField( FIX::FIELD::OrderQty, nos.getField( FIX::FIELD::OrderQty));
	FIX::OrdType ordType;
	message.setField( nos.getField( ordType));

	// Price if Limit order
	if( ordType == FIX::OrdType_LIMIT || ordType == FIX::OrdType_STOP_LIMIT) {
		message.setField(FIX::FIELD::Price, nos.getField(FIX::FIELD::Price));
	}
}

void QuickFIXMessageMapper::map(const OrderCancelRequest & ocr, FIX::Message &message) {
	message.setField(FIX::FIELD::ClOrdID, ocr.getField(FIX::FIELD::ClOrdID));
	message.setField(FIX::FIELD::Symbol, ocr.getField(FIX::FIELD::Symbol));
	message.setField(FIX::FIELD::Side, ocr.getField(FIX::FIELD::Side));
	message.setField(FIX::FIELD::TransactTime, ocr.getField(FIX::FIELD::TransactTime));
	message.setField(FIX::FIELD::OrderQty, ocr.getField(FIX::FIELD::OrderQty));

}

}
