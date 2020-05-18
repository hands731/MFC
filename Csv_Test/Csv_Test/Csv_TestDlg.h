
// Csv_TestDlg.h : 헤더 파일
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include <queue>

using namespace std;

// CCsv_TestDlg 대화 상자
class CCsv_TestDlg : public CDialog
{
// 생성입니다.
public:
	CCsv_TestDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
	enum { IDD = IDD_CSV_TEST_DIALOG };

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
	CButton m_button1;
	CButton m_button2;
	CProgressCtrl m_progress[6];
	afx_msg void OnBnClicked(UINT nID);

	CEdit editText;
	CEdit editText2;
	CString editStr, editStr2;
	CStatic staticStr[6];
	int threadCount;                //임계영역 들어간 스레드개수
	queue<CString> queue;

	afx_msg void OnStnClickedStatic4();
};
