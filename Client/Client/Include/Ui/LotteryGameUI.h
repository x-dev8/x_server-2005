/********************************************************************
Created by UIEditor.exe
FileName: D:\My Documents\桌面\Lottery\LotteryGame.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "TreasureBoxConfig.h"
#include "MessageDefine.h"
#include "ItemEnableChangeSysBase.h"

#ifndef ID_FRAME_LotteryGame
#define ID_FRAME_LotteryGame		"ID_FRAME_LotteryGame"
#endif  ID_FRAME_LotteryGame
#ifndef ID_TEXT_LotteryName
#define ID_TEXT_LotteryName		"ID_TEXT_LotteryName"
#endif  ID_TEXT_LotteryName
#ifndef ID_LISTIMG_Item1
#define ID_LISTIMG_Item1		"ID_LISTIMG_Item1"
#endif  ID_LISTIMG_Item1
#ifndef ID_LISTIMG_Item2
#define ID_LISTIMG_Item2		"ID_LISTIMG_Item2"
#endif  ID_LISTIMG_Item2
#ifndef ID_LISTIMG_Item3
#define ID_LISTIMG_Item3		"ID_LISTIMG_Item3"
#endif  ID_LISTIMG_Item3
#ifndef ID_LISTIMG_Item4
#define ID_LISTIMG_Item4		"ID_LISTIMG_Item4"
#endif  ID_LISTIMG_Item4
#ifndef ID_LISTIMG_Item5
#define ID_LISTIMG_Item5		"ID_LISTIMG_Item5"
#endif  ID_LISTIMG_Item5
#ifndef ID_LISTIMG_Item6
#define ID_LISTIMG_Item6		"ID_LISTIMG_Item6"
#endif  ID_LISTIMG_Item6
#ifndef ID_LISTIMG_Item7
#define ID_LISTIMG_Item7		"ID_LISTIMG_Item7"
#endif  ID_LISTIMG_Item7
#ifndef ID_LISTIMG_Item8
#define ID_LISTIMG_Item8		"ID_LISTIMG_Item8"
#endif  ID_LISTIMG_Item8
#ifndef ID_LISTIMG_Item9
#define ID_LISTIMG_Item9		"ID_LISTIMG_Item9"
#endif  ID_LISTIMG_Item9
#ifndef ID_LISTIMG_Item10
#define ID_LISTIMG_Item10		"ID_LISTIMG_Item10"
#endif  ID_LISTIMG_Item10
#ifndef ID_LISTIMG_Item11
#define ID_LISTIMG_Item11		"ID_LISTIMG_Item11"
#endif  ID_LISTIMG_Item11
#ifndef ID_LISTIMG_Item12
#define ID_LISTIMG_Item12		"ID_LISTIMG_Item12"
#endif  ID_LISTIMG_Item12
#ifndef ID_LISTIMG_Item13
#define ID_LISTIMG_Item13		"ID_LISTIMG_Item13"
#endif  ID_LISTIMG_Item13
#ifndef ID_LISTIMG_Item14
#define ID_LISTIMG_Item14		"ID_LISTIMG_Item14"
#endif  ID_LISTIMG_Item14
#ifndef ID_LISTIMG_Item15
#define ID_LISTIMG_Item15		"ID_LISTIMG_Item15"
#endif  ID_LISTIMG_Item15
#ifndef ID_LISTIMG_Item16
#define ID_LISTIMG_Item16		"ID_LISTIMG_Item16"
#endif  ID_LISTIMG_Item16
#ifndef ID_LISTIMG_Item17
#define ID_LISTIMG_Item17		"ID_LISTIMG_Item17"
#endif  ID_LISTIMG_Item17
#ifndef ID_LISTIMG_Item18
#define ID_LISTIMG_Item18		"ID_LISTIMG_Item18"
#endif  ID_LISTIMG_Item18
#ifndef ID_LISTIMG_Item19
#define ID_LISTIMG_Item19		"ID_LISTIMG_Item19"
#endif  ID_LISTIMG_Item19
#ifndef ID_LISTIMG_Item20
#define ID_LISTIMG_Item20		"ID_LISTIMG_Item20"
#endif  ID_LISTIMG_Item20
#ifndef ID_LISTIMG_Item21
#define ID_LISTIMG_Item21		"ID_LISTIMG_Item21"
#endif  ID_LISTIMG_Item21
#ifndef ID_LISTIMG_Item22
#define ID_LISTIMG_Item22		"ID_LISTIMG_Item22"
#endif  ID_LISTIMG_Item22
#ifndef ID_LISTIMG_Item23
#define ID_LISTIMG_Item23		"ID_LISTIMG_Item23"
#endif  ID_LISTIMG_Item23
#ifndef ID_LISTIMG_Item24
#define ID_LISTIMG_Item24		"ID_LISTIMG_Item24"
#endif  ID_LISTIMG_Item24
#ifndef ID_PICTURE_FinallyAward
#define ID_PICTURE_FinallyAward		"ID_PICTURE_FinallyAward"
#endif  ID_PICTURE_FinallyAward
#ifndef ID_BUTTON_Open
#define ID_BUTTON_Open		"ID_BUTTON_Open"
#endif  ID_BUTTON_Open
#ifndef ID_BUTTON_Stop
#define ID_BUTTON_Stop		"ID_BUTTON_Stop"
#endif  ID_BUTTON_Stop
#ifndef ID_BUTTON_GetAwards
#define ID_BUTTON_GetAwards		"ID_BUTTON_GetAwards"
#endif  ID_BUTTON_GetAwards
#ifndef ID_PICTURE_GetAwardLight
#define ID_PICTURE_GetAwardLight		"ID_PICTURE_GetAwardLight"
#endif  ID_PICTURE_GetAwardLight
#ifndef ID_LISTIMG_Chest
#define ID_LISTIMG_Chest		"ID_LISTIMG_Chest"
#endif  ID_LISTIMG_Chest
#ifndef ID_LISTIMG_Key
#define ID_LISTIMG_Key		"ID_LISTIMG_Key"
#endif  ID_LISTIMG_Key
#ifndef ID_PICTURE_LotteryBackground1
#define ID_PICTURE_LotteryBackground1		"ID_PICTURE_LotteryBackground1"
#endif  ID_PICTURE_LotteryBackground1
#ifndef ID_PICTURE_LotteryBackground2
#define ID_PICTURE_LotteryBackground2		"ID_PICTURE_LotteryBackground2"
#endif  ID_PICTURE_LotteryBackground2
#ifndef ID_PICTURE_LotteryBackground3
#define ID_PICTURE_LotteryBackground3		"ID_PICTURE_LotteryBackground3"
#endif  ID_PICTURE_LotteryBackground3
#ifndef ID_PICTURE_LotteryBackground4
#define ID_PICTURE_LotteryBackground4		"ID_PICTURE_LotteryBackground4"
#endif  ID_PICTURE_LotteryBackground4
#ifndef ID_PICTURE_LotteryBackground5
#define ID_PICTURE_LotteryBackground5		"ID_PICTURE_LotteryBackground5"
#endif  ID_PICTURE_LotteryBackground5
#ifndef ID_PICTURE_LotteryBackground6
#define ID_PICTURE_LotteryBackground6		"ID_PICTURE_LotteryBackground6"
#endif  ID_PICTURE_LotteryBackground6

#ifndef ID_PICTURE_LotteryBackground7
#define ID_PICTURE_LotteryBackground7		"ID_PICTURE_LotteryBackground7"
#endif  ID_PICTURE_LotteryBackground7

#include "UiBase.h"
class CUI_ID_FRAME_LotteryGame :public CUIBase, CItemEnableChangeSysBase
{
	// Member
public:	
	CUI_ID_FRAME_LotteryGame();

	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_OpenOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_StopOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_GetAwardsOnButtonClick( ControlObject* pSender );
	bool ID_LISTIMG_ChestOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_ChestOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	bool ID_LISTIMG_KeyOnIconDragOn( ControlObject* pSender, ControlObject* pMe, ControlIconDrag::S_ListImg* pItemDrag, ControlIconDrag::S_ListImg* pItemSrc );
	bool ID_LISTIMG_KeyOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );

	
private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视

public:
    void SetBoxValue( unsigned char ucBagType, short stIndex, __int64 nGuid );
    void SetKeyValue( unsigned char ucBagType, short stIndex, __int64 nGuid );

    void RefreshBoxNKeyIndexByGuid();
    void SetCurrentBg( int nIndex );
	// 更新奖品
	void UpdateRewards();

	// 更新icon
	void UpdateBoxNKeyUI();

	// 改变箱子的id，变为已摇奖
	void ChangeBoxItemId( unsigned char ucBagtype, short stIndex, __int64 nGuid, short stNewId );	
	void SetTargetResultIndex( unsigned char ucTargetIndex );

    void SetButtonStopVisable(bool bVisable);
    void SetButtonStopEnable(bool bEnable);

	void OnMsgShowTreasureBox(MsgShowTreasureBox* pMsg);
	void OnMsgTreasureBoxResult(MsgTreasureBoxResult* pMsg);

    virtual bool IsPackItemBeUsing( __int64 nGuid );

private:
	unsigned char m_uchOperate;    // 操作类型
	unsigned char m_ucItemBagType; // 背包类型
	short m_stIndex;               // 背包索引
	__int64 m_nGuid;               // 物品guid
	unsigned char m_uchLevel;      // 宝箱等级
	unsigned char m_nResultIndex;  // 摇到的宝箱奖励的索引 

	void ResetMembers();

	unsigned char m_ucKeyBagType;
	short m_stKeyIndex;
	__int64 m_nKeyGuid;

	
	void ConfigSound();	
	void SendGetMessageToServer();
	void UpdatePicRect();
	void ResetButtonState();
	void RenderMiddlePic();
	static void PostUpdateInRollingEnd();
	static void OnVisibleChanged( ControlObject* pSender );	
	static DWORD ms_dwFirstEndTime;
	ControlPicture* m_apBackground[ECD_Max_BoxLevel];
	ControlListImage* m_apRewardControl[ECD_Max_TreasureCount];

    ControlFrame*	m_pID_FRAME_LotteryGame;
    ControlText*	m_pID_TEXT_LotteryName;
    ControlListImage*	m_pID_LISTIMG_Item1;
    ControlListImage*	m_pID_LISTIMG_Item2;
    ControlListImage*	m_pID_LISTIMG_Item3;
    ControlListImage*	m_pID_LISTIMG_Item4;
    ControlListImage*	m_pID_LISTIMG_Item5;
    ControlListImage*	m_pID_LISTIMG_Item6;
    ControlListImage*	m_pID_LISTIMG_Item7;
    ControlListImage*	m_pID_LISTIMG_Item8;
    ControlListImage*	m_pID_LISTIMG_Item9;
    ControlListImage*	m_pID_LISTIMG_Item10;
    ControlListImage*	m_pID_LISTIMG_Item11;
    ControlListImage*	m_pID_LISTIMG_Item12;
    ControlListImage*	m_pID_LISTIMG_Item13;
    ControlListImage*	m_pID_LISTIMG_Item14;
    ControlListImage*	m_pID_LISTIMG_Item15;
    ControlListImage*	m_pID_LISTIMG_Item16;
    ControlListImage*	m_pID_LISTIMG_Item17;
    ControlListImage*	m_pID_LISTIMG_Item18;
    ControlListImage*	m_pID_LISTIMG_Item19;
    ControlListImage*	m_pID_LISTIMG_Item20;
    ControlListImage*	m_pID_LISTIMG_Item21;
    ControlListImage*	m_pID_LISTIMG_Item22;
    ControlListImage*	m_pID_LISTIMG_Item23;
    ControlListImage*	m_pID_LISTIMG_Item24;
    ControlPicture*	m_pID_PICTURE_FinallyAward;
    ControlPicture*	m_pID_PICTURE_GetAwardLight;
    ControlButton*	m_pID_BUTTON_Open;
    ControlButton*	m_pID_BUTTON_Stop;
    ControlButton*	m_pID_BUTTON_GetAwards;
    ControlListImage*	m_pID_LISTIMG_Chest;
    ControlListImage*	m_pID_LISTIMG_Key;
    ControlPicture*	m_pID_PICTURE_LotteryBackground1;
    ControlPicture*	m_pID_PICTURE_LotteryBackground2;
    ControlPicture*	m_pID_PICTURE_LotteryBackground3;
    ControlPicture*	m_pID_PICTURE_LotteryBackground4;
    ControlPicture*	m_pID_PICTURE_LotteryBackground5;
    ControlPicture*	m_pID_PICTURE_LotteryBackground6;
    ControlPicture*	m_pID_PICTURE_LotteryBackground7;
};
extern CUI_ID_FRAME_LotteryGame s_CUI_ID_FRAME_LotteryGame;
