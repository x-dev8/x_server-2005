#include "Matrixbot.h"
#include "ItemDetail.h"
#include "DromeBot.h"
#include "MapConfig.h"
#include "ItemDetailConfig.h"

#define  RUNSTEPTIME  (1000)
#define  GAOJULIMAPID (1)
#define  SPACEBETWEEN (6)
#define BarginItemNum   (20)
// 练功房
#define TESTECTYPEMAPID 20
#define TESTECTYPEMAPPOSX 47
#define TESTECTYPEMAPPOSY 15
#define REQ_FLYTOMAP_SPANCE (60 * 1000)

#define Begin_Point_X 50 //放在Lua脚本中了
#define Begin_Point_Y 50
#define BeginBotID    1001
#define XiaChunBeginBotID 4001
#define NaLanBeginBotID 7001
#define MuRongBeginBotID 10001
#define OtherCountryBeginBotID 13001 // 被Lua取代

//static int TianwenMapArray[15] = { 1, 2 ,3, 6, 98, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110 };
//static int XiaChunMapArray[15] = { 301, 302, 303, 306, 398, 401, 402, 403, 404, 405, 406, 407, 408, 409, 410 };
//static int NaLanMapArray[15]   = { 601, 602, 603, 606, 698, 701, 702, 703, 704, 705, 706, 707, 708, 709, 710 };
//static int MuRongMapArray[15]  = { 901, 902, 903, 904, 998, 1001, 1001, 1003, 1004, 1005, 1006, 1007, 1008, 1009, 1010 };

static int TianwenMapArray[15] = { 1, 2, 3, 4, 5, 6, 7, 8, 299 };

extern bool g_PlaySkill;			// 释放技能
extern int  g_skillID;				// 技能ID
extern bool g_BotMove;				// 移动开关
extern int  g_nBotMoveRange;		// 移动距离
extern bool g_BotPlayAttack;		// 全局攻击开关
extern bool g_BotRide;				// 全局骑马开关
extern bool g_BotReloadLuaScript;	// 全局的重新加载Lua脚本开关

extern bool g_bCreateMonster;		// 全局机器人创建怪物开关 luo.qin 3.18
extern bool g_bChangeEquip;			// 全局机器人换装开关 luo.qin 3.21
extern bool g_bRandRide;			// 全局机器人随机骑马开关 luo.qin 3.21	

// 骑乘操作时间与最大坐骑数量
#define OPERATION_SPACE (2*1000) // 骑乘操作时间设为2秒
#define MAX_DROMENUM 3

CMatrixBot::ItrPointList CMatrixBot::itrPoint;
CMatrixBot::PointList CMatrixBot::Points;
bool CMatrixBot::IsInitPoint = false;

CMatrixBot::CMatrixBot():IsGetPoint(false),RunTime(HQ_TimeGetTime()),IsLearnSkill(false),dwMapLoadTime(0),bIsInitPlayGame(false),
                        OperationTime(HQ_TimeGetTime()), bIsFly(false), bMoveBack(false), bIsRide(false), bGetEquip(false), bIsEquip(false), bInit(true)
{
    m_BotType =Bot_MatrixBot;
    _CurPoint.x = 0;
    _CurPoint.y = 0;
    
    selfPos.x = 0;
    selfPos.y = 0;
    selfPos.y = 0;
    bGetPos = false;
    MoveTargetPos.x = 0.f;
    MoveTargetPos.y = 0.f;
    MoveTargetPos.z = 0.f;

	m_LastCreateTime = HQ_TimeGetTime();
    ControlTime = HQ_TimeGetTime();
}

CMatrixBot::~CMatrixBot()
{
}

bool CMatrixBot::InitPoint()
{
    if (IsInitPoint)
    {
        return false;
    }

    fPoint _fPoint;
    // 暂时先放置600个MatrixBot，在此区域内进行打架，如要扩大或缩小测试流量压力，则需修改 
    // 王城:60 160 70 130
    // 石碣村 70 130 80 160
    for (int i = 30;i<=230;i+=SPACEBETWEEN) 
    {
        _fPoint.x = (float)i;
        for (int n = 30;n <= 230;n+=2)//SPACEBETWEEN)
        {
            _fPoint.y = (float)n;
            Points.push_back(_fPoint);
        }
    }

    if (!IsInitPoint)
    {
        itrPoint = Points.begin();
    }

    IsInitPoint = true;
    return true;
}

