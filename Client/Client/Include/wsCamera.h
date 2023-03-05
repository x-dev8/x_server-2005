#pragma once
#include "Me3d\Include.h"

/////////////////////////////////////////////////
//该类对MeCamera进行封装对相机功能进行管理 
//负责相机的控制和碰撞功能
//MeCamera* m_pCamera;为观察摄像机

//相机与游戏逻辑粘连过多需要继续分离
/////////////////////////////////////////////////

static const float WSCAMERA_DISPLAY_ZOOMIN_LIMIT = 8.3286;
static const float WSCAMERA_45DEGREE_CAMERA_ROTATE_ZMIN	= -53.6248;

class TObjectInfo;
class wsCamera
{
public:
	wsCamera(void);
	virtual ~wsCamera(void);

	//更新
	void UpdateCamera();
	void ProcessCamera();

	MeCamera* GetMeCamera(){ return m_pCamera; }
	void SetMeCamera( MeCamera* pCamera ){ m_pCamera = pCamera; }

public:
	void Init2DCamera(void);
	void Init3DCamera(void);

	void zoomoutCamera();
	void zoominCamera();
	void moveleftCamera();
	void moverightCamera();
	void moveupCamera();
	void movedownCamera();

	void Set45DegreeCameraMode(BOOL bLock);
	void SetFollowCameraMode(BOOL bLock);
	void Set28Mode(BOOL bLock);

	void CorrectCameraRotateValue( float& fCameraRotateXCorrect, float fRotateXDistance );

	void Update45DegreeCameraRotate();

	bool GetAutoCamera(){ return m_bAutoCamera; }
	void SetAutoCamera( bool b ){ m_bAutoCamera = b; }

	void SetCameraRotateX( float fCameraRotateX ){ m_fCameraRotateX = fCameraRotateX; } 
	void SetCameraRotateZ( float fCameraRotateZ );

	float GetCameraRotateX(){ return m_fCameraRotateX; }
	float GetCameraRotateZ(){ return m_fCameraRotateZ; }

	void SetCameraRotateXCorrect( float fCameraRotateXCorrect ){ m_fCameraRotateXCorrect = fCameraRotateXCorrect; }
	float GetCameraRotateXCorrect(){ return m_fCameraRotateXCorrect;}

	void SetCameraRotateXSpeed( float fCameraRotateXSpeed ){ m_fCameraRotateXSpeed = fCameraRotateXSpeed; }
	void SetCameraRotateZSpeed( float fCameraRotateZSpeed ){ m_fCameraRotateZSpeed = fCameraRotateZSpeed; }

	float GetCameraRotateXSpeed(){ return m_fCameraRotateXSpeed; }
	float GetCameraRotateZSpeed(){ return m_fCameraRotateZSpeed; }

	void SetCameraRotateXBuf( float fCameraRotateXBuf ){ m_fCameraRotateXBuf = fCameraRotateXBuf; }
	void SetCameraRotateZBuf( float fCameraRotateZBuf ){ m_fCameraRotateZBuf = fCameraRotateZBuf; }
	float GetCameraRotateXBuf(){ return m_fCameraRotateXBuf; };
	float GetCameraRotateZBuf(){ return m_fCameraRotateZBuf; };

	void SetCameraSmoothParameter( float smooth ){ m_fCameraSmoothParameter = smooth; }
	float GetCameraSmoothParameter(){ return m_fCameraSmoothParameter; }

	void SetLookUpAngle( float angle ){ m_fLookUpAngle = angle; }
	float GetLookUpAngle(){ return m_fLookUpAngle; }

	void SetCurCameraZoom( float zoom ){ m_fCurCameraZoom = zoom; }
	float GetCurCameraZoom(){ return m_fCurCameraZoom; }

	void SetCameraDefaultZoomOutLimit( float limit ){ m_fCameraDefaultZoomOutLimit = limit; }
	float GetCameraDefaultZoomOutLimit(){ return m_fCameraDefaultZoomOutLimit; }

	void Set45DegreeDefaultCameraZoomOutLimit( float limit ){ m_f45DegreeDefaultZoomOutLimit = limit; }
	float Get45DegreeDefaultCameraZoomOutLimit(){ return m_f45DegreeDefaultZoomOutLimit; }

	void SetCameraZoomOutLimit( float limit ){ m_fCameraZoomOutLimit = limit; }
	float GetCameraZoomOutLimit(){ return m_fCameraZoomOutLimit; }

