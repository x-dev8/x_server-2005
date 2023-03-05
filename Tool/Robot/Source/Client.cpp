#include "stdafx.h"
#include "Bot.h"
#include "GameBot.h"
#include "MessageDefine.h"

#include "MsgBase.h"
#include "FuncPerformanceLog.h"
#include "Helper.h"
#include "ProcessCharInfo.h"
#include "PosChangePackage.h"
#include "AckEnterWorldPackage.h"
#include "EnterMySightPackage.h"
#include "application_config.h"
#include "Client.h"
#include "LoginInfo.h"
#include "GameDefineBot.h"

Client::Client()
{
    SetBotID(CLIENT_ID);
    /*SetPermanence(TRUE);*/
    m_BotType = Bot_Client;

    m_vecDelete.resize(CHARACTOR_COUNT);

    m_xToPos.x = 0;
    m_xToPos.y = 0;
    m_xToPos.z = 0;
	
	m_pLoginInfo=NULL;


    m_BotType = Bot_Client;
    dwPingTime = 0;
}

Client::Client(LoginInfo *pLoginInfo)
{
	m_pLoginInfo = pLoginInfo;

	SetBotID(CLIENT_ID);
	/*SetPermanence(TRUE);*/
	m_BotType = Bot_Client;

	m_vecDelete.resize(CHARACTOR_COUNT);

	m_xToPos.x = 0;
	m_xToPos.y = 0;
	m_xToPos.z = 0;


    m_BotType = Bot_Client;
    dwPingTime = 0;
}

Client::~Client()
{
	m_vecDelete.clear();
}
#define CONFIG_FILE_PATH

void Client::Update()
{
	__super::Update();
    if (IsConnectted())
    {
//         char sBuf[512];
//         ZeroMemory(sBuf,sizeof(sBuf));
//   //      GettheNetworkInput().RecvMsg(sBuf);
//         Msg *sMsgBuf = (Msg*)&sBuf;
//         if (sMsgBuf->header.stLength != 0)
//         {
//             SwitchMsg(sMsgBuf);
//         }

        if (HQ_TimeGetTime() - dwPingTime > PING_MSG_SPACE)
        {
            MsgPingMsg pingMsg;
            pingMsg.dwTime = HQ_TimeGetTime();
            SendMsg(&pingMsg);
            dwPingTime = HQ_TimeGetTime();
        }
    }
}
void Client::OnMsgPingMsg(Msg* PingMsg)
{
    MsgPingMsg* pPingMsg = (MsgPingMsg*)PingMsg;
    DWORD UseTime = HQ_TimeGetTime() - pPingMsg->dwTime;
    char buf[30];
    ZeroMemory(buf,sizeof(buf));
    ltoa(UseTime,buf,10);
    OutputDebugStringA(buf);
	BaseRobot::OnMsg_Ping(PingMsg);
}
// void Client::Update()
// {
// 	INetworkNode::Update();
// 
// 	if (!IsConnected())
// 	{		
// 		int nState = GetBotState();		
// 		if ( nState != State_SwitchGate && nState != State_WaitCloseToNewGateServer)
// 		{
// 			SetBotState(State_BeginLogin);
// 			SetConnectServerData();
// 		}
// 
// 		SetTipsInfo("断开连接");		
// 		m_pLoginInfo->m_listChar.DeleteAllItems();
// 		m_pLoginInfo->m_buttonSend.EnableWindow(TRUE);
// 
// 		return;
// 	}
// 
// 	DWORD dwTime = HQ_TimeGetTime();
// 
// 	if(dwTime - m_dwLastPingTime > 5000)
// 	{
// 		MsgPingMsg ping;
//         ping.dwTime = HQ_TimeGetTime();
// 		SendMsg(&ping);
// 		m_dwLastPingTime = dwTime;
// 	}
// 
// 	switch (GetBotState())
// 	{		
// 		
// 	case State_BeginLogin:
// 		//LoginServer();
// 		break;
// 
// 	case State_WaitCloseToNewGateServer:
// 		break;
// 
// 	case State_SwitchGate:
// 		{		
// 			MsgAllocGWID allgwid;
// 			SendMsg(&allgwid);
// 			SetBotState(State_GetChar);
// 			break;
// 		}
// 	case State_GetChar:
// 		{
// 			if(CheckTime(1000*100*100))
// 			{
// 				MsgGetCharacter getChar;
// 				strcpy(getChar.szAccount, m_szBotName);
// #ifdef	__NEW_LOGIN__
// 				strcpy(getChar.SessionKey, m_strSessionKey.c_str());
// #else
// 				getChar.SessionKey = m_dwSessionKey;
// #endif
// 				getChar.nAccountID = m_dwAccountId;
// 				//getChar.nIsSwitchGame = m_bSwitchGate;
// 				SendMsg(&getChar);
// 				SetBotState( State_WaitGetChar );
// 			}
// 			break;
// 		}
// 	case State_CreateChar:
// 		break;
// 	case State_EnterWorld:
// 		break;
// 	case State_Play:
// 		PlayGame();
// 		break;
// 	case State_Wait:
// 		break;
// 	}
// }

