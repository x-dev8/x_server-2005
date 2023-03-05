#include "ServerVarInterface.h"
#include "ShareData.h"
#include "GamePlayer.h"
#include "GameBattleControl.h"
#include "GameWorld.h"
#include "MonsterCreater.h"
#include "GameGuildGeneralBattleConfig.h"
#include "GameGuildGeneralBattleManager.h"
#include "GameGuildGeneralBattle.h"
int CServerVarInterface::EnterGameGuildGeneralBattle()
{
	BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return 0; }
    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );
	//��ͼ����ҽ��뵽ս������ȥ
	GameGuild* pGuild = theGameGuildManager.GetGuild(pPlayer->GetGuildID());
	if(!pGuild)
		return 0;
	//��ҹ�����ڵĻ� ���ǻ�ȡս���Ĺ�����
	GameGuildGeneralBattleManager* pManager = static_cast<GameGuildGeneralBattleManager*>(theGameBattleControl.GetGameBattleManager(GameBattleDefine::GameBattle_Type_GuildGeneral));
	if(!pManager)
		return 0;
	GameGuildGeneralBattle* pBattle = pManager->GetGameBattleByUnitID(pPlayer->GetGuildID());
	if(!pBattle)
		return 0;
	if(!pManager->EnterGameBattle(pPlayer))
		return 0;
	return 1;
}
bool CServerVarInterface::IsInGameGuildGeneralBattle()
{
	//�жϵ�ǰ����Ƿ���ս������
	BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
		return false;
    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );
	GameGuildGeneralBattleManager* pManager = static_cast<GameGuildGeneralBattleManager*>(theGameBattleControl.GetGameBattleManager(GameBattleDefine::GameBattle_Type_GuildGeneral));
	if(!pManager)
		return false;
	GameGuildGeneralBattle* pBattle = pManager->GetGameBattleByPlayerID(pPlayer->GetDBCharacterID());
	if(pBattle)
	{
		if(pPlayer->GetMapID() != pBattle->GetBattleMapID())
			return false;
		return true;
	}
	else
		return false;
}
int CServerVarInterface::GetPlayerGameGuildGeneralBattleFigh()
{
	BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
		return -1;
    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );
	GameGuildGeneralBattleManager* pManager = static_cast<GameGuildGeneralBattleManager*>(theGameBattleControl.GetGameBattleManager(GameBattleDefine::GameBattle_Type_GuildGeneral));
	if(!pManager)
		return -1;
	GameGuild* pGuild = theGameGuildManager.GetGuild(pPlayer->GetGuildID());
	if(!pGuild)
		return -1;
	GameGuildGeneralBattle* pBattle = pManager->GetGameBattleByPlayerID(pPlayer->GetDBCharacterID());
	if(!pBattle)
		return -1;
	return pBattle->GetGameBattleFight(pGuild->GetID());
}
int CServerVarInterface::GetGameGuildGeneralBattleStates()
{
	BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
		return -1;
    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );
	GameGuildGeneralBattleManager* pManager = static_cast<GameGuildGeneralBattleManager*>(theGameBattleControl.GetGameBattleManager(GameBattleDefine::GameBattle_Type_GuildGeneral));
	if(!pManager)
		return -1;
	GameGuild* pGuild = theGameGuildManager.GetGuild(pPlayer->GetGuildID());
	if(!pGuild)
		return -1;
	GameGuildGeneralBattle* pBattle = pManager->GetGameBattleByUnitID(pGuild->GetID());
	if(!pBattle)
		return -1;
	return pBattle->GetStatus();
}
int CServerVarInterface::GetGameGuildGeneralBattleSource(unsigned int Fight)
{
	//��ȡָ���Լ�����
	BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
		return 0;
    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );
	GameGuildGeneralBattleManager* pManager = static_cast<GameGuildGeneralBattleManager*>(theGameBattleControl.GetGameBattleManager(GameBattleDefine::GameBattle_Type_GuildGeneral));
	if(!pManager)
		return 0;
	GameGuild* pGuild = theGameGuildManager.GetGuild(pPlayer->GetGuildID());
	if(!pGuild)
		return 0;
	GameGuildGeneralBattle* pBattle = pManager->GetGameBattleByPlayerID(pPlayer->GetDBCharacterID());
	if(!pBattle)
		return 0;
	return pBattle->GetGameBattleResource(Fight);
}
void CServerVarInterface::ChangeGameGuildGeneralBattleSource(unsigned int Fight,int Value)
{
	if(Value == 0)
		return;
	BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
		return;
    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );
	GameGuildGeneralBattleManager* pManager = static_cast<GameGuildGeneralBattleManager*>(theGameBattleControl.GetGameBattleManager(GameBattleDefine::GameBattle_Type_GuildGeneral));
	if(!pManager)
		return;
	GameGuild* pGuild = theGameGuildManager.GetGuild(pPlayer->GetGuildID());
	if(!pGuild)
		return;
	GameGuildGeneralBattle* pBattle = pManager->GetGameBattleByPlayerID(pPlayer->GetDBCharacterID());
	if(!pBattle)
		return;
	//����ս���Ļ���
	if(Fight == GameBattleDefine::GameBattle_Red)
		pBattle->SetRedResource(pBattle->GetRedResource()+Value);
	else if(Fight == GameBattleDefine::GameBattle_Blue)
		pBattle->SetBlueResource(pBattle->GetBlueResource()+Value);
}
void CServerVarInterface::SetGameGuildGeneralBattleSource(unsigned int Fight,int Value)
{
	BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
		return;
    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );
	GameGuildGeneralBattleManager* pManager = static_cast<GameGuildGeneralBattleManager*>(theGameBattleControl.GetGameBattleManager(GameBattleDefine::GameBattle_Type_GuildGeneral));
	if(!pManager)
		return;
	GameGuild* pGuild = theGameGuildManager.GetGuild(pPlayer->GetGuildID());
	if(!pGuild)
		return;
	GameGuildGeneralBattle* pBattle = pManager->GetGameBattleByPlayerID(pPlayer->GetDBCharacterID());
	if(!pBattle)
		return;
	if(Fight == GameBattleDefine::GameBattle_Red)
		pBattle->SetRedResource(Value);
	else if(Fight == GameBattleDefine::GameBattle_Blue)
		pBattle->SetBlueResource(Value);
}
void CServerVarInterface::CreateGameGuildGeneralBattleMonster( int nMonsterID, int nCount, int nMapId, float fPosX, float fPosY, int nFight, float fRadius, float fBodySize, int nRouteID )
{
	MonsterCreateData xCreateData;
    xCreateData.SetMonsterID( nMonsterID );
    xCreateData.SetCount( nCount );
    xCreateData.SetMapID( nMapId );
    xCreateData.SetPostionX( fPosX );
    xCreateData.SetPostionY( fPosY );
    xCreateData.SetDirX( 0.f );
    xCreateData.SetDirY( 0.f );
    xCreateData.SetRadius( fRadius );
    xCreateData.SetBodySize( fBodySize );
    xCreateData.SetFightCamp( nFight );
    xCreateData.SetRouteID( nRouteID );
    MonsterCreater::ProcessCreateNormalMonster( xCreateData );

}
void CServerVarInterface::CreateGameGuildGeneralBattleMonster( int nMonsterID, int nCount, float fRadius, float fBodySize, int nRouteID )
{
	BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
		return;
    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );
	MonsterCreateData xCreateData;
    xCreateData.SetMonsterID( nMonsterID );
    xCreateData.SetCount( nCount );
    xCreateData.SetMapID( pPlayer->GetMapID() );
    xCreateData.SetPostionX( pPlayer->GetFloatX() );
    xCreateData.SetPostionY( pPlayer->GetFloatY() );
    xCreateData.SetDirX( pPlayer->GetDirX() );
    xCreateData.SetDirY( pPlayer->GetDirY() );
    xCreateData.SetRadius( fRadius );
    xCreateData.SetBodySize( fBodySize );
    xCreateData.SetFightCamp( pPlayer->GetFightCamp() );
    xCreateData.SetRouteID( nRouteID );
    MonsterCreater::ProcessCreateNormalMonster( xCreateData );
}