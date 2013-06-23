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

#ifndef LONG_MAX_STRING_BUSQUEDA
#define LONG_MAX_STRING_BUSQUEDA 500
#endif


//DEFINICION DUPLICADA
#ifndef LONG_MAX_LINEA
#define LONG_MAX_LINEA 200
#endif


namespace buscador {

Buscador::Buscador() {
	this->archivoLexico = fopen(constantes::NombresArchivos::archivoLexico,"rb");
	this->tablalexico = fopen(constantes::NombresArchivos::archivoTablaLexico,"rb");
	this->archivoPunteros = fopen(constantes::NombresArchivos::archivoPunteros,"rb");
	this->archivoPosiciones = fopen(constantes::NombresArchivos::archivoPosicionesRelativas,"rb");
	archivoGamma.abrir();
	this->arbolB = new abb::ArbolB<abb::Nodo, ORDEN_NODO>();
	this->levantarArbol();

}

match::Match* Buscador::buscarFrase(string frase){

	//PARSEO LA FRASE DE LA MISMA FORMA QUE PARSEABA AL ARMAR EL INDICE
	parser::Parser pars;
	parser::Posiciones posiciones;
	string* palabras = pars.parsearLinea(frase, &posiciones, LONG_MAX_STRING_BUSQUEDA);
	match::Match* match = new match::Match();

	//Si viene un usuario kaker y pone solo delimitadores, es un caso especial:
	if(posiciones.getCantPosiciones()==0){
		match->setEncontroFrase(false);
		match->setOffsetsDocumentos(new Posiciones());
		return match;
	}

	abb::Nodo nodosEncontrados[LONG_MAX_STRING_BUSQUEDA];
	bool estanTodas = asignarPosicionesAPalabras(nodosEncontrados, palabras, posiciones.getCantPosiciones());
	if(!estanTodas) {
		match->setEncontroFrase(false);
		match->setOffsetsDocumentos(new Posiciones());
		return match;
	}

	abb::Nodo menor = nodosEncontrados[0];
	//Agarro el que tiene menor cantidad de documentos:
	for (int i=0; i <posiciones.getCantPosiciones(); i++){
		if(nodosEncontrados[i].getDocumentos()->getCantPosiciones() < menor.getDocumentos()->getCantPosiciones()){
			menor = nodosEncontrados[i];
		}
	}
	//Empiezo tomando los documentos que tienen a todas las palabras
	Posiciones matchDocumentos;
	bool documentoCandidato=true;
	for(int i=0; i<menor.getDocumentos()->getCantPosiciones(); i++){
		int documento = menor.getDocumentos()->getPosiciones()[i];
		bool nuevoMatch = esDocumentoCandidato(nodosEncontrados,posiciones.getCantPosiciones(), documento);
		if(nuevoMatch){
			matchDocumentos.agregarPosicion(documento);
		}

	}
	Posiciones* matchFrases = new Posiciones();
	//Por cada documento matcheado me tengo que fijar si el orden que siguen las palabras de la frase es el correcto.
	for (int i=0; i<matchDocumentos.getCantPosiciones(); i++){
		bool documentoMatch = true;
		int documento = matchDocumentos.getPosiciones()[i];
		//Caso especial: si es una sola palabra la que estoy buscando, todos los documentos son match.
		if(posiciones.getCantPosiciones() == 1) {
			matchFrases->agregarPosicion((matchDocumentos.getPosiciones()[i]));
		} else {

			documentoMatch = esFrase(nodosEncontrados,posiciones.getCantPosiciones(),documento);
			if(documentoMatch){
				matchFrases->agregarPosicion(matchDocumentos.getPosiciones()[i]);
			}
		}
	}

	if(matchFrases->getCantPosiciones() == 0)
		match->setEncontroFrase(false);
	match->setOffsetsDocumentos(matchFrases);


	for(int i=0; i<posiciones.getCantPosiciones();i++){
		nodosEncontrados[i].borrar();
	}

	return match;

}

std::set<string> Buscador::armarSetParaBusquedaFrases(abb::Nodo* nodosEncontrados, int cant, int documentoBuscado){
	std::set<string> set;
	std::set<int>* posiciones;
	std::set<int>::iterator it;
	for(int i = 0; i<cant; i++){
		posiciones = getPosiciones(nodosEncontrados[i], documentoBuscado);
		for (it=posiciones->begin(); it!=posiciones->end(); ++it){
			string cadena;
			stringstream ss;
			ss<<nodosEncontrados[i].getPalabra()<<"-"<<documentoBuscado<<"-"<<*it;
			ss>>cadena;
			set.insert(cadena);
		}
	}
	return set;
}

bool Buscador::asignarPosicionesAPalabras(abb::Nodo* nodosEncontrados, string* palabras, int cantidadPalabras){
	//BUSCO CADA FRASE EN EL ARBOL SI UNA NO ESTA ZARAZA
	bool estanTodas = true;
	for(int i = 0; i<cantidadPalabras; i++){
		abb::Nodo n1;
		n1.setPalabra(palabras[i]);
		bool encontrado = arbolB->buscar(n1);
		if(!(encontrado)){
			estanTodas = false;
		}
		if(!estanTodas){
			return false;
		} else {
			abb::Nodo n;
			n=buscarTermino2(palabras[i]);
			nodosEncontrados[i] = n;
		}
	}
	return true;


}

bool Buscador::esFrase(abb::Nodo *nodosEncontrados, int cantidad, int doc){
	abb::Nodo nodosNoPrimeros[LONG_MAX_STRING_BUSQUEDA-1];
	for(int i=1; i <cantidad; i++){
		nodosNoPrimeros[i-1]=nodosEncontrados[i];
	}
	std::set<string> set = armarSetParaBusquedaFrases(nodosNoPrimeros, cantidad-1, doc);


	std::set<int>* primerPalabraPosiciones = getPosiciones(nodosEncontrados[0], doc);
	std::set<int>::iterator it;
	bool esFrase = false;

	//Para todas las posiciones de la primer palabra de la frase.
	for (it=primerPalabraPosiciones->begin(); it!=primerPalabraPosiciones->end(); ++it){
		//Contador es quien lleva la coherencia de la frase.
		int contador = *it+1;
		//Para todo el resto de palabras de la frase
		for(int i=1; i<cantidad; i++){
			string palabra = nodosEncontrados[i].getPalabra();
			string cadenaABuscar;
			stringstream ss;
			//Me armo la cadena que tengo que buscar en el set donde estan todas las posiciones de la forma Palabra-Doc-Posicion
			ss<<palabra<<"-"<<doc<<"-"<<contador;
			ss >> cadenaABuscar;
			//Si existe alguna posicion que matchee, la palabra sigue la frase, si no, no.
			esFrase = (set.count(cadenaABuscar)!=0);
			//Si alguna palabra me rompe la coherencia, no es frase, chau.
			if(!esFrase){
				break;
			}
			contador++;
		}
		//Ya se que es una frase y esta en el docu así que no sigo buscando.
		if(esFrase){
			delete(primerPalabraPosiciones);
			return true;
		}

	}
	delete(primerPalabraPosiciones);
	return esFrase;
}

//Devuelve todas las posiciones de una palabra en un documento
std::set<int>* Buscador::getPosiciones(abb::Nodo n, int doc){
	int frec;
	int pos = getPosPalabraEnVectorPosiciones(n,doc,&frec);
	std::set<int>* posis = new std::set<int>();
	for(int i=0; i<frec; i++){
		posis->insert((n.getPosiciones()->getPosiciones()[pos]));
		pos++;
	}
	return posis;
}


//Devuelve la posicion en el vector posiciones de una palabra dado un documento.
int Buscador::getPosPalabraEnVectorPosiciones(abb::Nodo n1, int doc, int* frecuenciaADevolver){
	//i: posicion en el vector de documentos.
	int i=0;
	//j: poscion en el vector de posiciones.
	int j=0;


	while ((i<n1.getDocumentos()->getCantPosiciones())){
		//VOY AUMENTANDO EL ITERADOR DE POSICIONES HASTA LLEGAR A LA QUE NECESITO.
		if(n1.getDocumentos()->getPosiciones()[i]==doc){
			*frecuenciaADevolver=n1.getFrecuencias()->getPosiciones()[i];
			return j;
		} else {
			//Tengo que avanzar en el vector posiciones las N posiciones que me indica la frecuencia.
			j+=n1.getFrecuencias()->getPosiciones()[i];
			i++;
		}
	}
	return -1;

}


bool Buscador::esDocumentoCandidato(abb::Nodo* nodosEncontrados, int cantidadNodos, int documento){
	bool esCandidato = true;
	int i=0;
	while (esCandidato && i<cantidadNodos){
		abb::Nodo nodo = nodosEncontrados[i];
		esCandidato = poseeDocumento(nodo, documento);
		i++;
	}
	return esCandidato;
}

//Dice si una determinada palabra esta en un documento
bool Buscador::poseeDocumento(abb::Nodo nodo, int documento){
	for (int i=0; i<nodo.getDocumentos()->getCantPosiciones(); i++){
		if(nodo.getDocumentos()->getPosiciones()[i] == documento) {
			return true;
		}
	}
	return false;
}

//PRE: ya no se comprueba que el termino este en la coleccion, so, el termino DEBE estar en la coleccion si se llama a esta funcion.
abb::Nodo Buscador::buscarTermino2(string term){
	abb::Nodo nodob;
	nodob.setPalabra(term);
	nodob = arbolB->buscarYdevolver(nodob);
	string* tokens;
	//SI EL OFFSET ME DA -1 ES PORQUE SE TRATA DE LA PRIMER PALABRA, Y COMO ESA LINEA NO LA
	//ESCRIBO EN LA TABLA, se lo tengo que avisar al seeker.
	int offset = nodob.getLineaTabla();
	if(offset != -1){
		char line[LONG_MAX_LINEA];
		fseek(this->tablalexico, nodob.getLineaTabla(),SEEK_SET);
		fgets(line,LONG_MAX_LINEA, this->tablalexico);
		tokens = parsearLinea(line);
	} else {
		tokens = parsearLinea("0,0,0,0");
		fseek(this->tablalexico, 0,SEEK_SET);
	}
	std::vector<unsigned int> punteros = archivoGamma.levantarVector(atoi(tokens[2].c_str()));
	nodob.deserializarPosiciones(punteros);
	return nodob;

}

//-------------- A BORRAR CUANDO TODO SALGA BIEN ----------------
abb::Nodo Buscador::buscarTermino(string term){

	abb::Nodo nodob;;
	nodob.setPalabra(term);

	if(arbolB->buscar(nodob)){
		nodob = arbolB->buscarYdevolver(nodob);
		Posiciones* documentos = new Posiciones();
		Posiciones* posiciones = new Posiciones();
		Posiciones* frecuencias = new Posiciones();


		string* tokens;
		//SI EL OFFSET ME DA -1 ES PORQUE SE TRATA DE LA PRIMER PALABRA, Y COMO ESA LINEA NO LA
		//ESCRIBO EN LA TABLA, se lo tengo que avisar al seeker.
		int offset = nodob.getLineaTabla();
		if(offset != -1){
			char line[LONG_MAX_LINEA];
			fseek(this->tablalexico, nodob.getLineaTabla(),SEEK_SET);
			fgets(line,LONG_MAX_LINEA, this->tablalexico);
			tokens = parsearLinea(line);
		} else {
			tokens = parsearLinea("0,0,0,0");
			fseek(this->tablalexico, 0,SEEK_SET);
		}

		//La siguiente linea la uso para obtener el total de documentos.
		int longitud;
		char siguienteLinea[LONG_MAX_LINEA];
		if (!(fgets(siguienteLinea,LONG_MAX_LINEA, this->tablalexico)) == NULL){
			string* siguientesTok = parsearLinea(siguienteLinea);
			longitud = atoi(siguientesTok[2].c_str()) - atoi(tokens[2].c_str());
		} else {
			longitud = 999999999;
		}

		//ME POSICIONO EN LOS ARCHIVOS DE PUNTEROS Y POSICIONES.
		fseek(this->archivoPunteros, atoi(tokens[2].c_str()), SEEK_SET);
		fseek(this->archivoPosiciones, atoi(tokens[3].c_str()), SEEK_SET);

		//LONGITUD: es la cantidad de caracteres que tienen los documentos.
		//Ahora es asi: documento1,frecuencia1,documento2,frecuencia2,..
		int i = 0;
		int docAnt=0;
		int sumaPosAnt=0;
		char c;

		while ((i<longitud)&&(c!=EOF)) {
			int doc;
			c = fgetc(this->archivoPunteros);
			i++;

			string strDoc;
			while((c!= ',')&&(i<longitud)){
				strDoc.append(toString(c));
				c = fgetc(this->archivoPunteros);
				i++;
			}


			doc = atoi(strDoc.c_str());
			documentos->agregarPosicion(doc+docAnt);
			docAnt+=doc;

			//AHORA NECESITO LA FRECUENCIA PARA SABER CUANTAS POSICIONES TENGO QUE PARSEAR.
			c = fgetc(this->archivoPunteros);
			i++;
			int frec;
			string strFrec;
			while((c!= ',')&&(i<longitud)){
				strFrec.append(toString(c));
				c = fgetc(this->archivoPunteros);
				i++;
			}


			//GUARDO LA FRECUENCIA SIGUIENTE AL NRO DE OFFSET DE DOCUMENTO
			frec = atoi(strFrec.c_str());
			frecuencias->agregarPosicion(frec);

			//Frec me dice la cantidad de posiciones que tengo que parsear del archivo de posiciones para el documento doc.
			int j = 0;
			sumaPosAnt = 0;
			while ((j<frec)){
				//PARSEO CADA POSICION
				char c2 = fgetc(this->archivoPosiciones);
				string strPos;
				while(c2!= ','){
					strPos.append(toString(c2));
					c2 = fgetc(this->archivoPosiciones);
				}
				int pos = atoi(strPos.c_str());
				posiciones->agregarPosicion(pos+sumaPosAnt);
				sumaPosAnt=pos+sumaPosAnt;
				j++;
			}

		}
		nodob.setFrecuencias(frecuencias);
		nodob.setPosiciones(posiciones);
		nodob.setDocumentos(documentos);
	} else {
		nodob.setEncontrado(false);
		return nodob;
	}
	return nodob;
}

string Buscador::toString(char c){
	stringstream s0;
	string lineaStr;
	s0 << c;
	s0 >> lineaStr;
	return lineaStr;
}

string* Buscador::parsearLinea(char* line){
	parser::Parser pars;
	stringstream s0;
	string lineaStr;
	s0 << line;
	s0 >> lineaStr;
	Posiciones pos;
	string* tokens;
	tokens = pars.parsearLinea(lineaStr, &pos, 50);
	return tokens;

}

void Buscador::levantarArbol(){
	char linea[LONG_MAX_LINEA];
	string palabraAnterior = "";
	//Tengo que agarrar la primera.


	int offset = 0;

	Parser pars;
	Posiciones p;
	int posicionAnterior = 0;
	int iguales = 0;

	bool esPrimerPalabra = true;
	bool esSegundaPalabra = false;
	int contador = 0;
	while (fgets(linea, LONG_MAX_LINEA, this->tablalexico) != NULL){

		abb::Nodo nuevoNodo;
		p.resetCantidadPosiciones();
		//AGARRO LA SIGUIENTE LINEA Y LA TENGO QUE COMPARAR CON LA ANTERIOR PARA SACAR LA LONGITUD DE LA PALABRA
		string* tokens = pars.parsearLinea(linea, &p, 50);

		//Horrible implemetacion de split:
		stringstream s0;
		string lineaStr;
		s0 << linea;
		s0 >> lineaStr;
		int j=0;
		for(int i=0; lineaStr[i]!=','; i++){
			j++;
		}
		int posicionSig = atoi(tokens[0].c_str());

		//LA LONG DEL ANTERIOR ES LA POSICION ACTUAL MENOS LA ANTERIOR.
		int longitud = posicionSig - posicionAnterior;

		//LOS CARACTERES IGUALES VIENEN DEL ANTERIOR, TODAVIA NO HAY QUE ACTUALIZARLOS
		fseek(this->archivoLexico, posicionAnterior, SEEK_SET);
		char* buffer = (char*) malloc (sizeof(char)*longitud);
		//LEO LA CADENA QUE NECESITO
		fread (buffer,1,longitud,this->archivoLexico);

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

		//LE PONGO TODAS LAS PROPIEDADES
		nuevoNodo.setPalabra(strPalabra);

		//agregando chanchadas al tp.
		//Si es la primer palabra (dado que no consideramos la linea (0,0,0,0), le ponemos un offset de -1
		//indicando que cuando lo agarre sepa que la linea es (0,0,0,0).
		if(esPrimerPalabra){
			nuevoNodo.setLineaTabla(-1);
			offset=0;
			esPrimerPalabra = false;
		} else if(contador == 1){
			nuevoNodo.setLineaTabla(offset-(lineaStr.length())-1);
		} //siempre que hay algun cambio, explota el offset de la segunda palabra u_u.
		 else {
			nuevoNodo.setLineaTabla(offset-(lineaStr.length()));
		}
		//FINALMENTE LO INSERTO EN EL ARBOL B
		arbolB->insertar(nuevoNodo);

		//ACTUALIZO TOOOOODO
		palabraAnterior = strPalabra;
		iguales = atoi(lineaStr.substr(j+1, lineaStr.length()).c_str());
		posicionAnterior = posicionSig;

		offset=ftell(this->tablalexico);
		contador++;
		delete(buffer);
	}
}


Buscador::~Buscador() {
	this->archivoGamma.cerrar();
}

} /* namespace buscador */
