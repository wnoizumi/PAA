/*
 * PPH.h
 *
 *  Created on: 26/05/2013
 *      Author: marcelo
 */

#ifndef PPH_H_
#define PPH_H_


#include "ParOrdenado.h"
#include "ListaEncadeada.h"


double calcula_R(ParOrdenado *a0b0, ListaEncadeada *S);

double pph_algoritmo1(ParOrdenado *a0b0, int n, ParOrdenado *ab, ListaEncadeada *S);

double pph_algoritmo2(ParOrdenado *a0b0, int n, ParOrdenado *ab, ListaEncadeada *S);

double pph_algoritmo4(ParOrdenado *a0b0, int n, ParOrdenado *ab, double R, int indiceInicial);


#endif /* PPH_H_ */
