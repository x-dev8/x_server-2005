/*************************************************************************************
                Wmv动画播放    by zhuomeng.hu		[2/23/2011]
*************************************************************************************/

#pragma once

#include "wmsdk.h"
#include "d3dx9.h"
#include <string>

#ifndef SAFE_DELETE
#define SAFE_DELETE( p )				{ if( p ){ delete ( p ); ( p ) = NULL; } }
#endif

#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY( p )			{ if( p ) { delete[] ( p );   ( p ) = NULL; } }
#endif
#ifndef SAFE_RELEASE
#define SAFE_RELEASE( p )				{ if( p ) { ( p )->Release(); ( p ) = NULL; } }
#endif

#ifndef SAFE_DESTROY
#define SAFE_DESTROY( p )				{ if( p ){ ( p )->Destroy(); } }
#endif

#ifndef SAFE_DESTROY_AND_DELETE
#define SAFE_DESTROY_AND_DELETE( p )	{ if( p ){ ( p )->Destroy(); delete ( p ); ( p ) = NULL; } }
#endif

#ifndef ASSERT_NULL
#define ASSERT_NULL( p )				{ Assert( ( p ) == NULL ); }
#endif

#ifndef ASSERT_NOTNULL
#define ASSERT_NOTNULL( p )				{ Assert( ( p ) != NULL ); }
#endif

class CWmvStreamBase
{
public:
    CWmvStreamBase();
    virtual ~CWmvStreamBase();

    // 打开资源文件，Syn模式需要传入当前时间
    virtual bool Open( LPDIRECT3DDEVICE9 pDevice, DWORD dwWidth, DWORD dwHeight, const char* pFile, bool bLoop, DWORD dwFadeTime, QWORD qwTime = 0 ) = 0;

    // 停止
    virtual void Close();

    // 更新，Syn模式需要传入当前时间
    virtual void Update( QWORD qwTime = 0 ) = 0;

    // 播放
    virtual void Render() = 0;


    // 丢失设备需要调用
    virtual void OnDeviceLost();

    // 恢复设备需要调用
    virtual void ResetDevice( LPDIRECT3DDEVICE9 pDevice, DWORD dwWidth, DWORD dwHeight );

    // 取消播放
    virtual void Cancel();

    // 是否在播放中
    virtual bool IsPlaying();

protected:
    virtual bool InitializeCom();
    virtual void UninitializeCom();

    virtual bool SetupD3d();
    virtual void ReleaseD3d();
    virtual bool SetupD3dVideo();
    virtual bool SetupD3dAudio();
    virtual void ReleaseD3dVideo();
    virtual void ReleaseD3dAudio();

    virtual DWORD GetCurrentAlpha();
    virtual bool FillImageBuffer( BYTE* pBuffer, DWORD dwBufLength, int nSrcWidth, int nSrcHeight );
    virtual bool DrawImageBuffer( int nSrcWidth, int nSrcHeight, int nDestWidth, int nDestHeight, DWORD dwAlpha );

    virtual void MusicBegin();
    virtual void MusicEnd();

protected:
    LPDIRECT3DDEVICE9       m_pDevice;                      // 当前设备
    DWORD                   m_dwScreenWidth;                // 当前屏幕宽
    DWORD                   m_dwScreenHeight;               // 当前屏幕高

    std::string             m_strFileName;                  // 播放的文件名
    bool                    m_bLoop;                        // 是否循环播放
    bool                    m_bPlaying;                     // 是否正在播放
    bool                    m_bInitialized;                 // 是否已初始化

    bool                    m_bHaveAudioStream;             // 是否有音频流
    BITMAPINFOHEADER        m_bitmapInfoHeader;             // 位图信息

    DWORD                   m_dwFadeTime;                   // 淡入淡出时间(段)，单位毫秒
    QWORD                   m_qwTotalTime;                  // 视频总计时间(段)，单位毫秒
    QWORD                   m_qwCurrentTime;                // 当前时间(点)，单位毫秒，相对于视频开始的时间
    QWORD                   m_qwCancelTime;                 // 取消视频的时间，单位毫秒,为0就是不取消

    const DWORD             m_dwMsToHNsRate;                // 毫秒与100纳秒的比例

private:
    DWORD                   m_dwTexWidth;                   // 纹理宽
    DWORD                   m_dwTexHeight;                  // 纹理高
    LPDIRECT3DTEXTURE9      m_pTexture;                     // 纹理
    LPD3DXSPRITE            m_pSprite;                      // 精灵

    const DWORD             m_dwMinTexSize;                 // 最小纹理大小
    const DWORD             m_dwMaxTexSize;                 // 最大纹理大小

    std::string             m_strLastMusicName;             // 播放此文件之前正在播放的音乐名
    bool                    m_bLastMusicLoop;               // 播放此文件之前正在播放的音乐是否循环 (用于恢复)
    bool                    m_bLastMusicFade;               // 播放此文件之前正在播放的音乐是否淡入淡出 (用于恢复)

	DWORD                   m_EscTexWidht;                  //左上角
	DWORD                   m_EscTexHight;
	LPDIRECT3DTEXTURE9      m_EscTexture;
	
    
};
