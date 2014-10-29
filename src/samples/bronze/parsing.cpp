//============================================================================
// Name        : parsing.cpp
// Author      : Jean-Cedric JOLLANT
// Version     :
// Copyright   : Please read LICENCE.txt
// Description : Turn a string into NewOrderSingle
//============================================================================

#include <iostream>
#include <ctime>
#include <sstream>
#include <string>

// Where the data models are defined
#include <metal/metal.h>
// and petty parsing
#include "parsing.h"

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

/**
 * This is where the action goes.
 * We are tuning a string into NewOrderSingle
 */
void parseNOS( const std::string &cmd, Metal::NewOrderSingle &nos) {
	// Perform split and basic validation
	std::vector<std::string> tokens;
	split( cmd, ' ', tokens);
	if( tokens.size() < 3 || tokens.size() > 4) throw ParsingException("Invalid command length. Should be 3 or 4 words.");

	// Client Order ID : Generated from current time
	std::stringstream ss;
	time_t now = std::time(0); // we memorize "now" which will be reused
	ss << now;
	nos.setField( FIX::ClOrdID( ss.str()));

	// Instrument, 3rd position
	nos.setField( FIX::Symbol( tokens[2]));

	// Side, 1st position
	FIX::Side side;
	if( tokens[0] == "buy") side = FIX::Side_BUY;
	else if( tokens[0] == "sell") side = FIX::Side_SELL;
	else throw ParsingException( "Unknown Side. Should be \"buy\" or \"sell\" ");
	nos.setField( side);

	// Transacttime : now
	FIX::UTCTIMESTAMP nowUTC;
	nos.setField( FIX::TransactTime( nowUTC));

	// Quantity, 2nd position
	nos.setField( FIX::OrderQty(std::stoi( tokens[1])));

	// Price, 4th position
	FIX::OrdType type;
	if( tokens.size() == 3) { 
		// Market Order
		type = FIX::OrdType_MARKET;
	} else { 
		// Limit Order
		type = FIX::OrdType_LIMIT;
		nos.setField( FIX::Price( std::stof( tokens[3])));
	}
	nos.setField( type);

}

