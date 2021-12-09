#include <pthread.h>
#include "ArchivosLibrerias.h"
#include "Servidores.h"
#include "ServerTCP.h"

int main(){
	
	char inicio[120];	
	char encontrar[120];
	char an[100];
	char path[100];
	int opcion =0;
	strcpy(inicio, "./");
	//strcpy(an)
	encontrar[0] = '\0';
	vaciarCadena(encontrar);
	printf("Ingrese como quiere conectar \n1: servidor UDP\n2:cliente UDP\n3:Servidor TCP\n4:Cliente TCP\n");
	
	scanf("%d", &opcion);
	if(opcion == 1){
		server();
	}else
		if(opcion == 2){
			client();
		}else
			if(opcion == 3){
				serverTCPhilos();
			}else
				if(opcion == 4){
					clientTCP();
				} 
				

  return 0;
}


