#pragma once


// CMyBlogDlg �Ի���

class CMyBlogDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMyBlogDlg)

public:
	CMyBlogDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMyBlogDlg();

// �Ի�������
	enum { IDD = IDD_MYBLOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
