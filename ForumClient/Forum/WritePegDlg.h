#pragma once
#include "afxwin.h"
#include "UDPNet.h"
#include "afxcmn.h"
#include"resource.h"

// CWritePegDlg �Ի���

class CWritePegDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CWritePegDlg)

public:
	CWritePegDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CWritePegDlg();
	virtual BOOL OnInitDialog();
// �Ի�������
	enum { IDD = IDD_WRITEDLG };
	afx_msg void OnBnClickedButton1();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_MyTitle;     //����
	CEdit m_Content;    //����
public:
	afx_msg void OnBnClickedButton3();
	CProgressCtrl m_transFilePro;
};
