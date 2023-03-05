#include "stdafx.h"
#include "bot.h"
#include "ItemDetailConfig.h"
#include "DelBot.h"
#include "LoginBot.h"
#include "AttackBot.h"
#include "NormalBot.h"
#include "FightBot.h"
#include "FlyBot.h"
#include "QuestBot.h"
#include "ScriptBot.h"
#include "BotApplication.h"
#include "GameBot.h"
//#include "GuildBot.h"
#include "IdleBot.h"
#include "TeamBot.h"
#include "EctypeBot.h"
#include "DromeBot.h"
#include "LoginBot.h"
//#include "BusinessBot.h"
#include "FirendBot.h"
#include "GmCommandRobot.h"
#include "MatrixBot.h"
//#include "WarBot.h"
#include "Client.h"
#include "BotAppDataCenter.h"
#include "MiniDumper.h"
#include "application_config.h"
#include "ScriptManager.h"
#include "LuaScriptManager.h"   //Lua脚本管理类
#include "NetworkInput.h"


bool BotApplication::Exit = false;
extern bool g_OpenConsole; // 控制台配置

#define MAX_BOTNUM 2000

BotApplication::BotApplication() : m_nAliveBotCount(0), m_nCurSel(-1)
{
    _appState         = EAppStateType_Init;
	m_nAttackBotCount = 0;
	m_nMoveBotCount   = 0;

    m_AddInfo = SAddInfo();
    nAddCount = 0;
    //nSpace = 0;
    pMsgOld = NULL;

	m_pSetInfo = NULL;
	m_vecAddInfo.clear();
    _lastShowTime.StartTimer( HQ_TimeGetTime(), 1000 );
	m_dwCreateTime = HQ_TimeGetTime();
}

BotApplication::~BotApplication()
{
    _robots.clear();

	if (m_pSetInfo != NULL)
	{
		delete m_pSetInfo;

		m_pSetInfo = NULL;
	}
}
enum{
	//gate server
	eN_Bot_BigBufferSize = 128*1024,//指定大块的大小
	eN_Bot_BigBufferNum = 1,//指定大块的数目
	eN_Bot_SmallBufferSize = 64*1024,//指定小块的大小
	eN_Bot_SmallBufferNum = 100,//指定小块的数目
	eN_Bot_ListenNum = 5,//指定用于监听的套接字的数目
	eN_Bot_SocketNum = 2000,//用于连接的总数目
	eN_Bot_ThreadNum = -1,//指定网络线程数目，若设置为小于等于0，则会开启cpu个数的线程数目
};


