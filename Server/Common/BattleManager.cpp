#include "BattleManager.h"
#include "GamePlayer.h"
#include "ShareData.h"
#include "MapConfig.h"
#include "MessageDefine.h"
#include "GameWorld.h"
#include "GlobalFunction.h"
#include "ScriptMgr.h"
#include "TeamManager.h"

template<>
GamePlayer* PlayerBattleData::GetUnit( unsigned int nID )
{
    return theRunTimeData.GetGamePlayerByDBID( nID );
}

template<>
void PlayerBattleData::CheckSignUpValid()
{
    bool bSendCountToClient = false;
    for ( UnitSetIter iter = setUnit.begin(); iter != setUnit.end(); )
    {
        GamePlayer* pPlayer = GetUnit( *iter );
        if ( pPlayer == NULL || GetWaitMapID() != EctypeId2MapId( pPlayer->GetMapID() )  )
        {
            iter = setUnit.erase( iter );
            bSendCountToClient = true;
        }
        else
        {
            ++iter;
        }
    }

    if ( bSendCountToClient )
    {
        SendUnitCountMessage();
    }
}

template<>
unsigned short PlayerBattleData::GetUnitLevel( unsigned int nID )
{
    if ( nID == BattleDefine::NoneUnitID )
    { return 0; }

    UnitSetIter iter = setUnit.find( nID );
    if ( iter == setUnit.end() )
    { return 0; }

    GamePlayer* pPlayer = GetUnit( nID );
    if ( pPlayer == NULL )
    { return 0; }

    return pPlayer->GetLevel();
}

template<>
void PlayerBattleData::StartEnterFightMap( unsigned int nCurrentTime )
{
    SetStatus( BattleDefine::Status_EndEnter );

    MapConfig::MapData* pFightMapData = theMapConfig.GetMapDataById( GetFightMapID() );
    if ( pFightMapData == NULL )
    { return; }
 
    MapConfig::TransportDestination* pFirstTransport  = pFightMapData->GetTransportDestinationByIndex( 0 );
    MapConfig::TransportDestination* pSecondTransport = pFightMapData->GetTransportDestinationByIndex( 1 );
    if ( pFirstTransport == NULL || pSecondTransport == NULL )
    { return; }

    // 1v1ս��, �漴ƥ����������ս��PK
    while( true )
    {
        if ( setUnit.empty() )
        { break; }

        UnitSetIter iter = setUnit.begin();
        GamePlayer* pFirstPlayer = GetUnit( *iter );
        if ( pFirstPlayer == NULL )      // ��һ�����
        {
            setUnit.erase( iter );
            continue;
        }

        int nSize = GetUnitCount();
        if ( nSize == 1 )
        { break; }  // ���ֻʣ��һ����

        // ����������
        setUnit.erase( iter );      // ɾ����
        GamePlayer* pSecondPlayer = NULL;
        while ( true )
        {
            nSize = GetUnitCount();
            if ( nSize == 0 )
            { break; }  // �Ѿ�û��ƥ��������

            int nIndex = rand() % nSize;
            iter = setUnit.begin();
            advance( iter, nIndex );

            pSecondPlayer = GetUnit( *iter );
            setUnit.erase( iter ); 

            if ( pSecondPlayer != NULL )
            { break; }  // �ҵ�ƥ������
        }

        if ( pSecondPlayer == NULL )
        {
            // û��ƥ������
            setUnit.insert( pFirstPlayer->GetDBCharacterID() );
            break;
        }

        // �ҵ��Ժ�, ��������, ׼�������ͼ
        unsigned long dwMapID = theGameWorld.GetEctypeMapID( GetFightMapID(), true );
        theGameWorld.MultiCreateStage( GetFightMapID(), dwMapID );
        
        // ��1�����
        pFirstPlayer->SetWaitChangeStage( GamePlayer::EnterStage, dwMapID, pFirstTransport->PositionX, pFirstTransport->PositionY, pFirstTransport->Direction, 60, false );

        // ��¼�������
        SaveSignUpInfo( pFirstPlayer );

        // ��2�����
        pSecondPlayer->SetWaitChangeStage( GamePlayer::EnterStage, dwMapID, pSecondTransport->PositionX, pSecondTransport->PositionY, pSecondTransport->Direction, 60, false );

        // ��¼�������
        SaveSignUpInfo( pSecondPlayer );
    }

    SendUnitCountMessage();
}

