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
#include "metal.h"
// This is our custom Implementation of some adapter
#include "Adapter.h"
// and petty parsing
#include "parsing.h"


/**
 * Our main function is a loop for all commands
 * We are expecting "exit" at some point
 * Otherwise we keep parsing incoming text into NewOrderSingle and send them through Output
 */
int main( int argc, char *argv[]) {

	std::cout << "---------------------------------------------------------------" << std::endl;
	std::cout << " Please type in your commands then \"exit\" when you are done" << std::endl;
	std::cout << " Orders should be entered using {Side} {Qty} {Symbol} [Price]" << std::endl;
	std::cout << " If price is omitted, \"market\" is assumed" << std::endl;
	std::cout << " Example: \"buy 10 BA\" => Buys 10 Boeing @ Market" << std::endl;
	std::cout << " Example: \"sell 20 INTC 35 \" => Sells 10 Intel @ 35.0" << std::endl;
	std::cout << "---------------------------------------------------------------" << std::endl;

	std::string command;
	Metal::NewOrderSingle nos;
	Adapter adapter;

	adapter.start();

	while( true) {
		std::cout << "> "; // Mighty prompt
		getline( std::cin, command);
		if( command == "exit") break;
//		std::cout << "Processing \"" << command << "\"" << std::endl;
		try {
			parseNOS( command, nos);
			adapter.send( nos);
			std::cout << "Order sent " << nos.getField(11) << std::endl;
		} catch( ParsingException &e) {
			std::cerr << "Parsing failed: " << e.what() << std::endl;
		} catch( std::exception &e) {
			std::cerr << "Something failed: " << e.what() << std::endl;
		}
	}

	adapter.stop();

	std::cout << "Good Bye!" << std::endl;

	return 0;
}


