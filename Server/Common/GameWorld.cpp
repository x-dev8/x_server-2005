#include "GameWorld.h"
#include "ShareData.h"
#include "InfoText.h"
#include "GameTime.h"
#include "NpcBaseEx.h"
#include "ItemCharacter.h"
#include "Configure.h"
#include "EffectChar.h"
#include "GameStage.h"
#include "WordParser.h"
#include "FuncPerformanceLog.h"
#include "MonsterProducer.h"
#include "ScriptMgr.h"
#include "ShopMgr.h"
#include "GameWorldTimer.h"
#include "DropItemManager.h"
#include "ScriptVarMgr.h"
#include "DataChunkMgr.h"
#include "DBChunk.h"
#include "StageMonitor.h"
#include "GlobalDef.h"
#include "RunStatus.h"
#include "Helper.h"
#include "FileDB.h"
#include "Mutex.h"
#include "WaitReleaseStage.h"
#include "XmlStringLanguage.h"
#include "ResourcePath.h"
#include "TeamManager.h"
#include "NpcInfo.h"
#include "GameStageDataCenter.h"
#include "LuckRewardManager.h"
#include "RabotManager.h"
#include "Configure.h"
#include "BattleManager.h"
#include "BargainingManager.h"
#include "CampBattleControl.h"
#include "SinglePlayerStage.h"
#include "SingleTeamStage.h"
#include "SingleGuildStage.h"
#include "MultiPlayerStage.h"
#include "MultiTeamStage.h"
#include "MultiGuildStage.h"
#include "GameParthFinder.h"
#include "PetBreedManager.h"
#include "GameBlockMap.h"
#include "PetSettingConfig.h"
#include "MonsterCreater.h"
#include "NpcCreater.h"
#include "MonsterGroupManager.h"
#include "..//Common//GameTimeHandleManager.h"
#include "CreateMonsterManager.h"
#include "GameBattleControl.h"
SProcessTime gwusetime[200] = {0};
__int64 tempUseTime[200] = {0};


static CSemiAutoIntLock refmonsterlock_cs;
static CSemiAutoIntLock stagemap_cs;
static CSemiAutoIntLock sysnstageinfo;

GameWorld& GettheWorld()
{
    static GameWorld s_world;
    return s_world;
}

bool GameWorld::bShowRunProcessInfo = false;
bool GameWorld::bShowMemoryInfo = false;
bool GameWorld::bCloseGate = false;

GameWorld::GameWorld() 
{
    m_NowSaveCharaStage     = 0; // ������Ҫ����ģ���ͼ
    m_NowSaveCharStageIndex = 0; // ������Ҫ���棬��npc���
    m_PreSaveTime           = 0;

    HKEY hKey;
    DWORD dwValue, dwLen, dwType;
    dwLen = sizeof(DWORD);
    dwType = REG_DWORD;
    RegOpenKey(HKEY_LOCAL_MACHINE, "HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0", &hKey);
    RegQueryValueEx(hKey, "~MHz", 0, &dwType, (LPBYTE)&dwValue, &dwLen);
    RegCloseKey(hKey);
    m_dwCpuHz = dwValue * 1000000;
    m_guildsorted = false;

    m_bExtendBornMapOpen = true;
}

GameWorld::~GameWorld()
{

}

bool GameWorld::GlobalMessage( EExternMessage msg, WPARAM wParam, LPARAM lParam )
{
    switch( msg )
    {
    case ExtMsg_AddCharacter:
        {
            return OnAddCharacter( (DWORD)wParam, __FILE__, __LINE__  );
        }
        break;
    case ExtMsg_DelCharacter:
        {
            return OnDelCharacter( (DWORD)wParam );
        }
        break;
    case ExtMsg_RefreshCurArea:
        {
            return OnRefreshNewArea( (DWORD)wParam );
        }
        break;
    case ExtMsg_FlashMoveTo:
        {
            SFlashMoveTo* pFlash = (SFlashMoveTo*)lParam;
            if ( pFlash == NULL )
            { return false; }

            return OnFlashMoveTo( (DWORD)wParam, pFlash->dwMapID, pFlash->x, pFlash->y, pFlash->fDir );
        }
        break;
    case ExtMsg_EnterStage:
        {
            return OnEnterStage( (DWORD)wParam );
        }
        break;
    case ExtMsg_LeaveStage:
        {
            return OnLeaveStage( (DWORD)wParam );
        }
        break;
    default:
        break;
    }
    return true;
}

GameStage* GameWorld::GetCharPosInWorld( BaseCharacter* pChar, DWORD& dwMapId, int& nX, int& nY, bool bCreate )
{
    if ( pChar == NULL )
    { return NULL; }

    GameStage* pGameStage = GetStageById( dwMapId );

    // ������ڳ����Ƿ����(������������Ӧ���Ǹ���û��)
    if ( pGameStage == NULL && pChar->IsPlayer() )
    {
        // ��ø���ID
        DWORD dwID = EctypeId2MapId( dwMapId );
        MapConfig::MapData* pMapData = theMapConfig.GetMapDataById( dwID );
        if ( pMapData != NULL && pMapData->IsEctypeMap() )
        {
            // ������ʱ�Ǵ������Ƿɵ���ȫ��
            if ( pMapData->IsCreateNewMap() )
            {
                dwMapId = MakeEctypeStageID( pMapData, pChar );
                pChar->SetMapID( dwMapId );
                pGameStage = GetStageById( dwMapId );
                if ( pGameStage == NULL && bCreate )
                {
                    pGameStage = SingleCreateStage( dwID, dwMapId );
                }
            }
        }
    }

	// ��Ȼû�еĻ� ����������ȫ��
    if( pGameStage == NULL && pChar->IsPlayer() )
    {
        DWORD dwID = EctypeId2MapId( dwMapId );
        MapConfig::MapData* pMapData = theMapConfig.GetMapDataById( dwID );
        MapConfig::RelivePosition* pRelivePosition = NULL;
        if (pMapData != NULL)
        {
            pRelivePosition = pMapData->GetRelivePositionByState( false );
        }

        if ( pRelivePosition != NULL && pRelivePosition->MapId != dwID )
        {
            pGameStage = GetStageById( dwMapId );

            dwMapId = pRelivePosition->MapId;
            nX      = FloatToTile( pRelivePosition->PositionX );
            nY      = FloatToTile( pRelivePosition->PositionY );

            LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_WARNING, "GetCharPosInWorld, [%s] �Ҳ�������[0x%0x]. ������[0x%0x]", pChar->GetCharName(), dwID, dwMapId );
        }

        if ( pGameStage == NULL )   // ��û���ҵ����ڵĳ���
        {
            pGameStage = GetActiveStageInWorld();
            if ( pGameStage != NULL )
            {
                MapConfig::RelivePosition* pStageRelive = theMapConfig.GetRelivePostionByMapID( EctypeId2MapId( pGameStage->GetStageID() ) );
                if ( pStageRelive != NULL )
                {
                    dwMapId = pStageRelive->MapId;
                    nX      = FloatToTile( pStageRelive->PositionX );
                    nY      = FloatToTile( pStageRelive->PositionY );

                    LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_WARNING, "GetCharPosInWorld, [%s] �Ҳ�����ȫ����߰�ȫ����Ǳ���ͼ [0x%0x]. ������[0x%0x]", pChar->GetCharName(), dwID, dwMapId );
                }

            }
        }

        //����ͼ��,����zֵ
        pChar->SetFloatZ( WORLD_HEIGHT );
    }

    return pGameStage;
}

bool GameWorld::OnAddCharacterOnlyID( GameObjectId dwID)
{
    //CSALocker locker(m_locknumcs);
    return _objectIds.insert( dwID ).second;
}

bool GameWorld::OnAddCharacter( GameObjectId dwID, const char* szFile, uint32 line )
{   
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( dwID ); // ��� dwID ��ɫ����
    if( NULL == pChar )
    { return false;}

    // �� dwID �ӵ�����Character�б���
    if ( pChar->IsPlayer() )
    { _playerIds.insert( dwID ); }

    if( !_objectIds.insert( dwID).second )
    {
        LogMessage::LogLogicError( "OnAddCharacter(dwID) Character is full [%d] or %s[%d] is already in the stage.",_objectIds.size(), pChar->GetCharName(), dwID );
        return false;
    }

    return OnEnterStage( dwID );
}

bool GameWorld::OnLeaveStage( GameObjectId dwID )
{   
    // ��� dwID ��ɫ����
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( dwID );
    if( NULL == pChar )
    { return false; }

    GameStage* pOldStage = GetStageById( pChar->GetLastMapID() );
    if ( !pOldStage )
    {
        LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_WARNING, "�˳��Ѿ��Ҳ���ԭ�ȵĳ�����[0x%x]", pChar->GetLastMapID() );
        return true;
    }

    return pOldStage->CharacterLeave( pChar ); 
}

bool GameWorld::OnEnterStage( GameObjectId dwID )
{
    // ��� dwID ��ɫ����
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( dwID );
    if( pChar == NULL )
    { return false; }

    DWORD dwMapId = pChar->GetMapID();
    int   nMapX   = pChar->GetTileX();
    int   nMapY   = pChar->GetTileY();

    DWORD dwLastMapId = dwMapId;
    GameStage* pGameStage = GetCharPosInWorld( pChar, dwMapId, nMapX, nMapY, true );
    if ( pGameStage == NULL )
    {
        pChar->Log( "Exit By OnEnterStage, Character[%s] in stage [0x%x] is beingless.", pChar->GetCharName(), EctypeId2MapId( dwLastMapId ) );
        return false;
    }

    // ����dwID���ڳ���
    if( !pGameStage->CharacterEnter( pChar, __FILE__, __LINE__ ) )
    {
        LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_WARNING, "OnEnterStage, character[%s] add to stage[0x%x] is failed.",pChar->GetCharName(), EctypeId2MapId( dwLastMapId ) );
        return false;
    }
    return true;
}

bool GameWorld::KickCharByAccount( DWORD dwAccount )
{
    int nSize = min(dr_worldMaxPlayers, theRunTimeData.theCharacters.GetSize());
    for( int i=0; i<nSize; ++i )
    {
        BaseCharacter* pChar = theRunTimeData.GetCharacterByID( i );
        if ( pChar && pChar->IsPlayer())
        {
            GamePlayer* pPlayer = (GamePlayer*)pChar;
            if ( pPlayer->GetAccountID() == dwAccount )
            {
                pPlayer->Log( "Exit By KickCharByAccount" );
                pPlayer->ExitWorld(__FUNCTION__, __FILE__, __LINE__);
                return true;
            }
        }
    }
    return false;
}

bool GameWorld::OnDelCharacterOnlyID( GameObjectId dwID)
{
    //CSALocker locker(m_locknumcs);
    GameObjectIDSetItr it = _objectIds.find( dwID );
    if ( it != _objectIds.end() )
    {
        _objectIds.erase( it );
        return true;
    }

    return false;
}

//bool GameWorld::OnDelNpc( DWORD dwID )
//{
//    int i = m_CharacterTable.Find( dwID );
//    if( i != -1 )
//    {
//        m_CharacterTable.Del( i, FALSE );
//    }
////     BaseCharacter* pChar = theRunTimeData.GetCharacterByNpcID( dwID );
////     if( !pChar && !pChar->IsNpc())
////         return false;
//
//    NpcInfo::Npc* npcType = theNpcInfo.GetNpcByStaticId(dwID);
//    if (!npcType && npcType->type != eNT_ScriptNpc)
//    {
//        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "OnDelCharacter(dwID)  [%d]Character Is Not Script Npc \n", dwID );
//        return false;
//    }
//
//    int nMapId = pChar->GetMapID();
//
//    GameStage* pGameStage = GetStageById( nMapId );
//
//    if ( !pGameStage )
//    {
//        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "OnDelCharacter(dwID)  [%d]Character can`t find stage[%d].\n", dwID, nMapId );
//        return false;
//    }
//
//    if( !pGameStage->CharacterLeave( pChar->GetID() ) )
//    {
//        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_WARNING, "OnDelCharacter(dwID) [%d]Character leave stage[%d] is wrong.\n", dwID, nMapId );
//    }
//    return true;
//}

bool GameWorld::OnDelCharacter( GameObjectId dwID )
{
    _objectIds.erase( dwID );

    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( dwID );
    if( NULL == pChar )
    { return false; }

    if ( pChar->IsPlayer() )
    { _playerIds.erase( dwID ); }

    uint32 nMapId = InvalidLogicNumber;
    if( pChar->GetLastMapID() != InvalidLogicNumber )
    { 
		nMapId = pChar->GetLastMapID(); 
	}
    else
    {
        if ( pChar->GetLastEctypeMapID() != InvalidLogicNumber )
        { nMapId = pChar->GetLastEctypeMapID(); }
        else
        { nMapId = pChar->GetMapID(); }
    }

    // �ж��Ƿ��Ѿ��������� �п���һ�ζ�û�н���
    if ( nMapId != InvalidLogicNumber )
    {
        GameStage* pGameStage = GetStageById( nMapId );
        if ( NULL == pGameStage )
        { // �����Ѿ�������
            return false;
        }

        // �����Ƿ���ͳ��ֵ --
        if( pChar->IsMonster() )
        {
            MonsterBaseEx* pAiChar = (MonsterBaseEx*)pChar;            
            int index = pAiChar->GetProduceIndex();
            if ( index >= 0 )
            { pGameStage->SetMonsterDead( index );}
        }

        if( !pGameStage->CharacterLeave( pChar ) )
        {
            LogMessage::LogLogicError( "OnDelCharacter(%d) Character leave stage[0x%x] not find", dwID, nMapId );
        }        
    }
    return true;
}

bool GameWorld::OnRefreshNewArea( GameObjectId dwID )
{ // ˢ�µ�ǰ��������
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( dwID );
    if( pChar == NULL )
    { return false; }

    // �������ڼ��ص�ͼ�Ͳ�ˢ��
    if ( pChar->GetStatus() == CS_LOADINGMAP )
    { return true; }

    GameStage* pStage = GetStageById( pChar->GetMapID() );
    if( pStage == NULL )
    {
        LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_ERROR, "[%s]OnRefreshNewArea::GetStageById[0x%0x]", pChar->GetCharName(), pChar->GetMapID() );
        pChar->OnExit( NULL );
        return false;
    }

    return pStage->RefreshNewArea( pChar );
}

// ˢ����ҵ�ǰ�ܿ����������(������9�����ڵ����)
int GameWorld::OnRefreshPlayerCharNumberInView( GameObjectId dwID )
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( dwID );
    if(!pChar)
        return 0;

    if ( pChar->GetStatus() == CS_LOADINGMAP )
    { // �������ڼ��ص�ͼ�Ͳ�ˢ��
        return 0;
    }

    GameStage* pStage = GetStageById( pChar->GetMapID() );
    if( pStage == NULL )
    {   
        pChar->Log( "Exit By OnRefreshPlayerCharNumberInView" );
        MoveRoleToSafePosAndExit( pChar );
        return 0;
    }

    return pStage->RefreshPlayerCharNumberInView( pChar );
}

bool GameWorld::OnFlashMoveTo( GameObjectId dwID, DWORD dwMapID, short nTileX, short nTileY, float fDir )
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( dwID );
    if( NULL == pChar)
    { return false; }

    GameStage* pNewStage = GetStageById( dwMapID );
    if ( pNewStage == NULL )
    {
       /* pChar->Log( "Exit By OnFlashMoveTo �Ҳ���Ҫ����ĳ���[0x%x]", dwMapID );*/
		 pChar->Log( theXmlString.GetString(eServerLog_CantFindMap), dwMapID );
        pChar->CriticalError(__FUNCTION__, __FILE__, __LINE__);
        return false;
    }   

    // ����Χ���˷���exitmysight��Ϣ
    MsgExitMySight exitSight;
    exitSight.header.stID = (GameObjectId)dwID;
    GettheServer().SendMsgToView( &exitSight, dwID, true );

    // �Ȳ��˳��ϵĳ���,�ȿͻ������������˳���
    pChar->SetLastMapID( pChar->GetMapID() );

    // ��FlashToMap��������г��
    pChar->ClearEnmity( true );

    if( pChar->IsPlayer() )
    {   
        GamePlayer* pBasePlayer = (GamePlayer*)pChar;
        pBasePlayer->SendChangeMapMessageToClient( dwMapID, nTileX, nTileY, DIR_0 /*theRand.rand32()%8*/, fDir );
    }
    else
    {
        pChar->SetTileX( nTileX );
        pChar->SetTileY( nTileY );
        pChar->SetFloatZ( WORLD_HEIGHT );
        pChar->SetMapID( dwMapID );          
        if( !pNewStage->CharacterEnter( pChar, __FILE__, __LINE__ ) )
        { //�����µĳ���
            pChar->CriticalError(__FUNCTION__, __FILE__, __LINE__); 
            return false;
        }
    }
    return true;
}

typedef std::vector<DWORD>             GameStageIdContainer;
typedef GameStageIdContainer::iterator ItrGameStageIdContainer;
bool GameWorld::Process()
{
    DECLARE_TIME_TEST

    gwusetime[0].szFunctionName = "GameWorld::Process";
    __int64 time = HelperFunc::GetCPUTime();

    // CSALocker locker(this);
    g_dwLastWorldProcessTime = HQ_TimeGetTime();

#ifndef _DEBUG
    BEGIN_TIME_TEST( "pGameStage->Run()" );
#endif
    gwusetime[1].szFunctionName = "pChar->Run";
    __int64 funtime = HelperFunc::GetCPUTime();
    GameStageIdContainer vtReleaseStage;
    {
		DECLARE_TIME_TEST
		BEGIN_TIME_TEST( "pGameStage->Run()[1]" );
        CSALocker lock( stagemap_cs );
        for( ItrGameStageContainer iter = m_mapGameStage.begin(); iter != m_mapGameStage.end(); ++iter )
        {
			DECLARE_TIME_TEST
			BEGIN_TIME_TEST( "pGameStage->Run()[2]" );
            GameStage* pStage = iter->second;
            if ( pStage == NULL )
            { continue; }

			// ���߼����߳����г���
            if ( !g_Cfg.bMTStageProcess )    
            {
                pStage->RunUpdate();
            }

            if ( pStage->IsStageRelease() )
            {
                vtReleaseStage.push_back( pStage->GetStageID() );
            }
			END_TIME_TEST_1( "pGameStage->Run()[2]", 100 );
        }
		END_TIME_TEST_1( "pGameStage->Run()[1]", 100 );
    }

    if (!vtReleaseStage.empty())
    {
        //CSALocker locker(refmonsterlock_cs);
        // �ͷų���
        for ( ItrGameStageIdContainer iter = vtReleaseStage.begin(); iter != vtReleaseStage.end(); ++iter )
        {
            bool bResult = ReleaseTheStage( *iter );
        }
    }
#ifndef _DEBUG
    END_TIME_TEST_1( "pGameStage->Run()", 100 );
#endif

	BEGIN_TIME_TEST( "GameWorld[1]" );
    tempUseTime[1] = (HelperFunc::GetCPUTime() - funtime);
    gwusetime[1].nTime += tempUseTime[1];

    gwusetime[2].szFunctionName = "pScriptMgr->Run";
    funtime = HelperFunc::GetCPUTime();
    GetScriptMgr()->Run();
    TryLoadAllScript();
	CheckAsynStageInfo();
    tempUseTime[2] = (HelperFunc::GetCPUTime() - funtime);
    gwusetime[2].nTime += tempUseTime[2];

	END_TIME_TEST_1( "GameWorld[1]", 100 );
	BEGIN_TIME_TEST( "GameWorld[2]" );
    gwusetime[3].szFunctionName = "GetShopMgr->Run";
    funtime = HelperFunc::GetCPUTime();
    GetShopMgr()->Run();
    tempUseTime[3] = (HelperFunc::GetCPUTime() - funtime);
    gwusetime[3].nTime += tempUseTime[3];
	END_TIME_TEST_1( "GameWorld[2]", 100 );
	BEGIN_TIME_TEST( "GameWorld[3]" );
    gwusetime[4].szFunctionName = "GetGameWorldTimer()->Run";
    funtime = HelperFunc::GetCPUTime();
    GetGameWorldTimer()->Run();
    tempUseTime[4] = (HelperFunc::GetCPUTime() - funtime);
    gwusetime[4].nTime += tempUseTime[4];
	END_TIME_TEST_1( "GameWorld[3]", 100 );
	BEGIN_TIME_TEST( "GameWorld[4]" );
    gwusetime[5].szFunctionName = "TeamMan->Update";
    funtime = HelperFunc::GetCPUTime();
    theGameTeamManager.RunTeamManagerUpdate( HQ_TimeGetTime(), TeamDefine::SendToCenter );
    tempUseTime[5] = (HelperFunc::GetCPUTime() - funtime);
    gwusetime[5].nTime += tempUseTime[5];
	END_TIME_TEST_1( "GameWorld[4]", 100 );
	BEGIN_TIME_TEST( "GameWorld[5]" );
    gwusetime[11].szFunctionName = "LuckRewardManager->Update";
    funtime = HelperFunc::GetCPUTime();
    theTeamLuckRewardManager.LuckRewardUpdate(); // ˢ������15��
    theCharLuckRewardManager.LuckRewardUpdate();
    tempUseTime[11] = (HelperFunc::GetCPUTime() - funtime);
    gwusetime[11].nTime += tempUseTime[11];
	END_TIME_TEST_1( "GameWorld[5]", 100 );
	BEGIN_TIME_TEST( "GameWorld[6]" );
    theRabotManager.RunCheckCheatUpdate( HQ_TimeGetTime() ); // ��Ҽ��
    thePlayerBattleManager.RunUpdate( HQ_TimeGetTime() );
    theTeamBattleManager.RunUpdate( HQ_TimeGetTime() );
    theGameCountryManager.RunUpdate( HQ_TimeGetTime() );
    theBargainingManager.RunUpdate( HQ_TimeGetTime() );
    theCampBattleControl.RunUpdate( HQ_TimeGetTime() );
	theGameBattleControl.RunUpdate( HQ_TimeGetTime() );	

	theGameTimeHandleManager.Update(HQ_TimeGetTime() );
    thePetBreedManager.RunUpdate( HQ_TimeGetTime() );
	theMonsterGroupManager.Update();
	theCreateMonsterManager.RunUpdate( HQ_TimeGetTime() );
	END_TIME_TEST_1( "GameWorld[6]", 100 );
	BEGIN_TIME_TEST( "GameWorld[7]" );
    gwusetime[6].szFunctionName = "GetScriptMgr()->RunDelayTime()";
    funtime = HelperFunc::GetCPUTime();

    // ScriptMgr    
    GetScriptMgr()->RunDelayTime();
    tempUseTime[6] = (HelperFunc::GetCPUTime() - funtime);
    gwusetime[6].nTime += tempUseTime[6];
	END_TIME_TEST_1( "GameWorld[7]", 100 );

	BEGIN_TIME_TEST( "GameWorld[8]" );
	END_TIME_TEST_1( "GameWorld[8]", 100 );

    //�Զ����洦��
	BEGIN_TIME_TEST( "GameWorld[9]" );
    gwusetime[9].szFunctionName = "AutoSave";
    funtime = HelperFunc::GetCPUTime();    
    AutoSaveUpdate();
    tempUseTime[9] = (HelperFunc::GetCPUTime() - funtime);
    gwusetime[9].nTime += tempUseTime[9];

    gwusetime[10].szFunctionName = "CheckStageLoad";
    funtime = HelperFunc::GetCPUTime();
    CheckStageLoad();	
    tempUseTime[10] = (HelperFunc::GetCPUTime() - funtime);
    gwusetime[10].nTime += tempUseTime[10];

    MapMonitorRender();
	END_TIME_TEST_1( "GameWorld[9]", 100 );
	BEGIN_TIME_TEST( "GameWorld[10]" );
    tempUseTime[0] = (HelperFunc::GetCPUTime() - time);
    gwusetime[0].nTime += tempUseTime[0];

    // �̳��ۿ�
    if (g_Cfg.bIsChangedShopCenterOff)
    {
        for (int nloop = 0;nloop<dr_worldMaxPlayers;++nloop)
        {
            BaseCharacter* pChar = theRunTimeData.GetCharacterByID(nloop);
            if ( NULL == pChar || !pChar->IsPlayer())
            { continue; }

            MsgTellShopCenterOffSet tellmsg;
            tellmsg.header.stID = pChar->GetID();
            tellmsg.stOffSell   = g_Cfg.m_nOffSetInShopCenter;
            GettheServer().SendMsgToSingle(&tellmsg,pChar);
            if (g_Cfg.m_nOffSetInShopCenter != 100)
            { pChar->TellClient( theXmlString.GetString(eTellClient_ShopCenterOff),g_Cfg.m_nOffSetInShopCenter);}
        }
        g_Cfg.bIsChangedShopCenterOff = false;
    }
	END_TIME_TEST_1( "GameWorld[10]", 100 );
	BEGIN_TIME_TEST( "GameWorld[11]" );
    if ( theRunTimeData.g_bIsChangeSkillExp)
    {
        for (int nloop = 0;nloop < dr_worldMaxPlayers;nloop++)
        {
            BaseCharacter* pChar = theRunTimeData.GetCharacterByID(nloop);
            if ( pChar == NULL || !pChar->IsPlayer())
            { continue; }

            pChar->TellClient( theXmlString.GetString(eTell_Client_ServerSkillExpPer), theRunTimeData.g_nSkillExpPer);            
        }
        theRunTimeData.g_bIsChangeSkillExp = false;
    }
	END_TIME_TEST_1( "GameWorld[11]", 100 );
	BEGIN_TIME_TEST( "GameWorld[12]" );
    theRunTimeData.RunUpdate( HQ_TimeGetTime() );
	END_TIME_TEST_1( "GameWorld[12]", 100 );

    ////�������ѭ��ʱ�䳬��
    //if(tempUseTime[0] >= m_dwCpuHz * 2)
    //{
    //    char szBuf[1024] = {0};
    //    _snprintf(szBuf, sizeof(szBuf), "CPUƵ�� %s Hz", BigInt2String(m_dwCpuHz));
    //    DebugLogout(szBuf);
    //    for(int i=0;i<=10;i++)
    //    {
    //        _snprintf(szBuf, sizeof(szBuf), "%s ��ʱ:%s", gwusetime[i].szFunctionName, BigInt2String(tempUseTime[i]));
    //        DebugLogout(szBuf);
    //    }
    //}
    return true;
}

