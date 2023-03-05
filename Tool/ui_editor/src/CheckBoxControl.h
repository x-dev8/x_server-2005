/********************************************************************
	created:	2004/06/16
	created:	16:6:2004   10:18
	filename: 	e:\UIEditor\CheckBoxControl.h
	file path:	e:\UIEditor
	file base:	CheckBoxControl
	file ext:	h
	author:		WitSun
	
	purpose:	CheckBoxControl
*********************************************************************/
#pragma once
#include "basecontrol.h"
#include "ButtonControl.h"

class CCheckBoxControl : public CBaseControl
{
public:
	enum
	{
		Item_CheckBox_Comments_State = 0
		,Item_CheckBox_Checked

		,Item_CheckBox_Comments_Event
		,Item_CheckBox_OnCheck

		,Item_CheckBox_Max
	};

public: /*Virtual Fun*/
	void Render( CDC* pDC, const RECT* pFatherRc );
	void OnSize();
	bool MouseMove( const POINT point, const RECT* pFatherRc );
	void AddToPropertyDlg();
	void AddToUIObjectDlg();
	bool SetData( const S_BaseData* /*[In]*/pData );
	bool GetData( S_BaseData* /*[Out]*/pData );
	void GetData_Event( int index );

public:
	BOOL			m_bChecked;
	CString			m_OnCheckName;

private:
	S_PropertyItem	m_ProCheckBox[Item_CheckBox_Max];
	CButtonControl	m_btnChecked;
	COLORREF		m_colChecked;

public:
	CCheckBoxControl(void);
	~CCheckBoxControl(void);
};
