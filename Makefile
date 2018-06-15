all: JogoDaCobra

JogoDaCobra: main.o modos.o jogadas.o funcoes.o
	gcc -o JogoDaCobra main.o modos.o jogadas.o funcoes.o

funcoes.o: funcoes.c
	gcc -o funcoes.o -c funcoes.c -W -Wall
jogadas.o: jogadas.c
	gcc -o jogadas.o -c jogadas.c -W -Wall
modos.o: modos.c
	gcc -o modos.o -c modos.c -W -Wall

main.o: main.c modos.h jogadas.h funcoes.h
	gcc -o main.o -c main.c -W -Wall

clean:
	rm -f *.o
mrproper: clean
	rm -f JogoDaCobra
