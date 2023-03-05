/********************************************************************
	Created by UIEditor.exe
	FileName: D:\3Guo_Client_02.05\Data\Ui\GuildBattlResultInfo.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "UIBase.h"
#include "CampBattleMessage.h"
#ifndef ID_FRAME_GuildBattleResult
#define ID_FRAME_GuildBattleResult		"ID_FRAME_GuildBattleResult"
#endif  ID_FRAME_GuildBattleResult
#ifndef ID_TEXT_Reult
#define ID_TEXT_Reult		"ID_TEXT_Reult"
#endif  ID_TEXT_Reult
#ifndef ID_BUTTON_Close
#define ID_BUTTON_Close		"ID_BUTTON_Close"
#endif  ID_BUTTON_Close
#ifndef ID_TEXT_KillSum
#define ID_TEXT_KillSum		"ID_TEXT_KillSum"
#endif  ID_TEXT_KillSum
#ifndef ID_LISTIMG_Reward
#define ID_LISTIMG_Reward		"ID_LISTIMG_Reward"
#endif  ID_LISTIMG_Reward
#ifndef ID_TEXT_Name1
#define ID_TEXT_Name1		"ID_TEXT_Name1"
#endif  ID_TEXT_Name1
#ifndef ID_TEXT_KIllNum3
#define ID_TEXT_KIllNum3		"ID_TEXT_KIllNum3"
#endif  ID_TEXT_KIllNum3
#ifndef ID_TEXT_KIllNum2
#define ID_TEXT_KIllNum2		"ID_TEXT_KIllNum2"
#endif  ID_TEXT_KIllNum2
#ifndef ID_TEXT_KIllNum6
#define ID_TEXT_KIllNum6		"ID_TEXT_KIllNum6"
#endif  ID_TEXT_KIllNum6
#ifndef ID_TEXT_Name6
#define ID_TEXT_Name6		"ID_TEXT_Name6"
#endif  ID_TEXT_Name6
#ifndef ID_TEXT_KIllNum1
#define ID_TEXT_KIllNum1		"ID_TEXT_KIllNum1"
#endif  ID_TEXT_KIllNum1
#ifndef ID_TEXT_Name5
#define ID_TEXT_Name5		"ID_TEXT_Name5"
#endif  ID_TEXT_Name5
#ifndef ID_TEXT_Name4
#define ID_TEXT_Name4		"ID_TEXT_Name4"
#endif  ID_TEXT_Name4
#ifndef ID_TEXT_Name3
#define ID_TEXT_Name3		"ID_TEXT_Name3"
#endif  ID_TEXT_Name3
#ifndef ID_TEXT_Name2
#define ID_TEXT_Name2		"ID_TEXT_Name2"
#endif  ID_TEXT_Name2
#ifndef ID_TEXT_KIllNum10
#define ID_TEXT_KIllNum10		"ID_TEXT_KIllNum10"
#endif  ID_TEXT_KIllNum10
#ifndef ID_TEXT_KIllNum9
#define ID_TEXT_KIllNum9		"ID_TEXT_KIllNum9"
#endif  ID_TEXT_KIllNum9
#ifndef ID_TEXT_Name10
#define ID_TEXT_Name10		"ID_TEXT_Name10"
#endif  ID_TEXT_Name10
#ifndef ID_TEXT_Name9
#define ID_TEXT_Name9		"ID_TEXT_Name9"
#endif  ID_TEXT_Name9
#ifndef ID_TEXT_KIllNum5
#define ID_TEXT_KIllNum5		"ID_TEXT_KIllNum5"
#endif  ID_TEXT_KIllNum5
#ifndef ID_TEXT_KIllNum4
#define ID_TEXT_KIllNum4		"ID_TEXT_KIllNum4"
#endif  ID_TEXT_KIllNum4
#ifndef ID_TEXT_KIllNum8
#define ID_TEXT_KIllNum8		"ID_TEXT_KIllNum8"
#endif  ID_TEXT_KIllNum8
#ifndef ID_TEXT_Name8
#define ID_TEXT_Name8		"ID_TEXT_Name8"
#endif  ID_TEXT_Name8
#ifndef ID_TEXT_KIllNum7
#define ID_TEXT_KIllNum7		"ID_TEXT_KIllNum7"
#endif  ID_TEXT_KIllNum7
#ifndef ID_TEXT_Name7
#define ID_TEXT_Name7		"ID_TEXT_Name7"
#endif  ID_TEXT_Name7

class CUI_ID_FRAME_GuildBattleResult :public CUIBase
{
	// Member
public:	
	CUI_ID_FRAME_GuildBattleResult();
	virtual ~CUI_ID_FRAME_GuildBattleResult();
	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_CloseOnButtonClick( ControlObject* pSender );
	bool ID_LISTIMG_RewardOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_RewardOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_RewardOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_RewardOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );

	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视

	void SetData(MsgCampGuildBattleRewardInfo * pMsg);
	void SetShowByNeed();
private:	
	 ControlFrame*	m_pID_FRAME_GuildBattleResult;
	 ControlText*	m_pID_TEXT_Reult;
	 ControlButton*	m_pID_BUTTON_Close;
	 ControlText*	m_pID_TEXT_KillSum;
	 ControlListImage*	m_pID_LISTIMG_Reward;
	 ControlText*	m_pID_TEXT_Name1;
	 ControlText*	m_pID_TEXT_KIllNum3;
	 ControlText*	m_pID_TEXT_KIllNum2;
	 ControlText*	m_pID_TEXT_KIllNum6;
	 ControlText*	m_pID_TEXT_Name6;
	 ControlText*	m_pID_TEXT_KIllNum1;
	 ControlText*	m_pID_TEXT_Name5;
	 ControlText*	m_pID_TEXT_Name4;
	 ControlText*	m_pID_TEXT_Name3;
	 ControlText*	m_pID_TEXT_Name2;
	 ControlText*	m_pID_TEXT_KIllNum10;
	 ControlText*	m_pID_TEXT_KIllNum9;
	 ControlText*	m_pID_TEXT_Name10;
	 ControlText*	m_pID_TEXT_Name9;
	 ControlText*	m_pID_TEXT_KIllNum5;
	 ControlText*	m_pID_TEXT_KIllNum4;
	 ControlText*	m_pID_TEXT_KIllNum8;
	 ControlText*	m_pID_TEXT_Name8;
	 ControlText*	m_pID_TEXT_KIllNum7;
	 ControlText*	m_pID_TEXT_Name7;

	 ControlText*	m_NameList[10];
	 ControlText*	m_KillNumList[10];
};
extern CUI_ID_FRAME_GuildBattleResult s_CUI_ID_FRAME_GuildBattleResult;
