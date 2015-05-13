main: main.o bases.o listaEnlazada.o
	gcc -Wall -o PROGRAMA main.o bases.o listaEnlazada.o
main.o: main.c bases.h listaEnlazada.h
	gcc -c main.c
bases.o: bases.c bases.h listaEnlazada.h
	gcc -c bases.c
listaEnlazada.o: listaEnlazada.c listaEnlazada.h
	gcc -c listaEnlazada.c -o listaEnlazada.o

