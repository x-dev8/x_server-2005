#include "Suit.h"

#ifdef GAME_CLIENT
#include "PlayerRole.h"
#else
#include "GamePlayer.h"
#include "ShareData.h"
#endif

#include "ItemDetail.h"
#include "ArmourElementsConfig.h"

SuitManager::SuitManager()
{
#ifndef GAME_CLIENT
    _pGamePlayer = NULL;
#endif
    m_uchSkillSuitLevel = 100;
}

SuitManager::~SuitManager()
{

}

void SuitManager::ClearSuitInfo( )
{
#ifndef GAME_CLIENT
    _pGamePlayer->SET_VALUE( fPhysicsAttack, fSuit_Extra, 0 );
    _pGamePlayer->UPDATE_VALUE( fPhysicsAttack );

    _pGamePlayer->SET_VALUE( fMagicAttack, fSuit_Extra, 0 );
    _pGamePlayer->UPDATE_VALUE( fMagicAttack );

    _pGamePlayer->SET_VALUE( fPhysicsAttackDefend, fSuit_Extra,0 );
    _pGamePlayer->UPDATE_VALUE( fPhysicsAttackDefend );

    _pGamePlayer->SET_VALUE( fMagicAttackDefend, fSuit_Extra, 0 );
    _pGamePlayer->UPDATE_VALUE( fMagicAttackDefend );

    _pGamePlayer->SET_VALUE( usAddDamageResist, suit_extra, 0 );
    _pGamePlayer->UPDATE_VALUE( usAddDamageResist );

    _pGamePlayer->SET_VALUE( iAddDamage, suit_extra, 0 );
    _pGamePlayer->UPDATE_VALUE( iAddDamage );

    _pGamePlayer->SET_VALUE( usGiddyResist, suit_extra, 0 );
    _pGamePlayer->UPDATE_VALUE( usGiddyResist );

    _pGamePlayer->SET_VALUE( usStandResist, suit_extra, 0 );
    _pGamePlayer->UPDATE_VALUE( usStandResist );

    _pGamePlayer->SET_VALUE( usSlowdownResist, suit_extra, 0 );
    _pGamePlayer->UPDATE_VALUE( usSlowdownResist );

    _pGamePlayer->SET_VALUE( usTorpidResist, suit_extra, 0 );
    _pGamePlayer->UPDATE_VALUE( usTorpidResist );

    _pGamePlayer->SET_VALUE( critical, suit_extra, 0 );
    _pGamePlayer->UPDATE_VALUE( critical );

    _pGamePlayer->SET_VALUE( criticalIntensity, suit_extra, 0);
    _pGamePlayer->UPDATE_VALUE( criticalIntensity );

    _pGamePlayer->SET_VALUE( usCriticalResist, suit_extra, 0);
    _pGamePlayer->UPDATE_VALUE( usCriticalResist );

    _pGamePlayer->SET_VALUE( exact, suit_extra, 0 );
    _pGamePlayer->UPDATE_VALUE( exact );

    _pGamePlayer->SET_VALUE( dodge, suit_extra, 0);
    _pGamePlayer->UPDATE_VALUE( dodge );

    _pGamePlayer->SET_VALUE( iHpMax, suit_extra, 0 );
    _pGamePlayer->UPDATE_VALUE( iHpMax );

    _pGamePlayer->SET_VALUE( iMpMax, suit_extra, 0 );
    _pGamePlayer->UPDATE_VALUE( iMpMax );

    _pGamePlayer->SET_VALUE( sHPRestoreRate, suit_extra, 0 );
    _pGamePlayer->UPDATE_VALUE( sHPRestoreRate );

    _pGamePlayer->SET_VALUE( sMPRestoreRate, suit_extra, 0 );
    _pGamePlayer->UPDATE_VALUE( sMPRestoreRate );

    _pGamePlayer->SET_VALUE( sNormalAttackSpeed, suit_extra, 0 );
    _pGamePlayer->UPDATE_VALUE( sNormalAttackSpeed );

    _pGamePlayer->SET_VALUE( sIntonate, suit_extra, 0 );
    _pGamePlayer->UPDATE_VALUE( sIntonate );

    _pGamePlayer->SET_VALUE( fMoveSpeed, fSuit_Extra, 0 );
    _pGamePlayer->UPDATE_VALUE( fMoveSpeed );
#endif
}

