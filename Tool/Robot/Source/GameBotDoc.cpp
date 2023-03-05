// GameBotDoc.cpp : CGameBotDoc 类的实现
//
#include "stdafx.h"
#include "GameBot.h"

#include "GameBotDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#pragma warning(disable:4201)

// CGameBotDoc

IMPLEMENT_DYNCREATE(CGameBotDoc, CDocument)

BEGIN_MESSAGE_MAP(CGameBotDoc, CDocument)
END_MESSAGE_MAP()


// CGameBotDoc 构造/析构

CGameBotDoc::CGameBotDoc()
{
	// TODO: 在此添加一次性构造代码

}

CGameBotDoc::~CGameBotDoc()
{
}

BOOL CGameBotDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CGameBotDoc 序列化

void CGameBotDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}


// CGameBotDoc 诊断

#ifdef _DEBUG
void CGameBotDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CGameBotDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CGameBotDoc 命令
