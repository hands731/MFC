
// threadTxtDlg.h : ��� ����
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CthreadTxtDlg ��ȭ ����
class CthreadTxtDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CthreadTxtDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_THREADTXT_DIALOG };

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
	CProgressCtrl m_progressbar[5];
	afx_msg void OnBnClickedButton1();
	
	CEdit testEdit;
	CString testStr;
	CStatic static1;
	CStatic static2;
	CString strStatic1;
	


	int int_progressRange[5];

	afx_msg void OnBnClickedButton3();
	CStatic ctr_Static[5];
	CString str_Static[5];
	CStatic m_static22;
	
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton2();
	CButton m_btn[3];
};
