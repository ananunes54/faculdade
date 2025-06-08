#include "PE.h"
#include <string.h>
#include <stdlib.h>


Pilha *cria_pilha() 
{
	Pilha *pilha = (Pilha *)malloc(sizeof(Pilha));
	pilha->topo = -1;
	return pilha;
}

Certificado popPilha(Pilha *p)
{
	Certificado certificado = p->certificados[p->topo];
	p->topo = p->topo - 1;
	return certificado;
}

void pushPilha(Pilha *p, Certificado certificado)
{
	p->topo = p->topo + 1;
	strcpy(p->certificados[p->topo].nome, certificado.nome);
	p->certificados[p->topo].ch = certificado.ch;

}

void freePilha(Pilha *p)
{
	free(p);
}

int pilhaVazia(Pilha *p)
{
	if (p->topo == -1)
		return 1;
	return 0;
}

int pilhaCheia(Pilha *p)
{
	if (p->topo == TAMANHO_MAXIMO_PILHA - 1)
		return 1;
	return 0;
}
