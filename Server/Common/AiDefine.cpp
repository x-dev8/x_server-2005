#include "AiDefine.h"
#include "GameDefineGlobal.h"
#include "GameTime.h"

unsigned int AiEnmity::AddEnmity( GameObjectId nID, unsigned int nEnmity, unsigned int nDamage, int nReductionRate )
{
	bool blNewEnmityTarget = false;
    TargetEnmityMapIter iter = m_mapTargetEnmity.find( nID );
    if ( iter == m_mapTargetEnmity.end() )
    {
        iter = m_mapTargetEnmity.insert( std::make_pair( nID, EnmityData() ) ).first;
        if ( iter == m_mapTargetEnmity.end() )
        { return AiDefine::NoneEnmity; }

		if ( nEnmity > 0 )
		{ blNewEnmityTarget = true; }
    }
	else
	{
		if ( ! iter->second.HaveEnmity() && nEnmity > 0 )
		{ blNewEnmityTarget = true; }
	}

    iter->second.AddEnmity( nEnmity );
    float fReductionRate = static_cast< float >( nReductionRate ) / static_cast< float >( AiDefine::EnmityBaseRate );
    iter->second.SetReduction( iter->second.GetEnmity() * fReductionRate );
    iter->second.AddDamage( nDamage );

	if ( blNewEnmityTarget )
	{ OnNewEnmityTarget(nID); }

    return iter->second.GetEnmity();
}

unsigned int AiEnmity::SetEnmity( GameObjectId nID, unsigned int nEnmity, int nReductionRate /* = MonsterDefine::EnmityReductionRate */ )
{
	bool blNewEnmityTarget = false;
    TargetEnmityMapIter iter = m_mapTargetEnmity.find( nID );
    if ( iter == m_mapTargetEnmity.end() )
    {
        iter = m_mapTargetEnmity.insert( std::make_pair( nID, EnmityData() ) ).first;
        if ( iter == m_mapTargetEnmity.end() )
        { return AiDefine::NoneEnmity; }

		if ( nEnmity > 0 )
		{ blNewEnmityTarget = true; }
    }
	else
	{
		if ( ! iter->second.HaveEnmity() && nEnmity > 0 )
		{ blNewEnmityTarget = true; }
	}

    iter->second.SetEnmity( nEnmity );
    float fReductionRate = static_cast< float >( nReductionRate ) / static_cast< float >( AiDefine::EnmityBaseRate );
    iter->second.SetReduction( iter->second.GetEnmity() * fReductionRate );

	if ( blNewEnmityTarget )
	{ OnNewEnmityTarget(nID); }

    return iter->second.GetEnmity();
}

unsigned int AiEnmity::DecEnmity( GameObjectId nID, unsigned int nEnmity )
{
    TargetEnmityMapIter iter = m_mapTargetEnmity.find( nID );
    if ( iter == m_mapTargetEnmity.end() )
    { return AiDefine::NoneEnmity; }

    iter->second.DecEnmity( nEnmity );

    // 没有仇恨了, 清除伤害
    if ( iter->second.GetEnmity() == AiDefine::NoneEnmity )
    { iter->second.ClearDamage();  }

    return iter->second.GetEnmity();
}

void AiEnmity::RemoveEnmity( GameObjectId nID )
{
    m_mapTargetEnmity.erase( nID );
    RemoveAttackTarget( nID );
}

void AiEnmity::ClearEnmity( bool bClearList )
{
    m_setAttackTarget.clear();

    for ( TargetEnmityMapIter iter = m_mapTargetEnmity.begin(); iter != m_mapTargetEnmity.end(); ++iter )
    {
        iter->second.ClearEnmity();
    }

    if ( bClearList )
    { m_mapTargetEnmity.clear(); }
}

bool AiEnmity::HaveEnmity()
{
    // 自己还对别人产生过仇恨
    if ( !m_setAttackTarget.empty() )
    { return true; }

    for ( TargetEnmityMapIter iter = m_mapTargetEnmity.begin(); iter != m_mapTargetEnmity.end(); ++iter )
    {
        if ( iter->second.GetEnmity() > AiDefine::NoneEnmity )
        { return true; }
    }

    return false;
}

EnmityData* AiEnmity::GetEnmity( GameObjectId nID )
{
    TargetEnmityMapIter iter = m_mapTargetEnmity.find( nID );
    if ( iter == m_mapTargetEnmity.end() )
    { return NULL; }

    return &( iter->second );
}

GameObjectId AiEnmity::GetMaxEnmityID()
{
    GameObjectId nID = InvalidGameObjectId;
    int nMaxEnmity = 0;
    for ( TargetEnmityMapIter iter = m_mapTargetEnmity.begin(); iter != m_mapTargetEnmity.end(); ++iter )
    {
        if ( iter->second.GetEnmity() > nMaxEnmity )
        {
            nMaxEnmity = iter->second.GetEnmity();
            nID = iter->first;
        }
    }

    return nID;
}

GameObjectId AiEnmity::GetMaxDamageID()
{
    GameObjectId nID = InvalidGameObjectId;
    unsigned int nMaxDamage = 0;
    for ( TargetEnmityMapIter iter = m_mapTargetEnmity.begin(); iter != m_mapTargetEnmity.end(); ++iter )
    {
        if ( iter->second.GetDamage() > nMaxDamage )
        {
            nMaxDamage = iter->second.GetDamage();
            nID = iter->first;
        }
    }

    return nID;
}

bool AiSkill::CanUseAiSkill( uint32 nHP, uint32 nMP ) const
{
    // 判断ColdDown时间
    if ( !GameTime::IsPassCurrentTime( GetStartColdDownTime(), GetColdDownTime() ) )
    { return false; }
 
    if ( ( nHP == 0 ) || ( nHP < GetCostHP() ) )
    { return false; }

    if ( nMP < GetCostMP() )
    { return false; }

    return true;
}