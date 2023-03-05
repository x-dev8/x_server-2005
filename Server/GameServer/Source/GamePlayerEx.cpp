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
#include "GlobalDef.h"
#include "GameWorldTimer.h"
#include "XmlStringLanguage.h"
#include "DuelHandler.h"
#include "TimeEx.h"
#include "AntiAddictionSystem.h"
#include "chatcheck.h"
#include "md5.h"
#include "ResourcePath.h"
#include "DataCenter.h"
#include "DropItemManager.h"
#include "TeamManager.h"
#include "XmlStringLanguage.h"
#include "NpcInfo.h"

void GamePlayer::OnMsgS2SSwitchGate( const S2SSwitchGate* pMessage )
{   
    // 这个进入保存数据流程
    if ( _bWantSwitchGameWaitSaveInfoOk )
    {
       // Log( "此用户已经在做服务器跳转的装备工作了");
		Log( theXmlString.GetString(eServerLog_HeroDoneTiaozhuan));
        return;
    }

    if ( GetStatus() > CS_DBLOGINED )
    { // 在游戏中准备跳转
        _bWantSwitchGameWaitSaveInfoOk = true;
        _GateInfo.header.stID = GetID();
        _GateInfo.nResult     = pMessage->nResult;
        _GateInfo.uGatePort   = pMessage->uGatePort;
        _GateInfo.nServerType = pMessage->nTargetServerType;
        strncpy_s( _GateInfo.szGateIP,  pMessage->szGateIP, sizeof(_GateInfo.szGateIP)-1);
        strncpy_s( _GateInfo.szChannelName, pMessage->szChannelName, sizeof(_GateInfo.szChannelName)-1);

        unsigned char saveType = EST_None;
        if ( GetStatus() == CS_WAITRETURNTOCHARACTER )
        {   
           // Log( "开始准备回到角色服务器[[%s:%s:%d]]，将角色数据入库到中转中心", _GateInfo.szChannelName, _GateInfo.szGateIP, _GateInfo.uGatePort);
			Log( theXmlString.GetString(eServerLog_HeroToCharServer), _GateInfo.szChannelName, _GateInfo.szGateIP, _GateInfo.uGatePort);
            saveType = EST_ExitWorld;
        }
        else
        {   
            //Log( "开始准备去游戏服务器[[%s:%s:%d]]，将角色数据入库到中转中心", _GateInfo.szChannelName, _GateInfo.szGateIP, _GateInfo.uGatePort);
			 Log( theXmlString.GetString(eServerLog_HeroToGameServer), _GateInfo.szChannelName, _GateInfo.szGateIP, _GateInfo.uGatePort);
            saveType = EST_ExitGameServer;
        }

        //TODO: 为什么我修改了这里的代码就会发生 _OnGS2CSSwitchStageReq 客户端作弊修改了协议 , WHY ?
        //貌似是由于编译链接引起的, 谁修改了这里的代码请 Rebuild 整个解决方案
        gTransferRuntimeInfo.xPetInfo[EPT_Protect].nPetID = 0;
        if ( m_ProtectCharID > InvalidGameObjectId )
        {
            MonsterBaseEx* pAiChar = (MonsterBaseEx*) theRunTimeData.GetCharacterByID(m_ProtectCharID);
            if ( pAiChar && !pAiChar->IsPet() )
            { SetRunTimePetInfo( gTransferRuntimeInfo.xPetInfo[EPT_Protect], pAiChar ); }
        }

        gTransferRuntimeInfo.xPetInfo[EPT_Skill].nPetID = 0;
        if ( HaveSummonPet() )
        {
            for (int i=0;i<CharSummonPetMaxCount; ++i)
            {
                MonsterBaseEx* pAiChar = (MonsterBaseEx*) theRunTimeData.GetCharacterByID( m_xSummonPets[i].petId );
                if ( pAiChar != NULL && pAiChar->IsPet() && !pAiChar->IsIllusionChar() && pAiChar->GetMonsterType() == eMT_Pet )
                { SetRunTimePetInfo( gTransferRuntimeInfo.xPetInfo[EPT_Skill], pAiChar, m_xSummonPets[i].skillId ); }
            }
        }

        gTransferRuntimeInfo.xPetInfo[EPT_Capture].nPetID = 0;
        if ( HaveCapturePet() )
        {
            MonsterBaseEx* pAiChar = (MonsterBaseEx*) theRunTimeData.GetCharacterByID( GetCapturePetId() );
            if ( pAiChar != NULL && pAiChar->IsPet() )
            { SetRunTimePetInfo( gTransferRuntimeInfo.xPetInfo[EPT_Capture], pAiChar ); }
        }

        gTransferRuntimeInfo.xPetInfo[EPT_Nurture].nPetID = 0;
        if ( _petManager.HaveActivePet() )
        {
            MonsterBaseEx* pAiChar = (MonsterBaseEx*) theRunTimeData.GetCharacterByID( _petManager.GetActivePetCharId() );
            if ( pAiChar != NULL && pAiChar->IsPet() )
            { SetRunTimePetInfo( gTransferRuntimeInfo.xPetInfo[EPT_Nurture], pAiChar, -1, _petManager.GetActivePetIndex() ); }
        }

        SetLastMapID( GetMapID() );         // 设置要退出的场景Id
        
        ProcessDeathExitRelive();           // 处理死亡复活

		CorrectMapID();				        // 纠正地图

        GettheFileDB().SaveCharAllData( this, saveType, pMessage );
    }
    else
    { // 没进入游戏，直接发
        MsgSwitchGate GateInfo;
        GateInfo.header.stID = GetID();
        GateInfo.nResult     = pMessage->nResult;
        GateInfo.uGatePort   = pMessage->uGatePort;
        GateInfo.nServerType = pMessage->nTargetServerType;
        strncpy_s( GateInfo.szGateIP,       pMessage->szGateIP, sizeof(GateInfo.szGateIP)-1);
        strncpy_s( GateInfo.szChannelName,  pMessage->szChannelName, sizeof(GateInfo.szChannelName)-1);
        GettheServer().SendMsgToSingle( &GateInfo, this);
       // Log( "从负载最低服务器跳转到 GateInfo[%s:%s:%d]", GateInfo.szChannelName, GateInfo.szGateIP, GateInfo.uGatePort);
		  Log( theXmlString.GetString(eServerLog_HeroToOther), GateInfo.szChannelName, GateInfo.szGateIP, GateInfo.uGatePort);
        OnExit( NULL, ET_SwitchGameServer );
    }
}

