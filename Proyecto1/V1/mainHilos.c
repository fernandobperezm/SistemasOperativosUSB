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
	char* p = (char*) arg;
	printf("%s",p);
	pthread_exit(0);
}

typedef struct nodo{
    char *clave;
    char *valor;
} NODO;

//void mapHilos(char *linea){
void *mapHilos(void* linea){
	printf("%s",(char*)linea);
	//size_t largo = strlen((char *)linea);
	//printf("%d %s",largo,line);
	/*
    char lineaIntro[ = ((char*) linea); 
    //////////////////////////////////////////////////////////////
    char *persona;
    char *amigos[sizeof(lineaIntro)-2];
    char *temp;
    printf("Después del thread: %s",lineaIntro);*/
    pthread_exit(0);
}


int main(int argc, char *argv[]){
	int nroHilos = atoi(argv[1]);
	pthread_t threads[nroHilos];
	char *nombreArchivo = argv[2];
	int contador = 0;
	int status;
	
	char *line = NULL;
	char *argumento = NULL;
    size_t len = 0;
    ssize_t read;
	
	FILE *filepointer;
    PERSONA P;
    
    //pthread_mutex_t my_lock = PTHREAD_MUTEX_INITIALIZER;
        
    filepointer = fopen(nombreArchivo,"r");

    if(filepointer == NULL){
    	perror("Lo lamentamos");
    	printf("Vuelva a ejecutar el programa con el nombre del archivo correcto.\n");
    	printf("errno = %d\n",errno);
    	exit(1);
    }
    printf("Abriendo el archivo...\n");
    
    printf("Leyendo los datos de la base de datos...\n");
	
	
	while ((read = getline(&line, &len, filepointer)) != -1) {  	
    	//printf("%s\n",line);
    	if(contador == nroHilos)
    		contador = 0;
    	printf("Antes del thread: %s \n",line);
    	status = pthread_create(&threads[contador],NULL,mapHilos,(void *) line);
    	if(status)
    		printf("No se pudo crear el hilo");
    	contador++;
    }
    
    int i;
    for(i = 0; i < nroHilos; i++){
    	pthread_join(threads[i],NULL);
    }
	
	free(line);
	
	fclose(filepointer);
    
    printf("Hemos terminado de leer el archivo.\n");
    
    exit(0);
	
	/*int t;
	int contador;
	int status;
	
	char *linea;
	char *temp;
	//char **nombre;
	//char **flecha;
	char *amigos;
	char fin;*/
	
	//  El proceso padre lee el archivo completo y cuenta las lineas. Esto, para
	// dividir el proceso de map y reduce a los hilos donde todos ejecuten la 
	//  misma cantidad de operaciones.
	/*
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
    
    
    w
    
    
    
    /*	    
    while(fscanf(filepointer,"%[^\n]%c",linea,&fin) != EOF){
    	printf("%s\n",linea);
    	temp = linea;
    	
    	printf("%s\n",temp);
    	temp = strtok(temp," ");
    	
    	
    	P.nombre = temp;
    	printf("%s\n",P.nombre);
    	
    	temp = strtok(NULL," ");
    	
    	contador = 0;
    	while((temp = strtok(NULL," ")) != NULL){
    		amigos = temp;
    		printf("%s amigos\n",amigos);
    		//contador = contador + 1;
    		amigos++;
    	}
    	//P.amigos = (amigos - contador);
    	//printf("%s\n",P.amigos);
    	
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
    	}
   	}*/
    
    //fclose(filepointer);
    
    //printf("Hemos terminado de leer el archivo.\n");
	
	/*
	for(t = 0; t < nroHilos; t++){
		status = pthread_create(&threads[t],NULL,PrintHello,(void *) t);
	}*/
	//exit(0);
}
