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
		eGSC_CHATFONTSIZE,		//聊天字体大小
		eGSC_AUTOREPLYSECRET,	//自动回复密语
		eGSC_AUTOTURNAROUND,	//智能转身
		eGSC_AUTOMOUSE,			//智能鼠标
		eGSC_SHOWHELMET,		//显示头盔
		eGSC_VERTICLEVIEW,		//垂直视角锁定
		eGSC_SHOWNPCNAME,		//显示NPC名字
		eGSC_SHOWITEMNAME,		//显示物品名字
		eGSC_SHOWPLAYERNAME,	//显示玩家名字
		eGSC_SHOWTITLE,			//显示称号
		eGSC_SHOWPLAYERNUMBER,	//同屏人数
		eGSC_FOV,				//广角
		eGSC_MAXCAMERADISTANCE,	//镜头最大距离
		eGSC_SHOWHPBARMP,		//显示hp,mp文字		
		eGSC_SHOWFP,			//显示fp文字
		eGSC_45CAMERA,			//45锁定视角
		eGSC_FOLLOWCAMERA,		//相机跟踪
		eGSC_SAVECHATMESSAGE,	//保存聊天记录
		eGSC_SHOWHPBAR,			//显示HP
		eGSC_SHOWMPBAR,			//显示MP
		eGSC_SHOWFPBAR,			//显示FP
		eGSC_SHOWCHATBACKGROUND,//显示聊天窗口背景
		eGSC_MOUSESPEED,		//鼠标灵敏度
		eGSC_CAMERAROTATESPEED, //摄像机旋转速度
		eGSC_SelfName,			//自身姓名
		eGSC_SelfHp,			//自身血条
		eGSC_SelfMp,			//自身蓝条
		eGSC_SelfGuild,			//自身公会
		eGSC_SelfTitle,			//自身称号
		eGSC_SelfTong,			//自身堂名
		eGSC_SelfPetName,		//自身宠物姓名
		eGSC_SelfPetHp,			//自身宠物血条
		eGSC_NpcName,			//NPC姓名
		eGSC_NpcHp,				//NPC血条
		eGSC_NpcTitle,			//NPC公会
		eGSC_MonsterName,		//Monster姓名
		eGSC_MonsterHp,			//Monster血条
		eGSC_ItemName,			//掉落Item名字
		eGSC_TeamPlayerName,	//队友头顶姓名
		eGSC_TeamPlayerHp,		//队友头顶血条
		eGSC_TeamPlayerTitle,	//队友头顶称号
		eGSC_TeamPlayerGuild,	//队友头顶帮会
		eGSC_TeamPlayerTong,	//队友头顶堂名
		eGSC_TeamPlayerPetName,	//队友召唤兽头顶姓名
		eGSC_TeamPlayerPetHp,	//队友召唤兽头顶血条
		eGSC_OtherPlayerName,	//非队友头顶姓名
		eGSC_OtherPlayerHp,		//非队友头顶血条
		eGSC_OtherPlayerTitle,	//非队友头顶称号
		eGSC_OtherPlayerGuild,	//非队友头顶帮会
		eGSC_OtherPlayerTong,	//非队友头顶堂名
		eGSC_OtherPlayerPetName,//非队友召唤兽头顶姓名
		eGSC_OtherPlayerPetHp,	//非队友召唤兽头顶血条
		eGSC_FightFlyText,		//战斗飘字
		eGSC_RefuseStrangerMsg,	//拒绝陌生人短消息
		eGSC_RefuseAllMsg,		//拒绝所有人短消息

		eGSC_MiniMapTeam,		//小地图显示队友
		eGSC_MiniMapNpc,		//小地图显示Npc
		eGSC_MiniMapMonster,	//小地图显示Monster
		eGSC_MiniMapFriend,		//小地图显示好友
		eGSC_MiniMapGuild,		//小地图显示帮派
		eGSC_MiniMapEnemy,		//小地图显示仇人
		eGSC_MiniMapOther,		//小地图显示其他玩家
		eGSC_ChatSelf,			//显示自身聊天泡泡
		eGSC_ChatTeam,			//显示队友聊天泡泡
		eGSC_ChatOther,			//显示其他人聊天泡泡
		eGSC_SOUND,				//声音大小
		eGSC_SOUNDEFFECT,		//环境音效
		eGSC_ChatNpc,           //显示NPC聊天泡泡
        eGSC_ChatMonster,       //显示怪物聊天泡泡
        eGSC_SelfPetTitle,      //自己宠物称号
        eGSC_TeamPetTitle,      //队友宠物称号
        eGSC_OtherPetTitle,     //非队友宠物称号
        eGSC_SelfEffect,        //自身特效
        eGSC_TeamPlayerEffect,  //队友特效
        eGSC_TeamPlayerModel,   //队友人物模型
        eGSC_OtherPlayerEffect, //非队友特效
        eGSC_OtherPlayerModel,  //非队友人物模型
        eGSC_RefuseAddFriendInFight,//战斗中拒绝加好友邀请
        eGSC_RefuseAddTeamInFight,  //战斗中拒绝组队申请
        eGSC_RefuseAddGangInFight,  //战斗中拒绝帮派邀请
        eGSC_RefuseDuelInFight,     //战斗中拒绝比武邀请
        eGSC_RefuseBargainInFight,  //战斗中拒绝交易邀请
        eGSC_RefuseHugInFight,     //战斗中拒绝拥抱邀请
        eGSC_RefuseAddFriend,   //非战斗中拒绝加好友邀请
        eGSC_RefuseAddTeam,     //非战斗中拒绝组队申请
        eGSC_RefuseAddGang,     //非战斗中拒绝帮派邀请
        eGSC_RefuseDuel,        //非战斗中拒绝比武邀请
        eGSC_RefuseBargain,     //非战斗中拒绝交易邀请
        eGSC_RefuseHug,        //非战斗中拒绝拥抱邀请
		eGSC_IntroductionEnable,        //非战斗中拒绝拥抱邀请
		eGSC_ChatListWidth,        //聊天框的宽度
		eGSC_ChatListHeight,        //聊天框的高度

		eGSC_SellPrompt1,
		eGSC_SellPrompt2,
		eGSC_SellPrompt3,
		eGSC_SellPrompt4,
		eGSC_SellPrompt5,
		eGSC_SellPrompt6,

		eGSC_TabMe					,	// 自身
		eGSC_TabMyPet				,	// 我的召唤兽或奴仆
		eGSC_TabTeamPlayer			,	// 队友
		eGSC_TabTeamPlayerPet		,	// 队友的召唤兽或奴仆
		eGSC_TabEnemyGuildPlayer	,	// 敌对帮会玩家
		eGSC_TabEnemyGuildPlayerPet	,	// 敌对帮会玩家的召唤兽或奴仆
		eGSC_TabLeaguePlayer		,	// 同盟玩家
		eGSC_TabLeaguePlayerPet		,	// 同盟玩家的召唤兽或奴仆
		eGSC_TabMyGuildPlayer		,	// 自己帮会玩家
		eGSC_TabMyGuildPlayerPet	,	// 自己帮会玩家的召唤兽或奴仆
		eGSC_TabNormalPlayer		,	// 普通玩家
		eGSC_TabNormalPlayerPet		,	// 普通玩家的召唤兽或奴仆
		eGSC_TabRedNamePlayer		,	// 红名，敌对玩家
		eGSC_TabRedNamePlayerPet	,	// 红名，敌对玩家的召唤兽或奴仆
		eGSC_TabPKPlayer			,	// PK玩家
		eGSC_TabPKPlayerPet			,	// PK玩家的召唤兽或奴仆
		eGSC_TabMonster				,	// 怪物
		eGSC_TabOther				,	// 其他
        eSSC_SKILLLOCK              ,   //技能栏锁定
        eSSC_SKILLLOCK2             ,   //技能栏锁定扩展
        eSSC_CLOSE_AUTO_SELECT      ,   //自动选怪
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

	///显示聊天窗口背景
	void ShowChatBackground( unsigned int uiValue );
	bool IsShowChatBackground() { return m_Settings[eGSC_SHOWCHATBACKGROUND]; }

	/// 声音/音效的存取
	int MakeSoundValue( int nValue, bool bSilence );
	void GetSoundValue( int nFinalValue, int& nValue, bool& bSilence );