GameStage* GameWorld::CreateNormalStage( MapConfig::MapData* pMapData, uint32 dwEctypeId )
{
    GameStage* pStage = GameStage::CreateStage< NormalStage >();
    if ( pStage == NULL )
    {
        LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_ERROR, "Create GameStage[%u] [0x%x] Alloc memory Error", pMapData->Id, dwEctypeId );
        return NULL;
    }

    if ( !pStage->Initialize( pMapData, dwEctypeId, 0 ) )
    {
        theCWaitReleaseStag.AddReleaseStage( pStage, 0 );
        return NULL;
    }

    LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "Create Stage:[%s][0x%x] Current World StageCount:[%d]", pMapData->MapName.c_str(), dwEctypeId, GetStageCount() );
    return pStage;
}

GameStage* GameWorld::CreateEctypeStage( MapConfig::MapData* pMapData, uint32 dwEctypeId, uint16 ustLevel /* = 0 */, uint32 dwReserveValue /* = 0 */ )
{
    GameStage* pStage = NULL;
    switch ( pMapData->GetMapType() )
    {
    case MapConfig::MT_SingleTeam:      // �����鸱��
        pStage = GameStage::CreateStage< SingleTeamStage >();
        break;
    case MapConfig::MT_SinglePlayer:    // ���˸���
        pStage = GameStage::CreateStage< SinglePlayerStage >();
        break;
    case MapConfig::MT_SingleGuild:     // �����ɸ���
        pStage = GameStage::CreateStage< SingleGuildStage >();
        break;
    case MapConfig::MT_MultiTeam:       // ����鸱��
        pStage = GameStage::CreateStage< MultiTeamStage >();
        break;
    case MapConfig::MT_MultiPlayer:     // ���˸���
        pStage = GameStage::CreateStage< MultiPlayerStage >();
        break;
    case MapConfig::MT_MultiGuild:      // ����ɸ���
        pStage = GameStage::CreateStage< MultiGuildStage >();
        break;
    default:
        break;
    }
    
    if ( pStage == NULL )
    {
        LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_ERROR, "Create GameStage[%u] [0x%x] Alloc memory Error", pMapData->Id, dwEctypeId );
        return NULL;
    }

    EctypeStage* pEctypeStage = static_cast< EctypeStage* >( pStage );
    if ( !pEctypeStage->Initialize( pMapData, dwEctypeId, ustLevel ) )
    {
        theCWaitReleaseStag.AddReleaseStage( pStage, 0 );
        return NULL;
    }

    // ��������
    pEctypeStage->AddReserve( dwReserveValue ); // ����ԤԼ

    switch( pMapData->GetMapType() )
    {
    case MapConfig::MT_MultiPlayer:
    case MapConfig::MT_MultiTeam:
    case MapConfig::MT_MultiGuild:
        {
            unsigned long uId = GetEctypeMapLastId( pMapData->Id, false );
            if ( uId == 0 || uId > 0xffffff )
            { InitEctypeMapId( pMapData->Id ); }
        }
        break;
    default:
        break;
    }

    // ͬ����gateServer
    MsgGW2GCreateStage xCreate;
    xCreate.dwMapId    = pMapData->Id;
    xCreate.dwEctypeId = dwEctypeId;
    GettheServer().SendMsgToGates( &xCreate );

    LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_INFO, "Create Stage:[%s][0x%x] Current World StageCount:[%d]", pMapData->MapName.c_str(), dwEctypeId, GetStageCount() );
    return pEctypeStage;
}

GameStage* GameWorld::AsynCreateEctypeStage( MapConfig::MapData* pMapData, uint32 dwEctypeId, uint16 ustLevel, uint32 dwReserveValue/*,GS2CSCreateMulitStageAck* pMsg = NULL*/)
{
	GameStage* pStage = NULL;
	switch ( pMapData->GetMapType() )
	{
	case MapConfig::MT_SingleTeam:      // �����鸱��
		pStage = GameStage::CreateStage< SingleTeamStage >();
		break;
	case MapConfig::MT_SinglePlayer:    // ���˸���
		pStage = GameStage::CreateStage< SinglePlayerStage >();
		break;
	case MapConfig::MT_SingleGuild:     // �����ɸ���
		pStage = GameStage::CreateStage< SingleGuildStage >();
		break;
	case MapConfig::MT_MultiTeam:       // ����鸱��
		pStage = GameStage::CreateStage< MultiTeamStage >();
		break;
	case MapConfig::MT_MultiPlayer:     // ���˸���
		pStage = GameStage::CreateStage< MultiPlayerStage >();
		break;
	case MapConfig::MT_MultiGuild:      // ����ɸ���
		pStage = GameStage::CreateStage< MultiGuildStage >();
		break;
	default:
		break;
	}

	if ( pStage == NULL )
	{
		LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_ERROR, "Create GameStage[%u] [0x%x] Alloc memory Error", pMapData->Id, dwEctypeId );
		return NULL;
	}

	EctypeStage* pEctypeStage = static_cast< EctypeStage* >( pStage );
	if ( !pEctypeStage->Initialize( pMapData, dwEctypeId, ustLevel ) )
	{
		theCWaitReleaseStag.AddReleaseStage( pStage, 0 );
		return NULL;
	}

	// ��������
	pEctypeStage->AddReserve( dwReserveValue ); // ����ԤԼ

	switch( pMapData->GetMapType() )
	{
	case MapConfig::MT_MultiPlayer:
	case MapConfig::MT_MultiTeam:
	case MapConfig::MT_MultiGuild:
		{
			unsigned long uId = GetEctypeMapLastId( pMapData->Id, false );
			if ( uId == 0 || uId > 0xffffff )
			{ InitEctypeMapId( pMapData->Id ); }
		}
		break;
	default:
		break;
	}

	// ͬ����gateServer
	//MsgGW2GCreateStage xCreate;
	//xCreate.dwMapId    = pMapData->Id;
	//xCreate.dwEctypeId = dwEctypeId;
	//GettheServer().SendMsgToGates( &xCreate );

	LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_INFO, "Create Stage:[%s][0x%x] Current World StageCount:[%d]", pMapData->MapName.c_str(), dwEctypeId, GetStageCount() );
	return pEctypeStage;
}

GameStage* GameWorld::SingleCreateStage( uint32 dwMapId, uint32 dwEctypeId )
{
    return CreateStage( dwMapId, dwEctypeId );
}

GameStage* GameWorld::MultiCreateStage( uint32 dwMapId, uint32 dwEctypeId, uint16 ustLevel /* = 0 */, uint32 dwReserveValue /* = 0 */,GS2CSCreateMulitStageAck* pMsg /*= NULL*/ )
{
	//�ɶ��޸�
	//return CreateStage( dwMapId, dwEctypeId,ustLevel,dwReserveValue);

    // �Ƿ����ڴ�������
    for ( CreateMapVectorIter iter = m_vecCreateMapInfo.begin(); iter != m_vecCreateMapInfo.end(); ++iter )
    {
        if ( iter->dwEctypeId == dwEctypeId )
        { return NULL; }
    }

	DWORD cur_time = HQ_TimeGetTime();

    SLoadMapInfo* pLoadMapInfo = new SLoadMapInfo;
    if ( pLoadMapInfo == NULL )
    {
        LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_INFO, "Start loading stage %x by multithreading. Fail", dwEctypeId );
        return NULL;
    }

    pLoadMapInfo->pGameWorld     = this;
    pLoadMapInfo->dwMapId        = dwMapId;
    pLoadMapInfo->dwEctypeId     = dwEctypeId;
    pLoadMapInfo->ustLevel       = ustLevel;
    pLoadMapInfo->dwStartTime    = cur_time;
    pLoadMapInfo->dwReserveValue = dwReserveValue;          // ԤԼֵ
	if (!pMsg)
	{
		pLoadMapInfo->sendtocenter = false;
	}
	else
	{
		memcpy(&pLoadMapInfo->mca,pMsg,sizeof(GS2CSCreateMulitStageAck));
		pLoadMapInfo->sendtocenter = true;
	}
    m_vecCreateMapInfo.push_back( *pLoadMapInfo );
    _beginthread( LoadMapThread, 0, pLoadMapInfo );
    return NULL;
}

void GameWorld::LoadMapThread( void *pLoadMapInfo )
{
    SLoadMapInfo* pInfo = (SLoadMapInfo*)pLoadMapInfo;
	if (pInfo->sendtocenter)
	{
		pInfo->pGameWorld->AsynCreateStage( pInfo->dwMapId, pInfo->dwEctypeId, pInfo->ustLevel, pInfo->dwReserveValue,&pInfo->mca );
	}
	else
		pInfo->pGameWorld->AsynCreateStage( pInfo->dwMapId, pInfo->dwEctypeId, pInfo->ustLevel, pInfo->dwReserveValue,NULL);
    
    delete pInfo;
}

GameStage* GameWorld::CreateStage( uint32 dwMapId, uint32 dwEctypeId, uint16 ustLevel /* = 0 */, uint32 dwReserveValue /* = 0 */ )
{
	//������ͼ ���� �������� (�����п��ܲ��鵱ǰGameServer����  ������Ҫ���͸�CenterServerȥ����)
    MapConfig::MapData* pMapData = theMapConfig.GetMapDataById( EctypeId2MapId( dwMapId ) );
    if ( pMapData == NULL )
    { return NULL; }

	if (!g_Cfg.IsMapRun(dwMapId))
	{
		return NULL;
	}

    GameStage* pStage = NULL;
    switch ( pMapData->GetMapType() )
    {
    case MapConfig::MT_NormalMap:
        pStage = CreateNormalStage( pMapData, dwEctypeId );
        break;
	default://�������� ��ͨ���� �ǲ��ᴴ��������
		pStage = CreateEctypeStage( pMapData, dwEctypeId, ustLevel, dwReserveValue );
        break;
    }
    if ( pStage == NULL )
    { return NULL; }

	//��ʼ��Ѱ·�� 
 	SwMap* pParthFinderData = GetParthFinderTemplates().GetParthFinder( dwMapId );
 	if ( pParthFinderData && pMapData->GetMapType() ==  MapConfig::MT_NormalMap )
	{//����������������AI�õ�Ѱ·��Ϣ�� by vvx 2013.7.26
		SwMap* pParthFinder = new SwMap;
		pParthFinder->Create( *pParthFinderData );
		pParthFinder->SetUseWeight( false );
		pStage->SetParthFinder( pParthFinder );

		pParthFinder = new SwMap;
		pParthFinder->Create( *pParthFinderData );
		pParthFinder->SetUseWeight( false );
		pStage->SetThreadParthFinder( pParthFinder );
	}

    //ˢ���̺߳��߼��̶߳����ã���ֻҪ�����߼��̼߳���
    if (/*g_Cfg.bMTRefreshMonster &&*/ g_Cfg.bMTStageProcess )
    {
        pStage->StartRunThread();
    }
//     else if (!g_Cfg.bMTRefreshMonster && g_Cfg.bMTStageProcess )
//     {
//         pStage->StartRunThread();
//     }
//     else if (g_Cfg.bMTRefreshMonster && !g_Cfg.bMTStageProcess )
//     {
//         pStage->StartRefreshMonsterThread();
//     }

    if ( !AddGameStage( pStage ) )
    {
        theCWaitReleaseStag.AddReleaseStage( pStage, 0 );
        return NULL;
    }

    // ����NPC
    NpcCreater::CreateNpc( pStage );
    return pStage;
}

GameStage* GameWorld::AsynCreateStage( uint32 dwMapId, uint32 dwEctypeId, uint16 ustLevel , uint32 dwReserveValue,GS2CSCreateMulitStageAck* pMsg)
{
	//���̴߳�������
	MapConfig::MapData* pMapData = theMapConfig.GetMapDataById( EctypeId2MapId( dwMapId ) );
	if ( pMapData == NULL )
	{ return NULL; }

	if(!g_Cfg.IsMapRun(dwMapId))
	{
		return NULL;
	}

	GameStage* pStage = NULL;
	switch ( pMapData->GetMapType() )
	{
	case MapConfig::MT_NormalMap://�����ִ�в����ģ���Ϊ��̬�����϶��Ǹ���
		pStage = CreateNormalStage( pMapData, dwEctypeId );
		break;
	default:
		pStage = AsynCreateEctypeStage( pMapData, dwEctypeId, ustLevel, dwReserveValue);
		break;
	}
	if ( pStage == NULL )
	{ return NULL; }

	//��ʼ��Ѱ·�� 
	SwMap* pParthFinderData = GetParthFinderTemplates().GetParthFinder( dwMapId );
	if ( pParthFinderData&&pMapData->GetMapType() ==  MapConfig::MT_NormalMap)
	{//����������������AI�õ�Ѱ·��Ϣ�� by vvx 2013.7.26
		SwMap* pParthFinder = new SwMap;
		pParthFinder->Create( *pParthFinderData );
		pParthFinder->SetUseWeight( false );
		pStage->SetParthFinder( pParthFinder );

		pParthFinder = new SwMap;
		pParthFinder->Create( *pParthFinderData );
		pParthFinder->SetUseWeight( false );
		pStage->SetThreadParthFinder( pParthFinder );
	}

	//ˢ���̺߳��߼��̶߳����ã���ֻҪ�����߼��̼߳���
	if (/*g_Cfg.bMTRefreshMonster &&*/ g_Cfg.bMTStageProcess )
	{
		pStage->StartRunThread();
	}
	//     else if (!g_Cfg.bMTRefreshMonster && g_Cfg.bMTStageProcess )
	//     {
	//         pStage->StartRunThread();
	//     }
	//     else if (g_Cfg.bMTRefreshMonster && !g_Cfg.bMTStageProcess )
	//     {
	//         pStage->StartRefreshMonsterThread();
	//     }


	//if ( !AddGameStage( pStage ) )
	//{
	//	theCWaitReleaseStag.AddReleaseStage( pStage, 0 );
	//	return NULL;
	//}

	/////////////////////////////////////////
	SSynStageInfo* pSyn = new SSynStageInfo;
	if (!pSyn)
	{
		theCWaitReleaseStag.AddReleaseStage( pStage, 0 );
		return NULL;
	}	
	pSyn->pStage = pStage;
	if (!pMsg)
	{
		pSyn->sendtocenter = false;
	}
	else
	{
		pSyn->sendtocenter = true;
		memcpy(&pSyn->mca,pMsg,sizeof(GS2CSCreateMulitStageAck));
	}
	pSyn->dwStartTime = HQ_TimeGetTime();
	pSyn->dwReserveValue = dwReserveValue;
	///////////////////////////////////////////////
	// ����NPC
	NpcCreater::AsynCreateNpc( pStage,pSyn);

	CSALocker lock( sysnstageinfo );
	{
		m_vecSSynStageInfo.push_back(pSyn);
	}
	return pStage;
}

bool GameWorld::ReleaseTheStage( uint32 dwEctypeId )
{
    ItrGameStageContainer it = m_mapGameStage.find( dwEctypeId );
    if ( it == m_mapGameStage.end() )
    { return false; }

    GameStage* pStage = it->second;

    if ( g_Cfg.bMTStageProcess )
    { pStage->StopRunThread(); }

	pStage->ReleaseAllCharacter();

    theCWaitReleaseStag.AddReleaseStage(pStage,0);

    {
        CSALocker locker(stagemap_cs);
        m_mapGameStage.erase( it );
    }

    if ( pStage != NULL && pStage->GetMapData())
    { LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_INFO, "Release Stage:[%s][0x%x] Current World StageCount:[%d]", pStage->GetMapData()->MapName.c_str(), dwEctypeId, m_mapGameStage.size() );}
    else
    { LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_INFO, "Release Stage:[0x%x] Current World StageCount:[%d]",dwEctypeId, m_mapGameStage.size() ); }

    MsgGW2GReleaseStage msg;
    msg.dwEctypeId = dwEctypeId;
    GettheServer().SendMsgToGates( &msg );
    return true;
}

bool GameWorld::AddGameStage( GameStage* pStage )
{
    //CSALocker locker(this);
    // ToLog( pStage );
    DWORD dwMapId = pStage->GetStageID();
    if( GetStageById( dwMapId ) )
    {
        return false;
    }
    else
    {
        CSALocker locker(stagemap_cs);
        m_mapGameStage[dwMapId] = pStage;
    }
    return true;
}

