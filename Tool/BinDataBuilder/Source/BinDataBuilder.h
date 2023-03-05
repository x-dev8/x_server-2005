// BinDataBuilder.h: BinDataBuilder 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "../Resource/Resource.h"       // 主符号


// BinDataBuilder:
// 有关此类的实现，请参阅 ItemFactory.cpp
//

class CBinDataBuilderApp : public CWinApp
{
public:
	CBinDataBuilderApp();

    void ShowVersionInformation();

// 重写
public:
	virtual BOOL InitInstance();

// 实现
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
};

extern CBinDataBuilderApp theApp;
