#ifndef AN_CONFIG_COLOR_H_
#define AN_CONFIG_COLOR_H_

#include <Windows.h>
#include <map>

enum ColorConfigure
{
	CC_CONFIG_INVALID = -1,

	CC_CHAT_NORMAL	= 0,	//普通聊天颜色
	CC_CHAT_PERSONAL,		//私聊颜色
	CC_CHAT_GUILD,			//公会聊天颜色
	CC_CHAT_TEAM,			//队伍聊天颜色
	CC_CHAT_SYSTEM,			//系统聊天颜色
	CC_CHAT_BULL,			//全服公告聊天颜色
	CC_CHAT_LEAGUE,			//同盟聊天颜色	
	CC_CHAT_HIGHSHOUT,		//全服公告(用于玩家)颜色
	CC_CHAT_FAMILY,			//家族聊天

	CC_TASK_MORE6,		//任务等级大于玩家6颜色
	CC_TASK_MORE3,			//任务等级大于玩家3颜色
	CC_TASK_LESS3ANDMORE3 = 10,	//任务和玩家 -3~~3颜色
	CC_TASK_LESS3,			//任务等级小于玩家3	颜色
	CC_TASK_LESS6,			//任务等级小于玩家6颜色
    CC_TASK_NAME,           //任务追踪中任务名称颜色
    CC_TASK_DONE,           //任务追踪中已完成的任务目标颜色
    CC_TASK_NONE,           //任务追踪中未完成的任务目标颜色
	//代码里的player(包括player、item、npc、monster等等)
	CC_ENTITY_PLAYER,			//玩家 包括自己颜色
	CC_ENTITY_NPC,				//npc颜色
	CC_ENTITY_ITEMLESS2,			//掉落到地上的物品 品质小于2级颜色
	CC_ENTITY_MONSTER_INITIATIVE,	//主动怪物颜色
	CC_ENTITY_MONSTER_PASSIVITY = 20,	//被动怪物颜色
	CC_ENTITY_MONSTER_PROFESSION,	//采集物品(代码里属于怪物)颜色

    CC_GUILD_MASTER,                //公会会长颜色
    CC_GUILD_VICEMASTER,            //公会副会长颜色
    CC_GUILD_MEMBER,                //公会会员颜色
    CC_GUILD_OFFLINE,               //公会离线会员颜色

    CC_FRIEND_ONLINE,               //好友在线颜色
    CC_FRIEND_OFFLINE,               //好友离线颜色

    CC_CHARACTER_DEL,               //选人界面被删除的角色颜色

	CC_MINIMAP_TIP,					//小地图tip字体颜色
	CC_CHAT_HYBER_DOWNLINE = 30,	//聊天框电击名字画下划线颜色

	CC_NPCLIST_MAPNAME = 31,		//大地图地名显示名字颜色
	
	CC_NPCLIST_NPCTYPE_1,			//npc列表颜色显示 类型 普通 
	CC_NPCLIST_NPCTYPE_2,			//npc列表颜色显示 类型 药品、武器、首饰、防具、特殊兑换商人
	CC_NPCLIST_NPCTYPE_3,			//npc列表颜色显示 类型 材料买卖商、坐骑商人
	CC_NPCLIST_NPCTYPE_4,			//npc列表颜色显示 类型 传送点
	CC_NPCLIST_NPCTYPE_5,			//npc列表颜色显示 类型 仓库、寄售商人
	CC_NPCLIST_NPCTYPE_6,			//npc列表颜色显示 类型 合成、升星
	CC_NPCLIST_NPCTYPE_7 = 38,		//npc列表颜色显示 活动、官府任务

	CC_ITME_SHOW		=	 39,	//物品介绍
	CC_ITME_TYPE		=	 40,	//物品类型
	CC_ITME_PRONEED		=	 41,	//职业需求
	CC_ITEM_LVLNEED		=	 42,	//需要级别
	CC_ITEM_WEAR		=	 43,	//耐久
	
