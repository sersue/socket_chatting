/*2020.7.1 network chatting program (server code) */
#include <stdio.h>
#include <stdio.h>
#include<sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#define bufsize 8192
int main(){
    struct sockaddr_in servAddr,cliAddr;
    int serv_socket,cli_socket,cliAddrSize;//ip,port주소 가지고있는 소켓의 디스크립터, cli_socket은 client로 부터 accpet할 디스크립터
    char buf[bufsize];
    int index=0;
    if((serv_socket = socket(PF_INET,SOCK_STREAM,0)) == -1){
        printf("Create socket fail\n");
        return 0;
    }
    int reuse;
    reuse=1;
    setsockopt(serv_socket,  SOL_SOCKET,  SO_REUSEADDR,  (const char*)&reuse, sizeof(reuse));
    memset(&servAddr,0,sizeof(servAddr));
    /*memset() : servAddr 구조체 초기화해주는 함수*/
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr=htonl(INADDR_ANY);
     /*servAddr.sin_addr.s_addr는 자신의 IP를 할당 (무작위로)
    (htonl,htons 함수는  host가 누구든 network long, short 타입으로 바꾸어줌
    )*/
    servAddr.sin_port = htons(8080);
    
    if ((bind(serv_socket, (struct sockadrr*)&servAddr, sizeof(servAddr)))==-1){
        printf("binding fail\n");
        return 0;

    }//serv_socket에 servAddr 구조체 바인딩

    listen(serv_socket,5); //server 기다림
    cliAddrSize= sizeof(cliAddr);
    cli_socket = accept(serv_socket,(struct sockadrr*)&cliAddr, &cliAddrSize);//cliaddrsize 포인터로 전달해줘야 accept함수 작동
    if(cli_socket == -1 ){
        printf("accept error (대기 함수 역할 안함)");
        return 0;
    }

        
    printf("client entered \n");
    while(1){

        recv(cli_socket,buf,bufsize,0);
       
        printf("[client]: %s\n",buf);
        /*이제 server가 씀 */
        char send_buf[bufsize];
        memset(send_buf,0,bufsize);
        printf("input : ");
        scanf("%s",send_buf);
        send(cli_socket,send_buf,sizeof(send_buf),0);
        
    
        
    }
    close(cli_socket);
    close(serv_socket);
   
    return 0;
}