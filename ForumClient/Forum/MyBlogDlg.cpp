// MyBlogDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Forum.h"
#include "MyBlogDlg.h"
#include "afxdialogex.h"


// CMyBlogDlg 对话框

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


// CMyBlogDlg 消息处理程序
