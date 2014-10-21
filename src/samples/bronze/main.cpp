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

vector<string> split(const string &s, char delim);

/**
 * Our main function is a loop for all commands
 * We are expecting "exit" at some point
 * Otherwise we keep parsing incoming text into NewOrderSingle and send them through Output
 */
int main( int argc, char *argv[]) {

	// Windows requires a favor to start WinSock
#ifdef _WIN32
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;

	/* Use the MAKEWORD(lowbyte, highbyte) macro declared in Windef.h */
	wVersionRequested = MAKEWORD(2, 2);

	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0) {
		/* Tell the user that we could not find a usable */
		/* Winsock DLL.                                  */
		cerr << "WSAStartup failed with error: " << err << endl;
		return 1;
	}
#endif

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

	while( true) {
		try {
			cout << "> "; // Mighty prompt
			getline(cin, command);
			if( command == "") continue;
			if (command == "exit") break;
			if (command == "stop") {
				adapter.stop();
			} else if (command.substr( 0,4) == "host") {
				vector<string> tokens =	split(command, ' ');
				if (tokens.size() != 3) throw runtime_error( "Expecting two arguments for \"host\"");
				adapter.setRemoteHost( tokens.at(1), (unsigned int)atoi( tokens.at(2).c_str()) );
			} else if (command == "start") {
				adapter.start();
			} else {

				// Transform command into NewOrderSingle (implemented in parsing.cpp)
				parseNOS(command, nos);
				adapter.send(nos);
				cout << "Order sent " << nos.getField(11) << endl;
			}
		} catch( ParsingException &e) {
			cerr << "Parsing failed: " << e.what() << endl;
		} catch( exception &e) {
			cerr << "Something failed: " << e.what() << endl;
		} catch (...) {
			cerr << "Something else failed" << endl;
		}
	}

	adapter.stop();

	cout << "Good Bye!" << endl;

	return 0;
}



std::vector<std::string> split(const std::string &s, char delim) {
	std::vector<std::string> elems;

	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		elems.push_back(item);
	}

	return elems;
}
