/********************************************************************
Filename:     ItemDetail.h
MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __COMMON_ITEMDEFINE_H__
#define __COMMON_ITEMDEFINE_H__

#pragma once

#include "GlobalDef.h"
#include "GameDefinePet.h"
#include "GameDefineChar.h"
#include "Array.h"

//其实是 class CItemDetail 辅助头文件 不想让类太肥大
namespace ItemDefine
{
	enum EItemType
	{
		ITEMTYPE_RESTORE = 0    , // 恢复药品
		ITEMTYPE_WEAPON         , // 武器
		ITEMTYPE_ARMOUR         , // 防具
		ITEMTYPE_SKILL          , // 技能
		ITEMTYPE_STATUS         , // 状态
		ITEMTYPE_ACTION         , // 基本动作
		ITEMTYPE_MATERIAL       , // 原料
		ITEMTYPE_GEM            , // 宝石
		ITEMTYPE_CREATEITEMRULE , // 合成配方
		ITEMTYPE_TASK           , // 任务
		ITEMTYPE_OTHER          , // 其他[ 超链接 ]
		ITEMTYPE_REEL           , // 卷轴
		ITEMTYPE_TREASUREBOX    , // 宝箱( 包括钥匙 ) 
		ITEMTYPE_CHECKUP        , // 鉴定类道具
		ITEMTYPE_REALAWARD      , // 鉴定物品表( 包裹五行, 和移星 )
		ITEMTYPE_GUILD          , // 帮会压镖任务给的帮会军资
		ITEMTYPE_SPECIAL        , // 某些特定专用的物品
		ITEMTYPE_TALISMAN       , // 法宝		
		ITEMTYPE_PETEQUIP		, // 副将装备
		ITEMTYPE_MAX            ,
	};

	enum enumProfessionType
	{
		ProfessionType_Normal            = 0
		,ProfessionType_Element
		,ProfessionType_Max
	};

	enum enumConst
	{
		const_iSkillUnderstandPCondition    = 5
		,const_iSkillUnderstandSCondition   = 5
		,const_iSkillUsingPCondition        = 5
		,const_iMaxSkillSpecialAttrNum      = 3
		,const_iEquipTypeNum                = 15
	};

	//enum enumSkillUseTarget
	//{
	//    usetarget_pos
	//    ,usetarget_friend
	//    ,usetarget_enemy
	//    ,usetarget_
	//};
	//范围和持续魔法可以对地面发出
	//技能产生效果的对象（比如一个技能对朋友发出，产生伤害的时候却是对敌人）

	enum MountOperaType
	{
		OperaType_Normal = 0,           // 正常骑马
		OperaType_Control   ,           // 控制模式
	};

	enum enumMoveType
	{
		movetype_twofooted = 0          // 双足移动
		,movetype_fourfooted            // 四足移动
		,movetype_fly                   // 飞行移动
		,movetype_reptile               // 爬行移动
		,movetype_drive                 // 驾驶移动
		,movetype_twowheel              // 两轮移动
		,movetype_fourwheel             // 四轮移动
	};

	enum enumEffCenter
	{
		center_no = 0         //没有持续性效果
		,center_metotarget    //以自己到敌人
		,center_me            //以自己当前位置为中心
		,center_target        //以目标位置为中心
	}; 

	enum enumMountAction
	{
		MountDrive = 0,
		MountWalk,
		MountWalkBackWards,
		MountRun,
		MountJump,
		MountFallToTheGroundRun,
		MountDrop,
		MountGlide,
		MountShuffleLeft,
		MountShuffleRight,
		MountNeigh,
		MountBackAttack,
		//MountAttackIdle,
		//MountAttackRun,
		//MountScabbard,
		//MountDraw,
		MountMaxActionNum
	};

	enum enumItemParam
	{   
		//把其它的Item的ID号限制在这里
		StartID_GameAction     = 100,
		EndID_GameAction       = 999,

		StartID_Skill          = 1000,
		EndID_Skill            = 2399,

		StartID_Status         = 2400,
		EndID_Status           = 3699,

		StartID_Material       = 3700,
		EndID_Material         = 5699,

		StartID_Restore        = 5700,
		EndID_Restore          = 6699,

		StartID_Reel           = 6700,
		EndID_Reel             = 7699,

		StartID_Weapon         = 7700,
		EndID_Weapon           = 10699,

		StartID_Armour         = 10700,
		EndID_Armour           = 12699,

		StartID_Task           = 12900,
		EndID_Task             = 19099,

		StartID_Restore1       = 19100,
		EndID_Restore1         = 19999,

		StartID_WeaponRand     = 20001,
		EndID_WeaponRand       = 20500,

		StartID_ArmourRand     = 20501,
		EndID_ArmourRand       = 20999,

		StartID_CreateItemRule = 21000,
		EndID_CreateItemRule   = 22000,

		StartID_Armour1        = 22001,
		EndID_Armour1          = 27000,

		StartID_Weapon1        = 27001,
		EndID_Weapon1          = 32000,

		StartID_Gem            = 32001,
		EndID_Gem              = 34000, 

		StartID_Special        = 34001,
		EndID_Special          = 36000, 

		StartID_MonsterCard    = 36001, // 宠物怪物图鉴卡
		EndID_MonsterCard      = 38500, 

		StartID_Talisman       = 38500,
		EndID_Talisman         = 40000,

		MaxNum_Weapon          = EndID_Weapon1 - StartID_Weapon1,
		MaxLevel_Weapon        = 11,

		MaxNum_Skill           = EndID_Skill - StartID_Skill + 1,
		MaxLevel_Skill         = 21,

		MaxNum_Status          = EndID_Status - StartID_Status + 1,
		MaxLevel_Status        = 21,
	};

	//enum enumSkillType
	//{
	//    skill_phycic,        //物理攻击系的技能
	//    skill_magic            //魔法
	//};

	//enum enumContinuousSkill
	//{
	//    cskill_attack            = 0    //多次攻击结算的技能
	//    cskill_helper                //一次加成的辅助技能
	//};

	enum enumWeaponAttackRate
	{
		attack_slow = 0 // 缓慢攻击
		,attack_normal  // 普通攻击
		,attack_fast    // 快速攻击
	};

	//装备类型
	enum enumEquipType
	{
		equip_Helmet             = 1<<0,  // 头盔
		equip_Armour             = 1<<1,  // 铠甲
		equip_Glove              = 1<<2,  // 护手
		equip_Shoe               = 1<<3,  // 鞋子
		equip_Weapon             = 1<<4,  // 主武器
		equip_WeaponMinor        = 1<<5,  // 副武器
		equip_Badge              = 1<<6,  // 徽章
		equip_Ring               = 1<<7,  // 戒指
		equip_Bangle             = 1<<8,  // 手镯
		//        equip_Manteau            = 1<<9,  // 披风
		equip_Shoulder           = 1<<9,  // 肩甲
		equip_Necklace           = 1<<10, // 项链
		equip_Sash               = 1<<11, // 腰带
		equip_LeaderCard         = 1<<12, // 掌门卡
		equip_Amulet             = 1<<13, // 护身符
		equip_AecorativeGoods    = 1<<14, // 装饰的物品
		equip_AecorativeClothing = 1<<15, // 装饰的衣服
		equip_Trousers			 = 1<<16, // 裤子

		equip_TypeMaxCount       = 17,
	};    

	//道具珍贵程度 最差品  差品、普通品、优质品、极品
	enum enumItemClass
	{
		ItemClass_Worst = 0
		,ItemClass_Bad
		,ItemClass_Normal
		,ItemClass_Good
		,ItemClass_Best
		,ItemClass_Max
	};

	//技能种类
	//    普通技能:一次效果，不需要清除，如:造成伤害，瞬间移动，复活，加血
	//    功能描述
	//    瞬间移动    瞬间移动到目标地点
	//    辅助加成:一次效果，有持续时间，如:加攻                
	//    功能描述 技能持续时间
	//    加攻击        加攻击6        5000
	//    持续性范围技能:对范围内目标每个目标每 n 秒产生一次作用        
	//    功能描述 技能持续时间 作用间隔
	//    治愈之雨    加血30        5000        1000            
	//    冰雪地狱    攻击力20    5000        1000
	//    持续性范围辅助技能:对范围内目标每个目标每 n 秒产生一次作用,作用持续 n1 秒            
	//    功能描述 技能持续时间 加成持续时间 作用间隔
	//    攻击光环    加攻击6        5000        800            1000

	//技能类型
	enum ESkillType
	{
		skilltype_action    = 0, // 在动作播放结束后结算的，技能
		skilltype_magic_hit = 1, // 在动作播放结束后结算，释放出一个法术组件
		skilltype_magic_npc = 2, // 在动作播放结束后，释放出一个法术npc
		skilltype_passive   = 3, // 被动技能
	};

	//释放类型
	enum ECastType
	{
		casttype_singletarget             = 0, // 单一目标                   *
		casttype_singletargetcircleAOE    = 1, // 单一目标圆形范围           
		casttype_AOEPointCircleArea       = 2, // 目标地点的圆形范围
		casttype_AOEcircleself            = 3, // 以自己为中心的圆形范围技能 *
		casttype_AOEquartercirlcefrontage = 4, // 正面90度的扇型范围技能     *
		casttype_AOEhalfcirclefrontage    = 5, // 正面180度的半圆范围技能
		casttype_AOEquartercirlcebackage  = 6, // 背面90度的扇型范围技能
		casttype_AOEhalfcirclebackage     = 7, // 背面180度的半圆范围技能
		casttype_AOETargetcirclearea      = 8, // 以选定目标为中心的圆形范围技能
		casttype_MAX,
	};

	//技能的“力”类型
	//招式
	//必杀技
	//魔法
	enum enumSkillPowerType
	{
		//招式
		skillpower_zhaoshi = 0
		//必杀技
		,skillpower_bishaji                        
		//魔法
		,skillpower_magic
	};

	//状态的结算公式类型
	enum EStatusBalanceType
	{
		balance_status_type_none        , // 默认结算公式
		balance_status_type_restore     , // 回复结算公式
		balance_status_type_timeexp     , // 时间经验
		balance_status_type_mount       , // 坐骑被动技能
	};

	// 物品使用目标
	enum EUserTargetType
	{
		eTargetMe = 0   // 只对自己
		,eTargetEnemy   // 只对敌方
		,eTargetSelf    // 对已方人
		,eTargetAll     // 对所有人
		,eTargetMount   // 对坐骑
		,eTargetFriend  // 对朋友使用
		,eTargetPet     // 对宠物
	};    

	enum ESkillCastCondition
	{
		SCC_Null,              // 无条件
		SCC_MustInFightState,  // 必须在战斗状态
		SCC_MustOutFightState, // 必须不在战斗状态
	};

	enum ECollectSkillID        // 生活技能，包括生产技能
	{
		eCSI_CaiYao     = 2300, // 采药
		eCSI_CaiKuang   = 2301, // 采矿
		eCSI_BuChong    = 2307, // 捕虫
		eCSI_DuanZao    = 2309, // 锻造	
		eCSI_ZhuJia     = 2310, // 铸甲
		eCSI_GongYi     = 2311, // 工艺
		eCSI_LianYao    = 2312, // 炼药
		eCSI_XunMa      = 2313, // 驯马
		eCSI_ZhuBao     = 2314, // 珠宝
		eCSI_CatchPet   = 2315, // 捉宠物

		// 其他通用技能
		eCSI_GoBack     = 2302, // 回程技能
		eCSI_BuZhuo     = 2304, // 捕捉
		eCSI_Treasure   = 2306, // 采集任务物品
		eCSI_GoBack2    = 2390, // 防卡回程
	};

	enum ECannotJumpStatusID    // 无法跳跃的状态ID
	{
		eCJS_StatusID1  = 3350, // 镖车1
		eCJS_StatusID2  = 3351, // 镖车2   
	};

	enum EFlagModelID           // 旗子模型ID
	{
		eFMI_Start  = 9400,
		eFMI_End    = 9409
	};

	enum ESpecialSkillID
	{
		eSSI_Relive         = 1108      ,
		eSSI_MountMonster   = 2305      ,   // 骑马技能
		eSSI_PetActive      = 2316      ,   // 宠物出战技能
	};

	enum ESpecialStatusID
	{
		ESSI_JiangHuInvitation = 3173   ,   // 江湖请柬
		ESSI_DoubleExpStatus   = 3142   ,   // 双倍经验
	};

	enum ESpecialRestoreID
	{
		ESRI_ReliveItem =   6465        ,   // 复活道具
	};

	enum ECostType
	{
		CT_Money = 0        ,   // 钱
		CT_Reputation       ,   // 名望
		CT_Exploit          ,   // 功勋
		CT_Item             ,   // 物品
		CT_GuildOffer       ,   // 帮贡
		CT_GuildMoney       ,   // 帮会资金  ( 帮主才能用 )
		CT_GuildBuild       ,   // 帮会建设度( 帮主才能用 )
		CT_CostType1        ,   // 预留字段
		CT_CostType2        ,   // 预留字段
		CT_CostType3        ,   // 预留字段 
		CT_CostType4        ,   // 预留字段 
		CT_JiaoZi           ,   // 交子
		CT_Honour           ,   // 荣誉
		CT_CountryScore     ,   // 国战积分
		CT_MasterValue = 20,    // 师门威望
	};

	enum EItemQuality
	{
		IQ_While,		// 白装
		IQ_Green,		// 绿装
		IQ_DeepGreen,	// 深绿装
		IQ_Blue,		// 蓝装
		IQ_Purple,		// 紫装
		IQ_Orange,		// 橙色
		IQ_Gold,		// 金色
		IQ_Red,			// 红色
	};

	struct SItemCommon
	{
		SItemCommon()
		{
			memset(this, 0, sizeof(*this) );
			bCanSingingInterrupt = false;
			nDropMaxCount = -1;
		}

		bool  IsExclusive();                // 是否叠加 
		uint16 GetStackNum();               // 获得可叠加数量
		const char* GetItemName();
		const char* GetItemDesc();
		const char* GetIconInItemBag();
		const char* GetIconTile();
		const char* GetIconSoundFile();
		const char* GetSingEffect();
		const char* GetAssoilEffect();
		const char* GetHurtEffect();

		bool IsCanEquip() const { return ucItemType == ITEMTYPE_ARMOUR || ucItemType == ITEMTYPE_WEAPON; }

		unsigned short ustItemID;
		unsigned int   dwItemNameAddr; // 道具名字地址
		unsigned int   dwItemDescAddr; // 道具描述地址
		int            nUseTime;       // 使用时间 （小时为单位）
		int            nBill;          // 冲值
		unsigned int   dwCost;         // 物品价格
		unsigned char  costType;       // 价格类型
		unsigned short costItemID;     // 价格物品ID(需要物品时,要这个值来判断)
		unsigned short ustLevel;       // 物品品质(Skill和Status为等级)
		unsigned int   dwSpecialCost;  // 特殊物品的出售价格

		unsigned char  ucItemType;
		unsigned int   dwIconInItemBagAddr;
		unsigned int   dwIconSoundAddr;
		unsigned int   dwIconTileAddr;

		unsigned short ustModelIDOverGround;        
		char           cItemClass;           // 道具珍贵程度
		bool           bShowEquipEffect;     // 是否显示装备特效 缺省false
		unsigned short ustItemW,ustItemH;    // 占格宽，高
		bool           bIsCanDrop;           // 可否丢弃
		bool           bIsCanMove;           // 可否移动
		bool           bIsCanDestory;        // 可否销毁
		bool           bIsCanSellShop;       // 可否买卖
		bool           bIsCanPushInStorage;  // 是否可以放入仓库 1:可以放入;0:不可以放入。
		bool           bIsCanLocked;         // 物品可否加锁  1:可以加锁;0:不可以加锁
		unsigned int   dwSingEffect;         // 吟唱特效
		unsigned int   dwAssoilEffect;       // 释放特效
		unsigned int   dwHurtEffect;         // 命中特效
		unsigned short ustIconId;            // ICONID
		float          fWeight;              // 重量
		bool           bIsCanTrade;          // 可否交易
		unsigned int   dwUseSingTime;        // 使用物品吟唱时间
		bool           bCanSingingInterrupt; // 是否吟唱中可以打断 0为不可以 1为可以
		unsigned char  byUserTarget;         // 附加状态 附加状态等级 状态命中几率 物品使用目标
		bool           bIsCanBound;          // 可否绑定
		bool           bIsCanSplit;          // 可否拆分
		unsigned int   nDropControlCount;    // 物品掉落控制阈值
		bool           bIsClearControlCount; // 达到条件以后是否清除阈值 
		int            nDropMaxCount;        // 服务器产出上限  -1=无限制 0 = 不产出
		uint16         nStackNum;            // 道具可堆叠数量
		bool		   bIsSinging;			 // 客户端专用
	};

	// 坐骑消耗类物品特殊功能
	enum EMountRestoreItemSpecialFunction
	{
		EMRIF_None,
		EMRIF_RestoreHP,            //1 恢复坐骑生命 (草料)
		EMRIF_AddExp,               //2 给坐骑增加经验值 (融雪丹)
		EMRIF_ResetPoint,           //3 给坐骑洗点 (归元丹)
		EMRIF_OpenSkill,            //4 相马书
		EMRIF_ForgetSkill,          //5 笑忘书
		EMRIF_HuanLongShu,          //6 还龙书
		EMRIF_HuanTongShu,          //7 还童书
	};

	// 宠物消耗类物品特殊功能
	enum EPetRestoreItemSpecialFunction
	{
		EPetFunc_None,                 // 
		EPetFunc_RestoreHP,            // 1恢复宠物HP
		EPetFunc_AddLife,              // 2增加宠物寿命
		EPetFunc_AddLoyalty,           // 3增加宠物快乐度
		EPetFunc_AddExp,               // 4给宠物增加经验值 
		EPetFunc_AddSavvy,             // 5给宠物增加悟性
		EPetFunc_ResetPoint,           // 6给宠物洗点
		EPetFunc_HuanTongShu,          // 7宠物还童
		EPetFunc_OpenSkill,            // 8学习技能
		EPetFunc_ForgetSkill,          // 9遗忘技能
	};

	//角色消耗类物品特殊功能
	enum ECharRestoreItemSpecialFunction
	{
		ECharFunc_ResetPoint = 3		// 洗属性点
	};
	enum EItemRestoreType
	{
		EIRT_None       ,           // 无类型消耗品
		EIRT_RestoreHP  ,           // 恢复HP药品
		EIRT_RestoreMP  ,           // 恢复MP药品
		EIRT_Mount      ,           // 坐骑消耗品
		EIRT_Epistar    ,           // 晶元消耗品 by cloud
	};

	enum ERestoreUseStatusType
	{
		EUseStatusType_None,        // 无
		EUseStatusType_NoFight,     // 战斗外才能使用
		EUseStatusType_InFight,     // 战斗中才能使用
	};

	struct SItemRestore : public SItemCommon
	{
		SItemRestore()
		{   
			memset(this, 0, sizeof(*this) );
		}

		uint8          nRestoreType;      // 消耗品类型
		uint32         dwAddHP;           // 可增加的HP
		uint32         dwAddMP;           // 可增加的MP
		uint32         dwAddExp;          // 可增加的经验
		short          stSubHunger;       // 消除饥饿
		unsigned short ustSubStatusID;    // 解除状态
		unsigned short ustAddStatusID;    // 导致状态
		unsigned short ustAddStatusLevel; // 导致状态等级
		DWORD          dwCoolDown;        // colddown
		short          stCoolDownType;    // type
		bool           bExpendable;       // 是否可消耗(也就是数量会减少)
		bool           bIsReliveItem;     // 是否复活物品
		uint8          nUseFightStatus;   // 战斗使用状态
		short          stUseLevel;        // 使用等级
		short          nMountUseLevel;    // 坐骑使用等级
		bool           bHPAuto;           // 是否自动回复HP
		bool           bMPAuto;           // 是否自动回复MP
		bool           bAutoRelive;       // 是否是守护天使
		//bool           bExclusive;        // 是否独占一个背包栏，则不可叠加
		unsigned char  specialFunction;   // 特殊的功能
		uint32         dwAddHPOnce;       // 每次增加的HP
		uint32         dwAddMPOnce;       // 每次增加的MP
		uint16         openSkillNum;      // 开启技能数
		uint16         forgetSkillIndex;  // 遗忘所处位置技能
		uint8          petSavvy;          // 宠物悟性

		Array< bool, EArmType_MaxSize> arrayProfessionReq;         // 消耗品的职业需求
	};

	//装备品质等级 0灰 1白 2绿 3蓝 4金 5紫
	enum EEquipQualityLevel
	{
		//EQL_Gray    ,
		EQL_White   ,
		EQL_Green   ,
		EQL_DeepGreen   ,
		EQL_Blue    ,
		EQL_Purple  ,
		EQL_Orange  ,
		EQL_Golden  ,
		EQL_Red  ,
		EQL_Max
	};

	enum EEquipStatusTrigger
	{
		EEquipStatusTrigger_None        ,   
		EEquipStatusTrigger_Attack      ,   // 攻击触发
		EEquipStatusTrigger_BeAttack    ,   // 被攻击触发
		EEquipStatusTrigger_Damage      ,   // 受到伤害触发
	};

	struct SItemCanEquip : public SItemCommon
	{
		enum EConstDefine
		{
			ECD_DistortionIdCount     = 3,
			ECD_AdditiveRandAttrCount = 7, // 附加的随机属性
			ECD_PurpleRandAttrCount   = 3, // 紫色的随机属性
			ECD_HandModelCount    = 2,

			ECD_Repair_Normal     = 0,  // 普通修理
			ECD_Repair_Item       = 1,  // 需要物品来修理
			ECD_Repair_Exploit    = 2,  // 消耗功勋
			ECD_Repair_Reputation = 3,  // 消耗名望
			ECD_Repair_GuildOffer = 4,  // 消耗帮贡
			ECD_SkillSuitCount    = 5,  // 技能套装数量
			ECD_ElementSuitCount  = 6,  // 五行套装数量
		};

		uint32 ustEquipType;                                      // 装备类型
		int8   arrayCanEquip[ EEquipPartType_MaxEquitPart ];      // 部位可否装备 1:0
		int8   isCommon;                                          // 是否是通用装备
		uint32 dwReplaceSkinAddr;                                 // 代替皮肤名字地址
		int8   isSpecular;                                        // 是否有溜光特效
		int8   isCanDistortion;                                   // 是否可以变形
		Array< uint16, ECD_DistortionIdCount > arrayDistortionId; // 变形的模型的ID
		int8  cEquipSexReq;                                       // 装备得性别需求 如果==-1，就没有限制
		Array< bool, EArmType_MaxSize> arrayEquipArmsReq;         // 装备的职业需求
		int16 stEquipLevelReq;                                    // 装备的级别需求
		int   nPkValueNeed;                                       // pk值需求
		int   nTitleNeed;                                         // 称号需求
		int16 stRepairPrice;                                      // 修理价格/点
		int   stHPMax;                                            // 最大耐久度
		float fStatusRate;                                        // 状态命中几率(敌人)
		float fMyStatusRate;                                      // 状态命中几率(我)
		int16 stAddStatus;                                        // 附加状态(敌人)
		int16 stAddStatusLevel;                                   // 状态等级(敌人)
		int8  nAddStatusTrigger;                                  // 附加状态触发方式(敌人)
		int16 stMyAddStatus;                                      // 附加状态(我)
		int16 stMyAddStatusLevel ;                                // 状态等级(我)
		int8  nMyAddStatusTrigger;                                // 附加状态触发方式(我)

		//modified by junyi.chen begin
		//        int8 additiveRandCount;                                    // 附加属性随机个数
		bool bRandWhenCreate;										//是否装备产生时鉴定其附加随机属性
		Array<uint16, ECD_AdditiveRandAttrCount> additiveRandCountRates;  // 随机相应附加属性随机个数的概率,array[0] 是7个的概率,[1]是6个的,以此类推
		uint8 additiveRandLvLowerLimit;								//附加随机属性等级下限
		uint8 additiveRandLvUpperLimit;								//附加随机属性等级上限
		//TODO:可优化结构
		Array<uint8, RT_AddAttrMaxSize> typeFilter;					//类型筛选.随机附加属性时,对应[EquipmentRandom.slk]的[Type]字段,只从填写的类型里面随机附加属性
		//Array<uint8, RT_AddAttrMaxSize> typeFilter_hero;			//类型筛选.随机附加属性时,对应[EquipmentRandom.slk]的[Type]字段,只从填写的类型里面随机附加属性

		//        Array<bool, ECD_AdditiveRandAttrCount> additiveRandFlags;  // 附加属性随机标示
		Array<uint16, ECD_AdditiveRandAttrCount> additiveRandFlags;  // 附加属性随机标示

		//        Array<int16,ECD_AdditiveRandAttrCount> additiveRandValues; // 附加属随机值
		//end
		int8 purpleRandCount;                                     // 紫色属性随机个数
		Array<bool, ECD_PurpleRandAttrCount> purpleRandFlags;     // 紫色属性随机标示
		Array<int16,ECD_PurpleRandAttrCount> purpleRandValues;    // 紫色属随机值

		bool   bFashion;                                          // 是否是时装
		uint32 dwSoundAddr;                                       // 音效
		float  attackPhysics;                                     // 物理攻击力
		float  attackMagic;                                       // 魔法攻击力
		float  attackSpeed;                                       // 攻击速度
		float  exact     ;                                        // 命中率
		float  dodge     ;                                        // 闪避率
		float  critical  ;                                        // 暴击率
		float  tenacity  ;                                        // 韧性  
		//新加 元素属性
		float  breakStrike;										  // 破甲伤害
		float  breakResist;										  // 破甲抗性
		float  stabStrike;										  // 贯穿伤害
		float  stabResist;										  // 贯穿抗性
		float  elementStrike;									  // 元素伤害
		float  elementResist;									  // 元素抗性
		float  toxinStrike;										  // 毒素伤害
		float  toxinResist;										  // 毒素抗性
		float  spiritStrike;									  // 精神伤害
		float  spiritResist;									  // 精神抗性


		uint16 skillId;                                           // 技能Id
		uint16 skillLevel;                                        // 技能等级
		uint8  uchRepairType;                                     // 修理类型
		uint32 nRepairValue;                                      // 修理所消耗的值( 如果是物品休息, 这个值就是物品ID )
		int16  sPartCount;                                        // 套装组成数量
		int16  sSuitID;                                           // 套装Id
		bool   bIsElements;                                       // 是否五行套装
		//主将套装用这个主将ID，装备不是主将套装的话nHeroID = 0;
		int    nHeroID;											  // 主将套装的主将ID
		//
		uint16 unBindCount;										  //装备解绑的次数 -1为无限解绑 0为无法解绑 正数为解绑次数


		SItemCanEquip()
		{ memset(this, 0, sizeof(*this) ); }

		const int8* GetReplaceSkin();
		const int8* GetSound();
		int8        IsCommon()   { return isCommon;   }
		int8        IsSpecular() { return isSpecular; }
		int8        GetCanEquipIndex() // 获得可以装备的部位
		{
			int8 chIndex = -1;
			for ( int i = 0; i < EEquipPartType_MaxEquitPart; ++i )
			{
				if ( arrayCanEquip[i] == 1 )
				{   
					chIndex = i;
					break;
				}
			}
			return chIndex;
		}

		bool IsSuitEquip()        { return sSuitID != 0; }              // 是否是套装部件
		bool IsHeroSuitEquip()	  { return sSuitID != 0 && nHeroID != 0; }				// 是否主将套装
		bool IsSkillSuitEquip()   { return ( sSuitID != 0 && sPartCount == ECD_SkillSuitCount ); }                  // 是否是技能套装部件
		bool IsElementSuitEquip() { return ( sSuitID != 0 && sPartCount == ECD_ElementSuitCount && bIsElements ); } // 是否是五行套装部件
		bool IsCannotEvolve()     { return !(ustEquipType < equip_LeaderCard) ; }
		bool RandWhenCreate()const{ return bRandWhenCreate; }	        //是否产生时鉴定其附加随机属性
		bool HasEquipHp();
	};

	struct SItemWeapon : public SItemCanEquip
	{
		uint16  ustModelID[ ECD_HandModelCount ];
		uint16  ustIdleModelID;
		int16   stWeaponType;      // 武器类型
		float   fWeaponAttackRate; // 武器的挥动速度
		bool    bTwoHandWeapon;    // 是否是双手武器
		float   fAtkRange;         // 攻击范围
		int32   iShotEffectID;     // 发射特效，弓箭类的武器才需要填写

		SItemWeapon()
		{ memset(this, 0, sizeof(*this) ); }  
	};

	struct SItemArmour : public SItemCanEquip
	{
		int8   isCape;     // 是否为袍子
		int8   isHeadWear; // 是否为头饰
		uint16 ustModelID[EArmType_MaxSize][2][2];
		int16  stTypeForInGem   ; // 强化类型
		float  defendPhysics    ; // 物理防御
		float  defendMagic      ; // 魔法防御
		/*
		* Author: 2012-10-9 16:10:19 liaojie
		* Desc:   添加HP和MP
		*/
		int		Hp				; // HP
		int		Mp				; // MP

		SItemArmour()
		{ memset(this, 0, sizeof(*this) ); }

		char IsCape()              { return isCape;       } // 是否袍子
	};

	// 物品制造,原料与产品的对应关系
	struct SProduceItem
	{
		SProduceItem() : ustMaterialID("[ItemDetail.h]SProduceItem.ustMaterialID"),
			ustMaterialNum("[ItemDetail.h]SProduceItem.ustMaterialNum")
		{
			memset( this, 0x00, sizeof(*this) );
		}
		//unsigned short ustMaterialID[ 3 ];
		//unsigned short ustMaterialNum[ 3 ];
		Array<unsigned short, 3>    ustMaterialID;
		Array<unsigned short, 3>    ustMaterialNum;    //Luoz add
		unsigned short ustToolID;
		unsigned short ustSpriteSkillID;
		unsigned short ustSpriteSkillLevel;
		unsigned short ustResultGoodID;
		unsigned short ustSuccessRate;
	};

	////魔法材料的结构
	//struct SItemMagic:public SItemCommon
	//{
	//    unsigned short ustSuccessRate;        //千分之...

	//    unsigned short ustSpecialRate[ 7 ];    //千分之...
	//    unsigned short ustAffectWeaponMin[ 7 ];
	//    unsigned short ustAffectWeaponMax[ 7 ];
	//    unsigned short ustAffectClothesMin[ 7 ];
	//    unsigned short ustAffectClothesMax[ 7 ];
	//    unsigned short ustAffectShoeMin[ 7 ];
	//    unsigned short ustAffectShoeMax[ 7 ];
	//    unsigned short ustAffectGloveMin[ 7 ];
	//    unsigned short ustAffectGloveMax[ 7 ];
	//    unsigned short ustHeadPieceMin[ 7 ];
	//    unsigned short ustHeadPieceMax[ 7 ];
	//    unsigned short ustDecorateMin[ 7 ];
	//    unsigned short ustDecorateMax[ 7 ];
	//    unsigned short ustStatusRate;
	//};

	//领悟技能的职业条件
	struct SSkillProfessionCondition
	{
		short stProfessionID;
		short stNeedLevel;
	};

	//领悟技能的技能使用条件
	struct SSkillUsedCondition
	{
		unsigned short ustSkillID;
		//在以下区间能可能领悟
		unsigned short ustMinUsed,ustMaxUsed;
	};

	//领悟技能的条件
	struct SSkillUnderstandCondition
	{
		SSkillUnderstandCondition() : profession("[ItemDetail.h]SSkillUnderstandCondition.profession"),
			skillused("[ItemDetail.h]SSkillUnderstandCondition.skillused")
		{
		}
		int iProfessionNum;
		//SSkillProfessionCondition    profession[ const_iSkillUnderstandPCondition ];
		Array<SSkillProfessionCondition, const_iSkillUnderstandPCondition>    profession;
		int iSkillUsedNum;
		//SSkillUsedCondition            skillused[ const_iSkillUnderstandSCondition ];
		Array<SSkillUsedCondition, const_iSkillUnderstandSCondition>    skillused;    //Luoz add
	};

	//使用技能的条件
	struct SSkillUsingCondition
	{
		SSkillUsingCondition() : profession("[ItemDetail.h]SSkillUsingCondition.profession")
		{
		}
		int iProfessionNum;
		//SSkillProfessionCondition    profession[ const_iSkillUsingPCondition ];
		Array<SSkillProfessionCondition, const_iSkillUsingPCondition>    profession;
	};

	enum EnumSkillActionFlags
	{
		IS_AUTO_STOP        = 0x01,    // 施放技能立刻停下，并不能跳跃
		CAN_MOUNT_CAST      = 0x02,    // 骑马时能施放
		IS_WHOLE_ACTION     = 0x04,    // 是全身动作技能
		CANNOT_JUMP_CAST    = 0x08,    // 跳跃时无法施放，且施放时不能跳跃
		ONLY_MOUNT_CAST     = 0x10,    // 只能马上释放
	};

	enum EnumMountSkillProfessionType   // 职业相关的只能马上施放的技能
	{
		MSPT_ALL            = 0x00,
		MSPT_SPEAR          = 0x01,
		MSPT_STAFF          = 0x02,
		MSPT_FAN            = 0x04,
		MSPT_SWORD          = 0x08,
		MSPT_BOW            = 0x10
	};

	enum ESkillHpLimitType
	{
		SHT_None,  // 无
		SHT_Above, // 高于
		SHT_Under, // 低于
		SHT_TargetAbove, // 高于
		SHT_TargetUnder, // 低于
	};

	enum ESpecialTargetType
	{
		STT_NONE = 0, // 无
		STT_MINHP,    // 血最少
		STT_MINMP,    // 蓝最少
		STT_MINLEVEL, // 等级最低
	};

	enum ESkillCategoryType
	{
		SCT_Attack,     // 人攻击技能
		SCT_Passive,    // 人被动技能
		SCT_Assistant,  // 人辅助技能

		SCT_MountPassive = 10,              // 坐骑被动技能
		SCT_MountMasterInitiativeUnControl, // 坐骑主人不可控主动技能
		SCT_MountMasterInitiativeControl,   // 坐骑主人可控主动技能

		SCT_PetPassive = 20,                // 宠物被动技能
		SCT_PetMasterAutoUnControl,         // 宠物主人不可控主动技能
		SCT_PetMasterManualControl,         // 宠物主人可控主动技能

		//加主将技能类型的话加到这两个主将技能类型的中间
		SCT_HeroPassive = 30,				// 主将被动技能
		SCT_HeroAttack,						// 主将主动技能
	};

	enum ESpecialSkillType
	{
		ESST_Normal = 0         ,   // 常规类型

		ESST_Capture            ,   // 捕获       套装技能
		ESST_SuckFetch          ,   // 吸魂       套装技能
		ESST_BreakOut           ,   // 爆烈       套装技能
		ESST_CallGraphic        ,   // 呼叫验证码 套装技能
		ESST_Other              ,   // 其他       套装技能
		ESST_SuitMax    = 39    ,   // 套装技能最大类型

		ESST_Team               ,   // 队伍技能
		ESST_TeamRelive         ,   // 队伍复活
		ESST_TeamFly            ,   // 队伍传送
		ESST_TeamMax    = 79    ,   // 队伍技能最大类型

		ESST_XPSkill    = 99    ,   // XP技能
		ESST_PetActive  = 100   ,   // 宠物出战技能
	};

	// 技能所属的总类
	enum ESkillGeneralType
	{
		generaltype_action   = 0, // 属于Action技能
		generaltype_magic    = 1, // 属于Magic技能
		generaltype_sequence = 2, // 属于连招技能
		generaltype_passive  = 3, // 属于被动技能
		generaltype_trigger  = 4, // 属于被动触发技能
	};


	//查找技能作用对象的标志
	enum ESkillTarget
	{
		target_no          , // 无目标
		target_myself      , // 我
		target_friend      , // 朋友
		target_normalplayer, // 普通玩家(所有玩家包括自己除了敌人)
		target_enemy       , // 敌人(只能对敌人)
		target_dead        , // 死亡目标(只对死人)
		target_herb        , // 目标草药
		target_mine        , // 目标矿
		target_wood        , // 目标木头
		target_treasure    , // 目标宝箱
		target_pet         , // pet为目标
		target_all         , // 所有人都可以
		target_team        , // 队伍目标
		target_mount       , // 目标坐骑
		target_insect      , // 目标昆虫
		target_guild       , // 公会
		target_campforce   , // 同阵营势力
	};

	enum ESkillCastTarget
	{ //技能使用目标类型
		casttarget_me           , // 以自己为目标
		casttarget_friendlive   , // 以朋友生物为目标
		casttarget_enemylive    , // 敌人生物
		casttarget_live         , // 所有生物
		casttarget_pos          , // 以位置为目标
		casttarget_friendcorpse , // 以朋友尸体为目标
		casttarget_enemycorpse  , // 以敌人尸体为目标
		casttarget_corpse       , // 尸体
		casttarget_herb         , // 以草药为目标
		casttarget_mine         , // 以矿为目标
		casttarget_wood         , // 以木头为目标
		casttarget_treasure     , // 以宝箱为目标
		casttarget_pet          , // 以宠物为目标
		casttarget_team         , // 队伍目标
		casttarget_mount        , // 坐骑为目标
		casttarget_insect       , // 昆虫为目标
		casttarget_guild        , // 公会成员
		casttarget_campforce    , // 同阵营势力
	};

	enum EPassiveSkillTarget
	{
		PassiveSkillTarget_Self             , // 作用自己的被动技能
		PassiveSkillTarget_AllPet           , // 作用所有宠物的技能
		PassiveSkillTarget_TargetPet        , // 作用目标宠物的技能
		PassiveSkillTarget_SelfAndAllPet    , // 作用自己和所有宠物的技能
		PassiveSkillTarget_SelfAndTargetPet , // 作用自己和目标宠物的技能
	};

	enum ESkillBalanceType
	{ // 结算类型
		balancetype_none                , // 没有任何结算
		balancetype_damagephysicaldefend, // 对物理防做伤害结算
		balancetype_damagemagicdefend   , // 对魔法防做伤害结算
		balancetype_damagebothdefend    , // 对物防魔防都做伤害结算
		balancetype_restorehpmp         , // 回HP结算
		balancetype_relive              , // 复活结算
	};

	enum EClearStatueType
	{
		CLEAR_STATUS_0   ,    
		CLEAR_STATUS_1   , 
		CLEAR_STATUS_2   , 
		CLEAR_STATUS_3   , 
		CLEAR_STATUS_4   , 
		CLEAR_MAX_STATUS ,
	};

	//吟唱结束类型
	enum EIntonateInterruptType
	{
		EIT_Normal      ,   // 正常结束
		EIT_Move        ,   // 移动打断
		EIT_Jump        ,   // 跳跃打断
		EIT_Msg         ,   // 消息打断
		EIT_Map         ,   // 切换地图
		EIT_Force       ,   // 强制打断

		EIT_MaxType     ,   // 最大类型
	};


	struct SItemSkill : public SItemCommon
	{ //技能的定义
		enum EItemSkillConst
		{
			EItemSkillConst_ActionMaxSize           = 10,
			EItemSkillConst_ActionSpeedMaxSize      = 20,
			EItemSkillConst_SkillNeedMaxSize        = 3,
			EItemSkillConst_AddStatusMaxSize        = 2,
			EItemSkillConst_DispelStatusMaxSize     = 4,

			EItemSkillConst_AddDamageType_None          = 0,    //无附加伤害
			EItemSkillConst_AddDamageType_Status        = 1,    //状态附加伤害
			EItemSkillConst_AddDamageType_Profession    = 2,    //职业附加伤害
			EItemSkillConst_AddDamageType_All           = 3,    //全附加伤害

			EItemSkillConst_MeStatusFirstIndex      = 0,
			EItemSkillConst_MeStatusSecondIndex     = 1,

			EItemSkillConst_XinFaMaxSize            = 5, // 技能所属心法个数
		};

		enum EMountSkillCategory
		{
			EMountSkillCategory_Aptitude    =   1,  // 资质类
			EMountSkillCategory_Restore     =   2,  // 回复类
			EMountSkillCategory_Assist      =   3,  // 辅助类
			EMountSkillCategory_Control     =   4,  // 控制类
			EMountSkillCategory_Profession  =   5,  // 职业类
			EMountSkillCategory_Special     =   6,  // 特殊类
			EMountSkillCategory_MaxSize     =   7,
		};

		struct SEasyUseData
		{
			bool bApplyToFriend;
			bool bSkillWithDamage; // 能造成伤害的技能
			bool bCanAttackPos;    // 可以攻击地面

			SEasyUseData()
			{
				bApplyToFriend   = false;
				bSkillWithDamage = false;
				bCanAttackPos    = false;
			}
		};

		uint32                         dwSkillNameAddr;             // 技能名字地址
		uint32						   dwRideAction;				// 骑战技能动作
		uint32						   dwRideIntonateAction;		// 骑战读条技能动作
		Array<uint32, EItemSkillConst_ActionMaxSize> dwSkillAction; // 技能动画名字
		uint16                         groupId;                     // 技能组ID
		uint16                         groupLevel;                  // 技能组等级
		uint16                         ustLevel;                    // 技能的等级
		uint16                         ustPrepTime;                 // 吟唱时间 (ms)
		bool                           bShowIntonateBar;            // 是否显示吟唱条 [客户端使用]
		uint32                         dwIntonateAction;            // 吟唱准备动作
		uint32                         dwIntonateEffectAddr;        // 吟唱特效  ( 男 )
		uint32                         dwAttackerEffectAddr;        // 攻击者特效( 男 )
		uint32                         dwSkillEffectAddr;           // 技能特效  ( 男 )
		uint32                         dwTargetEffectAddr;          // 目标特效  ( 男 )
		uint32                         dwIntonateEffectAddr2;       // 吟唱特效  ( 女 )
		uint32                         dwAttackerEffectAddr2;       // 攻击者特效( 女 )
		uint32                         dwSkillEffectAddr2;          // 技能特效  ( 女 )
		uint32                         dwTargetEffectAddr2;         // 目标特效  ( 女 )
		uint16                         ustIDTargetHitAction;        // 目标NPC被击的动作
		uint8                          triggerType;                 // 技能触发类型
		float                          actionRatio;                 // 技能触发几率
		uint16                         normalAttackRatio;           // 普通公司出发几率
		int16                          ustMeAddStatusID[EItemSkillConst_AddStatusMaxSize];            // 附加状态编号(给我的)
		uint16                         ustMeAddStatusLevel[EItemSkillConst_AddStatusMaxSize];         // 附加状态等级(给我的)
		int16                          ustDstAddStatusID[EItemSkillConst_AddStatusMaxSize];           // 附加状态编号(给对方的)
		uint16                         ustDstAddStatusLevel[EItemSkillConst_AddStatusMaxSize];        // 附加状态等级(给对方的)
		uint16                         ustStatusHitRate;            // 状态命中几率
		uint32                         dwSubComboStatus;            // 解除状态位置
		Array<uint32,CLEAR_MAX_STATUS> dwClearStatus;               // 解除状态ID
		uint16                         ustHoldTime;                 // 僵硬时间
		uint16                         ustDamageBalanceType;        // 使用的伤害结算公式
		Array<uint16, EItemSkillConst_ActionSpeedMaxSize>  ustSkillActionSpeed;  // 技能动作的播放速度
		uint16                         ustCostHP;                   // 消耗HP
		uint16                         ustCostHPPer;                // 消耗HP(%)
		uint16                         ustCostMP;                   // 消耗MP
		uint16                         ustCostMPPer;                // 消耗MP(%)    
		int16                          stSkillType;                 // 技能的类型(是普通攻击，是必杀技(哪一种必杀技)，是法术(哪一个法术)是火墙，还是火球..)
		int16                          stGeneralType;               // 技能所属的总类(一种是Action类型；一种是Magic类型;一种是连招技能,一种是被动技能)
		int16                          stTargetType;                // 作用的对象类型
		int32                          iDurationTime;               // 效果的持续时间
		int32                          iDamageBalanceDelay;         // 效果伤害的结算间隔
		int16                          stEffectCenterType;          // 持续效果中心类型
		bool                           bMoveInterrupt;              // 是否移动打断      true 为可打断 false 为不可打断
		int8                           cLearnProfessionReq;         // 技能的职业需求
		int16                          stLearnLevelReq;             // 技能的等级需求
		float                          fRangeCanCast;               // 最大施法距离
		float                          fRangeCanCastMin;            // 最小施法距离
		int16                          stDamageEffectDistance;      // 伤害有效距离(?)
		int16                          shCastType;                  // 施放范围类型
		int16                          shMaxTargetNum;              // 最大目标个数
		float                          fAOEradius;                  // 范围技能的半径
		bool                           bNeedWeapon;                 // 是否需要武器
		int16                          stUseItem;                   // 使用此技能所需要的道具
		bool                           bHoldSkill;                  // 维持技能的持续时间>0
		uint16                         ustHoldEffect;               // 维持技能特效
		uint32                         dwSkillCoolDownTime;         // 冷却时间
		int32                          nSkillCoolDownType;          // 冷却类型 
		uint16                         ustCastTarget;               // 施法目标
		Array<int16,EItemSkillConst_SkillNeedMaxSize> stSkillNeed;      // 技能条件
		Array<int16,EItemSkillConst_SkillNeedMaxSize> stSkillLevelNeed; // 学习牵制技能等级
		int32                          stMoneyNeed;                 // 学习所需金钱
		int16                          stWeaponNeed;                // 武器类型要求
		int16                          stEnmity;                    // 该技能所能造成的仇恨值变化
		bool                           bContinueAtt;                // 是否继续攻击
		int16                          stSkillHitRate;              // 技能命中率
		uint16                         ustSkillMaxLvl;              // 技能最大等级
		bool                           bNeedTestBackStrike;         // 是否需要背击判定
		float                          fBackStrikePlus;             // 背击加成
		bool                           bNeedTestAngle;              // 是否需要角度判定
		float                          fAngle;                      // 施放角度
		bool                           bEmissionSkill;              // 是否发射技能
		bool                           bAssaultSkill;               // 是否冲锋技能
		bool                           bHideSkill;                  // 是否隐形技能
		bool                           bGiddyDischarge;             // 眩晕是否可以释放
		bool                           bCancelHideSkill;            // 是否会撤消当前的隐形状态
		bool                           bAutoAttackTarget;           // 是否自动攻击锁定目标
		int32                          nLearnNeedExp;               // 学习技能需要的技能经验
		int32                          nSuckHpAtt;                  // 吸收HP
		int32                          nSuckMpAtt;                  // 吸收MP
		bool                           bIsRelive;                   // 是否复活技能
		float                          fReliveHp;                   // 复活生命HP
		float                          fReliveMp;                   // 复活MP
		bool                           bSummonSkill;                // 是否召唤技能
		int32                          nSummonMonsterId;            // 召唤的宠物Id
		int16                          shPassiveSkillTarget;        // 被动技能作用对象
		int32                          nPassiveSkillTargetSkillID;  // 被动技能作用的技能ID
		int16                          stBackStrikeMeStatus;        // 背击给我的状态Id
		int16                          stBackStrikeMeStatusLevel;   // 背击给我的状态等级
		int16                          stBackStrikeDstStatus;       // 背击给对方的状态
		int16                          stBackStrikeDstStatusLevel;  // 背击给对方的状态等级
		float                          fBackStrikeStatusRate;       // 背击状态命中率
		char                           cHpLimitType;                // 使用技能血量限制的类型
		float                          fHpPerLimit;                 // 使用技能血量限制百分比
		uint32                         ustInstantMovingType;        // 是否瞬间移动
		bool                           bIsAfterIllusion;            // 是否残像技能
		int32                          nInterruptIntonatingAbility; // 干扰吟唱的能力
		bool                           bEnterFightStatus;           // 是否进入战斗状态
		bool                           bIsCatchNurturePet;          // 是否捕捉宠物
		bool                           iskillpet;                   // 是否杀死宝宝
		bool                           ispettouseskill;             // 是否使宝宝释放技能
		uint16                         ustPetSkillID;               // 宝宝使用技能ID
		uint16                         ustPetSkillLevel;            // 宝宝使用技能等级
		bool                           needpet;                     // 有宝宝才能使用技能
		int32                          iSkillActionFlags;           // 技能行为方面综合标志
		uint16                         usConsumeFightPower;         // 消耗的斗气值
		uint16                         usIncreaseFightPower;        // 增加的斗气值
		uint32                         dwSkillDescription;          // 技能描述
		int32							nAddonDesc1;				// 技能描述附加值
		int32							nAddonDesc2;				// 技能描述附加值
		int32							nXinFaID;					// 所属心法ID
		int32							nLearnNeedXinFaLevel;		//	学习需要心法等级
		uint32                         dwCommonCoolDownTime;        // 公共冷却时间
		float                          fDamageRate;                 // 伤害百分比
		uint32                         dwDamageDelayBalanceTime;    // 伤害延迟结算时间
		char                           cFightStateCastType;         // 战斗状态释放类型
		bool                           bMustInBackUse;              // 必须在背后才可攻击
		uint16                         usSpecialTargetType;         // 特殊目标判定
		float                          fFPDamageRatio;              // 斗气影响伤害率
		bool                           bNextNotIntonate;            // 接下来吟唱不要吟唱
		int8                           nNextNotIntonateNum;         // 接下来吟唱不要吟唱次数
		uint16                         sSkillCategory;              // 技能种类 ESkillCategoryType
		bool                           bScriptRunSkill;             // 是否脚本执行技能
		int32                          iMountSkillProfessionType;   // 职业相关的只能马上施放的技能，具体定义见EnumMountSkillProfessionType
		uint16                         usConsumeVigor;              // 消耗的精力值
		uint16                         specialSkillType;            // 特色技能类型

		uint8                          additionalDamageType;	    // 附加伤害类型
		uint32                         additionalDamageStatus;	    // 附加伤害状态
		uint16                         additionalDamagePer;         // 附加伤害百分比
		int8                           additionalDamageProfession;  // 附加伤害职业
		int16                          addtionalCritical;           // 暴击率加成

		uint16                         additionalPhyAttack;         // 附加物理攻击力
		uint16                         additionalMagAttack;         // 附加魔法攻击力

		int8                           dispelNegativeType[EItemSkillConst_DispelStatusMaxSize];         // 解除负面状态类型

		uint8                          mountSkillCategory;          // 坐骑技能类别
		uint8                          mountAptitudeCategory;       // 坐骑技能资质类别  
		uint16                         mountAptitudeModulus;        // 坐骑技能系数

		int8                           petSkillCategory;            // 宠物技能类别
		int8                           petAutoSkillType ;           // 宠物自动技能类型
		uint8                          petAutoSkillTriggerRate;     // 宠物自动技能基础触发几率

		uint16                         releaseLapoverStatus;        // 释放叠加技能
		uint16                         breakStrike      ;           // 破甲伤害
		uint16                         stabStrike       ;           // 贯穿伤害
		uint16                         elementStrike    ;           // 元素伤害
		uint16                         toxinStrike      ;           // 毒素伤害
		uint16                         spiritStrike     ;           // 精神伤害


		Array< bool, EArmType_MaxSize> arrayProfessionReq;          // 技能释放需要职业

		SEasyUseData                   easyusedata;                 // 简易查询数据

		SItemSkill() : dwSkillAction("[SItemSkill.dwSkillAction"),dwClearStatus("SItemSkill.dwClearStatus"),
			ustSkillActionSpeed("SItemSkill.ustSkillActionSpeed"), stSkillNeed("SItemSkill.stSkillNeed"), 
			stSkillLevelNeed("SItemSkill.stSkillLevelNeed")
		{
			bSummonSkill                = false;
			nSummonMonsterId            = -1;
			bAssaultSkill               = false;
			bCancelHideSkill            = true;
			bHideSkill                  = false;
			bGiddyDischarge             = false;
			bEmissionSkill              = false;
			bAutoAttackTarget           = false;
			bNeedTestBackStrike         = false;
			bNeedTestAngle              = false;
			fAngle                      = D3DX_PI;
			shCastType                  = 0;
			shMaxTargetNum              = 1;
			bIsAfterIllusion            = false;
			nInterruptIntonatingAbility = 0;
			bEnterFightStatus           = true;
			iskillpet                   = false;

			ustMeAddStatusID[0]         = -1;
			ustMeAddStatusLevel[0]      = 0 ;
			ustMeAddStatusID[1]         = -1;
			ustMeAddStatusLevel[1]      = 0 ;
			ustDstAddStatusID[0]        = -1;
			ustDstAddStatusLevel[0]     = 0 ;
			ustDstAddStatusID[1]        = -1;
			ustDstAddStatusLevel[1]     = 0 ;
		}
		const char* GetSkillName();
		const char* GetSkillRideAction();
		const char* GetSkillAction( int Index );
		const char* GetIntonateAction();
		const char* GetIntonateEffectName();
		const char* GetIntonateEffectName2();
		const char* GetAttackerEffectName();
		const char* GetAttackerEffectName2();
		const char* GetTargetEffectName();
		const char* GetTargetEffectName2();
		const char* GetSkillEffectName();
		const char* GetSkillEffectName2();
		const char* GetSkillDescription();
		const char* GetRideIntonateAction();

	};

	enum EStatusRestoreType
	{
		ESRT_OnlyInServer = 0,  // 在一个服务器内存 有效
		ESRT_OnlyInWorld,       // 在整个游戏世界范围内存 有效
		ESRT_Forever,           // 无论什么时候都存
		ESRT_Never,             // 无论什么时候都不存
		ESRT_OnlyInMap,         // 在同一地图内存   有效
	};

	struct SItemStatus : public SItemCommon
	{ // 状态的定义
		enum EConstDefine 
		{
			ECD_TimeExpMulModulusCount = 5,
			ECD_DurationTimeForever    = -1, // 永久Buffer

			ECD_ChangeSkillMaxSize     = 4,
		};

		uint16                        ustLevel          ; // 状态等级
		uint32                        dwStatusEffectAddr; // 状态特效
		uint32                        dwStatusActionAddr; // 状态动作
		bool                          bAvail            ; // 是否有利状态
		int32                         iDurationTime     ; // 状态持续时间(ms)
		int32                         iBalanceDelayTime ; // 影响间隔时间(ms)
		int16                         stType            ; // 状态的类型
		int16                         stPriority        ; // 状态的优先级别
		bool                          bIsCanCong        ; // 是否可叠加
		int16                         stBalanceType     ; // 状态结算公式
		bool                          bAttckedNoStatus  ; // 受到攻击解除该状态
		bool                          bAttckNoStatus    ; // 攻击解除该状态        
		int16                         changePhyAttackPer; // 改变物理攻击力%
		float                         changePhyAttack   ; // 改变物理攻击力
		int16                         changeMagAttackPer; // 改变魔法攻击力%
		float                         changeMagAttack   ; // 改变魔法攻击力
		Array<int16, EDefendType_Max> changeDefendPer   ; // 改变防御力%
		Array<float, EDefendType_Max> changeDefend      ; // 改变防御
		int16                         changeHPMaxPer    ; // 生命最大值%
		int32                         stChanged_HPMax   ; // 生命最大值
		int16                         changeMPMaxPer    ; // 能量最大值%
		int32                         stChanged_MPMax   ; // 能量最大值
		int16                         resumeHPPer       ; // 生命恢复%
		int16                         resumeHP          ; // 生命恢复
		int16                         resumeMPPer       ; // 能量恢复%
		int16                         resumeMP          ; // 能量恢复
		int32                         stChanged_HP      ; // 更改生命
		int32                         stChanged_MP      ; // 更改能量
		int32                         recoverHPBasePer  ; // 恢复生命基础%
		int32                         recoverMPBasePer  ; // 恢复能量基础%
		int32                         recoverHPMaxPer   ; // 恢复生命上限%
		int32                         recoverMPMaxPer   ; // 恢复能量上限%
		int32                         changeActivityMax ; // 更改活力上限
		int16                         stChanged_Hit     ; // 更改命中能力
		int16                         stChanged_Hedge   ; // 更改躲闪能力
		int16                         changeTenacity    ; // 韧性
		int16                         changed_Critical  ; // 改变暴击率
		int16                         changed_CriticalIntensity    ; // 改变暴击伤害
		float                         fChanged_ReboundVal     ; // 伤害反弹比例
		uint8                         nDamageReflectProability; // 伤害反弹几率
		int16                         stAbsorbExtraHPVal      ; // 吸血值
		float                         fSuckHpRate             ; // 吸血比例
		uint8                         nSuckHpProbability      ; // 吸血的几率
		float                         fMoveSpeedChanged       ; // 移动速度
		int16                         nMoveSpeedPer           ; // 移动速度 %
		float                         fAttSpeedPer            ; // 攻击速度
		bool                          bIsMove                 ; // 是否能移动        
		bool                          bIsAtt                  ; // 是否能物理攻击
		bool                          bIsUsingMagic           ; // 是否能使用魔法   
		bool                          bIsBePhyAttack          ; // 是否能被物理攻击
		bool                          bIsBeMagAttack          ; // 是否能被魔法攻击
		bool                          bIsUsingTools           ; // 是否能使用道具具
		int8                          stMagicShield           ; // 魔法盾
		float                         fSuckDamagePer          ; // 吸收伤害百分比
		int32                         stSuckDamageMax         ; // 最大的伤害吸收
		Array<int16, EBaseAttr_MaxSize> stAddBaseAttr         ; // 一级属性的加成
		Array<int16, EBaseAttr_MaxSize> stAddBaseAttrPer      ; // 一级属性的加成%
		bool                          bUseStateColour         ; // 是否使用状态颜色
		float                         fStateColourR           ; // 红 /加了状态后的人物颜色
		float                         fStateColourG           ; // 绿
		float                         fStateColourB           ; // 蓝
		float                         fChangActionTime        ; // 改变动画播放时间
		bool                          bIsChangActionTime      ; // 是否改变动画播放时间
		bool                          bIsHide                 ; // 是否隐身 
		bool                          bIsFlyAir               ; // 是否悬空              
		bool                          bIsClearDamgeStatus     ; // 是否清除有害状态
		bool                          bIsReplaceOldStatus     ; // 是否替换已有状态
		int32                         nChangeMonsterID        ; // 变身ID
		bool                          bIsAddBufferBeCSed      ; // 被暴击时加状态
		int16                         stBeCsedAddBufferMeId   ; // 被暴击时加状态Id
		int16                         stBeCsedAddBufferMeLevel; // 被暴击时加状态Level
		bool                          bIsAddDeBufferToAttacker; // 是否给攻击者增加状态
		float                         fAddDeBufferByHpPer     ; // 给攻击者加状态HP条件
		int16                         stAddDeBufferID         ; // 给攻击者增加的状态ID
		int16                         stAddDeBufferLevel      ; // 给攻击者增加的状态等级
		int32                         nSuperpositionCount     ; // 叠加的数量
		int32                         restoreType             ; // 存储类型
		int32                         nStandingEnmity         ; // 持续仇恨
		float                         fAddExpMul              ; // 经验倍率
		float                         fAddSkillExpMul         ; // 技能经验倍率
		int32                         nStatusAnim             ; // 状态动画
		bool                          bIsClearByDead          ; // 死亡后清除状态
		int16                         stActualTime            ; // 持续现实时间(小时)
		bool                          bIsRandRun              ; // 是否随机乱跑
		bool                          bIsPetSupport           ; // 是否宠物承受伤害
		bool                          bBackAttckedDispel      ; // 受到背击解除该状态
		bool                          bMoveDispel             ; // 移动解除该状态
		int16                         stChangedFightPoint        ; // 更改斗气点
		Array<float, ECD_TimeExpMulModulusCount> timeExpModulus  ; // 时间增加的基础经验因子
		float                         timeExpMul                 ; // 时间增加的基础经验前提下的倍率
		uint32                        dwAnimationAddr            ; // 动画名
		bool                          bInvincible                ; // 无敌状态
		int8                          negativeType               ; // 负面状态类型
		uint8                         damagetohp                 ; // 伤害转换到hp
		bool                          bDisableCallGraphic        ; // 是否屏蔽呼叫验证码
		uint16                        actionMapConfigId          ; // 对应的在场景id中起作用
		bool                          canCancel                  ; // 是否可以取消
		uint8                         hurtImmunity               ; // 伤害免疫

		uint8                         attackModulus           ;    // 攻击系数
		uint8                         defendModulus           ;    // 防御系数
		bool                          ifConsumeEnergy         ;    // 是否不消耗能量
		bool                          ifStatusIntonate        ;    // 是否吟唱相关状态

		uint16                      changeSkillIds[ECD_ChangeSkillMaxSize]      ;   //改变冷却时间的技能
		uint32                      changeSkillTimes[ECD_ChangeSkillMaxSize]    ;   //改变技能冷却时间

		uint8                         addEquipAttrType        ;   // 影响装备属性类型
		uint8                         addEquipAttrValuePer    ;   // 影响装备属性加成

		float                         activityMul             ;   // 活力倍数
		uint16                        reduceTax               ;   // 降低税率
		uint16                        deathDurabilityPer      ;   // 死亡装备耐久度降低
		uint16                        deathMountHPDropPer     ;   // 死亡坐骑生命减少

		int32                         addMoney                ;   // 增加金钱         
		int32                         addReputation           ;   // 增加声望
		int32                         addExploit              ;   // 增加功勋
		int32                         addHonour               ;   // 增加荣誉
		int32                         addMasterValue          ;   // 增加威望
		int32                         addBattleScore          ;   // 增加战场积分
		float                         reputationMul           ;   // 声望倍数
		float                         exploitMul              ;   // 功勋倍数
		float                         honourMul               ;   // 荣誉倍数
		float                         masterValueMul          ;   // 威望倍数
		float                         battleScoreMul          ;   // 战场积分倍数
		int32                         addHonourLimit          ;   // 增加荣誉上限

		uint8                         lapoverNum              ;   // 叠加数量上限
		uint16                        lapoverValue            ;   // 叠加值
		uint16                        lapoverMod              ;   // 叠加系数

		uint16                        breakStrike             ;   // 破甲伤害
		uint16                        stabStrike              ;   // 贯穿伤害
		uint16                        elementStrike           ;   // 元素伤害
		uint16                        toxinStrike             ;   // 毒素伤害
		uint16                        spiritStrike            ;   // 精神伤害

		uint16                        breakResist             ;   // 破甲抗性
		uint16                        stabResist              ;   // 贯穿抗性
		uint16                        elementResist           ;   // 元素抗性
		uint16                        toxinResist             ;   // 毒素抗性
		uint16                        spiritResist            ;   // 精神抗性

		int16                         addCatchPetRate         ;   // 增加宠物捕捉几率

		bool						  canRide				  ;	  // 是否能骑坐骑
		uint16						  BeDamagePerHpMax		  ;   // 被伤害后不管多少值,每次都只掉百分比生命

		bool						  canGetHonour			  ;   // 是否可以获得荣誉
		bool						  canBeGetHonour		  ;	  // 是否可以被获得荣誉

		SItemStatus() : changeDefend("SItemStatus.changeDefend"),
			changeDefendPer("SItemStatus.changedDefendPer"),
			timeExpModulus("SItemStatus.timeExpModulus")
		{ 
			memset(this, 0, sizeof(*this) ); 
			canGetHonour = true;
			canBeGetHonour = true;
		}

		bool        IsForeverStatus()
		{ return iDurationTime == ECD_DurationTimeForever; } // 是否是永久Buffer
		const char* GetStatusEffectName();
		const char* GetStatusAction();
		const char* GetAnimationName();
		bool        IsHaveContinueValueChange();
		bool		IsCanGetHonour(){return canGetHonour;}
		bool	    IsCanBeGetHonour(){return canBeGetHonour;}
	};

	struct SItemAction : public SItemCommon
	{ //玩家动作的定义
		SItemAction()
		{
			memset(this, 0, sizeof(*this) );
		}
		unsigned short ustActionID; //动作ID
		short    stType;            //动作类型（0，基本动作 1，社群动作 2，社交动作）
		short    stSinglePlayTime;  //单次播放时间
		short    stLastingPlayTime; //持续播放时间
		bool     bLastFrameRemain;  //保留最后一帧
	};

	struct SItemReel : public SItemCommon
	{ // 卷轴的定义
		enum EConstDefine
		{
			ECD_RatioMaxSize = 6,
		};

		SItemReel()
		{
			memset(this, 0, sizeof(*this) );
		}
		unsigned short skillId;      // 技能Id
		unsigned char  skillLevel;   // 技能
		unsigned char  replaceRatio[ECD_RatioMaxSize]; // 替代其他技能的几率
		unsigned char  mountTakeLevel;  // 坐骑携带等级
		unsigned char  mountLevel;      // 坐骑等级
		unsigned char  petTakeLevel;    // 宠物携带等级
		unsigned char  petLevel;        // 宠物等级
		unsigned long  costMoney;       // 花费金钱
	};

	struct SItemTask : public SItemCommon
	{
		SItemTask ()
		{ memset(this, 0, sizeof(*this) );}
	};

	enum EItemOtherType
	{
		OtherType_Unknow        ,   // 未知
		OtherType_PetIdentify   ,   // 宠物图鉴
		OtherType_ZhujiangIdentify   ,   // 主将图鉴
		OtherType_Mount				// 坐骑
	};

	struct SItemOther : public SItemCommon
	{
		SItemOther ()
		{ memset(this, 0, sizeof(*this) );}

		unsigned char   otherType;  
		unsigned short  petType  ;  // 激活宠物图鉴类型
	};

	// 一些鉴定, 转移所使用的材料
	struct SItemCheckUp : public SItemCommon
	{
		enum EConstDefine
		{
			// 物品鉴定类型
			ECD_MoveStar = 0,             // 移星道具
			ECD_Elements = 1,             // 五行鉴定符
			ECD_Suit     = 2,             // 套装材料

			// 作用效果类型
			ECD_ElementsClear   = 0,      // 清除五行元素
			ECD_ElementsCheckUp = 1,      // 鉴定五行元素
			ECD_ElementsMove    = 2,      // 五行转移石头

			// 套装
			ECD_SkillSuitLevel     = 0,   // 技能套装装备升级
			ECD_SkillSuitChange    = 1,   // 技能套装装备转换
			ECD_SkillSuitAttribute = 2,   // 洗技能套装属性的道具
			ECD_ElementsSuitLevel  = 3,   // 五行提纯道具
			ECD_ElementsSuitChange = 4,   // 五行转化道具
		};

		SItemCheckUp ()
		{ memset( this, 0, sizeof( SItemCheckUp ) ); }

		//bool bExclusive;        // 是否可叠加
		short stCheckUpType;    // 物品鉴定类型
		short stEffectType;     // 作用效果类型
		short stEquipLevel;     // 对应的装备等级
		short stEffectLevel;    // 作用等级 ( 如果是技能套装升级材料, 这个是1-5个等级 )


		int nValue1;            // 预留字段1  如果是套装材料升级材料, 这个值填的是强化套装材料的强化对应的男装备ID  如果是ECD_ElementsSuitLevel材料, 这个值是对应的五行属性(金木水火土1-5, 如果都万能鉴定, 这个值是 ItemElements_End = 6 ) 
		int nValue2;            // 预留字段2  如果是套装材料升级材料, 这个值填的是强化套装材料的强化对应的女装备ID
	};

	struct SItemRealAward : public SItemCommon
	{
		SItemRealAward ()
		{ memset( this, 0, sizeof( SItemRealAward ) );}

	};

	// 专用物品
	struct SItemSpecial : public SItemCommon
	{
		SItemSpecial()
		{
			memset( this, 0, sizeof( SItemSpecial ) );
		}

		enum EConstDefine
		{
			ECD_MarriageCard = 1,       // 结婚喜帖
			ECD_UnknowEquip	 = 2,       // 未鉴定装备
		};

		unsigned char uchSpecialType;   // 类型
		//bool bExclusive;                // 是否可叠加
	};

	// 法宝
	struct SItemTalisman : public SItemCommon
	{
		enum EConstDefine
		{

		};

		SItemTalisman()
		{
			memset( this, 0, sizeof( SItemTalisman ) );
		}

		int    iModelID;                                          // 模型ID

		int8   iSexReq;                                           // 性别需求
		Array< bool, EArmType_MaxSize> arrayEquipArmsReq;         // 职业需求
		int16  iEquipLevelReq;                                    // 级别需求

		uint16 skillId;                                           // 技能Id
		uint16 skillLevel;                                        // 技能等级

		uint32 daoxing          ; // 道行限制
		uint16 poolId           ; // 法宝随机属性池ID
		uint32 nimbusMax        ; // 灵气最大值
		uint16 nimbusRestore    ; // 灵气回复
	};

	struct SItemPetEquip : public SItemCommon
	{
		//副将装备
		SItemPetEquip()
		{
			memset( this, 0, sizeof( SItemPetEquip ) );
		}

		//副将装备只加一级属性
		int						Strength;//力量
		int						Agility;//敏捷
		int						Stamina;//耐力
		int						Intelligence;//灵力

		uint16					iEquipLevelReq;//等级需求

		int						iPos;//装备的位置
	};

	struct SItemGuild : public SItemCommon
	{
		SItemGuild ()
		{ memset( this, 0, sizeof( SItemGuild ) );}

		enum EConstDefine
		{
			ECD_GuildBox = 0,   // 公会的压镖军资
			ECD_ClearRupture,   // 清除敌对令牌
			ECD_MemberCall,     // 公会召集令牌
		};

		unsigned char uchType;      // 公会物品的类型

		unsigned int nValue1;       // 预留的Value
		unsigned int nValue2;       // 预留的Value
	};

	struct SItemTreasureBox : public SItemCommon        // 宝箱类型
	{
		SItemTreasureBox ()
		{ memset( this, 0, sizeof( SItemTreasureBox ) );}

		enum TreasureBoxDefine
		{
			BoxType_Luck = 0,   // 摇奖的箱子
			BoxType_Receive,    // 领奖的箱子
			BoxType_BoxKey,     // 箱子的钥匙
		};

		uint8  uchBoxType;    // 类型
		uint8  uchLevel;      // 等级
		uint16 ustCorrItemID; // 对应的ID( 箱子对应钥匙, 钥匙则对应箱子, 没有则不用填 )
		uint16 ustNewItemID;  // 使用后更换到新的id
	};

	struct SItemCard : public SItemCommon
	{
	};

	enum EGemType
	{
		egem_normal = 0,  // 普通宝石
		egem_red       ,  // 红宝石
		egem_yellow    ,  // 黄宝石
		egem_blue      ,  // 蓝宝石
		egem_green     ,  // 绿宝石
		egem_special   ,  // 特殊宝石
		egem_max   
	};

	// 可镶嵌的宝石
	struct SItemGem : public SItemCommon
	{
		enum EConstDefine
		{
			CD_TypeCount  = 2,
			CD_ValueCount = 2,
		};

		SItemGem()
		{
			gemType          = 0;   
			gemLevel         = 0;    
			effectEquipPart  = 0;   
			preGemId         = 0;   
			preGemType       = 0;  
			useCostMoney     = 0;
			type[0]          = 0;
			type[1]          = 0;
		}

		uint8          gemType             ; // 宝石类型
		uint8          gemLevel            ; // 宝石级别
		uint32         effectEquipPart     ; // 作用部位装备
		uint16         preGemId            ; // 前置激活宝石Id
		uint8          preGemType          ; // 前置激活宝石类型
		int32          useCostMoney        ; // 使用花费
		int16          levelLimit          ; // 作用对象等级限制
		uint16         type[CD_TypeCount]  ;    
		CustomValue    value[CD_ValueCount];
		uint16		   downGradeID;			 //镶嵌失败宝石降级对应的低一级的宝石ID

		bool CanEquipPart( uint32 equipPart ) // 可否作用在此装备位
		{ return effectEquipPart == 0 ? true : _HAS_FLAG( effectEquipPart, equipPart ); }
	};

	enum EMaterialType
	{
		ematerial_metal   = 0, // 金属
		ematerial_wood       , // 木头
		ematerial_pelage     , // 毛皮
		ematerial_starlevel  , // 升星材料
		ematerial_compound   , // 合成辅助
		ematerial_identify   , // 鉴定材料
		ematerial_reidentify , // 鉴定回炉
		ematerial_stiletto   , // 装备打孔材料
		ematerial_gemtakedown, // 宝石拆卸材料
		ematerial_gemlevelup , // 宝石升级材料
		ematerial_soulstamp  , // 灵魂铭刻材料
		ematerial_openlight  , // 装备鎏金材料
		ematerial_reopenlight, // 装备鎏金回炉材料
		ematerial_maintain   , // 装备保值材料
		ematerial_maintacross, // 装备跨级保值材料
		ematerial_charm      , // 符文吸蓝材料
		ematerial_inlay		 , // 镶嵌符
		ematerial_rateboll   , // 几率宝珠
		ematerial_gemcomposerune, // 宝石合成符
		ematerial_zhujianguprune, // 主将合成提升概率材料
		ematerial_mountrune,	// 坐骑强化材料
		ematerial_max        
	};

	struct SCreateMaterial : public SItemCommon
	{
		int16  stMaterialType   ; // 材料类型
		float  fAddIntensifyRate[18]; // 增加强化几率
		int16  useLevel         ; // 人物使用等级
		int16  levelLowLimit    ; // 作用对象的等级下限
		int16  levelUpLimit     ; // 作用对象的等级上限
		int16  starLevelLimit	; // 星级要求
		int16  useCostMoney     ; // 使用花费
		uint32 effectEquipPart  ; // 作用部位装备
		int16  equipQuality     ; // 装备品质要求
		uint32 nValue           ; // 复用数据结构 打孔材料做顺序用

		SCreateMaterial()
		{ 
			stMaterialType    = ematerial_max;
			//fAddIntensifyRate = 0;
			memset(fAddIntensifyRate, 0, 18*sizeof(float));
			levelLowLimit     = 0;
			levelUpLimit      = 0;
			starLevelLimit    = 0;
			starLevelLimit    = 0;
			effectEquipPart   = 0;
			nValue            = 0;
		}

		bool CanEquipPart( uint32 equipPart ) // 可否作用在此装备位
		{ return effectEquipPart == 0 ? true : _HAS_FLAG( effectEquipPart, equipPart ); }
	};

	struct SItemCreateItemRule : public SItemCommon
	{ //合成配方
		struct SMaterial
		{   
			unsigned short ustItemID; //需求原料
			unsigned short ustCount;  //需求原料个数
		};

		SItemCreateItemRule() :material("[ItemDetail.h]SItemCreateItemRule.material")
		{
			ustTargetItemID = InvalidLogicNumber;
			ustTargetItemID1 = InvalidLogicNumber;
			ustTargetItemID2 = InvalidLogicNumber;
		}
		//合成目标
		unsigned short ustTargetItemID;
		unsigned short ustTargetItemID1;
		unsigned short ustTargetItemID2;

		SItemCommon* pItemTarget;
		SItemCommon* pItemTarget1;
		SItemCommon* pItemTarget2;

		int iMaterialNum;
		Array<SMaterial, 4> material; //原料

		//合成成功率
		//float fCreateSuccRate;        
		//精度1/1000
		int iCreateSuccRate;
		int iCreateSuccRate1;
		int iCreateSuccRate2;

		bool bIntensify;
		int  nNeedMenoy;
		int  nSingTime;
		int  nNeedEnergy;

		unsigned char ucCompoundType; // 生产类型
	};

	struct SItemCrystal : public SItemCommon
	{
		//unsigned short usCrystalId;
		//水晶等级
		unsigned short usCrystalLevel;

	};

	struct SProfession
	{
		SProfession()
		{
			memset(this, 0, sizeof(*this) );
		}
		const char* GetName();
		const char* GetDesc();
		//std::string    szName;
		//std::string    szDesc;
		DWORD    dwNameAddr;
		DWORD    dwDescAddr;
		short    stType;
	};

	enum EMonsterVisualType
	{
		EMVT_Normal,       // 所有人可见
		EMVT_MasterVisual, // 主人可见
	};

	enum EMonsterRewardType
	{
		EMRT_None,
		EMRT_CashMoney,
		EMRT_Reputation,
		EMRT_MaxSize
	};

	// 在XML中对应的字段含义
	/*<!--
	<> 包含的字段表示是默认值, 或者是 地形名.monster表中有的字段, 些处忽略

	MonsterID|怪物id,  MonsterPrefix|前缀,  MonsterName|怪物名, ModelID|模型id,  MonsterSound|声音, MonsterType|类型, BodyModify|体型修正缩放, BodyLengthSize|体型大小,
	MonsterLv|等级, MonsterExp|经验值, PhyAtk|物理攻击, MagicAtk|法术攻击, PhyDef|物理防御, MagicDef|法术防御, Critical|暴击率, CriticalIntensity|暴击伤害,
	Tenacity|韧性, BackStrike|背击伤害, BackStrikeResist|背击抗性, BreakStrike|破甲, BreakResist|破甲抗性, StabStrike|贯穿伤害, StabResist|贯穿抗性,
	ElementStrike|元素伤害, ElementResist|元素抗性, ToxinStrike|毒素伤害, ToxinResist|毒素抗性,  SpiritStrike|精神伤害, SpiritResist|精神抗性,
	MaxMP|最值法力值, RecoverMP|法力恢复速度, MaxHP|最大生命值, RecoverHP|生命恢复速度, Hit|精确值(基础), Dodge|躲避率(基础), AtkSpeed|攻击速度, EyeShot|视野,
	FightShot|战斗视野, AttackPhysicsMod|物攻系数, AttackMagicMod|法攻系数, DefendPhysicsMod|物防系数, DefendMagicMod|法防系数, AttackFloatMin|攻击最小系数,
	AttackFloatMax|攻击最大系数, ChaseTime|追击时间, MoveSpeed|移动速度, UseSkill1|可用技能1, UseSkill2|可用技能2, UseSkill3|可用技能3, 
	Skill1Lv|技能1等级, Skill2Lv|技能2等级, Skill3Lv|技能3等级, ChanceOfSkill1|技能1使用概率, ChanceOfSkill2|技能2使用概率, ChanceOfSkill3|技能3使用概率, 
	MinDropMoney|掉落金钱最小值, MaxDropMoney|掉落金钱最大值, DropItemRate|物品掉落倍率, IfInitiative|是否主动怪, MonsterSkin|怪物皮肤, MonsterAlpha|怪物透明度,
	<<ReviveTime|复活时间>>, IfDisappear|是否消失, DisappearTime|消失时间, DeathScript|默认死亡脚本, AIScript|默认AI脚本, MonsterWeaponSoundPrefix|怪物武器音效前缀,
	MonsterArmorSoundPrefix|怪物防具音效前缀, RunStep|怪物奔跑步长, WalkStep|怪物行走步长, IfHalfLengthMonster|是否上下半身怪物, IfFourFeetMonster|是否四足怪物,
	MonsterSide|所属阵营, EnemityRate|仇恨比率, InitialEnemity|视野触发仇恨, ResistUnmovable|不能移动被抵抗, ResistUnatkable|不能攻击被抵抗, ResistUncastable|不能施法被抵抗,
	ResistUnitemusable|不能用道具被抵抗, ExtraSkillExp|额外技能经验, MaxActArea|最大活动范围, ChangePassive|战斗中变为被动怪, PassiveTime|战斗结束被动持续秒数,
	BaseEnmityRange|基础仇恨保持范围, IdleMoveSpeed|空闲移动速度, Citymonster|城市怪(不能被守城方攻击), Citydefmonster|城市防守怪(只攻击攻城的), MonsterTitle|怪物称号,
	FrontFoot|前脚或右脚, BackFoot|后脚或左脚, NeedQuest|关联的任务, MonsterReputation|增加声望, MonsterExploit|增加功勋, RewardFriendly|奖励好友度, Daoxing|道行,
	RewardDaoxing|奖励道行, VisualType|可视类型, IdleMoveRate|控制空闲移动的频率值(万分之几),  BornProtectTime|出生保护时间, RestoreSpaceTime|回血间隔时间,
	CashMoney|可交易金钱, RewardStatusID奖励状态ID, RewardMulType|倍数奖励类型, RewardMulValue|奖励倍数, IsFindParth|是否开启寻路, IsDynamicBlock|是否参与动态阻挡,
	CatchPetID|对应宠物ID, CatchBaseRate|捕捉基础几率, PetQuality|产生的宠物品质, Phyle|种族, FiveElements|五行, GroupID|怪物组ID
	-->*/
	enum SMonsterDropType
	{
		SMDT_First = 1,
		SMDT_DPS   = 2,
	};

	struct SMonster 
	{ //怪物
		enum EConstDefine
		{
			MONSTER_SKILL_COUNT = 3,
		};

		int   iMonsterContainerIndex; // 容器索引
		int   stMonsterId;            // Id   副本怪时候,110012  副本只会添1100 , 12是等级,要根据相应玩家等级来计算
		DWORD dwNameAddr;             // 怪物名地址
		DWORD dwNamePrefix;           // 怪物名前缀地址
		int   iModelID;               // 模型ID
		DWORD dwCreatureSoundAddr;    // 怪物声音地址
		DWORD dwSkinAddr;             // 怪物皮肤地址
		DWORD dwWeaponSoundAddr;      // 怪物武器音效前缀地址
		DWORD dwArmourSoundAddr;      // 怪物防具音效前缀地址
		uint8 stProfession;           // 怪物职业
		uint8 stMonsterType;          // 怪物类型
		float fBodyLengthSize;        // 怪物体型大小
		float fBodySize;              // 怪物体型修正缩放【注意】
		float fAlpha;                 // 怪物透明度
		short stLevel;                // 级别
		int   nRewardExp;             // 拥有的经验值(给玩家)
		int   nRewardReputation;      // 拥有的声望值(给玩家)
		int   nRewardExploit;         // 拥有的功勋值
		int   nRewardFriendly;        // 奖励好友度
		int   nRewardDaoxing;         // 奖励道行
		int   nHPMax;                 // 最大HP
		short stMPMax;                // 最大MP
		short stHPRestore;            // HP恢复速度
		short stMPRestore;            // MP恢复速度
		short stExact;                // 精确
		short stDodge;                // 回避率
		short stAttackRate;           // 攻击速度
		float fPhysicAtt;             // 物攻
		float fMagicAtt;              // 法攻
		float fPhysicDef;             // 物防
		float fMagicDef;              // 法防

		float  critical             ; // 暴击率
		uint16 criticalIntensity    ; // 暴击伤害
		uint16 tenacity             ; // 韧性
		uint16 backStrike           ; // 背击伤害
		uint16 backStrikeResist     ; // 背击抗性
		uint16 breakStrike          ; // 破甲伤害
		uint16 stabStrike           ; // 贯穿伤害
		uint16 elementStrike        ; // 元素伤害
		uint16 toxinStrike          ; // 毒素伤害
		uint16 spiritStrike         ; // 精神伤害
		uint16 breakResist          ; // 破甲抗性
		uint16 stabResist           ; // 贯穿抗性
		uint16 elementResist        ; // 元素抗性
		uint16 toxinResist          ; // 毒素抗性
		uint16 spiritResist         ; // 精神抗性  

		// 攻击系数
		float fAttackPhysicsMod;
		float fAttackMagicMod;

		// 防御系数
		float fDefendPhysicsMod;
		float fDefendMagicMod;

		short nAttackFloatMin ;     // 攻击最小系数
		short nAttackFloatMax ;     // 攻击最大系数 
		short stView;               // 视野
		short stFightView;          // 战斗视野
		DWORD dwCatchTime;          // 追击时间
		float fMoveSpeed;           // 移动速度
		float fIdleMoveSpeed;       // 空闲时移动速度
		float fMovingStep;          // 行走步长
		float fRunStep;             // 跑步步长
		Array<uint16,MONSTER_SKILL_COUNT> iSkillID;     // 可能使用的技能
		Array<uint8, MONSTER_SKILL_COUNT> stSkillLevel; // 可使用技能的等级
		Array<short, MONSTER_SKILL_COUNT> stSkillRate;  // 可使用技能的使用概率
		short  stDropMinMoney;        // 掉落金钱(min)
		short  stDropMaxMoney;        // 掉落金钱(max)
		float  fItemDropMultipleRate; // 物品掉落倍率
		int    nReliveTime;           // 复活时间
		DWORD  dwDeadScriptAddr;      // 怪物死亡脚本地址
		DWORD  dwAILuaScriptAddr;     // 怪物AI脚本地址
		int    nIsInitiative;         // 是否主动怪
		uint32 nRandMoveRange;        // 怪物随机活动范围
		int    nIsHaveTwoHalfBody;    // 是否上下半身怪物
		int    nIsHaveFourFoot;       // 是否四足怪物
		bool   bIsDisappear;          // 怪物是否消失
		DWORD  dwDisappearTime;       // 怪物消失时间
		int    nEnmityRate;           // 仇恨比率
		int    nEnmity;               // 仇恨
		int    nDaoxing;              // 道行
		int    nResistMove;           // 抵抗1
		int    nResistAtt;            // 抵抗2
		int    nResistMagic;          // 抵抗3
		int    nResistTools;          // 抵抗4
		int    nSuperfluitySkillExp;  // 额外技能经验   备注:字段复用 如果怪物为采集怪 此字段为扣除活力值
		int    nMaxRange;             // 最大活动范围
		int    nChangePassive;        // 战斗时是否变为被动怪
		int    nPassiveTime;          // 被动持续时间
		int    nBaseEnmityRange;      // 基础仇恨保持区域
		int    nMonsterSide;          // 所属阵营
		bool   bIsCityMonster;        // 是否城市怪物
		bool   bIsCityDefMonster;     // 是否防守城市怪物
		DWORD  strTitleAddress;       // 称号
		DWORD  dwFrontFootPrintAddr;  // 前脚或右脚
		DWORD  dwBackFootPrintAddr;   // 后脚或左脚
		int    nRelativeQuest;        // 关联的任务
		uint8  visualType;            // 可视类型
		uint16 nIdleMoveRate;         // 控制空闲移动的频率值 万分之一
		DWORD  dwBornProtectTime;     // 出生保护时间
		DWORD  dwRestoreSpaceTime;    // 回血间隔时间

		//江湖请柬状态相关字段
		uint16 nCashMoney;           // 可交易金钱
		uint16 nRewardStatusID;      // 奖励状态ID 江湖请柬 ID 3173
		uint16 nRewardMulType ;      // 倍数奖励类型
		uint16 nRewardMulValue;      // 奖励倍数

		// 寻路相关配置
		bool	blIsFindParth;		// 是否开启寻路
		bool	blIsDynamicBlock;	// 是否参与动态阻挡

		// 宠物相关
		int     nCatchPetID;         // 对应宠物ID
		int16   nCatchBaseRate;      // 捕捉基础几率 万分之一
		int8    nPetQuality;         // 产生的宠物品质    
		uint8   phyle  ;             // 种族
		uint8   element;             // 五行

		uint16	nGroupID;			// 怪物组ID

		uint16  nDropType;			// 掉落类型

		const char* GetName();
		const char* GetNamePrefix();
		const char* GetCreatureSound();
		const char* GetSkin();
		const char* GetDeadScript();
		const char* GetAILuaScript();
		const char* GetWeaponSound();
		const char* GetArmourSound();
		const char* GetFrontFootPrintPath(); // 前脚印
		const char* GetBackFootPrintPath();  // 后脚印
		const char* GetTitle();

		SMonster() : iSkillID("[ItemDetail.h]SMonster.iSkillID"), stSkillLevel("[ItemDetail.h]SMonster.stSkillLevel"), stSkillRate("[ItemDetail.h]SMonster.stSkillRate")
		{ memset(this, 0, sizeof(*this) ); }
	};

	struct SPetMonster : public SMonster
	{
		enum EPetMonsterDefine
		{
			EPet_LvRealizeCount       = 10,
			EPet_RandSkillCount       = 10, // 随机技能数
			EPet_ManualSkillCount     = 2 , // 主动技能数
			EPet_AutoSkillCount       = 4 , // 被动技能数
			EPet_BabyListIDCount      = 5 , // 宠物繁殖下一代ID
			EPet_DropItemIDCount      = 10,
		};

		SPetMonster()
		{ memset(this, 0, sizeof(*this)); }

		int            iPetContainerIndex;           // 容器索引
		int            itemId ;                      // 对应物品ID
		DWORD          dwPetDescAddr;                // 宠物简介地址
		DWORD          dwPetBornDescAddr;            // 宠物出没地点
		DWORD          dwNameColor;                  // 宠物名称颜色
		int            petType;                      // 宠物类型
		DWORD          dwPetTypeNameAddr;            // 宠物类型名称
		unsigned char  catchQuality;                 // 捕捉品质 金银铜
		unsigned char  catchLevel;                   // 捕捉等级
		unsigned char  takeLevel;                    // 携带等级
		int            babyId;                       // 宝宝ID
		unsigned char  aberranceLevel;               // 变异等级
		bool           bIsAberrance;                 // 是否为变异宠物
		bool           bIsBaby;                      // 是否宝宝
		unsigned char  food;                         // 食物
		int            duration;                     // 寿命
		unsigned char  attackType;                   // 攻击类型
		int            regenerateTime;               // 死后重生时间
		DWORD		   identifyTotal;				 // 鉴定次数累计

		int            growthRate  [EPetGrowth_Count];      // 成长率
		int            aptitudeAttr[EBaseAttr_MaxSize];     // 初始资质属性

		unsigned char  characterizeRate[EPetChar_Count];    // 性格

		unsigned char  skillNumControl;     // 技能控制数
		unsigned short talentSkillId;       // 天赋技能
		unsigned char  lvRealizeSkill   [EPet_LvRealizeCount];  // 等级领悟技能
		unsigned short manualSkillId    [EPet_RandSkillCount];  // 领悟主动技能ID
		unsigned short manualSkillRate  [EPet_RandSkillCount];  // 领悟主动技能几率
		unsigned short autoSkillId      [EPet_RandSkillCount];  // 领悟被动技能ID
		unsigned short autoSkillRate    [EPet_RandSkillCount];  // 领悟被动技能几率

		int            babyListId       [EPet_BabyListIDCount];
		int            babyListIdRate   [EPet_BabyListIDCount];

		unsigned short dropItemIds      [EPet_DropItemIDCount];

		const char* GetPetDesc();
		const char* GetPetBornDesc();
		const char* GetPetTypeName();

	};

	struct STraffic
	{
		STraffic()
		{
			memset(this, 0, sizeof(*this));
			nextTrafficId = -1;
		}

		const char* GetName(); // 名称

		int   nID          ; // ID编号
		DWORD dwNameAddr   ; // 名称地址
		int   nDromeID     ; // 坐骑编号
		int   nMapID       ; // 地图ID
		int   nRouteID     ; // 路线ID
		int32 nextTrafficId; // 下一个Traffic
	};

	enum EMountQuality
	{
		EMQ_Ordinary    =   1,  //普通马
		EMQ_Good        =   2,  //优良马
		EMQ_Excellent   =   3,  //精品马
		EMQ_Variation   =   4,  //变异马
	};

	//坐骑
	struct SDrome
	{
		enum EConstDefine
		{
			DCD_SELFSKILLIDCOUNT    = 10,
			DCD_MASTERSKILLIDCOUNT  = 10,
			DCD_MASTERUSESKILLCOUNT = 10,
		};

		SDrome()
		{
			memset(this, 0, sizeof(*this));
		}
		const char* GetName();                    // 名称
		const char* GetModelPath();               // 模型文件路径
		const char* GetSkinName();                // 获取皮肤名称
		const char* GetMountEffectPath();         // 上坐骑的特效路径
		const char* GetDisMountEffectPath();      // 下坐骑的特效路径
		const char* GetRunSoundOfLeftFootPath();  // 左脚脚步声
		const char* GetRunSoundOfRightFootPath(); // 右脚脚步声
		const char* GetNeightSoundPath();         // 原地叫声
		const char* GetFrontFootPrintPath();      // 前脚印
		const char* GetBackFootPrintPath();       // 后脚印
		int         GetMountCameraHeight() { return nCameraHeight; } // 相机抬高高度
		const char* GetMountAction( int Index );  // 骑手动作表
		const char* GetHeadPicPath();             // 头像路径

		short stId;                      // Id编号
		short stIndex;                   // 索引
		DWORD dwNameAddr;                // 名称地址
		DWORD dwModelAddr;               // 模型文件地址
		DWORD dwSkinAddr;                // 皮肤地址
		DWORD dwMountEffectAddr;         // 上坐骑的特效路径
		DWORD dwDisMountEffectAddr;      // 下坐骑的特效路径
		DWORD dwRunSoundOfLeftFootAddr;  // 左脚脚步声
		DWORD dwRunSoundOfRightFootAddr; // 右脚脚步声
		DWORD dwNeightSoundAddr;         // 原地叫声
		DWORD dwFrontFootPrintAddr;      // 前脚印
		DWORD dwBackFootPrintAddr;       // 后脚印
		Array<DWORD, MountMaxActionNum>  dwMountAction;

		int   nAddStatusID;              // 附加的状态ID
		short stOperaType;               // 操作类型
		short stType;                    // 类型
		short stCarry;                   // 运载能力
		short shMoveType;                // 移动类型
		float fFlyHeight;                // 飞行高度
		float fInertia;                  // 惯性
		float fSpeed;                    // 速度
		float fRunningStep;              // Run的步长
		float fWalkingStep;              // Walk的步长
		float fJumpingHeight;            // 跳跃高度
		short stMaxRange;                // 最大活动范围
		float fDromeScaleCorrect;        // 坐骑体型修正
		float fRiderScaleCorrect;        // 骑手体型修正
		//float fAccelerate;             // 加速度
		//DWORD dwFireTime;              // 加速持续时间
		DWORD dwMaxLifeTime;             // 最大使用时间
		DWORD dwJumpAnimTime;            // 跳跃动画播放时间
		DWORD dwDropAnimTime;            // 下落动画播放时间
		DWORD dwFallToTheGroundRunTime;  // 下落跑动画播放时间
		float fJumpSpeed;                // 起跳速度
		float fDropSpeed;                // 下落速度
		DWORD dwBlendJumpTime;           // 起跳过渡时间
		int   nCameraHeight;             // 相机抬高高度
		DWORD dwHeadPicAddr;             // 头像地址

		unsigned char  takeLevel;            // 携带等级
		unsigned char  quality;              // 初始品质
		float          growMin;              // 成长率最小值
		float          growMax;              // 成长率最大值
		float          baseSum;              // 初始基本属性总和
		float          baseMin[EBaseAttr_MaxSize]; // 初始基本5个属性最小值
		float          baseMax[EBaseAttr_MaxSize]; // 初始基本5个属性最大值
		float          addSum;               // 初始资质属性总和
		float          addMin[EBaseAttr_MaxSize];  // 初始资质5个属性最小值
		float          addMax[EBaseAttr_MaxSize];  // 初始资质5个属性最大值
		unsigned short sawyMin;              // 悟性最小值
		unsigned short sawyMax;              // 悟性最大值
		unsigned short selfSpeedSkillId;     // 坐骑速度技能
		unsigned char  selfSkillNum;         // 自身技能个数
		unsigned char  selfSkillRate;        // 产生这几个技能的个数
		unsigned short selfSkillId[DCD_SELFSKILLIDCOUNT];         // 可以随机的坐骑技能
		unsigned char  masterSkillNum;                            // 主人被动触发技能个数
		unsigned char  masterSkillRate;                           // 产生这几个技能的个数
		unsigned short masterSkillId[DCD_MASTERSKILLIDCOUNT];     // 可以随机的坐骑主人被动触发技能
		unsigned char  masterUseSkillNum;                         // 主人主动触发技能个数
		unsigned char  masterUseSkillRate;                        // 产生这几个技能的个数
		unsigned short masterUseSKillId[DCD_MASTERUSESKILLCOUNT]; // 可以随机的坐骑主人主动触发技能
		Array< unsigned short, 4 > arrayProbability;              // 洗点的4种品质的概率
		Array< unsigned short, 4 > arrayMountID;                  // 洗点对应得到的马的新的id

		uint16         nextGeneration;      //下一代坐骑
		uint16		   modelID[SMountItem::MICD_MountMaxLevel + 1];	   //模型ID
	};

	struct SUpBaseAttr
	{
		SUpBaseAttr() : Str("[ItemDetail.h]SUpBaseAttr.Str"),
			Agi("[ItemDetail.h]SUpBaseAttr.Agi"),
			Con("[ItemDetail.h]SUpBaseAttr.Con"),
			Mag("[ItemDetail.h]SUpBaseAttr.Mag"),
			Int("[ItemDetail.h]SUpBaseAttr.Int"),
			Charm("[ItemDetail.h]SUpBaseAttr.Charm")
		{
			memset(this, 0, sizeof(*this) );
		}
		short sLevel;        
		Array<short, EArmType_MaxSize>    Str;
		Array<short, EArmType_MaxSize>    Agi;
		Array<short, EArmType_MaxSize>    Con;
		Array<short, EArmType_MaxSize>    Mag;
		Array<short, EArmType_MaxSize>    Int;
		Array<short, EArmType_MaxSize>    Charm;
		short stSkillPoint;
	};

	struct TagEquipRequest
	{
		bool    bSex;
		bool    bProfession;
		bool    bLevel;
		bool    bStr; // 力量        
		bool    bCons;// 体质        
		bool    bAgi; // 敏捷
		bool    bInt; // 智力
		bool    bMag; // 魔法        
		bool    bCha; // 魅力
	};

	struct SRandAttribute
	{
		enum EConstDefine
		{
			CD_TypeCount  = 2,
			CD_ValueCount = 2,
		};

		SRandAttribute()
		{
			memset(this, 0, sizeof(*this) );
		}

		unsigned short id;
		short          level;        
		unsigned short type[CD_TypeCount];
		CustomValue    value[CD_ValueCount];
	};

	struct SEquipQualityIntensity
	{
		SEquipQualityIntensity()
		{
			ZeroMemory( this, sizeof(*this) );
		}

		uint8	nQuality;
		uint32	nColor;
		uint16	nIntensity;
	};

	enum eBulk
	{
		eBulk_Small = 0,
		eBulk_Normal,
		eBulk_Big
	};

	struct SItemNew
	{
		SItemNew()
		{
			memset(this, 0, sizeof(*this) );
		}
		float fHitMod;
		short stModelID;
		//DWORD dwIconFileName;
		//char cIconFileName[MAX_PATH];
		short stAttSpeed;
		float fAttRange;
		int nCost;
		short stIconId;
	};

	struct SCreatItemMod
	{
		SCreatItemMod()
		{
			memset(this, 0, sizeof(*this) );
		}

		unsigned short ustLevel;
		bool  bIsWeapon;
		bool  bIsArmour;
		short stItemType;
		short stItemSize;    
		std::vector <SItemNew*> vtItemNew;
	};

	struct sIcon
	{
		short stIconId;
		char sIconFile[MAX_PATH];
		//Array<char, MAX_PATH>    sIconFile;
	};

	struct ReputeStruct
	{
		int        usReputeID;
		std::string szReputeName;
		std::string szReputeExp;
		//增加一级属性
		Array< short, EBaseAttr_MaxSize>    stReputeBattr;
		int        usReputeFlag;
		bool    bInUsing;
	};

	enum ECreatureSound
	{
		CreatureSound_Idle    = 0 ,
		CreatureSound_Attack    ,
		CreatureSound_BeHit     ,
		CreatureSound_Dead      ,
		CreatureSound_Max
	};

	struct SCreatureSound
	{
		const char* GetName();
		DWORD dwCreatureNameAddr;
		Array< int, CreatureSound_Max > SoundNum;
	};

	//added by junyi.chen begin
	struct RandAttr
	{
		unsigned short	usID;
		unsigned short	usType;
	};


	//////////////////////////////////////////////////////////////////////////

	static char* (g_szWeaponType[]) = 
	{
		"Combat"  , // 徒手
		"Warrior" , // 战士
		"Mage"    , // 法师
		"Taoist"  , // 道士
		"Assassin", // 刺客
		"Hunter"  , // 猎人
		"Sniper"  , // 火枪
		"Shield"  , // 盾牌
		"Flag"    , // 旗子
	};

	static char* (g_szItemType[]) =
	{
		"restore"       ,
		"weapon"        ,
		"armour"        ,
		"skill"         ,
		"status"        ,
		"action"        ,
		"material"      ,
		"gem"           ,
		"createitemrule",
		"task"          ,
		"other"         ,
		"reel"          ,
		"treasurebox"   ,
		"checkup"       ,
		"realaward"     ,
		"guilditem"     ,
		"special"       ,
		"talisman"		,
		"petequip"		,
	};

	// 部位
	static char *(g_szCanEquip[])=
	{
		"Helmet"            , // 头盔
		"Armour"            , // 铠甲
		"Glove"             , // 护手
		"Shoe"              , // 鞋子
		"Weapon"            , // 主武器
		"WeaponMinor"       , // 副武器
		"Badge"             , // 徽章
		"Ring1"             , // 戒指1
		"Ring2"             , // 戒指2
		"Bangle1"           , // 手镯1
		"Bangle2"           , // 手镯2
		//    "Manteau"           , // 披风
		"Shoulder"          , // 肩甲
		"Necklace"          , // 项链
		"Sash"              , // 腰带
		"LeaderCard"        , // 掌门卡
		"Amulet"            , // 护身符
		"AecorativeGoods"   , // 装饰的物品
		"AecorativeClothing", // 装饰的衣服
		"Trousers"			, // 裤子
	};

	static char*(g_szTargetString[])=
	{
		"target_no"          , // 无目标
		"target_myself"      , // 我 （只对自己）
		"target_friend"      , // 朋友（只对队友）    
		"target_normalplayer", // 普通玩家（所有玩家包括自己除了敌人）
		"target_enemy"       , // 敌人（只能对敌人）
		"target_dead"        , // 死亡目标（只对死人）
		"target_herb"        , // 目标草药
		"target_mine"        , // 目标矿
		"target_wood"        , // 目标木头
		"target_treasure"    , // 目标宝箱
		"target_pet"         , // 目标PET
		"target_all"         , // 所有人都可以
		"target_team"        , // 队伍目标
		"target_mount"       , // 目标坐骑
		"target_insect"      , // 目标昆虫
		"target_guild"       , // 公会
		"target_campforce"   , // 同阵营势力
	};

	static char*(g_szPassiveSkillTargetString[])=
	{
		"PassiveSkillTarget_Self"            , // 作用自己的被动技能
		"PassiveSkillTarget_AllPet"          , // 作用所有宠物的技能
		"PassiveSkillTarget_TargetPet"       , // 作用目标宠物的技能
		"PassiveSkillTarget_SelfAndAllPet"   , // 作用自己和所有宠物的技能
		"PassiveSkillTarget_SelfAndTargetPet", // 作用自己和目标宠物的技能
	};

	static char*(g_szMoveTypeString[])=
	{
		"movetype_twofooted" , // 双足移动
		"movetype_fourfooted", // 四足移动
		"movetype_fly"       , // 飞行移动
		"movetype_reptile"   , // 爬行移动
		"movetype_drive"     , // 驾驶移动
		"movetype_twowheel"  , // 两轮移动
		"movetype_fourwheel" , // 四轮移动
	};

	static char*(g_szEffectCenter[])=
	{
		"center_no"        , // 没有持续性效果
		"center_metotarget", // 以自己到敌人
		"center_me"        , // 以自己当前位置为中心
		"center_target"    , // 以目标位置为中心
	};

	static char*(g_szEquipType[])=
	{
		"Helmet"            , // 头盔
		"Armour"            , // 铠甲
		"Glove"             , // 护手
		"Shoe"              , // 鞋子
		"Weapon"            , // 主武器
		"WeaponMinor"       , // 副武器
		"Badge"             , // 徽章
		"Ring"              , // 戒指
		"Bangle"            , // 手镯
		//    "Manteau"           , // 披风
		"Shoulder"          , // 肩甲
		"Necklace"          , // 项链
		"Sash"              , // 腰带
		"LeaderCard"        , // 掌门卡
		"Amulet"            , // 护身符
		"AecorativeGoods"   , // 装饰的物品
		"AecorativeClothing", // 装饰的衣服
		"Trousers"			, // 裤子
	};

	static char* (g_szSkillType[])=
	{
		"skilltype_action",    // 在动作播放结束后结算的，技能
		"skilltype_magic_hit", // 在动作播放结束后结算，释放出一个法术组件
		"skilltype_magic_npc", // 在动作播放结束后，释放出一个法术npc
		"skilltype_passive"    // 被动技能
	};

	static char* (g_szCastType[])=
	{
		"casttype_singletarget",             // 单一目标
		"casttype_singletargetcircleAOE",    // 单一目标圆形范围
		"casttype_AOEPointCircleArea",       // 目标地点的圆形范围
		"casttype_AOEcircleself",            // 以自己为中心的圆形范围技能
		"casttype_AOEquartercirlcefrontage", // 正面90度的扇型范围技能
		"casttype_AOEhalfcirclefrontage",    // 正面180度的半圆范围技能
		"casttype_AOEquartercirlcebackage",  // 背面90度的扇型范围技能
		"casttype_AOEhalfcirclebackage",     // 背面180度的半圆范围技能
		"casttype_AOETargetcirclearea",      // 以选定地面为中心的圆形范围技能
	};

	static char* (g_szSkillGeneralType[])=
	{
		"generaltype_action",   // 属于Action技能
		"generaltype_magic",    // 属于Magic技能
		"generaltype_sequence", // 属于连招技能
		"generaltype_passive",  // 被动技能
		"generaltype_trigger",  // 属于被动触发技能
	};

	static char* (g_szMonsterType[])=
	{
		"monstertype_normal",
		"monstertype_leader",
		"monstertype_boss",
		"monstertype_god",
		"monstertype_illusion",
		"monstertype_trap",
		"monstertype_herb",
		"monstertype_mine",
		"monstertype_wood",
		"monstertype_treasure",
		"monstertype_building",
		"monstertype_mount",
		"monstertype_pet",
		"monstertype_collision",
		"monstertype_insect",
		"monstertype_protect",
		"monstertype_pickup",
	};

	static char* (g_szStatusAnimType[])=
	{
		"AnimType_None",
		"AnimType_Stun",
		"AnimType_FallOver",
		"AnimType_Freeze",
	};

	static char* (g_szBalanceType[])=
	{
		"balancetype_none"                  , // 没有任何结算
		"balancetype_damagephysicaldefend"  , // 对物防做伤害结算
		"balancetype_damagemagicdefend"     , // 对魔法防做伤害结算
		"balancetype_damagebothdefend"      , // 对物防魔防做伤害结算
		"balancetype_restorehpmp"           , // 回HP MP结算
		"balancetype_relive"                , // 复活结算
	};

	//状态的结算公式类型
	static char* (g_szStatusBalanceType[])=
	{
		"balance_status_type_none"          ,
		"balance_status_type_restore"       , // 回复结算
		"balance_status_type_timeexp"       , // 时间经验
		"balance_status_type_mount"         , // 坐骑被动技能
	};

	//动作类型
	static char* (g_szActionType[])=
	{
		"baseaction"        ,
		"communityaction"   ,
		"socialaction"      ,
	};

	//性别
	static char* (g_szSexType[])=
	{
		"male",
		"female",
	};

	//职业
	static char* (g_szProfessionType[])=
	{
		"Warrior" , // 战士
		"Mage"    , // 法师
		"Taoist"  , // 道士
		"Assassin", // 刺客
		"Hunter"  , // 猎人
		"Sniper"  , // 火枪
	};

	//施放目标，客户端
	//如果是对自己使用，那么不需要鼠标指向攻击目标，直接取角色当前位置
	//如果是需要对人使用，那么攻击目标必须是角色
	//如果对位置使用，那么攻击目标为位置（如果指向角色，取角色位置）
	static char* (g_szSkillCastTarget[])=
	{
		"casttarget_me"            // 自己
		,"casttarget_friendlive"   // 同伴
		,"casttarget_enemylive"    // 敌人
		,"casttarget_live"         // 所有活着的东西
		,"casttarget_pos"          // 地面
		,"casttarget_friendcorpse" // 同伴的尸体
		,"casttarget_enemycorpse"  // 敌人的尸体
		,"casttarget_corpse"       // 尸体
		,"casttarget_herb"         // 以草药为目标
		,"casttarget_mine"         // 以矿为目标
		,"casttarget_wood"         // 以木头为目标
		,"casttarget_treasure"     // 以宝箱为目标
		,"casttarget_pet"          // PET目标
		,"casttarget_team"         // 队伍为目标
		,"casttarget_mount"        // 坐骑为目标
		,"casttarget_insect"       // 昆虫为目标
		,"casttarget_guild"        // 公会成员
		,"casttarget_campforce"    // 同阵营势力
	};

	//武器属性
	static char* (g_szWeaponElement[])=
	{    
		"physic"    ,
		"magic"     ,
		"forst"     ,
		"blaze"     ,
		"thunder"   ,
		"wind"      ,
		"all"
	};

	static char str_action[][32] = 
	{
		"idle"          ,//(待机)   

		"idle1"         ,//(待机)   new
		"idle2"         ,//(待机)   new
		"specialidle"   ,//(特殊待机)
		"attack_idle"   ,//(战斗待机)new
		"hurt"          ,//(被击)	new
		"run"           ,//(奔跑)
		"walk"          ,//(行走)
		"stun"          ,

		"sit"           ,//(坐下)    
		"stup"          ,//(站起)
		"dead",		//(原地倒地)
		"dead1",	//(屍體姿勢)  
		"pick",		//采药new
		"hack",		//砍伐new
		"dig",		//采矿new
		"recital",	//吟唱new
		"fire",		//师法 new
		"defend",	//防御new
		"sway",

		"attack1",//普通攻击
		"attack2",//普通攻击
		"attack3",//普通攻击

		"walk_attack",
		"run_attack",

		//双手武器		
		"double_attack_idle",// 战斗待机
		"double_attack2",    //普通攻击2   897    934  (912
		//普通攻击3           941    988  (954
		//普通攻击4           1003   1047 (1023
		"double_defend",	//防御                1159   1174
		"double_recital",	//武器吟唱            1185   1215
		"double_recital1",	//武器吟唱            1185   1215
		"double_recital2",	//武器吟唱            1185   1215
		"double_recital3",	//武器吟唱            1185   1215
		"double_recital4",	//武器吟唱            1185   1215
		"double_recital5",	//武器吟唱            1185   1215
		"double_recital6",	//武器吟唱            1185   1215
		"double_fire",		//武器师法            1217   1256
		"double_hurt",		//被击                1261   1275
		"double_dead",		//死亡                1282   1333
		"double_attack1",	//普通攻击1    1337   1366  (1350
		"double_scabbard",	//收武器          1383   1426
		"double_draw",		//拔出武器         1433   1446
		"double_run",		//拿双手武器跑步

		//单手武器
		"single_attack_idle",		//战斗待机       35      67
		"single_idle"	,			//非战斗待机		75     132
		//		walk,				//走路              135     167
		//		run,				//跑步              180     199
		"single_attackr1",		//右手普通攻击1     208     229  (218  
		"single_attackl1",		//左手普通攻击2       238     260  (249  
		"single_attackr2",		//右手普通攻击3       273     295 （283
		"single_attackl2",		//左手普通攻击4       304     326 （313
		//右手重击            334     360 （344
		//防御                366     382 （371
		"single_recital",			//武器吟唱            386     415
		"single_recital1",			//武器吟唱            386     415
		"single_recital2",			//武器吟唱            386     415
		"single_recital3",			//武器吟唱            386     415
		"single_recital4",			//武器吟唱            386     415
		"single_recital5",			//武器吟唱            386     415
		"single_recital6",			//武器吟唱            386     415
		"single_fire",			//武器师法            417     454
		"single_hurt",			//被击                456     470
		"single_dead",			//死亡                475     520       
		"jump",			//跳起                604     618
		"drop",			//落地                619     635
		"glide",			//停空                647     666
		"falltothegroundrun",//落地跑                674     703
		"single_double_draw",		//双手拔出武器             741     754
		"single_double_scabbard",	//双手收起武器             710     740
		"single_draw",				//单手收起武器             760     790 
		"single_scabbard",			//单手拔出武器             791     804
		"single_walk_attackr1",		//行走右手攻击            2141     2172  (2154
		"single_walk_attackl1",		//行走左手攻击            2176     2207 （2185
		"single_run",				//拿单手武器跑步
		"single_run_attackr1",		//跑步右手攻击            2212     2231 （2221
		"single_run_attackl1",		//跑步右手攻击            2233     2252 （2243 
		"run_fire",					//跑步施法                2275     2294 （2263
		"walk_fire",				//行走施法                2298     2329

		//特殊动作
		"strike",					//冲击              2341     2378 （2359，2367
		"sting",					//刺甲               2401     2423 （2409
		"brisance",					//震裂            2431     2455 （2443
		"frenzy",					//狂暴              2461     2485

		"single_run_scabbard",		// 跑步中拔出武器
		"single_run_draw",			// 跑步中收起武器
		"single_flag_run",          // 举旗run
		"single_flag_idle",          // 举旗idle
		"neigh",
		"shuffleleft",
		"shuffleright",
		"backattack",
		"single_yanwu",
		"mountattackidle",
		"mountattack_run",
		"single_mountattackidle",
		"single_mountattack_run",
		"single_mountscabbard",
		"single_mountdraw",
		"single_walk",
		"single_walkbackwards",
		"yongbao"
	};	

};

//////////////////////////////////////////////////////////////////////////

#endif // __COMMON_ITEMDEFINE_H__
