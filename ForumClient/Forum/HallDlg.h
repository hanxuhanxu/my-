#pragma once
#include"resource.h"
#include "afxwin.h"
#include"MyDlg.h"
#include"WritePegDlg.h"

// CHallDlg �Ի���

class CHallDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CHallDlg)

public:
	CHallDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CHallDlg();
	virtual BOOL OnInitDialog();

// �Ի�������
	enum { IDD = IDD_HALL_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:	
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton1();
	afx_msg LRESULT OnUserInfoMsg(WPARAM,LPARAM);	
	afx_msg void OnBnClickedButton9();

public:
	CListBox m_LastArticle;
	CMyDlg * m_pMyDlg;  //������ҳ
	CWritePegDlg  * m_pWritePegDlg;   //д����
};
