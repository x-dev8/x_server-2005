/********************************************************************
	created:	2004/06/16
	created:	16:6:2004   10:19
	filename: 	e:\UIEditor\EditControl.h
	file path:	e:\UIEditor
	file base:	EditControl
	file ext:	h
	author:		WitSun
	
	purpose:	EditControl
*********************************************************************/
#pragma once
#include "basecontrol.h"
#include "ScrollBarControl.h"

class CEditControl : public CBaseControl
{
public:
	enum
	{
		Item_Edit_Comments_State = 0
		,Item_Edit_Multiline
		,Item_Edit_ReadOnly
		,Item_Edit_Password
		,Item_Edit_Number
		,Item_Edit_TextAlign
		,Item_Edit_ScrollBar

		,Item_Edit_Comments_Event
		,Item_Edit_OnEnter
		,Item_Edit_OnTab
		,Item_Edit_OnLBtnDown
		,Item_Edit_OnLBtnUp
		,Item_Edit_DelByte

		,Item_Edit_Max
	};

public: /*Virtual Fun*/
	void Render( CDC* pDC, const RECT* pFatherRc );
	void OnSize();
	void AddToPropertyDlg();
	void AddToUIObjectDlg();
	bool SetData( const S_BaseData* /*[In]*/pData );
	bool GetData( S_BaseData* /*[Out]*/pData );
	bool MouseMove( const POINT point, const RECT* pFatherRc );
	void GetData_Event( int index );

public:
	BOOL	m_bMultiline;
	BOOL	m_bReadOnly;
	BOOL	m_bPassword;
	BOOL	m_bIsNumber;
	S_Combo m_comboTextAlign;
	CScrollBarControl	m_ScrollBar;
	COLORREF m_colComments;

	CString		m_OnEnterName;
	CString		m_OnTabName;
	CString		m_OnLBtnDownName;
	CString		m_OnLBtnUpName;
	CString		m_DelByteName;


private:
	S_PropertyItem	m_ProEdit[Item_Edit_Max];

public:
	CEditControl(void);
	~CEditControl(void);
};
