/*
	map-reduce.
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct nodo{
    char *clave;
    char *valor;
} NODO;

//void mapHilos(char *linea){
void *mapHilos(void* linea){
    char* lineaIntro = (char*) linea; 
    //////////////////////////////////////////////////////////////
    char *persona;
    char *amigos[sizeof(lineaIntro)-2];
    char *temp;
    printf("Llegue");
    /*
    //asignamos memoria al temporal 
    temp = malloc(sizeof(linea));

    //copiamos la linea en el temporal
    temp = strcpy(temp,linea);
    
    temp = strtok(temp," ");
    
    persona = temp;
    
    temp = strtok(NULL, " ");

    int i = 0;

    //podemos implementarlo con un for
    //en cada casilla del arreglo almacenamos un amigo        
    while ((temp = strtok(NULL, " ")) != NULL){
        
        amigos[i] = temp;
        printf("%s\n",amigos[i]);
        i++;
    	}
    i--;

    /////////////////////////////////////////////////////////
    	
    NODO nodo;
    int largo;
    persona[strlen(persona)] = ' ';
    nodo.clave = persona;
    printf("amigo %s\n",amigos[0]);
    strcat(nodo.clave,amigos[0]);
    printf("clave %s\n",nodo.clave);
    
    //largo = strlen(persona) + strlen(amigos[0]) + 2;
    //printf("amigo = %s",*amigos);
    //printf("largo = %d",largo);
    //nodo.clave = malloc(largo);
    //printf("amigo = %s",*amigos);
    //printf("largo = %d",sizeof(largo));
    //nodo.clave = strcpy(nodo.clave,persona);
    //nodo.clave[strlen(persona)] = ' ';
    //printf("amigo = %s",*amigos);
    //strcat(nodo.clave,amigos[0]);
    //printf("largo = %d\n",strlen(nodo.clave));
    //printf("%s\n",nodo.clave);
/*
    strcat(nodo.clave,amigos[0]);
    printf("%s\n",nodo.clave);*/
    
}
void reduce(){
}
