/*******************************************************************************
*  Copyright ZNWL (C) 2007 - All Rights Reserved
*
* File: 	ToolDoodad.cpp
* Date: 	08/06/2007
* Desc:
*
*******************************************************************************/
#include "stdafx.h"
#include "OptStack.h"
#include "Ndl/NdlWorldEditor.h"
#include "EditRes/NdlEditRes.h"
#include "MeTerrain/NdlResMgr.h"
#include "MeTerrain/NdlGlobalResMgr.h"
#include "ToolDoodad.h"
#include "ui/ToolsWnd/ToolDoodadDlg.h"
////////////////////////////////////////////////////////////////////////////////
namespace {

	enum emDoodadOptMode {
		emDOM_Assign   = 0,
		emDOM_Add,
		emDOM_Reduce,
		emDOM_Del,
		emDOM_ScaleRefresh
	};
};

////////////////////////////////////////////////////////////////////////////////
CToolDoodad::CToolDoodad()
{
	m_optMode			= emDOM_Assign;
	m_brushIndex			= 3;
	m_curDoodadClassId	= 0;
	m_curDoodadId		= 0;
	m_isLock			= false;
	m_layerDlg			= NULL;
	m_selWorldChunk	= NULL;
	m_selResMgr		= NULL;
	m_nCurrLevel		= -1;
	m_size[0]			= 100;
	m_size[1]			= 100;
	m_density			= 100;
	m_coaf				= 0.94f;
}

CToolDoodad::~CToolDoodad()
{
	SAFE_DELETE( m_brushDecal );
}

bool CToolDoodad::Create( CToolManager* toolMgr )
{
	CBaseTool::Create( toolMgr );


	m_brushDecal = MeNew CNdlDecalRes();
	char path[MAX_PATH];
	sprintf_s( path, "%s\\Required\\Helper\\brushDecal.tga", CWorld::GetAppCharDir() );
	m_brushDecal->Create( path, (1<<m_brushIndex)/m_coaf );
	m_brushDecal->SetScale(GetBrushDecalScale());
	return true;
}

bool CToolDoodad::UpdateLayer( flt32* pt )
{
	if( m_isLock )
		return false;

	CWorldChunk* oldWorldChunk = m_selWorldChunk;
	if( theApp.GetWorldEditor()->GetSelWorld( pt, &m_selWorldChunk, &m_selResMgr ) ) {
		if( NULL != m_layerDlg ) {
			if (m_selWorldChunk->GetDoodadLevelCount() > 0)
			{
				if (-1 == m_nCurrLevel)
				{
					m_nCurrLevel = 0;
				}
			}
			else
			{
				m_nCurrLevel = -1;
			}
			if (oldWorldChunk != m_selWorldChunk)
			{
				m_layerDlg->RefreshChunckDoodadLevel();
			}
			m_layerDlg->Refresh(pt);
		}
	}
	return true;
}

bool CToolDoodad::OnKeyUp( UINT nChar, UINT nRepCnt, UINT nFlags )
{
	CBaseTool::OnKeyUp(nChar,nRepCnt,nFlags);
	if( nChar == VK_SPACE ) {
		SetLock( !m_isLock );
		m_layerDlg->UpdateLock( m_isLock );
	}
	if( nChar == VK_OEM_4 ) 
	{
		if (m_brushIndex > 0)
		{
			--m_brushIndex;
			m_layerDlg->BrushChanged(m_brushIndex);
			m_brushDecal->SetScale( GetBrushDecalScale() );
		}		

	}
	if( nChar == VK_OEM_6 ) 
	{
		if (m_brushIndex + 1 < 7)
		{
			++m_brushIndex;
			m_layerDlg->BrushChanged(m_brushIndex);
			m_brushDecal->SetScale( GetBrushDecalScale() );
		}		

	}

	return true;
}


bool CToolDoodad::OnLMouseDown( UINT nFlags, CPoint point )
{
	m_isLDrag	= true;
	m_oldPos	= point; 

	
	return true;
}

bool CToolDoodad::OnLMouseUp( UINT nFlags, CPoint point )
{
	m_isLDrag = false;


	return true;
}

bool CToolDoodad::OnLMouseDblClk( UINT nFlags, CPoint point )
{
	return true;
}

bool CToolDoodad::OnRMouseDown( UINT nFlags, CPoint point )
{
	m_isRDrag = true;
	m_oldPos = point; 

	return true;
}

bool CToolDoodad::OnRMouseUp( UINT nFlags, CPoint point )
{
	m_isRDrag = false;



	return true;
}

