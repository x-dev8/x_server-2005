/********************************************************************
    Filename:     GlobalDef.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __COMMON_GLOBALDEF_H__
#define __COMMON_GLOBALDEF_H__

#pragma once

#include "MeRTLibsServer.h"
#include "ErrorCode.h"
#include "DataChunkWriter.h"
#include "FuncPerformanceLog.h"
#include "Dxsdk\d3dx9math.h"
#include "ResourcePath.h"
#include "PasswordDefine.h"
#include "TimeEx.h"
#include "IBAA_RandAlgorithm.h"
#include "GameDefineGlobal.h"
#include "GameDefineChar.h"
#include "GameDataType.h"

// 使用新的登录流程
#if 1

#ifndef __NEW_LOGIN__
#define __NEW_LOGIN__
#endif
 
#endif

#define GAMESERVER_MESSAGE_MAPPING_BEGIN \
        switch ( dwType ) \
        {

#define GAMESERVER_MESSAGE_HANDLE( messageId , messageHandle ) \
        case messageId: \
            { \
                messageHandle( pMsg ); \
                return true; \
            } \
            break;

#define GAMESERVER_MESSAGE_MAPPING_END \
        }

#define DATABASE_MESSAGE_MAPPING_BEGIN \
    switch ( pMessage->type ) \
        {

#define DATABASE_MESSAGE_HANDLE( messageId , messageHandle ) \
        case messageId: \
            { \
                messageHandle( pMessage ); \
            } \
            break;

#define DATABASE_MESSAGE_MAPPING_END \
        }

#define PLATFORM_MESSAGE_MAPPING_BEGIN \
    switch ( type ) \
        {

#define PLATFORM_MESSAGE_HANDLE( clientId, messageId , messageHandle ) \
        case messageId: \
            { \
                messageHandle( clientId, pMsg ); \
                return; \
            } \
            break;

#define PLATFORM_MESSAGE_MAPPING_END \
        }

#define SAFE_CONVERSION_MESSAGE( messagepointer, messagetype ) \
    messagetype* pTMessage = (messagetype*)messagepointer; \
    CHECK_RETURN( pMessage->GetLength()!=sizeof(messagetype), ER_MessageLengthError); 

#define MESSAGE_MAPPING_BEGIN \
        CHECK_RETURN( pMessage==NULL, ER_NullPointer); \
        switch ( msgType ) \
        {

#define MESSAGE_HANDLE_UNPACK( messageId, messageClassType, messageHandle ) \
		case messageId: \
				{ \
				messageHandle(pMessage ); \
				} \
				break;

#define MESSAGE_HANDLE_USER( messageId, messageClassType, messageHandle ) \
		case messageId: \
			{ \
			    SAFE_CONVERSION_MESSAGE(pMessage, messageClassType ); \
				messageHandle(pTMessage ); \
			} \
			break;

#define MESSAGE_HANDLE_USER_NOTCHECK( messageId, messageClassType, messageHandle ) \
		case messageId: \
			{ \
				messageClassType* pTMessage = (messageClassType*)pMessage; \
				messageHandle(pTMessage ); \
			} \
			break;

#define MESSAGE_HANDLE( messageId, messageClassType, messageHandle ) \
        case messageId: \
            { \
                SAFE_CONVERSION_MESSAGE(pMessage, messageClassType ); \
                messageHandle( pNetClient, pTMessage ); \
            } \
            break;

#define MESSAGE_HANDLE_1( messageId, messageClassType, messageHandle ) \
        case messageId: \
            { \
                SAFE_CONVERSION_MESSAGE(pMessage, messageClassType ); \
                messageHandle( pTMessage ); \
            } \
            break;

#define MESSAGE_HANDLE_NOTCHECK( messageId, messageClassType, messageHandle ) \
        case messageId: \
            { \
                messageClassType* pTMessage = (messageClassType*)pMessage; \
                messageHandle( pNetClient, pTMessage ); \
            } \
            break;

#define MESSAGE_MAPPING_END \
        }
//////////////////////////////////////////////////////////////////////////
// 小于最小值则等于某值
#define FIX_NUMBER(l,n,m)\
    {\
    if( l < n )\
        {\
        l = m;\
        }\
    }
#define FIX_NORMAL(value) FIX_NUMBER(value,1,1)

#define FIX_NORMAL_ZERO(value) FIX_NUMBER( value, 0, 0)

//////////////////////////////////////////////////////////////////////////
// GlobalDef.h


#define MAX_NAME_CREATE          16
#define MAX_NAME_STRING          32
#define MAX_PASSWORD_STRING      32
#define MAX_TITLE_COUNT          255
#define MAX_RECIPE_COUNT         500
#define BORN_POINT_COUNT         6
#define IP_LENGTH                16
#define INVALID_SERVERID         0xffffffff
#define MAX_KILLINFO_COUNT       100
#define MAX_SPECIALQUEST_COUNT   10
#define MAX_AREAREPULATION_COUNT 10
#define MAX_FRIENDDEGREE_COUNT   13
#define MAX_PRESSKEYSUIT_COUNT   10         // 人物一键换装数量
#define MAX_ACHIVEVMENT_COUNT    1000       // 人物成就总计

#define MAPTILESIZE         (128.0f*0.02f) // 地形块的基本大小 单位空间坐标单位
#define CHUNK_SIZE          16.0f          // Chunck 单位空间坐标单位
#define DORIDE_RATE         15000          // 两次骑马的间隔

#define INVALID_CHAR_ID     -1

#define MOVEVELOCITY        (3.0f)                 // 每秒移动格数，也就是人物移动速率
#define ONESTEPCOST         (1000.0f/MOVEVELOCITY) // 一步消耗的时间，毫秒

#define CHAR_DEFAULTBODYSIZE 0.3

#define PI	3.1415926f

//游戏世界信息搜集服务器
#define DATACOLLECTINTERVAL  (1*1000) //一分钟搜集一次信息(T)
#define SYNCCHARPOSINTERVAL  (5*1000) //游戏世界与clinet同步坐标消息的间隔

#define DEF_PER                   100.0f
#define DEF_PER_INT               100
#define DEF_PER_REC               0.01
#define POSITION_FLOAT_DIFFERENCE 0.01

#define DEF_TENTH                 0.1       //十分之一
#define DEF_PERCENT               0.01      //百分之一
#define DEF_THOUSANDTH            0.001     //千分之一

#define QUEST_MAX        4
#define PKVALUEDAILY_MOD 5 // PK值每天获得的最大值系数

#define PLUE_EXP_MODULUS     0.2
#define NEGATIVE_EXP_MODULUS 0.5
#define MOUNT_EXP_MODULUS    1.0

#define CHAR_REFRESHTIME 1000
#define EMISSIONFLYCOST 40
#define TEAM_EXP_DIS 60.0f
#define PackagePickDistance 1.5f            //拾取包裹的有效距离

#define BaseMoveSpeed 4.0f

#define SPELLACTION_CASTTIME 200
#define ONE_MIN              60000
#define ONE_SEC              1000
#define CheckPlayerPerTime   60000   // 一分钟
#define TellPlayerPerTime    1800000 // 30分钟

#define PKVALUEADD_PERTIME 2        // 每个时间段增加的PK值，只有当PK小于0时

#define ECTYPEMONSTERSTARTID 110000 // 这个ID以后就是副本怪物ID
#define ECTYPEMAPMONSTERIDLENGTH 4  // 副本地图怪物ID是4位
#define NORMALMAPMONSTERIDLENGTH 6  // 普通地图怪物ID是6位
#define MAPLEVELPERPLAYERLEVEL 5    // 每个地图等级对应人物角色5级
#define MAX_MAP_LEVEL 14            // 目前地图分14个等级 (人物角色 每5级一个等级) 

#define PrivateShopSellItemDiscount 0.95  // 摆摊扣税

// 角色是否阻挡

#define OneMinuteSecond ( 60 )          // 1分钟秒数
#define OneHourSecond   ( 60 * OneMinuteSecond )           // 一小时的秒数
#define OneDaySecond    ( 24 * OneHourSecond   )

#define OneMinuteMicroSecond ( 60 * 1000 )          // 1分钟毫秒数
#define OneHourMicroSecond   ( 60 * OneMinuteMicroSecond )           // 一小时的毫秒数
#define OneDayMicroSecond    ( 24 * OneHourMicroSecond   )

#define ItemUnLockTime ( 3 * 24 * 60 * 60 ) // 3天

// 安全地图
#define Safe_Map_Id     11
#define Safe_Map_PosX   218.0f
#define Safe_Map_PosY   212.0f
#define Safe_Map_Dir    0.0f

#define MoBeiMapID     9         // 漠北地图ID
#define LiaoDongMapID  0         // 辽东地图ID
#define DunHuangMapID  8         // 敦煌地图ID
#define GaoGouLiMapID  1         // 高句丽地图ID

#define eMAX_TEMP_BUFF 0xFF
// CharacterServer Id
#define CHARACTERSERVERID 100

#define WORLD_HEIGHT 40000.f


// 金钱总额的上限
#define MoneyUnit   10000
#define MaxMoney20 ( 10 * MoneyUnit )           // 20级金钱总额最大值
#define MaxMoney40 ( 100 * MoneyUnit )          // 40级金钱总额最大值
#define MaxMoney55 ( 1000 * MoneyUnit )         // 55级金钱总额最大值
#define MaxMoney60 ( 5000 * MoneyUnit )         // 55级以上金钱总额最大值


// 交子总额的上限
#define JiaoZiUnit   100
#define MaxJiaoZi20 ( 1 * MoneyUnit )              // 20级金钱总额最大值
#define MaxJiaoZi40 ( 10 * MoneyUnit )             // 40级金钱总额最大值
#define MaxJiaoZi55 ( 100 * MoneyUnit )           // 55级金钱总额最大值
#define MaxJiaoZi60 ( 500 * MoneyUnit )           // 55级以上金钱总额最大值

// 召唤怪上限
#define CharPetMonsterMaxCount   3

#define CHAT_STRINGMAX 500

// world define
const unsigned short ErrorUnsignedShortID = 0xffff;
const unsigned long  ErrorUnsignedLongID  = 0xffffffff;

const int dr_worldMaxPlayers      = 5000;
const int dr_worldMaxCharacters   = 32767; // World最大角色数/*32767*/ 65535
const int dr_worldMaxStages       = 128;   // 活动场景数
const int dr_refreshstagezonerate = 1;     // 刷新触发区域的频率

// stage define
const int dr_stageMaxCharacters  = 32767;     // Stage最大角色数
const int dr_stageMaxAreas       = 32*32*8*8; // 最大区块数
const int dr_stageMaxMapWidth    = 128*32;    // 地图最大宽度
const int dr_stageMaxMapHeight   = 128*32;    // 地图最大高度
const int dr_stageAreaSize       = 9;         // 12 区块大小 原来 16
const int dr_stageAIInterval     = 200;       // 地图内怪物的思考频率

// area define 
//const int dr_areaMaxCharacters   = dr_stageAreaSize*dr_stageAreaSize;   // Area区块内最大角色数
const int dr_areaMaxCharacters   = 1024;   // Area区块内最大角色数

// zone define
const int dr_stageMaxZones      = 32*32*16;
const int dr_zoneMaxCoveredArea = 256;

const int dr_MaxAttackTarget           = 16; //最多攻击目标
const int dr_MaxNameString             = MAX_NAME_STRING;     // 用户名
const int dr_MaxUserName               = dr_MaxNameString;
const int dr_MaxPassword               = MAX_PASSWORD_STRING; // 密码
const int dr_MaxTongCount              = 9;
const int dr_MaxPublicMessagesPerCount = 100;
const int dr_MaxPlayerName             = dr_MaxNameString + 1;
const int dr_MaxTongName               = 8;
//const int dr_MaxTongNumber             = 9;
const int dr_MaxPath                   = 256;
const int dr_MaxChatString             = 1024;
const int dr_MaxOfficialTitle          = 16;
const int dr_MaxYearName               = 16;
const int dr_LengthDate                = 20;
const int dr_MaxReputeName             = 18;
const int dr_MaxOfficialLevel          = 10;

// 物品名字
// 物品名字的长度应为英文版有些道具的名字会很长,现在修改为64,以前为32
const int dr_MaxItemName               = 2 * dr_MaxNameString;
const int dr_MaxItemDesc               = 100; //物品说明文字
const int dr_MaxShopDesc               = 24;  // 个人商店说明
const int dr_MaxQuestDesc              = 256; // 任务说明
const int dr_MaxQuestStateDesc         = 128; // 任务状态说明
const int dr_MaxQuestNextState         = 4;   // 下一任务所需状态数量
const int dr_MaxQuestState             = 10;  // 任务状态数量
const int dw_MaxQuestReward            = 8;   // 任务报酬
const int dr_MaxCharactersEachAccount  = 3;   // 每个账号能有3个角色

const unsigned long dr_MaxGuilSkillNum  = USHRT_MAX;     //攻击技能数量
                                     
// 任务相关                          
const int dr_MaxQuest                  = 3000;     // 最大任务数
const int dr_MinQuestId                = 3000;     // 任务起始Id
const int dr_MaxRemindQuestId          = 5000-1; // 任务结束Id
const int dr_MaxQuestId                = dr_MinQuestId+dr_MaxQuest-1; // 任务结束Id
const int dr_MaxActiveQuest            = 20/*10*/; // 最大活动任务数
const int dr_MaxGameVersion            = 12;       // 版本号最大
const int dr_MaxShopItem               = 50;       // 商店物品最大数
const int dr_MaxShoper                 = 20;       // 商店最大数
const int dr_MaxBattleMasterCount      = 1;        // 梁城主人最大个数
const int dr_MaxBattleAttacker         = 1;        // 梁城攻城最大个数

// 数据保存
const unsigned long dwAutoSaveDelay = 1000*60*5; //自动存储间隔时间
const unsigned int nSaveBatchNum    = 50;        //每次轮循保存的玩家数量

// 打斗相关
const float fDuelLength = 20.0f;
const float fDuelOutRange = 40.0f;

// 买卖相关
const float fSellBuyToNpcRange = 20.0f;
const float fSellDiscountRate  = 0.33f;
const float fReclaimDiscountRate  = 0.7f;

const int nReputeFlagCount = 26;

const unsigned short GameServerIdPrefix  = 0000;
const unsigned short GateServerIdPrefix  = 1000;
const unsigned short WorldServerIdPrefix = 2000;
const short          DiskServerId        = -1;
const unsigned long  EnterWorldMessageIntervalTime = 3000;

const uint32         bangGongMax = 65535;

const uint32         protectTime = 60 * 1000 * 30;
//////////////////////////////////////////////////////////////////////////
// 枚举
enum EGlobelConst
{ // 全局用枚举定义的常量    
    RAND_NUM               = 100,
    GEM_RAND_NUM           = 100, // 宝石镶嵌的随机数
    ADD_STATUS_RAND_NUM    = 100, // buffer作用的随机数
    WARD_RAND_NUM          = 100,
    RAND_THOUSAND          = 1000,// 千分率随机
    MAX_LEVEL_LIMIT        = 200, // 最高的等级
    ARMS_NAME_LENGTH       = 20,
    CANEQUIPITEM_HP_UNIT   = 100,
    MIN_ENMINYVALUE        = 10,  // 每次最少增加的仇恨值
    MULTIPLE_ENMINY        = 10,  // 仇恨系数倍数
    ATTACK_FLOAT_COUNT     = 5,   // 攻击幅度值档
    LEVEL_DISTANCE_SEGMENT = 5,   // 等级段数
    GEM_MAX_COUNT          = 3,   // 宝石最大个数    
    CompoundItemID         = 0,
    ClearElementCount      = 5,   // 五行套装一天只能洗掉5次
};

enum EConstDefine
{
    More_iCharPerAccount                = 5    //每个账号在一组游戏服务器能拥有5个角色
    ,More_iSkillCountPerLinkedSkills    = 5    //每个连招由5个招式组成
    ,More_iMaxLinkedSkills              = 5    //每个角色的连招个数
    ,More_iMaxCountOfAItem              = 30   //每个物品在一个物品包中最大的个数
    ,More_iMaxVars                      = 6000 //角色系统变量的个数
    ,More_iMaxTempVars                  = 2000
    ,More_iMaxSysVars                   = 5000
    ,More_iMaxGuildVars                 = 500  // 公会记数变量
    ,More_iMaxAchieveVars               = 300  // 成就计数变量 

    ,VarTimeBeginRange                  = 500 // 开始时间 2 个 short 记一个时间
    ,VarTimeEndRange                    = 999 // 结束时间
    //快捷背包序号变更 维护策划不停的更改变化
    ,More_exMainUIMax                    = 25//| 0--25  扩展快捷栏用 s_CUI_ID_FRAME_Exmain.m_pID_LISTIMG_exmain
    ,More_mainUIMax                      = 67//| 26--67 主界面用 s_CUI_ID_FRAME_MAIN.m_pID_LISTIMG_Hotkey(0,1,2各用14个)
    ,More_ainUIMaxOnly                   = 14//|            (0,1,2各用14个)
    ,More_rightSkill                     = 68//| 68     右键快捷用 s_CUI_ID_FRAME_SelectSkill.m_pID_LISTIMG_skill
    ,More_rightShortcutBegin             = 69//| 69-80  右面快捷栏 用
    ,More_skillEducate                   = 81//| 81        技能修炼
    ,More_iHotkey                        = 82//| 所以    enumConst::More_iHotkey 设为36         
    //------------------------------------------------

    ,More_nMapSize           = 128   //大陆中地图的大小
    //,More_iHotkey          = 9     //热键的数量
    ,More_iMaxSkillByte      = 32    //        
    ,More_iMaxSkill          = More_iMaxSkillByte*8 //最多8*32个技能
    //,More_iMaxEquipedSkill = 50
    
    ,More_iMaxSkillKnown        = 100   //最多习得的技能
    ,More_iCharDataRestoreCheck = 3000  //HP,MP恢复的时间单位
    ,More_iCharPoisonCheck      = 3000  //中毒扣血的检查间隔
    //,More_iHungerCheck        = 18000 //饥饿的时间单位

    ,More_iMaxLinkSymbolStone   = 3
    ,More_iMaxLinkNormalSkill   = 5
    ,Beginner_LevelLimit                = 5
    ,ObtainExp_LevelDiffLimit           = 5
    ,AttackMonster_MaxPlayer            = 8    
    ,Distance_ShareTeamExp              = 50
    //,UpgradeEquipMaxLimit             = 67
    ,UpgradeSkillMaxLimit               = 10
    ,UpgradePropertyMaxLimit            = 300
    ,PowerPointMax                      = 3
    ,PowerCountMax                      = 300
};

enum EHandType
{
    HT_RightHand, // 右手
    HT_LeftHand,  // 左手
};

