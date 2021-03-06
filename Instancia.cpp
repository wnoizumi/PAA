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
#include "QuickSort.h"
#include <cstdio>

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
			ListaEncadeada *y = S;
			while (y != NULL && y->proximo != NULL) {
				x = y->proximo;
				double r = x->valor->razao();
				// "... Se existir um elemento em S que não satisfaz
				//  as condições do lema..."
				if (r < R) {
					// "... este elemento deve ser removido."
					y->removerProximo();
				} else {
					y = y->proximo;
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

	int I[this->n];
	for (int i = 0; i < this->n; i++) {
		I[i] = i;
	}

	// Modificação com relação à primeira versão: ordena antes.
	//merge_sort(ab, n);
	quickSort(this->ab, I, 0, this->n-1);
	ListaEncadeada *Sk = S;

	// "... testa repetidamente se existe algum par (ak, bk)
	//  que satisfaz as condições do lema."
	for (int k = 0; k < n; k++) {
		ParOrdenado *akbk = &ab[I[k]];
		// "... No caso afirmativo..."
		if (akbk->razao() > R) {
			// "... inclui o par no conjunto S..."
			Sk = Sk->inserir(akbk);

			sizeS = sizeS + 1;
			// "... atualiza o valor de R... "
			R = this->calcula_R();
		}
	}
	return R;
}

double Instancia::pph_algoritmo3() {
	//Vetor I é preenchido com os "indices" originais do vetor ab
	ParOrdenado I[this->n];
	for (int i = 0; i < this->n; i++) {
		I[i] = this->ab + i;
	}
	double r = this->pph_algoritmo3(I, 0, this->n - 1, 0, 0);
	return r;
}

/*
 * I: vetor contendo os indices originais do vetor ab
 * inf: indice inicial em I para a execucao do algoritmo
 * sup: indice final em I para a execucao do algoritmo
 * SumA: Somatorio acumulado de a
 * SumB: Somatorio acumulado de b
 */
double Instancia::pph_algoritmo3(ParOrdenado* I, int inf, int sup, long sumA, long sumB) {
	int a0 = this->a0b0->a;
	int b0 = this->a0b0->b;

	if (sup-inf+1 < 5) {
		//quantidade de pares menores do que o pivot inferior a 5
		//o algoritmo é finalizado, incluindo os pares que possuem razao maior do que R
		insertionSort(I, inf, sup);
		for (int i = sup; i >= inf; i--) {
			double R = (sumA + a0) / (float)(sumB + b0);
			ParOrdenado* newAB = I + i;
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

	int MSize = (int)ceil((sup-inf+1) / 5);
	ParOrdenado* M[MSize];
	int MIndex[MSize];
	int j = inf+2;
	//criação e preenchimento de vetor com as medianas de cada parte ordenado
	for (i = 0; i < MSize; i++) {
		M[i] = I + j;
		MIndex[i] = j;
		j += 5;
		if (j > sup)
			j = sup;
	}

	int mOfMediansIndex = 0;
	//chamada ao algoritmo do k-esimo para encontrar a mediana das medianas
	if (MSize > 1)
		mOfMediansIndex = kth(M, 0, MSize-1, MIndex, (int)ceil(MSize / (float)2));
	else
		mOfMediansIndex = MIndex[0];

	//particao do vetor I, usando como pivot a mediana das medianas
	int mIndice = partition(I, inf, sup, mOfMediansIndex);
	ParOrdenado* newSum = new ParOrdenado();
	newSum->a = sumA;
	newSum->b = sumB;
	//Calculo do somatorio de A e B para o trecho de I que contem os pares maiores do que o pivot
	ParOrdenado* aux = NULL;
	for(i = mIndice; i <= sup; i++) {
		aux = I + i;
		newSum->a = newSum->a + aux->a;
		newSum->b = newSum->b + aux->b;
	}
	if (I[mIndice].razao() <= newSum->razao()) {
		//razao do pivot inferior ou igual ao R: chama-se o algoritmo recursivamente para os pares maiores do que o pivot
		return pph_algoritmo3(I, mIndice + 1, sup, sumA, sumB);
	} else {
		//razao do pivot maior do que R: os pares maiores ou iguais ao pivot são adicionados em S
		for(i = mIndice; i <= sup; i++) {
			this->Sx = this->Sx->inserir(&I[i]);
		}
		//em seguida é feita uma chamada recursiva ao algoritmo para os pares menores do que o pivot
		return pph_algoritmo3(I, inf, mIndice - 1, newSum->a, newSum->b);
	}
}


void Instancia::insertionSort(ParOrdenado* I, int inf, int sup) {
	ParOrdenado* par;
	int j;
	for (int i = inf; i <= sup; i++) {
		par = I + i;
		j = i;
		while ((j > inf) && (I[j - 1].razao() > par->razao())) {
			I[j] = I[j - 1];
			j = j - 1;
	    }
		I[j] = par;
	}
}

int Instancia::kth(ParOrdenado** I, int inf, int sup, int* IIndex, int k) {
	if (k < 0 || k > sup) {
		printf("\nk: %d", k);
	}

	int i = inf;
	//divisão e ordenação da entrada em "pedaços" de tamanho 5
	while (i < sup) {
		int l = i+4;
		if (l > sup)
			l = sup;
		kthInsertionSort(I, i, l, IIndex);
		i = i + 5;
	}

	int j = inf + 2;
	int MSize = (int)floor((sup-inf+1) / 5);

	ParOrdenado* M[MSize];
	int MIndex[MSize];
	//criação e preenchimento de vetor com as medianas de cada parte ordenado
	for (i = 0; i < MSize; i++) {
		M[i] = I[j];
		MIndex[i] = j;
		j += 5;
		if (j > sup)
			j = sup;
	}

	int mk = (int)ceil(MSize / 2);
	int mOfMediansIndex = MSize > 1 ? kth(M, 0, MSize-1, MIndex, mk) : MIndex[0];

	//particao do vetor I, usando como pivot a mediana das medianas
	int mIndice = kthPartition(I, inf, sup, IIndex, mOfMediansIndex);

	if (mIndice == k) {
		int ret = IIndex[mIndice];
		if (ret < 0) {
			printf("valor do k-esimo: %d", ret);
		}
		return ret;
	} else if (k < mIndice)
		return kth(I, inf, mIndice-1, IIndex, k);
	return kth(I, mIndice+1, sup, IIndex, k);
}

void Instancia::kthInsertionSort(ParOrdenado** I, int inf, int sup, int* IIndex) {
	ParOrdenado* value;
	int iIndex;
	int j;
	for (int i = inf; i <= sup; i++) {
		value = I[i];
		iIndex = IIndex[i];
		j = i;
		while (j > 0 && I[j - 1]->razao() > value->razao()) {
			I[j] = I[j - 1];
			IIndex[j] = IIndex[j - 1];
			j = j - 1;
	    }
		I[j] = value;
		IIndex[j] = iIndex;
	}
}

int Instancia::kthPartition(ParOrdenado** I, int inf, int sup, int* IIndex, int pivot) {
	if (pivot < 0 || pivot > sup) {
		printf("\nk-pivot: %d", pivot);
	}

	int min = inf, max = sup;

	ParOrdenado* pivotValue = I[pivot];
	int pivotIndex = IIndex[pivot];
	I[pivot] = I[max];
	IIndex[pivot] = IIndex[max];
	I[max] = pivotValue;
	IIndex[max] = pivotIndex;
	int storeIndex = min;

	while(min < max) {
		if (I[min]->razao() <= I[pivot]->razao()) {
			ParOrdenado* tempValue = I[min];
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

int Instancia::partition(ParOrdenado* I, int inf, int sup, int pivot) {
	if (pivot < 0 || pivot > sup) {
		printf("\npivot: %d", pivot);
	}

	int min = inf, max = sup;

	ParOrdenado* pivotValue = I + pivot;
	I[pivot] = I[max];
	I[max] = pivotValue;
	int storeIndex = min;

	while(min < max) {
		if (I[min].razao() <= pivotValue->razao()) {
			ParOrdenado* temp = I + min;
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

double Instancia::pph_algoritmo4() {
	//Vetor I é preenchido com os "indices" originais do vetor ab
	int I[this->n];
	for (int i = 0; i < this->n; i++) {
		I[i] = i;
	}

	//primeira chamada passando a razão do par a0b0 (único par em S)
	return this->pph_algoritmo4(this->a0b0->razao(), 0, I);
}

double Instancia::pph_algoritmo4(double R, int indiceInicial, int* I) {
	int inf = indiceInicial;
	int sup = n - 1;

	//partição do vetor I usando como pivot a razão R
	int temp = 0;
	while (inf < sup) {
		if (this->ab[I[inf]].razao() > R) {
			temp = I[sup];
			I[sup] = I[inf];
			I[inf] = temp;
			sup--;
		} else {
			inf++;
		}
	}

	//quando inf é igual a indiceInicial significa que o particionamento não movimentou nenhum par
	//portanto o conjunto S já está completo
	if (inf == indiceInicial) {
		return R;
	} else {
		//cálculo do novo R para a próxima recursão
		ParOrdenado *soma = new ParOrdenado(a0b0);
		for (int i = inf; i < this->n; i++) {
			soma->a += this->ab[I[i]].a;
			soma->b += this->ab[I[i]].b;
		}

		R = soma->razao();
		return pph_algoritmo4(R, inf, I);
	}
}
