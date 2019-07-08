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

//�߽�ֵ
#define _DEF_PORT 1234   /* 8003*/
#define _DEF_NAME_SIZE  64       //�û�������
#define _DEF_PASSWORD_SIZE  64
#define _DEF_ID_SIZE   64             //�û�id
#define _DEF_DATE_SIZE	64
#define _DEF_SIZE 4096       
#define _DEF_BUFFERSIZE  2000*1024   
#define _MAX_PROTOCOL_LEN 100    //Э�鳤��
#define _MAX_READ_SIZE 20480


//��Ϣ
#define UM_ONLINEMSG      WM_USER + 1
#define UM_MYINFOMSG    WM_USER + 2
#define UM_TEST  WM_USER + 3
#define UM_MSG  WM_USER + 4
//#define UM_FILEINFOMSG   WM_USER + 5
//#define UM_PICINFOMSG    WM_USER + 6
//#define UM_ONLINE_ADD   WM_USER + 7

////������Ϣ
//#define NM_READMSG  WM_USER + 50

//Э�������

#define _DEF_PROTOCOL_BASE  100
#define _DEF_PROTOCOL_ONLINE_RQ                 _DEF_PROTOCOL_BASE   +0     //��¼
#define _DEF_PROTOCOL_ONLINE_RS                  _DEF_PROTOCOL_BASE  +1     //��¼�ظ�
#define _DEF_PROTOCOL_OFFLINE_RQ                _DEF_PROTOCOL_BASE   +2     //����
#define  _DEF_PROTOCOL_REGISTER_RQ              _DEF_PROTOCOL_BASE   +3     //ע��
#define  _DEF_PROTOCOL_REGISTER_RS               _DEF_PROTOCOL_BASE  +4     //ע��ظ�
#define _DEF_PROTOCOL_SENDINFO_RQ				_DEF_PROTOCOL_BASE   +5		//���͸�����Ϣ����
#define _DEF_PROTOCOL_HANDPEG_RQ				_DEF_PROTOCOL_BASE   +6		//�ϴ�����

//Э���
typedef int PackdefType;
//�������� ���߻ظ� ��������

struct MyInfo
{
	int m_userId;
	char m_username[_DEF_NAME_SIZE];
	char m_password[_DEF_PASSWORD_SIZE];
};

struct User  //�û��ṹ��
{
	char m_userId[_DEF_ID_SIZE];
	char m_username[_DEF_NAME_SIZE];
};


struct STRU_ONLINE  //��¼�����
{
	PackdefType m_nType;//Э������
	int m_userId;
	char m_password[_DEF_PASSWORD_SIZE];
};

struct STRU_RESGISTER  //ע��
{
	PackdefType m_nType;//Э������
	char m_username[_DEF_NAME_SIZE];
	char m_password[_DEF_PASSWORD_SIZE];
};

 struct STRU_OFFLINE
{
	PackdefType m_nType;//Э������
	char m_MyIP[16];
	char m_username[_DEF_PASSWORD_SIZE];
};

struct STRU_ONLINERS
{
	PackdefType m_nType;//Э������
	int IfSuccess;
	char  m_username[20]; //�û���
};

struct STRU_REGISTER_RS
{
	PackdefType m_nType;//Э������
	int m_userId;	
	int IfSuccess;
};

struct STRU_SEND_INFO_RQ
{
	PackdefType m_nType;
	char m_username[_DEF_NAME_SIZE]; //�û���
	char Sex[_DEF_DATE_SIZE];		//�Ա�
	char date[_DEF_DATE_SIZE];		//����
	char brief[_DEF_SIZE];			//���
};

struct STRU_SEND_INFO_RS
{
	PackdefType m_nType;
	BOOL IfSuccess;
	char m_username[_DEF_NAME_SIZE]; //�û���
	bool Sex;						//true Ϊ Ů  false Ϊ ��
	char date[_DEF_DATE_SIZE];		//����
	char brief[_DEF_SIZE];			//���
};

struct STRU_ARTICLE_INFO  //�����ϴ���
{
	PackdefType m_nType;
	char	title[64];							//����
	char body[_MAX_READ_SIZE];   //���һ�ζ�ȡ�Ĵ�С
	int transSize;								//һ�δ����С
	int fileOffset;								//ƫ����
	ULONGLONG fileLen;				//�ļ���С
	BOOL isfinished;						//�Ƿ��ϴ���
	int		 ID;									//�ϴ���id
};
static long GetValidIp()
	{
		char szName[20] = {0};
		struct hostent *remoteHost = NULL;
		long ip;
		struct in_addr addr;

		//1.���������
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