enum EConstItemId
{ //[0,999]
    const_ustItemMoney  = 1,     // 钱
    const_ustItemGold   = 6,     // 元宝
    SCAPEGOAT_ID        = 45000, // 替身ID
    PALLADIUM_ID        = 14022 ,// 守护天使ID
    ITEM_LOCK_INTENSIFY = 4678,  // 神佑天晶
    NorPackageItemID    = 2,     // 普通包裹
    MidPackageItemID    = 3,     // 中等包裹
    AdvPackageItemID    = 4,     // 高级包裹
    PackageModelID      = 4000,  // 包裹模型id  
    HighShoutItemID     = 6108,  // 世界喊话道具

    ResetPubQuestItemID1 = 6068,   // 皇榜=>皇榜令
    ResetPubQuestItemID2 = 15071,  // 酒馆=>行酒令

};

enum EWeaponType
{
    eWeaponType_Combat  , // 徒手
    eWeaponType_Warrior , // 战士
    eWeaponType_Mage    , // 法师
    eWeaponType_Taoist  , // 道士
    eWeaponType_Assassin, // 刺客
    eWeaponType_Hunter  , // 猎人
    eWeaponType_Sniper  , // 火枪
    eWeaponType_Shied   , // 盾牌
    eWeapontype_Flag    , // 旗子
    eWeaponType_Max     ,
    eWeaponType_Invalid, // 无效的
};

enum EFightStatus
{ // 战斗状态标志 //在 8个bit中
    eFIGHT_NOFLAG       = 0,    // 没有特殊状态
    eFIGHT_RELIVE       = 1<<0, // 复活
    eFIGHT_MISS         = 1<<1, // 攻击未命中
    eFIGHT_BEKILLED     = 1<<2, // 目标被杀
    eFIGHT_BACKSTRIKE   = 1<<3, // 背击
    eFIGHT_CRITICALHIT  = 1<<4, // 暴击
    eFIGHT_DEADLYHIT    = 1<<5, // 致命一击
    eFIGHT_CANCEL       = 1<<6, // 取消
    eFIGHT_ERROR        = 1<<7, // 战斗出错
    eFIGHT_WARD         = 1<<8, // 招架
    eFIGHT_RESIST       = 1<<9, // 抵抗
    eFIGHT_SUCKHP       = 1<<10,// 吸血
    eFIGHT_DAMREFLECT   = 1<<11,// 反伤
    eFIGHT_SELFBEKILLED = 1<<12,// 攻击者自杀
};

enum EReasonType
{ // 请求原因
    eREASON_NOFLAG      = 0,     // 没有理由
    eREASON_NOTPERMIT   = 1<<0,  // 不被允许
    eREASON_ACK         = 1<<1,  // 确认
    eREASON_LOSTCONTROL = 1<<2,  // 失去控制
    eREASON_UNMOVEABLE  = 1<<3,  // 不能移动
    eREASON_UNARRIVABLE = 1<<4,  // 不可达
    eREASON_OUTOFRANGE  = 1<<5,  // 超过范围
    eREASON_OUTOFSIGHT  = 1<<6,  // 超出视野
    eREASON_MAYIDOIT    = 1<<20, // 我可以吗
    eREASON_STOPIT      = 1<<21, // 停下来
    eREASON_UNKNOWN     = 1<<31  // 原因不明
};

enum EPathDir
{ //路径方向
    DIR_0,
    DIR_45,
    DIR_90,
    DIR_135,
    DIR_180,
    DIR_225,
    DIR_270,
    DIR_315,
};

enum EActionType
{
    eAttack1,
    eAttack2,
    eAttack3,
    eAttack4,
    eAttack5,
    eMiss,      // 失准
    eFightBack, // 反击
    eResist,    // 格挡
    eHurt,
    eDead,
    eIdle,
    eWalk,
    eRun,

    eActionUnknown,
};

enum ENpcShowType
{
    eNormalNpc    = 0,    // 普通npc
    eNotChangeDir = 1<<0, // 不根据玩家转向
    eNotShadow    = 1<<1, // 脚下有阴影
};

enum EActionFlag
{
    eNormalFight  = 0,      // 普通状态
    eFighting     = 1 << 0, // 战斗中
    eSitting      = 2 << 1, // 坐着动作
    ePrepareFight = 3 << 1, // 准备战斗动作
};

enum ENpcType
{
    eNT_Normal = 0   , // 普通NPC
    eNT_Restore      , // 药品商人
    eNT_Weapon       , // 武器商人
    eNT_Jewelry      , // 首饰商人
    eNT_Dress        , // 服装商人
    eNT_Material     , // 材料商人
    eNT_Transport    , // 传送npc
    eNT_Cavalry      , // 坐骑商人
    eNT_Storage      , // 仓库npc
    eNT_Star         , // 升星npc
    eNT_MakeItemNpc  , // 合成NPC
    eNT_Activity     , // 活动NPC
    eNT_Feudal       , // 官府任务NPC
    eNT_Sale         , // 寄售商人NPC
    eNT_SpecialSale  , // 特殊兑换商
    eNT_ScriptNpc    , // 脚本创建的NPC
	eNT_GongXun      , // 贡献NPC
	eNT_MingWang     , // 名望NPC
	eNT_ShiZhuang    , // 时装NPC
	eNT_WenDa        , // 问答NPC
	eNT_JiNeng       , // 技能NPC
	eNT_PeiJian      , // 武器配件NPC
	eNT_ShiWu        , // 食物NPC
	eNT_YiZhan       , // 驿站NPC
	eNT_ZaHuo        , // 杂货NPC
	eNT_FenJie       , // 分解NPC
	eNT_QianZhuang   , // 钱庄NPC
	eNT_Pub          , // 酒馆黄榜NPC
	eNT_MoveStar     , // 移星
	eNT_SpecialRepair, // 特修
	eNT_Patrol       , // 巡逻
	eNT_Ship         , // 载物
	eNT_KeepWord2    , // 保留npc类型2
	eNT_KeepWord3    , // 保留npc类型3
	eNT_KeepWord4    , // 保留npc类型4
	eNT_KeepWord5    , // 保留npc类型5
	eNT_KeepWord6    , // 保留npc类型6
	eNT_KeepWord7    , // 保留npc类型7
	eNT_KeepWord8    , // 保留npc类型8
	eNT_KeepWord9    , // 保留npc类型9
    eNT_Item    = 99 ,
    eNT_Battle = 100 , //战场Npc
    eNT_Max,
};

enum EObjectType
{
    // 总称谓
    Object_Dump = 0       , // 不是任何类型npc
    Object_Player         , // 玩家
    Object_Npc            , // npc
    Object_Item           , // 道具
    Object_Monster        , // 怪物
    Object_Effect         , // 法术    

    // Object_Monster 派生
    Object_MonsterNormal = 10, // 一般怪 分布在地图上一群群的怪 boss
    Object_MonsterPet        , // 宠物怪
    Object_MonsterIllusion   , // 分身怪
    Object_MonsterResource   , // 资源怪
    Object_MonsterTrap       , // 陷阱机关怪
    Object_MonsterProtected  , // 被保护怪 镖车 马 娘么
    Object_MonsterRoute      , // 路径怪
    Object_MonsterBuilding   , // 建筑

    // Object_Npc 派生
    Object_NpcNormal     = 20, // 普通脚本Npc
    Object_NpcFight          , // 带巡逻战斗Npc
    Object_NpcShip           , // 带Ship数据的载体Npc
};

// 国家
enum ECountry
{
    //无国家，中立
    country_none    = 0,
    country_sanguo     , // 3国
    country_qin        , // 秦
    country_npc        , // npc
    country_human      , // 人类
    country_monster    , // 怪物
    country_naturalness, // 自然物
    country_max        ,
};

enum EBankTradeResult
{ // 银行交易结果
    eBankTradeResultSuccess = 0     // 成功
    ,eBankTradeResultBankFull       // 存的钱超过钱柜上限
    ,eBankTradeResultPlayerNotMoney // 玩家没有这么多钱
    ,eBankTradeResultBankNotMoney   // 钱柜没有这么多钱
    ,eBankTradeResultUpgradeMax     // 钱柜已是最高级
    ,eBankTradeResultFalied         // 未知错误
};

enum BattleType
{ // 战场类型
    BT_Normal   = 0,  // 普通
    BT_Master   = 1,  // 主人
    BT_Attacker = -1, // 攻城
};

enum StorageTradeResult
{ //仓库交易结果
    eStorageTradeResultSuccess = 0, // 成功
    eStorageTradeResultUpgradeMax , // 仓库已是最高级
    eStorageTradeResultFalied       // 未知错误
};

enum EDefaultPorts 
{  //服务器使用默认端口 
    // 服务器组
    DP_LoginServerListenClientPort        = 20003, // LoginServer默认监听客户端那的端口
    DP_GateServerListenClientPort         = 20004, // GateServer默认监听客户端的端口
    DP_GameServerListenGateServerPort     = 20005, // GameServer默认监听GateServer端口
    DP_AccountServerListenLoginServerPort = 20006, // AccountServer默认监听LoginServer端口
    DP_DatabaseServerListenGameServerPort = 20007, // DatabaseServer默认监听GameServer端口
    DP_GameServerListenGMPort             = 20008, // GameServer默认监听GM工具端口
    DP_GameServerListenManagerToolPort    = 20009, // GameServer默认监听管理工具端口
    DP_GameServerListenLoginServerPort    = 20010, // GameServer默认监听LoginServer端口
    DP_LogServerListenGameServerPort      = 20011, // LogServer默认监听GameServer端口
    DP_GameServerListenThunderPort        = 20012, // GameServer默认监听迅雷端口
    DP_CenterServerListenGameServerPort   = 20013, // CenterServer默认监听GameServer端口
    DP_CenterServerListenLoginServerPort  = 20014, // CenterServer默认监听LoginServer端口
};

enum EMonsterType
{ // 记录怪物类型
    eMT_NormalMonster,   // 普通怪物
    eMT_LeaderMonster,   // 精英怪物
    eMT_BossMonster,     // Boss怪物
    eMT_GodMonster,      // 神话怪物
    eMT_IllusionMonster, // 镜像怪物
    eMT_Trap,            // 陷阱怪物
    eMT_Herb,            // 草药
    eMT_Mine,            // 矿物
    eMT_Wood,            // 木头
    eMT_Treasure,        // 宝箱
    eMT_Building,        // 建筑怪
    eMT_Mount,           // 骑宠
	eMT_Pet,			 // 召唤兽
    eMT_Collision,       // 阻挡怪
    eMT_Insect,          // 昆虫
    eMT_MaxCount,        //
};

//组队相关
enum TeamMangerEnum
{
    TeamMaxCount = 6000,			//最大的团队数量

    TeamMaxMember = 24,				//一个团最多20人
    TeamMaxManipleMember = 6,		//一个小队5人
    TeamMaxManipleCount = 4,		//一个团4个小队
    TeamUpdateInterval = 2000,		//队员信息2秒刷新一次
    TeamUpdateToCenter = 5000,      //为了缓解跨服同步压力,队员信息5秒同步一次
    TeamSelfUpdate = 100000,         //队伍创建后每60秒检查一次是否还有效

    ReleaseSpaceTime = 1000,    
    TeamManipleDefalutId = -1,		//默认自动分配小队
};

enum AssignModeType                    //组队模式
{
    AssignMode_FreeMode = 0,        //自由分配
    AssignMode_Team,                //队伍。。
    AssignMode_Random,                //随即。。
    AssignMode_Assign,                //分配。。
};

enum BoultAssignTeam                //掉落物品后操作
{
    BoultAssign_None = 0,            //未选择
    BoultAssign_ComeDown,            //索取
    BoultAssign_GiveUp,                //放弃
};

enum ChangeAssignModeAnswer
{
    ChangeMode_None = 0, //未选择
    ChangeMode_Agree,    //同意
    ChangeMode_Refuse,   //拒绝
};
//////////////////////////////////////////////////////////////////////////////////////////

enum EItemLevel
{
    eIL_Normal = 1,     // 普通
    eIL_Choiceness,     // 良品
    eIL_Polish,         // 精品
    eIL_Nonsuch,        // 极品
    eIL_Holiness,       // 神品
};

// 装备五行属性
enum EItemElements
{
    ItemElements_Init = 0,
    ItemElements_Metal,     // 金
    ItemElements_Wood,      // 木
    ItemElements_Water,     // 水
    ItemElements_Fire,      // 火
    ItemElements_Earth,     // 土

    ItemElements_End,
};

enum EItemPickLevel
{
    eIPL_Nothing = 0,            // 无权限  (暂时无权限, 但当打开的包裹关闭以后, 也许会获得拾取权)
    eIPL_View    = 0x1,          // 查看权  (是否能查看这个物品包裹)
    eIPL_Assign  = 0x2,          // 分配权  (服务器判断的, 队伍是队长分配模式时, 队长有分配权)
    eIPL_Pick    = 0x4,          // 拾取权  (表明该玩家有拾取这个物品的权限)
    eIPL_Hold    = 0x8,          // 拥有权  (表明这个物品已经归属于某个玩家,其他玩家已经不能再获得这个物品,有这个权限一定能拾取)

    eIPL_End     = 0xF,        
};

enum PackageItemInfo
{
    MaxPackageItemCount = 48,            // 包裹最大的物品
    MaxPackageAccessCount = TeamMaxManipleMember,         // 以后可能会是公会所有,最大可能会到100个

};

enum EPetType
{
    EPT_Skill = 0, // 技能宠物
    EPT_Protect,   // 保护宠物
    EPT_Capture,   // 捕获宠物
    EPT_Max,       // 最多的宠物
};

enum ECurPetTactic
{ // 宠物的处理策略
    ePetCommandAI = 0,
    ePetAttackAI,
    ePetDefendAI,
};

enum EJiFengItemStatus
{
    EJFIS_Delete = 0, // 已经领取
    EJFIS_Have   = 1, // 持有未领取
};

//PK系统 相关
/////////////////////////////////////////////////////////////// 

#define  MinPKValue             0           // 最小PK值
#define  MaxPKValue             999         // 最大PK值
#define  PKProtectLevel         20          // PK 保护等级
#define  PKKillValue            50          // 杀死一个PK值为0的玩家，将获得50点PK值
#define  PKHellPunishValue      250         // 250 进监狱
#define  PKHellleaveValue       200         // 200 离开监狱
#define  PKDropItemRate         30          // 红名玩家被杀死后，30%几率掉落1件未绑定的物品
#define  PKModeChangeDelayed    180000      // 切换完PK模式后延迟 3分钟
#define  PKValueUpdateTime      300000      // 每 5分钟减少 1点PK值
#define  PKCriticalTime         1800000     // 狂暴模式持续时间

enum PKMode
{
    PKMode_Normal = 0,		    // 普通模式
    PKMode_Fight     ,			// PK模式
    PKMode_Critical  ,			// 狂暴模式
	PKMode_MaxValue  ,
};
/////////////////////////////////////////////////////////////////

enum EItemHoldType
{
    eIHT_Nothing = 0,            // 不属于任务类型
    eIHT_Individual,             // 属于个人
    eIHT_Team,                   // 属于队伍
    eIHT_Guild,                  // 属于公会
    eIHT_All,                    // 属于所有人

    eIHT_End,                    
};

enum LoginValidateType
{ //验证方式
    LVT_AccountServer,    // 通过 自己的 AccountServer
    LVT_17173Interface,   // 通过 17173 接口
    LVT_ThunderInterface, // 通过 迅雷 接口
    LVT_MAX,
};

enum eDllRet
{
    e_errorID      = 0, //“0 “ 没有这个用户
    e_succ_adult   = 1, //“1” 验证成功(成年人)
    e_IDBeLock     = 2, //“2” 此用户被禁止登陆
    e_unlegalityID = 3, //“3 “ 用户名不合法
    e_errorPWD     = 5, //“5” chk错误
    e_succ_minor   = 7, //“7” 验证成功(未成年人)
    e_fail         = 9  //“9” 验证失败
};

enum EServerType
{
    ST_LoginServer,     // 登录服务器 
    ST_CharacterServer, // 登陆选择人物游戏服务器
    ST_GameServer,      // 地图游戏服务器
    ST_CenterServer,    // 中心服务器
    ST_None,
};

enum ESwitchStageReqType
{   
    SSRT_EnterGameWorld,        // 第一次进入游戏世界
    SSRT_EnterGameServerMap,    // 进入地图服务器 切服行为
    SSRT_EnterToCharacterLogin, // 回到CharacterServer
    SSRT_FlyToMap,              // 用于发送飞地图请求    
};

enum ESwitchStageAckType
{
    SSAT_EnterWorldUseDatabaseMapInfo,         // 进入游戏使用数据库存的地图信息
    SSAT_EnterWorldUseMessageMapInfo,          // 进入游戏使用切GameServer时候的地图信息
    SSAT_LocalFlyToMap,                        // 本地切地图
    SSAT_EnterWorldUseDatabaseMapInfoBeCorrect,// 进入游戏使用数据库存的地图信息 需要修正( 数据库存了错误的地图ID)
};

enum EClientStateType
{
    CST_NoState,                                       // 无状态
    
    CST_InLoginQueueNotSendLoginInfo,                  // 在登录队列中还没有发登录消息（请求Ip port）
    CST_InLoginQueueWaitGateInfo,                      // 在登录队列中发了登录消息

    CST_InCharacterServerWaitTargetGameServerGateInfo, // 在专门用于选择人物登入进入游戏的CharacterServer等待目标GameServer的GateServer信息
    CST_InGameServerWaitTargetGameServerGateInfo,      // 在GameServer上等待目标GameServer的GateServer信息
    CST_InGameServerWaitTargetCharacterServerGateInfo, // 在GameServer上等待目标专门用于选择人物登入进入游戏的CharacterServer的GateServer信息
    
    CST_WaitLoginServer2CharacterServer,               // 等待LoginServer到专门用于选择人物登入进入游戏的CharacterServer
    CST_WaitCharacterServer2GameServer,                // 等待从CharacterServer到目标GameServer
    CST_WaitGameServer2GameServer,                     // 等待GameServer间切换
    CST_WaitGameServer2CharacterServer,                // 等待GameServer到CharacterServer切换

    CST_InCharacterServer,                             // 已经连到专门用于选择人物登入进入游戏的CharacterServer
    CST_InGameServer,                                  // 已经连到专门用于游戏的MapGameServer
    CST_InGameServerPlaying,                           // 已经在专门用于游戏的MapGameServer上游戏
};

// 复活类型
enum EReliveType
{
    eReliveTypeBorn = 0         , // 出生点
    eReliveTypeCity             , // 王城复活
    eReliveTypeNearPos          , // 最近的复活点
    eReliveTypeOrigin           , // 原地
    eReliveTypeOriginFullHpMP   , // 信春哥原地复活满血满状态
};


