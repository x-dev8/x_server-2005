#include "CameraStuntManager.h"
#include "FuncPerformanceLog.h"
#include "wsCamera.h"
#include "SystemSetting.h"

extern DWORD HQ_TimeGetTime();
extern DWORD g_dwLastFrameCostTime;

CCameraStuntManager::CCameraStuntManager()
{
	guardfunc;
	m_vTheRolePos = D3DXVECTOR3( 0, 0, 0 );
	m_vViewDir    = D3DXVECTOR3( 0, 0, 0 );
	m_nLookatPosOffsetType = LPOT_NORMAL;
	m_fLookatPosMaxOffset = 0;
	m_fLookatPosMinOffset = 0;
	m_fLookatPosShakeCorrect = 0;
	m_dwLookatPosStartShakeTime = 0;
	m_dwLookatPosShakeKeepTime = 0;
	m_fDistance = 6.0f;
	m_fLastDistance = 0.0f;

	m_dwStartMovingCameraTime = 0;      //开始移动相机的时间
	m_dwMovingElapse = 800;               //移动间隔
	unguard;
}

CCameraStuntManager::~CCameraStuntManager()
{
	guardfunc;

	unguard;
}

void CCameraStuntManager::UpdateRolePos( D3DXVECTOR3 vRolePos,D3DXVECTOR3 vDir)
{
	guardfunc;
	m_vTheRolePos = vRolePos;
	m_vViewDir    = vDir;
	unguard;
}

D3DXVECTOR3 CCameraStuntManager::GetLookatPosOffset()
{
	guardfunc;
	if(IsCameraMoving())
		return D3DXVECTOR3( 0, 0, 0);

	int nElapse = 0;
	if(m_nLookatPosOffsetType == LPOT_VIEWDIR)
		nElapse = m_dwMovingElapse;

	if( HQ_TimeGetTime() - m_dwLookatPosStartShakeTime - nElapse < m_dwLookatPosShakeKeepTime )
	{
		D3DXVECTOR3 vLookatPosOffset = D3DXVECTOR3( 0, 0, 0 );
		switch( m_nLookatPosOffsetType )
		{
		case LPOT_NORMAL:
			vLookatPosOffset = D3DXVECTOR3( rand()%1024, rand()%1024, rand()%1024 );
			break;
		case LPOT_HORIZONTAL:
			vLookatPosOffset = D3DXVECTOR3( rand()%1024, rand()%1024, 0 );
			break;
		case LPOT_VERTICAL:
			vLookatPosOffset = D3DXVECTOR3( 0, 0, rand()%1024 );
			break;
		case LPOT_VIEWDIR:
			vLookatPosOffset = m_vViewDir;
			break;
        default:
            break;
		}

		D3DXVec3Normalize( &vLookatPosOffset, &vLookatPosOffset );
		float fShakeRange = m_fLookatPosMinOffset + (float)(rand()%1024)/1024*( m_fLookatPosMaxOffset - m_fLookatPosMinOffset );
		vLookatPosOffset = vLookatPosOffset*fShakeRange*m_fLookatPosShakeCorrect;
		return vLookatPosOffset;
	}

	m_nLookatPosOffsetType = LPOT_NORMAL;
	if(m_fLastDistance != 0)
	{
		getwsCamera()->SetCurCameraZoom(m_fLastDistance);
		m_fLastDistance = 0;
	}

	return D3DXVECTOR3( 0, 0, 0 );
	unguard;
}

void CCameraStuntManager::StartRandShake( D3DXVECTOR3 vShakePos,			//震动点
										  float fMaxShakeWaveRange,			//震波影响最弱的范围
										  float fMinShakeWaveRange,			//震波影响最强的范围
										  float fMaxShakeRange,				//最大振幅
										  float fMinShakeRange,				//最小振幅
										  DWORD dwShakeKeepTime,			//震动维持时间
										  int	nShakeType ,int nCurZoom /*= 0*/)				//振动类型
{
	guardfunc;
	if (!SystemSetting::Instance()->GetLevel(SystemSetting::eSSC_CameraShake))
		return;

	if( fMaxShakeWaveRange < 0 || fMinShakeWaveRange < 0 || fMaxShakeRange < 0 || fMinShakeRange < 0 )
		return;

	if( fMinShakeWaveRange > fMaxShakeWaveRange )
		fMinShakeWaveRange = fMaxShakeWaveRange;

	if( fMinShakeRange > fMaxShakeRange )
		fMinShakeRange = fMaxShakeRange;

	D3DXVECTOR3 vRolePosToShakePosOffset = vShakePos - m_vTheRolePos;
	vRolePosToShakePosOffset.z = 0;
	float fDistanceToShakePos = D3DXVec3Length( &vRolePosToShakePosOffset );

	if( fDistanceToShakePos >= fMaxShakeWaveRange )
		return;

	if( fDistanceToShakePos <= fMinShakeWaveRange || fMaxShakeWaveRange - fMinShakeWaveRange == 0 )
		m_fLookatPosShakeCorrect = 1;
	else
		m_fLookatPosShakeCorrect = ( fDistanceToShakePos - fMinShakeWaveRange )/(fMaxShakeWaveRange - fMinShakeWaveRange);

	m_nLookatPosOffsetType = nShakeType;
	m_fLookatPosMaxOffset = fMaxShakeRange;
	m_fLookatPosMinOffset = fMinShakeRange;
	m_dwLookatPosStartShakeTime = HQ_TimeGetTime();
	m_dwLookatPosShakeKeepTime = dwShakeKeepTime;
	m_fLastDistance = nCurZoom;

	m_dwStartMovingCameraTime = HQ_TimeGetTime();
	unguard;
}

void CCameraStuntManager::StartRandShake( float fMaxShakeRange,
										 float fMinShakeRange,
										 DWORD dwShakeKeepTime,
										 int nShakeType /* = LPOT_NORMAL  */,int nCurZoom/* = 0*/)
{
	guardfunc;
	if (!SystemSetting::Instance()->GetLevel(SystemSetting::eSSC_CameraShake))
		return;

	if( fMaxShakeRange < 0 || fMinShakeRange < 0 )
		return;

	if( fMinShakeRange > fMaxShakeRange )
		fMinShakeRange = fMaxShakeRange;

	m_fLookatPosShakeCorrect = 1;
	m_nLookatPosOffsetType = nShakeType;
	m_fLookatPosMaxOffset = fMaxShakeRange;
	m_fLookatPosMinOffset = fMinShakeRange;
	m_dwLookatPosStartShakeTime = HQ_TimeGetTime();
	m_dwLookatPosShakeKeepTime = dwShakeKeepTime;

	m_fLastDistance = nCurZoom;

	m_dwStartMovingCameraTime = HQ_TimeGetTime();
	unguard;
}

void CCameraStuntManager::ProcessSmothMove(float &fLen)
{
	if(!IsCameraMoving())
		return;

	if(fLen > m_fDistance)
	{
		fLen -= g_dwLastFrameCostTime * 0.00618f;
		if( fLen < m_fDistance )
			fLen = m_fDistance;
	}
	else if(fLen < m_fDistance)
	{
		fLen += g_dwLastFrameCostTime * 0.00618f;
		if(fLen > m_fDistance)
			fLen = m_fDistance;
	}
}

bool CCameraStuntManager::IsCameraMoving()
{
	if(m_nLookatPosOffsetType != LPOT_VIEWDIR)
		return false;

	if(HQ_TimeGetTime() - m_dwStartMovingCameraTime > m_dwMovingElapse)
		return false;

	return true;
}
