#include "NetEvent.h"
#include "RunStatusDefine.h"
#include "FuncPerformanceLog.h"
#include "GameServerManager.h"
#include "LoginServerManager.h"
#include "CenterServer.h"
#include "SqlService.h"
#include "Config.h"
#include "TradeCenterInfo.h"
#include "CountryManager.h"
#include "RelationManager.h"
#include "GuildManager.h"
#include "ConsignmentManager.h"
#include "CenterItemDropManager.h"
#include "FamilyManager.h"
#include "CenterFamily.h"
#include "GlobalDBManager.h"
#include "RunStatus.h"
//xuda #include "WantedManager.h"
#include "QuestEntrust.h"
#include "GameBattleDataManager.h"

void NetEvent::_OnRegiseterLoginServerInfo( NetClient* pNetClient, LS2CSRegiseterLoginServerInfoReq* pMessage  )
{
	if (theRunStatus.GetStatus() != RunStatusDefine::RunStatus_Running)
	{
		return;
	}

    LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Receive LoginServer Regiseter Information LoginServerId[%d], btReset[%d]", 
        pMessage->nLoginServerId, pMessage->btReset);

    unsigned long nLoginServerId = pMessage->nLoginServerId;

    LoginServerPeer* pLoginPeer = LoginServerManager::GetInstance().GetLoginServerPeer( nLoginServerId );
    if ( pLoginPeer )
    {
        if ( LS2CSRegiseterLoginServerInfoReq::ROT_NOT_REPLACE == pMessage->btReset )
        {
            theCenterServer.CloseConnection( ST_LoginServer, pNetClient );
            return;
        }
        else if ( GS2CSRegiseterGameServerInfoReq::ROT_REPLACE == pMessage->btReset )
        {
            LoginServerManager::GetInstance().RemoveLoginServerPeer( nLoginServerId );
        }        
    }

    pLoginPeer = LoginServerPeer::CreateInstance();
    if ( !pLoginPeer)
        return;

    pLoginPeer->SetId( pMessage->nLoginServerId);
    pLoginPeer->SetNetClient( pNetClient );
    LoginServerManager::GetInstance().AddLoginServerPeer( pLoginPeer );

    // Ϊ�������ùؼ���Ϣ �����Ժ����
    pNetClient->SetExtendData( pLoginPeer->GetId() );

    CS2LSRegiseterLoginServerInfoAck ackMsg;
    ackMsg.nResult = ER_Success;
    pNetClient->Send( &ackMsg );
}

