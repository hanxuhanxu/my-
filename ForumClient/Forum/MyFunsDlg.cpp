// MyFunsDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Forum.h"
#include "MyFunsDlg.h"
#include "afxdialogex.h"


// CMyFunsDlg 对话框

IMPLEMENT_DYNAMIC(CMyFunsDlg, CDialogEx)

CMyFunsDlg::CMyFunsDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMyFunsDlg::IDD, pParent)
{

}

CMyFunsDlg::~CMyFunsDlg()
{
}

void CMyFunsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMyFunsDlg, CDialogEx)
END_MESSAGE_MAP()


// CMyFunsDlg 消息处理程序
