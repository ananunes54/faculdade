#ifndef FE_INCLUDED_H
#define FE_INCLUDED_H
#include "NODE.h"

typedef struct Fila {
	Certificado vetor[TAMANHO_MAXIMO_FILA];
	int inicio, fim, elementos_na_fila;
} Fila;

Fila *cria_fila();
Certificado popFila(Fila *f);
void pushFila(Fila *f, Certificado certificado);
void freeFila(Fila *f);
void printFila(Fila *f);
int filaVazia(Fila *f);
int filaCheia(Fila *f);
#endif //FE_INCLUDED_H
