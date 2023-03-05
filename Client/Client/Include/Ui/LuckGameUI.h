/********************************************************************
	Created by UIEditor.exe
	FileName: F:\Hero\Program\trunk\Bin\Client\Data\Ui\LuckGame.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "LGStatus.h"
#include "LuckRewardConfig.h"
#include "LuckAwardUI.h"

#ifndef ID_FRAME_LuckGame
#define ID_FRAME_LuckGame		"ID_FRAME_LuckGame"
#endif  ID_FRAME_LuckGame
#ifndef ID_PICTURE_Background
#define ID_PICTURE_Background		"ID_PICTURE_Background"
#endif  ID_PICTURE_Background
#ifndef ID_PICTURE_Light
#define ID_PICTURE_Light		"ID_PICTURE_Light"
#endif  ID_PICTURE_Light
#ifndef ID_PICTURE_Dice
#define ID_PICTURE_Dice		"ID_PICTURE_Dice"
#endif  ID_PICTURE_Dice
#ifndef ID_BUTTON_Begin
#define ID_BUTTON_Begin		"ID_BUTTON_Begin"
#endif  ID_BUTTON_Begin
#ifndef ID_BUTTON_Stop
#define ID_BUTTON_Stop		"ID_BUTTON_Stop"
#endif  ID_BUTTON_Stop
#ifndef ID_PICTURE_Unknown
#define ID_PICTURE_Unknown		"ID_PICTURE_Unknown"
#endif  ID_PICTURE_Unknown
#ifndef ID_PICTURE_Fire
#define ID_PICTURE_Fire		"ID_PICTURE_Fire"
#endif  ID_PICTURE_Fire
#ifndef ID_BUTTON_CLOSE
#define ID_BUTTON_CLOSE		"ID_BUTTON_CLOSE"
#endif  ID_BUTTON_CLOSE
#ifndef ID_PICTURE_MissionText1
#define ID_PICTURE_MissionText1		"ID_PICTURE_MissionText1"
#endif  ID_PICTURE_MissionText1
#ifndef ID_PICTURE_MissionText2
#define ID_PICTURE_MissionText2		"ID_PICTURE_MissionText2"
#endif  ID_PICTURE_MissionText2
#ifndef ID_PICTURE_MissionText3
#define ID_PICTURE_MissionText3		"ID_PICTURE_MissionText3"
#endif  ID_PICTURE_MissionText3
#ifndef ID_PICTURE_MissionText4
#define ID_PICTURE_MissionText4		"ID_PICTURE_MissionText4"
#endif  ID_PICTURE_MissionText4
#ifndef ID_PICTURE_MissionText5
#define ID_PICTURE_MissionText5		"ID_PICTURE_MissionText5"
#endif  ID_PICTURE_MissionText5
#ifndef ID_PICTURE_MissionText6
#define ID_PICTURE_MissionText6		"ID_PICTURE_MissionText6"
#endif  ID_PICTURE_MissionText6
#ifndef ID_PICTURE_MissionText7
#define ID_PICTURE_MissionText7		"ID_PICTURE_MissionText7"
#endif  ID_PICTURE_MissionText7
#ifndef ID_PICTURE_MissionText8
#define ID_PICTURE_MissionText8		"ID_PICTURE_MissionText8"
#endif  ID_PICTURE_MissionText8
#ifndef ID_PICTURE_MissionText9
#define ID_PICTURE_MissionText9		"ID_PICTURE_MissionText9"
#endif  ID_PICTURE_MissionText9
#ifndef ID_PICTURE_MissionText10
#define ID_PICTURE_MissionText10		"ID_PICTURE_MissionText10"
#endif  ID_PICTURE_MissionText10
#ifndef ID_PICTURE_MissionText11
#define ID_PICTURE_MissionText11		"ID_PICTURE_MissionText11"
#endif  ID_PICTURE_MissionText11
#ifndef ID_PICTURE_MissionText12
#define ID_PICTURE_MissionText12		"ID_PICTURE_MissionText12"
#endif  ID_PICTURE_MissionText12
#ifndef ID_PICTURE_MissionText13
#define ID_PICTURE_MissionText13		"ID_PICTURE_MissionText13"
#endif  ID_PICTURE_MissionText13
#ifndef ID_PICTURE_MissionText14
#define ID_PICTURE_MissionText14		"ID_PICTURE_MissionText14"
#endif  ID_PICTURE_MissionText14
#ifndef ID_PICTURE_MissionText15
#define ID_PICTURE_MissionText15		"ID_PICTURE_MissionText15"
#endif  ID_PICTURE_MissionText15

#include "UiBase.h"
class CUI_ID_FRAME_LuckGame :public CUIBase
{
	// Member
public:	
	 CUI_ID_FRAME_LuckGame();

	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_BeginOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_StopOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender );

	
private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
public:


	void AddReward( const RewardData& data );
	void StartRoll();
	void SetRewardResult( unsigned char ucReward );
	void UpdateResultByResult();
	void RefreshRewardList();
	void EnableGetAward( bool bEnable );
	void ClearLastRewards(){
		s_CUI_ID_FRAME_LuckAward.ClearLastRewards();
	}

	void ShowMissionText( int n );
	void SetCurrentLevel( unsigned char ucLevel ){
		m_ucCurrentLevel = ucLevel;
	}

    void SetButtonBeginVisable(bool bVisval);
    void SetButtonStopVisable(bool bVisable);

    void SetButtonBeginEnable(bool bEnable);
    void SetButtonStopEnable(bool bEnable);

protected:
	void ResetMembers();

	void UpdatePicRect();
	void ResetButtonState();
	void ResetButtonEnableState();
	void ConfigSound();
	unsigned int GetStateTypeByRewardType();
	void SendGetMessageToServer();

	typedef std::vector< RewardData > RewardIDArr;
	RewardIDArr m_aRewardIds;

	bool m_bNewBegin;
	ControlGroup m_GroupMissionTexts;
	unsigned int m_uiRewardListBeginIndex;
	unsigned char m_ucReward;
	unsigned char m_ucCurrentLevel;
	static void OnVisibleChanged( ControlObject* pSender );
	static void PostUpdateInRollingEnd();
	static bool GetAwardsFunc( const bool bPressYesButton, void *pData );
	static DWORD ms_dwFirstEndTime;
private:
    ControlFrame*	m_pID_FRAME_LuckGame;
    ControlPicture*	m_pID_PICTURE_Background;
    ControlPicture*	m_pID_PICTURE_Light;
    ControlPicture*	m_pID_PICTURE_Dice;
    ControlButton*	m_pID_BUTTON_Begin;
    ControlButton*	m_pID_BUTTON_Stop;
    ControlPicture*	m_pID_PICTURE_Unknown;
    ControlPicture*	m_pID_PICTURE_Fire;
    ControlButton*	m_pID_BUTTON_CLOSE;
    ControlPicture*	m_pID_PICTURE_MissionText1;
    ControlPicture*	m_pID_PICTURE_MissionText2;
    ControlPicture*	m_pID_PICTURE_MissionText3;
    ControlPicture*	m_pID_PICTURE_MissionText4;
    ControlPicture*	m_pID_PICTURE_MissionText5;
    ControlPicture*	m_pID_PICTURE_MissionText6;
    ControlPicture*	m_pID_PICTURE_MissionText7;
    ControlPicture*	m_pID_PICTURE_MissionText8;
    ControlPicture*	m_pID_PICTURE_MissionText9;
    ControlPicture*	m_pID_PICTURE_MissionText10;
    ControlPicture*	m_pID_PICTURE_MissionText11;
    ControlPicture*	m_pID_PICTURE_MissionText12;
    ControlPicture*	m_pID_PICTURE_MissionText13;
    ControlPicture*	m_pID_PICTURE_MissionText14;
    ControlPicture*	m_pID_PICTURE_MissionText15;
};
extern CUI_ID_FRAME_LuckGame s_CUI_ID_FRAME_LuckGame;
