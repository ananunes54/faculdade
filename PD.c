#include "PD.h"
#include <stdlib.h>

Pilha *cria_pilha() {
	Pilha *p = (Pilha *)malloc(sizeof(Pilha));
	p->topo = NULL;
	return p;
}

int popPilha(Pilha *p) {
	int temp = p->topo->info;
	Node *aux = p->topo->prox;
	free(p->topo);
	p->topo = aux;
	return temp;
}

void pushPilha(Pilha *p, int x) {
	Node *aux = (Node *)malloc(sizeof(Node));
	aux->prox = p->topo;
	aux->info = x;
	p->topo = aux;
}

void freePilha(Pilha *p) {
	if (p->topo == NULL) {
		free(p);
		return;
	}
	Node *aux = p->topo->prox;
	free(p->topo);
	p->topo = aux;
	freePilha(p);
}
