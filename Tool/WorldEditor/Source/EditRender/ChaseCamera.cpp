#include "stdafx.h"
#include "MeTerrain/WorldEntry.h"
#include "MeTerrain/World.h"
#include "ChaseCamera.h"

ChaseCamera::ChaseCamera()
{

}
ChaseCamera::~ChaseCamera()
{

}

bool ChaseCamera::Create()
{
	m_ptCameraPos = Vector::ZERO;
	m_ptCameraRot = Vector( -PI*0.4f/*-PI*0.5f*/, 0.f/*-PI*0.5f*/, PI/*0.0f*/ );

	Update( 0.0f, 0.0f );

	SetUpVector( D3DXVECTOR3( 0, 0, 1 ) );

	return true;
}

void ChaseCamera::SetUpVector( const D3DXVECTOR3& up )
{
	m_ptCameraUp.x = up.x;
	m_ptCameraUp.y = up.y;
	m_ptCameraUp.z = up.z;
}

void ChaseCamera::Update( flt32 totalTime, flt32 deltaTime )
{

	D3DXVECTOR3 vEye;
	D3DXVECTOR3 vLookAt;

	vEye = m_vEye;
	vLookAt = m_vLookAt;

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

void ChaseCamera::SetProjectionMatrix(CView* pView)
{
	// Set the projection matrix
	float fFarPlane = CULL_DISTANCE/*MAX_RAYCAST_DISTANCE*/;
	//D3DXMatrixPerspectiveFovLH( &m_matProj, D3DX_PI/4.f, 1.4f, 0.1f, fFarPlane );
	RECT rect;
	pView->GetClientRect( &rect );
	float aspect = (rect.right - rect.left)/(float)(rect.bottom - rect.top);
	D3DXMatrixPerspectiveFovRH( &m_matProj, D3DX_PI/4.f, aspect, 0.1f, fFarPlane );
}