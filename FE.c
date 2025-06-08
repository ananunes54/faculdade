#include "FE.h"
#include <stdlib.h>


Fila *cria_fila() 
{
	Fila *f = (Fila *)malloc(sizeof(Fila));
	f->inicio = f->fim = f->elementos_na_fila = 0; 
	return f;	
}



Certificado popFila(Fila *f) 
{
	Certificado temp = f->vetor[f->inicio];
	f->inicio = (f->inicio + 1) % TAMANHO_MAXIMO_FILA;
	f->elementos_na_fila = f->elementos_na_fila - 1;
        return temp;
}



void pushFila(Fila *f, Certificado certificado) 
{
	f->vetor[f->fim] = certificado;

	f->fim = (f->fim + 1) % TAMANHO_MAXIMO_FILA; 
	f->elementos_na_fila = f->elementos_na_fila + 1; 
}




void freeFila(Fila *f) 
{
	free(f);
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
