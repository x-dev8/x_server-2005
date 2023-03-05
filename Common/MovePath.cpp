#include "Dxsdk/d3dx9.h"
#include <stdio.h>
#include "MovePath.h"
#include "FuncPerformanceLog.h"
//
int g_nSendMovingMessageRate = 250; //服务器每次下发移动消息的频率
extern DWORD g_dwLastFrameCostTime;

CMovePath::CMovePath()
{
	guardfunc;
	m_f = 0.0f;
	//m_fDistPerSecond = 0.0f;
	m_fKeepDistance = 0.0f;
	//m_fMoveRateCorrect = 1.0f;
	m_dwKeepMovingStartTime = 0;
	m_bKeepMoving = FALSE;
	m_bMoveOver = TRUE;
	m_bMovingToTarget = FALSE;
	m_bNeedChangeDir = TRUE;
    m_bHasTargetDir = FALSE;

	//m_vFaceDir				= D3DXVECTOR3( 0, 0, 0 ); //脸的朝向
	m_vTargetPos			= D3DXVECTOR3( 0, 0, 0 ); //目标点
	m_vLastTargetPos		= D3DXVECTOR3( 0, 0, 0 ); //上一个目标点
	m_vStartPos				= D3DXVECTOR3( 0, 0, 0 ); //出发点
	m_vCurPos				= D3DXVECTOR3( 0, 0, 0 ); //当前位置
	m_vStoTDir				= D3DXVECTOR3( 0, 0, 0 );
    m_vTargetDir            = D3DXVECTOR3( 0, 0, 0 );
	unguard;
}

CMovePath::~CMovePath()
{

}

BOOL CMovePath::SetContinueMoving( float fDirX, float fDirY, float fTurnSpeed, short shMovingType )
{
	guardfunc;
	m_bKeepMoving = TRUE;

	//m_vFaceDir.x = fDirX;
	//m_vFaceDir.y = fDirY;

	m_bMoveOver = FALSE;

	return TRUE;
	unguard;
}

BOOL CMovePath::SetStartPosAndTargetPos( float sX, float sY, float tX, float tY, BOOL bKeepMoving, BOOL bNeedFilter /* = TRUE  */)
{
	guardfunc;
	m_bKeepMoving = bKeepMoving;

	/*if( bNeedFilter )
	{
		if( abs(sX - tX) < 0.618f && abs(sY - tY) < 0.618f )
		{
			return FALSE;
		}

		if( abs(m_vTargetPos.x - tX) < 0.618f && abs(m_vTargetPos.y - tY) < 0.618f )
		{
			return FALSE;
		}
	}*/
    if( abs(sX - tX) < 0.001f && abs(sY - tY) < 0.001f )
    {
        return FALSE;
    }

	float fPosXOff = 0;
	float fPosYOff = 0;
	m_f = 0.0f;
	m_vLastTargetPos = m_vTargetPos;
	m_vStartPos.x = sX;
	m_vStartPos.y = sY;
	m_vTargetPos.x = tX;
	m_vTargetPos.y = tY;
	m_bMoveOver = FALSE;
	m_bMovingToTarget = FALSE;
	m_dwKeepMovingStartTime = HQ_TimeGetTime();
	m_fKeepDistance = 0;
	m_vStoTDir.x = tX - sX;
	m_vStoTDir.y = tY - sY;
	fPosXOff = tX - sX;
	fPosYOff = tY - sY;
    m_bHasTargetDir = FALSE;
	//float fDistance = sqrtf( fPosXOff*fPosXOff + fPosYOff*fPosYOff );

	//m_fMoveRateCorrect = 1;
	//int nMoveRateAdd = fDistance;
	//m_fMoveRateCorrect += (float)nMoveRateAdd*0.2f;

	if( abs(sX - tX) < 0.00618f && abs(sY - tY) < 0.00618f )
	{
		m_bNeedChangeDir = FALSE;
	}
	else
	{
		m_bNeedChangeDir = TRUE;
	}

	D3DXVec3Normalize( &m_vStoTDir, &m_vStoTDir );

	return TRUE;
	unguard;
}

