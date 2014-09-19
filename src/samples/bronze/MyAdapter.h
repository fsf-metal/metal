/*
 * MyAdapter.h
 *
 *  Created on: Sep 10, 2014
 *      Author: jc
 *     Purpose: This class is meant to extend whatever Metal Adapter should be used
 */

#ifndef MYADAPTER_H_
#define MYADAPTER_H_

#include "QuickFIXAdapter/QuickFIXAdapter.h"

class MyAdapter: public Metal::QuickFIXAdapter {
public:
	MyAdapter();
	void recv( const Metal::ExecutionReport &er);

	virtual ~MyAdapter();
};

#endif /* MYADAPTER_H_ */
