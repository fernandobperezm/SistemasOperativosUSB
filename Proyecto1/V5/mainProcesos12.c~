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

typedef  struct lista {
    char *nombre[2];
    char **amigos1;
    char **amigos2;
    char **comunes;
    struct lista *sig;
    struct lista *ant;
} LISTA;


/*
 * insertar es un procedimiento que añade una pregunta a la lista enlazada. 
 * La inserción se hace al final de la lista y se actualiza el puntero al último
 * elemento.
 * Argumentos: ultimo, es un apuntador a la última posición de la lista.
 * 			   pregunta, es el tipo PREGUNTA que se va a añadir.
 * Retorna: nada, las modificaciones las hace a la lista enlazada en memoria.
 */
void insertar(LISTA **ultimo,char *nombre1,char *nombre2, char **amigos){
    LISTA *nuevo;
    nuevo = (LISTA *) malloc(sizeof(LISTA));

    if (*ultimo != NULL)
        (*ultimo)->sig = nuevo;

    nuevo->nombre[0] = strdup(nombre1);
    printf("%s",nuevo->nombre[0]);
    nuevo->nombre[1] = strdup(nombre2);
    //nuevo->amigos1 = malloc(sizeof(amigos));
    nuevo->amigos1 = amigos;
    
    nuevo->ant = *ultimo;
    *ultimo = nuevo;
}

LISTA **buscar(LISTA **ultimo, char *nombre1, char *nombre2){
    LISTA **list;
    list = ultimo;

    while(*list != NULL){
        if (((*list)->nombre[0]) == nombre1 && (((*list)->nombre[1]) == nombre2)){
            return list;
        }
        list = &(*list)->ant;
    }
    return NULL;
}
void mapProcesos(char *linea){

    //char* lineaIntro = (char*) linea;
    char *temp; 
    char *persona[1];
    char **amigos = NULL; //arreglo de amigos
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
        amigos[nroAmigos] = (char*)malloc(sizeof(temp));
       
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

void reduce(LISTA **l){
/**    int i,j;
    
    
    if((l->amigos1 != NULL)&&(l->amigos2 != NULL)){
        for(i = 0; i < sizeof(l->amigos1); i++){
            for(j = 0; i < sizeof(l->amigos2); j++){
                if((l->amigos1[i] != l->nombre1) && (l->amigos1[i] != l->nombre2)){
                    if((l->amigos2[j] != l->nombre1) && (l->amigos2[j] != l->nombre2))
                        if(l->amigos1[j] == l->amigos2[j]){
                            //agregamos a amigos en comun 
                        }
                }
            }
        }
    }*/
}

int main(int argc, char *argv[]){
	int nroProcesos = atoi(argv[1]);
	char *nombreArchivo = argv[2];
	//int contador = 0;
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
    }
    
    printf("Numero de lineas del archivo = %d\n",lineasTotales);
    puts("El archivo contiene lo siguiente: \n");
    for(i = 0; i<lineasTotales; i++)
        puts(*(lineas+i));
    
    //free(line);
    
    int j;
    //creacion de hijos    
    //puts(*lineas);
    
    PIDs = (int *)malloc(sizeof(int *) * nroProcesos);
    
    //int pid[nroProcesos]
    int primera = 0;
    int ultima = 0;
    //int aja[nroProcesos][2];
    //int k;
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
        else{ 
            PIDs[i] = (int ) malloc(sizeof(int));
        
            //Guardamos el PID del hijo.
        	PIDs[i] = (int)childpid;
        	//printf("aquiiiiiiiiiiiiiiiiiiiiiii %d\n",PIDs[i]);
        }

    }
     
  
           
    
    // El padre espera que terminen todos los hijos que creo.
    for (i = 0; i < nroProcesos; i++){
        wait(&status);
    }

	fclose(filepointer);
	printf("Hemos terminado de leer el archivo.\n");
	
	
	char *nombre1;
	char *nombre2;
	char **amigos;
	char nombreHijo[10];
	char *temp;
	int nroAmigos;
	
	
    LISTA **lista;
    lista = malloc(sizeof(LISTA **));
    *lista = NULL;
    
    LISTA **listaTemp;
    listaTemp = malloc(sizeof(LISTA **));
    *listaTemp = NULL;
	
	puts("##############EL PADRE LEE!!###########");
	
    lineasTotales = 0;//nro de nodos
    
 	//inicializamos el numero de nodos a asignar a cada proceso en 0
	for(i= 0; i < nroProcesos; i++ )
	    nroLineas[i] = 0;
	       
	
	//Ahora pasamos a la lectura de todos los archivos que los hijos crearon.
	for (i = 0; i < nroProcesos; i++){
	    
	    sprintf(nombreHijo,"%d",PIDs[i]);
        strcat(nombreHijo,".txt");
        
        filepointer = fopen(nombreHijo,"r");
        
        
        amigos = (char **)malloc(sizeof(char **) * nroLineas[i]);//pedimos memoria
        
        j = 0;
        
        //almacenamos las lineas
        while ((read = getline(&line, &len, filepointer)) != -1) {
	        
	        if(j == 5){
	            j = 0;
	        }
	        
	        temp = strdup(line);//copiamos la linea leida en un temporal
	        
	        // temp = strdup(line);//copiamos la linea leida en un temporal
	        
	        temp = strtok(temp," ");
	        
	        nombre1 = strdup(temp);
	        
	        temp = strtok(NULL," ");
	        
	        nombre2 = strdup(temp);
	        
	        temp = strtok(NULL," "); //la flecha
	        
	        nroAmigos = 0;
	        while((temp = strtok(NULL, " "))!=NULL){
                
                *(amigos + nroAmigos) = strdup(temp);
                nroAmigos++;
                
            }
            nombre1 = strtok(nombre1,"(");//quitamos el "(" del nombre
            
            
            nombre2 = strtok(nombre2,")");//quitamos el ")" del nombre
            
            puts("llegue");
            
            
            //insertar(lista,nombre1,nombre2,amigos);
            //puts((*lista)->nombre[1]);
                
            //lineasTotales++;//se incrementa el numero de nodos
            
            //lista = (LISTA **)realloc(lista,sizeof(LISTA **)*lineasTotales);
            
            //INSERTAMOS EN LA ESTRUCTURA ###################################
            
             
            listaTemp = buscar(lista,nombre1,nombre2);
            if (listaTemp == NULL){
                insertar(lista,nombre1,nombre2,amigos);
                
                lineasTotales++;//se incrementa el numero de nodos
                nroLineas[j]++;
            }else{
                (*listaTemp)->comunes = amigos;
            }
            //################################################################
        }       
        
        
        fclose(filepointer);
	}
	
	puts("###################HIJOS HACEN REDUCE###################");
	
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
                //MANDAMOS A HACER REDUCE Y CORREMOS LA LISTA #################
                /*
                reduceProcesos(lista);
                if(lista->ant != NULL)
                    lista = lista->ant;
                    
                */
                //##############################################################
                primera++;
            }
            exit(0);
        }
        else{ 
            //PIDs[i] = (int ) malloc(sizeof(int));
        
            //Guardamos el PID del hijo.
        	PIDs[i] = (int)childpid;
        	//printf("aquiiiiiiiiiiiiiiiiiiiiiii %d\n",PIDs[i]);
        }

    }	


    
    exit(0);
}
