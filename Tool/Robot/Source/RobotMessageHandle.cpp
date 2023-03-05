#include "stdafx.h"
#include "Bot.h"
#include "PosChangePackage.h"
#include "AckEnterWorldPackage.h"
#include "EnterMySightPackage.h"
#include "GameBot.h"
#include "MeRTLibs.h"

void BaseRobot::ProcessMsgs()
{

	Msg* pMsg=GetConnector()->GetMsg();
	while( pMsg )
	{
		#ifdef HIDE_BOT_INFO
			   //////////////////////////////////////////////
			   StatMsgInfo(Msg_Recv, pMsg); //统计接受的消息
			   /////////////////////////////////////////////
		#else
			   ++m_nTotalMsgNum;
			   ++g_nTotalMsgNum;

			   ++m_RecvPackNum;
			   m_RecvPackSize += pMsg->GetLength();   
		#endif // HIDE_BOT_INFO
		SwitchMsg( pMsg );
		if (!GetConnector())
		{ break; }
		pMsg = GetConnector()->GetMsg();
	}
	//////////////////////////////////////////////////////
	#ifdef HIDE_BOT_INFO
	   //更新接受的统计信息
	   m_xMsgStatistician.UpdataMaxAndMinRecvInfo();
	   theApp.m_xTatolMsgStatistician.UpdataMaxAndMinRecvInfo();
	#endif // HIDE_BOT_INFO
}

