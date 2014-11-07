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

#ifndef METAL_LSE_NORMALIZEDMILLENIUM_H
#define METAL_LSE_NORMALIZEDMILLENIUM_H

#include "MilleniumAdapter.h"

#include <metal/metal.h>
#include <metal/NormalizedTrading.h>

namespace Metal {
namespace LSE {


class NormalizedMillenium :
	public MilleniumAdapter, NormalizedTrading 
{
public:
	NormalizedMillenium( std::string userName, std::string password);
	~NormalizedMillenium();

	/**
	 * Sends a normalized cancel
     * @see NormalizedTrading#sendCancel()
	 */
	void sendCancel(const Metal::OrderCancelRequest& ocr);

	/**
	 * Sends a normalized new order
	 */
	void sendNewOrder(const Metal::NewOrderSingle &nos);

protected:
	/**
	 * Entry point for normalized execution reports
	 */
	void onExecutionReport(const Metal::ExecutionReport &) = 0;


private:
	/**
	 * Invoked when a native execution report has been received<br>
	 * Will eventualy Invoke onExecutionReport()
	 */
	virtual void onMessage(const Metal::LSE::ExecutionReport &nativeER);



};

} // namespace LSE
} // namespace Metal


#endif // METAL_LSE_NORMALIZEDMILLENIUM_H
