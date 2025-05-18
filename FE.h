#ifndef FE_INCLUDED_H
#define FE_INCLUDED_H
#include <stdlib.h>
typedef struct fila Fila;
Fila *cria_fila();
int popFila(Fila *f);
void pushFila(Fila *f, int x);
void freeFila(Fila *f);
#endif //FE_INCLUDED_H
