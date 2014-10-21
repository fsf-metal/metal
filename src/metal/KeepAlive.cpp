#include <iostream>
#include <algorithm>
#include <chrono>
#include <ctime>
#include <string>

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

	cout << "KeepAlive started with HBInt=" << to_string(heartBeatInterval) << ", RetryInt=" << to_string(retryInterval) << endl;
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

const KeepAlive::Status KeepAlive::getStatus() {

	this->statusMutex.lock();
	Status output = this->status;
	this->statusMutex.unlock();

	return output;
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
	chrono::time_point<chrono::system_clock> lastBeat, lastRetry;
	lastBeat = chrono::system_clock::now();
	lastRetry = lastBeat;

	bool loopHappily = true;

	while( loopHappily) {
		this_thread::sleep_for(this->granularity);

//		string output;
//		cout << "KeepAlive: " << getStatusName( getStatus(), output) << endl;
		switch (getStatus()) {
		case IDLE:
			// Watchout, this can be quite verbose
			// cout << "KeepAlive: Idle" << endl;
			break;

        case CONNECTING:    
            // Just wait for connection
            break;

		case HEARTBEATING: { // send the heatbeat if the time is reight
			// cout << "KeepAlive: Heartbeat" << endl;
			using namespace chrono;
			time_point<system_clock> now = system_clock::now();
			duration<double> elapsed = now - lastBeat;
			if( elapsed.count() > this->heartBeatIntervalInSeconds) {
				heartBeat();
				lastBeat = now;
			}
		}
			break;

		case RETRYING: { // retry the connection if the timming is right
			//cout << "KeepAlive: Retry" << endl;
			using namespace chrono;
			time_point<system_clock> now = system_clock::now();
			duration<double> elapsed = now - lastRetry;
			if( elapsed.count() > this->retryIntervalInSeconds) {
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