enum EElementType
{ // 法元素
    eElement_Ice,    
    eElement_Fire,   
    eElement_Thunder,
    eElement_Wind,   
    eElement_Max,
};

enum EOperationType
{ // 运算枚举
    EOT_Add,
    EOT_Sub,
    EOT_Mul,
    EOT_Div,
    EOT_Set,
};

enum EBagType
{
    BT_NormalItemBag   ,
    BT_PrivateShopBag  ,
    BT_StorageBag      ,
    BT_CompoundBag     ,
    BT_IntensifyBag    ,
    BT_ReduceBag       ,
    BT_UnSoulBag       ,
    BT_LockIntensifyBag,
    BT_EquipBag        ,
    BT_MaterialBag     ,
    BT_TaskBag         ,
    BT_MountBag        ,
    BT_All             ,
};

//角色包裹的定义
enum ECharItemBagConst
{
    ITEM_BAGMAX              = 100,             // 背包 Normal 物品的最大数
    ITEM_BAGMATERIAL_MAX     = 60,              // 背包 Material 物品的最大数
    ITEM_BAGTASK_MAX         = 35,              // 背包 Task 物品的最大数
    ITEM_BAG_TOTAL           = ITEM_BAGMAX + ITEM_BAGMATERIAL_MAX + ITEM_BAGTASK_MAX,

    ITEM_DISTORY             = ITEM_BAGMAX + 1, // 删除背包物品的宏

    ITEM_PRIVATE_SHOP_BAGMAX = 25,              // 个人商店
    ITEM_COMPOUND_BAGMAX     = 3 ,              // 合成背包
    ITEM_BAGMAX_IN           = 10,
    ITEM_PACK_OLD            = 24,
    ITEM_MOUNT_MAXCOUNT      = 6 ,              // 坐骑最大数

    //ITEM_STORAGEMAX = 10,
    //ITEM_STOREMAX = 40,
    //ITEM_SYMBOLSTONEMAX = 30,
    //ITEM_ACTIONMAX = 50,
    //ITEM_TRADEMAX = 20,
    //ITEM_MATERIALMAX = 3
};

// 各种生产, 生活技能点类型枚举
#define RecipeSkillNumMax   3   // 最多只能学习三个生活技能

enum ERecipeType
{
    ERT_CaoYao,           // 草药
    ERT_ZhuBao,           // 珠宝
    ERT_DuanZao,          // 锻造
    ERT_ZhuJia,           // 铸甲
    ERT_GongYi,           // 工艺
    ERT_XunMa,            // 驯马
    ERT_GemLevelUp,       // 宝石升级

    ERT_Default2,         // 初始值
    ERT_Default3,         // 初始值
    ERT_Default4,         // 初始值
    ERT_CaiKuang,         // 采矿
    ERT_CaiYao,           // 采药
    ERT_BuZhuo,           // 捕捉
    ERT_BuChong ,         // 捕虫

    ERT_MaxType = 24,     // 最大类型
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

enum ECharAttrType
{ // 人物属性的枚举
    //一级属性
    CharAttr_Strength     , // 力量
    CharAttr_Agility      , // 敏捷
    CharAttr_Constitution , // 体质
    CharAttr_Intelligence , // 智力
    CharAttr_BaseAttributeMaxCount,
    //二级属性
    CharAttr_HPMax = CharAttr_BaseAttributeMaxCount, // 生命上限
    CharAttr_MPMax            , // 能源上限
    CharAttr_Attack           , // 攻击力
    CharAttr_DefendShort      , // 近程防御
    CharAttr_DefendLong       , // 远程防御
    CharAttr_DefendMagic      , // 魔法防御
    CharAttr_MoveSpeed        , // 移动速度
    CharAttr_HPRestore        , // HP恢复速率
    CharAttr_MPRestore        , // MP恢复速率
    CharAttr_DerateShort      , // 近程减免
    CharAttr_DerateLong       , // 远程减免
    CharAttr_DerateMagic      , // 魔法减免
    CharAttr_DerateIgnoreShort, // 忽视近程减免
    CharAttr_DerateIgnoreLong , // 忽视远程减免
    CharAttr_DerateIgnoreMagic, // 忽视魔法减免
    CharAttr_Dodge            , // 闪避率
    CharAttr_Exact            , // 命中率
    CharAttr_Critical         , // 暴击率
    CharAttr_CriticalIntensity, // 暴击伤害
    CharAttr_Tenacity         , // 韧性
    CharAttr_ResistDread      , // 恐惧抗性
    CharAttr_ResistComa       , // 昏迷抗性
    CharAttr_ResistSilence    , // 沉默抗性
    CharAttr_ResistSlow       , // 减速抗性
    CharAttr_AttackSpeed      , // 攻击速度
    CharAttr_IntonateSpeed    , // 吟唱速度
    CharAttr_AttributMaxCount , 

    //其它属性
    CharAttr_Level = CharAttr_AttributMaxCount, // 等级                                    
    CharAttr_Reputation           , // 当前名望
    CharAttr_CurGetReputation     , // 当前获得名望                
    CharAttr_Exploit              , // 当前功勋
    CharAttr_CurGetExploit        , // 当前获得功勋                                                
    CharAttr_HP                   , // 血量
    CharAttr_MP                   , // 魔量 
    CharAttr_Exp                  , // 当前经验
    CharAttr_ExpNotUsed           , // 未使用的经验
    CharAttr_SkillExp             , // 技能经验
    CharAttr_SkillExpNotUsed      , // 未使用的技能经验
    CharAttr_Energy               , // 活力值 (生产消耗)
    CharAttr_EnergyMax            , // 活力值最大值        45+人物等级(ILevel)*5
    CharAttr_Vigor                , // 精力 (采集消耗)
    CharAttr_VigorMax             , // 精力最大值 45+人物等级(ILevel)*5

    ///////////////////////////////////////////////////////////////////////////////////
    CharAttr_CaoYao,           // 草药
    CharAttr_ZhuBao,           // 珠宝
    CharAttr_DuanZao,          // 锻造
    CharAttr_ZhuJia,           // 铸甲
    CharAttr_GongYi,           // 工艺
    CharAttr_XunMa,            // 驯马

    CharAttr_Default1,         // 初始值
    CharAttr_Default2,         // 初始值
    CharAttr_Default3,         // 初始值
    CharAttr_Default4,         // 初始值
    CharAttr_CaiKuang,         // 采矿
    CharAttr_CaiYao,           // 采药
    CharAttr_BuZhuo,           // 捕捉
    CharAttr_BuChong ,         // 捕虫

    CharAttr_Max = CharAttr_CaoYao + ERT_MaxType,  // 最大值
    //////////////////////////////////////////////////////////////////////////////////
    CharAttr_AreaRepulation       , // 刷新地区声望 ( 操作在 GlobalFunction.h )
    CharAttr_CanReceivePrentice   , // 当前可以招收徒弟
    CharAttr_MasterLevel          , // 当前师门等级
    CharAttr_MasterValue          , // 当前师门威望值
    CharAttr_MasterExperience     , // 当前的历练值            
    CharAttr_GiddyResist          ,
    CharAttr_StandResist          ,
    CharAttr_SlowdownResist       ,
    CharAttr_TorpidResist         ,
    CharAttr_Death                , // 死亡
    CharAttr_Relive               , // 复生
    CharAttr_HPHeal               , // 治疗恢复的HP
    CharAttr_HPRestoreEatDrug     , // 吃完药恢复
    CharAttr_Profession           , // 职业改变
    CharAttr_SkillHPCost          , // 使用技能的HPCost
    CharAttr_SkillMPCost          , // 使用技能的MPCost
    CharAttr_Country              , // 国籍
    CharAttr_CurGetExp            , 
    CharAttr_XPValue              , // 使用技能的XP Cost short
    CharAttr_MountExp             , // 坐骑经验当前
    CharAttr_MountChangeLevel     , // 等级变更
    CharAttr_NextNotIntonate      ,
    CharAttr_CurMountHP          ,
    CharAttr_CurMountHPMax       ,
    CharAttr_GuildContribute      , // 当前帮贡 
    CharAttr_CurGetGuildContribute, // 当前获得帮贡
    CharAttr_MaxKillMonsterCount  , // 最大杀怪数量
    CharAttr_CurKillMonsterCount  , // 当前杀怪数量
    CharAttr_Challenge            , // 当前战场擂台积分
    CharAttr_MountCountLimit      , // 可拥有坐骑数量
    CharAttr_Honour               , // 当前荣誉
    CharAttr_CurGetHonour         , // 当前获得荣誉   
    CharAttr_CountryScore         , // 当前国战积分
    CharAttr_CurGetCountrySocre   , // 当前获得国战积分  
    CharAttr_StorageItemGrid      , // 当前的物品仓库格数
    CharAttr_StorageMountGrid     , // 当前的坐骑仓库格数
};


// 生产生活类型获得人物属性消息类型( 人物属性消息类型必须定义在一起  )
static unsigned short GetCharAttrByRecipeType( unsigned char uchType )
{
    if ( uchType >= ERT_MaxType )
    { return 0; }

    return CharAttr_CaoYao + ( uchType - ERT_CaoYao );
}

static unsigned short GetRecipeTypeByCharAttr( unsigned char uchAttr )
{
    return uchAttr - CharAttr_CaoYao;
}

enum eAddToClenResult
{
    eResult_NotFound = 0  //找不到此人
    ,eResult_RepeatedAdd  //重复加入
    ,eResult_Success      //添加成功
    ,eResult_SameSex      //企图同性恋
    ,eResult_NotEnoughAge //未成年不能入伙
    ,eResult_WrongTeacher //拜师失败
    ,eResult_WrongStudent //收徒弟失败
    ,eResult_Excessive    //重婚、滥交友拜师
};    

enum AN_S2A_OpenClientUI_Flag
{
    AN_S2A_OpenUI_NULL               = 0,
    AN_S2A_OpenUI_StoryBook          = 1,   //打开故事书
    AN_S2A_OpenUI_GuildIcon          = 2,   //打开帮派图标
    AN_S2A_OpenUI_Brother            = 3,   //打开兄弟
    AN_S2A_OpenUI_ChatBULL           = 4,   //打开全服公告--
    AN_S2A_OpenUI_ChatSHOUT          = 5,   //打开喊话 区域服务器九宫格
    AN_S2A_OpenUI_ChatHIGHSHOUT      = 6,   //打开高喊 区域同全服-- 其实用于玩家]
    AN_S2A_OpenUI_IntensifyUI        = 7,   //强化
    AN_S2A_OpenUI_UnSoulBoundUI      = 8,   //解除绑定
    AN_S2A_OpenUI_ReduceUI           = 9,   //分解
    AN_S2A_OpenUI_ChatParticular1    = 10,  //打开小道小心1 用于vip玩家
    AN_S2A_OpenUI_ChatParticular2    = 11,  //打开小道小心2 用于vip玩家
    AN_S2A_OpenUI_ChatParticular3    = 12,  //打开小道小心3 用于vip玩家
    AN_S2A_OpenUI_ChatParticular4    = 13,  //打开小道小心4 用于vip玩家
    AN_S2A_OpenUI_ChatParticular5    = 14,  //打开小道小心5 用于vip玩家
    AN_S2A_OpenUI_ChatParticular6    = 15,  //打开小道小心6 用于vip玩家
    AN_S2A_OpenUI_ChatParticular7    = 16,  //打开小道小心7 用于vip玩家
    AN_S2A_OpenUI_ChatParticular8    = 17,  //打开小道小心8 用于vip玩家
    AN_S2A_OpenUI_ChatParticular9    = 18,  //打开小道小心9 用于vip玩家
    AN_S2A_OpenUI_ChatParticular10   = 19,  //打开小道小心10 用于vip玩家
    AN_S2A_OpenUI_LockIntensifyUI    = 20,  //打开锁强化UI
    AN_S2A_OpenUI_CopyMap_WSS        = 21,  //打开万兽山奖励界面
    AN_S2A_OpenUI_BiaoShi            = 22,  //打开镖师查询
    AN_S2A_OpenUI_LearnSkill         = 23,  //打开技能学习界面
    AN_S2A_OpenUI_Intensify          = 24,  //打开升星界面
	AN_S2A_OpenUI_Identify			 = 25,  //打开鉴定界面
	AN_S2A_OpenUI_KaiGuang			 = 26,  //打开开光界面
    AN_S2A_OpenUI_ShopChangePoint    = 27,  //打开金锭兑换界面
    AN_S2A_OpenUI_Decompound         = 28,  //打开分解界面
	AN_S2A_OpenUI_LotteryAwards		 = 29,  // 宝箱奖励说明界面
	AN_S2A_OpenUI_MoveStarToEquip	 = 30,  // 移星界面，星移到装备上
	AN_S2A_OpenUI_MoveStarToItem	 = 31,  // 移星界面，星移到移星石上
	AN_S2A_OpenUI_FiveElement		 = 32,  // 五行
	AN_S2A_OpenUI_RealAward			 = 33,  // 实物奖励
	AN_S2A_OpenUI_FiveElementClear	 = 34,  // 洗五行
	AN_S2A_OpenUI_SpecialRepair		 = 35,  // 特殊修理
	AN_S2A_OpenUI_EquipUpgrade		 = 36,  // 装备升阶
    AN_S2A_OpenUI_FiveXingChange     = 37,  //五行改变
    AN_S2A_OpenUI_FinvXinigLevel     = 38,  //五行提纯
	AN_S2A_OpenUI_UpgradeSkillEquip	 = 39,  // 升级套装技能装备部件
	AN_S2A_OpenUI_ChangeSkillEquip	 = 40,  // 转化套装技能装备部件
	AN_S2A_OpenUI_ShowScriptGif		 = 41,	// 显示特性GIF的界面
	AN_S2A_OpenUI_JoinFight			 = 42,	// 显示JoinFight的界面
    AN_S2A_OpenUI_ChangeName         = 43,  //改变名字
	AN_S2A_OpenUI_PointShop			 = 44,  //积分商城
	AN_S2A_OpenUI_WeaponUpgrade		 = 45,	// 武器升阶
	AN_S2A_OpenUI_MoveStarUprade	 = 46,	//移星石升级
	AN_S2A_OpenUI_StarMaterialUpgrade= 47,	//升星材料升级
	AN_S2A_OpenUI_MailSystem		 = 48,
	AN_S2A_OpenUI_GoldTrade			 = 49,
    AN_S2A_OpenUI_CampBattle         = 50,  //阵营战场
    AN_S2A_OpenUI_FiveXingTrans      = 51,  //五行转移
    AN_S2A_OpenUI_CampBattleResMove  = 52,  //阵营战场资源之间传送
	AN_S2A_OpenUI_IntensifyStar      = 53,  //打开流光升星界面
    AN_S2A_OpenUI_LearnCaoYao        = 54,  //制药学习界面
    AN_S2A_OpenUI_LearnZhuBao        = 55,  //珠宝学习界面
    AN_S2A_OpenUI_LearnDuanZao       = 56,  //锻造学习界面
    AN_S2A_OpenUI_LearnZhuJia        = 57,  //铸甲学习界面
    AN_S2A_OpenUI_LearnGongYi        = 58,  //工艺学习界面
    AN_S2A_OpenUI_LearnXunMa         = 59,  //驯马学习界面
    AN_S2A_OpenUI_LearnCaiKuang      = 60,  //采矿学习界面
    AN_S2A_OpenUI_LearnCaiYao        = 61,  //采药学习界面
    AN_S2A_OpenUI_LearnBuZhuo        = 62,  //捕捉学习界面
    AN_S2A_OpenUI_HookOffline        = 63,  //NPC离线挂机
    AN_S2A_OpenUI_MountBreed         = 64,  //坐骑繁殖界面
	AN_S2A_OpenUI_DELETESTUDENT      = 65,  //删除徒弟
	AN_S2A_OpenUI_Soul				 = 66,  //装备铭刻
	AN_S2A_OpenUI_Hole				 = 67,  //装备打孔
	AN_S2A_OpenUI_Gem				 = 68,  //镶嵌宝石
	AN_S2A_OpenUI_GemRemove			 = 69,  //拆卸宝石
	AN_S2A_OpenUI_GemReplace		 = 70,  //拆卸宝石
	AN_S2A_OpenUI_Purple			 = 71,  //鎏金
	AN_S2A_OpenUI_ReOpenLight		 = 72,  //鎏金回炉
	AN_S2A_OpenUI_Maintain			 = 73,  //保值
	AN_S2A_OpenUI_Amulet			 = 74,  //护身符上色
	AN_S2A_OpenUI_GemLevelUp		 = 75,  //宝石升级
	AN_S2A_OpenUI_Charm				 = 76,  //符文吸蓝
	AN_S2A_OpenUI_Recycle			 = 77,  //装备回收
	AN_S2A_OpenUI_Melt				 = 78,  //装备熔炼
	AN_S2A_OpenUI_CREATEGUILD        = 79, //创建帮会
	AN_S2A_OpenUI_MaintainCross		 = 80,  //跨级保值
	AN_S2A_OpenUI_XSJLevelUp		 = 81,  //洗石剂升阶
	AN_S2A_OpenUI_ApplyJoinGuild		 = 82,  //申请入帮
	AN_S2A_OpenUI_LevelOneGuildShop		 = 83,  //1级帮会商店
	AN_S2A_OpenUI_LevelTwoGuildShop		 = 84,  //2级帮会商店
	AN_S2A_OpenUI_LevelThreeGuildShop	 = 85,  //3级帮会商店
	AN_S2A_OpenUI_LevelFourGuildShop	 = 86,  //4级帮会商店
	AN_S2A_OpenUI_LevelFiveGuildShop	 = 87,  //5级帮会商店
	AN_S2A_OpenUI_LevelSixGuildShop		 = 88,  //6级帮会商店
    AN_S2A_OpenUI_PetStorage		     = 89,  //坐骑宠物仓库
    AN_S2A_OpenUI_Max
};

enum EIdleSubAction
{
    // Server和Client保持一致
    CS_SubAction_Normal,
    CS_SubAction_SitDown,        
    CS_SubAction_FightAction,
    CS_SubAction_Embrace,     // 拥抱
};

//普通攻击消耗的时间
enum ENormalAttackCostTime
{
    Fast_NormalAttackCostTime = 667
    ,Normal_NormalAttackCostTime = 1333
    ,Slow_NormalAttackCost = 2000
};

enum EItemBagProcessResult
{
    //处理成功
    ierr_Success = 0             // 操作成功
    ,ierr_notallitempushed       // 不是所有的物品都放下了。只放下来一部分
    ,ierr_NotHaveTargetCountItem // 没有制定数目的物品
    ,ierr_reachmaxcountofaitem   // 达到某个物品最大数量
    ,ierr_ItemNotExist           // 物品不存在
    ,ierr_erritemid              // 错误的物品ID
    ,ierr_PackIsFull             // 背包已经慢了
    ,ierr_CanNotOverlap          // 不能重叠
    ,ierr_ItemIsLocked           // 物品已经加锁
    ,ierr_IndexOutOfBagSize      // 下标超过背包大小
    ,ierr_RepeatedBigId          // BigId重复
    ,ierr_PackItemPointerNull    // 实际背包数据指针为空
    ,ierr_ErrorItemGuid          // 错误物品guid
    ,ierr_unknown
};

enum EHotKeyBagType
{ //背包类型
    //BagTypeMouse,           //鼠标上的道具
    BagTypePack,           
    //BagTypeEquip,           //装备背包（包括武器，防具）
    //BagTypeUse,             //消耗品背包（主要是Restore类）
    //BagTypeMaterial,        //原料背包（用来合成使用）
    //BagTypeReel,            //卷轴背包（用来产生特殊物品，如技能，符石）
    //BagTypeMedal,           //勋章背包（）
    //BagTypeOther,           //存放其它没有分类的物品(如任务道具)
    BagTypeSkill,             //技能背包
    //BagTypeSymbolstone,     //符石背包
    //BagTypeBaseaction,      //基本动作背包
    //BagTypeCommunityaction, //社交背包
    //BagTypeSocialaction,    //社群背包
    //BagTypeStore,           //仓库
    //BagTypeTrade,           //交易背包
    BagTypeHotkey,            //热键背包
    //BagTypeProduceItem,     //制造背包(存放原料的）
    //BagTypeUpgradeEquip,    //打造背包(升级装备的魔法材料;装备)
    BagTypeFunction,
    BagTypeActionUI,
    BagTypeMountSkill,        // 坐骑背包技能
	BagTypeExpressionAction,  // 表情动作
    BagTypeMax,               //最多的背包类型
};

enum ProduceItemPos
{ //制造界面中的位置
    ItemPos_Material1,
    ItemPos_Material2,
    ItemPos_Material3,
    ItemPos_Tool
};

//元素定义
//enum enumElement
//{        
//    ELEMENT_FIRE = 0,
//    ELEMENT_ICE, 
//    ELEMENT_CLOUD,
//    ELEMENT_THUNDER,
//    ELEMENT_LIGHT,
//    ELEMENT_DARK,
//    eElement_Max
//};
//

enum enumCharStorage
{ //角色仓库的定义
    STORAGE_ITEMGRID_MAX  = 90,                      // 每个仓库最大格子数
    STORAGE_MOUNTGRID_MAX = 6 ,                      // 坐骑仓库最大格子数
    PAGESIZE = 48,                                   // 每页的格子数目
    STORAGE_MAX = 30,                                // 整个游戏世界最大仓库数目
    STORAGE_ITEMMAX_IN_GRIDS = 99,                   // 每个仓库每个格子最大存储物品数目
    STORAGE_MAX_PAGE = STORAGE_ITEMGRID_MAX / PAGESIZE, // 仓库的最大页数
};

enum enumPwd
{
    PWD_OF_ITEM = 20,
    PWD_OF_STORAGE = 20
};         

enum EHeadPic
{    //玩家头像
    HeadPic_Male = 0,   //男性头像
    HeadPic_Female = 1, //女性头像
};

enum ECharFightStatus
{
    PeaceStatus = 0, //和平模式    
    FightStatus = 1, //战斗模式
};

enum ESitStatus
{
    StandStatus = 0, //站立
    SitStatus = 1,   //坐着
};

enum EBodyStatus
{
    BodyStatusType_Max = 32,
    /*
    BodyStatus_Max = 4
    ,BodyStatus_Poison    = 1
    //中毒
    //逻辑效果：每秒扣血
    //显示效果：掉血显示为绿色
    //？扣血是否固定，还是有不同的中毒程度
    //,BodyStatus_Chaos
    //混乱，操作不受控制，角色到处乱动，不能攻击
    ,BodyStatus_Frost    = 1<<1            
    //冰冻
    //逻辑效果：移动缓慢，攻击缓慢（速度全部减半）
    //显示效果：人物颜色变为深蓝色            
    ,BodyStatus_Stone    = 1<<2
    //石化
    //逻辑效果：不能移动，不能攻击
    //显示效果：人物显示类似石像
    ,BodyStatus_Sleep    = 1<<3
    //昏睡
    //逻辑效果：不能移动，不能攻击，被攻击解除状态
    //显示效果：可否有昏睡动作？头顶显示ZZZZZ
    */        
};

enum EBodyType
{ //角色身体类型
    BODYTYPE_MICRO = 0, //微型
    BODYTYPE_MINI     , //小型
    BODYTYPE_MIDDLE   , //中型
    BODYTYPE_LARGE    , //大型
    BODYTYPE_HUGE     , //巨型
    BODYTYPE_MAX      ,
};

enum EDefColor
{ //装备特效的颜色
    COLOR_RED = 0,                        // 红色
    COLOR_BLUE,                            // 蓝色
    COLOR_TEAL,                            // 青色                    
    COLOR_PURPLE,                        // 紫色
    COLOR_YELLOW,                        // 黄色
    COLOR_ORANGE,                        // 橙色
    COLOR_GREEN,                        // 绿色
    COLOR_PINK,                            // 粉红色
    COLOR_GRAY,                            // 灰色
    COLOR_LIGHTBLUE,                    // 亮蓝色
    COLOR_DARKGREEN,                    // 暗绿色
    COLOR_BROWN,                        // 棕色
};

//物品各种改变(合成，精练，强化)
enum enumItemProcess
{
    ITEMTYPE_INTENSIFY = 18,    //强化次数
};

enum EOwnAttribute
{
    EOA_show_repute_name = 0,
    EOA_Max
};

enum PublicMessageType
{
    PMT_TEACHER,
    PMT_STUDENT,
};

enum EScriptType
{
    ST_NPC = 0               , // NPC触发
    ST_QUEST                 , // 任务触发
    ST_LEVELUP               , // 等级触发
    ST_MONSTER_DEAD          , // 怪物死亡触发
    ST_USE_ITEM              , // 使用道具触发
    ST_INTO_AREA             , // 进入区块触发
    ST_LEAVE_AREA            , // 离开区块触发
    ST_REAL_TIME             , // 真实时间触发
    ST_GAME_TIME             , // 游戏时间触发
    ST_ONLINE                , // 上线触发
    ST_CREATE_CHAR           , // 创建玩家
    ST_CHAR_DEAD             , // 玩家死亡
    ST_GRAPHICCODE_CHECKRIGHT, // 玩家图形验证码成功
    ST_DelayTime             , // 延迟时间执行脚本
    ST_OFFLINE               , // 下线触发
    ST_CANCELQUEST           , // 取消任务时触发
//    ST_BANGUILD              , // 帮派踢人的时候调用
    ST_GAMESTAGE             , // 副本场景
    ST_CHALLENGE             , // 个人擂台脚本
    ST_MARRIAGE              , // 结婚脚本
	ST_PKBATTLE				 , //阵营副本
    ST_TEAMBATTLER           , // 小队混战脚本
    ST_LEAVEGUILD            , // 离开公会
    ST_GUIDEQUEST            , // 指引任务
    ST_TEACHERSTUDENT        , // 师徒脚本
    ST_NPC_DEAD              , // Npc死亡触发
    ST_MAX                   , // 最大
    ST_UNKNOW = -1           , // 未知
};

enum GamePropertyEnum
{
    HP,
    MP,
    LEVEL,
};

//状态有害类型
enum EStatusNegativeType
{
    SNT_GIDDY       ,   // 眩晕
    SNT_STAND       ,   // 定身
    SNT_SLOWDOWN    ,   // 减速
    SNT_TORPID      ,   // 沉默
    SNT_HURT        ,   // 持续伤害
    SNT_ATTR        ,   // 降低人物属性
    SNT_AFRAID      ,   // 恐惧
    SNT_MaxCount    ,   // 
};

enum EInstantMovingType
{
    IMT_None,            // 不瞬移
    IMT_Forward,        // 向前瞬移
    IMT_Backwards,        // 向后瞬移
    IMT_TargetBack        // 瞬移到背后
};

enum ETrafficType
{
    TT_Land,  // 陆地
    TT_Water, // 水上
    TT_Sky,   // 空中
};

enum EBoolValue
{
    BV_NeedTellClientCharInfo    = 1,
    BV_NotNeedTellClientCharInfo = 0,
    BV_NeedUseMessageMapInfo     = 1,
    BV_NotNeedUseMessageMapInfo  = 0,
    BV_LocalFlyMap               = 1,
    BV_NotLocalFlyMap            = 0,
    BV_SendMessage               = 1,
    BV_NotSendMessage            = 0,
    BV_FullHp                    = 1,
    BV_NotFullHp                 = 0,
    BV_SendUpAttrInfo            = 1,
    BV_NotSendUpAttrInfo         = 0,
    BV_ForSaveDb                 = 1,
    BV_NotForSaveDb              = 0,
};

enum EExitType
{
    ET_ExitGame,              // 正常退出
    ET_SwitchGameServer,      // 切换服务器
    ET_ReturnCharacterServer, // 返回角色登录服务器
    ET_BeKick,                // 正常被踢除游戏 走保存 走流程
    ET_ExceptionKick,         // 异常踢除游戏   不保存 不走流程
};

enum EAckEnterWorld
{
    Server_Ok = 0,
    Server_Busy = 1,
    Server_Full = 2,
    Server_LoginInfoError = 3,
};

enum ESaveType
{
    EST_None,          // 无状态
    EST_ExitWorld,     // 退出游戏世界的时候
    EST_ExitGameServer,// 退出一台服务器的时候
    EST_Time,          // 定时
};

enum EBattleType
{
    BATTLE_ATTACK = -1,
    BATTLE_NORMAL = 0,
    BATTLE_GUARD  = 1
};

enum ETeamPosition
{
    ETP_None,          // 无
    ETP_Leader,        // 队长
    ETP_ManipleLeader, // 小队长
    ETP_Member,        // 队员
};

enum EPlatformQueryType
{
    ECT_XinShouCard       = 0, // 新手卡                 ( 没有 0, 领过了 11, 1(原来的新手卡), 2(新的新手卡) )
    ECT_17173Card         = 1, // 17173特权卡            ( 没有 0, 领过了 11, 有 22            )
    ECT_ZhiZunCardLevel   = 2, // 至尊卡等级             ( 1, 2, 3, 4, 5 ,6                    )
    ECT_ZhiZunVipGift     = 3, // 至尊Vip卡礼包          ( 没有 0, 领过了 11, 1, 2, 3, 4, 5 ,6 )
    ECT_HuiGuiGift        = 4, // 老玩家回归礼包         ( 没有 0, 领过了 11, 1, 2             )
    ECT_ChongZhiFirstGift = 5, // 首次充值礼包           ( 没有 0, 领过了 11, 有 22            )
    ECT_ChongZhiBackGift  = 6, // 多冲多送冲值返还等级段 ( 没有 0, 领过了 11, 1, 2, 3, 4       )
};

/*! \brief 玩家处于防沉迷系统中的状态
*
*  
*
*/
enum  AntiAddictionState{
    enumAntiAddictionStateNormal    = 0,  //!< 正常时间
    enumAntiAddictionStateTired     = 1,  //!< 疲劳时间
    enumAntiAddictionStateRest      = 2,  //!< 不健康时间
};


//////////////////////////////////////////////////////////////////////////
// 结构体
#pragma pack(push,1)


// 游戏场景
struct SGameStage
{
    SGameStage()
    {
        bIsRun = true;
    }

