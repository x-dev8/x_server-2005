// ItemFactoryDoc.cpp :  CItemFactoryDoc ���ʵ��
//

#include "stdafx.h"
#include "BinDataBuilder.h"

#include "doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CItemFactoryDoc

IMPLEMENT_DYNCREATE(CItemFactoryDoc, CDocument)

BEGIN_MESSAGE_MAP(CItemFactoryDoc, CDocument)
END_MESSAGE_MAP()


// CItemFactoryDoc ����/����

CItemFactoryDoc::CItemFactoryDoc()
{
	// TODO���ڴ����һ���Թ������

}

CItemFactoryDoc::~CItemFactoryDoc()
{
}

BOOL CItemFactoryDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO���ڴ�������³�ʼ������
	// ��SDI �ĵ������ø��ĵ���

	return TRUE;
}




// CItemFactoryDoc ���л�

void CItemFactoryDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO���ڴ���Ӵ洢����
	}
	else
	{
		// TODO���ڴ���Ӽ��ش���
	}
}


// CItemFactoryDoc ���

#ifdef _DEBUG
void CItemFactoryDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CItemFactoryDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CItemFactoryDoc ����
