
#include "Me3d/Include.h"
#include "Me3d/Camera.h"
#include "FuncPerformanceLog.h"

extern long VIEWPORT_WIDTH;
extern long VIEWPORT_HEIGHT;


MeCamera::MeCamera()
:m_vIdealSpherical(0, 0, 0)
,m_fCameraRotAngle(0.0)
{
	guardfunc;
	unguard;
}

MeCamera::~MeCamera()
{
	guardfunc;
	unguard;
}

bool MeCamera::Create()
{
	guardfunc;
	return true;
	unguard;
}

void MeCamera::Destroy()
{
}

void MeCamera::MoveForward( float fDist )
{
	guardfunc;
	D3DXVECTOR3 vEyePt = GetEyePt()+GetViewDir()*fDist;
	D3DXVECTOR3 vLookatPt = vEyePt+GetViewDir();
	D3DXVECTOR3 vWorldUp = D3DXVECTOR3( 0, 0, 1.0 );
	
	SetViewParams( vEyePt, vLookatPt, vWorldUp );
	unguard;
}

void MeCamera::MoveRight( float fDist )
{
	guardfunc;
	D3DXVECTOR3 vEyePt = GetEyePt()+GetCross()*fDist;
	D3DXVECTOR3 vLookatPt = vEyePt+GetViewDir();
	D3DXVECTOR3 vWorldUp = D3DXVECTOR3( 0, 0, 1.0 );
	
	SetViewParams( vEyePt, vLookatPt, vWorldUp );
	unguard;
}

void MeCamera::MoveUp( float fDist )
{
	guardfunc;
	D3DXVECTOR3 vEyePt = GetEyePt()+GetUpVec()*fDist;
	D3DXVECTOR3 vLookatPt = vEyePt+GetViewDir();
	D3DXVECTOR3 vWorldUp = D3DXVECTOR3( 0, 0, 1.0 );

	SetViewParams( vEyePt, vLookatPt, vWorldUp );
	unguard;
}

void MeCamera::RotateY( float fPitch )
{
	guardfunc;
	D3DXVECTOR3 vUp = GetUpVec();
	D3DXVECTOR3 vDir = GetViewDir();
	D3DXMATRIX matrix;
	D3DXMatrixRotationAxis( &matrix, &vUp, fPitch );
	D3DXVec3TransformCoord( &vDir, &vDir, &matrix );

	
	D3DXVECTOR3 vEyePt = GetEyePt();
	D3DXVECTOR3 vLookatPt = vEyePt+vDir;
	D3DXVECTOR3 vWorldUp = D3DXVECTOR3( 0, 0, 1 );
	SetViewParams( vEyePt, vLookatPt, vWorldUp );
	unguard;
}

void MeCamera::BuildPickRay( int x, int y, D3DXVECTOR3& vPickRayOrig, D3DXVECTOR3& vPickRayDir, int nScreenWidth, int nScreenHeight )
{
	guardfunc;
	// Compute the vector of the pick ray in screen space
	D3DXMATRIX matView = GetViewMatrix();
	D3DXMATRIX matProj = GetProjMatrix();
	D3DXVECTOR3 v;
	v.x =  ( ( ( 2.0f * x ) / nScreenWidth  ) - 1 ) / matProj._11;
	v.y = -( ( ( 2.0f * y ) / nScreenHeight ) - 1 ) / matProj._22;
	v.z = -1.0f;

	// width/2+(p.x*proj._11)/2 = x; ===>
	// p.x = ( ( 2*x )/width-1 )/proj._11;

	// Get the inverse view matrix
	D3DXMATRIX m;
	D3DXMatrixInverse( &m, NULL, &matView );

	// Transform the screen space pick ray into 3D space
	vPickRayDir.x  = v.x*m._11 + v.y*m._21 + v.z*m._31;
	vPickRayDir.y  = v.x*m._12 + v.y*m._22 + v.z*m._32;
	vPickRayDir.z  = v.x*m._13 + v.y*m._23 + v.z*m._33;
	vPickRayOrig.x = m._41;
	vPickRayOrig.y = m._42;
	vPickRayOrig.z = m._43;

	D3DXVec3Normalize( &vPickRayDir, &vPickRayDir );
	unguard;
}

