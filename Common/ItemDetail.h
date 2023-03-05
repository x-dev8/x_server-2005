/********************************************************************
    Filename:     ItemDetail.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __COMMON_ITEMDETAIL_H__
#define __COMMON_ITEMDETAIL_H__

#pragma once

#include "GlobalDef.h"
#include "GameDefinePet.h"
#include "ItemDefine.h"
#include "MapStrToID.h"
#include "ProcessCharInfo.h"
#include "Array.h"
#include "Dxsdk/D3DX9Math.h"
// #include "Tinyxml\tinyxml.h"
class CSlkReader;

class CItemDetail
{
public:
    typedef std::vector< unsigned short >            RandContainer;

	typedef std::vector< ItemDefine::RandAttr >			RandAttrContainer;
	typedef RandAttrContainer::iterator		ItrRandAttrContainer;

    typedef std::map< std::string, ItemDefine::SCreatureSound* > CreatureSoundContainer;
    typedef CreatureSoundContainer::iterator         ItrCreatureSoundContainer;

    typedef std::vector<ItemDefine::SItemCommon*> vectorItem;       //Vector��¼Item����
    typedef std::map<int,ItemDefine::SItemCommon*> ItemContainer;   //Map��¼Item����
    typedef std::map< unsigned short, unsigned short > mapSkillNO;
    typedef std::vector< unsigned short > vectorSkill;

protected:    
    CreatureSoundContainer _creatureSounds;
    vectorItem             m_vectorItem;
    std::map< short, std::vector<ItemDefine::SItemCanEquip*> > m_mapSuit;
    vectorItem m_BakupItem ;

    //map�����ֲ�����Ʒ����
    CMapStrToIDMgr m_ItemFinder;

    //��¼ÿ��Item��ID��
    typedef std::vector<int> vectorItemID;
    vectorItemID m_vectorItemID;

    //��Itemϸ��ΪRestore,Weapon,Armour,Glove,Shoe,Cap
    vectorItem m_vecRestoreItem;
    vectorItem m_vecWeaponItem;

    vectorItem m_vecArmourItem;
    vectorItem m_vecGloveItem;
    vectorItem m_vecShoeItem;
    vectorItem m_vecCapItem;

    vectorItem m_vecSkillItem;
    vectorItem m_vecStatusItem;
    vectorItem m_vecGameActionItem;
    vectorItem m_vecMaterialItem;    
    vectorItem m_vecGemItem;
    vectorItem m_vecReelItem;
    vectorItem m_vecTreasureBoxItem;
    vectorItem m_vecCheckUpItem;
    vectorItem m_vecGuildBoxItem;
    vectorItem m_vecSpecialItem;
    vectorItem m_vecTalismanItem;
    vectorItem m_vecOtherItem;
	vectorItem m_vecPetEquipItem;//����װ��

    //��Item���ݵȼ�����
    Array<vectorItem, 100>    m_vectorLevelItem;

    //��¼Skill��ItemID��Index
    mapSkillNO m_mapSkillNO;

    //��¼Skill��ItemID
    vectorSkill m_vecSkill;

    Array< Array<ItemDefine::SItemSkill, ItemDefine::MaxLevel_Skill>, ItemDefine::MaxNum_Skill>    m_SkillArray;  // ���Skill���������(�����ȼ�) 
    Array< Array<ItemDefine::SItemStatus, ItemDefine::MaxLevel_Status>, ItemDefine::MaxNum_Status> m_StatusArray; // ���Status���������(�����ȼ�)

    Array<vectorSkill, EArmType_MaxSize> m_ArmSkillArray; //����ְҵ���Skill���������

    //��¼Profession��vector��map
    typedef std::vector<ItemDefine::SProfession> vectorProfession;
    typedef std::map<std::string,short,std::less<std::string> > mapProfession;
    vectorProfession        m_vecProfession;
    mapProfession           m_mapProfession;

    //��¼Monster��vector��map
    typedef std::vector<ItemDefine::SMonster*>       MonsterInfoContainer;
    typedef std::map< std::string, int > Name2IndexMonsterContainer;
    typedef std::map< int, int >         Id2IndexMonsterContainer;
    MonsterInfoContainer       _MonsterInfos;
    Name2IndexMonsterContainer _Name2IndexMonsters;
    Id2IndexMonsterContainer   _Id2IndexMonsters;

    //��¼Pet��vector��map
    typedef std::vector< ItemDefine::SPetMonster* >     PetMonsterContainer;
    typedef std::map< int, int >            Id2IndexPetMonsterContainer;
    typedef std::map< std::string, int >    Name2IndexPetMonsterContainer;
    typedef std::map< int, std::vector< ItemDefine::SPetMonster* > >  PetTypeMonsterContainer;
    PetMonsterContainer             m_vecPetMonster;
    Id2IndexPetMonsterContainer     m_mapId2IndexPetMonster;
    Name2IndexPetMonsterContainer   m_mapName2IndexPetMonster;
    PetTypeMonsterContainer         m_mapPetTypeList;
    //Array< std::vector< SPetMonster* >, MAX_PETIDENTIFY_COUNT >    m_PetTypeArray;

    //��¼Drome��vector��map
    typedef std::vector<ItemDefine::SDrome*> vectorDrome;
    typedef std::map< std::string, int, std::less<std::string> > mapDrome;
    vectorDrome  m_vecDrome;
    mapDrome     m_mapDrome;

    //��¼Traffic��vector��map
    typedef std::vector<ItemDefine::STraffic> vectorTraffic;
    typedef std::map< std::string, int, std::less<std::string> > mapTraffic;
    vectorTraffic       m_vecTraffic;
    mapTraffic          m_mapTraffic;
    typedef std::vector<ItemDefine::SCreatItemMod*>vectorCreatItemMod;    
    vectorCreatItemMod m_vecCreatItemMod;

    typedef std::vector<ItemDefine::sIcon*>vectorIcon;
    vectorIcon m_vectorIcon;

    //��¼������Ʒ,ԭ�����Ʒ�Ķ�Ӧ����
    typedef std::vector<ItemDefine::SProduceItem*> vectorProduceItem;
    typedef std::vector<ItemDefine::SProduceItem*>::iterator iterProduceItem;
    vectorProduceItem m_vecProduceItem;

    // �������
    typedef std::map< unsigned short, ItemDefine::SRandAttribute*>                  RandContainerById;
    typedef std::multimap< short, ItemDefine::SRandAttribute*>                      RandContainerByLevel;
    typedef RandContainerByLevel::iterator                              ItrRandContainerByLevel;    
    typedef std::pair<ItrRandContainerByLevel, ItrRandContainerByLevel> RandPairResult;
    RandContainerById    _RandsById;
    RandContainerByLevel _RandsByLevel;
	//Ʒ��ǿ��ϵ��
	typedef std::map< uint8, ItemDefine::SEquipQualityIntensity* >		EquipQualityIntensityContainer;
	EquipQualityIntensityContainer	m_mapEquipQualityIntensity;

    // ����ȼ������Ͷ�Ӧ�����ֵ
    typedef std::map< unsigned short, float >                           mapRandMaxValueByType;
    typedef std::map< short, mapRandMaxValueByType >                    mapRandMaxValueByLevelType;
    mapRandMaxValueByLevelType _RandMaxValueByLevelType;

    //����������������
    typedef std::vector<ItemDefine::SUpBaseAttr*> vectorUpBaseAttr;
    typedef std::map< unsigned short ,ItemDefine::SUpBaseAttr*> mapUpBaseAttr;
    vectorUpBaseAttr m_vectorUpBaseAttr;
    mapUpBaseAttr    m_mapUpBaseAttr;

    BYTE*    m_pbyGlobalBuffer;
    DWORD    m_dwGlobalBufferSize;
    DWORD    m_dwGlobalBufferUsed;

    DWORD    AllocGlobalBuffer( DWORD dwBufferSize );
    

    typedef std::map<int,ItemDefine::ReputeStruct> ReputeMap;
    typedef ReputeMap::iterator ReputeMapIter;
    ReputeMap ReputeList;

    //Slk�����ֶζ�ȡ����
    bool GetIntField( CSlkReader *pReader,const char * szColName,int &iValue );
    bool GetStringField(  CSlkReader *pReader,const char * szColName,std::string& pstrRetValue ) ;
    bool GetFloatField( CSlkReader *pReader, const char * szColName, float &fValue );

    //������Item����������
    bool AddItemToContainer( ItemDefine::SItemCommon *pItem );

    // ��ȡSlk�����ļ�����غ���
    bool AddItemConfig     ( const char *szFileName );
    bool AddRestoreItem    ( const char *szFileName ); // �ָ�ҩƷ
    bool AddWeaponItem     ( const char *szFileName ); // ����
    bool AddArmourItem     ( const char *szFileName ); // ����
    bool AddSkillItem      ( const char *szFileName ); // ����
    bool AddStatusItem     ( const char *szFileName ); // ״̬
    bool AddActionItem     ( const char *szFileName ); // ��������
    bool AddMaterialItem   ( const char *szFileName ); // ԭ��
    bool AddGemItem        ( const char *szFileName ); // ��ʯ
    bool AddTaskItem       ( const char *szFileName ); // ����
    bool AddOtherItem      ( const char *szFileName ); // ����[ ������ ]
    bool AddReelItem       ( const char *szFileName ); // ����
    bool AddTreasureBoxItem( const char *szFileName ); // ����
    bool AddCheckUpItem    ( const char *szFileName ); // ��������������һЩ��Ʒ
	//bool AddRealAwardItem  ( const char *szFileName );
    bool AddGuildBoxItem   ( const char *szFileName );
    bool AddSpecialItem    ( const char *szFileName );
    bool AddTalismanItem   ( const char *szFileName );
	bool AddPetEquipItem   ( const char *szFileName );

    void ReadCanEquipData ( CSlkReader &pReader, ItemDefine::SItemCanEquip* pEquip, const char* szFileName );

    void AddCardItem      ( CSlkReader* pReader, ItemDefine::SItemCommon& common );
    void AddCrystalItem   ( CSlkReader* pReader, ItemDefine::SItemCommon& common );

    //ȡ�ü���ְҵҪ��
    bool GetProfessionCondition( ItemDefine::SSkillProfessionCondition *pCondition, char *szProfession,char *szLevel );

    //ȡ�ü���ʹ��Ҫ��
    //bool GetSkillUsedCondition( SSkillUsedCondition *pCondition, char *szSkill, char *szMinUsed,char *szMaxUsed );
    //void GetSkillUsingConditionFromString( SItemSkill *pSkill,char *szStr );
    //void GetSkillUnderstandConditionFromString( SItemSkill *pSkill,char *szStr );

    //װ�ط�ʯ�����ܵĶ�Ӧ��ϵ
    bool LoadStoneSkill( char *szFile );

    //װ�ؼ���Ƭ�ε����ܵĶ�Ӧ��ϵ
    bool LoadSkillToSkill( char *szFile );

    //װ��������Ʒ,ԭ�����Ʒ�Ķ�Ӧ��ϵ
    bool LoadProduceItem( char *szFile );

    //װ�ع�ʽϵ������ʽ��
    bool LoadFormulamodulus(char *szFile );

protected:
    CItemDetail();
    virtual ~CItemDetail();

public:
	const char* GetString( DWORD dwAddr );

    //��������Slk��������
    bool LoadSlkItemDetail( const char *szPath,FILE *fpOutput = 0 );

    //װ��ÿ��һ���Զ����ӵ�����
    bool LoadSlkBaseAttr(char *szFile );
    
    bool LoadSlkMonster( const char *szFile);   // װ�ع���������Ϣ
	bool LoadXmlMonster( const char *szFile);   // ��XML��װ�ع���������Ϣ
	bool SaveXMLMonster( const char *szFile);   // ����XML����������Ϣ

    bool LoadSlkPetMonster( const char *szFile);   // װ�س���������Ϣ
    bool LoadXmlPetMonster( const char *szFile);   // ��XML��װ�س���������Ϣ
    bool SaveXMLPetMonster( const char *szFile);   // ����XML����������Ϣ

    bool LoadSlkMount( const char* szFile );                // װ������������Ϣ
    bool LoadXmlMount( const char* szFileName );            // ��XMLװ�����������Ϣ
    bool SaveXmlMount( const char* szFileName );            // ��XML�������������Ϣ

    bool LoadSlkCreatureSound( const char* szFile );        // ת����������������Ϣ
    bool LoadXmlCreatureSound( const char* szFileName );    //��XML��װ�ع����������Ϣ
    bool SaveXmlCreatureSound( const char* szFileName );    //��XML�б�������������Ϣ

    //��ȡItem����غ���
    ItemDefine::SItemCommon* GetItemByName(const char*szItemName );
    ItemDefine::SItemCommon* GetItemByNameAndLevel( char*szItemName, int nLevel );
    ItemDefine::SItemCommon* GetItemByID( unsigned short ustItemID );
    ItemDefine::SItemCommon* GetItem( unsigned short ustItemID,int iItemType );
	
    //ȡ�ö�Ӧ���ߵ�����
    uint8 GetItemType( unsigned short ustItemID);
    bool  IsEquipItem( unsigned short ustItemID);

    // ȡ�ö�Ӧ��װmap
    std::vector<ItemDefine::SItemCanEquip*>* GetSuitsByID( short stSuitID );

    //��ȡItem���ֺ���������
    int GetWeaponNumber( );
    int GetArmourNumber( );
    int GetGloveNumber( );
    int GetShoeNumber( );
    int GetCapNumber( );

    ItemDefine::SItemCommon* GetWeaponItem( int iIndex );
    ItemDefine::SItemCommon* GetArmourItem( int iIndex );
    ItemDefine::SItemCommon* GetGloveItem( int iIndex );
    ItemDefine::SItemCommon* GetShoeItem( int iIndex );
    ItemDefine::SItemCommon* GetCapItem( int iIndex );

    // ����ԭ��
    const std::vector<ItemDefine::SItemCommon*>&  GetMaterialItemList() const { return m_vecMaterialItem; }
    // ���б�ʯ
    const std::vector<ItemDefine::SItemCommon*>&  GetGemItemList() const { return m_vecGemItem; }
	const std::vector<ItemDefine::SItemCommon*>& GetRestoreItemList() const { return m_vecRestoreItem;}
    //��ȡ���ܵ������Ϣ
    ItemDefine::SItemSkill* GetSkillByIndex( int iIndex ) ;
    ItemDefine::SItemSkill* GetSkillByID   (unsigned short ustSkillItemID,  unsigned short ustSkillLevel) ;

    int         GetSkillIndexByID( unsigned short ustSkillItemID );
    DWORD       GetSkillHoldTime(unsigned short ustSkillID, unsigned short ustSkillLevel);
    DWORD       GetSkillHoldTime(ItemDefine::SItemSkill *pSkill);
    BOOL        GetSkillNeedInfo( SCharBaseInfo *pCharBaseInfo, SCharOtherDataClient *pCharOtherInfo, int nSkillCurExp, int nId, int nLevel, char* szSkillInfo, size_t SkillInfoSize);

    const vectorSkill& GetProfessionSkill( uint8 iProfession ) const
    {
        if(iProfession >= EArmType_MaxSize)
        { return m_ArmSkillArray[0]; }

        return m_ArmSkillArray[iProfession];
    }

    //��ȡ״̬�������Ϣ
    ItemDefine::SItemStatus* GetStatusBySkill   ( const ItemDefine::SItemSkill *pSkill );
    ItemDefine::SItemStatus* GetMeStatusBySkill ( const ItemDefine::SItemSkill *pSkill, uint8 index  );
    ItemDefine::SItemStatus* GetDstStatusBySkill( const ItemDefine::SItemSkill *pSkill );
    ItemDefine::SItemStatus* GetStatus( unsigned short ustStatusItemID, unsigned short ustStatusLevel );

    //��ȡ������������
    int FindMonsterIndexByName( const char* szName );
    int FindMonsterIndexById( int nId );
    ItemDefine::SMonster* GetMonster( int nIndex );
    ItemDefine::SMonster* GetMonsterById( int nId );
    ItemDefine::SMonster* GetMonsterByName( const char* szName );

    inline int GetMonsterNumber()
    { 
        return (int)(_MonsterInfos.size()); 
    }
    inline MonsterInfoContainer & GetMonsterInfo() 
    { 
        return _MonsterInfos; 
    }
    inline void AddNewMonster(ItemDefine::SMonster * &pMonster) 
    { 
        _MonsterInfos.push_back(pMonster); 
    }
	inline void DelOneMonster(MonsterInfoContainer::iterator &it) 
    { 
        _MonsterInfos.erase(it); 
    } 

    //��ȡ������������
    int FindPetIndexById( int nId );
    int FindPetIndexByName( const char *szName );
    ItemDefine::SPetMonster* GetPet ( int nIndex );
    ItemDefine::SPetMonster* GetPetById( int nId );
    ItemDefine::SPetMonster* GetPetByName( const char* szName );
    std::vector< ItemDefine::SPetMonster* >& GetPetListByType( uint16 petType );
    int GetTalentSkillIdByType( uint16 petType );
    const char* GetPetTypeName( uint16 petType );
	std::map< int, std::vector< ItemDefine::SPetMonster* > >& GetPetMonsterList() { return m_mapPetTypeList;}
    inline int GetPetNumber()
    { return (int)(m_vecPetMonster.size()); }

    ItemDefine::SCreatureSound* GetCreatureSound( const std::string& strName );
    ItrCreatureSoundContainer GetCreatureSoundItr( const std::string& strName );

    //��ȡ������������
    int     FindDromeIndxByName( char *szName );
    ItemDefine::SDrome* GetDrome( int nIndex );
    ItemDefine::SDrome* GetDromeByID( int nID );
    ItemDefine::SDrome* GetDromeByName( char *szName );

    inline int GetDromeNumber()
    { 
        return (int)(m_vecDrome.size()); 
    }

    inline int GetItemCount( )
    {
        return static_cast< int >( m_vectorItemID.size() );
    }
    inline int GetItemID( int iIndex )
    {
        return m_vectorItemID[iIndex];
    }

    BYTE* GetAddrPointer( DWORD dwAddr );
    BOOL  AllocStringCopy( const char* pszString );
    BYTE* AllocItem( DWORD dwItemType, DWORD dwSize );
    
    BOOL LoadBinFile( const char* pszFilename );
    BOOL SaveBinFile( const char* pszFilename );
    //BOOL LoadBinFile( const char* pszFilename );

    const char* GetStringByDword(DWORD dwName);    

    void SetCanEquipByString(char *szDst,const char *pszEquip);

    uint32   IsCanSplitItem( uint16 itemId ); // �Ƿ���Էֽ���Ʒ

    //װ������������ɵ�����
    bool     LoadSlkRand( const char* szFileName ); // EquipmentRandom.slk
    bool     LoadXmlRand( const char* szFileName ); // ��XML�м��������������
    bool     SaveXmlRand( const char* szFileName ); // ��XML�б�������������� EquipmentRandom.config
	bool     LoadXmlEquipQualityIntensity( const char* szFileName ); // ��XML�м���װ��Ʒ��ǿ��ϵ��
	bool     SaveXmlEquipQualityIntensity( const char* szFileName ); // ��XML�б���װ��Ʒ��ǿ��ϵ�� EquipQualityIntensity.config


    ItemDefine::SRandAttribute* GetRandByID(unsigned short id);
	float GetEquipQualityIntensity(uint8 nQuality);
	float GetEquipRandAttrValue( float fRandValue, uint8 nQuality );

    bool            HaveSameRandType(unsigned short usRandID1, unsigned short usRandID2);
    long            GetRandByLevel( short level, OUT RandContainer& result );
	long            GetRandByLevel( short level, OUT RandAttrContainer& result );

    void            SetRandValueLevelType(float value, short level, unsigned short type);             // ��ȡ�ȼ������Ͷ�Ӧ�����ֵ
    float           GetMaxValueByRandLevelType( short level, unsigned short type );

    ItemDefine::SUpBaseAttr* GetBaseAttrByLevel(short sLevel);


    void GetCreatItemModByLevel(unsigned short ustLevel,std::vector<ItemDefine::SCreatItemMod*> &pvtCreatItemMod);
    ItemDefine::SCreatItemMod *GetCreatMod(unsigned short ustLevel,short stSize,bool bWeapon,bool bArmour,short stType);

    ItemDefine::sIcon* GetIconFileByID(unsigned short ustId);

    //���ȡ��һ���ȼ���Χ�ĵ���
    unsigned short GetRandomLevelRangeItem(int iMinLevel, int iMaxLevel);

    bool LoadSlkTraffic( const char* szFileName );          //װ�ؽ�ͨ�������Ϣ
    bool LoadSlkProfession( char *szFile );                 //װ��ְҵ�������Ϣ
    bool LoadSlkCharModulus( char *szFile );                //װ�ؽ�ɫϵ���������Ϣ
    bool LoadSlkNewCreatItem(char *szFile);
    bool LoadSlkIcon(char* szFile);

    //��ȡְҵ�������Ϣ
    ItemDefine::SProfession *GetProfession( int iIndex );
    int         GetProfessionNum( void );
    int         GetProfessionID( char *szName );
    ItemDefine::SProfession *GetProfession( char *szName );

    //��ȡ��Ʒ����,ԭ�����Ʒ�Ķ�Ӧ��ϵ
    ItemDefine::SProduceItem* GetProduceItem( int iIndex );
    int           GetProduceItemSize( );

    //��ȡ���ܵ�������Ϣ
    int CreateSkillDesc( unsigned short ustSkillID, unsigned short ustSkillLevel, 
        char (*pDesc)[256], DWORD *pDescColor, int iDescLength );
    //��ȡ״̬��������Ϣ
    int CreateStatusDesc( unsigned short ustStatusID, unsigned short ustStatusLevel,
        char (*pDesc)[256], DWORD *pDescColor, int iDescLength );

    //��ȡ��ͨ���������
    int FindTrafficIndexByName( char *szName );
    ItemDefine::STraffic *GetTraffic( int nIndex );
    ItemDefine::STraffic *GetTrafficByID( int nID );
    ItemDefine::STraffic *GetTrafficByName( char *szName );

    inline size_t GetTrafficNumber() const 
    { 
        return m_vecTraffic.size(); 
    }

    //���� ��
    inline short CItemDetail::GetReputeListSize()
    {
        return static_cast< short >( ReputeList.size() );
    }

    inline ItemDefine::ReputeStruct* CItemDetail::GetReputeById( int nID )
    {
        ReputeMapIter iter = ReputeList.find( nID );
        if ( iter == ReputeList.end() )
        { return NULL; }

        return &( iter->second );
    }
};

bool   IsNormalAttack   ( unsigned short ustSkillID );
bool   IsCollectSkill   ( unsigned short ustSkillID );
bool   IsRecipeSkill    ( unsigned short ustSkillID );
bool   IsDamageSkill    ( unsigned short ustSkillID );
bool   IsMountSkill     ( unsigned short ustSkillID );
bool   IsHoldSkill      ( unsigned short ustSkillID );

bool   IsSkillCanBeInterrupt( unsigned char interrupeType, unsigned short ustSkillID );

const char* GetWeaponTypeNamed( int nIdx );
uint32 GetEquipTypeByName( const char* pName );
const char * FindActionStringByID( const int nID);
int FindActionIdByName( const char* pszName );
int GetIDByConstString( const char* szString,char**pszString,int iHowManyString );

extern CItemDetail& GettheItemDetail();
extern int GetItemTypeByString ( const char *szStrItemType );
extern int GetBagTypeByItemType( int nItemType );

extern void OutputSlkLoadingMessage( char* pszString, ... );

/////////////////////////////////////////////////////////////////////////
#define SLK_GET_INT( target, name ) \
    iValue = 0; \
    if( !pReader.GetIntFieldByName( name, iValue ) ) \
{ \
    OutputSlkLoadingMessage( "\tError: %s ��ȡ[%s]ʧ��\r\n", name, szFileName  ); \
} \
    else \
{\
    target = iValue;\
}

#define SLK_GET_STRING( target, name ) \
    strValue = "";\
    if( !pReader.GetStringFieldByName( name, strValue ) ) \
{ \
    OutputSlkLoadingMessage( "\tError: %s ��ȡ[%s]ʧ��\r\n", name, szFileName  ); \
} \
    else \
{\
    target = strValue;\
}

#define SLK_GET_FLOAT( target, name ) \
    fValue = 0.0f;\
    if( !pReader.GetFloatFieldByName( name, fValue ) ) \
{ \
    OutputSlkLoadingMessage( "\tError:%s ��ȡ[%s]ʧ��\r\n", name, szFileName ); \
} \
    else \
{\
    target = fValue;\
}

#define CopyCommon( pItemDest,common ) *(ItemDefine::SItemCommon*)pItemDest = common;
//////////////////////////////////////////////////////////////////

#endif // __COMMON_ITEMDETAIL_H__
