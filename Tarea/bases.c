/**
 * Bases.c
 * 
 * Descripción: Este archivo contiene las funciones y procedimientos principales
 * para el manejo de las preguntas en las bases de datos.
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

#include "listaEnlazada.h"

/*
 * LeerArchivo es el procedimiento que abre el archivo, crea una pregunta, lee 
 * línea por línea y los datos los guarda en la pregunta, ésta se insera en
 * alguna de las tres listas enlazadas que están en memoria y al acabarse el
 * archivo, lo cierra.
 * Argumentos: nombre, es un String que tiene el nombre del archivo.
 * 			   listas, es un apuntador al arreglo de listas enlazadas en memoria.
 * Retorna: nada, se modifican directamente las listas enlazadas.
 */
void LeerArchivo(char nombre[], LISTA **listas){
    FILE *filepointer;
    PREGUNTA P;
        
    filepointer = fopen(nombre,"r");
    if(filepointer == NULL){
    	perror("Lo lamentamos");
    	printf("Vuelva a ejecutar el programa con el nombre del archivo correcto.\n");
    	printf("errno = %d\n",errno);
    	exit(1);
    }
    printf("Abriendo el archivo...\n");
    
    printf("Leyendo los datos de la base de datos...\n");
    
    while(
     fscanf(filepointer,"%d %d %c \"%[^\"]\" \"%[^\"]\" \"%[^\"]\" \"%[^\"]\" %d ",&P.codigo,&P.complejidad,&P.area,P.strings[0],P.strings[1],P.strings[2],P.strings[3],&P.respuestaCorrecta) != EOF){
    	insertar(&listas[P.complejidad],P);
    	
   	}
    
    fclose(filepointer);
    
    printf("Hemos terminado de leer el archivo.\n");
}

/*
 * MostrarPregunta le muestra al usuario en consola los datos de la pregunta que
 * se recibe de argumento.
 * Argumentos: P, es la pregunta que se desea mostrar al usuario.
 * Retorna: nada, sólo se imprime en pantalla los atributos de la pregunta.
 */
void mostrarPregunta(PREGUNTA P){

    printf("\tCódigo: %d\n",P.codigo);
    printf("\tÁrea: %c\n",P.area);
    printf("\tNivel de complejidad: %d\n",P.complejidad);
    printf("\tPregunta: %s\n",P.strings[0]);
    printf("\tRespuesta1: %s\n",P.strings[1]);
    printf("\tRespuesta2: %s\n",P.strings[2]);
    printf("\tRespuesta3: %s\n",P.strings[3]);
    printf("\tEntero correspondiente a la respuesta correcta: %d\n\n\n\n",P.respuestaCorrecta);

}

/*
 * ConsultarComplejidad determina, para una complejidad dada, si hay elementos en
 * la lista correspondiente a la misma. Si la lista tiene elementos, se llama
 * al procedimiento de mostrarPregunta, en caso contrario, imprime en pantalla
 * que la lista no tiene elementos de esa complejidad.
 * Argumentos: listas, es un apuntador al arreglo de listas enlazadas en memoria.
 * 			   complejidad, es un String que tiene el nombre del archivo.
 * Retorna: nada, en ambos casos, imprime un mensaje en pantalla.
 */
void ConsultarComplejidad(LISTA **listas, int complejidad){
    LISTA *temp;
    temp = listas[complejidad];

    if (temp == NULL){
        printf("No existen preguntas en la base de datos con nivel complejidad %d.\n",complejidad);
    } 
    else{
        printf("PREGUNTAS de complejidad %d \n",complejidad);
    }

    while (temp != NULL){

        mostrarPregunta((temp)->preg);
        temp = (temp)->ant;
    }
}

/*
 * EliminarPregunta es un procedimiento que se encarga de eliminar una pregunta
 * de las listas en memoria, esto lo hace ejecutando la función eliminar. Si no
 * existía la pregunta, imprime en pantalla un mensaje de error, en caso contrario,
 * imprime en pantalla que la pregunta fue eliminada con éxito.
 * Argumentos: código, entero que representa el código de la pregunta a eliminar.				 
 * 			   listas, es un apuntador al arreglo de listas enlazadas en memoria.
 * Retorna: nada, las modificaciones las hace en memoria e imprime en pantalla
 * si la pregunta fue removida exitosamente.
 */
