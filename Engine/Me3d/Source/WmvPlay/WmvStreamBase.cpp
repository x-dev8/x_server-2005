/*************************************************************************************
                        Wmv动画播放    by zhuomeng.hu    [2/23/2011]
*************************************************************************************/

#include "Me3d/WmvPlay/WmvStreamBase.h"
#include "MeAudio/MeAudio.h"
#include "Me3d/Engine/Engine.h"

CWmvStreamBase::CWmvStreamBase()
: m_dwMinTexSize( 0x00000001 ),
m_dwMaxTexSize( 0x80000000 ),
m_dwMsToHNsRate( 10000 )
{
    m_strFileName.clear();
    m_pDevice               = NULL;
    m_dwScreenWidth         = 0;
    m_dwScreenHeight        = 0;

    m_bLoop                 = false;
    m_bInitialized          = false;
    m_bPlaying              = false;
    m_bHaveAudioStream      = false;
    m_dwFadeTime            = 0;
    m_qwTotalTime           = 0;
    m_qwCurrentTime         = 0;
    m_qwCancelTime          = 0;

    m_pTexture              = NULL;
    m_pSprite               = NULL;
    m_dwTexWidth            = 0;
    m_dwTexHeight           = 0;

	m_EscTexWidht           = 256;                
	m_EscTexHight           = 128;
	m_EscTexture            = NULL;
}

CWmvStreamBase::~CWmvStreamBase()
{
    if( IsPlaying() )
    {
        Close();
    }
}

bool CWmvStreamBase::InitializeCom()
{
    if( m_bInitialized )
    {
        return false;
    }

    CoInitialize( NULL );

    m_bInitialized = true;
    return true;
}

void CWmvStreamBase::UninitializeCom()
{
    if( !m_bInitialized )
    {
        return;
    }

    CoUninitialize();

    m_bInitialized = false;
}

bool CWmvStreamBase::SetupD3d()
{
    if( SetupD3dVideo() && SetupD3dAudio() )
    {
        return true;
    }
    return false;
}

void CWmvStreamBase::ReleaseD3d()
{
    ReleaseD3dVideo();
    ReleaseD3dAudio();
}

bool CWmvStreamBase::SetupD3dVideo()
{
    // 视频
    if( !m_pDevice )
    {
        return false;
    }

    if( m_bitmapInfoHeader.biWidth > m_dwMaxTexSize || m_bitmapInfoHeader.biHeight > m_dwMaxTexSize
        || m_bitmapInfoHeader.biWidth < m_dwMinTexSize || m_bitmapInfoHeader.biHeight < m_dwMinTexSize )
    {
        return false;
    }

    m_dwTexWidth = m_bitmapInfoHeader.biWidth;
    m_dwTexHeight = m_bitmapInfoHeader.biHeight;

    SAFE_RELEASE( m_pTexture );
	
    HRESULT hr = m_pDevice->CreateTexture( m_dwTexWidth, m_dwTexHeight, 1, 0, D3DFMT_X8R8G8B8, D3DPOOL_MANAGED, &m_pTexture, NULL );
    if( FAILED( hr ) )
    {
        return false;
    }

	SAFE_RELEASE(m_EscTexture);
	D3DXCreateTextureFromFile(m_pDevice,"..\\Data\\Movies\\EscMovie.dds",&m_EscTexture);
// 	if( !m_EscTexture )
// 	{
// 		return false;
// 	}

    SAFE_RELEASE( m_pSprite );
    hr = D3DXCreateSprite( m_pDevice, &m_pSprite );
    if( FAILED( hr ) )
    {
        return false;
    }

    return true;
}

bool CWmvStreamBase::SetupD3dAudio()
{
    return true;
}

void CWmvStreamBase::ReleaseD3dVideo()
{
    SAFE_RELEASE( m_pTexture );
    SAFE_RELEASE( m_pSprite );
	SAFE_RELEASE(m_EscTexture);

    m_pDevice = NULL;
}

void CWmvStreamBase::ReleaseD3dAudio()
{
}

void CWmvStreamBase::OnDeviceLost()
{
    if( IsPlaying() )
    {
        ReleaseD3dVideo();
    }
}

