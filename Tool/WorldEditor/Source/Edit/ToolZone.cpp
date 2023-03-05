/*******************************************************************************
*  Copyright ZWS (C) 2008 - All Rights Reserved
*
* File: 	ToolZone.cpp
* Date: 	01/17/2008
* Desc:
*
*******************************************************************************/
#include "stdAfx.h"
#include "OptStack.h"
#include "Ndl/NdlWorldEditor.h"
#include "EditRes/NdlEditRes.h"
#include "MeTerrain/NdlResMgr.h"
#include "MeTerrain/NdlGlobalResMgr.h"
#include "ToolZone.h"
#include "ui/ToolsScene/ToolZoneDlg.h"

////////////////////////////////////////////////////////////////////////////////
CToolZone::CToolZone()
{
	m_zoneDlg				= NULL;
	m_isPaintZone			= false;
	m_brushRadius			= 0;
	m_brushZoneId			= RES_INVALID_ID;
}

CToolZone::~CToolZone()
{
	
}

bool CToolZone::Create( CToolManager* toolMgr )
{
	
	
	return true;
}

void CToolZone::Bind( CToolZoneDlg* bindDlg )
{
	m_zoneDlg	= bindDlg;
}

bool CToolZone::OnLMouseDown( UINT nFlags, CPoint point )
{
	CWorldEditView* view = CWorldEditDoc::GetActiveMapDoc()->GetWorldView();

	sInt32 pickId = view->PickWorldTerrain( point );
	if( -1 != pickId ) { 
		const TPickResult& pickResult = view->GetPickResult();
		flt32 pt[2];
		pt[0] = pickResult.pickResultInfo[pickId].point.x;
		pt[1] = pickResult.pickResultInfo[pickId].point.y;
		
		if( m_isPaintZone ) {
			PaintZone( pt, m_brushRadius );
			UpdateZone( pt );
		}
		else {
			CWorldChunk* worldChunk = pickResult.pickResultInfo[pickId].resultChunk;
			if( NULL != worldChunk ) {
				UpdateZonePreview( worldChunk->GetZoneId() );
			}
		}
		m_oldPos = point;
	}
	m_isLDrag	= true;

	return true;
}

bool CToolZone::OnLMouseUp( UINT nFlags, CPoint point )
{
	m_isLDrag	= false;

	return true;
}

bool CToolZone::OnLMouseDblClk( UINT nFlags, CPoint point )
{

	return true;
}

bool CToolZone::OnRMouseDown( UINT nFlags, CPoint point )
{
	m_isRDrag = true;
	m_oldPos = point; 

	return true;
}

bool CToolZone::OnRMouseUp( UINT nFlags, CPoint point )
{
	m_isRDrag = false;

	return true;
}

