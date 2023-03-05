/********************************************************************
    Filename:    GameWorld.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __GAMESERVER_GAMEWORLD_H__
#define __GAMESERVER_GAMEWORLD_H__

#include "MapConfig.h"
#include "NormalStage.h"
#include "EctypeStage.h"
#include "Mutex.h"
#include "DropItem.h"
#include "NpcInfo.h"
#include "CountryConfig.h"
#include "MonsterProtectedEx.h"
#include "MonsterPetTrap.h"
#include "MonsterBuildEx.h"
#include "MonsterNurturePet.h"

extern SProcessTime gwusetime[200];

class CEffectChar;
class ItemCharacter;

#define theGameWorld GettheWorld()

class GameWorld
{ // ��Ϸ������
public:
    enum EConstDefine
    {
        constMaxCharacters     = dr_worldMaxCharacters,   // ����ɫ��
        //constMaxStages       = dr_worldMaxStages,       // ���������
        constRefreshStagesRate = dr_refreshstagezonerate, // ˢ�´��������Ƶ��
    };

    enum EExternMessage
    { // ��Ϣ����
        ExtMsg_AddCharacter  , // �����ɫ
        ExtMsg_DelCharacter  , // ɾ����ɫ
        ExtMsg_RefreshCurArea, // ˢ�µ�ǰ��������
        ExtMsg_ChangeMapTest , // �����л����
        ExtMsg_FlashMoveTo   , // ��ɫ˲���ƶ���
        ExtMsg_EnterStage    , // ��ɫ���볡��
        ExtMsg_LeaveStage    , // ��ɫ�뿪����
    };

    struct SFlashMoveTo
    {
        DWORD dwMapID;
        short x,y;
        float fDir;
    };
   
    struct SSafePos
    { // ��Ϸ�еİ�ȫλ�ã�λ�ó���ʱ������ɫ�͵����λ��
        DWORD dwMapID;
        short x,y;
    };

    struct SLoadMapInfo
    {
        GameWorld* pGameWorld;
        DWORD dwMapId;
        DWORD dwEctypeId;
        unsigned short ustLevel;
        DWORD dwStartTime;
        DWORD dwReserveValue;
		GS2CSCreateMulitStageAck	mca;
		bool sendtocenter;
    };

	//���̴߳�����ͼ��Ҫͬ������Ϣ
	typedef std::vector< GameObjectId > vecSSynStageInfoNpc;
	typedef vecSSynStageInfoNpc::iterator SynStageNpcIter;
	struct SSynStageInfo
	{
		SSynStageInfo()
		{
			pStage = NULL;
			_vecSynStageNpc.clear();
			memset(&mca,0,sizeof(mca));
			sendtocenter = false;
		}

		GameStage*					pStage;
		vecSSynStageInfoNpc			_vecSynStageNpc;
		GS2CSCreateMulitStageAck	mca;
		bool						sendtocenter;
		DWORD						dwStartTime;
		DWORD						dwReserveValue;
	};

public:
    GameWorld();
    virtual ~GameWorld();
    
    bool           Process();         // ������
    bool           GlobalMessage( EExternMessage msg, WPARAM wParam = NULL, LPARAM lParam = NULL ); // ��Ϣ�ӿں���
    bool           InitStages();      // ��ʼ����ͼ
	
	// �������� ���߳�/���߳� 
    GameStage*     SingleCreateStage( uint32 dwMapId, uint32 dwEctypeId );	
    GameStage*     MultiCreateStage( uint32 dwMapId, uint32 dwEctypeId, uint16 ustLevel = 0, uint32 dwReserveValue = 0,GS2CSCreateMulitStageAck* pMsg = NULL);
    
	bool           ReleaseTheStage( uint32 dwEctypeId );// ���� �ͷ�  ��ͼ
    void           TermStages();      // ȫ�� �ͷ�  ��ͼ

    static void    AutoSave(void* p); // �Զ�����ϵͳ��ɫ���� ȫ��ʱ���㷨
    static void    AutoSaveUpdate();  // �Զ�����ϵͳ��ɫ���� ������ɫʱ���㷨

	//���� ����/���� ���㸱��id
    DWORD          MakeEctypeStageID( MapConfig::MapData* pMapData, BaseCharacter* pChar, int nMapLevel = 0 );
	DWORD		   MakeEctypeStageIDByTeamID(MapConfig::MapData* pMapData,unsigned int TeamID);

    GameStage*     FindMultiTeamStage( MapConfig::MapData* pMapData, DWORD dwTeamSessionID );//���Ҷ��鸱��
    GameStage*     FindMultiGuildStage( MapConfig::MapData* pMapData, DWORD dwGuildID );	 //���ҹ��ḱ��

    GameStage*     GetStageById( DWORD dwMapID ); // ���ָ���ĳ���
    
    GameStage*     GetActiveStageInWorld();	//����Ϊʲô��������ӿ�...��õ�һ������.

	int            GetStageCount(){ return (int)m_mapGameStage.size(); }//������и���������
	DWORD          GetMapCount( DWORD dwMapId );			//���ĳ��id��ͼ������

	// ���ĳ����ͼ����������ʱid������
	void           GetCurMapStage( DWORD ustMapID, std::vector< GameStage* >& vecStage );
	bool           GetCurMapStage( DWORD dwMapId,  std::vector<DWORD>& vtEctypeId );

	unsigned long  GetEctypeMapLastId( unsigned long uEctypeMapDataId , bool bIncreaseAfterGet = false );
	unsigned long  GetEctypeMapID( unsigned long uEctypeMapDataId , bool bIncreaseAfterGet = false );

	int            GetCreateLoadMapCount( DWORD dwMapID );		//����m_vecCreateMapInfo������
	//std::string    GetMonsterDataFilePath( const std::string& stageName );
	
	size_t		   GetObjectSize()		 { return _objectIds.size(); }// �õ�Object��Size
	size_t		   GetPlayerObjectSize() { return _playerIds.size(); }// �õ�Player��Size

    // // �������в�������.
    //BaseCharacter* SummonMonster( int nMapID, float fPosX, float fPosY, float fDirX, float fDirY, float fBodySize, int nMonsterId, int nMonsterNumber, float fRadius, int nSummonType, DWORD dwSpecialID = 0, int nInfluence = 0); // �ٻ�����   
    //BaseCharacter* CreateMonster( CMonsterProducer::TagMonsterData *pMonsterInfo, int nMapID, float nX, float nY, float fDirX, float fDirY, int iProductIndex, DWORD dwSpecialID = 0, int nInfluence = 0, BOOL bStartUpAI = FALSE );

    //// �ٻ�������
    //MonsterBuildEx*  CreateMonsterBuild( uint32 monsterId, uint32 mapId, float fx, float fy, float fdirx, float fdiry, uint8 campId );

    //// �ٻ�·����
    //MonsterRoute*  CreateMonsterRoute( uint32 monsterId, uint32 mapId, float fx, float fy, float fdirx, float fdiry, uint16 routeId, uint8 campId, bool bBornInRouteBegin, float xoff, float yoff );
    //
    //// �ٻ�������
    //MonsterProtected* CreateMonsterProtected( uint32 monsterId, uint32 mapId, float fx, float fy, float fdirx, float fdiry, GameObjectId summonId );

    //// �ٻ�����
    //MonsterTrap*   CreateMonsterTrap( uint32 monsterId, uint32 mapId, float fx, float fy, float fdirx, float fdiry, GameObjectId summonId );

    //// �������в����ٻ����� (������ʱ���ڵĹ�����ֹ�����ص��ǣ� // 1������������ 2���и��� )
    //BaseCharacter* CreateSummonPet( CMonsterProducer::TagMonsterData *pMonsterInfo, int nMapID, float fx, float fy, float fdirx, float fdiry, int iProductIndex, GameObjectId shID = -1, int nInfluence  = 0, int nSummonSkillID = -1 );

    // ��������
    //MonsterNurturePet* CreateNurturePet( CMonsterProducer::TagMonsterData *pMonsterInfo, int nMapID, float fx, float fy, float fdirx, float fdiry, int iProductIndex, GameObjectId iMasterID, SPetItem* pPetData );

    // �ٻ�����
    //bool           CreateIllusion( CMonsterProducer::TagMonsterData pIllusionInfo, float fPosX, float fPosY, float fDirX, float fDirY, GameObjectId RealityID, GameObjectId& IllusionID ); //GameStage������Ӱ����    

    ItemCharacter* CreateItemNpc( const char *szItem, int nMapID, float fX, float fY, int nDir,  SCharItem &item, short stMasterNpc, unsigned char ucBornDelay, bool bTilePos = true );

    ItemCharacter* CreateItemPackageNpc( uint16 stItemID, unsigned long nMapID, float fX, float fY, int nDir, DropItemVector& vecDropItem, DropCharItemVector& vecCharItem, unsigned long dwTeamSeesionID, unsigned long dwPlayerID, SCharItem &item, unsigned char ucBornDelay);

    CEffectChar*   CreateEffectChar( BaseCharacter *pCharCaster,const char *szName ,int nMapID ,int iSkillID, int iSkillLevel, float nX, float nY);

    //bool           CreateNpcsHero( GameStage* pStage );
    //bool           CreateNpcHero( GameStage* pStage, NpcInfo::Npc* pNpcInfo, bool bConfigNpcInfoPointer, DWORD OnlineTime = -1);

    GameStage*     GetCharPosInWorld( BaseCharacter* pChar, DWORD& dwMapId, int& nX, int& nY, bool bCreate = false );

	bool           OnAddCharacter( GameObjectId dwID, const char* szFile, uint32 line );       // �����ɫ
    bool           OnAddCharacterOnlyID(GameObjectId dwID);   // רΪˢ�ֶ�׼���ļ����ɫ��ֻ��ID�����Character�б�����ʲô������
    bool           OnDelCharacter( GameObjectId dwID );       // ɾ����ɫ
    bool           OnDelCharacterOnlyID(GameObjectId dwID);   // רΪˢ�ֶ�׼���ļ����ɫ��ֻ��ID��Character�б�����ʲô������
    //bool         OnDelNpc( DWORD dwID );					 // רΪɾ���ű�NPC 

    bool           OnRefreshNewArea( GameObjectId dwID );    // ˢ�µ�ǰ��������
    bool           OnLeaveStage    ( GameObjectId dwID );    // ��ɫ�뿪����
    bool           OnEnterStage    ( GameObjectId dwID );    // ��ɫ���볡��
    int            OnRefreshPlayerCharNumberInView( GameObjectId dwID ); // ˢ����ҵ�ǰ�ܿ����������(������9�����ڵ����)

	//void           DebugShowCharListInfo(bool bRefreshNow); // ��ʾ�����Ϣ
    
    bool           KickCharByAccount( DWORD dwAccount );	        // �����˺�id�������н�ɫ������,Ч���е��
    void           MoveRoleToSafePosAndExit( BaseCharacter *pChar );// ������Ƶ���ȫ��Ȼ�������� 
    void           ProcessGameStageOp();							// _gameStageOp�����������ô�����ݶ�û�и���,�͸�center������һ��
    //void           ProcGMCommand(const char* szCommand);			// GM������ص�.���ã�ȫ����center
    

    // �����õ�Id
    GameObjectId GetNextObjectBId( bool bFirst );

    void DeleteGameStage( int nMapID );

    // ��ɫ������ר��
    void SetExtendrnMapOpen( bool bValue );
    const CountryConfig::BornMapSetting* GetPlayerBornMap( int nCountry );

protected:
    //static void RefreshMonster(void* p = NULL);     // �����µù���
    static void LoadMapThread( void *pLoadMapInfo );  // ��̬�����������߳�

	GameStage*  CreateStage( uint32 dwMapId, uint32 dwEctypeId, uint16 ustLevel = 0, uint32 dwReserveValue = 0 );
	GameStage* 	CreateNormalStage( MapConfig::MapData* pMapData, uint32 dwEctypeId );
	GameStage* 	CreateEctypeStage( MapConfig::MapData* pMapData, uint32 dwEctypeId, uint16 ustLevel = 0, uint32 dwReserveValue = 0 );
	GameStage*  AsynCreateStage( uint32 dwMapId, uint32 dwEctypeId, uint16 ustLevel = 0, uint32 dwReserveValue = 0 ,GS2CSCreateMulitStageAck* pMsg = NULL);
	GameStage* 	AsynCreateEctypeStage( MapConfig::MapData* pMapData, uint32 dwEctypeId, uint16 ustLevel = 0, uint32 dwReserveValue = 0 /*,GS2CSCreateMulitStageAck* pMsg = NULL*/);

    void        MapMonitorRender();
    bool        OnFlashMoveTo( GameObjectId dwID, DWORD dwMapID, short nTileX, short nTileY, float fDir );
    bool        AddGameStage( GameStage* pStage );
    
    bool        CheckStageLoad();
    void        InitEctypeMapId( unsigned long uEctypeMapDataId );
    void        TryLoadAllScript();

    
	bool       CheckAsynStageInfo();
	void       CleanAsynStageInfo(SSynStageInfo* pSyn);
