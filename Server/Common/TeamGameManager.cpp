#include "TeamManager.h"
#include "GameServer.h"
#include "ShareData.h"
#include "GamePlayer.h"
#include "RelationConfig.h"

template<>
void GameTeam::ProcessManipleInfo( GameTeamMember& xMember )
{
    // 在GameServer上什么也不做
}

template<>
void GameTeam::ChangeTeamHeaderToOnLineMember()
{
    // 在GameServer上什么也不做
}
template<>
void GameTeam::UpdateTeamTransnationalStates(bool IsAdd,unsigned int ID)
{
}
template<>
void GameTeam::ProcessAddTeamMember( GameTeamMember& xMember, TeamDefine::TeamInvite* pRecord )
{
    // 先把新队员发送给客户端 
    MsgAddTeamMember xAdd;

    xAdd.bIsNewAdd  = true;
    xAdd.bHeader    = IsTeamHeader( xMember.GetID() );
    xAdd.dwMemberID = xMember.GetID();                
    xAdd.dwGroupId  = GetID();         
    xAdd.stManiple  = xMember.GetManipleID();
    xAdd.bHeader2   = xMember.GetManipleHeader();
    xAdd.nHp        = xMember.GetHP();
    xAdd.nMp        = xMember.GetMP();
    xAdd.nHpMax     = xMember.GetHPMax();
    xAdd.nMpMax     = xMember.GetMPMax();
    xAdd.stLvl      = xMember.GetLevel();
    xAdd.nFaceId    = xMember.GetFaceID();
    xAdd.nHairId    = xMember.GetHairID();
    xAdd.nHeadPicId = xMember.GetHeadPicID();
    xAdd.shSex      = xMember.GetSex();    
    xAdd.Profession = xMember.GetProfession();
    HelperFunc::SafeNCpy( xAdd.szName, xMember.GetName(), sizeof( xAdd.szName ) );
    SendMessageToTeamClient( &xAdd, TeamDefine::ErrorID, TeamDefine::NotSendToCenter ); 
    
    UpdateTeamBuffer(); // 更新小队Buffer

    // 发送消息给客户端
    GamePlayer* pMemberPlayer = GetMemberPlayer( xMember.GetID() );
    if ( pMemberPlayer == NULL )
    { return; }

    // 把所有队员的资料发送给新队员
    for ( MemberListIter iter = m_listTeamMember.begin(); iter != m_listTeamMember.end(); ++iter )
    {
        if ( iter->GetID() == xMember.GetID() )
        { continue; }

        xAdd.bIsNewAdd   = false;
        xAdd.bHeader     = IsTeamHeader( iter->GetID() );
        xAdd.dwMemberID  = iter->GetID();                
        xAdd.dwGroupId   = GetID();         
        xAdd.stManiple   = iter->GetManipleID();
        xAdd.bHeader2    = iter->GetManipleHeader();
        xAdd.nHp         = iter->GetHP();
        xAdd.nMp         = iter->GetMP();
        xAdd.nHpMax      = iter->GetHPMax();
        xAdd.nMpMax      = iter->GetMPMax();
        xAdd.stLvl       = iter->GetLevel();
        xAdd.nFaceId     = iter->GetFaceID();
        xAdd.nHairId     = iter->GetHairID();
        xAdd.nHeadPicId  = iter->GetHeadPicID();
        xAdd.shSex       = iter->GetSex();    
        xAdd.Profession  = iter->GetProfession();
        HelperFunc::SafeNCpy( xAdd.szName, iter->GetName(), sizeof( xAdd.szName ) );

        GettheServer().SendMsgToSingle( &xAdd, pMemberPlayer );
    }
}

template<>
void GameTeam::ProcessRemoveTeamMember( unsigned int dwMemberID )
{
    if ( TeamMemberCount() <= 1 )
    {
        MsgExitTeam xExitTeamMsg;
        xExitTeamMsg.bIsDisband = true;
        for ( MemberListIter iter = m_listTeamMember.begin(); iter != m_listTeamMember.end(); ++iter )
        {
            GamePlayer* pMemberPlayer = GetMemberPlayer( iter->GetID() );
            if ( pMemberPlayer != NULL )
            {
				xExitTeamMsg.header.stID = pMemberPlayer->GetID();
                GettheServer().SendMsgToSingle( &xExitTeamMsg, pMemberPlayer );

                pMemberPlayer->SetTeamID( TeamDefine::NoneSessionID );
                pMemberPlayer->TellTeamInfoChange( ETP_None );

                ClearTeamBuffer( pMemberPlayer );
            }
        }
    }
    else
    {
        GamePlayer* pMemberPlayer = GetMemberPlayer( dwMemberID );
        if ( pMemberPlayer != NULL )
        {
            //通知该队员离开队伍
            MsgExitTeam xExitTeamMsg;
			xExitTeamMsg.header.stID = pMemberPlayer->GetID();
            GettheServer().SendMsgToSingle( &xExitTeamMsg, pMemberPlayer );

            pMemberPlayer->SetTeamID( TeamDefine::NoneSessionID );
            pMemberPlayer->TellTeamInfoChange( ETP_None );

            ClearTeamBuffer( pMemberPlayer );
        }

        //通知其他玩家
        MsgDeleteTeamMember xMsg;
        xMsg.dwMemberID = dwMemberID;
        SendMessageToTeamClient( &xMsg, dwMemberID, TeamDefine::NotSendToCenter );

        if ( dwMemberID != GetTeamHeaderID() )      // 不是队长的时候直接更新Buffer, 如果是队长在 ProcessUpgradeTeamHeader 更新
        {
            UpdateTeamBuffer( dwMemberID, true );     // 这个时候还没有删除该队员,所以更新队伍Buffer的时候, 该玩家不能计算在内
        }
    }
    // 这个函数会在调用离开队伍前
}

