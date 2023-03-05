#include "stdafx.h"
#include "Bot.h"
#include "GameBot.h"
#include "MainFrm.h"
#include "MessageDefine.h"
#include "FuncPerformanceLog.h"
#include "Helper.h"
#include "ProcessCharInfo.h"
#include "application_config.h"
#include "GameDefineBot.h"
#include "XmlRpc/XmlRpc.h"
#include "md5.h"
#include "sha1.h"
#include "ItemDetail.h"
#include "GameTimer.h"
#include "ScriptManager.h"
#include "NpcInfo.h"
#include "PosChangePackage.h"
#include "AckEnterWorldPackage.h"
#include "EnterMySightPackage.h"
#include "CountryDefine.h"
#include "SimpleCryptograph.h"

#include "NpcInfo.h"
#pragma warning(disable:4201)
#pragma warning(disable:4706)
#pragma warning(disable:4702)
#pragma warning(disable:4189)
#pragma warning(disable:4389)

#define TryLoginMax 50  //最大尝试登录次数

#define PICKITEM_DISTANCE 1.5
#define YOUQUANDIYU_MAPID 51
#define YOUQUANDIYU_ECTYPE_MAPID 55
#define LOOPQUERYMAXNUM   20
#define DefaultBagNum    (20)

#define _LOGININFO_ 1

//#include "HttpEncapsulation/HttpEncapsulation.h"

using namespace XmlRpc;

#if 0
#define __NET_TEST__
#endif

//进入游戏随即地图坐标
POINT PosInfo[MAP_COUNT] = {{100,100},{450,260},{200,500},{440,640},{200,200},{380,310},{510,550},{340,430},{80, 630},};


CPosChangePackage g_PosMsgProcess;
float RandFloat()
{
    return (float)rand()/0x7fff;
}

D3DXVECTOR3 RandDir()
{
    D3DXVECTOR3 dir(-0.5+RandFloat(), -0.5+RandFloat(), -0.5+RandFloat());
    D3DXVec3Normalize(&dir, &dir);
    return dir;
}

class XmlRpcClientGuard
{
public:
    XmlRpcClientGuard( XmlRpcClient* pRpcClient )
    {
        if ( pRpcClient != NULL )
        { pRpcClient_ = pRpcClient; }
    }

    ~XmlRpcClientGuard()
    {
        if ( pRpcClient_ != NULL )
        { pRpcClient_->close(); }
    }

private:
    XmlRpcClient* pRpcClient_;
};

bool BaseRobot::m_bIsLoginGLS = false;

BaseRobot::BaseRobot() : m_vPos(0,0,0),m_ReqConnectNum(0),_charDbId(0)
,m_ReqLogRoleInfo(0),dw_SleepTime(0)
,IsLearn(false),dw_FirstLoginTotalTime(0)
,bIsPlayTime(false),dw_FirstLoginGLSTime(0),dw_FirstLoginSelectRoleTime(0)
,dw_FirstEnterWorldTime(0),bIsFirstReqLogin(true)
,dw_LoginGLSTime(0),dw_LoginSelectRoleTime(0),dw_EnterWorldTime(0), CanControl(true)
,m_dwDeadTime(HQ_TimeGetTime()),m_dwEquipDoneTime(HQ_TimeGetTime())
,m_LastCreateTime(HQ_TimeGetTime()),m_bFirstInWorld(true)
{
	g_dwSwitchGateTime = 0;
	g_dwSwitchGatePeriod = 3000;
	g_bSwitchGate = FALSE;
	g_bEndGetCharacter = FALSE;
	m_bNeedAckAgain = false;
	nTimeLastConfirm=0;
	isReadyEnterGame = false;

	dwEnterWorldQueueStartTime = 0;
	isEnterWorldQueue = false;
	
	memset(m_szBotName, 0, sizeof(m_szBotName));
    memset(m_szPassWord, 0, sizeof(m_szPassWord));
    memset(m_szTips, 0, sizeof(m_szTips));
    sPlayerSlot =0 ;
    m_dwLastLoopTime = 0;
    _accountId = 0;
    m_bAckLogin = false;
    m_vectorCharInfo.resize(CHARACTOR_COUNT);
    m_vCharacterID.resize(CHARACTOR_COUNT);
    m_dwStartMovingTime = 0;
    m_vLastProTime.resize(State_End);
    m_nMoveStep = 500;
    m_nTotalMsgNum = 0;
    m_nTotalPosPack = 0;
    m_nTotalPosMsg = 0;
    m_nTotalSightPack = 0;
    m_nTotalSightMsg = 0;
    m_pItemBag = NULL;

    isTest = false;

    m_nMapID = -1;
    m_strMap.clear();
    m_listChatMsg.clear();

    m_dwLastTime = 0;
    m_nMoveSpaceTimes = 10;

    m_vDir.x = 0;
    m_vDir.y = 0;
    m_vDir.z = 0;
    
    m_SendPackNum = 0;
    m_RecvPackNum = 0;
    ShowPackTime = 0;
    m_RecvPackSize = 0;
    m_SendPackSize = 0;
    m_FirstSendPackage = true;

    ClearMovePos();

    m_pSetInfo = NULL;

    m_dwReqCharInfoTime = 0;
    m_nReqCharInfoCount = 0;

    m_bFlyMap = false;
    m_bGetItem = false;
    m_dwInitStartTime = 0;

    m_dwLoginError = 0;

    _targetChannelName = _T("A服");


	g_bSwitchGate=false;

    m_pSkillBag  = NULL;
    m_pItemBag   = NULL;
    m_BromeItems = NULL;
	m_PetItems   = NULL;

    m_bLoadMapOver = false;
    m_WaitUpdateSightTime = 0;

    m_BotType = Bot_End;
    LastSummonPetTime = 0;
    m_LastSeeAttactTime = 0;
    NeedCheckLoginTime = true;
    CheckLoginTime = 0;

    m_dwMoveSpaceTime = 500; // 移动间隔时间初始化
	m_MonsterNum = 0;
	m_hasCreateRole = false;
    //SetOutMessageEncType( msgflag_des8 );
    //SetConnectOverTime( 5 ); // 5ms
}

BaseRobot::~BaseRobot(void)
{
    if (m_pSetInfo != NULL)
    {
        delete m_pSetInfo;
        m_pSetInfo = NULL;
    }
}

BOOL BaseRobot::Init(SSetInfo *pSetInfo)
{
    if (m_pSetInfo == NULL)
    {
        m_pSetInfo = new SSetInfo();
    }
    
    if(m_pSetInfo == NULL || pSetInfo == NULL)
    {
        return FALSE;
    }

    *m_pSetInfo = *pSetInfo;

    //SetNoteType( NT_ConnectNode );
    return TRUE;
}

// void BaseRobot::SetGLSAddress( const char* szIP, uint32 port )
// {
//     strncpy_s( _szGLSIP, szIP, sizeof(_szGLSIP) - 1);
//     _GLSPort = port;
// }

// void BaseRobot::OnConnectToServer()
// {
// 	//m_pConnector->SetMaxQueueMsgNum( IMeConnector::ET_InQueue, -1);
//     //m_pConnector->SetMaxQueueMsgNum( IMeConnector::ET_OutQueue, -1);
//     //m_pConnector->SetOutMessageEncType( msgflag_des8, true );
//     //m_pConnector->SetSkipInQueueWhenReset( true ); // 如果有被动的关闭 清空队列消息
// }



void BaseRobot::Update()
{
	INetworkNode::Update();

	if (isEnterWorldQueue && HQ_TimeGetTime() - dwEnterWorldQueueStartTime >= 3000 )
	{	//收到被排队的3秒后再发一次进入地图消息
		isEnterWorldQueue = false;
		MsgEnterWorld msg;
		msg.nSwitchStageType = SSRT_EnterGameServerMap;
		msg.stWhichSlot      = sPlayerSlot;
		msg.dwCharacterID    = m_vCharacterID[sPlayerSlot];
		msg.dwEnterWorldTime = HQ_TimeGetTime();
		msg.dwAccountId      = _accountId;
		SendMsg( &msg );
		isReadyEnterGame = false;
	}
	if ((!IsConnectted() || HQ_TimeGetTime() > g_dwSwitchGateTime) && g_bSwitchGate)
	{
		SwitchGate(!m_bNeedAckAgain);
	}
	switch(GetBotState())
	{
	case State_CreateChar:
		{ HandleStateCreateChar();}
		break;

	case State_Play:
		{ HandleStatePlay(); }
		break;
	case State_End:
		{ HandleStateEnd();  }
		break;
	}

#ifdef HIDE_BOT_INFO
	///////////////////////////////////////////////////////////////////////
	//执行完一轮updata以后更新统计信息
	m_xMsgStatistician.SetLoopCount();
	m_xMsgStatistician.UpdataMaxAndMinSendInfo();

	theApp.m_xTatolMsgStatistician.SetLoopCount();
	theApp.m_xTatolMsgStatistician.UpdataMaxAndMinSendInfo();
#endif // HIDE_BOT_INFO
}

void BaseRobot::SendMsg(Msg* pMsg)
{
    if ( !GetConnector() )
    { return; }

    if(!GetConnector()->SendMsg(pMsg))
    {
   //     Close();
        LOG_MESSAGE(LogObject, LOG_PRIORITY_INFO, "Send Msg Error");

        if (m_FirstSendPackage)
       {
           ShowPackTime = HQ_TimeGetTime();
           m_FirstSendPackage = false;
       }
   }
   else
   {
#ifdef HIDE_BOT_INFO
       //////////////////////////////////////////////////////////////////
       StatMsgInfo(Msg_Send, pMsg);  //统计发送数据
       ///////////////////////////////////////////////////////////////////
#else
       ++m_SendPackNum;
       m_SendPackSize += pMsg->GetLength();
#endif // HIDE_BOT_INFO
   }
}

/* 主界面输出提示信息*/
void BaseRobot::SetTipsInfo(const char* pszTips)
{
    sprintf_s( m_szTips, sizeof(m_szTips) - 1 , "%s", pszTips); 

    LMsgRobotInfoChange msg;
    msg.info.id       = GetBotID();
    msg.info.type     = GetType();
    msg.info.state    = GetBotState();
    strncpy_s( msg.info.account, sizeof(msg.info.account), GetAccount(),     sizeof(msg.info.account) - 1 );
    strncpy_s( msg.info.tipInfo, sizeof(msg.info.tipInfo), m_szTips,         sizeof(msg.info.tipInfo) - 1 );
    strncpy_s( msg.info.channel, sizeof(msg.info.channel), GetChannelName(), sizeof(msg.info.channel) - 1 );
    strncpy_s( msg.info.map,     sizeof(msg.info.map),     GetMapName(),     sizeof(msg.info.map)     - 1 );
    theApp.PushMessage( &msg );
}

void BaseRobot::InitPlayerSkill()
{
    if (IsLearn)
    {
        return;
    }
    IsLearn = true;
    typedef std::pair<BotApplication::SkillMap::iterator,BotApplication::SkillMap::iterator> Pairs;
    Pairs valuePair = theApp.gBotApplication.RoleSkillMap.equal_range(GetSelfProfession());
    for (BotApplication::SkillMap::iterator itr = valuePair.first;itr != valuePair.second;++itr)
    {
        BotApplication::skillStruct InitSkill = itr->second;
        //CItemDetail::SItemSkill* psikll = GettheItemDetail().GetSkillByID(InitSkill.id,1);
        //if (NULL != psikll)
        {
            //for (int i = 1;i <= psikll->ustSkillMaxLvl;++i)
            {
                MsgChat msg;
                char temp[100];
                sprintf_s(temp,sizeof(temp),"/LearnSkill %d %d",InitSkill.id,InitSkill.SkillLevel);
                msg.SetString(temp);
                SendMsg(&msg);
            }
        }
    }
    return;

    switch (GetSelfProfession())
    {
    case EArmType_Warrior:
        {
            for (int i = 1000;i<=1020;++i)
            {
                MsgChat msg;
                char temp[100];
                sprintf_s(temp,sizeof(temp),"/LearnSkill %d 1",i);
                msg.SetString(temp);
                SendMsg(&msg);
            }
        }
        break;
    case EArmType_Mage:
        {
             for (int i = 1030;i<=1050;++i)
             {
                 MsgChat msg;
                 char temp[100];
                 sprintf_s(temp,sizeof(temp),"/LearnSkill %d 1",i);
                 msg.SetString(temp);
                 SendMsg(&msg);
             }
        }
        break;
    case EArmType_Taoist:
        {
             for (int i = 1090;i<=1110;++i)
             {
                 MsgChat msg;
                 char temp[100];
                 sprintf_s(temp,sizeof(temp),"/LearnSkill %d 1",i);
                 msg.SetString(temp);
                 SendMsg(&msg);
             }
        }
        break;
    case EArmType_Assassin:
        {
            for (int i = 1060;i<=1080;++i)
            {
                MsgChat msg;
                char temp[100];
                sprintf_s(temp,sizeof(temp),"/LearnSkill %d 1",i);
                msg.SetString(temp);
                SendMsg(&msg);
            }
        }
        break;
    case EArmType_Hunter:
        {
             for (int i = 1120;i<=1140;++i)
             {
                 MsgChat msg;
                 char temp[100];
                 sprintf_s(temp,sizeof(temp),"/LearnSkill %d 1",i);
                 msg.SetString(temp);
                 SendMsg(&msg);
             }
        }
        break;
    }
}

void BaseRobot::InitLevel()
{
    std::string FullPath = theBotDataCenter.ScriptFilePath;
    FullPath += theBotDataCenter.ScriptFileName;
    uint32 result = theScriptManager.LoadScript(FullPath.c_str());
    if (ER_Success == result)
    {
        theScriptManager.ScriptFunctionVoid("InitBotLevel",this);
	}
//     if(GetBotLevel() < 50)
//     {
//         ReqLvlUp(50);
//         return;
//     }
}

void BaseRobot::InitPlayGame(UINT mapid)
{
    //m_bFlyMap = true;
    if (m_bFlyMap || GetMapID() == m_xAreaInfo.nMap)  //如果已经飞过地图了,或者当前所在地图就是目标地图
    {
        //SetBotState(State_Play);
        //m_bIsLogin = false;
        //--g_bLogining;   //进入以后设置为false;
        return;
    }

    if (m_dwInitStartTime < HQ_TimeGetTime())
    {
        //请求装备
        InitGetItem();
        InitPlayerSkill();
        //Sleep(100);
        //请求等级
        InitLevel();

        ////////////////////////////////////////////先让机器人均匀分布
        if (vecMap.empty())
        {
            int nCount = theMapConfig.MapDataCount();
            for (int i = 0; i < nCount; ++i)
            {
                MapConfig::MapData *pMapData = theMapConfig.GetMapDataByIndex(i);
                if (pMapData == NULL) { continue; }
                if (!pMapData->IsEctypeMap() && !pMapData->MapName.empty()&&(pMapData->Id != YOUQUANDIYU_MAPID || pMapData->Id != YOUQUANDIYU_ECTYPE_MAPID))
                {
                    vecMap.push_back(pMapData->Id);
                }
            }
            nMapCount = vecMap.size();
        }

        static int nIndex = 0;
        int nPos = (rand() % (40 * (int)CHUNK_SIZE - 200)) + 50;

		//luo.qin 4.15 begin去掉注释
        if (mapid == 0)
        {
            if (GetMapID() != vecMap[nIndex])
            {
                FlyToMap(vecMap[nIndex], nPos, nPos);
            }
        }
        else
        {
            FlyToMap(mapid, nPos, nPos);
        }
        //luo.qin 4.15 end

        m_bFlyMap = true;
        ++nIndex;
        if (nIndex >= nMapCount)
        {
            nIndex = 0; 
        }

        m_bFlyMap = true;
        m_dwInitStartTime = HQ_TimeGetTime() + 5000;
        SetTipsInfo("切换地图");
    }        
}

//按照职业和性别来获得装备
static const int s_nItemTatol = 8;    //总共4套  0 = 不请求
static const int s_nItemCount = 8;    //一套8件
static int s_nItemID[2][s_nItemTatol] = {{11100, 11104, 11102, 11101,11103,11105,11106,8003}, {11160, 11164, 11162, 11101,11103,11105,11106,8354}}; //每套装备的起始ID  0 = 不请求,

//按照职业来获得装备
static const int s_nItemTotal = 10;	  //一套10件 luo.qin 3.21
static int s_nItemID_Hunter[6][10] = {{9104,11501,11502,11503,11504,11505,11506,11507,11508,11509},
{9114,11541,11542,11543,11544,11545,11546,11547,11548,11549},
{9124,12041,12042,12043,12044,12045,12046,12047,12048,12049},
{9129,11511,11512,11513,11514,11515,11516,11517,11518,11519},
{9134,11521,11522,11523,11524,11525,11526,11527,11528,11529},
{9207,11551,11552,11553,11554,11555,11556,11557,11558,11559} };

