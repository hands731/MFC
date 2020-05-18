
// threadTxtDlg.h : 헤더 파일
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CthreadTxtDlg 대화 상자
class CthreadTxtDlg : public CDialogEx
{
// 생성입니다.
public:
	CthreadTxtDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
	enum { IDD = IDD_THREADTXT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
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
