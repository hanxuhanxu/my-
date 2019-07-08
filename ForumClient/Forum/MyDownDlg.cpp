// MyDownDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Forum.h"
#include "MyDownDlg.h"
#include "afxdialogex.h"


// CMyDownDlg 对话框

IMPLEMENT_DYNAMIC(CMyDownDlg, CDialogEx)

CMyDownDlg::CMyDownDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMyDownDlg::IDD, pParent)
{

}

CMyDownDlg::~CMyDownDlg()
{
}

void CMyDownDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMyDownDlg, CDialogEx)
END_MESSAGE_MAP()


// CMyDownDlg 消息处理程序