void    BaseRobot::SwitchMsg( Msg* pMsg ){

	switch( pMsg->GetType() )
	{
	case MSG_USESKILLHINTMESSAGE:
		OnMsgUseSkillHintMessage(pMsg);
		break;
	case MSG_ACKLOGIN:
		OnMsg_AckLogin( pMsg );
		break;
	case MSG_SWITCHGATE:
		OnMsg_SwitchGate( pMsg );
		break;
	case MSG_ACKCHAR:
		OnMsg_AckChar( pMsg );
		break;
	case MSG_ENDACKCHAR:
		OnMsg_EndAckChar( pMsg );
		break;
	case MSG_ACKCREATECHAR:
		OnMsg_CreateChar( pMsg );
		break;
	case MSG_ACKENTERWORLD:
		OnMsgAckEnterWorld( pMsg );
		break;
	case MSG_ACKENTERWORLDPACK:
		{
			static CAckEnterWorldPackage unpacker;
			MsgAckEnterWorld* pAckEnterWorld = unpacker.UnPackageMsg(*static_cast<MsgAckEnterWorldPack*>(pMsg));
			OnMsgAckEnterWorld(pAckEnterWorld);
		}
		break;
	//case MSG_TELLC_REASKGATE:
	//	{
	//		//	try_comfirm_account();
	//		if(GetBotState()<State_Select){
	//			m_bNeedAckAgain = true;
	//			g_bSwitchGate = true;
	//			g_dwSwitchGateTime = HQ_TimeGetTime() + g_dwSwitchGatePeriod;
	//		}	
	//	}
	//	break;
	case MSG_VERIFYPOS:
		OnMsg_VerifyPos( pMsg );
		break;
	case MSG_LOGINWAIT:
		OnMsg_LoginWait( pMsg );
		break;
		//case MSG_INQUIREINVITEE:    //邀请组队
		//    OnMsg_InquireInvitee( pMsg );
		//    break;
	case MSG_CHAT:    //邀请组队
		OnMsg_Chat( pMsg );
		break;
	case MSG_CHARATTRCHANGE:
		OnMsg_AttrChanged( pMsg );
		break;
	case MSG_PLAYERMOVINGPOS:
		OnMsg_PlayerMovingPos(pMsg);
		break;
	case MSG_PLAYERMOVINGPOSANDDIR:
		OnMsg_PlayerMovingPosAndDir(pMsg);
		break;
	case MSG_UNPLAYERVERIFYPOS:
		OnMsg_UnPlayerVerifyPos( pMsg );
		break;
	case MSG_PLAYERVERIFYPOS:
		OnMsg_PlayerVerifyPos(pMsg);
		break;
	case MSG_UNPLAYERMOVINGTOPOS:
		OnMsg_UnPlayerMovingToPos( pMsg );
		break;
	case MSG_UNPLAYERCLOSINGTOLOCKTARGET:
		OnMsg_UnPlayerClosingToLockTarget( pMsg );
		break;
	case MSG_PLAYER_ENTERMYSIGHT:
	case MSG_PLAYER_ENTERMYSIGHTMOVINGASTEP:
		OnMsg_PlayerEnterSight( pMsg );
		break;
	case MSG_ENTERMYSIGHTPACK:
		OnMsg_PlayerEnterSightPack( pMsg );
		break;
	case MSG_NPC_ENTERMYSIGHT:
	case MSG_NPC_ENTERMYSIGHTMOVINGASTEP:
		OnMsg_UnPlayerEnterSight( pMsg );
		break;
	case MSG_EXITMYSIGHT:
		OnMsg_ExitSight( pMsg );
		break;
	case MSG_ACKCHARINFO:
		OnMsg_AckCharInfo( pMsg );
		break;
	case MSG_SEEATTACK3:
		OnMsgSeeAttack3( pMsg );
		break;
	case MSG_POSCHANGE:
		OnMsg_PosChange( pMsg );
		break;
	case MSG_SAWSOMEONEDEAD:
		OnMsg_SawSomeOnDead( pMsg );
		break;
	case MSG_GETITEM:
		OnMsg_GetItem( pMsg );
		break;
		//case MSG_QUERYBARGAINING:
		//    OnMsg_QueryBargaining( pMsg );
		//    break;
		//case MSG_ACKBARGAINING:
		//    OnMsg_AckBargaining( pMsg );
		//    break;
	case MSG_CHANGEMAP:
		OnMsgChangeMap( pMsg );
		break; 
	case MSG_ACKEQUIP:    //装备物品
		OnMsgChangeEquip(pMsg);    
		break;
	case MSG_ACKDROPITEM:    //丢弃物品
		OnMsgDropItem(pMsg);
		break;
	case MSG_CHARLEVELUP:  //角色升级
		OnMsgLevelUp(pMsg);
		break;
	case MSG_TELLMAP_NPCQUEST:
		OnMsg_TellMap_NpcQuest(pMsg);
		break;
	case MSG_ALLNPCONTHEMAP:
		OnMsg_AllNpcInTheMap(pMsg); //服务器回应的NPC 动态ID
		break;
	case MSG_INQUIREINVITEE:
		OnMsgInviteeTeam(pMsg);
		break;
	case MSG_OUT_OF_LONGIN_TIME:
		OnMsgConnectGateOverTime(pMsg);
		break;
	case MSG_EXIT:
		OnMsgExit(pMsg);
		break;
	case MSG_ACK_RESULT:
		OnMsgAckResult(pMsg);
		break;
	case MSG_MAPINFOREADY:
		//      OnMsgMapInfoReady(pMsg);
		break;
	case MSG_PACKAGEVIEWACK:
		OnMsgPackageViewAck(pMsg);
		break;
	case MSG_ITEMENTERMYSIGHT:
		OnMsgItemEnterMySight(pMsg);
		break;
	case MSG_PACKAGEITEMACCESSACK:
		OnMsgPackageitemAccessAck(pMsg);
	case MSG_PICKPACKAGEITEMACK:
		OnMsgPickPackageItemAck(pMsg);
		break;
	case MSG_PING:
		OnMsg_Ping(pMsg);
		break;
	case MSG_CANCONTROLMOVING:
		OnMsgCanControlMoving(pMsg);
		break;
	case MSG_HITCHMOVETARGETPOS:
		OnMsgHitchMoveTargetPos(pMsg);
		break;
	case MSG_MONEYCHANGE:
		OnMsgMoneyChange(pMsg);
	case MSG_MOVEGOODS:
		OnMsgMoveGoods(pMsg);
		break;
	case MSG_ADDUPDATEPET:
		OnMsgGetPet(pMsg);
		break;
		//case MSG_ACK_FRIENDLIST:
		//    OnMsgAckFriendList(pMsg);
		//    break;
		//case MSG_ACK_DELFRIEND:
		//    OnMsgAckDelFriend(pMsg);
		//    break;
		//case MSG_INVITEADDRELATIONREQ:
		//    OnMsgInviteAddRelationReq(pMsg);
		//    break;
		//case MSG_ACK_ADDFRIEND:
		//    OnMsgAckAddFriend( pMsg);
		//    break;
	default:
		break;
	}


}

void BaseRobot::OnMsg_CreateChar( Msg* pMsg )
{
    MsgAckCreateChar* pCreate = (MsgAckCreateChar*)pMsg;
}

void BaseRobot::OnMsg_AckChar( Msg* pMsg )
{    	
	MsgAckChar* pAck = (MsgAckChar*)pMsg;
//    if(!pAck->bIsDel)
//    { _charDbId = pAck->dwCharacterID; }
    
    m_vectorCharInfo[pAck->stWhichSlot] = pAck->baseinfo;
    m_vCharacterID[pAck->stWhichSlot]   = pAck->dwCharacterID;

    SetTipsInfo("获得角色");
    if ( GetLastBotState() == State_CreateChar )
    { 
        EnterWorld(0);
        SetTipsInfo("选人进入游戏");
    }
	SetBotState(State_Select);
}

