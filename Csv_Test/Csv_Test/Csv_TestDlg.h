
// Csv_TestDlg.h : ��� ����
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include <queue>

using namespace std;

// CCsv_TestDlg ��ȭ ����
class CCsv_TestDlg : public CDialog
{
// �����Դϴ�.
public:
	CCsv_TestDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_CSV_TEST_DIALOG };

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
	CButton m_button1;
	CButton m_button2;
	CProgressCtrl m_progress[6];
	afx_msg void OnBnClicked(UINT nID);

	CEdit editText;
	CEdit editText2;
	CString editStr, editStr2;
	CStatic staticStr[6];
	int threadCount;                //�Ӱ迵�� �� �����尳��
	queue<CString> queue;

	afx_msg void OnStnClickedStatic4();
};
