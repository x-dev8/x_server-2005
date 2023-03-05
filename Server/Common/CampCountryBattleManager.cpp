#include "CampCountryBattleManager.h"
#include "CampCountryBattleConfig.h"
#include "CampCountryBattle.h"
#include "CampBattleMessage.h"
#include "GuildManager.h"
#include "GameWorld.h"
#include "GamePlayer.h"
#include "CountryReward.h"
#include "ShareData.h"
#include "LogEventService.h"
CampCountryBattleManager::CampCountryBattleManager() : m_nGuildStrength( 0 ), m_nSignUpGuildID( 0 )
{
	switch ( GetCountryBattleType() )
    {
    case CountryDefine::Battle_King:        // ��������ս
		m_BattleValue = GuildDefine::CampBattleCountry;
		m_BattleValueIsOpen = theGameGuildManager.GetCampBattleConfig()->m_CountrySetting.IsOpen;
        break;
	default:
		m_BattleValueIsOpen = false;
		m_BattleValue = 0;
		break;
	}
}

// ����ת����׼��״̬�߼�
void CampCountryBattleManager::ProcessChangeToPrepareStatus()
{
    m_nSignUpGuildID = GuildDefine::InitID;
    m_mapMatchUnit.clear();

    GameCountry* pCountry = theGameCountryManager.GetCountry( GetCountryID() );
    if ( pCountry == NULL )
    { return; }

    unsigned int nSignUpGuildID = GuildDefine::InitID;
    // ������б����İ�����Ϣ, 
    for ( SignUpVectorIter iter = m_vecSignUp.begin(); iter != m_vecSignUp.end(); ++iter )
    {
        GameGuild* pGuild = theGameGuildManager.GetGuild( *iter );
        if ( pGuild == NULL )
        { continue; }

        nSignUpGuildID = pGuild->GetID();
    }

    m_vecSignUp.clear();

    unsigned int nMasterGuildID = GuildDefine::InitID;
    switch ( GetCountryBattleType() )
    {
    case CountryDefine::Battle_King:        // ��������ս
        nMasterGuildID = pCountry->GetKingGuild();
        break;
    case CountryDefine::Battle_Dragon:      // ��������ս
        nMasterGuildID = pCountry->GetDragonGuild();
        break;
    case CountryDefine::Battle_Rosefinch:   // ��ȸ����ս
        nMasterGuildID = pCountry->GetRosefinchGuild();
        break;
    default:
        return;
    }

    // ���û����ս����, ֱ��ʤ��
    if ( nSignUpGuildID == GuildDefine::InitID )
    {
        if ( nMasterGuildID == GuildDefine::InitID )    
        {
            // ��û��, ս��ֱ�ӽ���
            ProcessBattleEndStatus();
            return;
        }

        SendCountryBattleResultMessage( nMasterGuildID, CountryDefine::BattleWin_Guard );
        return;
    }

    m_nSignUpGuildID = nSignUpGuildID;
    m_mapMatchUnit[ nMasterGuildID ] = nSignUpGuildID;

    // ֪ͨȫ��, ĳ�����ɻ������ս�ʸ�
    MsgTellCountryBattleGuild xTell;
    xTell.nGuildID      = nSignUpGuildID;
    xTell.uchBattleType = GetCountryBattleType();
    GettheServer().SendMsgToCountry( &xTell, GetCountryID(), true );
}

// ����ת��������״̬�߼�
void CampCountryBattleManager::ProcessChangeToEnterStatus()
{
    // ������������, 
    for ( MatchUnitMapIter iter = m_mapMatchUnit.begin(); iter != m_mapMatchUnit.end(); ++iter )
    {
        // ��������
		CampCountryBattleConfig* pBattleConfig = static_cast< CampCountryBattleConfig* >( m_pBattleConfig );
		//pBattleConfig->SetBlueScore();
		//pBattleConfig->SetRedScore();

        unsigned int nBattleMapID = theGameWorld.GetEctypeMapID( GetMapID(), true );
        theGameWorld.MultiCreateStage( GetMapID(), nBattleMapID );

        // ����ս��
        CampBattle* pCampBattle = CampBattle::CreateBattle< CampCountryBattle >();
        pCampBattle->SetBattleManager( this );
        pCampBattle->SetBattleMapID( nBattleMapID );
        pCampBattle->SetRedID( iter->first );
        pCampBattle->SetBlueID( iter->second );
		pCampBattle->SetBlueResource(pBattleConfig->GetBlueScore());
		pCampBattle->SetRedResource(pBattleConfig->GetRedScore());//���ó�ʼ������
		pCampBattle->SetWinResource(pBattleConfig->GetResourceSetting().GetMaxResource());
        // �����Ƿ����ս����Ϣ
        pCampBattle->SendEnterCampBattleMessage();
		
		//this->EnterCampBattle()


        // ��ӵ�ս���б���
        AddCampBattle( pCampBattle );
    }

	
    m_nSignUpGuildID = GuildDefine::InitID;
    m_mapMatchUnit.clear();
}