static int s_nItemID_Warrior[1][10] = {9130,10721,10722,10723,10724,10725,10726,10727,10728,10729 };
static int s_nItemID_Mage[1][10] = {9131,10921,10922,10923,10924,10925,10926,10927,10928,10929};
static int s_nItemID_Taoist[1][10] = {9133,11321,11322,11323,11324,11325,11326,11327,11328,11329};
static int s_nItemID_Assassin[1][10] = {9132,11121,11122,11123,11124,11125,11126,11127,11128,11129};

//不同职业的装备luo.qin 3.29
void BaseRobot::ChangeEquipByProfession()
{
	switch (GetSelfProfession())
	{
	case EArmType_Warrior:
		{
			ReqRemoveAllEquip( GetBotDBID() );
			for (int i = 0; i < s_nItemTotal; ++i )
			{
				//ReqCreateItemForBot( GetBotDBID(), s_nItemID_Warrior[0][i], 1, 0 );
				ReqItem(s_nItemID_Warrior[0][i]);
			}
		}
		break;
	case EArmType_Mage: // 法王
		{
			ReqRemoveAllEquip( GetBotDBID() );
			for (int i = 0; i < s_nItemTotal; ++i )
			{
				//ReqCreateItemForBot( GetBotDBID(), s_nItemID_Mage[0][i], 1, 0 );
				ReqItem(s_nItemID_Mage[0][i]);
			}
		}
		break;
	case EArmType_Taoist:
		{
			ReqRemoveAllEquip( GetBotDBID() );
			for (int i = 0; i < s_nItemTotal; ++i )
			{
				//ReqCreateItemForBot( GetBotDBID(), s_nItemID_Taoist[0][i], 1, 0 );
				ReqItem(s_nItemID_Taoist[0][i]);
			}
		}
		break;
	case EArmType_Assassin:
		{
			ReqRemoveAllEquip( GetBotDBID() );
			for (int i = 0; i < s_nItemTotal; ++i )
			{
				//ReqCreateItemForBot( GetBotDBID(), s_nItemID_Assassin[0][i], 1, 0 );
				ReqItem(s_nItemID_Assassin[0][i]);
			}
		}
		break;
	case EArmType_Hunter:
		{
			RandChangeEquip_BotCommand();
		}
		break;
	}
}
//随机换装备 luo.qin 3.21
void BaseRobot::RandChangeEquip()
{
	int nSelect = theRand.rand32() % 5;

	for (int i = 0; i < s_nItemTotal; ++i )
	{
		//请求装备
		ReqGetItem( s_nItemID_Hunter[nSelect][i], 1, 0 );

	}

}

//随机换装备 luo.qin 3.24
void BaseRobot::RandChangeEquip_BotCommand()
{
	ReqRemoveAllEquip( GetBotDBID() );

	int nSelect = theRand.rand32() % 5;
	for (int i = 0; i < s_nItemTotal; ++i )
	{
		//请求装备
		//ReqCreateItemForBot( GetBotDBID(), s_nItemID_Hunter[nSelect][i], 1, 0 );
		ReqItem(s_nItemID_Hunter[nSelect][i]);

	}

}

//BOT命令:请求创建装备，并在创建之前清理自身和服务器的玩家包裹和装备栏数据luo.qin 3.24
void BaseRobot::ReqCreateItemForBot(int nDBID, int nItemID, int nCount, int nFlag)
{
	if (nItemID < 0) { return; }

	MsgChat msg( MsgChat::CHAT_TYPE_NORMAL );
	strncpy( msg.chatHeader.szToName, m_CharInfo.baseinfo.aptotic.szCharacterName , MAX_NAME_STRING - 1 );

	char szMsg[dr_MaxChatString - 1] = {0};
	std::string command = ROBOT_REQUEST_COMMAND;
	command += "CreateEquip %d %d %d %d";
	_snprintf( szMsg, dr_MaxChatString - 1, command.c_str(), nDBID, nItemID, nCount, nFlag);

	msg.SetString(szMsg);
	SendMsg( &msg );

}
//BOT命令:在创建之前清理自身和服务器的玩家包裹和装备栏数据luo.qin 3.24
void BaseRobot::ReqRemoveAllEquip(int nDBID)
{
	MsgChat msg( MsgChat::CHAT_TYPE_NORMAL );
	strncpy( msg.chatHeader.szToName, m_CharInfo.baseinfo.aptotic.szCharacterName , MAX_NAME_STRING - 1 );

	char szMsg[dr_MaxChatString - 1] = {0};
	std::string command = ROBOT_REQUEST_COMMAND;
	command += "RemoveAllEquip %d";
	_snprintf( szMsg, dr_MaxChatString - 1, command.c_str(), nDBID);

	msg.SetString(szMsg);
	SendMsg( &msg );

}

//机器人命令:机器人创建怪物luo.qin 3.17 
void BaseRobot::BotCreateMonster( DWORD dwDBID, DWORD dwMonsterID, float fPos_X, float fPos_Y, DWORD dwMonsterNum, DWORD dwMapID, DWORD dwMonsterType, float fRadius )
{	
	MsgChat msg( MsgChat::CHAT_TYPE_NORMAL );
	strncpy( msg.chatHeader.szToName, m_CharInfo.baseinfo.aptotic.szCharacterName , MAX_NAME_STRING - 1 );

	char szMsg[dr_MaxChatString - 1] = {0};

	std::string command = ROBOT_REQUEST_COMMAND;
	command += "CreateMonster %d %d %d %d %d";

	_snprintf( szMsg, dr_MaxChatString - 1, command.c_str(), dwDBID, dwMonsterID, dwMonsterNum, (int)fPos_X, (int)fPos_Y );

	msg.SetString( szMsg );
	SendMsg( &msg );
}

//机器人命令;换装备luo.qin 3.21
void BaseRobot::ChangeEquip( DWORD dwDBID )
{
	MsgChat msg( MsgChat::CHAT_TYPE_NORMAL );
	strncpy( msg.chatHeader.szToName, m_CharInfo.baseinfo.aptotic.szCharacterName , MAX_NAME_STRING - 1 );

	char szMsg[dr_MaxChatString - 1] = {0};

	std::string command = ROBOT_REQUEST_COMMAND;
	command += "ChangeEquip %d";

	_snprintf( szMsg, dr_MaxChatString - 1, command.c_str(), dwDBID );

	msg.SetString( szMsg );
	SendMsg( &msg );
}

bool BaseRobot::InitGetItem()
{
    if (m_bGetItem)  //创建人物以后
    {
        //先判断职业
        int nSex = m_CharInfo.baseinfo.aptotic.ucSex;
        
        if (nSex < 0 || nSex > Sex_Max)
        {
            m_bGetItem = false;
            return false;
        }

        int nSelect = rand() % s_nItemTatol;

        int nStartItemID = s_nItemID[nSex][nSelect];
        if(nStartItemID != 0)    //ID为0 时, 不请求装备
        {
            for (int i = 0; i < s_nItemCount; ++i, ++nStartItemID)
            {
                //请求装备
                ReqGetItem(nStartItemID, 1, 0);
                //Sleep(1000);
            }
        }        

        m_bGetItem = false;
        return true;
    }

    return false;
}

void BaseRobot::PlayGame()
{
	Move();
	static vector<int> vecPlayMap;
	static int nPlayMapCount = 0;
	static int nFlyIndex = 0;
	static DWORD dwLastReqFlyTime = HQ_TimeGetTime();

#define ReqLeaveDiYuTime 20*1000

	if ((GetMapID() == YOUQUANDIYU_MAPID/*||GetMapID() == YOUQUANDIYU_ECTYPE_MAPID*/))
	{
		LoadRandFlyMap();
		if (HQ_TimeGetTime() - dwLastReqFlyTime >= ReqLeaveDiYuTime)
		{
			RandFly();
			dwLastReqFlyTime = HQ_TimeGetTime();
		}
		//         dwLastReqFlyTime = HQ_TimeGetTime();
		//         if (vecPlayMap.empty())
		//         {
		//             int nCount = theMapConfig.MapDataCount();
		//             for (int i = 0; i < nCount; ++i)
		//             {
		//                 MapConfig::MapData *pMapData = theMapConfig.GetMapDataByIndex(i);
		//                 if (pMapData == NULL) { continue; }
		//                 if (!pMapData->IsEctypeMap() && !pMapData->MapName.empty() && (pMapData->Id != YOUQUANDIYU_MAPID || pMapData->Id != YOUQUANDIYU_ECTYPE_MAPID))
		//                 {
		//                     vecPlayMap.push_back(pMapData->Id);
		//                 }
		//             }
		//             nPlayMapCount = vecPlayMap.size();
		//         }
		// 
		//         int nPos = (rand() % (40 * (int)CHUNK_SIZE - 200)) + 50;
		// 
		//         if (GetMapID() != vecPlayMap[nFlyIndex])
		//         {
		//             FlyToMap(vecPlayMap[nFlyIndex], nPos, nPos);
		//         }
		// 
		//         m_bFlyMap = true;
		//         ++nFlyIndex;
		//         if (nFlyIndex >= nPlayMapCount)
		//         {
		//             nFlyIndex = 0; 
		//         }
	}

// 	if (GetMapID() == 11 && theApp.LoadFileMappingNum() >= theBotDataCenter.BotFlyLimit && m_bEnterWorldSuccess)
// 	{
// 		LoadRandFlyMap();
// 		RandFly();
// 	}

// 	if (!m_bFlyMap && m_bEnterWorldSuccess)
// 	{
// 		LoadRandFlyMap();
// 		RandFly();
// 		//         if (vecPlayMap.empty())
// 		//         {
// 		//             int nCount = theMapConfig.MapDataCount();
// 		//             for (int i = 0; i < nCount; ++i)
// 		//             {
// 		//                 MapConfig::MapData *pMapData = theMapConfig.GetMapDataByIndex(i);
// 		//                 if (pMapData == NULL) { continue; }
// 		//                 if (!pMapData->IsEctypeMap() && !pMapData->MapName.empty()&&(pMapData->Id != YOUQUANDIYU_MAPID || pMapData->Id != YOUQUANDIYU_ECTYPE_MAPID))
// 		//                 {
// 		//                     vecPlayMap.push_back(pMapData->Id);
// 		//                 }
// 		//             }
// 		//             nPlayMapCount = vecPlayMap.size();
// 		//         }
// 		// 
// 		//         int nPos = (rand() % (40 * (int)CHUNK_SIZE - 200)) + 50;
// 		// 
// 		//         if (GetMapID() != vecPlayMap[nFlyIndex])
// 		//         {
// 		//             FlyToMap(vecPlayMap[nFlyIndex], nPos, nPos);
// 		//         }
// 		// 
// 		//         m_bFlyMap = true;
// 		//         ++nFlyIndex;
// 		//         if (nFlyIndex >= nPlayMapCount)
// 		//         {
// 		//             nFlyIndex = 0; 
// 		//         }
// 	}

    //if (GetSelfProfession() == EArmType_Taoist && HQ_TimeGetTime() - LastSummonPetTime >= 10 * 60 * 1000) // 10分钟召唤一次BB
    //{
    //    // 使用技能召唤宝宝
    //    MsgReqSkillAttack SkillMsg;
    //    SkillMsg.bCharTarget = true;
    //    SkillMsg.stWho = GetBotShortId();
    //    SkillMsg.stSkill = 1091; // 召唤BB
    //    SkillMsg.chSkillCount = 1;
    //    SkillMsg.stSkillLevel = 1;
    //    SendMsg(&SkillMsg);
    //    LastSummonPetTime = HQ_TimeGetTime();
    //}
}

//随即移动
void BaseRobot::Move()
{
    //移动
    DWORD dwCostMovingTime = HQ_TimeGetTime() - m_dwStartMovingTime;
    if(dwCostMovingTime < m_nMoveStep)
    {
        return;
    }
    m_dwStartMovingTime = HQ_TimeGetTime();
    
    //随即 设置移动坐标点
    if (m_vMovePos.x == 0 && m_vMovePos.y == 0)
    {
        GetMapName(); //获得地图大小

  //      int nPosX = rand() % (m_nMapWidth - 200) + 100;
  //      int nPosY = rand() % (m_nMapHeight - 200) + 100;
		int nPosX = rand() %m_nMapWidth;
		int nPosY = rand() %m_nMapWidth;
        SetMovePos(nPosX, nPosY);
    }

	if (m_vMovePos.x > m_nMapWidth)
	{
		m_vMovePos.x = 0;
	}
	if (m_vMovePos.y > m_nMapHeight)
	{
		m_vMovePos.y = 0;
	}
	if (m_vMovePos.x == 0 && m_vMovePos.y == 0)
	{
		return;
	}

    m_vDir = m_vMovePos - m_vPos;
    float fDist = D3DXVec3Length( &m_vDir );

    if(fDist <= 1.5) //到了以后清空坐标
    {
        ClearMovePos();

        return;
    }

    D3DXVec3Normalize(&m_vDir, &m_vDir);
    float fMoveDist = m_fMoveSpeed * m_nMoveStep / 1000;

    m_vPos.x += fMoveDist * m_vDir.x;
    m_vPos.y += fMoveDist * m_vDir.y;	

    MsgPlayerMovingPosAndDirToServer xMsg;
    xMsg.header.stID = m_shPlayerId;
    xMsg.vPos.x = m_vPos.x;
    xMsg.vPos.y = m_vPos.y;
    xMsg.vPos.z = 0;
    xMsg.chDirX = (char)(m_vDir.x * 127);
    xMsg.chDirY = (char)(m_vDir.y * 127);
    xMsg.chDirZ = 0;
    xMsg.dwSendTime = HQ_TimeGetTime();
    SendMsg(&xMsg);

    SetTipsInfo("随机移动");  
}

int GetRandChaChannel()
{
	const int channel_max = 30;
	int temp_ = (rand()%30 + 1);
	return 1 << temp_;
}

void BaseRobot::Say(const char *pszChat)
{
	if (m_dwLastTime > HQ_TimeGetTime() || pszChat == NULL)
	{
		return;
	}
	m_dwLastTime = HQ_TimeGetTime() + m_nMoveStep*20;

	////要随即喊话,
	MsgChat msgChat;//(MsgChat::CHAT_TYPE_HIGHSHOUT);
	int nType = MsgChat::CHAT_TYPE_NORMAL;//rand() % MsgChat::CHAT_TYPE_NORMAL;

	switch(nType)
	{
	case MsgChat::CHAT_TYPE_NORMAL:
		msgChat.chatHeader.stType =  MsgChat::CHAT_TYPE_NORMAL;
		break;

	case MsgChat::CHAT_TYPE_HIGHSHOUT:
		msgChat.chatHeader.stType =  MsgChat::CHAT_TYPE_HIGHSHOUT;
		break;
	default:
		return;  //目前就执行普通和世界喊话
	}

	msgChat.SetString(pszChat);
	SendMsg( &msgChat );
}

void BaseRobot::OnMsg_VerifyPos( Msg* pMsg )
{
    MsgVerifyPos* xPosMsg = (MsgVerifyPos*)pMsg;
    if(xPosMsg == NULL)
    {
        return;
    }
    m_cMoveSerial = xPosMsg->cMoveSerial;
    SetPos(xPosMsg->x, xPosMsg->y, 0);
}

int BaseRobot::GetNullItemIndex()
{
    for (int i = 0 ;i<ITEM_BAGMAX;++i)
    {
        if(m_pItemBag[i].itembaseinfo.ustItemID == ErrorUnsignedShortID)
        {
            return i;
        }
    }
    return -1;
}

void BaseRobot::OnMsg_AckLogin( Msg* pMsg )
{ 
    MsgAckLogin* pAck = (MsgAckLogin*)pMsg;
    if( pAck->stErrorCode == MsgAckLogin::ret_succ )
    {
        _accountId = pAck->dwAccountID;
		SessionKey = pAck->SessionKey;
        SetTipsInfo("登陆Login成功");
		m_hasCreateRole = false;
    }
    else
    {
        SetTipsInfo("登陆Login失败");
        //Close();

        m_vLastProTime[GetBotState()].StartTimer( HQ_TimeGetTime(), 300000); //5分钟以后重登
    }
}


void BaseRobot::OnMsg_LoginWait( Msg* pMsg )
{
	MsgLoginWait * ack=(MsgLoginWait *)pMsg;
	{
		if(ack->getcharacter)
		{
			SetTipsInfo("GameID分配成功，拿角色列表");
		}
		else 
		{
			SetTipsInfo("GameID分配失败,重连");
		}
	}
}

void BaseRobot::OnMsg_InquireInvitee( Msg* pMsg )
{
    MsgInquireInvitee * pMsgInquireInvitee = (MsgInquireInvitee *)pMsg;
    MsgAckInquireInvitee msg;
    msg.bAgree = TRUE;
    msg.dwReqID = pMsgInquireInvitee->dwReqID;
    msg.header.stID = m_shPlayerId;
    msg.AssignMode = pMsgInquireInvitee->AssignMode;
    SendMsg(&msg);
}

