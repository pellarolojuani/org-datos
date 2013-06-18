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

	this->arbolB = new abb::ArbolB<abb::Nodo, ORDEN_NODO>();
	this->levantarArbol();
	arbolB->emitir();

}

match::Match* Buscador::buscarFrase(string frase){

	//PARSEO LA FRASE DE LA MISMA FORMA QUE PARSEABA AL ARMAR EL INDICE
	parser::Parser pars;
	parser::Posiciones posiciones;
	string* palabras = pars.parsearLinea(frase, &posiciones, LONG_MAX_STRING_BUSQUEDA);

	match::Match* match = new match::Match();

	abb::Nodo nodosEncontrados[LONG_MAX_STRING_BUSQUEDA];

	bool estanTodas = estanTodasLasPalabras(nodosEncontrados, palabras, posiciones.getCantPosiciones());
	if(!estanTodas) {
		match->setEncontroFrase(false);
		match->setOffsetsDocumentos(new Posiciones());
		return match;
	}

	//imprimo las posiciones de todos a ver que onda
	for (int i=0; i<posiciones.getCantPosiciones(); i++) {
		abb::Nodo nodo = nodosEncontrados[i];
		cout<<"Posiciones:  "<<nodo.getPalabra()<<endl;
		for (int i=0; i<nodo.getPosiciones()->getCantPosiciones(); i++){
			cout<<nodo.getPosiciones()->getPosiciones()[i]<<"   ";
		}
		cout<<endl;
		cout<<"DOCUMENTOS:  "<<endl;
		for (int i=0; i<nodo.getDocumentos()->getCantPosiciones(); i++){
			cout<<nodo.getDocumentos()->getPosiciones()[i]<<"   ";
		}
		cout<<endl;
		cout<<"Frecuencias:  "<<endl;
		for (int i=0; i<nodo.getFrecuencias()->getCantPosiciones(); i++){
			cout<<nodo.getFrecuencias()->getPosiciones()[i]<<"   ";
		}
		cout<<endl;
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

	cout<<"matches documentos:  "<<endl;
	for (int i=0; i<matchDocumentos.getCantPosiciones(); i++){
		cout<<matchDocumentos.getPosiciones()[i]<<"   ";
	}
	cout<<endl;

	//Por cada documento matcheado me tengo que fijar si el orden que siguen las palabras de la frase es el correcto.
	for (int i=0; i<matchDocumentos.getCantPosiciones(); i++){
		bool documentoMatch = true;
		int documento = matchDocumentos.getPosiciones()[i];
		//Caso especial: si es una sola palabra la que estoy buscando, todos los documentos son match.
		if(posiciones.getCantPosiciones() == 1) {
			matchFrases->agregarPosicion((matchDocumentos.getPosiciones()[i]));
		}

		int j=0;
		while(j<(posiciones.getCantPosiciones()-1) && documentoMatch){
			documentoMatch = esPalabraSiguiente(nodosEncontrados[j], nodosEncontrados[j+1], documento);
			cout<<documentoMatch<<endl;
			j++;
		}
		if(documentoMatch){
			matchFrases->agregarPosicion(matchDocumentos.getPosiciones()[i]);
			cout<<"DOC MATCH: "<<matchDocumentos.getPosiciones()[i];
			cout<<"LA ENCONTRO"<<endl;


		}
	}
	match->setOffsetsDocumentos(matchFrases);
	return match;

}

bool Buscador::estanTodasLasPalabras(abb::Nodo* nodosEncontrados, string* palabras, int cantidadPalabras){
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
			n=buscarTermino(palabras[i]);
			nodosEncontrados[i] = n;

		}

	}
	return true;


}

bool Buscador::esPalabraSiguiente(abb::Nodo n1, abb::Nodo n2, int doc){
	int frec1 = 0;
	int frec2 = 0;


	int pos1 = this->getPosPalabraEnVectorPosiciones(n1,doc,&frec1);
	int pos2 = this->getPosPalabraEnVectorPosiciones(n2,doc,&frec2);
	int pos2Original = pos2;

	cout<<"palabras : "<<n1.getPalabra()<<endl;
	cout<<"palabras : "<<n2.getPalabra()<<endl;

	for(int i=0; i<frec1; i++){
		for(int j=0; j<frec2; j++){
			int ubicacionPalabra1 = n1.getPosiciones()->getPosiciones()[pos1];
			cout<<ubicacionPalabra1<<endl;
			int ubicacionPalabra2menosUno = n2.getPosiciones()->getPosiciones()[pos2]-1;
			cout<<ubicacionPalabra1<<endl;
			bool esSiguiente =  ((ubicacionPalabra1) == (ubicacionPalabra2menosUno));
			if(esSiguiente){
				return true;
			}
			pos2++;
		}
		//Tengo que reiniciar pos2
		pos2=pos2Original;
		pos1++;
	}
	return false;
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
			esSegundaPalabra = true;
			cout<<"PAL:   "<<strPalabra<<"   ||     "<<"OFFSET  "<<nuevoNodo.getLineaTabla()<<endl;
		} else if(contador == 2){
			nuevoNodo.setLineaTabla(1+offset-(lineaStr.length()));
			cout<<"SS PAL:   "<<strPalabra<<"   ||     "<<"OFFSET  "<<nuevoNodo.getLineaTabla()<<endl;
			esSegundaPalabra = false;
		} else {
			nuevoNodo.setLineaTabla(offset-(lineaStr.length()));
			cout<<"PAL:   "<<strPalabra<<"   ||     "<<"OFFSET  "<<nuevoNodo.getLineaTabla()<<endl;
		}

		//FINALMENTE LO INSERTO EN EL ARBOL B
		arbolB->insertar(nuevoNodo);

		//ACTUALIZO TOOOOODO
		palabraAnterior = strPalabra;
		iguales = atoi(lineaStr.substr(j+1, lineaStr.length()).c_str());
		posicionAnterior = posicionSig;

		offset=ftell(this->tablalexico);
		contador++;
		free(buffer);
	}
}



Buscador::~Buscador() {
	// TODO Auto-generated destructor stub
}

} /* namespace buscador */
