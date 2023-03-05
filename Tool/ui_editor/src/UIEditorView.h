// UIEditorView.h : CUIEditorView ��Ľӿ�
//
#pragma once

class CUIEditorView : public CView
{
// ����
public:
	CUIEditorDoc* GetDocument() const;

private:
	void	DrawDialog( CDC* pDC );

	void OnLButtonDownDialog( CPoint point );

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
	virtual ~CUIEditorView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CRectTracker	m_rcSelect;
	bool			m_bErase;

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
public:
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);

protected: // �������л�����
	CUIEditorView();
	DECLARE_DYNCREATE(CUIEditorView)
public:
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);

	void GetFramePos( int* pLeft, int* pTop, int* pRight, int* pBottom );
};

#ifndef _DEBUG  // UIEditorView.cpp �ĵ��԰汾
inline CUIEditorDoc* CUIEditorView::GetDocument() const
   { return reinterpret_cast<CUIEditorDoc*>(m_pDocument); }
#endif