void GamePlayer::OnMsgAckSwitchStage(const CS2GSSwitchStageAck* pMessage )
{  
    if ( RESULT_SUCCESS(pMessage->nResult) )
    {
        if ( pMessage->ucIsLocalFlyMap == BV_LocalFlyMap )
        {
            FlyToMapReq( pMessage->nMapId, pMessage->fX, pMessage->fY, pMessage->fDir );
        }
        else
        {
            m_dwEnterWorldServerTime = HQ_TimeGetTime();
            m_dwEnterWorldClientTime = pMessage->dwTime;

            // 如果玩家还在内存中就退出保存
            GamePlayer* pPlayer = theRunTimeData.GetGamePlayerByDBID( pMessage->nCharDBId );
            if ( pPlayer != NULL )
            {
                LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_WARNING, "OnMsgAckSwitchStage 被T下线 CharDbId[%u][-]", pMessage->nCharDBId/*, GetSessionKey() */);
                //Log( "OnMsgAckSwitchStage 被T下线" );
				Log(theXmlString.GetString(eServerLog_HeroBeT));
                pPlayer->OnExit( NULL, ET_BeKick );
            }

            DBMsgEnterWorld  msgEnterWorld;
            msgEnterWorld.dwCharacterID            = pMessage->nCharDBId;
            msgEnterWorld.header.stID              = GetID();
            msgEnterWorld.dwAccountID              = pMessage->nAccountId; // 安全性 以后要改，安全问题
            msgEnterWorld.stSlot                   = pMessage->stWhichSlot;
            msgEnterWorld.nMapId                   = pMessage->nMapId;
            msgEnterWorld.nTileX                   = FloatToTile(pMessage->fX);
            msgEnterWorld.nTileY                   = FloatToTile(pMessage->fY);
            msgEnterWorld.fDir                     = pMessage->fDir;
            msgEnterWorld.ucNeedTellClientCharInfo = pMessage->ucNeedTellClientCharInfo;
            msgEnterWorld.ucNeedUseMessageMapInfo  = pMessage->ucNeedUseMessageMapInfo;  
            msgEnterWorld.dwTeamSessionID          = pMessage->dwTeamSessionId;
            strncpy_s( msgEnterWorld.szIP, sizeof( msgEnterWorld.szIP ), _strIp.c_str(), sizeof( msgEnterWorld.szIP ) - 1 );
            GettheDBCon().SendMsg( &msgEnterWorld,GetLifeCode() );

            SetAccountID(pMessage->nAccountId);

            //DBMsgAccountState state;
            //state.dwAccountID = m_dbinfo.dwAccountID;
            //state.shState = DBMsgAccountState::state_play;
            //GettheDBCon().SendMsg( &state,GetLifeCode() );
            m_PreSaveTime = HQ_TimeGetTime();
        }
    }
    else
    {
        switch ( GetStatus()  )
        {
        case CS_WAITRETURNTOCHARACTER:
            SetStatus( CS_IDLE );
            break;
        }

        MsgAckResult msg;
        msg.header.stID = GetID();
        msg.result      = pMessage->nResult;
        GettheServer().SendMsgToSingle( &msg, this);
    }   
}

