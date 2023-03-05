#include "GamePlayer.h"
#include "Dxsdk/d3dx9math.h"
#include "BaseCharacter.h"
#include "ShareData.h"
#include "GameTime.h"
#include "GameWorld.h"
#include "LoginStage.h"
#include "MathLib.h"
#include "DBMessageDefine.h"
#include "MonsterBaseEx.h"
#include "ServerVarInterface.h"
#include "ScriptCompiler.h"
#include "ScriptVarMgr.h"
#include "ItemCharacter.h"
#include "ItemDetail.h"
#include "ExpStage.h"
#include "helper.h" 
#include "Configure.h"
#include "MissionList.h"
#include "DatabaseConnectors.h"
#include "TimeClock.h"
#include "WordParser.h"
#include "AvatarSystemSetting.h"
#include "QuestManager.h"
#include "WordParser.h"
#include "ProcessCharInfo.h"
#include "SystemConfig.h"
#include "NpcBaseEx.h"
#include "ErrorLog.h"
#include "FuncPerformanceLog.h"
#include "DropQuestItem.h"
#include "ShareData.h"
#include "DataChunkWriter.h"
#include "ServerVarInterface.h"
#include "GameWorldTimer.h"
#include "XmlStringLanguage.h"
#include "DuelHandler.h"
#include "TimeEx.h"
#include "AntiAddictionSystem.h"
#include "ResourcePath.h"
#include "DataCenter.h"
#include "DropItemManager.h"
#include "TeamManager.h"
#include "XmlStringLanguage.h"
#include "NpcInfo.h"

void GamePlayer::OnMsgS2SSwitchGate( const S2SSwitchGate* pMessage )
{   
    MsgSwitchGate GateInfo;
    GateInfo.header.stID = GetID();
    GateInfo.nResult     = pMessage->nResult;
    GateInfo.uGatePort   = pMessage->uGatePort;
    GateInfo.nServerType = pMessage->nTargetServerType;
    strncpy_s( GateInfo.szGateIP,       pMessage->szGateIP, sizeof(GateInfo.szGateIP)-1);
    strncpy_s( GateInfo.szChannelName,  pMessage->szChannelName, sizeof(GateInfo.szChannelName)-1);
    GettheServer().SendMsgToSingle( &GateInfo, this);
    if ( RESULT_SUCCESS( pMessage->nResult ))
    {
        Log( "从角色选择服务器跳转到地图服务器[%s:%s:%d]", GateInfo.szChannelName, GateInfo.szGateIP, GateInfo.uGatePort);
        OnExit( NULL, ET_SwitchGameServer );
    }
    else
    {
        Log( "游戏服务器还未启动完全r[%u][%s:%s:%d]", pMessage->nResult, GateInfo.szChannelName, GateInfo.szGateIP, GateInfo.uGatePort);
    }
}

void GamePlayer::OnMsgAckSwitchStage(const CS2GSSwitchStageAck* pMessage )
{  
    if ( RESULT_SUCCESS(pMessage->nResult) )
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_DEBUG, "CharacterServer 不应该到这里 OnMsgAckSwitchStage");
    }
    else
    {
        MsgAckResult msg;
        msg.header.stID = GetID();
        msg.result      = pMessage->nResult;
        switch ( pMessage->nResult )
        {
        case ER_LocusGameServerNotExit:
        case ER_GameServerNotExist:
        case ER_SystemException:
        case ER_CharacterServerCantBeGameServer:
            msg.result = pMessage->nResult;
            break;

        case ER_MapGameServerPlayerIsFull:
            msg.result = ER_EnterWorldQueue;
            msg.value = GetTheLoginStage().GetLoginQueuePos( GetID() ); // 排队修改
            break;
        }
        GettheServer().SendMsgToSingle( &msg, this);
    }   
}

