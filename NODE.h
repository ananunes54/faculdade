#ifndef NODE_INCLUDED_H
#define NODE_INCLUDED_H
#define MAX 100
typedef struct Certificado {
	char *nome;
	int valor;
} Certificado;

typedef struct node {
	Certificado *certificado;
	struct node *prox;
} Node;
#endif //NODE_INCLUDED_H