BOOL CMovePath::SetLockTarget( short shLockTargetID, float fKeepDistance )
{
	guardfunc;
	m_bMoveOver = FALSE;
	m_bMovingToTarget = TRUE;
	m_fKeepDistance = fKeepDistance;
	m_nLockTargetID = shLockTargetID;
	m_bNeedChangeDir = TRUE;
	m_bHaveLockTarget = TRUE;
	return TRUE;
	unguard;
}

void CMovePath::GetCurPosAndDir( float* x, float* y, float* d, float* s, float fMoveRate, int nSmoothFrame )
{
	guardfunc;
	/////////////////////////////////////////////////////////////
	float fCurMoveDist = fMoveRate*nSmoothFrame/1000;
	m_vCurPos.x = *x;
	m_vCurPos.y = *y;
	float fXOff = m_vTargetPos.x - m_vCurPos.x;
	float fYOff = m_vTargetPos.y - m_vCurPos.y;
	float fTotalDist = sqrtf( fXOff*fXOff + fYOff*fYOff );

	if( fTotalDist == 0.0f )
	{
		m_bMoveOver = TRUE;
		return ;
	}

	float f1 = fCurMoveDist/fTotalDist;

	if( fTotalDist < m_fKeepDistance )
	{
		m_bMoveOver = TRUE;
	}
	else
	{
		if( f1 >= 1 )
		{
			m_bMoveOver = TRUE;
			m_vCurPos = m_vTargetPos;
		}
		else
		{
			m_vCurPos = m_vCurPos + f1*(m_vTargetPos - m_vCurPos);
		}
	}

	///////////////////////////////
	//if( NeedClosingToLockTarget() )
	//{
	//	m_bMoveOver = FALSE;
	//}

	*d = atan2f(fYOff,fXOff);
	*x = m_vCurPos.x;
	*y = m_vCurPos.y;
	unguard;
}

