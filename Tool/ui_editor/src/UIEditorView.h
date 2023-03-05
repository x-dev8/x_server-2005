// UIEditorView.h : CUIEditorView 类的接口
//
#pragma once

class CUIEditorView : public CView
{
// 属性
public:
	CUIEditorDoc* GetDocument() const;

private:
	void	DrawDialog( CDC* pDC );

	void OnLButtonDownDialog( CPoint point );

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CUIEditorView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CRectTracker	m_rcSelect;
	bool			m_bErase;

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
public:
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);

protected: // 仅从序列化创建
	CUIEditorView();
	DECLARE_DYNCREATE(CUIEditorView)
public:
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);

	void GetFramePos( int* pLeft, int* pTop, int* pRight, int* pBottom );
};

#ifndef _DEBUG  // UIEditorView.cpp 的调试版本
inline CUIEditorDoc* CUIEditorView::GetDocument() const
   { return reinterpret_cast<CUIEditorDoc*>(m_pDocument); }
#endif

