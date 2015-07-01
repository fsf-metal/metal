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
#ifndef METAL_ORDERSENDEROBSERVER_H
#define METAL_ORDERSENDEROBSERVER_H

#include <string>

#include <metal/metal.h>

namespace Metal {

/**
 * This class should be extend to implement custom execution report processing
 * Once an OrderSender receives a message, it will invoked onExecutionReport on this object<br>
 */
class OrderSenderObserver {
public:
	OrderSenderObserver() {
	}
	;

protected:
	~OrderSenderObserver() {
	}
	;

	/**
	 * Entry point for every execution reports
	 */
	virtual void onExecutionReport(const ExecutionReport &) = 0;

};

} // namespace Metal

#endif
