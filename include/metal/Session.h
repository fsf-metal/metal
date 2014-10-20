#ifndef __METAL_SESSION_H
#define __METAL_SESSION_H

#include <thread>
#include <mutex>

namespace Metal {

enum SessionStatus { IDLE, CONNECTING, CONNECTED, LOGGING, LOGGED, DISCONNECTED, SUSPENDING, KILLING};

/**
 * This class is responsible for managing session lifecycle<br>
 * The main duties are HeartBeats, Reconnections and Logons<br>
 * Checks are perfomed in a dedicated thread which checks status and reacts accordingly
 */
class Session {
public:
	/**
	 * Constructor
	 * @param interval number of seconds between heartbeats
	 */
	Session( int hearBeatInterval, int retryInterval);
	~Session();

	/**
	 * Starts the session
	 */
	void start();

	/**
	 * Stops session
	 */
	void stop();

	/**
	 * Kills session and associated thread
	 */
	void kill();

protected:
	/**
	 * Thread safe function to change status
	 */
	void changeStatus(SessionStatus newStatus);

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
	int heartBeatIntervalInSeconds;
	int retryIntervalInSeconds;
	bool keepBeating;
	SessionStatus status;
	std::mutex statusMutex;

	/**
	* This method is meant to be used at the thread entry point
	*/
	void run();

};

}

#endif // __METAL_SESSION_H

