/*
 * mainHilos.c
 * 
 * Descripción: Este archivo contiene el ciclo principal del proyecto usando 
 * hilos según la API POSIX.
 *
 * Autores: 
 * 	Br. Fernando Pérez, carné: 12-11152.
 * 	Br. Leslie Rodrigues, carné: 10-10613.
 *
 * Última modificación: 21-05-2015.
 */

//Inclumimos las librerías que necesitaremos.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "listaEnlazada.h"
#include <math.h>
#include <pthread.h>

typedef struct argumento{
	int *primero;
	int *ultimo;
}ARGUMENTO;

/*
 * Variables globales necesarias para los hilos.
 */
char **lineas = NULL;
ARGUMENTO argumentoHilo;
LISTA **lista;
int lineasTotales;
int nodosTotales;
pthread_mutex_t listLock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t linesLock= PTHREAD_MUTEX_INITIALIZER;


/*
 * mapHilos es una función que dada una linea, reconoce a una persona y su
 * lista de amigos. Luego, hace un mapeo de essa persona con sus amigos y el 
 * resultado lo guarda en la lista enlazada. Esta función la hace un hilo HIJO, 
 * creado en el MAIN.
 * Argumentos: entero, posicion de la lista a leer.
 * Retorna: nada, hace modificaciones en memoria.
 */
void *mapHilos(void *entero){
	
	char *savePtr = NULL;
	char *temp, *temp2;
	char *nombre;
	char **amigos;
    int nroDeAmigos = 0;
    int contador;
    int i,j;
	LISTA **listaTemp = NULL;
	int *casilla, tarea;
	casilla = (int *)entero;
	tarea = *casilla;
	int l;

	for(l = argumentoHilo.primero[tarea] ; l< argumentoHilo.ultimo[tarea];l++ ){
	    listaTemp = lista;
	    //COMIENZA LA SECCIÓN CRITICA
	    pthread_mutex_lock(&linesLock);
	    
	    temp = strdup(lineas[l]);
	    temp2 = strdup(lineas[l]);
	    
	    temp = strtok_r(temp, " ",&savePtr);
	    nombre = strdup(temp);
	
	    temp = strtok_r(NULL, " ",&savePtr);
	    nroDeAmigos = 0;
	    while((temp = strtok_r(NULL, " ",&savePtr))!=NULL){
	        
            nroDeAmigos++;
        }
        savePtr = NULL;
	    free(temp);
	    
        amigos = (char **)malloc(nroDeAmigos * sizeof(char **));
        
        contador = 0;
        
        
        
        temp2 = strtok_r(temp2," ",&savePtr);
        
        temp2 = strtok_r(NULL," ",&savePtr);
        
        while((temp2 = strtok_r(NULL," ",&savePtr)) != NULL){
            
    	    amigos[contador] = strdup(temp2);

    	    contador++;
        }
        
        free(temp2);
        savePtr = NULL;
        amigos[contador - 1] = strtok_r(amigos[contador - 1],"\n",&savePtr);
        

    
        for(i = 0; i < nroDeAmigos; i++){
        
            j = strcmp(nombre,amigos[i]);

            listaTemp = buscar(lista,nombre,amigos[i]);
            if(j <= 0){  
                    listaTemp = buscar(lista,nombre,amigos[i]);
                    
                    
           }else{
                    listaTemp = buscar(lista,amigos[i],nombre);
            }
            
            if(listaTemp == NULL){
                
                if(j <= 0){  
                    insertar(lista,nombre,amigos[i]);
                    
                }else{
                    insertar(lista,amigos[i],nombre);
                }
                
                (*lista)->nroAmigos[0] = nroDeAmigos;
                (*lista)->nroAmigos[1] = 0;
                (*lista)->nroAmigos[2] = 0;                
                
                (*lista)->amigos1 = (char **)malloc(nroDeAmigos * sizeof(char **));
                for(contador =0; contador<(*lista)->nroAmigos[0];contador++){
                
                    (*lista)->amigos1[contador] = strdup(amigos[contador]);
                }
                nodosTotales++;
                
            } else{
                (*listaTemp)->nroAmigos[1] = nroDeAmigos;
                //pedimos espacio para almacenar a los amigos
                (*listaTemp)->amigos2 = (char **)malloc(contador * sizeof(char **));
                for(contador =0; contador<(*listaTemp)->nroAmigos[1];contador++){
                    (*listaTemp)->amigos2[contador] = strdup(amigos[contador]);
                }
            }
            printf("i = %d\n",i);
        }
        pthread_mutex_unlock(&linesLock);
    }    

    pthread_exit(NULL);
}

