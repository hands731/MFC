
// threadTxtDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "threadTxt.h"
#include "threadTxtDlg.h"
#include "afxdialogex.h"
#include <sstream>
#include <iostream>
#include <boost/thread/mutex.hpp>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#define threadNum 5
#define semNum 3
CCriticalSection g_csBuffer;		
CSemaphore g_sem(semNum		, semNum);      
CCriticalSection g_csUPDOWN[threadNum];			//두종류 스레드 상호배제
CCriticalSection g_csUP[threadNum];
CCriticalSection g_csDOWN[threadNum];
boost::mutex  mutex;
bool g_bufferFlag[5]={false,};
int g_bufferCount[5]={0,};
int g_UpCount[5] = {0,};


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




CthreadTxtDlg::CthreadTxtDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CthreadTxtDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CthreadTxtDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS1, m_progressbar[0]);
	DDX_Control(pDX, IDC_PROGRESS2, m_progressbar[1]);
	DDX_Control(pDX, IDC_PROGRESS3, m_progressbar[2]);
	DDX_Control(pDX, IDC_PROGRESS4, m_progressbar[3]);
	DDX_Control(pDX, IDC_PROGRESS5, m_progressbar[4]);

	DDX_Control(pDX, IDC_STATIC1, static1);
	DDX_Control(pDX, IDC_STATIC22, m_static22);

	DDX_Control(pDX, IDC_STATIC5, ctr_Static[0]);
	DDX_Control(pDX, IDC_STATIC6, ctr_Static[1]);
	DDX_Control(pDX, IDC_STATIC7, ctr_Static[2]);
	DDX_Control(pDX, IDC_STATIC8, ctr_Static[3]);
	DDX_Control(pDX, IDC_STATIC9, ctr_Static[4]);

	DDX_Control(pDX, IDC_BUTTON3, m_btn[0]);
	DDX_Control(pDX, IDC_BUTTON1, m_btn[1]);
	DDX_Control(pDX, IDC_BUTTON4, m_btn[2]);
}

