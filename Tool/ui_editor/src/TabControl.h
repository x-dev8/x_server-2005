#pragma once
#include "basecontrol.h"
#include "ButtonControl.h"
#include "FrameControl.h"

class CTabControl : public CBaseControl
{
public:
	enum
	{
		Item_Tab_Comments = 0
		,Item_Tab_FrameCount
		,Item_Tab_FrameFileName1
		,Item_Tab_FrameFileName2
		,Item_Tab_FrameFileName3
		,Item_Tab_FrameFileName4
		,Item_Tab_FrameFileName5
		,Item_Tab_Comments_Button

		,Item_Tab_Max
	};


public: /*Virtual Fun*/
	void Render( CDC* pDC, const RECT* pFatherRc );
	void OnSize();
	bool MouseMove( const POINT point, const RECT* pFatherRc );
	void AddToPropertyDlg();
	void AddToUIObjectDlg();
	bool SetData( const S_BaseData* /*[In]*/pData );
	bool GetData( S_BaseData* /*[Out]*/pData );

private:
	S_PropertyItem	m_ProTab[Item_Tab_Max];
	COLORREF		m_colComments;
	CButtonControl	m_btnTab[TAB_CONTROL_MAX];
	CFrameControl	m_frame;
	int				m_nTabCount;
	CString			m_strFrameFileName[TAB_CONTROL_MAX];

public:
	CTabControl(void);
	~CTabControl(void);
};
