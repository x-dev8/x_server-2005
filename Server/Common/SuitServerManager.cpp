#include "SuitManager.h"
#include "GamePlayer.h"
#include "SuitConfig.h"
template<>
bool SuitManager< GamePlayer >::IsSuitHaveSkill( unsigned short skillId, unsigned short level )
{
    for ( ItrSuitContainer iter = m_vecSuitID.begin(); iter != m_vecSuitID.end(); ++iter )
    {
        ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( *iter );
        if ( pItemCommon == NULL || !pItemCommon->IsCanEquip() )
        { continue; }

        ItemDefine::SItemCanEquip* pItemEquip = static_cast< ItemDefine::SItemCanEquip* >( pItemCommon );
        if ( pItemEquip->skillId == skillId )
        { 
            if ( m_uchSkillSuitLevel <= 2 ) // 小于2级,技能等级不增加
            {
                return ( pItemEquip->skillLevel == level );
            }
            else if ( m_uchSkillSuitLevel >= 3 )    // 大于3级, 每升一级技能等级增加1
            {
                return ( ( m_uchSkillSuitLevel - 2 + 1 ) >= level );
            }
        }
    }

    return false;
}

template<>
bool SuitManager< GamePlayer >::ApplyToPlayer()
{
    if( m_pGamePlayer == NULL )
    { return false; }

    m_vecSuitID.clear();
    m_uchSkillSuitLevel = 100;
    ClearSuitInfo(); // 清除属性
	ClearSuitEquipSkill();

    SuitCounter      suitCounter        ;   // 套装计数
    StarLevelCounter starLevelCounter   ;   // 同星个数计数
    uint8            stampCounter = 0   ;
	std::map<unsigned int,unsigned char> SuitList;
	std::set<unsigned int>	EquipList;
    for( int8 i=0; i<EEquipPartType_MaxEquitPart; ++i ) // 将装备数值累加
    {
        SCharItem* pItem = GetAttriSuitEquipItem( i );
        if ( pItem == NULL || pItem->equipdata.usHP <= 0.0f )
        { continue; }

        ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( pItem->itembaseinfo.ustItemID );
        if( pItemCommon == NULL )
        { continue; }

        ItemDefine::SItemCanEquip* pItemEquip = static_cast< ItemDefine::SItemCanEquip* >( pItemCommon );
        if ( pItemEquip == NULL )
        { continue; }

        // 累计同星个数
        if ( pItem->equipdata.ucLevel >= SStarActivation::EConstDefine_StarActivationStartLevel )
        { 
            for( int j = SStarActivation::EConstDefine_StarActivationStartLevel ; j <= pItem->equipdata.ucLevel; ++j )
            {
                starLevelCounter[j] += 1;
            }
        }

        // 累计铸魂个数
        if (pItem->IsSoulStamp())
        { ++stampCounter; }

        // 累计套装个数
        if (pItemEquip->IsSuitEquip())
        {
            // 累计套装
            suitCounter[ pItemEquip->sSuitID ] += 1;

            // 判断技能套
            if ( pItemEquip->IsSkillSuitEquip() )
            {
                if ( m_uchSkillSuitLevel > pItem->GetSuitLevel() ) // 计算技能套装精炼最小等级
                { m_uchSkillSuitLevel = pItem->GetSuitLevel(); }
            }
        }

		//新的套装属性 我们需要进出处理 需要处理是否计算重复装备的件数 EquipList
		unsigned int SuitID = theSuitConfig.GetSuitIDByItemID(pItem->itembaseinfo.ustItemID);
		if(SuitID != 0)
		{
			if(!theSuitConfig.IsRepeatSum(SuitID))
			{
				//重复的装备不计数
				if(EquipList.count(pItem->itembaseinfo.ustItemID) == 1)
				{
					continue;
				}
			}
			//这件装备有套装 我们需要处理下
			if(SuitList.count(SuitID) == 1)
			{
				SuitList.find(SuitID)->second++;
			}
			else
			{
				SuitList.insert(std::map<unsigned int,unsigned char>::value_type(SuitID,1));
			}
		}
		EquipList.insert(std::set<unsigned int>::value_type(pItem->itembaseinfo.ustItemID));
    }

    for ( ItrSuitCounter it = suitCounter.begin(); it != suitCounter.end(); ++it )
    {
        for ( int i = 0; i < it->second; ++i )
        {
            unsigned short suitId = it->first * 10 + i + 1;
            ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( suitId );
            if( pItemCommon == NULL )
            { continue; }

            m_vecSuitID.push_back( suitId );
        }
    }

    // 附加套装装备属性
    for ( ItrSuitContainer it = m_vecSuitID.begin(); it != m_vecSuitID.end(); ++it )
    { AddEquipAttribute( *it ); } 

    // 附加套装星激活属性
    for ( StarLevelCounterReItr it = starLevelCounter.rbegin(); it != starLevelCounter.rend(); ++it )
    {
        SStarActivation::SEffect* pEffect = theStarLevelUpConfig.GetStarActivationEffect( it->first, it->second );
        if ( pEffect == NULL)
        { continue; }

        AddStarActivationAttribute( pEffect  );
        break;
    }

    // 附加铭刻激活属性
    SStampActivation::EffectContainer stampEffect;
    theStarLevelUpConfig.GetStampActivationEffect( stampCounter, stampEffect );
    for (SStampActivation::EffectContainerItr it = stampEffect.begin(); it != stampEffect.end(); ++it )
    {
        AddStampActivationAttribute( &(*it) );
    }
	
	if(!SuitList.empty())
	{
		std::map<unsigned int,unsigned char>::iterator Iter = SuitList.begin();
		for(;Iter != SuitList.end();++Iter)
		{
			unsigned int SuitID = Iter->first;
			unsigned char Sum = Iter->second;
			SuitAtt*  pSuit = theSuitConfig.GetSuitInfoBySuitID(SuitID);
			if(pSuit)
			{
				std::vector<unsigned int> vecList;
				pSuit->GetAllFullSuitIDBySum(Sum,vecList);
				if(!vecList.empty())
				{
					//有需要添加的套装属性
					std::vector<unsigned int>::iterator Iter = vecList.begin();
					for(;Iter != vecList.end();++Iter)
					{
						//添加属性到玩家身上去
						AddEquipAttribute(*Iter);
						ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( *Iter );
						if ( pItemCommon && pItemCommon->IsCanEquip() )
						{
							ItemDefine::SItemCanEquip* pItemCanEquip = static_cast< ItemDefine::SItemCanEquip* >( pItemCommon );
							if(pItemCanEquip->skillId !=0)
							{
								//让玩家学会技能
								if(m_pGamePlayer->LearnSkill( pItemCanEquip->skillId, pItemCanEquip->skillLevel,false,false))
								{
									//发送命令到客户端去 添加技能	
									SuitEquipSkillVec.push_back(pItemCanEquip->skillId);
								}
							}
						}
					}
				}
			}
		}
	}
    return true;
}
template<>
void SuitManager< GamePlayer >::ClearSuitEquipSkill(bool IsCheckEmpty)
{
	if(!SuitEquipSkillVec.empty())
	{
		std::vector<unsigned short>::iterator Iter = SuitEquipSkillVec.begin();
		for(;Iter != SuitEquipSkillVec.end();++Iter)
		{
			m_pGamePlayer->ForgetSkill(*Iter);
		}
	}
	else if(IsCheckEmpty)
	{
		//为空不代表一定没技能需要删除
		std::map<unsigned int,unsigned char> SuitList;
		std::set<unsigned int>	EquipList;
		for( int8 i=0; i<EEquipPartType_MaxEquitPart; ++i ) // 将装备数值累加
		{
			SCharItem* pItem = GetAttriSuitEquipItem( i );
			if ( pItem == NULL || pItem->equipdata.usHP <= 0.0f )
			{ continue; }

			ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( pItem->itembaseinfo.ustItemID );
			if( pItemCommon == NULL )
			{ continue; }

			ItemDefine::SItemCanEquip* pItemEquip = static_cast< ItemDefine::SItemCanEquip* >( pItemCommon );
			if ( pItemEquip == NULL )
			{ continue; }

			//新的套装属性 我们需要进出处理 需要处理是否计算重复装备的件数 EquipList
			unsigned int SuitID = theSuitConfig.GetSuitIDByItemID(pItem->itembaseinfo.ustItemID);
			if(SuitID != 0)
			{
				if(!theSuitConfig.IsRepeatSum(SuitID))
				{
					//重复的装备不计数
					if(EquipList.count(pItem->itembaseinfo.ustItemID) == 1)
					{
						continue;
					}
				}
				//这件装备有套装 我们需要处理下
				if(SuitList.count(SuitID) == 1)
				{
					SuitList.find(SuitID)->second++;
				}
				else
				{
					SuitList.insert(std::map<unsigned int,unsigned char>::value_type(SuitID,1));
				}
			}
			EquipList.insert(std::set<unsigned int>::value_type(pItem->itembaseinfo.ustItemID));
		}
		if(!SuitList.empty())
		{
			std::map<unsigned int,unsigned char>::iterator Iter = SuitList.begin();
			for(;Iter != SuitList.end();++Iter)
			{
				unsigned int SuitID = Iter->first;
				unsigned char Sum = Iter->second;
				SuitAtt*  pSuit = theSuitConfig.GetSuitInfoBySuitID(SuitID);
				if(pSuit)
				{
					std::vector<unsigned int> vecList;
					pSuit->GetAllFullSuitIDBySum(Sum,vecList);
					if(!vecList.empty())
					{
						//有需要添加的套装属性
						std::vector<unsigned int>::iterator Iter = vecList.begin();
						for(;Iter != vecList.end();++Iter)
						{
							//添加属性到玩家身上去
							ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( *Iter );
							if ( pItemCommon && pItemCommon->IsCanEquip() )
							{
								ItemDefine::SItemCanEquip* pItemCanEquip = static_cast< ItemDefine::SItemCanEquip* >( pItemCommon );
								if(pItemCanEquip->skillId !=0)
								{
									//让玩家学会技能
									m_pGamePlayer->ForgetSkill(pItemCanEquip->skillId);
								}
							}
						}
					}
				}
			}
		}
	}
}
template<>
void SuitManager< GamePlayer >::SetPlayer( GamePlayer* pPlayer )
{
    m_pGamePlayer = pPlayer;
    ClearSuitInfo();
	ClearSuitEquipSkill(true);
}