	void SetCameraZoomInLimit( float limit ){ m_fCameraZoomInLimit = limit; }
	float GetCameraZoomInLimit(){ return m_fCameraZoomInLimit; }

	void SetDisplayRotateYMax( float max ){ m_fDisplayRotateYMax = max; }
	void SetDisplayRotateYMin( float min ){ m_fDisplayRotateYMin = min; }

	float GetDisplayRotateYMax(){ return m_fDisplayRotateYMax; }
	float GetDisplayRotateYMin(){ return m_fDisplayRotateYMin; }

	void SetLookatPtHeight( float height ){ m_fLookatPtHeight = height; }
	float GetLookatPtHeight(){ return m_fLookatPtHeight; }

	void SetZoomChangeSpeed( float speed ){ m_fZoomChangeSpeed = speed; }
	float GetZoomChangeSpeed(){ return m_fZoomChangeSpeed; }

	void SetMountLookUpHeight( float height ){ m_fMountLookUpHeight = height; }
	float GetMountLookUpHeight(){ return m_fMountLookUpHeight; }

	void SetShowCollision( bool b ){ m_bShowCollision = b; }
	BOOL GetShowCollision(){ return m_bShowCollision; }

	void SetCameraCollision( bool b ){ m_bCameraCollision = b; }
	BOOL GetCameraCollision(){ return m_bCameraCollision; }

	void SetFreeCameraMode( bool b ){ m_bFreeCameraMode = b; } 
	BOOL GetFreeCameraMode(){ return m_bFreeCameraMode; }

	void SetLockCameraMode( bool b ){ m_bLockCameraMode = b; } 
	BOOL GetLockCameraMode(){ return m_bLockCameraMode; }

	void SetFollowCameraMode( bool b ){ m_bFollowCameraMode = b; } 
	BOOL GetFollowCameraMode(){ return m_bFollowCameraMode; }

	void SetFreeCameraStartPos( D3DXVECTOR3 pos ){ m_bFreeCameraStartPos = pos; } 
	D3DXVECTOR3 GetFreeCameraStartPos(){ return m_bFreeCameraStartPos; }

	void SetLock45DegreeCameraMode( bool b ){ m_bLock45DegreeCameraMode = b; }
	BOOL GetLock45DegreeCameraMode(){ return m_bLock45DegreeCameraMode; }

	void SetNeedUpdate45DegreeCamera( bool b ){ m_bNeedUpdate45DegreeCamera = b; }
	BOOL GetNeedUpdate45DegreeCamera(){ return m_bNeedUpdate45DegreeCamera; }

	void Set45DegreeCameraRotateZ( float rotate ){ m_f45DegreeCameraRotateZ = rotate; }
	float Get45DegreeCameraRotateZ(){ return m_f45DegreeCameraRotateZ; }

	void Set45DegreeCameraZoomOutLimit( float limit ){ m_f45DegreeCameraZoomOutLimit = limit; }
	float Get45DegreeCameraZoomOutLimit(){ return m_f45DegreeCameraZoomOutLimit; }

	void SetDIMOFS_X_Changed( bool b ){ m_bDIMOFS_X_Changed = b; };
	bool GetDIMOFS_X_Changed(){ return m_bDIMOFS_X_Changed; };

	void SetDIMOFS_Y_Changed( bool b ){ m_bDIMOFS_Y_Changed = b; };
	bool GetDIMOFS_Y_Changed(){ return m_bDIMOFS_Y_Changed; };

	void SetRotateXBuf( float f ){ m_fRotateXBuf = f; }
	float GetRotateXBuf(){ return m_fRotateXBuf; }

	void SetRotateYBuf( float f ){ m_fRotateYBuf = f; }
	float GetRotateYBuf(){ return m_fRotateYBuf; }

	void SetCameraZoomBuf( float f ){ m_fCameraZoomBuf = f; };
	float GetCameraZoomBuf(){ return m_fCameraZoomBuf; };

	void SetCameraInertia( float f ){ m_fCameraInertia = f; }
	float GetCameraInertia(){ return m_fCameraInertia; }

	void SetCameraRotateXWhenRButtonIsDown( float fValue ) { m_fCameraRotateXWhenRButtonIsDown = fValue; }
	float GetCameraRotateXWhenRButtonIsDown() { return m_fCameraRotateXWhenRButtonIsDown; }

