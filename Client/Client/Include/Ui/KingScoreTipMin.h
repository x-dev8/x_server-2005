/********************************************************************
	Created by UIEditor.exe
	FileName: D:\3Guo_Client_02.05\Data\Ui\KingScoreTipMin.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "UiBase.h"

#ifndef ID_FRAME_KingScoreMin
#define ID_FRAME_KingScoreMin		"ID_FRAME_KingScoreMin"
#endif  ID_FRAME_KingScoreMin
#ifndef ID_BUTTON_Max
#define ID_BUTTON_Max		"ID_BUTTON_Max"
#endif  ID_BUTTON_Max

class CUI_ID_FRAME_KingScoreMin :public CUIBase
{
	// Member
public:	
	 CUI_ID_FRAME_KingScoreMin();
	 ControlFrame*	m_pID_FRAME_KingScoreMin;
	 ControlButton*	m_pID_BUTTON_Max;

	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_MaxOnButtonClick( ControlObject* pSender );

	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视

	void SetIsKingFight( bool b ) { m_bKingFight = b; }

private:
	bool m_bKingFight;
};
extern CUI_ID_FRAME_KingScoreMin s_CUI_ID_FRAME_KingScoreMin;
