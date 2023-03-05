#include "MonsterCreater.h"
#include "GameWorld.h"
#include "ShareData.h"
#include "MonsterNormalEx.h"
#include "MonsterBuildEx.h"
#include "GamePlayer.h"
#include "PetSettingConfig.h"

void MonsterCreater::FillMonsterCreateData( MonsterCreateData& xCreateData, CMonsterProducer::TagMonsterData* pMonsterData )
{
    xCreateData.SetThinkingTime( pMonsterData->stAiValue );
    xCreateData.SetCanMoveZone( pMonsterData->rcBron );
    xCreateData.SetCountry( pMonsterData->eCountry );
    xCreateData.SetFightCamp( pMonsterData->nFightCamp );
    xCreateData.SetForce( pMonsterData->nForce );
    xCreateData.SetRouteID( pMonsterData->nRouteID );
    xCreateData.SetReliveTime( pMonsterData->dwReliveTime );

    //如果不是定点怪
    if ( pMonsterData->bRandRange )
    {
        int nTileX = pMonsterData->rcBron.left + rand() % ( pMonsterData->rcBron.right - pMonsterData->rcBron.left + 1 );
        int nTileY = pMonsterData->rcBron.top + rand() % ( pMonsterData->rcBron.bottom - pMonsterData->rcBron.top + 1 );

        xCreateData.SetPostionX( TileToFloat( nTileX ) );
        xCreateData.SetPostionY( TileToFloat( nTileY ) );
    }
    else
    {
        xCreateData.SetPostionX( pMonsterData->x );
        xCreateData.SetPostionY( pMonsterData->y );
    }

    // 为负数时, 随即朝向
    xCreateData.SetDirection( pMonsterData->nDirection );
    if ( xCreateData.GetDirection() < 0 )
    { xCreateData.SetDirection( rand() % 360 ); }
    SetDirectiron( xCreateData );
}

ItemDefine::SMonster* MonsterCreater::CheckCreateMonster( MonsterCreateData& xCreateData )
{
    int nMonsterIndex = GettheItemDetail().FindMonsterIndexById( xCreateData.GetMonsterID() );
    ItemDefine::SMonster* pMonsterConfig = GettheItemDetail().GetMonster( nMonsterIndex );
    if ( pMonsterConfig == NULL )
    {
        LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_ERROR, "CreateNormalMonster[%u] pMonsterConfig == NULL", xCreateData.GetMonsterID() );
        return NULL;
    }

    GameStage* pStage = theGameWorld.GetStageById( xCreateData.GetMapID() );
    if ( pStage == NULL )
    {
        LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_ERROR, "CreateNormalMonster[%u] pStage[%u] == NULL", xCreateData.GetMonsterID(), EctypeId2MapId( xCreateData.GetMapID() ) );
        return NULL;
    }

    if ( pStage->IsCaracterFull() )
    {
        LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_ERROR, "Stage %d refresh monster failed!,pStage->IsCaracterFull", pStage->GetStageID() );
        return NULL;
    }

    if ( xCreateData.GetPostionX() < 0.f || xCreateData.GetPostionY() < 0.f ||
        xCreateData.GetPostionX() >= TileToFloat( pStage->GetWidth() ) ||
        xCreateData.GetPostionY() >= TileToFloat( pStage->GetHeight() ) )
    {
        LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_ERROR, "Map[%s] Monster[%s][%d] pos or area size is wrong, monster x:%f y:%f StageWidth:%d StageHeight:%d", 
            pStage->GetMapData()->MapName.c_str(), pMonsterConfig->GetName(), xCreateData.GetMonsterID(), xCreateData.GetPostionX(), xCreateData.GetPostionY(), pStage->GetWidth(), pStage->GetHeight() );
        return NULL;
    }

    return pMonsterConfig;
}

MonsterBaseEx* MonsterCreater::CreateMonster( MonsterCreateData& xCreateData, int nMonsterType, GamePlayer* pPlayer )
{
    ItemDefine::SMonster* pMonsterConfig = CheckCreateMonster( xCreateData );
    if ( pMonsterConfig == NULL )
    { return NULL; }

    int nMonsterID = theRunTimeData.CreateObject( nMonsterType );
    if ( nMonsterID == -1 )
    {
        LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_ERROR, "ShareData::CreateObject Monster Fail" );
        return NULL;
    }

    MonsterBaseEx* pMonster = static_cast< MonsterBaseEx* >( theRunTimeData.GetCharacterByID( nMonsterID ) );
    if ( pMonster == NULL )
    { return NULL; }

    pMonster->Initialize( pMonsterConfig, xCreateData, pPlayer );

    // 实际加入到世界中
    if( !theGameWorld.OnAddCharacter( nMonsterID, __FILE__, __LINE__ ) )
    {
        LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_ERROR, "CreateMonster OnAddCharacterOnlyID 加入怪物[%s]出错", pMonsterConfig->GetName() );
        theGameWorld.OnDelCharacter( nMonsterID );
        theRunTimeData.ReleaseObject( nMonsterID, __FILE__, __LINE__ );
        return NULL;
    }

    return pMonster;
}

