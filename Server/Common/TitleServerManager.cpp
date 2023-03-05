#include "TitleServerManager.h"
#include "GamePlayer.h"

template<>
void ServerTitleManager< GamePlayer >::UpdataTitleCounterByCount( GamePlayer* pPlayer, short nType, int nValue, int nCount /* = 1 */, bool bOnlyOne /* = false */ ) 
{
    for ( TitleCounterMapIter iter = m_mapTitleCounter.begin(); iter != m_mapTitleCounter.end(); )
    {
        bool bDeleteiter = false;
        if ( iter->second.GetType() == nType && iter->second.GetValue() == nValue )
        {
            iter->second.AddCount( nCount );

            // 判断是否已经满足了添加称号条件
            TitleConfig::Title* pTitleData = theTitleConfig.GetTitleByTitleID( iter->second.GetTitleID() );
            if ( pTitleData != NULL && !pTitleData->IsScript() && pTitleData->GetConditionType() == nType && 
                pTitleData->GetParameter1() == nValue && iter->second.GetCount() >= pTitleData->GetParameter2() )
            {
                if ( pPlayer != NULL && pPlayer->AddTitle( iter->second.GetTitleID() ) )
                {
                    iter = m_mapTitleCounter.erase( iter );
                    bDeleteiter = true;
                }
            }

            // 只更新一个记数, 否则更新条件相同的所有记数
            if ( bOnlyOne )
            { break; }
        }

        if ( !bDeleteiter )
        { ++iter; }    
    }
}

template<>
void ServerTitleManager< GamePlayer >::SendRemoveTitleToClient( GamePlayer* pPlayer )
{
    if ( pPlayer == NULL || m_vecRemoveTitle.empty() )
    { return; }

    for ( RemoveVectorIter iter = m_vecRemoveTitle.begin(); iter != m_vecRemoveTitle.end(); ++iter )
    {
        MsgRemoveTitleAck xAck;
        xAck.nTitleID = *iter;

        pPlayer->SendMessageToClient( &xAck );
    }

    m_vecRemoveTitle.clear();
}