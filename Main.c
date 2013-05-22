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

void imprime_pares_ab(int *a, int *b, int n) {
	printf("{");
	for (int i = 0; i < n; i++) {
		if (i > 0) {
			printf(",");
		}
		printf(" (%d, %d)", *(a+i), *(b+i));
	}
	printf(" }");
}

void imprime_pares(ListaEncadeada *a, ListaEncadeada *b) {
	printf("{");
	while ((a->proximo != NULL) && (b->proximo != NULL)) {
		if (a->anterior != NULL) {
			printf(",");
		}
		a = a->proximo;
		b = b->proximo;
		printf(" (%d, %d)", a->valor.a, b->valor.b);
	}
	printf(" }");
}

int xmain(void) {
	printf("PPH\n");

	int a0 = 132;
	int b0 = 434;
	int a[] = { 132, 461, 10, 130 };
	int b[] = { 563, 874, 581, 84 };
	printf("(a0, b0) = (%d, %d)\n", a0, b0);
	printf("S = ");
	imprime_pares_ab(a, b, 4);
	printf("\n");


	printf("\nALGORITMO 1\n");

	ListaEncadeada *Sa = inicializar_lista();
	ListaEncadeada *Sb = inicializar_lista();
	double r = pph_algoritmo1(a0, b0, 4, a, b, Sa, Sb);
	double R = calcula_R(a0, b0, Sa, Sb);

	printf("r = %f, R = %f\n", r, R);
	printf("S* = ");
	imprime_pares(Sa, Sb);

	desalocar_lista(Sa);
	desalocar_lista(Sb);
	printf("\n");


	printf("\nALGORITMO 2\n");

	Sa = inicializar_lista();
	Sb = inicializar_lista();
	r = pph_algoritmo2(a0, b0, 4, a, b, Sa, Sb);
	R = calcula_R(a0, b0, Sa, Sb);

	printf("r = %f, R = %f\n", r, R);
	printf("S* = ");
	imprime_pares(Sa, Sb);

	desalocar_lista(Sa);
	desalocar_lista(Sb);
	printf("\n");

	return 0;
}
