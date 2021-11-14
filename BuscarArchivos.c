#include "ArchivosLibrerias.h"


int main(){
	

	//Pedir directorio de inicio y archivo a buscar
	/* Con un puntero a DIR abriremos el directorio */
	DIR *dir;

	//Empezaremos a leer en el directorio escrito
	dir = opendir(".");

	accion(dir);

  return 0;
}