template<>
bool GameTeam::ProcessUpgradeTeamHeader( GameTeamMember* pTeamMember )
{
    RunTeamUpdate( TeamDefine::NotSendToCenter );

    // 更新小队Buffer
    UpdateTeamBuffer();

    return true;
}

template<>
GamePlayer* GameTeam::GetMemberPlayer( unsigned int dwMemberID, bool bIncludeNotInStage )
{
    GamePlayer* pGamePlayer = theRunTimeData.GetGamePlayerByDBID( dwMemberID );
    if ( pGamePlayer == NULL )
    { return NULL; }

    if ( bIncludeNotInStage )
    { // 包括非正常状态,还没有进场景
        return pGamePlayer;
    }

    if ( pGamePlayer->GetStatus() < CS_IDLE || pGamePlayer->GetStatus() > CS_ONSHIP )
    { return NULL; }

    return pGamePlayer;
}

template<>
int GameTeam::RunTeamUpdate( unsigned char chOperate )
{
    //把队员信息下发给客户端
    for ( MemberListIter iter = m_listTeamMember.begin(); iter != m_listTeamMember.end(); ++iter )
    {
        GamePlayer* pMemberPlayer = GetMemberPlayer( iter->GetID() );
        if( pMemberPlayer == NULL ) 
        { continue; }   //不在本服的不发送

        // 更新队伍中的信息
        iter->SetTimeOut( 0 );
        iter->SetHP( pMemberPlayer->GetHP() );
        iter->SetMP( pMemberPlayer->GetMP() );
        iter->SetHPMax( pMemberPlayer->GetCharFightAttr()->hpMax.final );
        iter->SetMPMax( pMemberPlayer->GetCharFightAttr()->mpMax.final );
        iter->SetLevel( pMemberPlayer->GetLevel() );
        
        Msg_Team_PlayerInfo xInfo;
        xInfo.header.stID   = pMemberPlayer->GetID();
        xInfo.dwDataBaseId  = iter->GetID();
        xInfo.bHeader       = IsTeamHeader( iter->GetID() );
        xInfo.nHp           = pMemberPlayer->GetHP();
        xInfo.nMp           = pMemberPlayer->GetMP();
        xInfo.nHpMax        = pMemberPlayer->GetCharFightAttr()->hpMax.final;
        xInfo.nMpMax        = pMemberPlayer->GetCharFightAttr()->mpMax.final;
        xInfo.Profession    = pMemberPlayer->GetProfession();
        xInfo.stLvl         = pMemberPlayer->GetLevel();
        xInfo.dwMapID       = pMemberPlayer->GetMapID();          //客户端使用的是mapconfig中的地图id
        xInfo.x             = pMemberPlayer->GetTileX();
        xInfo.y             = pMemberPlayer->GetTileY();
        xInfo.fx            = pMemberPlayer->GetFloatX();
        xInfo.fy            = pMemberPlayer->GetFloatY();
        xInfo.stManiple     = iter->GetManipleID();
        xInfo.bHeader2      = iter->GetManipleHeader();
		xInfo.AssignMode	= GetTeamAssignModeType();

        SendMessageToTeamClient( &xInfo, TeamDefine::ErrorID, chOperate );    // 自己也要更新
    }

    UpdateTeamFriendly();       // 更新队伍好友度
    
    return TeamDefine::DoNothing;
}

template<>
void GameTeam::UpdateTeamFriendly()
{
    if ( theRelationConfig.GetUpdateFriendlyValue() == 0 )
    { return; }

    unsigned int dwCurrentTime = HQ_TimeGetTime();
    if ( !GameTime::IsPassCurrentTime( dwCurrentTime, m_dwLastUpdateFrienlyTime, theRelationConfig.GetUpdateFriendlyTimeSpan() ) )
    { return; }

    // 更新每个好友的好友度
    bool bFriendlyChange = false;
    for ( MemberListIter iter = m_listTeamMember.begin(); iter != m_listTeamMember.end(); ++iter )
    {
        GamePlayer* pMemberPlayer = GetMemberPlayer( iter->GetID() );
        if ( pMemberPlayer == NULL )
        { continue; }

        if ( UpdateTeamFriendly( pMemberPlayer, theRelationConfig.GetUpdateFriendlyValue() ) )
        { bFriendlyChange = true; }
    }

    m_dwLastUpdateFrienlyTime = dwCurrentTime;

    if ( bFriendlyChange )
    {
        UpdateTeamBuffer();
    }
}

template<>
bool GameTeam::UpdateTeamFriendly( GamePlayer* pMemberPlayer, unsigned int nFriendly )
{
    if ( pMemberPlayer == NULL || nFriendly == 0 )
    { return false; }

    GameRelation* pRelation = pMemberPlayer->GetRelation();
    if ( pRelation == NULL )
    { return false; }

    bool bFriendlyChange = false;
    for ( MemberListIter iter = m_listTeamMember.begin(); iter != m_listTeamMember.end(); ++iter )
    {
        if ( iter->GetID() == pMemberPlayer->GetDBCharacterID() )
        { continue; }

        GamePlayer* pPlayer = GetMemberPlayer( iter->GetID() );
        if ( pPlayer == NULL || !pPlayer->IsInMapArea( pMemberPlayer->GetMapID(), pMemberPlayer->GetFloatX(), pMemberPlayer->GetFloatY(), TEAM_EXP_DIS ) )
        { continue; }   // 不在范围内

        if ( !pRelation->HaveRelation( iter->GetID(), RelationDefine::Friend ) )
        { continue; }

        pMemberPlayer->UpdateFriendly( iter->GetID(), RelationDefine::UpdateAddFriendly, nFriendly );
        bFriendlyChange = true;
    }

   return bFriendlyChange;
}

