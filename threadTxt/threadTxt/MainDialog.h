#pragma once


// MainDialog ��ȭ �����Դϴ�.

class MainDialog : public CDialog
{
	DECLARE_DYNAMIC(MainDialog)

public:
	MainDialog(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~MainDialog();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_MAIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};
