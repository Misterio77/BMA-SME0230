/*The Snake and The Hunter - IPC 2018


Gabriel Silva Fontes        10856803
Rafaela Delgado Nascimento  10818904
*/
#include <stdio.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>
 #include<unistd.h> 

#include "modos.h"
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

/*Jogada humana interativa
  Recebe como argumentos o número do Jogador (1 ou 2),
  número do lance e número da rodada (1 ou 2).
*/
void jogada_interativa(int jogador, int rodada, int lances, int risco_x[7][7], int risco_y[7][7]) {
	jogada coord;
	int  sucesso;
	char lixo[1000];

	if (lances == 0) {
		printf("Rodada: %i\n", rodada);    //Imprimir rodada atual
		printf("Lance: %i\n\n", lances+1); //Imprimir lance atual

		if (jogador == 1) printf("%sJogador 1 é a cobra!%s \n", F_BLUE,  RESET);
		if (jogador == 2) printf("%sJogador 2 é a cobra!%s \n", F_YELLOW, RESET);
		printf("\n...\n\n");
		sleep(1);
	}

	do {

		imprimir_campo(risco_x, risco_y);
		printf("Rodada: %i\n", rodada);
		printf("Lance: %i\n\n", lances+1);
		if (jogador == 1) printf("%sJogador 1%s, sua vez! \n", F_BLUE,  RESET);
		if (jogador == 2) printf("%sJogador 2%s, sua vez! \n", F_YELLOW, RESET);

		printf("Digite as duas coordenadas %sx%s e %sy%s do ponto inicial da jogada (1-7).\n", GREEN, RESET, GREEN, RESET);

		printf(">");
		scanf("%i %i", &coord.x, &coord.y); //Receber coordenadas
		getchar();

		printf("E agora, a %sdireção%s do traçado.\n", GREEN, RESET);
		printf("(Utilize WASD.)\n");

		printf(">");
		scanf(" %c", &(coord).d); //Receber direção
		(coord).d = tolower((coord).d); //Transformar maiúsculas em minúsculas

		fgets(lixo, 1000, stdin); //Ignora input após o primeiro caractere
		printf("\n");

		//Verificar a jogada, e guardar em uma variável
		sucesso = verificar_jogada(coord, lances, 1, risco_x, risco_y);

		if (sucesso == 1) {
			printf("\n...\n\n");
			sleep(4);
		}
	} while (sucesso); //Repetir a verificação, até que seja válida (Quando retornar 0)

	//Fazer a jogada
	realizar_jogada(coord, risco_x, risco_y);

}

/*Jogada automatica do computador
  Recebe como argumentos o número do Jogador (1 ou 2),
  número do lance e número da rodada (1 ou 2).*/

void jogada_automatica(int jogador, int rodada, int lances, int risco_x[7][7], int risco_y[7][7]) {
	jogada coord;
	int aleatorio_x, aleatorio_y, aleatorio_d;

	//Avisar quem é a cobra, caso seja o primeiro lance
	if (lances == 0) {
		printf("Rodada: %i\n", rodada);    //Imprimir rodada atual
		printf("Lance: %i\n\n", lances+1); //Imprimir lance atual
		if (jogador == 1) printf("%sJogador 1 (PC) é a cobra!%s \n", F_BLUE,  RESET);
		if (jogador == 2) printf("%sJogador 2 (PC) é a cobra!%s \n", F_YELLOW, RESET);
		printf("\n...\n\n");
		sleep(1);
	}

	imprimir_campo(risco_x, risco_y);
	printf("Rodada: %i\n", rodada);
	printf("Lance: %i\n\n", lances+1);
	if (jogador == 1) printf("É a vez do computador (%sJogador 1%s)! \n", F_BLUE,  RESET);
	if (jogador == 2) printf("É a vez do computador (%sJogador 2%s)! \n", F_YELLOW, RESET);

	//Fazer a jogada
	if (lances == 0) {
		coord.x = 4;
		coord.y = 4;
		coord.d = 's';
	}
	
	else {
		do {
			aleatorio_x = 1 + (rand() % (7));
			aleatorio_y = 1 + (rand() % (7));
			aleatorio_d = 1 + (rand() % (4));

			coord.x = aleatorio_x;
			coord.y = aleatorio_y;

			if (aleatorio_d == 1) {
				coord.d = 'a';
			}
			else if (aleatorio_d == 2) {
				coord.d = 'w';
			}
			else if (aleatorio_d == 3) {
				coord.d = 'd';
			}
			else {
				coord.d = 's';
			}
		} while (verificar_jogada(coord, lances, 0, risco_x, risco_y));
	}

	//Fazer a jogada
	realizar_jogada(coord, risco_x, risco_y);

}

