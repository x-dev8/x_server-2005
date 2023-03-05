#include "stdafx.h"
#include "FlyBot.h"
#include "MessageDefine.h"
#include "GameBot.h" //mapinfo
#include "ItemDetail.h"

#define FLY_SPACE_TIME 60

int ServerA_MapId[] = { 0, 1, 2 };
int ServerB_MapId[] = { 3, 4, 5, 6, 7, 8};

CFlyBot::CFlyBot():m_dwLastFlyTime(0)
{
	m_dwLastFlyTime = HQ_TimeGetTime();

	SetFlySpaceTime(FLY_SPACE_TIME);

    m_BotType = Bot_Fly;

}

CFlyBot::~CFlyBot()
{
}

void CFlyBot::PlayGame()
{
	Say("���ң����ң� ���һһҡ�����");	//����

	PlayFly();    
}

void CFlyBot::PlayFly()
{
	if(HQ_TimeGetTime() - m_dwLastFlyTime > m_nFlySpaceTime)
	{		
		int ranmap = rand() % MAP_COUNT;
		MapConfig::MapData* pMapData = theMapConfig.GetMapDataById(ranmap);			

		if (pMapData != NULL)
		{
			int nWidth  = pMapData->Row * CHUNK_SIZE - 200;  //128 * 2.56 = 327
			int nHeight = pMapData->Column * CHUNK_SIZE - 200;	//��200��ֹ�ɵ���ͼ�߽�����ƶ������ܳ��߽�

			if (nWidth != 0 && nHeight != 0)
			{
				FlyToMap(ranmap, (rand() % nWidth + 100), (rand() % nHeight + 100));

				m_dwLastFlyTime = HQ_TimeGetTime();
			}			
		}

		ClearMovePos();  //����ƶ��������
	}
	else
	{
		Move();
	}
}