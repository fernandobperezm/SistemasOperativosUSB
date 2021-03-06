/**
 * listaEnlazada.c
 * 
 * Descripción: Este archivo contiene las funciones y procedimientos principales
 * para la definición del tipo LISTA y PREGUNTA, así como sus atributos.
 * 
 * Autores: 
 * 	Br. Fernando Pérez, carné: 12-11152.
 * 	Br. Leslie Rodrigues, carné: 10-10613.
 *
 * Última modificación: 27-04-2015.
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

/*
 * NivelDeComplejidad es un tipo enumerado que representa la complejidad de 
 * las preguntas.
 * basico -> 0.
 * intermedio -> 1.
 * avanzado -> 2.
 */
enum NivelDeComplejidad {basico, intermedio, avanzado};

/*
 * PREGUNTA es un tipo de datos apoyado en la estructura pregunta. Modela
 * el esquema de preguntas que se estarán manejando en los archivos y en las
 * listas enlazadas.
 * Atributos: codigo, entero que representa a la pregunta unívocamente.
 * 		      area, caracter 
 * 			  complejidad, tipo enumerado que representa la dificultad de la 
 *						   pregunta, básico->0;intermedio ->1;avanzado->2.
 *			  strings, es un arreglo que almacena 4 strings de largo a lo sumo 100.
 * 					   la primera posición almacena la pregunta y las demás, las
 * 					   respuestas.
 * 			  respuestaCorrecta, entero del 1 al 3 que identifica la respuesta
 * 								 correcta a la pregunta.
 */
typedef struct pregunta{
    int codigo;
    char area;
    enum NivelDeComplejidad complejidad;
    char strings[4][100];
    int respuestaCorrecta;
} PREGUNTA;

/*
 * LISTA es un tipo de datos apoyado en la estructura lista. Es la implementación
 * en C de una lista doblemente enlazada. En LISTA se guarda una pregunta y dos
 * apuntadores a otros elementos de la misma.
 * Atributos: preg, es una PREGUNTA.
 * 		      sig, apuntador al siguiente elemento de la lista.
 * 			  ant, apuntador al elemento anterior de la lista.
 */
typedef  struct lista {
    PREGUNTA preg;
    struct lista *sig;
    struct lista *ant;
} LISTA;


/*
 * insertar es un procedimiento que añade una pregunta a la lista enlazada. 
 * La inserción se hace al final de la lista y se actualiza el puntero al último
 * elemento.
 * Argumentos: ultimo, es un apuntador a la última posición de la lista.
 * 			   pregunta, es el tipo PREGUNTA que se va a añadir.
 * Retorna: nada, las modificaciones las hace a la lista enlazada en memoria.
 */
void insertar(LISTA **ultimo, PREGUNTA pregunta){
    LISTA *nuevo;
    nuevo = (LISTA *) malloc(sizeof(LISTA));

    if (*ultimo != NULL)
        (*ultimo)->sig = nuevo;

    nuevo->preg = pregunta;
    nuevo->sig = NULL;
    nuevo->ant = *ultimo;
    *ultimo = nuevo;
}

/*
 * buscar es una función que recorre la lista enlazada para encontrar una 
 * pregunta con el código dado.
 * Argumentos: ultimo, es un apuntador a la última posición de la lista.
 *             codigo, es un entero que representa el código de la pregunta a buscar.		   
 * Retorna: un apuntador al elemento de la lista que contiene a la pregunta con 
 * el código buscado, si existe. En caso contrario, devuelve NULL.
 */
LISTA **buscar(LISTA **ultimo, int codigo){
    LISTA **list;
    list = ultimo;

    while(*list != NULL){
        if (((*list)->preg.codigo) == codigo){
            return list;
        }
        list = &(*list)->ant;
    }
    return NULL;
}


/*
 * eliminar es una función que dado un elemento de la lista, lo elimina y hace
 * free para liberar memoria.
 * Argumentos: list, es un apuntador a la lista.
 *             codigo, es un entero que representa el código de la pregunta a eliminar.		   
 * Retorna: 1 si elimina la pregunta exitosamente, 0 en caso contrario.
 */
int eliminar(LISTA **list, int codigo){

    LISTA **temp;
    temp = buscar(list,codigo);
    
    
	if (temp != NULL){
	    //Cuando hay un solo elemento en la lista.
	    if((*temp)->sig == NULL && (*temp)->ant == NULL){
	        *list = NULL;
	        free(*temp);    
	    }
	    //Aquí estamos eliminando el último nodo.
	    else if((*temp)->sig == NULL && (*temp)->ant != NULL){
	        **list = *(*list)->ant; //Situamos el último en el anterior.
	        (*list)->sig = NULL;
	        free(*temp);
	    }
	    //Aquí estamos eliminando el primer nodo.
	    else if((*temp)->sig != NULL && (*temp)->ant == NULL){
	        (*temp)->sig->ant = NULL;
	        free(*temp);
	    }
	    //Aquí estamos en un caso del medio.
	    else{
	        (*temp)->ant->sig = (*temp)->sig;
	        (*temp)->sig->ant = (*temp)->ant;
	        free(*temp);
	    }
        
        return 1;

    } 
    else
		return 0;
    
    
}