void Client::SwitchMsg(Msg* pMsg)
{
	if (pMsg == NULL)
	{
		return;
	}
	switch (pMsg->GetType())
	{
    case MSG_PING:
        OnMsgPingMsg(pMsg);
        break;
	/*case MSG_ACKLOGIN:
		OnMsg_AckLogin(pMsg);
		break;*/
	case MSG_ACKCHAR:
		OnMsg_AckChar(pMsg);
		break;
	case MSG_ENDACKCHAR:
		OnMsg_EndAckChar(pMsg);
		break;
	case MSG_ACKENTERWORLD:
		OnMsgAckEnterWorld(pMsg);
		break;
	case MSG_ACK_CREATECHECKNAME:
		OnMsg_AckCreateCheckName(pMsg);
		break;
	case MSG_ACKCREATECHAR:
		OnMsg_AckCreateChar(pMsg);
		break;

	default:
		BaseRobot::SwitchMsg(pMsg);
		break;
	}	
}


//void Client::OnMsg_AckLogin(Msg* pMsg)
//{
//    MsgAckLogin* pAck = (MsgAckLogin*)pMsg;
//    if( pAck->stErrorCode == MsgAckLogin::ret_succ )
//    {
//        _accountId = pAck->dwAccountID;
//
//        SetTipsInfo("登陆Login成功");	
//        if(m_pLoginInfo)m_pLoginInfo->m_buttonSend.EnableWindow(FALSE);		
//        return;
//    }
//
//    if(m_pLoginInfo)m_pLoginInfo->m_buttonSend.EnableWindow(FALSE);
//
//    SetTipsInfo("登陆Login失败");
//}

void Client::ReGetCharacterlist(){
	if(m_pLoginInfo)m_pLoginInfo->m_listChar.DeleteAllItems();
}

void Client::OnMsg_AckChar(Msg *pMsg)
{
	static char *s_pszProfession[] = {"戟", "剑", "枪", "舞", "刀", };
	static const int nCount = sizeof(s_pszProfession) / sizeof(char*);	

	MsgAckChar* pAck = (MsgAckChar*)pMsg;

	m_vectorCharInfo[pAck->stWhichSlot] = pAck->baseinfo;
	m_vCharacterID[pAck->stWhichSlot] = pAck->dwCharacterID;
	m_vecDelete[pAck->stWhichSlot] = pAck->bIsDel;

	if(m_pLoginInfo)m_pLoginInfo->m_listChar.InsertItem(pAck->stWhichSlot, pAck->baseinfo.aptotic.szCharacterName);
	if(m_pLoginInfo)theApp.SetListItemText(m_pLoginInfo->m_listChar, pAck->stWhichSlot, 1, "%d",pAck->baseinfo.liveinfo.ustLevel);
	int nIndex = pAck->baseinfo.aptotic.usProfession;
	if (nIndex > -1 && nIndex < nCount)
	{
		if(m_pLoginInfo)m_pLoginInfo->m_listChar.SetItemText(pAck->stWhichSlot, 2, s_pszProfession[nIndex]);
	}

	CString strBrithDay = "";
	strBrithDay.Format(_T("%s %d年%d月%d日"), pAck->baseinfo.aptotic.szYearName, pAck->baseinfo.aptotic.byYear, 
		pAck->baseinfo.aptotic.byMonth, pAck->baseinfo.aptotic.byDay);

	if(m_pLoginInfo)m_pLoginInfo->m_listChar.SetItemText(pAck->stWhichSlot, 3, strBrithDay.GetBuffer());
	
	SetTipsInfo("获取角色列表");   	
}

