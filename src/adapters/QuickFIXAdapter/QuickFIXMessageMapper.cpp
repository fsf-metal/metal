#include "QuickFIXMessageMapper.h"

/**
 * Translate FIX NewOrderSingle into fixprotobuf representation
 */
void QuickFIXMessageMapper::map( const FIX44::NewOrderSingle &message, 
                                 NewOrderSingle &nos){
	std::cout << "QuickFIXMessageMapper: NewOrderSingle map invoked (FIX44->MeTAL) but not implemented" << std::endl;

}

/**
 * Execution Report FIX -> fixprotobuf
 */
void QuickFIXMessageMapper::map( const FIX42::ExecutionReport &, 
                                 ExecutionReport &){
	std::cout << "QuickFIXMessageMapper: ExecutionReport map invoked but not implemented" << std::endl;
}

void QuickFIXMessageMapper::map( const NewOrderSingle &nos, 
                                 FIX42::NewOrderSingle &message) {
	std::cout << "QuickFIXMessageMapper: NewOrderSingle map invoked (metal->FIX42) but not implemented" << std::endl;
}

