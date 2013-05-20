/*
 * PPH.c
 *
 *  Created on: 19/05/2013
 *      Author: marcelo
 */

#include <stdlib.h>
#include "PPH.h"
#include "ListaEncadeada.h"

double calcula_R(int a0, int b0, ListaEncadeada *Sa, ListaEncadeada *Sb) {
	int somaA = a0;
	int somaB = b0;

	// Verificando Sa e Sb apenas por segurança. Eles deveriam ter sempre o mesmo tamanho.
	while ((Sa->proximo != NULL) && (Sb->proximo != NULL)) {
		Sa = Sa->proximo;
		Sb = Sb->proximo;
		somaA = somaA + Sa->valor;
		somaB = somaB + Sb->valor;
	}

	return ((double) somaA) / somaB;
}

double pph_algoritmo1(int a0, int b0, int n, int *a, int *b, ListaEncadeada *Sa,
		ListaEncadeada *Sb) {

	/* "... inicia com R = a0 / b0..." */
	double R = ((double) a0) / b0;
	int sizeS = 0;
	ListaEncadeada *SAk = Sa;
	ListaEncadeada *SBk = Sb;

	// "... testa repetidamente se existe algum par (ak, bk)
	//  que satisfaz as condições do lema."
	for (int k = 0; k < n; k++) {
		int ak = *(a + k);
		int bk = *(b + k);
		double r = ((double) ak) / bk;

		// "... No caso afirmativo..."
		if (r > R) {
			// "... inclui o par no conjunto S..."
			SAk = inserir_depois_de(SAk, ak);
			SBk = inserir_depois_de(SBk, bk);

			sizeS = sizeS + 1;
			// "... atualiza o valor de R... "
			R = calcula_R(a0, b0, Sa, Sb);

			// "... e repete o teste."
			ListaEncadeada *ax = Sa;
			ListaEncadeada *bx = Sb;
			while ((ax->proximo != NULL )&& (bx->proximo != NULL)) {
				ax = ax->proximo;
				bx = bx->proximo;
				double r = ((double) (ax->valor)) / bx->valor;
				// "... Se existir um elemento em S que não satisfaz
				//  as condições do lema..."
				if (r < R) {
					// "... este elemento deve ser removido."
					ax=remover(ax);
					bx=remover(bx);
				}
			}
		}
	}
	return R;
}
