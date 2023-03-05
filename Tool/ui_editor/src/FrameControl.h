/********************************************************************
	created:	2004/06/16
	created:	16:6:2004   10:19
	filename: 	e:\UIEditor\FrameControl.h
	file path:	e:\UIEditor
	file base:	FrameControl
	file ext:	h
	author:		WitSun
	
	purpose:	FrameControl
*********************************************************************/
#pragma once
#include "basecontrol.h"

#define ARRAY_MODE_NORMAL	"∆’Õ®"
#define ARRAY_MODE_TOP		"÷√∂•"
#define ARRAY_MODE_BOTTOM	"÷√µ◊"
#define ARRAY_MODE_COMBO	"∆’Õ®|÷√∂•|÷√µ◊|"

class CFrameControl : public CBaseControl
{
public:
	enum
	{
		Item_Frame_Comments_State = 0
		,Item_Frame_Array
		,Item_Frame_Moveable
		,Item_Frame_Script

		,Item_Frame_Event
		,Item_Frame_OnClick
		,Item_Frame_OnRBtnDown
		,Item_Frame_OnMouseMoveOn
		,Item_Frame_OnMouseMoveLeave
		,Item_Frame_OnFrameMove
		,Item_Frame_Run
		,Item_Frame_Render
		,Item_Frame_OnTab

		,Item_Frame_Max
	};

public: /*Virtual Fun*/
	void AddToPropertyDlg();
	bool SetData( const S_BaseData* /*[In]*/pData );
	bool GetData( S_BaseData* /*[Out]*/pData );
	void GetData_Event( int index );

public:
	static int GetArrayMode( S_Combo* pCombo );

private:
	CString GetArrayMode( int nMode );

public:
	S_Combo			m_comboArray;
	BOOL			m_bMoveable;
	CString			m_bScriptName;

	CString			m_OnClickName;
	CString			m_OnRBtnDownName;
	CString			m_OnMouseMoveOnName;
	CString			m_OnMouseMoveLeaveName;
	CString			m_OnFrameMoveName;
	CString			m_RunName;
	CString			m_RenderName;
	CString			m_OnTabName;

private:
	S_PropertyItem	m_ProFrame[Item_Frame_Max];

public:
	CFrameControl(void);
	~CFrameControl(void);
};
