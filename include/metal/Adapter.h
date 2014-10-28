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

#ifndef __METAL_ADAPTER_H
#define __METAL_ADAPTER_H

#include <string>
#include <thread>
#include <mutex>

#include <netlink/socket.h>
#include <netlink/socket_group.h>

namespace Metal {
	using namespace std;

	/**
	 * This class is responsible for reading inbound data as well as storing basic information about the adapter<br>
	 * Inbound data is read in a separate thread which entry point is Adapter#dataListenner()
	 */
	class Adapter {
	public:
		/**
		 * Constructor
		 * @param nameParam the actual adapter name in english
		 * @param uuidParam a unique adapter identifier. checkout http://www.famkruithof.net/uuid/uuidgen to create your own.
		 */
		Adapter(const string& nameParam, const string& uuidParam);

		/**
		 * Find out Adapter name
		 * @return Current adapter name
		 */
		const string & getName() { return this->name; };

		/**
		 * Retrieve Adapter Unique ID
		 * For example, this is used by benchmarking to report results<br>
		 * This is also used on the web site to identify adapters.
		 */
		const string & getUUID() { return this->uuid; };

		/**
		 * Starts the listenner thread
		 */
		virtual void start();

		/**
		 * Stops the listenner thread
		 */
		virtual void stop();

	protected:
		~Adapter();
		string name;
		string uuid;

		/**
		* This is the active socket
		*/
		NL::Socket *socket;

	private:
		/** This thread will read inbound data */
		thread *listennerThread;

		/** Flag used to terminate the listenning thread */
		bool listenning;

		/**
		* This method is meant to be used at the thread entry point
		*/
		void dataListenner();

		/**
		 * Stops the listenner thread if running
		 */
		void stopListenner();

	};
}

#endif // __METAL_ADAPTER_H
