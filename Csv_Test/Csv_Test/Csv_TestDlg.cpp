
// Csv_TestDlg.cpp : ���� ����
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
#define threadNum 4					//������ �ִ��� ����
#define	progressNum 200
CSemaphore g_sem(threadNum	, threadNum);
CCriticalSection g_cs;

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


// CCsv_TestDlg ��ȭ ����




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


// CCsv_TestDlg �޽��� ó����

BOOL CCsv_TestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

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
	threadCount = 0;

	for(int i=0; i<6;i++){
	m_progress[i].SetRange(0, progressNum);
    m_progress[i].SetPos(0);
	
	}
	
	
    return TRUE;




	// �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
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

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CCsv_TestDlg::OnPaint()
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
		CDialog::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CCsv_TestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

typedef struct            //������ �Ķ���� ����ü
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
	
		
	
	if(pTestDlg->threadCount>=threadNum)								//�Ӱ迵�� ����������
	{
		pTestDlg->queue.push(myText);		
			pTestDlg->editStr2.Append(pTestDlg->queue.front() +_T("\t"));
			pTestDlg->queue.pop();
			pTestDlg->editText2.SetWindowTextW(pTestDlg->editStr2);
		



	}

    g_sem.Lock();
	pTestDlg->threadCount++;									 //�Ӱ迵�� ������ +1

	pTestDlg->editStr.Append(myText+_T("\t"));
	pTestDlg->editText.SetWindowTextW(pTestDlg->editStr);
	
	for(int i=0;i<5;i++){
		//���α׷����� ����
		for(int i=0;i<=progressNum;i++)
		{	
			CString percent;
			pTestDlg->m_progress[index].SetPos(i);
			
			int j=(int)i/2;
			//�ۼ�Ƽ�� ���
			percent.Format(_T("%d"),j);
			pTestDlg->staticStr[index].SetWindowTextW(percent+_T("%"));
			



			::Sleep(10);
		}
	}
	g_sem.Unlock();					 //�Ӱ迵�� ������ -1
	
	pTestDlg->threadCount--;
	//��⿭ �ֽ�ȭ
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
	
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}



	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.


void CCsv_TestDlg::OnStnClickedStatic4()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}
