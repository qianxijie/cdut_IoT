/*==============================================================
 *   Copyright (C) 2019 All rights reserved.
 *   
 *   文件名称：clt.c
 *   创 建 者：liujing
 *   创建日期：2019年12月06日
 *   描    述：
 *
 *   更新日志：
 *
 ================================================================*/
#include<stdio.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h> /* superset of previous */
#include <sys/types.h>          /* See NOTES */
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
int main()
{
	int connectfd;
	int ret=0;
	//创建套接字
	connectfd= socket(PF_INET,SOCK_STREAM,0);
	if(ret < 0)
	{
		perror("socket fail\n");
		return -1;
	}
	//初始化ip
	struct sockaddr_in servaddr={0};
	memset(&servaddr,0,sizeof(servaddr));

	servaddr.sin_family = PF_INET;
	servaddr.sin_port = htons(8888);//要连接的服务器端口号
	servaddr.sin_addr.s_addr = inet_addr("0");//要连接的服务器ip
		//连接通信
		ret = connect(connectfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
	if(-1 == ret)
	{
		perror("connect fail\n");
		return -1;
	}
	char writebuf[1024]={0};//定义一个buf  
	while(1)
	{
		memset(writebuf,0,sizeof(writebuf));//清空buf
		printf("please input string\n");
		scanf("%s",writebuf);//输入聊天信息
			ret = write(connectfd,writebuf,strlen(writebuf));
		if(-1 == ret)
		{
			perror("write fail \n");
			return -1;
		}
		printf("write:%d\n",ret);
		/*char readbuf[1024]={0};
		  read(connectfd,readbuf,sizeof(readbuf));
		  printf(%s \n",readbuf);*/

	}
	close(connectfd);
	return 0;
}


