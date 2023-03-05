#include "wsCamera.h"
#include "GameMain.h"
#include "FuncPerformanceLog.h"
#include "PlayerMgr.h"
#include "Player.h"
#include "CameraStuntManager.h"
#include "GameSettingUI.h"
#include "MeTerrain/stdafx.h"
#include "MeTerrain/NdlWorldPickerBase.h"
#include "wsRender.h"
#include "Cfg.h"
#include "SettingEffect.h"

//��Ҫ���뵽������Ϊ��Ա��������   ��ʹ��ȫ�ֱ���
////////////////////////////////////////////
extern BOOL	g_bTheRoleMovingByDir;
extern BOOL g_bTheRoleCountermarch;
extern BOOL g_bMouseLButtonIsDown;
extern BOOL g_bMouseRButtonIsDown;

extern BOOL g_bMouseLButtonRotate;
extern BOOL g_bMouseRButtonRotate;

extern BOOL	g_bTheRoleJumping; //�����Ƿ�����
extern BOOL g_bTheRoleJumpingCountermarch; //�����Ƿ��������
extern BOOL g_bTheRoleSlipJumping; //�������»���Ծ

extern float g_fTheRoleRotateZCorrect;
extern DWORD g_dwLastFrameCostTime;


extern float			g_fTheRoleDirCorrect;
extern BOOL				g_bTheRoleMoveToTargetPos;
extern D3DXVECTOR3		g_vTheRoleTargetPos;
extern D3DXVECTOR3		g_vTheRoleTargetDir;
extern D3DXVECTOR3		g_vTheRoleJumpingDir;

extern float g_fPlayerCollisionHeight;
float g_fDisrenderRoleDistance = 0.8f;

extern BOOL	g_bRenderRole; //�Ƿ���Ⱦ����

extern float g_fCamerFOV;

extern GAME_STATE		g_GameState;

extern BOOL g_b25DRoleMoveFollowMouse;
extern BOOL g_b25DMouseLButtonDownOnTerrain;
extern BOOL g_b25DRoleMoveFollowMouseFocusOnUI;
extern DWORD g_dw25DLButtonDownStartTime;

////////////////////////////////////////////

extern CCameraStuntManager g_CameraStuntManager;		//������ؼ�������

// Ĭ�ϵ�֡��
#define DEFUALT_FPS 60.0f
#define MOUNT_LOOKUP_ACCELERATE	600.f	// ÿ����ٶ�


wsCamera* getwsCamera()
{
	static wsCamera s_wsCamera;
	return  &s_wsCamera;
}

wsCamera::wsCamera(void)
{
	m_bAutoCamera = TRUE;//FALSE;

	m_fCameraRotateX = 0.0f;
	m_fCameraRotateXCorrect = 0.0f;
//	m_fCameraRotateZ = (float)( 16 - 90 )/180*D3DX_PI; 45�ȳ�ʼ���ӽ�
	m_fCameraRotateZ = -(float)58/180*D3DX_PI; //2.8d��ʼ���ӽ�

	m_fCameraRotateZSpeed = D3DX_PI/4; //�������Z����ת���ٶ�
	m_fCameraRotateXSpeed = D3DX_PI/4; //�������X����ת���ٶ�

	m_fCameraRotateZBuf = 0; //�������Z����תBuf
	m_fCameraRotateXBuf = 0; //�������X����תBuf

	m_fRotateXBuf = 0;
	m_fRotateYBuf = 0;

	m_bReturnTheCamera = TRUE;

	m_fCameraSmoothParameter = 0.5f;

	m_fLookUpAngle = D3DX_PI*0.54f;

	m_fBeginZoom = 6; //��ʼ�����Զ��
	m_fCurCameraZoom = m_fBeginZoom; //��ǰ�������Զ������

	m_fCameraInertia = 1; //������Ĺ���ϵ��

	m_fCameraZoomOutLimit = 6.0f; //��ͷ��Զ��������
	m_fCameraDefaultZoomOutLimit = 6.0f; //��ͷ��Զ��Ĭ��������
	m_fCameraZoomInLimit = 0.f;//1.2f;
	m_fDisplayRotateYMax = -(float)120/180*D3DX_PI;
	m_fDisplayRotateYMin = -(float)5/180*D3DX_PI;

	m_fCameraZoomBuf = 0;

	m_fZoomChangeSpeed = 10.0f;

	// ��������ӵ�߶�
	m_fLookatPtHeight = 80.0f;
	// �����������ʱ��Ҫ���������߶�
	m_fUpHeightWhenZoomIn = 56.0f;
	m_fUpHeightMaxWhenZoomIn = 32.0f;

	m_fMountLookUpHeight = 55.f;	// ��������̧�ߵĸ߶�
	m_fMountLookupSpeed = 0.f;
	m_fCurMountLookAtHeight = 0.f;

	m_bDIMOFS_X_Changed = false;
	m_bDIMOFS_Y_Changed = false;

	m_bShowCollision = FALSE; //��ʾ�赲
	m_bCameraCollision = TRUE; //�������ײ

	m_bFreeCameraMode = FALSE; //���������ģʽ

	m_bLockCameraMode = FALSE;             //���������ģʽ
	m_bFollowCameraMode = FALSE;	        // β�������ģʽ

	m_bLock45DegreeCameraMode = FALSE;	            // ��45��������ģʽ
	m_f45DegreeDefaultCameraDist = 15.0f;         // ��45���ʱ��Ĭ����������룬����ʱ�����ƽ��g_f45DegreeCamereRotateZMin
	m_f45DegreeCameraZoomOutLimit = 11.0f;         // ���������g_f45DegreeDefaultCameraDist��g_f45DegreeCameraZoomOutLimit*1.5֮����ǲ���
	m_f45DegreeDefaultZoomOutLimit = m_f45DegreeCameraZoomOutLimit;
	m_f45DegreeCameraRotateZ = -45.f;	            // ��45���ʱ������Զ��ĽǶȣ��봹ֱ�н�90 - 45����ˮƽ�н�45��
	//WSCAMERA_45DEGREE_CAMERA_ROTATE_ZMIN = -70.f;    // ��45���ʱ��������ĽǶ�90 - 70��ˮƽ�н�20��
	m_fCameraIntersectDegree = -75.f;       // �����ˮƽ�нǴ���90��-75��ʱ����������BBOX�ж��Ƿ��ڵ����С������Ƕ�ʱ��������coli�ж�
	m_bNeedUpdate45DegreeCamera = FALSE;
	m_fEyeToGroundDist = 100.0f*20;
	m_fCameraRotateXWhenRButtonIsDown = 0.f;
	m_B28D = FALSE;
}

wsCamera::~wsCamera(void)
{
}

void wsCamera::Update45DegreeCameraRotate()
{
	if( m_fCurCameraZoom < m_f45DegreeDefaultCameraDist )
	{
		float fCameraRotate = (m_fCurCameraZoom - 4.f)* (m_f45DegreeCameraRotateZ - WSCAMERA_45DEGREE_CAMERA_ROTATE_ZMIN) / (m_f45DegreeDefaultCameraDist - 4.f) + WSCAMERA_45DEGREE_CAMERA_ROTATE_ZMIN;
		m_fCameraRotateZ = fCameraRotate * D3DX_PI / 180.f;
	}
    else
    {
        m_fCameraRotateZ = m_f45DegreeCameraRotateZ * D3DX_PI / 180.f;
    }
}

