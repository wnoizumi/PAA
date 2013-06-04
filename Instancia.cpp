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
	int I[this->n];
	for (int i = 0; i < this->n; i++) {
		I[i] = i;
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
	int M[MSize];
	int MIndex[MSize];
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
	//delete M;
	//delete MIndex;
	//particao do vetor I, usando como pivot a mediana das medianas
	int mIndice = partition(I, inf, sup, mOfMediansIndex);
	long newSumA = sumA;
	long newSumB = sumB;
	//Calculo do somatorio de A e B para o trecho de I que contem os pares maiores do que o pivot
	ParOrdenado* newAB = NULL;
	for(i = mIndice; i <= sup; i++) {
		newAB = &(this->ab[I[i]]);
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
		kthInsertionSort(I, i, l, IIndex);
		i = i + 5;
	}

	if (sup - inf + 1 <= 5)
		return I[k];

	int j = 2;
	float t2 = (sup-inf+1) / 5;
	int MSize = (int)floor(t2);
	if (MSize <= 1)
		return I[j];

	int M[MSize];
	int MIndex[MSize];
	//criação e preenchimento de vetor com as medianas de cada parte ordenado
	for (i = 0; i < MSize; i++) {
		M[i] = I[j];
		MIndex[i] = j;
		j += 5;
		if (j > sup)
			j = sup;
	}

	int mOfMediansIndex = MSize > 1 ? kth(M, 0, MSize-1, MIndex, (int)ceil(MSize / 2)) : MIndex[0];

	//particao do vetor I, usando como pivot a mediana das medianas
	int mIndice = kthPartition(I, 0, sup, IIndex, mOfMediansIndex);

	if (mIndice+1 == k) {
		return IIndex[mIndice];
	} else if (k < mIndice+1)
		return kth(I, inf, mIndice-1, IIndex, k);
	return kth(I, mIndice+1, sup, IIndex, k);
}

void Instancia::kthInsertionSort(int* I, int inf, int sup, int* IIndex) {
	double value;
	int index, iIndex;
	int j;
	for (int i = inf; i <= sup; i++) {
		value = this->ab[I[i]].razao();
		index = I[i];
		iIndex = IIndex[i];
		j = i;
		while ((j > 0) && (this->ab[I[j - 1]].razao() > value)) {
			I[j] = I[j - 1];
			IIndex[j] = IIndex[j - 1];
			j = j - 1;
	    }
		I[j] = index;
		IIndex[j] = iIndex;
	}
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
		if (this->ab[I[min]].razao() <= this->ab[I[pivot]].razao()) {
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
	while (inf < sup) {
		double r = this->ab[I[inf]].razao();
		if (r > R) {
			int temp = I[sup];
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
		double r = soma->razao();
		delete soma;

		return pph_algoritmo4(r, inf, I);
	}
}
