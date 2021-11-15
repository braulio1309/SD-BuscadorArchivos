#include <pthread.h>
#include "ArchivosLibrerias.h"
#include "Servidores.h"


int main(){
	
	char inicio[120];	
	char encontrar[120];
	char an[100];
	char path[100];
/*	pthread_t proceso1;
	pthread_t proceso2;*/
	strcpy(inicio, "./");
//	strcpy(encontrar, "texto");
	encontrar[0] = '\0';
	vaciarCadena(encontrar);
	/*pthread_create(&proceso1, NULL, &procesoArchivo, inicio, encontrar, an);
	pthread_create(&proceso2, NULL, &procesoArchivo, "./Dentro", encontrar, an);
	pthread_join(proceso1, NULL);
	pthread_join(proceso2, NULL);*/
	//procesoArchivo(inicio, encontrar, an);
	server();

  return 0;
}


