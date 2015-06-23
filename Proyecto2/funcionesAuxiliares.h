/*
 * funcionesAuxiliares.h
 * 
 * Descripción: Este archivo es la cabecera del archivo funcionesAuxiliares.c
 *
 * Autores: 
 * 	Br. Fernando Pérez, carné: 12-11152.
 * 	Br. Leslie Rodrigues, carné: 10-10613.
 *
 * Última modificación: 22-06-2015
 */
void leerArchivo(char *nombre);
int verificarConjunto(int numero, int arreglo[], int tamano);
void verificarArgumentos(int *n, int *m, char **salida,char **directorio, struct stat statbuf, int argc, char *argv[]);
void inicializarArreglo(int arreglo[], int tamano);
