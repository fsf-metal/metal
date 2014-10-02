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
#include <algorithm>

#include <metal/metal.h>
#include <metal/Mapper.h>
#include <metal/adapters/QuickFIXAdapter/QuickFIXAdapter.h>
#include <metal/adapters/LSETradingAdapter/MilleniumAdapter.h>

#include "Display.h"

#define BATCH_SIZE 100000L
#define LOOPS      5L
#define SEP1 "============================================================"
#define SEP2 "------------------------------------------------------------"

using namespace Metal;
using namespace std;

// Fills a string with random characters
void randomString(char *s, const int len);

// Output formatting
void displayResult( string title, chrono::milliseconds durationMapping, chrono::milliseconds durationEncoding);


int main( int argc, char* argv[]) {

	// step 1 create a bunch of NewOrderSingle
	vector<NewOrderSingle> allOrders;
	vector<OrderCancelRequest> allCancels;
	allOrders.reserve( BATCH_SIZE);
	allCancels.reserve( BATCH_SIZE);


	for( int index = 0; index < BATCH_SIZE; index++) {
		NewOrderSingle * pNos = new NewOrderSingle();
		FIX::UTCTIMESTAMP now;

        char clOrdID[16];
        randomString( clOrdID, 15);
		pNos->setField(FIX::ClOrdID( clOrdID));
        char symbol[6];
        randomString( symbol, 6);
		pNos->setField(FIX::Symbol( symbol));
        FIX::Side side = rand() >=0/5 ? FIX::Side_BUY : FIX::Side_SELL;
		pNos->setField(FIX::Side(side));
		pNos->setField(FIX::TransactTime(now));
		int qty = (int)(rand() * 100);
		pNos->setField(FIX::OrderQty(qty));
		pNos->setField(FIX::OrdType( FIX::OrdType_LIMIT));
		pNos->setField(FIX::Price(rand()*1000));

		allOrders.push_back( *pNos);

		OrderCancelRequest * pOcr = new OrderCancelRequest();

		pOcr->setField(FIX::ClOrdID(clOrdID));
		pOcr->setField(FIX::Symbol(symbol));
		pOcr->setField(FIX::Side(side));
		pOcr->setField(FIX::TransactTime(now));
		pOcr->setField(FIX::OrderQty(qty));

		allCancels.push_back(*pOcr);

	}

	cout << "Allocated " << BATCH_SIZE << " random NewOrderSingle and OrderCancelRequest" << endl;
	cout << "Results will be averaged over " << LOOPS << " loops" << endl;
	string cpuDetails;
	Display::getCPUDescription(cpuDetails);
	cout << "CPU : " << cpuDetails << endl;
	string osDescription;
	Display::getOSDescription(osDescription);
	cout << "OS  : " << osDescription << endl;

	// what should be benchmarked?
	vector<TradingAdapter*> allAdapters;
	allAdapters.push_back(new QuickFIX::QuickFIXAdapter());
	allAdapters.push_back(new LSE::MilleniumAdapter());

	unsigned int selection;
	while( true) {
		cout << SEP1 << endl;
		cout << "Please choose which adapter should be benchmarked:" << endl;
		cout << setw(4) << 0 << ". All" << endl;
		for (unsigned int index = 0; index < allAdapters.size(); ++index) {
			cout << setw(4) << to_string(index + 1) << ". " << (allAdapters.at(index))->getName() << endl;
		}
		cout << "[0-" << to_string(allAdapters.size()) << "]: " << flush;
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

	for( vector<TradingAdapter*>::iterator iter = selectedAdapters.begin(); iter != selectedAdapters.end(); ++iter) {
		cout << endl << SEP1 << endl;
		cout << "Benchmarking : " << (*iter)->getName() << " " << flush;

		int index = 2 * LOOPS;
		chrono::milliseconds durationMapping, durationEncoding;
		chrono::milliseconds durationNOSMapping(0);
		chrono::milliseconds durationNOSEncoding(0);
		chrono::milliseconds durationOCRMapping(0);
		chrono::milliseconds durationOCREncoding(0);

		// We are benchmarking several times to reduce anomalies
		for( int loop = 0; loop < LOOPS; ++loop) {
			cout << to_string(index--) << ".." << flush;

			// this is the actual benchmarking
			(*iter)->benchmark(allOrders, durationMapping, durationEncoding);

			durationNOSMapping += durationMapping;
			durationNOSEncoding += durationEncoding;

			cout << to_string(index--) << ".." << flush;

			// this is the actual benchmarking
			(*iter)->benchmark(allCancels, durationMapping, durationEncoding);

			durationOCRMapping += durationMapping;
			durationOCREncoding += durationEncoding;
		}
		cout << endl;

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

void displayResult( string title, chrono::milliseconds durationMapping, chrono::milliseconds durationEncoding) {
	using namespace std;
	string title2 = "Mapping";
	string title3 = "Encoding";
	string title4 = "Combined";

	int width1 = title.length();
	int width2 = title2.length();
	int width3 = title3.length();
	int width4 = title4.length();

	string speedMapping = durationMapping.count() == 0 ? "n/a" : Display::formatWithCommas((long)(LOOPS * BATCH_SIZE * 1000L / durationMapping.count()));
	string speedEncoding = durationEncoding.count() == 0 ? "n/a" : Display::formatWithCommas((long)(LOOPS * BATCH_SIZE * 1000L / durationEncoding.count()));
	long totalDuration = (long)( durationMapping.count() + durationEncoding.count());
	string speedTotal = totalDuration == 0 ? "n/a" : Display::formatWithCommas(LOOPS * BATCH_SIZE * 1000L / totalDuration);

	width2 = max( width2, (int)speedMapping.length());
	width3 = max( width3, (int)speedEncoding.length());
	width4 = max( width4, (int)speedTotal.length());

	cout << SEP2 << endl;
	cout << setw(width1) << title << " : " << setw(width2) << title2 << " : " << setw(width3) << title3 << " : " << setw(width4) << title4 << endl;

	cout << setw(width1) << "Messages/sec" << " : ";
	cout << setw(width2) << speedMapping << " : ";
	cout << setw(width3) << speedEncoding << " : ";
	cout << setw(width4) << speedTotal;
	cout << endl;
	cout << setw(width1) << "Nanos/Msg" << " : ";
	cout << setw(width2) << Display::formatWithCommas((long)(((double)durationMapping.count() * 1000000.) / (double)(LOOPS * BATCH_SIZE))) << " : ";
	cout << setw(width3) << Display::formatWithCommas((long)(((double)durationEncoding.count() * 1000000.) / (double)(LOOPS * BATCH_SIZE))) << " : ";
	cout << setw(width4) << Display::formatWithCommas( (long)( ( ( double)totalDuration * 1000000.) / ( double)(LOOPS * BATCH_SIZE)));
	cout << endl;
}
