enum NivelDeComplejidad {basico, intermedio, avanzado};

typedef struct pregunta{
    int codigo;
    char area;
    enum NivelDeComplejidad complejidad;
    char strings[4][100];
    int respuestaCorrecta;
} PREGUNTA;

typedef  struct lista {

    PREGUNTA preg;
    struct lista *sig;
    struct lista *ant;

} LISTA;

void insertar(LISTA **ultimo, PREGUNTA pregunta);
LISTA **buscar(LISTA **ultimo, int codigo);
int eliminar(LISTA **list, int codigo);