//����ת����ս��״̬
void CampCountryBattleManager::ProcessChangeToFightStatus()
{
	//Ҫ��m_mapBattlePlayer�����а���Ա������
	CampBattleManager::ProcessChangeToFightStatus();
}

// ����ս������
bool CampCountryBattleManager::SignUpCampBattle( GamePlayer* pPlayer )
{
    GameCountry* pCountry = theGameCountryManager.GetCountry( GetCountryID() );
    if ( pCountry == NULL )
    { return false; }

    // �жϰ������
    GameGuild* pGuild = pPlayer->GetGuild();
    if ( pGuild == NULL || !pGuild->IsMaster( pPlayer->GetDBCharacterID() ) )
    {
        pPlayer->SendOperateAckToClient< MsgCampBattleSignUpAck >( CampDefine::SignUp_MustGuildMaster );
        return false;
    } 
	
	if ( !CampBattleManager::SignUpCampBattle( pPlayer, pGuild->GetID() ) )
    { return false; }


    switch ( GetCountryBattleType() )
    {
    case CountryDefine::Battle_King:
        {
            if ( pCountry->GetKingGuild() == pGuild->GetID() )
            {
                pPlayer->SendOperateAckToClient< MsgCampBattleSignUpAck >( CampDefine::SignUp_CanNotSignUp );
                return false;
            }
        }
        break;
    case CountryDefine::Battle_Dragon:
    case CountryDefine::Battle_Rosefinch:
        {
            if ( pCountry->GetDragonGuild() == pGuild->GetID() || pCountry->GetRosefinchGuild() == pGuild->GetID() || pCountry->GetKingGuild() == pGuild->GetID() )
            {
                pPlayer->SendOperateAckToClient< MsgCampBattleSignUpAck >( CampDefine::SignUp_CanNotSignUp );
                return false;
            }
        }
        break;
    default:
        return false;
    }

    const CampCountryBattleConfig* pBattleConfig = static_cast< const CampCountryBattleConfig* >( m_pBattleConfig );
    const CampCountryBattleConfig::SignUpSetting& xSetting = pBattleConfig->GetSignUpSetting();

    if ( pGuild->GetLevel() < xSetting.GetMinGuildLevel() )
    {
        pPlayer->SendOperateAckToClient< MsgCampBattleSignUpAck >( CampDefine::SignUp_GuildLevelLess );
        return false;
    }

    if ( pGuild->MemberCount() < xSetting.GetMinMemberCount() )
    {
        pPlayer->SendOperateAckToClient< MsgCampBattleSignUpAck >( CampDefine::SignUp_GuildMemberLess );
        return false;
    }

    if ( pGuild->GetMoney() < xSetting.GetCostGuildMoney() )
    {
        pPlayer->SendOperateAckToClient< MsgCampBattleSignUpAck >( CampDefine::SignUp_NotEnoughGuildMoney );
        return false;
    }

    // �жϰ��ʵ��
    unsigned int nStrength = pGuild->GetGuildStrength();
    if ( nStrength < m_nGuildStrength )
    {
        pPlayer->SendOperateAckToClient< MsgCampBattleSignUpAck >( CampDefine::SignUp_GuildStrengthLess /*,(m_nGuildStrength - nStrength),nStrength*/);
        return false;
    }

    // ����CenterServer���ɿ�Ǯ
    pGuild->SendGuildDataChangeReqMessage( GuildDefine::UpdateGuildMoney, GuildDefine::OperateSub, xSetting.GetCostGuildMoney() );

	//LYH��־��� �������Ǯ���٣�
	theLogEventService.LogGuildDetail(pPlayer->GetAccountID(),pPlayer->GetDBCharacterID(),pGuild->GetID(),xSetting.GetCostGuildMoney(),0,0,pPlayer->GetCharName());


    //LYH��־��� ������ս������
	theLogEventService.LogGuild(pPlayer->GetAccountID(),pPlayer->GetDBCharacterID(),pGuild->GetID(),eSystemLogInfo_guild_SignUpKingWar,pPlayer->GetCharName());

    // �����ɹ�, ���û�й���, ����, ��ȸս��
    switch ( GetCountryBattleType() )
    {
    case CountryDefine::Battle_King:
        {
            if ( !pCountry->IsHaveKing() )      // ��û�й���, ��һ�������ɹ��߼���Ϊ����
            {
                SendCountryBattleResultMessage( pGuild->GetID(), CountryDefine::BattleWin_FistTime );
                ProcessChangeStatus( CampDefine::StatusEnd );
                return true;
            }
        }
        break;
    case CountryDefine::Battle_Dragon:
        {
            if ( !pCountry->IsHaveDragon() )      // ��û������֮��, ��һ�������ɹ��߼���Ϊ��������
            {
                SendCountryBattleResultMessage( pGuild->GetID(), CountryDefine::BattleWin_FistTime );
                ProcessChangeStatus( CampDefine::StatusEnd );
                return true;
            }
        }
        break;
    case CountryDefine::Battle_Rosefinch:
        {
            if ( !pCountry->IsHaveRosefinch() )      // ��û����ȸ֮��, ��һ�������ɹ��߼���Ϊ��ȸ����
            {
                SendCountryBattleResultMessage( pGuild->GetID(), CountryDefine::BattleWin_FistTime );
                ProcessChangeStatus( CampDefine::StatusEnd );
                return true;
            }
        }
        break;
    default:
        return false;
    }

    if ( !m_vecSignUp.empty() ) // �Ѿ��а��ɱ�����, ����֮
    {
        unsigned int nGuildID = m_vecSignUp.front();
        GameGuild* pReplaceGuild = theGameGuildManager.GetGuild( nGuildID );
        if ( pReplaceGuild != NULL )   // ֪ͨ�Է�����, ��ı������������
        {
            GamePlayer* pPlayer = GameGuild::GetPlayer( pReplaceGuild->GetMasterID() );
            if ( pPlayer != NULL )
            {
                MsgTellCampBattleSignUpReplace xReplace;
                xReplace.uchBattleType = GetBattleType();
                pPlayer->SendMessageToClient( &xReplace );
            }
        }

        m_vecSignUp.clear();
    }

    // ���ñ�������ID ��ʵ��
    m_nGuildStrength = nStrength;
    AddSignUpUnit( pGuild->GetID() );

	
    pPlayer->SendOperateAckToClient< MsgCampBattleSignUpAck >( CampDefine::SignUp_Success );
    return true;
}

