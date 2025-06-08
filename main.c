#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "PD.h"
#include "FD.h"
#include <ctype.h>


enum program_flag { CONTINUE, TERMINATE };
enum parametrosDaFuncao { CERTIFICADO, INTEIRO, STRING };



unsigned long djb2(const char *input) 
{
	unsigned long hash = 5381;
	int c;
	while ((c = *input++))
	{
		hash = ((hash << 5) + hash) + c;
	}
	return hash%100;
}



void RegistrarSistema(Node *sistema, Certificado certificado_fonte, int *alunos_no_sistema)
{
	unsigned long hashValue = djb2(certificado_fonte.nome);

	Node *aux = sistema + hashValue;

	while (aux->certificado != NULL)
	{
		if (strcmp(certificado_fonte.nome, aux->certificado->nome) == 0)
		{
			aux->certificado->ch += certificado_fonte.ch;
			return;
		}
		if (aux->prox == NULL)
		{
			aux->prox = (Node *)malloc(sizeof(Node));
			aux->prox->certificado = NULL;
			aux->prox->prox = NULL;
		}
		else aux = aux->prox;
	}

	Certificado *certificado = (Certificado *)malloc(sizeof(Certificado));
	aux->certificado = certificado;
	strcpy(certificado->nome, certificado_fonte.nome);
	certificado->ch = certificado_fonte.ch;
	*alunos_no_sistema += 1;
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
				{
					if (buffer[i+1] >= '0' && buffer[i+1] <= '9')
						buffer[i] = 0;
					nome[i] = toupper(buffer[i]);
				}
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
}


void EmpilharCertificado(Pilha *pilha, char *nome, int ch) 
{
	Certificado certificado;
	strcpy(certificado.nome, nome);
	certificado.ch = ch;
	pushPilha(pilha, certificado);
	
	printf("%s empilhou certificado de %d horas\n", certificado.nome, certificado.ch);

}



void RepassarCertificado(Pilha *pilha, Fila *fila, int certificados_a_repassar) 
{
	int certificados_repassados = 0;
	
	for (; certificados_repassados < certificados_a_repassar && !pilhaVazia(pilha) && !filaCheia(fila); certificados_repassados++)
	{
		pushFila(fila, popPilha(pilha));
	}

	printf("[%d] certificados repassados\n", certificados_repassados);

}



void ProcessarCertificado(Fila *fila, Node *sistema, int certificados_a_processar, int *alunos_no_sistema) 
{
	int certificados_processados = 0;

	for ( ; certificados_processados < certificados_a_processar && !filaVazia(fila); certificados_processados++) 
	{		
		RegistrarSistema(sistema, popFila(fila), alunos_no_sistema);
	}

	printf("[%d] certificados processados\n", certificados_processados);

}



void ValidarDisciplina (char *nome, Node *sistema) 
{
	unsigned long hashValue = djb2(nome);
	Node *aux = sistema + hashValue;
	
	while (strcmp(aux->certificado->nome, nome) != 0)
	{
		aux = aux->prox;
	}

	if (aux->certificado->ch >= 60)
	{
		aux->certificado->ch -= 60;
		printf("%s validou 60 horas\n", nome);
	}
	else printf("%s nao tem 60 horas regisradas\n", nome);
}



void ExibirSistema(Node *sistema, int *alunos_a_exibir, int chaning)
{
	Node *aux = sistema;

	if (*alunos_a_exibir <= 0) return;
	
	if (aux->certificado != NULL) 
	{	
		if (aux->certificado->ch > 0)	
		{
			printf("%s: %d horas totais\n", aux->certificado->nome, aux->certificado->ch); 
		
		}

		(*alunos_a_exibir)--;
		
		if (aux->prox != NULL) 
		{
			ExibirSistema(aux->prox, alunos_a_exibir, 1);
			
		}


	}
	
	if (chaning) return;

	else ExibirSistema(aux+1, alunos_a_exibir, 0);
}



int main() 
{

	char buffer[TAMANHO_BUFFER+1] = {0}; 
	char *parametros_ptr;
	char nome[TAMANHO_BUFFER_NOME] = {0};
	enum program_flag status = CONTINUE;
	int valor = 0;
	int alunos_no_sistema = 0;
	int alunos_a_exibir = 0;
	int restantes_na_pilha = 0;
	int restantes_na_fila = 0;
	int i;

	Pilha *pilha = cria_pilha();
	Fila *fila = cria_fila();
	Node sistema[100] = {0};


	while (status == CONTINUE) 
	{
		printf("> ");
		if (fgets(buffer, TAMANHO_BUFFER, stdin) == NULL) {
		    printf("erro ao ler entrada\n");
		    exit(EXIT_FAILURE);
		}

		buffer[strcspn(buffer, "\n")] = '\0'; 
		
		if (buffer[0] == 'c' || buffer[0] == 'd' || buffer[0] == 'v') 
		{
			for (i = 0; buffer[i] != ' '; i++);

			parametros_ptr = &buffer[i+1];
		}

		switch (buffer[0]) {
			
			case 'F':
				while (pilhaVazia(pilha) == 0) 
				{
					popPilha(pilha);
					restantes_na_pilha++;
				}
				while (filaVazia(fila) == 0) 
				{
					popFila(fila);
					restantes_na_fila++;
				}
				printf("sobraram %d certificados na pilha e sobraram %d certificados na fila\n", restantes_na_pilha, restantes_na_fila);
				status = TERMINATE;
				break;

			case 's':
				alunos_a_exibir = alunos_no_sistema;
				ExibirSistema(sistema, &alunos_a_exibir, 0);
				break;
			
			case 'c':
				if (buffer[1] == 'e')
				{
					if (pilhaCheia(pilha))
					{
						printf("pilha cheia\n");
						continue;
					}
					else
					{
						FormatarEntrada(parametros_ptr, CERTIFICADO, nome, &valor);
						EmpilharCertificado(pilha, nome, valor); 
					}
				}

				else if (buffer[1] == 'o')
				{
					FormatarEntrada(parametros_ptr, INTEIRO, nome, &valor);
					ProcessarCertificado(fila, sistema, valor, &alunos_no_sistema);		
				}

				break;


			case 'd':
				FormatarEntrada(parametros_ptr, INTEIRO, nome, &valor);
				RepassarCertificado(pilha, fila, valor);
				break;


			case 'v':
				FormatarEntrada(parametros_ptr, STRING, nome, &valor);
				ValidarDisciplina(nome, sistema);
				break;
			}
	}
	return 0;
}

