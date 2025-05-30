#ifndef FE_INCLUDED_H
#define FE_INCLUDED_H
#include <stdlib.h>
#include "NODE.h"
#define MAX 100


typedef struct Fila {
	Certificado vetor[MAX];
	int inicio, fim, tamanho;
} Fila;

Fila *cria_fila();
Certificado *popFila(Fila *f);
void pushFila(Fila *f, char *nome, int valor);
void freeFila(Fila *f);
int filaVazia(Fila *f);
#endif //FE_INCLUDED_H
