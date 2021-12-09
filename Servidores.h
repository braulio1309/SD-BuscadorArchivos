#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define SA struct sockaddr
#define PORT    8080
#define MAXLINE 1024

typedef  struct   dato{
    char archivo[MAXLINE];
    int sockt;
} data;

typedef  struct   datos{
    char archivo[MAXLINE];
    int sockt;
    struct sockaddr_in cliente;
} dataUDP;
void server();

void *conectarUDP(void *args){
    dataUDP *datas = (dataUDP *)args;
    struct sockaddr_in servaddr, cliaddr;
    int len = sizeof(datas->cliente);
    printf("%s", datas->archivo);
    sendto(datas->sockt, (const char *)datas->archivo, strlen(datas->archivo), 
        MSG_CONFIRM, (const struct sockaddr *) &datas->cliente,
            len);

}

void server(){
	 int sockfd;
    char buffer[MAXLINE];
    char hello[100];
    struct sockaddr_in servaddr, cliaddr;
       strcpy(hello, "hola");
    // servidor
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
       
    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));
       
    
    servaddr.sin_family    = AF_INET; // IPv4
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(2002);
       
    // Bind the socket with the server address
    if ( bind(sockfd, (const struct sockaddr *)&servaddr, 
            sizeof(servaddr)) < 0 )
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
       
    int len, n;

   
    len = sizeof(cliaddr);  //len is value/resuslt

    int i=0, opcion=0;
    struct sockaddr_in clients[50];
    while(1){
        printf("Desea conectar un clieente? (1:SI/2:NO\n");
        scanf("%d", &opcion);
        if(opcion==1){
            n = recvfrom(sockfd, (char *)hello, MAXLINE, 
                MSG_WAITALL, ( struct sockaddr *) &cliaddr,
                &len);
            if(n< 0){
                printf("Server fallo");
                exit(0);
            }else{
                //printf
                clients[i++]= cliaddr;

            }
        }else{
            break;
        }
        
    }
    dataUDP data;
   while(1){
    
    printf("Ingree el archivo a buscar\n");
    scanf("%s",hello);

    pthread_t tr;
    for(n=0;n<i;n++){
        int *pclient = malloc(sizeof(int));
        data.sockt = sockfd;
        data.cliente = clients[n];
        strcpy(data.archivo, hello);
        pthread_create(&tr, NULL, (void*)conectarUDP, (void*)&data);
    }
    
    
    
   }
    
       
    return;
}

void client(){
	int sockfd;
    char buffer[MAXLINE];
    char *hello = "HHola desde cliiente";
    struct sockaddr_in     servaddr;
   char inicio[100];
   strcpy(inicio, "./");
   char an[100];
    // Creating socket file descriptor
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("Creacion de socket fallo");
        exit(EXIT_FAILURE);
    }
   
    memset(&servaddr, 0, sizeof(servaddr));
       
    // Filling server information
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(2002);
    servaddr.sin_addr.s_addr = INADDR_ANY;
       
    int n, len;
    char *rutafinal[100];
    int flag =0;
    char encontrar[100];
    encontrar[0]='\0';
    
    while(1){
        sendto(sockfd, (const char * ) encontrar, strlen(encontrar),
        MSG_CONFIRM, (const struct sockaddr *) &servaddr, 
            sizeof(servaddr));

        printf("Mensaje hola enviado\n");
        bzero(buffer,MAXLINE);
        n = recvfrom(sockfd, (char *)buffer, MAXLINE, 
                    MSG_WAITALL, (struct sockaddr *) &servaddr,
                    &len);
        buffer[n]='\0';
       printf ("entra buffer %s", buffer);
        
        procesoArchivo(inicio, encontrar, buffer, &flag, rutafinal);
        flag=0;
    }
    
   
    close(sockfd);
    return;
}
