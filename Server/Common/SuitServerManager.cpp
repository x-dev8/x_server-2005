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
            if ( m_uchSkillSuitLevel <= 2 ) // С��2��,���ܵȼ�������
            {
                return ( pItemEquip->skillLevel == level );
            }
            else if ( m_uchSkillSuitLevel >= 3 )    // ����3��, ÿ��һ�����ܵȼ�����1
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
    ClearSuitInfo(); // �������
	ClearSuitEquipSkill();

    SuitCounter      suitCounter        ;   // ��װ����
    StarLevelCounter starLevelCounter   ;   // ͬ�Ǹ�������
    uint8            stampCounter = 0   ;
	std::map<unsigned int,unsigned char> SuitList;
	std::set<unsigned int>	EquipList;
    for( int8 i=0; i<EEquipPartType_MaxEquitPart; ++i ) // ��װ����ֵ�ۼ�
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

        // �ۼ�ͬ�Ǹ���
        if ( pItem->equipdata.ucLevel >= SStarActivation::EConstDefine_StarActivationStartLevel )
        { 
            for( int j = SStarActivation::EConstDefine_StarActivationStartLevel ; j <= pItem->equipdata.ucLevel; ++j )
            {
                starLevelCounter[j] += 1;
            }
        }

        // �ۼ��������
        if (pItem->IsSoulStamp())
        { ++stampCounter; }

        // �ۼ���װ����
        if (pItemEquip->IsSuitEquip())
        {
            // �ۼ���װ
            suitCounter[ pItemEquip->sSuitID ] += 1;

            // �жϼ�����
            if ( pItemEquip->IsSkillSuitEquip() )
            {
                if ( m_uchSkillSuitLevel > pItem->GetSuitLevel() ) // ���㼼����װ������С�ȼ�
                { m_uchSkillSuitLevel = pItem->GetSuitLevel(); }
            }
        }

		//�µ���װ���� ������Ҫ�������� ��Ҫ�����Ƿ�����ظ�װ���ļ��� EquipList
		unsigned int SuitID = theSuitConfig.GetSuitIDByItemID(pItem->itembaseinfo.ustItemID);
		if(SuitID != 0)
		{
			if(!theSuitConfig.IsRepeatSum(SuitID))
			{
				//�ظ���װ��������
				if(EquipList.count(pItem->itembaseinfo.ustItemID) == 1)
				{
					continue;
				}
			}
			//���װ������װ ������Ҫ������
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

    // ������װװ������
    for ( ItrSuitContainer it = m_vecSuitID.begin(); it != m_vecSuitID.end(); ++it )
    { AddEquipAttribute( *it ); } 

    // ������װ�Ǽ�������
    for ( StarLevelCounterReItr it = starLevelCounter.rbegin(); it != starLevelCounter.rend(); ++it )
    {
        SStarActivation::SEffect* pEffect = theStarLevelUpConfig.GetStarActivationEffect( it->first, it->second );
        if ( pEffect == NULL)
        { continue; }

        AddStarActivationAttribute( pEffect  );
        break;
    }

    // �������̼�������
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
					//����Ҫ��ӵ���װ����
					std::vector<unsigned int>::iterator Iter = vecList.begin();
					for(;Iter != vecList.end();++Iter)
					{
						//������Ե��������ȥ
						AddEquipAttribute(*Iter);
						ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( *Iter );
						if ( pItemCommon && pItemCommon->IsCanEquip() )
						{
							ItemDefine::SItemCanEquip* pItemCanEquip = static_cast< ItemDefine::SItemCanEquip* >( pItemCommon );
							if(pItemCanEquip->skillId !=0)
							{
								//�����ѧ�Ἴ��
								if(m_pGamePlayer->LearnSkill( pItemCanEquip->skillId, pItemCanEquip->skillLevel,false,false))
								{
									//��������ͻ���ȥ ��Ӽ���	
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
		//Ϊ�ղ�����һ��û������Ҫɾ��
		std::map<unsigned int,unsigned char> SuitList;
		std::set<unsigned int>	EquipList;
		for( int8 i=0; i<EEquipPartType_MaxEquitPart; ++i ) // ��װ����ֵ�ۼ�
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

			//�µ���װ���� ������Ҫ�������� ��Ҫ�����Ƿ�����ظ�װ���ļ��� EquipList
			unsigned int SuitID = theSuitConfig.GetSuitIDByItemID(pItem->itembaseinfo.ustItemID);
			if(SuitID != 0)
			{
				if(!theSuitConfig.IsRepeatSum(SuitID))
				{
					//�ظ���װ��������
					if(EquipList.count(pItem->itembaseinfo.ustItemID) == 1)
					{
						continue;
					}
				}
				//���װ������װ ������Ҫ������
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
						//����Ҫ��ӵ���װ����
						std::vector<unsigned int>::iterator Iter = vecList.begin();
						for(;Iter != vecList.end();++Iter)
						{
							//������Ե��������ȥ
							ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( *Iter );
							if ( pItemCommon && pItemCommon->IsCanEquip() )
							{
								ItemDefine::SItemCanEquip* pItemCanEquip = static_cast< ItemDefine::SItemCanEquip* >( pItemCommon );
								if(pItemCanEquip->skillId !=0)
								{
									//�����ѧ�Ἴ��
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

