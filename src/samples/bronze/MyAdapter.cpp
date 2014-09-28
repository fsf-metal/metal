/*
 * Adapter.cpp
 *
 *  Created on: Sep 10, 2014
 *      Author: jc
 */

#include <metal/Translator.h>
#include "MyAdapter.h"

MyAdapter::MyAdapter() {
	// TODO Auto-generated constructor stub

}

MyAdapter::~MyAdapter() {
	// TODO Auto-generated destructor stub
}

void MyAdapter::recv( const Metal::ExecutionReport &er) {
	FIX::OrderID orderID;
	er.getField(orderID);

	FIX::ExecID execID;
	er.getField(execID);

	FIX::ExecType execType;
	er.getField(execType);

	FIX::ClOrdID clOrdID;
	er.getField( clOrdID);

	FIX::OrdStatus ordStatus;
	er.getField( ordStatus);

	FIX::Symbol symbol;
	er.getField(symbol);

	FIX::Side side;
	er.getField(side);

	FIX::LeavesQty leavesQty;
	er.getField(leavesQty);

	FIX::CumQty cumQty;
	er.getField(cumQty);

	// report and mimic prompt
	std::cout << "\nExecution Report: clOrdID=" << clOrdID;
	std::cout << " status=" << Metal::Translator::field(ordStatus);
	std::cout << " orderID=" << orderID;
	std::cout << " execID=" << execID;
	std::cout << " execType=" << execType;
	std::cout << " symbol=" << symbol;
	std::cout << " side=" << side;
	std::cout << " leavesQty=" << leavesQty;
	std::cout << " cumQty=" << cumQty;

	std::cout << "\n> " << std::flush;
}

