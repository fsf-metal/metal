#include <vector>
#include <chrono>

#include <metal/metal.h>

#include "Benchmarker.h"
#include "adapters/LSETradingAdapter/MilleniumAdapter.h"

class LSEBenchmarker : public Benchmarker {
public:
	LSEBenchmarker() : Benchmarker(Metal::LSE::MilleniumAdapter::NAME){};

	/**
	 * @see TradingAdapter#benchmark
	 */
	void benchmark( const std::vector<Metal::NewOrderSingle> &, std::chrono::milliseconds &, std::chrono::milliseconds &);

	/**
	 * @see TradingAdapter#benchmark
	 */
	void benchmark( const std::vector<Metal::OrderCancelRequest> &, std::chrono::milliseconds &, std::chrono::milliseconds &);

};
