
// Csv_TestDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "Csv_Test.h"
#include "Csv_TestDlg.h"
#include "afxdialogex.h"
#include "math.h"
#include <queue>
#include <iostream>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#define threadNum 4					//스레드 최대사용 개수
#define	progressNum 200
CSemaphore g_sem(threadNum	, threadNum);
CCriticalSection g_cs;

// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCsv_TestDlg 대화 상자




CCsv_TestDlg::CCsv_TestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCsv_TestDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCsv_TestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_PROGRESS1, m_progress[0]);
	DDX_Control(pDX, IDC_PROGRESS2, m_progress[1]);
	DDX_Control(pDX, IDC_PROGRESS3, m_progress[2]);
	DDX_Control(pDX, IDC_PROGRESS5, m_progress[3]);
	DDX_Control(pDX, IDC_PROGRESS6, m_progress[4]);
	DDX_Control(pDX, IDC_PROGRESS7, m_progress[5]);
	
	DDX_Control(pDX, IDC_STATIC1,staticStr[0]);
	DDX_Control(pDX, IDC_STATIC2, staticStr[1]);
	DDX_Control(pDX, IDC_STATIC3, staticStr[2]);
	DDX_Control(pDX, IDC_STATIC4, staticStr[3]);
	DDX_Control(pDX, IDC_STATIC5, staticStr[4]);
	DDX_Control(pDX, IDC_STATIC6, staticStr[5]);
	
	DDX_Control(pDX, IDC_EDIT1, editText);
	DDX_Control(pDX, IDC_EDIT2, editText2);
}

BEGIN_MESSAGE_MAP(CCsv_TestDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND_RANGE(IDC_BUTTON1,IDC_BUTTON6, &CCsv_TestDlg::OnBnClicked)
	ON_STN_CLICKED(IDC_STATIC4, &CCsv_TestDlg::OnStnClickedStatic4)
END_MESSAGE_MAP()


// CCsv_TestDlg 메시지 처리기

BOOL CCsv_TestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	threadCount = 0;

	for(int i=0; i<6;i++){
	m_progress[i].SetRange(0, progressNum);
    m_progress[i].SetPos(0);
	
	}
	
	
    return TRUE;




	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CCsv_TestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CCsv_TestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CCsv_TestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

typedef struct            //스레드 파라미터 구조체
{ 
	int index;
	CWnd *pWnd;
	CString text;
	
} TestT; 


UINT WorkerThread(LPVOID pParam)
{
	TestT *test = (TestT *)pParam; 
	int index = test->index;
	CCsv_TestDlg *pTestDlg = (CCsv_TestDlg*)test->pWnd;
	CString myText= test->text;
	
		
	
	if(pTestDlg->threadCount>=threadNum)								//임계영역 꽉차있으면
	{
		pTestDlg->queue.push(myText);		
			pTestDlg->editStr2.Append(pTestDlg->queue.front() +_T("\t"));
			pTestDlg->queue.pop();
			pTestDlg->editText2.SetWindowTextW(pTestDlg->editStr2);
		



	}

    g_sem.Lock();
	pTestDlg->threadCount++;									 //임계영역 스레드 +1

	pTestDlg->editStr.Append(myText+_T("\t"));
	pTestDlg->editText.SetWindowTextW(pTestDlg->editStr);
	
	for(int i=0;i<5;i++){
		//프로그레스바 동작
		for(int i=0;i<=progressNum;i++)
		{	
			CString percent;
			pTestDlg->m_progress[index].SetPos(i);
			
			int j=(int)i/2;
			//퍼센티지 출력
			percent.Format(_T("%d"),j);
			pTestDlg->staticStr[index].SetWindowTextW(percent+_T("%"));
			



			::Sleep(10);
		}
	}
	g_sem.Unlock();					 //임계영역 스레드 -1
	
	pTestDlg->threadCount--;
	//대기열 최신화
	pTestDlg->editStr2=pTestDlg->editStr2.Mid(4,pTestDlg->editStr2.GetLength());
	pTestDlg->editText2.SetWindowTextW(pTestDlg->editStr2);
	
	return 0;
}
 



void CCsv_TestDlg::OnBnClicked(UINT nID)
{
	TestT *test = new TestT;
	test->pWnd = this;

	switch(nID)
	{
		case IDC_BUTTON1:
			test-> index = 0;
			test->text = _T("T-1");
			break;
		
		case IDC_BUTTON2:
			test-> index = 1;
			test->text = _T("T-2");
			break;

		case IDC_BUTTON3:
			test-> index = 2;
			test->text = _T("T-3");
			break;

		case IDC_BUTTON4:
			test-> index = 3;
			test->text = _T("T-4");
			break;
			
		case IDC_BUTTON5:
			test-> index = 4;
			test->text = _T("T-5");
			break;

		case IDC_BUTTON6:
			test-> index = 5;
			test->text = _T("T-6");
			break;
	}



	AfxBeginThread(WorkerThread, (LPVOID)test);
	
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}



	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.


void CCsv_TestDlg::OnStnClickedStatic4()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