void CMatrixBot::SetAreaInfo(SAreaInfo *pAreaInfo)
{
    IsInitPoint = false;
    CAttackBot::SetAreaInfo(pAreaInfo);
}

void CMatrixBot::PlaySkill()
{    
    MsgReqSkillAttack xMsg;
    xMsg.bCharTarget = true;
    xMsg.stWho = GetBotShortId();
    switch (GetSelfProfession())
    {
    case EArmType_Warrior:
        {
            xMsg.stSkill = 1011;
        }
    	break;
    case EArmType_Mage: // 法王
        {
            xMsg.stSkill = g_skillID; // g_skillID为消息中传过来的全局技能ID
            xMsg.bCharTarget = false;
            xMsg.stWho = -1;
            xMsg.vPos.x = GetPosX();
            xMsg.vPos.y = GetPosY();
            xMsg.vPos.z = 0.f;
        }
        break;
    case EArmType_Taoist:
        {
            xMsg.stSkill = 1103;
        }
        break;
    case EArmType_Assassin:
        {
            xMsg.stSkill = 1103;
        }
        break;
    case EArmType_Hunter:
        {
            xMsg.stSkill = 1131;
        }
        break;
    }
    xMsg.chSkillCount = 1;
    xMsg.stSkillLevel = 1;
    SendMsg(&xMsg);
}

void CMatrixBot::LearnSkill(int id)
{
    MsgChat msg;
    char temp[100];
    sprintf_s(temp,sizeof(temp),"/LearnSkill %d 1",id);
    msg.SetString(temp);
    SendMsg(&msg);
    SetSleep(2000);
    IsLearnSkill = true;
}

void CMatrixBot::InitPlayGame()
{
    CAttackBot::InitAttackSkill();	// 初始化技能

    //InitPoint();
    //fPoint result = GetPoint();
    if (GetMapID() != GAOJULIMAPID && m_dwInitStartTime < HQ_TimeGetTime())
    {
        //FlyToMap(GAOJULIMAPID,result.x,result.y);
        m_dwInitStartTime = m_dwInitStartTime + 3000;
    }

    GetDrome();						// 初始化时获得一匹马
    LearnAllSkill();				// 学习所有技能
    // 机器人PK模式改变，使得矩阵机器人可以互相攻击
    MsgChangePKFlag xMsg;
    xMsg.shFlag = PKMode_Fight;
    SendMsg(&xMsg);
	//FlyToMap(100, 206, 305);		// 新手村马的位置
    bIsInitPlayGame = true;
}

GameObjectId CMatrixBot::LockTarget()
{

    GameObjectId shTarget = -1;

    vector<PlayerInfo*> vecEnemy;

    IterPlayerInfoContainer iterBegin = m_listPlayerList.begin();
    IterPlayerInfoContainer iterEnd  = m_listPlayerList.end();

    for ( ; iterBegin != iterEnd; ++iterBegin)
    {
        if (IsInArea(GetMapID(), iterBegin->m_vPos)) //在区域外的怪物不攻击
        {
            vecEnemy.push_back(&(*iterBegin));
        }
    }

    if (vecEnemy.empty())
    {
        return shTarget;
    }

    //随机一个目标 
    int nRand = rand() % vecEnemy.size();
    shTarget = vecEnemy[nRand]->shPlayerID;
    //请求怪物信息
    MsgQueryCharInfo query;
    query.stChar = shTarget;
    SendMsg(&query);  		

    return shTarget;
}

PlayerInfo* CMatrixBot::GetLockPlayerInfo(GameObjectId shID)
{
    return GetPlayer(shID);
}

