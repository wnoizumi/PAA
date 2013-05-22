/*
 * PPH.c
 *
 *  Created on: 19/05/2013
 *      Author: marcelo
 */

#include <stdlib.h>
#include "PPH.h"
#include "ListaEncadeada.h"
#include "MergeSort.h"

//double calcula_R(int a0, int b0, ListaEncadeada *Sa, ListaEncadeada *Sb) {
//	int somaA = a0;
//	int somaB = b0;
//
//	// Verificando Sa e Sb apenas por segurança. Eles deveriam ter sempre o mesmo tamanho.
//	while ((Sa->proximo != NULL) && (Sb->proximo != NULL)) {
//		Sa = Sa->proximo;
//		Sb = Sb->proximo;
//		somaA = somaA + Sa->valor.a;
//		somaB = somaB + Sb->valor.b;
//	}
//
//	return ((double) somaA) / somaB;
//}

double calcula_R(int a0, int b0, ListaEncadeada *S) {
	int somaA = a0;
	int somaB = b0;

	while (S->proximo != NULL) {
		S = S->proximo;
		somaA = somaA + S->valor.a;
		somaB = somaB + S->valor.b;
	}

	return ((double) somaA) / somaB;
}

double pph_algoritmo1(int a0, int b0, int n, int *a, int *b, ListaEncadeada *S) {

	/* "... inicia com R = a0 / b0..." */
	double R = ((double) a0) / b0;
	int sizeS = 0;
	ListaEncadeada *Sk = S;

	// "... testa repetidamente se existe algum par (ak, bk)
	//  que satisfaz as condições do lema."
	for (int k = 0; k < n; k++) {
		int ak = *(a + k);
		int bk = *(b + k);
		double r = ((double) ak) / bk;

		// "... No caso afirmativo..."
		if (r > R) {
			// "... inclui o par no conjunto S..."
			Sk = inserir_depois_de(Sk, ak, bk);

			sizeS = sizeS + 1;
			// "... atualiza o valor de R... "
			R = calcula_R(a0, b0, S);

			// "... e repete o teste."
			ListaEncadeada *x = S;
			while (x->proximo != NULL) {
				x = x->proximo;
				double r = ((double) (x->valor.a)) / x->valor.b;
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


double pph_algoritmo2(int a0, int b0, int n, int *a, int *b, ListaEncadeada *S) {

	/* "... inicia com R = a0 / b0..." */
	double R = ((double) a0) / b0;
	int sizeS = 0;

	// Modificação com relação à primeira versão: ordena antes.
	merge_sort(S, n);
	ListaEncadeada *Sk = S;

	// "... testa repetidamente se existe algum par (ak, bk)
	//  que satisfaz as condições do lema."
	for (int k = 0; k < n; k++) {
		int ak = *(a + k);
		int bk = *(b + k);
		double r = ((double) ak) / bk;

		// "... No caso afirmativo..."
		if (r > R) {
			// "... inclui o par no conjunto S..."
			Sk = inserir_depois_de(Sk, ak, bk);

			sizeS = sizeS + 1;
			// "... atualiza o valor de R... "
			R = calcula_R(a0, b0, S);

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
double pph_algoritmo4(int a0, int b0, int n, int *a, int *b, double R, int indiceInicial) {

	int p_inicio = indiceInicial;
	int p_fim = n - 1;

	while (p_inicio < p_fim) {
		double r = ((double) *(a + p_inicio)) / *(b + p_inicio);
		if (r > R) {
			int temp;
			temp = *(a + p_fim);
			*(a + p_fim) = *(a + p_inicio);
			*(a + p_inicio) = temp;
			temp = *(b + p_fim);
			*(b + p_fim) = *(b + p_inicio);
			*(b + p_inicio) = temp;
			p_fim--;
		} else {
			p_inicio++;
		}
	}

	if (p_inicio == indiceInicial) {
		return R;
	} else {
		int somaA = a0;
		int somaB = b0;
		for (int i = p_inicio; i < n; i++) {
			somaA = somaA + *(a + i);
			somaB = somaB + *(b + i);
		}
		double r = ((double) somaA) / somaB;

		return pph_algoritmo4(a0, b0, n, a, b, r, p_inicio);
	}
}
