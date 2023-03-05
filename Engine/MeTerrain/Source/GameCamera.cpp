/*******************************************************************************
* Copyright ShenWang 2008 - All Rights Reserved
* 
* File: 	GameCamera.cpp
* Create: 	10/09/06
* Desc:		游戏相机，为方便Editor可以运行游戏相机模式，放在Public里实现GameCamera类
* Author:	Qiu Li
*
* Modify:
* Modify by:
*******************************************************************************/
#include "stdafx.h"
#include "GameCamera.h"
//#include "PtInput/PtInput.h"

#include "Public/swLuaScript.h"

const float CAMERA_LOOK_AT_Z_OFFSET	=	1.1f;			// 看向脚底向上1.2米处，人物1.6米
float CAMERA_MOVE_SPEED			=	7.8f;
float CAMERA_LOOK_DOWN_LIMIT	=	-0.25f * PI;	// 俯视的角度限制45°，弧度
float CAMERA_LOOK_UP_LIMIT		=	-0.125f * PI;	// 仰视的角度限制25°，弧度
float CAMERA_MIN_DISTANCE		=	3.5f;	// 相机到人的最小距离
float CAMERA_MAX_DISTANCE		=	25.0f;	// 相机到人的最大距离
float CAMERA_DEFAULT_DISTANCE	=	9.0f;	// 相机到人的默认距离，从此距离到最小距离，相机角度线性插值

GameCamera::GameCamera( void )
{
	// 初始化相机球坐标
	m_ptSphericalPos.x	= CAMERA_DEFAULT_DISTANCE;		// 相机与目标的默认距离
	m_ptSphericalPos.y	= 0;							// 经度
	m_ptSphericalPos.z	= CAMERA_LOOK_DOWN_LIMIT;		// 纬度， 45°角


	m_ptCameraPos		= Vector::ZERO;
	m_ptCameraIdealPos	= Vector::ZERO;
	m_ptCurLookAtPos	= Vector::ZERO;
	m_ptDestLookAtPos	= Vector::ZERO;

	m_nMouseRB_PosX		= 0;
	bCameraDirty		= false;
	bCameraRotChange	= false;
	m_bForceUpdate		= false;

    m_ptCameraPos		= Vector::ZERO;
    m_ptCameraRot		= Vector::ZERO;


    m_ptCameraUp		= Vector(0.f, 0.f, 1.f);	// Z axis

}

GameCamera::~GameCamera( void )
{
}

bool GameCamera::Create()
{
	if( !SwCamera::Create() )
		return false;

	bool bFindPath = false;
	// 读配置文件参数
	double lookup, lookdown, mindist, maxdist, defaultdist;
	if( SwGlobal::s_Lua->GetGlobalNumber("CAMERA_LOOK_UP_LIMIT", &lookup) )
		CAMERA_LOOK_UP_LIMIT = -lookup;
	if( SwGlobal::s_Lua->GetGlobalNumber("CAMERA_LOOK_DOWN_LIMIT", &lookdown) )
	{
		CAMERA_LOOK_DOWN_LIMIT = -lookdown;
		m_ptSphericalPos.z = CAMERA_LOOK_DOWN_LIMIT;
	}
	if( SwGlobal::s_Lua->GetGlobalNumber("CAMERA_MIN_DISTANCE", &mindist) )
		CAMERA_MIN_DISTANCE = mindist;
	if( SwGlobal::s_Lua->GetGlobalNumber("CAMERA_MAX_DISTANCE", &maxdist) )
		CAMERA_MAX_DISTANCE = maxdist;
	if( SwGlobal::s_Lua->GetGlobalNumber("CAMERA_DEFAULT_DISTANCE", &defaultdist) )
		CAMERA_DEFAULT_DISTANCE = defaultdist;

	double speed;
	if( SwGlobal::s_Lua->GetGlobalNumber("CHARACTOR_SPEED", &speed) && speed >= 0)
	{
		UpdateCameraMoveSpeed(speed);
	}

	double fRight;
	double fTop;
	bFindPath = (SwGlobal::s_Lua->GetGlobalNumber("CAMERA_FRUSTUM_RIGHT", &fRight)
					&& SwGlobal::s_Lua->GetGlobalNumber("CAMERA_FRUSTUM_TOP", &fTop));

	{
		m_fRotateSpeed	= 0.005f;
	}

    m_ptCameraPos = Vector::ZERO;
    m_ptCameraRot = Vector( -PI*0.4f/*-PI*0.5f*/, 0.f/*-PI*0.5f*/, PI/*0.0f*/ );

    Update( 0.0f, 0.0f );
	return true;
}

