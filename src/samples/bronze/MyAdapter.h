/*
 * MyAdapter.h
 *
 *  Created on: Sep 10, 2014
 *      Author: jc
 *     Purpose: This class is meant to extend whatever Metal Adapter should be used
 */

#ifndef MYADAPTER_H_
#define MYADAPTER_H_

//#include <metal/adapters/QuickFIXAdapter/QuickFIXAdapter.h>
#include <metal/adapters/LSETradingAdapter/MilleniumAdapter.h>

//class MyAdapter: public Metal::QuickFIX::QuickFIXAdapter {
class MyAdapter : public Metal::LSE::MilleniumAdapter {
	public:
		MyAdapter();
		virtual ~MyAdapter();

		virtual void onMessage( const Metal::ExecutionReport &er);

};

#endif /* MYADAPTER_H_ */
