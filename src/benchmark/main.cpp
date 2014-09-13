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

#define BATCH_SIZE 50000L
#define LOOPS      3L

using namespace Metal;

int main( int argc, char* argv[]) {

	// step 1 create a bunch of NewOrderSingle
	std::vector<NewOrderSingle> allOrders;
	allOrders.reserve(BATCH_SIZE);


	for( int index = 0; index < BATCH_SIZE; index++) {
		NewOrderSingle * pNos = new NewOrderSingle();

		pNos->setField(FIX::ClOrdID("LKdq23"));
		pNos->setField(FIX::Symbol("APOOI"));
		pNos->setField(FIX::Side(FIX::Side_BUY));
		pNos->setField(FIX::TransactTime(FIX::Side_BUY));
		pNos->setField(FIX::OrderQty(100));
		pNos->setField(FIX::OrdType( FIX::OrdType_LIMIT));
		pNos->setField(FIX::Price(10.5));

		allOrders.push_back( *pNos);
	}

	std::cout << "Allocated " << allOrders.size() << " NewOrderSingle" << std::endl;

	// Find out which message mapper will be used
	// This is where custom adapter should go
	QuickFIXAdapter adapter;
	MessageMapper *mapper = adapter.getMessageMapper();

	long totalDuration = 0;
	for (int count = 0; count < LOOPS; ++count) {

		auto start = std::chrono::system_clock::now();
		mapper->benchmark( allOrders);
		auto stop = std::chrono::system_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

		std::cout << "Mapped " << BATCH_SIZE << " orders in " << duration.count() << "ms" << std::endl;
		totalDuration += duration.count();
	}

	std::cout << "Average speed " << (LOOPS * BATCH_SIZE * 1000 / totalDuration) << " nos/sec over " << LOOPS << " loops" << std::endl;

	delete mapper;

	return 0;
}



