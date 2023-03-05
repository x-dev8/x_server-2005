/********************************************************************
    Filename:     Configure.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __GAMESERVER_CONFIGURE_H__
#define __GAMESERVER_CONFIGURE_H__

#pragma once

#include "GlobalDef.h"
#include "GameDefinePlayer.h"

// 配置信息
class Configure
{
public:
    
    struct SOpenMap
    {
        SOpenMap()
        {
            MapId  = -1;
            IsRun  = true;
        }

        int  MapId;
        bool IsRun; // 是否需要Run
        bool operator == (const int mapid )
        { return MapId == mapid; }
    };

    typedef std::vector<SOpenMap> OpenMaps;

public:
    Configure();

    void       Save();
         
    bool       InitCommonData  ( const char* GamesettingPath   );
    bool       InitPrivateData ( const char* szGamesettingPath );
    bool       InitNetSetting();
    void       ReLoadSome();     // 动态读入的配置

    bool       IsMapOpen(int MapId);
    bool       IsMapRun( int MapId );

public:
    char         szGameServerName[64];        // 服务器名字
    DWORD        dwAreaId;                    // 区域ID
    DWORD        dwServerID;                  // 服务器ID
    char         szDBServerIP[64];            // DatabaseServer
    int          iDBServerPort;
	char         szLogServerIp[64];            // LogServer
	int          iLogServerPort;
	bool		 bOpenLogService;
    char         szCenterServerIP[IP_LENGTH]; // CenterServer
    uint16       sCenterServerPort;
    uint16       wListenGateServerPort;
    uint16       wListenGmToolsPort;
    uint16       wListenLoginServerPort; // 登录服务器监听端口
    char         szDBIP[64];             // Sql
    char         szDBUser[64];
    char         szDBPwd[64];
    char         szDBName[64];
    //char         szAccountServerIP[20]; // AccountServer
    //WORD         wAccountServerPort;
    int          m_iBornPointMap[BORN_POINT_COUNT]; // 出生点
    int          m_iBornPointX[BORN_POINT_COUNT];
    int          m_iBornPointY[BORN_POINT_COUNT];
    int          m_iBornOpen[BORN_POINT_COUNT];
    char         m_szYearName[ 32 ];
    int          m_nYear;   // 年 游戏世界开始时间
    int          m_nMonth;  // 月
    int          m_nDay;    // 日
    int          m_nHour;   // 时
    int          m_nMinute; // 分
    int          m_nGameWorldTimerRate;
    int          m_nGameYear; // 游戏年
    bool         bAntiPluginOpen;
    char         szCreateImgExePath[256];
    char         szTmpImageFolder[256];
    DWORD        dwCheckWhenFightingTime;
    DWORD        dwPlayerApplyTime;
    bool         m_bIsKickCheater;   // 检测到非指定客户端登陆是否KICK掉这个PLAYER
    int          nMaxCheckFailCount; // 最大图片码检测失败次数    

	bool              bIsOpenAntiAddiction           ; // 是否打开防沉迷    
	bool              bHaveGetAntiAddictionInfoConfig; // 是否已经获取到打开防沉迷系统与否信息防沉迷系统配置的代码
	AntiAddictionTime xAntiAddictionInfo             ; // 防沉迷系统时间设置
	uint32            nAntiAddictionSaveTime         ; // 防沉迷保存时间


    int          m_nRefreshHour;
    int          m_nRefreshMin;
    int          m_TellPlayerPerTime;
    int          m_nIntegralPerTime; // 积分增加的时间
    BOOL         bPKOpen;            // 是否开启PK
    int          m_nFirstKill;
    int          m_nSecondKill;
    int          m_nThirdKill;
    int          m_nMoreKill;
    DWORD        m_dwRefreshKillTime;    // 杀同一玩家3次以上没有荣誉值，第一次100%的荣誉值，第二次60%的荣誉值，第三次20%的荣誉值
    int          nMaxDailyPKValue;       // 每天获得最大PK值
    int          nDulEndHpper;           // 切磋结束后恢复的HP%
    //int          protecttime;            // 决斗完后的保护时间(s)
    int          nProtectStatusId;       // PK和原地复活的保护状态Id
    int          nProtectStatusLevel;    // PK和原地复活的保护状态Level
    bool         iAllAIOpen;             // 是否开启所有的怪物AI
    //bool         bMTRefreshMonster;      // 是否启用多线程刷怪
    bool         bAIFindParth;           // 是否开启怪物寻路
    int          iOnlineMax;             // 最多同时在线
    int          m_nLevelLimt;           // 等级上限
    int          m_nSkillExpLimt;        // 技能经验上限
    DWORD        m_nMoneyMax;    
    DWORD        m_nMaxJiaoZi;           //最大交子
    uint32       dwAutoSaveDelay;        // 轮询收集需要存角色数据的Update频率    
    bool         bOnlySaveToDBOnExit;
    int          m_nCreatBagSize;
    int          m_nCreateMaterialSize;
    int          m_nStorageItemGrid;     //
    int          m_nStorageMountGrid;    // 
    int          m_nLockItemLimt;        // 加锁的上限
    float        m_SitdownRestorePer;    // 坐下回复速度加快%
    uint32       nCharHPRestoreCheck;    // 回血速度
    uint32       nCharMPCheckTime[EArmType_MaxSize];    // 回MP速度
    uint32       nCharXPRestoreCheck;    // 回XP速度
    int          m_nIntegralMaxByItem;   // 物品增加的积分上限
    int          m_nTimeInAfk;           // 进入暂离时间
    bool         bHighShoutTimeLimit;    // 喊话的时间限制
    int          nHighShoutPerTime;      // 高喊时间
    int          nHighShoutLevelLimit;   // 高喊等级
    int          nHighShoutCostMoney;
    bool         bMTStageProcess;        // 是否启用多线程处理地图逻辑
    int          m_nGlodCovSilver;
    int          iMonsterNumber;         // 怪物总数设定
    bool         bKickPlayerByCredit;    // 是否打开踢人
    int          m_nReliveOriginAllHpMp;
    int          m_nReliveOriginNon;     // 复活需要的RMB
    int          m_nReqairRmb;           // 远程修理的RMB
    DWORD        dwMapThreadSleep;    
    bool         bDisableChatofWorld;    // 禁用天下喊话 
    int          m_nLockIntensifySilver; // 锁定强化的银票
    int          m_nOffSetInShopCenter;  // 商城折扣
    bool         bIsChangedShopCenterOff;
    float        m_fGlobalDropRate;

    int16        nWeaponDropHp;          // 武器掉耐久度
    int16        nArmourDropHp;          // 防具掉耐久度
    int16        nDeathEquipDropHpMin;   // 死亡掉耐久百分比
    int16        nDeathEquipDropHpMax;   // 死亡掉耐久百分比

    int32        nEquipTopStarExp;       // 装备升10星奖励经验

    char         szGMPassword[128];
    float        fTaskGoldMultiplicator;       // 完成任务时获取额外的经验奖励和经验奖励倍数
    float        fTaskExperienceMultiplicator;
    int          nTaskGetMultiplicatorPercent; // 完成任务时获取额外的经验奖励和经验奖励倍数的机率百分比
    int          logintype;
    char         gamenum[MAX_PATH];
    std::string  strLogConfigFilePath;
    bool         bIsOpenCommand;            // 是否开启GM命令
    bool         bIsOpenRobotCmd;           // 是否开启机器人命令
    int          m_nPKProtectLevel;         // PK 保护等级
    int          m_nPrivateShopLevel;       // 摆摊限制等级    
    int          beRelivePkValue;           // 可以被复活的Pk值
    bool         m_bSleepTime;
    float        m_fMinModelPercent;
    float        m_fMaxModelPercent;
    uint16       exchangeJindingLevelLimit; // 兑换金锭的等级限制
    uint32       graphicValidFailBlockTime; // 验证码验证失败block时间
    uint32       onMapLimitTime;            //
    bool         isTakeMoneyCorrect;        // 是否纠正携带金钱

    uint32       antiAddictionTime[2];      // 3个阶段的两个时间分割点
    bool         isSendChatToCenter;        // 是否发聊天消息到CenterServer
    uint16       ustPrivateChatLevel;       // 最小聊天等级

    uint16       maintainCrossLevel;        // 跨级保值最大级别差距
    uint32       minuteOfflineHookMoney;    // 离线挂机每分钟需要金钱

    bool         bOpenAchievement;          // 是否开启成就系统
    bool         bOpenOnlineReward;         // 是否开启在线奖励

    uint8        itemDropDelaySecond;       // 掉落包裹延迟显示
    uint32       petBreedIntervalTime;      // 宠物繁殖时间 单位 分钟
    uint32       petBreedFailedTime ;       // 宠物繁殖失败时间 单位 分钟

	bool		 isOpenPetAttacter;
	bool		 isOpenSubPetAtter;

    OpenMaps     OpenMaps_;

	int			 nOnBiaoCheBuffId;			// 上镖车添加的Buff ID
	int			 nOnBiaoCheBuffLevel;		// Buff Level

	int          nChannelStatusId;       // 切线保护状态Id
	int          nChannelStatusLevel;    // 切线保护状态Level


	int			KillPlayerHonour;
	int			CountryKillPlayerHonour;
	int			LevelLimit;
	int			TeamHonourDis;
	int			MaxHonour;
	int			AllMaxHonour;
	int			OncePlayerKillSum;
	int			KillPlayerMission;
	int			TeamDelHonour;
	int			TeamOtherPlayerHonour;

	int			MaxPetDuration;
	int			InitPetDuration;

	float		nDropExp;		//被杀死掉落经验百分比
	int			nDropHonour;	//被杀死掉落荣誉

	int			MaxMissionSum;

	bool		IsOpenCSAuth;

	unsigned int CountryWeakBuffID;
	unsigned int CountryWeakBuffLevel;

	unsigned int CountryStrongBuffID;
	unsigned int CountryStrongBuffLevel;

	unsigned int CountryBalancedBuffID;
	unsigned int CountryBalancedBuffLevel;

	unsigned int MaxLeaveExpHour;
};

// 全局配置文件信息
extern Configure g_Cfg;

#endif // __GAMESERVER_CONFIGURE_H__