	void ClearCollideTree(){ pCameraCollideTreeList.clear(); }

	BOOL IsPlayerMustUseAlphaTest() { return pCameraCollideTreeList.size() > 0;}

	void ResetViewport();

	D3DVIEWPORT9 * GetViewPortMain(){ return &m_ViewPortMain; }

	/*
	 * Author:	2012-7-19 wangshuai
	 * Desc: 	返回与摄像机碰撞的模型透明度
	 */
	float GetCameraCollisionModelAlpha(const TObjectInfo *model);

	//camera 相机变量 ncx
private:
	D3DVIEWPORT9	m_ViewPortMain;

	MeCamera*		m_pCamera;

	std::vector<TObjectInfo*> pCameraCollideTreeList;		// 遮挡视线的树列表

	BOOL m_bAutoCamera;//FALSE;

	float m_fCameraRotateX;//摄象机左右旋转值
	float m_fCameraRotateZ;//摄象机上下旋转值
	float m_fCameraRotateXCorrect;

	float m_fCameraRotateZSpeed; //摄象机饶Z轴旋转的速度
	float m_fCameraRotateXSpeed; //摄象机饶X轴旋转的速度

	float m_fCameraRotateZBuf; //摄象机的Z轴旋转Buf
	float m_fCameraRotateXBuf; //摄象机的X轴旋转Buf

	float m_fRotateXBuf;
	float m_fRotateYBuf;

	BOOL  m_bReturnTheCamera;

	float m_fCameraSmoothParameter; //摄象机的平滑系数

	float m_fLookUpAngle;

	float m_fBeginZoom; //起始摄象机远近
	float m_fCurCameraZoom; //当前摄象机的远近距离

	float m_fCameraInertia; //摄象机的惯性系数

	float m_fCameraZoomOutLimit; //镜头拉远的最大距离
	float m_fCameraDefaultZoomOutLimit; //镜头拉远的默认最大距离

	float m_fCameraZoomInLimit;//1.2f;

	float m_fDisplayRotateYMax;
	float m_fDisplayRotateYMin;

	float m_fCameraZoomBuf;//摄像机的距离缓冲

	float m_fZoomChangeSpeed;//

	// 摄象机的视点高度
	float m_fLookatPtHeight;
	// 摄像机拉近的时候要提升的最大高度
	float m_fUpHeightWhenZoomIn;
	float m_fUpHeightMaxWhenZoomIn;

	float m_fMountLookUpHeight;	// 骑马后相机抬高的高度
	float m_fMountLookupSpeed;
	float m_fCurMountLookAtHeight;

	bool m_bDIMOFS_X_Changed;
	bool m_bDIMOFS_Y_Changed;

	BOOL m_bShowCollision; //显示阻挡
	BOOL m_bCameraCollision; //摄象机碰撞

	BOOL m_bFreeCameraMode; //自由摄像机模式
	D3DXVECTOR3 m_bFreeCameraStartPos; //自由摄像机模式

	BOOL m_bLockCameraMode;             //锁定摄象机模式
	BOOL m_bFollowCameraMode;	        // 尾随摄像机模式

	BOOL m_B28D;//2.8d
	BOOL m_bLock45DegreeCameraMode;	            // 锁45°角摄像机模式
	float m_f45DegreeDefaultCameraDist;         // 锁45°角时，默认与人物距离，拉近时相机放平到g_f45DegreeCamereRotateZMin
	float m_f45DegreeCameraZoomOutLimit;         // 相机距离在g_f45DegreeDefaultCameraDist和g_f45DegreeCameraZoomOutLimit*1.5之间倾角不变
	float m_f45DegreeDefaultZoomOutLimit;
	float m_f45DegreeCameraRotateZ;	            // 锁45°角时，拉最远后的角度，与垂直夹角90 - 45，即水平夹角45°
	//float WSCAMERA_45DEGREE_CAMERA_ROTATE_ZMIN;    // 锁45°角时，拉近后的角度90 - 70即水平夹角20°
	float m_fCameraIntersectDegree;       // 相机与水平夹角大于90°-75°时，根据树的BBOX判断是否遮挡人物，小于这个角度时根据树的coli判断
	BOOL m_bNeedUpdate45DegreeCamera;
	float m_fEyeToGroundDist;
	float m_fCameraRotateXWhenRButtonIsDown;	// 记录右键按下时相机旋转方向
};

extern wsCamera* getwsCamera();