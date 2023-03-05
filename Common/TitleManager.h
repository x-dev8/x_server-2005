#ifndef __TITLEMANAGER_H__
#define __TITLEMANAGER_H__
/*********************************************************************************************
                        �ƺŹ�����( �ͻ���ʹ�� )
                        Filename:     TitleManager.h 
                        MaintenanceMan Mail: lori227@live.cn
*********************************************************************************************/

#include <vector>
#include <map>

class TitleData;
class TitleManager
{
protected:
    typedef std::vector< TitleData > TitleVector;
    typedef TitleVector::iterator TitleVectorIter;

    typedef std::vector< unsigned short > RemoveVector;
    typedef RemoveVector::iterator RemoveVectorIter;

public:
    TitleManager() : m_ustCurrentTitle( 0 ), m_ustMaxTitleCount( 255 )
    {
        m_vecTitle.clear();
        m_vecRemoveTitle.clear();
    }

    void InitTitle( TitleData* pTitleData, int nCount, bool bCheckTimeLimit = false );   // ��ʼ���ƺ� ( �ͻ��˳�ʼ����ʱ����Ҫ���ʱ�� )
    void SaveTitle( TitleData* pTitleData, int nCount );                // ����ƺ�( ������ʹ�� )

    unsigned short GetTitleCount() { return static_cast< unsigned short >( m_vecTitle.size() ); }
    unsigned short GetCurrentTitle() { return m_ustCurrentTitle; }
    bool SetCurrentTitle( unsigned short ustValue );
    bool AddTitle( unsigned short ustTitleID, __int64 n64AcquireTime, unsigned int nActiveTime );
    bool AddTitle( TitleData& xData );
    bool RemoveTitle( unsigned short ustTitleID );
    bool IsHaveTitle( unsigned short ustTitleID );
    TitleData* GetTitleDataByID( unsigned short ustTitleID );           // ID ���ҳƺ�
    TitleData* GetTitleDataByIndex( unsigned short uchIndex );          // �������ҳƺ�
    TitleData* GetTimeLimitTitleByTitleType( unsigned short ustConditionType );         // ͨ���ƺ����͹��ĳƺ�
    unsigned short GetDisplaceID( unsigned short ustTitleID );        // ��ñ�ustTitleID��ID
    bool IsAlreadyDisplaceTitle( unsigned short ustTitleID );   // ���Ѿ��õ��ĳƺ���,�Ƿ��гƺ�ȡ����stTitleID

    bool IsHaveTypeTitle( unsigned char uchType );  // �Ƿ���ĳ�����͵ĳƺ�
    bool RemoveTypeTitle( unsigned char uchType );   // ɾ��ĳһ�����͵����гƺ�
    void GetTypeTitle( unsigned char uchType, std::vector< unsigned short >& vecTitleID );

protected:
    TitleVector m_vecTitle;             // �ƺ��б�
    unsigned short m_ustMaxTitleCount;

    unsigned short m_ustCurrentTitle;   // ��ǰID

    RemoveVector m_vecRemoveTitle;      // ɾ���ĳƺ�
};

#endif