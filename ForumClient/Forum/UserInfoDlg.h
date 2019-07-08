#pragma once
#include"resource.h"
#include "afxwin.h"
#include"res.h"
#include"UserChangeDlg.h"
// CUserInfoDlg �Ի���

class CUserInfoDlg : public CDialog
{
	DECLARE_DYNAMIC(CUserInfoDlg)

public:
	CUserInfoDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CUserInfoDlg();
	virtual BOOL OnInitDialog();

// �Ի�������
	enum { IDD = IDD_USER_INFO_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton3();
	afx_msg LRESULT OnUserInfoMsg(WPARAM,LPARAM);
	CEdit m_myID;
	CEdit m_myNameInfo;
	CString m_edtID;
	CString m_edtName;
	MyInfo m_Info;
	CUserChangeDlg* pDlg;
	CComboBox m_ShowSex;
	CString m_ShowDate;
	CString m_ShowBrief;
};
