#pragma once
#include <windows.h>
#include <vector>
#include <string>
#include <map>
#include "GlobalDef.h"
#include "RapidXml/MeRapidXml.h"

#define MAX_FONTCOUNT	3

#define AREA_COUNT 10
#define MaxStringSize 1024
#define XML_GLOBALCONFIG_FILENAME "..\\Data\\ClientConfig\\GameSetting.config"
#define XML_GLOBALCONFIG_ROOT_NAME "Project"


struct AreaInfo
{
	std::string strName;
	std::string gid;
	std::string areaid;
};

struct CreateRoleSetting
{
    int    nProfession;
    int    nFaceModelId;

    int    nWeaponModelId;
    int    nArmourModelId;
    int    nGloveModelId;
    int    nHeadModelId;
    int    nShoeModelId;
    /*int    nShoulderModelId;*/
    int    nSashModelId;
    /*int    nTrousersModelId;*/

    int    nWeaponItemId;
    int    nArmourItemId;
    int    nGloveItemId;
    int    nHeadItemId;
    int    nShoeItemId;
    /*int    nShoulderItemId;*/
    int    nSashItemId;
    /*int    nTrousersItemId;*/
    char   szEffectName[MAX_PATH];
};

struct ProduceSkillInfo
{
    int     iSkillId;
    char    szSkillName[17];
    int     iLearnSkillNPCId;
    int     SkillPointLimit[9];        // 目前只有9级
};

struct NpcHeadModel
{
	float fStature;
	float fX;
	float fY;
	float fWidth;
	float fHeight;
	float fViewHigh;  //视野高度
	float fScale;     //缩放
	NpcHeadModel()
	{
		fStature = 0.0;
		fX = 0.0f;
		fY = 0.0f;
		fWidth = 0.0f;
		fHeight = 0.0f;
		fViewHigh = 0.0f;
		fScale = 0.06f;
	}
};

/*
 * 2012.6.30 wangshuai
 * 对应GameSetting.config文件
 */
class CCfg
{
public:

	//目标连接地址，端口
	char	m_szDstIP[ 200 ];
	int		m_iLoginDstPort;
	int		m_iServerPort;
	std::string m_strHttp;
	int		m_nLanguage;			//------- 语言    (   at 2003/12/5)

	BOOL	m_bFullScreen;
// 	char	m_szLoginPageMusic[MAX_PATH];
// 	char	m_szSelectPageMusic[MAX_PATH];

	//锁定被动目标时的特效路径
	char	m_szLockPassivityTargetEffectPath[MAX_PATH];
	//锁定主动目标时的特效路径
	char	m_szLockInitiativeTargetEffectPath[MAX_PATH];

	// 起跳，落地跑，落地的动作播放时间
	DWORD	m_dwJumpPlayTimeMale;
	DWORD	m_dwJumpPlayTimeFemale;

	DWORD	m_dwFallToTheGroundRunPlayTimeMale;
	DWORD	m_dwFallToTheGroundRunPlayTimeFemale;

	DWORD	m_dwDropPlayTimeMale;
	DWORD	m_dwDropPlayTimeFemale;

	// 起跳系数
	float	m_fJumpUpValueMale;
	float	m_fJumpUpValueFemale;

	// 下落系数
	float	m_fDropValueMale;
	float	m_fDropValueFemale;

	// 起跳过渡时间
	DWORD	m_dwJumpBlendingTimeMale;
	DWORD	m_dwJumpBlendingTimeFemale;

	// 暴击特效
	//char	m_szRoleCriticalEffect[MAX_PATH];
	char	m_szSpearCriticalEffectSelf[MAX_PATH];
	char	m_szStaffCriticalEffectSelf[MAX_PATH];
	char	m_szFanCriticalEffectSelf[MAX_PATH];
    char	m_szSwordCriticalEffectSelf[MAX_PATH];
	char	m_szBowCriticalEffectSelf[MAX_PATH];

	char	m_szSpearCriticalEffectTarget[MAX_PATH];
	char	m_szStaffCriticalEffectTarget[MAX_PATH];
	char	m_szFanCriticalEffectTarget[MAX_PATH];
	char	m_szSwordCriticalEffectTarget[MAX_PATH];
	char	m_szBowCriticalEffectTarget[MAX_PATH];
	//背击特效
	//char	m_szRoleBackStrikeEffect[MAX_PATH];
	char	m_szSpearBackStrikeEffectSelf[MAX_PATH];
	char	m_szStaffBackStrikeEffectSelf[MAX_PATH];
	char	m_szFanBackStrikeEffectSelf[MAX_PATH];
    char	m_szSwordBackStrikeEffectSelf[MAX_PATH];
	char	m_szBowBackStrikeEffectSelf[MAX_PATH];

