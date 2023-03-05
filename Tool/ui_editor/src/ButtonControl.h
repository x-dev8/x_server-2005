/********************************************************************
	created:	2004/06/16
	created:	16:6:2004   10:18
	filename: 	e:\UIEditor\ButtonControl.h
	file path:	e:\UIEditor
	file base:	ButtonControl
	file ext:	h
	author:		WitSun
	
	purpose:	ButtonControl
*********************************************************************/
#pragma once
#include "basecontrol.h"

class CButtonControl : public CBaseControl
{
public:
	enum
	{
		Item_Button_Comments_State = 0
		,Item_Button_MoveOn
		,Item_Button_Press
		,Item_Button_Disabled

		,Item_Button_Comments_Event
		,Item_Button_OnClick
		,Item_Button_MouseOn

		,Item_Button_Max
	};

public: /*Virtual Fun*/
	void Render( CDC* pDC, const RECT* pFatherRc );
	bool MouseMove( const POINT point, const RECT* pFatherRc );
	void AddToPropertyDlg();
	void AddToUIObjectDlg();
	bool SetData( const S_BaseData* /*[In]*/pData );
	bool GetData( S_BaseData* /*[Out]*/pData );
	void GetData_Event( int index );

public:
	CPicEditorDlg	m_PicMoveOn;
	CPicEditorDlg	m_PicPress;
	CPicEditorDlg	m_PicDisabled;

	CString			m_OnClickName;
	CString			m_MouseOnName;

private:
	S_PropertyItem	m_ProButton[Item_Button_Max];

public:
	CButtonControl();
	~CButtonControl();
};