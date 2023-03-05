#include "LuckRewardManager.h"
#include "TeamManager.h"
#include "ShareData.h"
#include "GamePlayer.h"
#include "XmlStringLanguage.h"

// ֻ����3���������ȡ��Ʒ
bool LuckReward::IsCanGetReward()
{
    switch( GetRewardType() )
    {
    case ECD_RandType_Init:
        {
            return !m_bIsLucking;       // �ͻ��˲���ת��
        }
        break;
    case ECD_RandType_Double:
    case ECD_RandType_Half:
        {
            return true;
        }
        break;
    }
    return false;
}

// �ж��ܷ���һ��
bool LuckReward::IsCanNextLuckLevel()
{
    switch( GetRewardType() )
    {
    case ECD_RandType_Front:
    case ECD_RandType_Next:
    case ECD_RandType_Jump:
        {
            return true;
        }
        break;
    }
    return false;
}

bool LuckReward::IsCanAcceptQuest( unsigned char uchLevel )
{
    if ( GetLevel() != uchLevel )
    { return false; }       // ���Ǳ��ز���ˢ��

    switch ( GetRewardType() )      // ��3�������������ˢ������
    {
    case ECD_RandType_Leave:
    case ECD_RandType_Half:
    case ECD_RandType_Double:
        {
            return false;
        }
        break;
    case ECD_RandType_Init:
        {
            return !m_bCanLuck;
        }
        break;
    default:
        break;
    }

    return true;
}

bool LuckReward::IsCanLuckReward()
{
    return ( GetRewardType() == ECD_RandType_Init );
}

