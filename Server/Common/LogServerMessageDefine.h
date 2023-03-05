#ifndef __LogServerMessageDefine_H__
#define __LogServerMessageDefine_H__

#pragma once

#include "MsgBase.h"

#pragma pack( push, 1 )

enum ELogMessageDefine
{
	LOGMSG_BEGIN_TEST         = 1,//开始的协议类型.也作为测试协议使用
	LOGMSG_SynServerid,			//同步serverid
	LOGMSG_OnlineInfo,			//在线信息
	LOGMSG_INOUNTINFO,			//player上下线log
	LOGMSG_ITEMGAIN,			//获得物品log
	LOGMSG_ITEMTRADE,			//物品交易(流通)log
	LOGMSG_ITEMCONSUME,			//消耗物品
	LOGMSG_ITEMUPGRADE,			//升级物品操作

	LOGMSG_QUESTLOG,			//任务日志
	LOGMSG_CURRENCY,			//货币流通日志
	LOGMSG_EXPLOG,				//经验改变log
	LOGMSG_LEVCHANGE,			//等级改变

	LOGMSG_MAILLOG,				//邮件日志

	LOGMSG_GUILDLOG,			//工会日志
	LOGMSG_GUILDDETAIL,			//工会属性日志

	LOGMSG_GMCOMMAND,			//在线GM命令
	LOGMSG_CHATINFO,            //聊天

	LOGMSG_max
};

struct TestLogMessage:public Msg
{
	TestLogMessage()
	{
		header.dwType = LOGMSG_BEGIN_TEST;
		header.stLength = sizeof(TestLogMessage);
		memset(frondose,0,sizeof(char)*128);
	}
	uint32     account_id;
	uint32	   character_id;
	SYSTEMTIME _time;
	char	   frondose[128];
};

struct S2LSynServerid:public Msg
{
	S2LSynServerid()
	{
		header.dwType = LOGMSG_SynServerid;
		header.stLength = sizeof(S2LSynServerid);
		serverid = -1;
	}
	int serverid;
};

struct CS2LOnlineInfo:public Msg
{
	CS2LOnlineInfo()
	{
		header.dwType = LOGMSG_OnlineInfo;
		header.stLength = sizeof(CS2LOnlineInfo);
		memset(frondose,0,sizeof(char)*512);
	}
	uint16 login;
	uint16 normalquit;
	uint16 kickquit;
	uint16 total;
	char   frondose[512];
	SYSTEMTIME _time;
};

struct LogPlayerInfo
{

	LogPlayerInfo()
	{
         memset(chName,0,sizeof(chName));
	}
	uint32     account_id;
	uint32	   character_id;
	char	   chName[20];
	SYSTEMTIME _time;
};

struct LogItemInfo
{

	LogItemInfo()
	{
       memset(ItemName,0,sizeof(ItemName));
	}

	uint16			item_id;
	__int64			item_guid;
	uint16			item_count;
	
	char	        ItemName[20];
};

enum ePlayerLogInfo
{
	ePlayerLogInfo_login = 1,	//角色进入游戏 V
	ePlayerLogInfo_logout = 0,  //角色离开游戏 V

	ePlayerExp_Kill		= 0,	//杀怪获得经验 VV
	ePlayerExp_Script	= 1,	//脚本或者完成任务 VVV
	ePlayerExp_TransSkill = 2,	//学习技能消耗经验 V
	
	ePlayerCurrency_Add = 0,	//增加金钱 V
	ePlayerCurrency_Sub = 1,	//减少金钱 V

	ePlayerMoneyType_BMoney = 0,	//绑银 V
	ePlayerMoneyType_Money = 1,		//银币 V
	ePlayerMoneyType_BGold = 2,		//绑金 V
	ePlayerMoneyType_Gold = 3,		//元宝  V

	ePlayerMoneyType_Jifen= 4,		//商城积分
	ePlayerMoneyType_Rongyu = 5,	//荣誉
    ePlayerMoneyType_ShengWang = 6,  //声望
    ePlayerMoneyType_GongXun = 7,   //功勋