	char	m_szSpearBackStrikeEffectTarget[MAX_PATH];
	char	m_szStaffBackStrikeEffectTarget[MAX_PATH];
	char	m_szFanBackStrikeEffectTarget[MAX_PATH];
	char	m_szSwordBackStrikeEffectTarget[MAX_PATH];
	char	m_szBowBackStrikeEffectTarget[MAX_PATH];
	//致命攻击特效
	//char	m_szRoleDeadlyEffect[MAX_PATH];
	char	m_szSpearDeadlyEffectSelf[MAX_PATH];
	char	m_szStaffDeadlyEffectSelf[MAX_PATH];
	char	m_szFanDeadlyEffectSelf[MAX_PATH];
    char	m_szSwordDeadlyEffectSelf[MAX_PATH];
	char	m_szBowDeadlyEffectSelf[MAX_PATH];

	char	m_szSpearDeadlyEffectTarget[MAX_PATH];
	char	m_szStaffDeadlyEffectTarget[MAX_PATH];
	char	m_szFanDeadlyEffectTarget[MAX_PATH];
	char	m_szSwordDeadlyEffectTarget[MAX_PATH];
	char	m_szBowDeadlyEffectTarget[MAX_PATH];

	//完成任务特效
	char	m_szDoneQuestEffect[MAX_PATH];

	//技能升级特效
	char	m_szSkillLevelUpEffect[MAX_PATH];

	float	m_fPathDirectionMaxStep;
	float	m_fPathDirectionMinStep;

	//单机版
	bool	m_bLocalVersion;
	unsigned short m_nLocalRoleProfession;
	unsigned short m_nLocalRoleSex;	

	int		m_nSimpleMapLoadDistance;
	int		m_nSimpleMapLoadDistanceFly;
	//
	char	m_szFontFile[MAX_FONTCOUNT][256];
	char	m_szNameFontName[256];
	int		m_nNameFontSize;
	char	m_szDefaultFont[256];
	int		m_nDefaultFontSize;
	//
	BOOL	m_bUseSigleModel;
	BOOL	m_bUseSkinMeshShader;

	DWORD	m_dwMultiSample;
	BOOL	m_bFastLoadMex;

	FLOAT	m_fFlyRunStep;

	int			m_nCriticalAttackCameraShakeType;			//暴击摄象机的振动类型
	float		m_fCriticalAttackMaxShakeRange;				//暴击最大振幅
	float		m_fCriticalAttackMinShakeRange;				//暴击最小振幅
	DWORD		m_dwCriticalAttackShakeKeepTime;			//暴击震动维持时间

	int		m_nUITextHeight;

//add the length of Homepage 
    char m_szHomePage[MaxStringSize];
	char m_szHomePage2[MaxStringSize];
	char m_szHomePage3[MaxStringSize];
	char m_szHomePagePrefix[MaxStringSize]; //快速注册

	//resource check
	bool m_bIsOpenResourceCkeck;

	//anti-charater

	DWORD m_dwAntiTime;
	int m_nAntiProcessNum;
	std::vector<std::string>m_strProcessName;

	// 启动UI浏览器
    bool m_bUiViewer;

    float m_fNameShowDistance;  // 人物字体显示距离
    float m_fNameFontScale;     // 人物字体缩放
    float m_fNameFontOffset;    // 人物字体离BBOX最大顶点的偏移量
	DWORD m_dwNameFontFrameColor;  // 人物字体边框的颜色
	float m_fUIFontScale;		// ui字体缩放

	float m_fModelShowDistance;	// 模型显示距离
	float m_fDoodadShowDistance;// 植被显示距离

	bool m_isNameFontBold;		// 人物字体是否粗体

    unsigned char m_ucPKLevelLimit; // PK保护等级限制
    unsigned char m_ucPrivateShopLevelLimit;   // 摆摊等级限制

    // 选兵器的设定
	struct RoleSetting
	{
		std::string m_strName;
        std::vector<CreateRoleSetting>  m_vCreateSetting;
		RoleSetting()
		{
			m_strName.clear();
			m_vCreateSetting.clear();
		}

		void Clear()
		{
			m_strName.clear();
			m_vCreateSetting.clear();
		}

		int GetSpaceSize(){return m_vCreateSetting.size();}
	};

	std::vector<RoleSetting> m_MaleRoleSetting;
	std::vector<RoleSetting> m_FemaleRoleSetting;

