#pragma once


// CMyFavorDlg �Ի���

class CMyFavorDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMyFavorDlg)

public:
	CMyFavorDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMyFavorDlg();

// �Ի�������
	enum { IDD = IDD_MYFAVOR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
