	
#include "Me3d\include.h"
#include "Me3d/MoreAction.h"
#include "Me3d/AnimTimeline.h"
#include "Stdcharskeleton.h"
#include "Me3d/Model/MexAnimCtrl.h"
#include "actionqueue.h"
#include "player.h"
#include "playerrole.h"
#include "playeranimctrl.h"
#include "gamemain.h"
#include "effect.h"
#include <assert.h>

#include "ui/ChatInfoBox.h"


#include "FuncPerformanceLog.h"
extern DWORD HQ_TimeGetTime();


extern CHeroGame* theApp;
CActionQueue::CActionQueue(void)
{
	guardfunc;
	unguard;
}

CActionQueue::~CActionQueue(void)
{
	guardfunc;
	unguard;
}

void CActionQueue::Clear(void)
{
	guardfunc;
	m_deAction.clear();
	unguard;
}

void CActionQueue::SkipAllWalkAction()
{
	guardfunc;
	for( int i = 0; i < m_deAction.size(); i++ )
	{
		if( m_deAction[i].stType == A_WALK )
			m_deAction[i].bSkip = true;
	}
	unguard;
}

void CActionQueue::SkipAllWalkActionBefore( DWORD dwSerialNo )
{
	guardfunc;
	for( int i = 0; i < m_deAction.size(); i++ )
	{
		if( m_deAction[i].stType == A_WALK &&
			m_deAction[i].dwSerialNo == dwSerialNo )
		{
			int k = 0;
		}
		else if( m_deAction[i].stType == A_WALK &&
			m_deAction[i].dwSerialNo <= dwSerialNo )
			m_deAction[i].bSkip = true;
		else
		{
			int k = 0;
		}
	}
	unguard;
}
bool CActionQueue::PopNextAction( SAction &action )
{
	guardfunc;
	if( m_deAction.size() <= 0 )
		return false;
	int k = m_deAction.size();
	action = m_deAction[0];
	m_deAction.pop_front();
	return true;
	unguard;
}

bool CActionQueue::PopToAttackFromEnd()
{
	guardfunc;
	int nSize = m_deAction.size();
	int i = 0;
	for( i = nSize-1; i >= 0; i-- )
	{
		if( m_deAction[i].stType == A_ATTACKEX )
			break;
	}
	if( i < 0 )
		return false;
	for( int j = nSize - 1 ; j > i ; j -- )
	{
		m_deAction.pop_back();
	}
	return true;
	unguard;
}

bool CActionQueue::Push_Action( SAction & action )
{
	guardfunc;

	action.dwPushTime = HQ_TimeGetTime();
	m_deAction.push_back( action );
	return true;
	unguard;
}

bool CActionQueue::PushFront_Action( SAction & action )
{
	guardfunc;
	action.dwPushTime = HQ_TimeGetTime();
	m_deAction.push_front( action );
	return true;
	unguard;
}

bool CActionQueue::Push_Expression(ExpressionInfo* pInfo)
{
	guardfunc;
    if( !pInfo )
        return false;

	SAction action;
	//
	action.dwSerialNo = pInfo->dwSerialNo;
	action.stType = A_EXPRESSION;
	memcpy(action.sData, pInfo, sizeof(ExpressionInfo));
	return Push_Action( action );
	unguard;
}

bool CActionQueue::Push_Intonate( IntonateInfo* pIntonate)
{
	guardfunc;
    if( !pIntonate )
        return false;

	SAction action;
	//
	pIntonate->dwSerialNo = HQ_TimeGetTime();
	action.dwSerialNo = pIntonate->dwSerialNo;
	action.stType = A_INTONATE;
	memcpy(action.sData, pIntonate, sizeof(IntonateInfo));
	return Push_Action( action );
	unguard;
}

bool CActionQueue::Push_SeeHoldSkill( SSeeHoldSkill* pSee )
{
	guardfunc;
    if( !pSee )
        return false;

	SAction action;
	action.stType = A_SEEHOLDSKILL;
	memcpy( action.sData,pSee,sizeof( SSeeHoldSkill ) );
	return Push_Action( action );
	unguard;
}

bool CActionQueue::Push_HoldSkillStart( IntonateEndInfo* pIntoend )
{
	guardfunc;
    if( !pIntoend )
        return false;

	SAction action;
	action.stType = A_STARTHOLDSKILL;
	memcpy( action.sData, pIntoend, sizeof( IntonateEndInfo ) );
	return Push_Action( action );
	unguard;
}
bool CActionQueue::Push_HoldSkillEnd()
{
	guardfunc;
	SAction action;
	action.stType = A_ENDHOLDSKILL;
	return Push_Action( action );
	unguard;
}
bool CActionQueue::Push_HoldSkillOneHit()
{
	guardfunc;
	return false;
	unguard;
}
bool CActionQueue::Push_CancelSkill()
{
	guardfunc;
	SAction action;
	action.stType = A_CANCELSKILL;
	return Push_Action( action );
	unguard;
}

bool CActionQueue::Push_BeAttacked()
{
	guardfunc;
	return true;
	unguard;
}

bool CActionQueue::Push_Attack(SAttackInfo* pAttackInfo )
{
	guardfunc;
    if( !pAttackInfo )
        return false;

	SAction action;
	//
	pAttackInfo->dwSerialNo = HQ_TimeGetTime();
	action.dwSerialNo = pAttackInfo->dwSerialNo;
	action.stType = A_ATTACKEX;
	//只保存AttackInfo的指针
	memcpy( action.sData, &pAttackInfo, sizeof( SAttackInfo* ) );
	return Push_Action( action );
	unguard;
}
bool CActionQueue::Push_Walk( unsigned char ucDir )
{
	guardfunc;
	SAction action;
	assert( sizeof( SWalk) < const_iMaxActionSize );
	action.dwSerialNo = HQ_TimeGetTime();

	SWalk *pWalk = (SWalk*)action.sData;
	action.stType= A_WALK;
	pWalk->ucDir = ucDir;
	return Push_Action( action );
	unguard;
}

bool CActionQueue::Push_Death()
{
	guardfunc;
	SAction action;
	SDeath* pDeath = (SDeath*)&action;
	action.stType = A_DEATH;
	
	return Push_Action( action );
	unguard;
}

int CActionQueue::GetAttackActionNum()
{
	int count = 0;
	if( m_deAction.size() )
	{
		for(UINT i=0; i<m_deAction.size(); i++)
		{
			SAction* pAction;
			pAction = &m_deAction[i];
			if( pAction->stType == A_INTONATE
				|| pAction->stType == A_ATTACKEX
				|| pAction->stType == A_DEATH
				|| pAction->stType == A_STARTHOLDSKILL
				|| pAction->stType == A_ENDHOLDSKILL
				|| pAction->stType == A_CANCELSKILL
				|| pAction->stType == A_BEATTACKED )
				count++;
		}
	}
	return count;
}

extern POINT GetNextPos( int x, int y, BYTE dir );

// 所有任务的时间原点
//-------------------------------------------------------------------------
//	End.
//-------------------------------------------------------------------------



