
// Ini_TestDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "Ini_Test.h"
#include "Ini_TestDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// CIni_TestDlg ��ȭ ����




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


// CIni_TestDlg �޽��� ó����

BOOL CIni_TestDlg::OnInitDialog()
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
	check2.SetCheck(1);
	chek10.SetCheck(1);
	




	// �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
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

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CIni_TestDlg::OnPaint()
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
											// ��[STRING]���� String�� �Է°���
	{ 
		WritePrivateProfileString(_T("STRING"), _T("name"), num, filePath );
		WritePrivateProfileString(_T("STRING"), _T("��"), GA, filePath );
		WritePrivateProfileString(_T("STRING"), _T("��"), NA, filePath );
		WritePrivateProfileString(_T("STRING"), _T("��"), DA, filePath );

	}
	else
	{
		AfxMessageBox(_T("[STRING]���� String���� �Է°���"));	
	}

	if(isdigit(name.GetAt(0))&&isdigit(A.GetAt(0))&&isdigit(B.GetAt(0)))			
											//��[INT]���� Int�� �Է°���
	{
		WritePrivateProfileString(_T("INT"), _T("Num"), name, filePath );
		WritePrivateProfileString(_T("INT"), _T("A"), A, filePath );
		WritePrivateProfileString(_T("INT"), _T("B"), B, filePath );
		
	}
	else
	{
		AfxMessageBox(_T("[INT]���� Int���� �Է°���"));	
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
	
											//[STRING] value����

	if(IsDlgButtonChecked(IDC_CHECK2))		//name
	{
		GetPrivateProfileString( _T("STRING"), _T("name"), _T("NONE"), name_Value,255,filePath);
		myString.Append(_T("[STRING]\nname = ")+CString(name_Value)+_T("\t"));
	}
	if(IsDlgButtonChecked(IDC_CHECK3))		//��
	{
		GetPrivateProfileString( _T("STRING"), _T("��"), _T("NONE"), GA_Value, 255,filePath);	
		myString.Append(_T("�� = ")+CString(GA_Value)+_T("\t"));
		
	}
	if(IsDlgButtonChecked(IDC_CHECK4))		//��
	{
		GetPrivateProfileString( _T("STRING"), _T("��"), _T("NONE"), NA_Value, 255,filePath);	
		myString.Append(_T("�� = ")+CString(NA_Value)+_T("\t"));
		
	}
	if(IsDlgButtonChecked(IDC_CHECK5))		//��
	{
		GetPrivateProfileString( _T("STRING"), _T("��"), _T("NONE"), DA_Value, 255,filePath);	
		myString.Append(_T("�� = ")+CString(DA_Value));
		
	}
											//[INT] value����

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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}
