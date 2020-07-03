/*2020.7.1 network chatting program (client code) */
#include <stdio.h>
#include <stdio.h>
#include<sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include<string.h>
#define bufsize 8192

int main(){
    int serv_socket;
    int index=0;
    struct sockaddr_in servAddr;
     char buf[bufsize];
     
    if((serv_socket=socket(PF_INET,SOCK_STREAM,0))==-1){
        printf("socket error\n");
        return 0;
    }

    int reuse;
    reuse=1;
    setsockopt(serv_socket,  SOL_SOCKET,  SO_REUSEADDR,  (const char*)&reuse, sizeof(reuse));

    memset(&servAddr,0,sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr=htonl(INADDR_ANY);
    servAddr.sin_port = htons(8080);

    connect(serv_socket,(struct sockadrr *)&servAddr, sizeof(servAddr));

    while(1){
        
        printf("input: ");
        scanf("%s",buf);
        send(serv_socket,buf,bufsize,0);
        memset(buf,0,bufsize);

        recv(serv_socket,buf,bufsize,0);

        
         printf("[server]: %s\n",buf);
        memset(buf,0,bufsize);
        
    }
    return 0;
}