    CC_NAME_Pet      =    44,    //召唤兽颜色
    CC_NAME_POLICE      =    45,                 //蓝名玩家颜色
    CC_NAME_KILL_1      =    46,                 //红名玩家颜色 等级1
    CC_NAME_KILL_2      =    47,                 //红名玩家颜色 等级2
    CC_NAME_KILL_3      =    48,                 //红名玩家颜色 等级3
    CC_NAME_KILL_4      =    49,                 //红名玩家颜色 等级4
    CC_NAME_KILL_5      =    50,                 //红名玩家颜色 等级5
    CC_NAME_ATTACKER    =    51,                 //灰名玩家颜色
    CC_NAME_GUILD       =    52,                 //玩家公会名字颜色

	CC_CUSTOM_SHORTCUTKEY	= 53,	//玩家自定义快捷键list描述颜色
	CC_CUSTOM_KEYFCOUT		= 54,	//玩家自定义快捷键list按下等待输入颜色
	CC_ITEM_EQUIPTYPE		= 55,	//EquipType

	CC_TASK_INFO			= 56,	//任务信息字体颜色
	CC_TASK_STATE			= 57,	//任务提示字体颜色
	CC_NPCDIALOG_INFO		= 58,	//npc对话问题字体颜色 selectBox.cpp.m_pID_TEXT_Info
	CC_NPCSELECKBOX_INFO	= 59,	//npc选择对话字体颜色 NpcChatDialogBox.cpp.m_pID_TEXT_Info
	CC_MESSGEBOX_TEXT		= 60,	//messagebox 字体颜色

	CC_LISTSELECTON			= 61,	//list选中item时候的颜色


	CC_CORPS_Robber			= 62,	//职业
	CC_CORPS_Warrior		= 63,	//职业
	CC_CORPS_Archer			= 64,	//职业
	CC_CORPS_Taoist			= 65,	//职业
	CC_CORPS_Wizard			= 66,	//职业

	CC_TEXT_ExpAllot		= 67,	//经验捐献界面Text颜色
	CC_SHOP_Desc			= 68,		//商店注释
	CC_SHOP_Storage			= 69,		//商店仓库

	CC_SHOP_Price			= 70,		//商店普通价格
	CC_SHOP_MemberPrice		= 71,		//商店VIP价格
	CC_SHOP_Price2			= 72,		//商店普通价格(游戏币购买)
	CC_SHOP_MemberPrice2	= 73,		//商店VIP价格(游戏币购买)

	CC_SHOP_ItemName		= 74,		//商店物品名
	
	CC_SHOP_Agio			= 75,		//商店Agio
	CC_LoginUI_TextInfo		= 76,		//loginUI test文字颜色
	CC_SkillTip_target		= 77,		//作用对象
	CC_ItemTip_suitNoneAll	= 78,		//skill_ tip 套装没有齐全
	CC_ItemTip_suitALL		= 79,		//skill_ tip 套装齐全 
	
	CC_CreateUI_StrNote     = 80,
	CC_CreateUI_Property     = 81,
	CC_CreateUI_ProName    = 82,


	CC_ServerInfoColor_0	=	83,
	CC_ServerInfoColor_1	=	84,
	CC_ServerInfoColor_2	=	85,
	CC_ServerInfoColor_3	=	86,
	CC_ServerInfoColor_4	=	87,
	CC_ServerInfoColor_5	=	88,
	CC_ServerInfoColor_6	=	89,
	CC_ServerInfoColor_7	=	90,
	CC_ServerInfoColor_8	=	91,
	CC_ServerInfoColor_9	=	92,
	CC_ServerInfoColor_10	=	93,

	CC_Client_Eventtime_description	= 94,	//event_time_description
	CC_Client_Eventtime_hortation	= 95,	//event_time_hortation
	CC_Client_Eventtime_timeinfo	= 96,	//event_time_timeinfo
	CC_Client_Eventtime_more		= 97,	//event_time_more

	CC_CompoundInfo_Icon_Enable		= 98,	//客户端合成表 icon 可用的名字颜色
	CC_CompoundInfo_Icon_Disable	= 99,	//客户端合成表 icon 不可用的名字颜色

