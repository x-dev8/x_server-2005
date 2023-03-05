// ItemFactoryDoc.cpp :  CItemFactoryDoc 类的实现
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


// CItemFactoryDoc 构造/销毁

CItemFactoryDoc::CItemFactoryDoc()
{
	// TODO：在此添加一次性构造代码

}

CItemFactoryDoc::~CItemFactoryDoc()
{
}

BOOL CItemFactoryDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO：在此添加重新初始化代码
	// （SDI 文档将重用该文档）

	return TRUE;
}




// CItemFactoryDoc 序列化

void CItemFactoryDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO：在此添加存储代码
	}
	else
	{
		// TODO：在此添加加载代码
	}
}


// CItemFactoryDoc 诊断

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


// CItemFactoryDoc 命令
