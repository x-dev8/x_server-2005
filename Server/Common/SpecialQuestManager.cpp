#include "SpecialQuestManager.h"
#include "GamePlayer.h"
#include "ShareData.h"
#include "NpcBaseEx.h"
#include "QuestManager.h"

template<>
bool PubQuest::Initialize( GamePlayer* pPlayer )
{
    if ( pPlayer == NULL )
    { return false; }

    m_pGamePlayer = pPlayer;

    // ��ʼ�� �ƹ�����ļ�¼ʱ����Ϣ
    for ( int i = 0; i < MAX_SPECIALQUEST_COUNT; ++i )
    {
        if ( m_pGamePlayer->gCharInfoServer.extendData.xPubQuestInfo[i].nNpcID == InvalidGameObjectId )
        { break; }

        RecordTime xRecordTime;
        xRecordTime.SetRecordTime( m_pGamePlayer->gCharInfoServer.extendData.xPubQuestInfo[i].dwTime );

        AddSpecialQuest( m_pGamePlayer->gCharInfoServer.extendData.xPubQuestInfo[i].nNpcID, xRecordTime );
    }

    // �����Ѿ��ӹ��ľƹ��������
    GetSpecialQuestCount();

    return true;
}

template<>
void PubQuest::ShowQuestList( unsigned int nNpcRunID )
{
    if ( nNpcRunID == 0 || m_pGamePlayer == NULL )
    { return; }
    
    BaseCharacter *pChar = theRunTimeData.GetCharacterByID( nNpcRunID );
    if ( pChar == NULL || !pChar->IsNpc() )
    { return; }

    NpcBaseEx* pNpc = static_cast< NpcBaseEx* >( pChar );
    if ( !m_pGamePlayer->IsInMapArea( pNpc->GetMapID(), pNpc->GetFloatX(), pNpc->GetFloatY(), 15.0f ) )
    { return; } // �Լ�����NPC����

    RecordTime* pRecordTime = GetSpecialQuestRecordTime( pNpc->GetNpcID() );
    SYSTEMTIME xSystemTime;
    ::GetLocalTime( &xSystemTime );
    if ( pRecordTime != NULL )
    {
        if ( !pRecordTime->CheckRecordTime( xSystemTime.wYear, xSystemTime.wMonth, xSystemTime.wDay ) )
        { return; }     // �Ѿ��漴���ƹ������б���
    }

    // �ҵ����Խӵ������б�, �Ѿ��ӹ��������ܳ���
    std::list< int > listQuestID;
    listQuestID.clear();
    
    QuestValues mapValue;          // ���������б���ļ�������
    mapValue.clear();

    for ( int i = 0; i < pNpc->GetQuestScriptCount(); ++i )
    {
        QuestScript* pQuestInfo = pNpc->GetQuestScriptByIndex( i );
        if ( pQuestInfo == NULL )
        { continue; }

        SetSpecialQuestState( pQuestInfo->stQuestId, QuestManager::ESQGS_CannotGain, mapValue );   // �����ǰ�ñ���
    
        if ( m_pGamePlayer->GetQuestState( pQuestInfo->stQuestId ) != QuestManager::eQuestGaining ) // ˵��û�н�
        {
            listQuestID.push_back( pQuestInfo->stQuestId );
        }
    }

    if ( !listQuestID.empty() )    // ��������
    { 
        // �漴 6 - 9 ������   Ҫ���ղ߻��Ŀ��Ƹ�����
        int nTotalCount = theRand.rand32() % 4 + 6; 

        for ( int i = 0; i < nTotalCount; ++i )
        {
            if ( listQuestID.empty() )
            { break; }

            SQuest* pRandQuest = theQuestManager.GetQuestByTheQuests( listQuestID );
            if ( pRandQuest == NULL )
            { continue; }

            // �õ��������ǰ�ñ���, ��֤�����ǿɽӵ�
            SetSpecialQuestState( pRandQuest->Id, QuestManager::ESQGS_CanGain, mapValue );

            listQuestID.remove( pRandQuest->Id );
        }

        // �漴�������б�, ����ʱ��
        if ( pRecordTime != NULL )
        {
            pRecordTime->SaveRecordTime( xSystemTime.wYear, xSystemTime.wMonth, xSystemTime.wDay );
        }
        else
        {
            RecordTime xRecordTime;
            xRecordTime.SaveRecordTime( xSystemTime.wYear, xSystemTime.wMonth, xSystemTime.wDay );
            AddSpecialQuest( pNpc->GetNpcID(), xRecordTime );
        }
    }

    // ���ͱ������ͻ���ˢ��
    MsgTellCharVar xTellVar;
    QuestValuesItr iter    = mapValue.begin();
    QuestValuesItr iterEnd = mapValue.end();
    for ( ; iter != iterEnd; ++iter )
    { xTellVar.AddValue( iter->first, iter->second ); }

    if ( xTellVar.varCount > 0 )
    {
        GettheServer().SendMsgToSingle( &xTellVar, m_pGamePlayer );
    }
}

