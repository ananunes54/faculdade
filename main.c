#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "PE.h"
#include "FD.h"
#include <ctype.h>

// AS ESTRUTURAS PARA CERTIFICADO E PARA NODE ESTÃO DEFINIDAS EM "NODE.h"
// TAMANHO_BUFFER_NOME, TAMANHO_BUFFER, TAMANHO_MAXIMO_PILHA, TAMANHO_MAXIMO_FILA, TAMANHO_SISTEMA ESTÃO DEFINIDOS EM "NODE.h"
// AS ESTRUTURAS PARA PILHAS E PARA FILAS ESTÃO DEFINIDAS EM SEUS RESPECTIVOS ARQUIVOS DE CABEÇALHO

enum program_flag { CONTINUE, TERMINATE };
enum parametrosDaFuncao { CERTIFICADO, INTEIRO, STRING };


// função hash que recebe um nome e retorna a posição de vetor associada a esse nome. as colisoes serão tratadas na função "Registrar Sistema"

unsigned long djb2(const char *input) 
{
	unsigned long hash = 5381;
	int c;
	while ((c = *input++))
	{
		hash = ((hash << 5) + hash) + c;
	}
	return hash%TAMANHO_SISTEMA;
}



// sistema: vetor de nodos onde os alunos são registrados
// certificado_fonte: cópia de um certificado retirado da fila, usado para inserir as informações dos alunos nos certificados do sistema
// alunos_no_sistema: alunos_no_sistema é uma variável definida dentro da main e que é utilizada como "variável de controle" em outras funções (ver: )

void RegistrarSistema(Node *sistema, Certificado certificado_fonte, int *alunos_no_sistema)
{
	unsigned long hashValue = djb2(certificado_fonte.nome);

	// aux é a posição associada a determinado aluno dentro do sistema 
	Node *aux = sistema + hashValue;

	// tratamento de colisões da função hash: implementado com lista ligada, itera até encontrar uma posição vazia 
	while (aux->certificado != NULL)
	{
		// dentro da lista ligada (caso tenha colisão associada ao valor do hash), verifica se o aluno já foi registrado no sistema 
		if (strcmp(certificado_fonte.nome, aux->certificado->nome) == 0)
		{
			aux->certificado->ch += certificado_fonte.ch;
			return;
		}

		// caso o aluno não tenha sido registrado, aloca um Nodo para ele 
		if (aux->prox == NULL)
		{
			aux->prox = (Node *)malloc(sizeof(Node));
			aux->prox->certificado = NULL;
			aux->prox->prox = NULL;
		}

		else aux = aux->prox;
	}

	Certificado *certificado = (Certificado *)malloc(sizeof(Certificado));
	
	// agora o ponteiro para certificado, dentro do nodo, aponta para um região de memória existente 
	aux->certificado = certificado;

	strcpy(certificado->nome, certificado_fonte.nome);
	certificado->ch = certificado_fonte.ch;
	
	*alunos_no_sistema += 1;
}



// buffer: é um ponteiro para a posição do vetor que armazena a entrada (função fgets localizada na main()) onde iniciam os parâmetros da função
// parametro: enumerador alterado dentro da main(), como se fosse uma flag, e que define para quais tipos de dados o buffer deve ser transformado
// nome e valor: variáveis definidas na main() para serem acessadas por outras função; são os dois possíveis tipos de parâmetros das funções; armazenam os dados obtidos através do tratamento do buffer
 
void FormatarEntrada(char *buffer, enum parametrosDaFuncao parametro, char *nome, int *valor) 
{
	// como são usadas após praticamente todas as entradas, devem ser inicializadas em 0 para evitar lixo de memória 
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
					// a menos que o próximo caractere seja um número, imprime buffer[i] na tela
					else putc(buffer[i], stdout);

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
	
	printf(" empilhou certificado de %d horas\n", certificado.ch);

}



