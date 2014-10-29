#ifndef __METAL___NAMESPACE__MAPPER_H
#define __METAL___NAMESPACE__MAPPER_H

#include <metal/metal.h>
#include <metal/Mapper.h>
#include "NewOrder.h"
#include "OrderCancelRequest.h"

namespace Metal {
namespace Nasdaq {

class Mapper : public Metal::Mapper {
	public:
	// Mapping Tables Delcarations
	std::map <std::string,std::string> sideFrom;

};

} // namespace Nasdaq
} // namespace Metal


#endif // __METAL___NAMESPACE__MAPPER_H
