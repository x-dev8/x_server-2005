/********************************************************************
    Filename:     GlobalDef.h
    MaintenanceMan Mail: debugcommand@hotmail.com
*********************************************************************/

#ifndef __COMMON_GLOBALDEF_H__
#define __COMMON_GLOBALDEF_H__

#pragma once

#include "MeRTLibsServer.h"
#include "MsgBase.h"
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
////////////////////////////////////////////////////////////////////////////
//#define USE_OLD_LOGIN
//#ifndef __NEW_LOGIN__
//	#undef  __NEW_LOGIN__
//#endif
////////////////////////////////////////////////////////////////////////////

// [消息安全转换] BEGIN HANDLE END 为一组  -产生新的指针pTMessage
#define SAFE_CONVERSION_MESSAGE( messagepointer, messagetype ) \
	messagetype* pTMessage = (messagetype*)messagepointer; \
	CHECK_RETURN( pMessage->GetLength()!=sizeof(messagetype), ER_MessageLengthError); 

// [GameServer] BEGIN HANDLE END 为一组
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

// [DataBase] BEGIN HANDLE END 为一组
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

// [Platform] BEGIN HANDLE END 为一组
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


// [最通用] BEGIN HANDLE END 为一组
#define MESSAGE_MAPPING_BEGIN \
        CHECK_RETURN( pMessage==NULL, ER_NullPointer); \
        switch ( msgType ) \
        {
//-1--[不]转换[直接]Handle([Null],pMessage )
#define MESSAGE_HANDLE_UNPACK( messageId, messageClassType, messageHandle ) \
		case messageId: \
				{ \
				messageHandle(pMessage ); \
				} \
				break;
//-2--[安全]转换[完整]Handle([Null],pTMessage )
#define MESSAGE_HANDLE_USER( messageId, messageClassType, messageHandle ) \
		case messageId: \
			{ \
			    SAFE_CONVERSION_MESSAGE(pMessage, messageClassType ); \
				messageHandle(pTMessage ); \
			} \
			break;
//-3--[不]转换[完整]Handle([Null],pTMessage )
#define MESSAGE_HANDLE_USER_NOTCHECK( messageId, messageClassType, messageHandle ) \
		case messageId: \
			{ \
				messageClassType* pTMessage = (messageClassType*)pMessage; \
				messageHandle(pTMessage ); \
			} \
			break;
//-4--[安全]转换[完整]Handle([pClient],pTMessage )
#define MESSAGE_HANDLE( messageId, messageClassType, messageHandle ) \
        case messageId: \
            { \
                SAFE_CONVERSION_MESSAGE(pMessage, messageClassType ); \
                messageHandle( pNetClient, pTMessage ); \
            } \
            break;
//-5--[安全]转换[完整]Handle( [Null],pTMessage ) 重复了
#define MESSAGE_HANDLE_1( messageId, messageClassType, messageHandle ) \
        case messageId: \
            { \
                SAFE_CONVERSION_MESSAGE(pMessage, messageClassType ); \
                messageHandle( pTMessage ); \
            } \
            break;
//-6--[不]转换[完整]Handle( [pClient],pTMessage )
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

//////////////////////////////////////////////////////////////////////////
#pragma warning( disable : 4800 )
//////////////////////////////////////////////////////////////////////////


#define MAX_NAME_CREATE          16
#define MAX_NAME_STRING          32
#define MAX_PASSWORD_STRING      32
#define MAX_TITLE_COUNT          255
#define MAX_RECIPE_COUNT         500
#define BORN_POINT_COUNT         6
#define IP_LENGTH                16
#define MAC_LENGTH               20
#define INVALID_SERVERID         0xffffffff
#define MAX_KILLINFO_COUNT       100
#define MAX_SPECIALQUEST_COUNT   10
#define MAX_AREAREPULATION_COUNT 10
#define MAX_FRIENDDEGREE_COUNT   13
#define MAX_PRESSKEYSUIT_COUNT   10         // 人物一键换装数量
#define MAX_ACHIVEVMENT_COUNT    2000       // 人物成就总计
#define MAX_PETIDENTIFY_COUNT    4000       // 宠物图鉴总数
#define MAX_GUIDE_COUNT          1000       // 新手指导
#define MAX_IDENTIFY_TOTAL		 65000		// 图鉴卡累计最大次数

#define MAX_KILLSUM				 3000

#define MAPTILESIZE         (128.0f*0.02f) // 地形块的基本大小 单位空间坐标单位
#define CHUNK_SIZE          16.0f          // Chunck 单位空间坐标单位
#define DORIDE_RATE         15000          // 两次骑马的间隔

#define INVALID_CHAR_ID     -1

#define MOVEVELOCITY        (3.0f)                 // 每秒移动格数，也就是人物移动速率
#define ONESTEPCOST         (1000.0f/MOVEVELOCITY) // 一步消耗的时间，毫秒

#define CHAR_DEFAULTBODYSIZE 0.3
#define GLS_CheckBlockTime   (1000*60)		
#define PI	3.1415926f

//游戏世界信息搜集服务器
#define DATACOLLECTINTERVAL  (1*1000) //一分钟搜集一次信息(T)
#define SYNCCHARPOSINTERVAL  (5*1000) //游戏世界与clinet同步坐标消息的间隔

#define QUEST_MAX        4
#define PKVALUEDAILY_MOD 5 // PK值每天获得的最大值系数

#define PLUE_EXP_MODULUS     0.2
#define NEGATIVE_EXP_MODULUS 0.5
#define MOUNT_EXP_MODULUS    1.0

#define CHAR_REFRESHTIME 1000
#define EMISSIONFLYCOST 40
#define TEAM_EXP_DIS 60.0f
#define PackagePickDistance 1.5f            //拾取包裹的有效距离
#define TARGET_VIEW_DIS 60.0f   
#define PickAuttonDistance 70.0f			//拾取包裹ID_BUTTON_PickOn按钮的拾取距离

#define BaseMoveSpeed  5.0f

#define MAXEMISSIONNUM 6    //发射型技能最大数量

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
#define MAX_MAP_LEVEL 40            // 目前地图分40个等级 (人物角色 每5级一个等级) 

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
#define Safe_Map_Id     2
#define Safe_Map_PosX   183.0f
#define Safe_Map_PosY   194.0f
#define Safe_Map_Dir    0.0f

//#define MoBeiMapID     9         // 漠北地图ID
//#define LiaoDongMapID  0         // 辽东地图ID
//#define DunHuangMapID  8         // 敦煌地图ID
//#define GaoGouLiMapID  1         // 高句丽地图ID

#define eMAX_TEMP_BUFF 0xFF
// CharacterServer Id
//#define CENTERLOGINSERVERID 99
#define CHARACTERSERVERID 100

#define WORLD_HEIGHT 40000.f


// 金钱总额的上限
#define MoneyUnit   10000
#define MaxMoney30 ( 20 * MoneyUnit )           // 30级金钱总额最大值
#define MaxMoney40 ( 2000 * MoneyUnit )          // 40级金钱总额最大值
#define MaxMoney55 ( 20000 * MoneyUnit )         // 55级金钱总额最大值
#define MaxMoney60 ( 100000 * MoneyUnit )         // 55级以上金钱总额最大值


// 交子总额的上限
#define JiaoZiUnit   10000
#define MaxJiaoZi30 ( 20 * JiaoZiUnit )              // 30级金钱总额最大值
#define MaxJiaoZi40 ( 2000 * JiaoZiUnit )             // 40级金钱总额最大值
#define MaxJiaoZi55 ( 20000 * JiaoZiUnit )           // 55级金钱总额最大值
#define MaxJiaoZi60 ( 100000 * JiaoZiUnit )           // 55级以上金钱总额最大值

// 召唤怪上限
#define CharSummonPetMaxCount   3

#define CHAT_STRINGMAX 500
//最高悟性等级
#define MaxSavvy 10

// 无效的HeroID
#define INVALID_HERO_ID		0xFFFF

//无效的地图ID
#define INVALID_MAP_ID		0xffffffff

//狩猎任务
#define Hunting_MaxAccept_OneDay 10
#define MaxCount_Show 10


#define PwdCardLength (8) //密保卡每个单元的字符长度
#define PwdCardSerialLength (32) //密保卡每个单序列号
// world define
const unsigned short ErrorUnsignedShortID = 0xffff;
const unsigned long  ErrorUnsignedLongID  = 0xffffffff;

const int dr_worldMaxPlayers      = 5000;
const int dr_worldMaxCharacters   = 200000; // World最大角色数/*32767*/ 65535
const int dr_worldMaxStages       = 128;   // 活动场景数
const int dr_refreshstagezonerate = 1;     // 刷新触发区域的频率

// stage define
const int dr_stageMaxCharacters  = 200000;     // Stage最大角色数
const int dr_stageMaxAreas       = 32*32*8*8; // 最大区块数
const int dr_stageMaxMapWidth    = 128*32;    // 地图最大宽度
const int dr_stageMaxMapHeight   = 128*32;    // 地图最大高度
const int dr_stageAreaSize       = 12;        // 12 区块大小 原来 16
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
const int dr_MaxChatString             = 1536;//2048;//1024;
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

const short          manual_levelup = 29;//开始手动升级的等级
const short          save_max_level_exp = 3;//保存最多3级的经验

const static int	 MaxPetDuration = 5000;
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
    More_iCharPerAccount                = 3    // 每个账号在一组游戏服务器能拥有3个角色
    ,More_iSkillCountPerLinkedSkills    = 5    // 每个连招由5个招式组成
    ,More_iMaxLinkedSkills              = 5    // 每个角色的连招个数
    ,More_iMaxCountOfAItem              = 30   // 每个物品在一个物品包中最大的个数
    ,More_iMaxVars                      = 6000 // 角色系统变量的个数
    ,QuestLimitTimeMaxCount             = 5    // 最大的限时任务
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
    ,More_skillEducate                   = 81//| 81     技能修炼
    ,More_iHotkey                        = 82//| 所以    enumConst::More_iHotkey 设为36

    ,const_iCharMaxLevel        = 200   //人物最高等级
    ,More_nMapSize              = 128   //大陆中地图的大小
    ,More_iMaxSkillByte         = 32    //        
    ,More_iMaxSkill             = More_iMaxSkillByte*8 //最多8*32个技能
    ,More_iMaxXinFa             = 20    //最多学习的心法
	,More_iMaxHeroSkill			= 3		//最多的主将技能
    ,More_iMaxSkillKnown        = 100   //最多习得的技能
    ,More_iCharDataRestoreCheck = 3000  //HP,MP恢复的时间单位
    ,More_iCharPoisonCheck      = 3000  //中毒扣血的检查间隔
    ,More_iMaxLinkSymbolStone   = 3
    ,More_iMaxLinkNormalSkill   = 5
    ,Beginner_LevelLimit        = 5
    ,ObtainExp_LevelDiffLimit   = 5
    ,AttackMonster_MaxPlayer    = 20    
	,CheckDamageScoreTime		= 1000*10  
    ,Distance_ShareTeamExp      = 50    
    ,UpgradeSkillMaxLimit       = 10
    ,UpgradePropertyMaxLimit    = 300
    ,PowerPointMax              = 3
    ,PowerCountMax              = 300
	,More_nCardMax				= 128 //玩家身上卡牌最大数量
	,More_nCardAchieve			= 32  //卡牌成就数量
	,More_nHuntingNum			= 32  //当前玩家可选的狩猎任务数量
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
{ // 战斗状态标志 //在 16个bit中
    eFIGHT_NOFLAG       = 0,    // 没有特殊状态
    eFIGHT_RELIVE       = 1<<0, // 复活
    eFIGHT_MISS         = 1<<1, // 攻击未命中
    eFIGHT_BEKILLED     = 1<<2, // 目标被杀
    eFIGHT_BACKSTRIKE   = 1<<3, // 背击
    eFIGHT_CRITICALHIT  = 1<<4, // 暴击
    eFIGHT_CANCEL       = 1<<5, // 取消
    eFIGHT_ERROR        = 1<<6, // 战斗出错
    eFIGHT_SUCKHP       = 1<<7, // 吸血
    eFIGHT_DAMREFLECT   = 1<<8, // 反伤
    eFIGHT_SELFBEKILLED = 1<<9, // 攻击者自杀
    eFIGHT_DAOXINGRESIST= 1<<10,// 道法抵抗
    eFIGHT_DAOXINGSTIFLE= 1<<11,// 道法压制
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
    eNT_Item        = 99  ,//物品形式NPC
    eNT_Battle      = 100 , //战场Npc
	eNT_Elevator    = 101 , //电梯
	eNT_SpecialNpc  = 102 , //特殊NPC,有任务才显示
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
    Object_MonsterPet        , // 召唤宠
    Object_MonsterIllusion   , // 分身怪
    Object_MonsterResource   , // 资源怪
    Object_MonsterTrap       , // 陷阱机关怪
    Object_MonsterCapture    , // 捕捉宠物怪
    Object_MonsterProtected  , // 被保护怪 镖车 马
    Object_MonsterBuilding   , // 建筑
    Object_MonsterNurturePet , // 培育宠
    Object_MonsterSpecial    , // 专属怪
    Object_MonsterPickup     , // 拾遗小妖

    // Object_Npc 派生
    Object_NpcNormal     = 50, // 普通脚本Npc
    Object_NpcFight          , // 带巡逻战斗Npc
    Object_NpcShip           , // 带Ship数据的载体Npc
};

namespace CheckAttack
{
    enum ECheckAttackResult
    {
        CanNotAttack = 0,   // 不能攻击
        EnmityFightCamp,    // 敌对阵营
        EnmityCountry,      // 敌对国家
        EnmityForce,        // 敌对势力
        EnmityTarget,       // 仇恨目标
        AttackUnknow,
    };
}

namespace ForceDefine
{
    enum EConstDefine
    {
        NoneForce = 0,      // 无势力
        NormalPlayerForce,  // 普通玩家
        EnmityPlayerForce,  // 红名玩家
        NormalNpcForce,     // 普通npc势力
        FightNpcForce,      // 战斗npc势力
        NormalMonsterForce, // 普通怪物势力
        PetMonsterForce,    // 宠物怪物势力
    };

    // 判断是否是仇恨势力( 暂时写在这里,以后要使用配置 )
    static bool CheckEnmityForce( uint8 nFirstForce, uint8 nSecondForce )
    {
        switch ( nFirstForce )
        {
        case NoneForce:
        case NormalNpcForce:
            return false;
            break;
        case NormalPlayerForce:
        case EnmityPlayerForce:
            {
                switch ( nSecondForce )
                {
                case NormalMonsterForce:
                    return true;
                    break;
                }
            }
            break;
        case FightNpcForce:
            {
                switch ( nSecondForce )
                {
                //case EnmityPlayerForce:
                case NormalMonsterForce:
                    return true;
                    break;
                }
				return false;
            }
            break;
        case NormalMonsterForce:
            {
                switch ( nSecondForce )
                {
                case NormalPlayerForce:
                case EnmityPlayerForce:
                case PetMonsterForce:
                case FightNpcForce:
                    return true;
                    break;
                }
            }
            break;
        case PetMonsterForce:
            {
                switch ( nSecondForce )
                {
                case NormalMonsterForce:
                    return true;
                    break;
                }
            }
            break;
        default:
            break;
        }

        return false;
    }
}


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
	eMT_Pet,			 // 宠物
    eMT_Collision,       // 阻挡怪
    eMT_Insect,          // 昆虫
    eMT_Protect,         // 护送怪
    eMT_Pickup,          // 拾遗小妖
    eMT_MaxCount,        //
};