template<>
void GameTeam::MemberOutLine( GameTeamMember* pTeamMember )
{
    if ( pTeamMember == NULL )
    { return; }

    pTeamMember->SetTimeOut( HQ_TimeGetTime() );

    // 更新给客户端
    MsgTeamOutLine xOutLine;
    xOutLine.dwID = pTeamMember->GetID();
    SendMessageToTeamClient( &xOutLine, pTeamMember->GetID(), TeamDefine::NotSendToCenter );

    // 队长掉线, 在更新队长信息中处理队伍Buffer
    if ( pTeamMember->GetID() != GetTeamHeaderID() )
    {
        UpdateTeamBuffer(); 
    }
}

template<>
void GameTeam::MemberOnLine( GameTeamMember* pTeamMember )
{
    if ( pTeamMember == NULL )
    { return; }

    pTeamMember->SetTimeOut( 0 );

    // 更新小队Buffer
    UpdateTeamBuffer();

    GamePlayer* pMemberPlayer = GetMemberPlayer( pTeamMember->GetID() );
    if ( pMemberPlayer == NULL )
    { return; }

    for ( MemberListIter iter = m_listTeamMember.begin(); iter != m_listTeamMember.end(); ++iter )
    {
        MsgAddTeamMember xAddTeam;

        HelperFunc::SafeNCpy( xAddTeam.szName, iter->GetName(), sizeof( xAddTeam.szName ) );
        xAddTeam.bIsNewAdd  = false;
        xAddTeam.dwMemberID = iter->GetID();
        xAddTeam.nHp        = iter->GetHP();
        xAddTeam.nHpMax     = iter->GetHPMax();
        xAddTeam.nMp        = iter->GetMP();
        xAddTeam.nMpMax     = iter->GetMPMax();
        xAddTeam.stLvl      = iter->GetLevel();
        xAddTeam.Profession = iter->GetProfession();
        xAddTeam.shSex      = iter->GetSex();
        xAddTeam.bHeader    = IsTeamHeader( iter->GetID() );
        xAddTeam.bHeader2   = iter->GetManipleHeader();
        xAddTeam.dwGroupId  = GetID();
        xAddTeam.bOnline    = ( iter->GetTimeOut() == 0 ); //== 0 说明在线
        xAddTeam.nFaceId    = iter->GetFaceID();
        xAddTeam.nHairId    = iter->GetHairID();
        xAddTeam.nHeadPicId = iter->GetHeadPicID();

        GettheServer().SendMsgToSingle( &xAddTeam, pMemberPlayer );
    }
}

template<>
void GameTeam::SendMessageToTeamClient( Msg* pMessage, unsigned int nExceptID, unsigned char chOperate )
{
    if ( pMessage == NULL )
    { return; }

    bool bSomeOneInAnotherServer = false;       //在其他服务器 
    for ( MemberListIter iter = m_listTeamMember.begin(); iter != m_listTeamMember.end(); ++iter )
    {
        if ( iter->GetID() != nExceptID )
        {
            GamePlayer *pMemberPlayer = GetMemberPlayer( iter->GetID() );
            if ( pMemberPlayer == NULL )
            {
                bSomeOneInAnotherServer = true;                                
                continue;
            }

            GettheServer().SendMsgToSingle( pMessage, pMemberPlayer );
        }
    }

    //新加入队员,有在别的服务器上的,就发消息给CenterServer
    if ( chOperate == TeamDefine::SendToCenter && bSomeOneInAnotherServer )  
    {
        switch( pMessage->GetType() )
        {
        case MSG_CHAT:
            {
                S2STransmit::STeam xTeam;
                xTeam.dwSessionID = GetID();
                GettheServer().SendMsgToTeamRemote( pMessage, xTeam );
            }
            break;
        case MSG_TEAM_PLAYERINFO:
            {
                UpdateTeamMemberInfo( pMessage );
            }
            break;
        }
    }
}

template<>
void GameTeam::UpdateTeamMemberInfo( Msg* pMessage )
{
    Msg_Team_PlayerInfo* pTeamPlayInfo = static_cast< Msg_Team_PlayerInfo* >( pMessage );
    if ( pTeamPlayInfo == NULL )
    { return; }

    GS2CSPlayerUpdateTeamMemberInfo xMemberInfo;
    xMemberInfo.dwSessionId    = GetID();
    xMemberInfo.dwDataBaseId   = pTeamPlayInfo->dwDataBaseId;
    xMemberInfo.nHp            = pTeamPlayInfo->nHp;
    xMemberInfo.nHpMax         = pTeamPlayInfo->nHpMax;
    xMemberInfo.nMp            = pTeamPlayInfo->nMp;
    xMemberInfo.nMpMax         = pTeamPlayInfo->nMpMax;
    xMemberInfo.Profession     = pTeamPlayInfo->Profession;
    xMemberInfo.stLevel        = pTeamPlayInfo->stLvl;
    xMemberInfo.dwMapID        = pTeamPlayInfo->dwMapID;
    xMemberInfo.x              = pTeamPlayInfo->x;
    xMemberInfo.y              = pTeamPlayInfo->y;
    xMemberInfo.fx             = pTeamPlayInfo->fx;
    xMemberInfo.fy             = pTeamPlayInfo->fy;
    xMemberInfo.stManiple      = pTeamPlayInfo->stManiple;
    xMemberInfo.bManipleHeader = pTeamPlayInfo->bHeader2;
    xMemberInfo.bTeamHeader    = pTeamPlayInfo->bHeader;
    GamePlayer* pTeamPlayer = GetMemberPlayer( pTeamPlayInfo->dwDataBaseId );
    if ( pTeamPlayer != NULL )
    {
        xMemberInfo.stSex   = pTeamPlayer->GetSex();
        xMemberInfo.nFaceID = pTeamPlayer->GetFaceID();
        xMemberInfo.nHairID = pTeamPlayer->GetHairID();
        xMemberInfo.nHeadPicId = pTeamPlayer->GetHeadPic();
        strncpy_s( xMemberInfo.szName, sizeof( xMemberInfo.szName ), pTeamPlayer->GetCharName(), sizeof( xMemberInfo.szName ) - 1 );
    }

    GettheServer().SendMsgToCenterServer( &xMemberInfo );
}