void BaseRobot::OnMsg_Chat( Msg* pMsg )
{    
    MsgChat* chat = (MsgChat*)pMsg;
    
#ifdef HIDE_BOT_INFO
    //do nothing
#else  //记录系统和聊天信息
    //系统信息

    //聊天信息
    PushChatMsgInList(pMsg);
#endif
    
    ////////////////////////////////////////////////////////
    if(chat->chatHeader.stType == MsgChat::CHAT_TYPE_PRIVATE)
    {
        MsgChat msgChat(MsgChat::CHAT_TYPE_PRIVATE);
        std::string strBuf(chat->szString);
        strncpy( msgChat.chatHeader.szToName, strBuf.substr(0, strBuf.find("对")).c_str(), MAX_NAME_STRING );

        std::string strBuff = "这是一个三足鼎立的舞台，这里曾经走过一批个性张扬的英雄。";
        msgChat.SetString(strBuff.c_str());
       
        SendMsg( &msgChat );
    }
}

PlayerInfo* BaseRobot::RandPlayer()
{
    if (m_listPlayerList.empty())
        return NULL;

    int ranNum = rand()%m_listPlayerList.size();// szName NPCName
    list<PlayerInfo>::iterator itr = m_listPlayerList.begin();
    for (int i = 0;i < ranNum;++i)
    {
        ++itr;
        if (itr == m_listPlayerList.end())
        {
            return NULL;
        }
    }
    //itr += ranNum;
    if (itr != m_listPlayerList.end())
    {
        return &(*itr);
    }
    return NULL;
}

void BaseRobot::OnMsg_PlayerEnterSight( Msg* pMsg )
{
    MsgPlayerEnterMySight* pEnter = (MsgPlayerEnterMySight*)pMsg;
    if(pEnter)
    {
        switch (pEnter->stCharType)
        {
        case Object_Player:
            {
                if(GetPlayer(pEnter->header.stID) == NULL)
                {
                    PlayerInfo info;
                    info.dwCharacterID = pEnter->dwPlayerCharacterID;
                    info.shPlayerID = pEnter->header.stID;
                    info.shCharType = pEnter->stCharType;
                    info.nHP = pEnter->nHp;
                    info.m_vPos.x = pEnter->fX;
                    info.m_vPos.y = pEnter->fY;
                    info.influence = pEnter->influence;
                    m_listPlayerList.push_back(info);

                    //随机请求
                    RandReqCharInfo(pEnter->header.stID);        
                }
            }
            break;
        case Object_Npc:
            {
//                 NpcInfo::Npc* Npcinfo = theNpcInfo.GetNpcByStaticId(pEnter->);
//                 if (Npcinfo != NULL)
//                 {
//                     strncpy(info.szName, Npcinfo->name.c_str(), dr_MaxPlayerName - 1);
//                     m_listNPCList.push_back(info);
//                 }
            }
            break;
        }
        
    }
}

void BaseRobot::OnMsgItemEnterMySight(Msg* pMsg)
{
    MsgItemEnterMySight* pMsgItemEnterMySight = (MsgItemEnterMySight*)pMsg;
    
    for (int i = 0;i<pMsgItemEnterMySight->nCount;++i)
    {
        if (pMsgItemEnterMySight->dwPickPlayerID[i] == GetBotDBID())
        {
            //CItemDetail::SItemCommon* Item = GettheItemDetail().GetItemByID(pMsgItemEnterMySight->ustItemId);
            if (pMsgItemEnterMySight->ustItemId >=2&&pMsgItemEnterMySight->ustItemId<=4)
            {
                PackageItem item;
                item.PackageId = pMsgItemEnterMySight->ustItemId;
                item.PackageShortId = pMsgItemEnterMySight->header.stID;
                item.FloatX = pMsgItemEnterMySight->fX;
                item.FloatY = pMsgItemEnterMySight->fY;
                m_listPackageList.push_back(item);
                //SetBotState(State_ViewPackage);
                return;
            }
        }
    }
}

bool BaseRobot::OnMsgPickPackageItemAck (Msg* pMsg)
{
    MsgPickPackageItemAck* pick = (MsgPickPackageItemAck*)pMsg;
    return pick->nResult == MsgPickPackageItemAck::Result_Success;
}

void BaseRobot::OnMsg_Ping(Msg* pMsg)
{
    MsgPingMsg* msgPing = (MsgPingMsg*) pMsg;
    DWORD time = HQ_TimeGetTime() - msgPing->dwTime;
    
    PingList.push_back(time);
}

void BaseRobot::OnMsgMoneyChange(Msg *pMsg)
{
    MsgMoneyChange* pMoney = (MsgMoneyChange*)pMsg;
    SetBotMoney(pMoney->dwNumber);
}

DWORD BaseRobot::GetPingTime()
{
    if(PingList.empty())
        return 0;
    DWORD time = *PingList.begin();
    PingList.pop_front();
    return time;
}

bool BaseRobot::IsHaveItem(int ItemId)
{
    if (ItemId<=0)
    {
        return false;
    }

    for (int i = 0;i<ITEM_BAGMAX;++i)
    {
        if (m_pItemBag[i].itembaseinfo.ustItemID == ItemId
            && m_pItemBag[i].itembaseinfo.ustItemCount > 0)
        {
            return true;
        }
    }

    return false;
}

void BaseRobot::OnMsgPackageViewAck( Msg* pMsg )
{
    MsgPackageViewAck* pMsgPackageViewAck = (MsgPackageViewAck*)pMsg;
    if (pMsgPackageViewAck->nItemCount == 0)
        return;

    MsgPickPackageItemReq pick;
    pick.bAllPick = true;
    pick.nItemPackageID = pMsgPackageViewAck->nItemPackageID;
    
    if (ItemNormalBag.GetNullItemCount() < 6)// 小于6个背包格子就清除10个格子
    {
        int clearCount = 0;
        for (int i = ItemNormalBag.GetNowBagSize();i != 0;--i)
        {
            SCharItem item;
            if (ItemNormalBag.GetItem(i,&item))
            {
                MsgDropItem2 dropMsg;
                dropMsg.fX = GetPosX();
                dropMsg.fY = GetPosY();
                dropMsg.ucItemBagType = BT_NormalItemBag;
                dropMsg.ustPackIndex = i;
                SendMsg(&dropMsg);
                if (clearCount++ >= 10)
                {
                    break;
                }
            }
        }
    }

    SendMsg(&pick);
}

bool BaseRobot::MoveToItemPackage(float X,float Y)
{
    // 移动时间间隔
    static DWORD m_MoveSpaceTime = HQ_TimeGetTime() - m_MoveSpaceTime;
    if(m_MoveSpaceTime < m_nMoveStep)
    {
        return false; //时间间隔未到
    }

    D3DXVECTOR3 TargetPos;
    TargetPos.x = X;
    TargetPos.y = Y;
    TargetPos.z = 0;
    m_vDir = TargetPos - m_vPos;
    float fDist = D3DXVec3Length(&m_vDir);
    if (fDist < PICKITEM_DISTANCE)
    {
        return true;
    }

    D3DXVec3Normalize( &m_vDir, &m_vDir );
    float fMoveDist = m_fMoveSpeed * m_nMoveStep / 1000;

    m_vPos.x += fMoveDist * m_vDir.x;
    m_vPos.y += fMoveDist * m_vDir.y;

    MsgPlayerMovingPosAndDirToServer xMsg;
    xMsg.header.stID = m_shPlayerId;
    xMsg.vPos.x = m_vPos.x;
    xMsg.vPos.y = m_vPos.y;
    xMsg.vPos.z = 0;
    xMsg.chDirX = (char)(m_vDir.x * 127);
    xMsg.chDirY = (char)(m_vDir.y * 127);
    xMsg.chDirZ = 0;
    xMsg.dwSendTime = HQ_TimeGetTime();
    SendMsg(&xMsg);

    return false;
}

void BaseRobot::OnMsgPackageitemAccessAck(Msg *pMsg)
{
    PickAcessLevelList.clear();
    MsgPackageitemAccessAck* pMsgPackageitemAccessAck = (MsgPackageitemAccessAck*)pMsg;
    for (int i = 0;i < pMsgPackageitemAccessAck->nCount;++i)
    {
        PickAcessLevelList.push_back(pMsgPackageitemAccessAck->xItemInfo[i]);
    }
}

bool BaseRobot::ViewPackageItem()
{
    if (!IsHavePackage())
    { return true; }

    PackageItem Item = m_listPackageList.front();
    //移动到包裹
    if (MoveToItemPackage(Item.FloatX,Item.FloatY))
    {
        MsgPackageViewReq msg;
        msg.nItemPackageID = Item.PackageShortId;
        m_listPackageList.pop_front();
        SendMsg(&msg);
        return true;
    }
    return false;
}

void BaseRobot::OnMsg_PlayerEnterSightPack( Msg* pMsg )
{ 
    MsgEnterMySightPack* pPack = static_cast<MsgEnterMySightPack*>(pMsg);

    //--------------------统计消息数目--------------------
    ++m_nTotalSightPack;
    m_nTotalSightMsg += pPack->nCharNum;
    ++g_nTotalSightPack;
    g_nTotalSightMsg += pPack->nCharNum;
    //----------------------------------------------------

    static CEnterMySightPackage unpacker;
    unpacker.LoadPackMsg(*pPack);

    while (!unpacker.IsEmpty())
    {
        MsgPlayerEnterMySight* pEnterMySight = unpacker.PopEnterMySight();
        OnMsg_PlayerEnterSight(pEnterMySight);
    }
}

void BaseRobot::OnMsg_UnPlayerEnterSight( Msg* pMsg )
{  
    MsgNPCEnterMySight* pEnter = (MsgNPCEnterMySight*)pMsg;
    if(pEnter)
    {
        
        if(GetMonster(pEnter->header.stID) != NULL ||
           GetNPC(pEnter->header.stID) != NULL)
        {
            return;
        }
        PlayerInfo info;
        info.shPlayerID = pEnter->header.stID;
        info.shCharType = pEnter->stCharType;
        info.shMonsterType = pEnter->stMonsterType;
        info.nHP = pEnter->nHp;
        info.m_vPos.x = pEnter->fX;
        info.m_vPos.y = pEnter->fY;
        info.dwCharacterID = pEnter->stId;

        switch(info.shCharType)
        {
        case Object_Monster:            
            if(info.shMonsterType <= eMT_GodMonster)
            {
                m_listMonsterList.push_back(info);
            }
            else if (info.shMonsterType >= eMT_Herb || info.shMonsterType <= eMT_Wood)
            {
                m_listItemMonsterList.push_back(info);
            }

            break;

        case Object_Npc:
            {
                NpcInfo::Npc targetNpcInfo;
                bool IsFind = false;
                for (NpcInfo::NpcsIter itr = theNpcInfo.npcs_.begin();itr != theNpcInfo.npcs_.end();++itr)
                {
                    if (itr->second.modelId == pEnter->stId)
                    {
                        targetNpcInfo = itr->second;
                        IsFind = true;
                        break;
                    }
                }

                //if (targetNpcInfo != NULL)
                if (IsFind)
                {
                    strncpy(info.szName, targetNpcInfo.name.c_str(), dr_MaxPlayerName - 1);
                    info.dwMapID = targetNpcInfo.mapId;
                    bool findInList = false;
                    for (PlayerInfoContainer::iterator itr = m_listNPCList.begin();itr != m_listNPCList.end();++itr)
                    {
                        if (_stricmp(itr->szName,info.szName) == 0)
                        {
                            findInList = true;
                            break;
                        }
                    }
                    if (!findInList)
                    {
                        m_listNPCList.push_back(info);
                    }
                }
            }
            break;

        default:
            break;
        }
    }
}

void BaseRobot::OnMsg_ExitSight( Msg* pMsg )
{  
    MsgExitMySight* pExit = (MsgExitMySight*)pMsg;
    if(pExit != NULL)
    {
        RemovePlayer(pExit->header.stID);
    }  
}

void BaseRobot::OnMsg_AckCharInfo( Msg* pMsg )
{

	MsgAckCharInfo* pAck = (MsgAckCharInfo*)pMsg;
    if(pAck != NULL)
    {
//         if(pAck->stChar == m_shPlayerId)
//         {                    
//             return;
//         }
        PlayerInfo* pInfo = GetPlayer(pAck->stChar);
        if(pInfo != NULL)
        {
            strncpy(pInfo->szName, pAck->szDisplayName, dr_MaxPlayerName - 1);
        }
        PlayerInfo* pNpcInfo = GetNPC(pAck->stChar);
        if ( NULL != pNpcInfo )
        {

        }
    }
}

void BaseRobot::OnMsgCanControlMoving(Msg *pMsg)
{
    MsgCanControlMoving* pCanMove = (MsgCanControlMoving* )pMsg;
    CanControl = pCanMove->bCanControlMoving;
}

void BaseRobot::OnMsgHitchMoveTargetPos(Msg *pMsg)
{
    MsgHitchMoveTargetPos* HitchMsg = (MsgHitchMoveTargetPos*)pMsg;
    AutoRunPosList.push_back(HitchMsg->vTargetPos);
}

void BaseRobot::OnMsg_UnPlayerClosingToLockTarget( Msg* pMsg )
{
    MsgUnPlayerClosingToLockTarget *pMove = (MsgUnPlayerClosingToLockTarget*)pMsg;

    if(pMove->header.stID != m_shPlayerId)
    {
        PlayerInfo* pInfo = GetMonster(pMove->header.stID);
        if(pInfo != NULL)
        {
            pInfo->m_vPos.x = pMove->vPos.x;
            pInfo->m_vPos.y = pMove->vPos.y;
        }
    }
}

void BaseRobot::OnMsg_PlayerMovingPos(Msg* pMsg)
{
    MsgPlayerMovingPos* pMove = (MsgPlayerMovingPos*)pMsg;

    if(pMove->header.stID != m_shPlayerId)
    {
        PlayerInfo* pInfo = GetPlayer(pMove->header.stID);
        if(pInfo != NULL)
        {
            pInfo->m_vPos.x = pMove->vPos.x;
            pInfo->m_vPos.y = pMove->vPos.y;
        }
    }
}

void BaseRobot::OnMsg_PlayerMovingPosAndDir(Msg* pMsg)
{
    MsgPlayerMovingPosAndDir* pMove = (MsgPlayerMovingPosAndDir*)pMsg;

    if(pMove->header.stID != m_shPlayerId)
    {
        PlayerInfo* pInfo = GetPlayer(pMove->header.stID);
        if(pInfo != NULL)
        {
            pInfo->m_vPos.x = pMove->vPos.x;
            pInfo->m_vPos.y = pMove->vPos.y;
        }
    }
}

void BaseRobot::OnMsg_UnPlayerMovingToPos(Msg* pMsg)
{ 
    MsgUnPlayerMovingToPos *pMove = (MsgUnPlayerMovingToPos*)pMsg;

    if(pMove->header.stID != m_shPlayerId )
    {
        PlayerInfo* pInfo = GetMonster( pMove->header.stID );
        if(pInfo != NULL)
        {
            pInfo->m_vPos.x = pMove->vStartPos.x;
            pInfo->m_vPos.y = pMove->vStartPos.y;
        }
    }
}

void BaseRobot::OnMsg_UnPlayerVerifyPos(Msg* pMsg)
{
    MsgUnPlayerVerifyPos *pMove = (MsgUnPlayerVerifyPos*)pMsg;

    if(pMove->header.stID != m_shPlayerId )
    {
        PlayerInfo* pInfo = GetMonster( pMove->header.stID );
        if(pInfo != NULL)
        {
            pInfo->m_vPos.x = pMove->vPos.x;
            pInfo->m_vPos.y = pMove->vPos.y;
        }
    }    
}

//玩家坐标纠正
void BaseRobot::OnMsg_PlayerVerifyPos(Msg* pMsg)
{
    MsgPlayerVerifyPos *pMove = (MsgPlayerVerifyPos*)pMsg;

    if(pMove->header.stID != m_shPlayerId )
    {
        PlayerInfo* pInfo = GetPlayer( pMove->header.stID );
        if(pInfo != NULL)
        {
            pInfo->m_vPos.x = pMove->vPos.x;
            pInfo->m_vPos.y = pMove->vPos.y;
        }
    }
    else
    {
        m_vPos.x = pMove->vPos.x;
        m_vPos.y = pMove->vPos.y;
    }
}

void BaseRobot::OnMsg_AttrChanged( Msg* pMsg )
{
    MsgCharAttrChanged* pCharAttrChanged = (MsgCharAttrChanged*)pMsg;

    if (m_shPlayerId != pMsg->header.stID)
    {
        return;
    }

    DWORD dwValue = 0;
    float fValue = 0.0;
    short stValue = 0;
    int nValue = 0;
    for (int n = 0; n < pCharAttrChanged->iChangeCount; ++n)
    {
        dwValue = pCharAttrChanged->pAttrChanged[n].data.dwValue;
        fValue = pCharAttrChanged->pAttrChanged[n].data.fValue;
        stValue = pCharAttrChanged->pAttrChanged[n].data.stValue;
        nValue = pCharAttrChanged->pAttrChanged[n].data.nValue;
        switch (pCharAttrChanged->pAttrChanged[n].ustWhichAttr)
        {
        //case CharAttr_SkillPoint:
        //    {
        //        m_CharInfo.baseinfo.liveinfo.dwSkillExpNotUsed = stValue;
        //    }
        //    break;
        case CharAttr_HP:
            {
                m_CharInfo.baseinfo.liveinfo.nHp = nValue;
            }
            break;
        case CharAttr_HPMax:
            {
                m_CharInfo.baseinfo.baseProperty.fightAttr.hpMax.final = stValue;
            }
            break;
        case CharAttr_MPMax:
            {
                m_CharInfo.baseinfo.baseProperty.fightAttr.mpMax.final = stValue;
            }
            break;
        case CharAttr_MP:
            {
                m_CharInfo.baseinfo.liveinfo.nMp = nValue;
            }
            break;
        case CharAttr_Relive:
            {
                MsgMapLoaded msgMapLoaded;
                msgMapLoaded.header.stID = m_shPlayerId;
                SendMsg( &msgMapLoaded );
            }
            break;
        default:
            break;
        }
    }
}

