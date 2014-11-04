#ifndef __BENCHMARKER_H_
#define __BENCHMARKER_H_

#include <string>

class Benchmarker {
public:
	Benchmarker(std::string nameParam) :name(nameParam){};
	std::string getName() { return this->name; }

	/**
	* The purpose is to measure Mapping and Encoding speed for NewOrderSingle<br>
	* Subclasses should make sure to execute both as opposed to just mapping
	* @param list A list of NewOrderSingle better if randomly generated
	* @param mappingDuration Time used to map messages
	* @param encodingDuration Time used to encode messages
	*/
	virtual void benchmark(const std::vector<Metal::NewOrderSingle> &list,
		std::chrono::milliseconds &mappingDuration,
		std::chrono::milliseconds &encodingDuration) = 0;

	/**
	* The purpose is to measure Mapping and Encoding speed for OrderCancelRequest<br>
	* Subclasses should make sure to execute both as opposed to just mapping
	* @param list A list of NewOrderSingle better if randomly generated
	* @param mappingDuration Time used to map messages
	* @param encodingDuration Time used to encode messages
	*/
	virtual void benchmark(const std::vector<Metal::OrderCancelRequest> &list,
		std::chrono::milliseconds &mappingDuration,
		std::chrono::milliseconds &encodingDuration) = 0;

private:
	std::string name;
};

#endif // __BENCHMARKER_H_