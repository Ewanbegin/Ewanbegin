#include "fileheader.h"
/*
实现广播发送
*/
int main(int argc, char const *argv[])
{

	if(argc!=4)
	{
		printf("error\n");
		exit(-1);
	}
	int socket1=socket(AF_INET,SOCK_DGRAM,0);
    //监听套接字
    if(socket1==-1)
    {
    	perror("socket:");
    	exit(-1);
    }
    //设置套接字支持广播发送
    int isbroadcast=1;
    setsockopt(socket1,SOL_SOCKET,SO_BROADCAST,(void*)&isbroadcast,sizeof(isbroadcast));
    //设置自身地址结构
    struct sockaddr_in seraddr;
    bzero(&seraddr,sizeof(seraddr));
    seraddr.sin_family=AF_INET;
    //seraddr.sin_port=htons(PORT1);
    seraddr.sin_port=htons(atoi(argv[1]));
    seraddr.sin_addr.s_addr=INADDR_ANY;

    //绑定自己的地址结构
    if(bind(socket1,(struct sockaddr*)&seraddr,sizeof(seraddr))==-1)
	{
		perror("bind fail:");
		exit(-1);
	}

	//设置我将要发送消息到的地址结构
    struct sockaddr_in cliaddr;
    bzero(&seraddr,sizeof(cliaddr));
    cliaddr.sin_family=AF_INET;
    cliaddr.sin_port=htons(atoi(argv[2]));
    //使用广播地址
    cliaddr.sin_addr.s_addr=inet_addr("192.168.252.255");

    int addrlen=sizeof(cliaddr);

    char  buf[1024];
   // while(1)
    {
      if(argv[3][0]=='y')
      {
         gets(buf);
         int len=sendto(socket1,buf,strlen(buf),0,(struct sockaddr*)&cliaddr,sizeof(cliaddr));
      }
      else
      {
          bzero(buf,sizeof(buf));
          recvfrom(socket1,buf,sizeof(buf)-1,0,(struct sockaddr*)&cliaddr,&addrlen);
          printf("msg:%s\n",buf);
      }     
    }   
	return 0;
}