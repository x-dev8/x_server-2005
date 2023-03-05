#ifndef CHASECAMERA_H_
#define CHASECAMERA_H_

#include "EditRender/SwCamera.h"

class ChaseCamera : public SwCamera
{
public:
	ChaseCamera();
	~ChaseCamera();

	virtual bool		Create();
	virtual void		Update( flt32 totalTime, flt32 deltaTime );

	void				SetProjectionMatrix(CView* pView);

	void				SetLookAt( const D3DXVECTOR3& lookat ){ m_vLookAt = lookat; }
	void				SetEyePos( const D3DXVECTOR3& pos ){ m_vEye = pos; }
	void				SetUpVector( const D3DXVECTOR3& up );

protected:
	D3DXVECTOR3 m_vLookAt;

};


#endif