
// txtSearch_TestDlg.h : ��� ����
//

#pragma once
#include "afxwin.h"


// CtxtSearch_TestDlg ��ȭ ����
class CtxtSearch_TestDlg : public CDialog
{
// �����Դϴ�.
public:
	CtxtSearch_TestDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_TXTSEARCH_TEST_DIALOG };

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
	afx_msg void OnBnClickedButton1();
	CEdit edit1;
	
	afx_msg void OnBnClickedButton2();
};
