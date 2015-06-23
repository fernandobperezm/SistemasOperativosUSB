/*
 * funcionesAuxiliares.c
 * 
 * Descripción: Este archivo contiene las funciones y procedimientos de
 * operaciones auxiliares al programa principal, tales como inicialización de 
 * arreglos, escritura en PIPE, verificación de argumentos, entre otros.
 *
 * Autores: 
 * 	Br. Fernando Pérez, carné: 12-11152.
 * 	Br. Leslie Rodrigues, carné: 10-10613.
 *
 * Última modificación: 22-06-2015.
 */
 
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h> 
#include <dirent.h>
#include <fcntl.h>

/*
 * leerArchivo abre, lee el contenido y cierra un archivo, además escribe en 
 * la salida estándar (que para el uso de esta función es el pipe entre los hijos
 * y el padre) el contenido del mismo.
 *
 * Argumentos: nombre, ruta y nombre del archivo a abrir. 
 *
 * Retorna: nada, escribe en el pipe el contenido del archivo al padre.
 */
void leerArchivo(char *nombre){
    int fd = 0;
    int charsRead; //número de carácteres leídos
    off_t offset;
    int nroChars; //número de carácteres que contiene el archivo 
    char *buffer;
    int archivoprueba;
    
    //Se abre el archivo.
    fd = open(nombre, O_RDONLY);
    
    //movemos el offset al final del archivo para determinar la
    //cantidad de caracteres
   	offset = 0;
    nroChars = lseek(fd, offset,SEEK_END);
    
    //movemos el offset al inicio del archivo
    lseek(fd, offset,SEEK_SET);  
    
    //pedimos memoria
    buffer = (char *) malloc(sizeof( char)* nroChars);
    //Se lee archivo.
    charsRead = read(fd, buffer, nroChars); 
	//Se escribe en el pipe.
	write(STDOUT_FILENO, buffer, charsRead);
	
    free(buffer);
    close(fd);
}

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
 * verificarArgumentos verifica que los argumentos de la entrada sean correctos.
 *
 * Argumentos: n, dirección de la cantidad de procesos a considerar.
 * 			   m, dirección de la cantidad de archivos a considerar.
 * 			   salida, dirección de dónde se va a guardar la ruta y el nombre del
 *				       archivo de salida.
 *			   directorio, dirección de dónde se va a guardar el directorio de entrada.
 * 			   statbuf, estructura de stat para poder usar la función de stat.
 * 		       argc, número de argumentos de la entrada.
 *             argv, argumentos de la entrada. 
 *
 * Retorna: Nada, los cambios los hace en n,m,salida, y directorio.
 */
void verificarArgumentos(int *n, int *m, char **salida,char **directorio, struct stat statbuf, int argc, char *argv[]){
    char *temp = NULL;  //Variable temporal
    char *temp2 = NULL; //Variable temporal
    
	if(argc == 4){
		    //convertimos segundo y tercer argumentos a enteros
		    *n = strtol(argv[1],&temp,10); 
		    *m = strtol(argv[2],&temp2,10);
		    
		    //verificamos que el segundo y tercer arguento sean enteros
		    if (strcmp(temp,"") || strcmp(temp2,"")){
		        printf("\nError. El formato correcto para correr el programa es:\n");
		        printf("MiCuento [-d directorio] <n> <m> <salida>\n\n");
		        printf("donde <n> y <m> son enteros no negativos.\n");
		        exit(1);        
		    }
		    
		    *salida = strdup(argv[3]);
		    *directorio = ".";
		    
		} else if (argc == 6){
		    //verificamos que se introdujo un flag válido
		    if (strcmp(argv[1],"-d")){
		        printf("Error. %s NO es una opción válida.\n",argv[1]);
		        exit(1);
		    }
		    
		    *directorio = (argv[2]);
		    
		    if (stat(*directorio, &statbuf) != -1){
		    	if (statbuf.st_mode & S_IFDIR){	
		    	}else{
		    		
		    		printf("Error.\n%s  NO es un directorio.\n",*directorio);
		    		exit(1);
		    	}
		    } else{
		    	
		    	printf("Error.\n%s  NO es un directorio.\n",*directorio);
		    	exit(1);
		    }
		    
		    
		    *n = strtol(argv[3],&temp,10);
		    *m = strtol(argv[4],&temp2,10);
		     
		    *salida = strdup(argv[5]);        
		
		} else {
		    printf("\nError. El formato correcto para correr el programa es:\n");
		    printf("MiCuento [-d directorio] <nrocarpetas> <nroarchivos> <salida>\n");
		    exit(1);
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
		    if ((*n < 0) || (*n > 10)){
		        printf("\nError. El formato correcto para correr el programa es:\n");
		        printf("MiCuento [-d directorio] <n> <m> <salida>\n\n");
		        printf("donde <n> es un entero no negativo menor o igual a 10.\n");
		        exit(1);
		    } 
		    
		    //verificamos que <m> sea mayor o igual a 0
		    //y menor o igual a 20
		    if ((*m < 0) || (*m > 20)){
		        printf("\nError. El formato correcto para correr el programa es:\n");
		        printf("MiCuento [-d directorio] <n> <m> <salida>\n\n");
		        printf("donde <m> es un entero no negativo menor o igual a 20.\n");
		        exit(1);
		    }

	
		if (*n == 0){
			printf("El número de directorios es 0.\n");
			printf("Finaliza el programa.\n");
			exit(0);
		}
	
		if (*m == 0){
			printf("El número de archivos a leer es 0.\n");
			printf("Finaliza el programa.\n");
			exit(0);
		}

}

/*
 * inicializarArreglo escribe en un arreglo dado el valor 0 en todas sus casillas.
 * 
 * Argumentos: arreglo, el arreglo a inicializar.
 *             tamano, entero que especifica el tamaño del arreglo.
 *
 * Salida: ninguna, los cambios los hace en memoria.
 */
void inicializarArreglo(int arreglo[], int tamano){
	int i;
	for(i = 0;i < tamano; i++)
		arreglo[i] = 0;
}
