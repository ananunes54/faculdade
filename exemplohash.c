#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct Certificado {
	char nome[100];
	int valor;
} Certificado;

typedef struct Node {
	Certificado *certificado;
	struct Node *prox;
} Node;
/*
 * mesmo rodando mais de uma vez a função strtok, ela retorna a mesma string se o primeiro argumento não for nulo 
 * não pode chamar duas vezes a função com o mesmo ponteiro, porque mesmo tendo mais strings, retorna null 
 */

unsigned long djb2(const char *str) {
	unsigned long hash = 5381;
	int c;
	while ((c = *str++)) {
		hash = ((hash << 5) + hash) + c;
	}
	printf("hash %lu\n", hash%10);
	return hash%10;
}
/*
void Sistema(Node *array, Certificado certificado_fonte) 
{
	unsigned long hashValue = djb2(certificado_fonte.nome);

	Node *aux = array+hashValue;

	while (aux->certificado != NULL) aux = aux->prox;

	
	printf("aux em null? %p\n", aux->certificado);

	if (aux->certificado == NULL)
	{
		Certificado *certificado = (Certificado *)malloc(sizeof(Certificado));
		aux->certificado = certificado;
		strcpy(certificado->nome, certificado_fonte.nome);	
		certificado->valor = certificado_fonte.valor;
	}
	printf("%s\n", array[0].certificado->nome);
	printf("%d\n", array[0].certificado->valor);


}
*/
void Sistema(Node *array, Certificado certificado_fonte) {
    unsigned long hashValue = djb2(certificado_fonte.nome) % 10;

    Node *aux = array + hashValue;

    while (aux->certificado != NULL) {
        if (aux->prox == NULL) {
            aux->prox = malloc(sizeof(Node));
            aux->prox->certificado = NULL;
            aux->prox->prox = NULL;
        }
        aux = aux->prox;
    }

    Certificado *certificado = malloc(sizeof(Certificado));
    aux->certificado = certificado;
    strcpy(certificado->nome, certificado_fonte.nome);
    certificado->valor = certificado_fonte.valor;
}

int main() 
{
	int colisoes = 0;
	
	Certificado certificado_modelo = {.nome = {'a', 'n', 'a', 0}, .valor = 10};
	
	Node array[10] = {0};

	Sistema(array, certificado_modelo);

	Sistema(array, certificado_modelo);

	printf("%p\n", array[7].prox);	
/*
	for (int i = 0; i < 100; i++) {
		unsigned long hashValue = djb2(input[i]);
		if (array[hashValue] == 1) colisoes++;
		else array[hashValue] = 1;
		printf("Hash value: %lu, %s\n", hashValue, input[i]);
	}
*/	
	return 0;
}

