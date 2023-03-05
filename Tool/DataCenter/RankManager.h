#pragma once

#include "DataCenterDefine.h"
#include "mysql++.h"
#include <map>
#include "GameTimer.h"
#include "DataCenterConfig.h"
#include "tstring.h"

using namespace  std;
using namespace DataCenterDefine;

union ReadCharData
{
	BYTE*   byte;
	bool*   boolean;
	int*    i;
	DWORD*  dw;
	char*   c;
	void*   p;
	float*  f;
	short*  s;

	ReadCharData(void* in) :p(in)
	{}
};

class CharChunkWR
{
public:
	enum EConstDefine
	{
		// ChunkBuffer大小
		CD_CharBaseInfoBufferSize = 1024 * 100,
		CD_ItemInfoBufferSize     = 1024 * 40,
		CD_VisualInfoBufferSize   = 1024 * 40,
		CD_OtherInfoBufferSize    = 1024 * 400,
		CD_ExtendInfoBufferSize   = 1024 * 400,
		CD_MountInfoBufferSize    = 1024 * 40,   
		CD_AchieveDataBufferSize  = 1024 * 100,
		CD_IdentifyDataBufferSize = 1024 * 100,

		// Zip需要的Buffer大小
		CD_ZipTempBufferSize      = 1024 * 40,

		// Encode需要的Buffer大小
		CD_EncodeFieldBufferSize  = 1024 * 10,
		CD_EncodeFieldBufferSize_Guild = 1024 * 6,

		// UnZip需要的Buffer大小
		CD_UnZipTempBufferSize_Char  = 1024 * 300,
		CD_UnZipTempBufferSize_Item  = 1024 * 40,
		CD_UnZipTempBufferSize_Guild = 1024 * 20,

		// Decode需要的Buffer大小
		CD_DecodeFieldBufferSize_Char  = 1024 * 300,
		CD_DecodeFieldBufferSize_Item  = 1024 * 40,
		CD_DecodeFieldBufferSize_Guild = 1024 * 10,
	};

public:
	/*bool WriteCharData   ( SCharBaseInfo*   pInfo,          uint32& nActualSize, uint8* pOutBuffer, uint32 outBufferSize );    
	bool WriteItemData   ( SCharItem*       pItem,          uint32& nActualSize, uint8* pOutBuffer, uint32 outBufferSize );
	bool WriteVisualData ( SCharVisual*     pInfo,          uint32& nActualSize, uint8* pOutBuffer, uint32 outBufferSize );
	bool WriteOtherData  ( SCharOtherData*  pOtherData,     uint32& nActualSize, uint8* pOutBuffer, uint32 outBufferSize );
	bool WriteExtendData ( SExtendData*     pExtendData,    uint32& nActualSize, uint8* pOutBuffer, uint32 outBufferSize );
	bool WriteAchieveData( SAchieveData*    pAchieveData,   uint32& nActualSize, uint8* pOutBuffer, uint32 outBufferSize );
	bool WriteIdentifyData( SIdentifyData*  pIdentifyData,  uint32& nActualSize, uint8* pOutBuffer, uint32 outBufferSize );
	bool WriteMountData  ( SMountItem*      pMount,         uint32& nActualSize, uint8* pOutBuffer, uint32 outBufferSize );
	bool WritePetData    ( SPetItem*        pPet  ,         uint32& nActualSize, uint8* pOutBuffer, uint32 outBufferSize );*/

	/*bool LoadCharData    ( uint8* buffer,    uint32 bufferSize, SCharBaseInfo* pInfo );
	void LoadCharApto    ( ReadCharData inP, int nSize,         SCharBaseInfo* pInfo );
	void LoadCharLive    ( ReadCharData inP, int nSize,         SCharBaseInfo* pInfo );    
	bool LoadOtherData   ( uint8* buffer,    uint32 bufferSize, SCharOtherData* pOtherData   );
	bool LoadExtendData  ( uint8* buffer,    uint32 bufferSize, SExtendData*   pExtendData   );
	bool LoadAchieveData ( uint8* buffer,    uint32 bufferSize, SAchieveData*  pAchieveData  );
	bool LoadIdentifyData( uint8* buffer,    uint32 bufferSize, SIdentifyData* pIdentifyData );
	bool LoadVisuals     ( uint8* buffer,    uint32 bufferSize, SCharVisual* pInfo );*/
};

enum ERankWorkStatus
{
	SS_TryConnect,
	SS_Connected,
	SS_ReConnected,
};

enum ERankConstDefine
{
	ECD_PingTime					= 3 * 1000 * 60, // 3 分钟

	ECD_PersonalRankCount			= 100,//个人排行榜的数量
	ECD_PersonalRankTypeMax			= 8,//个人排行榜的种类
	ECD_PersonalRankType_LV			= 0,//等级排行榜
	ECD_PersonalRankType_Fortune	= 1,//财富排行榜,银币,money
	ECD_PersonalRankType_Honor		= 2,//荣誉排行榜
	ECD_PersonalRankType_Offer		= 3,//军功排行榜
	ECD_PersonalRankType_Fame		= 4,//功勋排行榜
	ECD_PersonalRankType_Kill		= 5,//杀敌排行榜
	ECD_PersonalRankType_Charm		= 6,//魅力排行榜
	ECD_PersonalRankType_PK			= 7,//红名排行榜

