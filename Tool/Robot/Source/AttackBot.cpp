#include "stdafx.h"
#include "Bot.h"
#include "MessageDefine.h"
#include "ItemDetail.h"
#include "AttackBot.h"
#include "LogFileObjectName.h"
#include "ScriptManager.h"
#include "BotAppDataCenter.h"
#include "BotApplication.h"
#include "GameBot.h"
#pragma warning(disable:4389)

#define ATTACKTIME 60000
#define ATTACK_DISTANCE 1.5
#define NORMAL_ATTACK_ID 1
#define NORMAL_ATTACK_SPACE 2000

// ������
#define TESTECTYPEMAPID 20
#define TESTECTYPEMAPPOSX 47
#define TESTECTYPEMAPPOSY 15
#define REQ_FLYTOMAP_SPANCE (60 * 1000)

static int totalXinFaNum = 13;
static int s_nXinFaID_Warrior[13]  = {1001,1012,1015,1000,1003,1014,1008,1002,1010,1005,1009,1013,1011 };
static int s_nXinFaID_Taoist[13]   = {1051,1059,1064,1061,1058,1065,1052,1053,1062,1055,1056,1066,1063 };
static int s_nXinFaID_Assassin[13] = {1101,1113,1108,1116,1107,1115,1103,1112,1102,1106,1104,1114,1105 };
static int s_nXinFaID_Hunter[13]   = {1152,1154,1166,1155,1162,1165,1157,1153,1160,1161,1158,1164,1159 };
static int s_nXinFaID_Mage[13]     = {1201,1206,1205,1216,1207,1202,1215,1212,1209,1211,1210,1214,1208 };

static int s_nSkillID[] = {1002,1003,1004,1007,1020};
extern bool g_bChangeEquip;			// ȫ�ֻ����˻�װ���� luo.qin 3.21

CAttackBot::CAttackBot(void) : 
m_shTargetID(EATI_InitAttackTargetId),
m_dwLastUseSkillTime(0),
m_shAttackCount(0),
m_ReqFlyTime(HQ_TimeGetTime())
{
	//m_listPlayerList.clear();

	m_nSkillStep = 0;

	m_dwLastFlyTime = 0;

	m_vecAttackSkill.clear();
	m_mapUseSkill.clear();

    AttackbotType = EAT_NormalType;

    m_BotType = Bot_Attack;

	m_dwReEquipItemTime = HQ_TimeGetTime();

}

CAttackBot::CAttackBot(int AttackbotType) : 
m_shTargetID(EATI_InitAttackTargetId),
m_dwLastUseSkillTime(0),
m_shAttackCount(0),
m_ReqFlyTime(HQ_TimeGetTime())
{
    //m_listPlayerList.clear();

    m_nSkillStep = 0;

    m_dwLastFlyTime = 0;

    m_vecAttackSkill.clear();
    m_mapUseSkill.clear();

    if (AttackbotType != EAT_TestEctypeType)
    {
        AttackbotType = EAT_NormalType;
    }
    this->AttackbotType = AttackbotType;

    m_BotType = Bot_Attack;

	m_dwReEquipItemTime = HQ_TimeGetTime();
}

CAttackBot::~CAttackBot(void)
{
	m_listPlayerList.clear();
}

void CAttackBot::InitPlayGame(UINT mapid)
{
	BaseRobot::InitPlayGame(mapid);

	InitEquipItem();
	InitAttackSkill();

	//luo.qin 3.16ע��
	//fPoint xPos;
	//xPos.x = Begin_Map_xPos + theRand.rand32() % 50;
	//xPos.y = Begin_Map_yPos + theRand.rand32() % 50;
	//FlyToMap(8, 34, 35);    // ���ִ����λ��
	//FlyToMap(8, Monster_Map_xPos, Monster_Map_yPos);
}

