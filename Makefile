all: JogoDaCobra

JogoDaCobra: main.o modos.o jogadas.o funcoes.o
	gcc -o JogoDaCobra main.o modos.o jogadas.o funcoes.o

funcoes.o: funcoes.c
	gcc -o funcoes.o -c funcoes.c -g -Wall
jogadas.o: jogadas.c
	gcc -o jogadas.o -c jogadas.c -g -Wall
modos.o: modos.c
	gcc -o modos.o -c modos.c -g -Wall

main.o: main.c modos.h jogadas.h funcoes.h
	gcc -o main.o -c main.c -g -Wall

clean:
	rm -f *.o
mrproper: clean
	rm -f JogoDaCobra