template<>
unsigned int GameTeam::GetTeamMemberNotHaveQuest( int nQuestID )
{
    for ( MemberListIter iter = m_listTeamMember.begin(); iter != m_listTeamMember.end(); ++iter )
    {
        GamePlayer* pMemberPlayer = GetMemberPlayer( iter->GetID() );
        if ( pMemberPlayer == NULL || !pMemberPlayer->IsQuestActive( nQuestID ) )
        {
            return iter->GetID();
        }
    }

    return TeamDefine::ErrorID;
}

template<>
bool GameTeam::IsAllTeamMemberGreaterLevel( int nLevel )
{
    for ( MemberListIter iter = m_listTeamMember.begin(); iter != m_listTeamMember.end(); ++iter )
    {
        GamePlayer* pMemberPlayer = GetMemberPlayer( iter->GetID() );
        if ( pMemberPlayer == NULL || pMemberPlayer->GetLevel() < nLevel )
        { return false; }
    }

    return true;
}

template<>
void GameTeam::GetTeamMemberInMapArea( unsigned int nMapID, float fX, float fY, std::vector< unsigned int >& vecTeamMemberID )
{
    vecTeamMemberID.clear();
    for ( MemberListIter iter = m_listTeamMember.begin(); iter != m_listTeamMember.end(); ++iter )
    {
        GamePlayer* pMemberPlayer = GetMemberPlayer( iter->GetID() );
        if ( pMemberPlayer == NULL || pMemberPlayer->GetMapID() != nMapID )
        { continue; }

        float x = fX - pMemberPlayer->GetFloatX();
        float y = fY - pMemberPlayer->GetFloatY();
        float fDistanceD = x * x + y * y;

        if ( fDistanceD <= TEAM_EXP_DIS * TEAM_EXP_DIS)
        {
            vecTeamMemberID.push_back( iter->GetID() );
        }            
    }
};

template<>
unsigned int GameTeam::GetTeamMemberCountInMap( unsigned int nMapID, float fX, float fY )
{
    unsigned int nCount = 0;
    for ( MemberListIter iter = m_listTeamMember.begin(); iter != m_listTeamMember.end(); ++iter )
    {
        GamePlayer* pMemberPlayer = GetMemberPlayer( iter->GetID() );
        if ( pMemberPlayer == NULL || pMemberPlayer->GetMapID() != nMapID )
        { continue; }

        float x = fX - pMemberPlayer->GetFloatX();
        float y = fY - pMemberPlayer->GetFloatY();
        float fDistanceD = x * x + y * y ;

        if ( fDistanceD <= TEAM_EXP_DIS * TEAM_EXP_DIS)
        { ++nCount; }            
    }

    return nCount;
}

template<>
unsigned int GameTeam::GetTeamMemberLevelDistance( unsigned int nMapID, float fX, float fY, int& nMinLevel, int& nMaxLevel )
{
    nMinLevel = 10000;
    nMaxLevel = 0;

    unsigned int nTotalLevel = 0;
    for ( MemberListIter iter = m_listTeamMember.begin(); iter != m_listTeamMember.end(); ++iter )
    {
        GamePlayer* pMemberPlayer = GetMemberPlayer( iter->GetID() );
        if ( pMemberPlayer == NULL || !pMemberPlayer->IsInMapArea( nMapID, fX, fY, TEAM_EXP_DIS ) )
        { continue; }

        if ( pMemberPlayer->GetLevel() > nMaxLevel )
        { nMaxLevel = pMemberPlayer->GetLevel(); }

        if ( pMemberPlayer->GetLevel() < nMinLevel )
        { nMinLevel = pMemberPlayer->GetLevel(); }

        nTotalLevel += pMemberPlayer->GetLevel();
    }

    return nTotalLevel;
}

template<>
float GameTeam::GetTeamExpPercent( unsigned int nTeamCount, bool bIsEcType )
{
    const static float fExpPercent[][ TeamMaxManipleMember ] = 
    {
        { 1.0f, 0.8f, 0.7f, 0.6f, 0.6f, /*0.6f,*/ },        // 普通地图经验比率
        { 1.0f, 0.8f/*1.2f*/, 0.7f/*1.4f*/, 0.6f/*1.6f*/, 0.6f/*1.8f*/, /*2.0f,*/ },        // 副本地图经验比率
    };

    if (nTeamCount == 0)
        nTeamCount = 1;
    if (nTeamCount > TeamMaxManipleMember)
        nTeamCount = TeamMaxManipleMember;

    return fExpPercent[ bIsEcType ][ nTeamCount - 1 ];
}

template<>
bool GameTeam::CallAllTeamPlayerFlyToMapReq( unsigned int nMapID, float fX, float fY, float fDir /* = 0.0f */ )
{
    for ( MemberListIter iter = m_listTeamMember.begin(); iter != m_listTeamMember.end(); ++iter )
    {
        GamePlayer* pMemberPlayer = GetMemberPlayer( iter->GetID() );
        if ( pMemberPlayer == NULL )
        { continue; }

        pMemberPlayer->FlyToMapReq( nMapID, fX, fY, fDir );
    }

    return true;
}