void wsCamera::UpdateCamera()
{
	guardfunc;
	if ( m_fCameraRotateX > 3.1415926*2 )
	{
		m_fCameraRotateX = 0;
	}

	if ( m_fCameraRotateX < -3.1415926*2 )
	{
		m_fCameraRotateX = 0;
	}

	static DWORD dwcurtime = HQ_TimeGetTime();

	DWORD dwCurCostTime = HQ_TimeGetTime() - dwcurtime;

	dwcurtime = HQ_TimeGetTime();
	/////////////////////////////////////////
	float fRotateXDistance = m_fCameraRotateZSpeed;
	float fRotateYDistance = m_fCameraRotateXSpeed;

	m_fCameraRotateZBuf += m_fRotateXBuf;

	// ��һ֡���������Z����ת��
	static float fLastCameraRotateZBuf = 0;

    /* ��Ұ��������ʼ�ƶ������ͷŷ����ֹͣ�ƶ�ʱ������Զ��ָ������ﱳ��; 
    ����Զ��ָ������У��������ٴ�������ı����ʱ���ͷ���������Զ��ָ�
    s_bNeedReturnTheCameraAfterMoving��¼�ƶ�״̬�ı���Ƿ�ָ��������*/
    //static BOOL s_bNeedReturnTheCameraAfterMoving = FALSE;
    if( m_bAutoCamera )
    {
        // ���������ʼ�ƶ�
		if( theHeroGame.GetPlayerMgr() && theHeroGame.GetPlayerMgr()->GetMe() )
        {
			if( g_bTheRoleMovingByDir && !theHeroGame.GetPlayerMgr()->GetMe()->m_bLastFrameMoving )
            {
                m_bReturnTheCamera = TRUE;
            }
        }
    }
    if( m_bReturnTheCamera && g_bMouseLButtonRotate )
    {
        m_bReturnTheCamera = FALSE;
    }

	float ftemp = 0;
	if( m_fCameraRotateZBuf != 0 )//�Ƿ�����Z��ת�� Y
	{
		if( m_bDIMOFS_X_Changed && abs(m_fCameraRotateZBuf) < 160 && dwCurCostTime < DEFUALT_FPS && fLastCameraRotateZBuf != m_fCameraRotateZBuf )
		{
			ftemp = m_fCameraRotateZBuf*m_fCameraSmoothParameter;//��X�����ƶ�
		}
		else
		{
			ftemp = m_fCameraRotateZBuf;//X�᷽����û����ת
		}

		m_fCameraRotateZBuf = m_fCameraRotateZBuf - ftemp;
		fLastCameraRotateZBuf = m_fCameraRotateZBuf;
		m_fRotateXBuf = 0;
	}
	//////////////////////////////////////////////
	// Mouse���δ���£��ҷ���Ծ״̬ //�������Զ���ת����
	if( !g_bMouseLButtonIsDown && !g_bTheRoleJumping )
	{
		m_fCameraRotateX -= ftemp * fRotateXDistance;	// ����ĳ�����ϵ����������ֵ���ţ�[QL]

        if( m_bReturnTheCamera && m_bAutoCamera )
		{
			CorrectCameraRotateValue(m_fCameraRotateXCorrect, fRotateXDistance);
			if( m_fCameraRotateXCorrect == 0 )
			{
				m_bReturnTheCamera = FALSE;
			}
		}

		if( g_bMouseRButtonIsDown )
		{
            if( !m_bLock45DegreeCameraMode )
            {
			    //���������������������λ��
			    m_fCameraRotateX += m_fCameraRotateXCorrect;
			    m_fCameraRotateX = fmodf( m_fCameraRotateX, D3DX_PI*2 );
			    g_fTheRoleRotateZCorrect = m_fCameraRotateX;
			    m_fCameraRotateXCorrect = 0;
			    g_fTheRoleDirCorrect = 0;

                if( abs(ftemp * fRotateXDistance) > 0.001 )
                {
                    g_bMouseRButtonRotate = TRUE;
                }
            }
            else
            {
                //������������򣬵����ﲻҪת���ƶ�ʱ���̸����������
                m_fCameraRotateX += m_fCameraRotateXCorrect;
                m_fCameraRotateX = fmodf( m_fCameraRotateX, D3DX_PI*2 );
                g_fTheRoleRotateZCorrect = m_fCameraRotateX;

                m_fCameraRotateXCorrect = 0;
                g_fTheRoleDirCorrect = 0;
            }
        }
		else
		{
			m_fCameraRotateX = fmodf( m_fCameraRotateX, D3DX_PI*2 );
		}
	}
	else	// Mouse������£�������Ծ״̬
	{	
		// Mouse�Ҽ�δ����
		if( !g_bMouseRButtonIsDown )
		{
			// Mouse�������
			if( g_bMouseLButtonIsDown )
			{
                if( !m_bLock45DegreeCameraMode )    // 3D�ӽ����������ת���
                {
				    m_fCameraRotateXCorrect /*+*/-= ftemp * fRotateXDistance;	// ����ĳ�����ϵ����������ֵ���ţ�[QL]
				    if( abs(ftemp * fRotateXDistance) > 0.005 )
				    {
					    g_bMouseLButtonRotate = TRUE;
				    }
                }
			}
			// Mouse���δ���£�����Ծ״̬
			else if( g_bTheRoleJumping )
			{
				m_fCameraRotateX /*+*/-= ftemp * fRotateXDistance;	// ����ĳ�����ϵ����������ֵ���ţ�[QL]
				g_fTheRoleRotateZCorrect = m_fCameraRotateX;
			}
		}
		else	// Mouse�Ҽ�����
		{
			// Mouse�������
			if( g_bMouseLButtonIsDown )
			{
// 				// ��Ծ״̬
// 				if( g_bTheRoleJumping )
// 				{
// 					m_fCameraRotateX -= ftemp * fRotateXDistance + m_fCameraRotateXCorrect;	// ����ĳ�����ϵ����������ֵ���ţ�[QL]
// 					m_fCameraRotateX = fmodf( m_fCameraRotateX, D3DX_PI*2 );
// 					g_fTheRoleRotateZCorrect = m_fCameraRotateX;
// 					m_fCameraRotateXCorrect = 0;
// 					g_fTheRoleDirCorrect = 0;
// 				}
// 				else	// ����Ծ״̬
				{
					if( m_fCameraRotateXCorrect != 0 )
					{
						// ��W��ǰ�ߣ�������������ת���ʱ��������Ҽ�����Ҫ����������ת���������
						m_fCameraRotateX += ftemp * fRotateXDistance + m_fCameraRotateXCorrect;
					}
					else
					{
						// ͬʱ�������������Ҽ����ƶ����ʱ��ת�����ƶ�����
						m_fCameraRotateX /*+*/-= ftemp * fRotateXDistance + m_fCameraRotateXCorrect;	// ����ĳ�����ϵ����������ֵ���ţ�[QL]
					}
					m_fCameraRotateX = fmodf( m_fCameraRotateX, D3DX_PI*2 );
					g_fTheRoleRotateZCorrect = m_fCameraRotateX;
					m_fCameraRotateXCorrect = 0;
					g_fTheRoleDirCorrect = 0;
				}
			}
			else	// Mouse���δ����
			{
				// ��Ծ״̬
				if( g_bTheRoleJumping )
				{
					////////////////���������������������λ��
					m_fCameraRotateX += m_fCameraRotateXCorrect;
					m_fCameraRotateXCorrect = 0;
				}

				m_fCameraRotateX /*+*/-= ftemp * fRotateXDistance;	// ����ĳ�����ϵ����������ֵ���ţ�[QL]
				m_fCameraRotateX = fmodf( m_fCameraRotateX, D3DX_PI*2 );
				g_fTheRoleRotateZCorrect = m_fCameraRotateX;

                if( abs(ftemp * fRotateXDistance) > 0.001 )
                {
                    g_bMouseRButtonRotate = TRUE;
                }
			}

			if( m_bReturnTheCamera && m_bAutoCamera )
			{
				CorrectCameraRotateValue(m_fCameraRotateXCorrect, fRotateXDistance);
				if( m_fCameraRotateXCorrect == 0 )
				{
					m_bReturnTheCamera = FALSE;
				}
			}
		}
	}

	m_fCameraRotateXBuf += m_fRotateYBuf;

	// ��һ֡���������X����ת��
	//static float fLastCameraRotateXFrame = 0;	// ò��û��[QL]
	static float fLastCameraRotateXBuf = 0;

	if( m_bDIMOFS_Y_Changed && abs(m_fCameraRotateXBuf) < 160 && dwCurCostTime < DEFUALT_FPS && fLastCameraRotateXBuf != m_fCameraRotateXBuf )
	{
		ftemp = m_fCameraRotateXBuf*m_fCameraSmoothParameter;
	}
	else
	{
		ftemp = m_fCameraRotateXBuf;
	}

	//fLastCameraRotateXFrame = ftemp;
	m_fCameraRotateXBuf = m_fCameraRotateXBuf - ftemp;
	fLastCameraRotateXBuf = m_fCameraRotateXBuf;
	m_fRotateYBuf = 0;

	float fStepY = ftemp * fRotateYDistance;

	if( !m_bLock45DegreeCameraMode && !m_bFollowCameraMode ) 
	{
		m_fCameraRotateZ += fStepY;

		if( m_fCameraRotateZ < m_fDisplayRotateYMax )
		{
			m_fCameraRotateZ = m_fDisplayRotateYMax;
		}
		else if( m_fCameraRotateZ > m_fDisplayRotateYMin )
		{
			m_fCameraRotateZ = m_fDisplayRotateYMin;
		}
	}else if (m_bLock45DegreeCameraMode && m_B28D && g_bMouseRButtonIsDown && !g_bMouseLButtonIsDown)//�������ӽǲ��ҿ���2.8d,����x����ת�Ƕȹ̶�һ��������
	{

		m_fCameraRotateZ += fStepY;

		if( m_fCameraRotateZ < -(float)58/180*D3DX_PI )
		{
			m_fCameraRotateZ = -(float)58/180*D3DX_PI;
		}
		else if( m_fCameraRotateZ > m_fDisplayRotateYMin)
		{
			m_fCameraRotateZ = m_fDisplayRotateYMin;
		}
	}


	// ����MeCamera Zoom
	float fDistDistance = m_fZoomChangeSpeed * g_dwLastFrameCostTime / 1000;
	BOOL fCameraZoomChange = FALSE;

	if( 0 > m_fCameraZoomBuf )
	{
		m_fCameraZoomBuf += fDistDistance;
		if( 0 < m_fCameraZoomBuf )
		{
			fDistDistance = fDistDistance - m_fCameraZoomBuf;
			m_fCameraZoomBuf = 0;
		}

		if( m_fCurCameraZoom > WSCAMERA_DISPLAY_ZOOMIN_LIMIT )
		{
			m_fCurCameraZoom -= fDistDistance;
			m_fUpHeightWhenZoomIn = ( m_fCurCameraZoom - WSCAMERA_DISPLAY_ZOOMIN_LIMIT )*4;
		}
		else
		{
			m_fCurCameraZoom -= fDistDistance;
			if( m_fCurCameraZoom < m_fCameraZoomInLimit/*1.382f*/ )
			{
				m_fCameraZoomBuf = 0;
				m_fCurCameraZoom = m_fCameraZoomInLimit/*1.382f*/;
			}
			m_fUpHeightWhenZoomIn = m_fUpHeightMaxWhenZoomIn*(WSCAMERA_DISPLAY_ZOOMIN_LIMIT - m_fCurCameraZoom)/(WSCAMERA_DISPLAY_ZOOMIN_LIMIT-1);
		}
		fCameraZoomChange = TRUE;
	}

	if( 0 < m_fCameraZoomBuf )
	{
		m_fCameraZoomBuf -= fDistDistance;

		if( 0 > m_fCameraZoomBuf )
		{
			fDistDistance = fDistDistance + m_fCameraZoomBuf;
			m_fCameraZoomBuf = 0;
		}

        if( !m_bLock45DegreeCameraMode )
        {
		    if( m_fCurCameraZoom < m_fCameraZoomOutLimit )
		    {
			    m_fCurCameraZoom += fDistDistance;

			    if( m_fCurCameraZoom < WSCAMERA_DISPLAY_ZOOMIN_LIMIT )
			    {
				    if( m_fCurCameraZoom < m_fCameraZoomInLimit/*1.382f*/ )
				    {
					    m_fCurCameraZoom = m_fCameraZoomInLimit/*1.382f*/;
				    }
				    m_fUpHeightWhenZoomIn = m_fUpHeightMaxWhenZoomIn*(WSCAMERA_DISPLAY_ZOOMIN_LIMIT - m_fCurCameraZoom)/(WSCAMERA_DISPLAY_ZOOMIN_LIMIT-1);
			    }
			    else
			    {
				    m_fUpHeightWhenZoomIn = (m_fCurCameraZoom - WSCAMERA_DISPLAY_ZOOMIN_LIMIT)*4;
			    }
		    }
		    else
		    {
			    m_fCameraZoomBuf = 0;
			    m_fCurCameraZoom = m_fCameraZoomOutLimit;
		    }
        }
        else
        {
            if( m_fCurCameraZoom < m_f45DegreeCameraZoomOutLimit )
            {
                m_fCurCameraZoom += fDistDistance;

                if( m_fCurCameraZoom < WSCAMERA_DISPLAY_ZOOMIN_LIMIT )
                {
                    if( m_fCurCameraZoom < m_fCameraZoomInLimit/*1.382f*/ )
                    {
                        m_fCurCameraZoom = m_fCameraZoomInLimit/*1.382f*/;
                    }
                    m_fUpHeightWhenZoomIn = m_fUpHeightMaxWhenZoomIn*(WSCAMERA_DISPLAY_ZOOMIN_LIMIT - m_fCurCameraZoom)/(WSCAMERA_DISPLAY_ZOOMIN_LIMIT-1);
                }
                else
                {
                    m_fUpHeightWhenZoomIn = (m_fCurCameraZoom - WSCAMERA_DISPLAY_ZOOMIN_LIMIT)*4;
                }
            }
            else
            {
                m_fCameraZoomBuf = 0;
                m_fCurCameraZoom = m_f45DegreeCameraZoomOutLimit;
            }
        }
		fCameraZoomChange = TRUE;
	}

	if( m_bLock45DegreeCameraMode ) 
	{
        if( m_bNeedUpdate45DegreeCamera )
        {
            Set45DegreeCameraMode(TRUE);
            m_bNeedUpdate45DegreeCamera = FALSE;
        }
        if( fCameraZoomChange && !m_B28D)//lyh++ 2.8d ���ù�������r x 
		    Update45DegreeCameraRotate();
	}
	//˵��:�������������ת�Ƕȣ���ֵ������У�У�keyword:eActionFollowCamare
	//add by yanli 2010-6-30*/
	//-------------------------------------------------------------------------------
	m_pCamera->SetRot(m_fCameraRotateX + m_fCameraRotateXCorrect);
	//-------------------------------------------------------------------------------
	unguard;
}

