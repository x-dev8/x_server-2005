#include "StdAfx.h"
#include "NormalBot.h"
#include "MessageDefine.h"
#include "AttackBot.h"
#include "WordParser.h"
#include "BotAppDataCenter.h"
#include "MapConfig.h"

#pragma warning(disable:4702)

CNormalBot::CNormalBot(void)
{
	m_dwStartPlayTime = 0;
	
	m_dwNextRunTimeSpace = 0;
	RandLoginOutSpaceTime();		//设置随即登出时间

    m_BotType = Bot_Normal;

}

CNormalBot::~CNormalBot(void)
{
}

void CNormalBot::InitPlayGame(UINT mapid)
{
	CAttackBot::InitPlayGame(mapid);

	m_dwStartPlayTime = HQ_TimeGetTime();	//开始游戏时间	
	m_dwLastFlyTime = HQ_TimeGetTime();
}

void CNormalBot::PlayGame()
{
	//Say("大王派我来巡山,我要说很长很长的话,才能把该说的都说完,现在开始说:斯蒂格个人个如果的呢个带了法国进口低声飞过了解胡罗口人家给哈萨克人韩国烧烤金额会让顾客色弱过进而jhrglerg8y478y5uguh98gkdgkslguioergnld说完啦~~!");

	//判断断开游戏
	//if (LoginOutGame())	{ return; }
	
	//判断是否要飞地图
	//if (RandFlyToMap())	{ return; }

	//RunTeam();

	//攻击怪物
	CAttackBot::PlayAttack();
    BaseRobot::PlayGame();
}

bool CNormalBot::LoginOutGame()
{
	if(HQ_TimeGetTime() - m_dwStartPlayTime > m_dwLoginOutSpace)
	{
		//Close(); //瞬间又连接上了

		return true;
	}

	return false;
}


bool CNormalBot::RandFlyToMap()
{
	if (GetAreaInfo())  //如果指定了地图 就不让飞
	{
		return false;
	}

	
	int ranmap = rand() % theMapConfig.MapDataCount();
	if(HQ_TimeGetTime() - m_dwLastFlyTime > m_nFlySpaceTime)
	{
		SetTipsInfo("飞行地图");
		MapConfig::MapData* pMapData = theMapConfig.GetMapDataById(ranmap);			

		if (pMapData != NULL)
		{
			int nWidth  = pMapData->Row * CHUNK_SIZE - 50;  //128 * 2.56 = 327
			int nHeight = pMapData->Column * CHUNK_SIZE - 50;	//减50防止飞到地图边界后又移动导致跑出边界

			//只有不是副本地图才飞
			if (!pMapData->IsEctypeMap() && !pMapData->MapName.empty() && nWidth != 0 && nHeight != 0)
			{
				
				//FlyToMap(ranmap, rand() % nWidth, rand() % nHeight);

				m_dwLastFlyTime = HQ_TimeGetTime();

				return true;
			}			
		}
	}
	
	return false;
}

void CNormalBot::RandLoginOutSpaceTime()
{
	//5  - 10 分钟之间
	int nCount = (rand() % 6) + 5;

	m_dwLoginOutSpace = nCount * PER_SPACE_TIME;
}

void CNormalBot::RunTeam()
{
	if (m_dwNextRunTimeSpace > HQ_TimeGetTime()) { return; }
	m_dwNextRunTimeSpace = HQ_TimeGetTime() + PER_SPACE_TIME;

	/*if (GetId() % 5 != 0) { return; }*/

	vector<DWORD> vecPlayerID;

	for (PlayerInfoContainer::iterator iter = m_listPlayerList.begin(); iter != m_listPlayerList.end(); ++iter)
	{
		vecPlayerID.push_back(iter->dwCharacterID);
	}

	if (vecPlayerID.empty()) { return; }

	int nRandIndex = rand() % vecPlayerID.size();

	MsgRequestTeam xRequest;
    xRequest.AssignMode = 2;
	xRequest.dwNewbieID = vecPlayerID[nRandIndex];
	memset(xRequest.szNewbieName, 0, sizeof(xRequest.dwNewbieID));
	

	SendMsg(&xRequest);
}