void CMatrixBot::PlayAttack()
{
    if (GetBotHP() <= 0)
    {
        return;
    }

    if (AttackbotType == EAT_TestEctypeType) // 测试副本用
    {
        if (GetMapID() != TESTECTYPEMAPID)
        {
            if (HQ_TimeGetTime() - m_ReqFlyTime > REQ_FLYTOMAP_SPANCE)
            {
                // 去Npc那里和npc说话,飞进去
                SetTipsInfo("请求飞到副本");
                //FlyToMap(TESTECTYPEMAPID,TESTECTYPEMAPPOSX,TESTECTYPEMAPPOSY);
                m_ReqFlyTime = HQ_TimeGetTime();
                UpdateBotState();
            }
            return;
        }
    }
    else
    {
        //不在区域内 先飞到区域内
        if (!IsInArea(GetMapID(), m_vPos))
        {
            MoveToArea();
            return;
        }
    }

    if (m_shTargetID == EATI_InitAttackTargetId)
    {
        m_shTargetID = LockTarget();	 //没有目标先找攻击目标
        if (m_shTargetID != EATI_InitAttackTargetId)
        {
            //锁定怪物
            MsgLockTarget msg;
            msg.stWho = m_shTargetID;
            SendMsg(&msg);

            //清除随即要移动去的目标
            ClearMovePos();

            SetTipsInfo("锁定目标");

            m_dwLockTargetTime = HQ_TimeGetTime();
        }
        else
        {
            if (m_BotType == Bot_Fight)
            {
                //Move();
                return;
            }

            if (AttackbotType == EAT_TestEctypeType)
            {
                if (m_bLoadMapOver)
                {
                    // 10秒没没有刷新怪物，就是没有怪物
                    if (0 == m_WaitUpdateSightTime)
                        m_WaitUpdateSightTime = HQ_TimeGetTime();

                    if (HQ_TimeGetTime() - m_WaitUpdateSightTime > 10*1000)
                    {
                        LOG_MESSAGE(LogObject,LOG_PRIORITY_ERROR,"机器人【%s】在副本视野范围内没有怪物",GetBotRoleName());
                        SetBotState(State_End);
                        SetTipsInfo("视野范围内没有怪物");
                    }
                    //else
                        //Move();
                }
                return;
            }

            //Move();			//没有找到怪物
        }
    }

    //已经找到目标了
    if (m_shTargetID != EATI_InitAttackTargetId)
    {
        PlayerInfo* pInfo = GetLockPlayerInfo(m_shTargetID);
        if(pInfo == NULL)
        {
            m_shTargetID = EATI_InitAttackTargetId; //怪物已经死了 不在视野中了
            m_dwLastUseSkillTime = 0;

            SetTipsInfo("目标不存在");

            if (AttackbotType == EAT_TestEctypeType )
            {
                if (GetMapID() != Safe_Map_Id)
                {
                    if (HQ_TimeGetTime() - m_ReqFlyTime > REQ_FLYTOMAP_SPANCE)
                    {
                        //FlyToMap(Safe_Map_Id,Safe_Map_PosX,Safe_Map_PosY);
                        m_ReqFlyTime = HQ_TimeGetTime();
                    }
                }
            }
            return;
        }

        //开始攻击
        CAttackBot::AttackEnemy();
    }

    BaseRobot::PlayGame();
}

void CMatrixBot::InitFirstPlayGame()
{
    // 使用Lua来设定初始值，坐骑，学技能等初始化条件
#if defined(Lua_Bind)
    LuaBindManager::LuaScriptConfig* pLuaScriptCfg = theLuaManager.GetLuaScriptById(Bot_MatrixBot);
    luaScript.Bind(); // 函数绑定
    luaScript.LoadLuaScript(pLuaScriptCfg->ScriptPath.c_str());

    try
    {
        luabind::call_function<void>( luaScript.GetLuaState(), "LuaOnFirstPlayGame", this);
    }
    catch (luabind::error& e)
    {
        std::string luaErrorInfo = lua_tostring(luaScript.GetLuaState(), -1);
        LOG_MESSAGE(LogObject, LOG_PRIORITY_ERROR, "CMatrixBot call_function [LuaOnFirstPlayGame] error:%s Desc:%s", e.what(), luaErrorInfo.c_str());
        return;
    }
#elif defined(Lua_Plus)
    // TODO:LuaPlus操作
    LuaPlusManager::LuaScriptConfig* pLuaScriptCfg = theLuaManager.GetLuaScriptById(Bot_MatrixBot);
    luaScript.LoadLuaScript(pLuaScriptCfg->ScriptPath.c_str());
    try
    {
        LuaPlus::LuaStateOwner LuaOwner = luaScript.GetLuaStateOwner();
        LuaObject luaObject = LuaOwner->GetGlobal("LuaOnFirstPlayGame");
        if(luaObject.IsFunction())
        {
            luaScript.GetGlobalFunc("LuaOnFirstPlayGame")();
        }
    }
    catch (LuaPlus::LuaException &e)
    {
        LOG_MESSAGE( LogObject, LOG_PRIORITY_ERROR, "Robot script [%s]  LuaOnFirstPlayGame failed : Error[%s]", pLuaScriptCfg->ScriptPath.c_str(), e.GetErrorMessage() );
        return;
    }
#endif

    bInit = false; //初始化一次
}