MonsterBaseEx* MonsterCreater::CreateNormalMonster( MonsterCreateData& xCreateData )
{
    ItemDefine::SMonster* pMonsterConfig = GettheItemDetail().GetMonsterById( xCreateData.GetMonsterID() );
    if ( pMonsterConfig == NULL )
    { return NULL; }
    
    switch ( xCreateData.GetForce() )
    {
    case ForceDefine::FightNpcForce:    // 战斗npc阵营
        return CreateFightNpcMosnter( xCreateData );
        break;
    default:
        break;
    }

    // 区分主动怪和被动怪
    int nMonsterType = Object_MonsterNormal;

    // 判断是否是资源怪
    switch ( pMonsterConfig->stMonsterType )
    {
    case eMT_Mine:
    case eMT_Treasure:
    case eMT_Herb:
    case eMT_Wood:
    case eMT_Insect:
        nMonsterType = Object_MonsterResource;
        break;
    case eMT_Pickup:
        nMonsterType = Object_MonsterPickup;
        break;
    default:
        break;
    }

    return CreateMonster( xCreateData, nMonsterType );
}

MonsterBaseEx* MonsterCreater::CreateBuildMonster( MonsterCreateData& xCreateData )
{
    return CreateMonster( xCreateData, Object_MonsterBuilding );
}

MonsterBaseEx* MonsterCreater::CreateProtectedMonster( MonsterCreateData& xCreateData, GamePlayer* pPlayer )
{
    return CreateMonster( xCreateData, Object_MonsterProtected, pPlayer );
}

MonsterBaseEx* MonsterCreater::CreateSpecialMonster( MonsterCreateData& xCreateData )
{
    return CreateMonster( xCreateData, Object_MonsterSpecial );
}

MonsterBaseEx* MonsterCreater::CreatePetCaptureMonster( MonsterCreateData& xCreateData, GamePlayer* pPlayer )
{
    return CreateMonster( xCreateData, Object_MonsterCapture, pPlayer );
}

MonsterBaseEx* MonsterCreater::CreatePetTrapMonster( MonsterCreateData& xCreateData, GamePlayer* pPlayer )
{
    return CreateMonster( xCreateData, Object_MonsterTrap, pPlayer );
}

MonsterBaseEx* MonsterCreater::CreatePetSummonMonster( MonsterCreateData& xCreateData, GamePlayer* pPlayer )
{
    return CreateMonster( xCreateData, Object_MonsterPet, pPlayer );
}

MonsterBaseEx* MonsterCreater::CreatePetNurtureMonster( MonsterCreateData& xCreateData, GamePlayer* pPlayer )
{   
    return CreateMonster( xCreateData, Object_MonsterNurturePet, pPlayer );
}

MonsterBaseEx* MonsterCreater::CreatePetIllusionMonster( MonsterCreateData& xCreateData, GamePlayer* pPlayer )
{
    return CreateMonster( xCreateData, Object_MonsterIllusion, pPlayer );
}

MonsterBaseEx* MonsterCreater::CreateFightNpcMosnter( MonsterCreateData& xCreateData )
{
    return CreateMonster( xCreateData, Object_NpcFight );
}

void MonsterCreater::ProcessCreateNormalMonster( MonsterCreateData& xCreateData )
{
    switch ( xCreateData.GetCreateType() )
    {
    case AiDefine::NormalCreateType:
        {
            ProcessNormalTypeCreateMonster( xCreateData );
        }
        break;
    default:
        LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_ERROR, "ProcessCreateMonster 目前只支持一种刷怪方式", xCreateData.GetMapID(), xCreateData.GetMonsterID() );
        break;
    }
}

void MonsterCreater::ProcessCreateSpecialMonster( MonsterCreateData& xCreateData )
{
    switch ( xCreateData.GetCreateType() )
    {
    case AiDefine::NormalCreateType:
        {
            ProcessNormalTypeCreateSpecialMonster( xCreateData );
        }
        break;
    default:
        LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_ERROR, "ProcessCreateMonster 目前只支持一种刷怪方式", xCreateData.GetMapID(), xCreateData.GetMonsterID() );
        break;
    }
}


