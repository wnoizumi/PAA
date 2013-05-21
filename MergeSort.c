/*
 * MergeSort.c
 *
 *  Created on: 20/05/2013
 *      Author: marcelo
 */

#include <stdlib.h>
#include "MergeSort.h"

void merge(int *esquerda, int tam_esq, int *direita, int tam_dir, int *resultado) {
	int i_esq = 0;
	int i_dir = 0;
	int i_resultado = 0;
	while ((i_esq < tam_esq) || (i_dir < tam_dir)) {
		if ((i_esq < tam_esq) && (i_dir < tam_dir)) {
			if (*(esquerda + i_esq) <= *(direita + i_dir)) {
				*(resultado + i_resultado) = *(esquerda + i_esq);
				i_esq = i_esq + 1;
				i_resultado = i_resultado + 1;
			}
			else {
				*(resultado + i_resultado) = *(direita + i_dir);
				i_dir = i_dir + 1;
				i_resultado = i_resultado + 1;
			}
		} else {
			if (i_esq < tam_esq) {
				*(resultado + i_resultado) = *(esquerda + i_esq);
				i_esq = i_esq + 1;
				i_resultado = i_resultado + 1;
			} else {
				if (i_dir < tam_dir) {
					*(resultado + i_resultado) = *(direita + i_dir);
					i_dir = i_dir + 1;
					i_resultado = i_resultado + 1;
				}
			}
		}
	}
}

void merge_sort(int *l, int n) {
	if (n > 1) {
		int meio = n / 2;

		int tamanho_esquerda = meio;
		int *esquerda = malloc(tamanho_esquerda * sizeof(int));
		for (int i = 0; i < meio; i++) {
			*(esquerda + i) = *(l + i);
		}

		int tamanho_direita = n - meio;
		int *direita = malloc(tamanho_direita * sizeof(int));
		for (int i = 0; i < tamanho_direita; i++) {
			*(direita + i) = *(l + i + meio);
		}

		merge_sort(esquerda, tamanho_esquerda);
		merge_sort(direita, tamanho_direita);

		merge(esquerda, tamanho_esquerda, direita, tamanho_direita, l);

		free(esquerda);
		free(direita);
	}
}

/* CÓDIGO DE TESTE
#include <stdio.h>

void imprime_inteiros(int *a, int n) {
	printf("{");
	for (int i = 0; i < n; i++) {
		if (i > 0) {
			printf(",");
		}
		printf(" %d", *(a + i));
	}
	printf(" }");
}

void imprime(ListaEncadeada *a) {
	printf("{");
	while (a->proximo != NULL ) {
		if (a->anterior != NULL ) {
			printf(",");
		}
		a = a->proximo;
		printf(" %d", a->valor);
	}
	printf(" }");
}

int main(void) {
	printf("TESTE DE MERGE SORT\n");

	int a[] = { 132, 461, 10, 130 };
	int b[] = { 563, 874, 1232898, 581, 84 };
	printf("a = ");
	imprime_inteiros(a, 4);
	printf("\n");
	printf("b = ");
	imprime_inteiros(b, 5);
	printf("\n");

	printf("\nMERGE SORT\n");

	merge_sort(a, 4);
	printf("a = ");
	imprime_inteiros(a, 4);
	printf("\n");

	merge_sort(b, 5);
	printf("b = ");
	imprime_inteiros(b, 5);
	printf("\n");

	return 0;
}
*/
