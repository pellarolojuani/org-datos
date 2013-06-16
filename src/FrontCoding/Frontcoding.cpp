/*
 * Frontcoding.cpp
 *
 *  Created on: Jun 14, 2013
 *      Author: lucia
 */

#include "Frontcoding.h"

namespace frontcoding {
//Recibo 2 archivos intermedios: uno con todo el léxico junto y otro con la tabla de los offset y
//creo el archivo de FC final y la tabla final.
Frontcoding::Frontcoding(FILE* rutaArchivoLexico, FILE* rutaArchivoTabla ) {

	this->archIntTabla = rutaArchivoTabla;
	this->archIntlexico = rutaArchivoLexico;
	palabraAnterior = ".";
	offset = 0;

}

void Frontcoding::agregarPalabra(string str){
	if (str.compare(".") == 0){
		this->guardarEnArchivo(str, 0, 0);
		this->palabraAnterior = str;
	} else {

		int cant;
		string substr = compararPorCharDistintos(palabraAnterior,str,&cant);
		this->guardarEnArchivo(substr, cant, offset);
		offset+=substr.length();
		this->palabraAnterior = str;

	}
}

//Esta función te devuelve cuántos caracteres distintos tiene el str uno con respecto al dos pero contando desde
//que empiezan a ser distitnos. strDos tiene que ser mayor que strUno.
string Frontcoding::compararPorCharDistintos(string uno, string dos, int* cantidadRepetidos){

	int i = 0;
	while ((uno[i] == dos[i])&&(i<uno.length()) && (i<dos.length())){
		i++;
	}

	*cantidadRepetidos = i;
	string s = dos.substr(i, strlen(dos.c_str()) );
	return s;
}

int Frontcoding::guardarEnArchivo(string str, int charsIguales, int offset){
	fputs(str.c_str(), this->archIntlexico);

	stringstream s1;
	s1 << charsIguales;
	string strDist = s1.str();

	stringstream ss;
	ss << offset;
	string strOffset = ss.str();

	fputs(strOffset.c_str(), this->archIntTabla);
	fputs(",", this->archIntTabla);


	fputs(strDist.c_str(), this->archIntTabla);
	fputc('\n', this->archIntTabla);


}


Frontcoding::~Frontcoding() {
	// TODO Auto-generated destructor stub
}

} /* namespace frontcoding */
