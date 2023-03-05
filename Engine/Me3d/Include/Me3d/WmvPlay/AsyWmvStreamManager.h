/*************************************************************************************
        Wmv动画播放，异步多线程读取，支持打包    by zhuomeng.hu     [3/25/2011]
*************************************************************************************/

#pragma once

#include "Me3d/WmvPlay/WmvStreamBase.h"
#include "Singleton.h"
#include "Me3d/WmvPlay/Reader.h"
#include <deque>


class CAsyWmvStreamManager : public CWmvStreamBase, public Singleton<CAsyWmvStreamManager>
{
public:
    virtual ~CAsyWmvStreamManager();

    virtual bool Open( LPDIRECT3DDEVICE9 pDevice, DWORD dwWidth, DWORD dwHeight, const char* pFile, bool bLoop, DWORD dwFadeTime, QWORD qwTime = 0 );
    virtual void Close();
    virtual void Update( QWORD qwTime = 0 );
    virtual void Render();

protected:
    bool OpenStream( const char* pFileName );
    bool GetMediaInfo( IWMReader* pReader );
    bool GetMediaDuration( IWMReader* pReader, OUT QWORD& qwDuration );
    void OnSample( DWORD dwOutputNum, QWORD cnsSampleTime, QWORD cnsSampleDuration, DWORD dwFlags, INSSBuffer* pSample, void* pvContext );
    void OnStatus( WMT_STATUS status );

private:
    friend class CReader;
    friend class Singleton<CAsyWmvStreamManager>;
    CAsyWmvStreamManager();

private:
    typedef std::deque< WMT_STATUS > MediaStatusQue;

    CRITICAL_SECTION        m_readerLockCS;                     // 多线程加锁
    CReader*                m_pReader;                          // Buffer格式的读取对象
    DWORD                   m_dwVideoOutputNum;                 // 视频所在流
    DWORD                   m_dwAudioOutputNum;                 // 音频所在流
    bool                    m_bNeedRefreshVBuffer;              // 是否需要刷新视频流Buffer

    BYTE*                   m_pVideoBuffer;                     // 视频 Buffer
    DWORD                   m_dwVideoBufferLength;              // 视频 Buffer 长度

    // 用队列来保存状态改变，否则主线程可能会没收到某些状态改变，导致底层计数不对，无法正常释放
    MediaStatusQue          m_mediaStatusDeq;

};