    char                            m_pszCreatePlayAnim[64];

    char m_pszSelectSceneName[33];
    std::vector<std::string> m_strSelectSceneModelNotUpdate; // 选人场景Update时不需要更新的模型
	float m_fSelectRoleManScale;		//选人界面人物缩放
	float m_fSelectRoleWomenScale;      //选人界面女性缩放
	float m_fCreateRoleManScale;		//创建界面人物缩放
	float m_fCreateRoleWomenScale;      //创建界面女性缩放		 
	float m_fSelectRoleRotateZ;		// 选人界面人物朝向

	//Help
	char						m_szHelpPagePath[MAX_PATH];
	int							m_nHelpPageWidth;
	int							m_nHelpPageHeight;

    std::vector<ProduceSkillInfo> m_vProduceSkillInfo;      // 生活技能
    ProduceSkillInfo* GetProduceSkillInfo(int iSkillId);

    //财产保护设置
    std::vector<std::string> m_vctStrProtectSetting;
    short                    m_shProtectTimeAtLeast;     // 最小财产保护时间

    //Ping设置显示
    int     m_PingGoodMin;      // 好
    DWORD   m_PingGoodColor;
    int     m_PingNormalMin;    // 中
    DWORD   m_PingNormalColor;
    int     m_PingBadMin;       // 差
    DWORD   m_PingBadColor;

    //隐藏武器动作列表
    std::vector<std::string>    m_vectorHideWeaponAnims;

    //创建人物身高限制
    float   m_fPlayerScaleMin;
    float   m_fPlayerScaleMax;

    //商城物品名称颜色
    bool    m_bShopCenterUseQualityColor;

    //能否创建人物
    bool    m_bCanCreatePlayer;

	//商城充值网址
	std::string m_strPayWebAddress;

	//Tab人物裁剪Frustom相关参数
	float	m_fTabFrutomFov;
	float	m_fTabFrutomFarDist;
	float	m_fTabFrutomNearDist;
	float	m_fTabFrutomToEyeDist;
	float	m_fTabBackRadius;

	//亲密度特效
	bool	m_bPlayFriendPointEffect;
	std::string m_strFriendPointEffect;
	bool	m_bPlayFriendUpgradeEffect;
	std::string m_strFriendUpgradeEffect;

	//镜像地图列表
	struct SMirrorType 
	{
		int				m_PrimaryMapId;
		std::vector<int> m_vectorMirrorMapIds;
	};
	std::vector<SMirrorType>    m_vectorMirrorType;

	std::map<int, int>				m_vectorCountryMap;
	// 摇奖箱子名称
	std::map<unsigned short, std::string>	m_mapLotteryBox;	//box item id和Name

	float m_fMountScales[EArmType_MaxSize];

	struct SGivePresent
	{
		int			iItemId;
		char		szEffect[256];
	};
	std::vector<SGivePresent>	m_vectorGivePresents;

	// LoadMap背景个数
	short	m_shLoadMapNum;
	float	m_fLoadMapProbability;	// 需要增加概率显示的背景，概率
	std::vector<short>	m_vecProbabilityLoadMaps;	// 需要增加概率显示的背景

	RECT m_rcFreeTipCloseRect;		// FreeTip上大叉位置
	std::string m_strFreeTipCloseBtn;// 图素路径

	int		m_nLoginMapId;
	int		m_nSelectPlayerMapId;
	int		m_nCreateMapId;
	int     m_nFirstMapId;

	//说话泡泡配置
	RECT		m_ChatPaoPaoRect;
	RECT		m_ChatPaoPaoInnerRect;
	std::string m_strChatPaoPaoTexture;// 图素路径

	//摆摊配置
	RECT        m_RealRect;
	RECT        m_PrivateRect;
	RECT        m_PrivateInnerRect;
	std::string m_strPrivateTexture;


	int		m_nXiaoLaBaItemId;

	std::string  m_strMapPath;
	RECT         m_BgSrc;

	int		m_nMinSoulPlayerLevel;
	int		m_nMinSoulItemLevel;
	int		m_nMinOpenLightPlayerLevel;
	int		m_nMinOpenLightItemLevel;
	int		m_nMinHoleLevel;
	int		m_nMinEquipCopyPlayerLevel;
	int		m_nMinEquipCopyItemLevel;
	int		m_nMaxEquipCopyItemCrossLevel;
	DWORD	m_dwAutoStarLevelUpInterval;

	int		m_nSoulPicWidth;
	int		m_nSoulPicHeight;

