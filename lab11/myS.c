#include <stdio.h>      /* for printf() and fprintf() */
#include <sys/socket.h> /* for socket(), bind(), and connect() */
#include <arpa/inet.h>  /* for sockaddr_in and inet_ntoa() */
#include <stdlib.h>     /* for atoi() and exit() */
#include <string.h>     /* for memset() */
#include <unistd.h> 
#define MAXPENDING 5
#define RCVBUFSIZE 32 
char echoBuffer[RCVBUFSIZE];
char data[RCVBUFSIZE];
int flag =0;
void DieWithError(char *errorMessage)
{
    perror(errorMessage);
    exit(1);
}
void HandleTCPClient(int clntSocket)
  /* Error handling function */
{
        /* Buffer for echo string */
    int recvMsgSize;
    if ((recvMsgSize = recv(clntSocket, echoBuffer, RCVBUFSIZE, 0)) < 0){
        DieWithError("recv() failed");
    }
//    printf("%s",echoBuffer);
}

int work(char name[])
{
	printf("enter %s",name);
int sum=0;
int count=0;
FILE *fp;
int s;
int k=0;
int r=0;
int m=0;
    if ((fp = fopen(name, "r")) == NULL)
        {
        printf("Не удалось открыть файл");
        }              

     while ((fscanf(fp, "%d",&s)!=EOF))
        {   
        if(!fp) break;    //чтобы не делал лишнего
        count+=1;
        }

	int *c = (int*) malloc(k*sizeof(int));  //должен быть динамическим
    //перематываем файл для повторногfpя
	rewind(fp);

	for(int i=0;i<count;i++)
		{
    	fscanf(fp, "%d",&c[i]);
  //printf("c[%d]=%d\n  ",i,c[i]);
   		 sum=sum+c[i];
  //printf("%d\n",r);
		}
    float t=(float)sum/count;
   // printf("%f",t);
    free(c);
    fclose(fp);
 return t;
 }

int main(int argc, char *argv[])
{
    int servSock;                    /* Socket descriptor for server */
    int clntSock;                    /* Socket descriptor for client */
    struct sockaddr_in echoServAddr; /* Local address */
    struct sockaddr_in echoClntAddr; /* Client address */
    unsigned short echoServPort;     /* Server port */
    unsigned int clntLen;            /* Length of client address data structure */

    if (argc != 2)     /* Test for correct number of arguments */
    {
        fprintf(stderr, "Usage:  %s <Server Port>\n", argv[0]);
        exit(1);
    }

    echoServPort = atoi(argv[1]);  /* First arg:  local port */

    /* Create socket for incoming connections */
    if ((servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
        DieWithError("socket() failed");
      
    /* Construct local address structure */
    memset(&echoServAddr, 0, sizeof(echoServAddr));   /* Zero out structure */
    echoServAddr.sin_family = AF_INET;                /* Internet address family */
    echoServAddr.sin_addr.s_addr = htonl(INADDR_ANY); /* Any incoming interface */
    echoServAddr.sin_port = htons(echoServPort);      /* Local port */

    /* Bind to the local address */
    if (bind(servSock, (struct sockaddr *) &echoServAddr, sizeof(echoServAddr)) < 0)
        DieWithError("bind() failed");

    /* Mark the socket so it will listen for incoming connections */
    if (listen(servSock, MAXPENDING) < 0)
        DieWithError("listen() failed");
    for (;;) /* Run forever */
    {
        /* Set the size of the in-out parameter */
        clntLen = sizeof(echoClntAddr);
    	printf("1");
        /* Wait for a client to connect */
        clntSock = accept(servSock, (struct sockaddr *) &echoClntAddr,&clntLen);
        /* clntSock is connected to a client! */
    	printf("2");
        printf("Handling client %s\n", inet_ntoa(echoClntAddr.sin_addr));
    	printf("3");
        HandleTCPClient(clntSock);
        printf("4");
        //printf("geet %s\n",(echoBuffer));
        printf("5");
        sleep(1);
        float d=work(echoBuffer);
        printf("6");
        printf("%f",d);
        printf("6");

    }
    /* NOT REACHED */
}