//template<>
//bool GameTeam::TeamChangeStage( GameStage* pGameStage, int nTileX, int nTileY, float dir )
//{
//    for ( MemberListIter iter = m_listTeamMember.begin(); iter != m_listTeamMember.end(); ++iter )
//    {
//        GamePlayer* pMemberPlayer = GetMemberPlayer( iter->GetID() );
//        if ( pMemberPlayer == NULL )
//        { continue; }
//     
//        pMemberPlayer->ChangeToMap( pGameStage, nTileX, nTileY, dir, __FILE__, __LINE__ );
//    }
//
//    return true;
//}

template<>
unsigned long GameTeam::IsTeamExpired( int nVarId, int keyHour, int keyMinute, int minDuration )
{
    for ( MemberListIter iter = m_listTeamMember.begin(); iter != m_listTeamMember.end(); ++iter )
    {
        GamePlayer* pTeamPlayer = GetMemberPlayer( iter->GetID() );
        if ( pTeamPlayer == NULL )
        { return iter->GetID(); }

        if ( !pTeamPlayer->IsExpired( nVarId, keyHour, keyMinute, minDuration ) )
        {
            return iter->GetID();
        }
    }

    return TeamDefine::ErrorID;
}

template<>
bool GameTeam::RecordTeamTime( int nVarId )
{
    bool bSuccess = true;
    for ( MemberListIter iter = m_listTeamMember.begin(); iter != m_listTeamMember.end(); ++iter )
    {
        GamePlayer* pTeamPlayer = GetMemberPlayer( iter->GetID() );
        if ( pTeamPlayer == NULL )
        { return false; }

        if ( !pTeamPlayer->RecordTimeVar( nVarId ) )
        {
            bSuccess = false;
        }
    }

    return bSuccess;
}

template<>
void GameTeam::ClearTeamExpiredVar( int nVarId, int keyHour, int keyMinute, int minDuration, int nClearVarId )
{
    for ( MemberListIter iter = m_listTeamMember.begin(); iter != m_listTeamMember.end(); ++iter )
    {
        GamePlayer* pTeamPlayer = GetMemberPlayer( iter->GetID() );
        if ( pTeamPlayer == NULL )
        { continue; }

        if ( pTeamPlayer->IsExpired( nVarId, keyHour, keyMinute, minDuration ) )
        {
            pTeamPlayer->SetVar( nClearVarId, 0 );
        }
    }
}

template<>
unsigned long GameTeam::IsTeamTimeVarPassOneDay( int nVarID )
{
    for ( MemberListIter iter = m_listTeamMember.begin(); iter != m_listTeamMember.end(); ++iter )
    {
        GamePlayer* pTeamPlayer = GetMemberPlayer( iter->GetID() );
        if ( pTeamPlayer == NULL )
        { return iter->GetID(); }

        if ( !pTeamPlayer->IsTimeVarPassOneDay( nVarID ) )
        { return iter->GetID(); }
    }

    return TeamDefine::ErrorID;
}

template<>
void GameTeam::RecordNowTeamTimeVar( int nVarID )
{
    for ( MemberListIter iter = m_listTeamMember.begin(); iter != m_listTeamMember.end(); ++iter )
    {
        GamePlayer* pTeamPlayer = GetMemberPlayer( iter->GetID() );
        if ( pTeamPlayer == NULL )
        { continue; }

        pTeamPlayer->RecordNowTimeVar( nVarID );
    }
}

template<>
void GameTeam::ClearTeamTimeVar( int nVarID, int nClearVarID )
{
    for ( MemberListIter iter = m_listTeamMember.begin(); iter != m_listTeamMember.end(); ++iter )
    {
        GamePlayer* pTeamPlayer = GetMemberPlayer( iter->GetID() );
        if ( pTeamPlayer == NULL )
        { continue; }

        if ( pTeamPlayer->IsTimeVarPassOneDay( nVarID ) )
        { pTeamPlayer->SetVar( nClearVarID, 0 ); }
    }
}

template<>
unsigned char GameTeam::GetHeaderFriendCount( unsigned int dwExceptMemberID /*= TeamDefine::ErrorID */ )
{
    unsigned char uchCount = 0;
    GameRelation* pHeaderRelation = theGameRelationManager.GetPlayerRelation( GetTeamHeaderID() );
    if ( pHeaderRelation == NULL )
    { return uchCount; }

    GamePlayer* pHeader = GetMemberPlayer( GetTeamHeaderID() );
    if ( pHeader == NULL )
    { return uchCount; }

    // 得到队伍中, 队长的好友个数
    for ( MemberListIter iter = m_listTeamMember.begin(); iter != m_listTeamMember.end(); ++iter )
    {
        if ( iter->GetID() == GetTeamHeaderID() || iter->GetID() == dwExceptMemberID )
        { continue; }

        GamePlayer* pPlayer = GetMemberPlayer( iter->GetID() );
        if ( pPlayer == NULL || pHeader->GetMapID() != pPlayer->GetMapID() || pPlayer->IsDead())
        { continue; }   // 不在相同的地图不计算个数

        if ( pHeaderRelation->HaveRelation( iter->GetID(), RelationDefine::Friend ) )
        {
            ++uchCount;
        }
    }

    return uchCount;
}

template<>
void GameTeam::UpdateTeamBuffer( unsigned int dwExceptMemberID /*= TeamDefine::ErrorID */, bool bLeaveTeam /*= false*/)
{
    // 得到队伍中, 队长的好友个数
    unsigned char uchCount = GetHeaderFriendCount( dwExceptMemberID );
    for ( MemberListIter iter = m_listTeamMember.begin(); iter != m_listTeamMember.end(); ++iter )
    {
        TeamMemberType& member = *iter; 
        // dwExceptMemberID 不要计算
        if ( member.GetID() == dwExceptMemberID && bLeaveTeam )
        { continue; }

        UpdateTeamBuffer( &( *iter ), uchCount, dwExceptMemberID );
    }
}