template<>
int PubQuest::GetSpecialQuestCount()
{
    if ( m_pGamePlayer == NULL )
    { return 0; }

    // ������еľƹ�����, �ж������ɫ���˶��ٸ�
    m_setReceiveQuestID.clear();
    std::vector< int >& vecPubQuest = theQuestManager.GetAllPubQuest();
    for ( std::vector< int >::iterator iter = vecPubQuest.begin(); iter != vecPubQuest.end(); ++iter )
    {
        if ( theQuestManager.IsQuestActive( m_pGamePlayer->GetQuestState( *iter ) ) )
        {
            m_setReceiveQuestID.insert( *iter );
        }
    }

    return m_setReceiveQuestID.size();
}

template<>
void PubQuest::SaveQuest()
{
    if ( m_pGamePlayer == NULL )
    { return; }

    memset( m_pGamePlayer->gCharInfoServer.extendData.xPubQuestInfo, 0, sizeof( m_pGamePlayer->gCharInfoServer.extendData.xPubQuestInfo ) );

    int i = 0;
    for ( MapPubQuestIter iter = m_mapSpecialQuest.begin(); iter != m_mapSpecialQuest.end(); ++iter, ++i )
    {
        m_pGamePlayer->gCharInfoServer.extendData.xPubQuestInfo[i].nNpcID = iter->first;
        m_pGamePlayer->gCharInfoServer.extendData.xPubQuestInfo[i].dwTime = iter->second.GetRecordTime();
    }
}

template<>
bool PubQuest::CanReceiveQuest( unsigned int nNpcConfigID, unsigned int nQuestID )
{
    SQuest* pQuest = theQuestManager.GetQuest( nQuestID );
    if ( pQuest == NULL )
    { return false; }

    // ������Ǿƹ�����,����ʱ�ɽӵ�, ����������SetQuestState���ж�
    if ( !pQuest->IsPubQuest() )
    { return true; }

    // �жϾƹ����������Ƿ��Ѿ��ﵽ�����ֵ
    if ( m_setReceiveQuestID.size() >= ECD_Max_PubQuestCount )
    { 
        MsgAckResult msg;
        msg.result = ER_MaxPubQuestCount;
        msg.value  = ECD_Max_PubQuestCount;
        GettheServer().SendMsgToSingle( &msg, m_pGamePlayer );
        return false; 
    }

    return true;
}

template<>
void PubQuest::SetSpecialQuestState( unsigned int nQuestID, uint8 nState )
{
    if ( m_pGamePlayer == NULL )
    { return; }

    // �ָ������ǰ�ñ���
    SQuest* pQuest = theQuestManager.GetQuest( nQuestID );
    if ( pQuest == NULL )
    { return; }

    SQuestRequirement* pRequirement = pQuest->GetReceiveRequirement( SQuest::eRequirement_Var );
    if ( pRequirement == NULL )
    { return; }

    uint8 questState = m_pGamePlayer->GetVar( pRequirement->wVar );
    if ( questState != nState )
    { m_pGamePlayer->SetVar( pRequirement->wVar, nState ); }
}

