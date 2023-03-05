/********************************************************************
	created:	2004/06/16
	created:	16:6:2004   10:18
	filename: 	e:\UIEditor\ComboBoxControl.h
	file path:	e:\UIEditor
	file base:	ComboBoxControl
	file ext:	h
	author:		WitSun
	
	purpose:	ComboBoxControl
*********************************************************************/
#pragma once
#include "basecontrol.h"
#include "ButtonControl.h"
#include "EditControl.h"
#include "ListControl.h"

class CComboBoxControl : public CBaseControl
{
public:
	enum
	{
		Item_ComboBox_Comments_EditInput = 0
		,Item_ComboBox_Comments_ListSelect
		,Item_ComboBox_Comments_ButtonSelect

		,Item_ComboBox_Comments_Event
		,Item_ComboBox_OnChange
		,Item_ComboBox_ShowList

		,Item_ComboBox_Max
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

	CString			m_OnChangeName;
	CString			m_ShowListName;;

private:
	S_PropertyItem	m_ProComboBox[Item_ComboBox_Max];
	COLORREF		m_colComments;
	CEditControl	m_editInput;
	CListControl	m_listSelect;
	CButtonControl	m_buttonSelect;

public:
	CComboBoxControl(void);
	~CComboBoxControl(void);
};
