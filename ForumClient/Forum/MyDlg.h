#pragma once
#include "afxcmn.h"
#include"resource.h"
#include"UserInfoDlg.h"
#include"MyBlogDlg.h"
#include"MyFavorDlg.h"
#include"MyFunsDlg.h"
#include"MyNoticeDlg.h"
#include"UserChangeDlg.h"
#include"MyDownDlg.h"

// CMyDlg �Ի���

class CMyDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMyDlg)

public:
	CMyDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMyDlg();
	virtual BOOL OnInitDialog();
// �Ի�������
	enum { IDD = IDD_DLG_MINE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CTabCtrl		m_myTab;
	CUserInfoDlg	m_tabUserInfo;
	CMyFavorDlg		m_tab2;
	CMyNoticeDlg	m_tab3;
	CMyFunsDlg		m_tab4;
	CMyBlogDlg		m_tab5;
	CMyDownDlg		m_tab6;
	CRect			tabRect;
	afx_msg LRESULT OnUserInfoMsg(WPARAM,LPARAM);
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
};
