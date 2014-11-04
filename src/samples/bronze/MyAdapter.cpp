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

/**
 * Display whatever is available
 */
void MyAdapter::onExecutionReport( const Metal::ExecutionReport &er) {
	std::cout << "\nExecution Report:";
	if (er.isSetField(FIX::FIELD::ClOrdID)) {
		FIX::ClOrdID clOrdID;
		er.getField(clOrdID);
		std::cout << " clOrdID=" << clOrdID;
	}

	if (er.isSetField(FIX::FIELD::OrderID)) {
		FIX::OrderID orderID;
		er.getField(orderID);
		std::cout << " orderID=" << orderID;
	}

	if (er.isSetField(FIX::FIELD::ExecID)) {
		FIX::ExecID execID;
		er.getField(execID);
		std::cout << " execID=" << execID;
	}

	if (er.isSetField(FIX::FIELD::ExecID)) {
		FIX::ExecType execType;
		er.getField(execType);
		std::cout << " execType=" << Metal::Translator::field(execType);
	}

	if (er.isSetField(FIX::FIELD::OrdStatus)) {
		FIX::OrdStatus ordStatus;
		er.getField(ordStatus);
		std::cout << " status=" << Metal::Translator::field(ordStatus);
	}

	if (er.isSetField(FIX::FIELD::Symbol)) {
		FIX::Symbol symbol;
		er.getField(symbol);
		std::cout << " symbol=" << symbol;
	}

	if (er.isSetField(FIX::FIELD::Side)) {
		FIX::Side side;
		er.getField(side);
		std::cout << " side=" << Metal::Translator::field( side);
	}

	if (er.isSetField(FIX::FIELD::LeavesQty)) {
		FIX::LeavesQty leavesQty;
		er.getField(leavesQty);
		std::cout << " leavesQty=" << leavesQty;
	}

	if (er.isSetField(FIX::FIELD::CumQty)) {
		FIX::CumQty cumQty;
		er.getField(cumQty);
		std::cout << " cumQty=" << cumQty;
	}

	// mimic prompt
	std::cout << "\n> " << std::flush;
}

