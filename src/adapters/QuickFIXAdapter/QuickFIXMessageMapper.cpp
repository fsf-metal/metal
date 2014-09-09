#include "QuickFIXMessageMapper.h"

void QuickFIXMessageMapper::map( const FIX44::NewOrderSingle &, SingleGeneralOrderHandling::NewOrderSingle &){
	std::cout << "QuickFIXMessageMapper: NewOrderSingle map invoked but not implemented" << std::endl;
}

/**
 * Execution Report FIX -> fixprotobuf
 */
void QuickFIXMessageMapper::map( const FIX42::ExecutionReport &, SingleGeneralOrderHandling::ExecutionReport &){
	std::cout << "QuickFIXMessageMapper: ExecutionReport map invoked but not implemented" << std::endl;
}

