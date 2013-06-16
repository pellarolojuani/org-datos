#ifndef STRINGMATCH_H_
#define STRINGMATCH_H_

#include <vector>

/**
 * Esta clase contiene una lista de ubicaciones por documento
 */
class StringMatch {
public:
	int nroDoc;
	void agregarUbicacion(int ubicacion);
	char* getStringUbicaciones();
private:
	std::vector<int> ubicaciones;
};

#endif /* STRINGMATCH_H_ */
