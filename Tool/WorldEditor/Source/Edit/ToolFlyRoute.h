/*******************************************************************************
* Copyright ShenWang 2008 - All Rights Reserved
* 
* File: 	ToolFlyRoute.h
* Create: 	11/04/08
* Desc:		
* Author:	Yuan Ding
*
* Modify:
* Modify by:
*******************************************************************************/

#ifndef __TOOL_FLYROUTE_H__
#define __TOOL_FLYROUTE_H__


////////////////////////////////////////////////////////////////////////////////
#include "BaseTool.h"

#include "rollback\RecoveryManager.h"

class CWorldChunk;
////////////////////////////////////////////////////////////////////////////////
class CToolRoute	: public CBaseTool
{
	friend class			CToolRouteDlg;
public:
	enum optMode {
		optMode_AddRoute = 0,
		optMode_Pick

	};
							CToolRoute();
	virtual					~CToolRoute();
	
	virtual ToolID			GetToolId()	{ return TOOL_FLYROUTE; };
	virtual bool				Create( CToolManager* toolMgr );
	virtual	void			SetActive( bool isActive = true );
	void						Bind( CToolRouteDlg* dlg );
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
	void					ApplyFlyRoute(float x,float y,float z);
	int						GetSelectedRoutePoint() const { return m_SelectedRoutePoint; }
	void					SetSelectedRoutePoint(int val) { m_SelectedRoutePoint = val; }
	void					SetCurrRoute(CRouteRes*			route);

	//added by zilong. 2011-03-15. --------------------------------------
	/*--------------------------------------------------------
	Desc	: 渲染选择的路径点的序号
	--------------------------------------------------------*/
	void RenderIndex(void);
	void RenderIndex(int index_, const Vector &point_);
	//added by zilong. end. ---------------------------------------------

//operations
public:
	virtual void Redo(void);
	virtual void Undo(void);
	virtual bool CanRedo(void);
	virtual bool CanUndo(void);

	bool DoDeleteRoute(CNPCRouteRes *_pRes_);
	bool DeleteRoute(CNPCRouteRes *_pRes_);

	bool DoAddRoute(const char *pName_, bool bFlyRoute_);
	bool AddRoute(CNPCRouteRes *_pRes_);

	bool DoGenerateCloseRoute(CNPCRouteRes *_pRes_, bool bShow_);
	bool GenerateCloseRoute(CNPCRouteRes *_pRes_, bool bShow_, bool bGenerate_);

	bool DoChangeRouteProperty(CNPCRouteRes *_pRes_, const char *name_, sInt32 nextMapId_, sInt32 nextRouteId_);
	bool ChangeRouteProperty(CNPCRouteRes *_pRes_, const char *name_, sInt32 nextMapId_, sInt32 nextRouteId_);

	bool DoAddRoutePoint(CNPCRouteRes *_pRes_, float x_, float y_,float z_,bool bShow_);
	bool AddRoutePoint(CNPCRouteRes *_pRes_,  int index_, CNPCRouteRes::SNpcRoutePoint *pNpcPoint_, Vector *pPoint_, bool bShow_);

	bool DoDeleteRoutePoint(CNPCRouteRes *_pRes_, int index_);
	bool DeleteRoutePoint(CNPCRouteRes *_pRes_, int index_);

	bool DoChangeRoutePointPosition(CNPCRouteRes *_pRes_, int index_, float x_, float y_,float z_);
	bool ChangeRoutePointPosition(CNPCRouteRes *_pRes_, int index_, float x_, float y_,float z_);

	bool DoChangeRoutePointProperty(CNPCRouteRes *_pRes_, int index_, const CNPCRouteRes::SNpcRoutePoint &npcPoint_);
	bool ChangeRoutePointProperty(CNPCRouteRes *_pRes_, int index_, const CNPCRouteRes::SNpcRoutePoint &npcPoint_);

protected:

	CToolRouteDlg*				m_transportDlg;

	CResEditMgr*					GetResMgr();
	void					DeletePointModel();

	CRouteRes*			m_currRoute;


	TObjectEditInfo*				m_selPmpBox;
	TObjectEditInfo*			m_pmpRoutePoint;
	TObjectEditInfo*			GetPmpModel();

	optMode						m_eoptMode;
	int						m_SelectedRoutePoint;

	CRecoveryManager m_opManager;
};






#endif //__TOOL_FLYROUTE_H__