#include "MonsterSummonPet.h"
#include "GamePlayer.h"

MonsterSummonPet::MonsterSummonPet() : MonsterPetEx()
{
    SetObjType( Object_MonsterPet );
    m_nPetType = EPT_Skill;
}

void MonsterSummonPet::Initialize( ItemDefine::SMonster* pConfig, MonsterCreateData& xCreateData, GamePlayer* pPlayer /* = NULL */ )
{
    MonsterPetEx::Initialize( pConfig, xCreateData, pPlayer );
}

void MonsterSummonPet::ProcessPetDeath( int deathType )
{
    GamePlayer* pMaster = GetMasterPlayer();
    if ( pMaster != NULL )
    { pMaster->LostSummonPet( GetID() ); }

    MonsterPetEx::ProcessPetDeath( deathType );
}
