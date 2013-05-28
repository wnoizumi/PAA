/*
 * MergeSort.c
 *
 *  Created on: 20/05/2013
 *      Author: marcelo
 */

#include <stdlib.h>
#include "MergeSort.h"
#include "ParOrdenado.h"

void merge(ParOrdenado *esquerda, int tam_esq, ParOrdenado *direita, int tam_dir, ParOrdenado *resultado) {
	ParOrdenado *p_esq = esquerda;
	ParOrdenado *p_dir = direita;
	ParOrdenado *p_resultado = resultado;
	int i_esq = 0;
	int i_dir = 0;
	int i_resultado = 0;
	while ((i_esq < tam_esq) || (i_dir < tam_dir)) {
		if ((i_esq < tam_esq) && (i_dir < tam_dir)) {
			double r_esq = p_esq->razao();
			double r_dir = p_dir->razao();
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

		ParOrdenado esquerda[tamanho_esquerda];
		ParOrdenado direita[tamanho_direita];
		dividir_lista(l, n, esquerda, direita);

		merge_sort(esquerda, tamanho_esquerda);
		merge_sort(direita, tamanho_direita);

		merge(esquerda, tamanho_esquerda, direita, tamanho_direita, l);
	}
}

/* CÓDIGO DE TESTE
#include <stdio.h>

void imprime(ParOrdenado *ab, int n) {
	printf("{");
	for (int i = 0; i < n; i++) {
		if (i > 0) {
			printf(",");
		}
		printf("\n\t");
		ParOrdenado *aibi = ab + i;
		printf(" (a = %8d, b = %8d, r = %14.6f)", aibi->a, aibi->b, razao(aibi));
	}
	printf("\n    }");
}

int main(void) {
	printf("TESTE DE MERGE SORT\n");

	ParOrdenado *lista = malloc(5 * sizeof(ParOrdenado));
	(lista + 0)->a =      132; (lista + 0)->b =     563;
	(lista + 1)->a =      461; (lista + 1)->b =     874;
	(lista + 2)->a =       10; (lista + 2)->b = 1232898;
	(lista + 3)->a = 25938920; (lista + 3)->b =      84;
	(lista + 4)->a =      130; (lista + 4)->b =     581;

	printf("L = ");
	imprime(lista, 5);
	printf("\n");

	printf("\nMERGE SORT\n");

	merge_sort(lista, 5);
	printf("L = ");
	imprime(lista, 5);
	printf("\n");

	return 0;
}
*/
