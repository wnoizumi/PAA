/*
 * ListaEncadeada.h
 *
 *  Created on: 19/05/2013
 *      Author: marcelo
 */

#ifndef LISTAENCADEADA_H_
#define LISTAENCADEADA_H_


struct ELEMENTO_LISTA_ENCADEADA {
	struct ELEMENTO_LISTA_ENCADEADA *anterior;
	int valor;
	struct ELEMENTO_LISTA_ENCADEADA *proximo;
};

typedef struct ELEMENTO_LISTA_ENCADEADA ListaEncadeada;

ListaEncadeada* inicializar_lista();

ListaEncadeada* inserir_depois_de(ListaEncadeada *anterior, int valor);

ListaEncadeada* remover(ListaEncadeada *elemento);

void desalocar_lista(ListaEncadeada *elementoInicial);


#endif /* LISTAENCADEADA_H_ */