void BaseRobot::OnMsgSeeAttack3( Msg* pMsg )
{
    MsgSeeAttack3 *pSee3 = (MsgSeeAttack3 *)pMsg;

    if (/*pSee3->target.stID == GetBotShortId() && */(pSee3->ustSkillID == 1002|| pSee3->ustSkillID == 1003 ||
        pSee3->ustSkillID == 1004|| pSee3->ustSkillID == 1007|| pSee3->ustSkillID == 1020))
    {
        if( m_LastSeeAttactTime == 0)
        {
            m_LastSeeAttactTime = HQ_TimeGetTime();
        }
        else
        {

            if ( HQ_TimeGetTime() - m_LastSeeAttactTime <= 800 ) // 收到MsgSeeAttack3消息时间间隔少于800毫秒
            {
                DWORD tiem = HQ_TimeGetTime() - m_LastSeeAttactTime;
                char szTime[30];
                sprintf_s(szTime,sizeof(szTime),"szTime = %d\n",tiem);
                TRACE(szTime);
                LOG_MESSAGE(LogObject,LOG_PRIORITY_ERROR,"收到MsgSeeAttack3消息时间间隔少于800毫秒");
            }
            m_LastSeeAttactTime = HQ_TimeGetTime();
        }
    }
    if( pSee3->stResultNum <= 0 )
    {
        return;
    }

    if ( pSee3->stResultNum > 0 )
    {
        if( m_shPlayerId == pSee3->header.stID )
        {
            m_CharInfo.baseinfo.liveinfo.nHp = pSee3->results[0].nSrcHp;
        }

        for( int i = 0; i < pSee3->stResultNum; ++i )
        {
            if( m_shPlayerId == pSee3->results[i].stTargetWho )
            {
                m_CharInfo.baseinfo.liveinfo.nHp = pSee3->results[i].nTagHp;
                std::vector<short>::iterator itr = find(KillMeTarget.begin(),KillMeTarget.end(),pSee3->results[i].stAttackerWho);
                if (itr == KillMeTarget.end())
                {
                    PlayerInfo* pPlayer = GetMonster(pSee3->results[i].stTargetWho);
                    if (NULL != pPlayer)
                    {
                        KillMeTarget.push_back(pSee3->results[i].stAttackerWho);
                    }
                    else
                    {
                        MsgQueryCharInfo query;
                        query.stChar = pSee3->results[i].stTargetWho;
                        SendMsg(&query);      
                    }
                }
                continue;
            }

            PlayerInfo* pPlayer = GetPlayer(pSee3->results[i].stTargetWho);
            if(pPlayer != NULL)
            {
                pPlayer->nHP = pSee3->results[i].nTagHp;
                if( _HAS_FLAG( pSee3->results[i].nStatusFlag, eFIGHT_BEKILLED ) )
                {
                    RemovePlayer(pPlayer->shPlayerID);
                }
            }
        }
    }
}

void BaseRobot::OnMsg_PosChange( Msg* pMsg )
{
    MsgPosChange* pMsgPack = (MsgPosChange*)pMsg;

    //--------------------统计消息数目--------------------
    ++m_nTotalPosPack;
    m_nTotalPosMsg += ((MsgPosChange*)pMsg)->nCharNum;
    ++g_nTotalPosPack;
    g_nTotalPosMsg += ((MsgPosChange*)pMsg)->nCharNum;
    //----------------------------------------------------

    g_PosMsgProcess.LoadPackMsg(*pMsgPack);

    SPosChangeInfo* pPosInfo = g_PosMsgProcess.PopPosChangeInfo();
    while(pPosInfo != NULL)
    {    
        switch(pPosInfo->nType)
        {
        case CPosChangePackage::PACK_MSG_PLAYERMOVINGPOS:
        case CPosChangePackage::PACK_MSG_PLAYERMOVINGPOSANDDIR:
            {            
                if (pPosInfo->nID == m_shPlayerId)
                {                    
                    m_vPos.x = pPosInfo->vPos.x;
                    m_vPos.y = pPosInfo->vPos.y;
                    break;
                }

                PlayerInfo* pInfo = GetPlayer(pPosInfo->nID);
                if(pInfo != NULL)
                {
                    pInfo->m_vPos.x = pPosInfo->vPos.x;
                    pInfo->m_vPos.y = pPosInfo->vPos.y;
                }
                break;
            }
        case CPosChangePackage::PACK_MSG_UNPLAYERCLOSINGTOLOCKTARGET:
        case CPosChangePackage::PACK_MSG_UNPLAYERMOVINGTOPOS:
        case CPosChangePackage::PACK_MSG_UNPLAYERVERIFYPOS:
            {
                PlayerInfo* pInfo = GetMonster(pPosInfo->nID);
                if(pInfo != NULL)
                {
                    pInfo->m_vPos.x = pPosInfo->vPos.x;
                    pInfo->m_vPos.y = pPosInfo->vPos.y;
                }
                break;
            }
        }

        pPosInfo = g_PosMsgProcess.PopPosChangeInfo();
    }
}


void BaseRobot::OnMsg_AllNpcInTheMap(Msg* pMsg)
{
    MsgAllNpcOnTheMap* NpcMapInfo = (MsgAllNpcOnTheMap*)pMsg;

    //LOG_MESSAGE(LogObject, LOG_PRIORITY_INFO, "Npc Total Count = %d In Map = %d", NpcMapInfo->wNpcCount, GetMapID());

}

void BaseRobot::OnMsg_TellMap_NpcQuest(Msg* pMsg)
{
    MsgTellMapNpcQuest* pQuestMsg = (MsgTellMapNpcQuest*)pMsg;

    // 只要找到自己要接的任务状态就可以了
    //for(int i = 0; i < pQuestMsg->byQuestCount; ++i)
    //{
    //    LOG_MESSAGE(LogObject, LOG_PRIORITY_INFO, "Npc Id = %d, Quest Id = %d, Quest State = %d", 
    //        pQuestMsg->infos[i].stNpcId, pQuestMsg->infos[i].stQuestId, pQuestMsg->infos[i].chState);
    //}
}

void BaseRobot::OnMsg_SawSomeOnDead( Msg* pMsg )
{ 
    MsgSawSomeoneDead* pDead = (MsgSawSomeoneDead*)pMsg;

    if(m_shPlayerId != pDead->header.stID)
    {
        RemovePlayer(pDead->header.stID);
    }
}

void BaseRobot::SetPos(float x, float y, float z)
{
    m_vPos.x = x;
    m_vPos.y = y;
    m_vPos.z = z;
}

bool BaseRobot::CheckTime(unsigned int nMax, bool bSpace/* = false*/, bool bClose/* = true*/)
{
    GameTimerEx& timer = m_vLastProTime[GetBotState()];
    if( !timer.IsStart())
    {
        m_bSpaceCheck = bSpace;
        m_bClose = bClose;
        timer.StartTimer( HQ_TimeGetTime(), nMax * 1000 );
        return true;
    }
    else
    {
        if(g_nDisableCheckTime == 0 || m_bSpaceCheck)
        {
            if( timer.DoneTimer() )
            {
                //if (m_bClose)   //是否要断开连接
                //{ Close(); }

                if (m_bSpaceCheck)
                { LOG_MESSAGE(LogObject, LOG_PRIORITY_INFO, "CheckTime Robot = %s, State = %d", m_szBotName, GetBotState()); }
                return true;
            }
        }
    }
    return false;
}

PlayerInfo* BaseRobot::GetMonster(GameObjectId shID)
{        
    //edit by lori 2009-5-25
    PlayerInfoContainer::iterator iter = find(m_listMonsterList.begin(), m_listMonsterList.end(), shID);
    if (iter != m_listMonsterList.end())
    {
        return &(*iter);
    }
    std::vector<short>::iterator itr = find(KillMeTarget.begin(),KillMeTarget.end(),shID);
    if (itr != KillMeTarget.end())
    {
        KillMeTarget.erase(itr);
    }

    return NULL;
}

PlayerInfo* BaseRobot::GetNPCByName(const std::string& Name)
{
    if (Name.empty())
    {
        return NULL;
    }

    for ( PlayerInfoContainer::iterator iter = m_listNPCList.begin();iter!= m_listNPCList.end();++iter )
    {
        if (Name.compare(iter->szName) == 0)
        {
            return &(*iter);
        }
        else if (strlen(iter->szName)==0)
        {
            MsgQueryCharInfo queryinfo;
            queryinfo.stChar = iter->shPlayerID;
            SendMsg(&queryinfo);
        }
    }
    return NULL;
}

PlayerInfo* BaseRobot::GetNPC(GameObjectId shID)
{
    //edit by lori 2009-5-25    
    PlayerInfoContainer::iterator iter = find(m_listNPCList.begin(), m_listNPCList.end(), shID);
    if (iter != m_listNPCList.end())
    {
        return &(*iter);
    }

    return NULL;
}

PlayerInfo* BaseRobot::GetPlayer(GameObjectId shID)
{
    //edit by lori 2009-5-25
    PlayerInfoContainer::iterator iter = find(m_listPlayerList.begin(), m_listPlayerList.end(), shID);
    if (iter != m_listPlayerList.end())
    {
        return &(*iter);
    }

    std::vector<short>::iterator itr = find(KillMeTarget.begin(),KillMeTarget.end(),shID);
    if (itr != KillMeTarget.end())
    {
        KillMeTarget.erase(itr);
    }
    return NULL;
}

PlayerInfo* BaseRobot::GetPlayerByName(const std::string &TargetName)
{
    if (TargetName.empty())
    {
        return NULL;
    }

    for (PlayerInfoContainer::iterator itr = m_listPlayerList.begin();itr != m_listPlayerList.end();++itr)
    {
        if (TargetName.compare(itr->szName) == 0)
        {
            return &(*itr);
        }
        else if (strlen(itr->szName)==0)
        {
            MsgQueryCharInfo queryinfo;
            queryinfo.stChar = itr->shPlayerID;
            SendMsg(&queryinfo);
        }

    }
    
    return NULL;
}

// void CBot::CheckPlayer()
// {
//     for (PlayerInfoContainer::iterator itr = m_listPlayerList.begin();itr != m_listPlayerList.end();++itr)
//     {
//         if (strlen(itr->szName) == 0)
//         {
//             MsgQueryCharInfo
//             SendMsg()
//         }
//     }
// }

short BaseRobot::GetWhoKillMe()
{
    if (KillMeTarget.empty())
    {
        return -1;
    }
    return KillMeTarget.front();
}

void BaseRobot::RemovePlayer(GameObjectId shID)
{
    list<PlayerInfo>::iterator itr;    
    //edit by lori 2009-5-25
    //Monster
    itr = find(m_listMonsterList.begin(), m_listMonsterList.end(), shID);
    if (itr != m_listMonsterList.end())
    {
        m_listMonsterList.erase(itr);
    }
    std::vector<short> ::iterator KillItr = find(KillMeTarget.begin(), KillMeTarget.end(), shID);
    if (KillItr != KillMeTarget.end())
    {
        KillMeTarget.erase(KillItr);
    }
    // 道具
    itr = find(m_listItemMonsterList.begin(), m_listItemMonsterList.end(), shID);
    if (itr != m_listItemMonsterList.end())
    {
        m_listItemMonsterList.erase(itr);
    }
    //NPC
    itr = find(m_listNPCList.begin(), m_listNPCList.end(), shID);
    if (itr != m_listNPCList.end())
    {
        m_listNPCList.erase(itr);
    }

    //Player
    itr = find(m_listPlayerList.begin(), m_listPlayerList.end(), shID);
    if (itr != m_listPlayerList.end())
    {
        m_listPlayerList.erase(itr);
    }
}

int BaseRobot::GetPlayerNum()
{  
    return m_listPlayerList.size();
}

int BaseRobot::GetNPCNum()
{
    return m_listNPCList.size();
}

int BaseRobot::GetMonsterNum()
{
    return m_listMonsterList.size();
}

//请求装备
void BaseRobot::ReqGetItem(int nPackPos)
{  
    MsgChat msg( MsgChat::CHAT_TYPE_NORMAL );
    strncpy( msg.chatHeader.szToName, m_CharInfo.baseinfo.aptotic.szCharacterName , MAX_NAME_STRING - 1 );


    char szMsg[dr_MaxChatString - 1] = {0};
    std::string command = ROBOT_REQUEST_COMMAND;
    command += "GetItem %d";
    _snprintf( szMsg, dr_MaxChatString - 1, command.c_str(), nPackPos );

    msg.SetString(szMsg);
    SendMsg( &msg );
}

void BaseRobot::ReqGetItem(int nItemID, int nCount, int nFlag)
{
    if (nItemID < 0) { return; }

    MsgChat msg( MsgChat::CHAT_TYPE_NORMAL );
    strncpy( msg.chatHeader.szToName, m_CharInfo.baseinfo.aptotic.szCharacterName , MAX_NAME_STRING - 1 );

    char szMsg[dr_MaxChatString - 1] = {0};
    std::string command = "";
    command += "/CreateItem %d %d %d";
    _snprintf( szMsg, dr_MaxChatString - 1, command.c_str(), nItemID, nCount, nFlag);

    msg.SetString(szMsg);
    SendMsg( &msg );
}

void BaseRobot::EquipItem(int nItemID, int nPackIndex)
{
    if (nItemID < 0 || nPackIndex < 0) { return; }

    CItemDetail::SItemWeapon *pItem = (CItemDetail::SItemWeapon*) GettheItemDetail().GetItemByID(nItemID); // ? 可能是Armour

    if (pItem != NULL)
    {                
        for (int j = 0; j < EEquipPartType_MaxEquitPart; ++j)
        {
            if (pItem->arrayCanEquip[j] == 1) //判断是否可以装备上去
            {
                MsgEquip msg;
                msg.ustPackIndex = nPackIndex;
                SendMsg( &msg );

                break;
            }
        }                                    
    }    
}

void BaseRobot::AddHp()
{
    MsgChat msg( MsgChat::CHAT_TYPE_NORMAL );
    strncpy( msg.chatHeader.szToName, m_CharInfo.baseinfo.aptotic.szCharacterName , MAX_NAME_STRING - 1 );

    std::string command = ROBOT_REQUEST_COMMAND;
    command += "AddHp";

    msg.SetString(command.c_str());
    SendMsg( &msg );
}

void BaseRobot::ReqLvlUp(int nLvl)
{   
    MsgChat msg( MsgChat::CHAT_TYPE_NORMAL );
    strncpy( msg.chatHeader.szToName, m_CharInfo.baseinfo.aptotic.szCharacterName , MAX_NAME_STRING - 1 );

    char szMsg[dr_MaxChatString - 1] = {0};
    std::string command = ROBOT_REQUEST_COMMAND;
    command += "LvlUp %d";
    _snprintf( szMsg, dr_MaxChatString - 1, command.c_str(), nLvl );

    msg.SetString(szMsg);
    SendMsg( &msg );

    m_CharInfo.baseinfo.liveinfo.ustLevel = nLvl;
}

void BaseRobot::FlyToMap(short shMap, short shAreaX, short shAreaY)
{
//      if (theBotDataCenter.BotFlyLimit <= -1 || theApp.LoadFileMappingNum() <= theBotDataCenter.BotFlyLimit)    
//      {
//          return;
//      }

    if (shMap < 0) { return; }

    MsgChat msg( MsgChat::CHAT_TYPE_NORMAL );
    strncpy( msg.chatHeader.szToName, m_CharInfo.baseinfo.aptotic.szCharacterName , MAX_NAME_STRING - 1 );

    char szMsg[dr_MaxChatString - 1] = {0};

    std::string command = ROBOT_REQUEST_COMMAND;
    command += "FlyToMap %d %d %d";
    _snprintf( szMsg, dr_MaxChatString - 1, command.c_str(), shMap, shAreaX, shAreaY);

    msg.SetString(szMsg);
    SendMsg( &msg );
}

void BaseRobot::LearnAllSkill()
{
    MsgChat msg( MsgChat::CHAT_TYPE_NORMAL );
    strncpy( msg.chatHeader.szToName, m_CharInfo.baseinfo.aptotic.szCharacterName , MAX_NAME_STRING - 1 );

    char szMsg[dr_MaxChatString - 1] = {0};

    std::string command = ROBOT_REQUEST_COMMAND;
    command += "LearnAllSkill";
    _snprintf( szMsg, dr_MaxChatString - 1, "%s", command.c_str());

    msg.SetString(szMsg);
    SendMsg( &msg );
}

