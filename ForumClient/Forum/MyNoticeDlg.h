#pragma once


// CMyNoticeDlg �Ի���

class CMyNoticeDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMyNoticeDlg)

public:
	CMyNoticeDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMyNoticeDlg();

// �Ի�������
	enum { IDD = IDD_MYNOTICE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
