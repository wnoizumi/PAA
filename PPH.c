/*
 * PPH.c
 *
 *  Created on: 19/05/2013
 *      Author: marcelo
 */

#include <stdlib.h>
#include "PPH.h"
#include "ParOrdenado.h"
#include "ListaEncadeada.h"
#include "MergeSort.h"

double calcula_R_old(int a0, int b0, ListaEncadeada *S) {
	int somaA = a0;
	int somaB = b0;

	while (S->proximo != NULL) {
		S = S->proximo;
		somaA = somaA + S->valor->a;
		somaB = somaB + S->valor->b;
	}

	return ((double) somaA) / somaB;
}

double calcula_R(ParOrdenado *a0b0, ListaEncadeada *S) {
	ParOrdenado *soma = malloc(sizeof(ParOrdenado));
	soma->a = a0b0->a;
	soma->b = a0b0->b;

	while (S->proximo != NULL) {
		S = S->proximo;
		soma->a = soma->a + S->valor->a;
		soma->b = soma->b + S->valor->b;
	}

	double r = razao(soma);
	free(soma);
	return r;
}

double pph_algoritmo1(ParOrdenado *a0b0, int n, ParOrdenado *ab, ListaEncadeada *S) {

	/* "... inicia com R = a0 / b0..." */
	double R = razao(a0b0);
	int sizeS = 0;
	ListaEncadeada *Sk = S;

	// "... testa repetidamente se existe algum par (ak, bk)
	//  que satisfaz as condições do lema."
	for (int k = 0; k < n; k++) {
		ParOrdenado *abk = ab + k;
		double r = razao(abk);

		// "... No caso afirmativo..."
		if (r > R) {
			// "... inclui o par no conjunto S..."
			Sk = inserir_depois_de(Sk, abk);

			sizeS = sizeS + 1;
			// "... atualiza o valor de R... "
			R = calcula_R(a0b0, S);

			// "... e repete o teste."
			ListaEncadeada *x = S;
			while (x->proximo != NULL) {
				x = x->proximo;
				double r = razao(x->valor);
				// "... Se existir um elemento em S que não satisfaz
				//  as condições do lema..."
				if (r < R) {
					// "... este elemento deve ser removido."
					x = remover(x);
				}
			}
		}
	}
	return R;
}


double pph_algoritmo2(ParOrdenado *a0b0, int n, ParOrdenado *ab, ListaEncadeada *S) {

	/* "... inicia com R = a0 / b0..." */
	double R = razao(a0b0);
	int sizeS = 0;

	// Modificação com relação à primeira versão: ordena antes.
	merge_sort(ab, n);
	ListaEncadeada *Sk = S;

	// "... testa repetidamente se existe algum par (ak, bk)
	//  que satisfaz as condições do lema."
	for (int k = 0; k < n; k++) {
		ParOrdenado *abk = ab + k;
		double r = razao(abk);

		// "... No caso afirmativo..."
		if (r > R) {
			// "... inclui o par no conjunto S..."
			Sk = inserir_depois_de(Sk, abk);

			sizeS = sizeS + 1;
			// "... atualiza o valor de R... "
			R = calcula_R(a0b0, S);

			// "... e repete o teste."
//			ListaEncadeada *x = S;
//			while (x->proximo != NULL) {
//				x = x->proximo;
//				double r = ((double) (x->valor.a)) / x->valor.b;
//				// "... Se existir um elemento em S que não satisfaz
//				//  as condições do lema..."
//				if (r < R) {
//					// "... este elemento deve ser removido."
//					x = remover(x);
//				}
//			}
		}
	}
	return R;
}

// Primeira chamada: pph_alg4(a0, b0, n, a, b, a0/b0, 0);
double pph_algoritmo4(ParOrdenado *a0b0, int n, ParOrdenado *ab, double R, int indiceInicial) {

	int p_inicio = indiceInicial;
	int p_fim = n - 1;

	while (p_inicio < p_fim) {
		ParOrdenado *apbp = ab + p_inicio;
		double r = razao(apbp);
		if (r > R) {
			ParOrdenado *ab_inicio = ab + p_inicio;
			ParOrdenado *ab_fim = ab + p_fim;
			ParOrdenado *temp = malloc(sizeof(ParOrdenado));

			temp->a = ab_fim->a;
			temp->b = ab_fim->b;
			ab_fim->a = ab_inicio->a;
			ab_fim->b = ab_inicio->b;
			ab_inicio->a = temp->a;
			ab_inicio->b = temp->b;

			free(temp);
			p_fim--;
		} else {
			p_inicio++;
		}
	}

	if (p_inicio == indiceInicial) {
		return R;
	} else {
		ParOrdenado *soma = malloc(sizeof(ParOrdenado));
		soma->a = a0b0->a;
		soma->b = a0b0->b;

		for (int i = p_inicio; i < n; i++) {
			soma->a = soma->a + (ab + i)->a;
			soma->b = soma->b + (ab + i)->b;
		}
		double r = razao(soma);
		free(soma);

		return pph_algoritmo4(a0b0, n, ab, r, p_inicio);
	}
}
