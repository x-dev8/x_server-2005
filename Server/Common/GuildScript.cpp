#include "ServerVarInterface.h"
#include "ShareData.h"
#include "GuildDefine.h"
#include "GamePlayer.h"
#include "GameWorld.h"
int CServerVarInterface::GetGuildId()
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return GuildDefine::InitID; }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );
    return pPlayer->GetGuildID();
}

bool CServerVarInterface::IsHaveGuild()
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return false; }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );
    return pPlayer->GetGuildID() != GuildDefine::InitID;
}

bool CServerVarInterface::IsGuildMaster()
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return false; }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );

    GameGuild* pGuild = pPlayer->GetGuild();
    if( pGuild == NULL )
    { return false; }

    return pGuild->IsMaster(pPlayer->GetDBCharacterID());
}
int CServerVarInterface::GetGuildMemberPosition()
{
	BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return 0; }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );

    GameGuild* pGuild = pPlayer->GetGuild();
    if( pGuild == NULL )
    { return 0; }

	GuildMember* pMember = pGuild->GetMember(pPlayer->GetDBCharacterID());
	if(!pMember)
		return 0;
	int Pos = pMember->GetPosition();
	return Pos;
}
int32 CServerVarInterface::GetGuildOffer()
{   
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return 0; }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );
    return pPlayer->GetGuildOffer();
}


void CServerVarInterface::AddGuildOffer( int nOffer )
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return; }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );

    pPlayer->OperateGuildOffer( GuildDefine::OperateAdd, nOffer );
}

void CServerVarInterface::DecGuildOffer( int nOffer )
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return; }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );
    pPlayer->OperateGuildOffer( GuildDefine::OperateSub, nOffer );
}

int32 CServerVarInterface::GetGuildActivity()
{   
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return 0; }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );
    return pPlayer->GetGuildActivity();
}


void CServerVarInterface::AddGuildActivity( int nOffer )
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return; }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );

    pPlayer->OperateGuildActivity( GuildDefine::OperateAdd, nOffer );
}

void CServerVarInterface::DecGuildActivity( int nOffer )
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return; }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );
    pPlayer->OperateGuildActivity( GuildDefine::OperateSub, nOffer );
}

int32 CServerVarInterface::GetGuildBuild()
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return 0; }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );
    return pPlayer->GetGuildExp();
}

void CServerVarInterface::AddGuildBuild(int nValue)
{    
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return; }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );
    pPlayer->OperateGuildExp( GuildDefine::OperateAdd, nValue );
}

void CServerVarInterface::DecGuildBuild(int nValue)
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return; }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );
    pPlayer->OperateGuildExp( GuildDefine::OperateSub, nValue );
}

int32 CServerVarInterface::GetGuildMoney()
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return 0; }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );
    return pPlayer->GetGuildMoney();
}

void CServerVarInterface::AddGuildMoney( int nValue )
{    
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return; }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );
    pPlayer->OperateGuildMoney( GuildDefine::OperateAdd, nValue );
}

void CServerVarInterface::DecGuildMoney(int nValue)
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return; }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );
    pPlayer->OperateGuildMoney( GuildDefine::OperateSub, nValue );
}

int32 CServerVarInterface::GetGuildMission()
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return 0; }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );
    return pPlayer->GetGuildMission();
}

void CServerVarInterface::AddGuildMission( int nValue )
{    
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return; }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );
    pPlayer->OperateGuildMission( GuildDefine::OperateAdd, nValue );
}

void CServerVarInterface::DecGuildMission(int nValue)
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return; }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );
    pPlayer->OperateGuildMission( GuildDefine::OperateSub, nValue );
}

int32 CServerVarInterface::GetGuildSalary()
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return 0; }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );
    return pPlayer->GetGuildSalary();
}

void  CServerVarInterface::AddGuildSalary( int nValue )
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return; }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );
    pPlayer->OperateGuildSalary( GuildDefine::OperateAdd, nValue );
}

void  CServerVarInterface::DecGuildSalary( int nValue )
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return; }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );
    pPlayer->OperateGuildSalary( GuildDefine::OperateSub, nValue );
}

int16 CServerVarInterface::GetGuildLevel()
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return 0; }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );
    return pPlayer->GetGuildLevel();
}