protected://protected functions

	///ctor
	GameSetting();

	///remove read-only flag
	void RemoveReadOnlyAttribute( const char* pszFilename );

	///is later change
	bool IsLaterChange( eGameSettingCategory eCategory );

	///实际变换
	void ChangeSetting( eGameSettingCategory eCategory, 
 			unsigned int uiValue );

	///聊天字体大小
	void SetChatFontSize( unsigned int uiValue );

	///自动回复密语
	void SetAutoReplySecret( unsigned int uiValue );

	///智能转身
	void SetAutoTurnAround( unsigned int uiValue );

	///智能鼠标
	void SetAutoMouse( unsigned int uiValue );

	///显示头盔
	void SetShowHelmet( unsigned int uiValue );

	///垂直视角锁定
	void SetVerticleView( unsigned int uiValue );

	///显示NPC名字
	void SetShowNPCName( unsigned int uiValue );

	///显示物品名字
	void SetShowItemName( unsigned int uiValue );

	///显示玩家名字
	void SetShowPlayerName( unsigned int uiValue );

	///显示称号
	void SetShowTitle( unsigned int uiValue );

	///同屏人数
	void SetShowPlayerNumber( unsigned int uiValue );

	///广角
	void SetFOV( unsigned int uiValue );

	///镜头最大距离
	void SetMaxCameraDistance( unsigned int uiValue );
	
	///显示hp,mp
	void ShowHpMp( unsigned int uiValue );

	///显示fp
	void ShowFp( unsigned int uiValue );

	///45锁定
	void Set45Camera( unsigned int uiValue );

	///相机跟踪
	void SetFollowCamera( unsigned int uiValue );

	///显示HP
	void ShowHPBar( unsigned int uiValue );

	///显示MP
	void ShowMPBar( unsigned int uiValue );

	///显示FP
	void ShowFPBar( unsigned int uiValue );

	///鼠标灵敏度
	void SetMouseSpeed( unsigned int uiValue );

	///摄像机旋转速度FP
	void SetCameraRotateSpeed( unsigned int uiValue );

	//声音大小
	void SetSound( unsigned int uiValue );

	//环境音效
	void SetSoundEffect( unsigned int uiValue );

	///bool值的设置
	void SetBool( eGameSettingCategory eCategory, bool bValue );

protected://protected static members
	static GameSetting* ms_pThis;

protected://protected members
	unsigned int m_Settings[eGSC_TOTAL];
	std::string m_SettingNames[eGSC_TOTAL];	
	bool m_bDirty[eGSC_TOTAL];
};
