/*******************************************************************************
* Copyright ShenWang 2008 - All Rights Reserved
* 
* File: 	ToolClick2Add.h
* Create: 	11/04/08
* Desc:		
* Author:	Yuan Ding
*
* Modify:
* Modify by:
*******************************************************************************/

#ifndef __TOOL_CLICK2ADD_H__
#define __TOOL_CLICK2ADD_H__


////////////////////////////////////////////////////////////////////////////////
#include "BaseTool.h"

class CWorldChunk;
////////////////////////////////////////////////////////////////////////////////
class CToolClick2Add	: public CBaseTool
{
	friend class			CToolClick2AddDlg;
public:
	enum optMode {
		optMode_AddClick2Add = 0,
		optMode_Pick

	};
							CToolClick2Add();
	virtual					~CToolClick2Add();
	
	virtual ToolID			GetToolId()	{ return TOOL_CLICK2ADD; };
	virtual bool				Create( CToolManager* toolMgr );
	virtual	void			SetActive( bool isActive = true );
	void						Bind( CToolClick2AddDlg* dlg );
	void					Reset();

	virtual bool			OnLMouseDown( UINT nFlags, CPoint point );
	virtual bool			OnLMouseUp( UINT nFlags, CPoint point );
	virtual bool			OnLMouseDblClk( UINT nFlags, CPoint point );
	virtual bool			OnRMouseDown( UINT nFlags, CPoint point );
	virtual bool			OnRMouseUp( UINT nFlags, CPoint point );
	virtual bool			OnMouseMove( UINT nFlags, CPoint point );
	virtual bool			OnKeyDown( UINT nChar, UINT nRepCnt, UINT nFlags );
	virtual bool			OnKeyUp( UINT nChar, UINT nRepCnt, UINT nFlags );

	virtual void			Render();


	void					SetOptMode(optMode eMode);
	void					ShowPmpModel(  );
	void					ApplyClick2Add(float x,float y,float z);
	int						GetSelectedClick2AddPoint() const { return m_SelectedClick2AddPoint; }
	void					SetSelectedClick2AddPoint(int val) { m_SelectedClick2AddPoint = val; }
	void					SetCurrClick2Add(CSoundPointEditRes*			route);
protected:

	CToolClick2AddDlg*				m_click2AddDlg;

	CResEditMgr*					GetResMgr();
	void					DeletePointModel();

	CSoundPointEditRes*			m_currClick2Add;


	TObjectEditInfo*				m_selPmpBox;
	TObjectEditInfo*			m_pmpClick2AddPoint;
	TObjectEditInfo*			GetPmpModel();

	optMode						m_eoptMode;
	int						m_SelectedClick2AddPoint;
};






#endif //__TOOL_CLICK2ADD_H__