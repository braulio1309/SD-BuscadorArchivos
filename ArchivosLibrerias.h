#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include  <string.h>
/* Función para devolver un error en caso de que ocurra */
void error(const char *s);
/* Función que hace algo con un archivo */
void procesoArchivo(char *archivo);

void vaciarCadena(char *cadena);

void accion( DIR *archivo);

void error(const char *s)
{
  /* perror() devuelve la cadena S y el error (en cadena de caracteres) que tenga errno */
  perror (s);
  exit(EXIT_FAILURE);
}

void procesoArchivo(char *archivo)
{
  /* Para "procesar", o al menos, hacer algo con el archivo, vamos a decir su tamaño en bytes */
  /* para ello haremos lo que vemos aquí: https://poesiabinaria.net/2010/04/tamano-de-un-fichero-en-c/ */
  FILE *fich;
  long ftam;

  fich=fopen(archivo, "r");
  if (fich)
    {
      fseek(fich, 0L, SEEK_END);
      ftam=ftell(fich);
      fclose(fich);
      /* Si todo va bien, decimos el tamaño */
      printf ("%30s (%ld bytes)\n", archivo, ftam);
    }
  else
    printf ("%30s (No info.)\n", archivo);
    
}

void vaciarCadena(char *cadena){
	int i=0;
	for(i=0; i<200; i++){
		cadena[i] = '\0';
	}
}

void accion(DIR *dir){
	 struct dirent *ent;
	/* Miramos que no haya error */
  if (dir == NULL)
    error("No puedo abrir el directorio");
 
 
  /* Leyendo uno a uno todos los archivos que hay */
  while ((ent = readdir (dir)) != NULL){
      
		/* Nos devolverá el directorio actual (.) y el anterior (..), como hace ls */
	    if ( (strcmp(ent->d_name, ".")!=0) && (strcmp(ent->d_name, "..")!=0) ){
	    	// Una vez tenemos el archivo, lo pasamos a una función para procesarlo. 
	      procesoArchivo(ent->d_name);
	    }
	}
  closedir (dir);
}
