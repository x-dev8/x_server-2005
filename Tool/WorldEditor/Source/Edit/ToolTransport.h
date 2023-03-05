/*******************************************************************************
* Copyright ShenWang 2008 - All Rights Reserved
* 
* File: 	ToolTransport.h
* Create: 	11/04/08
* Desc:		
* Author:	Yuan Ding
*
* Modify:
* Modify by:
*******************************************************************************/

#ifndef __TOOL_TRANSPORT_H__
#define __TOOL_TRANSPORT_H__


////////////////////////////////////////////////////////////////////////////////
#include "BaseTool.h"

class CWorldChunk;
////////////////////////////////////////////////////////////////////////////////
class CToolTransport	: public CBaseTool
{
	friend class			CToolTransportDlg;
public:
	enum optMode {
		optMode_Transport = 0,
		optMode_Target,
		optMode_Pick

	};
							CToolTransport();
	virtual					~CToolTransport();
	
	virtual ToolID			GetToolId()	{ return TOOL_TRANSPORT; };
	virtual bool				Create( CToolManager* toolMgr );
	virtual	void			SetActive( bool isActive = true );
	void						Bind( CToolTransportDlg* dlg );
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
	void					ApplyTransport(float top,float left,float right,float bottom,sInt32 nIndex);
	void					ApplyTarget(float posX,float posY,float dir, BOOL bRed = FALSE, int nVestType = 0, int nMapId = -1);
protected:

	CToolTransportDlg*				m_transportDlg;

	CResEditMgr*					GetResMgr();
	void					DeleteModel();
	CTransportResBase*		GetEditTran(){return m_currTran;}
	CTransportResBase*			m_currTran;


	TObjectEditInfo*				m_selPmpBox;
	CTransportEditRes			m_pmpTransport;
	CTargetEditRes				m_pmpTarget;

	optMode						m_eoptMode;
};






#endif //__TOOL_TRANSPORT_H__