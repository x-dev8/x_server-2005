#include <MeRTLibs.h>
#include "MeUi/UiPicture.h"
#include "PlaneEffect.h"

CPlaneEffect::CPlaneEffect()
{
    m_strPicPath.clear();
    m_rectVec.clear();
    m_bInited = false;
    m_dwTimePerFrame = 0;
    m_dwLastPicTime = 0;
    m_pCurRect = 0;
}

CPlaneEffect::~CPlaneEffect()
{
    m_strPicPath.clear();
    m_rectVec.clear();
}

bool CPlaneEffect::Initialize( const std::string& strPicPath, int nRowCount, int nColCount, int nCount, 
                              const RECT& rcFirst, DWORD dwTotalTime, bool bOrderByRow, bool bReverse )
{
    // 参数设置有误
    if( strPicPath.empty() || nRowCount <= 0 || nColCount <= 0 || nCount <= 0 || nRowCount * nColCount < nCount || dwTotalTime == 0 )
    {
        m_bInited = false;
        return false;
    }

	m_strPicPath = strPicPath;
	m_dwTimePerFrame = dwTotalTime / nCount;

    // 设置每帧坐标
    SrcRect _srcRect;
    m_rectVec.clear();
    bool _bSetOver = false;
    for( int i = 0; i < ( bOrderByRow ? nRowCount : nColCount ); ++i )
    {
        if( bOrderByRow )
        {
            _srcRect.rcSrc.top = rcFirst.top + i * ( rcFirst.bottom - rcFirst.top );
            _srcRect.rcSrc.bottom = rcFirst.bottom + i * ( rcFirst.bottom - rcFirst.top );
        }
        else
        {
            _srcRect.rcSrc.left = rcFirst.left + i * ( rcFirst.right - rcFirst.left );
            _srcRect.rcSrc.right = rcFirst.right + i * ( rcFirst.right - rcFirst.left );
        }

        for( int j = 0; j < ( bOrderByRow ? nColCount : nRowCount ); ++j )
        {
            if( i * ( bOrderByRow ? nColCount : nRowCount ) + j + 1 > nCount )
            {
                _bSetOver = true;
                break;
            }

            if( bOrderByRow )
            {
                _srcRect.rcSrc.left = rcFirst.left + j * ( rcFirst.right - rcFirst.left );
                _srcRect.rcSrc.right = rcFirst.right + j * ( rcFirst.right - rcFirst.left );
            }
            else
            {
                _srcRect.rcSrc.top = rcFirst.top + j * ( rcFirst.bottom - rcFirst.top );
                _srcRect.rcSrc.bottom = rcFirst.bottom + j * ( rcFirst.bottom - rcFirst.top );
            }
            m_rectVec.push_back( _srcRect );
        }
        if( _bSetOver )
            break;
    }

    if( m_rectVec.empty() )
    {
        m_bInited = false;
        return false;
    }
    // 构建环形链表
    if( !bReverse )
    {
        std::vector<SrcRect>::iterator _it = m_rectVec.begin();
        for( ; _it != m_rectVec.end() - 1; ++_it )
        {
            _it->pNext = &( *( _it + 1 ) );
        }
        m_pCurRect = m_rectVec.back().pNext = &m_rectVec.front();
    }
    else
    {
        std::vector<SrcRect>::reverse_iterator _it = m_rectVec.rbegin();
        for( ; _it != m_rectVec.rend() - 1; ++_it )
        {
            _it->pNext = &( *( _it + 1 ) );
        }
        m_pCurRect = m_rectVec.front().pNext = &m_rectVec.back();
    }

    m_bInited = true;
    return true;
}

void CPlaneEffect::Display( const RECT& rcDest )
{
    if( !m_bInited )
        return;
    
    int _nPicID = -1;
    RECT _rcDest = rcDest;
    DWORD dwNowTime = HQ_TimeGetTime();
    if( dwNowTime < m_dwLastPicTime + m_dwTimePerFrame )
    {
        theControlPictureManager.BitBlt( &_nPicID, m_strPicPath.c_str(), &_rcDest, &m_pCurRect->rcSrc );
    }
    else
    {
        //m_dwLastPicTime = dwNowTime;
		RECT _rcSrc;
		while( dwNowTime >= m_dwLastPicTime + m_dwTimePerFrame ) //要是更新速度慢的时候直接跳帧
		{
			m_dwLastPicTime += m_dwTimePerFrame;
			_rcSrc = GetNextSrcRect();
			
		}
		theControlPictureManager.BitBlt( &_nPicID, m_strPicPath.c_str(), &_rcDest, &_rcSrc );

    }
}

const RECT& CPlaneEffect::GetNextSrcRect()
{
    static RECT rc;
    rc.left = 0;
    rc.top = 0;
    rc.right = 0;
    rc.bottom = 0;
    if( !m_pCurRect )
        return rc;

    m_pCurRect = m_pCurRect->pNext;
    return m_pCurRect->rcSrc;
}

void CPlaneEffect::Restart()
{
	if (m_rectVec.empty())
	{
		return;
	}

	m_dwLastPicTime = 0;
	m_pCurRect = &m_rectVec[0];
}