template<>
void GameTeam::UpdateTeamBuffer( GameTeamMember* pMember, unsigned char uchCount, unsigned int dwExceptMemberID )
{
    if ( pMember == NULL )
    { return; }

    GamePlayer* pPlayer = GetMemberPlayer( pMember->GetID() );  // 这里不能先return, 否则队伍中的Buffer状态不能清除掉

    bool bChangeSuccess = false;

	bool bHasGuildBuffer = false;
	if ( pPlayer != NULL && !pPlayer->IsDead())
	{
		const TeamBuffer* pGuildBuffer = NULL;

		if ( IsTeamHeader( pMember->GetID() ) ) // 如果是队长
		{
			for ( MemberListIter iter = m_listTeamMember.begin(); iter != m_listTeamMember.end(); ++iter )
			{
				if ( pMember->GetID() == iter->GetID() || iter->GetID() == dwExceptMemberID )
				{ continue; }

				GamePlayer* pMemberPlayer = GetMemberPlayer( iter->GetID() );
				if ( pMemberPlayer == NULL || pMemberPlayer->GetMapID() != pPlayer->GetMapID() || pMemberPlayer->IsDead())
				{ continue; }

				if ( pMemberPlayer->GetGuildID() == pPlayer->GetGuildID() && pPlayer->GetGuildID() != GuildDefine::InitID )
				{
					GameGuild * pGuild = theGameGuildManager.GetGuild(pPlayer->GetGuildID());
					if ( pGuild != NULL )
					{
						pGuildBuffer = theRelationConfig.GetGuildBuffer( pGuild->GetLevel(), pPlayer->GetProfession() );
						if ( pGuildBuffer )
						{
							bHasGuildBuffer = true;
							break;
						}
					}
				}
			}
		}
		else
		{
			GamePlayer* pHeaderPlayer = GetMemberPlayer( GetTeamHeaderID() );
			if ( pHeaderPlayer != NULL && pHeaderPlayer->GetMapID() == pPlayer->GetMapID() && !pHeaderPlayer->IsDead())     // 要在同一地图才行
			{
				if ( pHeaderPlayer->GetGuildID() == pPlayer->GetGuildID() && pPlayer->GetGuildID() != GuildDefine::InitID )
				{
					GameGuild * pGuild = theGameGuildManager.GetGuild(pPlayer->GetGuildID());
					if ( pGuild != NULL )
					{
						pGuildBuffer = theRelationConfig.GetGuildBuffer( pGuild->GetLevel(), pPlayer->GetProfession() );
						if ( pGuildBuffer )
							bHasGuildBuffer = true;
					}
				}
			}
		}

		if ( UpdateTeamBuffer( pMember, pPlayer, TeamDefine::Buffer_Guild, pGuildBuffer ) )
			bChangeSuccess = true;  
	}

    if ( uchCount != TeamMaxManipleMember && !bHasGuildBuffer )     // 如果 数量 = TeamMaxManipleMember, 不判断队伍队伍Buffer
    {
        const TeamBuffer* pTeamBuffer = NULL;
        GamePlayer* pHeaderPlayer = GetMemberPlayer( GetTeamHeaderID() );
        if ( pHeaderPlayer != NULL && pPlayer != NULL && pHeaderPlayer->GetMapID() == pPlayer->GetMapID() && !pHeaderPlayer->IsDead())     // 要在同一地图才行
        { 
            // 按照队长的职业来添加Buffer
            pTeamBuffer = theRelationConfig.GetTeamBuffer( uchCount, pHeaderPlayer->GetProfession() );
        }

        if ( UpdateTeamBuffer( pMember, pPlayer, TeamDefine::Buffer_Team, pTeamBuffer ) )
        { bChangeSuccess = true; }   
    }

    // 单独与队长是好友 附加Buffer
    const TeamBuffer* pFriendBuffer = NULL;
    if ( pPlayer != NULL && !pPlayer->IsDead())
    {
        if ( IsTeamHeader( pMember->GetID() ) ) // 如果是队长
        {
            GameRelation* pRelation = pPlayer->GetRelation();
            if ( pRelation != NULL )
            {
                unsigned int nFriendly = 0;    // 算出最高好友度
                for ( MemberListIter iter = m_listTeamMember.begin(); iter != m_listTeamMember.end(); ++iter )
                {
                    if ( pMember->GetID() == iter->GetID() || iter->GetID() == dwExceptMemberID )
                    { continue; }

                    GamePlayer* pMemberPlayer = GetMemberPlayer( iter->GetID() );
                    if ( pMemberPlayer == NULL || pMemberPlayer->GetMapID() != pPlayer->GetMapID() || pMemberPlayer->IsDead())
                    { continue; }

                    RelationDataToServer* pData = pRelation->GetRelationData( iter->GetID() );
                    if ( pData == NULL || !pData->HaveRelation( RelationDefine::Friend ) )
                    { continue; }   // 不是好友

                    if ( pData->GetFriendly() > nFriendly )
                    { nFriendly = pData->GetFriendly(); }
                }

                if ( nFriendly != 0 )
                {
                    unsigned char uchFriendLevel = theRelationConfig.GetFriendLevel( nFriendly );
                    pFriendBuffer = theRelationConfig.GetFriendBuffer( uchFriendLevel, pMember->GetProfession() );
                }
            }
        }
        else        // 是队员
        {
            GamePlayer* pHeaderPlayer = GetMemberPlayer( GetTeamHeaderID() );
            if ( pHeaderPlayer != NULL && pHeaderPlayer->GetMapID() == pPlayer->GetMapID() && !pHeaderPlayer->IsDead())     // 要在同一地图才行
            {
                GameRelation* pRelation = pPlayer->GetRelation();
                if ( pRelation != NULL )
                {
                    RelationDataToServer* pData = pRelation->GetRelationData( GetTeamHeaderID() );
                    if ( pData != NULL && pData->HaveRelation( RelationDefine::Friend ) && pData->GetFriendly() > 0 )
                    {
                        unsigned char uchFriendLevel = theRelationConfig.GetFriendLevel( pData->GetFriendly() );
                        pFriendBuffer = theRelationConfig.GetFriendBuffer( uchFriendLevel, pMember->GetProfession() );
                    }
                }
            }
        }
    }

    if ( UpdateTeamBuffer( pMember, pPlayer, TeamDefine::Buffer_Friend, pFriendBuffer ) )
    { bChangeSuccess = true; }   

    // 添加成功, 更新给客户端
    if ( bChangeSuccess && pPlayer != NULL )      
    { pPlayer->OnBuffStatusChanged( true ); }
}