bool GameWorld::InitStages()
{
    int nMapCount = theMapConfig.MapDataCount();
    if( nMapCount < 0 )
    {
        LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_CRITICAL, "InitStages nMapCount < 0");
        return false;
    }

    static bool bInitStageSave = false;
    // �������г������ҳ�ʼ��
    for( int i = 0; i < nMapCount; ++i )
    {
        MapConfig::MapData* pMapData = theMapConfig.GetMapDataByIndex( i );
        if ( pMapData == NULL || !g_Cfg.IsMapRun( pMapData->Id ) )
        { continue; }   // �Ƿ񼤻�˵�ͼ

        std::string strFilePath = STAGEROOTDIRECTORY;
        strFilePath += "\\";
        strFilePath += pMapData->GetMapMonsterDataFile();

		// ��ʼ����������
        long result = GetGameStageDataCenter().InitStageDataLoader( pMapData->Id, strFilePath.c_str() );
        if ( result != ER_Success  )
        {
            LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "GetGameStageDataCenter().InitStageDataLoader(%s)(%s)(%d)", pMapData->MapName.c_str(), strFilePath.c_str() , result );
            return false;
        }

		// ��ʼ��Ѱ·ͼ
		strFilePath = STAGEROOTDIRECTORY;
		strFilePath += "\\";
		strFilePath += pMapData->ClientReachableMap;
		result = GetParthFinderTemplates().InitParthFinder( pMapData->Id, strFilePath.c_str() );
		if ( result != ER_Success  )
		{
			LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "GetGameParthFinder().InitParthFinder(%s)(%s)(%d)", pMapData->MapName.c_str(), strFilePath.c_str() , result );
			return false;
		}

		// ��ʼ���赲ͼ
		strFilePath = STAGEROOTDIRECTORY;
		strFilePath += "\\";
		strFilePath += pMapData->ClientReachableMap;
		result = GetBlockMapManager().InitBlockMap( pMapData->Id, strFilePath.c_str() );
		if ( result != ER_Success  )
		{
			LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, "GetBlockMapManager().InitBlockMap(%s)(%s)(%d)", pMapData->MapName.c_str(), strFilePath.c_str() , result );
			return false;
		}

        //if ( !pMapData->IsEctypeMap() )  ������ͼ�����ĸ���������CenterServerҲ��Ҫ֪��
        { // ���߸�CenterServer��GameServer���������ͼ
            SGameStageOp gso;
            gso.op                = SGameStageOp::OT_Update;
            gso.gameStageInfoType = SGameStageOp::GSIT_MapSetting;
            gso.gs.ulStageId      = pMapData->Id;
            gso.gs.usPlayerCount  = 0;
            gso.gs.bIsRun         = g_Cfg.IsMapRun( pMapData->Id );
            _gameStageOp.push_back( gso );
        }

        if ( pMapData->IsEctypeMap() )
        { // �Ǹ���
            InitEctypeMapId(pMapData->Id);
            continue;
        }
		// ��һ�� ûɶ�ð�
        if( bInitStageSave == false )
        {
            extern int g_start_stage;
            g_start_stage = i;
            m_NowSaveCharaStage = i;
            bInitStageSave = true;
        }

        if ( g_Cfg.IsMapRun( pMapData->Id ) )
        {
            if( !SingleCreateStage( pMapData->Id, pMapData->Id ) ) // ��ͨ��������Ҫ�ȼ���Ϣ
            {
                LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_INFO, " CreateStage Fail [%d:%d]", pMapData->Id, pMapData->Id);
                return false;
            }
        }
    }
    return true;
}