D3DXMATRIX MeCamera::GetViewXProj()
{
	guardfunc;
	D3DXMATRIX matMix;
	D3DXMatrixMultiply( &matMix, &GetViewMatrix(), &GetProjMatrix() );
	//D3DXMatrixMultiply( &matMix,&GetProjMatrix(), &GetViewMatrix() );
	return matMix;
	unguard;
}

D3DXMATRIX MeCamera::GetProjXView()
{
	guardfunc;
	D3DXMATRIX matMix;
	//D3DXMatrixMultiply( &matMix, &GetViewMatrix(), &GetProjMatrix() );
	D3DXMatrixMultiply( &matMix,&GetProjMatrix(), &GetViewMatrix() );
	return matMix;
	unguard;
}

bool MeCamera::WorldToScreen( const Vector& p, int *x, int *y, int nScreenWidth, int nScreenHeight )
{
	guardfunc;
	D3DXVECTOR3 q;
	D3DXMATRIX matMix;
	D3DXMatrixMultiply( &matMix, &GetViewMatrix(), &GetProjMatrix() );
	D3DXVec3TransformCoord( &q, (D3DXVECTOR3*)&p, &matMix );
	
	*x = nScreenWidth/2+q.x*nScreenWidth/2;
	*y = nScreenHeight/2-q.y*nScreenHeight/2;
	if( q.z < 0 || q.z > 1 )
		return false;
	return true;
	unguard;
}

bool MeCamera::WorldToScreen( const Vector& p, float *x, float *y, int nScreenWidth, int nScreenHeight )
{
	guardfunc;
	static const int s_cnMaxTransformedValue = 1000000;
	if( p.x > s_cnMaxTransformedValue || p.x < -s_cnMaxTransformedValue ||
		p.y > s_cnMaxTransformedValue || p.y < -s_cnMaxTransformedValue ||
		p.z > s_cnMaxTransformedValue || p.z < -s_cnMaxTransformedValue )
	{
		assert( 0 && "WorldToScreen Error!" );
		return false;
	}
		
	D3DXVECTOR3 q;
	D3DXMATRIX matMix;
	D3DXMatrixMultiply( &matMix, &GetViewMatrix(), &GetProjMatrix() );
	D3DXVec3TransformCoord( &q, (D3DXVECTOR3*)&p, &matMix );

	*x = (float)nScreenWidth / 2.f + q.x * (float)nScreenWidth / 2.f;
	*y = (float)nScreenHeight / 2.f - q.y * (float)nScreenHeight / 2.f;
	if( q.z < 0 || q.z > 1 )
		return false;
	return true;
	unguard;
}

void MeCamera::Update( float fTime )
{
	guardfunc;
	if( m_vIdealSpherical == D3DXVECTOR3(0,0,0) )
	{
		m_vIdealSpherical = m_vTargetPos;
		m_vPos = m_vTargetPos;
	}
//	m_vIdealSpherical.y = atan2f( m_vPos.y - m_vTargetPos.y, m_vPos.x - m_vTargetPos.y );
	//m_vTargetPos = m_vPos - vPos;
	m_vIdealSpherical.x = m_vPos.x;
	m_vIdealSpherical.y = m_vPos.y;

	if( abs( m_vPos.z )  - m_vTargetPos.z  < 0.0f )
	{	
		m_vIdealSpherical.z = m_vIdealSpherical.z-0.001f;
		if( m_vIdealSpherical.z < m_vTargetPos.z )
		{
			m_vIdealSpherical = m_vPos = m_vTargetPos;
		}
	}
	else
	{
		m_vIdealSpherical.z = m_vIdealSpherical.z+0.001f;
		if( m_vIdealSpherical.z > m_vTargetPos.z  )
		{
			m_vIdealSpherical = m_vPos = m_vTargetPos;
		}
	}

	//m_vIdealSpherical.z = m_vPos.z + 0.001f;
	//if( m_vTargetPos.z < m_vIdealSpherical.z )
	//{
	//	m_vPos = m_vTargetPos;
	//	m_vIdealSpherical = m_vTargetPos;
	//	return;
	//}
	unguard;	
}

