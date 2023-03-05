#include "MonsterAITrigger.h"

CMonsterAITrigger::CMonsterAITrigger()
{

}

CMonsterAITrigger::~CMonsterAITrigger()
{

}

void CMonsterAITrigger::AddMonsterAITrigger()
{
	SMonsterTrigger mt;
	m_vectorMonsterAITriggerStore.push_back( mt );
}

void CMonsterAITrigger::AddMonsterAITrigger( SMonsterTrigger mt )
{
	m_vectorMonsterAITriggerStore.push_back( mt );
}

int CMonsterAITrigger::GetMaxMonsterAITrigger()
{
	return (int)m_vectorMonsterAITriggerStore.size();
}

SMonsterTrigger* CMonsterAITrigger::GetMonsterAITriggerByID( int id )
{
	if( id < 0 || id >= (int)m_vectorMonsterAITriggerStore.size() )
		return NULL;

	return &m_vectorMonsterAITriggerStore[id];
}

void CMonsterAITrigger::Clear()
{
	m_vectorMonsterAITriggerStore.clear();
}