	CC_Intensify_Text_Color_1 = 100,   //强化文字显示颜色
	CC_Intensify_Text_Color_2 = 101,
	CC_Intensify_Text_Color_3 = 102,
	CC_Intensify_Text_Color_4 = 103,

    CC_GUILD_CITYMASTER = 104,

	CC_PlayerNormal = 105,	// 正常玩家字体颜色
	CC_PlayerEnemy = 106,	// 敌对玩家字体颜色
	CC_PlayerLeague = 107,	// 同盟玩家字体颜色
	CC_PlayerTile = 108,	// 玩家称号字体颜色
	CC_Guild = 109,			// 公会字体颜色
    CC_NPCTile = 110,		// NPC称号字体颜色
	CC_NPC = 111,			// NPC字体颜色
	

	CC_MonsterNormal = 112,	// 被动怪字体颜色
	CC_MonsterLevelRange5,	// 主动怪等级 - 玩家等级 = -5 ~ 5
	CC_MonsterLevelLow5,	// 主动怪等级 - 玩家等级 = < -5
	CC_MonsterLevelUp5,		// 主动怪等级 - 玩家等级 = > 5

	CC_ItemLevel1,          // 等级为1的道具字体颜色
	CC_ItemLevel2,          // 等级为2的道具字体颜色
	CC_ItemLevel3,          // 等级为3的道具字体颜色
	CC_ItemLevel4,          // 等级为4的道具字体颜色
	CC_ItemLevel5,          // 等级为5的道具字体颜色
	CC_ItemLevel6,          // 等级为6的道具字体颜色
	CC_PathFindLinker,          // 寻路链接的颜色

	CC_ZoneNameTip,          // zone名字颜色
	CC_TileNameTip,          // 区域tile名字颜色

	CC_TaskRank0,			// 品质为0的任务
	CC_TaskRank1,            // 品质为1的任务永远显示此颜色
	CC_TaskRank2,            // 品质为2的任务永远显示此颜色
	CC_TaskRank3,            // 品质为3的任务永远显示此颜色
	CC_TaskRank4,            // 品质为4的任务永远显示此颜色
	CC_HighLightNpcName,          // 高亮npc的颜色

	CC_MessageSelfName,          // 短消息中自己名称的颜色
	CC_MessageOtherName,          // 短消息中对方名称的颜色
	CC_MessageSelfWord,          // 短消息中自己聊天内容的颜色
	CC_MessageOtherWord,          // 短消息中对方聊天内容的颜色

	CC_PlayerTip_NameP1 = 150,		//Tips内容里玩家名字的霸王的颜色
	CC_PlayerTip_NameP2,		//Tips内容里玩家名字的奇门的颜色
	CC_PlayerTip_NameP3,		//Tips内容里玩家名字的红颜的颜色
	CC_PlayerTip_NameP4,		//Tips内容里玩家名字的剑侠的颜色
	CC_PlayerTip_NameP5,		//Tips内容里玩家名字的飞羽的颜色
	CC_PlayerTip_Gang = 158,			//Tips内容里玩家公会名的颜色
	CC_PlayerTip_Level,			//Tips内容里玩家等级的颜色
	CC_PlayerTip_Profession,			//Tips内容里玩家职业的颜色
	CC_PlayerTip_PkMode,			//Tips内容里玩家PK模式的颜色

	CC_MonsterTip_Name = 163,			//Tips内容里怪物名的颜色
	CC_MonsterTip_Title,			//Tips内容里怪物称号的颜色
	CC_MonsterTip_Level,			//Tips内容里怪物等级的颜色
	CC_MonsterTip_Strong,			//Tips内容里怪物强度的颜色
	CC_MonsterTip_SkillOK = 168,			//Tips内容里需求技能等级满足的颜色
	CC_MonsterTip_SkillFail,			//Tips内容里需求技能等级不满足的颜色