void BaseRobot::ReqItem(unsigned int ItemId, unsigned int nCount, unsigned int nType)
{
    char szChatItem[255];
    ZeroMemory(szChatItem,sizeof(szChatItem));
    sprintf_s(szChatItem,sizeof(szChatItem)-1,"/CreateItem %d %d %d", ItemId, nCount, nType);
    MsgChat ItemChat(MsgChat::CHAT_TYPE_NORMAL);
    ItemChat.SetString(szChatItem);
    SendMsg(&ItemChat);
}

void BaseRobot::UseItem(unsigned int ItemId,EBagType type,short targetType,short TargetId)
{
#define Self (0)
    MsgUseGoods UseItem;
    UseItem.nRemainValue = 0;
    UseItem.stDstChar = targetType == Self?GetBotShortId():TargetId;
    UseItem.stSrcChar = GetBotShortId();
    UseItem.stItemCount = 1;
    UseItem.ucItemBagType = type;
    UseItem.ustItemIndex = ItemId;//pGet->item.itembaseinfo.stPacketIdx;
    SendMsg(&UseItem);
}

void BaseRobot::OnMsg_GetItem( Msg* pMsg )
{
    MsgGetItem2* pGet = (MsgGetItem2*)pMsg;

    if (pGet->item.itembaseinfo.ustItemID == const_ustItemMoney)
    {
        SetBotMoney(GetBotMoney()+pGet->item.itembaseinfo.value1);
        return;
    }

    CItemDetail::SItemCommon* pComm = GettheItemDetail().GetItemByID(pGet->item.itembaseinfo.ustItemID);
    ASSERT(pComm != NULL);
    if (NULL == pComm)
    {
        return;
    }

    if(pGet->enResult == MsgGetItem2::RESULT_SUCCESS)
    {
        switch (pComm->ucItemType)
        {
        case CItemDetail::ITEMTYPE_MATERIAL:
            {
                if (m_pMaterialBag[pGet->item.itembaseinfo.stPacketIdx].itembaseinfo.ustItemID != ErrorUnsignedShortID 
                    && m_pMaterialBag[pGet->item.itembaseinfo.stPacketIdx].itembaseinfo.ustItemID == pGet->item.itembaseinfo.ustItemID)
                {
                    m_pMaterialBag[pGet->item.itembaseinfo.stPacketIdx].itembaseinfo.nOnlyInt = pGet->item.itembaseinfo.nOnlyInt;
                    m_pMaterialBag[pGet->item.itembaseinfo.stPacketIdx].itembaseinfo.ustItemCount += 1;
                    return;
                }
                memcpy(&m_pMaterialBag[pGet->item.itembaseinfo.stPacketIdx], &pGet->item, sizeof(SCharItem));
                return;
//                 for(int i = 0; i < ITEM_BAGMATERIAL_MAX; ++i)
//                 {
//                     if(m_pMaterialBag[i].itembaseinfo.ustItemID == ErrorUnsignedShortID && pGet->item.itembaseinfo.stPacketIdx == i)
//                     {
//                         memcpy(&m_pMaterialBag[i], &pGet->item, sizeof(SCharItem));
//                         return;
//                     }
//                 }
            }
            break;
        case CItemDetail::ITEMTYPE_TASK:
            {
                if (m_pTaskItemBag[pGet->item.itembaseinfo.stPacketIdx].itembaseinfo.ustItemID != ErrorUnsignedShortID 
                    && m_pTaskItemBag[pGet->item.itembaseinfo.stPacketIdx].itembaseinfo.ustItemID == pGet->item.itembaseinfo.ustItemID)
                {
                    m_pTaskItemBag[pGet->item.itembaseinfo.stPacketIdx].itembaseinfo.nOnlyInt = pGet->item.itembaseinfo.nOnlyInt;
                    m_pTaskItemBag[pGet->item.itembaseinfo.stPacketIdx].itembaseinfo.ustItemCount += 1;
                    return;
                }
                memcpy(&m_pTaskItemBag[pGet->item.itembaseinfo.stPacketIdx], &pGet->item, sizeof(SCharItem));
                return;
//                 for(int i = 0; i < ITEM_BAGTASK_MAX; ++i)
//                 {
//                     if(m_pTaskItemBag[i].itembaseinfo.ustItemID == ErrorUnsignedShortID && pGet->item.itembaseinfo.stPacketIdx == i)
//                     {
//                         memcpy(&m_pTaskItemBag[i], &pGet->item, sizeof(SCharItem));
//                         return;
//                     }
//                 }
            }
            break;
        default:
            {
                if (m_pItemBag[pGet->item.itembaseinfo.stPacketIdx].itembaseinfo.ustItemID != ErrorUnsignedShortID 
                    && m_pItemBag[pGet->item.itembaseinfo.stPacketIdx].itembaseinfo.ustItemID == pGet->item.itembaseinfo.ustItemID)
                {
                    m_pItemBag[pGet->item.itembaseinfo.stPacketIdx].itembaseinfo.nOnlyInt = pGet->item.itembaseinfo.nOnlyInt;
                    m_pItemBag[pGet->item.itembaseinfo.stPacketIdx].itembaseinfo.ustItemCount += 1;
                    return;
                }
                memcpy(&m_pItemBag[pGet->item.itembaseinfo.stPacketIdx], &pGet->item, sizeof(SCharItem));
                //ItemNormalBag.PushItem(pGet->item,pGet->item.itembaseinfo.ustItemCount);
                if (NULL != pComm && 
                    (
                    pComm->ucItemType == CItemDetail::ITEMTYPE_WEAPON ||
                    pComm->ucItemType == CItemDetail::ITEMTYPE_ARMOUR
                    )
                    )
                {
                    //装备物品
                    EquipItem(pGet->item.itembaseinfo.ustItemID, pGet->item.itembaseinfo.stPacketIdx);
                }
                if (NULL != pComm && pComm->ucItemType == CItemDetail::ITEMTYPE_RESTORE )
                {
                    if (m_CharInfo.baseinfo.liveinfo.nMp <= 80 )
                    {
                        MsgUseGoods UseItem;
                        UseItem.nRemainValue = 0;
                        UseItem.stDstChar = GetBotShortId();
                        UseItem.stSrcChar = GetBotShortId();
                        UseItem.stItemCount = 1;
                        UseItem.ucItemBagType = BT_NormalItemBag;
                        UseItem.ustItemIndex = pGet->item.itembaseinfo.stPacketIdx;
                    }
                }
                return;
//                 for(int i = 0; i < ITEM_BAGMAX; ++i)
//                 {
//                     if(m_pItemBag[i].itembaseinfo.ustItemID == ErrorUnsignedShortID && pGet->item.itembaseinfo.stPacketIdx == i)
//                     {
//                         memcpy(&m_pItemBag[i], &pGet->item, sizeof(SCharItem));
//                         CItemDetail::SItemCommon* pItemComm = GettheItemDetail().GetItemByID( pGet->item.itembaseinfo.ustItemID );
//                         if (NULL != pItemComm && 
//                             (
//                             pItemComm->ucItemType == CItemDetail::ITEMTYPE_WEAPON ||
//                             pItemComm->ucItemType == CItemDetail::ITEMTYPE_ARMOUR
//                             )
//                             )
//                         {
//                             //装备物品
//                             EquipItem(pGet->item.itembaseinfo.ustItemID, i);
//                         }
//                         return;
//                     }
//                 }
            }
            break;
        }
        
    }
}

void BaseRobot::OnMsg_QueryBargaining( Msg* pMsg )
{/*
MsgQueryBargaining* pQuery = (MsgQueryBargaining*)pMsg;
switch( pQuery->enType )
{
case TYPE_QUERY_BARGAINING: //请求交易
   {
       MsgAckBargaining msg;
       msg.stTargetID = pQuery->stTargetID;
       msg.enType = TYPE_ACK_BARGAINING;
       msg.enResult = MsgAckBargaining::ACK_SUCCESSORAGREE;
       SendMsg( &msg );
       break;
   }
case TYPE_BEGIN_BARGAINING: //开始交易
   {
       //SetBotState(State_Exchange);
       SetTipsInfo("交易中");
       //for(int i=10;i<15;i++)
       //{
       //    MsgBargainingNow msg;
       //    msg.bGetDown = false;
       //    msg.item = m_pItemBag[i];
       //    msg.nIndex = i;
       //    SendMsg( &msg );
       //}
       //MsgQueryBargaining query;
       //query.enType = TYPE_AGREE_COMPLETION_FIRST;
       //SendMsg( &query );
       break;
   }
case TYPE_AGREE_COMPLETION_FIRST:
   {
       MsgAckBargaining ack;
       ack.enType = TYPE_AGREE_COMPLETION_LAST;
       SendMsg( &ack ); 
       break;
   }
case TYPE_CANCEL_BARGAINING:
   {
       SetBotState(State_Play);
       break;
   }
}*/
}

void BaseRobot::OnMsg_AckBargaining( Msg* pMsg )
{
    //MsgAckBargaining* pQuery = (MsgAckBargaining*)pMsg;
    //switch( pQuery->enType )
    //{
    //case TYPE_AGREE_COMPLETION_LAST:
    //    {
    //        SetBotState(State_Play);
    //        break;
    //    }
    //}
}

//返回切换装备
void BaseRobot::OnMsgChangeEquip(Msg* pMsg)
{
    MsgAckEquip *pAck = (MsgAckEquip*) pMsg;
    if (pAck->ustWhere < 0 || pAck->ustWhere >= EEquipPartType_MaxEquitPart)
    {
        return;
    }

    if (pAck->ustPackIndex < 0 || pAck->ustPackIndex >= ITEM_BAGMAX)
    {
        return;
    }
    
    memcpy(&m_CharInfo.visual.equipitem[pAck->ustWhere], &m_pItemBag[pAck->ustPackIndex], sizeof(SCharItem));
    
    m_pItemBag[pAck->ustPackIndex].itembaseinfo.ustItemID = ErrorUnsignedShortID;
    m_pItemBag[pAck->ustPackIndex].itembaseinfo.nOnlyInt = 0;
	m_dwReEquipItemTime = HQ_TimeGetTime();	
}

void BaseRobot::OnMsgDropItem(Msg* pMsg)
{
    MsgAckDropItem2* pAck = (MsgAckDropItem2*) pMsg;

    if (pAck < 0 || pAck->ustPackIndex >= ITEM_BAGMAX)
    {
        return;
    }

    m_pItemBag[pAck->ustPackIndex].itembaseinfo.ustItemID = ErrorUnsignedShortID;
    m_pItemBag[pAck->ustPackIndex].itembaseinfo.ustItemCount = 0;
}

void BaseRobot::OnMsgLevelUp(Msg *pMsg)
{
    MsgCharacterLevelup* pAck = (MsgCharacterLevelup*) pMsg;

    //m_CharInfo.baseinfo.liveinfo.ustLevel = pAck->ustNewLevel;
}

void BaseRobot::OnMsgChangePKFlag(Msg *pMsg)
{
    MsgAckChangePKFlag *pAck = (MsgAckChangePKFlag*) pMsg;


}

void BaseRobot::OnMsgExit(Msg *pMsg)
{
    MsgExit* pExit = (MsgExit*) pMsg;
    if (pExit->header.stID == m_shPlayerId)
    {
        SetTipsInfo("退出游戏");
    }
}

void BaseRobot::OnMsgInviteeTeam(Msg* pMsg)
{
    MsgInquireInvitee* pInviteeMsg = (MsgInquireInvitee*) pMsg;

    MsgAckInquireInvitee xAck;

    xAck.header.stID = m_shPlayerId;
    xAck.bAgree = true;
    xAck.dwReqID = pInviteeMsg->dwReqID;
    strncpy(xAck.name, GetBotRoleName(), sizeof(xAck.name) - 1);
    xAck.AssignMode = pInviteeMsg->AssignMode;

    SendMsg(&xAck);
}

///////////////////////////////////////////////////////////////////

void BaseRobot::OnDisconnectFromServer()
{
	int nState = GetBotState();
	SetTipsInfo("服务器主动断开");
}

///////////////////////////////////
void BaseRobot::PushChatMsgInList(Msg *pMsg)
{
    static char* s_pszChat[] = 
    {
        "【普通】", "【公会】", "【队伍】", "【结义】", "【世界】",
    };

    MsgChat* pChat = (MsgChat*) pMsg;

    string strChat = "";
    if(pChat->chatHeader.stType == MsgChat::CHAT_TYPE_NORMAL)
    {
        strChat = s_pszChat[0];
    }
    else if (pChat->chatHeader.stType == MsgChat::CHAT_TYPE_GUILD)
    {
        strChat = s_pszChat[1];
    }
    else if (pChat->chatHeader.stType == MsgChat::CHAT_TYPE_TERM)
    {
        strChat = s_pszChat[2];
    }
    else if (pChat->chatHeader.stType == MsgChat::CHAT_TYPE_LEAGUE)
    {
        strChat = s_pszChat[3];
    }
    else if (pChat->chatHeader.stType == MsgChat::CHAT_TYPE_HIGHSHOUT)
    {
        strChat = s_pszChat[4];
    }
    else
    {
        return;
    }

    strChat += pChat->szString;
    
    m_listChatMsg.push_front(strChat);

    if (m_listChatMsg.size() > 50)
    {
        m_listChatMsg.pop_back();
    }
}

string BaseRobot::PopChatMsgFormList()
{
    if (m_listChatMsg.empty())
    {
        return "";
    }

    int nSize = m_listChatMsg.size();
    string strChat = m_listChatMsg.back();
    m_listChatMsg.pop_back();

    nSize = m_listChatMsg.size();
    return strChat;
}

const char* BaseRobot::GetMapName()
{
    //地图
    if (GetBotState() != State_Play)
    {
        m_nMapID = -1;
        m_strMap.clear();
        return "N/A";
    }

    if (m_nMapID != GetMapID())
    {
        m_nMapID = GetMapID();
        MapConfig::MapData* pMapData = theMapConfig.GetMapDataById( m_nMapID );
        if (pMapData == NULL)
        {
            m_strMap.clear();
            m_nMapWidth = 0;
            m_nMapHeight = 0;
            return "ErrorID";
        }

        m_strMap     = pMapData->MapName;
        m_nMapWidth  = pMapData->Row * CHUNK_SIZE;
        m_nMapHeight = pMapData->Column * CHUNK_SIZE;
    }

    return m_strMap.c_str();
}

void BaseRobot::ReqCharInfo(GameObjectId shID)
{
    MsgQueryCharInfo query;
    query.stChar = shID;
    SendMsg(&query); 
    ++m_nReqCharInfoCount;
}
//////////////////////////////////
void BaseRobot::RandReqCharInfo(GameObjectId shID)
{
    /////战斗机器人都要请求
    if (m_pSetInfo == NULL || m_pSetInfo->nRequestStart == 0)
    {
        return;
    }

    if (m_dwReqCharInfoTime < HQ_TimeGetTime())        
    {
        m_nReqCharInfoCount = 0;    //超过时间 统计数量清零
        m_dwReqCharInfoTime = HQ_TimeGetTime() + m_pSetInfo->nRequestSecond * 1000;
    }

    if (m_nReqCharInfoCount >= m_pSetInfo->nRequestCount)
    {
        return;
    }

//    int nReq = rand() % 2;
//     if (nReq == 0)
//     {
//         return;            //0 不请求
//     }

    ++m_nReqCharInfoCount;

    MsgQueryCharInfo query;
    query.stChar = shID;
    SendMsg(&query); 
}


/////////////////////////////////////////////////////////////
void BaseRobot::StatMsgInfo(int nType,Msg* pMsg)
{
    if (pMsg == NULL)
    {
        return;
    }

	MsgStatistician::Msg_Info_ xMsgInfo;
	xMsgInfo.dwType = pMsg->GetType();
	xMsgInfo.dwCount = 1;
	xMsgInfo.dwSize = pMsg->GetLength();

	switch(nType)
	{
	case Msg_Send:        
	   m_xMsgStatistician.SetCurrentSendInfo(1, pMsg->GetLength(), xMsgInfo);    //统计当前机器人        
	   theApp.m_xTatolMsgStatistician.SetCurrentSendInfo(1, pMsg->GetLength(), xMsgInfo);    //统计所有机器人
	   break;

	case Msg_Recv:        
	   m_xMsgStatistician.SetCurrentRecvInfo(1, pMsg->GetLength(), xMsgInfo);    //统计当前机器人        
	   theApp.m_xTatolMsgStatistician.SetCurrentRecvInfo(1, pMsg->GetLength(), xMsgInfo);    //统计所有机器人
	   break;

	default:
	   break;
	}
}

void BaseRobot::OnMsgConnectGateOverTime(Msg* pMsg)
{
    //MsgConnectGateOverTime* msg = static_cast<MsgConnectGateOverTime*>(pMsg);
    //if (_accountId == msg->accountId)
    //{
    //    LOG_MESSAGE(LogObject,LOG_PRIORITY_ERROR,"Account [%d] MsgConnectGateOverTime SessionKey = %s",msg->accountId,msg->szSessionKey);
    //    SetBotState(State_End);
    //    //Close();
    //}
}

