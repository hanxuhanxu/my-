// MyFavorDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Forum.h"
#include "MyFavorDlg.h"
#include "afxdialogex.h"


// CMyFavorDlg 对话框

IMPLEMENT_DYNAMIC(CMyFavorDlg, CDialogEx)

CMyFavorDlg::CMyFavorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMyFavorDlg::IDD, pParent)
{

}

CMyFavorDlg::~CMyFavorDlg()
{
}

void CMyFavorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMyFavorDlg, CDialogEx)
END_MESSAGE_MAP()


// CMyFavorDlg 消息处理程序
