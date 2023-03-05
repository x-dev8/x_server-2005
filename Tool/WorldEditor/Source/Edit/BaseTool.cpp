/*******************************************************************************
*  Copyright ZWS (C) 2007 - All Rights Reserved
*
* File: 	BaseTool.cpp
* Date: 	11/09/2007
* Desc:
*
*******************************************************************************/
#include "stdafx.h"
#include "BaseTool.h"
#include "ToolManager.h"
#include "wintab/EditTablet.h"
#include "Utility.h"

#define ID_TOOL_TIMER	0x100
////////////////////////////////////////////////////////////////////////////////
void CBaseTool::BeginTimer( UINT uElapse )
{ 
	m_activeTimer = m_toolMgr->BeginTimer( ID_TOOL_TIMER, uElapse ); 
}

void CBaseTool::EndTimer()
{ 
	m_toolMgr->EndTimer( m_activeTimer ); 
}

Vector SphericalToCartesian(Vector kSpherical)
{
	Vector Position;
	float fAngle = kSpherical.z + PI * 0.5f;

	Position.x = kSpherical.x * cos(kSpherical.y) * sin(fAngle);
	Position.y = kSpherical.x * sin(kSpherical.y) * sin(fAngle);
	Position.z = kSpherical.x * cos(fAngle);

	return Position;
}

void CBaseTool::GetRelativePath( LPCTSTR fullModelName, char * localName )
{
	char objPath[MAX_PATH*2];
	char objName[MAX_PATH*2];
	if( !SpliteFullPathToDataPath( fullModelName, objPath, objName ) ) {
		return;
	}
	sprintf_s(localName,MAX_PATH*2,"%s\\%s", objPath, objName );
	_strlwr_s( localName ,MAX_PATH*2);
}


bool CBaseTool::CameraAdjust( CPoint point, UINT nFlags )
{
	CPoint delta		= point - m_oldPos;
	Vector2 viewSize;
	CWorldEditView* view = CWorldEditDoc::GetActiveMapDoc()->GetWorldView();
	view->GetViewSize( viewSize.x, viewSize.y );
	SwCamera* camera	= view->GetActiveCamera();
	if( viewSize.x < 1 || viewSize.y < 1 )
		return false;
	if( 0 != (nFlags&MK_SHIFT) ) 
	{
		Vector deltaRot;	

		deltaRot.x	= delta.y / viewSize.y * PI;
		deltaRot.y  = 0.f;
		deltaRot.z	= /*-*/delta.x / viewSize.x * PI;

		deltaRot += camera->GetRot();

		camera->SetRot( deltaRot );
		camera->Update(0.f,0.f);
	}
	else 
	{
// 		if((nFlags & MK_CONTROL) != 0)
// 		{
			Vector deltaPos;
			//deltaPos.x	= -delta.x / viewSize.x * 64.0f;
			//deltaPos.y  = 0.f;
			//deltaPos.z	= delta.y / viewSize.y * 64.0f;
			deltaPos.x	= -delta.x / viewSize.x * 64.0f;
			deltaPos.y	= delta.y / viewSize.y * 64.0f;
			deltaPos.z  = 0.f;
			if( deltaPos.x > 100.0f )
				deltaPos.x = 100.0f;

			if( deltaPos.y > 100.0f )
				deltaPos.y = 100.0f;

			if( 0 != (nFlags&MK_CONTROL) ) {
				deltaPos  = deltaPos * CAMERA_HUGE_STEP;
			}

			//Vector pos = camera->GetPos() + deltaPos;
			Vector pos = camera->GetPos() + deltaPos;
			// Get the inverse view matrix
			D3DXMATRIX m;
			D3DXMatrixInverse( &m, NULL, &camera->GetViewMatrix() );

			Vector worldPos;
			worldPos.x  = deltaPos.x*m._11 + deltaPos.y*m._21 + deltaPos.z*m._31;
			worldPos.y  = deltaPos.x*m._12 + deltaPos.y*m._22 + deltaPos.z*m._32;
			worldPos.z  = deltaPos.x*m._13 + deltaPos.y*m._23 + deltaPos.z*m._33;
			worldPos.x = m._41 + worldPos.x;
			worldPos.y = m._42 + worldPos.y;
			worldPos.z = m._43 + worldPos.z;

			//camera->SetPos( pos );
			//theApp.GetWorld()->SetActivePos( pos.x, pos.y );
			camera->SetPos( worldPos );
			theApp.GetWorld()->SetActivePos( worldPos.x, worldPos.y );

			camera->Update(0.f,0.f);
//		}
	}

	m_oldPos = point;
	return true;
}

bool CBaseTool::OnKeyUp( UINT nChar, UINT nRepCnt, UINT nFlags )
{
	if( nChar == VK_ADD  ||
		(nChar == VK_OEM_PLUS  && nFlags&MK_CONTROL)) 
	{
		Vector deltaPos;
		deltaPos.x	= 1.f;
		deltaPos.y  = 0.0f;
		deltaPos.z	= 0.0f;

		if( 0 != (nFlags&MK_SHIFT) ) {
			deltaPos = deltaPos * CAMERA_HUGE_STEP;
		}

		CameraFarNear(deltaPos);
	}
	if( nChar == VK_SUBTRACT  ||
		(nChar == VK_OEM_MINUS  && nFlags&MK_CONTROL)) 
	{
		Vector deltaPos;
		deltaPos.x	= -1.f;
		deltaPos.y  = 0.0f;
		deltaPos.z	= 0.0f;

		if( 0 != (nFlags&MK_CONTROL) ) {
			deltaPos = deltaPos * CAMERA_HUGE_STEP;
		}

		CameraFarNear(deltaPos);
	}
	return true;
}
void CBaseTool::CameraFarNear( Vector deltaPos )
{
	//SwCamera* camera = CWorldEditDoc::GetActiveMapDoc()->GetWorldView()->GetActiveCamera();
	//NiMatrix3 rot;
	//rot.FromEulerAnglesXYZ( camera->GetRot().x, camera->GetRot().y, camera->GetRot().z );
	//Vector pos = camera->GetPos() + rot * deltaPos;

	SwCamera* camera = CWorldEditDoc::GetActiveMapDoc()->GetWorldView()->GetActiveCamera();
	Vector pos = camera->GetPos();
	D3DXVECTOR3 dDir = camera->GetDir();
	Vector kDir;
	kDir.x = dDir.x;
	kDir.y = dDir.y;
	kDir.z = dDir.z;
	pos	+= kDir * deltaPos.x;

	camera->SetPos( pos );
	camera->Update( 0.0f, 0.0f );
}

bool CBaseTool::OnMouseWheel( UINT nFlags, short zDelta, CPoint point )
{
	Utility::AdjustCameraComeCloseOrFaraway(nFlags, zDelta);
	return true;
}

int CBaseTool::GetCloseIndex( const TPickResult &pickResult ,int except )
{
	int close_id = 0;
	float fMinDist = 100000.0f;
	for (sInt32 i = 0; i < pickResult.pickResultCount; ++i)
	{
		if (pickResult.pickResultInfo[i].resultType & except)
		{
			continue;
		}
		if (pickResult.pickResultInfo[i].dist < fMinDist)
		{
			fMinDist = pickResult.pickResultInfo[i].dist;
			close_id = i;						
		}
	}
	return close_id;

}