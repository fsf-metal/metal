/*
 * Adapter.cpp
 *
 *  Created on: Sep 10, 2014
 *      Author: jc
 */

#include "Adapter.h"
#include "Translator.h"

Adapter::Adapter() {
	// TODO Auto-generated constructor stub

}

Adapter::~Adapter() {
	// TODO Auto-generated destructor stub
}

void Adapter::recv( const Metal::ExecutionReport &er) {
	FIX::ClOrdID clOrdID;
	er.getField( clOrdID);
	FIX::OrdStatus ordStatus;
	er.getField( ordStatus);

	// report and mimic prompt
	std::cout << "\nExecution Report: order " << clOrdID << " is \"" << Metal::Translator::field(ordStatus) << "\"\n> " << std::flush;
}