    bool bIsRun;
    unsigned long  ulStageId;     
    unsigned short usPlayerCount; // 当前场景中玩家人数
};

// 游戏场景Op
struct SGameStageOp 
{
    enum OpType
    {
        OT_Update,
        OT_Remove,
    };

    enum EGameStageInfoType
    {
        GSIT_MapSetting,
        GSIT_RunStage,
    };

    char op;
    char gameStageInfoType; 
    SGameStage gs;
};

#define SHOP_ITEM_MAXCOUNT    100           // 商店最大物品个数
struct SShopItem
{ // 道具
    SShopItem():nId(-1), nCurCount(0), nMaxCount(0), nBasePrice(0),
        dwSellPrice(0), dwBuyPrice(0) {}

    int   nId;              // 物品ID
    int   nCurCount;        // 当前数量
    int   nMaxCount;        // 物品最大数量
    int   nPerCount;        // 每次出售的最大数量
    int   nBasePrice;       // 原始价格
    DWORD dwSellPrice;      // 出售价格
    DWORD dwBuyPrice;       // 收购价格
    unsigned char costType; // 价格类型
    unsigned short costItemID; // 物品买卖时,需要的物品ID
    bool  bIsBound;         // 是否绑定
};

struct SChannelInfo
{
    char szChannelName[MAX_NAME_STRING];

    unsigned long nServerId;
};

struct SServerInfo
{
    char nServerType;
    unsigned long nServerId;
};

struct SLoginInfoBase
{
    SLoginInfoBase()
    {
        memset( this, 0, sizeof(*this));
    }

    char         szIP[IP_LENGTH+1];          // IP
    int          nAccountID;                 // 账号ID
    unsigned int LoginTime;                  // 登陆时间
    char         szAccount[MAX_NAME_STRING]; // 登陆账号
    char         SessionKey[32+1];           // SessionKey
    char         Password[50];               // 密码
    char         Seed[50];                   // 种子
    int8         isWallow;                   // 是否成年
    bool operator == (SLoginInfoBase &other) { return strcmp(SessionKey,other.SessionKey)==0;}
    bool operator == (const char* other) { return strcmp(SessionKey,other)==0; }
};

struct SBurthenBase
{
    unsigned int nCurrentPlayerCount;
    unsigned int nMaxPlayerCount;
    unsigned int nGateCount;
};

struct SStageReqInfo
{
    SStageReqInfo()
    {
        bHaveInvalidInfo = false;
        nServerId        = ErrorUnsignedLongID;
    };

    unsigned long nServerId;
    unsigned long nMapId;
    float         fX;
    float         fY;
    float         fDir;
    bool          bHaveInvalidInfo;
};

struct SRankManager
{
    SRankManager()
    {
        memset(this,0,sizeof(SRankManager));
    }

    struct SRank
    {
        BYTE first;
        BYTE second;

        void WriteRank(CDataChunkWriter *w);
        void ReadRank(BYTE* bybuff,DWORD dwsize);            
    };
    void clear()
    {
        memset(this,0,sizeof(SRankManager));
    }

    void Write(BYTE idx,BYTE value)
    {
        int nIndex = idx/2;
        if ( nIndex<0 || nIndex>=16)
            return;
        
        if (idx%2)
            rankArray[nIndex].second = value;
        else
            rankArray[nIndex].first = value;
    }

    BYTE Read(WORD idx)
    {
        int nIndex = idx/2;
        if ( nIndex<0 || nIndex>=16)
            return 0;
        if (idx%2)
            return rankArray[idx/2].second;
        else
            return rankArray[idx/2].first;
    }

    SRank rankArray[16];

    void WriteRankManager(CDataChunkWriter *w);
    void ReadRankManager(BYTE* bybuff,DWORD dwsize);
};

struct SElement
{ // 元素属性
    unsigned short item_stAtt;
    unsigned short item_stDef;
    unsigned short exec_stAtt;
    unsigned short exec_stDef;
    unsigned short status_stAtt;
    unsigned short status_stDef;
    unsigned short final_Att;
    unsigned short final_Def;

    SElement()
    {
        item_stAtt = 0;
        item_stDef = 0;
        exec_stAtt = 0;
        exec_stDef = 0;
        final_Att = 0;
        final_Def = 0;
        status_stAtt = 0;
        status_stDef = 0;
    }
    void UpdateFinal_Att( )
    {
        final_Att = item_stAtt+status_stAtt+exec_stAtt;
        if (final_Att < 0)
        {
            final_Att = 0;
        }
    }
    void UpdateFinal_Def( )
    {
        final_Def = item_stDef+status_stDef+exec_stDef;
        if (final_Def < 0)
        {
            final_Def = 0;
        }
    }
    unsigned short GetFinal_Def( )
    {
        if (final_Att < 0)
        {
            final_Att = 0;
        }
        return final_Def = item_stDef+status_stDef+exec_stDef;
    }
    unsigned short GetFinal_Att( )
    {
        if (final_Def < 0)
        {
            final_Def = 0;
        }
        return     final_Att = item_stAtt+status_stAtt+exec_stAtt;
    }

    void WriteElement(CDataChunkWriter *w);
    void ReadElement(BYTE* bybuff,DWORD dwsize);
}; 

struct SAreaRepulation
{
    enum EConstDefine
    {
        ECD_Max_Value = 500,
    };

    SAreaRepulation()
    {
        Reset();
    };

    short nMapID;
    int nCurrentReputation;
    int nMaxReputation;

    void Reset()
    {
        nMapID             = -1;
        nCurrentReputation = 0;
        nMaxReputation     = ECD_Max_Value;
    }
};

// 称号属性
class TitleData
{
public:
    TitleData() : m_ustTitleID( 0 ), m_n64AcquireTime( 0 ), m_nActiveTime( 0 ){ }
    TitleData( unsigned short ustTitleID, __int64 n64AcquireTime, unsigned int nActiveTime )
        : m_ustTitleID( ustTitleID ), m_n64AcquireTime( n64AcquireTime ), m_nActiveTime( nActiveTime ) { }

    bool operator == ( const TitleData& xData ) { return m_ustTitleID == xData.GetTitleID(); }
    bool operator == ( unsigned short ustTitleID ) { return m_ustTitleID == ustTitleID; }
    friend bool operator == ( const TitleData& xLeft, const TitleData& xRight ){ return xLeft.GetTitleID() == xRight.GetTitleID(); }
    friend bool operator ==( const TitleData& xData, unsigned short ustTitleID ) { return xData.GetTitleID() == ustTitleID; }

    unsigned short GetTitleID() const  { return m_ustTitleID; }
    __int64 GetAcquireTime() const     { return m_n64AcquireTime; }
    unsigned int GetActiveTime() const { return m_nActiveTime; }

    void SetTitleID( unsigned short ustValue ) { m_ustTitleID = ustValue; }
    void SetAcquireTime( __int64 n64Value )    { m_n64AcquireTime = n64Value; }
    void SetActiveTime( unsigned int nValue )  { m_nActiveTime = nValue; }


