include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

int main(int argc, char *argv[])
{
    int my_sock, port, n;
    struct sockaddr_in serv;
    struct hostent *server;
    char buff[1024];

    if (argc < 3)
    {
        fprintf(stderr,"usage %s hostname port\n", argv[0]);
        exit(0);
    }
       port = atoi(argv[2]);

        my_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (my_sock < 0){
        printf("ERROR opening socket");
    exit(-1);
    }
        server = gethostbyname(argv[1]);
    if (server == NULL)
    {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    serv.sin_family = AF_INET;
    bcopy((char*)server->h_addr,
          (char*)&serv.sin_addr.s_addr,
          server->h_length);
        serv.sin_port = htons(portn);
    if (connect(my_sock,(struct sockaddr *) &serv,sizeof(serv)) < 0){
        printf("ERRORconnecting\n");
        exit(-1);
    }

    n = recv(my_sock, &buff[0], sizeof(buff) - 1, 0);
    bzero((char *)buff, sizeof(buff));
    fgets(&buff[0], sizeof(buff) - 1, stdin);
    if (!strcmp(&buff[0], "quit\n"))
    {
        printf("Exit...");
        close(my_sock);
        return 0;
    }

    send(my_sock, &buff[0], strlen(&buff[0])-1, 0);
    bzero((char *)buff, sizeof(buff));
     n = recv(my_sock, &buff[0], sizeof(buff)-1, 0);
    printf("Reply from server %d bytes :%s\n", n, buff);
    if (n=0)
    printf("Recv error \n");
    close(my_sock);
    return -1;

}