//组队相关
enum TeamMangerEnum
{
    TeamMaxCount = 6000,			//最大的团队数量

    TeamMaxMember = 24,				//一个团最多20人
    TeamMaxManipleMember = 5,		//一个小队5人
    TeamMaxManipleCount = 4,		//一个团4个小队
    TeamUpdateInterval = 2000,		//队员信息2秒刷新一次
    TeamUpdateToCenter = 5000,      //为了缓解跨服同步压力,队员信息5秒同步一次
    TeamSelfUpdate = 100000,        //队伍创建后每60秒检查一次是否还有效

    ReleaseSpaceTime = 1000,    
    TeamManipleDefalutId = -1,		//默认自动分配小队
};

enum AssignModeType                 //组队模式
{
    AssignMode_FreeMode = 0,        //自由分配
    AssignMode_Team,                //队伍。。
    AssignMode_Random,              //随即。。
    AssignMode_Assign,              //分配。。
};

enum BoultAssignTeam                //掉落物品后操作
{
    BoultAssign_None = 0,           //未选择
    BoultAssign_ComeDown,           //索取
    BoultAssign_GiveUp,             //放弃
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
    eIL_Normal = 0,     // 普通
    eIL_Choiceness = 1, // 良品
    eIL_Polish = 3,     // 精品
    eIL_Nonsuch = 4,    // 极品
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

// 五行属性
enum EFiveElements
{
    FiveElements_None = 0,
    FiveElements_Metal = ItemElements_Metal  ,       // 金
    FiveElements_Wood  = ItemElements_Wood   ,       // 木
    FiveElements_Water = ItemElements_Water  ,       // 水
    FiveElements_Fire  = ItemElements_Fire   ,       // 火
    FiveElements_Earth = ItemElements_Earth  ,       // 土

    FiveElements_End,
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
    EPT_Skill = 0,  // 技能宠
    EPT_Protect  ,  // 保护宠
    EPT_Capture  ,  // 捕获宠
    EPT_Nurture  ,  // 培育宠
    EPT_Max      ,  // 最多的宠物
};

enum ECurPetTactic
{ // 宠物的处理策略
    ePetCommandAI = 0,
    ePetAttackAI,
    ePetDefendAI, // 防守模式 不做任何反应宝宝 只跟着人
};

enum EJiFengItemStatus
{
    EJFIS_Delete = 0, // 已经领取
    EJFIS_Have   = 1, // 持有未领取
};

//PK系统 相关
/////////////////////////////////////////////////////////////// 

//#define  MinPKValue             0           // 最小PK值
//#define  MaxPKValue             999         // 最大PK值
#define  PKProtectLevel         30          // zhuxincong 根据策划要求 新手保护改到30 PK 保护等级
//#define  PKKillValue            1          // 杀死一个PK值为0的玩家，将获得50点PK值
//#define  PKHellPunishValue      250          // 250 进监狱
//#define  PKHellleaveValue       200         // 200 离开监狱
#define  PKDropItemRate         30          // 红名玩家被杀死后，30%几率掉落1件未绑定的物品
#define  PKModeChangeDelayed    180000      // 切换完PK模式后延迟 3分钟
//#define  PKValueUpdateTime      3600000      // 每 60分钟减少 1点PK值
#define  PKCriticalTime         1800000     // 狂暴模式持续时间
#define  MaxHonourSum			10000		//玩家最大荣誉值
#define  MaxLevelAttack			20000		//离开战斗状态20秒后脱离特殊模式
enum PKMode
{
    PKMode_Normal = 0,		    // 普通模式
    PKMode_Fight     ,			// PK模式: 全体模式 可攻击除队友的其他玩家
	PKMode_Critical  ,			// 狂暴模式
	PKMode_Guild	 ,			// PK模式: 军团模式 可攻击除队友和军团之外的其他玩家
	PKMode_AttackFight,			// 特殊模式 和狂暴模式类似 
	PKMode_AttackGuild,			// 特殊模式 和狂暴模式类似 
	PKMode_MaxValue  ,			// 
};
/////////////////////////////////////////////////////////////////

enum PlayerShowMode
{
	PSM_ShowAll = 0,		    // 显示所有玩家
	PSM_HideAll      ,			// 隐藏所有玩家
	PSM_ShowAmity   ,			// 显示本国的玩家
	PSM_ShowAntagonize	   ,	// 显示他国的玩家。
	PSM_Max,
		
};

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
	SSRT_CHANGECHANNEL			// 游戏中切换分线
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
    eReliveTypeSkill            , // 技能复活
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
    BT_PetBag          ,
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
    ITEM_PET_MAXCOUNT        = 6 ,              // 宠物最大数
    ITEM_BREEDPET_MAXCOUNT   = 1 ,              // 繁殖宠物最大数

