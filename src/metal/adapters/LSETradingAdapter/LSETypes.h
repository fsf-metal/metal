/*
 * LSETypes.h
 *
 *  Created on: Sep 18, 2014
 *      Author: jc
 */

#ifndef METAL_LSE_LSETYPES_H_
#define METAL_LSE_LSETYPES_H_

#include <string>

namespace Metal {
namespace LSE {

	typedef long Price;
	typedef int Quantity;
	typedef char Side;
	typedef std::string ClientOrderID;
	typedef std::string OrderID;
	typedef std::string OriginalClientOrderID;
	typedef std::string Symbol;

} // namespace LSE
} // namespace Metal


#endif /* METAL_LSE_LSETYPES_H_ */
