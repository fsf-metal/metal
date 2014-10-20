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
	this->statusMutex.lock();
	this->status = newStatus;
	this->statusMutex.unlock();
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
		switch (this->status) {
		case IDLE:
			//cout << "HeartBeat: Suspended" << endl;
			break;

		case HEARTBEATING: { // send the heatbeat if the time is reight
			clock_t now = clock();
			if( float(now - lastBeat) >= maxClocksHeartBeat) {
				heartBeat();
				lastBeat = now;
			}
		}
			break;

		case RETRYING: { // retry the connection if the timming is right
			clock_t now = clock();
			if (float(now - lastRetry) >= maxClocksRetry) {
				retryConnection();
				lastRetry = now;
			}
		}
			break;

		case KILLED:
			loopHappily = false;
			break;

		}
		this->statusMutex.unlock();
	}
//	cout << "HeartBeat: thread is stopping" << endl;

}

}
