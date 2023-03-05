/********************************************************************
	Created by UIEditor.exe
	FileName: D:\My Documents\桌面\新十X关\LuckAward.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "LuckRewardConfig.h"

#ifndef ID_FRAME_LuckAward
#define ID_FRAME_LuckAward		"ID_FRAME_LuckAward"
#endif  ID_FRAME_LuckAward
#ifndef ID_PICTURE_Background
#define ID_PICTURE_Background		"ID_PICTURE_Background"
#endif  ID_PICTURE_Background
#ifndef ID_BUTTON_GetAwards
#define ID_BUTTON_GetAwards		"ID_BUTTON_GetAwards"
#endif  ID_BUTTON_GetAwards
#ifndef ID_BUTTON_LeftAward
#define ID_BUTTON_LeftAward		"ID_BUTTON_LeftAward"
#endif  ID_BUTTON_LeftAward
#ifndef ID_BUTTON_RightAward
#define ID_BUTTON_RightAward		"ID_BUTTON_RightAward"
#endif  ID_BUTTON_RightAward
#ifndef ID_LISTIMG_Award
#define ID_LISTIMG_Award		"ID_LISTIMG_Award"
#endif  ID_LISTIMG_Award
#ifndef ID_TEXT_Page
#define ID_TEXT_Page		"ID_TEXT_Page"
#endif  ID_TEXT_Page
#ifndef ID_BUTTON_CLOSE
#define ID_BUTTON_CLOSE		"ID_BUTTON_CLOSE"
#endif  ID_BUTTON_CLOSE
#include "UiBase.h"
class CUI_ID_FRAME_LuckAward :public CUIBase
{
	// Member
public:	
	 CUI_ID_FRAME_LuckAward();

	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_GetAwardsOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_LeftAwardOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_RightAwardOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender );

	
private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
public:

	void RefreshRewardList();
	void AddReward( const RewardData& data );
	void SetRewardType( unsigned char ucType ){ uchRewardType = ucType; }
	void SendGetMsgToServer();
	void ClearLastRewards(){
		m_aRewardIds.clear();
	}
protected:
	typedef std::vector< RewardData > RewardIDArr;
	RewardIDArr m_aRewardIds;
	unsigned char uchRewardType;
	int m_nRewardListBeginIndex ;

    ControlFrame*	m_pID_FRAME_LuckAward;
    ControlPicture*	m_pID_PICTURE_Background;
    ControlButton*	m_pID_BUTTON_GetAwards;
    ControlButton*	m_pID_BUTTON_LeftAward;
    ControlButton*	m_pID_BUTTON_RightAward;
    ControlListImage*	m_pID_LISTIMG_Award;
    ControlText*	m_pID_TEXT_Page;
    ControlButton*	m_pID_BUTTON_CLOSE;
};
extern CUI_ID_FRAME_LuckAward s_CUI_ID_FRAME_LuckAward;