void wsCamera::ProcessCamera()
{
	guardfunc;
	if( pCameraCollideTreeList.size() )
	{
		for(UINT i=0; i<pCameraCollideTreeList.size(); i++)
		{
			pCameraCollideTreeList[i]->SetAlpha(1.f);
		}
	}
	pCameraCollideTreeList.clear();

	float fCameraRotateY = m_fCameraRotateZ;

	float fCameraCurRotateY = fCameraRotateY;
	if( fCameraCurRotateY < -m_fLookUpAngle )
	{
		fCameraCurRotateY = -m_fLookUpAngle;
	}

	D3DXVECTOR3 vLookatPt( 0,0,0 );
	float fZAdjust = 0.2;

	if( m_bFreeCameraMode )
	{
		if( theHeroGame.GetPlayerMgr()->GetMe() )
		{
			if( theHeroGame.GetPlayerMgr()->GetMe()->IsMoving() )
			{
				float fHeightCorrect = -(fCameraRotateY + D3DX_PI/2);
				if( theHeroGame.GetPlayerMgr()->GetMe()->IsCountermarch() )
				{
					m_fLookatPtHeight -= fHeightCorrect*6.18f;
				}
				else
				{
					m_fLookatPtHeight += fHeightCorrect*6.18f;
				}
			}
		}
	}

	if( theHeroGame.GetPlayerMgr()->GetMe() )
	{		
		vLookatPt.z += (m_fLookatPtHeight)*GetMe3dConfig()->m_fMdlSpaceScale;		

		if( theHeroGame.GetPlayerMgr()->GetMe()->IsMounting() )
		{
			if( m_fCurMountLookAtHeight < m_fMountLookUpHeight )
			{
				m_fMountLookupSpeed += g_dwLastFrameCostTime * MOUNT_LOOKUP_ACCELERATE / 1000.f;
				m_fCurMountLookAtHeight += g_dwLastFrameCostTime * m_fMountLookupSpeed / 1000.f;
				if( m_fCurMountLookAtHeight > m_fMountLookUpHeight )
				{
					m_fCurMountLookAtHeight = m_fMountLookUpHeight;
					m_fMountLookupSpeed = 0.f;
				}
			}
			vLookatPt.z += m_fCurMountLookAtHeight*GetMe3dConfig()->m_fMdlSpaceScale;
		}
		else if( m_fCurMountLookAtHeight > 0 )
		{
			m_fMountLookupSpeed += g_dwLastFrameCostTime * MOUNT_LOOKUP_ACCELERATE / 1000.f;
			m_fCurMountLookAtHeight -= g_dwLastFrameCostTime * m_fMountLookupSpeed / 1000.f;
			if( m_fCurMountLookAtHeight < 0 )
			{
				m_fCurMountLookAtHeight = 0;
				m_fMountLookupSpeed = 0.f;
			}
			else
				vLookatPt.z += m_fCurMountLookAtHeight*GetMe3dConfig()->m_fMdlSpaceScale;
		}
	}
	else
	{
		return;
	}

	D3DXVECTOR3 vEyePt = vLookatPt+D3DXVECTOR3( 0,0,1);
	D3DXVECTOR3 vDist = vEyePt-vLookatPt;
	D3DXVec3Normalize( &vDist, &vDist );

	// ��ֱ��ת��
	{
		D3DXVECTOR3 vXAxis( 1, 0, 0 );
		D3DXMATRIX matRotX;

		D3DXMatrixRotationAxis(
			&matRotX,
			&vXAxis,
			fCameraCurRotateY );

		D3DXVec3TransformCoord( &vDist, &vDist, &matRotX );
	}

	// ˮƽ��ת��
	float fdir;
	m_fCameraRotateX = fmodf( m_fCameraRotateX, D3DX_PI*2 );
	fdir = m_fCameraRotateX + m_fCameraRotateXCorrect;

	{
		D3DXVECTOR3 vZAxis( 0, 0, -1 );
		D3DXMATRIX matRotZ;

		D3DXMatrixRotationAxis(
			&matRotZ,
			&vZAxis,
			fdir );

		D3DXVec3TransformCoord( &vDist, &vDist, &matRotZ );
	}

	D3DXVECTOR3 vPos;
	static float fTargetHeight = 0;//Ŀ��߶�
	static float fNowHeight = 0;//��ǰ�߶�
	static float fMoveDis = 0;//��Ҫ�ƶ��ھ���

	if( theHeroGame.GetPlayerMgr()->GetMe() )
	{
		if (m_bFreeCameraMode)
		{
			m_bFreeCameraStartPos.x = theHeroGame.GetPlayerMgr()->GetMe()->GetPos().x;
			m_bFreeCameraStartPos.y = theHeroGame.GetPlayerMgr()->GetMe()->GetPos().y;
			vPos =  m_bFreeCameraStartPos + vLookatPt;
		}
		else
		{
			vPos = theHeroGame.GetPlayerMgr()->GetMe()->GetPos() + vLookatPt;
		}

		if(fTargetHeight!=vPos.z)
		{
			fTargetHeight = vPos.z;

			float dis = fTargetHeight - fNowHeight;

			fMoveDis = dis;
		}


		if( fMoveDis!=0 && !theHeroGame.GetPlayerMgr()->GetMe()->IsJumping() )
		{
			float length = fTargetHeight-fNowHeight;
			float length2 = fMoveDis*theHeroGame.GetFrameElapsedTime()*10;//����0.1�� �ƶ���Ŀ��߶�

			//�ƶ����
			if(length>length2&&length>0)
			{
				vPos.z = fNowHeight + length2;
			}
			else if(length<length2&&length<0)
			{
				vPos.z = fNowHeight + length2;
			}
			else
			{
				vPos.z = fTargetHeight;
				fMoveDis = 0;
			}
		}

		fNowHeight = vPos.z;//���µ�ǰ����߶�

		g_CameraStuntManager.UpdateRolePos( vPos,m_pCamera->GetViewDir());
	}
	else
	{
		return;
	}

	vPos += g_CameraStuntManager.GetLookatPosOffset();

	D3DXVECTOR3 vStart = vPos;	// ������λ��
	D3DXVECTOR3 vDir = vPos+vDist*m_fCurCameraZoom;	// �������λ��

	// ��ײ����
	D3DXVECTOR3 vCollisionNormal;

	float fDistToTerrain = 0xffffffff;
	float fDistToCollision = 0xffffffff;
	float fNextDist = 0xffffffff;

	static float fCurDist = m_fCurCameraZoom;
    BOOL bCameraIntersectColi;  // �Ƿ��������coli�ж����߱����ڵ�
    int close_id = -1;
    TPickResult castCameraColiResult;
    castCameraColiResult.pickResultCount = 0;

	if (!m_bFreeCameraMode)
	{
		BOOL bhaspick = FALSE;
		float fLength1;
		fLength1 = m_fCurCameraZoom;
		if (theHeroGame.GetWorld()->IsActive() && theHeroGame.GetWorld()->GetWorldBuffer() && theHeroGame.GetWorld()->GetWorldBuffer()->GetActiveTile() && theHeroGame.GetWorld()->GetWorldBuffer()->GetActiveTile()->IsLoad())
		{
			// ֱ��ȡChunk���÷�Σ��
			BspTree::SIntersect *pIntersect = NULL;
			ChunkIntersection NearestIntersection;
			if (m_bCameraCollision)
			{
				vStart.z -= fZAdjust;   // ��ֹ��0����ر�̫�ӽ�����Pick���̧��fZAdjust
				std::vector<ChunkIntersection> vectorIntersection;

				// ȡ�������chunk
				INT nCameraChunkX = ChunkFromPos( vDir.x );
				INT nCameraChunkY = ChunkFromPos( vDir.y );
				if( nCameraChunkX < 0 || nCameraChunkY < 0 || nCameraChunkX >= theHeroGame.GetWorld()->GetWorldBuffer()->GetActiveTile()->GetRowColumn()[0] || nCameraChunkY >= theHeroGame.GetWorld()->GetWorldBuffer()->GetActiveTile()->GetRowColumn()[1] )
				{
					LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "Process Camera ���λ�ó��� \t[%f:%f]", vDir.x, vDir.y);
					return;
				}

				SwGlobal::GetWorldPicker()->GetCameraTerrainIntersection(nCameraChunkX, nCameraChunkY, &vStart, &vDist, &vectorIntersection);

				// ȡ������chunk
				INT nRoleChunkX = ChunkFromPos( vStart.x );
				INT nRoleChunkY	= ChunkFromPos( vStart.y );
				if (nRoleChunkX < 0 || nRoleChunkY < 0 || nRoleChunkX >= theHeroGame.GetWorld()->GetWorldBuffer()->GetActiveTile()->GetRowColumn()[0] || nRoleChunkY >= theHeroGame.GetWorld()->GetWorldBuffer()->GetActiveTile()->GetRowColumn()[1] )
				{
					LOG_MESSAGE( INFO_LOG, LOG_PRIORITY_INFO, "Process Camera ��λ�ó��� \t[%f:%f]", vStart.x, vStart.y);
					return;
				}

				// ������˵�����������chunk�ر��Ƿ��ڵ����
				if( nCameraChunkX != nRoleChunkX || nCameraChunkY != nRoleChunkY )
				{
					struct chunk_info_
					{
						int nChunkX;
						int nChunkY;
					};
					std::vector<chunk_info_> vtInterChunkList;
					vtInterChunkList.clear();
					if( nCameraChunkX == nRoleChunkX )
					{
						int step = (nCameraChunkY - nRoleChunkY > 0)? 1 : -1;
						int nStartY = nRoleChunkY;
						int num = 0;
						while( nStartY != nCameraChunkY )
						{
							chunk_info_ kChunkInfo;
							kChunkInfo.nChunkX = nRoleChunkX;
							kChunkInfo.nChunkY = nStartY;
							vtInterChunkList.push_back(kChunkInfo);
							nStartY += step;
							num++;
							if( num > 10 )  // ÿ��chunk��16*16��������˾��벻���ܳ���10��
								break;
						}
					}
					else if( nCameraChunkY == nRoleChunkY )
					{
						int step = (nCameraChunkX - nRoleChunkX > 0)? 1 : -1;
						int nStartX = nRoleChunkX;
						int num = 0;
						while( nStartX != nCameraChunkX )
						{
							chunk_info_ kChunkInfo;
							kChunkInfo.nChunkX = nStartX;
							kChunkInfo.nChunkY = nRoleChunkY;
							vtInterChunkList.push_back(kChunkInfo);
							nStartX += step;
							num++;
							if( num > 10 )  // ÿ��chunk��16*16��������˾��벻���ܳ���10��
								break;
						}
					}
					else
					{
						int deltax = (nCameraChunkX - nRoleChunkX)>0 ? 1 : -1;
						int deltay = (nCameraChunkY - nRoleChunkY)>0 ? 1 : -1;
						LONG x = nRoleChunkX;
						LONG y = nRoleChunkY;
						int num = 0;
						while (x != nCameraChunkX + deltax)
						{
							while (y != nCameraChunkY + deltay)
							{
								if(!( x == nCameraChunkX && y == nCameraChunkY ))	// camera����chunk�Ѿ�����������Դ˴�ȥ��[QL]
								{
									//��������ε��ĸ����㶼��ֱ�ߵ�ͬһ�࣬��ô�����������ֱ�߲��ཻ,�����������������һ������Ļ�������һ��С�ڵ�����
									// ֱ����chunk�ཻ
									{
										chunk_info_ kChunkInfo;
										kChunkInfo.nChunkX = x;
										kChunkInfo.nChunkY = y;
										vtInterChunkList.push_back(kChunkInfo);
										num++;
										if( num > 10 )  // ÿ��chunk��16*16��������˾��벻���ܳ���10��
											break;
									}

								}
								y += deltay;
							}
							if( num > 10 )  // ÿ��chunk��16*16��������˾��벻���ܳ���10��
								break;

							x += deltax;
							y = nRoleChunkY;
						}
					}

					for(UINT nChunk = 0; nChunk<vtInterChunkList.size(); nChunk++)
					{
						SwGlobal::GetWorldPicker()->GetCameraTerrainIntersection(vtInterChunkList[nChunk].nChunkX, vtInterChunkList[nChunk].nChunkY,
							&vStart, &vDist, &vectorIntersection);
					}
				}

				if( vectorIntersection.size() > 0 )
				{
					ChunkIntersection* is = &vectorIntersection[0];
					for(int i = 1; i < vectorIntersection.size(); i++ )
					{
						if( is->t > vectorIntersection[i].t )
							is = &vectorIntersection[i];
					}
					NearestIntersection = *is;

					bhaspick = TRUE;
					fDistToTerrain = D3DXVec3Length( &(NearestIntersection.p-vStart) );
					fNextDist = fDistToTerrain;

					D3DXVECTOR3 vX1;
					D3DXVECTOR3 vY1;

					D3DXVec3Normalize( &vX1, &vDist );
					D3DXVec3Normalize( &vY1, &NearestIntersection.normal );

					float fDot = D3DXVec3Dot( &vX1, &vY1 );
					fNextDist = fNextDist - ( 1 -/*+*/ fDot )*1.5f;	// ���������ϵ�󣬷���ȡ��[QL]
				}
				vStart.z += fZAdjust;
			}

			bCameraIntersectColi = m_fCameraRotateZ <= m_fCameraIntersectDegree*D3DX_PI/180 ? TRUE: FALSE;
			if (SwGlobal::GetWorldPicker()->Pick(*(Vector*) &vStart, *(Vector *) &vDist, castCameraColiResult, emPT_CameraCollisionObj, false, fLength1))
			{
				// ��ȡ���������ģ��
				float fMinDist = 10000.0f;
				for (sInt32 i = 0; i < castCameraColiResult.pickResultCount; ++i)
				{
					// ����ʾģ��
					if (castCameraColiResult.pickResultInfo[i].resultObjInfo && castCameraColiResult.pickResultInfo[i].resultObjInfo->model
						&& castCameraColiResult.pickResultInfo[i].resultObjInfo->model->GetMex() )
					{
						char modelname[MAX_PATH] = {0};
						strcpy(modelname, castCameraColiResult.pickResultInfo[i].resultObjInfo->model->GetMex()->GetFilename());
						strlwr(modelname);

						// ��ǰֻ�����Ų����͸����ײ
						//if( castCameraColiResult.pickResultInfo[i].dist < fMinDist && !strstr(modelname, "tree") )

						if (castCameraColiResult.pickResultInfo[i].dist < fMinDist)
						{
							fMinDist = castCameraColiResult.pickResultInfo[i].dist;
							close_id = i;
						}
					}
				}

				if( close_id >= 0 )				
				{
					// �������λ��
					fDistToCollision = castCameraColiResult.pickResultInfo[close_id].dist;
					D3DXVECTOR3 vNormal = *(D3DXVECTOR3*)&castCameraColiResult.pickResultInfo[close_id].normal;
					D3DXVec3Normalize(&vNormal, &vNormal);
					D3DXVECTOR3 vDistNormal;
					D3DXVec3Normalize( &vDistNormal, &vDist );
					float fDot = D3DXVec3Dot( &vDistNormal, &vNormal);

					// ����볡��ģ�͵Ľ���Ͻ�
					if( fDistToCollision < fDistToTerrain )
					{
						if (m_bLock45DegreeCameraMode && castCameraColiResult.pickResultInfo[close_id].resultObjInfo->m_bIs2_5dColi)
						{
							// ֻ��2.5Dģʽ��, ����ģ����2.5d�赲��ײ��ʶ, ���������λ��
							bhaspick = TRUE;
							fNextDist = fDistToCollision - ( 1 - fDot )*1.3f;
						}
					}
				}
			}
		}

		static BOOL bStartZoomOut = FALSE; //��ʼ����ͷ��Զ
		static DWORD dwStartZoomOutTime = HQ_TimeGetTime(); //��ʼ��Զ��ʱ��

		// ����ͷ������Զ����
		if (bhaspick)
		{
			if (fNextDist > fLength1)
			{
				if( fCurDist < m_fCurCameraZoom )
				{
					if( !bStartZoomOut )
					{
						dwStartZoomOutTime = HQ_TimeGetTime();
						bStartZoomOut = TRUE;
					}
				}
				else
				{
					bStartZoomOut = FALSE;
					fCurDist = m_fCurCameraZoom;
				}
			}
			else
			{
				if( fCurDist < fNextDist )
				{
					if( !bStartZoomOut )
					{
						dwStartZoomOutTime = HQ_TimeGetTime();
						bStartZoomOut = TRUE;
					}
				}
				else
				{
					bStartZoomOut = FALSE;
					fCurDist = fNextDist;
				}
			}
		}
		else
		{
			if( fCurDist < m_fCurCameraZoom )
			{
				if( !bStartZoomOut )
				{
					dwStartZoomOutTime = HQ_TimeGetTime();
					bStartZoomOut = TRUE;
				}
			}
			else
			{
				bStartZoomOut = FALSE;
				fCurDist = m_fCurCameraZoom;
			}
		}

		if( bStartZoomOut )
		{
			if( m_fCameraZoomBuf != 0 || ( HQ_TimeGetTime() - dwStartZoomOutTime > 100 ) )
			{
				if( fNextDist > fCurDist/*6*/ )
				{
					fCurDist += g_dwLastFrameCostTime*0.00618f;
					if( fCurDist > fNextDist )
						fCurDist = fNextDist;
				}
			}
		}
	}

	g_CameraStuntManager.ProcessSmothMove(m_fCurCameraZoom);
    if( !m_bLock45DegreeCameraMode )
    {
	    if( fCurDist > m_fCameraZoomOutLimit )
	    {
		    fCurDist = m_fCameraZoomOutLimit;
	    }
    }
    else
    {
        if( fCurDist > m_f45DegreeCameraZoomOutLimit )
        {
            fCurDist = m_f45DegreeCameraZoomOutLimit;
        }
    }

	/*
	 * 2012.6.30 wangshuai
	 * 2.5Dģ�����ƾ�ͷZoom���������, fCurDistԽ������Խ��
	 */
	if (m_bLock45DegreeCameraMode)
	{
		if (fCurDist < 2.32)
		{
			fCurDist = 2.32;
		}
	}
	else
	{
		if (fCurDist < 0.1)
		{
			fCurDist = 0.1;
		}
	}

	vDir = vPos + vDist * fCurDist;

	/*
	 * 2012.6.25 wangshuai
	 * ��ס��ɫ��ģ�Ͱ�͸����ʾ
	 */
	if (!m_bFreeCameraMode)
	{
		// ���������ʵ��λ���ж�
		if( castCameraColiResult.pickResultCount > 0 )
		{
			if( close_id < 0 )
			{
				// û�з�����ģ�ͣ�������ģ�Ͷ���ӵ����б���
				for(int i=0; i<castCameraColiResult.pickResultCount; i++)
				{
					if (castCameraColiResult.pickResultInfo[i].dist < fCurDist
						&& castCameraColiResult.pickResultInfo[i].resultObjInfo && !castCameraColiResult.pickResultInfo[i].resultObjInfo->m_bIsOpaque)
					{
						pCameraCollideTreeList.push_back(castCameraColiResult.pickResultInfo[i].resultObjInfo);
						castCameraColiResult.pickResultInfo[i].resultObjInfo->SetAlpha(
							this->GetCameraCollisionModelAlpha(castCameraColiResult.pickResultInfo[i].resultObjInfo));
					}
				}
			}
			else
			{
				// �Ѿ���С���±�Ϊclose_id��ģ�ͼ������б���
				for (int i = 0; i < castCameraColiResult.pickResultCount; i++)
				{
					//if( i == close_id )
					//	continue;
					if (castCameraColiResult.pickResultInfo[i].dist < fCurDist
						&& castCameraColiResult.pickResultInfo[i].resultObjInfo && !castCameraColiResult.pickResultInfo[i].resultObjInfo->m_bIsOpaque)
					{
						pCameraCollideTreeList.push_back(castCameraColiResult.pickResultInfo[i].resultObjInfo);
						castCameraColiResult.pickResultInfo[i].resultObjInfo->SetAlpha(
							this->GetCameraCollisionModelAlpha(castCameraColiResult.pickResultInfo[i].resultObjInfo));
					}
				}
			}
		}
		// ���������coli�ж����ڵ����������ģ��BBox�ж϶����ߵ��ڵ�
		if( !bCameraIntersectColi && pCameraCollideTreeList.size() == 0 && false)
		{
			TPickResult cameraCastResult;
            cameraCastResult.pickResultCount = 0;

			if(SwGlobal::GetWorldPicker() && SwGlobal::GetWorldPicker()->Pick(*(Vector*)&vStart, *(Vector*)&vDist,cameraCastResult,emPT_ObjBBox,false,fCurDist))
			{
				if( close_id < 0 )
				{
					// ����û�����ģ���ڵ�����������ģ�Ͷ���ӵ����б���
					for (sInt32 i = 0; i < cameraCastResult.pickResultCount; ++i)
					{
						if( cameraCastResult.pickResultInfo[i].resultObjInfo
							&& cameraCastResult.pickResultInfo[i].resultObjInfo->model
							&&  cameraCastResult.pickResultInfo[i].resultObjInfo->model->GetMex()
							&& cameraCastResult.pickResultInfo[i].resultType == emPT_ObjBBox )
						{
							char modelname[MAX_PATH] = {0};
							MexAnimCtrl* pAnimCtrl = cameraCastResult.pickResultInfo[i].resultObjInfo->model;
							strcpy(modelname, pAnimCtrl->GetMex()->GetFilename());
							strlwr(modelname);
							if( strstr(modelname, "tree") )
							{
								Vector vecMin = pAnimCtrl->GetWorldMin();
								vecMin.z = vStart.z;
								Vector vecMax = pAnimCtrl->GetWorldMax();
								vecMax.z = vStart.z;
								Vector vecCenter = (vecMin + vecMax) / 2;        //BBoxˮƽ�����ĵ�
								float fRadius = (vecMax - vecMin).length() / 2;  //BBOXˮƽ��뾶
								Vector vecEye = *(Vector*)&vDir;
								vecEye.z = vStart.z;
								float roleToCenter = (vecCenter - *(Vector*)&vStart).length();
								float roleToEye = (vecEye - *(Vector*)&vStart).length();
								float eyeToCenter = (vecEye - vecCenter).length();
								/* ���������˾�����������BBox���ľ��룬
								����������˾���С�������BBox���ľ��룬���˿���BBoxһ��fRadius�ľ���*/
								if( roleToEye > eyeToCenter
									|| (roleToEye <= eyeToCenter && roleToCenter < fRadius / 2))
								{
									pCameraCollideTreeList.push_back(cameraCastResult.pickResultInfo[i].resultObjInfo);
									cameraCastResult.pickResultInfo[i].resultObjInfo->SetAlpha(0.2);
								}
							}
						}
					}
				}
				else
				{
					// �Ҿ���С��fCurDist����ģ��
					for (sInt32 i = 0; i < cameraCastResult.pickResultCount; ++i)
					{
						if( cameraCastResult.pickResultInfo[i].resultObjInfo
							&& cameraCastResult.pickResultInfo[i].resultObjInfo->model
							&& cameraCastResult.pickResultInfo[i].resultObjInfo->model->GetMex()
							&& cameraCastResult.pickResultInfo[i].resultType == emPT_ObjBBox )
						{
							char modelname[MAX_PATH] = {0};
							MexAnimCtrl* pAnimCtrl = cameraCastResult.pickResultInfo[i].resultObjInfo->model;
							strcpy(modelname, pAnimCtrl->GetMex()->GetFilename());
							strlwr(modelname);
							if( strstr(modelname, "tree") )
							{
								Vector vecMin = pAnimCtrl->GetWorldMin();
								vecMin.z = vStart.z;
								Vector vecMax = pAnimCtrl->GetWorldMax();
								vecMax.z = vStart.z;
								Vector vecCenter = (vecMin + vecMax) / 2;
								float fRadius = (vecMax - vecMin).length() / 2;
								Vector vecEye = *(Vector*)&vDir;
								vecEye.z = vStart.z;
								float roleToCenter = (vecCenter - *(Vector*)&vStart).length();
								float roleToEye = (vecEye - *(Vector*)&vStart).length();
								float eyeToCenter = (vecEye - vecCenter).length();
								/* ���������˾�����������BBox���ľ��룬
								����������˾���С�������BBox���ľ��룬���˿���BBoxһ��fRadius�ľ���*/
								if( roleToEye > eyeToCenter
									|| (roleToEye <= eyeToCenter && roleToCenter < fRadius / 2))
								{
									pCameraCollideTreeList.push_back(cameraCastResult.pickResultInfo[i].resultObjInfo);
									cameraCastResult.pickResultInfo[i].resultObjInfo->SetAlpha(0.2);
								}
							}
						}
					}
				}
			}
		}
		//////////////////////////////////////////////////////////////////////////////////////////
	}
  
	if( !m_bFreeCameraMode )
	{
		if( fCurDist < g_fDisrenderRoleDistance )
		{
			g_bRenderRole = FALSE;
		}
		else
		{
			g_bRenderRole = TRUE;
		}
	}

	float fLookatHeightCorrect = 0;

	if( fCameraRotateY < -m_fLookUpAngle)
	{
		fLookatHeightCorrect = (-fCameraRotateY) - m_fLookUpAngle;
		fLookatHeightCorrect = fLookatHeightCorrect*fLookatHeightCorrect*25.0f;
	}

	vPos.z += fLookatHeightCorrect;

	INT nChunkX = ChunkFromPos(vDir.x);
	INT nChunkY = ChunkFromPos(vDir.y);

    CWorldChunk* pChunk = NULL;
    if( SwGlobal::GetWorld() && SwGlobal::GetWorld()->GetWorldBuffer() && SwGlobal::GetWorld()->GetWorldBuffer()->GetActiveTile())
    {
        pChunk = SwGlobal::GetWorld()->GetWorldBuffer()->GetActiveTile()->GetChunk( nChunkX, nChunkY );

		CPlayer *pMe = theHeroGame.GetPlayerMgr()->GetMe();
        if( pMe )
        {
            INT nMyChunkX = ChunkFromPos(vPos.x);
            INT nMyChunkY = ChunkFromPos(vPos.y);
            CWorldChunk* pMyChunk = SwGlobal::GetWorld()->GetWorldBuffer()->GetActiveTile()->GetChunk( nMyChunkX, nMyChunkY );

            if( pChunk && pMyChunk )
            {
                if( vDir.z - pChunk->GetLiquidHeight() < 0.6f )
                {
                    vDir.z =  pChunk->GetLiquidHeight() + 0.6f;
                }
            }
        }
    }

	m_pCamera->SetViewParams( vDir, vPos, D3DXVECTOR3( 0, 0, 1 ) );//��ʱ��û�ƹ���

	// ��������������ģ�ͣ����а�͸������
	D3DXVECTOR3 vec3Len = vDir - vPos;//theHeroGame.GetPlayerMgr()->GetMe()->GetPos();
	if ( vec3Len.z < 0 )
	{
		vec3Len.z = 0.0f;
	}
	float len = D3DXVec3Length(&vec3Len);
	if ( len < 1.0f )
	{
		theHeroGame.GetPlayerMgr()->GetMe()->SetCurRenderAlpha(len * 0.1);
	}
	else
	{
		theHeroGame.GetPlayerMgr()->GetMe()->SetCurRenderAlpha(theHeroGame.GetPlayerMgr()->GetMe()->GetFinalRenderAlpha());
	}

	unguard;
}

