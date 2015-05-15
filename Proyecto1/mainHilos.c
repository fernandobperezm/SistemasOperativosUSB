/*
 * mainHilos.c
 * 
 * Descripción: Este archivo contiene el ciclo principal del proyecto usando 
 * hilos POSIX.
 * 
 * Autores: 
 * 	Br. Fernando Pérez, carné: 12-11152.
 * 	Br. Leslie Rodrigues, carné: 10-10613.
 *
 * Última modificación: 13-05-2015.
 */

//Inclumimos las librerías que necesitaremos.
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <errno.h>
#include "listaEnlazada.h"

void *PrintHello(void* arg){
	printf("Hola, ya me cree");
	pthread_exit(0);
}

int main(int argc, char *argv[]){
	int nroHilos = atoi(argv[1]);
	pthread_t threads[nroHilos];
	char *nombreArchivo = argv[2];
	int t;
	int status;
	
	char **linea;
	char **temp;
	char **nombre;
	//char **flecha;
	char **amigo;
	char fin;
	
	//  El proceso padre lee el archivo completo y cuenta las lineas. Esto, para
	// dividir el proceso de map y reduce a los hilos donde todos ejecuten la 
	//  misma cantidad de operaciones.
	FILE *filepointer;
    PERSONA P;
    
        
    filepointer = fopen(nombreArchivo,"r");
    if(filepointer == NULL){
    	perror("Lo lamentamos");
    	printf("Vuelva a ejecutar el programa con el nombre del archivo correcto.\n");
    	printf("errno = %d\n",errno);
    	exit(1);
    }
    printf("Abriendo el archivo...\n");
    
    printf("Leyendo los datos de la base de datos...\n");	    
    while(fscanf(filepointer,"%[^\n]%c",linea,&fin) != EOF){
    	printf("%s\n",linea);
    	/*temp = (*linea);
    	temp = strtok(temp," ");
    	
    	printf("%d %d",temp,&(temp));
    	
    	P.nombre = &(*temp);
    	
    	temp = strtok(NULL, " ");
    	
    	//P.amigos = &(amigos);
    	
    	while ((temp = strtok(NULL, " ")) != NULL){
    		amigos = &temp;
    		puts(*amigos);
    		amigos++;
    	}*/
   	}
    
    fclose(filepointer);
    
    printf("Hemos terminado de leer el archivo.\n");
	
	/*
	for(t = 0; t < nroHilos; t++){
		status = pthread_create(&threads[t],NULL,PrintHello,(void *) t);
	}*/
	exit(0);
}