void CMatrixBot::PlayGame()
{
    // 点击重新加载之后，需要再次运行InitFirstPlayGame
    // bInit被设置为true，从而使得文件重新加载
    if ( GetbInit() )
    {
		InitPlayGame();
		//InitFirstPlayGame();
		//RandChangeEquip();
		//if ( GetMapID() != 8 )
		//{
		//	//FlyToMap(8, 34, 35);    // 新手村马的位置
		//	FlyToMap(8, Monster_Map_xPos, Monster_Map_yPos);
		//	bInit = false;
		//}
    }
    //////////////////////////////////////////////////////////////////////////
    if (HQ_TimeGetTime() - RunTime <= RUNSTEPTIME)
    {
        return;
    }

	//每3秒给对应的机器人创建一个Monster luo.qin 3.17
	if ( GameTime::IsPassCurrentTime( m_LastCreateTime, 2 * 1000 ) && g_bCreateMonster )//保证机器人已经飞到指定地图
	{
		float fX = 0.0f, fY = fX ;

		int nMonsterNum = 5;
		if ( GetRandBotPos( fX, fY, GetMapID(), Monster_Map_xPos, Monster_Map_yPos ) && m_MonsterNum < 500 )
		{		

			//BotCreateMonster( (DWORD)GetBotDBID(), 100011, fX, fY );
			BotCreateMonster( (DWORD)GetBotDBID(), 100011 , Monster_Map_xPos, Monster_Map_yPos , nMonsterNum );
			m_MonsterNum += nMonsterNum;
			//m_xMsgStatistician.SetMonsterNum( m_MonsterNum );
			//m_xMsgStatistician.SetMonsterNum( ++m_MonsterNum );
			m_LastCreateTime = HQ_TimeGetTime();

		}
	}
	if ( GameTime::IsPassCurrentTime( m_dwReEquipItemTime, 8 * 1000 ) && g_bChangeEquip && m_dwReEquipItemTime != 0 )
	{
		ChangeEquip( GetBotDBID() );

		m_dwReEquipItemTime = 0;
		m_bCanEquip = false;
	}
    if (GetWhoKillMe() != -1)
    {
        int id = GetWhoKillMe();
        PlayerInfo* monster = GetMonster(id);
        if (NULL != monster)
        {
            if (m_shTargetID == EATI_InitAttackTargetId)
            {
                MsgLockTarget msg;
                msg.stWho = id;
                SendMsg(&msg);
                m_shTargetID = id;
            }
            else
            {
                AttackEnemy();
            }
        }
        return;
    }
    
    if ( !bGetPos ) // 得到当前的坐标
    {
        selfPos.x = GetBotPos().x;
        selfPos.y = GetBotPos().y;
        selfPos.z = 0.f;

        bGetPos = true;
    }

    if ( !DecideVisualSuit() )
    {
        EquipItem();
    }

    if ( g_BotMove ) // 移动的全局控制开关
    {
        if ( !PlayBotMove() )//移动
        {
            return;
        }
    }

    AddHpTimer();  //加血
    
    if (g_BotPlayAttack) //全局的攻击开关
    {
        PlayAttack(); 
    }

    if ( !bIsRide )
    {
        PlayMountTimer(); // 召唤坐骑
    }
    
    PlaySkillTimer(); // 设时释放技能

    RunTime = HQ_TimeGetTime() + RUNSTEPTIME;
}

bool CMatrixBot::ergodicItemBag(int nItemID) // 遍历背包，判断有无此ID的装备
{
    if (nItemID < 0)
    { return false;}

    for (int i = 0;i <= BarginItemNum;++i)
    {
        if (m_pItemBag[i].itembaseinfo.ustItemID != ErrorUnsignedShortID && m_pItemBag[i].itembaseinfo.ustItemID == nItemID)
        {
            return true;
        }
    }
    return false;
}

bool CMatrixBot::DecideVisualSuit()
{
    SCharItem* pChar = this->m_CharInfo.visual.GetVisual(EEquipPartType_Helmet);    // 判断头盔，如果有，则不穿装备
    if (pChar->itembaseinfo.ustItemID == 0)  // 如果手镯没有装备
    {
        return false;   // 没装备
    }
    else
    {
        return true;    // 有装备
    }
    return false;
}

void CMatrixBot::AddHpTimer()
{
    _addHpTime.StartTimer( HQ_TimeGetTime(), 5*1000); // 5秒回血
    if ( _addHpTime.DoneTimer(HQ_TimeGetTime()) )
    {
        AddHp();
    }
}

