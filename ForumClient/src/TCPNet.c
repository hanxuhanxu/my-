#include"../include/TCPNet.h"
#include"../include/thread_pool.h"
#include"../include/lock.h"



#define EPOLLMAX 100000

const char * uname;

void str_error(char * str,int exitno)
{
		perror(str);
		exit(exitno);
}

void CreateUDPSocket()
{
	int len;

	UDPSocket=socket(AF_INET,SOCK_DGRAM,0);
	if(UDPSocket<0)
	{
       	   perror("udp sockfd error\n");
	}
	else
	{
 		printf("udp socket create success\n");
	}
	bzero(&server_udp,sizeof(server_udp));

	server_udp.sin_family=AF_INET;
	server_udp.sin_port=htons(8003);
	server_udp.sin_addr.s_addr=inet_addr(HOST_IP);

	len=sizeof(server_udp);
	if(bind(UDPSocket,(struct sockaddr*)&server_udp,len)<0)
	{
		perror("bind error\n");
	}
	else
	{
		printf("bind udp socket success\n");
	}
 	pthread_t thread_id;

	if((pthread_create(&thread_id, NULL,udp_recv_thread,(void *)UDPSocket))>0)
	{
	    printf("create udp_recv_thread error\n");
		perror("recv thread error\n");
	}
	else
	{
		printf("recv thread create success\n");
	}
	pthread_detach(thread_id);

   // close(sockfd);
//while(1);

}

void CreateTCPSocket()
{
	int len;
	int err;
	//初始化tcp

    	TCPSocket=socket(AF_INET,SOCK_STREAM,0);
	if(TCPSocket<0)
	{
       		perror("tcp sockfd error\n");
	}

	bzero(&server_tcp,sizeof(server_tcp));
	bzero(&client_tcp,sizeof(client_tcp));

	server_tcp.sin_family=AF_INET;
	server_tcp.sin_port=htons(1234);
	server_tcp.sin_addr.s_addr=inet_addr(HOST_IP);

	len=sizeof(server_tcp);
	if(bind(TCPSocket,(struct sockaddr*)&server_tcp,len)<0)
	{
		perror("tcpsocket bind error\n");
		return ;
	}

	if(-1==listen(TCPSocket,128))
	{
        perror("listen error\n");
		return ;
	}


printf("create TCP SOCKET success\n");
	//创建epoll线程
	pthread_t epoll_thread_id;

	if((pthread_create(&epoll_thread_id, NULL,epoll_thread,(void *)TCPSocket))>0)
	{
	    perror("create epoll_thread error\n");
	}
	else
	{
		printf("epoll_thread create success\n");
	}
	pthread_detach(epoll_thread_id);

while(1);
}


void  * udp_recv_thread(void * arg)
{
	int recv_len=0;
	char recv_buf[1024]="";
    	int UDPSocket=(int)arg;
	struct sockaddr_in client_udp;
	socklen_t len=sizeof(client_udp);
    	printf("in recv thread...\n");

    while(1)
	{
		
		recv_len=recvfrom(UDPSocket,recv_buf,BUFFSIZE,0,(struct sockaddr*)&client_udp,&len);
		printf("recv_len %d\n",recv_len);
		if(recv_len>0)
		{
             		printf("recv success\n");
		}
 		else
		{
             		perror("recv failed\n");
		}


		PackdefType *pType = (PackdefType*)recv_buf;
                printf("pType = %d\n",*pType);
		if (*pType == _DEF_PROTOCOL_REGISTER_RQ)//注册
		{
			STRU_RESGISTER* str =(STRU_RESGISTER*) recv_buf;
			printf("用户注册 ：username= %s password=%s \n",str->m_username,str->m_password);
			int id;
			id=sqlAdd(str->m_username, str->m_password);//表中注册获得ip
			//回复包
			STRU_REGISTER_RS rs;
			rs.IfSuccess = 1;
			rs.m_nType = _DEF_PROTOCOL_REGISTER_RS;
			rs.m_userId = id;
			int sen;
			sen=sendto(UDPSocket, (char*)&rs, sizeof(rs), 0, (const sockaddr*)&client_udp, sizeof(client_udp));//给对方回去他的ip
			if(sen>0)
			{
			printf("send STRU_REGISTER_RS success\n");	
			}
		}
		else if(*pType == _DEF_PROTOCOL_ONLINE_RQ)//登录
		{
			
                      	STRU_ONLINE* rq =(STRU_ONLINE*) recv_buf;
			printf("用户登录 ：id= %d password=%s \n",rq->m_userId,rq->m_password);
			STRU_ONLINERS onliners;
STRU_ONLINERS onliners2;

			
			if (sqlfind(rq->m_userId,rq->m_password,&onliners2))
			{
				onliners.IfSuccess = 1;
				onliners.m_nType = _DEF_PROTOCOL_ONLINE_RS;//登录回复
				
for(int i=0;i<64;i++)
{
onliners.m_username[i]=0;
}
strcpy(onliners.m_username, uname);

cout<<"aaaaaaaa uname =========="<<onliners.m_username<<endl;
				//给对方回去信息	
			}
			else
				onliners.IfSuccess = 0;
		int s=sendto(UDPSocket, (char*)&onliners, sizeof(onliners), 0, (const sockaddr*)&client_udp, sizeof(client_udp));
		if(s>0)	
			printf("send STRU_ONLINERS success\n");
		      
		}
	}
	

    close(UDPSocket);
	return NULL;
}

