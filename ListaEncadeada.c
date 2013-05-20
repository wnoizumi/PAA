/*
 * ListaEncadeada.c
 *
 *  Created on: 19/05/2013
 *      Author: marcelo
 */

#include <stdlib.h>
#include "ListaEncadeada.h"

ListaEncadeada* inicializar_lista() {
	ListaEncadeada *elemento_inicial = malloc(sizeof(ListaEncadeada));
	elemento_inicial->anterior = NULL;
	elemento_inicial->valor = 0;
	elemento_inicial->proximo = NULL;

	return elemento_inicial;
}

ListaEncadeada* inserir_depois_de(ListaEncadeada *anterior, int valor) {
	ListaEncadeada *novoElemento = malloc(sizeof(ListaEncadeada));
	novoElemento->valor = valor;

	anterior->proximo = novoElemento;
	novoElemento->anterior = anterior;
	novoElemento->proximo = NULL;

	return novoElemento;
}

ListaEncadeada* remover(ListaEncadeada *elemento) {
	ListaEncadeada *proximoElemento = elemento->proximo;

	if (elemento->anterior != NULL ) {
		elemento->anterior->proximo = elemento->proximo;
	}
	if (elemento->proximo != NULL ) {
		elemento->proximo->anterior = elemento->anterior;
	}

	free(elemento);
	return proximoElemento;
}

void desalocar_lista(ListaEncadeada *elementoInicial) {
	while (elementoInicial->proximo != NULL ) {
		ListaEncadeada *elemento = elementoInicial;
		elementoInicial = elementoInicial->proximo;
		free(elemento);
	}
	free(elementoInicial);
}
