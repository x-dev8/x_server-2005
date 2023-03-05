/********************************************************************
	Filename : UI\GameSetting.h
*********************************************************************/
#pragma once

class GameSetting 
{
public://enum

	/*
	@desc: category
	*/
	enum eGameSettingCategory
	{
		eGSC_CHATFONTSIZE,		//���������С
		eGSC_AUTOREPLYSECRET,	//�Զ��ظ�����
		eGSC_AUTOTURNAROUND,	//����ת��
		eGSC_AUTOMOUSE,			//�������
		eGSC_SHOWHELMET,		//��ʾͷ��
		eGSC_VERTICLEVIEW,		//��ֱ�ӽ�����
		eGSC_SHOWNPCNAME,		//��ʾNPC����
		eGSC_SHOWITEMNAME,		//��ʾ��Ʒ����
		eGSC_SHOWPLAYERNAME,	//��ʾ�������
		eGSC_SHOWTITLE,			//��ʾ�ƺ�
		eGSC_SHOWPLAYERNUMBER,	//ͬ������
		eGSC_FOV,				//���
		eGSC_MAXCAMERADISTANCE,	//��ͷ������
		eGSC_SHOWHPBARMP,		//��ʾhp,mp����		
		eGSC_SHOWFP,			//��ʾfp����
		eGSC_45CAMERA,			//45�����ӽ�
		eGSC_FOLLOWCAMERA,		//�������
		eGSC_SAVECHATMESSAGE,	//���������¼
		eGSC_SHOWHPBAR,			//��ʾHP
		eGSC_SHOWMPBAR,			//��ʾMP
		eGSC_SHOWFPBAR,			//��ʾFP
		eGSC_SHOWCHATBACKGROUND,//��ʾ���촰�ڱ���
		eGSC_MOUSESPEED,		//���������
		eGSC_CAMERAROTATESPEED, //�������ת�ٶ�
		eGSC_SelfName,			//��������
		eGSC_SelfHp,			//����Ѫ��
		eGSC_SelfMp,			//��������
		eGSC_SelfGuild,			//������
		eGSC_SelfTitle,			//����ƺ�
		eGSC_SelfTong,			//��������
		eGSC_SelfPetName,		//�����������
		eGSC_SelfPetHp,			//�������Ѫ��
		eGSC_NpcName,			//NPC����
		eGSC_NpcHp,				//NPCѪ��
		eGSC_NpcTitle,			//NPC����
		eGSC_MonsterName,		//Monster����
		eGSC_MonsterHp,			//MonsterѪ��
		eGSC_ItemName,			//����Item����
		eGSC_TeamPlayerName,	//����ͷ������
		eGSC_TeamPlayerHp,		//����ͷ��Ѫ��
		eGSC_TeamPlayerTitle,	//����ͷ���ƺ�
		eGSC_TeamPlayerGuild,	//����ͷ�����
		eGSC_TeamPlayerTong,	//����ͷ������
		eGSC_TeamPlayerPetName,	//�����ٻ���ͷ������
		eGSC_TeamPlayerPetHp,	//�����ٻ���ͷ��Ѫ��
		eGSC_OtherPlayerName,	//�Ƕ���ͷ������
		eGSC_OtherPlayerHp,		//�Ƕ���ͷ��Ѫ��
		eGSC_OtherPlayerTitle,	//�Ƕ���ͷ���ƺ�
		eGSC_OtherPlayerGuild,	//�Ƕ���ͷ�����
		eGSC_OtherPlayerTong,	//�Ƕ���ͷ������
		eGSC_OtherPlayerPetName,//�Ƕ����ٻ���ͷ������
		eGSC_OtherPlayerPetHp,	//�Ƕ����ٻ���ͷ��Ѫ��
		eGSC_FightFlyText,		//ս��Ʈ��
		eGSC_RefuseStrangerMsg,	//�ܾ�İ���˶���Ϣ
		eGSC_RefuseAllMsg,		//�ܾ������˶���Ϣ

