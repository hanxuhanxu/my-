// UserChangeDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Forum.h"
#include "UserChangeDlg.h"
#include "afxdialogex.h"
#include"UDPMediator.h"

// CUserChangeDlg �Ի���

IMPLEMENT_DYNAMIC(CUserChangeDlg, CDialogEx)

	CUserChangeDlg::CUserChangeDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CUserChangeDlg::IDD, pParent)
	, m_userName(_T(""))
	, m_date(_T(""))
	, m_Brief(_T(""))
{
	m_pMediator=new UDPMediator(this);
}

CUserChangeDlg::~CUserChangeDlg()
{
}

void CUserChangeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT6, m_userName);
	DDX_Control(pDX, IDC_COMBO1, m_Sex);
	DDX_Text(pDX, IDC_EDIT5, m_date);
	DDX_Text(pDX, IDC_EDIT2, m_Brief);
}


BEGIN_MESSAGE_MAP(CUserChangeDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CUserChangeDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CUserChangeDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CUserChangeDlg ��Ϣ�������


void CUserChangeDlg::OnBnClickedButton1() //�����޸�
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	this->DestroyWindow();


	STRU_SEND_INFO_RQ packdef;

	packdef.m_nType = _DEF_PROTOCOL_SENDINFO_RQ;
	WideCharToMultiByte(CP_ACP,0,m_userName,-1,packdef.m_username,sizeof(packdef.m_username),0,0);

	/*�õ��ؼ�λ��*/                       // ����
	int nIndex1 = m_Sex.GetCurSel();

	/*ͨ��λ�����ı�*/
	CString strCBText1;
	m_Sex.GetLBText(nIndex1,strCBText1);

	/*�ŵ���*/
	WideCharToMultiByte(CP_ACP,0,strCBText1,-1,packdef.Sex,sizeof(packdef.Sex),0,0);
	WideCharToMultiByte(CP_ACP,0,m_Brief,-1,packdef.brief,sizeof(packdef.brief),0,0);

	m_pMediator->SendData(_HOST_IP,(char*)&packdef,sizeof(packdef));

}


void CUserChangeDlg::OnBnClickedButton2() //ȡ��
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	this->DestroyWindow();
}


BOOL CUserChangeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_Sex.AddString(_T("��"));
	m_Sex.AddString(_T("Ů"));
	m_Sex.SetCurSel(0);


	return TRUE; 
}
