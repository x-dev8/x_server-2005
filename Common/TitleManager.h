#ifndef __TITLEMANAGER_H__
#define __TITLEMANAGER_H__
/*********************************************************************************************
                        称号管理类( 客户端使用 )
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

    void InitTitle( TitleData* pTitleData, int nCount, bool bCheckTimeLimit = false );   // 初始化称号 ( 客户端初始化的时候不需要检测时限 )
    void SaveTitle( TitleData* pTitleData, int nCount );                // 保存称号( 服务器使用 )

    unsigned short GetTitleCount() { return static_cast< unsigned short >( m_vecTitle.size() ); }
    unsigned short GetCurrentTitle() { return m_ustCurrentTitle; }
    bool SetCurrentTitle( unsigned short ustValue );
    bool AddTitle( unsigned short ustTitleID, __int64 n64AcquireTime, unsigned int nActiveTime );
    bool AddTitle( TitleData& xData );
    bool RemoveTitle( unsigned short ustTitleID );
    bool IsHaveTitle( unsigned short ustTitleID );
    TitleData* GetTitleDataByID( unsigned short ustTitleID );           // ID 查找称号
    TitleData* GetTitleDataByIndex( unsigned short uchIndex );          // 索引查找称号
    TitleData* GetTimeLimitTitleByTitleType( unsigned short ustConditionType );         // 通过称号类型过的称号
    unsigned short GetDisplaceID( unsigned short ustTitleID );        // 获得被ustTitleID的ID
    bool IsAlreadyDisplaceTitle( unsigned short ustTitleID );   // 在已经得到的称号中,是否有称号取代了stTitleID

    bool IsHaveTypeTitle( unsigned char uchType );  // 是否有某种类型的称号
    bool RemoveTypeTitle( unsigned char uchType );   // 删除某一个类型的所有称号
    void GetTypeTitle( unsigned char uchType, std::vector< unsigned short >& vecTitleID );

protected:
    TitleVector m_vecTitle;             // 称号列表
    unsigned short m_ustMaxTitleCount;

    unsigned short m_ustCurrentTitle;   // 当前ID

    RemoveVector m_vecRemoveTitle;      // 删除的称号
};

#endif