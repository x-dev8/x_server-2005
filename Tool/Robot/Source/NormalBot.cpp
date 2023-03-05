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
	RandLoginOutSpaceTime();		//�����漴�ǳ�ʱ��

    m_BotType = Bot_Normal;

}

CNormalBot::~CNormalBot(void)
{
}

void CNormalBot::InitPlayGame(UINT mapid)
{
	CAttackBot::InitPlayGame(mapid);

	m_dwStartPlayTime = HQ_TimeGetTime();	//��ʼ��Ϸʱ��	
	m_dwLastFlyTime = HQ_TimeGetTime();
}

void CNormalBot::PlayGame()
{
	//Say("����������Ѳɽ,��Ҫ˵�ܳ��ܳ��Ļ�,���ܰѸ�˵�Ķ�˵��,���ڿ�ʼ˵:˹�ٸ���˸�������ظ����˷������ڵ����ɹ��˽���޿��˼Ҹ��������˺����տ������ù˿�ɫ��������jhrglerg8y478y5uguh98gkdgkslguioergnld˵����~~!");

	//�ж϶Ͽ���Ϸ
	//if (LoginOutGame())	{ return; }
	
	//�ж��Ƿ�Ҫ�ɵ�ͼ
	//if (RandFlyToMap())	{ return; }

	//RunTeam();

	//��������
	CAttackBot::PlayAttack();
    BaseRobot::PlayGame();
}

bool CNormalBot::LoginOutGame()
{
	if(HQ_TimeGetTime() - m_dwStartPlayTime > m_dwLoginOutSpace)
	{
		//Close(); //˲������������

		return true;
	}

	return false;
}


bool CNormalBot::RandFlyToMap()
{
	if (GetAreaInfo())  //���ָ���˵�ͼ �Ͳ��÷�
	{
		return false;
	}

	
	int ranmap = rand() % theMapConfig.MapDataCount();
	if(HQ_TimeGetTime() - m_dwLastFlyTime > m_nFlySpaceTime)
	{
		SetTipsInfo("���е�ͼ");
		MapConfig::MapData* pMapData = theMapConfig.GetMapDataById(ranmap);			

		if (pMapData != NULL)
		{
			int nWidth  = pMapData->Row * CHUNK_SIZE - 50;  //128 * 2.56 = 327
			int nHeight = pMapData->Column * CHUNK_SIZE - 50;	//��50��ֹ�ɵ���ͼ�߽�����ƶ������ܳ��߽�

			//ֻ�в��Ǹ�����ͼ�ŷ�
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
	//5  - 10 ����֮��
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
