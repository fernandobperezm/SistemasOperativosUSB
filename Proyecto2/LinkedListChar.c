/*
 * LinkedListChar.c
 *
 * Descripción: Implementación en C de una lista enlazada de nodos, con un solo 
 * enlace. La misma tiene un apuntador al primer nodo, al último y su tamaño. Las 
 * operaciones son: insertarNodo y destruirLista. Los nodos se componen de una
 * cadena de caracteres y un apuntador al siguiente nodo.
 *
 * Autores:
 * 		Br. Fernando Pérez, carné USB: 12-11152.
 * 		Br. Leslie Rodrigues, carné USB: 10-10613.
 *
 * Última modificación: 05-27-2015. 
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct nodo{
	char *cadena;
	struct nodo *sig;
};

typedef struct cabecera{
	struct nodo *primero;
	struct nodo *ultimo;
	int size;
} LinkedList;

void crearLista(LinkedList *L){
	L->primero = NULL;
	L->ultimo = NULL;
	L->size = 0;
}

void insertarNodo(LinkedList *L, char *texto){
	struct nodo *node = (struct nodo *)malloc(sizeof(struct nodo));
	node->cadena = strdup(texto);
	node->sig = NULL;
	
	if(L->size == 0){
		L->primero = node;
		L->ultimo = L->primero;
	}
	else{
		L->ultimo->sig = node;
		L->ultimo = L->ultimo->sig; 
	}
	L->size = L->size + 1;
}

void destruirLista(LinkedList *L){
	struct nodo *aux;
	int i = 0;
	while(i < L->size){
		aux = L->primero;
		L->primero = L->primero->sig;
		free(aux->cadena);
		aux->sig = NULL;
		free(aux);
		i++;
	}
	L->size = 0;
	L->ultimo = NULL;
}

int main(){
	LinkedList lista;
	crearLista(&lista);
	char *texto1 = "hola";
	char *texto2 = "como";
	char *texto3 = "estas";
	char *texto4 = "menor";
	insertarNodo(&lista,texto1);
	insertarNodo(&lista,texto2);
	insertarNodo(&lista,texto3);
	insertarNodo(&lista,texto4);
	destruirLista(&lista);
	exit(0);
}
