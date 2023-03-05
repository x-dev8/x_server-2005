/*************************************************************************************
       Wmv动画播放，同步单线程读取，不支持打包    by zhuomeng.hu    [2/23/2011]
*************************************************************************************/

#include "Me3d/WmvPlay/SynWmvStreamManager.h"
#include "tstring.h"

CSynWmvStreamManager::CSynWmvStreamManager()
{
    m_bNeedRefreshVBuffer   = false;
    m_qwVSampleTime         = 0;
    m_qwBeginTime           = 0;

    m_ISyncReader           = NULL;
    m_nVideoStreamNumber    = 0;
    m_pVideoBuffer          = NULL;
    m_dwVideoBufferLength   = 0;
}

CSynWmvStreamManager::~CSynWmvStreamManager()
{
    if( IsPlaying() )
    {
        Close();
    }
}

bool CSynWmvStreamManager::Open( LPDIRECT3DDEVICE9 pDevice, DWORD dwWidth, DWORD dwHeight, const char* pFile, bool bLoop, DWORD dwFadeTime, QWORD qwTime )
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

    if( OpenFile( pFile ) )
    {
        if( !SetupD3d() )
        {
            Close();
            return false;
        }
        m_bLoop = bLoop;
        m_bPlaying = true;
        m_strFileName = pFile;
        m_dwFadeTime = min( dwFadeTime, m_qwTotalTime / 2 );
        m_qwBeginTime = qwTime;
        m_qwCurrentTime = 0;
        m_qwCancelTime = 0;
        MusicBegin();

        return true;
    }
    else
    {
        Close();
        return false;
    }

    return true;
}

void CSynWmvStreamManager::Close()
{
    SAFE_DELETE_ARRAY( m_pVideoBuffer );
    SAFE_RELEASE( m_ISyncReader );

    MusicEnd();

    ReleaseD3d();
    UninitializeCom();

    m_strFileName.clear();
    m_bPlaying          = false;
    m_bLoop             = false;
    m_bHaveAudioStream  = false;
    m_dwFadeTime        = 0;
    m_qwTotalTime       = 0;
    m_qwVSampleTime     = 0;
    m_qwBeginTime       = 0;
    m_qwCurrentTime     = 0;
    m_qwCancelTime      = 0;
}

void CSynWmvStreamManager::Update( QWORD qwTime )
{
    if( !IsPlaying() )
    {
        return;
    }

    // 视频结束
    if( qwTime - m_qwBeginTime > m_qwBeginTime + m_qwTotalTime )
    {
        if( m_bLoop )
        {
            Open( m_pDevice, m_dwScreenWidth, m_dwScreenHeight, m_strFileName.c_str(), true, m_dwFadeTime, qwTime );
        }
        else
        {
            Close();
            return;
        }
    }

    QWORD qwSampleTime( 0 );
    QWORD qwSampleDuration( 0 );
    DWORD dwFlags( 0 );
    INSSBuffer* pINSSBuffer = NULL;
    HRESULT hr = S_OK;

    // 获取此帧视频信息
    while( SUCCEEDED( hr ) && ( m_qwCurrentTime == 0 || m_qwBeginTime + m_qwCurrentTime < qwTime - m_qwVSampleTime ) )
    {
        SAFE_RELEASE( pINSSBuffer );
        hr = m_ISyncReader->GetNextSample( m_nVideoStreamNumber, &pINSSBuffer, &qwSampleTime, &qwSampleDuration, &dwFlags, NULL, NULL );
        m_qwCurrentTime = qwSampleTime / m_dwMsToHNsRate;

        // 视频被取消后，过了淡出时间就关闭
        if( m_qwCancelTime > 0 && m_qwCurrentTime > m_qwCancelTime + m_dwFadeTime )
        {
            Close();
            return;
        }
    }

    // 视频流已读完 (理论上不应该进)
    if( hr == NS_E_NO_MORE_SAMPLES )
    {
        if( m_bLoop )
        {
            Open( m_pDevice, m_dwScreenWidth, m_dwScreenHeight, m_strFileName.c_str(), true, m_dwFadeTime, qwTime );
        }
        else
        {
            Close();
            return;
        }
    }

    if( SUCCEEDED( hr ) && pINSSBuffer )
    {
        if( dwFlags == WM_SF_CLEANPOINT )
        {
            BYTE* pBuffer = NULL;
            DWORD dwBufferLength( 0 );
            pINSSBuffer->GetBufferAndLength( &pBuffer, &dwBufferLength );
            if( pBuffer && dwBufferLength > 0 )
            {
                m_dwVideoBufferLength = dwBufferLength;
                SAFE_DELETE_ARRAY( m_pVideoBuffer );
                m_pVideoBuffer = new BYTE[ m_dwVideoBufferLength ];
                memcpy( m_pVideoBuffer, pBuffer, m_dwVideoBufferLength );
                m_bNeedRefreshVBuffer = true;
            }
        }
        SAFE_RELEASE( pINSSBuffer );
    }
}

