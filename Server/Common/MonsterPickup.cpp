#include "MonsterPickup.h"
#include "ShareData.h"
#include "GamePlayer.h"
#include "TeamManager.h"
#include "DropItemManager.h"

MonsterPickup::MonsterPickup() : MonsterBaseEx()
{
    SetObjType( Object_MonsterPickup );
}

void MonsterPickup::Initialize( ItemDefine::SMonster* pConfig, MonsterCreateData& xCreateData, GamePlayer* pPlayer /* = NULL */ )
{
    MonsterBaseEx::Initialize( pConfig, xCreateData, pPlayer );
}

long MonsterPickup::ApplyBufferStatus( int iStatusID, int iStatusLevel, GameObjectId iMaster, int eventType, int eventValue )
{
    return GLR_StatusApplyFail; 
}

void MonsterPickup::ProcessLockTarget( int nTargetID )
{
    if ( nTargetID == InvalidGameObjectId )
    { return; }

    // 在跑回出生点的时候, 不锁定新目标
    //if ( GetAiStatus() == MonsterDefine::ThinkingMoveToBorn )
    //{  return; }

    SetLockID( nTargetID );
    SetAiStatus( AiDefine::ThinkingDoNothing );
}

void MonsterPickup::ProcessDeathDromItem()
{
    return;
}

void MonsterPickup::ProcessDropItemPackage( int nDropPackIndex )
{
    uint32 nMapId   = GetMapID();
    float  fX       = GetFloatX();
    float  fY       = GetFloatY();

    // 掉落包裹
    DropItemVector vecDropItem;
    DropCharItemVector vecCharItem( 0 );

    std::vector<SMonsterDrop>::iterator iter = theDropMonsterItemConfig.GetDropMonsterItemConfig().begin();
    std::vector<SMonsterDrop>::iterator end  = theDropMonsterItemConfig.GetDropMonsterItemConfig().end();
    for ( ; iter != end; ++iter )
    {
        // 查找Monster
        if ( iter->nMonsterId != GetMonsterID() )
        { continue; }

        vecDropItem.clear();

        if ( nDropPackIndex >= iter->vtPackId.size() )
        { return; }

        SCommonPack* pCommonPack = &(iter->vtPackId[nDropPackIndex]);

        std::vector<SCommonPackID>::iterator viter = pCommonPack->vtCommonPackID.begin();
        std::vector<SCommonPackID>::iterator vend  = pCommonPack->vtCommonPackID.end();
        for ( ; viter != vend; ++viter )
        {
            m_CommonDropItem.DropPackage( viter->nIndex, vecDropItem );
        }

        if (iter->nPackDropType == PackDropType_Package)
        {
            m_CommonDropItem.DropItemPackage( vecDropItem, vecCharItem, InvalidLogicNumber, InvalidLogicNumber, GetID(), nMapId, fX, fY, LogDefine::ECD_DropType_Monster );
        }
        else
        {
            m_CommonDropItem.DropItemAround ( vecDropItem, vecCharItem, InvalidLogicNumber, InvalidLogicNumber, GetID(), nMapId, fX, fY, LogDefine::ECD_DropType_Monster );
        }

        break;
    }

    return;
}
