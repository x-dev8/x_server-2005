/********************************************************************
    Filename:    MapStatic.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef _MAPSTATIC_H
#define _MAPSTATIC_H

#define TIMER_ID 0x227
#define TIMER_SPACE 500

#include "MeRTLibs.h"

// 右下角小地图控件
class MapStatic : public CStatic
{
	DECLARE_DYNAMIC(MapStatic)

public:
	MapStatic();
	virtual ~MapStatic();

	BOOL StartTimer();
	BOOL StopTimer();

	void SetBotID(int nBotID); //设置机器人ID号
	
	void MapPaint();
	void DrawSelPoint(CBrush *rbrush, CDC *rtmpDC, CPoint &rmidpos, int nRadius);
	virtual void OnDestroy();
	

protected:
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT_PTR nIDEvent);

public:
	BOOL        m_bTimerStart;
	int         m_nBotID;
	uint32      m_dwMapID;
    std::string m_strMapName;
	int         m_nWidth;
	int         m_nHeight;
};

#endif
