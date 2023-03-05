#pragma once
#include "d3dutil.h"
#include "Me3d.h"
class Vector;
class MeCamera:public CD3DCamera, public MeCommonAllocObj<MeCamera>
{
public:
	MeCamera();
	virtual ~MeCamera();

	bool Create();
	void Destroy();

	void MoveForward( float fDist );	// z
	void MoveUp( float fDist );			// y
	void MoveRight( float fDist );		// x

	void RotateX( float fRoll);
	void RotateY( float fPitch );
	void RotateZ( float fYaw );
	void RotateAxis( const Vector& vAxis, float fAngle );

	void BuildPickRay( int x, int y, D3DXVECTOR3& vPickRayOrig, D3DXVECTOR3& vPickRayDir, int nScreenWidth, int nScreenHeight );
	bool WorldToScreen( const Vector& p, int *x, int *y, int nScreenWidth, int nScreenHeight );
	bool WorldToScreen( const Vector& p, float *x, float *y, int nScreenWidth, int nScreenHeight );
	D3DXMATRIX GetViewXProj();
	D3DXMATRIX GetProjXView();
	D3DXMATRIX GetStandboardMatrix();
	float GetFOV(){return m_fFOV;}


	void Update( float fTime );

	//   added 2004.06.25
	void SetViewMatrix( MeMatrix* pViewMatrix );
	void SetProjMatrix( MeMatrix* pProjMatrix );

	void SetProjMatrix(const D3DXMATRIX& pProjMatrix );
	void SetViewMatrix(const D3DXMATRIX& pViewMatrix );

	
	D3DXVECTOR3* GetTargetPos( void )				{	return &m_vTargetPos;}
	D3DXVECTOR3* GetPos( void )						{	return &m_vPos;	}
	void		 SetPos( D3DXVECTOR3& p )			{	m_vPos = p;		}
	void		 SetTargetPos( D3DXVECTOR3& p )		{	m_vTargetPos = p;}
	D3DXVECTOR3* GetIdealSphericalPos()				{	return &m_vIdealSpherical; }
	
	/*add by yanli 2010-6-30*/
	//-----------------------------------------------------------------------
	float		 GetRot( void )						{	return m_fCameraRotAngle;	}
	void		 SetRot( float _fAngle )			{	m_fCameraRotAngle = _fAngle;	}
	//-----------------------------------------------------------------------

//	void		 SetTargetPos( D3DXVECTOR3& p )		{	m_vTargetPos = p;	}

protected:
	float				m_fCameraRotAngle;   // add by yanli 2010-6-30
	D3DXVECTOR3	m_vPos;			//当前点
	D3DXVECTOR3	m_vVelocity;	//摄像机速度
	D3DXVECTOR3	m_vTargetPos;	//目标点
	D3DXVECTOR3	m_vIdealSpherical;//理想球坐标
};
class MouseCtrl
{
public:
	enum STATE
	{
		IDLE,
		ROTATE_CAMERA,
		HORIZON_MOVE_CAMERA,
		VERTICLE_MOVE_CAMERA,
		ROTATE_ROUND_MODEL_CAMERA,
	};
	enum MS_State
	{
		MS_NONE,
		MS_DOWN,
		MS_DRAG,
		MS_UP,
	};
	struct MSInfo
	{
		MS_State	msLastState;
		MS_State	msState;
		DWORD		dwLastUpdateTime;

		BOOL		IsDown(){ return msState == MS_DOWN; }
		BOOL		IsUp(){ return msState == MS_UP; }

		void		CopyState(){ msLastState = msState; }
	};
public:
	MouseCtrl();
	void			SetCamera( MeCamera* camera ){ m_pCamera = camera; }
	virtual UINT	OnMessage( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
	POINT			GetMousePt(){ return m_ptMouse; }
	
	BOOL			IsLBUp(){ return m_miLB.IsUp(); }
	BOOL			IsLBDown(){ return m_miLB.IsDown(); }
	void			UseCtrlKeyRotate( BOOL b ){ m_bUseCtrlKeyRotate = b; }
	BOOL			IsUseCtrlKeyRotate(){ return m_bUseCtrlKeyRotate; }
protected:
	STATE			m_state;
	MeCamera* 	m_pCamera;
	POINT			m_ptMouse;
	POINT			m_ptMouseDragStart;
	float			m_fRoll;
	float			m_fPitch;
	float			m_fYaw;
	D3DXVECTOR3		m_vRotateCamLock;
	float			m_fRotateRadius;

	MSInfo			m_miLB;
	BOOL			m_bUseCtrlKeyRotate;
};