bool CampCountryBattleManager::ShowCampBattleEnter( GamePlayer* pPlayer )
{
    GameGuild* pGuild = pPlayer->GetGuild();
    if ( pGuild == NULL )
    { return false; }

    return CampBattleManager::ShowCampBattleEnter( pPlayer, pGuild->GetID() );
}

bool CampCountryBattleManager::EnterCampBattle( GamePlayer* pPlayer )
{
    GameGuild* pGuild = pPlayer->GetGuild();
    if ( pGuild == NULL )
    { 
        pPlayer->SendOperateAckToClient< MsgEnterCampBattleAck >( CampDefine::Enter_MustSignUpGuild );
        return false;
    }

    return CampBattleManager::EnterCampBattle( pPlayer, pGuild->GetID() );   
}

void CampCountryBattleManager::SendCountryBattleResultMessage( unsigned int nWinID, unsigned char uchWinType ,unsigned int nLoseID,unsigned int nCampBattle)
{
    GS2CSCountryBattleResult xResult;
    xResult.uchCountryID  = GetCountryID();
    xResult.uchBattleType = GetCountryBattleType();
    xResult.nGuildID      = nWinID;
    xResult.uchWinType    = uchWinType;
	xResult.nLoseGuildID = nLoseID;
	xResult.nCampBattle = nCampBattle;
    GettheServer().SendMsgToCenterServer( &xResult );

	if(xResult.uchBattleType == CountryDefine::Battle_King)
	{
		//��������֪ͨCenter ����¹���
		GS2CSAddCountryOfficial msg;
		msg.uchCountryID = GetCountryID();
		GameGuild * pGuild = theGameGuildManager.GetGuild(nWinID);	
		if(!pGuild)
			return;
		msg.position = CountryDefine::Position_King;
		GamePlayer * pPlayer = theRunTimeData.GetGamePlayerByDBID( pGuild->GetMasterID() );
		msg.nPlayerID = pGuild->GetMasterID();
		if(pPlayer)
		{
			HelperFunc::SafeNCpy( msg.szName, pPlayer->GetCharName(), sizeof( msg.szName ) );
			msg.sexID = pPlayer->GetCharInfo().baseinfo.aptotic.ucSex;
			msg.faceID = pPlayer->GetCharInfo().visual.faceId;
			msg.headerID = pPlayer->GetCharInfo().visual.hairId;
			msg.professionID = pPlayer->GetCharInfo().baseinfo.aptotic.usProfession;
		}
		else
		{
			GuildMember * pMember = pGuild->GetMember(pGuild->GetMasterID());
			if(!pMember) return;
			HelperFunc::SafeNCpy( msg.szName, pMember->GetName(), sizeof( msg.szName ) );
			msg.sexID = -1;
			msg.faceID = -1;
			msg.headerID = -1;
			msg.professionID = -1;
		}	
		GettheServer().SendMsgToCenterServer( &msg );
	}
}

