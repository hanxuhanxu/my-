#pragma once
#include<stdio.h>
#include<signal.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/socket.h>
#include<fcntl.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<openssl/ssl.h>
#include<openssl/err.h>
#include<sys/mman.h>
#include<regex.h>
#include<netdb.h>
#include<openssl/ssl.h>
#include<openssl/err.h>
#include<sys/epoll.h>
#include<pthread.h>
#include<ctype.h>
#include <mysql/mysql.h>
#include <iostream>
#include <list>
#include <netinet/in.h>
#include <sys/epoll.h>
#include <errno.h>
#include <cstdlib>
      
    #include <string>     
    using namespace std;


#ifndef _RES_H_
#define _RES_H_

#define FALSE 0
#define TRUE 1

#define _DEF_BUFFERSIZE  2000*1024   
#define _MAX_READ_SIZE  20*1024*1024  //一次传20M
#define ULONGLONG  unsigned long

#define HOST_IP "192.168.216.128"

#define _DEF_PROTOCOL_BASE  100
#define _DEF_PROTOCOL_ONLINE_RQ                 _DEF_PROTOCOL_BASE  +0
#define _DEF_PROTOCOL_ONLINE_RS                  _DEF_PROTOCOL_BASE  +1
#define _DEF_PROTOCOL_OFFLINE_RQ                _DEF_PROTOCOL_BASE  +2
#define  _DEF_PROTOCOL_REGISTER_RQ              _DEF_PROTOCOL_BASE  +3
#define  _DEF_PROTOCOL_REGISTER_RS               _DEF_PROTOCOL_BASE  +4
#define _DEF_PROTOCOL_SENDINFO_RQ		_DEF_PROTOCOL_BASE   +5	//发送个人信息请求
#define _DEF_PROTOCOL_HANDPEG_RQ		_DEF_PROTOCOL_BASE   +6	//上传文章

typedef int PackdefType;
//上线请求 上线回复 下线请求

struct STRU_ONLINE
{
	PackdefType m_nType;//协议类型
	int m_userId;
	char m_password[64];
};

struct STRU_RESGISTER  //注册
{
	PackdefType m_nType;//协议类型
	char m_username[64];
	char m_password[64];
};

 struct STRU_OFFLINE
{
	PackdefType m_nType;//协议类型
	char m_MyIP[20];
	char m_username[64];
};

struct STRU_ONLINERS
{
	PackdefType m_nType;//协议类型
	int IfSuccess;
	char m_username[64];
};

struct STRU_REGISTER_RS
{
	PackdefType m_nType;//协议类型
	int m_userId;
	int IfSuccess;
};

struct STRU_ARTICLE_INFO  //文章上传包
{
	PackdefType m_nType;
	char title[64];	//标题
	char body[_MAX_READ_SIZE];   //最多一次读取的大小
	int transSize;	//一次传输大小
	int fileOffset;	//偏移量
	ULONGLONG fileLen;//文件大小
	int isfinished;//是否上传完
	int ID;//上传者id
};

#endif
