/*
MeTAL: My Electronic Trading Adapters Library
Copyright 2014 Jean-Cedric JOLLANT (jc@jollant.net)

This file is part of MeTAL.

MeTAL is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

MeTAL is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with MeTAL source code. If not, see <http://www.gnu.org/licenses/>.

*/
/*
 * MyAdapter.h
 *
 *  Created on: Sep 10, 2014
 *      Author: jc
 *     Purpose: This class is meant to extend whatever Metal Adapter should be used
 */

#ifndef MYADAPTER_H_
#define MYADAPTER_H_

#include <adapters/LSETradingAdapter/NormalizedMillenium.h>

class MyAdapter : public Metal::LSE::NormalizedMillenium {
	public:
		MyAdapter();
		virtual ~MyAdapter();

	protected:
		virtual void onExecutionReport( const Metal::ExecutionReport &er);

};

#endif /* MYADAPTER_H_ */
