/********************************************************************
    Filename:    GameDefinePlayer.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __COMMON_GAMEDEFINEPLAYER_H__
#define __COMMON_GAMEDEFINEPLAYER_H__

#pragma once

#pragma pack ( push, 1 )

enum ENumeric
{
    NUMERIC_ZERO,
    NUMERIC_ONE,
    NUMERIC_TWO,
    NUMERIC_THREE,
    NUMERIC_FOUR,
    NUMERIC_FIVE,
    NUMERIC_SIX,
    NUMERIC_SEVEN,
    NUMERIC_EIGHT,
    NUMERIC_NINE ,
    NUMERIC_TEN ,
};

static const char* s_szChineseNumericString[] = { "零", "一", "二", "三", "四", "五", "六", "七", "八", "九", "十","十一","十二","十三","十四","十五","十六","十七","十八" };

enum ESendMessageState
{
    SEND_READY  ,   // 未发送
    SENDING     ,   // 发送中
    SNED_OVER   ,   // 发送完毕
};

//物品获得来源
enum EItemGetSource
{
    EIGS_UnKnow         ,    // 未知
    EIGS_OnlineReward   ,    // 在线奖励
    EIGS_Quest          ,    // 任务道具
    EIGS_Achieve        ,    // 成就奖励
    EIGS_DropItem       ,    // 打怪掉落
    EIGS_TreasureBox    ,    // 开宝箱
    EIGS_JiFengShop     ,    // 积分商店
    EIGS_NpcShop        ,    // NPC商店
    EIGS_Bargaining     ,    // 交易
    EIGS_Stall          ,    // 摆摊
    EIGS_Script         ,    // 脚本获得
    EIGS_Upgrade        ,    // 装备升阶
    EIGS_Compose        ,    // 合成
    EIGS_GemTakeDown    ,    // 宝石拆卸
    EIGS_FromPlat       ,    // 通过平台获得
	EIGS_GemInlayFail   ,    // 镶嵌失败降级
	EIGS_UnknowIdentify ,    // 装备未知鉴定
	EIGS_Mail			,	 // 邮件
	EIGS_Decompose		,	 // 分解
};

//重新计算属性来源
enum EWhereForeRecalcProperty
{
    EWRP_Init           ,    // 初始化
    EWRP_Equip          ,    // 装备
    EWRP_Level          ,    // 升级
    EWRP_Skill          ,    // 技能
    EWRP_Status         ,    // 状态
    EWRP_Title          ,    // 称号
    EWRP_Relive         ,    // 复活
    EWRP_Potential      ,    // 分配潜力点
};

//////////////////////////////////////////////////////////////////////////
//  成就系统相关

//成就大类
enum EAchieveMainType
{
    EAM_EverydayAchieve     = 1,    // 天道酬勤
    EAM_AdolesceAchieve     = 2,    // 成长之路
    EAM_TougheningAchieve   = 3,    // 江湖历练
    EAM_ArmamentAchieve     = 4,    // 绝世神兵
    EAM_BattleAchieve       = 5,    // 浴血沙场
};

enum EAchieveValueType
{
    EAT_OnlineTime          = 1     ,   //在线时间
    EAT_LoginDay            = 2     ,   //登陆天数
    EAT_BillAmount          = 3     ,   //累计充值      [未触发]
    EAT_Level               = 4     ,   //个人等级
    EAT_Reputation          = 5     ,   //个人声望
    EAT_Honour              = 6     ,   //个人荣誉
    EAT_Exploit             = 7     ,   //个人功勋
    EAT_Prestige            = 8     ,   //个人威望

    EAT_FirstTeam           = 9     ,   //第一次组队    
    EAT_FirstFriend         = 10    ,   //第一次加好友  
    EAT_FirstMaster         = 11    ,   //第一次拜师    
    EAT_FirstStudent        = 12    ,   //第一次收徒    
    EAT_JoinGuild           = 13    ,   //第一次加入帮派
    EAT_CreateGuild         = 14    ,   //第一次建立帮派

    EAT_EquipStar           = 15    ,   //装备升9星
    EAT_EquipStamp          = 16    ,   //装备铭刻
    EAT_EquipGem            = 17    ,   //宝石镶嵌
    EAT_EquipOpen           = 18    ,   //装备鎏金
    EAT_EquipAmulet         = 19    ,   //护身符

    EAT_BuyWeapon           = 20    ,   //买一把武器
    EAT_BuyRestore          = 21    ,   //买一个药品
    EAT_BuyArmour           = 22    ,   //买一件防具
    EAT_BuyOrnament         = 23    ,   //买一件饰品
    EAT_BuyHonour           = 24    ,   //买一件勋章    [未触发]

    EAT_EquipExchange       = 25    ,   //兑换装备      [未触发]
    EAT_GuildCloak          = 26    ,   //购买帮会披风  [未触发]
    EAT_Money               = 27    ,   //金钱
    EAT_JiaoZi              = 28    ,   //交子
    EAT_RecipeSkill         = 29    ,   //学习生活技能

    EAT_Rank1               = 30    ,   //排行榜
    EAT_Rank2               = 31    ,   //排行榜
    EAT_Rank3               = 32    ,   //排行榜
    EAT_Rank4               = 33    ,   //排行榜
    EAT_Rank5               = 34    ,   //排行榜
    EAT_Rank6               = 35    ,   //排行榜
    EAT_Rank7               = 36    ,   //排行榜
    EAT_Rank8               = 37    ,   //排行榜

    EAT_GoodMount           = 38    ,   //抓一匹良品马
    EAT_ExcellentMount      = 39    ,   //抓一匹精品马
    EAT_VariationMount      = 40    ,   //抓一匹变异马
    EAT_MountLevel          = 41    ,   //坐骑升级

    //////////////////////////////////////////////////////////////////////////
    //  脚本触发

	EAT_FinishTask			= 42	,	//完成X级剧情任务   
	EAT_EctypeCount_HJJ		= 43	,	//完成X次黄巾军副本
    //43	累计完成X次帮会暗战	
    //44	累计完成X次帮会护兽	
    //45	累计完成X次帮会内政	
    //46	累计完成X次帮会除魔	
    //47	累计完成X此帮会图腾	
    //48	累计上交X次帮会募集卷
    //49	累计上交X次帮贡捐献
    //50	参加一次帮会战
    //51	打赢一次帮会战
    //52	累计参加X次帮会战	
    //53	累计成功击毁敌国镖车	
    //54	累计成功击毁敌国护兽	
    //55	累计击杀敌国玩家	
    //56	累计完成X次国运任务	
    //57	累计完成X次出国任务	

    EAT_AddTitle            = 58    ,   //获得称号	  

    //////////////////////////////////////////////////////////////////////////
    //  脚本触发

    //59	参加国王争夺战
    //60	参加青龙之主争夺战
    //61	参加朱雀之主争夺战
    //62	累计完成X次云游四海任务
    //63	累计完成X次四大奸臣任务
    //64	累计完成X次武林大会任务
    //65	累计完成X次快马加鞭任务
    //66	累计完成X次个人狩猎任务
    //67	累计完成X此天降宝箱任务
    //68	累计完成X此内政任务
    //69	累计完成X此征税任务
    //70	副本无死亡通关
    //71	限时击杀副本BOSS
    //72	累计完成副本通关次数
    //73	累计X次击杀同一个副本BOSS
    //74	同时完成几个副本
    //75	完成江州法场副本
    //76	完成西域矿山副本
    //77	完成白虎岭副本
    //78	完成青龙道副本
    //79	完成凤凰山副本
    //80	完成玄武岛副本
    //81	完成秦皇地宫副本
    //82	完成无冤亡海副本
    //83	完成夜落七星副本
    //84	完成江州法场副本死亡次数小于几次
    //85	完成西域矿山副本死亡次数小于几次
    //86	完成白虎岭副本死亡次数小于几次
    //87	完成青龙道副本死亡次数小于几次
    //88	完成凤凰山副本死亡次数小于几次
    //89	完成玄武岛副本死亡次数小于几次
    //90	完成秦皇地宫副本死亡次数小于几次
    //91	完成无冤亡海副本死亡次数小于几次
    //92	完成夜落七星副本死亡次数小于几次
	EAT_FinishActivity				= 93		//完成活动次数
};

enum ECharAchieveState
{
    ECS_Unfinished  ,   // 未完成
    ECS_Finished    ,   // 已完成
    ECS_GetReward   ,   // 已领奖
    ECS_MaxCount    ,
};


enum EAchieveCompare
{
    EAC_Greater     ,   // 大于
    EAC_Equal       ,   // 等于
    EAC_Less        ,   // 大于
};

//////////////////////////////////////////////////////////////////////////

#define CHAR_AUTO_LEVELUP           10  //玩家自动升级等级
#define CHAR_OFFLINE_HOOK_LEVEL     40  //玩家离线挂机等级
#define CHAR_RELIVEMAP_LEVEL        10  //玩家重生点等级

////战神怒气回复 普通攻击怒气+5 被攻击怒气+2
//#define CHAR_WARRIOR_ATTACK_RESTORE_MP     5
//#define CHAR_WARRIOR_BEATTACK_RESTORE_MP   2

//坐骑相关
#define MOUNT_HP_RESTORE_COST    7   //  恢复坐骑生命值每10点花费7铜
#define MOUNT_HP_CONSUME         4   //  坐骑生命值每小时下降4点
#define MOUNT_LOWEST_ACTIVE_HP   1   //  坐骑出战生命值

#define MOUNT_HP_DROP_KILLED_BY_PALYER   10  //被其他玩家杀死下降10点
#define MOUNT_HP_DROP_KILLED_BY_MONSTER  20  //被怪物杀死下降20点

#define MOUNT_BREED_MASTER_LEVEL    60  // 骑乘繁殖等级主坐骑为60级
#define MOUNT_BREED_MONEY  1000         // 坐骑繁殖所需金钱

//玩家XP技能相关
#define DEF_CHAR_XP_LIMIT       1000
#define DEF_XP_NOFIGHT_RESTORE  2       // 玩家在游戏中等待回复，每10秒回复2点
#define DEF_XP_FIGHT_RESTORE    1       // 玩家在游戏中打怪，每打一下怪物回复1点

//装备相关
const int CharmAbsorbProbabilitys[SCharItem::EConstDefine_BaseRandMaxCount] = { 80, 40, 10, 0, 0, 0, 0 } ;   //符文布吸蓝概率

enum PKManagerEnum
{
    PKValueOp_Set    = 0,          
    PKValueOp_Add    = 1,
    PKValueOp_Reduce = 2,
};

enum EPKManagerConstDefine
{
    PKHonour_SelfCountry      = 12,
    PKHonour_ForeignCountry   = 30,
	PKHoniur15				  = 15,
	PKHoniur20		          = 20,
	PKHoniur5			      = 5,
	PKHoniur6				  = 6,

};

#define OFFLINE_HOOK_MAX_TIME       7 * 24 * 60 * 60 * 1000         //离线挂机时间最多可累积7天

#define CHAR_SYS_DOUBLE_EXP_MAX_TIME     300  * OneMinuteMicroSecond     //系统双倍经验时间最多300分钟
#define CHAR_ITEM_DOUBLE_EXP_MAX_TIME    9999 * OneMinuteMicroSecond     //道具双倍经验时间最多9999分钟

#pragma pack ( pop )

#endif // __COMMON_GAMEDEFINEPLAYER_H__
