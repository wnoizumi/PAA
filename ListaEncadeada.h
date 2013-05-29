/*
 * ListaEncadeada.h
 *
 *  Created on: 26/05/2013
 *      Author: marcelo
 */

#ifndef LISTAENCADEADA_H_
#define LISTAENCADEADA_H_

//#include <list>
#include "ParOrdenado.h"

//using namespace std;

class ListaEncadeada { //: public list<ParOrdenado> {
public:
	ListaEncadeada *anterior;
	ParOrdenado *valor;
	ListaEncadeada *proximo;

	ListaEncadeada();
	virtual ~ListaEncadeada();
	ListaEncadeada* inserir(ParOrdenado* ab);
	ListaEncadeada* remover(ListaEncadeada* elemento);
	ListaEncadeada* removerProximo();
private:
	ListaEncadeada(ParOrdenado* ab);
};

#endif /* LISTAENCADEADA_H_ */
