///********************************************************************
//	created:	2004/06/16
//	created:	16:6:2004   10:19
//	filename: 	e:\UIEditor\ListControl.h
//	file path:	e:\UIEditor
//	file base:	ListControl
//	file ext:	h
//	author:		WitSun
//	
//	purpose:	ListControl
//*********************************************************************/
//#pragma once
//#include "basecontrol.h"
//#include "ScrollBarControl.h"
//
//class CTreeControl : public CBaseControl
//{
//public:
//	enum
//	{
//		Item_Tree_Comments_State = 0
//		,Item_Tree_OpenPic
//		,Item_Tree_ClosePic
//		,Item_Tree_ItemPic
//		,Item_Tree_ItemHeight
//		,Item_Tree_SelBarColor
//		,Item_Tree_ScrollBar
//
//		,Item_Tree_Comments_Event
//		,Item_Tree_SelectChange
//		,Item_Tree_LDBClick
//		,Item_Tree_LRBClick
//		,Item_Tree_ShiftRBClick
//		,Item_Tree_ShiftLBClick
//
//
//		,Item_Tree_Max
//	};
//
//public: /*Virtual Fun*/
//	void OnSize();
//	void Render( CDC* pDC, const RECT* pFatherRc );
//	bool MouseMove( const POINT point, const RECT* pFatherRc );
//	void AddToPropertyDlg();
//	void AddToUIObjectDlg();
//	bool SetData( const S_BaseData* /*[In]*/pData );
//	bool GetData( S_BaseData* /*[Out]*/pData );
//	void GetData_Event( int index );
//
//public:
//	CScrollBarControl	m_ScrollBar;
//	COLORREF	m_colSelBar;
//	int			m_nItemHeight;
//	COLORREF	m_colComments;
//
//	CString		m_SelectChangeName;
//	CString		m_LDBClickName;
//	CString		m_LRBClickName;
//	CString		m_ShiftRBClickName;
//	CString		m_ShiftLBClickName;
//
//	CPicEditorDlg	m_OpenPicDlg;
//	CPicEditorDlg	m_ClosePicDlg;
//	CPicEditorDlg	m_ItemPicDlg;
//
//private:
//	S_PropertyItem	m_ProList[Item_Tree_Max];
//public:
//	CTreeControl(void);
//	~CTreeControl(void);
//};
