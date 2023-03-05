/********************************************************************
	created:	2004/06/16
	created:	16:6:2004   10:19
	filename: 	e:\UIEditor\ListControl.h
	file path:	e:\UIEditor
	file base:	ListControl
	file ext:	h
	author:		WitSun
	
	purpose:	ListControl
*********************************************************************/
#pragma once
#include "basecontrol.h"
#include "ScrollBarControl.h"

class CListControl : public CBaseControl
{
public:
	enum
	{
		Item_List_Comments_State = 0
		,Item_List_ItemHeight
		,Item_List_SelBarColor
		,Item_List_ScrollBar

		,Item_List_Comments_Event
		,Item_List_SelectChange
		,Item_List_LDBClick
		,Item_List_LRBClick
		,Item_List_ShiftRBClick
		,Item_List_ShiftLBClick
		,Item_List_HyberClick
		,Item_List_HyberRBClick
		,Item_List_HyberItemClick


		,Item_List_Max
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
	COLORREF	m_colComments;

	CString		m_SelectChangeName;
	CString		m_LDBClickName;
	CString		m_LRBClickName;
	CString		m_ShiftRBClickName;
	CString		m_ShiftLBClickName;
	CString		m_HyberClickName;
	CString		m_HyberRBClickName;
	CString		m_HyberItemClickName;

private:
	S_PropertyItem	m_ProList[Item_List_Max];

public:
	CListControl(void);
	~CListControl(void);
};
