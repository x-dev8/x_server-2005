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
		// ChunkBuffer��С
		CD_CharBaseInfoBufferSize = 1024 * 100,
		CD_ItemInfoBufferSize     = 1024 * 40,
		CD_VisualInfoBufferSize   = 1024 * 40,
		CD_OtherInfoBufferSize    = 1024 * 400,
		CD_ExtendInfoBufferSize   = 1024 * 400,
		CD_MountInfoBufferSize    = 1024 * 40,   
		CD_AchieveDataBufferSize  = 1024 * 100,
		CD_IdentifyDataBufferSize = 1024 * 100,

		// Zip��Ҫ��Buffer��С
		CD_ZipTempBufferSize      = 1024 * 40,

		// Encode��Ҫ��Buffer��С
		CD_EncodeFieldBufferSize  = 1024 * 10,
		CD_EncodeFieldBufferSize_Guild = 1024 * 6,

		// UnZip��Ҫ��Buffer��С
		CD_UnZipTempBufferSize_Char  = 1024 * 300,
		CD_UnZipTempBufferSize_Item  = 1024 * 40,
		CD_UnZipTempBufferSize_Guild = 1024 * 20,

		// Decode��Ҫ��Buffer��С
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
	ECD_PingTime					= 3 * 1000 * 60, // 3 ����

	ECD_PersonalRankCount			= 100,//�������а������
	ECD_PersonalRankTypeMax			= 8,//�������а������
	ECD_PersonalRankType_LV			= 0,//�ȼ����а�
	ECD_PersonalRankType_Fortune	= 1,//�Ƹ����а�,����,money
	ECD_PersonalRankType_Honor		= 2,//�������а�
	ECD_PersonalRankType_Offer		= 3,//�������а�
	ECD_PersonalRankType_Fame		= 4,//��ѫ���а�
	ECD_PersonalRankType_Kill		= 5,//ɱ�����а�
	ECD_PersonalRankType_Charm		= 6,//�������а�
	ECD_PersonalRankType_PK			= 7,//�������а�

	ECD_GuildRankCount				= 100,//�������а������

	ECD_CountryRankCount			= 3,//�������а������
	ECD_CountryRankType 			= 2,//�������а������
	ECD_CountryRankType_Power		= 0,//����ʵ����
	ECD_CountryRankType_Tribute		= 1,//�������а�

	ECD_EquipScoreRank				= 100,//װ�����ְ�����
};

//װ������
enum enumEquipType
{
	equip_Helmet             = 0,  // ͷ��
	equip_Armour             = 1,  // ����
	equip_Glove              = 2,  // ����
	equip_Shoe               = 3,  // Ь��
	equip_Weapon             = 4,  // ������
	equip_WeaponMinor        = 5,  // ������
	equip_Badge              = 6,  // ����
	equip_Ring               = 7,  // ��ָ
	equip_Bangle             = 8,  // ����
	equip_Shoulder           = 9,  // ���
	equip_Necklace           = 10, // ����
	equip_Sash               = 11, // ����
	equip_LeaderCard         = 12, // ���ſ�
	equip_Amulet             = 13, // �����
	equip_AecorativeGoods    = 14, // װ�ε���Ʒ
	equip_AecorativeClothing = 15, // װ�ε��·�
	equip_Trousers			 = 16, // ����

	equip_TypeMaxCount       = 17,
};    

class CRankInfo
{
public:
	CRankInfo();
	~CRankInfo();

	void _TryConnectToSqlDb();
	bool _CheckState();        // ���SqlService�������
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
	bool  bBuildRank; // �Ƿ������������а�����
	bool  bInit;  //�Ƿ��ʼ��
	mysqlpp::Connection* _mySqlConnection;// ��mysql ������
	unsigned char _workState;
	unsigned short serverid;
	GameTimerEx          _connectTime;    // ����ʱ��������
	unsigned long        _lastUpdateTime; // ���µĸ���ʱ��
	time_t				 _lastSaveTime;   // ��������ʱ��

	sPersonalRank*       rankinfo_LV	 ; //�ȼ����а�
	sPersonalRank*       rankinfo_Fortune; //�Ƹ����а�
	sPersonalRank*       rankinfo_Honor  ; //�������а�
	sPersonalRank*       rankinfo_Offer	 ; //�������а�
	sPersonalRank*       rankinfo_Fame	 ; //��ѫ���а�
	sPersonalRank*       rankinfo_Kill	 ; //ɱ�����а�
	sPersonalRank*       rankinfo_Charm	 ; //�������а�
	sPersonalRank*       rankinfo_PK	 ; //�������а�
	sPersonalRank*       rankinfo_EquipAllScore; //װ��������

	sGuildRank*			 guildrankinfo	 ;//�������а�

	sCountryRank*		 countryrankinfo_Power	 ; //����ʵ����
	sCountryRank*		 countryrankinfo_Tribute ; //�������а�

	sEquipScore*         equip_score_Weapon;	//1.	����װ����������
	sEquipScore*         equip_score_Helmet;	//2.	ͷ��װ����������
	sEquipScore*         equip_score_Shoulder;	//3.	���װ����������
	sEquipScore*         equip_score_Armour;	//4.	����װ����������
	sEquipScore*         equip_score_Glove;		//5.	����װ����������
	sEquipScore*         equip_score_Sash;		//6.	����װ����������
	sEquipScore*         equip_score_Shoe;		//7.	Ь��װ����������
	sEquipScore*         equip_score_Necklace;	//8.	����װ����������
	sEquipScore*         equip_score_Ring;		//9.	��ָװ����������
	sEquipScore*         equip_score_Bangle;	//10.	����װ����������
	sEquipScore*         equip_score_WeaponMinor;	//11.	����װ����������

	sGuildCampBattlePoint* guildcampbattle_pint;  //����Ѫսɳ���������а�
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
	bool IsInit;   //�Ƿ��ʼ�����	
	typedef map<unsigned short,CRankInfo*> mapRankInfo; 
	mapRankInfo _mapRankInfo;
};

#define theRankManager CRankManager::Instance()