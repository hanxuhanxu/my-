// UserInfoDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Forum.h"
#include "afxdialogex.h"
#include"ForumDlg.h"

// CUserInfoDlg �Ի���

IMPLEMENT_DYNAMIC(CUserInfoDlg, CDialog)

	CUserInfoDlg::CUserInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUserInfoDlg::IDD, pParent)
	, m_edtID(_T(""))
	, m_edtName(_T(""))
	, m_ShowDate(_T(""))
	, m_ShowBrief(_T(""))
{

}

CUserInfoDlg::~CUserInfoDlg()
{
}

void CUserInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_myID);
	DDX_Control(pDX, IDC_EDIT2, m_myNameInfo);
	DDX_Text(pDX, IDC_EDIT1, m_edtID);
	DDX_Text(pDX, IDC_EDIT2, m_edtName);
	DDX_Control(pDX, IDC_COMBO3, m_ShowSex);
	DDX_Text(pDX, IDC_EDIT3, m_ShowDate);
	DDX_Text(pDX, IDC_EDIT4, m_ShowBrief);
}

BOOL CUserInfoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	pDlg = new CUserChangeDlg;

	UpdateData(TRUE);
	CString str=_T("���                                       ");
	CString info=(CString)m_Info.m_username;
	//str.Format(_T("%s"), ((CForumDlg*)GetParent())->GetMediator()->myinfo.m_username);
	//m_edtName= str;
	//WideCharToMultiByte(CP_ACP,0,str,-1, ((CForumDlg*)GetParent())->GetMediator()->myinfo.m_username,sizeof( ((CForumDlg*)GetParent())->GetMediator()->myinfo.m_username),0,0);
	//m_edtName= info;
	//m_tabUserInfo.m_edtName= ((CForumDlg*)GetParent())->GetMediator()->m_myUserName;
	UpdateData(FALSE);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

BEGIN_MESSAGE_MAP(CUserInfoDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON3, &CUserInfoDlg::OnBnClickedButton3)
	ON_MESSAGE(UM_MSG,&CUserInfoDlg::OnUserInfoMsg)
END_MESSAGE_MAP()


// CUserInfoDlg ��Ϣ�������


void CUserInfoDlg::OnBnClickedButton3()  //�޸�����
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	pDlg->Create(IDD_USER_CHANGE_DLG);
	
}

LRESULT CUserInfoDlg::OnUserInfoMsg(WPARAM w,LPARAM l)
{
	//��ʾID��name
	MyInfo * myinfo=(MyInfo*) w;
	m_Info=*myinfo;
	UpdateData(TRUE);
	CString ID;
	ID.Format(_T("%d"),m_Info.m_userId);
	CString Name=(CString)m_Info.m_username;
	m_edtName= Name;
	m_edtID=ID;
	UpdateData(FALSE);
	ShowWindow(SW_SHOW);

	return 0;
}