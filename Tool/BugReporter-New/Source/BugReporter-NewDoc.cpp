// BugReporter-NewDoc.cpp : implementation of the CBugReporterNewDoc class
//

#include "stdafx.h"
#include "BugReporter-New.h"

#include "BugReporter-NewDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CBugReporterNewDoc

IMPLEMENT_DYNCREATE(CBugReporterNewDoc, CDocument)

BEGIN_MESSAGE_MAP(CBugReporterNewDoc, CDocument)
END_MESSAGE_MAP()


// CBugReporterNewDoc construction/destruction

CBugReporterNewDoc::CBugReporterNewDoc()
{
	// TODO: add one-time construction code here

}

CBugReporterNewDoc::~CBugReporterNewDoc()
{
}

BOOL CBugReporterNewDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CBugReporterNewDoc serialization

void CBugReporterNewDoc::Serialize(CArchive& ar)
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


// CBugReporterNewDoc diagnostics

#ifdef _DEBUG
void CBugReporterNewDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CBugReporterNewDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CBugReporterNewDoc commands