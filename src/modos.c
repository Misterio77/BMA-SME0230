/*The Snake and The Hunter - IPC 2018


Gabriel Silva Fontes        10856803
Rafaela Delgado Nascimento  10818904
*/
#include <stdio.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h> 

#include "jogadas.h"
#include "funcoes.h"
#include "modos.h"

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
	printf("\n...\n\n");
	sleep(1);

	//Fim do jogo ================

	ganhador(pontos_1, pontos_2);
}