    //ITEM_STORAGEMAX = 10,
    //ITEM_STOREMAX = 40,
    //ITEM_SYMBOLSTONEMAX = 30,
    //ITEM_ACTIONMAX = 50,
    //ITEM_TRADEMAX = 20,
    //ITEM_MATERIALMAX = 3
};

// 各种生产, 生活技能点类型枚举
#define RecipeSkillNumMax   4   // 最多只能学习三个生活技能

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
    ERT_CatchPet,         // 捕捉宠物

    ERT_MaxType = 24,     // 最大类型
};

//引发吟唱的类型
enum EIntonateType
{
    IntonateType_UnKnow     ,   // 未知
    IntonateType_Item       ,   // 物品
    IntonateType_NPC        ,   // NPC
};

enum ECharAttrType
{ // 人物属性的枚举
    //一级属性
    CharAttr_Strength     , // 力量
    CharAttr_Agility      , // 敏捷
    CharAttr_Stamina      , // 耐力
    CharAttr_Intelligence , // 灵气
    CharAttr_BaseAttributeMaxCount,
    //二级属性
    CharAttr_HPMax = CharAttr_BaseAttributeMaxCount, // HP上限
    CharAttr_MPMax                  ,   // MP上限
    CharAttr_AttackPhysics          ,   // 物理攻击力
    CharAttr_AttackMagic            ,   // 魔法攻击力
    CharAttr_DefendPhysics          ,   // 物理防御
    CharAttr_DefendMagic            ,   // 魔法防御
    CharAttr_AttackSpeed            ,   // 攻击速度
    CharAttr_MoveSpeed              ,   // 移动速度
    CharAttr_HPRestore              ,   // HP恢复
    CharAttr_MPRestore              ,   // MP恢复
    CharAttr_Exact                  ,   // 命中率
    CharAttr_Dodge                  ,   // 闪避率
    CharAttr_Critical               ,   // 暴击率
    CharAttr_Tenacity               ,   // 韧性
    CharAttr_CriticalIntensity      ,   // 暴击伤害
    CharAttr_BackStrike             ,   // 背击伤害
    CharAttr_BackStrikeResist       ,   // 背击抗性
    CharAttr_BreakStrike            ,   // 破甲伤害
    CharAttr_StabStrike             ,   // 贯穿伤害
    CharAttr_ElementStrike          ,   // 元素伤害
    CharAttr_ToxinStrike            ,   // 毒素伤害
    CharAttr_SpiritStrike           ,   // 精神伤害
    CharAttr_BreakResist            ,   // 破甲抗性
    CharAttr_StabResist             ,   // 贯穿抗性
    CharAttr_ElementResist          ,   // 元素抗性
    CharAttr_ToxinResist            ,   // 毒素抗性
    CharAttr_SpiritResist           ,   // 精神抗性
    CharAttr_AttributMaxCount       , 

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
    CharAttr_CurMountHP           ,
    CharAttr_CurMountHPMax        ,
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
    CharAttr_FreeRelive           , // 当前总计免费复活次数
    CharAttr_Daoxing              , // 当前道行
    CharAttr_CurGetDaoxing        , // 当前获得道行
    CharAttr_BasePotential        , // 当前剩余潜力点
    CharAttr_CurGetSkillExp       , // 当前获得技能经验
    CharAttr_ActivePetHP          , // 当前出战宠物血量
    CharAttr_ActivePetCurGetExp   , // 当前出战宠物获得经验
	CharAttr_LostExp			  , // 人物减少的经验
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
//	AN_S2A_OpenUI_RealAward			 = 33,  // 实物奖励
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
	AN_S2A_OpenUI_EquipqualityIdentify   = 90,  //装备品质鉴定
	AN_S2A_OpenUI_StallQuery		     = 91,	//摆摊查询
    AN_S2A_OpenUI_QuestCommitItem        = 92,	//任务提交物品
    AN_S2A_OpenUI_PetBreed               = 93,	//宠物繁殖
	AN_S2A_OpenUI_PetUp					 = 94,  //使用宠物悟性升级
	AN_S2A_OpenUI_PetStudy               = 95,  //宠物技能学习
	AN_S2A_OPenUI_PetMaterialUp          = 96,  //道具升级悟性
	AN_S2A_OpenUI_CreateFamily		 = 97,	// 创建家族
	AN_S2A_OpenUI_ApplyJoinFamily	 = 98,  // 申请加入家族
	AN_S2A_OpenUI_ZhujiangBianshen	 = 99,	// 主将变身
	AN_S2A_OpenUI_Achievement		 = 100,	// 成就
	AN_S2A_OpenUI_ChangeCountry		 = 101, // 改变国家
	AN_S2A_OpenUI_ShopCenter		 = 102, // 商城
	AN_S2A_OpenUI_ItemTrade			 = 103, // 物品寄售			 
	AN_S2A_OpenUI_CaoYao			 = 104,  //制药界面
	AN_S2A_OpenUI_ZhuBao			 = 105,  //珠宝界面
	AN_S2A_OpenUI_DuanZao			 = 106,  //锻造界面
	AN_S2A_OpenUI_ZhuJia			 = 107,  //铸甲界面
	AN_S2A_OpenUI_GongYi			 = 108,  //工艺界面
	AN_S2A_OpenUI_XunMa				 = 109,  //驯马界面
	AN_S2A_OpenUI_CaiKuang			 = 110,  //采矿界面
	AN_S2A_OpenUI_CaiYao			 = 111,  //采药界面
	AN_S2A_OpenUI_ShiTu				 = 112, //zhuxincong 可能是师徒
	AN_S2A_OpenUI_ShiTu2			 = 113, //zhuxincong 可能是师徒
	AN_S2A_OpenUI_Title				 = 114,
	AN_S2A_OpenUI_ZhuJianUp			 = 115, //主将图鉴合成
	AN_S2A_OpenUI_TransferStar		 = 116, //转星界面
	AN_S2A_OpenUI_UnBind			 = 117, //解绑界面
	AN_S2A_OpenUI_MountStrengthen	 = 118,
	AN_S2A_OpenUI_CountryBaseInfo	 = 119,
	AN_S2A_OpenUI_AskPresent		 = 120,
	AN_S2A_OpenUI_MoveCountry		 = 121,
	AN_S2A_OpenUI_MaterialBag		 = 122, //材料背包
	AN_S2A_OpenUI_TaskBag			 = 123, //任务背包
    AN_S2A_OpenUI_RandAttribute		 = 124, //清洗随机属性
	AN_S2A_OpenUI_PetComPose		 = 125,
	AN_S2A_OpenUI_GuildChangeName    = 126,
	AN_S2A_OpenUI_QuestEntrust		= 127,
	AN_S2A_OpenUI_Hunting			 = 128, //狩猎任务
	AN_S2A_OpenUI_Card				 = 129, //卡牌
	AN_S2A_OpenUI_MountMoveStar		 = 130,
	AN_S2A_OpenUI_AutoAttack		= 131,
	AN_S2A_OpenUI_Task				= 132,
	AN_S2A_OpenUI_ActivityList		= 133,
};

//打开UI来源
enum AN_S2A_OpenClientUI_Type
{
    OpenClientUIType_Other = 0,     //
    OpenClientUIType_Quest    ,     // 任务

    OpenClientUIType_Max
};

enum EIdleSubAction
{
    // Server和Client保持一致
    CS_SubAction_Normal,
    CS_SubAction_SitDown,        
    CS_SubAction_FightAction,
    CS_SubAction_Embrace,     // 拥抱
    CS_SubAction_Restore,     // 喝药治疗  
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
    BagTypeMountSkill,        //坐骑背包技能
    BagTypePetSkill,          //宠物背包技能
	BagTypeExpressionAction,  //表情动作
	BagTypeHeroSkill,		  //主将技能背包
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
    STORAGE_ITEMGRID_MAX  = 150,                     // 每个仓库最大格子数
    STORAGE_MOUNTGRID_MAX = 6 ,                      // 坐骑仓库最大格子数
    PAGESIZE = 30,                                   // 每页的格子数目
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
    //逻辑效果:每秒扣血
    //显示效果:掉血显示为绿色
    //？扣血是否固定，还是有不同的中毒程度
    //,BodyStatus_Chaos
    //混乱，操作不受控制，角色到处乱动，不能攻击
    ,BodyStatus_Frost    = 1<<1            
    //冰冻
    //逻辑效果:移动缓慢，攻击缓慢（速度全部减半）
    //显示效果:人物颜色变为深蓝色            
    ,BodyStatus_Stone    = 1<<2
    //石化
    //逻辑效果:不能移动，不能攻击
    //显示效果:人物显示类似石像
    ,BodyStatus_Sleep    = 1<<3
    //昏睡
    //逻辑效果:不能移动，不能攻击，被攻击解除状态
    //显示效果:可否有昏睡动作？头顶显示ZZZZZ
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
    ST_MONSTER               , // 怪物触发
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
	ST_CHAR_KILLCHAR		,	//玩家杀死敌对阵营玩家
	ST_ACHIEVE				 , //完成成就时触发
	ST_CARD_ACHIEVE			 , //完成卡牌成就时触发
	ST_ScriptSleep			,  //如果有脚本在吟唱，则中止它
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
    SNT_SLEEP       ,   // 睡眠
    SNT_DISTORTION  ,   // 变羊
    SNT_FROST       ,   // 冰冻
    SNT_SNEERAT     ,   // 嘲讽
    SNT_FORGET      ,   // 遗忘
    SNT_ILLIBERALITY,   // 吝啬
    SNT_ATONY       ,   // 无力
    SNT_ALLURE      ,   // 魅惑
    SNT_MaxCount    ,   // 
};

