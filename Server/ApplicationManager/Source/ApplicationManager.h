#pragma once

#ifndef __AFXWIN_H__
	#error "�� PCH �����˵���ǰ�Ȱ��� 'stdafx.h'"
#endif

#include "../Resource/Resource.h"

class CProtectorApplication : public CWinApp
{
public:
	CProtectorApplication();


public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};

extern CProtectorApplication theApp;