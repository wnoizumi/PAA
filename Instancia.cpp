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
	//Vetor I é preenchido com os "indices" originais do vetor ab
	int* I = new int[this->n];
	for (int i = 0; i < this->n; i++) {
		I[i] = i;
	}
	double r = this->pph_algoritmo3(I, 0, this->n - 1, 0, 0);
	delete I;
	return r;
}

/*
 * I: vetor contendo os indices originais do vetor ab
 * inf: indice inicial em I para a execucao do algoritmo
 * sup: indice final em I para a execucao do algoritmo
 * SumA: Somatorio acumulado de a
 * SumB: Somatorio acumulado de b
 */
double Instancia::pph_algoritmo3(int* I, int inf, int sup, long sumA, long sumB) {
	int a0 = this->a0b0->a;
	int b0 = this->a0b0->b;

	if (sup-inf+1 < 5) {
		//quantidade de pares menores do que o pivot inferior a 5
		//o algoritmo é finalizado, incluindo os pares que possuem razao maior do que R
		insertionSort(I, inf, sup);
		for (int i = sup; i >= inf; i--) {
			double R = (sumA + a0) / (float)(sumB + b0);
			ParOrdenado* newAB = &(this->ab[I[i]]);
			if (newAB->razao() > R) {
				this->Sx = this->Sx->inserir(newAB);
				sumA += newAB->a;
				sumB += newAB->b;
			}
		}
		return (sumA + a0) / (float)(sumB + b0);
	}

	int i = inf;
	//divisão e ordenação da entrada em "pedaços" de tamanho 5
	while (i < sup) {
		int l = i+4;
		if (l > sup)
			l = sup;
		insertionSort(I, i, l);
		i = i + 5;
	}

	float t1 = (sup-inf+1);
	float t2 = t1 / 5;
	int MSize = (int)ceil(t2);
	int* M = new int[MSize];
	int* MIndex = new int[MSize];
	int j = inf+2;
	//criação e preenchimento de vetor com as medianas de cada parte ordenado
	for (i = 0; i < MSize; i++) {
		M[i] = I[j];
		MIndex[i] = j;
		j += 5;
		if (j > sup)
			j = sup;
	}
	//chamada ao algoritmo do k-esimo para encontrar a mediana das medianas
	int mOfMediansIndex = kth(M, 0, MSize-1, MIndex, (int)ceil(MSize / (float)2));
	delete M;
	delete MIndex;
	//particao do vetor I, usando como pivot a mediana das medianas
	int mIndice = partition(I, inf, sup, mOfMediansIndex);
	long newSumA = sumA;
	long newSumB = sumB;
	//Calculo do somatorio de A e B para o trecho de I que contem os pares maiores do que o pivot
	for(i = mIndice; i <= sup; i++) {
		ParOrdenado* newAB = &(this->ab[I[i]]);
		newSumA += newAB->a;
		newSumB += newAB->b;
	}
	//calculo do R com base nos somatorios obtidos para os pares maiores do que o pivot
	double R = (newSumA + a0) / (float)(newSumB + b0);
	if (this->ab[I[mIndice]].razao() <= R) {
		//razao do pivot inferior ou igual ao R: chama-se o algoritmo recursivamente para os pares maiores do que o pivot
		return pph_algoritmo3(I, mIndice + 1, sup, sumA, sumB);
	} else {
		//razao do pivot maior do que R: os pares maiores ou iguais ao pivot são adicionados em S
		for(i = mIndice; i <= sup; i++) {
			this->Sx = this->Sx->inserir(&(this->ab[I[i]]));
		}
		//em seguida é feita uma chamada recursiva ao algoritmo para os pares menores do que o pivot
		return pph_algoritmo3(I, inf, mIndice - 1, newSumA, newSumB);
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

int Instancia::kth(int* I, int inf, int sup, int* IIndex, int k) {
	int i = inf;
	//divisão e ordenação da entrada em "pedaços" de tamanho 5
	while (i < sup) {
		int l = i+4;
		if (l > sup)
			l = sup;
		insertionSort(I, i, l);
		i = i + 5;
	}

	float t1 = (sup-inf+1);
	float t2 = t1 / 5;
	int MSize = (int)ceil(t2);
	int* M = new int[MSize];
	int* MIndex = new int[MSize];
	int j = 2;
	//criação e preenchimento de vetor com as medianas de cada parte ordenado
	for (i = 0; i < MSize; i++) {
		M[i] = I[j];
		MIndex[i] = j;
		j += 5;
		if (j > sup)
			j = sup;
	}

	int mOfMediansIndex = MSize > 1 ? kth(M, 0, MSize-1, MIndex, (int)ceil(MSize / 2)) : MIndex[0];

	delete M;
	delete MIndex;
	//particao do vetor I, usando como pivot a mediana das medianas
	int mIndice = kthPartition(I, 0, sup, IIndex, mOfMediansIndex);

	if (mIndice+1 == k) {
		return IIndex[mIndice];
	} else if (k < mIndice+1)
		return kth(I, inf, mIndice-1, IIndex, k);
	return kth(I, mIndice+1, sup, IIndex, k);
}

int Instancia::kthPartition(int* I, int inf, int sup, int* IIndex, int pivot) {
	int min = inf, max = sup;

	int pivotValue = I[pivot];
	int pivotIndex = IIndex[pivot];
	I[pivot] = I[max];
	IIndex[pivot] = IIndex[max];
	I[max] = pivotValue;
	IIndex[max] = pivotIndex;
	int storeIndex = min;

	while(min < max) {
		if (this->ab[I[min]].razao() <= this->ab[pivotValue].razao()) {
			int tempValue = I[min];
			int tempIndex = IIndex[min];
			I[min] = I[storeIndex];
			IIndex[min] = IIndex[storeIndex];
			I[storeIndex] = tempValue;
			IIndex[storeIndex] = tempIndex;
			storeIndex++;
		}
		min++;
	}
	I[max] = I[storeIndex];
	IIndex[max] = IIndex[storeIndex];
	I[storeIndex] = pivotValue;
	IIndex[storeIndex] = pivotIndex;

	return storeIndex;
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
