/*
 * ParOrdenado.cpp
 *
 *  Created on: 26/05/2013
 *      Author: marcelo
 */

#include "ParOrdenado.h"

ParOrdenado::ParOrdenado() {
	this->a = 0;
	this->b = 0;
}

ParOrdenado::ParOrdenado(int valor_a, int valor_b) {
	this->a = valor_a;
	this->b = valor_b;
}

ParOrdenado::ParOrdenado(ParOrdenado* outroPar) {
	this->a = outroPar->a;
	this->b = outroPar->b;
}

double ParOrdenado::razao() {
	return ((double) this->a) / this->b;
}
