#include "ServerVarInterface.h"
#include "ShareData.h"
#include "GamePlayer.h"
#include "CampBattleControl.h"
#include "CampBattle.h"
#include "GameWorld.h"
#include "MonsterCreater.h"
#include "CampCountryBattleConfig.h"
int CServerVarInterface::GetBattleCamp()
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return CampDefine::NoneCamp; }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );
    return CampDefine::GetBaseFightCamp( pPlayer->GetFightCamp() );
}

int CServerVarInterface::GetCampBattleStatus( int nType ,int countryid)
{
    CampBattleManager* pManager = theCampBattleControl.GetManagerBytypeAndCountry(nType,countryid);/* theCampBattleControl.GetManager( nType );*/
    if ( pManager == NULL )
    { return CampDefine::StatusInit; }

    return pManager->GetBattleStatus();
}

//
bool CServerVarInterface::ShowCampBattleSignUp( int nType)
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return false; }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );

    CampBattleManager* pManager = theCampBattleControl.GetManagerBytypeAndCountry(nType ,pPlayer->GetCountryId());
    if ( pManager == NULL )
    { return false; }

    return pManager->ShowCampBattleSignUp( pPlayer );
}

bool CServerVarInterface::SignUpCampBattle( int nType )
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return false; }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );

    CampBattleManager* pManager = theCampBattleControl.GetManagerBytypeAndCountry( nType,pPlayer->GetCountryId() );
    if ( pManager == NULL )
    { return false; }

    return pManager->SignUpCampBattle( pPlayer );
}

bool CServerVarInterface::ShowCampBattleEnter( int nType )
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return false; }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );

    CampBattleManager* pManager = theCampBattleControl.GetManagerBytypeAndCountry( nType,pPlayer->GetCountryId() );
    if ( pManager == NULL )
    { return false; }

    return pManager->ShowCampBattleEnter( pPlayer );
}

bool CServerVarInterface::EnterCampBattle( int nBattleType )
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return false; }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );

    CampBattleManager* pManager = theCampBattleControl.GetManagerBytypeAndCountry( nBattleType,pPlayer->GetCountryId() );
    if ( pManager == NULL )
    { return false; }

    return pManager->EnterCampBattle( pPlayer );
}

void CServerVarInterface::AddCampBattleResource( int nAddValue )
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return; }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );

    CampBattle* pCampBattle = theCampBattleControl.GetCampBattle( pPlayer->GetFightCamp(), pPlayer->GetMapID(),pPlayer->GetCountryId() );
    if ( pCampBattle == NULL )
    { return; }

    pCampBattle->ProcessAddCampResource( pPlayer->GetFightCamp(), nAddValue );
}

int CServerVarInterface::GetCampBattleResource()
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return 0; }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );

    CampBattle* pCampBattle = theCampBattleControl.GetCampBattle( pPlayer->GetFightCamp(), pPlayer->GetMapID() ,pPlayer->GetCountryId());
    if ( pCampBattle == NULL )
    { return 0; }

    return pCampBattle->GetCampBattleResource( pPlayer->GetFightCamp() );
}

void CServerVarInterface::KillCampBattleMonster( int nMonsterID )
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return; }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );

    pPlayer->KillCampBattleMonster( nMonsterID );
}

void CServerVarInterface::CreateCampMonster( int nMonsterID, int nCount, float fRadius, float fBodySize, int nRouteID )
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return; }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );
    if ( pPlayer->GetFightCamp() == CampDefine::NoneCamp )
    { return; }

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

void CServerVarInterface::CreateCampMonster( int nMonsterID, int nCount, int nMapId, float fPosX, float fPosY, int nFightCamp, float fRadius, float fBodySize, int nRouteID )
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
    xCreateData.SetFightCamp( nFightCamp );
    xCreateData.SetRouteID( nRouteID );
    MonsterCreater::ProcessCreateNormalMonster( xCreateData );
}

