#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include  <string.h>



void procesoArchivo(char *archivo, char *path, char *oldpath);
void vaciarCadena(char *cadena);



void procesoArchivo(char *start, char *path, char *oldpath){
	struct dirent *ent;
	FILE *fich;
	long ftam;
	DIR *dir;
	char ini[100];
	char auxpath[100];
	char anterior[1000];
	auxpath[0] = '\0';
	int i=0;
	
//strcat(auxpath, path);
	
	if(path[0] == '\0' ){
		dir = opendir("./");
		
		strcpy(path, "./");
	
	}else{
		
		
		if(strcmp(path, "./") != 0){
			strcpy(auxpath, "/");
		}
			
			
		strcat(auxpath, start);
		strcat(path, auxpath);
	//	printf("%s", path);
		dir = opendir(path);
		
	}

	/*Miramos que no haya error */
	if (dir == NULL){
	
		path[strlen(path) - strlen(auxpath) ] = '\0';
		
		
		return;
	}
 
 	
 	
  /* Leyendo uno a uno todos los archivos que hay */
  while ((ent = readdir (dir)) != NULL){
      
		
	    if ((strcmp(ent->d_name, ".")!=0) && strcmp(ent->d_name,"..")!=0){
	    	
			fich=fopen(ent->d_name, "r");
	    	//Decimos el tamaño
			if(fich){
				fseek(fich, 0L, SEEK_END);
				ftam=ftell(fich);
				fclose(fich);
				printf ("%30s (%ld bytes)\n", ent->d_name, ftam);
    		}else
    			printf ("%30s (No info.)\n", ent->d_name);
    			
    		//Si revisamos si es carpeta	
    		procesoArchivo(ent->d_name, path, ent->d_name);
			
    			
	      
	    }
	}

	
	path[strlen(path) - strlen(oldpath)-1] = '\0';
	//oldpath[0] = '\0';
	closedir (dir);
}

void vaciarCadena(char *cadena){
		int i=0;
		for(i=0; i<120; i++){
			cadena[i] = '\0';
		}
}
