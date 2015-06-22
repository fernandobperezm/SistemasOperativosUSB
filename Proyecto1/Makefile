default: mainProcesos.o mainHilos.o listaEnlazada.o
	gcc -Wall -g -o friendfindP mainProcesos.o listaEnlazada.o
	gcc -Wall -g -o friendfindH mainHilos.o -lpthread listaEnlazada.o 
	make clean
mainProcesos.o: mainProcesos.c listaEnlazada.h
	gcc -g -c mainProcesos.c
mainHilos.o: mainHilos.c listaEnlazada.h
	gcc -g -c mainHilos.c -lpthread
listaEnlazada.o: listaEnlazada.c listaEnlazada.h
	gcc -g -c listaEnlazada.c -o listaEnlazada.o
clean:
	rm -f *.o
	reset
