#ifndef __METAL_ADAPTER_H
#define __METAL_ADAPTER_H

#include <string>

namespace Metal {
class Adapter {
	public:
		Adapter( std::string nameParam):name( nameParam){};

		const std::string & getName() { return this->name;};

		/**
		 * This UUID is the Adapter unique ID.<br>
		 * You can use services such as http://www.famkruithof.net/uuid/uuidgen to create your own.<br>
		 * For example, this is used by benchmarking to report results<br>
		 * This is also used on the web site to identify adapters.
		 */
		virtual std::string getUUID() = 0;

		virtual void start() = 0;
		virtual void stop() = 0;

	protected:
		~Adapter(){};
		std::string name;
};
}

#endif // __METAL_ADAPTER_H
