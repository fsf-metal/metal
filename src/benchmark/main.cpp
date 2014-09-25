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

// Fills a string with random characters
void randomString(char *s, const int len);

// Output formatting
void displayResult( std::string title, std::chrono::milliseconds durationMapping, std::chrono::milliseconds durationEncoding);

using namespace std;


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
		pNos->setField(FIX::TransactTime(time( (time_t *)NULL)));
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

	// what should be benchmarked?
	std::vector<TradingAdapter*> allAdapters;
	allAdapters.push_back(new QuickFIX::QuickFIXAdapter());
	allAdapters.push_back(new LSE::MilleniumAdapter());

	bool validSelection = false;
	unsigned int selection;
	while( true) {
		std::cout << SEP1 << std::endl;
		cout << "Please choose which adapter should be benchmarked: [0-" << to_string(allAdapters.size()) << "]" << endl;
		cout << setw(4) << 0 << ". All" << endl;
		for (unsigned int index = 0; index < allAdapters.size(); ++index) {
			cout << setw(4) << to_string(index + 1) << ". " << (allAdapters.at(index))->getName() << endl;
		}
		cin >> selection;
		if (selection <= allAdapters.size()) break;

		cout << "Incorrect input, please pick a number between 0 and " << to_string(allAdapters.size()) << endl;
		continue;
	} 

	// at this point, we should have a proper selection
	// let's turn it into a vector of trading adapters
	vector<TradingAdapter*> selectedAdapters;
	if (selection == 0) {
		selectedAdapters = allAdapters;
	}
	else {
		selectedAdapters.push_back(allAdapters.at(selection - 1));
	}

	for( std::vector<TradingAdapter*>::iterator iter = selectedAdapters.begin(); iter != selectedAdapters.end(); ++iter) {
		std::cout << SEP1 << std::endl;
		std::cout << "Benchmarking : " << (*iter)->getName() << " " << std::flush;

		int index = 2 * LOOPS;
		std::chrono::milliseconds durationMapping, durationEncoding;
		std::chrono::milliseconds durationNOSMapping;
		std::chrono::milliseconds durationNOSEncoding;
		std::chrono::milliseconds durationOCRMapping;
		std::chrono::milliseconds durationOCREncoding;

		// We are benchmarking several times to reduce anomalies
		for( int loop = 0; loop < LOOPS; ++loop) {
			std::cout << std::to_string(index--) << ".." << std::flush;
			// this is the meat
			(*iter)->benchmark(allOrders, durationMapping, durationEncoding);
			durationNOSMapping += durationMapping;
			durationNOSEncoding += durationEncoding;

			std::cout << std::to_string(index--) << ".." << std::flush;
			(*iter)->benchmark(allCancels, durationMapping, durationEncoding);
			durationOCRMapping += durationMapping;
			durationOCREncoding += durationEncoding;
		}
		std::cout << std::endl;

		displayResult( "NewOrderSingle", durationNOSMapping, durationNOSEncoding);
		displayResult( "OrderCancelRequest", durationOCRMapping, durationOCREncoding);

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

void displayResult( std::string title, std::chrono::milliseconds durationMapping, std::chrono::milliseconds durationEncoding) {
	using namespace std;
	string title2 = "Mapping";
	string title3 = "Encoding";
	string title4 = "Combined";

	cout << SEP2 << endl;
	cout << title << " : " << title2 << " : " << title3 << " : " << title4 << endl;

	int width1 = title.length();
	int width2 = title2.length();
	int width3 = title3.length();
	int width4 = title4.length();

	string speedMapping = durationMapping.count() == 0 ? "n/a" : to_string(LOOPS * BATCH_SIZE * 1000L / durationMapping.count());
	string speedEncoding = durationEncoding.count() == 0 ? "n/a" : to_string(LOOPS * BATCH_SIZE * 1000L / durationEncoding.count());
	long totalDuration = (long)( durationMapping.count() + durationEncoding.count());
	string speedTotal = totalDuration == 0 ? "n/a" : to_string(LOOPS * BATCH_SIZE * 1000L / totalDuration);

	cout << setw(width1) << "Messages/sec" << " : ";
	cout << setw(width2) << speedMapping << " : ";
	cout << setw(width3) << speedEncoding << " : ";
	cout << setw(width4) << speedTotal;
	cout << endl;
	cout << setw(width1) << "Nanos/Msg" << " : ";
	cout << setw(width2) << to_string((long)(((double)durationMapping.count() * 1000000.) / (double)(LOOPS * BATCH_SIZE))) << " : ";
	cout << setw(width3) << to_string((long)(((double)durationEncoding.count() * 1000000.) / (double)(LOOPS * BATCH_SIZE))) << " : ";
	cout << setw(width4) << to_string( (long)( ( ( double)totalDuration * 1000000.) / ( double)(LOOPS * BATCH_SIZE)));
	cout << endl;
}