void wsCamera::CorrectCameraRotateValue( float& fCameraRotateXCorrect, float fRotateXDistance )
{
	m_fCameraRotateXCorrect = fmodf( m_fCameraRotateXCorrect, D3DX_PI*2 );

	if( m_fCameraRotateXCorrect > 0 )
	{
		if( m_fCameraRotateXCorrect > D3DX_PI )
		{
			m_fCameraRotateXCorrect = m_fCameraRotateXCorrect - D3DX_PI*2;
			m_fCameraRotateXCorrect += fRotateXDistance*60;
		}
		else
		{
			m_fCameraRotateXCorrect -= fRotateXDistance*60;
			if( m_fCameraRotateXCorrect < 0 )
			{
				m_fCameraRotateXCorrect = 0;
			}
		}
	}
	else if( m_fCameraRotateXCorrect < 0 )
	{
		if( m_fCameraRotateXCorrect < -D3DX_PI )
		{
			m_fCameraRotateXCorrect = m_fCameraRotateXCorrect + D3DX_PI*2;
			m_fCameraRotateXCorrect -= fRotateXDistance*60;
		}
		else
		{
			m_fCameraRotateXCorrect += fRotateXDistance*60;
			if( m_fCameraRotateXCorrect > 0 )
			{
				m_fCameraRotateXCorrect = 0;
			}
		}
	}
}