void ganhador(int pontos_1, int pontos_2) {
	printf("\e[1;1H\e[2J");
	printf("%s___          %s __              %s                                                  %s\n", CYAN, GREEN, CYAN, RESET);
	printf("%s |  |_   _   %s(_   _   _  |   _%s    _   _   _|   |_ |_   _   |__|      _  |_  _  _%s\n", CYAN, GREEN, CYAN, RESET);
	printf("%s |  | ) (-   %s__) | ) (_| |( (-%s   (_| | ) (_|   |_ | ) (-   |  | |_| | ) |_ (- | %s\n", CYAN, GREEN, CYAN, RESET);
	printf("%s             %s                 %s                                                  %s\n", CYAN, GREEN, CYAN, RESET);
	if (pontos_1 > pontos_2) {
		printf("Jogador 1 venceu!\n");
	}
	else if (pontos_2 > pontos_1) {
		printf("Jogador 2 venceu!\n");
	}
	else {
		printf("Empate!\n");
	}
	printf("\nPontuação:\n");
	printf("%s%i%s x %s%i%s\n", CYAN, pontos_1, RESET, GREEN, pontos_2, RESET);
	printf("\n");
}

/*Rodará o modo para 1 jogador.*/
void singleplayer() {
	int risco_x[7][7], risco_y[7][7];
	/*As variáveis risco_x e risco_y guardam, respectivamente, os espaços
	  horizontais e verticais entre as bolinhas.
	  O valor 0 significa vazio, valor 1 significa um traçado e o valor 2
	  significa a última jogada feita (Assim, mostramos de forma destacada)
	*/
	int pontos_1, pontos_2, lances;
	
	//Rodada 1 ==========
	lances = 0;
	reiniciar_campo(risco_x, risco_y);
	imprimir_campo(risco_x, risco_y);

	//Loopear pelas jogadas, quebrar quando não houver válidas
	do {
		jogada_interativa(1, 1, lances, risco_x, risco_y);
		lances++;
		if (verificar_fim(risco_x, risco_y)) break;
		
		jogada_automatica(2, 1, lances, risco_x, risco_y);
		printf("\n...\n\n");
		sleep(1);
		lances++;
		if (verificar_fim(risco_x, risco_y)) break;
		
	} while (1);

	imprimir_campo(risco_x, risco_y);
	//Guardar nro de lances na pontuação do jogador 1
	pontos_1 = lances;
	
	printf("%sFim da rodada 1.%s\n", F_MAGENTA, RESET);
	printf("Jogador 1 marcou %s%i%s pontos!\n", GREEN, lances, RESET);
	printf("\n...\n\n");
	sleep(1);
	
	//Rodada 2 ==========
	lances = 0;

	reiniciar_campo(risco_x, risco_y);
	imprimir_campo(risco_x, risco_y);

	//Loopear pelas jogadas, quebrar quando não houver válidas
	do {
		jogada_automatica(2, 2, lances, risco_x, risco_y);
		printf("\n...\n\n");
		sleep(1);
		lances++;
		if (verificar_fim(risco_x, risco_y)) break;
		
		jogada_interativa(1, 2, lances, risco_x, risco_y);
		lances++;
		if (verificar_fim(risco_x, risco_y)) break;
		
	} while (1);

	imprimir_campo(risco_x, risco_y);
	//Guardar nro de lances na pontuação do jogador 2
	pontos_2 = lances;
	
	printf("%sFim da rodada 2.%s\n", F_MAGENTA, RESET);
	printf("Jogador 2 marcou %s%i%s pontos!\n", GREEN, lances, RESET);
	printf("\n...\n\n");
	sleep(1);

	//Fim do jogo ================

	ganhador(pontos_1, pontos_2);
}