uint32 BotApplication::Init(const char* szConfig )
{	
    if ( NULL == szConfig )
    { return ER_Failed; }

    //MiniDumper dumper("Robot",ApplicationConfig::Instance().GetFullVersion(),".\\Bot.dump");

    //GetMeNetwork().SocketStartUp();
    //GetMeNetwork().StartIoCompletionPort( 1, -1);
	if (!network::net_init(eN_Bot_BigBufferSize,
		eN_Bot_BigBufferNum,
		eN_Bot_SmallBufferSize,
		eN_Bot_SmallBufferNum,
		eN_Bot_ListenNum,
		eN_Bot_SocketNum,
		eN_Bot_ThreadNum))
	{
		return 0;
	}
    // 读取怪物配置文件
    theApp.LoadMonsterFile();
    //theApp.LoadBinPathFinder();

    if (!theMapConfig.LoadMapConfig(WorldMapFile))
    {
        CString strText = "";
        strText.Format("加载%s错误!", WorldMapFile);
        AfxMessageBox(strText);
        return ER_Failed;
    }

    //try
    //{
    //    //LOG_CONFIGURE(LogConfig);
    //    //2008下面,log4cpp权限太低,不能创建文件夹
    //    HelperFunc::CreateOutputFolder(LogPath);
    //    if(_access(LogFile, 0) == -1)
    //    {
    //        CreateFile(LogFile,	GENERIC_WRITE, 0, NULL,  CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, NULL);            
    //    }
    //}
    //catch(ConfigureException&)
    //{   
    //    return false;
    //}

    _robots.clear();

    char* szConfigFile = "..\\Data\\RobotScript\\Robot.ini";
    char* szDef = "GameBot";
    char szBuffer[256] = {0};
    memset( szBuffer, 0, sizeof(szBuffer));

    if (BotAppDataCenter::Successed != theBotDataCenter.Init( szConfig ))
    {
        return ER_Failed;
    }
    if ( theBotDataCenter.GetOpenConsole() )
    {
        myConsole.RedirectIoToConsole(); // 控制台打印信息
    }
    
    //读取设定
    if (m_pSetInfo == NULL)
    {
        m_pSetInfo = new SSetInfo();
    }

    GetIniInt(m_pSetInfo->nRequestStart, "RequestStart", 1);
    GetIniInt(m_pSetInfo->nRequestSecond, "RequestSecond", 5);
    GetIniInt(m_pSetInfo->nRequestCount, "RequestCount", 3);


    //读取道具相关配置信息
    if (!theItemDetailConfig.InitItemDetail())
    {
        CString strText = "";
        strText.Format("加载 %s 失败!", DataFile);
        AfxMessageBox(strText);

        return ER_Failed;
    }

    //加载怪物数据
    if (!theItemDetailConfig.LoadXmlMonster(MONSTERCONFIG_FILEPATH))
    {
        CString strText = "";
        strText.Format("加载 %s 失败!", MONSTERCONFIG_FILEPATH);
        AfxMessageBox(strText);

        return ER_Failed;
    }

    //加载怪物声音
    if (!theItemDetailConfig.LoadXmlCreatureSound(MONSTERSOUNDCFG_FILEPATH))
    {
        CString strText = "";
        strText.Format("加载 %s 失败!", MONSTERSOUNDCFG_FILEPATH);
        AfxMessageBox(strText);

        return ER_Failed;
    }

    //加载坐骑属性
    if (!theItemDetailConfig.LoadXmlMount(MOUNTCONFIG_FILEPATH))
    {
        CString strText = "";
        strText.Format("加载 %s 失败!", MOUNTCONFIG_FILEPATH);
        AfxMessageBox(strText);

        return ER_Failed;
    }

    //加载装备随机属性
    if (!theItemDetailConfig.LoadXmlRand(EQUIPMENTRANDOM_FILEPATH))
    {
        CString strText = "";
        strText.Format("加载 %s 失败!", EQUIPMENTRANDOM_FILEPATH);
        AfxMessageBox(strText);

        return ER_Failed;
    }

    // 加载Robot脚本路径文件
    if ( !theLuaManager.LoadScriptConfig(RobotScriptFile) )
    {
        CString strText = "";
        strText.Format("加载 %s 失败！", RobotScriptFile);
        AfxMessageBox(strText);

        return ER_Failed;
    }
#define CommonJob (-1)
    for (int skillid = 1000;skillid <= 1917;++skillid)
    {
        CItemDetail::SItemSkill* psikll = GettheItemDetail().GetSkillByID(skillid,1);
        if (NULL != psikll && psikll->cLearnProfessionReq != CommonJob)
        {
            for (int n = 1;n <= psikll->ustSkillMaxLvl;++n)
            {
                skillStruct skill;
                skill.id = skillid;
                skill.SkillLevel = psikll->ustLevel;
                skill.targetType = n;//psikll->ustCastTarget;
                RoleSkillMap.insert(SkillMap::value_type(psikll->cLearnProfessionReq,skill));
            }
        }
    }

    if (ER_Failed == theScriptManager.Init())
    { return ER_Failed; }

    if ( ER_Success != theNpcInfo.LoadConfig(NpcXml_File))
    { 
        CString strText = "";
        strText.Format("加载 %s 失败!", NpcXml_File);
        return ER_Failed; 
    }
    srand(HQ_TimeGetTime());

    SetAppState( EAppStateType_Update );

    LMsgInitReady msg;
    msg.bIsInitReady = true;
    theApp.PushMessage(&msg);

    return ER_Success;
}

void BotApplication::Update()
{
    // 网络消息
	network::net_run();
	for (int i=0; i<_robots.size(); ++i)
	{
		BaseRobot* pBot = _robots[i];
		if (pBot == NULL)
		{ continue;}
		pBot->Update();
	}

    /*INetworkApp::Update();*/
    
    // gui消息
    ProcessGuiMessage();
   
    //显示机器人信息
    ShowBotCountInformation();

    // 定时添加机器人
    AddRobotInformation();

	Sleep(1);
}

void BotApplication::UnInit()
{
   /* ShutDown();

    GetMeNetwork().StopIoCompletionPort();
    GetMeNetwork().SocketCleanUp();*/

    SetAppState( EAppStateType_Exiting );

    theApp.PostThreadMessage( WM_QUIT,0,0 );
}

void BotApplication::PushMessage( SBaseGuiLogicMessage* pGuiMessage )
{
    uint8* pTemp = _messageAlloc.allocate( pGuiMessage->size );
    if ( NULL == pTemp )
    { return; }
    memcpy_s( pTemp, pGuiMessage->size, pGuiMessage, pGuiMessage->size );

    CSALocker lock(_messageLock);
    _messages.push_back( pTemp );
}

