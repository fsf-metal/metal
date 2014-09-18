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
#include "MappingException.h"

namespace Metal {

class MessageMapper {
public:
	MessageMapper();
	virtual ~MessageMapper();
};

} /* namespace Metal */
#endif /* __METAL_MESSAGEMAPPER_H_ */
