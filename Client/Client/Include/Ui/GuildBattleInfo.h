/********************************************************************
	Created by UIEditor.exe
	FileName: D:\3Guo_Client_02.05\Data\Ui\GuildBattleInfo.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "UIBase.h"
#ifndef ID_FRAME_GuildBattleInfo
#define ID_FRAME_GuildBattleInfo		"ID_FRAME_GuildBattleInfo"
#endif  ID_FRAME_GuildBattleInfo
#ifndef ID_TEXT_MyGuildPoint
#define ID_TEXT_MyGuildPoint		"ID_TEXT_MyGuildPoint"
#endif  ID_TEXT_MyGuildPoint
#ifndef ID_TEXT_OtherGuildPoint
#define ID_TEXT_OtherGuildPoint		"ID_TEXT_OtherGuildPoint"
#endif  ID_TEXT_OtherGuildPoint
#ifndef ID_TEXT_TotleKillSumA
#define ID_TEXT_TotleKillSumA		"ID_TEXT_TotleKillSumA"
#endif  ID_TEXT_TotleKillSumA
#ifndef ID_TEXT_TotleKillSumB
#define ID_TEXT_TotleKillSumB		"ID_TEXT_TotleKillSumB"
#endif  ID_TEXT_TotleKillSumB
#ifndef ID_PROGRESS_BarracksA2
#define ID_PROGRESS_BarracksA2		"ID_PROGRESS_BarracksA2"
#endif  ID_PROGRESS_BarracksA2
#ifndef ID_PROGRESS_BarracksA1
#define ID_PROGRESS_BarracksA1		"ID_PROGRESS_BarracksA1"
#endif  ID_PROGRESS_BarracksA1
#ifndef ID_PROGRESS_BarracksA3
#define ID_PROGRESS_BarracksA3		"ID_PROGRESS_BarracksA3"
#endif  ID_PROGRESS_BarracksA3
#ifndef ID_PROGRESS_BarracksB3
#define ID_PROGRESS_BarracksB3		"ID_PROGRESS_BarracksB3"
#endif  ID_PROGRESS_BarracksB3
#ifndef ID_PROGRESS_BarracksB2
#define ID_PROGRESS_BarracksB2		"ID_PROGRESS_BarracksB2"
#endif  ID_PROGRESS_BarracksB2
#ifndef ID_PROGRESS_BarracksB1
#define ID_PROGRESS_BarracksB1		"ID_PROGRESS_BarracksB1"
#endif  ID_PROGRESS_BarracksB1
#ifndef ID_PROGRESS_BarracksA4
#define ID_PROGRESS_BarracksA4		"ID_PROGRESS_BarracksA4"
#endif  ID_PROGRESS_BarracksA4
#ifndef ID_PROGRESS_BarracksB4
#define ID_PROGRESS_BarracksB4		"ID_PROGRESS_BarracksB4"
#endif  ID_PROGRESS_BarracksB4
#ifndef ID_TEXT_BarracksA1
#define ID_TEXT_BarracksA1		"ID_TEXT_BarracksA1"
#endif  ID_TEXT_BarracksA1
#ifndef ID_TEXT_BarracksA2
#define ID_TEXT_BarracksA2		"ID_TEXT_BarracksA2"
#endif  ID_TEXT_BarracksA2
#ifndef ID_TEXT_BarracksA3
#define ID_TEXT_BarracksA3		"ID_TEXT_BarracksA3"
#endif  ID_TEXT_BarracksA3
#ifndef ID_TEXT_BarracksA4
#define ID_TEXT_BarracksA4		"ID_TEXT_BarracksA4"
#endif  ID_TEXT_BarracksA4
#ifndef ID_TEXT_BarracksB1
#define ID_TEXT_BarracksB1		"ID_TEXT_BarracksB1"
#endif  ID_TEXT_BarracksB1
#ifndef ID_TEXT_BarracksB2
#define ID_TEXT_BarracksB2		"ID_TEXT_BarracksB2"
#endif  ID_TEXT_BarracksB2
#ifndef ID_TEXT_BarracksB3
#define ID_TEXT_BarracksB3		"ID_TEXT_BarracksB3"
#endif  ID_TEXT_BarracksB3
#ifndef ID_TEXT_BarracksB4
#define ID_TEXT_BarracksB4		"ID_TEXT_BarracksB4"
#endif  ID_TEXT_BarracksB4

#ifndef ID_TEXT_GuildNameA
#define ID_TEXT_GuildNameA		"ID_TEXT_GuildNameA"
#endif  ID_TEXT_GuildNameA

#ifndef ID_TEXT_GuildNameB
#define ID_TEXT_GuildNameB		"ID_TEXT_GuildNameB"
#endif  ID_TEXT_GuildNameB


class CUI_ID_FRAME_GuildBattleInfo:public CUIBase
{
	// Member
public:	
	CUI_ID_FRAME_GuildBattleInfo();
	virtual ~CUI_ID_FRAME_GuildBattleInfo();
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();

	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视

	void SetData(unsigned int GuildAID,unsigned int APoint,unsigned int AKillSum,float A1,float A2,float A3,float A4,unsigned int GuildBID,unsigned int BPoint,unsigned int BKillSum,float B1,float B2,float B3,float B4);
	void SetShowByNeed();
private:
	char* GetString(unsigned int Num,char * Info);
	char* GetString(float Num,char * Info);
private:	
	 ControlFrame*	m_pID_FRAME_GuildBattleInfo;
	 ControlText*	m_pID_TEXT_MyGuildPoint;
	 ControlText*	m_pID_TEXT_OtherGuildPoint;
	 ControlText*	m_pID_TEXT_TotleKillSumA;
	 ControlText*	m_pID_TEXT_TotleKillSumB;
	 ControlProgress*	m_pID_PROGRESS_BarracksA2;
	 ControlProgress*	m_pID_PROGRESS_BarracksA1;
	 ControlProgress*	m_pID_PROGRESS_BarracksA3;
	 ControlProgress*	m_pID_PROGRESS_BarracksB3;
	 ControlProgress*	m_pID_PROGRESS_BarracksB2;
	 ControlProgress*	m_pID_PROGRESS_BarracksB1;
	 ControlProgress*	m_pID_PROGRESS_BarracksA4;
	 ControlProgress*	m_pID_PROGRESS_BarracksB4;
	 ControlText*	m_pID_TEXT_BarracksA1;
	 ControlText*	m_pID_TEXT_BarracksA2;
	 ControlText*	m_pID_TEXT_BarracksA3;
	 ControlText*	m_pID_TEXT_BarracksA4;
	 ControlText*	m_pID_TEXT_BarracksB1;
	 ControlText*	m_pID_TEXT_BarracksB2;
	 ControlText*	m_pID_TEXT_BarracksB3;
	 ControlText*	m_pID_TEXT_BarracksB4;

	 ControlText*	m_pID_TEXT_GuildNameA;
	 ControlText*	m_pID_TEXT_GuildNameB;
	 
};
extern CUI_ID_FRAME_GuildBattleInfo s_CUI_ID_FRAME_GuildBattleInfo;