template<>
void PlayerBattleData::EndFight( unsigned int nCurrentTime )
{
    // ������ظ�����ս��, ������һ��
    if ( GetRepeatTurns() > 0 )
    {
        SetSignUpInfo( nCurrentTime );
    }
    else
    {
        SetStatus( BattleDefine::Status_Close );
    }
}

template<>
void PlayerBattleData::SendUnitCountMessage()
{
    MsgTellBattleSignUpCount xTell;
    
    xTell.uchType  = BattleDefine::PlayerType;
    xTell.ustMapID = GetWaitMapID();
    xTell.ustCount = GetUnitCount();
    if ( GetStatus() == BattleDefine::Status_SignUp )       // �����׶ΰ�ʣ��ʱ�䷢���ͻ���
    {
        xTell.nStartLeftTime = GameTime::GetLeftKeepTime( HQ_TimeGetTime(), GetStartSignUpTime(), GetSignUpTime() ) / 1000;
    }

    for ( UnitSetIter iter = setUnit.begin(); iter != setUnit.end(); ++iter )
    {
        GamePlayer* pPlayer = GetUnit( *iter );
        if ( pPlayer == NULL )
        { continue; }

        GettheServer().SendMsgToSingle( &xTell, pPlayer );
    }
}

template<>
bool PlayerBattleData::CheckCanSignUp( unsigned int nID )
{
    GamePlayer* pPlayer = GetUnit( nID );
    if ( pPlayer == NULL )
    { return false; }

    // ��������

    return true;
}

template<>
void PlayerBattleData::SaveSignUpInfo( GamePlayer* pPlayer )
{
    if ( pPlayer == NULL )
    { return; }
    
    GetScriptMgr()->StartupVM( ST_CHALLENGE, 0, pPlayer );      // ���ýű�, �ɽű��������Щʲô
}

