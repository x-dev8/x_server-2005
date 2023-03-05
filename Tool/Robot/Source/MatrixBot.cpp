#include "Matrixbot.h"
#include "ItemDetail.h"
#include "DromeBot.h"
#include "MapConfig.h"
#include "ItemDetailConfig.h"

#define  RUNSTEPTIME  (1000)
#define  GAOJULIMAPID (1)
#define  SPACEBETWEEN (6)
#define BarginItemNum   (20)
// ������
#define TESTECTYPEMAPID 20
#define TESTECTYPEMAPPOSX 47
#define TESTECTYPEMAPPOSY 15
#define REQ_FLYTOMAP_SPANCE (60 * 1000)

#define Begin_Point_X 50 //����Lua�ű�����
#define Begin_Point_Y 50
#define BeginBotID    1001
#define XiaChunBeginBotID 4001
#define NaLanBeginBotID 7001
#define MuRongBeginBotID 10001
#define OtherCountryBeginBotID 13001 // ��Luaȡ��

//static int TianwenMapArray[15] = { 1, 2 ,3, 6, 98, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110 };
//static int XiaChunMapArray[15] = { 301, 302, 303, 306, 398, 401, 402, 403, 404, 405, 406, 407, 408, 409, 410 };
//static int NaLanMapArray[15]   = { 601, 602, 603, 606, 698, 701, 702, 703, 704, 705, 706, 707, 708, 709, 710 };
//static int MuRongMapArray[15]  = { 901, 902, 903, 904, 998, 1001, 1001, 1003, 1004, 1005, 1006, 1007, 1008, 1009, 1010 };

static int TianwenMapArray[15] = { 1, 2, 3, 4, 5, 6, 7, 8, 299 };

extern bool g_PlaySkill;			// �ͷż���
extern int  g_skillID;				// ����ID
extern bool g_BotMove;				// �ƶ�����
extern int  g_nBotMoveRange;		// �ƶ�����
extern bool g_BotPlayAttack;		// ȫ�ֹ�������
extern bool g_BotRide;				// ȫ��������
extern bool g_BotReloadLuaScript;	// ȫ�ֵ����¼���Lua�ű�����

extern bool g_bCreateMonster;		// ȫ�ֻ����˴������￪�� luo.qin 3.18
extern bool g_bChangeEquip;			// ȫ�ֻ����˻�װ���� luo.qin 3.21
extern bool g_bRandRide;			// ȫ�ֻ�������������� luo.qin 3.21	

