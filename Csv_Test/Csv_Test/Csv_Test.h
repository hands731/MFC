
// Csv_Test.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CCsv_TestApp:
// �� Ŭ������ ������ ���ؼ��� Csv_Test.cpp�� �����Ͻʽÿ�.
//

class CCsv_TestApp : public CWinApp
{
public:
	CCsv_TestApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CCsv_TestApp theApp;