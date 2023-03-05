#include "Stage.h"
#include "FuncPerformanceLog.h"
#include "MessageDefine.h"

CGateStage::CGateStage()
{
    m_dwMapCfgID = -1;
    m_dwStageID = -1;
    _pTiles = 0;
}

CGateStage::~CGateStage()
{
    if (_pTiles)
    { delete [] _pTiles; }
}

bool CGateStage::InitStage( int iWidth,int iHeight )
{
    m_iWidth = iWidth;
    m_iHeight = iHeight;
    m_iAreaCol = (m_iWidth + dr_stageAreaSize - 1)/dr_stageAreaSize;
    m_iAreaRow = (m_iHeight + dr_stageAreaSize - 1)/dr_stageAreaSize;
    m_iAreaMax = m_iAreaCol * m_iAreaRow;
    _pTiles = new BigTile[m_iAreaMax];
    
    if (!_pTiles)
    {
        LogMessage::LogLogicError( "CGateStage::InitStage new BigTile Fail %d 0x%x", m_dwMapCfgID, m_dwStageID );
        return false;
    }
    return true;
}


int CGateStage::AddToTile( GameObjectId stID, short stTileID )
{
    if (stTileID< 0 || stTileID>= m_iAreaMax)
    { stTileID = 0; }

    _pTiles[stTileID].AddId(stID);
    return stTileID;
}

void CGateStage::RemoveFromTile( GameObjectId stID,short stTileID )
{
    if (stTileID < 0 || stTileID >= m_iAreaMax)
    { return; }

    _pTiles[stTileID].RemoveId(stID);
}

void CGateStage::SendMsgToArea( Msg* pMsg, int nX, int nY )
{
    const int nAreaCount = More_nMapSize / dr_stageAreaSize;

    int nStartCol = nAreaCount * nX;
    int nStartRow = nAreaCount * nY;

    int nEndCol = nStartCol + nAreaCount;
    int nEndRow = nStartRow + nAreaCount;

    for ( int h = nStartRow; h<nEndRow; h++ )
    {
        if ( h >= m_iAreaRow )
        {
            // ToLog(false);
            continue;
        }

        for ( int w = nStartCol; w<nEndCol; w++ )
        {
            if ( w >= m_iAreaCol )
            {
                // ToLog(false);
                continue;
            }
            int nIndex = h*m_iAreaCol + w;
            if ( nIndex >= m_iAreaMax )
            {
                // ToLog(false);
                return;
            }
            _pTiles[nIndex].SendMsg( 0, pMsg, false );
        }
    }
}

void CGateStage::SendMsgToView( GameObjectId stID,short stArea,Msg* pMsg,bool bExceptMe )
{
    //
    // 3 * 3 的广播范围
    //

    if (stArea < 0 || stArea >= m_iAreaMax || m_iAreaCol == 0)
        return;

    short sRadius = (BR_View-1)/2;

    short stXArea = stArea % m_iAreaCol - sRadius;
    short stYArea = stArea / m_iAreaCol - sRadius;

    short x = 0;        // x 坐标光标
    short y = stYArea ; // y 坐标光标

    short stRow = y * m_iAreaCol; // 当前行的起始位置
    short stNow = 0;

    for(int iRow=0; iRow<BR_View ; ++iRow, ++y, stRow += m_iAreaCol )
    {
        if( y < 0 || y >= m_iAreaRow )
            continue;

        x = stXArea;

        // 得到Tile位置
        stNow = stRow;
        stNow += x;

        for( int iCol=0; iCol<BR_View ; ++iCol, ++x, ++stNow )
        {
            if( x < 0 || x >= m_iAreaCol )
                continue;

            _pTiles[ stNow ].SendMsg( stID, pMsg, bExceptMe );
        }
    }
    
    //if ( pMsg->GetType() == MSG_SAWSOMEONEDEAD )
    //{
    //    char szTemp[128] = {0};
    //    std::string strTemp;
    //    for ( int i=0; i<Tiles.size(); ++i)
    //    {
    //        sprintf_s( szTemp, sizeof(szTemp), "%d", Tiles[i]);
    //        strTemp += szTemp;
    //        strTemp += ",";
    //    }
    //}
}

void CGateStage::SendMsgToRegion( GameObjectId id, short stArea, Msg *pMsg)
{
    if (stArea < 0 || stArea >= m_iAreaMax || m_iAreaCol == 0)
        return;

    short sRadius = (BR_Region-1)/2;

    short stXArea = stArea % m_iAreaCol - sRadius;
    short stYArea = stArea / m_iAreaCol - sRadius;
    
    short x = 0;
    short y = stYArea;

    short stRow = y * m_iAreaCol;
    short stNow = 0;

    for(int iRow = 0 ; iRow <BR_Region ; iRow++, y++, stRow += m_iAreaCol )
    {
        if( y < 0 || y >= m_iAreaRow )
            continue;

        x = stXArea;

        // 得到Tile位置
        stNow = stRow;
        stNow += x;

        for(int iCol = 0 ; iCol <BR_Region ; iCol++, x++, stNow++ )
        {
            if( x < 0 || x >= m_iAreaCol )
                continue;

            _pTiles[ stNow ].SendMsg( id, pMsg, false );
        }
    }
}

void CGateStage::SendMsgToStage( Msg* pMsg )
{
    for(int iLoop = 0 ; iLoop < m_iAreaMax ; ++iLoop )
    {
        _pTiles[ iLoop ].SendMsg( 0, pMsg, false );
    }
}

void CGateStage::SendCountryMsgToStage(  Msg* pMsg, TCountryId country, uint16 ustLevel, uint16 stExceptID )
{
    for(int iLoop = 0; iLoop<m_iAreaMax ; ++iLoop )
    {
        _pTiles[ iLoop ].SendCountryMsg( pMsg, country, ustLevel, stExceptID );
    }
}
