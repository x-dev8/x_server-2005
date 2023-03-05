#include "StdAfx.h"
#include "AttackBot.h"
#include "FightBot.h"
#include "BotAppDataCenter.h"
#include "ScriptManager.h"
#include "CountryDefine.h"
#include "MapConfig.h"
#include "ItemDetailConfig.h"
extern bool g_bCountryFight;			// 全局机器人国战开关 luo.qin 3.28
extern bool g_PlaySkill;				// 全局技能控制开关 luo.qin 3.28

extern bool g_bCreateMonster;			// 全局机器人创建怪物开关 luo.qin 3.18
extern bool g_bChangeEquip;				// 全局机器人换装开关 luo.qin 3.21
extern bool g_bRandRide;				// 全局机器人随机骑马开关 luo.qin 3.21	

CFightBot::CFightBot() : CAttackBot(),LastMapId(-1)
{
	m_BotType = Bot_Fight;
}

CFightBot::~CFightBot()
{

}

void CFightBot::InitPlayGame(UINT mapid)
{
	//切换到PK 模式

	MsgChangePKFlag xMsg;
	xMsg.shFlag = PKMode_Fight;
	SendMsg(&xMsg);

	CAttackBot::InitPlayGame(mapid);
}

void CFightBot::PlayGame()
{
	std::string FullPath = theBotDataCenter.ScriptFilePath;
	FullPath += theBotDataCenter.ScriptFileName;
	uint32 result = theScriptManager.LoadScript(FullPath.c_str());
	if (ER_Success == result)
	{
		theScriptManager.ScriptFunctionVoid("PlayGame",this);
	}


	//每3秒给对应的机器人创建一个Monster luo.qin 3.17
	if ( GameTime::IsPassCurrentTime( m_LastCreateTime, Monster_Create_TimeSpace ) && g_bCreateMonster )//保证机器人已经飞到指定地图
	{
		if (  m_MonsterNum < Monster_Num_Total )
		{		

			BotCreateMonster( (DWORD)GetBotDBID(), 100011 , GetPosX() , GetPosY(), Monster_Num_PerSecond );
			m_MonsterNum += Monster_Num_PerSecond;
			//m_xMsgStatistician.SetMonsterNum( m_MonsterNum );
			m_LastCreateTime = HQ_TimeGetTime();

		}
	}
	if (g_bCountryFight)
	{
		PlayFight();
	}

	Say("神功盖世，天下无敌，敢来与我决一死战否！");

	if (LastMapId == -1)
		LastMapId = GetMapID();

	if (LastMapId != GetMapID())
	{
		MsgChangePKFlag xMsg;
		xMsg.shFlag = PKMode_Normal;
		SendMsg(&xMsg);
		LastMapId = GetMapID();
	}
	PlayFight();
}

void CFightBot::PlayFight()
{
	CAttackBot::PlayAttack();
}

GameObjectId CFightBot::LockTarget()
{
	return CAttackBot::LockTarget();
	short shTarget = -1;

	vector<PlayerInfo*> vecPlayer;

	list<PlayerInfo>::iterator iter = m_listPlayerList.begin();
	list<PlayerInfo>::iterator end = m_listPlayerList.end();
	for ( ; iter != end; ++iter)
	{
		if (IsInArea(GetMapID(), (*iter).m_vPos) && (*iter).nHP > 0 && IsNotSameCountry((*iter)))
		{
			vecPlayer.push_back(&(*iter));
		}
	}

	if (vecPlayer.empty())
	{
		return shTarget;
	}

	//随即一个目标
	int nRand = rand() % vecPlayer.size();
	shTarget = vecPlayer[nRand]->shPlayerID;

	//请求怪物信息
	MsgQueryCharInfo query;
	query.stChar = shTarget;
	SendMsg(&query);  		

	return shTarget;
}


PlayerInfo* CFightBot::GetLockPlayerInfo(GameObjectId shID)
{
	//return GetPlayer(shID);
	return CAttackBot::GetLockPlayerInfo(shID);
}

void CFightBot::RandReqCharInfo(GameObjectId shID)
{
	///////战斗机器人都要请求
	MsgQueryCharInfo query;
	query.stChar = shID;
	SendMsg(&query); 
	CAttackBot::RandReqCharInfo(shID);
}

//通过名字来判断, 机器人分T 和 H 开头的~  T 和 H 就是敌对方
bool CFightBot::IsEnemyPlayer(PlayerInfo &xpPlayer)
{
	string strPlayerName = xpPlayer.szName;					//玩家的名字
	string strSelfName = GetBotRoleName();					//自己的名字

	//判断首个字符, 首先要是机器人, 自己人上去的不能攻击
	string strFirstName = "";
	for (int i = 0; i < s_nNameCount; ++i)
	{
		if (strPlayerName.find(s_pszName[i]) != string::npos)
		{
			strFirstName.assign(strPlayerName.c_str(), 1);
			break;
		}
	}

	if (strFirstName.empty())								//不是机器人
	{
		return false;
	}

	return (strSelfName.find(strFirstName) == string::npos);
}

extern bool g_bCountryFight;								// 全局机器人国战开关 luo.qin 3.28
extern bool g_PlaySkill;									// 全局技能控制开关 luo.qin 3.28

//抽取字符串中的整数，并让字符串转整形luo.qin 3.28
int CFightBot::StrToInt( char *strPlayerName )
{

	char temchar[10] = {0};
	int  nPos = 0;
	int  nNameLen = strlen( strPlayerName );
	for ( int i = 0; i < nNameLen; ++i )
	{
		if ( strPlayerName[i] >=48 && strPlayerName[i] <= 57)
		{
			temchar[nPos] = strPlayerName[i]; 
			++nPos;
		}
	}
	temchar[nPos] = '\0';

	int nPlayerID = atoi( temchar );
	return nPlayerID;
}
//获得国家的枚举值luo.qin 3.28
int CFightBot::GetCountry( char *strPlayerName )
{
	int nPlayerID = StrToInt( strPlayerName );

	if ( 0 < nPlayerID && nPlayerID < 1000 )							//中立的玩家，用于观察机器人
	{
		return -1;
	}
	else if (1000 < nPlayerID && nPlayerID <= 6000)						// 江南
	{
		return CountryDefine::Country_LouLan;
	}
	else if ( 6000 < nPlayerID && nPlayerID <= 11000 )					// 淮西
	{
		return CountryDefine::Country_KunLun;
	}
	else if ( 11000 < nPlayerID && nPlayerID <= 16000 )					// 河北
	{
		return CountryDefine::Country_DunHuang;
	}
	else
	{
		return CountryDefine::Country_Init;
	}


}
//通过账号分布来判断是否是敌对方
bool CFightBot::IsNotSameCountry(PlayerInfo &xpPlayer)
{
	if ( StrToInt( xpPlayer.szName ) < 1000 )							//玩家账号,让玩家处于无阵营状态，防止玩家被机器人打死
	{
		return false;
	}
	return ( GetCountry( this->GetBotRoleName() ) != GetCountry( xpPlayer.szName ) );
}