    // 判断是否已经过期
    bool IsPassLimitTime()
    {
        if ( m_nActiveTime == 0 )       //  = 0 永远不过期
        { return false; }

        TimeEx xStartTime( m_n64AcquireTime );
        TimeSpan xTimeSpan( static_cast< DWORD >( m_nActiveTime ) );
        xStartTime += xTimeSpan;

        return TimeEx::IsPassCurrentTime( xStartTime.GetTime() );
    }

private:
    unsigned short m_ustTitleID;        // 称号ID
    __int64 m_n64AcquireTime;           // 称号获得的时间
    unsigned int m_nActiveTime;         // 称号的有效时间  = 0 永久有效
};

// 师门属性
class MasterData
{
public:
    MasterData() : m_uchMasterLevel( 1 ), m_dwMasterValue( 0 ){}

    unsigned char GetMasterLevel() const { return m_uchMasterLevel; }
    DWORD GetMasterValue() const { return m_dwMasterValue; }

    void SetMasterLevel( unsigned char uchValue ) { m_uchMasterLevel = uchValue; }
    void SetMasterValue( DWORD dwValue ) { m_dwMasterValue = dwValue; }
private:
    unsigned char m_uchMasterLevel;     // 师门等级
    DWORD m_dwMasterValue;              // 威望值
};

// 物品ColdDown属性
#define MAX_RESTORE_COUNT 200
#define MAX_SAVERESTORE_COUNT 50
struct SColdDown
{
    SColdDown()
    {
        m_ustType = 0;
        m_dwStartTime = 0;
        m_dwPeriod = 0;
    }

    bool IsEmpty() { return m_ustType == 0 || m_dwStartTime == 0 || m_dwPeriod == 0; }

    unsigned short m_ustType;
    DWORD          m_dwStartTime; // 开始时间
    DWORD          m_dwPeriod;    // 周期
};

struct SCharBaseInfo
{
    struct SCharAptotic
    {
        SCharAptotic()
        { memset( this, 0, sizeof( SCharAptotic ) ); }

        int8   szCharacterName[ dr_MaxPlayerName ]; // 名字
        uint8  ucSex;                               // 性别
        uint16 usProfession;                        // 角色职业
        uint8  ucHeadPic;                           // 角色的头像
        uint8  ucCountry;                           // 国家        
        int8   szYearName[dr_MaxYearName];          // 出生年的名字
        uint8  byYear;                              // 出生年
        uint8  byMonth;                             // 出生月
        uint8  byDay;                               // 出生日
    };

    struct SCharLiveInfo
    {
        SCharLiveInfo()
        {
            memset( this, 0, sizeof( SCharLiveInfo) );
            for ( int i=0; i<MAX_AREAREPULATION_COUNT; ++i )
            { xArea[i].Reset(); }
        }

        uint16          ustLevel;                             // 等级
        uint32          dwMoney;                              // 游戏金钱
        uint32          reputation;                           // 声望值
        uint32          exploit;                              // 功勋值
        uint32          honour;                               // 荣誉值
        uint32          battleScore;                          // 战场积分
        uint32          dwCountryScore;                       // 国战积分
        uint32          jinDing;                              // 金锭
        uint32          jinPiao;                              // 金票
        uint32          dwHelpFlag;                           // 泡泡提示
        uint32          nHighShoutCount;                      // 当天的喊话次数
        int             nHp;                                  // 血量
        int             nMp;                                  // 魔量
        int             nXp;                                  // XP值
        int64           dwExp;                                // 当前经验
        int64           dwExpNotUsed;                         // 未使用的经验
        uint32          dwSkillExp;                           // 技能经验        [不用]
        uint32          dwSkillExpNotUsed;                    // 未使用的技能经验[不用]
        uint16          ustSkillExpForSkillID;                // 要升级的技能ID  [不用]
        uint8           ucNormalBagSize;                      // 实际普通背包的开放个数
        uint8           ucMaterialBagSize;                    // 实际材料背包的开放个数
        uint8           ucMountCount;                         // 坐骑个数
        uint16          activity;                             // 活力 (生产消耗)
        uint16          activityMax;                          // 活力最大值 45+人物等级(ILevel)*5
        uint16          vigor;                                // 精力 (采集消耗)
        uint16          vigorMax;                             // 精力最大值 45+人物等级(ILevel)*5
        uint32          dwOnlineTime;                         // 玩家总在线时间( 单位; 分钟 )
        uint32          dwRewardItemInfo;                     // 玩家在线时长领取奖励的信息( 最大可以32次, 32位 每一位的数值 0 = 没有领取, 1 = 已经领取过 )
        
        int16           nCurrentTitleID;                      // 当前称号
        uint16          nCountryTitle;                        // 国家称号( 这个不需要保存在数据库 )
        TitleData       xTitleData[MAX_TITLE_COUNT];          // 称号列表
        SAreaRepulation xArea[MAX_AREAREPULATION_COUNT]; 
        MasterData      xMasterData;                          // 师门属性
        uint32          jiaoZi;                               // 交子
        SColdDown       xItemColdDown[MAX_SAVERESTORE_COUNT]; // 物品的colddown时间

        uint16          nRecipeSkillNum;                      // 生活技能个数
        uint16          nSkillPoint[ ERT_MaxType ];           // 各种生产生活技能熟练度

        uint8           nStorageItemGrid ;                    // 仓库物品格子数量
        uint8           nStorageMountGrid;                    // 仓库坐骑格子数量
    }; 
    
    SCharBaseInfo()
    {
        memset( &aptotic,  0, sizeof( SCharAptotic ));
        memset( &liveinfo, 0, sizeof( SCharLiveInfo ));

        for ( int i = 0; i < MAX_AREAREPULATION_COUNT; ++i )
        {
            liveinfo.xArea[i].Reset();
        }
    };

    SCharAptotic  aptotic;
    SCharLiveInfo liveinfo;
    SBaseProperty baseProperty; // [ 不用入库 ]
};

struct SSocietyRelation 
{ // 关系
    SSocietyRelation()
    {
        memset( szPlayer, 0, sizeof(szPlayer) );
        Stype = 0;
    }
    DWORD Stype;                      // 社会关系
    char  szPlayer[dr_MaxPlayerName]; // 名字
};

struct SCharItem
{
    enum EConstDefine
    {
        EConstDefine_BaseRandMaxCount   = 7, // 基本附加随机
        EConstDefine_PurpleRandMaxCount = 3, // 紫色附加随机
        EConstDefine_GemHoleMaxCount    = 4, // 最大的镶嵌空位
        EConstDefine_SuitRandMaxCount   = 1, // 套装的精炼附加随机 技能套装精炼以后
    };

    enum EEquipEvolveConstDefine
    {
        EEquipEvolve_SoulStampAddition  = 50, // 装备铭刻加成
    };

    enum ELevel
    {
        EL_Min    = 0 ,
        EL_Notice = 9 , // 大于9级全服公告
        EL_StarMax= 10, // 装备最高10星
        EL_Max    = 18,
    };

    enum EUseType
    {
        EUT_None,
        EUT_AutoUse,
        EUT_Other,
    };

    enum EEquipDataFlagType
    {
        EEquipDataFlagType_SoulStamp = 1 << 0, // 是否灵魂铭刻
        EEquipDataFlagType_Bounded   = 1 << 1, // 是否绑定
        EEquipDataFlagType_Lock      = 1 << 2, // 是否锁定
    };

    struct SItemBaseInfo
    {
        SItemBaseInfo() { memset( this, 0, sizeof(SItemBaseInfo) ); }

        uint16  ustItemID                      ; // 物品ID
        __int64 nOnlyInt                       ; // 物品世界唯一ID
        int16   stPacketIdx                    ; // 背包的位置
        uint16  ustItemCount                   ; // 个数
        uint32  value1                         ; // 数值  装备的五行属性在value1的后8位   宝箱直接用这个的值
        __int64 n64UseTime                     ; // 物品使用的到期时间lo
        uint32  nLeftTime                      ; // 物品使用的剩余时间( 不用存储到数据库, 每次角色上线计算一次, 不能客户端计算, 时区不同, 取出来的本地时间会不同 )
        uint32  value2                         ; // 数值，可以改变，如HP,MP
        uint8   useType                        ; // 使用类型 0 无类型 1 激活自动使用 2 以后用
        char    szCreaterName[dr_MaxPlayerName]; // 拥有者的名字
        uint8   flag                           ; // 标志位 参考 EEquipDataFlagType
    };

    struct SEquipData
    {   // 物品的扩展属性 装备时，是物体的特殊属性 道具时，是物体的个数
        // 每个道具的属性只能由7项目  special0 ~ special6 (uint8 )
        // 针对不同的道具，不同的道具有不同的属性说明
        // (武器, 衣服, 鞋子, 手套, 头盔, 饰品 )
        // 如果该项数值为0表示该项目无效!!
        SEquipData() { memset( this, 0, sizeof(SEquipData) ); }

        float  usHP           ;                                 // 装备耐久度
        int32  usHpMax        ;                                 // 装备耐久度最大值
        uint16 baseRands  [ EConstDefine_BaseRandMaxCount   ];  // 基本附加随机属性
        uint16 purpleRands[ EConstDefine_PurpleRandMaxCount ];  // 紫色附加随机属性
        uint16 suitRands  [ EConstDefine_SuitRandMaxCount   ];  // 技能套装附加随机属性
        uint16 gemIds     [ EConstDefine_GemHoleMaxCount    ];  // 嵌套宝石
        uint8  gemHoleCount   ;                                 // 装备打孔数
        uint8  ucLevel        ;                                 // 装备星级
        uint8  quality        ;                                 // 装备品质
    };

    struct SStorageInfo
    {   
        SStorageInfo() { memset( this, 0, sizeof(SStorageInfo) ); }

        bool  bIsLocked;     // ( 这个不知道为啥是用来判断客户端锁住不让操作的变量 )
        int32 nStorageNpcId; // NPCid 仓库存储之用
    };

    struct SLockInfo
    {
        SLockInfo() { memset( this, 0, sizeof(SLockInfo) ); }

        __int64 n64UnLockTime;   // 解锁的到期时间( 锁定状态 和 解锁状态这个值为 0 )
        uint32  nUnLockLeftTime; // 解锁剩余时间( 服务器计算, 用来给客户端显示 )
    };

    SCharItem()
    {
        memset( this, 0, sizeof(SCharItem) );
        bCanUse = true;
    }

    const bool operator==( const SCharItem& stItem ) const
    {
        //if( memcmp( this, &stItem, sizeof(SCharItem) ) == 0 )
          //  return true;
        if (itembaseinfo.ustItemID == stItem.itembaseinfo.ustItemID && itembaseinfo.nOnlyInt == stItem.itembaseinfo.nOnlyInt)
            return true;
        return false;
    }

    const bool operator!=( const SCharItem& stItem ) const
    {
        return !( *this == stItem );
    }

    const bool Included( const SCharItem& stItem ) const 
    {
        if( itembaseinfo.ustItemID == stItem.itembaseinfo.ustItemID )
        {
            if( itembaseinfo.ustItemCount >= stItem.itembaseinfo.ustItemCount )
                return true;
        }
        return false;
    }

    unsigned short GetItemID()   { return itembaseinfo.ustItemID; }
    void           SetItemID( unsigned short ustValue ){ itembaseinfo.ustItemID = ustValue; }
    unsigned short GetItemCount(){ return itembaseinfo.ustItemCount; }
    void           SetItemCount( unsigned short ustValue ) { itembaseinfo.ustItemCount = ustValue; }
    __int64        GetItemGuid() { return itembaseinfo.nOnlyInt; }
    bool           IsEmpty()     { return ( itembaseinfo.ustItemID == InvalidLogicNumber || itembaseinfo.nOnlyInt == InvalidLogicNumber || itembaseinfo.ustItemCount == 0 ); }
    void           Clear()       { itembaseinfo.ustItemID = InvalidLogicNumber; itembaseinfo.nOnlyInt = 0; itembaseinfo.ustItemCount = 0; }
    void           SetItemGuid( __int64 n64Value ) { itembaseinfo.nOnlyInt = n64Value; }

    // 设置五行套装的五行属性 五行装备才有效
    void          SetElements( unsigned char chValue ) { itembaseinfo.value1 = ( itembaseinfo.value1 & 0xFFFFFF00 ) | chValue; }
    unsigned char GetElements() { return static_cast< unsigned char >( itembaseinfo.value1 & 0xFF ); }

    // 五行套装和技能套装
    void SetSuitLevel( unsigned char chValue )       // 设置套装装备强化等级
    { 
        if ( chValue == 0 )
        {
            itembaseinfo.value1 = ( itembaseinfo.value1 & 0xFFFF00FF ); 
        }
        else
        {
            itembaseinfo.value1 = ( itembaseinfo.value1 & 0xFFFF00FF ) | ( chValue << 8 ); 
        }
    }     
    unsigned char GetSuitLevel() { return static_cast< unsigned char >( ( itembaseinfo.value1 & 0xFF00 ) >> 8 ); }       // 获得套装装备强化等级

    //装备星级
    void SetStarLevel( bool bRandom, uint8 nStarLevel )
    {
        if (nStarLevel == 0 ||  nStarLevel >= EL_StarMax)
        { return; }

        if (bRandom)
        { equipdata.ucLevel = theRand.rand16() % nStarLevel; }
        else
        { equipdata.ucLevel = nStarLevel; }
    }

    bool IsOverdue( bool bSetLeftTime = false );
    bool IsSoulStamp() { return _HAS_FLAG( itembaseinfo.flag, EEquipDataFlagType_SoulStamp); } // 是否被灵魂铭刻
    bool IsBounded()   { return _HAS_FLAG( itembaseinfo.flag, EEquipDataFlagType_Bounded  ); } // 是否被绑定
    bool IsLock()      { return _HAS_FLAG( itembaseinfo.flag, EEquipDataFlagType_Lock     ); } // 是否被锁定

    unsigned char GetSoulStampAddition() { return IsSoulStamp() ? EEquipEvolve_SoulStampAddition : 0 ; } //物品经过铭刻后，会提升基础属性的50%

    void SetSoulStamp( bool bValue ) 
    {
        if ( bValue )
        { _SET_FLAG( itembaseinfo.flag, EEquipDataFlagType_SoulStamp ); }
        else
        { _CLS_FLAG( itembaseinfo.flag, EEquipDataFlagType_SoulStamp ); }
    }

    void SetBounded( bool bValue )
    {
        if ( bValue )
        { _SET_FLAG( itembaseinfo.flag, EEquipDataFlagType_Bounded ); }
        else
        { _CLS_FLAG( itembaseinfo.flag, EEquipDataFlagType_Bounded ); }
    }

    void SetLock( bool bValue )
    {
        if ( bValue )
        { _SET_FLAG( itembaseinfo.flag, EEquipDataFlagType_Lock ); }
        else
        { 
            _CLS_FLAG( itembaseinfo.flag, EEquipDataFlagType_Lock ); 
            xLockInfo.n64UnLockTime = 0;
            xLockInfo.nUnLockLeftTime = 0;
        }
    }

    bool IsPassUnLockTime( bool bSetLeftTime = false );

    void    SetUnLockTime( __int64 n64Time ) { xLockInfo.n64UnLockTime = n64Time; }
    __int64 GetUnLockTime() { return xLockInfo.n64UnLockTime; }

    void   SetUnLockLeftTime( uint32 nLeftTime ) { xLockInfo.nUnLockLeftTime = nLeftTime; }
    uint32 GetUnLockLeftTime() { return xLockInfo.nUnLockLeftTime; }

    void Write( CDataChunkWriter *w);
    void Read( BYTE* bybuff,DWORD dwsize );

    void ReadItemBaseInfo(ReadData inP,int nSize);
    void ReadEquipInfo   (ReadData inP,int nSize);
    void ReadStorgeInfo  (ReadData inP,int nSize);
    void ReadLockInfo    ( ReadData inP,int nSize );

    bool          bCanUse;     // 只做为逻辑，不作为存储
    SItemBaseInfo itembaseinfo;
    SEquipData    equipdata;
    SStorageInfo  storageinfo;
    SLockInfo     xLockInfo;
};

inline bool SortItemID( const SCharItem& left, const SCharItem& right )
{
    return ( left.itembaseinfo.ustItemID < right.itembaseinfo.ustItemID) ? true : false;
}

struct SCharSkill
{ // 玩家身上技能的定义
    SCharSkill()
    { Reset(); }

    void Reset()
    {
        memset(this, 0, sizeof(SCharSkill));
        bAvailable    = true;
    }

    void write( CDataChunkWriter* w );
    void read ( BYTE* buffer,DWORD size );

    short          stSkillLevel;    // 等级
    unsigned short ustSkillID;      // 技能ID
    DWORD          dwCurSkillExp;   // 技能经验
    bool           bAvailable;

    unsigned int   nColdTime;       // 剩余的冷却时间
};

struct SMountItem
{
    enum EConstDefine
    {
        MICD_MaxSkillCount = 12,        // 坐骑技能个数
        MICD_InitiativeSkillIndex = 0,  // 主动技能槽开始索引
        MICD_PassiveSkillIndex    = 6,  // 被动技能槽开始索引

        MICD_MountBreedGeneration = 0,  // 坐骑繁殖代数
        MICD_MountBreedQuality    = 2,  // 坐骑繁殖品质
    };

    struct SBaseInfo
    {
        SBaseInfo()
        { Reset(); }
        
        void Reset()
        {
            memset( this, 0, sizeof( SBaseInfo));
        }

        void ResetAttibute()
        {
            memset( baseAttribute,     0, sizeof(baseAttribute     ));
            memset( aptitudeAttribute, 0, sizeof(aptitudeAttribute ));
            memset( potentialAttribute,0, sizeof(potentialAttribute));
            memset( currentAttribute,  0, sizeof(currentAttribute  ));
        }

        SBaseInfo& operator= ( const SBaseInfo& v )
        {
            if ( this != &v )
            {
                id           = v.id;
                guid         = v.guid;
                isActive     = v.isActive;
                level        = v.level;
                exp          = v.exp;
                hp           = v.hp;
                hpMax        = v.hpMax;
                savvy        = v.savvy;
                generation   = v.generation;
                nextId       = v.nextId;
                quality      = v.quality;
                nPotentialPoint = v.nPotentialPoint;
                memcpy( baseAttribute, v.baseAttribute, sizeof(float) * EBaseAttr_MaxSize );
                memcpy( aptitudeAttribute, v.aptitudeAttribute, sizeof(float) * EBaseAttr_MaxSize );
                memcpy( potentialAttribute, v.potentialAttribute, sizeof(float) * EBaseAttr_MaxSize );
                memcpy( currentAttribute, v.currentAttribute, sizeof(float) * EBaseAttr_MaxSize );
                strncpy_s( szName, sizeof(szName), v.szName, sizeof(szName)-1 );
            }
            return *this;
        }

