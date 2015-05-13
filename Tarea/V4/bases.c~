#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tareav2.h"

/*
typedef struct pregunta{
    int codigo;
    char area;
    //enum NivelDeComplejidad complejidad;
    int complejidad;
    char strings[4][100];
    int respuestaCorrecta;
} PREGUNTA;*/

void LeerArchivo(char nombre[], LISTA *listas[3]){
    FILE *filepointer;
    char preguntas[430];
    PREGUNTA P;
    char *token;
    
    
    filepointer = fopen(nombre,"r");
    fscanf(filepointer,"%d %d %c \"%[^\"]\" \"%[^\"]\" \"%[^\"]\" \"%[^\"]\" %d ",&P.codigo,&P.complejidad,&P.area,&P.strings[0],&P.strings[1],&P.strings[2],&P.strings[3],P.respuestaCorrecta);
    
    
    /*while(fgets(linea,sizeof(linea),filepointer) != NULL){
        sscanf(linea,"%d %d %c %[^\"]s",&P.codigo,&P.complejidad,&P.area,P.strings[0]);
    }*/
    
    
    /*while(1){
        if(fscanf(filepointer,"%d %c %d",&P.codigo,&P.complejidad,&P.area) == EOF){
            break;
        }
    }*/
    /*while((letra = fgetc(filepointer)) != EOF){
        contador++;
        switch(contador){
            case 1:
                P.codigo
        }
    }*/

    printf("%d,%d,%c,%s",P.codigo,P.complejidad,P.area,preguntas);   
    //fprintf(filepointer,"%d",prueba);
    
    fclose(filepointer);
    
    printf("\nHemos terminado de leer el archivo, será regresado al menú principal");
}

void ConsultarComplejidad(int complejidad){
    printf("La complejidad es %d",complejidad);
}

void EliminarPregunta(int codigo,LISTA **listas){
    //eliminar();
}

void InsertarPregunta(){
    PREGUNTA P;
    
    printf("Ha seleccionado Insertar una pregunta a la base de datos.\n");
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
	fgets(P.strings[0],sizeof(P.strings[0]),stdin);
	
    printf("\n");
    
    printf("\tRespuesta1: ");
    fgets(P.strings[1],sizeof(P.strings[1]),stdin);
    
    printf("\n");
    
    printf("\tRespuesta2: ");
    fgets(P.strings[2],sizeof(P.strings[2]),stdin);
    
    printf("\n");
    
    printf("\tRespuesta3: ");
    fgets(P.strings[3],sizeof(P.strings[3]),stdin);
    
    printf("\n");
    
    printf("\tEntero correspondiente a la respuesta correcta: ");
    scanf("%d",&P.respuestaCorrecta);
    getchar();
    
    printf("\n");
    
    printf("Escriba 0 si los datos son correctos o 1 si son incorrectos.");
    
    
    
    
    //Ahora insertamos la pregunta con todos sus atributos en 
    
    
}

void Salvar(){
    printf("Salvar");
}
