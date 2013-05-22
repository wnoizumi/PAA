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
	elemento_inicial->valor.a = 0;
	elemento_inicial->valor.b = 0;
	elemento_inicial->proximo = NULL;

	return elemento_inicial;
}

ListaEncadeada* inserir_depois_de(ListaEncadeada *anterior, int a, int b) {
	ListaEncadeada *novoElemento = malloc(sizeof(ListaEncadeada));
	novoElemento->valor.a = a;
	novoElemento->valor.b = b;

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

void dividir_lista(ListaEncadeada *listaOriginal, int tamanhoListaOriginal, ListaEncadeada *esquerda, ListaEncadeada *direita) {
	ListaEncadeada *p = listaOriginal->proximo;
	int i;
	int meio = tamanhoListaOriginal / 2;

	int tamanho_esquerda = meio;
	ListaEncadeada *p_esq = esquerda;
	i = 0;
	while ((i < tamanho_esquerda) && (p != NULL)) {
		p_esq = inserir_depois_de(p_esq, p->valor.a, p->valor.b);
		i++;
		p = p->proximo;
	}

	int tamanho_direita = tamanhoListaOriginal - meio;
	ListaEncadeada *p_dir = direita;
	i = 0;
	while ((i < tamanho_direita) && (p != NULL)) {
		p_dir = inserir_depois_de(p_dir, p->valor.a, p->valor.b);
		i++;
		p = p->proximo;
	}
}