// void _LoginProcessThread(void* lParam)
// {
//     BaseRobot* pBot = (BaseRobot*) lParam;
//     if ( theBotDataCenter.GetBotNet() == 0 )
//     {
//         pBot->AsynGLSLoginLan(); // 内网登录方式
//     }
//     else if ( theBotDataCenter.GetBotNet() == 1 )
//     {
//         pBot->AsynGLSLoginWan(); // 外网登录方式
//     }
//     
// }

// void BaseRobot::OnMsgMapInfoReady(Msg* pMsg)
// {
//     MsgMapInfoReady* pMsgResult = (MsgMapInfoReady*)pMsg;
//     if (m_bEnterWorldSuccess)
//     {
//         SetBotState(State_Play);
//         UpdateBotState();
//         m_bLoadMapOver = true;
//         m_WaitUpdateSightTime = 0;
// #if _LOGININFO_
//         LOG_MESSAGE(LogObject,LOG_PRIORITY_DEBUG,"Recv MsgMapInfoReady In %s",__FUNCTION__);
// #endif
//     }
// }

void BaseRobot::UpdateBotState()
{
    if (GetBotState() == State_Play)
    {
        SetTipsInfo("游戏中..");
    }
}

//  bool CBot::AStarMove(int map,float x,float y)
//  {
//      if (!theApp.LoadBinAStarOver)
//      {
//          return false;
//      }
//      theApp.Mo
//      MoveToPoint
//  }

bool BaseRobot::Move2Point(D3DXVECTOR3& xPos ,float Distance_Error)
{
    DWORD dwSpaceTime = HQ_TimeGetTime() - m_dwMoveSpaceTime;
    if(dwSpaceTime < m_nMoveStep)
    {
        return false; //时间间隔未到
    }
    m_dwMoveSpaceTime = HQ_TimeGetTime();

    bool AutoRun = false;
    if (!CanControl)
    {
        AutoRun = true;
        if (!AutoRunPosList.empty())
        {
            xPos = AutoRunPosList.front();
        }
        else
        {
            return false;
        }
    }
    float x = GetPosX();
    float y = GetPosY();
    if (abs(xPos.x - x ) <= Distance_Error && abs(xPos.y - y ) <= Distance_Error)
    {
        return true;
    }
//     m_vDir = xPos - m_vPos;
//     float fDist = D3DXVec3Length(&m_vDir);
// 
//     if(fDist < Distance_Error)
//     {
//         if (AutoRun || !AutoRunPosList.empty())
//         {
//             AutoRunPosList.pop_front();
//         }
// 
//         m_dwMoveSpaceTime = 0;
//         //到了设置开始攻击时间
//         return true;
//     }

    D3DXVec3Normalize( &m_vDir, &m_vDir );
    float fMoveDist = m_fMoveSpeed * m_nMoveStep / 1000;

    m_vPos.x += fMoveDist * m_vDir.x;
    m_vPos.y += fMoveDist * m_vDir.y;

    MsgPlayerMovingPosAndDirToServer xMsg;
    xMsg.header.stID = m_shPlayerId;
    xMsg.vPos.x = m_vPos.x;
    xMsg.vPos.y = m_vPos.y;
    xMsg.vPos.z = 0;
    xMsg.chDirX = (char)(m_vDir.x * 127);
    xMsg.chDirY = (char)(m_vDir.y * 127);
    xMsg.chDirZ = 0;
    xMsg.dwSendTime = HQ_TimeGetTime();
    SendMsg(&xMsg);

    SetTipsInfo("向怪物移动");

    return false;
}

bool BaseRobot::MoveToPoint(D3DXVECTOR3& xPos ,float Distance_Error)
{
    DWORD dwSpaceTime = HQ_TimeGetTime() - m_dwMoveSpaceTime;
    if(dwSpaceTime < m_nMoveStep)
    {
        return false; //时间间隔未到
    }
    m_dwMoveSpaceTime = HQ_TimeGetTime();

    bool AutoRun = false;
    if (!CanControl)
    {
        AutoRun = true;
        if (!AutoRunPosList.empty())
        {
            xPos = AutoRunPosList.front();
        }
        else
        {
            return false;
        }
    }
    m_vDir = xPos - m_vPos;
    float fDist = D3DXVec3Length(&m_vDir);

    if(fDist < Distance_Error)
    {
        if (AutoRun || !AutoRunPosList.empty())
        {
            AutoRunPosList.pop_front();
        }
        
        m_dwMoveSpaceTime = 0;//到了设置开始攻击时间

        if (fDist < Distance_Error && fDist > 0.5)
        {
            D3DXVec3Normalize( &m_vDir, &m_vDir );

//             m_vPos.x += xPos.x;
//             m_vPos.y += xPos.y;
            MsgPlayerMovingPosToServer xMsg;
            xMsg.header.stID = m_shPlayerId;
            xMsg.vPos.x = xPos.x;
            xMsg.vPos.y = xPos.y;
            xMsg.vPos.z = 0;
            xMsg.dwSendTime = HQ_TimeGetTime();
            SendMsg(&xMsg);
            m_vPos.x = xPos.x;
            m_vPos.y = xPos.y;
        }
        return true;
    }

    D3DXVec3Normalize( &m_vDir, &m_vDir );

    float fMoveDist;
    fMoveDist = m_fMoveSpeed * m_nMoveStep / 1000;

    m_vPos.x += fMoveDist * m_vDir.x;
    m_vPos.y += fMoveDist * m_vDir.y;

    MsgPlayerMovingPosAndDirToServer xMsg;
    xMsg.header.stID = m_shPlayerId;
    xMsg.vPos.x = m_vPos.x;
    xMsg.vPos.y = m_vPos.y;
    xMsg.vPos.z = 0;
    xMsg.chDirX = (char)(m_vDir.x * 127);
    xMsg.chDirY = (char)(m_vDir.y * 127);
    xMsg.chDirZ = 0;
    xMsg.dwSendTime = HQ_TimeGetTime();
    SendMsg(&xMsg);
    SetTipsInfo("向怪物移动");

    return false;
}

void BaseRobot::LoadRandFlyMap()
{
    if (vecMap.empty())
    {
        int nCount = theMapConfig.MapDataCount();
        //for (int i = 0; i < nCount; ++i)
        {
            vecMap.push_back(0);    // 
            vecMap.push_back(1);    // 
            vecMap.push_back(2);    // 
            vecMap.push_back(3);    // 
            vecMap.push_back(4);    // 
            vecMap.push_back(7);    // 
            vecMap.push_back(8);    // 
            vecMap.push_back(9);    // 
            vecMap.push_back(10);   // 
            vecMap.push_back(11);   // 
            vecMap.push_back(12);   // 
//             MapConfig::MapData *pMapData = theMapConfig.GetMapDataByIndex(i);
//             if (pMapData == NULL) { continue; }
//             if (!pMapData->IsEctypeMap() && !pMapData->MapName.empty()&&(pMapData->Id != YOUQUANDIYU_MAPID || pMapData->Id != YOUQUANDIYU_ECTYPE_MAPID))
//             {
//                 vecMap.push_back(pMapData->Id);
//             }
        }
        nMapCount = vecMap.size();
    }
}

void BaseRobot::RandFly()
{
    if (vecMap.empty())
    {
        LoadRandFlyMap();
    }
    static int nIndex = 0;
    int nPos = (rand() % (40 * (int)CHUNK_SIZE - 200)) + 50;
    if (nIndex >= nMapCount)
    {
        nIndex = 0; 
    }

    if (GetMapID() != vecMap[nIndex])
    {
        FlyToMap(vecMap[nIndex], nPos, nPos);
        SetSleep(3000);
    }

    ++nIndex;
    
    // 设置发送成功
    m_bFlyMap = true;
}

//void BaseRobot::SetBotPrivateShopBag(SPrivateShopItemInfo * Item,int Idex )
//{
//    if (Item == NULL)
//        return;
//    if (Idex >=ITEM_PRIVATE_SHOP_BAGMAX || Idex<0)
//        return;
//
//    memcpy_s(&m_CharInfo.otherdataclient.stPrivateShopItem[Idex],sizeof(SPrivateShopItemInfo),Item,sizeof(SPrivateShopItemInfo));
//}

//SPrivateShopItemInfo* BaseRobot::GetPrivateShopBag(int Idex)
//{
//    if (Idex >=ITEM_PRIVATE_SHOP_BAGMAX || Idex<0)
//        return NULL;
//
//    return &m_CharInfo.otherdataclient.stPrivateShopItem[Idex];
//}

//bool BaseRobot::IsPrivateShopBagEmpty()
//{
//    for (int i = 0;i < ITEM_PRIVATE_SHOP_BAGMAX;++i)
//    {
//        if (m_CharInfo.otherdataclient.stPrivateShopItem[i].nOnlyInt > 0)
//        {
//            return false;
//        }
//    }
//    return true;
//}

void BaseRobot::OnMsgMoveGoods(Msg* pMsg)
{
    MsgMoveGoods* pMoveGoods = (MsgMoveGoods*)pMsg;
    if (pMoveGoods->ustDstIndex == ITEM_DISTORY)
    {
        if (pMoveGoods->ustSrcIndex == ITEM_DISTORY)
        {
            return;
        }
        switch( pMoveGoods->ucItemBagType)
        {
        case BT_NormalItemBag:
            m_pItemBag[pMoveGoods->ustSrcIndex].itembaseinfo.ustItemID = ErrorUnsignedShortID;
            m_pItemBag[pMoveGoods->ustSrcIndex].itembaseinfo.ustItemCount = 0;
            m_pItemBag[pMoveGoods->ustSrcIndex].itembaseinfo.nOnlyInt = 0;
            break;
        case BT_MaterialBag:
            m_pMaterialBag[pMoveGoods->ustSrcIndex].itembaseinfo.ustItemID = ErrorUnsignedShortID;
            m_pMaterialBag[pMoveGoods->ustSrcIndex].itembaseinfo.nOnlyInt = 0;
            m_pMaterialBag[pMoveGoods->ustSrcIndex].itembaseinfo.ustItemCount = 0;
            break;
        case BT_TaskBag:
            m_pTaskItemBag[pMoveGoods->ustSrcIndex].itembaseinfo.ustItemID = ErrorUnsignedShortID;
            m_pTaskItemBag[pMoveGoods->ustSrcIndex].itembaseinfo.nOnlyInt = 0;
            m_pTaskItemBag[pMoveGoods->ustSrcIndex].itembaseinfo.ustItemCount = 0;
            break;
        default:
            break;
        }
        return;
    }

    switch( pMoveGoods->ucItemBagType)
    {
    case BT_NormalItemBag:
        {
            SCharItem TempRes;
            memcpy_s(&TempRes ,sizeof(SCharItem), &m_pItemBag[pMoveGoods->ustDstIndex],sizeof(SCharItem));
            memcpy_s(&m_pItemBag[pMoveGoods->ustDstIndex],sizeof(SCharItem),&m_pItemBag[pMoveGoods->ustSrcIndex],sizeof(SCharItem));
            memcpy_s(&m_pItemBag[pMoveGoods->ustSrcIndex],sizeof(SCharItem),&TempRes,sizeof(SCharItem));
        }
        break;
    case BT_MaterialBag:
        {
            SCharItem TempRes;
            memcpy_s(&TempRes ,sizeof(SCharItem), &m_pMaterialBag[pMoveGoods->ustDstIndex],sizeof(SCharItem));
            memcpy_s(&m_pMaterialBag[pMoveGoods->ustDstIndex],sizeof(SCharItem),&m_pMaterialBag[pMoveGoods->ustSrcIndex],sizeof(SCharItem));
            memcpy_s(&m_pMaterialBag[pMoveGoods->ustSrcIndex],sizeof(SCharItem),&TempRes,sizeof(SCharItem));
        }
        break;
    case BT_TaskBag:
        {
            SCharItem TempRes;
            memcpy_s(&TempRes ,sizeof(SCharItem), &m_pTaskItemBag[pMoveGoods->ustDstIndex],sizeof(SCharItem));
            memcpy_s(&m_pTaskItemBag[pMoveGoods->ustDstIndex],sizeof(SCharItem),&m_pTaskItemBag[pMoveGoods->ustSrcIndex],sizeof(SCharItem));
            memcpy_s(&m_pTaskItemBag[pMoveGoods->ustSrcIndex],sizeof(SCharItem),&TempRes,sizeof(SCharItem));
        }
        break;
    default:
        break;
    }
}

void BaseRobot::ClearNormalBagItem()
{
    // 清理背包
    for(int i = 0;i<= DefaultBagNum ;++i)
    {
        if (NULL != m_pItemBag && m_pItemBag[i].itembaseinfo.ustItemID != ErrorUnsignedShortID)
        {
            MsgMoveGoods msg;
            msg.ustSrcIndex = i;//m_pItemBag[i].itembaseinfo.stPacketIdx;
            msg.ustDstIndex = ITEM_DISTORY;
            msg.ustCount = m_pItemBag[i].itembaseinfo.ustItemCount;
            msg.ucItemBagType = BT_NormalItemBag;
            SendMsg(&msg);
            //Sleep(1000);
        }
    }
}

void BaseRobot::ClearMaterialBagItem()
{
    // 清理背包
    for(int i = 0;i<= DefaultBagNum;++i)
    {
        if (NULL != m_pMaterialBag && m_pMaterialBag[i].itembaseinfo.ustItemID != ErrorUnsignedShortID)
        {
            MsgMoveGoods msg;
            msg.ustSrcIndex = i;//m_pItemBag[i].itembaseinfo.stPacketIdx;
            msg.ustDstIndex = ITEM_DISTORY;
            msg.ustCount = m_pItemBag[i].itembaseinfo.ustItemCount;
            msg.ucItemBagType = BT_MaterialBag;
            SendMsg(&msg);
            //Sleep(1000);
        }
    }
}

bool BaseRobot::IsMaterialBagFull()
{
    int count = 0;
    for (int i = 0;i < ITEM_BAGMATERIAL_MAX ;++i)
    {
        if (m_pMaterialBag[i].itembaseinfo.ustItemID != ErrorUnsignedShortID)
        {
            ++count;
        }
    }
    if (count > 18)
    {
        return true;
    }
    return false;
}

bool BaseRobot::IsNormalBagFull()
{
    int count = 0;
    for (int i = 0;i < ITEM_PRIVATE_SHOP_BAGMAX - 5;++i)
    {
        if (m_pItemBag[i].itembaseinfo.ustItemID != ErrorUnsignedShortID)
        {
            ++count;
        }
    }
    if (count > 18)
    {
        return true;
    }
    return false;
}

bool BaseRobot::IsPrivateShopBagFull()
{
    //int count = 0;
    //for (int i = 0;i < ITEM_PRIVATE_SHOP_BAGMAX;++i)
    //{
    //    if (m_CharInfo.otherdataclient.stPrivateShopItem[i].nOnlyInt > 0)
    //    {
    //        ++count;
    //    }
    //}
    //if (count != ITEM_PRIVATE_SHOP_BAGMAX)
    //{
    //    return false;
    //}
    return true;
}

void BaseRobot::SetSleep(DWORD Time)
{
    dw_SleepTime = Time;
    dw_SleepCurTime = HQ_TimeGetTime();
}

void BaseRobot::OnMsgAckFriendList(Msg* pMsg)
{
    //MsgAckFriendList* pMsgAckFriendList = (MsgAckFriendList*)pMsg;
    //for (int i = 0;i < pMsgAckFriendList->ustCount;++i)
    //{
    //    ItrRelation itr = Relations.find(pMsgAckFriendList->xDataToClient[i].GetPlayerID());
    //    if(itr == Relations.end())
    //    {
    //        Relations.insert(RelationList::value_type(pMsgAckFriendList->xDataToClient[i].GetPlayerID(),pMsgAckFriendList->xDataToClient[i]));
    //    }
    //}
}

void BaseRobot::OnMsgAckDelFriend(Msg* pMsg)
{
    //MsgAckDelFriend* pMsgAckDelFriend = (MsgAckDelFriend*)pMsg;
    //if (pMsgAckDelFriend->nResult == MsgAckDelFriend::ECD_Success)
    //{
    //    ItrRelation itr = Relations.find(pMsgAckDelFriend->nFriendID);
    //    if (itr!=Relations.end())
    //    {
    //        itr->second.RemoveRelation(pMsgAckDelFriend->stRelation);
    //        if ( !itr->second.IsHaveRelation() )
    //        {
    //            Relations.erase(itr);
    //        }
    //    }
    //}
    //else if (pMsgAckDelFriend->nResult == MsgAckDelFriend::ECD_NotHaveThisRelation)
    //{
    //    ItrRelation itr = Relations.find(pMsgAckDelFriend->nFriendID);
    //    if (itr!=Relations.end())
    //    {
    //        Relations.erase(itr);
    //    }
    //}

}