void CMatrixBot::PlaySkillByID(int nSkillID) //现在只限于无需目标的技能释放
{
    MsgReqSkillAttack xMsg;
    xMsg.stSkill = nSkillID;
    xMsg.bCharTarget = true;
    xMsg.stWho = GetBotShortId(); // 2305骑马技能给自己释放
    xMsg.vPos.x = GetPosX();
    xMsg.vPos.y = GetPosY();
    xMsg.vPos.z = 0.f;
    xMsg.chSkillCount = 1;
    xMsg.stSkillLevel = 1;
    SendMsg(&xMsg);
}

void CMatrixBot::PlayMountTimer()
{
    if ( !g_BotRide )
    { return;}

    if (SDromes.empty())
    { return;}

    MsgChangeDrome changedrome;
    changedrome.nIndex   = rand() % SDromes.size();
    changedrome.ucOpType = MsgChangeDrome::EOT_Active;
    changedrome.guid     = SDromes[changedrome.nIndex].GetMountGuid();
    SendMsg(&changedrome);
    
    SetSleep(2000); // 等待马匹出战消息延时

    CItemDetail::SItemSkill* pSkill = theItemDetailConfig.GetSkillByID(2305, 1);
    if (pSkill == NULL)
    { return;}

    DWORD AllCoolDownTime = pSkill->dwSkillCoolDownTime + pSkill->ustPrepTime + pSkill->dwCommonCoolDownTime; // 技能cd + 吟唱时间 + 公共cd时间
    _RideTime.StartTimer(HQ_TimeGetTime(), AllCoolDownTime);
    if ( _RideTime.DoneTimer(HQ_TimeGetTime()) )
    {
        PlaySkillByID(2305); // 释放召唤坐骑技能
        bIsRide = true;
    }

    //MsgChangeDrome DisDrome;
    //DisDrome.nDromeID = -1; // 下马，传-1
    //SendMsg(&DisDrome);
}

void CMatrixBot::PlaySkillTimer()
{
    if ( !g_PlaySkill ) //逻辑线程中释放技能的控制开关
    { return;}

    CItemDetail::SItemSkill* pSkill = theItemDetailConfig.GetSkillByID(g_skillID, 1);
    if (pSkill == NULL)
    { return;}

    DWORD AllCoolDownTime = pSkill->dwSkillCoolDownTime + pSkill->ustPrepTime + pSkill->dwCommonCoolDownTime; // 技能cd + 吟唱时间 + 公共cd时间
    _PlaySkillTime.StartTimer( HQ_TimeGetTime(), AllCoolDownTime);

    if ( _PlaySkillTime.DoneTimer(HQ_TimeGetTime()) )
    {
        PlaySkill();
    }
}

bool CMatrixBot::PlayBotMove()
{
    MoveTargetPos.x = selfPos.x + g_nBotMoveRange; //g_nBotMoveRange 消息传过来的值
    MoveTargetPos.y = selfPos.y;
    MoveTargetPos.z = selfPos.z;
    if (!bMoveBack) //移动到x+g_nBotMoveRange的目标点
    {
        if ( !MoveToPoint(MoveTargetPos) )
        {
            return false;
        }
        else
        {
            bMoveBack = true;
            return true;
        }
    }
    else // 移动到原始点
    {
        if ( !MoveToPoint(selfPos) )
        { 
            return false;
        }
        else
        { 
            bMoveBack = false;
            return true;
        }
    }

}

bool CMatrixBot::CheckWeapon()
{
    if(m_CharInfo.visual.equipitem[EEquipPartType_Weapon].itembaseinfo.ustItemID == ErrorUnsignedShortID)
    {
        return false;
    }
    return true;
}

void CMatrixBot::EquipItem()
{
    //if ( !_EquipTimer.DoneTimer(HQ_TimeGetTime()) )
    //{
    //    return;
    //}
    if ( bIsEquip ) // 如果已经装备，return
    { return;}

    for (int i = 0;i <= BarginItemNum;++i)
    {
        if (m_pItemBag[i].itembaseinfo.ustItemID != ErrorUnsignedShortID)
        {
            CItemDetail::SItemCommon* pItem = GettheItemDetail().GetItemByID(m_pItemBag[i].itembaseinfo.ustItemID);
            if ( NULL != pItem && ( pItem->ucItemType == CItemDetail::ITEMTYPE_WEAPON || pItem->ucItemType == CItemDetail::ITEMTYPE_ARMOUR ) ) // 如果是武器或者防具
            {
                MsgEquip xMsg;
                xMsg.ustPackIndex = i;

                SendMsg(&xMsg);
                SetSleep(2000);
                //机器人穿上背包中所有的装备
                //return; 
            }
        }
    }
    //_EquipTimer.StopTimer();
    bIsEquip = true;
}

