/*
 * Main.c
 *
 *  Created on: 19/05/2013
 *      Author: marcelo
 */


#include <stdlib.h>
#include <stdio.h>
#include "ListaEncadeada.h"
#include "PPH.h"

void imprime_pares_ab(ParOrdenado *ab, int n) {
	printf("{");
	for (int i = 0; i < n; i++) {
		if (i > 0) {
			printf(",");
		}
		printf(" (%d, %d)", (ab + i)->a, (ab + i)->b);
	}
	printf(" }");
}

void imprime_pares(ListaEncadeada *l) {
	printf("{");
	while (l->proximo != NULL) {
		if (l->anterior != NULL) {
			printf(",");
		}
		l = l->proximo;
		printf(" (%d, %d)", l->valor->a, l->valor->b);
	}
	printf(" }");
}

int main(void) {
	printf("PPH\n");

	ParOrdenado *a0b0 = malloc(sizeof(ParOrdenado));
	a0b0->a = 132;
	a0b0->b = 434;
	ParOrdenado *ab = malloc(4 * sizeof(ParOrdenado));
	int a[] = { 132, 461, 10, 130 };
	int b[] = { 563, 874, 581, 84 };
	for (int i = 0; i < 4; i++) {
		(ab + i)->a = *(a + i);
		(ab + i)->b = *(b + i);
	}
	printf("(a0, b0) = (%d, %d)\n", a0b0->a, a0b0->b);
	printf("S = ");
	imprime_pares_ab(ab, 4);
	printf("\n");


	printf("\nALGORITMO 1\n");

	ListaEncadeada *S = inicializar_lista();
	double r = pph_algoritmo1(a0b0, 4, ab, S);
	double R = calcula_R(a0b0, S);

	printf("r = %f, R = %f\n", r, R);
	printf("S* = ");
	imprime_pares(S);

	desalocar_lista(S);
	printf("\n");


	printf("\nALGORITMO 2\n");

	S = inicializar_lista();
	r = pph_algoritmo2(a0b0, 4, ab, S);
	R = calcula_R(a0b0, S);

	printf("r = %f, R = %f\n", r, R);
	printf("S* = ");
	imprime_pares(S);

	desalocar_lista(S);
	printf("\n");


	printf("\nALGORITMO 4\n");

	r = pph_algoritmo4(a0b0, 4, ab, razao(a0b0), 0);
//	R = calcula_R(a0, b0, S);

	printf("R = %f\n", r);
//	printf("S* = ");
//	imprime_pares(S);

//	desalocar_lista(S);
	printf("\n");

	free(a0b0);

	return 0;
}