D3DXMATRIX  MeCamera::GetStandboardMatrix()
{
	guardfunc;
	D3DXMATRIX mat;
	D3DXVECTOR3 eye = GetEyePt();
	eye.z = 0;
	D3DXVECTOR3 d = GetViewDir();
	d.z = 0;
	D3DXVECTOR3 up( 0, 0, 1 );
	D3DXVECTOR3 lookat = eye+d;
	D3DXMatrixLookAtLH( &mat, &eye, &lookat, &up );
	D3DXMatrixInverse( &mat, NULL, &mat );
	mat._41 = 0.0f;
	mat._42 = 0.0f;
	mat._43 = 0.0f;
	return mat;
	unguard;
}


MouseCtrl::MouseCtrl()
{
	guardfunc;
	m_state = IDLE;
	m_pCamera = NULL;
	m_fRoll = 0;
	m_fPitch = 0;
	m_fYaw = 0;
	
	m_miLB.msLastState = MS_NONE;
	m_miLB.msState = MS_NONE;
	m_miLB.dwLastUpdateTime = 0;

	m_bUseCtrlKeyRotate = FALSE;
	unguard;
}

UINT MouseCtrl::OnMessage( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	guardfunc;
	switch( uMsg )
	{
	case WM_MOUSEMOVE:
		GetCursorPos( &m_ptMouse );
		ScreenToClient( hWnd, &m_ptMouse );
		switch( m_state )
		{
		case HORIZON_MOVE_CAMERA:
			{
				D3DXVECTOR3 eye = m_pCamera->GetEyePt();
				D3DXVECTOR3 dir = m_pCamera->GetViewDir();
				D3DXVECTOR3 right = m_pCamera->GetCross();
				
				eye += ( m_ptMouse.x-m_ptMouseDragStart.x )*1.0f*right+( m_ptMouse.y-m_ptMouseDragStart.y )*1.5f*dir;
				m_pCamera->SetViewParams( eye, eye+dir, D3DXVECTOR3( 0, 0, 1 ) );
				m_ptMouseDragStart = m_ptMouse;
			}
			break;
		case VERTICLE_MOVE_CAMERA:
			{
				D3DXVECTOR3 eye = m_pCamera->GetEyePt();
				D3DXVECTOR3 dir = m_pCamera->GetViewDir();
				
				eye += ( m_ptMouse.y-m_ptMouseDragStart.y )*1.0f*D3DXVECTOR3( 0, 0, 1 );
				m_pCamera->SetViewParams( eye, eye+dir, D3DXVECTOR3( 0, 0, 1 ) );
				m_ptMouseDragStart = m_ptMouse;
			}
			break;
		case ROTATE_CAMERA:
			{
				//D3DXVECTOR3 vFromPt = m_pCamera->GetEyePt();
				D3DXVECTOR3 vUpVec( 0, 0, 1 );
				
				
				m_fRoll += -( m_ptMouse.y-m_ptMouseDragStart.y )*0.5f*3.1415626f/180; 
				
				D3DXMATRIX matRotX;
				D3DXMatrixRotationX( &matRotX, -m_fRoll );	
				D3DXVec3TransformCoord( (D3DXVECTOR3*)&vUpVec, (D3DXVECTOR3*)&vUpVec, &matRotX );
				
				
				//float radius = D3DXVec3Length( (D3DXVECTOR3*)&vFromPt );
				//D3DXVECTOR3 vLookAt = vFromPt+radius*m_pCamera->GetViewDir();
				
				D3DXVECTOR3 vDir( 0.0f, -1.0f, 0.0f );
				
				m_fYaw += ( m_ptMouse.x-m_ptMouseDragStart.x )*0.5f*3.1415626f/180;
				
				D3DXMATRIX matRotZ;
				D3DXMatrixRotationZ( &matRotZ, m_fYaw );	
				D3DXVec3TransformCoord( (D3DXVECTOR3*)&vDir, (D3DXVECTOR3*)&vDir, &matRotX );
				D3DXVec3TransformCoord( (D3DXVECTOR3*)&vDir, (D3DXVECTOR3*)&vDir, &matRotZ );
				
				//vFromPt = vLookAt-radius*vDir;
				D3DXVECTOR3 vFromPt = m_vRotateCamLock-m_fRotateRadius*vDir;
				
				m_pCamera->SetViewParams( vFromPt, m_vRotateCamLock, vUpVec );
				
				m_ptMouseDragStart = m_ptMouse;
			}
			break;
		}
		break;
	case WM_LBUTTONUP:
		m_miLB.CopyState();
		m_miLB.msState = MS_UP;
		m_state = IDLE;
		ReleaseCapture();
		return WM_LBUTTONUP;
		break;
	case WM_RBUTTONUP:
		m_state = IDLE;
		ReleaseCapture();
		break;
	case WM_MBUTTONUP:
		m_state = IDLE;
		ReleaseCapture();
		break;
	case WM_LBUTTONDOWN:
		{

			m_miLB.CopyState();
			m_miLB.msState = MS_DOWN;

			D3DXVECTOR3 vEye = m_pCamera->GetEyePt();
			D3DXVECTOR3 vDir = m_pCamera->GetViewDir();

			float t = -vEye.z/vDir.z;
			
			switch( m_state )
			{
			case IDLE:
				if( IsUseCtrlKeyRotate() )
				{
					if( ( GetAsyncKeyState(VK_LCONTROL) & 0x8000 ) == 0x8000 ||
						( GetAsyncKeyState(VK_RCONTROL) & 0x8000 ) == 0x8000 ) 
					{
						m_state = ROTATE_CAMERA;
						m_ptMouseDragStart = m_ptMouse;
						SetCapture(hWnd);
						//m_vRotateCamLock = vEye+t*vDir;
						m_vRotateCamLock = D3DXVECTOR3(0,0,0);
						m_fRotateRadius = t;
					}
				}
				else
				{
					m_state = ROTATE_CAMERA;
					m_ptMouseDragStart = m_ptMouse;
					SetCapture(hWnd);
					//m_vRotateCamLock = vEye+t*vDir;
					m_vRotateCamLock = D3DXVECTOR3(0,0,0);
					m_fRotateRadius = t;

				}
				break;
			}
		}
		break;
	case WM_RBUTTONDOWN:
		switch( m_state )
		{
		case IDLE:
			SetCapture(hWnd);
			m_state = HORIZON_MOVE_CAMERA;
			m_ptMouseDragStart = m_ptMouse;
			break;
		}
	case WM_MBUTTONDOWN:
		switch( m_state )
		{
		case IDLE:
			SetCapture(hWnd);
			m_state = VERTICLE_MOVE_CAMERA;
			m_ptMouseDragStart = m_ptMouse;
			break;
		}
		break;
	}
	return 0;
	unguard;
}

