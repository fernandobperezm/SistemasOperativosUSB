#include <stdio.h>
#include <stdlib.h>

enum NivelDeComplejidad {basico, intermedio, avanzado};

typedef struct pregunta{
    int codigo;
    char area;
    //enum NivelDeComplejidad complejidad;
    int complejidad;
    char strings[4][100];
    int respuestaCorrecta;
} PREGUNTA;

void LeerArchivo(){
    printf("Hola, soy leerPregunta");
}

void ConsultarComplejidad(int complejidad){
    printf("La complejidad es %d",complejidad);
}

void EliminarPregunta(){
    printf("HOla, soy EliminarPregunta()");
}

void InsertarPregunta(){
    PREGUNTA P;
    printf("Ha seleccionado Insertar una pregunta a la base de datos.\n");
    printf("A continuación, introduzca los atributos que se le piden.\n");
    
    
    printf("\tCódigo: ");
    scanf("%d",&P.codigo);
    
    
    
    
    printf("\n");
    
    
    printf("\tÁrea(H,G,T,C ó L): ");
    scanf("%c",&P.area);
    
    
    
    
    
    return;
    /*
    
    
    
    
    printf("\n");
    printf("\tNivel de complejidad(0, 1 ó 2): ");
    scanf("%d",&(P.complejidad));
    printf("\n");
    printf("\tPregunta: ");
    scanf("%s",P.strings[0]);
    printf("\n");
    printf("\tRespuesta1: ");
    scanf("%s",P.strings[1]);
    printf("\n");
    printf("\tRespuesta2: ");
    scanf("%s",P.strings[2]);
    printf("\n");
    printf("\tRespuesta3: ");
    scanf("%s",P.strings[3]);
    printf("\n");
    printf("\tEntero correspondiente a la respuesta correcta: ");
    scanf("%d",&P.respuestaCorrecta);
    printf("\n");
    
    printf("%d %c %d %s %s %s %s %d",P.codigo,P.area,(int)P.complejidad,P.strings[0],P.strings[1],P.strings[2],P.strings[3],P.respuestaCorrecta);
    */
}

void Salvar(){
    printf("Salvar");
}
