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

    // 初始化 酒馆任务的记录时间信息
    for ( int i = 0; i < MAX_SPECIALQUEST_COUNT; ++i )
    {
        if ( m_pGamePlayer->gCharInfoServer.extendData.xPubQuestInfo[i].nNpcID == InvalidGameObjectId )
        { break; }

        RecordTime xRecordTime;
        xRecordTime.SetRecordTime( m_pGamePlayer->gCharInfoServer.extendData.xPubQuestInfo[i].dwTime );

        AddSpecialQuest( m_pGamePlayer->gCharInfoServer.extendData.xPubQuestInfo[i].nNpcID, xRecordTime );
    }

    // 计算已经接过的酒馆任务个数
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
    { return; } // 自己不在NPC附近

    RecordTime* pRecordTime = GetSpecialQuestRecordTime( pNpc->GetNpcID() );
    SYSTEMTIME xSystemTime;
    ::GetLocalTime( &xSystemTime );
    if ( pRecordTime != NULL )
    {
        if ( !pRecordTime->CheckRecordTime( xSystemTime.wYear, xSystemTime.wMonth, xSystemTime.wDay ) )
        { return; }     // 已经随即过酒馆任务列表了
    }

    // 找到可以接的任务列表, 已经接过的任务不能出现
    std::list< int > listQuestID;
    listQuestID.clear();
    
    QuestValues mapValue;          // 保存所有有保存的记数变量
    mapValue.clear();

    for ( int i = 0; i < pNpc->GetQuestScriptCount(); ++i )
    {
        QuestScript* pQuestInfo = pNpc->GetQuestScriptByIndex( i );
        if ( pQuestInfo == NULL )
        { continue; }

        SetSpecialQuestState( pQuestInfo->stQuestId, QuestManager::ESQGS_CannotGain, mapValue );   // 清除掉前置变量
    
        if ( m_pGamePlayer->GetQuestState( pQuestInfo->stQuestId ) != QuestManager::eQuestGaining ) // 说明没有接
        {
            listQuestID.push_back( pQuestInfo->stQuestId );
        }
    }

    if ( !listQuestID.empty() )    // 存在任务
    { 
        // 随即 6 - 9 个任务   要按照策划的控制概率来
        int nTotalCount = theRand.rand32() % 4 + 6; 

        for ( int i = 0; i < nTotalCount; ++i )
        {
            if ( listQuestID.empty() )
            { break; }

            SQuest* pRandQuest = theQuestManager.GetQuestByTheQuests( listQuestID );
            if ( pRandQuest == NULL )
            { continue; }

            // 得到该任务的前置变量, 保证任务是可接的
            SetSpecialQuestState( pRandQuest->Id, QuestManager::ESQGS_CanGain, mapValue );

            listQuestID.remove( pRandQuest->Id );
        }

        // 随即完任务列表, 保存时间
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

    // 发送变量给客户端刷新
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

    // 获得所有的酒馆任务, 判断人物角色接了多少个
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

    // 如果不是酒馆任务,任务时可接的, 其他条件在SetQuestState中判断
    if ( !pQuest->IsPubQuest() )
    { return true; }

    // 判断酒馆任务数量是否已经达到了最大值
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

    // 恢复任务的前置变量
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

    // 恢复任务的前置变量
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

        // 保存起来,等下一起发送给客户端
        mapValue[pRequirement->wVar] = (short)(m_pGamePlayer->GetVar( pRequirement->wVar ));
    }
}

////////////////////////////////////////////////////////////////////////////////////////////
// 征伐任务
template<>
bool ConQuest::Initialize( GamePlayer* pPlayer )
{
    if ( pPlayer == NULL )
    { return false; }

    m_pGamePlayer = pPlayer;

    // 初始化 酒馆任务的记录时间信息
    for ( int i = 0; i < MAX_SPECIALQUEST_COUNT; ++i )
    {
        if ( m_pGamePlayer->gCharInfoServer.extendData.xConQuestInfo[i].nNpcID == 0 )
        { break; }

        RecordTime xRecordTime;
        xRecordTime.SetRecordTime( m_pGamePlayer->gCharInfoServer.extendData.xConQuestInfo[i].dwTime );

        AddSpecialQuest( m_pGamePlayer->gCharInfoServer.extendData.xConQuestInfo[i].nNpcID, xRecordTime );
    }

    // 计算已经接过的酒馆任务个数
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
    { return; } // 自己不在NPC附近

    RecordTime* pRecordTime = GetSpecialQuestRecordTime( pNpc->GetNpcID() );
    SYSTEMTIME xSystemTime;
    ::GetLocalTime( &xSystemTime );
    if ( pRecordTime != NULL )
    {
        if ( !pRecordTime->CheckRecordTime( xSystemTime.wYear, xSystemTime.wMonth, xSystemTime.wDay ) )
        { return; }     // 已经随即过接过征伐任务列表了
    }

    QuestValues mapValue;          // 保存所有有保存的记数变量
    mapValue.clear();

    for ( int i = 0; i < pNpc->GetQuestScriptCount(); ++i )
    {
        QuestScript* pQuestInfo = pNpc->GetQuestScriptByIndex( i );
        if ( pQuestInfo == NULL )
        { continue; }

        SetSpecialQuestState( pQuestInfo->stQuestId, QuestManager::ESQGS_CannotGain, mapValue );   // 清除掉变量记数
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

    // 发送变量给客户端刷新
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

    // 获得所有的征伐任务, 判断人物角色接了多少个
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

    // 如果不是征伐任务,任务时可接的, 其他条件在SetQuestState中判断
    if ( !pQuest->IsConQuest() )
    { return true; }

    // 判断酒馆任务数量是否已经达到了最大值
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

    // 恢复任务的前置变量
    SQuest* pQuest = theQuestManager.GetQuest( nQuestID );
    if ( pQuest == NULL )
    { return; }

    SQuestRequirement* pRequirement = pQuest->GetReceiveRequirement( SQuest::eRequirement_VarLimit );
    if ( pRequirement == NULL )
    { return; }

    int nValue = m_pGamePlayer->GetVar( pRequirement->wVar );
    nValue += 1;    // 变量记数+1
    m_pGamePlayer->SetVar( pRequirement->wVar, nValue );
}

template<>
void ConQuest::SetSpecialQuestState( unsigned int nQuestID, uint8 nState, QuestValues& mapValue )
{
    if ( m_pGamePlayer == NULL )
    { return; }

    // 恢复任务的前置变量
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

        // 保存起来,等下一起发送给客户端
        mapValue[ pRequirement->wVar ] = (short)(m_pGamePlayer->GetVar( pRequirement->wVar ));
    }
}