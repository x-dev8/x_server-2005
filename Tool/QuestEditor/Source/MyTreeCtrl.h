#if !defined(AFX_TREECTRLBT_H__F2142A27_2B46_45A5_B502_3CFED4D1616F__INCLUDED_)
#define AFX_TREECTRLBT_H__F2142A27_2B46_45A5_B502_3CFED4D1616F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TreeCtrlBT.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTreeCtrlBT window
#include <map>
#include <afxtempl.h>
//�궨�庯���������ͷ�GDI����
#define RELEASE_GDI_RESOURCE(gdiResource) if(gdiResource.GetSafeHandle()){gdiResource.DeleteObject();}

//���������������Ϣ
typedef struct tagItemMsg  
{	
	HTREEITEM hItem;			//��ľ��
	CBitmap   ItemBitmap;		//���λͼ
	COLORREF  crTransparent;	//͸����ɫ
	tagItemMsg()
	{
		hItem   = NULL;
		
		crTransparent = RGB(255,255,255);
	}
	
	~tagItemMsg()
	{
		if ( ItemBitmap.GetSafeHandle() )
		{
			ItemBitmap.DeleteObject();
		}
	}
	
}ITEM_MSG;
typedef std::map<HTREEITEM,ITEM_MSG*>	ITEMMSG_MAP;

class MyTreeCtrl : public CTreeCtrl
{
// Construction
public:
	MyTreeCtrl();
	
public:

	//���ñ���λͼ
	BOOL SetBackgroudBitmap( UINT nID );
	BOOL SetBackgroudBitmap(LPCTSTR lpszRecourceName);
	
	//����ĳһ��λͼ
	void SetItemBitmap(HTREEITEM hItem, UINT nIdBitmap);
	void SetItemBitmap(HTREEITEM hItem, LPCTSTR lpszBitmap);

	//����չ��������ͼ��
	void SetExpandBitmap(UINT nIdExpand, UINT nIdCollapse, COLORREF crTransparent = RGB(255,255,255));
	
	//�����µ���Ŀ
	HTREEITEM InsertItemEx(HTREEITEM hParent, LPCTSTR lpszItem, UINT nIdBitmap = 0,COLORREF crTransparent = RGB(255,255,255));
	HTREEITEM InsertItemEx(HTREEITEM hParent, LPCTSTR lpszItem, LPCTSTR lpszBitmap,COLORREF crTransparent = RGB(255,255,255));
	//��������
	void EnableRowLine( BOOL bEnable = TRUE );
	//�Ƿ�������
	BOOL IsEnableRowLine();
	
	//�������ڵ㱳��
	void EnableRootBk( BOOL bEnable = TRUE );
	//�Ƿ������ڵ㱳��
	BOOL IsEnableRootBk();

	//��ȡĳһ����Ϣ
	ITEM_MSG* GetItemMsg(HTREEITEM hItem);

	//��õ�ǰ���ѡ�е���
	HTREEITEM GetCursorItem();

	//����ĳ����Ա༭
	CEdit* SetItemCanEdit(HTREEITEM hItem, bool bEdit);

	//չ�������������нڵ�
	void ExpandAllTreeNodes(HTREEITEM hRoot, BOOL bExpand);

	//�����ض��ڵ�
	HTREEITEM FindNodeItem(LPCTSTR lpszRoot, LPCTSTR lpszNode);


	//����ĳһ��ı�����ɫ
	void SetItemBgColor(HTREEITEM hItem, COLORREF leftcolor, COLORREF rightcolor);
	void ClearAllItemBgColor();
// Operations
protected:

	struct Color_Font
	{
		COLORREF leftcolor;
		COLORREF rightcolor;
	};

	CMap<void*, void*, Color_Font, Color_Font&> m_mapColorFont;
	
private:
	void Calculate();
	
	void GradientFillRect( CDC *pDC, CRect &rect, COLORREF col_from, COLORREF col_to, bool vert_grad );
	void DrawBackgroudBitmap(CDC* pDc);
	void DrawItem( CDC* pDC );
	void DrawRowLine(CPoint ptBegin, CPoint ptEnd, CDC *pDc = NULL);
	void DrawExpand(CRect rect, int state, CDC *pDc = NULL);
	void DrawItemBitmap(CRect rect, HTREEITEM hItem, CDC *pDc = NULL);
public:
	void DrawItemText(CRect rect, HTREEITEM hItem, bool bselected,CDC *pDc = NULL);
	void DrawItemText_(CRect rect, HTREEITEM hItem, COLORREF bgcolor, CDC *pDc = NULL);

	HTREEITEM FindNodeItemNode(HTREEITEM hItem, LPCTSTR lpszNode);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTreeCtrlBT)
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~MyTreeCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CTreeCtrlBT)
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

private:
	ITEMMSG_MAP		m_itmemsg_map;		//����������������Ϣ
	ITEM_MSG*       m_pCurDrawItemMsg;	//��ǰ���ڻ��Ƶ�����Ϣ

	CRect			m_rect;				// The client rect when drawing
	int				m_h_offset;			// 0... -x (scroll offset)
	int				m_h_size;			// width of unclipped window
	int				m_v_offset;			// 0... -y (scroll offset)
	int				m_v_size;			// height of unclipped window


	CBitmap			m_bmpBackgroud;		//����λͼ
	CImageList		m_ImageList;		//չ��������ͼ��
	int				m_nImageHeight;		//չ������ͼ��߶�
	int				m_nImageWidth;		//չ������ͼ����
	int				m_nItemHeight;		//��Ԫ��Ŀ�ĸ߶�

	bool			m_bEnableRowLine;	//��Ԫ��ֿ��ĺ��� true:��ʾ   false:��֮
	bool			m_bEnableRootBk;	//���ڵ���ı���   true:��ʾ   flase:��֮
	int             m_nCellWidth;		//��Ԫ��ͼ���ı��ļ��
	
	COLORREF		m_clrTextNormal;	//���������������ɫ
	COLORREF		m_clrTextSelect;	//ѡ�������������ɫ
	
	COLORREF		m_clrRoot_from;		//���ڵ㽥��ɫ
	COLORREF		m_clrRoot_to;		//���ڵ㽥��ɫ
	
	CFont			m_FontRoots;		//���ڵ�����
	CFont			m_FontChild;		//�ӽڵ�����

	HTREEITEM		m_hItemSelect;		//��ǰѡ�е���Ŀ���
	HTREEITEM       m_hItemMouseMove;	//��ǰ������ڵľ��
	CPoint			m_ptOldMouse;		//��һ��������ڵ�λ��

	
	
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TREECTRLBT_H__F2142A27_2B46_45A5_B502_3CFED4D1616F__INCLUDED_)
