all: sokoban

sokoban : main.o partie.o affichage.o
	gcc main.o partie.o affichage.o -o sokoban

main.o: main.c partie.h
	gcc -c main.c

partie.o: partie.c affichage.h
	gcc -c partie.c

affichage.o: affichage.c struct.h
	gcc -c affichage.c