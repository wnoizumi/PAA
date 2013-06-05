/*
 * QuickSort.cpp
 *
 *  Created on: 05/06/2013
 *      Author: wnoizumi
 */

#include "QuickSort.h"
#include <stdlib.h>
#include "ParOrdenado.h"

int qPartition(ParOrdenado* ab, int *I, int left, int right, int pivotIndex) {
	double pivotValue = ab[I[pivotIndex]].razao();
	int temp = I[right];
	I[right] = I[pivotIndex];
	I[pivotIndex] = temp;
	int storeIndex = left;
	for (int i = left; i < right; ++i) {
		if (ab[I[i]].razao() <= pivotValue) {
			temp = I[i];
			I[i] = I[storeIndex];
			I[storeIndex] = temp;
			storeIndex++;
		}
	}
	temp = I[right];
	I[right] = I[storeIndex];
	I[storeIndex] = temp;

	return storeIndex;
}

void quickSort(ParOrdenado* ab, int *I, int left, int right) {
	if (left < right) {
		int pivotIndex = (int)left+(right-left) / 2;
		pivotIndex = qPartition(ab, I, left, right, pivotIndex);

		quickSort(ab, I, left, pivotIndex-1);
		quickSort(ab, I, pivotIndex+1, right);
	}
}
