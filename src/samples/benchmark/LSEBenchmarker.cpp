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

