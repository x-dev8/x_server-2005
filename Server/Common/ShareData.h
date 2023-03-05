/********************************************************************
    Filename:     ShareData.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __SERVERCOMMON_SHAREDATA_H__
#define __SERVERCOMMON_SHAREDATA_H__

#include "GlobalDef.h"
#include "StaticArray.h"
#include "BaseCharacter.h"
#include "g_assert.h"
#include "CCharacterID.h"
#include "Mutex.h"

class GameWorld;
class LoginStage;
class CDBInterface;
class CItemData;
class TimeClock;
class GamePlayer;

#define theRunTimeData RunTimeData::GetInstance()

class RunTimeData
{
public:    
    struct SOnlineCharacterInfo
    {
        DWORD dwOnlinePlayer;               // 总玩家角色数
        DWORD dwEnterGameWorldOnlinePlayer; // 进入游戏世界玩家角色数目
        DWORD dwMaximalOnlinePlayer;        // 最高在线人数
        DWORD dwToalMonster;				// Monster总数
		DWORD dwTotalNPC;					// NPC总数
		DWORD dwTotalItemchar;				// ItemChar总数
        DWORD dwCharacterCount;             // 总角色数 包括onlinePlayer Npc Monster ItemChar
    };
    
    struct SControlWithLifeCode
    {
        unsigned short ustLifeCode;
        IBaseControl* pCtrl;
    };

    struct GameObject
    {
        IBaseCharControl*          m_Char;
        SControlWithLifeCode m_lifecode;
    };

public:
    static RunTimeData& GetInstance();

    void RunUpdate( uint32 dwCurrentTime );

    DWORD IncreaseOnlinePlayer( int nPlayerCount = 1); 
    DWORD IncreaseEnterWorldOnlinePlayer( int nPlayerCount = 1);
    DWORD IncreaseCharacter( int nPlayerCount = 1);
	DWORD IncreaseMonster( int nMonsterCount = 1 );
	DWORD IncreaseNPC( int nNPCCount = 1 );
	DWORD IncreaseItemchar( int nItemcharCount = 1 );
    void  OnUpdateBurthen();

    DWORD GetOnlinePlayer()           { return _onlineCharactorInfo.dwOnlinePlayer;}
    DWORD GetEnterWorldOnlinePlayer() { return _onlineCharactorInfo.dwEnterGameWorldOnlinePlayer;}
    DWORD GetMaximalOnlinePlayer()    { return _onlineCharactorInfo.dwMaximalOnlinePlayer; }
    DWORD GetCharacterCount()         { return _onlineCharactorInfo.dwCharacterCount; }
	DWORD			  GetTotalMonster()	{ return _onlineCharactorInfo.dwToalMonster; }
	DWORD			  GetTotalNPC() { return _onlineCharactorInfo.dwTotalNPC; }
	DWORD			  GetTotalItemchar() { return _onlineCharactorInfo.dwTotalItemchar; }
    
    uint8   GetObjecTypeByNpcType( uint8 npcType );

    GameObjectId  CreateObject( int type );    
    void ReleaseObject( GameObjectId iID , const char* szFile, uint32 line);    
    void ReleaseAllObject(); // 释放所有的Object,注意:只在程序退出时用(一般不用)

    BaseCharacter* GetCharacterByID( GameObjectId iID );

    GamePlayer*    GetGamePlayerByName( const std::string& strName );    
    void           GetGamePlayersByName( const std::string& strName, StringContainer& szCharList);    
    GamePlayer*    GetGamePlayerByDBID( DWORD nDBID );

    BaseCharacter* GetCharacterByNpcID( int nNpcId, unsigned int nMapId );
	BaseCharacter* GetCharacterByMonsterID( int nMonsterId, unsigned int nMapId );
    IBaseCharControl*    GetCharacterByIDAndLifecode( GameObjectId iID,unsigned short ustLifeCode );
    
    GamePlayer*    GetCharacterByAccountID( uint32 dwAccount);

    bool           InitTalismanEquip( OUT SCharItem& rItem, ItemDefine::SItemTalisman* pItemCanEquip );
    bool           EquipBaseRand( OUT IN SCharItem& rItem, bool bJustFixedRand = false ); // 生成基本随机属性 JuseFixedRand 只上固定随机属性
	bool           EquipBaseRand( OUT IN uint16 *rands, ItemDefine::SItemCanEquip* pConfig, bool bJustFixedRand = false ); // 生成基本随机属性 JuseFixedRand 只上固定随机属性
	//bool           EquipBaseRand_Hero( OUT IN uint16 *rands, ItemDefine::SItemCanEquip* pConfig, bool bJustFixedRand = false ); // 生成基本随机属性 JuseFixedRand 只上固定随机属性
    bool           EquipPurpleRand( OUT IN SCharItem& rItem); // 生成鎏金随机属性
	bool		   InitPetEquip( OUT SCharItem& rItem, ItemDefine::SItemPetEquip* pItemCanEquip );
    short          EquipRandByLevel( short stLevel );

    bool           AddMapDBID(DWORD dwDBID, GameObjectId iID, bool bReplace = true);
    bool           RemoveMapDBID(DWORD dwDBID);

    bool           AddMapNameToID(std::string strName, GameObjectId iID, bool bReplace = true);
    bool           RemoveMapNameToID(std::string strName);

    bool           AddMapAccountID( uint32 accountId, GameObjectId iId, bool bReplace = true );
    bool           RemoveMapAccountID( uint32 accountId );

    bool           CreateItem( BaseCharacter* pChar, unsigned short ustItemID, short stCount, __int64 nGUID, OUT SCharItem& rItem ,bool isChangeUnBindSum = false,unsigned short UnBindeSum =0);
    bool           CreateItem(unsigned short ustItemID, short stCount, __int64 nGUID, OUT SCharItem& rItem,bool isChangeUnBindSum = false,unsigned short UnBindeSum =0);


    // 获得当前弱国ID
    uint8 GetWeakCountry() const { return m_uchWeakCountryID; }

    // 设置弱国ID
    void SetWeakCountry( uint8 uchValue ) {  m_uchWeakCountryID = uchValue; }

	uint8 GetStrongCountry() const {return m_uchStrongCountryID;}
	void SetStrongCountry(uint8 uchValue) { m_uchStrongCountryID = uchValue;}

    void UpdateCountryOnLineCount( uint8 uchCountryID, int nCount );

    // 创建人物时, 随即国籍规则
    uint8 CalcRandCreateCountryID();

	void EquipScore( SCharItem& rItem, ItemDefine::SItemCommon *pItemDetail ); //计算装备评分
	bool EquipRandAttrByIds(SCharItem& rItem, int nRandId1 = 0, int nRandId2 = 0, int nRandId3 = 0, int nRandId4 = 0, int nRandId5 = 0, int nRandId6 = 0, int nRandId7 = 0);

protected:
    RunTimeData();
    RunTimeData( const RunTimeData& );
    RunTimeData& operator=( const RunTimeData& ){}

public:
    CCharacterID<GameObject>                   theCharacters;
    typedef std::map<unsigned long, GameObjectId> CharacterByDbIdContainer;
    typedef std::map<uint32, GameObjectId>        CharacterByAccountIdContainer;

    typedef CharacterByDbIdContainer::iterator      ItrDbIdCharacterContainer;
    typedef CharacterByAccountIdContainer::iterator ItrCharacterByAccountIdContainer;

    CharacterByDbIdContainer      m_mapDBCharacters; // db id 和 动态id 关联
    CharacterByAccountIdContainer accountCharacters; // account id 和 动态Id 关联

    typedef std::map<std::string, GameObjectId>         CharacterByNameContainer;
    typedef CharacterByNameContainer::iterator ItrCharacterByNameContainer;
    CharacterByNameContainer m_mapNameCharacters;

    unsigned long serverStartTime;
    volatile bool g_bNowSave;
    int           g_nExpPer;           // 经验的百分比
    int           g_nSkillExpPer;      // 技能的百分比
    bool          g_bIsChangeSkillExp; // 技能百分比是否改变

private:
    SOnlineCharacterInfo _onlineCharactorInfo;
    unsigned long        _nLiftCodeIndex;

    // 当前弱国ID
    uint8 m_uchWeakCountryID;
	uint8 m_uchStrongCountryID;
    
    int m_nCountryOnLineCount[ CountryDefine::Country_Max ];

	static RunTimeData* pRunTimeDataInstance;
};

#endif // __SERVERCOMMON_SHAREDATA_H__
