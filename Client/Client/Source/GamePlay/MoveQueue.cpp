#include "MoveQueue.h"
#include "FuncPerformanceLog.h"

extern DWORD HQ_TimeGetTime();

CMoveQueue::CMoveQueue()
{
	guardfunc;
	m_veMove.clear();
	unguard;
}

CMoveQueue::~CMoveQueue()
{
	guardfunc;
	unguard;
}

BOOL CMoveQueue::Push_Move( SMove &move )
{
	guardfunc;
	move.dwPushTime = HQ_TimeGetTime();
	m_veMove.push_back( move );
	return TRUE;
	unguard;
}

int CMoveQueue::Size()
{
	guardfunc;
	return m_veMove.size();
	unguard;
}

void CMoveQueue::Clear()
{
	guardfunc;
	m_veMove.clear();
	unguard;
}

BOOL CMoveQueue::PopNextMove( SMove &move )
{
	guardfunc;
	int nSize = m_veMove.size();

	if( nSize < 1 )
		return FALSE;

	move = m_veMove[0];
	m_veMove.pop_front();
	return TRUE;
	unguard;
}

BOOL CMoveQueue::Push_KeepMovingToPos( float x, float y, float dx, float dy )
{
	guardfunc;
	SMove move;
	move.dwSerialNo = HQ_TimeGetTime();
	move.stType = M_KEEPMOVINGTOPOS;
	move.vTargetPos.x = x;
	move.vTargetPos.y = y;
	move.vDir.x = dx;
	move.vDir.y = dy;
	return Push_Move( move );
	unguard;
}

BOOL CMoveQueue::Push_MovingToPos( float x, float y, float dx, float dy )
{
	guardfunc;
	SMove move;
	move.dwSerialNo = HQ_TimeGetTime();
	move.stType = M_MOVINGTOPOS;
	move.vTargetPos.x = x;
	move.vTargetPos.y = y;
	move.vDir.x = dx;
	move.vDir.y = dy;
	return Push_Move( move );
	unguard;
}

BOOL CMoveQueue::Push_MovingToTarget( int nTargetID, float fKeepDistance )
{
	guardfunc;
	SMove move;
	move.dwSerialNo = HQ_TimeGetTime();
	move.stType = M_MOVINGTOLOCKTARGET;
	move.nTargetID = nTargetID;
	move.fKeepDistance = fKeepDistance;
	return Push_Move( move );
	unguard;
}

BOOL CMoveQueue::Push_PlayerMovingDirAndType( D3DXVECTOR3 vDir, short shMovingType )
{
	guardfunc;
	SMove move;
	move.dwSerialNo = HQ_TimeGetTime();
	move.stType = M_PLAYERMOVINGDIRANDTYPE;
	move.vDir = vDir;
	move.shMovingType = shMovingType;
	return Push_Move( move );
	unguard;
}

BOOL CMoveQueue::Push_PlayerMovingType( short shMovingType)
{
	guardfunc;
	return TRUE;
	unguard;
}

BOOL CMoveQueue::PushPlayerKeepMovingPassPos( D3DXVECTOR3 vPos )
{
	guardfunc;
	SMove move;
	move.dwSerialNo = HQ_TimeGetTime();
	move.stType = M_PLAYERKEEPMOVINGPOS;
	move.vTargetPos = vPos;
	return Push_Move( move );
	unguard;
}

BOOL CMoveQueue::PushPlayerKeepMovingPassPos( D3DXVECTOR3 vPos, D3DXVECTOR3 vDir )
{
	guardfunc;
	SMove move;
	move.dwSerialNo = HQ_TimeGetTime();
	move.stType = M_PLAYERKEEPMOVINGPOSANDDIR;
	move.vTargetPos = vPos;
	move.vDir = vDir;
	return Push_Move( move );
	unguard;
}

BOOL CMoveQueue::PushPlayerKeepMovingPassPos_TargetDir( D3DXVECTOR3 vPos, D3DXVECTOR3 vDir )
{
    guardfunc;
    SMove move;
    move.dwSerialNo = HQ_TimeGetTime();
    move.stType = M_PLAYERKEEPMOVINGPOSANDDIR_FINDPATH;
    move.vTargetPos = vPos;
    move.vDir = vDir;
    return Push_Move( move );
    unguard;
}

BOOL CMoveQueue::PushPlayerPos( D3DXVECTOR3 vPos )
{
	guardfunc;
	SMove move;
	move.dwSerialNo = HQ_TimeGetTime();
	move.stType = M_PLAYERPOS;
	move.vTargetPos = vPos;
	return Push_Move( move );
	unguard;
}

BOOL CMoveQueue::PushPlayerDir( D3DXVECTOR3 vDir )
{
	guardfunc;
	SMove move;
	move.dwSerialNo = HQ_TimeGetTime();
	move.stType = M_PLAYERDIR;
	move.vDir = vDir;
	return Push_Move( move );
	unguard;
}

BOOL CMoveQueue::PushPlayerPosAndDir( D3DXVECTOR3 vPos, D3DXVECTOR3 vDir )
{
	guardfunc;
	SMove move;
	move.dwSerialNo = HQ_TimeGetTime();
	move.stType = M_PLAYERPOSANDDIR;
	move.vTargetPos = vPos;
	move.vDir = vDir;
	return Push_Move( move );
	unguard;
}