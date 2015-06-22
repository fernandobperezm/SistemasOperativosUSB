default: main.o sistemaDeArchivos.o
	gcc -Wall -g -o MiCuento main.o sistemaDeArchivos.o
	make clean
main.o: main.c sistemaDeArchivos.h
	gcc -g -c main.c
sistemaDeArchivos.o: sistemaDeArchivos.c sistemaDeArchivos.h
	gcc -g -c sistemaDeArchivos.c -o sistemaDeArchivos.o
clean:
	rm -f *.o
	reset
