
// threadTxt.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CthreadTxtApp:
// �� Ŭ������ ������ ���ؼ��� threadTxt.cpp�� �����Ͻʽÿ�.
//

class CthreadTxtApp : public CWinApp
{
public:
	CthreadTxtApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CthreadTxtApp theApp;