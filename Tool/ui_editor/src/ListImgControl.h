/********************************************************************
	created:	2004/06/16
	created:	16:6:2004   10:19
	filename: 	e:\UIEditor\ListImgControl.h
	file path:	e:\UIEditor
	file base:	ListImgControl
	file ext:	h
	author:		WitSun
	
	purpose:	ListImgControl
*********************************************************************/
#pragma once
#include "basecontrol.h"
#include "ScrollBarControl.h"

class CListImgControl : public CBaseControl
{
public:
	enum
	{
		Item_ListImg_Comments_State = 0
		,Item_ListImg_IconSize
		,Item_ListImg_OffsetWidth
		,Item_ListImg_OffsetHeight
		,Item_ListImg_MaxHeightCount
		,Item_ListImg_CanbePick
		,Item_ListImg_ShowSelFrame
		,Item_ListImg_ColSelFrame
		,Item_ListImg_ScrollBar

		,Item_ListImg_Max
	};


public: /*Virtual Fun*/
	void Render( CDC* pDC, const RECT* pFatherRc );
	void OnSize();
	void AddToPropertyDlg();
	void AddToUIObjectDlg();
	bool SetData( const S_BaseData* /*[In]*/pData );
	bool GetData( S_BaseData* /*[Out]*/pData );
	bool MouseMove( const POINT point, const RECT* pFatherRc );

public:
	int		m_nIconSize;
	int		m_nOffsetWidth;
	int		m_nOffsetHeight;
	int		m_nMaxHeightCount;
	BOOL	m_bCanbePick;
	BOOL	m_bShowSelFrame;
	COLORREF m_colSelFrame;
	COLORREF m_colComments;
	CScrollBarControl	m_ScrollBar;

private:
	S_PropertyItem	m_ProListImg[Item_ListImg_Max];

public:
	CListImgControl(void);
	~CListImgControl(void);
};