template<>
bool GameTeam::UpdateTeamBuffer( GameTeamMember* pMember, GamePlayer* pPlayer, unsigned char uchType, const TeamBuffer* pTeamBuffer )
{
    if ( pMember == NULL )
    { return false; }

    TeamBuffer* pLastBuffer = pMember->GetTeamBuffer( uchType );
    if ( pLastBuffer == NULL )
    { return false; }

    bool bChangeSuccess = false;    
    if ( pTeamBuffer != NULL )      // 如果没有可添加的Buffer
    {
        // 不相同才添加buffer
        /*if ( pLastBuffer->GetBufferID() != pTeamBuffer->GetBufferID() || pLastBuffer->GetBufferLevel() != pTeamBuffer->GetBufferLevel() )
        {
            if ( pPlayer != NULL && pPlayer->ApplyBufferStatus( pTeamBuffer->GetBufferID(), pTeamBuffer->GetBufferLevel(), pPlayer->GetID(),SCharBuff::StatusEventType_Other, 0 ) == GLR_Success )
            { bChangeSuccess = true; }

            pMember->AddTeamBuffer( uchType, *pTeamBuffer );
        }*/
		//有BUFF 直接添加
		if ( pPlayer != NULL && pPlayer->ApplyBufferStatus( pTeamBuffer->GetBufferID(), pTeamBuffer->GetBufferLevel(), pPlayer->GetID(),SCharBuff::StatusEventType_Other, 0 ) == GLR_Success )
        { bChangeSuccess = true; }
		pMember->AddTeamBuffer( uchType, *pTeamBuffer );
    }
    else
    {
       /* if ( !pLastBuffer->IsEmpty() )
        {
            if ( pPlayer != NULL && pPlayer->_buffManager.ClearBuffByBuffIdLevel( pLastBuffer->GetBufferID(), pLastBuffer->GetBufferLevel() ) )
            { bChangeSuccess = true; }
            
            pLastBuffer->Clear();
        }*/
		if ( pPlayer != NULL && pPlayer->_buffManager.ClearBuffByBuffIdLevel( pLastBuffer->GetBufferID(), pLastBuffer->GetBufferLevel() ) )
		{ bChangeSuccess = true; }
	    
		pLastBuffer->Clear();
    }

    return bChangeSuccess;
}

template<>
void GameTeam::ClearTeamBuffer( GamePlayer* pMemberPlayer )
{
    if ( pMemberPlayer == NULL )
    { return; }

    bool bRemoveSuccess = false;
    for ( int i = 0; i < TeamDefine::Buffer_Max; ++i )
    {
        if ( ClearTeamBuffer( pMemberPlayer, i, TeamDefine::NotSendToClient ) )
        { bRemoveSuccess = true; }
    }

    if ( bRemoveSuccess )
    { pMemberPlayer->OnBuffStatusChanged( true ); }
}

template<>
bool GameTeam::ClearTeamBuffer( GamePlayer* pMemberPlayer, unsigned char uchBufferType, unsigned char uchSendMessage )
{
    if ( pMemberPlayer == NULL )
    { return false; }

    GameTeamMember* pTeamMember = GetTeamMemberByID( pMemberPlayer->GetDBCharacterID() );
    if ( pTeamMember == NULL )
    { return false; }

    TeamBuffer* pTeamBuffer = pTeamMember->GetTeamBuffer( uchBufferType );
    if ( pTeamBuffer == NULL )
    { return false; }

    if ( !pMemberPlayer->_buffManager.ClearBuffByBuffIdLevel( pTeamBuffer->GetBufferID(), pTeamBuffer->GetBufferLevel() ) )
    { return false; }

    pTeamBuffer->Clear();

    if ( uchSendMessage == TeamDefine::SendToClient )
    { pMemberPlayer->OnBuffStatusChanged( true ); }

    return true;
}