void  wsCamera::SetCameraRotateZ( float fCameraRotateZ )
{
	if (m_bLock45DegreeCameraMode && !m_B28D)
	{
		 m_fCameraRotateZ = fCameraRotateZ;
	}
	else
	{
		if( m_fCameraRotateZ < -(float)58/180*D3DX_PI )
		{
			m_fCameraRotateZ = -(float)58/180*D3DX_PI;
		}
		else if( m_fCameraRotateZ > m_fDisplayRotateYMin)
		{
			m_fCameraRotateZ = m_fDisplayRotateYMin;
		}

	}
	
}


void wsCamera::Set28Mode(BOOL bLock)
{
m_B28D = TRUE;
m_bLock45DegreeCameraMode = TRUE;
theHeroGame.setshCur25Direction( CHeroGame::EMD_NONE );   
}
//���ܻ��ֲ�����Ҫ�޸�
void wsCamera::Set45DegreeCameraMode(BOOL bLock)
{
	if( bLock ) // 2.5D����
	{  
		if(!m_B28D)
		m_fCameraRotateZ = m_f45DegreeCameraRotateZ*D3DX_PI/180.f;
		else
		{
			if( m_fCameraRotateZ < -(float)58/180*D3DX_PI )
			{
				m_fCameraRotateZ = -(float)58/180*D3DX_PI;
			}
			else if( m_fCameraRotateZ > m_fDisplayRotateYMin)
			{
				m_fCameraRotateZ = m_fDisplayRotateYMin;
			}
		}

		m_bLock45DegreeCameraMode = TRUE;
		//m_B28D = FALSE;
		g_fCamerFOV = D3DX_PI / 180 * ( 45 + 13 );
		//m_fCurCameraZoom = m_f45DegreeCameraZoomOutLimit;
		s_CUI_ID_FRAME_SettingEffect.SetScrollBarFov(520);//���������߼����Ƴ�
		theHeroGame.setshCur25Direction( CHeroGame::EMD_NONE );      // Ĭ�����ƶ�

		m_B28D = TRUE; //Ĭ�ϴ�2.8d
	        if( g_GameState != G_MAIN )	
            m_bNeedUpdate45DegreeCamera = TRUE;

	}
	else        // 3D����
	{
        if( m_fCurCameraZoom > m_fCameraZoomOutLimit )
            m_fCurCameraZoom = m_fCameraZoomOutLimit;
		m_fCameraRotateZ = (float)( 16 - 90 )/180*D3DX_PI;	// �ָ�Ĭ��ֵ
		m_bLock45DegreeCameraMode = FALSE;
	}
	if( theHeroGame.GetPlayerMgr() && theHeroGame.GetPlayerMgr()->GetMe() )
        theHeroGame.GetPlayerMgr()->GetMe()->SetForceTurnRole(FALSE);
    g_b25DRoleMoveFollowMouse = FALSE;
    g_b25DMouseLButtonDownOnTerrain = FALSE;
    g_b25DRoleMoveFollowMouseFocusOnUI = FALSE;
	
}

