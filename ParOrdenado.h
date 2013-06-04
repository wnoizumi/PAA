/*
 * ParOrdenado.h
 *
 *  Created on: 26/05/2013
 *      Author: marcelo
 */

#ifndef PARORDENADO_H_
#define PARORDENADO_H_
#define INFINITO 2000.0;

class ParOrdenado {

public:
	long a;
	long b;
	ParOrdenado();
//	ParOrdenado(int valor_a, int valor_b);
	ParOrdenado(ParOrdenado* outroPar);
	double razao();
};

#endif /* PARORDENADO_H_ */
