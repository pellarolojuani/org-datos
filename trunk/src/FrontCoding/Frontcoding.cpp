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

	this->archIntTabla = rutaArchivoLexico;
	this->archIntlexico = rutaArchivoTabla;

}

//Esta función te devuelve cuántos caracteres distintos tiene el str uno con respecto al dos pero contando desde
//que empiezan a ser distitnos. strDos tiene que ser mayor que strUno.
string Frontcoding::compararPorCharDistintos(string uno, string dos, int* cantidad){

	int i = 0;
	while (uno[i] == dos[i]){
		i++;
	}
	string s = dos;
	int numDistintos = strlen(dos.c_str()) - i;
	if(numDistintos <= 0){
		*cantidad = 0;
	} else {
		*cantidad = numDistintos;
		s = dos.substr(i, strlen(dos.c_str()) );
	}

	return s;
}

int Frontcoding::guardarEnArchivo(string str, int charsDistintos, int offset){
	fputs(str.c_str(), this->archIntlexico);
	fputc((char)charsDistintos, this->archIntTabla);
	fputs(" ", this->archIntTabla);

	stringstream ss;
	ss << offset;
	string strOffset = ss.str();

	fputs(strOffset.c_str(), this->archIntTabla);
	fputs("\n", this->archIntTabla);
}

void Frontcoding::almacenarLexico(){

}

Frontcoding::~Frontcoding() {
	// TODO Auto-generated destructor stub
}

} /* namespace frontcoding */
