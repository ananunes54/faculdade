#ifndef NODE_INCLUDED_H
#define NODE_INCLUDED_H

#define TAMANHO_MAXIMO_PILHA 50
#define TAMANHO_MAXIMO_FILA 25
#define TAMANHO_BUFFER_NOME 100
#define TAMANHO_BUFFER 128


typedef struct Certificado {
	char nome[TAMANHO_BUFFER_NOME];
	int ch;
} Certificado;

typedef struct node {
	Certificado *certificado;
	struct node *prox;
} Node;


#endif //NODE_INCLUDED_H