        void UpdateCurrentAttribute()
        {
            for ( int i=0; i<EBaseAttr_MaxSize; ++i)
            { 
                //旧公式： 坐骑当前的属性值 = 坐骑初始的属性值 + （等级-1）*（初始属性^0.16/(12.5^0.16)+成长率）* 增值 
                //currentAttribute[i] = baseAttribute[i] + (level-1) * ( pow( (float)baseAttribute[i], (float)0.16) / pow( (float)12.5, (float)0.16) + growRate ) * aptitudeAttribute[i];

                //新公式： 坐骑当前的属性值 = 坐骑初始的属性值 + （等级-1） + 分配的潜能
                currentAttribute[i] = baseAttribute[i] + (level-1) + potentialAttribute[i];
            }
        }

        void Write( CDataChunkWriter* w );
        void Read( BYTE* szBuff,DWORD nSize );

        char        szName[ dr_MaxPlayerName ];     // 名字
        uint16      id;                             // 坐骑种类ID
        int64       guid;                           // 物品世界唯一ID
        uint8       isActive;                       // 是否被激活
        uint16      level;                          // 等级
        int64       exp;                            // 经验
        int16       hp;                             // 坐骑生命
        uint16      hpMax;                          // 坐骑生命最大值
        uint16      savvy;                          // 悟性
        uint8       generation;                     // 几代
        uint16      nextId;                         // 下一代马ID
        uint8       quality;                        // 品质

        int		       nPotentialPoint;                // 可分配潜力点
        float          baseAttribute[EBaseAttr_MaxSize];        // 基础初始属性
        float          aptitudeAttribute[EBaseAttr_MaxSize];    // 资质属性
        float          potentialAttribute[EBaseAttr_MaxSize];   // 已分配潜力点
        float          currentAttribute[EBaseAttr_MaxSize];     // 当前属性
    };
    
    struct SSkillInfo
    {
        SSkillInfo()
        { memset( this, 0, sizeof( SSkillInfo)); }

        bool              AddSkill    ( unsigned short skillId, unsigned short skillLevel = 1, uint8 beginIndex = 0 );
        bool              ReplaceSkill( unsigned short skillId, unsigned short skillLevel, int nIndex );
        bool              RemoveSkill ( unsigned short skillId );
        const SCharSkill* GetSkill    ( unsigned short skillId );
        int               GetCurrentSkillCount();
        void Reset();

        void Write( CDataChunkWriter* w );
        void Read( BYTE* szBuff, DWORD nSize );

        SCharSkill skills[MICD_MaxSkillCount]; // 技能
        int16      initiativeSkillNumber;      // 开启主动技能槽个数
    };

    struct LockInfo
    {   
        LockInfo() : bIsLocked( false ), n64UnLockTime( 0 ), nUnLockLeftTime( 0 ){}

        void Write( CDataChunkWriter* w );
        void Read( BYTE* szBuff, DWORD nSize );

        bool bIsLocked;         // 物品是否加锁
        __int64 n64UnLockTime;  // 解锁的到期时间( 锁定状态 和 解锁状态这个值为 0 )
        uint32 nUnLockLeftTime;
    };


    unsigned short GetMountID() const { return baseInfo.id; }
    __int64 GetMountGuid() const { return baseInfo.guid; }
    const char* GetMountName() const { return baseInfo.szName; }

    bool IsPassUnLockTime( bool bSetLeftTime = false );
    bool IsLock() { return xLockInfo.bIsLocked; }
    void SetLock( bool bValue )
    {
        xLockInfo.bIsLocked = bValue;
        xLockInfo.n64UnLockTime = 0;
    }
    __int64 GetUnLockTime() { return xLockInfo.n64UnLockTime; }
    void SetUnLockTime( __int64 n64Time ) { xLockInfo.n64UnLockTime = n64Time; }

    void SetUnLockLeftTime( uint32 nLeftTime ) { xLockInfo.nUnLockLeftTime = nLeftTime; }
    uint32 GetUnLockLeftTime() { return xLockInfo.nUnLockLeftTime; }

    bool IsCanBreed()
    {
        if ( baseInfo.generation != MICD_MountBreedGeneration )
        { return false; }

        if ( baseInfo.quality < MICD_MountBreedQuality )
        { return false; }

        return true;
    }

    void Write( CDataChunkWriter* w);
    void Read( BYTE* bybuff,DWORD dwsize );

    SBaseInfo  baseInfo;
    SSkillInfo skillInfo;
    LockInfo xLockInfo;
};

// 战车类道具
struct SPanzerItem
{
    enum EPanzerConstDefine
    {
       PCD_PanzerLoadMaxSize    = 6,
       PCD_PanzerSkillMaxSize   = 5,
    };

    SPanzerItem() 
    { memset( this, 0, sizeof( SPanzerItem)); }

    void Write( CDataChunkWriter* w );
    void Read( BYTE* szBuff,DWORD nSize );

    struct SBaseInfo
    {
        SBaseInfo()
        { Reset(); }

        void Reset()
        { memset( this, 0, sizeof( SBaseInfo)); }

        char          szName[dr_MaxPlayerName];
        uint16        id            ;
        uint8         type          ;
        uint8         level         ;
        uint8         takeLevel     ;
        int           nHp           ;
        int           nMp           ;
        uint32        nHpMax        ;
        uint32        nMpMax        ;
        uint16        defendShort   ;
        uint16        defendLong    ;
        uint8         repairCount   ;
        uint8         repairMaxCount;
        uint8         loadNumber    ;
        float         moveSpeed     ;
        int64         guid          ;

        void Write( CDataChunkWriter* w );
        void Read( BYTE* szBuff,DWORD nSize );
    };
    
    struct SSkillInfo
    {
        SSkillInfo()
        { memset( this, 0, sizeof( SSkillInfo)); }

        void Write( CDataChunkWriter* w );
        void Read( BYTE* szBuff, DWORD nSize );

        SCharSkill    skills[PCD_PanzerSkillMaxSize]; // 技能
    };

    struct LockInfo
    {   
        LockInfo() : bIsLocked( false ), n64UnLockTime( 0 ), nUnLockLeftTime( 0 ){}

        void Write( CDataChunkWriter* w );
        void Read( BYTE* szBuff, DWORD nSize );

        bool bIsLocked;         // 物品是否加锁
        int64 n64UnLockTime;    // 解锁的到期时间( 锁定状态 和 解锁状态这个值为 0 )
        uint32 nUnLockLeftTime;
    };

    SBaseInfo  baseInfo ;
    SSkillInfo skillInfo;
    LockInfo   lockInfo ;
};

struct SCharSkills
{
    SCharSkills()
    { }

    void write(CDataChunkWriter* w);
    void read(BYTE* bybuff,DWORD dwsize);

    SCharSkill skill[ More_iMaxSkillKnown ];
};
 
enum EEquipPartType
{
    EEquipPartType_Helmet            , // 头盔
    EEquipPartType_Armour            , // 铠甲
    EEquipPartType_Glove             , // 护手
    EEquipPartType_Shoe              , // 鞋子
    EEquipPartType_Weapon            , // 主武器(只显示此位置)
    EEquipPartType_WeaponMinor       , // 次武器
    EEquipPartType_Badge             , // 徽章
    EEquipPartType_Ring1             , // 戒指1
    EEquipPartType_Ring2             , // 戒指2
    EEquipPartType_Bangle1           , // 手镯1
    EEquipPartType_Bangle2           , // 手镯2
    EEquipPartType_Manteau           , // 披风
    EEquipPartType_Necklace          , // 项链
    EEquipPartType_Sash              , // 腰带
    EEquipPartType_LeaderCard        , // 掌门卡
    EEquipPartType_Amulet            , // 护身符
    EEquipPartType_AecorativeGoods   , // 装饰的物品
    EEquipPartType_AecorativeClothing, // 装饰的衣服

    EEquipPartType_MaxEquitPart      , // 最大可装备个数
};

struct SCharVisual
{
    enum EShowFlagType
    {
        EShowFlagType_Aecpratove = 1 << 0, // 是否显示时装
        EShowFlagType_Helmet     = 1 << 1, // 是否显示头盔
    };

    uint16    hairId;                                   // 头发模型Id
    uint16    faceId;                                   // 脸部模型Id    
    uint8     showFlag;                                 // EShowFlagType
    float     fModelPercent;                            // 模型缩放百分比
    SCharItem equipitem[ EEquipPartType_MaxEquitPart ]; // 身上装备的道具

    SCharVisual()
    {
        hairId        = 0;
        faceId        = 0;
        showFlag      = 0;
        fModelPercent = 1.0f;
    }

    SCharItem* GetVisual( uint8 part )
    {
        if ( part >= EEquipPartType_MaxEquitPart)
        { return NULL; }
        return &equipitem[ part ];
    }

    SCharItem* GetVisualArray()
    { return equipitem; }

    bool IsShowAecorative() 
    { return _HAS_FLAG( showFlag, EShowFlagType_Aecpratove); } // 是否显示时装

    bool IsShowHelmet()
    { return _HAS_FLAG( showFlag, EShowFlagType_Helmet); } // 是否显示头盔

    void ShowAecorative( bool bShow )
    {      
        if ( bShow )
        { _SET_FLAG( showFlag, EShowFlagType_Aecpratove ); }
        else
        { _CLS_FLAG( showFlag, EShowFlagType_Aecpratove ); }
    }

    void ShowHelmet( bool bShow )
    { // 显示头盔
        if ( bShow )
        { _SET_FLAG( showFlag, EShowFlagType_Helmet ); }
        else
        { _CLS_FLAG( showFlag, EShowFlagType_Helmet ); }
    } 
    
    void WriteVisual ( CDataChunkWriter* w);
    void ReadVisual ( uint8* bybuff, uint32 dwsize );
};

struct SCharStorageData
{
    typedef std::vector<SCharItem>      ItemSortContainer;
    typedef ItemSortContainer::iterator ItrItemSortContainer;

    uint32 dwStorageMoney;          // 仓库里的钱
    SCharItem   stStorageItems[STORAGE_ITEMGRID_MAX] ;
    SMountItem  xStorageMounts[STORAGE_MOUNTGRID_MAX];

    SCharItem* GetItemByIndex( int nIndex )
    {
        if ( nIndex < 0 || nIndex >= STORAGE_ITEMGRID_MAX )
        { return NULL; }

        if ( stStorageItems[nIndex].itembaseinfo.ustItemID == InvalidLogicNumber || stStorageItems[nIndex].itembaseinfo.nOnlyInt == InvalidLogicNumber )
        { return NULL; }

        return &( stStorageItems[nIndex] );
    }

    SMountItem* GetMountByIndex( int nIndex )
    {
        if ( nIndex < 0 || nIndex >= STORAGE_MOUNTGRID_MAX )
        { return NULL; }

        if ( xStorageMounts[nIndex].baseInfo.id == InvalidLogicNumber || xStorageMounts[nIndex].baseInfo.guid  == InvalidLogicNumber )
        { return NULL; }

        return &( xStorageMounts[nIndex] );
    }

    void CleanUp()
    {
        ItemSortContainer items;
        for(int i = 0; i< STORAGE_ITEMGRID_MAX ; ++i)
        {
            if( stStorageItems[i].itembaseinfo.ustItemID == InvalidLogicNumber || stStorageItems[i].itembaseinfo.nOnlyInt == 0 )
                continue;

            items.push_back( stStorageItems[i] );

            stStorageItems[i].itembaseinfo.ustItemID = InvalidLogicNumber;
            stStorageItems[i].itembaseinfo.nOnlyInt  = 0;
            stStorageItems[i].bCanUse = false;
        }

        sort( items.begin(), items.end(), SortItemID);

        ItrItemSortContainer it    = items.begin();
        ItrItemSortContainer itEnd = items.end();
        for (int i=0; i< STORAGE_ITEMGRID_MAX && it != itEnd; ++it, ++i)
        {
            stStorageItems[i] = *it;
            stStorageItems[i].itembaseinfo.stPacketIdx = i;
        }
    }
};

struct SBattleResult
{ //战绩
    short shVictory; //胜利
    short shDraw;    //平局
    short shFail;    //失败
};

struct SGameWorldTime
{ //游戏时间
    short shYear;
    short shMonth;
    short shDay;
    short shHour;
    short shMinute;
};

struct SValueChanged
{
    union uData
    {  
        __int64 n64Value;
        uint32  dwValue;
        float   fValue;
        short   stValue;
        int     nValue;
    };
    unsigned short ustWhichAttr;
    uData          data;
};

struct SCharPosData
{
    uint32      dwMapID;
    int16       stX;
    int16       stY;
    D3DXVECTOR3 vPos;

    void WritePosData (CDataChunkWriter *w);
    void ReadPosData (BYTE* bybuff,DWORD dwsize);
};

enum EMail
{  
    EM_MoneySendMax        = 200 * 10000,      // 最多寄200金
    EM_MailMaxCount        = 100,              // 收件箱可保存邮件的上限为100封    
    EM_MailFullNotifyCount = 90,               // 邮箱容量超过90封系统提示清理邮箱    
    EM_AddressNameSize     = dr_MaxPlayerName, // 地址
    EM_HoldMailDays        = 30,               // 邮箱里的存放时间
    EM_MailFee             = 50,               // 每份邮件的邮资    
    EM_MailContentMax      = 50 * 2,           // 每份邮件的最大字符数    
    EM_TileMaxCount        = 32,               // 邮件标题
    EM_MailAccessorySize   = 300,              // 附件大小
    EM_FromMaxCount        = 1,                // 发信人的个数
    EM_ToMaxCount          = 1,                // 目标最大个数
    EM_OtherSendMaxCount   = 6,                // 抄送
    EM_TargetMaxCount      = EM_ToMaxCount + EM_OtherSendMaxCount,
    EM_OwnerMaxCount       = EM_FromMaxCount + EM_TargetMaxCount,

    EM_FromIndex           = 0,                              // 发信人在数组中的位置
    EM_ToIndex             = EM_FromIndex + EM_FromMaxCount, // 收信人在数组中的位置
    EM_OtherIndex          = EM_ToIndex + EM_ToMaxCount,     // 抄送人在数组中的位置
};  

enum EMailOp
{
    EMO_None,         // 无操作
    EMO_Delete,       // 删除邮件
    EMO_Open,         // 打开邮件
    EMO_GetMoney,     // 得钱
    EMO_GetAccessory, // 得附件
};

struct SMail
{ // 邮件
    enum EMailType
    {
        EMT_System, // 系统邮件
        EMT_Player, // 玩家邮件
    };

    enum EMailState
    {
        EMS_NotOpen    = 0,  // 未打开
        EMS_Open       = 1,  // 打开
        EMS_HaveGetItem = 2, // 已经获得
    };

    enum EAccessoryType
    {
        EAT_None,  // 无 无附件
        EAT_Item,  // 道具
        EAT_Mount, // 马
    };

    enum ETargetAddressResult
    {
        ETAR_Success,        // 成功 
        ETAR_TargetNotExit,  // 目标不存在
        ETAR_TargetMailFull, // 目标邮件已经满
    };

    struct SAddress
    {
        int8   addressName[ EM_AddressNameSize ]; // 角色名
        uint32 charDbId;                          // 角色DbId
    };

    // 目标结果
    struct SAddressResult
    {
        uint8           result;  // 结果
        SMail::SAddress address; // 所有人的地址        
    };

    struct SAccessory
    {
        uint8 type;                          // 附件类型
        uint8 content[EM_MailAccessorySize]; // 附件
    };

    SMail()
    { Reset(); }

    void Reset()
    { memset( this, 0, sizeof(SMail) ); }

    int32      id;                         // 邮件Id
    uint8      type;                       // 邮件类型
    uint8      state;                      // 邮件状态
    int8       title[EM_TileMaxCount];     // 标题
    SAddress   owners[EM_OwnerMaxCount];   // 所有人的地址
    int8       content[EM_MailContentMax]; // 邮件内容
    uint32     money;                      // 寄钱
    time_t     sendTime;                   // 邮寄时间
    SAccessory accessory;                  // 附件类型
};

struct SDBMail 
{
    enum EDeleteState
    {
        EDS_NotDelete = 1,
        EDS_Delete    = 0,
    };

    SDBMail()
    {
        deleteState = 0;
    }

    SMail  baseInfo;    // 
    uint16 deleteState; // 删除的情况 占32个位置
};

struct SShortCut
{
    int BagType;  // 所在的背包的类型
    int BagIndex; // 所在的背包中的位置

    SShortCut() : BagType(-1), BagIndex(-1)
    { }

    void writeShortCut(CDataChunkWriter *w);
    void readShortCut(BYTE* bybuff,DWORD dwsize);
};

struct SHotKey 
{
    SShortCut  ShortCut;

    void writeMouseItem(CDataChunkWriter *w);
    void readMouseItem(BYTE* bybuff,DWORD dwsize);  
};

//对应的拾取权限
struct SPickAccessInfo
{
    uint32 dwPlayerDBID;
    uint8 chPickAccess;     // 权限 (位或的关系)

    bool operator == (uint32 dwID) { return dwPlayerDBID == dwID; }
};

struct SMouseItem
{ //在mouse上记录的item数据
    //enum
    //{
    //    TypeNull,     // 表示鼠标上为空，没有任何道具
    //    TypeFactItem, // 表示鼠标上记录的是真的道具数据
    //    TypeNotItem,  // 表示鼠标上记录的不是真的道具数据，是技能，等。。。
    //};
    //unsigned short type;
    SCharItem  ItemData;
    SShortCut  ShortCut;    
    void writeMouseItem(CDataChunkWriter *w);
    void readMouseItem(BYTE* bybuff,DWORD dwsize);        
};

// 热键
struct SCharHotKeys
{
    SHotKey itemHotKey[More_iHotkey];

    void writeCharHotKeys(CDataChunkWriter *w);
    void readCharHotKeys(BYTE* bybuff,DWORD dwsize);        
};

struct SSysVars
{
    SSysVars()
    { memset( szVars, 0, sizeof( szVars )); }

    void writeVars( CDataChunkWriter *w );
    void readVars( ReadData inP,int nSize );

    short szVars[ More_iMaxVars ];
};

struct SCharBuff
{ //关于状态的数据
    enum StatusEventType
    {
        StatusEventType_Other,
        StatusEventType_Skill,
    };

    int16   StatusID;        // 该状态的id编号    
    int16   iLevel;          // 附加该状态的等级(如果 <= 0 表示没有附加状态)
    int16   stMasterID;      // 该状态的释放者的ID    
    int     nEffectID;       // 客户端在特效管理器内的ID
    uint8   bLastEffect;     // 是否最后一个特效
    uint32  dwStartTime;     // 开始时间
    uint32  dwPreDamage;     // 上次进行伤害的时间
    uint32  dwDurationTime;  // 状态持续时间
    int     restoreType;     // 存储类型
    uint32  dwPlayerDBID;    // 释放者的DBID
    __int64 nInt64StartTime; // 未来失效时间
    uint8   bStop;           // 是否停止
    uint8  eventType    ;   // 触发该状态的类型
    uint16 eventValue   ;   // 触发该状态的值

