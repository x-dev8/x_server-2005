/*************************************************************************************
                Wmv��������    by zhuomeng.hu		[2/23/2011]
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

    // ����Դ�ļ���Synģʽ��Ҫ���뵱ǰʱ��
    virtual bool Open( LPDIRECT3DDEVICE9 pDevice, DWORD dwWidth, DWORD dwHeight, const char* pFile, bool bLoop, DWORD dwFadeTime, QWORD qwTime = 0 ) = 0;

    // ֹͣ
    virtual void Close();

    // ���£�Synģʽ��Ҫ���뵱ǰʱ��
    virtual void Update( QWORD qwTime = 0 ) = 0;

    // ����
    virtual void Render() = 0;


    // ��ʧ�豸��Ҫ����
    virtual void OnDeviceLost();

    // �ָ��豸��Ҫ����
    virtual void ResetDevice( LPDIRECT3DDEVICE9 pDevice, DWORD dwWidth, DWORD dwHeight );

    // ȡ������
    virtual void Cancel();

    // �Ƿ��ڲ�����
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
    LPDIRECT3DDEVICE9       m_pDevice;                      // ��ǰ�豸
    DWORD                   m_dwScreenWidth;                // ��ǰ��Ļ��
    DWORD                   m_dwScreenHeight;               // ��ǰ��Ļ��

    std::string             m_strFileName;                  // ���ŵ��ļ���
    bool                    m_bLoop;                        // �Ƿ�ѭ������
    bool                    m_bPlaying;                     // �Ƿ����ڲ���
    bool                    m_bInitialized;                 // �Ƿ��ѳ�ʼ��

    bool                    m_bHaveAudioStream;             // �Ƿ�����Ƶ��
    BITMAPINFOHEADER        m_bitmapInfoHeader;             // λͼ��Ϣ

    DWORD                   m_dwFadeTime;                   // ���뵭��ʱ��(��)����λ����
    QWORD                   m_qwTotalTime;                  // ��Ƶ�ܼ�ʱ��(��)����λ����
    QWORD                   m_qwCurrentTime;                // ��ǰʱ��(��)����λ���룬�������Ƶ��ʼ��ʱ��
    QWORD                   m_qwCancelTime;                 // ȡ����Ƶ��ʱ�䣬��λ����,Ϊ0���ǲ�ȡ��

    const DWORD             m_dwMsToHNsRate;                // ������100����ı���

private:
    DWORD                   m_dwTexWidth;                   // �����
    DWORD                   m_dwTexHeight;                  // �����
    LPDIRECT3DTEXTURE9      m_pTexture;                     // ����
    LPD3DXSPRITE            m_pSprite;                      // ����

    const DWORD             m_dwMinTexSize;                 // ��С�����С
    const DWORD             m_dwMaxTexSize;                 // ��������С

    std::string             m_strLastMusicName;             // ���Ŵ��ļ�֮ǰ���ڲ��ŵ�������
    bool                    m_bLastMusicLoop;               // ���Ŵ��ļ�֮ǰ���ڲ��ŵ������Ƿ�ѭ�� (���ڻָ�)
    bool                    m_bLastMusicFade;               // ���Ŵ��ļ�֮ǰ���ڲ��ŵ������Ƿ��뵭�� (���ڻָ�)

	DWORD                   m_EscTexWidht;                  //���Ͻ�
	DWORD                   m_EscTexHight;
	LPDIRECT3DTEXTURE9      m_EscTexture;
	
    
};