void GameWorld::TermStages()
{
    //CSALocker locker(this);
    std::map<DWORD,GameStage*>::iterator it;
    for ( it=m_mapGameStage.begin(); it!=m_mapGameStage.end(); ++it )
    {
        GameStage* pGameStage = it->second;
        theCWaitReleaseStag.AddReleaseStage(pGameStage, 0);
        //CNewWithDebug<GameStage>::Free(pGameStage);
        pGameStage = NULL;
    }
    m_mapGameStage.clear();
}
//
//BaseCharacter* GameWorld::CreateMonster( CMonsterProducer::TagMonsterData* pMonsterInfo, int nMapID, float nX, float nY, float fDirX, float fDirY, int iProductIndex, DWORD dwSpecialID, int nInfluence, BOOL bStartUpAI /* = FALSE  */ )
//{
//    GameStage* pStage = GetStageById(nMapID);
//    if ( pStage == NULL )
//    { return NULL; }
//
//    return pStage->CreateMonster( pMonsterInfo, nX, nY, fDirX, fDirY, iProductIndex, bStartUpAI, dwSpecialID, nInfluence );
//}
//
//MonsterBuildEx* GameWorld::CreateMonsterBuild( uint32 monsterId, uint32 mapId, float fx, float fy, float fdirx, float fdiry, uint8 campId )
//{
//    GameStage* pStage = GetStageById( mapId );
//    if ( pStage == NULL )
//    { return NULL; }
//
//    return (MonsterBuildEx*)pStage->CreateMonsterBuild( monsterId, fx, fy, fdirx, fdiry, campId );
//}
//
//MonsterRoute* GameWorld::CreateMonsterRoute( uint32 monsterId, uint32 mapId, float fx, float fy, float fdirx, float fdiry, uint16 routeId, uint8 campId, bool bBornInRouteBegin, float xoff, float yoff )
//{
//    GameStage* pStage = GetStageById( mapId );
//    if ( pStage == NULL )
//    { return NULL; }
//
//    if ( pStage->IsCaracterFull() )
//    {
//        LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_ERROR, "CreateMonsterRoute Stage %d refresh monster failed!,pStage->IsCaracterFull", mapId );
//        return NULL;
//    }
//
//    int nIndex = GettheItemDetail().FindMonsterIndexById( monsterId );
//    if ( nIndex < 0)
//    { return NULL;}
//
//    ItemDefine::SMonster* pMonsterConfig = GettheItemDetail().GetMonster( nIndex );
//    if ( pMonsterConfig == NULL )
//    {
//        LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_ERROR, "CreateMonsterRoute GettheItemDetail().GetMonster the ID:%d is null", monsterId );
//        return NULL;
//    }
//
//    if ( !pStage->IsInStage( fx, fy, 0 ))
//    {
//        LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_ERROR, "CreateMonsterRoute Map[%s] Monster[%s][%d] pos or area size is wrong, monster x:%f y:%f StageWidth:%d StageHeight:%d", 
//            pStage->GetStoreName(), pMonsterConfig->GetName(), pMonsterConfig->stMonsterId, fx, fy, pStage->GetWidth(), pStage->GetHeight() );
//        return NULL;
//    }
//
//    uint8 nType = Object_MonsterRoute;
//    GameObjectId nID = theRunTimeData.CreateObject( (EObjectType)nType );
//    if( nID == -1 )
//    {
//        LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_ERROR, "ShareData::CreateObject Monster Fail" );
//        return NULL;
//    }
//
//    MonsterRoute* pChar = (MonsterRoute*)theRunTimeData.GetCharacterByID( nID );
//    if( pChar == NULL )
//    {
//        LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_ERROR, "ShareData::GetCharacterByID Monster Fail" );
//        return NULL;
//    }
//
//    pChar->InitRoute( mapId, routeId ); // ��ʼ��·��
//
//    pChar->SetFightCamp( campId );
//    pChar->SetPosOff( xoff, yoff );
//    if ( bBornInRouteBegin )
//    { // 
//        SMovePos* pPos = pChar->GetBeginPos();
//        if ( pPos )
//        {
//            pChar->SetFloatXF( pPos->fX + xoff );
//            pChar->SetFloatYF( pPos->fY + yoff );
//        }
//        else
//        {
//            pChar->SetFloatXF( fx );
//            pChar->SetFloatYF( fy );
//        }
//    }
//    else
//    {
//        pChar->SetFloatXF( fx );
//        pChar->SetFloatYF( fy );
//    }
//
//    // ����Ĭ��ֵ����
//    pChar->SetMonsterId ( pMonsterConfig->stMonsterId  ); // ���ù���Id
//    pChar->SetObjType   ( nType                        ); // ��������Ϊ����
//    pChar->SetCanSwitchStage( false                    ); // ����Ϊ�����л�����
//    pChar->SetStatus    ( CS_IDLE                      ); // ���ó�ʼ��״̬Ϊ����
//    pChar->SetDir       ( 0                            );
//    pChar->SetDirX      ( fdirx                        );
//    pChar->SetDirY      ( fdiry                        );
//    pChar->SetCharName  ( pMonsterConfig->GetName()    );
//    pChar->SetMapID     ( mapId                        );
//    pChar->SetProfession( pMonsterConfig->stProfession );
//    pChar->SetModelId   ( pMonsterConfig->iModelID     );
//    if( pMonsterConfig->bIsDisappear )
//    { pChar->SetDisappearTime( pMonsterConfig->dwDisappearTime ); }
//    pChar->SetBodySize        ( pMonsterConfig->fBodyLengthSize      ); // ���������С
//    pChar->SetDeadScript      ( pMonsterConfig->GetDeadScript()      );
//    pChar->LoadLuaScript      ( pMonsterConfig->GetAILuaScript()     );    
//    pChar->SetLevel           ( pMonsterConfig->stLevel              ); // ���õȼ�
//    pChar->SetRewardExp       ( pMonsterConfig->nRewardExp           ); // ���ÿɻ�õľ���
//    pChar->SetKillSkillExp    ( pMonsterConfig->nSuperfluitySkillExp );
//    pChar->SetRewardReputation( pMonsterConfig->nRewardReputation    );
//    pChar->SetRewardExpolit   ( pMonsterConfig->nRewardExploit       );
//    pChar->SetRewardFriendly  ( pMonsterConfig->nRewardFriendly      );   
//    pChar->SetRewardDaoxing   ( pMonsterConfig->nRewardDaoxing       );
//    pChar->SetDaoxing         ( pMonsterConfig->nDaoxing             );
//    pChar->nMaxRange            = pMonsterConfig->nMaxRange       ;
//    pChar->changePassiveConfig  = pMonsterConfig->nChangePassive  ;
//    pChar->endPassiveTimeConfig = pMonsterConfig->nPassiveTime    ;
//    pChar->m_nBaseEnmityRange   = pMonsterConfig->nBaseEnmityRange;
//
//    pChar->SetFightModulus( pMonsterConfig->fAttackPhysicsMod, pMonsterConfig->fDefendPhysicsMod, pMonsterConfig->fAttackMagicMod, pMonsterConfig->fDefendMagicMod );
//    //pChar->SetAttackFloat ( pMonsterConfig->sAttackFloating );
//
//    pChar->SetHPMax( pMonsterConfig->nHPMax  ); // HPMax
//    pChar->SetMPMax( pMonsterConfig->stMPMax ); // MPMax
//
//    pChar->GetCharFightAttr()->hpRestore    .base = pMonsterConfig->stHPRestore ;
//    pChar->GetCharFightAttr()->mpRestore    .base = pMonsterConfig->stMPRestore ;
//    pChar->GetCharFightAttr()->exact        .base = pMonsterConfig->stExact     ;
//    pChar->GetCharFightAttr()->dodge        .base = pMonsterConfig->stDodge     ;
//    pChar->GetCharFightAttr()->attackPhysics.base = pMonsterConfig->fPhysicAtt  ;
//    pChar->GetCharFightAttr()->attackMagic  .base = pMonsterConfig->fMagicAtt   ;
//    pChar->GetCharFightAttr()->defendPhysics.base = pMonsterConfig->fPhysicDef  ;
//    pChar->GetCharFightAttr()->defendMagic  .base = pMonsterConfig->fMagicDef   ;
//    pChar->GetCharFightAttr()->critical     .base = pMonsterConfig->critical    ;
//    pChar->GetCharFightAttr()->tenacity     .base = pMonsterConfig->tenacity    ;
//    pChar->GetCharFightAttr()->criticalIntensity  .base = pMonsterConfig->criticalIntensity ;
//    pChar->GetCharFightAttr()->attackSpeed  .base = pMonsterConfig->stAttackRate;
//    pChar->SetViewSight        ( pMonsterConfig->stView      );
//    pChar->SetIdleMoveViewSight( pMonsterConfig->stView      );
//    pChar->SetFightViewSight   ( pMonsterConfig->stFightView );
//
//    // �ƶ��ٶ�
//    if( pMonsterConfig->fIdleMoveSpeed > 1.5f )
//    { pChar->GetCharFightAttr()->moveSpeed.base = 1.5f; }
//    else
//    { pChar->GetCharFightAttr()->moveSpeed.base = pMonsterConfig->fMoveSpeed; }
//
//    pChar->SetNormalMoveSpeed   ( pMonsterConfig->fMoveSpeed      );
//    pChar->SetIdleMoveSpeed     ( pMonsterConfig->fIdleMoveSpeed  );
//    pChar->SetLastMovingSpeed   ( pChar->GetMoveSpeed()           );
//
//    pChar->UpdateCharAllAttibute();
//
//    pChar->SetHP                ( pMonsterConfig->nHPMax          );
//    pChar->SetMP                ( pMonsterConfig->stMPMax         );
//    pChar->SetIdleMoveRate      ( pMonsterConfig->nIdleMoveRate   );
//    pChar->SetCashMoney         ( pMonsterConfig->nCashMoney      );
//    pChar->SetRewardStatusID    ( pMonsterConfig->nRewardStatusID );
//    pChar->SetRewardMulType     ( pMonsterConfig->nRewardMulType  );
//    pChar->SetRewardMulValue    ( pMonsterConfig->nRewardMulValue );
//
//    for ( int i=0; i<ItemDefine::SMonster::MONSTER_SKILL_COUNT; ++i )
//    {
//        pChar->SetSkill     ( i, pMonsterConfig->iSkillID[i]     );
//        pChar->SetSkillLevel( i, pMonsterConfig->stSkillLevel[i] );
//        pChar->SetSkillRate ( i, pMonsterConfig->stSkillRate[i]  );
//    }
//
//    pChar->SetSkillRateTotal();
//    pChar->SetThinkTime   ( 0 );
//
//    // ������ﲻΪ������
//    if (pMonsterConfig->nIsInitiative == 0)
//    { pChar->bPassiveConfig = true;  } // ����Ϊ��������
//    else
//    { pChar->bPassiveConfig = false; }
//
//    pChar->SetPassiveAttack( pChar->bPassiveConfig );     
//    pChar->SetEnmityRate    ( pMonsterConfig->nEnmityRate       );
//    ((MonsterBaseEx*)pChar)->SetEnmity( pMonsterConfig->nEnmity     );
//    pChar->SetResistBeMove  ( pMonsterConfig->nResistMove       );
//    pChar->SetResistBeAtt   ( pMonsterConfig->nResistAtt        );
//    pChar->SetResistBeMagic ( pMonsterConfig->nResistMagic      );
//    pChar->SetResistBeTools ( pMonsterConfig->nResistTools      );    
//    pChar->SetCityMonster   ( pMonsterConfig->bIsCityMonster    );
//    pChar->SetCityDefMonster( pMonsterConfig->bIsCityDefMonster );
//    pChar->SetSkill2LowLimit();
//    pChar->SetSkill3LowLimit();
//    pChar->SetSkillColdDown();
//    pChar->SetMonsterType( pMonsterConfig->stMonsterType );// ��������
//    pChar->SetCountry( country_monster );
//    pChar->StartUpAI(); 
//
//    if (!OnAddCharacter( nID, __FILE__, __LINE__ ) )
//    {
//        LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_ERROR, "CreateMonsterRoute GameStage->CharacterEnter[%s]����", pMonsterConfig->GetName() );
//        OnDelCharacter( nID );
//        theRunTimeData.ReleaseObject( nID );
//        return NULL;
//    }
//
//    return pChar;
//}
//
//MonsterProtectedEx* GameWorld::CreateMonsterProtected( uint32 monsterId, uint32 mapId, float fx, float fy, float fdirx, float fdiry, GameObjectId summonId )
//{ 
//    int index = GettheItemDetail().FindMonsterIndexById( monsterId );
//    if ( index < 0)
//    { return NULL;}
//
//    GameStage* pStage = GetStageById( mapId );
//    if( pStage == NULL || pStage->IsCaracterFull() || !pStage->IsInStage( fx, fy, 0) )
//    { return NULL; }
//
//    ItemDefine::SMonster* pMonsterConfig = GettheItemDetail().GetMonster( index );
//    if( pMonsterConfig == NULL)
//    { return NULL; }
//
//    uint8 nType = Object_MonsterProtected;
//    GameObjectId nID = theRunTimeData.CreateObject( (EObjectType)nType );
//
//    MonsterProtectedEx* pChar = (MonsterProtectedEx*)theRunTimeData.GetCharacterByID(nID);
//    if( pChar == NULL )
//    { return NULL; }
//
//    //����Ĭ��ֵ����
//    pChar->SetFightModulus    ( pMonsterConfig->fAttackPhysicsMod, pMonsterConfig->fDefendPhysicsMod, pMonsterConfig->fAttackMagicMod, pMonsterConfig->fDefendMagicMod);    
//    //pChar->SetAttackFloat     ( pMonsterConfig->sAttackFloating      );
//    pChar->SetMonsterId       ( pMonsterConfig->stMonsterId          );
//    pChar->SetObjType         ( nType                                ); // ��������Ϊ����
//    pChar->SetCanSwitchStage  ( true                                 ); // ����Ϊ�����л�����
//    pChar->SetStatus          ( CS_IDLE                              ); // ���ó�ʼ��״̬Ϊ����
//    pChar->SetCharName        ( pMonsterConfig->GetName()            );
//    pChar->SetMapID           ( mapId                                );
//    pChar->SetProfession      ( pMonsterConfig->stProfession         );
//    pChar->SetModelId         ( pMonsterConfig->iModelID             );
//    pChar->SetBodySize        ( pMonsterConfig->fBodyLengthSize      );
//    pChar->SetDeadScript      ( pMonsterConfig->GetDeadScript()      );
//    pChar->LoadLuaScript      ( pMonsterConfig->GetAILuaScript()     );
//    pChar->SetLevel           ( pMonsterConfig->stLevel              );
//    pChar->SetRewardExp       ( pMonsterConfig->nRewardExp           );
//    pChar->SetKillSkillExp  ( pMonsterConfig->nSuperfluitySkillExp );
//    pChar->SetRewardReputation( pMonsterConfig->nRewardReputation    );
//    pChar->SetRewardExpolit   ( pMonsterConfig->nRewardExploit       );
//    pChar->SetRewardFriendly  ( pMonsterConfig->nRewardFriendly      );
//    pChar->SetRewardDaoxing   ( pMonsterConfig->nRewardDaoxing       );
//    pChar->SetDaoxing         ( pMonsterConfig->nDaoxing             );
//    pChar->nMaxRange          = pMonsterConfig->nMaxRange;
//    pChar->changePassiveConfig   = pMonsterConfig->nChangePassive;
//    pChar->endPassiveTimeConfig     = pMonsterConfig->nPassiveTime;
//    pChar->m_nBaseEnmityRange = pMonsterConfig->nBaseEnmityRange;
//
//    pChar->GetCharFightAttr()->hpRestore    .base = pMonsterConfig->stHPRestore ;
//    pChar->GetCharFightAttr()->mpRestore    .base = pMonsterConfig->stMPRestore ;
//    pChar->GetCharFightAttr()->exact        .base = pMonsterConfig->stExact     ;
//    pChar->GetCharFightAttr()->dodge        .base = pMonsterConfig->stDodge     ;
//    pChar->GetCharFightAttr()->attackPhysics.base = pMonsterConfig->fPhysicAtt  ;
//    pChar->GetCharFightAttr()->attackMagic  .base = pMonsterConfig->fMagicAtt   ;
//    pChar->GetCharFightAttr()->defendPhysics.base = pMonsterConfig->fPhysicDef  ;
//    pChar->GetCharFightAttr()->defendMagic  .base = pMonsterConfig->fMagicDef   ;
//    pChar->GetCharFightAttr()->critical     .base = pMonsterConfig->critical    ;
//    pChar->GetCharFightAttr()->tenacity     .base = pMonsterConfig->tenacity    ;
//    pChar->GetCharFightAttr()->criticalIntensity  .base = pMonsterConfig->criticalIntensity ;
//    pChar->GetCharFightAttr()->attackSpeed  .base = pMonsterConfig->stAttackRate;
//
//    pChar->SetNormalMoveSpeed  ( pMonsterConfig->fMoveSpeed     );
//    pChar->SetIdleMoveSpeed    ( pMonsterConfig->fIdleMoveSpeed );
//    pChar->SetViewSight        ( pMonsterConfig->stView         );
//    pChar->SetIdleMoveViewSight( pMonsterConfig->stView         );
//    pChar->SetFightViewSight   ( pMonsterConfig->stFightView    );
//
//    pChar->GetCharFightAttr()->hpMax        .UpdateFinal();
//    pChar->GetCharFightAttr()->mpMax    .UpdateFinal();
//    pChar->GetCharFightAttr()->hpRestore    .UpdateFinal();
//    pChar->GetCharFightAttr()->mpRestore.UpdateFinal();
//    pChar->GetCharFightAttr()->exact        .UpdateFinal();
//    pChar->GetCharFightAttr()->dodge        .UpdateFinal();
//    pChar->GetCharFightAttr()->attackSpeed  .UpdateFinal();
//    //pChar->GetCharFightAttr()->intonate     .UpdateFinal();
//    pChar->GetCharFightAttr()->moveSpeed    .UpdateFinal();
//    pChar->GetCharFightAttr()->attackPhysics       .UpdateFinal();
//
//    pChar->SetLastMovingSpeed    ( pChar->GetMoveSpeed() );
//
//    for (int i = 0; i < AI_MONSTERMAXSKILLNUM; ++i)
//    {
//        pChar->SetSkill     ( i, pMonsterConfig->iSkillID[i]     );
//        pChar->SetSkillLevel( i, pMonsterConfig->stSkillLevel[i] );
//        pChar->SetSkillRate ( i, pMonsterConfig->stSkillRate[i] );
//    }
//
//    pChar->SetSkillRateTotal();
//    pChar->SetFloatXF( fx );
//    pChar->SetFloatYF( fy );
//    pChar->SetDirX( fdirx );
//    pChar->SetDirY( fdiry );
//    pChar->SetThinkTime( 0 );
//
//    //�ٻ������Ĺֳ�ʼΪ������
//    pChar->bPassiveConfig = true;
//    pChar->SetPassiveAttack( pChar->bPassiveConfig );
//    pChar->SetEnmityRate( pMonsterConfig->nEnmityRate );
//    pChar->SetEnmity    ( pMonsterConfig->nEnmity     );
//    pChar->SetCityMonster   ( false );
//    pChar->SetCityDefMonster( false );
//
//    pChar->nSuperfluitySkillExp = pMonsterConfig->nSuperfluitySkillExp;
//    pChar->nMaxRange = pMonsterConfig->nMaxRange;
//    pChar->changePassiveConfig = pMonsterConfig->nChangePassive;
//    pChar->endPassiveTimeConfig = pMonsterConfig->nPassiveTime;
//    pChar->m_nBaseEnmityRange = pMonsterConfig->nBaseEnmityRange;
//    pChar->SetResistBeMove(pMonsterConfig->nResistMove);
//    pChar->SetResistBeAtt(pMonsterConfig->nResistAtt);
//    pChar->SetResistBeMagic(pMonsterConfig->nResistMagic);
//    pChar->SetResistBeTools(pMonsterConfig->nResistTools);
//
//    if( pMonsterConfig->bIsDisappear )
//    { pChar->SetDisappearTime(pMonsterConfig->dwDisappearTime); }
//    pChar->SetBornPoint     ( SFPos2( fx, fy ) );
//    pChar->SetMonsterType   ( pMonsterConfig->stMonsterType );// ��������
//    pChar->SetSkill2LowLimit();
//    pChar->SetSkill3LowLimit();
//    pChar->SetSkillColdDown ();
//    pChar->SetSummonMasterID( summonId );
//    pChar->SetProtectChar   ( summonId );
//
//    pChar->StartUpAI();
//
//    BaseCharacter* pSummonMasterChar = theRunTimeData.GetCharacterByID( summonId );
//    if( pSummonMasterChar )
//    {
//        pChar->SetCountry( pSummonMasterChar->GetCountry() );
//    }
//
//    pChar->SetHP( pChar->GetHPMax() );
//    pChar->SetMP( pChar->GetMPMax() );
//
//    if( !OnAddCharacter( nID, __FILE__, __LINE__  ) )
//    { // ʵ�ʼ��뵽������
//        LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_ERROR, "MonsterProtected[%s] Fail", pMonsterConfig->GetName() );
//        OnDelCharacter( nID );
//        theRunTimeData.ReleaseObject( nID );
//        return NULL;
//    }
//
//    return pChar;
//}
//
//MonsterTrap* GameWorld::CreateMonsterTrap( uint32 monsterId, uint32 mapId, float fx, float fy, float fdirx, float fdiry, GameObjectId summonId )
//{
//    int index = GettheItemDetail().FindMonsterIndexById( monsterId );
//    if ( index < 0)
//    { return NULL;}
//
//    GameStage* pStage = GetStageById( mapId );
//    if( pStage == NULL || pStage->IsCaracterFull() || !pStage->IsInStage( fx, fy, 0) )
//    { return NULL; }
//
//    ItemDefine::SMonster* pMonsterConfig = GettheItemDetail().GetMonster( index );
//    if( pMonsterConfig == NULL)
//    { return NULL; }
//
//    uint8 nType = Object_MonsterTrap;
//    GameObjectId nID = theRunTimeData.CreateObject( (EObjectType)nType );
//
//    MonsterTrap* pChar = (MonsterTrap*)theRunTimeData.GetCharacterByID(nID);
//    if( pChar == NULL )
//    { return NULL; }
//
//    //����Ĭ��ֵ����
//    pChar->SetFightModulus    ( pMonsterConfig->fAttackPhysicsMod, pMonsterConfig->fDefendPhysicsMod, pMonsterConfig->fAttackMagicMod, pMonsterConfig->fDefendMagicMod);    
//    //pChar->SetAttackFloat     ( pMonsterConfig->sAttackFloating );
//    pChar->SetMonsterId       ( pMonsterConfig->stMonsterId );
//    pChar->SetObjType         ( nType                       ); // ��������Ϊ����
//    pChar->SetCanSwitchStage  ( true                        ); // ����Ϊ�����л�����
//    pChar->SetStatus          ( CS_IDLE                     ); // ���ó�ʼ��״̬Ϊ����
//    pChar->SetCharName        ( pMonsterConfig->GetName()        );
//    pChar->SetMapID           ( mapId                           );
//    pChar->SetProfession      ( pMonsterConfig->stProfession     );
//    pChar->SetModelId         ( pMonsterConfig->iModelID         );
//    pChar->SetBodySize        ( pMonsterConfig->fBodyLengthSize  );
//    pChar->SetDeadScript      ( pMonsterConfig->GetDeadScript()  );
//    pChar->LoadLuaScript      ( pMonsterConfig->GetAILuaScript() );
//    pChar->SetLevel           ( pMonsterConfig->stLevel          );
//    pChar->SetRewardExp       ( pMonsterConfig->nRewardExp       );
//    pChar->SetKillSkillExp  ( pMonsterConfig->nSuperfluitySkillExp );
//    pChar->SetRewardReputation( pMonsterConfig->nRewardReputation    );
//    pChar->SetRewardExpolit   ( pMonsterConfig->nRewardExploit       );
//    pChar->SetRewardFriendly  ( pMonsterConfig->nRewardFriendly      );
//    pChar->SetRewardDaoxing   ( pMonsterConfig->nRewardDaoxing       );
//    pChar->SetDaoxing         ( pMonsterConfig->nDaoxing             );
//    pChar->nMaxRange          = pMonsterConfig->nMaxRange;
//    pChar->changePassiveConfig   = pMonsterConfig->nChangePassive;
//    pChar->endPassiveTimeConfig     = pMonsterConfig->nPassiveTime;
//    pChar->m_nBaseEnmityRange = pMonsterConfig->nBaseEnmityRange;
//
//    pChar->GetCharFightAttr()->hpRestore    .base = pMonsterConfig->stHPRestore ;
//    pChar->GetCharFightAttr()->mpRestore    .base = pMonsterConfig->stMPRestore ;
//    pChar->GetCharFightAttr()->exact        .base = pMonsterConfig->stExact     ;
//    pChar->GetCharFightAttr()->dodge        .base = pMonsterConfig->stDodge     ;
//    pChar->GetCharFightAttr()->attackPhysics.base = pMonsterConfig->fPhysicAtt  ;
//    pChar->GetCharFightAttr()->attackMagic  .base = pMonsterConfig->fMagicAtt   ;
//    pChar->GetCharFightAttr()->defendPhysics.base = pMonsterConfig->fPhysicDef  ;
//    pChar->GetCharFightAttr()->defendMagic  .base = pMonsterConfig->fMagicDef   ;
//    pChar->GetCharFightAttr()->critical     .base = pMonsterConfig->critical    ;
//    pChar->GetCharFightAttr()->tenacity     .base = pMonsterConfig->tenacity    ;
//    pChar->GetCharFightAttr()->criticalIntensity  .base = pMonsterConfig->criticalIntensity ;
//    pChar->GetCharFightAttr()->attackSpeed  .base = pMonsterConfig->stAttackRate;
//
//    pChar->SetNormalMoveSpeed  ( pMonsterConfig->fMoveSpeed     );
//    pChar->SetIdleMoveSpeed    ( pMonsterConfig->fIdleMoveSpeed );
//    pChar->SetViewSight        ( pMonsterConfig->stView         );
//    pChar->SetIdleMoveViewSight( pMonsterConfig->stView         );
//    pChar->SetFightViewSight   ( pMonsterConfig->stFightView    );
//
//    pChar->GetCharFightAttr()->hpMax        .UpdateFinal();
//    pChar->GetCharFightAttr()->mpMax    .UpdateFinal();
//    pChar->GetCharFightAttr()->hpRestore    .UpdateFinal();
//    pChar->GetCharFightAttr()->mpRestore.UpdateFinal();
//    pChar->GetCharFightAttr()->exact        .UpdateFinal();
//    pChar->GetCharFightAttr()->dodge        .UpdateFinal();
//    pChar->GetCharFightAttr()->attackSpeed  .UpdateFinal();
//    //pChar->GetCharFightAttr()->intonate     .UpdateFinal();
//    pChar->GetCharFightAttr()->moveSpeed    .UpdateFinal();
//    pChar->GetCharFightAttr()->attackPhysics       .UpdateFinal();
//
//    pChar->SetLastMovingSpeed    ( pChar->GetMoveSpeed() );
//
//    for (int i = 0; i < AI_MONSTERMAXSKILLNUM; ++i)
//    {
//        pChar->SetSkill( i, pMonsterConfig->iSkillID[i] );
//        pChar->SetSkillLevel( i, pMonsterConfig->stSkillLevel[i] );
//        pChar->SetSkillRate( i, pMonsterConfig->stSkillRate[i] );
//    }
//
//    pChar->SetSkillRateTotal();
//
//    pChar->SetFloatXF( fx );
//    pChar->SetFloatYF( fy );
//    pChar->SetDirX( fdirx );
//    pChar->SetDirY( fdiry );
//    pChar->SetThinkTime( 0 );
//
//    //�ٻ������Ĺֳ�ʼΪ������
//    pChar->bPassiveConfig = true;
//    pChar->SetPassiveAttack(pChar->bPassiveConfig);
//
//    pChar->SetEnmityRate(pMonsterConfig->nEnmityRate);
//    pChar->SetEnmity(pMonsterConfig->nEnmity);
//    pChar->SetCityMonster( false );
//    pChar->SetCityDefMonster( false );
//
//    pChar->nSuperfluitySkillExp = pMonsterConfig->nSuperfluitySkillExp;
//    pChar->nMaxRange = pMonsterConfig->nMaxRange;
//    pChar->changePassiveConfig = pMonsterConfig->nChangePassive;
//    pChar->endPassiveTimeConfig = pMonsterConfig->nPassiveTime;
//    pChar->m_nBaseEnmityRange = pMonsterConfig->nBaseEnmityRange;
//    pChar->SetResistBeMove(pMonsterConfig->nResistMove);
//    pChar->SetResistBeAtt(pMonsterConfig->nResistAtt);
//    pChar->SetResistBeMagic(pMonsterConfig->nResistMagic);
//    pChar->SetResistBeTools(pMonsterConfig->nResistTools);
//
//    if( pMonsterConfig->bIsDisappear )
//    { pChar->SetDisappearTime(pMonsterConfig->dwDisappearTime); }
//
//    pChar->SetBornPoint     ( SFPos2( fx, fy ) );
//    pChar->SetMonsterType   ( pMonsterConfig->stMonsterType );// ��������
//    pChar->SetSkill2LowLimit();
//    pChar->SetSkill3LowLimit();
//    pChar->SetSkillColdDown ();
//    pChar->SetSummonMasterID( summonId );
//    pChar->StartUpAI();
//
//    BaseCharacter* pSummonMasterChar = theRunTimeData.GetCharacterByID( summonId );
//    if( pSummonMasterChar )
//    { pChar->SetCountry( pSummonMasterChar->GetCountry() ); }
//
//    pChar->SetIsPet( true );
//    pChar->SetPetType( EPT_Skill );
//
//    pChar->SetHP( pChar->GetHPMax() );
//    pChar->SetMP( pChar->GetMPMax() );
//
//    if( !OnAddCharacter( nID, __FILE__, __LINE__  ) )
//    { // ʵ�ʼ��뵽������
//        LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_ERROR, "CreateMonsterTrap [%s]fail", pMonsterConfig->GetName() );
//        OnDelCharacter( nID );
//        theRunTimeData.ReleaseObject( nID );
//        return NULL;
//    }
//
//    return pChar;
//}
//
//BaseCharacter* GameWorld::CreateSummonPet( CMonsterProducer::TagMonsterData* pMonsterData, int nMapID, float fx, float fy, float fdirx, float fdiry,  int iProductIndex, GameObjectId shID /* = -1 */, int nInfluence /* = 0 */, int nSummonSkillID /* = -1  */)
//{
//    if ( pMonsterData == NULL )
//    { return NULL; }
//
//    GameStage* pStage = GetStageById( nMapID );
//    if( pStage == NULL || pStage->IsCaracterFull() || !pStage->IsInStage( fx, fy, 0) )
//    { return NULL; }
//
//    ItemDefine::SMonster* pMonsterConfig = GettheItemDetail().GetMonster( pMonsterData->nMonsterIndex );
//    if( pMonsterConfig == NULL)
//    { return NULL; }
//
//    int nID = -1;
//    int nType = Object_MonsterNormal;
//    if( nInfluence != 0  || pMonsterConfig->nMonsterSide > 0 )
//    {
//        nType = Object_MonsterPet;
//        nID = theRunTimeData.CreateObject(Object_MonsterPet);
//    }
//    else
//    {
//        nType = Object_MonsterNormal;
//        nID = theRunTimeData.CreateObject(Object_MonsterNormal);
//    }
//
//    MonsterBaseEx* pChar = (MonsterBaseEx*)theRunTimeData.GetCharacterByID(nID);
//    if( pChar == NULL )
//    { return NULL; }
//
//    pChar->SetHPMax( pMonsterConfig->nHPMax  ); // HPMax
//    pChar->SetMPMax( pMonsterConfig->stMPMax ); // MPMax
//
//    //����Ĭ��ֵ����
//    pChar->SetFightModulus    ( pMonsterConfig->fAttackPhysicsMod, pMonsterConfig->fDefendPhysicsMod, pMonsterConfig->fAttackMagicMod, pMonsterConfig->fDefendMagicMod);    
//    //pChar->SetAttackFloat     ( pMonsterConfig->sAttackFloating );
//    pChar->SetMonsterId       ( pMonsterConfig->stMonsterId );
//    pChar->SetObjType         ( nType                       ); // ��������Ϊ����
//    pChar->SetCanSwitchStage  ( true                        ); // ����Ϊ�����л�����
//    pChar->SetStatus          ( CS_IDLE                     ); // ���ó�ʼ��״̬Ϊ����
//    pChar->SetCharName        ( pMonsterConfig->GetName()        );
//    pChar->SetMapID           ( nMapID                           );
//    pChar->SetProfession      ( pMonsterConfig->stProfession     );
//    pChar->SetModelId         ( pMonsterConfig->iModelID         );
//    pChar->SetBodySize        ( pMonsterConfig->fBodyLengthSize  );
//    pChar->SetDeadScript      ( pMonsterConfig->GetDeadScript()  );
//    pChar->LoadLuaScript      ( pMonsterConfig->GetAILuaScript() );
//    pChar->SetLevel           ( pMonsterConfig->stLevel          );
//    pChar->SetRewardExp       ( pMonsterConfig->nRewardExp       );
//    pChar->SetKillSkillExp  ( pMonsterConfig->nSuperfluitySkillExp );
//    pChar->SetRewardReputation( pMonsterConfig->nRewardReputation    );
//    pChar->SetRewardExpolit   ( pMonsterConfig->nRewardExploit       );
//    pChar->SetRewardFriendly  ( pMonsterConfig->nRewardFriendly      );
//    pChar->SetRewardDaoxing   ( pMonsterConfig->nRewardDaoxing       );
//    pChar->SetDaoxing         ( pMonsterConfig->nDaoxing             );
//    pChar->nMaxRange          = pMonsterConfig->nMaxRange;
//    pChar->changePassiveConfig   = pMonsterConfig->nChangePassive;
//    pChar->endPassiveTimeConfig     = pMonsterConfig->nPassiveTime;
//    pChar->m_nBaseEnmityRange = pMonsterConfig->nBaseEnmityRange;
//
//    pChar->GetCharFightAttr()->hpRestore    .base = pMonsterConfig->stHPRestore ;
//    pChar->GetCharFightAttr()->mpRestore    .base = pMonsterConfig->stMPRestore ;
//    pChar->GetCharFightAttr()->exact        .base = pMonsterConfig->stExact     ;
//    pChar->GetCharFightAttr()->dodge        .base = pMonsterConfig->stDodge     ;
//    pChar->GetCharFightAttr()->attackPhysics.base = pMonsterConfig->fPhysicAtt  ;
//    pChar->GetCharFightAttr()->attackMagic  .base = pMonsterConfig->fMagicAtt   ;
//    pChar->GetCharFightAttr()->defendPhysics.base = pMonsterConfig->fPhysicDef  ;
//    pChar->GetCharFightAttr()->defendMagic  .base = pMonsterConfig->fMagicDef   ;
//    pChar->GetCharFightAttr()->critical     .base = pMonsterConfig->critical    ;
//    pChar->GetCharFightAttr()->tenacity     .base = pMonsterConfig->tenacity    ;
//    pChar->GetCharFightAttr()->criticalIntensity  .base = pMonsterConfig->criticalIntensity ;
//    pChar->GetCharFightAttr()->attackSpeed  .base = pMonsterConfig->stAttackRate;
//    pChar->GetCharFightAttr()->moveSpeed.    base = pMonsterConfig->fMoveSpeed  ;
//
//    pChar->SetNormalMoveSpeed  ( pMonsterConfig->fMoveSpeed     );
//    pChar->SetIdleMoveSpeed    ( pMonsterConfig->fIdleMoveSpeed );
//    pChar->SetViewSight        ( pMonsterConfig->stView         );
//    pChar->SetIdleMoveViewSight( pMonsterConfig->stView         );
//    pChar->SetFightViewSight   ( pMonsterConfig->stFightView    );
//
//    pChar->GetCharFightAttr()->hpMax        .UpdateFinal();
//    pChar->GetCharFightAttr()->mpMax        .UpdateFinal();
//    pChar->GetCharFightAttr()->hpRestore    .UpdateFinal();
//    pChar->GetCharFightAttr()->mpRestore    .UpdateFinal();
//    pChar->GetCharFightAttr()->exact        .UpdateFinal();
//    pChar->GetCharFightAttr()->dodge        .UpdateFinal();
//    pChar->GetCharFightAttr()->attackSpeed  .UpdateFinal();
//    //pChar->GetCharFightAttr()->intonate     .UpdateFinal();
//    pChar->GetCharFightAttr()->moveSpeed    .UpdateFinal();
//    pChar->GetCharFightAttr()->attackPhysics.UpdateFinal();
//
//    pChar->SetLastMovingSpeed    ( pChar->GetMoveSpeed() );
//
//    for (int i = 0; i < AI_MONSTERMAXSKILLNUM; ++i)
//    {
//        pChar->SetSkill( i, pMonsterConfig->iSkillID[i] );
//        pChar->SetSkillLevel( i, pMonsterConfig->stSkillLevel[i] );
//        pChar->SetSkillRate( i, pMonsterConfig->stSkillRate[i] );
//    }
//
//    pChar->SetSkillRateTotal();
//
//    pChar->SetFloatXF( fx );
//    pChar->SetFloatYF( fy );
//    pChar->SetDirX( fdirx );
//    pChar->SetDirY( fdiry );
//    pChar->SetProduceIndex( iProductIndex );
//    pChar->SetThinkTime( pMonsterData->stAiValue );
//    pChar->bPassiveConfig = true; // �ٻ������Ĺֳ�ʼΪ������
//    pChar->SetPassiveAttack(pChar->bPassiveConfig);
//
//    pChar->SetEnmityRate(pMonsterConfig->nEnmityRate);
//    pChar->SetEnmity(pMonsterConfig->nEnmity);
//
//    int nSide = 0;
//    if( nInfluence == -1 )
//    { nSide = pMonsterConfig->nMonsterSide; }
//    else
//    { nSide = nInfluence; }
//
//    pChar->SetCanMoveZone( pMonsterData->rcBron );
//
//    pChar->SetCityMonster( false );
//    pChar->SetCityDefMonster( false );
//
//    pChar->nSuperfluitySkillExp = pMonsterConfig->nSuperfluitySkillExp;
//    pChar->nMaxRange = pMonsterConfig->nMaxRange;
//    pChar->changePassiveConfig = pMonsterConfig->nChangePassive;
//    pChar->endPassiveTimeConfig = pMonsterConfig->nPassiveTime;
//    pChar->m_nBaseEnmityRange = pMonsterConfig->nBaseEnmityRange;
//    pChar->SetResistBeMove(pMonsterConfig->nResistMove);
//    pChar->SetResistBeAtt(pMonsterConfig->nResistAtt);
//    pChar->SetResistBeMagic(pMonsterConfig->nResistMagic);
//    pChar->SetResistBeTools(pMonsterConfig->nResistTools);
//
//    if( pMonsterConfig->bIsDisappear )
//    { pChar->SetDisappearTime(pMonsterConfig->dwDisappearTime); }
//
//    pChar->SetBornPoint     ( SFPos2( fx, fy ) );
//    pChar->SetMonsterType   ( pMonsterConfig->stMonsterType );// ��������
//    pChar->SetSkill2LowLimit();
//    pChar->SetSkill3LowLimit();
//    pChar->SetSkillColdDown ();
//    pChar->SetSummonMasterID( shID );
//    pChar->StartUpAI();
//
//    BaseCharacter* pSummonMasterChar = theRunTimeData.GetCharacterByID(shID);
//    if( pSummonMasterChar )
//    {
//        pChar->SetCountry( pSummonMasterChar->GetCountry() );
//        //if( pSummonMasterChar->IsPlayer() )
//        //{
//        //    GamePlayer* pPlayerChar = (GamePlayer*)pSummonMasterChar;
//        //    pPlayerChar->ApplyPassiveSkillsToPet( nID, nSummonSkillID );
//        //}
//    }
//
//    if ( nSummonSkillID > -1 )
//    {
//        pChar->SetIsPet( true );
//        pChar->SetPetType( EPT_Skill );
//
//        if ( pSummonMasterChar && pMonsterConfig->fMoveSpeed !=0 && pMonsterConfig->fIdleMoveSpeed != 0)
//        {
//            pChar->GetCharFightAttr()->moveSpeed.base = pSummonMasterChar->GetMoveSpeed();
//            pChar->SetNormalMoveSpeed( pSummonMasterChar->GetMoveSpeed() );
//            pChar->SetIdleMoveSpeed( pSummonMasterChar->GetMoveSpeed() );
//        }
//    }
//
//    pChar->SetHP( pChar->GetHPMax() );
//    pChar->SetMP( pChar->GetMPMax() );
//
//    if( !OnAddCharacter( nID, __FILE__, __LINE__  ) )
//    { // ʵ�ʼ��뵽������
//        LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_ERROR, "�������[%s]����", pMonsterConfig->GetName() );
//        OnDelCharacter( nID );
//        theRunTimeData.ReleaseObject( nID );
//        return NULL;
//    }
//
//    return pChar;
//}
//
//MonsterNurturePet* GameWorld::CreateNurturePet( CMonsterProducer::TagMonsterData *pMonsterData, int nMapID, float fx, float fy, float fdirx, float fdiry, int iProductIndex, GameObjectId iMasterID, SPetItem* pPetData )
//{
//    if ( pMonsterData == NULL || pPetData == NULL )
//    { return NULL; }
//
//    BaseCharacter* pSummonMasterChar = theRunTimeData.GetCharacterByID(iMasterID);
//    if( pSummonMasterChar == NULL || !pSummonMasterChar->IsPlayer() )
//    { return NULL; }
//
//    GameStage* pStage = GetStageById( nMapID );
//    if( pStage == NULL || pStage->IsCaracterFull() || !pStage->IsInStage( fx, fy, 0) )
//    { return NULL; }
//
//    ItemDefine::SPetMonster* pMonsterConfig = GettheItemDetail().GetPet( pMonsterData->nMonsterIndex );
//    if( pMonsterConfig == NULL)
//    { return NULL; }
//
//    int nID = theRunTimeData.CreateObject(Object_MonsterNurturePet);
//
//    MonsterNurturePet* pChar = (MonsterNurturePet*)theRunTimeData.GetCharacterByID(nID);
//    if( pChar == NULL )
//    { return NULL; }
//
//    GamePlayer* pGamePlayer = static_cast< GamePlayer* > ( pSummonMasterChar );
//
//    pChar->SetCountry( pSummonMasterChar->GetCountry() );
//
//    // ��ʼ����������
//    pChar->InitPetData( pPetData );
//
//    //����Ĭ��ֵ����
//    pChar->SetFightModulus    ( pMonsterConfig->fAttackPhysicsMod, pMonsterConfig->fDefendPhysicsMod, pMonsterConfig->fAttackMagicMod, pMonsterConfig->fDefendMagicMod);    
//    pChar->SetMonsterId       ( pMonsterConfig->stMonsterId          );
//    pChar->SetObjType         ( Object_MonsterNurturePet             ); // ��������Ϊ������
//    pChar->SetCanSwitchStage  ( true                                 ); // ����Ϊ�����л�����
//    pChar->SetStatus          ( CS_IDLE                              ); // ���ó�ʼ��״̬Ϊ����
//    pChar->SetCharName        ( pMonsterConfig->GetName()            );
//    pChar->SetMapID           ( nMapID                               );
//    pChar->SetProfession      ( pMonsterConfig->stProfession         );
//    pChar->SetModelId         ( pMonsterConfig->iModelID             );
//    pChar->SetBodySize        ( pMonsterConfig->fBodyLengthSize      );
//    pChar->SetDeadScript      ( pMonsterConfig->GetDeadScript()      );
//    pChar->LoadLuaScript      ( pMonsterConfig->GetAILuaScript()     );
//    pChar->SetLevel           ( pPetData->baseInfo.level             );
//    pChar->SetRewardExp       ( pMonsterConfig->nRewardExp           );
//    pChar->SetKillSkillExp    ( pMonsterConfig->nSuperfluitySkillExp );
//    pChar->SetRewardReputation( pMonsterConfig->nRewardReputation    );
//    pChar->SetRewardExpolit   ( pMonsterConfig->nRewardExploit       );
//    pChar->SetRewardFriendly  ( pMonsterConfig->nRewardFriendly      );
//    pChar->SetRewardDaoxing   ( pMonsterConfig->nRewardDaoxing       );
//    pChar->SetDaoxing         ( pMonsterConfig->nDaoxing             );
//
//    pChar->nMaxRange                = pMonsterConfig->nMaxRange;
//    pChar->changePassiveConfig      = pMonsterConfig->nChangePassive;
//    pChar->endPassiveTimeConfig     = pMonsterConfig->nPassiveTime;
//    pChar->m_nBaseEnmityRange       = pMonsterConfig->nBaseEnmityRange;
//
//    pChar->GetCharFightAttr()->hpMax        .base = pPetData->baseInfo.fightAttribute[CharAttr_HPMax]           ;
//    pChar->GetCharFightAttr()->exact        .base = pPetData->baseInfo.fightAttribute[CharAttr_Exact]           ;
//    pChar->GetCharFightAttr()->dodge        .base = pPetData->baseInfo.fightAttribute[CharAttr_Dodge]           ;
//    pChar->GetCharFightAttr()->attackPhysics.base = pPetData->baseInfo.fightAttribute[CharAttr_AttackPhysics]   ;
//    pChar->GetCharFightAttr()->attackMagic  .base = pPetData->baseInfo.fightAttribute[CharAttr_AttackMagic]     ;
//    pChar->GetCharFightAttr()->defendPhysics.base = pPetData->baseInfo.fightAttribute[CharAttr_DefendPhysics]   ;
//    pChar->GetCharFightAttr()->defendMagic  .base = pPetData->baseInfo.fightAttribute[CharAttr_DefendMagic]     ;
//    pChar->GetCharFightAttr()->critical     .base = pPetData->baseInfo.fightAttribute[CharAttr_Critical]        ;
//    pChar->GetCharFightAttr()->tenacity     .base = pPetData->baseInfo.fightAttribute[CharAttr_Tenacity]        ;
//
//    pChar->GetCharFightAttr()->criticalIntensity  .base = pMonsterConfig->criticalIntensity ;
//    pChar->GetCharFightAttr()->hpRestore    .base = pMonsterConfig->stHPRestore ;
//    pChar->GetCharFightAttr()->mpRestore    .base = pMonsterConfig->stMPRestore ;
//    pChar->GetCharFightAttr()->attackSpeed  .base = pMonsterConfig->stAttackRate;
//    pChar->GetCharFightAttr()->moveSpeed.    base = pMonsterConfig->fMoveSpeed  ;
//
//    pChar->SetNormalMoveSpeed  ( pMonsterConfig->fMoveSpeed     );
//    pChar->SetIdleMoveSpeed    ( pMonsterConfig->fIdleMoveSpeed );
//    pChar->SetViewSight        ( pMonsterConfig->stView         );
//    pChar->SetIdleMoveViewSight( pMonsterConfig->stView         );
//    pChar->SetFightViewSight   ( pMonsterConfig->stFightView    );
//
//    pChar->GetCharFightAttr()->hpMax        .UpdateFinal();
//    pChar->GetCharFightAttr()->mpMax        .UpdateFinal();
//    pChar->GetCharFightAttr()->attackPhysics.UpdateFinal();
//    pChar->GetCharFightAttr()->attackMagic  .UpdateFinal();
//    pChar->GetCharFightAttr()->defendPhysics.UpdateFinal();
//    pChar->GetCharFightAttr()->defendMagic  .UpdateFinal();
//    pChar->GetCharFightAttr()->hpRestore    .UpdateFinal();
//    pChar->GetCharFightAttr()->mpRestore    .UpdateFinal();
//    pChar->GetCharFightAttr()->exact        .UpdateFinal();
//    pChar->GetCharFightAttr()->dodge        .UpdateFinal();
//    pChar->GetCharFightAttr()->critical     .UpdateFinal();
//    pChar->GetCharFightAttr()->tenacity     .UpdateFinal();
//    pChar->GetCharFightAttr()->attackSpeed  .UpdateFinal();
//    pChar->GetCharFightAttr()->moveSpeed    .UpdateFinal();
//    pChar->GetCharFightAttr()->attackPhysics.UpdateFinal();
//
//    pChar->SetLastMovingSpeed    ( pChar->GetMoveSpeed() );
//
//    for (int i = 0; i < AI_MONSTERMAXSKILLNUM; ++i)
//    {
//        pChar->SetSkill( i, pMonsterConfig->iSkillID[i] );
//        pChar->SetSkillLevel( i, pMonsterConfig->stSkillLevel[i] );
//        pChar->SetSkillRate( i, pMonsterConfig->stSkillRate[i] );
//    }
//
//    pChar->SetSkillRateTotal();
//
//    pChar->SetFloatXF( fx );
//    pChar->SetFloatYF( fy );
//    pChar->SetDirX( fdirx );
//    pChar->SetDirY( fdiry );
//    pChar->SetProduceIndex( iProductIndex );
//    pChar->SetThinkTime( pMonsterData->stAiValue );
//    pChar->bPassiveConfig = true; // �ٻ������Ĺֳ�ʼΪ������
//    pChar->SetPassiveAttack(pChar->bPassiveConfig);
//
//    pChar->SetEnmityRate(pMonsterConfig->nEnmityRate);
//    //pChar->SetEnmity(pMonsterConfig->nEnmity);
//
//    pChar->SetCanMoveZone( pMonsterData->rcBron );
//
//    pChar->SetCityMonster( false );
//    pChar->SetCityDefMonster( false );
//
//    pChar->nSuperfluitySkillExp = pMonsterConfig->nSuperfluitySkillExp;
//    pChar->nMaxRange = pMonsterConfig->nMaxRange;
//    pChar->changePassiveConfig = pMonsterConfig->nChangePassive;
//    pChar->endPassiveTimeConfig = pMonsterConfig->nPassiveTime;
//    pChar->m_nBaseEnmityRange = pMonsterConfig->nBaseEnmityRange;
//    pChar->SetResistBeMove(pMonsterConfig->nResistMove);
//    pChar->SetResistBeAtt(pMonsterConfig->nResistAtt);
//    pChar->SetResistBeMagic(pMonsterConfig->nResistMagic);
//    pChar->SetResistBeTools(pMonsterConfig->nResistTools);
//
//    if( pMonsterConfig->bIsDisappear )
//    { pChar->SetDisappearTime(pMonsterConfig->dwDisappearTime); }
//
//    pChar->SetBornPoint     ( SFPos2( fx, fy ) );
//    pChar->SetMonsterType   ( pMonsterConfig->stMonsterType );// ��������
//    pChar->SetSkill2LowLimit();
//    pChar->SetSkill3LowLimit();
//    pChar->SetSkillColdDown ();
//    pChar->SetSummonMasterID( iMasterID );
//    pChar->StartUpAI();
//
//    
//    pChar->SetIsPet( true );
//    pChar->SetPetType( EPT_Nurture );
//
//    if ( pSummonMasterChar && pMonsterConfig->fMoveSpeed !=0 && pMonsterConfig->fIdleMoveSpeed != 0)
//    {
//        pChar->GetCharFightAttr()->moveSpeed.base = pSummonMasterChar->GetMoveSpeed();
//        pChar->SetNormalMoveSpeed( pSummonMasterChar->GetMoveSpeed() );
//        pChar->SetIdleMoveSpeed( pSummonMasterChar->GetMoveSpeed() );
//    }
//
//    pChar->SetHP( pPetData->baseInfo.fightAttribute[CharAttr_HPMax] );
//    pChar->SetMP( pMonsterConfig->stMPMax );
//
//    PetSettingConfig::STitle* pTitle = thePetSettingConfig.GetPetTitle( pPetData->baseInfo.savvy, pPetData->baseInfo.growStar, pPetData->baseInfo.aptitudeLevel );
//    if ( pTitle != NULL )
//    { pChar->SetTitleName( pTitle->strTitleName.c_str() ); }
//
//    if( !OnAddCharacter( nID, __FILE__, __LINE__  ) )
//    { // ʵ�ʼ��뵽������
//        LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_ERROR, "�������[%s]����", pMonsterConfig->GetName() );
//        OnDelCharacter( nID );
//        theRunTimeData.ReleaseObject( nID );
//        return NULL;
//    }
//
//    return pChar;
//}
//
////GameStage������Ӱ����
//bool GameWorld::CreateIllusion( CMonsterProducer::TagMonsterData pIllusionInfo, 
//                               float fPosX, float fPosY,
//                               float fDirX, float fDirY, GameObjectId RealityID, GameObjectId& IllusionID )
//{
//    ItemDefine::SMonster* pMonsterData = GettheItemDetail().GetMonster( pIllusionInfo.nMonsterIndex );
//    if( !pMonsterData )
//        return false;
//
//    BaseCharacter *pReality = theRunTimeData.GetCharacterByID(RealityID);
//    if( !pReality )
//    {   
//        return false;
//    }
//
//    int nMapID = pReality->GetMapID();
//    GameStage *pStage = GetStageById( nMapID );
//    if( pStage == NULL )
//    {
//        GetErrorLog()->logString( "Error:Cann't Find the Stage !!( StageID = %d)", nMapID );
//        return false;
//    }
//
//    if( pStage->IsCaracterFull() )
//    {
//        GetErrorLog()->logString("Error: MapId = %d , CreateIllusion Error!, pStage->IsCaracterFull", nMapID );
//        return false;
//    }
//
//    if( fPosX >= TileToFloat(pStage->GetWidth()) || fPosY >= TileToFloat(pStage->GetHeight()))
//    {
//        GetErrorLog()->logString( "Illusion's Pos is Error! ( IllusionPos: x=%f y=%f ----- StageWidth=%d StageHeight=%d )", fPosX, fPosY, pStage->GetWidth(), pStage->GetHeight() );
//        return false;
//    }
//
//    int nID = -1;
//    int nType = Object_MonsterNormal;
//    //if(pMonsterData->nMonsterSide == 0)
//    //{
//    //    nType = Object_MonsterNormal;
//    //    nID = theRunTimeData.CreateObject(Object_MonsterNormal);
//    //}
//    //else
//    //{
//        nType = Object_MonsterPet;
//        nID = theRunTimeData.CreateObject(Object_MonsterPet);
//    //}
//
//    if( nID == -1 )
//    { return false; }
//
//    MonsterBaseEx *pChar = (MonsterBaseEx*)theRunTimeData.GetCharacterByID(nID);
//    if( !pChar )
//    { return false; }
//
//    IllusionID = nID;
//
//    // ����Ϊ�����ɫ
//    pChar->SetIllusionChar( TRUE );
//
//    // ����Ĭ��ֵ����
//    pChar->SetMonsterId( pMonsterData->stMonsterId );        // ���������ID
//    pChar->SetObjType( nType );            // ��������Ϊ����
//    pChar->SetCanSwitchStage( false );                            // ����Ϊ�����л�����
//    pChar->SetStatus( CS_IDLE );                    // ���ó�ʼ��״̬Ϊ����
//
//    // ��ɫ�ĳ���
//    pChar->SetDirX( fDirX );
//    pChar->SetDirY( fDirY );                            
//    pChar->SetCharName( pReality->GetCharName() );            // ���������
//    pChar->SetMapID( nMapID );
//    pChar->SetProfession( pMonsterData->stProfession );
//    pChar->SetModelId( pReality->GetModelId() );
//    //pChar->SetModelId( pMonsterData->iModelID );
//    if( pMonsterData->bIsDisappear )
//    {
//        pChar->SetDisappearTime( pMonsterData->dwDisappearTime );
//    }
//
//    //���������С
//    pChar->SetBodySize( pReality->GetBodySize() );
//    pChar->SetDeadScript( pMonsterData->GetDeadScript() );
//    pChar->LoadLuaScript( pMonsterData->GetAILuaScript() );
//
//    // ���õȼ�
//    pChar->SetLevel( pReality->GetLevel() );
//
//    // ���ÿɻ�õľ���
//    pChar->SetRewardExp         ( pMonsterData->nRewardExp              );
//    pChar->SetKillSkillExp      ( pMonsterData->nSuperfluitySkillExp    );
//    pChar->SetRewardReputation  ( pMonsterData->nRewardReputation       );
//    pChar->SetRewardExpolit     ( pMonsterData->nRewardExploit          );
//    pChar->SetRewardFriendly    ( pMonsterData->nRewardFriendly         );
//    pChar->SetRewardDaoxing     ( pMonsterData->nRewardDaoxing          );
//    pChar->SetDaoxing           ( pMonsterData->nDaoxing                );
//
//    ////////////////////////////////////////
//    pChar->nMaxRange = pMonsterData->nMaxRange;
//    pChar->changePassiveConfig = pMonsterData->nChangePassive;
//    pChar->endPassiveTimeConfig = pMonsterData->nPassiveTime;
//    pChar->m_nBaseEnmityRange = pMonsterData->nBaseEnmityRange;
//
//    //////////////////////////////////////////    
//    pChar->GetCharFightAttr()->hpMax    .base = pReality->GetCharFightAttr()->hpMax.final;      // ���ù�������HP
//    pChar->GetCharFightAttr()->mpMax    .base = pReality->GetCharFightAttr()->mpMax.final;      // ���ù�������MP    
//    pChar->GetCharFightAttr()->hpRestore.base = pReality->GetCharFightAttr()->hpRestore.final;  // ���ù����HP�ָ��ٶ�
//    pChar->GetCharFightAttr()->mpRestore.base = pReality->GetCharFightAttr()->mpRestore.final;  // ���ù����MP�ָ��ٶ�
//    pChar->GetCharFightAttr()->exact    .base = pReality->GetCharFightAttr()->exact.final;      // ���ù���ľ�ȷֵ
//    pChar->GetCharFightAttr()->dodge    .base = pReality->GetCharFightAttr()->dodge.final;      // ���ù���Ļر�
//
//    //���ù���Ĺ�����
//    pChar->GetCharFightAttr()->attackPhysics.base = pReality->GetCharFightAttr()->attackPhysics.final;
//    pChar->GetCharFightAttr()->attackMagic.base = pReality->GetCharFightAttr()->attackMagic.final;
//
//    //���ù���ķ���
//    pChar->GetCharFightAttr()->defendPhysics.base = pReality->GetCharFightAttr()->defendPhysics.final;
//    pChar->GetCharFightAttr()->defendMagic.base = pReality->GetCharFightAttr()->defendMagic.final;
//
//    //���ù�����������
//    pChar->GetCharFightAttr()->attackSpeed.base = pReality->GetCharFightAttr()->attackSpeed.final;//���ù��﹥��Ƶ��
//    //pChar->SetAnkylosisTimeBase( pReality->GetAnkylosisTime()->final ); ////��Ӳʱ��
//    //pChar->GetCharFightAttr()->intonate.final = pReality->GetCharFightAttr()->intonate.final; // �����ٶ�
//
//    // ���ù���Ŀ��ӷ�Χ
//    pChar->SetViewSight( pMonsterData->stView );            //��Ұ
//    pChar->SetIdleMoveViewSight( pMonsterData->stView );
//    pChar->SetFightViewSight( pMonsterData->stFightView );
//    pChar->GetCharFightAttr()->moveSpeed.base=pReality->GetMoveSpeed();
//    pChar->SetNormalMoveSpeed( pReality->GetMoveSpeed() );
//    pChar->SetIdleMoveSpeed( pReality->GetMoveSpeed() );
//
//    //////////////////////////////////////////////
//    pChar->GetCharFightAttr()->hpMax.UpdateFinal();
//    pChar->GetCharFightAttr()->mpMax.UpdateFinal();
//    pChar->GetCharFightAttr()->hpRestore.UpdateFinal();
//    pChar->GetCharFightAttr()->mpRestore.UpdateFinal();
//    pChar->GetCharFightAttr()->exact.UpdateFinal();
//    pChar->GetCharFightAttr()->dodge.UpdateFinal();
//    pChar->GetCharFightAttr()->moveSpeed.UpdateFinal();
//    pChar->GetCharFightAttr()->attackSpeed.UpdateFinal();
//    pChar->GetCharFightAttr()->attackPhysics.UpdateFinal();
//    pChar->GetCharFightAttr()->attackMagic.UpdateFinal();
//    //pChar->GetCharFightAttr()->intonate .UpdateFinal();
//    pChar->GetCharFightAttr()->defendPhysics.UpdateFinal();
//    pChar->GetCharFightAttr()->defendMagic.UpdateFinal();
//
//    pChar->SetLastMovingSpeed ( pChar->GetMoveSpeed() );
//
//    pChar->SetHP( pReality->GetHP() );
//    pChar->SetMP( pReality->GetMP() );
//
//    for (int i = 0; i < AI_MONSTERMAXSKILLNUM; ++i)
//    {
//        pChar->SetSkill( i, pMonsterData->iSkillID[i] );				//���ù��＼��
//        pChar->SetSkillLevel( i, pMonsterData->stSkillLevel[i] );		// ���ù���ļ��ܵȼ�
//        pChar->SetSkillRate( i, pMonsterData->stSkillRate[i] );			// ���ù��＼�ܵ�ʹ�ø���
//    }
//
//    pChar->SetSkillRateTotal();
//
//    pChar->SetFloatXF( fPosX );
//    pChar->SetFloatYF( fPosY );
//    pChar->SetDir( 0 );
//
//    //pChar->SetProduceIndex( iProductIndex );
//    pChar->SetThinkTime( 500 );
//
//    //�����Ƿ�����������
//    pChar->bPassiveConfig = pMonsterData->nIsInitiative;
//    pChar->SetPassiveAttack(pChar->bPassiveConfig);
//
//    pChar->SetEnmityRate( pMonsterData->nEnmityRate );
//    pChar->SetEnmity( pMonsterData->nEnmity );
//    pChar->SetResistBeMove( pMonsterData->nResistMove );
//    pChar->SetResistBeAtt( pMonsterData->nResistAtt );
//    pChar->SetResistBeMagic( pMonsterData->nResistMagic );
//    pChar->SetResistBeTools( pMonsterData->nResistTools );
//
//    ///////////////////////////////
//    RECT rBornZone;
//    int nX = FloatToTile(fPosX);
//    int nY = FloatToTile(fPosY);
//    rBornZone.left = nX - 6;
//    rBornZone.right = nX + 6;
//    rBornZone.top = nY - 6;
//    rBornZone.bottom = nY + 6;
//
//    if( rBornZone.left < 0 )
//        rBornZone.left = 0;
//
//    if( rBornZone.right > pStage->GetWidth() )
//        rBornZone.right = pStage->GetWidth();
//
//    if( rBornZone.top < 0 )
//        rBornZone.top = 0;
//
//    if( rBornZone.bottom > pStage->GetHeight() )
//        rBornZone.bottom = pStage->GetHeight();
//
//    pChar->SetCanMoveZone( rBornZone );
//    /////////////////////////
//
//    // ���ù������λ��
//    SFPos2 ptBornPoint;
//    ptBornPoint.x = fPosX;
//    ptBornPoint.y = fPosY;
//    pChar->SetBornPoint( ptBornPoint );
//    pChar->SetSkill2LowLimit();
//    pChar->SetSkill3LowLimit();
//    pChar->SetSkillColdDown();
//    pChar->SetMonsterType( pMonsterData->stMonsterType );// ��������
//    pChar->SetSummonMasterID( pReality->GetID() );  // ��������ID
//    pChar->StartUpAI();
//    pChar->SetCountry( pReality->GetCountry() );
//
//    pChar->SetIsPet  ( true );
//    pChar->GetCharFightAttr()->moveSpeed.base = pReality->GetMoveSpeed();
//    pChar->SetNormalMoveSpeed( pReality->GetMoveSpeed() );
//    pChar->SetIdleMoveSpeed( pReality->GetMoveSpeed() );
//
//    pChar->SetPetType( EPT_Skill );
//
//    // ʵ�ʼ��뵽������
//    if( !OnAddCharacterOnlyID( nID ) )
//    {        
//        LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_ERROR, "�������[%s]����\n", pMonsterData->GetName() );
//        //ɾ����ɫ
//        OnDelCharacter( nID );
//        theRunTimeData.ReleaseObject( nID );
//        return false;
//    }
//
//    if( !pStage->CharacterEnter( pChar, __FILE__, __LINE__ ) )
//    {
//        LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_ERROR, "GameStage->CharacterEnter[%s]����\n", pMonsterData->GetName() );
//        //ɾ����ɫ
//        OnDelCharacter( nID );
//        theRunTimeData.ReleaseObject( nID );
//        return false;
//    }
//
//    //���õ��䱶��
//    pChar->SetItemDropMultiple( pMonsterData->fItemDropMultipleRate );
//    pChar->SetDead( false );
//    return true;
//}

