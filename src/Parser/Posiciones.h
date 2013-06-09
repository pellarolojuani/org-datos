/*
 * Posiciones.h
 *
 *  Created on: Jun 8, 2013
 *      Author: lucia
 */

#ifndef POSICIONES_H_
#define POSICIONES_H_
#ifndef MAX_POSICIONES_LINEA
#define MAX_POSICIONES_LINEA 50
#endif /* MAX_POSICIONES_LINEA */

namespace parser {

class Posiciones {
public:
	Posiciones();
	int* getPosiciones();
	int getCantPosiciones();
	void setCantPosiciones(int cant);
	void resetCantidadPosiciones();
	virtual ~Posiciones();
private:
	int posiciones[MAX_POSICIONES_LINEA];
	int cantPosiciones;
};

} /* namespace parser */
#endif /* POSICIONES_H_ */