public:
    bool  m_guildsorted;
    DWORD g_dwLastWorldProcessTime;

    static bool bShowRunProcessInfo;
    static bool bShowMemoryInfo;
	static bool bCloseGate;

private:
    typedef std::map<uint32,GameStage*>  GameStageContainer;
    typedef GameStageContainer::iterator ItrGameStageContainer;

    typedef std::vector< SLoadMapInfo > CreateMapVector;
    typedef CreateMapVector::iterator CreateMapVectorIter;

	typedef std::vector< SSynStageInfo* > SSynStageInfoVector;
	typedef SSynStageInfoVector::iterator SSynStageInfoVectorIter;

    GameStageContainer  m_mapGameStage;          // �������
    CreateMapVector     m_vecCreateMapInfo;		 // ���10�����ڴ����Ķ�̬����
	SSynStageInfoVector m_vecSSynStageInfo;		 // ���̴߳�����Ҫͬ������Ϣ

    GameObjectIDSet     _objectIds  ; // player Npc Monster Item ��
    GameObjectIDSet     _playerIds  ; // player 
    GameObjectIDSetItr  _objectIdItr; // ���

    int                 m_NowSaveCharaStage;     // ������Ҫ����ģ���ͼ
    int                 m_NowSaveCharStageIndex; // ������Ҫ���棬��npc���
    DWORD               m_PreSaveTime;           // �ϴα����ʱ��
    DWORD               m_dwCpuHz;               // ��¼CPUƵ��
    SSafePos            m_safepos;

    // ���� CenterServer �ҵ����߻�û������CenterServerʱ�� GameServer���¸����Ĳ���
    typedef std::vector<SGameStageOp> GameStageOpContainer;
    typedef GameStageOpContainer::iterator ItrGameStageOpContainer;
    GameStageOpContainer _gameStageOp;

    typedef std::map< unsigned short, unsigned long > MapIdMakeContainer;
    typedef MapIdMakeContainer::iterator              ItrMapIdMakeContainer;
    MapIdMakeContainer _MapIdMake;
    GameTimerEx _reloadScriptTimeRecord;  // ���ؽű�ʱ���¼

    // �Ƿ�򿪶�������ֳ�����
    bool m_bExtendBornMapOpen;

    // ��¼��������ĳ�����������Ϣ
    typedef std::map< unsigned int, unsigned int > CountryBornMap;
    typedef CountryBornMap::iterator CountryBornMapIter;

    CountryBornMap m_mapCountryBorn;
};

GameWorld& GettheWorld();

#endif // __GAMESERVER_GAMEWORLD_H__
