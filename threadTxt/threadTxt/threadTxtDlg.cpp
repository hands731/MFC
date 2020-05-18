
// threadTxtDlg.cpp : ���� ����
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
CCriticalSection g_csUPDOWN[threadNum];			//������ ������ ��ȣ����
CCriticalSection g_csUP[threadNum];
CCriticalSection g_csDOWN[threadNum];
boost::mutex  mutex;
bool g_bufferFlag[5]={false,};
int g_bufferCount[5]={0,};
int g_UpCount[5] = {0,};


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
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


// CthreadTxtDlg �޽��� ó����

BOOL CthreadTxtDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
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

	// �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	for(int i=0;i<threadNum;i++)
	{
	int_progressRange[i]=300;
	m_progressbar[i].SetRange(0, int_progressRange[i]);
	m_progressbar[i].SetPos(0);
	}


	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
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

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CthreadTxtDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CthreadTxtDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

typedef struct            //�Ķ���� ����ü
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	OnInitDialog();

}