// void GameWorld::RefreshMonster(void*)
// {
//     //��������
//     //CSALocker locker(refmonsterlock_cs);
//     ItrGameStageContainer iter = theGameWorld.m_mapGameStage.begin();
//     ItrGameStageContainer end = theGameWorld.m_mapGameStage.end();
//     for ( ; iter != end; ++iter)
//     {
//         GameStage *pStage = iter->second;
//         if (pStage != NULL)
//         {
//             pStage->RefreshMonster();
//         }
//     }
// }

CEffectChar* GameWorld::CreateEffectChar( BaseCharacter* pCharCaster,const char* szName ,int nMapID ,int iSkillID, int iSkillLevel, float nX, float nY)
{
    //return NULL;

    ItemDefine::SItemSkill *pSkill = GettheItemDetail().GetSkillByID(iSkillID, iSkillLevel);
    if (!pSkill)
        return NULL;

    int nID = theRunTimeData.CreateObject( Object_Effect );
    if( -1 == nID )
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "���� ħ��Ч��ʧ�� [%s]", szName );
        return NULL;
    }

    CEffectChar* pChar = (CEffectChar*)theRunTimeData.GetCharacterByID( nID );
    if( !pChar )
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "�õ� ħ��Ч��ʧ�� [%d]", nID );
        return NULL;
    }

    pChar->SetMapID(nMapID);
    pChar->SetFloatXF( nX);
    pChar->SetFloatYF( nY);
    pChar->SetCanSwitchStage( false );

	pChar->Init(pCharCaster,iSkillID, iSkillLevel);
	pChar->SetDead( false );

    if( !OnAddCharacter( nID, __FILE__, __LINE__  ) )
    {
        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "ħ��Ч��[%d]���뵽��Ϸ����ʱʧ��",nID );
        OnDelCharacter( nID );
        theRunTimeData.ReleaseObject( nID, __FILE__, __LINE__ );
        return 0;
    }

    return pChar;
}

