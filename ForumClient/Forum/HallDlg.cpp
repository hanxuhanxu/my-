// HallDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Forum.h"
#include "HallDlg.h"
#include "afxdialogex.h"
#include"ForumDlg.h"
#include "WritePegDlg.h"

// CHallDlg �Ի���

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
		MAKEINTRESOURCE(IDB_BITMAP1)); // IDB_BITMAP_TESTΪ��ԴͼƬID

	((CButton *)GetDlgItem(IDC_BUTTON10))->SetBitmap(hBitmap); 

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}


BEGIN_MESSAGE_MAP(CHallDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON8, &CHallDlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON1, &CHallDlg::OnBnClickedButton1)
	ON_MESSAGE(UM_MYINFOMSG,&CHallDlg::OnUserInfoMsg)
	ON_BN_CLICKED(IDC_BUTTON9, &CHallDlg::OnBnClickedButton9)
END_MESSAGE_MAP()


// CHallDlg ��Ϣ�������


void CHallDlg::OnBnClickedButton8()  //ˢ��
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_LastArticle.AddString(_T("����һ"));
}


void CHallDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//�����ť �鿴������ҳ
	m_pMyDlg->Create(IDD_DLG_MINE);
	m_pMyDlg->ShowWindow(SW_SHOW);

	CWnd * wnd  = AfxGetMainWnd();
	wnd->SendMessage(UM_TEST,0,0);


}

LRESULT CHallDlg::OnUserInfoMsg(WPARAM w,LPARAM l)
{
	MyInfo * myinfo=(MyInfo*) w;
	HWND hWnd=::FindWindow(NULL,_T("��ҳ"));      //�õ��Ի���ľ��
	CHallDlg* pWnd= (CHallDlg*)CHallDlg::FromHandle(hWnd);
	m_pMyDlg->SendMessage(UM_MSG,(WPARAM)myinfo,0);
	return 0;
}


void CHallDlg::OnBnClickedButton9()   //д����
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_pWritePegDlg->Create(IDD_WRITEDLG);
	m_pWritePegDlg->ShowWindow(SW_SHOW);
}
