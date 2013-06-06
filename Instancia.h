/*
 * Instancia.h
 *
 *  Created on: 29/05/2013
 *      Author: marcelo
 */

#ifndef INSTANCIA_H_
#define INSTANCIA_H_

#include "ParOrdenado.h"
#include "ListaEncadeada.h"

class Instancia {
public:
//	Instancia(int a0, int b0, int n, int* a, int* b);
	Instancia(ParOrdenado* a0b0, int n, ParOrdenado* ab);
	virtual ~Instancia();
	double calcula_R();
	double pph_algoritmo1();
	double pph_algoritmo2();
	double pph_algoritmo3();
	double pph_algoritmo4();
	ListaEncadeada* S;
private:
	ParOrdenado* a0b0;
	int n;
	ParOrdenado* ab;
	ListaEncadeada* Sx;
	double pph_algoritmo3(ParOrdenado* I, int inf, int sup, long sumA, long sumB);
	void insertionSort(ParOrdenado* I, int inf, int sup);
	int partition(ParOrdenado* I, int inf, int sup, int mOfMediansIndex);
	int kth(ParOrdenado** I, int inf, int sup, int* IIndex, int k);
	void kthInsertionSort(ParOrdenado** I, int inf, int sup, int* IIndex);
	int kthPartition(ParOrdenado** I, int inf, int sup, int* IIndex, int pivot);
	double pph_algoritmo4(double R, int indiceInicial, int* I);
};

#endif /* INSTANCIA_H_ */