ItemCharacter* GameWorld::CreateItemNpc( const char *szItem
                                        ,int nMapID
                                        ,float fX, float fY, int nDir
                                        ,SCharItem &item,
                                        short stMasterNpc, unsigned char ucBornDelay,
                                        bool bTilePos )
{
    // ToLog( szItem );
    ItemDefine::SItemCommon *pItem = NULL;
    pItem = GettheItemDetail().GetItemByName( ( char *)szItem );
    if( !pItem )
        return NULL;
    if( item.itembaseinfo.ustItemID == InvalidLogicNumber )
        return NULL;
    if ( !pItem->IsExclusive())
    {
        if( 0 == item.itembaseinfo.ustItemCount )
            return NULL;
    }
    ItemCharacter *pChar = NULL;
    GameObjectId  nID; 
    nID = theRunTimeData.CreateObject( Object_Item );
    if( nID == -1 )
    {
        return NULL;
    }
    pChar = (ItemCharacter*)theRunTimeData.GetCharacterByID(nID);
    if( !pChar )
    {
        return NULL;
    }
    //
    pChar->SetMasterID(stMasterNpc);
    //
    pChar->SetObjType( Object_Item );
    //pChar->SetCurArea( 0 );                           // ��ǰ���������ʼ��Ϊ0
    pChar->SetCanSwitchStage( false );                  // ����Ϊ�����л�����
    pChar->SetStatus( CS_IDLE );           // ���ó�ʼ��״̬Ϊ����
    pChar->SetMapID( nMapID );
    pChar->SetItem( item );
    if ( bTilePos == true )
    {
        pChar->SetFloatXF( fX );
        pChar->SetFloatYF( fY );
    }
    else
    {
        pChar->SetFloatXF( fX );
        pChar->SetFloatYF( fY );
    }
    pChar->SetDir( nDir );
    pChar->SetBornDelay( ucBornDelay );
    // ʵ�ʼ��뵽������
    if( !OnAddCharacter( nID, __FILE__, __LINE__  ) )
    {
        //ɾ����ɫ        
        OnDelCharacter( nID );
        theRunTimeData.ReleaseObject( nID , __FILE__, __LINE__);
        return NULL;
    }

    //LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_DEBUG, "������Ʒ[%s] ������ = [%d] ��ǰ���� = [%04d] λ�� = (%d,%d,%d)" 
    //    ,szItem
    //    ,pChar->GetMapID()
    //    ,pChar->GetCurArea()
    //    ,pChar->GetX()
    //    ,pChar->GetY()
    //    ,pChar->GetDir() );


    pChar->SetDead( false );
    return pChar;
}

ItemCharacter* GameWorld::CreateItemPackageNpc(uint16 stItemID, unsigned long nMapID, float fX, float fY, int nDir, 
                                               DropItemVector& vecDropItem, DropCharItemVector& vecCharItem, unsigned long dwTeamSessionID, unsigned long dwPlayerID, 
                                               SCharItem &item, unsigned char ucBornDelay)
{
    if ( vecDropItem.empty() && vecCharItem.empty() )
    { return NULL;}

    ItemDefine::SItemCommon* pItem = GettheItemDetail().GetItemByID( stItemID );
    if( pItem == NULL)
    { return NULL; }

    if( item.itembaseinfo.ustItemID == InvalidLogicNumber )
    { return NULL; }

    if ( !pItem->IsExclusive() )
    {
        if( 0 == item.itembaseinfo.ustItemCount )
            return NULL;
    }

    int nID = theRunTimeData.CreateObject( Object_Item );
    if( nID == -1 ) 
    { return NULL; }

    ItemCharacter* pItemChar = (ItemCharacter*) theRunTimeData.GetCharacterByID( nID );
    if( pItemChar == NULL )
    { return NULL; }

    pItemChar->SetObjType( Object_Item );
    pItemChar->SetDead( false );
    pItemChar->SetCanSwitchStage( false ); // ����Ϊ�����л�����
    pItemChar->SetStatus( CS_IDLE );       // ���ó�ʼ��״̬Ϊ����
    pItemChar->SetMapID( nMapID );
    pItemChar->SetItem( item );
    pItemChar->SetFloatXF( fX );
    pItemChar->SetFloatYF( fY );
    pItemChar->SetDir( nDir );
    pItemChar->SetBornDelay( ucBornDelay );

    if ( dwTeamSessionID == InvalidLogicNumber && dwPlayerID == InvalidLogicNumber )    // ����������
    {
        pItemChar->SetPackageHoldType( eIHT_All );
    }

    //���� ������Ȩ������
    uint32 dwAssignPlayerDBID = -1;                 // ��ǰ��������Ķ�ԱID
    ItemCharacter::CharIdContainer vecTeamMemberID; // ������Ч���ID

    //��Ҷ���
    GameTeam* pTeam = NULL;
    if ( !pItemChar->IsPackageHoldByAll() )     // ���ǹ�����������
    {
        pTeam = theGameTeamManager.GetTeam( dwTeamSessionID );
        if ( pTeam != NULL )                      // ����ж���,�����Ƕ��������߶ӳ�����ģʽ, �Ȼ�õ�ǰ����Ķ�ԱID
        {
            switch( pTeam->GetTeamAssignModeType() )
            {
            case AssignMode_FreeMode:           // ���ɷ���
                break;
            case AssignMode_Random:             // �漴����
            case AssignMode_Team:               // �������
            case AssignMode_Assign:             // �ӳ�����
                {
                    int nLoopCount = 0;
                    while( nLoopCount < pTeam->TeamMemberCount() )
                    {
                        uint32 dwTeamMember = pTeam->GetCurrentAssignTeamMemberID();
                        GamePlayer* pTeamPlayer = theRunTimeData.GetGamePlayerByDBID( dwTeamMember );

                        if ( pTeamPlayer == NULL || !pTeamPlayer->IsPlayer() || !pTeamPlayer->IsInMapArea( nMapID, fX, fY, TEAM_EXP_DIS) )
                        {
                            ++nLoopCount;
                            continue;
                        }

                        dwAssignPlayerDBID = dwTeamMember;          //�з���Ҫ���,break
                        break;
                    }
                }
                break;
            default:
                dwAssignPlayerDBID = dwPlayerID;
                break;
            }

            //�����Ч���ID
            pTeam->GetTeamMemberInMapArea( nMapID, fX, fY, vecTeamMemberID );
        }
    }

    bool bHasTeamQualityItem = false;           // �Ƿ��ж���Ʒ�����ϵ���Ʒ

    //�ȼ��������Ʒ��������
    DropItemVectorIter miter = vecDropItem.begin();
    DropItemVectorIter mend  = vecDropItem.end();
    for ( ; miter != mend; ++miter )
    {
        SCharItem item;
        if( !theRunTimeData.CreateItem( NULL, miter->nItemId, 1, HelperFunc::CreateID(), item ) )
        {
            LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "������Ʒʧ��[%u]����[%u]", miter->nItemId, 1 ); 
            continue;
        }

        // �Ƿ��
        item.SetBounded( miter->bIsBound );

        // �����Ǽ�װ��
        item.SetStarLevel( miter->bStarRandom , miter->nStarLevel );

		theRunTimeData.EquipScore(item, GettheItemDetail().GetItemByID( item.itembaseinfo.ustItemID )); // ����װ������

        pItemChar->AddCharItem( item );
    }

    // ��������ϵ������Ʒ
    DropCharItemVectorIter viter = vecCharItem.begin();
    DropCharItemVectorIter vend  = vecCharItem.end();
    for ( ; viter != vend; ++viter )
    {
        if ( viter->itembaseinfo.ustItemCount > 1 && pTeam != NULL && pTeam->GetTeamAssignModeType() != AssignMode_FreeMode )
        {
            ItemDefine::SItemCommon* pItem = GettheItemDetail().GetItemByID( viter->itembaseinfo.ustItemID );
            if ( pItem != NULL && pItem->ustLevel >= pTeam->GetTeamAssignItemLevel() && !pItem->IsExclusive() )
            {
                for ( int i = 0; i < viter->itembaseinfo.ustItemCount; ++i )
                {
                    SCharItem item;
                    if( !theRunTimeData.CreateItem( NULL, viter->itembaseinfo.ustItemID, 1, HelperFunc::CreateID(), item) )
                    {
                        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "������Ʒʧ��[%u]����[%u]", viter->itembaseinfo.ustItemID, 1 ); 
                        continue;
                    }
                    pItemChar->AddCharItem( item );
                }
                continue;
            }
        }

        pItemChar->AddCharItem( *viter );
    }

    if ( !pItemChar->IsPackageHoldByAll() )
    {
        int nItemCount = pItemChar->GetCharItemCount();
        for ( int i = 0; i < nItemCount; ++i )
        {
            SCharItem* pCharItem = pItemChar->GetCharItemByIndex( i );
            if ( pCharItem == NULL )
            { continue; }

            if (pTeam == NULL)          //û�ж���
            {
                pItemChar->SetItemPickLevel( pCharItem->itembaseinfo.nOnlyInt, dwPlayerID, eIPL_View | eIPL_Pick | eIPL_Hold );
            }
            else
            {
                int nTeamCount = pTeam->TeamMemberCount();
                switch( pTeam->GetTeamAssignModeType() )
                {
                case AssignMode_FreeMode:       // ���ɷ���
                    {
                        ItemCharacter::CharIdContainer::iterator iter = vecTeamMemberID.begin();
                        ItemCharacter::CharIdContainer::iterator end  = vecTeamMemberID.end();
                        for ( ; iter != end; ++iter)
                        {
                            pItemChar->SetItemPickLevel( pCharItem->itembaseinfo.nOnlyInt, (*iter), eIPL_View | eIPL_Pick );
                        }
                    }
                    break;
                case AssignMode_Random:             // �漴����
                case AssignMode_Team:               // �������
                    {
                        pItemChar->SetPackageHoldPlayerID(dwAssignPlayerDBID);

                        ItemDefine::SItemCommon* pItem = GettheItemDetail().GetItemByID( pCharItem->itembaseinfo.ustItemID );
                        if ( pItem != NULL && pItem->ustLevel >= pTeam->GetTeamAssignItemLevel() )
                        {
                            ItemCharacter::CharIdContainer::iterator iter = vecTeamMemberID.begin();
                            ItemCharacter::CharIdContainer::iterator end  = vecTeamMemberID.end();
                            for ( ; iter != end; ++iter)
                            {
                                //�����ڶ������Ʒ��ʱ,�����Ʒ��Ҫ��ɸ������������, ����ֻ���鿴Ȩ��
                                pItemChar->SetItemPickLevel( pCharItem->itembaseinfo.nOnlyInt, (*iter), eIPL_View );
                            }

                            pItemChar->AddPolishItem( pCharItem->itembaseinfo.nOnlyInt );
                            pItemChar->SetPackageAssignType( pTeam->GetTeamAssignModeType() );
                            pItemChar->SetPackagePolistDeathTime();
                            bHasTeamQualityItem = true;
                        }
                        else
                        {
                            ItemCharacter::CharIdContainer::iterator iter = vecTeamMemberID.begin();
                            ItemCharacter::CharIdContainer::iterator end  = vecTeamMemberID.end();
                            for ( ; iter != end; ++iter)
                            {
                                if ( *iter == dwAssignPlayerDBID )
                                {
                                    pItemChar->SetItemPickLevel( pCharItem->itembaseinfo.nOnlyInt, (*iter), eIPL_View | eIPL_Pick );
                                }
                                else
                                {
                                    //�Ȳ�����Ȩ��, �ȷ���Ķ�Ա�鿴�����Ժ�,������Ӧ��Ȩ��
                                    pItemChar->SetItemPickLevel( pCharItem->itembaseinfo.nOnlyInt, (*iter), eIPL_View | eIPL_Pick/*eIPL_Nothing*/ );        
                                }
                            }
                        }
                    }
                    break;
                case AssignMode_Assign:         // �ӳ�����
                    {
                        pItemChar->SetPackageHoldPlayerID( dwAssignPlayerDBID );

                        ItemDefine::SItemCommon* pItem = GettheItemDetail().GetItemByID( pCharItem->itembaseinfo.ustItemID );
                        if ( pItem != NULL && pItem->ustLevel >= pTeam->GetTeamAssignItemLevel() )
                        {
                            ItemCharacter::CharIdContainer::iterator iter = vecTeamMemberID.begin();
                            ItemCharacter::CharIdContainer::iterator end  = vecTeamMemberID.end();
                            for ( ; iter != end; ++iter)
                            {
                                if (pTeam->IsTeamHeader(*iter)) // �ӳ��з���Ȩ�� �ɶӳ�������Ʒ����Ʒ����
                                {
                                    pItemChar->SetItemPickLevel( pCharItem->itembaseinfo.nOnlyInt, (*iter), eIPL_View | eIPL_Assign );
                                }
                                else
                                {
                                    //���Ƕӳ��в鿴Ȩ��
                                    pItemChar->SetItemPickLevel( pCharItem->itembaseinfo.nOnlyInt, (*iter), eIPL_View );
                                }
                            }
                            pItemChar->AddPolishItem(pCharItem->itembaseinfo.nOnlyInt);  
                            pItemChar->SetPackageAssignType(pTeam->GetTeamAssignModeType());
                            pItemChar->SetPackageAssignTeamHeaderID(pTeam->GetTeamHeaderID());
                            pItemChar->SetPackagePolistDeathTime();
                            bHasTeamQualityItem = true;
                        }
                        else
                        {
                            ItemCharacter::CharIdContainer::iterator iter = vecTeamMemberID.begin();
                            ItemCharacter::CharIdContainer::iterator end  = vecTeamMemberID.end();
                            for ( ; iter != end; ++iter )
                            {
                                if ( *iter == dwAssignPlayerDBID )
                                {
                                    pItemChar->SetItemPickLevel( pCharItem->itembaseinfo.nOnlyInt, (*iter), eIPL_View | eIPL_Pick );
                                }
                                else
                                {
                                    //�Ȳ�����Ȩ��, �ȷ���Ķ�Ա�鿴�����Ժ�,������Ӧ��Ȩ��
                                    pItemChar->SetItemPickLevel( pCharItem->itembaseinfo.nOnlyInt, (*iter), eIPL_View | eIPL_Pick/*eIPL_Nothing*/ );        
                                }
                            }
                        }
                    }
                    break;
                default:
                    pItemChar->SetItemPickLevel( pCharItem->itembaseinfo.nOnlyInt, dwPlayerID, eIPL_View | eIPL_Pick );
                }
            }
        }


        //�жϰ�����Ȩ�����
        if ( pTeam == NULL )          //û�ж���
        {
            pItemChar->SetItemPackageAccess( dwPlayerID, eIPL_View );
        }
        else
        {
            //�ж϶������ģʽ,   
            // ���� == ���ж�Ա�в鿴��ʰȡȨ   
            // ���� == ֻ��Ʒ��������Ʒ����ʱ,���ж�Ա�в鿴Ȩ, ����ʼ��ɸ����������Ʒ����, ����ֻ�з��䵽�Ķ�Ա�в鿴Ȩ��ʰȡȨ
            // �ӳ� == ֻ��Ʒ��������Ʒ����ʱ,���ж�Ա�в鿴Ȩ, ���ɶӳ�����Ʒ����Ʒ��˭, ����ֻ��ϵͳ����Ķ�Ա��Ȩ��
            switch ( pTeam->GetTeamAssignModeType() )
            {
            case AssignMode_FreeMode:               // ���ɷ���, ÿ����Ч��Ա���ܿ�
                {
                    ItemCharacter::CharIdContainer::iterator iter = vecTeamMemberID.begin();
                    ItemCharacter::CharIdContainer::iterator end  = vecTeamMemberID.end();
                    for ( ; iter != end; ++iter)
                    {
                        pItemChar->SetItemPackageAccess( *iter, eIPL_View );
                    }
                }
                break;
            case AssignMode_Random:             
            case AssignMode_Team:
            case AssignMode_Assign:
                {
                    if ( bHasTeamQualityItem )                //�з���Ʒ��������Ʒ
                    {
                        ItemCharacter::CharIdContainer::iterator iter = vecTeamMemberID.begin();
                        ItemCharacter::CharIdContainer::iterator end  = vecTeamMemberID.end();
                        for ( ; iter != end; ++iter)
                        {
                            pItemChar->SetItemPackageAccess( *iter, eIPL_View );
                        }
                    }
                    else
                    {
                        ItemCharacter::CharIdContainer::iterator iter = vecTeamMemberID.begin();
                        ItemCharacter::CharIdContainer::iterator end  = vecTeamMemberID.end();
                        for ( ; iter != end; ++iter )
                        {
                            if ( *iter == dwAssignPlayerDBID )
                            {
                                pItemChar->SetItemPackageAccess( *iter, eIPL_View );
                            }
                            else
                            {
                                pItemChar->SetItemPackageAccess( *iter, /*eIPL_Nothing*/eIPL_View );        //�ȼӵ��б���
                            }
                        }
                    }
                }
                break;
            default:
                pItemChar->SetItemPackageAccess( dwPlayerID, eIPL_View );
            }
        }

        //��������������ʼ��ʱ, ����ʱ��, ������Ч���Ҳ�ܻ��ʰȡȨ��(���˵İ����������޷����)
        if ( vecDropItem.size() > 1 && dwAssignPlayerDBID != -1 )
        {
            pItemChar->SetPackageFristViewTimeOut( HQ_TimeGetTime() + ItemCharacter::PackageViewTimeOut );
        }
    }


    // ʵ�ʼ��뵽������
    if( !OnAddCharacter( nID, __FILE__, __LINE__  ) )
    {
        //ɾ����ɫ        
        OnDelCharacter( nID );
        theRunTimeData.ReleaseObject( nID, __FILE__, __LINE__ );
        return NULL;
    }

    return pItemChar;
}

//char g_DebugShowCharListInfoBuffer[GameWorld::constMaxCharacters][1024];
// static DWORD g_DebugShowCharListStartTime = 0;
// 
// void GameWorld::DebugShowCharListInfo(bool bRefreshNow)
// {   
//     if( (HQ_TimeGetTime() - g_DebugShowCharListStartTime < 1000 + GetObjectSize()*10) && !bRefreshNow )
//     { return; }
// 
//     g_DebugShowCharListStartTime =HQ_TimeGetTime();
// 
//     char TempStatusStr[256] = { 0 };
// 
//     DWORD dwot = HQ_TimeGetTime();
// 
//     GameObjectId objectId = InvalidGameObjectId;
//     for ( uint32 currentIndex = 0; (objectId = GetNextObjectBId( 0 == currentIndex )) != InvalidGameObjectId; ++currentIndex )
//     {
//         BaseCharacter* pChar = theRunTimeData.GetCharacterByID( objectId );
//         if ( pChar == NULL || !pChar->IsPlayer() )
//         { continue; }
// 
//         if( pChar->m_ExtendStatus.m_fsExtend < CharacterTimeStatus::efs_Normal || pChar->m_ExtendStatus.m_fsExtend >= CharacterTimeStatus::efs_StatusMax )
//         { strncpy_s(TempStatusStr, sizeof( TempStatusStr ), "Error", sizeof(TempStatusStr)-1); }
//         else
//         { sprintf_s(TempStatusStr, sizeof(TempStatusStr)-1, "Status_ID ::[%d]", pChar->m_ExtendStatus.m_fsExtend); }
// 
//         //           sprintf(g_DebugShowCharListInfoBuffer[j],
//         //"%d:[%s] hp:[%d/%d] Map:[%d] Pos:(%d,%d) PathLen:(%d) PathCur:(%d) MoveRate:(%f) Status:[%s] TimerLeft[%d]"
//         //               "Status:[%d] Level:[%d] Mp:[%d/%d] [h%dd%dma%dmd%dpa%dppd%d] [ModeID=%d]",
//         //               pChar->GetControl()->GetID(), pChar->GetCharName(),
//         //               (int)pChar->GetHP(),(int)pChar->GetHPMax(),
//         //               pChar->GetMapID(),
//         //               pChar->GetX(), pChar->GetY(),
//         //pChar->GetWalkPathLen(),
//         //pChar->GetWalkPathCurPos(),
//         //pChar->GetMoveSpeed(),
//         //               TempStatusStr,
//         //               (int)pChar->m_ExtendStatus.m_fsExtendTimer.TimeLeft(),
//         //               pChar->GetStatus(),
//         //               pChar->GetLevel(),
//         //               (int)pChar->GetMP(),(int)pChar->GetMPMax(),
//         //               pChar->GetHit(),
//         //               //���ջر���
//         //               pChar->GetDodge(),
//         //               //����ħ��������
//         //               pChar->GetMagicAtt(),
//         //               //����ħ��������
//         //               pChar->GetMagicDef(),
//         //               //������������
//         //               pChar->GetPhysicAtt(),
//         //               //�������������
//         //               pChar->GetPhysicDef(),
//         //               pChar->GetModelId()
//         //               );
//     }
//     dwot = HQ_TimeGetTime() - dwot;
// }

