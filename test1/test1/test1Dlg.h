
// test1Dlg.h : ��� ����
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// Ctest1Dlg ��ȭ ����
class Ctest1Dlg : public CDialog
{
// �����Դϴ�.
public:
	Ctest1Dlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_TEST1_DIALOG };

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
	CListCtrl List1;
	CListCtrl List2;
	
	CButton button1;
	CButton button2;
	CButton leftButton;
	CButton delButton;
	CButton rightButton;
	afx_msg void OnBnClickedButton1();
	CButton insertButton;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	int list2Count;
	int list1Count;
	CString editString;
	CString myStr;        //����Ʈ���� �ѱ�� String
	CEdit insertEdit;
	CButton txtSaveButton;
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	CButton txtLoadButton;
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton8();
};
