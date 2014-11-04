#include <vector>
#include <chrono>

#include <metal/metal.h>

#include "Benchmarker.h"
#include "adapters/QuickFIXAdapter/QuickFIXAdapter.h"

class QuickFIXBenchmarker : public Benchmarker {
public:
	QuickFIXBenchmarker() : Benchmarker(Metal::QuickFIX::QuickFIXAdapter::NAME){};

	/**
	 * @see TradingAdapter#benchmark
	 */
	void benchmark( const std::vector<Metal::NewOrderSingle> &, std::chrono::milliseconds &, std::chrono::milliseconds &);

	/**
	 * @see TradingAdapter#benchmark
	 */
	void benchmark( const std::vector<Metal::OrderCancelRequest> &, std::chrono::milliseconds &, std::chrono::milliseconds &);

};
