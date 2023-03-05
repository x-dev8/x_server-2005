/*************************************************************************************
        Wmv动画播放，同步单线程读取，不支持打包    by zhuomeng.hu   [2/23/2011]
*************************************************************************************/

#pragma once

#include "Me3d/WmvPlay/WmvStreamBase.h"
#include "MeUtility/Singleton.h"


class CSynWmvStreamManager : public CWmvStreamBase, public Singleton<CSynWmvStreamManager>
{
public:
    virtual ~CSynWmvStreamManager();

    virtual bool Open( LPDIRECT3DDEVICE9 pDevice, DWORD dwWidth, DWORD dwHeight, const char* pFile, bool bLoop, DWORD dwFadeTime, QWORD qwTime = 0 );
    virtual void Close();
    virtual void Update( QWORD qwTime = 0 );
    virtual void Render();

protected:
    bool OpenFile( const char* pFileName );
    bool GetMediaDuration( const char* pFileName, OUT QWORD& qwDuration );
    
private:
    friend class Singleton<CSynWmvStreamManager>;
    CSynWmvStreamManager();

private:
    IWMSyncReader*          m_ISyncReader;                  // 文件格式的读取对象
    BYTE*                   m_pVideoBuffer;                 // 视频 Buffer
    DWORD                   m_dwVideoBufferLength;          // 视频 Buffer 长度
    int                     m_nVideoStreamNumber;           // 视频所在流数
    bool                    m_bNeedRefreshVBuffer;          // 是否需要刷新视频流Buffer

    QWORD                   m_qwBeginTime;                  // 开播时间(点)，单位毫秒，绝对时间
    QWORD                   m_qwVSampleTime;                // 平均一帧持续时间，单位毫秒

};
