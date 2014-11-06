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

#ifndef LSEBENCHMARKER_H
#define LSEBENCHMARKER_H

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

#endif