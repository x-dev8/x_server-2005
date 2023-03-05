/********************************************************************
    Filename:     Configure.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __GAMESERVER_CONFIGURE_H__
#define __GAMESERVER_CONFIGURE_H__

#pragma once

#include "GlobalDef.h"
#include "GameDefinePlayer.h"

// ������Ϣ
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
        bool IsRun; // �Ƿ���ҪRun
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
    void       ReLoadSome();     // ��̬���������

    bool       IsMapOpen(int MapId);
    bool       IsMapRun( int MapId );

public:
    char         szGameServerName[64];        // ����������
    DWORD        dwAreaId;                    // ����ID
    DWORD        dwServerID;                  // ������ID
    char         szDBServerIP[64];            // DatabaseServer
    int          iDBServerPort;
	char         szLogServerIp[64];            // LogServer
	int          iLogServerPort;
	bool		 bOpenLogService;
    char         szCenterServerIP[IP_LENGTH]; // CenterServer
    uint16       sCenterServerPort;
    uint16       wListenGateServerPort;
    uint16       wListenGmToolsPort;
    uint16       wListenLoginServerPort; // ��¼�����������˿�
    char         szDBIP[64];             // Sql
    char         szDBUser[64];
    char         szDBPwd[64];
    char         szDBName[64];
    //char         szAccountServerIP[20]; // AccountServer
    //WORD         wAccountServerPort;
    int          m_iBornPointMap[BORN_POINT_COUNT]; // ������
    int          m_iBornPointX[BORN_POINT_COUNT];
    int          m_iBornPointY[BORN_POINT_COUNT];
    int          m_iBornOpen[BORN_POINT_COUNT];
    char         m_szYearName[ 32 ];
    int          m_nYear;   // �� ��Ϸ���翪ʼʱ��
    int          m_nMonth;  // ��
    int          m_nDay;    // ��
    int          m_nHour;   // ʱ
    int          m_nMinute; // ��
    int          m_nGameWorldTimerRate;
    int          m_nGameYear; // ��Ϸ��
    bool         bAntiPluginOpen;
    char         szCreateImgExePath[256];
    char         szTmpImageFolder[256];
    DWORD        dwCheckWhenFightingTime;
    DWORD        dwPlayerApplyTime;
    bool         m_bIsKickCheater;   // ��⵽��ָ���ͻ��˵�½�Ƿ�KICK�����PLAYER
    int          nMaxCheckFailCount; // ���ͼƬ����ʧ�ܴ���    

	bool              bIsOpenAntiAddiction           ; // �Ƿ�򿪷�����    
	bool              bHaveGetAntiAddictionInfoConfig; // �Ƿ��Ѿ���ȡ���򿪷�����ϵͳ�����Ϣ������ϵͳ���õĴ���
	AntiAddictionTime xAntiAddictionInfo             ; // ������ϵͳʱ������
	uint32            nAntiAddictionSaveTime         ; // �����Ա���ʱ��


    int          m_nRefreshHour;
    int          m_nRefreshMin;
    int          m_TellPlayerPerTime;
    int          m_nIntegralPerTime; // �������ӵ�ʱ��
    BOOL         bPKOpen;            // �Ƿ���PK
    int          m_nFirstKill;
    int          m_nSecondKill;
    int          m_nThirdKill;
    int          m_nMoreKill;
    DWORD        m_dwRefreshKillTime;    // ɱͬһ���3������û������ֵ����һ��100%������ֵ���ڶ���60%������ֵ��������20%������ֵ
    int          nMaxDailyPKValue;       // ÿ�������PKֵ
    int          nDulEndHpper;           // �д������ָ���HP%
    //int          protecttime;            // �������ı���ʱ��(s)
    int          nProtectStatusId;       // PK��ԭ�ظ���ı���״̬Id
    int          nProtectStatusLevel;    // PK��ԭ�ظ���ı���״̬Level
    bool         iAllAIOpen;             // �Ƿ������еĹ���AI
    //bool         bMTRefreshMonster;      // �Ƿ����ö��߳�ˢ��
    bool         bAIFindParth;           // �Ƿ�������Ѱ·
    int          iOnlineMax;             // ���ͬʱ����
    int          m_nLevelLimt;           // �ȼ�����
    int          m_nSkillExpLimt;        // ���ܾ�������
    DWORD        m_nMoneyMax;    
    DWORD        m_nMaxJiaoZi;           //�����
    uint32       dwAutoSaveDelay;        // ��ѯ�ռ���Ҫ���ɫ���ݵ�UpdateƵ��    
    bool         bOnlySaveToDBOnExit;
    int          m_nCreatBagSize;
    int          m_nCreateMaterialSize;
    int          m_nStorageItemGrid;     //
    int          m_nStorageMountGrid;    // 
    int          m_nLockItemLimt;        // ����������
    float        m_SitdownRestorePer;    // ���»ظ��ٶȼӿ�%
    uint32       nCharHPRestoreCheck;    // ��Ѫ�ٶ�
    uint32       nCharMPCheckTime[EArmType_MaxSize];    // ��MP�ٶ�
    uint32       nCharXPRestoreCheck;    // ��XP�ٶ�
    int          m_nIntegralMaxByItem;   // ��Ʒ���ӵĻ�������
    int          m_nTimeInAfk;           // ��������ʱ��
    bool         bHighShoutTimeLimit;    // ������ʱ������
    int          nHighShoutPerTime;      // �ߺ�ʱ��
    int          nHighShoutLevelLimit;   // �ߺ��ȼ�
    int          nHighShoutCostMoney;
    bool         bMTStageProcess;        // �Ƿ����ö��̴߳����ͼ�߼�
    int          m_nGlodCovSilver;
    int          iMonsterNumber;         // ���������趨
    bool         bKickPlayerByCredit;    // �Ƿ������
    int          m_nReliveOriginAllHpMp;
    int          m_nReliveOriginNon;     // ������Ҫ��RMB
    int          m_nReqairRmb;           // Զ�������RMB
    DWORD        dwMapThreadSleep;    
    bool         bDisableChatofWorld;    // �������º��� 
    int          m_nLockIntensifySilver; // ����ǿ������Ʊ
    int          m_nOffSetInShopCenter;  // �̳��ۿ�
    bool         bIsChangedShopCenterOff;
    float        m_fGlobalDropRate;

    int16        nWeaponDropHp;          // �������;ö�
    int16        nArmourDropHp;          // ���ߵ��;ö�
    int16        nDeathEquipDropHpMin;   // �������;ðٷֱ�
    int16        nDeathEquipDropHpMax;   // �������;ðٷֱ�

    int32        nEquipTopStarExp;       // װ����10�ǽ�������

    char         szGMPassword[128];
    float        fTaskGoldMultiplicator;       // �������ʱ��ȡ����ľ��齱���;��齱������
    float        fTaskExperienceMultiplicator;
    int          nTaskGetMultiplicatorPercent; // �������ʱ��ȡ����ľ��齱���;��齱�������Ļ��ʰٷֱ�
    int          logintype;
    char         gamenum[MAX_PATH];
    std::string  strLogConfigFilePath;
    bool         bIsOpenCommand;            // �Ƿ���GM����
    bool         bIsOpenRobotCmd;           // �Ƿ�������������
    int          m_nPKProtectLevel;         // PK �����ȼ�
    int          m_nPrivateShopLevel;       // ��̯���Ƶȼ�    
    int          beRelivePkValue;           // ���Ա������Pkֵ
    bool         m_bSleepTime;
    float        m_fMinModelPercent;
    float        m_fMaxModelPercent;
    uint16       exchangeJindingLevelLimit; // �һ��𶧵ĵȼ�����
    uint32       graphicValidFailBlockTime; // ��֤����֤ʧ��blockʱ��
    uint32       onMapLimitTime;            //
    bool         isTakeMoneyCorrect;        // �Ƿ����Я����Ǯ

    uint32       antiAddictionTime[2];      // 3���׶ε�����ʱ��ָ��
    bool         isSendChatToCenter;        // �Ƿ�������Ϣ��CenterServer
    uint16       ustPrivateChatLevel;       // ��С����ȼ�

    uint16       maintainCrossLevel;        // �缶��ֵ��󼶱���
    uint32       minuteOfflineHookMoney;    // ���߹һ�ÿ������Ҫ��Ǯ

    bool         bOpenAchievement;          // �Ƿ����ɾ�ϵͳ
    bool         bOpenOnlineReward;         // �Ƿ������߽���

    uint8        itemDropDelaySecond;       // ��������ӳ���ʾ
    uint32       petBreedIntervalTime;      // ���ﷱֳʱ�� ��λ ����
    uint32       petBreedFailedTime ;       // ���ﷱֳʧ��ʱ�� ��λ ����

	bool		 isOpenPetAttacter;
	bool		 isOpenSubPetAtter;

    OpenMaps     OpenMaps_;

	int			 nOnBiaoCheBuffId;			// ���ڳ���ӵ�Buff ID
	int			 nOnBiaoCheBuffLevel;		// Buff Level

	int          nChannelStatusId;       // ���߱���״̬Id
	int          nChannelStatusLevel;    // ���߱���״̬Level


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

	float		nDropExp;		//��ɱ�����侭��ٷֱ�
	int			nDropHonour;	//��ɱ����������

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

// ȫ�������ļ���Ϣ
extern Configure g_Cfg;

#endif // __GAMESERVER_CONFIGURE_H__
