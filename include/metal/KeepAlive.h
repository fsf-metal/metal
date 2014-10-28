/*
    MeTAL: My Electronic Trading Adapters Library
    Copyright 2014 Jean-Cedric JOLLANT (jc@jollant.net)

    This file is part of MeTAL.

	MeTAL is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	MeTAL is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with MeTAL source code. If not, see <http://www.gnu.org/licenses/>.

*/
#ifndef __METAL_KEEPALIVE_H
#define __METAL_KEEPALIVE_H

#include <thread>
#include <mutex>

namespace Metal {

// enum SessionStatus { IDLE, CONNECTING, CONNECTED, LOGGING, LOGGED, DISCONNECTED, SUSPENDING, KILLING};

/**
 * This class is responsible for sending heartbeats and retrying lost connections<br>
 * Actions are based on a status which can be changed using KeepAlive::changeStatus()<br>
 * Checks are perfomed in a dedicated thread which checks status and reacts accordingly
 */
class KeepAlive {
public:
	/**
	 * Constructor
	 * @param interval number of seconds between heartbeats
	 */
	KeepAlive(int hearBeatInterval, int retryInterval);
	~KeepAlive();

	/**
	 * These are the possible statuses for keep alive.<br>
	 * You can suspend operation using IDLE or terminate the thread using KILLED
	 */
	enum Status { IDLE, CONNECTING, HEARTBEATING, RETRYING, KILLED };

	/**
	 * Thread safe function to change status
	 */
	void changeStatus( Status newStatus);

	/**
	 * Thread safe method to get current status
	 */
	const Status getStatus();

	static std::string getStatusName(const Status &status, std::string &output);

protected:

	/**
	 * This function should be implemented by subclasses when a beat needs to be sent
	 */
	virtual void heartBeat() = 0;

	/**
	* This function should be implemented by subclasses when a connection should be attempted
	*/
	virtual void retryConnection() = 0;

	int getHeartBeatInterval() { return this->heartBeatIntervalInSeconds; };
	int getRetryInterval() { return this->retryIntervalInSeconds; };

private:
	/**
	 * This thead will loop until the status is set to KILLED
	 */
	std::thread thread;

	/**
	 * How often should we look at the watch. interval should be a multiple of granularity
	 * For example interval = 30s and Granularity = 10s
	 */
	std::chrono::seconds granularity;
	int heartBeatIntervalInSeconds;
	int retryIntervalInSeconds;

	/**
	 * Stores the current status
	 */
	Status status;
	/**
	 * Used for status synchronization
	 */
	std::mutex statusMutex;

	/**
	* This method is meant to be used at the thread entry point
	*/
	void run();

};

}

#endif // __METAL_KEEPALIVE_H

