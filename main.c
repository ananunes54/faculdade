#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "PD.h"
#include "FE.h"

#define TAMANHO_BUFFER 128 //20 bytes reservados para a escolha da função, 4 bytes reservados para algum valor, 2 bytes reservados para espaços
#define TAMANHO_BUFFER_NOME 102

enum program_flag { CONTINUE, TERMINATE };
enum parametrosDaFuncao { CERTIFICADO, INTEIRO, STRING };


unsigned long djb2(const char *input) 
{
	unsigned long hash = 5381;
	int c;
	while ((c = *str++))
	{
		hash = ((hash << 5) + hash) + c;
	}
	return hash%100;
}


void FormatarEntrada(char *buffer, enum parametrosDaFuncao parametro, char *nome, int *valor) 
{
	memset(nome, 0, TAMANHO_BUFFER_NOME);
	*valor = 0;

	for (int i = 0; i < TAMANHO_BUFFER && buffer[i] != 0; i++) 
	{
		switch (parametro) 
		{
			
			case CERTIFICADO:	
				if (buffer[i] < '0' || buffer[i] > '9') 
					nome[i] = toupper(buffer[i]);
			
				else if (buffer[i] >= '0' && buffer[i] <= '9') 
				{
					*valor *= 10;
					*valor += (int)(buffer[i] - '0');
				}
				break;

			
			case STRING:
				nome[i] = toupper(buffer[i]);
				break;

			
			case INTEIRO:
				*valor *= 10;
				*valor += (int)(buffer[i] - '0');
				break;
		
		}
	}

	printf("nome: %s\nvalor: %d\n", nome, *valor);

}

void EmpilharCertificado(Pilha *pilha, char *nome, int ch) 
{
	Certificado certificado = {.nome = nome, .ch = ch};

	pushPilha(pilha, certificado);

	printf("%s empilhou certificado de %d horas\n", nome, ch);
}

void RepassarCertificado(Pilha *pilha, Fila *fila, int certificados_a_repassar) 
{
	int certificados_repassados = 0;
	
	for (; certificados_repassados < certificados_a_repassar; certificados_repassados++) 
		pushFila(fila, popPilha(pilha));

	printf("[%d] certificados repassados\n", certificados_repassados);

}

void ProcessarCertificado(Fila *fila, Certificado sistema[], int certificados_a_processar) 
{
	int certificados_processados = 0;

	for ( ; certificados_processados < certificados_a_processar; certificados_processados++) 
	{		
		unsigned long hashValue = djb2();
		if (sistema[hashValue]
		pushFila(sistema, popFila(fila));
	}

	printf("[%d] certificados processados\n", certificados_processados);

}



void CovalidarDisciplina () {}

int main() 
{

	char buffer[TAMANHO_BUFFER+1] = {0}; 
	char *parametros_ptr;
	char nome[TAMANHO_BUFFER_NOME] = {0};
	enum program_flag status = CONTINUE;
	int valor = 0;
	int i;

	Pilha *pilha = cria_pilha();
	Fila *fila = cria_fila();
	Certificado *sistema[100] = {0};

	while (status == CONTINUE) 
	{
		
		if (fgets(buffer, TAMANHO_BUFFER, stdin) == NULL) {
		    printf("erro ao ler entrada\n");
		    exit(EXIT_FAILURE);
		}

		buffer[strcspn(buffer, "\n")] = '\0'; 
		
		if (buffer[0] == 'c' || buffer[0] == 'd' || buffer[0] == 'v') {
			for (i = 0; buffer[i] != ' '; i++);

			parametros_ptr = &buffer[i+1];
		
			printf("parametros ptr: %s\n buffer: %s\n", parametros_ptr, buffer);
		}

		switch (buffer[0]) {
			
			case 'F':
				status = TERMINATE;
				break;

			case 's':
				break;

			case 'c':
				if (buffer[1] == 'e')
				{
					FormatarEntrada(parametros_ptr, CERTIFICADO, nome, &valor);
					EmpilharCertificado(pilha, nome, valor); 
				}

				else if (buffer[1] == 'o')
				{
					FormatarEntrada(parametros_ptr, INTEIRO, nome, &valor);
					ProcessarCertificado(fila, sistema, valor);		
				}

				break;


			case 'd':
				FormatarEntrada(parametros_ptr, INTEIRO, nome, &valor);
				RepassarCertificado(pilha, fila, valor);
				break;


			case 'v':
				FormatarEntrada(parametros_ptr, STRING, nome, &valor);
				CovalidarDisciplina();
				break;
			}
	}
	return 0;
}

