/*
 * Instancia.cpp
 *
 *  Created on: 29/05/2013
 *      Author: marcelo
 */

#include <cstdlib>
#include <cmath>
#include "Instancia.h"
#include "MergeSort.h"

using namespace std;

Instancia::Instancia(ParOrdenado* a0b0, int n, ParOrdenado* ab) {
	this->a0b0 = a0b0;
	this->n = n;
	this->ab = ab;
	this->S = new ListaEncadeada();
	this->Sx = this->S;
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
	ListaEncadeada* Si = this->S;

	while (Si->proximo != NULL) {
		Si = Si->proximo;
		soma.a = soma.a + Si->valor->a;
		soma.b = soma.b + Si->valor->b;
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
			Sk = Sk->inserir(akbk);
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
		ParOrdenado *akbk = ab + k;
		double r = akbk->razao();

		// "... No caso afirmativo..."
		if (r > R) {
			// "... inclui o par no conjunto S..."
			Sk = Sk->inserir(akbk);

			sizeS = sizeS + 1;
			// "... atualiza o valor de R... "
			R = this->calcula_R();

			// ... e não precisa repetir o teste.
		}
	}
	return R;
}

double Instancia::pph_algoritmo3() {
	int* I = new int[this->n];
	for (int i = 0; i < this->n; i++) {
		I[i] = i;
	}
	double r = this->pph_algoritmo3(I, 0, this->n - 1, 0, 0);
	delete I;
	return r;
}

double Instancia::pph_algoritmo3(int* I, int inf, int sup, long sumA, long sumB) {
	int i = inf;
	while (i < sup) {
		int l = i+4;
		if (l > sup)
			l = sup;
		insertionSort(I, i, l);
		i = i + 5;
	}

	int MSize = (int)ceil((sup-inf+1) / (double)5);
	int* M = new int[MSize];
	int* MIndex = new int[MSize];

	int j = inf+2;
	for (i = 0; i < MSize; i++) {
		M[i] = I[j];
		MIndex[i] = j;
		j += 5;
		if (j > sup)
			j = sup;
	}
	int mOfMediansIndex = kith(M, MSize, MIndex, MSize / 2);
	int mIndice = partition(I, inf, sup, mOfMediansIndex);
	long newSumA = sumA;
	long newSumB = sumB;
	for(i = mIndice; i <= sup; i++) {
		ParOrdenado* newAB = &(this->ab[I[i]]);
		newSumA += newAB->a;
		newSumB += newAB->b;
	}
	int a0 = this->a0b0->a;
	int b0 = this->a0b0->b;
	double R = (newSumA + a0) / (double)(newSumB + b0);
	if (this->ab[I[mIndice]].razao() <= R) {
		return pph_algoritmo3(I, mIndice + 1, sup, sumA, sumB);
	} else {
		if (mIndice >= inf+4) {
			for(i = mIndice; i <= sup; i++) {
				this->Sx = this->Sx->inserir(&(this->ab[I[i]]));
			}
			return pph_algoritmo3(I, inf, mIndice - 1, newSumA, newSumB);
		} else {
			insertionSort(I, inf, mIndice - 1);
			for (i = mIndice-1; i >= inf; i--) {
				ParOrdenado* newAB = &(this->ab[I[i]]);
				if (newAB->razao() > R) {
					this->Sx = this->Sx->inserir(newAB);
					newSumA += newAB->a;
					newSumB += newAB->b;
				}
			}
			return (newSumA + a0) / (double)(newSumB + b0);
		}
	}
}


void Instancia::insertionSort(int* I, int inf, int sup) {
	double value;
	int index;
	int j;
	for (int i = inf; i <= sup; i++) {
		value = this->ab[I[i]].razao();
		index = I[i];
		j = i;
		while ((j > inf) && (this->ab[I[j - 1]].razao() > value)) {
			I[j] = I[j - 1];
			j = j - 1;
	    }
		I[j] = index;
	}
}

int Instancia::kith(int* M, int tamanhoM, int* MIndex, int k) {
	// TODO Fazer implementa��o correta!

	double value;
	int index, iIndex;
	int j;
	for (int i = 0; i < tamanhoM; i++) {
		value = this->ab[M[i]].razao();
		index = M[i];
		iIndex = MIndex[i];
		j = i;
		while ((j > 0) && (this->ab[M[j - 1]].razao() > value)) {
			M[j] = M[j - 1];
			MIndex[j] = MIndex[j - 1];
			j = j - 1;
	    }
		M[j] = index;
		MIndex[j] = iIndex;
	}

	return MIndex[k];
}

int Instancia::partition(int* I, int inf, int sup, int pivot) {
	int min = inf, max = sup;

	int pivotValue = I[pivot];
	I[pivot] = I[max];
	I[max] = pivotValue;
	int storeIndex = min;

	while(min < max) {
		if (this->ab[I[min]].razao() <= this->ab[pivotValue].razao()) {
			int temp = I[min];
			I[min] = I[storeIndex];
			I[storeIndex] = temp;
			storeIndex++;
		}
		min++;
	}
	I[max] = I[storeIndex];
	I[storeIndex] = pivotValue;

	return storeIndex;
}


// Primeira chamada: pph_alg4(a0, b0, n, a, b, a0/b0, 0);
double Instancia::pph_algoritmo4() {
	return this->pph_algoritmo4(this->a0b0, n, this->ab, this->a0b0->razao(), 0);
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
		ParOrdenado *soma = new ParOrdenado(a0b0);

		for (int i = p_inicio; i < n; i++) {
			soma->a = soma->a + (ab + i)->a;
			soma->b = soma->b + (ab + i)->b;
		}
		double r = soma->razao();
		delete soma;

		return pph_algoritmo4(this->a0b0, this->n, this->ab, r, p_inicio);
	}
}
