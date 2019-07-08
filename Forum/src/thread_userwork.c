#include "../include/thread_pool.h"
#include "../include/res.h"
#include"../include/lock.h"
//#include"../include/TCPNet.h"

void DealFileRq(char * szbuf);
pthread_mutex_t file_write_lock;
void * file_recv_thread(void *);

void * thread_userwork(void * arg)
{
		int serverfd = *(int *)arg;
		struct sockaddr_in clientaddr;
		int clientfd,len;
		char ip[16];
		char buf[1500];
		bzero(ip,sizeof(ip));
		bzero(buf,sizeof(buf));
		socklen_t size = sizeof(clientaddr);
		pthread_mutex_lock(&accept_lock);
		//pthread_mutex_t file_write_lock;
		pthread_mutex_init(&accept_lock,NULL);

		if((clientfd = accept(serverfd,(struct sockaddr *)&clientaddr,&size))==-1)
				return NULL;
		pthread_mutex_unlock(&accept_lock);

		printf("Custom output info Client ip:[%s] Client port:[%d]\n",inet_ntop(AF_INET,&clientaddr.sin_addr.s_addr,ip,sizeof(ip)),ntohs(clientaddr.sin_port));

		while((len = read(clientfd,buf,sizeof(buf)))>0)
		{
				//具体工作 接受 发送
				//判断协议包
				PackdefType *pType = (PackdefType*)buf;
                		//printf("pType = %d\n",*pType);
				if (*pType == _DEF_PROTOCOL_REGISTER_RQ)//注册
				{
					
				}
				else if(*pType == _DEF_PROTOCOL_ONLINE_RQ)//登录
				{
						      
				}
				else if(*pType == _DEF_PROTOCOL_HANDPEG_RQ) //文章上传包
				{
					STRU_ARTICLE_INFO * sa =(STRU_ARTICLE_INFO *)buf;
					//创建n个线程
					//int num=sa->fileLen % (_MAX_READ_SIZE)==0?sa->fileLen % (_MAX_READ_SIZE):sa->fileLen % (_MAX_READ_SIZE)+1;
					pthread_t file_recv_thread_id;
					//if(sa->isfinished!=0) //只有第一次上传时创建线程们
					//{
						//for(int i=0;i<num;i++)
						//{
							if((pthread_create(&file_recv_thread_id, NULL,file_recv_thread,(void *)sa))>0)
							{
							    perror("create file_recv_thread error\n");
							}
							else
							{
								printf("file_recv_thread create success\n");
							}

					//DealFileRq((char *)sa);
				}
				bzero(buf,sizeof(buf));
		}
		if(len == 0)
		{
				close(clientfd);
				close(serverfd);
				//关闭锁
				pthread_mutex_destroy(&file_write_lock);
		}
		return NULL;
}

void DealFileRq(char * szbuf)
{
      //创建n个线程
	STRU_ARTICLE_INFO * sa =(STRU_ARTICLE_INFO *)szbuf;
	printf("收到文章上传包\n");
	cout<<"文章标题 "<<sa->title<<endl;
   	cout<<"作者ID "<<sa->ID<<endl;
	
	
}

void * file_recv_thread(void * szbuf)  //文件接受线程
{		
		STRU_ARTICLE_INFO * sa =(STRU_ARTICLE_INFO *)szbuf;
		//加锁，创建文件，写入，解锁
		pthread_mutex_lock(&file_write_lock);
		int filefd;
int result;
		char* szpath="/home/colin/Forum/file";
		//szpath=szpath+"\\";
		//szpath=szpath+sa->title;
		filefd = open("/home/colin/Forum/file/aa.txt",O_RDWR| O_CREAT | O_TRUNC);
        	if (filefd == -1) 
		{
           		 perror("open error");
            	         return NULL;
		}
		else{
			if((result= write(filefd+sa->fileOffset-_MAX_READ_SIZE, sa->body, _MAX_READ_SIZE) )== -1) 
			{
				perror("write error");
				return NULL;
			}
			else
				cout<<"write success "<<result<<endl;
		} 
 		close(filefd);
		pthread_mutex_unlock(&file_write_lock);
		
		return NULL;
}
