/*******************************************************************************
*  Copyright ZNWL (C) 2007 - All Rights Reserved
*
* File: 	NdlCamera.cpp
* Date: 	01/18/2007
* Desc:
*
*******************************************************************************/
#include "stdafx.h"
#include "MeTerrain/WorldEntry.h"
#include "EditCamera.h"
#include "MeTerrain/World.h"

////////////////////////////////////////////////////////////////////////////////
CEditCamera::CEditCamera()
{
	m_ptCameraPos		= Vector::ZERO;
	m_ptCameraRot		= Vector::ZERO;
	m_scl		= 1.0f;


	m_ptCameraUp		= Vector(0.f, 0.f, 1.f);	// Z axis

	m_bNeedUpdateViewMatrix = true;

}

CEditCamera::~CEditCamera()
{
}

bool CEditCamera::CreateDefault()
{
	//m_spCamera			= NiTCreate<NiCamera>();
	//ASSERT_NOTNULL( m_spCamera );

	//NiFrustum frustum	= m_spCamera->GetViewFrustum();
	//frustum.m_fFar		=  MAX_RAYCAST_DISTANCE;
	//frustum.m_fNear		=  1.0f;
	//frustum.m_fLeft		= -0.5f;
	//frustum.m_fRight	=  0.5f;
	//frustum.m_fTop		=  0.5f;
	//frustum.m_fBottom	= -0.5f;
	//frustum.m_bOrtho	= false;
	//m_spCamera->SetViewFrustum( frustum );

	// 调整摄像机为　Z 轴朝上．
	m_ptCameraPos = Vector::ZERO;
	m_ptCameraRot = Vector( -PI*0.4f/*-PI*0.5f*/, 0.f/*-PI*0.5f*/, PI/*0.0f*/ );
		
	m_bNeedUpdate = true;
	Update( 0.0f, 0.0f );

	return true;
}


bool CEditCamera::Clone( CEditCamera* camera )
{

	return true;
}


bool CEditCamera::ScreenToWorldRay( const Vector2& scrPos, Vector& worldPos, Vector& worldDir )
{
	D3DXMATRIX matView = GetViewMatrix();
	D3DXMATRIX matProj = GetProjMatrix();
	D3DXVECTOR3 v;

	CWorldEditView* pEditView = CWorldEditDoc::GetActiveMapDoc()->GetWorldView();
	//unsigned int uiWidth;
	//unsigned int uiHeight;
	//pEditView->GetBackbufferWidthHeight(uiWidth, uiHeight);
	RECT rect;
	pEditView->GetClientRect( &rect );
	v.x =  ( ( ( 2.0f * scrPos.x ) / /*uiWidth*/(rect.right - rect.left)  ) - 1 ) / matProj._11;
	v.y =  -( ( ( 2.0f * scrPos.y ) / /*uiHeight*/(rect.bottom - rect.top) ) - 1 ) / matProj._22;
	v.z = -1.0f;

	// Get the inverse view matrix
	D3DXMATRIX m;
	D3DXMatrixInverse( &m, NULL, &matView );

	// Transform the screen space pick ray into 3D space
	worldDir.x  = v.x*m._11 + v.y*m._21 + v.z*m._31;
	worldDir.y  = v.x*m._12 + v.y*m._22 + v.z*m._32; 
	worldDir.z  = v.x*m._13 + v.y*m._23 + v.z*m._33;

	worldPos.x = m._41;
	worldPos.y = m._42;
	worldPos.z = m._43;

	worldDir.normalize();

	return true;
}

void CEditCamera::Update( flt32 totalTime, flt32 deltaTime )
{
	if( !m_bNeedUpdate )
		return;

	m_bNeedUpdate = false;
	// 用下面代码替代
// 	NiMatrix3 rot;
// 	rot.FromEulerAnglesXYZ( m_ptCameraRot.x, m_ptCameraRot.y, m_ptCameraRot.z );
	//D3DXMATRIX kXRot, kYRot, kZRot;
	//D3DXMatrixRotationX(&kXRot,m_ptCameraRot.x);
	//D3DXMatrixRotationY(&kYRot,m_ptCameraRot.y);
	//D3DXMatrixRotationZ(&kZRot,m_ptCameraRot.z);
	//m_matView = kXRot*(kYRot*kZRot);

	D3DXVECTOR3 vEye;
	D3DXVECTOR3 vLookAt;

	CaluEyeAndLookat( vEye,vLookAt );

	D3DXVECTOR3 vUp;
	vUp.x = m_ptCameraUp.x;
	vUp.y = m_ptCameraUp.y;
	vUp.z = m_ptCameraUp.z;
	//D3DXMatrixLookAtLH( &m_matView,&vEye,&vLookAt,&vUp );	
	D3DXMatrixLookAtRH( &m_matView,&vEye,&vLookAt,&vUp );	
	m_vEye = vEye;
	m_vDir = vLookAt-vEye;
	D3DXVec3Normalize( &m_vDir, &m_vDir );
	D3DXVec3Cross( &m_vCross, &m_vDir, &vUp );
	D3DXVec3Normalize( &m_vCross, &m_vCross );

	m_frustum.BuildFrustum( m_matProj,m_matView );
	
	m_bNeedUpdateViewMatrix = true;

	GetMe3dConfig()->GetCamera()->SetLeftHand(false);
	GetMe3dConfig()->GetCamera()->SetViewParams(m_vEye, m_vEye+m_vDir, vUp);
}

void CEditCamera::SetPos( const Vector& pos )
{
	m_ptCameraPos.x		= pos.x;
	m_ptCameraPos.y		= pos.y;
	m_ptCameraPos.z		= pos.z;
	
	CWorldEditDoc::GetActiveMapDoc()->UpdateMinimap();
	m_bNeedUpdate		= true;
}

void CEditCamera::SetRot( const Vector& rot )
{
	m_ptCameraRot		= rot;
	if( rot.x > 0)
		m_ptCameraRot.x = -0.001f;

	if( m_ptCameraRot.y > PI)
		m_ptCameraRot.y -= PI * 2.f;
	if( m_ptCameraRot.y < -PI)
		m_ptCameraRot.y += PI * 2.f;

	if( m_ptCameraRot.z > PI)
		m_ptCameraRot.z -= PI * 2.f;
	if( m_ptCameraRot.z < -PI)
		m_ptCameraRot.z += PI * 2.f;
	Trace( "camera rot %.3f, %.3f, %.3f\n", m_ptCameraRot.x, m_ptCameraRot.y, m_ptCameraRot.z );

	CWorldEditDoc::GetActiveMapDoc()->UpdateMinimap();
	m_bNeedUpdate		= true;
}


const flt32& CEditCamera::GetScl() const
{
	return m_scl;
}

void CEditCamera::SetScl( const flt32& scl )
{
	m_scl		= scl;
}

bool CEditCamera::Create()
{
	return CreateDefault();
}

void CEditCamera::SetProjectionMatrix(CView* pView)
{
	// Set the projection matrix
	float fFarPlane = CULL_DISTANCE/*MAX_RAYCAST_DISTANCE*/;
	//D3DXMatrixPerspectiveFovLH( &m_matProj, D3DX_PI/4.f, 1.4f, 0.1f, fFarPlane );
	RECT rect;
	pView->GetClientRect( &rect );
	float aspect = (rect.right - rect.left)/(float)(rect.bottom - rect.top);
	D3DXMatrixPerspectiveFovRH( &m_matProj, D3DX_PI/4.f, aspect, 0.1f, fFarPlane );
}