template<>
unsigned int GameTeam::GetMemberMinFriendly()
{
    GamePlayer* pHeader = GetMemberPlayer( GetTeamHeaderID() );
    if ( pHeader == NULL )
    { return 0; }

    GameRelation* pRelation = pHeader->GetRelation();
    if ( pRelation == NULL )
    { return 0; }

    std::vector< unsigned int > vecFriendly( 0 );
    for ( MemberListIter iter = m_listTeamMember.begin(); iter != m_listTeamMember.end(); ++iter )
    {
        if ( iter->GetID() == GetTeamHeaderID() )
        { continue; }

        GamePlayer* pMember = GetMemberPlayer( iter->GetID() );
        if ( pMember == NULL || pMember->GetMapID() != pHeader->GetMapID() )
        { return 0; }       // 必须在同一个地图

        RelationDataToServer* pData = pRelation->GetRelationData( iter->GetID() );
        if ( pData == NULL || !pData->HaveRelation( RelationDefine::Friend ) )
        { return 0; }       // 必须满足与所有队员都是好友

        vecFriendly.push_back( pData->GetFriendly() );
    }

    // 计算好友度方法是 取3个最大值求和除以3 求平均的
    static const int s_nCalcCount = 3;
    if ( vecFriendly.size() < s_nCalcCount )
    { return 0; }

    std::sort( vecFriendly.begin(), vecFriendly.end(), greater< unsigned int >() );
    __int64 n64Friendly = 0;
    for ( int i = 0; i < s_nCalcCount; ++i )
    {
        n64Friendly += vecFriendly[i];
    }

    return ( n64Friendly + s_nCalcCount - 1 ) / s_nCalcCount;
}

template<>
unsigned char GameTeam::CheckTeamSkillCanUse( GamePlayer* pPlayer, unsigned short ustSkillID, unsigned char uchSkillLevel )
{
    if ( pPlayer == NULL || ustSkillID == InvalidLogicNumber || uchSkillLevel == 0 || pPlayer->IsDead() )
    { return TeamDefine::SkillCanNotUse; }

    if ( !IsTeamFull() )    // 队伍必须要满
    { return TeamDefine::SkillCanNotUse; }

    if ( !IsTeamHeader( pPlayer->GetDBCharacterID() ) )
    { return TeamDefine::SkillCanNotUse; }      // 不是队长不能使用

    if ( !GameTime::IsPassCurrentTime( m_dwStartCoolDownTime, m_dwCoolDownTime ) )
    { return TeamDefine::SkillCoolDown; }       // cooldown时间还没到

    unsigned int nFriendly = GetMemberMinFriendly();
    if ( nFriendly == 0 )
    { return TeamDefine::SkillCanNotUse; }      // 都必须是要好友

    unsigned char uchFriendlyLevel = theRelationConfig.GetFriendLevel( nFriendly );

    const RelationConfig::TeamSkillVector* pTeamSkillVector = theRelationConfig.GetTeamSkill( uchFriendlyLevel, pPlayer->GetProfession() );
    if ( pTeamSkillVector == NULL)
    { return TeamDefine::SkillCanNotUse; }

    for ( RelationConfig::TeamSkillVectorConstIter iter = pTeamSkillVector->begin(); iter != pTeamSkillVector->end(); ++iter )
    {
        if ( iter->GetSkillID() != ustSkillID )
        { continue; }

        if ( iter->GetSkillLevel() >= uchSkillLevel )
        { return TeamDefine::SkillCanUse; }
    }
    
    return TeamDefine::SkillCanNotUse;
}

template<>
CDTIME GameTeam::StartTeamSkillCoolDown( unsigned short ustSkillID, unsigned char uchLevel, unsigned int dwCoolDownTime )
{
    CDTIME result( 0, 0 );

    SetStartCoolDownTime( HQ_TimeGetTime() );   // 设置队伍技能CD开始时间
    SetCoolDownTime( dwCoolDownTime );          // 设置队伍技能CD时间

    for ( MemberListIter iter = m_listTeamMember.begin(); iter != m_listTeamMember.end(); ++iter )
    {
        GamePlayer* pPlayer = GetMemberPlayer( iter->GetID() );
        if ( pPlayer == NULL )
        { continue; }

        CDTIME temp = pPlayer->StartSkillCoolDown( ustSkillID, uchLevel );
        if ( IsTeamHeader( iter->GetID() ) )
        { result = temp; }
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<>
void GameTeamManager::SendCreateTeamMessage( GameTeam* pTeam )
{
    // GameServer上这个函数什么也不干
}

template<>
void GameTeamManager::RunInviteRecordUpdate( unsigned int dwCurrentTime )
{
    // GameServer上这个函数什么也不干
}


template<> 
void GameTeamManager::SendOnLineMessage( unsigned int dwMemberID )
{
    GS2CSTeamOnLine xOnLine;
    xOnLine.dwID = dwMemberID;
    GettheServer().SendMsgToCenterServer( &xOnLine );
}

template<>
void GameTeamManager::UpdateTeamBuffer( unsigned int dwReqPlayerID, unsigned int dwAckPlayerID, bool bAllTeamUpdate, bool bAddRelation )
{
    GameTeam* pReqTeam = GetTeamByMemberID( dwReqPlayerID );
    if ( pReqTeam == NULL )
    { return; }
    GameTeam* pAckTeam = GetTeamByMemberID( dwAckPlayerID );
    if ( pAckTeam == NULL )
    { return; }

    if ( pReqTeam->GetID() != pAckTeam->GetID() )
    { return; }    // 不在同一个队伍

    if ( bAllTeamUpdate )       // 是更新所有队伍信息
    {
        if ( pReqTeam->IsTeamHeader( dwReqPlayerID ) || pReqTeam->IsTeamHeader( dwAckPlayerID ) )
        {
            if ( bAddRelation ) // 添加好友关系
            {
                pReqTeam->UpdateTeamBuffer();
            }
            else
            {
                // 删除好友关系
                if ( pReqTeam->IsTeamHeader( dwReqPlayerID ) )
                {
                    pReqTeam->UpdateTeamBuffer( dwAckPlayerID );
                }
                else
                {
                    pReqTeam->UpdateTeamBuffer( dwReqPlayerID );
                }
            }
        }
    }
    else
    {
        // 只更新指定队员的
        GameTeamMember* pMember = pReqTeam->GetTeamMemberByID( dwReqPlayerID );
        pReqTeam->UpdateTeamBuffer( pMember );
    }  
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////