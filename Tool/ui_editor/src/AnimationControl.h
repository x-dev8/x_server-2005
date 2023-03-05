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

class CAnimationControl :
	public CBaseControl
{
public:
	enum
	{
		Item_Picture_Max = 8
	};

	CAnimationControl(void);
	~CAnimationControl(void);

	void	AddToPropertyDlg();
	bool	SetData( const S_BaseData* /*[In]*/pData );
	void	AddToUIObjectDlg( );
	bool	GetData( S_BaseData* /*[Out]*/pData );


	CString		m_strPicName[Item_Picture_Max];
	S_PropertyItem	m_ProPicture[Item_Picture_Max];
	S_PropertyItem  m_nInterval;
	S_PropertyItem  m_nAutoStart;

private:
	CPicEditorDlg	m_PictureDlg[Item_Picture_Max];

	int				m_nCInterval;
	S_Combo			m_nCAutoStart;
};