void CServerVarInterface::SetGuildLevel( int nValue )
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return; }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );
    pPlayer->OperateGuildLevel( GuildDefine::OperateSet, nValue );
}

void CServerVarInterface::AddGuildVar( int nIndex, int nValue )
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return; }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );
    pPlayer->OperateGuildVar( GuildDefine::OperateAdd, nIndex, nValue );
}

void CServerVarInterface::DecGuildVar( int nIndex, int nValue )
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return; }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );
    pPlayer->OperateGuildVar( GuildDefine::OperateSub, nIndex, nValue );
}

void CServerVarInterface::SetGuildVar( int nIndex, int nValue )
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return; }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );
    pPlayer->OperateGuildVar( GuildDefine::OperateSet, nIndex, nValue );
}

int CServerVarInterface::GetGuildVar( int nIndex )
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return 0; }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );
    return pPlayer->GetGuildVar( nIndex );
}

bool CServerVarInterface::RecordGuildTimeVar( int nVarId )
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return false; }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );
    pPlayer->OperateGuildVar( GuildDefine::OperateSet, nVarId, RecordVarTime::FormatTimeVar() );
    return true;
}

bool CServerVarInterface::IsGuildTimeVarPassOneDay( int nVarId )
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return false; }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );
    GameGuild* pGuild = pPlayer->GetGuild();
    if ( pGuild == NULL )
    { return false; }

    return RecordVarTime::CheckPassOneDay( pGuild->GetGuildVar( nVarId ) );
}

void CServerVarInterface::ClearGuildTimeVar( int nVarId, int nClearVarId )
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return; }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );

    if ( IsGuildTimeVarPassOneDay( nVarId ) )
    {
        pPlayer->OperateGuildVar( GuildDefine::OperateSet, nClearVarId, 0 );
    }
}

void CServerVarInterface::GuildLevelUp()
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return; }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );
    pPlayer->GuildLevelUp();
}

void CServerVarInterface::GuildOfferBuild()
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return; }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );
    pPlayer->GuildOfferBuild();
}

void CServerVarInterface::GuildCollect()
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return; }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );
    pPlayer->GuildCollect();
}

void CServerVarInterface::GuildMasterDelate()
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return; }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );
    pPlayer->GuildMasterDelate();
}

void CServerVarInterface::GuildDonate()
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return; }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );
    pPlayer->GuildDonate();
}

bool CServerVarInterface::GuildQuestRelease( int nValue )
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return false; }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );
    return pPlayer->GuildQuestRelease( nValue );
}

int16 CServerVarInterface::GetGuildReleaseQuest()
{
	BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
	if ( pChar == NULL || !pChar->IsPlayer() )
	{ return false; }

	GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );
	return pPlayer->GetGuildReleaseQuest();
}


bool CServerVarInterface::GuildShopLevelUp( int nValue )
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return false; }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );
    return pPlayer->GuildShopLevelUp( nValue );
}

bool CServerVarInterface::GuildConvene()
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return false; }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );
    return pPlayer->GuildConvene();
}

void CServerVarInterface::AddGuildBuffByMapID(int MapID,int BuffID,int Level)
{
	BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return; }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );
	int GuildID = pPlayer->GetGuildID();
	if(MapID == -1)
		MapID = pPlayer->GetMapID();
	if(BuffID != 0 && Level != 0) //玩家刚进入的时候添加一个BUFF
	{
		GameStage* pGameStage = theGameWorld.GetStageById(MapID);
		if(pGameStage)
		{
			//获取地图块后 我们获取全部的玩家
			for(int i =0;i<pGameStage->GetCharacterCount();++i)
			{
				BaseCharacter * pBase = theRunTimeData.GetCharacterByID(pGameStage->GetCharacterID(i));
				if(pBase && pBase->IsPlayer())
				{
					GamePlayer * pPlayer = static_cast<GamePlayer*>(pBase);
					if(pPlayer && pPlayer->GetGuildID() == GuildID)
					{
						long nResult = GLR_Success;
						nResult = pPlayer->ApplyBufferStatus(BuffID,Level, pPlayer->GetID(), SCharBuff::StatusEventType_Other, 0);
						if ( nResult == GLR_Success  )
						{
							pPlayer->OnBuffStatusChanged( true );
						}
					}
				}
			}
		}
	}
}
