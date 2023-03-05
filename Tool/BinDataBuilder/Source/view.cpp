// ItemFactoryView.cpp : CItemFactoryView 类的实现
//

#include "stdafx.h"
#include "BinDataBuilder.h"

#include "doc.h"
#include "view.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CItemFactoryView

IMPLEMENT_DYNCREATE(CItemFactoryView, CView)

BEGIN_MESSAGE_MAP(CItemFactoryView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CItemFactoryView 构造/销毁

CItemFactoryView::CItemFactoryView()
{
	// TODO: 在此处添加构造代码

}

CItemFactoryView::~CItemFactoryView()
{
}

BOOL CItemFactoryView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改 CREATESTRUCT cs 来修改窗口类或
	// 样式

	return CView::PreCreateWindow(cs);
}

// CItemFactoryView 绘制

void CItemFactoryView::OnDraw(CDC* /*pDC*/)
{
	CItemFactoryDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: 在此处为本机数据添加绘制代码
}


// CItemFactoryView 打印

BOOL CItemFactoryView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CItemFactoryView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 打印前添加额外的初始化
}

void CItemFactoryView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 打印后添加清除过程
}


// CItemFactoryView 诊断

#ifdef _DEBUG
void CItemFactoryView::AssertValid() const
{
	CView::AssertValid();
}

void CItemFactoryView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CItemFactoryDoc* CItemFactoryView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CItemFactoryDoc)));
	return (CItemFactoryDoc*)m_pDocument;
}
#endif //_DEBUG


// CItemFactoryView 消息处理程序
