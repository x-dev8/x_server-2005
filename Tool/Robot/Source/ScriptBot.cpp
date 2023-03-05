#include "stdafx.h"
#include "ScriptBot.h"
#include "ScriptManager.h"
#include "BotAppDataCenter.h"
#include "MapConfig.h"

CScriptBot::CScriptBot()
{
	m_nScriptInMapId = s_nScriptMapId[rand() % s_nScriptMapCount];	//�漴һ��������ͼ
	m_nScriptOutMapId = s_nMapId[rand() % s_nMapCount];				//�漴һ��������ĵ�ͼ

	m_dwStayInScriptMapTime = ((rand() % 2) + 1 ) * 30000;	//�ڸ������ʱ��  0.5 - 1 ����
	m_dwStayOutScriptMapTime = ((rand() % 2) + 1) * 30000;	//�ڸ������ʱ��  0.5 - 1 ����

	m_dwNextFlyMapTime = 0;
	m_dwSpaceTime = 0;

	m_bFlyIn = false;
	m_bFlyOut = false;

    m_BotType = Bot_Script;

}

CScriptBot::~CScriptBot()
{

}

void CScriptBot::InitPlayGame(UINT mapid)
{
	ClearAreaInfo();
    CAttackBot::InitPlayGame(mapid);    
}

void CScriptBot::PlayGame()
{
    std::string FullPath = theBotDataCenter.ScriptFilePath;
    FullPath += theBotDataCenter.ScriptFileName;
    uint32 result = theScriptManager.LoadScript(FullPath.c_str());
    if (ER_Success == result)
    {
        theScriptManager.ScriptFunctionVoid("PlayGame",this);
    }
// 	Say("��ҿ�׼������Ҫ����������");
// 	
// 	PlayScript();	
}

void CScriptBot::PlayScript()
{
	DWORD dwNowTime = HQ_TimeGetTime();

	if (GetMapID() != m_nScriptInMapId) //���ڸ�����
	{	
		if (m_bFlyOut)
		{
			m_bFlyOut = false;

			SetTipsInfo("�ȴ����븱��");
			m_dwNextFlyMapTime = dwNowTime + m_dwStayOutScriptMapTime;
		}

		FlyMap(dwNowTime, m_nScriptInMapId); //�ɽ�����		
		m_bFlyIn = true;
	}
	else
	{
		if (m_bFlyIn)
		{
			m_bFlyIn = false;

			SetTipsInfo("������...");
			m_dwNextFlyMapTime = dwNowTime + m_dwStayInScriptMapTime;
		}

		if (FlyMap(dwNowTime, m_nScriptOutMapId))//�ɳ�����
		{		
			m_bFlyOut = true;
		}
		else
		{
			CAttackBot::PlayAttack(); //���
		}		
	}
}

bool CScriptBot::FlyMap(DWORD dwNowTime, int nMapId)
{
	if (dwNowTime > m_dwNextFlyMapTime)
	{
		//5���һ��
		if (dwNowTime > m_dwSpaceTime)
		{
			MapConfig::MapData* pMapData = theMapConfig.GetMapDataById(nMapId);
			if (pMapData != NULL)
			{
				MapConfig::RelivePosition* pRelive = pMapData->GetRelivePositionById(0);
				if (pRelive != NULL)
				{
					FlyToMap(m_nScriptInMapId, pRelive->PositionX, pRelive->PositionY);
				}								
			}	

			m_dwSpaceTime = dwNowTime + 5000;
		}
		return true;
	}

	return false;
}
