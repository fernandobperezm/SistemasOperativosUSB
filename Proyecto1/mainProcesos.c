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
#include <time.h>

/*
 * mapProcesos es una función que dada una linea, reconoce a una persona y su
 * lista de amigos. Luego, hace un mapeo de essa persona con sus amigos y el 
 * resultado lo guarda en un archivo. Esta función la hace un proceso HIJO, 
 * creado en el MAIN. El nombre del archivo es PID.txt donde PID es el PID del
 * hijo.
 * Argumentos: linea, es la línea a mapear.
 * Retorna: crea un archivo en disco con el mapeado de la línea.
 */
void mapProcesos(char *linea){
    char *temp = NULL;
    char *temp2 = NULL; 
    char *persona[1];
    char **amigos = NULL; //arreglo de amigos
    int i,j,contador; //contador
    char archivo[10];
    int nroAmigos = 0; //Cantidad de amigos que posee la persona
    
    sprintf(archivo,"%d",getpid());
    strcat(archivo,".txt");
    
    FILE *fp;
    fp = fopen(archivo,"a");
    
    //copiamos la línea en el temporal
    
    temp = strdup(linea);
    
    //guardamos el nombre de la persona
    temp = strtok(temp," ");      
	
    persona[0] = temp;

    //ponemos la flecha en el temporal pero no la guardamos
    temp = strtok(NULL, " ");
    while((temp = strtok(NULL, " "))!=NULL){
        nroAmigos++;
    }
    
    free(temp);
    
    amigos = (char **)malloc(nroAmigos * sizeof(char **));
    contador = 0;
    temp2 = strdup(linea);
    temp2 = strtok(temp2," ");
    temp2 = strtok(NULL," ");
    while((temp2 = strtok(NULL," ")) != NULL){
    	amigos[contador] = strdup(temp2);
    	contador++;
    }        
    
    amigos[nroAmigos-1] = strtok(amigos[nroAmigos-1],"\n");
    for(i = 0; i < nroAmigos; i++){
        if(!strcmp(amigos[i],"-none-")){
            j = strcmp(persona[0],amigos[i]);
        
            if(j<=0){
                fprintf(fp,"(%s %s) -> ",persona[0],amigos[i]);
            }else{
                fprintf(fp,"(%s %s) -> ",amigos[i],persona[0]);
            }
            for(j = 0; j < nroAmigos; j++){
                fprintf(fp," %s",amigos[j]);         
            }

            fprintf(fp,"\n");
        }
    }
    fclose(fp);
    
    free(temp2); 
    free(amigos);   
}

/*
 * reduceProcesos es un procedimiento que, dada una lista enlazada de nodos, 
 * abre un archivo y guarda en él, los amigos que puedan tener en común dos 
 * personas de la red social. Esta función la ejecuta un proceso HIJO creado en
 * el MAIN. El nombre del archivo es PID.txt donde PID es el PID del
 * hijo.
 * Argumentos: l, es una lista enlazada, apuntando al nodo a reducir.
 * Retorna: crea un archivo en disco con los amigos en común de la persona.
 */
void reduceProcesos(LISTA **l){
    int i,j;
    char archivo[10];
    FILE *fp;
    int amigosEnComun = 0;    
    sprintf(archivo,"%d",getpid());
    strcat(archivo,".txt");      
    
    fp = fopen(archivo,"a");
     
    if((*l)->nroAmigos[1] != 0){
        fprintf(fp,"(%s %s) ->",(*l)->nombre[0],(*l)->nombre[1]);
        for(i = 0; i < (*l)->nroAmigos[0]; i++){
            for(j = 0; j < (*l)->nroAmigos[1]; j++){
                if (!strcmp((*l)->amigos1[i],(*l)->amigos2[j] )){
                    fprintf(fp," %s",(*l)->amigos1[i]);
                    amigosEnComun++;
                }
            }
        
        }
        if(amigosEnComun == 0)
            fprintf(fp,"-none-");
        fprintf(fp," \n");
        
           
    }else{
        fprintf(fp,"(%s %s) ->",(*l)->nombre[0],(*l)->nombre[1]);
    }
    fclose(fp);
}

