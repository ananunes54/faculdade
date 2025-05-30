#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "PD.h"
#include "FE.h"

#define TAMANHO_BUFFER 128 //20 bytes reservados para a escolha da função, 4 bytes reservados para algum valor, 2 bytes reservados para espaços
#define TAMANHO_BUFFER_NOME 102

enum program_flag { CONTINUE, TERMINATE };


void EmpilharCertificado(char *buffer, Pilha *pilha) {
	
	int i = 0;
	int ch = 0;
	char nome[TAMANHO_BUFFER_NOME] = {0};

	//laço para ler até que encontre caracteres que representam numeros
	for (; i < TAMANHO_BUFFER_NOME; i++) {
		if (buffer[i] >= '0' && buffer[i] <= '9') {
			break;
		}
		nome[i] = toupper(buffer[i]);
	}

	//laço para transformar em int o numero digitado
	while (i <= 105) {
		if (buffer[i] < '0' || buffer[i] > '9')
			break;
		ch *= 10;
		ch += (int)(buffer[i] - '0');
		i++;
	}

	pushPilha(pilha, nome, ch);

	printf("%s empilhou certificado de %d horas\n", nome, ch);
}

void RepassarCertificado(char *buffer, Pilha *pilha, Fila *fila) {
	int certificados_a_repassar = atoi(buffer);
	int certificados_repassados = 0;
	for (; certificados_repassados < certificados_a_repassar; certificados_repassados++) {
		Certificado certificado = popPilha(pilha);
		pushFila(fila, certificado.nome, certificado.valor);
	}

	printf("[%d] certificados repassados\n", certificados_repassados);

}

void ProcessarCertificado(Fila *fila, Fila *sistema, int quantidade) {
	for (int i = 0; i < quantidade; i++) {
		Certificado certificado = popFila(fila);
		push(sistema, certificado.nome, certificado.valor);
	}

	printf("[%d] certificados processados\n");

}

void CovalidarDisciplina () {}

int main() {

	char buffer[TAMANHO_BUFFER+1] = {0}; 
	char *token_pointer;
	enum program_flag status = CONTINUE;

	Pilha *pilha = cria_pilha();
	Fila *fila = cria_fila();
	Fila *sistema = cria_fila();

	while (status == CONTINUE) {
entrada:
		//registra entrada do usuario
		if (fgets(buffer, TAMANHO_BUFFER, stdin) == NULL) {
		    printf("erro ao ler entrada\n");
		    exit(EXIT_FAILURE);
		}

		buffer[strcspn(buffer, "\n")] = '\0'; 
		
		//define endereço em que começam os argumentos das funções
		for (int i = 0;; i++) {
			if (buffer[i] == ' ') {
				token_pointer = &buffer[i+1];
				break;
		}
	

		switch (buffer[0]) {
			case 'c':
				if (buffer[1] == 'e')
					EmpilharCertificado(token_pointer, pilha); //registra carga horaria de um aluno por vez

				else if (buffer[1] == 'o')
					ProcessarCertificado(buffer);		
				break;
			case 'd':
				RepassarCertificado(token_pointer, pilha, fila);
				break;

			case 'v':
				CovalidarDisciplina();
				break;
			case 's':
				break;
			case 'F':
				status = TERMINATE;
				break;
		}
	}

	return 0;
}

