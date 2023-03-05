/*************************************************************************************
        Wmv动画播放，异步多线程读取，支持打包    by zhuomeng.hu     [3/25/2011]
*************************************************************************************/

#include <MeFoundation/MeFoundationPCH.h>
#include "Me3d/WmvPlay/AsyWmvStreamManager.h"


CAsyWmvStreamManager::CAsyWmvStreamManager()
{
    InitializeCriticalSection( &m_readerLockCS );
    m_mediaStatusDeq.clear();
    m_pReader                   = NULL;
    m_pVideoBuffer              = NULL;
    m_dwVideoOutputNum          = 0;
    m_dwVideoBufferLength       = 0;
    m_bNeedRefreshVBuffer       = false;
}

CAsyWmvStreamManager::~CAsyWmvStreamManager()
{
    if( IsPlaying() )
    {
        Close();
    }

    m_mediaStatusDeq.clear();
    DeleteCriticalSection( &m_readerLockCS );
}

bool CAsyWmvStreamManager::Open( LPDIRECT3DDEVICE9 pDevice, DWORD dwWidth, DWORD dwHeight, const char* pFile, bool bLoop, DWORD dwFadeTime, QWORD qwTime )
{
    // 循环播放不支持淡入淡出
    if( bLoop )
    {
        dwFadeTime = 0;
    }

    if( !m_bInitialized )
    {
        m_pDevice = pDevice;
        m_dwScreenWidth = dwWidth;
        m_dwScreenHeight = dwHeight;

        if( !InitializeCom() )
        {
            return false;
        }
    }

    if( OpenStream( pFile ) )
    {
        if( !SetupD3d() )
        {
            Close();
            return false;
        }
        m_bLoop         = bLoop;
        m_strFileName   = pFile;
        m_dwFadeTime    = min( dwFadeTime, m_qwTotalTime / 2 );
        m_qwCurrentTime = 0;
        m_bPlaying      = true;             // 这里子线程还未回调，先得置成播放状态

        return true;
    }
    else
    {
        Close();
        return false;
    }

    return true;
}

bool CAsyWmvStreamManager::OpenStream( const char* pFileName )
{
    if( !pFileName )
    {
        return false;
    }

    if( m_pReader )
    {
        m_pReader->Close();
        SAFE_RELEASE( m_pReader );
    }

    m_pReader = new CReader;
    IWMReader* pWMReader = NULL;
    HRESULT hr = m_pReader->Open( pFileName, &pWMReader );
    if( FAILED( hr ) )
    {
        return false;
    }

    if( !GetMediaInfo( pWMReader ) )
    {
        return false;
    }

    hr = m_pReader->Start();
    if( FAILED( hr ) )
    {
        return false;
    }

    return true;
}

bool CAsyWmvStreamManager::GetMediaInfo( IWMReader* pWMReader )
{
    if( !pWMReader )
    {
        return false;
    }

    IWMProfile* pProfile = NULL;
    HRESULT hr = pWMReader->QueryInterface( IID_IWMProfile, ( void** )&pProfile );
    if( FAILED( hr ) )
    {
        return false;
    }

    DWORD dwStreamCount( 0 );
    DWORD dwSize( 0 );
    WM_MEDIA_TYPE* pMediaType = NULL;
    IWMOutputMediaProps* pIVideoOutputProps = NULL;

    // 获取流数量
    hr = pProfile->GetStreamCount( &dwStreamCount );
    if( FAILED( hr ) )
    {
        return false;
    }

    // 遍历各个流
    for( DWORD dwIndex = 0; dwIndex < dwStreamCount; ++dwIndex )
    {
        SAFE_RELEASE( pIVideoOutputProps );
        SAFE_DELETE_ARRAY( pMediaType );

        pWMReader->GetOutputProps( dwIndex, &pIVideoOutputProps );
        hr = pIVideoOutputProps->GetMediaType( NULL, &dwSize );
        if( FAILED( hr ) )
        {
            SAFE_RELEASE( pIVideoOutputProps );
            return false;
        }

        pMediaType = ( WM_MEDIA_TYPE* ) new BYTE[ dwSize ];
        hr = pIVideoOutputProps->GetMediaType( pMediaType, &dwSize );
        if( FAILED( hr ) )
        {
            SAFE_RELEASE( pIVideoOutputProps );
            SAFE_DELETE_ARRAY( pMediaType );
            return false;
        }

        IWMStreamConfig *pConfig = NULL;
        hr = pProfile->GetStream( dwIndex, &pConfig );
        if( FAILED( hr ) )
        {
            SAFE_RELEASE( pIVideoOutputProps );
            SAFE_DELETE_ARRAY( pMediaType );
            return false;
        }

        // 为视频
        if( WMMEDIATYPE_Video == pMediaType->majortype )
        {
            m_dwVideoOutputNum = dwIndex;

            // 保存分辨率信息
            if( WMFORMAT_VideoInfo == pMediaType->formattype )
            {
                WMVIDEOINFOHEADER videoInfoHeader;
                memcpy( &videoInfoHeader, pMediaType->pbFormat, sizeof( WMVIDEOINFOHEADER ) );
                m_bitmapInfoHeader = videoInfoHeader.bmiHeader;
            }
        }

        // 为音频
        if( WMMEDIATYPE_Audio == pMediaType->majortype )
        {
            m_bHaveAudioStream = true;
        }

        SAFE_RELEASE( pConfig );
    }

    SAFE_RELEASE( pIVideoOutputProps );
    SAFE_DELETE_ARRAY( pMediaType );
    SAFE_RELEASE( pProfile );

    // 获取视频长度
    QWORD qwDuration( 0 );
    if( !GetMediaDuration( pWMReader, qwDuration ) )
    {
        return false;
    }
    m_qwTotalTime = qwDuration / m_dwMsToHNsRate;

    return true;
}

