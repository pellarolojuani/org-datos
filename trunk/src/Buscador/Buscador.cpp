/*
 * Buscador.cpp
 *
 *  Created on: Jun 15, 2013
 *      Author: lucia
 */

#include "Buscador.h"

#include <sstream>
#include <string>
#include "../Parser/Posiciones.h"
#include <stdlib.h>



//DEFINICION DUPLICADA
#ifndef LONG_MAX_LINEA
#define LONG_MAX_LINEA 200
#endif

#ifndef TOKENS
#define TOKENS 2
#endif

namespace buscador {

Buscador::Buscador() {
	this->archivoLexico = fopen(constantes::NombresArchivos::archivoLexico,"rb");
	this->tablalexico = fopen(constantes::NombresArchivos::archivoTablaLexico,"rb");
	this->arbolB = new abb::ArbolB<abb::Nodo, ORDEN_NODO>();
	this->levantarArbol();
	arbolB->emitir();

}

void Buscador::levantarArbol(){
	char linea[LONG_MAX_LINEA];
	string palabraAnterior = "";


	//Tengo que agarrar la primera.
	fgets(linea, LONG_MAX_LINEA, this->tablalexico);
	Parser pars;

	Posiciones p;


	int posicionAnterior = 0;
	int iguales = 0;


	while (fgets(linea, LONG_MAX_LINEA, this->tablalexico) != NULL){
		p.resetCantidadPosiciones();
		//AGARRO LA SIGUIENTE LINEA Y LA TENGO QUE COMPARAR CON LA ANTERIOR PARA SACAR LA LONGITUD DE LA PALABRA
		string* tokens = pars.parsearLinea(linea, &p);
		cout<<linea<<endl;
		int posicionSig = atoi(tokens[0].c_str());

		cout<<"VER:  "<<p.getPosiciones()[1]<<endl;

		cout<<"TOK 0: "<<tokens[0]<<" | TOK 1: "<<tokens[1]<<"  | TOK2 :"<<tokens[2]<<" |  TOK3 :"<<tokens[3]<<endl;
		cout<<p.getCantPosiciones()<<endl;
		cout<<"La poscion: "<<tokens[0]<<endl;
		cout<<"La cantidad de chars iguales "<<tokens[1]<<endl;


		//LA LONG DEL ANTERIOR ES LA POSICION ACTUAL MENOS LA ANTERIOR.
		int longitud = posicionSig - posicionAnterior;


		//LOS CARACTERES IGUALES VIENEN DEL ANTERIOR, TODAVIA NO HAY QUE ACTUALIZARLOS
		fseek(this->archivoLexico, posicionAnterior, SEEK_SET);
		char* buffer = (char*) malloc (sizeof(char)*longitud);
		//LEO LA CADENA QUE NECESITO
		size_t result = fread (buffer,1,longitud,this->archivoLexico);

		//ME ARMO LA PALABRA EN BASE AL LA ANTERIOR
		stringstream ss;
		string strCharsDistintos;
		ss << buffer;
		ss >> strCharsDistintos;
		strCharsDistintos = strCharsDistintos.substr(0, longitud);
		string comienzoPalabra = palabraAnterior.substr(0,iguales);

		string fin = strCharsDistintos;
		std::stringstream s2;
		s2 << comienzoPalabra << fin;
		std::string strPalabra = s2.str();

		cout<<strPalabra<<endl;

		//LE PONGO TODAS LAS PROPIEDADES (FALTAN MUCHAS!!!)
		abb::Nodo nuevoNodo;
		nuevoNodo.setPalabra(strPalabra);

		//FINALMENTE LO INSERTO EN EL ARBOL B
		arbolB->insertar(nuevoNodo);

		//ACTUALIZO TOOOOODO
		palabraAnterior = strPalabra;
		iguales = atoi(tokens[1].c_str());
		posicionAnterior = posicionSig;





		free(buffer);




	}


}


Buscador::~Buscador() {
	// TODO Auto-generated destructor stub
}

} /* namespace buscador */
