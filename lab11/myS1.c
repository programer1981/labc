#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#define str1 "Enter 1 parametr\r\n"
#define str2 "Enter 2 parametr\r\n"

void service(int);
int concli=0;
void clientamount() {
if (concli!=0){
}
else printf("Nobody  %d\n",getpid());
}
int hash (char *fn){
    FILE *f1;
    char c;
    int j=0;
f1=fopen(fn, "r");
    if (f1==NULL){
        printf("File not found %s\n",fn);
        exit(-1);
    }

    while(!feof(f1)){
        c=fgetc(f1);
        if (c==EOF) {
            printf("End of file \n");
        }
        j=j+c;

    }
return(j);
}
int main(int argc, char *argv[])
{
    char buff[1024];
    printf("Hello world!\n");
    int sock_l,sock_w;
    int portnum;
    pid_t pid;
    socklen_t clilen;
    struct sockaddr_in serv, usr;
    if (argc<2){
        printf("Usage ./main <port>\n");
        exit(-1);
    }
    sock_l=socket(AF_INET, SOCK_STREAM,0);
        if (sock_l<0){
        printf("Error:socket is down\n");
        exit(-1);
    }
    bzero((char*)&serv, sizeof(serv));
    portnum=atoi(argv[1]);
    serv.sin_family=AF_INET;
    serv.sin_addr.s_addr=INADDR_ANY;
    serv.sin_port=htons(portnum);
    if (bind(sock_l,(struct sockaddr*)&serv,sizeof(serv))<0){
        printf("Error while binding\n");
        exit(-1);
    }
    listen(sock_l,5);
    clilen=sizeof(usr);
    for(;;){
        sock_w=accept(sock_l,(struct sockaddr *)&usr,&clilen);
        if (sock_w<0){
        printf("Error on accept\n");
        exit(-1);
        }
        concli++;
     clientamount();
     pid=fork();
     concli--;
     if (pid < 0){
             printf("ERROR on fork\n");exit(-1); }
         if (pid == 0)
		 {
             close(sock_l);
             service(sock_w);
             exit(0);
         }
         else  close(sock_w);


     }
     close(sock_l);
    return 0; 

}
void service (int sock)
{

	int bytes_recv;
	int a;
	char buff[20 * 1024];
    write(sock, str1, sizeof(str1));
    bytes_recv = read(sock,&buff[0],sizeof(buff));
    printf("Bytes received %d\n", bytes_recv);
    printf("Filename %s\n", buff);
	if (bytes_recv < 0){ 
printf("ERROR reading from socket\n");exit(-1);
}
	 if (!strcmp(buff, "quit\n"))
    {
        printf("Exit...");
       exit(-1);
    }
	a=hash(buff);
	sprintf(buff, "%d", a);
	printf("%s\n",buff);
	buff[strlen(buff)] = '\n';
	write(sock,&buff[0],strlen(buff));
     clientamount();
	return;
}