/*******************************************************************************
* Copyright ShenWang 2008 - All Rights Reserved
* 
* File: 	SwCamera.h
* Create: 	10/09/06
* Desc:		MeCamera基类
* Author:	Qiu Li
*
* Modify:
* Modify by:
*******************************************************************************/
#ifndef __SWCAMERA_H__
#define __SWCAMERA_H__

////////////////////////////////////////////////////////////////////////////////
class CNdlWorldPickerBase;
//struct SPtInputMessage;
class FrustumEx;

const float CAMERA_FAR = 600.f;

////////////////////////////////////////////////////////////////////////////////
class SwCamera /* : public NiMemObject*/
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
// typedef NiPointer<SwCamera> SwCameraPtr;

#endif