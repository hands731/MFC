
// Ini_TestDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "Ini_Test.h"
#include "Ini_TestDlg.h"
#include "afxdialogex.h"

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


// CIni_TestDlg 대화 상자




CIni_TestDlg::CIni_TestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CIni_TestDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CIni_TestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, editNum);
	DDX_Control(pDX, IDC_EDIT7, editGA);
	DDX_Control(pDX, IDC_EDIT2, editNA);
	DDX_Control(pDX, IDC_EDIT3, editDA);
	DDX_Control(pDX, IDC_EDIT4, editName);
	DDX_Control(pDX, IDC_EDIT5, editA);
	DDX_Control(pDX, IDC_EDIT6, editB);
	DDX_Control(pDX, IDC_STATIC1, static1);
	DDX_Control(pDX, IDC_CHECK2, check2);
	DDX_Control(pDX, IDC_CHECK10, chek10);
}

BEGIN_MESSAGE_MAP(CIni_TestDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CIni_TestDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CIni_TestDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_CHECK8, &CIni_TestDlg::OnBnClickedCheck8)
END_MESSAGE_MAP()


// CIni_TestDlg 메시지 처리기

BOOL CIni_TestDlg::OnInitDialog()
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
	check2.SetCheck(1);
	chek10.SetCheck(1);
	




	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CIni_TestDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CIni_TestDlg::OnPaint()
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
HCURSOR CIni_TestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CIni_TestDlg::OnBnClickedButton1()     //.ini Write
{
	CString filePath = _T("d:\\Work\\Ini_Test\\iniTest.ini");
	editNum.GetWindowTextW(num);
	editGA.GetWindowTextW(GA);
	editNA.GetWindowTextW(NA);
	editDA.GetWindowTextW(DA);
	editName.GetWindowTextW(name);
	editA.GetWindowTextW(A);
	editB.GetWindowTextW(B);

											//[STRING] write
	if(!isdigit(num.GetAt(0))&&!isdigit(GA.GetAt(0))&&!isdigit(NA.GetAt(0))&&!isdigit(DA.GetAt(0)))				
											// ㄴ[STRING]에는 String만 입력가능
	{ 
		WritePrivateProfileString(_T("STRING"), _T("name"), num, filePath );
		WritePrivateProfileString(_T("STRING"), _T("가"), GA, filePath );
		WritePrivateProfileString(_T("STRING"), _T("나"), NA, filePath );
		WritePrivateProfileString(_T("STRING"), _T("다"), DA, filePath );

	}
	else
	{
		AfxMessageBox(_T("[STRING]에는 String형만 입력가능"));	
	}

	if(isdigit(name.GetAt(0))&&isdigit(A.GetAt(0))&&isdigit(B.GetAt(0)))			
											//ㄴ[INT]에는 Int만 입력가능
	{
		WritePrivateProfileString(_T("INT"), _T("Num"), name, filePath );
		WritePrivateProfileString(_T("INT"), _T("A"), A, filePath );
		WritePrivateProfileString(_T("INT"), _T("B"), B, filePath );
		
	}
	else
	{
		AfxMessageBox(_T("[INT]에는 Int형만 입력가능"));	
		editName.SetWindowTextW(_T(""));
		editA.SetWindowTextW(_T(""));
		editB.SetWindowTextW(_T(""));
	}

	editNum.SetWindowTextW(_T(""));
	editGA.SetWindowTextW(_T(""));
	editNA.SetWindowTextW(_T(""));
	editDA.SetWindowTextW(_T(""));
	editA.SetWindowTextW(_T(""));
	editB.SetWindowTextW(_T(""));

}


void CIni_TestDlg::OnBnClickedButton2()      //.ini Read
{
	CString filePath = _T("d:\\Work\\Ini_Test\\iniTest.ini");
	TCHAR GA_Value[255];
	TCHAR NA_Value[255];
	TCHAR DA_Value[255];
	TCHAR name_Value[255];
	int A_Int, B_Int;
	CString myString;
	
											//[STRING] value추출

	if(IsDlgButtonChecked(IDC_CHECK2))		//name
	{
		GetPrivateProfileString( _T("STRING"), _T("name"), _T("NONE"), name_Value,255,filePath);
		myString.Append(_T("[STRING]\nname = ")+CString(name_Value)+_T("\t"));
	}
	if(IsDlgButtonChecked(IDC_CHECK3))		//가
	{
		GetPrivateProfileString( _T("STRING"), _T("가"), _T("NONE"), GA_Value, 255,filePath);	
		myString.Append(_T("가 = ")+CString(GA_Value)+_T("\t"));
		
	}
	if(IsDlgButtonChecked(IDC_CHECK4))		//나
	{
		GetPrivateProfileString( _T("STRING"), _T("나"), _T("NONE"), NA_Value, 255,filePath);	
		myString.Append(_T("나 = ")+CString(NA_Value)+_T("\t"));
		
	}
	if(IsDlgButtonChecked(IDC_CHECK5))		//다
	{
		GetPrivateProfileString( _T("STRING"), _T("다"), _T("NONE"), DA_Value, 255,filePath);	
		myString.Append(_T("다 = ")+CString(DA_Value));
		
	}
											//[INT] value추출

	if(IsDlgButtonChecked(IDC_CHECK10))    //Num
	{
		numInt = GetPrivateProfileInt( _T("INT"), _T("Num"), 0, filePath);	
		num.Format(_T("%d"),numInt);
		myString.Append(_T("\n\n[INT]\nNum = ")+CString(num)+_T("\t"));
		
	}
	if(IsDlgButtonChecked(IDC_CHECK9))		//A		
	{
		A_Int = GetPrivateProfileInt( _T("INT"), _T("A"), 0, filePath );
		A.Format(_T("%d"),A_Int);
		myString.Append(_T("A = ")+A+_T("   \t"));
	}
	if(IsDlgButtonChecked(IDC_CHECK8))		//B
	{
		B_Int = GetPrivateProfileInt( _T("INT"), _T("B"), 0, filePath );
		B.Format(_T("%d"),B_Int);
		myString.Append(_T("B = ")+B+_T("\t"));
	}
	static1.SetWindowTextW(myString);
}


void CIni_TestDlg::OnBnClickedCheck8()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
