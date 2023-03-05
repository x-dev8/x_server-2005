// EditorDoc.cpp : implementation of the CQuestEditorDoc class
//

#include "stdafx.h"
#include "QuestEditor.h"

#include "QuestEditorDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CQuestEditorDoc

IMPLEMENT_DYNCREATE(CQuestEditorDoc, CDocument)

BEGIN_MESSAGE_MAP(CQuestEditorDoc, CDocument)
END_MESSAGE_MAP()


// CQuestEditorDoc construction/destruction

CQuestEditorDoc::CQuestEditorDoc()
{
	// TODO: add one-time construction code here

}

CQuestEditorDoc::~CQuestEditorDoc()
{
}

BOOL CQuestEditorDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CQuestEditorDoc serialization

void CQuestEditorDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}


// CQuestEditorDoc diagnostics

#ifdef _DEBUG
void CQuestEditorDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CQuestEditorDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CQuestEditorDoc commands
