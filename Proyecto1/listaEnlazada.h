/**
 * listaEnlazada.h
 * 
 * Descripción: Este es el archivo cabecera para listaEnlazada.c
 * 
 * Autores: 
 * 	Br. Fernando Pérez, carné: 12-11152.
 * 	Br. Leslie Rodrigues, carné: 10-10613.
 *
 * Última modificación: 27-04-2015.
 */

enum NivelDeComplejidad {basico, intermedio, avanzado};

typedef struct persona{
    char *nombre;
    char **amigos;
} PERSONA;

typedef  struct lista {
    PERSONA usuario;
    struct lista *sig;
    struct lista *ant;
} LISTA;


void insertar(LISTA **ultimo, PERSONA p);
LISTA **buscar(LISTA **ultimo, char *nombre);
int eliminar(LISTA **list, int *nombre);