void RepassarCertificado(Pilha *pilha, Fila *fila, int certificados_a_repassar) 
{
	int certificados_repassados = 0;
	
	for (; certificados_repassados < certificados_a_repassar && !pilhaVazia(pilha) && !filaCheia(fila); certificados_repassados++)
	{
		pushFila(fila, popPilha(pilha));
	}

	printf("%d certificados repassados\n", certificados_repassados);

}


// alunos_no_sistema: ponteiro para variavel definida na main() e que é necessária para a função "RegistrarSistema"
void ProcessarCertificado(Fila *fila, Node *sistema, int certificados_a_processar, int *alunos_no_sistema) 
{
	int certificados_processados = 0;

	for ( ; certificados_processados < certificados_a_processar && !filaVazia(fila); certificados_processados++) 
	{		
		RegistrarSistema(sistema, popFila(fila), alunos_no_sistema);
	}

	printf("%d certificados processados\n", certificados_processados);

}




void ValidarDisciplina (char *nome, Node *sistema) 
{
	// a função hash facilita a busca pelo aluno a ter sua carga horária alterada
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



// alunos a exibir: passado como ponteiro pois se trata de uma função recursiva que lida com dois tipos de "busca": o vetor do sistema e possíveis listas ligadas devido a colisões; se encontrada uma lista ligada, aprofunda na lista e depois retorna para incrementar uma posição no vetor do sistema
// chaining: "flag" que informa à função se está dentro de uma lista ligada (1) ou se está incrementando a posição no vetor (0)
void ExibirSistema(Node *sistema, int *alunos_a_exibir, int chaning)
{
	Node *aux = sistema;

	if (*alunos_a_exibir <= 0) return;

	// como os certificados são alocados diretamente na pilha, uma posição do sistema que não foi preenchida por um aluno, é uma posição com certificado nulo	
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

	// uso do else para impedir que tente acessar memória inválida (sistema->prox + 1, por exemplo, uma vez que sistema->prox indica que a função está executando dentro de uma lista ligada)
	else ExibirSistema(aux+1, alunos_a_exibir, 0);
}



// alunos_no_sistema: variável usada para controlar a quantidade de nodos restantes para liberar
// chaining: da mesma forma que na função "RegistrarSistema", pode ser que a função esteja liberando dentro de uma lista ligada 

void freeSistema(Node *sistema, int *alunos_no_sistema, int chaining)
{

	if (*alunos_no_sistema <= 0) return;

	if (sistema->certificado != NULL)
	{
		
		*alunos_no_sistema -= 1;
		free(sistema->certificado);
		sistema->certificado = NULL;
		if (sistema->prox == NULL && chaining) 
		{
			return;
		}

		else if (sistema->prox != NULL) 
		{
			freeSistema(sistema->prox, alunos_no_sistema, 1);
			sistema->prox = NULL;
			return;
		}
	}
	

	freeSistema(sistema+1, alunos_no_sistema, 0);
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
	Node sistema[TAMANHO_SISTEMA] = {0};


	while (status == CONTINUE) 
	{
		printf("> ");

		if (fgets(buffer, TAMANHO_BUFFER, stdin) == NULL) {
		    printf("erro ao ler entrada\n");
		    exit(EXIT_FAILURE);
		}

		// como a função fgets considera o '\n' da entrada, substitui por '\0'
		buffer[strcspn(buffer, "\n")] = '\0'; 
		
		// para as funções que recebem parâmetros, vai definir um ponteiro para a posição em que esses parâmetros começam
		if (buffer[0] == 'c' || buffer[0] == 'd' || buffer[0] == 'v') 
		{
			for (i = 0; buffer[i] != ' '; i++);

			parametros_ptr = &buffer[i+1];
		}


		switch (buffer[0]) {
			
			case 'F':
				status = TERMINATE;
				break;

			case 's':
				//como a função "ExibirSistema" altera a variável alunos_a_exibir, é preciso "reiniciá-la" a cada chamada da função sistema
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

	printf("sobraram %d certificados na pilha \nsobraram %d certificados na fila\n", restantes_na_pilha, restantes_na_fila);
	free(pilha);
	free(fila);
	freeSistema(sistema, &alunos_no_sistema, 0);
				
	return 0;
}

