#include "FE.h"
#define MAX 100

typedef struct fila {
	int v[MAX];
	int inicio, fim, tamanho;
} Fila;

Fila *cria_fila() {
	Fila *f = (Fila *)malloc(sizeof(Fila));
	f->inicio = f->fim = f->tamanho = 0; //inicilizando a fila para que esteja vazia
	return f;	
}

int popFila(Fila *f) {
	int temp = f->v[f->inicio];
	f->inicio = (f->inicio + 1) % MAX; //atualizando o inicio da fila para o próximo índice; usando %MAX para utilizar o número máximo de elementos na fila
}

void pushFila(Fila *f, int x) {
	f->v[f->fim] = x;
	f->fim = (f->fim + 1) % MAX; //da mesma forma que no pop, tornando a fila circular
	f->tamanho = f->tamanho + 1; //atualizando o tamanho da fila
}


void freeFila(Fila *f) {
	free(f);
}
