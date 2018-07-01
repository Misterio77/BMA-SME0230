all: JogoDaCobra

JogoDaCobra: main.o modos.o jogadas.o funcoes.o
	gcc -o JogoDaCobra main.o modos.o jogadas.o funcoes.o

funcoes.o: src/funcoes.c
	gcc -o funcoes.o -c src/funcoes.c -g -Wall
jogadas.o: src/jogadas.c
	gcc -o jogadas.o -c src/jogadas.c -g -Wall
modos.o: src/modos.c
	gcc -o modos.o -c src/modos.c -g -Wall

main.o: src/main.c src/modos.h src/jogadas.h src/funcoes.h
	gcc -o main.o -c src/main.c -g -Wall

clean:
	rm -f *.o
mrproper: clean
	rm -f JogoDaCobra
