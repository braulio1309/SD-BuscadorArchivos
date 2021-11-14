#include "ArchivosLibrerias.h"


int main(){
	
	char inicio[120];	
	char encontrar[120];
	char an[100];
	char path[100];
	strcpy(inicio, "./");
//	strcpy(encontrar, "texto");
encontrar[0] = '\0';
vaciarCadena(encontrar);
	procesoArchivo(inicio, encontrar, an);

  return 0;
}


