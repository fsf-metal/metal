/*
 * Translator.h
 *
 *  Created on: Sep 12, 2014
 *      Author: jc
 *     Purpose: This class is meant to translate FIX field values into plain English
 */

#ifndef __METAL_TRANSLATOR_H
#define __METAL_TRANSLATOR_H

#include "quickfix/FixFields.h"

namespace Metal {

class Translator {
public:
	Translator();
	static const std::string field( const FIX::OrdStatus &);
	static const std::string field(const FIX::ExecType &);
	static const std::string field(const FIX::Side &);
	virtual ~Translator();
};

} /* namespace Metal */
#endif /* __METAL_TRANSLATOR_H */
