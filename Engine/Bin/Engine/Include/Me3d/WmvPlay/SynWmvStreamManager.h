/*************************************************************************************
        Wmv�������ţ�ͬ�����̶߳�ȡ����֧�ִ��    by zhuomeng.hu   [2/23/2011]
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
    IWMSyncReader*          m_ISyncReader;                  // �ļ���ʽ�Ķ�ȡ����
    BYTE*                   m_pVideoBuffer;                 // ��Ƶ Buffer
    DWORD                   m_dwVideoBufferLength;          // ��Ƶ Buffer ����
    int                     m_nVideoStreamNumber;           // ��Ƶ��������
    bool                    m_bNeedRefreshVBuffer;          // �Ƿ���Ҫˢ����Ƶ��Buffer

    QWORD                   m_qwBeginTime;                  // ����ʱ��(��)����λ���룬����ʱ��
    QWORD                   m_qwVSampleTime;                // ƽ��һ֡����ʱ�䣬��λ����

};
