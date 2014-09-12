/*
 * Adapter.h
 *
 *  Created on: Sep 10, 2014
 *      Author: jc
 *     Purpose: This class is meant to extend whatever Metal Adapter should be used
 */

#ifndef ADAPTER_H_
#define ADAPTER_H_

#include "QuickFIXAdapter/QuickFIXAdapter.h"

class Adapter: public Metal::QuickFIXAdapter {
public:
	Adapter();
	void recv( const Metal::ExecutionReport &er);

	virtual ~Adapter();
};

#endif /* ADAPTER_H_ */