void BotApplication::ProcessGuiMessage()
{
    GuiLogicMessageContainer tempMessage;
    {
        CSALocker locker( _messageLock );
        if ( _messages.empty())
        { return; }
        tempMessage = _messages;
        _messages.clear();
    }
    
    while( !tempMessage.empty()  )
    {	
        unsigned char* pBlock = tempMessage.front();
        SBaseGuiLogicMessage* pMessage = (SBaseGuiLogicMessage*)pBlock;
        switch ( pMessage->id )
        {
        case EGuiLogicMessageType_AddRobot:
            {
                GMsgAddRobot* pDetail = (GMsgAddRobot*)pMessage;
                HandleGMsgAddRobot( pDetail );
            }
            break;
        case EGuiLogicMessageType_ShowRobot:
            {
                GMsgShowRobot* pMsgShowBot = (GMsgShowRobot*)pMessage;
                HandleGMsgShowRobot( pMsgShowBot );
            }
            break;
        case EGuiLogicMessageType_PauseAddBot:
            {
                GMsgPauseBot* pMsgPauseAddBot = (GMsgPauseBot*)pMessage;
                HandleGMsgPauseAddBot( pMsgPauseAddBot );
            }
            break;
        case EGuiLogicMessageType_PlaySkill:
            {
                GMsgPlaySkill* pMsgPlaySkill = (GMsgPlaySkill*)pMessage;
                HandleGMsgPlaySkill(pMsgPlaySkill);
            }
            break;
        case EGuiLogicMessageType_Moving:
            {
                GMsgBotMoving* pMsgBotMove = (GMsgBotMoving*)pMessage;
                HandleGMsgBotMoving(pMsgBotMove);
            }
            break;
        case EGuiLogicMessageType_PlayAttack:
            {
                GMsgBotPlayAttack* pMsgPlayAttack = (GMsgBotPlayAttack*)pMessage;
                HandleGMsgBotPlayAttack(pMsgPlayAttack);
            }
            break;
        case EGuiLogicMessageType_BotRide:
            {
                GMsgBotRide* pBotRide = (GMsgBotRide*)pMessage;
                HandleGMsgBotRide(pBotRide);
            }
            break;
        case EGuiLogicMessageType_ReloadLuaScript:
            {
                GMsgReLoadLuaScript* pMsgReload = (GMsgReLoadLuaScript*)pMessage;
                HandleGMsgReloadLuaScript(pMsgReload);
            }
            break;
		case EGuiLogicMessageType_PrepareSuit:
			{
				GMsgPrepareSuit* pSuitMsg = (GMsgPrepareSuit*)pMessage;
				HandlePrepareSuit(pSuitMsg);
			}
			break;
        }
        _messageAlloc.deallocate( pBlock );
        tempMessage.pop_front();
    }
}

void BotApplication::ScriptAddBot()
{
	if (m_vecAddInfo.empty() || m_xAddInfo.nCount > 0) { return; }

	ItrAddInfoContainer iter = m_vecAddInfo.begin();
	AddBot(*iter); //添加

	
	m_vecAddInfo.erase(iter);
}

void BotApplication::AddBot( const SAddInfo& xAddInfo)
{
    // 脚本机器人先屏蔽掉
    if (xAddInfo.nType == Bot_Script) 
    { return;	}
	
	_addTime.StartTimer(HQ_TimeGetTime(), m_xAddInfo.nSpaceTime);
    m_xAddInfo.nCount = xAddInfo.nCount;
    m_xAddInfo.nStartId = xAddInfo.nStartId;//(xAddInfo.nStartId < 1000 ? 1000 : xAddInfo.nStartId);

    m_xAddInfo.nType = xAddInfo.nType;
    m_xAddInfo.nSpaceTime = xAddInfo.nSpaceTime;
    m_xAddInfo.nPerCount = xAddInfo.nPerCount;
    m_xAddInfo.nOnlineTime = xAddInfo.nOnlineTime;
    m_xAddInfo.nFlySpace = xAddInfo.nFlySpace;
    m_xAddInfo.nMoveStep = xAddInfo.nMoveStep;
    m_xAddInfo.xAreaInfo = xAddInfo.xAreaInfo;
}

