#include "ActionManager.h"
#include "FuncPerformanceLog.h"
#include "shortcutkey_configure.h"

extern DWORD HQ_TimeGetTime();

CActionManager::CActionManager()
{
	guardfunc;
	m_deGameActionOperation.clear();
	unguard;
}

CActionManager::~CActionManager()
{
	guardfunc;
	m_deGameActionOperation.clear();
	unguard;
}

bool CActionManager::Push_NormalAction( int nActionID, DWORD dwPushTime )
{
	guardfunc;
	if( nActionID < 0 )
		return false;

	int nSize = m_deGameActionOperation.size();

	for( int i = 0; i < nSize; i++ )
	{
		if( m_deGameActionOperation[i].nActionID == nActionID)
		{
			m_deGameActionOperation[i].dwPushTime = dwPushTime;
			return true;
		}
	}

	SGameActionOperation gameactionoperation;
	gameactionoperation.nActionID = nActionID;
	gameactionoperation.stType = 0;
	gameactionoperation.dwPushTime = dwPushTime;
	m_deGameActionOperation.push_back( gameactionoperation );
	return true;
	unguard;
}

bool CActionManager::Push_ActionBackToDeque( SGameActionOperation gameactionoperation )
{
	guardfunc;
	if( HQ_TimeGetTime() - gameactionoperation.dwPushTime < 300 )
		m_deGameActionOperation.push_back( gameactionoperation );
	else
		return false;

	return true;
	unguard;
}

bool CActionManager::Push_OperationBackToDeque( SGameActionOperation gameactionoperation )
{
	guardfunc;
	if( HQ_TimeGetTime() - gameactionoperation.dwPushTime < 1000 )
		m_deGameActionOperation.push_back( gameactionoperation );
	else
		return false;

	return true;
	unguard;
}

bool CActionManager::PopNextAction( SGameActionOperation &gameactionoperation )
{
	guardfunc;
	int nSize = m_deGameActionOperation.size();

	if( nSize < 1 )
		return false;

	gameactionoperation = m_deGameActionOperation[0];
	m_deGameActionOperation.pop_front();
	return true;
	unguard;
}

bool CActionManager::Push_UseSkillOperation( GameObjectId TargetID, int nSkillID, int nSkillLevel, DWORD dwPushTime )
{
	guardfunc;
	int nSize = m_deGameActionOperation.size();
	for( int i = 0; i < nSize; i++ )
	{
		if( m_deGameActionOperation[i].nActionID == AN_Configure_ShortcutKey::AN_SCKC_useSkill_operator)
		{
			m_deGameActionOperation[i].dwPushTime = dwPushTime;
			SUseSkillOperation UseSkillOperation;
			UseSkillOperation.SkillTargetID = TargetID;
			UseSkillOperation.nSkillID = nSkillID;
			UseSkillOperation.nSkillLevel = nSkillLevel;
			memcpy( m_deGameActionOperation[i].szOperationData, &UseSkillOperation, min(sizeof(SUseSkillOperation), sizeof(m_deGameActionOperation[i].szOperationData)));
			return true;
		}
	}

	SGameActionOperation gameactionoperation;
	gameactionoperation.nActionID = AN_Configure_ShortcutKey::AN_SCKC_useSkill_operator;
	gameactionoperation.stType = 0;
	gameactionoperation.dwPushTime = dwPushTime;
	SUseSkillOperation UseSkillOperation;
	UseSkillOperation.SkillTargetID = TargetID;
	UseSkillOperation.nSkillID = nSkillID;
	UseSkillOperation.nSkillLevel = nSkillLevel;
	memcpy( gameactionoperation.szOperationData, &UseSkillOperation, min(sizeof(SUseSkillOperation), sizeof(gameactionoperation.szOperationData)));

	m_deGameActionOperation.push_back( gameactionoperation );
	return true;
	unguard;
}

void CActionManager::Clear()
{
	m_deGameActionOperation.clear();
}