void CAttackBot::SetAreaInfo(SAreaInfo *pAreaInfo)
{
	if (pAreaInfo  != NULL)
	{
		m_xAreaInfo.nMap = pAreaInfo->nMap;
		m_xAreaInfo.xPoint.x = pAreaInfo->xPoint.x;
		m_xAreaInfo.xPoint.y = pAreaInfo->xPoint.y;
		m_xAreaInfo.nRadius = pAreaInfo->nRadius;
	}		
}

bool CAttackBot::GetAreaInfo()
{
	if (m_xAreaInfo.nMap == -1 || m_xAreaInfo.nRadius == 0)
	{		
		return false;
	}

	return true;
}

void CAttackBot::PlayGame()
{
    std::string FullPath = theBotDataCenter.ScriptFilePath;
    FullPath += theBotDataCenter.ScriptFileName;
    uint32 result = theScriptManager.LoadScript(FullPath.c_str());
    if (ER_Success == result)
    {
        theScriptManager.ScriptFunctionVoid("PlayGame",this);
    }
	// �Ƿ��ǵ�һ�ε�½��Ϸ
	if ( GetbFirstInWorld() )
	{
		ReqAddPet( 701200, 1 , 0 );
		if ( SPets.size() != 0 )
		{
			MsgChangePet changeAck;
			changeAck.header.stID = GetBotShortId();
			changeAck.ucOpType    = MsgChangePet::EOT_Active;
			changeAck.nIndex      = 0;
			changeAck.guid        = SPets[changeAck.nIndex].baseInfo.guid;
			SendMsg( &changeAck );

			// ѧϰ�ķ�
			LearnXinFa( Enum_NoRand );
			SetbFirstInWorld( false );
		}	
	}

// 	Say("�������ȤŶ�������������������ۣ�");	//����
// 
// 	PlayAttack();
}


void CAttackBot::PlayAttack()
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
                Move();
                return;
            }

            if (AttackbotType == EAT_TestEctypeType)
            {
                if (m_bLoadMapOver)
                {
                    // 10��ûû��ˢ�¹������û�й���
                    if (0 == m_WaitUpdateSightTime)
                        m_WaitUpdateSightTime = HQ_TimeGetTime();

                    if (HQ_TimeGetTime() - m_WaitUpdateSightTime > 1*1000)
                    {
                        LOG_MESSAGE(LogObject,LOG_PRIORITY_ERROR,"�����ˡ�%s���ڸ�����Ұ��Χ��û�й���",GetBotRoleName());
                        SetBotState(State_End);
                        SetTipsInfo("��Ұ��Χ��û�й���");
                    }
                    else
                        Move();
                }
                return;
            }

			Move();			//û���ҵ�����
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

		//�ƶ�������
		if (!MoveToPoint(pInfo->m_vPos))
		{
			return;
		}
		//��ʼ����
		AttackEnemy();
	}
    BaseRobot::PlayGame();
}

void CAttackBot::OnMsgSeeAttack3( Msg* pMsg )
{
	//MsgSeeAttack3 *pSee3 = (MsgSeeAttack3 *)pMsg;

	//if( pSee3->stResultNum <= 0 )
	//	return;

	//if ( pSee3->stResultNum > 0 )
	//{
	//	for( int i = 0; i < pSee3->stResultNum; ++i )
	//	{
	//		if( m_shTargetID == pSee3->results[i].stTargetWho )
	//		{
	//			m_dwLockTargetTime = HQ_TimeGetTime();
	//		}

	//		//˭�������Ҿ͹���˭
	//		if( m_shPlayerId == pSee3->results[i].stTargetWho )
	//		{
	//			m_shTargetID = pSee3->results[i].stAttackerWho;
	//		}
	//	}
	//}

	BaseRobot::OnMsgSeeAttack3(pMsg);
}

