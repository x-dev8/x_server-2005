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
        DWORD dwOnlinePlayer;               // ����ҽ�ɫ��
        DWORD dwEnterGameWorldOnlinePlayer; // ������Ϸ������ҽ�ɫ��Ŀ
        DWORD dwMaximalOnlinePlayer;        // �����������
        DWORD dwToalMonster;				// Monster����
		DWORD dwTotalNPC;					// NPC����
		DWORD dwTotalItemchar;				// ItemChar����
        DWORD dwCharacterCount;             // �ܽ�ɫ�� ����onlinePlayer Npc Monster ItemChar
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
    void ReleaseAllObject(); // �ͷ����е�Object,ע��:ֻ�ڳ����˳�ʱ��(һ�㲻��)

    BaseCharacter* GetCharacterByID( GameObjectId iID );

    GamePlayer*    GetGamePlayerByName( const std::string& strName );    
    void           GetGamePlayersByName( const std::string& strName, StringContainer& szCharList);    
    GamePlayer*    GetGamePlayerByDBID( DWORD nDBID );

    BaseCharacter* GetCharacterByNpcID( int nNpcId, unsigned int nMapId );
	BaseCharacter* GetCharacterByMonsterID( int nMonsterId, unsigned int nMapId );
    IBaseCharControl*    GetCharacterByIDAndLifecode( GameObjectId iID,unsigned short ustLifeCode );
    
    GamePlayer*    GetCharacterByAccountID( uint32 dwAccount);

    bool           InitTalismanEquip( OUT SCharItem& rItem, ItemDefine::SItemTalisman* pItemCanEquip );
    bool           EquipBaseRand( OUT IN SCharItem& rItem, bool bJustFixedRand = false ); // ���ɻ���������� JuseFixedRand ֻ�Ϲ̶��������
	bool           EquipBaseRand( OUT IN uint16 *rands, ItemDefine::SItemCanEquip* pConfig, bool bJustFixedRand = false ); // ���ɻ���������� JuseFixedRand ֻ�Ϲ̶��������
	//bool           EquipBaseRand_Hero( OUT IN uint16 *rands, ItemDefine::SItemCanEquip* pConfig, bool bJustFixedRand = false ); // ���ɻ���������� JuseFixedRand ֻ�Ϲ̶��������
    bool           EquipPurpleRand( OUT IN SCharItem& rItem); // �����̽��������
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


    // ��õ�ǰ����ID
    uint8 GetWeakCountry() const { return m_uchWeakCountryID; }

    // ��������ID
    void SetWeakCountry( uint8 uchValue ) {  m_uchWeakCountryID = uchValue; }

	uint8 GetStrongCountry() const {return m_uchStrongCountryID;}
	void SetStrongCountry(uint8 uchValue) { m_uchStrongCountryID = uchValue;}

    void UpdateCountryOnLineCount( uint8 uchCountryID, int nCount );

    // ��������ʱ, �漴��������
    uint8 CalcRandCreateCountryID();

	void EquipScore( SCharItem& rItem, ItemDefine::SItemCommon *pItemDetail ); //����װ������
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

    CharacterByDbIdContainer      m_mapDBCharacters; // db id �� ��̬id ����
    CharacterByAccountIdContainer accountCharacters; // account id �� ��̬Id ����

    typedef std::map<std::string, GameObjectId>         CharacterByNameContainer;
    typedef CharacterByNameContainer::iterator ItrCharacterByNameContainer;
    CharacterByNameContainer m_mapNameCharacters;

    unsigned long serverStartTime;
    volatile bool g_bNowSave;
    int           g_nExpPer;           // ����İٷֱ�
    int           g_nSkillExpPer;      // ���ܵİٷֱ�
    bool          g_bIsChangeSkillExp; // ���ܰٷֱ��Ƿ�ı�

private:
    SOnlineCharacterInfo _onlineCharactorInfo;
    unsigned long        _nLiftCodeIndex;

    // ��ǰ����ID
    uint8 m_uchWeakCountryID;
	uint8 m_uchStrongCountryID;
    
    int m_nCountryOnLineCount[ CountryDefine::Country_Max ];

	static RunTimeData* pRunTimeDataInstance;
};

#endif // __SERVERCOMMON_SHAREDATA_H__