void CSynWmvStreamManager::Render()
{
    if( !IsPlaying() )
    {
        return;
    }

    // 播放视频
    if( m_pVideoBuffer && m_dwVideoBufferLength > 0 )
    {
        if( m_bNeedRefreshVBuffer )
        {
            FillImageBuffer( m_pVideoBuffer, m_dwVideoBufferLength, m_bitmapInfoHeader.biWidth, m_bitmapInfoHeader.biHeight );
            m_bNeedRefreshVBuffer = false;
        }
        DWORD dwAlpha = GetCurrentAlpha();
        DrawImageBuffer( m_bitmapInfoHeader.biWidth, m_bitmapInfoHeader.biHeight, m_dwScreenWidth, m_dwScreenHeight, dwAlpha );
    }
}

bool CSynWmvStreamManager::OpenFile( const char* pFileName )
{
    if( !pFileName )
    {
        return false;
    }

    std::wstring strFileName = Common::_tstring::toWideString( pFileName );
    HRESULT hr;

    // 1. 创建读取对象
    SAFE_RELEASE( m_ISyncReader );
    hr = WMCreateSyncReader( NULL, 0, &m_ISyncReader );
    if( hr != S_OK )
    {
        return false;
    }

    // 2. 打开文件
    hr = m_ISyncReader->Open( strFileName.c_str() );
    if( hr != S_OK )
    {
        return false;
    }

    // 3. 分析文件中的输出流 ( wmv文件中的流从1开始，输出数从0开始 )
    DWORD dwSize( 0 );
    DWORD dwOutputCount( 0 );
    int nVideoOutputNumber( 0 );
    int nAudioOutputNumber( 0 );
    WM_MEDIA_TYPE* pMediaType = NULL;
    IWMOutputMediaProps* pIVideoOutputProps = NULL;

    m_ISyncReader->GetOutputCount( &dwOutputCount );
    m_bHaveAudioStream = false;

    for( int i = 0; i < dwOutputCount; ++i )
    {
        SAFE_RELEASE( pIVideoOutputProps );
        SAFE_DELETE_ARRAY( pMediaType );

        m_ISyncReader->GetOutputProps( i, &pIVideoOutputProps );
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

        // 为视频
        if( WMMEDIATYPE_Video == pMediaType->majortype )
        {
            nVideoOutputNumber = i;
            m_ISyncReader->GetStreamNumberForOutput( nVideoOutputNumber, ( WORD* )&m_nVideoStreamNumber );
            if( WMFORMAT_VideoInfo == pMediaType->formattype )
            {
                WMVIDEOINFOHEADER videoInfoHeader;
                memcpy( &videoInfoHeader, pMediaType->pbFormat, sizeof( WMVIDEOINFOHEADER ) );
                m_bitmapInfoHeader = videoInfoHeader.bmiHeader;
                m_qwVSampleTime = videoInfoHeader.AvgTimePerFrame / m_dwMsToHNsRate;
            }
        }

        // 为音频
        if( WMMEDIATYPE_Audio == pMediaType->majortype )
        {
            m_bHaveAudioStream = true;
        }
    }

    SAFE_RELEASE( pIVideoOutputProps );
    SAFE_DELETE_ARRAY( pMediaType );

    // 4. 设置正确的 Sample Duration
    BYTE* pValue = new BYTE[5];
    strcpy( ( char* )pValue, "TRUE" );
    hr = m_ISyncReader->SetOutputSetting( nVideoOutputNumber, g_wszVideoSampleDurations, WMT_TYPE_BOOL, pValue, sizeof( pValue ) );
    SAFE_DELETE_ARRAY( pValue );
    if( FAILED( hr ) )
    {
        return false;
    }

    // 5. 设置为读取未压缩数据
    hr = m_ISyncReader->SetReadStreamSamples( m_nVideoStreamNumber, FALSE );
    if( FAILED( hr ) )
    {
        return false;
    }

    // 6. 获取视频长度
    QWORD qwDuration( 0 );
    if( !GetMediaDuration( pFileName, qwDuration ) )
    {
        return false;
    }
    m_qwTotalTime = qwDuration / m_dwMsToHNsRate;

    return true;
}

bool CSynWmvStreamManager::GetMediaDuration( const char* pFileName, OUT QWORD& qwDuration )
{
    if( !pFileName )
    {
        return false;
    }

    std::wstring strFileName = Common::_tstring::toWideString( pFileName );

    IWMMetadataEditor* pEditor;
    HRESULT hr = WMCreateEditor( &pEditor );
    if( hr != S_OK )
    {
        return false;
    }

    hr = pEditor->Open( strFileName.c_str() );
    if( FAILED( hr ) )
    {
        return false;
    }

    IWMHeaderInfo3* pHeaderInfo = NULL;
    hr = pEditor->QueryInterface( IID_IWMHeaderInfo3, ( void** )&pHeaderInfo );
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
        SAFE_RELEASE( pEditor );
        return false;
    }

    BYTE* pValue = new BYTE[ wSize ];
    hr = pHeaderInfo->GetAttributeByName( &wStream, L"Duration", &dType, pValue, &wSize );
    if( FAILED( hr ) )
    {
        SAFE_DELETE_ARRAY( pValue );
        SAFE_RELEASE( pHeaderInfo );
        SAFE_RELEASE( pEditor );
        return false;
    }

    qwDuration = *( ( QWORD* )pValue );

    SAFE_DELETE_ARRAY( pValue );
    SAFE_RELEASE( pHeaderInfo );
    SAFE_RELEASE( pEditor );

    return true;
}