#ifndef GAME_CLIENT
void SuitManager::SetPlayer(GamePlayer* pPlayer)
{
    _pGamePlayer = pPlayer;
    ClearSuitInfo();
}
#endif
    
bool SuitManager::ApplyToPlayer()
{
#ifndef GAME_CLIENT
    if( _pGamePlayer == NULL )
	{ return false; }

    _pGamePlayer->SetArmourElementsCount( 0, 0, 0 );
#endif

    m_uchSkillSuitLevel = 100;
    m_vecRand.clear();
    m_ustExtendAttack = 0;
    ClearSuitInfo();

    SuitCounter suitCounter;

    MapElementsCount mapElementsCount; // ����������װ����������
    int nElementsCount = 0;
    ElementInfoVertor vecElementInfo( 0 );

    // ��װ����ֵ���ۼ�
	for(int i = 0; i < EEquipPartType_MaxEquitPart; ++i)
	{
#ifdef GAME_CLIENT
		SCharItem* pItems = &thePlayerRole.m_pVisual->GetVisualArray()[i];
#else
		SCharItem* pItems = _pGamePlayer->GetAttriSuitEquipItem( i );
#endif

        if ( pItems == NULL || pItems->equipdata.usHP == 0.0f )
        { continue; }

        ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( pItems->itembaseinfo.ustItemID );
        if( pItemCommon == NULL )
        { continue; }

        if ( pItemCommon->ucItemType != ItemDefine::ITEMTYPE_ARMOUR )
        { continue; }

        ItemDefine::SItemArmour* pItemArmour = (ItemDefine::SItemArmour*)pItemCommon;
        if ( pItemArmour == NULL )
        { continue; }

        if( !pItemArmour->IsSuitEquip() )
        { continue; }

        suitCounter[pItemArmour->sSuitID] += 1;

        // �жϼ����� ���� ������
        if ( pItemArmour->IsSkillSuitEquip() )
        {
            if ( m_uchSkillSuitLevel > pItems->GetSuitLevel() ) // ���㼼����װ������С�ȼ�
            {
                m_uchSkillSuitLevel = pItems->GetSuitLevel();
            }
        }
        else if ( pItemArmour->IsElementSuitEquip() )
        {
            // ����������װװ������
            if ( pItems->GetElements() > 0 )
            {
                ++nElementsCount;   // ����װ������ +1
                vecElementInfo.push_back( ElementInfo( pItems->GetElements(), pItems->GetSuitLevel() ) );   // �������Ե�Ԫ�غ͵ȼ�
                MapElementsCountIter iter = mapElementsCount.find( pItems->GetElements() );   // ����������Եĸ���
                if ( iter == mapElementsCount.end() )
                {
                    mapElementsCount.insert( make_pair( pItems->GetElements(), 1 ) );
                }
                else
                {
                    iter->second += 1;
                }
            }
        }
    }

    if ( suitCounter.empty())
    { return true; }

    _suits.clear();
    {
        ItrSuitCounter it    = suitCounter.begin();
        ItrSuitCounter itEnd = suitCounter.end();
        for ( ; it != itEnd; ++it )
        {
            for ( int i=0; i< it->second; ++i)
            {
                unsigned short suitId = it->first * 10 + i + 1;
                ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( suitId );
                if( pItemCommon == NULL )
                { continue; }

                _suits.push_back( suitId );
            }
        }
    }

    // ������������������װ����
    int nMaxCount = 0;
    uint8 nElement = 0;
    bool bSameMaxCount = false;
    unsigned short nSuitID = 0;
    for ( ItrSuitCounter iter = suitCounter.begin(); iter != suitCounter.end(); ++iter )          // ����6��, ���ұ�����ͬһ��, Ч������Ч
    {
        if ( iter->second >= ItemDefine::SItemArmour::ECD_ElementSuitCount && nElementsCount >= ItemDefine::SItemArmour::ECD_ElementSuitCount )    // ��װ������ 6�� ���Ҷ�����������������
        {
            nSuitID = iter->first * 10 + ItemDefine::SItemArmour::ECD_ElementSuitCount;
            for ( MapElementsCountIter iter = mapElementsCount.begin(); iter != mapElementsCount.end(); ++iter )
            {
                if ( iter->second > nMaxCount )
                {
                    nMaxCount     = iter->second;
                    nElement      = iter->first;
                    bSameMaxCount = false;
                }
                else if ( iter->second == nMaxCount )
                {
                    bSameMaxCount = true;
                }
            }

            break;
        }
    }

#ifdef GAME_CLIENT
	m_bHaveNoMainElement = bSameMaxCount;
	m_nMainElement = nElement;
	m_nMaxElementCount = nMaxCount;	
#else

    if ( nElement > 0 && nMaxCount > 0 && !bSameMaxCount )       // �õ���װ����Ԫ�� �Լ�����
    {
        ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( nSuitID );
        if ( pItemCommon != NULL && pItemCommon->ucItemType == ItemDefine::ITEMTYPE_ARMOUR )
        {
            ItemDefine::SItemArmour* pItemArmour = (ItemDefine::SItemArmour*)pItemCommon;
            if ( pItemArmour != NULL )
            {
                _pGamePlayer->SetArmourElementsCount( pItemArmour->stEquipLevelReq, nElement, nMaxCount );

                CalcElementAttribute( pItemArmour->stEquipLevelReq, nElement, nMaxCount, vecElementInfo );
            }
        }
    }
#endif


#ifndef GAME_CLIENT
    if ( _suits.empty())
    { return true; }

    {
        ItrSuitContainer it    = _suits.begin();
        ItrSuitContainer itEnd = _suits.end();
        for ( ; it != itEnd; ++it )
        {
            unsigned short suitId = *it;
            ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( suitId );
            
            if ( pItemCommon == NULL || pItemCommon->ucItemType != ItemDefine::ITEMTYPE_ARMOUR )
            { continue; }

            ItemDefine::SItemArmour* pItemArmour = (ItemDefine::SItemArmour*)pItemCommon;
            if ( pItemArmour == NULL )
            { continue; }

            _pGamePlayer->SET_VALUE( fPhysicsAttack, fSuit_Extra, _pGamePlayer->GET_VALUE( fPhysicsAttack, fSuit_Extra) + pItemArmour->fAddtionPhysicsAttack );
            _pGamePlayer->UPDATE_VALUE( fPhysicsAttack );

            _pGamePlayer->SET_VALUE( fMagicAttack, fSuit_Extra, _pGamePlayer->GET_VALUE( fMagicAttack, fSuit_Extra) + pItemArmour->fAddtionMagicAttack  );
            _pGamePlayer->UPDATE_VALUE( fMagicAttack );

            _pGamePlayer->SET_VALUE( fPhysicsAttackDefend, fSuit_Extra, _pGamePlayer->GET_VALUE( fPhysicsAttackDefend, fSuit_Extra) + pItemArmour->fPhysicsDefend  );
            _pGamePlayer->UPDATE_VALUE( fPhysicsAttackDefend );

            _pGamePlayer->SET_VALUE( fMagicAttackDefend, fSuit_Extra, _pGamePlayer->GET_VALUE( fMagicAttackDefend, fSuit_Extra) + pItemArmour->fMagicDefend );
            _pGamePlayer->UPDATE_VALUE( fMagicAttackDefend );

            _pGamePlayer->SET_VALUE( usAddDamageResist, suit_extra, _pGamePlayer->GET_VALUE( usAddDamageResist, suit_extra) + pItemArmour->usAddDamageResist );
            _pGamePlayer->UPDATE_VALUE( usAddDamageResist );

            _pGamePlayer->SET_VALUE( iAddDamage, suit_extra, _pGamePlayer->GET_VALUE( iAddDamage, suit_extra) + pItemArmour->usAddtionDamage );
            _pGamePlayer->UPDATE_VALUE( iAddDamage );

            _pGamePlayer->SET_VALUE( usGiddyResist, suit_extra, _pGamePlayer->GET_VALUE( usGiddyResist, suit_extra) + pItemArmour->resistDread );
            _pGamePlayer->UPDATE_VALUE( usGiddyResist );

            _pGamePlayer->SET_VALUE( usStandResist, suit_extra, _pGamePlayer->GET_VALUE( usStandResist, suit_extra) + pItemArmour->resistComa );
            _pGamePlayer->UPDATE_VALUE( usStandResist );

            _pGamePlayer->SET_VALUE( usSlowdownResist, suit_extra, _pGamePlayer->GET_VALUE( usSlowdownResist, suit_extra) + pItemArmour->resistSlow );
            _pGamePlayer->UPDATE_VALUE( usSlowdownResist );

            _pGamePlayer->SET_VALUE( usTorpidResist, suit_extra, _pGamePlayer->GET_VALUE( usTorpidResist, suit_extra) + pItemArmour->resistSilence );
            _pGamePlayer->UPDATE_VALUE( usTorpidResist );

            _pGamePlayer->SET_VALUE( critical, suit_extra, _pGamePlayer->GET_VALUE( critical, suit_extra) + pItemArmour->critical );
            _pGamePlayer->UPDATE_VALUE( critical );

            _pGamePlayer->SET_VALUE( criticalIntensity, suit_extra, _pGamePlayer->GET_VALUE( criticalIntensity, suit_extra) + pItemArmour->criticalIntensity );
            _pGamePlayer->UPDATE_VALUE( criticalIntensity );

            _pGamePlayer->SET_VALUE( usCriticalResist, suit_extra, _pGamePlayer->GET_VALUE( usCriticalResist, suit_extra) + pItemArmour->usCriticalResist );
            _pGamePlayer->UPDATE_VALUE( usCriticalResist );

            _pGamePlayer->SET_VALUE( exact, suit_extra, _pGamePlayer->GET_VALUE( exact, suit_extra) + pItemArmour->exact );
            _pGamePlayer->UPDATE_VALUE( exact );

            _pGamePlayer->SET_VALUE( dodge, suit_extra, _pGamePlayer->GET_VALUE( dodge, suit_extra) + pItemArmour->dodge );
            _pGamePlayer->UPDATE_VALUE( dodge );

            _pGamePlayer->SET_VALUE( iHpMax, suit_extra, _pGamePlayer->GET_VALUE( iHpMax, suit_extra) + pItemArmour->nHpMax );
            _pGamePlayer->UPDATE_VALUE( iHpMax );

            _pGamePlayer->SET_VALUE( iMpMax, suit_extra, _pGamePlayer->GET_VALUE( iMpMax, suit_extra) + pItemArmour->sMpMax );
            _pGamePlayer->UPDATE_VALUE( iMpMax );

            _pGamePlayer->SET_VALUE( sHPRestoreRate, suit_extra, _pGamePlayer->GET_VALUE( sHPRestoreRate, suit_extra) + pItemArmour->sHpRestore );
            _pGamePlayer->UPDATE_VALUE( sHPRestoreRate );

            _pGamePlayer->SET_VALUE( sMPRestoreRate, suit_extra, _pGamePlayer->GET_VALUE( sMPRestoreRate, suit_extra) + pItemArmour->sMpRestore );
            _pGamePlayer->UPDATE_VALUE( sMPRestoreRate );

            _pGamePlayer->SET_VALUE( sNormalAttackSpeed, suit_extra, _pGamePlayer->GET_VALUE( sNormalAttackSpeed, suit_extra) + pItemArmour->sAttSpeedAdd );
            _pGamePlayer->UPDATE_VALUE( sNormalAttackSpeed );

            _pGamePlayer->SET_VALUE( sIntonate, suit_extra, _pGamePlayer->GET_VALUE( sIntonate, suit_extra) + pItemArmour->sIntonateSpeed );
            _pGamePlayer->UPDATE_VALUE( sIntonate );

            _pGamePlayer->SET_VALUE( fMoveSpeed, fSuit_Extra, _pGamePlayer->GET_VALUE( fMoveSpeed, fSuit_Extra) + pItemArmour->fMoveSpeed );
            _pGamePlayer->UPDATE_VALUE( fMoveSpeed );
        }
    }   
#endif
    
    return true;
}

