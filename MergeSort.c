/*
 * MergeSort.c
 *
 *  Created on: 20/05/2013
 *      Author: marcelo
 */

#include <stdlib.h>
#include "MergeSort.h"
#include "ParOrdenado.h"
#include "ListaEncadeada.h"

void old_merge(ListaEncadeada *esquerda, ListaEncadeada *direita, ListaEncadeada *resultado) {
	ListaEncadeada *p_esq = esquerda->proximo;
	ListaEncadeada *p_dir = direita->proximo;
	ListaEncadeada *p_resultado = resultado;
	while ((p_esq != NULL) || (p_dir != NULL)) {
		if ((p_esq != NULL) && (p_dir != NULL)) {
			double r_esq = razao(p_esq->valor);
			double r_dir = razao(p_dir->valor);
			if (r_esq >= r_dir) {
				p_resultado = inserir_depois_de(p_resultado, p_esq->valor);
				p_esq = p_esq->proximo;
			}
			else {
				p_resultado = inserir_depois_de(p_resultado, p_dir->valor);
				p_dir = p_dir->proximo;
			}
		} else {
			if (p_esq != NULL) {
				p_resultado = inserir_depois_de(p_resultado, p_esq->valor);
				p_esq = p_esq->proximo;
			} else {
				if (p_dir != NULL) {
					p_resultado = inserir_depois_de(p_resultado, p_dir->valor);
					p_dir = p_dir->proximo;
				}
			}
		}
	}
}

void old_merge_sort(ListaEncadeada *l, int n) {
	if (n > 1) {
		int meio = n / 2;
		int tamanho_esquerda = meio;
		int tamanho_direita = n - meio;

		ListaEncadeada *esquerda = inicializar_lista();
		ListaEncadeada *direita = inicializar_lista();
//		dividir_lista(l, n, esquerda, direita);

		old_merge_sort(esquerda, tamanho_esquerda);
		old_merge_sort(direita, tamanho_direita);

		ListaEncadeada *listaOrdenada = inicializar_lista();
		old_merge(esquerda, direita, listaOrdenada);

		// Troca os ponteiros iniciais de l (a lista original) e listaOrdenada,
		// de forma que a função chamadora tenha um ponteiro para a lista ordenada.
		ListaEncadeada *temp = listaOrdenada->proximo;
		listaOrdenada->proximo = l->proximo;
		listaOrdenada->proximo->anterior = listaOrdenada;
		l->proximo = temp;
		l->proximo->anterior = l;

		desalocar_lista(esquerda);
		desalocar_lista(direita);
		desalocar_lista(listaOrdenada);
	}
}

void merge(ParOrdenado *esquerda, int tam_esq, ParOrdenado *direita, int tam_dir, ParOrdenado *resultado) {
	ParOrdenado *p_esq = esquerda;
	ParOrdenado *p_dir = direita;
	ParOrdenado *p_resultado = resultado;
	int i_esq = 0;
	int i_dir = 0;
	int i_resultado = 0;
	while ((i_esq < tam_esq) || (i_dir < tam_dir)) {
		if ((i_esq < tam_esq) && (i_dir < tam_dir)) {
			double r_esq = razao(p_esq);
			double r_dir = razao(p_dir);
			if (r_esq >= r_dir) {
				p_resultado->a = p_esq->a;
				p_resultado->b = p_esq->b;
				p_resultado++;
				i_resultado++;
				p_esq++;
				i_esq++;
			}
			else {
				p_resultado->a = p_dir->a;
				p_resultado->b = p_dir->b;
				p_resultado++;
				i_resultado++;
				p_dir++;
				i_dir++;
			}
		} else {
			if (i_esq < tam_esq) {
				p_resultado->a = p_esq->a;
				p_resultado->b = p_esq->b;
				p_resultado++;
				i_resultado++;
				p_esq++;
				i_esq++;
			} else {
				if (i_dir < tam_dir) {
					p_resultado->a = p_dir->a;
					p_resultado->b = p_dir->b;
					p_resultado++;
					i_resultado++;
					p_dir++;
					i_dir++;
				}
			}
		}
	}
}


void dividir_lista(ParOrdenado *listaOriginal, int tamanhoListaOriginal, ParOrdenado *esquerda, ParOrdenado *direita) {
	ParOrdenado *p = listaOriginal;
	int i;
	int meio = tamanhoListaOriginal / 2;

	int tamanho_esquerda = meio;
	ParOrdenado *p_esq = esquerda;
	i = 0;
	while (i < tamanho_esquerda) {
		p_esq->a = p->a;
		p_esq->b = p->b;
		i++;
		p++;
		p_esq++;
	}

	int tamanho_direita = tamanhoListaOriginal - meio;
	ParOrdenado *p_dir = direita;
	i = 0;
	while (i < tamanho_direita) {
		p_dir->a = p->a;
		p_dir->b = p->b;
		i++;
		p++;
		p_dir++;
	}
}

void merge_sort(ParOrdenado *l, int n) {
	if (n > 1) {
		int meio = n / 2;
		int tamanho_esquerda = meio;
		int tamanho_direita = n - meio;

		ParOrdenado *esquerda = malloc(tamanho_esquerda * sizeof(ParOrdenado));
		ParOrdenado *direita = malloc(tamanho_direita * sizeof(ParOrdenado));
		dividir_lista(l, n, esquerda, direita);

		merge_sort(esquerda, tamanho_esquerda);
		merge_sort(direita, tamanho_direita);

//		ParOrdenado *listaOrdenada = malloc(n * sizeof(ParOrdenado));
		merge(esquerda, tamanho_esquerda, direita, tamanho_direita, l);

		// Troca os ponteiros iniciais de l (a lista original) e listaOrdenada,
		// de forma que a função chamadora tenha um ponteiro para a lista ordenada.
//		ListaEncadeada *temp = listaOrdenada->proximo;
//		listaOrdenada->proximo = l->proximo;
//		listaOrdenada->proximo->anterior = listaOrdenada;
//		l->proximo = temp;
//		l->proximo->anterior = l;

		free(esquerda);
		free(direita);
//		desalocar_lista(listaOrdenada);
	}
}

/* CÓDIGO DE TESTE
#include <stdio.h>

void imprime(ListaEncadeada *a) {
	printf("{");
	while (a->proximo != NULL ) {
		if (a->anterior != NULL ) {
			printf(",");
		}
		printf("\n\t");
		a = a->proximo;
		printf(" (a = %8d, b = %8d, r = %14.6f)", a->valor->a, a->valor->b, razao(a->valor));
	}
	printf("\n    }");
}

ListaEncadeada* inserir_valores_depois_de(ListaEncadeada *anterior, int a, int b) {
	ParOrdenado *ab = malloc(sizeof(ParOrdenado));
	ab->a = a;
	ab->b = b;

	ListaEncadeada *proximo = inserir_depois_de(anterior, ab);
	free(ab);
	return proximo;
}

int main(void) {
	printf("TESTE DE MERGE SORT\n");

	ListaEncadeada *lista = inicializar_lista();
	ListaEncadeada *l = lista;
	l = inserir_valores_depois_de(l, 132, 563);
	l = inserir_valores_depois_de(l, 461, 874);
	l = inserir_valores_depois_de(l, 10, 1232898);
	l = inserir_valores_depois_de(l, 25938920, 84);
	l = inserir_valores_depois_de(l, 130, 581);

	printf("L = ");
	imprime(lista);
	printf("\n");

	printf("\nMERGE SORT\n");

	merge_sort(lista, 5);
	printf("L = ");
	imprime(lista);
	printf("\n");

	return 0;
}
*/
