#pragma once


// CMyDownDlg �Ի���

class CMyDownDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMyDownDlg)

public:
	CMyDownDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMyDownDlg();

// �Ի�������
	enum { IDD = IDD_MYDOWN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
