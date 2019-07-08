// MyDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Forum.h"
#include "MyDlg.h"
#include "afxdialogex.h"
#include"ForumDlg.h"

// CMyDlg 对话框

IMPLEMENT_DYNAMIC(CMyDlg, CDialogEx)

	CMyDlg::CMyDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMyDlg::IDD, pParent)
{

}

CMyDlg::~CMyDlg()
{
}

void CMyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_myTab);
}

BOOL CMyDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_myTab.InsertItem(0, _T("个人资料"));
	m_myTab.InsertItem(1, _T("我的收藏"));
	m_myTab.InsertItem(2, _T("我的关注"));
	m_myTab.InsertItem(3, _T("我的粉丝"));
	m_myTab.InsertItem(4, _T("我的博客"));
	m_myTab.InsertItem(5, _T("我的下载"));

	this->ShowWindow(SW_SHOW);

	m_tabUserInfo.Create(IDD_USER_INFO_DLG,&(m_myTab));
	m_tab2.Create(IDD_MYFAVOR, &(m_myTab));
	m_tab3.Create(IDD_MYNOTICE,&(m_myTab));
	m_tab4.Create(IDD_MYFUNS,  &(m_myTab));
	m_tab5.Create(IDD_MYBLOG,  &(m_myTab));
	m_tab6.Create(IDD_MYDOWN,  &(m_myTab));


	m_myTab.GetClientRect(&tabRect);
	m_tabUserInfo.SetWindowPos(NULL,10,30,tabRect.right -20,tabRect.bottom - 40,SWP_SHOWWINDOW); 

	m_myTab.SetCurFocus(0);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

BEGIN_MESSAGE_MAP(CMyDlg, CDialogEx)
	ON_MESSAGE(UM_MSG,&CMyDlg::OnUserInfoMsg)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CMyDlg::OnTcnSelchangeTab1)
END_MESSAGE_MAP()


// CMyDlg 消息处理程序
LRESULT CMyDlg::OnUserInfoMsg(WPARAM w,LPARAM l)
{
	MyInfo * myinfo=(MyInfo*) w;
	m_tabUserInfo.SendMessage(UM_MSG,(WPARAM)myinfo,l);
	return 0;
}

void CMyDlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码

	switch (m_myTab.GetCurSel())
	{
	case 0:
		m_tabUserInfo.SetWindowPos(NULL,10,30,tabRect.right -30,tabRect.bottom - 40,SWP_SHOWWINDOW);
		m_tab2.SetWindowPos(NULL,10,30,tabRect.right -20,tabRect.bottom - 40,SWP_HIDEWINDOW);
		m_tab3.SetWindowPos(NULL,10,30,tabRect.right -20,tabRect.bottom - 40,SWP_HIDEWINDOW);
		m_tab4.SetWindowPos(NULL,10,30,tabRect.right -20,tabRect.bottom - 40,SWP_HIDEWINDOW);
		m_tab5.SetWindowPos(NULL,10,30,tabRect.right -20,tabRect.bottom - 40,SWP_HIDEWINDOW);
		m_tab6.SetWindowPos(NULL,10,30,tabRect.right -20,tabRect.bottom - 40,SWP_HIDEWINDOW);

		break;
	case 1:
		m_tabUserInfo.SetWindowPos(NULL,10,30,tabRect.right -20,tabRect.bottom - 40,SWP_HIDEWINDOW);
		m_tab2.SetWindowPos(NULL,10,30,tabRect.right -20,tabRect.bottom - 40,SWP_SHOWWINDOW);
		m_tab3.SetWindowPos(NULL,10,30,tabRect.right -20,tabRect.bottom - 40,SWP_HIDEWINDOW);
		m_tab4.SetWindowPos(NULL,10,30,tabRect.right -20,tabRect.bottom - 40,SWP_HIDEWINDOW);
		m_tab5.SetWindowPos(NULL,10,30,tabRect.right -20,tabRect.bottom - 40,SWP_HIDEWINDOW);
		m_tab6.SetWindowPos(NULL,10,30,tabRect.right -20,tabRect.bottom - 40,SWP_HIDEWINDOW);

		break;
	case 2:
		m_tabUserInfo.SetWindowPos(NULL,10,30,tabRect.right -20,tabRect.bottom - 40,SWP_HIDEWINDOW);
		m_tab2.SetWindowPos(NULL,10,30,tabRect.right -20,tabRect.bottom - 40,SWP_HIDEWINDOW);
		m_tab3.SetWindowPos(NULL,10,30,tabRect.right -20,tabRect.bottom - 40,SWP_SHOWWINDOW);
		m_tab4.SetWindowPos(NULL,10,30,tabRect.right -20,tabRect.bottom - 40,SWP_HIDEWINDOW);
		m_tab5.SetWindowPos(NULL,10,30,tabRect.right -20,tabRect.bottom - 40,SWP_HIDEWINDOW);
		m_tab6.SetWindowPos(NULL,10,30,tabRect.right -20,tabRect.bottom - 40,SWP_HIDEWINDOW);

		break;
	case 3:
		m_tabUserInfo.SetWindowPos(NULL,10,30,tabRect.right -20,tabRect.bottom - 40,SWP_HIDEWINDOW);
		m_tab2.SetWindowPos(NULL,10,30,tabRect.right -20,tabRect.bottom - 40,SWP_HIDEWINDOW);
		m_tab3.SetWindowPos(NULL,10,30,tabRect.right -20,tabRect.bottom - 40,SWP_HIDEWINDOW);
		m_tab4.SetWindowPos(NULL,10,30,tabRect.right -20,tabRect.bottom - 40,SWP_SHOWWINDOW);
		m_tab5.SetWindowPos(NULL,10,30,tabRect.right -20,tabRect.bottom - 40,SWP_HIDEWINDOW);
		m_tab6.SetWindowPos(NULL,10,30,tabRect.right -20,tabRect.bottom - 40,SWP_HIDEWINDOW);

		break;
	case 4:
		m_tabUserInfo.SetWindowPos(NULL,10,30,tabRect.right -20,tabRect.bottom - 40,SWP_HIDEWINDOW);
		m_tab2.SetWindowPos(NULL,10,30,tabRect.right -20,tabRect.bottom - 40,SWP_HIDEWINDOW);
		m_tab3.SetWindowPos(NULL,10,30,tabRect.right -20,tabRect.bottom - 40,SWP_HIDEWINDOW);
		m_tab4.SetWindowPos(NULL,10,30,tabRect.right -20,tabRect.bottom - 40,SWP_HIDEWINDOW);
		m_tab5.SetWindowPos(NULL,10,30,tabRect.right -20,tabRect.bottom - 40,SWP_SHOWWINDOW);
		m_tab6.SetWindowPos(NULL,10,30,tabRect.right -20,tabRect.bottom - 40,SWP_HIDEWINDOW);

		break;
	case 5:
		m_tabUserInfo.SetWindowPos(NULL,10,30,tabRect.right -20,tabRect.bottom - 40,SWP_HIDEWINDOW);
		m_tab2.SetWindowPos(NULL,10,30,tabRect.right -20,tabRect.bottom - 40,SWP_HIDEWINDOW);
		m_tab3.SetWindowPos(NULL,10,30,tabRect.right -20,tabRect.bottom - 40,SWP_HIDEWINDOW);
		m_tab4.SetWindowPos(NULL,10,30,tabRect.right -20,tabRect.bottom - 40,SWP_HIDEWINDOW);
		m_tab5.SetWindowPos(NULL,10,30,tabRect.right -20,tabRect.bottom - 40,SWP_HIDEWINDOW);
		m_tab6.SetWindowPos(NULL,10,30,tabRect.right -20,tabRect.bottom - 40,SWP_SHOWWINDOW);

	default:
		break;
	}
	*pResult = 0;
}