void GameCamera::Update( float fTotalTime, float fDeltaTime )
{
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

void GameCamera::Destroy()
{
	SwCamera::Destroy();
}

const Vector& GameCamera::GetLookAtPos()
{
	return m_ptCurLookAtPos;
}


// 根据球坐标计算笛卡尔坐标
Vector GameCamera::SphericalToCartesian(Vector kSpherical)
{
	Vector Position;
	float fAngle = kSpherical.z + PI * 0.5;

	Position.x = kSpherical.x * cos(kSpherical.y) * sin(fAngle);
	Position.y = kSpherical.x * sin(kSpherical.y) * sin(fAngle);
	Position.z = kSpherical.x * cos(fAngle);

	return Position;
}

void GameCamera::OnMouseScroll(int nMouseZ)
{
	float offset = nMouseZ * m_fRotateSpeed * 130;
	m_ptSphericalPos.x -= offset;

	if(m_ptSphericalPos.x > CAMERA_MAX_DISTANCE)
	{
		m_ptSphericalPos.x = CAMERA_MAX_DISTANCE;
	}
	else if(m_ptSphericalPos.x < CAMERA_MIN_DISTANCE)
	{
		m_ptSphericalPos.x = CAMERA_MIN_DISTANCE;
	}

	if( m_ptSphericalPos.x >= CAMERA_MIN_DISTANCE && m_ptSphericalPos.x <= CAMERA_DEFAULT_DISTANCE )
	{
		// 相机纬度线性插值
		m_ptSphericalPos.z = (CAMERA_LOOK_DOWN_LIMIT - CAMERA_LOOK_UP_LIMIT)*(m_ptSphericalPos.x - CAMERA_MIN_DISTANCE) / (CAMERA_DEFAULT_DISTANCE - CAMERA_MIN_DISTANCE) + CAMERA_LOOK_UP_LIMIT;
	}
	bCameraDirty = true;
}

// void GameCamera::OnMouseMoveRBDown(int nOffsetX, int nOffsetY)
// {
// 	float offset = nOffsetX * m_fRotateSpeed;
// 	m_ptSphericalPos.y -= offset;	// 更新球坐标的Y值，即相机逆时针绕Z轴的旋转角度
// 	while (m_ptSphericalPos.y > PI)
// 		m_ptSphericalPos.y -= PI * 2;
// 
// 	while (m_ptSphericalPos.y < -PI)
// 		m_ptSphericalPos.y += PI * 2;
// 	bCameraDirty = true;
// 	bCameraRotChange = true;
// }

void GameCamera::UpdateCameraMoveSpeed( float fRoleMoveSpeed )
{
	if( fRoleMoveSpeed > 0 )
		CAMERA_MOVE_SPEED = fRoleMoveSpeed + 2.8f;
}

bool GameCamera::IsRotChange()
{
	bool ret = bCameraRotChange;
	bCameraRotChange = false;
	return ret;
}

void GameCamera::ForceCameraToDestLookAtPos(float x, float y, float z)
{
	m_ptDestLookAtPos =  Vector(x, y, z);//m_pkFollowNode->GetTranslate();
	m_ptDestLookAtPos.z	+= CAMERA_LOOK_AT_Z_OFFSET;
	m_ptCurLookAtPos = m_ptDestLookAtPos;
	bCameraDirty = true;
	m_bForceUpdate = true;

	//Trace("Force MeCamera to %.3f, %.3f\n", m_ptCurLookAtPos.x, m_ptCurLookAtPos.y);
}

void GameCamera::SetSphericalY( float fRotZ )
{
	m_ptSphericalPos.y	= fRotZ - PI * 0.5;
	while (m_ptSphericalPos.y > PI)
		m_ptSphericalPos.y -= PI * 2;

	while (m_ptSphericalPos.y < -PI)
		m_ptSphericalPos.y += PI * 2;
	//Trace("SetSphericalY %.3f\n", fRotZ);

	bCameraDirty = true;
	bCameraRotChange = true;
}

#ifdef WORLD_EDIT
void GameCamera::SetProjectionMatrix(CView* pView)
{
    float fFarPlane = CULL_DISTANCE/*MAX_RAYCAST_DISTANCE*/;
    RECT rect;
    pView->GetClientRect( &rect );
    float aspect = (rect.right - rect.left)/(float)(rect.bottom - rect.top);
    D3DXMatrixPerspectiveFovRH( &m_matProj, D3DX_PI/4.f, aspect, 0.1f, fFarPlane );
}
#endif
void GameCamera::SetLookAt(Vector& LookAt)
{
    m_LookAt.x = LookAt.x;
    m_LookAt.y = LookAt.y;
    m_LookAt.z = LookAt.z;
}


void GameCamera::CaluEyeAndLookat( D3DXVECTOR3 &vEye,D3DXVECTOR3 &vLookat )
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

    vLookat.x = m_LookAt.x;
    vLookat.y = m_LookAt.y;
    vLookat.z = m_LookAt.z;
 
    m_ptCameraPos.x = vLookat.x + vDist.x * 30;
    m_ptCameraPos.y = vLookat.y + vDist.y * 30;
    m_ptCameraPos.z = vLookat.z + vDist.z * 30;

//     m_ptCameraPos.x = m_LookAt.x;
//     m_ptCameraPos.y = m_LookAt.y;
//     m_ptCameraPos.z = m_LookAt.z;
// 
    vEye.x = m_ptCameraPos.x;
    vEye.y = m_ptCameraPos.y;
    vEye.z = m_ptCameraPos.z;
//     vLookat= vEye - vDist*MAX_RAYCAST_DISTANCE;
}