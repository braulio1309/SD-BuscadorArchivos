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
void server();

void server(){
	 int sockfd;
    char buffer[MAXLINE];
    char hello[100];
    struct sockaddr_in servaddr, cliaddr;
       strcpy(hello, "hola");
    // Creando socket
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
       
    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));
       
   
    servaddr.sin_family    = AF_INET; // IPv4
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);
       
    
    if ( bind(sockfd, (const struct sockaddr *)&servaddr, 
            sizeof(servaddr)) < 0 )
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
       
    int len, n;
   
    len = sizeof(cliaddr);  
   while(1){
    n = recvfrom(sockfd, (char *)buffer, MAXLINE, 
                MSG_WAITALL, ( struct sockaddr *) &cliaddr,
                &len);
    buffer[n] = '\0';
    
    printf("Ingree el archivo a buscar\n");
    scanf("%s",hello);
    sendto(sockfd, (const char *)hello, strlen(hello), 
        MSG_CONFIRM, (const struct sockaddr *) &cliaddr,
            len);
    
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
   
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("Creacion de socket fallo");
        exit(EXIT_FAILURE);
    }
   
    memset(&servaddr, 0, sizeof(servaddr));
       
    // Filling server informatio
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = INADDR_ANY;
       
    int n, len;
    char *rutafinal[100];
    int flag =0;
    char encontrar[100];
    encontrar[0]='\0';
    while(1){
        sendto(sockfd, (const char *)hello, strlen(hello),
        MSG_CONFIRM, (const struct sockaddr *) &servaddr, 
            sizeof(servaddr));

        printf("Mensaje hola enviado\n");
               
        n = recvfrom(sockfd, (char *)buffer, MAXLINE, 
                    MSG_WAITALL, (struct sockaddr *) &servaddr,
                    &len);
        buffer[n] = '\0';
       
        
        procesoArchivo(inicio, encontrar, buffer, &flag, rutafinal);
        flag=0;
    }
    
   
    close(sockfd);
    return;
}