void BotApplication::AddBot( int nPerCount, int nStartId, int nType, int nOnlineTime, int nFlySpace, int nMoveStep, SAreaInfo *pAreaInfo )
{
	CString s;
	s.Format("%d,%d",nPerCount,nStartId);
    for(int i=0; i<nPerCount; ++i)
    {
        BaseRobot* pRobot = NULL;
        switch(nType)
        {
        case Bot_Normal:
            { pRobot = new CNormalBot; }
            break;
        case Bot_Attack:
            { pRobot = new CAttackBot; }
            break;
        case Bot_Fly:
            { pRobot = new CFlyBot; }
            break;
        case Bot_Fight:
            { pRobot = new CFightBot; }
            break;
        case Bot_Quest:
            { pRobot = new CQuestBot; }
            break;
        case Bot_Script:
            { pRobot = new CScriptBot; }
            break;
        //case Bot_Guild:
        //    { pRobot = new CGuildBot; }
        //    break;
        case Bot_Online:
            { pRobot = new OnlineBot; }
            break;
        case Bot_Team:
            { pRobot = new TeamBot; }
            break;
        case Bot_Ectype:
            { pRobot = new EctypeBot; }
            break;
        case Bot_Brome:
            { pRobot = new DromeBot; }
            break;
        case Bot_Login:
            { pRobot = new CLoginBot; }
            break;
        //case Bot_Business:
        //    { pRobot = new CBusinessBot; }
        //    break;
        case Bot_Firend:
            { pRobot = new FirendBot; }
            break;
        case Bot_PlatformTest:
            { pRobot = new GmCommandRobot; }
            break;
        case Bot_MatrixBot:
            { pRobot = new CMatrixBot; }
            break;
        case Bot_Client:
            { pRobot = new Client; }
            break;
        //case Bot_WarBot:
        //    { pRobot = new CWarBot; }
        //    break;
        default:
            {
                char MessageBuf[512] = {0};
                sprintf_s(MessageBuf,512,"添加机器人时,没有找到对应的机器人类型,%s %s %d",__FILE__,__FUNCTION__,__LINE__);
                MessageBox(AfxGetApp()->GetMainWnd()->GetSafeHwnd(),MessageBuf,"Warning",MB_OK|MB_ICONWARNING);
            }
            return;
        }
        
        if ( NULL == pRobot )
        { return; }

        if ( !AddBotInMapList( pRobot, nStartId, nType, nMoveStep ) )
        { 
            delete pRobot; 
            return;
        }

        switch( nType )
        {
        case Bot_Normal:
            {
                CNormalBot* pBot = (CNormalBot*)pRobot;
                pBot->SetAreaInfo(pAreaInfo); //设置区域范围
                if (nFlySpace > 0)
                { pBot->SetFlySpaceTime(nFlySpace); }
            }
            break;
        case Bot_Attack:
            {
                CAttackBot* pBot = (CAttackBot*)pRobot;
                pBot->SetAreaInfo(pAreaInfo); //设置区域范围
                ++m_nAttackBotCount;
            }
            break;
        case Bot_Fly:
            {
                CFlyBot* pBot = (CFlyBot*)pRobot;
                if (nFlySpace > 0)
                { pBot->SetFlySpaceTime(nFlySpace); }					
                ++m_nMoveBotCount;                
            }
            break;
        case Bot_Fight:
            {
                CFightBot* pBot = (CFightBot*)pRobot;
                pBot->SetAreaInfo(pAreaInfo); //设置区域范围
                ++m_nAttackBotCount;
            }
            break;
            // ToDo:其他Pk的机器人类型
        default:
            {}
            break;
		}
	
    }
}

bool BotApplication::AddBotInMapList( BaseRobot* pBot, int nStartId, int nType, int nMoveStep )
{
	if(pBot == NULL || !pBot->Init(m_pSetInfo) || m_nAliveBotCount >= MAX_BOTNUM)
	{ return false; }	
	pBot->SetBotID(++m_nAliveBotCount);
	

	char szFormat[20] = {0};
	char szUserName[20] = {0};
	/*sprintf(szFormat, "%%s%%0%dd",  m_nWildCardNum);*/
	if (m_nAliveBotCount > 0)
	{
		sprintf(szFormat, "%%s%%0%dd",  theBotDataCenter.GetAccountWidth());
	}
	else
		sprintf(szFormat, "%%s%%d");

	sprintf( szUserName, szFormat, theBotDataCenter.GetBotAccount(), m_nAliveBotCount+nStartId );
	
	//::MessageBox(NULL,szUserName,"",MB_OK);
	
	
	pBot->SetPassword(theBotDataCenter.GetBotPassword());
	pBot->SetAccount(szUserName);
	pBot->_targetGateIp=theBotDataCenter.GetServerIP();
	pBot->_targetGatePort=theBotDataCenter.GetServerPort();
//	pBot->SetGLSAddress(theBotDataCenter.GetServerIP(), theBotDataCenter.GetServerPort());
//	pBot->SetPermanence(TRUE);
	pBot->SetType(nType);
	pBot->SetMoveStep(nMoveStep);
	pBot->SetTipsInfo("未初始化");
  //  pBot->SetBotSpace(nSpace);

	////设置开始统计时间
	pBot->m_xMsgStatistician.SetStartTime(HQ_TimeGetTime());
 //   
	//RegisterNode(pBot); // 注册节点
    CSALocker lock( _lockRobots );
    _robots.insert( RobotContainer::value_type(m_nAliveBotCount, pBot));
	
	return true;
}

void BotApplication::HandleGMsgAddRobot( GMsgAddRobot* pMessage )
{
    if (pMessage == NULL)
    { return; }

    // m_AddInfo来记录消息的数值，如果多次点击，则累加总数
    m_AddInfo = pMessage->m_xAddInfo;
	//nSpace = pMessage->nBotSpace;

	if ( (pMsgOld != pMessage) && (pMsgOld != NULL) )
	{
	   m_AddInfo.nCount += pMessage->m_xAddInfo.nCount;
	}
	pMsgOld = pMessage;

    _addTime.StartTimer(HQ_TimeGetTime(), m_AddInfo.nSpaceTime);
}