void GameWorld::MoveRoleToSafePosAndExit( BaseCharacter *pChar )
{
    if( pChar == NULL || !pChar->IsPlayer() )
    { return; }
    
    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );

    MapConfig::MapData* pMapData = pPlayer->GetMapData();
    if ( pMapData == NULL )
    { return; }
    
    // �������ĵ�ͼID
    pPlayer->SetLastMapID( pPlayer->GetMapID() );
    //����ɫ�͵���ȷ�ĳ���
    MapConfig::RelivePosition* pRelivePosition = pMapData->GetRelivePositionByState( false );
    if ( pRelivePosition != NULL )
    {
        pPlayer->SetMapID( pRelivePosition->MapId );
        pPlayer->SetFloatXF( pRelivePosition->PositionX );
        pPlayer->SetFloatYF( pRelivePosition->PositionY );
        pPlayer->SetFloatZ( WORLD_HEIGHT );
    }
    else
    {
        const CountryConfig::BornMapSetting* pSetting = theCountryConfig.GetBornMapSetting( pChar->GetCountry() );
        if ( pSetting != NULL )
        {
            pPlayer->SetMapID( pSetting->GetMapID() );
            pPlayer->SetFloatXF( pSetting->GetPosX() );
            pPlayer->SetFloatYF( pSetting->GetPosY() );
            pPlayer->SetFloatZ( WORLD_HEIGHT );
        }
    }
    
    // ����ֱ���ˣ������CricrilError����run,����������
    pPlayer->OnExit( NULL );
}

void GameWorld::AutoSave(void* p)
{
    if ( g_Cfg.dwServerID == CHARACTERSERVERID )
    { return;}

    static uint32 dwLastTime = HQ_TimeGetTime(); // �ϴ��ռ���ʱ��
    static std::list<uint32> s_SaveList;

    // ÿ����ѭֻ����10���������
    uint32 nSaveCount = 0;
    while (!s_SaveList.empty() && nSaveCount < nSaveBatchNum)
    {
        uint32 dwID = s_SaveList.front();
        s_SaveList.pop_front();
        BaseCharacter* pChar = theRunTimeData.GetCharacterByID(dwID);
        if (pChar && pChar->IsPlayer())
        {
            GamePlayer* pGamePlayer = (GamePlayer*)pChar;
            if ( pGamePlayer->IsCanSaveToDB())
            {
                GettheFileDB().SaveCharAllData( pGamePlayer, EST_Time );
                ++nSaveCount;
            }
        }
    }

    // һ���Ա����������� ���ʱ�䵽�˻���NowSave��ǿ�Ʊ���
    bool bIsNeedPush = false;
    if ( s_SaveList.empty() )
    { bIsNeedPush = true; }

    uint32 dwCurrTime = HQ_TimeGetTime();
    if ( dwCurrTime - dwLastTime >= g_Cfg.dwAutoSaveDelay || theRunTimeData.g_bNowSave)
    {
        theRunTimeData.g_bNowSave = false;
        uint32 nNum = 0;

        if (bIsNeedPush)
        {
            for (int i=0; i<dr_worldMaxPlayers; ++i)
            {
                BaseCharacter* pChar = theRunTimeData.GetCharacterByID(i);
                if (pChar && pChar->IsPlayer())
                {
                    s_SaveList.push_back(i);
                    ++ nNum;
                }
            }
            LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_INFO, "��� %d ����ɫ����Ҫ�������", nNum );
        }

        //GetScriptVarMgr()->SaveVar();
        //GetShopMgr()->SaveData();
        //GetBankMgr()->SaveData();        
        //g_dbchunk.SaveOnlineInfoToDB(nNum);
        //char szFilePath[512] = {0};
        //sprintf_s( szFilePath, "%s%s-%s", OUTPUT_DIRECTORY, DATACHUNK_FILEPATH, g_Cfg.szGameServerName );
        //GetDataChunkMgr()->SaveToFile( szFilePath );
        dwLastTime = HQ_TimeGetTime();            
    }
}

static const uint32 querySaveTimeFrequency = 1000 * 60; // һ����

void GameWorld::AutoSaveUpdate()
{
    if ( g_Cfg.dwServerID == CHARACTERSERVERID)
    { return;}

    static uint32 dwLastTime = HQ_TimeGetTime(); // �ϴ��ռ���ʱ��
    static std::list<uint32> saveList;

    uint32 nLeaveCount = saveList.size();
    if ( GameTime::IsPassCurrentTime( dwLastTime, querySaveTimeFrequency )|| theRunTimeData.g_bNowSave)
    {
        theRunTimeData.g_bNowSave = false;

        uint32 nNum = 0;
        for (int i=0; i<dr_worldMaxPlayers; ++i)
        {
            BaseCharacter* pChar = theRunTimeData.GetCharacterByID(i);
            if (pChar && pChar->IsPlayer())
            {
                GamePlayer* pGamePlayer = (GamePlayer*)pChar;
                if ( pGamePlayer->IsSaveTime())
                {
                    saveList.push_back(i);
                    ++nNum;
                }
            }
        }

        LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_INFO, "���[%d]����ɫ���������[%d]", nNum, nLeaveCount );

        dwLastTime = HQ_TimeGetTime();            
    }

    // ÿ����ѭֻ���� nSaveBatchNum ���������
    uint32 nSaveCount = 0;
    while ( !saveList.empty() && nSaveCount < nSaveBatchNum )
    {
        uint32 dwID = saveList.front();
        saveList.pop_front();
        BaseCharacter* pChar = theRunTimeData.GetCharacterByID(dwID);
        if ( pChar && pChar->IsPlayer() )
        {
            GamePlayer* pGamePlayer = (GamePlayer*)pChar;
            if ( pGamePlayer->IsCanSaveToDB())
            {
                GettheFileDB().SaveCharAllData( pGamePlayer, EST_Time );
                ++nSaveCount;
            }
        }
    }
}

void GameWorld::MapMonitorRender()
{
    static uint32 dwMonitorStartTime = HQ_TimeGetTime();
    if ( GameWorld::bShowMemoryInfo /*|| GameTime::IsPassCurrentTime( dwMonitorStartTime, ONE_MIN * 15 ) */)
    { 
        PrintMemoryInfo();
        dwMonitorStartTime = HQ_TimeGetTime();     
        GameWorld::bShowMemoryInfo = false;
        return; 
    }
}

GameStage* GameWorld::GetStageById( DWORD dwMapID )
{
    //CSALocker locker(this);
    GameStage* pGameStage = NULL;
    ItrGameStageContainer it = m_mapGameStage.find( dwMapID );
    if ( it != m_mapGameStage.end() )
    {
        pGameStage = it->second;
    }
    return pGameStage;
}

void GameWorld::GetCurMapStage( DWORD ustMapID, std::vector< GameStage* >& vecStage )
{
    vecStage.clear();
	DWORD dwId = EctypeId2MapId( ustMapID );
    ItrGameStageContainer iter = m_mapGameStage.begin();
    ItrGameStageContainer end = m_mapGameStage.end();
    for ( ; iter != end; ++iter )
    {
        if ( iter->second->IsStageWaitingRelease() )
        { continue; }

        if ( EctypeId2MapId( iter->second->GetStageID() ) == dwId )
        {
            vecStage.push_back( iter->second );
        }
    }
}

GameStage* GameWorld::GetActiveStageInWorld()
{
    GameStage* pGameStage = NULL;
    ItrGameStageContainer iter = m_mapGameStage.begin();
    ItrGameStageContainer end = m_mapGameStage.end();
    for ( ; iter != end; ++iter )
    {
        if (!iter->second->IsEctypeStage())
        {
            return iter->second;
        }
    }

    return NULL;
}

bool GameWorld::GetCurMapStage( DWORD dwMapId, std::vector<DWORD>& vtEctypeId )
{
    //CSALocker locker(this);
    vtEctypeId.clear();
    DWORD dwId = EctypeId2MapId( dwMapId );
    ItrGameStageContainer iter = m_mapGameStage.begin();
    ItrGameStageContainer end = m_mapGameStage.end();
    for ( ; iter != end; ++iter)
    {
        GameStage *pStage = iter->second;
        if (pStage == NULL) { continue; }
        DWORD dwStageMapID = EctypeId2MapId( pStage->GetStageID() );
        if ( dwStageMapID == dwId )
        {
            vtEctypeId.push_back( pStage->GetStageID() );
        }
    }
    return true;
}

void GameWorld::ProcessGameStageOp()
{   
    MessageUpdateMapInfo msg;

    ItrGameStageOpContainer iter = _gameStageOp.begin();
    ItrGameStageOpContainer end = _gameStageOp.end();
    for ( ; iter != end; ++iter)
    { 
        if ( !msg.AddStageOp( *iter ) )
        {
            GettheServer().SendMsgToCenterServer( &msg );
            msg.Reset();
            --iter;             //ʧ����Ҫ����ȥ
        }
    }

    if ( msg.szGameStageCount != 0)
        GettheServer().SendMsgToCenterServer( &msg );
}

DWORD GameWorld::GetMapCount( DWORD dwMapId )
{
    DWORD dwCount = 0;
    //CSALocker locker(this);
    DWORD dwId = EctypeId2MapId( dwMapId );
    ItrGameStageContainer iter = m_mapGameStage.begin();
    ItrGameStageContainer end = m_mapGameStage.end();
    for ( ; iter != end; ++iter)
    {
        GameStage *pStage = iter->second;
        if (pStage == NULL) { continue; }
        DWORD dwStageMapID = EctypeId2MapId( pStage->GetStageID() );
        if ( dwStageMapID == dwId )
        {
            ++dwCount;
        }
    }
    return dwCount;
}
DWORD GameWorld::MakeEctypeStageIDByTeamID(MapConfig::MapData* pMapData,unsigned int TeamID)
{
	if ( pMapData == NULL)
		return 0;
	if( pMapData->GetMapType() != MapConfig::MT_SingleTeam)
		return 0;
	if ( TeamID == TeamDefine::NoneSessionID )
		return 0;
	DWORD dwEctypeID = ( TeamID & EctypeStageValue2 );
	DWORD dwMapId = 0;
    dwMapId |= dwEctypeID << EctypeStageValue1;
    dwMapId |= pMapData->Id;
    return dwMapId;
}
DWORD GameWorld::MakeEctypeStageID( MapConfig::MapData* pMapData, BaseCharacter* pChar, int nMapLevel /* = 0 */ )
{
    if ( pMapData == NULL || pChar == NULL || !pChar->IsPlayer() )
    { return 0; }
    // 0xffff ffff
    // ǰ16λΪר��ID,��16λΪ��ͼID
    GamePlayer* pPlayer = static_cast< GamePlayer* >( pChar );

    DWORD dwEctypeID = 0;
    switch( pMapData->GetMapType() ) 
    {
    case MapConfig::MT_SinglePlayer:
        {
            dwEctypeID = ( pPlayer->GetDBCharacterID() & EctypeStageValue2 );
        }
        break;    
    case MapConfig::MT_SingleTeam:
        {
            if ( pChar->GetTeamID() == TeamDefine::NoneSessionID )
            { return 0; }
            dwEctypeID = ( pChar->GetTeamID() & EctypeStageValue2 );
        }
        break;   
    case MapConfig::MT_SingleGuild:
        {
            if ( pChar->GetGuildID() == GuildDefine::InitID )
            { return 0; }
            dwEctypeID = ( pChar->GetGuildID() & EctypeStageValue2 );
        }
        break;
    case MapConfig::MT_MultiPlayer:
    case MapConfig::MT_MultiTeam:
    case MapConfig::MT_MultiGuild:
        {
            for ( ItrGameStageContainer iter = m_mapGameStage.begin(); iter != m_mapGameStage.end(); ++iter )
            {
                GameStage* pStage = iter->second;
                if ( !pStage->IsEctypeStage() || pStage->IsStageWaitingRelease() )
                { continue; }

                DWORD dwStageMapID = EctypeId2MapId( pStage->GetStageID() );
                if ( dwStageMapID != pMapData->Id )
                { continue; }   // ��ͼ����ͬ

                // �еȼ�����, �ҵȼ���ͬ
                if ( pStage->GetStageLevel() != 0 && pStage->GetStageLevel() != nMapLevel )
                { continue; }

                if ( !pStage->CheckCanEnterStage( pPlayer ) )
                { continue; }

                return pStage->GetStageID();
            }

            // û�ҵ����и�����ͼ����һ����ID, �����Ҫϵͳ�����ĸ���,ID��Ҫ�ۼ�
            dwEctypeID  = GetEctypeMapLastId( pMapData->Id, !pMapData->IsSystemCreateMap() );            
        }
        break;
    default:
        break;
    }

    DWORD dwMapId = 0;
    dwMapId |= dwEctypeID << EctypeStageValue1;
    dwMapId |= pMapData->Id;
    return dwMapId;
}

// ���Ҷ��ŶӸ���
GameStage* GameWorld::FindMultiTeamStage( MapConfig::MapData* pMapData, DWORD dwTeamSessionID )
{
    for ( ItrGameStageContainer iter = m_mapGameStage.begin(); iter != m_mapGameStage.end(); ++iter )
    {
        GameStage* pStage = iter->second;
        if ( pStage == NULL || !pStage->IsEctypeStage() || pStage->IsStageWaitingRelease() )
        { continue; }

        DWORD dwStageMapID = EctypeId2MapId( pStage->GetStageID() );
        if ( dwStageMapID != pMapData->Id )
        { continue; }

        MultiTeamStage* pEctypeStage = static_cast< MultiTeamStage* >( pStage );

        if ( pEctypeStage->HaveTeam( dwTeamSessionID ) )
        { return pEctypeStage; }
    }

    return NULL;
}

GameStage* GameWorld::FindMultiGuildStage( MapConfig::MapData* pMapData, DWORD dwTeamSessionID )
{
    for ( ItrGameStageContainer iter = m_mapGameStage.begin(); iter != m_mapGameStage.end(); ++iter )
    {
        GameStage* pStage = iter->second;
        if ( pStage == NULL || !pStage->IsEctypeStage() || pStage->IsStageWaitingRelease() )
        { continue; }

        DWORD dwStageMapID = EctypeId2MapId( pStage->GetStageID() );
        if ( dwStageMapID != pMapData->Id )
        { continue; }

        MultiGuildStage* pEctypeStage = static_cast< MultiGuildStage* >( pStage );

        if ( pEctypeStage->HaveGuild( dwTeamSessionID ) )
        { return pEctypeStage; }
    }

    return NULL;
}

//void GameWorld::ProcGMCommand(const char* szCommand)
//{
//    if (szCommand == NULL)
//    {
//        return;
//    }
//
//    std::string strCmd = szCommand;
//    std::string strOp = strCmd.substr(0, strCmd.find(" "));
//    std::string strParam = strCmd.substr(strCmd.find(" ")+1, strCmd.length());
//
//    //if (strOp == "login")
//    //{
//    //    if (strParam == g_Cfg.szGMPassword)
//    //    {
//
//    //    }
//    //}
//
//    //���δ��½������������ִ��
//    //if (!GetGettheServer().m_GMIsLogin)
//    //{
//    //    return;
//    //}
//
//    if (strOp == "chat")
//    {
//        std::string strPlayer = strParam.substr(0, strParam.find(" "));
//        std::string strChat = strParam.substr(strParam.find(" ")+1, strParam.length());
//
//        BaseCharacter* pChar = theRunTimeData.GetGamePlayerByName(strPlayer.c_str());
//        if (pChar != NULL)
//        {
//            MsgChat chat(MsgChat::CHAT_TYPE_GAMEPROMPT);
//            chat.SetString( strChat.c_str() );
//            GettheServer().SendMsgToSingle( &chat, pChar );
//        }
//    }
//
//    //����
//    if (strOp == "private")
//    {
//        std::string strPlayer = strParam.substr(0, strParam.find(" "));
//        std::string strChat = strParam.substr(strParam.find(" ")+1, strParam.length());
//
//        BaseCharacter* pChar = theRunTimeData.GetGamePlayerByName(strPlayer.c_str());
//        if (pChar != NULL)
//        {            
//            MsgChat chat(MsgChat::CHAT_TYPE_PRIVATE);
//            chat.SetString( strChat.c_str() );
//            sprintf_s(chat.chatHeader.szToName,sizeof(chat.chatHeader.szToName) -1,theXmlString.GetString(eTellClient_Gm2Player_ShowName));
//            GettheServer().SendMsgToSingle( &chat, pChar );
//        }
//    }
//
//    if (strOp == "cmd")
//    {
//        // ��������
//        std::string strCommand = strParam.substr(0, strParam.find(" "));
//
//        // �ߵ���� kick ��ɫ��
//        if (strCommand == "kick")
//        {
//            std::string strCharName = strParam.substr(strParam.find(" ")+1, strParam.length());
//
//            BaseCharacter *pChar = theRunTimeData.GetGamePlayerByName( strCharName.c_str() );
//
//            if(NULL == pChar) 
//            {
//                return;
//            }
//            pChar->Log( "Exit by GM kick" );
//            pChar->ExitWorld(__FUNCTION__, __FILE__, __LINE__);
//            return;
//        }
//        else if (strCommand == "bull")    // ���� bull ��������
//        {
//            std::string strBull = strParam.substr(strParam.find(" ")+1, strParam.length());
//
//            MsgChat chat(MsgChat::CHAT_TYPE_BULL);
//            chat.SetString( strBull.c_str() );    
//            GettheServer().SendMsgToWorld( &chat );
//        }
//        else if (strCommand == "lookup")     // �鿴�����Ϣ
//        {
//            std::string strName = strParam.substr(strParam.find(" ")+1, strParam.length());
//        }
//        else if (strCommand == "unchat")    // ����
//        {
//            std::string strName = strParam.substr(strParam.find(" ")+1, strParam.length());
//            BaseCharacter* pChar = theRunTimeData.GetGamePlayerByName(strName.c_str());
//
//            if(pChar != NULL && pChar->IsPlayer())
//            {
//                GamePlayer* pPlayer = (GamePlayer*)pChar;
//
//                pPlayer->SetCanChat(FALSE);
//            }
//        }
//        else if (strCommand == "canchat")   // �����
//        {
//            std::string strName = strParam.substr(strParam.find(" ")+1, strParam.length());
//            BaseCharacter* pChar = theRunTimeData.GetGamePlayerByName(strName.c_str());
//
//            if(pChar != NULL && pChar->IsPlayer())
//            {
//                GamePlayer* pPlayer = (GamePlayer*)pChar;
//
//                pPlayer->SetCanChat(TRUE);
//            }
//        }
//        else if (strCommand == "permission")    // �������GMȨ��.
//        {
//            char cmd[64];
//            char playerName[128];
//            int permisssion = 0;
//            sscanf( strParam.c_str(), "%s%s%d", cmd, playerName, &permisssion );
//            GamePlayer* pChar = theRunTimeData.GetGamePlayerByName(playerName);
//            if ( pChar )
//            {
//                pChar->m_nGMLevel = permisssion;
//            }
//        }
//    }
//}

bool GameWorld::CheckStageLoad()
{
    for ( CreateMapVectorIter iter = m_vecCreateMapInfo.begin(); iter != m_vecCreateMapInfo.end(); ++iter )
    {
        GameStage* pStage = GetStageById( iter->dwEctypeId );
        if ( pStage != NULL )
        {
            m_vecCreateMapInfo.erase( iter );
            break;
        }

        if ( HQ_TimeGetTime() - iter->dwStartTime > 600000 ) // ��ʱ
        {
            m_vecCreateMapInfo.erase( iter );
            break;
        }
    }

    return true;
}

void GameWorld::CleanAsynStageInfo(SSynStageInfo* pSyn)
{
	if (!pSyn)
	{
		return;
	}
	if (pSyn->_vecSynStageNpc.empty())
	{
		return;
	}
	pSyn->_vecSynStageNpc.clear();

	delete pSyn;

}

