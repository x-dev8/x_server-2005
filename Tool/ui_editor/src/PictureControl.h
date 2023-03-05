/********************************************************************
	created:	2004/06/16
	created:	16:6:2004   10:20
	filename: 	e:\UIEditor\PictureControl.h
	file path:	e:\UIEditor
	file base:	PictureControl
	file ext:	h
	author:		WitSun
	
	purpose:	PictureControl
*********************************************************************/
#pragma once
#include "basecontrol.h"

class CPictureControl :
	public CBaseControl
{
public:
	enum
	{
		Item_Picture_Comments_Event = 0
		,Item_Picture_OnClick
		,Item_Picture_MouseOn
		,Item_Picture_MouseLeave
		,Item_Picture_LDBClick

		,Item_Picture_Max
	};

	CPictureControl(void);
	~CPictureControl(void);

	void	AddToPropertyDlg();
	void	GetData_Event( int index );

	CString		m_OnClickName;
	CString		m_MouseOnName;
	CString		m_MouseLeaveName;
	CString		m_LDBClickName;


private:
	S_PropertyItem	m_ProPicture[Item_Picture_Max];
};