		eGSC_MiniMapTeam,		//С��ͼ��ʾ����
		eGSC_MiniMapNpc,		//С��ͼ��ʾNpc
		eGSC_MiniMapMonster,	//С��ͼ��ʾMonster
		eGSC_MiniMapFriend,		//С��ͼ��ʾ����
		eGSC_MiniMapGuild,		//С��ͼ��ʾ����
		eGSC_MiniMapEnemy,		//С��ͼ��ʾ����
		eGSC_MiniMapOther,		//С��ͼ��ʾ�������
		eGSC_ChatSelf,			//��ʾ������������
		eGSC_ChatTeam,			//��ʾ������������
		eGSC_ChatOther,			//��ʾ��������������
		eGSC_SOUND,				//������С
		eGSC_SOUNDEFFECT,		//������Ч
		eGSC_ChatNpc,           //��ʾNPC��������
        eGSC_ChatMonster,       //��ʾ������������
        eGSC_SelfPetTitle,      //�Լ�����ƺ�
        eGSC_TeamPetTitle,      //���ѳ���ƺ�
        eGSC_OtherPetTitle,     //�Ƕ��ѳ���ƺ�
        eGSC_SelfEffect,        //������Ч
        eGSC_TeamPlayerEffect,  //������Ч
        eGSC_TeamPlayerModel,   //��������ģ��
        eGSC_OtherPlayerEffect, //�Ƕ�����Ч
        eGSC_OtherPlayerModel,  //�Ƕ�������ģ��
        eGSC_RefuseAddFriendInFight,//ս���оܾ��Ӻ�������
        eGSC_RefuseAddTeamInFight,  //ս���оܾ��������
        eGSC_RefuseAddGangInFight,  //ս���оܾ���������
        eGSC_RefuseDuelInFight,     //ս���оܾ���������
        eGSC_RefuseBargainInFight,  //ս���оܾ���������
        eGSC_RefuseHugInFight,     //ս���оܾ�ӵ������
        eGSC_RefuseAddFriend,   //��ս���оܾ��Ӻ�������
        eGSC_RefuseAddTeam,     //��ս���оܾ��������
        eGSC_RefuseAddGang,     //��ս���оܾ���������
        eGSC_RefuseDuel,        //��ս���оܾ���������
        eGSC_RefuseBargain,     //��ս���оܾ���������
        eGSC_RefuseHug,        //��ս���оܾ�ӵ������
		eGSC_IntroductionEnable,        //��ս���оܾ�ӵ������
		eGSC_ChatListWidth,        //�����Ŀ��
		eGSC_ChatListHeight,        //�����ĸ߶�

		eGSC_SellPrompt1,
		eGSC_SellPrompt2,
		eGSC_SellPrompt3,
		eGSC_SellPrompt4,
		eGSC_SellPrompt5,
		eGSC_SellPrompt6,

		eGSC_TabMe					,	// ����
		eGSC_TabMyPet				,	// �ҵ��ٻ��޻�ū��
		eGSC_TabTeamPlayer			,	// ����
		eGSC_TabTeamPlayerPet		,	// ���ѵ��ٻ��޻�ū��
		eGSC_TabEnemyGuildPlayer	,	// �ж԰�����
		eGSC_TabEnemyGuildPlayerPet	,	// �ж԰����ҵ��ٻ��޻�ū��
		eGSC_TabLeaguePlayer		,	// ͬ�����
		eGSC_TabLeaguePlayerPet		,	// ͬ����ҵ��ٻ��޻�ū��
		eGSC_TabMyGuildPlayer		,	// �Լ�������
		eGSC_TabMyGuildPlayerPet	,	// �Լ������ҵ��ٻ��޻�ū��
		eGSC_TabNormalPlayer		,	// ��ͨ���
		eGSC_TabNormalPlayerPet		,	// ��ͨ��ҵ��ٻ��޻�ū��
		eGSC_TabRedNamePlayer		,	// �������ж����
		eGSC_TabRedNamePlayerPet	,	// �������ж���ҵ��ٻ��޻�ū��
		eGSC_TabPKPlayer			,	// PK���
		eGSC_TabPKPlayerPet			,	// PK��ҵ��ٻ��޻�ū��
		eGSC_TabMonster				,	// ����
		eGSC_TabOther				,	// ����
        eSSC_SKILLLOCK              ,   //����������
        eSSC_SKILLLOCK2             ,   //������������չ
        eSSC_CLOSE_AUTO_SELECT      ,   //�Զ�ѡ��
		eGSC_TOTAL
	};


public://public static functions	
	static GameSetting* Instance();	
	static bool		    Destroy();

public://public functions

