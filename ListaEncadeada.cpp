/*
 * ListaEncadeada.cpp
 *
 *  Created on: 26/05/2013
 *      Author: marcelo
 */

#include <cstdlib>
#include "ListaEncadeada.h"

using namespace std;

ListaEncadeada::ListaEncadeada() {
	this->anterior = NULL;
	this->valor = NULL;
	this->proximo = NULL;
}

ListaEncadeada::ListaEncadeada(ParOrdenado* ab) {
	this->anterior = NULL;
	this->valor = ab;
	this->proximo = NULL;
}

ListaEncadeada::~ListaEncadeada() {
	delete this->valor;
}

ListaEncadeada* ListaEncadeada::inserir(ParOrdenado* ab) {
	ListaEncadeada *novoElemento = new ListaEncadeada(new ParOrdenado(ab));

	novoElemento->valor->a = ab->a;
	novoElemento->valor->b = ab->b;

	this->proximo = novoElemento;
	novoElemento->anterior = this;
	novoElemento->proximo = NULL;

	return novoElemento;
}

ListaEncadeada* ListaEncadeada::removerProximo() {
	ListaEncadeada *proximo = this->proximo;
	ListaEncadeada *seguinteAoProximo = NULL;

	if (proximo != NULL) {
		seguinteAoProximo = proximo->proximo;
	}

	this->proximo = seguinteAoProximo;

	delete proximo;
	return this->proximo;
}
