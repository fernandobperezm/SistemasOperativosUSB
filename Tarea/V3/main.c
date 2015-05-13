#include <stdio.h>
#include <stdlib.h>

#include "bases.h"

/*
char imprimirMenu(){
    char Respuesta;
    
    return Respuesta;
}
*/


/*
    El main se declara de esta manera para que podamos recibir por el shell los
    comandos(en este caso, el nombre del archivo). argc cuenta el número de ar-
    gumentos introducidos por el usuario, y *argv guarda en una arreglo cada uno
    de ellos.
*/
int main (int argc, char *argv[]){
    if(argc != 2){
        printf("Disculpe, el formato es ./nombreDePrograma nombreDeArchivo\n");
        printf("Vuelva a ejecutar el programa.\n");
        exit(1);
    }
    else{
        /*
          Cuando el número de argumentos es correcto, pasamos a mostrar la
          bienvenida al programa y enseguida mostramos las opciones. Recibiremos
          la respuesta y con un Switch se decidirá qué hará el programa.
        */
        printf("Bienvidos al programa. Creadores: Fernando Pérez y Leslie\
 Rodrigues\n\n");
        printf("MENÚ. Para usarlo, escriba el número de la opción que quiera\
 que el programa realice.\n");
        
        
        //menú.
        printf("\tOpción 1: Leer los datos de la base de datos.\n");
        printf("\tOpción 2: Consultar la base de datos.\n");
        printf("\tOpción 3: Consultar la base de datos por complejidad.\n");
        printf("\tOpción 4: Eliminar una pregunta.\n");
        printf("\tOpción 5: Insertar una pregunta.\n");
        printf("\tOpción 6: Salvar los cambios en la base de datos.\n");
        printf("\tOpción 0: Salir del sistema.\n\n");
        
        
        char Respuesta;
        int numero;
        
        
        
        do{
            scanf("%c",&Respuesta);
            //printf("La opción que seleccionó es: %c",Respuesta);
            switch(Respuesta){
                case '1':
                    LeerArchivo(argv[1]);
                    break;
                case '2':
                    ConsultarComplejidad(0);
                    ConsultarComplejidad(1);
                    ConsultarComplejidad(2);
                    break;
                case '3':
                    printf("Indique el nivel de complejidad que quiera consultar\n");
                    scanf("%d",&numero);
                    ConsultarComplejidad(numero);
                    break;
                case '4':
                    printf("Introduzca el codigo de la pregunta que desea eliminar\n");
                    scanf("%d",&numero);
                    EliminarPregunta();
                    break;
                case '5':
                    InsertarPregunta();
                    printf("%c",Respuesta);
                    break;
                case '6':
                    Salvar();
                    break;
                case '0':
                    //exit(0);
                    break;
                default:
                    printf("El caracter %c no es válido. Introduzca nuevamente la\
 opción\n",Respuesta); 
                    //Respuesta = 'E';    
           }
        } while(Respuesta != '0');
        exit(0);
    }
}