void BotApplication::SetAddBot(SAddInfo& addInfo)
{
 //   ScriptAddBot();

    if (addInfo.nPerCount > addInfo.nCount)
    {
        addInfo.nPerCount = addInfo.nCount;
    }

    AddBot(addInfo.nPerCount, addInfo.nStartId, addInfo.nType, addInfo.nOnlineTime, 
        addInfo.nFlySpace, addInfo.nMoveStep, &addInfo.xAreaInfo);
}

void BotApplication::AddRobotInformation()
{
    if (_addTime.DoneTimer(HQ_TimeGetTime()) && m_AddInfo.nCount > 0)
    {
        SetAddBot( m_AddInfo );
        m_AddInfo.nCount -= m_AddInfo.nPerCount;
    }
	if (_addTime.DoneTimer(HQ_TimeGetTime()) && m_xAddInfo.nCount > 0)
	{
		SetAddBot( m_xAddInfo );
		m_xAddInfo.nCount -= m_xAddInfo.nPerCount;
	}
	
	ScriptAddBot();
}

int  BotApplication::nBotID = 0;// 初始化当前机器人ID 
void BotApplication::HandleGMsgShowRobot( GMsgShowRobot* pMessage )// [10/8/2010 pengbo.yang]
{
    theApp.gBotApplication.SetBotID(pMessage->robotId);// 设置RobotID
}

void BotApplication::HandleGMsgPauseAddBot( GMsgPauseBot* pMessage )
{
    if (pMessage->bIsPause)
    {
        nAddCount = m_AddInfo.nCount;
        m_AddInfo.nCount = 0;
    }
    else
    {
        m_AddInfo.nCount = nAddCount;
    }
}

bool g_PlaySkill = false;
int  g_skillID = 0;
void BotApplication::HandleGMsgPlaySkill( GMsgPlaySkill* pMessage )
{
    g_PlaySkill = pMessage->bIsPlaySkill; // 全局的释放技能的开关
    g_skillID   = pMessage->nSkillID;     // 全局的技能ID
}

bool g_BotMove = false;
int  g_nBotMoveRange = 0;
void BotApplication::HandleGMsgBotMoving( GMsgBotMoving* pMessage)
{
    g_BotMove = pMessage->bIsMove;
    g_nBotMoveRange = pMessage->nMoveRange;
}

bool g_BotPlayAttack = false;			  // 全局的攻击开关
bool g_bCreateMonster = false;			  //机器人创建开关 luo.qin 3.18
bool g_bChangeEquip = false;			  //机器人随机换装开关 luo.qin 3.28
bool g_bRandRide = false;				  //机器人随机骑马开关 luo.qin 3.28
bool g_bCountryFight = false;			  //机器人国战开关 luo.qin 3.28
void BotApplication::HandleGMsgBotPlayAttack( GMsgBotPlayAttack* pMessage )
{
    g_BotPlayAttack = pMessage->bIsPlayAttack;
}

bool g_BotRide = false;
void BotApplication::HandleGMsgBotRide( GMsgBotRide* pMessage)
{
    g_BotRide = pMessage->bIsRide;
}

bool g_BotReloadLuaScript = false;
void BotApplication::HandleGMsgReloadLuaScript(GMsgReLoadLuaScript* pMessage)
{
    g_BotReloadLuaScript = pMessage->bIsReloadLuaScript;
    for (int i=0; i<_robots.size(); ++i)
    {
        BaseRobot* pBot = _robots[i];
        if (pBot == NULL)
        { continue;}

        ((CMatrixBot*)pBot)->SetbInit(g_BotReloadLuaScript);
    }
}

//准备换装的消息处理 luo.qin 4.2
static int s_nItemID_Hunter[6][10] = {{9104,11501,11502,11503,11504,11505,11506,11507,11508,11509},
{9114,11541,11542,11543,11544,11545,11546,11547,11548,11549},
{9124,12041,12042,12043,12044,12045,12046,12047,12048,12049},
{9129,11511,11512,11513,11514,11515,11516,11517,11518,11519},
{9134,11521,11522,11523,11524,11525,11526,11527,11528,11529},
{9207,11551,11552,11553,11554,11555,11556,11557,11558,11559} };
void BotApplication::HandlePrepareSuit( GMsgPrepareSuit* pMessage )
{
	for ( int i = 0; i < _robots.size(); ++i )
	{
		BaseRobot* pBot = _robots[i];
		if ( pBot == NULL )
		{ continue; }
		//pBot->RandChangeEquip_BotCommand();
		pBot->ChangeEquipByProfession();
	}

}