	CC_NpcTip_Name = 170,			//Tips内容里NPC名字的颜色
	CC_NpcTip_Title,			//Tips内容里NPC称号的颜色
	CC_NpcTip_Level,			//Tips内容里NPC等级的颜色

	CC_ElevenBlueName = 189,		//11级蓝名
	CC_TenBlueName ,		//10级蓝名
	CC_NineBlueName,
	CC_EightBlueName,
	CC_SevenBlueName,
	CC_SixBlueName,
	CC_FiveBlueName,
	CC_FourBlueName,
	CC_ThreeBlueName,
	CC_TwoBlueName,
	CC_OneBlueName,
	CC_WhiteName,				//白名
	CC_OrangeName,				//橙色名字
	CC_OneRedName,
	CC_TwoRedName,
	CC_ThreeRedName,
	CC_FourRedName,
	CC_FiveRedName,
	CC_SixRedName,
	CC_SevenRedName,
	CC_EightRedName,
	CC_NineRedName,
	CC_TenRedName,
 	CC_ElevenRedName,
	CC_Exp,
	CC_Exploit,
	CC_Reputation,
	CC_SkillLevelUp,
	CC_Pick,
	CC_SystemPromp,
	CC_Center_MapInfo,
	CC_Center_ImmediateInfo,
	CC_Center_WarningErrorInfo,
	CC_Center_OtherInfo,
	CC_CHAT_PLAYERNAME, // 聊天窗口中玩家名字颜色
	CC_CHAT_VIP_PLAYERNAME,	// 聊天窗口中VIP玩家名字颜色
	CC_PRIVATE_SHOP_MONEY,	// 摆摊交易记录里获得金钱
    CC_MAILTIP,          //邮件Tip
    CC_CampBattleSame,    //同阵营
    CC_CampBattleNoSame,  //不同阵营
    CC_CampBattleSameInList,  //在同阵营中成员列表中显示
	CC_CHAT_ZHENYING,	// 阵营频道
	CC_CHAT_COUNTRY,	// 国家频道
	CC_CHAT_XIAOLABA,	// 小喇叭频道
	CC_Gem_Attribute,	// 宝石属性文字颜色
	CC_ContryTitle,		// 官职称号，用于头顶
	CC_PetTitle,		// 宠物称号（xx的宠物）

    CC_BESTEQUIP_GETMODE,	// 装备获取方式
    CC_BESTEQUIP_INFO,		// 装备获取方式说明
    CC_BESTEQUIP_OTHERINFO,	// 装备获取方式其它说明
    CC_BESTEQUIP_TIP,		// 装备获取提示

    CC_Player_OtherCountry          = 240,      // 头顶文字颜色
    CC_Pet_OtherCountry             = 241,
    CC_PetTitle_OtherCountry        = 242,
    CC_NPC_OtherCountry             = 243,
    CC_NPC_NoCountry                = 244,

    CC_ActivityDay_LevelReach       = 245,      // 今日指引等级达到颜色
    CC_ActivityDay_LevelNotReach    = 246,      // 未达到

    // 物品、技能、状态 Tip 颜色配置        added by zhuomeng.hu		[12/3/2010]
    /***************************************************************/
    CC_ItemTip_Name_Quality0        = 250,      // 品质
    CC_ItemTip_Name_Quality1,
    CC_ItemTip_Name_Quality2,
    CC_ItemTip_Name_Quality3,
    CC_ItemTip_Name_Quality4,
    CC_ItemTip_Name_Quality5,
	CC_ItemTip_Name_Quality6,
	CC_ItemTip_Name_Quality7,

    CC_ItemTip_SkillName            = 260,      // 物品名
    CC_ItemTip_ItemType             = 261,      // 物品类型

    CC_ItemTip_ItemBind             = 262,      // 物品已绑定

    CC_ItemTip_Endure_Nonzero       = 263,      // 耐久非0
    CC_ItemTip_Endure_Zero          = 264,      // 耐久为0

    CC_ItemTip_Lock                 = 265,      // 加锁
    CC_ItemTip_Unlock               = 266,      // 解锁