bool CToolDoodad::OnMouseMove( UINT nFlags, CPoint point )
{
	Vector2 viewSize;
	CWorldEditView* view = CWorldEditDoc::GetActiveMapDoc()->GetWorldView();
	view->GetViewSize( viewSize.x, viewSize.y );
	if( viewSize.x < 1 || viewSize.y < 1 )
		return false;

	SwCamera* camera = CWorldEditDoc::GetActiveMapDoc()->GetWorldView()->GetActiveCamera();

	CPoint delta = point - m_oldPos;
	if( m_isRDrag ){	// move
		CameraAdjust(point, nFlags);
	}
	else if( m_isLDrag ) {
		sInt32 pickId = view->PickWorldTerrain( point );
		if( -1 != pickId ) { 
			const TPickResult& pickResult = view->GetPickResult();
			flt32 dis = delta.x*delta.x+delta.y*delta.y;
			flt32 pt[2];
			pt[0] = pickResult.pickResultInfo[pickId].point.x;
			pt[1] = pickResult.pickResultInfo[pickId].point.y;
			m_brushDecal->SetPos( pt );
			m_brushDecal->SetScale( GetBrushDecalScale() );
			if( dis > 64.0f ) {
				bool isInv = false;
				if( 0 != (nFlags&MK_CONTROL) ) {
					isInv = true;
				}
			}
		}
		m_oldPos = point;
	}
	else {
		sInt32 pickId = view->PickWorldTerrain( point );
		if( -1 != pickId ) { 
			const TPickResult& pickResult = view->GetPickResult();
			flt32 pt[2];
			pt[0] = pickResult.pickResultInfo[pickId].point.x;
			pt[1] = pickResult.pickResultInfo[pickId].point.y;
			m_brushDecal->SetPos( pt );
			m_brushDecal->SetScale( GetBrushDecalScale() );
			UpdateLayer( pt );
		}
	}
	camera->Update( 0.0f, 0.0f );

	// 拖动实现装饰物操作
	if (m_isLDrag)
	{
		CWorldEditView* view = CWorldEditDoc::GetActiveMapDoc()->GetWorldView();
		sInt32 pickId = view->PickWorldTerrain( point );
		TDoodadLevelInfo* pInfo = GetCurrLevel();
		if(pInfo && -1 != pickId ) { 
			const TPickResult& pickResult = view->GetPickResult();
			flt32 pt[2];
			pt[0] = pickResult.pickResultInfo[pickId].point.x;
			pt[1] = pickResult.pickResultInfo[pickId].point.y;
			theApp.GetWorldEditor()->PaintDoodads(  pt,pInfo->mdoodadId,pInfo->mulevelUnit, 1<<(m_brushIndex),m_density, m_size, m_optMode );
		}
	}

	return true;
}

bool CToolDoodad::OnKeyDown( UINT nChar, UINT nRepCnt, UINT nFlags )
{
	
	return true;
}


void CToolDoodad::SetOptMode( sInt32 optMode )
{
	m_optMode = optMode;
}

void CToolDoodad::Render()
{
#ifdef ST_EDITOR_DOODAD
	if( m_brushDecal->IsFill() )
		g_render->RenderGeometry( m_brushDecal->GetTriShape() );
#endif
	if( m_brushDecal ->IsFill() )
	{
		m_brushDecal->Render();
	}
	
}

void CToolDoodad::Bind( CToolDoodadDlg* dlg )
{
		m_layerDlg = dlg;

}

void CToolDoodad::CreateNewLevel( uInt32 ulevelUnit ,const char* name)
{
	m_nCurrLevel = m_selWorldChunk->AddDoodadLevel(ulevelUnit,true);

	ChangeDoodad(GetCurrLevel(),name);
}

TDoodadLevelInfo*		CToolDoodad::GetCurrLevel()
{
	if	(-1 != m_nCurrLevel)
		return m_selWorldChunk->GetDoodadLevel(m_nCurrLevel);
	return NULL;
}

bool CToolDoodad::DeleteCurrLevel( )
{
	bool bRet = m_selWorldChunk->DeleteDoodadLevel(m_nCurrLevel);
	if (m_nCurrLevel == m_selWorldChunk->GetDoodadLevelCount())
	{
		--m_nCurrLevel;
	}
	return bRet;
}

const	char* CToolDoodad::GetDoodadName( TDoodadLevelInfo* pInfo )
{
	CDoodadRes* pNdlDoodadRes = m_selResMgr->GetDoodadRes(pInfo->mdoodadId);
	return pNdlDoodadRes->GetName();
}

void CToolDoodad::ChangeDoodad( TDoodadLevelInfo* pInfo ,const char* name)
{
	if (RES_INVALID_ID != pInfo->mdoodadId)
	{
		m_selResMgr->PopDoodad(pInfo->mdoodadId);
	}
	pInfo->mdoodadId =  m_selResMgr->PushDoodad(name);
	pInfo->RefreshDoodadInstance(m_selResMgr,m_selWorldChunk);
}

void CToolDoodad::SetBrushIndex( sInt32 val )
{
	m_brushIndex = val;
}

flt32 CToolDoodad::GetBrushDecalScale()
{
	flt32 fNewScale = (1<<m_brushIndex)*1.0f/(1<<3);
	if (NULL != GetCurrLevel())
	{
		fNewScale *= (WORLD_TILE_CHUNK_ATOM_NUM*1.0f)/GetCurrLevel()->mulevelUnit;
	}
	return fNewScale/8;
}

void CToolDoodad::Reset()
{
	m_selWorldChunk	= NULL;
	m_selResMgr		= NULL;
	m_nCurrLevel		= -1;
	m_size[0]			= 100;
	m_size[1]			= 100;
	m_density			= 100;

}