void wsCamera::SetFollowCameraMode(BOOL bLock)
{
	if( bLock )
	{
		m_bFollowCameraMode = TRUE;
		SetCameraRotateZ( -90.f * D3DX_PI / 180.f );	// ���ˮƽ�н�Ϊ0
	}
	else
	{
		m_bFollowCameraMode = FALSE;
	}
}

void wsCamera::zoomoutCamera()
{
	guardfunc;

	if ( WSCAMERA_DISPLAY_ZOOMIN_LIMIT < m_fCurCameraZoom )
	{
		m_fCameraZoomBuf -= 6;
		if ( m_fCameraZoomBuf < -10 )
		{
			m_fCameraZoomBuf = -10;
		}
	}

	unguard;
}

void wsCamera::zoominCamera()
{
	guardfunc;

	if ( m_fCameraZoomOutLimit > m_fCurCameraZoom )
	{
		m_fCameraZoomBuf += 6;
		if ( m_fCameraZoomBuf > 10 )
		{
			m_fCameraZoomBuf = 10;
		}
	}

	unguard;
}

void wsCamera::moveleftCamera()
{
	guardfunc;

	float fRotateXDistance = m_fCameraRotateZSpeed * g_dwLastFrameCostTime / 200;

	if( !g_bMouseLButtonIsDown )
	{
		m_fCameraRotateX += 2 * fRotateXDistance;
		g_fTheRoleRotateZCorrect = m_fCameraRotateX;
	}
	else
	{
		g_fTheRoleRotateZCorrect += 2 * fRotateXDistance;
	}

	unguard;
}

