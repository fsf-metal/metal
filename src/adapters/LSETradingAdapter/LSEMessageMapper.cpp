#include "LSEMessageMapper.h"
#include "quickfix/FieldNumbers.h"

namespace Metal {
/**
 * Translate FIX NewOrderSingle into Metal representation
 */
void LSEMessageMapper::map( const LSENewOrder& message,
                                 NewOrderSingle &nos){
	std::cout << "LSEMessageMapper: NewOrderSingle map invoked (LSE->MeTAL) but not implemented" << std::endl;

}

/**
 * NewOrderSingle MeTAL -> LSE
 */
void LSEMessageMapper::map( const NewOrderSingle &nos,
                                 LSENewOrder &message) {
	// Client Order ID @4 L20
    strncpy( &message[4], (const char*)nos.getField( FIX::FIELD::ClOrdID), 20);

    // Trader ID
    message[35] = 0;

    // Account

    // Clearing Account

    // Instrument ID @46 L4
    strncpy( &message[46], (const char *)nos.getField( FIX::FIELD::Symbol), 4);

    // OrderType @52 L1
    FIX::OrdType ordType;
    nos.getField( ordType);
    switch( ordType) {
		case FIX::OrdType_MARKET: &message[52] = LSE::OrdType_MARKET; break;
		case FIX::OrdType_LIMIT: &message[52] = LSE::OrdType_LIMIT; break;
		case FIX::OrdType_STOP: &message[52] = LSE::OrdType_STOP; break;
		case FIX::OrdType_STOP_LIMIT: &message[52] = LSE::OrdType_STOP_LIMIT; break;
		default: throw MappingException( "Unknown value for order type " << ordType);
    }

    // Time in Force @53 L1
    if( nos.isSetField( FIX::FIELD::TimeInForce)) {
    	FIX::TimeInForce tif;
    	nos.getField( tif);
    	switch( tif) {
    	case FIX::TimeInForce_DAY: &message[53] = LSE::TimeInForce_DAY; break;
    	case FIX::TimeInForce_IMMEDIATE_OR_CANCEL: &message[53] = LSE::TimeInForce_IMMEDIATE_OR_CANCEL; break;
    	case FIX::TimeInForce_FILL_OR_KILL: &message[53] = LSE::TimeInForce_FILL_OR_KILL; break;
    	case FIX::TimeInForce_AT_THE_OPENING: &message[53] = LSE::TimeInForce_AT_THE_OPENING; break;
    	case FIX::TimeInForce_GOOD_TILL_DATE: &message[53] = LSE::TimeInForce_GOOD_TILL_DATE; break;
    	// FGAP => GoodTill Time is missing
    	//case FIX::TimeInForce_DAY: &message[53] = 0; break;
    	case FIX::TimeInForce_AT_THE_CLOSE: &message[53] = LSE::TimeInForce_AT_THE_CLOSE; break;
    	// FGAP => Good For Auction is missing
    	//case FIX::TimeInForce_: &message[53] = LSE::TimeInForce_GOOD_FOR_AUCTION; break;
    	// FGAP => Good for Intraday option is missing
    	// case FIX::TimeInForce_: &message[53] = LSE::TimeInForce_GOOD_FOR_INTRADAY_AUCTION; break;
    	default:
    		throw MappingException( "Unknown value for TimeInForce " << tif);
    	}
    } else {
    	// Default to day
    	&message[53] = LSE::TimeInForce_DAY;
    }

    // Expire date @54 L4
    // TODO implement for Good Till Date

    // Side &58 L1
    FIX::Side side;
    nos.getField( side);
    switch( side) {
		case FIX::Side_BUY: &message[58] = LSE::Side_BUY; break;
		case FIX::Side_SELL: &message[58] = LSE::Side_SELL; break;
		default: throw MappingException( "Unknown value for Side " << side);
    }

    // Order Qty @59 L4
    FIX::OrderQty ordQty;
    nos.getField( ordQty);
    encodeInt32( (int)ordQty, message, 59);

    // Display Qty @63 L4
    if( nos.isSetField( FIX::FIELD::DisplayQty)) {
    	FIX::DisplayQty displayQty;
    	nos.getField( displayQty);
    	encodeInt32( (int)displayQty, message, 63);
    }

    // Limit Price @67 L8
}

/**
 * This is just a dumb loop that maps all incoming NewOrderSingle.
 * It has no other function than measuring mapping speed
 */
void LSEMessageMapper::benchmark( std::vector<NewOrderSingle> &allOrders) {
	LSENewOrder nosLSE;

	for( std::vector<NewOrderSingle>::iterator iter = allOrders.begin(); iter != allOrders.end(); ++iter) {
		map( *iter, nosLSE);
	}
}

inline void LSEMessageMapper::encodeInt32( const int value, char *message, int position) {
	message[position  ] = ( value & 0xFF000000) >> 24;
	message[position+1] = ( value & 0x00FF0000) >> 16;
	message[position+2] = ( value & 0x0000FF00) >> 8;
	message[position+3] = value & 0x000000FF;
}


}
