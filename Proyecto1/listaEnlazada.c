/*
 * listaEnlazada.c
 * 
 * Descripción: Este archivo contiene la definición y operaciones de una lista
 * doblemente enlazada. 
 *
 * Autores: 
 * 	Br. Fernando Pérez, carné: 12-11152.
 * 	Br. Leslie Rodrigues, carné: 10-10613.
 *
 * Última modificación: 21-05-2015.
 */
 
#include "listaEnlazada.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/*
 * LISTA es una lista enlazada que guarda un par de nombres, el número de amigos
 * de cada map, los amigos, y los comunes, además, la lista es doblemente enlazada,
 * por lo tanto, tiene apuntadores al siguiente nodo y al anterior.
 */ /*
typedef  struct lista {
    char *nombre[2];
    int nroAmigos[3];
    char **amigos1;
    char **amigos2;
    char **comunes;
    struct lista *sig;
    struct lista *ant;
} LISTA;
*/

/*
 * insertar es un procedimiento que añade una pregunta a la lista enlazada. 
 * La inserción se hace al final de la lista y se actualiza el puntero al último
 * elemento.
 * Argumentos: ultimo, es un apuntador a la última posición de la lista.
 * 			   nombre1, es una cadena de caracteres que representan al nombre del
 * 			   primer amigo.
 * 			   nombre2, es una cadena de caracteres que representan al nombre del
 * 			   segundo amigo.
 * Retorna: nada, las modificaciones las hace a la lista enlazada en memoria.
 */
void insertar(LISTA **ultimo,char *nombre1,char *nombre2){
    LISTA *nuevo;
    nuevo = (LISTA *) malloc(sizeof(LISTA));

    if (*ultimo != NULL)
        (*ultimo)->sig = nuevo;

    nuevo->nombre[0] = strdup(nombre1);
    nuevo->nombre[1] = strdup(nombre2);
    
    nuevo->ant = *ultimo;
    *ultimo = nuevo;
}


/*
 * Buscar es un procedimiento que itera sobre la lista enlazada buscando a una
 * tupla de nombres.
 * Argumentos: ultimo, es un apuntador a la última posición de la lista.
 * 			   nombre1, es una cadena de caracteres que representan al nombre del
 * 			   primer amigo.
 * 			   nombre2, es una cadena de caracteres que representan al nombre del
 * 			   segundo amigo.
 * Retorna: Un apuntador al nodo de la lista que contiene a la tupla, si esta
 * existe, en caso contrario, retorna NULL.
 */
LISTA **buscar(LISTA **ultimo, char *nombre1, char *nombre2){
    LISTA **list;
    list = ultimo;

    while(*list != NULL){
        if (!strcmp(((*list)->nombre[0]),nombre1)){ 
            if(!strcmp(((*list)->nombre[1]), nombre2)){
                return list;
            }
        }
        list = &(*list)->ant;
    }
    return NULL;
}

/*
 * destruirLista es un procedimiento que destruye la lista previamente creada.
 * Esto para liberar memoria.
 * Argumentos: ultimo, es un apuntador a la última posición de la lista.
 * Retorna: nada, las modificaciones las hace a la lista enlazada en memoria.
 */
void destruirLista(LISTA **ultimo){
	while(*ultimo != NULL){
		free((*ultimo)->nombre[0]);
		free((*ultimo)->nombre[1]);
		free((*ultimo)->nombre);
		free((*ultimo)->amigos1);
		free((*ultimo)->amigos2);
		free((*ultimo)->comunes);
		(*ultimo)->sig = NULL;
		
		if(((*ultimo)->ant != NULL)){
			*ultimo = (*ultimo)->ant;
			(*ultimo)->sig->ant = NULL; 
		}
		else
			*ultimo = NULL;
	}
}