void * tcp_accept_thread(void * arg)
{

	  
	char buf[1024];	  
	socklen_t len=sizeof(client_tcp);
	int accept_fd = accept(TCPSocket, (struct sockaddr*)&client_tcp, &len); 	  
	if(accept_fd < 0)	  
	{		  
		perror("accept error\n");		  
		return NULL;	  
	}	  
	else	  
	{			  
		printf("connected with ip: %s  and port: %d\n", inet_ntop(AF_INET,&client_tcp.sin_addr, buf, 1024), ntohs(client_tcp.sin_port));			 
 	}

	//創建tcp recv 線程
	pthread_t tcp_recv_id;

	if((pthread_create(&tcp_recv_id, NULL, tcp_recv_thread,(void *)TCPSocket))>0)
	{
		perror("tcp_recv_thread error\n");
	}
	else
	{
		printf("tcp_recv_thread create success\n");
	}
	pthread_detach(tcp_recv_id);

	return NULL;
}

void * tcp_recv_thread(void * arg)
{
 	int recv_len=0;
	char recv_buf[1024]="";
    	int TCPSocket=(int)arg;
	struct sockaddr_in client_tcp;
	//int len=sizeof(client_tcp);
    	printf("in tcp recv thread...\n");

    while(1)
	{
		
		recv_len=recv(UDPSocket,recv_buf,BUFFSIZE,0);
		printf("recv_len %d\n",recv_len);
		if(recv_len>0)
		{
             		printf("tcp recv success\n");
				//	exit(-1);
		}
 		else
		{
             		perror("tcp recv failed\n");
		}
	}
	

    close(TCPSocket);
	return NULL;
}

void  * epoll_thread(void * arg)
{
	//树节点类型
	struct epoll_event tmp;
	int epfd;
	//int clientfd;
	int ready;
	//int j;

	//定义就绪队列
	struct epoll_event readyarr[EPOLLMAX];

	if((epfd=epoll_create(EPOLLMAX))==-1)
		str_error("Epoll create error",-1);
	printf("[1] Epoll Create Success..\n");

	//创建线程池
	task_t task;
	thread_pool_t * pool;
	//pthread_mutex_init(&accept_lock,NULL);
	if((pool = thread_pool_create(10,300,100))==NULL){
				str_error("Create Thread Pool Error!",-1);
				perror("thread pool create error\n");
				}
	printf("[2] Thread Pool Create Success..\n");
				//exit(-1);
	

	task.Job = thread_userwork;
	task.arg = (void*)&TCPSocket;

	tmp.events=EPOLLIN;
	tmp.events |= EPOLLET;
	tmp.data.fd=TCPSocket;
	if((epoll_ctl(epfd,EPOLL_CTL_ADD,TCPSocket,&tmp))==-1)
		str_error("epoll_ctl add error",-1);
	printf("[4] Thread Pool Server Runing....\n");

	//epoll阻塞监听事件
	while(pool->thread_shutdown)
	{
		ready=epoll_wait(epfd,readyarr,EPOLLMAX,-1);
		if(ready>0)
		{
			//判断就绪socket是否是serverfd就绪(建立链接)
			//if(readyarr[ready-1].data.fd == TCPSocket)
			//{
			//	socklen_t size = sizeof(client_tcp);
			//	if((clientfd  = accept(TCPSocket,(struct sockaddr *)&client_tcp,&size))==-1)
			//		str_error("Accept Error",-1);
			//	else
			//		printf("connected with ip: %s  and port: %d\n", inet_ntop(AF_INET,&client_tcp.sin_addr, buf, 1024), ntohs(client_tcp.sin_port));

			//	tmp.events = EPOLLIN;
			//	tmp.data.fd = clientfd;
			//	if((epoll_ctl(epfd,EPOLL_CTL_ADD,clientfd,&tmp))==-1)
			//		str_error("Epoll_Ctl Add Error",-1);
			//}
			//else//判断就绪socket是否是clientfd就绪(请求响应)
			//{

			//}
			//--ready;

			thread_add_task(pool,task);
			
		}
		else
		{
			str_error("Epoll Wait Error",-1);
		}
	}
	pthread_exit(NULL);
	close(TCPSocket);
	return NULL;
}

