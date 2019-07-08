// HallDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Forum.h"
#include "HallDlg.h"
#include "afxdialogex.h"
#include"ForumDlg.h"
#include "WritePegDlg.h"

// CHallDlg 对话框

IMPLEMENT_DYNAMIC(CHallDlg, CDialogEx)

	CHallDlg::CHallDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CHallDlg::IDD, pParent)
{
	m_pMyDlg=new CMyDlg;
	m_pWritePegDlg=new CWritePegDlg;
}

CHallDlg::~CHallDlg()
{
	if(m_pMyDlg)
	{
		delete(m_pMyDlg);
		m_pMyDlg=NULL;
	}
	if(m_pWritePegDlg)
	{
		delete(m_pWritePegDlg);
		m_pWritePegDlg=NULL;
	}
}

void CHallDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_LastArticle);
}

BOOL CHallDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CString name= ((CForumDlg*)GetParent())->GetMediator()->m_myUserName;
	CButton *pBtn = (CButton *)GetDlgItem(IDC_BUTTON1);
	pBtn->SetWindowText(name);

	HBITMAP hBitmap;
	hBitmap = LoadBitmap(AfxGetInstanceHandle(), 
		MAKEINTRESOURCE(IDB_BITMAP1)); // IDB_BITMAP_TEST为资源图片ID

	((CButton *)GetDlgItem(IDC_BUTTON10))->SetBitmap(hBitmap); 

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}


BEGIN_MESSAGE_MAP(CHallDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON8, &CHallDlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON1, &CHallDlg::OnBnClickedButton1)
	ON_MESSAGE(UM_MYINFOMSG,&CHallDlg::OnUserInfoMsg)
	ON_BN_CLICKED(IDC_BUTTON9, &CHallDlg::OnBnClickedButton9)
END_MESSAGE_MAP()


// CHallDlg 消息处理程序


void CHallDlg::OnBnClickedButton8()  //刷新
{
	// TODO: 在此添加控件通知处理程序代码
	m_LastArticle.AddString(_T("文章一"));
}


void CHallDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	//点击按钮 查看个人主页
	m_pMyDlg->Create(IDD_DLG_MINE);
	m_pMyDlg->ShowWindow(SW_SHOW);

	CWnd * wnd  = AfxGetMainWnd();
	wnd->SendMessage(UM_TEST,0,0);


}

LRESULT CHallDlg::OnUserInfoMsg(WPARAM w,LPARAM l)
{
	MyInfo * myinfo=(MyInfo*) w;
	HWND hWnd=::FindWindow(NULL,_T("首页"));      //得到对话框的句柄
	CHallDlg* pWnd= (CHallDlg*)CHallDlg::FromHandle(hWnd);
	m_pMyDlg->SendMessage(UM_MSG,(WPARAM)myinfo,0);
	return 0;
}


void CHallDlg::OnBnClickedButton9()   //写博客
{
	// TODO: 在此添加控件通知处理程序代码
	m_pWritePegDlg->Create(IDD_WRITEDLG);
	m_pWritePegDlg->ShowWindow(SW_SHOW);
}
