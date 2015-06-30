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

#include "OrderSender.h"
#include "MilleniumMapper.h"

namespace Metal {
namespace LSE {

NormalizedMillenium::NormalizedMillenium( std::string userName, std::string password) : MilleniumAdapter( userName, password) {
}


NormalizedMillenium::~NormalizedMillenium() {
}

void NormalizedMillenium::onMessage(const Metal::LSE::ExecutionReport &nativeER) {
	//std::cout << "MilleniumAdapter: Received Native Execution Report" << std::endl;
	Metal::ExecutionReport metalER;
	MilleniumMapper::map(nativeER, metalER);

	// Propagate the normalized message
	onExecutionReport(metalER);
}


void NormalizedMillenium::sendCancel(const Metal::OrderCancelRequest& ocr) {
	OrderCancelRequest nativeOCR;
	MilleniumMapper::map(ocr, nativeOCR);
	send(nativeOCR);
}

void NormalizedMillenium::sendNewOrder(const NewOrderSingle& nos) {
	NewOrder no;
	MilleniumMapper::map(nos, no);

	Message msg;
	this->codec->encode(no, msg);
	send(msg);
}


} // namespace LSE
} // namespace Metal


