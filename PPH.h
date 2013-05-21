/*
 * PPH.h
 *
 *  Created on: 19/05/2013
 *      Author: marcelo
 */

#ifndef PPH_H_
#define PPH_H_

#include "ListaEncadeada.h"

double calcula_R(int a0, int b0, ListaEncadeada *Sa, ListaEncadeada *Sb);

double pph_algoritmo1(int a0, int b0, int n, int *a, int *b, ListaEncadeada *Sa,
		ListaEncadeada *Sb);

double pph_algoritmo2(int a0, int b0, int n, int *a, int *b, ListaEncadeada *Sa,
		ListaEncadeada *Sb);


#endif /* PPH_H_ */
