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


ParOrdenado *a0b0;
ParOrdenado *ab;
int n = 0;

void imprime_pares_ab(ParOrdenado *ab, int n) {
	printf("{");
	for (int i = 0; i < n; i++) {
		if (i > 0) {
			printf(",");
		}
		printf(" (%ld, %ld)", (ab + i)->a, (ab + i)->b);
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
		printf(" (%ld, %ld)", l->valor->a, l->valor->b);
	}
	printf(" }");
}

void algoritmo1() {
	printf("\nALGORITMO 1\n");

	Instancia I1 = Instancia(a0b0, n, ab);
	double r = I1.pph_algoritmo1();
	double R = I1.calcula_R();

	printf("r = %f, R = %f\n", r, R);
	if (n <= 16) {
		printf("S* = ");
		imprime_pares(I1.S);
	}

	printf("\n");
}

void algoritmo2() {
	printf("\nALGORITMO 2\n");

	Instancia I2 = Instancia(a0b0, n, ab);
	double r = I2.pph_algoritmo2();
	double R = I2.calcula_R();

	printf("r = %f, R = %f\n", r, R);
	if (n <= 16) {
		printf("S* = ");
		imprime_pares(I2.S);
	}

	printf("\n");
}

void algoritmo3() {
	printf("\nALGORITMO 3\n");

	Instancia I3 = Instancia(a0b0, n, ab);
	double r = I3.pph_algoritmo3();
	double R = I3.calcula_R();

	printf("r = %f, R = %f\n", r, R);
	if (n <= 16) {
		printf("S* = ");
		imprime_pares(I3.S);
	}

	printf("\n");
}

void algoritmo4() {
	printf("\nALGORITMO 4\n");

	Instancia I4 = Instancia(a0b0, n, ab);
	double r = I4.pph_algoritmo4();

	printf("R = %f\n", r);
	if (n <= 16) {
		printf("S* = ");
		imprime_pares(I4.S);
	}
}

int carregaEntrada(int argc, char **argv) {
	n = 0;
	a0b0 = new ParOrdenado();
	ab = NULL;

	if (argc >= 3) {
		char *nomeArquivo = (argv[1] + 2);
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

		eof = !fscanf(arquivo, "%ld\n", &a0b0->a);
		if (eof) {
			printf("O arquivo \"%s\" está incompleto.\n", nomeArquivo);
			free(a0b0);
			free(ab);
			fclose(arquivo);
			return EXIT_FAILURE;
		}
		for (int i = 0; i < n; i++) {
			eof = !fscanf(arquivo, "%ld\n", &(ab + i)->a);
			if (eof) {
				printf("O arquivo \"%s\" está incompleto.\n", nomeArquivo);
				free(a0b0);
				free(ab);
				fclose(arquivo);
				return EXIT_FAILURE;
			}
		}

		eof = !fscanf(arquivo, "%ld\n", &a0b0->b);
		if (eof) {
			printf("O arquivo \"%s\" está incompleto.\n", nomeArquivo);
			free(a0b0);
			free(ab);
			fclose(arquivo);
			return EXIT_FAILURE;
		}
		for (int i = 0; i < n; i++) {
			eof = !fscanf(arquivo, "%ld\n", &(ab + i)->b);
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
		printf("Sintaxe: PPH <numero do algoritmo> <nome do arquivo>\nDemonstração com instância de teste:\n");
		n = 15;
		a0b0->a = 334;
		a0b0->b = 563;
		ab = new ParOrdenado[n];
		int a[] = {272, 249, 74, 188, 186, 77, 263, 323, 100, 132, 132, 461, 10, 130, 217};
		int b[] = {874, 581, 84, 743, 820, 42, 949,  37, 936, 424,  39, 758, 83, 286, 453};
		for (int i = 0; i < n; i++) {
			ab[i].a = a[i];
			ab[i].b = b[i];
		}
	}

	printf("n = %d\n", n);
	printf("(a0, b0) = (%ld, %ld)\n", a0b0->a, a0b0->b);
	if (n <= 16) {
		printf("S = ");
		imprime_pares_ab(ab, n);
	}

	return EXIT_SUCCESS;
}

int main(int argc, char **argv) {
	printf("PPH\n");

	if (carregaEntrada(argc, argv) == EXIT_SUCCESS) {
		char algo = argv[1][0];
		switch(algo) {
			case '1':
				algoritmo1();
				break;
			case '2':
				algoritmo2();
				break;
			case '3':
				algoritmo3();
				break;
			case '4':
				algoritmo4();
				break;
		}
	}

	printf("\n");
	delete a0b0;
	return EXIT_SUCCESS;
}
