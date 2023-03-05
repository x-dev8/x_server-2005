#include "stdafx.h"
#include "MapStatic.h"
#include "Bot.h"
#include "BotApplication.h"
#include "GameBot.h"

IMPLEMENT_DYNAMIC(MapStatic, CStatic)

BEGIN_MESSAGE_MAP(MapStatic, CStatic)
	ON_WM_PAINT()
	ON_WM_TIMER()	
	ON_WM_DESTROY()
END_MESSAGE_MAP()

MapStatic::MapStatic()
{
	m_nBotID = 0;
	m_bTimerStart = FALSE;
	m_dwMapID = ErrorUnsignedLongID;

	m_nWidth = 0;
	m_nHeight = 0;

}

MapStatic::~MapStatic()
{	
	m_nBotID = 0;	
}

BOOL MapStatic::StartTimer()
{
	if (m_bTimerStart == TRUE)
	{
		return FALSE;
	}

	SetTimer(TIMER_ID, TIMER_SPACE, NULL);
	m_bTimerStart = TRUE;

	return TRUE;
}

BOOL MapStatic::StopTimer()
{
	if (m_bTimerStart == FALSE)
	{
		return FALSE;
	}

	KillTimer(TIMER_ID);
	m_bTimerStart = FALSE;

	return FALSE;
}

void MapStatic::SetBotID(int nBotID)
{	
	m_nBotID = nBotID;
	StartTimer();
}

void MapStatic::MapPaint()
{	
	if (this->m_hWnd == NULL) { return; }
	CPaintDC  MemDC(this);  

	CRect rect;
	GetClientRect(&rect);

	MemDC.SetBkMode(TRANSPARENT);
	MemDC.SetBkColor(GetSysColor(COLOR_BTNFACE));

	static CBrush tmpbrush(RGB(132, 251, 171));  
	MemDC.FillRect(&rect, &tmpbrush);                 //填充背景

	int nWidth = rect.Width();
	int nHeight = rect.Height();


	//画机器人坐标
	BaseRobot *pBot = theApp.gBotApplication.GetBot(m_nBotID);
	if (pBot != NULL && m_nWidth != 0 && m_nHeight != 0)
	{
		if (pBot->GetBotState() == State_Play)
		{
			CPoint BotPoint;
			BotPoint.x = (pBot->GetPosX() * nWidth) / m_nWidth;
			BotPoint.y = nHeight - (pBot->GetPosY() * nHeight) / m_nHeight;	

			if (BotPoint.x > 0 && BotPoint.x < nWidth && BotPoint.y > 0 && BotPoint.y < nHeight)
			{
				static CBrush BotPointBrush(RGB(255,0,0));  
				DrawSelPoint(&BotPointBrush, &MemDC, BotPoint, 2);  
			}	
		}
	}	
}

void MapStatic::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == TIMER_ID)
	{
		BaseRobot *pBot = theApp.gBotApplication.GetBot(m_nBotID);
		if (pBot != NULL && pBot->GetBotState() == State_Play)
		{		
			//地图ID
			DWORD dwMapID = pBot->GetMapID();
			if(dwMapID != m_dwMapID)
			{
				//获得地图大小
				MapConfig::MapData* pMapData = theMapConfig.GetMapDataById(dwMapID);			
				
				if (pMapData != NULL)
				{
					m_nWidth = pMapData->Row * CHUNK_SIZE ;  
					m_nHeight = pMapData->Column * CHUNK_SIZE ;
								
					m_strMapName = pMapData->MapName;

					m_dwMapID = dwMapID;
				}
				else  //没找到地图信息
				{
					m_nWidth = 0; 
					m_nHeight = 0;
					m_strMapName.clear();
				}
			}			
		}
		else
		{			
			m_dwMapID = ErrorUnsignedLongID;
			m_strMapName.clear();
		}

		Invalidate(TRUE);
	}

	CStatic::OnTimer(nIDEvent);
}

void MapStatic::OnPaint()
{
	MapPaint();
}

//rmidpos中心点
void MapStatic::DrawSelPoint(CBrush *rbrush, CDC *rtmpDC, CPoint &rmidpos, int nRadius)  
{	
	if (this->m_hWnd == NULL){ return; }
	CBrush *old = rtmpDC->SelectObject(rbrush);

	CRect rect;
	rect.left = rmidpos.x - nRadius;
	rect.top = rmidpos.y - nRadius;
	rect.right = rmidpos.x + nRadius;
	rect.bottom = rmidpos.y + nRadius;

	if(rect.left <= 0)
	{
		rect.left = 1;
	}
	if (rect.top <= 0)
	{
		rect.top = 1;
	}

	if (rect.right > m_nWidth && m_nWidth != 0)
	{
		rect.right = m_nWidth - 1;
	}

	if (rect.bottom > m_nHeight && m_nHeight != 0)
	{
		rect.bottom = m_nHeight - 1;
	}

	rtmpDC->FillRect(&rect, rbrush);
	rtmpDC->SelectObject(old);          
}

void MapStatic::OnDestroy()
{
	StopTimer();

	CStatic::OnDestroy();

	// TODO: Add your message handler code here
}