//����false �����ƶ�
// bool CAttackBot::MoveToPoint(D3DXVECTOR3& xPos)
// {
// 	DWORD dwSpaceTime = HQ_TimeGetTime() - m_dwSpaceTime;
// 	if(dwSpaceTime < m_nMoveStep)
// 	{
// 		return false; //ʱ����δ��
// 	}
// 	m_dwSpaceTime = HQ_TimeGetTime();
// 
// 	m_vDir = xPos - m_vPos;
// 	float fDist = D3DXVec3Length(&m_vDir);
// 	
// 	if(fDist < ATTACK_DISTANCE)
// 	{
// 		m_dwSpaceTime = 0;
// 		//�������ÿ�ʼ����ʱ��
// 		return true;
// 	}
// 
// 	D3DXVec3Normalize( &m_vDir, &m_vDir );
// 	float fMoveDist = m_fMoveSpeed * m_nMoveStep / 1000;
// 
// 	m_vPos.x += fMoveDist * m_vDir.x;
// 	m_vPos.y += fMoveDist * m_vDir.y;
// 
// 	MsgPlayerMovingPosAndDirToServer xMsg;
// 	xMsg.header.stID = m_shPlayerId;
// 	xMsg.vPos.x = m_vPos.x;
// 	xMsg.vPos.y = m_vPos.y;
// 	xMsg.vPos.z = 0;
// 	xMsg.chDirX = (char)(m_vDir.x * 127);
// 	xMsg.chDirY = (char)(m_vDir.y * 127);
// 	xMsg.chDirZ = 0;
// 	xMsg.dwSendTime = HQ_TimeGetTime();
// 	SendMsg(&xMsg);
// 
// 	SetTipsInfo("��Ŀ���ƶ�");
// 
// 	return false;
// }

bool CAttackBot::AttackEnemy()
{
	DWORD dwSpaceTime = HQ_TimeGetTime() - m_dwMoveSpaceTime;
	if(dwSpaceTime < m_nMoveStep * 2)  //����ʱ������һ��
	{
		return false; //ʱ����δ��
	}
	m_dwMoveSpaceTime = HQ_TimeGetTime();

	if(HQ_TimeGetTime() - m_dwLockTargetTime > ATTACKTIME /*|| m_shAttackCount > 5*/) 
	{
		//����ʱ�仹δɱ��,������չ���
		m_shTargetID = EATI_InitAttackTargetId;
		m_shAttackCount = 0;
		return false;
	}
	
	DWORD dwSkillSpaceTime = 0;
	int nSkill = GetAttackSkill(dwSkillSpaceTime);
	if (nSkill == -1)
	{
		SetTipsInfo("�����ӳ�");
		return false;
	}

	if (nSkill == NORMAL_ATTACK_ID)   //��ͨ����
	{
		MsgAttackLockTarget	xMsg2;
		SendMsg(&xMsg2);	
		SetTipsInfo("��ͨ����");
	}
	else
	{        
        // �жϼ���Ŀ������

		MsgReqSkillAttack xMsg;
		xMsg.bCharTarget = true;
		xMsg.stWho = m_shTargetID;
		xMsg.stSkill = nSkill;
		xMsg.chSkillCount = 1;
		xMsg.stSkillLevel = 1;
		SendMsg(&xMsg);
		SetTipsInfo("���ܹ���");
	}

    if (GetBotHP() <= 1300) // ��ֹ�����˱���ɱ
    {
        AddHp(); // ��������Ѫ����
    }

	++m_shAttackCount;
	AddUseSkill(nSkill, dwSkillSpaceTime);

	return true;
}