	ECD_GuildRankCount				= 100,//军团排行榜的数量

	ECD_CountryRankCount			= 3,//国家排行榜的数量
	ECD_CountryRankType 			= 2,//国家排行榜的种类
	ECD_CountryRankType_Power		= 0,//国家实力榜
	ECD_CountryRankType_Tribute		= 1,//兵书排行榜

	ECD_EquipScoreRank				= 100,//装备评分榜数量
};

//装备类型
enum enumEquipType
{
	equip_Helmet             = 0,  // 头盔
	equip_Armour             = 1,  // 铠甲
	equip_Glove              = 2,  // 护手
	equip_Shoe               = 3,  // 鞋子
	equip_Weapon             = 4,  // 主武器
	equip_WeaponMinor        = 5,  // 副武器
	equip_Badge              = 6,  // 徽章
	equip_Ring               = 7,  // 戒指
	equip_Bangle             = 8,  // 手镯
	equip_Shoulder           = 9,  // 肩甲
	equip_Necklace           = 10, // 项链
	equip_Sash               = 11, // 腰带
	equip_LeaderCard         = 12, // 掌门卡
	equip_Amulet             = 13, // 护身符
	equip_AecorativeGoods    = 14, // 装饰的物品
	equip_AecorativeClothing = 15, // 装饰的衣服
	equip_Trousers			 = 16, // 裤子

	equip_TypeMaxCount       = 17,
};    

class CRankInfo
{
public:
	CRankInfo();
	~CRankInfo();

	void _TryConnectToSqlDb();
	bool _CheckState();        // 检查SqlService运行情况
	bool SaveRankFile(const char *szFileName);
	bool LoadRankFile();
	void SetServerid(unsigned short id){serverid = id;}
	void SetBuildRank(bool b){bBuildRank = b;}
	unsigned short GetServerId(){return serverid;}

	void Run();
	void ProcessRank();
	void BuildRankFile();
	void ResetRankInfos();

	void AppedItem(SCharItem* pItem,Common::_tstring& strContent);
private:
	bool  bBuildRank; // 是否马上生成排行榜数据
	bool  bInit;  //是否初始化
	mysqlpp::Connection* _mySqlConnection;// 和mysql 的连接
	unsigned char _workState;
	unsigned short serverid;
	GameTimerEx          _connectTime;    // 连接时间间隔控制
	unsigned long        _lastUpdateTime; // 最新的更新时间
	time_t				 _lastSaveTime;   // 最后的生成时间

	sPersonalRank*       rankinfo_LV	 ; //等级排行榜
	sPersonalRank*       rankinfo_Fortune; //财富排行榜
	sPersonalRank*       rankinfo_Honor  ; //荣誉排行榜
	sPersonalRank*       rankinfo_Offer	 ; //军功排行榜
	sPersonalRank*       rankinfo_Fame	 ; //功勋排行榜
	sPersonalRank*       rankinfo_Kill	 ; //杀敌排行榜
	sPersonalRank*       rankinfo_Charm	 ; //魅力排行榜
	sPersonalRank*       rankinfo_PK	 ; //红名排行榜
	sPersonalRank*       rankinfo_EquipAllScore; //装备总评分

	sGuildRank*			 guildrankinfo	 ;//军团排行榜

	sCountryRank*		 countryrankinfo_Power	 ; //国家实力榜
	sCountryRank*		 countryrankinfo_Tribute ; //兵书排行榜

	sEquipScore*         equip_score_Weapon;	//1.	武器装备评分排行
	sEquipScore*         equip_score_Helmet;	//2.	头盔装备评分排行
	sEquipScore*         equip_score_Shoulder;	//3.	肩甲装备评分排行
	sEquipScore*         equip_score_Armour;	//4.	铠甲装备评分排行
	sEquipScore*         equip_score_Glove;		//5.	护手装备评分排行
	sEquipScore*         equip_score_Sash;		//6.	腰带装备评分排行
	sEquipScore*         equip_score_Shoe;		//7.	鞋子装备评分排行
	sEquipScore*         equip_score_Necklace;	//8.	项链装备评分排行
	sEquipScore*         equip_score_Ring;		//9.	戒指装备评分排行
	sEquipScore*         equip_score_Bangle;	//10.	手镯装备评分排行
	sEquipScore*         equip_score_WeaponMinor;	//11.	手套装备评分排行

	sGuildCampBattlePoint* guildcampbattle_pint;  //公会血战沙场积分排行榜
};

class CRankManager
{
public:
	CRankManager(void);
	~CRankManager(void);

public:
	static CRankManager& Instance()
	{
		static CRankManager crm;
		return crm;
	}

	void Run();
	bool InitRank();
	bool AddRankInfo(CRankInfo* pInfo);	
private:
	bool IsInit;   //是否初始化完成	
	typedef map<unsigned short,CRankInfo*> mapRankInfo; 
	mapRankInfo _mapRankInfo;
};

#define theRankManager CRankManager::Instance()