	ePlayerMoneySourceType_Unkown					= -1, // 位置
	ePlayerMoneySourceType_Bargain					= 0, // 交易
	ePlayerMoneySourceType_ReliveTypeOrigin			= 1,//原地复活
	ePlayerMoneySourceType_ReliveTypeOriginFullHpMP = 2,//完美复活
	ePlayerMoneySourceType_UseReelItemToPet			= 3,//使用物品宠物学习技能
	ePlayerMoneySourceType_KillMonsterSpecialReward = 4,//杀死怪物的特殊奖励
	ePlayerMoneySourceType_ChangeCountry			= 5,//改变国家
	ePlayerMoneySourceType_GMAddmoney				= 6,//GM AddMoney命令
	ePlayerMoneySourceType_NPCShop					= 7,//系统商店
	ePlayerMoneySourceType_Storage					= 8,//仓库
	ePlayerMoneySourceType_BuyBack					= 9,//回购
	ePlayerMoneySourceType_PetSavvyUp				= 10,//提升宠物悟性
	ePlayerMoneySourceType_PetBreedConfirm			= 11,//宠物繁殖
	ePlayerMoneySourceType_PetBreedAcquire			= 12,//领取繁殖宠物
	ePlayerMoneySourceType_BianShen					= 13,//主将变身
	ePlayerMoneySourceType_DoneQuest				= 14,//完成任务
	ePlayerMoneySourceType_Consignment				= 15,//寄售
	ePlayerMoneySourceType_CountryRaise				= 16,//国家募捐
	ePlayerMoneySourceType_ItemReclaim				= 17,//装备回收
	ePlayerMoneySourceType_CreateFamily				= 18,//创建家族
	ePlayerMoneySourceType_FamilyDonate				= 19,//家族捐赠
	ePlayerMoneySourceType_GuildDelate				= 20,//工会弹劾
	ePlayerMoneySourceType_CreateGuild				= 21,//创建工会
	ePlayerMoneySourceType_ChangeGuildAim			= 22,//改变工会宣言
	ePlayerMoneySourceType_Luck						= 23,//幸运闯关
	ePlayerMoneySourceType_SendMail					= 24,//邮资
	ePlayerMoneySourceType_MailCache				= 25,//邮件附带
	ePlayerMoneySourceType_Scprit					= 26,//脚本设置
	ePlayerMoneySourceType_StallRevenue				= 27,//摆摊占地税
	ePlayerMoneySourceType_StallSetmeal				= 28,//摆摊套餐
	ePlayerMoneySourceType_Stall					= 29,//个人商店
	ePlayerMoneySourceType_BuffAdd					= 30,//状态额外增加
	ePlayerMoneySourceType_OfflineHookExp			= 31,//下线挂机获得经验
	ePlayerMoneySourceType_UpSkill					= 32,//升级技能心法
	ePlayerMoneySourceType_MoveStarLevelUp			= 33,//升级转星石
	ePlayerMoneySourceType_SuitElementCheck			= 34,//套装鉴定
	ePlayerMoneySourceType_RepairItem				= 35,//修理
	ePlayerMoneySourceType_MountStreng				= 36,//坐骑强化
	ePlayerMoneySourceType_LearnSkill				= 37,//学习技能心法
	ePlayerMoneySourceType_ItemCompose				= 38,//合成物品
	ePlayerMoneySourceType_ComposeGem				= 39,//合成宝石
	ePlayerMoneySourceType_ComposeZhujiang			= 40,//主将合成
	ePlayerMoneySourceType_Intensify				= 41,//升星强化
	ePlayerMoneySourceType_Identify					= 42,//鉴定坐骑繁衍
	ePlayerMoneySourceType_MountBreed				= 43,//坐骑繁衍
	ePlayerMoneySourceType_RestoreMountHP			= 44,//回复坐骑生命
	ePlayerMoneySourceType_SuitElementMove			= 45,//套装属性传承
	ePlayerMoneySourceType_ElementSuitChange		= 46,//套装随即转换属性
	ePlayerMoneySourceType_SkillSuitChange			= 47,//套装技能改变 
	ePlayerMoneySourceType_ElementSuitLevelUp		= 48,//套装属性升级
	ePlayerMoneySourceType_SkillSuitLevelUp			= 49,//套装技能升级 
	ePlayerMoneySourceType_EquipAmuletAbsorb		= 50,//升级护身符
	ePlayerMoneySourceType_EquipCharmAbsorb			= 51,//升级符文 
	ePlayerMoneySourceType_EquipMaintainCross		= 52,//装备保值
	ePlayerMoneySourceType_TransferStar				= 53,//转星
	ePlayerMoneySourceType_RandAttribute			= 54,//装备属性随机 
	ePlayerMoneySourceType_EquipUpgrade				= 55,//装备升级阶
	ePlayerMoneySourceType_SoulStamp				= 56,//灵魂铭刻物品
	ePlayerMoneySourceType_GemReplace				= 57,//替换宝石
	ePlayerMoneySourceType_GemTakeDown				= 58,//拆卸宝石
	ePlayerMoneySourceType_Hole						= 59,//打孔
	ePlayerMoneySourceType_EquipReOpenLight			= 60,//重开光
	ePlayerMoneySourceType_EquipOpenLight			= 61,//开光
	ePlayerMoneySourceType_EquipIdentify			= 62,//鉴定
	ePlayerMoneySourceType_ShopCenter				= 63,//商城
	ePlayerMoneySourceType_ResetItemTime			= 64,//充值限时装备延期
	ePlayerMoneySourceType_DBMsgSetBillingMoney		= 65,//DB SERVER同步
	ePlayerMoneySourceType_Cache					= 66,//充值
	ePlayerMoneySourceType_KillPerson				= 67,//杀人获得
	ePlayerMoneySourceType_QuestEntrust				= 68,//任务委托
};