void CWmvStreamBase::ResetDevice( LPDIRECT3DDEVICE9 pDevice, DWORD dwWidth, DWORD dwHeight )
{
    if( IsPlaying() )
    {
        m_pDevice = pDevice;
        m_dwScreenWidth = dwWidth;
        m_dwScreenHeight = dwHeight;

        SetupD3dVideo();
    }
}

void CWmvStreamBase::Cancel()
{
    if( !IsPlaying() )
    {
        return;
    }

    // 循环播放的 或者 不淡入淡出的直接停止
    if( m_bLoop || m_dwFadeTime == 0 )
    {
        Close();
        return;
    }

    // 已经被取消 或者 还未淡入完成 或者 在淡出时间内视频就要播完的 不响应取消
    if( m_qwCancelTime > 0 || m_qwCurrentTime <= m_dwFadeTime || m_qwTotalTime - m_qwCurrentTime <= m_dwFadeTime )
    {
        return;
    }

    // 记录取消时间
    m_qwCancelTime = m_qwCurrentTime;
}

bool CWmvStreamBase::IsPlaying()
{
    return m_bPlaying;
}

void CWmvStreamBase::Close()
{
}

DWORD CWmvStreamBase::GetCurrentAlpha()
{
    DWORD dwAlpha( 255 );
    if( m_dwFadeTime > 0 )
    {
        // 超时将Alpha置为0
        if( m_qwCurrentTime >= m_qwTotalTime )
        {
            dwAlpha = 0;
        }
        // 淡入
        else if( m_qwCurrentTime < m_dwFadeTime )
        {
            dwAlpha = dwAlpha * m_qwCurrentTime / m_dwFadeTime;
        }
        // 取消的淡出
        else if( m_qwCancelTime > 0 && m_qwCurrentTime > m_qwCancelTime )
        {
            if( m_qwCurrentTime - m_qwCancelTime <= m_dwFadeTime )
            {
                dwAlpha = dwAlpha * ( ( QWORD )m_dwFadeTime + m_qwCancelTime - m_qwCurrentTime ) / m_dwFadeTime;
            }
            else
            {
                dwAlpha = 0;
            }
        }
        // 结束的淡出
        else if( m_qwTotalTime - m_qwCurrentTime < m_dwFadeTime )
        {
            dwAlpha = dwAlpha * ( m_qwTotalTime - m_qwCurrentTime ) / m_dwFadeTime;
        }
    }
    return dwAlpha;
}

bool CWmvStreamBase::FillImageBuffer( BYTE* pBuffer, DWORD dwBufLength, int nSrcWidth, int nSrcHeight )
{
    if( !pBuffer || !m_pTexture )
    {
        return false;
    }

    if( nSrcWidth * nSrcHeight * 3 != dwBufLength || m_dwTexWidth < nSrcWidth || m_dwTexHeight < nSrcHeight )
    {
        assert( false && "Image Buffer Not Match!" );
        return false;
    }

    D3DLOCKED_RECT d3dlr;
    HRESULT hr = m_pTexture->LockRect( 0, &d3dlr, 0, 0 );
    if( FAILED( hr ) )
    {
        return false;
    }

    // 1像素 3 BYTE
    for( DWORD i = 0; i < dwBufLength; i += 3 )
    {
        DWORD dwBlue    = pBuffer[ i + 0 ];
        DWORD dwGreen   = pBuffer[ i + 1 ];
        DWORD dwRed     = pBuffer[ i + 2 ];
        DWORD dwY = nSrcHeight - 1 - i / 3 / nSrcWidth;
        DWORD dwX = i / 3 % nSrcWidth;
        ( ( DWORD* )d3dlr.pBits )[ dwY * m_dwTexWidth + dwX ] = D3DCOLOR_ARGB( 255, dwRed, dwGreen, dwBlue );
    }
    hr = m_pTexture->UnlockRect( 0 );

    if( FAILED( hr ) )
    {
        return false;
    }

    return true;
}

typedef struct 
{
	D3DXVECTOR4 p;
	DWORD color;
	float u, v;
} UVVertex2D;

