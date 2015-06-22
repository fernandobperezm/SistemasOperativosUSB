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

typedef struct pregunta{
    int codigo;
    char area;
    enum NivelDeComplejidad complejidad;
    char strings[4][100];
    int respuestaCorrecta;
} PREGUNTA;

typedef  struct lista {

    PREGUNTA preg;
    struct lista *sig;
    struct lista *ant;

} LISTA;

void insertar(LISTA **ultimo, PREGUNTA pregunta);
LISTA **buscar(LISTA **ultimo, int codigo);
int eliminar(LISTA **list, int codigo);
