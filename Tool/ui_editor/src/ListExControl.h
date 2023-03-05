#pragma once
#include "basecontrol.h"
#include "ScrollBarControl.h"

class CListExControl : public CBaseControl
{
public:
	enum
	{
		Item_ListEx_Comments_State = 0
		,Item_ListEx_ItemHeight
		,Item_ListEx_ItemWidth
		,Item_ListEx_OffsetWidth
		,Item_ListEx_OffsetHeight
		,Item_ListEx_MaxHeightCount
		,Item_ListEx_SelBarColor
		,Item_ListEx_CanbePick
		,Item_ListEx_ScrollBar

		,Item_ListEx_Comments_Event
		,Item_ListEx_DrawInfo

		,Item_ListEx_Max
	};

public: /*Virtual Fun*/
	void OnSize();
	void Render( CDC* pDC, const RECT* pFatherRc );
	bool MouseMove( const POINT point, const RECT* pFatherRc );
	void AddToPropertyDlg();
	void AddToUIObjectDlg();
	bool SetData( const S_BaseData* /*[In]*/pData );
	bool GetData( S_BaseData* /*[Out]*/pData );
	void GetData_Event( int index );

public:
	CScrollBarControl	m_ScrollBar;
	COLORREF	m_colSelBar;
	int			m_nItemHeight;
	int			m_nItemWidth;
	int			m_nOffsetWidth;
	int			m_nOffsetHeight;
	int			m_nMaxHeightCount;
	BOOL		m_bCanbePick;
	COLORREF	m_colComments;

	CString		m_DrawInfoName;

private:
	S_PropertyItem	m_ProListEx[Item_ListEx_Max];

public:
	CListExControl(void);
	~CListExControl(void);
};