// ��˲���ʱ���������������
#define OPERATION_SPACE (2*1000) // ��˲���ʱ����Ϊ2��
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
    // ��ʱ�ȷ���600��MatrixBot���ڴ������ڽ��д�ܣ���Ҫ�������С��������ѹ���������޸� 
    // ����:60 160 70 130
    // ʯ�ٴ� 70 130 80 160
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
    case EArmType_Mage: // ����
        {
            xMsg.stSkill = g_skillID; // g_skillIDΪ��Ϣ�д�������ȫ�ּ���ID
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
    CAttackBot::InitAttackSkill();	// ��ʼ������

    //InitPoint();
    //fPoint result = GetPoint();
    if (GetMapID() != GAOJULIMAPID && m_dwInitStartTime < HQ_TimeGetTime())
    {
        //FlyToMap(GAOJULIMAPID,result.x,result.y);
        m_dwInitStartTime = m_dwInitStartTime + 3000;
    }

    GetDrome();						// ��ʼ��ʱ���һƥ��
    LearnAllSkill();				// ѧϰ���м���
    // ������PKģʽ�ı䣬ʹ�þ�������˿��Ի��๥��
    MsgChangePKFlag xMsg;
    xMsg.shFlag = PKMode_Fight;
    SendMsg(&xMsg);
	//FlyToMap(100, 206, 305);		// ���ִ����λ��
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
        if (IsInArea(GetMapID(), iterBegin->m_vPos)) //��������Ĺ��ﲻ����
        {
            vecEnemy.push_back(&(*iterBegin));
        }
    }

    if (vecEnemy.empty())
    {
        return shTarget;
    }

    //���һ��Ŀ�� 
    int nRand = rand() % vecEnemy.size();
    shTarget = vecEnemy[nRand]->shPlayerID;
    //���������Ϣ
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

    if (AttackbotType == EAT_TestEctypeType) // ���Ը�����
    {
        if (GetMapID() != TESTECTYPEMAPID)
        {
            if (HQ_TimeGetTime() - m_ReqFlyTime > REQ_FLYTOMAP_SPANCE)
            {
                // ȥNpc�����npc˵��,�ɽ�ȥ
                SetTipsInfo("����ɵ�����");
                //FlyToMap(TESTECTYPEMAPID,TESTECTYPEMAPPOSX,TESTECTYPEMAPPOSY);
                m_ReqFlyTime = HQ_TimeGetTime();
                UpdateBotState();
            }
            return;
        }
    }
    else
    {
        //���������� �ȷɵ�������
        if (!IsInArea(GetMapID(), m_vPos))
        {
            MoveToArea();
            return;
        }
    }

    if (m_shTargetID == EATI_InitAttackTargetId)
    {
        m_shTargetID = LockTarget();	 //û��Ŀ�����ҹ���Ŀ��
        if (m_shTargetID != EATI_InitAttackTargetId)
        {
            //��������
            MsgLockTarget msg;
            msg.stWho = m_shTargetID;
            SendMsg(&msg);

            //����漴Ҫ�ƶ�ȥ��Ŀ��
            ClearMovePos();

            SetTipsInfo("����Ŀ��");

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
                    // 10��ûû��ˢ�¹������û�й���
                    if (0 == m_WaitUpdateSightTime)
                        m_WaitUpdateSightTime = HQ_TimeGetTime();

                    if (HQ_TimeGetTime() - m_WaitUpdateSightTime > 10*1000)
                    {
                        LOG_MESSAGE(LogObject,LOG_PRIORITY_ERROR,"�����ˡ�%s���ڸ�����Ұ��Χ��û�й���",GetBotRoleName());
                        SetBotState(State_End);
                        SetTipsInfo("��Ұ��Χ��û�й���");
                    }
                    //else
                        //Move();
                }
                return;
            }

            //Move();			//û���ҵ�����
        }
    }

    //�Ѿ��ҵ�Ŀ����
    if (m_shTargetID != EATI_InitAttackTargetId)
    {
        PlayerInfo* pInfo = GetLockPlayerInfo(m_shTargetID);
        if(pInfo == NULL)
        {
            m_shTargetID = EATI_InitAttackTargetId; //�����Ѿ����� ������Ұ����
            m_dwLastUseSkillTime = 0;

            SetTipsInfo("Ŀ�겻����");

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

        //��ʼ����
        CAttackBot::AttackEnemy();
    }

    BaseRobot::PlayGame();
}

void CMatrixBot::InitFirstPlayGame()
{
    // ʹ��Lua���趨��ʼֵ�����ѧ���ܵȳ�ʼ������
#if defined(Lua_Bind)
    LuaBindManager::LuaScriptConfig* pLuaScriptCfg = theLuaManager.GetLuaScriptById(Bot_MatrixBot);
    luaScript.Bind(); // ������
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
    // TODO:LuaPlus����
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

    bInit = false; //��ʼ��һ��
}

void CMatrixBot::PlayGame()
{
    // ������¼���֮����Ҫ�ٴ�����InitFirstPlayGame
    // bInit������Ϊtrue���Ӷ�ʹ���ļ����¼���
    if ( GetbInit() )
    {
		InitPlayGame();
		//InitFirstPlayGame();
		//RandChangeEquip();
		//if ( GetMapID() != 8 )
		//{
		//	//FlyToMap(8, 34, 35);    // ���ִ����λ��
		//	FlyToMap(8, Monster_Map_xPos, Monster_Map_yPos);
		//	bInit = false;
		//}
    }
    //////////////////////////////////////////////////////////////////////////
    if (HQ_TimeGetTime() - RunTime <= RUNSTEPTIME)
    {
        return;
    }

	//ÿ3�����Ӧ�Ļ����˴���һ��Monster luo.qin 3.17
	if ( GameTime::IsPassCurrentTime( m_LastCreateTime, 2 * 1000 ) && g_bCreateMonster )//��֤�������Ѿ��ɵ�ָ����ͼ
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
    
    if ( !bGetPos ) // �õ���ǰ������
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

    if ( g_BotMove ) // �ƶ���ȫ�ֿ��ƿ���
    {
        if ( !PlayBotMove() )//�ƶ�
        {
            return;
        }
    }

    AddHpTimer();  //��Ѫ
    
    if (g_BotPlayAttack) //ȫ�ֵĹ�������
    {
        PlayAttack(); 
    }

    if ( !bIsRide )
    {
        PlayMountTimer(); // �ٻ�����
    }
    
    PlaySkillTimer(); // ��ʱ�ͷż���

    RunTime = HQ_TimeGetTime() + RUNSTEPTIME;
}