void wsCamera::moverightCamera()
{
	guardfunc;

	float fRotateXDistance = m_fCameraRotateZSpeed * g_dwLastFrameCostTime / 200;

	if( !g_bMouseLButtonIsDown )
	{
		m_fCameraRotateX -= 2 * fRotateXDistance;
		g_fTheRoleRotateZCorrect = m_fCameraRotateX;

	}
	else
	{
		g_fTheRoleRotateZCorrect -= 2 * fRotateXDistance;
	}

	unguard;
}
void wsCamera::moveupCamera()
{
	guardfunc;

	float fRotateYDistance = m_fCameraRotateXSpeed * g_dwLastFrameCostTime / 1000;

	float fStepY = 2 * fRotateYDistance;

	m_fCameraRotateZ -= fStepY;

	if( m_fCameraRotateZ < m_fDisplayRotateYMax )
	{
		m_fCameraRotateZ = m_fDisplayRotateYMax;
	}
	else if( m_fCameraRotateZ > m_fDisplayRotateYMin )
	{
		m_fCameraRotateZ = m_fDisplayRotateYMin;
	}

	unguard;
}
void wsCamera::movedownCamera()
{
	guardfunc;

	float fRotateYDistance = m_fCameraRotateXSpeed * g_dwLastFrameCostTime / 1000;

	float fStepY = 2 * fRotateYDistance;

	m_fCameraRotateZ += fStepY;

	if( m_fCameraRotateZ < m_fDisplayRotateYMax )
	{
		m_fCameraRotateZ = m_fDisplayRotateYMax;
	}
	else if( m_fCameraRotateZ > m_fDisplayRotateYMin )
	{
		m_fCameraRotateZ = m_fDisplayRotateYMin;
	}
	unguard;
}