void Client::OnMsg_EndAckChar(Msg* pMsg)
{
	BaseRobot::OnMsg_EndAckChar(pMsg);


	if(m_pLoginInfo)m_pLoginInfo->m_buttonSend.EnableWindow(FALSE);
	if(m_pLoginInfo)m_pLoginInfo->m_buttonLoginOut.EnableWindow(TRUE);
	if(m_pLoginInfo){
		if (m_pLoginInfo->m_listChar.GetItemCount() == CHARACTOR_COUNT)
		{
			m_pLoginInfo->m_buttonCreate.EnableWindow(FALSE);
		}
		else
		{
			m_pLoginInfo->m_buttonCreate.EnableWindow(TRUE);
		}
	}
	
}

void Client::OnMsgAckEnterWorld(Msg* pMsg)
{	
	MsgAckEnterWorld* pAck = (MsgAckEnterWorld*)pMsg;
	m_CharInfo = pAck->charinfo;                           // 角色信息
	m_pSkillBag = m_CharInfo.otherdataclient.skills.skill; // 技能
	m_pItemBag = m_CharInfo.ItemBagData.stPackItems;       // 背包

	m_shPlayerId = pAck->header.stID;
	
	m_cMoveSerial = pAck->cMoveSerial;
	SetPos(pAck->charinfo.otherdataclient.pos.vPos.x, pAck->charinfo.otherdataclient.pos.vPos.y, 0);	

	m_fMoveSpeed = pAck->charinfo.baseinfo.baseProperty.fightAttr.moveSpeed.final;

	MsgMapLoaded msgMapLoaded;
	msgMapLoaded.header.stID = m_shPlayerId;
	SendMsg(&msgMapLoaded);

	// 进入了游戏世界了
	SetBotState(State_Play);
	SetTipsInfo("开始游戏");	

	////////////////////////////////////////////////////
	if(m_pLoginInfo){
		m_pLoginInfo->m_buttonEnter.EnableWindow(FALSE);
		m_pLoginInfo->m_buttonCreate.EnableWindow(FALSE);
		m_pLoginInfo->m_buttonDelete.EnableWindow(FALSE);

		m_pLoginInfo->m_buttonCheck.EnableWindow(FALSE);
		m_pLoginInfo->m_buttonReset.EnableWindow(FALSE);
		m_pLoginInfo->m_buttonCancle.EnableWindow(FALSE);
		m_pLoginInfo->m_buttonCreateOk.EnableWindow(FALSE);
	}
	
}

void Client::OnMsg_AckCreateCheckName(Msg *pMsg)
{
	MsgAckCreateCheckName* pAck = (MsgAckCreateCheckName*) pMsg;

	if (pAck->bResult)
	{
		AfxMessageBox(_T("恭喜,该角色名可以注册!"));
	}
	else
	{
		AfxMessageBox(_T("抱歉,该角色名已经被注册!"));
	}
}

void Client::OnMsg_AckCreateChar(Msg* pMsg)
{
	MsgAckCreateChar* pCreate = (MsgAckCreateChar*)pMsg;

	if (pCreate->bCreateSucc)
	{
		if(m_pLoginInfo)m_pLoginInfo->CreateCharSuccess();
	}	
}



void Client::PlayGame()
{
	Move();
}

void Client::Move()
{
	if (m_xToPos.x == 0 && m_xToPos.y == 0)
	{
		return;
	}

	DWORD dwCostMovingTime = HQ_TimeGetTime() - m_dwStartMovingTime;
	if(dwCostMovingTime >= m_nMoveStep)
	{
		m_dwStartMovingTime = HQ_TimeGetTime();

		m_vDir = m_xToPos - m_vPos;
		float fDist = D3DXVec3Length( &m_vDir );
		D3DXVec3Normalize( &m_vDir, &m_vDir );
		float fMoveDist = m_fMoveSpeed * m_nMoveStep / 1000;
		if(fMoveDist < fDist)
		{			
			m_vPos.x += fMoveDist * m_vDir.x;
			m_vPos.y += fMoveDist * m_vDir.y;

			MsgPlayerMovingPosAndDirToServer msg;
			msg.header.stID = m_shPlayerId;
			msg.vPos.x = m_vPos.x;
			msg.vPos.y = m_vPos.y;
			msg.vPos.z = 0;
			msg.chDirX = (char)(m_vDir.x*127);
			msg.chDirY = (char)(m_vDir.y*127);
			msg.chDirZ = 0;
			msg.dwSendTime = HQ_TimeGetTime();
			SendMsg( &msg );

		}
		else
		{
			m_xToPos.x = 0;
			m_xToPos.y = 0;
		}
	}
}

void Client::SetToPositon(int nPosX, int nPosY)
{
	m_xToPos.x = nPosX;
	m_xToPos.y = nPosY;
	m_xToPos.z = 0;
}