//用户名密码由logininfo采集
bool BotApplication::AddClientInMapList(BaseRobot *pBot, int nSetp /* = 1000 */)
{
	if(pBot == NULL || !pBot->Init(m_pSetInfo))
	{
		return false;
	}
	pBot->SetBotID(++m_nAliveBotCount);
	pBot->_targetGateIp=theBotDataCenter.GetServerIP();
	pBot->_targetGatePort=theBotDataCenter.GetServerPort();
	//	pBot->SetGLSAddress(theBotDataCenter.GetServerIP(), theBotDataCenter.GetServerPort());
	pBot->SetMoveStep(nSetp);
	pBot->m_xMsgStatistician.SetStartTime(HQ_TimeGetTime());
	//RegisterNode(pBot);
	CSALocker lock( _lockRobots );
	_robots.insert( RobotContainer::value_type(pBot->GetBotID(), pBot));
	return true;
}

BaseRobot* BotApplication::GetBot( int nID)
{
    CSALocker lock( _lockRobots );
    ItrRobotContainer itr = _robots.find( nID );
    if(itr != _robots.end())
    { return itr->second; }
    return NULL;
}

bool BotApplication::DeleteBot(int nID)
{
    CSALocker lock( _lockRobots );
	ItrRobotContainer iter = _robots.find(nID);
	if (iter == _robots.end())
	{ return false; }

	/*UnRegisterNode((*iter).second);*/
	_robots.erase(iter);
	return true;
}

void BotApplication::ShowBotCountInformation()
{
    // 显示逻辑    
    if ( !_lastShowTime.DoneTimer( HQ_TimeGetTime() ) )
    { return; }

    // 机器人数量和地图分布，坐标，错误信息 初始化就应该显示当前数量
    LMsgShowAllRobotInfo MsgShowAllBotInfo;
    if ( GetAllBotInfo(MsgShowAllBotInfo) )
    {
        theApp.PushMessage( &MsgShowAllBotInfo ); // 发送消息给Ui
        m_mapMapDistributing.clear();
    }

    // 每X秒通知Ui显示属性 Begin
	BaseRobot* pRobot = GetBot(GetRobotID());
    if (pRobot == NULL)
    { return;}

	LMsgShowRobotInfo msg;
	msg.BotID = pRobot->GetBotID();
	// 给GMsgShowRobotInfo消息赋值
	msg.dwStartTime =pRobot->m_xMsgStatistician.GetStartTime();
	msg.ExecuteActNum = pRobot->m_xMsgStatistician.GetLoopCount();
	// 发送消息
	msg.totalSendMsgNum = pRobot->m_xMsgStatistician.GetMsgSendCount();
	msg.SendMsgSize = pRobot->m_xMsgStatistician.GetMsgSendSize();
	// 接收消息
	msg.totalReceiveMsgNum = pRobot->m_xMsgStatistician.GetMsgRecvCount();
	msg.ReceiveMsgSize = pRobot->m_xMsgStatistician.GetMsgRecvSize();
	// 单次循环发送/接收情况
	msg.MinSingleSendMsgNum  = pRobot->m_xMsgStatistician.m_xMinSendInfo.dwCount;
	msg.MinSingleSendMsgSize = pRobot->m_xMsgStatistician.m_xMinSendInfo.dwSize;
	msg.MaxSingleSendMsgNum  = pRobot->m_xMsgStatistician.m_xMaxSendInfo.dwCount;
	msg.MaxSingleSendMsgSize = pRobot->m_xMsgStatistician.m_xMaxSendInfo.dwSize;
	msg.MinSingleRecvMsgNum  = pRobot->m_xMsgStatistician.m_xMinRecvInfo.dwCount;
	msg.MinSingleRecvMsgSize = pRobot->m_xMsgStatistician.m_xMinRecvInfo.dwSize;
	msg.MaxSingleRecvMsgNum  = pRobot->m_xMsgStatistician.m_xMaxRecvInfo.dwCount;
	msg.MaxSinglerecvMsgSize = pRobot->m_xMsgStatistician.m_xMaxRecvInfo.dwSize;
	msg.MonsterMum			 = pRobot->m_xMsgStatistician.m_dwMonsterNum;			//luo.qin 3.18
	// 每X秒通知Ui显示属性 End

	// 最大最小收发消息
	if ( !pRobot->m_xMsgStatistician.m_xMinSendInfo.vecMsgInfo.empty() )
	{
		std::copy( pRobot->m_xMsgStatistician.m_xMinSendInfo.vecMsgInfo.begin(), pRobot->m_xMsgStatistician.m_xMinSendInfo.vecMsgInfo.end(), msg.vecMinSendMsgInfo );
	}

	if ( !pRobot->m_xMsgStatistician.m_xMaxSendInfo.vecMsgInfo.empty() )
	{
		std::copy( pRobot->m_xMsgStatistician.m_xMaxSendInfo.vecMsgInfo.begin(), pRobot->m_xMsgStatistician.m_xMaxSendInfo.vecMsgInfo.end(), msg.vecMaxSendMsgInfo );
	}

	if ( !pRobot->m_xMsgStatistician.m_xMinRecvInfo.vecMsgInfo.empty() )
	{
		std::copy( pRobot->m_xMsgStatistician.m_xMinRecvInfo.vecMsgInfo.begin(), pRobot->m_xMsgStatistician.m_xMinRecvInfo.vecMsgInfo.end(), msg.vecMinRecvMsgInfo );
	}

	if ( !pRobot->m_xMsgStatistician.m_xMaxRecvInfo.vecMsgInfo.empty() )
	{
		std::copy( pRobot->m_xMsgStatistician.m_xMaxRecvInfo.vecMsgInfo.begin(), pRobot->m_xMsgStatistician.m_xMaxRecvInfo.vecMsgInfo.end(), msg.vecMaxRecvMsgInfo );
	}
	// 所有消息总数
	map<DWORD, MsgStatistician::Msg_Info_>::iterator iterBegin = pRobot->m_xMsgStatistician.m_mapMsgSendCount.begin();
	map<DWORD, MsgStatistician::Msg_Info_>::iterator iterEnd   = pRobot->m_xMsgStatistician.m_mapMsgSendCount.end();
	for ( int i=0; iterBegin != iterEnd; ++iterBegin, ++i )
	{
		msg.mapMsgSendCount[i] = iterBegin->second;
	}

	iterBegin = pRobot->m_xMsgStatistician.m_mapMsgRecvCount.begin();
	iterEnd   = pRobot->m_xMsgStatistician.m_mapMsgRecvCount.end();
	for ( int i=0; iterBegin != iterEnd; ++iterBegin, ++i )
	{
		msg.mapMsgRecvCount[i] = iterBegin->second;
	}
	// 连接状态 ip port 
	msg.strIp = pRobot->_targetGateIp;
	msg.wPort = pRobot->_targetGatePort;
	msg.nState = pRobot->GetBotState();
//	msg.dwError = pRobot->GetLoginErrorCode();
	msg.bConnect = pRobot->IsConnectted();
	// Ping chat
	msg.dwPingTime = pRobot->GetPingTime();

	theApp.PushMessage( &msg );
}

