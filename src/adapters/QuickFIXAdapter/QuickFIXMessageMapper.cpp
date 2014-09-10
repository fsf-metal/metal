#include "QuickFIXMessageMapper.h"
#include <google/protobuf/text_format.h>

/**
 * Translate FIX NewOrderSingle into fixprotobuf representation
 */
void QuickFIXMessageMapper::map( const FIX44::NewOrderSingle &message, 
                                 SingleGeneralOrderHandling::NewOrderSingle &nos){
	FIX::ClOrdID clOrdID;
	message.get( clOrdID);
	nos.set_cl_ord_id( clOrdID);

	std::cout << "QuickFIXMessageMapper: NewOrderSingle map invoked but not implemented" << std::endl;

}

/**
 * Execution Report FIX -> fixprotobuf
 */
void QuickFIXMessageMapper::map( const FIX42::ExecutionReport &, 
                                 SingleGeneralOrderHandling::ExecutionReport &){
	std::cout << "QuickFIXMessageMapper: ExecutionReport map invoked but not implemented" << std::endl;
}

void QuickFIXMessageMapper::map( const SingleGeneralOrderHandling::NewOrderSingle &nos, 
                                 FIX42::NewOrderSingle &message) {
    if( nos.has_cl_ord_id()) {
        message.setField( FIX::ClOrdID(nos.cl_ord_id()));
    } else {
        // TODO throw exception
    }
    // TODO map Handle Instance
    message.setField( FIX::HandlInst(1));
   
    if( nos.has_instrument()) { 
        if( nos.instrument().has_symbol()) {
            message.setField( FIX::Symbol( nos.instrument().symbol()));
        } else {
            // TODO throw exception
        }
    } else {
        // TODO throw exception
    }

    if( nos.has_side()) {
        FIX::Side side;
        mapSide( nos.side(), side);
        message.setField( side);
    } else {
        // TODO throw exception
    }

    if( nos.has_transact_time()) {
        // TODO map transca time
        FIX::UtcTimeStamp transactTime;
        message.setField( FIX::TransactTime( nos.transact_time()));
    } else {
        // TODO throw exception
    }

    // Qty
    if( nos.has_order_qty_data()) {
           if( nos.order_qty_data().has_order_qty()) {
                message.setField( FIX::OrderQty( nos.order_qty_data().order_qty()));
           }
    }

    // TODO map Order Type
    message.setField( FIX::OrdType(1));

    // TODO map price if needed

    std::string str1;
    google::protobuf::TextFormat::PrintToString( nos, &str1);
    std::string str2;
    str2 = message.toString();
    std::cout << "QuickFIXMessageMappe: Mapped " << str1 << " into " << str2 << std::endl;
}

void QuickFIXMessageMapper::mapSide( const SingleGeneralOrderHandling::SideEnum& from, FIX::Side& to) {
    using namespace SingleGeneralOrderHandling;
    switch( from) {
        case SIDE_BUY: to = FIX::Side_BUY; break;
        case SIDE_SELL: to = FIX::Side_SELL; break;
                        // TODO finish with the other stuff
                        // SIDE_BUY_MINUS = 1,
                        // SIDE_SELL_PLUS = 3,
                        // SIDE_SELL_SHORT = 4,
                        // SIDE_SELL_SHORT_EXEMPT = 5,
                        // SIDE_CROSS = 6,
                        // SIDE_UNDISCLOSED = 7,
                        // SIDE_CROSS_SHORT = 8,
                        // SIDE_AS_DEFINED = 9,
                        // SIDE_CROSS_SHORT_EXEMPT = 10, 
                        // SIDE_OPPOSITE = 11, 
                        // SIDE_BORROW = 12, 
                        // SIDE_LEND = 13, 
                        // SIDE_REDEEM = 14, 
                        // SIDE_SUBSCRIBE = 15
        default: to = FIX::Side_AS_DEFINED;
    }
}
