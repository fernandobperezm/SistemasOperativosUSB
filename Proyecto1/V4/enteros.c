#include <stdio.h>
#include <stdlib.h>

#include "listaEnlazada.h"

int main(){
	int *arreglo = NULL;
	arreglo = (int *)malloc(sizeof(int) *4);
	int i;
	for(i = 0;i < 4; i++){
		arreglo[i] = i;
		printf("HOla mi número es: %d",arreglo[i]);
	}
	free(arreglo);
	
	
	
	
	///////////////
	
	
	LISTA *listas[3];
	insertar(listas,"ana","bernardo",NULL);
	listas[0] = *buscar(listas,"ana","bernardo");
	if(listas[0] = NULL)
		printf("fracaso");
	
	else{
		printf("Exito");
		printf("%s %s",listas[0]->nombre[0],listas[0]->nombre[1]);
	}
	exit(1);
}
