#include "stdafx.h"
#include "EctypeBot.h"
#include "GameBot.h"

#pragma warning(disable:4389)

#define MINUTE (60 * 1000)
#define REQFLYTIME ( MINUTE * 1)
#define SEND_PING_SPACE ( MINUTE * 2 )
//���ܼ������5��ʹ�log
#define RECV_PING_SPACE ( 5 * 1000 )
#define TargetEnctypeMapId ( 57 ) //̫ԭϷԺ
#define YueGuangBaoHeMapId (73)
#define TaiYuanItemId   (13340)
DWORD EctypeBot::EctypeMapTimeSpace = 10 * 60 * 100;

EctypeBot::EctypeBot():
CAttackBot(CAttackBot::EAT_NormalType),
ReadlyFlyToEctype(false),
ReqFlyEctypeTime(0),
ReqFlyMapId(-1),
OnEctypeTime(0),
SendPingTime(HQ_TimeGetTime())
{
    m_BotType = Bot_Ectype;
    Targetmap = rand()%2 == 0?TargetEnctypeMapId:YueGuangBaoHeMapId;
}

EctypeBot::~EctypeBot()
{

}

void EctypeBot::InitPlayGame(UINT MapId)
{
    BaseRobot::InitPlayGame(TargetEnctypeMapId);
}

void EctypeBot::ReqOpenEcTypeMap4XiYuan()
{
    char szMsg[dr_MaxChatString - 1] = {0};
    std::string command = ROBOT_REQUEST_COMMAND;
    command += "OpenTaiYuanXiYuan";
    MsgChat Chat(MsgChat::CHAT_TYPE_NORMAL);
    Chat.SetString(command.c_str());
    SendMsg(&Chat);
}

void EctypeBot::PlayGame()
{
    if (GetBotHP() <= 0)
    {
        return;
    }

//     if (HQ_TimeGetTime() - SendPingTime >= SEND_PING_SPACE)
//     {
//         MsgPingMsg ping;
//         ping.dwTime = HQ_TimeGetTime();
//         SendMsg(&ping);
//         SendPingTime = HQ_TimeGetTime();
//     }
#define TaiYuanXiYuan (57)
#define TaiYuan (10)

    //if (!ReadlyFlyToEctype)
    {
        if (HQ_TimeGetTime() - ReqFlyEctypeTime >=  (REQFLYTIME / 2))
        {
            if ( GetMapID() != TaiYuan &&  GetMapID() != TaiYuanXiYuan)
            {
                FlyToMap(TaiYuan, 99,245);
                ReqFlyEctypeTime = HQ_TimeGetTime();
                return;
            }
            if (GetMapID() != TaiYuanXiYuan )
            {
                ReqOpenEcTypeMap4XiYuan();
                if (GetBotLevel() < 38)
                {
                    ReqLvlUp(40);
                }
                FlyToMap(TaiYuanXiYuan,68,33);
                //if (IsHaveItem(TaiYuanItemId))//ItemNormalBag.IsHaveItemById(TaiYuanItemId) )
                //{
                    //UseItem(TaiYuanItemId,BT_NormalItemBag);
                    //FlyToMap(Targetmap, 67,23);
//                     PlayerInfo* NpcInfo = GetNPCByName("��ɽ");
//                     if ( NULL == NpcInfo )
//                     {
//                         if (GetMapID() != TaiYuan)
//                         {
//                             FlyToMap(TaiYuan, 99,245);
//                             //theNpcInfo.GetNpcByName("��ɽ",TaiYuan)
//                         }
//                     }
//                     else
//                     {
//                         if ( MoveToPoint(NpcInfo->m_vPos) )
//                         {
//                             // ����Npc
//                             MsgReqScript MsgScript;
//                             MsgScript.header.stID = GetBotShortId();
//                             MsgScript.stNpcId = NpcInfo->shPlayerID;//m_nNpcId;
//                             SendMsg(&MsgScript);
//                             m_bFlyMap = true;
//                         }
//                     }
                //}
//                 else
//                 {
//                     ReqItem(TaiYuanItemId);
//                 }

                ReqFlyEctypeTime = HQ_TimeGetTime();
                return;
            }

            if (GetMapID() == TaiYuanXiYuan)
            {
                Move();
                ReqFlyMapId = TaiYuanXiYuan;
            }
            else
            {
//                 CGameBotApp::EctypeMaps result = theApp.FlyEctypeMapTableByPlayerNum[ GetMapID() ];
//                 if (result.size() != 0)
//                 {
//                     if (result.size() == 1)
//                     {
//                         FlyToMap(result[0].EctyprMapID,result[0].EnterMapX,result[0].EnterMapY);
//                         ReqFlyEctypeTime = HQ_TimeGetTime();
//                         ReqFlyMapId = result[0].EctyprMapID;
//                         return;
//                     }
//                     else
//                     {
//                         DWORD RandNum = rand()%result.size();
//                         FlyToMap(result[RandNum].EctyprMapID,result[RandNum].EnterMapX,result[RandNum].EnterMapY);
//                         ReqFlyEctypeTime = HQ_TimeGetTime();
//                         ReqFlyMapId = result[0].EctyprMapID;
//                         return;
//                     }
//                 }
//                 else
//                 {
//                     LoadRandFlyMap();
//                     RandFly();
//                 }
            }
            ReqFlyEctypeTime = HQ_TimeGetTime();
        }
     }
//     else
//     {
//         if (ReadlyFlyToEctype && HQ_TimeGetTime() - OnEctypeTime >= 10 * MINUTE)
//         {
//             //LeaveEctypeMap();
//             return;
//         }        
//    }



    if ( HQ_TimeGetTime() - LastLockTargetTime > MINUTE && m_shTargetID == -1)
    {
//         m_shTargetID = LockTarget();	 //û��Ŀ�����ҹ���Ŀ��
//         LastLockTargetTime = HQ_TimeGetTime();
    }
    if (m_shTargetID != EATI_InitAttackTargetId)
    {
//         if (HQ_TimeGetTime() - m_dwLockTargetTime >= 3 * MINUTE )
//         {
//             //��������
//             MsgLockTarget msg;
//             msg.stWho = m_shTargetID;
//             SendMsg(&msg);
// 
//             //����漴Ҫ�ƶ�ȥ��Ŀ��
//             ClearMovePos();
// 
//             SetTipsInfo("����Ŀ��");
// 
//             m_dwLockTargetTime = HQ_TimeGetTime();
//         }
    }
    else
    {
        //if (m_bLoadMapOver && InEctypeMap(GetMapID()))
        {
            // 10��ûû��ˢ�¹������û�й���
            if (0 == m_WaitUpdateSightTime)
                m_WaitUpdateSightTime = HQ_TimeGetTime();

//             if (HQ_TimeGetTime() - m_WaitUpdateSightTime > 30*60*1000 && ReadlyFlyToEctype)
//             {
//                 LOG_MESSAGE(LogObject,LOG_PRIORITY_ERROR,"�����ˡ�%s���ڸ�����Ұ��Χ��û�й���",GetBotRoleName());
//                 SetBotState(State_End);
//                 SetTipsInfo("��Ұ��Χ��û�й���");
//                 m_WaitUpdateSightTime = HQ_TimeGetTime();
//             }
//             else
//                 Move();
        }
        //else
        {
//             if (m_shTargetID != -1)
//             {
//                 PlayerInfo* pInfo = GetLockPlayerInfo(m_shTargetID);
//                 if(pInfo == NULL)
//                 {
//                     m_shTargetID = -1; //�����Ѿ����� ������Ұ����
//                     m_dwLastUseSkillTime = 0;
// 
//                     SetTipsInfo("Ŀ�겻����");
// 
//                     return;
//                 }
// 
//                 //��ʼ����
//                 AttackEnemy();
//             }
        }
    }
    // CBot::PlayGame();
}