template<>
void PlayerBattleData::EnterWaitMap( unsigned int nID )
{
    GamePlayer* pPlayer = GetUnit( nID );
    if ( pPlayer == NULL )
    { return; }

    MapConfig::MapData* pMapData = theMapConfig.GetMapDataById( GetWaitMapID() );
    if ( pMapData == NULL )
    { return; }

    // ˵��һ��, ��Ϊ����֪��������Ϣ, �������ͼ�ֲ�������, �����ò߻����0��������Ϊ�����ͼ�Ĵ��͵�
    MapConfig::RelivePosition* pRelive = pMapData->GetRelivePositionByState( true );
    if ( pRelive == NULL )
    { return; }

    pPlayer->FlyToMapReq( GetWaitMapID(),  pRelive->PositionX, pRelive->PositionY, pRelive->Direction );
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////
template<>
GameTeam* TeamBattleData::GetUnit( unsigned int nID )
{
    return theGameTeamManager.GetTeam( nID );
}

template<>
bool TeamBattleData::CheckCanSignUp( unsigned int nID )
{
    //GameTeam* pTeam = GetUnit( nID );
    //if ( pTeam == NULL )
    //{ return false; }

    // ��������

    return true;
}

template<>
void TeamBattleData::CheckSignUpValid()
{
    bool bSendCountToClient = false;
    for ( UnitSetIter iter = setUnit.begin(); iter != setUnit.end(); )
    {
        GameTeam* pTeam = GetUnit( *iter );
        if ( pTeam == NULL )
        {
            iter = setUnit.erase( iter );
            bSendCountToClient = true;
        }
        else
        {
            // �ж��Ƿ��ڱ�������, ��������, ɾ������
            bool bNeedDelete = true;
            for ( int i = 0; i < pTeam->TeamMemberCount(); ++i )
            {
                GameTeamMember* pMember = pTeam->GetTeamMemberByIndex( i );
                if ( pMember == NULL )
                { continue; }

                GamePlayer* pPlayer = pTeam->GetMemberPlayer( pMember->GetID() );
                if ( pPlayer == NULL )
                { continue; }       

                bNeedDelete = false;
                break;
            }

            if ( bNeedDelete )
            {
                iter = setUnit.erase( iter );
                bSendCountToClient = true;
            }
            else
            {
                ++iter;
            }
        }
    }

    if ( bSendCountToClient )
    {
        SendUnitCountMessage();
    }
}

template<>
void TeamBattleData::SendWaitNextBattleMessage()
{
    if ( setUnit.empty() )
    { return; }

    MsgAckResult xAck;
    xAck.result = ER_WaitNextTeamBattle;
    xAck.value  = 3;

    for ( UnitSetIter iter = setUnit.begin(); iter != setUnit.end(); ++iter )
    {
        GameTeam* pTeam = GetUnit( *iter );
        if ( pTeam == NULL )
        { continue; }

        pTeam->SendMessageToTeamClient( &xAck, TeamDefine::ErrorID, TeamDefine::NotSendToCenter );
    }
}

template<>
void TeamBattleData::SendUnitCountMessage()
{
    //MsgTellBattleSignUpCount xTell;

    //xTell.uchType  = BattleDefine::TeamType;
    //xTell.ustMapID = GetFightMapID();
    //xTell.ustCount = GetUnitCount();
    //if ( GetStatus() == BattleDefine::Status_SignUp )       // �����׶ΰ�ʣ��ʱ�䷢���ͻ���
    //{
    //    xTell.nStartLeftTime = ( GetStartSignUpTime() + GetSignUpTime() - HQ_TimeGetTime() ) / 1000;
    //}

    //for ( UnitSetIter iter = setUnit.begin(); iter != setUnit.end(); ++iter )
    //{
    //    GameTeam* pTeam = GetUnit( *iter );
    //    if ( pTeam == NULL )
    //    { continue; }

    //    pTeam->SendMessageToTeamClient( &xTell, TeamDefine::ErrorID, TeamDefine::NotSendToCenter );
    //}
}

template<>
void TeamBattleData::StartEnterFightMap( unsigned int nCurrentTime )
{
    SetStatus( BattleDefine::Status_EndEnter );

    // ���ս����¼
    mapBattleRecord.clear();
    mapKillInfo.clear();

    MapConfig::MapData* pMapData = theMapConfig.GetMapDataById( GetFightMapID() );
    if ( pMapData == NULL )
    { return; }

    while ( true )      // �������ս���߼�
    {
        if ( GetUnitCount() < 3 )
        { break; }

        unsigned long dwMapID = theGameWorld.GetEctypeMapID( GetFightMapID(), true );
        GameStage* pStage = theGameWorld.SingleCreateStage( GetFightMapID(), dwMapID );
        if ( pStage == NULL )
        { continue; }

        for ( int i = 0; i < 6; ++i )           // ÿ����ͼ�����������6������
        {
            int nSize = GetUnitCount();
            if ( nSize == 0 )
            { break; }  // �Ѿ�û��ƥ��������

            int nIndex = rand() % nSize;
            UnitSetIter iter = setUnit.begin();
            advance( iter, nIndex );

            GameTeam* pTeam = GetUnit( *iter );
            if ( pTeam != NULL )
            {
                MapConfig::RelivePosition* pRelive = pMapData->GetRelivePositionByIndex( i + 2 );
                if ( pRelive == NULL )
                { return; }

                BattleDefine::BattleRecord xRecord;
                xRecord.SetTeamID( *iter );
                xRecord.SetReliveIndex( i + 2 );
                AddBattleRecord( dwMapID, *iter, xRecord );

                for ( int i = 0; i < pTeam->TeamMemberCount(); ++i )
                {
                    GameTeamMember* pMember = pTeam->GetTeamMemberByIndex( i );
                    if ( pMember == NULL )
                    { continue; }

                    GamePlayer* pPlayer = pTeam->GetMemberPlayer( pMember->GetID() );
                    if ( pPlayer == NULL )      // С��50 ���ý�
                    { continue; }

                    if ( pPlayer->GetLevel() < 50 )
                    {
                        MsgAckResult xAck;
                        xAck.result = ER_LevelErrorEnterTeamBattle;
                        xAck.value  = 50;
                        pPlayer->SendMessageToClient( &xAck );
                        continue;
                    }

                    // ���ü��ʱ��0, �ȿͻ��˻�����Ϣ
                    pPlayer->SetWaitChangeStage( GamePlayer::EnterStage, dwMapID, pRelive->PositionX, pRelive->PositionY, pRelive->Direction, 0, false );

                    MsgEnterTeamBattleReq xReq;
                    xReq.dwMapID = dwMapID;
                    pPlayer->SendMessageToClient( &xReq );
                }
            }

            setUnit.erase( iter );
        }
    }

    SendWaitNextBattleMessage();    // ֪ͨ�ͻ���û����ĵȴ���һ��
    SendUnitCountMessage();
}

struct GreaterBattleRecord : public std::unary_function< BattleDefine::BattleRecord*, bool >
{
    bool operator()( BattleDefine::BattleRecord* pLeft, BattleDefine::BattleRecord* pRight )
    {
        return ( *pLeft > *pRight );
    }
};

template<>
void TeamBattleData::EndFight( unsigned int nCurrentTime )
{
    // ������ظ�����ս��, ������һ��
    if ( GetRepeatTurns() > 0 )
    {
        SetSignUpInfo( nCurrentTime );
    }
    else
    {
        SetStatus( BattleDefine::Status_Close );
    }

    for ( MapBattleRecordIter iter = mapBattleRecord.begin(); iter != mapBattleRecord.end(); ++iter )
    {
        SendBattleRecordToClient( iter->first, MsgTellBattleRecord::Status_FightEnd );      // ���ͽ�����ͻ���

        // �������, ������
        std::vector< BattleDefine::BattleRecord* > vecRecord( 0 );
        for ( TeamRecordIter riter = iter->second.begin(); riter != iter->second.end(); ++riter )
        {
            vecRecord.push_back( &riter->second );
        }

        std::sort( vecRecord.begin(), vecRecord.end(), GreaterBattleRecord() );       // ����
        int nIndex = 1;
        for ( std::vector< BattleDefine::BattleRecord* >::iterator viter = vecRecord.begin(); viter != vecRecord.end(); ++viter )
        {
            GameTeam* pTeam = GetUnit( ( *viter )->GetTeamID() );
            if ( pTeam == NULL )
            { continue; }

            // ������
            for ( int i = 0; i < pTeam->TeamMemberCount(); ++i )
            {
                GameTeamMember* pMember = pTeam->GetTeamMemberByIndex( i );
                if ( pMember == NULL )
                { continue; }

                GamePlayer* pPlayer = pTeam->GetMemberPlayer( pMember->GetID() );
                if ( pPlayer == NULL || pPlayer->GetMapID() != iter->first )
                { continue; }       // ���ڱ���ͼ�Ĳ������� 

                // ���ýű�, �ɽű��������Щʲô
                GetScriptMgr()->StartupVM( ST_TEAMBATTLER, 0, pPlayer, false, nIndex );      
            }

            ++nIndex;
        }
    }
}

template<>
void TeamBattleData::UpdateBattleRecord( unsigned dwMapID, unsigned int nID, unsigned int nPlayeriD, int nIntegral, int nKillCount, int nDeathCount, bool bSendMessage /* = true */ )
{
    BattleDefine::BattleRecord* pRecord = GetBattleRecord( nID, dwMapID );
    if ( pRecord == NULL )
    { return; }

    pRecord->AddIntegral( nIntegral );
    pRecord->AddKillCount( nKillCount );
    pRecord->AddDeathCount( nDeathCount );

    // ���¸��˻���
    if ( nIntegral > 0 )
    {
        MapKillInfoIter kiter = mapKillInfo.find( nPlayeriD );
        if ( kiter == mapKillInfo.end() )
        {
            kiter = mapKillInfo.insert( std::make_pair( nPlayeriD, BattleDefine::KillInfo() ) ).first;
        }
        if ( kiter != mapKillInfo.end() )
        {
            kiter->second.SetIntegral( kiter->second.GetIntegral() + nIntegral );
        }
    }

    // ֪ͨ�ͻ���
    if ( !bSendMessage )
    { return; }

    SendBattleRecordToClient( dwMapID, MsgTellBattleRecord::Status_Fighting );
}

template<>
void TeamBattleData::SendBattleRecordToClient( unsigned int dwMapID, unsigned char uchStatus, GamePlayer* pPlayer /* = NULL*/ )
{
    MapBattleRecordIter iter = mapBattleRecord.find( dwMapID );
    if ( iter == mapBattleRecord.end() )
    { return; }

    MsgTellBattleRecord xTell;
    xTell.uchType   = BattleDefine::TeamType;
    xTell.uchStatus = uchStatus;
    xTell.dwMapID   = dwMapID;

    int nCount = 0;
    for ( TeamRecordIter riter = iter->second.begin(); riter != iter->second.end(); ++riter )
    {
        GameTeam* pTeam = GetUnit( riter->first );
        if ( pTeam == NULL )
        { continue; }

        GameTeamMember* pMember = pTeam->GetTeamMemberByID( pTeam->GetTeamHeaderID() );
        if ( pMember == NULL )
        { continue; }

        xTell.xRecord[nCount].dwID = pTeam->GetID();
        strncpy_s( xTell.xRecord[nCount].szName, sizeof( xTell.xRecord[nCount].szName ), pMember->GetName(), sizeof( xTell.xRecord[nCount].szName ) - 1 );

        xTell.xRecord[nCount].nIntegral   = riter->second.GetIntegral();
        xTell.xRecord[nCount].nKillCount  = riter->second.GetKillCount();
        xTell.xRecord[nCount].nDeathCount = riter->second.GetDeathCount();
        ++nCount;
    }

    if ( pPlayer != NULL )
    {
        pPlayer->SendMessageToClient( &xTell );
    }
    else
    {
        GettheServer().SendMsgToStage( &xTell, dwMapID );
    }
}

template<>
void TeamBattleData::GetUnitName( MsgTellBattleSignUpInfo* pSignUpInfo )
{
    if ( pSignUpInfo == NULL )
    { return; }

    for ( UnitSetIter iter = setUnit.begin(); iter != setUnit.end(); ++iter )
    {
        GameTeam* pTeam = GetUnit( *iter );
        if ( pTeam == NULL )
        { continue; }

        GameTeamMember* pMember = pTeam->GetTeamMemberByID( pTeam->GetTeamHeaderID() );
        if ( pMember == NULL )
        { continue; }

        pSignUpInfo->AddTeamInfo( *iter, pMember->GetName() );
    }
}

template<>      // ����ÿ���˵�ɱ�����, ���ض���Ľ�������
unsigned int TeamBattleData::UpdateKillRecord( GamePlayer* pKiller, GamePlayer* pBeKill )
{
    if ( pKiller == NULL || pBeKill == NULL )
    { return 0; }

    // ���ɱ���ߵ�ɱ����Ϣ
    MapKillInfoIter kiter = mapKillInfo.find( pKiller->GetDBCharacterID() );
    if ( kiter == mapKillInfo.end() )
    {
        kiter = mapKillInfo.insert( std::make_pair( pKiller->GetDBCharacterID(), BattleDefine::KillInfo() ) ).first;
        if ( kiter == mapKillInfo.end() )
        { return 1; }
    }

    // ��ñ�ɱ�ߵ�ɱ����Ϣ
    MapKillInfoIter biter = mapKillInfo.find( pBeKill->GetDBCharacterID() );
    if ( biter == mapKillInfo.end() )
    {
        biter = mapKillInfo.insert( std::make_pair( pBeKill->GetDBCharacterID(), BattleDefine::KillInfo() ) ).first;
        if ( biter == mapKillInfo.end() )
        { return 1; }
    }

    // �ж�ɱ����....
    kiter->second.SetKillCount( kiter->second.GetKillCount() + 1 );     // ɱ����+1
    kiter->second.SetKeepKill( kiter->second.GetKeepKill() + 1 );       // ����ɱ����+1

    // ��ɱ��
    int nKillCount = biter->second.GetKeepKill();
    biter->second.SetKeepKill( 0 );     // �������ɱ�˼�¼
    biter->second.SetBeKillCount( biter->second.GetBeKillCount() + 1 );

    // ɱ��2������, �����ս�ɱ2������, ֪ͨ�ͻ���
    if ( kiter->second.GetKeepKill() > 2 || nKillCount > 2 )
    {
        MsgNotifyBattleKillNum xKill;
        strncpy_s( xKill.killer, sizeof( xKill.killer ), pKiller->GetCharName(), sizeof( xKill.killer ) - 1 );
        strncpy_s( xKill.beKiller, sizeof( xKill.beKiller ), pBeKill->GetCharName(), sizeof( xKill.beKiller ) - 1 );
        xKill.killNum   = kiter->second.GetKeepKill();
        xKill.beKillNum = nKillCount;
        GettheServer().SendMsgToStage( &xKill, pKiller->GetMapID() );
    }

    unsigned int nIntegral = 1;
    if ( nKillCount > 2 )       // �սᱻɱ��3��ɱ..��ö���Ļ���
    {
        nIntegral = ( nKillCount - 1 ) / 2;
        if ( nIntegral > 5 )
        { nIntegral = 5; }
    }

    return nIntegral;
}