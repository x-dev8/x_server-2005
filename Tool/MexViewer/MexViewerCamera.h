#pragma once

class SwCamera
{
public:
	SwCamera(void);
	virtual			~SwCamera(void);

	virtual bool		Create();
	virtual void		Destroy();
	virtual void		Update( float fTotalTime, float fDeltaTime );


	// Get			
	const Vector&		GetPos() const;			
	Vector&			GetPos();			
	const Vector&		GetRot() const;			
	Vector&			GetRot();			

	virtual	void		SetPos(const Vector& pos );
	virtual void		SetRot(const Vector& rot );

	D3DXMATRIX& GetViewMatrix(){return m_matView;};
	const D3DXMATRIX& GetProjMatrix(){return m_matProj;};

	void CaluEyeAndLookat( D3DXVECTOR3 &vEye,D3DXVECTOR3 &vLookat );
	bool IsNeedUpdateViewMatrix(void){ bool ret = m_bNeedUpdateViewMatrix; m_bNeedUpdateViewMatrix = false; return ret;}
	FrustumEx&  GetFrustum(){ return m_frustum; }
	const D3DXVECTOR3&  GetEye(){ return m_vEye; }
	const D3DXVECTOR3&	GetLookAt(void){ m_vLookAt = m_vEye+m_vDir; return m_vLookAt; }
	const D3DXVECTOR3&  GetDir(){ return m_vDir; }
	const D3DXVECTOR3&	GetRight(){ return m_vCross;}

	//added by zilong. 2011-01-20---------------------
	bool WorldToScreen( const Vector& p, int *x, int *y, int nScreenWidth, int nScreenHeight );
	bool WorldToScreen( const Vector& p, float *x, float *y, int nScreenWidth, int nScreenHeight );
	//------------------------------------------------

protected:
	Vector		m_ptCameraPos;		// 当前帧相机位置
	Vector		m_ptCameraRot;		// 当前帧相机旋转
	Vector		m_ptCameraUp;

	D3DXMATRIX		m_matView;
	D3DXMATRIX		m_matProj;

	D3DXVECTOR3		m_vEye,m_vDir,m_vCross, m_vLookAt;
	bool			m_bNeedUpdateViewMatrix;

	FrustumEx		m_frustum;

};

class MexViewerCamera	: public SwCamera
{
public:
	MexViewerCamera();
	~MexViewerCamera();

	virtual bool		Create();
	void				SetProjectionMatrix(int w, int h);
	virtual void		Update( flt32 totalTime, flt32 deltaTime );

	bool				Clone( MexViewerCamera* camera );



	bool				ScreenToWorldRay( const Vector2& scrPos, Vector& worldPos, Vector& worldDir );
	// Get			
	const flt32&		GetScl() const;			

	virtual void		SetPos( const Vector& pos );
	virtual	void		SetRot( const Vector& rot );
	void		SetScl( const flt32	& scl );

private:
	//NiMatrix3			m_cameraToWorld;

	bool				CreateDefault();

	bool				m_bNeedUpdate;


protected:
	flt32				m_scl;
};