void *reduceHilo(void *entero){
    
    int *casilla, tarea;
	casilla = (int *)entero;
	tarea = *casilla;
	int nroAmigosComunes; //numero de amigos en comun
    LISTA **l;
    l = lista;
    
    printf("primero = %d; ultimo =  %d \n",argumentoHilo.primero[tarea],argumentoHilo.ultimo[tarea]);
    int i,j,k,n;
    pthread_mutex_lock(&linesLock);
    
    for(i = 0; i < argumentoHilo.primero[tarea]; i++){
    	if((*l)->ant != NULL)
        	*l = (*l)->ant;
        
    }
    
    for(k = argumentoHilo.primero[tarea]; k < argumentoHilo.ultimo[tarea]; k++){
        nroAmigosComunes = 0;
        if((*l)->nroAmigos[1] != 0){
            for(i = 0; i < (*l)->nroAmigos[0]; i++){
            
                 for(j = 0; j < (*l)->nroAmigos[1]; j++){
                    if (!strcmp((*l)->amigos1[i],(*l)->amigos2[j] )){
                        nroAmigosComunes++;
                    }
                 }
            }
            
            n = 0;
            (*l)->comunes = (char **)malloc(sizeof(char **) * nroAmigosComunes);
            for(i = 0; i < (*l)->nroAmigos[0]; i++){
                for(j = 0; j < (*l)->nroAmigos[1]; j++){
                    if (!strcmp((*l)->amigos1[i],(*l)->amigos2[j] )){
                        (*l)->comunes[n] = strdup((*l)->amigos1[i]);
                        n++;
                    }
                }
            }
            (*l)->nroAmigos[2] = n; 
        }
        if(((*l)->ant)!=NULL)
            *l = (*l)->ant;
    }
pthread_mutex_unlock(&linesLock);
}


/*
 * main es el ciclo principal del programa, también, es el ciclo principal del
 * proceso padre, aquí se generarán las llamadas a pthread_create necesarias para que
 * los hijos hagan MAP y REDUCE.
 * Argumentos: argc, es el contador de argumentos pasados por entrada estándar.
 * 			   argv, contiene los distintos argumentos pasados por entrada estándar.
 * Retorna: 0 si termina con éxito, otro entero en cualquier otro caso.
 */
