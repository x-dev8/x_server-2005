// BinDataBuilder.h: BinDataBuilder Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "../Resource/Resource.h"       // ������


// BinDataBuilder:
// �йش����ʵ�֣������ ItemFactory.cpp
//

class CBinDataBuilderApp : public CWinApp
{
public:
	CBinDataBuilderApp();

    void ShowVersionInformation();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
};

extern CBinDataBuilderApp theApp;