void GamePlayer::OnEnterWorld( Msg* pMsg ) // 进入游戏世界
{       
    MsgEnterWorld* pEnterWorld = (MsgEnterWorld*)pMsg;
    if ( pEnterWorld == NULL)
    { return; }
    
    if ( pEnterWorld->nSwitchStageType != SSRT_EnterGameWorld && pEnterWorld->nSwitchStageType != SSRT_EnterGameServerMap )
    { 
        Log("pEnterWorld->nSwitchStageType = %d Error!", pEnterWorld->nSwitchStageType);      
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

    // 检查CharacterID是否是此账号的。防止玩家伪造数据
    bool bCandEnterWorld = false;
    long nSlot = -1;
   /* for (int i = 0; i<More_iCharPerAccount; ++i)
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
       // Log("使用非此账号的角色");
		Log(theXmlString.GetString(eServerLog_UseHeroNoThisAccount));
        return; 
    }

    GamePlayer* pPlayer = theRunTimeData.GetGamePlayerByDBID( pEnterWorld->dwCharacterID );
    if ( pPlayer != NULL )
    { 
		
		if ( pPlayer->GetStallOpenOffline() )
		{
			MsgAckResult  AkMsg ;
			AkMsg.header.stID = GetID();
			AkMsg.result      = ER_EnterWorldWhithOffineStall;
			GettheServer().SendMsgToSingle(&AkMsg,this);
		}
		
		//如果游戏中已经存在此角色，则踢掉玩家下线
        LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_WARNING, "OnEnterWorld 被T下线 CharDbId[%u][-]", pEnterWorld->dwCharacterID/*, GetSessionKey()*/ );
        //pPlayer->Log( "OnEnterWorld 被T下线" );
		pPlayer->Log(theXmlString.GetString(eServerLog_EnterWorldBeT));
        pPlayer->OnExit( NULL, ET_BeKick ); //给游戏中的玩家发这个消息 
    }

    // 去CenterServer拿数据
    GS2CSSwitchStageReq msg;
    msg.header.stID      = GetID();
    msg.nSwitchStageType = SSRT_EnterGameServerMap;
    msg.nAccountId       = pEnterWorld->dwAccountId;
    msg.nCharacterDbId   = pEnterWorld->dwCharacterID;
    msg.stWhichSlot      = pEnterWorld->stWhichSlot;
    msg.fX               = 0.0f;
    msg.fY               = 0.0f;
    msg.fDir             = 0.0f;
    msg.dwTime           = pEnterWorld->dwEnterWorldTime;
    msg.nServerId        = g_Cfg.dwServerID;
	//获取数据
	msg.nMapId           = m_dbinfo.pdwCharacterMapId[i];
	msg.ustCountryID     = m_dbinfo.ustCountryID[i];

    GettheServer().SendMsgToCenterServer( &msg );
    m_dwLastEnterWorldReqTime = HQ_TimeGetTime();
}