void BaseRobot::OnMsgInviteAddRelationReq(Msg* pMsg)
{
// MsgInviteAddRelationReq* pMsgInviteAddRelationReq = (MsgInviteAddRelationReq*)pMsg;
// 
// MsgInviteAddRelationAck ackMsg;
// ackMsg.bAgree = rand()%2 == 1?true:false;
// ackMsg.dwReqID = pMsgInviteAddRelationReq->dwReqID;
// ackMsg.stRelation = pMsgInviteAddRelationReq->stRelation;
// strncpy_s(ackMsg.szAckName,sizeof(ackMsg.szAckName),GetBotRoleName(),sizeof(ackMsg.szAckName)-1);
// SendMsg(&ackMsg);
// SetSleep(2000);
}

void BaseRobot::OnMsgAckAddFriend(Msg* pMsg)
{
    //MsgAckAddFriend* pMsgAckAddFriend = (MsgAckAddFriend*)pMsg;
    //if (pMsgAckAddFriend->nResult == MsgAckAddFriend::succeed)
    //{
    //    ItrRelation itr = Relations.find(pMsgAckAddFriend->xRelationData.GetPlayerID());
    //    if (itr == Relations.end())
    //    {
    //        Relations.insert(RelationList::value_type(pMsgAckAddFriend->xRelationData.GetPlayerID(),pMsgAckAddFriend->xRelationData));
    //    }
    //}
}

void BaseRobot::OnMsgUseSkillHintMessage(Msg *pMsg)
{
#define BarginItemNum   (20)
    MsgUseSkillHintMessage *pSkillMsg = (MsgUseSkillHintMessage*)pMsg;
    switch (pSkillMsg->shHintId)
    {
    case MsgUseSkillHintMessage::eNoEnoughWeaponToUseSkill:
        {
            for (int i = 0;i <= BarginItemNum;++i)
            {
                if (m_pItemBag[i].itembaseinfo.ustItemID != ErrorUnsignedShortID)
                {
                    CItemDetail::SItemCommon* pItem = GettheItemDetail().GetItemByID(m_pItemBag[i].itembaseinfo.ustItemID);
                    if (NULL != pItem && pItem->ucItemType == CItemDetail::ITEMTYPE_WEAPON)
                    {
                        MsgEquip xMsg;
                        xMsg.ustPackIndex = i;

                        SendMsg(&xMsg);
                        SetSleep(2000);
                        return;
                    }
                }
            }
        }
        break;
    }
}

void  BaseRobot::ReqBotMoney(unsigned long Money)
{
#define NoMoney (0)
    if ( Money == NoMoney )
    {
        return;
    }
    char ChatBuf[dr_MaxPath];
    memset(ChatBuf,0,sizeof(ChatBuf));
    sprintf_s(ChatBuf,sizeof(ChatBuf),"/Self AddMoney %d",Money);
    MsgChat ReqMsg;
    ReqMsg.SetString(ChatBuf);
    SendMsg(&ReqMsg);
}

bool BaseRobot::IsInArea(int nMap, D3DXVECTOR3& xPos)
{
    if (m_xAreaInfo.nMap == -1 || m_xAreaInfo.nRadius == 0)
    {    
        return true;
    }

    if (nMap != m_xAreaInfo.nMap)
    {        
        return false;
    }

    float fPosX = xPos.x - m_xAreaInfo.xPoint.x;
    float fPosY = xPos.y - m_xAreaInfo.xPoint.y;

    int nRadius = sqrtf(fPosX * fPosX + fPosY * fPosY);

    return (nRadius <= m_xAreaInfo.nRadius);    
}

void BaseRobot::MoveToArea()
{
    DWORD dwCostMovingTime = HQ_TimeGetTime() - m_dwStartMovingTime;
    if(dwCostMovingTime < m_nMoveStep)
    {
        return;
    }
    m_dwStartMovingTime = HQ_TimeGetTime();


    if (GetMapID() != m_xAreaInfo.nMap)
    {
        //计算一个随即坐标
        int nPosX = 0;
        int nPosY = 0;

        int nRadius = rand() % (m_xAreaInfo.nRadius);

        int nSelect1 = rand() % 2;
        int nSelect2 = rand() % 2;

        int nWidth = 0;
        int nHeight = 0;

        MapConfig::MapData* pMapData = theMapConfig.GetMapDataById(m_xAreaInfo.nMap);
        if (pMapData != NULL)
        {    
            nWidth = pMapData->Row * CHUNK_SIZE;
            nHeight = pMapData->Column * CHUNK_SIZE;
        }
        else
        {        
            return;
        }

        //X 坐标
        if (nSelect1 == 0)
        {
            nPosX = m_xAreaInfo.xPoint.x + nRadius;
            if (nPosX >= nWidth)
            {
                nPosX = nWidth - 50;
            }
        }
        else
        {
            nPosX = m_xAreaInfo.xPoint.x - nRadius;
            if (nPosX <= 0)
            {
                nPosX = 50;
            }
        }

        //Y 坐标
        if (nSelect2 == 0)
        {
            nPosY = m_xAreaInfo.xPoint.y + nRadius;
            if (nPosY >= nHeight)
            {
                nPosY = nHeight - 50;
            }
        }
        else
        {
            nPosY = m_xAreaInfo.xPoint.y - nRadius;
            if (nPosY <= 0)
            {
                nPosY = 50;
            }
        }

        SetTipsInfo("切换地图");
        FlyToMap(m_xAreaInfo.nMap, nPosX, nPosY);
    }
    else
    {
        D3DXVECTOR3 xPos;
        xPos.x = m_xAreaInfo.xPoint.x;
        xPos.y = m_xAreaInfo.xPoint.y;
        xPos.z = 0;

        MoveToPoint(xPos);

        ClearMovePos();
    }
}

void BaseRobot::OnMsgAckResult(Msg* pMsg)
{
    if (NULL == pMsg)
    {
        return;
    }
    MsgAckResult* pMsgResult = (MsgAckResult*)pMsg;
    
    if (pMsgResult->result != ER_Success)
    {
        switch (pMsgResult->result)
        {
        case ER_EnterWorldQueue:
            {
				isEnterWorldQueue = true;
				dwEnterWorldQueueStartTime = HQ_TimeGetTime();
				//
                char buf[256] = {0};
                sprintf_s(buf,sizeof(buf),"排队...%d",pMsgResult->value);
                SetTipsInfo(buf);
                m_bFlyMap = false;
                m_vLastProTime[GetBotState()].StopTimer();
                SetSleep(100);
            }
            return;
        case ER_EnterWorldInColdDown:
            {
                SetSleep(3000);
                dw_EnterWorldTime = 0;//HQ_TimeGetTime() + 3000;
                SetTipsInfo("重新进入");
         //       m_bEnterWorldSuccess = false;
                m_bFlyMap = false;
            }
            return;
        case ER_ErrorTargetMapGameServerId:
        case ER_CorrectMapGameServerNotExist:
        case ER_GameServerNotExist:
            {
                //LoadRandFlyMap();
                //RandFly();
            }
            return;
        case ER_SessionKeyOverTime:
        case ER_CharacterServerNotExit:
        case ER_CharacterServerCantBeGameServer:
        case ER_EnterWorldSwitchStageTypeError:
        case ER_EnterWorldDbSqlException:
        case ER_MapGameServerPlayerIsFull:
            {
                // 失败
                CheckTime(180,true);
                LOG_MESSAGE(LogObject,LOG_PRIORITY_INFO,"机器人[%d] 请求登录失败 ，返回的结果[%d]",GetBotID(),pMsgResult->result);
                //Close();
            }
            return;
        case ER_InFightNotActiveMount:
        case ER_InDeadNotActiveMount:
        case ER_IndexOutOfRange:
        case ER_NullPointer:
        case ER_InMountConfigNotExist:
        case ER_Failed:
        case ER_MountTakeLevelNotEnough:
        case ER_NotEnoughEnjoyment:
            return;
        default:
            LOG_MESSAGE(LogObject,LOG_PRIORITY_INFO,"机器人[%d] 收到 MsgAckResult，返回的结果[%d]",GetBotID(),pMsgResult->result);
            return;
//            Close();
        };
        //SetTipsInfo("ResultError");
        //Close();
    }
}

void BaseRobot::SetBotState( uint8 nState ) 
{   
    _lastState = _currentState;
    _currentState = nState;
    //m_vLastProTime.clear();
    //m_vLastProTime.resize(State_End);
    if (nState == e_state_no_confirm)
    {
   //     m_bEnterWorldSuccess = false;
        m_bLoadMapOver = false;
    }
}

//1. get_glsid
//1208   该用户没激活
//2. login
//1200   glsid不存在 
//1201   glsid过期
//1202   glsid错误
//1203   用户名或密码错误
//1205   用户已经在online表(重复登录)
//1207   该用户被block
//3. query_user_status
//1202   glsid错误
//1204   用户不在online表
// bool BaseRobot::AsynGLSLoginLan()
// {
// 	SetTipsInfo("try连接GLS");
// 
// 	//XmlRpcClient client( GetGLSIP(), GetGLSPort(), "/");
// 	XmlRpcClient client( GetGLSIP(), GetGLSPort(), "/gls");
// 
//     XmlRpcClientGuard clientGuard( &client );
// 
// 	XmlRpcValue args;
// 
// 	args[0] = GetAccount();
// 	args[1] = "";
// 
// 	XmlRpcValue result;
// 	// 打印GLS IP Port
// 	std::string strGlsIp = GetGLSIP();
// 	uint32 nGlsPort = GetGLSPort();
// 	LOG_MESSAGE( LogObject, LOG_PRIORITY_INFO, "Current IP[%s] Port[%d]", strGlsIp.c_str(), nGlsPort );
// 
// 	if (!client.execute("get_glsid", args, result))
// 	{
// 		SetLoginErrorCode( 9000 ); //Error calling 'get_glsid'        
// 		SetBotState(State_End);
// 		SetTipsInfo("get_glsid fail");
// 		std::string Result = result;
// 		LOG_MESSAGE( LogObject, LOG_PRIORITY_ERROR, "XmlRpcValue get_glsid Error! Result = %s, Code=9000",Result.c_str());
// 		//client.close();
// 		return false;
// 	}
// 	//client.close();
// 
// 	std::string glsid = result["glsid"];
// 	std::string password( GetPassword());
// 
// 	SHA1 sha1;
// 	sha1.Reset();
// 	sha1 << password.c_str();
// 
// 	unsigned digest[5];
// 	if (!sha1.Result(digest))
// 	{
// 		SetLoginErrorCode(9001); //Error calling 'sha1.Result'
// 		SetBotState(State_End);
// 		SetTipsInfo("sha1 fail");
// 		LOG_MESSAGE( LogObject, LOG_PRIORITY_ERROR,"sha1 Result Error!");
// 		return false; 
// 	}
// 
// 	std::stringstream sstrSha1;
// 	std::ios::fmtflags flags = sstrSha1.setf(std::ios::hex, std::ios::basefield);
// 
// 	for (int i = 0; i < 5; ++i)
// 	{
// 		sstrSha1.width(8);
// 		sstrSha1.fill('0');
// 		sstrSha1 << digest[i];
// 	}
// 
// 	sstrSha1.setf(flags);
// 
// 	std::stringstream sstr;
// 	sstr << glsid;
// 	sstr << sstrSha1.str();
// 
// 	MD5 md5(sstr.str());
// 	std::string md5Result = md5.toString();
// 
// 	// execute login
// 	args.clear();
// 	result.clear();
// 
// 	args[0] = GetAccount();
// 	args[1] = glsid;
// 	args[2] = md5Result;
// 	if (!client.execute("login", args, result))
// 	{
// 		SetLoginErrorCode(9002); //Error calling 'login'
// 		SetBotState(State_End);
// 		SetTipsInfo("login fail");
// 		LOG_MESSAGE( LogObject, LOG_PRIORITY_ERROR, "XmlRpcClient Login Error faultCode = %d!", 9002);
// 		//client.close();
// 		return false;
// 	}
// 	//client.close();
// 
// 	if (result.hasMember("faultCode"))
// 	{
// 		int nError = result["faultCode"];
// 		SetLoginErrorCode(nError);
// 		SetBotState(State_End);
// 		SetTipsInfo("login faultCode fail");
// 		LOG_MESSAGE( LogObject, LOG_PRIORITY_ERROR,"XmlRpcClient Login Result HasMember faultCode = %d!",nError);
// 		return false;
// 	}
// 
// 	int guid = result["guid"];
// 
// 	args.clear();
// 	result.clear();
// 
// 	args[0] = guid;
// 	args[1] = glsid;
// 
// 	SetTipsInfo("通过验证");
// 
// 	int nLoopCount = 0;
// 	while ( true )
// 	{
// 		if (!client.execute("query_user_status", args, result))
// 		{
// 			SetLoginErrorCode(9002); //Error calling 'query_user_status'
// 			SetBotState(State_End);
// 			SetTipsInfo("query_user_status fail");
// 			LOG_MESSAGE( LogObject, LOG_PRIORITY_ERROR, "XmlRpcClient query_user_status Error faultCode = %d!", 9002);
// 			//client.close();
// 			return false;
// 		}
// 		//client.close();
// 
// 		if (result.hasMember("faultCode"))
// 		{
// 			int nError = result["faultCode"];
// 			SetLoginErrorCode(nError);
// 			SetBotState(State_End);
// 			SetTipsInfo("query_user_status faultCode fail");
// 			LOG_MESSAGE(LogObject,LOG_PRIORITY_ERROR,"XmlRpcClient query_user_status Result HasMember faultCode = %d!", nError);
// 			return false; 
// 		}
// 
// 		int status = result["status"];
// 		if (status == 3)
// 		{
// 			std::string msg = result["msg"];
// 			std::string key;
// 			std::string ip;
// 			int port;
// 
// 			size_t p = msg.find(',') + 1;
// 			size_t p2 = msg.find(',', p);
// 
// 			key = msg.substr(0, p - 1);
// 			ip = msg.substr(p, p2 - p);
// 			port = atoi(msg.substr(p2 + 1).c_str());
// 
// 			InitConnect(ip.c_str(),port);
// 			//SetServerIp(ip.c_str());
// 			//SetServerPort(port);
// 
// 			MD5 md5Key(key + sstrSha1.str());
// 
// 			_accountId = guid;
// 			m_strSessionKey =  md5Key.toString();
// 
// 			SetBotState(State_EnterCharacterS);
// 			break;
// 		}
// 
// 		++nLoopCount;
// 
// 		if (nLoopCount > LOOPQUERYMAXNUM)
// 		{
// 			SetBotState(State_End);
// 			SetTipsInfo("query_user_status overtime");
// 			//Close();
// 			break;
// 		}
// 		Sleep( 500 );
// 	}
// 
// 	return true;
// }

// bool BaseRobot::GetGlsId( const char* szAccount, std::string& glsid)
// {
//     if ( szAccount == NULL || szAccount[0] == '\0')
//     { return false;}
// 
//     try
//     {
//         XmlRpcValue args;
//         XmlRpcClient c(GetGLSIP(), GetGLSPort(), "/gls");
//         XmlRpcClientGuard clientGuard( &c );
// 
//         args[0] = szAccount;
//         args[1] = "";
//         args[2] = ApplicationConfig::Instance().GetFullVersion();
//         XmlRpcValue result;
//         LOG_MESSAGE( LogObject, LOG_PRIORITY_INFO, "Excute [get_glsid_version] [%s:%d] ...", GetGLSIP(), GetGLSPort());
//         if ( !c.execute("get_glsid_version", args, result) )
//         {
//             LOG_MESSAGE( LogObject, LOG_PRIORITY_ERROR, "Excute [get_glsid_version] error");
// 			//c.close();
//             return false;
//         }
// 		// 关闭连接
// 		//c.close();
// 
//         if ( result.hasMember("faultCodefaultCode") )
//         {
//             int err = result["faultCode"];
//             LOG_MESSAGE( LogObject, LOG_PRIORITY_ERROR, "Excute [get_glsid_version] error code [%d]", err);
//             return false;
//         }
// 
//         glsid = result["glsid"];
//     }
//     catch (const XmlRpcException& e)
//     {
//         LOG_MESSAGE(LogObject, LOG_PRIORITY_ERROR, "GLS Login Exception [%s]", e.getMessage().c_str());
//     }
//     return true;
// }
// 
// bool BaseRobot::GetPwdMd5( const char* szPwd, const std::string& glsid, std::string& md5Result, std::stringstream& sstrMd5)
// {
//     if ( szPwd == NULL || szPwd[0] == '\0' )
//     { return false;}
// 
//     try
//     {
//         std::string password(szPwd);
//         MD5 md5pass( password.c_str() );
//         sstrMd5<<md5pass.toString();
//         // md5( glsid + md5( password ) )
//         std::stringstream sstr;
//         sstr << glsid;
//         sstr << md5pass.toString();
// 
//         MD5 md5(sstr.str());
//         md5Result = md5.toString();
//     }
//     catch (const XmlRpcException& e)
//     {
//     	LOG_MESSAGE(LogObject, LOG_PRIORITY_ERROR, "GLS Login MD5 Exception [%s]", e.getMessage().c_str());
//     }
//     return true;
// }
// 
// bool BaseRobot::GetPwdSha1( const char* szPwd, const std::string& glsid, std::string& md5Result, std::stringstream& sstrSha1)   // 老的MD5登录方式
// {
//     if ( szPwd == NULL || szPwd[0] == '\0' )
//     { return false;}
// 
//     try
//     {
//         std::string password(szPwd);
//         SHA1 sha1;
//         sha1.Reset();
//         sha1<<password.c_str();
//         unsigned digest[5];
//         if ( !sha1.Result(digest) )
//         {
//             LOG_MESSAGE(LogObject, LOG_PRIORITY_ERROR, "SHA1 Result Error!");
//             return false;
//         }
// 
//         std::ios::fmtflags flags = sstrSha1.setf(std::ios::hex, std::ios::basefield);
//         for (int i=0; i<5; ++i)
//         {
//             sstrSha1.width(8);
//             sstrSha1.fill('0');
//             sstrSha1<<digest[i];
//         }
// 
//         sstrSha1.setf(flags);
// 
//         std::stringstream sstr;
//         sstr<<glsid;
//         sstr<<sstrSha1.str();
// 
//         MD5 md5(sstr.str());
//         md5Result = md5.toString();
//     }
//     catch (const XmlRpcException& e)
//     {
//         LOG_MESSAGE(LogObject, LOG_PRIORITY_ERROR, "GLS Login MD5 Exception [%s]", e.getMessage().c_str());
//     }
//     return true;
// }

