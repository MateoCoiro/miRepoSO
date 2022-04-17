/*
 ============================================================================
 Name        : Modulo.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <commons/config.h>
#include <commons/collections/list.h>
#include <commons/temporal.h>
#include <commons/log.h>

char parsear(FILE* archivo,char* buffer,int largoMaximoDeLinea){
	char caracter;
	int largo = 0;
	while((caracter != EOF) && (caracter != '\n')){
			if(largo == largoMaximoDeLinea) //me quede sin memoria?
			{
				largoMaximoDeLinea *= 2; //agrando el buffer
				buffer = realloc(buffer,largoMaximoDeLinea); //aloco memoria nueva a buffer
			}
			caracter = getc(archivo);
			memcpy(buffer+largo,caracter,sizeof(char));
			largo++;
	}

	return caracter;//devuelvo el caracter para saber si ya estoy en EOF
}

void noHagoNada(void* nada){

}
void imprimir(void* string){
	printf("%s\n",(char*) string);
}

void limpiarBuffer(void* buffer){
	for(int i=0;i < sizeof(buffer); i++){
		buffer='\0';
	}
}
void consola(int tamanioDelProceso,char* ruta) {

	FILE* archivo = fopen(ruta,"r+b");
	int MAX_LENGTH_LINE = 3;
	t_list* listaDeInstrucciones = list_create(); // creo la lista de instrucciones
	char* buffer = malloc(sizeof(char) * MAX_LENGTH_LINE);// agarro memoria
	char caracter;
	t_log* logger = log_create("../logger.txt","LOGS:",true,LOG_LEVEL_INFO); //creo el log


	while(caracter != EOF)
	{
		caracter = parsear(archivo,buffer,MAX_LENGTH_LINE); // parseo el archivo segun '/n'
		log_info(logger,buffer);// chequeo que ande bien
		list_add(listaDeInstrucciones,buffer); //agrego a la lista la instruccion leida 
		limpiarBuffer(buffer);
	}

	list_iterate(listaDeInstrucciones,imprimir);
	//Libero toda la memoria
	fclose(archivo);
	list_destroy_and_destroy_elements(listaDeInstrucciones,noHagoNada); 
	free(buffer);
	log_destroy(logger);
}
