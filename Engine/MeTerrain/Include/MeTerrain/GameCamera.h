/*******************************************************************************
* Copyright ShenWang 2008 - All Rights Reserved
* 
* File: 	GameCamera.h
* Create: 	10/09/06
* Desc:		��Ϸ�����Ϊ����Editor����������Ϸ���ģʽ������Public��ʵ��GameCamera��
* Author:	Qiu Li
*
* Modify:
* Modify by:
*******************************************************************************/
#ifndef __GAMECAMERA_H__
#define __GAMECAMERA_H__

#include "SwCamera.h"
//struct SPtInputMessage;

extern float CAMERA_MIN_DISTANCE;	// ������˵���С����
extern float CAMERA_MAX_DISTANCE;	// ������˵�������
extern float CAMERA_DEFAULT_DISTANCE;	// ������˵�Ĭ�Ͼ��룬�Ӵ˾��뵽��С���룬����Ƕ����Բ�ֵ

class GameCamera : public SwCamera
{
public:
	GameCamera(void);
	virtual			~GameCamera(void);

	virtual bool		Create();
	virtual void		Destroy();
	virtual void		Update( float fTotalTime, float fDeltaTime );

	// ��ֱ�Ӹ�Editorʹ�ã�ProcessMouse������Ҳ�������湦��
	void				OnMouseScroll(int nMouseZ);					// nMouseZ > 0 �Ϲ��� < 0 �¹�
	//void				OnMouseMoveRBDown(int nOffsetX, int nOffsetY);	// �Ҽ�����ʱ����ƶ�
	bool				IsRotChange();

	const Vector&		GetLookAtPos();

	const Vector&		GetSphericalPos() { return m_ptSphericalPos; }
	void				SetSphericalY(float fRotZ);					// �������������ת����
	void				ClearDirtyFlag() {bCameraDirty = false;}
	void				UpdateCameraMoveSpeed(float fRoleMoveSpeed); // ���������ƶ��ٶȸ�������ƶ��ٶ�

	void				ForceCameraToDestLookAtPos(float x, float y, float z);		// ǿ�ư�������ø���λ��

	void				ClearCameraRotFlag() {m_bCameraSetRot = false;};

protected:
	Vector			SphericalToCartesian(Vector kSpherical);		// ��������ת���ɵѿ�������
public:
#ifdef WORLD_EDIT
	void			SetProjectionMatrix(CView* pView);
#endif
    void            SetLookAt(Vector& LookAt);
    void            CaluEyeAndLookat( D3DXVECTOR3 &vEye,D3DXVECTOR3 &vLookat );
protected:
    Vector          m_LookAt;
protected:
	/* 
	������������귽������
	m_ptSphericalPos.x: ������˵ľ��루��m_fDistance��x = sqrt(Distance.x*Distance.x + Distance.y*Distance.y + Distance.z*Distance.z)
	m_ptSphericalPos.y: ��ʱ����Z�����ת�Ƕȣ������ȣ�y = arctan(Distance.y/Distance.x)
	m_ptSphericalPos.z: ��XYƽ��нǵ��з�����ת�Ƕȣ���γ�ȣ�z = arcos(Distance.z / x) - PI * 0.5;
	*/
	Vector			m_ptSphericalPos;

	Vector			m_ptCurLookAtPos;	// ��ǰ�۲��Ŀ���
	Vector			m_ptDestLookAtPos;	// ���չ۲��Ŀ���

	Vector			m_ptCameraIdealPos;	// �������λ�ã�������������ײʱ��λ��

	float				m_fRotateSpeed;		// ��ת�ٶ�

	int					m_nMouseRB_PosX;	// ����Ҽ����º󣬱������ˮƽ�������꣬������������ת

	bool				bCameraDirty;		// �Ƿ�Ҫ�������
	bool				bCameraRotChange;	// ���������ת�Ƕȸı�
	bool				m_bCameraSetRot;	// ÿֻ֡����һ�ΰ�����ת��Ϣ�������Ϸ��ʼ����һ֡��δ�����ת��Ϣ
	bool				m_bForceUpdate;		// �����Ƿ�����Ŀ�����壬���������
};

#endif //__GAMECAMERA_H__