BEGIN_MESSAGE_MAP(CthreadTxtDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CthreadTxtDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &CthreadTxtDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CthreadTxtDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON2, &CthreadTxtDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CthreadTxtDlg 메시지 처리기

BOOL CthreadTxtDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

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

	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	for(int i=0;i<threadNum;i++)
	{
	int_progressRange[i]=300;
	m_progressbar[i].SetRange(0, int_progressRange[i]);
	m_progressbar[i].SetPos(0);
	}


	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CthreadTxtDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CthreadTxtDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CthreadTxtDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

typedef struct            //파라미터 구조체
{ 
	int num;
	CWnd *pWnd;
	int For_count;
	int range;
	int version;
} Parameter; 


UINT Bottom_Up(LPVOID pParam){
	
	
	
	CString name = _T("");
	Parameter *pP = (Parameter *)pParam; 
	int num = pP->num;
	CthreadTxtDlg *pDlg = (CthreadTxtDlg*)pP->pWnd;
	int countc=0;

	
	while(true)
	{
	Sleep(rand()%100);
		if(g_bufferFlag[num]==false&&g_UpCount[num]==0)
		{
			g_UpCount[num]++;
			break;
		}
	}
	name.Format(_T("%d"),num);
	
	if(pP->version == 1)
	{
		g_csBuffer.Lock();
	}
	else if(pP->version==2)
	{
		g_sem.Lock();
	}
	else if(pP->version==3){
	
		mutex.lock();
	}
	
	for(int i=0;i<pP->range+1;i++)
	{	
		pDlg->m_progressbar[pP->num].SetPos(i);
		::Sleep(3);
	}
	
	g_bufferCount[num]++;

	CString strStatic2=_T("");
	CString strCount = _T("");
	
	strCount.Format(_T("%d"),g_bufferCount[num]);
	strStatic2.Append(strCount+_T("\t"));	

	pDlg->ctr_Static[num].SetWindowTextW(strStatic2);

	if(pP->version == 1)
	{
		g_csBuffer.Unlock();

	}
	else if(pP->version == 2)
	{	
		g_sem.Unlock();
	}
	else if(pP->version == 3){
		mutex.unlock();
	}

	g_bufferFlag[num] = true;
	return 0;
}


UINT Top_Down(LPVOID pParam){
	
	
	CString name = _T("");
	Parameter *pP = (Parameter *)pParam; 
	int num = pP->num;
	CthreadTxtDlg *pDlg = (CthreadTxtDlg*)pP->pWnd;

	while(true)
	{
		Sleep(rand()%100);
		
		if(g_bufferFlag[num]==true&&g_UpCount[num]==1)
		{
			g_UpCount[num]--;
			break;
		}
	}
	//Lock()
	if(pP->version == 1)
	{
		g_csBuffer.Lock();
	}
	else if(pP->version==2)
	{
		g_sem.Lock();
	}
	else if(pP->version==3){
		mutex.lock();

	}
	//Task
	for(int i=pP->range;i>0;i--)
		{	

			pDlg->m_progressbar[pP->num].SetPos(i);
			::Sleep(3);
		}

	
	int buttonCount=0;
	//Button enable TRUE
	for(int i=0;i<threadNum;i++)
	{
		if(g_bufferCount[i]==pP->For_count)
		{
			buttonCount++;
		}
	}
	
	if(buttonCount == 5)
	{
	
		for(int i=0;i<3;i++)
		{
			pDlg->m_btn[i].EnableWindow(TRUE);
		}
		pDlg->Invalidate();
	}else
	{
		CString btnStr;
		btnStr.Format(_T("%d"), buttonCount);
	}

	//UnLock
	if(pP->version == 1)
	{
		g_csBuffer.Unlock();
	}else if(pP->version == 2)
	{	

		g_sem.Unlock();

	}else if(pP->version == 3){
	
		mutex.unlock();
	}

	g_bufferFlag[num]=false;
	
	return 0;
}

void CthreadTxtDlg::OnBnClickedButton1()			//Semaphore
{
	for(int i=0;i<5;i++)
	{
		ctr_Static[i].SetWindowTextW(_T("0"));
		g_bufferCount[i]=0;
	}
	
	for(int i=0;i<3;i++)
	{
	m_btn[i].EnableWindow(FALSE);
	}
	Invalidate();	
	int count = 3;
	for(int j=0; j<count;j++){
		for(int i=0;i<threadNum;i++)
		{
			Parameter *Pp = new Parameter;
			Pp->pWnd = this;
			Pp->num = i;
			Pp->version = 2;
			Pp->For_count=count;
			Pp->range = int_progressRange[i];
		
			AfxBeginThread(Bottom_Up, (LPVOID)Pp);
			AfxBeginThread(Top_Down ,(LPVOID)Pp);	
		}
		
	}


}      

void CthreadTxtDlg::OnBnClickedButton3()//CriticalSection
{
	
	for(int i=0;i<5;i++)
	{
		ctr_Static[i].SetWindowTextW(_T("0"));
		g_bufferCount[i]=0;
	}

	for(int i=0;i<3;i++)
	{
	m_btn[i].EnableWindow(FALSE);
	}
	Invalidate();	

	int count=2;
	for(int j=0; j<count;j++){
		
		for(int i=0;i<threadNum;i++)
		{
			Parameter *Pp = new Parameter;
			Pp->pWnd = this;
			Pp->num = i;
			Pp->version = 1;
			Pp->For_count = count;
			Pp->range = int_progressRange[i];
			
			AfxBeginThread(Bottom_Up, (LPVOID)Pp);
			AfxBeginThread(Top_Down ,(LPVOID)Pp);	
		}
		
	}

	
}


void CthreadTxtDlg::OnBnClickedButton4()//mutex
{
	for(int i=0;i<5;i++)
	{
		ctr_Static[i].SetWindowTextW(_T("0"));
		g_bufferCount[i]=0;
	}

	for(int i=0;i<3;i++)
	{
		m_btn[i].EnableWindow(FALSE);
	}
	Invalidate();	
	

	int count = 2;
	for(int j=0; j<count;j++){
		for(int i=0;i<threadNum;i++)
		{
			
			Parameter *Pp = new Parameter;
			Pp->pWnd = this;
			Pp->num = i;
			Pp->version = 3;
			Pp->range = int_progressRange[i];
			Pp->For_count=count;
			AfxBeginThread(Bottom_Up, (LPVOID)Pp);
			AfxBeginThread(Top_Down ,(LPVOID)Pp);	
			
			
		}
		
	}

}


void CthreadTxtDlg::OnBnClickedButton2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	OnInitDialog();

}
