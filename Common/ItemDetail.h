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

    typedef std::vector<ItemDefine::SItemCommon*> vectorItem;       //Vector记录Item数据
    typedef std::map<int,ItemDefine::SItemCommon*> ItemContainer;   //Map记录Item数据
    typedef std::map< unsigned short, unsigned short > mapSkillNO;
    typedef std::vector< unsigned short > vectorSkill;

protected:    
    CreatureSoundContainer _creatureSounds;
    vectorItem             m_vectorItem;
    std::map< short, std::vector<ItemDefine::SItemCanEquip*> > m_mapSuit;
    vectorItem m_BakupItem ;

    //map用名字查找物品数据
    CMapStrToIDMgr m_ItemFinder;

    //记录每个Item的ID号
    typedef std::vector<int> vectorItemID;
    vectorItemID m_vectorItemID;

    //将Item细分为Restore,Weapon,Armour,Glove,Shoe,Cap
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
	vectorItem m_vecPetEquipItem;//副将装备

    //将Item根据等级分类
    Array<vectorItem, 100>    m_vectorLevelItem;

    //记录Skill的ItemID和Index
    mapSkillNO m_mapSkillNO;

    //记录Skill的ItemID
    vectorSkill m_vecSkill;

    Array< Array<ItemDefine::SItemSkill, ItemDefine::MaxLevel_Skill>, ItemDefine::MaxNum_Skill>    m_SkillArray;  // 存放Skill的相关数据(包含等级) 
    Array< Array<ItemDefine::SItemStatus, ItemDefine::MaxLevel_Status>, ItemDefine::MaxNum_Status> m_StatusArray; // 存放Status的相关数据(包含等级)

    Array<vectorSkill, EArmType_MaxSize> m_ArmSkillArray; //根据职业存放Skill的相关数据

    //记录Profession的vector和map
    typedef std::vector<ItemDefine::SProfession> vectorProfession;
    typedef std::map<std::string,short,std::less<std::string> > mapProfession;
    vectorProfession        m_vecProfession;
    mapProfession           m_mapProfession;

    //记录Monster的vector和map
    typedef std::vector<ItemDefine::SMonster*>       MonsterInfoContainer;
    typedef std::map< std::string, int > Name2IndexMonsterContainer;
    typedef std::map< int, int >         Id2IndexMonsterContainer;
    MonsterInfoContainer       _MonsterInfos;
    Name2IndexMonsterContainer _Name2IndexMonsters;
    Id2IndexMonsterContainer   _Id2IndexMonsters;

    //记录Pet的vector和map
    typedef std::vector< ItemDefine::SPetMonster* >     PetMonsterContainer;
    typedef std::map< int, int >            Id2IndexPetMonsterContainer;
    typedef std::map< std::string, int >    Name2IndexPetMonsterContainer;
    typedef std::map< int, std::vector< ItemDefine::SPetMonster* > >  PetTypeMonsterContainer;
    PetMonsterContainer             m_vecPetMonster;
    Id2IndexPetMonsterContainer     m_mapId2IndexPetMonster;
    Name2IndexPetMonsterContainer   m_mapName2IndexPetMonster;
    PetTypeMonsterContainer         m_mapPetTypeList;
    //Array< std::vector< SPetMonster* >, MAX_PETIDENTIFY_COUNT >    m_PetTypeArray;

    //记录Drome的vector和map
    typedef std::vector<ItemDefine::SDrome*> vectorDrome;
    typedef std::map< std::string, int, std::less<std::string> > mapDrome;
    vectorDrome  m_vecDrome;
    mapDrome     m_mapDrome;

    //记录Traffic的vector和map
    typedef std::vector<ItemDefine::STraffic> vectorTraffic;
    typedef std::map< std::string, int, std::less<std::string> > mapTraffic;
    vectorTraffic       m_vecTraffic;
    mapTraffic          m_mapTraffic;
    typedef std::vector<ItemDefine::SCreatItemMod*>vectorCreatItemMod;    
    vectorCreatItemMod m_vecCreatItemMod;

    typedef std::vector<ItemDefine::sIcon*>vectorIcon;
    vectorIcon m_vectorIcon;

    //记录制造物品,原料与产品的对应数据
    typedef std::vector<ItemDefine::SProduceItem*> vectorProduceItem;
    typedef std::vector<ItemDefine::SProduceItem*>::iterator iterProduceItem;
    vectorProduceItem m_vecProduceItem;

    // 随机属性
    typedef std::map< unsigned short, ItemDefine::SRandAttribute*>                  RandContainerById;
    typedef std::multimap< short, ItemDefine::SRandAttribute*>                      RandContainerByLevel;
    typedef RandContainerByLevel::iterator                              ItrRandContainerByLevel;    
    typedef std::pair<ItrRandContainerByLevel, ItrRandContainerByLevel> RandPairResult;
    RandContainerById    _RandsById;
    RandContainerByLevel _RandsByLevel;
	//品质强度系数
	typedef std::map< uint8, ItemDefine::SEquipQualityIntensity* >		EquipQualityIntensityContainer;
	EquipQualityIntensityContainer	m_mapEquipQualityIntensity;

    // 随机等级和类型对应的最大值
    typedef std::map< unsigned short, float >                           mapRandMaxValueByType;
    typedef std::map< short, mapRandMaxValueByType >                    mapRandMaxValueByLevelType;
    mapRandMaxValueByLevelType _RandMaxValueByLevelType;

    //人物升级增加属性
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

    //Slk内容字段读取函数
    bool GetIntField( CSlkReader *pReader,const char * szColName,int &iValue );
    bool GetStringField(  CSlkReader *pReader,const char * szColName,std::string& pstrRetValue ) ;
    bool GetFloatField( CSlkReader *pReader, const char * szColName, float &fValue );

    //将所有Item放入容器中
    bool AddItemToContainer( ItemDefine::SItemCommon *pItem );

    // 读取Slk配置文件的相关函数
    bool AddItemConfig     ( const char *szFileName );
    bool AddRestoreItem    ( const char *szFileName ); // 恢复药品
    bool AddWeaponItem     ( const char *szFileName ); // 武器
    bool AddArmourItem     ( const char *szFileName ); // 防具
    bool AddSkillItem      ( const char *szFileName ); // 技能
    bool AddStatusItem     ( const char *szFileName ); // 状态
    bool AddActionItem     ( const char *szFileName ); // 基本动作
    bool AddMaterialItem   ( const char *szFileName ); // 原料
    bool AddGemItem        ( const char *szFileName ); // 宝石
    bool AddTaskItem       ( const char *szFileName ); // 任务
    bool AddOtherItem      ( const char *szFileName ); // 其他[ 超链接 ]
    bool AddReelItem       ( const char *szFileName ); // 卷轴
    bool AddTreasureBoxItem( const char *szFileName ); // 宝箱
    bool AddCheckUpItem    ( const char *szFileName ); // 鉴定或者其他的一些物品
	//bool AddRealAwardItem  ( const char *szFileName );
    bool AddGuildBoxItem   ( const char *szFileName );
    bool AddSpecialItem    ( const char *szFileName );
    bool AddTalismanItem   ( const char *szFileName );
	bool AddPetEquipItem   ( const char *szFileName );

    void ReadCanEquipData ( CSlkReader &pReader, ItemDefine::SItemCanEquip* pEquip, const char* szFileName );

    void AddCardItem      ( CSlkReader* pReader, ItemDefine::SItemCommon& common );
    void AddCrystalItem   ( CSlkReader* pReader, ItemDefine::SItemCommon& common );

    //取得技能职业要求
    bool GetProfessionCondition( ItemDefine::SSkillProfessionCondition *pCondition, char *szProfession,char *szLevel );

    //取得技能使用要求
    //bool GetSkillUsedCondition( SSkillUsedCondition *pCondition, char *szSkill, char *szMinUsed,char *szMaxUsed );
    //void GetSkillUsingConditionFromString( SItemSkill *pSkill,char *szStr );
    //void GetSkillUnderstandConditionFromString( SItemSkill *pSkill,char *szStr );

    //装载符石到技能的对应关系
    bool LoadStoneSkill( char *szFile );

    //装载技能片段到技能的对应关系
    bool LoadSkillToSkill( char *szFile );

    //装载制造物品,原料与产品的对应关系
    bool LoadProduceItem( char *szFile );

    //装载公式系数到公式中
    bool LoadFormulamodulus(char *szFile );