/*
 * main es el ciclo principal del programa, también, es el ciclo principal del
 * proceso padre, aquí se generarán las llamadas a fork necesarias para que
 * los hijos hagan MAP y REDUCE.
 * Argumentos: argc, es el contador de argumentos pasados por entrada estándar.
 * 			   argv, contiene los distintos argumentos pasados por entrada estándar.
 * Retorna: 0 si termina con éxito, otro entero en cualquier otro caso.
 */
int main(int argc, char *argv[]){
	int nroProcesos;
	char *nombreArchivo;
	char *salida;
	
	//Verificamos que la entrada del usuario sea correcta y ajustamos las variables.
	if(argc == 5){
		nroProcesos = atoi(argv[2]);
		nombreArchivo = argv[3];
		salida = argv[4];
	}
	else if (argc == 3){
		nroProcesos = 1;
		nombreArchivo = argv[1];
		salida = argv[2];
	}
	
	if (nroProcesos == 0){
		printf("El número de procesos debe ser positivo, ejecute el programa nuevamente.\n");
		exit(1);
	}
	
	clock_t comienzo;   
    clock_t final;  
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
	FILE *filepointer, *fp;
	
	int *PIDs = NULL;
      
    filepointer = fopen(nombreArchivo,"r");

    if(filepointer == NULL){
    	perror("Lo lamentamos");
    	printf("Vuelva a ejecutar el programa con el nombre del archivo correcto.\n");
    	printf("errno = %d\n",errno);
    	exit(1);
    }
    printf("Abriendo el archivo...\n");
	
	//inicializamos el numero de lineas a asignar a cada proceso en 0
	for(i= 0; i < nroProcesos; i++ )
	    nroLineas[i] = 0;
	    
	i = 0;
	
	//lectura y almacenado de lineas
	//se determina cuantas y cuales lineas se le asignan a cada proceso
	while ((read = getline(&line, &len, filepointer)) != -1) {
	    if(i == nroProcesos)
	        i = 0;
	        
        nroLineas[i]++;
        lineasTotales++;
        i++;
        
    }

    rewind(filepointer);
    lineas = (char **)malloc(sizeof(char*) * lineasTotales);
    
    i= 0;
    //almacenamos las lineas
    while ((read = getline(&line, &len, filepointer)) != -1) {
	    lineas[i] = strdup(line); 
	    i++;        
    }

    int j;
    //creacion de hijos    
    PIDs = (int *)malloc(sizeof(int *) * nroProcesos);

    int primera = 0;
    int ultima = 0;
    for (i = 0; i < nroProcesos; i++){
        
        primera = ultima;
        ultima = ultima + nroLineas[i];

    
        if ((childpid = fork()) < 0){
            perror("fork:");
            exit(1);
        } 
        
        if (childpid == 0){
            
            while(primera<ultima){
                mapProcesos(lineas[primera]);
                primera++;    
            }
            exit(0);
        }
        else{
            comienzo = clock(); 
        	PIDs[i] = (int)childpid;
        }

    }
     
    // El padre espera que terminen todos los hijos que creo.
    for (i = 0; i < nroProcesos; i++){
        wait(&status);
    }

	fclose(filepointer);
	
	char *nombre1;
	char *nombre2;
	char **amigos;
	char nombreHijo[10];
	char *temp;
	char *temp2;
	int nroAmigos;
	
	
    LISTA **lista;
    lista = (LISTA **)malloc(sizeof(LISTA **));
    *lista = NULL;
    
    LISTA **listaTemp;
    listaTemp = (LISTA **)malloc(sizeof(LISTA **));
    *listaTemp = NULL;
	
	int nodosTotales;
	int *nroNodos = NULL;
	int nroArchivos;
	nroNodos = (int *)malloc(sizeof(int*));
	
	puts("Ya los hijos terminaron de hacer map, ahora el padre juntará los datos.\n");
	
    nodosTotales = 0;//nro de nodos
    
    if(lineasTotales < nroProcesos){
        nroArchivos = lineasTotales;
    } else {
        nroArchivos = nroProcesos;
    }
    
 	//inicializamos el numero de nodos a asignar a cada proceso en 0
	for(i= 0; i < nroProcesos; i++ ){
	    nroNodos[i] = 0;
	}       
	
	//Ahora pasamos a la lectura de todos los archivos que los hijos crearon.
	for (i = 0; i < nroArchivos; i++){
	    
	    sprintf(nombreHijo,"%d",PIDs[i]);
        strcat(nombreHijo,".txt");
        
        filepointer = fopen(nombreHijo,"r");
        
        j = 0;
        
        //almacenamos las lineas
        while ((read = getline(&line, &len, filepointer)) != -1) {
	        
            if(j == nroArchivos){
	            j = 0;
	        }
	        
            //copiamos la línea en el temporal
    
            temp = strdup(line);
    
            //guardamos el nombre de la primera persona
            temp = strtok(temp," ");      
	
            nombre1 = temp;

            //guardamos el nombre de la primera persona
            temp = strtok(NULL," ");      
	
            nombre2 = temp;

            //ponemos la flecha en el temporal pero no la guardamos
            temp = strtok(NULL, " ");

            while((temp = strtok(NULL, " "))!=NULL){
                nroAmigos++;
            }
    
            free(temp);
    
 
            temp2 = strdup(line);
            temp2 = strtok(temp2," ");
            
            temp2 = strtok(NULL," ");  
                    
            temp2 = strtok(NULL," ");
            amigos = (char **)malloc(contador * sizeof(char **));
            while((temp2 = strtok(NULL," ")) != NULL){
    	            amigos[contador] = strdup(temp2);
    	            contador++;
                }
            
            nombre1 = strtok(nombre1,"(");//Removemos el "(" del nombre
            nombre2 = strtok(nombre2,")");//Removemos el ")" del nombre
            
            amigos[contador-1] = strtok(amigos[contador-1],"\n");
            free(temp2);
            
            listaTemp = buscar(lista,nombre1,nombre2);
            
            
            if(listaTemp == NULL){
                insertar(lista,nombre1,nombre2);
                
                (*lista)->nroAmigos[0] = contador;
                (*lista)->nroAmigos[1] = 0;

                //pedimos espacio para almacenar a los amigos
                (*lista)->amigos1 = (char **)malloc(nroAmigos * sizeof(char **));

                for(contador =0; contador<(*lista)->nroAmigos[0];contador++){
                
                    (*lista)->amigos1[contador] = strdup(amigos[contador]);

                }
                
                nroNodos[j]++;
                nodosTotales++;
                
            } else{
                (*listaTemp)->nroAmigos[1] = contador;
                //pedimos espacio para almacenar a los amigos
                (*listaTemp)->amigos2 = (char **)malloc(contador * sizeof(char **));
                for(contador =0; contador<(*listaTemp)->nroAmigos[1];contador++){
                    (*listaTemp)->amigos2[contador] = strdup(amigos[contador]);
                }
            }

        	j++;
        	contador = 0;
        }
        free(amigos);
        fclose(filepointer);
	}
	

	
	puts("################### Hijos Hacen reduce###################");
	primera = 0;
	ultima = 0;	
    for (i = 0; i < nroProcesos; i++){
        
        primera = ultima;
        ultima = ultima + nroNodos[i];

        if ((childpid = fork()) < 0){
            perror("fork:");
            exit(1);
        } 
        
        if (childpid == 0){
            for(j = 0; j< ultima; j++){
                if(j>=primera)
                    reduceProcesos(lista);
                   
                if((*lista) != NULL)
                    *lista = (*lista)->ant;
                
            }
            exit(0);
        }
        else
        	PIDs[i] = (int)childpid;
    }	

    // El padre espera que terminen todos los hijos que creo.
    for (i = 0; i < nroProcesos; i++){
        wait(&status);
    }
    puts("################El padre escribe archivo de salida################");
    
    if(nroArchivos == 1)
    	nroArchivos++;
    	
    for (i = 0; i < nroArchivos -1; i++){
	    
	    sprintf(nombreHijo,"%d",PIDs[i]);
        strcat(nombreHijo,".txt");
        
        filepointer = fopen(nombreHijo,"r");
        
        j = 0;
        
        //Almacenamos las lineas de un archivo y las escribimos en la salida.
        while ((read = getline(&line, &len, filepointer)) != -1) {
	        fp = fopen(salida,"a");
	        fputs(line,fp);
	        fclose(fp);
        }
        fclose(filepointer);            
    }
    final = clock() - comienzo;
    
    printf("La ejecución del programa tomo: %d unidades de tiempo.\n",(int)final);       
    free(lineas);
    free(PIDs);
    free(lista);
    free(listaTemp);
    free(nroNodos);
    exit(0);
}