void GamePlayer::OnEnterWorld( Msg* pMsg ) // 进入游戏世界
{       
    MsgEnterWorld* pEnterWorld = (MsgEnterWorld*)pMsg;
    if ( pEnterWorld == NULL)
    { return; }
    
    if ( 0 != GettheServer().GetShutdownTime())
    {
        MsgShutdownServer msgShutdown;
        __time64_t ltime;
        _time64(&ltime);
        msgShutdown.nowTime   = ltime;
        msgShutdown.delayTime = GettheServer().GetShutdownTimeDelay() - ( HQ_TimeGetTime() - GettheServer().GetShutdownTime() ) / ONE_SEC;
        GettheServer().SendMsgToSingle( &msgShutdown, this );
        return;
    }

    if ( g_Cfg.bAntiPluginOpen )
    { // 开启验证码
        if ( !_graphicCodeManager.IsHavePassCheck() )
        { // 还没有通过
            if ( _graphicCodeManager.IsNeedSendReqMsg() )
            {
                memcpy( &_msgEnterWorldCache, pEnterWorld, sizeof(MsgEnterWorld) );

//                 MsgReqNumberCode msg;
//                 bool bResult = _graphicCodeManager.MakeReqNumberCode(msg);
//                 if ( bResult )
//                 { GettheServer().SendMsgToSingle(&msg, this);}
				GraphicCodeCheckCommunication::SCheckReqMsg msg;
				msg.checkType = GraphicCodeCheckCommunication::ECT_NumberCode;
				msg.nIDNeedToCheck = GetAccountID();
				theGraphicCodeCheckCommunication.AddCheckReqMsg(msg);
            }
            return;
        }
    }

    if ( pEnterWorld->nSwitchStageType != SSRT_EnterGameWorld && pEnterWorld->nSwitchStageType != SSRT_EnterGameServerMap )
    { 
        Log("pEnterWorld->nSwitchStageType = %d Error!", pEnterWorld->nSwitchStageType);      
        return; 
    }
	
	//判断是否需要修改名称 修改名称的具体操作 我们直接调用数据库执行存储过程进行
	if(GetCharInfo().baseinfo.liveinfo.ChangeName !=0)
	{
		//发送命令道客户端
		MsgEnterWorldChangeNameReq msg;
		GettheServer().SendMsgToSingle(&msg, this);
        return;
	}
    
    // 发送两次消息时间间隔不得大于3秒钟
    if ( !GameTime::IsPassCurrentTime( m_dwLastEnterWorldReqTime, EnterWorldMessageIntervalTime ) )
    { 
        MsgAckResult msg;
        msg.header.stID = GetID();
        msg.result      = ER_EnterWorldInColdDown;
        GettheServer().SendMsgToSingle(&msg, this);
        return;
    }


    m_dwLastEnterWorldReqTime = HQ_TimeGetTime();

	//排队修改
	// 在Character中的位置
	if (GetTheLoginStage().IsOpenQueue())
	{
		int nQueuePos = GetTheLoginStage().GetLoginQueuePos( GetID() );
		if ( nQueuePos == -1 )
		{ // 不在队伍中
			nQueuePos = GetTheLoginStage().EnterQueue( GetID() );
		}

		if ( nQueuePos > 1/*0*/ )//放宽排队速度
		{
			// 前面有人不让进
			MsgAckResult msg; 
			msg.header.stID = GetID();
			msg.result      = ER_EnterWorldQueue;
			msg.value       = nQueuePos;
			GettheServer().SendMsgToSingle( &msg, this);
			return;
		}
	}
    // 检查CharacterID是否是此账号的。防止玩家伪造数据
    bool bCandEnterWorld = false;
    long nSlot = -1;
    /*for (int i = 0; i<More_iCharPerAccount; ++i)
    {
        if ( m_dbinfo.pdwCharacterID[i] == pEnterWorld->dwCharacterID )
        {
            bCandEnterWorld = true;
            nSlot = i;
            break;
        }
    }*/
	vector<uint32>::iterator Iter = m_dbinfo.pdwCharacterID.begin();
	int i = 0;
	for(;Iter != m_dbinfo.pdwCharacterID.end();++Iter)
	{
		if((*Iter) == pEnterWorld->dwCharacterID)
		{
            bCandEnterWorld = true;
            nSlot = m_dbinfo.pdwSlot[i];
            break;
        }
		++i;
	}

    if (!bCandEnterWorld)
    { 
        Log("使用非此账号的角色(AccountId%d: CharId%d)", pEnterWorld->dwAccountId, pEnterWorld->dwCharacterID );
        OnExit( NULL, ET_BeKick );
        return; 
    }

    // 去CenterServer拿数据
    GS2CSSwitchStageReq msg;
    msg.header.stID      = GetID();
    msg.nSwitchStageType = SSRT_EnterGameWorld;
    msg.nAccountId       = pEnterWorld->dwAccountId;
    msg.nCharacterDbId   = pEnterWorld->dwCharacterID;
    msg.stWhichSlot      = pEnterWorld->stWhichSlot;
   
    msg.fX               = 0.0f;
    msg.fY               = 0.0f;
    msg.fDir             = 0.0f;
    msg.dwTime           = pEnterWorld->dwEnterWorldTime;
    msg.nServerId        = g_Cfg.dwServerID;

	//msg.nMapId           = m_dbinfo.pdwCharacterMapId[nSlot];
    //msg.ustCountryID     = m_dbinfo.ustCountryID[nSlot];
	msg.nMapId           = m_dbinfo.pdwCharacterMapId[i];
	msg.ustCountryID     = m_dbinfo.ustCountryID[i];

    GettheServer().SendMsgToCenterServer( &msg );    
}

