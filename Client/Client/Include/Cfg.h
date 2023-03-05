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
    int     SkillPointLimit[9];        // Ŀǰֻ��9��
};

struct NpcHeadModel
{
	float fStature;
	float fX;
	float fY;
	float fWidth;
	float fHeight;
	float fViewHigh;  //��Ұ�߶�
	float fScale;     //����
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
 * ��ӦGameSetting.config�ļ�
 */
class CCfg
{
public:

	//Ŀ�����ӵ�ַ���˿�
	char	m_szDstIP[ 200 ];
	int		m_iLoginDstPort;
	int		m_iServerPort;
	std::string m_strHttp;
	int		m_nLanguage;			//------- ����    (   at 2003/12/5)

	BOOL	m_bFullScreen;
// 	char	m_szLoginPageMusic[MAX_PATH];
// 	char	m_szSelectPageMusic[MAX_PATH];

	//��������Ŀ��ʱ����Ч·��
	char	m_szLockPassivityTargetEffectPath[MAX_PATH];
	//��������Ŀ��ʱ����Ч·��
	char	m_szLockInitiativeTargetEffectPath[MAX_PATH];

	// ����������ܣ���صĶ�������ʱ��
	DWORD	m_dwJumpPlayTimeMale;
	DWORD	m_dwJumpPlayTimeFemale;

	DWORD	m_dwFallToTheGroundRunPlayTimeMale;
	DWORD	m_dwFallToTheGroundRunPlayTimeFemale;

	DWORD	m_dwDropPlayTimeMale;
	DWORD	m_dwDropPlayTimeFemale;

	// ����ϵ��
	float	m_fJumpUpValueMale;
	float	m_fJumpUpValueFemale;

	// ����ϵ��
	float	m_fDropValueMale;
	float	m_fDropValueFemale;

	// ��������ʱ��
	DWORD	m_dwJumpBlendingTimeMale;
	DWORD	m_dwJumpBlendingTimeFemale;

	// ������Ч
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
	//������Ч
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
	//����������Ч
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

	//���������Ч
	char	m_szDoneQuestEffect[MAX_PATH];

	//����������Ч
	char	m_szSkillLevelUpEffect[MAX_PATH];

	float	m_fPathDirectionMaxStep;
	float	m_fPathDirectionMinStep;

	//������
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

	int			m_nCriticalAttackCameraShakeType;			//�����������������
	float		m_fCriticalAttackMaxShakeRange;				//����������
	float		m_fCriticalAttackMinShakeRange;				//������С���
	DWORD		m_dwCriticalAttackShakeKeepTime;			//������ά��ʱ��

	int		m_nUITextHeight;

//add the length of Homepage 
    char m_szHomePage[MaxStringSize];
	char m_szHomePage2[MaxStringSize];
	char m_szHomePage3[MaxStringSize];
	char m_szHomePagePrefix[MaxStringSize]; //����ע��

	//resource check
	bool m_bIsOpenResourceCkeck;

	//anti-charater

	DWORD m_dwAntiTime;
	int m_nAntiProcessNum;
	std::vector<std::string>m_strProcessName;

	// ����UI�����
    bool m_bUiViewer;

    float m_fNameShowDistance;  // ����������ʾ����
    float m_fNameFontScale;     // ������������
    float m_fNameFontOffset;    // ����������BBOX��󶥵��ƫ����
	DWORD m_dwNameFontFrameColor;  // ��������߿����ɫ
	float m_fUIFontScale;		// ui��������

	float m_fModelShowDistance;	// ģ����ʾ����
	float m_fDoodadShowDistance;// ֲ����ʾ����

	bool m_isNameFontBold;		// ���������Ƿ����

    unsigned char m_ucPKLevelLimit; // PK�����ȼ�����
    unsigned char m_ucPrivateShopLevelLimit;   // ��̯�ȼ�����

    // ѡ�������趨
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
    std::vector<std::string> m_strSelectSceneModelNotUpdate; // ѡ�˳���Updateʱ����Ҫ���µ�ģ��
	float m_fSelectRoleManScale;		//ѡ�˽�����������
	float m_fSelectRoleWomenScale;      //ѡ�˽���Ů������
	float m_fCreateRoleManScale;		//����������������
	float m_fCreateRoleWomenScale;      //��������Ů������		 
	float m_fSelectRoleRotateZ;		// ѡ�˽������ﳯ��

	//Help
	char						m_szHelpPagePath[MAX_PATH];
	int							m_nHelpPageWidth;
	int							m_nHelpPageHeight;

