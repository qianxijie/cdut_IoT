/*===============================================================
 *   Copyright (C) 2019 All rights reserved.
 *   
 *   文件名称：mysever.c
 *   创 建 者：liujing
 *   创建日期：2019年12月06日
 *   描    述：
 *
 *   更新日志：
 *
 ================================================================*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <strings.h>
#include "myhead.h"
int main(int argc,const char *argv[])
{
	/*基于TCP/IP的服务器搭建*/

	/*创建套接字 scoket*/
	int sfd = socket(PF_INET,SOCK_STREAM,0);
	if(sfd==-1)
	{
		perror("socket");
		return -1;
	}
	printf("socket ok\n");
	struct sockaddr_in myseraddr={0};
	myseraddr.sin_family =PF_INET;
	myseraddr.sin_port = htons(8888);
	myseraddr.sin_addr.s_addr = inet_addr("0");//0可以改成固定ip地址
	/*设置套结字重用*/
	int opt = 1;
	setsockopt(sfd,SOL_SOCKET,SO_REUSEADDR,(const void*)&opt,sizeof(opt));


	/*绑定ip和端口bind*/
	int ret = bind(sfd,(struct sockaddr *)&myseraddr,sizeof(myseraddr));
	if (ret==-1)
	{
		perror("bind");
		return -1;
	}
	printf("bind ok\n");//绑定成功
	/*启用监听，等待客户端连接listen*/
	ret=listen(sfd,10);
	if (ret==-1)
	{
		perror("listen");
		return -1;
	}
	printf("listen ok,wait connection\n");//监听成功，等待客户端连接
	/*有客户请求连接，需要处理请求accept*/
	while(1)
	{
		int confd = accept(sfd,NULL,NULL);
		if (confd==-1)
		{
			perror("accept");
			return -1;
		}
		printf("accept %d ok\n",confd -3);//建立了多少连接

		/*正常通信 read/write*/
		while(1)
		{
			char buf[1024]={0};
			int count=read(confd,buf,sizeof(buf));
			if(count==-1)
			{
				perror("read");
				return -1;
			}else if(count==0)
			{
				printf("client quit\n");
				break;
			}
			else{
				//连接正常   调用其他函数做事，
				printf("size:%d\n data:%s \n",count,buf);
			}
		}
		close(confd);
		/*关闭未使用的套接字*/
	}
	close(sfd);//服务器结束，关闭监听字
	return 0;
}

