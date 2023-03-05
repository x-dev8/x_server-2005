/*******************************************************************************
* Copyright ShenWang 2008 - All Rights Reserved
* 
* File: 	GameCamera.h
* Create: 	10/09/06
* Desc:		游戏相机，为方便Editor可以运行游戏相机模式，放在Public里实现GameCamera类
* Author:	Qiu Li
*
* Modify:
* Modify by:
*******************************************************************************/
#ifndef __GAMECAMERA_H__
#define __GAMECAMERA_H__

#include "SwCamera.h"
//struct SPtInputMessage;

extern float CAMERA_MIN_DISTANCE;	// 相机到人的最小距离
extern float CAMERA_MAX_DISTANCE;	// 相机到人的最大距离
extern float CAMERA_DEFAULT_DISTANCE;	// 相机到人的默认距离，从此距离到最小距离，相机角度线性插值

class GameCamera : public SwCamera
{
public:
	GameCamera(void);
	virtual			~GameCamera(void);

	virtual bool		Create();
	virtual void		Destroy();
	virtual void		Update( float fTotalTime, float fDeltaTime );

	// 可直接给Editor使用，ProcessMouse函数里也调用下面功能
	void				OnMouseScroll(int nMouseZ);					// nMouseZ > 0 上滚； < 0 下滚
	//void				OnMouseMoveRBDown(int nOffsetX, int nOffsetY);	// 右键按下时鼠标移动
	bool				IsRotChange();

	const Vector&		GetLookAtPos();

	const Vector&		GetSphericalPos() { return m_ptSphericalPos; }
	void				SetSphericalY(float fRotZ);					// 设置相机绕人旋转弧度
	void				ClearDirtyFlag() {bCameraDirty = false;}
	void				UpdateCameraMoveSpeed(float fRoleMoveSpeed); // 根据人物移动速度更新相机移动速度

	void				ForceCameraToDestLookAtPos(float x, float y, float z);		// 强制把相机设置给定位置

	void				ClearCameraRotFlag() {m_bCameraSetRot = false;};

protected:
	Vector			SphericalToCartesian(Vector kSpherical);		// 球面坐标转换成笛卡尔坐标
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
	相机采用球坐标方法计算
	m_ptSphericalPos.x: 相机到人的距离（即m_fDistance）x = sqrt(Distance.x*Distance.x + Distance.y*Distance.y + Distance.z*Distance.z)
	m_ptSphericalPos.y: 逆时针绕Z轴的旋转角度（即经度）y = arctan(Distance.y/Distance.x)
	m_ptSphericalPos.z: 与XY平面夹角的有符号旋转角度（即纬度）z = arcos(Distance.z / x) - PI * 0.5;
	*/
	Vector			m_ptSphericalPos;

	Vector			m_ptCurLookAtPos;	// 当前观察的目标点
	Vector			m_ptDestLookAtPos;	// 最终观察的目标点

	Vector			m_ptCameraIdealPos;	// 相机理想位置，如果与地形无碰撞时的位置

	float				m_fRotateSpeed;		// 旋转速度

	int					m_nMouseRB_PosX;	// 鼠标右键按下后，保存鼠标水平方向坐标，用于绕人物旋转

	bool				bCameraDirty;		// 是否要更新相机
	bool				bCameraRotChange;	// 相机绕人旋转角度改变
	bool				m_bCameraSetRot;	// 每帧只处理一次按键旋转消息，解决游戏初始化后，一帧多次传入旋转消息
	bool				m_bForceUpdate;		// 不管是否设置目标物体，都更新相机
};

#endif //__GAMECAMERA_H__