bool CToolZone::OnMouseMove( UINT nFlags, CPoint point )
{
	Vector2 viewSize;
	CWorldEditView* view = CWorldEditDoc::GetActiveMapDoc()->GetWorldView();
	view->GetViewSize( viewSize.x, viewSize.y );
	if( viewSize.x < 1 || viewSize.y < 1 )
		return false;

	//g_render->SetShowZoneId( RES_INVALID_ID );

	SwCamera* camera = CWorldEditDoc::GetActiveMapDoc()->GetWorldView()->GetActiveCamera();

	CPoint delta = point - m_oldPos;
	if( m_isRDrag ){	// move
		CameraAdjust(point, nFlags);
	}
	else if( m_isLDrag ) {
		CWorldEditView* view = CWorldEditDoc::GetActiveMapDoc()->GetWorldView();

		sInt32 pickId = view->PickWorldTerrain( point );
		if( -1 != pickId ) { 
			CPoint delta = point - m_oldPos;

			const TPickResult& pickResult = view->GetPickResult();
			flt32 dis = delta.x*delta.x+delta.y*delta.y;

			flt32 pt[2];
			pt[0] = pickResult.pickResultInfo[pickId].point.x;
			pt[1] = pickResult.pickResultInfo[pickId].point.y;

			if( dis > 64.0f ) {
				if( m_isPaintZone ) {
					PaintZone( pt, m_brushRadius );
					UpdateZone( pt );
				}
				else {
					CWorldChunk* worldChunk = pickResult.pickResultInfo[pickId].resultChunk;
					if( NULL != worldChunk ) {

						g_render->SetShowZoneId( worldChunk->GetZoneId() );
					}
				}
			}
		}
		m_oldPos = point;
	}
	else {
		CWorldEditView* view = CWorldEditDoc::GetActiveMapDoc()->GetWorldView();

		sInt32 pickId = view->PickWorldTerrain( point );
		if( -1 != pickId ) { 
			CPoint delta = point - m_oldPos;

			const TPickResult& pickResult = view->GetPickResult();
			flt32 dis = delta.x*delta.x+delta.y*delta.y;

			flt32 pt[2];
			pt[0] = pickResult.pickResultInfo[pickId].point.x;
			pt[1] = pickResult.pickResultInfo[pickId].point.y;

			//if( dis > 64.0f ) 
			{
				if( !m_isPaintZone ) {
					//CWorldChunk* worldChunk = pickResult.pickResultInfo[pickId].resultChunk;
					//if( NULL != worldChunk ) {
					//	g_render->SetShowZoneId( worldChunk->GetZoneId() );
					//	UpdateZonePreview( worldChunk->GetZoneId() );
					//}
				}	
			}
		}
	}
	camera->Update( 0.0f, 0.0f );
	return true;
}

bool CToolZone::OnKeyDown( UINT nChar, UINT nRepCnt, UINT nFlags )
{

	return true;
}

bool CToolZone::OnKeyUp( UINT nChar, UINT nRepCnt, UINT nFlags )
{
	CBaseTool::OnKeyUp(nChar,nRepCnt,nFlags);

	return true;
}

void CToolZone::Render()
{

}

void CToolZone::SetPaintMode( bool isPaint )
{
	m_isPaintZone	= isPaint;
}

bool CToolZone::PaintZone( flt32* pt, sInt32 brushSize )
{
	if( RES_INVALID_ID == m_brushZoneId )
		return false;

	g_render->SetShowZoneId( m_brushZoneId );
	m_zoneDlg->SetSaved(false);
	return theApp.GetWorldEditor()->SetChunkZone( pt, brushSize, m_brushZoneId );
}

bool CToolZone::UpdateZone( flt32* pt )
{
	
	
	return true;
}

void CToolZone::UpdateZonePreview( sInt32 zoneId )
{
	if( -1 == zoneId )
	{
		m_zoneDlg->SetSelectedZoneName(_T("无"));
		return;
	}

	if( !theApp.GetWorld()->IsActive() )
		return;

	if( !theApp.GetWorld()->HasName() )
		return;

	m_zoneDlg->UpdateZoneInfo(zoneId);

	CResEditMgr* resMgr = (CResEditMgr*)theApp.GetWorld()->GetWorldBuffer()->GetResMgr();
	Assert( NULL != resMgr );
	Assert( zoneId>=0 && zoneId<resMgr->GetZoneResList().size() );

	CNdlZoneRes* zoneRes	= (CNdlZoneRes*)resMgr->GetZoneResList()[zoneId];
	Assert( NULL != zoneRes );

	g_render->SetShowZoneId( zoneId );
}

void CToolZone::SetActive( bool isActive /*= true */ )
{
	CBaseTool::SetActive(isActive);
	CWorldTile* pTile = CURRENTTILE;
	if (NULL == pTile)
	{
		return;
	}
	if (isActive == false && !m_zoneDlg->GetSavedFlag())
	{
		::AfxMessageBox(_T("Zone的修改未保存！！！！请返回点击“导出到xml”按钮进行保存"));
	}
}

