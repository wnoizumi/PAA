/*
 * Main.c
 *
 *  Created on: 19/05/2013
 *      Author: marcelo
 */


//#include <stdlib>
#include <cstdio>
#include "Instancia.h"
#include "ListaEncadeada.h"
#include "CPUTimer.h"

using namespace std;


void imprime_pares_ab(ParOrdenado *ab, int n) {
	printf("{");
	for (int i = 0; i < n; i++) {
		if (i > 0) {
			printf(",");
		}
		printf(" (%d, %d)", (ab + i)->a, (ab + i)->b);
	}
	printf(" }");
}

void imprime_pares(ListaEncadeada *l) {
	printf("{");
	while (l->proximo != NULL) {
		if (l->anterior != NULL) {
			printf(",");
		}
		l = l->proximo;
		printf(" (%d, %d)", l->valor->a, l->valor->b);
	}
	printf(" }");
}

int main(int argc, char **argv) {
	printf("PPH\n");

	int n = 0;
	ParOrdenado *a0b0 = new ParOrdenado();
	ParOrdenado *ab = NULL;

	if (argc == 2) {
		char *nomeArquivo = argv[1];
		FILE *arquivo = NULL;
		printf("Lendo instâncias de \"%s\"... ", nomeArquivo);
		arquivo = fopen(nomeArquivo, "r");
		if (arquivo == NULL) {
			printf("Não foi possível abrir \"%s\".\n", nomeArquivo);
			return EXIT_FAILURE;
		}

		int eof;
		eof = !fscanf(arquivo, "%d\n", &n);
		if (eof) {
			printf("O arquivo \"%s\" está vazio.\n", nomeArquivo);
			free(a0b0);
			fclose(arquivo);
			return EXIT_FAILURE;
		}

		ab = new ParOrdenado[n];

		eof = !fscanf(arquivo, "%d\n", &a0b0->a);
		if (eof) {
			printf("O arquivo \"%s\" está incompleto.\n", nomeArquivo);
			free(a0b0);
			free(ab);
			fclose(arquivo);
			return EXIT_FAILURE;
		}
		for (int i = 0; i < n; i++) {
			eof = !fscanf(arquivo, "%d\n", &(ab + i)->a);
			if (eof) {
				printf("O arquivo \"%s\" está incompleto.\n", nomeArquivo);
				free(a0b0);
				free(ab);
				fclose(arquivo);
				return EXIT_FAILURE;
			}
		}

		eof = !fscanf(arquivo, "%d\n", &a0b0->b);
		if (eof) {
			printf("O arquivo \"%s\" está incompleto.\n", nomeArquivo);
			free(a0b0);
			free(ab);
			fclose(arquivo);
			return EXIT_FAILURE;
		}
		for (int i = 0; i < n; i++) {
			eof = !fscanf(arquivo, "%d\n", &(ab + i)->b);
			if (eof) {
				printf("O arquivo \"%s\" está incompleto.\n", nomeArquivo);
				free(a0b0);
				free(ab);
				fclose(arquivo);
				return EXIT_FAILURE;
			}
		}

		fclose(arquivo);
		printf("%d pares lidos.\n", n);
	} else {
		printf("Sintaxe: PPH <nome do arquivo>\nDemonstração com instância de teste:\n");
		n = 4;
		a0b0->a = 132;
		a0b0->b = 434;
		ab = new ParOrdenado[n];
		int a[] = { 132, 461, 10, 130 };
		int b[] = { 563, 874, 581, 84 };
		for (int i = 0; i < 4; i++) {
			ab[i].a = a[i];
			ab[i].b = b[i];
		}
	}

	printf("n = %d\n", n);
	printf("(a0, b0) = (%d, %d)\n", a0b0->a, a0b0->b);
	if (n <= 16) {
		printf("S = ");
		imprime_pares_ab(ab, n);
	}
	printf("\n");


	printf("\nALGORITMO 1\n");

	double r;
	double R;

	Instancia I1 = Instancia(a0b0, n, ab);
	r = I1.pph_algoritmo1();
	R = I1.calcula_R();

	printf("r = %f, R = %f\n", r, R);
	if (n <= 16) {
		printf("S* = ");
		imprime_pares(I1.S);
	}

	printf("\n");


	printf("\nALGORITMO 2\n");

	Instancia I2 = Instancia(a0b0, n, ab);
	r = I2.pph_algoritmo2();
	R = I2.calcula_R();

	printf("r = %f, R = %f\n", r, R);
	if (n <= 16) {
		printf("S* = ");
		imprime_pares(I2.S);
	}

	printf("\n");


	printf("\nALGORITMO 3\n");

	Instancia I3 = Instancia(a0b0, n, ab);
	r = I3.pph_algoritmo3();
	R = I3.calcula_R();

	printf("r = %f, R = %f\n", r, R);
	if (n <= 16) {
		printf("S* = ");
		imprime_pares(I3.S);
	}

	printf("\n");


	printf("\nALGORITMO 4\n");

	Instancia I4 = Instancia(a0b0, n, ab);
	r = I4.pph_algoritmo4();
//	r = pph_algoritmo4(a0b0, n, ab, a0b0->razao(), 0);

	printf("R = %f\n", r);

	printf("\n");

	delete a0b0;
	delete ab;
	return EXIT_SUCCESS;
}
