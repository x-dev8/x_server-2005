#include "GamePlayer.h"
#include "Dxsdk/d3dx9math.h"
#include "ShareData.h"
#include "GameTime.h"
#include "GameWorld.h"
#include "LoginStage.h"
#include "MathLib.h"
#include "DBMessageDefine.h"
#include "MonsterBaseEx.h"
#include "ServerVarInterface.h"
#include "ScriptCompiler.h"
#include "ScriptVarMgr.h"
#include "ItemCharacter.h"
#include "ExpStage.h"
#include "Configure.h"
#include "MissionList.h"
#include "DatabaseConnectors.h"
#include "TimeClock.h"
#include "WordParser.h"
#include "AvatarSystemSetting.h"
#include "QuestManager.h"
#include "WordParser.h"
#include "ProcessCharInfo.h"
#include "SystemConfig.h"
#include "NpcBaseEx.h"
#include "ErrorLog.h"
#include "FuncPerformanceLog.h"
#include "DropQuestItem.h"
#include "ShareData.h"
#include "DataChunkWriter.h"
#include "ServerVarInterface.h"
#include "GameWorldTimer.h"
#include "XmlStringLanguage.h"
#include "DuelHandler.h"
#include "TimeEx.h"
#include "AntiAddictionSystem.h"
#include "ChatCheck.h"
#include "md5.h"
#include "ResourcePath.h"
#include "DataCenter.h"
#include "DropItemManager.h"
#include "TeamManager.h"
#include "XmlStringLanguage.h"
#include "NpcInfo.h"
#include "StarLevelUpConfig.h"
#include "LuckRewardManager.h"
#include "RabotManager.h"
#include "SpecialQuestManager.h"
#include "BattleManager.h"
#include "KillMonsterCountConfig.h"
#include "TradeCenterInfo.h"
#include "RabotDefine.h"
#include "CountryManager.h"
#include "CountryConfig.h"
#include "CharacterAttributeConfig.h"
#include "NpcShop.h"
#include "NpcShipEx.h"
#include "PKConfig.h"
#include "DateTimeFunction.h"
#include "CampBattleControl.h"
#include "CampBattle.h"
#include "NpcFightEx.h"
#include "VarClearConfig.h"
#include "XinFaConfig.h"
#include "PetSettingConfig.h"
#include "StallMessage.h"
#include "MonsterCreater.h"
#include "PetBreedManager.h"
#include "FamilyConfig.h"
#include "RouteManager.h"
#include "ItemHero.h"
#include "TPHJManger.h"
#include "UserLoger.h"
#include <time.h>
#include "MessageDefine.h"
#include "LevelLimitGameManager.h"
#include "MountStrengthenConfig.h"
#include "ChangeCountryConfig.h"
#include "PetDefineConfig.h"
#include "PasswordMessage.h"
#include "LogEventService.h"
#include "CardAchieveConfig.h"
#include "SevenDays.h"
#include "EffectChar.h"
#include "RankTitleConfig.h"
#include "QuestEntrust.h"
#include "HuntingQuestManager.h"
#include "GameBattleControl.h"
#include "GameGuildGeneralBattleManager.h"
#include "GameGuildGeneralBattle.h"
#include "GameBattleDefine.h"
#include "ThreeDayConfig.h"
#include "CardIconConfig.h"
extern IScriptInterface* GetScriptInterface();

typedef int(*lplogout)(BSTR,BSTR,BSTR,BSTR,BSTR,BSTR,BSTR,BSTR,char* pBuffer,int* pBufferLen);
typedef int(*lpUserIDToAccount)(BSTR,BSTR,char* pBuffer,int* pBufferLen);
typedef int(*lpPayment)(BSTR,BSTR,BSTR,BSTR,BSTR,BSTR,BSTR,BSTR,BSTR,char* pBuffer,int* pBufferLen);
typedef int(*lpGetGoods)(BSTR,BSTR,BSTR,BSTR,BSTR,BSTR,BSTR,BSTR,BSTR,char* pBuffer,int* pBufferLen);
typedef int(*lpGetPoint)(BSTR,BSTR,BSTR,BSTR,char* pBuffer,int* pBufferLen);

GamePlayer::GamePlayer()
{
    memset(&m_dbinfo, 0, sizeof(m_dbinfo));

    Initialize();
    m_bTellCostTime = false;
    m_dwTellCostTime = 300;
    m_ProtectCharID = -1;
    m_nProtectCharMonsterId = -1;
    m_nDromeId  = -1;
	m_nMountLevel = 0;
    m_nDromePos =  0;
    m_nDriverId = InvalidGameObjectId;

    _capturePetId = InvalidGameObjectId;
    _capturePetAIType = ePetCommandAI;

    //????????

	_nHaveSaveAntiAddtionDuration = 0;
	_xUpdateAntiAddictionTimer.StartTimer( HQ_TimeGetTime(), OneMinuteMicroSecond );
    m_nOfflineTime = 0;
    _exitType      = ET_ExitGame;
    //m_nEnterTime   = 0;

    m_nCurActionId          = 0;    
    m_nCurActionPlayTime    = 0;

    m_nProtectLockLeaveTime = 0;
    m_nBanSpeakTime = 0;

    _graphicCodeManager.SetOwner( this );
    _blockTime = 0;
    dwCharSaveDelay = 0;
    _actionManager.SetBeWatcher( this );
    _mailManager.SetOwner( this );
	_sevenDayManager.SetOwner( this );
	//theHuntingQuestManager.SetOwner( this );

	ResetAntiAddictionNotifyIndex();
	_nAntiAddtionTimeCount = 0;

    memset( &lastFightAttr       , 0, sizeof(lastFightAttr        ));
    memset( fightAttrChangeRecord, 0, sizeof(fightAttrChangeRecord));
    memset( &addSubBaseAttr  , 0, sizeof(addSubBaseAttr   ));

    //SetOwnerType( RunningScriptControl::EOwnerType_GamePlayer );

    m_bIsStatusChangeHpMpMax = false;
    m_bIsClearDuelFight      = false;
    m_bMoving                = false;
    m_bIsFlyMoving           = false;
    m_nBigShipId             = InvalidGameObjectId;
    m_nDuelFightLoser       = ErrorUnsignedShortID;
    m_dwCheckProtectTimePer  = HQ_TimeGetTime();
    strncpy_s( m_szLoginName, sizeof(m_szLoginName), "Invalid", sizeof(m_szLoginName) - 1);
    strncpy_s( m_szLoginIP,   sizeof(m_szLoginIP)  , "Invalid", sizeof(m_szLoginIP) - 1);

    m_nPKValue             = 0;
    m_nPKMode              = PKMode_Normal;

    m_gtUpdatePKModeTimer.StopTimer()       ;
    m_gtUpdatePKValueTimer.StopTimer()      ;
    m_gtUpdateCriticalModeTimer.StopTimer() ;
	
	_nEnterRealTime = 0;

	m_IsUpdateLevelPKAttMode = false;

	m_LogTime = 0;
	m_LogTeamID = 0;
	
	_nAntiAddtionNotifyIndex = 0;
	_nAntiAddtionStatusChangeStamp = 0;

	m_DeadPetID = 0;

	m_PetExpUpdateLog = 0;

	m_IsCanDead = true;

	m_ScriptStatesID = 0;
}

void GamePlayer::Initialize()
{
    m_bPosDebugOpen = false;

    SetForce( ForceDefine::NormalPlayerForce );

    SetStatus(CS_LOGIN);
    SetHP(100);
    SetHPMax(100);
    SetMP(1);
    SetMPMax(10);
    SetLevel(1);    
    m_bDeathAndWaitForRelive = false;    
    SetObjType( Object_Player );
    _lastVerifyPosTime = 0;

    _lastHitchMovingTime = 0;

    m_nCredit = 20000;

    m_ucCharStatus = MsgPlayerEnterMySight::charstatus_normal_drawin;

    m_dwEnterWorldClientTime = 0;
    m_dwEnterWorldServerTime = 0;
    m_dwClientLastSendMovingMsgTime = 0;
    m_dwClientLastSendMovingMsgServerTime = 0;
    m_dwClientPassedTimePerCheck = 0;
    m_bAssaultMovingProcess = false;
    m_fLastMoveSpeedPerCheck = 0;
    m_nKickCount = 0;
    m_nTrafficID = -1;
    m_bHitchMoving = false;
    m_bHitchBack = false;
    m_dwRouteStep = 0;

    m_nGMLevel                = 0;
    m_bEnmityDebugOpen        = false;
    m_bDamageEnmityDebugOpen  = false;

    memset( &gCharInfoServer, 0, sizeof(gCharInfoServer) );

    m_pstShop                = NULL;
    m_nScriptNpcId           = -1;
    m_bStorageDBFlag          = false;
    m_PreSaveTime            = 0; // ????????????????????????????????
    m_dwLastEnterWorldReqTime  = 0;
    m_ustCauseStatusID       = -1;
    SetDead( false );

    _bWantSwitchGameWaitSaveInfoOk = false;
    _GateInfo.uGatePort = 0;

    for( int i = 0;i < EEquipPartType_MaxEquitPart; ++i)
    {
        m_stMeAddStatus         [i]  = -1;
        m_stMeAddStatusLvl      [i]  = -1;
        m_stDstAddStatus        [i]  = -1;
        m_stDstAddStatusLvl     [i]  = -1;
        m_fDstStatusRate        [i]  = 0;
        m_fMeStatusRate         [i]  = 0;
        m_nMeAddStatusTrigger   [i]  = 0; 
        m_nDstAddStatusTrigger  [i]  = 0;
    }

    _suitManager.SetPlayer(this);

    SetAttackLockCharState( false );

    m_dwTeamSessionId         = TeamDefine::NoneSessionID;

    m_dwLastUpdateTime        = HQ_TimeGetTime();
    m_dwExpressionTime        = 0;

    m_dwLastHintMessageSendTime = 0;
    _bFirstEnterGameServer      = true;

    memset(m_nTempVars,0,sizeof(m_nTempVars));

    m_bCanChat              = TRUE;
    m_nDstPlayerId          = -1;
    //m_bInPKDisableZone      = FALSE;
//    m_bInPrivateShopZone    = FALSE;
    m_nCurZoneID            = -1;
    m_bPosDebugOpen          = false;
    m_dwLastDoRideTime       = 0;
    m_dwScriptSleep          = 0;
    m_dwScriptSleepStartTime = 0;
    m_bInDuelReq             = FALSE;
    m_tmChatCoolDownTime      = 0;
    //m_bInFreePKZone         = false;
    bAlwayCritical          = false;
    bShowFightInfo          = false;
    _bInLoginStage          = true;    
    _accumulateEneryTime    = 0;
    _accumulateVigorTime    = 0;
    m_dwLastChatTime        = 0;
    memset( _newPlayerName, 0, sizeof(_newPlayerName));
    //memset( _szSessionKey,  0, sizeof(_szSessionKey));
	_SessionKey = 0;
    m_dwReqShopTime = 0;

    m_nCountrySpeakSpaceTime = 0;

    SetReqRemoveMarriage( false );
    SetForceRemove( false );
    m_nLastQueryTime = 0;

    dwProtectTime = 0;
    m_nChangeStageType = PlayerChangeStage;

    m_nBargainingID = BargainingDefine::NoneID;
    dwLastReceiveMoveMessageTime = 0;

    m_dwPetBreedId = 0;
    m_bBreedPetPrompt = false;

    m_fChangeExpPer = 1.0f;
    m_fChangeSkillExpPer = 1.0f;
    m_bIsOpenDoubleExp = false;

    m_nVarClearTime = 0;
    m_pMapData  = NULL;
    m_pRelation = NULL;
    m_pCountry  = NULL;
    m_pGuild    = NULL;

	_bGetWallowInfo = false;
	mBiaocheState = false;
	m_BiaoCheSpeed = 0.0f;

	m_nRMBMoney  = 0;         // ????????
	m_nGameMoney  = 0;        // ??????????

	m_bIsWaitProcess = false;      // ??????????????
	m_dwLastOperateTime = 0; // ????????????

	m_LogTime  =0;
	m_LogTeamID = 0;

	m_IsCanDead = true;
}

GamePlayer::~GamePlayer()
{    
#ifdef NPGUARD
	_authManager.ClosePlayerCSAuth();
#endif
}

void GamePlayer::CheckEnterWorldMapID( DBMsgAckEnterWorld* pEnterWord, DWORD& dwMapID, int& nMapX, int& nMapY )
{
    // ??????????
    if ( pEnterWord->dwTeamSessionID != TeamDefine::NoneSessionID )
    {
        GameTeam* pTeam = theGameTeamManager.GetTeam( pEnterWord->dwTeamSessionID );
        if ( pTeam != NULL && pTeam->IsInTeam( GetDBCharacterID() ) )
        {
            SetTeamID( pEnterWord->dwTeamSessionID );
        }
        else
        {
            GS2CSPlayerRemoveFromTeamReq xRemove;
            xRemove.dwSessionId  = pEnterWord->dwTeamSessionID;
            xRemove.dwDataBaseId = GetDBCharacterID();
            GettheServer().SendMsgToCenterServer( &xRemove );

            SetTeamID( TeamDefine::NoneSessionID );
        }
    }

    MapConfig::MapData* pMapData = theMapConfig.GetMapDataById( EctypeId2MapId( dwMapID ) );
    if ( pMapData == NULL || !pMapData->IsEctypeMap() )        //??????????????????????????????????
    { return; }

    // ??????????????????
    //CampBattle* pCampBattle = theCampBattleControl.GetCampBattle( GetDBCharacterID() );
    //if ( pCampBattle != NULL && pCampBattle->GetBattleManager()->GetMapID() == EctypeId2MapId( dwMapID ) )
    //{
    //    // ????, ????, ??????????????????????????????
    //    switch ( pCampBattle->GetBattleManager()->GetBattleType() )
    //    {
    //    case CampDefine::BattleTypeGuild:   // ??????????
    //        {
    //            BattlePlayer* pBattlePlayer = pCampBattle->GetBattlePlayer( GetDBCharacterID() );
    //            if ( pBattlePlayer != NULL )
    //            {
    //                SetFightCamp( pBattlePlayer->GetFightCamp() );
    //                SetMapID( pCampBattle->GetBattleMapID() );
    //                SetFloatZ( WORLD_HEIGHT );
    //                dwMapID = GetMapID();
    //                return;
    //            }
    //        }
    //        break;
    //    default:
    //        break;
    //    }
    //}

    switch ( pMapData->GetMapType() )
    {
    case MapConfig::MT_MultiPlayer:     // ????????????????
        {
        }
        break;
    case MapConfig::MT_MultiTeam:   // ??????????????
        {
            GameStage* pStage = theGameWorld.FindMultiTeamStage( pMapData, GetTeamID() );
            if ( pStage != NULL && !pStage->IsStageWaitingRelease() )
            {
                SetMapID( pStage->GetStageID() );
                SetFloatZ( WORLD_HEIGHT );
                dwMapID = GetMapID();
                return;
            }
        }
        break;
    case MapConfig::MT_MultiGuild:   // ??????????
        {
            GameStage* pStage = theGameWorld.FindMultiGuildStage( pMapData, GetTeamID() );
            if ( pStage != NULL && !pStage->IsStageWaitingRelease() )
            {
                SetMapID( pStage->GetStageID() );
                SetFloatZ( WORLD_HEIGHT );
                dwMapID = GetMapID();
                return;
            }
        }
        break;
    case MapConfig::MT_SingleTeam:
    case MapConfig::MT_SingleGuild:
    case MapConfig::MT_SinglePlayer:
        {
            DWORD dwEctypeMapID = theGameWorld.MakeEctypeStageID( pMapData, this );  
            GameStage* pStage = theGameWorld.GetStageById( dwEctypeMapID );
            if ( pStage != NULL && !pStage->IsStageWaitingRelease() )       // ??????????,????????????????
            {
                SetMapID( pStage->GetStageID() );
                SetFloatZ( WORLD_HEIGHT );       //  z????????????
                dwMapID = GetMapID();
                return;
            }
        }
        break;
    default:
        break;
    }

	//?????????? ??????????
	const MapConfig::RelivePosition* pRelivePosition = NULL;
	pRelivePosition = GetSpecRelivePosition(pMapData);
	if(!pRelivePosition)
	{
		pRelivePosition = GetRelivePosition(pMapData);
		if ( pRelivePosition == NULL )
			return;
	}
	if ( pRelivePosition != NULL )
    {
        SetMapID( pRelivePosition->MapId );
        SetFloatXF( pRelivePosition->PositionX );
        SetFloatYF( pRelivePosition->PositionY );
        SetFloatZ( WORLD_HEIGHT );

        dwMapID = pRelivePosition->MapId;
        nMapX = FloatToTile( pRelivePosition->PositionX );
        nMapY = FloatToTile( pRelivePosition->PositionY );
    }

   /* MapConfig::RelivePosition* pRelive = pMapData->GetRelivePositionByState( false );
    if ( pRelive != NULL )
    {
        SetMapID( pRelive->MapId );
        SetFloatXF( pRelive->PositionX );
        SetFloatYF( pRelive->PositionY );
        SetFloatZ( WORLD_HEIGHT );

        dwMapID = pRelive->MapId;
        nMapX = FloatToTile( pRelive->PositionX );
        nMapY = FloatToTile( pRelive->PositionY );
    }*/
}

void GamePlayer::AddEspecialItemCounter( uint16 itemId, uint32 itemCount)
{
    //if ( itemId == 407 || itemId == 408 || itemId == 409 )
    //{ _itemCounter[itemId] += itemCount; }
}

void GamePlayer::LogEspecialItemCounter()
{
    if ( _itemCounter.empty() )
    { return; }

    char szBuffer[1024] = {0};
    sprintf_s( szBuffer,"EspecialItemCounter:");
    ItrItemCounterContainer it = _itemCounter.begin();
    for ( ; it!=_itemCounter.end(); ++it )
    {
        char szTemp[250] = {0};
        sprintf_s( szTemp,"(%u:%u)-", it->first, it->second );
        HelperFunc::AddNCpy(szBuffer, szTemp, sizeof(szBuffer));
    }
    Log(szBuffer);
}


void GamePlayer::PlayerExitGameServer( unsigned char exitType )
{
	//????????
	if ( IsOpenStall() )
	{ CloseStall(); }

    //????????
    PetBreedInfo* pPetBreedInfo = thePetBreedManager.GetPetBreed( GetPetBreedID() );
    if ( pPetBreedInfo != NULL )
    {
        thePetBreedManager.RemovePetBreed( pPetBreedInfo->GetID(), EPetBreed_FinishCancel );
    }

    if ( HaveProtectChar() )    // ??????
    {
        BaseCharacter* pChar = theRunTimeData.GetCharacterByID( m_ProtectCharID );
        if ( pChar != NULL && pChar->IsMonster() )
        {   
            MonsterBaseEx* pAiMonster = static_cast< MonsterBaseEx* >( pChar );
            if ( pAiMonster->GetVarID() != -1 )
            { SetVar( pAiMonster->GetVarID(), 0 ); }
        }
    }

    if ( HaveSummonPet() )    // ????????
    {
        for (int i=0;i<CharSummonPetMaxCount; ++i)
        {
            MonsterBaseEx* pTarget = (MonsterBaseEx*) theRunTimeData.GetCharacterByID( m_xSummonPets[i].petId );
            if (pTarget != NULL && pTarget->IsMonster())
            {
                pTarget->SetDead();
                pTarget->WasKilled( this );
            }

            m_xSummonPets[i].Clear();
        }
    }

    if ( HaveCapturePet() ) // ????????
    {
        MonsterBaseEx* pTarget = (MonsterBaseEx*) theRunTimeData.GetCharacterByID( GetCapturePetId() );
        if (pTarget != NULL && pTarget->IsMonster())
        {
            pTarget->SetDead();
            KillCapturePet();
        }
    }

	int64 ID = GetCharInfo().otherdata.nsuanimalID;

    if ( _petManager.HaveActivePet() ) // ??????
    { _petManager.LostActivePetMonster(); }

	if(ID != 0)
		 GetCharInfo().otherdata.nsuanimalID = ID;

    if ( m_nDriverId != InvalidGameObjectId )
    { 
        _mountManager.AllPlayerGotOffMultiMount();
        GotOffMultiMount(); 
    }

    if ( m_nBigShipId != InvalidGameObjectId )
    {
        BaseCharacter* pChar = theRunTimeData.GetCharacterByID( m_nBigShipId );
        if ( pChar && pChar->GetObjType() == Object_NpcShip )
        {
            NpcShipEx* pNpcShip = (NpcShipEx*)pChar;
            pNpcShip->OffShip( GetID() );
            OffNpcShip();
        }
    }

    // ????????
    //m_graphiccodecheck.SaveCheckState();

    // ????????????????????
    CheckPosRightful();

    // ????
    theDuelHandler()->RemoveDuel( GetID(), false );

    // ????
    theBargainingManager.RemoveBargaining( GetBargainingID(), BargainingDefine::FinishOutLine );

    // ????????????????
    CampBattle* pCampBattle = theCampBattleControl.GetCampBattle( GetFightCamp(), GetMapID() ,GetCountryId());
    if ( pCampBattle != NULL )
    { pCampBattle->ProcessBattlePlayerOutLine( this ); }

    // ????????????
    ProcessDeathExitRelive();
	// ????????
	CorrectMapID();

    // ????????
    _NormalItemBag.CheckItemBag();
    _MaterialItemBag.CheckItemBag();
    _TaskItemBag.CheckItemBag();

    // ????????????
    theRabotManager.RemoveCheckPlayer( GetDBCharacterID() );
    // ????????????????
    thePubQuestManager.RemoveSpecialQuest( GetDBCharacterID() );
    // ????????????????
    theConQuestManager.RemoveSpecialQuest( GetDBCharacterID() );

	// ??????????????????????????????????????????????????
	GameTeam* pTeam = theGameTeamManager.GetTeamByMemberID( GetDBCharacterID() );
	if ( pTeam )
	{
		GamePlayer* pPlayer = theRunTimeData.GetGamePlayerByDBID( GetDBCharacterID() );
		if ( pPlayer && pTeam->IsTeamHeader( GetDBCharacterID() ) )
		{
			MsgHeaderCancelTeamFollow msgReq;
			pPlayer->OnHeaderCancelTeamFollow( &msgReq );
		}

		// ????????????????????????????????????????????????????
		if ( pPlayer && !pTeam->IsTeamHeader( GetDBCharacterID() ) )
		{
			for ( int i = 0; i < pTeam->TeamMemberCount(); ++i )
			{
				unsigned int nMemberID = pTeam->GetMemberIDByIndex(i);
				GamePlayer* pMember = theRunTimeData.GetGamePlayerByDBID( nMemberID );
				if ( pMember && pMember->GetDBCharacterID() == GetDBCharacterID() )
				{
					GameTeamMember* pMemberSelf = pTeam->GetTeamMemberByIndex( i );
					GameTeamMember* pMemberFellow = pTeam->GetTeamMemberByID( pMemberSelf->GetTeamFollowMemberID() );
					if ( pMemberFellow )
					{
						unsigned long nTeamLeaderID = pTeam->GetTeamHeaderID();
						GamePlayer* pLeader = theRunTimeData.GetGamePlayerByDBID( nTeamLeaderID );
						if ( pLeader )
						{
							// ????????????????????
							MsgTeamMemberAck memberAck;
							HelperFunc::SafeNCpy( memberAck.strMemberName, this->GetCharName(), MAX_NAME_STRING/*sizeof( this->GetCharName() )*/ );
							memberAck.nType     = MsgTeamMemberAck::ECD_CancelFollow;
							GettheServer().SendMsgToSingle( &memberAck, pLeader );
						}
					}
				}
			}

		}

	}

    if ( theRunTimeData.GetEnterWorldOnlinePlayer() > 0 )
    { theRunTimeData.IncreaseEnterWorldOnlinePlayer( -1 ); }

    // TODO: ?????????????????? ???????????????????????????????? ????????????
    if ( !_bInLoginStage )
    { theGameWorld.GlobalMessage( GameWorld::ExtMsg_DelCharacter,GetID() ); }
    
    MsgExit exit;
    exit.header.stID = GetID();
	exit.ExitType = exitType;
    GettheServer().SendMsgToView( &exit, GetID(), exitType == ET_SwitchGameServer );

	//lyh++ ???????????????????????? ??????
	/*const CountryConfig::ReliveSetting& xReliveSetting = theCountryConfig.GetReliveSetting();
	uint8 nFreeReliveLimit = xReliveSetting.GetFreeReliveLimitByLevel( GetLevel() );
	if (GetFreeReliveCount() >= nFreeReliveLimit)
		gCharInfoServer.baseinfo.liveinfo.nFreeReliveCount = nFreeReliveLimit ;*/

    switch ( exitType )
    {
    case ET_ExitGame:
    case ET_BeKick:
	case ET_SystemBeKick:
        {
            // ??????DB  ??????????ExitWorld?? ReturnCharacter??????ExitWorld?? ???? ????????????????????????ExitWorld??
            ClearCharRunTimeData();
            GettheFileDB().SaveCharAllData( this, EST_ExitWorld );
        }
        break;
    default:
        break;
    }
}

void GamePlayer::ProcessDeathExitRelive()
{
    if( m_bDeathAndWaitForRelive )
    {   
        SReliveInfo xReliveInfo;
        xReliveInfo.bSendMessage = false;
        xReliveInfo.bDeathExit = true;
        ProcessRelive( eReliveTypeNearPos, xReliveInfo );
    }
}

void GamePlayer::ProcessExitGameInTPHJ(DBMsgSaveCharacter& msg)
{
	if (EctypeId2MapId( GetMapID() ) == theTPHJManager.GetMapIdByRank(GetTPHJRank()))
	{
		msg.dbInfo.otherdata.pos.dwMapID = GetLastMapID_BeforeTPHJ();
		msg.dbInfo.otherdata.pos.stX     = FloatToTile( GetLastX_BeforeTPHJ() );
		msg.dbInfo.otherdata.pos.stY     = FloatToTile( GetLastY_BeforeTPHJ() );
		msg.dbInfo.otherdata.pos.vPos.x = GetLastX_BeforeTPHJ();
		msg.dbInfo.otherdata.pos.vPos.y = GetLastY_BeforeTPHJ();		
	}
}

void GamePlayer::SetVar( int nKey, int nVar, int nOp /* = SKW_SET */, unsigned char uchSendMessage /* = BV_SendMessage */ )
{
    CScriptVarMgr::E_VarType eType = CScriptVarMgr::GetKeyType( nKey );

    int nIndex = CScriptVarMgr::GetKeyIndex( eType, nKey );
    if ( nIndex < 0 )
    {
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "????????GamePlayer::SetVar(%d,%d,%d) Type%d,Index%d", nKey, nVar, nOp, eType, nIndex );
        return;
    }
    short* pShort = NULL;
    int*  pInt = NULL;
    switch( eType ) 
    {
    case CScriptVarMgr::VT_CHAR:        
        if ( nIndex < More_iMaxVars )
        {
            pShort = &gCharInfoServer.otherdata.vars.szVars[nIndex];
        }
        break;
    case CScriptVarMgr::VT_TEMP:
        if ( nIndex < More_iMaxTempVars )
        {
            pInt = &m_nTempVars[nIndex];
        }   
        break;
    case CScriptVarMgr::VT_SYS:
        pInt = GetScriptVarMgr()->GetSysVar( nIndex );            
        break;
    default:
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "SetVar Invalid eType = %d", eType );
        return;
    }

    switch( nOp ) 
    {
        // +=
    case SKW_SETADD:
        if(pShort) *pShort += nVar;
        if(pInt) *pInt += nVar;
        break;
        // -=
    case SKW_SETSUB:
        if(pShort) *pShort -= nVar;
        if(pInt) *pInt -= nVar;
        break;
        // =
    case SKW_SET:
        if(pShort) *pShort = nVar;
        if(pInt) *pInt = nVar;
        break;
        // *=
    case SKW_SETMUL:
        if(pShort) *pShort *= nVar;
        if(pInt) *pInt *= nVar;
        break;
        // /=
    case SKW_SETDIV:
        if ( nVar != 0 )
        {
            if(pShort) *pShort /= nVar;
            if(pInt) *pInt /= nVar;
        }
        break;
    case SKW_SETRES:
        if ( nVar != 0 )
        {
            if(pShort) *pShort %= nVar;
            if(pInt) *pInt %= nVar;
        }
        break;
    default:
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "SetVar Invalid nOp");
        return;
    }

//#define MAX_VAR_VALUE 127
//#define MIN_VAR_VALUE -127
//	if (pShort)
//	{
//		if (*pShort > MAX_VAR_VALUE)
//		{
//			*pShort = MAX_VAR_VALUE;
//		}
//		else if (*pShort < MAX_VAR_VALUE)
//		{
//			*pShort = MIN_VAR_VALUE;
//		}
//	}

    // ????????????????????????????CenterServer????????????
    if (eType == CScriptVarMgr::VT_SYS)
    {
        GS2CSSendChangeVarReq xChangeReq;
        xChangeReq.serverId = g_Cfg.dwServerID;
        xChangeReq.nIndex = nIndex;
        xChangeReq.nVar = *pInt;                  // Var??
        sprintf( xChangeReq.szName, "%s", GetScriptVarMgr()->GetVarNameByIndex(nIndex) ); // Var???? ID
        GettheServer().SendMsgToCenterServer( &xChangeReq );
    }

    if ( uchSendMessage == BV_NotSendMessage )
    { return; }

    // ??????????
    if ( eType == CScriptVarMgr::VT_CHAR && pShort )
    {
        MsgTellCharVar msg;
        msg.AddValue( nIndex, *pShort );
        GettheServer().SendMsgToSingle( &msg, this );
    }
    else if ( eType == CScriptVarMgr::VT_GUILD && pShort != NULL )
    {
        TellGuildVar( nIndex, *pShort );
    }
}

int GamePlayer::GetVar( int nKey )
{
    CScriptVarMgr::E_VarType eType = CScriptVarMgr::GetKeyType( nKey );

    int nIndex = CScriptVarMgr::GetKeyIndex( eType, nKey );
    if ( nIndex < 0 )
    { return 0; }

    switch( eType ) 
    {
    case CScriptVarMgr::VT_CHAR:
        if ( nIndex < More_iMaxVars )
        {
            return gCharInfoServer.otherdata.vars.szVars[nIndex];
        }
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "%s ??????????????????????????", GetCharName());
        break;
    case CScriptVarMgr::VT_TEMP:
        if ( nIndex < More_iMaxTempVars )
        {
            return m_nTempVars[nIndex];
        }
        LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "%s ??????????????????????????", GetCharName());
        break;
    case CScriptVarMgr::VT_SYS:
        {
            int *pInt = GetScriptVarMgr()->GetSysVar( nIndex );
            if( pInt )
            {
                return *pInt;
            }
            LOG_MESSAGE( SCRIPTOBJECT, LOG_PRIORITY_ERROR, "%s ??????????????????????????", GetCharName());
        }
        break;
    case CScriptVarMgr::VT_GUILD:
        {
            return GetGuildVar( nIndex );
        }
        break;
    default:
        break;
    }
    return 0;
}

void GamePlayer::InitCharacter( const SCharDBInfo& dbSaveInfo, const SRuntimeInfo& dbRunInfo )
{
    // ????????
	/*for (int i = 0; i < dbSaveInfo.baseinfo.liveinfo.ucMountCount; i++)
	{
		UpdateMountWrongData(const_cast<SMountItem*>(&dbSaveInfo.itemData.miItems[i]));
	}*/
	
    gCharInfoServer      = dbSaveInfo; // ????????????????
    gTransferRuntimeInfo = dbRunInfo;  // ????????????????

	if(gCharInfoServer.otherdata.nThreeDayVision != ThreeDayConfig::Instance().GetVision())
	{
		gCharInfoServer.otherdata.nThreeDayValue = 0;
		gCharInfoServer.otherdata.nThreeDayVision = ThreeDayConfig::Instance().GetVision();
	}

	OnCheckKillPlayerSum();
	//????????????
	RefreshHeroSkill();

	//????????????????????????
	GameGuild * pGuild =theGameGuildManager.GetGuildByPlayerID(GetDBCharacterID());
	unsigned int GuildID = (pGuild?pGuild->GetID():0);
	if(GuildID != GetGuildID())
	{
		SetGuildID(GuildID);
		gCharInfoServer.otherdata.nGuildID = GuildID;
	}

    // ????,  ????, ????, 3??????????????????,
    // ??????????????
    InitPlayerGuild();

	// ??????????????
	InitPlayerFamily();

    // ????
    GameCountry* pCountry = theGameCountryManager.GetCountry( gCharInfoServer.baseinfo.aptotic.ucCountry );
    InitPlayerCountry( pCountry );

    // ????????????
    InitCountryTitle( false );  

    // ????????????
    GameRelation* pRelation = theGameRelationManager.GetPlayerRelation( GetDBCharacterID(), true );
	if(pRelation)
		InitPlayerRelation( pRelation );

    // ????
    gCharInfoServer.baseinfo.liveinfo.ustLevel = theExpStage.GetLevel( gCharInfoServer.baseinfo.liveinfo.dwExp );
    if( gCharInfoServer.baseinfo.liveinfo.ustLevel > g_Cfg.m_nLevelLimt )
    { gCharInfoServer.baseinfo.liveinfo.ustLevel = g_Cfg.m_nLevelLimt; }                
    SetLevel( gCharInfoServer.baseinfo.liveinfo.ustLevel );

    // ????
    SetBodySize( CHAR_DEFAULTBODYSIZE );

    // ????
    SetCharName( gCharInfoServer.baseinfo.aptotic.szCharacterName );
    _buffManager.SetCharName( GetCharName() );

    // ???? ????????float????????????????????float????????????????????????,??????????
    SetMapID  ( gCharInfoServer.otherdata.pos.dwMapID );
    SetTileX  ( gCharInfoServer.otherdata.pos.stX     );
    SetTileY  ( gCharInfoServer.otherdata.pos.stY     );          
    SetFloatX ( gCharInfoServer.otherdata.pos.vPos.x  );
    SetFloatY ( gCharInfoServer.otherdata.pos.vPos.y  );
    SetFloatZ ( gCharInfoServer.otherdata.pos.vPos.z  );
    SetDirX   ( gCharInfoServer.otherdata.fDirX       );
    SetDirY   ( gCharInfoServer.otherdata.fDirY       );

    // ????????
    gCharInfoServer.baseinfo.liveinfo.activityMax = ProcessCharInfo::ActivityMax( GetLevel() );
    gCharInfoServer.baseinfo.liveinfo.vigorMax  = ProcessCharInfo::VigorMax( GetLevel() );

    // ???? (Center ?????????????????????????? ????????0, ????????????????????)
    if ( gCharInfoServer.baseinfo.liveinfo.ucNormalBagSize < g_Cfg.m_nCreatBagSize )
    { gCharInfoServer.baseinfo.liveinfo.ucNormalBagSize = g_Cfg.m_nCreatBagSize; }

    if ( gCharInfoServer.baseinfo.liveinfo.ucMaterialBagSize < g_Cfg.m_nCreateMaterialSize )
    { gCharInfoServer.baseinfo.liveinfo.ucMaterialBagSize = g_Cfg.m_nCreateMaterialSize; }

    if ( gCharInfoServer.baseinfo.liveinfo.nStorageItemGrid < g_Cfg.m_nStorageItemGrid )
    { gCharInfoServer.baseinfo.liveinfo.nStorageItemGrid = g_Cfg.m_nStorageItemGrid; }

    if ( gCharInfoServer.baseinfo.liveinfo.nStorageMountGrid < g_Cfg.m_nStorageMountGrid )
    { gCharInfoServer.baseinfo.liveinfo.nStorageMountGrid = g_Cfg.m_nStorageMountGrid; }

    if ( gCharInfoServer.baseinfo.liveinfo.ucMountCount < ITEM_MOUNT_MAXCOUNT )
    { gCharInfoServer.baseinfo.liveinfo.ucMountCount = ITEM_MOUNT_MAXCOUNT; }

    // ??????????????
    InitPlayerTitleList(); 

    // ????cd
    m_RestoreColdDown.InitColdDown( gCharInfoServer.baseinfo.liveinfo.xItemColdDown, MAX_SAVERESTORE_COUNT );

    // ??????????
    _accumulateEneryTime = gCharInfoServer.extendData.xRunTime.nEneryTime;
    _accumulateVigorTime = gCharInfoServer.extendData.xRunTime.nVigorTime;
    _mountManager.SetAccumulateActionTime( gCharInfoServer.extendData.xRunTime.nMountActionTime );

    // ????????
    SetBanSpeakTime( gCharInfoServer.otherdata.dwBanSpeakTime * 60000 );

    // ????
    _NormalItemBag.CreateFromData  ( this, gCharInfoServer.itemData.stPackItems,     GetNormalBagSize(),   BT_NormalItemBag );
    _MaterialItemBag.CreateFromData( this, gCharInfoServer.itemData.ciMaterialItems, GetMaterialBagSize(), BT_MaterialBag   );
    _TaskItemBag.CreateFromData    ( this, gCharInfoServer.itemData.ciTaskItems,     GetTaskBagSize(),     BT_TaskBag       );

    // ????`
    //InitKillInfoFromData( gCharInfoServer.extendData.xKillInfo, MAX_KILLINFO_COUNT );

    // ????
    _mountManager.CreateFromData( this, gCharInfoServer.itemData.miItems,  GetMountCount() ); 

    // ????
    _petManager.CreateFromData( this, gCharInfoServer.itemData.petItems, ITEM_PET_MAXCOUNT );

    // ????
    _achieveManager.CreateFromData( this, &gCharInfoServer.achieveData );

    // ????
    CheckCountryMount();        // ????????????

    // ???? 
    _recipeManager.CreateFromData( this, gCharInfoServer.otherdata.recipes, MAX_RECIPE_COUNT );

    // ????????
    _SkillBag.Init( gCharInfoServer.otherdata.skills.skill, More_iMaxSkillKnown );

	//????????????
	_HeroSkillBag.Init(gCharInfoServer.otherdata.skills.heroSkill, More_iMaxHeroSkill);

    // ????
    _XinFaManager.Init( gCharInfoServer.otherdata.skills.xinfa, More_iMaxXinFa  );

    // ????????
    _buffManager.CreateFromData( this, _buffs, BodyStatusType_Max);
    _buffManager.AddStatusFromData( GetMapID(), gCharInfoServer.otherdata.sCharBodyStatus, BodyStatusType_Max, HQ_TimeGetTime(), _bFirstEnterWorld );

    // ??????(??????????)????????
    SetCauseStatusID( -1 ); 

    // ????????
    UpdateAllEquipData();

    // ????????
    ApplyTalentXinFaToChar();

    // ????????????
    ApplyPassiveSkillsToChar();

    // ????????
    _mountManager.ApplyMountAttributeToChar( true, false );

    // buff????
    //_buffManager.ApplyBuffsToChar( GetProfession(), GetCharBaseAttr(), GetCharFightAttr() );
	//????????BUFF
	HandlePlayerCountryBuff();
    ApplyBuffStatusToCharAttr();

    // ????????
    UpdateBaseAttrByAllTitle(false);
    UpdateTitleListByDataBaseTop10();

    // ????
	_suitManager.SetPlayer(this);
    UpdateAllSuitData() ;

    // ????????
    RecalcBaseProperty( true, BV_NotFullHp, BV_NotSendMessage, EWRP_Init );

    // ????????
    if (HaveFighteFlag(eSitting))
    { OnSitDownRestore(); } // ??????????????
    else
    { OnStandUpRestore(); } // ??????????????

    if ( gCharInfoServer.otherdata.bNewChar )
    { // ???????? ????????
        SetHP( GetCharFightAttr()->hpMax.final );
        SetMP( GetCharFightAttr()->mpMax.final );
        SetXP( DEF_CHAR_XP_LIMIT );
        gCharInfoServer.baseinfo.liveinfo.activity = gCharInfoServer.baseinfo.liveinfo.activityMax;
        gCharInfoServer.baseinfo.liveinfo.vigor    = gCharInfoServer.baseinfo.liveinfo.vigorMax;
    }

    // ??????????????????????
    UpdateCommonData( BV_NotForSaveDb ); 

	CalcCanTakeExp();

	OnRoleOnLineQuestEntrustHandle();

	m_IsCanDead = true;

#ifdef NPGUARD
	_authManager.InitPlayerCSAuth(this);
#endif
}

bool GamePlayer::IsCanAutoSaveToDB()
{ // ????????????????
    if (!IsCanSaveToDB())
    { return false; }

    return GameTime::IsPassCurrentTime( m_PreSaveTime, g_Cfg.dwAutoSaveDelay );
}

void GamePlayer::ApplyBaseAttrToFightAttr( bool total, uint16 part, bool bAdd )
{
    for ( uint8 i=0; i<EBaseAttr_MaxSize; ++i)
    { 
        if ( total )
        { ProcessCharInfo::BaseAttrEffectFightAttr( i, part, *GetBaseAttr( i ), GetProfession(), *GetCharFightAttr(), true ); }
        else
        { ProcessCharInfo::BaseAttrEffectFightAttr( i, part, *GetAddSubBaseAttr( i ), GetProfession(), *GetCharFightAttr(), bAdd ); }
        GetAddSubBaseAttr(i)->ClearPart( part );
    }
}

void GamePlayer::ApplyBuffStatusToCharAttr()
{
    // ????Buff????????????????
    GetCharBaseAttr()->ClearPart( ECustomDataPart_status );

    // ????Buff????????????????
    GetCharFightAttr()->hpMax            .status = 0 ;
    GetCharFightAttr()->mpMax            .status = 0 ;
    GetCharFightAttr()->attackPhysics    .status = 0 ;
    GetCharFightAttr()->attackMagic      .status = 0 ;
    GetCharFightAttr()->defendPhysics    .status = 0 ;
    GetCharFightAttr()->defendMagic      .status = 0 ;
    GetCharFightAttr()->attackSpeed      .status = 0 ;
    GetCharFightAttr()->moveSpeed        .status = 0 ;
    GetCharFightAttr()->hpRestore        .status = 0 ;
    GetCharFightAttr()->mpRestore        .status = 0 ;
    GetCharFightAttr()->exact            .status = 0 ;
    GetCharFightAttr()->dodge            .status = 0 ;
    GetCharFightAttr()->critical         .status = 0 ;
    GetCharFightAttr()->tenacity         .status = 0 ;
    GetCharFightAttr()->criticalIntensity.status = 0 ;
    GetCharFightAttr()->backStrike       .status = 0 ;
    GetCharFightAttr()->backStrikeResist .status = 0 ;
    GetCharFightAttr()->breakStrike      .status = 0 ;
    GetCharFightAttr()->stabStrike       .status = 0 ;
    GetCharFightAttr()->elementStrike    .status = 0 ;
    GetCharFightAttr()->toxinStrike      .status = 0 ;
    GetCharFightAttr()->spiritStrike     .status = 0 ;
    GetCharFightAttr()->breakResist      .status = 0 ;
    GetCharFightAttr()->stabResist       .status = 0 ;
    GetCharFightAttr()->elementResist    .status = 0 ;
    GetCharFightAttr()->toxinResist      .status = 0 ;
    GetCharFightAttr()->spiritResist     .status = 0 ;
    GetCharFightAttr()->hpMax            .statusPer = 0 ;
    GetCharFightAttr()->mpMax            .statusPer = 0 ;
    GetCharFightAttr()->attackPhysics    .statusPer = 0 ;
    GetCharFightAttr()->attackMagic      .statusPer = 0 ;
    GetCharFightAttr()->defendPhysics    .statusPer = 0 ;
    GetCharFightAttr()->defendMagic      .statusPer = 0 ;
    GetCharFightAttr()->attackSpeed      .statusPer = 0 ;
    GetCharFightAttr()->moveSpeed        .statusPer = 0 ;
    GetCharFightAttr()->hpRestore        .statusPer = 0 ;
    GetCharFightAttr()->mpRestore        .statusPer = 0 ;
    GetCharFightAttr()->exact            .statusPer = 0 ;
    GetCharFightAttr()->dodge            .statusPer = 0 ;
    GetCharFightAttr()->critical         .statusPer = 0 ;
    GetCharFightAttr()->tenacity         .statusPer = 0 ;

    int nXinFaAddBaseAttr[EBaseAttr_MaxSize] =  { 0 } ;

    // ?????????????????????? ????????????????????????????????
    for (int i=0; i<_buffManager.GetBufferStatusCount(); ++i)
    {
        SCharBuff* pCharBuff = _buffManager.GetBuff( i );
        if( pCharBuff == NULL )
        { continue; }

        if ( pCharBuff->eventType != SCharBuff::StatusEventType_Skill )
        { continue; }

        ItemDefine::SItemStatus* pStatus = GettheItemDetail().GetStatus( pCharBuff->StatusID, pCharBuff->iLevel);
        if ( pStatus == NULL )
        { continue; }

        ItemDefine::SItemSkill*  pSkill  = GettheItemDetail().GetSkillByID( pCharBuff->eventValue, 1 );
        if ( pSkill == NULL )
        { continue; }

        int nXinFaSkillAttr[SkillAttr_MaxSize] =  { 0 } ;
        BaseCharacter* pMasterChar =  theRunTimeData.GetCharacterByID( pCharBuff->masterId ) ; 
        if ( pMasterChar != NULL && pMasterChar->IsPlayer() )
        {
            GamePlayer* pMasterPlayer = static_cast< GamePlayer* >( pMasterChar );
            ItemDefine::SItemSkill* pSkillConfig = GettheItemDetail().GetSkillByID( pCharBuff->eventValue, 1 );
            if (pSkillConfig != NULL)
            { pMasterPlayer->GetXinFaSkillEffect( pSkillConfig, nXinFaSkillAttr ); }
        }

        nXinFaAddBaseAttr[EBaseAttr_Strength]     += nXinFaSkillAttr[StatusAttr_Strength]; 
        nXinFaAddBaseAttr[EBaseAttr_Agility]      += nXinFaSkillAttr[StatusAttr_Agility] ; 
        nXinFaAddBaseAttr[EBaseAttr_Stamina]      += nXinFaSkillAttr[StatusAttr_Stamina] ; 
        nXinFaAddBaseAttr[EBaseAttr_Intelligence] += nXinFaSkillAttr[StatusAttr_Intelligence]; 
    }

    for (uint8 i=0; i<EBaseAttr_MaxSize; ++i)
    { 
        // ????????????
        GetBaseAttr( i )->status    += _buffManager.GetAddBaseAttr   (i) + nXinFaAddBaseAttr[i];
        GetBaseAttr( i )->statusPer += _buffManager.GetAddBaseAttrPer(i);

        // ????????????????????
        ProcessCharInfo::BaseAttrEffectFightAttr( i, ECustomDataPart_status, *GetBaseAttr( i ), GetProfession(), *GetCharFightAttr() ); 
    }

    // ????????????
    for (int i=0; i<_buffManager.GetBufferStatusCount(); ++i)
    {
        SCharBuff* pCharBuff = _buffManager.GetBuff( i );
        if( pCharBuff == NULL )
        { continue; }

        ItemDefine::SItemStatus* pStatus = GettheItemDetail().GetStatus( pCharBuff->StatusID, pCharBuff->iLevel);
        if ( NULL == pStatus )
        { continue; }

        int nXinFaSkillAttr[SkillAttr_MaxSize] =  { 0 } ;
        if ( SCharBuff::StatusEventType_Skill == pCharBuff->eventType )
        {
            BaseCharacter* pMasterChar =  theRunTimeData.GetCharacterByID( pCharBuff->masterId ) ; 
            if ( pMasterChar != NULL && pMasterChar->IsPlayer() )
            {
                GamePlayer* pMasterPlayer = static_cast< GamePlayer* >( pMasterChar );
                ItemDefine::SItemSkill* pSkillConfig = GettheItemDetail().GetSkillByID( pCharBuff->eventValue, 1 );
                if (pSkillConfig != NULL)
                { pMasterPlayer->GetXinFaSkillEffect( pSkillConfig, nXinFaSkillAttr ); }
            }
        }
        
        GetCharFightAttr()->moveSpeed.status        += pStatus->fMoveSpeedChanged;                  // ??????????????????
        GetCharFightAttr()->moveSpeed.statusPer     += pStatus->nMoveSpeedPer;                      // ?????????????????? %

        GetCharFightAttr()->attackPhysics.status    += pStatus->changePhyAttack + nXinFaSkillAttr[StatusAttr_PhysicsAttack];  // ??????????
        GetCharFightAttr()->attackPhysics.statusPer += pStatus->changePhyAttackPer;                                          // ??????????%
        GetCharFightAttr()->attackMagic.status      += pStatus->changeMagAttack + nXinFaSkillAttr[StatusAttr_MagicAttack];    // ??????????
        GetCharFightAttr()->attackMagic.statusPer   += pStatus->changeMagAttackPer;                                          // ??????????%

        GetCharFightAttr()->defendPhysics.status    += pStatus->changeDefend[EDefendType_Physical] + nXinFaSkillAttr[StatusAttr_PhysicsDefend]; // ????
        GetCharFightAttr()->defendPhysics.statusPer += pStatus->changeDefendPer[EDefendType_Physical];  // ????%
        GetCharFightAttr()->defendMagic.status      += pStatus->changeDefend[EDefendType_Magic]    + nXinFaSkillAttr[StatusAttr_MagicDefend];   // ????
        GetCharFightAttr()->defendMagic.statusPer   += pStatus->changeDefendPer[EDefendType_Magic]; // ????%

        GetCharFightAttr()->hpRestore.status        += pStatus->resumeHP;                           // ????HP????????????
        GetCharFightAttr()->hpRestore.statusPer     += pStatus->resumeHPPer;                        // ????HP????????????%
        GetCharFightAttr()->mpRestore.status        += pStatus->resumeMP;                           // ????MP????????????
        GetCharFightAttr()->mpRestore.statusPer     += pStatus->resumeMPPer;                        // ????MP????????????%
        GetCharFightAttr()->hpMax.status            += pStatus->stChanged_HPMax;                    // ??????????
        GetCharFightAttr()->hpMax.statusPer         += pStatus->changeHPMaxPer;                     // ??????????%
        GetCharFightAttr()->mpMax.status            += pStatus->stChanged_MPMax;                    // ??????????
        GetCharFightAttr()->mpMax.statusPer         += pStatus->changeMPMaxPer;                     // ??????????%
        GetCharFightAttr()->dodge.status            += pStatus->stChanged_Hedge + nXinFaSkillAttr[StatusAttr_Exact] ;   // ????????
        GetCharFightAttr()->exact.status            += pStatus->stChanged_Hit   + nXinFaSkillAttr[StatusAttr_Dodge ] ;   // ????
        GetCharFightAttr()->critical.status         += pStatus->changed_Critical+ nXinFaSkillAttr[StatusAttr_Critical] ; // ??????
        GetCharFightAttr()->criticalIntensity.status+= pStatus->changed_CriticalIntensity  + nXinFaSkillAttr[StatusAttr_CriticalIntensity] ;    // ????????
        GetCharFightAttr()->tenacity.status         += pStatus->changeTenacity  + nXinFaSkillAttr[StatusAttr_Tenacity];    // ????????

        GetCharFightAttr()->breakStrike.status      += pStatus->breakStrike;           
        GetCharFightAttr()->stabStrike.status       += pStatus->stabStrike;
        GetCharFightAttr()->spiritStrike.status     += pStatus->spiritStrike;   
        GetCharFightAttr()->toxinStrike.status      += pStatus->toxinStrike;    
        GetCharFightAttr()->elementStrike.status    += pStatus->elementStrike;   

        GetCharFightAttr()->breakResist.status      += pStatus->breakResist;           
        GetCharFightAttr()->stabResist.status       += pStatus->stabResist;
        GetCharFightAttr()->spiritResist.status     += pStatus->spiritResist;   
        GetCharFightAttr()->toxinResist.status      += pStatus->toxinResist;    
        GetCharFightAttr()->elementResist.status    += pStatus->elementResist;   

        GetCharFightAttr()->attackSpeed.statusPer   += pStatus->fAttSpeedPer ;                      // ????????
        
    }

    GetCharFightAttr()->hpMax            .UpdateFinal();
    GetCharFightAttr()->mpMax            .UpdateFinal();
    GetCharFightAttr()->attackPhysics    .UpdateFinal();
    GetCharFightAttr()->attackMagic      .UpdateFinal();
    GetCharFightAttr()->defendPhysics    .UpdateFinal();
    GetCharFightAttr()->defendMagic      .UpdateFinal();
    GetCharFightAttr()->attackSpeed      .UpdateFinal();
    GetCharFightAttr()->moveSpeed        .UpdateFinal();
    GetCharFightAttr()->hpRestore        .UpdateFinal();
    GetCharFightAttr()->mpRestore        .UpdateFinal();
    GetCharFightAttr()->exact            .UpdateFinal();
    GetCharFightAttr()->dodge            .UpdateFinal();
    GetCharFightAttr()->critical         .UpdateFinal();
    GetCharFightAttr()->tenacity         .UpdateFinal();
    GetCharFightAttr()->criticalIntensity.UpdateFinal();
    GetCharFightAttr()->backStrike       .UpdateFinal();
    GetCharFightAttr()->backStrikeResist .UpdateFinal();
    GetCharFightAttr()->breakStrike      .UpdateFinal();
    GetCharFightAttr()->stabStrike       .UpdateFinal();
    GetCharFightAttr()->elementStrike    .UpdateFinal();
    GetCharFightAttr()->toxinStrike      .UpdateFinal();
    GetCharFightAttr()->spiritStrike     .UpdateFinal();
    GetCharFightAttr()->breakResist      .UpdateFinal();
    GetCharFightAttr()->stabResist       .UpdateFinal();
    GetCharFightAttr()->elementResist    .UpdateFinal();
    GetCharFightAttr()->toxinResist      .UpdateFinal();
    GetCharFightAttr()->spiritResist     .UpdateFinal();
}

////????????????????????????
//void GamePlayer::ApplyPassiveSkillsToPet( GameCharID PetID, int nSummonSkillID )
//{       
//    BaseCharacter* pPetChar = theRunTimeData.GetCharacterByID(PetID);
//    if ( pPetChar == NULL )
//    { return; }
//
//    if( pPetChar->IsMonster() )
//    {
//        for(int iLoop=0; iLoop<_SkillBag.GetSkillNum(); ++iLoop)
//        {
//            SCharSkill* pCharSkill = _SkillBag.GetSkillByIndex(iLoop);
//            if ( NULL == pCharSkill)
//            { continue; }
//
//            ItemDefine::SItemSkill *pSkill = GettheItemDetail().GetSkillByID( pCharSkill->ustSkillID, pCharSkill->stSkillLevel );
//            if( NULL == pSkill)
//            { continue; }
//
//            //??????????????
//            if( pSkill->stGeneralType != ItemDefine::generaltype_passive)
//            { continue; }
//
//            short shPassiveSkillTarget = pSkill->shPassiveSkillTarget;
//            if( shPassiveSkillTarget == CItemDetail::PassiveSkillTarget_TargetPet || shPassiveSkillTarget == CItemDetail::PassiveSkillTarget_SelfAndTargetPet )
//            {
//                if( pSkill->nPassiveSkillTargetSkillID != nSummonSkillID )
//                { continue; }
//            }
//            else
//            {
//                if( !(shPassiveSkillTarget == CItemDetail::PassiveSkillTarget_AllPet || shPassiveSkillTarget == CItemDetail::PassiveSkillTarget_SelfAndAllPet) )
//                { continue; }
//            }
//
//            //1??????????????2??????????
//            for (int i = 0;i < ItemDefine::SItemSkill::EItemSkillConst_AddStatusMaxSize; ++i )
//            {
//                ItemDefine::SItemStatus* pStatus = GettheItemDetail().GetStatus( pSkill->ustMeAddStatusID[i], pSkill->ustMeAddStatusLevel[i] );
//
//                if( NULL == pStatus)
//                { continue; }
//
//                //TODO: ???????????????????? ??????????????????
//                //pPetChar->GetCharFightAttr()->moveSpeed.skill        += pStatus->fMoveSpeedChanged;                  // ????????
//                //pPetChar->GetCharFightAttr()->attackSpeed.skill      += pStatus->fAttSpeedChanged;                   // ????????
//                //pPetChar->GetCharFightAttr()->intonate.skill         += pStatus->stPrepSpeedChanged;                 // ??????????????????
//                //pPetChar->GetCharFightAttr()->attackPhysics.skill           += pStatus->changeAttack;                       // ??????
//                //pPetChar->GetCharFightAttr()->attackPhysics.skillPer        += pStatus->changeAttackPer;                    // ??????%
//                //pPetChar->GetCharFightAttr()->defendPhysics.skill      += pStatus->changeDefend[EDefendType_Short];    // ????  
//                //pPetChar->GetCharFightAttr()->defendLong .skill      += pStatus->changeDefend[EDefendType_Long];     // ????
//                //pPetChar->GetCharFightAttr()->defendMagic.skill      += pStatus->changeDefend[EDefendType_Magic];    // ????
//                //pPetChar->GetCharFightAttr()->defendPhysics.skillPer   += pStatus->changeDefendPer[EDefendType_Short]; // ????%
//                //pPetChar->GetCharFightAttr()->defendLong .skillPer   += pStatus->changeDefendPer[EDefendType_Long];  // ????%
//                //pPetChar->GetCharFightAttr()->defendMagic.skillPer   += pStatus->changeDefendPer[EDefendType_Magic]; // ????%
//                //pPetChar->GetCharFightAttr()->hpRestore.skill        += pStatus->resumeHP;                           // ????HP????????????
//                //pPetChar->GetCharFightAttr()->hpRestore.skillPer     += pStatus->resumeHPPer;                        // ????HP????????????%
//                //pPetChar->GetCharFightAttr()->mpRestore.skill    += pStatus->resumeMP;                           // ????MP????????????
//                //pPetChar->GetCharFightAttr()->mpRestore.skillPer += pStatus->resumeMPPer;                        // ????MP????????????%
//                //pPetChar->GetCharFightAttr()->hpMax.skill            += pStatus->stChanged_HPMax;                    // ??????????
//                //pPetChar->GetCharFightAttr()->hpMax.skillPer         += pStatus->changeHPMaxPer;                     // ??????????%
//                //pPetChar->GetCharFightAttr()->mpMax.skill        += pStatus->stChanged_MPMax;                    // ??????????
//                //pPetChar->GetCharFightAttr()->mpMax.skillPer     += pStatus->changeMPMaxPer;                     // ??????????%
//                //pPetChar->GetCharFightAttr()->dodge.skill            += pStatus->stChanged_Hedge  * DEF_PER_INT ;    // ????????
//                //pPetChar->GetCharFightAttr()->exact.skill            += pStatus->stChanged_Hit    * DEF_PER_INT ;    // ????
//                //pPetChar->GetCharFightAttr()->critical.skill         += pStatus->changed_Critical;                   // ????       
//                //pPetChar->GetCharFightAttr()->tenacity.skill         += pStatus->changeTenacity;                     // ????
//                //pPetChar->GetCharFightAttr()->criticalIntensity.skill+= pStatus->changed_CriticalIntensity ;         // ????      
//            }
//        }
//    }
//
//    // Update
//    pPetChar->UpdateCharAllAttibute();
//}

void GamePlayer::UpdateAllEquipData()
{
    // ????????????
    ClearAllBaseAttrByPart ( ECustomDataPart_item );

    // ????????????
    ClearAllFightAttrByPart( ECustomDataPart_item );

    SetWeaponAttackRange( 0 );

    memset( m_stMeAddStatus    , 0, sizeof(m_stMeAddStatus    ) );
    memset( m_stMeAddStatusLvl , 0, sizeof(m_stMeAddStatusLvl ) );
    memset( m_stDstAddStatus   , 0, sizeof(m_stDstAddStatus   ) );
    memset( m_stDstAddStatusLvl, 0, sizeof(m_stDstAddStatusLvl) );
    memset( m_fDstStatusRate   , 0, sizeof(m_fDstStatusRate   ) );
    memset( m_fMeStatusRate    , 0, sizeof(m_fMeStatusRate    ) );

    for(int i=0; i<EEquipPartType_MaxEquitPart; ++i )
    {
        SCharItem* pItem = GetVisualEquipItem( i );
        if ( NULL == pItem)
        { continue; }

        // ????????????????????
        if( pItem->equipdata.usHP<=0 )
        { continue; }

        if ( pItem->itembaseinfo.ustItemID == InvalidLogicNumber || pItem->GetItemGuid() == 0 )
        { continue; }

        ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( pItem->itembaseinfo.ustItemID );
        if ( pItemCommon == NULL ||  !pItemCommon->IsCanEquip() )
        { continue; }

        ItemDefine::SItemCanEquip* pItemCanEquip = (ItemDefine::SItemCanEquip* )pItemCommon;
        if( pItemCanEquip == NULL )
        { continue; }

        if ( pItemCanEquip->bFashion && pItem->IsOverdue() )
        { continue; }       // ????????????????

        Equip( i, *pItem, false );
    }

    //????
    SCharItem* pTalismanItem = GetTalismanItem();
    ApplyTalismanRandAttributesToChar( pTalismanItem ,ECustomDataPart_item );

    // ????????????????????????
    ApplyBaseAttrToFightAttr( true, ECustomDataPart_item );
}

void GamePlayer::UpdateAllSuitData()
{
    _suitManager.ApplyToPlayer();
    // ????????????????????????
    ApplyBaseAttrToFightAttr( true, ECustomDataPart_suit );
}

bool GamePlayer::IsCanEquip( uint8 stWhere, SCharItem* pItem, bool bCheck /*= false*/ )
{       
    if( !pItem || GetHP() <= 0 || stWhere <0 || stWhere >= EEquipPartType_MaxEquitPart || pItem->equipdata.usHP <=0 )
    { return false; }

	if(CS_INTONATE == GetStatus())
	{
		//????????????????????
		SendChangeEquipErrorInfo();
		return false;
	}

    if( pItem->IsOverdue() )
    { return false; }

    if(pItem->itembaseinfo.ustItemID == InvalidLogicNumber)
    { return false; }

    ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( pItem->itembaseinfo.ustItemID );    
    if ( pItemCommon == NULL || !pItemCommon->IsCanEquip() )
    { return false; }

    ItemDefine::SItemCanEquip* pCanEquip = (ItemDefine::SItemCanEquip*)pItemCommon;

    // ??????????
    if( -1 != pCanEquip->cEquipSexReq && pCanEquip->cEquipSexReq != GetSex())
    { return false; }

    // ????????    
    if( !pCanEquip->arrayEquipArmsReq[GetProfession()] )
    { return false; }

    // ????????
    if (pCanEquip->stEquipLevelReq > GetLevel())
    { return false; }

    ////????????
    //if ( abs( pCanEquip->nPkValueNeed ) > abs( GetPKValue() ) )
    //{ return false; }
    //if ( pCanEquip->nPkValueNeed < 0 && pCanEquip->nPkValueNeed < GetPKValue() )
    //    return false;

    //if (pCanEquip->nPkValueNeed > 0 && pCanEquip->nPkValueNeed > GetPKValue())
    //    return false;

    //????????

    //????????
    if ( pCanEquip->nTitleNeed != TitleConfig::Init_ID && !IsHaveTitle( pCanEquip->nTitleNeed ) )    
    { return false; }

    //????????

    //????????????
    if ( pItemCommon->ucItemType == ItemDefine::ITEMTYPE_WEAPON)
    {
        ItemDefine::SItemWeapon* pItemWeapon = (ItemDefine::SItemWeapon*)pCanEquip;
        if ( pItemWeapon->stWeaponType == eWeapontype_Flag )
        { 
            if ( m_pGuild == NULL || m_pGuild->GetID() != pItem->itembaseinfo.value1 )
            { return false; }

            GuildMember* pMember = m_pGuild->GetMember( GetDBCharacterID() );
            if ( pMember == NULL || pMember->GetPosition() != GuildDefine::Position_ViceMaster )
            { return false; }
        }
    }

    int8 stCan = pCanEquip->arrayCanEquip[ stWhere  ];
    if ( stCan == 1)
    { // ????????
        return true;
    }
    else
    { return false; }

    return true;
}

bool GamePlayer::Equip( uint8 part, SCharItem& item, bool bJustSetItem )
{       
    bool bRetOp = true;

    //???????????????? 
    if (item.itembaseinfo.ustItemID == InvalidLogicNumber)
    { return false; }

    //??????????????
    if (part < 0 || part >= EEquipPartType_MaxEquitPart)
    { return false; }

    // ????????????????????
    if (!IsCanEquip( part, &item))
    { return false; }

    ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( item.itembaseinfo.ustItemID );
    if ( NULL == pItemCommon || !pItemCommon->IsCanEquip() )
    { return false; }

    ItemDefine::SItemCanEquip* pItemCanEquip = (ItemDefine::SItemCanEquip*)pItemCommon;

    // ????
    if ( pItemCanEquip->stHPMax != item.equipdata.usHpMax )
    { item.equipdata.usHpMax = pItemCanEquip->stHPMax; }

    if ( item.equipdata.usHP > item.equipdata.usHpMax )
    { item.equipdata.usHP = item.equipdata.usHpMax; }

    if ( !bJustSetItem )
    {
        switch( pItemCanEquip->ucItemType )
        {
        case ItemDefine::ITEMTYPE_WEAPON:
            {
                m_stDstAddStatus        [ part ] = -1;
                m_stDstAddStatusLvl     [ part ] = -1;
                m_fDstStatusRate        [ part ] = 0.0f;
                m_nDstAddStatusTrigger  [ part ] = 0;
                m_stMeAddStatus         [ part ] = -1;
                m_stMeAddStatusLvl      [ part ] = -1;
                m_fMeStatusRate         [ part ] = 0.0f;
                m_nMeAddStatusTrigger   [ part ] = 0;

                bRetOp = EquipWeapon( part, &item);

                if( bRetOp )
                {
                    ItemDefine::SItemWeapon* pItemWeapon = (ItemDefine::SItemWeapon*)pItemCanEquip;
                    m_stDstAddStatus        [ part ] = pItemWeapon->stAddStatus;
                    m_stDstAddStatusLvl     [ part ] = pItemWeapon->stAddStatusLevel;
                    m_fDstStatusRate        [ part ] = pItemWeapon->fStatusRate;
                    m_nDstAddStatusTrigger  [ part ] = pItemWeapon->nAddStatusTrigger;
                    m_stMeAddStatus         [ part ] = pItemWeapon->stMyAddStatus;
                    m_stMeAddStatusLvl      [ part ] = pItemWeapon->stMyAddStatusLevel;
                    m_fMeStatusRate         [ part ] = pItemWeapon->fMyStatusRate;
                    m_nMeAddStatusTrigger   [ part ] = pItemWeapon->nMyAddStatusTrigger;
                }
            }
            break;
        case ItemDefine::ITEMTYPE_ARMOUR:
            {
                m_stMeAddStatus         [ part ] = -1;
                m_stMeAddStatusLvl      [ part ] = -1;
                m_fMeStatusRate         [ part ] = 0.0f;
                m_nMeAddStatusTrigger   [ part ] = 0;
                m_stDstAddStatus        [ part ] = -1;
                m_stDstAddStatusLvl     [ part ] = -1;
                m_fDstStatusRate        [ part ] = 0.0f;
                m_nDstAddStatusTrigger  [ part ] = 0;

                bRetOp = EquipArmour( part, &item );

                if( bRetOp )
                {
                    ItemDefine::SItemArmour *pItemArmour = (ItemDefine::SItemArmour *)pItemCanEquip;

                    m_stMeAddStatus         [ part ] = pItemArmour->stMyAddStatus;
                    m_stMeAddStatusLvl      [ part ] = pItemArmour->stMyAddStatusLevel;
                    m_fMeStatusRate         [ part ] = pItemArmour->fMyStatusRate;
                    m_nMeAddStatusTrigger   [ part ] = pItemArmour->nMyAddStatusTrigger;
                    m_stDstAddStatus        [ part ] = pItemArmour->stAddStatus;
                    m_stDstAddStatusLvl     [ part ] = pItemArmour->stAddStatusLevel;
                    m_fDstStatusRate        [ part ] = pItemArmour->fStatusRate;
                    m_nDstAddStatusTrigger  [ part ] = pItemArmour->nAddStatusTrigger;
                }
            }
            break;
        default:
            return false;
        }
    }

    if ( bRetOp )
    {   
        if ( pItemCanEquip->bIsCanBound )
        { item.SetBounded( true ); } // ????????

        SetEquip( part, item );

        if ( pItemCanEquip->ucItemType == ItemDefine::ITEMTYPE_WEAPON )
        { UpdateNormalAttackSkillId(); }
    }

	//????7????
	_sevenDayManager.TriggerSevenDaysVar( (int)SevenDaysConfig::TD_SixthDay );
	_sevenDayManager.TriggerSevenDaysVar( (int)SevenDaysConfig::TD_SeventhDay );

	//????????????
	GetCharInfo().otherdata.equipTotalScore = 0;
	for( int i = 0; i < EEquipPartType_MaxEquitPart; i++ )
	{
		SCharItem* pSCharItem = GetVisualEquipItem(i);
		if ( !pSCharItem )
			continue;

		GetCharInfo().otherdata.equipTotalScore += pSCharItem->equipdata.fScore;
	}

    return bRetOp;
}

void GamePlayer::RemoveAllEquip()
{
    if ( !ProcessSecondPasswordOperate(PasswordDefine::EProtect_UnpackEquip, PasswordDefine::OP_InitAction) )
    { return;}  // ??????????????????????????

	if(CS_INTONATE == GetStatus())
	{
		//????????????????????
		SendChangeEquipErrorInfo();
		return;
	}

    //??????????????????
    for (int i=0; i<EEquipPartType_MaxEquitPart; ++i)
    {
        SCharItem* pCharItem = GetVisualEquipItem( i );
        if ( pCharItem == NULL)
        { continue; }

        pCharItem->SetItemID( InvalidLogicNumber );
        pCharItem->SetItemGuid( InvalidLogicNumber );
    }

    UpdateAllEquipData(); // ??????????????????????????????????????????
    UpdateAllSuitData() ; // ????????????
    RecalcBaseProperty( false, BV_NotFullHp, BV_SendMessage, EWRP_Equip );
}

void GamePlayer::RemoveEquipItemSkill ( uint8 stPart )
{
    if ( stPart >= EEquipPartType_MaxEquitPart)
    { return; }

	if(CS_INTONATE == GetStatus())
	{
		//????????????????????
		SendChangeEquipErrorInfo();
		return;
	}

    SCharItem* pCharItem = gCharInfoServer.visual.GetVisual(stPart);
    if ( NULL == pCharItem)
    { return; }

    ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( pCharItem->itembaseinfo.ustItemID );
    if ( NULL == pItemCommon || !pItemCommon->IsCanEquip() )
    { return; }

    ItemDefine::SItemCanEquip* pItemCanEquip = (ItemDefine::SItemCanEquip*)pItemCommon;

    if ( pItemCanEquip->skillId > 0 )
    { ForgetSkill( pItemCanEquip->skillId, false ); }
}

void GamePlayer::ApplyAttrTypeToChar(uint16 attrType , uint16 part , CustomValue value )
{
    switch ( attrType )
    {
    case RT_AddStrength:
        GetBaseAttr( EBaseAttr_Strength )->AddPartValue(part,value.fValue);
        GetAddSubBaseAttr( EBaseAttr_Strength )->AddPartValue(part,value.fValue);
        break;
    case RT_AddAgility:
        GetBaseAttr( EBaseAttr_Agility )->AddPartValue(part,value.fValue);
        GetAddSubBaseAttr( EBaseAttr_Agility )->AddPartValue(part,value.fValue);
        break;
    case RT_AddConstitution:
        GetBaseAttr( EBaseAttr_Stamina )->AddPartValue(part,value.fValue);
        GetAddSubBaseAttr( EBaseAttr_Stamina )->AddPartValue(part,value.fValue);
        break;
    case RT_AddIntelligence:
        GetBaseAttr( EBaseAttr_Intelligence )->AddPartValue(part,value.fValue);
        GetAddSubBaseAttr( EBaseAttr_Intelligence )->AddPartValue(part,value.fValue);
        break;        
    case RT_AddHPMax:
        GetCharFightAttr()->hpMax.AddPartValue(part,value.fValue);
        break;
    //case RT_AddAPMax:  //????
    //    if(GetProfession() == EArmType_Hunter)
    //    { GetCharFightAttr()->mpMax.AddPartValue(part,value.fValue); }
    //    break;
    //case RT_AddBPMax:  //????
    //    if(GetProfession() == EArmType_Sniper)
    //    {  GetCharFightAttr()->mpMax.AddPartValue(part,value.fValue);}
    //    break;
    //case RT_AddFPMax:  //????
    //    if(GetProfession() == EArmType_Warrior)
    //    { GetCharFightAttr()->mpMax.AddPartValue(part,value.fValue); }
    //    break;
    //case RT_AddEPMax:  //????
    //    if(GetProfession() == EArmType_Assassin)
    //    { GetCharFightAttr()->mpMax.AddPartValue(part,value.fValue); }
    //    break;
    case RT_AddMPMax:  //????
        GetCharFightAttr()->mpMax.AddPartValue(part,value.fValue);
        break;
    case RT_AddPhysicsAttack:            
        GetCharFightAttr()->attackPhysics.AddPartValue(part,value.fValue);
        break;
    //case RT_AddLongAttack:
    //    if(GetProfession() == EArmType_Hunter || GetProfession() == EArmType_Sniper)
    //    { GetCharFightAttr()->attackPhysics.AddPartValue(part,value.fValue); }
    //    break;
    case RT_AddMagicAttack:
        GetCharFightAttr()->attackMagic.AddPartValue(part,value.fValue);
        break;
    case RT_AddPhysicsDefend:
        GetCharFightAttr()->defendPhysics.AddPartValue(part,value.fValue);
        break;
    case RT_AddMagicDefend:
        GetCharFightAttr()->defendMagic.AddPartValue(part,value.fValue);
        break;
    //case RT_AddLongDefend:
    //    GetCharFightAttr()->defendPhysics.AddPartValue(part,value.fValue);
    //    break;
    case RT_AddExact:
        GetCharFightAttr()->exact.AddPartValue(part,value.fValue); 
        break;
    case RT_AddDodge:
        GetCharFightAttr()->dodge.AddPartValue(part,value.fValue);
        break;
    case RT_AddCritical:
        GetCharFightAttr()->critical.AddPartValue(part,value.fValue);
        break;
    case RT_AddTenacity:
        GetCharFightAttr()->tenacity.AddPartValue(part,value.fValue);
        break;
    case RT_AddCriticalIntensity:
        GetCharFightAttr()->criticalIntensity.AddPartValue(part,value.fValue);
        break;
        //??????????????????
    case RT_AddBaseAttr:
        for (int baseAttr = 0; baseAttr < EBaseAttr_MaxSize; ++baseAttr)
        { 
            GetBaseAttr( baseAttr )->AddPartValue(part,value.fValue); 
            GetAddSubBaseAttr( baseAttr )->AddPartValue(part,value.fValue);
        }
        break;
    case RT_AddEnergyMax:
        GetCharInfo().baseinfo.liveinfo.activityMax += value.fValue;
        break;
    case RT_AddExpPer:
        GetBuffManager()->SetExpMulAddByEquip(value.fValue);
        break;
    case RT_AddHPRestore:
        GetCharFightAttr()->hpRestore.AddPartValue(part,value.fValue);
        break;
    case RT_AddMoveSpeed:
        GetCharFightAttr()->moveSpeed.AddPartValue(part,value.fValue);
        break;
    //case RT_AddAPRestore:  //????
    //    if(GetProfession() == EArmType_Hunter)
    //    { GetCharFightAttr()->mpRestore.AddPartValue(part,value.fValue); }
    //    break;
    //case RT_AddBPRestore:  //????
    //    if(GetProfession() == EArmType_Sniper)
    //    {  GetCharFightAttr()->mpRestore.AddPartValue(part,value.fValue);}
    //    break;
    //case RT_AddFPRestore:  //????
    //    if(GetProfession() == EArmType_Warrior)
    //    { GetCharFightAttr()->mpRestore.AddPartValue(part,value.fValue); }
    //    break;
    //case RT_AddEPRestore:  //????
    //    if(GetProfession() == EArmType_Assassin)
    //    { GetCharFightAttr()->mpRestore.AddPartValue(part,value.fValue); }
    //    break;
    case RT_AddMPRestore:  //????
        GetCharFightAttr()->mpRestore.AddPartValue(part,value.fValue);
        break;
	case RT_AddBreakStrike:
		GetCharFightAttr()->breakStrike.AddPartValue(part,value.fValue);
		break;
	case RT_AddStabStrike:
		GetCharFightAttr()->stabStrike.AddPartValue(part,value.fValue);
		break;
	case RT_AddElementStrike:
		GetCharFightAttr()->elementStrike.AddPartValue(part,value.fValue);
		break;
	case RT_AddToxinStrike:
		GetCharFightAttr()->toxinStrike.AddPartValue(part,value.fValue);
		break;
	case RT_AddSpiritStrike:
		GetCharFightAttr()->spiritStrike.AddPartValue(part,value.fValue);
		break;
	case RT_AddBreakResist:
		GetCharFightAttr()->breakResist.AddPartValue(part,value.fValue);
		break;
	case RT_AddStabResist:
		GetCharFightAttr()->stabResist.AddPartValue(part,value.fValue);
		break;
	case RT_AddElementResist:
		GetCharFightAttr()->elementResist.AddPartValue(part,value.fValue);
		break;
	case RT_AddToxinResist:
		GetCharFightAttr()->toxinResist.AddPartValue(part,value.fValue);
		break;
	case RT_AddSpiritResist:
		GetCharFightAttr()->spiritResist.AddPartValue(part,value.fValue);
		break;
    }
}

void GamePlayer::ApplyEquipRandAttributesToChar( SCharItem* pItem, uint16 part )
{   
    if ( pItem == NULL )
    { return; }

    for (int nloop = 0; nloop <  SCharItem::EConstDefine_BaseRandMaxCount; ++nloop)
    {
        unsigned short usRandId = pItem->equipdata.baseRands[nloop];        
        if ( usRandId == InvalidLogicNumber )
        { continue; }

        ApplyRandAttributeToChar( usRandId, part, pItem->equipdata.quality );
    }

    for (int nloop = 0; nloop <  SCharItem::EConstDefine_PurpleRandMaxCount; ++nloop)
    {
        unsigned short usRandId = pItem->equipdata.purpleRands[nloop];        
        if ( usRandId == InvalidLogicNumber )
        { continue; }

        ApplyRandAttributeToChar( usRandId, part );
    }

    for (int nloop = 0; nloop <  SCharItem::EConstDefine_SuitRandMaxCount; ++nloop)
    {
        unsigned short usRandId = pItem->equipdata.suitRands[nloop];        
        if ( usRandId == InvalidLogicNumber )
        { continue; }

        ApplyRandAttributeToChar( usRandId, part );
    }
}

void GamePlayer::ApplyTalismanRandAttributesToChar( SCharItem* pItem, uint16 part )
{
    if ( pItem == NULL )
    { return; }

    for (int nloop = 0; nloop <  SCharItem::EConstDefine_BaseRandMaxCount; ++nloop)
    {
        unsigned short usRandId = pItem->equipdata.baseRands[nloop];        
        if ( usRandId == InvalidLogicNumber )
        { continue; }

        ApplyRandAttributeToChar( usRandId, part );
    }

    //for (int nloop = 0; nloop <  SCharItem::EConstDefine_TalismanRandMaxCount; ++nloop)
    //{

    //}
}

void GamePlayer::ApplyRandAttributeToChar( uint16 stRandID, uint16 part )
{
	if ( stRandID == InvalidLogicNumber )
	{ return; }

	ItemDefine::SRandAttribute* pItemEquipRand = GettheItemDetail().GetRandByID( stRandID );
	if ( pItemEquipRand == NULL )
	{ return; }

	for ( int i=0; i<ItemDefine::SRandAttribute::CD_TypeCount; ++i)
	{
		ApplyAttrTypeToChar( pItemEquipRand->type[i], part, pItemEquipRand->value[i] );
	}
}

void GamePlayer::ApplyRandAttributeToChar( uint16 stRandID, uint16 part, uint8 nQuality )
{
	if ( stRandID == InvalidLogicNumber )
	{ return; }

	ItemDefine::SRandAttribute* pItemEquipRand = GettheItemDetail().GetRandByID( stRandID );
	if ( pItemEquipRand == NULL )
	{ return; }

	for ( int i=0; i<ItemDefine::SRandAttribute::CD_TypeCount; ++i)
	{
		CustomValue value;
		value.fValue = GettheItemDetail().GetEquipRandAttrValue( pItemEquipRand->value[i].fValue, nQuality );
		ApplyAttrTypeToChar( pItemEquipRand->type[i], part, value );
	}
}

void GamePlayer::ApplyGemsToChar( SCharItem* pItem, uint16 part )
{
    if ( pItem->equipdata.gemHoleCount > SCharItem::EConstDefine_GemHoleMaxCount )
    { pItem->equipdata.gemHoleCount = SCharItem::EConstDefine_GemHoleMaxCount; }        

    for ( uint8 i=0; i<pItem->equipdata.gemHoleCount; ++i )
    {
        uint16 gemId = pItem->equipdata.gemIds[i];
        if ( gemId == InvalidLogicNumber )
        { continue; }

        ApplyGemAttributeToChar( gemId, part );
    }
}

void GamePlayer::ApplyGemAttributeToChar( unsigned short ustItemID, uint16 part )
{
    if ( ustItemID == InvalidLogicNumber )
    { return; }

    ItemDefine::SItemGem* pItemGem = (ItemDefine::SItemGem*) GettheItemDetail().GetItemByID( ustItemID );
    if ( pItemGem == NULL )
    { return; }

    for (int i=0;i< ItemDefine::SItemGem::CD_TypeCount; ++i)
    {
        ApplyAttrTypeToChar( pItemGem->type[i], part , pItemGem->value[i] );
    }      
}

void GamePlayer::ApplyStarActivationAttribute( SStarActivation::SEffect* pEffect )
{
    if ( pEffect == NULL )
    { return; }

    ApplyAttrTypeToChar( pEffect->type, ECustomDataPart_suit, pEffect->value );
}

void GamePlayer::ApplyStampActivationAttribute( SStampActivation::SEffect* pEffect )
{
    if ( pEffect == NULL )
    { return; }

    ApplyAttrTypeToChar( pEffect->type, ECustomDataPart_suit, pEffect->value );
}

bool GamePlayer::EquipWeapon( uint8 part, SCharItem* pCharItem)
{       
    if ( !pCharItem)
    { return false; }

	if(CS_INTONATE == GetStatus())
	{
		//????????????????????
		SendChangeEquipErrorInfo();
		return false;
	}

	ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID(pCharItem->itembaseinfo.ustItemID);
	if ( pItemCommon->ucItemType != ItemDefine::ITEMTYPE_WEAPON )
	{ return false; }

	ItemDefine::SItemWeapon* pItemWeapon = (ItemDefine::SItemWeapon*)pItemCommon;

	// ????????
	if (GetWeaponAttackRange() <= 0|| pItemWeapon->fAtkRange < GetWeaponAttackRange())
	{ SetWeaponAttackRange( pItemWeapon->fAtkRange); }

	if (pCharItem->equipdata.usHP <= 0 || pCharItem->IsOverdue())
	{
		return false;
	}    

    int iLevel = GetLevel();

	bool bSoul = pCharItem->IsSoulStamp();
	float fSoulPer = 0.0f;
	if ( bSoul )
		fSoulPer = pCharItem->equipdata.ucSoulPer / 100.0f;

    //unsigned char usArmsType = GetProfession();
    //SArmsParamModulusCommon& rArmsParamModulusCommon = DataCenter::GetInstance().GetArmsParamModulusCommon();

    //SArmsParamModulusExtend* pArmsParamModulusExtend = DataCenter::GetInstance().GetArmsParamModulus(usArmsType);
    //if ( !pArmsParamModulusExtend )
    //    return false;

    unsigned char ucLevel = pCharItem->equipdata.ucLevel;
    // float fAttributeMod = (ucLevel == 0 ? 1.0f : 1.f + 0.025f * (ucLevel * 2 + 1 ) / 0.475f );
    float fAttributeMod     = theStarLevelUpConfig.GetItemStarLevelModulus( pItemWeapon->ustEquipType, ucLevel );
    //float fStampAdditionPer = pCharItem->GetSoulStampAddition() * DEF_PERCENT;
    //float fStampAttack      = pItemWeapon->attack * fStampAdditionPer;

    if( part == EEquipPartType_Weapon )
    { // ????????
        GetCharFightAttr()->attackSpeed.item   += pItemWeapon->attackSpeed;
        GetCharFightAttr()->attackPhysics.item += pItemWeapon->attackPhysics * (fAttributeMod + fSoulPer);
        GetCharFightAttr()->attackMagic.item   += pItemWeapon->attackMagic * (fAttributeMod + fSoulPer)  ;

        GetCharFightAttr()->exact.item   += pItemWeapon->exact * (fAttributeMod + fSoulPer) + 0.5f;
        GetCharFightAttr()->dodge.item   += pItemWeapon->dodge * (fAttributeMod + fSoulPer) + 0.5f;
        GetCharFightAttr()->critical.item   += pItemWeapon->critical * (fAttributeMod + fSoulPer) + 0.5f;
        GetCharFightAttr()->tenacity.item   += pItemWeapon->tenacity * (fAttributeMod + fSoulPer) + 0.5f;
		//????????
		GetCharFightAttr()->breakStrike.item		+= pItemWeapon->breakStrike * (fAttributeMod + fSoulPer) + 0.5f;
		GetCharFightAttr()->breakResist.item		+= pItemWeapon->breakResist * (fAttributeMod + fSoulPer) + 0.5f;
		GetCharFightAttr()->stabStrike.item			+= pItemWeapon->stabStrike * (fAttributeMod + fSoulPer) + 0.5f;
		GetCharFightAttr()->stabResist.item			+= pItemWeapon->stabResist * (fAttributeMod + fSoulPer) + 0.5f;
		GetCharFightAttr()->elementStrike.item		+= pItemWeapon->elementStrike * (fAttributeMod + fSoulPer) + 0.5f;
		GetCharFightAttr()->elementResist.item		+= pItemWeapon->elementResist * (fAttributeMod + fSoulPer) + 0.5f;
		GetCharFightAttr()->toxinStrike.item		+= pItemWeapon->toxinStrike * (fAttributeMod + fSoulPer) + 0.5f;
		GetCharFightAttr()->toxinResist.item		+= pItemWeapon->toxinResist * (fAttributeMod + fSoulPer) + 0.5f;
		GetCharFightAttr()->spiritStrike.item		+= pItemWeapon->spiritStrike * (fAttributeMod + fSoulPer) + 0.5f;
		GetCharFightAttr()->spiritResist.item		+= pItemWeapon->spiritResist * (fAttributeMod + fSoulPer) + 0.5f;
    }

    // ????????????
    ApplyEquipRandAttributesToChar( pCharItem , ECustomDataPart_item );
    ApplyGemsToChar          ( pCharItem , ECustomDataPart_item );

    if ( pItemWeapon->skillId > 0 )
    { LearnSkill( pItemWeapon->skillId, pItemWeapon->skillLevel, false, true, false );}

    return true;
}

bool GamePlayer::EquipArmour( uint8 stWhere, SCharItem* pCharItem )
{
    if ( !pCharItem || pCharItem->itembaseinfo.ustItemID == InvalidLogicNumber )
    { return false; }

	if(CS_INTONATE == GetStatus())
	{
		//????????????????????
		SendChangeEquipErrorInfo();
		return false;
	}

    if (pCharItem->equipdata.usHP <= 0 || pCharItem->IsOverdue() )
    { return false; }

    ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID(pCharItem->itembaseinfo.ustItemID);
    if ( pItemCommon->ucItemType != ItemDefine::ITEMTYPE_ARMOUR )
    { return false; }

    ItemDefine::SItemArmour* pItemArmour = (ItemDefine::SItemArmour*)pItemCommon;

    unsigned char ucLevel = pCharItem->equipdata.ucLevel;
    //float fAttributeMod = (ucLevel == 0 ? 1.0f : 1.f + 0.025f * (ucLevel * 2 + 1 ) / 0.475f );

    float fAttributeMod     = theStarLevelUpConfig.GetItemStarLevelModulus( pItemArmour->ustEquipType, ucLevel );
    //float fStampAdditionPer = pCharItem->GetSoulStampAddition() * DEF_PERCENT;

    //float fStampAttack          = pItemArmour->attack * fStampAdditionPer;
    //float fStampDefendShort     = pItemArmour->defendShort * fStampAdditionPer;
    //float fStampDefendLong      = pItemArmour->defendLong  * fStampAdditionPer;
    //float fStampDefendMagic     = pItemArmour->defendMagic * fStampAdditionPer;

	bool bSoul = pCharItem->IsSoulStamp();
	float fSoulPer = 0.0f;
	if ( bSoul )
		fSoulPer = pCharItem->equipdata.ucSoulPer / 100.0f;

    GetCharFightAttr()->attackPhysics.item += pItemArmour->attackPhysics * (fAttributeMod + fSoulPer) ;
    GetCharFightAttr()->attackMagic.item   += pItemArmour->attackMagic * (fAttributeMod + fSoulPer) ;
    GetCharFightAttr()->defendPhysics.item += pItemArmour->defendPhysics * (fAttributeMod + fSoulPer) ;
    //GetCharFightAttr()->defendLong.item  += pItemArmour->defendLong  * fAttributeMod + fStampDefendLong ;
    GetCharFightAttr()->defendMagic.item   += pItemArmour->defendMagic * (fAttributeMod + fSoulPer)   ;
    GetCharFightAttr()->attackSpeed.item   += pItemArmour->attackSpeed * (fAttributeMod + fSoulPer);
	//HP??MP
	GetCharFightAttr()->hpMax.item		   += pItemArmour->Hp * (fAttributeMod + fSoulPer);
	GetCharFightAttr()->mpMax.item		   += pItemArmour->Mp * (fAttributeMod + fSoulPer);

    GetCharFightAttr()->exact.item         += pItemArmour->exact * (fAttributeMod + fSoulPer) + 0.5f;
    GetCharFightAttr()->dodge.item         += pItemArmour->dodge * (fAttributeMod + fSoulPer) + 0.5f;
    GetCharFightAttr()->critical.item      += pItemArmour->critical * (fAttributeMod + fSoulPer) + 0.5f;
    GetCharFightAttr()->tenacity.item      += pItemArmour->tenacity * (fAttributeMod + fSoulPer) + 0.5f;
	//????????
	GetCharFightAttr()->breakStrike.item		+= pItemArmour->breakStrike * (fAttributeMod + fSoulPer) + 0.5f;
	GetCharFightAttr()->breakResist.item		+= pItemArmour->breakResist * (fAttributeMod + fSoulPer) + 0.5f;
	GetCharFightAttr()->stabStrike.item			+= pItemArmour->stabStrike * (fAttributeMod + fSoulPer) + 0.5f;
	GetCharFightAttr()->stabResist.item			+= pItemArmour->stabResist * (fAttributeMod + fSoulPer) + 0.5f;
	GetCharFightAttr()->elementStrike.item      += pItemArmour->elementStrike * (fAttributeMod + fSoulPer) + 0.5f;
	GetCharFightAttr()->elementResist.item      += pItemArmour->elementResist * (fAttributeMod + fSoulPer) + 0.5f;
	GetCharFightAttr()->toxinStrike.item		+= pItemArmour->toxinStrike * (fAttributeMod + fSoulPer) + 0.5f;
	GetCharFightAttr()->toxinResist.item		+= pItemArmour->toxinResist * (fAttributeMod + fSoulPer) + 0.5f;
	GetCharFightAttr()->spiritStrike.item		+= pItemArmour->spiritStrike * (fAttributeMod + fSoulPer) + 0.5f;
	GetCharFightAttr()->spiritResist.item		+= pItemArmour->spiritResist * (fAttributeMod + fSoulPer) + 0.5f;

    ApplyEquipRandAttributesToChar( pCharItem, ECustomDataPart_item );
    ApplyGemsToChar          ( pCharItem, ECustomDataPart_item );

    if ( pItemArmour->skillId > 0 )
    { LearnSkill( pItemArmour->skillId, pItemArmour->skillLevel, false, true, false );}

    return true;
}

int GamePlayer::GetWeaponAttack( int nType )
{
    SCharItem* pWeapon = GetVisualEquipItem( EEquipPartType_Weapon );
    if ( pWeapon == NULL )
    { return 0; }

    ItemDefine::SItemWeapon* pWeaponItem = (ItemDefine::SItemWeapon*) GettheItemDetail().GetItemByID( pWeapon->itembaseinfo.ustItemID );
    if ( pWeaponItem == NULL || !pWeaponItem->IsCanEquip() )
    { return 0; }

    if ( nType == CharAttr_AttackPhysics )
    { return pWeaponItem->attackPhysics;    }
    else
    { return pWeaponItem->attackMagic;      }

    return 0;
}

int GamePlayer::GetArmourDefend( int nType )
{
    int nArmourDefend = 0;
    for( int nPartLoop = 0; nPartLoop < EEquipPartType_MaxEquitPart; ++nPartLoop )
    {
        if ( nPartLoop == EEquipPartType_Weapon )
        { continue; }

        SCharItem* pArmour = GetVisualEquipItem( nPartLoop );
        if ( pArmour == NULL )
        { continue; }

        ItemDefine::SItemArmour* pArmourItem = (ItemDefine::SItemArmour*) GettheItemDetail().GetItemByID( pArmour->itembaseinfo.ustItemID );
        if ( pArmourItem == NULL || !pArmourItem->IsCanEquip() )
        { continue; }

        if ( nType == CharAttr_DefendPhysics )
        { nArmourDefend += pArmourItem->defendPhysics;  }
        else
        { nArmourDefend += pArmourItem->defendMagic;    }
    }

    return nArmourDefend;
}


bool GamePlayer::RecalcBaseProperty( bool bInitBase, uint8 ucFullHpMp, uint8 ucSendMsg, uint8 ucWherefore )
{
    if ( bInitBase )
    {
        SLevelAttribute* pLevelAttribute = theCharacterAttributeConfig.GetCharacterAttribute( GetProfession(), GetLevel() );
        if ( NULL == pLevelAttribute )
        {
            LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_ERROR, "RecalculateFightData->GetLevelSecondAttributeCorrect(%d,%d) Fail", GetProfession(), GetLevel());
            return false;
        }

        SetCharAllBaseAttributeBase( pLevelAttribute->baseAttribute, EBaseAttr_MaxSize );

        for( int i=0; i<EBaseAttr_MaxSize; ++i)
        { GetBaseAttr(i)->assign = gCharInfoServer.baseinfo.liveinfo.baseAssignValue[i]; }

        SArmsParamModulusCommon& gArmsParamModulusCommon = theDataCenter.GetArmsParamModulusCommon();
        SArmsParamModulusExtend* pArmsParamModulusExtend = theDataCenter.GetArmsParamModulus(GetProfession());
        if ( NULL == pArmsParamModulusExtend )
        {
            LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_ERROR, "RecalculateFightData->GetArmsParamModulus(%d) Fail", GetProfession());
            return false;
        }

        ClearAllFightAttrByPart ( ECustomDataPart_base )        ;

        ApplyBaseAttrToFightAttr( true, ECustomDataPart_base )  ;

        ClearAllFightAttrByPart ( ECustomDataPart_assign )      ;

        ApplyBaseAttrToFightAttr( true, ECustomDataPart_assign );

        // ????????
        GetCharFightAttr()->hpMax        .base     += pLevelAttribute->secondAttributeFix[ ESecondAttrFixType_hpMax       ];
        GetCharFightAttr()->mpMax        .base     += pLevelAttribute->secondAttributeFix[ ESecondAttrFixType_mpMax       ];
        GetCharFightAttr()->attackPhysics.base     += pLevelAttribute->secondAttributeFix[ ESecondAttrFixType_phyAttack   ];
        GetCharFightAttr()->attackMagic  .base     += pLevelAttribute->secondAttributeFix[ ESecondAttrFixType_magicAttack ];
        GetCharFightAttr()->defendPhysics.base     += pLevelAttribute->secondAttributeFix[ ESecondAttrFixType_phyDefend   ];
        GetCharFightAttr()->defendMagic  .base     += pLevelAttribute->secondAttributeFix[ ESecondAttrFixType_magicDefend ];
        GetCharFightAttr()->exact        .base     += pLevelAttribute->secondAttributeFix[ ESecondAttrFixType_exact       ];
        GetCharFightAttr()->dodge        .base     += pLevelAttribute->secondAttributeFix[ ESecondAttrFixType_dodge       ];
        GetCharFightAttr()->critical     .base     += pLevelAttribute->secondAttributeFix[ ESecondAttrFixType_critical    ];
        GetCharFightAttr()->tenacity     .base     += pLevelAttribute->secondAttributeFix[ ESecondAttrFixType_tenacityl   ];
        GetCharFightAttr()->hpRestore    .base     += pLevelAttribute->secondAttributeFix[ESecondAttrFixType_hpRestore    ];
        GetCharFightAttr()->mpRestore    .base     += pLevelAttribute->secondAttributeFix[ESecondAttrFixType_mpRestore    ];
        GetCharFightAttr()->attackSpeed  .base     += gArmsParamModulusCommon.GetNormalAttackSpeed();
        GetCharFightAttr()->moveSpeed    .base     += gArmsParamModulusCommon.GetMoveSpeed();  
        GetCharFightAttr()->backStrike   .base     += gArmsParamModulusCommon.GetBackStrikeModulus() ; 
        GetCharFightAttr()->criticalIntensity.base += gArmsParamModulusCommon.GetCriticalIntensityModulus() ;
    }

    if ( ucWherefore == EWRP_Status )
    { m_bIsStatusChangeHpMpMax = true;   }
    else
    { m_bIsStatusChangeHpMpMax = false;  }

    // ????????????
    UpdateCharAllAttibute();

    // ????????????????????
    if( ucSendMsg == BV_SendMessage)
    { SendCharAttibuteToClient(); }

    // ????????HP MP
    RecalcHpMp( ucFullHpMp, ucSendMsg );

    return true;
}

bool GamePlayer::RecalcHpMp( uint8 ucFullHpMp, uint8 ucSendMsg )
{
    if ( ucFullHpMp == BV_FullHp )
    {
        SetHP( GetCharFightAttr()->hpMax.final );
        SetMP( GetCharFightAttr()->mpMax.final );
    }
    else
    { // ??????????
        if( GetHP() > GetCharFightAttr()->hpMax.final )
        { SetHP( GetCharFightAttr()->hpMax.final ); }

        if( GetMP()> GetCharFightAttr()->mpMax.final )
        { SetMP( GetCharFightAttr()->mpMax.final ); }
    }

    if( ucSendMsg == BV_NotSendMessage)
    { return false; }

    //MsgCharAttrChanged Change;
    //Change.iChangeCount = 0;

    MsgCharAttrChanged msgSeeAttrChange;
    msgSeeAttrChange.iChangeCount = 0;
    msgSeeAttrChange.AddAttrIntChange( CharAttr_HPMax, GetCharFightAttr()->hpMax.final );
    msgSeeAttrChange.AddAttrIntChange( CharAttr_MPMax, GetCharFightAttr()->mpMax.final );

    //Change.AddAttrIntChange(CharAttr_HP, GetHP() );
    //Change.AddAttrIntChange(CharAttr_MP, GetMP() );

    msgSeeAttrChange.AddAttrIntChange( CharAttr_HP, GetHP() );
    msgSeeAttrChange.AddAttrIntChange( CharAttr_MP, GetMP() );

    //if( Change.iChangeCount > 0 )
    //{    
    //    Change.header.stID = GetID();
    //    Change.CaluLength();
    //    GettheServer().SendMsgToSingle( &Change, this );
    //}

    if( msgSeeAttrChange.iChangeCount > 0 )
    {
        msgSeeAttrChange.header.stID = GetID();
        msgSeeAttrChange.CaluLength();
        GettheServer().SendMsgToView( &msgSeeAttrChange, GetID() );
    }

    return true;
}

//??????????????
void GamePlayer::OnSitDownRestore()                
{ // ToCheck
    ////param1
    //short stBaseHPRestoreRate;
    //short stBaseMPRestoreRate;
    ////short stBaseTPRestoreRate;
    //stBaseHPRestoreRate = GetBaseHPRestoreRate();
    //stBaseMPRestoreRate = GetBaseMPRestoreRate();
    ////stBaseTPRestoreRate = GetBaseTPRestoreRate();

    ////param2
    //float iStr, iCon, iWis;
    //iStr = GetCharBaseAttr(EBaseAttr_Strength)->final;
    //iCon = GetCharBaseAttr(EBaseAttr_Constitution)->final;
    //iWis = GetCharBaseAttr(EBaseAttr_Intelligence)->final;

    ////param3
    //float fHPRestoreAffect;
    //float fMPRestoreAffect;
    ////float fTPRestoreAffect;
    //fHPRestoreAffect = GetHPRestoreAffect();
    //fMPRestoreAffect = GetMPRestoreAffect();
    ////fTPRestoreAffect = GetTPRestoreAffect();

    ////calc
    //int iHPRestore, iMPRestore;
    //iHPRestore = stBaseHPRestoreRate*(1+iCon/g_CfgParam.iHPRestoreParam1)*fHPRestoreAffect;
    //iMPRestore = stBaseMPRestoreRate*(1+iWis/g_CfgParam.iMPRestoreParam1)*fMPRestoreAffect;

    ////Set targetData
    //
    ////SetTPRestoreBaseRate( iTPRestore );

    //UpdateTPRestoreRateFinal();
}

//??????????????
void GamePlayer::OnStandUpRestore()
{       
    ////param1
    //short stBaseHPRestoreRate;
    //short stBaseMPRestoreRate;
    ////short stBaseTPRestoreRate;
    //stBaseHPRestoreRate = GetBaseHPRestoreRate();
    //stBaseMPRestoreRate = GetBaseMPRestoreRate();
    ////stBaseTPRestoreRate = GetBaseTPRestoreRate();

    ////param2
    //float iStr, iCon, iWis;
    //iStr = GetCharBaseAttr(EBaseAttr_Strength)->final;
    //iCon = GetCharBaseAttr(EBaseAttr_Constitution)->final;
    //iWis = GetCharBaseAttr(EBaseAttr_Intelligence)->final;

    ////param3
    //float fHPRestoreAffect;
    //float fMPRestoreAffect;
    ////float fTPRestoreAffect;
    //fHPRestoreAffect = GetHPRestoreAffect();
    //fMPRestoreAffect = GetMPRestoreAffect();
    ////fTPRestoreAffect = GetTPRestoreAffect();

    ////calc
    //int iHPRestore, iMPRestore;
    //iHPRestore = stBaseHPRestoreRate*(1+iCon/g_CfgParam.iHPRestoreParam1)*fHPRestoreAffect/2;
    //iMPRestore = stBaseMPRestoreRate*(1+iWis/g_CfgParam.iMPRestoreParam1)*fMPRestoreAffect/2;
    ////iTPRestore = stBaseTPRestoreRate*(1+iStr/g_CfgParam.iTPRestoreParam1)*fTPRestoreAffect/2;

    ////Set targetData
    //
    //SET_VALUE( hpRestore, base, iHPRestore );
    //SET_VALUE( energyRestore, base, iMPRestore );

    ////SetTPRestoreBaseRate( iTPRestore );
    //UPDATE_VALUE( hpRestore );
    //UPDATE_VALUE( energyRestore );
    //UpdateTPRestoreRateFinal();
}

void GamePlayer::ChangeLevel(int nNewLevel)
{    
    if ( nNewLevel == 0 )
    { return; }

    if ( nNewLevel>g_Cfg.m_nLevelLimt )
    { nNewLevel = g_Cfg.m_nLevelLimt; }

	//if ( nNewLevel>theLevelLimitGameManager.GetLimitLevel() && theLevelLimitGameManager.GetLimitLevel() > 0)
	//{ nNewLevel = theLevelLimitGameManager.GetLimitLevel(); }

    int iOldLevel = GetLevel();
    __int64 nAmountExp = 0;     //??????????????????????

    for ( int i = iOldLevel; i < nNewLevel; ++i )
    {
        nAmountExp += theExpStage.GetExpDistance(i);
    }

    if (nAmountExp > GetPlayerExpUnUsed())
    {
        MsgAckResult msg;
        msg.result = ER_NoExpToLevelUp;
        GettheServer().SendMsgToSingle( &msg, this );
        return;
    }

    SetLevel(nNewLevel);
    SetPlayerExpUnUsed( GetPlayerExpUnUsed() - nAmountExp );
    SetPlayerExp(GetPlayerExp() + nAmountExp);

	//????????30????????????????????????????????
	int nLevel = theGuildConfig.GetJoinSetting().GetLevel();
	if ( ( iOldLevel < nLevel ) && ( nNewLevel >= nLevel ) )
	{
		GameGuild* pGuild = theGameGuildManager.GetGuildByPlayerID( GetDBCharacterID() );
		if ( !pGuild )
		{
			// ????CenterServer????
			GS2CSPlayerLvUpToThirtyMessage xReq;
			xReq.nPlayerID	= GetDBCharacterID();
			xReq.nPlayerLv  = this->GetLevel();
			HelperFunc::SafeNCpy( xReq.szSpeakName, GetCharName(), sizeof( xReq.szSpeakName ) );
			GettheServer().SendMsgToCenterServer( &xReq );
		}
	}

	// ????????10??????????????????????????????????
	nLevel = theFamilyConfig.GetJoinSetting().GetLevelLimit();
	if ( ( iOldLevel < nLevel ) && ( nNewLevel >= nLevel ) )
	{
		GameFamily* pFamily = theGameFamilyManager.GetFamilyByPlayerID( GetDBCharacterID() );
		if ( !pFamily )
		{
			// ????CenterServer????
			GS2CSFamilyPlayerLvUpToTenMessage xReq;
			xReq.nPlayerID	= GetDBCharacterID();
			xReq.nPlayerLv  = this->GetLevel();
			HelperFunc::SafeNCpy( xReq.szSpeakName, GetCharName(), sizeof( xReq.szSpeakName ) );
			GettheServer().SendMsgToCenterServer( &xReq );
		}

	}
	//luo.qin 4.20 end

    MsgSeeCharacterLevelup msgSeeCharLevelup;
    msgSeeCharLevelup.header.stID = GetID();
    msgSeeCharLevelup.nNewLevel = GetLevel();
    msgSeeCharLevelup.nUnUsedExp   = GetPlayerExpUnUsed();
    GettheServer().SendMsgToView( &msgSeeCharLevelup, GetID(), false );

    int iLevelInterval = nNewLevel - iOldLevel;

    //??????????
    SArmsParamModulusCommon& gArmsParamModulusCommon = theDataCenter.GetArmsParamModulusCommon();
    for (int i = iOldLevel ; i < nNewLevel; ++i)
    {
        int nPotential = gArmsParamModulusCommon.GetPotentialByLevel(i);
        gCharInfoServer.baseinfo.liveinfo.basePotential += nPotential;
        ChangeAttr( CharAttr_BasePotential, gCharInfoServer.baseinfo.liveinfo.basePotential, true );
        //Log("ChangeLevel() level[%d] get potential [%d] ", i, nPotential);
		Log(theXmlString.GetString(eServerLog_GetPoint), i, nPotential);
    }

    RecalcBaseProperty( true, BV_FullHp, BV_SendMessage, EWRP_Level  );

    // XP????????
    SetXP( DEF_CHAR_XP_LIMIT );
    ChangeAttr( CharAttr_XPValue, GetXP() );

    // ????????????
    gCharInfoServer.baseinfo.liveinfo.activityMax = ProcessCharInfo::ActivityMax( GetLevel() );
    ChangeAttr( CharAttr_EnergyMax, gCharInfoServer.baseinfo.liveinfo.activityMax, true );

    // ????????????
    gCharInfoServer.baseinfo.liveinfo.vigorMax = ProcessCharInfo::VigorMax( GetLevel() );
    ChangeAttr( CharAttr_VigorMax, gCharInfoServer.baseinfo.liveinfo.vigorMax, true );

    // ????????????
    GetScriptMgr()->StartupVM( ST_LEVELUP, nNewLevel, this );
    UpdateCommonData( BV_NotForSaveDb );

    // ??????, ????????????, ??????????????
    if ( m_pRelation != NULL )  // ???????????????? ?????????????????????????????????????????? ??????????????????
    { m_pRelation->ProcessStudentLevelUp( GetDBCharacterID(), GetLevel() ); }

    if ( m_pGuild != NULL )     // ??????????
    { m_pGuild->SendMemberDataChangeReqMessage( GetDBCharacterID(), GuildDefine::UpdateMemberLevel, GuildDefine::OperateSet, GetLevel() ); }

	if ( m_pFamily != NULL )	// ??????????
	{ m_pFamily->SendMemberDataChangeReqMessage( GetDBCharacterID(), FamilyDefine::UpdateMemberLevel, FamilyDefine::OperateSet, GetLevel() ); }

    _achieveManager.UpdateTriggerByValueType( EAT_Level , GetLevel() );

	CalcCanTakeExp();
	CheckToSendAddLimitPlayerCount();
}

void GamePlayer::ChangeExp( int64 exp )
{
    exp = exp - 1;
    int nNewLevel = theExpStage.GetLevel( exp ); 

    if ( this->GetLevel() < nNewLevel )
    {
        SetPlayerExpUnUsed( exp - theExpStage.GetLevelupExp( this->GetLevel() - 1 ) );
    }
    else
    {
        SetPlayerExp(theExpStage.GetLevelupExp( nNewLevel - 1 ));
        SetPlayerExpUnUsed( 1 );
    }

    if ( nNewLevel != GetLevel() )
    { 
        //LYH????????
		theLogEventService.LogLevelChange(GetAccountID(),GetDBCharacterID(),GetLevel(),nNewLevel,GetCharName());
		ChangeLevel( nNewLevel ); 

		
		
	}
}

void GamePlayer::GetOfflineHookExp(uint8 nHookLevel)
{
    //if (nHookLevel >= EHookLevel_MaxSize)
    //{
    //    MsgAckResult msg;
    //    msg.result = ER_HookLevelNotHas;
    //    GettheServer().SendMsgToSingle( &msg, this );
    //    return;
    //}

    if ( GetLevel() < CHAR_OFFLINE_HOOK_LEVEL )
    {
        MsgAckResult msg;
        msg.result = ER_OfflineHookLevel;
        GettheServer().SendMsgToSingle( &msg, this );
        return;
    }

    if (gCharInfoServer.extendData.totalHookTime == 0 )
    {
        MsgAckResult msg;
        msg.result = ER_NoOfflineHookExp;
        GettheServer().SendMsgToSingle( &msg, this );
        return;
    }

    int minute = (int) ceil( (double)gCharInfoServer.extendData.totalHookTime  * ONE_SEC / ONE_MIN ) ;
    int money  = minute * g_Cfg.minuteOfflineHookMoney;

    if ( money > GetJiaoZiMoney() )
    {
        MsgAckResult msg;
        msg.result = ER_NoMoneyGetHookExp;
        GettheServer().SendMsgToSingle( &msg, this );
        return;
    }

    int minuteExp = GetOfflineHookMinuteExp( nHookLevel );
    int nTotalExp = minute * minuteExp;

    IncreaseExp( nTotalExp, 0 );
    OperateJiaoZi( EOT_Sub , money, true, __FUNCTION__, __LINE__,ePlayerMoneySourceType_OfflineHookExp );

    gCharInfoServer.extendData.totalHookTime = 0;
}

int32 GamePlayer::GetOfflineHookMinuteExp( uint8 hookLevel )
{
    if ( GetLevel() >= 40 && GetLevel() < 59 )
    { return  GetLevel() * 75; }

    if (GetLevel() >= 60 && GetLevel() < 69 )
    { return  GetLevel() * 105; }

    if (GetLevel() >= 70 )
    { return  GetLevel() * 135; }

    return 0;
}

// ????????????
GameFamily* GamePlayer::GetFamily()
{
	return m_pFamily;
}

short GamePlayer::IsInBattle(MapConfig::MapData* pMapData)
{
	if ( pMapData == NULL )
	{ return Battle_Non; }
	TeamBattleData* pBattleData = theTeamBattleManager.GetBattleDateByMapID( pMapData->Id );
	if ( pBattleData)
	{
		return Battle_Team;
	}
	CampBattle* pCampBattle = theCampBattleControl.GetCampBattle( GetFightCamp(), GetMapID() ,GetCountryId());
	if ( pCampBattle)
	{
		return Battle_Camp;
	}

	GameGuildGeneralBattleManager* pManager = static_cast<GameGuildGeneralBattleManager*>(theGameBattleControl.GetGameBattleManager(GameBattleDefine::GameBattle_Type_GuildGeneral));
	if(pManager)
	{
		GameGuildGeneralBattle* pBattle = pManager->GetGameBattleByPlayerID(GetDBCharacterID());
		if(pBattle)
		{
			if(GetMapID() == pBattle->GetBattleMapID())
				return Battle_Camp;
		}
	}
	return Battle_Non;
}

MapConfig::RelivePosition* GamePlayer::GetRelivePosition( MapConfig::MapData* pMapData )
{
    if ( pMapData == NULL )
    { return NULL; }

    // ????????
    TeamBattleData* pBattleData = theTeamBattleManager.GetBattleDateByMapID( pMapData->Id );
    if ( pBattleData != NULL )
    {
        BattleDefine::BattleRecord* pRecord = pBattleData->GetBattleRecord( GetTeamID(), GetMapID() );
        if ( pRecord != NULL )
        {
            return pMapData->GetRelivePositionByIndex( pRecord->GetReliveIndex() );
        }

        return pMapData->GetRelivePositionByIndex( 0 );      // ??????????????
    }

    // ??????????????????????
    CampBattle* pCampBattle = theCampBattleControl.GetCampBattle( GetFightCamp(), GetMapID() ,GetCountryId());
    if ( pCampBattle != NULL )
    {
        return pMapData->GetRelivePositionByIndex( pCampBattle->GetReliveIndex( this ) );//zhuxincong ??????????5???? ??????
    }

	GameGuildGeneralBattleManager* pManager = static_cast<GameGuildGeneralBattleManager*>(theGameBattleControl.GetGameBattleManager(GameBattleDefine::GameBattle_Type_GuildGeneral));
	if(pManager)
	{
		GameGuildGeneralBattle* pBattle = pManager->GetGameBattleByPlayerID(GetDBCharacterID());
		if(pBattle)
		{
			 return pMapData->GetRelivePositionByIndex(pBattle->GetReliveIndex( this ));
		}
	}

    return pMapData->GetRelivePositionByState( true );
}

const MapConfig::SpecRelivePosition* GamePlayer::GetSpecRelivePosition( MapConfig::MapData* pMapData )
{
	if ( pMapData == NULL )
	{ return NULL; }
	const MapConfig::SpecRelivePosition* pSpecRelivePosition = pMapData->GetSpecRelivePositionByCountry(GetCountry());
	return pSpecRelivePosition;
}

bool GamePlayer::IsCanFreeRelive()
{
   bool b = false;

   
   const CountryConfig::ReliveSetting& xReliveSetting = theCountryConfig.GetReliveSetting();

   uint8 nFreeReliveLimit =xReliveSetting.GetReilvelSum(GetLevel());

   //uint8 nFreeReliveLimit = xReliveSetting.GetFreeReliveLimitByLevel( GetLevel() );

   if( GetReliveCount() < nFreeReliveLimit )
   { 
         //b = true;
	   return true;
   }
    //++gCharInfoServer.baseinfo.liveinfo.nFreeReliveCount; //????????++
	return false;
   //return b;



   //lyh?????????????? ???????????????????????????????? ??????????????????????????????

   /* const CountryConfig::ReliveSetting& xReliveSetting = theCountryConfig.GetReliveSetting();

    uint8 nFreeReliveLimit = xReliveSetting.GetFreeReliveLimitByLevel( GetLevel() );

   if( GetFreeReliveCount() < nFreeReliveLimit )
   { 

       ++gCharInfoServer.baseinfo.liveinfo.nFreeReliveCount;
       return true; 
   }

    return false;*/
}

void GamePlayer::ProcessReliveBySkill( SReliveInfo& xReliveInfo )
{
    uint8 uchReliveType = eReliveTypeSkill;

    CampBattle* pCampBattle = theCampBattleControl.GetCampBattle( GetFightCamp(), GetMapID(),GetCountryId() );
    if ( pCampBattle != NULL && pCampBattle->GetBattleManager()->IsCountryBattle() )
    { 
        // ??????????????????????( ???????????? )
        uchReliveType = eReliveTypeNearPos;
    }

    ProcessRelive( uchReliveType, xReliveInfo );
}

/*
????: 
?????????????? RelivePosition Id="0" ???????????????????? ??????????????
?????????????? RelivePosition Id="1" ???????????????????????????? ????????????????????!!!
*/
void GamePlayer::ProcessRelive( uint8 uchReliveType, SReliveInfo& xReliveInfo )
{
    if( !IsDead() )
    { return; }

    MapConfig::MapData* pMapData = GetMapData();
    if( pMapData == NULL )
    { return; }

    switch( uchReliveType ) 
    {
    case eReliveTypeBorn:   // ??????????
        {
            MapConfig::RelivePosition* pRelivePosition = GetRelivePosition( pMapData );
            if ( pRelivePosition == NULL )
            { return; }

			//lyh++ ???????????????????????? ??????
			/*const CountryConfig::ReliveSetting& xReliveSetting = theCountryConfig.GetReliveSetting();
			uint8 nFreeReliveLimit = xReliveSetting.GetFreeReliveLimitByLevel( GetLevel() );
			if (GetFreeReliveCount() >= nFreeReliveLimit)
				gCharInfoServer.baseinfo.liveinfo.nFreeReliveCount = nFreeReliveLimit ;*/
			const CountryConfig::ReliveSetting& xReliveSetting = theCountryConfig.GetReliveSetting();
			uint8 nFreeReliveLimit =xReliveSetting.GetReilvelSum(GetLevel());
			if(gCharInfoServer.baseinfo.liveinfo.nFreeReliveCount > nFreeReliveLimit)
				gCharInfoServer.baseinfo.liveinfo.nFreeReliveCount = nFreeReliveLimit;
            ProcessReliveToMap( pRelivePosition->MapId, pRelivePosition->PositionX, pRelivePosition->PositionY, pRelivePosition->Direction, xReliveInfo );
        }
        break;
    case eReliveTypeCity:
    case eReliveTypeNearPos:
        {// ???????????????????? ????????????????
            if ( pMapData->IsEctypeMap() )  // ??????????????
            {
				//lyh???????????????????????? ??????????
				//????????,????????????country.config???????????????? vvx 2013.6.6
				
				//const MapConfig::SpecRelivePosition* pSpecRelivePosition = GetSpecRelivePosition(pMapData); //??????????????????
				//if (!pSpecRelivePosition)
				//{

				//	MapConfig::RelivePosition* pRelivePosition = GetRelivePosition(pMapData);
				//	if ( pRelivePosition == NULL )
				//	{ return; }
				//	ProcessReliveToMap( pRelivePosition->MapId, pRelivePosition->PositionX, pRelivePosition->PositionY, pRelivePosition->Direction, xReliveInfo );
				//	return ;
				//}
				//else //???????????? 
				//{
				//	ProcessReliveToMap( pSpecRelivePosition->MapId, pSpecRelivePosition->PositionX, pSpecRelivePosition->PositionY, pSpecRelivePosition->Direction, xReliveInfo );
				//}

				
				/*
				LYH:???????????? ????????????????
				1???????????????????? ????????????????????????
				2??????1 ???????? ????????????????
				3??????2??????????????????????????
				*/

				//????????????????????
				if (IsInBattle(pMapData) == Battle_Non)
				{

					//??????????
					MapConfig::RelivePosition* pNormalRelivePosition = GetRelivePosition(pMapData);
					if(pNormalRelivePosition)
					{
						const CountryConfig::ReliveSetting& xReliveSetting = theCountryConfig.GetReliveSetting();
						uint8 nFreeReliveLimit =xReliveSetting.GetReilvelSum(GetLevel());
						if(gCharInfoServer.baseinfo.liveinfo.nFreeReliveCount > nFreeReliveLimit)
							gCharInfoServer.baseinfo.liveinfo.nFreeReliveCount = nFreeReliveLimit;	
						ProcessReliveToMap( pNormalRelivePosition->MapId, pNormalRelivePosition->PositionX,
							                pNormalRelivePosition->PositionY, pNormalRelivePosition->Direction, xReliveInfo );
						return ;
					}

					//??????????
					const MapConfig::SpecRelivePosition* pSpecRelivePosition = GetSpecRelivePosition(pMapData); 
					if(pSpecRelivePosition)
					{
						const CountryConfig::ReliveSetting& xReliveSetting = theCountryConfig.GetReliveSetting();
						uint8 nFreeReliveLimit =xReliveSetting.GetReilvelSum(GetLevel());
						if(gCharInfoServer.baseinfo.liveinfo.nFreeReliveCount > nFreeReliveLimit)
							gCharInfoServer.baseinfo.liveinfo.nFreeReliveCount = nFreeReliveLimit;	
						ProcessReliveToMap( pSpecRelivePosition->MapId, pSpecRelivePosition->PositionX, 
							                pSpecRelivePosition->PositionY, pSpecRelivePosition->Direction, xReliveInfo );
						return;
					}

					//??????????
					const CountryConfig::SpecialMapSetting* pCountryRelivePosition = theCountryConfig.GetReliveMapSetting( GetCountry() );
					if(pCountryRelivePosition)
					{
						const CountryConfig::ReliveSetting& xReliveSetting = theCountryConfig.GetReliveSetting();
						uint8 nFreeReliveLimit =xReliveSetting.GetReilvelSum(GetLevel());
						if(gCharInfoServer.baseinfo.liveinfo.nFreeReliveCount > nFreeReliveLimit)
							gCharInfoServer.baseinfo.liveinfo.nFreeReliveCount = nFreeReliveLimit;	
						ProcessReliveToMap( pCountryRelivePosition->GetMapID(), pCountryRelivePosition->GetPosX(), 
							                pCountryRelivePosition->GetPosY(), pCountryRelivePosition->GetDir(), xReliveInfo );
						return;
					}

					//???? ????3??????????????????

					/*
					const CountryConfig::SpecialMapSetting* pCountryRelivePosition = theCountryConfig.GetReliveMapSetting( GetCountry() );
					if ( pCountryRelivePosition == NULL )
					{
					const MapConfig::SpecRelivePosition* pSpecRelivePosition = GetSpecRelivePosition(pMapData); //??????????????????
					if (!pSpecRelivePosition)
					{
					MapConfig::RelivePosition* pRelivePosition = GetRelivePosition(pMapData);
					if ( pRelivePosition == NULL )
					{ return; }
					ProcessReliveToMap( pRelivePosition->MapId, pRelivePosition->PositionX, pRelivePosition->PositionY, pRelivePosition->Direction, xReliveInfo );
					return ;
					}
					else //???????????? 
					{
					ProcessReliveToMap( pSpecRelivePosition->MapId, pSpecRelivePosition->PositionX, pSpecRelivePosition->PositionY, pSpecRelivePosition->Direction, xReliveInfo );
					}
					}
					else
					{
					ProcessReliveToMap( pCountryRelivePosition->GetMapID(), pCountryRelivePosition->GetPosX(), 
					pCountryRelivePosition->GetPosY(), pCountryRelivePosition->GetDir(), xReliveInfo );
					}
					*/

				}
				else
				{  //????????????
					MapConfig::RelivePosition* pRelivePosition = GetRelivePosition(pMapData);
					if ( pRelivePosition == NULL )
					{ return; }
					const CountryConfig::ReliveSetting& xReliveSetting = theCountryConfig.GetReliveSetting();
					uint8 nFreeReliveLimit =xReliveSetting.GetReilvelSum(GetLevel());
					if(gCharInfoServer.baseinfo.liveinfo.nFreeReliveCount > nFreeReliveLimit)
						gCharInfoServer.baseinfo.liveinfo.nFreeReliveCount = nFreeReliveLimit;	
					ProcessReliveToMap( pRelivePosition->MapId, pRelivePosition->PositionX, pRelivePosition->PositionY, pRelivePosition->Direction, xReliveInfo );
					return ;
				}
                // ??????????, ??????????????????
                //uint32 nReliveMapId = pRelivePosition->MapId;
                //if ( pRelivePosition->MapId == pMapData->Id )    
                //{ nReliveMapId = GetMapID(); }    

                //ProcessReliveToMap( mapID, PositionX, PositionY, Direction, xReliveInfo );
            }
            else        // ??????, ??????????????????????
            {
				//zhuxincong ???????????????????????? ??????????????
				//zhuxincong ??????????SB ??????????????FB??????????????????????????????FB????????????????????????
				//if(pMapData->mapRelivePositions.size() >= 4)
				//{
				//	/*MapConfig::RelivePosition* pRelivePosition = GetRelivePosition(pMapData);*/
				//	

				//	switch (GetCountry())
				//	{
				//	case CountryDefine::Country_LouLan:
				//		 ProcessReliveToMap( pMapData->mapRelivePositions[GetCountry()].MapId, pMapData->mapRelivePositions[GetCountry()].PositionX, pMapData->mapRelivePositions[GetCountry()].PositionY, pMapData->mapRelivePositions[GetCountry()].Direction, xReliveInfo );
				//		break;
				//	case CountryDefine::Country_KunLun:
				//		  ProcessReliveToMap( pMapData->mapRelivePositions[GetCountry()].MapId, pMapData->mapRelivePositions[GetCountry()].PositionX, pMapData->mapRelivePositions[GetCountry()].PositionY, pMapData->mapRelivePositions[GetCountry()].Direction, xReliveInfo );
				//		break;
				//	case CountryDefine::Country_DunHuang:
				//		  ProcessReliveToMap( pMapData->mapRelivePositions[GetCountry()].MapId, pMapData->mapRelivePositions[GetCountry()].PositionX, pMapData->mapRelivePositions[GetCountry()].PositionY, pMapData->mapRelivePositions[GetCountry()].Direction, xReliveInfo );
				//		break;
				//	default:
				//		 ProcessReliveToMap( pMapData->mapRelivePositions[GetCountry()].MapId, pMapData->mapRelivePositions[GetCountry()].PositionX, pMapData->mapRelivePositions[GetCountry()].PositionY, pMapData->mapRelivePositions[GetCountry()].Direction, xReliveInfo );
				//		break;
				//	}
				//}
				//else
				/*{*/

				//????????,??????????????,??????????,?????????????????? vvx 2013.6.6
				const MapConfig::SpecRelivePosition* pSpecRelivePosition = GetSpecRelivePosition(pMapData); //??????????????????
				if (!pSpecRelivePosition)
				{

					MapConfig::RelivePosition* pRelivePosition = GetRelivePosition(pMapData);
					if ( pRelivePosition == NULL )
					{ return; }
					const CountryConfig::ReliveSetting& xReliveSetting = theCountryConfig.GetReliveSetting();
					uint8 nFreeReliveLimit =xReliveSetting.GetReilvelSum(GetLevel());
					if(gCharInfoServer.baseinfo.liveinfo.nFreeReliveCount > nFreeReliveLimit)
						gCharInfoServer.baseinfo.liveinfo.nFreeReliveCount = nFreeReliveLimit;	
					ProcessReliveToMap( pRelivePosition->MapId, pRelivePosition->PositionX, pRelivePosition->PositionY, pRelivePosition->Direction, xReliveInfo );
					
					return ;
				}
				else //???????????? 
				{
					const CountryConfig::ReliveSetting& xReliveSetting = theCountryConfig.GetReliveSetting();
					uint8 nFreeReliveLimit =xReliveSetting.GetReilvelSum(GetLevel());
					if(gCharInfoServer.baseinfo.liveinfo.nFreeReliveCount > nFreeReliveLimit)
						gCharInfoServer.baseinfo.liveinfo.nFreeReliveCount = nFreeReliveLimit;
					ProcessReliveToMap( pSpecRelivePosition->MapId, pSpecRelivePosition->PositionX, pSpecRelivePosition->PositionY, pSpecRelivePosition->Direction, xReliveInfo );
					
				}

					/*const CountryConfig::SpecialMapSetting* pSetting = theCountryConfig.GetReliveMapSetting( GetCountry() );
					if ( pSetting == NULL )
					{ return; }



					ProcessReliveToMap( pSetting->GetMapID(), pSetting->GetPosX(), pSetting->GetPosY(), pSetting->GetDir(), xReliveInfo );*/
				/*}*/

                /*const CountryConfig::SpecialMapSetting* pSetting = theCountryConfig.GetReliveMapSetting( GetCountry() );
                if ( pSetting == NULL )
                { return; }

                ProcessReliveToMap( pSetting->GetMapID(), pSetting->GetPosX(), pSetting->GetPosY(), pSetting->GetDir(), xReliveInfo );*/
            }

			//lyh++ ???????????????????????? ??????
			/*const CountryConfig::ReliveSetting& xReliveSetting = theCountryConfig.GetReliveSetting();
			uint8 nFreeReliveLimit = xReliveSetting.GetFreeReliveLimitByLevel( GetLevel() );
			if (GetFreeReliveCount() >= nFreeReliveLimit)
				gCharInfoServer.baseinfo.liveinfo.nFreeReliveCount = nFreeReliveLimit ;*/
        }
        break;
    case eReliveTypeOrigin:     // ????????
		{
			if ( !xReliveInfo.bFreeRelive )
			{
				if ( _NormalItemBag.GetItemCount( /*CItemDetail::ESRI_ReliveItem*/theCountryConfig.GetReliveSetting().GetReliveItemId() ) >= theCountryConfig.GetReliveSetting().GetReliveItemCount() )
				{ _NormalItemBag.RemoveItemByID( /*CItemDetail::ESRI_ReliveItem*/theCountryConfig.GetReliveSetting().GetReliveItemId(), theCountryConfig.GetReliveSetting().GetReliveItemCount() ); }
				else
				{
					//?????????????????????????????????????? lrt
					return;
					/*const CountryConfig::ReliveSetting& xReliveSetting = theCountryConfig.GetReliveSetting();

					uint8 nFreeReliveLimit = xReliveSetting.GetFreeReliveLimitByLevel( GetLevel() );
					int32 jiaozi = GetJiaoZi();
					if (GetReliveCount() < nFreeReliveLimit)
					{
						if (jiaozi>g_Cfg.m_nReliveOriginNon)
						{
							OperateJiaoZi( EOT_Sub, g_Cfg.m_nReliveOriginNon,true, __FUNCTION__, __LINE__ ,ePlayerMoneySourceType_ReliveTypeOrigin); 
						}
						else
						{
							OperateJiaoZi( EOT_Sub, jiaozi,true, __FUNCTION__, __LINE__,ePlayerMoneySourceType_ReliveTypeOrigin ); 
							OperateMoney(EOT_Sub, g_Cfg.m_nReliveOriginNon-jiaozi,true, __FUNCTION__, __LINE__ ,ePlayerMoneySourceType_ReliveTypeOrigin);
						}
						
					}
					else
					{
						if (jiaozi>g_Cfg.m_nReliveOriginNon*5)
						{
							OperateJiaoZi( EOT_Sub, g_Cfg.m_nReliveOriginNon,true, __FUNCTION__, __LINE__,ePlayerMoneySourceType_ReliveTypeOrigin ); 
						}
						else
						{
							OperateJiaoZi( EOT_Sub, jiaozi,true, __FUNCTION__, __LINE__ ,ePlayerMoneySourceType_ReliveTypeOrigin); 
							OperateMoney(EOT_Sub, g_Cfg.m_nReliveOriginNon*5-jiaozi,true, __FUNCTION__, __LINE__ ,ePlayerMoneySourceType_ReliveTypeOrigin);
						}
					}*/
					
				}
			}

			xReliveInfo.bFlyToMap = true;
			xReliveInfo.nReliveHP = 20;
			xReliveInfo.nReliveMP = 20;
			ProcessReliveToMap( GetMapID(), GetFloatX(), GetFloatY(), GetDir(), xReliveInfo );
			//????????buff
			if (/*xReliveInfo.byAddition*/m_byReliveBuff & MsgReqRelive::EAddBuff1)
			{
				ApplyBufferStatus(theCountryConfig.GetReliveSetting().GetBuffStatusID1(),0,GetID(),SCharBuff::StatusEventType_Other,0);
			}
			
		}
		break;
    case eReliveTypeOriginFullHpMP:
        {
            if ( !xReliveInfo.bFreeRelive )
            {
				//?????????????????????? ?????????????????? ROUNDDOWN((MAX(0,????????-5)*0.6)+1,0)
				const CountryConfig::ReliveSetting& xReliveSetting = theCountryConfig.GetReliveSetting();
				uint8 nFreeReliveLimit =xReliveSetting.GetReilvelSum(GetLevel());
				int Num = ceil(max(0,GetReliveCount() - nFreeReliveLimit-5)*0.6 + 1.0) * theCountryConfig.GetReliveSetting().GetReliveItemCount();
				

                if ( _NormalItemBag.GetItemCount( /*CItemDetail::ESRI_ReliveItem*/theCountryConfig.GetReliveSetting().GetReliveItemId() ) >= Num )
                { _NormalItemBag.RemoveItemByID( /*CItemDetail::ESRI_ReliveItem, NUMERIC_ONE*/theCountryConfig.GetReliveSetting().GetReliveItemId(), Num ); }
                else
                {
					//?????????????????????????????????????? lrt
					return;
					//const CountryConfig::ReliveSetting& xReliveSetting = theCountryConfig.GetReliveSetting();

					////?????????????? ???????? 
					//int money = xReliveSetting.GetReviceMoney(GetLevel(),GetReliveCount());
					//if(money > 0)
					//{
					//	int32 jiaozi = GetJiaoZi();
					//	if (jiaozi>money)
					//	{
					//		OperateJiaoZi( EOT_Sub, money,true, __FUNCTION__, __LINE__,ePlayerMoneySourceType_ReliveTypeOriginFullHpMP ); 
					//	}
					//	else
					//	{
					//		OperateJiaoZi( EOT_Sub, jiaozi,true, __FUNCTION__, __LINE__,ePlayerMoneySourceType_ReliveTypeOriginFullHpMP ); 
					//		OperateMoney(EOT_Sub, money-jiaozi,true, __FUNCTION__, __LINE__ ,ePlayerMoneySourceType_ReliveTypeOriginFullHpMP);
					//	}
					//}
					
					//uint8 nFreeReliveLimit = xReliveSetting.GetFreeReliveLimitByLevel( GetLevel() );
					
					//if (GetReliveCount() < nFreeReliveLimit)
					//{
					//	if (jiaozi>g_Cfg.m_nReliveOriginNon)
					//	{
					//		OperateJiaoZi( EOT_Sub, g_Cfg.m_nReliveOriginNon,true, __FUNCTION__, __LINE__ ); 
					//	}
					//	else
					//	{
					//		OperateJiaoZi( EOT_Sub, jiaozi,true, __FUNCTION__, __LINE__ ); 
					//		OperateMoney(EOT_Sub, g_Cfg.m_nReliveOriginNon-jiaozi,true, __FUNCTION__, __LINE__ );
					//	}
					//	//OperateJiaoZi( EOT_Sub, g_Cfg.m_nReliveOriginNon,true, __FUNCTION__, __LINE__ ); 
					//}
					//else
					//{
					// 
					//uint8 _ReliveCntOffset = GetReliveCount() - nFreeReliveLimit - 1;
					//if (_ReliveCntOffset < 0) _ReliveCntOffset = 0;
					//float  _temp = _ReliveCntOffset * 0.1f;
     //               int32 _ReliveNeedMoney = 0;

					//if (_ReliveCntOffset <= 10) //??10??????????
					//{
					//	_ReliveNeedMoney = _temp*xReliveSetting.GetPerReliveMoney() + xReliveSetting.GetPerReliveMoney();
					//}else //10????????????????????
					//{
     //                     _ReliveNeedMoney = xReliveSetting.GetPerReliveMoney()*10;
					//}

					//if (jiaozi > _ReliveNeedMoney)
					//{
					//	//????????
					//	OperateJiaoZi( EOT_Sub, _ReliveNeedMoney,true, __FUNCTION__, __LINE__ ); 
					//}else
					//{
     //                   //????????????????????
					//	OperateJiaoZi( EOT_Sub, jiaozi,true, __FUNCTION__, __LINE__ ); 
					//	OperateMoney(EOT_Sub, _ReliveNeedMoney - jiaozi,true, __FUNCTION__, __LINE__ );

					//}
                    
						/*if (jiaozi>g_Cfg.m_nReliveOriginNon*5)
						{
							OperateJiaoZi( EOT_Sub, g_Cfg.m_nReliveOriginNon*5,true, __FUNCTION__, __LINE__ ); 
						}
						else
						{
							OperateJiaoZi( EOT_Sub, jiaozi,true, __FUNCTION__, __LINE__ ); 
							OperateMoney(EOT_Sub, g_Cfg.m_nReliveOriginNon*5-jiaozi,true, __FUNCTION__, __LINE__ );
						}*/
						
					/*}*/
				}
            }
			gCharInfoServer.baseinfo.liveinfo.nFreeReliveCount++;
            xReliveInfo.bFlyToMap = true;
            xReliveInfo.nReliveHP = 100;
            xReliveInfo.nReliveMP = 100;
            ProcessReliveToMap( GetMapID(), GetFloatX(), GetFloatY(), GetDir(), xReliveInfo );
			if (/*xReliveInfo.byAddition*/m_byReliveBuff & MsgReqRelive::EAddBuff1)
			{
				const CountryConfig::ReliveSetting RS = theCountryConfig.GetReliveSetting();
				ApplyBufferStatus(RS.GetBuffStatusID1(),RS.GetBuffStatusLV1(),GetID(),SCharBuff::StatusEventType_Other,0);
			}
			else if (/*xReliveInfo.byAddition*/m_byReliveBuff & MsgReqRelive::EAddBuff2)
			{
				const CountryConfig::ReliveSetting RS = theCountryConfig.GetReliveSetting();
				ApplyBufferStatus(RS.GetBuffStatusID2(),RS.GetBuffStatusLV2(),GetID(),SCharBuff::StatusEventType_Other,0);
			}
        }
        break;
    case eReliveTypeSkill:  // ????????
        {
            xReliveInfo.bFlyToMap = true;
            ProcessReliveToMap( GetMapID(), GetFloatX(), GetFloatY(), GetDir(), xReliveInfo );
        }
        break;
    default:
        break;
    }
}

void GamePlayer::ProcessReliveToMap( DWORD dwMapId, float fX, float fY, float fDir, SReliveInfo& xReliveInfo )
{       
    SetStatus( CS_IDLE );
    SetDead( false );
   
    int nHpUp = GetCharFightAttr()->hpMax.final * xReliveInfo.nReliveHP / 100;
    int nMpUp = GetCharFightAttr()->mpMax.final * xReliveInfo.nReliveMP / 100;

	//??????????????????????
	MapConfig::MapData* pTargetMapData = GetMapData();
	if ( pTargetMapData != NULL )
	{
		int nMapPKMode  = pTargetMapData->CanPk ;
		if(MapConfig::MapData::EPKM_Guild_PK == nMapPKMode)
		{
			nHpUp = GetCharFightAttr()->hpMax.final;
			nMpUp = GetCharFightAttr()->mpMax.final;
		}
	}

    SetHP( nHpUp );
    SetMP( nMpUp );

    // ??????????????????
    bool bResult = _buffManager.UpdateOnDead();
    if ( bResult )
    {
        //_buffManager.ApplyBuffsToChar( GetProfession(), GetCharBaseAttr(), GetCharFightAttr() );  
        ApplyBuffStatusToCharAttr();
        SendBuffChanged( NULL );
    }

    // ????5????????????????????
    bool bHaveChange = false;
    if ( ApplyBufferStatus( g_Cfg.nProtectStatusId, g_Cfg.nProtectStatusLevel, GetID(), SCharBuff::StatusEventType_Other, 0) == GLR_Success )
    { bHaveChange = true; }

    if ( bHaveChange )
    { OnBuffStatusChanged( true ); }

    // ????????
    UpdateAllEquipData();

    // ????????????
    UpdateAllSuitData() ;

    // ????????
    ApplyPassiveSkillsToChar();

    RecalcBaseProperty( false,  BV_NotFullHp, BV_SendMessage, EWRP_Relive );
		
	if ( xReliveInfo.bDeathExit )
	{
		// ????????, ??????????????
		SetLastMapID( GetMapID() );

		SetMapID( dwMapId );
		SetFloatXF( fX );
		SetFloatYF( fY );
		SetFloatZ( WORLD_HEIGHT );
		SetDir( fDir );
	}
	else
	{
		// ????????????
		if ( xReliveInfo.bFlyToMap )
		{ FlyToMapReq( dwMapId, fX, fY, fDir, xReliveInfo.bFlyToMap); } 
	}
	if( xReliveInfo.bSendMessage )
	{
		MsgCharAttrChanged Change;
		Change.iChangeCount = 0;

		// ????????????????
		// ??????????, ????????????????????,??????????,flytomap??????????????????????, ????????????????????????????????????
		Change.AddAttrShortChange( CharAttr_Relive, xReliveInfo.bFlyToMap );       
		Change.AddAttrIntChange( CharAttr_HP, GetHP() );
		Change.AddAttrIntChange( CharAttr_MP, GetMP() );
		Change.AddAttrShortChange( CharAttr_FreeRelive, GetReliveCount() );
		Change.CaluLength();
		Change.header.stID = GetID();
		GettheServer().SendMsgToSingle( &Change, this );

		MsgCharAttrChanged ChangeEveryBodyCanSee;        
		ChangeEveryBodyCanSee.iChangeCount = 0;
		ChangeEveryBodyCanSee.AddAttrShortChange( CharAttr_Relive, xReliveInfo.bFlyToMap );
		ChangeEveryBodyCanSee.AddAttrIntChange( CharAttr_HP, GetHP() );
		ChangeEveryBodyCanSee.CaluLength();
		ChangeEveryBodyCanSee.header.stID = GetID();
		GettheServer().SendMsgToView( &ChangeEveryBodyCanSee, GetID(), true );
	}
    m_bDeathAndWaitForRelive = false;

	//ProcessPKPunish();

	if(!g_Cfg.isOpenPetAttacter && m_DeadPetID !=0)
	{
		SPetItem* pPetItem = _petManager.GetPetByGuid(m_DeadPetID);
		int index = _petManager.GetPetIndexByGuid(m_DeadPetID);
        if (pPetItem)
        { 
			_petManager.ProcessSetPetActive( index );
			m_DeadPetID = 0;
		}
	}
}

bool GamePlayer::IsInBornMap()
{
	unsigned int Size = theCountryConfig.GetBornMapSettingCount(GetCountry());
	for(size_t i =0;i<Size;++i)
	{
		const CountryConfig::BornMapSetting* pSetting = theCountryConfig.GetBornMapSetting( GetCountry() );
		if ( pSetting == NULL )
			continue;	
		if(GetMapID() == pSetting->GetMapID())
			return true;
	}
	return false;
}

void GamePlayer::CorrectMapID()       // ????????
{
    MapConfig::MapData* pMapData = GetMapData();
    if( pMapData == NULL )
    { return; }

    if ( m_bHitchMoving )
    {
        // ??????????????????????????????????????????????????????
        D3DXVECTOR3 vPos = GetRouteManager().GetLastRoutePoint( GetCurTrafficID() );
        if ( vPos != D3DXVECTOR3( 0, 0, 0 ) )
        {
            SetTileX( FloatToTile( vPos.x ) );
            SetTileY( FloatToTile( vPos.y ) );
            SetFloatX( vPos.x );
            SetFloatY( vPos.y );
            SetFloatZ( WORLD_HEIGHT );
            gCharInfoServer.otherdata.pos.vPos.x  = vPos.x;
            gCharInfoServer.otherdata.pos.vPos.y  = vPos.y;
            gCharInfoServer.otherdata.pos.vPos.z  = WORLD_HEIGHT;
        }

        return;
    }
	else
	{
		////zhuxincong  ????SB????????,??flytomap????
		//SReliveInfo xReliveInfo;
		//xReliveInfo.bSendMessage = false;
		//xReliveInfo.bDeathExit = true;
		//xReliveInfo.bFlyToMap = true;
		//switch (GetCountry())
		//		{
		//		case CountryDefine::Country_LouLan:
		//			// FlyToMapReq( dwMapId, fX, fY, fDir, xReliveInfo.bFlyToMap)
		//			 FlyToMapReq( pMapData->mapRelivePositions[GetCountry()].MapId, pMapData->mapRelivePositions[GetCountry()].PositionX, pMapData->mapRelivePositions[GetCountry()].PositionY, pMapData->mapRelivePositions[GetCountry()].Direction, xReliveInfo.bFlyToMap );
		//			break;
		//		case CountryDefine::Country_KunLun:
		//			  FlyToMapReq( pMapData->mapRelivePositions[GetCountry()].MapId, pMapData->mapRelivePositions[GetCountry()].PositionX, pMapData->mapRelivePositions[GetCountry()].PositionY, pMapData->mapRelivePositions[GetCountry()].Direction, xReliveInfo.bFlyToMap );
		//			break;
		//		case CountryDefine::Country_DunHuang:
		//			  FlyToMapReq( pMapData->mapRelivePositions[GetCountry()].MapId, pMapData->mapRelivePositions[GetCountry()].PositionX, pMapData->mapRelivePositions[GetCountry()].PositionY, pMapData->mapRelivePositions[GetCountry()].Direction, xReliveInfo.bFlyToMap );
		//			break;
		//		default:
		//			 FlyToMapReq( pMapData->mapRelivePositions[GetCountry()].MapId, pMapData->mapRelivePositions[GetCountry()].PositionX, pMapData->mapRelivePositions[GetCountry()].PositionY, pMapData->mapRelivePositions[GetCountry()].Direction, xReliveInfo.bFlyToMap );
		//			break;
		//		}

		//zhuxincong ??????????????????????
		//????????
		/*GamePlayer* pPlayer = theRunTimeData.GetGamePlayerByDBID( GetDBCharacterID() );
		if (pPlayer == NULL)
		{
			return;
		}
		pPlayer->SetMapID(pMapData->mapRelivePositions[GetCountry()].MapId);
		pPlayer->SetFloatXF(pMapData->mapRelivePositions[GetCountry()].PositionX);
		pPlayer->SetFloatYF(pMapData->mapRelivePositions[GetCountry()].PositionY);*/

		//???????????????????????????????????????? by vvx 2013.2.21
	}
}

Msg* GamePlayer::FirstSightOnMe(char* szMsgBuffer, unsigned int nBuffSize)
{       
    if (nBuffSize < sizeof(MsgPlayerEnterMySight))
    { return NULL; }

    MsgPlayerEnterMySight* pMsg = new (szMsgBuffer) MsgPlayerEnterMySight;
    pMsg->header.stID = GetID();
    pMsg->nMapID = GetMapID();
    pMsg->stX    = GetTileX();
    pMsg->stY    = GetTileY();
    pMsg->byDir  = GetDir();
    pMsg->fX     = GetFloatX();
    pMsg->fY     = GetFloatY();
    pMsg->fZ     = GetFloatZ();
    pMsg->fDirX  = GetDirX();
    pMsg->fDirY  = GetDirY();
    pMsg->stModelID  = GetModelId();
    pMsg->stCharType = GetObjType();
    pMsg->bigShipId  = m_nBigShipId;
    pMsg->npcShipPos = m_nNpcShipPos;
    pMsg->bIsFlyMoving = m_bIsFlyMoving;
    pMsg->dwGuildId = GetGuildID();
	pMsg->nFamilyID = GetFamilyID();
	pMsg->familyPosition = FamilyDefine::Position_None;

	if ( m_pGuild )
	{
		GuildMember* pMember = m_pGuild->GetMember( GetDBCharacterID() );
		if ( pMember )
			pMsg->nGuildPosition = pMember->GetPosition();
	}
	
    for ( int i=0; i<EEquipPartType_MaxEquitPart; ++i )
    {
        SCharItem* pCharItem = GetVisualEquipItem( i );
        if ( NULL == pCharItem )
        { continue; }

        pMsg->stVisualItemID    [i] = pCharItem->itembaseinfo.ustItemID;
        pMsg->equipIntensifyTime[i] = pCharItem->equipdata.gemHoleCount;
        pMsg->equipLevel        [i] = pCharItem->equipdata.ucLevel;
        pMsg->equipElements     [i] = pCharItem->GetElements();
    }
    
    SCharItem* pTalismanItem = GetTalismanItem() ;
    if ( pTalismanItem != NULL )
    { pMsg->talismanId = pTalismanItem->GetItemID(); }

    pMsg->headPicId           = gCharInfoServer.baseinfo.aptotic.ucHeadPic;
    pMsg->hairId              = gCharInfoServer.visual.hairId;
    pMsg->faceId              = gCharInfoServer.visual.faceId;
	pMsg->defaultModelIndex      = gCharInfoServer.visual.defaultModelIndex;
    pMsg->showFlag            = gCharInfoServer.visual.showFlag;
    pMsg->fMoveRate           = GetMoveSpeed();
    pMsg->fNormalAttackRate   = GetCharFightAttr()->attackSpeed.final ;
    pMsg->shDromeId           = GetRideId();
	pMsg->nMountLevel		  = GetRideLevel();
    pMsg->nDromePos           = GetRidePos();
    pMsg->nDriverId           = GetRideDriverId();
    pMsg->stAction            = GetCurActionId();
    pMsg->bySubAction         = GetSubAction();
    pMsg->nActionPlayTime     = GetCurActionPlayTime();
    pMsg->nHp                 = GetHP();
    pMsg->nMp                 = GetMP();
    pMsg->nHpMax              = GetCharFightAttr()->hpMax.final;
    pMsg->nMpMax              = GetCharFightAttr()->mpMax.final;
    pMsg->fight_status        = HaveFighteFlag( eFighting ); // ????????
    pMsg->sex                 = GetSex();                         // ????
    pMsg->profession          = GetProfession();                  // ????
    pMsg->dwPlayerCharacterID = GetDBCharacterID();
    pMsg->stLevel = GetLevel();
	pMsg->shRankTitleId		  = gCharInfoServer.otherdata.rankTitle.shCurRankTitleId;
    if( IsDead() )
    { pMsg->ucCharStatus = MsgPlayerEnterMySight::charstatus_death; }
    else
    {
        if( HaveFighteFlag( eSitting ) )
        { pMsg->ucCharStatus = MsgPlayerEnterMySight::charstatus_sitdown; }
        else
        { pMsg->ucCharStatus = m_ucCharStatus; }
    }

    pMsg->nCurrentTitleID = GetCurrentTitle();
    GetRelationNameByTitle( pMsg->nCurrentTitleID, pMsg->szTitleTargetName, sizeof( pMsg->szTitleTargetName ) );

    GameTeam* pTeam = theGameTeamManager.GetTeam( GetTeamID() );
    if ( pTeam != NULL )
    {
        pMsg->teamId       = pTeam->GetID();
        pMsg->teamPosition = pTeam->IsTeamHeader( GetDBCharacterID() ) ? ETP_Leader : ETP_Member;
    }

	GameFamily* pFamily = theGameFamilyManager.GetFamilyByID( GetFamilyID() );
	if ( pFamily != NULL )
	{
		pMsg->familyPosition = pFamily->IsFamilyLeader( GetDBCharacterID() ) ? FamilyDefine::Position_Leader : FamilyDefine::Position_Member;
	}

    pMsg->nPKMode  = GetPKMode();
    pMsg->nPKValue = GetPKValue();

    pMsg->fModelPercent = gCharInfoServer.visual.fModelPercent; // ????????????????
    pMsg->influence = this->GetFightCamp();

    // ????
    pMsg->uchCountryID = GetCountry();
    pMsg->uchCountryTitle = GetCountryTitle();
	pMsg->hero_id = GetHeroId();	

    HelperFunc::SafeNCpy( pMsg->szSignature, m_pRelation->GetSignature()  , RelationDefine::MaxSignLength );
    
    return pMsg;
}

void GamePlayer::OnMsgQueryContinuousSkill( Msg*pMsg )
{       
    BaseCharacter *pChar = (BaseCharacter *)theRunTimeData.GetCharacterByID( pMsg->header.stID );
    if( !pChar )
        return;

    MsgAckContinuousSkill Ack;
    //pChar->GetContinuousSkillMsg( &Ack );
    if( Ack.stSkillNum <= 0 )
        return;
    Ack.header.stID = pMsg->header.stID;
    Ack.CaluLength();
    GettheServer().SendMsgToSingle( &Ack, this );
}

void GamePlayer::UpdateCommonData( unsigned char bForSaveDb )
{        
    HelperFunc::SafeNCpy( gCharInfoServer.baseinfo.aptotic.szCharacterName, GetCharName(), sizeof( gCharInfoServer.baseinfo.aptotic.szCharacterName ) );  
    gCharInfoServer.baseinfo.aptotic.ucCountry            = GetCountry();
    gCharInfoServer.baseinfo.liveinfo.ustLevel            = GetLevel();
    gCharInfoServer.otherdata.pos.dwMapID                 = EctypeId2MapId( GetMapID() );            // ????mapconfig????????ID      
    gCharInfoServer.otherdata.pos.stX                     = GetTileX();
    gCharInfoServer.otherdata.pos.stY                     = GetTileY();
    gCharInfoServer.otherdata.pos.vPos.x                  = GetFloatX();
    gCharInfoServer.otherdata.pos.vPos.y                  = GetFloatY();
    gCharInfoServer.otherdata.pos.vPos.z                  = GetFloatZ();
    gCharInfoServer.extendData.xRunTime.nEneryTime        = _accumulateEneryTime;
    gCharInfoServer.extendData.xRunTime.nVigorTime        = _accumulateVigorTime;
    gCharInfoServer.extendData.xRunTime.nMountActionTime  = _mountManager.GetAccumulateActionTime();
    gCharInfoServer.otherdata.dwBanSpeakTime              = ( GetBanSpeakTime() + 59999 ) / 60000;  // ????????
    gCharInfoServer.baseinfo.liveinfo.dwOnlineTime       += GetOnLineTime() / OneMinuteMicroSecond; // ??????????

    if ( bForSaveDb == BV_ForSaveDb )
    { // ???? gCharInfoServer->DbMsg
        gCharInfoServer.otherdata.stMountId = GetRideId();
        gCharInfoServer.otherdata.fDirX     = GetDirX();
        gCharInfoServer.otherdata.fDirY     = GetDirY();

        // ??buff
        for (int nloop = 0; nloop < BodyStatusType_Max; ++nloop)
        {
            gCharInfoServer.otherdata.sCharBodyStatus[nloop].Reset();

            SCharBuff* pBodyStatus = _buffManager.GetBuff( nloop );
            if ( pBodyStatus == NULL )
            { continue; }

            memcpy(&gCharInfoServer.otherdata.sCharBodyStatus[nloop],pBodyStatus,sizeof(SCharBuff));
            gCharInfoServer.otherdata.sCharBodyStatus[nloop].dwPreDamage = HQ_TimeGetTime();
        }

        SavePlayerTitleList();         // ????????????
        _SkillBag.SaveSkillColdTime(); // ????????cd????
        m_RestoreColdDown.SaveColdDown( gCharInfoServer.baseinfo.liveinfo.xItemColdDown, MAX_SAVERESTORE_COUNT );

        thePubQuestManager.SaveSpecialQuest( GetDBCharacterID() );
        theConQuestManager.SaveSpecialQuest( GetDBCharacterID() ); // ????????????????

        //Log( "_NormalItemBag Size=%d, _MaterialItemBag Size=%d", GetNormalBagSize(), GetMaterialBagSize() );
		Log( theXmlString.GetString(eServerLog_BagSize), GetNormalBagSize(), GetMaterialBagSize() );
    }
    else
    { // ??????????

    }
}


void GamePlayer::ProcessMapLoaded( bool bFirstEnterGameServer )
{
    if( IsDead() )
    { SetStatus( CS_DIEING ); }
    else
    { SetStatus( CS_IDLE );   }

	ProcessChangeMapFightGame(bFirstEnterGameServer);
    ProcessChangeMapFightCamp(bFirstEnterGameServer); // ????????????????????

    ProcessChangeMap( bFirstEnterGameServer );      // ????????????????

    //ResetCheckMoving();                           // ????????????????????

    ProcessChangeMapMsg( bFirstEnterGameServer );   // ????????????????????

    SetLastMapID( InvalidLogicNumber );
    SetLastEctypeMapID( InvalidLogicNumber );
    SetChangeStageType( GamePlayer::PlayerChangeStage );
}

void GamePlayer::ProcessChangeMapMsg( bool bFirstEnterGameServer )
{
    // ??????????????????????????
    MsgMapInfoReady xReady;
    xReady.header.stID = GetID();
    GettheServer().SendMsgToSingle( &xReady,this );

    // ??????????????????????,????????????????????????
    MapConfig::MapData* pMapData = GetMapData();
    if ( pMapData != NULL && pMapData->IsEctypeMap() && pMapData->IsLifeTimeLimitMap() )
    {
        unsigned long dwTimeRemain = 0;
        EctypeStage* pStage = static_cast< EctypeStage* >( theGameWorld.GetStageById( GetMapID() ) );
        if ( pStage != NULL && !pStage->IsStageWaitingRelease() )
        {
            dwTimeRemain = ( pStage->GetStageRemainTime() + 999 ) / 1000;
        }

        MsgEctypeStageTimeRemain xTimeRemain;
        xTimeRemain.dwTimeRemain = dwTimeRemain;
        GettheServer().SendMsgToSingle( &xTimeRemain,this );
    }

    // ????????????????????????????????????????????
    if ( bFirstEnterGameServer )
    {
		//????????????????????????????????????
		if (gCharInfoServer.otherdata.xSecondPassword.HavePassword())
		{
			MsgSetSecondPasswordAck MsgPsw;
			MsgPsw.uchResult = MsgSetSecondPasswordAck::AlreadyHavePassword;
			GettheServer().SendMsgToSingle( &MsgPsw, this );
		}
        // ??????????????
        SPetItem* pPetItem = _petManager.GetActivePet();
        if ( pPetItem != NULL )
        {
            MsgChangePet changeAck;
            changeAck.header.stID = GetID();
            changeAck.ucOpType    = MsgChangePet::EOT_Active;
            changeAck.nIndex      = _petManager.GetActivePetIndex();
            changeAck.guid        = pPetItem->baseInfo.guid;
            GettheServer().SendMsgToSingle( &changeAck, this );
        }

        m_xChangeServerTimer.DoneTimer();
    }
}

void GamePlayer::FirstEnterGameServer( char* szMacAddress )
{
    _bFirstEnterGameServer = false; // ????????
   // Log("[IP:%s][MAC:%s]\t??????????????\t[%s:%d]", GetIp(), szMacAddress, g_Cfg.szGameServerName, g_Cfg.dwServerID );

	theLogEventService.LogPlayerInOut(GetAccountID(),m_dbinfo.dwCharacterID,GetLevel(),GetCountry(),0,GetIp(),szMacAddress,ePlayerLogInfo_login,GetCharName());
	Log(theXmlString.GetString(eServerLog_EnterGameServer), GetIp(), szMacAddress, g_Cfg.szGameServerName, g_Cfg.dwServerID );

    if ( !_bFirstEnterWorld )
    {   // ??????????????
        _ProcessSwitchGameServerRuntimeInfo();
    }

    if ( _bFirstEnterWorld )            // ??????????????????
    { 
        FirstEnterGameWorld( szMacAddress ); 
    } 
    
    InitStall();// ??????????????

    // ExtMsg_AddCharacter ???????????? Buff BaseAttribute FightData?????? ????????
    if( !theGameWorld.GlobalMessage( GameWorld::ExtMsg_AddCharacter, GetID() ) )
    { // ??????,????,????????????
        LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_WARNING, "ExtMsg_AddCharacter Failed! MapID = [0x%x]", GetMapID() );
        return OnExit( NULL );
    }

    _bInLoginStage = false; // ????????????
    theRunTimeData.IncreaseEnterWorldOnlinePlayer(); // ????????????????????

    //ToModify ?????????? ????????????????????buff??????????????
    SendBuffs( NULL, false);  //
    SendCharAttibuteToClient();

    // ????????????????
    _accumulateEneryTime = gCharInfoServer.extendData.xRunTime.nEneryTime;
    _accumulateVigorTime = gCharInfoServer.extendData.xRunTime.nVigorTime;
    _mountManager.SetAccumulateActionTime( gCharInfoServer.extendData.xRunTime.nMountActionTime );

    // ????????????
    theRabotManager.AddCheckPlayer( GetDBCharacterID() );
}

void GamePlayer::FirstEnterGameWorld( char* szMacAddress )
{
    if ( gCharInfoServer.otherdata.bNewChar )
    {
        gCharInfoServer.otherdata.bNewChar = false;
        GetScriptMgr()->StartupVM( ST_CREATE_CHAR, 0, this );
    }

    EnterGameServerLog( szMacAddress );           // ????LOG

    // ????????????????????????
    StartSendOnLineMessaage();

    SetTimeVar( ECT_LastLoginTime, TimeEx::GetNowTime() );

	if(gCharInfoServer.otherdata.chProtectLockTime >99)
		gCharInfoServer.otherdata.chProtectLockTime = 1;//??????????????????1

    m_nProtectLockLeaveTime = gCharInfoServer.otherdata.chProtectLockTime * 60000; // ????????????????????

	//?????????????? ????????????????
	FirstEnterWorldClearTimeVar();

    GetScriptMgr()->StartupVM( ST_ONLINE, 0, this );

    // ????????????????
    TellAllCountryName();

    // ????????????????
    theGameGuildManager.SendGuildListToClient( GetDBCharacterID() );

	// ????????????????
	theGameFamilyManager.SendAllFamiliesToClient( GetDBCharacterID() );

    // ToModify ?????????????? ??????????????????
    if ( GetTeamID() != TeamDefine::NoneSessionID ) // ??????????CenterServer, ????????????
    {
        theGameTeamManager.SendOnLineMessage( GetDBCharacterID() );
    }

    // ????????????????????
    if ( gCharInfoServer.extendData.isOfflineHook )
    {
        // ??????????????????
        uint32 hookTime = TimeEx::GetNowTime() - GetTimeVar( ECT_LastOfflineTime );
        gCharInfoServer.extendData.totalHookTime += hookTime;
        //????????7??
        if ( gCharInfoServer.extendData.totalHookTime > OFFLINE_HOOK_MAX_TIME )
        { gCharInfoServer.extendData.totalHookTime = OFFLINE_HOOK_MAX_TIME; }
        gCharInfoServer.extendData.isOfflineHook = false;   // ????????
    }

	// ??????????????
	if ( !g_Cfg.bHaveGetAntiAddictionInfoConfig || ( g_Cfg.bIsOpenAntiAddiction && _bNeedAntiAddiction ) )
	{ // ?? game server ???????????????????????????????????? ???? ?????????? ????????????????
		GS2CSUpdateAntiaddictionInfoReq xUpdateAntiaddiction;
		xUpdateAntiaddiction.nType      = GS2CSUpdateAntiaddictionInfoReq::EUpdateReqType_Init;
		xUpdateAntiaddiction.nAccountId = GetAccountID();
		strncpy_s( xUpdateAntiaddiction.passport, sizeof(xUpdateAntiaddiction.passport), GetAccount(), sizeof(xUpdateAntiaddiction.passport)-1);
		xUpdateAntiaddiction.nDuration = 0;
		GettheServer().SendMsgToCenterServer( &xUpdateAntiaddiction );

		//DBAccountWallowInfoReq dbmsg;
		//if ( IsWallow() )
		//{ dbmsg.accountType = DBAccountWallowInfoReq::ACCOUNT_TYPE_CHILD ; }
		//dbmsg.header.stID = GetID();
		//dbmsg.accountId   = GetAccountID();
		//GettheDBCon().SendMsg( &dbmsg , GetLifeCode() );
	}
	
	

	//????????????????????????????????
	//if (GetGuild()&&GetGuild()->GetReleaseQuest() > 0)
	//{
		//GetGuild()->SendQuestReleaseStatusMessage();
	//}

}
void GamePlayer::ProcessChangeMapFightGame(bool bFirstEnterGameServer)
{
	if(!IsGameBattleFigh())
		return;
	if (!bFirstEnterGameServer&&GetFightCamp() == GameBattleDefine::GameBattle_None)
	{
		return;
	}
	GameGuildGeneralBattleManager* pManager = static_cast<GameGuildGeneralBattleManager*>(theGameBattleControl.GetGameBattleManager(GameBattleDefine::GameBattle_Type_GuildGeneral));
	if(!pManager)
	{
		SetFightGame( GameBattleDefine::GameBattle_None, true ); 
		return;
	}
	GameGuildGeneralBattle* pBattle = pManager->GetGameBattleByUnitID(GetGuildID());
	if(!pBattle || GetMapID() != pBattle->GetBattleMapID())
	{
		SetFightGame( GameBattleDefine::GameBattle_None, true ); 
		return;
	}
	SetFightGame( GetFightCamp(), true ); 
    pBattle->SendBattleStatusMessage( this );
    pBattle->SendGameBattleMatchMessage( this );
}
void GamePlayer::ProcessChangeMapFightCamp(bool bFirstEnterGameServer)
{
    // ????????, ????????, ??????????]	
	//if (GetMapID() == GetLastMapID())
	//{
	//	return;
	//}
	if(IsGameBattleFigh())
		return;
	if (!bFirstEnterGameServer&&GetFightCamp() == CampDefine::NoneCamp)
	{
		return;
	}
	
    CampBattle* pCampBattle = theCampBattleControl.GetCampBattle( GetFightCamp(), GetMapID() ,GetCountryId());
    if ( pCampBattle != NULL )
    { 
        SetFightCamp( GetFightCamp(), true ); 
        pCampBattle->SendBattleStatusMessage( this );   // ??????????????
        pCampBattle->SendCampBattleMatchMessage( this );
    }
    else
    { 
		SetFightCamp( CampDefine::NoneCamp, true ); 
    }
}

void GamePlayer::ProcessChangeMap( bool bFirstEnterGameServer )
{
    if ( _bFirstEnterWorld )
    { 
		ProcessSummonObjectEnterGameServer();
        _bFirstEnterWorld = false;  // ??????????????????????????
        return; 
    }

    m_xBuyBackItem.ClearPack(); // ??????????????????????

    // ????????????????????Buff
    _buffManager.ClearBuffWhenChangeMap();

    // ????CenterServer????????????????
    if ( GetTeamID() != TeamDefine::NoneSessionID ) // ????????????????????
    {
        MsgChangeMapCallBack xCallBack;
        xCallBack.dwTeamSessionID = GetTeamID();
        GettheServer().SendMsgToCenterServer( &xCallBack );

        TeamBattleData* pBattleData = theTeamBattleManager.GetBattleDateByMapID( EctypeId2MapId( GetMapID() ) );
        if ( pBattleData != NULL )
        {
            if ( pBattleData->IsInBattleData( GetTeamID(), GetMapID() ) )
            {
                pBattleData->SendBattleRecordToClient( GetMapID(), MsgTellBattleRecord::Status_Fighting, this );
            }
        }
    }

    if ( bFirstEnterGameServer )
    { // ???????????????????? ????????????
       ProcessSummonObjectEnterGameServer();
    }
    else
    { // ??????????????????
        if ( HaveProtectChar() )
        { ProcessSummonObjectChangeMap( GetProtectCharID() ); }

        for (int i=0;i<CharSummonPetMaxCount; ++i)
        {
            MonsterBaseEx* pAiChar = (MonsterBaseEx*) theRunTimeData.GetCharacterByID( m_xSummonPets[i].petId );
            if ( pAiChar != NULL && pAiChar->IsPet() && !pAiChar->IsIllusionChar() && pAiChar->GetMonsterType() == eMT_Pet )
            { ProcessSummonObjectChangeMap( m_xSummonPets[i].petId ); }           
        }

        if ( _petManager.HaveActivePet() )
        { ProcessSummonObjectChangeMap( _petManager.GetActivePetCharId() ); }

        if ( HaveCapturePet() )
        { ProcessSummonObjectChangeMap( GetCapturePetId() ); }
    }
}

void GamePlayer::ProcessSummonObjectChangeMap( GameObjectId objectId )
{
    // ????????????
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( objectId );

    if ( NULL == pChar || !pChar->IsMonster() )
    { return; }

    MonsterBaseEx* pAiChar = static_cast< MonsterBaseEx* >( pChar );
    GamePlayer* pMaster = pAiChar->GetMasterPlayer();
    if ( pMaster == NULL || pMaster->GetID() != GetID() )
    { return; }
    
    if( !theGameWorld.OnDelCharacter( objectId ) )
    { // ??????,????,????????????
        //Log("%s leave fail", pAiChar->GetCharName() );
		Log(theXmlString.GetString(eServerLog_leaveFail), pAiChar->GetCharName() );
    }

    // ????????Mapid
    pAiChar->SetMapID( GetMapID() );
    pAiChar->SetFloatXF( GetFloatX() + 1 );
    pAiChar->SetFloatYF( GetFloatY()  );
    pAiChar->SetDirX( GetDirX() );
    pAiChar->SetDirY( GetDirY() );

    // ????????????
    if( !theGameWorld.OnAddCharacter( objectId, __FILE__, __LINE__ ) )
    { // ??????,????,???????????? 
        //Log("%s enter fail", pAiChar->GetCharName() );
		 Log(theXmlString.GetString(eServerLog_EnterFail), pAiChar->GetCharName() );
        pAiChar->OnExit( NULL );
    }
}

void GamePlayer::ProcessSummonObjectEnterGameServer()
{
	int64 ID = GetCharInfo().otherdata.nsuanimalID;
    for ( int i=0; i<EPT_Max; ++i )
    {
        if ( gTransferRuntimeInfo.xPetInfo[i].nPetID == 0  && ID == 0)
        { continue; }

        // ????????
        MonsterCreateData xCreateData;
        xCreateData.SetMapID( GetMapID() );
        xCreateData.SetPostionX( GetFloatX() + 2.0f );
        xCreateData.SetPostionY( GetFloatY() + 2.0f );
        xCreateData.SetDirX( GetDirX() );
        xCreateData.SetDirY( GetDirY() );
        xCreateData.SetMonsterID( gTransferRuntimeInfo.xPetInfo[i].nPetID );

        MonsterBaseEx* pAIMonster = NULL;
        switch ( i )
        {
        case EPT_Skill:
            {
                int Id = GettheItemDetail().FindMonsterIndexById( gTransferRuntimeInfo.xPetInfo[i].nPetID );
                if ( Id < 0 )
                { continue; }

                pAIMonster = MonsterCreater::CreatePetSummonMonster( xCreateData, this );
                if ( pAIMonster == NULL )
                { continue; }

                SSummonPet pet;
                pet.petId = pAIMonster->GetID();
                pet.petAIType = ePetAttackAI;
                pet.skillId = gTransferRuntimeInfo.xPetInfo[EPT_Skill].nSummonSkillID;
                AddSummonPet(pet);
            }
            break;
        case EPT_Protect:
            {
                int Id = GettheItemDetail().FindMonsterIndexById( gTransferRuntimeInfo.xPetInfo[i].nPetID );
                if ( Id < 0 )
                { continue; }
				xCreateData.SetCanRide(gTransferRuntimeInfo.xPetInfo[i].IsCanRide);
                // ????????
                pAIMonster = MonsterCreater::CreateProtectedMonster( xCreateData, this );
                if ( pAIMonster == NULL )
                { continue; }

                m_ProtectCharID         = pAIMonster->GetID();
                m_nProtectCharMonsterId = gTransferRuntimeInfo.xPetInfo[i].nPetID;
                if ( gTransferRuntimeInfo.xPetInfo[i].varValue > 0 )
                { SetVar( gTransferRuntimeInfo.xPetInfo[i].varValue, 1 ); }

                pAIMonster->SetVarID( gTransferRuntimeInfo.xPetInfo[i].varValue );
            }
            break;
        case EPT_Capture:
            {
                int Id = GettheItemDetail().FindMonsterIndexById( gTransferRuntimeInfo.xPetInfo[i].nPetID );
                if ( Id < 0 )
                { continue; }

                // ????????
                pAIMonster = MonsterCreater::CreatePetCaptureMonster( xCreateData, this );
                if ( pAIMonster == NULL )
                { continue; }

                _capturePetId    = pAIMonster->GetID(); 
                SetCapturePetAIType       ( ePetAttackAI );
            }
            break;
        case EPT_Nurture:
            {
                int index = gTransferRuntimeInfo.xPetInfo[i].nPetIndex;
                if ( index < 0  && ID == 0)
                { continue; }
	
				SPetItem* pPetItem = _petManager.GetPetByGuid(ID);
				index = _petManager.GetPetIndexByGuid(ID);
                //SPetItem* pPetItem = _petManager.GetPetByIndex( index );
                if ( pPetItem == NULL )
                { continue; }

                int nResult = _petManager.ProcessSetPetActive( index );
                if ( RESULT_FAILED( nResult ) )
                { continue; }
				pAIMonster = _petManager.GetMonsterNurturePet();
            }
            break;
        }
        pAIMonster->SetHP( gTransferRuntimeInfo.xPetInfo[i].nHp );
        pAIMonster->SetMP( gTransferRuntimeInfo.xPetInfo[i].nMp );
        //pAIMonster->_buffManager.AddStatusFromData( pAIMonster->GetMapID(), gTransferRuntimeInfo.xPetInfo[i].sCharBodyStatus, BodyStatusType_Max, HQ_TimeGetTime() );
        //pAIMonster->_buffManager.ApplyBuffsToChar( GetProfession(),pAIMonster->GetCharBaseAttr(),pAIMonster->GetCharFightAttr() );

        gTransferRuntimeInfo.xPetInfo[i].nPetID = 0;
        memset( gTransferRuntimeInfo.xPetInfo[i].sCharBodyStatus, 0, sizeof(gTransferRuntimeInfo.xPetInfo[i].sCharBodyStatus) );
    }
}

void GamePlayer::StartSendOnLineMessaage()
{
    DWORD dwSpaceTime = ONE_SEC + theRand.rand16() % ONE_SEC;
    m_uchSendOnLineMessageStatus = SendQuestMessage; //lyh?? ?????? ?????? ????????
    m_xSendOnLineMessageTimer.StartTimer( HQ_TimeGetTime(), dwSpaceTime );
}

void GamePlayer::ProcessSendOnLineMessage( uint32 nCurrentTime )
{
    if ( !m_xSendOnLineMessageTimer.DoneTimer( nCurrentTime ) )
    { return; }

    switch ( m_uchSendOnLineMessageStatus )
    {
    case SendQuestMessage:      // ????????????????
        {
            // ????????????
            MsgTellQuestTime xQuestTime;
            GetQuestTimes( &xQuestTime );
            SendMessageToClient( &xQuestTime );

            // ????????
            MsgTellCharVar xTell;
            GetQuestCharVars( &xTell );
            SendMessageToClient( &xTell );

			//????????????
			OnMsgSevenDaysData( NULL );
            
            // ????????????
            TellWeakCountry(); 

			//????????????
			TellStrongCountry();

            // ????????????????????????
            TellCountryQuestStatus();  

            // ????PK??????PK??
            TellClientPKValue( false ); 
        }
        break;
    case SendRelationMessage:   // ????????????????????
        {
            if ( m_pRelation != NULL )
            { m_pRelation->ProcessEnterWorld(); }
        }
        break;
    case SendGuildMessage:      // ????????????????????????
        {
            if ( m_pGuild != NULL )  
            { m_pGuild->ProcessEnterWorld( GetDBCharacterID() ); } 
        }
        break;
	case SendFamilyMessage:
		{
			if ( m_pFamily )
			{ m_pFamily->ProcessEnterWorld( GetDBCharacterID() ); }
		}
		break;
    case SendIdentifyMessage:
        { // ??????????????
            MsgAllIdentifyData msg;
            msg.identifyData = gCharInfoServer.identifyData;
            GettheServer().SendMsgToSingle( &msg, this );
        }
        break;
    case SendOtherMessage:
        {
            // ??????????????????????
            if ( theRunTimeData.g_nExpPer > 100 || theRunTimeData.g_nSkillExpPer > 100 )
            {
                MsgTellServerExpModulus xTell;
                xTell.nExpModulus      = theRunTimeData.g_nExpPer;
                xTell.nSkillExpModulus = theRunTimeData.g_nSkillExpPer;
                SendMessageToClient( &xTell );
            }
        }
        break;
	case SendMessageEnd:
		{
			MsgSendMessageEnd msg;
			GettheServer().SendMsgToSingle( &msg, this );
			m_xSendOnLineMessageTimer.StopTimer();
		}
		break;
    default:
        m_xSendOnLineMessageTimer.StopTimer();
        break;
    }

    ++m_uchSendOnLineMessageStatus;
}

void GamePlayer::CancelCurScript( const char* szFile, const char* szFun )
{
    SScript *pScript = GetScript();
    if ( pScript == NULL )
    { return; }

    CScriptVM* pVM = pScript->thread.GetVM();
    if ( pVM != NULL)
    { pVM->Return(); }

    MsgScriptEnd msgScriptEnd;
	if ( m_dwScriptSleep != 0 )
		msgScriptEnd.type = ST_ScriptSleep;
	else
		msgScriptEnd.type = ST_UNKNOW;
    GettheServer().SendMsgToSingle( &msgScriptEnd, this );

    m_dwScriptSleep = 0;
    if ( PopScript() == true )
    {
        GetScriptMgr()->ExecuteVM( ST_UNKNOW, -1, this );
    }

   // Log( "%s:%scall CancelCurScript", szFile, szFun );
	Log( theXmlString.GetString(eServerLog_CurScript), szFile, szFun );
}

void GamePlayer::CancelAllScript()
{
    SScript* pScript = GetScript();
    if ( pScript == NULL )
    { return; }

    CScriptVM* pVM = pScript->thread.GetVM();
    if ( pVM != NULL)
    { pVM->Return(); }

    MsgScriptEnd msgScriptEnd;
	if ( m_dwScriptSleep != 0 )
		msgScriptEnd.type = ST_ScriptSleep;
	else
		msgScriptEnd.type = ST_UNKNOW;
    GettheServer().SendMsgToSingle( &msgScriptEnd, this );

    m_dwScriptSleep = 0;
    m_nScriptNpcId  = 0;
    m_lsScript.clear();

	SetScriptStatesID();
}


BOOL GamePlayer::RegisterVar( short stVarId )
{       
    SScript* pScript = GetScript();
    if ( !pScript )
    {   
        return FALSE;
    }
    pScript->nVarId = stVarId;
    return TRUE;
}

bool GamePlayer::IsNeedDropTaskItem( short stQuestId, short stTaskState, int nItemId )
{
    GameTeam* pTeam = theGameTeamManager.GetTeam( GetTeamID() );
    if( pTeam == NULL )
    {
        // ????????????????????????
        if ( GetQuestState( stQuestId ) != stTaskState )
            return false;

        // ????????????
        if( GetDropItemManager().GetTaskDropItem().IsTaskItemFull( this, nItemId ))
        { return false; }

        return true;
    }
    else
    {
        int nCount = pTeam->TeamMemberCount();
        for ( int i = 0; i < nCount; ++i )
        {
            DWORD dwPlayerID = pTeam->GetMemberIDByIndex( i );
            GamePlayer* pPlayer = theRunTimeData.GetGamePlayerByDBID( dwPlayerID );
            if ( pPlayer == NULL )
            { continue; }

            if ( pPlayer->GetQuestState( stQuestId ) != stTaskState ) // ????????????????????????
                continue;

            // ????????????
            if ( GetDropItemManager().GetTaskDropItem().IsTaskItemFull( pPlayer, nItemId ))
                continue;

            return true;
        }
    }
    return false;
}

void GamePlayer::SendCharAttibuteToClient()
{
    MsgCharAttrChanged changeMessage;
    changeMessage.iChangeCount = 0;

    for ( int i = CharAttr_Strength; i<CharAttr_AttributMaxCount; ++i )
    {
        if ( !fightAttrChangeRecord[i])
        { continue; }

        fightAttrChangeRecord[i] = false;
        switch ( i )
        {
        case CharAttr_Strength: 
             changeMessage.AddAttrFloatChange( CharAttr_Strength        , GetBaseAttr( EBaseAttr_Strength )->final    );
             break;
        case CharAttr_Agility :    
            changeMessage.AddAttrFloatChange( CharAttr_Agility          , GetBaseAttr( EBaseAttr_Agility )->final     );
            break;
        case CharAttr_Stamina:
            changeMessage.AddAttrFloatChange( CharAttr_Stamina          , GetBaseAttr( EBaseAttr_Stamina )->final     );
            break;
        case CharAttr_Intelligence:
            changeMessage.AddAttrFloatChange( CharAttr_Intelligence     , GetBaseAttr( EBaseAttr_Intelligence )->final);
            break;
        case CharAttr_HPMax:
            changeMessage.AddAttrIntChange  ( CharAttr_HPMax            , GetCharFightAttr()->hpMax            .final);
            break;
        case CharAttr_MPMax:
            changeMessage.AddAttrIntChange  ( CharAttr_MPMax            , GetCharFightAttr()->mpMax            .final);
            break;
        case CharAttr_AttackPhysics:
            changeMessage.AddAttrFloatChange( CharAttr_AttackPhysics    , GetCharFightAttr()->attackPhysics    .final);
            break;
        case CharAttr_AttackMagic:
            changeMessage.AddAttrFloatChange( CharAttr_AttackMagic      , GetCharFightAttr()->attackMagic      .final);
            break;
        case CharAttr_DefendPhysics:
            changeMessage.AddAttrFloatChange( CharAttr_DefendPhysics    , GetCharFightAttr()->defendPhysics   .final);
            break;
        case CharAttr_DefendMagic:
            changeMessage.AddAttrFloatChange( CharAttr_DefendMagic      , GetCharFightAttr()->defendMagic      .final);
            break;
        case CharAttr_AttackSpeed:
            changeMessage.AddAttrFloatChange( CharAttr_AttackSpeed      , GetCharFightAttr()->attackSpeed      .final);
            break;
        case CharAttr_MoveSpeed:
			//????????????????
			changeMessage.AddAttrFloatChange( CharAttr_MoveSpeed        , GetMoveSpeed());
			//changeMessage.AddAttrFloatChange( CharAttr_MoveSpeed        , GetCharFightAttr()->moveSpeed        .final);
            break;
        case CharAttr_HPRestore:
            changeMessage.AddAttrFloatChange( CharAttr_HPRestore        , GetCharFightAttr()->hpRestore        .final);
            break;
        case CharAttr_MPRestore:
            changeMessage.AddAttrFloatChange( CharAttr_MPRestore        , GetCharFightAttr()->mpRestore        .final);
            break;
        case CharAttr_Exact:
            changeMessage.AddAttrIntChange  ( CharAttr_Exact            , GetCharFightAttr()->exact            .final);
            break;
        case CharAttr_Dodge:
            changeMessage.AddAttrIntChange  ( CharAttr_Dodge            , GetCharFightAttr()->dodge            .final);
            break;
        case CharAttr_Critical:
            changeMessage.AddAttrFloatChange( CharAttr_Critical         , GetCharFightAttr()->critical         .final);
            break;
        case CharAttr_Tenacity:
            changeMessage.AddAttrFloatChange( CharAttr_Tenacity         , GetCharFightAttr()->tenacity         .final);
            break;
        case CharAttr_CriticalIntensity:
            changeMessage.AddAttrShortChange( CharAttr_CriticalIntensity, GetCharFightAttr()->criticalIntensity.final);
            break;
        case CharAttr_BackStrike:
            changeMessage.AddAttrShortChange( CharAttr_BackStrike       , GetCharFightAttr()->backStrike       .final);
            break;
        case CharAttr_BackStrikeResist:
            changeMessage.AddAttrShortChange( CharAttr_BackStrikeResist , GetCharFightAttr()->backStrikeResist .final);
            break;
        case CharAttr_BreakStrike:
            changeMessage.AddAttrShortChange( CharAttr_BreakStrike      , GetCharFightAttr()->breakStrike      .final);
            break;
        case CharAttr_StabStrike:
            changeMessage.AddAttrShortChange( CharAttr_StabStrike       , GetCharFightAttr()->stabStrike       .final);
            break;
        case CharAttr_ElementStrike:
            changeMessage.AddAttrShortChange( CharAttr_ElementStrike    , GetCharFightAttr()->elementStrike    .final);
            break;
        case CharAttr_ToxinStrike:
            changeMessage.AddAttrShortChange( CharAttr_ToxinStrike      , GetCharFightAttr()->toxinStrike      .final);
            break;
        case CharAttr_SpiritStrike:
            changeMessage.AddAttrShortChange( CharAttr_SpiritStrike     , GetCharFightAttr()->spiritStrike     .final);
            break;
        case CharAttr_BreakResist:
            changeMessage.AddAttrShortChange( CharAttr_BreakResist      , GetCharFightAttr()->breakResist      .final);
            break;
        case CharAttr_StabResist:
            changeMessage.AddAttrShortChange( CharAttr_StabResist       , GetCharFightAttr()->stabResist       .final);
            break;
        case CharAttr_ElementResist:
            changeMessage.AddAttrShortChange( CharAttr_ElementResist    , GetCharFightAttr()->elementResist    .final);
            break;
        case CharAttr_ToxinResist:
            changeMessage.AddAttrShortChange( CharAttr_ToxinResist      , GetCharFightAttr()->toxinResist      .final);
            break;
        case CharAttr_SpiritResist:
            changeMessage.AddAttrShortChange( CharAttr_SpiritResist    , GetCharFightAttr()->spiritResist      .final);
            break;
        }
    }

    if( changeMessage.iChangeCount > 0 )
    {    
        changeMessage.header.stID = GetID();
        changeMessage.CaluLength();
        GettheServer().SendMsgToSingle( &changeMessage, this );
    }
}

//??????????????????????????????
void GamePlayer::SendVisualEquipDataToClient()
{ // ToModify ????????
    MsgUpdateVisualEquip EquipMsg;
    for (int i=0; i<EEquipPartType_MaxEquitPart; ++i)
    { EquipMsg.AddItem( i, GetVisualEquipItem( i ) ); }
    GettheServer().SendMsgToSingle( &EquipMsg, this );
}

bool GamePlayer::IsTeamMember( BaseCharacter *pChar )
{
    if ( pChar == NULL )
    { return false; }

    if ( pChar->GetID() == GetID() )
    { return true; }

    if ( !pChar->HaveTeam() )
    { return false; }

    return GetTeamID() == pChar->GetTeamID();
}

bool GamePlayer::CheckWalkPreconditionState()
{ // ????????????
    if (HaveFighteFlag(eSitting))
        return false; // ??????????????????????

    return BaseCharacter::CheckWalkPreconditionState();
}

bool GamePlayer::CheckUseSkillPreconditionState()
{       
    //????????????????????????
    if (HaveFighteFlag(eSitting))
        return false;
    return BaseCharacter::CheckUseSkillPreconditionState();
}

bool GamePlayer::IsHaveWeapon( int16 weapontype )
{ // ??????????????
    SCharItem* pRCharItem = GetVisualEquipItem( EEquipPartType_Weapon );

    if ( pRCharItem == NULL )
    { return false; }

    ItemDefine::SItemCommon* pItemConfig = GettheItemDetail().GetItemByID( pRCharItem->itembaseinfo.ustItemID);
    if ( pItemConfig == NULL || pItemConfig->ucItemType != ItemDefine::ITEMTYPE_WEAPON )
    { return false; }

    ItemDefine::SItemWeapon* pItemWeaponConfig = (ItemDefine::SItemWeapon*)pItemConfig;
    if ( pItemWeaponConfig->stWeaponType != weapontype)
    { return false; }

    return true;
}

bool GamePlayer::OnScriptSkill( ItemDefine::SItemSkill* pItemSkill )
{
    if ( !pItemSkill )
        return false;

    // ??????????????????????????
    if ( m_dwScriptSleep != 0 )
    {
        //m_dwScriptSleep = 0;
        CancelCurScript( __FILE__, __FUNCTION__ );
    }     
    return GetScriptMgr()->StartupVM( ST_USE_ITEM, pItemSkill->ustItemID, this, false, 1, GetID() );    // ???
}

bool GamePlayer::IsHaveEquipItem( uint16 nItemId )
{
    for( int i = 0; i< EEquipPartType_MaxEquitPart; ++i )
    {
        SCharItem* pSCharItem = GetVisualEquipItem(i);
        if ( pSCharItem == NULL )
        { continue; }

        if( pSCharItem->itembaseinfo.ustItemID == nItemId ) 
        { return true; }
    }
    return false;
}

short GamePlayer::ApplySkillCost( ItemDefine::SItemSkill *pSkill )
{
    bool bResult = BaseCharacter::ApplySkillCost( pSkill );
    if ( !bResult )
        return false;

    if( GetHP() < ( pSkill->ustCostHP + 1 ) )
    {
        return  MsgUseSkillHintMessage::eNoEnoughHpToUseSkill;
    }

    if( !_buffManager.IfConsumeEnergy() )
    {
        if(GetMP() < pSkill->ustCostMP )
        {
            return MsgUseSkillHintMessage::eNoEnoughMpToUseSkill;
        }
    }

    MsgCharAttrChanged Change;
    Change.iChangeCount = 0;

    // HP????
    int nValue = 0;
    if( pSkill->ustCostHP > 0|| pSkill->nSuckHpAtt > 0)
    {
        nValue = GetHP();
        nValue -= pSkill->ustCostHP;
        //????????????
        nValue += pSkill->nSuckHpAtt;
        SetHP( nValue );
        Change.AddAttrIntChange( CharAttr_SkillHPCost,GetHP());
    }

    // MP????
    if( !_buffManager.IfConsumeEnergy() ) 
    {
        if( pSkill->ustCostMP > 0||pSkill->nSuckMpAtt >0 )
        {
            nValue = GetMP();
            nValue -= pSkill->ustCostMP;

            nValue += pSkill->nSuckMpAtt;        
            SetMP( nValue );

            Change.AddAttrIntChange( CharAttr_SkillMPCost,pSkill->ustCostMP );
        }
    }

    // XP????
    if ( (pSkill->usConsumeFightPower > 0) && (GetXP() >= pSkill->usConsumeFightPower) )
    {
        short sValue = GetXP();
        sValue -= pSkill->usConsumeFightPower;
        SetXP( sValue );

        Change.AddAttrShortChange( CharAttr_XPValue, GetXP() );
    }

    if (  pSkill->usConsumeVigor > 0 )
    {   
        short sValue = GetVigor();
        sValue -= pSkill->usConsumeVigor;
        SetVigor( sValue );
        Change.AddAttrShortChange( CharAttr_Vigor, GetVigor() );
    }

    if( Change.iChangeCount > 0 )
    {
        Change.CaluLength();
        Change.header.stID = GetControl()->GetID();
        GettheServer().SendMsgToSingle( &Change, this );
    }
    return MsgUseSkillHintMessage::eNormal;
}
void GamePlayer::UnEquipAndRemove( uint8 part)
{
    if (part >= EEquipPartType_MaxEquitPart)
    { return; }

	SCharItem* pEquip = GetVisualEquipItem( part );
    if ( NULL == pEquip )
    { return; }

	if(CS_INTONATE == GetStatus())
	{
		//????????????????????
		SendChangeEquipErrorInfo();
		return;
	}

    ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID(pEquip->itembaseinfo.ustItemID);
    if ( NULL == pItemCommon || !pItemCommon->IsCanEquip() )
    { return; }

    ItemDefine::SItemCanEquip* pItemCanEquip = (ItemDefine::SItemCanEquip*)pItemCommon;
    if ( NULL == pItemCanEquip )
    { return; }

	RemoveEquipItemSkill( part );

	pEquip->itembaseinfo.ustItemID = InvalidLogicNumber;
    pEquip->itembaseinfo.nOnlyInt  = 0;

    SendVisualEquipDataToClient(); // ??????????????player
	
    if (pItemCanEquip->ucItemType == ItemDefine::ITEMTYPE_WEAPON)
    { UpdateNormalAttackSkillId(); }

    UpdateAllEquipData();       // ??????????????????????

    // ????????????
    UpdateAllSuitData() ;

    ApplyPassiveSkillsToChar();  // ??????????player

    RecalcBaseProperty( false,  BV_NotFullHp, BV_SendMessage, EWRP_Equip );

	if ( (gCharInfoServer.visual.IsShowAecorative() && (part == EEquipPartType_AecorativeGoods || part == EEquipPartType_AecorativeClothing ))
        || (!gCharInfoServer.visual.IsShowAecorative() && (part != EEquipPartType_AecorativeGoods && part != EEquipPartType_AecorativeClothing )) )
    {
        //??????????????player????????,????????????????????
        MsgEquipChanged2 changed;
        changed.header.stID = GetID();
        changed.cWhere      = part;
        SCharItem* pCharItem = GetVisualEquipItem( part );
        if ( pCharItem )
        { changed.equip = *pCharItem;}
        changed.nSuitIndex  = gCharInfoServer.visual.IsShowAecorative();
        GettheServer().SendMsgToView( &changed, GetID(), true );
    }
}
void GamePlayer::UnEquip( uint8 ustWhere, uint16 stPackIndex )
{
	//??????????????
    /*if (HaveFighteFlag(eFighting))
    { return; }*/

    if ( !ProcessSecondPasswordOperate( PasswordDefine::EProtect_UnpackEquip, PasswordDefine::OP_InitAction ) )
    { return;}  // ??????????????????????????

	if(CS_INTONATE == GetStatus())
	{
		//????????????????????
		SendChangeEquipErrorInfo();
		return;
	}

    if (GetHP() <= 0 || ustWhere >= EEquipPartType_MaxEquitPart)
    { return; }

    SCharItem* pEquip = GetVisualEquipItem( ustWhere );
    if ( NULL == pEquip )
    { return; }

    ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID(pEquip->itembaseinfo.ustItemID);
    if ( NULL == pItemCommon || !pItemCommon->IsCanEquip() )
    { return; }

    ItemDefine::SItemCanEquip* pItemCanEquip = (ItemDefine::SItemCanEquip*)pItemCommon;
    if ( NULL == pItemCanEquip )
    { return; }

    unsigned short ustCount = 0;

    Log( theXmlString.GetString( eLog_info_2slk_154), pEquip->itembaseinfo.ustItemID,pEquip->itembaseinfo.ustItemCount);
    int nRes = _NormalItemBag.PushItem( *pEquip, ustCount, stPackIndex );
    if ( nRes != ierr_Success )
    { return; }

    RemoveEquipItemSkill( ustWhere );

    pEquip->itembaseinfo.ustItemID = InvalidLogicNumber;
    pEquip->itembaseinfo.nOnlyInt  = 0;

    SendVisualEquipDataToClient(); // ??????????????player

    //if ( ustWhere != EEquipPartType_AecorativeGoods && ustWhere != EEquipPartType_AecorativeClothing ) //??????????????
    { // ????????
        if (pItemCanEquip->ucItemType == ItemDefine::ITEMTYPE_WEAPON)
        { UpdateNormalAttackSkillId(); }

        UpdateAllEquipData();       // ??????????????????????

        // ????????????
        UpdateAllSuitData() ;

        ApplyPassiveSkillsToChar();  // ??????????player

        RecalcBaseProperty( false,  BV_NotFullHp, BV_SendMessage, EWRP_Equip );
    }

    if ( (gCharInfoServer.visual.IsShowAecorative() && (ustWhere == EEquipPartType_AecorativeGoods || ustWhere == EEquipPartType_AecorativeClothing ))
        || (!gCharInfoServer.visual.IsShowAecorative() && (ustWhere != EEquipPartType_AecorativeGoods && ustWhere != EEquipPartType_AecorativeClothing )) )
    {
        //??????????????player????????,????????????????????
        MsgEquipChanged2 changed;
        changed.header.stID = GetID();
        changed.cWhere      = ustWhere;
        SCharItem* pCharItem = GetVisualEquipItem( ustWhere );
        if ( pCharItem )
        { changed.equip = *pCharItem;}
        changed.nSuitIndex  = gCharInfoServer.visual.IsShowAecorative();
        GettheServer().SendMsgToView( &changed, GetID(), true );
    }

	//????7????
	_sevenDayManager.TriggerSevenDaysVar( (int)SevenDaysConfig::TD_SixthDay );
	_sevenDayManager.TriggerSevenDaysVar( (int)SevenDaysConfig::TD_SeventhDay );

	//????????????
	GetCharInfo().otherdata.equipTotalScore = 0;
	for( int i = 0; i < EEquipPartType_MaxEquitPart; i++ )
	{
		SCharItem* pSCharItem = GetVisualEquipItem(i);
		if ( !pSCharItem )
			continue;

		GetCharInfo().otherdata.equipTotalScore += pSCharItem->equipdata.fScore;
	}
}

void GamePlayer::_ProcessRefreshProtectTime ( uint32 dwCurTime )
{
    //// ????????
    //if ( GetProtectTime() > 0 && GameTime::IsPassCurrentTime( dwCurTime, GetProtectTime(), g_Cfg.protecttime * 1000 ) )
    //{ SetProtectTime( 0 ); }

    //if (m_nCompoundRateAddTemp == 0&&_buffManager.GetCompoundRate() > 0)
    //{
    //    m_nCompoundRateAddTemp = _buffManager.GetCompoundRate();
    //    TellCompooundRateAdd();
    //}
    //else if(m_nCompoundRateAddTemp > 0)
    //{
    //    if (m_nCompoundRateAddTemp != _buffManager.GetCompoundRate())
    //    {
    //        m_nCompoundRateAddTemp = _buffManager.GetCompoundRate();
    //        TellCompooundRateAdd();
    //    }    
    //}

    //if (m_nIntensifyRateAddTemp == 0&&_buffManager.GetIntensifyRate())
    //{
    //    m_nIntensifyRateAddTemp = _buffManager.GetIntensifyRate();
    //    TellIntensifyRateAdd();
    //}
    //else if(m_nIntensifyRateAddTemp > 0)
    //{
    //    if (m_nIntensifyRateAddTemp != _buffManager.GetIntensifyRate())
    //    {
    //        m_nIntensifyRateAddTemp = _buffManager.GetIntensifyRate();
    //        TellIntensifyRateAdd();
    //    }
    //}
}

void GamePlayer::_ProcessRefreshProtectChar ( uint32 dwCurTime )
{
    // ??????????????????????
    if ( !HaveProtectChar() )
    { return; }

    if ( !GameTime::IsPassCurrentTime( m_dwCheckProtectTimePer, AiDefine::TellClientDisPerTime ) )
    { return; }

    BaseCharacter* pProtectPet = theRunTimeData.GetCharacterByID(GetProtectCharID());
    if ( pProtectPet == NULL || !pProtectPet->IsMonster() )
    { return; }
    
    m_dwCheckProtectTimePer = HQ_TimeGetTime();

    if ( pProtectPet->GetMapID() != GetMapID())
    { 
        TellClient(theXmlString.GetString(eTell_Client_ProtectCharDis)); 

        MsgProtectPetPos msgPos;
        msgPos.header.stID = GetID();
        msgPos.nPetID = pProtectPet->GetID();
        msgPos.nMapID = pProtectPet->GetMapID();
        msgPos.pos    = pProtectPet->GetPos();
        GettheServer().SendMsgToSingle( &msgPos, this );
    }
    else
    {
        D3DXVECTOR3 vDistance( pProtectPet->GetFloatX() - GetFloatX(), pProtectPet->GetFloatY() - GetFloatY(), 0 );
        float fDistance = D3DXVec3Length( &vDistance);

        if ( fDistance > AiDefine::ProjectCharDistance )
        { 
			if (mBiaocheState) //lyh?????????????? ?????????????? ????????????????????
			{    
			 pProtectPet->SetFloatXF(this->GetFloatX());
			 pProtectPet->SetFloatYF(this->GetFloatY());
			
			}else
			{
			ShowInfo(false, 262, theXmlString.GetString(eTell_Client_ProtectCharDis)); 
			}
		}

        MsgProtectPetPos msgPos;
        msgPos.header.stID = GetID();
        msgPos.nPetID = pProtectPet->GetID();
        msgPos.nMapID = pProtectPet->GetMapID();
        msgPos.pos    = pProtectPet->GetPos();
        GettheServer().SendMsgToSingle( &msgPos, this );
    }
}

void GamePlayer::_ProcessRefreshRestore ( uint32 dwCurTime )
{
#ifdef _DEBUG
    //???????????????????? MsgCharAttrChanged
    return;
#endif // _DEBUG

    short stRate  = 0;
    short stValue = 0;

    MsgCharAttrChanged Change;
    Change.iChangeCount = 0;

    MsgCharAttrChanged ChangeEveryBodyCanSee;
    ChangeEveryBodyCanSee.iChangeCount = 0;

    //////////////////////////////////////////////////////////////////////////
    //  HP ????????
    //////////////////////////////////////////////////////////////////////////
    if( GameTime::IsPassCurrentTime( m_restoretime.dwLastHPRestoreTime, g_Cfg.nCharHPRestoreCheck ) )
    {
        // ??????????????????
        m_restoretime.dwLastHPRestoreTime     = dwCurTime;  

        if ( GetHP() < GetCharFightAttr()->hpMax.final )
        {
            // ????????????????????
            if( !HaveFighteFlag( eFighting ) )
            {
                //??HP
                stRate = GetCharFightAttr()->hpRestore.final;
                //????????
                if ( GetSubAction() == CS_SubAction_SitDown )
                { stRate = g_Cfg.m_SitdownRestorePer*stRate; }

                if( stRate > 0 && GetHP() < GetCharFightAttr()->hpMax.final )
                {        
                    OperateHP( EOT_Add, stRate );
                    ChangeEveryBodyCanSee.AddAttrIntChange( CharAttr_HP, GetHP() );
                }

            }
            else
            { // ??????
                stRate = GetCharFightAttr()->hpRestore.final;    
                if( stRate > 0 && GetHP() < GetCharFightAttr()->hpMax.final )
                {            
                    OperateHP( EOT_Add, stRate );       
                    ChangeEveryBodyCanSee.AddAttrIntChange( CharAttr_HP, GetHP() );
                }
            }
        }
    }

    //////////////////////////////////////////////////////////////////////////
    //  MP ????????
    //////////////////////////////////////////////////////////////////////////
    int nProfession   =   GetProfession();  //????????????
    if( GameTime::IsPassCurrentTime( m_restoretime.dwLastMPRestoreTime, g_Cfg.nCharMPCheckTime[nProfession] ) )
    {
        // ??????????????????
        m_restoretime.dwLastMPRestoreTime     = dwCurTime;  

        // ????????????????????
        if( !HaveFighteFlag( eFighting ) )
        {
            // ??MP
            stRate = GetCharFightAttr()->mpRestore.final;

            //????????
            if ( GetSubAction() == CS_SubAction_SitDown )
            { stRate = g_Cfg.m_SitdownRestorePer*stRate; }

            if( stRate > 0 && GetMP() < GetCharFightAttr()->mpMax.final )
            {    
                OperateMP( EOT_Add, stRate );
                Change.AddAttrIntChange(CharAttr_MP, GetMP() );
            }
        }
        else
        { // ??????

            stRate = GetCharFightAttr()->mpRestore.final;
            if( stRate > 0 && GetMP() < GetCharFightAttr()->mpMax.final )
            {    
                OperateMP( EOT_Add, stRate );
                Change.AddAttrIntChange(CharAttr_MP, GetMP() );
            }
        }
    }

    //////////////////////////////////////////////////////////////////////////
    //  XP ????????
    //////////////////////////////////////////////////////////////////////////
    if( GameTime::IsPassCurrentTime( m_restoretime.dwLastXPRestoreTime, g_Cfg.nCharXPRestoreCheck ) )
    {
        // ??????????????????
        m_restoretime.dwLastXPRestoreTime     = dwCurTime;  

        if ( GetXP() < DEF_CHAR_XP_LIMIT )
        {
            // ????????????????
            if( !HaveFighteFlag( eFighting ) )
            {
                //??10??????2??
                SetXP( GetXP() + DEF_XP_NOFIGHT_RESTORE );        
                Change.AddAttrIntChange( CharAttr_XPValue, GetXP() );
            }
        }
    }

    //????????    
    if( Change.iChangeCount > 0 )
    {    
        Change.header.stID = GetID();
        Change.CaluLength();
        GettheServer().SendMsgToSingle( &Change, this );
    }

    if( ChangeEveryBodyCanSee.iChangeCount > 0 )
    {
        ChangeEveryBodyCanSee.header.stID = GetID();
        ChangeEveryBodyCanSee.CaluLength();
        GettheServer().SendMsgToView( &ChangeEveryBodyCanSee, GetID(), false );
    }
}

void GamePlayer::_ProcessCurrentAction ( uint32 dwCurTime )
{
    if ( (m_nCurActionPlayTime != 0) && (dwCurTime >= m_nCurActionPlayTime) )
    {
        m_nCurActionId  = 0;
        m_nCurActionPlayTime = 0;
    }
}

void GamePlayer::_ProcessLongIntervalTimer( uint32 dwCurTime )
{
    // ????????????????
    if( GameTime::IsPassCurrentTime( m_restoretime.dwLastPassOnlineTime, ONE_MIN) )
    {
        m_restoretime.dwLastPassOnlineTime  = dwCurTime;
        _achieveManager.UpdateTriggerByValueType( EAT_OnlineTime , /*GetOnLineTime() / ONE_MIN*/1,1 );
    }

    //????????????????????????????
    if ( RecordTime::CheckRecordTime( GetRecordReliveTime() ) )
    {
		int LogSum = gCharInfoServer.baseinfo.liveinfo.nFreeReliveCount;
        gCharInfoServer.baseinfo.liveinfo.nFreeReliveCount = 0;
        RecordTime::SaveRecordTime( gCharInfoServer.baseinfo.liveinfo.nRecordReliveTime );
		//????????????????
		if(LogSum != 0)
		{
			MsgCharAttrChanged Change;
			Change.iChangeCount = 0;
			Change.AddAttrShortChange( CharAttr_FreeRelive, GetReliveCount() );
			Change.CaluLength();
			Change.header.stID = GetID();
			GettheServer().SendMsgToSingle( &Change, this );
		}
    }

    //????????????????
    SPetItem* pBreedPet = _petManager.GetBreedPet();
    if ( pBreedPet != NULL )
    {
        int64 interval = TimeEx::GetNowTime() - pBreedPet->breedInfo.commitTime ;
        int32 petBreedIntervalTime = OneMinuteSecond * g_Cfg.petBreedIntervalTime;
        int32 petBreedFailedTime   = OneMinuteSecond * g_Cfg.petBreedFailedTime ;

        if ( interval >= petBreedIntervalTime && !m_bBreedPetPrompt )
        {
            MsgPetBreedAcquireAck msgAck;
            msgAck.result = MsgPetBreedAcquireAck::ER_BreedTime;
            msgAck.pet    = *pBreedPet;
            GettheServer().SendMsgToSingle( &msgAck, this );
            m_bBreedPetPrompt = true;
        }

        if ( interval >= petBreedFailedTime )
        { 
            MsgPetBreedAcquireAck msgAck;
            msgAck.result = MsgPetBreedAcquireAck::ER_PetLost;
            msgAck.pet    = *pBreedPet;
            GettheServer().SendMsgToSingle( &msgAck, this );

            _petManager.ClearBreedPet(); 
        }
    }
}

bool  GamePlayer::AddSysDoubleExpTime ( int nValue ) 
{ 
    if (gCharInfoServer.baseinfo.liveinfo.nSysDoubleExpTime >= CHAR_SYS_DOUBLE_EXP_MAX_TIME)
    { 
        SendErrorToClient( ER_SysDoubleExpTimeLimit );
        return false; 
    }

    gCharInfoServer.baseinfo.liveinfo.nSysDoubleExpTime  += nValue * OneMinuteMicroSecond; 

    if(gCharInfoServer.baseinfo.liveinfo.nSysDoubleExpTime > CHAR_SYS_DOUBLE_EXP_MAX_TIME)
    { gCharInfoServer.baseinfo.liveinfo.nSysDoubleExpTime = CHAR_SYS_DOUBLE_EXP_MAX_TIME; }

    MsgDoubleExpAck msgack;
    msgack.bState = m_bIsOpenDoubleExp;
    msgack.nSysDoubleExpTime  = gCharInfoServer.baseinfo.liveinfo.nSysDoubleExpTime;
    msgack.nItemDoubleExpTime = gCharInfoServer.baseinfo.liveinfo.nItemDoubleExpTime;
    GettheServer().SendMsgToSingle( &msgack , this );

    return true;
}

bool  GamePlayer::AddItemDoubleExpTime( int nValue ) 
{ 
    if (gCharInfoServer.baseinfo.liveinfo.nItemDoubleExpTime >= CHAR_ITEM_DOUBLE_EXP_MAX_TIME)
    { 
        SendErrorToClient( ER_ItemDoubleExpTimeLimit );
        return false; 
    }

    gCharInfoServer.baseinfo.liveinfo.nItemDoubleExpTime += nValue * OneMinuteMicroSecond; 

    if(gCharInfoServer.baseinfo.liveinfo.nItemDoubleExpTime > CHAR_ITEM_DOUBLE_EXP_MAX_TIME)
    { gCharInfoServer.baseinfo.liveinfo.nItemDoubleExpTime = CHAR_ITEM_DOUBLE_EXP_MAX_TIME; }

    MsgDoubleExpAck msgack;
    msgack.bState = m_bIsOpenDoubleExp;
    msgack.nSysDoubleExpTime  = gCharInfoServer.baseinfo.liveinfo.nSysDoubleExpTime;
    msgack.nItemDoubleExpTime = gCharInfoServer.baseinfo.liveinfo.nItemDoubleExpTime;
    GettheServer().SendMsgToSingle( &msgack , this );

    return true;
}

void GamePlayer::ClearDoubleExpStatus()
{
    gCharInfoServer.baseinfo.liveinfo.nSysDoubleExpTime  = 0;
    gCharInfoServer.baseinfo.liveinfo.nItemDoubleExpTime = 0;
    _buffManager.ClearBuffByBuffId( ItemDefine::ESSI_DoubleExpStatus );
    m_restoretime.dwLastDoubleExpTime = 0 ;
    m_bIsOpenDoubleExp = false;

    OnBuffStatusChanged( true );

    MsgDoubleExpAck msgack;
    msgack.bState = m_bIsOpenDoubleExp;
    msgack.nSysDoubleExpTime  = gCharInfoServer.baseinfo.liveinfo.nSysDoubleExpTime;
    msgack.nItemDoubleExpTime = gCharInfoServer.baseinfo.liveinfo.nItemDoubleExpTime;

    GettheServer().SendMsgToSingle( &msgack , this );
}

void GamePlayer::_ProcessDoubleExpTime( uint32 dwCurTime )
{
    if ( !IsOpenDoubleExp() )
    { return; }

    if (m_restoretime.dwLastDoubleExpTime == 0)
    { m_restoretime.dwLastDoubleExpTime = HQ_TimeGetTime(); }

    uint32 dwPassTime = dwCurTime - m_restoretime.dwLastDoubleExpTime;
    if (dwPassTime <= 0 )
    { return; }

    uint32 nSysDoubleExpTime   = gCharInfoServer.baseinfo.liveinfo.nSysDoubleExpTime;
    uint32 nItemDoubleExpTime  = gCharInfoServer.baseinfo.liveinfo.nItemDoubleExpTime;
    uint32 nTotalDoubleExpTime = nSysDoubleExpTime + nItemDoubleExpTime;

    if ( nTotalDoubleExpTime <= dwPassTime )
    {  
        ClearDoubleExpStatus(); 
        return;
    }
    
    if ( gCharInfoServer.baseinfo.liveinfo.nSysDoubleExpTime >= dwPassTime )
    {
        gCharInfoServer.baseinfo.liveinfo.nSysDoubleExpTime -= dwPassTime;
    }
    else if (gCharInfoServer.baseinfo.liveinfo.nItemDoubleExpTime >= dwPassTime)
    {
        dwPassTime -= gCharInfoServer.baseinfo.liveinfo.nSysDoubleExpTime;
        gCharInfoServer.baseinfo.liveinfo.nSysDoubleExpTime = 0;

        gCharInfoServer.baseinfo.liveinfo.nItemDoubleExpTime -= dwPassTime;
    }
    else
    {
        ClearDoubleExpStatus();
        return;
    }

    m_restoretime.dwLastDoubleExpTime = HQ_TimeGetTime();
}

void GamePlayer::RefreshCharData( uint32 dwCostTime )
{  
    // ????
    BaseCharacter::RefreshCharData( dwCostTime );

    // ????????
    _RefreshEnergyAbout( dwCostTime );
    _RefreshVigorAbout ( dwCostTime );
    //_mountManager.RefreshMountData( dwCostTime );

    _petManager.RefreshPetData( dwCostTime );

    uint32 dwCurTime = HQ_TimeGetTime();

    //_ProcessRefreshProtectTime ( dwCurTime );

    _ProcessRefreshProtectChar ( dwCurTime );

    // ????Player??????????????????
    _ProcessRefreshRestore ( dwCurTime );

    _ProcessCurrentAction  ( dwCurTime );

    _ProcessDoubleExpTime  ( dwCurTime );

    _ProcessLongIntervalTimer( dwCurTime );
}

//----
//????????....????????
//----
//????????
void GamePlayer::StatusLoginStart()
{
    if (Object_Player == GetObjType())
    {
        //??????????
        CriticalError(__FUNCTION__, __FILE__, __LINE__);
    }
}
//PlayerChar??????????????????????????????????????????????..(????????????????)
void GamePlayer::StatusLoginCheck()
{
    const DWORD c_CheckDelayTime = 1000 * 20; //????????????????10??????????????????????
    if (Object_Player == GetObjType())
    {
        if ( GameTime::IsPassCurrentTime( m_dwStatusStartTime, c_CheckDelayTime ) )
        {
            //??????????
            //CriticalError();
        }
    }
}

//????????
void GamePlayer::StatusLoginLogin()
{
    const DWORD c_CheckDelayTime = 1000 * 40; //????????????????20??????????????????????
    if (Object_Player == GetObjType())
    {
        if ( GameTime::IsPassCurrentTime( m_dwStatusStartTime, c_CheckDelayTime ) ) 
        {
            //??????????
            //CriticalError();
        }
    }
}

void GamePlayer::StatusLoginWaitDBRet()
{
    const DWORD c_CheckDelayTime = 1000 * 60 * 5; //????????????????5????????????????????????
    if (Object_Player == GetObjType())
    {
        if ( GameTime::IsPassCurrentTime( m_dwStatusStartTime, c_CheckDelayTime ) )
        {
            //??????????
            CriticalError(__FUNCTION__, __FILE__, __LINE__);
        }
    }
}

//??????????????????
void GamePlayer::StatusLoginLoginToDB()
{
    if (Object_Player == GetObjType())
    {

    }
}

//??????????????????
void GamePlayer::StatusLoginDBLoginED()
{
    if ( IsPlayer() )
    { }
}

bool GamePlayer::IsBeginVigorOfflineFight()
{
    if ( !_offlineFightTime.IsStart() )
    { return false; }

    if ( _offlineFightTime.DoneTimer( HQ_TimeGetTime() ) )
    {
        int nValue = 0;
        if ( GetLevel() <= 29 )
        { nValue = 2; }
        else if ( GetLevel() <= 49 )
        { nValue = 4; }
        else
        { nValue = 6; }

        Script_SetVigor( nValue, SKW_SETSUB );
        if ( GetVigor() == 0 )
        { 
            MsgOfflineFightOpAck msg;
            msg.result = ER_VigorNotEnoughOnOfflineFight;
            msg.op     = EOfflineFightOP_End;
            GettheServer().SendMsgToSingle( &msg, this );
            return false; 
        }
    }
    return true;
}

bool GamePlayer::IsCanVigorOfflineFight()
{
    int nValue = 0;
    if ( GetLevel() <= 29 )
    { nValue = 2; }
    else if ( GetLevel() <= 49 )
    { nValue = 4; }
    else
    { nValue = 6; }

    if ( GetVigor() < nValue )
    { return false; }

    return true;
}

void GamePlayer::ProcessLogicBeforeProcessMsg( DWORD dwCostTime, bool& bContinue )
{
    bool bCostTime = false;    // ??????????????????????
    m_dwProcessLogicCostTime += dwCostTime; // ???????? ??????????????????????????????

    m_ExtendStatus.Process();  // ????????????
    
    //m_SkillHoldTime.Run(); //????????????
    
    int status = GetStatus();
    switch( status )
    {
//////////////////////////////////////////////////////////////////////////
// ??????????
    case CS_START: // ???????? ??Character::??????????????
        StatusLoginStart();
        break;
    case CS_CHECK: // PlayerChar??????????????????????????????????????????????..(????????????????)
        StatusLoginCheck();
        break;
    case CS_LOGIN: // ????????
        StatusLoginLogin();
        break;
    case CS_LOGINTODB: // ??????????????????
        StatusLoginLoginToDB();
        break;
    case CS_WAITDBRET: // ????????????????Player????????
        StatusLoginWaitDBRet();
        break;
    case CS_DBLOGINED: // ??????????????????
        StatusLoginDBLoginED();
        break;
//////////////////////////////////////////////////////////////////////////
// ????????
    case CS_LOADINGMAP://??????????????????????????????????????
        break;
    case CS_IDLE:
    case CS_WALK:
        StatusActionIdle();
        break;
    case CS_READYTOUSESPEICALSKILL:
        StatusActionReadyToUseSpecialSkill();
        break;
    case CS_USESPEICALSKILL:
        StatusActionUseSpecialSkill();
        break;
    case CS_ATTACK://??????????????????
        StatusActionAttack();
        break;
    case CS_INTONATE://????
        StatusActionIntonate();
        break;
    case CS_HOLDSKILL://????????
        StatusActionHoldSkill();
        break;
    case CS_HURT:
        break;
    case CS_DIEING:// ??????????????????????
        {
            StatusActionDieing();
            // ??????????????????????????????
            // ??????????????1????????
            if( GameTime::IsPassCurrentTime( m_dwLastRefreshStatusTime, CHAR_REFRESHTIME ) )
            {    
                m_dwLastRefreshStatusTime = HQ_TimeGetTime();                
                UpdateBuff(); // ??????????????????
            }
        }            
        break;
    case CS_DOACTION: // ??????????
        StatusActionDoAction();
        break;
    default:
        break;
    }

    // ????????(????????????????????????)
    switch( status )
    { // ??????????????????????????
    case CS_IDLE:
    case CS_WALK:
    case CS_ATTACK:
    case CS_HURT:
    case CS_INTONATE:
    case CS_DOACTION:        
        {
            if( GameTime::IsPassCurrentTime( m_dwLastRefreshCharDataTime, 1000 ) ) // ??????????????1????????
            {   
                if( !IsDead() )
                {
                    RefreshCharData( m_dwProcessLogicCostTime );
                }

                m_dwLastRefreshCharDataTime = HQ_TimeGetTime();
                bCostTime = true;
            }
        }
        break;
    default:
        break;
    }

    //??????????????????????????????????
    //setRequesting(false) ????????????????

    if ( bCostTime )
    { m_dwProcessLogicCostTime = 0; }

    bContinue = true;
}

void GamePlayer::Run( DWORD dwCostTime )
{
    BEGINFUNCPERLOG( "GamePlayer->Run" );

    bool bIsHaveEnmity = false;
    if ( m_bTellCostTime && dwCostTime >= m_dwTellCostTime ) 
    { TellClient( theXmlString.GetString(eClient_AddInfo_2slk_113), dwCostTime); }

    // ??????????????????????
    ProcessSendOnLineMessage( HQ_TimeGetTime() );

    BEGINFUNCPERLOG( "GamePlayer->Step1" );
    if( GetStatus() > CS_DBLOGINED )
    { 
        if ( g_Cfg.bAntiPluginOpen )
        { _graphicCodeManager.Update(); }

        if( m_bAttackLockChar )
        {
            if( m_nLockID < 0 )
            {
                SetAttackLockCharState( false );
                m_nLockID = -1;
            }
            else
            {
                if( TryNormalAttack() == -1)
                {
                    SetAttackLockCharState( false );
                }
            }
        }

        if( m_bHitchMoving  )
        {
            DWORD dwMoveInterval = ONE_SEC;
            if ( m_bIsFlyMoving ) { dwMoveInterval = 500; } // ?????????????? ???????????? ????????????
            if ( GameTime::IsPassCurrentTime( _lastHitchMovingTime, dwMoveInterval) )
            {
                DoHitchMoving( GetCurTrafficID() );
                _lastHitchMovingTime = HQ_TimeGetTime();
            }
        }

        if( GameTime::IsPassCurrentTime( _lastVerifyPosTime, 3000 ) )
        {
            // ??????????????????
            CheckPosRightful();

            // ????????????
            theGameWorld.OnRefreshNewArea( GetID() );

            //if( m_bInPKZone )
            //{
            //    CheckCurInPKZone();
            //}

            //int nCount = theGameWorld.OnRefreshPlayerCharNumberInView( GetID() );
            //m_dwSendPlayerMovingMsgRate = nCount*nCount*2;

            //DWORD dwLastReceiveMoveMessageTime = GetLastReceiveMoveMessageTime();
            //if( g_dwLastWorldProcessTime > dwLastReceiveMoveMessageTime && g_dwLastWorldProcessTime - dwLastReceiveMoveMessageTime > 3000 )

            // 0919??????
            if( theGameWorld.g_dwLastWorldProcessTime - GetLastReceiveMoveMessageTime() > 3000 )
            {
                MsgPlayerVerifyPos msg;
                msg.header.stID = GetID();
                msg.vPos.x = GetFloatX();
                msg.vPos.y = GetFloatY();
                msg.vPos.z = GetFloatZ();
                GettheServer().SendMsgToView( &msg, GetID(), true );
            }
            _lastVerifyPosTime = HQ_TimeGetTime();
        }

        // ???????????? ????????????????????????
        ProcessRefreshEnmity( HQ_TimeGetTime() );         

        CheckScriptSleep();
    }
    ENDFUNCPERLOG( "GamePlayer->Step1" );

    BEGINFUNCPERLOG( "GamePlayer->Step2" );
    // ????????????????????
    if ( g_Cfg.dwServerID == CHARACTERSERVERID )
    { // ??CharacterServer????
        if ( g_Cfg.bAntiPluginOpen )
        { _graphicCodeManager.Update(); }
    }

    PKProcessRun( dwCostTime ); // ????PK????
    _SkillBag.Update();
	_HeroSkillBag.Update();
    _mountManager.Update( dwCostTime );
	_petManager.UpdatePetInfo();
    ENDFUNCPERLOG( "GamePlayer->Step2" );

    // ????????????????
    ProcessWaitChangeStage();
    
    // ??????????????0
    ProcessCheckVarClearTime();
    ProcessClearTimeVar();

	ProessClearSalary();
    
    BEGINFUNCPERLOG( "GamePlayer->Step3" );
    BaseCharacter::Run( dwCostTime );
    ENDFUNCPERLOG( "GamePlayer->Step3" );

    RunUpdateTime( dwCostTime );        // ????????
    SetLastUpdateTime( HQ_TimeGetTime() );

    // ??????Update
    UpdateAntiAddiction();

	OnUpdatePetExp();//??????????????

	CheckIsNeedLeaveTeam();//????????????????????
#ifdef NPGUARD
	_authManager.OnUpdate(this);
#endif
    unsigned int nOfflineTime = GetOfflineTime();
    if( nOfflineTime != 0 && GameTime::IsPassCurrentTime( nOfflineTime, 1000 ) )
    {
		// ????????
		if ( GetStallOpenOffline() && nOfflineTime < GetOfflineStallEndTime() )
		{
			m_nOfflineTime = GetOfflineStallEndTime();

			// ????????????
			MsgTellStartStall xTell;
			xTell.nPlayerID = GetID();
			xTell.nModelID  = GetStallModelID( true );
			xTell.blIsOffline = true;
			HelperFunc::SafeNCpy( xTell.szTitle, GetStallTitle(), sizeof( xTell.szTitle ) );
			GettheServer().SendMsgToView( &xTell, GetID(), true );

			// ????????????
			GS2CSPlayerSynInServerInfo msg;
			msg.header.stID            = GetID();
			msg.uchCountry             = 0;
			msg.nAccountId             = GetAccountID();
			msg.serverInfo.nServerId   = g_Cfg.dwServerID;
			msg.serverInfo.nServerType = g_Cfg.dwServerID == CHARACTERSERVERID ? ST_CharacterServer : ST_GameServer;
			msg.ucStatus               = GS2CSPlayerSynInServerInfo::ES_OfflineStall;
			GettheServer().SendMsgToCenterServer( &msg );
		}
		else
		{ OnExit(NULL, GetOfflineType()); }
	}

    ENDFUNCPERLOG( "GamePlayer->Run" );
}

void GamePlayer::RunUpdateTime( uint32 dwCostTime )
{
    m_xChangeServerTimer.DoneTimer();
    m_xSkillItemRelive.xTimer.DoneTimer();

    //  ????????????????
    if( gCharInfoServer.otherdata.dwHighShoutCDTime != 0 ) 
    {
        if ( gCharInfoServer.otherdata.dwHighShoutCDTime <= dwCostTime )
        {
            gCharInfoServer.otherdata.dwHighShoutCDTime = 0;
        }
        else
        {
            gCharInfoServer.otherdata.dwHighShoutCDTime -= dwCostTime;
        }
    }

    if ( m_nProtectLockLeaveTime != 0 ) 
    { // ??????????????????
        m_nProtectLockLeaveTime -= dwCostTime;
        if ( m_nProtectLockLeaveTime < 0 )
            m_nProtectLockLeaveTime = 0;
    }

    if ( IsBanSpeak() )             
    { // ????????????,????GM????????
        if ( GetBanSpeakTime() <= dwCostTime )
        { SetBanSpeakTime( 0 ); }
        else
        { SetBanSpeakTime( GetBanSpeakTime() - dwCostTime ); }
    }

    // ????????????????
    if ( m_nCountrySpeakSpaceTime > 0 )
    {
        m_nCountrySpeakSpaceTime -= dwCostTime;
        if ( m_nCountrySpeakSpaceTime < 0 )
        { m_nCountrySpeakSpaceTime = 0; }
    }
}


bool GamePlayer::ResetItemTime( SCharItem *pItem )
{       
    if( pItem == NULL )
    { return false; }

    ItemDefine::SItemCommon *pItemDetail = GettheItemDetail().GetItemByID( pItem->itembaseinfo.ustItemID );
    if( !pItemDetail )
    { return false; }

    if ( pItemDetail->IsExclusive() )
    {   
        //ItemDatail??????????????????. ?????????????? 
        if( pItemDetail->nUseTime != TimeEx::UNDEF_TIME )
        {
            char szID[60] = { 0 };
            TimeEx timesrc(  pItem->itembaseinfo.n64UseTime  );
            Log(
                theXmlString.GetString(eLog_info_2slk_102),
                pItemDetail->GetItemName(),
                BigInt2String(pItem->itembaseinfo.nOnlyInt, szID), 
                timesrc.GetYear(),timesrc.GetMonth(), timesrc.GetDay(),
                timesrc.GetHour(),timesrc.GetMinute()                            
                );

            uint32 dwTime = pItemDetail->nUseTime * 60 * 60 ; 
            TimeSpan timespan( dwTime );
            TimeEx DestTime = TimeEx::GetCurrentTime() + timespan;

            pItem->itembaseinfo.n64UseTime = DestTime.GetTime();
            pItem->bCanUse = true;

            TimeEx timedest( pItem->itembaseinfo.n64UseTime  );
            Log(
                theXmlString.GetString(eLog_info_2slk_103),
                pItemDetail->GetItemName(),
                BigInt2String(pItem->itembaseinfo.nOnlyInt, szID), 
                timespan.GetTotalMinutes()
                );
            Log(
                theXmlString.GetString(eLog_info_2slk_104),
                pItemDetail->GetItemName(),
                BigInt2String(pItem->itembaseinfo.nOnlyInt, szID), 
                timedest.GetYear(),timedest.GetMonth(), timedest.GetDay(),
                timedest.GetHour(),timedest.GetMinute()                            
                );
        }
        else
        {
            //????Time????1????????????
            pItem->itembaseinfo.n64UseTime = TimeEx::UNDEF_TIME;
        }
        //////////////////////////////////////////////////////////////////////////        
    }
    else
    {
        pItem->itembaseinfo.n64UseTime = TimeEx::UNDEF_TIME;
    }    

    return true;
}

//void GamePlayer::TryAttackLockChar()
//{
//    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( m_shLockCharID );
//    if ( pChar == NULL )
//    {
//        SetAttackLockCharState( false );
//        m_shLockCharID = -1;
//        return;
//    }
//
//    if( pChar->IsMonster() )
//    {
//        MonsterBaseEx* pAIChar = (MonsterBaseEx*)pChar;
//        if ( !pAIChar->IsNeedFightMonster() )
//        {   
//            SetAttackLockCharState( false );
//            return;
//        }
//    }
//
//    if ( !IsCanAttack( pChar ) )
//    {
//        SetAttackLockCharState( false );
//        return;
//    }
//
//    SetAttackLockCharState( true );
//}

long GamePlayer::TryNormalAttack()
{ // -1 ?????????????? : 0 ????  : 1 ????????????????????????
    BaseCharacter* pTargetChar = theRunTimeData.GetCharacterByID(m_nLockID);
    if ( !pTargetChar )
    { return -1; }

    if( pTargetChar->IsItem() )
    { return -1; }

    if ( pTargetChar->IsDead() || IsDead() )
    { return -1; }

    if( m_bHitchMoving ) // ????????
    { return -1; }

	//??????????????
	if ( pTargetChar->IsResourceMonster() )
	{ return -1; }

	//????????????????????????
	if(pTargetChar->IsMonster() &&!pTargetChar->HaveMaster())
	{	
		if (pTargetChar->GetCountry() != CountryDefine::Country_Init &&
			GetCountry() == pTargetChar->GetCountry())
		{
			return -1;
		}
	}
	

    // ????????????????????
    if ( _buffManager.IsRandRun() )
    { return -1; }

    if ( !pTargetChar->_buffManager.IsCanBePhyAttack() )
    { return -1; }

    if ( IsOpenStall() )
    { return -1; }

    if( !CheckCanAttackTarget(pTargetChar) )
    { return -1; }

    if ( !_buffManager.IsCanUsePhysicsSkill() )
    { return -1; }

    int nSkillId = GetNormalAttackSkillId(m_iAttackHand);
    ItemDefine::SItemSkill* pSkill = GettheItemDetail().GetSkillByID(nSkillId, 1);
    if ( pSkill == NULL )
    { return -1;}

    // ??????????????????????????
    if ( GetRideId() > InvalidLogicNumber )
    {
        ItemDefine::SDrome* pMountConfig = GettheItemDetail().GetDromeByID( GetRideId() );
        if ( pMountConfig != NULL && pMountConfig->stOperaType == ItemDefine::OperaType_Control  )
        { return -1; }
    }

    if ( !_SkillTaskManager.IsTaskEmpty() )
    {
        /*if ( GetProfession() == EArmType_Hunter )
        {  return 1; }
        else
        {  return 1; }*/
        return 1;
    }

    if( m_ExtendStatus.IsCannotNormalAttack() || !m_ExtendStatus.IsCannotNormalAttackDone() )
    { return 1; }

    // ??????????????????
    float fRangeCorrect = 1.0f;
    if( !IsInAttackRange( pTargetChar, pSkill, fRangeCorrect ) )
    {   
        if( theGameWorld.g_dwLastWorldProcessTime - m_dwLastHintMessageSendTime > HINTMESSAGESENDRATE )
        {
            MsgUseSkillHintMessage HintMsg;
            HintMsg.header.stID = GetID();
            HintMsg.shHintId    = MsgUseSkillHintMessage::eOutAttackRangeHint;
            GettheServer().SendMsgToSingle( &HintMsg, this );
            m_dwLastHintMessageSendTime = theGameWorld.g_dwLastWorldProcessTime;
        }
        return 1;
    }

    // ????????
    if( pSkill->bNeedTestAngle && !IsTargetInFront( pTargetChar, pSkill->fAngle ))
    {
        if( theGameWorld.g_dwLastWorldProcessTime - m_dwLastHintMessageSendTime > HINTMESSAGESENDRATE )
        {
            MsgUseSkillHintMessage HintMsg;
            HintMsg.header.stID = GetID();
            HintMsg.shHintId = MsgUseSkillHintMessage::eUnfaceToTarget;
            GettheServer().SendMsgToSingle( &HintMsg, this );
            m_dwLastHintMessageSendTime = theGameWorld.g_dwLastWorldProcessTime;
        }
        return 1;
    }

    //// ????????
    //if ( pTargetChar->_buffManager.GetHurtImmunity() > 0 )
    //{
    //    MsgUseSkillHintMessage HintMsg;
    //    HintMsg.header.stID = GetID();
    //    HintMsg.TargetID = pTargetChar->GetID();   
    //    HintMsg.shHintId = MsgUseSkillHintMessage::eHurtImmunity;
    //    GettheServer().SendMsgToView( &HintMsg, GetID() );
    //    m_dwLastHintMessageSendTime = theGameWorld.g_dwLastWorldProcessTime;

    //    int nHurtImmunity = pTargetChar->_buffManager.GetHurtImmunity() - 1;
    //    pTargetChar->_buffManager.SetHurtImmunity( nHurtImmunity );

    //    return -1;
    //}

    SAttackTarget sTarget;
    sTarget.bIsCharTarget = true;
    sTarget.nCharID = pTargetChar->GetID();

    if ( pSkill->bEmissionSkill )
    {
        _SkillTaskManager.SetTasks( SSkillTask::STT_SingleSkill, true, pTargetChar->GetID(), D3DXVECTOR3(0,0,0), nSkillId, 1 );
    }
    else
    {
        DWORD state = SkillDischarge(&sTarget, nSkillId, 1,this );
        if ( state == eFIGHT_NOFLAG )
        { TryPassivenessTriggerAttack(); }
    }

    return 0;
}

void GamePlayer::_ProcessSwitchGameServerRuntimeInfo()
{
    // ????????????
    short sMountId = GetRidingMountIdInDb();
    if ( sMountId >= 0 )
    { 
		  ItemDefine::SDrome* pItemDrome = GettheItemDetail().GetDromeByID( sMountId );
		  if(pItemDrome && pItemDrome->stMaxRange != 0) //??????????????
		  {
            _mountManager.SetLastRidePos(-1,-1,-1); //????????????
		  }
		DoRide( sMountId );//??????????????????
	}
    // ????
    //_mountManager.ProcessSwitchGameServerRuntimeInfo( gTransferRuntimeInfo );

    m_nProtectLockLeaveTime = gTransferRuntimeInfo.dwProtectLockLeaveTime;
    _graphicCodeManager.SetInFightTime( gTransferRuntimeInfo.inFightTime );

    SetReqRemoveMarriage( gTransferRuntimeInfo.bReqRemoveMarriage );
    SetForceRemove( gTransferRuntimeInfo.bForceRemove );

    // ????????????????
    m_nCountrySpeakSpaceTime = gTransferRuntimeInfo.nCountrySpeakSpaceTime;
    // m_xBuyBackItem.InitPack( gTransferRuntimeInfo.xBuyBackItem, sizeof( gTransferRuntimeInfo.xBuyBackItem ) / sizeof( SCharItem ) );
}

#define ENERGY_UPDATE_TIME ( 10 * 60 * 1000 )

void GamePlayer::_RefreshEnergyAbout( DWORD dwCostTime )
{
    if ( gCharInfoServer.baseinfo.liveinfo.activity == gCharInfoServer.baseinfo.liveinfo.activityMax )
    { return; }

    _accumulateEneryTime += dwCostTime;
    if ( _accumulateEneryTime > ENERGY_UPDATE_TIME )
    {
        int count = _accumulateEneryTime / ENERGY_UPDATE_TIME;

        if ( _accumulateEneryTime >= count * ENERGY_UPDATE_TIME )
        { _accumulateEneryTime -= count * ENERGY_UPDATE_TIME; }
        else
        { _accumulateEneryTime = 0; }

        /*if ( GetLevel() <= 29 )
        {
            gCharInfoServer.baseinfo.liveinfo.vigor += 2 * count;
        }
        else if ( GetLevel() <= 59 )
        {
            gCharInfoServer.baseinfo.liveinfo.vigor += 3 * count;
        }
        else
        {
            gCharInfoServer.baseinfo.liveinfo.vigor += 4 * count;
        }*/
		int nextLevel = GetLevel();
		if(nextLevel%10 != 0)
			nextLevel = nextLevel/10 +1;
		else
			nextLevel = nextLevel/10;
		nextLevel = nextLevel * count;
		gCharInfoServer.baseinfo.liveinfo.activity += nextLevel;
        
        if ( gCharInfoServer.baseinfo.liveinfo.activity > gCharInfoServer.baseinfo.liveinfo.activityMax )
        { gCharInfoServer.baseinfo.liveinfo.activity = gCharInfoServer.baseinfo.liveinfo.activityMax; }

        ChangeAttr( CharAttr_Energy, gCharInfoServer.baseinfo.liveinfo.activity, true );
    }
}

void GamePlayer::_RefreshVigorAbout( DWORD dwCostTime )
{
    if ( gCharInfoServer.baseinfo.liveinfo.vigor == gCharInfoServer.baseinfo.liveinfo.vigorMax )
    { return; }

    _accumulateVigorTime += dwCostTime;
    if ( _accumulateVigorTime > ENERGY_UPDATE_TIME )
    {
        int count = _accumulateVigorTime / ENERGY_UPDATE_TIME;

        if ( _accumulateVigorTime >= count * ENERGY_UPDATE_TIME )
        { _accumulateVigorTime -= count * ENERGY_UPDATE_TIME; }
        else
        { _accumulateVigorTime = 0; }

        if ( GetLevel() <= 29 )
        {
            gCharInfoServer.baseinfo.liveinfo.vigor += 2 * count;
        }
        else if ( GetLevel() <= 59 )
        {
            gCharInfoServer.baseinfo.liveinfo.vigor += 3 * count;
        }
        else
        {
            gCharInfoServer.baseinfo.liveinfo.vigor += 4 * count;
        }

        if ( gCharInfoServer.baseinfo.liveinfo.vigor > gCharInfoServer.baseinfo.liveinfo.vigorMax )
        { gCharInfoServer.baseinfo.liveinfo.vigor = gCharInfoServer.baseinfo.liveinfo.vigorMax; }

        ChangeAttr( CharAttr_Vigor, gCharInfoServer.baseinfo.liveinfo.vigor, true );
    }
}

void GamePlayer::UpdateNormalAttackSkillId()
{
    m_nNormalAttSkillId0 = ConstSkillId_NormalAttack_Combat;
    m_nNormalAttSkillId1 = ConstSkillId_NormalAttack_Combat;    

    SCharItem* pSCharItem = GetVisualEquipItem(EEquipPartType_Weapon);
    if ( NULL == pSCharItem)
    { return; }

    ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( pSCharItem->itembaseinfo.ustItemID );
    if ( NULL == pItemCommon)
    { return; }

    if ( pItemCommon->ucItemType == ItemDefine::ITEMTYPE_WEAPON )
    {
        ItemDefine::SItemWeapon* pItemWeapon = (ItemDefine::SItemWeapon *)pItemCommon;
        if ( NULL == pItemWeapon )
        { return; }

        switch(pItemWeapon->stWeaponType)
        {
        case eWeaponType_Warrior:
            m_nNormalAttSkillId0 = ConstSkillId_NormalAttack_Warrior;
            m_nNormalAttSkillId1 = ConstSkillId_NormalAttack_Warrior;
            break;
        case eWeaponType_Mage:
            m_nNormalAttSkillId0 = ConstSkillId_NormalAttack_Mage;
            m_nNormalAttSkillId1 = ConstSkillId_NormalAttack_Mage;
            break;
        case eWeaponType_Taoist:
            m_nNormalAttSkillId0 = ConstSkillId_NormalAttack_Taoist;
            m_nNormalAttSkillId1 = ConstSkillId_NormalAttack_Taoist;
            break;
        case eWeaponType_Assassin:
            m_nNormalAttSkillId0 = ConstSkillId_NormalAttack_Assassin;
            m_nNormalAttSkillId1 = ConstSkillId_NormalAttack_Assassin;
            break;
        case eWeaponType_Hunter:
            m_nNormalAttSkillId0 = ConstSkillId_NormalAttack_Hunter;
            m_nNormalAttSkillId1 = ConstSkillId_NormalAttack_Hunter;
            break;
        case eWeaponType_Sniper:
            m_nNormalAttSkillId0 = ConstSkillId_NormalAttack_Sniper;
            m_nNormalAttSkillId1 = ConstSkillId_NormalAttack_Sniper;
            break;
        }
    }   
}

int GamePlayer::GetNormalAttackSkillId(int nAttackHand)
{       
    if (nAttackHand == 0)
    { return m_nNormalAttSkillId0; }
    else if (nAttackHand == 1)
    { return m_nNormalAttSkillId1; }
    else
    { return -1; }
}

bool GamePlayer::CreateProtectMonster( int monsterId, int varId, bool isCanRide )
{
    // ????????????????
    KillProtectChar();

    MonsterCreateData xCreateData;
    xCreateData.SetMapID( GetMapID() );
    xCreateData.SetPostionX( GetFloatX() + 2.0f );
    xCreateData.SetPostionY( GetFloatY() + 2.0f );
    xCreateData.SetDirX( GetDirX() );
    xCreateData.SetDirY( GetDirY() );
    xCreateData.SetMonsterID( monsterId );
	xCreateData.SetCanRide( isCanRide );
    MonsterBaseEx* pMonster = MonsterCreater::CreateProtectedMonster( xCreateData, this );
    if ( pMonster == NULL )
    { return false; }

    pMonster->SetVarID( varId );

    gTransferRuntimeInfo.xPetInfo[EPT_Protect].nSummonSkillID = -1;
    m_ProtectCharID         = pMonster->GetID();
    m_nProtectCharMonsterId = monsterId;

    return true;
}

void GamePlayer::ResetLostProtectCharData()
{
    m_ProtectCharID         = -1;
    m_nProtectCharMonsterId = -1;
	mBiaocheState			= false;

	// ??????????????
	GetCharFightAttr()->moveSpeed.base = 5.0;
	GetCharFightAttr()->moveSpeed.UpdateFinal();
	ChangeAttr(CharAttr_MoveSpeed, GetMoveSpeed());
}

void GamePlayer::KillProtectChar()
{       
	if ( m_ProtectCharID >= 0 )
    {
		BaseCharacter* pProtectChar = theRunTimeData.GetCharacterByID( m_ProtectCharID );
        if( pProtectChar )
        {
            MsgExit exit;
            exit.header.stID = pProtectChar->GetID();
            pProtectChar->OnExit(&exit);
        }
		
		ResetLostProtectCharData();
    }   
}

void GamePlayer::KillCapturePet()
{
    if ( HaveCapturePet() )
    {
        BaseCharacter* pCapturePet = theRunTimeData.GetCharacterByID( GetCapturePetId() );
        if( pCapturePet )
        {
            MsgExit exit;
            exit.header.stID = pCapturePet->GetID();
            pCapturePet->OnExit(&exit);
        }
        LostCapturePet();
    }
}

int GamePlayer::GetProtectCharMonsterId()
{ // ????????
    if ( m_ProtectCharID < 0 )
    {
        m_nProtectCharMonsterId = -1;
        return -1;
    }

    BaseCharacter* pProtectChar = theRunTimeData.GetCharacterByID( m_ProtectCharID );
    if( pProtectChar == NULL )
    {   
        m_ProtectCharID         = -1;
        m_nProtectCharMonsterId = -1;
        return -1;
    }

    D3DXVECTOR3 vCharPos = GetPos();
    D3DXVECTOR3 vProtectCharPos = pProtectChar->GetPos();
    vCharPos.z        = 0;
    vProtectCharPos.z = 0;

    float fDistance = D3DXVec3Length( &(vCharPos - vProtectCharPos) );
    if( fDistance > 24 )
    { return -1;}

    return m_nProtectCharMonsterId;
}

bool GamePlayer::IsCanRide( void )
{
    // ??????????????????
    if ( _buffManager.IsHide() )
    {
        ShowInfo( false, 269, theXmlString.GetString(eClient_AddInfo_2slk_58) );
        return false;
    }
    if ( HaveFighteFlag( eFighting ) )
    {
        ShowInfo( false, 269, theXmlString.GetString(eClient_AddInfo_2slk_59) );
        return false;
    }
	if (!_buffManager.IsCanRide())
	{
		ShowInfo( false, 269, theXmlString.GetString(eClient_AddInfo_2slk_58) );
		return false;
	}
    return true;
}

bool GamePlayer::DoRide( int nId )
{
    if ( nId == -1)
    { // id??-1??????????
        MsgChangeDrome changedrome;
        changedrome.header.stID = GetID();
        changedrome.nDromeID    = -1;
        changedrome.ucOpType    = MsgChangeDrome::EOT_Ride;
        GettheServer().SendMsgToView( &changedrome, GetID(), false );

        _mountManager.AllPlayerGotOffMultiMount();
        _mountManager.SetActiveBeRiding( false );
        _mountManager.RemoveActiveSkillBag();
        _mountManager.ClearMountStatusToMaster();
        _mountManager.SetLastRidePos( GetMapID(), GetFloatX(), GetFloatY());
        _mountManager.SetActiveMountConfig( NULL );

        SetRideId(-1);
		SetRideLevel(0);
        SetRideDriverId(InvalidGameObjectId);

        GetCharFightAttr()->moveSpeed.pet = 0;
        GetCharFightAttr()->moveSpeed.UpdateFinal();
        ChangeAttr( CharAttr_MoveSpeed, GetMoveSpeed() );
    }
    else if ( nId == -2 )
    { // id??-2????????????????
        int nMountID = _mountManager.GetActiveMountId();
        if ( nMountID < 0 )
        {
            SendErrorToClient( ER_NotActiveMount  );
            return false;
        }

        DoRide( nMountID );
    }
    else
    {
        ItemDefine::SDrome* pItemDrome = GettheItemDetail().GetDromeByID( nId );
        if( pItemDrome == NULL )
        {
            //Log("DoRide() Fail MountID[%d] ", nId );
			Log(theXmlString.GetString(eServerLog_DoRideFail), nId );
            SendErrorToClient( ER_ErrorMountData  );
            return false;
        }

        // ????????????????????
        MapConfig::MapData* pMapData = GetMapData();
        if ( pMapData == NULL || !pMapData->CanRide )
        {
            ShowInfo( false, 269, theXmlString.GetString(eClient_AddInfo_2slk_56) );
            return false;
        }

        if ( IsOpenStall() )
        { return false; }

        if ( _buffManager.IsHide() )
        { // ????????????????
            ShowInfo( false, 269, theXmlString.GetString(eClient_AddInfo_2slk_58) );
            return false;
        }

		if ( !_buffManager.IsCanRide() )
		{ // ??????????????
			ShowInfo( false, 269, theXmlString.GetString(eClient_AddInfo_2slk_NoRide) );
			return false;
		}

        //if ( HaveFighteFlag( eFighting ) )
        //{ // ??????
        //    ShowInfo( false, 269, theXmlString.GetString(eClient_AddInfo_2slk_59) );
        //    return false;
        //}
		DoRide(-1);//?????? ??????
        IntonateInterrupt( ItemDefine::EIT_Normal, __FUNCTION__ );

        m_dwLastDoRideTime = HQ_TimeGetTime();

        SetRideId( nId );
		if (_mountManager.GetActiveMount())
			SetRideLevel(_mountManager.GetActiveMount()->baseInfo.level);
		else
			SetRideLevel( 0 );
        SetRideDriverId( GetID() );
        _mountManager.SetActiveBeRiding( true );
        _mountManager.UpdateActiveSkillBag();
        _mountManager.ApplyMountStatusToMaster();

		int MapId,PosX,PosY = 0;
		_mountManager.GetLastRidePos(MapId,PosX,PosY);
		if ( MapId!=-1)
		{  //???????????????????? ?????????? ??????SetLastRidePos ????????????????
			_mountManager.SetLastRidePos( GetMapID(), GetFloatX(), GetFloatY() );
		}
       
        _mountManager.SetActiveMountConfig( pItemDrome );

        GetCharFightAttr()->moveSpeed.pet = pItemDrome->fSpeed;
        GetCharFightAttr()->moveSpeed.UpdateFinal();
        ChangeAttr( CharAttr_MoveSpeed, GetMoveSpeed() );

        MsgChangeDrome changedrome;
        changedrome.header.stID = GetID();
        changedrome.nDromeID    = nId;
		if (_mountManager.GetActiveMount())
			changedrome.nMountLevel = _mountManager.GetActiveMount()->baseInfo.level;
		else
			changedrome.nMountLevel = 0;
        changedrome.ucOpType    = MsgChangeDrome::EOT_Ride;
        if (pItemDrome->stCarry >= 2)
        {//????????????
            _mountManager.InitMultiMount ( pItemDrome->stCarry );
            _mountManager.GotOnMultiMount( GetID() );
        }

        GettheServer().SendMsgToView( &changedrome, GetID(), false );
    }

    return true;
}

bool  GamePlayer::IsCanPet( void )
{
	if (IsDead())
	{
		return false;
	}
	MapConfig::MapData* pMapData = GetMapData();
	if (pMapData==NULL || !pMapData->CanPet)
	{
		return false;
	}
	return true;
}

bool GamePlayer::DoPet(int nIndex)
{
	if (nIndex==-1)	//????????
	{
		MsgChangePet Msg;
		Msg.ucOpType = MsgChangePet::EOT_UnActive;
		SPetItem* pPetItem = _petManager.GetActivePet();
		if (!pPetItem)
		{
			return false;
		}
		Msg.header.stID = GetID();
		Msg.guid = pPetItem->GetPetGuid();
		Msg.nIndex = _petManager.GetActivePetIndex();

		//????????????????????
		_petManager.LostActivePetMonster();
		//_petManager.ClearPassiveSkillAffect();
		_petManager.GetActiveSkillBag()->SaveSkillColdTime();
		//??????????????????????????????????????????????????????????????????buff
		{
			for (int indexSkill=0; indexSkill<pPetItem->skillInfo.GetCurrentSkillCount(); indexSkill++)
			{
				ItemDefine::SItemSkill* pPetSkill = GettheItemDetail().GetSkillByID( pPetItem->skillInfo.skills[indexSkill].ustSkillID, pPetItem->skillInfo.skills[indexSkill].stSkillLevel );
				if(pPetSkill && pPetSkill->petSkillCategory==EPetSkillCategory_Aptitude && pPetSkill->stGeneralType==ItemDefine::generaltype_passive)
				{
					//????????????????????????buff
					ApplyPetAttrToChar(pPetSkill,true);
				}
			}
		}
		RefreshLieutenantAttr(false);
		//////////////////////////////////////////////////////////////////////
		GettheServer().SendMsgToSingle( &Msg, this );
	}
	else
	{
		

		MapConfig::MapData* pMapData = GetMapData();
		if (pMapData==NULL || !pMapData->CanPet)
		{
			return false;
		}
		SPetItem* pPet = _petManager.GetPetByIndex( nIndex );
		if (!pPet)
		{
			return false;
		}
		//////////////////////
		if ( /*pPet->baseInfo.duration*/ GetCharInfo().otherdata.PetDuration== 0 )
		{ 
			MsgAckResult msg;
			msg.result = ER_LifeNotActivePet;
			GettheServer().SendMsgToSingle( &msg, this );
			return false; 
		}

		//??????????????   by liaojie 11.21
		/*if ( pPet->baseInfo.loyalty < 60 )
		{ 
			MsgAckResult msg;
			msg.result = ER_LoyaltyNotActivePet;
			GettheServer().SendMsgToSingle( &msg, this );
			return false; 
		}*/

		//????????????
		/*if ( pPet->baseInfo.regenerateTime > HQ_TimeGetTime() )
		{ 
			int nSecond = (pPet->baseInfo.regenerateTime - HQ_TimeGetTime()) / ONE_SEC ;
			MsgAckResult msg;
			msg.result = ER_PetRegenerateTime;
			msg.value  = nSecond ;
			GettheServer().SendMsgToSingle( &msg, this );
			return false; 
		}*/

		//????????????????????
		_petManager.LostActivePetMonster()   ;
		//_petManager.ClearPassiveSkillAffect();

		int nResult = _petManager.ProcessSetPetActive( nIndex );
		if ( RESULT_FAILED( nResult ) )
		{   
			MsgAckResult msg;
			msg.result = nResult;
			GettheServer().SendMsgToSingle( &msg, this );
			return false;
		}
		MsgChangePet changeAck;
		changeAck.header.stID = GetID();
		changeAck.ucOpType    = MsgChangePet::EOT_Active;
		changeAck.nIndex      = nIndex;
		changeAck.guid        = pPet->GetPetGuid();
		//??????????????????????????????????????????????????????????????????
		//SPetItem* pPetActive = _petManager.GetActivePet();
		//if (pPetActive)
		//{
		//	for (int indexSkill=0; indexSkill<pPetActive->skillInfo.GetCurrentSkillCount(); indexSkill++)
		//	{
		//		ItemDefine::SItemSkill* pPetSkill = GettheItemDetail().GetSkillByID( pPetActive->skillInfo.skills[indexSkill].ustSkillID, pPetActive->skillInfo.skills[indexSkill].stSkillLevel );
		//		if(pPetSkill && pPetSkill->petSkillCategory==EPetSkillCategory_Aptitude && pPetSkill->stGeneralType==ItemDefine::generaltype_passive)
		//		{
		//			//??????????????????????????????????????
		//			ApplyPetAttrToChar(pPetSkill,false);
		//		}
		//	}
		//}
		//////////////////////////////////////////////////////////////////////
		GettheServer().SendMsgToSingle( &changeAck, this );
	}
	return true;
}

bool GamePlayer::AddSkillToFristMount( uint16 skillId, uint8 level )
{
    SMountItem* pMount = _mountManager.GetMountByIndex( 0 );
    if ( pMount == NULL )
    { return false; }

    if (_mountManager.GetMountCount() != 1)
    { return false; }

    pMount->skillInfo.initiativeSkillNumber = NUMERIC_ONE;
    pMount->skillInfo.AddSkill( skillId, level, SMountItem::MICD_InitiativeSkillIndex );

    MsgUpdateMount msg;
    msg.header.stID = GetID();
    msg.mount       = *pMount;
    GettheServer().SendMsgToSingle(&msg,this);
    return true;
}

bool GamePlayer::DoRideFristMount()
{
    SMountItem* pMount = _mountManager.GetMountByIndex( 0 );
    if ( pMount == NULL )
    { return false; }

    /*if (_mountManager.GetMountCount() != 1)
    { return false; }*/

    //????????????????????
    _mountManager.ClearPassiveSkillAffect();

    int nResult = _mountManager.SetMountActiveStatus( 0, true );
    if ( RESULT_FAILED( nResult ))
    { return false; }

    MsgChangeDrome changedrome;
    changedrome.header.stID = GetID();
    changedrome.ucOpType    = MsgChangeDrome::EOT_Active;
    changedrome.nIndex      = 0;
    changedrome.guid        = pMount->GetMountGuid();
    GettheServer().SendMsgToSingle( &changedrome, this );

    _mountManager.ClearPassiveSkillAffect();
    _mountManager.UpdateMountHP( 0 );
    _mountManager.UpdateActiveSkillBag();
    _mountManager.ApplyMountAttributeToChar( false, true );
    
    DoRide( pMount->GetMountID() );

    return true;
}

unsigned short GamePlayer::GetSkillExpForSkillLevel(unsigned short ustSkillID)
{
    SCharSkill* pskill = _SkillBag.GetSkillByID(ustSkillID);
    if (pskill)
        return pskill->stSkillLevel;
    return 0;
}

void GamePlayer::SetSkillExpToSkill(DWORD dwSkillExp,unsigned short ustSkillID)
{
    /*for (int n = 0; n < More_iMaxSkillKnown;n++)
    {
    if (gCharInfoServer.otherdata.skills.status[n].ustSkillID == ustSkillID)
    {
    gCharInfoServer.otherdata.skills.status[n].dwCurSkillExp = dwSkillExp;
    break;
    }        
    }*/
    SCharSkill* pskill = _SkillBag.GetSkillByID(ustSkillID);
    if (pskill)
    {
        pskill->dwCurSkillExp = dwSkillExp;
    }    
}

DWORD GamePlayer::GetSkillExpToSkill(unsigned short ustSkillID)
{
    //for (int n = 0; n < More_iMaxSkillKnown;n++)
    //{
    //    if (gCharInfoServer.otherdata.skills.status[n].ustSkillID == ustSkillID)
    //    {
    //        return gCharInfoServer.otherdata.skills.status[n].dwCurSkillExp;
    //    }        
    //}
    SCharSkill* pskill = _SkillBag.GetSkillByID(ustSkillID);
    if (pskill)
    {
        return pskill->dwCurSkillExp;
    }
    return 0;
}

void GamePlayer::GuardExpError()
{

    SetPlayerExp(theExpStage.GetLevelupExp(GetLevel()));
    unsigned short nSkillId = GetSkillExpForSkillID();
    LOG_MESSAGE( PLAYERLOGIC, LOG_PRIORITY_CRITICAL,"Exp exceptional %s|%d", GetCharName(), GetSkillExpToSkill(nSkillId));

}

void GamePlayer::EnterGameServerLog( char* szMacAddress )
{
    ClearEspecialItemCounter();
    Log( theXmlString.GetString(eLog_FirstEnterWord), GetIp(), szMacAddress );

    LogCharData( false );
    LogForBagItem(BT_NormalItemBag, gCharInfoServer.itemData.stPackItems,     GetNormalBagSize(),  true);
    LogForBagItem(BT_MaterialBag, gCharInfoServer.itemData.ciMaterialItems, GetMaterialBagSize(),true);

    LogForPlayerVisual(gCharInfoServer.visual.GetVisualArray());    
    LogOtherBagItem(&gCharInfoServer.otherdata,true);
    LogStorage();
    LogMountData();
    LogEspecialItemCounter();
}

void GamePlayer::ExitGameServerLog()
{
    ClearEspecialItemCounter();
    LogCharData( true );
    LogBagItemByExit( BT_NormalItemBag, gCharInfoServer.itemData.stPackItems, GetNormalBagSize());
    LogBagItemByExit( BT_MaterialBag, gCharInfoServer.itemData.ciMaterialItems, GetMaterialBagSize());
    LogForPlayerVisualByExit( gCharInfoServer.visual.GetVisualArray() );
    LogOtherBagItem( &gCharInfoServer.otherdata, false );
    LogStorage();
    LogMountData();
    LogEspecialItemCounter();
    _buffManager.LogStatus();
}

void GamePlayer::LogCharData( bool bExit /* = true */ )
{
    if ( bExit )
    {
        Log( theXmlString.GetString(eLog_info_2slk_163), GetMoney(), _StorageBag.dwStorageMoney, GetJinDing() );
    }
    else        // ????????
    {
        Log( theXmlString.GetString(eLog_info_2slk_81), GetMoney(), _StorageBag.dwStorageMoney, GetJinDing() );
    }
	Log(theXmlString.GetString(eServerLog_RoleShengWang),gCharInfoServer.baseinfo.liveinfo.reputation);
	Log( theXmlString.GetString(eServerLog_RoleLevJingyan), GetLevel(), GetPlayerExp(),GetPlayerExpUnUsed() );

    //Log("???????? ????%u", gCharInfoServer.baseinfo.liveinfo.reputation );
   // Log( "????????%d, ????%I64u,??????????%I64u", GetLevel(), GetPlayerExp(),GetPlayerExpUnUsed() );
}

void GamePlayer::LogForBagItem(int nBagType, SCharItem *pPackItem, int iBagSize,bool bIsDbCome)
{
    if ( pPackItem == NULL )
    { return; }

    bool bLogItemInfoHeader = false;  // ????Log,????????????????????
    if (nBagType == BT_MaterialBag)
    {
        Log(theXmlString.GetString(eLog_EnterWorld_Material_Bag_Begin));
    }
    else if (nBagType == BT_NormalItemBag)
    {
        Log(theXmlString.GetString(eLog_EnterWorld_Normal_Bag_Begin));
    }

    for (int n = 0; n< iBagSize; ++n)
    {
        if ( pPackItem[n].itembaseinfo.ustItemID == InvalidLogicNumber )
        { continue; }

        ItemDefine::SItemCommon* pItem = GettheItemDetail().GetItemByID( pPackItem[n].itembaseinfo.ustItemID);
        if ( pItem == NULL )
        { continue; }

        bool bIsHaveSpecial = false;
        char szID[40];
        char szSpecialsIDLogOut[128];
        char szSpecialsIDTemp  [16];
        char szRandIDLogOut    [128];

        AddEspecialItemCounter( pPackItem[n].itembaseinfo.ustItemID, pPackItem[n].itembaseinfo.ustItemCount );

        if ( pItem->IsCanEquip() )
        {
            sprintf_s( szSpecialsIDLogOut,sizeof(szSpecialsIDLogOut)-1, "SpecialID:" );
            sprintf_s( szRandIDLogOut,    sizeof(szRandIDLogOut)-1,     "RandId:"    );
            if (pPackItem[n].equipdata.gemHoleCount > 0 && pPackItem[n].equipdata.gemHoleCount < SCharItem::EConstDefine_GemHoleMaxCount)   //?????????? > 0 && < 4 
            {
                for (int nloop = 0; nloop < pPackItem[n].equipdata.gemHoleCount; ++nloop)
                {
                    uint16 id = pPackItem[n].equipdata.gemIds[nloop];
                    if ( id == InvalidLogicNumber )
                    { continue; }

                    ItemDefine::SItemGem* pGem = (ItemDefine::SItemGem *)GettheItemDetail().GetItemByID( id );
                    if ( pGem == NULL )
                    { continue; }

                    sprintf_s(szSpecialsIDTemp,sizeof(szSpecialsIDTemp)-1,"%d;",id );
                    HelperFunc::AddNCpy(szSpecialsIDLogOut,szSpecialsIDTemp, sizeof(szSpecialsIDLogOut));
                    bIsHaveSpecial = true;
                }
            }

            for (int m = 0; m < SCharItem::EConstDefine_BaseRandMaxCount;m++)
            {
                ItemDefine::SRandAttribute* pRandAttribute = GettheItemDetail().GetRandByID(pPackItem[n].equipdata.baseRands[m]);
                if ( pRandAttribute == NULL )
                { continue; }

                sprintf_s(szSpecialsIDTemp,sizeof(szSpecialsIDTemp)-1,"%d;",pPackItem[n].equipdata.baseRands[m]);
                HelperFunc::AddNCpy(szRandIDLogOut,szSpecialsIDTemp, sizeof(szRandIDLogOut));
                bIsHaveSpecial = true;
            }

            HelperFunc::AddNCpy(szSpecialsIDLogOut,szRandIDLogOut, sizeof(szSpecialsIDLogOut));
        }

        if (bIsHaveSpecial)
        {
            if (bIsDbCome)
            {
                Log(theXmlString.GetString(eLog_info_2slk_107), pItem->GetItemName(), pItem->ustItemID, BigInt2String(pPackItem[n].itembaseinfo.nOnlyInt, szID),
                    pPackItem[n].itembaseinfo.ustItemCount, n, szSpecialsIDLogOut);
            }
            else
            {
                if (!bLogItemInfoHeader)
                {
                    Log(theXmlString.GetString(eLog_EnterWorld_DB_Begin));
                    bLogItemInfoHeader = true;
                }
                Log(theXmlString.GetString(eLog_info_2slk_108), pItem->GetItemName(), pItem->ustItemID, BigInt2String(pPackItem[n].itembaseinfo.nOnlyInt, szID),
                    pPackItem[n].itembaseinfo.ustItemCount, szSpecialsIDLogOut);
            }
        }
        else
        {
            if (bIsDbCome)
            {
                Log(theXmlString.GetString(eLog_info_2slk_107), pItem->GetItemName(), pItem->ustItemID, BigInt2String(pPackItem[n].itembaseinfo.nOnlyInt, szID), 
                    pPackItem[n].itembaseinfo.ustItemCount, n, " ");
            }
            else
            {
                if (!bLogItemInfoHeader)
                {
                    Log(theXmlString.GetString(eLog_EnterWorld_DB_Begin));
                    bLogItemInfoHeader = true;
                }
                Log(theXmlString.GetString(eLog_info_2slk_108), pItem->GetItemName(), pItem->ustItemID, BigInt2String(pPackItem[n].itembaseinfo.nOnlyInt, szID),
                    pPackItem[n].itembaseinfo.ustItemCount, " ");
            }
        }
    }

    if (bIsDbCome)
    {
        // ????????????????????????
        if (nBagType == BT_MaterialBag)
        {
            Log(theXmlString.GetString(eLog_EnterWorld_Material_Bag_End));
        }
        else if (nBagType == BT_NormalItemBag)
        {
            Log(theXmlString.GetString(eLog_EnterWorld_Normal_Bag_End));
        }
    }
    else
    {
        Log(theXmlString.GetString(eLog_EnterWorld_DB_End));
    }
}

void GamePlayer::LogBagItemByExit(int nBagType, SCharItem *pPackItem, int iBagSize)
{
    if ( pPackItem == NULL )
    { return; }

    // ????????????????????????????????
    // ????????????????Log????
    if (nBagType == BT_MaterialBag)
    {
        Log(theXmlString.GetString(eLog_ExitWorld_Material_Bag_Begin));
    }
    else if (nBagType == BT_NormalItemBag)
    {
        Log(theXmlString.GetString(eLog_ExitWorld_Normal_Bag_Begin));
    }

    for (int m = 0; m< iBagSize; ++m)
    {
        if ( pPackItem[m].itembaseinfo.ustItemID == InvalidLogicNumber)
        { continue; }

        ItemDefine::SItemCommon* pItem = GettheItemDetail().GetItemByID( pPackItem[m].itembaseinfo.ustItemID );
        if ( pItem == NULL )
        { continue; }

        char szID[40]                 = { 0 };
        char  szSpecialsIDLogOut[128] = { 0 };
        char  szSpecialsIDTemp[16]    = { 0 };
        char  szRandIDLogOut[128]     = { 0 };

        AddEspecialItemCounter( pPackItem[m].itembaseinfo.ustItemID, pPackItem[m].itembaseinfo.ustItemCount );

        if ( pItem->IsCanEquip() )
        {            
            sprintf_s(szSpecialsIDLogOut,sizeof(szSpecialsIDLogOut)-1,"SpecialID:");
            sprintf_s(szRandIDLogOut,sizeof(szRandIDLogOut)-1,"RandID:");
            if (pPackItem[m].equipdata.gemHoleCount > 0 && pPackItem[m].equipdata.gemHoleCount < SCharItem::EConstDefine_GemHoleMaxCount)   //?????????? > 0 && < 4 
            {
                for (int nloop = 0; nloop < pPackItem[m].equipdata.gemHoleCount; ++nloop)
                {
                    uint16 id = pPackItem[m].equipdata.gemIds[nloop];
                    if ( id == InvalidLogicNumber )
                    { continue; }

                    ItemDefine::SItemGem *pGem =  (ItemDefine::SItemGem *)GettheItemDetail().GetItemByID( id );
                    if ( pGem == NULL )
                    { continue; }

                    sprintf_s(szSpecialsIDTemp,sizeof(szSpecialsIDTemp)-1,"%d;", id );
                    HelperFunc::AddNCpy(szSpecialsIDLogOut,szSpecialsIDTemp, sizeof(szSpecialsIDLogOut));
                }
            }

            for ( int ml = 0; ml < SCharItem::EConstDefine_BaseRandMaxCount; ++ml )
            {
                ItemDefine::SRandAttribute* pRandAttribute = GettheItemDetail().GetRandByID(pPackItem[m].equipdata.baseRands[ml]);
                if ( pRandAttribute == NULL )
                { continue; }

                sprintf_s(szSpecialsIDTemp,sizeof(szSpecialsIDTemp)-1,"%d;",pPackItem[m].equipdata.baseRands[ml]);
                HelperFunc::AddNCpy(szRandIDLogOut,szSpecialsIDTemp, sizeof(szRandIDLogOut));
            }

            HelperFunc::AddNCpy( szSpecialsIDLogOut,szRandIDLogOut, sizeof(szSpecialsIDLogOut) );
        }

        Log(theXmlString.GetString(eLog_info_2slk_164),  pItem->GetItemName(), pItem->ustItemID, BigInt2String(pPackItem[m].itembaseinfo.nOnlyInt, szID), pPackItem[m].itembaseinfo.ustItemCount, m, szSpecialsIDLogOut);
    }
    // ????????????
    if (nBagType == BT_MaterialBag)
    {
        Log(theXmlString.GetString(eLog_ExitWorld_Material_Bag_End));
    }
    else if (nBagType == BT_NormalItemBag)
    {
        Log(theXmlString.GetString(eLog_ExitWorld_Normal_Bag_End));
    }
}

void GamePlayer::GetBirthday( int *pYear, int *pMonth, int *pDay )
{
    if ( pYear )
    {
        *pYear = gCharInfoServer.baseinfo.aptotic.byYear;
    }
    if ( pMonth )
    {
        *pMonth = gCharInfoServer.baseinfo.aptotic.byMonth;
    }
    if ( pDay )
    {
        *pDay = gCharInfoServer.baseinfo.aptotic.byDay;
    }
}

//BOOL GamePlayer::IsInPKDisableZone()
//{
//
//    return m_bInPKDisableZone;
//
//}
//
//void GamePlayer::SetInPKDisableZone( BOOL bInPKDisableZone/*, int nZoneID*/ )
//{
//    m_bInPKDisableZone = bInPKDisableZone;
//}

//void GamePlayer::SetInFreePKZone(bool bFlag)
//{
//
//    m_bInFreePKZone = bFlag;
//
//}
//
//bool GamePlayer::IsInFreePKZone()
//{
//
//    return m_bInFreePKZone;
//
//}

void GamePlayer::AddCharToFirstList(GameObjectId shCharID)
{
    MsgAddFirstList add;
    add.shCharID = shCharID;
    GettheServer().SendMsgToSingle(&add, this);
}

// bool GamePlayer::IsInPrivateShopZone()
// {
// 
//     return m_bInPrivateShopZone;        
// }
// 
// void GamePlayer::SetInPrivateShopZone( bool bInPrivateShopZone )
// {
//     m_bInPrivateShopZone = bInPrivateShopZone;
// 
// }

void GamePlayer::RemoveCharToFirstList(GameObjectId shCharID)
{
    MsgRemoveFirstList remove;
    remove.shCharID = shCharID;
    GettheServer().SendMsgToSingle(&remove, this);
}

short GamePlayer::IsSkillCanUse(BaseCharacter *pDst, int skillId, int skillLevel)
{    
    ItemDefine::SItemSkill* pSkill = GettheItemDetail().GetSkillByID(skillId, skillLevel);    
    if ( pSkill == NULL )
    { return MsgUseSkillHintMessage::eServerCannotFindSkill; }

    if (GetNormalAttackSkillId(m_iAttackHand) == skillId)
    {
        if( m_ExtendStatus.IsCannotNormalAttack() || !m_ExtendStatus.IsCannotNormalAttackDone() )
        {  return MsgUseSkillHintMessage::eSkillIsInCoolDown;  }
    }

    SkillBag* pSkillBag =  GetSkillBagBySkill( pSkill );

    if ( pSkillBag == NULL )
    { return MsgUseSkillHintMessage::eServerCannotFindSkill; }

    SCharSkill* pCharSkill = pSkillBag->GetSkillByID(skillId);;
    if ( pCharSkill == NULL  )     // ??????????????????????????????( ???????????? )
    { return MsgUseSkillHintMessage::eServerCannotFindSkill; }

    if ( pSkill->specialSkillType == ItemDefine::ESST_Normal )
    {
        if ( pCharSkill->stSkillLevel < skillLevel )
        { return MsgUseSkillHintMessage::eServerCannotFindSkill; }
    }
    else if ( pSkill->specialSkillType > ItemDefine::ESST_Normal && pSkill->specialSkillType < ItemDefine::ESST_SuitMax )      // ????????
    {
		if ( pCharSkill->stSkillLevel < skillLevel )
        { return MsgUseSkillHintMessage::eServerCannotFindSkill; }
       /* if ( !_suitManager.IsSuitHaveSkill( skillId, skillLevel ) )
        { return MsgUseSkillHintMessage::eSuitNoRight; }*/
    }
    else if ( pSkill->specialSkillType >= ItemDefine::ESST_Team && pSkill->specialSkillType < ItemDefine::ESST_TeamMax )      // ????????
    {
        if ( pCharSkill->stSkillLevel < skillLevel )
        { return MsgUseSkillHintMessage::eServerCannotFindSkill; }

        GameTeam* pTeam = theGameTeamManager.GetTeam( GetTeamID() );
        if ( pTeam == NULL )
        { return MsgUseSkillHintMessage::eTeamSkillCanNotUse; }

        unsigned char uchResult = pTeam->CheckTeamSkillCanUse( this, skillId, skillLevel );
        switch ( uchResult )
        {
        case TeamDefine::SkillCanNotUse:
            return MsgUseSkillHintMessage::eTeamSkillCanNotUse;
            break;
        case TeamDefine::SkillCoolDown:
            return MsgUseSkillHintMessage::eTeamSkillInCoolDown;
            break;
        }
    }
    else if ( pSkill->specialSkillType == ItemDefine::ESST_XPSkill )
    {
        if ( pCharSkill->stSkillLevel < skillLevel )
        { return MsgUseSkillHintMessage::eServerCannotFindSkill; }
    }
    else if ( pSkill->specialSkillType == ItemDefine::ESST_PetActive )
    {
        // ??????????????????????????
    }
    else
    {
        return MsgUseSkillHintMessage::eServerCannotFindSkill;
    }

    if( pSkillBag->IsSkillCoolDownById( skillId ) )
    { return MsgUseSkillHintMessage::eSkillIsInCoolDown; }

    switch( pSkill->cFightStateCastType )
    {
    case ItemDefine::SCC_MustInFightState:
        {
            if ( !HaveFighteFlag( eFighting ))
                return MsgUseSkillHintMessage::eMustInFightState;
        }    
        break;
    case ItemDefine::SCC_MustOutFightState:
        {   
            if ( HaveFighteFlag( eFighting ))
                return MsgUseSkillHintMessage::eMustInFightState;
        }
        break;
    }
    // ??????????
    short sResult = BaseCharacter::IsSkillCanUse( skillId, skillLevel);
    if ( sResult != MsgUseSkillHintMessage::eNormal )
    { return sResult; }

    // ????????????
    int nHpMax = GetCharFightAttr()->hpMax.final;
    if ( nHpMax <= 0)
    { return MsgUseSkillHintMessage::eHpLimitError; }

    if ( pSkill->cHpLimitType != ItemDefine::SHT_None)
    {
        float nCurrentRate = (float)GetHP() / nHpMax;


        switch ( pSkill->cHpLimitType )
        {
        case ItemDefine::SHT_Above:
            {                
                if ( nCurrentRate < pSkill->fHpPerLimit )
                    return MsgUseSkillHintMessage::eHpLimitError;
            }
            break;
        case ItemDefine::SHT_Under:
            {
                if ( nCurrentRate > pSkill->fHpPerLimit )
                    return MsgUseSkillHintMessage::eHpLimitError;
            }
            break;
        case ItemDefine::SHT_TargetAbove:
            {               
                if ( pDst != NULL)
                {
                    int nTargetHpMax = pDst->GetCharFightAttr()->hpMax.final;
                    if ( nTargetHpMax <= 0)
                    { return MsgUseSkillHintMessage::eHpLimitError; }

                    float nTargetRate  = (float)pDst->GetHP()  / nTargetHpMax;

                    if ( nTargetRate < pSkill->fHpPerLimit )
                        return MsgUseSkillHintMessage::eHpLimitError;
                }

            }
            break;
        case ItemDefine::SHT_TargetUnder:
            {
                if ( pDst != NULL)
                {
                    int nTargetHpMax = pDst->GetCharFightAttr()->hpMax.final;
                    if ( nTargetHpMax <= 0)
                    { return MsgUseSkillHintMessage::eHpLimitError; }

                    float nTargetRate  = (float)pDst->GetHP()  / nTargetHpMax;

                    if ( nTargetRate > pSkill->fHpPerLimit )
                        return MsgUseSkillHintMessage::eHpLimitError;
                }
            }
            break;
        }
    }

    // ????????
    if ( GetXP() < pSkill->usConsumeFightPower )
    { return MsgUseSkillHintMessage::eNoEnoughFpToUseSkill; }

    if ( GetVigor() < pSkill->usConsumeVigor )
    { return MsgUseSkillHintMessage::eNotEnoughVigorToUseSkill;}

    // ??????????????????????????
    short stUseItem = pSkill->stUseItem;
    if( stUseItem != 0 && !IsHaveEquipItem( stUseItem ))
    { return MsgUseSkillHintMessage::eNoEnoughItemToUseSkill; }

    // ????????????????
    if ( pSkill->stWeaponNeed > 0 && !IsHaveWeapon( pSkill->stWeaponNeed ) )
    { return MsgUseSkillHintMessage::eNoEnoughWeaponToUseSkill; }

    if ( pSkill->needpet && !HaveSummonPet() )
    { return MsgUseSkillHintMessage::eCannotUseSkillInCurStatus;}

    //????????????
    if( pSkill->stWeaponNeed > -1 )
    {
        SCharItem* pItem = GetVisualEquipItem( EEquipPartType_Weapon );
        if ( !pItem )
        { return MsgUseSkillHintMessage::eNoEnoughWeaponToUseSkill; }

        ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID(pItem->itembaseinfo.ustItemID);
        if ( !pItemCommon)
        { return MsgUseSkillHintMessage::eNoEnoughWeaponToUseSkill; }

        if ( pItemCommon->ucItemType != ItemDefine::ITEMTYPE_WEAPON)
        { return MsgUseSkillHintMessage::eNoEnoughWeaponToUseSkill; }

        ItemDefine::SItemWeapon* pWeapon = (ItemDefine::SItemWeapon*)(pItemCommon);
        if ( !pWeapon )
        { return MsgUseSkillHintMessage::eNoEnoughWeaponToUseSkill; }
    }

    //????????????????
    if (!_buffManager.IsCanUseSkill( skillId, skillLevel))
    { return MsgUseSkillHintMessage::eCannotUseSkillInCurStatus; }

    // ????????????????????
    if (ItemDefine::generaltype_passive == pSkill->stGeneralType)
    { return MsgUseSkillHintMessage::eCannotUsePassivitySkill;   }

    return MsgUseSkillHintMessage::eNormal;
}

int GamePlayer::PushScript(SScript* p)
{       
    if ( m_lsScript.size() <= 10 )
    {
        m_lsScript.push_back( *p );
    }
    return m_lsScript.size();
}

bool GamePlayer::PopScript()
{       
    if ( m_lsScript.size() == 0 )
    { return false;}

    m_lsScript.pop_front();
    if ( m_lsScript.size() == 0 )
    { return false; }
    return true;
}

SScript* GamePlayer::GetScript()
{       
    if( m_lsScript.size() == 0 )
        return NULL;
    return &m_lsScript.front();
}

void GamePlayer::EnterMySight( BaseCharacter* pWho )
{
    // ??????????????
    char szMsgBuff[1024] = {0};

    // ????????????????????
    pWho->SendSkillStatusTo( this ); 

    if ( pWho->IsPlayer() )
    {
        GamePlayer* pGamePlayer = (GamePlayer*)pWho;

        if ( pGamePlayer->GetStatus() != CS_ONSHIP && !pGamePlayer->_mountManager.IsRideMultiMount() )
        { // ??????????Npc??????????
            GettheServer().SendMsgToSingle( pWho->FirstSightOnMe(szMsgBuff, sizeof(szMsgBuff)), this );

            // ????????
            if ( pGamePlayer->IsOpenStall() )
            { pGamePlayer->ShowStallInfo( this ); }
        }

        // ????????????
        if ( pGamePlayer->_mountManager.IsDriveMultiMount() )
        { pGamePlayer->_mountManager.SendBeCarryPlayersTo( this ); }
    }
    else if (pWho->IsMonster())
    {
        MonsterBaseEx* pMonsterBase = (MonsterBaseEx*)pWho;
        GettheServer().SendMsgToSingle( pWho->FirstSightOnMe(szMsgBuff, sizeof(szMsgBuff)), this );

        //bool bEnmity = true;
        //if ( pMonsterBase->GetObjType() == Object_MonsterBuilding || pMonsterBase->GetObjType() == Object_MonsterRoute )
        //{
        //    if ( pMonsterBase->GetFightCamp() == GetFightCamp())
        //    { bEnmity = false; }
        //}

        //if ( bEnmity )
        //{ AddEnmityList(pWho->GetID()); }
    }
    else if ( pWho->IsNpc() )
    {
        GettheServer().SendMsgToSingle( pWho->FirstSightOnMe(szMsgBuff, sizeof(szMsgBuff)), this );

        NpcBaseEx* pNpc = (NpcBaseEx*)pWho;
        pNpc->UpdateMoveRouteToPlayer( this );
        switch ( pWho->GetObjType() )
        {
        case Object_NpcShip:
            {
                NpcShipEx* pNpc = (NpcShipEx*)pWho;
                pNpc->SendBeCarryPlayersTo( this );
            }
            break;
        case Object_NpcFight:
            {
                //bool bEnmity = true;
                //if ( GetCountry() == pNpc->GetCountry() )
                //{ bEnmity = false; }

                //if ( bEnmity )
                //{ AddEnmityList( pWho->GetID() ); }
            }
        	break;
        }
    }
    else
    { // ???????? ??ItemObject ItemEffect
        GettheServer().SendMsgToSingle( pWho->FirstSightOnMe(szMsgBuff, sizeof(szMsgBuff)), this );
    }
}

void GamePlayer::ExitMySight( BaseCharacter* pWho )
{
    MsgExitMySight msg;
    msg.header.stID = pWho->GetID();    
    GettheServer().SendMsgToSingle( &msg, this );

    RemoveEnmity( pWho->GetID() );
}

void GamePlayer::OnMsgReqSkillIdToClient(unsigned short ustSkillID)
{       
    MsgREQSkillExpForSkillID ReqSkillId;
    ReqSkillId.header.stID = GetControl()->GetID();
    ReqSkillId.stSkillId = ustSkillID;
    GettheServer().SendMsgToSingle(&ReqSkillId,this);        
}

void GamePlayer::AddNormalBagNowSize(unsigned short ustNum)
{
    gCharInfoServer.baseinfo.liveinfo.ucNormalBagSize +=  ustNum;
    if (gCharInfoServer.baseinfo.liveinfo.ucNormalBagSize > ITEM_BAGMAX)
        gCharInfoServer.baseinfo.liveinfo.ucNormalBagSize = ITEM_BAGMAX;

    _NormalItemBag.CreateFromData( this, gCharInfoServer.itemData.stPackItems, GetNormalBagSize(), BT_NormalItemBag );

    MsgChangeBagSize msg;
    msg.ustCurSize    = GetNormalBagSize();
    msg.ucItemBagType = BT_NormalItemBag;
    GettheServer().SendMsgToSingle(&msg,this);
}

void GamePlayer::AddMaterialBagNowSize( unsigned short usNum )
{
    gCharInfoServer.baseinfo.liveinfo.ucMaterialBagSize +=  usNum;
    if (gCharInfoServer.baseinfo.liveinfo.ucMaterialBagSize > ITEM_BAGMATERIAL_MAX )
        gCharInfoServer.baseinfo.liveinfo.ucMaterialBagSize = ITEM_BAGMATERIAL_MAX;

    _MaterialItemBag.CreateFromData( this, gCharInfoServer.itemData.ciMaterialItems, GetMaterialBagSize(), BT_MaterialBag );

    MsgChangeBagSize msg;
    msg.ustCurSize    = GetMaterialBagSize();
    msg.ucItemBagType = BT_MaterialBag;
    GettheServer().SendMsgToSingle(&msg,this);
}

//void GamePlayer::SetPower(int nIndex,float fDamge)
//{       
//    short stPower = 0;
//    short stProfession = this->GetProfession();
//    std::string szProfession = GetSystemConfig()->GetProessionInfoFromID(stProfession)->m_strProShow;
//
//    CItemDetail::SCharModulus *pCharModulus = NULL;
//    pCharModulus = GettheItemDetail().GetCharModulusByName(szProfession.c_str());
//    if ( !pCharModulus )
//    {
//        return;
//    }
//
//    float fExact = pCharModulus->fExactAssemblePower;
//    float fAttack = pCharModulus->fAttackAssemblePower;
//    float fBeAttack = pCharModulus->fBeAttackAssemblePower;
//
//    switch(nIndex)
//    {
//    case e_Exact:
//        {
//            float fTemp = (this->GetLevel())*fExact;
//            stPower = fTemp;
//        }
//        break;
//    case e_Attack:
//        {
//            float fTemp = (this->GetLevel())*fAttack;
//            if (fTemp <= 0.0f)
//            {
//                return;
//            }
//            fTemp = fDamge/fTemp;
//
//            stPower = fTemp;
//        }
//        break;
//    case e_BeAttack:
//        {
//            float fTemp = (this->GetLevel())*fBeAttack;
//            if (fTemp <= 0.0f)
//            {
//                return;
//            }
//            fTemp = fDamge/fTemp;
//            stPower = fTemp;
//        }
//        break;
//    default:
//        break;
//    }
//
//    if (stPower > 0)
//    {
//        short stTemp = gCharInfoServer.baseinfo.liveinfo.stPower;
//        gCharInfoServer.baseinfo.liveinfo.stPower += stPower;
//        
//        if (gCharInfoServer.baseinfo.liveinfo.stPower > pCharModulus->stAssemblePower3)
//        {
//            gCharInfoServer.baseinfo.liveinfo.stPower = pCharModulus->stAssemblePower3;
//        }
//        if (gCharInfoServer.baseinfo.liveinfo.stPower > stTemp)
//        {
//            int nPowerMax = 0;
//            int nPower = 0;
//            MsgChangePower MsgPower;
//            MsgPower.header.stID = this->GetID();
//
//            if (GetPower() >= 0 && GetPower() < pCharModulus->stAssemblePower1)
//            {
//                nPower = GetPower();
//                nPowerMax = pCharModulus->stAssemblePower1;
//            }
//            else if (GetPower() >= pCharModulus->stAssemblePower1 
//                     &&GetPower() < pCharModulus->stAssemblePower2
//                     &&pCharModulus->stAssemblePower2 > pCharModulus->stAssemblePower1)
//            {
//                nPower = GetPower() - pCharModulus->stAssemblePower1;
//                nPowerMax = pCharModulus->stAssemblePower2 - pCharModulus->stAssemblePower1;
//            }
//            else if (GetPower() >= pCharModulus->stAssemblePower2 
//                &&GetPower() < pCharModulus->stAssemblePower3
//                &&pCharModulus->stAssemblePower3 > pCharModulus->stAssemblePower2)
//            {
//                nPower = GetPower() - pCharModulus->stAssemblePower2;
//                nPowerMax = pCharModulus->stAssemblePower3 - pCharModulus->stAssemblePower2;
//            }
//            else if (GetPower() == pCharModulus->stAssemblePower3
//                &&pCharModulus->stAssemblePower3 > pCharModulus->stAssemblePower2)
//            {
//                nPower = GetPower() - pCharModulus->stAssemblePower2;
//                nPowerMax = pCharModulus->stAssemblePower3 - pCharModulus->stAssemblePower2;
//            }
//            else if (GetPower() == pCharModulus->stAssemblePower3
//                &&pCharModulus->stAssemblePower3 == pCharModulus->stAssemblePower2)
//            {
//                nPowerMax = pCharModulus->stAssemblePower3;
//                nPower = GetPower();
//            }
//            
//            MsgPower.stPower = nPower;
//            MsgPower.stPowerMax = nPowerMax;
//
//            GettheServer().SendMsgToSingle(&MsgPower,(BaseCharacter*)this);
//
//            /*TellClient("POWER????????%d,??????%d",GetPower(),stTemp);*/
//
//            short stPPointTemp = GetPowerPoint();
//            this->ChangePowerAndPoint(gCharInfoServer.baseinfo.liveinfo.stPower);
//            if (GetPowerPoint() != stPPointTemp)
//            {
//                MsgChangePowerPoint MsgPPoint;
//                MsgPPoint.header.stID = this->GetID();
//
//                MsgPPoint.stPoint = GetPowerPoint();
//                MsgPPoint.stPointMax = pCharModulus->nPointMax;
//
//                GettheServer().SendMsgToSingle(&MsgPPoint,(BaseCharacter*)this);
//                /*TellClient("????????%d",GetPowerPoint());*/
//            }
//        }
//    }
//        
//}

//void GamePlayer::SetPowerPoint(int nPPoint,int nPPointMax)
//{       
//    gCharInfoServer.baseinfo.liveinfo.stPowerPoint = nPPoint;
//
//    if (gCharInfoServer.baseinfo.liveinfo.stPowerPoint > nPPointMax)
//    {
//        gCharInfoServer.baseinfo.liveinfo.stPowerPoint = nPPointMax;
//    }   
//}

//void GamePlayer::ClearPower(short stPowerMax)
//{       
//    gCharInfoServer.baseinfo.liveinfo.stPower = 0;
//
//    MsgChangePower MsgPower;
//    MsgPower.header.stID = this->GetID();
//
//    MsgPower.stPower = 0;
//    MsgPower.stPowerMax = stPowerMax;
//    GettheServer().SendMsgToSingle(&MsgPower,(BaseCharacter*)this);        
//}

//void GamePlayer::ClearPowerPoint(short stPointMax)
//{       
//    gCharInfoServer.baseinfo.liveinfo.stPowerPoint = 0;
//    MsgChangePowerPoint MsgPPoint;
//    MsgPPoint.header.stID = this->GetID();
//    MsgPPoint.stPoint = 0;
//    MsgPPoint.stPointMax = stPointMax;
//    GettheServer().SendMsgToSingle(&MsgPPoint,(BaseCharacter*)this);
//        
//}

//void GamePlayer::SetPowerCount(short stPower)
//{       
//    short stProfession = this->GetProfession();
//
//    string szProfession = GetSystemConfig()->GetProessionInfoFromID(stProfession)->m_strProShow;
//
//    CItemDetail::SCharModulus *pCharModulus = NULL;
//    pCharModulus = GettheItemDetail().GetCharModulusByName(szProfession.c_str());
//    if ( !pCharModulus )
//    {
//        GetErrorLog()->logString( "GamePlayer::SetPower() ????" );
//        return;
//    }
//
//    if (stPower > pCharModulus->stAssemblePower3)
//    {
//        stPower = pCharModulus->stAssemblePower3;
//    }
//
//    gCharInfoServer.baseinfo.liveinfo.stPower = stPower;
//
//    MsgChangePower MsgPower;
//    MsgPower.header.stID = this->GetID();
//    MsgPower.stPower = stPower;
//    MsgPower.stPowerMax = pCharModulus->stAssemblePower3;
//
//    GettheServer().SendMsgToSingle(&MsgPower,(BaseCharacter*)this);
//
//    if (stPower < pCharModulus->stAssemblePower1 )
//    {
//        ClearPowerPoint(pCharModulus->nPointMax);
//    }   
//}



void GamePlayer::LogForPlayerVisualByExit(SCharItem *pVisualItem)
{
    if (!pVisualItem)
    {
        return;
    }
    // ????????????????????Log????
    Log(theXmlString.GetString(eLog_ExitWorld_EquipInfo_Begin));
    for (int m = 0; m< EEquipPartType_MaxEquitPart; ++m)
    {
        ItemDefine::SItemCommon* pItem = GettheItemDetail().GetItemByID( pVisualItem[m].itembaseinfo.ustItemID);
        if (!pItem)
        {
            continue;
        }
        if ( pItem->IsCanEquip() )
        {
            bool bIsHaveSpecial = false;
            char szID[40];            
            char  szSpecialsIDLogOut[128];
            char  szSpecialsIDTemp[16];
            char  szRandIDLogOut[128];    
            //if (pItem->ucItemType == ItemDefine::ITEMTYPE_WEAPON||
            //    pItem->ucItemType == ItemDefine::ITEMTYPE_ARMOUR)
            {            
                sprintf_s(szSpecialsIDLogOut,sizeof(szSpecialsIDLogOut)-1,"SpecialID:");
                sprintf_s(szRandIDLogOut,sizeof(szRandIDLogOut)-1,"RandID:");
                if (pVisualItem[m].equipdata.gemHoleCount > 0)
                {
                    for (int nloop = 0; nloop < SCharItem::EConstDefine_SuitRandMaxCount; ++nloop)
                    {
                        uint16 id = pVisualItem[m].equipdata.suitRands[nloop];
                        ItemDefine::SItemGem *pGem = (ItemDefine::SItemGem *)GettheItemDetail().GetItemByID(id);
                        if (pGem)
                        {
                            sprintf_s(szSpecialsIDTemp,sizeof(szSpecialsIDTemp)-1,"%d;",id);
                            HelperFunc::AddNCpy(szSpecialsIDLogOut,szSpecialsIDTemp, sizeof(szSpecialsIDLogOut));
                            bIsHaveSpecial = true;
                        }
                    }
                }            
                for (int ml = 0; ml < SCharItem::EConstDefine_BaseRandMaxCount;ml++)
                {
                    ItemDefine::SRandAttribute *pItemWeaponRand = NULL;
                    ItemDefine::SRandAttribute *pItemArmourRand = NULL;
                    pItemWeaponRand    = GettheItemDetail().GetRandByID(pVisualItem[m].equipdata.baseRands[ml]);
                    pItemArmourRand    = GettheItemDetail().GetRandByID(pVisualItem[m].equipdata.baseRands[ml]);
                    if (pItemArmourRand||pItemWeaponRand)
                    {
                        sprintf_s(szSpecialsIDTemp,sizeof(szSpecialsIDTemp)-1,"%d;",pVisualItem[m].equipdata.baseRands[ml]);
                        HelperFunc::AddNCpy(szRandIDLogOut,szSpecialsIDTemp, sizeof(szRandIDLogOut));
                        bIsHaveSpecial = true;
                    }
                }
                HelperFunc::AddNCpy(szSpecialsIDLogOut,szRandIDLogOut, sizeof(szSpecialsIDLogOut));
            }

            Log(theXmlString.GetString(eLog_info_2slk_165), pItem->GetItemName(), pItem->ustItemID, BigInt2String(pVisualItem[m].itembaseinfo.nOnlyInt, szID), pVisualItem[m].itembaseinfo.ustItemCount);
        }
    }

    Log(theXmlString.GetString(eLog_ExitWorld_EquipInfo_End));
}
void GamePlayer::LogForPlayerVisual(SCharItem *pVisualItem)
{
    if (!pVisualItem)
    {
        return;
    }
    // ????????????????????Log????
    Log(theXmlString.GetString(eLog_EnterWorld_EquipInfo_Begin));
    for (int m = 0; m< EEquipPartType_MaxEquitPart;m++)
    {
        ItemDefine::SItemCommon* pItem = GettheItemDetail().GetItemByID( pVisualItem[m].itembaseinfo.ustItemID);
        if (!pItem)
        {
            continue;
        }
        if ( pItem->IsCanEquip() )
        {
            bool bIsHaveSpecial = false;
            char szID[40];            
            char  szSpecialsIDLogOut[128];
            char  szSpecialsIDTemp[16];
            char  szRandIDLogOut[128];    
            //if (pItem->ucItemType == ItemDefine::ITEMTYPE_WEAPON||
            //    pItem->ucItemType == ItemDefine::ITEMTYPE_ARMOUR)
            {
                sprintf_s(szSpecialsIDLogOut,sizeof(szSpecialsIDLogOut)-1,"SpecialID:");
                sprintf_s(szRandIDLogOut,sizeof(szRandIDLogOut)-1,"RandID:");
                if (pVisualItem[m].equipdata.gemHoleCount > 0)
                {
                    for (int nloop = 0; nloop < SCharItem::EConstDefine_SuitRandMaxCount; ++nloop)
                    {
                        uint16 id = pVisualItem[m].equipdata.suitRands[nloop];
                        ItemDefine::SItemGem *pGem = (ItemDefine::SItemGem *)GettheItemDetail().GetItemByID(id);
                        if (pGem)
                        {
                            sprintf_s(szSpecialsIDTemp,sizeof(szSpecialsIDTemp)-1,"%d;",id);
                            HelperFunc::AddNCpy(szSpecialsIDLogOut,szSpecialsIDTemp, sizeof(szSpecialsIDLogOut));
                            bIsHaveSpecial = true;
                        }
                    }
                }            
                for (int ml = 0; ml < SCharItem::EConstDefine_BaseRandMaxCount;ml++)
                {
                    ItemDefine::SRandAttribute *pItemWeaponRand = NULL;
                    ItemDefine::SRandAttribute *pItemArmourRand = NULL;
                    pItemWeaponRand    = GettheItemDetail().GetRandByID(pVisualItem[m].equipdata.baseRands[ml]);
                    pItemArmourRand    = GettheItemDetail().GetRandByID(pVisualItem[m].equipdata.baseRands[ml]);
                    if (pItemArmourRand||pItemWeaponRand)
                    {
                        sprintf_s(szSpecialsIDTemp,sizeof(szSpecialsIDTemp)-1,"%d;",pVisualItem[m].equipdata.baseRands[ml]);
                        HelperFunc::AddNCpy(szRandIDLogOut,szSpecialsIDTemp, sizeof(szRandIDLogOut));
                        bIsHaveSpecial = true;
                    }
                }
                HelperFunc::AddNCpy(szSpecialsIDLogOut,szRandIDLogOut, sizeof(szSpecialsIDLogOut));
            }

            Log(theXmlString.GetString(eLog_info_2slk_166), pItem->GetItemName(), pItem->ustItemID, BigInt2String(pVisualItem[m].itembaseinfo.nOnlyInt, szID), pVisualItem[m].itembaseinfo.ustItemCount );
        }
    }
    Log(theXmlString.GetString(eLog_EnterWorld_EquipInfo_End));
}
void GamePlayer::LogOtherBagItem( SCharOtherData* pOtherData, bool bIsInWorld )
{       
    if (!pOtherData)
    { return; } 
}
void GamePlayer::LogItem(SCharItem* pCharItem,int nStringIndex)
{        
    if (pCharItem)
    {
        ItemDefine::SItemCommon* pItem = NULL;
        pItem = GettheItemDetail().GetItemByID( pCharItem->itembaseinfo.ustItemID);
        if (pItem)
        {
            bool bIsHaveSpecial = false;
            char szID[40];            
            char  szSpecialsIDLogOut[128];
            char  szSpecialsIDTemp[16];
            char  szRandIDLogOut[128];    
            if (pItem->ucItemType == ItemDefine::ITEMTYPE_WEAPON||
                pItem->ucItemType == ItemDefine::ITEMTYPE_ARMOUR)
            {            
                sprintf_s(szSpecialsIDLogOut,sizeof(szSpecialsIDLogOut)-1,"SpecialID:");
                sprintf_s(szRandIDLogOut,sizeof(szRandIDLogOut)-1,"RandID:");
                if (pCharItem->equipdata.gemHoleCount > 0)
                {
                    for (int nloop = 0; nloop < SCharItem::EConstDefine_SuitRandMaxCount;nloop++)
                    {
                        uint16 id = pCharItem->equipdata.suitRands[nloop];
                        ItemDefine::SItemGem *pGem = (ItemDefine::SItemGem *)GettheItemDetail().GetItemByID(id);
                        if (pGem)
                        {
                            sprintf_s(szSpecialsIDTemp,sizeof(szSpecialsIDTemp)-1,"%d;",id);
                            HelperFunc::AddNCpy(szSpecialsIDLogOut,szSpecialsIDTemp, sizeof(szSpecialsIDLogOut));
                            bIsHaveSpecial = true;
                        }
                    }
                }            
                for (int ml = 0; ml < SCharItem::EConstDefine_BaseRandMaxCount;ml++)
                {
                    ItemDefine::SRandAttribute *pItemWeaponRand = NULL;
                    ItemDefine::SRandAttribute *pItemArmourRand = NULL;
                    pItemWeaponRand    = GettheItemDetail().GetRandByID(pCharItem->equipdata.baseRands[ml]);
                    pItemArmourRand    = GettheItemDetail().GetRandByID(pCharItem->equipdata.baseRands[ml]);
                    if (pItemArmourRand||pItemWeaponRand)
                    {
                        sprintf_s(szSpecialsIDTemp,sizeof(szSpecialsIDTemp)-1,"%d;",pCharItem->equipdata.baseRands[ml]);
                        HelperFunc::AddNCpy(szRandIDLogOut,szSpecialsIDTemp, sizeof(szRandIDLogOut));
                        bIsHaveSpecial = true;
                    }
                }
                HelperFunc::AddNCpy(szSpecialsIDLogOut,szRandIDLogOut, sizeof(szSpecialsIDLogOut));
            }
            if (bIsHaveSpecial)
            {
                Log(theXmlString.GetString(nStringIndex), 
                    pItem->GetItemName(), 
                    BigInt2String(pCharItem->itembaseinfo.nOnlyInt, szID),
                    pCharItem->itembaseinfo.ustItemCount,
                    szSpecialsIDLogOut);
            }
            else
            {
                Log(theXmlString.GetString(nStringIndex), 
                    pItem->GetItemName(), 
                    BigInt2String(pCharItem->itembaseinfo.nOnlyInt, szID),
                    pCharItem->itembaseinfo.ustItemCount," ");
            }
        }
    }   
}

void GamePlayer::LogStorage()
{
    for(int n = 0;n < STORAGE_ITEMGRID_MAX; ++n)
    {
        if ( _StorageBag.stStorageItems[n].itembaseinfo.ustItemID == InvalidLogicNumber )
        { continue; }

        ItemDefine::SItemCommon* pItem = GettheItemDetail().GetItemByID(_StorageBag.stStorageItems[n].itembaseinfo.ustItemID);
        if ( pItem == NULL )
        { continue; }

        char szLog[512]              = {0};
        bool bIsHaveSpecial          = false;
        char szID[40]                = {0};
        char szSpecialsIDLogOut[128] = {0};
        char szSpecialsIDTemp[16]    = {0};
        char szRandIDLogOut[128]     = {0};

        sprintf_s(szLog, sizeof(szLog)-1, theXmlString.GetString(eLog_info_2slk_85), pItem->GetItemName(), BigInt2String(_StorageBag.stStorageItems[n].itembaseinfo.nOnlyInt, szID),_StorageBag.stStorageItems[n].itembaseinfo.ustItemCount, n );

        AddEspecialItemCounter( _StorageBag.stStorageItems[n].itembaseinfo.ustItemID, _StorageBag.stStorageItems[n].itembaseinfo.ustItemCount );

        if ( pItem->IsCanEquip() )
        {
            sprintf_s( szSpecialsIDLogOut, sizeof(szSpecialsIDLogOut)-1, "SpecialID:" );
            sprintf_s( szRandIDLogOut,     sizeof(szRandIDLogOut)-1,     "RandID:"    );
            if (_StorageBag.stStorageItems[n].equipdata.gemHoleCount > 0)
            {
                for (int nloop = 0; nloop < SCharItem::EConstDefine_SuitRandMaxCount;nloop++)
                {
                    uint16 id = _StorageBag.stStorageItems[n].equipdata.suitRands[nloop];
                    ItemDefine::SItemGem *pGem = (ItemDefine::SItemGem *)GettheItemDetail().GetItemByID(id);
                    if (pGem)
                    {
                        sprintf_s(szSpecialsIDTemp,sizeof(szSpecialsIDTemp)-1,"%d;",id);
                        HelperFunc::AddNCpy(szSpecialsIDLogOut,szSpecialsIDTemp, sizeof(szSpecialsIDLogOut));
                        bIsHaveSpecial = true;
                    }
                }
            }

            for (int ml = 0; ml < SCharItem::EConstDefine_BaseRandMaxCount;ml++)
            {   
                ItemDefine::SRandAttribute* pRandAttribute = GettheItemDetail().GetRandByID(_StorageBag.stStorageItems[n].equipdata.baseRands[ml]);
                if ( pRandAttribute == NULL )
                { continue;}

                sprintf_s(szSpecialsIDTemp,sizeof(szSpecialsIDTemp)-1,"%d;",_StorageBag.stStorageItems[n].equipdata.baseRands[ml]);
                HelperFunc::AddNCpy(szRandIDLogOut,szSpecialsIDTemp, sizeof(szRandIDLogOut));
                bIsHaveSpecial = true;
            }

            HelperFunc::AddNCpy(szSpecialsIDLogOut,szRandIDLogOut, sizeof(szSpecialsIDLogOut));
        }

        if (bIsHaveSpecial)
        { HelperFunc::AddNCpy(szLog,szSpecialsIDLogOut, sizeof(szLog));}

        Log(szLog);
    }   
}

#define MOUNTLOG_BUFFERSIZE      511
#define MOUNTSKILLIDS_BUFFERSIZE 127
#define MOUNTSKILLID_BUFFERSIZE  15

void GamePlayer::LogMountData()
{
    char szLog[MOUNTLOG_BUFFERSIZE+1]           = {0};
    char szSkillIds[MOUNTSKILLIDS_BUFFERSIZE+1] = {0};
    char szSkillId[MOUNTSKILLID_BUFFERSIZE+1]   = {0};

    for ( int i=0; i< ITEM_MOUNT_MAXCOUNT; ++i )
    {
        SMountItem& mountItem = gCharInfoServer.itemData.miItems[i];
        if ( mountItem.baseInfo.id == InvalidLogicNumber )
        { break;}

        ItemDefine::SDrome* pMountConfig = GettheItemDetail().GetDromeByID( mountItem.baseInfo.id );

        memset( szLog,      0, sizeof(szLog)     );
        memset( szSkillIds, 0, sizeof(szSkillIds));

        if ( pMountConfig )
        { 
			sprintf_s(szLog, MOUNTLOG_BUFFERSIZE, theXmlString.GetString(eServerLog_Mount1), pMountConfig->GetName(), mountItem.baseInfo.id, mountItem.baseInfo.guid );
			//sprintf_s(szLog, MOUNTLOG_BUFFERSIZE, "????[%s:%d],[%I64u]", pMountConfig->GetName(), mountItem.baseInfo.id, mountItem.baseInfo.guid );
		}
        else
        { 
			sprintf_s(szLog, MOUNTLOG_BUFFERSIZE, theXmlString.GetString(eServerLog_Mount2), mountItem.baseInfo.id, mountItem.baseInfo.guid );
			//sprintf_s(szLog, MOUNTLOG_BUFFERSIZE, "????[%d],[%I64u]", mountItem.baseInfo.id, mountItem.baseInfo.guid ); 
		}

        sprintf_s( szSkillIds, MOUNTSKILLIDS_BUFFERSIZE, "SkillIds:");
        for ( int i=0; i<SMountItem::MICD_MaxSkillCount; ++i )
        {
            SCharSkill& charSkill = mountItem.skillInfo.skills[i];

            if ( charSkill.ustSkillID == InvalidLogicNumber)
            { break; }

            memset( szSkillId,  0, sizeof(szSkillId) );
            sprintf_s( szSkillId, MOUNTSKILLID_BUFFERSIZE, "%d", charSkill.ustSkillID);
            HelperFunc::AddNCpy( szSkillIds, szSkillId, sizeof(szSkillIds) );
        }

        HelperFunc::AddNCpy( szLog, szSkillIds, sizeof(szLog));
        Log(szLog);
    }

    for(int n = 0;n < STORAGE_MOUNTGRID_MAX; ++n)
    {
        if ( _StorageBag.xStorageMounts[n].baseInfo.id == InvalidLogicNumber )
        { continue; }

        uint16 nMountId = _StorageBag.xStorageMounts[n].baseInfo.id;

        ItemDefine::SDrome* pMountConfig = GettheItemDetail().GetDromeByID( nMountId );

        memset( szLog,      0, sizeof(szLog)     );
        memset( szSkillIds, 0, sizeof(szSkillIds));

        if ( pMountConfig )
        { 
			//sprintf_s(szLog, MOUNTLOG_BUFFERSIZE, "????????[%s:%d],[%I64u]", pMountConfig->GetName(), nMountId, _StorageBag.xStorageMounts[n].baseInfo.guid );
			sprintf_s(szLog, MOUNTLOG_BUFFERSIZE, theXmlString.GetString(eServerLog_Mount3), pMountConfig->GetName(), nMountId, _StorageBag.xStorageMounts[n].baseInfo.guid );
		}
        else
        { 
			//sprintf_s(szLog, MOUNTLOG_BUFFERSIZE, "????????[%d],[%I64u]", nMountId, _StorageBag.xStorageMounts[n].baseInfo.guid ); 
			sprintf_s(szLog, MOUNTLOG_BUFFERSIZE, theXmlString.GetString(eServerLog_Mount4), nMountId, _StorageBag.xStorageMounts[n].baseInfo.guid ); 
		}

        sprintf_s( szSkillIds, MOUNTSKILLIDS_BUFFERSIZE, "SkillIds:");
        for ( int i=0; i<SMountItem::MICD_MaxSkillCount; ++i )
        {
            SCharSkill& charSkill = _StorageBag.xStorageMounts[n].skillInfo.skills[i];

            if ( charSkill.ustSkillID == InvalidLogicNumber)
            { break; }

            memset( szSkillId,  0, sizeof(szSkillId) );
            sprintf_s( szSkillId, MOUNTSKILLID_BUFFERSIZE, "%d", charSkill.ustSkillID);
            HelperFunc::AddNCpy( szSkillIds, szSkillId, sizeof(szSkillIds) );
        }

        HelperFunc::AddNCpy( szLog, szSkillIds, sizeof(szLog));
        Log(szLog);
    }
}

//nLastTitleID = ????????id   nCurrentTitleID = ????????id  bRemoveLastAttr = ??????????????????????
bool GamePlayer::UpdateBaseAttrByTitle(bool bSendToClient, unsigned short nCurrentTitleID, unsigned short nLastTitleID /* = TitleInfo::Init_ID */, bool bRemoveLastAttr /* = true */)
{
	//????????????????????????????????
    if (nLastTitleID < TitleConfig::Init_ID && nCurrentTitleID < TitleConfig::Init_ID)
    { return false;}

    //????????????????????????title????
    if (bRemoveLastAttr && nLastTitleID > TitleConfig::Init_ID)//????????????????????????
    {
        TitleConfig::Title* pLastTitle = theTitleConfig.GetTitleByTitleID(nLastTitleID);
        if (pLastTitle == NULL)
        { 
            //Log("????????????????????\t%d\t??????????,",nLastTitleID);
			Log(theXmlString.GetString(eServerLog_RoleChenghao),nLastTitleID);
            return false;
        }   
        ItemDefine::SItemStatus* pLastStatus = GettheItemDetail().GetStatus(pLastTitle->GetStatusID(), pLastTitle->GetStatusLevel());
        if (pLastStatus != NULL)
        {   
            UpdateFightAttrByTitle(bSendToClient, pLastStatus, false);
            ApplyBaseAttrToFightAttr( false, ECustomDataPart_title, false );
        }
    }

    if (nCurrentTitleID > TitleConfig::Init_ID)
    {
        TitleConfig::Title* pCurrentTitle = theTitleConfig.GetTitleByTitleID(nCurrentTitleID);
        if (pCurrentTitle == NULL)
        {
            Log(theXmlString.GetString(eServerLog_RoleChenghao),nLastTitleID);
            return false;
        }

        ItemDefine::SItemStatus* pCurrentStatus = GettheItemDetail().GetStatus(pCurrentTitle->GetStatusID(), pCurrentTitle->GetStatusLevel());
        if (pCurrentStatus != NULL)
        {
            UpdateFightAttrByTitle(bSendToClient, pCurrentStatus, true);
            ApplyBaseAttrToFightAttr( false, ECustomDataPart_title, true );
        }
    }

    if (!bSendToClient)
    { return true; }

    MsgCharAttrChanged Change;
    Change.iChangeCount = 0;
    Change.AddAttrFloatChange( CharAttr_Strength    , GetBaseAttr(EBaseAttr_Strength    )->final);
    Change.AddAttrFloatChange( CharAttr_Stamina, GetBaseAttr(EBaseAttr_Stamina)->final);
    Change.AddAttrFloatChange( CharAttr_Agility     , GetBaseAttr(EBaseAttr_Agility     )->final);
    Change.AddAttrFloatChange( CharAttr_Intelligence, GetBaseAttr(EBaseAttr_Intelligence)->final);

    //??????????????
    if( Change.iChangeCount > 0 )
    {    
        Change.header.stID = GetID();
        Change.CaluLength();
        GettheServer().SendMsgToSingle( &Change, this );
    }

    return true;
}

bool GamePlayer::UpdateFightAttrByTitle(bool bSendToClient,ItemDefine::SItemStatus* pStatus, bool bIsAdd /* = true */)
{
    if (pStatus == NULL)
    { return false; }

	//// ????????????
 //   ClearAllBaseAttrByPart (ECustomDataPart_title);

 //   // ????????????
 //   ClearAllFightAttrByPart(ECustomDataPart_title);
	
	//?????????????????????? ?????? ???????? 
	if(bIsAdd)
	{
		//??????????????????????????????
		//????????
		for (uint8 i=0; i<EBaseAttr_MaxSize; ++i)
		{
			GetBaseAttr(i)->title    += pStatus->stAddBaseAttr[i];
			GetBaseAttr(i)->titlePer += pStatus->stAddBaseAttrPer[i];
			//????????????????????????
			ProcessCharInfo::BaseAttrEffectFightAttr( i, ECustomDataPart_title, *GetBaseAttr( i ), GetProfession(), *GetCharFightAttr() ); 
		}
		//????????
		GetCharFightAttr()->moveSpeed.title        += pStatus->fMoveSpeedChanged;                  // ??????????????????
        GetCharFightAttr()->moveSpeed.titlePer     += pStatus->nMoveSpeedPer;                      // ?????????????????? %
        GetCharFightAttr()->attackPhysics.title    += pStatus->changePhyAttack;  // ??????????
        GetCharFightAttr()->attackPhysics.titlePer += pStatus->changePhyAttackPer;                                          // ??????????%
        GetCharFightAttr()->attackMagic.title      += pStatus->changeMagAttack;    // ??????????
        GetCharFightAttr()->attackMagic.titlePer   += pStatus->changeMagAttackPer;                                          // ??????????%
        GetCharFightAttr()->defendPhysics.title    += pStatus->changeDefend[EDefendType_Physical]; // ????
        GetCharFightAttr()->defendPhysics.titlePer += pStatus->changeDefendPer[EDefendType_Physical];  // ????%
        GetCharFightAttr()->defendMagic.title      += pStatus->changeDefend[EDefendType_Magic];   // ????
        GetCharFightAttr()->defendMagic.titlePer   += pStatus->changeDefendPer[EDefendType_Magic]; // ????%
        GetCharFightAttr()->hpRestore.title        += pStatus->resumeHP;                           // ????HP????????????
        GetCharFightAttr()->hpRestore.titlePer     += pStatus->resumeHPPer;                        // ????HP????????????%
        GetCharFightAttr()->mpRestore.title        += pStatus->resumeMP;                           // ????MP????????????
        GetCharFightAttr()->mpRestore.titlePer     += pStatus->resumeMPPer;                        // ????MP????????????%
        GetCharFightAttr()->hpMax.title            += pStatus->stChanged_HPMax;                    // ??????????
        GetCharFightAttr()->hpMax.titlePer         += pStatus->changeHPMaxPer;                     // ??????????%
        GetCharFightAttr()->mpMax.title            += pStatus->stChanged_MPMax;                    // ??????????
        GetCharFightAttr()->mpMax.titlePer         += pStatus->changeMPMaxPer;                     // ??????????%
        GetCharFightAttr()->dodge.title            += pStatus->stChanged_Hedge;   // ????????
        GetCharFightAttr()->exact.title            += pStatus->stChanged_Hit;   // ????
        GetCharFightAttr()->critical.title         += pStatus->changed_Critical ; // ??????
        GetCharFightAttr()->criticalIntensity.title+= pStatus->changed_CriticalIntensity ;    // ????????
        GetCharFightAttr()->tenacity.title         += pStatus->changeTenacity ;    // ????????
        GetCharFightAttr()->breakStrike.title      += pStatus->breakStrike;           
        GetCharFightAttr()->stabStrike.title       += pStatus->stabStrike;
        GetCharFightAttr()->spiritStrike.title     += pStatus->spiritStrike;   
        GetCharFightAttr()->toxinStrike.title      += pStatus->toxinStrike;    
        GetCharFightAttr()->elementStrike.title    += pStatus->elementStrike;   
        GetCharFightAttr()->breakResist.title      += pStatus->breakResist;           
        GetCharFightAttr()->stabResist.title       += pStatus->stabResist;
        GetCharFightAttr()->spiritResist.title     += pStatus->spiritResist;   
        GetCharFightAttr()->toxinResist.title      += pStatus->toxinResist;    
        GetCharFightAttr()->elementResist.title    += pStatus->elementResist;   
        GetCharFightAttr()->attackSpeed.titlePer   += pStatus->fAttSpeedPer ;                      // ????????
	}	
	else
	{
		//????????????????????????????
		for (uint8 i=0; i<EBaseAttr_MaxSize; ++i)
		{
			GetBaseAttr(i)->title    -= pStatus->stAddBaseAttr[i];
			GetBaseAttr(i)->titlePer -= pStatus->stAddBaseAttrPer[i];
			//????????????????????????
			ProcessCharInfo::BaseAttrEffectFightAttr( i, ECustomDataPart_title, *GetBaseAttr( i ), GetProfession(), *GetCharFightAttr() ); 
		}
		//????????
		GetCharFightAttr()->moveSpeed.title        -= pStatus->fMoveSpeedChanged;                  // ??????????????????
        GetCharFightAttr()->moveSpeed.titlePer     -= pStatus->nMoveSpeedPer;                      // ?????????????????? %
        GetCharFightAttr()->attackPhysics.title    -= pStatus->changePhyAttack;  // ??????????
        GetCharFightAttr()->attackPhysics.titlePer -= pStatus->changePhyAttackPer;                                          // ??????????%
        GetCharFightAttr()->attackMagic.title      -= pStatus->changeMagAttack;    // ??????????
        GetCharFightAttr()->attackMagic.titlePer   -= pStatus->changeMagAttackPer;                                          // ??????????%
        GetCharFightAttr()->defendPhysics.title    -= pStatus->changeDefend[EDefendType_Physical]; // ????
        GetCharFightAttr()->defendPhysics.titlePer -= pStatus->changeDefendPer[EDefendType_Physical];  // ????%
        GetCharFightAttr()->defendMagic.title      -= pStatus->changeDefend[EDefendType_Magic] ;   // ????
        GetCharFightAttr()->defendMagic.titlePer   -= pStatus->changeDefendPer[EDefendType_Magic]; // ????%
        GetCharFightAttr()->hpRestore.title        -= pStatus->resumeHP;                           // ????HP????????????
        GetCharFightAttr()->hpRestore.titlePer     -= pStatus->resumeHPPer;                        // ????HP????????????%
        GetCharFightAttr()->mpRestore.title        -= pStatus->resumeMP;                           // ????MP????????????
        GetCharFightAttr()->mpRestore.titlePer     -= pStatus->resumeMPPer;                        // ????MP????????????%
        GetCharFightAttr()->hpMax.title            -= pStatus->stChanged_HPMax;                    // ??????????
        GetCharFightAttr()->hpMax.titlePer         -= pStatus->changeHPMaxPer;                     // ??????????%
        GetCharFightAttr()->mpMax.title            -= pStatus->stChanged_MPMax;                    // ??????????
        GetCharFightAttr()->mpMax.titlePer         -= pStatus->changeMPMaxPer;                     // ??????????%
        GetCharFightAttr()->dodge.title            -= pStatus->stChanged_Hedge ;   // ????????
        GetCharFightAttr()->exact.title            -= pStatus->stChanged_Hit;   // ????
        GetCharFightAttr()->critical.title         -= pStatus->changed_Critical; // ??????
        GetCharFightAttr()->criticalIntensity.title-= pStatus->changed_CriticalIntensity ;    // ????????
        GetCharFightAttr()->tenacity.title         -= pStatus->changeTenacity ;    // ????????
        GetCharFightAttr()->breakStrike.title      -= pStatus->breakStrike;           
        GetCharFightAttr()->stabStrike.title       -= pStatus->stabStrike;
        GetCharFightAttr()->spiritStrike.title     -= pStatus->spiritStrike;   
        GetCharFightAttr()->toxinStrike.title      -= pStatus->toxinStrike;    
        GetCharFightAttr()->elementStrike.title    -= pStatus->elementStrike;   
        GetCharFightAttr()->breakResist.title      -= pStatus->breakResist;           
        GetCharFightAttr()->stabResist.title       -= pStatus->stabResist;
        GetCharFightAttr()->spiritResist.title     -= pStatus->spiritResist;   
        GetCharFightAttr()->toxinResist.title      -= pStatus->toxinResist;    
        GetCharFightAttr()->elementResist.title    -= pStatus->elementResist;   
        GetCharFightAttr()->attackSpeed.titlePer   -= pStatus->fAttSpeedPer ;                      // ????????
	}
	//????????
	GetCharFightAttr()->hpMax            .UpdateFinal();
	GetCharFightAttr()->mpMax            .UpdateFinal();
	GetCharFightAttr()->attackPhysics    .UpdateFinal();
	GetCharFightAttr()->attackMagic      .UpdateFinal();
	GetCharFightAttr()->defendPhysics    .UpdateFinal();
	GetCharFightAttr()->defendMagic      .UpdateFinal();
	GetCharFightAttr()->attackSpeed      .UpdateFinal();
	GetCharFightAttr()->moveSpeed        .UpdateFinal();
	GetCharFightAttr()->hpRestore        .UpdateFinal();
	GetCharFightAttr()->mpRestore        .UpdateFinal();
	GetCharFightAttr()->exact            .UpdateFinal();
	GetCharFightAttr()->dodge            .UpdateFinal();
	GetCharFightAttr()->critical         .UpdateFinal();
	GetCharFightAttr()->tenacity         .UpdateFinal();
	GetCharFightAttr()->criticalIntensity.UpdateFinal();
	GetCharFightAttr()->backStrike       .UpdateFinal();
	GetCharFightAttr()->backStrikeResist .UpdateFinal();
	GetCharFightAttr()->breakStrike      .UpdateFinal();
	GetCharFightAttr()->stabStrike       .UpdateFinal();
	GetCharFightAttr()->elementStrike    .UpdateFinal();
	GetCharFightAttr()->toxinStrike      .UpdateFinal();
	GetCharFightAttr()->spiritStrike     .UpdateFinal();
	GetCharFightAttr()->breakResist      .UpdateFinal();
	GetCharFightAttr()->stabResist       .UpdateFinal();
	GetCharFightAttr()->elementResist    .UpdateFinal();
	GetCharFightAttr()->toxinResist      .UpdateFinal();
	GetCharFightAttr()->spiritResist     .UpdateFinal();

    if( !bSendToClient)
    { return true; }

    RecalcBaseProperty( false, BV_NotFullHp, BV_SendMessage, EWRP_Equip  );

    return true;
}

bool GamePlayer::UpdateBaseAttrByAllTitle(bool bSendToClient /* = false */)
{
    // ????????????
    ClearAllBaseAttrByPart (ECustomDataPart_title);

    // ????????????
    ClearAllFightAttrByPart(ECustomDataPart_title);

    int nTitleCount = m_xTitleEx.GetTitleCount();
    for ( int i = 0; i < nTitleCount; ++i )
    {
        TitleData* pTitleData = m_xTitleEx.GetTitleDataByIndex( i );
        if ( pTitleData == NULL ) 
        { continue; }

        TitleConfig::Title* pTitleConfig = theTitleConfig.GetTitleByTitleID( pTitleData->GetTitleID() );
        if ( pTitleConfig == NULL )
        {
            Log( theXmlString.GetString(eServerLog_RoleChenghao),pTitleData->GetTitleID() );
            continue;
        }

        ItemDefine::SItemStatus* pStatus = GettheItemDetail().GetStatus(pTitleConfig->GetStatusID(), pTitleConfig->GetStatusLevel());
        if (pStatus != NULL)
        {
            UpdateFightAttrByTitle(bSendToClient, pStatus, true);
        }
    }

    // ????????????????????
    //ApplyBaseAttrToFightAttr( true, ECustomDataPart_title );

    //for (int i = 0; i < MAX_TITLE_COUNT; ++i)
    //{
    //    short nTitleID = GetTitleListByIndex(i);
    //    if (nTitleID == TitleConfig::Init_ID) { continue; }

    //    TitleConfig::Title* pTitle = theTitleConfig.GetTitleByTitleID(nTitleID);
    //    if (pTitle != NULL)
    //    {
    //        ItemDefine::SItemStatus* pStatus = GettheItemDetail().GetStatus(pTitle->GetStatusID(), pTitle->GetStatusLevel());
    //        if (pStatus != NULL)
    //        {
    //            for (int i = 0; i < EBaseAttr_MaxSize; ++i)
    //            {
    //                SetBaseAttrTitle(i, GetCharBaseAttr(i)->title + pStatus->stAddBaseAttr[i]);
    //                UpdateBaseAttrFinal(i);
    //            }

    //            UpdateFightAttrByTitle(bSendToClient, pStatus, true);
    //        }
    //    }
    //    else
    //    {
    //        //LOG_MESSAGE(PLAYERLOGIC, LOG_PRIORITY_ERROR, "???? [%s] ????ID [%u] ??????????????????????????", GetCharName(), nTitleID);
    //        Log("????????????????????\t%d\t??????????",nTitleID);
    //    }
    //}

    int nSendMessage = BV_NotSendMessage;

    if (bSendToClient)
    {
        MsgCharAttrChanged Change;
        Change.iChangeCount = 0;

        Change.AddAttrFloatChange(CharAttr_Strength    , GetBaseAttr(EBaseAttr_Strength    )->final);
        Change.AddAttrFloatChange(CharAttr_Stamina, GetBaseAttr(EBaseAttr_Stamina)->final);
        Change.AddAttrFloatChange(CharAttr_Agility     , GetBaseAttr(EBaseAttr_Agility     )->final);
        Change.AddAttrFloatChange(CharAttr_Intelligence, GetBaseAttr(EBaseAttr_Intelligence)->final);

        //??????????????
        GameObjectId stID = GetControl()->GetID();
        if( Change.iChangeCount > 0 )
        {    
            Change.header.stID = stID;
            Change.CaluLength();
            GettheServer().SendMsgToSingle( &Change, this );
        }

        nSendMessage = BV_SendMessage;
    }    

	// Buff
	TitleConfig::Title* pTitleConfig = theTitleConfig.GetTitleByTitleID( GetCurrentTitle() );
	if ( pTitleConfig )
	{
		if ( ApplyBufferStatus( pTitleConfig->GetBuffId(), pTitleConfig->GetBuffLevel(), GetID(), SCharBuff::StatusEventType_Other, 0) == GLR_Success )
			OnBuffStatusChanged( true );
	}

	RankTitleConfig::RankTitleVector& vecTitle = theRankTitleConfig.GetRankTitleVec();
	short shCurId = gCharInfoServer.otherdata.rankTitle.shCurRankTitleId;
	if ( shCurId >= 0 && shCurId < vecTitle.size() )
	{
		if ( ApplyBufferStatus( vecTitle[shCurId].nBuffId, vecTitle[shCurId].nBuffLevel, GetID(), SCharBuff::StatusEventType_Other, 0) == GLR_Success )
			OnBuffStatusChanged( true );
	}

    return true;
}

BaseCharacter* GamePlayer::GetTargetCanUseGood( GameObjectId ustCharId, unsigned short ustTargetType, unsigned short ustItemID)
{       
    switch(ustTargetType)
    {
    case ItemDefine::eTargetMe:
        {
            if (ustCharId == GetID())
            { return this; }
            return NULL;
        }
        break;
    case ItemDefine::eTargetEnemy:
        {
            BaseCharacter* pChar = theRunTimeData.GetCharacterByID(ustCharId);
            if ( pChar == NULL )
            { return NULL; }

            if (pChar->IsMonster())
            { return pChar; }
            else if (pChar->IsPlayer())
            {
                return pChar;
                // int nType = CheckTargetType(pChar);
            }
            return NULL;
        }
        break;
    case ItemDefine::eTargetSelf:
        {            
            BaseCharacter* pChar = theRunTimeData.GetCharacterByID(ustCharId);
            if ( pChar == NULL )
            { return NULL; }

            if (pChar->IsMonster())
            { return NULL; }
            else if (pChar->IsPlayer())
            {
                GamePlayer* pGamePlayer = (GamePlayer*)pChar;
                if ( pGamePlayer == NULL )
                { return NULL; }

                uint32 nTeamIDMe = GetTeamID();
                uint32 nTeamIDTarget = pGamePlayer->GetTeamID();

                if ((nTeamIDMe != -1)&&(nTeamIDTarget != -1))
                {
                    if (nTeamIDTarget == nTeamIDMe)
                    {
                        return pChar;
                    }
                    else
                    {
                        //if (pGuildTarget&&pGuildMe)
                        //{
                        //    if (GR_LEAGUE == pGuildMe->getGuildRelation(pGuildTarget))
                        //    {
                        //        return pChar;
                        //    }
                        //    return NULL;
                        //}
                        //else
                        //    return NULL;
                    }
                }
                else
                {
                    //if (pGuildTarget&&pGuildMe)
                    //{
                    //    if (GR_LEAGUE == pGuildMe->getGuildRelation(pGuildTarget))
                    //    {
                    //        return pChar;
                    //    }
                    //    return NULL;
                    //}
                    //return NULL;
                }
            }
            return NULL;            
        }
        break;
    case ItemDefine::eTargetAll:
        {
            BaseCharacter* pChar = theRunTimeData.GetCharacterByID(ustCharId);
            if ( pChar == NULL )
            { return NULL; };

            return pChar;
        }
        break;
    }
    return NULL;
}

void GamePlayer::UpdateTitleCounter()
{
    int nCount = theTitleConfig.GetTitleCount();
    for (int i = 0; i < nCount; ++i)
    {
        TitleConfig::Title* pTitleData = theTitleConfig.GetTitleByIndex(i);
        if (pTitleData == NULL || pTitleData->IsScript()) { continue; }

        switch (pTitleData->GetConditionType())
        {
        case TitleConfig::Condition_KillEnemy: //????????????????
        case TitleConfig::Condition_Quest:     //????????????????
            if (m_xTitleEx.IsHaveTitle(pTitleData->GetID()))
            {
                //??????????,????????
                m_xTitleEx.RemoveTitleCounter(pTitleData->GetID());
            }
            else
            {
                TitleCounter* pCounter = m_xTitleEx.GetTitleCounterByTitleID(pTitleData->GetID());
                if (pCounter == NULL)
                {
                    TitleCounter xCounter;

                    xCounter.titleid    = pTitleData->GetID();
                    xCounter.type       = pTitleData->GetConditionType();
                    xCounter.value      = pTitleData->GetParameter1();
                    xCounter.count      = 0;

                    m_xTitleEx.AddTitleCounter(xCounter);
                }
            }
            break;

        default:
            break;
        }
    }
}

int GamePlayer::GetHP()
{
    return gCharInfoServer.baseinfo.liveinfo.nHp;
}

void GamePlayer::SetHP( int nHp )
{
    if ( gCharInfoServer.baseinfo.liveinfo.nHp < 0)
    { gCharInfoServer.baseinfo.liveinfo.nHp = 0; }

    if ( nHp> GetHPMax() )
    { gCharInfoServer.baseinfo.liveinfo.nHp = GetHPMax(); }
    else
    { gCharInfoServer.baseinfo.liveinfo.nHp = nHp; }

    //_OnHPChanged( 0.3f );
}

void GamePlayer::OperateHP( uint8 uchOperateType, int nValue )
{
    if ( nValue == 0 && uchOperateType != EOT_Set )
    { return; }

    switch ( uchOperateType )
    {
    case EOT_Add:
        { gCharInfoServer.baseinfo.liveinfo.nHp += nValue; }
        break;
    case EOT_Sub:
        { gCharInfoServer.baseinfo.liveinfo.nHp -= nValue; }
        break;
    case EOT_Set:
        { gCharInfoServer.baseinfo.liveinfo.nHp = nValue; }
        break;
    default:
        return;
        break;
    }

    if ( gCharInfoServer.baseinfo.liveinfo.nHp < 0)
    { gCharInfoServer.baseinfo.liveinfo.nHp = 0; }

    if ( gCharInfoServer.baseinfo.liveinfo.nHp > GetHPMax() )
    { gCharInfoServer.baseinfo.liveinfo.nHp = GetHPMax(); }
}

void GamePlayer::SetMP( int nMp )
{
    if ( gCharInfoServer.baseinfo.liveinfo.nMp < 0)
    { gCharInfoServer.baseinfo.liveinfo.nMp = 0; }

    if ( nMp> GetMPMax() )
    { gCharInfoServer.baseinfo.liveinfo.nMp = GetMPMax(); }
    else
    { gCharInfoServer.baseinfo.liveinfo.nMp = nMp; }

    _OnMPChanged( 0.3f );
}

void GamePlayer::OperateMP( uint8 uchOperateType, int nValue )
{
    if ( nValue == 0 && uchOperateType != EOT_Set )
    { return; }

    switch ( uchOperateType )
    {
    case EOT_Add:
        { gCharInfoServer.baseinfo.liveinfo.nMp += nValue; }
        break;
    case EOT_Sub:
        { gCharInfoServer.baseinfo.liveinfo.nMp -= nValue; }
        break;
    case EOT_Set:
        { gCharInfoServer.baseinfo.liveinfo.nMp = nValue; }
        break;
    default:
        return;
        break;
    }

    if ( gCharInfoServer.baseinfo.liveinfo.nMp < 0)
    { gCharInfoServer.baseinfo.liveinfo.nMp = 0; }

    if ( gCharInfoServer.baseinfo.liveinfo.nMp > GetMPMax() )
    { gCharInfoServer.baseinfo.liveinfo.nMp = GetMPMax(); }
}

int GamePlayer::GetMP()
{
    return gCharInfoServer.baseinfo.liveinfo.nMp;
}

bool GamePlayer::HasHPMaxChange()
{
    int nHpChange = GetCharFightAttr()->hpMax.final - lastFightAttr.hpMax;
    if ( nHpChange > 0 && lastFightAttr.hpMax != 0  && m_bIsStatusChangeHpMpMax )
    {
        return true;
    }

    return false;
}

bool GamePlayer::HasMPMaxChange()
{
    int nMpChange = GetCharFightAttr()->mpMax.final - lastFightAttr.mpMax;
    if ( nMpChange > 0 && lastFightAttr.mpMax != 0  && m_bIsStatusChangeHpMpMax )
    {
        return true;
    }

    return false;
}

void GamePlayer::_OnHPChanged(float underPercent )
{       
    //if ( GetHP() > 0 && GetHP() < GetHPMax()->final * underPercent )
    //{
    //    for ( int i = More_rightShortcutBegin; i < More_skillEducate; ++i )
    //    {
    //        int bagIndex = gCharInfoServer.otherdata.hotkeys.itemHotKey[i].ShortCut.BagIndex;
    //        if ( !_NormalItemBag.IsHaveItem( bagIndex ) )
    //            continue;

    //        SCharItem charItem;
    //        if ( !_NormalItemBag.GetItem( bagIndex, &charItem ) )
    //            continue;

    //        ItemDefine::SItemCommon *pItemCommon = GettheItemDetail().GetItemByID(
    //            charItem.itembaseinfo.ustItemID );
    //        if ( pItemCommon && pItemCommon->ucItemType == ItemDefine::ITEMTYPE_RESTORE )
    //        {
    //            ItemDefine::SItemRestore* pItemRestore = (ItemDefine::SItemRestore*)pItemCommon;
    //            if ( pItemRestore->bHPAuto )
    //            {
    //                MsgUseGoods msg;
    //                msg.ustItemIndex = bagIndex;
    //                msg.stDstChar = GetID();
    //                OnUseGoods( &msg );
    //                break;
    //            }
    //        }
    //    }
    //} 
}

void GamePlayer::_OnMPChanged(float underPercent )
{       
    //if ( GetMP() < GetMPMax()->final * underPercent )
    //{
    //    for ( int i = More_rightShortcutBegin; i < More_skillEducate; ++i )
    //    {
    //        int bagIndex = gCharInfoServer.otherdata.hotkeys.itemHotKey[i].ShortCut.BagIndex;
    //        if ( !_NormalItemBag.IsHaveItem( bagIndex ) )
    //            continue;

    //        SCharItem charItem;
    //        if ( !_NormalItemBag.GetItem( bagIndex, &charItem ) )
    //            continue;

    //        ItemDefine::SItemCommon *pItemCommon = GettheItemDetail().GetItemByID(
    //            charItem.itembaseinfo.ustItemID );
    //        if ( pItemCommon && pItemCommon->ucItemType == ItemDefine::ITEMTYPE_RESTORE )
    //        {
    //            ItemDefine::SItemRestore* pItemRestore = (ItemDefine::SItemRestore*)pItemCommon;
    //            if ( pItemRestore->bMPAuto )
    //            {
    //                MsgUseGoods msg;
    //                msg.ustItemIndex = bagIndex;
    //                msg.stDstChar = GetID();
    //                OnUseGoods( &msg );
    //                break;
    //            }
    //        }
    //    }
    //}
}

bool GamePlayer::UseRestoreItem( ItemDefine::SItemRestore* pRestore, int bagIndex, BaseCharacter* pTargetChar )
{       
    if ( !pTargetChar || !pRestore )
        return false;

    ItemDefine::SItemRestore tempItem = *pRestore;

    bool ret = false;
    uint32 nLeftValue = 0;      // ????????
    if ( tempItem.bHPAuto )
    {
        // ????????????????????????????????????????????

        if ( tempItem.dwAddHPOnce > 0)
        { // ????????????????
            nLeftValue = _NormalItemBag.m_pPackItem[ bagIndex ].itembaseinfo.value2;
            if ( tempItem.dwAddHPOnce > nLeftValue )
            { // ????????????????????????????
                tempItem.dwAddHP = nLeftValue;
            }
            else
            { // ??????????????????
                tempItem.dwAddHP = tempItem.dwAddHPOnce;
            }
            nLeftValue = _NormalItemBag.m_pPackItem[ bagIndex ].itembaseinfo.value2 - tempItem.dwAddHP;        // ??????????
        }
        else
        { // ????????????
            tempItem.dwAddHP = _NormalItemBag.m_pPackItem[ bagIndex ].itembaseinfo.value2;
        }
        ret = pTargetChar->UseRestoreItem( &tempItem );
        if ( ret && tempItem.dwAddHPOnce > 0 )
        {
            tempItem.dwAddHP = nLeftValue;          // ??????????tempItem. ????????????UpdateBagItem????????
        }
    }
    else if ( tempItem.bMPAuto )
    {
        // ????????????????????????????????????????????
        if ( tempItem.dwAddMPOnce > 0 )
        { // ????????????????
            nLeftValue = _NormalItemBag.m_pPackItem[ bagIndex ].itembaseinfo.value2;
            if ( tempItem.dwAddMPOnce > nLeftValue )
            { // ????????????????????????????
                tempItem.dwAddMP = nLeftValue;
            }
            else
            { // ??????????????????
                tempItem.dwAddMP = tempItem.dwAddMPOnce;
            }

            nLeftValue = _NormalItemBag.m_pPackItem[ bagIndex ].itembaseinfo.value2 - tempItem.dwAddMP;        // ??????????
        }
        else
        { // ????????????
            tempItem.dwAddMP = _NormalItemBag.m_pPackItem[ bagIndex ].itembaseinfo.value2;
        }
        ret = pTargetChar->UseRestoreItem( &tempItem );
        if ( ret && tempItem.dwAddMPOnce > 0 )
        {
            tempItem.dwAddMP = nLeftValue;          // ??????????tempItem. ????????????UseRestoreItem????????
        }
    }
    else
    {
        // ????Item??????????????????????????
        ret = pTargetChar->UseRestoreItem( &tempItem );
    }

    UpdateRestoreItemValue( &tempItem, bagIndex );
    return ret;
}

void GamePlayer::UpdateRestoreItemValue( ItemDefine::SItemRestore* pRestore, int bagIndex )
{       
    if ( pRestore->bHPAuto )
    { _NormalItemBag.m_pPackItem[bagIndex].itembaseinfo.value2 = pRestore->dwAddHP; }

    if ( pRestore->bMPAuto )
    { _NormalItemBag.m_pPackItem[bagIndex].itembaseinfo.value2 = pRestore->dwAddMP; }
}

bool GamePlayer::AddStorageItemGrid( unsigned char nValue )
{       
    unsigned char nFinal = gCharInfoServer.baseinfo.liveinfo.nStorageItemGrid + nValue;
    if ( nFinal > STORAGE_ITEMGRID_MAX )
    { return false; }

    gCharInfoServer.baseinfo.liveinfo.nStorageItemGrid = nFinal;
    ChangeAttr( CharAttr_StorageItemGrid, (short) nFinal );
    return true;
}

bool GamePlayer::AddStorageMountGrid( unsigned char nValue )
{       
    unsigned char nFinal = gCharInfoServer.baseinfo.liveinfo.nStorageMountGrid + nValue;
    if ( nFinal > STORAGE_MOUNTGRID_MAX )
    { return false; }

    gCharInfoServer.baseinfo.liveinfo.nStorageMountGrid = nFinal;
    ChangeAttr( CharAttr_StorageMountGrid, (short) nFinal );
    return true;
}


//void GamePlayer::OnMsgAckSwitchStage(const CS2GSSwitchStageAck* pMessage )
//{  
//    if ( RESULT_SUCCESS(pMessage->nResult) )
//    {
//        if ( pMessage->ucIsLocalFlyMap == BV_LocalFlyMap )
//        {
//            FlyToMapAction( pMessage->nMapId, FloatToTile(pMessage->fX), FloatToTile(pMessage->fY), pMessage->fDir );
//        }
//        else
//        {
//            m_dwEnterWorldServerTime = HQ_TimeGetTime();
//            m_dwEnterWorldClientTime = pMessage->dwTime;
//
//            // ????????????????????????????
//            GamePlayer* pPlayer = (GamePlayer*)theRunTimeData.GetGamePlayerByDBID(pMessage->nCharDBId);
//            if ( pPlayer )
//            {
//                pPlayer->OnExit( NULL ); 
//                LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "GamePlayer[%s] Exist In The Game", pPlayer->GetCharName());
//            }
//
//            DBMsgEnterWorld  msgEnterWorld;
//            msgEnterWorld.dwCharacterID            = pMessage->nCharDBId;
//            msgEnterWorld.header.stID              = GetID();
//            msgEnterWorld.accoundId              = pMessage->nAccountId; // ?????? ??????????????????
//            msgEnterWorld.stSlot                   = pMessage->stWhichSlot;
//            msgEnterWorld.nMapId                   = pMessage->nMapId;
//            msgEnterWorld.nTileX                   = FloatToTile(pMessage->fX);
//            msgEnterWorld.nTileY                   = FloatToTile(pMessage->fY);
//            msgEnterWorld.fDir                     = pMessage->fDir;
//            msgEnterWorld.ucNeedTellClientCharInfo = pMessage->ucNeedTellClientCharInfo;
//            msgEnterWorld.ucNeedUseMessageMapInfo  = pMessage->ucNeedUseMessageMapInfo;  
//            msgEnterWorld.dwTeamSessionID          = pMessage->dwTeamSessionId;
//            strncpy(msgEnterWorld.szIP, m_szLoginIP, sizeof(msgEnterWorld.szIP)-1);
//            GettheDBCon().SendMsg( &msgEnterWorld,GetLifeCode() );
//
//            SetAccountId(pMessage->nAccountId);
//
//            //DBMsgAccountState state;
//            //state.accoundId = m_dbinfo.accoundId;
//            //state.shState = DBMsgAccountState::state_play;
//            //GettheDBCon().SendMsg( &state,GetLifeCode() );
//            m_PreSaveTime = HQ_TimeGetTime();
//        }
//    }
//    else
//    {
//        switch ( GetStatus()  )
//        {
//        case CS_WAITRETURNTOCHARACTER:
//            SetStatus( CS_IDLE );
//            break;
//        }
//
//        MsgAckResult msg;
//        msg.header.stID = GetID();
//        msg.result      = pMessage->nResult;
//        GettheServer().SendMsgToSingle( &msg, this);
//
//        LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_DEBUG, "OnMsgAckSwitchStage GamePlayer[%s] CS2GSSwitchStageAck[%d]", GetCharName(), pMessage->nResult );
//    }   
//}


long GamePlayer::ApplyBufferStatus(int iStatusID, int iStatusLevel, GameObjectId iMaster, int eventType, int eventValue)
{    
    ItemDefine::SItemStatus* pStatusItem = (ItemDefine::SItemStatus *)GettheItemDetail().GetStatus(iStatusID, iStatusLevel);
    if( NULL == pStatusItem )
    { return GLR_StatusNotExist; }

    if (IsDead())
    { return GLR_InDeadNotUseStatus; }

    bool bIsCanAddStatus = true;
    BaseCharacter* pMaster = theRunTimeData.GetCharacterByID(iMaster);
    if( pMaster == NULL )
    { return GLR_StatusSourceNotExist; }

    // ????????????????????
    if ( !pStatusItem->bIsReplaceOldStatus && _buffManager.IsHaveStatus( iStatusID ) )
    { return GLR_StatusApplyFail; }

    //////////////////////////////////////////////////////////////////////////
    // ????????????
    if( !pStatusItem->bAvail && !pMaster->CheckCanAttackTarget(this) )
    { // ??????????buff
        bIsCanAddStatus = false;
    }

    //////////////////////////////////////////////////////////////////////////
    // ????Buffer
    bool bHaveNewBufferAdd = false;
    if (bIsCanAddStatus)
    {
        DWORD dwPlayerDBId = 0;
        if ( pMaster->IsPlayer())
        {
            GamePlayer* pPlayer = (GamePlayer*)pMaster;        
            dwPlayerDBId = pPlayer->GetDBCharacterID();
        }

        bool bStop = false;
        if ( pStatusItem->actionMapConfigId != InvalidLogicNumber && pStatusItem->actionMapConfigId != EctypeId2MapId(GetMapID()) )
        { bStop = true; }

        if (m_DaoxingEffect.nStatusID != iStatusID)
        {
            bHaveNewBufferAdd = _buffManager.ApplyBuff( bStop, iStatusID, iStatusLevel, iMaster, HQ_TimeGetTime(), false, 0, dwPlayerDBId, eventType, eventValue);
        }
        else
        {
            int nDurationTime = m_DaoxingEffect.nDurationTime;
            bHaveNewBufferAdd = _buffManager.ApplyBuff( bStop, iStatusID, iStatusLevel, iMaster, HQ_TimeGetTime(), false, nDurationTime, dwPlayerDBId, eventType, eventValue);
        }
    } 

    if (bHaveNewBufferAdd)
    {         
        //??????????????????????????????????
        if( pStatusItem->bIsUsingMagic )
            CancelSkill();

        if (pStatusItem->bIsClearDamgeStatus)
            _buffManager.ClearBuffByBuffIdLevel(pStatusItem->ustItemID,pStatusItem->ustLevel);

        return GLR_Success;
    }
    return GLR_StatusApplyFail;
}

void GamePlayer::OnBuffStatusChanged( bool bSendMessage  )
{
    BaseCharacter::OnBuffStatusChanged( bSendMessage );

    RecalcBaseProperty( false, BV_NotFullHp, bSendMessage ? BV_SendMessage : BV_NotSendMessage, EWRP_Status );
}

void GamePlayer::IncreaseSingleSkillExp( int nSkillExp )
{
    unsigned short ustSkillID = GetSkillExpForSkillID();
    SCharSkill* pCharSkill    = _SkillBag.GetSkillByID(ustSkillID);
    if ( !pCharSkill )
    { return; }

    // ??????????????
    unsigned short ustSkillLevel = GetSkillExpForSkillLevel(ustSkillID);

    // ????????????????
    DWORD dwCurSkillExp = GetSkillExpToSkill(ustSkillID);

    // ??????????????????
    SetSkillExpToSkill( dwCurSkillExp + nSkillExp, ustSkillID);

    ItemDefine::SItemSkill* pItemSkill = GettheItemDetail().GetSkillByID(ustSkillID,ustSkillLevel);
    if ( !pItemSkill )
        return;

    if(nSkillExp > 0 )
    {
        Log(theXmlString.GetString(eLog_info_2slk_31),pItemSkill->GetSkillName(),nSkillExp );
        Log(theXmlString.GetString(eLog_info_2slk_32),pItemSkill->GetSkillName(),dwCurSkillExp );
    }                        

    // ??????????????????
    dwCurSkillExp = GetSkillExpToSkill(ustSkillID);
    if (dwCurSkillExp >= 0)
    {
        SetSkillExpToSkill(dwCurSkillExp,ustSkillID);
        MsgSkillExpUp SkillExpUp;
        SkillExpUp.header.stID  = GetID( );
        SkillExpUp.dwSkillExp   = dwCurSkillExp;
        SkillExpUp.ustSkillID   = ustSkillID;
        SkillExpUp.stSkilllevel = ustSkillLevel;
        GettheServer().SendMsgToSingle(&SkillExpUp,this);
	//	LogPlayer(LogString::Instance().GetString(LogContent::e_AddExpCommon),dwCurSkillExp,nSkillExp,dwCurExp);
	}

    if ( ustSkillLevel < pItemSkill->ustSkillMaxLvl )
    {
        ItemDefine::SItemSkill* pNextSkill = GettheItemDetail().GetSkillByID(ustSkillID,ustSkillLevel+1);
        if ( !pNextSkill )
            return;

        if ( dwCurSkillExp >= pNextSkill->nLearnNeedExp )
		{
            OnSkillLevelUp(); // ????????
			Log(theXmlString.GetString(eServerLog_SkillUp),ustSkillLevel,GetLevel());
			//Log("????-??????[%d],????????[%d]",ustSkillLevel,GetLevel());
		}
    }
}

void GamePlayer::IncreaseTotalSkillExp( int& nSkillExp )
{
    DWORD dwSkillTotalExp = GetSkillExp();

    if ( nSkillExp > 0 )
    {
		if ( _bNeedAntiAddiction )
		{ // ??????????
			if ( enumAntiAddictionStateTired == gTransferRuntimeInfo.nAntiAddicationStatus)
			{
				nSkillExp /= 2;
			}
			else if (enumAntiAddictionStateRest == gTransferRuntimeInfo.nAntiAddicationStatus )
			{
				nSkillExp = 0;
			}
		}

        // ????????????
        if ( dwSkillTotalExp >= g_Cfg.m_nSkillExpLimt)
        {
            dwSkillTotalExp = g_Cfg.m_nSkillExpLimt;
            return;
        }

        DWORD dwSpace = g_Cfg.m_nSkillExpLimt - dwSkillTotalExp;
        if (nSkillExp > dwSpace )
        { nSkillExp = dwSpace; } 

        OperateSkillExp( EOT_Add, nSkillExp , __FUNCTION__, __LINE__ );

        //SetSkillExp( nSkillExp + dwSkillTotalExp);
    }
    //else
    //{ // ??
    //    int iSkillExp = dwSkillTotalExp + nSkillExp;
    //    if ( iSkillExp < 0)
    //        iSkillExp = 0;

    //    SetSkillExp( iSkillExp );
    //}

    if ( nSkillExp != 0 )
    { 
        ChangeAttr( CharAttr_CurGetSkillExp , nSkillExp, true);
        ChangeAttr( CharAttr_SkillExpNotUsed, GetSkillExpUnUsed(), true); 
    }
}

void GamePlayer::OnEnterFightState()
{   
    //if ( GetRideId() >= 0 && GetMoveSpeed() )
    //{ ChangeAttr( CharAttr_MoveSpeed, GetMoveSpeed() ); }

    // ??????????????????????????????????????????
    if ( g_Cfg.bAntiPluginOpen )
    { _graphicCodeManager.SetFight( true );}
}

void GamePlayer::OnOutFightState()
{
    //if ( GetRideId() >= 0)
    //{ ChangeAttr( CharAttr_MoveSpeed, GetMoveSpeed() ); }

    // ??????????????????????????????????????????
    if ( g_Cfg.bAntiPluginOpen )
    { _graphicCodeManager.SetFight( false );}
}

short GamePlayer::GetWeaponType( char cWhichHand )  
{ 
    if ( cWhichHand != EEquipPartType_Weapon )
    { return eWeaponType_Invalid; }

    SCharItem* pCharItem = GetVisualEquipItem( cWhichHand );
    if ( !pCharItem )
    { return eWeaponType_Invalid; }

    ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( pCharItem->itembaseinfo.ustItemID );
    if ( !pItemCommon || pItemCommon->ucItemType != ItemDefine::ITEMTYPE_WEAPON )
    { return eWeaponType_Invalid; }

    ItemDefine::SItemWeapon* pWeaponItem = (ItemDefine::SItemWeapon*)pItemCommon;
    if ( !pWeaponItem)
    { return eWeaponType_Invalid; }

    return pWeaponItem->stWeaponType;
}

void GamePlayer::ProcessMountAndPetWhenDeath()
{
    //??????????????????????????????????10??????????????????????????????20??
    if ( m_pBelongKiller != NULL )
    { 
        SMountItem* pMount = _mountManager.GetActiveMount();
        if ( pMount )
        {
            int activeIndex = _mountManager.GetActiveMountIndex();
            float hpDropPer = 1.0f;
            if (_buffManager.GetDeathMountHPDropPer() > 0)
            { hpDropPer = _buffManager.GetDeathMountHPDropPer() * DEF_PERCENT; }

			//????????????????????
            //if (m_pKiller->IsPlayer())
            //{ pMount->baseInfo.hp -= MOUNT_HP_DROP_KILLED_BY_PALYER * hpDropPer ; }
            //else
            //{ pMount->baseInfo.hp -= MOUNT_HP_DROP_KILLED_BY_MONSTER * hpDropPer; }

            if (pMount->baseInfo.hp  < 0)
            { pMount->baseInfo.hp = 0; }

            MsgUpdateMount msgUpdate;
            msgUpdate.header.stID = GetID();
            msgUpdate.mount = *pMount;
            GettheServer().SendMsgToSingle( &msgUpdate, this );

            if (pMount->baseInfo.hp  <= MOUNT_LOWEST_ACTIVE_HP)
            {
                MsgChangeDrome changedrome;
                changedrome.header.stID = GetID();
                changedrome.ucOpType    = MsgChangeDrome::EOT_UnActive;
                changedrome.nIndex      = activeIndex;
                GettheServer().SendMsgToSingle( &changedrome, this );

                //????????????????????
                _mountManager._activeSkillBag.SaveSkillColdTime();
                _mountManager.ClearPassiveSkillAffect   ();
                _mountManager.SetMountActiveStatus      ( activeIndex, false );
                _mountManager.ApplyMountAttributeToChar ( false, true );
            }
        }
    }

    // ?????????? ??????
    if ( _mountManager.GetActiveBeRiding() )
    {
        DebugLog("ProcessMountAndPetWhenDeath DoRide( -1 )  ");
        DoRide( -1 );      
    }

    if ( HaveProtectChar() )
    {
        BaseCharacter* pTarget = theRunTimeData.GetCharacterByID( GetProtectCharID() );
        if ( pTarget != NULL && pTarget->IsMonster() )
        {
            MonsterBaseEx* pAiChar = static_cast< MonsterBaseEx* >( pTarget );

            pAiChar->SetMasterID( InvalidGameObjectId );
        }

        ResetLostProtectCharData();
    }

    // ??????????
    if ( HaveSummonPet() )
    {
        for (int i=0;i<CharSummonPetMaxCount; ++i)
        {
            SSummonPet* pPetMonster = GetSummonPet(i);
            if ( NULL == pPetMonster )
            { continue;  }

            BaseCharacter* pTarget = theRunTimeData.GetCharacterByID( pPetMonster->petId );
            if ( pTarget != NULL )
            {
                MonsterBaseEx* pAiChar = static_cast< MonsterBaseEx* >( pTarget );
                pAiChar->SetMasterID( InvalidGameObjectId );
            }

            pPetMonster->Clear();
        }
    }

    // ??????????
    if ( HaveCapturePet() )
    {
        BaseCharacter* pTarget = theRunTimeData.GetCharacterByID( GetCapturePetId() );
        if ( pTarget != NULL )
        {
            MonsterBaseEx* pAiChar = static_cast< MonsterBaseEx* >( pTarget );
            pAiChar->SetMasterID( InvalidGameObjectId );
        }
    }	

    if ( _petManager.HaveActivePet() )
    { _petManager.LostActivePetMonster(); }
}

void GamePlayer::OnDeath()
{
    // ????????????????????		
    // ??????????????????????????????????????
	if(!m_IsCanDead)
	{
		//?????????????????? ????1????
		SetHP( 1 );
		return;
	}

	OnHandleScriptStates();//????????????????????

    switch( GetStatus() )
    {
    case CS_INTONATE:
    case CS_HOLDSKILL:
        CancelSkill();
        break;
    }
    //Log("Dead MapId:%u X:%f Y:%f", GetMapID(), GetFloatX(), GetFloatY() );
	Log(theXmlString.GetString(eServerLog_Deadmap), GetMapID(), GetFloatX(), GetFloatY() );
	//??????????????buff
	srand(time(NULL));
	int randNum = rand()%100;
	if (randNum<= theCountryConfig.GetReliveSetting().GetTrueBZRand())		//??????
	{
		m_byReliveBuff = MsgReqRelive::EAddBuff2 | MsgReqRelive::EFullHPMP | MsgReqRelive::EFreeRelive;
	}
	else if (randNum <= theCountryConfig.GetReliveSetting().GetBaoZouRand())		//????
	{
		m_byReliveBuff = MsgReqRelive::EAddBuff1 | MsgReqRelive::EFullHPMP | MsgReqRelive::EFreeRelive;
	}
	else if (randNum <= theCountryConfig.GetReliveSetting().GetFullHpMpRand())			//????
	{
		m_byReliveBuff = MsgReqRelive::EFullHPMP | MsgReqRelive::EFreeRelive;
	}
	else
	{
		m_byReliveBuff = 0;
	}
	MsgTellReliveBuff msgBuff;
	msgBuff.header.stID = GetID();
	msgBuff.byBuff = m_byReliveBuff;
	SendMessageToClient(&msgBuff);

    // ??????????????
    SetStatus( CS_DIEING );
    SetDead();
    SetHP( 0 );
    SetMP( 0 );
	
    //????????????????
    ClearEnmity( false );

    //??????????????
    MsgSawSomeoneDead msg;
    msg.header.stID = GetID();
	msg.shReliveCnt = gCharInfoServer.baseinfo.liveinfo.nFreeReliveCount;
    GettheServer().SendMsgToView( &msg, GetID(), false );

    // ????????????
    TryChangeFightState( false, eFighting, false );

    GetScriptMgr()->StartupVM( ST_CHAR_DEAD, 0, this );

	if(!g_Cfg.isOpenPetAttacter)
	{
		SPetItem * pPet = _petManager.GetActivePet();
		if(pPet)
		{
			m_DeadPetID = pPet->baseInfo.guid;
		}
		else
		{
			m_DeadPetID = 0;
		}
	}
	else
	{
		m_DeadPetID = 0;
	}

    // ????????, ??????????
    ProcessMountAndPetWhenDeath();

	if(m_DeadPetID !=0)
	{
		GetCharInfo().otherdata.nsuanimalID  = m_DeadPetID;//??????????????????
	}

    // ??????????????????
    bool bResult = _buffManager.UpdateOnDead();	
    if ( bResult )
    {
        //_buffManager.ApplyBuffsToChar( GetProfession(), GetCharBaseAttr(), GetCharFightAttr() );
        ApplyBuffStatusToCharAttr();
        SendBuffChanged( NULL );
    }

	GameTeam* pTeam = theGameTeamManager.GetTeam(GetTeamID());
    if ( pTeam != NULL )
    {
        pTeam->UpdateTeamBuffer();
    }

    m_bDeathAndWaitForRelive = true;
    m_ExtendStatus.EnterReliveTime( 1000 );
    //////////////////////////////////////////////////////////////////////////
    _graphicCodeManager.SetFight( false );  // ????????????????????false
    SetXP( 0 ); // ????????

    // ??????????????????, ??????????????????
    CampBattle* pCampBattle = theCampBattleControl.GetCampBattle( GetFightCamp(), GetMapID() ,GetCountryId());
    if ( pCampBattle != NULL )
    {
        pCampBattle->ProcessKillPlayer( m_pBelongKiller, this );
        return;
    }

	GameGuildGeneralBattleManager* pManager = static_cast<GameGuildGeneralBattleManager*>(theGameBattleControl.GetGameBattleManager(GameBattleDefine::GameBattle_Type_GuildGeneral));
	if(pManager)
	{
		GameGuildGeneralBattle* pBattle = pManager->GetGameBattleByPlayerID(GetDBCharacterID());
		if(pBattle)
		{
			pBattle->ProcessKillPlayer( m_pBelongKiller, this );
			return;
		}
	}
	

    MapConfig::MapData* pMapData = GetMapData();
    if ( pMapData == NULL )
    { return; }

    if ( pMapData->IsEctypeMap() )  // ??????????????
    {
        GameStage* pStage = theGameWorld.GetStageById( GetMapID() );
        if ( pStage != NULL )
        { pStage->RecordPlayerDeath( this ); }
    }

    // ??????????
    if ( m_pBelongKiller == NULL || !m_pBelongKiller->IsPlayer() )
    { return; }

    GamePlayer* pWhoKillMe = (GamePlayer*)m_pBelongKiller;

    // ??????????????, ????????
    TeamBattleData* pTeamBattleData = theTeamBattleManager.GetBattleDateByMapID( EctypeId2MapId( GetMapID() ) );
    if ( pTeamBattleData != NULL )
    {
        if ( pTeamBattleData->IsInBattleData( GetTeamID(), GetMapID() ) )
        {
            unsigned int dwIntegral = pTeamBattleData->UpdateKillRecord( pWhoKillMe, this );
            pTeamBattleData->UpdateBattleRecord( GetMapID(), GetTeamID(), GetDBCharacterID(), 0, 0, 1, false );
            pTeamBattleData->UpdateBattleRecord( GetMapID(), pWhoKillMe->GetTeamID(), pWhoKillMe->GetDBCharacterID(), dwIntegral, 1, 0, true );
        }
        return;
    }

    // ??????, ????????????????
    ProcessCountryBeKilledByPlayer( pWhoKillMe, pMapData->CountryID );
    /////////////////////////////////////////////////////////////////////////////////////////////
    // ??????????, ????????????
   /* switch ( pMapData->CanPk )
    {
    case MapConfig::MapData::EPKM_UnAllow_PK:
    case MapConfig::MapData::EPKM_Critical_PK:
    case MapConfig::MapData::EPKM_Allow_PK:
    case MapConfig::MapData::EPKM_Normal_PK:
        {
            // ????????, ????????
            pWhoKillMe->ProcessRelationKillPlayer( this );
            ProcessRelationKilledByPlayer( pWhoKillMe );
        }
        break;
    default:
        break;
    }*/
    /////////////////////////////////////////////////////////////////////////////////////////////
}

bool GamePlayer::IsMountFull()
{
	return _mountManager.IsMountFull();
}

int GamePlayer::AddMount( const SMountItem& xMount )
{
    int nResult = _mountManager.PushMount( xMount );
    if ( nResult == ER_Success )    
    {
        MsgGetMount msg;
        msg.header.stID = GetID();
        msg.mount       = xMount;
        msg.usResult    = ER_Success;
        GettheServer().SendMsgToSingle( &msg, this);
    }

    return nResult;
}

__int64 GamePlayer::AddMount( unsigned short usMountId )
{    
    ItemDefine::SDrome* pMount = GettheItemDetail().GetDromeByID( usMountId );
    if ( pMount == NULL ) 
    { return InvalidLogicNumber; }

    SMountItem mount;
    mount.baseInfo.id           = pMount->stId;
    mount.baseInfo.guid         = _mountManager.GetNewBigID();
    mount.baseInfo.isActive     = MountManager::AT_NotActive;
    mount.baseInfo.generation   = 0;
    mount.baseInfo.nextId       = pMount->nextGeneration;
    mount.baseInfo.quality      = pMount->quality;
    strncpy_s( mount.baseInfo.szName, sizeof(mount.baseInfo.szName), pMount->GetName(), sizeof(mount.baseInfo.szName) -1 );    

    // ????????????
    _mountManager.InitMountAttribute( mount );

    // ??????????
    _mountManager.InitMountSkill( mount );

	MsgGetMount msg;
	msg.header.stID = GetID();
	msg.mount       = mount;
	msg.usResult    = MsgGetMount::ER_Success;

    int nResult = _mountManager.PushMount( mount );
    if ( nResult != ER_Success )    
	{ msg.usResult = MsgGetMount::ER_MountFull; }

    switch( pMount->quality )
    {
    case ItemDefine::EMQ_Good:
        { _achieveManager.UpdateTriggerByValueType( EAT_GoodMount , pMount->takeLevel ); }
        break;
    case ItemDefine::EMQ_Excellent:
        { _achieveManager.UpdateTriggerByValueType( EAT_ExcellentMount , pMount->takeLevel ); }
        break;
    }

    GettheServer().SendMsgToSingle( &msg, this);
	if (msg.usResult!=MsgGetMount::ER_Success)
	{
		return 0;
	}
    return mount.GetMountGuid();
}

int GamePlayer::AddPet( const SPetItem& xPet, uint8 source )
{
    if ( _petManager.IsPetFull() )
    { return ER_Failed; }

    int nResult = _petManager.PushPet( xPet );
    if ( nResult == ER_Success )    
    {
        MsgAddUpdatePet msg;
        msg.header.stID = GetID();
        msg.type        = MsgAddUpdatePet::OT_Add;
        msg.source      = source;
        msg.pet         = xPet;
        GettheServer().SendMsgToSingle( &msg, this);
    }

    return nResult;
}

int64 GamePlayer::AddPet( int monsterId, int quality, int sex, int generation, uint8 source )
{    
    if ( _petManager.IsPetFull() )
    { 
        SendErrorToClient( ER_PetNumIsFull );
        return InvalidLogicNumber; 
    }

    ItemDefine::SPetMonster* pMonsterConfig = GettheItemDetail().GetPetById( monsterId );
    if ( pMonsterConfig == NULL ) 
    { 
        SendErrorToClient( ER_NotFoundPet );
        return InvalidLogicNumber; 
    }

    SPetItem pet;
    pet.baseInfo.petId       = pMonsterConfig->stMonsterId;
    pet.baseInfo.itemId      = pMonsterConfig->itemId ;
    pet.baseInfo.petType     = pMonsterConfig->petType;
    pet.baseInfo.guid        = _petManager.GetNewBigID();
    pet.baseInfo.isActive    = MountManager::AT_NotActive;
    pet.baseInfo.level       = pMonsterConfig->stLevel;
    pet.baseInfo.exp         = theExpStage.GetPetLevelupExp( pet.baseInfo.level - 1 ) ;
    pet.baseInfo.daoxing     = pMonsterConfig->nDaoxing;
    pet.baseInfo.hp          = pMonsterConfig->nHPMax;
    pet.baseInfo.loyalty     = PET_LOYALTY_LIMIT ;
    pet.baseInfo.duration    = pMonsterConfig->duration;
    pet.baseInfo.quality     = quality;
    pet.baseInfo.isShowGrow  = 0;
    pet.baseInfo.growStar    = thePetSettingConfig.GetGrowRateStar( pet.baseInfo.quality );
    pet.baseInfo.growRate    = pMonsterConfig->growthRate[pet.baseInfo.growStar - 1];
    pet.baseInfo.takeLevel   = pMonsterConfig->takeLevel;
    pet.baseInfo.aptitudeLevel  = thePetSettingConfig.GetAptitudeLevel( pet.baseInfo.quality );
    pet.baseInfo.sex         = sex;
    pet.baseInfo.phyle       = pMonsterConfig->phyle;
    pet.baseInfo.attackType  = pMonsterConfig->attackType;
    pet.baseInfo.generation  = generation;
    pet.baseInfo.characterize= GetRandIndex( pMonsterConfig->characterizeRate, EPetChar_Count, theRand.rand16() % RAND_NUM );
    strncpy_s( pet.baseInfo.szName, sizeof(pet.baseInfo.szName), pMonsterConfig->GetName(), sizeof(pet.baseInfo.szName) -1 );    

    if (!pMonsterConfig->bIsBaby)
    { pet.baseInfo.bone = thePetSettingConfig.GetPetBone( pMonsterConfig->catchQuality, pMonsterConfig->catchLevel ); }

    // ????????????
    _petManager.InitPetAttribute( pet );
    pet.baseInfo.hp = pet.baseInfo.GetFightAttribute(CharAttr_HPMax);

    // ??????????
    _petManager.InitPetSkill( pet );

    int nResult = _petManager.PushPet( pet );
    if ( nResult != ER_Success )    
    { return InvalidLogicNumber; }

    MsgAddUpdatePet msg;
    msg.header.stID = GetID();
    msg.type        = MsgAddUpdatePet::OT_Add;
    msg.source      = source;
    msg.pet         = pet;
    GettheServer().SendMsgToSingle( &msg, this);

    return pet.GetPetGuid();
}

bool GamePlayer::AddPetIdentify ( uint16 petType )
{
    SPetIdentify* pIdentify = GetPetIdentify( petType );
    if ( pIdentify == NULL )
    {// ???????????????? ????????
        SPetIdentify xIdentify;
        xIdentify.petType = petType;
        xIdentify.identifyTotal  = 1;
        
        MsgUpdatePetIdentify msg;
        msg.petIdentify = xIdentify;
        GettheServer().SendMsgToSingle( &msg, this );

        return gCharInfoServer.identifyData.AddPetIdentify( xIdentify );
    }
	else
	{
		MsgRepeatedlyPet msg;
		msg.petType = petType;
		GettheServer().SendMsgToSingle( &msg, this );
		return false;
	}

    std::vector< ItemDefine::SPetMonster* > vecPetMonsterList = GettheItemDetail().GetPetListByType( petType );
    ItemDefine::SPetMonster *petMonster = vecPetMonsterList[0];    // ??????????????????????????????
    if ( petMonster != NULL )
    {
        if ( pIdentify->identifyTotal < petMonster->identifyTotal )
        { pIdentify->identifyTotal += 1; }
    }

    int talentSkillId = GettheItemDetail().GetTalentSkillIdByType( petType );
    for ( int skillLv = 1; skillLv < ItemDefine::MaxLevel_Skill; ++skillLv )
    {
        ItemDefine::SItemSkill* pSkillConfig = GettheItemDetail().GetSkillByID( talentSkillId, skillLv );
        if ( pSkillConfig == NULL )
        { continue; }

        if ( pIdentify->identifyTotal >= pSkillConfig->nLearnNeedExp )
        { _petManager.UpdateTalentSkill( petType, skillLv ); }
    }

    MsgUpdatePetIdentify msg;
    msg.petIdentify = *pIdentify;
    GettheServer().SendMsgToSingle( &msg, this );

    return gCharInfoServer.identifyData.AddPetIdentify( *pIdentify );
}

ItemDefine::SItemSkill* GamePlayer::GetPetTalentSkillByType ( uint16 petType ) 
{
    int talentSkillId = GettheItemDetail().GetTalentSkillIdByType( petType );

    SPetIdentify* pIdentify = GetPetIdentify( petType );
    if ( pIdentify == NULL )
    { return GettheItemDetail().GetSkillByID( talentSkillId, 1 ); }

    for ( int skillLv = 1; skillLv < ItemDefine::MaxLevel_Skill; ++skillLv )
    {
        ItemDefine::SItemSkill* pSkillConfig = GettheItemDetail().GetSkillByID( talentSkillId, skillLv );
        if ( pSkillConfig == NULL )
        { continue; }

        if ( pIdentify->identifyTotal >= pSkillConfig->nLearnNeedExp )
        { return pSkillConfig; }
    }
    
    return GettheItemDetail().GetSkillByID( talentSkillId, 1 );
}

SPetIdentify* GamePlayer::GetPetIdentify( uint16  petType )
{
    return gCharInfoServer.identifyData.GetPetIdentify( petType );
}

void GamePlayer::SendClientSwitchGateInfo()
{ 
	unsigned int nOfflineTime = GetOfflineTime();
    if( nOfflineTime != 0)
		return;
    GettheServer().SendMsgToSingle( &_GateInfo, this);
   // Log( "???????????????????????????????? ??????????????[%s:%d]", _GateInfo.szGateIP, _GateInfo.uGatePort);
	Log( theXmlString.GetString(eServerLog_DBFlyMap), _GateInfo.szGateIP, _GateInfo.uGatePort);

    if ( GetStatus() == CS_WAITRETURNTOCHARACTER)
    { OnExit( NULL, ET_ReturnCharacterServer );}
    else
    { OnExit( NULL, ET_SwitchGameServer ); }
}

void GamePlayer::SaveCharacterToDB()
{
    DBMsgSaveCharacter save;
    save.dwCharacterID   = m_dbinfo.dwCharacterID;
    save.dwSaveTime      = HQ_TimeGetTime() - m_PreSaveTime;
    save.stPKProtectFlag = GetPKMode();
    save.nPKValue        = GetPKValue();
    m_PreSaveTime        = HQ_TimeGetTime();

    UpdateCommonData( BV_ForSaveDb );

    //RePairData(&gCharInfoServer.baseinfo);
    save.dbInfo = gCharInfoServer;    
    save.storageInfo = _StorageBag;
    save.bOpenDB = m_bStorageDBFlag;
    save.nGMLevel = m_nGMLevel;    
    save.runtimeInfo = gTransferRuntimeInfo;

    GettheDBCon().SendMsg( &save,GetLifeCode() );
}

//?????????????????????????? ????????????????,??????????????????????, ????????????????????????,????????????????
//??????????????2??????2??????????
void GamePlayer::UpdateTitleListByDataBaseTop10(bool bSendToClient /* = false */)
{
    //????????,????????????,??????????????????????
    UpdateTitleListByConditionType(TitleConfig::Condition_Money, bSendToClient); // ????????
    UpdateTitleListByConditionType(TitleConfig::Condition_Level, bSendToClient); // ????????
}    

void GamePlayer::UpdateTitleListByConditionType(short nConditionType, bool bSendToClient /* = false */)
{
    //????????????,????????????????????10
    short nIndex = GetPlayerAttrDataBaseTop10(nConditionType);
    //??????????????????????ID
    TitleData* pTitleData = m_xTitleEx.GetTimeLimitTitleByTitleType(nConditionType);
    if (nIndex == -1)           //????-1, ??????????10
    {
        //????????,????????????????,????????????
        if ( pTitleData != NULL )
        {
            m_xTitleEx.RemoveTitle( pTitleData->GetTitleID() );

            if (bSendToClient)
            {
                MsgRemoveTitleAck xAck;

                xAck.header.stID = GetID();
                xAck.nTitleID = nConditionType;
                GettheServer().SendMsgToSingle(&xAck, this); 
            }

            if ( m_xTitleEx.GetCurrentTitle() == pTitleData->GetTitleID() )
            {
                m_xTitleEx.SetCurrentTitle(TitleConfig::Init_ID);

                if (bSendToClient)
                {
                    MsgTellCurrentTitle xTell;
                    xTell.header.stID = GetID();
                    xTell.nTitleID = TitleConfig::Init_ID;
                    GettheServer().SendMsgToView(&xTell, GetID(), false);
                }          
            }

            //????????
            UpdateBaseAttrByTitle(bSendToClient, TitleConfig::Init_ID, pTitleData->GetTitleID() );
        }
    }
    else
    {
        //??????????, ??????????????,????????????,??????,???? 1 ?? 2-10 ??????????????
        TitleConfig::Title* pTitleConfig = theTitleConfig.GetTitleByConditionType(nConditionType, nIndex + 1, nIndex + 1);
        if ( pTitleConfig == NULL )
        {
            LOG_MESSAGE( PLAYERLOGIC, LOG_PRIORITY_ERROR,"????\t%d\t%d\t????????????????????!", nConditionType, nIndex + 1);
            return;
        }

        TimeEx xCurrentTime = TimeEx::GetCurrentTime();

        MsgAddTitleAck xAck;
        xAck.header.stID    = GetID();
        xAck.nTitleID       = pTitleConfig->GetID();
        xAck.n64AcquireTime = xCurrentTime.GetTime();
        xAck.nActiveTime    = pTitleConfig->GetTimeLimit() * OneHourSecond;

        if ( pTitleData == NULL )         //??????????????????
        { 
            if ( m_xTitleEx.AddTitle( pTitleConfig->GetID(), xCurrentTime.GetTime(), xAck.nActiveTime ) )
            {
                UpdateBaseAttrByTitle(bSendToClient, pTitleConfig->GetID());
            }
            else
            {
                xAck.nError = MsgAddTitleAck::Add_TitleFull;
            }

            if (bSendToClient)
            {
                GettheServer().SendMsgToSingle(&xAck, this);
            }
        }
        else            //????????????????
        {
            if ( pTitleConfig->GetID() != pTitleData->GetTitleID() )
            {
                if ( m_xTitleEx.AddTitle( pTitleConfig->GetID(), xCurrentTime.GetTime(), xAck.nActiveTime ) )
                {
                    m_xTitleEx.RemoveTitle( pTitleData->GetTitleID() );     // ????????,??????????????
                    UpdateBaseAttrByTitle( bSendToClient, pTitleConfig->GetID(), pTitleData->GetTitleID() );

                    if (bSendToClient)
                    {
                        GettheServer().SendMsgToSingle(&xAck, this);

                        //????????????????,??????????????
                        MsgRemoveTitleAck xRemove;
                        xRemove.header.stID = GetID();
                        xRemove.nTitleID = pTitleData->GetTitleID();
                        GettheServer().SendMsgToSingle(&xRemove, this);   
                    }

                    if ( m_xTitleEx.GetCurrentTitle() == pTitleData->GetTitleID() )
                    {
                        m_xTitleEx.SetCurrentTitle(pTitleConfig->GetID());

                        if (bSendToClient)
                        {
                            MsgTellCurrentTitle xTell;
                            xTell.nTitleID = pTitleConfig->GetID();
                            GetRelationNameByTitle( xTell.nTitleID, xTell.szTitleTargetName, sizeof( xTell.szTitleTargetName ) );
                            GettheServer().SendMsgToView(&xTell, GetID(), false);
                        }
                    }  
                }
            }
        }
    }
}

//??????????,????????????????????????10
short GamePlayer::GetPlayerAttrDataBaseTop10(int nType)
{
    switch (nType)
    {
    case TitleConfig::Condition_Money:
        break;

    case TitleConfig::Condition_Level:
        break;
    }

    return -1;
}

void GamePlayer::InitPlayerTitleList()
{
    m_xTitleEx.InitTitle( gCharInfoServer.baseinfo.liveinfo.xTitleData, MAX_TITLE_COUNT, true );   // ????????????????????????????
    m_xTitleEx.SetCurrentTitle( gCharInfoServer.baseinfo.liveinfo.nCurrentTitleID );

    m_xTitleEx.ChangeTitleCounterArrayToMap( gCharInfoServer.extendData.nTitleCounters, MAX_TITLE_COUNT );


    // ??????????????????, ??InitTitle????????????????????, ????????????????????????????
    // SavePlayerTitleList();       // ??InitCharacter??????, ????????????????????????, ??????????????
}

void GamePlayer::SavePlayerTitleList()
{
    gCharInfoServer.baseinfo.liveinfo.nCurrentTitleID = m_xTitleEx.GetCurrentTitle();

    memset( gCharInfoServer.baseinfo.liveinfo.xTitleData, 0, sizeof( gCharInfoServer.baseinfo.liveinfo.xTitleData ) );
    m_xTitleEx.SaveTitle( gCharInfoServer.baseinfo.liveinfo.xTitleData, MAX_TITLE_COUNT );

    memset( gCharInfoServer.extendData.nTitleCounters, 0, sizeof( gCharInfoServer.extendData.nTitleCounters ) );
    m_xTitleEx.ChangeTitleCounterMapToArray( gCharInfoServer.extendData.nTitleCounters, MAX_TITLE_COUNT );
}

void GamePlayer::RemoveTypeTitle( unsigned char uchType )
{
    std::vector< unsigned short > vecTitleID;
    m_xTitleEx.GetTypeTitle( uchType, vecTitleID );
    if ( vecTitleID.empty() )
    { return; }

    for ( std::vector< unsigned short >::iterator iter = vecTitleID.begin(); iter != vecTitleID.end(); ++iter )
    {
        RemoveTitle( *iter, false );
    }

    SendCharAttibuteToClient();
}

void GamePlayer::UpdatePlayerCounterByCount(short nConditionType, int nID)
{
    m_xTitleEx.UpdataTitleCounterByCount(this, nConditionType, nID);
}

void GamePlayer::BuildRuntimeInfo( SRuntimeInfo& runtimeInfo )
{ 
    // ????????????????
    runtimeInfo                            = gTransferRuntimeInfo;
    runtimeInfo.dwProtectLockLeaveTime     = m_nProtectLockLeaveTime; // ????????
    runtimeInfo.inFightTime                = _graphicCodeManager.GetInFightTime();
    runtimeInfo.dwOnLineTime              += GetOnLineTime();  // ????????????
    runtimeInfo.nAntiAddictionDbOnlineTime = GetAntiAddictionOnlineTime();  
    runtimeInfo.nCountrySpeakSpaceTime     = m_nCountrySpeakSpaceTime;  // ????????????????

    // ????????
    int nCount = 0;
    m_xBuyBackItem.GetPack( runtimeInfo.xBuyBackItem, nCount, sizeof( runtimeInfo.xBuyBackItem ) / sizeof( SCharItem ) );

    runtimeInfo.bForceRemove       = GetForceRemove();
    runtimeInfo.bReqRemoveMarriage = GetReqRemoveMarriage();
}

void GamePlayer::_ProcessUseRestoreItemToMount( MsgUseGoodsToMount* pUseGoodsToMount, SCharItem* pTargetItem, ItemDefine::SItemCommon* pTargetItemCommonConfig )
{
    if (pUseGoodsToMount == NULL || pTargetItem == NULL || pTargetItemCommonConfig == NULL)
    { return; }

    SMountItem* pMountItem = _mountManager.GetMountByIndex(pUseGoodsToMount->nMountIndex);
    if ( pMountItem == NULL )
    {  
        MsgAckResult msg;
        msg.header.stID = GetID();
        msg.result      = ER_NotHaveThisMount;//ER_NotActiveMount;
        GettheServer().SendMsgToSingle( &msg, this);
        return;
    }

    ItemDefine::SItemRestore* pRestore = (ItemDefine::SItemRestore*)pTargetItemCommonConfig;

    if( !m_RestoreColdDown.UseRestore( pTargetItem->itembaseinfo.ustItemID ))
    { return; }

    if ( !pRestore->bExpendable )
    { return; }

    // ?????? ??????????????????????
    if ( pRestore->specialFunction != ItemDefine::EMRIF_HuanLongShu && pRestore->specialFunction != ItemDefine::EMRIF_HuanTongShu )
    {
        if (pMountItem->baseInfo.level < pRestore->nMountUseLevel)
        { 
            MsgAckResult msg;
            msg.result = ER_MountLevelCannotUseItem;
            GettheServer().SendMsgToSingle(&msg, this);
            return; 
        }
    }

    bool bIsUsedSuccess = false;

    switch ( pRestore->specialFunction )
    {
    case ItemDefine::EMRIF_RestoreHP:
        {// ??????????????
            bIsUsedSuccess = _mountManager.AddMountHp(pUseGoodsToMount->nMountIndex, pRestore->stSubHunger);
        }
        break;
    case ItemDefine::EMRIF_AddExp:
        {
            bIsUsedSuccess = _mountManager.AddMountExp(pUseGoodsToMount->nMountIndex, pRestore->dwAddExp);
        }
        break;
    case ItemDefine::EMRIF_ResetPoint:
        {
            if ( pMountItem->IsLock() )
            {
                MsgAckResult msg;
                msg.result = ER_IsLocked;
                GettheServer().SendMsgToSingle( &msg, this );
                return; 
            }

            bIsUsedSuccess = _mountManager.ClearMountPotential(pUseGoodsToMount->nMountIndex);
        }
        break;
    case ItemDefine::EMRIF_OpenSkill:
        {
            if ( pMountItem->IsLock() )
            {
                MsgAckResult msg;
                msg.result = ER_IsLocked;
                GettheServer().SendMsgToSingle( &msg, this );
                return; 
            }

            bIsUsedSuccess = _mountManager.SetInitiativeSkill(pUseGoodsToMount->nMountIndex, pRestore->openSkillNum);
        }
        break;
    case ItemDefine::EMRIF_ForgetSkill:
        {
            if ( pMountItem->IsLock() )
            {
                MsgAckResult msg;
                msg.result = ER_IsLocked;
                GettheServer().SendMsgToSingle( &msg, this );
                return; 
            }

            bIsUsedSuccess = _mountManager.ForgetInitiativeSkill(pUseGoodsToMount->nMountIndex, pRestore->forgetSkillIndex);
        }
        break;
    case ItemDefine::EMRIF_HuanLongShu:
        {
            //TODO: ????????????
            //if ( pMountItem->IsLock() )
            //{
            //    MsgAckResult msg;
            //    msg.result = ER_IsLocked;
            //    GettheServer().SendMsgToSingle( &msg, this );
            //    return; 
            //}

            //ItemDefine::SDrome* pSelfDrome = GettheItemDetail().GetDromeByID( pMountItem->baseInfo.id );
            //if ( pSelfDrome == NULL ) 
            //{ 
            //    MsgAckResult msg;
            //    msg.result = ER_ErrorMountData;
            //    GettheServer().SendMsgToSingle(&msg,this);
            //    return; 
            //}

            //if (pSelfDrome->takeLevel < pRestore->nMountUseLevel )
            //{
            //    MsgAckResult msg;
            //    msg.result = ER_ErrorMountHuanLongShuLevel;
            //    GettheServer().SendMsgToSingle(&msg,this);
            //    return;
            //}

            //ItemDefine::SDrome* pDrome = GettheItemDetail().GetDromeByID( pMountItem->baseInfo.nextId );
            //if ( pDrome == NULL ) 
            //{ 
            //    MsgAckResult msg;
            //    msg.result = ER_MountCannotUseHuanLongShu;
            //    GettheServer().SendMsgToSingle(&msg,this);
            //    return; 
            //}

            //pMountItem->baseInfo.id           = pDrome->stId;
            //pMountItem->baseInfo.generation   = pMountItem->baseInfo.generation + 1;
            //pMountItem->baseInfo.nextId       = 0;
            //strncpy_s( pMountItem->baseInfo.szName, sizeof(pMountItem->baseInfo.szName), pDrome->GetName(), sizeof(pMountItem->baseInfo.szName) -1 );    

            //bool bResult = _mountManager.InitMountAttribute( *pMountItem );
            //if ( !bResult )
            //{ return; }

            //bResult = _mountManager.InitMountSkill( *pMountItem );
            //if ( !bResult )
            //{ return; }

            //_mountManager.UpdateActiveSkillBag();
            //_mountManager.ApplyMountAttributeToChar();

            //bIsUsedSuccess = true;
            //MsgUpdateMount msg;
            //msg.header.stID = GetID();
            //msg.mount       = *pMountItem;
            //GettheServer().SendMsgToSingle(&msg,this);
        }
        break;
    case ItemDefine::EMRIF_HuanTongShu:
        {
            if ( pMountItem->IsLock() )
            {
                SendErrorToClient( ER_IsLocked );
                return; 
            }

            // ??????????????????????
            if (pMountItem->baseInfo.generation != 0)
            {
                SendErrorToClient( ER_ErrorMountHuanTongShu );
                return; 
            }

            ItemDefine::SDrome* pSelfDrome = GettheItemDetail().GetDromeByID( pMountItem->baseInfo.id );
            if ( pSelfDrome == NULL ) 
            { 
                SendErrorToClient( ER_ErrorMountData );
                return; 
            }

            if (pSelfDrome->takeLevel < pRestore->nMountUseLevel )
            {
                SendErrorToClient( ER_ErrorMountHuanTongShuLevel );
                return;
            }

            // ????????????????
            if ( pUseGoodsToMount->nMountIndex == _mountManager.GetActiveMountIndex() )
            { _mountManager.ClearPassiveSkillAffect(); }

            _mountManager.RandMountQuality( *pMountItem );  // ??????????????

            bool bResult = _mountManager.InitMountAttribute( *pMountItem );
            if ( !bResult )
            { return; }

            bResult = _mountManager.InitMountSkill( *pMountItem );
            if ( !bResult )
            { return; }

            // ??????????????????????
            if ( pUseGoodsToMount->nMountIndex == _mountManager.GetActiveMountIndex() )
            { 
                _mountManager.UpdateActiveSkillBag(); 
                _mountManager.ApplyMountAttributeToChar( false, true );
            }

            bIsUsedSuccess = true;
            MsgUpdateMount msg;
            msg.header.stID = GetID();
            msg.mount       = *pMountItem;
            GettheServer().SendMsgToSingle(&msg,this);
        }
        break;

    }

    if (bIsUsedSuccess)
    {
        uint16 ustCount = 1;

        //Log("???????? \t%s\t%d",pTargetItemCommonConfig->GetItemName(),pTargetItemCommonConfig->ustItemID );
	   
		switch ( pUseGoodsToMount->ucItemBagType )
		{
		case BT_NormalItemBag:
			{
				SCharItem * _item  = _NormalItemBag.GetItemByIndex(pUseGoodsToMount->ustItemIndex);
				if (_item)
				{
					theLogEventService.LogItemConsume(GetAccountID(),GetDBCharacterID(),_item->GetItemID(),ustCount,_item->GetItemGuid(),
						_item->GetItemCount()-ustCount>=0?_item->GetItemCount()-ustCount:0,eItemLogInfo_ItemConsume_Use,GetCharName(),pTargetItemCommonConfig->GetItemName());
				}				
			}
			break;
		case BT_MaterialBag:
			{
				SCharItem * _item  = _MaterialItemBag.GetItemByIndex(pUseGoodsToMount->ustItemIndex);
				if (_item)
				{
					theLogEventService.LogItemConsume(GetAccountID(),GetDBCharacterID(),_item->GetItemID(),ustCount,_item->GetItemGuid(),
						_item->GetItemCount()-ustCount>=0?_item->GetItemCount()-ustCount:0,eItemLogInfo_ItemConsume_Use,
						                              GetCharName(),pTargetItemCommonConfig->GetItemName());
				}
			}
			break;
		case BT_TaskBag:
			{
				SCharItem * _item  = _TaskItemBag.GetItemByIndex(pUseGoodsToMount->ustItemIndex);
				if (_item)
				{
					theLogEventService.LogItemConsume(GetAccountID(),GetDBCharacterID(),_item->GetItemID(),ustCount,_item->GetItemGuid(),
						_item->GetItemCount()-ustCount>=0?_item->GetItemCount()-ustCount:0,eItemLogInfo_ItemConsume_Use,
						                               GetCharName(),pTargetItemCommonConfig->GetItemName());
				}
			}
			break;

		}

	
  Log(theXmlString.GetString(eServerLog_UseItem),pTargetItemCommonConfig->GetItemName(),pTargetItemCommonConfig->ustItemID );
        switch ( pUseGoodsToMount->ucItemBagType )
        {
        case BT_NormalItemBag:
            if( _NormalItemBag.PopItem( pUseGoodsToMount->ustItemIndex, ustCount ) != ierr_Success )
                return;
            break;
        case BT_MaterialBag:
            if( _MaterialItemBag.PopItem( pUseGoodsToMount->ustItemIndex, ustCount ) != ierr_Success )
                return;
            break;
        case BT_TaskBag:
            if( _TaskItemBag.PopItem( pUseGoodsToMount->ustItemIndex, ustCount ) != ierr_Success )
                return;
            break;
        default:
            return;
        }
        pUseGoodsToMount->stItemCount = ustCount;

        // ????MsgUseGoods????????????
        MsgUseGoods xUseGoods;
        xUseGoods.ustItemIndex  = pUseGoodsToMount->ustItemIndex;
        xUseGoods.stItemCount   = pUseGoodsToMount->stItemCount;
        xUseGoods.stDstChar     = pUseGoodsToMount->stDstChar;
        xUseGoods.stSrcChar     = pUseGoodsToMount->stSrcChar;
        xUseGoods.nRemainValue  = pUseGoodsToMount->nRemainValue;
        xUseGoods.ucItemBagType = pUseGoodsToMount->ucItemBagType;
        GettheServer().SendMsgToSingle( &xUseGoods, this );
    }
}

void GamePlayer::_ProcessUseReelItemToMount( MsgUseGoodsToMount* pUseGoodsToMount, SCharItem* pTargetItem, ItemDefine::SItemCommon* pTargetItemCommonConfig )
{
    if (pUseGoodsToMount == NULL || pTargetItem == NULL || pTargetItemCommonConfig == NULL)
    { return; }

    SMountItem* pMountItem = _mountManager.GetMountByIndex(pUseGoodsToMount->nMountIndex);
    if ( pMountItem == NULL )
    {  
        SendErrorToClient( ER_NotHaveThisMount );
        return;
    }
    
    ItemDefine::SItemReel* pReel = (ItemDefine::SItemReel*)pTargetItemCommonConfig;
    const SCharSkill* pMountSkill = pMountItem->skillInfo.GetSkill( pReel->skillId );

    ItemDefine::SDrome* pDrome = GettheItemDetail().GetDromeByID( pMountItem->baseInfo.id );
    if ( pDrome == NULL ) 
    { 
        SendErrorToClient( ER_ErrorMountData );
        return; 
    }

    ItemDefine::SItemSkill* pSkillConfig = GettheItemDetail().GetSkillByID( pReel->skillId, pReel->skillLevel );
    if( pSkillConfig == NULL )
    { return; }

    if ( pSkillConfig->sSkillCategory == ItemDefine::SCT_MountMasterInitiativeControl)
    { 
        if (pMountItem->skillInfo.initiativeSkillNumber <= 0)
        {
            SendErrorToClient( ER_MountCantLearnSkill );
            return;
        }
    }

    if(pDrome->takeLevel < pReel->mountTakeLevel)
    {
        SendErrorToClient( ER_ReelMountTakeLevel );
        return; 
    }

    if(pMountItem->baseInfo.level < pReel->mountLevel)
    {
        SendErrorToClient( ER_ReelMountLevel );
        return; 
    }            

    if (pMountSkill == NULL && pReel->skillLevel != 1)
    {
        SendErrorToClient( ER_ReelMountPreSkill );
        return; 
    }

    if (pMountSkill != NULL && (pMountSkill->stSkillLevel + 1 != pReel->skillLevel) )
    {
        SendErrorToClient( ER_ReelMountPreSkill );
        return; 
    }

    if ( pUseGoodsToMount->nMountIndex == _mountManager.GetActiveMountIndex() )
    { _mountManager.ClearPassiveSkillAffect(); }

    int nReplaceIndex = -1;

    uint8 beginIndex = 0, endIndex = 0;
    if ( pSkillConfig->sSkillCategory == ItemDefine::SCT_MountMasterInitiativeControl)
    { 
        beginIndex = SMountItem::MICD_InitiativeSkillIndex; 
        endIndex   = pMountItem->skillInfo.initiativeSkillNumber;
    }
    else
    { 
        beginIndex = SMountItem::MICD_PassiveSkillIndex; 
        endIndex   = SMountItem::MICD_MaxSkillCount;
    }

    for ( int i = beginIndex; i < endIndex; ++i)
    {
        // ??????????????????
        if ( pMountItem->skillInfo.skills[i].ustSkillID != InvalidLogicNumber )
        { 
            ItemDefine::SItemSkill* pMountSkill = GettheItemDetail().GetSkillByID( pMountItem->skillInfo.skills[i].ustSkillID, pMountItem->skillInfo.skills[i].stSkillLevel );
            if( pMountSkill == NULL )
            { return; }

            if ( pMountSkill->mountSkillCategory == pSkillConfig->mountSkillCategory )
            { 
                nReplaceIndex = i;
                break;
            }
            continue; 
        }

        // ??????????????????????????,??????????????????
        uint8 replaceRatio = pReel->replaceRatio[i - beginIndex];
        int randNum = theRand.rand32() % RAND_NUM;
        if ( randNum >= replaceRatio )
        {  nReplaceIndex = i - 1;  }
        break;
    }

    bool bResult = false;            
    if ( nReplaceIndex >=0 )
    { bResult = pMountItem->skillInfo.ReplaceSkill( pReel->skillId, pReel->skillLevel, nReplaceIndex  ); }
    else
    { bResult = pMountItem->skillInfo.AddSkill( pReel->skillId, pReel->skillLevel, beginIndex ); }

    if ( !bResult )
    {
        SendErrorToClient( ER_MountCantLearnSkill );
        return;
    }

    if ( pUseGoodsToMount->nMountIndex == _mountManager.GetActiveMountIndex() )
    {
        _mountManager.UpdateActiveSkillBag(); 
        _mountManager.ApplyMountAttributeToChar( false, true );
    }

	unsigned short ustCount = 1;

   //LYH????????
	switch ( pUseGoodsToMount->ucItemBagType )
	{
	case BT_NormalItemBag:
		{
			SCharItem * _item  = _NormalItemBag.GetItemByIndex(pUseGoodsToMount->ustItemIndex);
			if (_item)
			{
				theLogEventService.LogItemConsume(GetAccountID(),GetDBCharacterID(),_item->GetItemID(),ustCount,_item->GetItemGuid(),
					_item->GetItemCount()-ustCount>=0?_item->GetItemCount()-ustCount:0,eItemLogInfo_ItemConsume_Use,
					                              GetCharName(),pTargetItemCommonConfig->GetItemName());
			}				
		}
		break;
	case BT_MaterialBag:
		{
			SCharItem * _item  = _MaterialItemBag.GetItemByIndex(pUseGoodsToMount->ustItemIndex);
			if (_item)
			{
				theLogEventService.LogItemConsume(GetAccountID(),GetDBCharacterID(),_item->GetItemID(),ustCount,_item->GetItemGuid(),
					_item->GetItemCount()-ustCount>=0?_item->GetItemCount()-ustCount:0,eItemLogInfo_ItemConsume_Use,
					                               GetCharName(),pTargetItemCommonConfig->GetItemName());
			}
		}
		break;
	case BT_TaskBag:
		{
			SCharItem * _item  = _TaskItemBag.GetItemByIndex(pUseGoodsToMount->ustItemIndex);
			if (_item)
			{
				theLogEventService.LogItemConsume(GetAccountID(),GetDBCharacterID(),_item->GetItemID(),ustCount,_item->GetItemGuid(),
					_item->GetItemCount()-ustCount>=0?_item->GetItemCount()-ustCount:0,eItemLogInfo_ItemConsume_Use,
					                                GetCharName(),pTargetItemCommonConfig->GetItemName());
			}
		}
		break;
	}

    
    switch ( pUseGoodsToMount->ucItemBagType )
    {
    case BT_NormalItemBag:
        if( _NormalItemBag.PopItem( pUseGoodsToMount->ustItemIndex, ustCount ) != ierr_Success )
            return;
        break;
    case BT_MaterialBag:
        if( _MaterialItemBag.PopItem( pUseGoodsToMount->ustItemIndex, ustCount ) != ierr_Success )
            return;
        break;
    case BT_TaskBag:
        if( _TaskItemBag.PopItem( pUseGoodsToMount->ustItemIndex, ustCount ) != ierr_Success )
            return;
        break;
    default:
        return;
    }

    MsgUseGoods msgUseGoods;
    msgUseGoods.ustItemIndex  = pUseGoodsToMount->ustItemIndex;
    msgUseGoods.stItemCount   = ustCount;
    msgUseGoods.stDstChar     = pUseGoodsToMount->stDstChar;
    msgUseGoods.stSrcChar     = pUseGoodsToMount->stSrcChar;
    msgUseGoods.nRemainValue  = pUseGoodsToMount->nRemainValue;
    msgUseGoods.ucItemBagType = pUseGoodsToMount->ucItemBagType;
    GettheServer().SendMsgToSingle( &msgUseGoods, this );

    MsgUpdateMount msg;
    msg.header.stID = GetID();
    msg.mount       = *pMountItem;
    GettheServer().SendMsgToSingle(&msg,this);
}

void GamePlayer::_ProcessUseItemToMount( MsgUseGoodsToMount* pUseGoodsToMount, SCharItem* pTargetItem, ItemDefine::SItemCommon* pTargetItemCommonConfig )
{
    if (pUseGoodsToMount == NULL || pTargetItem == NULL || pTargetItemCommonConfig == NULL)
    { return; }

    SMountItem* pMountItem = _mountManager.GetMountByIndex(pUseGoodsToMount->nMountIndex);
    if ( pMountItem == NULL )
    {  
        MsgAckResult msg;
        msg.header.stID = GetID();
        msg.result      = ER_NotHaveThisMount;//ER_NotActiveMount;
        GettheServer().SendMsgToSingle( &msg, this);
        return;
    }

    switch( pTargetItemCommonConfig->ucItemType )
    {
    case ItemDefine::ITEMTYPE_RESTORE:
        {
            _ProcessUseRestoreItemToMount(pUseGoodsToMount,pTargetItem,pTargetItemCommonConfig);
        }
        break;
    case ItemDefine::ITEMTYPE_REEL:
        { 
           _ProcessUseReelItemToMount(pUseGoodsToMount,pTargetItem,pTargetItemCommonConfig);
        }
        break;
    }
}

void GamePlayer::_ProcessUseItemToPet( MsgUseGoodsToPet* pUseGoodsToPet, SCharItem* pTargetItem, ItemDefine::SItemCommon* pTargetItemCommonConfig )
{
    if (pUseGoodsToPet == NULL || pTargetItem == NULL || pTargetItemCommonConfig == NULL)
    { return; }

    SPetItem* pPetItem = _petManager.GetPetByIndex( pUseGoodsToPet->nPetIndex );
    if ( pPetItem == NULL )
    {  
        MsgAckResult msg;
        msg.result = ER_NotFoundPet;
        GettheServer().SendMsgToSingle( &msg, this);
        return;
    }

    switch( pTargetItemCommonConfig->ucItemType )
    {
    case ItemDefine::ITEMTYPE_RESTORE:
        {
            _ProcessUseRestoreItemToPet(pUseGoodsToPet,pTargetItem,pTargetItemCommonConfig);
        }
        break;
    case ItemDefine::ITEMTYPE_REEL:
        { 
            _ProcessUseReelItemToPet(pUseGoodsToPet,pTargetItem,pTargetItemCommonConfig);
        }
        break;
    }
}

void GamePlayer::_ProcessUseRestoreItemToPet( MsgUseGoodsToPet* pUseGoodsToPet, SCharItem* pTargetItem, ItemDefine::SItemCommon* pTargetItemCommonConfig )
{
    if (pUseGoodsToPet == NULL || pTargetItem == NULL || pTargetItemCommonConfig == NULL)
    { return; }

    SPetItem* pPetItem = _petManager.GetPetByIndex( pUseGoodsToPet->nPetIndex );
    if ( pPetItem == NULL )
    {  
        SendErrorToClient( ER_NotFoundPet );
        return;
    }

    ItemDefine::SPetMonster* pMonsterConfig = GettheItemDetail().GetPetById( pPetItem->baseInfo.petId );
    if ( pMonsterConfig == NULL ) 
    { 
        SendErrorToClient( ER_NotFoundPet );
        return; 
    }

    ItemDefine::SItemRestore* pRestore = (ItemDefine::SItemRestore*)pTargetItemCommonConfig;

    if( !m_RestoreColdDown.UseRestore( pTargetItem->itembaseinfo.ustItemID ))
    { return; }

    if ( !pRestore->bExpendable )
    { return; }

    bool bIsUsedSuccess = false;
    switch ( pRestore->specialFunction )
    {
    case ItemDefine::EPetFunc_RestoreHP:
        {
            bIsUsedSuccess = _petManager.AddPetHp       (pUseGoodsToPet->nPetIndex, pRestore->dwAddHP);
        }
        break;
    case ItemDefine::EPetFunc_AddLife:
        {
            bIsUsedSuccess = _petManager.AddPetLife     (pUseGoodsToPet->nPetIndex, pRestore->dwAddHP);
        }
        break;
    case ItemDefine::EPetFunc_AddLoyalty:
        {
			//????????????????  ????????????????????  by liaojie 11.21
            bIsUsedSuccess = _petManager.AddPetLoyalty  (pUseGoodsToPet->nPetIndex, pRestore->dwAddHP);
        }
        break;
    case  ItemDefine::EPetFunc_AddExp:
        {
            bIsUsedSuccess = _petManager.AddPetExp      (pUseGoodsToPet->nPetIndex, pRestore->dwAddExp);
        }
        break;
    case ItemDefine::EPetFunc_AddSavvy:
        {
			if ( pPetItem == _petManager.GetActivePet() )
			{  
				SendErrorToClient( ER_IsActivePet );
				return;
			}
            if ( pRestore->petSavvy < pPetItem->baseInfo.savvy )
            {
                SendErrorToClient( ER_ItemSavvy );
                return;
            }

            _petManager.AddPetSavvy ( pUseGoodsToPet->nPetIndex );
            bIsUsedSuccess = true;
        }
        break;
    case ItemDefine::EPetFunc_ResetPoint:
        {
            if ( pPetItem->IsLock() )
            {
                MsgAckResult msg;
                msg.result = ER_IsLocked;
                GettheServer().SendMsgToSingle( &msg, this );
                return; 
            }

            bIsUsedSuccess = _petManager.ClearPetPotential(pUseGoodsToPet->nPetIndex);
        }
        break;
    //case ItemDefine::EMRIF_OpenSkill:
    //    {
    //        if ( pMountItem->IsLock() )
    //        {
    //            MsgAckResult msg;
    //            msg.result = ER_IsLocked;
    //            GettheServer().SendMsgToSingle( &msg, this );
    //            return; 
    //        }

    //        bIsUsedSuccess = _mountManager.SetInitiativeSkill(pUseGoodsToMount->nMountIndex, pRestore->openSkillNum);
    //    }
    //    break;
    //case ItemDefine::EMRIF_ForgetSkill:
    //    {
    //        if ( pMountItem->IsLock() )
    //        {
    //            MsgAckResult msg;
    //            msg.result = ER_IsLocked;
    //            GettheServer().SendMsgToSingle( &msg, this );
    //            return; 
    //        }

    //        bIsUsedSuccess = _mountManager.ForgetInitiativeSkill(pUseGoodsToMount->nMountIndex, pRestore->forgetSkillIndex);
    //    }
    //    break;
    //case ItemDefine::EPetFunc_HuanTongShu:
    //    {
    //        if ( pPetItem->IsLock() )
    //        {
    //            SendErrorToClient( ER_IsLocked );
    //            return; 
    //        }

    //        ItemDefine::SPetMonster* pMonsterConfig = GettheItemDetail().GetPetById( monsterId );
    //        if ( pMonsterConfig == NULL ) 
    //        { 
    //            SendErrorToClient( ER_NotFoundPet );
    //            return ; 
    //        }
    //        
    //        if( pMonsterConfig->bIsAberrance )
    //        { 
    //            SendErrorToClient( ER_PetIsAberrance );
    //            return ; 
    //        }

    //        if ( pPetItem->baseInfo.breedNum > 0 )
    //        {
    //            SendErrorToClient( ER_PetHasBreed );
    //            return; 
    //        }
 
    //        bIsUsedSuccess = true;
    //        MsgUpdateMount msg;
    //        msg.header.stID = GetID();
    //        msg.mount       = *pMountItem;
    //        GettheServer().SendMsgToSingle(&msg,this);
    //    }
    //    break;
    default:
        break;
    }

    if (bIsUsedSuccess)
    {
        uint16 ustCount = 1;

		//LYH????????
		switch ( pUseGoodsToPet->ucItemBagType )
		{
		case BT_NormalItemBag:
			{
				SCharItem * _item  = _NormalItemBag.GetItemByIndex(pUseGoodsToPet->ustItemIndex);
				if (_item)
				{
					theLogEventService.LogItemConsume(GetAccountID(),GetDBCharacterID(),_item->GetItemID(),ustCount,_item->GetItemGuid(),
						_item->GetItemCount()-ustCount>=0?_item->GetItemCount()-ustCount:0,eItemLogInfo_ItemConsume_Use,
						                               GetCharName(),pTargetItemCommonConfig->GetItemName());
				}				
			}
			break;
		case BT_MaterialBag:
			{
				SCharItem * _item  = _MaterialItemBag.GetItemByIndex(pUseGoodsToPet->ustItemIndex);
				if (_item)
				{
					theLogEventService.LogItemConsume(GetAccountID(),GetDBCharacterID(),_item->GetItemID(),ustCount,_item->GetItemGuid(),
						_item->GetItemCount()-ustCount>=0?_item->GetItemCount()-ustCount:0,eItemLogInfo_ItemConsume_Use,
						                              GetCharName(),pTargetItemCommonConfig->GetItemName());
				}
			}
			break;
		case BT_TaskBag:
			{
				SCharItem * _item  = _TaskItemBag.GetItemByIndex(pUseGoodsToPet->ustItemIndex);
				if (_item)
				{
					theLogEventService.LogItemConsume(GetAccountID(),GetDBCharacterID(),_item->GetItemID(),ustCount,_item->GetItemGuid(),
						_item->GetItemCount()-ustCount>=0?_item->GetItemCount()-ustCount:0,eItemLogInfo_ItemConsume_Use,
						                              GetCharName(),pTargetItemCommonConfig->GetItemName());
				}
			}
			break;
		}

        Log(theXmlString.GetString(eServerLog_UseItem),pTargetItemCommonConfig->GetItemName(),pTargetItemCommonConfig->ustItemID );

        switch ( pUseGoodsToPet->ucItemBagType )
        {
        case BT_NormalItemBag:
            if( _NormalItemBag.PopItem( pUseGoodsToPet->ustItemIndex, ustCount ) != ierr_Success )
                return;
            break;
        case BT_MaterialBag:
            if( _MaterialItemBag.PopItem( pUseGoodsToPet->ustItemIndex, ustCount ) != ierr_Success )
                return;
            break;
        case BT_TaskBag:
            if( _TaskItemBag.PopItem( pUseGoodsToPet->ustItemIndex, ustCount ) != ierr_Success )
                return;
            break;
        default:
            return;
        }
        pUseGoodsToPet->stItemCount = ustCount;

        // ????MsgUseGoods????????????
        MsgUseGoods xUseGoods;
        xUseGoods.ustItemIndex  = pUseGoodsToPet->ustItemIndex;
        xUseGoods.stItemCount   = pUseGoodsToPet->stItemCount;
        xUseGoods.stDstChar     = pUseGoodsToPet->stDstChar;
        xUseGoods.stSrcChar     = pUseGoodsToPet->stSrcChar;
        xUseGoods.nRemainValue  = pUseGoodsToPet->nRemainValue;
        xUseGoods.ucItemBagType = pUseGoodsToPet->ucItemBagType;
        GettheServer().SendMsgToSingle( &xUseGoods, this );
    }
}

void GamePlayer::_ProcessUseReelItemToPet( MsgUseGoodsToPet* pUseGoodsToPet, SCharItem* pTargetItem, ItemDefine::SItemCommon* pTargetItemCommonConfig )
{
    if (pUseGoodsToPet == NULL || pTargetItem == NULL || pTargetItemCommonConfig == NULL)
    { return; }

    SPetItem* pPetItem = _petManager.GetPetByIndex(pUseGoodsToPet->nPetIndex);
    if ( pPetItem == NULL )
    {  
        SendErrorToClient( ER_NotFoundPet );
        return;
    }

    ItemDefine::SItemReel* pReel = (ItemDefine::SItemReel*)pTargetItemCommonConfig;
    if ( pReel->petLevel > pPetItem->baseInfo.level )
    {
        SendErrorToClient( ER_PetLevelSkill );
        return;
    }

    ItemDefine::SPetMonster* pPetMonster = GettheItemDetail().GetPetById( pPetItem->baseInfo.petId );
    if ( pPetMonster == NULL ) 
    { 
        SendErrorToClient( ER_NotFoundPet );
        return; 
    }

    if( pReel->petTakeLevel > pPetMonster->takeLevel )
    { 
        SendErrorToClient( ER_PetTakeLevel, pPetMonster->takeLevel );
        return; 
    }

    if ( pReel->costMoney > GetMoney()  )
    {
        SendErrorToClient( ER_PetSkillMoney );
        return; 
    }

    ItemDefine::SItemSkill* pSkillConfig = GettheItemDetail().GetSkillByID( pReel->skillId, pReel->skillLevel );
    if( pSkillConfig == NULL )
    { return; }

    // ???????????? ????????????
    int manualSkillNum = 0, autoSkillNum = 0;
    std::vector< int > vecManualSkillIndex;
    std::vector< int > vecAutoSkillIndex  ;
    for (int i=0; i<SPetItem::PetDefine_MaxSkillCount; ++i )
    {
        if (pPetItem->skillInfo.skills[i].ustSkillID == InvalidLogicNumber)
        { continue; }

        if (pPetItem->skillInfo.skills[i].ustSkillID == pPetMonster->talentSkillId)
        { continue; }

        // ????????????????????
        if (pPetItem->skillInfo.skills[i].ustSkillID == pReel->skillId)
        {
            SendErrorToClient( ER_HasPetSkill );
            return;
        }

        ItemDefine::SItemSkill* pPetSkill = GettheItemDetail().GetSkillByID( pPetItem->skillInfo.skills[i].ustSkillID, pPetItem->skillInfo.skills[i].stSkillLevel );
        if( pPetSkill == NULL )
        { continue; }

        if ( pPetSkill->groupId == pSkillConfig->groupId && pPetSkill->groupLevel > pSkillConfig->groupLevel )
        { 
            SendErrorToClient( ER_PetSkillGroupLevel );
            return;
        }

        if ( pPetSkill->sSkillCategory == ItemDefine::SCT_PetMasterManualControl )
        { 
            vecManualSkillIndex.push_back( i );
            ++manualSkillNum; 
        }
        else
        { 
            vecAutoSkillIndex.push_back( i );
            ++autoSkillNum; 
        }
    }

    bool bResult = false;
    bool bIsManualSkill = (pSkillConfig->sSkillCategory == ItemDefine::SCT_PetMasterManualControl);
    
    uint16 replaceSkillId    = 0;
    uint8  replaceSkillLevel = 0;
    int    nReplaceIndex     = -1;
    if ( pSkillConfig->groupLevel > 1 || pSkillConfig->petSkillCategory == EPetSkillCategory_ManualAttack || pSkillConfig->petSkillCategory == EPetSkillCategory_AutoAttack )
    {// ???????????????????????? ????????????  ???????????? ????
        for ( int i = 0; i < SPetItem::PetDefine_MaxSkillCount; ++i)
        {
            if (pPetItem->skillInfo.skills[i].ustSkillID == InvalidLogicNumber)
            { continue; }

            if (pPetItem->skillInfo.skills[i].ustSkillID == pPetMonster->talentSkillId)
            { continue; }

            ItemDefine::SItemSkill* pPetSkill = GettheItemDetail().GetSkillByID( pPetItem->skillInfo.skills[i].ustSkillID, pPetItem->skillInfo.skills[i].stSkillLevel );
            if( pPetSkill == NULL )
            { continue; }

            if ( pPetSkill->groupId == pSkillConfig->groupId && pPetSkill->groupLevel < pSkillConfig->groupLevel )
            { 
                nReplaceIndex = i;
                break;
            }

            if ( pPetSkill->petSkillCategory == EPetSkillCategory_ManualAttack  && pSkillConfig->petSkillCategory == EPetSkillCategory_ManualAttack )
            { 
                nReplaceIndex = i;
                break;
            }

            if ( pPetSkill->petSkillCategory == EPetSkillCategory_AutoAttack && pSkillConfig->petSkillCategory == EPetSkillCategory_AutoAttack )
            { 
                nReplaceIndex = i;
                break;
            }
        }
    }
    
	int SkillSum = thePetDefineConfig.GetLevelSkillSum(pPetItem->baseInfo.level);//??????????????????????
	bool IsCanAddSkill = (SkillSum<=(manualSkillNum + autoSkillNum + 1))?false:true;//????????????????

    if (nReplaceIndex == -1)
    {//????????
        if ((thePetSettingConfig.IsSkillRepalce( bIsManualSkill, pPetMonster->skillNumControl, manualSkillNum, autoSkillNum ) || !IsCanAddSkill))
        {
            if ( pSkillConfig->sSkillCategory == ItemDefine::SCT_PetMasterManualControl )
            {
                nReplaceIndex = vecManualSkillIndex [ theRand.rand16() % vecManualSkillIndex.size() ]; 
            }
            else
            {
                nReplaceIndex = vecAutoSkillIndex   [ theRand.rand16() % vecAutoSkillIndex.size() ]; 
            }
        }
        else
        { bResult = pPetItem->skillInfo.AddSkill( pReel->skillId, pReel->skillLevel ); }
    }

    if ( nReplaceIndex >= 0 )
    { 
        replaceSkillId    = pPetItem->skillInfo.skills[nReplaceIndex].ustSkillID    ;
        replaceSkillLevel = pPetItem->skillInfo.skills[nReplaceIndex].stSkillLevel  ;
        bResult = pPetItem->skillInfo.ReplaceSkill( pReel->skillId, pReel->skillLevel, nReplaceIndex  ); 
    }

    // ????????????
    for (int i=0; i<SPetItem::PetDefine_MaxSkillCount; ++i )
    {
        if (pPetItem->skillInfo.skills[i].ustSkillID == InvalidLogicNumber)
        { continue; }

        if (pPetItem->skillInfo.skills[i].ustSkillID == pPetMonster->talentSkillId)
        { continue; }

        for (int lv=0; lv < ItemDefine::MaxLevel_Skill; ++lv )
        {
            ItemDefine::SItemSkill* pSkill = GettheItemDetail().GetSkillByID( pPetItem->skillInfo.skills[i].ustSkillID, lv );
            if (pSkill == NULL)
            { continue; }

            if (pSkill->stLearnLevelReq <= pPetItem->baseInfo.level )
            { pPetItem->skillInfo.skills[i].stSkillLevel = lv; }
        }
    }

    // ????????
    OperateMoney( EOT_Sub, pReel->costMoney, true, __FUNCTION__, __LINE__ ,ePlayerMoneySourceType_UseReelItemToPet);

    if ( !bResult )
    { SendErrorToClient( ER_PetLearnSkill ); }
    else
    {
        // ????????????
        //_petManager.ApplyPassiveSkillToPet( pPetItem );

        if ( pUseGoodsToPet->nPetIndex == _petManager.GetActivePetIndex() )
        { // ????????????????
            MonsterNurturePet* pNurturePet = (MonsterNurturePet*)_petManager.GetMonsterNurturePet();
            if ( pNurturePet != NULL )
            { pNurturePet->UpdatePetData(); }
        }

        MsgAddUpdatePet msgUpdate;
        msgUpdate.header.stID =  GetID();
        msgUpdate.type        = MsgAddUpdatePet::OT_Update;
        msgUpdate.pet         = *pPetItem;
        GettheServer().SendMsgToSingle(&msgUpdate,this);

        MsgPetLearnSkill msg;
        msg.source  = MsgPetLearnSkill::ESource_Item;
        msg.index   = pUseGoodsToPet->nPetIndex;
        msg.skillId = pReel->skillId;
        msg.skillLevel = pReel->skillLevel;
        msg.replaceSkillId = replaceSkillId;
        msg.replaceSkillLevel = replaceSkillLevel;
        GettheServer().SendMsgToSingle( &msg, this );
    }

    // ????????
	unsigned short ustCount = 1;
	//LYH????????
	switch ( pUseGoodsToPet->ucItemBagType )
	{
	case BT_NormalItemBag:
		{
			SCharItem * _item  = _NormalItemBag.GetItemByIndex(pUseGoodsToPet->ustItemIndex);
			if (_item)
			{
				theLogEventService.LogItemConsume(GetAccountID(),GetDBCharacterID(),_item->GetItemID(),ustCount,_item->GetItemGuid(),
					_item->GetItemCount()-ustCount>=0?_item->GetItemCount()-ustCount:0,eItemLogInfo_ItemConsume_Use,
					                              GetCharName(),pTargetItemCommonConfig->GetItemName());
			}				
		}
		break;
	case BT_MaterialBag:
		{
			SCharItem * _item  = _MaterialItemBag.GetItemByIndex(pUseGoodsToPet->ustItemIndex);
			if (_item)
			{
				theLogEventService.LogItemConsume(GetAccountID(),GetDBCharacterID(),_item->GetItemID(),ustCount,_item->GetItemGuid(),
					_item->GetItemCount()-ustCount>=0?_item->GetItemCount()-ustCount:0,eItemLogInfo_ItemConsume_Use,
					                               GetCharName(),pTargetItemCommonConfig->GetItemName());
			}
		}
		break;
	case BT_TaskBag:
		{
			SCharItem * _item  = _TaskItemBag.GetItemByIndex(pUseGoodsToPet->ustItemIndex);
			if (_item)
			{
				theLogEventService.LogItemConsume(GetAccountID(),GetDBCharacterID(),_item->GetItemID(),ustCount,_item->GetItemGuid(),
					_item->GetItemCount()-ustCount>=0?_item->GetItemCount()-ustCount:0,eItemLogInfo_ItemConsume_Use,
					                              GetCharName(),pTargetItemCommonConfig->GetItemName());
			}
		}
		break;
	}


    
    switch ( pUseGoodsToPet->ucItemBagType )
    {
    case BT_NormalItemBag:
        if( _NormalItemBag.PopItem( pUseGoodsToPet->ustItemIndex, ustCount ) != ierr_Success )
            return;
        break;
    case BT_MaterialBag:
        if( _MaterialItemBag.PopItem( pUseGoodsToPet->ustItemIndex, ustCount ) != ierr_Success )
            return;
        break;
    case BT_TaskBag:
        if( _TaskItemBag.PopItem( pUseGoodsToPet->ustItemIndex, ustCount ) != ierr_Success )
            return;
        break;
    default:
        return;
    }

    MsgUseGoods msgUseGoods;
    msgUseGoods.ustItemIndex  = pUseGoodsToPet->ustItemIndex;
    msgUseGoods.stItemCount   = ustCount;
    msgUseGoods.stDstChar     = pUseGoodsToPet->stDstChar;
    msgUseGoods.stSrcChar     = pUseGoodsToPet->stSrcChar;
    msgUseGoods.nRemainValue  = pUseGoodsToPet->nRemainValue;
    msgUseGoods.ucItemBagType = pUseGoodsToPet->ucItemBagType;
    GettheServer().SendMsgToSingle( &msgUseGoods, this );
}

void GamePlayer::_ProcessUseItemToChar( MsgUseGoods* pUseGoods, SCharItem* pTargetItem, ItemDefine::SItemCommon* pTargetItemConfig )
{
    // ?????????? // ????????????
    GameObjectId stDstPlayerId = pUseGoods->stDstChar;
    if ( stDstPlayerId == -1 )
        return;
    BaseCharacter* pDstPlayer = GetTargetCanUseGood( stDstPlayerId, pTargetItemConfig->byUserTarget,pTargetItemConfig->ustItemID);
    if ( pDstPlayer == NULL )
    { return; }

    unsigned short itemId = pTargetItem->itembaseinfo.ustItemID;
 
	//??????????????????????????????????FLAG?????????????????????????????????????????? by vvx 2012.8.18
	bool call_script = true;

    switch( pTargetItemConfig->ucItemType )
    {
    case ItemDefine::ITEMTYPE_RESTORE:
        {
			if( !m_RestoreColdDown.UseRestore( itemId, true ))
			{ return; }
            _ProcessUseRestoreItemToChar( pUseGoods, pTargetItem, pTargetItemConfig );
        }
        break;
    case ItemDefine::ITEMTYPE_REEL:
        return;
    case ItemDefine::ITEMTYPE_OTHER:
        {
   //         ItemDefine::SItemOther* pOtherItemConfig = static_cast< ItemDefine::SItemOther* >( pTargetItemConfig );
   //         if ( pOtherItemConfig->otherType == CItemDetail::OtherType_PetIdentify )
   //         {
			//	//????????????,??????????????????????????,?????????????????????????????????? by vvx 2012.7.27
			//	if ( pDstPlayer->IsPlayer() )
			//	{
			//		// ????????????????
			//		if ( pDstPlayer != this )
			//		{ pDstPlayer->TellClient( theXmlString.GetString(eClient_AddInfo_2slk_86), GetCharName(), pTargetItemConfig->GetItemName() );}

			//		// ??????????????
			//		if ( m_dwScriptSleep != 0 )
			//		{ // ??????????????????????????
			//			//m_dwScriptSleep = 0;
			//			CancelCurScript( __FILE__, __FUNCTION__ );
			//		}
			//		/////////////////////////////////////////////////////////////////////////////////////
			//		// ????????????????????????????
			//		UseItemInfo xItemInfo;
			//		switch ( pUseGoods->ucItemBagType )
			//		{
			//		case BT_MaterialBag:
			//			xItemInfo.pItemBag = &_MaterialItemBag;
			//			break;
			//		case BT_NormalItemBag:
			//			xItemInfo.pItemBag = &_NormalItemBag;
			//			break;
			//		case BT_TaskBag:
			//			xItemInfo.pItemBag = &_TaskItemBag;
			//			break;
			//		}
			//		xItemInfo.uchItemBagType = pUseGoods->ucItemBagType;
			//		xItemInfo.stIndex  = pUseGoods->ustItemIndex;
			//		xItemInfo.stItemID = pTargetItem->itembaseinfo.ustItemID;
			//		xItemInfo.stCount  = pUseGoods->stItemCount;
			//		xItemInfo.nGuid    = pTargetItem->itembaseinfo.nOnlyInt;
			//		SetUseItemInfo( xItemInfo );
			//		///////////////////////////////////////////////////////////////////////////////////////////////////////////
			//		GetScriptMgr()->StartupVM( ST_USE_ITEM, pTargetItem->itembaseinfo.ustItemID, (GamePlayer*)pDstPlayer );
			//		///////////////////////////////////////////////////////////////////////////////////////////////////////////

			//		call_script = false;
			//	}
			//	//????????????????????,???????????????????? by vvx 2012.7.27
			//	if (_ProcessUsePetIdentifyItemToChar( pUseGoods, pTargetItem, pTargetItemConfig ))
			//	{
			//		return;
			//	}
			//}
        }
        break;
    }

    if ( itemId == InvalidLogicNumber )
    { return; }

    // ????????????
    if ( !pDstPlayer->IsPlayer() )
    { return; }

    // ????????????????
    if ( pDstPlayer != this )
    { pDstPlayer->TellClient( theXmlString.GetString(eClient_AddInfo_2slk_86), GetCharName(), pTargetItemConfig->GetItemName() );}

    // ??????????????
    if ( m_dwScriptSleep != 0 )
    { // ??????????????????????????
        //m_dwScriptSleep = 0;
        CancelCurScript( __FILE__, __FUNCTION__ );
    }

    /////////////////////////////////////////////////////////////////////////////////////
    // ????????????????????????????
	if (call_script)
	{
		UseItemInfo xItemInfo;
		switch ( pUseGoods->ucItemBagType )
		{
		case BT_MaterialBag:
			xItemInfo.pItemBag = &_MaterialItemBag;
			break;
		case BT_NormalItemBag:
			xItemInfo.pItemBag = &_NormalItemBag;
			break;
		case BT_TaskBag:
			xItemInfo.pItemBag = &_TaskItemBag;
			break;
		}
		xItemInfo.uchItemBagType = pUseGoods->ucItemBagType;
		xItemInfo.stIndex  = pUseGoods->ustItemIndex;
		xItemInfo.stItemID = pTargetItem->itembaseinfo.ustItemID;
		xItemInfo.stCount  = pUseGoods->stItemCount;
		xItemInfo.nGuid    = pTargetItem->itembaseinfo.nOnlyInt;
		SetUseItemInfo( xItemInfo );
		/////////////////////////////////////////////////////////////////////////////////////
		GetScriptMgr()->StartupVM( ST_USE_ITEM, pTargetItem->itembaseinfo.ustItemID, (GamePlayer*)pDstPlayer );
	}
}

void GamePlayer::_ProcessUseRestoreItemToChar( MsgUseGoods* pUseGoods, SCharItem* pTargetItem, ItemDefine::SItemCommon* pTargetItemConfig )
{
    // ?????????? // ????????????
    GameObjectId stDstPlayerId = pUseGoods->stDstChar;
    if ( stDstPlayerId == -1 )
        return;
    BaseCharacter* pDstPlayer = GetTargetCanUseGood( stDstPlayerId, pTargetItemConfig->byUserTarget,pTargetItemConfig->ustItemID);
    if ( pDstPlayer == NULL )
    { return; }

    unsigned short itemId = pTargetItem->itembaseinfo.ustItemID;

    if( pTargetItem->IsLock() )
    { return;}

    ItemDefine::SItemRestore* pRestore = (ItemDefine::SItemRestore*)pTargetItemConfig;
    if ( pRestore->stUseLevel > GetLevel() )
    { return;}

    if( pRestore->nUseFightStatus != ItemDefine::EUseStatusType_None )
    {
        if ( pRestore->nUseFightStatus == ItemDefine::EUseStatusType_NoFight &&  HaveFighteFlag( eFighting ) )
        { return;}

        if ( pRestore->nUseFightStatus == ItemDefine::EUseStatusType_InFight && !HaveFighteFlag( eFighting ) )
        { return;}
    }

    if (!pRestore->arrayProfessionReq[GetProfession()])
    { return;}

    if (pRestore->bIsReliveItem || pRestore->bAutoRelive )
    { return; }

    if( !m_RestoreColdDown.UseRestore( pTargetItem->itembaseinfo.ustItemID ))
    { return; }

    if ( !UseRestoreItem( pRestore, pUseGoods->ustItemIndex, pDstPlayer ) )
    { return; }

    if ( pRestore->ustAddStatusID != InvalidLogicNumber && pRestore->ustAddStatusID > 0)
    {
        if ( GLR_Success == pDstPlayer->ApplyBufferStatus(pRestore->ustAddStatusID, pRestore->ustAddStatusLevel, GetID(), SCharBuff::StatusEventType_Other, 0 ))
        {
            pDstPlayer->OnBuffStatusChanged( true );
        }
    }

	//????????	??????
	if (pRestore->specialFunction == ItemDefine::ECharFunc_ResetPoint)
	{
		SCharBaseAttr* pCharBaseInfo = GetCharBaseAttr();
		SCharDBInfo& charDBInfo = GetCharInfo();
		for (int i=0;i<EBaseAttr_MaxSize;i++)
		{
			GetBaseAttr(i)->assign = 0;
			charDBInfo.baseinfo.liveinfo.basePotential += charDBInfo.baseinfo.liveinfo.baseAssignValue[i];
			charDBInfo.baseinfo.liveinfo.baseAssignValue[i] = 0;
			//pCharBaseInfo->baseAttrValue[i].assign = 0;
		}
		ChangeAttr( CharAttr_BasePotential, charDBInfo.baseinfo.liveinfo.basePotential, true );
		ClearAllFightAttrByPart ( ECustomDataPart_assign )      ;
		ApplyBaseAttrToFightAttr( true, ECustomDataPart_assign );
		UpdateCharAllAttibute();
		SendCharAttibuteToClient();
	}
	else if (pRestore->nRestoreType == ItemDefine::EIRT_Epistar)//????????????????????
	{
		MsgGS2CSEpistarPoint msg;
		msg.accountid = GetAccountID();
		msg.characterid = GetDBCharacterID();
		msg._type	= 0;
		msg.nItemId = pTargetItemConfig->ustItemID;
		msg.nPoint  = pRestore->dwAddExp;
		HelperFunc::SafeNCpy( msg.charactername, GetCharName(), sizeof( msg.charactername ) ); 
		GettheServer().SendCenterServerMsg( &msg );
	}

    if ( pRestore->bExpendable )
    {
        unsigned short ustCount = 1;

		//LYH????????
		switch ( pUseGoods->ucItemBagType )
		{
		case BT_NormalItemBag:
			{
				SCharItem * _item  = _NormalItemBag.GetItemByIndex(pUseGoods->ustItemIndex);
				if (_item)
				{
					theLogEventService.LogItemConsume(GetAccountID(),GetDBCharacterID(),_item->GetItemID(),ustCount,_item->GetItemGuid(),
						_item->GetItemCount()-ustCount>=0?_item->GetItemCount()-ustCount:0,eItemLogInfo_ItemConsume_Use,
						                              GetCharName(),pTargetItemConfig->GetItemName());
				}				
			}
			break;
		case BT_MaterialBag:
			{
				SCharItem * _item  = _MaterialItemBag.GetItemByIndex(pUseGoods->ustItemIndex);
				if (_item)
				{
					theLogEventService.LogItemConsume(GetAccountID(),GetDBCharacterID(),_item->GetItemID(),ustCount,_item->GetItemGuid(),
						_item->GetItemCount()-ustCount>=0?_item->GetItemCount()-ustCount:0,eItemLogInfo_ItemConsume_Use,
						                              GetCharName(),pTargetItemConfig->GetItemName());
				}
			}
			break;
		case BT_TaskBag:
			{
				SCharItem * _item  = _TaskItemBag.GetItemByIndex(pUseGoods->ustItemIndex);
				if (_item)
				{
					theLogEventService.LogItemConsume(GetAccountID(),GetDBCharacterID(),_item->GetItemID(),ustCount,_item->GetItemGuid(),
						_item->GetItemCount()-ustCount>=0?_item->GetItemCount()-ustCount:0,eItemLogInfo_ItemConsume_Use,
						                               GetCharName(),pTargetItemConfig->GetItemName());
				}
			}
			break;
		}

        Log(theXmlString.GetString(eServerLog_UseItem),pTargetItemConfig->GetItemName(),pTargetItemConfig->ustItemID );

        if ( pRestore->bHPAuto || pRestore->bMPAuto ) // ????????????????HP
        {
            pUseGoods->nRemainValue = pTargetItem->itembaseinfo.value2;
            if ( pUseGoods->nRemainValue <= 0 ) // ????
            {
                switch ( pUseGoods->ucItemBagType )
                {
                case BT_NormalItemBag:
                    if( _NormalItemBag.PopItem( pUseGoods->ustItemIndex, ustCount ) != ierr_Success )
                        return;
                    break;
                case BT_MaterialBag:
                    if( _MaterialItemBag.PopItem( pUseGoods->ustItemIndex, ustCount ) != ierr_Success )
                        return;
                    break;
                case BT_TaskBag:
                    if( _TaskItemBag.PopItem( pUseGoods->ustItemIndex, ustCount ) != ierr_Success )
                        return;
                    break;
                default:
                    return;
                }
            }
        }
        else // ??????????
        {
            switch ( pUseGoods->ucItemBagType )
            {
            case BT_NormalItemBag:
                if( _NormalItemBag.PopItem( pUseGoods->ustItemIndex, ustCount ) != ierr_Success )
                    return;
                break;
            case BT_MaterialBag:
                if( _MaterialItemBag.PopItem( pUseGoods->ustItemIndex, ustCount ) != ierr_Success )
                    return;
                break;
            case BT_TaskBag:
                if( _TaskItemBag.PopItem( pUseGoods->ustItemIndex, ustCount ) != ierr_Success )
                    return;
                break;
            default:
                return;
            }
        }
        pUseGoods->stItemCount = ustCount;
        GettheServer().SendMsgToSingle( pUseGoods, this );
    }
	else //??????????????????????CD??????????????????CD
	{
		pUseGoods->nRemainValue = pTargetItem->itembaseinfo.ustItemCount; //????????????????????????
		GettheServer().SendMsgToSingle( pUseGoods, this );
	}

    // 
    if ( GetStatus() == CS_IDLE && !HaveFighteFlag(eFighting) )
    { ChangeSubAction( CS_SubAction_Restore, -1 ); }
}

bool GamePlayer::_ProcessUsePetIdentifyItemToChar( MsgUseGoods* pUseGoods, SCharItem* pTargetItem, ItemDefine::SItemCommon* pTargetItemConfig )
{
    GameObjectId stDstPlayerId = pUseGoods->stDstChar;
    if ( stDstPlayerId == -1 )
        return false;
    BaseCharacter* pDstPlayer = GetTargetCanUseGood( stDstPlayerId, pTargetItemConfig->byUserTarget,pTargetItemConfig->ustItemID);
    if ( pDstPlayer == NULL )
    { return false; }

    unsigned short itemId = pTargetItem->itembaseinfo.ustItemID;

    if( pTargetItem->IsLock() )
    { return false;}

    ItemDefine::SItemOther* pOtherItemConfig = static_cast< ItemDefine::SItemOther* >( pTargetItemConfig );

	if (!AddPetIdentify( pOtherItemConfig->petType ))
	{
		return false;
	}    
 unsigned short ustCount = 1;
	//LYH????????
	switch ( pUseGoods->ucItemBagType )
	{
	case BT_NormalItemBag:
		{
			SCharItem * _item  = _NormalItemBag.GetItemByIndex(pUseGoods->ustItemIndex);
			if (_item)
			{
				theLogEventService.LogItemConsume(GetAccountID(),GetDBCharacterID(),_item->GetItemID(),ustCount,_item->GetItemGuid(),
					_item->GetItemCount()-ustCount>=0?_item->GetItemCount()-ustCount:0,eItemLogInfo_ItemConsume_Use,
					                              GetCharName(),pTargetItemConfig->GetItemName());
			}				
		}
		break;
	case BT_MaterialBag:
		{
			SCharItem * _item  = _MaterialItemBag.GetItemByIndex(pUseGoods->ustItemIndex);
			if (_item)
			{
				theLogEventService.LogItemConsume(GetAccountID(),GetDBCharacterID(),_item->GetItemID(),ustCount,_item->GetItemGuid(),
					_item->GetItemCount()-ustCount>=0?_item->GetItemCount()-ustCount:0,eItemLogInfo_ItemConsume_Use,
					                              GetCharName(),pTargetItemConfig->GetItemName());
			}
		}
		break;
	case BT_TaskBag:
		{
			SCharItem * _item  = _TaskItemBag.GetItemByIndex(pUseGoods->ustItemIndex);
			if (_item)
			{
				theLogEventService.LogItemConsume(GetAccountID(),GetDBCharacterID(),_item->GetItemID(),ustCount,_item->GetItemGuid(),
					_item->GetItemCount()-ustCount>=0?_item->GetItemCount()-ustCount:0,eItemLogInfo_ItemConsume_Use,
					                              GetCharName(),pTargetItemConfig->GetItemName());
			}
		}
		break;
	}

   
    switch ( pUseGoods->ucItemBagType )
    {
    case BT_NormalItemBag:
        if( _NormalItemBag.PopItem( pUseGoods->ustItemIndex, ustCount ) != ierr_Success )
            return false;
        break;
    case BT_MaterialBag:
        if( _MaterialItemBag.PopItem( pUseGoods->ustItemIndex, ustCount ) != ierr_Success )
            return false;
        break;
    case BT_TaskBag:
        if( _TaskItemBag.PopItem( pUseGoods->ustItemIndex, ustCount ) != ierr_Success )
            return false;
        break;
    default:
        return false;
    }
    
    pUseGoods->stItemCount = ustCount;
    GettheServer().SendMsgToSingle( pUseGoods, this );
	return true;
}

void GamePlayer::_ProcessUseItemToFriend( MsgUseGoods* pUseGoods, ItemBag* pItemBag, SCharItem* pTargetItem, ItemDefine::SItemCommon* pTargetItemConfig )
{
    if ( pUseGoods == NULL || pItemBag == NULL || pTargetItem == NULL || pTargetItemConfig == NULL )
    { return; }

    if ( pTargetItem->GetItemCount() < pUseGoods->stItemCount )
    { return; }

    if ( pTargetItemConfig->ucItemType != ItemDefine::ITEMTYPE_RESTORE )
    { return; }
    ItemDefine::SItemRestore* pItemRestore = static_cast< ItemDefine::SItemRestore* >( pTargetItemConfig );

    BaseCharacter* pTargetChar = theRunTimeData.GetCharacterByID( pUseGoods->stDstChar );
    if ( pTargetChar == NULL || !pTargetChar->IsPlayer() || !pTargetChar->IsInMapArea( GetMapID(), GetFloatX(), GetFloatY(), 10.f ) )
    { 
        MsgAckResult xAck;
        xAck.result = ER_UseItemMustInArea;
        xAck.value  = 10;
        SendMessageToClient( &xAck );
        return; 
    }

    if ( pTargetChar == this )
    { return; } // ??????????????

    GamePlayer* pTargetPlayer = static_cast< GamePlayer* >( pTargetChar );

    // ??????????????????????
    if ( !m_pRelation->HaveRelation( pTargetPlayer->GetDBCharacterID(), RelationDefine::Friend ) )
    { 
        MsgAckResult xAck;
        xAck.result = ER_UseItemOnlyFriend;
        SendMessageToClient( &xAck );
        return; 
    }

    bool bClear = false;
    if ( m_pRelation->HaveAddFriendlyTime( pTargetPlayer->GetDBCharacterID(), bClear ) )
    {
        MsgAckResult xAck;
        xAck.result = ER_UseItemToFriendTimeLimit;
        xAck.value  = 1;
        SendMessageToClient( &xAck );
        return; 
    }

    // ????????
    if ( m_pRelation->GetAddFriendlyTimeCount() >= 5 )
    {
        MsgAckResult xAck;
        xAck.result = ER_UseItemToFriendCountLimit;
        xAck.value  = 5;
        SendMessageToClient( &xAck );
        return; 
    }

    // ????????, ??????????????????????
    GameRelation* pTargetRelation = pTargetPlayer->GetRelation();
    if ( pTargetRelation == NULL )
    { return; }

    if ( !pTargetRelation->HaveRelation( RelationDefine::Friend ) )
    { 
        MsgAckResult xAck;
        xAck.result = ER_UseItemOnlyFriend;
        SendMessageToClient( &xAck );
        return; 
    }

    if( !m_RestoreColdDown.UseRestore( pTargetItem->itembaseinfo.ustItemID ))
    { return; }     // cd????

    uint32 nAddFriendly = pItemRestore->dwAddExp * pUseGoods->stItemCount;
    UpdateFriendly( pTargetPlayer->GetDBCharacterID(), RelationDefine::UpdateAddFriendly, nAddFriendly );
    pTargetPlayer->UpdateFriendly( GetDBCharacterID(), RelationDefine::UpdateAddFriendly, nAddFriendly );

    // ??????????
    m_pRelation->SendAddFriendlyTimeMessage( pTargetPlayer->GetDBCharacterID(), bClear );

    // ??????????, ????????
    MsgShowViewUseItemToPlayer xShowView;
    xShowView.stSrcPlayerID  = GetID();
    xShowView.stDestPlayerID = pTargetPlayer->GetID();
    xShowView.ustItemID      = pTargetItem->GetItemID();
    GettheServer().SendMsgToView( &xShowView, GetID(), false );

    // ???????????????????? ??????????????
    if ( pTargetItemConfig->ustLevel >= eIL_Nonsuch && pUseGoods->stItemCount == pTargetItemConfig->nStackNum )
    {
        MsgShowAllUseItemToPlayer xShowAll;
        HelperFunc::SafeNCpy( xShowAll.szSrcPlayerName, GetCharName(), sizeof( xShowAll.szSrcPlayerName ) );
        HelperFunc::SafeNCpy( xShowAll.szDestPlayerName, pTargetPlayer->GetCharName(), sizeof( xShowAll.szDestPlayerName ) );
        xShowAll.xCharItem = *pTargetItem;
        GettheServer().SendMsgToWorld( &xShowAll, true );
    }

    pItemBag->ClearItem( pUseGoods->ustItemIndex, pUseGoods->stItemCount );
    Log( theXmlString.GetString( eLog_UseItemToFriend ), pTargetRelation->GetName(), pItemRestore->GetItemName(), pUseGoods->stItemCount, nAddFriendly );

    SendMessageToClient( pUseGoods );       // ????????????
}

// ??????????????
void GamePlayer::ClearCharRunTimeData()
{
}

int IsLeapYear(int y)
{   
    if(y%400==0||(y%4==0&&y%100!=0))   
    { return 1; }
    return 0;   
}

int MonthDay( int y, int m)
{
    int data[] = { 31,28+IsLeapYear(y),31,30,31,30,31,31,30,31,30};  
    return data[m-1];   
}   

int DayInYear( int y, int m, int d)
{   
    int sum = d;   
    for(int i=1; i<m; ++i)
    {
        sum += MonthDay(y,i);   
    }   
    return sum;   
}   

int SubDate( int y1, int m1, int d1,int y2, int m2,int d2)
{   
    int sum = DayInYear(y1,m1,d1)-DayInYear(y2,m2,d2);   
    if(y1!=y2)
    {   
        for( int i=y2; i<y1; ++i)
        {
            sum+=365+IsLeapYear(i);   
        }   
    }   
    return sum;
} 

// ????????
long GamePlayer::DistanceNowTime( unsigned char year, unsigned char month, unsigned char day, unsigned char hour, unsigned char minute )
{
    // ????????
    SYSTEMTIME systime;
    GetLocalTime( &systime );
    const short yearBase = 2000;
    unsigned char nCurYear   = systime.wYear - yearBase;
    unsigned char nCurMonth  = systime.wMonth;
    unsigned char nCurDay    = systime.wDay;
    unsigned char nCurHour   = systime.wHour;
    unsigned char nCurMinute = systime.wMinute;

    // ??????????????????
    bool bLessTime = false;
    if ( year < nCurYear )
    {   
        bLessTime = true;
    }
    else
    {
        if ( month < nCurMonth )
        {
            bLessTime = true;
        }
        else
        {
            if ( day < nCurDay )
            {
                bLessTime = true;
            }
            else
            {
                if ( hour < nCurHour)
                {
                    bLessTime = true;
                }
                else
                {
                    if ( minute < nCurMinute )
                    {
                        bLessTime = true;
                    }
                }
            }
        }
    }

    int subDay = 0;
    if ( bLessTime )
    { // (((nCurYear-year) * 12 + nCurMonth - month) * 31 + nCurDay - day)
        subDay = SubDate( nCurYear+yearBase, nCurMonth, nCurDay, year+yearBase, month, day); 
        return -(( subDay * 24 + nCurHour - hour) * 60 + nCurMinute - minute);
    }
    else
    { // (((year-nCurYear) * 12 + month - nCurMonth) * 31 + day - nCurDay )
        subDay = SubDate( year+yearBase, month, day, nCurYear+yearBase, nCurMonth, nCurDay );
        return ( subDay * 24 + hour - nCurHour ) * 60 + minute - nCurMinute;
    }
}

bool GamePlayer::IsExpired( int nVarId, int keyHour, int keyMinute, int minDuration  )
{
    if ( nVarId < VarTimeBeginRange || nVarId>VarTimeEndRange-1)
        return false;

    unsigned short low  = GetVar( nVarId );
    unsigned short high = GetVar( nVarId + 1);
    unsigned long dwLastTime = MAKELONG( low, high);

    // ??????????????
    unsigned char Year   = (dwLastTime>>20) & 0xFFF;  // 12  1024
    unsigned char Month  = (dwLastTime>>16) & 0xF;    //  4  16
    unsigned char Day    = (dwLastTime>>11) & 0x1F;   //  5  32
    unsigned char Hour   = (dwLastTime>>6)  & 0x1F;   //  5  32
    unsigned char Minute = (dwLastTime>>0)  & 0x3F;   //  6  64

    // ????????
    SYSTEMTIME systime;
    GetLocalTime( &systime );
    unsigned char nCurYear   = systime.wYear - 2000;
    unsigned char nCurMonth  = systime.wMonth;
    unsigned char nCurDay    = systime.wDay;
    unsigned char nCurHour   = systime.wHour; 
    unsigned char nCurMinute = systime.wMinute;     

    long recordTimeDistance = DistanceNowTime( Year, Month, Day, Hour, Minute );    
    if ( recordTimeDistance > 0)
    { // ?????????? ???? ???????? ????????????????????
        SetVar( nVarId,   0 );
        SetVar( nVarId+1, 0 );
        return false;
    }

    if ( abs(recordTimeDistance)> 24 * 60 && abs(recordTimeDistance) >= minDuration )
    { // ????????????
        //Log("???????????? ????????????[%d][%d:%d:%d:%d:%d][%d:%d:%d]", nVarId, Year, Month, Day, Hour, Minute,keyHour, keyMinute, minDuration);
        return true;
    }

    long keyTimeDistance = DistanceNowTime( nCurYear, nCurMonth, nCurDay, keyHour, keyMinute );
    if ( keyTimeDistance < 0) 
    { // ????????????????KeyTime
        if ( abs(recordTimeDistance) > abs(keyTimeDistance) && abs(recordTimeDistance) >= minDuration )
        {
            //Log("???????????????? ????????????[%d][%d:%d:%d:%d:%d][%d:%d:%d]", nVarId, Year, Month, Day, Hour, Minute,keyHour, keyMinute, minDuration);
            return true;
        }
    }

    if ( Year==0 && nCurMonth==0) 
    { // ??????????
        /*Log("?????????? ????????????[%d][%d:%d:%d:%d:%d][%d:%d:%d]", nVarId, Year, Month, Day, Hour, Minute,
            keyHour, keyMinute, minDuration);*/

		Log(theXmlString.GetString(eServerLog_NOrecord), nVarId, Year, Month, Day, Hour, Minute,
			keyHour, keyMinute, minDuration);

        return true;
    }
    return false;
}

unsigned long GamePlayer::GetRecordSystemTime()
{
    SYSTEMTIME systime;
    GetLocalTime( &systime );
    unsigned char nYear   = systime.wYear - 2000; // 12  1024
    unsigned char nMonth  = systime.wMonth;       //  4  16
    unsigned char nDay    = systime.wDay;         //  5  32
    unsigned char nHour   = systime.wHour;        //  5  32
    unsigned char nMinute = systime.wMinute;      //  6  64    

    return (nYear<<20)|(nMonth<<16)|(nDay<<11)|(nHour<<6)|(nMinute<<0);
}

bool GamePlayer::RecordTimeVar( int nVarId )
{
    if ( nVarId < VarTimeBeginRange || nVarId>VarTimeEndRange-1)
        return false;

    unsigned long dwTime = GetRecordSystemTime();

    unsigned short low  = LOWORD( dwTime );
    unsigned short high = HIWORD( dwTime );

    SetVar( nVarId,   low );
    SetVar( nVarId+1, high );

    //Log("???????? [%d][%d:%d:%d:%d:%d][0x%x]", nVarId, nYear, nMonth, nDay, nHour, nMinute, dwTime);
    return true;
}

void GamePlayer::SetRunTimePetInfo( RunTimePetInfo &xPetInfo, MonsterBaseEx* pAiPet, int nSummonSkillID, int nPetIndex )
{
    if ( pAiPet == NULL )
    { return; }

    xPetInfo.nPetID   = pAiPet->GetMonsterID(); // ??????????????
    xPetInfo.nHp      = pAiPet->GetHP();
    xPetInfo.nMp      = pAiPet->GetMP();
    xPetInfo.varValue = pAiPet->GetVarID();
    xPetInfo.nPetIndex= nPetIndex;
    xPetInfo.nSummonSkillID = nSummonSkillID;
	if(pAiPet->GetObjType() == Object_MonsterProtected)
	{
		xPetInfo.IsCanRide = ((MonsterProtectedEx*)pAiPet)->IsCanRide();
	}
	else
		xPetInfo.IsCanRide = false;
    memset( xPetInfo.sCharBodyStatus, 0, sizeof(xPetInfo.sCharBodyStatus) );
    for (int nloop = 0; nloop < BodyStatusType_Max; ++nloop)
    {
        SCharBuff* pBodyStatus = pAiPet->_buffManager.GetBuff( nloop );
        if ( !pBodyStatus )
        { continue; }

        memcpy(&xPetInfo.sCharBodyStatus[nloop], pBodyStatus, sizeof(SCharBuff) );
        xPetInfo.sCharBodyStatus[nloop].masterId = -1;
        xPetInfo.sCharBodyStatus[nloop].dwPreDamage = HQ_TimeGetTime();
    }
}

long GamePlayer::ProcessSkillAboutPetModule( const ItemDefine::SItemSkill* pSkill, SAttackTarget* pTarget )
{
    if ( !pSkill )
    { return ER_NullPointer; }

    if (pSkill->bIsCatchNurturePet)
    {// ????????
        if ( _petManager.IsPetFull() )
        {
            SendErrorToClient( ER_PetNumIsFull );
            return ER_Failed;
        }

        BaseCharacter*  pTargetChar = theRunTimeData.GetCharacterByID(pTarget->nCharID);
        if(  pTargetChar == NULL )
        { return ER_NullPointer; } 

        if ( !pTargetChar->IsMonster() )
        { return ER_Failed; }

        MonsterBaseEx* pMonsterChar = static_cast< MonsterBaseEx* > ( pTargetChar );

        int monsterId = pMonsterChar->GetMonsterID();
        ItemDefine::SMonster* pMonsterConfig = GettheItemDetail().GetMonsterById( monsterId );
        if ( pMonsterConfig == NULL )
        { return ER_NullPointer; } 

        int petId = pMonsterConfig->nCatchPetID;
        ItemDefine::SPetMonster* pPetConfig = GettheItemDetail().GetPetById( petId );
        if ( pPetConfig == NULL )
        { return ER_NullPointer; } 

        if ( pSkill->ustLevel < pPetConfig->catchLevel )
        {
            SendErrorToClient( ER_CatchSkillLevel );
            return ER_Failed;
        }

        SPetIdentify* pPetIdentify = GetPetIdentify( pPetConfig->petType );
        if ( pPetIdentify == NULL )
        {
            SendErrorToClient( ER_PetIdentify );
            return ER_Failed;
        }

        int nSkillCatchRate  = thePetSettingConfig.GetSkillCatchRate( pPetConfig->catchLevel, pSkill->ustLevel );
        int nHPCatchRate     = thePetSettingConfig.GetHPCatchRate( pTargetChar->GetHP() * DEF_PER_INT / pMonsterConfig->nHPMax );
        int nSelfStatusRate  = _buffManager.GetAddCatchPetRate();
        int nTargetStatusRate= pTargetChar->_buffManager.GetAddCatchPetRate();
        float fAddRateMod    = ( 1.0f + nSelfStatusRate / PET_CATCH_PROBABILITY + nTargetStatusRate / PET_CATCH_PROBABILITY 
            + nHPCatchRate / PET_CATCH_PROBABILITY + nSkillCatchRate / PET_CATCH_PROBABILITY );

        int nFinalCatchRate  = pMonsterConfig->nCatchBaseRate * fAddRateMod;

        if ( theRand.rand32() % PET_CATCH_PROBABILITY > nFinalCatchRate )
        {
            SendErrorToClient( ER_PetCatchFail );
            return ER_Failed; 
        } 

        AddPet( petId , pMonsterConfig->nPetQuality, theRand.rand16() % Sex_Max, 0, EPetSource_Skill );
        OperateRecipeSkillPoint( EOT_Add, pSkill->ustItemID, pMonsterChar->GetRewardSkillExp(), __FUNCTION__ , __LINE__ );
        pMonsterChar->CharacterMurder();

        return ER_SuccessBreak;
    }

    if (pSkill->iskillpet)
    { // ??????????PET?????????? 
        // ??????????????????
        KillSummonPet(pSkill->ustItemID);
    }

    if( pSkill->bSummonSkill && !pSkill->bIsAfterIllusion && !IsSummonPetFull() )
    { // ??????????????

        if ( IsSummonPetFull() )
        { return ER_Success; }

        // ??????????????????
        KillSummonPet( pSkill->ustItemID );

        ItemDefine::SMonster* pMonsterConfig = GettheItemDetail().GetMonsterById( pSkill->nSummonMonsterId );
        if ( pMonsterConfig == NULL )
        { return ER_Failed; }

        MonsterCreateData xCreateData;
        xCreateData.SetMapID( GetMapID() );
        xCreateData.SetPostionX( GetFloatX() );
        xCreateData.SetPostionY( GetFloatY() );
        xCreateData.SetDirX( GetDirX() );
        xCreateData.SetDirY( GetDirY() );
        xCreateData.SetMonsterID( pSkill->nSummonMonsterId );

        MonsterBaseEx* pMonster = NULL;
        switch ( pMonsterConfig->stMonsterType )
        {
        case eMT_Trap:
            {
                pMonster = MonsterCreater::CreatePetTrapMonster( xCreateData, this );
            }
            break;
        default:
            {
                xCreateData.SetPostionX( GetFloatX() + 2.0f );
                xCreateData.SetPostionY( GetFloatY() + 2.0f );
                pMonster = MonsterCreater::CreatePetSummonMonster( xCreateData, this );
            }
            break;
        }

        if ( pMonster != NULL )
        {
            SSummonPet pet;
            pet.petId = pMonster->GetID();
            pet.petAIType = ePetAttackAI;
            pet.skillId = pSkill->ustItemID;
            AddSummonPet(pet);
        }

        return ER_SuccessBreak;
    }

    MonsterBaseEx* pSummonPet  = GetMonsterSummonPet();
    MonsterBaseEx* pNurturePet = _petManager.GetMonsterNurturePet();

    if ( pSkill->ispettouseskill && pSummonPet != NULL && pSummonPet->IsPet() )
    { // ????????????????????
        ItemDefine::SItemSkill* pPetSkill = GettheItemDetail().GetSkillByID(pSkill->ustPetSkillID,pSkill->ustPetSkillLevel);
        if ( pPetSkill != NULL )
        {
            MonsterBaseEx* pMonsterPet = static_cast< MonsterBaseEx*>( pSummonPet );

            pMonsterPet->ProcessLockTarget( GetLockID() );
            pMonsterPet->SetUseSkill( pSkill->ustPetSkillID, pSkill->ustPetSkillLevel );
        }

        return ER_SuccessBreak;
    }
    
    if ( pSkill->sSkillCategory == ItemDefine::SCT_PetMasterManualControl || pSkill->sSkillCategory == ItemDefine::SCT_PetMasterAutoUnControl )
    {
        if ( pNurturePet != NULL && pNurturePet->IsPet() )
        {
            MonsterBaseEx* pMonsterPet = static_cast< MonsterBaseEx*>( pNurturePet );

            pMonsterPet->ProcessLockTarget( GetLockID() );
            pMonsterPet->SetUseSkill( pSkill->ustPetSkillID, pSkill->ustPetSkillLevel );
        }

        return ER_SuccessBreak;
    }

    return ER_Success;
}


long GamePlayer::ProcessAfterIllusionModule( const ItemDefine::SItemSkill* pSkill, SAttackTarget* pTarget )
{
    if ( !pSkill || !pTarget)
    {  return ER_NullPointer; }

    if( pSkill->bIsAfterIllusion )
    { // ??????????????

        if ( IsSummonPetFull() )
        { 
            MsgUseSkillHintMessage HintMsg;
            HintMsg.header.stID = GetID();
            HintMsg.shHintId    = MsgUseSkillHintMessage::eSkillTargetWrong;
            GettheServer().SendMsgToSingle( &HintMsg, this );
            return ER_Failed; 
        }

        BaseCharacter* pTargetChar = theRunTimeData.GetCharacterByID( pTarget->nCharID );
        if( pTargetChar == NULL )
        { return ER_NullPointer; } 

        // ??????????????????
        KillSummonPet(pSkill->ustItemID);

        int index = GettheItemDetail().FindMonsterIndexById( pSkill->nSummonMonsterId );
        if( index < 0 )
        { return ER_Failed; }

        // ??????????
        MonsterCreateData xCreateData;
        xCreateData.SetMapID( pTargetChar->GetMapID() );
        xCreateData.SetPostionX( pTargetChar->GetFloatX() + 1.0f );
        xCreateData.SetPostionY( pTargetChar->GetFloatY() + 1.0f );
        xCreateData.SetDirX( pTargetChar->GetDirX() );
        xCreateData.SetDirY( pTargetChar->GetDirY() );
        xCreateData.SetMonsterID( pSkill->nSummonMonsterId );
        MonsterBaseEx* pMonster = MonsterCreater::CreatePetIllusionMonster( xCreateData, this );
        if ( pMonster == NULL )
        { return ER_Failed; }

        SSummonPet pet;
        pet.petId = pMonster->GetID();
        pet.petAIType = ePetAttackAI;
        pet.skillId = pSkill->ustItemID;

        AddSummonPet(pet);
        return ER_SuccessBreak;
    }

    return ER_Failed;
}

bool GamePlayer::TryPassivenessTriggerAttack()
{
    TrySelfPassivenessTriggerAttack() ;
    //TryMountPassivenessTriggerAttack();
    return true;
}

bool GamePlayer::TrySelfPassivenessTriggerAttack()
{
	bool buff_change_self = false;
	bool buff_change_target = false;

	BaseCharacter* pTarget = theRunTimeData.GetCharacterByID( m_nLockID );

    for( int iLoop=0; iLoop<_SkillBag.GetSkillNum(); ++iLoop )
    {
        SCharSkill* pCharSkill = _SkillBag.GetSkillByIndex( iLoop );        
        if ( pCharSkill == NULL )
        { continue; }

        ItemDefine::SItemSkill* pSkill = GettheItemDetail().GetSkillByID( pCharSkill->ustSkillID, pCharSkill->stSkillLevel );                
        if( pSkill == NULL )
        { continue; }

        if ( pSkill->stGeneralType != ItemDefine::generaltype_trigger )
        { // ????????????????????
            continue;
        }

        if (!pSkill->arrayProfessionReq[GetProfession()])
        { continue; }

        int actionRatio = theRand.rand32() % RAND_THOUSAND;
        if ( actionRatio > pSkill->actionRatio )
        { continue; }

        if ( pSkill->bNeedWeapon )
        { // ????????
            SCharItem* pCharItem = GetVisualEquipItem( EEquipPartType_Weapon );
            if ( NULL == pCharItem)
            { continue; }

            ItemDefine::SItemCommon* pItemWeaponCommon = GettheItemDetail().GetItemByID(pCharItem->itembaseinfo.ustItemID);
            if ( NULL == pItemWeaponCommon || pItemWeaponCommon->ucItemType != ItemDefine::ITEMTYPE_WEAPON )
            { continue; }

            ItemDefine::SItemWeapon* pItemWeaponRhand = (ItemDefine::SItemWeapon*)pItemWeaponCommon;
            if ( NULL == pItemWeaponRhand )
            { continue; }

            if ( pSkill->stWeaponNeed != -1 && pSkill->stWeaponNeed != pItemWeaponRhand->stWeaponType )
            { continue; }
        }
        
        ItemDefine::SItemStatus* pStatus = GettheItemDetail().GetStatusBySkill( pSkill );           
        if( pStatus == NULL )
        { continue; }

        if ( pStatus->bAvail )
        {// ??????????
			if (GLR_Success == ApplyBufferStatus( pStatus->ustItemID, pStatus->ustLevel, GetID(), SCharBuff::StatusEventType_Skill, pSkill->ustItemID ))
			{
				buff_change_self = true;
			}
        }
        else
        {// ??????????
            
            if ( pTarget == NULL )
            { continue; }

			if (GLR_Success == pTarget->ApplyBufferStatus( pStatus->ustItemID, pStatus->ustLevel, GetID(), SCharBuff::StatusEventType_Skill, pSkill->ustItemID ))
			{	
				buff_change_target = true;
			}
        }
    }

	if (pTarget&&buff_change_target)
	{
		pTarget->OnBuffStatusChanged( true );
	}
	if (buff_change_self)
	{
		OnBuffStatusChanged( true );
	}

    return true;
}

bool GamePlayer::TryMountPassivenessTriggerAttack()
{
    if ( _mountManager.GetActiveMountId() > 0 )
    {
        for ( int i=0; i< SMountItem::MICD_MaxSkillCount; ++i )
        {
            SCharSkill* pMountSkill = _mountManager._activeSkillBag.GetSkillByIndex( i );
            if ( pMountSkill == NULL || pMountSkill->ustSkillID == InvalidLogicNumber )
            { continue; }

            ItemDefine::SItemSkill* pSkillConfig = GettheItemDetail().GetSkillByID(pMountSkill->ustSkillID, pMountSkill->stSkillLevel);
            if( pSkillConfig == NULL )
            { continue; }

            if ( pSkillConfig->sSkillCategory != ItemDefine::SCT_MountMasterInitiativeUnControl )
            { continue; }

            if (!pSkillConfig->arrayProfessionReq[GetProfession()])
            { continue; }

            // ????????????
            //if ( pSkillConfig->normalAttackRatio > 0 )
            //{
            //    int nRandRatio = theRand.rand32() % RAND_NUM;
            //    if( nRandRatio < pSkillConfig->normalAttackRatio )
            //    {
            //        //TryNormalAttack();
            //        int nNormalSkillId = GetNormalAttackSkillId(m_iAttackHand);
            //        ItemDefine::SItemSkill* pNormalSkill = GettheItemDetail().GetSkillByID(nNormalSkillId, 1);
            //        if ( pNormalSkill == NULL )
            //        { continue; }

            //        SAttackTarget target;
            //        target.bIsCharTarget = true;
            //        target.nCharID       = GetLockID();
            //        ProcessNormalSkill( &target, pNormalSkill, this );
            //    }
            //    continue;
            //}

            int actionRatio = theRand.rand32() % RAND_THOUSAND;
            if ( actionRatio > pSkillConfig->actionRatio )
            { continue; }

            SAttackTarget target;
            target.bIsCharTarget = false;
            target.nCharID       = GetID();
            target.vPos          = GetPos();

            bool bCanAttack = false;
            switch ( pSkillConfig->shCastType )
            {
            case ItemDefine::casttype_singletarget:
            case ItemDefine::casttype_AOETargetcirclearea: // ??????????????????????????????
                {
                    target.bIsCharTarget = true;

                    switch( pSkillConfig->ustCastTarget )
                    {
                    case ItemDefine::casttarget_me:
                        {   
                            target.nCharID = GetID();
                            bCanAttack     = true;
                        }
                        break;
                    default:
                        if ( m_nLockID != -1)
                        {
                            target.nCharID = m_nLockID;
                            bCanAttack     = true;
                        }
                        break;
                    }
                }
                break;
            case ItemDefine::casttype_AOEcircleself            : // ?????????????????????????? *
            case ItemDefine::casttype_AOEquartercirlcefrontage : // ????90????????????????     *
            case ItemDefine::casttype_AOEhalfcirclefrontage    : // ????180????????????????
            case ItemDefine::casttype_AOEquartercirlcebackage  : // ????90????????????????
            case ItemDefine::casttype_AOEhalfcirclebackage     : // ????180????????????????
                {
                    bCanAttack = true;
                }
                break;
            default:
                break;
            }

            if( _mountManager._activeSkillBag.IsSkillCoolDownById( pMountSkill->ustSkillID ) )
            { bCanAttack = false; }

            if ( bCanAttack )
            {   
                CDTIME cdResult = StartSkillCoolDown( pMountSkill->ustSkillID, pMountSkill->stSkillLevel );
                SkillDischarge( &target, pMountSkill->ustSkillID, pMountSkill->stSkillLevel, this );
            }
        }
    }

    return true;
}

void GamePlayer::TellTeamInfoChange( char positon )
{
    MsgTellTeamInfo msg;
    msg.charId       = GetID();
    msg.teamId       = GetTeamID();
    msg.teamPosition = positon;
    GettheServer().SendMsgToView( &msg, GetID(), true);
}

void GamePlayer::SetBanSpeakTime( unsigned int dwTime, bool bSendToClient /* = false */ )
{
    m_nBanSpeakTime = dwTime;

    if ( bSendToClient )
    {
        MsgAckResult xResult;           // ???????????????? 
        xResult.result = ER_BanSpeakTime;
        xResult.value  = ( GetBanSpeakTime() + 59999 ) / 60000;                   // ??????????????
        GettheServer().SendMsgToSingle( &xResult, this );
    }
}

bool GamePlayer::IsCanHighShout()
{
    if ( !g_Cfg.bHighShoutTimeLimit )           // ????????
    { return true; }

    if ( GetLevel() < g_Cfg.nHighShoutLevelLimit )          // ????????????
    { return false; }

    if ( gCharInfoServer.otherdata.dwHighShoutCDTime > g_Cfg.nHighShoutPerTime )
    { gCharInfoServer.otherdata.dwHighShoutCDTime = 0; }    // ????????

    MsgAckResult xResult;     

    // ????????????????????????
	// ?????????????? vvx 2013.6.14
    //if ( !m_pCountry->IsHaveRight( CountryDefine::Right_WorldSpeak, GetDBCharacterID() ) )
    //{
    //    if ( GetJiaoZiMoney() < g_Cfg.nHighShoutCostMoney )
    //    { 
    //        xResult.result = ER_HighShoutNotEnoughMoney;
    //        xResult.value  = g_Cfg.nHighShoutCostMoney;
    //        SendMessageToClient( &xResult );
    //        return false; 
    //    }

    //    OperateJiaoZi( EOT_Sub, g_Cfg.nHighShoutCostMoney, true, __FUNCTION__, __LINE__ );       // ????
    //}

    xResult.result = ER_HighShoutTimeLimitFail;
    if( gCharInfoServer.otherdata.dwHighShoutCDTime == 0 )
    {
        // AddCurrentHighShoutCount(1);        // ????????????
        gCharInfoServer.otherdata.dwHighShoutCDTime = g_Cfg.nHighShoutPerTime;      // ????????????????

        xResult.result = ER_HighShoutTimeLimitSuccess;
    }

    // ???????????????? ( ??????????????????????,?????????????? )
    xResult.value  = gCharInfoServer.otherdata.dwHighShoutCDTime;           // ????
    GettheServer().SendMsgToSingle( &xResult, this );

    return xResult.result == ER_HighShoutTimeLimitSuccess;
}

float GamePlayer::GetKillMonsterModulus()
{
    if ( RecordTime::CheckRecordTime( gCharInfoServer.otherdata.dwRecordKillMonsterTime ) )
    {
        ClearRecordKillMonsterCount();
        RecordTime::SaveRecordTime( gCharInfoServer.otherdata.dwRecordKillMonsterTime );
    }

    return theKillMonsterCountConfig.GetModulus( GetRecordKillMonsterCount() );
}

// ????15?? ????????
void GamePlayer::EnterLuckReward()
{
    LuckReward* pLuckReward = GetLuckReward( GetTeamID() != TeamDefine::NoneSessionID );
    if ( pLuckReward != NULL )
    { return; }         // ???????? ??????

    pLuckReward = LuckReward::CreateLuckReward();
    if ( pLuckReward == NULL )
    { return; }

    if ( GetTeamID() != TeamDefine::NoneSessionID )
    {
        pLuckReward->SetID( GetTeamID() );
        theTeamLuckRewardManager.AddLuckReward( pLuckReward->GetID(), pLuckReward );
    }
    else
    {
        pLuckReward->SetID( GetDBCharacterID() );
        theCharLuckRewardManager.AddLuckReward( pLuckReward->GetID(), pLuckReward );
    }
}

void GamePlayer::UpdateLuckReward( int nType )            // ????????15??????
{
    LuckReward* pLuckReward = GetLuckReward( GetTeamID() != TeamDefine::NoneSessionID );
    if ( pLuckReward == NULL )
    { return; }

    pLuckReward->SetMapID( GetMapID() );                                // ????????
    pLuckReward->SetFloatX( GetFloatX() );
    pLuckReward->SetFloatY( GetFloatY() );
    pLuckReward->SetTimeOut( ECD_LuckReward_TimeOut );                  // ????????????????,????????????
    switch ( nType )
    {
    case 0:     // ????????????
        pLuckReward->SetCanPlay( false );
        pLuckReward->SetHasPlay( false );
        pLuckReward->SetIsLucking( false );
        pLuckReward->SetRewardType( ECD_RandType_Init );
        break;
    case 1:
        pLuckReward->SetCanPlay( true );
        ShowRandLuckReward( pLuckReward, GetTeamID() != TeamDefine::NoneSessionID );         // ??????????????,????????????????????????
        break;
    case 2:
        pLuckReward->SetCanPlay( true );
        ShowReceiveLuckReward( pLuckReward, GetTeamID() != TeamDefine::NoneSessionID );      // ??????????????????????
        break;
    default:
        break;
    }
}

bool GamePlayer::IsCanLuckReward()
{
    LuckReward* pLuckReward = GetLuckReward( GetTeamID() != TeamDefine::NoneSessionID );
    if ( pLuckReward == NULL )
    { return false; }

    return pLuckReward->IsCanLuckReward();
}

bool GamePlayer::IsCanNextLuckLevel()
{
    LuckReward* pLuckReward = GetLuckReward( GetTeamID() != TeamDefine::NoneSessionID );
    if ( pLuckReward == NULL )
    { return false; }

    return pLuckReward->IsCanNextLuckLevel();
}

bool GamePlayer::IsCanAcceptQuest( unsigned char uchLevel )
{
    LuckReward* pLuckReward = GetLuckReward( GetTeamID() != TeamDefine::NoneSessionID );
    if ( pLuckReward == NULL )
    { return false; }

    return pLuckReward->IsCanAcceptQuest( uchLevel );
}

bool GamePlayer::IsCanReceiveReward()
{
    LuckReward* pLuckReward = GetLuckReward( GetTeamID() != TeamDefine::NoneSessionID );
    if ( pLuckReward == NULL )
    { return false; }

    return pLuckReward->IsCanGetReward();
}

void GamePlayer::SetCanLuckReward()
{
    LuckReward* pLuckReward = GetLuckReward( GetTeamID() != TeamDefine::NoneSessionID );
    if ( pLuckReward == NULL )
    { return; }

    pLuckReward->SetCanPlay( true );
}

bool GamePlayer::IsInLuckReward()
{
    if ( GetTeamID() != TeamDefine::NoneSessionID )
    {
        return theTeamLuckRewardManager.IsInLuckReward( GetTeamID() );
    }

    return theCharLuckRewardManager.IsInLuckReward( GetDBCharacterID() );
}

LuckReward* GamePlayer::GetLuckReward( bool bIsTeam )
{
    LuckReward* pLuckReward = NULL;
    if ( bIsTeam )
    {
        pLuckReward = theTeamLuckRewardManager.GetLuckReward( GetTeamID() );
    }
    else
    {
        pLuckReward = theCharLuckRewardManager.GetLuckReward( GetDBCharacterID() );
    }

    return pLuckReward;
}

int GamePlayer::GetLuckRewardLevel( bool bCheckType /* = false */ )
{
    LuckReward* pLuckReward = GetLuckReward( GetTeamID() != TeamDefine::NoneSessionID );
    if ( pLuckReward == NULL )
    { return 0; }

    if ( bCheckType )
    {
        if ( pLuckReward->GetRewardType() == ECD_RandType_Leave )
        { return 0; }
    }

    return pLuckReward->GetLevel();
}

void GamePlayer::ShowReceiveLuckReward( LuckReward* pLuckReward, bool bIsTeam )
{
    if ( pLuckReward == NULL || !pLuckReward->IsCanGetReward())
    { return; }

    // ????????????????
    pLuckReward->SetMapID( GetMapID() );
    pLuckReward->SetFloatX( GetFloatX() );
    pLuckReward->SetFloatY( GetFloatY() );

    if ( bIsTeam )
    {
        theTeamLuckRewardManager.ShowLuckReward( pLuckReward, MsgTellLuckReward::ECD_Operator_ShowReward );
    }
    else
    {
        theCharLuckRewardManager.ShowLuckReward( pLuckReward, MsgTellLuckReward::ECD_Operator_ShowReward );
    }
}

void GamePlayer::ProcessReceiveLuckReward( LuckReward* pLuckReward, bool bIsTeam, bool bReceive )
{
    if ( bIsTeam )
    {
        theTeamLuckRewardManager.ProcessReceiveLuckReward( pLuckReward, bReceive );
    }
    else
    {
        theCharLuckRewardManager.ProcessReceiveLuckReward( pLuckReward, bReceive );
    }
}

void GamePlayer::RunLuckReward( LuckReward* pLuckReward, bool bIsTeam )
{
    if ( bIsTeam )
    {
        theTeamLuckRewardManager.RunLuckReward( pLuckReward );
    }
    else
    {
        theCharLuckRewardManager.RunLuckReward( pLuckReward );
    }
}

// ??????????????,????????????
void GamePlayer::ShowRandLuckReward( LuckReward* pLuckReward, bool bIsTeam )
{
    if ( bIsTeam )
    {
        theTeamLuckRewardManager.ShowLuckReward( pLuckReward, MsgTellLuckReward::ECD_Operator_ShowLuck );
    }
    else
    {
        theCharLuckRewardManager.ShowLuckReward( pLuckReward, MsgTellLuckReward::ECD_Operator_ShowLuck );
    }
}

void GamePlayer::StartLuckReward( LuckReward* pLuckReward, bool bIsTeam )
{
    if ( bIsTeam )
    {
        theTeamLuckRewardManager.StartLuckReward( pLuckReward );
    }
    else
    {
        theCharLuckRewardManager.StartLuckReward( pLuckReward );
    }
}

void GamePlayer::SetLuckSummonCount( unsigned short ustCount )
{
    LuckReward* pLuckReward = GetLuckReward( GetTeamID() != TeamDefine::NoneSessionID );
    if ( pLuckReward == NULL )
    { return; }

    pLuckReward->SetSummonCount( ustCount );
}

unsigned short GamePlayer::GetLuckSummonCount()
{
    LuckReward* pLuckReward = GetLuckReward( GetTeamID() != TeamDefine::NoneSessionID );
    if ( pLuckReward == NULL )
    { return 0xFFFF; }

    return pLuckReward->GetSummonCount();
}

// ????????????
void GamePlayer::ShowTreasureBox()
{
    if ( !CheckUseItemValid() )
    { return; }

    ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( m_xUseItemInfo.stItemID );
    if ( pItemCommon == NULL || pItemCommon->ucItemType != ItemDefine::ITEMTYPE_TREASUREBOX )
    { return; }

    ItemDefine::SItemTreasureBox* pItemTreasure = static_cast< ItemDefine::SItemTreasureBox* >( pItemCommon );
    if ( pItemTreasure == NULL || ( pItemTreasure->uchBoxType != ItemDefine::SItemTreasureBox::BoxType_Luck && pItemTreasure->uchBoxType != ItemDefine::SItemTreasureBox::BoxType_Receive ) )
    { return; }

    SCharItem xCharItem;
    if ( m_xUseItemInfo.pItemBag == NULL || !m_xUseItemInfo.pItemBag->GetItem( m_xUseItemInfo.stIndex, &xCharItem ) )
    { return; }

    if ( xCharItem.itembaseinfo.ustItemID != m_xUseItemInfo.stItemID || xCharItem.itembaseinfo.nOnlyInt != m_xUseItemInfo.nGuid )
    { return; }

    // ??????????????????????
    MsgShowTreasureBox xShow;
    xShow.ucItemBagType = m_xUseItemInfo.uchItemBagType;
    xShow.stIndex       = m_xUseItemInfo.stIndex;
    xShow.nGuid         = m_xUseItemInfo.nGuid;
    xShow.uchLevel      = pItemTreasure->uchLevel;

    // ?????? value1 ???? ( ?????????? )
    if ( xCharItem.itembaseinfo.value1 == 0 )
    {
        xShow.uchOperate = MsgShowTreasureBox::ECD_Type_Init;
    }
    else/* ( xCharItem.itembaseinfo.value1 != 0 )*/
    {
        xShow.uchOperate   = MsgShowTreasureBox::ECD_Type_Receive;
        xShow.uchLevel     = xCharItem.itembaseinfo.value1;
        xShow.nResultIndex = xCharItem.itembaseinfo.value2;
    }

    SendMessageToClient( &xShow );
}

/////////////////////////////////////////////////////////////////////////////////////////
// ????????????????????
bool GamePlayer::ProcessSendCheckCheatData( CodeData* pCodeData, unsigned char uchCodeType )
{
    if ( pCodeData == NULL || pCodeData->GetCodeLength() == 0 )
    { return false; }

    //if ( GetStatus() == CS_LOADINGMAP )
    //{ return false; } // ??????????????

    //CheckCheatLog( "????[%s]??????,????????[%s]???????????? ??????????????[%0x]!", theGameProtectManager.GetLoadFileName(), pCodeData->GetCodeFuncName(), pCodeData->GetRightResult() );

    bool bSendSuccess = false;
    switch ( uchCodeType )
    {
    case RabotDefine::EGP_CheckCode:
        {
            MsgCheckCheatReq xReq;
            bSendSuccess = xReq.AddCode( pCodeData->GetCheckCode(), pCodeData->GetCodeLength() );
            if ( bSendSuccess )
            { SendMessageToClient( &xReq ); }
        }
        break;
    case RabotDefine::EGP_GetProcessList:
        {
            MsgGetProcessListReq xReq;
            bSendSuccess = xReq.AddCode( pCodeData->GetCheckCode(), pCodeData->GetCodeLength() );
            if ( bSendSuccess )
            { SendMessageToClient( &xReq ); }
        }
        break;
    default:
        break;
    }

    return bSendSuccess;
}

bool GamePlayer::ProcessKickByCheckCheat( unsigned int dwErrorResult )
{
    // pszFileName ???????????????? ???????????????????? ??????
    CheckCheatLog( theXmlString.GetString( eLog_KickByCheckCheat ), dwErrorResult );
    if ( GetLevel() > 15 )
    { return true; }        // ??????????????T????, ??????T,????????

    // ?????????? T ????
    Log( "Exit By ProcessKickByCheckCheat" );

    uint32 dwBlockTime = g_Cfg.graphicValidFailBlockTime;
    switch( dwErrorResult )
    {
    case Result_ManyClient:
    case RabotDefine::EGP_NotResult:  // ??????
        {
            dwBlockTime = 3 * OneHourMicroSecond;
        }
        break;
    default:
        {
            dwBlockTime = 3 * OneDayMicroSecond;
        }
        break;
    }

    ProcessBeBlock( MsgNotifyBeKick::EKT_Hook, dwBlockTime );
    return true;
}

void GamePlayer::OnEnterStage()
{
    MapConfig::MapData* pMapData = GetMapData();
    if ( pMapData != NULL )
    {
        bool bHaveChange = false;
        for ( int i=0; i<pMapData->GetStatusSize(); ++i)
        {
            MapConfig::Status* pStatus = pMapData->GetStatusByIndex( i );
            if ( pStatus == NULL )
            { continue; }

            if ( ApplyBufferStatus( pStatus->Id, pStatus->Level, GetID(), SCharBuff::StatusEventType_Other, 0) == GLR_Success && !bHaveChange )
            { bHaveChange = true;}
        }

        if ( _buffManager.UpdateBufferOnEnterStage( GetMapID() ) )
        { bHaveChange = true; }

        if ( bHaveChange )
        { OnBuffStatusChanged( true ); }

        if ( abs(pMapData->ExpRate - 1.0) > 0.001f)
        { TellClient( theXmlString.GetString(eText_ShowMapExpRate), static_cast< int >( pMapData->ExpRate * 100 ) ); }

    }

    // ??????
    _graphicCodeManager.OnEnterStage();

}

void GamePlayer::OnLeaveStage()
{
    _graphicCodeManager.OnLeaveStage();
}

void GamePlayer::ProcessBeBlock( uint8 type , uint32 time )
{
    MsgNotifyBeKick msg;
    msg.kickType = type;
    GettheServer().SendMsgToSingle( &msg, this );

	_blockTime = time;

    Log( "Exit By ProcessBeBlock = %d", type );
    ExitWorld(__FUNCTION__, __FILE__, __LINE__,ET_SystemBeKick);    
}

void GamePlayer::ShowPubQuestDlg( int nNpcID, int nType, const char* szInfo )
{
    // ??????????????????, ????????????????
    switch( nType )
    {
    case MsgScriptReqShowQuestDlg::ShowType_Pub:
    case MsgScriptReqShowQuestDlg::ShowType_Royal:
        {
            thePubQuestManager.ShowSpecialQuestList( this, GetDBCharacterID(), nNpcID );
        }
        break;
    case MsgScriptReqShowQuestDlg::ShowType_ConQuest:   // ????????
        {
            theConQuestManager.ShowSpecialQuestList( this, GetDBCharacterID(), nNpcID );
        }
        break;
    default:
        return;
        break;
    }

    MsgScriptReqShowQuestDlg xShow;
    xShow.header.stID = GetID();
    xShow.stNpcId     = nNpcID;
    xShow.chShowType  = nType;        // ????
    HelperFunc::SafeNCpy( xShow.szInfo, szInfo, MsgScriptReqShowQuestDlg::eInfoLengthMax );
    SendMessageToClient( &xShow );
}

bool GamePlayer::IsCanSaveToDB()
{
    switch ( GetStatus() )
    {
    case CS_START:
    case CS_CHECK:
    case CS_LOGIN:
    case CS_LOGINTODB:
    case CS_WAITDBRET:
    case CS_DBLOGINED:
        return false;
        break;
    default:
        break;
    }

    return true;
}

bool GamePlayer::IsSaveTime()
{
    if ( dwCharSaveDelay == 0)
    { dwCharSaveDelay = HQ_TimeGetTime(); }

    bool bNeedSave = false;
    if ( GameTime::IsPassCurrentTime( dwCharSaveDelay, g_Cfg.dwAutoSaveDelay ) )
    { // ????????
        bNeedSave = true;
        dwCharSaveDelay = HQ_TimeGetTime();
    }
    return bNeedSave;
}


void GamePlayer::TellGameStage( short stTotalStage, short stCurrentStage, uint32 dwTime )
{
    MsgTellGameStage xTell;
    xTell.stTotalStage = stTotalStage;
    xTell.stStage      = stCurrentStage;
    xTell.dwTime       = dwTime;
    SendMessageToClient( &xTell );
}

bool GamePlayer::CheckItemOperate( SCharItem* pCharItem )
{
    if ( pCharItem == NULL )
    { return false; }

    if ( pCharItem->IsPassUnLockTime( true ) )  // ????????????????
    {
        pCharItem->SetLock( false );
    }

    return pCharItem->IsOverdue( true );
}

void GamePlayer::CheckAllItemOperate()
{
    //MsgTellRemoveTimeLimitItem xTellRemoveTimeLimitItem;     // ????????????????????, ???????????????? ????????????????Onmsgmapload????????????????
    // ??????????
    ItemBag* s_ItemBag[] = { &_NormalItemBag, &_MaterialItemBag, &_TaskItemBag, };
    for ( int m = 0; m < sizeof( s_ItemBag ) / sizeof( ItemBag* ); ++m )
    {
        ItemBag* pItemBag = s_ItemBag[m];
        if ( pItemBag == NULL )
        { continue; }

        for ( int i = 0; i < pItemBag->GetNowBagSize(); ++i )
        {
            SCharItem* pCharItem = pItemBag->GetItemByIndex( i );
            if ( pCharItem == NULL )
            { continue; }

            if ( CheckItemOperate( pCharItem ) )
            {
                ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( pCharItem->itembaseinfo.ustItemID );
                int nCount = 1;
                if ( pItemBag->ClearItem( i, nCount ) )
                {
                    if ( pItemCommon != NULL )
                    {
                       // Log( "????????????[%s][%d]??", pItemCommon->GetItemName(), nCount );
						 Log( theXmlString.GetString(eServerLog_DeleteItem), pItemCommon->GetItemName(), nCount );
                    }
                }
            }  
        }
    }

    // ????????????
    bool bEquipOverdue = false;

    for ( int i = 0; i < EEquipPartType_MaxEquitPart; ++i )
    {
        SCharItem* pCharItem = GetVisualEquipItem(i);
        if ( pCharItem==NULL )
        { continue; }

        if ( pCharItem->itembaseinfo.ustItemID == InvalidLogicNumber || pCharItem->itembaseinfo.nOnlyInt == 0 )
        { continue; }

        if ( CheckItemOperate( pCharItem ) )
        {
            bEquipOverdue = true;
            ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( pCharItem->itembaseinfo.ustItemID );
            pCharItem->itembaseinfo.ustItemID = InvalidLogicNumber;
            pCharItem->itembaseinfo.nOnlyInt  = InvalidLogicNumber;

            if ( pItemCommon != NULL )
            {
                Log( theXmlString.GetString(eServerLog_DeleteItem), pItemCommon->GetItemName(), 1 );
            }
        }
    }

    if ( bEquipOverdue )
    {
        UpdateAllEquipData();
        UpdateAllSuitData() ;
        RecalcBaseProperty( false, BV_NotFullHp, BV_NotSendMessage, EWRP_Equip );
    }

    // ????????
    for ( int i = 0; i < STORAGE_ITEMGRID_MAX; ++i )
    {
        SCharItem* pCharItem = &_StorageBag.stStorageItems[i];
        if ( pCharItem->itembaseinfo.ustItemID == InvalidLogicNumber || pCharItem->itembaseinfo.nOnlyInt <= 0 )
        { continue; }

        if ( CheckItemOperate( pCharItem ) )
        {
            ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( pCharItem->itembaseinfo.ustItemID );
            pCharItem->itembaseinfo.ustItemID = InvalidLogicNumber;
            pCharItem->itembaseinfo.nOnlyInt  = 0;

            if ( pItemCommon != NULL )
            {
                Log( theXmlString.GetString(eServerLog_DeleteItem), pItemCommon->GetItemName(), 1 );
            }
        }
    }

    // ??????????
    for ( int i = 0; i < _mountManager.GetMountCount(); ++i )
    {
        SMountItem* pMountItem = _mountManager.GetMountByIndex( i );
        if ( pMountItem == NULL )
        { continue; }

        if ( pMountItem->IsPassUnLockTime( true ) )
        {
            pMountItem->SetLock( false );
        }
    }
}

void GamePlayer::ApplySuitEquipAttributesToChar( unsigned short ustItemID )
{
    ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( ustItemID );
    if ( pItemCommon == NULL || !pItemCommon->IsCanEquip() )
    { return; }

    ItemDefine::SItemCanEquip* pItemCanEquip = static_cast< ItemDefine::SItemCanEquip* >( pItemCommon );
    if ( pItemCanEquip == NULL )
    { return; }

	//????????????????????????????????????????
	if (pItemCanEquip->IsHeroSuitEquip() &&  pItemCanEquip->nHeroID != GetHeroId())
	{
		return;
	}
	if(pItemCommon->ucItemType == ItemDefine::ITEMTYPE_ARMOUR)
	{
		ItemDefine::SItemArmour* pArmour = (ItemDefine::SItemArmour*)pItemCommon;
		GetCharFightAttr()->defendPhysics.suit += pArmour->defendPhysics;
		GetCharFightAttr()->defendMagic.suit += pArmour->defendMagic;
		GetCharFightAttr()->hpMax.suit += pArmour->Hp;
		GetCharFightAttr()->mpMax.suit += pArmour->Mp;
	}
	

    GetCharFightAttr()->attackPhysics.suit += pItemCanEquip->attackPhysics;
    GetCharFightAttr()->attackMagic.suit   += pItemCanEquip->attackMagic;
    GetCharFightAttr()->attackSpeed.suit   += pItemCanEquip->attackSpeed;
    GetCharFightAttr()->exact.suit         += pItemCanEquip->exact;
    GetCharFightAttr()->dodge.suit         += pItemCanEquip->dodge;
    GetCharFightAttr()->critical.suit      += pItemCanEquip->critical;
    GetCharFightAttr()->tenacity.suit      += pItemCanEquip->tenacity;
	//????????
	GetCharFightAttr()->breakStrike.suit		+= pItemCanEquip->breakStrike;
	GetCharFightAttr()->breakResist.suit		+= pItemCanEquip->breakResist;
	GetCharFightAttr()->stabStrike.suit			+= pItemCanEquip->stabStrike;
	GetCharFightAttr()->stabResist.suit			+= pItemCanEquip->stabResist;
	GetCharFightAttr()->elementStrike.suit      += pItemCanEquip->elementStrike;
	GetCharFightAttr()->elementResist.suit      += pItemCanEquip->elementResist;
	GetCharFightAttr()->toxinStrike.suit		+= pItemCanEquip->toxinStrike;
	GetCharFightAttr()->toxinResist.suit		+= pItemCanEquip->toxinResist;
	GetCharFightAttr()->spiritStrike.suit		+= pItemCanEquip->spiritStrike;
	GetCharFightAttr()->spiritResist.suit		+= pItemCanEquip->spiritResist;
//modified by junyi.chen begin
//     short sRandNum = pItemCanEquip->additiveRandCount;
// 
//     if (sRandNum <= 0)
//     { return; }
// 
//     if (sRandNum > SCharItem::EConstDefine_BaseRandMaxCount)
//     { sRandNum = SCharItem::EConstDefine_BaseRandMaxCount; }
// 
//     // ????Flag??????????sRandNum???????? ?????????? ????????????
//     if ( !pItemCanEquip->additiveRandFlags[0] )
//     { sRandNum = theRand.rand32() % sRandNum + 1; }
// 
     uint16 suitRands[ SCharItem::EConstDefine_BaseRandMaxCount ] = { 0 };
// 
//     for (int i = 0; i<sRandNum; ++i)
//     {
//         if ( pItemCanEquip->additiveRandFlags[i])
//         { // ????
//             ItemDefine::SRandAttribute* pRand = GettheItemDetail().GetRandByID(pItemCanEquip->additiveRandValues[i]);
//             if ( pRand != NULL )
//             {
//                 suitRands[i] = pRand->id;
//             }
//         }
//         else
//         { // ????
//             CItemDetail::RandContainer rands;
//             GettheItemDetail().GetRandByLevel(pItemCanEquip->additiveRandValues[i],rands);
// 
//             if ( !rands.empty() )
//             {
//                 int nSize = rands.size();
//                 int nIndex = theRand.rand16() % nSize;
//                 suitRands[i] = rands[nIndex];
//             }
//         }
//     }
	theRunTimeData.EquipBaseRand(suitRands, pItemCanEquip);
//end
    //????????????????
    for (int nloop = 0; nloop < SCharItem::EConstDefine_BaseRandMaxCount; ++nloop)
    {    
		if ( suitRands[nloop] == InvalidLogicNumber )
		{ continue; }

		ApplyRandAttributeToChar( suitRands[nloop], ECustomDataPart_suit );
        
    }
	
	//???????? by liaojie
	//if (pItemCanEquip->nHeroID!=0)
	//{
	//	theRunTimeData.EquipBaseRand_Hero(suitRands, pItemCanEquip);
	//	for (int nloop = 0; nloop < SCharItem::EConstDefine_BaseRandMaxCount; ++nloop)
	//	{    
	//		if ( suitRands[nloop] == InvalidLogicNumber )
	//		{ continue; }

	//		ApplyRandAttributeToChar( suitRands[nloop], ECustomDataPart_suit );

	//	}
	//}
}

void GamePlayer::ShowBattleSignUpDlg( int nNpcID, int nType, const char* szInfo )
{
    MsgShowBattleSignUpDlg msg;
    msg.header.stID = GetID();
    msg.stNpcId     = nNpcID;
    msg.uchShowType = nType;        // ????
    HelperFunc::SafeNCpy( msg.szInfo, szInfo, MsgScriptReqShowQuestDlg::eInfoLengthMax );

    switch( nType )
    {
    case BattleDefine::PlayerType:
        {
            int nCount = 0;
            for ( int i = 0; i < thePlayerBattleManager.GetBattleDataCount(); ++i )
            {
                PlayerBattleData* pBattleData = thePlayerBattleManager.GetBattleDateByIndex( i );
                if ( pBattleData == NULL )
                { continue; }

                msg.xSignUpInfo[nCount].ustMapID    = pBattleData->GetWaitMapID();
                msg.xSignUpInfo[nCount].ustLevel    = pBattleData->GetMapLevel();
                msg.xSignUpInfo[nCount].ustCount    = pBattleData->GetUnitCount();
                msg.xSignUpInfo[nCount].ustMaxCount = pBattleData->GetMaxUnitCount();
                if ( pBattleData->GetStatus() == BattleDefine::Status_SignUp )
                {
                    msg.xSignUpInfo[nCount].nSignUpLeftTime = GameTime::GetLeftKeepTime( HQ_TimeGetTime() + 1999, pBattleData->GetStartSignUpTime(), pBattleData->GetSignUpTime() ) / 1000;
                }
                ++nCount;
            }

            SendMessageToClient( &msg );
        }
        break;
    case BattleDefine::TeamType:
        {
            MsgTellBattleSignUpInfo xSignUpInfo;
            xSignUpInfo.uchType = nType;

            int nCount = 0;
            for ( int i = 0; i < theTeamBattleManager.GetBattleDataCount(); ++i )
            {
                TeamBattleData* pBattleData = theTeamBattleManager.GetBattleDateByIndex( i );
                if ( pBattleData == NULL )
                { continue; }

                msg.xSignUpInfo[nCount].ustMapID    = pBattleData->GetWaitMapID();
                msg.xSignUpInfo[nCount].ustLevel    = pBattleData->GetMapLevel();
                msg.xSignUpInfo[nCount].ustCount    = pBattleData->GetUnitCount();
                msg.xSignUpInfo[nCount].ustMaxCount = pBattleData->GetMaxUnitCount();
                if ( pBattleData->GetStatus() == BattleDefine::Status_SignUp )
                {
                    msg.xSignUpInfo[nCount].nSignUpLeftTime = GameTime::GetLeftKeepTime( HQ_TimeGetTime(), pBattleData->GetStartSignUpTime(), pBattleData->GetSignUpTime() );
                    msg.xSignUpInfo[nCount].nSignUpLeftTime = ( msg.xSignUpInfo[nCount].nSignUpLeftTime + 999 ) / 1000;
                }
                ++nCount;

                pBattleData->GetUnitName( &xSignUpInfo );
            }

            SendMessageToClient( &msg );
            SendMessageToClient( &xSignUpInfo );
        }
        break;
    case BattleDefine::GuildType:
        break;
    default:
        return;
    }
}

void GamePlayer::CheckRemoveSecondPassword()
{
    __int64 n64RemoveTime = gCharInfoServer.otherdata.xSecondPassword.GetRemoveTime();
    if ( n64RemoveTime == 0 )
    { return; }

    if ( TimeEx::IsPassCurrentTime( n64RemoveTime ) )
    {
        gCharInfoServer.otherdata.xSecondPassword.SetRemoveTime( 0 );
        gCharInfoServer.otherdata.xSecondPassword.ClearPassword();
    }
}

bool GamePlayer::FlyToPlayer( int nType )
{
    DWORD dwFlyToPlayerID = InvalidLogicNumber;
    switch( nType )
    {
    case 1:     // ????????????( ???????? )
        {
            if (!m_pRelation->IsHaveMarriage() )
            {
                MsgAckResult xAck;
                xAck.result = ER_MustBeMarriageCanFly;
                SendMessageToClient( &xAck );
                return false;
            }

            GameRelation* pAckRelation = theGameRelationManager.GetPlayerRelation( m_pRelation->GetMarriageID() );
            if ( pAckRelation == NULL )
            {
                MsgAckResult xAck;
                xAck.result = ER_ItemFlyNotOnline;
                SendMessageToClient( &xAck );
                return false;
            }

            dwFlyToPlayerID = m_pRelation->GetMarriageID();
        }
        break;
    default:
        break;
    }

    if ( dwFlyToPlayerID == InvalidLogicNumber )
    { return false; }

    bool bResult = false;

    GamePlayer* pFlyToPlayer = theRunTimeData.GetGamePlayerByDBID( dwFlyToPlayerID);
    if ( pFlyToPlayer == NULL )  //??????????????, ??????centerserver
    {
        GS2CSQueryPlayerInfoReq xReq;
        xReq.dwReqID = GetDBCharacterID();
        xReq.dwAckID = dwFlyToPlayerID;
        xReq.nAction = GS2CSQueryPlayerInfoReq::Action_ItemFlyToPlayer;
        GettheServer().SendMsgToCenterServer( &xReq );  

        bResult = true;
    }
    else
    {
        MapConfig::MapData* pMapData = pFlyToPlayer->GetMapData();
        if ( pMapData == NULL )
        { return false; }

        if ( !pMapData->IsEctypeMap() )
        {
            bResult = FlyToMapReq( pFlyToPlayer->GetMapID(), pFlyToPlayer->GetFloatX() /*+ 1.0f*/, pFlyToPlayer->GetFloatY() /*+ 1.0f*/, 0.0f, false );
        }
        else
        {
            MapConfig::RelivePosition* pRelive = pMapData->GetRelivePositionByState( false );
            if ( pRelive == NULL )
            { return false; }

            if ( IsInMapArea( pRelive->MapId, pRelive->PositionX, pRelive->PositionY, 40.f ) )
            { return false; }      // ????????????????????

            bResult = FlyToMapReq( pRelive->MapId, pRelive->PositionX, pRelive->PositionY, pRelive->Direction, false );
        }
    }

    return bResult;
}

void GamePlayer::AddTeamBattleIntegral( int nIntegral, int nKillCount, int nDeathCount, bool bSendMessage /* = true */ )
{
    TeamBattleData* pBattleData = theTeamBattleManager.GetBattleDateByMapID( EctypeId2MapId( GetMapID() ) );
    if ( pBattleData == NULL )
    { return; }

    pBattleData->UpdateBattleRecord( GetMapID(), GetTeamID(), GetDBCharacterID(), nIntegral, nKillCount, nDeathCount, bSendMessage );
}

bool GamePlayer::HaveTeam() 
{
    return GetTeamID() != TeamDefine::NoneSessionID;
}

// ???????????????????? 
void GamePlayer::IncreaseTeamExp( BaseCharacter *pTarget )
{
    if( pTarget == NULL || !pTarget->IsMonster() )
    { return; }

    MonsterBaseEx* pAiMonster = static_cast< MonsterBaseEx* >( pTarget );

    int iRewardExp = pAiMonster->GetRewardExp();
    int iRewardSkillExp = pAiMonster->GetRewardSkillExp();
    if ( iRewardExp == 0 && iRewardSkillExp == 0 )
    { return; }

    // ??????????????
    GameTeam* pTeam = theGameTeamManager.GetTeam( GetTeamID() );
    if ( pTeam == NULL )
    {
        ProcessKillMonsterExp( pTarget, iRewardExp, iRewardSkillExp );
    }
    else
    {
        //????????????????????????????????????????????????????????????????????????????
        MapConfig::MapData* pMapData = GetMapData();
        if ( pMapData == NULL )
        { return; }

        //????????????????
        unsigned int nAreaCount = pTeam->GetTeamMemberCountInMap( pTarget->GetMapID(), pTarget->GetFloatX(), pTarget->GetFloatY() );
        if ( nAreaCount == 0 ) 
        { nAreaCount = 1; }

        //????????????????
        float fExpPercent = pTeam->GetTeamExpPercent( nAreaCount, pMapData->IsEctypeMap() );

        int nMinLevel = 0;
        int nMaxLevel = 0;
        int nTotalLevel = pTeam->GetTeamMemberLevelDistance( pTarget->GetMapID(), pTarget->GetFloatX(), pTarget->GetFloatY(), nMinLevel, nMaxLevel );
        for( int i = 0; i < pTeam->TeamMemberCount(); ++i )
        {
            GamePlayer* pPlayer = pTeam->GetMemberPlayer( pTeam->GetMemberIDByIndex( i ) );
            if ( pPlayer == NULL || pPlayer->IsDead() || !pPlayer->IsInMapArea(pTarget->GetMapID(), pTarget->GetFloatX(), pTarget->GetFloatY(), TEAM_EXP_DIS) ) 
            { continue; }

            int iPlayerExp = iRewardExp * fExpPercent;
            if( pPlayer->GetLevel() < g_Cfg.m_nLevelLimt )    // ????????????????
            {
                // ????????????????
                if ( nMaxLevel - nMinLevel >= 20 )     //??????????????????20??,??????????
                {
                    iPlayerExp = iPlayerExp * ( pPlayer->GetLevel() * 1.3 ) / ( nMinLevel + nMaxLevel );
                }
            }
            pPlayer->ProcessKillMonsterExp( pTarget, iPlayerExp, iRewardSkillExp );

            if ( pAiMonster->GetRewardFriendly() != 0 )        // ????????????????????0, ??????????????
            { pTeam->UpdateTeamFriendly( pPlayer, pAiMonster->GetRewardFriendly() ); }
        }
    }

    //zhuxincong ????????????
    _mountManager.AddActiveMountExp( iRewardExp );

    // ????????????
    /*MonsterBaseEx* pNurturePet = _petManager.GetMonsterNurturePet();
    if ( pNurturePet == NULL )
    { return; }

    float fPetLevelDis = GetLevelDistanceExpModulus( pNurturePet->GetLevel(), pAiMonster->GetLevel() );
    int iPetExp = iRewardExp * fPetLevelDis;
    _petManager.AddActivePetExp( iPetExp );*/
}

void GamePlayer::ProcessKillMonsterExp( BaseCharacter* pTarget, int iRewardExp, int iRewardSkillExp )
{
    if ( pTarget == NULL || !pTarget->IsMonster() || iRewardExp == 0 )
    { return; }

    MapConfig::MapData* pMapData = GetMapData();
    if (pMapData == NULL)
    { return; }

    MonsterBaseEx* pAiBase = static_cast< MonsterBaseEx* >( pTarget );
    if ( pAiBase == NULL )
    { return; }

    float fLevelDis = GetLevelDistanceExpModulus( GetLevel(), pAiBase->GetLevel() );
    if ( pMapData->IsEctypeMap() )
    { fLevelDis = 1.0f; }

    int iPlayerExp = 0;

    if( GetLevel() < g_Cfg.m_nLevelLimt+3 )
    { iPlayerExp = iRewardExp * fLevelDis; }

    // ????????????????
    iPlayerExp = ( ( float ) iPlayerExp ) * ( 1.0f + CalcStudentExpModulus() );
    IncreaseExp( iPlayerExp, iRewardSkillExp , pAiBase );

    // ????????
    IncreaseDaoxing( pAiBase->GetRewardDaoxing() );

    MsgKillMonster killMonster;
    killMonster.header.stID = GetID();
    killMonster.stMonsterID = pAiBase->GetID();
    killMonster.nExp        = iPlayerExp;
    killMonster.nSkillExp   = 0;
    SendMessageToClient( &killMonster );

    int nRewardExpolit = pAiBase->GetRewardExpolit();
    OperateExploit( EOT_Add, nRewardExpolit, __FUNCTION__, __LINE__ ,ePlayerMoneySourceType_KillMonsterSpecialReward);

    // ????????
    int nRewardReputation = pAiBase->GetRewardReputation();
    int nRewardMoney      = pAiBase->GetRewardMoney();
    if ( !_buffManager.IsHaveStatus( pAiBase->GetRewardStatusID() ) )
    {// ??????????
        OperateReputation( EOT_Add, nRewardReputation, __FUNCTION__, __LINE__ ,ePlayerMoneySourceType_KillMonsterSpecialReward);
        OperateJiaoZi    ( EOT_Add, nRewardMoney, true, __FUNCTION__, __LINE__ ,ePlayerMoneySourceType_KillMonsterSpecialReward);
    }
    else
    {// ??????????????
        int mulValue = pAiBase->GetRewardMulValue();

        if (pAiBase->GetRewardMulType() == ItemDefine::EMRT_Reputation )
        { nRewardReputation *= mulValue; }
        OperateReputation( EOT_Add, nRewardReputation, __FUNCTION__, __LINE__ ,ePlayerMoneySourceType_KillMonsterSpecialReward);

        if (pAiBase->GetRewardMulType() == ItemDefine::EMRT_CashMoney )
        { OperateMoney( EOT_Add, nRewardMoney * mulValue, true, __FUNCTION__, __LINE__ ,ePlayerMoneySourceType_KillMonsterSpecialReward); }
        else
        { OperateJiaoZi( EOT_Add, nRewardMoney, true, __FUNCTION__, __LINE__ ,ePlayerMoneySourceType_KillMonsterSpecialReward); }
    }
}

void GamePlayer::IncreaseExp( int nCharExp, int nSkillExp, BaseCharacter* pKillTarget /* = NULL */ )
{
    if ( IsDead() )
    { return; }

    // ????????
    if ( nSkillExp > 0 )
    {   //??????????????????????STATUS????????
        nSkillExp = nSkillExp * ( GetSkillExpChangePer()               );
        nSkillExp = nSkillExp * ( theRunTimeData.g_nSkillExpPer * DEF_PERCENT );
        nSkillExp = nSkillExp * ( _buffManager.GetSkillExpAddMul() + 1 );

//#if 0 // ????????
//        IncreaseSingleSkillExp( nSkillExp );
//#else
        IncreaseTotalSkillExp( nSkillExp );
//#endif
    }

    // ????
    bool bAddKillMonster = true;
    if ( nCharExp == 0 && pKillTarget != NULL )
    {  
        bAddKillMonster = false;    // ?????????????? 0 ??????
        nCharExp = 1;               // ??????????????
    } 

	int nOldLevel = GetLevel();
    // ??????????????????
 //   if( nOldLevel >= g_Cfg.m_nLevelLimt )
 //   { 
	//	if ( enumAntiAddictionStateTired == gTransferRuntimeInfo.nAntiAddicationStatus)
 //       { nCharExp /= 2; }
 //       else if (enumAntiAddictionStateRest == gTransferRuntimeInfo.nAntiAddicationStatus )
 //       { nCharExp = 0; }
	//	//nCharExp = 0; 
	//	//????????????3????????
	//	int64 MaxExp = theExpStage.GetLevelupExp(g_Cfg.m_nLevelLimt +3) - theExpStage.GetLevelupExp(g_Cfg.m_nLevelLimt);
	//	if(GetPlayerExpUnUsed() + nCharExp > MaxExp)
	//		nCharExp = MaxExp - GetPlayerExpUnUsed();
	//	if(nCharExp <=0)
	//		return;
	//	SetPlayerExpUnUsed(GetPlayerExpUnUsed() + nCharExp);
	//	MsgCharAttrChanged Change;
	//	Change.header.stID = GetID();
	//	Change.iChangeCount = 0;
	//	Change.AddAttrInt64Change( CharAttr_ExpNotUsed,GetPlayerExpUnUsed() );
	//	Change.AddAttrDWORDChange( CharAttr_CurGetExp, 0 );
	//	if ( bAddKillMonster )
	//	{
	//		// ????????, ?????????????????????? ????????????????????
	//		if ( theKillMonsterCountConfig.IsSettingKillCount( GetRecordKillMonsterCount() ) )
	//		{
	//			//Change.AddAttrDWORDChange( CharAttr_MaxKillMonsterCount, g_Cfg.m_nMaxKillMonsterCount );
	//			Change.AddAttrDWORDChange( CharAttr_CurKillMonsterCount, GetRecordKillMonsterCount() );
	//		}
	//	}
	//	Change.CaluLength();
	//	SendMessageToClient( &Change );
	//}     // ??????????????????????

    if ( pKillTarget != NULL )
    {
        nCharExp = nCharExp * ( GetExpChangePer()                );
        nCharExp = nCharExp * ( theRunTimeData.g_nExpPer * DEF_PERCENT  );
        nCharExp = nCharExp * ( _buffManager.GetExpAddMul() + 1  );

        MapConfig::MapData* pMapData = GetMapData();
        if ( pMapData != NULL )
        { nCharExp = nCharExp * pMapData->ExpRate; }

        // ????????????????????????????????
        float fKillMonsterPercent = 1.00f;
        if ( bAddKillMonster && pMapData && !pMapData->IsEctypeMap())      // ?????????? ????????????????????????
        {
            fKillMonsterPercent = GetKillMonsterModulus();
            AddRecordKillMonsterCount();

            nCharExp = nCharExp * fKillMonsterPercent;      // ????????????
        }

        float fPercent = 1.00f; 
        Log( theXmlString.GetString(eLog_Info_ExpPercent), fPercent, GetExpChangePer(), (float)theRunTimeData.g_nExpPer / 100, _buffManager.GetExpAddMul() + 1.00f, fKillMonsterPercent );
    }

    if ( nCharExp <= 0 )
    { return; }     // 0??????????????????

    //??????????
	int Exp =  IncreasePlayerExp( nCharExp );

	//LYH????????
	if(pKillTarget)
		theLogEventService.LogExp(GetAccountID(),GetDBCharacterID(),Exp,pKillTarget->GetMonsterID(),ePlayerExp_Kill,GetCharName());
	else
		theLogEventService.LogExp(GetAccountID(),GetDBCharacterID(),Exp,0,ePlayerExp_Script,GetCharName());



    int64 dwUnUsedExp = GetPlayerExpUnUsed();

    MsgCharAttrChanged Change;
    Change.header.stID = GetID();
    Change.iChangeCount = 0;
    Change.AddAttrInt64Change( CharAttr_ExpNotUsed,dwUnUsedExp );
    Change.AddAttrDWORDChange( CharAttr_CurGetExp, nCharExp );
    if ( bAddKillMonster )
    {
        // ????????, ?????????????????????? ????????????????????
        if ( theKillMonsterCountConfig.IsSettingKillCount( GetRecordKillMonsterCount() ) )
        {
            //Change.AddAttrDWORDChange( CharAttr_MaxKillMonsterCount, g_Cfg.m_nMaxKillMonsterCount );
            Change.AddAttrDWORDChange( CharAttr_CurKillMonsterCount, GetRecordKillMonsterCount() );
        }
    }
    Change.CaluLength();
    SendMessageToClient( &Change );

    if ( pKillTarget != NULL )
    {
        Log( theXmlString.GetString(eLog_info_2slk_30), pKillTarget->GetCharName(), nCharExp );
    }
    else
    {
        Log( theXmlString.GetString(eLog_info_2slk_35), nCharExp );
    }

    // ????????????
	if (nOldLevel < manual_levelup)
	{
		int64 nCurExp = GetPlayerCurrentExp();
		int nNewLevel = theExpStage.GetLevel( nCurExp );     
		if( nOldLevel < nNewLevel && nNewLevel <= g_Cfg.m_nLevelLimt )
		{
			ChangeLevel( nNewLevel );

			//LYH????????
			if (!theLogEventService.LogLevelChange(GetAccountID(),GetDBCharacterID(),nOldLevel,nNewLevel,GetCharName()))
			{
				Log(theXmlString.GetString(eLog_info_2slk_29),nOldLevel,nNewLevel);
			}
		}
	}
    // ???????????????? 
    //int64 nCurExp = GetPlayerCurrentExp();
    //int nNewLevel = theExpStage.GetLevel( nCurExp ); 
    //int nOldLevel = GetLevel();
    //
    //if ( nOldLevel < CHAR_AUTO_LEVELUP && nNewLevel > CHAR_AUTO_LEVELUP )
    //{ nNewLevel = CHAR_AUTO_LEVELUP; }

    //if( nOldLevel < CHAR_AUTO_LEVELUP && nOldLevel < nNewLevel && nNewLevel <= g_Cfg.m_nLevelLimt )
    //{
    //    ChangeLevel( nNewLevel );    
    //    Log(theXmlString.GetString(eLog_info_2slk_29),nOldLevel,nNewLevel);
    //}
}

void GamePlayer::IncreaseDaoxing ( int nDaoxing )
{
    // ?????? = ????????/??????*100% ????????90%??????0%
    int nStdDaoxing = ProcessCharInfo::StdDaoxing( GetLevel() );
    float nAttenuationPer = 0;

    if (nStdDaoxing != 0 )
    { nAttenuationPer = gCharInfoServer.baseinfo.liveinfo.daoxing / nStdDaoxing * DEF_PER - 100; }
    
    if (nAttenuationPer < 0)
    { nAttenuationPer = 0; }

    if (nAttenuationPer > DEF_PER_INT)
    { nAttenuationPer = DEF_PER_INT; }

    nDaoxing = nDaoxing * ( GetExpChangePer()                );
    nDaoxing = nDaoxing * ( theRunTimeData.g_nExpPer * DEF_PERCENT  );
    nDaoxing = nDaoxing * ( _buffManager.GetExpAddMul() + 1  );
    nDaoxing = nDaoxing * ( DEF_PER_INT - nAttenuationPer ) * DEF_PERCENT;

    OperateDaoxing( EOT_Add, nDaoxing, __FUNCTION__, __LINE__ );
}

int GamePlayer::IncreasePlayerExp( int & dwExp)
{
    if ( _bNeedAntiAddiction )
    { // ??????????
        if ( enumAntiAddictionStateTired == gTransferRuntimeInfo.nAntiAddicationStatus)
        { dwExp /= 2; }
        else if (enumAntiAddictionStateRest == gTransferRuntimeInfo.nAntiAddicationStatus )
        { dwExp = 0; }
    }

	//??????????????????
	//float f_add = theLevelLimitGameManager.GetLimitExpAward(GetLevel())/100;
	//dwExp = dwExp*f_add;
	/////////////////////////////////////////////////////////////////////////
	unsigned long all_exp =GetPlayerExpUnUsed() + dwExp;	
	if (all_exp > GetCanTakeExp())
	{
		SetPlayerExpUnUsed(GetCanTakeExp());
	}
	else
		SetPlayerExpUnUsed( all_exp );
    return dwExp;
}

bool GamePlayer::RemoveMountByid(unsigned short usMountId,bool _All)
{
	if (usMountId == InvalidLogicNumber)
	{
		return false;
	}
	for (int n =0;n < ITEM_MOUNT_MAXCOUNT;)
	{
		SMountItem* pMount = _mountManager.GetMountByIndex( n );
		if ( pMount == NULL )
		{ 
			++n;
			continue; 
		}

		if (pMount->baseInfo.id != usMountId)
		{
			++n;
			continue;
		}

		int64 n64Guid = pMount->GetMountGuid();

		//???????????? ??????????????????????????????
		if(_mountManager.GetActiveMount() == pMount)
		{
			//??????
			DoRide(-1);
			//GotOffMultiMount();
		}

		bool bActiveIndex = false;
		int nResult = _mountManager.PopMount( n, bActiveIndex );
		if ( nResult != ER_Success )
		{ 
			++n;
			continue;
		}
		MsgChangeDrome changedrome;
		changedrome.header.stID = GetID();
		changedrome.ucOpType    = MsgChangeDrome::EOT_Discard;
		changedrome.nIndex      = n;
		changedrome.guid        = n64Guid;
		SendMessageToClient( &changedrome );

		if ( bActiveIndex )
		{
			_mountManager.ApplyMountAttributeToChar( false, true );
		}
		if (!_All)
		{//????????????????,??????????????
			return true;
		}
	}
	return true;
}

bool GamePlayer::RemoveMountByGuid( __int64 nGuild )//????????ID????????
{
    int nIndex = _mountManager.GetMountIndexByGuid( nGuild );

    return RemoveMountByIndex( nIndex );
}

bool GamePlayer::RemoveMountByIndex( uint8 uchIndex )
{
    SMountItem* pMount = _mountManager.GetMountByIndex( uchIndex );
    if ( pMount == NULL )
    { return false; }

    int64 n64Guid = pMount->GetMountGuid();

    bool bActiveIndex = false;
    int nResult = _mountManager.PopMount( uchIndex, bActiveIndex );
    if ( nResult != ER_Success )
    { return false; }

    MsgChangeDrome changedrome;
    changedrome.header.stID = GetID();
    changedrome.ucOpType    = MsgChangeDrome::EOT_Discard;
    changedrome.nIndex      = uchIndex;
    changedrome.guid        = n64Guid;
    SendMessageToClient( &changedrome );

    if ( bActiveIndex )
    {
        _mountManager.ApplyMountAttributeToChar( false, true );
    }

    return true;
}

bool GamePlayer::RemovePetByGuid( __int64 nGuild, int source )
{
    int nIndex = _petManager.GetPetIndexByGuid( nGuild );

    return RemovePetByIndex( nIndex );
}

bool GamePlayer::RemovePetByIndex( uint8 uchIndex, int source )
{
    SPetItem* pPet = _petManager.GetPetByIndex( uchIndex );
    if ( pPet == NULL )
    { return false; }

    if ( uchIndex == _petManager.GetActivePetIndex() )
    { _petManager.LostActivePetMonster(); }

    int64 n64Guid = pPet->GetPetGuid();

    bool bActiveIndex = false;
    int nResult = _petManager.PopPet( uchIndex, bActiveIndex );
    if ( nResult != ER_Success )
    { return false; }

    MsgChangePet msg;
    msg.header.stID = GetID();
    msg.ucOpType    = MsgChangePet::EOT_Disappear;
    msg.nIndex      = uchIndex;
    msg.guid        = n64Guid;
    msg.source      = source;
    SendMessageToClient( &msg );

    return true;
}

void GamePlayer::PetBreedAcquire()
{
    SPetItem* pBreedPet = _petManager.GetBreedPet();
    if ( pBreedPet == NULL )
    {
        MsgPetBreedAcquireAck msgAck;
        msgAck.result = MsgPetBreedAcquireAck::ER_NoBreedPet;
        GettheServer().SendMsgToSingle( &msgAck, this );
        return; 
    }

    int64 interval = TimeEx::GetNowTime() - pBreedPet->breedInfo.commitTime;
    int32 petBreedIntervalTime = OneMinuteSecond * g_Cfg.petBreedIntervalTime ;
    if ( interval < petBreedIntervalTime )
    {
        MsgPetBreedAcquireAck msgAck;
        msgAck.result = MsgPetBreedAcquireAck::ER_Interval;
        msgAck.value  = petBreedIntervalTime - interval;
        GettheServer().SendMsgToSingle( &msgAck, this );
        return; 
    }

    ItemDefine::SPetMonster* pMonsterConfig = GettheItemDetail().GetPetById( pBreedPet->GetPetID() );
    if ( pMonsterConfig == NULL ) 
    {
        MsgPetBreedAcquireAck msgAck;
        msgAck.result = MsgPetBreedAcquireAck::ER_NoBreedPet;
        GettheServer().SendMsgToSingle( &msgAck, this );
        return; 
    }

    GameTeam* pTeam = theGameTeamManager.GetTeam( GetTeamID() );
    if( pTeam == NULL )
    {// 
        DBMsgPetBreedQueryReq msgQuery;
        msgQuery.header.stID     = GetID();
        msgQuery.dwDBCharacterID = pBreedPet->breedInfo.targetCharDBID;
        msgQuery.nPetGuid        = pBreedPet->breedInfo.targetGuid;
        GettheDBCon().SendMsg( &msgQuery , GetLifeCode() );
        return; 
    }

    if ( !pTeam->IsTeamHeader( GetDBCharacterID() ) )
    {
        MsgPetBreedAcquireAck msgAck;
        msgAck.result = MsgPetBreedAcquireAck::ER_TeamHeader;
        GettheServer().SendMsgToSingle( &msgAck, this );
        return; 
    }

    if ( pTeam->TeamMemberCount() != 2 )
    {
        MsgPetBreedAcquireAck msgAck;
        msgAck.result = MsgPetBreedAcquireAck::ER_TeamMember;
        GettheServer().SendMsgToSingle( &msgAck, this );
        return; 
    }

    for ( int i=0;i<pTeam->TeamMemberCount(); ++i )
    {
        if( pTeam->GetMemberIDByIndex( i ) != GetDBCharacterID() )
        {
            GamePlayer* pPlayer = theRunTimeData.GetGamePlayerByDBID( pTeam->GetMemberIDByIndex( i ) ) ;
            if ( pPlayer != NULL && pBreedPet->breedInfo.targetCharDBID != pPlayer->GetDBCharacterID() )
            {
                MsgPetBreedAcquireAck msgAck;
                msgAck.result = MsgPetBreedAcquireAck::ER_TeamMember;
                GettheServer().SendMsgToSingle( &msgAck, this );
                return; 
            }
        }
    }

    // ????????
    GamePlayer* pTargetPlayer = theRunTimeData.GetGamePlayerByDBID( pBreedPet->breedInfo.targetCharDBID );
    if ( pTargetPlayer == NULL )
    {
        MsgPetBreedAcquireAck msgAck;
        msgAck.result = MsgPetBreedAcquireAck::ER_TeamMember;
        GettheServer().SendMsgToSingle( &msgAck, this );
        return; 
    }

    if ( _petManager.GetPetEmptyCount() < 2 )
    {
        MsgPetBreedAcquireAck msgAck;
        msgAck.result = MsgPetBreedAcquireAck::ER_PetFull;
        GettheServer().SendMsgToSingle( &msgAck, this );
        return; 
    }

    if ( pTargetPlayer->_petManager.GetPetEmptyCount() < 2 )
    {
        MsgPetBreedAcquireAck msgAck;
        msgAck.result = MsgPetBreedAcquireAck::ER_PetFull;
        GettheServer().SendMsgToSingle( &msgAck, this );
        return; 
    }

    // ????????????
    PetBreedGenerate();
    pTargetPlayer->PetBreedGenerate();
}

bool GamePlayer::PetBreedGenerate()
{
    SPetItem* pBreedPet = _petManager.GetBreedPet();
    if ( pBreedPet == NULL )
    {
        MsgPetBreedAcquireAck msgAck;
        msgAck.result = MsgPetBreedAcquireAck::ER_NoBreedPet;
        GettheServer().SendMsgToSingle( &msgAck, this );
        return false; 
    }

    ItemDefine::SPetMonster* pMonsterConfig = GettheItemDetail().GetPetById( pBreedPet->GetPetID() );
    if ( pMonsterConfig == NULL ) 
    {
        MsgPetBreedAcquireAck msgAck;
        msgAck.result = MsgPetBreedAcquireAck::ER_NoBreedPet;
        GettheServer().SendMsgToSingle( &msgAck, this );
        return false; 
    }

    int babyId  = 0;
    int quality = (pBreedPet->baseInfo.quality + pBreedPet->breedInfo.targetQuality) / 2;

    for ( int i=0; i < ItemDefine::SPetMonster::EPet_BabyListIDCount; ++i )
    {
        int nRateNum = theRand.rand32() % PET_BREED_PROBABILITY;
        int nBabyListIdRate = pMonsterConfig->babyListIdRate[i];
        if ( nRateNum < nBabyListIdRate )
        {
            babyId = pMonsterConfig->babyListId[i];
            break;
        }
    }

    if ( babyId == 0 )
    { babyId = pMonsterConfig->babyId; }

    int64 nNewGuid = AddPet( babyId, quality, theRand.rand16() % Sex_Max, 1, EPetSource_Breed );

    pBreedPet->baseInfo.breedNum += 1;
    AddPet( *pBreedPet, EPetSource_Breed );

    MsgPetBreedAcquireAck msgAck;
    msgAck.result = MsgPetBreedAcquireAck::ER_Success;
    msgAck.pet    = *pBreedPet;
    GettheServer().SendMsgToSingle( &msgAck, this );

    PetBreedBroadcast( pBreedPet->baseInfo.guid, nNewGuid );

    _petManager.ClearBreedPet();
    return true;
}

void GamePlayer::PetBreedBroadcast( int64 nOldGuid , int64 nNewGuid )
{
    SPetItem* pOldPet = _petManager.GetPetByGuid( nOldGuid );
    SPetItem* pNewPet = _petManager.GetPetByGuid( nNewGuid );
    if ( pOldPet == NULL || pNewPet == NULL )
    { return; }

    MsgChat chat(MsgChat::CHAT_TYPE_PROGRAM_SYSTEM);
    chat.type = BT_PetBag;
    chat.nHyberItemCnt = 1;
    chat.onlyId[0] = pNewPet->baseInfo.guid;

    char bufStr[BUFSIZ] = {0};
    sprintf_s( bufStr,sizeof(bufStr), theXmlString.GetString(eText_PetBreedSuccess), GetCharName(), pNewPet->baseInfo.szName );

    ProcessSystem( bufStr, SystemWorld, &chat );
}

uint32 GamePlayer::GetOnLineTime()
{
    if (gTransferRuntimeInfo.OnLineTime /*m_nEnterTime*/ == 0 )
    { return 0; }

    return GameTime::GetPassTime( HQ_TimeGetTime(), gTransferRuntimeInfo.OnLineTime );
}

uint32 GamePlayer::GetOnlineRealTime()
{
	if ( 0 == _nEnterRealTime )
	{ return 0; }

	TimeEx xStartTime( _nEnterRealTime );
	TimeEx xCurTime = TimeEx::GetCurrentTime();
	if ( xStartTime > xCurTime)
	{ 
		xStartTime = xCurTime; 
		return 0;
	}

	TimeSpan xTimeSpan = TimeEx::GetCurrentTime() - xStartTime;
	return xTimeSpan.GetTotalSeconds();    
}

void GamePlayer::ProcessChangeToMap()
{
    if ( 0 )
    {
        // ??????????
        //if( HaveProtectChar() )
        //{
        //    MonsterBase* pAiChar = (MonsterBase*) theRunTimeData.GetCharacterByID( GetProtectCharID() );
        //    if ( pAiChar != NULL && !pAiChar->IsPet() )
        //    {   
        //        SetRunTimePetInfo( gTransferRuntimeInfo.xPetInfo[EPT_Protect], pAiChar );
        //        KillProtectChar();
        //    }
        //}

        //if( HaveSummonPet() )
        //{
        //    for (int i=0;i<CharSummonPetMaxCount; ++i)
        //    {
        //        MonsterBase* pAiChar = (MonsterBase*) theRunTimeData.GetCharacterByID( m_xSummonPets[i].petId );
        //        if ( pAiChar != NULL && pAiChar->IsPet() && !pAiChar->IsIllusionChar() )
        //        {
        //            if( pAiChar->GetMonsterType() == eMT_Pet )
        //            {
        //                SetRunTimePetInfo( gTransferRuntimeInfo.xPetInfo[EPT_Skill], pAiChar );
        //            }
        //            pAiChar->SetDead();
        //            pAiChar->WasKilled(this);
        //        }

        //        m_xSummonPets[i].Clear();
        //    }
        //}

        //if( HaveCapturePet() )
        //{
        //    MonsterBase* pAiChar = (MonsterBase*) theRunTimeData.GetCharacterByID( GetCapturePetId() );
        //    if ( pAiChar != NULL && pAiChar->IsPet() )
        //    {
        //        SetRunTimePetInfo( gTransferRuntimeInfo.xPetInfo[EPT_Capture], pAiChar );
        //        pAiChar->SetDead();
        //        KillCapturePet();
        //    }
        //}
    }
}

void GamePlayer::ProcessGuideQuest( int nType )
{
    // ????????????
    if ( BitValue< unsigned long >::GetBitValue( nType, gCharInfoServer.extendData.dwGuideQuestInfo ) != BitValue< unsigned long >::NoneValue )
    { return; }

    // ????
    BitValue< unsigned long >::SetBitValue( nType, gCharInfoServer.extendData.dwGuideQuestInfo );   

    switch( nType )
    {
    case GuideQuest::Guide_Team:
        { _achieveManager.UpdateTriggerByValueType( EAT_FirstTeam ); }
        break;
    case GuideQuest::Guide_Friend:
        { _achieveManager.UpdateTriggerByValueType( EAT_FirstFriend ); }
        break;
    case GuideQuest::Guide_Guild:
        { _achieveManager.UpdateTriggerByValueType( EAT_JoinGuild ); }
        break;
    }
}

bool GamePlayer::IsLessThenMapLevel( uint32 nMapID )
{
    MapConfig::MapData* pMapData = theMapConfig.GetMapDataById( EctypeId2MapId( nMapID ) );
    if ( pMapData == NULL )
    { return false; }

    if ( GetLevel() < pMapData->MinPlayerLevel )
    {
        ShowInfo( false, 251, theXmlString.GetString( eTellClient_LessMapMinLevel ), pMapData->MinPlayerLevel );
        return true; 
    }

    return false;
}

bool GamePlayer::CheckPunishHell( uint32 nMapID )
{
    const CountryConfig::SpecialMapSetting* pSetting = theCountryConfig.GetPrisonMapSetting( GetCountry() );
    if ( pSetting->GetMapID() != EctypeId2MapId( nMapID ) )
    { return false; }
    return GetPKValue() > /*PKHellleaveValue*/thePKConfig.GetLeaveJianYu();
}
bool GamePlayer::CheckFlyToJianYu(uint32 nMapID)
{
	const CountryConfig::SpecialMapSetting* pSetting = theCountryConfig.GetPrisonMapSetting( GetCountry() );
    if ( pSetting->GetMapID() != EctypeId2MapId( nMapID ) )
    { return false; }
	return GetPKValue() < thePKConfig.GetEnterJianYu();
}
void GamePlayer::SetClientShowMapTimeStep(bool IsOpen,uint32 TimeStep)
{
	//?????????????????????????? ????????????
	MsgChangeMapTimeStepReq msg;
	msg.IsOpen = IsOpen;
	msg.TimeStep = TimeStep;
	SendMessageToClient(&msg);
}
void GamePlayer::StartChangeServerTimer(uint32 TimeStep)
{
	//????????????????????????
	if(m_xChangeServerTimer.IsStart())
		return;
	m_xChangeServerTimer.StartTimer( HQ_TimeGetTime(), TimeStep );
	SetClientShowMapTimeStep(true,TimeStep);
}
void GamePlayer::ReviceByFlyToMap()
{
	//?????????????? 
	if(IsDead())
	{
		SReliveInfo xReliveInfo;
		xReliveInfo.bFlyToMap = true;
		xReliveInfo.nReliveHP = 20;
		xReliveInfo.nReliveMP = 20;
		ProcessReliveToMap( GetMapID(), GetFloatX(), GetFloatY(), GetDir(), xReliveInfo );
	}
}
bool GamePlayer::FlyToMapReq(DWORD iMapID, float x, float y, float dir, bool bCheckCanFly /* = true */ )
{
    if ( m_xChangeServerTimer.IsStart() )
    { return false; }

	//???????????????????????? ??????????????????
	
	const CountryConfig::SpecialMapSetting* pSetting = theCountryConfig.GetPrisonMapSetting( GetCountry() );
    if ( pSetting->GetMapID() != EctypeId2MapId( iMapID ) )
	{
		if(GetPKValue() >= thePKConfig.GetEnterJianYu())
		{
			return FlyToMapReq(pSetting->GetMapID(), pSetting->GetPosX(), pSetting->GetPosY(), pSetting->GetDir(),false);
		}
	}
    if ( bCheckCanFly )
    {
        if (EctypeId2MapId(GetMapID()) != iMapID && CheckPunishHell( EctypeId2MapId(GetMapID())) )
        { return false; }

        if ( IsLessThenMapLevel( iMapID ) )
        { return false; }
    }

	//??????????????????????????????
	_mountManager.GotOffMultiMountExcludeDriver();

    MapConfig::MapData* pMapData = theMapConfig.GetMapDataById( EctypeId2MapId(iMapID) );
    if ( pMapData == NULL )
    { return false; }

    if ( pMapData->IsEctypeMap() )      // ????????????
    {   
        if(g_Cfg.IsMapRun( pMapData->Id ) )
			return FlyToMapAction( iMapID, FloatToTile( x ), FloatToTile( y ), dir );
		else
		{
			//??????????GameServer????????????
			//?????????????????????????????? ???????????? ???????????????????????? ??????ID??????
			//????DBID ???????? ????????ID ????????ID ????MapID ???? 
			DWORD dwMapDataId = 0;
			unsigned short ustLevel = 0;
			uint32 dwEctypeMapID = 0;
			DWORD dwReserveValue = 0;
			if(!IsCanFlyToMapAction(iMapID, FloatToTile( x ), FloatToTile( y ), dir,dwMapDataId,ustLevel,dwEctypeMapID,dwReserveValue))
				return false;
			//??????????centerserver ??????????		
			GS2CSCreateMulitStageReq msgCreate;
			msgCreate.PlayerDBID = GetDBCharacterID();
			msgCreate.MapID = dwMapDataId;
			msgCreate.EctypeMapID = dwEctypeMapID;
			msgCreate.Level = ustLevel;
			msgCreate.ReserveValue = dwReserveValue;
			msgCreate.x = x;
			msgCreate.y = y;
			msgCreate.dir = dir;
			msgCreate.GameServerID = g_Cfg.dwServerID;

			GettheServer().SendMsgToCenterServer( &msgCreate );
			
			StartChangeServerTimer(OneMinuteMicroSecond);
			//m_xChangeServerTimer.StartTimer( HQ_TimeGetTime(), OneMinuteMicroSecond );
			ReviceByFlyToMap();

			m_IsCanDead = false;

			return true;
		}
    }

    GameStage* pStage = theGameWorld.GetStageById( iMapID ); 
    if ( pStage != NULL)   // ????????????,??????
    { return FlyToMapAction( iMapID, FloatToTile( x ), FloatToTile( y ), dir ); }

    // ??????????????, ????centerserver
	ReviceByFlyToMap();

    GS2CSSwitchStageReq msg;//??????????GameServer????????
    msg.header.stID      = GetID();
    msg.nSwitchStageType = SSRT_FlyToMap;
    msg.nMapId           = iMapID;
    msg.fX               = x;
    msg.fY               = y;
    msg.fDir             = dir;
    msg.nAccountId       = GetAccountID();
    msg.nCharacterDbId   = GetDBCharacterID();
    msg.dwTime           = HQ_TimeGetTime();
    msg.nServerId        = g_Cfg.dwServerID;
    msg.ustCountryID     = GetCountry();
    GettheServer().SendMsgToCenterServer( &msg );

    SetFloatZ( WORLD_HEIGHT );     // ??????????, ????z??????

    // ????????????????
	StartChangeServerTimer(OneMinuteMicroSecond);

	m_IsCanDead = false;
    //m_xChangeServerTimer.StartTimer( HQ_TimeGetTime(), OneMinuteMicroSecond );
    return true;
}                                                                            
bool GamePlayer::IsCanFlyToMapAction(DWORD iMapID, int nTileX, int nTileY, float dir,DWORD& dwMapDataId,unsigned short& ustLevel,uint32& dwEctypeMapID,DWORD& dwReserveValue)
{
	if ( m_xChangeServerTimer.IsStart() )
    { return false; }

    if (EctypeId2MapId(GetMapID()) != iMapID && (CheckPunishHell( EctypeId2MapId(GetMapID()) )) )
    { return false; }

    if ( IsLessThenMapLevel( iMapID ) )
    { return false; }

	CheckPos( &iMapID, &nTileX, &nTileY, false );

	dwMapDataId = EctypeId2MapId( iMapID );

    MapConfig::MapData* pMapData = theMapConfig.GetMapDataById( dwMapDataId );
    if ( pMapData == NULL ) // ??????????????
    { return false; }

	ustLevel = GetPlayerEctypeMapLevel( GetMapID(), GetFloatX(), GetFloatY(), pMapData->GetMapType() );
    dwEctypeMapID = theGameWorld.MakeEctypeStageID( pMapData, this, ustLevel );

    switch( pMapData->GetMapType() )
    {
    case MapConfig::MT_SinglePlayer:
    case MapConfig::MT_MultiPlayer:
        dwReserveValue = GetDBCharacterID();
        break;
    case MapConfig::MT_SingleTeam:
    case MapConfig::MT_MultiTeam:
        dwReserveValue = GetTeamID();
        break;
    case MapConfig::MT_SingleGuild:
    case MapConfig::MT_MultiGuild:
        dwReserveValue = GetGuildID();
        break;
    default:
        break;
    }
	if ( dwEctypeMapID == 0 )
    { return false; }   // ??????????????ID

    // ????????????, ????????????
    //????????????????????, ????????
    if ( pMapData->IsSystemCreateMap() )   
    { return false; }
    
	return true;
}
bool GamePlayer::FlyToMapAction( DWORD iMapID, int nTileX, int nTileY, float fDir )
{
	//????FlyToMapReq????
    CheckPos( &iMapID, &nTileX, &nTileY, false );

    DWORD dwMapDataId = EctypeId2MapId( iMapID );

    MapConfig::MapData* pMapData = theMapConfig.GetMapDataById( dwMapDataId );
    if ( pMapData == NULL ) // ??????????????
    { return false; }

    GameStage* pStage = theGameWorld.GetStageById( iMapID );
    if ( !pMapData->IsEctypeMap() )     // ??????
    {
        if ( pStage == NULL )
        {
            LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_ERROR, "??????[%s]????????????????!", pMapData->MapName.c_str() );
            return false;
        }
        return ChangeToMap( pStage, nTileX, nTileY, fDir, __FILE__, __LINE__ );
    }
    ///////////////////////////////////////////////////////////////////////////////////////////////////////
    // ????????????
    unsigned short ustLevel = GetPlayerEctypeMapLevel( GetMapID(), GetFloatX(), GetFloatY(), pMapData->GetMapType() );
    uint32 dwEctypeMapID = 0;   // ????ID
    if ( pStage == NULL )   
    {
        // ??????????, ????????????????????????????
        dwEctypeMapID = theGameWorld.MakeEctypeStageID( pMapData, this, ustLevel );
        pStage = theGameWorld.GetStageById( dwEctypeMapID );
    }

    // ????????????
    DWORD dwReserveValue = 0;   
    switch( pMapData->GetMapType() )
    {
    case MapConfig::MT_SinglePlayer:
    case MapConfig::MT_MultiPlayer:
        dwReserveValue = GetDBCharacterID();
        break;
    case MapConfig::MT_SingleTeam:
    case MapConfig::MT_MultiTeam:
        dwReserveValue = GetTeamID();
        break;
    case MapConfig::MT_SingleGuild:
    case MapConfig::MT_MultiGuild:
        dwReserveValue = GetGuildID();
        break;
	/*case MapConfig::MT_MultiWar:
		dwReserveValue = GetGuildID();*/
    default:
        break;
    }

    // ??????????????
    if ( pStage != NULL )   
    {
        EctypeStage* pEctypeStage = static_cast< EctypeStage* >( pStage );
        // ????????????????????
        if ( pEctypeStage->IsStageWaitingRelease() )
        {
            // ?????????????? ????????????,??????????????????,????????????????

			//????????????????????????????????????????????????????????????,???????????????????????????????? by vvx 2012.8.23
            //if ( pMapData->GetMapType() != MapConfig::MT_SingleGuild)
			if(pMapData->GetMapType() == MapConfig::MT_Period)
            {
                ShowInfo( false, 251, theXmlString.GetString( eClient_AddInfo_2slk_120 ) );
                return false;
            }


            pEctypeStage->SetStageWaitRelease( false );
        }

        // ????????????
        pEctypeStage->AddReserve( dwReserveValue );        
        return ChangeToMap( pStage, nTileX, nTileY, fDir, __FILE__, __LINE__ );
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    if ( dwEctypeMapID == 0 )
    { return false; }   // ??????????????ID

    // ????????????, ????????????
    //????????????????????, ????????
    if ( pMapData->IsSystemCreateMap() )   
    { return false; }

    // ??????????????????????
    if ( pMapData->IsMapCountLimitMap() && theGameWorld.GetMapCount( iMapID ) >= pMapData->Count )
    {
        ShowInfo( false, 251, theXmlString.GetString( eClient_AddInfo_2slk_46 ) );
        return false;
    }

    // ??MT_PlayerLimit??????????????????????     // ????????
    theGameWorld.MultiCreateStage( dwMapDataId, dwEctypeMapID, ustLevel, dwReserveValue );
    
    // ????????????????????, ????????????
    SetWaitChangeStage( GamePlayer::EnterStage, dwEctypeMapID, TileToFloat( nTileX ), TileToFloat( nTileY ), fDir, 60, false );
    return true;
}

unsigned short GamePlayer::GetPlayerEctypeMapLevel( uint32 nMapID, float fX, float fY, uint8 nMapType )
{
    unsigned short ustLevel = 0;

    switch ( nMapType )
    {
    case MapConfig::MT_SingleTeam:
    case MapConfig::MT_MultiTeam:
        {
            GameTeam* pTeam = theGameTeamManager.GetTeam( GetTeamID() );
            if ( pTeam != NULL )
            {
                int nTeamCount = pTeam->GetTeamMemberCountInMap( nMapID, fX, fY );
                int nMinLevel = 0;
                int nMaxLevel = 0;
                int nTeamTotalLevel = pTeam->GetTeamMemberLevelDistance( nMapID, fX, fY, nMinLevel, nMaxLevel );
                if ( nTeamCount != 0 )
                { ustLevel = nTeamTotalLevel / nTeamCount; }
            }

            // ????????????
            if ( ustLevel == 0 )
            { ustLevel = GetLevel(); }
        }
        break;
    case MapConfig::MT_SinglePlayer:
    case MapConfig::MT_MultiPlayer:
        {
            ustLevel = GetLevel();
        }
        break;
    default:
        break;
    }

    // ????????????????
    ustLevel = ( ustLevel + MAPLEVELPERPLAYERLEVEL - 1 ) / MAPLEVELPERPLAYERLEVEL;
    if ( ustLevel > MAX_MAP_LEVEL )
    { ustLevel = MAX_MAP_LEVEL; }

    return ustLevel;
}

bool GamePlayer::ChangeToMap( GameStage* pStage, int nTileX, int nTileY, float dir, const char* szFile, uint32 line )
{
    if ( pStage == NULL )
    { return false; }

    if( !pStage->Moveable( this, nTileX, nTileY ) )
    {
        //Log( "????????????: Stage[%u](%d,%d)", pStage->GetStageID(), nTileX, nTileY );
		 Log( "????????????: Stage[%u](%d,%d)", pStage->GetStageID(), nTileX, nTileY );
        OnExit( NULL );
        return false;
    }

	ReviceByFlyToMap();

    ProcessChangeToMap();

    GameWorld::SFlashMoveTo flash;
    flash.dwMapID = pStage->GetStageID();
    flash.x       = nTileX;
    flash.y       = nTileY;
    flash.fDir    = dir;
    theGameWorld.GlobalMessage( GameWorld::ExtMsg_FlashMoveTo, (WPARAM)GetID(), (LPARAM)&flash );
    return true;
}

void GamePlayer::SetWaitChangeStage( uint8 uchType, uint32 nMapID, float fX, float fY, float fDir, uint32 nSpaceTime, bool bSendMessage )
{
    m_xWaitChangeStage .uchType       = uchType;
    m_xWaitChangeStage.dwCurrentMapID = GetMapID();
    m_xWaitChangeStage.dwMapID        = nMapID;
    m_xWaitChangeStage.fX             = fX;
    m_xWaitChangeStage.fY             = fY;
    m_xWaitChangeStage.fDir           = fDir;
    m_xWaitChangeStage.xTimer.StartTimer( HQ_TimeGetTime(), nSpaceTime * 1000 );

    if ( bSendMessage )
    {   // ????????????
        SendErrorToClient( ER_LeaveStage, nSpaceTime );
    }
};

void GamePlayer::ProcessWaitChangeStage() 
{
    if ( !m_xWaitChangeStage.xTimer.IsStart() || m_xWaitChangeStage.dwMapID == 0 )
    { return; }

    // ??????????????????
    if ( m_xWaitChangeStage.dwCurrentMapID != GetMapID() )
    {
        m_xWaitChangeStage.xTimer.StopTimer();
        return;
    }

    switch ( m_xWaitChangeStage.uchType )
    {
    case GamePlayer::EnterStage:        // ????????
        {
            if ( m_xWaitChangeStage.xTimer.DoneTimer() )
            { return; }

           /* GameStage *pStage = theGameWorld.GetStageById( m_xWaitChangeStage.dwMapID );
            if ( pStage == NULL )
            { return; }*/

            // ????????????
            switch ( GetChangeStageType() )
            {
            case GamePlayer::PlayerChangeStage:
                {
					FlyToMapReq(m_xWaitChangeStage.dwMapID, m_xWaitChangeStage.fX,m_xWaitChangeStage.fY,m_xWaitChangeStage.fDir);
                    //ChangeToMap( pStage, FloatToTile( m_xWaitChangeStage.fX ), FloatToTile( m_xWaitChangeStage.fY ), m_xWaitChangeStage.fDir, __FILE__, __LINE__ );
                }
                break;
            case GamePlayer::TeamChangeStage:
                {
                    GameTeam* pTeam = theGameTeamManager.GetTeam( GetTeamID() );
                    if ( pTeam != NULL )
                    { 
						//pTeam->TeamChangeStage( pStage, FloatToTile( m_xWaitChangeStage.fX ), FloatToTile( m_xWaitChangeStage.fY ), m_xWaitChangeStage.fDir ); 
						//????????????????????
						pTeam->CallAllTeamPlayerFlyToMapReq(m_xWaitChangeStage.dwMapID, m_xWaitChangeStage.fX,m_xWaitChangeStage.fY,m_xWaitChangeStage.fDir);
					}
                }
                break;
            default:
                return;
                break;
            }

            SetChangeStageType( GamePlayer::PlayerChangeStage );
        }
        break;
    case GamePlayer::LeaveStage:
        {
            if ( !m_xWaitChangeStage.xTimer.DoneTimer() )
            { return; }

            FlyToMapReq( m_xWaitChangeStage.dwMapID, m_xWaitChangeStage.fX, m_xWaitChangeStage.fY, m_xWaitChangeStage.fDir );
        }
        break;
    default:
        break;
    }
}

uint32 GamePlayer::GetMaxMoney()
{
    uint32 limitMaxMoney = MaxMoney30;
    if ( GetLevel() > 55 )
    {
        limitMaxMoney = MaxMoney60;
    }
    else if ( GetLevel() > 40 )
    {
        limitMaxMoney = MaxMoney55;
    }
    else if ( GetLevel() > 30 )
    {
        limitMaxMoney = MaxMoney40;
    }

    return limitMaxMoney;
}

bool GamePlayer::CheckCanAddMoney( DWORD dwAddMoney )
{
    uint32 nMaxMoney = GetMaxMoney();
    return ( dwAddMoney + GetMoney() + _StorageBag.dwStorageMoney <= nMaxMoney );
}

uint32 GamePlayer::GetMaxJiaoZi()
{
    uint32 limitMaxMoney = MaxJiaoZi30;
    if ( GetLevel() > 55 )
    {
        limitMaxMoney = MaxJiaoZi60;
    }
    else if ( GetLevel() > 40 )
    {
        limitMaxMoney = MaxJiaoZi55;
    }
    else if ( GetLevel() > 30 )
    {
        limitMaxMoney = MaxJiaoZi40;
    }

    return limitMaxMoney;
}

bool GamePlayer::CheckCanAddJiaoZi( DWORD dwAddJiaoZi )
{
    return dwAddJiaoZi + GetJiaoZi() <= GetMaxJiaoZi(); 
}

void GamePlayer::OperateActivity( uint8 uchOperateType, int nValue, bool bSendMessage /* = true */ )
{
    if ( nValue == 0 && uchOperateType != EOT_Set )
    { return; }

    switch( uchOperateType ) 
    {
    case EOT_Add:
        gCharInfoServer.baseinfo.liveinfo.activity += nValue;
        break;
    case EOT_Sub:
        {
            if (gCharInfoServer.baseinfo.liveinfo.activity < nValue)
            { gCharInfoServer.baseinfo.liveinfo.activity = 0; }
            else
            { gCharInfoServer.baseinfo.liveinfo.activity -= nValue; }
        }
        break;
    case EOT_Set:
        gCharInfoServer.baseinfo.liveinfo.activity = nValue;
        break;
    }

    if (gCharInfoServer.baseinfo.liveinfo.activity > GetActivityMax())
    { gCharInfoServer.baseinfo.liveinfo.activity = GetActivityMax(); }

    if (bSendMessage)
    { ChangeAttr( CharAttr_Energy, gCharInfoServer.baseinfo.liveinfo.activity, true ); }
}


void GamePlayer::OperateMoney( uint8 uchOperateType, uint32 nValue, bool bSendMessage, char* szFunction, int nLine ,int16 sourcetype)
{
    if ( nValue == 0 && uchOperateType != EOT_Set )
    { return; }

    Log( theXmlString.GetString( eLog_Money_1 ), szFunction, nLine, GetMoney() );

    switch ( uchOperateType )
    {
    case EOT_Add:
        {
            int nCanAdd = g_Cfg.m_nMoneyMax - GetMoney();
            if ( nCanAdd < nValue )
            { nValue = nCanAdd; }
            if ( nValue == 0 )
            { return; }

			if ( _bNeedAntiAddiction )
			{ // ??????????
				if ( enumAntiAddictionStateTired == gTransferRuntimeInfo.nAntiAddicationStatus)
				{
					nValue /= 2;
				}
				else if (enumAntiAddictionStateRest == gTransferRuntimeInfo.nAntiAddicationStatus )
				{
					nValue = 0;
				}
			}

            gCharInfoServer.baseinfo.liveinfo.dwMoney += nValue;

			//LYH???????? ????????
			if (!theLogEventService.LogCurrency(GetAccountID(),GetDBCharacterID(),nValue,ePlayerMoneyType_Money,ePlayerCurrency_Add,GetCharName(),sourcetype))
			{
				Log( theXmlString.GetString( eLog_Money_2 ), szFunction, nLine, nValue, GetMoney() );
			}
            
        }
        break;
    case EOT_Sub:
        {
            if ( nValue > GetMoney() )
            { nValue = GetMoney(); }

            gCharInfoServer.baseinfo.liveinfo.dwMoney -= nValue;

			//LYH???????? ????????
			if (!theLogEventService.LogCurrency(GetAccountID(),GetDBCharacterID(),nValue,ePlayerMoneyType_Money,ePlayerCurrency_Sub,GetCharName(),sourcetype))
				Log( theXmlString.GetString( eLog_Money_3 ), szFunction, nLine, nValue, GetMoney() );
        }
        break;
    case EOT_Set:
        {
			uint32 moneytemp = gCharInfoServer.baseinfo.liveinfo.dwMoney;
            gCharInfoServer.baseinfo.liveinfo.dwMoney = nValue;

			if (moneytemp > nValue)
			{
				theLogEventService.LogCurrency(GetAccountID(),GetDBCharacterID(),moneytemp - nValue,ePlayerMoneyType_Money,ePlayerCurrency_Sub,GetCharName(),sourcetype);
			}
			else if (moneytemp < nValue)
			{
				theLogEventService.LogCurrency(GetAccountID(),GetDBCharacterID(),nValue - moneytemp,ePlayerMoneyType_Money,ePlayerCurrency_Add,GetCharName(),sourcetype);
			}
            Log( theXmlString.GetString( eLog_Money_4 ), szFunction, nLine, nValue, GetMoney() );
        }
        break;
    default:
        return;
        break;
    }

    _achieveManager.UpdateTriggerByValueType( EAT_Money, GetMoney() );

    if ( bSendMessage )
    {
        MsgJiaoZiChange xChange;
        xChange.dwNumber = GetMoney();
        xChange.dwJiaoZi = GetJiaoZi();
        SendMessageToClient( &xChange );
    }
}

void GamePlayer::OperateJiaoZi( uint8 uchOperateType, uint32 nValue, bool bSendMessage, char* szFunction, int nLine,int16 sourcetype )
{
    if ( nValue == 0 && uchOperateType != EOT_Set )
    { return; }

    
    Log( theXmlString.GetString( eLog_JiaoZi_1 ), szFunction, nLine, GetJiaoZi() );

    switch ( uchOperateType )
    {
    case EOT_Add:
        {
            int nCanAdd = g_Cfg.m_nMaxJiaoZi - GetJiaoZi();
            if ( nCanAdd < nValue )
            { nValue = nCanAdd; }
            if ( nValue == 0 )
            { return; }

			if ( _bNeedAntiAddiction )
			{ // ??????????
				if ( enumAntiAddictionStateTired == gTransferRuntimeInfo.nAntiAddicationStatus)
				{
					nValue /= 2;
				}
				else if (enumAntiAddictionStateRest == gTransferRuntimeInfo.nAntiAddicationStatus )
				{
					nValue = 0;
				}
			}

            gCharInfoServer.baseinfo.liveinfo.jiaoZi += nValue;

			//LYH???????? ???????? ????
			if (!theLogEventService.LogCurrency(GetAccountID(),GetDBCharacterID(),nValue,ePlayerMoneyType_BMoney,ePlayerCurrency_Add,GetCharName(),sourcetype))
				Log( theXmlString.GetString( eLog_JiaoZi_2 ), szFunction, nLine, nValue, GetJiaoZi() );
        }
        break;
    case EOT_Sub:
        {
            if ( nValue > GetJiaoZi() )
            { 
                // ????????, ????
                OperateMoney( EOT_Sub, nValue - GetJiaoZi(), false, __FUNCTION__, __LINE__,sourcetype );       
                nValue = GetJiaoZi(); 
            }

            gCharInfoServer.baseinfo.liveinfo.jiaoZi -= nValue;

			//LYH???????? ????????
			if (!theLogEventService.LogCurrency(GetAccountID(),GetDBCharacterID(),nValue,ePlayerMoneyType_BMoney,ePlayerCurrency_Sub,GetCharName(),sourcetype))
				Log( theXmlString.GetString( eLog_JiaoZi_3 ), szFunction, nLine, nValue, GetJiaoZi() );
        }
        break;
    case EOT_Set:
        {
			uint32  tempjiaozi = gCharInfoServer.baseinfo.liveinfo.jiaoZi;
            gCharInfoServer.baseinfo.liveinfo.jiaoZi = nValue;
			if (tempjiaozi > nValue)
			{
				theLogEventService.LogCurrency(GetAccountID(),GetDBCharacterID(),tempjiaozi - nValue,ePlayerMoneyType_BMoney,ePlayerCurrency_Sub,GetCharName(),sourcetype);
			}
			else if (tempjiaozi < nValue)
			{
				theLogEventService.LogCurrency(GetAccountID(),GetDBCharacterID(),nValue - tempjiaozi,ePlayerMoneyType_BMoney,ePlayerCurrency_Add,GetCharName(),sourcetype);
			}
            Log( theXmlString.GetString( eLog_JiaoZi_4 ), szFunction, nLine, nValue, GetJiaoZi() );
        }
        break;
    default:
        return;
        break;
    }

    _achieveManager.UpdateTriggerByValueType( EAT_JiaoZi , GetJiaoZi() );

    if ( bSendMessage )
    {
        MsgJiaoZiChange xChange;
        xChange.dwNumber = GetMoney();
        xChange.dwJiaoZi = GetJiaoZi();
        SendMessageToClient( &xChange );
    }
}

//???????????? ????????
void GamePlayer::OperateConsumeScore( uint8 uchOperateType, uint32 nValue, char* szFunction, int nLine,int16 sourcetype,bool bSyncToDB)
{
	if ( nValue == 0 && uchOperateType != EOT_Set )
	{ return; }

	Log( theXmlString.GetString( eLog_info_2slk_131 ), szFunction, nLine, GetConsumeScore() );

	DBMsgOperateAccountConsumeScore ConsumeScore;
	ConsumeScore.header.stID = GetID();
	ConsumeScore.account_id = GetAccountID();
	ConsumeScore.character_id = GetDBCharacterID();

	switch ( uchOperateType )
	{
	case EOT_Add:
		{
			gCharInfoServer.baseinfo.liveinfo.ConsumeScore += nValue;
			//LYH???????? ????????
			theLogEventService.LogCurrency(GetAccountID(),GetDBCharacterID(),nValue,ePlayerMoneyType_Jifen,ePlayerCurrency_Add,GetCharName(),sourcetype);			

			ConsumeScore.operate_flag = 1;
		}
		break;
	case EOT_Sub:
		{
			if ( GetConsumeScore() < nValue )
			{ nValue = GetConsumeScore(); }

			gCharInfoServer.baseinfo.liveinfo.ConsumeScore -= nValue;

			//LYH???????? ????????
			theLogEventService.LogCurrency(GetAccountID(),GetDBCharacterID(),nValue,ePlayerMoneyType_Jifen,ePlayerCurrency_Sub,GetCharName(),sourcetype);
			ConsumeScore.operate_flag = 0;
		}
		break;
	case EOT_Set:
		{
			uint32 tempcs = gCharInfoServer.baseinfo.liveinfo.ConsumeScore;
			gCharInfoServer.baseinfo.liveinfo.ConsumeScore = nValue;

			if (tempcs > nValue)
			{
				theLogEventService.LogCurrency(GetAccountID(),GetDBCharacterID(),tempcs - nValue,ePlayerMoneyType_Jifen,ePlayerCurrency_Sub,GetCharName(),sourcetype);
			}
			else if (tempcs < nValue)
			{
				theLogEventService.LogCurrency(GetAccountID(),GetDBCharacterID(),nValue - tempcs,ePlayerMoneyType_Jifen,ePlayerCurrency_Add,GetCharName(),sourcetype);
			}
			//Log( theXmlString.GetString( eLog_info_2slk_134 ), szFunction, nLine, nValue, gCharInfoServer.baseinfo.liveinfo.jinDing );

			ConsumeScore.operate_flag = 2;
		}
		break;
	default:
		return;
		break;
	}

	if (bSyncToDB)
	{		
		ConsumeScore.modify_money = nValue;
		GettheDBCon().SendMsg( &ConsumeScore, GetLifeCode() );
	}

	MsgRMBConsumeScore xChange;
	xChange.header.stID = GetID();
	xChange.jifen     = GetConsumeScore();	
	SendMessageToClient( &xChange );

}

void GamePlayer::OperateJinDing( uint8 uchOperateType, uint32 nValue, char* szFunction, int nLine,int16 sourcetype,bool bSyncToDB)
{
    if ( nValue == 0 && uchOperateType != EOT_Set )
    { return; }

    Log( theXmlString.GetString( eLog_info_2slk_131 ), szFunction, nLine, GetJinDing() );

	DBMsgOperateAccountMoney operatejinding;
	operatejinding.header.stID = GetID();
	operatejinding.account_id = GetAccountID();
	operatejinding.character_id = GetDBCharacterID();

    switch ( uchOperateType )
    {
    case EOT_Add:
        {
            gCharInfoServer.baseinfo.liveinfo.jinDing += nValue;

			//LYH???????? ????????
			if (!theLogEventService.LogCurrency(GetAccountID(),GetDBCharacterID(),nValue,ePlayerMoneyType_Gold,ePlayerCurrency_Add,GetCharName(),sourcetype))
				Log( theXmlString.GetString( eLog_info_2slk_132 ), szFunction, nLine, nValue, gCharInfoServer.baseinfo.liveinfo.jinDing );

			operatejinding.operate_flag = 1;
        }
        break;
    case EOT_Sub:
        {
            if ( GetJinDing() < nValue )
            { nValue = GetJinDing(); }

            gCharInfoServer.baseinfo.liveinfo.jinDing -= nValue;

			//LYH???????? ????????
			if (!theLogEventService.LogCurrency(GetAccountID(),GetDBCharacterID(),nValue,ePlayerMoneyType_Gold,ePlayerCurrency_Sub,GetCharName(),sourcetype))
				Log( theXmlString.GetString( eLog_info_2slk_133 ), szFunction, nLine, nValue, gCharInfoServer.baseinfo.liveinfo.jinDing );

			operatejinding.operate_flag = 0;
        }
        break;
    case EOT_Set:
        {
			uint32 tempjinding = gCharInfoServer.baseinfo.liveinfo.jinDing;
            gCharInfoServer.baseinfo.liveinfo.jinDing = nValue;

			if (tempjinding > nValue)
			{
				theLogEventService.LogCurrency(GetAccountID(),GetDBCharacterID(),tempjinding - nValue,ePlayerMoneyType_Gold,ePlayerCurrency_Sub,GetCharName(),sourcetype);
			}
			else if(tempjinding < nValue)
			{
				theLogEventService.LogCurrency(GetAccountID(),GetDBCharacterID(),nValue - tempjinding,ePlayerMoneyType_Gold,ePlayerCurrency_Add,GetCharName(),sourcetype);
			}

            Log( theXmlString.GetString( eLog_info_2slk_134 ), szFunction, nLine, nValue, gCharInfoServer.baseinfo.liveinfo.jinDing );

			operatejinding.operate_flag = 2;
        }
        break;
    default:
        return;
        break;
    }

	if (bSyncToDB)
	{		
		operatejinding.modify_money = nValue;
		GettheDBCon().SendMsg( &operatejinding, GetLifeCode() );
	}

    MsgRMBGoldChange xChange;
    xChange.header.stID = GetID();
    xChange.jinDing     = GetJinDing();
    xChange.jinPiao     = GetJinPiao();
    SendMessageToClient( &xChange );
}


void GamePlayer::OperateJinPiao( uint8 uchOperateType, uint32 nValue, char* szFunction, int nLine,int16 sourcetype )
{
    if ( nValue == 0 && uchOperateType != EOT_Set )
    { return ; }

    Log(theXmlString.GetString( eLog_JingPiao_1 ), szFunction, nLine, GetJinPiao() );

    switch ( uchOperateType )
    {
    case EOT_Add:
        {
            gCharInfoServer.baseinfo.liveinfo.jinPiao += nValue;

			//LYH???????? ????????
			if (!theLogEventService.LogCurrency(GetAccountID(),GetDBCharacterID(),nValue,ePlayerMoneyType_BGold,ePlayerCurrency_Add,GetCharName(),sourcetype))
				Log( theXmlString.GetString( eLog_JingPiao_2 ), szFunction, nLine, nValue, gCharInfoServer.baseinfo.liveinfo.jinPiao );
        }
        break;
    case EOT_Sub:
        {
            if ( GetJinPiao() < nValue )
            { nValue = GetJinPiao(); }

            gCharInfoServer.baseinfo.liveinfo.jinPiao -= nValue;

			//LYH???????? ????????
			if (!theLogEventService.LogCurrency(GetAccountID(),GetDBCharacterID(),nValue,ePlayerMoneyType_BGold,ePlayerCurrency_Sub,GetCharName(),sourcetype))
				Log( theXmlString.GetString( eLog_JingPiao_3 ), szFunction, nLine, nValue, gCharInfoServer.baseinfo.liveinfo.jinPiao );
        }
        break;
    case EOT_Set:
        {
			uint32 tempjinpiao = gCharInfoServer.baseinfo.liveinfo.jinPiao ;
            gCharInfoServer.baseinfo.liveinfo.jinPiao = nValue;
			if (tempjinpiao > nValue)
			{
				theLogEventService.LogCurrency(GetAccountID(),GetDBCharacterID(),tempjinpiao - nValue,ePlayerMoneyType_BGold,ePlayerCurrency_Sub,GetCharName(),sourcetype);
			}
			else if (tempjinpiao < nValue)
			{
				theLogEventService.LogCurrency(GetAccountID(),GetDBCharacterID(),nValue - tempjinpiao,ePlayerMoneyType_BGold,ePlayerCurrency_Add,GetCharName(),sourcetype);
			}
            Log( theXmlString.GetString( eLog_JingPiao_4 ), szFunction, nLine, nValue, gCharInfoServer.baseinfo.liveinfo.jinPiao );
        }
        break;
    default:
        return;
        break;
    }

    MsgRMBGoldChange xChange;
    xChange.header.stID = GetID();
    xChange.jinDing     = GetJinDing();
    xChange.jinPiao     = GetJinPiao();
    SendMessageToClient( &xChange );
}

void GamePlayer::OperateHonour( uint8 uchOperateType, uint32 nValue, char* szFunction, int nLine ,int16 sourcetype)
{
    if ( nValue == 0 && uchOperateType != EOT_Set )
    { return; }

    Log(theXmlString.GetString( eLog_Honour_1 ), szFunction, nLine, gCharInfoServer.baseinfo.liveinfo.honour );

    switch ( uchOperateType )
    {
    case EOT_Add:
        {
			if(GetHonour() + nValue > g_Cfg.AllMaxHonour)
				nValue -= (GetHonour() + nValue - g_Cfg.AllMaxHonour);
            gCharInfoServer.baseinfo.liveinfo.honour += nValue;
            gCharInfoServer.otherdata.nRecordHonourCount += nValue;
			//LYH???????? ???? ????
			if(!theLogEventService.LogCurrency(GetAccountID(),GetDBCharacterID(),nValue,ePlayerMoneyType_Rongyu,ePlayerCurrency_Add,GetCharName(),sourcetype))
				Log(theXmlString.GetString( eLog_Honour_2 ), szFunction, nLine, nValue, gCharInfoServer.baseinfo.liveinfo.honour );

			//????7????
			_sevenDayManager.TriggerSevenDaysVar( (int)SevenDaysConfig::TD_ThirdDay, nValue );
        }
        break;
    case EOT_Sub:
        {
            if ( nValue > GetHonour() )
            { nValue = GetHonour(); }
            gCharInfoServer.baseinfo.liveinfo.honour -= nValue;

			//LYH???????? ???? ????
			if(!theLogEventService.LogCurrency(GetAccountID(),GetDBCharacterID(),nValue,ePlayerMoneyType_Rongyu,ePlayerCurrency_Sub,GetCharName(),sourcetype))
				Log(theXmlString.GetString( eLog_Honour_3 ), szFunction, nLine, nValue, gCharInfoServer.baseinfo.liveinfo.honour );
        }
        break;
    case EOT_Set:
        {
			if(nValue > g_Cfg.AllMaxHonour)
				nValue=g_Cfg.AllMaxHonour;
			uint32 temphonour =  gCharInfoServer.baseinfo.liveinfo.honour;
            gCharInfoServer.baseinfo.liveinfo.honour = nValue;
			if (temphonour > nValue)
			{
				theLogEventService.LogCurrency(GetAccountID(),GetDBCharacterID(),temphonour - nValue,ePlayerMoneyType_Rongyu,ePlayerCurrency_Sub,GetCharName(),sourcetype);
			}
			else if (temphonour < nValue)
			{
				theLogEventService.LogCurrency(GetAccountID(),GetDBCharacterID(),nValue - temphonour,ePlayerMoneyType_Rongyu,ePlayerCurrency_Add,GetCharName(),sourcetype);
			}
            Log(theXmlString.GetString( eLog_Honour_4 ), szFunction, nLine, nValue, gCharInfoServer.baseinfo.liveinfo.honour );
        }
        break;
    default:
        return;
        break;
    }

    _achieveManager.UpdateTriggerByValueType( EAT_Honour, GetHonour() );

    // ????????????????
    MsgCharAttrChanged xChange;
    xChange.header.stID = GetID();

    xChange.AddAttrDWORDChange( CharAttr_Honour, GetHonour() );
    switch ( uchOperateType )
    {
    case EOT_Add:
        xChange.AddAttrDWORDChange( CharAttr_CurGetHonour, nValue );
        break;
    }
    xChange.CaluLength();
    SendMessageToClient( &xChange );
}

void GamePlayer::OperateSkillExp( uint8 uchOperateType, uint32 nValue, char* szFunction, int nLine )
{
    if ( nValue == 0 && uchOperateType != EOT_Set )
    { return; }

   // Log("[%s:%d]?????????????????? ??????: %u", szFunction, nLine, gCharInfoServer.baseinfo.liveinfo.dwSkillExpNotUsed );
	
		Log(theXmlString.GetString(eServerLog_NoUseSkill), szFunction, nLine, gCharInfoServer.baseinfo.liveinfo.dwSkillExpNotUsed );

    switch ( uchOperateType )
    {
    case EOT_Add:
        {
			if ( _bNeedAntiAddiction )
			{ // ??????????
				if ( enumAntiAddictionStateTired == gTransferRuntimeInfo.nAntiAddicationStatus)
				{
					nValue /= 2;
				}
				else if (enumAntiAddictionStateRest == gTransferRuntimeInfo.nAntiAddicationStatus )
				{
					nValue = 0;
				}
			}

            gCharInfoServer.baseinfo.liveinfo.dwSkillExpNotUsed += nValue;
            gCharInfoServer.baseinfo.liveinfo.dwSkillExp += nValue; 
           // Log("[%s:%d]?????????????????? ??????: %u, ??????: %u", szFunction, nLine, nValue, gCharInfoServer.baseinfo.liveinfo.dwSkillExpNotUsed );
			Log(theXmlString.GetString(eServerLog_NoUseSkill1), szFunction, nLine, nValue, gCharInfoServer.baseinfo.liveinfo.dwSkillExpNotUsed );
        }
        break;
    case EOT_Sub:
        {
            if ( nValue > GetSkillExpUnUsed() )
            { nValue = GetSkillExpUnUsed(); }

            gCharInfoServer.baseinfo.liveinfo.dwSkillExpNotUsed -= nValue;
           // Log("[%s:%d]?????????????????? ??????: %u, ??????: %u", szFunction, nLine, nValue, gCharInfoServer.baseinfo.liveinfo.dwSkillExpNotUsed );
			 Log(theXmlString.GetString(eServerLog_NoUseSkill2), szFunction, nLine, nValue, gCharInfoServer.baseinfo.liveinfo.dwSkillExpNotUsed );
        }
        break;
    case EOT_Set:
        {
            gCharInfoServer.baseinfo.liveinfo.dwSkillExpNotUsed = nValue;
            //Log("[%s:%d]?????????????????? ??????: %u, ??????: %u", szFunction, nLine, nValue, gCharInfoServer.baseinfo.liveinfo.dwSkillExpNotUsed );
			Log(theXmlString.GetString(eServerLog_NoUseSkill3), szFunction, nLine, nValue, gCharInfoServer.baseinfo.liveinfo.dwSkillExpNotUsed );
        }
        break;
    default:
        return;
        break;
    }
}

void GamePlayer::OperateRecipeSkillPoint( uint8 uchOperateType, uint16 skillId, uint32 nValue, char* szFunction, int nLine )
{
    if ( nValue == 0 && uchOperateType != EOT_Set )
    { return; }

    int recipeType = theRecipeConfig.GetRecipeTypeBySkillId( skillId );
    if (recipeType < 0 || recipeType >= ERT_MaxType)
    { return; }


   // Log("[%s:%d]??????????????[%u]?????????? ??????: %u", szFunction, nLine, skillId, gCharInfoServer.baseinfo.liveinfo.nSkillPoint[ recipeType ] );
	Log(theXmlString.GetString(eServerLog_NoUseJobSkill), szFunction, nLine, skillId, gCharInfoServer.baseinfo.liveinfo.nSkillPoint[ recipeType ] );

    switch ( uchOperateType )
    {
    case EOT_Add:
        {
            gCharInfoServer.baseinfo.liveinfo.nSkillPoint[ recipeType ] += nValue;
            //Log("[%s:%d]??????????????[%u]?????????? ??????: %u", szFunction, nLine, skillId, nValue );
			Log(theXmlString.GetString(eServerLog_NoUseJobSkill1), szFunction, nLine, skillId, nValue );
        }
        break;
    case EOT_Sub:
        {
            if ( nValue >= gCharInfoServer.baseinfo.liveinfo.nSkillPoint[ recipeType ] )
            { nValue = gCharInfoServer.baseinfo.liveinfo.nSkillPoint[ recipeType ]; }

            gCharInfoServer.baseinfo.liveinfo.nSkillPoint[ recipeType ] -= nValue;
           // Log("[%s:%d]??????????????[%u]?????????? ??????: %u", szFunction, nLine, skillId, nValue );
			 Log(theXmlString.GetString(eServerLog_NoUseJobSkill2), szFunction, nLine, skillId, nValue );
        }
        break;
    case EOT_Set:
        {
            gCharInfoServer.baseinfo.liveinfo.nSkillPoint[ recipeType ] = nValue;
          //  Log("[%s:%d]??????????????[%u]?????????? ??????: %u", szFunction, nLine, skillId, nValue );
			Log(theXmlString.GetString(eServerLog_NoUseJobSkill3), szFunction, nLine, skillId, nValue );
        }
        break;
    default:
        return;
        break;
    }

}

void GamePlayer::OperateDaoxing( uint8 uchOperateType, uint32 nValue, char* szFunction, int nLine )
{
    if ( nValue == 0 && uchOperateType != EOT_Set )
    { return; }

   // Log("[%s:%d]???????? ????????: %u", szFunction, nLine, gCharInfoServer.baseinfo.liveinfo.daoxing );
	Log(theXmlString.GetString(eServerLog_NoUseDaoHang), szFunction, nLine, gCharInfoServer.baseinfo.liveinfo.daoxing );

    switch ( uchOperateType )
    {
    case EOT_Add:
        {
            gCharInfoServer.baseinfo.liveinfo.daoxing += nValue;
           // Log("[%s:%d]???????? ????????: %u, ????????: %u", szFunction, nLine, nValue, gCharInfoServer.baseinfo.liveinfo.daoxing );
			 Log(theXmlString.GetString(eServerLog_NoUseDaoHang1), szFunction, nLine, nValue, gCharInfoServer.baseinfo.liveinfo.daoxing );
        }
        break;
    case EOT_Sub:
        {
            if ( nValue > GetDaoxing() )
            { nValue = GetDaoxing(); }

            gCharInfoServer.baseinfo.liveinfo.daoxing -= nValue;

           // Log("[%s:%d]???????? ????????: %u, ????????: %u", szFunction, nLine, nValue, gCharInfoServer.baseinfo.liveinfo.daoxing );
			Log(theXmlString.GetString(eServerLog_NoUseDaoHang2), szFunction, nLine, nValue, gCharInfoServer.baseinfo.liveinfo.daoxing );
        }
        break;
    case EOT_Set:
        {
            gCharInfoServer.baseinfo.liveinfo.daoxing = nValue;
           // Log("[%s:%d]???????? ????????: %u, ????????: %u", szFunction, nLine, nValue, gCharInfoServer.baseinfo.liveinfo.daoxing );
			 Log(theXmlString.GetString(eServerLog_NoUseDaoHang3), szFunction, nLine, nValue, gCharInfoServer.baseinfo.liveinfo.daoxing );
        }
        break;
    default:
        return;
        break;
    }

    // ????????????????
    MsgCharAttrChanged xChange;
    xChange.header.stID = GetID();

    xChange.AddAttrDWORDChange( CharAttr_Daoxing, GetDaoxing() );
    switch ( uchOperateType )
    {
    case EOT_Add:
        xChange.AddAttrDWORDChange( CharAttr_CurGetDaoxing, nValue );
        break;
    }
    xChange.CaluLength();
    SendMessageToClient( &xChange );
}

void GamePlayer::OperateExploit( uint8 uchOperateType, uint32 nValue, char* szFunction, int nLine,int16 sourcetype )
{ 
    if ( nValue == 0 && uchOperateType != EOT_Set )
    { return; }

    Log( theXmlString.GetString( eLog_Exploit_1 ), szFunction, nLine, gCharInfoServer.baseinfo.liveinfo.exploit );

    switch ( uchOperateType )
    {
    case EOT_Add:
        {
            gCharInfoServer.baseinfo.liveinfo.exploit += nValue;
			//LYH ????????????
			if(!theLogEventService.LogCurrency(GetAccountID(),GetDBCharacterID(),nValue,ePlayerMoneyType_GongXun,ePlayerCurrency_Add,GetCharName(),sourcetype))
				Log( theXmlString.GetString( eLog_Exploit_2 ), szFunction, nLine, nValue, gCharInfoServer.baseinfo.liveinfo.exploit );
        }
        break;
    case EOT_Sub:
        {
            if ( nValue > GetExploit() )
            { nValue = GetExploit(); }

            gCharInfoServer.baseinfo.liveinfo.exploit -= nValue;

			//LYH ????????????
			if(!theLogEventService.LogCurrency(GetAccountID(),GetDBCharacterID(),nValue,ePlayerMoneyType_GongXun,ePlayerCurrency_Add,GetCharName(),sourcetype))
				Log( theXmlString.GetString( eLog_Exploit_3 ), szFunction, nLine, nValue, gCharInfoServer.baseinfo.liveinfo.exploit );
        }
        break;
    case EOT_Set:
        {
			uint32 tempexploit = gCharInfoServer.baseinfo.liveinfo.exploit;
            gCharInfoServer.baseinfo.liveinfo.exploit = nValue;
			if (tempexploit > nValue)
			{
				theLogEventService.LogCurrency(GetAccountID(),GetDBCharacterID(),tempexploit - nValue,ePlayerMoneyType_GongXun,ePlayerCurrency_Sub,GetCharName(),sourcetype);
			}
			else if (tempexploit < nValue)
			{
				theLogEventService.LogCurrency(GetAccountID(),GetDBCharacterID(),nValue - tempexploit,ePlayerMoneyType_GongXun,ePlayerCurrency_Add,GetCharName(),sourcetype);
			}
            Log( theXmlString.GetString( eLog_Exploit_4 ), szFunction, nLine, nValue, gCharInfoServer.baseinfo.liveinfo.exploit );
        }
        break;
    default:
        return;
        break;
    }

    _achieveManager.UpdateTriggerByValueType( EAT_Exploit , GetExploit() );

    // ????????????????
    MsgCharAttrChanged xChange;
    xChange.header.stID = GetID();

    xChange.AddAttrDWORDChange( CharAttr_Exploit, GetExploit() );
    switch ( uchOperateType )
    {
    case EOT_Add:
        xChange.AddAttrDWORDChange( CharAttr_CurGetExploit, nValue );
        break;
    }
    xChange.CaluLength();
    SendMessageToClient( &xChange );
}

void GamePlayer::OperateReputation( uint8 uchOperateType, uint32 nValue, char* szFunction, int nLine,int16 sourcetype )
{ 
    if ( nValue == 0 && uchOperateType != EOT_Set )
    { return; }

    Log( theXmlString.GetString( eLog_Reputation_1 ), szFunction, nLine, gCharInfoServer.baseinfo.liveinfo.reputation );

    switch ( uchOperateType )
    {
    case EOT_Add:
        {
            gCharInfoServer.baseinfo.liveinfo.reputation += nValue;
			//LYH???????? ????
			if (!theLogEventService.LogCurrency(GetAccountID(),GetDBCharacterID(),nValue,ePlayerMoneyType_ShengWang,ePlayerCurrency_Add,GetCharName(),sourcetype))
			{
				Log( theXmlString.GetString( eLog_Reputation_2 ), szFunction, nLine, nValue, gCharInfoServer.baseinfo.liveinfo.reputation );
			}			
        }
        break;
    case EOT_Sub:
        {
            if ( nValue > GetReputation() )
            { nValue = GetReputation(); }

            gCharInfoServer.baseinfo.liveinfo.reputation -= nValue;

			if (!theLogEventService.LogCurrency(GetAccountID(),GetDBCharacterID(),nValue,ePlayerMoneyType_ShengWang,ePlayerCurrency_Sub,GetCharName(),sourcetype))
			{
				Log( theXmlString.GetString( eLog_Reputation_3 ), szFunction, nLine, nValue, gCharInfoServer.baseinfo.liveinfo.reputation );
			}          
        }
        break;
    case EOT_Set:
        {
			uint32 tempreputation = gCharInfoServer.baseinfo.liveinfo.reputation;
            gCharInfoServer.baseinfo.liveinfo.reputation = nValue;
			if (tempreputation > nValue)
			{
				theLogEventService.LogCurrency(GetAccountID(),GetDBCharacterID(),tempreputation - nValue,ePlayerMoneyType_ShengWang,ePlayerCurrency_Sub,GetCharName(),sourcetype);
			}
			else if (tempreputation < nValue)
			{
				theLogEventService.LogCurrency(GetAccountID(),GetDBCharacterID(),nValue - tempreputation,ePlayerMoneyType_ShengWang,ePlayerCurrency_Add,GetCharName(),sourcetype);
			}
            Log( theXmlString.GetString( eLog_Reputation_4 ), szFunction, nLine, nValue, gCharInfoServer.baseinfo.liveinfo.reputation );
        }
        break;
    default:
        return;
        break;
    }

    _achieveManager.UpdateTriggerByValueType( EAT_Reputation , GetReputation() );
    
    // ????????????????
    MsgCharAttrChanged xChange;
    xChange.header.stID = GetID();

    xChange.AddAttrDWORDChange( CharAttr_Reputation, GetReputation() );
    switch ( uchOperateType )
    {
    case EOT_Add:
        xChange.AddAttrDWORDChange( CharAttr_CurGetReputation, nValue );
        break;
    }
    xChange.CaluLength();
    SendMessageToClient( &xChange );
}


void GamePlayer::OperateEctypeScore( uint8 uchOperateType, uint32 nValue )
{ 
    if ( nValue == 0 && uchOperateType != EOT_Set )
    { return; }

    switch ( uchOperateType )
    {
    case EOT_Add:
        gCharInfoServer.baseinfo.liveinfo.battleScore += nValue;
        break;
    case EOT_Sub:
        if ( nValue > GetEctypeScore() )
        { nValue = GetEctypeScore(); }

        gCharInfoServer.baseinfo.liveinfo.battleScore -= nValue;
        break;
    case EOT_Set:
        gCharInfoServer.baseinfo.liveinfo.battleScore = nValue;
        break;
    default:
        return;
        break;
    }

    // _achieveManager.UpdateTriggerByValueType( EAT_Exploit , gCharInfoServer.baseinfo.liveinfo.battleScore );

    // ????????????????
    //    MsgCharAttrChanged xChange;
    //    xChange.header.stID = GetID();

    //    xChange.AddAttrDWORDChange( CharAttr_Reputation, gCharInfoServer.baseinfo.liveinfo.battleScore );
    //    switch ( uchOperateType )
    //    {
    //    case EOT_Add:
    //        xChange.AddAttrDWORDChange( CharAttr_CurGetReputation, nValue );
    //        break;
    //    }
    //    xChange.CaluLength();
    //    SendMessageToClient( &xChange );
}

void GamePlayer::OperateTeamCountryScore( uint8 uchOperateType, uint32 nValue )
{
    // ??????????
    OperateCountryScore( uchOperateType, nValue, __FUNCTION__, __LINE__ );

    // ??????????, ??????????
    GameTeam* pTeam = theGameTeamManager.GetTeam( GetTeamID() );
    if ( pTeam == NULL )
    { return; }

    // ????????????????
    for ( int i = 0; i < pTeam->TeamMemberCount(); ++i )
    {
        GameTeamMember* pMember = pTeam->GetTeamMemberByIndex( i );
        if ( pMember == NULL || pMember->GetID() == GetDBCharacterID() )
        { continue; }

        GamePlayer* pPlayer = pTeam->GetMemberPlayer( pMember->GetID() );
        if ( pPlayer == NULL || !pPlayer->IsDead() )
        { continue; }

        if ( !pPlayer->IsInMapArea( GetMapID(), GetFloatX(), GetFloatY(), TEAM_EXP_DIS ) )
        { continue; }   // ??????????

        pPlayer->OperateCountryScore( uchOperateType, nValue, __FUNCTION__, __LINE__ );
    }
}

void GamePlayer::OperateCountryScore( uint8 uchOperateType, uint32 nValue, char* szFunction, int nLine )
{ 
    if ( nValue == 0 && uchOperateType != EOT_Set )
    { return; }

    Log( theXmlString.GetString( eLog_CountryScore_1 ), szFunction, nLine, gCharInfoServer.baseinfo.liveinfo.dwCountryScore );
    
    switch ( uchOperateType )
    {
    case EOT_Add:
        {
            gCharInfoServer.baseinfo.liveinfo.dwCountryScore += nValue;
            Log( theXmlString.GetString( eLog_CountryScore_2 ), szFunction, nLine, nValue, gCharInfoServer.baseinfo.liveinfo.dwCountryScore );
        }
        break;
    case EOT_Sub:
        {
            if ( nValue > GetCountryScore() )
            { nValue = GetCountryScore(); }

            gCharInfoServer.baseinfo.liveinfo.dwCountryScore -= nValue;
            Log( theXmlString.GetString( eLog_CountryScore_3 ), szFunction, nLine, nValue, gCharInfoServer.baseinfo.liveinfo.dwCountryScore );
        }
        break;
    case EOT_Set:
        {
            gCharInfoServer.baseinfo.liveinfo.dwCountryScore = nValue;
            Log( theXmlString.GetString( eLog_CountryScore_4 ), szFunction, nLine, nValue, gCharInfoServer.baseinfo.liveinfo.dwCountryScore );
        }
        break;
    default:
        return;
        break;
    }

    //_achieveManager.UpdateTriggerByValueType( EAT_CountryScore , GetCountryScore() );

    // ????????????????
    MsgCharAttrChanged xChange;
    xChange.header.stID = GetID();

    xChange.AddAttrDWORDChange( CharAttr_CountryScore, GetCountryScore() );
    switch ( uchOperateType )
    {
    case EOT_Add:
        xChange.AddAttrDWORDChange( CharAttr_CurGetCountrySocre, nValue );
        break;
    }
    xChange.CaluLength();
    SendMessageToClient( &xChange );
}

bool GamePlayer::CheckDeathRemit()
{
    // ??????????
    if ( ierr_Success != _NormalItemBag.PopItemByID( SCAPEGOAT_ID, 1 ) )
    { return false; }

    MsgRemoveItem msg;
    msg.ucItemBagType = BT_NormalItemBag;
    msg.ustItemID     = SCAPEGOAT_ID;
    msg.ustCount      = 1;
    SendMessageToClient( &msg );
   // Log( "DropItemByDead ????????[ID:%d,????:%d]",SCAPEGOAT_ID, 1 );

	Log( theXmlString.GetString(eServerLog_DropItemByDead),SCAPEGOAT_ID, 1 );

    return true;
}

void GamePlayer::PunishWhenDeath( BaseCharacter* pAttacker )
{
    if ( pAttacker == NULL || !IsDead() )
    { return; }

    if ( CheckDeathRemit() )
    { return; }     // ??????????????

    // ????????????
    DropItemWhenDeath( pAttacker );

    // ????????????????
    CalcEquipHpWhenDeath();

	// ????????????????
	DropExpHonourWhenDeath( pAttacker );
}      

// ????????????????
void GamePlayer::CalcEquipHpWhenDeath()
{
    float fEquipDropHp = 0.0f ;
    int nDropPer       = GetRand( g_Cfg.nDeathEquipDropHpMin, g_Cfg.nDeathEquipDropHpMax );  

    if ( _buffManager.GetDeathDurabilityPer() > 0 )
    { nDropPer *= _buffManager.GetDeathDurabilityPer(); }

    if ( nDropPer <= 0 )
    { return; }

    bool bIsNeedRefresh = false;

    MsgChangEquipHp msg;
    msg.header.stID = GetID();
    for ( int i = 0; i < EEquipPartType_MaxEquitPart; ++i )
    {
        SCharItem* pTargetEquip = GetVisualEquipItem( i );
        if ( pTargetEquip == NULL || pTargetEquip->equipdata.usHP <= 0.f )
        { continue; }

        ItemDefine::SItemCanEquip* pItemCanEquip = (ItemDefine::SItemCanEquip*)GettheItemDetail().GetItemByID( pTargetEquip->itembaseinfo.ustItemID );
        if ( pItemCanEquip == NULL || !pItemCanEquip->HasEquipHp() )
        { continue; }

        fEquipDropHp = pTargetEquip->equipdata.usHP * nDropPer * DEF_PERCENT;
        // ??????????????????
        if ( fEquipDropHp < 1.0f )
        { fEquipDropHp = 1.0f; }

        pTargetEquip->equipdata.usHP -= fEquipDropHp;    
        if ( pTargetEquip->equipdata.usHP <= 0.0f )
        {
            pTargetEquip->equipdata.usHP = 0.0f;
            bIsNeedRefresh = true;
        }

        msg.stIndex = i;
        msg.nEquipHp = pTargetEquip->equipdata.usHP;
        msg.nEquipMaxHp = pTargetEquip->equipdata.usHpMax;
        msg.nGuid = pTargetEquip->itembaseinfo.nOnlyInt;
        SendMessageToClient( &msg );
    }

    if ( bIsNeedRefresh )
    {
        UpdateAllEquipData();
        UpdateAllSuitData() ;
    }
}

void GamePlayer::SubEquipHp( short index, float fDropHp, bool& bNeedUpdateEquipData )
{
    if ( !IsPlayer() || index < 0 || index >= EEquipPartType_MaxEquitPart || fDropHp <= 0.0f )
    { return; }

    GamePlayer* pSelf = (GamePlayer*) this;
    SCharItem* pEquip = pSelf->GetVisualEquipItem( index );
    if ( pEquip == NULL )
    { return; }

    ItemDefine::SItemCanEquip* pItem = (ItemDefine::SItemCanEquip*)GettheItemDetail().GetItemByID( pEquip->itembaseinfo.ustItemID );
    if ( pItem == NULL || !pItem->HasEquipHp() || pItem->bFashion)
    { return; }

    // ????
    if ( pEquip->equipdata.usHpMax != pItem->stHPMax )
        pEquip->equipdata.usHpMax = pItem->stHPMax;

    if ( pEquip->equipdata.usHP > pEquip->equipdata.usHpMax )
        pEquip->equipdata.usHP = pEquip->equipdata.usHpMax;

    if ( pEquip->equipdata.usHP > 0.0f )
    {
        float fLastHp = pEquip->equipdata.usHP;     // ??????????????????HP

        pEquip->equipdata.usHP -= fDropHp;
        if ( pEquip->equipdata.usHP <= 0.0f )
        {
            pEquip->equipdata.usHP = 0.0f;
            bNeedUpdateEquipData   = true;
        }
        int nOldHp = (int)ceil( fLastHp );
        int nNewHp = (int)ceil( pEquip->equipdata.usHP );
        if ( nNewHp < nOldHp )
        {
            MsgChangEquipHp xChange;
            xChange.header.stID = GetID();
            xChange.stIndex  = index;
            xChange.nEquipMaxHp = pEquip->equipdata.usHpMax;
            xChange.nEquipHp = pEquip->equipdata.usHP;
            xChange.nGuid    = pEquip->itembaseinfo.nOnlyInt;
            GettheServer().SendMsgToSingle( &xChange, this );
        }
    }
}

void GamePlayer::DropExpHonourWhenDeath( BaseCharacter* pAttacker )
{
	if ( pAttacker == NULL || this == pAttacker || !pAttacker->IsPlayer() )
	{ return; }

	GamePlayer* pAttackerPlayer = static_cast< GamePlayer* >( pAttacker );

	// ????????????
	if ( pAttackerPlayer->GetCountryId() == GetCountryId() )
		return;

	if ( pAttackerPlayer->GetCountryId() == CountryDefine::Country_Init || GetCountryId() == CountryDefine::Country_Init )
		return;

	// ??????
	uint32 curlvexp = theExpStage.GetPLevelupExp( GetLevel() );
	uint32 dropexp = curlvexp * g_Cfg.nDropExp * DEF_PERCENT;
	int64 setCurexp = GetPlayerExpUnUsed() - dropexp;
	if ( setCurexp < 0 )
		setCurexp = 0;

	int64 lastExp = GetPlayerExpUnUsed();

	SetPlayerExpUnUsed( setCurexp );

	MsgCharAttrChanged Change;
	Change.header.stID = GetID();
	Change.iChangeCount = 0;
	Change.AddAttrInt64Change( CharAttr_ExpNotUsed,GetPlayerExpUnUsed() );
	Change.AddAttrDWORDChange( CharAttr_LostExp, lastExp - GetPlayerExpUnUsed() );
	
	Change.CaluLength();
	SendMessageToClient( &Change );

	//??????
	if(!IsInBattleMap())
		OperateHonour( EOT_Sub, g_Cfg.nDropHonour, __FUNCTION__, __LINE__ , ePlayerMoneySourceType_KillPerson );
}

void GamePlayer::DropItemWhenDeath( BaseCharacter* pAttacker )
{
    if ( pAttacker == NULL || this == pAttacker || !pAttacker->IsPlayer() )
    { return; }

    // ????????, ????????
    DropItemWhenDeadByGuildQuest();      

    GamePlayer* pAttackerPlayer = static_cast< GamePlayer* >( pAttacker );
    //if ( IsInFreePKZone() || pAttackerPlayer->IsInFreePKZone() )
    //{ return;  }

    // ??????????????????????????????????
    if ( GetPKMode() != PKMode_Critical )
    { return; }

    // 30% ??????????
    if ( ( theRand.rand32() % RAND_NUM ) > PKDropItemRate )
    { return; }

    // ?? 1 ??????
    int nDropCount = 1; 

    // ????????,??????????????
    std::vector<SCharItem*> vecDropItemTemp;
    vecDropItemTemp.clear();
    // ????????
    for ( int i = 0; i < _NormalItemBag.GetNowBagSize(); ++i )
    {
        SCharItem* pItem = _NormalItemBag.GetItemByIndex( i );
        if ( pItem == NULL )
        { continue; }

        if ( pItem->IsLock() || pItem->IsBounded() || pItem->IsOverdue() )
        { continue; }           // ??????????????????

        ItemDefine::SItemCommon* pCommon = GettheItemDetail().GetItemByID( pItem->itembaseinfo.ustItemID );
        if ( pCommon == NULL || !pCommon->bIsCanTrade )
        { continue; }           // ????????????????

        vecDropItemTemp.push_back( pItem );
    }

    // ????????
    for ( int i = 0; i < _MaterialItemBag.GetNowBagSize(); ++i )
    {
        SCharItem* pItem = _MaterialItemBag.GetItemByIndex( i );
        if ( pItem == NULL )
        { continue; }

        if ( pItem->IsLock() || pItem->IsBounded() || pItem->IsOverdue() )
        { continue; }           // ??????????????????

        ItemDefine::SItemCommon* pCommon = GettheItemDetail().GetItemByID( pItem->itembaseinfo.ustItemID );
        if ( pCommon == NULL || !pCommon->bIsCanTrade )
        { continue; }           // ????????????????

        vecDropItemTemp.push_back( pItem );
    }

    int nDropItemSize = vecDropItemTemp.size();
    if ( nDropItemSize == 0 )
    { return; }         // ??????????????

    std::map<SCharItem*, int> mapPopItem;       // ????????????????
    mapPopItem.clear();

    std::vector<SCharItem*> vecDropItem;        // ??????????????
    vecDropItem.clear();

    if ( nDropItemSize < nDropCount )           // ??????????????????????
    {
        vecDropItem = vecDropItemTemp;
    }
    else
    {
        for ( int i = 0; i < nDropCount; ++i )
        {
            int iIndex = theRand.rand32() % nDropItemSize;        // ??????

            std::vector<SCharItem*>::iterator iter = find( vecDropItem.begin(), vecDropItem.end(), vecDropItemTemp[iIndex] );
            if ( iter == vecDropItem.end() )
            {
                vecDropItem.push_back( vecDropItemTemp[iIndex] );
            }
        }
    }

    DropCharItemVector vecDropItemPackage;
    for ( std::vector<SCharItem*>::iterator iter = vecDropItem.begin(); iter != vecDropItem.end(); ++iter )
    {
        if ( *iter == NULL )
        { continue; }

        ItemDefine::SItemCommon* pCommon = GettheItemDetail().GetItemByID( (*iter)->itembaseinfo.ustItemID );
        if ( pCommon == NULL )
        { continue; }

        int nItemCount = 1;
        if ( pCommon->IsExclusive() )       // ????????
        {
            vecDropItemPackage.push_back( *(*iter) );
        }
        else
        {
            if ( (*iter)->itembaseinfo.ustItemCount > 1 )
            {
                nItemCount = ( theRand.rand32() % (*iter)->itembaseinfo.ustItemCount ) + 1;
            }
            SCharItem item;
            if( !theRunTimeData.CreateItem( NULL, (*iter)->itembaseinfo.ustItemID, nItemCount, HelperFunc::CreateID(), item ) )
            { continue; }

            vecDropItemPackage.push_back( item );
        }

        mapPopItem.insert( make_pair( (*iter), nItemCount ) );
    }

    // ??????????????????
    for ( std::map<SCharItem*, int>::iterator iter = mapPopItem.begin(); iter != mapPopItem.end(); ++iter )
    {
        if( iter->first == NULL )
        { continue; }
        ItemDefine::SItemCommon* pCommon = GettheItemDetail().GetItemByID( iter->first->itembaseinfo.ustItemID );
        if ( pCommon == NULL )
        { continue; }

        unsigned char ucItemBagType = GetItemBagType( pCommon->ucItemType );

        ItemBag* pItemBag = GetItemBagByItemType( pCommon->ucItemType );
        __int64 nGuid = iter->first->GetItemGuid();
        int nIndex = pItemBag->GetItemIndexByGuid( nGuid );
        if ( nIndex != -1 )
        {
            RemoveItem( ucItemBagType, nIndex, iter->second, nGuid );
			SCharItem *_item = GetBagItemByGuid(nGuid);

            //Log( "DropItemWhenDead ????????????[ID:%I64u] ????[%d]??", nGuid, iter->second );
				//LYH????????
				if(!theLogEventService.LogItemConsume(GetAccountID(),GetDBCharacterID(),iter->first->GetItemID(),
				iter->first->GetItemCount(),nGuid,
				_item?_item->GetItemCount():0,eItemLogInfo_ItemConsume_DeadDrop,GetCharName(),pCommon->GetItemName()))
			{
                   Log( theXmlString.GetString(eServerLog_DropItemByDead1), nGuid, iter->second );
			}
			
        }
    }

    DropItemVector mapDropPackage;           // ??????
    mapDropPackage.clear();
    DropBaseItem::DropItemPackage( mapDropPackage, vecDropItemPackage, pAttackerPlayer->GetTeamID(), pAttackerPlayer->GetDBCharacterID(), GetMapID(), GetFloatX(), GetFloatY(), LogDefine::ECD_DropType_Player );

    return;
}

 int64 GamePlayer::GetItemGUIDByItemID(unsigned short ustItemId)
 {
	 int64 _TGUID = 0;

	 SCharItem * _CharItem = _NormalItemBag.GetItemByItemID(ustItemId) ;
	 if(!_CharItem)
	 {
		 _CharItem = _MaterialItemBag.GetItemByItemID(ustItemId) ;

		  if(!_CharItem)
			  _CharItem = _TaskItemBag.GetItemByItemID(ustItemId) ;
	 }

	 if (_CharItem)
	 {
		_TGUID = _CharItem->GetItemGuid();
	 }

	 return _TGUID;

 }
SCharItem* GamePlayer::GetBagItemByGuid( int64 guid )
{
    ItemBag* s_ItemBag[] = { &_NormalItemBag, &_MaterialItemBag, &_TaskItemBag, };

    for ( int m = 0; m < sizeof( s_ItemBag ) / sizeof( ItemBag* ); ++m )
    {
        ItemBag* pItemBag = s_ItemBag[m];
        if ( pItemBag == NULL )
        { continue; }
        
        SCharItem* pCharItem = pItemBag->GetItemByOnlyBigId( guid );
        if ( pCharItem != NULL )
        { return pCharItem; }
    }

    return NULL;
}

bool GamePlayer::RemoveBagItemByGuid( int64 guid, int count)
{
    ItemBag* s_ItemBag[] = { &_NormalItemBag, &_MaterialItemBag, &_TaskItemBag, };

    for ( int m = 0; m < sizeof( s_ItemBag ) / sizeof( ItemBag* ); ++m )
    {
        ItemBag* pItemBag = s_ItemBag[m];
        if ( pItemBag == NULL )
        { continue; }

        SCharItem* pCharItem = pItemBag->GetItemByOnlyBigId( guid );
        if ( pCharItem == NULL )
        { continue; }

        return pItemBag->RemoveItemByGuID( guid, count );
    }

    return false;
}

// ????????????????????????
void GamePlayer::DropItemWhenDeadByGuildQuest()
{
    ItemBag* s_ItemBag[] = { &_NormalItemBag, &_MaterialItemBag, &_TaskItemBag, };
    unsigned char s_ItemBatType[] = { BT_NormalItemBag, BT_MaterialBag, BT_TaskBag, };

    for ( int m = 0; m < sizeof( s_ItemBag ) / sizeof( ItemBag* ); ++m )
    {
        ItemBag* pItemBag = s_ItemBag[m];
        if ( pItemBag == NULL )
        { continue; }

        for ( int i = 0; i < pItemBag->GetNowBagSize(); ++i )
        {
            SCharItem* pItem = pItemBag->GetItemByIndex( i );
            if ( pItem == NULL )
            { continue; }

            ItemDefine::SItemCommon* pCommon = GettheItemDetail().GetItemByID( pItem->itembaseinfo.ustItemID );
            if ( pCommon == NULL || pCommon->ucItemType != ItemDefine::ITEMTYPE_GUILD )
            { continue; }           

            ItemDefine::SItemGuild* pItemGuild = static_cast< ItemDefine::SItemGuild* >( pCommon );
            if ( pItemGuild == NULL || pItemGuild->uchType != ItemDefine::SItemGuild::ECD_GuildBox )
            { continue; } // ??????????????????,??????

            DropItemVector mapDropPackage;           // ??????
            mapDropPackage.clear();

            int nItemCount = 1;
            if ( pCommon->IsExclusive() )       // ????????
            {
                DropCharItemVector vecDropItemPackage ( 0 ); // ????????????
                vecDropItemPackage.push_back( *pItem );
                DropBaseItem::DropItemPackage( mapDropPackage, vecDropItemPackage, TeamDefine::NoneSessionID, InvalidLogicNumber, GetMapID(), GetFloatX(), GetFloatY(), LogDefine::ECD_DropType_Player );
            }
            else
            {
                for ( int j = 0; j < pItem->itembaseinfo.ustItemCount; ++j )    // ????????????????
                {
                    SCharItem item;
                    if( !theRunTimeData.CreateItem( NULL, pItem->itembaseinfo.ustItemID, 1, HelperFunc::CreateID(), item ) )
                    { continue; }

                    DropCharItemVector vecDropItemPackage ( 0 ); // ????????????
                    vecDropItemPackage.push_back( item );
                    DropBaseItem::DropItemPackage( mapDropPackage, vecDropItemPackage, TeamDefine::NoneSessionID, InvalidLogicNumber, GetMapID(), GetFloatX(), GetFloatY(), LogDefine::ECD_DropType_Player );
                }
            }

            // ????????
            RemoveItem( s_ItemBatType[m], i, pItem->GetItemCount(), pItem->GetItemCount() );

			//LYH????????
			theLogEventService.LogItemConsume(GetAccountID(),GetDBCharacterID(),pItem->GetItemID(),
				pItem->GetItemCount(),pItem->GetItemGuid(),
				0,eItemLogInfo_ItemConsume_DeadDrop,GetCharName(),pCommon->GetItemName());
        }
    }
}



bool GamePlayer::AddTitle(short nTitleID)
{
    MsgAddTitleAck xAck;
    xAck.header.stID = GetID();
    xAck.nTitleID = nTitleID;

    if (nTitleID <= TitleConfig::Init_ID)
    {
        xAck.nError = MsgAddTitleAck::Add_ErrorID;
        GettheServer().SendMsgToSingle(&xAck, this);
        return false;
    }

    //????????
    if (m_xTitleEx.IsHaveTitle(nTitleID))
    {
        xAck.nError = MsgAddTitleAck::Add_AlreadyExist;
        GettheServer().SendMsgToSingle(&xAck, this);
        return false;
    }

    //????????????
    TitleConfig::Title* pTitleConfig = theTitleConfig.GetTitleByTitleID(nTitleID);
    if (pTitleConfig == NULL)
    {
        xAck.nError = MsgAddTitleAck::Add_NoThisTitle;
        GettheServer().SendMsgToSingle(&xAck, this);

        //Log("??????????????ID[%u]??????????????????????????", nTitleID);
		Log(theXmlString.GetString(eServerLog_NoFindChenghaoAdd), nTitleID);
        return false;
    }

    if ( m_xTitleEx.IsAlreadyDisplaceTitle(nTitleID) )
    {
        xAck.nError = MsgAddTitleAck::Add_HasAdvancedTitle;
        GettheServer().SendMsgToSingle(&xAck, this);
        return false;
    }

    TimeEx xCurrentTime = TimeEx::GetCurrentTime();
    xAck.n64AcquireTime = xCurrentTime.GetTime();
    xAck.nActiveTime    = pTitleConfig->GetTimeLimit() * OneHourSecond; // ????????

    short nDisplaceTitleID = m_xTitleEx.GetDisplaceID( nTitleID );   // ??????????????????
    if ( nDisplaceTitleID != TitleConfig::Init_ID )
    {
        if ( m_xTitleEx.AddTitle( nTitleID, xCurrentTime.GetTime(), xAck.nActiveTime  ) )
        {
            m_xTitleEx.RemoveTitle( nDisplaceTitleID );            // ??????????????????????????????  

            UpdateBaseAttrByTitle( true, nTitleID, nDisplaceTitleID );    
            GettheServer().SendMsgToSingle(&xAck, this);

            //??????????,??????????
            MsgRemoveTitleAck xRemove;
            xRemove.nTitleID = nDisplaceTitleID;
            GettheServer().SendMsgToSingle(&xRemove, this);

            //????????????????????????,??????????
            if( m_xTitleEx.GetCurrentTitle() == nDisplaceTitleID )
            {
                if (m_xTitleEx.SetCurrentTitle(nTitleID))
                {
                    MsgTellCurrentTitle xTell;
                    xTell.nTitleID = nTitleID;
                    GetRelationNameByTitle( xTell.nTitleID, xTell.szTitleTargetName, sizeof( xTell.szTitleTargetName ) );
                    GettheServer().SendMsgToView(&xTell, GetID(), false);

                    if ( m_pRelation->GetTitleID() != GetCurrentTitle() )
                    { m_pRelation->SendUpdateAttributeReqMessage( RelationDefine::UpdateTitle, GetCurrentTitle() ); }
                }
            }
        }
        else
        {
            xAck.nError = MsgAddTitleAck::Add_Unknow;
            GettheServer().SendMsgToSingle(&xAck, this);
        }
    }
    else            //??????????????????
    {
        if ( m_xTitleEx.AddTitle( nTitleID, xCurrentTime.GetTime(), xAck.nActiveTime ) )
        {
            UpdateBaseAttrByTitle(true, nTitleID);
            GettheServer().SendMsgToSingle(&xAck, this);
        }
        else
        {
            xAck.nError = MsgAddTitleAck::Add_TitleFull;
            GettheServer().SendMsgToSingle(&xAck, this);
        }
    }

    _achieveManager.UpdateTriggerByValueType( EAT_AddTitle , nTitleID );
    return (xAck.nError == MsgAddTitleAck::Add_Success);
}


bool GamePlayer::RemoveTitle(short nTitleID, bool bSendMessage /* = true */ )
{
    MsgRemoveTitleAck xAck;
    xAck.header.stID = GetID();
    xAck.nTitleID = nTitleID;

    if (nTitleID <= TitleConfig::Init_ID)
    {
        xAck.nError = MsgRemoveTitleAck::Remove_ErrorID;
        GettheServer().SendMsgToSingle(&xAck, this);
        return false;
    }

    if (!m_xTitleEx.RemoveTitle(nTitleID))
    {
        xAck.nError = MsgRemoveTitleAck::Remove_NoThisTitle;
        GettheServer().SendMsgToSingle(&xAck, this);
        return false;
    }
    else
    {
        GettheServer().SendMsgToSingle(&xAck, this);

        if (m_xTitleEx.GetCurrentTitle() == nTitleID)
        {
            m_xTitleEx.SetCurrentTitle(TitleConfig::Init_ID);

            MsgTellCurrentTitle xTell;
            xTell.header.stID = GetID();
            xTell.nTitleID = TitleConfig::Init_ID;
            GettheServer().SendMsgToView(&xTell, GetID(), false);

            if ( m_pRelation->GetTitleID() != GetCurrentTitle() )
            { m_pRelation->SendUpdateAttributeReqMessage( RelationDefine::UpdateTitle, GetCurrentTitle() ); }
        }

        UpdateBaseAttrByTitle( bSendMessage, TitleConfig::Init_ID, nTitleID );
    }

    return true;
}

bool GamePlayer::IsLastLoginPassOneDay() 
{
    TimeEx xLastTime( GetTimeVar( ECT_LastLoginTime ) );
    TimeSpan xTimeSpan = TimeEx::GetCurrentTime() - xLastTime;
    return xTimeSpan.GetDays() >= 1;
}

bool GamePlayer::IsPassSunday( int64 nRecordTime )
{
    int nNowWeek  = GetWeekOfYear();
    int nRecordWeek = GetWeekOfYear( (time_t) nRecordTime );

    if (nNowWeek == -1 || nRecordWeek == -1)
    { return false; }

    return (nNowWeek != nRecordWeek);
}

int64 GamePlayer::GetTimeVar( uint8 nVarId)
{
    if( nVarId > ECT_MaxTimeVar )
    { return -1; }

    return gCharInfoServer.extendData.n64TimeVars[nVarId];
}

void GamePlayer::SetTimeVar( uint8 nVarId, int64 n64Time )
{
    if( nVarId > ECT_MaxTimeVar )
    { return; }

    gCharInfoServer.extendData.n64TimeVars[nVarId] = n64Time;
}

uint32 GamePlayer::Get32TimeVar( uint8 nVarId)
{
    if( nVarId > ECT_MaxTimeVar )
    { return -1; }

    return gCharInfoServer.extendData.n32TimeVars[nVarId];
}

void GamePlayer::Set32TimeVar( uint8 nVarId, uint32 n32Time )
{
    if( nVarId > ECT_MaxTimeVar )
    { return; }

    gCharInfoServer.extendData.n32TimeVars[nVarId] = n32Time;
}

int GamePlayer::GetItemCount( unsigned short ustItemId )
{
    ItemDefine::SItemCommon* pCommon = GettheItemDetail().GetItemByID( ustItemId );
    if ( pCommon == NULL )
    { return 0; }

    ItemBag* pItemBag = GetItemBagByItemType( pCommon->ucItemType );
    return pItemBag->GetItemCount( ustItemId );
}

int GamePlayer::GetNullItemCount( unsigned char ucItemBagType )
{
    switch ( ucItemBagType )
    {
    case BT_NormalItemBag:
        return _NormalItemBag.GetNullItemCount();
        break;
    case BT_MaterialBag:
        return _MaterialItemBag.GetNullItemCount();
        break;
    case BT_TaskBag:
        return _TaskItemBag.GetNullItemCount();
        break;
    case BT_MountBag:
        return _mountManager.GetMountEmptyCount();
        break;
    case BT_PetBag:
        return _petManager.GetPetEmptyCount();
        break;
    default:
        break;
    }
    return 0;
}

short GamePlayer::AddItem(int nItemId, short nCount, uint8 nItemSource, bool bIsBound, int64* pGuid /* = NULL */ ,bool isChangeUnBindSum ,unsigned short UnBindeSum, int sysType, int typeID )
{
    if ( nItemId < 0 || nCount < 0 ) 
    { return ierr_unknown; }

    __int64 nItemBigId = _NormalItemBag.GetNewItemID();
    if ( nItemBigId == InvalidLogicNumber ) 
    { return ierr_unknown; }

    if ( pGuid != NULL )
    { *pGuid = nItemBigId; }

    SCharItem xItem;
    if( !theRunTimeData.CreateItem( this, nItemId, nCount, nItemBigId, xItem ,isChangeUnBindSum,UnBindeSum) )
    { return ierr_unknown; }

    xItem.SetBounded(bIsBound);

    unsigned short ustCount = nCount;
    return AddItemToBag( xItem, ustCount, nItemSource, sysType, typeID );
}

short GamePlayer::AddEquipItem(int nItemId, short nCount, uint8 nItemSource, bool bIsBound, int64* pGuid /* = NULL */, bool bStarRandom /*= false*/, int16 nStarLevel /*= 0*/ ,bool isChangeUnBindSum ,unsigned short UnBindeSum, int sysType, int typeID )
{
    if ( nItemId < 0 || nCount < 0 ) 
    { return ierr_unknown; }

    __int64 nItemBigId = _NormalItemBag.GetNewItemID();
    if ( nItemBigId == InvalidLogicNumber ) 
    { return ierr_unknown; }

    if ( pGuid != NULL )
    { *pGuid = nItemBigId; }

    SCharItem xItem;
    if( !theRunTimeData.CreateItem( this, nItemId, nCount, nItemBigId, xItem ,isChangeUnBindSum,UnBindeSum) )
    { return ierr_unknown; }

    xItem.SetBounded(bIsBound);

    //????????
    xItem.SetStarLevel( bStarRandom, nStarLevel );

	theRunTimeData.EquipScore(xItem, GettheItemDetail().GetItemByID( xItem.itembaseinfo.ustItemID )); // ????????????

    unsigned short ustCount = nCount;
    return AddItemToBag( xItem, ustCount, nItemSource, sysType, typeID );
}

short GamePlayer::AddEquipRandAttrItem(int nItemId, short nCount, uint8 nItemSource , bool bIsBound, int64* pGuid, int nRandId1, int nRandId2, int nRandId3, int nRandId4, int nRandId5, int nRandId6, int nRandId7, int sysType, int typeID )
{
	if ( nItemId < 0 || nCount < 0 ) 
	{ return ierr_unknown; }

	__int64 nItemBigId = _NormalItemBag.GetNewItemID();
	if ( nItemBigId == InvalidLogicNumber ) 
	{ return ierr_unknown; }

	if ( pGuid != NULL )
	{ *pGuid = nItemBigId; }

	SCharItem xItem;
	if ( !theRunTimeData.CreateItem( this, nItemId, nCount, nItemBigId, xItem))
	{ return ierr_unknown; }

	xItem.SetBounded(bIsBound);

	theRunTimeData.EquipRandAttrByIds(xItem, nRandId1, nRandId2, nRandId3, nRandId4, nRandId5, nRandId6, nRandId7);
	theRunTimeData.EquipScore(xItem, GettheItemDetail().GetItemByID( xItem.itembaseinfo.ustItemID )); // ????????????

	unsigned short ustCount = nCount;
	return AddItemToBag( xItem, ustCount, nItemSource, sysType, typeID );
}
short GamePlayer::AddItemToBagByIndex(SCharItem &item,int Index, unsigned short &nCount, uint8 nItemSource )
{
	if ( nCount < 0 ) 
    { return ierr_unknown; }

    ItemDefine::SItemCommon* pItem = GettheItemDetail().GetItemByID(item.itembaseinfo.ustItemID);
    if( pItem == NULL )
    { return ierr_ItemNotExist; }

	SCharItem * pBagItem = GetNormalBagPointerByIndex(Index);
	if(!pBagItem || pBagItem->itembaseinfo.ustItemID != 0 || pBagItem->itembaseinfo.nOnlyInt != 0)
		return ierr_CanNotOverlap;

    MsgGetItem2 getitem;
    getitem.item  = item;
    getitem.itemSource = nItemSource;

    //????????????????
    unsigned short ustCount = nCount;
    ItemBag* pItemBag = GetItemBagByItemType( pItem->ucItemType );
    int nResult = pItemBag->PushItem( getitem.item, ustCount,Index);
    switch( nResult )
    {
    case ierr_Success:
        { // ????????????????
            Log(theXmlString.GetString(eLog_PickItemPack), pItem->GetItemName(),pItem->ustItemID,getitem.item.itembaseinfo.nOnlyInt, ustCount, nItemSource );
            getitem.enResult = MsgGetItem2::RESULT_SUCCESS;
        }
        break;
    case ierr_notallitempushed:
        {
            getitem.enResult = MsgGetItem2::RESULT_NOSPACE;
            int nLess = getitem.item.itembaseinfo.ustItemCount;
            getitem.item.itembaseinfo.ustItemCount = ustCount - nLess;
            nCount = nLess;

            ShowInfo( false, 273, theXmlString.GetString(eText_ItemNoPlace) );
            Log( theXmlString.GetString(eLog_info_2slk_143), ustCount, pItem->GetItemName() );
        }
        break;
    case ierr_PackIsFull:
        {
            getitem.enResult = MsgGetItem2::RESULT_NOSPACE;
            ShowInfo( false, 273, theXmlString.GetString(eText_ItemNoPlace) );
            Log(theXmlString.GetString(eLog_info_2slk_143), ustCount, pItem->GetItemName() );
        }
        return ierr_PackIsFull;
    default:
        Log( theXmlString.GetString(eLog_info_2slk_144), ustCount, pItem->GetItemName() );
        getitem.enResult = MsgGetItem2::RESULT_UNKNOW;
        return ierr_unknown;
    }
	//getitem.item.itembaseinfo.stPacketIdx = ReturnItemID( BT_NormalItemBag, pItem->ustItemID );			//luo.qin 3.22
    getitem.header.stID = GetID(); 
    GettheServer().SendMsgToSingle( &getitem, this );

    return nResult;
}
short GamePlayer::AddItemToBag( SCharItem &item, unsigned short &nCount, uint8 nItemSource, int sysType, int typeID )
{
    if ( nCount < 0 ) 
    { return ierr_unknown; }

    ItemDefine::SItemCommon* pItem = GettheItemDetail().GetItemByID(item.itembaseinfo.ustItemID);
    if( pItem == NULL )
    { return ierr_ItemNotExist; }

    MsgGetItem2 getitem;
    getitem.item  = item;
    getitem.itemSource = nItemSource;

    //????????????????
    unsigned short ustCount = nCount;
    ItemBag* pItemBag = GetItemBagByItemType( pItem->ucItemType );
    int nResult = pItemBag->PushItem( getitem.item, ustCount );
    switch( nResult )
    {
    case ierr_Success:
        { // ????????????????
			//LYH???????? ????????????
			if(!theLogEventService.LogItemGain(GetAccountID(),GetDBCharacterID(),pItem->ustItemID,ustCount,getitem.item.itembaseinfo.nOnlyInt,nItemSource,GetCharName(),pItem->GetItemName()))
			{
            Log(theXmlString.GetString(eLog_PickItemPack), pItem->GetItemName(),pItem->ustItemID,getitem.item.itembaseinfo.nOnlyInt, ustCount, nItemSource );
			}
            getitem.enResult = MsgGetItem2::RESULT_SUCCESS;
        }
        break;
    case ierr_notallitempushed:
        {
            getitem.enResult = MsgGetItem2::RESULT_NOSPACE;
            int nLess = getitem.item.itembaseinfo.ustItemCount;
            getitem.item.itembaseinfo.ustItemCount = ustCount - nLess;
            nCount = nLess;

            ShowInfo( false, 273, theXmlString.GetString(eText_ItemNoPlace) );
            Log( theXmlString.GetString(eLog_info_2slk_143), ustCount, pItem->GetItemName() );
        }
        break;
    case ierr_PackIsFull:
        {
            getitem.enResult = MsgGetItem2::RESULT_NOSPACE;
            ShowInfo( false, 273, theXmlString.GetString(eText_ItemNoPlace) );
            Log(theXmlString.GetString(eLog_info_2slk_143), ustCount, pItem->GetItemName() );
        }
        return ierr_PackIsFull;
    default:
        Log( theXmlString.GetString(eLog_info_2slk_144), ustCount, pItem->GetItemName() );
        getitem.enResult = MsgGetItem2::RESULT_UNKNOW;
        return ierr_unknown;
    }
	//getitem.item.itembaseinfo.stPacketIdx = ReturnItemID( BT_NormalItemBag, pItem->ustItemID );			//luo.qin 3.22
    getitem.header.stID = GetID(); 
    GettheServer().SendMsgToSingle( &getitem, this );

	if ( nResult == ierr_Success )
	{
		AddItemSystemChat( sysType, typeID, item );
	}

    return nResult;
}

const char* GamePlayer::GetDefaultCountryNameById( int Id )
{
	switch( Id )
	{
	case CountryDefine::Country_Init:
		return theXmlString.GetString( eText_CountryName );
		break;
	case CountryDefine::Country_LouLan:
		return theXmlString.GetString( eText_Country_LouLan );
		break;
	case CountryDefine::Country_KunLun:
		return theXmlString.GetString( eText_Country_KunLun );
		break;
	case CountryDefine::Country_DunHuang:
		return theXmlString.GetString( eText_Country_DunHuang );
		break;
	default:
		break;
	}
	return "";
}

void GamePlayer::AddItemSystemChat(int sysType, int typeID, SCharItem &item)
{
	if ( sysType <= 0 )
		return;
	ItemDefine::SItemCommon* pItem = GettheItemDetail().GetItemByID(item.itembaseinfo.ustItemID);
	if( !pItem )
		return;

	if (pItem->ustLevel < eIL_Nonsuch)
		return;

	MsgChat chat(MsgChat::CHAT_TYPE_PROGRAM_SYSTEM);
	chat.type = GetItemBagType( pItem->ucItemType );
	chat.nHyberItemCnt = 1;
	chat.onlyId[0] = item.itembaseinfo.nOnlyInt;
	chat.itemId[0] = item.itembaseinfo.ustItemID;

	Common::_tstring strName = pItem->GetItemName();
	ReplaceSpecifiedName( pItem->ustLevel, strName );

	char bufStr[BUFSIZ] = {0};

	if ( sysType == 1 )
	{
		ItemDefine::SItemCommon* pItemType = GettheItemDetail().GetItemByID(typeID);
		if( !pItemType )
			return;

		sprintf_s( bufStr,sizeof(bufStr) - 1,theXmlString.GetString(eText_AddItem_Type1), GetDefaultCountryNameById( GetCountryId() ), GetCharName(), pItemType->GetItemName(), strName.c_str() );
	}

	if ( sysType == 2 )
	{
		 NpcInfo::Npc* NpcName = theNpcInfo.GetNpcByStaticId(typeID);
		 if ( !NpcName )
			 return;

		 sprintf_s( bufStr,sizeof(bufStr) - 1,theXmlString.GetString(eText_AddItem_Type2), GetDefaultCountryNameById( GetCountryId() ), GetCharName(), NpcName->name.c_str(), strName.c_str() );
	}

	if ( sysType == 3 )
	{
		ItemDefine::SMonster* pMonsterConfig = GettheItemDetail().GetMonsterById( typeID );
		if ( !pMonsterConfig )
			return;

		sprintf_s( bufStr,sizeof(bufStr) - 1,theXmlString.GetString(eText_AddItem_Type3), GetDefaultCountryNameById( GetCountryId() ), GetCharName(), pMonsterConfig->GetName(), strName.c_str() );
	}

	ProcessSystem( bufStr, SystemWorld, &chat );
}

bool GamePlayer::RemoveItem( unsigned short ustItemId, unsigned short ustCount )
{
    ItemDefine::SItemCommon* pCommon = GettheItemDetail().GetItemByID( ustItemId );
    if ( pCommon == NULL )
    { return false; }

    unsigned char ucItemBagType = GetItemBagType( pCommon->ucItemType );

    ItemBag* pItemBag = GetItemBagByItemType( pCommon->ucItemType );

    // ??????????????
    int nCount = pItemBag->GetItemCount( ustItemId );
	if (nCount == 0||ustCount == 0)
	{//????0,????????????.??????0??,????????
		return false;
	}
	else
	{
		if (ustCount == 0xffff)
		{//????-1,??????????
			ustCount = nCount;
		}
		else if ( nCount < ustCount )
		{ /*ustCount = nCount;*/ return false;} //lrt ????????return false;??????????????????
	}
    int nResult = pItemBag->PopItemByID( ustItemId, ustCount );
    switch ( nResult )
    {
    case ierr_Success:
    case ierr_NotHaveTargetCountItem:
        {
            MsgRemoveItem msg;
            msg.ucItemBagType = ucItemBagType;
            msg.ustItemID     = ustItemId;
            msg.ustCount      = ustCount;
            SendMessageToClient( &msg );
            return true;
        }
        break;
    default:
        break;
    }

    return false;
}

bool GamePlayer::RemoveItem( uint8 uchBagType, uint8 uchIndex, int nCount, __int64 n64Guid )
{
    ItemBag* pItemBag = NULL;
    switch ( uchBagType )
    {
    case BT_MaterialBag:
        pItemBag = &_MaterialItemBag;
        break;
    case BT_TaskBag:
        pItemBag = &_TaskItemBag;
        break;
    default:
        pItemBag = &_NormalItemBag;
    }

    if ( !pItemBag->ClearItem( uchIndex, nCount ) )
    { return false; }

    MsgMoveGoodsReq xDel;
    xDel.ulResult      = ER_Success;
    xDel.ustDstIndex   = ITEM_DISTORY;
    xDel.ucItemBagType = uchBagType;
    xDel.ustSrcIndex   = uchIndex;
    xDel.ustCount      = nCount;
    xDel.nGuID         = n64Guid;
    SendMessageToClient( &xDel );

    return true;
}

//??????????????????????luo.qin 3.21 ??uchBagType = 0 ????????????
void GamePlayer::RemoveAllItem( uint8 uchBagType )
{
	//??????????????Item

	ItemBag* pItemBag = GetItemBagByBagType( uchBagType );

	for (int index = 0; index < pItemBag->GetNowBagSize(); ++index )
	{
		pItemBag->ClearItem( index );
	}

	pItemBag->CleanUp();	//????????????
}

//????????ID??????????????????????????luo.qin 3.22
int	 GamePlayer::ReturnItemID( uint8 uchBagType ,unsigned short ustItemId )
{
	ItemBag* pItemBag = NULL;
	switch ( uchBagType )
	{
	case BT_MaterialBag:
		pItemBag = &_MaterialItemBag;
		break;
	case BT_TaskBag:
		pItemBag = &_TaskItemBag;
		break;
	default:
		pItemBag = &_NormalItemBag;
	}

	//??????????????Item
	int n_BagSize = pItemBag->GetItemCount();
	for (int index = 0; index < pItemBag->GetItemCount(); ++index )
	{
		if ( ustItemId == pItemBag->m_pPackItem[index].GetItemID() )
		{
			return index;
		}
		else
		{
			continue;
		}

	}
	return 0;
}


ItemBag* GamePlayer::GetItemBagByItemType( uint16 ustItemType )
{
    switch( ustItemType )
    {
    case ItemDefine::ITEMTYPE_MATERIAL:
    case ItemDefine::ITEMTYPE_GEM:
        return &_MaterialItemBag;
        break;
    case ItemDefine::ITEMTYPE_TASK:
        return &_TaskItemBag;
        break;
    default:
        break;
    }

    return &_NormalItemBag;
}

ItemBag* GamePlayer::GetItemBagByBagType( uint8 uchBagType )
{
    switch( uchBagType )
    {
    case BT_MaterialBag:
        return &_MaterialItemBag;
        break;
    case BT_TaskBag:
        return &_TaskItemBag;
        break;
    default:
        break;
    }

    return &_NormalItemBag;
}

uint8 GamePlayer::GetItemBagType( uint16 ustItemType )
{
    switch( ustItemType )
    {
    case ItemDefine::ITEMTYPE_MATERIAL:
    case ItemDefine::ITEMTYPE_GEM:
        return BT_MaterialBag;
        break;
    case ItemDefine::ITEMTYPE_TASK:
        return BT_TaskBag;
        break;
    default:
        break;
    }

    return BT_NormalItemBag;
}

bool GamePlayer::PickPackageItem( int nItemPackageID )
{
    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( nItemPackageID );
    if ( pChar == NULL || !pChar->IsItem() )
    { return false; }

    ItemCharacter* pItemChar = static_cast<ItemCharacter*>( pChar );

    std::vector<int64> vecPickItem;
    pItemChar->GetCharItemList( vecPickItem );

    Log( theXmlString.GetString( eLog_PickPackage ), pItemChar->GetPackageDropType() );

    bool bIsSuccess = false;

    std::vector<int64>::iterator end = vecPickItem.end();
    for (std::vector<int64>::iterator iter = vecPickItem.begin(); iter != end; ++iter)
    {
        //????????????????????
        SCharItem* pItem = pItemChar->GetCharItem( *iter );
        if (pItem == NULL)
        {
            MsgPickPackageItemAck xPickAck;
            xPickAck.nItemPackageID = nItemPackageID;
            xPickAck.nItemID        = *iter;
            xPickAck.nResult        = MsgPickPackageItemAck::Result_AlreadyPick;
            GettheServer().SendMsgToSingle(&xPickAck, this);
            continue;
        }

        //????????
        if (!pItemChar->IsCanPickUpItem(*iter, GetDBCharacterID()))
        {
            MsgPickPackageItemAck xPickAck;
            xPickAck.nItemPackageID = nItemPackageID;
            xPickAck.nItemID        = *iter;
            xPickAck.nResult        = MsgPickPackageItemAck::Result_NoPurview;
            GettheServer().SendMsgToSingle(&xPickAck, this);
            continue;
        }

        uint16 nItemCount = pItem->itembaseinfo.ustItemCount;
        short nResult = AddItemToBag( *pItem, nItemCount, EIGS_DropItem, 3, pItemChar->GetDropMonsterID() );
        switch( nResult )
        {
        case ierr_Success:                  // ??????
            {
                MsgPickPackageItemAck xPickAck;
                xPickAck.nItemPackageID = nItemPackageID;
                xPickAck.nItemID        = *iter;
                xPickAck.nItemCount     = pItem->itembaseinfo.ustItemCount;
                xPickAck.nResult        = MsgPickPackageItemAck::Result_Success;
                GettheServer().SendMsgToSingle(&xPickAck, this);

                GameTeam* pTeam = theGameTeamManager.GetTeam( GetTeamID() );
                if ( pTeam != NULL )          // ??????
                {
                    ItemDefine::SItemCommon* pItemCommon = GettheItemDetail().GetItemByID( pItem->itembaseinfo.ustItemID );
                    if ( pItemCommon != NULL && pItemCommon->ustLevel >= pTeam->GetTeamAssignItemLevel() )
                    {
                        //????????????????,????????????
                        MsgTellPickPackageItem xPickItem;
                        xPickItem.xItem = *pItem;
                        HelperFunc::SafeNCpy(xPickItem.szPlayerName, GetCharName(), sizeof(xPickItem.szPlayerName));

                        pItemChar->SendMsgToAllPackageEffectPlayer( &xPickItem, GetDBCharacterID() );
                    }
                }

                pItemChar->RemoveCharItem( pItem->itembaseinfo.nOnlyInt, pItem->itembaseinfo.ustItemCount );

                bIsSuccess = true;
            }
            break;
        }
    }

    return bIsSuccess;
}

bool GamePlayer::OnNpcShip()
{
    if ( GetScirptNpc() <= 0)
    { return false; }

    BaseCharacter* pChar = theRunTimeData.GetCharacterByID( GetScirptNpc() );
    if ( pChar == NULL )
    { return false;}

    if ( !pChar->IsNpc())
    { return false; }

    NpcBaseEx* pNpcBaseCharcter = (NpcBaseEx*)pChar;

    if ( pNpcBaseCharcter->GetObjType() != Object_NpcShip )
    { return false; }

    NpcShipEx* pNpcShip = (NpcShipEx*)pNpcBaseCharcter;

    uint8 pos = 0;
    uint16 result = pNpcShip->OnShip( GetID(), pos );
    if ( result != ER_Success )
    { return false; }

	int temp = GetScirptNpc();
    m_nBigShipId  = GetScirptNpc();
    m_nNpcShipPos = pos;
    SetStatus( CS_ONSHIP );

    ResetCheckMoving();

    MsgOnOffNpcShip msg;
    msg.header.stID = GetID();
    msg.type        = MsgOnOffNpcShip::EOnOffType_On;
    msg.npcObjectId = m_nBigShipId;
    msg.pos         = m_nNpcShipPos;
    GettheServer().SendMsgToView( &msg, GetID(), false );
    
    return true;
}

bool GamePlayer::OffNpcShip()
{
    MsgOnOffNpcShip msg;
    msg.header.stID = GetID();
    msg.type        = MsgOnOffNpcShip::EOnOffType_Off;
    msg.npcObjectId = m_nBigShipId;
    msg.pos         = m_nNpcShipPos;
    GettheServer().SendMsgToView( &msg, GetID(), false );

    m_nBigShipId = InvalidGameObjectId;
    m_nNpcShipPos = 0;
    SetStatus( CS_IDLE );

    ResetCheckMoving();

    return true;
}

bool GamePlayer::GotOffMultiMount()
{
    BaseCharacter* pCharDriver = theRunTimeData.GetCharacterByID( m_nDriverId );
    if (pCharDriver == NULL)
    { return false; }

    GamePlayer* pDriver = static_cast< GamePlayer* >( pCharDriver );

    MsgGotOnOffDrome msg;
    msg.type = MsgGotOnOffDrome::EOnOffType_Off;
    msg.driverId = pDriver->GetID();
    msg.riderId  = GetID();
    msg.pos      = GetRidePos();

    int nResult = pDriver->_mountManager.GotOffMultiMount( GetID() );
    if (nResult != ER_Success)
    { 
        SendErrorToClient( ER_GotOffMultiMount );
        return false; 
    }

    GettheServer().SendMsgToView( &msg, GetID() );
    return true;
}

uint8 GamePlayer::CheckCanAttackResult( BaseCharacter* pTarget )
{
    uint8 nCheckResult = BaseCharacter::CheckCanAttackResult( pTarget );
    switch ( nCheckResult )
    {
    case CheckAttack::CanNotAttack:
    case CheckAttack::EnmityFightCamp:
    case CheckAttack::EnmityForce:
    case CheckAttack::EnmityTarget:
        {
            return nCheckResult;
        }
        break;
    case CheckAttack::EnmityCountry:
        {
            if ( pTarget->IsNpc() )
            { return nCheckResult; }
        }
        break;
    default:
        break;
    }

    // NPC ??????????
    if ( pTarget->IsNpc() )
    { return CheckAttack::CanNotAttack; }

    // ??????????
    if ( pTarget->IsPlayer() )
    {
        GamePlayer* pPlayer = static_cast< GamePlayer* >( pTarget );
        return CheckCanAttackPlayer( pPlayer );
    }

    // ??????????
    GamePlayer* pMaster = pTarget->GetMasterPlayer();
    if ( pMaster != NULL )
    { return CheckCanAttackPlayer( pMaster ); }

	//lyh++??????
	if(pTarget->IsEffectChar())
	{
	   BaseCharacter * Caster = ((CEffectChar*) pTarget)->GetCaster();
	   if (Caster)
	   {
		   return CheckCanAttackPlayer( ((GamePlayer*)Caster) );
	   }

	}

    // ??????????????
    int nSpecialType = pTarget->GetSpecialType();
    switch ( nSpecialType )
    {
    case MonsterDefine::SpecialPlayerAttack:
        {
            if ( pTarget->GetSpecialValue() == GetDBCharacterID() )
            { return CheckAttack::EnmityTarget; }
        }
        break;
    case MonsterDefine::SpecialTeamAttack:
        {
            if ( pTarget->GetSpecialValue() == GetTeamID() )
            { return CheckAttack::EnmityTarget; }
        }
        break;
    default:
        break;
    }

    return CheckAttack::AttackUnknow;
}

bool GamePlayer::CheckCanBeAttack()
{
    switch( GetStatus() )
    { //????????????????????????????????
    case CS_START:
    case CS_CHECK:
    case CS_LOGIN:
    case CS_LOGINTODB:
    case CS_WAITDBRET:
    case CS_DBLOGINED:
    case CS_LOADINGMAP:
        return false;
        break;
    default:
        break;
    }

    if ( GetStallOpen() )
    { 
        // ??????????????????????????????????
        if ( m_pMapData->CountryID == CountryDefine::Country_Init || m_pMapData->CountryID == GetCountry() )
        { return false; }
    }

    return BaseCharacter::CheckCanBeAttack();
}

void GamePlayer::Log(const char* szFormat, ...)
{
	
	if(!IsPlayer())
		return;

	char szDate[256] = {0};
	char szTime[256] = {0};
	char szBuf[LOG_MSG_LENGTH] = {0};

	SYSTEMTIME systime;
	GetLocalTime( &systime );

	_snprintf(szDate, sizeof(szDate)-1, "%04d-%02d-%02d", systime.wYear, systime.wMonth, systime.wDay);
	_snprintf(szTime, sizeof(szTime)-1, "%02d:%02d:%02d", systime.wHour, systime.wMinute, systime.wSecond);

	//????????
	va_list vl;
	va_start(vl, szFormat);
	int cnt = vsnprintf(szBuf, sizeof(szBuf)-1, szFormat, vl);
	va_end(vl);
	
	Common::_tstring logStr;
	logStr.Format( "%s|%s|%d|%d|%s|%s\n", szDate, szTime, GetAccountID(),GetDBCharacterID(), GetCharName(),szBuf);
	//_snprintf(plog->szText, sizeof(plog->szText)-1,"%s|%s|%d|%d|%s|%s\n", szDate, szTime, GetAccountID(),GetDBCharacterID(), GetCharName(),szBuf);

	if (!GetthePlayerLogger().PushLogger(logStr))
	{
		LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_WARNING, "GetthePlayerLogger().PushLogger() is Full!!!");
	}
}


void GamePlayer::DebugLog( const char* szFormat, ...)
{
    if( szFormat == NULL || szFormat[0] == 0 )
    { return; }

    char szBuf[1024] = {0};	
    va_list vl;
    va_start(vl, szFormat);
    int cnt = vsnprintf(szBuf, sizeof(szBuf)-1, szFormat, vl);
    va_end(vl);

    if ( szBuf[0] == 0 )
    { return; }

    GamePlayer* pPlayer = (GamePlayer*)this;
    
    LOG_MESSAGE( PLAYERLOGIC, LOG_PRIORITY_DEBUG, "[%d]\t[%s]\t[%s]\t[%d]\t[%d]\t[-]\t[%d]\t%s", GetAccountID(), GetAccount(),GetCharName(), GetDBCharacterID(), EctypeId2MapId( GetMapID()), /*GetSessionKey(),*/ GetID(), szBuf );
}

void GamePlayer::ShoppingLog(const char* szFormat, ...)
{
    if( szFormat == NULL || szFormat[0] == 0 )
    { return; }

    char szBuf[1024] = {0};
    // ????????
    va_list vl;
    va_start(vl, szFormat);
    int cnt = vsnprintf(szBuf, sizeof(szBuf)-1, szFormat, vl);
    va_end(vl);

    if ( szBuf[0] == 0 )
    { return; }
    
    LOG_MESSAGE( SHOPPINGOBJECT, LOG_PRIORITY_INFO, "[%d]\t[%s]\t[%s]\t[%d]\t[%d]\t%s", GetAccountID(), GetAccount(), GetCharName(), GetDBCharacterID(), GetID(),szBuf );
}

void GamePlayer::CheckCheatLog( const char* szFormat, ... )
{
    if(  szFormat == NULL || szFormat[0] == 0 )
    { return; }

    char szBuf[1024] = {0};
    // ????????
    va_list vl;
    va_start(vl, szFormat);
    int cnt = vsnprintf(szBuf, sizeof(szBuf)-1, szFormat, vl);
    va_end(vl);

    if ( szBuf[0] == 0 )
    { return; }

    LOG_MESSAGE( CHECKCHEATOBJECT, LOG_PRIORITY_INFO, "[%d]\t[%s]\t[%d]\t[%s]\t%s", GetAccountID(), GetAccount(), GetDBCharacterID(), GetCharName(), szBuf );
}

SCharFightAttr* GamePlayer::GetCharFightAttr()
{ 
    return &gCharInfoServer.baseinfo.baseProperty.fightAttr;
}

void GamePlayer::SetHPMax( uint32 hpMax )
{
    GetCharFightAttr()->hpMax.base = hpMax;
    GetCharFightAttr()->hpMax.UpdateFinal();
    _OnHPChanged( 0.3f );
}

uint32 GamePlayer::GetHPMax()
{ 
    return GetCharFightAttr()->hpMax.final; 
}

void GamePlayer::SetMPMax( uint32 mpMax )
{
    GetCharFightAttr()->mpMax.base = mpMax ;
    GetCharFightAttr()->mpMax.UpdateFinal();
    _OnMPChanged( 0.3f );
}

uint32 GamePlayer::GetMPMax()
{
    return GetCharFightAttr()->mpMax.final; 
}

//////////////////////////////////////////////////////////////////////////////////////
void GamePlayer::RecordNowTimeVar( int nVarID )
{
    unsigned short nNowTime = RecordVarTime::FormatTimeVar();
    SetVar( nVarID, nNowTime, SKW_SET, BV_NotSendMessage );
}

bool GamePlayer::IsTimeVarPassOneDay( int nVarID )
{
    // ????????
    unsigned short nRecordTime = GetVar( nVarID );
    return RecordVarTime::CheckPassOneDay( nRecordTime );
}

void GamePlayer::ProcessCheckVarClearTime()
{
    if ( !RecordTime::CheckRecordTime( m_nVarClearTime ) )
    { return; }

    RecordTime::SaveRecordTime( m_nVarClearTime );
    m_xVarClearTimer.StartTimer( HQ_TimeGetTime(), 60000 );

	//?????????? ????????????
	gCharInfoServer.otherdata.ClearKillInfo();
}

void GamePlayer::ProessClearSalary()
{
	if ( !RecordTime::CheckRecordTime( gCharInfoServer.otherdata.rankTitle.dGetSalaryTime ) )
		return;

	RecordTime::SaveRecordTime( gCharInfoServer.otherdata.rankTitle.dGetSalaryTime );

	ClearGetSalary();

	//theHuntingQuestManager.PassOneDay( this );
}

void GamePlayer::ProcessClearTimeVar()
{
    if ( !m_xVarClearTimer.DoneTimer())
    { return; }

    MsgTellCharVar xTell;
    const VarClearConfig::VarMap& mapVar = theVarClearConfig.GetPlayerVar();
    for ( VarClearConfig::VarMapConstIter iter = mapVar.begin(); iter != mapVar.end(); ++iter )
    {
        if ( !IsTimeVarPassOneDay( iter->first ) )   // ????????
        { continue; }

		RecordNowTimeVar( iter->first );

        for ( VarClearConfig::VarVectorIter viter = iter->second.begin(); viter != iter->second.end(); ++viter )
        {
            SetVar( *viter, 0, SKW_SET, BV_NotSendMessage );
            xTell.AddValue( *viter, 0 );
        }
    }

    if ( xTell.varCount == 0 )
    { return; }

    SendMessageToClient( &xTell );

	//????????????
	OnMsgSevenDaysData( NULL );
}

void GamePlayer::FirstEnterWorldClearTimeVar()
{
	MsgTellCharVar xTell;
	const VarClearConfig::VarMap& mapVar = theVarClearConfig.GetPlayerVar();
	for ( VarClearConfig::VarMapConstIter iter = mapVar.begin(); iter != mapVar.end(); ++iter )
	{
		if ( !IsTimeVarPassOneDay( iter->first ) )   // ????????
		{ continue; }

		RecordNowTimeVar( iter->first );

		for ( VarClearConfig::VarVectorIter viter = iter->second.begin(); viter != iter->second.end(); ++viter )
		{
			SetVar( *viter, 0, SKW_SET, BV_NotSendMessage );
			xTell.AddValue( *viter, 0 );
		}
	}

	if ( xTell.varCount == 0 )
	{ return; }

	SendMessageToClient( &xTell );
}

void GamePlayer::RefreshLieutenantAttr(bool IsDoPet)
{
	if(!g_Cfg.isOpenSubPetAtter)
		return;//?????????????? ??????
	//1.??????????????????
	ClearAllBaseAttrByPart (ECustomDataPart_lieutenant);//????????????????????????
	ClearAllFightAttrByPart( ECustomDataPart_lieutenant );
	//2.??????????????????????
	SPetItem*   pPetItem= _petManager.GetActivePet();    
	if(!pPetItem)
		return;
	if(!IsDoPet)
	{
		//???????? ???? ????????
		ApplyBaseAttrToFightAttr(true,ECustomDataPart_lieutenant);
		UpdateCharAllAttibute();
		SendCharAttibuteToClient();
	}
	else
	{
		//3.??????????????????
		//4.???????????? ????????????????????	
		for (uint8 i=0; i<EBaseAttr_MaxSize; ++i)
		{ 
			int Value = pPetItem->baseInfo.GetCurrentBaseAttr(i) * pPetItem->baseInfo.GetCurrentAptitude(i) /100
				* pPetItem->baseInfo.growRate /1000;
			gCharInfoServer.baseinfo.baseProperty.baseAttr.baseAttrValue[i].lieutenant  = Value;
			gCharInfoServer.baseinfo.baseProperty.baseAttr.baseAttrValue[i].UpdateFinal();
		}
		//5.????????????????????????
		ApplyBaseAttrToFightAttr(true,ECustomDataPart_lieutenant);
		//6.?????????????? ?????? ???????? ??????
		UpdateCharAllAttibute();
		SendCharAttibuteToClient();
	}
}
void GamePlayer::RefreshHeroAttr()
{
	
	ClearAllBaseAttrByPart ( ECustomDataPart_hero );
	// ????????????
	ClearAllFightAttrByPart( ECustomDataPart_hero );
	CItemHero::SItemHero* hero = theItemHero.FindHeroByHeroID(GetHeroId());
	if (!hero)
	{
		return;
	}
	for (uint8 i=0; i<EBaseAttr_MaxSize; ++i)
	{ 

		gCharInfoServer.baseinfo.baseProperty.baseAttr.baseAttrValue[i].hero += hero->heroAttr[i];
		gCharInfoServer.baseinfo.baseProperty.baseAttr.baseAttrValue[i].heroPer += hero->heroAttrPer[i];	
		gCharInfoServer.baseinfo.baseProperty.baseAttr.baseAttrValue[i].UpdateFinal();
	}
	// ????????????????????
	ApplyBaseAttrToFightAttr(true,ECustomDataPart_hero);

	UpdateCharAllAttibute();
}

void GamePlayer::RefreshHeroSkill()
{
	if (gCharInfoServer.baseinfo.liveinfo.hero_id!=INVALID_HERO_ID)
	{
		CItemHero::SItemHero* pHero = theItemHero.FindHeroByHeroID(gCharInfoServer.baseinfo.liveinfo.hero_id);
		if (pHero)
		{
			int skill[More_iMaxHeroSkill] = {pHero->hero_skill1,pHero->hero_skill2,pHero->hero_skill3};
			int skillLevel[More_iMaxHeroSkill] = {pHero->skill1_lv,pHero->skill2_lv,pHero->skill3_lv};

			for (int i=0;i<More_iMaxHeroSkill;i++)
			{
				//ItemDefine::SItemSkill* pItemSkill = GettheItemDetail().GetSkillByID( skill[i],skillLevel[i] );
				gCharInfoServer.otherdata.skills.heroSkill[i].ustSkillID = skill[i];
				gCharInfoServer.otherdata.skills.heroSkill[i].stSkillLevel = skillLevel[i];
				//gCharInfoServer.otherdata.skills.heroSkill[i].nColdTime	 = 0;
			}
		}
		else
		{
			return;
		}
	}
	else
	{
		return;
	}
}

void GamePlayer::RefreshMountAttr(bool IsInit)
{
	if(!IsInit)
		_mountManager.ApplyMountAttributeToChar( false, true );
	//////////????????///////////////////////////////////
	SMountItem* pCurrentMount = _mountManager.GetActiveMount();
	if (!pCurrentMount)
	{
		return;
	}
	// ????????????
	ClearAllBaseAttrByPart ( ECustomDataPart_pet );
	// ????????????
	ClearAllFightAttrByPart( ECustomDataPart_pet );

	for (uint8 i=0; i<EBaseAttr_MaxSize; ++i)
	{
		if (pCurrentMount->baseInfo.currentAttribute[i] > 0.0f)
			gCharInfoServer.baseinfo.baseProperty.baseAttr.baseAttrValue[i].pet += pCurrentMount->baseInfo.currentAttribute[i] * pCurrentMount->baseInfo.aptitudeAttribute[i]/100;
		gCharInfoServer.baseinfo.baseProperty.baseAttr.baseAttrValue[i].petPer += 0;//??????????????????????????????
		gCharInfoServer.baseinfo.baseProperty.baseAttr.baseAttrValue[i].UpdateFinal();
	}	
	// ????????????????????
	ApplyBaseAttrToFightAttr(true,ECustomDataPart_pet);
	UpdateCharAllAttibute();
}

void GamePlayer::GetHeroAddAttr(SCharHeroInfo* pHeroAddAttr)
{
	SCharFightAttr* pFightAttr = GetCharFightAttr();
	pHeroAddAttr->hpMax = pFightAttr->hpMax.hero;
	pHeroAddAttr->mpMax = pFightAttr->mpMax.hero;
	pHeroAddAttr->attackPhysics = pFightAttr->attackPhysics.hero;
	pHeroAddAttr->attackMagic = pFightAttr->attackMagic.hero;
	pHeroAddAttr->defendPhysics = pFightAttr->defendPhysics.hero;
	pHeroAddAttr->defendMagic = pFightAttr->defendMagic.hero;
	pHeroAddAttr->attackSpeed = pFightAttr->attackSpeed.hero;
	pHeroAddAttr->moveSpeed = pFightAttr->moveSpeed.hero;
	pHeroAddAttr->hpRestore = pFightAttr->hpRestore.hero;
	pHeroAddAttr->mpRestore = pFightAttr->mpRestore.hero;
	pHeroAddAttr->exact = pFightAttr->exact.hero;
	pHeroAddAttr->dodge = pFightAttr->dodge.hero;
	pHeroAddAttr->critical = pFightAttr->critical.hero;
	pHeroAddAttr->tenacity = pFightAttr->tenacity.hero;
	pHeroAddAttr->criticalIntensity = pFightAttr->criticalIntensity.hero;
	pHeroAddAttr->backStrike = pFightAttr->backStrike.hero;
	pHeroAddAttr->backStrikeResist = pFightAttr->backStrikeResist.hero;
	pHeroAddAttr->breakStrike = pFightAttr->breakStrike.hero;
	pHeroAddAttr->stabStrike = pFightAttr->stabStrike.hero;
	pHeroAddAttr->elementStrike = pFightAttr->elementStrike.hero;
	pHeroAddAttr->toxinStrike = pFightAttr->toxinStrike.hero;
	pHeroAddAttr->spiritStrike = pFightAttr->spiritStrike.hero;
	pHeroAddAttr->breakResist = pFightAttr->breakResist.hero;
	pHeroAddAttr->stabResist = pFightAttr->stabResist.hero;
	pHeroAddAttr->elementResist = pFightAttr->elementResist.hero;
	pHeroAddAttr->toxinResist = pFightAttr->toxinResist.hero;
	pHeroAddAttr->spiritResist = pFightAttr->spiritResist.hero;
}

//bool GamePlayer::ApplyHeroPassiveSkillEffect()
//{
//	if (INVALID_HERO_ID == GetHeroId())
//	{
//		return false;
//	}
//	if (_HeroSkillBag.GetSkillNum()<=0)
//	{
//		return false;
//	}
//	bool bRet = false;
//	for (int iLoop=0;iLoop<_HeroSkillBag.GetSkillNum();iLoop++)
//	{
//		SCharSkill* pCharSkill = _HeroSkillBag.GetSkillByIndex( iLoop );        
//		if ( !pCharSkill )
//		{ continue; }
//
//		ItemDefine::SItemSkill* pSkill = GettheItemDetail().GetSkillByID( pCharSkill->ustSkillID, pCharSkill->stSkillLevel );                
//		if(!pSkill)
//		{ continue; }
//
//		if ( pSkill->stGeneralType != ItemDefine::generaltype_passive )
//		{ // ????????????????
//			continue;
//		}
//
//		if ( !pSkill->bNeedWeapon )
//		{ // ??????????
//			ApplyPassiveSkillToChar( pSkill );
//			continue;
//		}
//
//		// ????????
//		SCharItem* pCharItem = GetVisualEquipItem( EEquipPartType_Weapon );
//		if ( NULL == pCharItem)
//		{ continue; }
//
//		ItemDefine::SItemCommon* pItemWeaponCommon = GettheItemDetail().GetItemByID(pCharItem->itembaseinfo.ustItemID);
//		if ( NULL == pItemWeaponCommon || pItemWeaponCommon->ucItemType != ItemDefine::ITEMTYPE_WEAPON )
//		{ continue; }
//
//		ItemDefine::SItemWeapon* pItemWeaponRhand = (ItemDefine::SItemWeapon*)pItemWeaponCommon;
//		if ( NULL == pItemWeaponRhand )
//		{ continue; }
//
//		if ( pSkill->stWeaponNeed == -1 || pSkill->stWeaponNeed == pItemWeaponRhand->stWeaponType )
//		{ 
//#pragma message("????????????????????????????????????????????")
//			//ApplyPassiveSkillToChar( pSkill ); 
//			bRet = true;
//		}
//	}
//	return bRet;
//}
//////////////////////////////////////////////////////////////////////////////////////

void GamePlayer::TellClientCountryID()
{
	MsgCountryTellCountryID msg;
	msg.header.stID = GetID();
	msg.uchCountry = gCharInfoServer.baseinfo.aptotic.ucCountry;
	SendMessageToClient(&msg);
}

void GamePlayer::TellClientTPHJRank()
{
	MsgTellTPHJRank msg;
	msg.rank = gCharInfoServer.baseinfo.liveinfo.TPHJRank;
	SendMessageToClient(&msg);
}

void GamePlayer::ChangeCountry(int& nCountryID)
{
	//??????????????
	if (HaveTeam())
	{
		return SendOperateAckToClient< MsgCountryChangeAck >( MsgCountryChangeAck::ECD_HaveTeam );
	}

	//????????????????????????
	if ( !TimeEx::IsPassCurrentTime( GetTimeVar( ECT_ChangeCountryTime ) , theChangeCountryConfig.GetCD()/*7 * OneDaySecond */) )
	{
		return SendOperateAckToClient< MsgCountryChangeAck >( MsgCountryChangeAck::ECD_TimeLimit );
	}

	//??????????ID
	if(nCountryID >= CountryDefine::Country_Max || nCountryID == CountryDefine::Country_Init)
	{
		return SendOperateAckToClient< MsgCountryChangeAck >( MsgCountryChangeAck::ECD_ErrorCountry );
	}

	//??????????????
	if (IsHaveTeacher())
	{
		return SendOperateAckToClient< MsgCountryChangeAck >( MsgCountryChangeAck::ECD_HaveTeacher );
	}

	//??????????????
	if (IsHaveMarriage())
	{
		return SendOperateAckToClient< MsgCountryChangeAck >( MsgCountryChangeAck::ECD_HaveMarriage );
	}

	//??????????????
	if (IsHaveStudent())
	{
		return SendOperateAckToClient< MsgCountryChangeAck >( MsgCountryChangeAck::ECD_HaveStudent );
	}

	//??????????????
	if ( m_pGuild != NULL )
	{
		return SendOperateAckToClient< MsgCountryChangeAck >( MsgCountryChangeAck::ECD_HaveGuild );
	}

	//????ID??????????????????
	if( GetCountry() == nCountryID)
	{
		return SendOperateAckToClient< MsgCountryChangeAck >( MsgCountryChangeAck::ECD_SameCountry );
	}
	
	// ????????
	if ( GetMoney() < theCountryConfig.GetCountryChangeCostMoney() )
	{
		return SendOperateAckToClient< MsgCountryChangeAck >( MsgCountryChangeAck::ECD_NotEnoughMoney );
	}

	// ????
	OperateMoney( EOT_Sub, theCountryConfig.GetCountryChangeCostMoney(), true, __FUNCTION__, __LINE__ ,ePlayerMoneySourceType_ChangeCountry);

	GS2CSCountryPlayerChange msg;
	msg.nPlayerID = GetDBCharacterID();
	msg.oldCountryID = GetCountry();
	msg.nowCountryID = nCountryID;
	GettheServer().SendMsgToCenterServer( &msg );

	// ????????
	GameCountry* pCountry = theGameCountryManager.GetCountry( nCountryID);
	InitPlayerCountry( pCountry );

	SetTimeVar( ECT_ChangeCountryTime, TimeEx::GetNowTime() );

	// ????????????
	MsgCountryTellCountryID xTell;
	xTell.header.stID = GetID();
	xTell.uchCountry = nCountryID;
	GettheServer().SendMsgToView( &xTell, GetID(), false );

	// ??????CenterServer
	GS2CSCountryChangeResult xResult;
	xResult.nPlayerID    = GetDBCharacterID();
	xResult.uchCountryID = nCountryID;
	GettheServer().SendMsgToCenterServer( &xResult );
}

void GamePlayer::ApplyPetAttrToChar(ItemDefine::SItemSkill* pPetSkill,bool bCancelApply)
{
	if (bCancelApply)
	{
		for (int nBufIndex=0;nBufIndex<ItemDefine::SItemSkill::EItemSkillConst_AddStatusMaxSize;nBufIndex++)
		{
			if (_buffManager.ClearBuffByBuffId( pPetSkill->ustMeAddStatusID[nBufIndex] ))
			{
				OnBuffStatusChanged( true );
			}
		}
	}
	else
	{
		if (pPetSkill && pPetSkill->petSkillCategory==EPetSkillCategory_Aptitude && pPetSkill->stGeneralType==ItemDefine::generaltype_passive)
		{
			long lResult =0;
			SPetItem* pPet = _petManager.GetActivePet();
			for (int nBufIndex=0;nBufIndex<ItemDefine::SItemSkill::EItemSkillConst_AddStatusMaxSize;nBufIndex++)
			{
				/*int16 addAttr[EBaseAttr_MaxSize]={0};
				ItemDefine::SItemStatus* pStatus = GetItemDetailConfig().GetStatus(pPetSkill->ustMeAddStatusID[nBufIndex],pPetSkill->ustMeAddStatusLevel[nBufIndex]);
				for(int nAddIndex=0;nAddIndex<EBaseAttr_MaxSize;nAddIndex++)
				{
					if (pStatus->stAddBaseAttrPer[nAddIndex]>0)
					{
						addAttr[i] += pPet->baseInfo.GetCurrentBaseAttr(nAddIndex) * pStatus->stAddBaseAttrPer[nAddIndex];
					}
					if (pStatus->stAddBaseAttr[nAddIndex]>0)
					{
						addAttr[i] += pStatus->stAddBaseAttr[nAddIndex];
					}
				}*/
				//??????????????????????????????????????????????????????????????????????????????????????????
				lResult = ApplyBufferStatus(pPetSkill->ustMeAddStatusID[nBufIndex],pPetSkill->ustMeAddStatusLevel[nBufIndex],GetID(),SCharBuff::StatusEventType_Other,0);
				if (lResult==GLR_Success)
				{
					OnBuffStatusChanged( true );
				}
			}
		}
	}
}

void GamePlayer::CalcCanTakeExp()
{
	ulCanTakeExp = 0;
	int iOldLevel = GetLevel();
	if ( iOldLevel >= g_Cfg.m_nLevelLimt )
	{
		iOldLevel = g_Cfg.m_nLevelLimt;
		//return;
	}

	int nNewLevel = iOldLevel + save_max_level_exp;
	//if ( nNewLevel >= g_Cfg.m_nLevelLimt + save_max_level_exp)
	//{
	//	nNewLevel = g_Cfg.m_nLevelLimt+ save_max_level_exp;
	//}
//??????????????????????
	for ( int i = iOldLevel; i < nNewLevel; ++i )
	{
		ulCanTakeExp += theExpStage.GetExpDistance(i);
	}
}

void GamePlayer::CheckToSendAddLimitPlayerCount()
{
	//if (GetLevel() >= theLevelLimitGameManager.GetLimitLevel()&&theLevelLimitGameManager.GetLimitLevel() > 0)
	//{
	//	theLevelLimitGameManager.AddPlayerCount(1);
	//}
}
bool GamePlayer::UnBindBagEquip(__int64 bagEquipGuid)
{
	//??????ID????????????
	//1.????????ID????????????
	SCharItem* pItem =  GetBagItemByGuid(bagEquipGuid);
	if(!pItem || pItem->itembaseinfo.nOnlyInt != bagEquipGuid) return false;
	ItemDefine::SItemCommon* pItemCommon = theItemDetailConfig.GetInstance().GetItemByID(pItem->itembaseinfo.ustItemID);
	if(!pItemCommon) return false;
	ItemDefine::SItemCanEquip * pEquipCommon = (ItemDefine::SItemCanEquip *)pItemCommon;
	if(!pEquipCommon) return false;
	//???????????????????? ??????????????????????????????
	if(!pEquipCommon->bIsCanBound)
		return false;
	if(!pEquipCommon->IsCanEquip())
		return false;
	//??????????
	if(GetNormalBagPointerByIndex(pItem->itembaseinfo.stPacketIdx)->itembaseinfo.nOnlyInt != bagEquipGuid)
		return false;
	int MaxUnBindSum = pEquipCommon->unBindCount;//????????????
	int NowUnBindSum =pItem->equipdata.unBindCount;//?????????????? 
	if(!pItem->IsBounded())
		return false;//?????????? ??????????


	//????????2??????????????
	/*if((NowUnBindSum == 0xFFFF && MaxUnBindSum !=0xFFFF) || ( MaxUnBindSum ==0xFFFF && NowUnBindSum != 0xFFFF))
	{
		NowUnBindSum = MaxUnBindSum;
		pItem->equipdata.unBindCount = pEquipCommon->unBindCount;
	}
	if(MaxUnBindSum == 0)
		return false;//??????????????
	if(NowUnBindSum == 0 && MaxUnBindSum !=0xFFFF)
		return false;//????????????????????????????*/
	//??????????????????-1??????
	if(NowUnBindSum == 0xFFFF)
	{
		if(MaxUnBindSum !=0xFFFF)
		{
			NowUnBindSum = MaxUnBindSum;
			pItem->equipdata.unBindCount = pEquipCommon->unBindCount;
		}
	}

	//????????????????????
	if(NowUnBindSum == 0)
		return false;//??0??????????????


	//???????????????????????????? ?????? ???????? ????????
	for(size_t i=0;i<pItem->EConstDefine_GemHoleMaxCount;++i)
	{
		if(pItem->equipdata.gemIds[i] != 0)
			return false;//????????????????????????
	}
	//?????????????????????? ??????????????????????????????????????
	int starLevel = pItem->equipdata.ucLevel +1;//??????0
	int QueryLevel = pItem->equipdata.quality +1;//????
	int level = pEquipCommon->stEquipLevelReq +1;//??????????
	int num = (int)((starLevel*0.7)*(4*0.2)*(level*0.1)*0.4) +1;
	int sum = GetItemCount(SID_UnBindItem);//????????????????????????????????
	if(sum < num)
		return false;
	//???????????? ?????????????????????????????? 
	if(!RemoveItem(SID_UnBindItem,num))
		return false;
	else
	{
		//LYH????????
		theLogEventService.LogItemConsume(GetAccountID(),GetDBCharacterID(),pItem->GetItemID(),
			pItem->GetItemCount(),pItem->GetItemGuid(),
			0,eItemLogInfo_ItemConsume_UnBind,GetCharName(),pItemCommon->GetItemName());
	}
	//???????????? ??????????????????????????????
	pItem->SetBounded(false);
	//?????? ??????????????????????
	if(pItem->equipdata.unBindCount >0 && pItem->equipdata.unBindCount != 0xFFFF)
	{
		--pItem->equipdata.unBindCount;
	}
	return true;
}
void GamePlayer::HandlePlayerCountryInfo()
{
	//???????????????????? ?????? ???????????????????????????? ???????????????????????? ???????????????????????????????????????? ????????????????
	uint8 uchPosition = gCharInfoServer.baseinfo.liveinfo.uchPosition;
	//1.????????ID ??????????????????????????????ID
	uint8 NowPos = CountryDefine::Position_None;
	GameCountry * pCountry = theGameCountryManager.GetCountry(GetCountryId());
	if(pCountry)
	{
		NowPos = pCountry->GetPosition(GetDBCharacterID());
		//???????????????????? ????????????????????????????????
		if(uchPosition == 0xFF)
		{
			//?????????????????????????????? ??????????????????????
			SetPlayerCountryPosition(NowPos);
		}
		else if(uchPosition != NowPos) 
		{
			//???????????????? ????????????????
			//1.?????????????? uchPosition
			theCountryReward.BSubItemAndMount(uchPosition,GetDBCharacterID());
			//2.??????
			SetPlayerCountryPosition(NowPos);
		}
	}
	else
	{
		//????????????????
		if(uchPosition == 0xFF)
		{
			SetPlayerCountryPosition(CountryDefine::Position_None);
		}
		else if(uchPosition != CountryDefine::Position_None)
		{
			theCountryReward.BSubItemAndMount(uchPosition,GetDBCharacterID());
			SetPlayerCountryPosition(NowPos);
		}
	}
}
void GamePlayer::SetPlayerCountryPosition(uint8 Position)
{
	gCharInfoServer.baseinfo.liveinfo.uchPosition = Position;
}
void GamePlayer::SendProcessTimeToClient(int StringID,int TimeStep)
{
	//??????????????????????
	uint32 SID = (uint32)StringID;
	uint32 Time = (uint32)TimeStep;
	MsgProcTimeStepAck msg;
	msg.StringID = SID;
	msg.TimeStep = Time;
	GettheServer().SendMsgToSingle( &msg,this);
}

void GamePlayer::UpdateMountWrongData(SMountItem* mount)
{
	if (!mount)
		return;

	const MountStrengthenData* pData = theMountStrengthenConfig.GetMountStrengthenData(mount->baseInfo.id);
	if (!pData || mount->baseInfo.level == 0)
	{
		for ( int i=0; i < EBaseAttr_MaxSize; ++i)
		{
			mount->baseInfo.potentialAttribute[i] = 0.0f;
		}
		mount->baseInfo.UpdateCurrentAttribute();
		return;
	}
	if (mount->baseInfo.level > 0)
	{
		for ( int i=0; i < EBaseAttr_MaxSize; ++i)
		{
			mount->baseInfo.potentialAttribute[i] = 0.0f;
		}
		for ( int i=0; i < mount->baseInfo.level; ++i)
		{
			mount->baseInfo.potentialAttribute[EBaseAttr_Strength] += pData->GetStrength(i);
			mount->baseInfo.potentialAttribute[EBaseAttr_Agility] += pData->GetAgility(i);
			mount->baseInfo.potentialAttribute[EBaseAttr_Stamina] += pData->GetStamina(i);
			mount->baseInfo.potentialAttribute[EBaseAttr_Intelligence] += pData->GetIntelligence(i);
		}
		mount->baseInfo.UpdateCurrentAttribute();
	}
}
void GamePlayer::CheckIsNeedLeaveTeam()
{	
	if(m_dwTeamSessionId == 0)
	{
		m_LogTime = 0;
		m_LogTeamID = 0;
		return;
	}
	GameTeam * pTeam = theGameTeamManager.GetTeam(m_dwTeamSessionId);
	if(!pTeam || !pTeam->GetIsTransnationalTeam())
	{
		m_LogTime = 0;
		m_LogTeamID = 0;
		return;
	}
	if(m_LogTime !=0 && HQ_TimeGetTime() >= m_LogTime && m_LogTeamID != 0 && m_LogTeamID == m_dwTeamSessionId)
	{
		//???????????????? ?????????????????????? ????????????
		GS2CSPlayerRemoveFromTeamReq xRemove;
		xRemove.dwSessionId  = m_dwTeamSessionId;
		xRemove.dwDataBaseId = GetDBCharacterID();
		xRemove.bKick        = true;
		GettheServer().SendMsgToCenterServer( &xRemove );
		m_LogTime = 0;
		m_LogTeamID = 0;
		return;
	}	
	//??????????????PK????
	MapConfig::MapData* pMapData = GetMapData();
	if ( pMapData != NULL )
	{
		int nMapPKMode  = pMapData->CanPk ;
		GameStage *pStage = theGameWorld.GetStageById( GetMapID() );
		if(pStage != NULL)
		{
			GameZone *pZone =  pStage->GetZone(GetCurZoneID());
			if ( pZone != NULL && pZone->GetZonePKMode() != nMapPKMode )
				nMapPKMode = pZone->GetZonePKMode();
		}
		//????????????PK?????? ???????????????????????????? ????
		if( MapConfig::MapData::EPKM_UnAllow_PK  != nMapPKMode && MapConfig::MapData::EPKM_None_PK  != nMapPKMode)
		{
			if(m_LogTime == 0)
			{
				m_LogTime = HQ_TimeGetTime() + 5*1000;
				m_LogTeamID = m_dwTeamSessionId;
				//???????? ???? ????????????????
				MsgTellClientLeaveTeam msg;
				msg.TeamID = m_dwTeamSessionId;
				msg.TimeStep = 5000;
				msg.Result = true;
				SendMessageToClient(&msg);
			}
		}
		else
		{
			if(m_LogTime !=0 && m_LogTeamID != 0)
			{
				MsgTellClientLeaveTeam msg;
				msg.TeamID = m_dwTeamSessionId;
				msg.TimeStep = 5000;
				msg.Result = false;
				SendMessageToClient(&msg);
			}
			m_LogTime = 0;
			m_LogTeamID = 0;
			
		}
	}
}
void GamePlayer::SetPetDuration(int Value)
{
	//????????????????
	GetCharInfo().otherdata.PetDuration += Value;
	if(GetCharInfo().otherdata.PetDuration >g_Cfg.MaxPetDuration)
		GetCharInfo().otherdata.PetDuration = g_Cfg.MaxPetDuration;
	if(GetCharInfo().otherdata.PetDuration < 0)
		GetCharInfo().otherdata.PetDuration = 0;
	//??????????????
	MsgChangePetDuration msg;
	msg.Value = GetCharInfo().otherdata.PetDuration;
	SendMessageToClient(&msg);//??????????????
}
int GamePlayer::GetPetDuration()
{
	return GetCharInfo().otherdata.PetDuration;	
}
void GamePlayer::OnUpdatePetExp()
{
	//????????????????????
	SPetItem * pPet = _petManager.GetActivePet();
	if(!pPet)
	{
		m_PetExpUpdateLog = HQ_TimeGetTime();
		return;
	}
	if(HQ_TimeGetTime() - m_PetExpUpdateLog >= thePetDefineConfig.GetTimeStep() * 1000)
	{
		m_PetExpUpdateLog = HQ_TimeGetTime();

		int Exp = thePetDefineConfig.GetTimeExp();
	    if ( _bNeedAntiAddiction )
		{ 
			if ( enumAntiAddictionStateTired == gTransferRuntimeInfo.nAntiAddicationStatus)
			{ Exp /= 2; }
			else if (enumAntiAddictionStateRest == gTransferRuntimeInfo.nAntiAddicationStatus )
			{ Exp = 0; }
		}

		_petManager.AddActivePetExp(Exp);//????????
	}
}
void GamePlayer::SetPetMode(__int64 PetGuID,uint32 ModeID,int LastTime)
{
	//??????????????????
	__int64 EndTime = 0;
	if(LastTime == -1)
	{
		EndTime = -1;
	}
	else
	{
		time_t NowTime;
		_time64(&NowTime);
		EndTime = (__int64)NowTime + LastTime;//????????
	}
	SPetItem * pPet = _petManager.GetPetByGuid(PetGuID);
	if(!pPet)
		return;
	if(pPet != _petManager.GetActivePet())
		return;
	//1.??????????????ID
	pPet->baseInfo.SetPetModeID(ModeID,EndTime);
	//2.??????????????????????????
	MsgAddUpdatePet msg;
	msg.header.stID = GetID();
	msg.pet = *pPet;
	msg.type = MsgAddUpdatePet::OT_Update;
	GettheServer().SendMsgToSingle( &msg, this);
	//3.????????????????????
	if(_petManager.GetActivePet() == pPet)
	{
		MonsterNurturePet* pNurturePet = (MonsterNurturePet*)_petManager.GetMonsterNurturePet();
		if ( pNurturePet != NULL )
		{ 
			pNurturePet->UpdatePetMode(); 
		}
	}
}

void GamePlayer::AddCard(short stCardID, short stLevel)
{
	if( stCardID < 0 || stCardID >= More_nCardMax || stLevel < 0 )
		return;

	short level = GetCharInfo().otherdata.cards.shCardLevel[stCardID];
	if ( level != -1 && level >= stLevel )
		return;

	GetCharInfo().otherdata.cards.shCardLevel[stCardID] = stLevel;

	MsgUpdateCard msg;
	msg.stCardID = stCardID;
	msg.stLevel = stLevel;
	GettheServer().SendMsgToSingle( &msg, this );

	//????7????
	_sevenDayManager.TriggerSevenDaysVar( (int)SevenDaysConfig::TD_FourthDay );
}

bool GamePlayer::SetCardAchieve(int nachID)
{
	if ( nachID < 0 || nachID >= More_nCardAchieve )
		return false;

	if ( GetCharInfo().otherdata.cards.unCardAchieve[nachID] == 1 ) 
		return false;

	CardAchieveConfig::CardAchieveVector achVec = theCardAchieveConfig.GetCardVec();

	int nHasCount = 0;
	for (int j = 0; j < achVec[nachID].shCardCount; j++)
	{
		if ( achVec[nachID].shCardIDs[j] < 0 || achVec[nachID].shCardIDs[j] > More_nCardMax )
			continue;
		if ( GetCharInfo().otherdata.cards.shCardLevel[achVec[nachID].shCardIDs[j]] >= 0 )
			nHasCount++;
	}

	if ( nHasCount >= achVec[nachID].shCardCount )
	{
		GetCharInfo().otherdata.cards.unCardAchieve[nachID] = 1;
		return true;
	}

	return false;
}

void GamePlayer::TriggerSevenDays()
{
	__time64_t nowTime = 0;
	_time64(&nowTime);

	if ( GetCharInfo().otherdata.sevenDayStartTime > 0 )
		return;

	GetCharInfo().otherdata.sevenDayStartTime = nowTime;

	MsgTriggerSevenDays msg;
	msg.triggerTime = nowTime;
	GettheServer().SendMsgToSingle( &msg, this );

	OnMsgSevenDaysData( NULL );
}

//=========
//?????????????????? 1 ???????????? 2??????????????????????????????????????????????
int  GamePlayer::AddFriendPoint(int Distance , int FriendlyPoint)
{
	GameTeam* pTeam = theGameTeamManager.GetTeam( GetTeamID() );
	if ( pTeam == NULL )
	{ 	//????????
		return 1; 
	}

	if (pTeam->TeamMemberCount() != 2)
	{
		//??????????????????
		return 2;
	}

	DWORD TeamMemberID  = InvalidLogicNumber;       // ????????id
	for ( int i = 0; i < 2; ++i )
	{
		GameTeamMember* pMember = pTeam->GetTeamMemberByIndex( i );
		if ( pMember != NULL  )
		{ 
			GamePlayer* pPlayer = theRunTimeData.GetGamePlayerByDBID( pMember->GetID() );
			if (pPlayer->GetID() == GetID())
			{
				continue; 
			}
			TeamMemberID = pMember->GetID();	
		}		
		
		break;
	}

	if ( TeamMemberID == InvalidLogicNumber)
	{
		//????????????
		return 10;
	}

	GamePlayer* pPlayer = theRunTimeData.GetGamePlayerByDBID( TeamMemberID );
	if(!pPlayer) return 10; //????????????????

	//4 ??????????????
	if ( !m_pRelation->HaveRelation( pPlayer->GetDBCharacterID(), RelationDefine::Friend ) )
	{ 
		return 3; //???????? 
	}

	//????????????
	D3DXVECTOR3 vDistance( pPlayer->GetFloatX() - GetFloatX(), pPlayer->GetFloatY() - GetFloatY(), 0 );
	float fDistance = D3DXVec3Length( &vDistance);
	if ( fDistance > Distance)
	{
		return 4; //????????
	}

	//=========================
	//??????????
	UpdateFriendly( pPlayer->GetDBCharacterID(), RelationDefine::UpdateAddFriendly, FriendlyPoint );
	pPlayer->UpdateFriendly( GetDBCharacterID(), RelationDefine::UpdateAddFriendly, FriendlyPoint );

	return 0;
}
void GamePlayer::OnHandleScriptStates()
{
	//??????????????????????????
	if(m_ScriptStatesID == EScriptStates_Init)
		return;
	switch(m_ScriptStatesID)
	{
	case EScriptStates_OnDead:
		{
			if(IsDead())
			{
				//???????????? ????????????
				CancelCurScript( __FILE__, __FUNCTION__ );
				SetScriptStatesID();
			}
		}
		break;
	}
}

void GamePlayer::ClearGetSalary()
{
	gCharInfoServer.otherdata.rankTitle.bGetSalary = 0;

	MsgAskGetSalaryAck msg;
	msg.bGet = gCharInfoServer.otherdata.rankTitle.bGetSalary;
	GettheServer().SendMsgToSingle( &msg, this );
}
void GamePlayer::OnRoleOnLineQuestEntrustHandle()
{
	//???????????????? ??????????????
	//????????????
	for( int i = 0; i < dr_MaxQuest; ++i )
    {
        short nQuestId = dr_MinQuestId + i;
		short QuestStates = theQuestManager.GetQuestState(GetVar(nQuestId));
		if(QuestStates == QuestManager::eQuestFrozen)
		{
			vector<unsigned int> vec;
			if(!theGameQuestEntrustManager.IsExitesQuestEntrust(GetDBCharacterID(),nQuestId,vec))
			{
				//?????????? ??????????????????????
				SetVar( nQuestId,theQuestManager.SetQuestState( GetVar(nQuestId), QuestManager::eQuestGaining ));
			}
			else
			{
				vector<unsigned int>::iterator Iter = vec.begin();
				for(;Iter != vec.end();++Iter)
				{
					QuestEntrustStates * pInfo = theGameQuestEntrustManager.GetQuestEntrust(*Iter);
					if(!pInfo || !pInfo->IsSecc)
						continue;
					//??????????????
					SetVar( nQuestId,theQuestManager.SetQuestState( GetVar( nQuestId  ), QuestManager::eQuestEntrustDone ));
					//????????
					GS2CSQuestEntrustEndReq msg;
					msg.ID = pInfo->ID;
					GettheServer().SendMsgToCenterServer( &msg );
				}
			}
		}
		else if(QuestStates == QuestManager::eQuestGaining && theGameQuestEntrustManager.GetConfig().GetOldQuestID(nQuestId) !=0)
		{
			if(theGameQuestEntrustManager.IsExitesJoinQuestEntrust(GetDBCharacterID()) == 0)
			{
				//SetVar( nQuestId,theQuestManager.SetQuestState( GetVar(nQuestId), QuestManager::eQuestNotGain ));
				//????????
				Script_CancelQuest(nQuestId);

				long nResult = ApplyBufferStatus(theGameQuestEntrustManager.GetConfig().GetBuffID(),theGameQuestEntrustManager.GetConfig().GetBuffLevel(), GetID(), SCharBuff::StatusEventType_Other, 0);
				if ( nResult == GLR_Success  )
					OnBuffStatusChanged( true );

				MsgQuestEntrustShowInfo msgInfo;
				msgInfo.ID = eText_QuestEntrust_QuestDrop;
				SendMessageToClient(&msgInfo);
			}
		}
	}
}

void GamePlayer::OperateHuntingCount( int nType, int nValue )
{
	switch ( nType )
	{
	case EOT_Add:
		{
			gCharInfoServer.otherdata.sHunting.nCount += nValue;
		}
		break;
	case EOT_Sub:
		{
			gCharInfoServer.otherdata.sHunting.nCount -= nValue;
		}
		break;
	case EOT_Set:
		{
			gCharInfoServer.otherdata.sHunting.nCount = nValue;
		}
		break;
	default:
		return;
	}

	if ( gCharInfoServer.otherdata.sHunting.nCount < 0 )
		gCharInfoServer.otherdata.sHunting.nCount = 0;
}

void GamePlayer::DoneHuntingQuest( int nQuestId )
{
	theHuntingQuestManager.DoneQuest( nQuestId, this );
}
void GamePlayer::SendChangeEquipErrorInfo()
{
	MsgShowCenterInfo msg;
	msg.ID = eText_ChangeEquip_ErrorStates;
	GettheServer().SendMsgToSingle( &msg, this );
}
void GamePlayer::UpdataThreeDayInfo()//????????
{
	//????3????????????
	uint32 OnLineTime = GetOnLineTime();
	if(ThreeDayConfig::Instance().GetWriteTime() > OnLineTime)//??????????????
		return;
	if(gCharInfoServer.otherdata.nThreeDayVision != ThreeDayConfig::Instance().GetVision())
		return;
	const ThreeDayOnce* pInfo = ThreeDayConfig::Instance().GetNowDayThreeDayOnceInfo();
	if(!pInfo)
		return;
	if(gCharInfoServer.otherdata.nThreeDayValue & pInfo->nValue)
		return;//??????????
	unsigned int ItemID = pInfo->nItemID;
	unsigned int ItemSum = pInfo->nItemSum;
	gCharInfoServer.otherdata.nThreeDayValue += pInfo->nValue;
	MsgGetThreeDayItemAck msg;
	msg.vision = gCharInfoServer.otherdata.nThreeDayVision;
	msg.value = gCharInfoServer.otherdata.nThreeDayValue;
	GettheServer().SendMsgToSingle( &msg, this );
	//????????????????????????
	GS2CSSendMailReq xReq;
	xReq.charDbId = RelationDefine::InitID;
	xReq.mail.type  = SMail::EMT_System;
	xReq.mail.state = SMail::EMS_NotOpen;
	xReq.mail.sendTime = TimeEx::GetNowTime();        
	// ??????
	xReq.mail.owners[EM_FromIndex].charDbId = 0;
	sprintf_s( xReq.mail.owners[EM_FromIndex].addressName, sizeof( xReq.mail.owners[EM_FromIndex] ) - 1, theXmlString.GetString( eText_MailSystemName ) );
	// ??????
	xReq.mail.owners[EM_ToIndex].charDbId = GetDBCharacterID();	
	HelperFunc::SafeNCpy( xReq.mail.owners[EM_ToIndex].addressName, GetCharInfo().baseinfo.aptotic.szCharacterName, sizeof( xReq.mail.owners[EM_ToIndex].addressName ) );
	//????
	sprintf_s( xReq.mail.content, sizeof( xReq.mail.content ) - 1,theXmlString.GetString( eText_ThreeDay_Mail_Context ) );
	//????
	sprintf_s( xReq.mail.title, sizeof( xReq.mail.title ) - 1, theXmlString.GetString( eText_ThreeDay_Mail_Title ) );
	//????
	SCharItem item;
	if(theRunTimeData.CreateItem(ItemID,ItemSum,HelperFunc::CreateID(),item))
	{
		xReq.mail.accessory.type = SMail::EAT_Item;
		memcpy( &xReq.mail.accessory.content, &item, sizeof(SCharItem)); 
		GettheServer().SendCenterServerMsg( &xReq );
	}
}
bool GamePlayer::IsInBattleMap()
{
	CampBattle* pCampBattle = theCampBattleControl.GetCampBattle( GetFightCamp(), GetMapID() ,GetCountryId());
    if ( pCampBattle != NULL )
    {
        return true; 
    }

	GameGuildGeneralBattleManager* pManager = static_cast<GameGuildGeneralBattleManager*>(theGameBattleControl.GetGameBattleManager(GameBattleDefine::GameBattle_Type_GuildGeneral));
	if(pManager)
	{
		GameGuildGeneralBattle* pBattle = pManager->GetGameBattleByPlayerID(GetDBCharacterID());
		if(pBattle)
		{
			return true;
		}
	}
	return false;
}
bool GamePlayer::ChangeMountStarLevel(__int64 MountOnlyID,unsigned int StarLevel,bool IsMoveLevel)
{
	//????????????????????????????  ????????????\
	//1.????????????????
	if(StarLevel >SMountItem::MICD_MountMaxLevel)
		return false;
	SMountItem* pMount = _mountManager.GetMountByGuid(MountOnlyID);
	if(!pMount)
		return false;
	//2.????????????????????????
	if(pMount == _mountManager.GetActiveMount())
		return false;
	//3.??????????????
	if(pMount->baseInfo.level == StarLevel)
		return true;
	const MountStrengthenData* pData = theMountStrengthenConfig.GetMountStrengthenData(pMount->baseInfo.id);
	if (!pData)
		return false;
	unsigned short oldLev[1] = {pMount->baseInfo.level};
	//4.??????????????????	
	unsigned int nLossLevel = 0;
	if(pMount->baseInfo.level > StarLevel)
	{
		nLossLevel = pMount->baseInfo.level - StarLevel;
		unsigned int nLevel = pMount->baseInfo.level;
		unsigned int MinLevel = (nLevel - nLossLevel);
		for (int i = (int)(nLevel - 1); i >= (int)MinLevel; i--)
		{
			pMount->baseInfo.potentialAttribute[EBaseAttr_Strength] -= pData->GetStrength(i);
			pMount->baseInfo.potentialAttribute[EBaseAttr_Agility] -= pData->GetAgility(i);
			pMount->baseInfo.potentialAttribute[EBaseAttr_Stamina] -= pData->GetStamina(i);
			pMount->baseInfo.potentialAttribute[EBaseAttr_Intelligence] -= pData->GetIntelligence(i);
		}
	}
	else
	{
		//????????????
		nLossLevel = StarLevel - pMount->baseInfo.level;
		unsigned int nLevel = pMount->baseInfo.level;
		for (int i = (int)nLevel; i < StarLevel; ++i)
		{
			pMount->baseInfo.potentialAttribute[EBaseAttr_Strength] += pData->GetStrength(i);
			pMount->baseInfo.potentialAttribute[EBaseAttr_Agility] += pData->GetAgility(i);
			pMount->baseInfo.potentialAttribute[EBaseAttr_Stamina] += pData->GetStamina(i);
			pMount->baseInfo.potentialAttribute[EBaseAttr_Intelligence] += pData->GetIntelligence(i);
		}
	}
	if (pMount->baseInfo.potentialAttribute[EBaseAttr_Strength] < 0.0f)
		pMount->baseInfo.potentialAttribute[EBaseAttr_Strength] = 0.0f;
	if (pMount->baseInfo.potentialAttribute[EBaseAttr_Agility] < 0.0f)
		pMount->baseInfo.potentialAttribute[EBaseAttr_Agility] = 0.0f;
	if (pMount->baseInfo.potentialAttribute[EBaseAttr_Stamina] < 0.0f)
		pMount->baseInfo.potentialAttribute[EBaseAttr_Stamina] = 0.0f;
	if (pMount->baseInfo.potentialAttribute[EBaseAttr_Intelligence] < 0.0f)
		pMount->baseInfo.potentialAttribute[EBaseAttr_Intelligence] = 0.0f;
	pMount->baseInfo.level = StarLevel;
	//5.????????
	pMount->baseInfo.UpdateCurrentAttribute();
	//6.????????
	short stCardId = theCardIconConfig.GetCardIdByTypeId( pMount->baseInfo.id );
	if ( stCardId != -1 )
	{
		AddCard( stCardId, pMount->baseInfo.level );
	}
	MsgMountStrengthenAck msg;
	msg.mount = *pMount;
	msg.result = MsgMountStrengthenAck::eR_Success;
	msg.loselevel = nLossLevel;
	msg.IsMoveLevel=IsMoveLevel;
	GettheServer().SendMsgToSingle( &msg, this);
	//????7????
	_sevenDayManager.TriggerSevenDaysVar( (int)SevenDaysConfig::TD_FifthDay );
	//????????????
	_achieveManager.UpdateTriggerByValueType( EAT_MountLevel , pMount->baseInfo.level );
	//LYH????????
	unsigned short curLev[1] = {pMount->baseInfo.level};
	theLogEventService.LogItemUpgrade(GetAccountID(),GetDBCharacterID(),pMount->GetMountID(),1,pMount->GetMountGuid(),eItemLogInfo_ItemUpgrade_MountIntensify,
		                              MsgMountStrengthenAck::eR_Success,oldLev,curLev,GetCharName(),pMount->GetMountName());
}
void GamePlayer::HandlePlayerCountryBuff()
{
	//???? ???? ??????????????BUFF
	if(!GetBuffManager())
		return;
	//OnBuffStatusChanged( true );
	//??????????????BUFF ????????????
	if(GetBuffManager()->IsHaveStatus(g_Cfg.CountryWeakBuffID) && GetCountryId() == theGameCountryManager.GetWeakCountry())
		return;
	else if(GetBuffManager()->IsHaveStatus(g_Cfg.CountryStrongBuffID) && GetCountryId() == theGameCountryManager.GetStrongCountry())
		return;
	else if(GetBuffManager()->IsHaveStatus(g_Cfg.CountryBalancedBuffID) && GetCountryId() != theGameCountryManager.GetWeakCountry() && GetCountryId() != theGameCountryManager.GetStrongCountry())
		return;
	bool IsChange= false;
	IsChange = GetBuffManager()->ClearBuffByBuffIdLevel(g_Cfg.CountryWeakBuffID,g_Cfg.CountryWeakBuffLevel);
	IsChange = GetBuffManager()->ClearBuffByBuffIdLevel(g_Cfg.CountryStrongBuffID,g_Cfg.CountryStrongBuffLevel);
	IsChange = GetBuffManager()->ClearBuffByBuffIdLevel(g_Cfg.CountryBalancedBuffID,g_Cfg.CountryBalancedBuffLevel);
	if(GetCountryId() == CountryDefine::Country_Init)
	{
		if(IsChange)
			OnBuffStatusChanged( true );
		return;
	}
	//?????????????? ??????????????????????
	long nResult = GLR_Success;
	if(GetCountryId() == theGameCountryManager.GetStrongCountry())
	{
		nResult =ApplyBufferStatus(g_Cfg.CountryStrongBuffID,g_Cfg.CountryStrongBuffLevel,GetID(),SCharBuff::StatusEventType_Other, 0);
	}
	else if(GetCountryId() == theGameCountryManager.GetWeakCountry())
	{
		nResult =ApplyBufferStatus(g_Cfg.CountryWeakBuffID,g_Cfg.CountryWeakBuffLevel,GetID(),SCharBuff::StatusEventType_Other, 0);
	}
	else
	{
		nResult =ApplyBufferStatus(g_Cfg.CountryBalancedBuffID,g_Cfg.CountryBalancedBuffLevel,GetID(),SCharBuff::StatusEventType_Other, 0);
	}
	if ( nResult == GLR_Success || IsChange)
	{
		OnBuffStatusChanged( true );
	}
}
void GamePlayer::SendLeaveExpInfo()
{
	//??????????????????????????????
	MsgLeaveExpAck msg;
	msg.PlayerID = GetDBCharacterID();
	//1.????????
	msg.RadExp	= GetKillMonsterModulus();
    msg.KillSum = gCharInfoServer.otherdata.dwRecordKillMonsterCount;
	msg.MaxKillSum = theKillMonsterCountConfig.GetMaxCount( msg.KillSum );
	//2.????????
	msg.Hour = min(g_Cfg.MaxLeaveExpHour, gCharInfoServer.otherdata.LeaveExpHourSum);
	msg.Exp = ceil(GetLevel() * GetLevel() * GetLevel() * GetLevel() * 0.07 * msg.Hour);
	GettheServer().SendMsgToSingle( &msg, this);
}
void GamePlayer::GetLeaveExp()
{
	//????????????????????
	int Exp = ceil(GetLevel() * GetLevel() * GetLevel() * GetLevel() * 0.07 * min(g_Cfg.MaxLeaveExpHour,gCharInfoServer.otherdata.LeaveExpHourSum));
	IncreaseExp(Exp,0);//????????
	gCharInfoServer.otherdata.LeaveExpHourSum = 0;//?????????? ????????????????
	SendLeaveExpInfo();
}