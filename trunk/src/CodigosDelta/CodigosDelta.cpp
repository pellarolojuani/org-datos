/*
 * CodigosDelta.cpp
 *
 *  Created on: Jun 8, 2013
 *      Author: lucia
 */

#include "CodigosDelta.h"

namespace parser {

CodigosDelta::CodigosDelta() {
	// TODO Auto-generated constructor stub

}

void CodigosDelta::codificar(char* fuente, char* destino){
//	IntReader intreader(source);
//	BitWriter bitwriter(dest);
//	while (intreader.hasLeft())
//	{
//		int num = intreader.getInt();
//		int len = 0;
//		int lengthOfLen = 0;
//		for (int temp = num; temp > 0; temp >>= 1)  // calculate 1+floor(log2(num))
//			len++;
//		for (int temp = len; temp > 1; temp >>= 1)  // calculate floor(log2(len))
//			lengthOfLen++;
//		for (int i = lengthOfLen; i > 0; --i)
//			bitwriter.outputBit(0);
//		for (int i = lengthOfLen; i >= 0; --i)
//			bitwriter.outputBit((len >> i) & 1);
//		for (int i = len-2; i >= 0; i--)
//			bitwriter.outputBit((num >> i) & 1);
//	}
//	bitwriter.close();
//	intreader.close();
}

CodigosDelta::~CodigosDelta() {
	// TODO Auto-generated destructor stub
}

} /* namespace parser */
