#ifndef __METAL_ADAPTER_H
#define __METAL_ADAPTER_H

namespace Metal {
class Adapter {
	public:
		Adapter(){};

		virtual void start() = 0;
		virtual void stop() = 0;

	protected:
		~Adapter(){};

};
}

#endif // __METAL_ADAPTER_H
