/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\zhuomeng.hu\����\InfoTips.h
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
	// ��ť��Ԫ��
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

	// ���ݱ�Ԫ��
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
		std::vector<void*>	pDataSet;	//�е�Ԫ���Ǻö����ֻ��һ����ʾ
		int				otherListId;	// �������ݶ�Ӧ�������򱣴�������
	};

	enum EButtonUsage
	{
		eButton_Usage_None = 0,
		eButton_Usage_Raise,			// ļ��
		eButton_Usage_Convene,			// �ټ�
		eButton_Usage_Help,				// ����
		eButton_Usage_Friend,			// ����
		eButton_Usage_Team,				// ���
		eButton_Usage_GuildCamp,		//���ս
		eButton_Usage_KingCamp,		//��������ս
		eButton_Usage_GuildMasterConvene, //�����ټ�
		eButton_Usage_GuildInvite,			// �������
		eButton_Usage_GuildTanHe,			// ��ᵯ��
		eButton_Usage_GuildApplying,		//���������
		eButton_Usage_GuildRaise, //������
		eButton_Usage_Chat,				// ����
		eButton_Usage_PlayerLevelUp,	// ��������
		eButton_Usage_PetLevelUp,		// ��������
		eButton_Usage_GuildSQ,			// ��������
		eButton_Usage_QuestFlyGY,		// ��������
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
	virtual bool _LoadUI();				// ����UI
	bool DoControlConnect();	// �����ؼ�
	virtual bool _UnLoadUI();			// ж��UI
	virtual bool _IsVisable();			// �Ƿ�ɼ�
	virtual void _SetVisable( const bool bVisable );			// �����Ƿ����

public:
	void AddGuildCampTip(Msg *); //���ս
	void AddKingCampTip(Msg *); //��������ս
	void AddRaiseTip();								// ļ��
	void AddConveneTip( uint32 officialId );		// �ټ�
	void UpdateHelpRemend();						// ����
	void AddFriendInviteTip( Msg *pMsg );			// ��������
	void AddTeamInviteTip( Msg *pMsg );				// �������
	void AddGuildInviteTip( Msg *pMsg );			// �������
	void AddGuildTanHeTip(Msg *); //��ᵯ��
	void AddGuildApplyingTip(Msg *); //���������
	void AddGuildMasterConvene(Msg *); //�����ټ���
	void AddGuildDonateTip();//������
	void AddMiniChatTip( std::string strName );		// ����
	void AddPlayerLevelUpTip();						// ��������
	void AddpetLevelUpTip();						// ��������
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
	void ProcessAddFriendReq(Msg *pMsg);        // �ӶԷ�Ϊ���ѣ��Է��ķ���
	void ProcessGuildTanHeReq(Msg *);           // ��ᵯ��
	void ProcessGuildApplyingReq(Msg *);        // ��Ϊ����
	void ProcessGuildMasterConveneReq(Msg *);   // �����ټ���
	void ProcessGuildRaiseReq();                // ������
    void ProcessCountryDonate();                // ����ļ��
	void ProcessGuildCampReq(Msg*);		//���ս
	void ProcessKingCampReq(Msg*);		//��������ս

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
