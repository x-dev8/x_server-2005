#include "StdAfx.h"
#include "MexViewerCamera.h"

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

MexViewerCamera::MexViewerCamera()
{
	m_ptCameraPos		= Vector::ZERO;
	m_ptCameraRot		= Vector::ZERO;
	m_scl		= 1.0f;


	m_ptCameraUp		= Vector(0.f, 0.f, 1.f);	// Z axis

	m_bNeedUpdateViewMatrix = true;

}

MexViewerCamera::~MexViewerCamera()
{
}

bool MexViewerCamera::CreateDefault()
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
	m_ptCameraRot = Vector(-1, 0, PI);

	m_bNeedUpdate = true;
	Update( 0.0f, 0.0f );

	return true;
}


bool MexViewerCamera::Clone( MexViewerCamera* camera )
{

	return true;
}


bool MexViewerCamera::ScreenToWorldRay( const Vector2& scrPos, Vector& worldPos, Vector& worldDir )
{
	return true;
}

void MexViewerCamera::Update( flt32 totalTime, flt32 deltaTime )
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

void MexViewerCamera::SetPos( const Vector& pos )
{
	m_ptCameraPos.x		= pos.x;
	m_ptCameraPos.y		= pos.y;
	m_ptCameraPos.z		= pos.z;

	m_bNeedUpdate		= true;
}

void MexViewerCamera::SetRot( const Vector& rot )
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

	m_bNeedUpdate		= true;
}


const flt32& MexViewerCamera::GetScl() const
{
	return m_scl;
}

void MexViewerCamera::SetScl( const flt32& scl )
{
	m_scl		= scl;
}

bool MexViewerCamera::Create()
{
	return CreateDefault();
}

void MexViewerCamera::SetProjectionMatrix(int w, int h)
{
	float fFarPlane = 10000.0f;
	float aspect = w / (float) h;
	D3DXMatrixPerspectiveFovRH( &m_matProj, D3DXToRadian(45), aspect, 0.1f, fFarPlane );
}