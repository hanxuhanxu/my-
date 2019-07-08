#include "../include/thread_pool.h"
#include "../include/res.h"
#include"../include/lock.h"



void * thread_userwork(void * arg)
{
		int serverfd = *(int *)arg;
		struct sockaddr_in clientaddr;
		int clientfd,len,j;
		char ip[16];
		char buf[1500];
		bzero(ip,sizeof(ip));
		bzero(buf,sizeof(buf));
		socklen_t size = sizeof(clientaddr);
		pthread_mutex_lock(&accept_lock);

		if((clientfd = accept(serverfd,(struct sockaddr *)&clientaddr,&size))==-1)
				return NULL;
		pthread_mutex_unlock(&accept_lock);

		printf("Custom output info Client ip:[%s] Client port:[%d]\n",inet_ntop(AF_INET,&clientaddr.sin_addr.s_addr,ip,sizeof(ip)),ntohs(clientaddr.sin_port));

		while((len = read(clientfd,buf,sizeof(buf)))>0)
		{
				//具体工作 接受 发送
				//判断协议包
				PackdefType *pType = (PackdefType*)buf;
                		printf("pType = %d\n",*pType);
				if (*pType == _DEF_PROTOCOL_REGISTER_RQ)//注册
				{
					
				}
				else if(*pType == _DEF_PROTOCOL_ONLINE_RQ)//登录
				{
						      
				}
				else if(*pType == _DEF_PROTOCOL_HANDPEG_RQ) //文章上传包
				{
					STRU_ARTICLE_INFO * sa =(STRU_ARTICLE_INFO *)buf;
					printf("收到文章上传包\n");
 					cout<<"文章标题 "<<sa->title<<endl;
					cout<<"文章内容 "<<sa->body<<endl;
					cout<<"作者ID "<<sa->ID<<endl;
				}
				bzero(buf,sizeof(buf));
		}
		if(len == 0)
		{
				close(clientfd);
				close(serverfd);
		}
		return NULL;
}
