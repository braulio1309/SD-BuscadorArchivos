#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include  <string.h>



void procesoArchivo(char *start, char *path, char *encontrar, int *bandera, char **ruta);
void vaciarCadena(char *cadena);



void procesoArchivo(char *start, char *path, char *encontrar, int *bandera, char **ruta){
    struct dirent *ent;
    FILE *fich;
    long ftam;
    DIR *dir;
    char ini[100];
    char auxpath[100];
    char anterior[1000];
    auxpath[0] = '\0';
    int i=0;
    
    if(*bandera==1) return;
    
     //dir = opendir("./");
    //printf("hey%s", path);
   if(path[0] == '\0' ){
        dir = opendir("./");
        strcpy(path, "./");
        //printf("if");
        
    }else{
         
        if(strcmp(path, "./") != 0){
            //printf("%s\n", path);
            strcpy(auxpath, "/");
        }
            
        
        strcat(auxpath, start);
        strcat(path, auxpath);
        // printf("%s\n", path);
        dir = opendir(path);
        
    }
    
    //printf ("dir null \n");
    //Miramos que no haya error 
    if (dir == NULL){ 
        path[strlen(path) - strlen(auxpath) ] = '\0';
        //printf("%s\n", path);
        return;
    }
    
  /* Leyendo uno a uno todos los archivos que hay */
    //printf ("while");
  while ((ent = readdir (dir)) != NULL){    
        if ((strcmp(ent->d_name, ".")!=0) && strcmp(ent->d_name,"..")!=0){  //Verificar si es una carpeta       
         
            
            //Si revisamos si es carpeta

            if ((strcmp(ent->d_name, encontrar)==0)){
                *bandera = 1;
                /*printf("if%s-%s\n", ent->d_name, path);
                strcpy(*ruta, path);
                printf("cpoy%s-%s\n", ent->d_name, encontrar);
                strcat(*ruta, "/");
                strcat(*ruta, encontrar);*/
                printf ("Se encontro en la ruta: %s/%s\n", path, encontrar);
                return ;
            }
            procesoArchivo(ent->d_name, path, encontrar, bandera, ruta);
            
                
          
        }
    }

    path[strlen(path) - strlen(auxpath) ] = '\0';
    closedir (dir);
}


void vaciarCadena(char *cadena){
        int i=0;
        for(i=0; i<120; i++){
            cadena[i] = '\0';
        }
}