    SCharBuff()
    { Reset(); }

    void Reset()
    {
        StatusID             = -1;
        iLevel               = -1;
        stMasterID           = -1;
        dwStartTime          = 0;
        dwPreDamage          = 0;
        nEffectID            = -1;
        bLastEffect          = false;
        dwDurationTime       = 0;
        restoreType           = false;
        dwPlayerDBID         = 0;
        nInt64StartTime      = -1;
        bStop                = 0;
        eventType            = 0;
        eventValue           = 0;
    }

    void WriteBodyStatus( CDataChunkWriter *w       );
    void ReadBodyStatus ( BYTE* bybuff,DWORD dwsize );
};

struct SCharOtherDataClient0
{
    SCharPosData  pos;
    SCharPosData  sBornPos;
    void WriteOtherDataClient0(CDataChunkWriter *w);
    void ReadOtherDataClient0 (BYTE* bybuff,DWORD dwsize);
};

struct SCharItemBagData
{
    SCharItemBagData()
    { }

    SCharItem  stPackItems[ITEM_BAGMAX];
    SCharItem  ciMaterialItems[ITEM_BAGMATERIAL_MAX];
    SCharItem  ciTaskItems[ITEM_BAGTASK_MAX];
    SMountItem miItems[ITEM_MOUNT_MAXCOUNT];
};

//称号任务要用的记数
struct TitleCounter
{
    TitleCounter() : titleid(0), type(0), value(0), count(0) { }
   
    void Clear()
    {
        titleid = 0;
        type = 0;
        value = 0;
        count = 0;
    }

    bool IsEmpty() { return titleid == 0; }

    const unsigned short GetTitleID() const { return titleid; }
    const unsigned short GetType() const { return type; }
    const unsigned int GetValue() const { return value; }
    const unsigned int GetCount() const { return count; }

    void AddCount(unsigned short nCount) { count += nCount; }
    void SetCount(unsigned short nCount) { count = nCount; }

    void Write( CDataChunkWriter* w );
    void Read( BYTE* szBuff, DWORD nSize );

    unsigned short titleid;
    unsigned short type;
    unsigned int value;
    unsigned int count;
};

struct SRunTimeInfoToDB
{
    SRunTimeInfoToDB()
    {
        nEneryTime = 0;
        nMountActionTime = 0;
    }

    void Write (CDataChunkWriter *w);
    void Read( BYTE* buffer, DWORD size );

    uint32 nEneryTime;                // 活力累计时间
    uint32 nVigorTime;                // 精力累计时间
    uint32 nMountActionTime;          // 坐骑生命累计时间
};

struct SpecialQuestInfo
{
    SpecialQuestInfo() : nNpcID( 0 ), dwTime( 0 ) { }

    void Write (CDataChunkWriter *w);
    void Read( BYTE* buffer, DWORD size );

    unsigned int nNpcID;
    unsigned int dwTime;
};

struct SPressKeySuit
{
    SPressKeySuit() { memset( this, 0, sizeof(SPressKeySuit)); }

    void Write (CDataChunkWriter *w);
    void Read( BYTE* buffer, DWORD size );

    char    keySuitName [ dr_MaxPlayerName ];               // 一键换装名
    int64   equipitem   [ EEquipPartType_MaxEquitPart ];    // 装备的GUID
};

enum ECharTimeVar
{
    ECT_LastLoginTime       ,   // 上次登录时间
    ECT_LastOfflineTime     ,   // 上次下线时间
    ECT_ChangeCountryTime   ,   // 上次更改国籍时间
    ECT_ExploitTime         ,   // 功勋值更改时间

    ECT_MaxTimeVar  =   20  ,   // 人物身上的时间计数变量
};

struct SExtendData
{
    SExtendData()
    { memset( this, 0, sizeof(SExtendData) ); }

    void          AddTitleCounter(TitleCounter& xcounter); 
    void          RemoveTitleCounter(short nTitleID);
    TitleCounter* GetTitleCounterByIndex(short nIndex);
    TitleCounter* GetTitleCounterByTitleID(short nID);
    TitleCounter* GetTitleCounterByConditionType(short nType, short nID);
    
    void Write (CDataChunkWriter *w);
    void Read( BYTE* buffer, DWORD size );

    SRunTimeInfoToDB xRunTime;  // 运行时数据
    TitleCounter     nTitleCounters[MAX_TITLE_COUNT];       // 人物称号记数
    SpecialQuestInfo xPubQuestInfo[MAX_SPECIALQUEST_COUNT]; // 记录酒馆任务时间信息
    SpecialQuestInfo xConQuestInfo[MAX_SPECIALQUEST_COUNT]; // 记录征伐任务间信息
    unsigned long    dwGuideQuestInfo;                      // 引导任务的完成情况

    bool             isOfflineHook   ;                      // 上一次是否离线挂机
    uint32           totalHookTime   ;                      // 累计离线挂机时间

    SPressKeySuit    xPressKeySuit[MAX_PRESSKEYSUIT_COUNT]; // 一键换装

    int64            n64TimeVars[ECT_MaxTimeVar];           // 时间计数变量
};

struct SCharOtherDataClient : public SCharOtherDataClient0
{ 
    SCharOtherDataClient()
    {
        memset( recipes,           0, sizeof(recipes) );
        chProtectLockTime = 1;
        dwBanSpeakTime    = 0;
    }

    // 添加玩家背包 需要UpDataItemPackInfo
    void writeOtherdataClient(CDataChunkWriter *w);
    void readOtherdataClient(BYTE* bybuff,DWORD dwsize);
    void readFightData(ReadData inP,int nsize);

    SCharSkills          skills;         // 技能背包
    SCharHotKeys         hotkeys;        // 热键背包            
    short                stMountId;      // 当前正在骑着的坐骑Id [<0没有骑坐骑 >0 一定骑着坐骑栏里出战的坐骑]
    float                fDirX;          // 朝向X -1 默认
    float                fDirY;          // 朝向Y 0
    SCharBuff sCharBodyStatus[BodyStatusType_Max]; // 状态
    unsigned short       recipes[MAX_RECIPE_COUNT];           // 人物配方
    unsigned char        chProtectLockTime;                   // 交易保护时间( 单位分钟 )   
    unsigned long        dwBanSpeakTime;                      // 禁言时间    ( 单位分钟 )
};

struct SCharOtherData : public SCharOtherDataClient
{
    SCharOtherData()
    {
        dwHighShoutCDTime = 0;
        dwRecordKillMonsterTime = 0;
        dwRecordKillMonsterCount = 0;
        nRecordHonourTime = 0;
        nRecordHonourCount = 0;
        nGuildID = 0;
        dwLeaveGuildTime = 0;
    }

    void WriteOtherDataBlob (CDataChunkWriter *w);
    void ReadOtherDataBlob (BYTE* bybuff,DWORD dwsize);
    void ReadOtherImport(ReadData inP,int nsize);
    
    SSysVars      vars;                        // 服务端系统变量
    bool          bNewChar;                    // 是否为新建角色
    unsigned long dwHighShoutCDTime;           // 世界喊话冷却剩余时间    
    unsigned int  dwRecordKillMonsterTime;     // 记录杀怪的最后时间
    unsigned int  dwRecordKillMonsterCount;    // 记录杀怪的个数

    unsigned int   nRecordHonourTime;          // 记录最后得到荣誉的时间
    unsigned short nRecordHonourCount;         // 记录每日荣誉值

    SecondPassword xSecondPassword;            // 玩家2级密码

    unsigned int nGuildID;                     // 公会ID  
    unsigned int dwLeaveGuildTime;             // 离开帮派的时间
};

struct SCharAchieve
{
    SCharAchieve() { memset( this, 0, sizeof(SCharAchieve)); }

    void Write (CDataChunkWriter *w);
    void Read( BYTE* buffer, DWORD size );

    uint8   finishState ;   
    int64   finishTime  ;
};

struct SAchieveData
{
    SAchieveData() { memset( this, 0, sizeof(SAchieveData)); }

    void Write( CDataChunkWriter *w );
    void Read ( BYTE* buffer, DWORD size );

    uint32           achievePoint;  // 成就点数
    uint32           achieveVars  [More_iMaxAchieveVars] ;
    SCharAchieve     xAchievements[MAX_ACHIVEVMENT_COUNT]; // 人物成就
};

struct SCharInfoClient
{ // 客户端的角色数据
    SCharBaseInfo        baseinfo;
    SCharVisual          visual;
    SCharOtherDataClient otherdataclient;
    SCharItemBagData     ItemBagData;
};

struct SCharDBInfo
 { // 角色数据 DB 级别
    SCharBaseInfo    baseinfo;   // 基本数据
    SCharVisual      visual;     // 角色外观
    SCharOtherData   otherdata;  // 额外数据
    SCharItemBagData itemData;   // 背包数据
    SExtendData      extendData; // 扩充数据
    SAchieveData     achieveData;// 成就数据
};

struct RunTimePetInfo
{
    enum EPetType
    {
        Type_Pet = 0, // 宠物
        Type_Protect, // 保护怪
        Type_Max,
    };

    RunTimePetInfo()
    { 
        nPetID      = 0;
        nPetSkillID = -1;
        nHp         = 0;
        nMp         = 0;
        varValue    = -1;
        memset( sCharBodyStatus, 0, sizeof(SCharBuff) * BodyStatusType_Max );
    }

    int                  nPetID;
    int                  nPetSkillID;
    int                  nHp;
    int                  nMp;
    int                  varValue; // 变量值
    SCharBuff sCharBodyStatus[BodyStatusType_Max]; // 状态
};

struct SRuntimeInfo
{ 
    SRuntimeInfo()
    {
        mountId                = 0;
        dwProtectLockLeaveTime = 0;
        dwUpdatePKValueTime    = 0;
        inFightTime            = 0;
        dwOnLineTime           = 0;
        onlineMinuteTimeForWallow = 0;
        offMinuteTimeForWallow    = 0;

        // add by zhangqi 2010-7-7
        _antiAddicationState = enumAntiAddictionStateNormal;
        _bLoopAntiState      = false;

        bReqRemoveMarriage = false;
        bForceRemove = false;
        nCountrySpeakSpaceTime = 0;
    }
    // 角色数据 Runtime 级别
    short mountId;             // 当前正在骑着的坐骑Id [<0没有骑坐骑 >0 一定骑着坐骑栏里出战的坐骑]

    unsigned int   dwProtectLockLeaveTime; // 交易保护剩余时间 ( == 0,已经到了锁定时间 )
    int            nCountrySpeakSpaceTime; // 国家发言冷却时间
    unsigned int   dwUpdatePKValueTime;    // 在线泡PK点时间
    RunTimePetInfo xPetInfo[EPT_Max];      // 1:技能宠物  2:保护怪 3:捕获宠物

    uint32         inFightTime;            // 在战斗中的时间
    uint32         dwOnLineTime;           // 角色本次在线时间 ( 单位: 毫秒 ) 

    SCharItem      xBuyBackItem[10];          // 回购物品列表
    uint32         onlineMinuteTimeForWallow; // 在线单位分钟
    uint32         offMinuteTimeForWallow;    // 下线单位分钟

    //add by zhangqi 2010-7-7
    AntiAddictionState	_antiAddicationState; //防沉迷状态
    bool                _bLoopAntiState;       //是否开始轮询防沉迷状态

    // 离婚请求数据
    bool bReqRemoveMarriage;
    bool bForceRemove;
};

struct SAttrUp
{
    char  cType;
    short stWhichAttr;
};

struct SEffectDamage
{
    short stWho;
    DWORD dwState;
    short stDamage;
};

struct SAttTargetResult
{
    SAttTargetResult()
    { Reset(); }

    void Reset()
    { memset( this, 0, sizeof( SAttTargetResult));}

    short stTargetWho;        // 攻击的目标
    short stAttackerWho;      // 谁是攻击者

    int   stTagHpNum;         // 目标跳出的Hp
    int   stSrcHpNum;         // 攻击者跳出的Hp

    int   stTagMpNum;         // 目标跳出的Mp
    int   stSrcMpNum;         // 攻击者跳出的Mp

    int   nTagHp;             // 被攻击目标剩下的hp
    int   nSrcHp;             // 攻击者hp

    int   nTagMp;             // 被攻击目标剩下的Mp
    int   nSrcMp;             // 攻击者Mp

    short stTagBackAttackNum; // 目标受背击跳出的数值

    char  cBalanceType;       // 法术应用的结算方式
    short ucStatus;           // 状态特征flag
};

struct PublicMessageDd
{ // 445 
    char          type;                         // 消息类型
    unsigned long playerDbId;                   // 角色db id
    char          playername[dr_MaxPlayerName]; // 角色名字
    short         level;                        // 等级
    short         profession;                   // 职业
    unsigned long time;                         // 发布时间
    char          addonInfo[4*100];             // 附加信息
};
enum sides
{
    e_blue = 0,
    e_red = 1,
    e_max
};

struct sKillPerSonTime 
{
    DWORD dwPlayerDBid;
    int nPlayerTimes;
    DWORD dwBeKilledTime;
};
typedef std::map<DWORD,sKillPerSonTime*> mapPersonkill;
//sbw_reputerank
//struct SReputeRank
//{
//    SReputeRank()
//    {
//        ::ZeroMemory(this,sizeof(SReputeRank));
//    }
//    DWORD current:4;
//    DWORD level:4;
//    DWORD skillId:8;
//    DWORD flags:16;
//    SReputeRank getReputeRankInf(DWORD    dw)
//    {
//        ::CopyMemory(this,&dw,sizeof(DWORD));
//        return *this;
//    }
//    void    sv_openrepute(WORD id,WORD level = 0);        //打开一个旗标
//    void    sv_setcurrent(WORD id,WORD level);                //设置当前的头衔信息
//    void    sv_save(DWORD*    pdw);                                //保存
//};


struct SQuestReward
{ // 任务回报
    SQuestReward()
    {
        Value = -1;
        shSex = Sex_Max;
        shProfession = -1;
        byType = 0;
        Number = 0;
        Icon   = 0;
        bIsBound = true;
        bIsStarRandom = false;
        nStarLevel = 0;
    }
    BYTE    byType; // 类型
    int     Number; // 数值
    int     Value;  // 名字值Id
    short   shSex;        // 奖励的道具物品的性别
    short   shProfession; // 奖励的道具物品的
    int     Icon;         // 奖励的道具的图标  
    bool    bIsBound     ;// 是否绑定
    bool    bIsStarRandom;// 是否随机星级
    short   nStarLevel   ;// 最大星级

    void ClearReward()
    {
        Value = -1;
        shSex = Sex_Max;
        shProfession = -1;
        byType = 0;
        Number = 0;
        Icon = 0;
    }
};

struct SQuestRequirement
{
    SQuestRequirement()
    {
        byType = 0;
        wVar = InvalidLogicNumber;
        MaxNum = 0;
        Value = InvalidLogicNumber;
    }
    BYTE    byType; // 类型
    WORD    wVar;   // 变量的ID
    WORD    MaxNum; // 任务需求最大数值
    int    Value;  //可以是道具Id,可以是值
    int    nStringID;   // 计数变量对应的字串ID，仅在选择需要类型为计数变量时存储
    
    void ClearRequirement()
    {
        byType = 0;
        wVar = 0;
        MaxNum = 0;
        Value = InvalidLogicNumber;
        nStringID = InvalidLogicNumber;
        //memset(szItem,0,dr_MaxQuestStateDesc);
    }
};

struct SQuest
{
    enum ERequirementTypes
    {
        eRequirement_Money = 0      ,             // 金钱
        eRequirement_Item           ,             // 道具
        eRequirement_Var            ,             // 任务相应的记数变量
        eRequirement_Profession     ,
        eRequirement_Level          ,
        eRequirement_Reputation     ,
        eRequirement_Sex            ,
        eRequirement_Energy         ,
        eRequirement_Monster        ,
        eRequirement_Quest          ,
        eRequirement_Time           ,
        eRequirement_SocialRelation ,             // 社会关系
        eRequirement_Exp            ,             // 经验值
        eRequirement_SkillExp       ,             // 技能经验
        eRequirement_Action         ,             // 行为任务，比如护送
        eRequirement_VarLimit       ,             // 记数限制( 小于记数值 可以领取任务 )
        eRequirement_WeakCountry    ,             // 弱国才能接
        eRequirement_Status         ,             // 需要状态
        eRequirement_NoStatus       ,             // 没有状态
        eRequirement_Max,
    };


    enum ERewardType
    {
        eReward_Money = 0, // 金钱
        eReward_Exp, // 经验值
        eReward_SkillExp , // 技能经验
        eReward_Item, // 道具
        eReward_Reputation,
        eReward_Exploit,        //功勋
        eReward_Title,
        eReward_Buff,
        eReward_ChangeRoleVar,
        eReward_GuildContribute,        // 奖励帮贡
        eReward_SpecialItem,            // 特别物品
        eReward_JiaoZi,                 // 交子
        eReward_Honor,                  // 奖励荣誉
        eReward_Max,
    };

    enum QuestRank
    {
        eQuestRank_Nor,  //普通
        eQuestRank_Nic,  //良好的
        eQuestRank_Exc,  //优秀
        eQuestRank_Gold, //卓越
        eQuestRank_Legend,//传说
//         eQuestRank_Epic,//史诗
        eQuestRank_Max,
    };

    enum QuestType
    {
        Type_Main = 0,      // 主线任务
        Type_Lateral,       // 支线任务
        Type_Campaign,      // 活动任务
        Type_Ectype,        // 副本任务
        Type_Official,      // 官府任务
        Type_Circle,        // 循环任务
        Type_Cruise,        // 巡城任务
        Type_Battalion,     // 军需任务
        Type_Precious,      // 藏宝任务
        Type_Title,         // 称号任务 
        Type_Gut,           // 剧情任务
        Type_Gout,          // 趣味任务
        Type_Guild,         // 帮派任务
        Type_Pub,           // 酒馆任务
        Type_Royal,         // 皇榜任务
        Type_ConQuest,      // 征伐任务
        Type_CountryKing,   // 国运任务
        Type_CountryGeneral,// 出国任务
        Type_CountryLeft,   // 天行任务
        Type_CountryRight,  // 探宝任务
        Type_Adventure,     // 奇遇任务
        Type_Achieve,       // 成就任务
        Type_End,
    };

