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

// Fills a string with random characters
void randomString(char *s, const int len);

int main( int argc, char* argv[]) {

	// step 1 create a bunch of NewOrderSingle
	std::vector<NewOrderSingle> allOrders;
	allOrders.reserve(BATCH_SIZE);


	for( int index = 0; index < BATCH_SIZE; index++) {
		NewOrderSingle * pNos = new NewOrderSingle();

        char clOrdID[16];
        randomString( clOrdID, 15);
		pNos->setField(FIX::ClOrdID( clOrdID));
        char symbol[6];
        randomString( symbol, 6);
		pNos->setField(FIX::Symbol( symbol));
        FIX::Side side = rand() >=0/5 ? FIX::Side_BUY : FIX::Side_SELL;
		pNos->setField(FIX::Side(side));
		pNos->setField(FIX::TransactTime(time(NULL)));
		pNos->setField(FIX::OrderQty((int)(rand()*100)));
		pNos->setField(FIX::OrdType( FIX::OrdType_LIMIT));
		pNos->setField(FIX::Price(rand()*1000));

		allOrders.push_back( *pNos);
	}

	std::cout << "Allocated " << allOrders.size() << " random NewOrderSingle" << std::endl;

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

		std::cout << "Mapped and Encoded " << BATCH_SIZE << " New Orders in " << duration.count() << "ms" << std::endl;
		totalDuration += duration.count();
	}

	std::cout << "Average speed " << (LOOPS * BATCH_SIZE * 1000 / totalDuration) << " nos/sec over " << LOOPS << " loops" << std::endl;
	std::cout << "That is " << ((totalDuration * 1000000) / ( LOOPS * BATCH_SIZE )) << " nanosecond/nos" << std::endl;

	delete mapper;

	return 0;
}

void randomString(char *s, const int len) {
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

    for (int i = 0; i < len; ++i) {
        s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    s[len] = 0;
}