    CC_ItemTip_Require_Reach        = 267,      // 着装需求达到
    CC_ItemTip_Require_NotReach     = 268,      // 着装需求未达到

    CC_ItemTip_BaseAttr             = 269,      // 装备基本属性
    CC_ItemTip_RandAttr             = 270,      // 装备附加随机属性
    CC_ItemTip_PurpleAttr           = 271,      // 装备鎏金属性
    CC_ItemTip_GemAttr              = 272,      // 装备宝石镶嵌属性

    CC_ItemTip_SuitPart_Have        = 273,      // 有套装部件
    CC_ItemTip_SuitPart_NotHave     = 274,      // 无套装部件
    CC_ItemTip_SuitAttr_Have        = 275,      // 有套装属性
    CC_ItemTip_SuitAttr_NotHave     = 276,      // 无套装属性

    CC_ItemTip_EquipDes_Default     = 277,      // 装备描述默认颜色

    CC_ItemTip_Identify             = 278,      // 装备评估的鉴定，现在已经没了

    CC_ItemTip_SellPrice            = 279,      // 物品售价
    CC_ItemTip_FixPrice             = 280,      // 修理价格

    CC_ItemTip_Item_Introduction    = 281,      // 物品、技能介绍

    CC_ItemTip_RestoreTime          = 282,      // 消耗品使用次数

    CC_ItemTip_Gem                  = 283,      // 宝石的属性

    CC_ItemTip_Skill_NextLevel      = 284,      // 技能描述“下一级”
    CC_ItemTip_Skill_MaxLevel       = 285,      // 技能描述“已达到最大等级”
    CC_ItemTip_Skill_NotLearn       = 286,      // 技能描述“未学习”
    CC_ItemTip_Skill_Level          = 287,      // 技能描述“等级”
    CC_ItemTip_Skill_LearnNotReach  = 288,      // 学习技能需求未达到

    CC_ItemTip_EventItem_Des        = 289,      // 事件(任务?)道具描述
    
    CC_ItemTip_Item_LeftTime        = 290,      // 物品剩余时间

    CC_ItemTip_Other                = 291,      // 武神残留颜色

    CC_ItemTip_NowEquip             = 292,      // 当前装备

	CC_Achievement_OK				= 293,      // 成就完成
	CC_Achievement_Gray             = 294,      // 成就未完成

	CC_MapName                      = 320,      // 地图名称
    /***************************************************************/
	CC_PetColor_Taupe           = 321,//暗灰色
	CC_PetColor_Red				   = 322,//红色
	CC_PetColor_Blue			   = 323,//蓝色
	CC_PetColor_Green			   = 324,//绿色
	CC_PetColor_White			   = 325,//白色
	CC_NearPlayerNoTeam            = 326, //附近玩家无队伍
	CC_NearPlayerTeam              = 327, //附近玩家有队伍 
	CC_ZhuJiang_Name			   = 328, //主将的名字颜色
	CC_Activity_Default			   = 329, //活动默认颜色
	CC_Activity_Start			   = 330, //活动进行中
	CC_Activity_Close			   = 331, //活动关闭
	CC_Activity_Finish			   = 332, //活动完成
	CC_Activity_Ready			   = 333, //活动预备
	CC_Activity_NoStart			   = 334, //活动未开始
	CC_ZhuJiang_Attr			   = 335, //主将属性
    CC_Chat_ChatGuanYuan           = 336, //官员频道聊天颜色
	CC_TeamPlayer				   = 337, //组队队友名字颜色
	CC_CONFIG_MAX
};
class CColor_Configure
{
public:
	CColor_Configure();
	virtual ~CColor_Configure();

public:
	void	load();
	DWORD	ARGBtoDWORD(int a, int r, int g, int b);

	DWORD	getColor(ColorConfigure type);

	DWORD	GetPkNameColor( int nPkType );
private:
	DWORD	mAllColor[CC_CONFIG_MAX];
};

extern CColor_Configure Color_Config;

#endif

