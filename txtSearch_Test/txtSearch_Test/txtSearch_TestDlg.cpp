
// txtSearch_TestDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "txtSearch_Test.h"
#include "txtSearch_TestDlg.h"
#include "afxdialogex.h"
#include <sstream>
#include <cstring>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// CtxtSearch_TestDlg 대화 상자




CtxtSearch_TestDlg::CtxtSearch_TestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CtxtSearch_TestDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CtxtSearch_TestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, edit1);
}

BEGIN_MESSAGE_MAP(CtxtSearch_TestDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CtxtSearch_TestDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CtxtSearch_TestDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CtxtSearch_TestDlg 메시지 처리기

BOOL CtxtSearch_TestDlg::OnInitDialog()
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

	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CtxtSearch_TestDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CtxtSearch_TestDlg::OnPaint()
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
HCURSOR CtxtSearch_TestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CtxtSearch_TestDlg::OnBnClickedButton1()       //.txt Create
{
	CStdioFile sFile;
	CString filePath = _T("d:\\Work\\txtSearch_Test\\searchTest.txt");
	CString writeStr = _T("");
	CString str = _T("");
	setlocale(LC_ALL,"");
			
	int count = 175200;
	BOOL isSame = FALSE;						//중복여부 판별 중복:T
	//int nRand=0;

	if (sFile.Open(filePath, CStdioFile::modeCreate | CStdioFile::modeWrite)) 
	{ 
		/*
		while(count<999)                         //txt.write
		{
				nRand = (rand()%999+1);          //난수발생

				if(count>=1)
				{					 
					for(int j =0;j<count;j++)	  //중복검사
					{
						if(nRand == RandomArr[j])
						{
							isSame = TRUE;
							break;
						}
					}
				}
				if(isSame==FALSE)					//중복안되면 값주입
				{									//형식 : ABCDXXX
					for(int j =0;j<count;j++)	  //중복검사
					{
						str.Format(_T("ABCD%05d\n"),j);
						sFile.WriteString(str);
					}	
				}
					isSame = FALSE;
			}
		*/
			for(int i =0;i<count;i++)	  
			{
				str.Format(_T("ABCD%05d\n"),i);
				sFile.WriteString(str);
			}
			sFile.Close();
			AfxMessageBox(_T(".txt생성 완료"));
	}
}


void CtxtSearch_TestDlg::OnBnClickedButton2()         //.txt Search
{
	
	CStdioFile sFile;
	CString fileName = _T("d:\\Work\\txtSearch_Test\\searchTest.txt");
	setlocale(LC_ALL,"");
	CString strLine;

	CString editStr;
	edit1.GetWindowTextW(editStr);

	boolean isFlag = false;		       //일치하는 값이 있으면 T, 없으면 F

	TCHAR szBuff[20]={0,};


		if (sFile.Open(fileName, CFile::modeRead))      //.txt 읽기
		{
			while (sFile.ReadString(strLine))
			{
				_sntprintf_s(szBuff, 20, 20-1, strLine);

				if(0==_tcscmp(szBuff, editStr))
				{
					isFlag = true;
					AfxMessageBox(_T("일치하는 값 O"));
					break;
				}

			}
			sFile.Close();
		} 

		if(isFlag == false)                                //일치하는 값이 없을경우
		{
			AfxMessageBox(_T("일치하는 값 X"));
		
		}
	
	

	
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
