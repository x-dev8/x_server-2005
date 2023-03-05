/********************************************************************
    Filename:    GuiLogicMessage.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __ROBOT_GUILOGCIMESSAGE_H__
#define __ROBOT_GUILOGCIMESSAGE_H__

#include "MeRTLibsServer.h"
#include "GameDefineBot.h"
#include "MsgStatistician.h"

#pragma pack( push, 1 )

struct SBaseGuiLogicMessage
{
    uint16 id;
    uint16 size;
};

enum EGuiLogicMessageType
{
    // GuiThread To LogicThread
    EGuiLogicMessageType_AddRobot        = 1000,
    EGuiLogicMessageType_ShowRobot       = 1001,
    EGuiLogicMessageType_PauseAddBot     = 1002, // ��ͣ/���� ��ӻ�����
    EGuiLogicMessageType_PlaySkill       = 1003, // �ͷ�/��ͣ�ͷ� ����
    EGuiLogicMessageType_Moving          = 1004, // for �������ƶ�
    EGuiLogicMessageType_PlayAttack      = 1005, // For �����˿�ʼ����
    EGuiLogicMessageType_BotRide         = 1006, // ����������
    EGuiLogicMessageType_ReloadLuaScript = 1007, // ���¼���lua�ű�
	EGuiLogicMessageType_PrepareSuit     = 1008, // ׼����װ

    // LogicThread to GuiThread
    EGuiLogicMessageType_RobotInfoChange = 2000,
    EGuiLogicMessageType_ShowRobotInfo   = 2001, // Logic To Ui ��ʾ�����˵���Ϣ
    EGuiLogicMessageType_ShowAllRobotInfo = 2002, // ��ʾ��������������ͼ�ֲ������꣬������Ϣ
    EGuiLogicMessageType_InitReady       = 2003, // Logic 2 Ui ȷ���Ƿ��ʼ�����
};

//////////////////////////////////////////////////////////////////////////
// Ui 2 Logic Message
struct GMsgAddRobot : public SBaseGuiLogicMessage
{
    GMsgAddRobot()
    {
        id = EGuiLogicMessageType_AddRobot;
        size = sizeof(GMsgAddRobot);
    }

    SAddInfo m_xAddInfo;
    //int nBotSpace;
};

struct GMsgShowRobot : public SBaseGuiLogicMessage
{
    GMsgShowRobot()
    {
        id   = EGuiLogicMessageType_ShowRobot;
        size = sizeof(GMsgShowRobot);
    }
    int robotId;
};
// ���þ�������˼��
//struct GMsgSetBetweenSpace : public SBaseGuiLogicMessage
//{
//    GMsgSetBetweenSpace()
//    {
//        id = EGuiLogicMessageType_SetBetweenSpace;
//        size = sizeof(GMsgSetBetweenSpace);
//    }
//    int nSpace;
//};
// ��ͣ/���� ��ӻ�����
struct GMsgPauseBot : public SBaseGuiLogicMessage
{
    GMsgPauseBot()
    {
        id = EGuiLogicMessageType_PauseAddBot;
        size = sizeof(GMsgPauseBot);
    }
    bool bIsPause;
};
// �ͷż���
struct GMsgPlaySkill : public SBaseGuiLogicMessage
{
    GMsgPlaySkill()
    {
        id = EGuiLogicMessageType_PlaySkill;
        size = sizeof(GMsgPlaySkill);
    }
    int nSkillID;
    bool bIsPlaySkill;
};
// �������ƶ�
struct GMsgBotMoving : public SBaseGuiLogicMessage 
{
    GMsgBotMoving()
    {
        id = EGuiLogicMessageType_Moving;
        size = sizeof(GMsgBotMoving);
    }
    bool bIsMove; // �Ƿ��ƶ�
    int nMoveRange; // �ƶ�����
};
// �����˹���
struct GMsgBotPlayAttack : public SBaseGuiLogicMessage
{
    GMsgBotPlayAttack()
    {
        id = EGuiLogicMessageType_PlayAttack;
        size = sizeof(GMsgBotPlayAttack);
    }
    bool bIsPlayAttack;
};
// ����
struct GMsgBotRide : public SBaseGuiLogicMessage
{
    GMsgBotRide()
    {
        id = EGuiLogicMessageType_BotRide;
        size = sizeof(GMsgBotRide);
    }
    bool bIsRide;
};
// ���¼���Lua�ű��ļ�
struct GMsgReLoadLuaScript : public SBaseGuiLogicMessage
{
    GMsgReLoadLuaScript()
    {
        id = EGuiLogicMessageType_ReloadLuaScript;
        size = sizeof(GMsgReLoadLuaScript);
    }
    bool bIsReloadLuaScript; //�Ƿ����¼���Lua�ű�
};
// ׼����װ
struct GMsgPrepareSuit : public SBaseGuiLogicMessage 
{
	GMsgPrepareSuit()
	{
		id = EGuiLogicMessageType_PrepareSuit;
		size = sizeof( GMsgPrepareSuit );
	}
};
//////////////////////////////////////////////////////////////////////////
// �߼��̵߳�UI�߳�
struct LMsgRobotInfoChange : public SBaseGuiLogicMessage
{
    LMsgRobotInfoChange()
    {
        id = EGuiLogicMessageType_RobotInfoChange;
        size = sizeof(LMsgRobotInfoChange);
    }

    SShowRobotInfo info;
};

struct LMsgShowRobotInfo : public SBaseGuiLogicMessage
{
    LMsgShowRobotInfo()
    {
        id = EGuiLogicMessageType_ShowRobotInfo;
        size = sizeof(LMsgShowRobotInfo);
    }

    int BotID; // ����λ�ã�������Ϣ
// Edit��CtrlList��ʾ����
    DWORD dwStartTime; // ��ʼʱ��
    int ExecuteActNum;

    //������Ϣ
    int totalSendMsgNum;
    int SendMsgSize;
    //������Ϣ
    int totalReceiveMsgNum;
    int ReceiveMsgSize;
    // ���ζ���ѭ����С�������
    int MinSingleSendMsgNum;
    int MinSingleSendMsgSize;
    // ���ζ���ѭ����������
    int MaxSingleSendMsgNum;
    int MaxSingleSendMsgSize;
    // ���ζ���ѭ����С�������
    int MinSingleRecvMsgNum;
    int MinSingleRecvMsgSize;
    // ���ζ���ѭ�����������
    int MaxSingleRecvMsgNum;
    int MaxSinglerecvMsgSize;

	// ����Monster��Ŀ
	int MonsterMum;										//luo.qin
// �����С�շ���Ϣ
    // Todo:�����С������ʱ����׼ȷ���������С
    MsgStatistician::Msg_Info_ vecMinSendMsgInfo[4];  // ��С��
    MsgStatistician::Msg_Info_ vecMaxSendMsgInfo[20]; // ���
    MsgStatistician::Msg_Info_ vecMinRecvMsgInfo[4];  // ��С��
    MsgStatistician::Msg_Info_ vecMaxRecvMsgInfo[50]; // �����,�����鲻����
// ������Ϣ����
	MsgStatistician::Msg_Info_ mapMsgSendCount[100];
	MsgStatistician::Msg_Info_ mapMsgRecvCount[100];
// ���� Ip port ����Ϣ
    string strIp;
    WORD wPort;
    int nState;
    DWORD dwError;
    bool bConnect;
// ping chat 
    DWORD dwPingTime;
};

// add [10/11/2010 pengbo.yang] ��ʾ��������������ͼ�ֲ������꣬������Ϣ
struct LMsgShowAllRobotInfo : public SBaseGuiLogicMessage 
{
    LMsgShowAllRobotInfo()
    {
        id = EGuiLogicMessageType_ShowAllRobotInfo;
        size = sizeof(LMsgShowAllRobotInfo);
    }
    int BotID;
    // ����������
    int nTotalBotNum;   // ���л����˵�����
    int nOnlineBotNum;  // �������߻����˵������������ߵ�Ϊ nTotalBotNum - nOnlineBotNum
    int nAtkBotNum;     // ���������˵�����
    int nMoveBotNum;    // �ƶ������˵�����
	int nTotalMonsterNum;//���л��������� luo.qin 4.8
    // ToDo�������˵�ͼ�ֲ�
    struct mapInfo
    {
        char mapName[32];
        int BotInMapNum;

        mapInfo()
        {
            memset(mapName, 0, sizeof(mapName));
            BotInMapNum = 0;
        }

        mapInfo& operator=(const pair<string, int>& mapPair)
        {
            strcpy_s( mapName, mapPair.first.c_str() );
            BotInMapNum = mapPair.second;
        }
    };
    mapInfo BotMap[50];
    // ToDo������������
    D3DXVECTOR3 BotPos[50];
    // ToDo: ������־
};  

// ��ʼ�����ݶ�ȡ�����Ϣ
struct LMsgInitReady : public SBaseGuiLogicMessage
{
    LMsgInitReady()
    {
        id = EGuiLogicMessageType_InitReady;
        size = sizeof(LMsgInitReady);
    }
    bool bIsInitReady;
};

#pragma pack( pop )
#endif // __ROBOT_GUILOGCIMESSAGE_H__
