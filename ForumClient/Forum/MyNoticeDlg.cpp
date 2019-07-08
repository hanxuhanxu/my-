// MyNoticeDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Forum.h"
#include "MyNoticeDlg.h"
#include "afxdialogex.h"


// CMyNoticeDlg 对话框

IMPLEMENT_DYNAMIC(CMyNoticeDlg, CDialogEx)

CMyNoticeDlg::CMyNoticeDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMyNoticeDlg::IDD, pParent)
{

}

CMyNoticeDlg::~CMyNoticeDlg()
{
}

void CMyNoticeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMyNoticeDlg, CDialogEx)
END_MESSAGE_MAP()


// CMyNoticeDlg 消息处理程序
