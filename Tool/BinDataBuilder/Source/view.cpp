// ItemFactoryView.cpp : CItemFactoryView ���ʵ��
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
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CItemFactoryView ����/����

CItemFactoryView::CItemFactoryView()
{
	// TODO: �ڴ˴���ӹ������

}

CItemFactoryView::~CItemFactoryView()
{
}

BOOL CItemFactoryView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸� CREATESTRUCT cs ���޸Ĵ������
	// ��ʽ

	return CView::PreCreateWindow(cs);
}

// CItemFactoryView ����

void CItemFactoryView::OnDraw(CDC* /*pDC*/)
{
	CItemFactoryDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CItemFactoryView ��ӡ

BOOL CItemFactoryView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CItemFactoryView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��ӡǰ��Ӷ���ĳ�ʼ��
}

void CItemFactoryView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��ӡ������������
}


// CItemFactoryView ���

#ifdef _DEBUG
void CItemFactoryView::AssertValid() const
{
	CView::AssertValid();
}

void CItemFactoryView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CItemFactoryDoc* CItemFactoryView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CItemFactoryDoc)));
	return (CItemFactoryDoc*)m_pDocument;
}
#endif //_DEBUG


// CItemFactoryView ��Ϣ�������
