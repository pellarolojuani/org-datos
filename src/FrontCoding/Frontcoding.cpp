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

void Frontcoding::agregarPalabra(string str, int offsetPosiciones, int offsetPunteros){
	if (str.compare(".") == 0){
		this->guardarEnArchivo(str, 0, 0, offsetPosiciones, offsetPunteros);
		this->palabraAnterior = str;
	} else {

		int cant;
		string substr = compararPorCharDistintos(palabraAnterior,str,&cant);
		this->guardarEnArchivo(substr, cant, offset,offsetPosiciones,offsetPunteros);
		this->offset+=substr.length();
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

//SE PONE : CARACTERES DISTINTOS DEL STRING EN EL LEXICO
//SE PONE:  NRO CARACTERES IGUALES, OFFSET A LEXICO, OFFSET A PUNTEROS, OFFSET A POSICIONES.
int Frontcoding::guardarEnArchivo(string str, int charsIguales, int offset, int offsetPosiciones, int offsetPunteros){
	fputs(str.c_str(), this->archIntlexico);
	//OBVIAMOS LA LINEA "0,0,0,0" de la primer palabra.
	if(!((charsIguales == 0)&& (offset == 0)&&(offsetPosiciones == 0)&&(offsetPunteros == 0))){
		stringstream s1;
		s1 << charsIguales;
		string strDist = s1.str();

		stringstream ss;
		ss << offset;
		string strOffset = ss.str();

		stringstream s2;
		s2 << offsetPunteros;
		string strOffsetPunteros = s2.str();

		stringstream s3;
		s3 << offsetPosiciones;
		string strOffsetPosiciones = s3.str();

		fputs(strOffset.c_str(), this->archIntTabla);
		fputs(",", this->archIntTabla);
		fputs(strDist.c_str(), this->archIntTabla);
		fputs(",", this->archIntTabla);

		fputs(strOffsetPunteros.c_str(), this->archIntTabla);
		fputs(",", this->archIntTabla);

		fputs(strOffsetPosiciones.c_str(), this->archIntTabla);
		fputc('\n', this->archIntTabla);
	}


}


Frontcoding::~Frontcoding() {
	// TODO Auto-generated destructor stub
}

} /* namespace frontcoding */
