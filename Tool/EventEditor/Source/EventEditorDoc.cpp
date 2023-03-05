// EditorDoc.cpp : implementation of the CEditorDoc class
//

#include "stdafx.h"
#include "EventEditor.h"

#include "EventEditorDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEditorDoc

IMPLEMENT_DYNCREATE(CEditorDoc, CDocument)

BEGIN_MESSAGE_MAP(CEditorDoc, CDocument)
END_MESSAGE_MAP()


// CEditorDoc construction/destruction

CEditorDoc::CEditorDoc()
{
	// TODO: add one-time construction code here

}

CEditorDoc::~CEditorDoc()
{
}

BOOL CEditorDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CEditorDoc serialization

void CEditorDoc::Serialize(CArchive& ar)
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


// CEditorDoc diagnostics

#ifdef _DEBUG
void CEditorDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEditorDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CEditorDoc commands
