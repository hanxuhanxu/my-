#include "stdafx.h"
#include "UDPNet.h"

bool bFlagQuit;
UDPNet::UDPNet(IMediator* pMediator)
{
	bFlagQuit=true;
	m_socketClient=NULL;
	m_TCPsockClient=NULL;
	m_pMediator=pMediator;
	m_hThread=NULL;
	m_hThreadRecv=NULL;
}


UDPNet::~UDPNet(void)
{
}


bool UDPNet::InitNetWork()
{
	WORD wVersionRequested;
    WSADATA wsaData;
    int err;

    wVersionRequested = MAKEWORD(2, 2);

    err = WSAStartup(wVersionRequested, &wsaData);
    if (err != 0) {

		UnInitNetWork();
        return false;
    }


    if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) {

       UnInitNetWork();
        return false;
    }


//2.雇个人  接口 套接字
	m_socketClient=socket(AF_INET ,SOCK_DGRAM ,IPPROTO_UDP );
	m_TCPsockClient=socket(AF_INET ,SOCK_STREAM ,IPPROTO_TCP );

	//u_long iMode = 0;
	BOOL bval = TRUE;
	//setsockopt(m_sockSend,SOL_SOCKET,SO_BROADCAST,(const char*)&bval,sizeof(bval));
	//ioctlsocket(m_socketClient,FIONBIO,&iMode);
	//ioctlsocket(m_TCPsockClient,FIONBIO,&iMode);

	if(INVALID_SOCKET==m_socketClient)
	{
		UnInitNetWork();
        return false;
	}
	if(INVALID_SOCKET==m_TCPsockClient)
	{
		UnInitNetWork();
        return false;
	}
	TRACE("%d\n",GetLastError());
//3.选址--连接
	sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.S_un.S_addr =GetValidIp();
    addr.sin_port = htons(8000);
	if(SOCKET_ERROR == bind(m_socketClient,(const sockaddr*)&addr,sizeof(addr)))
	{
		UnInitNetWork();
			TRACE("%d\n",GetLastError());
		return false;
	}



	//创建线程
	m_hThread=(HANDLE)_beginthreadex(NULL,0,&ThreadProc,this,0,0);
	/*m_hThreadRecv = (HANDLE)_beginthreadex(NULL,0,&ThreadRecv,this,0,0);*/
	TRACE("%d\n",GetLastError());
	return true;
}

bool UDPNet::InitTCPNetWork()
{
	sockaddr_in addr2;
	addr2.sin_family = AF_INET;
	addr2.sin_addr.S_un.S_addr =_HOST_IP;
    addr2.sin_port = htons(1234);

	if(SOCKET_ERROR == connect(m_TCPsockClient,(const sockaddr*)&addr2,sizeof(addr2)))
	{
		TRACE("%d\n",GetLastError());
		UnInitNetWork();
		TRACE("%d\n",GetLastError());
		return false;
	}

	m_hThreadRecv = (HANDLE)_beginthreadex(NULL,0,&ThreadRecv,this,0,0);

	return true;
}


unsigned  __stdcall  UDPNet::ThreadProc( void * lpvoid)
{
	UDPNet * pthis=(UDPNet*)lpvoid;
	//recv
	char RecvBuf[_DEF_BUFFERSIZE]={0};
	sockaddr_in addrClient;
	int nClientSize=sizeof(sockaddr_in);
	int nRelReadNum=0;
	
	while(/*pthis->*/bFlagQuit)
	{
		nRelReadNum=recvfrom(pthis->m_socketClient,RecvBuf,_DEF_BUFFERSIZE,0,(sockaddr *)&addrClient,&nClientSize);


		  TRACE("%d\n",GetLastError());

		if(nRelReadNum>0)
		{
			//处理
			pthis->m_pMediator->DealData(RecvBuf,addrClient.sin_addr.S_un.S_addr);
		}
	}
	return 0;
}

unsigned  __stdcall UDPNet::ThreadRecv( void * lpvoid)
{
	UDPNet* pthis  = (UDPNet*)lpvoid;
	char* pszbuf = NULL;
	int nRelReadNum;
	int nPackSize;
	CString str; //提示语
	while(bFlagQuit)
	{
		//接收包大小
		nRelReadNum =  recv(pthis->m_TCPsockClient,(char*)&nPackSize,sizeof(int),0);
		if(nRelReadNum <=0)
		{
			continue;
		}
		HWND  mainHwnd = ::GetForegroundWindow();//当前最顶端窗口句柄			
		//接收完整数据包
		 pszbuf = new char[nPackSize];
		 int noffset = 0;
		 while(nPackSize)
		 {
			nRelReadNum =  recv(pthis->m_TCPsockClient,pszbuf+noffset,nPackSize,0);
			noffset += nRelReadNum;
			nPackSize -= nRelReadNum;
	 
		 }
		 	int * ptype=(int *)pszbuf;
			//switch (* ptype)
			//{

			//default:
			//	break;
			//}

		 delete []pszbuf;
		 pszbuf =  NULL;

   }	return 0;
}

bool UDPNet::SendData(long lSendIP, char *szbuf ,int nlen)
{
	sockaddr_in addr;
	addr.sin_family=AF_INET;
	addr.sin_port=htons(/*_DEF_PORT*//*4000*/8003);
	addr.sin_addr.S_un.S_addr=lSendIP;

	if(!szbuf || nlen <=0)
		return false;
	int * ptype=(int *)szbuf;

		if(sendto(m_socketClient,( char *)szbuf,nlen,0,(sockaddr *)&addr,sizeof(addr))<=0)
		{
			TRACE("%d\n",WSAGetLastError());
	         return false;
	    }

	return true;
}


bool UDPNet::SendDataTCP(SOCKET sock,char* szbuf,int nlen)
{
		if(!szbuf || nlen <=0)
		return false;

		//发送包大小
		if(send(m_TCPsockClient,(const char*)&nlen,sizeof(int),0)<0)
		return false;

		//包内容
		if(send(m_TCPsockClient,szbuf,nlen,0)<0)
			return false;
	
		return true;
}

void UDPNet::UnInitNetWork()
{
	bFlagQuit=false;
	WSACleanup();
	if(m_hThreadRecv )
	{
		if(WAIT_TIMEOUT == WaitForSingleObject(m_hThreadRecv,100))
			TerminateThread(m_hThreadRecv,-1);
		
		CloseHandle(m_hThreadRecv);
		m_hThreadRecv = NULL;
	
	}
	 if(m_socketClient)
	 {
		 closesocket(m_socketClient);
		 m_socketClient=INVALID_SOCKET;
		 m_socketClient = NULL;
	 }
	  if(m_TCPsockClient)
	 {
		 shutdown(m_TCPsockClient,SD_BOTH);
		 closesocket(m_TCPsockClient);
		 m_TCPsockClient = NULL;
	 }
	 if(m_hThread)
	 {
		  if( WaitForSingleObject(m_hThread,100) == WAIT_TIMEOUT)
		 {
			 TerminateThread(m_hThread,-1);
		 }
		 CloseHandle(m_hThread);
		 m_hThread=NULL;
	 }

}