void EctypeBot::LeaveEctypeMap()
{
    LoadRandFlyMap();
    RandFly();
}

void EctypeBot::OnMsgChangeMap(Msg* pMsg)
{
    MsgChangeMap* pChangeMap = (MsgChangeMap*)pMsg;
    if (pChangeMap->dwMapId == ReqFlyMapId)
    {
        ReadlyFlyToEctype = true;
        OnEctypeTime = HQ_TimeGetTime();
    }
    else
    {
        ReadlyFlyToEctype = false;
    }
    BaseRobot::OnMsgChangeMap(pMsg);
}

void EctypeBot::OnMsg_Ping(Msg* pMsg)
{
    BaseRobot::OnMsg_Ping(pMsg);
}

bool EctypeBot::InEctypeMap(int CurMapid)
{
    if (CurMapid <= 0)
        return false;
    for (CGameBotApp::ItrEctypeMapContainer itr= theApp.FlyEctypeMapTableByPlayerNum.begin();itr!=theApp.FlyEctypeMapTableByPlayerNum.end();++itr)
    {
        for(CGameBotApp::EctypeMaps::iterator EctypeItr = itr->second.begin();EctypeItr!= itr->second.end();++EctypeItr)
        {
            if (CurMapid == EctypeItr->EctyprMapID)
            {
                return true;
            }
        }
    }
    return false;
}

void EctypeBot::SwitchMsg(Msg* pMsg)
{
    if (NULL == pMsg)
    {
        return;
    }
    switch(pMsg->GetType())
    {
        case MSG_ACK_SCRIPT:
            OnMsg_Ack_Script(pMsg);
            break;
    }
/*    CAttackBot::SwitchMsg(pMsg);*/
}

void EctypeBot::OnMsg_Ack_Script(Msg* pMsg)
{
    MsgAckScript* pAck = (MsgAckScript*)pMsg;
    if(pAck->byType == MsgAckScript::eAskQuestion)
    {
        switch(pAck->dlgType)
        {
            case MsgAckScript::eNDT_Description:
            {
                MsgReqScript MsgScript;
                MsgScript.stNpcId = pAck->stNpcId;
                MsgScript.chSelItem = 0;
                SendMsg(&MsgScript);
            }
            break;
        }
    }
}