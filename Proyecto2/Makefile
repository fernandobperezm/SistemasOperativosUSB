#
# Makefile
#
# Archivo de make para compilar y limpiar los directorios del proyecto.
#
# Autores:
#	Br. Fernando Pérez, carné: 12-11152.
# 	Br. LeslieRodrigues, carné: 10-10613.
#
# Última modificación: 22-06-2015.
#

#Definimos nuestras variables.
CC := gcc
MODULOS := main.o funcionesAuxiliares.o

default: $(MODULOS)
	$(CC) -Wall -o MiCuento $(MODULOS)
	make clean
main.o: main.c funcionesAuxiliares.h
	$(CC) -c main.c -o main.o
funcionesAuxiliares.o: funcionesAuxiliares.c funcionesAuxiliares.h
	$(CC) -c funcionesAuxiliares.c -o funcionesAuxiliares.o
clean:
	rm -f *.o
	reset
