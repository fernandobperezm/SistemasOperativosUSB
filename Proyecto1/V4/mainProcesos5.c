/*
 * mainProcesos.c
 * 
 * Descripción: Este archivo contiene el ciclo principal del proyecto usando 
 * procesos.
 *
 * Autores: 
 * 	Br. Fernando Pérez, carné: 12-11152.
 * 	Br. Leslie Rodrigues, carné: 10-10613.
 *
 * Última modificación: 16-05-2015.
 */

//Inclumimos las librerías que necesitaremos.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
//#include "listaEnlazada.h"
#include <math.h>

//#define DIGITOS(n) (floor(log10(abs(n)))+1)

//int nDigits  floor(log10(abs(the_integer))) + 1;

//typedef

void mapProcesos(char *linea){

    //char* lineaIntro = (char*) linea;
    char *temp; 
    char *persona[1];
    char **amigos; //arreglo de amigos
    int i,j; //contador
    //int nroDigitos = DIGITOS(getpid())+1;
    char archivo[10];
    int nroAmigos = 0; //Cantidad de amigos que posee la persona
    
    
    //archivo = (char *)malloc(nroDeDigitos(getpid())+1);
    
    sprintf(archivo,"%d",getpid());
    strcat(archivo,".txt");
    
    FILE *fp;
    fp = fopen(archivo,"a");
    
    //copiamos la linea en el temporal
    
    temp = strdup(linea);
    puts("entre!!");
    //guardamos el nombre de la persona
    temp = strtok(temp," ");      

    persona[0] = temp;

    //ponemos la flecha en el temporal pero no la guardamos
    temp = strtok(NULL, " ");
    
    
    while((temp = strtok(NULL, " "))!=NULL){
        
        //puts("hola");
        amigos[nroAmigos] = malloc(sizeof(temp));
       
        amigos[nroAmigos] = temp;
        
        nroAmigos++;
           
    }
    //i--;
    
    amigos[nroAmigos-1] = strtok(amigos[nroAmigos-1],"\n");

    //amigos[i] = temp;
    
    //int i;
    printf("mi pid es %d, mi linea adentro es:\n ",getpid());
    for(i = 0; i < nroAmigos; i++){
        j = strcmp(persona[0],amigos[i]);
        
        if(j<=0){
            fprintf(fp,"(%s %s) -> ",persona[0],amigos[i]);
            printf("(%s %s) -> ",persona[0],amigos[i]);
        }else{
            fprintf(fp,"(%s %s) -> ",amigos[i],persona[0]);
            printf("(%s %s) -> ",amigos[i],persona[0]);
        }
        for(j = 0; j < nroAmigos; j++){
            fprintf(fp," %s",amigos[j]); 
            printf(" %s",amigos[j]);            
        }
;
        fprintf(fp,"\n");
        printf("\n");
    }
    fclose(fp);
    
    free(temp); 
       
}

int main(int argc, char *argv[]){
	int nroProcesos = atoi(argv[1]);
	char *nombreArchivo = argv[2];
	int contador = 0;
	int i;
	int nroLineas[nroProcesos];//Nro de lineas a asignar a cada proceso
	int lineasTotales = 0;//Nro de lineas que contiene el archivo
	
	char *line = NULL;
    size_t len = 0;
    ssize_t read;
	
	char **lineas;
	
	int status;
	
	pid_t childpid;
	FILE *filepointer;
	
	int *PIDs = NULL;
        
    filepointer = fopen(nombreArchivo,"r");

    if(filepointer == NULL){
    	perror("Lo lamentamos");
    	printf("Vuelva a ejecutar el programa con el nombre del archivo correcto.\n");
    	printf("errno = %d\n",errno);
    	exit(1);
    }
    printf("Abriendo el archivo...\n");
    
    printf("Leyendo los datos de la base de datos...\n");
	
	//inicializamos el numero de lineas a asignar a cada proceso en 0
	for(i= 0; i < nroProcesos; i++ )
	    nroLineas[i] = 0;
	    
	i = 0;
	
	//lectura y almacenado de lineas
	//se determina cuantas y cuales lineas se le asignan a cada proceso

	while ((read = getline(&line, &len, filepointer)) != -1) {
	    if(i == nroProcesos)
	        i = 0;
        
        //incrementamos contadores
        nroLineas[i]++;
        lineasTotales++;
        i++;
        //puts(*line);
        
    }
    //free(line);
    rewind(filepointer);
    //pedimos memoria para almacenar las lineas
    lineas = (char **)malloc(sizeof(char **)*4);
    
    i= 0;
    //almacenamos las lineas
    while ((read = getline(&line, &len, filepointer)) != -1) {
	    lineas[i] = strdup(line); 
	    i++;
	    //if(i == nroProcesos)
	    //    i = 0;
        
        //incrementamos contadores
        //nroLineas[i]++;
        //lineasTotales++;
        //i++;
        //puts(*line);
        
    }
    
    printf("Numero de lineas del archivo = %d\n",lineasTotales);
    puts("El archivo contiene lo siguiente: \n");
    for(i = 0; i<lineasTotales; i++)
        puts(*(lineas+i));
    
    //free(line);
    
    int j;
    //creacion de hijos    
    //puts(*lineas);
    
    PIDs = (char*)malloc(sizeof(int) * nroProcesos);
    
    //int pid[nroProcesos]
    int primera = 0;
    int ultima = 0;
    int aja[nroProcesos][2];
    int k;
    for (i = 0; i < nroProcesos; i++){
        
        primera = ultima;
        ultima = ultima + nroLineas[i];

    
        if ((childpid = fork()) < 0){
            perror("fork:");
            exit(1);
        } 
        
        if (childpid == 0){
            
            while(primera<ultima){
                printf("Soy el hijo %d con pid %d\n",i,getpid());
                puts("mi linea a mapear es: ");
                puts(lineas[primera]);
                mapProcesos(lineas[primera]);
                primera++;    
            }
            exit(0);
        }
        else{ //Guardamos los distintos PID de los hijos.
        	PIDs[i] = (int)childpid;
        }

    }
     
  
           
    
    // El padre espera que terminen todos los hijos que creo.
    for (i = 0; i < nroProcesos; i++){
        wait(&status);
    }

	fclose(filepointer);
	printf("Hemos terminado de leer el archivo.\n");
	
	//Ahora pasamos a la lectura de todos los archivos que los hijos crearon.
    for (i = 0; i < nroProcesos; i++){
        
        primera = ultima;
        ultima = ultima + nroLineas[i];

    
        if ((childpid = fork()) < 0){
            perror("fork:");
            exit(1);
        } 
        
        if (childpid == 0){
            
            while(primera<ultima){
                printf("Soy el hijo %d con pid %d\n",i,getpid());
                puts("mi linea a mapear es: ");
                puts(lineas[primera]);
                mapProcesos(lineas[primera]);
                primera++;    
            }
            exit(0);
        }
        else{ //Guardamos los distintos PID de los hijos.
        	PIDs[i] = (int)childpid;
        }

    }
    
    
    exit(0);
}