bool CAsyWmvStreamManager::GetMediaDuration( IWMReader* pReader, OUT QWORD& qwDuration )
{
    if( !pReader )
    {
        return false;
    }

    IWMHeaderInfo3* pHeaderInfo = NULL;
    HRESULT hr = pReader->QueryInterface( IID_IWMHeaderInfo3, ( void** )&pHeaderInfo );
    if( FAILED( hr ) )
    {
        return false;
    }

    WORD wStream( 0 );
    WMT_ATTR_DATATYPE dType;
    WORD wSize( 0 );

    // 先读一次，获取 Size
    hr = pHeaderInfo->GetAttributeByName( &wStream, L"Duration", &dType, NULL, &wSize );
    if( FAILED( hr ) || wSize == 0 )
    {
        SAFE_RELEASE( pHeaderInfo );
        return false;
    }

    BYTE* pValue = new BYTE[ wSize ];
    hr = pHeaderInfo->GetAttributeByName( &wStream, L"Duration", &dType, pValue, &wSize );
    if( FAILED( hr ) )
    {
        SAFE_DELETE_ARRAY( pValue );
        SAFE_RELEASE( pHeaderInfo );
        return false;
    }

    qwDuration = *( ( QWORD* )pValue );
    SAFE_DELETE_ARRAY( pValue );
    SAFE_RELEASE( pHeaderInfo );

    return true;
}

void CAsyWmvStreamManager::Close()
{
    if( m_pReader )
    {
        m_pReader->Close();
        SAFE_RELEASE( m_pReader );
    }
    SAFE_DELETE_ARRAY( m_pVideoBuffer );

    MusicEnd();

    ReleaseD3d();
    UninitializeCom();

    m_strFileName.clear();
    m_bLoop             = false;
    m_bHaveAudioStream  = false;
    m_bPlaying          = false;
    m_dwVideoOutputNum  = 0;
    m_dwFadeTime        = 0;
    m_qwCurrentTime     = 0;
    m_qwCancelTime      = 0;
}

