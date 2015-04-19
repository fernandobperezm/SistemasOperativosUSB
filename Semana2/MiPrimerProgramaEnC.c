//MiPrimerProgramaEnC.
#include <stdio.h>
#include <stdlib.h>

//Creo el TIPO ARBOL, y llamo a arbol para poder referenciarlo a el mismo.
typedef struct arbol{
	int nodo;
	struct arbol *izq;
	struct arbol *der;
} ARBOL;

/*
//Función para recorrer el árbol.
void recorridoEnArbol(ARBOL *miArbol,int k){
	if (miArbol->der == NULL && miArbol->izq == NULL){
		
	}
	else{
		
	}
	
}
*/

/*La estructura es la siguiente:
1- Se crea el árbol y se pide la memoria para el primer nodo y sus apuntadores.
2- Se inicializa el primer nodo en 0.
3- Para crear las otras cajas, hacemos que el sistema nos de memoria tanto en 
el hijo izquierdo como en el derecho.
4- Inicializamos los otros hijos.
*/
void main(){
	//Se define el árbol.
	ARBOL *elArbol;

	//Se pide memoria al sistema.
	elArbol = (ARBOL *)malloc(sizeof(ARBOL));
	
	//Inicializo el primer nodo.
	elArbol->nodo= 0;
	//Pido la memoria para los otros hijos.
	elArbol->izq = (ARBOL *)malloc(sizeof(ARBOL));
	elArbol->der = (ARBOL *)malloc(sizeof(ARBOL));
	
	//Inicializo los hijos izquierdos y derechos.
	elArbol->izq->nodo = 1;
	elArbol->izq->izq = NULL;
	elArbol->izq->der = NULL;

	elArbol->der->nodo = 2;
	elArbol->der->izq = NULL;
	elArbol->der->der = NULL;
	
	printf("nodo %d\n",elArbol->nodo);
	printf("nodo %d\n",elArbol->izq->nodo);
	printf("nodo %d\n",elArbol->der->nodo);
	
	free(elArbol);
}
