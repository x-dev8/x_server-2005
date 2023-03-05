/********************************************************************
	created:	2004/06/16
	created:	16:6:2004   10:20
	filename: 	e:\UIEditor\ScrollBarControl.h
	file path:	e:\UIEditor
	file base:	ScrollBarControl
	file ext:	h
	author:		WitSun
	
	purpose:	ScrollBarControl
*********************************************************************/
#pragma once
#include "basecontrol.h"
#include "ButtonControl.h"

class CScrollBarControl : public CBaseControl
{
public:
	enum
	{
		Item_ScrollBar_Comments_Up = 0
		,Item_ScrollBar_Comments_Down
		,Item_ScrollBar_Comments_Bar

		,Item_ScrollBar_Max
	};

public: /*Virtual Fun*/
	virtual void Render( CDC* pDC, const RECT* pFatherRc );
	virtual void OnSize();
	virtual bool MouseMove( const POINT point, const RECT* pFatherRc );
	virtual void AddToPropertyDlg();
	virtual void AddToUIObjectDlg();
	virtual bool SetData( const S_BaseData* /*[In]*/pData );
	virtual bool GetData( S_BaseData* /*[Out]*/pData );

protected:
	S_PropertyItem	m_ProScrollBar[Item_ScrollBar_Max];
	COLORREF		m_colComments;
	CButtonControl	m_btnUp;
	CButtonControl	m_btnDown;
	CButtonControl	m_btnBar;

public:
	CScrollBarControl(void);
	virtual ~CScrollBarControl(void);
};
