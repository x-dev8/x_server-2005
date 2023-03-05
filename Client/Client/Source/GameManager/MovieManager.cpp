/*************************************************************************************
                    动画播放    by zhuomeng.hu		[2/23/2011]
*************************************************************************************/

#include "MovieManager.h"
#include "tstring.h"
#include "GameMain.h"

extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;

CMovieManager::Movie::Movie()
{
    strFileName.clear();
    dwFadeTime      = 0;
    dwBlackTime     = 0;
    bLoop           = false;
    bTop            = false;
    bDisableInput   = false;
    bCanCancel      = false;
}

CMovieManager::Movie& CMovieManager::Movie::operator = ( const CMovieManager::Movie& movie )
{
    strFileName     = movie.strFileName;
    dwFadeTime      = movie.dwFadeTime;
    dwBlackTime     = movie.dwBlackTime;
    bLoop           = movie.bLoop;
    bTop            = movie.bTop;
    bDisableInput   = movie.bDisableInput;
    bCanCancel      = movie.bCanCancel;

    return *this;
}

CMovieManager::CMovieManager()
{
    m_movieMap.clear();
    m_nCurrentType = Type_None;
    m_dwBlackBeginTime = 0;
}

CMovieManager::~CMovieManager()
{
    m_movieMap.clear();
}

bool CMovieManager::LoadConfig( MeXmlElement* pRoot )
{
    if( !pRoot )
    {
        return false;
    }

    MeXmlElement* pMovieSet = pRoot->FirstChildElement( "MovieSet" );
    if( !pMovieSet )
    {
        return false;
    }

    m_movieMap.clear();
    MeXmlElement* pMovie = pMovieSet->FirstChildElement( "Movie" );
    while( pMovie )
    {
        Movie movieInfo;
        int nId( -1 );
        if( pMovie->Attribute( "Id", &nId ) == NULL )
        {
            return false;
        }

        const char* pFile = pMovie->Attribute( "FilePath" );
        if( !pFile )
        {
            return false;
        }
        movieInfo.strFileName = std::string( GetRootPath() ) + "\\" + Common::_tstring::toNarrowString( Common::_tstring::UTF8towcs( pFile ).c_str() );

        int nTemp( -1 );
        if( pMovie->Attribute( "IsLoop", &nTemp ) == NULL )
        {
            return false;
        }
        movieInfo.bLoop = nTemp;

        if( pMovie->Attribute( "IsTop", &nTemp ) == NULL )
        {
            return false;
        }
        movieInfo.bTop = nTemp;

        if( pMovie->Attribute( "IsDisableInput", &nTemp ) == NULL )
        {
            return false;
        }
        movieInfo.bDisableInput = nTemp;

        if( pMovie->Attribute( "CanCancel", &nTemp ) == NULL )
        {
            return false;
        }
        movieInfo.bCanCancel = nTemp;

        if( pMovie->Attribute( "BlackTime", &nTemp ) == NULL )
        {
            return false;
        }
        movieInfo.dwBlackTime = nTemp;

        if( pMovie->Attribute( "FadeTime", &nTemp ) == NULL )
        {
            return false;
        }
        movieInfo.dwFadeTime = nTemp;

        if( nId < 0 || nTemp < 0 || m_movieMap.count( nId ) > 0 )
        {
            return false;
        }
        m_movieMap.insert( make_pair( nId, movieInfo ) );

        pMovie = pMovie->NextSiblingElement();
    }

    return true;
}

