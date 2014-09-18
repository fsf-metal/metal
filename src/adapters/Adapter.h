#ifndef __METAL_ADAPTER_H
#define __METAL_ADAPTER_H

#include <string>

namespace Metal {
class Adapter {
	public:
		Adapter( std::string nameParam):name( nameParam){};

		const std::string & getName() { return this->name;};

		virtual void start() = 0;
		virtual void stop() = 0;

	protected:
		~Adapter(){};
		std::string name;
};
}

#endif // __METAL_ADAPTER_H
