
// Ini_TestDlg.h : ��� ����
//

#pragma once
#include "afxwin.h"


// CIni_TestDlg ��ȭ ����
class CIni_TestDlg : public CDialog
{
// �����Դϴ�.
public:
	CIni_TestDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_INI_TEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CEdit editNum;
	CEdit editGA;
	CEdit editNA;
	CEdit editDA;
	CEdit editName;
	CEdit editA;
	CEdit editB;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	CString num, GA, NA, DA, name, A, B;
	int numInt;
	CStatic static1;
	afx_msg void OnBnClickedCheck8();
	CButton check2;
	CButton chek10;
};
