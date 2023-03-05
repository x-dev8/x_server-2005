/*******************************************************************************
* Copyright ShenWang 2008 - All Rights Reserved
* 
* File: 	SwCamera.cpp
* Create: 	10/09/06
* Desc:		MeCamera基类
* Author:	Qiu Li
*
* Modify:
* Modify by:
*******************************************************************************/
#include "stdafx.h"
#include "Render/SwCamera.h"
//#include "NDL/NdlWorldPicker.h"

SwCamera::SwCamera(void)
{
}

SwCamera::~SwCamera(void)
{
}

bool SwCamera::Create()
{
	return true;
}

void SwCamera::Update( float fTotalTime, float fDeltaTime )
{	
	// 用下面代码替代
	// 	NiMatrix3 rot;
	// 	rot.FromEulerAnglesXYZ( m_ptCameraRot.x, m_ptCameraRot.y, m_ptCameraRot.z );
	D3DXMATRIX kXRot, kYRot, kZRot;
	D3DXMatrixRotationX(&kXRot,m_ptCameraRot.x);
	D3DXMatrixRotationY(&kYRot,m_ptCameraRot.y);
	D3DXMatrixRotationZ(&kZRot,m_ptCameraRot.z);
	m_matView = kXRot*(kYRot*kZRot);

}

void SwCamera::Destroy()
{
}


void SwCamera::SetPos(const Vector& pos )
{
	m_ptCameraPos = pos;
}

void SwCamera::SetRot(const Vector& rot )
{
	m_ptCameraRot = rot;
}

const Vector&	SwCamera::GetPos() const
{
	return m_ptCameraPos;
}

Vector& SwCamera::GetPos()
{
	return m_ptCameraPos;
}

const Vector& SwCamera::GetRot() const
{
	return m_ptCameraRot;
}

Vector& SwCamera::GetRot()
{
	return m_ptCameraRot;
}

void SwCamera::CaluEyeAndLookat( D3DXVECTOR3 &vEye,D3DXVECTOR3 &vLookat )
{
	D3DXVECTOR3 vDist(0,0,1);
	D3DXVec3Normalize( &vDist, &vDist );


	D3DXVECTOR3 vXAxis( 1, 0, 0 );
	D3DXMATRIX matRotX;
	D3DXMatrixRotationAxis(
		&matRotX,
		&vXAxis,
		m_ptCameraRot.x );
	D3DXVec3TransformCoord( &vDist, &vDist, &matRotX );

	D3DXVECTOR3 vZAxis( 0, 0, -1 );
	D3DXMATRIX matRotZ;
	D3DXMatrixRotationAxis(
		&matRotZ,
		&vZAxis,
		m_ptCameraRot.z );
	D3DXVec3TransformCoord( &vDist, &vDist, &matRotZ );
	D3DXVec3Normalize( &vDist, &vDist );

	vEye.x = m_ptCameraPos.x;
	vEye.y = m_ptCameraPos.y;
	vEye.z = m_ptCameraPos.z;
	vLookat= vEye - vDist*MAX_RAYCAST_DISTANCE;
}