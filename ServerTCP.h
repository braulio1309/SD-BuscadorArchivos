
#include <errno.h>
typedef  struct   dato{
	char archivo[MAXLINE];
	int sockt;
} data;
void * conectar(void *args){
	
    data *datas = (data *)args;
    char buffs[MAXLINE];
    static int clientCount = 0;
    printf("%d", clientCount++);
    char archivo[MAXLINE];
    strcpy(archivo, datas->archivo);

    //strcpy(buff, "jola");
    printf("%s\n",datas->archivo);
    int n;
    
    	
    	bzero(buffs, MAXLINE);
    	n =recv(datas->sockt, buffs, MAXLINE, 0);
    	printf("%s", buffs);
	    
	    //envío de archivo
	    send(datas->sockt, archivo, strlen(archivo), 0);

     
	  	
	
  
}
void serverTCPhilos(){

    int sockfd, connfd, len;
    struct sockaddr_in servaddr, cli;
    static int clientCount = 0;
    static int clients[20];
    char buff[MAXLINE];
    // Creación y verificación de socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("socket creation failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully created..\n");
  
   
   memset(&servaddr, 0, sizeof(servaddr));
    memset(&cli, 0, sizeof(cli));
   
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);
    bzero(&(servaddr.sin_zero),8);
   int reuse = 1;
   setsockopt(sockfd,SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
   
    // Binding nuevo socket
    if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) {
        printf("socket bind failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully binded..\n");
   
    // Servidor escuchando
    if ((listen(sockfd, 5)) != 0) {
        printf("Listen failed...\n");
        exit(0);
    }
    else
        printf("Server listening..\n");
	    len = sizeof(cli);

	int i=0, opcion=0;
	while(1){
		printf("Desea conectar un clieente? (1:SI/2:NO\n");
		scanf("%d", &opcion);
		if(opcion==1){
			connfd = accept(sockfd, (SA*)&cli, &len);
			if(connfd < 0){
				printf("Server fallo");
				exit(0);
			}else{
				clients[i++]= connfd;

			}
		}else{
			break;
		}
		
	}
    
	  	
	
	int n=0;
	char archivo[MAXLINE];
	data data;
    while(1){
   			printf("Inggrees el archivo a buscar\n");
   			scanf("%s", archivo);
			pthread_t tr;
			for(n=0; n<i; n++){
		  		int *pclient = malloc(sizeof(int));
				*pclient = connfd;
				data.sockt = clients[n];
				strcpy(data.archivo, archivo);
		  	 	//Hilo de envío de mensajes
		  		pthread_create(&tr, NULL, (void*)conectar, (void*)&data);
		  		//Hilo de procesar archivo servdioor
	  		}
	  	
	 }

}

void serverTCPprocesos(){

}

void clientTCP(){

    int sockfd, connfd;
    struct sockaddr_in servaddr, cli;
   char buff[MAXLINE];
    
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("creaciion  de socket fallo..\n");
        exit(0);
    }
    else
        printf("socket  creado con exito..\n");
    bzero(&servaddr, sizeof(servaddr));
   
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(PORT);
   
    // Conectar el cliente con el socket
    	if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) != 0) {
        	printf("creacion de socket fallo...\n");
        	exit(0);
    	}
    else
        printf("conectado al servidor..\n");
    
    
   int len; 
   
   char *hello = "hola\0";
   char inicio[100];
   strcpy(inicio, "./");
   char encontrar[100];
   encontrar[0] = '\0';
   int flag = 0;
   char *an;
   char *rutafinal[MAXLINE];
   int n=0, i;
   while(1){

  //saludo al server
	  	send(sockfd, hello, strlen(hello)+1,0);
	    printf("Mensaje hola enviado\n");
	           bzero(buff, MAXLINE);
	    //recibo archivo
	    n = recv(sockfd, buff, MAXLINE, 0);
	    if(n > 0){
	    	//printf("Buffer %s\n", buff);
	    	
	    	//printf("an%s", an);
		    procesoArchivo(inicio, encontrar, buff, &flag, rutafinal);
		  	flag=0;
		  	encontrar[0]= '\0';
		    /*printf("hey%s\n %d\n", buff, n );
		    strcpy(buff, *rutafinal);
	     	send(sockfd, buff, strlen(buff)+1,0);*/
	   	
	    }
	}

	    
}