void MeCamera::SetViewMatrix( const D3DXMATRIX& pViewMatrix )
{
	guardfunc;
	memcpy( &m_matView, pViewMatrix, sizeof( float )*16 );
	D3DXMatrixInverse( &m_matBillboard, NULL, &m_matView );
	m_matBillboard._41 = 0.0f;
	m_matBillboard._42 = 0.0f;
	m_matBillboard._43 = 0.0f;
	unguard;
}
void MeCamera::SetProjMatrix( const D3DXMATRIX& pProjMatrix )
{
	guardfunc;
	memcpy( &m_matProj, pProjMatrix, sizeof( float )*16 );
	unguard;
}

void MeCamera::SetViewMatrix( MeMatrix* pViewMatrix )
{
	guardfunc;
	memcpy( &m_matView, pViewMatrix, sizeof( float )*16 );
	D3DXMatrixInverse( &m_matBillboard, NULL, &m_matView );
	m_matBillboard._41 = 0.0f;
	m_matBillboard._42 = 0.0f;
	m_matBillboard._43 = 0.0f;
	unguard;

}
void MeCamera::SetProjMatrix( MeMatrix* pProjMatrix )
{
	guardfunc;
	memcpy( &m_matProj, pProjMatrix, sizeof( float )*16 );
	unguard;
}
