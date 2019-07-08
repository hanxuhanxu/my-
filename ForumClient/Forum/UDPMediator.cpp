#include "stdafx.h"
#include "UDPMediator.h"
#include"UDPNet.h"
#include"ForumDlg.h"


UDPMediator::UDPMediator(CWnd * pWnd)
{
	m_pUDPNetClient=new UDPNet(this);
	m_pWnd=pWnd;
	m_pUserInfoDlg=new CUserInfoDlg;
}


UDPMediator::~UDPMediator(void)
{
    if(m_pUDPNetClient)
	{
		delete(m_pUDPNetClient);
		m_pUDPNetClient=NULL;
	}
	 if(m_pUserInfoDlg)
	{
		delete(m_pUserInfoDlg);
		m_pUserInfoDlg=NULL;
	}
}

static const ProtocolMap m_ProtocolMapEntries[] =
{
	////{_DEF_PROTOCOL_ONLINE_RQ,&CTCPMediator::DealOnLineRq},
	{_DEF_PROTOCOL_ONLINE_RS,&UDPMediator::DealOnLineRs},
	{_DEF_PROTOCOL_REGISTER_RS,&UDPMediator::DealRegisterInfoRs},
	{0,0}

};


bool UDPMediator::open(){
	if( ! m_pUDPNetClient->InitNetWork())
	{
		TRACE("%d\n",GetLastError());
		return false;
	}
	return true;
}
void UDPMediator::close()
{
	m_pUDPNetClient->UnInitNetWork();
}

bool UDPMediator::SendData(long lSendIP, char * szbuf ,int nlen)
{
	in_addr ia;
	ia.S_un.S_addr=lSendIP;
	int * ptype=(int *)szbuf;
		
	switch ( * ptype)
	{
	case _DEF_PROTOCOL_ONLINE_RS:
		{
			STRU_ONLINE* sd=(STRU_ONLINE*)szbuf;
			if( !m_pUDPNetClient->SendData(lSendIP,szbuf,nlen))
			return false;
			break;
		}
	case _DEF_PROTOCOL_REGISTER_RQ:
		{
			STRU_RESGISTER* sd=(STRU_RESGISTER*)szbuf;
			if( !m_pUDPNetClient->SendData(lSendIP,szbuf,nlen))
			return false;
			
		}
		break;
	default:
			STRU_ONLINE *so=(STRU_ONLINE *)szbuf;
			if( !m_pUDPNetClient->SendData(lSendIP,szbuf,nlen))
			return false;
		break;
	}
	return true;
}

bool UDPMediator::SendDataTCP(SOCKET sock, char * szbuf ,int nlen)
{
	int * ptype=(int *)szbuf;
		
	switch ( * ptype)
	{
	case _DEF_PROTOCOL_HANDPEG_RQ:
		{
			STRU_ARTICLE_INFO * sa =(STRU_ARTICLE_INFO * )szbuf;
			if( !m_pUDPNetClient->SendDataTCP(sock,szbuf,nlen))
				return false;
		}
		break;
	default:
		break;
	}
	return true;
}

void UDPMediator::DealData(char * szbuf , long lRecvIP) 
{
	//�õ�����ǰ�ĸ��ֽڴ��������
	int * ptype=(int *)szbuf;
	int nn=sizeof(szbuf);
	//�������� ������Ϣӳ���
	int i = 0;
	while(1)
	{
		if(m_ProtocolMapEntries[i].m_nType == *ptype)
		{
			char * mm=(char *)m_ProtocolMapEntries[i].m_nType;
			(this->*m_ProtocolMapEntries[i].m_pfun)(szbuf,lRecvIP);
			return ;
		}
		else if(m_ProtocolMapEntries[i].m_nType ==0 &&m_ProtocolMapEntries[i].m_pfun ==0 )
			return;

		i++;
	}
}

void UDPMediator::DealDataTCP(char * szbuf ,SOCKET sock) //��tcp�йصĴ������������
{
			int * ptype=(int *)szbuf;
			//switch (* ptype)
			//{

			//default:
			//	break;
			//}
}

void UDPMediator::DealRegisterInfoRs(char * szbuf , long lRecvIP) 
{
	//STRU_REGISTER_RS
	STRU_REGISTER_RS* sr=(STRU_REGISTER_RS*)szbuf;
	if(sr->IfSuccess==1)
	{
		//ע��ɹ�����¼
		CString ID;
		ID.Format(_T("%d"), sr->m_userId);
		MessageBox((HWND)m_pWnd->m_hWnd,ID,_T("ע��ɹ� ����˺�Ϊ"),NULL);
		return;
	}
	else if(sr->IfSuccess==0)
	{
		MessageBox((HWND)m_pWnd->m_hWnd,_T("�û����Ѵ���"),_T("��ʾ"),NULL);
		return;
	}
}

void UDPMediator::DealOnLineRs(char * szbuf , long lRecvIP) 
{
	STRU_ONLINERS* so=(STRU_ONLINERS*)szbuf;
	if(so->IfSuccess==TRUE)
	{
		 this->m_myUserName.Empty();
		 this->m_myUserName="";
		 this->m_myUserName=so->m_username;

		 strcpy_s((char*)&myinfo.m_username,(size_t)sizeof(myinfo.m_username),(char*)&so->m_username);
		 
		 //TCP����
		 m_pUDPNetClient->InitTCPNetWork();		 

		//��¼�ɹ�����ʾ����
		
		 m_pWnd->SendMessage(UM_ONLINEMSG,(WPARAM)&so,lRecvIP);

	}
	else if(so->IfSuccess==FALSE)
	{
		MessageBox((HWND)m_pWnd->m_hWnd,_T("�û������������"),_T("��ʾ"),NULL);
		return;
	}
}