    std::vector<ProduceSkillInfo> m_vProduceSkillInfo;      // �����
    ProduceSkillInfo* GetProduceSkillInfo(int iSkillId);

    //�Ʋ���������
    std::vector<std::string> m_vctStrProtectSetting;
    short                    m_shProtectTimeAtLeast;     // ��С�Ʋ�����ʱ��

    //Ping������ʾ
    int     m_PingGoodMin;      // ��
    DWORD   m_PingGoodColor;
    int     m_PingNormalMin;    // ��
    DWORD   m_PingNormalColor;
    int     m_PingBadMin;       // ��
    DWORD   m_PingBadColor;

    //�������������б�
    std::vector<std::string>    m_vectorHideWeaponAnims;

    //���������������
    float   m_fPlayerScaleMin;
    float   m_fPlayerScaleMax;

    //�̳���Ʒ������ɫ
    bool    m_bShopCenterUseQualityColor;

    //�ܷ񴴽�����
    bool    m_bCanCreatePlayer;

	//�̳ǳ�ֵ��ַ
	std::string m_strPayWebAddress;

	//Tab����ü�Frustom��ز���
	float	m_fTabFrutomFov;
	float	m_fTabFrutomFarDist;
	float	m_fTabFrutomNearDist;
	float	m_fTabFrutomToEyeDist;
	float	m_fTabBackRadius;

	//���ܶ���Ч
	bool	m_bPlayFriendPointEffect;
	std::string m_strFriendPointEffect;
	bool	m_bPlayFriendUpgradeEffect;
	std::string m_strFriendUpgradeEffect;

	//�����ͼ�б�
	struct SMirrorType 
	{
		int				m_PrimaryMapId;
		std::vector<int> m_vectorMirrorMapIds;
	};
	std::vector<SMirrorType>    m_vectorMirrorType;

	std::map<int, int>				m_vectorCountryMap;
	// ҡ����������
	std::map<unsigned short, std::string>	m_mapLotteryBox;	//box item id��Name

	float m_fMountScales[EArmType_MaxSize];

	struct SGivePresent
	{
		int			iItemId;
		char		szEffect[256];
	};
	std::vector<SGivePresent>	m_vectorGivePresents;

	// LoadMap��������
	short	m_shLoadMapNum;
	float	m_fLoadMapProbability;	// ��Ҫ���Ӹ�����ʾ�ı���������
	std::vector<short>	m_vecProbabilityLoadMaps;	// ��Ҫ���Ӹ�����ʾ�ı���

	RECT m_rcFreeTipCloseRect;		// FreeTip�ϴ��λ��
	std::string m_strFreeTipCloseBtn;// ͼ��·��

	int		m_nLoginMapId;
	int		m_nSelectPlayerMapId;
	int		m_nCreateMapId;
	int     m_nFirstMapId;

	//˵����������
	RECT		m_ChatPaoPaoRect;
	RECT		m_ChatPaoPaoInnerRect;
	std::string m_strChatPaoPaoTexture;// ͼ��·��

	//��̯����
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
	 * ���߽��� ע��
	 */
	std::string m_strOnlineRewardFile;		// ����֡�ļ�·��
	int		m_nOnlineRewardItemWidth;		// ���
	int		m_nOnlineRewardItemHeight;		// �߶�
	int		m_nOnlineRewardRow;				// ����
	int		m_nOnlineRewardColumn;			// ����
	int		m_nOnlineRewardTime;			// ÿ֡���
	int		m_nOnlineRewardCount;			// ��֡��

	//С����
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

	//��ť��˸
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
		char	m_acSingName[MAX_PATH]; // ����������
		PlayerNPCActions() : m_nId(-1)
		{
			memset( m_acSingName, 0, sizeof( m_acSingName ) );
		}
	};
	std::map< int, PlayerNPCActions > m_PlayerNpcActions;
	
	// �����ܲ�����ʱ�䳤�ȣ�����
	int		m_nRoleRunLoopTime;

	std::string m_strReliveEffect;  //������Ч
	std::string m_strReliveAnim;    //�����
	std::string m_strImmunity;      //�۹���Ч

	std::string m_strNpcShowEffect; //Npc��ʾ��Ч
	std::string m_strNpcShowAnim;   //Npc��ʾ����

	std::string m_strNpcHideEffect; //Npc������Ч
	std::string m_strNpcHideAnim;   //Npc���ض���

	//ͼ����Ч
	std::string m_SuAnimalCardEffect;
	int  m_nFriendLevel;

	std::string m_strRanklistWebPath;	//���а��web���ص�ַ
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