void CServerVarInterface::QueryCampBattleSignUp( unsigned char nBattleType )
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return; }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );
    pPlayer->QueryCampBattleSignUp( nBattleType );
}
void CServerVarInterface::ChangeCampBattleScore(int IsRadOrBlue,int ChangeType,int Value)
{
	BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return; }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );
	CampBattle* pCampBattle =theCampBattleControl.GetCampBattle(pPlayer->GetDBCharacterID());
	if(!pCampBattle)
		return;
	if(pCampBattle->GetBattleManager()->GetBattleType() == CampDefine::BattleTypeKing)
	{
		//为国家战场的时候 
		CampCountryBattleConfig * pConfig = (CampCountryBattleConfig *)pCampBattle->GetBattleManager()->GetBattleConfig();
		if(!pConfig) return;
		int RedScore = pCampBattle->GetRedResource();
		int BlueScore= pCampBattle->GetBlueResource();
		switch(ChangeType)
		{
		case 1:
			RedScore += Value;
			BlueScore+=Value;
			break;
		case 2:
			RedScore -= Value;
			BlueScore-=Value;
			break;
		case 3:
			RedScore = Value;
			BlueScore=Value;
			break;
		}

		if(RedScore < 0)
			RedScore = 0;

		if(BlueScore < 0)
			BlueScore = 0;

		switch(IsRadOrBlue)
		{
		case 0:
			{
				if(ChangeType == 1)
					pCampBattle->ProcessAddCampResource(CampDefine::BaseCampRed,Value);
				else
					pCampBattle->SetRedResource(RedScore);
			}
			break;
		case 1:
			{
				if(ChangeType == 1)
					pCampBattle->ProcessAddCampResource(CampDefine::BaseCampBlue,Value);
				else
					pCampBattle->SetBlueResource(BlueScore);
			}
			break;
		case -1:
			{
				BattlePlayer*  pBPlayer =pCampBattle->GetBattlePlayer( pPlayer->GetDBCharacterID());
				if(pBPlayer && pBPlayer->GetFightCamp() == CampDefine::GuildCampRed)
				{
					if(ChangeType == 1)
						pCampBattle->ProcessAddCampResource(CampDefine::BaseCampRed,Value);
					else
						pCampBattle->SetRedResource(RedScore);
				}
				else if(pBPlayer && pBPlayer->GetFightCamp() == CampDefine::GuildCampBlue)
				{
					if(ChangeType == 1)
						pCampBattle->ProcessAddCampResource(CampDefine::BaseCampBlue,Value);
					else
						pCampBattle->SetBlueResource(BlueScore);
				}
			}
			break;
		}
	}
	else
	{
		int RedScore = pCampBattle->GetRedResource();
		int BlueScore= pCampBattle->GetBlueResource();
		switch(ChangeType)
		{
		case 1:
			RedScore += Value;
			BlueScore+=Value;
			break;
		case 2:
			RedScore -= Value;
			BlueScore-=Value;
			break;
		case 3:
			RedScore = Value;
			BlueScore=Value;
			break;
		}

		if(RedScore < 0)
			RedScore = 0;

		if(BlueScore < 0)
			BlueScore = 0;

		switch(IsRadOrBlue)
		{
		case 0:
			{
				if(ChangeType == 1)
					pCampBattle->ProcessAddCampResource(CampDefine::BaseCampRed,Value);
				else
					pCampBattle->SetRedResource(RedScore);
			}
			break;
		case 1:
			{
				if(ChangeType == 1)
					pCampBattle->ProcessAddCampResource(CampDefine::BaseCampBlue,Value);
				else
					pCampBattle->SetBlueResource(BlueScore);
			}
			break;
		case -1:
			{
				BattlePlayer*  pBPlayer =pCampBattle->GetBattlePlayer( pPlayer->GetDBCharacterID());
				if(pBPlayer && pBPlayer->GetFightCamp() == CampDefine::GuildCampRed)
				{
					if(ChangeType == 1)
						pCampBattle->ProcessAddCampResource(CampDefine::BaseCampRed,Value);
					else
						pCampBattle->SetRedResource(RedScore);
				}
				else if(pBPlayer && pBPlayer->GetFightCamp() == CampDefine::GuildCampBlue)
				{
					if(ChangeType == 1)
						pCampBattle->ProcessAddCampResource(CampDefine::BaseCampBlue,Value);
					else
						pCampBattle->SetBlueResource(BlueScore);
				}
			}
			break;
		}
	}
}
int CServerVarInterface::GetCampBattleFight()
{
	BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return -1; }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );
	CampBattle* pCampBattle =theCampBattleControl.GetCampBattle(pPlayer->GetDBCharacterID());
	if(!pCampBattle)
		return -1;
	if(!pCampBattle->GetBattlePlayer(GetCurCharId()))
		return -1;
	//获取玩家的阵营
	if(CampDefine::GetBaseFightCamp(pCampBattle->GetBattlePlayer(GetCurCharId())->GetFightCamp())== CampDefine::BaseCampRed)
		return 0;
	else
		return 1;
}