bool CWmvStreamBase::DrawImageBuffer( int nSrcWidth, int nSrcHeight, int nDestWidth, int nDestHeight, DWORD dwAlpha )
{
    IRenderer* RI = GetEngine()->GetRenderer();
    if( !RI || !m_pSprite || !m_pTexture )
    {
        return false;
    }

    RI->SetRenderState( D3DRS_ZENABLE, FALSE );
    RI->Commit();

    if( FAILED( RI->BeginScene() ) )
    {
        return false;
    }
    
    if( SUCCEEDED( m_pSprite->Begin( D3DXSPRITE_ALPHABLEND ) ) )
    {
        // 是否需要缩放
        if( nSrcWidth != nDestWidth || nSrcHeight != nDestHeight )
        {
            D3DXMATRIX M;
            D3DXMatrixIdentity( &M );
            M._11 = ( double )nDestWidth / ( double )nSrcWidth;
            M._22 = ( double )nDestHeight / ( double )nSrcHeight;
            m_pSprite->SetTransform( &M );
        }
        RECT rc;
        rc.left = 0;
        rc.right = nSrcWidth;
        rc.top = 0;
        rc.bottom = nSrcHeight;
        m_pSprite->Draw( m_pTexture, &rc, NULL, NULL, ( dwAlpha << 24 ) | 0x00ffffff );
        m_pSprite->End();

    }

	DWORD alpha = 0;
	if (m_qwCurrentTime > 2000 )
		alpha = GetCurrentAlpha();
	if (m_EscTexture)
	{
		UVVertex2D vertex[4];
		vertex[0].p = D3DXVECTOR4( 0 , 0, 0, 1 );
		vertex[0].u = 0.f;
		vertex[0].v = 0.f;
		vertex[0].color = D3DCOLOR_ARGB(alpha,255,255,255);

		vertex[1].p = D3DXVECTOR4( m_EscTexWidht , 0, 0, 1 );
		vertex[1].u = 1.f;
		vertex[1].v = 0.f;
		vertex[1].color = D3DCOLOR_ARGB(alpha,255,255,255);

		vertex[2].p = D3DXVECTOR4( 0 , m_EscTexHight, 0, 1 );
		vertex[2].u = 0.f;
		vertex[2].v = 1.f;
		vertex[2].color = D3DCOLOR_ARGB(alpha,255,255,255);

		vertex[3].p = D3DXVECTOR4( m_EscTexWidht , m_EscTexHight, 0.f, 1 );
		vertex[3].u = 1.f;
		vertex[3].v = 1.f;
		vertex[3].color = D3DCOLOR_ARGB(alpha,255,255,255);


		m_pDevice->SetFVF(D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1);
		m_pDevice->SetTexture( 0, m_EscTexture );
		m_pDevice->DrawPrimitiveUP( D3DPT_TRIANGLESTRIP, 2, vertex, sizeof( UVVertex2D ) );
	}
	

    RI->EndScene();

    return true;
}

void CWmvStreamBase::MusicBegin()
{
    if( !m_bHaveAudioStream )
    {
        return;
    }

    // 有音频流则需要保存原来的场景音乐
    GSound.Paused( true );
	//GMusic.Paused(true);
    if( GMusic.GetCurrentMusicInfo( m_strLastMusicName, m_bLastMusicLoop, m_bLastMusicFade ) )
    {
        // 如果之前的音乐不循环播放 或者 视频本身循环播放，就不用恢复
        if( !m_bLastMusicLoop || m_bLoop )
        {
            m_strLastMusicName.clear();
        }
    }
    GMusic.PlayMusic( m_strFileName.c_str(), FALSE, TRUE );
}

void CWmvStreamBase::MusicEnd()
{
    if( !m_bHaveAudioStream )
    {
        return;
    }

    // 有音频流则需要恢复原来的场景音乐
    GSound.Paused( false );
	//GMusic.Paused(false);
    if( m_strLastMusicName.empty() )
    {
        GMusic.StopMusic();
    }
    else
    {
        GMusic.PlayMusic( m_strLastMusicName.c_str(), m_bLastMusicLoop, m_bLastMusicFade );
    }
}