int main(int argc, char *argv[]){
    clock_t comienzo;   
    clock_t final;
	int nroHilos;
	char *nombreArchivo;
	char *salida;
	
	//Verificamos que la entrada del usuario sea correcta y ajustamos las variables.
	if(argc == 5){
		nroHilos = atoi(argv[2]);
		nombreArchivo = argv[3];
		salida = argv[4];
	}
	else if (argc == 3){
		nroHilos = 1;
		nombreArchivo = argv[1];
		salida = argv[2];
	}
	
	if (nroHilos == 0){
		printf("El número de procesos debe ser positivo, ejecute el programa nuevamente.\n");
		exit(1);
	}
	int contador = 0;
	int i;
	int nroLineas[nroHilos];//Nro de lineas a asignar a cada hilo
	lineasTotales = 0;//Nro de lineas que contiene el archivo
	int nroNodos = 0;
	int residuo = 0;
	
	LISTA **lTemp;
	
	char *line = NULL;
    size_t len = 0;
    ssize_t read;
	
	
	int status;

    lineasTotales = 0;//Nro de lineas que contiene el archivo

	FILE *filepointer;
	
	pthread_t *TIDs = NULL;
        
    filepointer = fopen(nombreArchivo,"r");

    if(filepointer == NULL){
    	perror("Lo lamentamos");
    	printf("Vuelva a ejecutar el programa con el nombre del archivo correcto.\n");
    	printf("errno = %d\n",errno);
    	exit(1);
    }
    printf("Abriendo el archivo...\n");
    
    printf("Leyendo los datos de la base de datos...\n");
	
	//inicializamos el numero de lineas a asignar a cada hilo en 0
	for(i= 0; i < nroHilos; i++ )
	    nroLineas[i] = 0;
	i = 0;
	
	//lectura y almacenado de lineas
	//se determina cuantas y cuales lineas se le asignan a cada proceso

	while ((read = getline(&line, &len, filepointer)) != -1) {
	    if(i == nroHilos)
	        i = 0;
        
        //incrementamos contadores
        nroLineas[i]++;
        lineasTotales++;
        i++;
        
    }
    //free(line);
    rewind(filepointer);
    //pedimos memoria para almacenar las lineas
    //lineas = (char **)malloc(sizeof(char **)*4);
    lineas = (char **)malloc(sizeof(char*) * lineasTotales);
    
    i= 0;
    //almacenamos las lineas
    while ((read = getline(&line, &len, filepointer)) != -1) {
	    lineas[i] = strdup(line); 
	    
	    i++;        
    }
    
    printf("Numero de lineas del archivo = %d\n",lineasTotales);
    puts("El archivo contiene lo siguiente: \n");
    for(i = 0; i<lineasTotales; i++)
        puts(*(lineas+i));
    
    int j;
    
    lista = (LISTA **)malloc(sizeof(LISTA **) * lineasTotales);
    *lista = NULL; 
    comienzo = clock();
    TIDs = (pthread_t *)malloc(sizeof(pthread_t *) * nroHilos);
    
    int primera = 0;
    int ultima = 0;
    int *icorrespondiente;
    argumentoHilo.primero = (int *)malloc(sizeof(int *) * nroHilos);
    argumentoHilo.ultimo = (int *)malloc(sizeof(int *) * nroHilos);
    icorrespondiente = (int *)malloc(sizeof(int *) * nroHilos);
    
    //mandamos a mapear
    for (i = 0; i < nroHilos; i++){
        
        primera = ultima;
        ultima = ultima + nroLineas[i];
		argumentoHilo.primero[i] = primera;
		argumentoHilo.ultimo[i] = ultima;
		icorrespondiente[i] = i;
		printf("%d %d",argumentoHilo.primero[i],argumentoHilo.ultimo[i] );
    	status = pthread_create(&TIDs[i],NULL,mapHilos, (void *)&(icorrespondiente[i]));
        if (status != 0){
            perror("Error al crear el hilo:");
            exit(1);
        } 
        
        else
        	printf("Se ha creado un hilo con éxito \n");
        
     }
    
    int retorno = 0;
    for (i=0;i < nroHilos; i++){
    	status = pthread_join(TIDs[i],(void *)&retorno);
    	if(status != 0)
    		printf("Ocurrió un error");
    	else
    		printf("éxito");
    }
        
        if(nodosTotales >= nroHilos){
            nroNodos = nodosTotales / nroHilos;
            residuo = nodosTotales % nroHilos;
        } else{
            residuo = nodosTotales;
        }

    
        puts("##########REDUCE################################");
        //Mandamos a hacer reduce
        for (i = 0; i < nroHilos; i++){
            icorrespondiente[i] = i;
            
            //asignamos primero y ultimo para el hijo
            if (i != 0){
                argumentoHilo.primero[i] = argumentoHilo.ultimo[i];
                }else{
                    argumentoHilo.primero[i] = 0;
                }   
            
		        argumentoHilo.ultimo[i] = argumentoHilo.primero[i] + nroNodos;
		    
		    if(residuo > i){
		        argumentoHilo.ultimo[i]++;
		    }else{
		        if(nroNodos == 0){
		            argumentoHilo.primero[i] = 0;
		            argumentoHilo.ultimo[i] = 0;
		        }
		    }

    	    status = pthread_create(&TIDs[i],NULL,reduceHilo, (void *)&(icorrespondiente[i]));
            if (status != 0){
                perror("Error al crear el hilo:");
                exit(1);
            } 
        
            else
        	    printf("Se ha creado un hilo con éxito \n");
                
        }
    
        retorno = 0;
        for (i=0;i < nroHilos; i++){
    	    status = pthread_join(TIDs[i],(void *)&retorno);
    	    if(status != 0)
    		    printf("Ocurrió un error");
    	    else
    		    printf("éxito");
        }
        puts("######PAPA GENERA ARCHIVO A PARTIR DE LA ESTRUCTURA###############");
        filepointer = fopen(argv[3],"w");
        
        lTemp = lista;
        while((*lTemp) !=NULL){
        	printf("(%s %s) -> %d \n",(*lTemp)->nombre[0],(*lTemp)->nombre[1],(*lTemp)->nroAmigos[2]);
            if ((*lTemp)->nroAmigos[2] != 0){
                fprintf(filepointer,"(%s %s) ->",(*lTemp)->nombre[0],(*lTemp)->nombre[1]);
            
                printf("(%s %s) ->",(*lTemp)->nombre[0],(*lTemp)->nombre[1]);
                for(i=0;i < (*lTemp)->nroAmigos[2]; i++){
                    fprintf(filepointer," %s",(*lTemp)->comunes[i]);
                    printf(" %s",(*lTemp)->comunes[i]);

            }
            fprintf(filepointer,"\n");
            printf("\n");
            }
            *lTemp = (*lTemp)->sig;
        }
        fprintf(filepointer," \n");
        fclose(filepointer);
        final = clock() -comienzo;
        printf("La ejecución del programa tomo: %d unidades de tiempo.\n",(int)final);
     
    exit(0);
}
