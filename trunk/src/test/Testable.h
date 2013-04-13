/*
 * Testable.h
 *
 *  Created on: Apr 8, 2013
 *      Author: matias
 */

#ifndef TESTABLE_H_
#define TESTABLE_H_

#include "cute.h"

class Testable{
	public:
	virtual cute::suite testSuite() = 0;
	virtual ~Testable() = 0;
};


#endif /* TESTABLE_H_ */
