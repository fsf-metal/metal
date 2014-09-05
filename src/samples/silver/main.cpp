#include <iostream>
#include <csignal>
#include <cstdlib>
#include <chrono>
#include <thread>

#include "InboundFIXSession.h"

using namespace std;

InboundFIXSession ifs;

void handler(int s) {
	cout << "Ctrl+C caught" << endl;
	ifs.stop();
	cout << "Cleanup done." << endl;

	exit( 1);
}

int main( int argc, char *argv[]) {
	try {
		struct sigaction sigIntHandler;
		chrono::minutes delay(10);

		ifs.start();

		// install a signal handler to catch Ctrl+C
		sigIntHandler.sa_handler = handler;
		sigemptyset(&sigIntHandler.sa_mask);
		sigIntHandler.sa_flags = 0;
		sigaction(SIGINT, &sigIntHandler, NULL);

		cout << "Press Ctrl+C to interrupt or wait for timeout" << endl;

		this_thread::sleep_for( delay);
		ifs.stop();
		cout << "Normal timeout shutdown" << endl;

		return 0;
	} catch(std::exception &e) {
		cerr << "Exception: " << e.what() << endl;
		return 1;
	} catch( FIX::FieldNotFound &e) {
		cerr << "FieldNotFound Exception" << endl;
		return 1;
	} catch( FIX::IncorrectDataFormat &e) {
		cerr << "IncorrectDataFormat Exception" << endl;
		return 1;
	} catch( FIX::IncorrectTagValue &e) {
		cerr << "IncorrectTagValue Exception" << endl;
		return 1;
	} catch( FIX::RejectLogon &e) {
		cerr << "RejectLogon Exception" << endl;
		return 1;
	} catch(...) {
		cerr << "Exception" << endl;
		return 1;
	}
}

