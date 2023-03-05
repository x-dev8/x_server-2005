/********************************************************************
	Created by UIEditor.exe
	FileName: E:\Code\RunTime\CLIENT\Data\ui/MiniMapUI.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "MessageDefine.h"
#include <time.h>
#include "PlaneEffect.h"

#ifndef ID_FRAME_MiniMap
#define ID_FRAME_MiniMap		"ID_FRAME_MiniMap"
#endif  ID_FRAME_MiniMap
#ifndef ID_PICTURE_MiniMap
#define ID_PICTURE_MiniMap		"ID_PICTURE_MiniMap"
#endif  ID_PICTURE_MiniMap
#ifndef ID_PICTURE_Map
#define ID_PICTURE_Map		"ID_PICTURE_Map"
#endif  ID_PICTURE_Map
#ifndef ID_TEXT_Name
#define ID_TEXT_Name		"ID_TEXT_Name"
#endif  ID_TEXT_Name
#ifndef ID_BUTTON_MapSize
#define ID_BUTTON_MapSize		"ID_BUTTON_MapSize"
#endif  ID_BUTTON_MapSize
#ifndef ID_TEXT_PlayerPos
#define ID_TEXT_PlayerPos		"ID_TEXT_PlayerPos"
#endif  ID_TEXT_PlayerPos
#ifndef ID_BUTTON_NPClist
#define ID_BUTTON_NPClist	"ID_BUTTON_NPClist"
#endif ID_BUTTON_NPClist
#ifndef ID_BUTTON_DisMount
#define ID_BUTTON_DisMount		"ID_BUTTON_DisMount"
#endif  ID_BUTTON_DisMount
#ifndef ID_BUTTON_ChaXunAll
#define ID_BUTTON_ChaXunAll		"ID_BUTTON_ChaXunAll"
#endif  ID_BUTTON_ChaXunAll
#ifndef ID_BUTTON_GM
#define ID_BUTTON_GM		"ID_BUTTON_GM"
#endif  ID_BUTTON_GM
#ifndef ID_BUTTON_Help
#define ID_BUTTON_Help		"ID_BUTTON_Help"
#endif  ID_BUTTON_Help
#ifndef ID_BUTTON_Hide
#define ID_BUTTON_Hide		"ID_BUTTON_Hide"
#endif  ID_BUTTON_Hide
#ifndef ID_TEXT_event_tip
#define ID_TEXT_event_tip	"ID_TEXT_event_tip"
#endif	ID_TEXT_event_tip
#ifndef ID_BUTTON_Appear
#define ID_BUTTON_Appear		"ID_BUTTON_Appear"
#endif  ID_BUTTON_Appear
#ifndef ID_BUTTON_Activity
#define ID_BUTTON_Activity		"ID_BUTTON_Activity"
#endif  ID_BUTTON_Activity
#ifndef ID_BUTTON_ProtectTime
#define ID_BUTTON_ProtectTime		"ID_BUTTON_ProtectTime"
#endif  ID_BUTTON_ProtectTime
#ifndef ID_BUTTON_Track
#define ID_BUTTON_Track		"ID_BUTTON_Track"
#endif  ID_BUTTON_Track
#ifndef ID_BUTTON_Shop
#define ID_BUTTON_Shop		"ID_BUTTON_Shop"
#endif  ID_BUTTON_Shop
#ifndef ID_BUTTON_SystemSetting
#define ID_BUTTON_SystemSetting		"ID_BUTTON_SystemSetting"
#endif  ID_BUTTON_SystemSetting
#ifndef ID_PICTURE_Red
#define ID_PICTURE_Red		"ID_PICTURE_Red"
#endif  ID_PICTURE_Red
#ifndef ID_PICTURE_Yellow
#define ID_PICTURE_Yellow		"ID_PICTURE_Yellow"
#endif  ID_PICTURE_Yellow
#ifndef ID_PICTURE_Green
#define ID_PICTURE_Green		"ID_PICTURE_Green"
#endif  ID_PICTURE_Green
#ifndef ID_TEXT_PlaceTime
#define ID_TEXT_PlaceTime		"ID_TEXT_PlaceTime"
#endif  ID_TEXT_PlaceTime
#ifndef ID_BUTTON_Direct
#define ID_BUTTON_Direct		"ID_BUTTON_Direct"
#endif  ID_BUTTON_Direct
#ifndef ID_BUTTON_Cancel
#define ID_BUTTON_Cancel		"ID_BUTTON_Cancel"
#endif  ID_BUTTON_Cancel
#ifndef ID_TEXT_NextTime
#define ID_TEXT_NextTime		"ID_TEXT_NextTime"
#endif  ID_TEXT_NextTime
#ifndef ID_BUTTON_AutoAttack
#define ID_BUTTON_AutoAttack		"ID_BUTTON_AutoAttack"
#endif  ID_BUTTON_AutoAttack
#ifndef ID_BUTTON_Email
#define ID_BUTTON_Email		"ID_BUTTON_Email"
#endif  ID_BUTTON_Email
#ifndef ID_PICTURE_Email
#define ID_PICTURE_Email		"ID_PICTURE_Email"
#endif  ID_PICTURE_Email
#ifndef ID_TEXT_Email
#define ID_TEXT_Email		"ID_TEXT_Email"
#endif  ID_TEXT_Email
#ifndef ID_BUTTON_SearchTeam
#define ID_BUTTON_SearchTeam		"ID_BUTTON_SearchTeam"
#endif  ID_BUTTON_SearchTeam
#ifndef ID_BUTTON_Rank
#define ID_BUTTON_Rank		"ID_BUTTON_Rank"
#endif  ID_BUTTON_Rank
#ifndef ID_BUTTON_QuickEquip
#define ID_BUTTON_QuickEquip		"ID_BUTTON_QuickEquip"
#endif  ID_BUTTON_QuickEquip
#ifndef ID_BUTTON_MapSizeSmall
#define ID_BUTTON_MapSizeSmall		"ID_BUTTON_MapSizeSmall"
#endif  ID_BUTTON_MapSizeSmall
#ifndef ID_BUTTON_ActivityDay
#define ID_BUTTON_ActivityDay		"ID_BUTTON_ActivityDay"
#endif  ID_BUTTON_ActivityDay
#ifndef ID_PICTURE_Effect
#define ID_PICTURE_Effect		"ID_PICTURE_Effect"
#endif  ID_PICTURE_Effect

#ifndef ID_BUTTON_Achivement
#define ID_BUTTON_Achivement		"ID_BUTTON_Achivement"
#endif  ID_BUTTON_Achivement
#ifndef ID_BUTTON_DoubleExp
#define ID_BUTTON_DoubleExp		"ID_BUTTON_DoubleExp"
#endif  ID_BUTTON_DoubleExp
#ifndef ID_BUTTON_Mail
#define ID_BUTTON_Mail		"ID_BUTTON_Mail"
#endif  ID_BUTTON_Mail
#ifndef ID_BUTTON_FuJin
#define ID_BUTTON_FuJin		"ID_BUTTON_FuJin"
#endif  ID_BUTTON_FuJin
#ifndef ID_TEXT_Activity
#define	ID_TEXT_Activity	"ID_TEXT_Activity"
#endif	ID_TEXT_Activity
#ifndef ID_BUTTON_Trade
#define ID_BUTTON_Trade		"ID_BUTTON_Trade"
#endif  ID_BUTTON_Trade

#ifndef ID_BUTTON_PlayerShowALL
#define ID_BUTTON_PlayerShowALL		     "ID_BUTTON_PlayerShowALL"
#endif  ID_BUTTON_PlayerShowALL
#ifndef ID_BUTTON_PlayerShowAmity
#define ID_BUTTON_PlayerShowAmity		 "ID_BUTTON_PlayerShowAmity"
#endif  ID_BUTTON_PlayerShowAmity
#ifndef ID_BUTTON_PlayerHideALL
#define ID_BUTTON_PlayerHideALL		     "ID_BUTTON_PlayerHideALL"
#endif  ID_BUTTON_PlayerHideALL
#ifndef ID_BUTTON_PlayerShowAntagonize
#define ID_BUTTON_PlayerShowAntagonize	 "ID_BUTTON_PlayerShowAntagonize"
#endif  ID_BUTTON_PlayerShowAntagonize

#ifndef ID_BUTTON_Card
#define ID_BUTTON_Card		"ID_BUTTON_Card"
#endif  ID_BUTTON_Card
#ifndef ID_TEXT_Card
#define ID_TEXT_Card		"ID_TEXT_Card"
#endif  ID_TEXT_Card
#ifndef ID_TEXT_Shop
#define ID_TEXT_Shop		"ID_TEXT_Shop"
#endif  ID_TEXT_Shop

#ifndef ID_CHECKBOX_HideChatList
#define ID_CHECKBOX_HideChatList		"ID_CHECKBOX_HideChatList"
#endif  ID_CHECKBOX_HideChatList

#ifndef ID_TEXT_Channel
#define ID_TEXT_Channel		"ID_TEXT_Channel"
#endif  ID_TEXT_Channel
#ifndef ID_BUTTON_Channel
#define ID_BUTTON_Channel		"ID_BUTTON_Channel"
#endif  ID_BUTTON_Channel

#ifndef ID_BUTTON_OpenQuestEntrust
#define ID_BUTTON_OpenQuestEntrust		"ID_BUTTON_OpenQuestEntrust"
#endif  ID_BUTTON_OpenQuestEntrust

#include "UiBase.h"
class CUI_ID_FRAME_MiniMap :public CUIBase
{
	// SGuildMember
public:
	 CUI_ID_FRAME_MiniMap();

	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
    bool OnFrameRenderPostUI();
	bool OnFrameRenderNeedRedraw();
	// Button
    bool ID_BUTTON_DirectOnButtonClick( ControlObject* pSender );
    bool ID_BUTTON_CancelOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_HelpOnButtonClick( ControlObject* pSender );
    bool ID_BUTTON_NPCListOnButtonClick( ControlObject* pSender );
	//bool ID_BUTTON_TrackOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_ActivityOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_ProtectTimeOnButtonClick( ControlObject* pSender );
    bool ID_BUTTON_MapSizeOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_SystemSettingOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_ShopOnButtonClick( ControlObject* pSender );
    bool ID_BUTTON_AutoAttackOnButtonClick( ControlObject* pSender );
    bool ID_BUTTON_EmailOnButtonClick( ControlObject* pSender );
    bool ID_BUTTON_HideOnButtonClick( ControlObject* pSender );
    bool ID_BUTTON_AppearOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_MapSizeSmallOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_AchivementOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_DoubleExpOnButtonClick( ControlObject* pSender );
	//bool ID_BUTTON_SearchTeamOnButtonClick( ControlObject* pSender );	
	//bool ID_BUTTON_QuickEquipOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_RankOnButtonClick( ControlObject* pSender );
    bool ID_BUTTON_ActivityDayOnButtonClick( ControlObject* pSender );

	bool ID_BUTTON_MailOnButtonClick( ControlObject* pSender );
	bool ID_TEXT_MailOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_FuJinOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_TradeOnButtonClick( ControlObject* pSender );
	void SetButtonToCustom();

	bool ID_BUTTON_PlayerShowALLOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_PlayerShowAmityOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_PlayerHideALLOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_PlayerShowAntagonizeOnButtonClick( ControlObject* pSender );

	bool ID_BUTTON_CardOnButtonClick( ControlObject* pSender );
	bool ID_TEXT_CardOnButtonClick( ControlObject* pSender );
	bool ID_TEXT_ShopOnButtonClick( ControlObject* pSender );

	void ID_CHECKBOX_HideChatListOnClick(ControlObject* pSender, bool* pbChecked);
	bool ID_BUTTON_ChannelOnButtonClick( ControlObject* pSender );

	bool ID_BUTTON_OpenQuestEntrustOnButtonClick ( ControlObject* pSender );

	virtual bool IsHoldInMemory() const { return true; }
	virtual void InitializeAtEnterWorld();

	void SetRenderPlayerFlag(unsigned int _flag, bool bCompositor = false)
	{
		m_bCompositor = bCompositor;
		m_nPlayerRenderFlag = _flag;
	}

	unsigned int GetRenderPlayerFlag(){return m_nPlayerRenderFlag;}

	bool HasRenderFlag(unsigned int flag) { return m_nPlayerRenderFlag == flag; }
	
private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );						// 设置是否可视

public:
	void SetDisMountButtonVisable( const bool bVisable );		// 设置下马按键是否可见

	void startHelp();

	void Refeash();

	float GetZoomScale();
	void SetCheckAngle(bool bChecked);
	void SetCheckMouse(bool bChecked);

	void OnMsgEctypeMapInfo( Msg* pMsg );
	void haveNewEventHappen( int id );
	void update();
	void setBtnRay();
	void firstInWorldEventInfo( std::vector<int>& duringEventIn );

    void SetServerName(const char* name);
    void ShowMapName(DWORD col);

	static bool frame_msg(UINT msg, WPARAM wParam, LPARAM lParam, bool bMsgUsed);
    static bool	m_bTipActive;

	bool ResetZoneInfo();


    void UpdateProtectTimeCountDown();
    void SetPing(int ping);
	void UpdatePing();

	DWORD GetEctypeMapTimeRemain();
    void ResetEctypeMapTimeRemain();
    void SetEctypeMapTimeRemain( DWORD time );
    void UpdateEctypeMapTimeRemain();

	void SetLastPFPoint(float mapX,float mapY,int nMapId);

	void	SetAutoRuning(bool val);

	void ShowGameStageTime(int stage, int maxStage, int duration);
	void RefreshGameStageTime();

    static bool MailProcessPress(const char bPressYesButton,void *pData);

    void ProcessMailNotify();
    void SetSplashTime(DWORD dwValue);
    void SetSplash(bool bValue){m_bSplash = bValue;}
    void SetMailSender(const char* pszMailSender);
    void SetTipInMail(bool bVisable);
	const std::string& GetServerName() { return m_strServerName; }

	ControlFrame* GetFrame() { return m_pID_FRAME_MiniMap; }
	ControlText* GetTEXT_PlayerPos();
	ControlButton* GetBUTTON_Activity();
	ControlButton* GetBUTTON_NPCList();
	ControlButton* GetBUTTON_Track();
	ControlButton* GetBUTTON_Shop();
	ControlButton* GetBUTTON_AutoAttack();
	ControlPicture* GetPICTURE_Map();
    int             GetMapID(){return m_nMap;}
    void UpdateByLevelUp();
   
	void GetPicMapRect(RECT &_rect)
	{
		assert(m_pID_PICTURE_Map);
    m_pID_PICTURE_Map->GetRealRect(&_rect);
		 
	}

	void SetCardTextShow(bool bshow);
	void SetShopTextShow(bool bshow);

	bool IsHideChatListChecked() { return m_pID_CHECKBOX_HideChatList->IsChecked(); }

	void ShowChannelName();

private:
	void ResetMembers();
    void CreateTodayActEffect();
    void DisplayTodayActEffect();       // 今日指引特效

private:
    DWORD m_dwStartSplash;  //用于邮件提示
    bool  m_bLastMailVisable; //上次邮件显示状态
    bool  m_bSplash;         //是否闪烁
    std::string m_SenderMail;  //发送邮件的人
	bool  m_bLastCardVisable;
	bool  m_bLastShopVisable;

	ControlFrame*	    m_pID_FRAME_MiniMap; 
    ControlPicture*	    m_pID_PICTURE_Map;
    ControlButton*		m_pID_BUTTON_Cancel;
    ControlButton*	    m_pID_BUTTON_Direct;
    ControlPicture*	    m_pID_PICTURE_MiniMap;
    ControlText*		m_pID_TEXT_Name;
    ControlButton*		m_pID_BUTTON_Help;
    ControlButton*		m_pID_BUTTON_NPCList;
    ControlText*		m_pID_TEXT_PlayerPos;
    //ControlButton*	    m_pID_BUTTON_Track;
    ControlButton*		m_pID_BUTTON_Hide;
    ControlButton*		m_pID_BUTTON_Appear;
    ControlButton*	    m_pID_BUTTON_Activity;
	ControlText*	    m_pID_TEXT_Activity;
    ControlButton*		m_pID_BUTTON_ProtectTime;
    ControlButton*		m_pID_BUTTON_MapSize;
	ControlButton*		m_pID_BUTTON_SystemSetting;
    ControlPicture*		m_pID_PICTURE_Green;
    ControlPicture*		m_pID_PICTURE_Yellow;
    ControlPicture*		m_pID_PICTURE_Red;
    //     ControlText*		m_pID_TEXT_PlaceTime;
    ControlButton*	    m_pID_BUTTON_Shop;
    // 
    //     ControlText*		m_pID_TEXT_NextTime;
    ControlButton*	    m_pID_BUTTON_AutoAttack;
    ControlButton*	    m_pID_BUTTON_Email;
    ControlPicture*	    m_pID_PICTURE_Email;
    ControlPicture*     m_pID_PICTURE_Effect;
    ControlText*	    m_pID_TEXT_Email;

//	ControlButton*		m_pID_BUTTON_SearchTeam;
	ControlButton*		m_pID_BUTTON_Rank;
//	ControlButton*		m_pID_BUTTON_QuickEquip;
	ControlButton*		m_pID_BUTTON_MapSizeSmall;
	ControlButton*		m_pID_BUTTON_Achivement;
	ControlButton*		m_pID_BUTTON_DoubleExp;
    ControlButton*	    m_pID_BUTTON_ActivityDay;

	ControlButton*	    m_pID_BUTTON_Mail;
	ControlButton*  	m_pID_BUTTON_FuJin;
	ControlButton*  	m_pID_BUTTON_Trade;

	ControlButton*	m_pID_BUTTON_Card;
	ControlText*	m_pID_TEXT_Card;
	ControlText*	m_pID_TEXT_Shop;

	ControlCheckBox* m_pID_CHECKBOX_HideChatList;
	ControlText*	m_pID_TEXT_Channel;
	ControlButton*	m_pID_BUTTON_Channel;

    ControlGroup		m_GroupAllUI;


    bool				m_bHaveNew_event;
    clock_t				m_tmBegin_show_tip;
    bool				m_bIsNormal_state;
    bool				m_bIsPress_state;
    clock_t				m_tmBtn_raytime;


    std::string         strLastTileName;
    std::string         strLastZoneName;

    bool			    m_bZoomIn;
    std::string		    m_strMapName;
    std::string		    m_strAreaName;
    DWORD			    m_dwCurEctypeId;
    bool                bIsOnButtonDisMount;
    bool				bFullScreen;	//保存全屏值 假全屏
    unsigned int        m_nPing;

    std::string         m_strServerName;


    float               m_fZoomScale;

    bool                m_bLowSetting;
    bool                m_bAutoRuning;
    DWORD               m_dwEctypeMapEndTime;

    DWORD               m_dwStartGSTime;
    int                 m_GSDuration;
    int	                m_gameStage;
    int	                m_maxGameStage;

    float	            m_lastPFX;
    float	            m_lastPFY;
    int		            m_nMap;

    CPlaneEffect*       m_pTodayActEff;             // 今日指引特效
    bool                m_bPlayTodayActEffect;      // 是否播放今日指引特效

	//===========================================================
	ControlButton*		m_pPlayerShowBtn[PSM_Max];
	ControlButton*      m_pCurPlayerShowBtn;
	bool                m_bPlayerShowModeOpen;  //列表是否展

public:
	void  SetPlayerModeOpenOrClose(ControlObject* pSender);
	void  compositor(bool IsChangeCurShowBtn = false);  //排序
	unsigned int		m_nPlayerRenderFlag;
	bool                m_bCompositor;

	int     ShowPlayerBtnPosX;
	int     ShowPlayerBtnPosY;
	ControlButton*	m_pID_BUTTON_PlayerShowALL;
	ControlButton*	m_pID_BUTTON_PlayerShowAmity;
	ControlButton*	m_pID_BUTTON_PlayerHideALL;
	ControlButton*	m_pID_BUTTON_PlayerShowAntagonize;

	ControlButton*	m_pID_BUTTON_OpenQuestEntrust;
	
};
extern CUI_ID_FRAME_MiniMap s_CUI_ID_FRAME_MiniMap;