void GamePlayer::OnMsgAckGraphiccode(Msg* pMsg)
{
    if ( _graphicCodeManager.CheckAckGraphicCode((MsgAckGraphicCode*)pMsg))
    {
        ShowInfo(false, 276, theXmlString.GetString(eClient_AddInfo_2slk_50)); 
        if ( !IsDead() )        // 死了不加血~~
        {
            SetHP( GetCharFightAttr()->hpMax.final );
            SetMP( GetCharFightAttr()->mpMax.final );
            MsgCharAttrChanged changeMsg;
            changeMsg.iChangeCount = 0;
            changeMsg.AddAttrIntChange(CharAttr_HP, GetHP() );
            changeMsg.AddAttrIntChange(CharAttr_MP, GetMP() );
            changeMsg.header.stID = GetID();
            changeMsg.CaluLength();
            GettheServer().SendMsgToView( &changeMsg, GetID(), false );
        }
    }
    else
    {
        ShowInfo(false,  276, theXmlString.GetString(eClient_AddInfo_2slk_51));        
        if ( g_Cfg.nMaxCheckFailCount>0 && _graphicCodeManager.GetCheckFailCount() >= g_Cfg.nMaxCheckFailCount )
        {
            Log( "Exit By OnMsgAckGraphiccode EKT_GraphicCodeErrorKick" );
            ProcessBeBlock( MsgNotifyBeKick::EKT_GraphicCodeErrorKick, g_Cfg.graphicValidFailBlockTime );
        }
    }
}

void GamePlayer::OnMsgAckNumberCode( Msg* pMsg )
{
    if ( _graphicCodeManager.CheckAckNumberCode((MsgAckNumberCode*)pMsg))
    {
        ShowInfo(false, 276, theXmlString.GetString(eClient_AddInfo_2slk_50));        
        SetHP( GetCharFightAttr()->hpMax.final );
        SetMP( GetCharFightAttr()->mpMax.final );
        MsgCharAttrChanged changeMsg;
        changeMsg.iChangeCount = 0;
        changeMsg.AddAttrIntChange(CharAttr_HP, GetHP() );
        changeMsg.AddAttrIntChange(CharAttr_MP, GetMP() );
        changeMsg.header.stID = GetID();
        changeMsg.CaluLength();
        GettheServer().SendMsgToView( &changeMsg, GetID(), false );
    }
    else
    {
        ShowInfo(false, 276, theXmlString.GetString(eClient_AddInfo_2slk_51));        
        if ( g_Cfg.nMaxCheckFailCount>0 && _graphicCodeManager.GetCheckFailCount() >= g_Cfg.nMaxCheckFailCount )
        {
            Log( "Exit By OnMsgAckNumberCode EKT_GraphicCodeErrorKick" );
            ProcessBeBlock( MsgNotifyBeKick::EKT_GraphicCodeErrorKick, g_Cfg.graphicValidFailBlockTime );
        }
    }
}