/*Roda o modo para 2 jogadores.*/
void multiplayer() {
	int risco_x[7][7], risco_y[7][7];
	/*As variáveis risco_x e risco_y guardam, respectivamente, os espaços
	  horizontais e verticais entre as bolinhas.
	  O valor 0 significa vazio, valor 1 significa um traçado e o valor 2
	  significa a última jogada feita (Assim, mostramos de forma destacada)
	*/
	int pontos_1, pontos_2, lances;
	
	//Rodada 1 ==========
	lances = 0;
	reiniciar_campo(risco_x, risco_y);
	imprimir_campo(risco_x, risco_y);

	//Loopear pelas jogadas, quebrar quando não houver válidas
	do {
		jogada_interativa(1, 1, lances, risco_x, risco_y);
		lances++;
		if (verificar_fim(risco_x, risco_y)) break;
		
		jogada_interativa(2, 1, lances, risco_x, risco_y);
		lances++;
		if (verificar_fim(risco_x, risco_y)) break;
		
	} while (1);

	imprimir_campo(risco_x, risco_y);
	//Guardar nro de lances na pontuação do jogador 1
	pontos_1 = lances;
	
	printf("%sFim da rodada 1.%s\n", F_MAGENTA, RESET);
	printf("Jogador 1 marcou %s%i%s pontos!\n", GREEN, lances, RESET);
	printf("\n...\n\n");
	sleep(1);
	
	//Rodada 2 ==========
	lances = 0;

	reiniciar_campo(risco_x, risco_y);
	imprimir_campo(risco_x, risco_y);

	//Loopear pelas jogadas, quebrar quando não houver válidas
	do {
		jogada_interativa(2, 2, lances, risco_x, risco_y);
		lances++;
		if (verificar_fim(risco_x, risco_y)) break;
		
		jogada_interativa(1, 2, lances, risco_x, risco_y);
		lances++;
		if (verificar_fim(risco_x, risco_y)) break;
		
	} while (1);

	imprimir_campo(risco_x, risco_y);
	//Guardar nro de lances na pontuação do jogador 2
	pontos_2 = lances;
	
	printf("%sFim da rodada 2.%s\n", F_MAGENTA, RESET);
	printf("Jogador 2 marcou %s%i%s pontos!\n", GREEN, lances, RESET);
	printf("\n...\n\n");
	sleep(1);

	//Fim do jogo ================

	ganhador(pontos_1, pontos_2);
}

/*Roda o modo para 0 jogadores.*/
void alone() {
	int risco_x[7][7], risco_y[7][7];
	/*As variáveis risco_x e risco_y guardam, respectivamente, os espaços
	  horizontais e verticais entre as bolinhas.
	  O valor 0 significa vazio, valor 1 significa um traçado e o valor 2
	  significa a última jogada feita (Assim, mostramos de forma destacada)
	*/
	int pontos_1, pontos_2, lances;
	char lixo[1000];
	
	//Rodada 1 ==========
	lances = 0;
	reiniciar_campo(risco_x, risco_y);
	imprimir_campo(risco_x, risco_y);

	//Loopear pelas jogadas, quebrar quando não houver válidas
	do {
		jogada_automatica(1, 1, lances, risco_x, risco_y);
		printf("\n...\n\n");
		sleep(1);
		lances++;
		if (verificar_fim(risco_x, risco_y)) break;

		jogada_automatica(2, 1, lances, risco_x, risco_y);
		printf("\n...\n\n");
		sleep(1);
		lances++;
		if (verificar_fim(risco_x, risco_y)) break;
		
	} while (1);

	imprimir_campo(risco_x, risco_y);
	//Guardar nro de lances na pontuação do jogador 1
	pontos_1 = lances;
	
	printf("%sFim da rodada 1.%s\n", F_MAGENTA, RESET);
	printf("Jogador 1 marcou %s%i%s pontos!\n", GREEN, lances, RESET);
	printf("\n...\n\n");
	sleep(1);
	
	//Rodada 2 ==========
	lances = 0;

	reiniciar_campo(risco_x, risco_y);
	imprimir_campo(risco_x, risco_y);

	//Loopear pelas jogadas, quebrar quando não houver válidas
	do {
		jogada_automatica(2, 2, lances, risco_x, risco_y);
		printf("\n...\n\n");
		sleep(1);
		lances++;
		if (verificar_fim(risco_x, risco_y)) break;
		
		jogada_automatica(1, 2, lances, risco_x, risco_y);
		printf("\n...\n\n");
		sleep(1);
		lances++;
		if (verificar_fim(risco_x, risco_y)) break;
		
	} while (1);

	imprimir_campo(risco_x, risco_y);
	//Guardar nro de lances na pontuação do jogador 2
	pontos_2 = lances;
	
	printf("%sFim da rodada 2.%s\n", F_MAGENTA, RESET);
	printf("Jogador 2 marcou %s%i%s pontos!\n", GREEN, lances, RESET);
	printf("(Aperte enter para continuar)\n");
	fgets(lixo, 1000, stdin); //Ignora qualquer input extra que o usuário digitar

	//Fim do jogo ================

	ganhador(pontos_1, pontos_2);
}