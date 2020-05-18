
// Ini_TestDlg.h : 헤더 파일
//

#pragma once
#include "afxwin.h"


// CIni_TestDlg 대화 상자
class CIni_TestDlg : public CDialog
{
// 생성입니다.
public:
	CIni_TestDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
	enum { IDD = IDD_INI_TEST_DIALOG };

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
