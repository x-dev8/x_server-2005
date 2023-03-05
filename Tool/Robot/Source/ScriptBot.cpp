#include "stdafx.h"
#include "ScriptBot.h"
#include "ScriptManager.h"
#include "BotAppDataCenter.h"
#include "MapConfig.h"

CScriptBot::CScriptBot()
{
	m_nScriptInMapId = s_nScriptMapId[rand() % s_nScriptMapCount];	//随即一个副本地图
	m_nScriptOutMapId = s_nMapId[rand() % s_nMapCount];				//随即一个副本外的地图

	m_dwStayInScriptMapTime = ((rand() % 2) + 1 ) * 30000;	//在副本里的时间  0.5 - 1 分钟
	m_dwStayOutScriptMapTime = ((rand() % 2) + 1) * 30000;	//在副本外的时间  0.5 - 1 分钟

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
// 	Say("大家快准备，我要进副本咯！");
// 	
// 	PlayScript();	
}

void CScriptBot::PlayScript()
{
	DWORD dwNowTime = HQ_TimeGetTime();

	if (GetMapID() != m_nScriptInMapId) //不在副本里
	{	
		if (m_bFlyOut)
		{
			m_bFlyOut = false;

			SetTipsInfo("等待进入副本");
			m_dwNextFlyMapTime = dwNowTime + m_dwStayOutScriptMapTime;
		}

		FlyMap(dwNowTime, m_nScriptInMapId); //飞进副本		
		m_bFlyIn = true;
	}
	else
	{
		if (m_bFlyIn)
		{
			m_bFlyIn = false;

			SetTipsInfo("副本中...");
			m_dwNextFlyMapTime = dwNowTime + m_dwStayInScriptMapTime;
		}

		if (FlyMap(dwNowTime, m_nScriptOutMapId))//飞出副本
		{		
			m_bFlyOut = true;
		}
		else
		{
			CAttackBot::PlayAttack(); //打怪
		}		
	}
}

bool CScriptBot::FlyMap(DWORD dwNowTime, int nMapId)
{
	if (dwNowTime > m_dwNextFlyMapTime)
	{
		//5秒飞一次
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
