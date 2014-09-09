/**
 * This sample application is a simple example of MeTAL Adapter instanciation
 * We create a QuickFIX Session which will be deemed client facing (client)
 * On the other side we are using a MeTAL Trading Adapter (adapter)
 * Both classes are customized to forward data to one another which creates
 * a simple FIX to Native translator.
 *
 * The typical work flow should be as follows:
 * (client) -> FIX44::NewOrder -> (adapter) -> Native::NewOrder -> Exchange
 * Exchange -> Native::ExecReport -> (adapter) -> FIX44::ExecReport -> (client)
 *
 * Please have a look at OutboundAdapter for implementation details
 * InboundFIXSession is a Slighlty Customized QuickFIX implementation
 */

#include <iostream>
#include <csignal>
#include <cstdlib>
#include <chrono>
#include <thread>

#include "InboundFIXSession.h"
#include "OutboundAdapter.h"

using namespace std;

// NewOrderSingle will flow in from client to adapter
// ExecutionReports will take the opposite route
InboundFIXSession client;
OutboundAdapter adapter;

void installHandler();
void handler(int s); 

/**
 * We start both connections and wait for Ctrl-C or 10 minutes
 * Whichever happens first will close both connections
 */
int main( int argc, char *argv[]) {
	try {
		chrono::minutes delay(10);

		// make each party aware of each other for message translation
		client.setTradingAdapter( &adapter);
		// TODO set client session on adapter
		
		// Start both conversations
		client.start();
		adapter.start();

		// install a signal handler to catch Ctrl+C
		installHandler();

		cout << "Press Ctrl+C to interrupt or wait for timeout" << endl;

		this_thread::sleep_for( delay);
		client.stop();
		adapter.stop();
		cout << "Normal timeout shutdown" << endl;

		return 0;
	} catch(std::exception &e) {
		cerr << "Exception: " << e.what() << endl;
		return 1;
	} catch(...) {
		cerr << "Exception" << endl;
		return 1;
	}
}

/**
 * This handler is used when Ctrl+C is caught
 * The intent is to close open sessions
 */
void handler(int s) {
	cout << "Ctrl+C caught" << endl;
	client.stop();
	adapter.stop();
	cout << "Cleanup done." << endl;

	exit( 1);
}

void installHandler() {
	struct sigaction sigIntHandler;
	sigIntHandler.sa_handler = handler;
	sigemptyset(&sigIntHandler.sa_mask);
	sigIntHandler.sa_flags = 0;
	sigaction(SIGINT, &sigIntHandler, NULL);
}

