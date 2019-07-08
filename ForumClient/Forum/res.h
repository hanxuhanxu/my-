#ifndef _PACKDEF_H
#define _PACKDEF_H 

#include<list>
#include <string>
#include<iostream>
#include<WinSock2.h>
using namespace std;


#define _HOST_IP  inet_addr("192.168.216.128")
//#define _MY_IP      inet_addr(/*"10.51.211.173"*/)
#define _MY_IP_STR "192.168.137.1"

//边界值
#define _DEF_PORT 1234   /* 8003*/
#define _DEF_NAME_SIZE  64       //用户名长度
#define _DEF_PASSWORD_SIZE  64
#define _DEF_ID_SIZE   64             //用户id
#define _DEF_DATE_SIZE	64
#define _DEF_SIZE 4096       
#define _DEF_BUFFERSIZE  2000*1024   
#define _MAX_PROTOCOL_LEN 100    //协议长度
#define _MAX_READ_SIZE 20480


//消息
#define UM_ONLINEMSG      WM_USER + 1
#define UM_MYINFOMSG    WM_USER + 2
#define UM_TEST  WM_USER + 3
#define UM_MSG  WM_USER + 4
//#define UM_FILEINFOMSG   WM_USER + 5
//#define UM_PICINFOMSG    WM_USER + 6
//#define UM_ONLINE_ADD   WM_USER + 7

////网络消息
//#define NM_READMSG  WM_USER + 50

//协议包类型

#define _DEF_PROTOCOL_BASE  100
#define _DEF_PROTOCOL_ONLINE_RQ                 _DEF_PROTOCOL_BASE   +0     //登录
#define _DEF_PROTOCOL_ONLINE_RS                  _DEF_PROTOCOL_BASE  +1     //登录回复
#define _DEF_PROTOCOL_OFFLINE_RQ                _DEF_PROTOCOL_BASE   +2     //下线
#define  _DEF_PROTOCOL_REGISTER_RQ              _DEF_PROTOCOL_BASE   +3     //注册
#define  _DEF_PROTOCOL_REGISTER_RS               _DEF_PROTOCOL_BASE  +4     //注册回复
#define _DEF_PROTOCOL_SENDINFO_RQ				_DEF_PROTOCOL_BASE   +5		//发送个人信息请求
#define _DEF_PROTOCOL_HANDPEG_RQ				_DEF_PROTOCOL_BASE   +6		//上传文章

//协议包
typedef int PackdefType;
//上线请求 上线回复 下线请求

struct MyInfo
{
	int m_userId;
	char m_username[_DEF_NAME_SIZE];
	char m_password[_DEF_PASSWORD_SIZE];
};

struct User  //用户结构体
{
	char m_userId[_DEF_ID_SIZE];
	char m_username[_DEF_NAME_SIZE];
};


struct STRU_ONLINE  //登录请求包
{
	PackdefType m_nType;//协议类型
	int m_userId;
	char m_password[_DEF_PASSWORD_SIZE];
};

struct STRU_RESGISTER  //注册
{
	PackdefType m_nType;//协议类型
	char m_username[_DEF_NAME_SIZE];
	char m_password[_DEF_PASSWORD_SIZE];
};

 struct STRU_OFFLINE
{
	PackdefType m_nType;//协议类型
	char m_MyIP[16];
	char m_username[_DEF_PASSWORD_SIZE];
};

struct STRU_ONLINERS
{
	PackdefType m_nType;//协议类型
	int IfSuccess;
	char  m_username[20]; //用户名
};

struct STRU_REGISTER_RS
{
	PackdefType m_nType;//协议类型
	int m_userId;	
	int IfSuccess;
};

struct STRU_SEND_INFO_RQ
{
	PackdefType m_nType;
	char m_username[_DEF_NAME_SIZE]; //用户名
	char Sex[_DEF_DATE_SIZE];		//性别
	char date[_DEF_DATE_SIZE];		//生日
	char brief[_DEF_SIZE];			//简介
};

struct STRU_SEND_INFO_RS
{
	PackdefType m_nType;
	BOOL IfSuccess;
	char m_username[_DEF_NAME_SIZE]; //用户名
	bool Sex;						//true 为 女  false 为 男
	char date[_DEF_DATE_SIZE];		//生日
	char brief[_DEF_SIZE];			//简介
};

struct STRU_ARTICLE_INFO  //文章上传包
{
	PackdefType m_nType;
	char	title[64];							//标题
	char body[_MAX_READ_SIZE];   //最多一次读取的大小
	int transSize;								//一次传输大小
	int fileOffset;								//偏移量
	ULONGLONG fileLen;				//文件大小
	BOOL isfinished;						//是否上传完
	int		 ID;									//上传者id
};
static long GetValidIp()
	{
		char szName[20] = {0};
		struct hostent *remoteHost = NULL;
		long ip;
		struct in_addr addr;

		//1.获得主机名
		if(!gethostname(szName,sizeof(szName)))
		{
				//2.IPLIST		
			remoteHost = gethostbyname(szName);
			int i = 0;
			while (remoteHost->h_addr_list[i] != 0) {
                 addr.s_addr = *(u_long *) remoteHost->h_addr_list[i++];
				 ip= addr.s_addr ;
            }
		}
		return ip;
	}


#endif