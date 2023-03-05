/*******************************************************************************
*  Copyright ZNWL (C) 2007 - All Rights Reserved
*
* File: 	EditCamera.h
* Date: 	01/18/2007
* Desc:
*
*******************************************************************************/
#ifndef _NDL_CAMERA_H__
#define _NDL_CAMERA_H__

#include "EditRender/SwCamera.h"
//#include "PtInput/PtInput.h"
#define WORLD_CULL	(266.66f*0.6f)	// Ö±¾¶

////////////////////////////////////////////////////////////////////////////////
class CWorld;
class CNdlCavas;
class NiPlane2d;
//struct SPtInputMessage;
////////////////////////////////////////////////////////////////////////////////
class CEditCamera	: public SwCamera
{
public:
						CEditCamera();
						~CEditCamera();

	virtual bool		Create();
	void				SetProjectionMatrix(CView* pView);
	virtual void		Update( flt32 totalTime, flt32 deltaTime );
	
	bool				Clone( CEditCamera* camera );
	

	
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


#endif	// _NDL_WORLDCAMERA_H__