void BaseRobot::OnMsg_EndAckChar( Msg* pMsg )
{
	SetBotState(State_Select);
	
	g_bEndGetCharacter=true;
	
	MsgEndAckChar* pMsg_EndAckChar = (MsgEndAckChar*)pMsg;

	int count=0;
	for(int i=0;i<4;i++){
		if(m_vCharacterID[i] != 0 )count++;
	}
	CString s;
	s.Format("己成功获得角色列表,共%d个角色", count);
    SetTipsInfo(s);
    if( m_vCharacterID[0] == 0 )
    {
        SetBotState( State_CreateChar );
    }
    else
    {
		if(isReadyEnterGame){
			MsgEnterWorld msg;
			msg.nSwitchStageType = SSRT_EnterGameServerMap;
			msg.stWhichSlot      = sPlayerSlot;
			msg.dwCharacterID    = m_vCharacterID[sPlayerSlot];
			msg.dwEnterWorldTime = HQ_TimeGetTime();
			msg.dwAccountId      = _accountId;
			SendMsg( &msg );
			isReadyEnterGame = false;

// 				dw_FirstEnterWorldTime = HQ_TimeGetTime();
// 				dw_LoginSelectRoleTime = HQ_TimeGetTime() - dw_FirstLoginSelectRoleTime;
			SetTipsInfo("进游戏");
		}
		else{
			EnterWorld(0);
		}
		
		
    }
}

void BaseRobot::OnMsg_SwitchGate( Msg* pMsg )
{
    MsgSwitchGate* pSwitchGate = (MsgSwitchGate*)pMsg;
  //  SetLoginErrorCode( pSwitchGate->nResult );
    if(RESULT_SUCCESS(pSwitchGate->nResult) &&  strlen(pSwitchGate->szGateIP) != 0 && pSwitchGate->uGatePort != 0)
    {
        _targetGateIp      = pSwitchGate->szGateIP;
        _targetGatePort    = pSwitchGate->uGatePort;        
        _targetChannelName = pSwitchGate->szChannelName;
		g_bSwitchGate = true;
		g_dwSwitchGateTime = HQ_TimeGetTime() + g_dwSwitchGatePeriod;
		if (pSwitchGate->nServerType == ST_CharacterServer){
			SetTipsInfo("帐号己验证，连接角色服务器");
		}
		else 
		{
			SetTipsInfo("切服，连接游戏服务器");
		}    
    }
    else
    {
        SetTipsInfo("无Gate可连接");    
        SetBotState(e_state_confirm_fail); //设置重连 或者已经在服务器上了
    }
}

void BaseRobot::OnMsgAckEnterWorld( Msg* pMsg )
{
    MsgAckEnterWorld* pAck = (MsgAckEnterWorld*)pMsg;

    if( pAck->nResult != ER_Success)
    { 
        SetTipsInfo("AckEnterWorld Fail");  
        return; 
    }

    m_CharInfo     = pAck->charinfo;                          // 角色信息
    m_pSkillBag    = m_CharInfo.otherdataclient.skills.skill; // 技能
    m_pItemBag     = m_CharInfo.ItemBagData.stPackItems;      // 背包
    m_pMaterialBag = m_CharInfo.ItemBagData.ciMaterialItems;
    m_pTaskItemBag = m_CharInfo.ItemBagData.ciTaskItems;

    ItemNormalBag.CreateFromData(m_CharInfo.ItemBagData.stPackItems,ITEM_BAGMAX);
    m_BromeItems = m_CharInfo.ItemBagData.miItems;
	m_PetItems   = m_CharInfo.ItemBagData.petItems;

 
    m_shPlayerId = pAck->header.stID;                      // 角色在服务器上的动态ID
    m_cMoveSerial = pAck->cMoveSerial;
    SetPos( pAck->charinfo.otherdataclient.pos.vPos.x, pAck->charinfo.otherdataclient.pos.vPos.y, 0 );
    m_fMoveSpeed = pAck->charinfo.baseinfo.baseProperty.fightAttr.moveSpeed.final;

	// 获得宠物数据
	if (NULL != m_PetItems)
	{
		for (int i= 0 ; i < ITEM_PET_MAXCOUNT ; ++i)
		{
			if (m_PetItems[i].baseInfo.petId == 0)
			{
				break;
			}
			SPetItem* pSMountItem = FindPetByGuid(m_PetItems[i].baseInfo.guid);
			if (NULL == pSMountItem)
				SPets.push_back(m_PetItems[i]);
			else
				*pSMountItem = m_PetItems[i];
		}
	}

    MsgMapLoaded msgMapLoaded;
    msgMapLoaded.header.stID = m_shPlayerId;
    SendMsg( &msgMapLoaded );
    
	SetBotState(State_Play);
	SetTipsInfo("进入游戏世界");
}

void BaseRobot::OnMsgChangeMap( Msg* pMessage )
{       
    MsgChangeMap* change = (MsgChangeMap*)pMessage;
    m_shPlayerId = change->header.stID;
    SetMapID ( change->dwMapId );
    SetPos(change->fX, change->fY, 0.f);

    MsgMapLoaded msgMapLoaded;
    msgMapLoaded.header.stID = m_shPlayerId;
    SendMsg( &msgMapLoaded );

    //换地图了 清空
    m_listMonsterList.clear();
    m_listNPCList.clear();
    m_listPlayerList.clear();
    KillMeTarget.clear();
    m_bLoadMapOver = false;

	SetBotState(State_Play);
    SetTipsInfo("进入场景");
}
