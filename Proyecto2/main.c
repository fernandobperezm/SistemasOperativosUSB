/*
 * main.c
 * 
 * Descripción: Este archivo contiene el ciclo principal del programa.
 *
 * Autores: 
 * 	Br. Fernando Pérez, carné: 12-11152.
 * 	Br. Leslie Rodrigues, carné: 10-10613.
 *
 * Última modificación: 22-06-2015.
 */

//Inclumimos las librerías que necesitaremos.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <dirent.h> 
#include <fcntl.h>
#include "funcionesAuxiliares.h"

/*
 * main es el ciclo principal del programa.
 *
 * Argumentos: argc, es el contador de argumentos pasados por entrada estándar.
 * 			   argv, contiene los distintos argumentos pasados por entrada estándar.
 * Retorna: 0 si termina con éxito, otro entero en cualquier otro caso.
 */
int main(int argc, char *argv[]){
    int n;  //valor que el padre debe considerar y número de procesos a crear.        
    int m;  //archivos que los procesos hijos deben considerar 
    char *salida;  //nombre del archivo de salida 
    char *directorio; //directorio donde se encuentran los archivos de texto 
    char *rutaDir; //almacena el path
    
    pid_t childpid;
    pid_t *pidHijos;
    int status = 0;   //estado del hijo
    
    int nroFilesT = 0; //número de archivos que el hijo transfirió al padre
    int nroDirs = 0; //número de directorios a los que se accedió 
    
    int *aleatoriosPadre = NULL;//almecena los n numeros aletorios generados por el padre 
    int *aleatoriosHijo = NULL;//almecena los m numeros aletorios generados por el padre    
                  
    char *nombre = NULL;  
    int i,j; //contadores
    int filedescriptor;
    
    int numeroAleatorio = -1; //Aquí se guarda temporalmente el número aleatorio.
    int estaEnConjunto = -1; //Booleano que dice si el numero esta en el conjunto.
    
    int pipefd[2]; //Aquí se guardan los descriptores de archivo del pipe.
    char buffer; //Guardará los caracteres que se lean del pipe.
    char *textoHijo = ""; //Aquí se almacenará lo que se reciba por un buffer.
    
    int salidafd; //Descriptor del archivo de salida.
    
    struct stat statbuf;
 	
 	int longitud;
 	int *directorios;//Almacena los números asociados a los directorios
 					 //a los que ya se se entró o intento entrar
 	int *archivos;   //Almacena los números asociados a los directorios
 					 //a los que ya se se entró o intento entrar
    int nroIntentos = 0; //número de archivos o directorios a los que se intento acceder
	
	verificarArgumentos(&n, &m, &salida, &directorio,statbuf, argc, argv);   
    
    ////////////////////////////////////////////////////////////////////////////
   
    //pedimos memoria
    aleatoriosPadre = (int *)malloc(sizeof(int)*n);
    aleatoriosHijo = (int *)malloc(sizeof(int)*m);
    rutaDir = (char *)malloc(strlen(directorio) + 3);
    directorios = (int *) malloc(sizeof(int *)*10);
    archivos = (int *) malloc(sizeof(int)*20);
    pidHijos = (pid_t *) malloc(sizeof(pid_t)*n);
 
    //Se inicializan los números aleatorios que generará el padre
 	//y arreglo que almacena los números asociados a los directorios a los 
 	//cuales ya intento acceder
 	inicializarArreglo(aleatoriosPadre, n);
 	inicializarArreglo(aleatoriosHijo, m);
    inicializarArreglo(directorios, 10);
 	inicializarArreglo(archivos, 20); 
        
    srand(getpid());
    //El padre genera n numeros aleatorios (mayores que 0 y menores o iguales a 10)
    // y los almacena en un arreglo que actúa como conjunto. y |conjunto| = n.
    for(i = 0; i< n; i++){
        do{
     
     		//se genera un numero aleatorio entre 0 y 10
        	numeroAleatorio = rand() % (11);
        	
  			//Se verifica si ya se intento acceder al directorio asociado
  			//al numero aleatorio generado
        	estaEnConjunto = verificarConjunto(numeroAleatorio,directorios, 10);
        	 
        	if(!estaEnConjunto && (numeroAleatorio != 0)){
        		
        		//se almacena el número asociado al directorio al que se intentará
        		//acceder
        		directorios = directorios + nroIntentos;
        		*directorios = numeroAleatorio;
        		directorios = directorios - nroIntentos;
        		
        		//se incrementa el numero de archivos al que se ha intentado acceder        		
        		nroIntentos++;
        		
        		//se almacena la ruta del directorio al que se intetará acceder
        		sprintf(rutaDir,"%s/%d",directorio,numeroAleatorio);
        		
        		//Se verifica que sea un archivo de tipo directorio
        		if (stat(rutaDir, &statbuf) != -1){
        			if (statbuf.st_mode & S_IFDIR){
        			
        				aleatoriosPadre[i] = numeroAleatorio;	
        				nroDirs++;
        			}
        		}
        		
        	}
        	
        } while((aleatoriosPadre[i] == 0) && (nroIntentos < 10) );
    }
    
    
    //En caso de que no haya carpetas para ingresar.
    if(nroDirs == 0){
    	puts("No se encontró ningún directorio.");
    	puts("Se finalizará el programa.");
    	exit(1);
    } 
    
    //se reinicializa el número de intentos en 0
    nroIntentos = 0;
    
    //Creamos el pipe.
    if (pipe(pipefd) == -1) {
    	perror("pipe");
        exit(EXIT_FAILURE);
    }
    
    //creación de los hijos
    for(i = 0; i< n; i++){
       if ((childpid = fork()) < 0) {
           perror("fork:");
           exit(1);
       }
       
        // Código que ejecutarán los hijos
        if (childpid == 0) { 
            if (aleatoriosPadre[i] == 0){
        			exit(nroFilesT);
        	}
               
        	dup2(pipefd[1], STDOUT_FILENO);
        	close(pipefd[0]);
        	close(pipefd[1]);
        	
            //Calculamos la longitud de la ruta           
            longitud = strlen(directorio) + 6;
            //pedimos memoria
			nombre = (char *) malloc(longitud * sizeof(char));
			
			srand(getpid());
			for(j = 0; j < m; j++){	        		
           		do{
           			//Se genera un numero aleatorio entre 0 y 20
           			numeroAleatorio = rand() % (21);
           			//se almacena la ruta 
           			sprintf(nombre,"%s/%d/%d",directorio,aleatoriosPadre[i],numeroAleatorio);	
           			
        			//se determina si ya se intento acceder al archivo asociado
        			//al numero aleatorio
           			estaEnConjunto = verificarConjunto(numeroAleatorio,archivos, 20); 
           			
           			if(!estaEnConjunto && (numeroAleatorio != 0)){
           				//se almacena el numero asociado al archivo
           				archivos = archivos + nroIntentos;
           				*archivos = numeroAleatorio;
           				archivos = archivos - nroIntentos;
           		
           				//se incrementa el numero de archivos al que se ha 
           				//intentado acceder
           				nroIntentos++;
           				
           				//Se verifica que el archivo sea de tipo regular						
           				if (stat(nombre, &statbuf) != -1){
        					if (statbuf.st_mode & S_IFREG){	
        						//se lee el archivo y su contenido se almacena
        						//en el pipe
        						leerArchivo(nombre);
        						nroFilesT++;	
        						aleatoriosHijo[j] = numeroAleatorio; 
        					}
        				}
            		}
            	}while((aleatoriosHijo[j] == 0) && nroIntentos < 20);		
            }
            //liberamos memoria   
            free(nombre);
            exit(nroFilesT);   
        }
        //Código que ejecutará el padre.
        else
        	pidHijos[i] = childpid;	
    }

    //Cambiamos la entrada estándar por el pipe en el modo de lectura.
	dup2(pipefd[0], STDIN_FILENO);
    close(pipefd[1]);
    close(pipefd[0]);
	
	//Se abre el archivo de salida
	salidafd = open(salida,O_WRONLY|O_CREAT,0600);	
	printf("El cuento aleatorio es: \n");
	
	//se lee del pipe
	while(read(0,&buffer,1) > 0){
		write(STDOUT_FILENO, &buffer, 1); //Se escribe en pantalla.
		write(salidafd,&buffer,1); //Se escribe en el archivo.
	}
	close(salidafd);//se ciera el archivo de salida
	
	//el padre espera por sus hijos
	printf("\n\n\nLa información de los procesos es la siguiente: \n");
	for (i = 0; i < n; i++){
        waitpid(pidHijos[i],&status,0);
        nroFilesT = status / 256;
       	printf("El hijo %d procesó %d archivos.\n",pidHijos[i], nroFilesT);
	}

	//liberamos memoria
	free(archivos);
    free(aleatoriosPadre);
    free(aleatoriosHijo);
    free(rutaDir);
    free(directorios);
    free(salida);
    free(pidHijos);

    exit(0);
}
