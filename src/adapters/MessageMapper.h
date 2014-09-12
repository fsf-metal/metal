/*
 * MessageMapper.h
 *
 *  Created on: Sep 12, 2014
 *      Author: jc
 */

#ifndef __METAL_MESSAGEMAPPER_H_
#define __METAL_MESSAGEMAPPER_H_

#include <vector>
#include "metal.h"

namespace Metal {

class MessageMapper {
public:
	MessageMapper();
	virtual ~MessageMapper();
	virtual void benchmark( std::vector<NewOrderSingle> &) = 0;
};

} /* namespace Metal */
#endif /* __METAL_MESSAGEMAPPER_H_ */
