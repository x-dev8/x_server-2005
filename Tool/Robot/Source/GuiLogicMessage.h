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
    EGuiLogicMessageType_PauseAddBot     = 1002, // 暂停/继续 添加机器人
    EGuiLogicMessageType_PlaySkill       = 1003, // 释放/暂停释放 技能
    EGuiLogicMessageType_Moving          = 1004, // for 机器人移动
    EGuiLogicMessageType_PlayAttack      = 1005, // For 机器人开始攻击
    EGuiLogicMessageType_BotRide         = 1006, // 机器人骑马
    EGuiLogicMessageType_ReloadLuaScript = 1007, // 重新加载lua脚本
	EGuiLogicMessageType_PrepareSuit     = 1008, // 准备换装

    // LogicThread to GuiThread
    EGuiLogicMessageType_RobotInfoChange = 2000,
    EGuiLogicMessageType_ShowRobotInfo   = 2001, // Logic To Ui 显示机器人的信息
    EGuiLogicMessageType_ShowAllRobotInfo = 2002, // 显示机器人数量，地图分布，坐标，错误信息
    EGuiLogicMessageType_InitReady       = 2003, // Logic 2 Ui 确认是否初始化完成
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
// 设置矩阵机器人间距
//struct GMsgSetBetweenSpace : public SBaseGuiLogicMessage
//{
//    GMsgSetBetweenSpace()
//    {
//        id = EGuiLogicMessageType_SetBetweenSpace;
//        size = sizeof(GMsgSetBetweenSpace);
//    }
//    int nSpace;
//};
// 暂停/继续 添加机器人
struct GMsgPauseBot : public SBaseGuiLogicMessage
{
    GMsgPauseBot()
    {
        id = EGuiLogicMessageType_PauseAddBot;
        size = sizeof(GMsgPauseBot);
    }
    bool bIsPause;
};
// 释放技能
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
// 机器人移动
struct GMsgBotMoving : public SBaseGuiLogicMessage 
{
    GMsgBotMoving()
    {
        id = EGuiLogicMessageType_Moving;
        size = sizeof(GMsgBotMoving);
    }
    bool bIsMove; // 是否移动
    int nMoveRange; // 移动距离
};
// 机器人攻击
struct GMsgBotPlayAttack : public SBaseGuiLogicMessage
{
    GMsgBotPlayAttack()
    {
        id = EGuiLogicMessageType_PlayAttack;
        size = sizeof(GMsgBotPlayAttack);
    }
    bool bIsPlayAttack;
};
// 骑马
struct GMsgBotRide : public SBaseGuiLogicMessage
{
    GMsgBotRide()
    {
        id = EGuiLogicMessageType_BotRide;
        size = sizeof(GMsgBotRide);
    }
    bool bIsRide;
};
// 重新加载Lua脚本文件
struct GMsgReLoadLuaScript : public SBaseGuiLogicMessage
{
    GMsgReLoadLuaScript()
    {
        id = EGuiLogicMessageType_ReloadLuaScript;
        size = sizeof(GMsgReLoadLuaScript);
    }
    bool bIsReloadLuaScript; //是否重新加载Lua脚本
};
// 准备换装
struct GMsgPrepareSuit : public SBaseGuiLogicMessage 
{
	GMsgPrepareSuit()
	{
		id = EGuiLogicMessageType_PrepareSuit;
		size = sizeof( GMsgPrepareSuit );
	}
};
//////////////////////////////////////////////////////////////////////////
// 逻辑线程到UI线程
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

    int BotID; // 坐标位置，错误信息
// Edit与CtrlList显示数据
    DWORD dwStartTime; // 起始时间
    int ExecuteActNum;

    //发送消息
    int totalSendMsgNum;
    int SendMsgSize;
    //接收消息
    int totalReceiveMsgNum;
    int ReceiveMsgSize;
    // 单次动作循环最小发送情况
    int MinSingleSendMsgNum;
    int MinSingleSendMsgSize;
    // 单次动作循环最大发送情况
    int MaxSingleSendMsgNum;
    int MaxSingleSendMsgSize;
    // 单次动作循环最小接收情况
    int MinSingleRecvMsgNum;
    int MinSingleRecvMsgSize;
    // 单次动作循环最大接收情况
    int MaxSingleRecvMsgNum;
    int MaxSinglerecvMsgSize;

	// 创建Monster数目
	int MonsterMum;										//luo.qin
// 最大最小收发消息
    // Todo:数组大小有误，暂时不能准确给出数组大小
    MsgStatistician::Msg_Info_ vecMinSendMsgInfo[4];  // 最小发
    MsgStatistician::Msg_Info_ vecMaxSendMsgInfo[20]; // 最大发
    MsgStatistician::Msg_Info_ vecMinRecvMsgInfo[4];  // 最小收
    MsgStatistician::Msg_Info_ vecMaxRecvMsgInfo[50]; // 最大收,【数组不够】
// 所有消息总数
	MsgStatistician::Msg_Info_ mapMsgSendCount[100];
	MsgStatistician::Msg_Info_ mapMsgRecvCount[100];
// 连接 Ip port 等信息
    string strIp;
    WORD wPort;
    int nState;
    DWORD dwError;
    bool bConnect;
// ping chat 
    DWORD dwPingTime;
};

// add [10/11/2010 pengbo.yang] 显示机器人数量，地图分布，坐标，错误信息
struct LMsgShowAllRobotInfo : public SBaseGuiLogicMessage 
{
    LMsgShowAllRobotInfo()
    {
        id = EGuiLogicMessageType_ShowAllRobotInfo;
        size = sizeof(LMsgShowAllRobotInfo);
    }
    int BotID;
    // 机器人数量
    int nTotalBotNum;   // 所有机器人的数量
    int nOnlineBotNum;  // 所有在线机器人的数量，不在线的为 nTotalBotNum - nOnlineBotNum
    int nAtkBotNum;     // 攻击机器人的数量
    int nMoveBotNum;    // 移动机器人的数量
	int nTotalMonsterNum;//所有机器人总数 luo.qin 4.8
    // ToDo：机器人地图分布
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
    // ToDo：机器人坐标
    D3DXVECTOR3 BotPos[50];
    // ToDo: 错误日志
};  

// 初始化数据读取完成消息
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
