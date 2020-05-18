// MainDialog.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "threadTxt.h"
#include "MainDialog.h"
#include "afxdialogex.h"


// MainDialog 대화 상자입니다.

IMPLEMENT_DYNAMIC(MainDialog, CDialog)

MainDialog::MainDialog(CWnd* pParent /*=NULL*/)
	: CDialog(MainDialog::IDD, pParent)
{

}

MainDialog::~MainDialog()
{
}

void MainDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(MainDialog, CDialog)
END_MESSAGE_MAP()


// MainDialog 메시지 처리기입니다.
