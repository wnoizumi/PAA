/*
 * MergeSort.c
 *
 *  Created on: 20/05/2013
 *      Author: marcelo
 */

#include <stdlib.h>
#include "MergeSort.h"
#include "ListaEncadeada.h"

void merge_int(int *esquerda, int tam_esq, int *direita, int tam_dir, int *resultado) {
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

void merge_sort_int(int *l, int n) {
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

		merge_sort_int(esquerda, tamanho_esquerda);
		merge_sort_int(direita, tamanho_direita);

		merge_int(esquerda, tamanho_esquerda, direita, tamanho_direita, l);

		free(esquerda);
		free(direita);
	}
}

void merge_pares(ListaEncadeada *esquerda, int tam_esq, ListaEncadeada *direita, int tam_dir, ListaEncadeada *resultado) {
	int i_esq = 0;
	int i_dir = 0;
	int i_resultado = 0;
	while ((i_esq < tam_esq) || (i_dir < tam_dir)) {
		if ((i_esq < tam_esq) && (i_dir < tam_dir)) {
			ListaEncadeada *primeiro_esquerda = esquerda + i_esq;
			ListaEncadeada *primeiro_direita = direita + i_esq;
			double r_esq = ((double)primeiro_esquerda->valor.a) / primeiro_esquerda->valor.b;
			double r_dir = ((double)primeiro_direita->valor.a) / primeiro_direita->valor.b;
			if (r_esq <= r_dir) {
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

void merge_sort_pares(ListaEncadeada *l, int n) {
	if (n > 1) {
		int meio = n / 2;
		int tamanho_esquerda = meio;
		int tamanho_direita = n - meio;

		ListaEncadeada *esquerda = inicializar_lista();
		ListaEncadeada *direita = inicializar_lista();
		dividir_lista(l, n, esquerda, direita);

		merge_sort_pares(esquerda, tamanho_esquerda);
		merge_sort_pares(direita, tamanho_direita);

		merge_pares(esquerda, tamanho_esquerda, direita, tamanho_direita, l);

		desalocar_lista(esquerda);
		desalocar_lista(direita);
	}
}

/* CÓDIGO DE TESTE*/
#include <stdio.h>

//void imprime_inteiros(int *a, int n) {
//	printf("{");
//	for (int i = 0; i < n; i++) {
//		if (i > 0) {
//			printf(",");
//		}
//		printf(" %d", *(a + i));
//	}
//	printf(" }");
//}
//
void imprime(ListaEncadeada *a) {
	printf("{");
	while (a->proximo != NULL ) {
		if (a->anterior != NULL ) {
			printf(",");
		}
		a = a->proximo;
		printf(" (a = %d, b = %d, r = %f)", a->valor.a, a->valor.b, ((double)a->valor.a) / a->valor.b);
	}
	printf(" }");
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

	merge_sort_pares(lista, 5);
	printf("L = ");
	imprime(lista);
	printf("\n");

	return 0;
}
/**/
