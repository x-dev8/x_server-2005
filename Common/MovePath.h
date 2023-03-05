#pragma once

class CMovePath
{
public:
	CMovePath();
	virtual ~CMovePath();
	BOOL SetStartPosAndTargetPos( float sX, float sY, float tX, float tY, BOOL bKeepMoving, BOOL bNeedFilter = TRUE);
	BOOL SetLockTarget( short shLockTargetID, float fKeepDistance );
	BOOL SetContinueMoving( float fDirX, float fDirY, float fTurnSpeed, short shMovingType );
	void GetCurPosAndDir( float* x, float* y, float* d, float* s, float fMoveRate, int nSmoothFrame );
	void GetPlayerCurPos( float* x, float* y, float fCurMoveRate, int nSmoothFrame );
    void SetTargetDir( D3DXVECTOR3 vTargetDir ) { m_bHasTargetDir = TRUE; m_vTargetDir = vTargetDir; }
    void ClearTargetDir() { m_bHasTargetDir = FALSE; }

	void UpdateLockTargetPos( D3DXVECTOR3 vTargetPos );
	void SetMoveOver();
	int GetLockTargetID();
	BOOL HaveLockTarget();
	void LostLockTarget();
	BOOL NeedClosingToLockTarget();
	BOOL IsMoveOver();
	BOOL IsNeedChangeDir();
	D3DXVECTOR3 GetTargetPos();
    BOOL HasTargetDir(D3DXVECTOR3& vTargetDir);

private:
	//D3DXVECTOR3 m_vFaceDir; //脸的朝向    // 貌似没用，删除
	D3DXVECTOR3	m_vTargetPos; //目标点
	D3DXVECTOR3 m_vLastTargetPos; //上一个目标点
	D3DXVECTOR3 m_vStartPos; //出发点
	D3DXVECTOR3 m_vStoTDir; //出发点到目标点的方向向量
	D3DXVECTOR3 m_vCurPos; //当前位置
	DWORD m_dwKeepMovingStartTime;
	int m_nLockTargetID; //锁定的目标ID
	BOOL m_bHaveLockTarget; //是否有锁定目标
	float m_f; //计算当前位置的系数
	//float m_fDistPerSecond; //每秒的位移
	float m_fKeepDistance; //保持的距离
	//float m_fMoveRateCorrect; //移动速度的矫正
	BOOL m_bKeepMoving; //在持续移动
	BOOL m_bMoveOver; //移动结束标志
	BOOL m_bMovingToTarget; //移动到目标
	BOOL m_bNeedChangeDir; //是否要改变朝向

    BOOL m_bHasTargetDir;       // 移动结束后是否需要改变朝向
    D3DXVECTOR3 m_vTargetDir;   // 移动结束后改变朝向
};