void GamePlayer::OnMsgAckGraphiccode(Msg* pMsg)
{
    if ( _graphicCodeManager.CheckAckGraphicCode((MsgAckGraphicCode*)pMsg) )
    { 
        OnEnterWorld( &_msgEnterWorldCache );
    }
    else
    {  
        if ( g_Cfg.nMaxCheckFailCount>0 && _graphicCodeManager.GetCheckFailCount() >= g_Cfg.nMaxCheckFailCount )
        {
            Log( "Exit By OnMsgAckGraphiccode EKT_GraphicCodeErrorKick" );
            ProcessBeBlock( MsgNotifyBeKick::EKT_GraphicCodeErrorKick, g_Cfg.graphicValidFailBlockTime );
            return;
        }

        if ( g_Cfg.bAntiPluginOpen && _graphicCodeManager.IsNeedSendReqMsg())
        {
//             MsgReqGraphicCode msg;
//             bool bResult = _graphicCodeManager.MakeReqGraphicCode(msg);
//             if ( bResult )
//             { GettheServer().SendMsgToSingle(&msg, this);}
			GraphicCodeCheckCommunication::SCheckReqMsg msg;
			msg.checkType = GraphicCodeCheckCommunication::ECT_GraphicCode;
			msg.nIDNeedToCheck = GetDBCharacterID();
			theGraphicCodeCheckCommunication.AddCheckReqMsg(msg);
        }
    }
}

void GamePlayer::OnMsgAckNumberCode( Msg* pMsg )
{
    if ( _graphicCodeManager.CheckAckNumberCode((MsgAckNumberCode*)pMsg) )
    {
        OnEnterWorld( &_msgEnterWorldCache );
    }
    else
    {  
        if ( g_Cfg.nMaxCheckFailCount>0 && _graphicCodeManager.GetCheckFailCount() >= g_Cfg.nMaxCheckFailCount )
        {
            Log( "Exit By OnMsgAckNumberCode EKT_GraphicCodeErrorKick" );
            ProcessBeBlock( MsgNotifyBeKick::EKT_GraphicCodeErrorKick, g_Cfg.graphicValidFailBlockTime );
            return;
        }

        if ( g_Cfg.bAntiPluginOpen && _graphicCodeManager.IsNeedSendReqMsg())
        {
//             MsgReqNumberCode msg;
//             bool bResult = _graphicCodeManager.MakeReqNumberCode(msg);
//             if ( bResult )
//             { GettheServer().SendMsgToSingle(&msg, this);}
			GraphicCodeCheckCommunication::SCheckReqMsg msg;
			msg.checkType = GraphicCodeCheckCommunication::ECT_NumberCode;
			msg.nIDNeedToCheck = GetAccountID();
			theGraphicCodeCheckCommunication.AddCheckReqMsg(msg);
        }
    }
}
