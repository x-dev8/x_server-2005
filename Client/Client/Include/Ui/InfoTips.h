/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\zhuomeng.hu\桌面\InfoTips.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "MsgBase.h"

#ifndef ID_FRAME_InfoTips
#define ID_FRAME_InfoTips		"ID_FRAME_InfoTips"
#endif  ID_FRAME_InfoTips
#ifndef ID_BUTTON_Tips1
#define ID_BUTTON_Tips1		"ID_BUTTON_Tips1"
#endif  ID_BUTTON_Tips1
#ifndef ID_BUTTON_Tips2
#define ID_BUTTON_Tips2		"ID_BUTTON_Tips2"
#endif  ID_BUTTON_Tips2
#ifndef ID_BUTTON_Tips3
#define ID_BUTTON_Tips3		"ID_BUTTON_Tips3"
#endif  ID_BUTTON_Tips3
#ifndef ID_BUTTON_Tips4
#define ID_BUTTON_Tips4		"ID_BUTTON_Tips4"
#endif  ID_BUTTON_Tips4
#ifndef ID_BUTTON_Tips5
#define ID_BUTTON_Tips5		"ID_BUTTON_Tips5"
#endif  ID_BUTTON_Tips5
#ifndef ID_BUTTON_Tips6
#define ID_BUTTON_Tips6		"ID_BUTTON_Tips6"
#endif  ID_BUTTON_Tips6
#ifndef ID_BUTTON_Tips7
#define ID_BUTTON_Tips7		"ID_BUTTON_Tips7"
#endif  ID_BUTTON_Tips7
#ifndef ID_BUTTON_Tips8
#define ID_BUTTON_Tips8		"ID_BUTTON_Tips8"
#endif  ID_BUTTON_Tips8

#include "UiBase.h"
class CUI_ID_FRAME_InfoTips :public CUIBase
{
public:
	// 按钮表元素
	struct TipButton
	{
		TipButton()
		{
			pButton = 0;
			usage = eButton_Usage_None;
			rect.left = 0;
			rect.right = 0;
			rect.top = 0;
			rect.bottom = 0;
			bVisable = false;
			picName = "";
		}

		ControlButton*	pButton;
		int				usage;
		RECT			rect;
		bool			bVisable;
		std::string		picName;
	};

	// 泡泡表元素
	struct TipInformation
	{
		TipInformation()
		{
			usage = eButton_Usage_None;
			tipStr = "";
			pData = 0;
			otherListId = -1;
		}

		int				usage;
		std::string		tipStr;
		void*			pData;
		std::vector<void*>	pDataSet;	//有的元素是好多个，只有一个提示
		int				otherListId;	// 如有数据对应其它表，则保存其索引
	};

	enum EButtonUsage
	{
		eButton_Usage_None = 0,
		eButton_Usage_Raise,			// 募捐
		eButton_Usage_Convene,			// 召集
		eButton_Usage_Help,				// 帮助
		eButton_Usage_Friend,			// 好友
		eButton_Usage_Team,				// 组队
		eButton_Usage_GuildCamp,		//帮会战
		eButton_Usage_KingCamp,		//国王争夺战
		eButton_Usage_GuildMasterConvene, //帮主召集
		eButton_Usage_GuildInvite,			// 帮会邀请
		eButton_Usage_GuildTanHe,			// 帮会弹劾
		eButton_Usage_GuildApplying,		//申请加入帮会
		eButton_Usage_GuildRaise, //帮会捐赠
		eButton_Usage_Chat,				// 单聊
		eButton_Usage_PlayerLevelUp,	// 人物升级
		eButton_Usage_PetLevelUp,		// 宠物升级
		eButton_Usage_GuildSQ,			// 公会申请
		eButton_Usage_QuestFlyGY,		// 国家任务
		eButton_Usage_QuestFlyGT,
		eButton_Usage_QuestFlyHL,
		eButton_Usage_QuestFlyBS,
		eButton_Usage_AddGuildGeneral,
		eButton_Usage_FlyToPosition,
		eButton_Usage_MAX
	};

private:	
	 // Member 
	 ControlFrame*	m_pID_FRAME_InfoTips;
	 ControlButton*	m_pID_BUTTON_Tips1;
	 ControlButton*	m_pID_BUTTON_Tips2;
	 ControlButton*	m_pID_BUTTON_Tips3;
	 ControlButton*	m_pID_BUTTON_Tips4;
	 ControlButton*	m_pID_BUTTON_Tips5;
	 ControlButton*	m_pID_BUTTON_Tips6;
	 ControlButton*	m_pID_BUTTON_Tips7;
	 ControlButton*	m_pID_BUTTON_Tips8;

public:	
	// Frame
	CUI_ID_FRAME_InfoTips();
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_Tips1OnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_Tips2OnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_Tips3OnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_Tips4OnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_Tips5OnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_Tips6OnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_Tips7OnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_Tips8OnButtonClick( ControlObject* pSender );
    virtual bool IsHoldInMemory() const { return true; }
    virtual void InitializeAtEnterWorld();
	
private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视

public:
	void AddGuildCampTip(Msg *); //帮会战
	void AddKingCampTip(Msg *); //国王争夺战
	void AddRaiseTip();								// 募捐
	void AddConveneTip( uint32 officialId );		// 召集
	void UpdateHelpRemend();						// 帮助
	void AddFriendInviteTip( Msg *pMsg );			// 好友邀请
	void AddTeamInviteTip( Msg *pMsg );				// 组队邀请
	void AddGuildInviteTip( Msg *pMsg );			// 帮会邀请
	void AddGuildTanHeTip(Msg *); //帮会弹劾
	void AddGuildApplyingTip(Msg *); //申请加入帮会
	void AddGuildMasterConvene(Msg *); //帮主召集令
	void AddGuildDonateTip();//帮会捐赠
	void AddMiniChatTip( std::string strName );		// 单聊
	void AddPlayerLevelUpTip();						// 人物升级
	void AddpetLevelUpTip();						// 宠物升级
	void DeleteGuildCampTip();
	void DeleteKingCampTip();
	void AddSQInfo();
	void ADdQuestFlyGY();
	void ADdQuestFlyHL();
	void ADdQuestFlyGT();
	void ADdQuestFlyBS();
	void AddGuildGeneralInfo();
	void AddFlyToPosition();
public:
	void ProcessAddFriendReq(Msg *pMsg);        // 加对方为好友，对方的反馈
	void ProcessGuildTanHeReq(Msg *);           // 帮会弹劾
	void ProcessGuildApplyingReq(Msg *);        // 加为好友
	void ProcessGuildMasterConveneReq(Msg *);   // 帮主召集令
	void ProcessGuildRaiseReq();                // 帮会捐赠
    void ProcessCountryDonate();                // 国家募捐
	void ProcessGuildCampReq(Msg*);		//帮会战
	void ProcessKingCampReq(Msg*);		//国王争夺战

	void DeleteTip( int index );

protected:	
	void Refresh();
	void ShowTip( const TipInformation& tipInfo );
	bool DeleteTipInfo( int index );
	void SetBtnPic( int i );
	void ResetProperties();

private:
	std::vector<TipButton>			m_tipButtonsVec;
	std::vector<TipInformation>		m_tipInformationVec;

};
extern CUI_ID_FRAME_InfoTips s_CUI_ID_FRAME_InfoTips;
