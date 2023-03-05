/********************************************************************
	created:	2004/06/16
	created:	16:6:2004   10:21
	filename: 	e:\UIEditor\TextControl.h
	file path:	e:\UIEditor
	file base:	TextControl
	file ext:	h
	author:		WitSun
	
	purpose:	TextControl
*********************************************************************/
#pragma once
#include "basecontrol.h"
#include "ScrollBarControl.h"

class CTextControl : public CBaseControl
{
public:
	enum
	{
		Item_Text_Comments = 0
		,Item_Text_TextAlign
		,Item_Text_SingleLine
		,Item_ScrollBar_BLeft

		,Item_Text_Comments_Event
		,Item_HyberClick
		,Item_Edit_ScrollBar

		//,Item_Text_Pic_Blank

		,Item_Text_Max
	};

public: /*Virtual Fun*/
	void Render( CDC* pDC, const RECT* pFatherRc );
	void OnSize();
	void AddToPropertyDlg();
	bool SetData( const S_BaseData* /*[In]*/pData );
	bool GetData( S_BaseData* /*[Out]*/pData );

	void GetData_Event( int index );

public:
	S_Combo m_comboTextAlign;
	CString		m_HyberClickName;
	//int m_PicTextBlank;
	CScrollBarControl	m_ScrollBar;
	COLORREF m_colComments;

	BOOL	m_bSingleLine;
	BOOL	m_bScrollBarLeft;

private:
	S_PropertyItem	m_ProText[Item_Text_Max];

public:
	CTextControl(void);
	~CTextControl(void);
};



