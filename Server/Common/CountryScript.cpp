#include "ServerVarInterface.h"
#include "ShareData.h"
#include "Configure.h"
#include "GamePlayer.h"
#include "CountryManager.h"

bool CServerVarInterface::IsHaveCountryMaster( unsigned char uchType, unsigned char uchCountry )
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return false;  }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );
    return pPlayer->IsHaveCountryMaster( uchType, uchCountry );
}

bool CServerVarInterface::ReceiveCountryMount( unsigned char uchType )
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return false;  }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );
    return pPlayer->ReceiveCountryMount( uchType );
}

bool CServerVarInterface::CountryConenve()
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return false;  }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );
    return pPlayer->CountryConenve();
}

bool CServerVarInterface::IsCountryMaster( unsigned char uchType )
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return false;  }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );
    return pPlayer->IsCountryMaster( uchType );
}

bool CServerVarInterface::IsCountryGuild( unsigned char uchType )
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return false;  }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );
    return pPlayer->IsCountryGuild( uchType );
}


bool CServerVarInterface::IsCountryQueen()
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return false;  }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );
    return pPlayer->IsCountryQueen();
}

void CServerVarInterface::AddCountryResource( unsigned char uchType, unsigned int nValue )
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return;  }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );
    pPlayer->AddCountryResource( uchType, nValue );
}

void CServerVarInterface::SubCountryResource( unsigned char uchType, unsigned int nValue )
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return;  }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );
    pPlayer->SubCountryResource( uchType, nValue );
}

int CServerVarInterface::GetCountryID()
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return 0;  }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );
    return pPlayer->GetCountry();
}

bool CServerVarInterface::IsCountryQuestOpen( unsigned char uchType )
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return false;  }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );
    return pPlayer->IsCountryQuestOpen( uchType );
}

uint32 CServerVarInterface::GetCountryScore()
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return 0;  }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );
    return pPlayer->GetCountryScore();
}

void CServerVarInterface::AddCountryScore( int nValue )
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return;  }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );
    pPlayer->OperateTeamCountryScore( EOT_Add, nValue );
}

void CServerVarInterface::SubCountryScore( int nValue )
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return;  }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );
    pPlayer->OperateTeamCountryScore( EOT_Sub, nValue );
}

void CServerVarInterface::SetCountryScore( int nValue )
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return;  }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );
    pPlayer->OperateTeamCountryScore( EOT_Set, nValue );
}

int CServerVarInterface::GetCountryOfficial()
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return 0;  }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );
    return pPlayer->GetCountryOfficial();
}

int CServerVarInterface::GetWarSortIndex()
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
    if ( pChar == NULL || !pChar->IsPlayer() )
    { return 0;  }

    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );
    return pPlayer->GetWarSortIndex();
}

bool CServerVarInterface::IsInCountryWarFight()
{
    return theGameCountryManager.CheckInCountryWarFight();
}

bool CServerVarInterface::SetCountryKing()
{
	BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
	if ( pChar == NULL || !pChar->IsPlayer() )
	{ return false;  }

	GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );
	 return pPlayer->SetCountryKing();
}


bool CServerVarInterface::IsPlayerKing()
{
	BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
	if ( pChar == NULL || !pChar->IsPlayer() )
	{ return false;  }

	GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );
	return pPlayer->IsPlayerKing();
}

void CServerVarInterface::SetCountryTribute(int nValue,int countryid,int operType)
{
	BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
	if ( pChar == NULL || !pChar->IsPlayer()||countryid == 0)
	{ return ;}

	GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );
	if (countryid < 0)
	{
		countryid = pPlayer->GetCountry();
	}
	pPlayer->SetCountryTribute(nValue,countryid,operType);
}

int CServerVarInterface::GetCountryTribute(int countryid)
{
	BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
	if ( pChar == NULL || !pChar->IsPlayer()||countryid == 0)
	{ return -1;}

	GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );
	if (countryid < 0)
	{
		countryid = pPlayer->GetCountry();
	}
	return pPlayer->GetCountryTribute(countryid);
}
void CServerVarInterface::AddCountryInfo(const char * Info,bool IsUseName,int Value)
{
	BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetCurCharId() );
	if ( pChar == NULL || !pChar->IsPlayer())
	{ return;}
	GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );
	char str[CountryDefine::MaxCountryInfoLength]={0};
	if(IsUseName)
		sprintf_s(str,CountryDefine::MaxCountryInfoLength-1,Info,pPlayer->gCharInfoServer.baseinfo.aptotic.szCharacterName);
	else
		strcpy_s(str,CountryDefine::MaxCountryInfoLength-1,Info);
	GS2CSAddCountryInfoReq msg;
	msg.uchCountryID = pPlayer->GetCountryId();
	strcpy_s(msg.szNotice,CountryDefine::MaxCountryInfoLength-1,str);
	msg.Value = Value;
	time_t now;
	time(&now);
	msg.Time =now; 
	GettheServer().SendMsgToCenterServer( &msg );
}