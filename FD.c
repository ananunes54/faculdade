#include "FD.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


Fila *cria_fila()
{
	Fila *fila = (Fila *)malloc(sizeof(Fila));
	fila->inicio = NULL;
	fila->fim = NULL;
	fila->elementos_na_fila = 0;
	return fila;
}



Certificado popFila(Fila *f)
{
	Certificado certificado = *(f->inicio->certificado);
	Node *aux = f->inicio->prox;
	free(f->inicio->certificado);
	free(f->inicio);
	f->inicio = aux;
	f->elementos_na_fila = f->elementos_na_fila - 1;
	return certificado;
}



void pushFila(Fila *f, Certificado certificado)
{
	Node *novo = (Node *)malloc(sizeof(Node));
	novo->certificado = (Certificado *)malloc(sizeof(Certificado));
	strcpy(novo->certificado->nome, certificado.nome);
	novo->certificado->ch = certificado.ch;
	novo->prox = NULL;
	if (filaVazia(f))
	{
		f->fim = f->inicio = novo;
	}
	else
	{
		f->fim->prox = novo;
		f->fim = novo;
	}

	f->elementos_na_fila = f->elementos_na_fila + 1;
}



void freeFila(Fila *f)
{
	if (f->inicio == NULL && f->fim == NULL)
	{
		free(f);
		return;
	}
	
	else 
	{
		Node *aux = f->inicio->prox;
		free(f->inicio->certificado);
		free(f->inicio);
		f->inicio = aux;
		freeFila(f);
	}
}



int filaVazia(Fila *f)
{
	if (f->elementos_na_fila == 0)
		return 1;
	return 0;
}



int filaCheia(Fila *f)
{
	if (f->elementos_na_fila == TAMANHO_MAXIMO_FILA)
		return 1;
	return 0;
}