void CMovePath::GetPlayerCurPos( float* x, float* y, float fCurMoveRate, int nSmoothFrame )
{
	guardfunc;
	m_vCurPos.x = *x;
	m_vCurPos.y = *y;

	// 是否已经穿过的要移动的目标点
	bool bPassedTargerPos = false;
	if( m_vTargetPos.x > m_vStartPos.x && m_vCurPos.x > m_vTargetPos.x )
	{
		bPassedTargerPos = true;
	}

	if( !bPassedTargerPos )
	{
		if( m_vTargetPos.x < m_vStartPos.x && m_vCurPos.x < m_vTargetPos.x )
		{
			bPassedTargerPos = true;
		}
	}

	if( !bPassedTargerPos )
	{
		if( m_vTargetPos.y < m_vStartPos.y && m_vTargetPos.y > m_vCurPos.y )
		{
			bPassedTargerPos = true;
		}
	}

	if( !bPassedTargerPos )
	{
		if( m_vTargetPos.y < m_vStartPos.y && m_vTargetPos.y > m_vCurPos.y )
		{
			bPassedTargerPos = true;
		}
	}

	if( bPassedTargerPos )
	{
		m_bMoveOver = TRUE;
        m_vCurPos = m_vTargetPos;
		return;
	}
	
	float fCurMoveDist = fCurMoveRate*nSmoothFrame/1000;
	float fTotalDist;

	//if( bPassedTargerPos )
	//{
	//	fTotalDist = D3DXVec3Length( &(m_vTargetPos - m_vLastTargetPos) );
	//}
	//else
	//{
	//	fTotalDist = D3DXVec3Length( &(m_vTargetPos - m_vStartPos) );
	//}

	fTotalDist = D3DXVec3Length( &(m_vTargetPos - m_vStartPos) );
	float fCurDist = D3DXVec3Length( &(m_vTargetPos - m_vCurPos) );
	float f1 = 0;

	//if( fCurDist > fCurMoveRate*0.618f )
	//{
	//	if( fTotalDist > fCurMoveRate*0.618f )
	//	{
	//		f1 = (fTotalDist-fCurMoveRate*0.618f)/fTotalDist;
	//	}
	//	else
	//	{
	//		f1 = fCurMoveDist/fTotalDist;
	//	}
	//}
	//else
	{
		f1 = fCurMoveDist/fTotalDist;
	}


	if( f1 >= 1 )
	{
		// 设为目标位置
		//*x = m_vTargetPos.x;
		//*y = m_vTargetPos.y;
		m_bMoveOver = TRUE;
		
        //return;
        m_vCurPos = m_vTargetPos;
	}
	else
	{
		//if( bPassedTargerPos )
		//	m_vCurPos = m_vCurPos + f1*(m_vTargetPos - m_vLastTargetPos);
		//else
		//	m_vCurPos = m_vCurPos + f1*(m_vTargetPos - m_vStartPos);

		m_vCurPos = m_vCurPos + f1*(m_vTargetPos - m_vStartPos);
	}

	*x = m_vCurPos.x;
	*y = m_vCurPos.y;

	//if( bPassedTargerPos )
	//{
	//	float fDistanceToTargetPos = D3DXVec3LengthSq( &( m_vCurPos - m_vTargetPos ) );

	//	if( fDistanceToTargetPos > 20 )
	//	{
	//		m_bMoveOver = TRUE;
	//		*x = m_vTargetPos.x;
	//		*y = m_vTargetPos.y;
	//	}
	//}
	return;


	////////////////////////old project
	//float fCurMoveDist = fCurMoveRate*nSmoothFrame/1000;
	//m_vCurPos.x = *x;
	//m_vCurPos.y = *y;
	//float fXOff = m_vTargetPos.x - m_vCurPos.x;
	//float fYOff = m_vTargetPos.y - m_vCurPos.y;
	//float fTotalDist = sqrtf( fXOff*fXOff + fYOff*fYOff );

	//if( fTotalDist == 0.0f )
	//{
	//	m_bMoveOver = TRUE;
	//	return ;
	//}

	//float f1 = fCurMoveDist/fTotalDist;

	//if( fTotalDist < m_fKeepDistance )
	//{
	//	m_bMoveOver = TRUE;
	//}
	//else
	//{
	//	if( f1 >= 1 )
	//	{
	//		m_bMoveOver = TRUE;
	//		m_vCurPos = m_vTargetPos;
	//	}
	//	else
	//	{
	//		m_vCurPos = m_vCurPos + f1*(m_vTargetPos - m_vCurPos);
	//	}
	//}

	//*x = m_vCurPos.x;
	//*y = m_vCurPos.y;
	unguard;
}

BOOL CMovePath::IsMoveOver()
{
	guardfunc;
	return m_bMoveOver;
	unguard;
}

BOOL CMovePath::HaveLockTarget()
{
	guardfunc;
	return m_bHaveLockTarget;
	unguard;
}

void CMovePath::LostLockTarget()
{
	guardfunc;
	m_bHaveLockTarget = FALSE;
	unguard;
}

BOOL CMovePath::NeedClosingToLockTarget()
{
	guardfunc;
	if( m_bMovingToTarget && m_nLockTargetID >= 0 )
	{
		return TRUE;
	}
	return FALSE;
	unguard;
}

void CMovePath::UpdateLockTargetPos( D3DXVECTOR3 vTargetPos )
{
	guardfunc;
	m_vTargetPos = vTargetPos;
	unguard;
}

void CMovePath::SetMoveOver()
{
	guardfunc;
	m_bMoveOver = TRUE;
	unguard;
}

int CMovePath::GetLockTargetID()
{
	guardfunc;
	return m_nLockTargetID;
	unguard;
}

BOOL CMovePath::IsNeedChangeDir()
{
	guardfunc;
	return m_bNeedChangeDir;
	unguard;
}

D3DXVECTOR3 CMovePath::GetTargetPos()
{
	guardfunc;
	return m_vTargetPos;
	unguard;
}

BOOL CMovePath::HasTargetDir( D3DXVECTOR3& vTargetDir )
{
    if( m_bHasTargetDir )
    {
        vTargetDir = m_vTargetDir;
        return TRUE;
    }
    return FALSE;
}