void CAsyWmvStreamManager::Update( QWORD qwTime )
{
    // 视频开始或者结束
    bool bNeedStart( false ), bNeedClose( false );
    int nMusicStatus( 0 );
    if( TryEnterCriticalSection( &m_readerLockCS ) )
    {
        if( !m_mediaStatusDeq.empty() )
        {
            WMT_STATUS status = m_mediaStatusDeq.front();
            m_mediaStatusDeq.pop_front();
            switch( status )
            {
            case WMT_STARTED:
                {
                    m_bPlaying      = true;
                    nMusicStatus    = WMT_STARTED;      // 需要播放音频
                }
                break;
            case WMT_EOF:
                {
                    // 循环播放
                    if( m_bLoop && m_pReader )
                    {
                        bNeedStart      = true;
                        nMusicStatus    = WMT_CLOSED;   // 需要关闭音频
                    }
                    else
                    {
                        bNeedClose  = true;
                    }
                }
                break;
            case WMT_CLOSED:
                {
                    // 视频播放结束，重置逻辑变量
                    m_qwCancelTime  = 0;
                    m_qwCurrentTime = 0;
                    m_bPlaying      = false;
                }
                break;
            default:
                break;
            }
        }
        LeaveCriticalSection( &m_readerLockCS );
    }

    // 这两个接口得抽出来写，要不会造成线程死锁
    if( bNeedClose )
    {
        Close();
    }
    else if( bNeedStart )
    {
        if( FAILED( m_pReader->Start() ) )
        {
            Close();
        }
    }

    // 音频
    switch( nMusicStatus )
    {
    case WMT_STARTED:
        {
            MusicBegin();
        }
        break;
    case WMT_CLOSED:
        {
            MusicEnd();
        }
        break;
    default:
        break;
    }

    // 更新时间
    if( !IsPlaying() )
    {
        return;
    }

    // 取消视频淡出完毕
    if( m_qwCancelTime > 0 && m_qwCurrentTime > m_qwCancelTime + m_dwFadeTime )
    {
        Close();
        return;
    }
}

void CAsyWmvStreamManager::OnSample( DWORD dwOutputNum, QWORD cnsSampleTime, QWORD cnsSampleDuration, DWORD dwFlags, INSSBuffer* pSample, void* pvContext )
{
    // 子线程中回调
    if( !IsPlaying() || !pSample )
    {
        return;
    }

    m_qwCurrentTime = cnsSampleTime / m_dwMsToHNsRate;

    // 视频流
    if( m_dwVideoOutputNum == dwOutputNum )
    {
        if( dwFlags == WM_SF_CLEANPOINT )
        {
            BYTE* pBuffer = NULL;
            DWORD dwBufferLength( 0 );
            pSample->GetBufferAndLength( &pBuffer, &dwBufferLength );
            if( pBuffer && dwBufferLength > 0 )
            {
                EnterCriticalSection( &m_readerLockCS );
                {
                    m_dwVideoBufferLength = dwBufferLength;
                    SAFE_DELETE_ARRAY( m_pVideoBuffer );
                    m_pVideoBuffer = new BYTE[ m_dwVideoBufferLength ];
                    memcpy( m_pVideoBuffer, pBuffer, m_dwVideoBufferLength );
                    m_bNeedRefreshVBuffer = true;
                }
                LeaveCriticalSection( &m_readerLockCS );
            }
        }
    }
}

void CAsyWmvStreamManager::OnStatus( WMT_STATUS status )
{
    // 子线程中回调
    EnterCriticalSection( &m_readerLockCS );
    switch( status )
    {
    case WMT_STARTED:
    case WMT_EOF:
    case WMT_CLOSED:
        {
            m_mediaStatusDeq.push_back( status );
        }
        break;
    }
    LeaveCriticalSection( &m_readerLockCS );
}

void CAsyWmvStreamManager::Render()
{
    if( !IsPlaying() )
    {
        return;
    }

    // 播放视频
    if( TryEnterCriticalSection( &m_readerLockCS ) )
    {
        if( m_pVideoBuffer && m_dwVideoBufferLength > 0 )
        {
            // 由于Alpha 改变时采样不一定更新，所以Buffer还是得一直刷
            DWORD dwAlpha = GetCurrentAlpha();
            if( m_bNeedRefreshVBuffer )
            {
                FillImageBuffer( m_pVideoBuffer, m_dwVideoBufferLength, m_bitmapInfoHeader.biWidth, m_bitmapInfoHeader.biHeight );
                m_bNeedRefreshVBuffer = false;
            }
            DrawImageBuffer( m_bitmapInfoHeader.biWidth, m_bitmapInfoHeader.biHeight, m_dwScreenWidth, m_dwScreenHeight, dwAlpha );
        }
        LeaveCriticalSection( &m_readerLockCS );
    }
    else
    {
        DWORD dwAlpha = GetCurrentAlpha();
        DrawImageBuffer( m_bitmapInfoHeader.biWidth, m_bitmapInfoHeader.biHeight, m_dwScreenWidth, m_dwScreenHeight, dwAlpha );
    }
}