void NetEvent::_OnRegisterGameServerInfo( NetClient* pNetClient, GS2CSRegiseterGameServerInfoReq* pMessage )
{
	if (theRunStatus.GetStatus() != RunStatusDefine::RunStatus_Running)
	{
		return;
	}
    /*std::string*/char IpAddr[20];
	pNetClient->GetSocket()->GetIP(IpAddr,20);/*NetApi::GetPeerIP(pNetClient->GetSocket());*/

    GameServerPeer* pGamePeer = theGameServerManager.GetGameServerPeer( pMessage->nServerId );
    if ( pGamePeer )
    {
        if ( GS2CSRegiseterGameServerInfoReq::ROT_NOT_REPLACE == pMessage->btReset )
        {
            LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "CenterServer::GetInstance().CloseConnection( ST_GameServer, pNetClient )");
            CenterServer::GetInstance().CloseConnection( ST_GameServer, pNetClient );
            return;
        }
        else if ( GS2CSRegiseterGameServerInfoReq::ROT_REPLACE == pMessage->btReset )
        {
			LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "theGameServerManager.RemoveGameServerPeer( pMessage->nServerId:%d )",pMessage->nServerId);
            theGameServerManager.RemoveGameServerPeer( pMessage->nServerId );			
        }
		else//GS2CSRegiseterGameServerInfoReq::ROT_LOOP
		{
			return;
		}
    }

    pGamePeer = GameServerPeer::CreateInstance();
    if ( pGamePeer==NULL)
    {
        LOG_MESSAGE(SYSTEMOBJECT, LOG_PRIORITY_INFO, "GameServerPeer::CreateInstance(%d) Fail", pMessage->nServerId );
        return;
    }

    if ( CHARACTERSERVERID == pMessage->nServerId)
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "ע�� CharacterServer[%s:%d:%s], btReset[%d] ��Ϣ", pMessage->szGameServerName, pMessage->nServerId , IpAddr/*.c_str() */,pMessage->btReset);
	}
	//else if ( CENTERLOGINSERVERID == pMessage->nServerId)
	//{
	//	LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "ע�� CenterLoginServer[%s:%d:%s], btReset[%d] ��Ϣ", pMessage->szGameServerName, pMessage->nServerId , IpAddr/*.c_str() */,pMessage->btReset);
	//}
    else
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "ע�� GameServer[%s:%d:%s], btReset[%d] ��Ϣ", pMessage->szGameServerName, pMessage->nServerId , IpAddr/*.c_str()*/ ,pMessage->btReset);
    }

    pGamePeer->SetName( pMessage->szGameServerName );
    pGamePeer->SetNetClient( pNetClient );
    pGamePeer->SetId( pMessage->nServerId );
    theGameServerManager.AddGameServerPeer( pGamePeer );

    // Ϊ�������ùؼ���Ϣ �����Ժ����
    pNetClient->SetExtendData( pMessage->nServerId );
    
    CS2GSRegiseterGameserverInfoAck ackMsg;
    ackMsg.nResult = ER_Success;
    pNetClient->Send( &ackMsg );

    if ( CHARACTERSERVERID != pMessage->nServerId )
    {
        // ֪ͨ��Ʒ��ֵ
        theCenterItemDropManager.SendDropControlToGameServer( pMessage->nServerId );

        // ���߹�����Ϣ
        theCenterCountryManager.SendCountryDataToGameServer( pMessage->nServerId );

        // ֪ͨ��ϵ��Ϣ
        theCenterRelationManager.SendRelationList2Client( pMessage->nServerId );

        // ���߹�����Ϣ
        theCenterGuildManager.SendGuildListToClient( pMessage->nServerId );

		// ֪ͨ������Ϣ
		theCenterFamilyManager.SendAllFamiliesToClient( pMessage->nServerId/*RelationDefine::InitID*/ );

        // ֪ͨϵͳ������Ϣ
        theCenterSysVarManager.SendSysVarToGameServer( pMessage->nServerId );

		// ����ͨ�������Ϣ
		//xuda theCenterWantedManager.SendWantedData( pMessage->nServerId );

		// ��������ί����Ϣ
		theCenterQuestEntrustManager.SendQuestEntrustData( pMessage->nServerId );

		// ��Ӫս������
		theCenterCampBattleDataManager.SendDataToServer( pMessage->nServerId );

		// ��������
        if ( theConsignmentManager.GetLoadSuccess() )
        {
            CS2GSLoadResourceSuccess xLoad;
            xLoad.uchLoadType = RunStatusDefine::LoadConsignmentSuccess;
            pGamePeer->Send( &xLoad );
        }

        // ���ߵ����̳�����
        S2SUpdateTradeShopConfig msg;
        msg.Clone( (uint8*)theTradeCenter.gszFileBuffer, theTradeCenter.gnFileBufferSize, false );
        pGamePeer->Send( &msg );

		if ( theConfig.bOpenAntiAddiction )
		{
			S2SNotiyAntiAddictionTimeInfo notifyMsg;
			notifyMsg.bOpenantiAddiction = theConfig.bOpenAntiAddiction;
			notifyMsg.antiAddictionTime  = theConfig.antiAddiction;
			notifyMsg.nAntiAddictionSaveTime = theConfig.nAntiAddictionSaveTime;
			pNetClient->Send( &notifyMsg );
		}

		//����GameServer GlobalDB������
		CS2GSLoadGlobalDBAck msgx;	
		msgx.info.SetData(theCenterGlobalDBManager.GetGlobalDB());
		pNetClient->Send( &msgx );
    }
    else
    {
        theCenterCountryManager.SendWeakCountryMessage();
		theCenterCountryManager.SendStrongCountryMessage();
    }
}
