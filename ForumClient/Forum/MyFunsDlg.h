#pragma once


// CMyFunsDlg �Ի���

class CMyFunsDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMyFunsDlg)

public:
	CMyFunsDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMyFunsDlg();

// �Ի�������
	enum { IDD = IDD_MYFUNS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
