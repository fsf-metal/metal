/*
 * main.cpp
 *
 *  Created on: Sep 12, 2014
 *      Author: jc
 *     Purpose: Measure how fast adapters map their messages
 */


#include <iostream>
#include <vector>
#include <chrono>

#include "metal.h"
#include "MessageMapper.h"
#include "QuickFIXAdapter/QuickFIXAdapter.h"

#define BATCH_SIZE 10000

using namespace Metal;

int main( int argc, char* argv[]) {

	QuickFIXAdapter adapter;

	// step 1 create a bunch of NewOrderSingle
	std::vector<NewOrderSingle> allOrders(BATCH_SIZE);

	for( int index = 0; index < BATCH_SIZE; index++) {
		NewOrderSingle * pNos = new NewOrderSingle();
		pNos->setField( FIX::AvgPx(1.0));
		pNos->setField( FIX::ClOrdID("Asdlklksd"));
		pNos->setField( FIX::CumQty(100));
		pNos->setField( FIX::ExecID("ASSAS"));
		pNos->setField( FIX::LastPx(1.25));
		pNos->setField( FIX::LastQty(152));
		pNos->setField( FIX::OrderID("DFDSKLJFD"));
		pNos->setField( FIX::OrdStatus( FIX::OrdStatus_FILLED));
		pNos->setField( FIX::Side( FIX::Side_BUY));
		pNos->setField( FIX::ExecType( FIX::ExecType_FILL));
		pNos->setField( FIX::LeavesQty( 10));
		allOrders.push_back( *pNos);
	}

	std::cout << "Allocated " << allOrders.size() << " NewOrderSingle" << std::endl;

	MessageMapper *mapper = adapter.getMessageMapper();

	auto start = std::chrono::system_clock::now();
	mapper->benchmark( allOrders);
	auto stop = std::chrono::system_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

	std::cout << "Mapped " << BATCH_SIZE << " orders in " << duration.count() << "ms" << std::endl;

	delete mapper;

	return 0;
}