GameObjectId CAttackBot::LockTarget()
{
	GameObjectId shTarget = -1;

	vector<PlayerInfo*> vecEnemy;

	list<PlayerInfo>::iterator iter = m_listMonsterList.begin();
	list<PlayerInfo>::iterator end = m_listMonsterList.end();
	for ( ; iter != end; ++iter)
	{
		if (IsInArea(GetMapID(), (*iter).m_vPos)) //��������Ĺ��ﲻ����
		{
			vecEnemy.push_back(&(*iter));
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

PlayerInfo* CAttackBot::GetLockPlayerInfo(GameObjectId shID)
{
	return GetMonster(shID);
}

//װ����Ʒ
void CAttackBot::InitEquipItem()
{
    if (NULL == m_pItemBag)
    {
        LOG_MESSAGE(LogObject,LOG_PRIORITY_ERROR,"��Ʒ����Ϊ��");
    }
	//���û������,��װ����Ʒ
	if (m_CharInfo.visual.equipitem[EEquipPartType_Weapon].itembaseinfo.ustItemID == ErrorUnsignedShortID)
	{
		for (int i = 0; i < ITEM_BAGMAX; ++i)
		{
			if (m_pItemBag[i].itembaseinfo.ustItemID != ErrorUnsignedShortID)
			{
				EquipItem(m_pItemBag[i].itembaseinfo.ustItemID, i);
			}			
		}
	}
}


//��ʼ����ɫ�Ĺ�������,
void CAttackBot::InitAttackSkill()
{
	if (!m_vecAttackSkill.empty())
	{
		return;
	}

    if (NULL == m_pSkillBag)
    {
        LOG_MESSAGE(LogObject,LOG_PRIORITY_ERROR,"���ܱ���Ϊ��");
        return;
    }
    
// 	for (int i = 0; i < sizeof(s_nSkillID)/sizeof(int); ++i)
// 	{
// 		CItemDetail::SItemSkill *pSkill = GettheItemDetail().GetSkillByID(m_pSkillBag[i].ustSkillID, m_pSkillBag[i].stSkillLevel);
//         //CItemDetail::SItemSkill *pSkill = GettheItemDetail().GetSkillByID(s_nSkillID[i], 1);
// 		if (pSkill != NULL)
// 		{
//             if ( pSkill->ustItemID >= 2300 && pSkill->ustItemID <= 2314)
//             {
//                 //��Ҫ��ҩ���� �Ͳɿ���
//                 continue;
//             }
// 			if (/*pSkill->easyusedata.bMagicSkill && */pSkill->easyusedata.bSkillWithDamage)
// 			{
// 				AttackSkill xAttackSkill;
// 				xAttackSkill.shID = m_pSkillBag[i].ustSkillID;
// 				xAttackSkill.dwSpaceTime = pSkill->dwSkillCoolDownTime + 2000; //�ӳ�ʱ����΢��һ��
// 
// 				m_vecAttackSkill.push_back(xAttackSkill);
// 			}				
// 		}
// 	}	

    typedef std::pair<BotApplication::SkillMap::iterator,BotApplication::SkillMap::iterator> Pairs;
    Pairs valuePair = theApp.gBotApplication.RoleSkillMap.equal_range(GetSelfProfession());
    for (BotApplication::SkillMap::iterator itr = valuePair.first;itr != valuePair.second;++itr)
    {
        BotApplication::skillStruct structSkill = itr->second;
//         CItemDetail::SItemSkill* psikll = GettheItemDetail().GetSkillByID(structSkill.id,1);
//         if (NULL != psikll)
//         {
            //for (int i = 1;i <= psikll->ustSkillMaxLvl;++i)
            {
                AttackSkill xAttackSkill;
                xAttackSkill.shID = structSkill.id;//m_pSkillBag[i].ustSkillID;
                xAttackSkill.Level = structSkill.SkillLevel;
                CItemDetail::SItemSkill* pSkill = GettheItemDetail().GetSkillByID(structSkill.id,structSkill.SkillLevel);
                if (pSkill)
                {
                    xAttackSkill.dwSpaceTime = pSkill->dwSkillCoolDownTime + 2000;
                }
                else
                {
                    xAttackSkill.dwSpaceTime = 2000; //�ӳ�ʱ����΢��һ��
                }
                

                m_vecAttackSkill.push_back(xAttackSkill);
            }
        //}
    }

    std::vector<AttackSkill>::iterator NorItr = find(m_vecAttackSkill.begin(),m_vecAttackSkill.end(),NORMAL_ATTACK_ID);
    if (NorItr == m_vecAttackSkill.end())
    {
	    //if (m_vecAttackSkill.empty())
	    {
		    //û�м��ܾ�ѧϰ���� //��ʹ����ͨ����

		    AttackSkill xAttackSkill;
		    xAttackSkill.shID = NORMAL_ATTACK_ID;
            xAttackSkill.Level = 1;
		    xAttackSkill.dwSpaceTime = NORMAL_ATTACK_SPACE;

		    m_vecAttackSkill.push_back(xAttackSkill);
	    }
    }
}

int CAttackBot::GetAttackSkill(DWORD &dwSpaceTime)
{
	int nSkillID = -1;

	//�����Լ��Ѿ�ѧ�ļ�����ʩ��,ֻʹ�öԹ��﹥���ļ���
	int nCount = m_vecAttackSkill.size();

	if (nCount != 0)
	{
		int nSelect = rand() % nCount;  //�漴һ������

		if (CanUseSkill(m_vecAttackSkill[nSelect].shID))
		{
			nSkillID = m_vecAttackSkill[nSelect].shID;
			dwSpaceTime = m_vecAttackSkill[nSelect].dwSpaceTime;

			return nSkillID;
		}	
	}

	if (CanUseSkill(NORMAL_ATTACK_ID))//��������ü��ܾ�����ͨ����
	{
		nSkillID = NORMAL_ATTACK_ID;
		dwSpaceTime = NORMAL_ATTACK_SPACE;
	}

	return nSkillID;
}

//�Ȳ�����MP ����
bool CAttackBot::CanUseSkill(USHORT nSkillID)
{
	mapiter iter = m_mapUseSkill.find(nSkillID);

	if (iter != m_mapUseSkill.end())
	{
		if ((*iter).second >= HQ_TimeGetTime())
		{
			return false;
		}
	}

	return true;
}

//����ʹ�ü��ܵ��ӳ�ʱ��
void CAttackBot::AddUseSkill(USHORT nSkillID, DWORD dwTime)
{
	mapiter iter = m_mapUseSkill.find(nSkillID);

	if (iter != m_mapUseSkill.end())
	{
		(*iter).second = HQ_TimeGetTime() + dwTime;
	}
	else
	{
		m_mapUseSkill.insert(make_pair(nSkillID, dwTime));
	}
}

void CAttackBot::LearnXinFa( unsigned int nType, unsigned int nXinFaLevel, unsigned int nXinFaID ) // bRandom = trueʱ�����ѧϰ�ķ�
{
    int nXinFaIndex = rand() % totalXinFaNum;
	switch ( GetSelfProfession() )
	{
	case EArmType_Warrior:
		if ( nType = Enum_RandId )
		{ nXinFaID = s_nXinFaID_Warrior[nXinFaIndex]; }
		else
			if ( nType = Enum_NoRand )
			{ nXinFaID = s_nXinFaID_Warrior[0]; }
		break;
	case EArmType_Mage:
		if ( nType = Enum_RandId )
		{ nXinFaID = s_nXinFaID_Warrior[nXinFaIndex]; }
		else
			if ( nType = Enum_NoRand )
			{ nXinFaID = s_nXinFaID_Warrior[0]; }
		break;
	case EArmType_Taoist:
		if ( nType = Enum_RandId )
		{ nXinFaID = s_nXinFaID_Warrior[nXinFaIndex]; }
		else
			if ( nType = Enum_NoRand )
			{ nXinFaID = s_nXinFaID_Warrior[0]; }
		break;
	case EArmType_Assassin:
		if ( nType = Enum_RandId )
		{ nXinFaID = s_nXinFaID_Warrior[nXinFaIndex]; }
		else
			if ( nType = Enum_NoRand )
			{ nXinFaID = s_nXinFaID_Warrior[0]; }
		break;
	case EArmType_Hunter:
		if ( nType = Enum_RandId )
		{ nXinFaID = s_nXinFaID_Warrior[nXinFaIndex]; }
		else
			if ( nType = Enum_NoRand )
			{ nXinFaID = s_nXinFaID_Warrior[0]; }
		break;

	}
	MsgLearnXinFa xLeanXinFa;
	xLeanXinFa.nXinFaID   = nXinFaID;
	xLeanXinFa.nXinFaLevel= nXinFaLevel;
	SendMsg( &xLeanXinFa );
}