enum eItemLogInfo
{
	//获得物品
	//eItemLogInfo_GainItem_Pick			= 0,  //拾取获得物品
	//eItemLogInfo_GainItem_Script		= 1,  //脚本获得物品
	//eItemLogInfo_GainItem_Shop			= 2,  //普通商店获得物品
	//eItemLogInfo_GainItem_ShopCenter	= 3,  //商城获得物品
	//eItemLogInfo_GainItem_Bargain		= 4,  //交易获得物品
	//eItemLogInfo_GainItem_Mail			= 5,  //邮件获得物品

	//EIGS_UnKnow        =  0  ,    // 未知 V
	//EIGS_OnlineReward   ,    // 在线奖励 V
	//EIGS_Quest          ,    // 任务道具 V
	//EIGS_Achieve        ,    // 成就奖励 V
	//EIGS_DropItem       ,    // 打怪掉落 V
	//EIGS_TreasureBox    ,    // 开宝箱 
	//EIGS_JiFengShop     ,    // 积分商店
	//EIGS_NpcShop        ,    // NPC商店 V
	//EIGS_Bargaining     ,    // 交易 V
	//EIGS_Stall          ,    // 摆摊 V
	//EIGS_Script         ,    // 脚本获得 V
	//EIGS_Upgrade        ,    // 装备升阶 
	//EIGS_Compose        ,    // 合成 V 
	//EIGS_GemTakeDown    ,    // 宝石拆卸 V
	//EIGS_FromPlat       ,    // 通过平台获得
	//EIGS_GemInlayFail   ,    // 镶嵌失败降级
	//EIGS_UnknowIdentify ,    // 装备未知鉴定 V


	//交易物品
	eItemTrade_PrivateShop				= 0,	//摆摊 V
	eItemTrade_Bargain					= 1,	//交易 V

