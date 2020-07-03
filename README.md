# socket_chatting
After Network class 👑  
(학교 "네트워크" 수업 이후 소캣을 사용하여 구현 해본 채팅프로그램입니다.)  

버퍼 사이즈를 8192로 늘렸지만 송신에서 8000정도를 수신으로 쏴주었는데  
recv()를 끊어서 받는 걸 확인했습니다.  

이론시간에 배웠던 tcp의 전송은 신뢰적이라고 배웠지만   
그렇게 하려면,  
실제 네트워크 상에서는 옵션을 이용해 수신버퍼의 사이즈를 알아내고  
분할 전송을 해야한다는 것을 알아냈습니다.  

<Algorithm>  
#define SPLIT 1000  
buf[10000];  
int size1=0, size2=0, idx=0;  

size1= recv(소켓,buf,sizeof(buf),MSG_PEEK); //옵션을 이용해서 수신버퍼의 사이즈를 알아내고   
size2= size1;  
do  
{  
    size2= size1/SPLIT;  
    recv(소켓,buf[idx], SPLIT,size);  
    idx=idx+SPLIT;      
}while(size2/SPLIT != 0);  
