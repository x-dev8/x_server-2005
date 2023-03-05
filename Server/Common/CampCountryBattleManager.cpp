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
    case CountryDefine::Battle_King:        // 国王争夺战
		m_BattleValue = GuildDefine::CampBattleCountry;
		m_BattleValueIsOpen = theGameGuildManager.GetCampBattleConfig()->m_CountrySetting.IsOpen;
        break;
	default:
		m_BattleValueIsOpen = false;
		m_BattleValue = 0;
		break;
	}
}

// 处理转换到准备状态逻辑
void CampCountryBattleManager::ProcessChangeToPrepareStatus()
{
    m_nSignUpGuildID = GuildDefine::InitID;
    m_mapMatchUnit.clear();

    GameCountry* pCountry = theGameCountryManager.GetCountry( GetCountryID() );
    if ( pCountry == NULL )
    { return; }

    unsigned int nSignUpGuildID = GuildDefine::InitID;
    // 获得所有报名的帮派信息, 
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
    case CountryDefine::Battle_King:        // 国王争夺战
        nMasterGuildID = pCountry->GetKingGuild();
        break;
    case CountryDefine::Battle_Dragon:      // 青龙争夺战
        nMasterGuildID = pCountry->GetDragonGuild();
        break;
    case CountryDefine::Battle_Rosefinch:   // 朱雀争夺战
        nMasterGuildID = pCountry->GetRosefinchGuild();
        break;
    default:
        return;
    }

    // 如果没有挑战帮派, 直接胜利
    if ( nSignUpGuildID == GuildDefine::InitID )
    {
        if ( nMasterGuildID == GuildDefine::InitID )    
        {
            // 都没有, 战场直接结束
            ProcessBattleEndStatus();
            return;
        }

        SendCountryBattleResultMessage( nMasterGuildID, CountryDefine::BattleWin_Guard );
        return;
    }

    m_nSignUpGuildID = nSignUpGuildID;
    m_mapMatchUnit[ nMasterGuildID ] = nSignUpGuildID;

    // 通知全国, 某个帮派获得了挑战资格
    MsgTellCountryBattleGuild xTell;
    xTell.nGuildID      = nSignUpGuildID;
    xTell.uchBattleType = GetCountryBattleType();
    GettheServer().SendMsgToCountry( &xTell, GetCountryID(), true );
}

// 处理转换到进入状态逻辑
void CampCountryBattleManager::ProcessChangeToEnterStatus()
{
    // 创建副本场景, 
    for ( MatchUnitMapIter iter = m_mapMatchUnit.begin(); iter != m_mapMatchUnit.end(); ++iter )
    {
        // 创建副本
		CampCountryBattleConfig* pBattleConfig = static_cast< CampCountryBattleConfig* >( m_pBattleConfig );
		//pBattleConfig->SetBlueScore();
		//pBattleConfig->SetRedScore();

        unsigned int nBattleMapID = theGameWorld.GetEctypeMapID( GetMapID(), true );
        theGameWorld.MultiCreateStage( GetMapID(), nBattleMapID );

        // 创建战场
        CampBattle* pCampBattle = CampBattle::CreateBattle< CampCountryBattle >();
        pCampBattle->SetBattleManager( this );
        pCampBattle->SetBattleMapID( nBattleMapID );
        pCampBattle->SetRedID( iter->first );
        pCampBattle->SetBlueID( iter->second );
		pCampBattle->SetBlueResource(pBattleConfig->GetBlueScore());
		pCampBattle->SetRedResource(pBattleConfig->GetRedScore());//设置初始化积分
		pCampBattle->SetWinResource(pBattleConfig->GetResourceSetting().GetMaxResource());
        // 发送是否进入战场消息
        pCampBattle->SendEnterCampBattleMessage();
		
		//this->EnterCampBattle()


        // 添加到战场列表中
        AddCampBattle( pCampBattle );
    }

	
    m_nSignUpGuildID = GuildDefine::InitID;
    m_mapMatchUnit.clear();
}

//处理转换到战斗状态
void CampCountryBattleManager::ProcessChangeToFightStatus()
{
	//要在m_mapBattlePlayer容器中把人员都加上
	CampBattleManager::ProcessChangeToFightStatus();
}

// 处理战场报名
bool CampCountryBattleManager::SignUpCampBattle( GamePlayer* pPlayer )
{
    GameCountry* pCountry = theGameCountryManager.GetCountry( GetCountryID() );
    if ( pCountry == NULL )
    { return false; }

    // 判断帮会条件
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

    // 判断帮会实力
    unsigned int nStrength = pGuild->GetGuildStrength();
    if ( nStrength < m_nGuildStrength )
    {
        pPlayer->SendOperateAckToClient< MsgCampBattleSignUpAck >( CampDefine::SignUp_GuildStrengthLess /*,(m_nGuildStrength - nStrength),nStrength*/);
        return false;
    }

    // 请求CenterServer帮派扣钱
    pGuild->SendGuildDataChangeReqMessage( GuildDefine::UpdateGuildMoney, GuildDefine::OperateSub, xSetting.GetCostGuildMoney() );

	//LYH日志添加 （工会金钱减少）
	theLogEventService.LogGuildDetail(pPlayer->GetAccountID(),pPlayer->GetDBCharacterID(),pGuild->GetID(),xSetting.GetCostGuildMoney(),0,0,pPlayer->GetCharName());


    //LYH日志添加 （国王战报名）
	theLogEventService.LogGuild(pPlayer->GetAccountID(),pPlayer->GetDBCharacterID(),pGuild->GetID(),eSystemLogInfo_guild_SignUpKingWar,pPlayer->GetCharName());

    // 报名成功, 如果没有国王, 青龙, 朱雀战场
    switch ( GetCountryBattleType() )
    {
    case CountryDefine::Battle_King:
        {
            if ( !pCountry->IsHaveKing() )      // 还没有国王, 第一个报名成功者即成为国王
            {
                SendCountryBattleResultMessage( pGuild->GetID(), CountryDefine::BattleWin_FistTime );
                ProcessChangeStatus( CampDefine::StatusEnd );
                return true;
            }
        }
        break;
    case CountryDefine::Battle_Dragon:
        {
            if ( !pCountry->IsHaveDragon() )      // 还没有青龙之主, 第一个报名成功者即成为青龙帮主
            {
                SendCountryBattleResultMessage( pGuild->GetID(), CountryDefine::BattleWin_FistTime );
                ProcessChangeStatus( CampDefine::StatusEnd );
                return true;
            }
        }
        break;
    case CountryDefine::Battle_Rosefinch:
        {
            if ( !pCountry->IsHaveRosefinch() )      // 还没有朱雀之主, 第一个报名成功者即成为朱雀帮主
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

    if ( !m_vecSignUp.empty() ) // 已经有帮派报名了, 顶替之
    {
        unsigned int nGuildID = m_vecSignUp.front();
        GameGuild* pReplaceGuild = theGameGuildManager.GetGuild( nGuildID );
        if ( pReplaceGuild != NULL )   // 通知对方帮主, 你的报名被顶替掉了
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

    // 设置报名帮会的ID 和实力
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
		//发送命令通知Center 添加新国王
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

