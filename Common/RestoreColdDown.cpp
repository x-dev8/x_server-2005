#include "RestoreColdDown.h"
#include "ItemDetail.h"
#include "FuncPerformanceLog.h"
#include "GameTime.h"

RestoreColdDown::RestoreColdDown()
{
    m_nUsedCount = 0;
}

RestoreColdDown::~RestoreColdDown()
{
}

bool RestoreColdDown::UseRestore( const int nId, bool bCheckCanUse )
{
    ItemDefine::SItemCommon* pItemDetail = GettheItemDetail().GetItemByID( nId );

    if ( !pItemDetail || pItemDetail->ucItemType != ItemDefine::ITEMTYPE_RESTORE )
    { return false; }

    ItemDefine::SItemRestore* pItemRestore = (ItemDefine::SItemRestore*)pItemDetail;
    if ( pItemRestore->stCoolDownType == -1 )
    { return true; }

    int nIndex = -1;
    for( int n=0; n<m_nUsedCount; ++n )
    {
        if ( pItemRestore->stCoolDownType == m_stCoolDown[n].m_ustType )
        {
            nIndex = n;
            break;
        }
    }
    if ( nIndex == -1 )
    {
        if( m_nUsedCount >= MAX_RESTORE_COUNT )
        {
            return false;
        }
        nIndex = m_nUsedCount++;
        if (nIndex < 0 || nIndex >= MAX_RESTORE_COUNT)
        {  return false; }
        m_stCoolDown[nIndex].m_ustType = pItemRestore->stCoolDownType;
        m_stCoolDown[nIndex].m_dwStartTime = 0;
        m_stCoolDown[nIndex].m_dwPeriod = 0;
    }

    DWORD dwCurTime = HQ_TimeGetTime();
    if( !GameTime::IsPassCurrentTime( dwCurTime, m_stCoolDown[nIndex].m_dwStartTime, m_stCoolDown[nIndex].m_dwPeriod ) )
    { return false;}

    if ( bCheckCanUse == false )
    {
        m_stCoolDown[nIndex].m_dwStartTime = dwCurTime;
        m_stCoolDown[nIndex].m_dwPeriod    = pItemRestore->dwCoolDown;
    }
    return true;
}

bool RestoreColdDown::GetTime( const int nId, DWORD* pdwStartTime, DWORD* pdwPeriod )
{
    ItemDefine::SItemCommon* pItemDetail = NULL;
    pItemDetail = GettheItemDetail().GetItemByID( nId );
    if ( pItemDetail == NULL || pItemDetail->ucItemType != ItemDefine::ITEMTYPE_RESTORE )
    {
        return false;
    }
    ItemDefine::SItemRestore* pItemRestore = (ItemDefine::SItemRestore*)pItemDetail;
    if ( pItemRestore->stCoolDownType == -1 )
        return false;
    DWORD dwCurTime = HQ_TimeGetTime();
    for( int n=0; n<m_nUsedCount; n++ )
    {
        if ( pItemRestore->stCoolDownType == m_stCoolDown[n].m_ustType )
        {
            if( GameTime::IsPassCurrentTime( dwCurTime, m_stCoolDown[n].m_dwStartTime, m_stCoolDown[n].m_dwPeriod ) )
            { return false; }

            *pdwStartTime = m_stCoolDown[n].m_dwStartTime;
            *pdwPeriod = m_stCoolDown[n].m_dwPeriod;
            return true;
        }
    }
    return false;
}

void RestoreColdDown::InitColdDown( SColdDown* pColdDown, int nCount )
{
    if ( pColdDown == NULL || nCount == 0 )
    { return; }

    m_nUsedCount = 0;
    DWORD dwCurrentTime = HQ_TimeGetTime();
    for ( int i = 0; i < nCount; ++i )
    {
        if ( m_nUsedCount >= MAX_RESTORE_COUNT )
        { break; }

        if ( pColdDown[i].IsEmpty() )
        { break; }

        m_stCoolDown[m_nUsedCount] = pColdDown[i];
        m_stCoolDown[m_nUsedCount].m_dwStartTime = dwCurrentTime;   // 设置开始时间
        ++m_nUsedCount;
    }
}

void RestoreColdDown::SaveColdDown( SColdDown* pColdDown, int nCount )
{
    if ( pColdDown == NULL || nCount == 0 )
    { return; }

    memset( pColdDown, 0, sizeof( SColdDown ) * nCount );

    int nIndex = 0;
    DWORD dwCurrentTime = HQ_TimeGetTime();

    for ( int i = 0; i < m_nUsedCount; ++i )
    {
        DWORD dwLeftTime = GameTime::GetLeftKeepTime( dwCurrentTime, m_stCoolDown[i].m_dwStartTime, m_stCoolDown[i].m_dwPeriod );
        if ( dwLeftTime == 0 )
        { continue; }

        pColdDown[nIndex] = m_stCoolDown[i];
        pColdDown[nIndex].m_dwPeriod = dwLeftTime;      // 设置剩余冷却时间
       
        ++nIndex;
        if ( nIndex >= nCount )
        { break; }
    }
}
