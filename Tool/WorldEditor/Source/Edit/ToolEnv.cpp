/*******************************************************************************
*  Copyright ZWS (C) 2008 - All Rights Reserved
*
* File: 	ToolEnv.cpp
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
#include "ui/ToolsScene/ToolEnvironment.h"
#include "ToolEnv.h"

////////////////////////////////////////////////////////////////////////////////
CToolEnv::CToolEnv()
{
	m_envDlg				= NULL;
	m_isPaintZone			= false;
	m_brushRadius			= 0;
	m_brushZoneId			= RES_INVALID_ID;
}

CToolEnv::~CToolEnv()
{
	
}

bool CToolEnv::Create( CToolManager* toolMgr )
{
	
	
	return true;
}

void CToolEnv::Bind( CToolEnvDlg* bindDlg )
{
	m_envDlg	= bindDlg;
}

bool CToolEnv::OnLMouseDown( UINT nFlags, CPoint point )
{
	CWorldEditView* view = CWorldEditDoc::GetActiveMapDoc()->GetWorldView();

	sInt32 pickId = view->PickWorldTerrain( point );
	if( -1 != pickId ) { 
		const TPickResult& pickResult = view->GetPickResult();
		flt32 pt[2];
		pt[0] = pickResult.pickResultInfo[pickId].point.x;
		pt[1] = pickResult.pickResultInfo[pickId].point.y;
		
		if ( m_isPaintZone )
		{
			PaintZone( pt, m_brushRadius );
			UpdateZone( pt );
		}
		else
		{
			CWorldChunk *worldChunk = pickResult.pickResultInfo[pickId].resultChunk;
			if (worldChunk != NULL && worldChunk->m_envId >= 0)
			{
				UpdateZonePreview( worldChunk->m_envId );
			}
		}
		m_oldPos = point;
	}
	m_isLDrag	= true;

	return true;
}

bool CToolEnv::OnLMouseUp( UINT nFlags, CPoint point )
{
	m_isLDrag	= false;

	return true;
}

bool CToolEnv::OnLMouseDblClk( UINT nFlags, CPoint point )
{

	return true;
}

bool CToolEnv::OnRMouseDown( UINT nFlags, CPoint point )
{
	m_isRDrag = true;
	m_oldPos = point; 

	return true;
}

bool CToolEnv::OnRMouseUp( UINT nFlags, CPoint point )
{
	m_isRDrag = false;

	return true;
}

bool CToolEnv::OnMouseMove( UINT nFlags, CPoint point )
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

						g_render->SetShowEnvId( worldChunk->m_envId );
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
					//	g_render->SetShowZoneId( worldChunk->m_envId );
					//	UpdateZonePreview( worldChunk->m_envId );
					//}
				}	
			}
		}
	}
	camera->Update( 0.0f, 0.0f );
	return true;
}

bool CToolEnv::OnKeyDown( UINT nChar, UINT nRepCnt, UINT nFlags )
{

	return true;
}

bool CToolEnv::OnKeyUp( UINT nChar, UINT nRepCnt, UINT nFlags )
{
	CBaseTool::OnKeyUp(nChar,nRepCnt,nFlags);

	return true;
}

void CToolEnv::Render()
{

}

void CToolEnv::SetPaintMode( bool isPaint )
{
	m_isPaintZone	= isPaint;
}

bool CToolEnv::PaintZone( flt32* pt, sInt32 brushSize )
{
	if( RES_INVALID_ID == m_brushZoneId )
		return false;

	g_render->SetShowEnvId( m_brushZoneId );

	return theApp.GetWorldEditor()->SetChunkEnv( pt, brushSize, m_brushZoneId );
}

bool CToolEnv::UpdateZone( flt32* pt )
{
	
	
	return true;
}

void CToolEnv::UpdateZonePreview( sInt32 zoneId )
{
	if( -1 == zoneId )
	{
		theApp.SetFogDepth( 0.f, 0.f);
		theApp.SetDefaultLight();
		m_envDlg->SetSelectedZoneName(_T("нч"));
		return;
	}

	if( !theApp.GetWorld()->IsActive() )
		return;

	if( !theApp.GetWorld()->HasName() )
		return;

	m_envDlg->UpdateZoneInfo(zoneId);

	CResEditMgr* resMgr = (CResEditMgr*)theApp.GetWorld()->GetWorldBuffer()->GetResMgr();
	Assert( NULL != resMgr );
	Assert( zoneId>=0 && zoneId<resMgr->GetEnvResList().size() );

	CNdlEnvRes* zoneRes	= (CNdlEnvRes*)resMgr->GetEnvResList()[zoneId];
	Assert( NULL != zoneRes );

	g_render->SetShowEnvId( zoneId );
	if( zoneRes->GetLightId()>= 0 && zoneRes->GetLightId() < resMgr->GetLightList().size() ) 
	{
		CNdlLightRes* lightRes	= (CNdlLightRes*)resMgr->GetLightList()[zoneRes->GetLightId()];
		theApp.SetLightDir( lightRes->m_lightDir );

		NiColor color;
		ConvertRGB2NiColor( lightRes->m_lightAmbient, color );
		theApp.SetLightAmbientColor( color );
		ConvertRGB2NiColor( lightRes->m_lightDiffuse, color );
		theApp.SetLightDiffuseColor( color );
		ConvertRGB2NiColor( lightRes->m_lightSpecular, color );
		theApp.SetLightSpecularColor( color );
		ConvertRGB2NiColor( lightRes->m_colorSunless, color );
		theApp.SetSunLessColor( color );
	}
	else
	{
		theApp.SetDefaultLight();

	}
	if( zoneRes->GetFogId()>= 0 && zoneRes->GetFogId() < resMgr->GetFogList().size() ) {
		CNdlFogRes* fogRes		= (CNdlFogRes*)resMgr->GetFogList()[zoneRes->GetFogId()];


		NiColor color;
		ConvertRGB2NiColor( fogRes->m_lightColor, color );
		theApp.SetFogColor( color );
		theApp.SetFogDepth( fogRes->m_lightNear, fogRes->m_lightFar );
	}
	else
	{
		theApp.SetFogDepth( 0.f, 0.f);
	}
}


