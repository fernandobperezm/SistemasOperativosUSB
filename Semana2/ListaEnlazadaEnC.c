//ListaEnlazadaEnC.c
#include <stdio.h>
#include <stdlib.h>

//Se crea la estructura de la lista enlazada.
typedef struct listaenlazada{
	int x;
	int y;
	struct listaenlazada *sigPunto;
} LinkedList;

/* La estructura es la siguiente:
1- Se crea la estructura de la lista.
2- Se pide la memoria que necesitaremos para el primero y crearemos un apuntador
   que quede siempre en el ultimo.
3- Con el manejo de un temporal, iterativamente iremos añadiendo más elementos
   a la lista enlazada.
4- Luego haremos printf de todos los elementos.
*/

void main(){
	//Creamos la variable.
	LinkedList *miLista;
	LinkedList *aux;
	int i;
	
	//Se pide la memoria para la primera caja.
	miLista = (LinkedList *)malloc(sizeof(LinkedList));
	aux = miLista;
	
	for(i = 0;i <= 20;i++){
		//Asignamos los valores actuales.
		aux->x = i;
		aux->y = 20 - i;
		
		aux->sigPunto = (LinkedList *)malloc(sizeof(LinkedList));
		printf("Datos actuales: %d - %d\n",aux->x,aux->y);
		aux = aux->sigPunto;
		
	}
	
	free(miLista);
	free(aux);
}
