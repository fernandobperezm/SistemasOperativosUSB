/**
 * main.c
 * 
 * Descripción: Este archivo contiene el ciclo principal del programa.
 * 
 * Autores: 
 * 	Br. Fernando Pérez, carné: 12-11152.
 * 	Br. Leslie Rodrigues, carné: 10-10613.
 *
 * Última modificación: 27-04-2015.
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "bases.h" 

/*
 * Es una función que verifica que las opciones presionadas por el usuario
 * sean válidas, como por ejemplo: no se llame dos veces a leer del archivo 
 * en la misma sesión ó que se hagan operaciones sin que estén los datos
 * cargados en memoria.
 * Argumentos: listas, apuntador al arreglo de las listas enlazadas.
 *             Respuesta, es un caracter que contiene la respuesta del usuario.
 *             valor, entero que dice si es primera vez que se entra a la función.
 * Retorna: un entero que dice si la operación es válida o no. Si devuelve 1 es 
 * válida, en caso contrario, devuelve 0.
 */
int verificarErrores(LISTA **listas,char Respuesta,int valor){
	//Primero verificamos si hay datos leídos de la base en memoria.
	if(listas[0] == NULL && listas[1] == NULL && listas[2] == NULL && valor != 1){
		//Como no hay nada en memoria verificamos si la respuesta fue leer de la
		//base de datos.
		if(Respuesta == '1' || Respuesta == '0')
			return 1;
		else
			printf("Lo lamentamos, no hay datos en memoria y por lo tanto no\
 puede hacer esta operación.\n");
 			printf("Será devuelto al menú principal.\n");
			return 0;
	}
	else{
		//Como si hay datos en la memoria, verificaremos que no vuelva a leer
		//del archivo.
		if(Respuesta == '1'){
			printf("Lo lamentamos, ya los datos de la base de datos se leyeron.\n");
			printf("Será devuelto al menú principal.\n");
			return 0;
		}
		else
			return 1;
	}
}


/*
 * main es la función principal del programa. En ella están las verificaciones
 * básicas del programa; como el pasaje de parámetros correctos. Además, está el
 * ciclo principal de interacción con el usuario y la base de datos.
 * Argumentos: argc, entero que cuenta los argumentos.
 *             argv, cadena de caracteres, en argv[0] está el nombre del programa,
 *                   en argv[1] está el directorio del archivo.
 *
 */
int main (int argc, char *argv[]){
    if(argc != 2){
        printf("Disculpe, el formato es ./nombreDePrograma nombreDeArchivo\n");
        printf("Vuelva a ejecutar el programa.\n");
        exit(1);
    }
    else{
        /*
         * Cuando el número de argumentos es correcto, pasamos a mostrar la
         * bienvenida al programa y enseguida mostramos las opciones. Recibiremos
         * la respuesta y con un Switch se decidirá qué hará el programa.
         */

        char Respuesta;
        int numero;
        int valor = 0;
        LISTA *listas[3];

        listas[0] = NULL; //Preguntas de complejidad 0.
        listas[1] = NULL; //Preguntas de complejidad 1.
        listas[2] = NULL; //Preguntas de complejidad 2.

        printf("Bienvidos al programa. Creadores: Fernando Pérez y Leslie\
 Rodrigues\n\n");
        
        do{
            printf("#######################################################\n");
            printf("##################      MENÚ          #################\n");
            printf("#######################################################\n");
        	printf("Para usar el menú, escriba el número de la opción que quiera\
 que el programa realice.");
        	printf("\n");
        	printf("\tOpción 1: Leer los datos de la base de datos.\n");
        	printf("\tOpción 2: Consultar la base de datos.\n");
        	printf("\tOpción 3: Consultar la base de datos por complejidad.\n");
        	printf("\tOpción 4: Eliminar una pregunta.\n");
        	printf("\tOpción 5: Insertar una pregunta.\n");
        	printf("\tOpción 6: Salvar los cambios en la base de datos.\n");
        	printf("\tOpción 0: Salir del sistema.\n\n");

            scanf("%c",&Respuesta);
            getchar();
            if(verificarErrores(listas,Respuesta,valor)){
		        switch(Respuesta){
		            case '1':
		                printf("#######################################################\n");
                        printf("##################    LEER ARCHIVO    #################\n");
                        printf("#######################################################\n");
		            	LeerArchivo(argv[1],&listas[0]);
		                valor = 1;
		                printf("A continuación será regresado al menú principal.\n\n");
		                break;
		            case '2':
		                printf("#######################################################\n");
                        printf("###############    CONSULTAR TODOS DATOS  #############\n");
                        printf("#######################################################\n");
		            	ConsultarComplejidad(&listas[0],0);
		            	ConsultarComplejidad(&listas[0],1);
		            	ConsultarComplejidad(&listas[0],2);
		            	printf("A continuación será regresado al menú principal.\n\n");
		                break;
		            case '3':
		                printf("#######################################################\n");
                        printf("###############     CONSULTA POR NIVEL    #############\n");
                        printf("#######################################################\n");
		                printf("Indique el nivel de complejidad que quiera consultar\n");
		                scanf("%d",&numero);
		                getchar();
		                ConsultarComplejidad(&listas[0],numero);
		                printf("A continuación será regresado al menú principal.\n\n");
		                break;
		            case '4':
		                printf("#######################################################\n");
                        printf("###############   ELIMINAR UNA PREGUNTA   #############\n");
                        printf("#######################################################\n");
		                printf("Introduzca el codigo de la pregunta que desea eliminar: ");
		                scanf("%d",&numero);
		                getchar();
		                printf("\n");
		                EliminarPregunta(numero,&listas[0]);
		                printf("A continuación será regresado al menú principal.\n");
		                break;
		            case '5':
		                printf("#######################################################\n");
                        printf("###############   INSERTAR UNA PREGUNTA   #############\n");
                        printf("#######################################################\n");
		            	InsertarPregunta(&listas[0]);
		            	printf("A continuación será regresado al menú principal.\n\n");
		                break;
		            case '6':
		                printf("#######################################################\n");
                        printf("###############      SALVAR LOS DATOS     #############\n");
                        printf("#######################################################\n");
		                Salvar(argv[1],&listas[0]);
		                printf("A continuación será regresado al menú principal.\n\n");
		                break;
		            case '0':
		                printf("#######################################################\n");
                        printf("###############     SALIR DEL SISTEMA     #############\n");
                        printf("#######################################################\n");
                        Salvar(argv[1],&listas[0]);
                        printf("Esperamos que el sistema haya sido de su agrado. Hasta pronto.\n");
		                break;
		            default:
		                printf("El caracter %c no es válido. Introduzca nuevamente la\
 opción\n",Respuesta);

           		}
            }
        } while(Respuesta != '0');
        exit(0);
    }
}
