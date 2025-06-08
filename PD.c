#include "PD.h"
#include <stdlib.h>


Pilha *cria_pilha() 
{
	Pilha *p = (Pilha *)malloc(sizeof(Pilha));
	p->topo = NULL;
	p->elementos_na_pilha = 0;
	return p;
}



Certificado popPilha(Pilha *p) 
{
	Certificado temp = *(p->topo->certificado);
	Node *aux = p->topo->prox;
	free(p->topo);
	p->topo = aux;
	p->elementos_na_pilha = p->elementos_na_pilha - 1;
	return temp;
}



void pushPilha(Pilha *p, Certificado certificado) 
{
	Node *novo = (Node *)malloc(sizeof(Node));
	novo->certificado = (Certificado *)malloc(sizeof(Certificado));
	*(novo->certificado) = certificado;
	novo->prox = p->topo;
	p->topo = novo;
	p->elementos_na_pilha = p->elementos_na_pilha + 1;
}



void freePilha(Pilha *p) 
{
	if (p->topo == NULL) 
	{
		free(p);
		return;
	}
	Node *aux = p->topo->prox;
	free(p->topo->certificado);
	free(p->topo);
	p->topo = aux;
	freePilha(p);
}




int pilhaVazia(Pilha *p) 
{
	if (p->elementos_na_pilha == 0)
		return 1;
	return 0;
}




int pilhaCheia(Pilha *p)
{
	if (p->elementos_na_pilha == TAMANHO_MAXIMO_PILHA)
		return 1;
	return 0;
}



	