	//销毁物品(失去物品)
	eItemLogInfo_ItemConsume_Use		= 0,   //使用物品 V
	eItemLogInfo_ItemConsume_SellNpc	= 1,   //卖给NPC V
	eItemLogInfo_ItemConsume_Destroy	= 2,   //摧毁 V
	eItemLogInfo_ItemConsume_Decompose	= 3,   //分解 V
	eItemLogInfo_ItemConsume_Script		= 4,   //脚本
	eItemLogInfo_ItemConsume_Bargain	= 5,   //交易 V
	eItemLogInfo_ItemConsume_Mail		= 6,   //邮件 V
	eItemLogInfo_ItemConsume_DeadDrop		= 7,   //死亡掉落
	eItemLogInfo_ItemConsume_UnBind		= 8,   //解绑失去 V
	eItemLogInfo_ItemConsume_UseLuck		= 9,   //摇奖
	eItemLogInfo_ItemConsume_UpItem		= 10,   //打造 V
	eItemLogInfo_ItemConsume_OnLineReward   = 11,   //在线奖励领取失败
	eItemLogInfo_ItemConsume_ChangeCountry = 12,  //叛国。 V
	eItemLogInfo_ItemConsume_CountryPosition = 13, //国家职位改变
	


	//升级物品
	eItemLogInfo_ItemUpgrade_Intensify	= 0,   //升星 V
	eItemLogInfo_ItemUpgrade_MountIntensify	= 1,   //坐骑升星 V
	eItemLogInfo_ItemUpgrade_TradeStar	= 2,   //转星 V
	eItemLogInfo_ItemUpgrade_Hole		= 3,   //打孔 V
	eItemLogInfo_ItemUpgrade_InsertHole	= 4,   //镶嵌 V
	eItemLogInfo_ItemUpgrade_OutGem		= 5,   //拔宝石 V
	eItemLogInfo_ItemUpgrade_Random		= 6,   //洗随机 V
	eItemLogInfo_ItemUpgrade_OpenLight	= 7,   //鎏金
	eItemLogInfo_ItemUpgrade_ReOpenLight= 8,   //回炉
	eItemLogInfo_ItemUpgrade_SoulStamp  = 9,   //铸魂
};

enum eSystemLogInfo
{
	eSystemLogInfo_guild_create = 0, // 创建军团 V
	eSystemLogInfo_guild_disband = 1, //自动解散 V
	eSystemLogInfo_guild_LevelUp = 2, // 升级 V
	eSystemLogInfo_guild_SignUpKingWar = 3, // 报名国王战 V
	eSystemLogInfo_guild_sysdisband = 4,  //系统解散 

};

struct GS2LPlayerInOutLog:public Msg
{
	GS2LPlayerInOutLog()
	{
		header.dwType = LOGMSG_INOUNTINFO;
		header.stLength = sizeof(GS2LPlayerInOutLog);
		memset(IpAddr,0,sizeof(IpAddr));
		memset(scMac,0,sizeof(scMac));
	}
	LogPlayerInfo   logcommon;
	char			IpAddr[20];
	char			scMac[20];//MAC_LENGTH
	int16			Logtype;
	uint32			onlinetime;
	uint16			lv;
	uint16			country;
	
};

struct GS2LItemGain:public Msg
{
	GS2LItemGain()
	{
		header.dwType = LOGMSG_ITEMGAIN;
		header.stLength = sizeof(GS2LItemGain);
	}
	LogPlayerInfo    logcommon;
	LogItemInfo		 logitem;
	int16			 logtype;
};

struct GS2LItemTrade:public Msg
{
	GS2LItemTrade()
	{
		header.stLength = sizeof(GS2LItemTrade);
		header.dwType =LOGMSG_ITEMTRADE; 
		memset(buyerName,0,sizeof(buyerName));
		memset(sellerName,0,sizeof(sellerName));
	}
	SYSTEMTIME _time;
	uint32		buyer_accid;
	uint32		buyer_chaid;
	char        buyerName[20];
	uint32		seller_accid;
	uint32		seller_chaid;
	char        sellerName[20];
	LogItemInfo	logitem;
	uint32		item_cost;
	int16		logtype;
};


struct GS2LItemConsume:public Msg
{
	GS2LItemConsume()
	{
		header.dwType = LOGMSG_ITEMCONSUME;
		header.stLength = sizeof(GS2LItemConsume);
	}
	LogPlayerInfo	logcommon;
	LogItemInfo		logitem;
	int16			logtype;
	uint16			item_LaveCount;
};