void BotApplication::AddBotMapDistributing(std::string strMap)
{
	if (strMap.empty())
	{ return;}

	map<string, int>::iterator iter  = m_mapMapDistributing.find(strMap);
    
    if (iter != m_mapMapDistributing.end())
    {
    	++(*iter).second;
    }
    else
    {
        m_mapMapDistributing.insert(make_pair(strMap, 1));
    }
}


void BotApplication::SetBotSetInfo(SSetInfo *pSetInfo)
{
	if (m_pSetInfo == NULL)
	{
		m_pSetInfo = new SSetInfo();
	}

	if (m_pSetInfo != NULL && pSetInfo != NULL)
	{
		*m_pSetInfo = *pSetInfo;

		map<int, BaseRobot*>::iterator iter;
		map<int, BaseRobot*>::iterator begin = _robots.begin();
		map<int, BaseRobot*>::iterator end = _robots.end();

		for (iter = begin; iter != end; ++iter)
		{	
			(*iter).second->Init(pSetInfo);
		}
	}
}

//机器人均匀分散
void BotApplication::DisPerseBot(char* pszMap, int nCount)
{
	if (pszMap == NULL || nCount == 0)
	{
		return;
	}
    //假定每个地图分250个区块
    static const int s_nMapArea = 250;
    static int s_nAreaWidth = 0;
    static int s_nAreaHeight = 0;
    static const POINT s_xPoint = {70, 70};
    static const int s_MaxPointX = 150;
    static const int s_MaxPointY = 450;
    MapConfig::MapData* pMapData = theMapConfig.GetMapDataByName(pszMap);
    if (NULL == pMapData )
        return;
    if (pMapData->IsEctypeMap())
        return;

    s_nAreaWidth = pMapData->Row * CHUNK_SIZE ;  
    s_nAreaHeight = pMapData->Column * CHUNK_SIZE ;
	

	//每个区域多少机器人
	int nAreaCount = (nCount / s_nMapArea);

	////多余出来的机器人随即分布
	//int nSpilthCount = nCount % s_nMapArea;

	int nAreaIndex = 0;
	int nBotCount = 0;

	map<int,BaseRobot*>::iterator iter = _robots.begin();
	map<int,BaseRobot*>::iterator end = _robots.end();
	for ( ; iter != end; ++iter)
	{
		if (iter->second->GetBotState() == State_Play && iter->second->GetMapName() == pszMap)
		{				
			SAreaInfo xAreaInfo;

			xAreaInfo.nMap = iter->second->GetMapID();
			xAreaInfo.xPoint.x = s_xPoint.x + (nAreaIndex % 16) * s_nAreaHeight;
			xAreaInfo.xPoint.y = s_xPoint.y + (nAreaIndex / 16) * s_nAreaWidth;
            if (s_MaxPointX < xAreaInfo.xPoint.x)
                xAreaInfo.xPoint.x = s_MaxPointX;
            if (s_MaxPointY < xAreaInfo.xPoint.x)
                xAreaInfo.xPoint.x = s_MaxPointY;
			xAreaInfo.nRadius = s_nAreaWidth;

			int nType = iter->second->GetType();

			switch (nType)
			{
			case Bot_Attack:
				((CAttackBot*)iter->second)->SetAreaInfo(&xAreaInfo);
				break;
			case Bot_Normal:
				((CNormalBot*)iter->second)->SetAreaInfo(&xAreaInfo);
				break;
			case Bot_Fight:
				((CFightBot*)iter->second)->SetAreaInfo(&xAreaInfo);
				break;
            //case Bot_Guild:
            //    ((CGuildBot*)iter->second)->SetAreaInfo(&xAreaInfo);
            //    break;
            case Bot_Online:
                ((OnlineBot*)iter->second)->SetAreaInfo(&xAreaInfo);
                break;
            case Bot_Team:
                ((TeamBot*)iter->second)->SetAreaInfo(&xAreaInfo);
                break;
            case Bot_Ectype:
                ((EctypeBot*)iter->second)->SetAreaInfo(&xAreaInfo);
                break;
            case Bot_Brome:
                ((DromeBot*)iter->second)->SetAreaInfo(&xAreaInfo);
                break;
            case Bot_Login:
                ((CLoginBot*)iter->second)->SetAreaInfo(&xAreaInfo);
                break;
            //case Bot_Business:
            //    ((CBusinessBot*)iter->second)->SetAreaInfo(&xAreaInfo);
            //    break;
            case Bot_Firend:
                ((FirendBot*)iter->second)->SetAreaInfo(&xAreaInfo);
                break;
            case Bot_MatrixBot:
                ((CMatrixBot*)iter->second)->SetAreaInfo(&xAreaInfo);
			default:
				continue;
			}	

			++nBotCount;
			if (nBotCount > nAreaCount)
			{
				nBotCount  = 0;
				++nAreaIndex;
			}
		}
	}
}

