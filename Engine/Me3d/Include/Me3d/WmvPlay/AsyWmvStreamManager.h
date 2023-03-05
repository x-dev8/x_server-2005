/*************************************************************************************
        Wmv�������ţ��첽���̶߳�ȡ��֧�ִ��    by zhuomeng.hu     [3/25/2011]
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

    CRITICAL_SECTION        m_readerLockCS;                     // ���̼߳���
    CReader*                m_pReader;                          // Buffer��ʽ�Ķ�ȡ����
    DWORD                   m_dwVideoOutputNum;                 // ��Ƶ������
    DWORD                   m_dwAudioOutputNum;                 // ��Ƶ������
    bool                    m_bNeedRefreshVBuffer;              // �Ƿ���Ҫˢ����Ƶ��Buffer

    BYTE*                   m_pVideoBuffer;                     // ��Ƶ Buffer
    DWORD                   m_dwVideoBufferLength;              // ��Ƶ Buffer ����

    // �ö���������״̬�ı䣬�������߳̿��ܻ�û�յ�ĳЩ״̬�ı䣬���µײ�������ԣ��޷������ͷ�
    MediaStatusQue          m_mediaStatusDeq;

};
