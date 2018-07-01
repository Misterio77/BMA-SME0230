/*The Snake and The Hunter - IPC 2018


Gabriel Silva Fontes        10856803
Rafaela Delgado Nascimento  10818904
*/
#ifndef FUNCOES_H_
#define FUNCOES_H_

typedef struct _jogada {
	int x;
	int y;
	char d;
} jogada;

void imprimir_campo(int risco_x[7][7], int risco_y[7][7]);
void reiniciar_campo(int risco_x[7][7], int risco_y[7][7]);
int verificar_adjacentes(jogada coord, int risco_x[7][7], int risco_y[7][7]);
int verificar_jogada(jogada coord, int lances, int erros, int risco_x[7][7], int risco_y[7][7]);
void realizar_jogada(jogada coord, int risco_x[7][7], int risco_y[7][7]);
int verificar_fim(int risco_x[7][7], int risco_y[7][7]);
void ganhador(int pontos_1, int pontos_2);

#endif
