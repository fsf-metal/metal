#include <iostream>
#include "Adapter.h"

Adapter::Adapter() {};
Adapter::~Adapter() {};

void Adapter::start() {
	std::cout << "Adapter: start() invoked but not implemented" << std::endl;
}

void Adapter::stop() {
	std::cout << "Adapter: stop() invoked but not implemented" << std::endl;
}
