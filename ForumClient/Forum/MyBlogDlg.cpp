// MyBlogDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Forum.h"
#include "MyBlogDlg.h"
#include "afxdialogex.h"


// CMyBlogDlg �Ի���

IMPLEMENT_DYNAMIC(CMyBlogDlg, CDialogEx)

CMyBlogDlg::CMyBlogDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMyBlogDlg::IDD, pParent)
{

}

CMyBlogDlg::~CMyBlogDlg()
{
}

void CMyBlogDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMyBlogDlg, CDialogEx)
END_MESSAGE_MAP()


// CMyBlogDlg ��Ϣ�������
