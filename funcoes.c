/*The Snake and The Hunter - IPC 2018


Gabriel Silva Fontes        10856803
Rafaela Delgado Nascimento  10818904
*/
#include <stdio.h>
#include <ctype.h>

#include "funcoes.h"


/*Definimos nomes para códigos de cores.
  Assim, podemos utilizá-los de forma mais prática.
*/

#define RED      "\x1b[31m"
#define GREEN    "\x1b[32m"
#define YELLOW   "\x1b[33m"
#define BLUE     "\x1b[34m"
#define MAGENTA  "\x1b[35m"
#define CYAN     "\x1b[36m"

#define F_RED     "\x1b[41m"
#define F_GREEN   "\x1b[42m"
#define F_YELLOW  "\x1b[43m"
#define F_BLUE    "\x1b[44m"
#define F_MAGENTA "\x1b[45m"
#define F_CYAN    "\x1b[46m"

#define RESET   "\x1b[0m"

/*Imprime o campo
*/
void imprimir_campo(int risco_x[7][7], int risco_y[7][7]) {
	int cont_x,cont_y;
	printf("\e[1;1H\e[2J"); //Magia pra limpar a tela.

	//Imprime moldura superior (Com colunas enumeradas)
	printf("%s    1  2  3  4  5  6  7    %s\n", F_CYAN, RESET);
	//Imprime uma linha em branco com molduras laterais
	printf("%s  %s                       %s  %s\n", F_CYAN, RESET, F_CYAN, RESET);

	//Repetir para todas as linhas
	//O campo é impresso alternando entre linhas com e sem bolinhas
	for (cont_y = 0;cont_y < 7;cont_y++){
		//Imprime a moldura do lado esquerdo (Com linhas enumeradas)
		printf("%s %i%s  ", F_CYAN, cont_y+1, RESET);

		//Esse for serve para imprimir bolinhas e riscos horizontais
		//Repetir para todas as colunas
		for (cont_x = 0;cont_x < 7;cont_x++) {
			//Coloca as bolinhas
			printf("%so%s", CYAN, RESET);
			//Imprimir um risco horizontal (Ou espaço, caso ele não exista)
			if (risco_x[cont_x][cont_y] == 0) {
				printf("  ");
			}
			else if (risco_x[cont_x][cont_y] == 1) {
				printf("==");
			}
			else { //Imprimimos diferente caso seja a última jogada feita
				printf("--");
			}
		}
		//Imprimir moldura do lado direito
		printf("%s  %s\n", F_CYAN, RESET);

		//Imprimir moldura do lado esquerdo (Sem numeros)
		printf("%s  %s  ", F_CYAN, RESET);
		
		//Esse for serve para imprimir espaço entre linhas e riscos verticais
		//Repetir para todas as colunas
		for (cont_x = 0;cont_x < 7;cont_x++) {
			//Imprimir um risco vertical (Ou espaço, caso ele não exista)
			if (risco_y[cont_x][cont_y] == 0) {
				printf(" ");
			}
			else if (risco_y[cont_x][cont_y] == 1) {
				printf("|");
			}
			else {
				printf(":");
			}
			//Espaçamento
			printf("  ");
		}
		//Imprimir moldura do lado direito
		printf("%s  %s\n", F_CYAN, RESET);
	}

	//Imprimir moldura abaixo, e pular linhas
	printf("%s                           %s\n\n", F_CYAN, RESET);
}

/*Reinicia as jogadas
*/
void reiniciar_campo(int risco_x[7][7], int risco_y[7][7]) {
	int cont_x, cont_y;	
	for (cont_x = 0;cont_x < 7;cont_x++) {
		for (cont_y = 0;cont_y < 7;cont_y++) {
			risco_x[cont_x][cont_y] = 0;
			risco_y[cont_x][cont_y] = 0;
		}
	}
}

