#ifndef FD_INCLUDED_H
#define FD_INCLUDED_H
#include "NODE.h"

typedef struct Fila
{
	Node *inicio;
	Node *fim;
	int elementos_na_fila;
} Fila;

Fila *cria_fila();
Certificado popFila(Fila *f);
void pushFila(Fila *f, Certificado certificado);
void freeFila(Fila *f);
void printFila(Fila *f);
int filaVazia(Fila *f);
int filaCheia(Fila *f);
#endif //FD_INCLUDED_H