enum EInstantMovingType
{
    IMT_None,               // 不瞬移
    IMT_Forward,            // 向前瞬移
    IMT_Backwards,          // 向后瞬移
    IMT_TargetBack,         // 瞬移到背后
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
	ET_SystemBeKick,          // 被系统正常踢除游戏 走保存 走流程
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

enum ESpecialTaskType
{
	ESTT_Intensify,			//强化任务
	ESTT_GemUp,				//宝石升级任务
	ESTT_Hole,				//打孔
	ESTT_EquipGem,			//镶嵌
	ESTT_EquipStar,			//升星
	ESTT_KillPlayer,		//杀敌对玩家(不是本国的玩家)
	ESTT_KillWei,			//杀魏国
	ESTT_KillShu,			//杀蜀国
	ESTT_KillWu,			//杀吴国
	ESTT_MAX
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
	uint8 chChannelStatus;
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
	__int64      Sessionkey;
   // char         SessionKey[40+1];           // SessionKey
    //char         Password[50];               // 密码
    //char         Seed[50];                   // 种子
	char         szMac[MAC_LENGTH];			 // mac 地址
    int8         isWallow;                   // 是否成年
    bool operator == (SLoginInfoBase &other) { return Sessionkey = other.Sessionkey /*strcmp(SessionKey,other.SessionKey)==0*/;}
    bool operator == (__int64 other/*const char* other*/) { return Sessionkey == other/*strcmp(SessionKey,other)==0*/; }
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

struct SCharHeroInfo		//变身主将所增加的属性结构
{
	SCharHeroInfo()
	{
		memset(this,0,sizeof(SCharHeroInfo));
	}
	int32		hpMax            ; // HP上限
	int32		mpMax            ; // MP上限
	int32		attackPhysics    ; // 物理攻击力
	int32		attackMagic      ; // 魔法攻击力 
	int32		defendPhysics    ; // 物理防御
	int32		defendMagic      ; // 魔法防御
	int32		attackSpeed      ; // 攻击速度
	int32		moveSpeed        ; // 移动速度
	int32		hpRestore        ; // HP恢复
	int32		mpRestore        ; // MP恢复
	int32		exact            ; // 命中率
	int32		dodge            ; // 闪避率
	int32		critical         ; // 暴击率 
	int32		tenacity         ; // 韧性  
	int32		criticalIntensity; // 暴击伤害
	int32		backStrike       ; // 背击伤害
	int32		backStrikeResist ; // 背击抗性
	int32		breakStrike      ; // 破甲伤害
	int32		stabStrike       ; // 贯穿伤害
	int32		elementStrike    ; // 元素伤害
	int32		toxinStrike      ; // 毒素伤害
	int32		spiritStrike     ; // 精神伤害
	int32		breakResist      ; // 破甲抗性
	int32		stabResist       ; // 贯穿抗性
	int32		elementResist    ; // 元素抗性
	int32		toxinResist      ; // 毒素抗性
	int32		spiritResist     ; // 精神抗性
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
			hero_id = INVALID_HERO_ID;
			//dwMapID = INVALID_MAP_ID;
			//PrePosition = D3DXVECTOR3(0,0,0);
			dwKillPlayerSum =0;
			dwKillPlayerWeekSum =0;
			uchPosition = 0;
            ConsumeScore = 0;
            ChangeName = 0;
        }

        uint16          ustLevel;                             // 等级
        uint32          dwMoney;                              // 游戏金钱
        uint32          jiaoZi;                               // 交子(绑银)
        uint32          reputation;                           // 声望值
        uint32          exploit;                              // 功勋值
        uint32          honour;                               // 荣誉值
        uint32          battleScore;                          // 战场积分
        uint32          dwCountryScore;                       // 国战积分
        uint32          jinDing;                              // 金锭(元宝)
        uint32          jinPiao;                              // 金票(绑金)
        uint32          dwHelpFlag;                           // 泡泡提示
        uint32          nHighShoutCount;                      // 当天的喊话次数
        int             nHp;                                  // 血量
        int             nMp;                                  // 魔量
        int             nXp;                                  // XP值
        int64           dwExp;                                // 当前经验
        int64           dwExpNotUsed;                         // 未使用的经验
        uint32          dwSkillExp;                           // 技能经验        
        uint32          dwSkillExpNotUsed;                    // 未使用的技能经验
        uint16          ustSkillExpForSkillID;                // 要升级的技能ID
        uint16          activity;                             // 活力 (生产消耗)
        uint16          activityMax;                          // 活力最大值 45+人物等级(ILevel)*5
        uint16          vigor;                                // 精力 (采集消耗)
        uint16          vigorMax;                             // 精力最大值 45+人物等级(ILevel)*5
        uint32          dwOnlineTime;                         // 玩家总在线时间( 单位; 分钟 )
        uint32          dwRewardItemInfo;                     // 玩家在线时长领取奖励的信息( 最大可以32次, 32位 每一位的数值 0 = 没有领取, 1 = 已经领取过 )
        
        int16           nCurrentTitleID;                      // 当前称号
        uint16          nCountryTitle;                        // 国家称号( 这个不需要保存在数据库 )
        TitleData       xTitleData[MAX_TITLE_COUNT];          // 称号列表
        SAreaRepulation xArea[MAX_AREAREPULATION_COUNT];      // 区域声望
        MasterData      xMasterData;                          // 师门属性
        
        SColdDown       xItemColdDown[MAX_SAVERESTORE_COUNT]; // 物品的colddown时间

        uint16          nRecipeSkillNum;                      // 生活技能个数
        uint16          nSkillPoint[ ERT_MaxType ];           // 各种生产生活技能熟练度

        uint8           ucMountCount;                         // 坐骑个数
        uint8           ucNormalBagSize;                      // 实际普通背包的开放个数
        uint8           ucMaterialBagSize;                    // 实际材料背包的开放个数
        uint8           nStorageItemGrid ;                    // 仓库物品格子数量
        uint8           nStorageMountGrid;                    // 仓库坐骑格子数量

        uint32          nRecordReliveTime;                    // 记录最后复活的时间
        uint8           nFreeReliveCount ;                    // 记录每日免费复活次数

        uint32          nSysDoubleExpTime;                    // 系统赠送的双倍经验时间
        uint32          nItemDoubleExpTime;                   // 道具双倍经验时间

        uint32          daoxing;                              // 道行
        uint16          basePotential;                        // 当前潜力点
        uint16          baseAssignValue[EBaseAttr_MaxSize];   // 已经分配的潜力点
		uint16          hero_id;                              //变身的主将ID
		char            TPHJRank;                             //进入太平幻境的等级

		//DWORD			dwMapID;							  //进入太平幻境之前的MapID
		//D3DXVECTOR3		PrePosition;						  //进入太平幻境之前的坐标 
		uint32			dwKillPlayerSum;					  //玩家杀人总数
		uint32			dwKillPlayerWeekSum;				  //玩家本周杀人数 每周六的凌晨清零

		uint8			uchPosition;						  //玩家在国家中的职位 默认值为Position_None=0 表示无职位
        uint32          ConsumeScore;                         //LYH商城积分
		int			    ChangeName;
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
        EConstDefine_BaseRandMaxCount       = 7, // 基本附加随机
        EConstDefine_PurpleRandMaxCount     = 3, // 紫色附加随机
        EConstDefine_GemHoleMaxCount        = 4, // 最大的镶嵌空位
        EConstDefine_SuitRandMaxCount       = 1, // 套装的精炼附加随机 技能套装精炼以后
		EConstDefine_HasBaseRanded		    = 0xffff, // 鉴定出无附加随机属性时赋予的值,表示已鉴定过了
        EConstDefine_TalismanRandMaxCount   = 7, // 法宝修炼属性
    };

    enum EEquipEvolveConstDefine
    {
        EEquipEvolve_SoulStampAddition  = 50, // 装备铭刻加成
    };

    enum ELevel
    {
        EL_Min    = 0 ,
        EL_Notice = 12 , // 大于12级全服公告
        EL_StarMax= 18, // 装备最高18星	//原来是10，现在改成18
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

	//基础属性太多了...筛选掉
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
/*
		ITEMTYPE_RESTORE = 0    , // 恢复药品
		ITEMTYPE_WEAPON         , // 武器----------------
		ITEMTYPE_ARMOUR         , // 防具----------------
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
*/
    struct SEquipData
    {   // 物品的扩展属性 装备时，是物体的特殊属性 道具时，是物体的个数
        // 每个道具的属性只能由7项目  special0 ~ special6 (uint8 )
        // 针对不同的道具，不同的道具有不同的属性说明
        // (武器, 衣服, 鞋子, 手套, 头盔, 饰品 )
        // 如果该项数值为0表示该项目无效!!
        SEquipData() { memset( this, 0, sizeof(SEquipData) );unBindCount = 0xffff; }

        float  usHP           ;                                 // 装备耐久度
        int32  usHpMax        ;                                 // 装备耐久度最大值
        uint16 baseRands  [ EConstDefine_BaseRandMaxCount   ];  // 蓝色附加随机属性
        uint16 purpleRands[ EConstDefine_PurpleRandMaxCount ];  // 紫色附加随机属性
        uint16 suitRands  [ EConstDefine_SuitRandMaxCount   ];  // 技能套装附加随机属性
        uint16 gemIds     [ EConstDefine_GemHoleMaxCount    ];  // 嵌套宝石
        uint8  gemHoleCount   ;                                 // 装备打孔数
        uint8  ucLevel        ;                                 // 装备强化星级
        uint8  quality        ;                                 // 装备品质 不一定是颜色品质 可能是其他用途
        uint8  element        ;                                 // 五行哪个
		uint16 unBindCount	  ;									// 装备解绑的次数 -1表示无限解绑 0表示无法解绑 正数表示解绑次数 默认值为-1 用于和配置文件进行对比
		float  fScore		  ;									// 装备评分
		uint32 ustEquipType	  ;                                 // 装备类型 可以丢弃
		uint8  ucSoulPer	  ;									// 装备铭刻加成百分比
    };

