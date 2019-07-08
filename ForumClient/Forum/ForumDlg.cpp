
// ForumDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Forum.h"
#include "ForumDlg.h"
#include "afxdialogex.h"
#include"UDPMediator.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CForumDlg 对话框



CForumDlg::CForumDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CForumDlg::IDD, pParent)
	, m_UserName(_T(""))
	, m_Password(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pMediator=new UDPMediator(this);
	m_myname="";
	m_pHallDlg=new CHallDlg;
}

void CForumDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_UserName);
	DDX_Text(pDX, IDC_EDIT2, m_Password);
}

BEGIN_MESSAGE_MAP(CForumDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CForumDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CForumDlg::OnBnClickedButton2)
	ON_MESSAGE(UM_ONLINEMSG,&CForumDlg::OnLineMsg) 
	ON_MESSAGE(UM_TEST,&CForumDlg::OnTestMsg)
END_MESSAGE_MAP()


// CForumDlg 消息处理程序

BOOL CForumDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
		if(!m_pMediator->open())
	{
		TRACE("%d\n",GetLastError());
		MessageBox(_T("open failed"));
		return FALSE;
	}

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CForumDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CForumDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CForumDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CForumDlg::OnBnClickedButton1()  //注册
{
	// TODO: 在此添加控件通知处理程序代码
UpdateData();
	int nlen = m_UserName.GetLength();
	if(nlen <0 || nlen >16)
	{
		MessageBox(_T("用户名请输入1-16位有效字符"));
		return;
	}
	 nlen = m_Password.GetLength();
	if(nlen <6 || nlen >16)
	{
		MessageBox(_T("密码请输入6-16位有效字符"));
		return;
	}

	//sd5加密
	CString src =m_Password/*"fasdfasdfasdfnmmw,enrsudfnsmndfejkjhuasdmnf"*/;
	Md5Encode encode_obj;
	std::string s;
	s=CW2A(src.GetString());
	string ret = encode_obj.Encode(s);

	m_Password=ret.c_str();

	m_pMediator->m_myUserName=m_UserName;

    STRU_RESGISTER so;
	so.m_nType=_DEF_PROTOCOL_REGISTER_RQ;
	WideCharToMultiByte(CP_ACP,0,m_UserName,-1,so.m_username,sizeof(so.m_username),0,0);
	WideCharToMultiByte(CP_ACP,0,m_Password,-1,so.m_password,sizeof(so.m_password),0,0);

	m_pMediator->SendData(_HOST_IP,(char*)&so,sizeof(so));
}


void CForumDlg::OnBnClickedButton2()  //登录
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();

	int nlen = m_UserName.GetLength();
	if(nlen <0 || nlen >16)
	{
		MessageBox(_T("用户名请输入1-16位有效字符"));
		return;
	}
	 nlen = m_Password.GetLength();
	if(nlen <6 || nlen >16)
	{
		MessageBox(_T("密码请输入6-16位有效字符"));
		return;
	
	}

	CString src =m_Password/*"fasdfasdfasdfnmmw,enrsudfnsmndfejkjhuasdmnf"*/;
	Md5Encode encode_obj;
	std::string s;
	s=CW2A(src.GetString());
	string ret = encode_obj.Encode(s);

	m_Password=ret.c_str();

	
	STRU_ONLINE so;
	so.m_nType=_DEF_PROTOCOL_ONLINE_RQ;
	so.m_userId= _ttoi(m_UserName);

	WideCharToMultiByte(CP_ACP,0,m_Password,-1,so.m_password,sizeof(so.m_password),0,0);
	m_pMediator->myinfo.m_userId= _ttoi(m_UserName);
	m_pMediator->SendData(_HOST_IP,(char*)&so,sizeof(so));
}

LRESULT CForumDlg::OnLineMsg(WPARAM w,LPARAM l)
{
	 m_pHallDlg->Create(IDD_HALL_DLG);
	 m_pHallDlg->ShowWindow(SW_SHOW);
	return 0;
}

LRESULT CForumDlg::OnTestMsg(WPARAM w,LPARAM l)
{
		HWND hWnd=::FindWindow(NULL,_T("首页"));      //得到对话框的句柄
        CHallDlg* pWnd= (CHallDlg*)CHallDlg::FromHandle(hWnd);
		(m_pMediator->myinfo).m_userId= _ttoi(m_UserName);
		pWnd->SendMessage(UM_MYINFOMSG,(WPARAM)&m_pMediator->myinfo,l);
	return 0;
}