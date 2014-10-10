#include <iostream>

#include <metal/HeartBeat.h>

namespace Metal {

using namespace std;

HeartBeater::HeartBeater(int interval) {
	changeStatus(SUSPENDED);
	this->granularity = chrono::seconds( interval / 3);
	this->intervalInSeconds = interval;

	// envertually start the thread
	this->hbThread = thread(&HeartBeater::run, this);
}


HeartBeater::~HeartBeater() {
	stopHeartBeats();
	hbThread.join();
}

void HeartBeater::changeStatus(HeartBeatStatus newStatus) {
	this->statusMutex.lock();
	this->status = newStatus;
	this->statusMutex.unlock();
}

void HeartBeater::run() {
//	cout << "HeartBeat: thread is running" << endl;
	clock_t lastBeat = 0;
	float maxClocks = (float)( this->intervalInSeconds * CLOCKS_PER_SEC);

	bool loopHapily = true;

	while( loopHapily) {
		this_thread::sleep_for(this->granularity);

		this->statusMutex.lock();
		switch (this->status) {
		case STOPPING: 
			loopHapily = false; 
			break;
		case SUSPENDED: 
			//cout << "HeartBeat: Suspended" << endl;
			break;

		case RUNNING: {
			clock_t now = clock();
			if (float(now - lastBeat) >= maxClocks) {
				heartBeat();
				lastBeat = now;
			}
		}break;

		}
		this->statusMutex.unlock();
	}
//	cout << "HeartBeat: thread is stopping" << endl;

}

void HeartBeater::resumeHeartBeats() {
	changeStatus( RUNNING);
}

void HeartBeater::stopHeartBeats() {
	changeStatus( STOPPING);
}

void HeartBeater::suspendHeartBeats() {
	changeStatus( SUSPENDED);
}

}
