/*
 * ParOrdenado.h
 *
 *  Created on: 23/05/2013
 *      Author: marcelo
 */

#ifndef PARORDENADO_H_
#define PARORDENADO_H_


struct PAR_ORDENADO {
	int a;
	int b;
};

typedef struct PAR_ORDENADO ParOrdenado;

double razao(ParOrdenado *ab);


#endif /* PARORDENADO_H_ */
