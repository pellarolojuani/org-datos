/*
 * Posiciones.h
 *
 *  Created on: Jun 8, 2013
 *      Author: lucia
 */

#ifndef POSICIONES_H_
#define POSICIONES_H_
#ifndef MAX_POSICIONES
#define MAX_POSICIONES 10
#endif /* MAX_POSICIONES */

namespace parser {

class Posiciones {
public:
	Posiciones();
	int* getPosiciones();
	int getCantPosiciones();
	void setCantPosiciones(int cant);
	void resetCantidadPosiciones();
	void agregarPosicion(int posicion);
	virtual ~Posiciones();
private:
	int* posiciones;
	int cantPosiciones;
	int tamanio;
};

} /* namespace parser */
#endif /* POSICIONES_H_ */