/*Verifica quantos adjacentes uma dada casa tem
  Contabiliza e retorna essa quantidade.

  Utilizamos essa função pra verificar se uma jogada começa na
  ponta da cobra (1 adjacente), e se tem como destino uma casa não conectada (0 adjacentes)
*/
int verificar_adjacentes(jogada coord, int risco_x[7][7], int risco_y[7][7]) {
	int adjacentes = 0;

	//Verificar casa acima
	if (risco_y[(coord).x-1][(coord).y-2] != 0 && (coord).y > 1) {
		adjacentes++;
	}

	//Verificar casa abaixo
	if (risco_y[(coord).x-1][(coord).y-1] != 0 && (coord).y < 7) {
		adjacentes++;
	}

	//Verificar casa à direita
	if (risco_x[(coord).x-1][(coord).y-1] != 0 && (coord).x < 7) {
		adjacentes++;

	}

	//Verificar casa à esquerda
	if (risco_x[(coord).x-2][(coord).y-1] != 0 && (coord).x > 1) {
		adjacentes++;
	}

	//Retornar a quantidade de adjacentes.
	return(adjacentes);
}

/*Verifica se uma jogada é válida.
  Argumentos: Coordenadas, e número do lance da rodada.
  Além disso, a variável erro oculta as mensagens de erro caso ela seja chamada como 0.
  Retorna 0 caso a jogada seja feita com sucesso, e 1 caso seja inválida.
*/
int verificar_jogada(jogada coord, int lances, int erros, int risco_x[7][7], int risco_y[7][7]) {

	//Verificar se a casa dada existe (1-7)
	if ((coord).x < 1 || (coord).x > 7 || (coord).y < 1 || (coord).y > 7) {
		if (erros) printf("%sErro! Digite apenas números entre 1 e 7!%s\n", F_RED, RESET);
		return(1);
	}

	//Verificar se a direção é valida (Apenas c, b, d ou e)
	if ((coord).d != 'w' && (coord).d != 's' && (coord).d != 'd' && (coord).d != 'a') {
		if (erros) printf("%sErro! Digite uma direção válida!%s\n", F_RED, RESET);
		return(1);
	}

	//Verificar se a casa destino não ultrapassa o campo
	if ((coord).d == 'w'&& (coord).y == 1) {
		if (erros) printf("%sErro! Não existe casa acima.%s\n", F_RED, RESET);
		return(1);
	}
	if ((coord).d == 's'&& (coord).y == 7) {
		if (erros) printf("%sErro! Não existe casa abaixo.%s\n", F_RED, RESET);
		return(1);
	}
	if ((coord).d == 'd'&& (coord).x == 7) {
		if (erros) printf("%sErro! Não existe casa à direita.%s\n", F_RED, RESET);
		return(1);
	}
	if ((coord).d == 'a'&& (coord).x == 1) {
		if (erros) printf("%sErro! Não existe casa à esquerda.%s\n", F_RED, RESET);
		return(1);
	}

	//Verificar se a casa inicial dada está na extremidade da cobra
	//Ou seja, se ela tem exatamente 1 risco adjacente
	if (lances != 0) { //Não verificar caso seja a primeira jogada do round
		if (verificar_adjacentes(coord, risco_x, risco_y) != 1) {
			if (erros) printf("%sErro! Escolha uma casa nas extremidades da cobra.%s\n", F_RED, RESET);
			return(1);
		}
	}

	//Verificar se a casa destino não faz parte da cobra
	//Ou seja, se ela tem exatamente 0 riscos adjacentes.
	if ((coord).d == 'w') {
		(coord).y--;
		if (verificar_adjacentes(coord, risco_x, risco_y) != 0) {
			if (erros) printf("%sErro! A casa acima não está livre.%s\n", F_RED, RESET);
			return(1);
		}
	}
	else if ((coord).d == 's') {
		(coord).y++;
		if (verificar_adjacentes(coord, risco_x, risco_y) != 0) {
			if (erros) printf("%sErro! A casa abaixo não está livre.%s\n", F_RED, RESET);
			return(1);
		}
	}
	else if ((coord).d == 'd') {
		(coord).x++;
		if (verificar_adjacentes(coord, risco_x, risco_y) != 0) {
			if (erros) printf("%sErro! A casa à direita não está livre.%s\n", F_RED, RESET);
			return(1);
		}
	}
	else if ((coord).d == 'a') {
		(coord).x--;
		if (verificar_adjacentes(coord, risco_x, risco_y) != 0) {
			if (erros) printf("%sErro! A casa à esquerda não está livre.%s\n", F_RED, RESET);
			return(1);
		}
	}

	//Caso todas as verificações passem, retornar 0.
	return(0);
}

