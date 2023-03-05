/*******************************************************************************
*  Copyright ZNWL (C) 2007 - All Rights Reserved
*
* File: 	ToolLiquid.cpp
* Date: 	03/24/2007
* Desc:
*
*******************************************************************************/\
#include "stdafx.h"
#include "ToolLiquid.h"
#include "OptStack.h"
#include "Ndl/NdlWorldEditor.h"
#include "EditRes/NdlEditRes.h"
#include "MeTerrain/NdlResMgr.h"
#include "ui/Custom/TexturePreviewWnd.h"
#include "ui/ToolsWnd/ToolLiquidDlg.h"


////////////////////////////////////////////////////////////////////////////////
CToolLiquid::CToolLiquid()
{
	m_isLock		= false;
	m_height	= 0.0f;
	m_alphaCoaf	= 0.0f;
	mLiquidDlg  = NULL;
	m_selWorldChunk = NULL;
	m_selResMgr	= NULL;

	m_multiSel = false;
}

CToolLiquid::~CToolLiquid()
{
	m_height = 0.0f;
	m_alphaCoaf	= 0.0f;
}

bool CToolLiquid::Create( CToolManager* toolMgr )
{
	CBaseTool::Create( toolMgr );



	return true;
}

void CToolLiquid::Bind( CToolLiquidDlg* dlg )
{
	mLiquidDlg = dlg;
}


bool CToolLiquid::UpdateLayer( flt32* pt )
{
	if (m_isLock)
	{
		// 已锁定CHUNK, 不再更新
		return false;
	}

	// 得到当前鼠标HOVER在哪个CHUNK上
	if (theApp.GetWorldEditor()->GetSelWorld( pt, &m_selWorldChunk, &m_selResMgr))
	{
		if (NULL != mLiquidDlg)
		{
			mLiquidDlg->RefreshLiquid(pt);
		}
	}
	return true;
}


bool CToolLiquid::OnLMouseDown( UINT nFlags, CPoint point )
{
// 	m_isLDrag	= true;
// 	m_oldPos	= point; 
// 
// 	CWorldEditView* view = CWorldEditDoc::GetActiveMapDoc()->GetWorldView();
// 	
// 	sInt32 pickId = view->PickWorldTerrain( point );
// 	if( -1 != pickId ) { 
// 		const TPickResult& pickResult = view->GetPickResult();
// 		if( pickResult.pickResultInfo[pickId].point.z < m_height ) {
// 			if( emLOM_Add == m_optMode ) {
// 				theApp.GetWorldEditor()->PaintLiquid( pickResult.pickResultInfo[pickId].point, m_height, emLT_Ocean );
// 			}
// 			else if( emLOM_Del == m_optMode ) {
// 				
// 			}
// 			else {
// 
// 			}
// 		}
// 		else {
// 			::AfxMessageBox( _T("必须在低于设定高度的块上填充！") );
// 		}
// 	}
	if(m_multiSel)
	{
		for(int i=0;i<m_vecWorldChunk.size();++i)
		{
			if(m_vecWorldChunk[i]==m_selWorldChunk)
			{
				m_selResMgr->RefreshLiquidHeight(m_vecWorldChunk[i],m_height,m_NiColor,m_alphaCoaf);

				m_vecWorldChunk.erase(m_vecWorldChunk.begin()+i);

				return true;
			}
		}

		COLORREF color;
		color = RGB(255,255,255);
		m_selResMgr->RefreshLiquidHeight(m_selWorldChunk,m_height,color,m_alphaCoaf);
		m_vecWorldChunk.push_back(m_selWorldChunk);
	}
	return true;
}

bool CToolLiquid::OnLMouseUp( UINT nFlags, CPoint point )
{
	m_isLDrag = false;


	return true;
}

bool CToolLiquid::OnLMouseDblClk( UINT nFlags, CPoint point )
{
	return true;
}

bool CToolLiquid::OnRMouseDown( UINT nFlags, CPoint point )
{
	m_isRDrag = true;
	m_oldPos = point; 

	return true;
}

bool CToolLiquid::OnRMouseUp( UINT nFlags, CPoint point )
{
	m_isRDrag = false;



	return true;
}

bool CToolLiquid::OnMouseMove( UINT nFlags, CPoint point )
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
		m_oldPos = point;
	}
	else {
		sInt32 pickId = view->PickWorldTerrain( point );
		if( -1 != pickId ) { 
			const TPickResult& pickResult = view->GetPickResult();
			flt32 pt[2];
			pt[0] = pickResult.pickResultInfo[pickId].point.x;
			pt[1] = pickResult.pickResultInfo[pickId].point.y;
			UpdateLayer( pt );
		}
	}
	camera->Update( 0.0f, 0.0f );

	return true;
}

bool CToolLiquid::OnKeyDown( UINT nChar, UINT nRepCnt, UINT nFlags )
{

	return true;
}

bool CToolLiquid::OnKeyUp( UINT nChar, UINT nRepCnt, UINT nFlags )
{
	CBaseTool::OnKeyUp(nChar,nRepCnt,nFlags);
	if (nChar == VK_SPACE)
	{
		SetLock(!m_isLock);
		mLiquidDlg->UpdateLock(m_isLock);
	}

	return true;
}


void CToolLiquid::Render()
{
	
}

bool CToolLiquid::RefreshLiquid()
{
	if(!m_selWorldChunk)
		return false;
	CWorldEditDoc::GetActiveMapDoc()->AddTileModify(m_selWorldChunk->GetParentTile());


	if(m_multiSel)
	{
		COLORREF color;
		color = RGB(255,255,255);

		for(int i=0;i<m_vecWorldChunk.size();++i)
		{
			m_selResMgr->RefreshLiquidHeight(m_vecWorldChunk[i],m_height,color,m_alphaCoaf);
		}

		return true;
	}
	else
	{
		return m_selResMgr->RefreshLiquidHeight(m_selWorldChunk,m_height,m_NiColor,m_alphaCoaf);
	}

	return m_selResMgr->RefreshLiquidHeight(m_selWorldChunk,m_height,m_NiColor,m_alphaCoaf);

}

bool CToolLiquid::IsCurSelectedChunkHaveLiquid()
{
	return m_selResMgr->IsChunkLiquidExist(m_selWorldChunk);
}

bool CToolLiquid::RemoveCurSelectedLiquid()
{
	bool bResult = m_selResMgr->RemoveChunkLiquid(m_selWorldChunk);
	mLiquidDlg->UpdateLock(m_isLock);
	return bResult;
}

void CToolLiquid::setMultiSel(bool b)
{
	m_multiSel = b;

	if(m_multiSel)
	{
		m_vecWorldChunk.clear();
	}
	else
	{
		for(int i=0;i<m_vecWorldChunk.size();++i)
		{
			m_selResMgr->RefreshLiquidHeight(m_vecWorldChunk[i],m_height,m_NiColor,m_alphaCoaf);
		}
		m_vecWorldChunk.clear();
	}

	RefreshLiquid();
}