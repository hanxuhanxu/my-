// UserChangeDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Forum.h"
#include "UserChangeDlg.h"
#include "afxdialogex.h"
#include"UDPMediator.h"

// CUserChangeDlg 对话框

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


// CUserChangeDlg 消息处理程序


void CUserChangeDlg::OnBnClickedButton1() //保存修改
{
	// TODO: 在此添加控件通知处理程序代码
	this->DestroyWindow();


	STRU_SEND_INFO_RQ packdef;

	packdef.m_nType = _DEF_PROTOCOL_SENDINFO_RQ;
	WideCharToMultiByte(CP_ACP,0,m_userName,-1,packdef.m_username,sizeof(packdef.m_username),0,0);

	/*得到控件位置*/                       // 报错
	int nIndex1 = m_Sex.GetCurSel();

	/*通过位置找文本*/
	CString strCBText1;
	m_Sex.GetLBText(nIndex1,strCBText1);

	/*放到包*/
	WideCharToMultiByte(CP_ACP,0,strCBText1,-1,packdef.Sex,sizeof(packdef.Sex),0,0);
	WideCharToMultiByte(CP_ACP,0,m_Brief,-1,packdef.brief,sizeof(packdef.brief),0,0);

	m_pMediator->SendData(_HOST_IP,(char*)&packdef,sizeof(packdef));

}


void CUserChangeDlg::OnBnClickedButton2() //取消
{
	// TODO: 在此添加控件通知处理程序代码
	this->DestroyWindow();
}


BOOL CUserChangeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_Sex.AddString(_T("男"));
	m_Sex.AddString(_T("女"));
	m_Sex.SetCurSel(0);


	return TRUE; 
}
