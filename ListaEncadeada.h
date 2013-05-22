/*
 * ListaEncadeada.h
 *
 *  Created on: 19/05/2013
 *      Author: marcelo
 */

#ifndef LISTAENCADEADA_H_
#define LISTAENCADEADA_H_


struct PAR_ORDENADO {
	int a;
	int b;
};

typedef struct PAR_ORDENADO ParOrdenado;

struct ELEMENTO_LISTA_ENCADEADA {
	struct ELEMENTO_LISTA_ENCADEADA *anterior;
	ParOrdenado valor;
	struct ELEMENTO_LISTA_ENCADEADA *proximo;
};

typedef struct ELEMENTO_LISTA_ENCADEADA ListaEncadeada;

ListaEncadeada* inicializar_lista();

ListaEncadeada* inserir_depois_de(ListaEncadeada *anterior, int a, int b);

ListaEncadeada* remover(ListaEncadeada *elemento);

void desalocar_lista(ListaEncadeada *elementoInicial);

void dividir_lista(ListaEncadeada *listaOriginal, int tamanhoListaOriginal, ListaEncadeada *esquerda, ListaEncadeada *direita);


#endif /* LISTAENCADEADA_H_ */