template<>
void SuitManager< GamePlayer >::ClearSuitInfo()
{
    if ( m_pGamePlayer == NULL )
    { return; }

    m_pGamePlayer->ClearAllBaseAttrByPart ( ECustomDataPart_suit );
    m_pGamePlayer->ClearAllFightAttrByPart( ECustomDataPart_suit );
}

template<>
SCharItem* SuitManager< GamePlayer >::GetAttriSuitEquipItem( int nIndex )
{
    if ( m_pGamePlayer == NULL )
    { return NULL; }

    return m_pGamePlayer->GetVisualEquipItem( nIndex );
}

template<>
void SuitManager< GamePlayer >::AddEquipAttribute( unsigned short ustItemID )
{
    if ( m_pGamePlayer == NULL )
    { return; }

    m_pGamePlayer->ApplySuitEquipAttributesToChar( ustItemID );
}

template<>
void SuitManager<GamePlayer>::AddStarActivationAttribute( SStarActivation::SEffect* pEffect )
{
    if ( m_pGamePlayer == NULL )
    { return; }

    m_pGamePlayer->ApplyStarActivationAttribute( pEffect );
}

template<>
void SuitManager<GamePlayer>::AddStampActivationAttribute( SStampActivation::SEffect* pEffect )
{
    if ( m_pGamePlayer == NULL )
    { return; }

    m_pGamePlayer->ApplyStampActivationAttribute( pEffect );
}

