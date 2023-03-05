#pragma once

#ifndef __AFXWIN_H__
	#error "对 PCH 包含此档案前先包含 'stdafx.h'"
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