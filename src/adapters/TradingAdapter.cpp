#include <iostream>
#include "TradingAdapter.h"

TradingAdapter::TradingAdapter() {};
TradingAdapter::~TradingAdapter() {};

void TradingAdapter::start() {
	Adapter::start();
	std::cout << "TradingAdapter: start() invoked but not implemented" << std::endl;
}