void CMovieManager::Update()
{
    if( IsPlaying() && m_dwBlackBeginTime > 0 )
    {
        // 黑屏时间
        Movie movieInfo;
        if( GetMovieByType( m_nCurrentType, &movieInfo ) )
        {
            // 视频开始 (如果有淡入淡出，则黑屏还未结束)
            if( HQ_TimeGetTime() > m_dwBlackBeginTime + movieInfo.dwBlackTime && !CAsyWmvStreamManager::Instance()->IsPlaying() )
            {
                CAsyWmvStreamManager::Instance()->Open( theHeroGame.GetD3DDevice(), SCREEN_WIDTH, SCREEN_HEIGHT,
                    movieInfo.strFileName.c_str(), movieInfo.bLoop, movieInfo.dwFadeTime, HQ_TimeGetTime() );
            }

            // 视频播放改为异步多线程后，Open时主线程仍在渲染，所以黑屏时间额外加一秒 (如果2，3秒的视频配了黑屏时间就可能会有问题)
            DWORD dwBlackTime = movieInfo.dwBlackTime + movieInfo.dwFadeTime + 1000;

            // 黑屏结束
            if( HQ_TimeGetTime() > m_dwBlackBeginTime + dwBlackTime )
            {
                UiDrawer::StartFillFullScreen( 1, false );
                m_dwBlackBeginTime = 0;
            }
        }
    }
    
    // 视频时间
    CAsyWmvStreamManager::Instance()->Update( HQ_TimeGetTime() );
}

void CMovieManager::Render( bool bTop )
{
    if( !IsPlaying() )
    {
        return;
    }

    Movie movieInfo;
    if( !GetMovieByType( m_nCurrentType, &movieInfo ) )
    {
        return;
    }

    if( bTop == movieInfo.bTop )
    {
        CAsyWmvStreamManager::Instance()->Render();
    }
}

void CMovieManager::OnDeviceLost()
{
    CAsyWmvStreamManager::Instance()->OnDeviceLost();
}

void CMovieManager::ResetDevice()
{
    CAsyWmvStreamManager::Instance()->ResetDevice( theHeroGame.GetD3DDevice(), SCREEN_WIDTH, SCREEN_HEIGHT );
}

bool CMovieManager::OpenByType( int nType )
{
    if( nType == Type_None )
    {
        Close();
        return true;
    }
    else
    {
        // 有没有此 Type
        Movie movieInfo;
        if( !GetMovieByType( nType, &movieInfo ) )
        {
            return false;
        }

        bool bRet( false );
        // 没有黑屏的直接播放
        if( movieInfo.dwBlackTime == 0 )
        {
            bRet = CAsyWmvStreamManager::Instance()->Open( theHeroGame.GetD3DDevice(), SCREEN_WIDTH, SCREEN_HEIGHT,
                movieInfo.strFileName.c_str(), movieInfo.bLoop, movieInfo.dwFadeTime, HQ_TimeGetTime() );
        }
        else
        {
            UiDrawer::StartFillFullScreen( movieInfo.dwBlackTime, true, 0, 255 );
            m_dwBlackBeginTime = HQ_TimeGetTime();
            bRet = true;
        }

        if( bRet )
        {
            m_nCurrentType = nType;
        }
        return bRet;
    }

    return true;
}

void CMovieManager::Close()
{
    CAsyWmvStreamManager::Instance()->Close();
    m_nCurrentType = Type_None;
    m_dwBlackBeginTime = 0;
}

bool CMovieManager::IsPlaying()
{
    if( m_dwBlackBeginTime > 0 )
    {
        return true;
    }

    return CAsyWmvStreamManager::Instance()->IsPlaying();
}

void CMovieManager::ProcessESC()
{
    if( !IsPlaying() )
    {
        return;
    }

    Movie movieInfo;
    if( GetMovieByType( m_nCurrentType, &movieInfo ) )
    {
        if( movieInfo.bCanCancel )
        {
            // 黑屏时不能取消，只能等时间过
            if( m_dwBlackBeginTime > 0 )
            {
                return;
            }

            CAsyWmvStreamManager::Instance()->Cancel();
        }
    }
}

bool CMovieManager::DisableInput()
{
    if( !IsPlaying() )
    {
        return false;
    }

    Movie movieInfo;
    if( GetMovieByType( m_nCurrentType, &movieInfo ) )
    {
        if( !movieInfo.bDisableInput )
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    return true;
}

bool CMovieManager::GetMovieByType( int nType, OUT Movie* pMovieInfo )
{
    if( !pMovieInfo )
    {
        return false;
    }

    if( m_movieMap.count( nType ) == 0 )
    {
        return false;
    }

    *pMovieInfo = m_movieMap.find( nType )->second;
    return true;
}
