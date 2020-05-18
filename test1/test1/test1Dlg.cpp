
// test1Dlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "test1.h"
#include "test1Dlg.h"
#include "afxdialogex.h"
#include <sstream>

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


// Ctest1Dlg 대화 상자




Ctest1Dlg::Ctest1Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(Ctest1Dlg::IDD, pParent)
	
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Ctest1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, List1);
	DDX_Control(pDX, IDC_LIST2, List2);
	DDX_Control(pDX, IDC_BUTTON1, insertButton);
	DDX_Control(pDX, IDC_BUTTON2, rightButton);
	DDX_Control(pDX, IDC_BUTTON3, leftButton);
	DDX_Control(pDX, IDC_BUTTON4, delButton);
	DDX_Control(pDX, IDC_EDIT1, insertEdit);
	DDX_Control(pDX, IDC_BUTTON5, txtLoadButton);
	DDX_Control(pDX, IDC_BUTTON6, txtSaveButton);
}

BEGIN_MESSAGE_MAP(Ctest1Dlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &Ctest1Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &Ctest1Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &Ctest1Dlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &Ctest1Dlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &Ctest1Dlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &Ctest1Dlg::OnBnClickedButton6)

END_MESSAGE_MAP()


// Ctest1Dlg 메시지 처리기

BOOL Ctest1Dlg::OnInitDialog()
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
	list1Count = 0;
	list2Count = 0;
	insertButton.SetWindowTextW(_T("insert"));
	delButton.SetWindowTextW(_T("select DEL"));
	rightButton.SetWindowTextW(_T(">>"));
	leftButton.SetWindowTextW(_T("<<"));

	
	
	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void Ctest1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void Ctest1Dlg::OnPaint()
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
HCURSOR Ctest1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void Ctest1Dlg::OnBnClickedButton1()     //Insert
{

	list1Count = List1.GetItemCount();
	insertEdit.GetWindowTextW(editString);
	if(!editString.IsEmpty())
	{	
		List1.InsertItem(list1Count,editString);
	}
		list1Count++;
	insertEdit.SetWindowTextW(_T(""));
}


void Ctest1Dlg::OnBnClickedButton2()   //LIST1 >> LIST2  향상된 로직
{
	int nCount = List1.GetSelectedCount();
	for(int i = nCount ; i>0  ; --i)
	{
		int nItem = List1.GetNextItem(-1,LVNI_SELECTED);
		myStr=List1.GetItemText(nItem,0);  
		list2Count = List2.GetItemCount();
		List2.InsertItem(list2Count,myStr);
		List1.DeleteItem(nItem);
	}
}


void Ctest1Dlg::OnBnClickedButton3()   //LIST1 << LIST2
{
	int nCount = List2.GetSelectedCount();
	for(int i = nCount ;i>=0 ; --i)
	{
		int nItem = List2.GetNextItem(-1,LVNI_SELECTED);
		myStr=List2.GetItemText(nItem,0);
		list1Count = List1.GetItemCount();
		List1.InsertItem(list1Count,myStr);
		List2.DeleteItem(nItem);
	}
	List1.DeleteItem(list1Count);
}


void Ctest1Dlg::OnBnClickedButton4()       //LIST 1 Del
{
	int nCount = List1.GetSelectedCount();
	for(int i = nCount;i>=0;--i)
	{
		POSITION pos = List1.GetFirstSelectedItemPosition();
		int nItem = List1.GetNextSelectedItem(pos);

		List1.DeleteItem(nItem);
	}

}


void Ctest1Dlg::OnBnClickedButton5()     //txt Read
{
	CStdioFile sFile;
	CString readStr = _T("");
	CString strLine = _T("");
	CString fileName = _T("List1.txt");
	setlocale(LC_ALL,"");

	if (sFile.Open(fileName, CFile::modeRead))
	{
		 UINT nBytes = sFile.GetLength();

		if (nBytes >= 0)
		{
			while (sFile.ReadString(strLine))
			{
				//readStr += strLine;
				list1Count = List1.GetItemCount();
				List1.InsertItem(list1Count,strLine);
			}
		}
		sFile.Close();
	} 
	
}


void Ctest1Dlg::OnBnClickedButton6()    //txt Write
{
	CStdioFile sFile;
	CString fileName = _T("List1.txt");
	CString writeStr = _T("");
	setlocale(LC_ALL,"");

	

	if (sFile.Open(fileName, CStdioFile::modeCreate | CStdioFile::modeWrite))
	{
		for (int i=0; i < List1.GetItemCount();i++) 
		{
		writeStr = List1.GetItemText(i,0);
		sFile.WriteString(writeStr+"\n");
		}

	}
	sFile.Close();
}

