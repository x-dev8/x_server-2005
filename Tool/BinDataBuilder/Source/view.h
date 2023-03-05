// ItemFactoryView.h : CItemFactoryView ��Ľӿ�
//


#pragma once


class CItemFactoryView : public CView
{
protected: // �������л�����
	CItemFactoryView();
	DECLARE_DYNCREATE(CItemFactoryView)

// ����
public:
	CItemFactoryDoc* GetDocument() const;

// ����
public:

// ��д
	public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CItemFactoryView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // ItemFactoryView.cpp �ĵ��԰汾
inline CItemFactoryDoc* CItemFactoryView::GetDocument() const
   { return reinterpret_cast<CItemFactoryDoc*>(m_pDocument); }
#endif