bool CMatrixBot::ergodicItemBag(int nItemID) // �����������ж����޴�ID��װ��
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
    SCharItem* pChar = this->m_CharInfo.visual.GetVisual(EEquipPartType_Helmet);    // �ж�ͷ��������У��򲻴�װ��
    if (pChar->itembaseinfo.ustItemID == 0)  // �������û��װ��
    {
        return false;   // ûװ��
    }
    else
    {
        return true;    // ��װ��
    }
    return false;
}

void CMatrixBot::AddHpTimer()
{
    _addHpTime.StartTimer( HQ_TimeGetTime(), 5*1000); // 5���Ѫ
    if ( _addHpTime.DoneTimer(HQ_TimeGetTime()) )
    {
        AddHp();
    }
}

void CMatrixBot::PlaySkillByID(int nSkillID) //����ֻ��������Ŀ��ļ����ͷ�
{
    MsgReqSkillAttack xMsg;
    xMsg.stSkill = nSkillID;
    xMsg.bCharTarget = true;
    xMsg.stWho = GetBotShortId(); // 2305�����ܸ��Լ��ͷ�
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
    
    SetSleep(2000); // �ȴ���ƥ��ս��Ϣ��ʱ

    CItemDetail::SItemSkill* pSkill = theItemDetailConfig.GetSkillByID(2305, 1);
    if (pSkill == NULL)
    { return;}

    DWORD AllCoolDownTime = pSkill->dwSkillCoolDownTime + pSkill->ustPrepTime + pSkill->dwCommonCoolDownTime; // ����cd + ����ʱ�� + ����cdʱ��
    _RideTime.StartTimer(HQ_TimeGetTime(), AllCoolDownTime);
    if ( _RideTime.DoneTimer(HQ_TimeGetTime()) )
    {
        PlaySkillByID(2305); // �ͷ��ٻ����＼��
        bIsRide = true;
    }

    //MsgChangeDrome DisDrome;
    //DisDrome.nDromeID = -1; // ������-1
    //SendMsg(&DisDrome);
}

void CMatrixBot::PlaySkillTimer()
{
    if ( !g_PlaySkill ) //�߼��߳����ͷż��ܵĿ��ƿ���
    { return;}

    CItemDetail::SItemSkill* pSkill = theItemDetailConfig.GetSkillByID(g_skillID, 1);
    if (pSkill == NULL)
    { return;}

    DWORD AllCoolDownTime = pSkill->dwSkillCoolDownTime + pSkill->ustPrepTime + pSkill->dwCommonCoolDownTime; // ����cd + ����ʱ�� + ����cdʱ��
    _PlaySkillTime.StartTimer( HQ_TimeGetTime(), AllCoolDownTime);

    if ( _PlaySkillTime.DoneTimer(HQ_TimeGetTime()) )
    {
        PlaySkill();
    }
}

