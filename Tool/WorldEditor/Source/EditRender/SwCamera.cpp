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
#include "EditRender/SwCamera.h"
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

bool SwCamera::WorldToScreen( const Vector& p, int *x, int *y, int nScreenWidth, int nScreenHeight )
{
	D3DXVECTOR3 q;
	D3DXMATRIX matMix;
	D3DXMatrixMultiply( &matMix, &GetViewMatrix(), &GetProjMatrix() );
	D3DXVec3TransformCoord( &q, (D3DXVECTOR3*)&p, &matMix );

	*x = nScreenWidth/2+q.x*nScreenWidth/2;
	*y = nScreenHeight/2-q.y*nScreenHeight/2;

// 	if( q.z < 0 || q.z > 1 )
// 		return false;

	const flt32 error_limit = 0.01f;
	if(q.z < -error_limit || q.z > error_limit)
	{
		//ASSERT(false);

		return false;
	}

	return true;
}

bool SwCamera::WorldToScreen( const Vector& p, float *x, float *y, int nScreenWidth, int nScreenHeight )
{
	D3DXVECTOR3 q;
	D3DXMATRIX matMix;
	D3DXMatrixMultiply( &matMix, &GetViewMatrix(), &GetProjMatrix() );
	D3DXVec3TransformCoord( &q, (D3DXVECTOR3*)&p, &matMix );

	*x = (float)nScreenWidth / 2.f + q.x * (float)nScreenWidth / 2.f;
	*y = (float)nScreenHeight / 2.f - q.y * (float)nScreenHeight / 2.f;
// 	if( q.z < 0 || q.z > 1 )
// 		return false;

	const flt32 error_limit = 0.01f;
	if(q.z < -error_limit || q.z > 1.0f + error_limit)
	{
		//ASSERT(false);

		return false;
	}

	return true;
}