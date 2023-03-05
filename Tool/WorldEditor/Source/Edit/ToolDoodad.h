/*******************************************************************************
*  Copyright ZNWL (C) 2007 - All Rights Reserved
*
* File: 	ToolDoodad.h
* Date: 	08/06/2007
* Desc:
*
*******************************************************************************/
#ifndef _EDIT_TOOLDOODAD_H__
#define _EDIT_TOOLDOODAD_H__


////////////////////////////////////////////////////////////////////////////////
#include "BaseTool.h"

class CWorldChunk;
class CToolDoodadDlg;
////////////////////////////////////////////////////////////////////////////////
class CToolDoodad	: public CBaseTool
{
	friend class			CToolDoodadDlg;
public:
							CToolDoodad();
	virtual					~CToolDoodad();

	virtual ToolID			GetToolId()	{ return TOOL_DOODAD; };
	bool					Create( CToolManager* toolMgr );
	void					Reset();
	void					SetOptMode( sInt32 optMode );
	void						Bind( CToolDoodadDlg* dlg );
	void					CreateNewLevel(uInt32 funitSize,const char* name);
	bool					DeleteCurrLevel();
	TDoodadLevelInfo*		GetCurrLevel();
	const	char*			GetDoodadName(TDoodadLevelInfo* pInfo);
	void					ChangeDoodad(TDoodadLevelInfo* pInfo,const char* name);
	
	virtual bool			OnLMouseDown( UINT nFlags, CPoint point );
	virtual bool			OnLMouseUp( UINT nFlags, CPoint point );
	virtual bool			OnLMouseDblClk( UINT nFlags, CPoint point );
	virtual bool			OnRMouseDown( UINT nFlags, CPoint point );
	virtual bool			OnRMouseUp( UINT nFlags, CPoint point );
	virtual bool			OnMouseMove( UINT nFlags, CPoint point );
	virtual bool			OnKeyDown( UINT nChar, UINT nRepCnt, UINT nFlags );
	virtual bool			OnKeyUp( UINT nChar, UINT nRepCnt, UINT nFlags );

	virtual void			Render();
	bool						UpdateLayer( flt32* pt );
	void						SetLock( bool isLock )	{ m_isLock = isLock; };

	void					SetBrushIndex(sInt32 val);
	flt32					GetBrushDecalScale();

protected:
	sInt32					m_optMode;
	sInt32					m_brushIndex;
	flt32					m_coaf;

	sInt32					m_curDoodadClassId;
	sInt32					m_curDoodadId;

	uInt32					m_size[2];
	sInt32					m_density;


	sInt32					m_nCurrLevel;
	bool						m_isLock;
	CToolDoodadDlg*				m_layerDlg;
	CWorldChunk*				m_selWorldChunk;
	CResEditMgr*					m_selResMgr;
	
	CNdlDecalRes*				m_brushDecal;


};





#endif	// _EDIT_TOOLDOODAD_H__