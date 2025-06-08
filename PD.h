#ifndef PD_INCLUDED_H
#define PD_INCLUDED_H
#include "NODE.h"

typedef struct pilha {
	Node *topo;
	int elementos_na_pilha;
} Pilha;

Pilha *cria_pilha();
Certificado popPilha(Pilha *p);
void pushPilha(Pilha *p, Certificado certificado);
void freePilha(Pilha *p);
void printPilha(Pilha *p);
int pilhaVazia(Pilha *p);
int pilhaCheia(Pilha *p);
#endif //PD_INCLUDED_H
