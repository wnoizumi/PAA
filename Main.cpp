/*
 * Main.c
 *
 *  Created on: 19/05/2013
 *      Author: marcelo
 */

//#include <stdlib>
#include <cstdio>
#include <sstream>
#include <string>
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

int carregaEntrada(char *nomeArquivo) {
	n = 0;
	a0b0 = new ParOrdenado();
	ab = NULL;

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

	printf("n = %d\n", n);
	printf("(a0, b0) = (%ld, %ld)\n", a0b0->a, a0b0->b);

	return EXIT_SUCCESS;
}

double executaAlgoritmo(char algo) {
	Instancia a = Instancia(a0b0, n, ab);
	switch(algo) {
		case '1':
			return a.pph_algoritmo1();
			break;
		case '2':
			return a.pph_algoritmo2();
			break;
		case '3':
			return a.pph_algoritmo3();
			break;
		case '4':
			return a.pph_algoritmo4();
			break;
	}
	return 0;
}

void gravarResultado(char algo, char* instancia, double R, CPUTimer totalTime, int k) {
	FILE *arquivo = NULL;
	char *nomeArquivo = "resultsPPH";
	arquivo = fopen(nomeArquivo, "a");
	if (arquivo == NULL) {
		printf("Não foi possível abrir \"%s\".\n", nomeArquivo);
	}

	char buff[200];
	for (int i = 0; i < 200; ++i) {
		buff[i] = '\0';
	}
	sprintf(buff, "\nalgoritmo %c - instancia: %s T CPU:   %lf   k=%d  ttotal:%lf\n", algo, instancia, totalTime.getCPUTotalSecs() / k , k, totalTime.getCPUTotalSecs());

	fwrite(buff, sizeof(char), sizeof(buff), arquivo);
	fclose(arquivo);
}

int main(int argc, char **argv) {
	printf("\nPPH");

	if (argc < 3) {
		printf("Sintaxe: PPH <numero do algoritmo> <nome do arquivo>\nDemonstração com instância de teste:\n");
		return EXIT_FAILURE;
	}

	char algo = argv[1][0];
	char *nomeArquivo = argv[1] + 3;

	if (carregaEntrada(nomeArquivo) == EXIT_SUCCESS) {
		printf("\nAlgoritmo %c", algo);
		CPUTimer totalTime;
		totalTime.reset();
		int k = 0;
		double R = 0;
		do {
			totalTime.start();

			R = executaAlgoritmo(algo);

			k++;
			totalTime.stop();
		} while ( totalTime.getCPUTotalSecs() < 5.0 );

		gravarResultado(algo, nomeArquivo, R, totalTime, k);

		printf("\nR = %lf", R);
		printf("\nT CPU:   %lf   k=%d  ttotal:%lf\n", totalTime.getCPUTotalSecs() / k , k, totalTime.getCPUTotalSecs());
	}

	printf("\n");
	delete a0b0;
	return EXIT_SUCCESS;
}
