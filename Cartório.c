#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

/* 8 ~ 12: *Macros de pr�-processador. Elas servem para definir constantes simb�licas que representam valores espec�ficos! */

#define TAM_CPF 11  		//Define o tamanho m�ximo do campo de CPF, que deve ser de 11 caracteres (incluindo d�gitos e h�fens)
#define TAM_NOME 40  		//Define o tamanho m�ximo do campo de nome, que deve ser de at� 40 caracteres.
#define TAM_SOBRENOME 40	//Define o tamanho m�ximo do campo de sobrenome, que deve ser de at� 40 caracteres.
#define TAM_CARGO 40		//Define o tamanho m�ximo do campo de cargo, que deve ser de at� 40 caracteres.
#define TAM_LINHA 200		//Define o tamanho m�ximo de uma linha de texto que ser� lida ou escrita em um arquivo, que deve ser de at� 200 caracteres.


typedef struct {			/*Cria um novo tipo de dado estruturado para tornar o c�digo mais leg�vel e facilitar o gerenciamento de dados.*/

// typedef -> "Tipo definido pelo usu�rio" - Fun��o: Permite criar novos tipos de dados a partir de tipos j� existentes na linguagem ou de tipos personalizados.
// struct -> Define um tipo de dado composto que agrupa diversas vari�veis sob um �nico nome.

  char cpf[TAM_CPF];		/*cria��o de vari�veis/string */
  char nome[TAM_NOME];
  char sobrenome[TAM_SOBRENOME];
  char cargo[TAM_CARGO];
} Aluno;



int registro() {
  Aluno aluno;

  printf("Digite o CPF (apenas n�meros): ");	//coletando informa��o do usu�rio
  scanf("%s", aluno.cpf);

  printf("Digite o nome: ");
  scanf("%s", aluno.nome);

  printf("Digite o sobrenome: ");
  scanf("%s", aluno.sobrenome);

  printf("Digite o cargo: ");
  scanf("%s", aluno.cargo);

  /* Cria��o de arquivo */
  FILE *arquivo;						
  arquivo = fopen(aluno.cpf, "w");		
  
  

  if (arquivo == NULL) {
    printf("Erro ao abrir o arquivo!\n");
    return 1;
  }
  
  /* salvar o valor da variavel */
  fprintf(arquivo, "%s,%s,%s,%s\n", aluno.cpf, aluno.nome, aluno.sobrenome, aluno.cargo);
  fclose(arquivo);
  
  system("cls");
  printf("Registro salvo com sucesso!\n");
  system("pause");
  return 0;
}

int consulta() {
  setlocale(LC_ALL, "Portuguese");

  char cpf[TAM_CPF];
  char linha[TAM_LINHA];

  printf("Digite o CPF para consulta: ");
  scanf("%s", cpf);

  FILE *arquivo;
  arquivo = fopen(cpf, "r");

  if (arquivo == NULL) {
    printf("CPF n�o encontrado!\n");
    
  }

  
  while (fgets(linha, TAM_LINHA, arquivo)) {
  	printf("\nInforma��es do aluno:\n\n");
    char *dados[4];
    int i = 0;
    char *pch = strtok(linha, ","); 			//Esta linha declara uma vari�vel de ponteiro para caractere pch e a inicializa com o valor retornado pela fun��o strtok.
    
    /* A fun��o strtok:

    -> Divide uma string (linha) em tokens (substrings) com base em um delimitador (no caso, a v�rgula ",").
    -> Retorna um ponteiro para o primeiro token na primeira chamada e para os tokens subsequentes nas chamadas subsequentes.
    -> Retorna NULL quando n�o h� mais tokens na string. 
    
    	* pch armazena o endere�o de cada token extra�do da linha do arquivo.
	
	*/

    
    while (pch != NULL) {
      dados[i++] = pch;
      pch = strtok(NULL, ",");
    }

    printf("CPF: %s\n", dados[0]);
    printf("Nome: %s\n", dados[1]);
    printf("Sobrenome: %s\n", dados[2]);
    printf("Cargo: %s\n", dados[3]);
  }

  fclose(arquivo);
  system("pause");
  return 0;
}

int deletar() {
  char cpf[TAM_CPF];

  printf("Digite o CPF para deletar: ");
  scanf("%s", cpf);

  if (remove(cpf) == 0) {
  	
  	system("cls");
    printf("Registro exclu�do com sucesso!\n");
  } else {
  	system("cls");
    printf("Erro ao excluir o registro!\n");
  }

  system("pause");
  return 0;
}

int main() {
  int opcao;

  do {
    system("cls");

    setlocale(LC_ALL, "Portuguese");

    printf("### Sistema de Cadastro de Alunos ###\n\n");
    printf("Menu:\n");
    printf("1. Registro\n");
    printf("2. Consultar nomes\n");
    printf("3. Deletar nomes\n");
    printf("4. Sair\n");
    printf("\nDigite a op��o desejada: ");

    scanf("%d", &opcao);

    system("cls");	//respons�vel por limpar a tela

    switch (opcao) {	//in�cio da sele��o do menu
      case 1:
        registro();
        break;
      case 2:
        consulta();
        break;
      case 3:
        deletar();
        break;
      case 4:
        printf("\nSaindo do sistema...\n");
        break;
      default:
        printf("Op��o inv�lida!\n");
        system("pause");
        break;
    }
  } while (opcao != 4);

  return 0;
}

