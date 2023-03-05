/*******************************************************************************
*  Copyright ZWS (C) 2008 - All Rights Reserved
*
* File: 	ToolLight.cpp
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
#include "ToolLight.h"
#include "Ndl/NdlHelper.h"
#include "UI/ToolsScene/ToolWorldLight.h"

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
CToolLight::CToolLight()
{
	m_lightOrigin	= Vector::ZERO;
	m_lightDir		= Vector::UNIT_X;
	
	
	m_bindDlg		= NULL;
}

CToolLight::~CToolLight()
{
	m_bindDlg		= NULL;
}

bool CToolLight::Create( CToolManager* toolMgr )
{

	if( !LoadDirModel() )
		return false;
	
	return true;
}

void CToolLight::Bind( CToolWorldLightDlg* bindDlg )
{
	m_bindDlg	= bindDlg;
}

bool CToolLight::OnLMouseDown( UINT nFlags, CPoint point )
{
	if( 0 != (nFlags&MK_SHIFT) ) {
		CWorldEditView* view = CWorldEditDoc::GetActiveMapDoc()->GetWorldView();

		sInt32 pickId = view->PickWorldTerrain( point );
		if( -1 != pickId ) { 
			const TPickResult& pickResult = view->GetPickResult();
			flt32 pt[2];
			pt[0] = pickResult.pickResultInfo[pickId].point.x;
			pt[1] = pickResult.pickResultInfo[pickId].point.y;
			m_oldPos = point;

			m_lightOrigin.x = pickResult.pickResultInfo[pickId].point.x;
			m_lightOrigin.y = pickResult.pickResultInfo[pickId].point.y;
			m_lightOrigin.z	= pickResult.pickResultInfo[pickId].point.z + 3.0f;

			m_lightNode.model->SetPosition( m_lightOrigin );
			m_lightNode.model->UpdateByParam( 0.f );


		}
	}

	m_isLDrag	= true;
	m_oldPos = point;

	return true;
}

bool CToolLight::OnLMouseUp( UINT nFlags, CPoint point )
{
	m_isLDrag	= false;

	return true;
}

bool CToolLight::OnLMouseDblClk( UINT nFlags, CPoint point )
{

	return true;
}

bool CToolLight::OnRMouseDown( UINT nFlags, CPoint point )
{
	m_isRDrag = true;
	m_oldPos = point; 

	return true;
}

bool CToolLight::OnRMouseUp( UINT nFlags, CPoint point )
{
	m_isRDrag = false;

	return true;
}

bool CToolLight::OnMouseMove( UINT nFlags, CPoint point )
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
			CPoint delta = point - m_oldPos;

			Vector kSpherical;	
			kSpherical.y  = delta.x / viewSize.x;
			kSpherical.z	= delta.y / viewSize.y;
			if( 0 != (nFlags&MK_CONTROL) ) {
				kSpherical  = kSpherical*CAMERA_HUGE_STEP;
			}
			kSpherical.x	= 1.0f;

			if( NULL != m_bindDlg )
			{
				m_bindDlg->UpdateDirLight( kSpherical );
			}
		m_oldPos = point;
	}
	else {

	}
	camera->Update( 0.0f, 0.0f );
	return true;
}

bool CToolLight::OnKeyDown( UINT nChar, UINT nRepCnt, UINT nFlags )
{
	
	return true;
}

bool CToolLight::OnKeyUp( UINT nChar, UINT nRepCnt, UINT nFlags )
{
	CBaseTool::OnKeyUp(nChar,nRepCnt,nFlags);
	
	return true;
}

void CToolLight::Render()
{
	m_lightNode.Render( 0.5f );
}

bool CToolLight::CalcLightPosition()
{
	CWorldEditView* view	= CWorldEditDoc::GetActiveMapDoc()->GetWorldView();

	flt32 w,h;
	view->GetViewSize( w, h );

	CPoint pt;
	pt.x			= w * 0.5f;
	pt.y			= h * 0.5f;
	sInt32 pickId	= view->PickWorldTerrain( pt );
	if( -1 != pickId ) { 
		const TPickResult& pickResult = view->GetPickResult();
		m_lightOrigin.x = pickResult.pickResultInfo[pickId].point.x;
		m_lightOrigin.y = pickResult.pickResultInfo[pickId].point.y;
		m_lightOrigin.z	= 2.0f;//pickResult.pickResultInfo[pickId].point.z;

		return true;
	}
	return false;
}


void CToolLight::UpdateLightLight()
{
//	UpdateLightNode();

}


bool CToolLight::LoadDirModel()
{
	char file[MAX_PATH*2];
	sprintf_s( file, "%s\\%s", CWorld::GetAppCharDir(), "Required\\Helper\\z.mex" );//Model\\DirLight.mex" );

	return m_lightNode.LoadFromFile( file );
}

void CToolLight::SetLightDir( Vector dir )
{
	m_lightDir = dir;
	UpdateLightNode();
}

void CToolLight::UpdateLightNode()
{
	m_lightDir.normalize();
	// 用光朝向计算三个轴夹角不对，应该用欧拉角计算绕轴旋转角度，计算2个轴旋转角度就够
	//Vector unitX = Vector::UNIT_X;

	//Quaternion rot = RotationArc( unitX, m_lightDir );

	//float length = Sqrt(rot.x * rot.x + rot.y * rot.y + rot.z * rot.z);

	//float angle = 0.f;
	//Vector axis;
	//if ( length < 1e-03f )
	//{
	//	angle = 0;
	//	axis.x = 0;
	//	axis.y = 0;
	//	axis.z = 0;
	//}
	//else
	//{
	//	angle = 2.0f * acos(rot.w);
	//	float invLength = 1.0f/length;
	//	axis.x = rot.x * invLength;
	//	axis.y = rot.y * invLength;
	//	axis.z = rot.z * invLength;
	//}

	//m_lightNode.model->SetRotationX( axis.x * angle );
	//m_lightNode.model->SetRotationY( axis.y * angle );
	//m_lightNode.model->SetRotationZ( axis.z * angle );

	// 用欧拉角计算旋转量
	float Yaw = (float)asin(m_lightDir.y);
	float Pitch = (float)atan2((double)-m_lightDir.x, (double)-m_lightDir.z);
	m_lightNode.model->SetRotationX( Yaw );
	m_lightNode.model->SetRotationY( Pitch );
	m_lightNode.model->SetRotationZ( 0 );

	m_lightNode.model->SetPosition( m_lightOrigin - m_lightDir / 5.f );
	m_lightNode.model->SetScale(0.5f);
	m_lightNode.model->UpdateByParam( 0.0f );
	m_lightNode.SetAlpha(0.5);
}