    struct STalismanData
    {   // 法宝扩展属性
        STalismanData() { memset( this, 0, sizeof(STalismanData) ); }

        uint8  quality        ;                                 // 法宝品质 1凡品、2良品、3精品、4仙物、5神器
        uint8  level          ;                                 // 法宝等级
        uint32 daoxing        ;                                 // 道行
        uint32 nimbus         ;                                 // 灵气
        uint32 nimbusMax      ;                                 // 灵气最大值
        uint16 nimbusRestore  ;                                 // 灵气回复
        int64  exp            ;                                 // 熟练度
        uint16 talismanRands[EConstDefine_TalismanRandMaxCount];// 修炼属性
        uint8  randAttrNumber ;                                 // 激活修炼属性数
    };

	struct SPetEquipData
	{
		SPetEquipData() { memset( this, 0, sizeof(SPetEquipData) ); isTimeEnd = false;}
		int						Strength;//力量
		int						Agility;//敏捷
		int						Stamina;//耐力
		int						Intelligence;//灵力
		uint16					iEquipLevelReq;//等级需求
		bool					isTimeEnd;//装备是否已经无效化了 默认为false
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
		equipdata.unBindCount = 0xffff;
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
        if (nStarLevel == 0 ||  nStarLevel > EL_StarMax)
        { return; }

        if (bRandom)
        { equipdata.ucLevel = theRand.rand16() % (nStarLevel + 1); }
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

	//是否已做过装备随机属性鉴定(前提是装备)
	bool HasBaseRanded() const
	{
		return equipdata.baseRands[0] != EConstDefine_HasBaseRanded;
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
    void ReadTalismanInfo(ReadData inP,int nSize);
    void ReadStorgeInfo  (ReadData inP,int nSize);
    void ReadLockInfo    ( ReadData inP,int nSize );
	void ReadPetEquipInfo( ReadData inP,int nSize );

    bool          bCanUse       ;     // 只做为逻辑，不作为存储
    SItemBaseInfo itembaseinfo  ;
    SEquipData    equipdata     ;
    STalismanData talismandata  ;
	SPetEquipData petequipdata	;
    SStorageInfo  storageinfo   ;
    SLockInfo     xLockInfo     ;
};

inline bool SortItemID( const SCharItem& left, const SCharItem& right )
{
    return ( left.itembaseinfo.ustItemID < right.itembaseinfo.ustItemID) ? true : false;
}


// 心法影响技能状态属性枚举 跟g_szSkillStatusAttrType一样
enum ESkillStatusAttrType
{
    SkillAttr_None = 0        ,
    SkillAttr_Strength        ,   //力量
    SkillAttr_Agility         ,   //敏捷
    SkillAttr_Stamina         ,   //耐力
    SkillAttr_Intelligence    ,   //智力
    SkillAttr_HPDamage        ,   //附加伤害
    SkillAttr_HPRestore       ,   //附加治疗
    SkillAttr_AOECharNum      ,   //攻击人数
    SkillAttr_PhysicsAttack   ,   //物理攻击
    SkillAttr_MagicAttack     ,   //法术攻击
    SkillAttr_PhysicsDefend   ,   //物理防御
    SkillAttr_MagicDefend     ,   //法术防御
    SkillAttr_Exact           ,   //命中
    SkillAttr_Dodge           ,   //闪避
    SkillAttr_Critical        ,   //暴击率
    SkillAttr_CriticalIntensity,  //暴击伤害
    SkillAttr_Tenacity        ,   //韧性
    
    StatusAttr_Strength        ,   //力量
    StatusAttr_Agility         ,   //敏捷
    StatusAttr_Stamina         ,   //耐力
    StatusAttr_Intelligence    ,   //智力
    StatusAttr_HPDamage        ,   //附加伤害
    StatusAttr_HPRestore       ,   //附加治疗
    StatusAttr_PhysicsAttack   ,   //物理攻击
    StatusAttr_MagicAttack     ,   //法术攻击
    StatusAttr_PhysicsDefend   ,   //物理防御
    StatusAttr_MagicDefend     ,   //法术防御
    StatusAttr_Exact           ,   //命中
    StatusAttr_Dodge           ,   //闪避
    StatusAttr_Critical        ,   //暴击率
    StatusAttr_CriticalIntensity,  //暴击伤害
    StatusAttr_Tenacity        ,   //韧性
    StatusAttr_SuckDamage      ,   //吸收伤害

	//这个新加的，就放这后面吧
	SkillAttr_AddHPMax		  ,		//HP上限
	SkillAttr_AddMPMax		  ,		//MP上限

    SkillAttr_MaxSize          ,   
};

static char* (g_szSkillStatusAttrType[]) =
{
    "SkillAttr_None"            ,
    "SkillAttr_Strength"        ,   //力量
    "SkillAttr_Agility"         ,   //敏捷
    "SkillAttr_Stamina"         ,   //体质
    "SkillAttr_Intelligence"    ,   //智力
    "SkillAttr_HPDamage"        ,   //附加伤害
    "SkillAttr_HPRestore"       ,   //附加治疗
    "SkillAttr_AOECharNum"      ,   //攻击人数
    "SkillAttr_PhysicsAttack"   ,   //物理攻击
    "SkillAttr_MagicAttack"     ,   //法术攻击
    "SkillAttr_PhysicsDefend"   ,   //物理防御
    "SkillAttr_MagicDefend"     ,   //法术防御
    "SkillAttr_Exact"           ,   //命中
    "SkillAttr_Dodge"           ,   //闪避
    "SkillAttr_Critical"        ,   //暴击率
    "SkillAttr_CriticalIntensity" , //暴击伤害
    "SkillAttr_Tenacity"        ,   //韧性

    "StatusAttr_Strength"        ,   //力量
    "StatusAttr_Agility"         ,   //敏捷
    "StatusAttr_Stamina"         ,   //体质
    "StatusAttr_Intelligence"    ,   //智力
    "StatusAttr_HPDamage"        ,   //附加伤害
    "StatusAttr_HPRestore"       ,   //附加治疗
    "StatusAttr_PhysicsAttack"   ,   //物理攻击
    "StatusAttr_MagicAttack"     ,   //法术攻击
    "StatusAttr_PhysicsDefend"   ,   //物理防御
    "StatusAttr_MagicDefend"     ,   //法术防御
    "StatusAttr_Exact"           ,   //命中
    "StatusAttr_Dodge"           ,   //闪避
    "StatusAttr_Critical"        ,   //暴击率
    "StatusAttr_CriticalIntensity",  //暴击伤害
    "StatusAttr_Tenacity"        ,   //韧性
    "StatusAttr_SuckDamage"      ,   //吸收伤害

	//这个新加的，就放这后面吧
	"SkillAttr_AddHPMax"		,	//HP上限
	"SkillAttr_AddMPMax"		,	//MP上限
};

struct SCharXinFa
{ // 玩家身上心法的定义
    SCharXinFa()
    { Reset(); }

    void Reset()
    {
        memset(this, 0, sizeof(SCharXinFa));
    }

    void Write( CDataChunkWriter* w );
    void Read ( BYTE* buffer,DWORD size );

    unsigned short nXinFaID     ;
    unsigned char  nXinFaLevel  ;
};

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
    
    unsigned short ustSkillID;      // 技能ID
    unsigned char  stSkillLevel;    // 等级
    DWORD          dwCurSkillExp;   // 技能经验
    bool           bAvailable;      // 客户端使用

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
		MICD_MountMaxLevel		  = 12, // 坐骑最大强化等级
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
                //旧公式: 坐骑当前的属性值 = 坐骑初始的属性值 + （等级-1）*（初始属性^0.16/(12.5^0.16)+成长率）* 增值 
                //currentAttribute[i] = baseAttribute[i] + (level-1) * ( pow( (float)baseAttribute[i], (float)0.16) / pow( (float)12.5, (float)0.16) + growRate ) * aptitudeAttribute[i];

                //新公式: 坐骑当前的属性值 = 坐骑初始的属性值 + （等级-1） + 分配的潜能
                //currentAttribute[i] = baseAttribute[i] + (level-1) + potentialAttribute[i];

				//新公式1: 坐骑当前的属性值 = 坐骑初始的属性值 + 强化分配的潜能
				currentAttribute[i] = baseAttribute[i] + potentialAttribute[i];
				if (currentAttribute[i] <= 0.0f)
					currentAttribute[i] = baseAttribute[i];
            }
        }

        void Write( CDataChunkWriter* w );
        void Read( BYTE* szBuff,DWORD nSize );

        char        szName[ dr_MaxPlayerName ];     // 名字
        uint16      id;                             // 坐骑种类ID
        int64       guid;                           // 物品世界唯一ID
        uint8       isActive;                       // 是否被激活
        uint16      level;                          // 等级/强化等级
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
        float          potentialAttribute[EBaseAttr_MaxSize];   // 已分配潜力点/强化加成的潜力点
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



struct SPetItem
{
    enum EPetConstDefine
    {
        PetDefine_MaxSkillCount     = 12, // 技能数
		
		PetEquip_Begin				= 0,
		PetEquip_One				= 0,
		PetEquip_Two				= 1,
		PetEquip_Three				= 2,
		PetEquip_Four				= 3,
		PetEquip_Fine				= 4,
		PetEquip_MaxSum				= 5, // 副将装备的装备数量
    };

    struct SBaseInfo
    {
        SBaseInfo()
        { Reset(); }

        void Reset()
        { memset( this, 0, sizeof( SBaseInfo)); }

        void ResetAttibute()
        {
            memset( baseAttribute,     0, sizeof(baseAttribute     ));
            memset( aptitudeAttribute, 0, sizeof(aptitudeAttribute ));
            memset( potentialAttribute,0, sizeof(potentialAttribute));
        }

        void Write( CDataChunkWriter* w );
        void Read( BYTE* szBuff,DWORD nSize );