CMatrixBot::fPoint CMatrixBot::GetPoint()
{
    if (IsGetPoint)
    {
        return _CurPoint;
    }
    if (itrPoint == Points.end())
    {
        itrPoint = Points.begin();
    }
    IsGetPoint = true;
    
    fPoint result;
    result.x =itrPoint->x;
    result.y =itrPoint->y;
    ++itrPoint;
    _CurPoint.x = result.x;
    _CurPoint.y = result.y;
    return result;
}

int CMatrixBot::GetCurrentMap()
{
    int nAccount = atoi(GetAccount());
    int nIndex = 0;
    //if (1000 < nAccount && nAccount <= 4000) // 天问
    //{
    //    nIndex = (nAccount - BeginBotID) / 200;
    //    return TianwenMapArray[nIndex];
    //}
    //else if ( 4000 < nAccount && nAccount <= 7000 ) // 夏淳
    //{
    //    nIndex = (nAccount - XiaChunBeginBotID) / 200;
    //    return XiaChunMapArray[nIndex];
    //}
    //else if ( 7000 < nAccount && nAccount <= 10000 ) // 慕容
    //{
    //    nIndex = (nAccount - MuRongBeginBotID) / 200;
    //    return MuRongMapArray[nIndex];
    //}
    //else if ( 10000 < nAccount && nAccount <= 13000 ) // 纳兰
    //{
    //    nIndex = (nAccount - NaLanBeginBotID) / 200;
    //    return NaLanMapArray[nIndex];
    //}

	if (1000 < nAccount && nAccount <= 13000) // 天问
	{
		nIndex = (nAccount - BeginBotID) / 200;
		return TianwenMapArray[nIndex];
	}

    return TianwenMapArray[0];
}

CMatrixBot::fPoint CMatrixBot::GetBotPos()
{
    fPoint BotPonit;

    //BeginX
    //    BeginY
    //    BeginId
    //    Space
    //    offset = AccountId - BeginId
    //    x = BeginX + ( offset * Space ) % (MapWidth - BeginX - 20)
    //    y = BeginY + ( offset * Space / MapWidth ) * Space

    int AccountID   = atoi(GetAccount());
    int widthMatrix = 150; //(int)width - Begin_Point_X - 50;

    MapConfig::MapData* pMapData = theMapConfig.GetMapDataById( GetCurrentMap() );
	if ( !pMapData )
	{
		//BotPonit.x = 34;
		//BotPonit.y = 35;
		BotPonit.x = Monster_Map_xPos;
		BotPonit.y = Monster_Map_yPos;
		return BotPonit;
	}
    int nMapWidth  = ChunckToTile( pMapData->Column ); 
    int nMapHeight = ChunckToTile( pMapData->Row);
    float width  = TileToFloat(nMapWidth);
    float height = TileToFloat(nMapHeight);

    int nSpaceBetween = SPACEBETWEEN; // 得到机器人间距
    int BeginID = (AccountID/1000) * 1000 + 1;  // 起始ID = 每一个ID的千位取整 + 1
    BotPonit.x = Begin_Point_X + ((AccountID - BeginID ) * nSpaceBetween ) % widthMatrix ;
    BotPonit.y = Begin_Point_Y + nSpaceBetween * ( ((AccountID - BeginID) * nSpaceBetween ) / widthMatrix );

    return BotPonit;
}

//获取固定区域内随机的BOT坐标 luo.qin 3.18
bool CMatrixBot::GetRandBotPos( float &fPosX, float &fPosY, DWORD dwMapID, float fBeginPosX, float fBeginPosY)
{

	int AccountID   = atoi(GetAccount());
	int widthMatrix = 95;

	MapConfig::MapData* pMapData = theMapConfig.GetMapDataById( GetMapID() );
	int nMapWidth  = ChunckToTile( pMapData->Column ); 
	int nMapHeight = ChunckToTile( pMapData->Row);
	float width  = TileToFloat(nMapWidth);
	float height = TileToFloat(nMapHeight);

	float fRectWidth = width - 2 * 50;
	float fRectHeight = height - 2 * 50;
	if ( fRectWidth >= 0 && fRectHeight >= 0 )
	{
		fPosX = fBeginPosX + theRand.rand32() % (int)fRectWidth;
		fPosY = fBeginPosY + theRand.rand32() % (int)fRectHeight;
		return true;
	}
	else
	{
		return false;
	}
}

