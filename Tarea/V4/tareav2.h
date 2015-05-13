typedef struct pregunta{
    int codigo;
    char area;
    //enum NivelDeComplejidad complejidad;
    int complejidad;
    char strings[4][100];
    int respuestaCorrecta;
} PREGUNTA;

typedef  struct lista {
    PREGUNTA preg;
    struct lista *sig;
    struct lista *ant;
} LISTA;


void insertar(LISTA **primero, LISTA **ultimo, PREGUNTA pregunta);
LISTA **buscar(LISTA **primero, int codigo);
int eliminar(LISTA **list, LISTA **ultimo, int codigo);