/*Realiza a jogada, utilizando dadas coordenadas e direção.
  Alterando os vetores que ditam o campo.
*/
void realizar_jogada(jogada coord, int risco_x[7][7], int risco_y[7][7]) {
	int cont_x, cont_y;	

	//Nesse for trocamos o valor da jogada 2 para 1, para que não seja
	//mais mostrada de forma destacada (Já que não é mais a última jogada)
	for (cont_x = 0;cont_x < 7;cont_x++) {
		for (cont_y = 0;cont_y < 7;cont_y++) {
			if (risco_x[cont_x][cont_y] == 2) risco_x[cont_x][cont_y] = 1;
			if (risco_y[cont_x][cont_y] == 2) risco_y[cont_x][cont_y] = 1;
		}
	}

	if ((coord).d == 'w') {
		//Guardar no vetor de riscos verticais, acima da posição
		//Ex: Jogada '5 5 c' equivale a risco_y[4][3]
		risco_y[(coord).x-1][(coord).y-2] = 2;
	}
	else if ((coord).d == 's') {
		//Guardar no vetor de riscos verticais, abaixo da posição
		//Ex: Jogada '5 5 b' equivale a risco_y[4][4]
		risco_y[(coord).x-1][(coord).y-1] = 2;
	}
	else if ((coord).d == 'd') {
		//Guardar no vetor de riscos horizontais, à direita da posição
		//Ex: Jogada '5 5 d' equivale a risco_x[4][4]
		risco_x[(coord).x-1][(coord).y-1] = 2;
	}
	else if ((coord).d == 'a') {
		//Guardar no vetor de riscos horizontais, à esquerda da posição
		//Ex: Jogada '5 5 e' equivale a risco_x[3][4]
		risco_x[(coord).x-2][(coord).y-1] = 2;
	}


	/*Nota 1:
	  Sempre removemos 1 das jogadas, para que o jogador possa lidar
	  com números de 1 à 7, ao invés de 0 à 6.

	  Nota 2:
	  Fazemos um "deslocamento" dependendo da direção, pois nossos
	  arrays que guardam jogadas equivalem aos espaços, não às bolinhas.
	  Dessa forma, duas jogadas, por exemplo, '5 5 c' e '5 4 b'
	  marcam o mesmo espaço. Por isso, podemos impedir jogadas repetidas.
	*/

	return;
}

/*Verifica se ainda existem jogadas possíveis
  Ao encontrar uma, retorna 0
  Caso contrário, retorna 1.
*/
int verificar_fim(int risco_x[7][7], int risco_y[7][7]) {
	jogada coord;
	int cont;
	
	(coord).d = 'd';
		
	//Verificar todas as jogadas, incrementando as coordenadas.
	for (cont = 0; cont < 4; cont++) {
		for ((coord).x = 1; (coord).x <= 7; (coord).x++) {
			for ((coord).y = 1; (coord).y <= 7; (coord).y++) {
				//Caso encontre uma 1 jogada válida, retornar 0
				if (verificar_jogada(coord, 1, 0, risco_x, risco_y) == 0) {
					return(0);
				}
			}
		}
		//Loopear (coord).d
		if      ((coord).d == 'd') (coord).d = 'w';
		else if ((coord).d == 'w') (coord).d = 'a';
		else if ((coord).d == 'a') (coord).d = 's';
		else if ((coord).d == 's') (coord).d = 'd';
	}

	//Caso nenhuma jogada seja válida, retornar 1
	return(1);
}
