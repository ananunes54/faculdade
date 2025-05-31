#include "NODE.h"

Node *InsereFinal(Node *cabeca, Certificado certificado) {
	if (cabeca == NULL) {
		Node *novo = (Node *)malloc(sizeof(Node));
		novo->certificado = certificado;
		novo->prox = NULL;
		return novo;
	}
	cabeca->prox = InsereFinal(cabeca->prox, certificado);
	return cabeca;
}

void LiberaListaLigada(Node *cabeca) {
	if (cabeca == NULL) return;
	LiberaListaLigada(cabeca->prox);
	if (cabeca->certificado != NULL) free(cabeca->certificado);
	free(cabeca);
}
