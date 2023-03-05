/*******************************************************************************
*  Copyright ZNWL (C) 2007 - All Rights Reserved
*
* File: 	ToolLiquid.h
* Date: 	03/24/2007
* Desc:
*
*******************************************************************************/
#ifndef _EDIT_TOOLLIQUID_H__
#define _EDIT_TOOLLIQUID_H__

////////////////////////////////////////////////////////////////////////////////
#include "BaseTool.h"

class CWorldChunk;
////////////////////////////////////////////////////////////////////////////////
class CToolLiquid	: public CBaseTool
{
	friend class			CToolLiquidDlg;
public:
							CToolLiquid();
	virtual					~CToolLiquid();
	
	virtual ToolID			GetToolId()	{ return TOOL_LIQUID; };
	virtual bool			Create( CToolManager* toolMgr );
	void					Bind( CToolLiquidDlg* dlg );
	void					setMultiSel(bool b);

	virtual bool			OnLMouseDown( UINT nFlags, CPoint point );
	virtual bool			OnLMouseUp( UINT nFlags, CPoint point );
	virtual bool			OnLMouseDblClk( UINT nFlags, CPoint point );
	virtual bool			OnRMouseDown( UINT nFlags, CPoint point );
	virtual bool			OnRMouseUp( UINT nFlags, CPoint point );
	virtual bool			OnMouseMove( UINT nFlags, CPoint point );
	virtual bool			OnKeyDown( UINT nChar, UINT nRepCnt, UINT nFlags );
	virtual bool			OnKeyUp( UINT nChar, UINT nRepCnt, UINT nFlags );

	virtual void			Render();


	bool					UpdateLayer( flt32* pt );
	void					SetLock( bool isLock )	{ m_isLock = isLock; };
	bool					RefreshLiquid();
	bool					IsCurSelectedChunkHaveLiquid();
	bool					RemoveCurSelectedLiquid();

	bool					m_multiSel;
protected:
	bool					m_isLock;
	flt32					m_height;
	flt32					m_alphaCoaf;
	sInt32					m_blockCount;			// 块数,用来生成名字和调试.
	sInt32					m_liquidId;
	CToolLiquidDlg*			mLiquidDlg;

	CWorldChunk*			m_selWorldChunk;
	CResEditMgr*			m_selResMgr;
	COLORREF				m_NiColor;

	vector<CWorldChunk*>	m_vecWorldChunk;

};





#endif	// _EDIT_TOOLLIQUID_H__