bool CMatrixBot::PlayBotMove()
{
    MoveTargetPos.x = selfPos.x + g_nBotMoveRange; //g_nBotMoveRange ��Ϣ��������ֵ
    MoveTargetPos.y = selfPos.y;
    MoveTargetPos.z = selfPos.z;
    if (!bMoveBack) //�ƶ���x+g_nBotMoveRange��Ŀ���
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
    else // �ƶ���ԭʼ��
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
    if ( bIsEquip ) // ����Ѿ�װ����return
    { return;}

    for (int i = 0;i <= BarginItemNum;++i)
    {
        if (m_pItemBag[i].itembaseinfo.ustItemID != ErrorUnsignedShortID)
        {
            CItemDetail::SItemCommon* pItem = GettheItemDetail().GetItemByID(m_pItemBag[i].itembaseinfo.ustItemID);
            if ( NULL != pItem && ( pItem->ucItemType == CItemDetail::ITEMTYPE_WEAPON || pItem->ucItemType == CItemDetail::ITEMTYPE_ARMOUR ) ) // ������������߷���
            {
                MsgEquip xMsg;
                xMsg.ustPackIndex = i;

                SendMsg(&xMsg);
                SetSleep(2000);
                //�����˴��ϱ��������е�װ��
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
    //if (1000 < nAccount && nAccount <= 4000) // ����
    //{
    //    nIndex = (nAccount - BeginBotID) / 200;
    //    return TianwenMapArray[nIndex];
    //}
    //else if ( 4000 < nAccount && nAccount <= 7000 ) // �Ĵ�
    //{
    //    nIndex = (nAccount - XiaChunBeginBotID) / 200;
    //    return XiaChunMapArray[nIndex];
    //}
    //else if ( 7000 < nAccount && nAccount <= 10000 ) // Ľ��
    //{
    //    nIndex = (nAccount - MuRongBeginBotID) / 200;
    //    return MuRongMapArray[nIndex];
    //}
    //else if ( 10000 < nAccount && nAccount <= 13000 ) // ����
    //{
    //    nIndex = (nAccount - NaLanBeginBotID) / 200;
    //    return NaLanMapArray[nIndex];
    //}

	if (1000 < nAccount && nAccount <= 13000) // ����
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

    int nSpaceBetween = SPACEBETWEEN; // �õ������˼��
    int BeginID = (AccountID/1000) * 1000 + 1;  // ��ʼID = ÿһ��ID��ǧλȡ�� + 1
    BotPonit.x = Begin_Point_X + ((AccountID - BeginID ) * nSpaceBetween ) % widthMatrix ;
    BotPonit.y = Begin_Point_Y + nSpaceBetween * ( ((AccountID - BeginID) * nSpaceBetween ) / widthMatrix );

    return BotPonit;
}

//��ȡ�̶������������BOT���� luo.qin 3.18
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
// ������������˲���
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

    int operation = rand()%EDO_TotalOperation; // �����������ս������Ϣ
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
            RemoveDrome(pResult->nIndex); // ���������ս������Ϣ
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
//        // ����ע��
//        metaTableObject.RegisterObjectDirect( "InitPlayGame",   (CMatrixBot*)0, CMatrixBot::InitPlayGame    );
//        metaTableObject.RegisterObjectDirect( "PlaySkill",      (CMatrixBot*)0, CMatrixBot::PlaySkill       );
//        //metaTableObject.RegisterObjectDirect( "PlaySkillByID",  (CMatrixBot*)0, CMatrixBot::PlaySkillByID   );
//        metaTableObject.RegisterObjectDirect( "LearnSkill",     (CMatrixBot*)0, CMatrixBot::LearnSkill      );
//        metaTableObject.RegisterObjectDirect( "FlyToMatrixPos", (CMatrixBot*)0, CMatrixBot::FlyToMatrixPos  );
//        metaTableObject.RegisterObjectDirect( "EquipItem",      (CMatrixBot*)0, CMatrixBot::EquipItem       );
//        metaTableObject.RegisterObjectDirect( "GetSelfProfession", (CMatrixBot*)0, CMatrixBot::GetSelfProfession() );
//        metaTableObject.RegisterObjectDirect( "ergodicItemBag", (CMatrixBot*)0, CMatrixBot::ergodicItemBag  );
//        // TODO:����������ע��
//
//        LuaObject MatrixBotCoreObj = m_LuaScript->BoxPointer(this);
//        MatrixBotCoreObj.SetMetaTable(metaTableObject);
//        m_LuaScript->GetGlobals().SetObject("MatrixBot", MatrixBotCoreObj);
//
//        if ( !m_LuaScript->LoadFile(szScriptName) )
//        {
//            bLuaScriptLoaded = true;
//            m_LuaScript->Call(0, 0);
//            AfxMessageBox(_T("����Robot.lua�ļ�ʧ�ܣ������ļ�!"));
//        }
//    }
//    catch (LuaPlus::LuaException& e)
//    {
//        LOG_MESSAGE(LogObject, LOG_PRIORITY_ERROR, "MatrixBot InitScript Failed:%s", e.GetErrorMessage());
//        bLuaScriptLoaded = false; // ��������쳣�������ʧ��
//    }
//}