    typedef std::vector<SQuestReward> RewardType;
    typedef std::vector<SQuestRequirement> RequirementType;
    short        Id;                        // 任务Id
    DWORD        QuestName;                 // 任务名称
    DWORD        IntroStringId;             // 任务说明
    RewardType stReward;                    // 报酬
    RequirementType stCommitRequirement;    // 任务完成的需求
    RequirementType stReceiveRequirement;   // 接受任务的需求
    bool  IsRepeat;                         // 是否重复试练
    bool  IsCancel;                         // 任务是否可被删除,重要的任务不能被删除,接任务的时候也不增加激活任务数
    BYTE  HintLevelMin;                     // 提示任务下限
    BYTE  HintLevelMax;                     // 提示任务上限
    DWORD AcceptTargetId;                   // 接任务目标
    DWORD   ReplyTargetId;                  // 交任务的NPC名称
    short   MapId;                          // 任务的地图Id
    DWORD   TargetStringId;                 // 任务目标
    bool  CanAssist;                        // 可否协助
    bool  CanShare;                         // 可否共享
    short RankId;                           // 任务品质
    unsigned char chQuestType;              // 任务类型
    bool  CanDisplay;                       // 客户端是否可显示
    bool  IsSingleRequirement;              // 完成一个条件即可完成任务
    SQuest()
    {
        QuestName = 0;
        IntroStringId = 0;
        Id = 0;
        IsRepeat = false;
        IsCancel = true;
        HintLevelMin = 0;
        HintLevelMax = 100;
        MapId = -1;
        CanAssist = true;
        CanShare = true;
        TargetStringId = 0;
        AcceptTargetId = InvalidLogicNumber;
        ReplyTargetId = InvalidLogicNumber;
        RankId = -1;
        chQuestType = Type_Main;
        CanDisplay = true;
        IsSingleRequirement = false;
    }

    const char*        GetQuestName();
    const char*        GetQuestStateInfo();
    const char*        GetRewardNpcName();
    const char*        GetAcceptNpcName();
    const char*        GetQuestInfo();

    SQuest& operator =(const SQuest& squest)
    {
        if (this == &squest)
        {
            return *this;
        }
        Id = squest.Id;
        IsRepeat = squest.IsRepeat;
        IsCancel = squest.IsCancel;
        HintLevelMin = squest.HintLevelMin;
        HintLevelMax = squest.HintLevelMax;
        MapId = squest.MapId;
        CanAssist = squest.CanAssist;
        CanShare = squest.CanShare;
        TargetStringId = squest.TargetStringId;
        QuestName = squest.QuestName;
        IntroStringId = squest.IntroStringId;
        AcceptTargetId = squest.AcceptTargetId;
        ReplyTargetId = squest.ReplyTargetId;
        RankId = squest.RankId;
        chQuestType = squest.chQuestType;

        stReward = squest.stReward;
        stCommitRequirement = squest.stCommitRequirement;
        stReceiveRequirement = squest.stReceiveRequirement;
        CanDisplay = squest.CanDisplay;
		IsSingleRequirement = squest.IsSingleRequirement;
        return *this;
    }
    
    int GetPlayerReceiveQuestLevel()
    {
        for (std::vector<SQuestRequirement>::iterator itrPlayerLevel=stReceiveRequirement.begin();itrPlayerLevel!=stReceiveRequirement.end();++itrPlayerLevel)
        {
            if (itrPlayerLevel->byType == eRequirement_Level)//eRequirement_Level
            {
                return itrPlayerLevel->Value;
            }
        }
        return 1;
    }
    int GetPlayerReceiveQuestSex()
    {
        for (std::vector<SQuestRequirement>::iterator itrPlayerLevel=stReceiveRequirement.begin();itrPlayerLevel!=stReceiveRequirement.end();++itrPlayerLevel)
        {
            if (itrPlayerLevel->byType == eRequirement_Sex)//eRequirement_Level
            {
                return itrPlayerLevel->Value;
            }
        }
        return 2;
    }
    int GetPlayerReceiveQuestProfession()
    {
        for (std::vector<SQuestRequirement>::iterator itrPlayerLevel=stReceiveRequirement.begin();itrPlayerLevel!=stReceiveRequirement.end();++itrPlayerLevel)
        {
            if (itrPlayerLevel->byType == eRequirement_Profession)//eRequirement_Profession
            {
                return itrPlayerLevel->Value;
            }
        }
        return 0xff;
    }
    int GetPlayerReceiveQuestReputation()
    {
        for (std::vector<SQuestRequirement>::iterator itrPlayerLevel=stReceiveRequirement.begin();itrPlayerLevel!=stReceiveRequirement.end();++itrPlayerLevel)
        {
            if (itrPlayerLevel->byType == eRequirement_Reputation)//eRequirement_Reputation
            {
                return itrPlayerLevel->Value;
            }
        }
        return 1;
    }
    short AddReceiveRequirement( const SQuestRequirement* pRequirement )
    {
        stReceiveRequirement.push_back(*pRequirement);

        return (short)stReceiveRequirement.size();
    }

    int RemoveReceiveRequirement( const SQuestRequirement* pRequirement )
    {
        if( stReceiveRequirement.empty() )
            return -1;
        int i = 0;
        for( std::vector<SQuestRequirement>::iterator it = stReceiveRequirement.begin();it != stReceiveRequirement.end();++it)
        {
            if(it->byType == pRequirement->byType)
            {
                stReceiveRequirement.erase(it);
                return i;
            }
            ++i;
        }

        return -1;
    }

    SQuestRequirement* GetReceiveRequirement(int Typeid,int* pBeginPos = NULL)
    {
        int nBeginPos = 0;
        if (pBeginPos)
        {
            nBeginPos = *pBeginPos;
        }

        if( stReceiveRequirement.empty() || nBeginPos >= (int)stReceiveRequirement.size())
        { return NULL; }
        int retPos = nBeginPos + 1;
        for(std::vector<SQuestRequirement>::iterator workitr = stReceiveRequirement.begin() + nBeginPos; workitr != stReceiveRequirement.end() ; ++workitr,++retPos)
        {
            if (workitr->byType == Typeid)
            {
                if (pBeginPos)
                {
                    *pBeginPos = retPos;
                }
                return &(*workitr);
            }            
        }
        return NULL;
    }
    void ClearCommitRequirement()
    {
        stCommitRequirement.clear();
    }
    void ClearReceiveRequirement()
    {
        stReceiveRequirement.clear();
    }
    void ClearReward()
    {
        stReward.clear();
    }
    short AddCommitRequirement( const SQuestRequirement* pRequirement )
    {
        stCommitRequirement.push_back(*pRequirement);
        
        return (short)stCommitRequirement.size();
    }

    int RemoveCommitRequirement( const SQuestRequirement* pRequirement )
    {
        if( stCommitRequirement.empty() )
            return -1;
        int i = 0;
        for( std::vector<SQuestRequirement>::iterator it = stCommitRequirement.begin();it != stCommitRequirement.end();++it)
        {
            if(it->byType == pRequirement->byType)
            {
                stCommitRequirement.erase(it);
                return i;
            }
            ++i;
        }

        return -1;
    }
    SQuestRequirement* GetCommitRequirementt(int Typeid)
    {
        if( stCommitRequirement.empty() )
            return NULL;
        for(std::vector<SQuestRequirement>::iterator workitr = stCommitRequirement.begin() ; workitr != stCommitRequirement.end() ; ++workitr)
        {
            if (workitr->byType == Typeid)
            {
                return &(*workitr);
            }
        }
        return NULL;
    }
    
    int AddReward( const SQuestReward* pReward )
    {
// 		for (std::vector<SQuestReward>::iterator iter = stReward.begin(); iter != stReward.end(); ++iter)
// 		{
// 			if ((*iter).byType > pReward->byType)
// 			{
// 				stReward.insert(iter,*pReward);
// 				return stReward.size();
// 			}
// 		} 排序，根据小胖建议去掉
        stReward.push_back(*pReward);
        return (int)stReward.size();
    }

    int RemoveReward( const SQuestReward* pReward )
    {
        int i = 0;
        for (std::vector<SQuestReward>::iterator it = stReward.begin(); it != stReward.end();++it)
        {
            if (it->byType == pReward->byType)
            {
                stReward.erase(it);
                return i;
            }
            ++i;
        }
     
        return -1;
    }
    SQuestReward* GetReward(int Typeid)
    {
        if( stReward.empty() )
            return NULL;
        for(std::vector<SQuestReward>::iterator workitr = stReward.begin() ; workitr != stReward.end() ; ++workitr)
        {
            if (workitr->byType == Typeid)
            {
                return &(*workitr);
            }
        }
        return NULL;
    }

    bool IsPubQuest() { return ( chQuestType == Type_Pub || chQuestType == Type_Royal ); }
    bool IsConQuest() { return chQuestType == Type_ConQuest; }
};

struct SGameProperty
{
    short stLevel;
    int   nHp;
    int   nMp;
};

struct SProcessTime
{
    char* szFunctionName;
    __int64 nTime;
};
    
struct SMovePos 
{
    float fX;      // 世界坐标的X轴
    float fY;      // 世界坐标的Y轴
    float fZ;      // 世界坐标的Z轴
    float fV;      // 行走速度百份比(1为正常).如0.8,1.2之类的
    float fStep;   // 步长
    int   nAction; // 到达目标点时所做的动作(1~n)
    DWORD dwTime;  // 到达目标点时所停留的时间(毫秒).
};

typedef std::vector<SMovePos> MovePosContainer;

struct SRoute
{
    unsigned int     mapId      ; // 地图Id
    unsigned int     routeId    ; // 路点Id
    unsigned int     nextMapId  ; // 下一张地图
    unsigned int     nextRouteId; // 下一个路点
    unsigned int     flyRoute   ; // 是否是飞行路径
    MovePosContainer allMovePos ; // 所有路点
};

struct SAttackTarget 
{ // 保存，目标数据，每个动作，需要的目标在这里
    bool bIsCharTarget; // 判断攻击的目标是对地面还是特别的npc
    int  nCharID;       // 作用目标的ID
    D3DXVECTOR3 vPos;   // 作用目标的位置
};

////////////////////////////////////////////////////////////////////////////////////////////////

// TellClient 参数联合体
union UnionParam
{
    unsigned long nValue;
    float fValue;
    char szValue[dr_MaxPlayerName];
};

struct ItemDropControl
{
    ItemDropControl()
    {
        dwControlCount = 0;
        dwDropCount    = 0;
    }

    uint32 dwControlCount;      // 当前阈值数
    uint32 dwDropCount;         // 已经出了的个数
};
typedef std::map< uint16, ItemDropControl > MapItemDropControl;
typedef MapItemDropControl::iterator MapItemDropControlIter;

const uint32 gJiFengItemValueMaxCount = 10;
const uint32 gJiFengItemSnMaxCount    = 32;
const uint32 gJiFengGainMaxCount      = 20;

struct SJiFengItemRecordPlatform
{
    int8   sn[gJiFengItemSnMaxCount+1];     // 订单号
    uint8  itemType;                        // 物品类型
    uint16 itemId;                          // 物品id
    uint16 itemCount;                       // 物品个数
    uint16 value[gJiFengItemValueMaxCount]; // 附加属性
};

struct SJiFengItemRecordServer
{
    uint32                    id;   // id 自增
    SJiFengItemRecordPlatform info; // 基本信息
};
typedef std::vector<SJiFengItemRecordServer> JiFengItemServerContainer;
typedef JiFengItemServerContainer::iterator  ItrJiFengItemServerContainer;

struct SJiFengItemRecordClient
{
    uint32 id;
    uint8  itemType;                        // 物品类型
    uint16 itemId;                          // 物品id
    uint16 itemCount;                       // 物品个数
    uint16 value[gJiFengItemValueMaxCount]; // 附加属性
};

//定义阵营枚举
enum enumBattleInfluence
{	
    enumBattleInfluence_Max  = 0, 
	enumBattleInfluence_Red	 = 1,		//红方, 阵营战场中的唐军
	enumBattleInfluence_Blue = 2,		//蓝方, 阵营战场中的隋军
};

//定义下阵营战场的常量
enum enumBattleConst
{	
	enumBattleConst_ResourcePosNum	= 5, 	//资源点个数
};

//定义下阵营战场资源枚举, 待定
enum enumBattleResouce
{
	enumBattleResource_Beast	= 0,	//兽栏
	enumBattleResource_Farm		= 1,	//农场
	enumBattleResource_Steel    = 2,	//铁矿
	enumBattleResource_Wood		= 3,	//木材
	enumBattleResource_Gold		= 4,	//矿洞
	enumBattleResource_Max		= 5,
};

//////////////////////////////////////////////////////////////////////////
//  排行榜
enum enumRankType
{
    EPersonalRank_Level     = 101,  // 个人等级排行
    EPersonalRank_Rich      = 102,  // 个人财富排行
    EPersonalRank_Honour    = 103,  // 个人荣誉排行
    EPersonalRank_Reputation= 104,  // 个人声望排行
    EPersonalRank_Dedicate  = 105,  // 个人帮贡排行
    EPersonalRank_Glamour   = 106,  // 个人魅力排行
    EPersonalRank_PK        = 107,  // 个人红名排行
    EPersonalRank_Kill      = 108,  // 个人杀敌排行

    EGuildRank_Score        = 201,  // 帮会积分排行

    ECountryRank_Strength   = 301,  // 国家实力排行

    EEctypeRank_JiangZhou   = 401,  // 江州法场排行

};

//start add by ZhangQi 防沉迷系统 for 2010/07/07


/*! \brief 各种时间持续的长度，和提示间隔
*
*  
*
*/
struct AntiTime{
    uint32	_playTime;    //!< 时间持续长度，单位为分钟
    uint32  _notifyTime;  //!< 提示的间隔，单位为分钟
};

/*! \brief 防沉迷系统各个时间段配置值
*
*  
*
*/
struct AntiAddictionTime{
    AntiTime _normal;  //!< 正常时间
    AntiTime _tired;   //!< 疲劳时间
    AntiTime _rest;	   //!< 不健康时间，此字段中playTime值表示累积离线时间清零的时长
};

// end add

#pragma pack(pop) 

//////////////////////////////////////////////////////////////////////////
// Typedef
typedef std::vector<std::string> StringContainer;
typedef StringContainer::iterator ItrStringContainer;

//////////////////////////////////////////////////////////////////////////
// funcion
inline DWORD EctypeId2MapId( DWORD dwEctypeId )
{
    return ( dwEctypeId & 0x0000FFFF );
}

inline float LogBase(float fValue, float base)
{
   return log(fValue) / log(base);
}

inline float TileToFloat( int nTile )
{
    return nTile * MAPTILESIZE + MAPTILESIZE * 0.5f;
}

inline int16 FloatToTile( float fValue )
{
    return static_cast<int>(( fValue - MAPTILESIZE * 0.5f) / MAPTILESIZE);
}

inline int16 ChunckToTile( int nChunkValue )
{    
    return static_cast<int>(nChunkValue * CHUNK_SIZE / MAPTILESIZE + 0.5f);
}

inline int GetRand( int Min, int Max )
{
    if ( Max <= Min)
    { return Max; }

    return theRand.rand32() % (Max - Min + 1) + Min;
}

inline float GetRand( float Min, float Max )
{
    int nMin = (int)(Min * 100);
    int nMax = (int)(Max * 100);

    return GetRand( nMin, nMax ) / DEF_PER;
}

#define MaxMonsterIdLength 20
inline bool IsEctypeMonsterID( int nID )    // 副本怪的ID是4位的 然后算出一个6位ID
{
    char chBuff[MaxMonsterIdLength + 1] = {0};
    sprintf_s( chBuff, MaxMonsterIdLength, "%d", nID );

    return strlen(chBuff) == ECTYPEMAPMONSTERIDLENGTH;
}

inline bool IsNormalMonsterID( int nID )
{
    char chBuff[MaxMonsterIdLength + 1] = {0};
    sprintf_s( chBuff, MaxMonsterIdLength, "%d", nID );

    return strlen(chBuff) == NORMALMAPMONSTERIDLENGTH;
}

inline int FormatEctypeMonsterID( int nID, unsigned short ustLevel )
{
    if ( IsNormalMonsterID( nID ) )        
    { return nID;}

    char szID[MaxMonsterIdLength + 1] = {0};

    sprintf_s( szID, MaxMonsterIdLength, "%d%02d", nID, ustLevel );

    return atoi( szID );
}

inline int GetEctypeMonsterID(int nID, unsigned short& ustLevel)          // 获得副本怪ID 前4位
{
    if ( IsEctypeMonsterID( nID ) )
    {
        ustLevel = 0;
        return nID;
    }
    
    char chBuff[MaxMonsterIdLength + 1] = {0};
    sprintf_s( chBuff, MaxMonsterIdLength, "%d", nID );

    ustLevel = atoi ( chBuff + 4 );
    chBuff[4] = 0;

    return atoi( chBuff );
}

inline bool CheckCreateName( const std::string& strName )
{
    if ( strName.empty() )
    { return false; }

    if (strName.find("'") != string::npos || strName.find("-") != string::npos ||
        strName.find("_") != string::npos || strName.find("%") != string::npos ||
        strName.find(" ") != string::npos || strName.find(":") != string::npos || strName.find("\\") != string::npos )
        //strName.find("：") != string::npos )
        //strName.find( theXmlString.GetString(eClient_Chat_Begin) ) != string::npos )
    { return false;}
    return true;
}


//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
// 记录log相关的一些定义
namespace LogDefine
{
    enum EConstDefine
    {
        // 包裹掉落的方式
        ECD_DropType_Monster = 0,       // 杀怪掉落
        ECD_DropType_Player  = 1,       // 杀人掉落
        ECD_DropType_Luck    = 2,       // 幸运15关掉落
    };

    enum ELogType
    {
        // Log的类型
        ELT_Unknow      = 0,            // 错误的类型,表示函数错误
        ELT_EnterGame   = 1,            // 登录日志
        ELT_ExitGame    = 2,            // 登出日志
        ELT_Script      = 3,            // 脚本获得经验日志增加类型
    };
}

namespace ServerDataDefine
{
    typedef unsigned char NodeType; // 节点类型
    typedef unsigned char Status;

    enum EnumDefine
    {
        // 节点类型
        Node_Root       = 0,  // 跟节点
        Node_Center     = 1,
        Node_Database   = 2,
        Node_Game       = 3,
        Node_Character  = 4,
        Node_Gate       = 5,
                       
        // 状态        
        Status_Fine     = 0,  // 良好
        Status_Busy     = 1,  // 忙
        Status_Bad      = 2,  // 挂了
                       
        ErrorID         = 0xFFFFFFFF, // 错误id

        DoNothing       = 0,      // 什么也不干
        ReqServerStatus = 1,      // 发送消息给各服务器
        WaitForAck      = 2,      // 等待各服务器回应
        SendToPlat      = 3,      // 发送消息给平台回报服务器状态

        WaitTime        = 10000,  // 等待回应时间
        BusyTimeOut     = 3000,   // 3秒表示服务器有点卡了
    };
}

#endif // __COMMON_GLOBALDEF_H__
