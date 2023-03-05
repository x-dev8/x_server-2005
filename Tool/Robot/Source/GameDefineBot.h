/********************************************************************
    Filename:    GameDefineBot.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#pragma once

#include "MeRTLibsServer.h"
#include "Dxsdk\d3dx9math.h"

#pragma pack( push, 1 )

#define LogObject      "System.log"

#define Script_Path    "..\\Data\\RobotScript"
#define Quest_File     "..\\Data\\Quest"
#define DataFile       "..\\Data\\Config\\Data.config"
#define NpcXml_File    "..\\Data\\Config\\Npc.config"
#define Position_File  "..\\Data\\Config\\Position.config"
#define WorldMapFile   "..\\Data\\Config\\Map.config"
#define LogConfig      "..\\Log4cxx\\log4cxx-Robot.config"
#define LogPath        "..\\LogOutput"
#define LogFile        "..\\LogOutput\\Robot.log"
#define Quest_DropFile "..\\Data\\Quest\\Server\\QuestMonsterDropItem.config"
#define RobotScriptFile "..\\Data\\RobotScript\\RobotScript.config"

typedef std::list<uint8*>                  GuiLogicMessageContainer;
typedef GuiLogicMessageContainer::iterator ItrGuiLogicMessageContaine;

enum EBotType
{
    Bot_Normal = 0,
    Bot_Attack,
    Bot_Fly,   
    Bot_Fight,        // PK机器人
    Bot_Quest,        // 任务机器人
    Bot_Script,
    Bot_Guild,        // 公会机器人
    Bot_Client,
    Bot_Online,     // Idle机器人
    Bot_Team,
    Bot_Ectype,
    Bot_Brome,
    Bot_Login,
    Bot_Business,
    Bot_Firend,
    Bot_PlatformTest,
    Bot_MatrixBot,
    Bot_WarBot,
    //Bot_Commond,    // 指令
    Bot_End,
};





//机器人类型
const static char* s_szType[] = 
{"普通", "打怪" , "传送", "PK", "任务",
"脚本", "军团", "客户端", "在线","组队",
"副本","骑马","登录","交易","交友",
"Gm测试","矩阵机器人","战场机器人",""};

const static char* s_pBotType[] = 
{"普通", "打怪", "飞行", "PK", "任务",
"脚本", "帮派","客户端", "在线","组队",
"副本","骑马","登录","交易","交友",
"Gm测试","矩阵机器人","战场机器人",""};

struct SAreaInfo
{
    int   nMap;
    POINT xPoint;
    int   nRadius;

    SAreaInfo()
    {
        nMap = -1;
        xPoint.x = 0;
        xPoint.y = 0;
        nRadius = 0;
    }
};

struct SSetInfo
{ //bot 设定
    int nRequestStart;
    int nRequestSecond;
    int nRequestCount;

    SSetInfo()
    {      
        nRequestStart = 0;
        nRequestSecond = 0;
        nRequestCount = 0;
    }

    inline SSetInfo& operator = (const SSetInfo &xSetInfo)
    {
        if (this != &xSetInfo)
        {
            nRequestStart = xSetInfo.nRequestStart;
            nRequestSecond = xSetInfo.nRequestSecond;
            nRequestCount = xSetInfo.nRequestCount;
        }
        return *this;
    }
};

struct SAddInfo
{
    int nCount;
    int nStartId;
    int nType;
    int nSpaceTime;
    int nPerCount;
    int nOnlineTime;
    int nFlySpace;
    int nMoveStep;
    SAreaInfo xAreaInfo;    

    SAddInfo()
    { nCount = 0; }

    inline SAddInfo& operator = (const SAddInfo& xAddInfo)
    {
        if (this != &xAddInfo)
        {
            nCount = xAddInfo.nCount;
            nStartId = xAddInfo.nStartId;
            nType = xAddInfo.nType;
            nSpaceTime = xAddInfo.nSpaceTime;
            nPerCount = xAddInfo.nPerCount;
            nOnlineTime = xAddInfo.nOnlineTime;
            nFlySpace = xAddInfo.nFlySpace;
            nMoveStep = xAddInfo.nMoveStep;
            xAreaInfo = xAddInfo.xAreaInfo;
        }

        return *this;
    }

    friend bool operator < (const SAddInfo &xLeft, const SAddInfo &xRight)
    {
        if (xLeft.nStartId != -1 && (xRight.nStartId == -1 || (xLeft.nStartId < xRight.nStartId)))
        { return true; }
        return false;
    }

    friend bool operator == (const SAddInfo &xAddInfo, const int nStartId)
    { return (xAddInfo.nStartId == nStartId); }
};
typedef std::vector<SAddInfo>       AddInfoContainer;
typedef AddInfoContainer::iterator ItrAddInfoContainer;

// for platform Operation
struct OperationMsg
{
    enum PlayOperation
    {
        EPO_KICKPLAYER = 0,                  //    踢角色
        EPO_BANPLAYERSPEAK = 1,              // 禁言
        EPO_BROADCAST = 2,                   // 广播
        EPO_UPDATEBANWOLDLIB = 3,            // 更新世界库
        EPO_MOVEPLAYER2POINT = 4,            // 召唤玩家到指定的点
        EPO_QUERYCHARACTER_ONLINE = 5,       // 查询角色是否在线
        EPO_QUERYCHARACTER = 6,              // 查询角色
        EPO_QUERTONG = 7,                    // 查询堂
        EPO_OPENDOUBLE = 8,                  // 打开双倍
        EPO_KILLMONSTER = 9,                 // 杀死怪物
        EPO_CREATEMONSTER = 10,              // 创建怪物
        EPO_CHANGEROLEATT = 11,              // 改变角色属性
        EPO_CREATEITEM = 12,                 // 创建道具
        EPO_CREATECHARACTER = 13,            // 创建角色
        EPO_REQADDPOINT = 14,                // 请求加点
        EPO_CHANGECHARACTERNAME = 15,        // 改变角色名
        EPO_ADDITEM = 16,                    // 添加道具
        EPO_RELOADTRADESHOP = 17,            // 请求重载商店
        EPO_SHUTDOWNSERVERS = 18,            // 请求重启服务器
        EPO_CHANGEMAPEXPRATE= 19,            // 改便服务器经验比率
        EPO_TOTALHANDLE,
    };

    OperationMsg()
    {
        Clear();
    }

    int SetString(const char* szString)
    {
        if (NULL == szString || strlen(szString) >= sizeof(szParm))
        {
            return 0;
        }
        return strncpy_s(szParm,sizeof(szParm),szString,sizeof(szParm)-1);;
    }

    void Clear()
    {
        TestOperation = EPO_TOTALHANDLE;
        memset(nParm,0,sizeof(nParm));
        memset(szParm,0,sizeof(szParm));
        fParm = 0.0;
    }
    int TestOperation;

    int nParm[3];
    float fParm;
    char szParm[512];

    OperationMsg& operator = (const OperationMsg& work)
    {
        if (this == &work)
        {
            return *this;
        }
        memcpy_s(this,sizeof(OperationMsg),&work,sizeof(OperationMsg));
        return *this;
    }
};

struct SShowRobotInfo
{
    int8   account[32]; // 帐号
    uint32 id;          // 机器人的Id
    uint16 type;        // 类型
    uint16 state;       // 状态
    int8   tipInfo[64]; // 自提示
    int8   channel[32]; // 频道
    int8   map[64];     // 所在地图名字

    SShowRobotInfo()
    { memset( this, 0, sizeof(SShowRobotInfo)); }
};

//////////////////////////////////////////////////////////////////////////
const int WM_ADDBOTLIST = ::RegisterWindowMessage("__WM_ADDBOTLIST__");

inline float GetDistance(D3DXVECTOR3 v1, D3DXVECTOR3 v2)
{
    float x = v1.x - v2.x;
    float y = v1.y - v2.y;
    return sqrtf(x*x + y*y);
}

#pragma pack( pop )