// bool BaseRobot::AsynGLSLoginWan()       // 外网登录
// {
//     SetTipsInfo("try连接GLS");
// 
//     XmlRpcClient client( GetGLSIP(), GetGLSPort(), "/gls");
//     XmlRpcValue args;
//     XmlRpcValue result;
// 
//     XmlRpcClientGuard clientGuard( &client );
// 
//     std::string glsid = "";
//     if ( !GetGlsId(GetAccount(), glsid) )
//     { return false; }
// 
//     std::string md5Result = "";
//     std::stringstream sstrSha1;
//     if ( !GetPwdSha1(GetPassword(), glsid, md5Result, sstrSha1) )
//     { return false;}
// 
//     args.clear();
//     result.clear();
// //////////////////////////////////////////////////////////////////////////
//     args[0] = GetAccount();
//     args[1] = glsid;
//     args[2] = md5Result;
//     args[3] = "geren";  //登录类型
//     if (!client.execute("login_vtype", args, result))
//     {
//         SetLoginErrorCode(9002); //Error calling 'login'
//         SetBotState(State_End);
//         SetTipsInfo("login fail");
//         LOG_MESSAGE( LogObject, LOG_PRIORITY_ERROR, "Excute [login_vtype] Login Error faultCode = %d!", 9002);
// 		//client.close();
//         return false;
//     }
// 	//client.close();
// 
//     if (result.hasMember("faultCode"))
//     {
//         int nError = result["faultCode"];
//         SetLoginErrorCode(nError);
//         SetBotState(State_End);
//         SetTipsInfo("login faultCode fail");
//         LOG_MESSAGE( LogObject, LOG_PRIORITY_ERROR,"XmlRpcClient Login Result HasMember faultCode = %d!",nError);
//         return false;
//     }
// 
//     int guid = result["guid"];
// 
//     args.clear();
//     result.clear();
// 
//     args[0] = guid;
//     args[1] = glsid;
// 
//     SetTipsInfo("通过验证");
// 
// 	// 等待5秒
// 	Sleep( 5000 );
// 
//     /*
// 		status返回值解释：
// 		0  帐号通过身份验证，排队中
// 		1  等待游戏服务器认领帐号
// 		2  游戏服务器正在为帐号分配资源
// 		3  资源分配完毕
// 		4  玩家进入游戏
// 	*/
//     int nLoopCount = 0;
//     while ( true )
//     {
//         if (!client.execute("query_user_status", args, result))
//         {
//             SetLoginErrorCode(9002); //Error calling 'query_user_status'
//             SetBotState(State_End);
//             SetTipsInfo("query_user_status fail");
//             LOG_MESSAGE( LogObject, LOG_PRIORITY_ERROR, "XmlRpcClient query_user_status Error faultCode = %d!", 9002);
// 			//client.close();
//             return false;
//         }
// 		//client.close();
// 
//         if (result.hasMember("faultCode"))
//         {
//             int nError = result["faultCode"];
//             SetLoginErrorCode(nError);
//             SetBotState(State_End);
//             SetTipsInfo("query_user_status faultCode fail");
//             LOG_MESSAGE(LogObject,LOG_PRIORITY_ERROR,"XmlRpcClient query_user_status Result HasMember faultCode = %d!", nError);
//             return false; 
//         }
// 
//         int status = result["status"];
//         if (status == 3)
//         {
//             std::string msg = result["msg"];
//             std::string key;
//             std::string ip;
//             int port;
// 
//             size_t p = msg.find(',') + 1;
//             size_t p2 = msg.find(',', p);
// 
//             key = msg.substr(0, p - 1);
//             ip = msg.substr(p, p2 - p);
//             port = atoi(msg.substr(p2 + 1).c_str());
// 
// 			InitConnect(ip.c_str(),port);
//         //    SetServerIp(ip.c_str());
//          //   SetServerPort(port);
// 
//             MD5 md5Key(key + sstrSha1.str());
// 
//             _accountId = guid;
//             m_strSessionKey =  md5Key.toString();
// 
//             SetBotState(State_EnterCharacterS);
//             break;
//         }
// 
//         ++nLoopCount;
// 
//         if (nLoopCount > LOOPQUERYMAXNUM)
//         {
//             SetBotState(State_End);
//             SetTipsInfo("query_user_status overtime");
//             break;
//         }
//         Sleep( 5000 );
//     }
// 
//     return true;
// }


bool BaseRobot::HandleStateEnd()
{
    if ( IsConnectted())
    { 
        Close();    // NetworkNode
       SetTipsInfo("退出游戏");
   }

    return true;
}
 
bool BaseRobot::HandleStatePlay()
{
    _pingTime.StartTimer( HQ_TimeGetTime(), PING_MSG_SPACE );
    if ( _pingTime.DoneTimer( HQ_TimeGetTime() ))
    {
        MsgPingMsg ping;
        ping.dwTime = HQ_TimeGetTime();
	      SendMsg(&ping);
    }

    if (!bIsPlayTime)
    {
        bIsPlayTime = true;
        dw_LoginTotalTime = HQ_TimeGetTime() - dw_FirstLoginTotalTime;
        dw_EnterWorldTime = HQ_TimeGetTime() - dw_FirstEnterWorldTime;

        LOG_MESSAGE( LogObject,LOG_PRIORITY_DEBUG,"请求登录到开始玩游戏之间总时间\t%ld ms\n登录GLS花费的时间\t%ld\n选择角色花费的时间\t%ld\n进入游戏世界花费的时间%ld",dw_LoginTotalTime,dw_LoginGLSTime,dw_LoginSelectRoleTime,dw_EnterWorldTime);
        if (GetBotLevel()<20)
            InitPlayGame();

        NeedCheckLoginTime = false;
    }
    //判断是否已经死亡
    if(m_CharInfo.baseinfo.liveinfo.nHp <= 0)
    {
        if(CheckTime(10))
        {
            MsgReqRelive msg;
            msg.byBornPos = eReliveTypeNearPos;
            SendMsg(&msg);    

            MsgMapLoaded msgMapLoaded;
			msgMapLoaded.header.stID = m_shPlayerId;
            SendMsg( &msgMapLoaded );

            SetTipsInfo("角色死亡");
        }
        return false; // 死了不执行
    }

    //SetTipsInfo("游戏中");
    m_vLastProTime[GetBotState()].StopTimer();
    PlayGame();

    return true;
}
void	BaseRobot::try_comfirm_account()
{
	//在不断重发MsgAllocGWID报文时,收到要求验证的回复，就验证一次
	DWORD t=GetTickCount();
	if(t-nTimeLastConfirm>16000){
	//	if(GetBotState()==e_state_no_confirm)
		{
			if(IsConnectted())
			{
				//MsgExit msg;
		//		SendMsg(&msg );
			}
			else
			{
				InitConnect(theBotDataCenter.GetServerIP(),theBotDataCenter.GetServerPort());
				if (!ConnectToServer())
				{
					return;
				}
			}
			ReGetCharacterlist();
			nTimeLastConfirm=t;
			g_bEndGetCharacter=false;
			SetBotState(e_state_wait_confirm_result);

			SAccountInfo	sAccount;
			strncpy( sAccount.szID, m_szBotName, sizeof(sAccount.szID)-1 );
			strncpy( sAccount.szPwd, m_szPassWord, sizeof(sAccount.szPwd)-1 );

			if (!EncodeAccountInfo(&sAccount))
			{
				return;
			}

			MsgLoginAccountInfo msg;		
			strncpy_s( msg.szFullVersion,sizeof(msg.szFullVersion),thApplication.GetFullVersion(),sizeof(msg.szFullVersion)-1   );
			memcpy(msg.szAccount,sAccount.szCryptID,min(SAccountInfo::eMaxString,MsgLoginAccountInfo::eAccountMax));
			memcpy(msg.szPwds,sAccount.szCryptPWD,min(SAccountInfo::eMaxString,MsgLoginAccountInfo::ePwdsMax));
			msg.isEncryp = true;
			SendMsg(&msg);

			/*SHttpTask* pTask = new SHttpTask;
			pTask->task_type = etasktype::etasktype_login;
			pTask->robot=this;
			strncpy( pTask->task_detail.accountinfo.user_name, m_szBotName, MAX_USERNAME-1 );
			strncpy( pTask->task_detail.accountinfo.passwords, m_szPassWord, MAX_PASSWORDS-1 );
			theHttpEncapsulation.AddHttTask(pTask);*/
		}
	}	
}


void BaseRobot::SwitchGate(bool _connect)
{
	DWORD dwTime = HQ_TimeGetTime();
	if (dwTime +g_dwSwitchGatePeriod - g_dwSwitchGateTime > 16 * 10000/* 16s */)
	{
		// 超时
		g_bSwitchGate = false;
		g_bEndGetCharacter = false;
		m_bNeedAckAgain =false;
	}
	InitConnect(_targetGateIp.c_str(),_targetGatePort);
	if (ConnectToServer()&& g_bSwitchGate)
	{
		g_bSwitchGate = false;
		g_bEndGetCharacter = TRUE;
		m_bNeedAckAgain = false;

		MsgAllocGWID allgwid;
		strncpy_s(allgwid.szAccount, sizeof(allgwid.szAccount), m_szBotName, sizeof(allgwid.szAccount)-1);
		allgwid.nAccountID = _accountId;
		allgwid.nIsSwitchGame = true;
		allgwid.SessionKey = SessionKey;
		//strncpy_s(allgwid.SessionKey,sizeof(allgwid.SessionKey), m_strSessionKey.c_str(),sizeof(allgwid.SessionKey)-1);
		SendMsg(&allgwid);

		MsgGetCharacter getChar;
		strcpy(getChar.szAccount, m_szBotName);
		getChar.nAccountID = _accountId;
		getChar.SessionKey = SessionKey;
		//strncpy_s( getChar.SessionKey, sizeof(getChar.SessionKey), m_strSessionKey.c_str(), sizeof(getChar.SessionKey) - 1);
		getChar.dwCharacterId = GetBotDBID();
		getChar.stWitchSlot = sPlayerSlot;
		SendMsg(&getChar);
		GetConnector()->CheckSend();
		SetTipsInfo("切服");
	}
}


void BaseRobot::EnterWorld(int nIndex)
{
	if (nIndex < 0 || nIndex >= CHARACTOR_COUNT || GetBotState() == State_Play)
	{
		return;
	}

	MsgEnterWorld xMsg;
	if (m_vCharacterID[nIndex] != 0)
	{
		xMsg.stWhichSlot = nIndex;
		sPlayerSlot =nIndex;
		xMsg.dwCharacterID = m_vCharacterID[nIndex];
		_charDbId=m_vCharacterID[nIndex];
		xMsg.dwEnterWorldTime = HQ_TimeGetTime();
		xMsg.dwAccountId = _accountId;
		SendMsg(&xMsg);	
		isReadyEnterGame=true;
		SetTipsInfo("进入游戏");
	}
}



bool BaseRobot::HandleStateCreateChar()
{    
	if (m_hasCreateRole)
	{
		return true;
	}
	SetTipsInfo("请求创建角色");

    MsgCreateHeroChar msg;
    msg.stWhichSlot = 0;
    int nSelect = rand() % s_nNameCount;
    int nAccount = atoi(GetAccount());
    if (nAccount % 2 == 0) // 账号偶数为TV
    {
        sprintf_s( msg.create.szCharacterName,sizeof(msg.create.szCharacterName), "%sV%s", s_pszName[0], m_szBotName);
    }
    else // 账号奇数为HV
    {
        sprintf_s( msg.create.szCharacterName,sizeof(msg.create.szCharacterName), "%sV%s", s_pszName[1], m_szBotName);
    }

    //if (theBotDataCenter.BotProfession < EArmType_Warrior || theBotDataCenter.BotProfession > EArmType_Sniper )
    //{ msg.create.usProfession = rand() % EArmType_MaxSize; } // 职业,随机
    //else
    //{ msg.create.usProfession = theBotDataCenter.BotProfession; }
    //msg.create.usProfession = EArmType_Mage; //法王
	msg.create.usProfession = theRand.rand32() % 5; /*EArmType_Hunter;*/// 随机职业
    msg.create.ucFaceIndex = Race_China;            // 种族
    msg.create.ucHairColorIndex = (unsigned char)0; // 头发颜色的索引
    msg.create.ucHairModelIndex = (unsigned char)0; // 头发模型的索引
    msg.create.ucModelIndex = (unsigned char)0;     // 身体模型的索引
    msg.create.ucHeadPic = (unsigned char)0;

	msg.create.ucCountry = CountryDefine::Country_Init;    // 中立区域    

    SendMsg(&msg);
    m_bGetItem = true;
	m_hasCreateRole = true;
    SetTipsInfo("等待创建角色回馈");
    return true;
}

void BaseRobot::ReqAddPet( unsigned int nPetId, unsigned int nQuality, unsigned int nSex )
{
	MsgChat msg( MsgChat::CHAT_TYPE_NORMAL );
	strncpy( msg.chatHeader.szToName, m_CharInfo.baseinfo.aptotic.szCharacterName , MAX_NAME_STRING - 1 );

	char szMsg[dr_MaxChatString - 1] = {0};
	std::string command = "";
	command += "/AddPet %d %d %d";
	_snprintf( szMsg, dr_MaxChatString - 1, command.c_str(), nPetId, nQuality, nSex );

	msg.SetString(szMsg);
	SendMsg( &msg );
}

SPetItem* BaseRobot::FindPetByGuid(__int64 FindGuid)
{
	if (FindGuid <= 0)
	{
		return NULL;
	}
	for (ItrSPetContainer itr = SPets.begin();itr != SPets.end();++itr)
	{
		if (itr->baseInfo.guid == FindGuid)
		{
			return &(*itr);
		}
	}

	return NULL;
}
SPetItem* BaseRobot::FindPetByIndex(int Index)
{
	if (Index < 0 || Index >= SPets.size())
	{
		return NULL;
	}

	int i = 0;
	for (ItrSPetContainer itr = SPets.begin();itr != SPets.end();++itr,++i)
	{
		if (i == Index)
		{
			return &(*itr);
		}
	}

	return NULL;
}

void BaseRobot::OnMsgGetPet(Msg* pMsg)
{
	MsgAddUpdatePet* pGetMsg = (MsgAddUpdatePet*) pMsg;

	if ( pGetMsg->type == MsgAddUpdatePet::OT_Add )
	{
		SPets.push_back(pGetMsg->pet);
	}
	else
	{
		ItrSPetContainer petItrBegin = SPets.begin();
		ItrSPetContainer petItrEnd	 = SPets.end();
		for ( ; petItrBegin != petItrEnd ; ++petItrBegin)
		{
			if ( petItrBegin->baseInfo.petId == pGetMsg->pet.baseInfo.petId )
			{
				*petItrBegin = pGetMsg->pet;
				break;
			}
		}
	}
}

bool BaseRobot::EncodeAccountInfo(SAccountInfo* pAccountInfo)
{
	if (!pAccountInfo)
	{
		return false;
	}

	memset(pAccountInfo->szCryptID,0,sizeof(pAccountInfo->szCryptID));
	memset(pAccountInfo->szCryptPWD,0,sizeof(pAccountInfo->szCryptPWD));

	/*return true;*/
	if (!theSimpleCtyp.Encode(pAccountInfo->szID,16/*strlen(pAccountInfo->szID)*/,pAccountInfo->szCryptID)
		||!theSimpleCtyp.Encode(pAccountInfo->szPwd,16/*strlen(pAccountInfo->szPwd)*/,pAccountInfo->szCryptPWD))
	{
		return false;
	}
	return true;
}