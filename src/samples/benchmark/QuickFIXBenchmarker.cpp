#include <vector>

#include <metal/metal.h>

#include "QuickFIXBenchmarker.h"
#include "adapters/QuickFIXAdapter/QuickFIXMessageMapper.h"

/**
 * This (dumb) loop maps and encodes all incoming NewOrderSingle.<br>
 * In the case of QuickFIX, encoding simply means calling toString()
 */
void QuickFIXBenchmarker::benchmark(const std::vector<Metal::NewOrderSingle> &allOrders,
	std::chrono::milliseconds &mappingDuration,
	std::chrono::milliseconds &encodingDuration) {
	std::string messageString;
	std::vector<FIX44::NewOrderSingle*> mappedNewOrders;

	int size = allOrders.size();
	// Save room and allocate resulting objects
	mappedNewOrders.reserve(size);
	for (int index = 0; index < size; ++index) {
		mappedNewOrders.push_back(new FIX44::NewOrderSingle());
	}

	auto t0 = std::chrono::system_clock::now();
	for (int index = 0; index < size; ++index) {
		Metal::QuickFIXMessageMapper::map(allOrders.at(index), *mappedNewOrders.at(index));
	}

	auto t1 = std::chrono::system_clock::now();
	for (int index = 0; index < size; ++index) {
		mappedNewOrders.at(index)->toString(messageString);
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

void QuickFIXBenchmarker::benchmark(const std::vector<Metal::OrderCancelRequest> &allCancels,
	std::chrono::milliseconds &mappingDuration,
	std::chrono::milliseconds &encodingDuration) {
	std::string messageString;
	std::vector<FIX::Message *> mappedCancels;

	int size = allCancels.size();
	mappedCancels.reserve(size);

	for (int index = 0; index < size; ++index) {
		mappedCancels.push_back(new (FIX::Message));
	}
	auto t0 = std::chrono::system_clock::now();
	for (int index = 0; index < size; ++index) {
		Metal::QuickFIXMessageMapper::map(allCancels.at(index), *mappedCancels.at(index));
	}
	auto t1 = std::chrono::system_clock::now();
	for (int index = 0; index < size; ++index) {
		mappedCancels.at(index)->toString(messageString);
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