bool GameWorld::CheckAsynStageInfo()
{
	CSALocker lock( sysnstageinfo );
	DWORD curr_time = HQ_TimeGetTime();
	for ( SSynStageInfoVectorIter iter = m_vecSSynStageInfo.begin(); iter != m_vecSSynStageInfo.end(); ++iter )
	{		
		SSynStageInfo* pSyn = *iter;
		if (!pSyn)
		{
			m_vecSSynStageInfo.erase( iter );
			break;
		}
		if (!pSyn->pStage)
		{
			CleanAsynStageInfo(pSyn);
			m_vecSSynStageInfo.erase( iter );
			break;
		}

		if ( HQ_TimeGetTime() - pSyn->dwStartTime > 600000 ) // ��ʱ10����
		{
			CleanAsynStageInfo(pSyn);
			m_vecSSynStageInfo.erase( iter );
			break;
		}

		GameStage* pStage = GetStageById( pSyn->pStage->GetStageID() );
		if ( pStage != NULL )
		{
			m_vecSSynStageInfo.erase( iter );
			break;
		}
		else
		{
			MsgGW2GCreateStage xCreate;
			xCreate.dwMapId    = pSyn->pStage->GetMapData()->Id;
			xCreate.dwEctypeId = pSyn->pStage->GetStageID();
			//GettheServer().SendMsgToGates( &xCreate ); 
			if ( !AddGameStage( pSyn->pStage ) )
			{
				if (pSyn->sendtocenter)
				{
					pSyn->mca.Result = false;
					pSyn->mca.ErrorID = 5;//��������ʧ��
					GettheServer().SendMsgToCenterServer(&pSyn->mca);
				}

				theCWaitReleaseStag.AddReleaseStage( pSyn->pStage, 0 );
				CleanAsynStageInfo(pSyn);
				m_vecSSynStageInfo.erase( iter );
				break;
			}
			GettheServer().SendMsgToGates( &xCreate ); //�Ƶ����� ���治һ���ɹ�
			for (int n =0;n < pSyn->_vecSynStageNpc.size();n++)
			{
				// Init����npc�ű�
				NpcBaseEx* pNpcOject = (NpcBaseEx*)theRunTimeData.GetCharacterByID( pSyn->_vecSynStageNpc[n] );
				if ( pNpcOject && pNpcOject->GetInitVMId() != -1 )
				{
					CScriptVMThread thread;
					CScriptVM* pVM = GetScriptMgr()->GetScriptControl()->GetVM( pNpcOject->GetInitVMId() );
					thread.SetVM( pVM );
					thread.SetCharId( pSyn->_vecSynStageNpc[n] );
					if( thread.SetEntrance( 0 ) )
					{	
						if (!thread.Restore())
							LogMessage::LogSystemError( "CScriptMgr::InitScripts() thread.Restore()[NPCID:%d] error" ,pNpcOject->GetNpcID());
					}
				}
				
				// ��ӵ�����
				if( !theGameWorld.OnAddCharacter( pSyn->_vecSynStageNpc[n], __FILE__, __LINE__ ) )
				{
					LogMessage::LogSystemError( "AsynCreateNpc theGameWorld.OnAddCharacter( %d ) error", pSyn->_vecSynStageNpc[n] );
					theGameWorld.OnDelCharacter( pSyn->_vecSynStageNpc[n]);
					theRunTimeData.ReleaseObject( pSyn->_vecSynStageNpc[n], __FILE__, __LINE__);						
				}
			}

			if (pSyn->sendtocenter)
			{
				pSyn->mca.Result = true;
				GettheServer().SendMsgToCenterServer(&pSyn->mca);
			}
			

			CleanAsynStageInfo(pSyn);
			m_vecSSynStageInfo.erase( iter );
			/*printf("sysn:%d\n",HQ_TimeGetTime() - curr_time);*/
			break;
		}
	}	
	return true;
}


void GameWorld::InitEctypeMapId( unsigned long EctypeMapDataId )
{
    ItrMapIdMakeContainer it = _MapIdMake.find( EctypeMapDataId );
    if ( it != _MapIdMake.end() )
    {
        it->second = 1;
        return;
    }

    // �� 1 ��ʼ
    _MapIdMake.insert( MapIdMakeContainer::value_type( EctypeMapDataId, 1 ) );
}

unsigned long GameWorld::GetEctypeMapLastId( unsigned long uEctypeMapDataId , bool bIncreaseAfterGet )
{
    ItrMapIdMakeContainer it = _MapIdMake.find( uEctypeMapDataId );
    if ( it != _MapIdMake.end())
    {
        unsigned long id = it->second;
        if ( bIncreaseAfterGet )
        {
            it->second += 1;
        }
        return id;
    }

    LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR,  "GameWorld::GetEctypeMapLastId Not Find %d", uEctypeMapDataId );
    return 0;
}

unsigned long GameWorld::GetEctypeMapID( unsigned long uEctypeMapDataId , bool bIncreaseAfterGet )
{
    unsigned long dwMapID = GetEctypeMapLastId( uEctypeMapDataId, bIncreaseAfterGet );
    dwMapID <<= EctypeStageValue1;
    dwMapID |= uEctypeMapDataId;

    return dwMapID;
}

int GameWorld::GetCreateLoadMapCount( DWORD dwMapID )
{
    int nCount = 0;
    DWORD dwMapDataID = EctypeId2MapId( dwMapID );
    for ( CreateMapVectorIter iter = m_vecCreateMapInfo.begin(); iter != m_vecCreateMapInfo.end(); ++iter )
    {
        if ( EctypeId2MapId( iter->dwEctypeId ) == dwMapDataID )
        {
            ++nCount;
        }
    }

    return nCount;
}

// �ٻ�����( SummonType �ٻ�����������:
//                                        0���Խ�ɫΪ�����ڰ뾶ΪfRadius��Բ�����ˢ��,
//                                        1���Խ�ɫΪ���İ뾶ΪfRadius��ԲȦ, ���йֳ����ɫ
//                                        2���Խ�ɫΪ���İ뾶ΪfRadius��ԲȦ, ���йֱ����ɫ
//                                        3���Խ�ɫ�������fRadius�ĵط���һ��, ���й��ﳯ��ͽ�ɫ�෴
//                                        4���Խ�ɫ�������fRadius�ĵط���һ��, ���й��ﳯ��ͽ�ɫһ��
//BOOL BaseCharacter::SummonMonster( int nMonsterId, int nMonsterNumber, float fRadius, int nSummonType )
//BaseCharacter* GameWorld::SummonMonster( int nMapID, float fPosX, float fPosY, float fDirX, float fDirY, float fBodySize, 
//                                        int nMonsterId, int nMonsterNumber, float fRadius, int nSummonType, DWORD dwSpecialID, int nInfluence )
//{
//    int nMonsterIndex = GettheItemDetail().FindMonsterIndexById( nMonsterId );
//    if ( nMonsterIndex == -1)
//    {
//        // �������Ҳ���,����һ��
//        if ( IsEctypeMonsterID( nMonsterId ) )
//        {
//            // ��ó����ȼ�
//            GameStage* pStage = GetStageById( nMapID );
//            if ( pStage == NULL || pStage->GetStageLevel() == 0 )
//            {
//                LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_ERROR, "GameWorld::SummonMonster [%d] GetStage Error MapID = [0x%x]",nMonsterId, nMapID );
//                return NULL;
//            }
//
//            nMonsterId = FormatEctypeMonsterID( nMonsterId, pStage->GetStageLevel() );
//            nMonsterIndex = GettheItemDetail().FindMonsterIndexById( nMonsterId );
//            if ( nMonsterIndex == -1 )
//            {
//                LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_ERROR, "GameWorld::SummonMonster �ɸ����ȼ��������ˢ��ID����ȷ MapID = [0x%x] ����ID = [%d] Level = [%d]", nMapID, nMonsterId, pStage->GetStageLevel() );
//                return NULL;
//            }
//        }
//        else
//        {
//            LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_ERROR, "GameWorld::SummonMonster ˢ��ID���ò���ȷ MapID = [0x%x] ����ID = [%d]", nMapID, nMonsterId );
//            return NULL;
//        }
//    }
//
//    D3DXVECTOR3 vDir( fDirX, fDirY, 0 );
//    D3DXVECTOR3 vZAxis( 0, 0, 1 );
//    float fStep     = 0.0f;
//    float fDistance = 0.0f;
//    if( nMonsterNumber > 0 )
//    {
//        fStep = D3DX_PI*2/nMonsterNumber;
//    }
//    else
//    {
//        fStep = 0;
//    }
//
//    const int nMoveRadius = 2;
//    BaseCharacter* pChar = NULL;
//    for( int i=0; i<nMonsterNumber; ++i )
//    {
//        CMonsterProducer::TagMonsterData MonsterData;
//        MonsterData.nMonsterIndex = nMonsterIndex;
//        switch( nSummonType )
//        {
//        case 2:
//            {
//                D3DXVECTOR3 vMonsterDir;
//                D3DXMATRIX matRotZ;
//
//                D3DXMatrixRotationAxis( &matRotZ, &vZAxis, fStep*i );
//                D3DXVec3TransformCoord( &vMonsterDir, &vDir, &matRotZ );
//                D3DXVec3Normalize( &vMonsterDir, &vMonsterDir );
//
//                fDistance = fRadius + fBodySize;
//                MonsterData.x = fPosX + vMonsterDir.x*fDistance;
//                MonsterData.y = fPosY + vMonsterDir.y*fDistance;
//
//                MonsterData.rcBron.left    = FloatToTile( MonsterData.x ) - nMoveRadius;
//                MonsterData.rcBron.right   = FloatToTile( MonsterData.x ) + nMoveRadius;
//                MonsterData.rcBron.top     = FloatToTile( MonsterData.y ) - nMoveRadius;
//                MonsterData.rcBron.bottom  = FloatToTile( MonsterData.y ) + nMoveRadius;
//                FIX_NORMAL_ZERO( MonsterData.rcBron.left );
//                FIX_NORMAL_ZERO( MonsterData.rcBron.top  );
//
//                pChar = CreateMonster( &MonsterData, nMapID, MonsterData.x, MonsterData.y, vMonsterDir.x, vMonsterDir.y, -1, dwSpecialID, nInfluence, TRUE );
//            }
//            break;
//        case 1:
//            {
//                D3DXVECTOR3 vMonsterDir;
//                D3DXMATRIX matRotZ;
//
//                D3DXMatrixRotationAxis( &matRotZ, &vZAxis, fStep*i );
//                D3DXVec3TransformCoord( &vMonsterDir, &vDir, &matRotZ );
//                D3DXVec3Normalize( &vMonsterDir, &vMonsterDir );
//
//                fDistance = fRadius + fBodySize;
//                MonsterData.x = fPosX + vMonsterDir.x*fDistance;
//                MonsterData.y = fPosY + vMonsterDir.y*fDistance;
//
//                MonsterData.rcBron.left    = FloatToTile( MonsterData.x ) - nMoveRadius;
//                MonsterData.rcBron.right   = FloatToTile( MonsterData.x ) + nMoveRadius;
//                MonsterData.rcBron.top     = FloatToTile( MonsterData.y ) - nMoveRadius;
//                MonsterData.rcBron.bottom  = FloatToTile( MonsterData.y ) + nMoveRadius;
//                FIX_NORMAL_ZERO( MonsterData.rcBron.left );
//                FIX_NORMAL_ZERO( MonsterData.rcBron.top  );
//
//                pChar = CreateMonster(&MonsterData, nMapID, MonsterData.x, MonsterData.y, -vMonsterDir.x, -vMonsterDir.y, -1, dwSpecialID, nInfluence, TRUE );
//            }
//            break;
//        default:
//            {
//                vDir.x = (theRand.rand32()%1001 - 500);
//                vDir.y = (theRand.rand32()%1001 - 500);
//                vDir.z = 0;
//                D3DXVec3Normalize( &vDir, &vDir );
//                fDistance = (float)(theRand.rand32()%1001)*fRadius*0.001f + fBodySize;
//
//                MonsterData.x = fPosX + vDir.x*fDistance;
//                MonsterData.y = fPosY + vDir.y*fDistance;
//
//                vDir.x = (theRand.rand32()%1001 - 500);
//                vDir.y = (theRand.rand32()%1001 - 500);
//                vDir.z = 0;
//                D3DXVec3Normalize( &vDir, &vDir );
//
//                MonsterData.rcBron.left    = FloatToTile( MonsterData.x ) - nMoveRadius;
//                MonsterData.rcBron.right   = FloatToTile( MonsterData.x ) + nMoveRadius;
//                MonsterData.rcBron.top     = FloatToTile( MonsterData.y ) - nMoveRadius;
//                MonsterData.rcBron.bottom  = FloatToTile( MonsterData.y ) + nMoveRadius;
//                FIX_NORMAL_ZERO( MonsterData.rcBron.left );
//                FIX_NORMAL_ZERO( MonsterData.rcBron.top  );
//
//                pChar = CreateMonster( &MonsterData, nMapID, MonsterData.x, MonsterData.y, vDir.x, vDir.y, -1, dwSpecialID, nInfluence );
//            }
//            break;
//        }
//    }
//    return pChar;
//}

void GameWorld::SetExtendrnMapOpen( bool bValue )
{
    m_bExtendBornMapOpen = bValue;
    m_mapCountryBorn.clear();
}

// �����ҳ������ͼ
const CountryConfig::BornMapSetting* GameWorld::GetPlayerBornMap( int nCountry )
{
    if ( !m_bExtendBornMapOpen )
    { return theCountryConfig.GetBornMapSetting( nCountry ); }

    unsigned char uchIndex = 0;
    CountryBornMapIter iter = m_mapCountryBorn.find( nCountry );
    if ( iter != m_mapCountryBorn.end() )
    {
        uchIndex = iter->second++;
        if ( uchIndex >= theCountryConfig.GetBornMapSettingCount( nCountry ) )
        { uchIndex = 0; }
    }
    else
    {
        m_mapCountryBorn.insert( std::make_pair( nCountry, 1 ) );
    }

    return theCountryConfig.GetBornMapSetting( nCountry, uchIndex );
}

void GameWorld::TryLoadAllScript()
{
    _reloadScriptTimeRecord.StartTimer( HQ_TimeGetTime(), 1000 );
    if ( !_reloadScriptTimeRecord.DoneTimer( HQ_TimeGetTime() ) )
    { return; }

    if ( !GetScriptMgr()->gbNeedReloadScript )
    { return; }

    // �ر������û��Ľű�
    int iLoopSize= 0,iLoopUsed = 0;
    BaseCharacter* pChar = NULL;
    int iUsed = theRunTimeData.theCharacters.GetUsed();
    int iSize = theRunTimeData.theCharacters.GetSize();
    for( iLoopUsed = 0,iLoopSize = 0 ; iLoopUsed < iUsed && iLoopSize < iSize ; ++iLoopSize )
    {
        if ( !theRunTimeData.theCharacters.IsUsed( iLoopSize ) )
        { continue; }
                
        pChar = (BaseCharacter*)theRunTimeData.GetCharacterByID( iLoopSize );
        if ( pChar == NULL || !pChar->IsPlayer() )
        { continue; }

        ++iLoopUsed;

        GamePlayer* pGamePlayer = (GamePlayer* )pChar;
        pGamePlayer->CancelAllScript();
    }

    // ���ؽű�    
    bool bResult = GetScriptMgr()->ReloadAllScripts();
    if ( bResult )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_INFO, "ReloadAllScripts() Success" );
    }
    else
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "ReloadAllScripts() Fail" );
    }

    GetScriptMgr()->gbNeedReloadScript = false;
}


//bool GameWorld::CreateNpcHero( GameStage* pStage, NpcInfo::Npc* pNpcInfo, bool bConfigNpcInfoPointer, DWORD OnlineTime)
//{
//    int nNpcId = theRunTimeData.CreateObject( (EObjectType)NpcBaseEx::GetObjecTypeByNpcType( pNpcInfo->type) );
//    NpcBaseEx* pNpcOject = (NpcBaseEx*)theRunTimeData.GetCharacterByID( nNpcId );
//    if ( NULL == pNpcOject )
//    {
//        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "Get NpcObject[%u] Error!", nNpcId);
//        return false;
//    }
//
//    pNpcOject->SetNpcInfoIsConfigAddress( bConfigNpcInfoPointer  );
//    pNpcOject->SetNpcInfo               ( pNpcInfo               );
//    pNpcOject->SetDisappearTime         ( OnlineTime             );
//    pNpcOject->SetCharName              ( pNpcInfo->name.c_str() );
//    pNpcOject->SetNpcID                 ( pNpcInfo->id           );
//    pNpcOject->SetLevel                 ( pNpcInfo->level        );
//    pNpcOject->SetModelId               ( pNpcInfo->modelId      );
//    pNpcOject->SetMapID                 ( pStage->GetStageID()   );
//    pNpcOject->SetFloatXF               ( pNpcInfo->x            );
//    pNpcOject->SetFloatYF               ( pNpcInfo->y            );
//    pNpcOject->SetFloatZ                ( pNpcInfo->z            );
//    pNpcOject->SetMask                  ( pNpcInfo->isCollision  );
//    pNpcOject->SetShow                  ( pNpcInfo->isWorldShow  ); // �����Ƿ�����״̬
//    pNpcOject->SetCountry               ( pNpcInfo->uchCountryID );
//
//    float fDir = pNpcInfo->direction;
//    float fDirX = 0.0f, fDirY = 0.0f;
//    if( fDir < 0 || fDir > 360 )
//    { fDir = 0; }
//
//    fDir = fDir/180*D3DX_PI;
//    float fxtoy = tan(fDir);
//    float fPosXOff = 0;
//    float fPosYOff = 0;
//
//    if( fxtoy == 0 )
//    {
//        fPosXOff = 1;
//    }
//    else
//    {
//        fPosXOff = sqrtf(1/(1+fxtoy*fxtoy));
//        fPosYOff = fabs(fxtoy*fPosXOff);
//    }
//    if( ( fDir >= 0 && fDir <= D3DX_PI/2 ) || ( fDir >= -D3DX_PI*2 && fDir <= -D3DX_PI*3/2 ) )
//    { // ��һ����
//        fDirX = fPosXOff;
//        fDirY = fPosYOff;
//    }
//    else if( ( fDir >= D3DX_PI/2 && fDir <= D3DX_PI ) || ( fDir >= -D3DX_PI*3/2 && fDir <= -D3DX_PI ) )
//    { // �ڶ�����
//        fDirX = -fPosXOff;
//        fDirY = fPosYOff;
//    }
//    else if( ( fDir >= D3DX_PI && fDir <= D3DX_PI*3/2 ) || ( fDir >= -D3DX_PI && fDir <= -D3DX_PI/2 ) )
//    { // ��������
//        fDirX = -fPosXOff;
//        fDirY = -fPosYOff;
//    }
//    else if( ( fDir >= D3DX_PI*3/2 && fDir <= D3DX_PI*2 ) || ( fDir >= -D3DX_PI/2 && fDir <= 0 ) )
//    { // ��������
//        fDirX = fPosXOff;
//        fDirY = -fPosYOff;
//    }
//
//    pNpcOject->SetDirX( fDirX );
//    pNpcOject->SetDirY( fDirY );
//    pNpcOject->SetDir( 0 );
//    pNpcOject->GetCharFightAttr()->moveSpeed.base=1.65f;
//    pNpcOject->GetCharFightAttr()->moveSpeed.UpdateFinal();
//    pNpcOject->GetCharFightAttr()->hpMax.base = 10000;
//    pNpcOject->GetCharFightAttr()->hpMax.UpdateFinal();
//    pNpcOject->SetHP( pNpcOject->GetCharFightAttr()->hpMax.final );
//
//    pNpcOject->SetLastMovingSpeed ( pNpcOject->GetMoveSpeed() );
//
//    //int nNewArea = TestAreaNumber( pNpcOject->GetX(), pNpcOject->GetY() );
//    //pNpcOject->SetCurArea( nNewArea );
//    //pNpcOject->SetNpcImgPath( pNpcInfo.strImgPath.c_str() );
//
//    pNpcOject->SetMoveState( NpcBaseEx::EAction_Prepare );
//    if( !pNpcInfo->canChangeDirection )
//    { pNpcOject->AddShowFlag( eNotChangeDir ); }
//
//    if( false )
//    { pNpcOject->AddShowFlag( eNotShadow ); }
//
//    // �ж��Ƿ���·��
//    if( pNpcInfo->movePath >=0 )
//    {
//        if( !pNpcOject->InitRoute() )
//        { LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "Npc[%d] Load Route[%d:%d] Fail ", pNpcInfo->id, pNpcInfo->mapId, pNpcInfo->movePath); }
//    }
//
//    // ��̬��ʼ��
//    if ( pNpcOject->Init() != ER_Success )
//    {
//        theRunTimeData.ReleaseObject( nNpcId );
//        return false; 
//    }
//
//    if( pNpcInfo->type >= 0 || pNpcInfo->type < eNT_Max )
//    { pNpcOject->SetNpcType( (ENpcType)pNpcInfo->type ); }
//
//    std::string strScriptPath;
//    if ( !pNpcInfo->triggerScript.empty())
//    {
//        strScriptPath = SCRIPT_ROOTDIRECTORY;
//        strScriptPath += pNpcInfo->triggerScript;
//    }
//
//    if ( !strScriptPath.empty())
//    {
//        int nVMId = GetScriptMgr()->CreateVM( ST_NPC, strScriptPath.c_str(), nNpcId );
//        CScriptVMThread thread;
//        CScriptVM* pVM = GetScriptMgr()->GetScriptControl()->GetVM( nVMId );
//        thread.SetVM( pVM );
//        if( thread.SetEntrance( 0 ) )
//        {
//            thread.SetCharId( nNpcId );
//            if ( !thread.Restore() )
//            {
//                LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "CScriptMgr::InitScripts() thread.Restore() error" );
//            }
//        }
//    }
//
//    if( !OnAddCharacter( nNpcId, __FILE__, __LINE__ ) )
//    {
//        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "CreateNpcHero theGameWorld.OnAddCharacter( %d ) error", nNpcId );
//        OnDelCharacter( nNpcId );
//        theRunTimeData.ReleaseObject( nNpcId );
//        return false;
//    }
//
//    return true;
//}
//
//bool GameWorld::CreateNpcsHero( GameStage* pStage )
//{
//    for ( NpcInfo::NpcsIter it = theNpcInfo.npcs_.begin(); it != theNpcInfo.npcs_.end(); ++it )
//    {
//        NpcInfo::Npc* pNpcInfo = &it->second;
//        if ( pNpcInfo->mapId != pStage->GetMapData()->Id )
//        { continue; }
//
//        if ( pNpcInfo->type == eNT_ScriptNpc) // �ű�NPC�����Զ�������ͨ���ű�������
//        { continue; }
//
//        if (!CreateNpcHero( pStage, pNpcInfo, true ) )
//        { continue; }
//    }
//    return true;
//}

GameObjectId GameWorld::GetNextObjectBId( bool bFirst )
{
    if ( bFirst )
    { _objectIdItr = _objectIds.begin(); }

    if ( _objectIdItr != _objectIds.end() )
    { 
        GameObjectId result = *_objectIdItr;
        ++_objectIdItr;
        return result; 
    }

    return InvalidGameObjectId;
}
