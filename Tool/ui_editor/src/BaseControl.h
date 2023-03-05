/********************************************************************
	created:	2004/06/16
	created:	16:6:2004   10:17
	filename: 	e:\UIEditor\BaseControl.h
	file path:	e:\UIEditor
	file base:	BaseControl
	file ext:	h
	author:		WitSun
	
	purpose:	BaseControl
*********************************************************************/
#pragma once
#include "../res/resource.h"
#include "PropertyList.h"
#include "MeUi/ControlData.h"
#include "PicEditorDlg.h"

#define DRAW_MODE_NORMAL	"普通"
#define DRAW_MODE_TILE		"平铺"
#define DRAW_MODE_STRECTCH	"拉伸"
#define DRAW_MODE_COMBO		"普通|平铺|拉伸|"

#define ALIGN_MODE_LEFT_TOP			"LeftTop"
#define ALIGN_MODE_RIGHT_TOP		"RightTop"
#define ALIGN_MODE_LEFT_BOTTOM		"LeftBottom"
#define ALIGN_MODE_RIGHT_BOTTOM		"RightBottom"
#define ALIGN_MODE_MIDDLE			"Middle"
#define ALIGN_MODE_LEFE				"Left"
#define ALIGN_MODE_TOP				"Top"
#define ALIGN_MODE_RIGHT			"Right"
#define ALIGN_MODE_BOTTOM			"Bottom"
#define ALIGN_MODE_TOP_MIDDLE		"TopMiddle"
#define ALIGN_MODE_LEFT_MIDDLE		"LeftMiddle"
#define ALIGN_MODE_RIGHT_MIDDLE		"RightMiddle"
#define ALIGN_MODE_BOTTOM_MIDDLE	"BottomMiddle"
#define ALIGN_MODE_CONTROL_COMBO	"LeftTop|RightTop|LeftBottom|RightBottom|Middle|TopMiddle|LeftMiddle|RightMiddle|BottomMiddle|"
#define ALIGN_MODE_TEXT_COMBO	"LeftTop|RightTop|LeftBottom|RightBottom|Middle|Left|Top|Right|Bottom|"

class CBaseControl
{
public:
	enum
	{
		Item_Comments_Normal = 0
		,Item_ID
		,Item_BackPic
		,ITEM_DisablePic
		,Item_Caption
		,Item_Tips
		,Item_Font
		,Item_Comments_Size
		,Item_Align
		,Item_X
		,Item_Y
		,Item_Width
		,Item_Height
		,Item_Comments_DrawMode
		,Item_DrawModeLeft
		,Item_DrawModeTop
		,Item_DrawModeRight
		,Item_DrawModeBottom
		,Item_DrawModeMiddle

		,Item_Max
	};

public: /*Virtual Fun*/
	virtual void Render( CDC* pDC, const RECT* pFatherRc );
	virtual void OnSize(){};
	virtual bool MouseMove( const POINT point, const RECT* pFatherRc );
	virtual void AddToPropertyDlg();
	virtual void AddToUIObjectDlg();
	virtual bool SetData( const S_BaseData* /*[In]*/pData );
	virtual bool GetData( S_BaseData* /*[Out]*/pData );
	virtual void GetData_Event( int index )				{}

public:
	void Release();

	void GetPos( int* /*[Out]*/pnX, int* /*[Out]*/pnY, const RECT* /*[In]*/pFatherRc );
	void SetPos( int nX, int nY, const RECT* pFatherRc );


	static int GetDrawMode( S_Combo* pCombo );
	static int GetAlignMode( S_Combo* pCombo );

protected:
	CString GetAlignMode( int nMode );

private:
	CString GetDrawMode( int nMode );

	void	BitBlt( CDC* pDst,
					int nDstX, int nDstY,
					int nDstWidth, int nDstHeight,
					CDC* pSrc,
					int nSrcX, int nSrcY,
					int nSrcWidht, int nSrcHeight,
					int nDrawMode );

public:
	CString			m_strID;
	CPicEditorDlg	m_PicBack;
	CPicEditorDlg	m_PicDisable;
	CString			m_strCaption;
	S_Font			m_stFont;
	S_Combo			m_comboAlign;
	int				m_nOffsetX;
	int				m_nOffsetY;
	int				m_nWidth;
	int				m_nHeight;
	S_Combo			m_comboLeft;
	S_Combo			m_comboTop;
	S_Combo			m_comboRight;
	S_Combo			m_comboBottom;
	S_Combo			m_comboMiddle;
	CString			m_Tips;

	int				m_nType;
	CString			m_strPicName;

private:
	S_PropertyItem	m_ProItem[Item_Max];

protected:
	CRect			m_rcDrawFrame;
	CRect			m_rcDrawClient;

public:
	CBaseControl();
	virtual ~CBaseControl();
};

