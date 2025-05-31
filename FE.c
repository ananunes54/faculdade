#include "FE.h"
#define MAX 100

Fila *cria_fila() {
	Fila *f = (Fila *)malloc(sizeof(Fila));
	f->inicio = f->fim = f->tamanho = 0; 
	return f;	
}

Certificado popFila(Fila *f) {
	Certificado temp = f->vetor[f->inicio];
	f->inicio = (f->inicio + 1) % MAX;
	f->tamanho = f->tamanho - 1;
        return temp;
}

void pushFila(Fila *f, Certificado certificado) {
	f->vetor[f->fim] = certificado;

	f->fim = (f->fim + 1) % MAX; 
	f->tamanho = f->tamanho + 1; 
}


void freeFila(Fila *f) {
	free(f);
}

int filaVazia(Fila *f) {
	if (f->inicio == f->fim && f->tamanho == 0)
		return 1;
	return 0;
}
