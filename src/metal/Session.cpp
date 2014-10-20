#include <iostream>
#include <algorithm>

#include <metal/Session.h>

namespace Metal {

using namespace std;

Session::Session(int heartBeatInterval, int retryInterval) {
	changeStatus(IDLE);
	this->granularity = chrono::seconds( min( heartBeatInterval, retryInterval) / 2);

	this->heartBeatIntervalInSeconds = heartBeatInterval;
	this->retryIntervalInSeconds = retryInterval;

	// envertually start the thread
	this->hbThread = thread(&Session::run, this);
}


Session::~Session() {
	kill();
	hbThread.join();
}

void Session::changeStatus(SessionStatus newStatus) {
	this->statusMutex.lock();
	this->status = newStatus;
	this->statusMutex.unlock();
}

void Session::run() {
//	cout << "HeartBeat: thread is running" << endl;
	clock_t lastBeat = 0;
	float maxClocksHeartBeat = (float)( this->heartBeatIntervalInSeconds * CLOCKS_PER_SEC);
	float maxClocksRetry = (float)( this->retryIntervalInSeconds * CLOCKS_PER_SEC);

	bool loopHappily = true;

	while( loopHappily) {
		this_thread::sleep_for(this->granularity);

		this->statusMutex.lock();
		switch (this->status) {
		case IDLE:
			//cout << "HeartBeat: Suspended" << endl;
			break;
		case CONNECTING:
			// Just wait for connection
			break;
		case CONNECTED:
			onConnection();
			// We should be sending a logon
			changeStatus( LOGGING);
			sendLogon();
			break;

		case LOGGED: { // send the heatbeat if the time is reight
			clock_t now = clock();
			if (float(now - lastBeat) >= maxClocks) {
				heartBeat();
				lastBeat = now;
			}
		}
			break;

		case KILLING:
			loopHappily = false;
			break;

		case DISCONNECTED:
			if( this->retryInterval > 0 && float( now - lastConnectionAttempt) >= maxClocksRetry) {
				// TODO: Retry the connection
			}
			break;

		}
		this->statusMutex.unlock();
	}
//	cout << "HeartBeat: thread is stopping" << endl;

}

void Session::start() {
	changeStatus( CONNECTING);
}

void Session:stop() {
	changeStatus( SUSPENDING);
}

void Session::kill() {
	changeStatus( KILLING);
}

}
