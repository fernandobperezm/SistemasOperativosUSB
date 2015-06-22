/*
 *
 *
 *
 *
 *
 */
 
#include <stdio.h>
#include <stdlib.h>

struct nodo{
	int numero;
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

void insertarNodo(LinkedList *L, int i){
	struct nodo *node = (struct nodo *)malloc(sizeof(struct nodo));
	node->numero = i;
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
		aux->numero = 0;
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
	int i;
	for(i = 0; i< 5; i++){
		insertarNodo(&lista,i);
	}
	destruirLista(&lista);
	exit(0);
}
