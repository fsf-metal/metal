#include <quickfix/FieldNumbers.h>
#include <metal/MappingException.h>
#include "LSEMessageMapper.h"
#include "LSEValues.h"

namespace Metal {
namespace LSE {
/**
 * Translate LSE NewOrder into Metal representation
 */
void LSEMessageMapper::map( const NewOrder& message,
                                 NewOrderSingle &nos){
	std::cout << "LSEMessageMapper: NewOrderSingle map invoked (LSE->MeTAL) but not implemented" << std::endl;

}

/**
 * NewOrderSingle MeTAL -> LSE
 * @throws FIX::FieldNotFound
 */
void LSEMessageMapper::map( const Metal::NewOrderSingle &nos, Metal::LSE::NewOrder &newOrder) {
	// Client Order ID @4 L20
	FIX::ClOrdID clOrdID;
	nos.getField( clOrdID);
	newOrder.clientOrderID = clOrdID;

    // Trader ID @24 L11
	// TODO => Where should we read from?
	newOrder.traderID.clear();

    // Account @35 L10
	if( nos.isSetField( FIX::FIELD::Account)) {
		newOrder.account = nos.getField( FIX::FIELD::Account);
	}

    // Clearing Account @45 L1
	// TODO => Should be read from FIX
	newOrder.clearingAccount = LSE::ClearingAccount_CLIENT;

    // Instrument ID @46 L4
	newOrder.instrumentID = nos.getField( FIX::FIELD::Symbol);

    // OrderType @52 L1
    FIX::OrdType ordType;
    nos.getField( ordType);

    switch( ordType) {
		case FIX::OrdType_MARKET: newOrder.orderType = LSE::OrderType_MARKET; break;
		case FIX::OrdType_LIMIT: newOrder.orderType = LSE::OrderType_LIMIT; break;
		case FIX::OrdType_STOP: newOrder.orderType = LSE::OrderType_STOP; break;
		case FIX::OrdType_STOP_LIMIT: newOrder.orderType = LSE::OrderType_STOP_LIMIT; break;
		default:
			std::stringstream message( "Unknown value for order type ");
			message << ordType;
			throw MappingException( message.str());
    }

    // Time in Force @53 L1
    if( nos.isSetField( FIX::FIELD::TimeInForce)) {
    	FIX::TimeInForce tif;
    	nos.getField( tif);
    	switch( tif) {
    	case FIX::TimeInForce_DAY: newOrder.timeInForce = LSE::TimeInForce_DAY; break;
    	case FIX::TimeInForce_IMMEDIATE_OR_CANCEL: newOrder.timeInForce = LSE::TimeInForce_IMMEDIATE_OR_CANCEL; break;
    	case FIX::TimeInForce_FILL_OR_KILL: newOrder.timeInForce = LSE::TimeInForce_FILL_OR_KILL; break;
    	case FIX::TimeInForce_AT_THE_OPENING: newOrder.timeInForce = LSE::TimeInForce_AT_THE_OPENING; break;
    	case FIX::TimeInForce_GOOD_TILL_DATE: newOrder.timeInForce = LSE::TimeInForce_GOOD_TILL_DATE; break;
    	// FGAP => GoodTill Time is missing
    	//case FIX::TimeInForce_DAY: newOrder.timeInForce  = 0; break;
    	case FIX::TimeInForce_AT_THE_CLOSE: newOrder.timeInForce  = LSE::TimeInForce_AT_THE_CLOSE; break;
    	// FGAP => Good For Auction is missing
    	//case FIX::TimeInForce_: newOrder.timeInForce  = LSE::TimeInForce_GOOD_FOR_AUCTION; break;
    	// FGAP => Good for Intraday option is missing
    	// case FIX::TimeInForce_: newOrder.timeInForce  = LSE::TimeInForce_GOOD_FOR_INTRADAY_AUCTION; break;
    	default:
			std::stringstream message( "Unknown value for TimeInForce ");
			message << tif;
			throw MappingException( message.str());
    	}
    } else {
    	// Default to day
    	newOrder.timeInForce = TimeInForce_DAY;
    }

    // Expire date @54 L4
    // TODO implement for Good Till Date

    // Side &58 L1
    FIX::Side side;
    nos.getField( side);
    map( side, newOrder.side);

    // Order Qty @59 L4
    FIX::OrderQty ordQty;
    nos.getField( ordQty);
    newOrder.quantity = (Quantity)ordQty;

    // Display Qty @63 L4
    if( nos.isSetField( FIX::FIELD::DisplayQty)) {
    	FIX::DisplayQty displayQty;
    	nos.getField( displayQty);
    	newOrder.displayQty = (Quantity) displayQty;
    }

    // Limit Price @67 L8
    if( newOrder.orderType == LSE::OrderType_LIMIT || newOrder.orderType == LSE::OrderType_STOP_LIMIT) {
    	FIX::Price price;
    	nos.getField( price);
    	newOrder.price = (Price)( price * 100000000);
    }

    // Capacity @75 L1
    // Auto Cancel @76 L1
    // Order Sub Type @77 L1
    // Anonymity @78 L1
    // Stopped price @79 L8
    // Passive Only Order @87 L1
    // Reservered Field @88L 9
}

/**
 * OrderCancel Request Metal -> LSE
 */
void LSEMessageMapper::map( const Metal::OrderCancelRequest &ocrFrom, Metal::LSE::OrderCancelRequest &ocrTo) {
	// Client Order ID
	FIX::ClOrdID clOrdID;
	ocrFrom.getField( clOrdID);
	ocrTo.clientOrderID = clOrdID;

	// Original Client Order ID
	if( ocrFrom.isSetField( FIX::FIELD::OrigClOrdID)) {
		FIX::OrigClOrdID origClOrdId;
		ocrFrom.getField( origClOrdId);
		ocrTo.originalClientOrderId = origClOrdId;
	}

	// Order ID
	FIX::OrderID orderId;

	// Instrument ID
	FIX::Symbol symbol;
	ocrFrom.getField( symbol);
	ocrTo.symbol = symbol;

	// Side
	FIX::Side sideFrom;
	ocrFrom.getField( sideFrom);
	map( sideFrom, ocrTo.side);
}

/**
 * Side Metal -> LSE
 */
void LSEMessageMapper::map( const FIX::Side &sideFrom, Metal::LSE::Side &sideTo) {

    switch( sideFrom) {
		case FIX::Side_BUY: sideTo = LSE::Side_BUY; break;
		case FIX::Side_SELL: sideTo = LSE::Side_SELL; break;
		default:
			std::stringstream message( "Unknown value for Side ");
			message << sideTo;
			throw MappingException( message.str());
    }
}


/**
 * This is just a dumb loop that maps all incoming NewOrderSingle.
 * It has no other function than measuring mapping speed
 */
void LSEMessageMapper::benchmark( std::vector<NewOrderSingle> &allOrders) {
	NewOrder nosLSE;

	for( std::vector<NewOrderSingle>::iterator iter = allOrders.begin(); iter != allOrders.end(); ++iter) {
		map( *iter, nosLSE);
	}
}

/*inline void LSEMessageMapper::encodeInt32( const int value, char *message, int position) {
	message[position  ] = ( value & 0xFF000000) >> 24;
	message[position+1] = ( value & 0x00FF0000) >> 16;
	message[position+2] = ( value & 0x0000FF00) >> 8;
	message[position+3] = value & 0x000000FF;
}*/

} // namespace LSE
} // namespace Metal