bool SuitManager::IsSuitHaveSkill( unsigned short skillId, unsigned short level )
{
    ItrSuitContainer it    = _suits.begin();
    ItrSuitContainer itEnd = _suits.end();
    for ( ; it!=itEnd; ++it )
    {
        ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( *it );
        if ( pItemCommon == NULL )
        { continue; }

        if ( pItemCommon->ucItemType != ItemDefine::ITEMTYPE_ARMOUR )
        { continue; }

        ItemDefine::SItemArmour* pItemArmour = (ItemDefine::SItemArmour* )pItemCommon;
        
        if ( pItemArmour->skillId == skillId )
        { 
            if ( m_uchSkillSuitLevel <= 2 ) // С��2��,���ܵȼ�������
            {
                return pItemArmour->skillLevel == level;
            }
            else if ( m_uchSkillSuitLevel >= 3 )    // ����3��, ÿ��һ�����ܵȼ�����1
            {
                return ( m_uchSkillSuitLevel - 2 + 1 ) >= level;
            }
        }
    }

    return false;
}

// ����Ҫ�������Բ��ܸ�����������
void SuitManager::CalcElementAttribute( unsigned short ustEquipLevel, unsigned char uchMainElement, unsigned char uchMaxCount, ElementInfoVertor& vecElementInfo )
{
    int nLevel4Count = 0;
    int nLevel5Count = 0;
    for ( ElementInfoVertorIter iter = vecElementInfo.begin(); iter != vecElementInfo.end(); ++iter )
    {
        if ( iter->uchElement != uchMainElement )
        { continue; }       // ������Ԫ��

        m_ustExtendAttack += theArmourElementsConfig.GetExtendAttack( ustEquipLevel, iter->uchLevel );  // �ۼӸ����˺�

        if ( iter->uchLevel == 4 )
        {
            ++nLevel4Count;
        }
        else if ( iter->uchLevel == 5 )
        {
            ++nLevel5Count;
        }
    }

    ArmourElementsConfig::ValueVector vecValue;

    // ����Ԫ��, ��û����ӳ�����
    theArmourElementsConfig.GetBaseAttribute( ustEquipLevel, uchMainElement, uchMaxCount, vecValue );
    if ( !vecValue.empty() )
    {
        m_vecRand = vecValue;
    }

    // 6������+4 ���߶���+5�� �������ص�����
    if ( uchMaxCount == ItemDefine::SItemArmour::ECD_ElementSuitCount )
    {
        vecValue.clear();
        if ( nLevel4Count == ItemDefine::SItemArmour::ECD_ElementSuitCount )
        {
            theArmourElementsConfig.GetHideAttribute( ustEquipLevel, 4, vecValue );
        }
        else if ( nLevel5Count == ItemDefine::SItemArmour::ECD_ElementSuitCount )
        {
            theArmourElementsConfig.GetHideAttribute( ustEquipLevel, 5, vecValue );
        }

        if ( !vecValue.empty() )
        {
            m_vecRand.insert( m_vecRand.end(), vecValue.begin(), vecValue.end() );
        }
    }

#ifndef GAME_CLIENT
    if ( !m_vecRand.empty() )
    {
        _pGamePlayer->UpdateRandAttribute( m_vecRand );
    }
#endif

}

unsigned short SuitManager::GetSkillSuitIdByPartSuitId(unsigned short id) {
	return id * 10 + ItemDefine::SItemArmour::ECD_SkillSuitCount;;
}