template<>
void PubQuest::SetSpecialQuestState( unsigned int nQuestID, uint8 nState, QuestValues& mapValue )
{
    if ( m_pGamePlayer == NULL )
    { return; }

    // �ָ������ǰ�ñ���
    SQuest* pQuest = theQuestManager.GetQuest( nQuestID );
    if ( pQuest == NULL )
    { return; }

    SQuestRequirement* pRequirement = pQuest->GetReceiveRequirement( SQuest::eRequirement_Var );
    if ( pRequirement == NULL )
    { return; }

    uint8 questState = m_pGamePlayer->GetVar( pRequirement->wVar );
    if ( questState != nState )
    {
        m_pGamePlayer->SetVar( pRequirement->wVar, nState, SKW_SET, BV_NotSendMessage );

        // ��������,����һ���͸��ͻ���
        mapValue[pRequirement->wVar] = (short)(m_pGamePlayer->GetVar( pRequirement->wVar ));
    }
}

////////////////////////////////////////////////////////////////////////////////////////////
// ��������
template<>
bool ConQuest::Initialize( GamePlayer* pPlayer )
{
    if ( pPlayer == NULL )
    { return false; }

    m_pGamePlayer = pPlayer;

    // ��ʼ�� �ƹ�����ļ�¼ʱ����Ϣ
    for ( int i = 0; i < MAX_SPECIALQUEST_COUNT; ++i )
    {
        if ( m_pGamePlayer->gCharInfoServer.extendData.xConQuestInfo[i].nNpcID == 0 )
        { break; }

        RecordTime xRecordTime;
        xRecordTime.SetRecordTime( m_pGamePlayer->gCharInfoServer.extendData.xConQuestInfo[i].dwTime );

        AddSpecialQuest( m_pGamePlayer->gCharInfoServer.extendData.xConQuestInfo[i].nNpcID, xRecordTime );
    }

    // �����Ѿ��ӹ��ľƹ��������
    GetSpecialQuestCount();

    return true;
}


template<>
void ConQuest::ShowQuestList( unsigned int nNpcRunID )
{
    if ( nNpcRunID == 0 || m_pGamePlayer == NULL )
    { return; }

    BaseCharacter *pChar = theRunTimeData.GetCharacterByID( nNpcRunID );
    if ( pChar == NULL || !pChar->IsNpc() )
    { return; }

    NpcBaseEx* pNpc = static_cast< NpcBaseEx* >( pChar );
    if ( !m_pGamePlayer->IsInMapArea( pNpc->GetMapID(), pNpc->GetFloatX(), pNpc->GetFloatY(), 15.0f ) )
    { return; } // �Լ�����NPC����

    RecordTime* pRecordTime = GetSpecialQuestRecordTime( pNpc->GetNpcID() );
    SYSTEMTIME xSystemTime;
    ::GetLocalTime( &xSystemTime );
    if ( pRecordTime != NULL )
    {
        if ( !pRecordTime->CheckRecordTime( xSystemTime.wYear, xSystemTime.wMonth, xSystemTime.wDay ) )
        { return; }     // �Ѿ��漴���ӹ����������б���
    }

    QuestValues mapValue;          // ���������б���ļ�������
    mapValue.clear();

    for ( int i = 0; i < pNpc->GetQuestScriptCount(); ++i )
    {
        QuestScript* pQuestInfo = pNpc->GetQuestScriptByIndex( i );
        if ( pQuestInfo == NULL )
        { continue; }

        SetSpecialQuestState( pQuestInfo->stQuestId, QuestManager::ESQGS_CannotGain, mapValue );   // �������������
    }

    if ( pRecordTime != NULL )
    {
        pRecordTime->SaveRecordTime( xSystemTime.wYear, xSystemTime.wMonth, xSystemTime.wDay );
    }
    else
    {
        RecordTime xRecordTime;
        xRecordTime.SaveRecordTime( xSystemTime.wYear, xSystemTime.wMonth, xSystemTime.wDay );
        AddSpecialQuest( pNpc->GetNpcID(), xRecordTime );
    }

    // ���ͱ������ͻ���ˢ��
    MsgTellCharVar xTellVar;
    QuestValuesItr iter    = mapValue.begin();
    QuestValuesItr iterEnd = mapValue.end();
    for ( ; iter != iterEnd; ++iter )
    { xTellVar.AddValue( iter->first, iter->second ); }

    if ( xTellVar.varCount > 0 )
    { GettheServer().SendMsgToSingle( &xTellVar, m_pGamePlayer ); }
}

