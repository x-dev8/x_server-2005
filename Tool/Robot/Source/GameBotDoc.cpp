// GameBotDoc.cpp : CGameBotDoc ���ʵ��
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


// CGameBotDoc ����/����

CGameBotDoc::CGameBotDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CGameBotDoc::~CGameBotDoc()
{
}

BOOL CGameBotDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CGameBotDoc ���л�

void CGameBotDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}


// CGameBotDoc ���

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


// CGameBotDoc ����
