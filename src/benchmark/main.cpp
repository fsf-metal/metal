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
#include <metal/Mapper.h>
#include <metal/adapters/QuickFIXAdapter/QuickFIXAdapter.h>
#include <metal/adapters/LSETradingAdapter/MilleniumAdapter.h>

#include "CPU.h"

#define BATCH_SIZE 100000L
#define LOOPS      5L
#define SEP1 "============================================================"
#define SEP2 "------------------------------------------------------------"

using namespace Metal;

// measure average duration for LOOPS loops
long measureNOS( TradingAdapter * adapter, const std::vector<NewOrderSingle> &, bool );
long measureOCR( TradingAdapter * adapter, const std::vector<OrderCancelRequest> &, bool );

// Fills a string with random characters
void randomString(char *s, const int len);

// Output formatting
void displayResult( std::string title, long durationAll, long durationMappingOnly);


int main( int argc, char* argv[]) {

	// step 1 create a bunch of NewOrderSingle
	std::vector<NewOrderSingle> allOrders;
	std::vector<OrderCancelRequest> allCancels;
	allOrders.reserve( (size_t)BATCH_SIZE);
	allCancels.reserve( (size_t)BATCH_SIZE);


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
	std::cout << "Results will be averaged over " << LOOPS << " loops" << std::endl;
	std::string cpuDetails;
	CPU::getDetails(cpuDetails);
	std::cout << "CPU: " << cpuDetails << std::endl;


	// Find out which message mapper will be used
	// This is where custom adapter should go
	std::vector<TradingAdapter*> allAdapters;
	allAdapters.push_back( new QuickFIX::QuickFIXAdapter());
	allAdapters.push_back( new LSE::MilleniumAdapter());

	for( std::vector<TradingAdapter*>::iterator iter = allAdapters.begin(); iter != allAdapters.end(); ++iter) {
		std::cout << SEP1 << std::endl;
		std::cout << "Benchmarking : " << (*iter)->getName() << std::flush;

		long durationNOS = measureNOS( *iter, allOrders, false);
		std::cout << "4..." << std::flush;
		long durationNOSMappingOnly = measureNOS( *iter, allOrders, true);
		std::cout << "3..." << std::flush;
		long durationOCR = measureOCR( *iter, allCancels, false);
		std::cout << "2..." << std::flush;
		long durationOCRMappingOnly = measureOCR( *iter, allCancels, true);
		std::cout << "1..." << std::endl;

		displayResult( "NewOrderSingle", durationNOS, durationNOSMappingOnly);
		displayResult( "OrderCancelRequest", durationOCR, durationOCRMappingOnly);

	}

	return 0;
}

long measureNOS( TradingAdapter * adapter, const std::vector<NewOrderSingle> &allOrders, bool mappingOnly) {
	long totalDuration = 0;
	for (int count = 0; count < LOOPS; ++count) {

		auto start = std::chrono::system_clock::now();
		adapter->benchmark( allOrders, mappingOnly);
		auto stop = std::chrono::system_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

		totalDuration += (long)duration.count();
	}

	return totalDuration;
}

long measureOCR( TradingAdapter * adapter, const std::vector<OrderCancelRequest> &allCancels, bool mappingOnly) {
	long totalDuration = 0;
	for (int count = 0; count < LOOPS; ++count) {

		auto start = std::chrono::system_clock::now();
		adapter->benchmark( allCancels, mappingOnly);
		auto stop = std::chrono::system_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

		totalDuration += (long)duration.count();
	}

	return totalDuration;
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

void displayResult( std::string title, long durationAll, long durationMappingOnly) {
	using namespace std;
	string title2 = "Mapping+Encoding";
	string title3 = "Mapping Only";
	cout << SEP2 << endl;
	cout << title << " : " << title2 << " : " << title3 << endl;

	int width1 = title.length();
	int width2 = title2.length();
	int width3 = title3.length();

	string speedAll = durationAll == 0 ? "n/a" : to_string(LOOPS * BATCH_SIZE * 1000 / durationAll);
	string speedMappingOnly = durationAll == 0 ? "n/a" : to_string(LOOPS * BATCH_SIZE * 1000 / durationMappingOnly);

	cout << setw(width1) << "Messages/sec" << " : " << setw(width2) << speedAll << " : " << setw(width3) << speedMappingOnly << endl;
	cout << setw(width1) << "Nanos/Msg" << " : " << setw(width2) << ((durationAll * 1000000) / ( LOOPS * BATCH_SIZE )) << " : " << setw(width3) << ((durationMappingOnly * 1000000) / ( LOOPS * BATCH_SIZE )) << endl;
}
