/*
 * listaEnlazada.h
 * 
 * Descripción: Este es el archivo cabecera para listaEnlazada.c.
 *
 * Autores: 
 * 	Br. Fernando Pérez, carné: 12-11152.
 * 	Br. Leslie Rodrigues, carné: 10-10613.
 *
 * Última modificación: 21-05-2015.
 */

/*
 * LISTA es una lista enlazada que guarda un par de nombres, el número de amigos
 * de cada map, los amigos, y los comunes, además, la lista es doblemente enlazada,
 * por lo tanto, tiene apuntadores al siguiente nodo y al anterior.
 */ 
typedef  struct lista {
    char *nombre[2];
    int nroAmigos[3];
    char **amigos1;
    char **amigos2;
    char **comunes;
    struct lista *sig;
    struct lista *ant;
} LISTA;

void insertar(LISTA **ultimo,char *nombre1,char *nombre2);
LISTA **buscar(LISTA **ultimo, char *nombre1, char *nombre2);
void destruirLista(LISTA **ultimo);
