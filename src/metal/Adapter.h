#ifndef __METAL_ADAPTER_H
#define __METAL_ADAPTER_H

#include <string>

namespace Metal {
class Adapter {
	public:
		/**
		 * @param: uuid a unique adapter identifier. checkout http://www.famkruithof.net/uuid/uuidgen to create your own.
		 */
		Adapter( const std::string& nameParam, const std::string& uuidParam):name( nameParam),uuid( uuidParam){};

		const std::string & getName() { return this->name;};

		/**
		 * Retrieve Unique ID
		 * For example, this is used by benchmarking to report results<br>
		 * This is also used on the web site to identify adapters.
		 */
		const std::string & getUUID() { return this->uuid; };

		virtual void start() = 0;
		virtual void stop() = 0;

	protected:
		~Adapter(){};
		std::string name;
		std::string uuid;
};
}

#endif // __METAL_ADAPTER_H
