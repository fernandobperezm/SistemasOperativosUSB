/*
 * sistemaDeArchivos.c
 * 
 * Descripción: Este archivo contiene las funciones y procedimientos de
 * operaciones de E/S y PIPES necesarias para el programa.
 *
 * Autores: 
 * 	Br. Fernando Pérez, carné: 12-11152.
 * 	Br. Leslie Rodrigues, carné: 10-10613.
 *
 * Última modificación:
 */
 
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h> 
#include <dirent.h>
#include <fcntl.h>

void leerArchivo(char *nombre){
    int fd = 0;
    int charsRead; //número de carácteres leídos
    off_t offset;
    int nroChars; //número de carácteres que contiene el archivo 
    char *buffer;
    int archivoprueba;
    
    //Se abre el archivo.
    fd = open(nombre, O_RDONLY);
    
    //movemos el offset al final del archivo para determinar la
    //cantidad de caracteres
   	offset = 0;
    nroChars = lseek(fd, offset,SEEK_END);
    
    //movemos el offset al inicio del archivo
    lseek(fd, offset,SEEK_SET);  
    
    //pedimos memoria
    buffer = (char *) malloc(sizeof( char)* nroChars);
    //Se lee archivo.
    charsRead = read(fd, buffer, nroChars); 
	//Se escribe en el pipe.
	write(STDOUT_FILENO, buffer, charsRead);
	
    free(buffer);
    close(fd);
}