bool CMatrixBot::Move2MatrixPoint()
{
    //fPoint result = GetPoint();
    fPoint result = GetBotPos();
    D3DXVECTOR3 xPos;
    xPos.x = result.x;
    xPos.y = result.y;
    xPos.z = 0;
    if (GetMapID() != GAOJULIMAPID )
    {
        //FlyToMap(GAOJULIMAPID,xPos.x,result.y);
        return false;
    }
    return MoveToPoint(xPos);
}



//////////////////////////////////////////////////////////////////////////
// 测试流量，骑乘操作
void CMatrixBot::GetDrome()
{
    MsgChat msg( MsgChat::CHAT_TYPE_NORMAL );

    char szMsg[dr_MaxChatString] = {0};

    int DromeId = rand()%35;
    DromeId += 700;
    _snprintf( szMsg, dr_MaxChatString - 1, "/AddMount %d",DromeId);

    msg.SetString(szMsg);
    SendMsg( &msg );
}

void CMatrixBot::RemoveDrome(int Drome)
{
    if (Drome < 0||Drome >= SDromes.size() || SDromes.empty())
    {
        return;
    }

    int Index = 0;

    for (ItrSDromeContainer itr = SDromes.begin();itr != SDromes.end();++itr)
    {
        if (Index == Drome)
        {
            SDromes.erase(itr);
            return;
        }
        Index++;
    }
}

void CMatrixBot::RandOperationDrome()
{
    if (HQ_TimeGetTime() - OperationTime < OPERATION_SPACE / 2)
    {
        return;
    }

    OperationTime = HQ_TimeGetTime();

    if (SDromes.size() < MAX_DROMENUM)
    {
        GetDrome();
        return;
    }

    MsgChangeDrome changedrome;
    changedrome.header.stID = GetBotShortId();

    int operation = rand()%EDO_TotalOperation; // 让坐骑随机出战或者休息
    switch(operation)
    {
    case EDO_Active:
        {
            changedrome.ucOpType = MsgChangeDrome::EOT_Active;
            changedrome.nIndex   = rand() % SDromes.size();
            changedrome.guid     = SDromes[changedrome.nIndex].GetMountGuid();
            SendMsg(&changedrome);
        }
        break;
    case EDO_UnActive:
        {
            changedrome.ucOpType = MsgChangeDrome::EOT_UnActive;
            changedrome.nIndex   = rand() % SDromes.size();
            changedrome.guid     = SDromes[changedrome.nIndex].GetMountGuid();
            SendMsg(&changedrome);
        }
        break;
    default:
        break;
    }
}

void CMatrixBot::SwitchMsg(Msg* pMsg)
{
    if (NULL == pMsg)
        return;

    switch(pMsg->GetType())
    {
    case MSG_GETMOUNT:
        OnMsgGetMount(pMsg);
        break;
    case MSG_ACK_RESULT:
        OnMsgAckResult(pMsg);
        break;
    case MSG_CHANGEDROME:
        OnMsgChangeDrome(pMsg);
        break;
    case MSG_ACKENTERWORLD:
        OnMsgAckEnterWorld(pMsg);
        break;
    default:
        break;
    }
    BaseRobot::SwitchMsg(pMsg);
}

void CMatrixBot::OnMsgGetMount(Msg* pMsg)
{
    MsgGetMount* pGetMsg = (MsgGetMount*) pMsg;
    if (pGetMsg->usResult == ER_Success)
    {
        for (int i= 0 ; i < ITEM_MOUNT_MAXCOUNT ; ++i)
        {
            if (pGetMsg->mount.baseInfo.id == 0)
            {
                break;
            }
            SMountItem* pSMountItem = FindMountByGuid(pGetMsg->mount.baseInfo.guid);
            if (pSMountItem == NULL)
                SDromes.push_back(pGetMsg->mount);
            else
                *pSMountItem = pGetMsg->mount;
        }
    }
}

void CMatrixBot::OnMsgAckResult(Msg* pMsg)
{
    MsgAckResult* result = (MsgAckResult*)pMsg;
    switch(result->result)
    {
    case ER_InFightNotActiveMount:
    case ER_InDeadNotActiveMount:
    case ER_IndexOutOfRange:
    case ER_NullPointer:
    case ER_InMountConfigNotExist:
    case ER_Failed:
    case ER_MountTakeLevelNotEnough:
    case ER_NotEnoughEnjoyment:
        return;
    }

    BaseRobot::OnMsgAckResult(pMsg);
}

