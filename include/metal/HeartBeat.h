#ifndef __METAL_HEARTBEAT_H
#define __METAL_HEARTBEAT_H

#include <thread>
#include <mutex>

namespace Metal {

enum HeartBeatStatus { SUSPENDED, RUNNING, STOPPING};

class HeartBeater {
public:
	/**
	 * Constructor
	 * @param interval number of seconds between heartbeats
	 */
	HeartBeater( int interval);
	~HeartBeater();

	/**
	 * Resume message sending
	 */
	void resumeHeartBeats();

	/**
	 * Stops the heartbeat thread for good.
	 */
	void stopHeartBeats();

	/**
	 * suspend messages
	 */
	void suspendHeartBeats();

protected:
	/**
	 * Thread safe function to change status
	 */
	void changeStatus(HeartBeatStatus newStatus);

	/**
	 * This function should be implemented by subclasses when a beat is triggered
	 */
	virtual void heartBeat() = 0;


private:
	std::thread hbThread;
	/**
	 * How often should we look at the watch. interval should be a multiple of granularity
	 * For example interval = 30s and Granularity = 10s
	 */
	std::chrono::seconds granularity;
	int intervalInSeconds;
	bool keepBeating;
	HeartBeatStatus status;
	std::mutex statusMutex;

	/**
	* This method is meant to be used at the thread entry point
	*/
	void run();

};

}

#endif // __METAL_HEARTBEAT_H