bool BotApplication::GetAllBotInfo(LMsgShowAllRobotInfo& msg)
{
    if (_robots.empty())
    {
        msg.nTotalBotNum  = 0;
        msg.nOnlineBotNum = 0;
        msg.nAtkBotNum    = 0;
        msg.nMoveBotNum   = 0;

        for (int i=0; i<50; ++i)
        {
            memset( msg.BotMap[i].mapName, 0, sizeof(msg.BotMap[i].mapName) );
            msg.BotMap[i].BotInMapNum = 0;
        }
        return false;
    }
    
    msg.nTotalBotNum = _robots.size();
    ItrRobotContainer iterBegin = _robots.begin();
    ItrRobotContainer iterEnd   = _robots.end();

    msg.nOnlineBotNum = 0;
    msg.nAtkBotNum = 0;
    msg.nMoveBotNum = 0;
	msg.nTotalMonsterNum = 0;//luo.qin 4.8

    for (; iterBegin != iterEnd; ++iterBegin)
    {
        if (iterBegin->second == NULL)
        { continue;}

        msg.BotID = iterBegin->second->GetBotID();

        if ( iterBegin->second->GetBotState() == State_Play ) // 在线机器人总数
        {
            ++msg.nOnlineBotNum;
        }

        if ( iterBegin->second->GetType() == Bot_Attack ) // 攻击机器人
        {
            ++msg.nAtkBotNum;
        }

        if ( iterBegin->second->GetType() == Bot_Fly ) // MoveRobot是指FlyRobot
        {
            ++msg.nMoveBotNum;
        }

		msg.nTotalMonsterNum +=iterBegin->second->m_MonsterNum;
        AddBotMapDistributing( iterBegin->second->GetMapName() );
    }

    IterMapDistributing itMapBegin = m_mapMapDistributing.begin();
    IterMapDistributing itMapEnd   = m_mapMapDistributing.end();
    for ( int i=0; i<50, itMapBegin != itMapEnd; ++itMapBegin )
    {
        strcpy_s( msg.BotMap[i].mapName, itMapBegin->first.c_str() );
        msg.BotMap[i].BotInMapNum = itMapBegin->second;
        ++i;
    }

    // 设置机器人数量
    m_nOnLineBot      = msg.nOnlineBotNum;
    m_nAttackBotCount = msg.nAtkBotNum;
    m_nMoveBotCount   = msg.nMoveBotNum;

    return true;
}


bool BotApplication::SetBCreateMonster( bool bCreateMonster )
{
	return ( g_bCreateMonster = bCreateMonster );
}

bool BotApplication::SetBChangeEquip( bool bChangeEquip )
{
	return ( g_bChangeEquip = bChangeEquip );
}

bool BotApplication::SetBRandRide( bool bRandRide )
{
	return ( g_bRandRide = bRandRide );
}

bool BotApplication::SetBCountryFight( bool bCountryFight )
{
	return ( g_bCountryFight = bCountryFight );
}