#ifndef PD_INCLUDED_H
#define PD_INCLUDED_H
#include "NODE.h"

typedef struct pilha {
	Node *topo;
} Pilha;

Pilha *cria_pilha();
Certificado popPilha(Pilha *p);
void pushPilha(Pilha *p, char *nome, int valor);
void freePilha(Pilha *p);
int pilhaVazia(Pilha *p);
#endif //PD_INCLUDED_H