	///~ctor
	~GameSetting();

	///set level
	void SetLevel( eGameSettingCategory eCategory, 
		unsigned int uiValue );

	///get level
	unsigned int GetLevel( eGameSettingCategory eCategory );

	///load setting
	bool LoadSetting( const char* pszFileName = NULL );

	///save setting
	bool SaveSetting( const char* pszFileName );

	///Commit changes
	void CommitChanges();

	//added by zilong. 2011-03-11. ---------------------------------
	void CommitChanges(eGameSettingCategory eCategory);
	//added by zilong. end. ----------------------------------------

	const char* GetCustomSettingDirectory();

	///��ʾ���촰�ڱ���
	void ShowChatBackground( unsigned int uiValue );
	bool IsShowChatBackground() { return m_Settings[eGSC_SHOWCHATBACKGROUND]; }

	/// ����/��Ч�Ĵ�ȡ
	int MakeSoundValue( int nValue, bool bSilence );
	void GetSoundValue( int nFinalValue, int& nValue, bool& bSilence );

protected://protected functions

	///ctor
	GameSetting();

	///remove read-only flag
	void RemoveReadOnlyAttribute( const char* pszFilename );

	///is later change
	bool IsLaterChange( eGameSettingCategory eCategory );

	///ʵ�ʱ任
	void ChangeSetting( eGameSettingCategory eCategory, 
 			unsigned int uiValue );

	///���������С
	void SetChatFontSize( unsigned int uiValue );

	///�Զ��ظ�����
	void SetAutoReplySecret( unsigned int uiValue );

	///����ת��
	void SetAutoTurnAround( unsigned int uiValue );

	///�������
	void SetAutoMouse( unsigned int uiValue );

	///��ʾͷ��
	void SetShowHelmet( unsigned int uiValue );

	///��ֱ�ӽ�����
	void SetVerticleView( unsigned int uiValue );

	///��ʾNPC����
	void SetShowNPCName( unsigned int uiValue );

	///��ʾ��Ʒ����
	void SetShowItemName( unsigned int uiValue );

	///��ʾ�������
	void SetShowPlayerName( unsigned int uiValue );

	///��ʾ�ƺ�
	void SetShowTitle( unsigned int uiValue );

	///ͬ������
	void SetShowPlayerNumber( unsigned int uiValue );

	///���
	void SetFOV( unsigned int uiValue );

	///��ͷ������
	void SetMaxCameraDistance( unsigned int uiValue );
	
	///��ʾhp,mp
	void ShowHpMp( unsigned int uiValue );

	///��ʾfp
	void ShowFp( unsigned int uiValue );

	///45����
	void Set45Camera( unsigned int uiValue );

	///�������
	void SetFollowCamera( unsigned int uiValue );

	///��ʾHP
	void ShowHPBar( unsigned int uiValue );

	///��ʾMP
	void ShowMPBar( unsigned int uiValue );

	///��ʾFP
	void ShowFPBar( unsigned int uiValue );

	///���������
	void SetMouseSpeed( unsigned int uiValue );

	///�������ת�ٶ�FP
	void SetCameraRotateSpeed( unsigned int uiValue );

	//������С
	void SetSound( unsigned int uiValue );

	//������Ч
	void SetSoundEffect( unsigned int uiValue );

	///boolֵ������
	void SetBool( eGameSettingCategory eCategory, bool bValue );

protected://protected static members
	static GameSetting* ms_pThis;

protected://protected members
	unsigned int m_Settings[eGSC_TOTAL];
	std::string m_SettingNames[eGSC_TOTAL];	
	bool m_bDirty[eGSC_TOTAL];
};
