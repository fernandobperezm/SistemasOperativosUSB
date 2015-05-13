/**
 * Bases.h
 * 
 * Descripción: Este es el archivo cabecera de Bases.c.
 * 
 * Autores: 
 * 	Br. Fernando Pérez, carné: 12-11152.
 * 	Br. Leslie Rodrigues, carné: 10-10613.
 *
 * Última modificación: 27-04-2015.
 */
#include "listaEnlazada.h"

void LeerArchivo(char nombre[], LISTA **listas);
void mostrarPregunta(PREGUNTA P);
void ConsultarComplejidad(LISTA **listas, int complejidad);
void EliminarPregunta(int codigo, LISTA **listas);
void InsertarPregunta(LISTA **listas);
void Salvar(char *nombre,LISTA **listas);