void EliminarPregunta(int codigo, LISTA **listas){
    int eliminado = 0;
    int i = 0;
    
    //Buscamos sobre las tres listas la pregunta.
    while((i < 3) && eliminado == 0){
        if (listas[i] != NULL)
            eliminado = eliminar(&listas[i],codigo);
        i++;
    }

    //Se imprime el mensaje al usuario.
    if(eliminado == 0){
        printf("En la base de datos no existe una pregunta con el código: %d\n",codigo);
    } 
    else {
        printf("La pregunta ha sido eliminada con exito.\n");
    }
}

/*
 * InsertarPregunta le pregunta al usuario los datos necesarios para añadir una
 * pregunta a alguna de las listas enlazadas que están en memoria. 
 * Argumentos: listas, es un apuntador al arreglo de listas enlazadas en memoria.
 * Retorna: nada, las modificaciones las hace en memoria.
 */
void InsertarPregunta(LISTA **listas){
    PREGUNTA P;
    int continuar;
    
    do{
        printf("A continuación, introduzca los atributos que se le piden.\n");

        printf("\tCódigo: ");
        scanf("%d",&P.codigo);
        getchar();

        printf("\n");

        printf("\tÁrea(H,G,T,C ó L): ");
        scanf("%c",&P.area);

        printf("\n");

        printf("\tNivel de complejidad(0, 1 ó 2): ");
        scanf("%d",&(P.complejidad));
        getchar();

        printf("\n");


        printf("\tPregunta: ");
        scanf("%[^\n]",P.strings[0]);
        getchar();

        printf("\n");

        printf("\tRespuesta1: ");
        scanf("%[^\n]",P.strings[1]);
        getchar();

        printf("\n");

        printf("\tRespuesta2: ");
        scanf("%[^\n]",P.strings[2]);
        getchar();

        printf("\n");

        printf("\tRespuesta3: ");
        scanf("%[^\n]",P.strings[3]);
        getchar();

        printf("\n");

        printf("\tEntero correspondiente a la respuesta correcta: ");
        scanf("%d",&P.respuestaCorrecta);
        getchar();

        printf("\n");

        printf("Los datos que introdujo son: \n\n");
        mostrarPregunta(P);
        printf("Escriba 0 si los datos son correctos o 1 si son incorrectos: ");

        scanf("%d",&continuar);
        getchar();
        printf("\n\n");

        

        if (!continuar){
            insertar(&listas[P.complejidad],P);
        }
    } while (continuar);
    
    printf("La pregunta se ha añadido correctamente.\n");
}


/*
 * Salvar es la opción para pasar de memoria a disco los datos modificados en
 * la sesión de trabajo, recibe el nombre del archivo y lo sobreescribe en disco
 * en este archivo, imprime todas las preguntas que estban en las listas.
 * Argumentos: nombre, es un String que tiene el nombre del archivo.
 * 			   listas, es un apuntador al arreglo de listas enlazadas en memoria.
 * Retorna: nada, las modificaciones las hace en disco.
 */
void Salvar(char *nombre,LISTA **listas){
    int i = 0;
    FILE *fp;
    LISTA *temp;
    PREGUNTA p;

    fp = fopen(nombre, "w");
    
    if(fp == NULL){
    	perror("Lo lamentamos");
    	printf("errno = %d\n",errno);
    	exit(1);
    }
    printf("Abriendo el archivo...\n");
    
    printf("Guardando los datos en la base de datos...\n");

    for (i = 0; i < 3; i++){
        temp = listas[i];
        while (temp != NULL){
            p = temp->preg;
            fprintf(fp,"%d %d %c \"%s\" \"%s\" \"%s\" \"%s\" %d\n",p.codigo,p.complejidad,p.area,p.strings[0],p.strings[1],p.strings[2],p.strings[3],p.respuestaCorrecta);

            temp = (temp)->ant;
        }

    }
    
    fclose(fp);
    printf("Hemos terminado de escribir en el archivo.\n");
}

