#include <stdio.h>
#include <stdlib.h>
#include "PD.h"
#include "FE.h"

int main() {
	Pilha *p = cria_pilha();
	Fila *f = cria_fila();
	pushPilha(p, 1);
	pushFila(f, 1);
	int popp = popPilha(p);
	int popf = popFila(f);
	freePilha(p);
	freeFila(f);
	return 0;
}
