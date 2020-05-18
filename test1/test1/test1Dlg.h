
// test1Dlg.h : 헤더 파일
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// Ctest1Dlg 대화 상자
class Ctest1Dlg : public CDialog
{
// 생성입니다.
public:
	Ctest1Dlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
	enum { IDD = IDD_TEST1_DIALOG };

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
	CString myStr;        //리스트에서 넘기는 String
	CEdit insertEdit;
	CButton txtSaveButton;
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	CButton txtLoadButton;
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton8();
};
