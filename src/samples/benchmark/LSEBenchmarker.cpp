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

#include <vector>

#include <metal/metal.h>

#include "LSEBenchmarker.h"
#include "adapters/LSETradingAdapter/MilleniumMapper.h"

using namespace Metal;
using namespace Metal::LSE;

void LSEBenchmarker::benchmark(const std::vector<Metal::NewOrderSingle> &allOrders,
	std::chrono::milliseconds &mappingDuration,
	std::chrono::milliseconds &encodingDuration) {
	Metal::Message msg;
	LSE::MilleniumCodec codec;

	std::vector<LSE::NewOrder *> mappedNewOrders;
	int size = allOrders.size();
	mappedNewOrders.reserve(size);

	for (int index = 0; index < size; ++index) {
		mappedNewOrders.push_back(new LSE::NewOrder());
	}

	auto t0 = std::chrono::system_clock::now();
	for (int index = 0; index < size; ++index) {
		LSE::MilleniumMapper::map(allOrders.at(index), *mappedNewOrders.at(index));
	}
	auto t1 = std::chrono::system_clock::now();
	for (int index = 0; index < size; ++index) {
		codec.encode(*mappedNewOrders.at(index), msg);
	}
	auto t2 = std::chrono::system_clock::now();

	// free allocated memory
	while (!mappedNewOrders.empty()) {
		delete mappedNewOrders.back();
		mappedNewOrders.pop_back();
	}

	mappingDuration = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0);
	encodingDuration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
}

void LSEBenchmarker::benchmark(const std::vector<Metal::OrderCancelRequest> &allCancels,
	std::chrono::milliseconds &mappingDuration,
	std::chrono::milliseconds &encodingDuration) {
	Metal::Message msg;
	MilleniumCodec codec;


	std::vector<Metal::LSE::OrderCancelRequest *> mappedCancels;
	int size = allCancels.size();
	mappedCancels.reserve(size);

	for (int index = 0; index < size; ++index) {
		mappedCancels.push_back(new Metal::LSE::OrderCancelRequest());
	}
	auto t0 = std::chrono::system_clock::now();
	for (int index = 0; index < size; ++index) {
		MilleniumMapper::map(allCancels.at(index), *mappedCancels.at(index));
	}
	auto t1 = std::chrono::system_clock::now();
	for (int index = 0; index < size; ++index) {
		codec.encode(*mappedCancels.at(index), msg);
	}
	auto t2 = std::chrono::system_clock::now();

	// free allocated memory
	while (!mappedCancels.empty()) {
		delete mappedCancels.back();
		mappedCancels.pop_back();
	}

	mappingDuration = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0);
	encodingDuration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);

}