        char    szName[ dr_MaxPlayerName ];     // 名字
        uint32  petId;                          // ID
        uint16  itemId;                         // 对应物品ID
        int     petType;                        // 宠物类型
        int64   guid;                           // 物品世界唯一ID
        uint8   isActive;                       // 是否出战
        uint16  level;                          // 等级
        uint8   quality;                        // 品质
        uint16  takeLevel;						// 携带等级
        uint8   aptitudeLevel;                  // 资质等级
        uint8   attackType;						// 战斗类别
        uint16  battleValue;                    // 战斗力
        uint8   sex;							// 性别
        uint8   characterize;					// 性格
        int64   exp;                            // 经验
        int32   daoxing;                        // 道行
        int     hp;                             // 生命值
        uint8   loyalty;						// 快乐度
        uint32  duration;						// 寿命
        uint8   savvy;                          // 悟性
        uint8   bone ;							// 根骨
        uint8   isShowGrow;                     // 是否显示成长率
        uint8   growStar;                       // 成长率星级
        uint16  growRate;                       // 成长率
        uint8   phyle;							// 种族
        uint8   element;						// 五行
        uint8   breedNum;                       // 繁殖次数
        uint8   generation;                     // 几代宠物
        uint32  regenerateTime;                 // 出战冷却时间
        uint16  lastRealizeSkillLevel;          // 上一次领悟技能等级

        uint16	nPotentialPoint;                            // 可分配潜力点
        uint16  baseAttribute       [EBaseAttr_MaxSize];    // 基础初始属性
        uint16  potentialAttribute  [EBaseAttr_MaxSize];    // 已分配潜力点
        uint16  aptitudeAttribute   [EBaseAttr_MaxSize];    // 基础资质属性

		uint32	PetModeID;						// 副将的模型ID
		__int64 n64ModeUseTime;					// 副将模型到期时间 到期后修改PetModeID 模型为0
		SCharItem PetEquip[PetEquip_MaxSum];	// 副将身上的装备数组 装备不修改外观 只影响属性

        uint16  GetCurrentBaseAttr( uint8 attrType );       // 当前基础属性
        uint16  GetCurrentAptitude( uint8 attrType );       // 当前资质属性
        uint32  GetFightAttribute ( uint8 attrType );       // 二级战斗属性

		uint32	GetPetNewModeID();
		void	SetPetModeID(uint32 ModeID,__int64 EndTime);

		bool    IsExitesEquip();
    };

    struct SSkillInfo
    {
        SSkillInfo()
        { memset( this, 0, sizeof( SSkillInfo)); }

        bool              AddSkill    ( unsigned short skillId, unsigned short skillLevel = 1 );
        bool              ReplaceSkill( unsigned short skillId, unsigned short skillLevel, int nIndex );
        bool              RemoveSkill ( unsigned short skillId );
        const SCharSkill* GetSkill    ( unsigned short skillId );
        int               GetCurrentSkillCount();
        void Reset();

        void Write( CDataChunkWriter* w );
        void Read( BYTE* szBuff, DWORD nSize );

        SCharSkill skills[PetDefine_MaxSkillCount];  // 技能
        uint8      initiativeSkillNumber;            // 开启主动技能槽个数
    };

    struct SLockInfo
    {   
        SLockInfo() : bIsLocked( false ), n64UnLockTime( 0 ), nUnLockLeftTime( 0 ){}

        void Write( CDataChunkWriter* w );
        void Read( BYTE* szBuff, DWORD nSize );

        bool   bIsLocked;         // 物品是否加锁
        int64  n64UnLockTime;     // 解锁的到期时间( 锁定状态 和 解锁状态这个值为 0 )
        uint32 nUnLockLeftTime;
    };

    struct SBreedInfo
    {
        int64   targetGuid    ;     // 对象宠物GUID
        uint32  targetCharDBID;     // 对方玩家DBID
        uint8   targetQuality ;     // 对方宠物品质
        int64   commitTime    ;     // 提交时间

        void Clear() { memset( this, 0, sizeof( SBreedInfo )); }
        void Write( CDataChunkWriter* w );
        void Read( BYTE* szBuff, DWORD nSize );
    };

    int     GetPetID      () const { return baseInfo.petId;     }
    int64   GetPetGuid    () const { return baseInfo.guid ;     }
    const char* GetPetName() const { return baseInfo.szName;    }

    bool IsPassUnLockTime( bool bSetLeftTime = false );
    bool IsLock() { return xLockInfo.bIsLocked; }
    void SetLock( bool bValue )
    {
        xLockInfo.bIsLocked = bValue;
        xLockInfo.n64UnLockTime = 0;
    }
    int64 GetUnLockTime() { return xLockInfo.n64UnLockTime; }
    void  SetUnLockTime( int64 n64Time ) { xLockInfo.n64UnLockTime = n64Time; }

    void   SetUnLockLeftTime( uint32 nLeftTime ) { xLockInfo.nUnLockLeftTime = nLeftTime; }
    uint32 GetUnLockLeftTime() { return xLockInfo.nUnLockLeftTime; }

    void Write( CDataChunkWriter* w);
    void Read( BYTE* bybuff,DWORD dwsize );

    SBaseInfo  baseInfo;
    SSkillInfo skillInfo;
    SBreedInfo breedInfo;
    SLockInfo  xLockInfo;
};

struct SCharSkills
{
    SCharSkills()
    { }

    void write(CDataChunkWriter* w);
    void read(BYTE* bybuff,DWORD dwsize);

    SCharXinFa xinfa[ More_iMaxXinFa      ];
    SCharSkill skill[ More_iMaxSkillKnown ];
	SCharSkill heroSkill[More_iMaxHeroSkill];
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
	EEquipPartType_Shoulder          , // 肩甲
//    EEquipPartType_Manteau           , // 披风
    EEquipPartType_Necklace          , // 项链
    EEquipPartType_Sash              , // 腰带
    EEquipPartType_LeaderCard        , // 掌门卡
    EEquipPartType_Amulet            , // 护身符
    EEquipPartType_AecorativeGoods   , // 装饰的物品
    EEquipPartType_AecorativeClothing, // 装饰的衣服
	EEquipPartType_Trousers			 , // 裤子
    EEquipPartType_MaxEquitPart      , // 最大可装备个数
};

struct SCharVisual
{
    enum EShowFlagType
    {
        EShowFlagType_Aecpratove = 1 << 0, // 是否显示时装
        EShowFlagType_Helmet     = 1 << 1, // 是否显示头盔
        EShowFlagType_Signature  = 1 << 2, // 是否显示心情
		EShowFlagType_Hero		 = 1 << 3, // 是否显示主将形态
		EShowFlagType_RankTitle  = 1 << 4, // 是否显示军阶
    };

    uint16    hairId;                                   // 头发模型Id
    uint16    faceId;                                   // 脸部模型Id    
	uint8	  defaultModelIndex;						// 裸体模型索引
    uint8     showFlag;                                 // EShowFlagType
    float     fModelPercent;                            // 模型缩放百分比
    SCharItem equipitem[ EEquipPartType_MaxEquitPart ]; // 身上装备的道具
    SCharItem talisman;                                 // 法宝

    SCharVisual()
    {
        hairId        = 0;
        faceId        = 0;
        showFlag      = 0;
        fModelPercent = 1.0f;
		defaultModelIndex = 0;
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
    { return _HAS_FLAG( showFlag, EShowFlagType_Aecpratove); }  // 是否显示时装

    bool IsShowHelmet()
    { return _HAS_FLAG( showFlag, EShowFlagType_Helmet); }      // 是否显示头盔

    bool IsShowSignature()
    { return _HAS_FLAG( showFlag, EShowFlagType_Signature); }   // 是否显示心情

	bool IsShowHero()
	{ return _HAS_FLAG( showFlag, EShowFlagType_Hero); }		// 是否显示主将形态

	bool IsShowRankTitle()
	{ return _HAS_FLAG( showFlag, EShowFlagType_RankTitle); }   // 是否显示军阶


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

    void ShowSignature( bool bShow )
    { // 显示心情
        if ( bShow )
        { _SET_FLAG( showFlag, EShowFlagType_Signature ); }
        else
        { _CLS_FLAG( showFlag, EShowFlagType_Signature ); }
    } 

	void ShowHero( bool bShow )
	{ // 是否显示主将形态
		if ( bShow )
		{ _SET_FLAG( showFlag, EShowFlagType_Hero ); }
		else
		{ _CLS_FLAG( showFlag, EShowFlagType_Hero ); }
	} 

	void ShowRankTitle( bool bShow )
	{ // 显示军阶
		if ( bShow )
		{ _SET_FLAG( showFlag, EShowFlagType_RankTitle ); }
		else
		{ _CLS_FLAG( showFlag, EShowFlagType_RankTitle ); }
	} 
    
    void WriteVisual ( CDataChunkWriter* w);
    void ReadVisual ( uint8* bybuff, uint32 dwsize );
};

struct SCharStorageData
{
    SCharStorageData()
    { memset( this, 0, sizeof(SCharStorageData) ); }

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
        EAT_Pet,   // 宠物
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

struct SQuestTimeRecord
{ // 任务的时间记录
    SQuestTimeRecord()
    {
        id = 0;
        time = 0;
    }

    uint16  id  ; // 任务id
    __int64 time; // 任务开始时间 或者 结束时间 (看任务Id对应的配置)
};

struct SSysVars
{
    SSysVars()
    {
        memset( szVars,    0, sizeof( szVars    ));
        memset( questTime, 0, sizeof( questTime ));
    }

    void writeVars( CDataChunkWriter* w );
    void readVars( ReadData inP,int nSize );

    short            szVars[ More_iMaxVars ];
    SQuestTimeRecord questTime[ QuestLimitTimeMaxCount ]; // 任务的时间限制
};

struct SCardData
{
	SCardData()
	{
		Reset();
	}
	void Reset()
	{
		memset( shCardLevel, -1, sizeof( shCardLevel ) );
		memset( unCardAchieve, 0, sizeof ( unCardAchieve ));
	}

	void writeCardData( CDataChunkWriter* w );
	void readCardData( BYTE* bybuff,DWORD dwsize );

	short shCardLevel[ More_nCardMax ];
	uint8 unCardAchieve[ More_nCardAchieve ];
};

struct SRankTitleData
{
	SRankTitleData()
	{
		Reset();
	}

