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
	//D3DXVECTOR3 m_vFaceDir; //���ĳ���    // ò��û�ã�ɾ��
	D3DXVECTOR3	m_vTargetPos; //Ŀ���
	D3DXVECTOR3 m_vLastTargetPos; //��һ��Ŀ���
	D3DXVECTOR3 m_vStartPos; //������
	D3DXVECTOR3 m_vStoTDir; //�����㵽Ŀ���ķ�������
	D3DXVECTOR3 m_vCurPos; //��ǰλ��
	DWORD m_dwKeepMovingStartTime;
	int m_nLockTargetID; //������Ŀ��ID
	BOOL m_bHaveLockTarget; //�Ƿ�������Ŀ��
	float m_f; //���㵱ǰλ�õ�ϵ��
	//float m_fDistPerSecond; //ÿ���λ��
	float m_fKeepDistance; //���ֵľ���
	//float m_fMoveRateCorrect; //�ƶ��ٶȵĽ���
	BOOL m_bKeepMoving; //�ڳ����ƶ�
	BOOL m_bMoveOver; //�ƶ�������־
	BOOL m_bMovingToTarget; //�ƶ���Ŀ��
	BOOL m_bNeedChangeDir; //�Ƿ�Ҫ�ı䳯��

    BOOL m_bHasTargetDir;       // �ƶ��������Ƿ���Ҫ�ı䳯��
    D3DXVECTOR3 m_vTargetDir;   // �ƶ�������ı䳯��
};