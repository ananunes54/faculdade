#ifndef NODE_INCLUDED_H
#define NODE_INCLUDED_H
#define MAX 100
#define TAMANHO_BUFFER_NOME 102
typedef struct Certificado {
	char nome[TAMANHO_BUFFER_NOME];
	int ch;
} Certificado;

typedef struct node {
	Certificado *certificado;
	struct node *prox;
} Node;

Node *InsereFinal(Node *cabeca, Certificado certificado);
void LiberaListaÇigada(Node *cabeca);

#endif //NODE_INCLUDED_H