void LuckReward::CopyReward( MsgTellLuckReward& xReward )
{
    for ( RewardVecIter iter = m_vecReward.begin(); iter != m_vecReward.end(); ++iter )
    {
        xReward.AddRewardIndex( *iter );
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
template<>
GameTeam* TeamLuckRewardManager::GetLuckUnit( unsigned int dwID )
{
    return theGameTeamManager.GetTeam( dwID );
}

template<>
void TeamLuckRewardManager::SendRewardMessage( LuckReward* pLuckReward, Msg* pMessage )
{
    if ( pLuckReward == NULL || pMessage == NULL )
    { return; }

    GameTeam* pTeam = GetLuckUnit( pLuckReward->GetID() );
    if ( pTeam == NULL )
    { return; }

    for ( int i = 0; i < pTeam->TeamMemberCount(); ++i )
    {
        GamePlayer* pPlayer = theRunTimeData.GetGamePlayerByDBID( pTeam->GetMemberIDByIndex( i ) );
        if ( pPlayer == NULL )
        { continue; }
        if ( pPlayer->IsInMapArea( pLuckReward->GetMapID(), pLuckReward->GetFloatX(), pLuckReward->GetFloatY(), TEAM_EXP_DIS ) )
        {
            GettheServer().SendMsgToSingle( pMessage, pPlayer );        // ��Ч��Χ�ڲŷ���
        }
    }
}

template<>       // ����ģʽ
bool TeamLuckRewardManager::CheckValid( LuckReward* pLuckReward )
{
    if ( pLuckReward == NULL )
    { return false; }

    GameTeam* pTeam = GetLuckUnit( pLuckReward->GetID() );
    if ( pTeam == NULL )
    { return false; }

    // �����Ա�����������ͼ��
    for ( int i = 0; i < pTeam->TeamMemberCount(); ++i )
    {
        GamePlayer* pPlayer = theRunTimeData.GetGamePlayerByDBID( pTeam->GetMemberIDByIndex( i ) );
        if ( pPlayer == NULL )
        { continue; }

        if ( pLuckReward->GetMapID() == InvalidLogicNumber || pPlayer->GetMapID() == pLuckReward->GetMapID() )
        { return true; }
    }
    return false;
}

template<>  // ����ģʽ
void TeamLuckRewardManager::ReceiveLuckReward( LuckReward* pLuckReward )
{
    if ( pLuckReward == NULL )
    { return; }

    GameTeam* pTeam = GetLuckUnit( pLuckReward->GetID() );
    if ( pTeam == NULL )
    { return ; }

    // ������Ʒ �������Ҫ���Զ�������
    DropItemVector mapDropItem;          // ƽ�����佱������Ʒ
    DropItemVector mapRollItem;          // ��Ҫroll����Ʒ
    int nRewardMoney = 0;                   // ������Ǯ
    int nRewardExp   = 0;                   // �����ľ���

    if ( pLuckReward->IsCanGetReward() )            // ֻ���ܻ�ý�Ʒ
    {
        LogLuckReward( pLuckReward, pTeam );        // ��¼��־

        unsigned int nTeamCount = pTeam->GetTeamMemberCountInMap( pLuckReward->GetMapID(), pLuckReward->GetFloatX(), pLuckReward->GetFloatY() );
        LuckReward::RewardVec& vecReward = pLuckReward->GetReward();
        for ( LuckReward::RewardVecIter iter = vecReward.begin(); iter != vecReward.end(); ++iter )
        {
            const RewardData* pRewardData = theLuckRewardConfig.GetReward( pLuckReward->GetLevel(), *iter );
            if ( pRewardData == NULL )
            { continue; }

            int nValue = pRewardData->GetValue();
            if ( pLuckReward->GetRewardType() == ECD_RandType_Half )        // ����һ��
            {
                if ( nValue > 1 )
                    nValue /= 2; 
            }
            else if ( pLuckReward->GetRewardType() == ECD_RandType_Double ) // ����˫��
            {
                nValue *= 2;
            }

            switch( pRewardData->GetType() )        // Ŀǰ ���� ��Ǯ ������һ��ȯ �һ�
            {
            case ECD_Reward_Item:
                {
                    if ( nValue < nTeamCount )
                    {
                        DropBaseItem::AddDropItemInPackage( mapRollItem, pRewardData->GetItemID(), nValue );
                    }
                    else
                    {
                        int nCount = nValue / nTeamCount;
                        DropBaseItem::AddDropItemInPackage( mapDropItem, pRewardData->GetItemID(), nCount );
                        if ( !pRewardData->GetRealLife() && ( nCount * nTeamCount ) < nValue )     // ����ʵ��������roll�� 
                        {
                            DropBaseItem::AddDropItemInPackage( mapRollItem, pRewardData->GetItemID(), nValue - ( nCount * nTeamCount ) );
                        }
                    }
                }
                break;
            case ECD_Reward_Money:
                {
                    nRewardMoney += ( nValue * 10000 / nTeamCount );            // ���õ�������ǽ� ���ﻻ��һ��
                }
                break;
            case ECD_Reward_Exp:
                {
                    nRewardExp += ( nValue / nTeamCount );
                }
                break;
            default:
                break;
            }
        }

        if ( !mapRollItem.empty() )     // �����Ҫroll����Ʒ
        {
            unsigned char chAssignMode = pTeam->GetTeamAssignModeType();
            unsigned char chAssignItemLevel = pTeam->GetTeamAssignItemLevel();

            pTeam->SetTeamAssignModeType( AssignMode_Team );            // �ĳɶ������
            pTeam->SetTeamAssignItemLevel( eIL_Choiceness );       // �ĳ���Ʒ

            DropCharItemVector vecCharItem;          // ������������
            DropBaseItem::DropItemPackage( mapRollItem, vecCharItem, pTeam->GetID(), pTeam->GetTeamHeaderID(), pLuckReward->GetMapID(), pLuckReward->GetFloatX(), pLuckReward->GetFloatY(), LogDefine::ECD_DropType_Luck );

            // �ָ�����������
            pTeam->SetTeamAssignModeType( chAssignMode );
            pTeam->SetTeamAssignItemLevel( chAssignItemLevel );
        }
    }

    // ����Ҫ�뿪
    uint32 dwMapID = Safe_Map_Id;
    float fX       = Safe_Map_PosX;
    float fY       = Safe_Map_PosY;
    float fDir     = Safe_Map_Dir;
    MapConfig::MapData* pMapData = theMapConfig.GetMapDataById( EctypeId2MapId( pLuckReward->GetMapID() ) );
    if ( pMapData != NULL )
    { 
        MapConfig::RelivePosition* pRelive = pMapData->GetRelivePositionByState( false );
        if ( pRelive != NULL )
        { 
            dwMapID = pRelive->MapId;
            fX      = pRelive->PositionX;
            fY      = pRelive->PositionY;
            fDir    = pRelive->Direction;
        }
    }

    for ( int i = 0; i < pTeam->TeamMemberCount(); ++i )
    {
        unsigned int dwPlayerID = pTeam->GetMemberIDByIndex( i );
        GamePlayer* pTeamPlayer = theRunTimeData.GetGamePlayerByDBID( dwPlayerID );
        if ( pTeamPlayer == NULL )
        { continue;  }

        if ( pTeamPlayer->GetMapID() == pLuckReward->GetMapID() )           // �ڵ�ͼ�ڵĶ�Ҫ�뿪����ͼ
        {
            pTeamPlayer->SetWaitChangeStage( GamePlayer::LeaveStage, dwMapID, fX, fY, fDir, 180, true );
        }

        if ( !pTeamPlayer->IsInMapArea( pLuckReward->GetMapID(), pLuckReward->GetFloatX(), pLuckReward->GetFloatY(), TEAM_EXP_DIS ) )
        { continue; }           // ���ڷ�Χ�ڵĲ�������

        if ( !mapDropItem.empty() )     // ֻ�������� ����ID����0
        {
            DropCharItemVector vecCharItem;
            DropBaseItem::DropItemPackage( mapDropItem, vecCharItem, TeamDefine::NoneSessionID, pTeamPlayer->GetDBCharacterID(), pLuckReward->GetMapID(), pLuckReward->GetFloatX(), pLuckReward->GetFloatY(), LogDefine::ECD_DropType_Luck );
        }

        if ( nRewardMoney != 0 )
        {
            pTeamPlayer->OperateMoney( EOT_Add, nRewardMoney, true, __FUNCTION__, __LINE__,ePlayerMoneySourceType_Luck );        // ������Ǯ
        }

        if ( nRewardExp != 0 )
        {
            pTeamPlayer->Script_SetExp( nRewardExp, SKW_SETADD, __FUNCTION__, __LINE__ );                   // ��������
        }
    }
}

template<>
void TeamLuckRewardManager::LogLuckReward( LuckReward* pLuckReward, GameTeam* pTeam )
{
    if ( pLuckReward == NULL || pTeam == NULL )
    { return; }

    GamePlayer* pPlayer = theRunTimeData.GetGamePlayerByDBID( pTeam->GetTeamHeaderID() );
    if ( pPlayer == NULL )  
    { return; }

    //LOG_MESSAGE( LOGICSYSTEMOBJECT, LOG_PRIORITY_INFO, theXmlString.GetString( eLog_TeamLuckReward ), pTeamHeader->GetName(), pLuckReward->GetLevel(), FormatLogString( pLuckReward ) );
    pPlayer->Log( theXmlString.GetString( eLog_TeamLuckReward ), pPlayer->GetCharName(), pLuckReward->GetLevel(), FormatLogString( pLuckReward ) );

    if ( pLuckReward->IsCanGetReward() && pLuckReward->GetLevel() > 5 )
    {
        char szBroadcast[256] = {0};
        sprintf_s( szBroadcast, sizeof( szBroadcast ) - 1, theXmlString.GetString( eTellClient_LuckReward ), pPlayer->GetCharName(), pLuckReward->GetLevel() );
        pPlayer->ProcessSystem( szBroadcast, GamePlayer::SystemWorld );
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<>
GamePlayer* CharLuckRewardManager::GetLuckUnit( unsigned int dwID )
{
    return theRunTimeData.GetGamePlayerByDBID( dwID );
}

template<>
void CharLuckRewardManager::SendRewardMessage( LuckReward* pLuckReward, Msg* pMessage )
{
    if ( pLuckReward == NULL || pMessage == NULL )
    { return; }

    GamePlayer* pPlayer = GetLuckUnit( pLuckReward->GetID() );
    if ( pPlayer == NULL )
    { return; }

    pPlayer->SendMessageToClient( pMessage );
}

template<>      // ����ģʽ
bool CharLuckRewardManager::CheckValid( LuckReward* pLuckReward )
{
    if ( pLuckReward == NULL )
    { return false; }

    GamePlayer* pPlayer = GetLuckUnit( pLuckReward->GetID() );
    if ( pPlayer == NULL )
    { return false; }

    return ( pLuckReward->GetMapID() == InvalidLogicNumber || pPlayer->GetMapID() == pLuckReward->GetMapID() );
}

template<>  // ����ģʽ
void CharLuckRewardManager::ReceiveLuckReward( LuckReward* pLuckReward )
{
    if ( pLuckReward == NULL )
    { return; }

    GamePlayer* pPlayer = GetLuckUnit( pLuckReward->GetID() );
    if ( pPlayer == NULL )
    { return; }

    if ( pLuckReward->IsCanGetReward() )
    {
        LogLuckReward( pLuckReward, pPlayer );  // ��¼��־

        // ������Ʒ
        DropItemVector mapDropItem;
        LuckReward::RewardVec& vecReward = pLuckReward->GetReward();
        for ( LuckReward::RewardVecIter iter = vecReward.begin(); iter != vecReward.end(); ++iter )
        {
            const RewardData* pRewardData = theLuckRewardConfig.GetReward( pLuckReward->GetLevel(), *iter );
            if ( pRewardData == NULL )
            { continue; }

            int nValue = pRewardData->GetValue();
            if ( pLuckReward->GetRewardType() == ECD_RandType_Half )        // ����һ��
            {
                nValue /= 2; 
            }
            else if ( pLuckReward->GetRewardType() == ECD_RandType_Double ) // ����˫��
            {
                nValue *= 2;
            }

            switch( pRewardData->GetType() )        // Ŀǰ ���� ��Ǯ ������һ��ȯ �һ�
            {
            case ECD_Reward_Item:
                {
                    DropBaseItem::AddDropItemInPackage( mapDropItem, pRewardData->GetItemID(), nValue );
                }
                break;
            case ECD_Reward_Money:
                {
                    pPlayer->OperateMoney( EOT_Add, nValue * 10000, true, __FUNCTION__, __LINE__ ,ePlayerMoneySourceType_Luck);      // ���õ�������ǽ� ���ﻻ��һ��
                }
                break;
            case ECD_Reward_Exp:
                {
                    pPlayer->Script_SetExp( nValue, SKW_SETADD, __FUNCTION__, __LINE__ );
                }
                break;
            default:
                break;
            }
        }

        if ( !mapDropItem.empty() )     // ������Ʒ ֻ�������� ����ID����0
        {
            DropCharItemVector vecCharItem;
            DropBaseItem::DropItemPackage( mapDropItem, vecCharItem, TeamDefine::NoneSessionID, pPlayer->GetDBCharacterID(), pLuckReward->GetMapID(), pLuckReward->GetFloatX(), pLuckReward->GetFloatY(), LogDefine::ECD_DropType_Luck );
        }
    }

    // �����뿪�����ͼ
    uint32 dwMapID = Safe_Map_Id;
    float fX       = Safe_Map_PosX;
    float fY       = Safe_Map_PosY;
    float fDir     = Safe_Map_Dir;
    MapConfig::MapData* pMapData = theMapConfig.GetMapDataById( EctypeId2MapId( pLuckReward->GetMapID() ) );
    if ( pMapData != NULL )
    { 
        MapConfig::RelivePosition* pRelive = pMapData->GetRelivePositionByState( false );
        if ( pRelive != NULL )
        { 
            dwMapID = pRelive->MapId;
            fX      = pRelive->PositionX;
            fY      = pRelive->PositionY;
            fDir    = pRelive->Direction;
        }
    }

    pPlayer->SetWaitChangeStage( GamePlayer::LeaveStage, dwMapID, fX, fY, fDir, 120, true );
}

template<>
void CharLuckRewardManager::LogLuckReward( LuckReward* pLuckReward, GamePlayer* pPlayer )
{
    if ( pPlayer == NULL )
    { return; }

    pPlayer->Log( theXmlString.GetString( eLog_CharLuckReward ), pPlayer->GetCharName(), pLuckReward->GetLevel(), FormatLogString( pLuckReward ) );
}