	void Reset()
	{
		shCurRankTitleId = -1;
		bGetSalary = 0;
		dGetSalaryTime = 0;
	}

	void writeRankTitleData( CDataChunkWriter* w );
	void readRankTitleData( BYTE* bybuff,DWORD dwsize );

	short shCurRankTitleId; //当前军阶Id
	BYTE bGetSalary; //今天是否领过俸禄
	DWORD dGetSalaryTime; //领取俸禄刷新的时间
};

struct SHuntingData
{
	SHuntingData()
	{
		Reset();
	}
	void Reset()
	{
		memset( nCurRandIds, 0, sizeof(nCurRandIds) );
		nCount = 0;
		dFreeRefreshTime = 0;
	}

	void writeHuntingData( CDataChunkWriter* w );
	void readHuntingData( BYTE* bybuff,DWORD dwsize );

	int nCurRandIds[More_nHuntingNum]; //玩家身上随即出来的狩猎任务
	int nCount; //今天狩猎的个数
	DWORD dFreeRefreshTime; //免费刷新的时间
};

struct SCharBuff
{ //关于状态的数据
    enum StatusEventType
    {
        StatusEventType_Other,
        StatusEventType_Skill,
        StatusEventType_Mount,
    };

    int16           StatusID;        // 该状态的id编号    
    int16           iLevel;          // 附加该状态的等级(如果 <= 0 表示没有附加状态)
    GameObjectId    masterId;        // 该状态的释放者的ID    
    int             nEffectID;       // 客户端在特效管理器内的ID
    uint8           bLastEffect;     // 是否最后一个特效
    uint32          dwStartTime;     // 开始时间
    uint32          dwPreDamage;     // 上次进行伤害的时间
    uint32          dwDurationTime;  // 状态持续时间
    int             restoreType;     // 存储类型
    uint32          dwPlayerDBID;    // 释放者的DBID
    int64           nInt64StartTime; // 未来失效时间
    uint8           bStop;           // 是否停止
    uint8           eventType    ;   // 触发该状态的类型
    uint16          eventValue   ;   // 触发该状态的值
    uint8           lapoverNum   ;   // 叠加次数

    SCharBuff()
    { Reset(); }

    void Reset()
    {
        StatusID             = -1;
        iLevel               = -1;
        masterId             = InvalidGameObjectId;
        dwStartTime          = 0;
        dwPreDamage          = 0;
        nEffectID            = -1;
        bLastEffect          = false;
        dwDurationTime       = 0;
        restoreType          = false;
        dwPlayerDBID         = 0;
        nInt64StartTime      = -1;
        bStop                = 0;
        eventType            = 0;
        eventValue           = 0;
        lapoverNum           = 0;
    }

    void WriteBodyStatus( CDataChunkWriter *w       );
    void ReadBodyStatus ( BYTE* bybuff,DWORD dwsize );
};

struct SCharOtherDataClient0
{
    SCharOtherDataClient0()
    { memset( this, 0, sizeof(SCharOtherDataClient0) ); }
    
    SCharPosData  pos;
    SCharPosData  sBornPos;
    void WriteOtherDataClient0(CDataChunkWriter *w);
    void ReadOtherDataClient0 (BYTE* bybuff,DWORD dwsize);
};

struct SCharItemBagData
{
    SCharItemBagData()
    { }

    SCharItem       stPackItems     [ITEM_BAGMAX]           ;   // 普通包裹道具
    SCharItem       ciMaterialItems [ITEM_BAGMATERIAL_MAX]  ;   // 材料包裹道具
    SCharItem       ciTaskItems     [ITEM_BAGTASK_MAX]      ;   // 任务包裹道具
    SMountItem      miItems         [ITEM_MOUNT_MAXCOUNT]   ;   // 坐骑
    SPetItem        petItems        [ITEM_PET_MAXCOUNT]     ;   // 宠物
    SPetItem        petBreedItem                            ;   // 正在繁殖的宠物
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

    GameObjectId nNpcID;
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

enum ECharTime64Var
{
    ECT_LastLoginTime       ,   // 上次登录时间
    ECT_LastOfflineTime     ,   // 上次下线时间
    ECT_ChangeCountryTime   ,   // 上次更改国籍时间
    ECT_ExploitTime         ,   // 功勋值更改时间

    ECT_MaxTimeVar  = 20    ,   // 人物身上的时间计数变量
};

enum ECharTime32Var
{
    ETV32_RewardTime        ,   // 领取奖励时间

    ETV32_MaxTimeVar = 20   ,   
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
    TitleCounter     nTitleCounters [MAX_TITLE_COUNT];          // 人物称号记数
    SpecialQuestInfo xPubQuestInfo  [MAX_SPECIALQUEST_COUNT];   // 记录酒馆任务时间信息
    SpecialQuestInfo xConQuestInfo  [MAX_SPECIALQUEST_COUNT];   // 记录征伐任务间信息
    unsigned long    dwGuideQuestInfo;                          // 引导任务的完成情况
    bool             isOfflineHook   ;                          // 上一次是否离线挂机
    uint32           totalHookTime   ;                          // 累计离线挂机时间

    int64            n64TimeVars    [ECT_MaxTimeVar];           // 时间计数变量
    unsigned int     n32TimeVars    [ETV32_MaxTimeVar];         // 32位时间计数变量

    //SPressKeySuit    xPressKeySuit  [MAX_PRESSKEYSUIT_COUNT];   // 一键换装
};

enum EGuideState
{
    EGuideState_UnFinish    = 0,
    EGuideState_Finish      = 1,
};

struct SCharKillPlayer
{
	unsigned int PlayerDBID;
	unsigned short Num;
};

struct SCharOtherDataClient : public SCharOtherDataClient0
{ 
    SCharOtherDataClient()
    {
        chProtectLockTime = 1;
        dwBanSpeakTime    = 0;

        memset( recipes,    0, sizeof(recipes) );
        memset( guideVars,  0, sizeof(guideVars) );

		PetDuration = 0;

		sevenDayStartTime = 0;
		equipTotalScore = 0;

		nThreeDayVision = 0;
		nThreeDayValue = 0;

		nBeginGameGeneralBattleTime = 0;
		
    }

    // 添加玩家背包 需要UpDataItemPackInfo
    void writeOtherdataClient(CDataChunkWriter *w);
    void readOtherdataClient(BYTE* bybuff,DWORD dwsize);
    void readFightData(ReadData inP,int nsize);

    void  SetGuideVar( int16 nId, uint8 state );
    uint8 GetGuideVar( int16 nId );

    SCharSkills          skills;         // 技能背包
    SCharHotKeys         hotkeys;        // 热键背包            
    short                stMountId;      // 当前正在骑着的坐骑Id [<0没有骑坐骑 >0 一定骑着坐骑栏里出战的坐骑]
    float                fDirX;          // 朝向X -1 默认
    float                fDirY;          // 朝向Y 0
    SCharBuff            sCharBodyStatus[BodyStatusType_Max];       // 状态
    unsigned short       recipes        [MAX_RECIPE_COUNT];         // 人物配方
    unsigned char        chProtectLockTime;                         // 交易保护时间( 单位分钟 )   
    unsigned long        dwBanSpeakTime;                            // 禁言时间    ( 单位分钟 )
    unsigned char        guideVars      [MAX_GUIDE_COUNT];          // 新手指导
	unsigned int		 PetDuration;
	SCardData			 cards;							// 卡牌
	__int64				 sevenDayStartTime;				// 七天乐开启时间
	uint32				 equipTotalScore;				// 装备总分
	SRankTitleData		 rankTitle;						// 军阶
	SHuntingData		 sHunting;						// 狩猎

	unsigned int		nThreeDayValue;				// 记录玩家3开服3日的领取奖励的记录
	unsigned short		nThreeDayVision;				// 记录开服3天的版本信息 不同的版本表示以前的 nThreeDayValue 将被清空

	__int64				nBeginGameGeneralBattleTime;	//公会约战的CD时间
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
		nFamilyID = 0;
		nRecordKillPlayerTime =0;
		nsuanimalID = 0;
		ClearKillInfo();
		exitGameTime = 0;
		LeaveExpHourSum = 0;
    }

    void WriteOtherDataBlob (CDataChunkWriter *w);
    void ReadOtherDataBlob (BYTE* bybuff,DWORD dwsize);
    void ReadOtherImport(ReadData inP,int nsize);

	void  ClearKillInfo();
	uint16 GetKillSum(unsigned int DBID);
	void  AddKIllPlayer(unsigned int DBID);
	uint16 GetAllKillSum();
	void SetExitTimeNow();
	void SetLeaveHourSum();
    
    SSysVars      vars;                        // 服务端系统变量
    bool          bNewChar;                    // 是否为新建角色
    unsigned long dwHighShoutCDTime;           // 世界喊话冷却剩余时间    

	unsigned int		dwRecordKillMonsterTime;     // 记录杀怪的最后时间
    unsigned int		dwRecordKillMonsterCount;    // 记录杀怪的个数

    unsigned int   nRecordHonourTime;          // 记录最后得到荣誉的时间
    unsigned short nRecordHonourCount;         // 记录每日荣誉值

    SecondPassword xSecondPassword;            // 玩家2级密码

    unsigned int nGuildID;                     // 公会ID  
    unsigned int dwLeaveGuildTime;             // 离开帮派的时间

	unsigned int nFamilyID;						// 家族ID

	__int64 nRecordKillPlayerTime;				//记录最后杀死敌国玩家的时间(在野外)

	__int64  nsuanimalID;						//下线时候 处于出战状态的副将ID

	//unsigned int PetDuration;					//玩家的指挥点

	SCharKillPlayer		 KillList[MAX_KILLSUM];			// 玩家当天杀人计数
	__int64				 exitGameTime;					//玩家上次离开游戏的时间
	unsigned int		 LeaveExpHourSum;				// 离线的小时数累计
};

struct SCharAchieve
{
    SCharAchieve() { memset( this, 0, sizeof(SCharAchieve)); }

