/*
 * MergeSort.c
 *
 *  Created on: 20/05/2013
 *      Author: marcelo
 */

#include <stdlib.h>
#include "MergeSort.h"
#include "ListaEncadeada.h"

void merge(ListaEncadeada *esquerda, ListaEncadeada *direita, ListaEncadeada *resultado) {
	ListaEncadeada *p_esq = esquerda->proximo;
	ListaEncadeada *p_dir = direita->proximo;
	ListaEncadeada *p_resultado = resultado;
	while ((p_esq != NULL) || (p_dir != NULL)) {
		if ((p_esq != NULL) && (p_dir != NULL)) {
			double r_esq = ((double)p_esq->valor.a) / p_esq->valor.b;
			double r_dir = ((double)p_dir->valor.a) / p_dir->valor.b;
			if (r_esq >= r_dir) {
				p_resultado = inserir_depois_de(p_resultado, p_esq->valor.a, p_esq->valor.b);
				p_esq = p_esq->proximo;
			}
			else {
				p_resultado = inserir_depois_de(p_resultado, p_dir->valor.a, p_dir->valor.b);
				p_dir = p_dir->proximo;
			}
		} else {
			if (p_esq != NULL) {
				p_resultado = inserir_depois_de(p_resultado, p_esq->valor.a, p_esq->valor.b);
				p_esq = p_esq->proximo;
			} else {
				if (p_dir != NULL) {
					p_resultado = inserir_depois_de(p_resultado, p_dir->valor.a, p_dir->valor.b);
					p_dir = p_dir->proximo;
				}
			}
		}
	}
}

void merge_sort(ListaEncadeada *l, int n) {
	if (n > 1) {
		int meio = n / 2;
		int tamanho_esquerda = meio;
		int tamanho_direita = n - meio;

		ListaEncadeada *esquerda = inicializar_lista();
		ListaEncadeada *direita = inicializar_lista();
		dividir_lista(l, n, esquerda, direita);

		merge_sort(esquerda, tamanho_esquerda);
		merge_sort(direita, tamanho_direita);

		merge(esquerda, direita, l);

		desalocar_lista(esquerda);
		desalocar_lista(direita);
	}
}

/* CÓDIGO DE TESTE*/
#include <stdio.h>

void imprime(ListaEncadeada *a) {
	printf("{");
	while (a->proximo != NULL ) {
		if (a->anterior != NULL ) {
			printf(",");
		}
		printf("\n\t");
		a = a->proximo;
		printf(" (a = %8d, b = %8d, r = %14.6f)", a->valor.a, a->valor.b, ((double)a->valor.a) / a->valor.b);
	}
	printf("\n    }");
}

int main(void) {
	printf("TESTE DE MERGE SORT\n");

	ListaEncadeada *lista = inicializar_lista();
	ListaEncadeada *l = lista;
	l = inserir_depois_de(l, 132, 563);
	l = inserir_depois_de(l, 461, 874);
	l = inserir_depois_de(l, 10, 1232898);
	l = inserir_depois_de(l, 25938920, 84);
	l = inserir_depois_de(l, 130, 581);

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
/**/
