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
    Bot_Fight,        // PK������
    Bot_Quest,        // ���������
    Bot_Script,
    Bot_Guild,        // ���������
    Bot_Client,
    Bot_Online,     // Idle������
    Bot_Team,
    Bot_Ectype,
    Bot_Brome,
    Bot_Login,
    Bot_Business,
    Bot_Firend,
    Bot_PlatformTest,
    Bot_MatrixBot,
    Bot_WarBot,
    //Bot_Commond,    // ָ��
    Bot_End,
};





//����������
const static char* s_szType[] = 
{"��ͨ", "���" , "����", "PK", "����",
"�ű�", "����", "�ͻ���", "����","���",
"����","����","��¼","����","����",
"Gm����","���������","ս��������",""};

const static char* s_pBotType[] = 
{"��ͨ", "���", "����", "PK", "����",
"�ű�", "����","�ͻ���", "����","���",
"����","����","��¼","����","����",
"Gm����","���������","ս��������",""};

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
{ //bot �趨
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
        EPO_KICKPLAYER = 0,                  //    �߽�ɫ
        EPO_BANPLAYERSPEAK = 1,              // ����
        EPO_BROADCAST = 2,                   // �㲥
        EPO_UPDATEBANWOLDLIB = 3,            // ���������
        EPO_MOVEPLAYER2POINT = 4,            // �ٻ���ҵ�ָ���ĵ�
        EPO_QUERYCHARACTER_ONLINE = 5,       // ��ѯ��ɫ�Ƿ�����
        EPO_QUERYCHARACTER = 6,              // ��ѯ��ɫ
        EPO_QUERTONG = 7,                    // ��ѯ��
        EPO_OPENDOUBLE = 8,                  // ��˫��
        EPO_KILLMONSTER = 9,                 // ɱ������
        EPO_CREATEMONSTER = 10,              // ��������
        EPO_CHANGEROLEATT = 11,              // �ı��ɫ����
        EPO_CREATEITEM = 12,                 // ��������
        EPO_CREATECHARACTER = 13,            // ������ɫ
        EPO_REQADDPOINT = 14,                // ����ӵ�
        EPO_CHANGECHARACTERNAME = 15,        // �ı��ɫ��
        EPO_ADDITEM = 16,                    // ��ӵ���
        EPO_RELOADTRADESHOP = 17,            // ���������̵�
        EPO_SHUTDOWNSERVERS = 18,            // ��������������
        EPO_CHANGEMAPEXPRATE= 19,            // �ı�������������
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
    int8   account[32]; // �ʺ�
    uint32 id;          // �����˵�Id
    uint16 type;        // ����
    uint16 state;       // ״̬
    int8   tipInfo[64]; // ����ʾ
    int8   channel[32]; // Ƶ��
    int8   map[64];     // ���ڵ�ͼ����

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
