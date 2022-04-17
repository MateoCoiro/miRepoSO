#include <stdio.h>
#include <stdlib.h>
#include <commons/config.h>
#include <commons/collections/list.h>
#include <commons/temporal.h>
#include <commons/log.h>

char parsear(FILE* ,char* ,int ); // recibe el archivo a parsear, el buffer donde alojar y el largo maximo
int consola(int ,char*);//tamaño del proceso y ruta del archivo a instrucciones