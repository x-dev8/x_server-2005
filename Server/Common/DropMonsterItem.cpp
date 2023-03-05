#include "GamePlayer.h"
#include "DropMonsterItem.h"
#include "SlkReader.h"
#include "ErrorLog.h"
#include "MonsterBaseEx.h"
#include "ShareData.h"
#include "ResourcePath.h"
#include "TeamManager.h"

DropMonsterItem::DropMonsterItem()
{
}

DropMonsterItem::~DropMonsterItem()
{
}

bool DropMonsterItem::MonsterDeath( MonsterBaseEx* pMonster, BaseCharacter* pKiller )
{
	if ( !pKiller || !pKiller->IsPlayer() || !pMonster )
		return false;

	GamePlayer* pPlayer = (GamePlayer*)pKiller;

    int nDistanceLevel = 0;
    float  fDisLvX  = GetDistanceLevelX( pMonster, pKiller, nDistanceLevel );
    uint32 nMapId   = pMonster->GetMapID();
    float  fX       = pMonster->GetFloatX();
    float  fY       = pMonster->GetFloatY();

    // 掉落包裹
    DropItemVector vecDropItem;
    DropCharItemVector vecCharItem( 0 );

    std::vector<SMonsterDrop>::iterator iter = theDropMonsterItemConfig.GetDropMonsterItemConfig().begin();
    std::vector<SMonsterDrop>::iterator end  = theDropMonsterItemConfig.GetDropMonsterItemConfig().end();
    for ( ; iter != end; ++iter )
    {
        // 查找Monster
        if ( IsNormalMonsterID( iter->nMonsterId ) )    // 如果是野外怪
        {
            if ( iter->nMonsterId != pMonster->GetMonsterID() )
            { continue; }
        }
        else if ( IsEctypeMonsterID( iter->nMonsterId ) )        // 是副本怪
        {
            unsigned short ustLevel = 0;
            int nMonsterID = GetEctypeMonsterID( pMonster->GetMonsterID(), ustLevel );

            if ( iter->nMonsterId != nMonsterID )
            { continue; }
        }
        else
        { continue; }

        vecDropItem.clear();

        //for ( uint32 i = 0; i < pMonsterDrop->vtMonsterPack.size(); ++i )
        //{
        //    SMonsterPack *pPack = &pMonsterDrop->vtMonsterPack[i];
        //    for ( int x = 0; x < pPack->nRandCount; ++x )
        //    {
        //        // 按掉落机率掉落
        //        int nRand = theRand.rand32() % DROP_PROBABILITY;
        //        if ( nRand < pPack->stItem.nProbability )
        //        {
        //            AddDropItemInPackage(mapDropItem, pPack->stItem.nItemId);
        //        }
        //    }
        //}

        std::vector<SCommonPack>::iterator piter = iter->vtPackId.begin();
        std::vector<SCommonPack>::iterator pend  = iter->vtPackId.end();
        for ( ; piter != pend; ++piter )
        {
                float fLevelRandRate = 1.0f;
                if (piter->nPackProbabilityRate != 0 && nDistanceLevel > 5)
                { fLevelRandRate = max( 0.0f, (1.0f - (fDisLvX + piter->nPackProbabilityRate * DEF_PERCENT)) ); }

                int nRandom = theRand.rand32() % DROP_PROBABILITY;
                if ( nRandom < fLevelRandRate * piter->nProbability )
                {
                    std::vector<SCommonPackID>::iterator viter = piter->vtCommonPackID.begin();
                    std::vector<SCommonPackID>::iterator vend  = piter->vtCommonPackID.end();
                    for ( ; viter != vend; ++viter )
                    {
                        m_CommonDropItem.DropPackage( viter->nIndex, vecDropItem );
                    }
                }
        }

        if (iter->nPackDropType == PackDropType_Package)
        {
            DropItemPackage( vecDropItem, vecCharItem, pPlayer->GetTeamID(), pPlayer->GetDBCharacterID(), pMonster->GetID(), nMapId, fX, fY, LogDefine::ECD_DropType_Monster );
        }
        else
        {
            DropItemAround ( vecDropItem, vecCharItem, pPlayer->GetTeamID(), pPlayer->GetDBCharacterID(), pMonster->GetID(), nMapId, fX, fY, LogDefine::ECD_DropType_Monster );
        }
        
        break;
    }

	return true;
}

float DropMonsterItem::GetDistanceLevelX( MonsterBaseEx* pMonster, BaseCharacter* pKiller, OUT int& nDistanceLevel )
{
    if ( !pKiller || !pKiller->IsPlayer() || !pMonster )
        return false;

    GamePlayer* pPlayer = (GamePlayer*)pKiller;

    float fX = pPlayer->GetFloatX();
    float fY = pPlayer->GetFloatY();

    // 等级差掉落系数 x 规则如下：
    //    a)	等级差△level = 玩家等级 – 怪物等级
    //    b)	如果△level  <=  5，x = 1
    //    c)	如果△level  >   5，x = max(10%,(1 – [(△level-5) *5%])。即玩家杀低自己5级的怪，每多一级掉率减少5%，最低10%。
    //    d)	如果玩家在队伍中，等级差△level = 队伍平均等级 – 怪物等级

    nDistanceLevel = 0;
    GameTeam* pTeam = theGameTeamManager.GetTeam( pKiller->GetTeamID() );
    if ( pTeam != NULL )
    {
        int nTeamCount = pTeam->GetTeamMemberCountInMap( pKiller->GetMapID(), fX, fY );
        int nMinLevel = 0;
        int nMaxLevel = 0;
        int nTeamTotalLevel = pTeam->GetTeamMemberLevelDistance( pKiller->GetMapID(), fX, fY, nMinLevel, nMaxLevel );
        if ( nTeamCount != 0 )
        { nDistanceLevel = nTeamTotalLevel / nTeamCount; }
    }

    // 没有获得等级
    if ( nDistanceLevel == 0 )
    { nDistanceLevel =  pKiller->GetLevel() - pMonster->GetLevel(); }
    else
    { nDistanceLevel =  nDistanceLevel - pMonster->GetLevel(); }

    float x = 0.0f;
    if (nDistanceLevel > 5)
    { x = min(0.9f, (nDistanceLevel - 5) * 0.05f ); }

    return x;
}
