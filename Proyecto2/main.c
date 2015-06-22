/*
 * main.c
 * 
 * Descripción: Este archivo contiene el ciclo principal del programa.
 *
 * Autores: 
 * 	Br. Fernando Pérez, carné: 12-11152.
 * 	Br. Leslie Rodrigues, carné: 10-10613.
 *
 * Última modificación:
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
#include "sistemaDeArchivos.h"

/*
 * verificarConjunto es una función que determina, dado un arreglo, y un número
 * aleatorio, si el mismo está en el arreglo. 
 *
 * Argumentos: numero, entero a verificar si está en el conjunto.
 *			   arreglo, arreglo de enteros donde buscar.
 * 			   tamano, entero que especifica el tamaño del arreglo.
 *
 * Retorna: 0 si no está en el conjunto, 1 si está en el conjunto.
 */
int verificarConjunto(int numero, int arreglo[], int tamano){
	int i;
	for(i = 0; i< tamano; i++){
		if(numero == arreglo[i])
			return 1;
	}
	return 0;
}


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
    int status = 0;   //estado del hijo
    
    int nroFilesT = 0; //número de archivos que el hijo transfirió al padre
    int nroDirs = 0; //número de directorios a los que se accedió 
    
    int *aleatoriosPadre = NULL;//almecena los n numeros aletorios generados por el padre 
    int *aleatoriosHijo = NULL;//almecena los m numeros aletorios generados por el padre    
                  
    char *temp = NULL;  //Variable temporal
    char *temp2 = NULL; //Variable temporal
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
    
    if(argc == 4){
    
        //convertimos segundo y tercer argumentos a enteros
        n = strtol(argv[1],&temp,10); 
        m = strtol(argv[2],&temp2,10);
        
        //verificamos que el segundo y tercer arguento sean enteros
        if (strcmp(temp,"") || strcmp(temp2,"")){
            printf("\nError. El formato correcto para correr el programa es:\n");
            printf("MiCuento [-d directorio] <n> <m> <salida>\n\n");
            printf("donde <n> y <m> son enteros no negativos.\n");
            
            exit(1);        
        }
        
         
        salida = strdup(argv[3]);
        
        directorio = ".";
    } else if (argc == 6){

        //verificamos que se introdujo un flag válido
        if (strcmp(argv[1],"-d")){
            printf("Error. %s NO es una opción válida.\n",argv[1]);
            exit(1);
        }
        
        directorio = (argv[2]);
        
        if (stat(directorio, &statbuf) != -1){
        	if (statbuf.st_mode & S_IFDIR){	
        	}else{
        		
        		printf("Error.\n%s  NO es un directorio.\n",directorio);
        		exit(1);
        	}
        } else{
        	
        	printf("Error.\n%s  NO es un directorio.\n",directorio);
        	exit(1);
        }
        
        
        n = strtol(argv[3],&temp,10);
        m = strtol(argv[4],&temp2,10);
        
        
         
        salida = strdup(argv[5]);        
    
    } else {
        printf("\nError. El formato correcto para correr el programa es:\n");
        printf("MiCuento [-d directorio] <nrocarpetas> <nroarchivos> <salida>\n");
    }


	//verificamos que <m> y <n> sean enteros
    if (strcmp(temp,"") || strcmp(temp2,"")){
        printf("\nError. El formato correcto para correr el programa es:\n");
        printf("MiCuento [-d directorio] <n> <m> <salida>\n\n");
        printf("donde <n> y <m> son enteros no negativos.\n");
        exit(1);        
    }
        
        //verificamos que <n> sea mayor o igual a 0
        //y menor o igual a 10
        if ((n < 0) || (n > 10)){
            printf("\nError. El formato correcto para correr el programa es:\n");
            printf("MiCuento [-d directorio] <n> <m> <salida>\n\n");
            printf("donde <n> es un enteros no negativo menor o igual a 10.\n");
            exit(1);
        } 
        
        //verificamos que <m> sea mayor o igual a 0
        //y menor o igual a 20
        if ((m < 0) ||(m > 20)){
            printf("\nError. El formato correcto para correr el programa es:\n");
            printf("MiCuento [-d directorio] <n> <m> <salida>\n\n");
            printf("donde <n> es un enteros no negativo menor o igual a 10.\n");
            exit(1);
        }

	
	if (n == 0){
		printf("El número de directorios es 0.\n");
		printf("Finaliza el programa.\n");
		exit(0);
	}
	
	if (m == 0){
		printf("El número de archivos a leer es 0.\n");
		printf("Finaliza el programa.\n");
		exit(0);
	}

    ////////////////////////////////////////////////////////////////////////////
   
    //pedimos memoria
    aleatoriosPadre = (int *)malloc(sizeof(int)*n);
    aleatoriosHijo = (int *)malloc(sizeof(int)*m);
    rutaDir = (char *)malloc(strlen(directorio) + 3);
    directorios = (int *) malloc(sizeof(int *)*10);
    archivos = (int *) malloc(sizeof(int)*20);
    
    //Se inicializan los números aleatorios que generará el padre
 	//y arreglo que almacena los números asociados a los directorios a los 
 	//cuales ya intento acceder   
    for(i = 0; i < 10; i++){
    	if(i < n)
    		aleatoriosPadre[i] = 0;
    	directorios[i] = 0;
    }
    
    //Se inicializan los números aleatorios que generará el hijo padre
    //y arreglo que almacena los números asociados a los archivos a los 
 	//cuales ya intento accede	
    for(i = 0; i < 20; i++){
    	if(i < m)
    		aleatoriosHijo[i] = 0;
    	archivos[i] = 0;
    }
    
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
    
    
    
    if(nroDirs == 0){
    	puts("No se encontró ningún directorio.");
    	puts("Se finalizará el programa.");
    	exit(0);
    } 
    
    //se reinicializa el nro de intentos en 0
    nroIntentos = 0;
    
    //Creamos el pipe.
    if (pipe(pipefd) == -1) {
    	perror("pipe");
        exit(EXIT_FAILURE);
    }
    
    for(i = 0; i < n; i++){
    	printf("%d\n",aleatoriosPadre[i]);
    }
    
    i = 0;
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
    }

    
	dup2(pipefd[0], STDIN_FILENO);
    close(pipefd[1]);
    close(pipefd[0]);
	
	//Se abre el archivo de salida
	salidafd = open(salida,O_WRONLY|O_CREAT,0600);	
	
	//se lee del pipe
	while(read(0,&buffer,1) > 0){
		write(salidafd,&buffer,1);
	}
	close(salidafd);//se ciera el archivo de salida
	
	//el padre espera por sus hijos
	for (i = 0; i < n; i++){
        wait(&status);
	}

	//liberamos memoria
	free(archivos);
    free(aleatoriosPadre);
    free(aleatoriosHijo);
    free(rutaDir);
    free(directorios);
    free(salida);

    exit(0);
}