    void Write( CDataChunkWriter *w );
    void Read ( BYTE* buffer, DWORD size );

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

struct SPetIdentify
{
    SPetIdentify() { Reset(); }

    void Reset() { memset( this, 0, sizeof(SPetIdentify)); }

    void Write( CDataChunkWriter *w );
    void Read ( BYTE* buffer, DWORD size );

    unsigned short  petType;        // 宠物类型
    unsigned short  identifyTotal;  // 鉴定次数累计
};

struct SIdentifyData
{
    SIdentifyData() { memset( this, 0, sizeof(SIdentifyData)); }

    void Write( CDataChunkWriter *w );
    void Read ( BYTE* buffer, DWORD size );

    bool AddPetIdentify         ( const SPetIdentify& xIdentify );
    bool RemovePetIdentify      ( uint16  petType );
    SPetIdentify* GetPetIdentify( uint16  petType );

    SPetIdentify    petIdentify[MAX_PETIDENTIFY_COUNT]; // 宠物图鉴
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
    SCharBaseInfo    baseinfo;      // 基本数据
    SCharVisual      visual;        // 角色外观
    SCharOtherData   otherdata;     // 额外数据
    SCharItemBagData itemData;      // 背包数据
    SExtendData      extendData;    // 扩充数据
    SAchieveData     achieveData;   // 成就数据
    SIdentifyData    identifyData;  // 图鉴数据
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
        nPetIndex   = -1;
        nHp         = 0;
        nMp         = 0;
        varValue    = -1;
        nSummonSkillID = -1;
        memset( sCharBodyStatus, 0, sizeof(SCharBuff) * BodyStatusType_Max );
    }

    int                  nPetID;
    int16                nPetIndex;
    int                  nHp;
    int                  nMp;
    int                  varValue;                  // 变量值
    int16                nSummonSkillID;            // 召唤技能
    SCharBuff sCharBodyStatus[BodyStatusType_Max];  // 状态
	bool				 IsCanRide;
};

struct SRuntimeInfo
{ 
    SRuntimeInfo()
    {
        mountId                   = 0;
        dwProtectLockLeaveTime    = 0;
        dwUpdatePKValueTime       = 0;
        inFightTime               = 0;
        dwOnLineTime              = 0;

		nAntiAddictionDbOnlineTime = 0;
		nOffTimeAntiAddiction      = 0;
		nAntiAddicationStatus      = enumAntiAddictionStateNormal;
		bGetAntiAddictionInfo      = false;

        bReqRemoveMarriage        = false;
        bForceRemove              = false;
        nCountrySpeakSpaceTime    = 0;
		PkValueTimeLog			  = 0;
		OnLineTime				  = 0;
    }

    // 角色数据 Runtime 级别
    short              mountId                  ; // 当前正在骑着的坐骑Id [<0没有骑坐骑 >0 一定骑着坐骑栏里出战的坐骑]
    unsigned int       dwProtectLockLeaveTime   ; // 交易保护剩余时间 ( == 0,已经到了锁定时间 )
    int                nCountrySpeakSpaceTime   ; // 国家发言冷却时间
    unsigned int       dwUpdatePKValueTime      ; // 在线泡PK点时间
    RunTimePetInfo     xPetInfo[EPT_Max]        ; // 1:技能宠物  2:保护怪 3:捕获宠物
    uint32             inFightTime              ; // 在战斗中的时间
    uint32             dwOnLineTime             ; // 角色本次在线时间 ( 单位: 毫秒 )
    SCharItem          xBuyBackItem[10]         ; // 回购物品列表
    bool               bGetAntiAddictionInfo     ; // 是否已经得到防沉迷信息
    uint32             nAntiAddictionDbOnlineTime; // 在线单位分钟 在每次同步的时候有可能变很大（一个账号在几个服同时玩）
    uint32             nOffTimeAntiAddiction     ; // 下线单位分钟
    AntiAddictionState nAntiAddicationStatus     ; // 防沉迷状态
    bool               bReqRemoveMarriage       ; // 离婚请求数据
    bool               bForceRemove             ;
	uint32			   PkValueTimeLog			;//PK值计时 不存入数据库		
	uint32			   OnLineTime;				//在线时间
};

struct SAttrUp
{
    char  cType;
    short stWhichAttr;
};

struct SEffectDamage
{
    GameObjectId stWho;
    DWORD dwState;
    short stDamage;
};

struct SAttTargetResult
{
    SAttTargetResult()
    { Reset(); }

    void Reset()
    { memset( this, 0, sizeof( SAttTargetResult));}

    GameObjectId stTargetWho;        // 攻击的目标
    GameObjectId stAttackerWho;      // 谁是攻击者

    int   stTagHpNum;         // 目标跳出的Hp
    int   stSrcHpNum;         // 攻击者跳出的Hp

    int   stTagMpNum;         // 目标跳出的Mp
    int   stSrcMpNum;         // 攻击者跳出的Mp

    int   nTagHp;             // 被攻击目标剩下的hp
    int   nSrcHp;             // 攻击者hp

    int   nTagMp;             // 被攻击目标剩下的Mp
    int   nSrcMp;             // 攻击者Mp

    short nBackAttack;        // 目标受背击跳出的数值
    int   nShieldHp;          // 魔法盾吸收HP

    char  cBalanceType;       // 法术应用的结算方式
    short nStatusFlag;        // 状态特征flag
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
    SMovePos()
    { memset( this, 0, sizeof(SMovePos) ); }

    float fX;       // 世界坐标的X轴
    float fY;       // 世界坐标的Y轴
    float fZ;       // 世界坐标的Z轴
    float fV;       // 行走速度百份比(1为正常).如0.8,1.2之类的
    float fStep;    // 步长
    DWORD dwTime;   // 到达目标点时所停留的时间(毫秒).
    short stSceneId;// 播放场景ID
    char  szActionName[32];
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
    bool		   bIsCharTarget; // 判断攻击的目标是对地面还是特别的npc
    GameObjectId   nCharID;       // 作用目标的ID
    D3DXVECTOR3	   vPos;		  // 作用目标的位置
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

struct QuestScript
{
    QuestScript() : m_nVMId(-1) {}
    short stQuestId; // 任务Id
    char  chState;   // 状态
    int   m_nVMId;   // 脚本Id
    short stEnter;   // 脚本入口
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


enum EEctypeSageDefine
{
    EctypeStageValue1 = 16,         // 副本场景ID偏移
    EctypeStageValue2 = 0xFFFF,     //                  
};

#pragma pack(pop) 

//////////////////////////////////////////////////////////////////////////
// Typedef
typedef std::vector<std::string> StringContainer;
typedef StringContainer::iterator ItrStringContainer;

//////////////////////////////////////////////////////////////////////////
// funcion


inline DWORD EctypeId2MapId( DWORD dwEctypeId )
{
    return ( dwEctypeId & EctypeStageValue2 );
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
    return static_cast<int>( ceil( (fValue - MAPTILESIZE * 0.5f) / MAPTILESIZE ) );
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

template< typename T >
inline int GetRandIndex( T* pProbability, int count, int randNumber )
{
    if (pProbability == NULL)
    { return 0; }

    int rate = 0;
    for (int i=0; i<count; ++i)
    {
        rate += pProbability[i];
        if (randNumber <= rate)
        { return i; }
    }

    return 0;
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

// 检查名字是否含有特殊运算符
inline bool CheckCreateName( const std::string& strName )
{
    if ( strName.empty() )
    { return false; }

	//strName.find( theXmlString.GetString(eClient_Chat_Begin) ) != string::npos )
    if (strName.find("'") != string::npos || strName.find("-") != string::npos ||
        strName.find("_") != string::npos || strName.find("%") != string::npos ||
        strName.find(" ") != string::npos || strName.find(":") != string::npos || strName.find("\\") != string::npos )
    { return false;}
    return true;
}

inline bool IsFloatZero(const float x, float epsilon = 1e-6f) 
{
    return fabs(x) < epsilon;
}

template< typename T >
inline void StrToIntArray( const char* str, T *iArray, int size, const char* split )
{
    if ( str == NULL || iArray == NULL || split == NULL || size == 0)
    { return; }

    int index = 0;
    char* token = NULL;
    char* next_token = NULL; 
    token = strtok_s ( const_cast<char*>( str ), split, &next_token ); 
    while( token != NULL ) { 
        if ( index >= size )
        { return; }

        iArray[index] = atoi( token );
        token = strtok_s( NULL, split, &next_token ); 
        ++index;
    } 
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

//特殊物品ID
enum SpecialItemID
{
	SID_ProtectStarSix		= 4505, //6星保级材料
	SID_ProtectStarNine		= 4506, //9星保级材料
	SID_ProtectStarTwelve	= 4507, //12星保级材料
	SID_ProtectStarFifteen	= 4508, //15星保级材料

	SID_ProtectMountFour	= 4746, //坐骑保护4级材料
	SID_ProtectMountSeven	= 4747, //坐骑保护7级材料
	SID_ProtectMountTen		= 4748, //坐骑保护10级材料
	SID_MountStrengthen		= 4749, //坐骑强化材料

	SID_TRANSFERSTAR_DROP   = 5081, //转星材料掉星
	SID_TRABSFERSTAR_UNDROP = 5082, //转星材料不掉星

	SID_UnBindItem			= 4745,//装备解绑符

	SID_GemUp_Level_One		= 5420, //一级宝石合成材料
	SID_GemUp_Level_Two		= 5421, //二级宝石合成材料
	SID_GemUp_Level_Three	= 5422, //三级宝石合成材料
	SID_GemUp_Level_Four	= 5423, //四级宝石合成材料

	SID_Identify_Material	= 4781, //装备鉴定材料

	SID_Gem_Material		= 5400, //宝石镶嵌材料
    SID_RandAttr_Material	= 4750, //装备洗随机属性材料

	SID_SuAnimalChangeName	= 4774,//副将改名称

	SID_PetComPose			= 4775,

	SID_UnKnowItem			= 25, //未知道具
};
#endif // __COMMON_GLOBALDEF_H__
