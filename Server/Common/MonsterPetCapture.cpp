#include "MonsterPetCapture.h"
#include "GamePlayer.h"

MonsterPetCapture::MonsterPetCapture() : MonsterPetEx()
{
    SetObjType( Object_MonsterCapture );
    m_nPetType = EPT_Capture;
}

void MonsterPetCapture::Initialize( ItemDefine::SMonster* pConfig, MonsterCreateData& xCreateData, GamePlayer* pPlayer /* = NULL */ )
{
    MonsterPetEx::Initialize( pConfig, xCreateData, pPlayer );

    SetMonsterType( eMT_Pet );

    // 设置没有死亡脚本
    m_nDeathScriptVMID = -1;
}

void MonsterPetCapture::ProcessPetDeath( int deathType )
{
    GamePlayer* pMaster = GetMasterPlayer();
    if ( pMaster != NULL )
    { pMaster->LostCapturePet(); }

    MonsterPetEx::ProcessPetDeath( deathType );
}

