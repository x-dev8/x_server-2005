/*************************************************************************************
                    ��������    by zhuomeng.hu		[2/23/2011]
*************************************************************************************/

#pragma once

#include <map>
#include "Me3d/WmvPlay/AsyWmvStreamManager.h"
#include "RapidXml/MeRapidXml.h"

class CMovieManager : public Singleton<CMovieManager>
{
public:
    struct Movie
    {
        Movie();
        Movie& operator = ( const Movie& movie );

        std::string strFileName;                            // ��Ƶ�ļ���
        DWORD       dwBlackTime;                            // ����ʱ��
        DWORD       dwFadeTime;                             // ���뵭��ʱ��
        bool        bLoop;                                  // �Ƿ�ѭ������
        bool        bTop;                                   // �Ƿ������ϲ�
        bool        bDisableInput;                          // �Ƿ������������
        bool        bCanCancel;                             // �Ƿ�����ESC��ȡ��
    };

    enum MovieType
    {
        Type_None               = 0,
        Type_Login              = 1,
    };

public:
    ~CMovieManager();
    bool LoadConfig( MeXmlElement* pRoot );

    void Update();                                          // ����
    void Render( bool bTop );                               // ����
    void OnDeviceLost();                                    // ��ʧ�豸��Ҫ����
    void ResetDevice();                                     // �ָ��豸��Ҫ����

    bool OpenByType( int nType );                           // ���ļ������ nType Ϊ Type_None�����ܵ�ͬ��Close
    void Close();                                           // ֹͣ
    bool IsPlaying();                                       // �Ƿ��ڲ�����
    void ProcessESC();                                      // ȡ����������
    bool DisableInput();                                    // �Ƿ��������

protected:
    bool GetMovieByType( int nType, OUT Movie* pMovieInfo );    // ��ȡָ��������Ϣ

private:
    friend class Singleton<CMovieManager>;
    CMovieManager();

private:
    std::map< int, Movie >      m_movieMap;                 // ������Ƶ��һЩ����
    int                         m_nCurrentType;             // ���浱ǰ���ڲ��ŵĶ��� ID
    DWORD                       m_dwBlackBeginTime;         // �����Ŀ�ʼʱ�䣬����0˵�������ں���ʱ��

};
