#include "ServerVarInterface.h"
#include "ShareData.h"
#include "RelationDefine.h"
#include "GamePlayer.h"


bool CServerVarInterface::IsHaveTeacher()
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return false; }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );
    return pPlayer->IsHaveTeacher();
}

int CServerVarInterface::GetMasterLevel()
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return 0; }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );
    return pPlayer->GetMasterLevel();
}

bool CServerVarInterface::MasterLevelUp()
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return false; }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );
    return pPlayer->MasterLevelUp();
}

void CServerVarInterface::AddMasterValue( unsigned short nValue )
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return; }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );
    pPlayer->OperateMasterValue( EOT_Add, nValue );
}
void CServerVarInterface::SubMasterValue( unsigned short nValue )
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return; }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );
    pPlayer->OperateMasterValue( EOT_Sub, nValue );
}

int CServerVarInterface::GetMasterValue()
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return 0; }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );
    return pPlayer->GetMasterValue();
}

void CServerVarInterface::RegisterTeacher()
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return; }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );
    pPlayer->RegisterRelation( RelationDefine::Teacher );
}

void CServerVarInterface::RegisterStudent()
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return; }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );
    pPlayer->RegisterRelation( RelationDefine::Student );
}

void CServerVarInterface::QueryTeacher()
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return; }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );
    pPlayer->QueryRegisterRelation( RelationDefine::Teacher );
}


void CServerVarInterface::QueryStudent()
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return; }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );
    pPlayer->QueryRegisterRelation( RelationDefine::Student );
}

void CServerVarInterface::RemoveTeacher()
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return; }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );
    pPlayer->RemoveTeacher();
}

void CServerVarInterface::RemoveStudent()
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return; }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );
    pPlayer->QueryRegisterRelation( RelationDefine::Student );
}

void CServerVarInterface::QueryAddStudentLeftTime()
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return; }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );
    pPlayer->QueryAddRelationLeftTime( RelationDefine::Student );
}

void CServerVarInterface::QueryAddTeacherLeftTime()
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return; }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );
    pPlayer->QueryAddRelationLeftTime( RelationDefine::Teacher );
}

bool CServerVarInterface::AddMarriage()
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return false; }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );

    return pPlayer->Script_AddMarriage();
}

bool CServerVarInterface::CheckCanMarriage()
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return false; }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );

    return ( pPlayer->Script_CheckCanMarriage( GamePlayer::EMO_GainQuest ) != NULL );
}

bool CServerVarInterface::RemoveMarriage( bool bForceRemove )
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return false; }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );

    return pPlayer->Script_RemoveMarriage( bForceRemove );
}


bool CServerVarInterface::CheckCanReceiveMarriageQuest( bool bMarriage )
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return false; }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );

    return pPlayer->Script_CheckCanReceiveMarriageQuest( bMarriage );
}

bool CServerVarInterface::CreageMarriageStage( unsigned short ustMapID )
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return false; }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );

    return pPlayer->Script_CreateMarriageStage( ustMapID );
}

bool CServerVarInterface::FlyToMarriageMap( unsigned short ustMapID, float fX, float fY, float fDir )
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return false; }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );

    return pPlayer->Script_FlyToMarriageMap( ustMapID, fX, fY, fDir );
}

int CServerVarInterface::GetMaxFriendlyLevel()
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return 0; }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );

    return pPlayer->GetMaxFriendlyLevel();
}

bool CServerVarInterface::IsCanReceiveFriendlyQuest()
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return false; }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );

    return pPlayer->IsCanReceiveFriendlyQuest();
}

void CServerVarInterface::SaveReceiveFriendlyQuest()
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return; }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );

    pPlayer->SaveReceiveFriendlyQuest();
}

bool CServerVarInterface::GetReqRemoveMarriage()
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return false; }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );

    return pPlayer->GetReqRemoveMarriage();
}

bool CServerVarInterface::GetForceRemove()
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return false; }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );

    return pPlayer->GetForceRemove();
}

void CServerVarInterface::AddStudent()
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return; }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );

    pPlayer->AddStudent();
}

bool CServerVarInterface::IsCanRegisterTeacher()
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return false; }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );
    return pPlayer->IsCanRegisterTeacher();
}

bool CServerVarInterface::IsCanRegisterStudent()
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return false; }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );
    return pPlayer->IsCanRegisterStudent();
}

int CServerVarInterface::GetStudentCount()
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return 0; }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );
    return pPlayer->GetStudentCount();
}