protected:
    CItemDetail();
    virtual ~CItemDetail();

public:
	const char* GetString( DWORD dwAddr );

    //加载所有Slk道具配置
    bool LoadSlkItemDetail( const char *szPath,FILE *fpOutput = 0 );

    //装载每升一级自动增加的属性
    bool LoadSlkBaseAttr(char *szFile );
    
    bool LoadSlkMonster( const char *szFile);   // 装载怪物的相关信息
	bool LoadXmlMonster( const char *szFile);   // 从XML中装载怪物的相关信息
	bool SaveXMLMonster( const char *szFile);   // 保存XML怪物的相关信息

    bool LoadSlkPetMonster( const char *szFile);   // 装载宠物的相关信息
    bool LoadXmlPetMonster( const char *szFile);   // 从XML中装载宠物的相关信息
    bool SaveXMLPetMonster( const char *szFile);   // 保存XML宠物的相关信息

    bool LoadSlkMount( const char* szFile );                // 装载坐骑的相关信息
    bool LoadXmlMount( const char* szFileName );            // 从XML装载坐骑相关信息
    bool SaveXmlMount( const char* szFileName );            // 从XML保存坐骑相关信息

    bool LoadSlkCreatureSound( const char* szFile );        // 转载生物的声音相关信息
    bool LoadXmlCreatureSound( const char* szFileName );    //从XML中装载怪物的声音信息
    bool SaveXmlCreatureSound( const char* szFileName );    //向XML中保存怪物的声音信息

    //获取Item的相关函数
    ItemDefine::SItemCommon* GetItemByName(const char*szItemName );
    ItemDefine::SItemCommon* GetItemByNameAndLevel( char*szItemName, int nLevel );
    ItemDefine::SItemCommon* GetItemByID( unsigned short ustItemID );
    ItemDefine::SItemCommon* GetItem( unsigned short ustItemID,int iItemType );
	
    //取得对应道具的类型
    uint8 GetItemType( unsigned short ustItemID);
    bool  IsEquipItem( unsigned short ustItemID);

    // 取得对应套装map
    std::vector<ItemDefine::SItemCanEquip*>* GetSuitsByID( short stSuitID );

    //获取Item划分后的相关数据
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

    // 所有原料
    const std::vector<ItemDefine::SItemCommon*>&  GetMaterialItemList() const { return m_vecMaterialItem; }
    // 所有宝石
    const std::vector<ItemDefine::SItemCommon*>&  GetGemItemList() const { return m_vecGemItem; }
	const std::vector<ItemDefine::SItemCommon*>& GetRestoreItemList() const { return m_vecRestoreItem;}
    //获取技能的相关信息
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

    //获取状态的相关信息
    ItemDefine::SItemStatus* GetStatusBySkill   ( const ItemDefine::SItemSkill *pSkill );
    ItemDefine::SItemStatus* GetMeStatusBySkill ( const ItemDefine::SItemSkill *pSkill, uint8 index  );
    ItemDefine::SItemStatus* GetDstStatusBySkill( const ItemDefine::SItemSkill *pSkill );
    ItemDefine::SItemStatus* GetStatus( unsigned short ustStatusItemID, unsigned short ustStatusLevel );

    //获取怪物的相关数据
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

    //获取宠物的相关数据
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

    //获取坐骑的相关数据
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

    uint32   IsCanSplitItem( uint16 itemId ); // 是否可以分解物品

    //装载武器随机生成的属性
    bool     LoadSlkRand( const char* szFileName ); // EquipmentRandom.slk
    bool     LoadXmlRand( const char* szFileName ); // 从XML中加载武器随机属性
    bool     SaveXmlRand( const char* szFileName ); // 向XML中保存武器随机属性 EquipmentRandom.config
	bool     LoadXmlEquipQualityIntensity( const char* szFileName ); // 从XML中加载装备品质强度系数
	bool     SaveXmlEquipQualityIntensity( const char* szFileName ); // 向XML中保存装备品质强度系数 EquipQualityIntensity.config


    ItemDefine::SRandAttribute* GetRandByID(unsigned short id);
	float GetEquipQualityIntensity(uint8 nQuality);
	float GetEquipRandAttrValue( float fRandValue, uint8 nQuality );

    bool            HaveSameRandType(unsigned short usRandID1, unsigned short usRandID2);
    long            GetRandByLevel( short level, OUT RandContainer& result );
	long            GetRandByLevel( short level, OUT RandAttrContainer& result );

    void            SetRandValueLevelType(float value, short level, unsigned short type);             // 获取等级和类型对应的最大值
    float           GetMaxValueByRandLevelType( short level, unsigned short type );

    ItemDefine::SUpBaseAttr* GetBaseAttrByLevel(short sLevel);


    void GetCreatItemModByLevel(unsigned short ustLevel,std::vector<ItemDefine::SCreatItemMod*> &pvtCreatItemMod);
    ItemDefine::SCreatItemMod *GetCreatMod(unsigned short ustLevel,short stSize,bool bWeapon,bool bArmour,short stType);

    ItemDefine::sIcon* GetIconFileByID(unsigned short ustId);

    //随机取得一个等级范围的道具
    unsigned short GetRandomLevelRangeItem(int iMinLevel, int iMaxLevel);

    bool LoadSlkTraffic( const char* szFileName );          //装载交通的相关信息
    bool LoadSlkProfession( char *szFile );                 //装载职业的相关信息
    bool LoadSlkCharModulus( char *szFile );                //装载角色系数的相关信息
    bool LoadSlkNewCreatItem(char *szFile);
    bool LoadSlkIcon(char* szFile);

    //获取职业的相关信息
    ItemDefine::SProfession *GetProfession( int iIndex );
    int         GetProfessionNum( void );
    int         GetProfessionID( char *szName );
    ItemDefine::SProfession *GetProfession( char *szName );

    //获取物品制造,原料与产品的对应关系
    ItemDefine::SProduceItem* GetProduceItem( int iIndex );
    int           GetProduceItemSize( );

    //获取技能的描述信息
    int CreateSkillDesc( unsigned short ustSkillID, unsigned short ustSkillLevel, 
        char (*pDesc)[256], DWORD *pDescColor, int iDescLength );
    //获取状态的描述信息
    int CreateStatusDesc( unsigned short ustStatusID, unsigned short ustStatusLevel,
        char (*pDesc)[256], DWORD *pDescColor, int iDescLength );

    //获取交通的相关数据
    int FindTrafficIndexByName( char *szName );
    ItemDefine::STraffic *GetTraffic( int nIndex );
    ItemDefine::STraffic *GetTrafficByID( int nID );
    ItemDefine::STraffic *GetTrafficByName( char *szName );

    inline size_t GetTrafficNumber() const 
    { 
        return m_vecTraffic.size(); 
    }

    //荣誉 ？
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
    OutputSlkLoadingMessage( "\tError: %s 读取[%s]失败\r\n", name, szFileName  ); \
} \
    else \
{\
    target = iValue;\
}

#define SLK_GET_STRING( target, name ) \
    strValue = "";\
    if( !pReader.GetStringFieldByName( name, strValue ) ) \
{ \
    OutputSlkLoadingMessage( "\tError: %s 读取[%s]失败\r\n", name, szFileName  ); \
} \
    else \
{\
    target = strValue;\
}

#define SLK_GET_FLOAT( target, name ) \
    fValue = 0.0f;\
    if( !pReader.GetFloatFieldByName( name, fValue ) ) \
{ \
    OutputSlkLoadingMessage( "\tError:%s 读取[%s]失败\r\n", name, szFileName ); \
} \
    else \
{\
    target = fValue;\
}

#define CopyCommon( pItemDest,common ) *(ItemDefine::SItemCommon*)pItemDest = common;
//////////////////////////////////////////////////////////////////

#endif // __COMMON_ITEMDETAIL_H__
