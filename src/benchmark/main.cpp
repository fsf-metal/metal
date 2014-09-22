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

#include <metal/metal.h>
#include <metal/MessageMapper.h>
#include <metal/adapters/QuickFIXAdapter/QuickFIXAdapter.h>
#include <metal/adapters/LSETradingAdapter/MilleniumAdapter.h>

#define BATCH_SIZE 50000L
#define LOOPS      3L

using namespace Metal;

// Fills a string with random characters
void randomString(char *s, const int len);

int main( int argc, char* argv[]) {

	// step 1 create a bunch of NewOrderSingle
	std::vector<NewOrderSingle> allOrders;
	std::vector<OrderCancelRequest> allCancels;
	allOrders.reserve(BATCH_SIZE);
	allCancels.reserve(BATCH_SIZE);


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
		int qty = (int)(rand() * 100);
		pNos->setField(FIX::OrderQty(qty));
		pNos->setField(FIX::OrdType( FIX::OrdType_LIMIT));
		pNos->setField(FIX::Price(rand()*1000));

		allOrders.push_back( *pNos);

		OrderCancelRequest * pOcr = new OrderCancelRequest();

		pOcr->setField(FIX::ClOrdID(clOrdID));
		pOcr->setField(FIX::Symbol(symbol));
		pOcr->setField(FIX::Side(side));
		pOcr->setField(FIX::TransactTime(time(NULL)));
		pOcr->setField(FIX::OrderQty(qty));

		allCancels.push_back(*pOcr);

	}

	std::cout << "Allocated " << BATCH_SIZE << " random NewOrderSingle and OrderCancelRequest" << std::endl;

	// Find out which message mapper will be used
	// This is where custom adapter should go
	std::vector<TradingAdapter*> allAdapters;
	allAdapters.push_back( new QuickFIX::QuickFIXAdapter());
	allAdapters.push_back( new LSE::MilleniumAdapter());

	for( std::vector<TradingAdapter*>::iterator iter = allAdapters.begin(); iter != allAdapters.end(); ++iter) {
		long totalDurationNOS = 0;
		long totalDurationOCR = 0;
		std::cout << "------------------------------------------------------------" << std::endl;
		std::cout << "Benchmarking : " << (*iter)->getName() << std::endl;
		std::cout << "New Order Single:" << std::endl;
		for (int count = 0; count < LOOPS; ++count) {

			auto start = std::chrono::system_clock::now();
			(*iter)->benchmark( allOrders);
			auto stop = std::chrono::system_clock::now();
			auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

			std::cout << "  Mapped and Encoded " << BATCH_SIZE << " New Orders in " << duration.count() << "ms" << std::endl;
			totalDurationNOS += (long)duration.count();
		}

		std::cout << "Average speed " << (LOOPS * BATCH_SIZE * 1000 / totalDurationNOS) << " nos/sec over " << LOOPS << " loops" << std::endl;
		std::cout << "That is " << ((totalDurationNOS * 1000000) / ( LOOPS * BATCH_SIZE )) << " nanosecond/nos" << std::endl;

		std::cout << "Order Cancel Requests:" << std::endl;
		for (int count = 0; count < LOOPS; ++count) {

			auto start = std::chrono::system_clock::now();
			(*iter)->benchmark(allCancels);
			auto stop = std::chrono::system_clock::now();
			auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

			std::cout << "  Mapped and Encoded " << BATCH_SIZE << " Order Cancel Request in " << duration.count() << "ms" << std::endl;
			totalDurationOCR += (long)duration.count();
		}

		std::string ocr_sec = (totalDurationOCR == 0) ? "n/a" : std::to_string( LOOPS * BATCH_SIZE * 1000 / totalDurationOCR);
		std::cout << "Average speed " << ocr_sec << " ocr/sec over " << LOOPS << " loops" << std::endl;
		std::cout << "That is " << ((totalDurationOCR * 1000000) / (LOOPS * BATCH_SIZE)) << " nanosecond/ocr" << std::endl;
	}

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

