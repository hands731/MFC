// MainDialog.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "threadTxt.h"
#include "MainDialog.h"
#include "afxdialogex.h"


// MainDialog ��ȭ �����Դϴ�.

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


// MainDialog �޽��� ó�����Դϴ�.
