/*******************************************************************************
*  Copyright ZNWL (C) 2007 - All Rights Reserved
*
* File: 	ToolCamera.cpp
* Date: 	02/08/2007
* Desc:
*
*******************************************************************************/
#include "stdafx.h"
#include "ToolCamera.h"

////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
CToolCamera::CToolCamera()
{
		
}

CToolCamera::~CToolCamera()
{

}

bool CToolCamera::OnLMouseDown( UINT nFlags, CPoint point )
{
	m_isLDrag = true;
	m_oldPos = point; 

	//CWorldEditView* view = CWorldEditDoc::GetActiveMapDoc()->GetWorldView();
	//flt32 height;
	//view->GetWorldPicker()->GetHeight( -0.4f, -0.3f, height );
	//view->GetWorldPicker()->GetHeight( -0.4f, -0.6f, height );
	//view->GetWorldPicker()->GetHeight( -0.4f, -1.3f, height );
	//view->GetWorldPicker()->GetHeight( -0.4f, -1.8f, height );
	//view->GetWorldPicker()->GetHeight( -1.4f, -0.3f, height );
	//view->GetWorldPicker()->GetHeight( -1.4f, -0.6f, height );
	//view->GetWorldPicker()->GetHeight( -1.4f, -1.3f, height );
	//view->GetWorldPicker()->GetHeight( -1.4f, -1.8f, height );
	
	//view->GetWorldPicker()->TestDecal(  );

	return true;
}

bool CToolCamera::OnLMouseUp( UINT nFlags, CPoint point )
{
	m_isLDrag = false;

	return true;
}

bool CToolCamera::OnLMouseDblClk( UINT nFlags, CPoint point )
{

	return true;
}

bool CToolCamera::OnRMouseDown( UINT nFlags, CPoint point )
{
	m_isRDrag = true;
	m_oldPos = point; 

	
		
		
	return true;
}

bool CToolCamera::OnRMouseUp( UINT nFlags, CPoint point )
{
	m_isRDrag = false;

	
	
	
	return true;
}

bool CToolCamera::OnMouseMove( UINT nFlags, CPoint point )
{
	Vector2 viewSize;
	CWorldEditDoc::GetActiveMapDoc()->GetWorldView()->GetViewSize( viewSize.x, viewSize.y );
	if( viewSize.x < 1 || viewSize.y < 1 )
		return false;

	SwCamera* camera = CWorldEditDoc::GetActiveMapDoc()->GetWorldView()->GetActiveCamera();

	CPoint delta = point - m_oldPos;
	 if( m_isRDrag ){	// move
		 CameraAdjust(point, nFlags);
	}
	else {
		CWorldEditView* view = CWorldEditDoc::GetActiveMapDoc()->GetWorldView();
		sInt32 pickId = view->PickWorldTerrain( point );	
// 		if( -1 != pickId ) { 
// 			const TPickResult& pickResult = view->GetPickResult();
// 			flt32 pt[2];
// 			pt[0] = pickResult.pickResultInfo[pickId].point.x;
// 			pt[1] = pickResult.pickResultInfo[pickId].point.y;
// 			THeightResult heightResult;
// 			SwGlobal::GetWorldPicker()->GetHeight(pt[0],pt[1],heightResult);
// 		}

	}
	
	camera->Update( 0.0f, 0.0f );

	return true;
}

bool CToolCamera::OnKeyDown( UINT nChar, UINT nRepCnt, UINT nFlags )
{

	return true;
}

bool CToolCamera::OnKeyUp( UINT nChar, UINT nRepCnt, UINT nFlags )
{
	CBaseTool::OnKeyUp(nChar,nRepCnt,nFlags);
	return true;
}

void CToolCamera::SetActive( bool isActive /*= true */ )
{
	CBaseTool::SetActive(isActive);
	if (isActive)
	{
		if (CWorldEditDoc::GetActiveMapDoc())
		{
			CWorldEditView* pView = CWorldEditDoc::GetActiveMapDoc()->GetWorldView();
			pView->SetActiveCameraID(0);
		}
	}
}