void ConnectMysql()
{
	mysql_init(&mysql);
	/*连接数据库*/
    	if(mysql_real_connect(&mysql,"localhost","root","hanxu","db1",0,NULL,CLIENT_FOUND_ROWS))
      	{
      		printf("connect mysql success\n");

     	}
}

int sqlAdd(char *name, char *password)
{
	int id;
    	std::string sname=string(name);
   	std::string spassword=string(password);
   	//name和password可能也需要转成string
    	string sql = "INSERT INTO db1.t_user(username,userpassword)  values('" + sname + "','" + spassword + "');";

	int k;
	k=mysql_query(&mysql, sql.c_str());
	//printf("k: %d\n",k);

	string sql2="select @@IDENTITY";
	mysql_query(&mysql, sql2.c_str());
	//执行mysql语句
	MYSQL_ROW row;
	MYSQL_RES * result = mysql_store_result(&mysql);
	//获取结果
	row = mysql_fetch_row(result);
	//按行获取下一个
	while (row !=NULL)
	{
		for (int i = 0; i < mysql_num_fields(result); i++)
		{
			cout<<"id"<<" " << row[i]<<endl;//这里可能需要强转
            		string sid=row[i];//先用string接
            		id=atoi(sid.c_str());//转int类型
		}
		row = mysql_fetch_row(result);
	}

return id;
}

bool sqlfind(int id,char *password,STRU_ONLINERS * onliners)
{
	int k;
	char intstr[20];

string pass=string(password);

 	sprintf(intstr,"%d",id);
 	string st=string(intstr);



    	string sql = "SELECT userpassword,username FROM db1.t_user WHERE id =" + st + ";";

	mysql_query(&mysql, sql.c_str());

	MYSQL_RES * result = mysql_store_result(&mysql);


    	int r = mysql_num_rows(result);

	MYSQL_ROW row ;
	row= mysql_fetch_row(result);

	if(r>0)
	{
		for (int i = 0; i < mysql_num_fields(result); i++)
	        {
			if(i==0)
			{
				cout << row[i]<<endl;//这里可能需要强转
				string ps=row[i];
				const char *p;
				p= ps.c_str();
				const char *p2;
		                p2=pass.c_str();
				k=strcmp(p,p2);
				if(k==0)
					printf("login success\n");
				else
					printf("login failed\n");
			}
			if(i==1)
			{
				string name=row[i];
				cout<<"========================="<<name<<endl;
				//onliners->m_username=name.c_str();
				uname=const_cast<char *>(name.c_str());
				printf("uname ====%s\n",uname);
			}

		}		    
	}

	if (r == 0||k!=0)
        {
		//没找到或者密码不对
		printf("没找到或者密码不对");
		return 0;
	}
	else
    	{
		printf("find success\n");
		return 1;
	}
}

int main()
{
	ConnectMysql();
 	CreateUDPSocket();
	CreateTCPSocket();
	//pthread_mutex_init(&accept_lock,NULL);
}