//以(x,y)为中心在半径为fRadius的圆内随机刷怪,怪物朝向(dx, dy)
void MonsterCreater::ProcessNormalTypeCreateMonster( MonsterCreateData& xCreateData )
{
    int nMonsterIndex = GettheItemDetail().FindMonsterIndexById( xCreateData.GetMonsterID() );
    if ( nMonsterIndex == -1 )
    {
        if ( !IsEctypeMonsterID( xCreateData.GetMonsterID() ) )
        {
            LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_ERROR, "ProcessNormalTypeCreateMonster 刷怪ID设置不正确 MapID = [0x%x] 怪物ID = [%d]", xCreateData.GetMapID(), xCreateData.GetMonsterID() );
            return;
        }

        // 获得场景等级
        GameStage* pStage = theGameWorld.GetStageById( xCreateData.GetMapID() );
        if ( pStage == NULL || pStage->GetStageLevel() == 0 )
        {
            LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_ERROR, "ProcessNormalTypeCreateMonster = [0x%x]",xCreateData.GetMonsterID(), xCreateData.GetMapID() );
            return;
        }

        int nMonsterID = FormatEctypeMonsterID( xCreateData.GetMonsterID(), pStage->GetStageLevel() );
        nMonsterIndex = GettheItemDetail().FindMonsterIndexById( nMonsterID );
        if ( nMonsterIndex == -1 )
        {
            LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_ERROR, "ProcessNormalTypeCreateMonster 由副本等级计算出的刷怪ID不正确 MapID = [0x%x] 怪物ID = [%d] Level = [%d]", pStage->GetStageID(), xCreateData.GetMonsterID(), pStage->GetStageLevel() );
            return;
        }
        xCreateData.SetMonsterID( nMonsterID );
    }
 
    for ( int i = 0; i < xCreateData.GetCount(); ++i )
    {
        MonsterCreateData xTempCreateData = xCreateData;
        SetNormalTypeRadiusPosition( xTempCreateData, xCreateData.GetPostionX(), xCreateData.GetPostionY(), xCreateData.GetRadius() );
        CreateNormalMonster( xTempCreateData );
    }
}

void MonsterCreater::SetNormalTypeRadiusPosition( MonsterCreateData& xCreateData, float fPosX, float fPosY, float fRadius )
{
    //朝向
    D3DXVECTOR3 vDir( fPosX, fPosY, 0 );
    vDir.x = ( rand() % 1001 - 500 );
    vDir.y = ( rand() % 1001 - 500 );
    vDir.z = 0;
    D3DXVec3Normalize( &vDir, &vDir );
    float fDistance = (float)( rand() % 1001 ) * fRadius * 0.001f + 1.0f;

    xCreateData.SetPostionX( fPosX + vDir.x * fDistance );
    xCreateData.SetPostionY( fPosY + vDir.y * fDistance );
}

void MonsterCreater::ProcessNormalTypeCreateSpecialMonster( MonsterCreateData& xCreateData )
{
    for ( int i = 0; i < xCreateData.GetCount(); ++i )
    {
        MonsterCreateData xTempCreateData = xCreateData;
        MonsterCreater::SetNormalTypeRadiusPosition( xCreateData, xCreateData.GetPostionX(), xCreateData.GetPostionY(), xCreateData.GetRadius() );
        MonsterCreater::CreateSpecialMonster( xCreateData );
    }
}

void MonsterCreater::SetDirectiron( MonsterCreateData& xCreateData )
{
    float fDirX = 0.0f, fDirY = 0.0f;

    float fDir = xCreateData.GetDirection() / 180 * D3DX_PI;
    float fxtoy = tan(fDir);
    float fPosXOff = 0;
    float fPosYOff = 0;

    if( fxtoy == 0 )
    {
        fPosXOff = 1;
    }
    else
    {
        fPosXOff = sqrtf(1/(1+fxtoy*fxtoy));
        fPosYOff = fabs(fxtoy*fPosXOff);
    }
    if( ( fDir >= 0 && fDir <= D3DX_PI/2 ) || ( fDir >= -D3DX_PI*2 && fDir <= -D3DX_PI*3/2 ) )
    { // 第一象限
        fDirX = fPosXOff;
        fDirY = fPosYOff;
    }
    else if( ( fDir >= D3DX_PI/2 && fDir <= D3DX_PI ) || ( fDir >= -D3DX_PI*3/2 && fDir <= -D3DX_PI ) )
    { // 第二象限
        fDirX = -fPosXOff;
        fDirY = fPosYOff;
    }
    else if( ( fDir >= D3DX_PI && fDir <= D3DX_PI*3/2 ) || ( fDir >= -D3DX_PI && fDir <= -D3DX_PI/2 ) )
    { // 第三象限
        fDirX = -fPosXOff;
        fDirY = -fPosYOff;
    }
    else if( ( fDir >= D3DX_PI*3/2 && fDir <= D3DX_PI*2 ) || ( fDir >= -D3DX_PI/2 && fDir <= 0 ) )
    { // 第四象限
        fDirX = fPosXOff;
        fDirY = -fPosYOff;
    }

    xCreateData.SetDirX( fDirX );
    xCreateData.SetDirY( fDirY );
}
