/*
 * Instancia.cpp
 *
 *  Created on: 29/05/2013
 *      Author: marcelo
 */

#include <cstdlib>
#include "Instancia.h"
#include "MergeSort.h"

using namespace std;

//Instancia::Instancia(int a0, int b0, int n, int* a, int* b) {
//	this->a0 = a0;
//	this->b0 = b0;
//	this->n = n;
//	this->a = a;
//	this->b = b;
//	this->Sa = NULL;
//	this->Sb = NULL;
//}

Instancia::Instancia(ParOrdenado* a0b0, int n, ParOrdenado* ab) {
	this->a0b0 = a0b0;
	this->n = n;
	this->ab = ab;
	this->S = new ListaEncadeada();
}

Instancia::~Instancia() {
	ListaEncadeada* proximo = this->S->proximo;
	while (proximo != NULL) {
		ListaEncadeada* elementoADesalocar = proximo;
		proximo = proximo->proximo;
		delete elementoADesalocar;
	}
	delete this->S;
}

double Instancia::calcula_R() {
	ParOrdenado soma = ParOrdenado(a0b0);

	while (S->proximo != NULL) {
		S = S->proximo;
		soma.a = soma.a + S->valor->a;
		soma.b = soma.b + S->valor->b;
	}

	double r = soma.razao();
	return r;
}

double Instancia::pph_algoritmo1() {

	/* "... inicia com R = a0 / b0..." */
	double R = a0b0->razao();
	int sizeS = 0;
	ListaEncadeada *Sk = S;

	// "... testa repetidamente se existe algum par (ak, bk)
	//  que satisfaz as condições do lema."
	for (int k = 0; k < n; k++) {
		ParOrdenado *akbk = ab + k;
		double r = akbk->razao();

		// "... No caso afirmativo..."
		if (r > R) {
			// "... inclui o par no conjunto S..."
			Sk = Sk->inserir_depois_de(Sk, akbk);
			sizeS = sizeS + 1;

			// "... atualiza o valor de R... "
			R = this->calcula_R();

			// "... e repete o teste."
			ListaEncadeada *x = S;
			ListaEncadeada *y = NULL;
			while (x->proximo != NULL) {
				y = x;
				x = x->proximo;
				double r = x->valor->razao();
				// "... Se existir um elemento em S que não satisfaz
				//  as condições do lema..."
				if (r < R) {
					// "... este elemento deve ser removido."
					x = y->removerProximo();
//					x = x->remover(x);
//					sizeS = sizeS - 1;
				}
			}
		}
	}
	return R;
}


double Instancia::pph_algoritmo2() {

	/* "... inicia com R = a0 / b0..." */
	double R = a0b0->razao();
	int sizeS = 0;

	// Modificação com relação à primeira versão: ordena antes.
	merge_sort(ab, n);
	ListaEncadeada *Sk = S;

	// "... testa repetidamente se existe algum par (ak, bk)
	//  que satisfaz as condições do lema."
	for (int k = 0; k < n; k++) {
		ParOrdenado *abk = ab + k;
		double r = abk->razao();

		// "... No caso afirmativo..."
		if (r > R) {
			// "... inclui o par no conjunto S..."
			Sk = Sk->inserir_depois_de(Sk, abk);

			sizeS = sizeS + 1;
			// "... atualiza o valor de R... "
			R = this->calcula_R();

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

double Instancia::pph_algoritmo3() {
	// Não implementado ainda.
	return -255;
}

// Primeira chamada: pph_alg4(a0, b0, n, a, b, a0/b0, 0);
double Instancia::pph_algoritmo4(ParOrdenado *a0b0, int n, ParOrdenado *ab, double R, int indiceInicial) {

	int p_inicio = indiceInicial;
	int p_fim = n - 1;

	while (p_inicio < p_fim) {
		ParOrdenado *apbp = ab + p_inicio;
		double r = apbp->razao();
		if (r > R) {
			ParOrdenado *ab_inicio = ab + p_inicio;
			ParOrdenado *ab_fim = ab + p_fim;
			ParOrdenado *temp = new ParOrdenado();

			temp->a = ab_fim->a;
			temp->b = ab_fim->b;
			ab_fim->a = ab_inicio->a;
			ab_fim->b = ab_inicio->b;
			ab_inicio->a = temp->a;
			ab_inicio->b = temp->b;

			delete temp;
			p_fim--;
		} else {
			p_inicio++;
		}
	}

	if (p_inicio == indiceInicial) {
		return R;
	} else {
//		ParOrdenado soma = ParOrdenado(a0b0->a, a0b0->b);
		ParOrdenado *soma = new ParOrdenado(a0b0->a, a0b0->b);

		for (int i = p_inicio; i < n; i++) {
			soma->a = soma->a + (ab + i)->a;
			soma->b = soma->b + (ab + i)->b;
		}
		double r = soma->razao();
		delete soma;

		return pph_algoritmo4(a0b0, n, ab, r, p_inicio);
	}
}
