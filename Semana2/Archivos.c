//Archivos.
#include <stdio.h>
#include <stdlib.h>


/* La estructura es la siguiente:
	1- Declaro un apuntador de tipo FILE.
	2- Asociamos el nombre del archivo con fopen.
	3- Traemos datos del disco a la RAM con fscanf.
	4- Guardamos datos en disco usando fprintf.
	5- cerramos el archivo.
*/

void main(){
	//Se declara el apuntador de tipo FILE.
	FILE *archivo;
	
	//Lo asociamos con fopen.
	archivo = fopen("numeros.txt","r+");
	int datos;
	int datos1[11];
	int i = 0;
	int dato = 11;
	
	//Lo traemos a RAM usando fscanf.
	//Si no sabemos la longitud total del archivo, iteramos hasta que se 
	//termine.
	while(fscanf(archivo,"%d",&datos) != EOF){
		printf("Todo es: %d\n",datos);
	}
	
	//Escribimos en el archivo.
	fprintf(archivo,"%d",dato);
	
	//Nos devolvemos al principio con una función de C.
	rewind(archivo);
	
	//Si sabemos cual es la longitud total del archivo pudiesemos usar esto.
	for(i = 0;i <= 10;i++){
		fscanf(archivo,"%d",&datos1[i]);
		printf("En el arreglo es: %d\n",datos1[i]);
	}
	
	//Lo cerramos.
	fclose(archivo);
}
