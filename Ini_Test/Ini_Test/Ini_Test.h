
// Ini_Test.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CIni_TestApp:
// �� Ŭ������ ������ ���ؼ��� Ini_Test.cpp�� �����Ͻʽÿ�.
//

class CIni_TestApp : public CWinApp
{
public:
	CIni_TestApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CIni_TestApp theApp;