void wsCamera::Init3DCamera()
{
	guardfunc;
	FLOAT fAspect = ((FLOAT)SCREEN_WIDTH) / SCREEN_HEIGHT;
	IRenderer* RI = GetEngine()->GetRenderer();
	m_pCamera->SetProjParams( g_fCamerFOV, fAspect, theHeroGame.GetSwRender()->GetNearPlane(), theHeroGame.GetSwRender()->GetFarPlane() );//near,farplaneҲӦ�����������
	RI->SetTransform( D3DTS_PROJECTION, (FLOAT*)&m_pCamera->GetProjMatrix() );

	m_ViewPortMain.X = 0;
	m_ViewPortMain.Y = 0;
	m_ViewPortMain.Width = SCREEN_WIDTH;
	m_ViewPortMain.Height = SCREEN_HEIGHT;
	m_ViewPortMain.MinZ = 0;
	m_ViewPortMain.MaxZ = 1;
	RI->SetViewport( &m_ViewPortMain );

	unguard;
}



void wsCamera::Init2DCamera(void)
{
	LPDIRECT3DDEVICE9 pd3dDevice = theHeroGame.GetD3DDevice();

	if(!pd3dDevice)
		return;

	guardfunc;
	Init3DCamera();
	return;
	if( gCfg.m_bLocalVersion )
	{	
		Init3DCamera();
		return;
	}
	D3DXVECTOR3 vFromPt( 0.0f, 0.0f, m_fEyeToGroundDist );
	D3DXVECTOR3 vLookatPt( 0.0f, 0.0f, 0.0f );
	D3DXVECTOR3 vUpVec( 0.0f, 1.0f, 0.0f );
	m_pCamera->SetViewParams( vFromPt, vLookatPt, vUpVec );
	pd3dDevice->SetTransform( D3DTS_VIEW, (D3DXMATRIX*)&m_pCamera->GetViewMatrix() );	

	float asp = 1.0f;
	D3DXVECTOR3 v3Min( -(SCREEN_WIDTH/2), -(SCREEN_HEIGHT/2)/asp, 1 );
	D3DXVECTOR3 v3Max( SCREEN_WIDTH/2, (SCREEN_HEIGHT/2)/asp, m_fEyeToGroundDist*2 );
	m_pCamera->SetOrthoLH( v3Min, v3Max );

	pd3dDevice->SetTransform( D3DTS_PROJECTION, (D3DXMATRIX*)&m_pCamera->GetProjMatrix() );

	unguard;
}

void wsCamera::ResetViewport()
{
	if( theHeroGame.GetD3DDevice() )
		theHeroGame.GetD3DDevice()->SetViewport(&m_ViewPortMain); 
}

float wsCamera::GetCameraCollisionModelAlpha(const TObjectInfo *model)
{
	char modelname[MAX_PATH] = {0};

	MexAnimCtrl *animCtrl = model->model;
	if (animCtrl == NULL)
		return 1.0;

	strcpy(modelname, animCtrl->GetMex()->GetFilename());
	strlwr(modelname);
	if (strstr(modelname, "tree"))
		return 0.5;
	else
		return 0.6;
}