// MyFavorDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Forum.h"
#include "MyFavorDlg.h"
#include "afxdialogex.h"


// CMyFavorDlg �Ի���

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


// CMyFavorDlg ��Ϣ�������
