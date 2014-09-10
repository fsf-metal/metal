/*
 * Output.h
 *
 *  Created on: Sep 10, 2014
 *      Author: jc
 */

#ifndef OUTPUT_H_
#define OUTPUT_H_

#include "QuickFIXAdapter/QuickFIXAdapter.h"

class Output: public QuickFIXAdapter {
public:
	Output();
	virtual ~Output();
};

#endif /* OUTPUT_H_ */
