default: main.o listaEnlazada.o
	gcc -Wall --debug -DTEST -o preguntas main.o listaEnlazada.o
main.o: enteros.c listaEnlazada.h
	gcc --debug -DTEST -c enteros.c -o main.o
listaEnlazada.o: listaEnlazada.c listaEnlazada.h
	gcc --debug -DTEST -c listaEnlazada.c -o listaEnlazada.o
clean:
	rm -f *.o
