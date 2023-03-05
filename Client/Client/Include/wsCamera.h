#pragma once
#include "Me3d\Include.h"

/////////////////////////////////////////////////
//�����MeCamera���з�װ��������ܽ��й��� 
//��������Ŀ��ƺ���ײ����
//MeCamera* m_pCamera;Ϊ�۲������

//�������Ϸ�߼�ճ��������Ҫ��������
/////////////////////////////////////////////////

static const float WSCAMERA_DISPLAY_ZOOMIN_LIMIT = 8.3286;
static const float WSCAMERA_45DEGREE_CAMERA_ROTATE_ZMIN	= -53.6248;

class TObjectInfo;
class wsCamera
{
public:
	wsCamera(void);
	virtual ~wsCamera(void);

	//����
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
	 * Desc: 	�������������ײ��ģ��͸����
	 */
	float GetCameraCollisionModelAlpha(const TObjectInfo *model);

	//camera ������� ncx
private:
	D3DVIEWPORT9	m_ViewPortMain;

	MeCamera*		m_pCamera;

	std::vector<TObjectInfo*> pCameraCollideTreeList;		// �ڵ����ߵ����б�

	BOOL m_bAutoCamera;//FALSE;

	float m_fCameraRotateX;//�����������תֵ
	float m_fCameraRotateZ;//�����������תֵ
	float m_fCameraRotateXCorrect;

	float m_fCameraRotateZSpeed; //�������Z����ת���ٶ�
	float m_fCameraRotateXSpeed; //�������X����ת���ٶ�

	float m_fCameraRotateZBuf; //�������Z����תBuf
	float m_fCameraRotateXBuf; //�������X����תBuf

	float m_fRotateXBuf;
	float m_fRotateYBuf;

	BOOL  m_bReturnTheCamera;

	float m_fCameraSmoothParameter; //�������ƽ��ϵ��

	float m_fLookUpAngle;

	float m_fBeginZoom; //��ʼ�����Զ��
	float m_fCurCameraZoom; //��ǰ�������Զ������

	float m_fCameraInertia; //������Ĺ���ϵ��

	float m_fCameraZoomOutLimit; //��ͷ��Զ��������
	float m_fCameraDefaultZoomOutLimit; //��ͷ��Զ��Ĭ��������

	float m_fCameraZoomInLimit;//1.2f;

	float m_fDisplayRotateYMax;
	float m_fDisplayRotateYMin;

	float m_fCameraZoomBuf;//������ľ��뻺��

	float m_fZoomChangeSpeed;//

	// ��������ӵ�߶�
	float m_fLookatPtHeight;
	// �����������ʱ��Ҫ���������߶�
	float m_fUpHeightWhenZoomIn;
	float m_fUpHeightMaxWhenZoomIn;

	float m_fMountLookUpHeight;	// ��������̧�ߵĸ߶�
	float m_fMountLookupSpeed;
	float m_fCurMountLookAtHeight;

	bool m_bDIMOFS_X_Changed;
	bool m_bDIMOFS_Y_Changed;

	BOOL m_bShowCollision; //��ʾ�赲
	BOOL m_bCameraCollision; //�������ײ

	BOOL m_bFreeCameraMode; //���������ģʽ
	D3DXVECTOR3 m_bFreeCameraStartPos; //���������ģʽ

	BOOL m_bLockCameraMode;             //���������ģʽ
	BOOL m_bFollowCameraMode;	        // β�������ģʽ

	BOOL m_B28D;//2.8d
	BOOL m_bLock45DegreeCameraMode;	            // ��45��������ģʽ
	float m_f45DegreeDefaultCameraDist;         // ��45���ʱ��Ĭ����������룬����ʱ�����ƽ��g_f45DegreeCamereRotateZMin
	float m_f45DegreeCameraZoomOutLimit;         // ���������g_f45DegreeDefaultCameraDist��g_f45DegreeCameraZoomOutLimit*1.5֮����ǲ���
	float m_f45DegreeDefaultZoomOutLimit;
	float m_f45DegreeCameraRotateZ;	            // ��45���ʱ������Զ��ĽǶȣ��봹ֱ�н�90 - 45����ˮƽ�н�45��
	//float WSCAMERA_45DEGREE_CAMERA_ROTATE_ZMIN;    // ��45���ʱ��������ĽǶ�90 - 70��ˮƽ�н�20��
	float m_fCameraIntersectDegree;       // �����ˮƽ�нǴ���90��-75��ʱ����������BBOX�ж��Ƿ��ڵ����С������Ƕ�ʱ��������coli�ж�
	BOOL m_bNeedUpdate45DegreeCamera;
	float m_fEyeToGroundDist;
	float m_fCameraRotateXWhenRButtonIsDown;	// ��¼�Ҽ�����ʱ�����ת����
};

extern wsCamera* getwsCamera();