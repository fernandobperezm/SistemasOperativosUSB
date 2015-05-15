#include <stdio.h>
#include <stdlib.h>

enum NivelDeComplejidad {basico, intermedio, avanzado};

typedef struct pregunta{
    int codigo;
    char area;
    enum NivelDeComplejidad complejidad;
    char respuesta[3][100];
    int respuestaCorrecta;
} PREGUNTA;

typedef  struct lista {
    PREGUNTA preg;
    struct lista *sig;
    struct lista *ant;
} LISTA;
/*
    Se pone el doble asterisco para decir que se esta pasando es la direcci�n
    donde est� el apuntador en memoria. Es decir, se pasa una referencia del
    apuntador dado que se va a modificar su contenido, esto para que al final de
    la funci�n no se pierdan los cambios.
*/

void insertar(LISTA **primero, LISTA **ultimo, PREGUNTA pregunta){

    LISTA *nuevo;

    nuevo = (LISTA *) malloc(sizeof(LISTA));

    /*if (list == NULL){

    }*/

    //si la lista no esta vacia
    if (*ultimo != NULL)
        (*ultimo)->sig = nuevo;
    else
        primero = ultimo;



    nuevo->preg = pregunta;
        nuevo->sig = NULL;
        nuevo->ant = *ultimo;
        *ultimo = nuevo;

}


LISTA **buscar(LISTA **primero, int codigo){
    //list: temporal para no perder el apuntador
    //      a la cabeza de la lista
    LISTA **list;
    list = primero;

    while(*list != NULL){
        if (((*list)->preg.codigo) == codigo){
            return list;
        }

        list = &(*list)->sig;

    }
    return NULL;
}

void eliminar(LISTA **list, LISTA **ultimo, int codigo){
    LISTA *temp;



    temp = *buscar(list,codigo);

    if ((*ultimo)->sig == NULL)
        *ultimo = temp;

    temp->ant->sig = temp->sig;
    temp->sig->ant = temp->ant;

    free(temp);


}

int main(void){

    LISTA *primero = NULL;
    LISTA *ultimo = NULL;
    //LISTA *ultimo = NULL;
    int num;

    PREGUNTA p;

    p.codigo = 2;
    insertar(&primero,&ultimo,p);

    primero = (ultimo);
    //ultimo = primero;
    //*ultimo = *primero;
    p.codigo = 3;
    insertar(&primero,&ultimo,p);

    p.codigo = 4;
    insertar(&primero,&ultimo,p);

    //primero = (ultimo->ant);

    eliminar(&primero,&ultimo,3);
    //num = (int)(*buscar(&primero,3));


    printf("%d",primero->sig->preg.codigo);

    return 0;
}