void CMatrixBot::OnMsgChangeDrome( Msg* Msg)
{
    MsgChangeDrome* pResult = (MsgChangeDrome*)Msg;
    switch(pResult->ucOpType)
    {
    case MsgChangeDrome::EOT_Discard:
        {
            RemoveDrome(pResult->nIndex); // 测试坐骑出战或者休息
        }
        break;

    default:
        break;
    }
}

void CMatrixBot::OnMsgAckEnterWorld( Msg* pMsg )
{
    BaseRobot::OnMsgAckEnterWorld( pMsg );
    SDromes.clear();
    if (NULL != m_BromeItems)
    {
        for (int i= 0 ; i < ITEM_MOUNT_MAXCOUNT ; ++i)
        {
            if (m_BromeItems[i].baseInfo.id == 0)
            {
                break;
            }
            SMountItem* pSMountItem = FindMountByGuid(m_BromeItems[i].baseInfo.guid);
            if (NULL == pSMountItem)
                SDromes.push_back(m_BromeItems[i]);
            else
                *pSMountItem = m_BromeItems[i];
        }
    }
}

SMountItem* CMatrixBot::FindMountByGuid(__int64 FindGuid)
{
    if (FindGuid <= 0)
    {
        return NULL;
    }
    for (ItrSDromeContainer itr = SDromes.begin();itr != SDromes.end();++itr)
    {
        if (itr->baseInfo.guid == FindGuid)
        {
            return &(*itr);
        }
    }

    return NULL;
}

//////////////////////////////////////////////////////////////////////////
// Lua
//void CMatrixBot::LoadLuaScript(const char* szScriptName)
//{
//    if (szScriptName == NULL || *szScriptName == 0)
//    {
//        LOG_MESSAGE(LogObject, LOG_PRIORITY_ERROR, "Script %s Open failed! Please check !", *szScriptName);
//        return;
//    }
//
//    try
//    {
//        LuaObject metaTableObject;
//        metaTableObject = m_LuaScript->GetGlobals().CreateTable("MultiObjectMetaTable");
//        metaTableObject.SetObject("__index", metaTableObject);
//        // 函数注册
//        metaTableObject.RegisterObjectDirect( "InitPlayGame",   (CMatrixBot*)0, CMatrixBot::InitPlayGame    );
//        metaTableObject.RegisterObjectDirect( "PlaySkill",      (CMatrixBot*)0, CMatrixBot::PlaySkill       );
//        //metaTableObject.RegisterObjectDirect( "PlaySkillByID",  (CMatrixBot*)0, CMatrixBot::PlaySkillByID   );
//        metaTableObject.RegisterObjectDirect( "LearnSkill",     (CMatrixBot*)0, CMatrixBot::LearnSkill      );
//        metaTableObject.RegisterObjectDirect( "FlyToMatrixPos", (CMatrixBot*)0, CMatrixBot::FlyToMatrixPos  );
//        metaTableObject.RegisterObjectDirect( "EquipItem",      (CMatrixBot*)0, CMatrixBot::EquipItem       );
//        metaTableObject.RegisterObjectDirect( "GetSelfProfession", (CMatrixBot*)0, CMatrixBot::GetSelfProfession() );
//        metaTableObject.RegisterObjectDirect( "ergodicItemBag", (CMatrixBot*)0, CMatrixBot::ergodicItemBag  );
//        // TODO:其他函数的注册
//
//        LuaObject MatrixBotCoreObj = m_LuaScript->BoxPointer(this);
//        MatrixBotCoreObj.SetMetaTable(metaTableObject);
//        m_LuaScript->GetGlobals().SetObject("MatrixBot", MatrixBotCoreObj);
//
//        if ( !m_LuaScript->LoadFile(szScriptName) )
//        {
//            bLuaScriptLoaded = true;
//            m_LuaScript->Call(0, 0);
//            AfxMessageBox(_T("加载Robot.lua文件失败，请检查文件!"));
//        }
//    }
//    catch (LuaPlus::LuaException& e)
//    {
//        LOG_MESSAGE(LogObject, LOG_PRIORITY_ERROR, "MatrixBot InitScript Failed:%s", e.GetErrorMessage());
//        bLuaScriptLoaded = false; // 如果出现异常，则加载失败
//    }
//}