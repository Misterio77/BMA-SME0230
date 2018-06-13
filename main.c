/*The Snake and The Hunter - IPC 2018


Gabriel Silva Fontes        10856803
Rafaela Delgado Nascimento  10818904
*/
#include <stdio.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>

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

#define RESET     "\x1b[0m"

/*Menu inicial*/
int main() {
	char jogar_novamente;
	char lixo[1000], modo;

	srand(time(NULL));

	do {
		printf("\e[1;1H\e[2J");
		printf("%s___          %s __              %s                                                  %s\n", CYAN, GREEN, CYAN, RESET);
		printf("%s |  |_   _   %s(_   _   _  |   _%s    _   _   _|   |_ |_   _   |__|      _  |_  _  _%s\n", CYAN, GREEN, CYAN, RESET);
		printf("%s |  | ) (-   %s__) | ) (_| |( (-%s   (_| | ) (_|   |_ | ) (-   |  | |_| | ) |_ (- | %s\n", CYAN, GREEN, CYAN, RESET);
		printf("%s             %s                 %s                                                  %s\n", CYAN, GREEN, CYAN, RESET);
		printf("Bem vindo! :3\n\n");
		printf("%s0 Jogadores%s: >   %sI.A. vs I.A.%s   < \n\n", MAGENTA, RESET, F_MAGENTA, RESET);
		printf("%s1 Jogador%s  : >  %sPlayer vs I.A.%s  < \n", CYAN, RESET, F_CYAN, RESET);
		printf("%s2 Jogadores%s: > %sPlayer vs Player%s < \n\n", YELLOW, RESET, F_YELLOW, RESET);
		printf("Digite o número de jogadores:\n");
		printf("Ou R, para ler as regras.\n");
		printf(">");
		scanf(" %c", &modo);
		modo = tolower(modo); //Deixar minúsculo
		fgets(lixo, 1000, stdin); //Ignora qualquer input extra que o usuário digitar

		if (modo == '0') alone();
		if (modo == '1') singleplayer();
		if (modo == '2') multiplayer();
		if (modo == 'r') {
			printf("\n\n");
			printf("O jogo consiste em 2 rodadas e é jogado em duplas,\n");
			printf("sendo um jogador a cobra, e o outro o caçador.\n");
			printf("As funções se invertem na segunda rodada, vencendo o\n");
			printf("jogador que mais pontuou quando teve sua vez de cobra. \n");
			printf("\n");
			printf("Nas rodadas, cada jogador se alterna fazendo lances e\n");
			printf("expandindo a cobra. A cobra atual deve tentar maximizar seu\n");
			printf("tamanho (portanto, sua pontuação), enquanto o caçador deve\n");
			printf("tentar evitar que a cobra se expanda, barrando possíveis\n");
			printf("jogadas da cobra, finalizando o jogo cedo.\n");
		}

		printf("\n\nRetornar ao menu? (Y/n)\n");
		printf(">");
		scanf("%c", &jogar_novamente);
		jogar_novamente = tolower(jogar_novamente); //Transformar maiúsculas em minúsculas
	} while (jogar_novamente != 'n');

	return(0);
}
