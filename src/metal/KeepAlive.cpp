#include <iostream>
#include <algorithm>

#include <metal/KeepAlive.h>

namespace Metal {

using namespace std;

KeepAlive::KeepAlive(int heartBeatInterval, int retryInterval) {
	this->status = IDLE;
	this->granularity = chrono::seconds( min( heartBeatInterval, retryInterval) / 2);

	this->heartBeatIntervalInSeconds = heartBeatInterval;
	this->retryIntervalInSeconds = retryInterval;

	// envertually start the thread
	this->thread = std::thread(&KeepAlive::run, this);
}


KeepAlive::~KeepAlive() {
	changeStatus(KILLED);
	this->thread.join();
}

void KeepAlive::changeStatus( Status newStatus) {
//	string statusName;
//	cout << "KeepAlive: Changing status to " << getStatusName( newStatus, statusName).c_str() << endl;

	this->statusMutex.lock();
	this->status = newStatus;
	this->statusMutex.unlock();
}

string KeepAlive::getStatusName( const Status &status, string &output) {
	switch (status) {
	case IDLE: output = "Idle"; break;
	case HEARTBEATING: output = "HeartBeating"; break;
	case RETRYING: output = "Retrying"; break;
	case KILLED: output = "Killed"; break;
	default: output = "?";
	}

	return output;
}

void KeepAlive::run() {
//	cout << "HeartBeat: thread is running" << endl;
	clock_t lastBeat = 0;
	clock_t lastRetry = 0;
	float maxClocksHeartBeat = (float)( this->heartBeatIntervalInSeconds * CLOCKS_PER_SEC);
	float maxClocksRetry = (float)( this->retryIntervalInSeconds * CLOCKS_PER_SEC);

	bool loopHappily = true;

	while( loopHappily) {
		this_thread::sleep_for(this->granularity);

		this->statusMutex.lock();
		Status status = this->status;
		this->statusMutex.unlock();
		switch (this->status) {
		case IDLE:
			// Watchout, this can be quite verbose
			// cout << "KeepAlive: Idle" << endl;
			break;

		case HEARTBEATING: { // send the heatbeat if the time is reight
			// cout << "KeepAlive: Heartbeat" << endl;
			clock_t now = clock();
			if( float(now - lastBeat) >= maxClocksHeartBeat) {
				heartBeat();
				lastBeat = now;
			}
		}
			break;

		case RETRYING: { // retry the connection if the timming is right
			//cout << "KeepAlive: Retry" << endl;
			clock_t now = clock();
			if (float(now - lastRetry) >= maxClocksRetry) {
				retryConnection();
				lastRetry = now;
			}
		}
			break;

		case KILLED:
			cout << "KeepAlive: Killed" << endl;
			loopHappily = false;
			break;

		}
	}
//	cout << "HeartBeat: thread is stopping" << endl;

}

}