struct GS2LItemUpgrade:public Msg
{
	GS2LItemUpgrade()
	{
		header.dwType = LOGMSG_ITEMUPGRADE;
		header.stLength = sizeof(GS2LItemUpgrade);

		memset(previous,0,sizeof(uint16)*7);
		memset(current,0,sizeof(uint16)*7);
	}
	LogPlayerInfo	logcommon;
	LogItemInfo		logitem;
	uint16			previous[7];
	uint16			current[7];
	int16			result;
	int16			logtype;
};

struct GS2LQuestLog:public Msg
{
	GS2LQuestLog()
	{
		header.stLength = sizeof(GS2LQuestLog);
		header.dwType = LOGMSG_QUESTLOG;
	}
	LogPlayerInfo logcommon;
	uint32		  questid;
};

struct GS2LCurrencyLog:public Msg
{
	GS2LCurrencyLog()
	{
		header.dwType = LOGMSG_CURRENCY;
		header.stLength = sizeof(GS2LCurrencyLog);
	}
	LogPlayerInfo logcommon;
	int16		  money_type;
	int32		  count;
	int16		  logtype;
	int16		  sourcetype;
};

struct GS2LExpLog:public Msg
{
	GS2LExpLog()
	{
		header.dwType = LOGMSG_EXPLOG;
		header.stLength = sizeof(GS2LExpLog);
	}
	LogPlayerInfo logcommon;
	int32		  _exp;
	int16		  logtype;
	int32		  monsterid;
};

struct GS2LLevelChange:public Msg
{
	GS2LLevelChange()
	{
		header.dwType = LOGMSG_LEVCHANGE;
		header.stLength =sizeof(GS2LLevelChange);
	}
	LogPlayerInfo logcommon;
	uint16		  previouslev;
	uint16		  newlev;
};

struct S2LMailLog:public Msg
{
	S2LMailLog()
	{
		header.dwType = LOGMSG_MAILLOG;
		header.stLength = sizeof(S2LMailLog);
	}
	SYSTEMTIME	_time;
	uint32		send_accid;
	uint32		send_chid;
	uint32		recv_chid;
	char		mail_title[32];
	char		mail_detail[100];
	char        send_CharName[20];
	char        recv_CharName[20];
	char        ItemName[20];
	uint16		item_id;
	uint16		item_count;
	uint32		money;
	__int64      item_Guid;
};

struct S2LGuildLog:public Msg
{
	S2LGuildLog()
	{
		header.dwType = LOGMSG_GUILDLOG;
		header.stLength = sizeof(S2LGuildLog);
	}
	LogPlayerInfo logcommon;
	uint32		  guild_id;
	int16		  logtype;
};

struct S2LGuildDetailLog:public Msg
{
	S2LGuildDetailLog()
	{
		header.dwType = LOGMSG_GUILDDETAIL;
		header.stLength = sizeof(S2LGuildDetailLog);
	}
	LogPlayerInfo logcommon;
	uint32		  guild_id;
	int32		  moneychange;
	int32		  expchange;
	int32		  missionchange;
};

struct GS2LGMCommand:public Msg
{
	GS2LGMCommand()
	{
		header.dwType = LOGMSG_GMCOMMAND;
		header.stLength = sizeof(GS2LGMCommand);
		memset(frondose,0,sizeof(char)*128);
		memset(name,0,sizeof(char)*32);
		memset(ipAddr,0,sizeof(char)*32);
	}
	LogPlayerInfo logcommon;
	char   name[32];
	char   ipAddr[32];
	char   frondose[128];
};

struct GS2LChatInfo:public Msg
{
	GS2LChatInfo()
	{
		header.dwType = LOGMSG_CHATINFO;
		header.stLength = sizeof(GS2LChatInfo);
		memset(content,0,sizeof(char)*500);
		memset(TargetCharName,0,sizeof(char)*20);
	}
	LogPlayerInfo logcommon;
	char		  content[500];
	char		  TargetCharName[20];
	uint32		  target_id;
	int16		  chat_type;
};

#pragma pack( pop ) 

#endif