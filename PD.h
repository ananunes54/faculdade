#ifndef PD_INCLUDED_H
#define PD_INCLUDED_H
#include "NODE.h"

typedef struct pilha {
	Node *topo;
} Pilha;

Pilha *cria_pilha();
int popPilha(Pilha *p);
void pushPilha(Pilha *p, int x);
void freePilha(Pilha *p);
#endif //PD_INCLUDED_H
