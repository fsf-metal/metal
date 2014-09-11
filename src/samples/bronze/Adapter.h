/*
 * Adapter.h
 *
 *  Created on: Sep 10, 2014
 *      Author: jc
 */

#ifndef ADAPTER_H_
#define ADAPTER_H_

#include "QuickFIXAdapter/QuickFIXAdapter.h"

class Adapter: public Metal::QuickFIXAdapter {
public:
	Adapter();
	virtual ~Adapter();
};

#endif /* ADAPTER_H_ */
