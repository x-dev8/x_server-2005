/********************************************************************
    Filename:    GameStage.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/
#ifndef __GAMESTAGE_H__
#define __GAMESTAGE_H__

#include "MeRTLibsServer.h"
#include "GameArea.h"
#include "GameZone.h"
#include "MonsterProducer.h"
#include "Mutex.h"
#include "WorkThread.h"
#include "MapConfig.h"
#include "StageDefine.h"
#include "GameTimer.h"
#include "GameDataType.h"
#include "SwMap.h"

class BaseCharacter;
class GamePlayer;

class GameStage
{ 
public:
	enum eEctypeKickType
	{
		eEctypeKickType_no = 0, //����
		eEctypeKickType_noTeam = 1,//��Ӹ������޶���
		eEctypeKickType_release = 2,//��������
		eEctypeKickType_noguild = 3,//���ḱ����û�й�����
	};
public:
    static void RunThread( void* p );

    // ��������
    template< class T > 
    static GameStage* CreateStage() { return CNewWithDebug< T >::Alloc( 1, "����GameStageʵ��" ); }

    // �ͷų���
    template< class T > 
    void ReleaseStage( T* pStage ) { CNewWithDebug< T >::Free( pStage ); }
    virtual void Release() = 0;

    GameStage();
    virtual ~GameStage();

    // ִ�и���
    virtual void RunUpdate();    // 1ˢ�� 2���� 3pChar->Run 4�����

    // ��ʼ������
    virtual bool Initialize( MapConfig::MapData* pMapData, uint32 nStageID, uint32 nMapLevel );

    // �ж��Ƿ�Ҫ����
    virtual void CheckStageValid() = 0;

    // ���ó�������
    virtual void SetStageWaitRelease( bool bRelease ,bool bNow = false) = 0;

    // �Ƿ�ȴ�����
    virtual bool IsStageWaitingRelease() = 0;

    // �Ƿ�Ҫ����
    virtual bool IsStageRelease() = 0;

    // ����Ƿ�Ҫ�޳����
    virtual void CheckKickOutPlayer( BaseCharacter* pChar ) = 0;

    virtual int GetStageLevel() { return 0; }

    // ��ͼ��������
    void SetMapData( MapConfig::MapData* pMapData) { m_pMapData = pMapData; }
    MapConfig::MapData* GetMapData() { return m_pMapData; }

    // ����ID
    uint32 GetStageID(){ return m_nStageID; }
    void SetStageID( uint32 nValue ) { m_nStageID = nValue; }

    // ��������
    int GetStageType() { return m_pMapData->GetMapType(); }

    // �Ƿ��Ǹ�������
    bool IsEctypeStage() { return m_pMapData->IsEctypeMap(); }

    // ��ͼ���
    int GetWidth() { return m_nMapWidth;}
    void SetWidth( int nValue ) { m_nMapWidth = nValue; }

    // ��ͼ����
    int GetHeight() { return m_nMapHeight; }
    void SetHeight( int nValue ) { m_nMapHeight = nValue; }

    // ���ô����
    void SetStoreName( const char *szValue ) { strncpy_s( m_szStageStoreName, sizeof( m_szStageStoreName ), szValue, sizeof( m_szStageStoreName ) - 1 ); }     
    const char* GetStoreName() const { return m_szStageStoreName; }

    // �ض��غϳ���Ӧ���ļ���
    void MakeFileName( char *dst, char *szRootDir, char *TailString, size_t dstsize );

    // ���ĳ������ָ��
    GameArea* GetArea( uint32 nArea );
    
    // ���ĳ��Zoneָ��
    GameZone* GetZone( uint32 nID ); 

    // ����������Ϣ
    void CalcAreaInfo();                  

    // ������������
    int TestAreaNumber( int x, int y );  

    // ��ȡ��ͼ���� �ֿ��ͼ���ض�ȡ
    bool LoadStage( const char* szRootDir, uint32 mapId, int nStageWidth, int nStageHeight, int nMapLevel = 0 );    

    // ��ȡ��ͼ���� һ���ͼ���ض�ȡ
    bool LoadStage( const char* szRootDir, uint32 mapId, int nMapLevel = 0 ); 
   
    // ��ý�ɫ�б�
    GameObjectIdTPL(dr_stageMaxCharacters)& GetCharacterTable() { return m_xCharacterTable; }

    // ��õ�ǰ��ɫ����
    int GetCharacterCount() { return m_xCharacterTable.Count(); } 

    // ��ý�ɫID
    GameObjectId GetCharacterID( uint32 nIndex ); 

    // ɾ����ɫ
    bool DelCharacterID( GameObjectId nID, int index = -1 );

    // ���9���ڵĽ�ɫID��
    void Get9AreaList( AreaIndexTPL(Area9)& IdList, int nArea );
    void GetCharIdTable( GameObjectIdTPL( dr_stageMaxCharacters ) &IdList, int nArea );

    // ��ɫ����
    bool CharacterEnter( BaseCharacter* pChar, const char* szFile, uint32 line ); 

    // ��ɫ�뿪
    bool CharacterLeave( BaseCharacter* pChar );        

    // ������Ұ��Χ�������˵���Ϣ�����˵�������
    bool SendAllInfoToCharBy9AreaEnter( BaseCharacter* pChar ); 

    // ������Ұ��Χ�������˵���Ϣ�����˵����뿪
    bool SendAllInfoToCharBy9AreaLeave( BaseCharacter* pChar ); 

    // �Դ���������м��
    bool CheckZone(); 

    // ˢ�µ�ǰ��������  
    bool RefreshNewArea( BaseCharacter* pChar );            

    // ˢ����ҵ�ǰ�ܿ����������(������9�����ڵ����)
    int RefreshPlayerCharNumberInView( BaseCharacter* pChar );        

    // ���ϼ������������
    void ComplexComputeArea( AreaIndexTPL(Area9) &pOld, AreaIndexTPL(Area9) &pNew, AreaIndexTPL(Area9) &ppNewRes, AreaIndexTPL(Area9) &ppDelRes );    

    // �������߳�
    bool StartRunThread();

    // �رն��߳�
    bool StopRunThread();

    // ��ȡ���������ļ� �ֿ��ͼ���ض�ȡ
    bool LoadMonsterConfig( uint32 mapId , const char* szFilePath, int nLandX, int nLandY, int nMapLevel = 0 ); 

    // ��ȡ���������ļ� һ���ͼ���ض�ȡ 
    bool LoadMonsterConfig( uint32 mapId , const char* szFilePath, int nMapLevel = 0 );   

    // �������߳�ˢ��
    //bool StartRefreshMonsterThread();

    // �رն��߳�ˢ��
    //bool StopRefreshMonsterThread();
    //static void RefreshMonsterThread( void* pStage );

    CMonsterProducer& GetMonsterProducer() { return m_xMonsterProducer; }

    // ˢ��
    void RefreshMonster( unsigned int nRefreshCount = 30 );           
    
    // ˢ���ع�
    void RefreshHideMonster( int x, int y, const char* pZoneName ); 

    // ���ù�������
    void SetMonsterDead( uint32 nIndex );

    // GameStageҲ�ܹ���������(Ϊ���ö��߳�ˢ�־������漰����)
    //BaseCharacter* CreateMonsterBuild( uint32 monsterId, float fx, float fy, float fdirx, float fdiry, uint8 campId );

    // ��������
    //BaseCharacter* CreateMonster( CMonsterProducer::TagMonsterData* pMonsterInfo, float nX, float nY, float fDirX, float fDirY, int iProductIndex, BOOL bStartUpAI = FALSE, DWORD dwSpecialID = 0, int nInfluence = 0 );

    // luaˢ��
    //void LuaSummonMonster( float x, float y, float dx, float dy, int32 monsterId, uint16 monsterNum, float fRadius, uint8 nSummonType, int nInfluence, uint16 routeId, bool bBornInRouteBegin );
    
    // �������ҹ�
    //void GameStage::CreateCountryMonster(uint32 countryId, uint32 monsterId, uint32 monsterNum, uint32 mapId, float fx, float fy, float fdirx, float fdiry, float fRadius, float fBodySize, GameObjectId summonId );
   
    // �Ƿ������Ѿ���
    bool IsCaracterFull(); 

    // �����Ƿ��ڳ�����
    bool IsInStage( float x, float y, float z );

    // tile�Ƿ��ڳ�����
    bool IsInStageTile( int tileX, int tileY, int tileZ );

    // �ж��Ƿ�������ߵ��õ�
    static bool MapMoveable( short x,short y ); // �ص�����
    bool Moveable( BaseCharacter *pChar,short x,short y );
    bool StagePosHasNoOne( short stX, short stY );

    //+1,-1ռλ
    bool IncPosMask( short x,short y );
    void DecPosMask( short x,short y );

    // ������һ�������еĽ�ɫ�б�
    int GetCharacterInRect( RECT&rc, short* pstIDBuf, int iMaxShortNum );  

    // ����Բ�����������н�ɫ�б�
    int GetAllCharInCircle( BaseCharacter* pSrcChar, D3DXVECTOR3 vPos, std::vector<int32>& vecCharID, int nCharType );
    int GetAllCharInCircle( float fRadius, D3DXVECTOR3 vPos, std::vector<int32>& vecCharID, int nCharType );

    // ������һ��Բ�������ڵĽ�ɫ�б�
    int GetCharacterInCircle( D3DXVECTOR3 vPos, float fRadius, GameObjectId* pnIDBuf, int nMaxNum ); 

    // ������һ��Բ�������ڵĹ����б�
    int GetMonsterInCircle( D3DXVECTOR3 vPos, float fRadius, GameObjectIdContainer& objects, int nMaxNum, bool bNeedCheckCanAttack = false, BaseCharacter* pSrcChar = NULL ); 

    // ����ĳ������ĳ�������ܹ�����Ŀ��
    int GetTargetInCircle( BaseCharacter* pSrcChar, D3DXVECTOR3 vPos, const ItemDefine::SItemSkill* pSkill, GameObjectId* pnIDBuf, int nMaxNum );  
    int GetTargetInCircle( BaseCharacter* pSrcChar, const ItemDefine::SItemSkill* pSkill, GameObjectId *pnIDBuf, int nMaxNum, float fAngle, BOOL bFront );

    // �����ڽ�ɫ��ǰһ��90�ȵ����������ڵĽ�ɫ�б�
    int GetCharacterInQuarterCirlce( BaseCharacter* pSrcChar, float fRadius, GameObjectId *pnIDBuf, int nMaxNum );

    // ���ҽ�ɫ�뾶�����н�ɫ�б�
    int GetCharacterInCircle( BaseCharacter* pSrcChar, float fRadius, GameObjectId *pnIDBuf, int nMaxNum, float fAngle, BOOL bFront );

    // ������������ļ�������
    void SetVarInTaskArea( BaseCharacter* pSrcChar, int nVarId, int nValue, int nRadius, int nType );  

    // ��Ҹ�����Ϣ
    virtual void RecordPlayerDeath ( GamePlayer* pPlayer ) {};
    virtual uint16 GetPlayerDeathCount( GamePlayer* pPlayer ){ return 0; }

    // ����Ƿ��ܽ���
    virtual bool CheckCanEnterStage( GamePlayer* pPlayer ) = 0;

    //Ѱ·����� ���߳���ʹ�� �����赲��
    void	SetParthFinder( SwMap* pParthFinder );
    SwMap*	GetParthFinder()	{ return m_pParthFinder; }

	//Ѱ·����� Ѱ·�߳���ʹ��
    void	SetThreadParthFinder( SwMap* pParthFinder );
    SwMap*	GetThreadParthFinder()	{ return m_pThreadParthFinder; }

	//�ͷű����������е�Character
	void ReleaseAllCharacter();

protected:
    typedef std::map< int, GameObjectId > CharacterMap;
    typedef CharacterMap::iterator        CharacterMapIter;

    typedef std::set< GameObjectId > PlayerList;
    typedef PlayerList::iterator     PlayerListIter; 

    virtual bool ProcessEnterStage( GamePlayer* pPlayer ) = 0;
    virtual void ProcessLeaveStage( GamePlayer* pPlayer ) = 0;

protected:
    // ��ͼ��������
    MapConfig::MapData* m_pMapData;

    //Ѱ·��,Ѱ·�߳���ʹ��
    SwMap* m_pParthFinder;
    //���߳���ʹ�õ�Ѱ·��
    SwMap* m_pThreadParthFinder;

    // ����ID
    uint32 m_nStageID;

    // ʵ�ʵ�ͼ�� ��λ��2.56 Tile
    int m_nMapWidth;

    // ʵ�ʵ�ͼ��
    int m_nMapHeight; 

    // ���������
    GameZone* m_cgzZone[ StageDefine::constMaxZones ]; 

    // �Զ�����������
    GameArea* m_cgaArea[ StageDefine::constMaxAreas ]; 

    // ʵ�ʵ�zones���� = m_nZoneNumber - ��ȡʧ�ܵ�Zone��
    int m_iZoneCount; 

    // �������
    int m_iAreaCount;

    // �����еĳ���,����ͼ���Ŷ��ٸ����� 12 * Tile ��λ
    int m_iAreaLength; 

    // �����еĳ���,����ͼ���Ŷ��ٸ�����
    int m_iAreaHeight; 

    // ����AI����
    RECT m_rcAIArea[ StageDefine::constMaxZones ];   

    // ���������
    char m_szStageStoreName[ StageDefine::constStoreNameMaxSize ]; 
    
    // ˢ������
    CMonsterProducer m_xMonsterProducer;

    // ˢ���߳� һ���̹߳���
    // CWorkThread m_RefreshMonsterThread;

    // �����߳�
    CWorkThread m_RunThread;

    // ������Ϸ��ɫID��[player character, monster, pet ��]
    GameObjectIdTPL( dr_stageMaxCharacters ) m_xCharacterTable; 

    // �ϴθ���ʱ��
    uint32 m_dwLastProcessTime;

    // CheckZone��ʱ��ӡʱ��
    GameTimerEx _errorCallTime; 

    // ����������б�
    PlayerList m_setPlayer;
};

////////////////////////////////////////////////////////////////////////////////////////////
//inline
inline GameArea* GameStage::GetArea( uint32 nArea )
{
    if( nArea >= StageDefine::constMaxAreas )
    { return NULL; }

    return m_cgaArea[ nArea ]; 
}

inline GameZone* GameStage::GetZone( uint32 nID )  
{ 
    if( nID >= StageDefine::constMaxZones )
    { return NULL; }

    return m_cgzZone[nID]; 
}

inline bool GameStage::IsInStage( float fx, float fy, float fz )
{
    if ( fx < 0 || fy < 0 || fx >= TileToFloat( GetWidth() ) || fy >= TileToFloat( GetHeight() ) )
    { return false; }

    return true;
}

inline bool GameStage::IsInStageTile( int tileX, int tileY, int tileZ )
{
    if ( tileX < 0 || tileX >= GetWidth() || tileY < 0 || tileY >= GetHeight() )
    { return false; }

    return true;
}

inline GameObjectId GameStage::GetCharacterID( uint32 nIndex )
{
    if ( GetCharacterCount() == 0 )
    { return InvalidGameObjectId; }

    if ( nIndex >= dr_stageMaxCharacters )
    { return InvalidGameObjectId; }

    return m_xCharacterTable[nIndex];
}

inline bool GameStage::DelCharacterID( GameObjectId nID, int index /*= -1*/ )
{
    m_setPlayer.erase( nID );

    if ( index == -1 )
    { return m_xCharacterTable.Del( nID ); }
    else
    { // ����Indexɾ 
        bool bResult = m_xCharacterTable.Del( index, false ); // û��ɾ������Ҫɾ��һ��
        if ( bResult )
        { return bResult; }
        
        return m_xCharacterTable.Del( nID );
    }
}

#endif