template<>
int ConQuest::GetSpecialQuestCount()
{
    if ( m_pGamePlayer == NULL )
    { return 0; }

    // ������е���������, �ж������ɫ���˶��ٸ�
    m_setReceiveQuestID.clear();
    std::vector< int >& vecConQuest = theQuestManager.GetConQuest();
    for ( std::vector< int >::iterator iter = vecConQuest.begin(); iter != vecConQuest.end(); ++iter )
    {
        if ( theQuestManager.IsQuestActive( m_pGamePlayer->GetQuestState( *iter ) ) )
        {
            m_setReceiveQuestID.insert( *iter );
        }
    }

    return m_setReceiveQuestID.size();
}

template<>
void ConQuest::SaveQuest()
{
    if ( m_pGamePlayer == NULL )
    { return; }

    memset( m_pGamePlayer->gCharInfoServer.extendData.xConQuestInfo, 0, sizeof( m_pGamePlayer->gCharInfoServer.extendData.xConQuestInfo ) );

    int i = 0;
    for ( MapPubQuestIter iter = m_mapSpecialQuest.begin(); iter != m_mapSpecialQuest.end(); ++iter, ++i )
    {
        m_pGamePlayer->gCharInfoServer.extendData.xConQuestInfo[i].nNpcID = iter->first;
        m_pGamePlayer->gCharInfoServer.extendData.xConQuestInfo[i].dwTime = iter->second.GetRecordTime();
    }
}

template<>
bool ConQuest::CanReceiveQuest( unsigned int nNpcConfigID, unsigned int nQuestID )
{
    SQuest* pQuest = theQuestManager.GetQuest( nQuestID );
    if ( pQuest == NULL )
    { return false; }

    // ���������������,����ʱ�ɽӵ�, ����������SetQuestState���ж�
    if ( !pQuest->IsConQuest() )
    { return true; }

    // �жϾƹ����������Ƿ��Ѿ��ﵽ�����ֵ
    if ( m_setReceiveQuestID.size() >= ECD_Max_ConQuestCount )
    { 
        MsgAckResult msg;
        msg.result = ER_MaxConQuestCount;
        msg.value  = ECD_Max_ConQuestCount;
        GettheServer().SendMsgToSingle( &msg, m_pGamePlayer );
        return false; 
    }

    return true;
}

template<>
void ConQuest::SetSpecialQuestState( unsigned int nQuestID, uint8 nState )
{
    if ( m_pGamePlayer == NULL )
    { return; }

    // �ָ������ǰ�ñ���
    SQuest* pQuest = theQuestManager.GetQuest( nQuestID );
    if ( pQuest == NULL )
    { return; }

    SQuestRequirement* pRequirement = pQuest->GetReceiveRequirement( SQuest::eRequirement_VarLimit );
    if ( pRequirement == NULL )
    { return; }

    int nValue = m_pGamePlayer->GetVar( pRequirement->wVar );
    nValue += 1;    // ��������+1
    m_pGamePlayer->SetVar( pRequirement->wVar, nValue );
}

template<>
void ConQuest::SetSpecialQuestState( unsigned int nQuestID, uint8 nState, QuestValues& mapValue )
{
    if ( m_pGamePlayer == NULL )
    { return; }

    // �ָ������ǰ�ñ���
    SQuest* pQuest = theQuestManager.GetQuest( nQuestID );
    if ( pQuest == NULL )
    { return; }

    SQuestRequirement* pRequirement = pQuest->GetReceiveRequirement( SQuest::eRequirement_VarLimit );
    if ( pRequirement == NULL )
    { return; }
    
    uint8 questState = m_pGamePlayer->GetVar( pRequirement->wVar );
    if ( questState != nState )
    {
        m_pGamePlayer->SetVar( pRequirement->wVar, nState, SKW_SET, BV_NotSendMessage );

        // ��������,����һ���͸��ͻ���
        mapValue[ pRequirement->wVar ] = (short)(m_pGamePlayer->GetVar( pRequirement->wVar ));
    }
}