	int		m_nAchievementFinishHoldTime;
	int		m_nAnimationDelayTime;
	std::string	m_strAchieveSoundPath;

	/*
	 * 2012.6.30 wangshuai
	 * 上线奖励 注释
	 */
	std::string m_strOnlineRewardFile;		// 序列帧文件路径
	int		m_nOnlineRewardItemWidth;		// 宽度
	int		m_nOnlineRewardItemHeight;		// 高度
	int		m_nOnlineRewardRow;				// 行数
	int		m_nOnlineRewardColumn;			// 列数
	int		m_nOnlineRewardTime;			// 每帧间隔
	int		m_nOnlineRewardCount;			// 总帧数

	//小喇叭
	struct HornSetting
	{
		HornSetting() : 
			m_nEffectShowTime(0), 
			m_nHornShowTime(0) 
		{}
		int		m_nEffectShowTime;
		int		m_nHornShowTime;
	};
	HornSetting m_HornSetting;

	//按钮闪烁
	struct ButtonSparkSetting
	{
		ButtonSparkSetting() : 
		m_nFamePerTime(0), 
		m_nStartX(0),
		m_nStartY(0),
		m_nGapX(0),
		m_nGapY(0),
		m_nPicWidth(0), 
		m_nPicLength(0), 
		m_nRow(0), 
		m_nColumn(0),
		m_nCount(0)
	{
	}
	std::string m_strPicPath; 
	int		m_nFamePerTime;
	int		m_nStartX;
	int		m_nStartY;
	int		m_nGapX;
	int		m_nGapY;
	int		m_nPicWidth;
	int		m_nPicLength;
	int		m_nRow;
	int		m_nColumn;
	int		m_nCount;
	};
	ButtonSparkSetting m_xGuildCampButton;
	// player actions when singing
	struct PlayerNPCActions
	{
		int		m_nId;			// npc id
		char	m_acSingName[MAX_PATH]; // 吟唱动作名
		PlayerNPCActions() : m_nId(-1)
		{
			memset( m_acSingName, 0, sizeof( m_acSingName ) );
		}
	};
	std::map< int, PlayerNPCActions > m_PlayerNpcActions;
	
	// 主角跑步动画时间长度，毫秒
	int		m_nRoleRunLoopTime;

	std::string m_strReliveEffect;  //复活特效
	std::string m_strReliveAnim;    //复活动作
	std::string m_strImmunity;      //折光特效

	std::string m_strNpcShowEffect; //Npc显示特效
	std::string m_strNpcShowAnim;   //Npc显示动作

	std::string m_strNpcHideEffect; //Npc隐藏特效
	std::string m_strNpcHideAnim;   //Npc隐藏动作

	//图鉴特效
	std::string m_SuAnimalCardEffect;
	int  m_nFriendLevel;

	std::string m_strRanklistWebPath;	//排行榜的web下载地址
	int	m_nflashWidth;
	int	m_nflashHeight;
	int	m_noffsizeX;
	int	m_noffsizeY;

	std::string DumpFtpUser;
	std::string DumpFtpPwd;
	std::string DumpFtpUrl;
	bool bUploadDump;

	std::string m_strExitPage;
	bool        m_bOpenExitPage;
	RECT      m_TargetTipsOffset;

	std::vector< int > m_vecChannelMapId;

	std::string	m_FirstWedAdd;
private:
	BOOL	InstallFont( const char* szFile );	
	void		GetChildElementFloat( MeXmlElement* pElement, const char* pszName, float& fValue );
	void     	GetChildElementInt( MeXmlElement* pElement, const char* pszName, int& nValue );
	void     	GetChildElementInt( MeXmlElement* pElement, const char* pszName, DWORD& dwValue );
	bool		GetChildElementString( MeXmlElement* pElement, const char* pszName, std::string& strValue );

public:
	CCfg(void);
	~CCfg(void);

	void InitializeConfig();

	void FillTileIdCountryMap();
	static AreaInfo Areas[AREA_COUNT];
	BOOL        IsMirrorMapIds(int nMapId);
	int			GetPrimaryMapId(int MapId);
	int			GetMyCountryMapId(int MapId,int nCountry);

public:
	bool		IsCountryMapInWorldMap(int MapId);
	NpcHeadModel* GetHeadModelByHeight(float fHeight);
private:
	std::vector<int>			m_CountryMapInWorldMap;
	std::map<float,NpcHeadModel> m_NpcHeadModel;
private:
	bool		m_IsOpenPetAtter;
public:
	bool		GetIsOpenPetAtter(){return m_IsOpenPetAtter;}
};

extern CCfg gCfg;