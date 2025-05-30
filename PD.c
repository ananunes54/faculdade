#include "PD.h"
#include <stdlib.h>

/*
typedef struct Nodo {
	Certificado *certificado;
	struct Nodo *prox;
} Nodo;

typedef struct Certificado {
	char *nome;
	int valor;
} Certificado;

typedef struct Pilha {
	Nodo *topo;
} Pilha;

*/


Pilha *cria_pilha() {
	Pilha *p = (Pilha *)malloc(sizeof(Pilha));
	p->topo = NULL;
	return p;
}

Certificado popPilha(Pilha *p) {
	Certificado temp = *(p->topo->certificado);
	Node *aux = p->topo->prox;
	free(p->topo);
	p->topo = aux;
	return temp;
}

void pushPilha(Pilha *p, char *nome, int valor) {
	Node *novo = (Node *)malloc(sizeof(Node));
	novo->certificado = (Certificado *)malloc(sizeof(Certificado));
	novo->certificado->nome = nome;
	novo->certificado->valor = valor;
	novo->prox = p->topo;
	p->topo = novo;
}

void freePilha(Pilha *p) {
	if (p->topo == NULL) {
		free(p);
		return;
	}
	Node *aux = p->topo->prox;
	free(p->topo->certificado);
	free(p->topo);
	p->topo = aux;
	freePilha(p);
}

int pilhaVazia(Pilha *p) {
	if (p->topo == NULL)
		return 1;
	return 0;
}
