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

// FIX Google Protocol Buffer Generated File
#include "singlegeneralorderhandling.pb.h"
// This is our custom Implementation of some adapter
#include "Output.h"

void parseNOS( const std::string& cmd, SingleGeneralOrderHandling::NewOrderSingle &);

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
	SingleGeneralOrderHandling::NewOrderSingle nos;
	Output output;

	output.start();

	while( true) {
		std::cout << "> "; // Mighty prompt
		std::cin >> command;
		if( command == "exit") break;
		std::cout << "Processing " << command << std::endl;
		try {
			parseNOS( command, nos);
		} catch( std::exception &e) {
			std::cerr << "Parsing failed: " << e.what() << std::endl;
		}
		try {
			output.send( nos);
		} catch( std::exception &e) {
			std::cerr << "Sending failed: " << e.what() << std::endl;
		}
	}

	output.stop();

	std::cout << "Good Bye!" << std::endl;

	return 0;
}

/**
 * This is a simple split utility to process command by tokens
 */
std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

void parseNOS( const std::string &cmd, SingleGeneralOrderHandling::NewOrderSingle &nos) {
	// Perform split and basic validation
	std::vector<std::string> tokens;
	split( cmd, ' ', tokens);
	if( tokens.size() < 3 || tokens.size() > 4) throw new std::exception();

	// Client Order ID : Generated from current time
	std::stringstream ss;
	time_t now = std::time(0);
	ss << now;
	nos.set_cl_ord_id( ss.str());

	// Instrument, 2nd position
	::Common::Instrument instrument( tokens[1]);
	nos.set_allocated_instrument( &instrument);

	// Side, 1st position
	SingleGeneralOrderHandling::SideEnum side;
	if( tokens[0] == "buy") side == SingleGeneralOrderHandling::SideEnum::SIDE_BUY;
	if( tokens[0] == "sell") side == SingleGeneralOrderHandling::SideEnum::SIDE_SELL;
	nos.set_side( side);

	// Transacttime : now
	nos.set_transact_time( now);

	// Quantity, 3rd position
	::Common::OrderQtyData qtyData;
	qtyData.set_order_qty( std::stoi( tokens[2]));
	nos.set_allocated_order_qty_data( &qtyData);

	// Price, 4th position

}

