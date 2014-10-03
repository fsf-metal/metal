//============================================================================
// Name        : bronze.cpp
// Author      : Jean-Cedric JOLLANT
// Version     :
// Copyright   : Please read LICENCE.txt
// Description : Basic Order Sending Using MeTAL Adapters
//============================================================================

#include <iostream>
#include <ctime>
#include <sstream>
#include <string>

// Where the data models are defined
#include <metal/metal.h>
// This is our custom Implementation of some adapter
#include "MyAdapter.h"
// and petty parsing
#include "parsing.h"

using namespace std;

/**
 * Our main function is a loop for all commands
 * We are expecting "exit" at some point
 * Otherwise we keep parsing incoming text into NewOrderSingle and send them through Output
 */
int main( int argc, char *argv[]) {

	cout << "---------------------------------------------------------------" << endl;
	cout << " Please type in your commands then \"exit\" when you are done" << endl;
	cout << " Orders should be entered using {Side} {Qty} {Symbol} [Price]" << endl;
	cout << " If price is omitted, \"market\" is assumed" << endl;
	cout << " Example: \"buy 10 BA\" => Buys 10 Boeing @ Market" << endl;
	cout << " Example: \"sell 20 INTC 35 \" => Sells 10 Intel @ 35.0" << endl;
	cout << "---------------------------------------------------------------" << endl;

	string command;
	Metal::NewOrderSingle nos;
	MyAdapter adapter;

	try {
		adapter.start();
	} catch (FIX::ConfigError &e) {
		cout << "Configuration error " << e.what() << endl;
		exit(2);
	}

	while( true) {
		cout << "> "; // Mighty prompt
		getline( cin, command);
		if( command == "exit") break;
//		cout << "Processing \"" << command << "\"" << endl;
		try {
			// Transform command into NewOrderSingle (implemented in parsing.cpp)
			parseNOS( command, nos);
			adapter.send( nos);
			cout << "Order sent " << nos.getField(11) << endl;
		} catch( ParsingException &e) {
			cerr << "Parsing failed: " << e.what() << endl;
		} catch( exception &e) {
			cerr << "Something failed: " << e.what() << endl;
		}
	}

	adapter.stop();

	cout << "Good Bye!" << endl;

	return 0;
}


