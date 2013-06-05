/*
 * QuickSort.h
 *
 *  Created on: 05/06/2013
 *      Author: wnoizumi
 */

#ifndef QUICKSORT_H_
#define QUICKSORT_H_

#include "ParOrdenado.h"

void quickSort(ParOrdenado* ab, int *I, int left, int right);
int qPartition(ParOrdenado* ab, int *I, int left, int right, int pivotIndex);

#endif /* QUICKSORT_H_ */
