
// txtSearch_Test.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CtxtSearch_TestApp:
// �� Ŭ������ ������ ���ؼ��� txtSearch_Test.cpp�� �����Ͻʽÿ�.
//

class CtxtSearch_TestApp : public CWinApp
{
public:
	CtxtSearch_TestApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CtxtSearch_TestApp theApp;