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

#include <thread>
#include <iostream>

#include <metal/Adapter.h>

using namespace std;

namespace Metal {
	Adapter::Adapter(const std::string& nameParam, const std::string& uuidParam) :name(name), uuid(uuidParam) {
		this->listenning = true;
		this->listennerThread = NULL;
	}

	Adapter::~Adapter() {
		stopListenner();
	}

	void Adapter::dataListenner() {
		chrono::seconds granularity = chrono::seconds(5);
		char buffer[4096];
		size_t size = sizeof(buffer);
		int readSize = 0;

		while (this->listenning) {
			try {
				if (this->socket != NULL) {
					readSize = this->socket->read(buffer, size);
					if (!readSize) {
						cerr << "Adapter::dataListenner nothing left to read" << endl;
					}
					else {
						cout << "Adapter::dataListenner received " << readSize << " bytes" << endl;
					}
				}
			} catch (NL::Exception e) {
				cerr << "Adapter::dataListenner exception " << e.what() << endl;
			}
			cout << "Adapter::runListenner is not doing much for now" << endl;
			this_thread::sleep_for(granularity);
		}

		cout << "Adapter::dataListenner Killed" << endl;
	}

	void Adapter::start() {
		// Prevent Duplicates
		stopListenner();
		this->listennerThread = new thread(&Adapter::dataListenner, this);
	}

	void Adapter::stop() {
		stopListenner();
	}

	void Adapter::stopListenner() {
		if (this->listennerThread != NULL){
			this->listenning = false;
			this->listennerThread->join();
			this->listennerThread = NULL;
			this->listenning = true;
		}
	}

}