#pragma once
#include"INet.h"
#include"IMediator.h"

class UDPNet:public INet
{
public:
	UDPNet(IMediator* pMediator);
	~UDPNet(void);
public:
	virtual bool InitNetWork();
	virtual void UnInitNetWork();
	virtual bool SendData(long lSendIP, char *szbuf ,int nlen);
	virtual bool SendDataTCP(SOCKET sock,char* szbuf,int nlen);
	virtual bool InitTCPNetWork();

public:
	static  unsigned  __stdcall ThreadProc( void * );
	static  unsigned  __stdcall ThreadRecv( void * );
public:
	SOCKET m_socketClient;  //udp
	SOCKET m_TCPsockClient;  //tcp
	IMediator*m_pMediator;
	HANDLE m_hThread;
	HANDLE m_hThreadRecv;
public:

};

