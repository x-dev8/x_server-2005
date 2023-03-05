#ifndef __RELATION_H__
#define __RELATION_H__

/************************************************************************
                   关系系统 
                   Filename:    Relation.h
                   MaintenanceMan Mail: lori227@live.cn
************************************************************************/
#include "memory_pool.h"
#include <map>
#include <vector>
#include <set>
#include <algorithm>
#include "RelationConfig.h"
#include "RelationDefine.h"
#include "GlobalFunction.h"
#include "msgbase.h"
// 谁的关系信息
template< class T >
class RelationInfo : public RelationAttributeToServer, INHERIT_POOL( RelationInfo< T > )
{
public:     // 数据结构
    // 保存ID与关系的关联
    typedef std::map< unsigned int, RelationDataToServer > RelationMap;             
    typedef typename RelationMap::iterator RelationMapIter;

    // 保存ID的容器
    typedef std::vector< unsigned int > IDVector;
    typedef typename IDVector::iterator IDVectorIter;
   
    // 保存好友之间的赠送好友度的时间
    typedef std::set< unsigned int > AddFriendlyTime;
    typedef typename AddFriendlyTime::iterator AddFriendlyTimeIter;

    // 保存好友之间一起做任务的时间
    typedef std::set< unsigned int > ReceiveQuestTime;
    typedef typename ReceiveQuestTime::iterator ReceiveQuestTimeIter;

    // 保存其他加了我有关系的玩家的ID 和关系
    typedef std::map< unsigned int, unsigned short > RelationToMeMap;
    typedef RelationToMeMap::iterator RelationToMeMapIter;

public:     // 方法
    static RelationInfo* CreateRelationInfo() { return CNewWithDebug< RelationInfo< T > >::Alloc( 1, "RelationInfo中创建RelationInfo实例" ); }
    virtual void Release() { CNewWithDebug< RelationInfo< T > >::Free( this ); }
    
    RelationInfo();
    ~RelationInfo();

    bool		AddRelation( RelationDataToServer& xRelation, unsigned char uchOperate );	// 给这个玩家添加关系   
    bool		RemoveRelation( unsigned int dwPlayerID, unsigned short stRelation );		// 删除关系
    

	static T*		GetPlayer( unsigned int dwPlayerID );									// 获得关联的角色信息            
	unsigned int	GetTeacherID() const;													// 获得师傅的ID
	unsigned int	GetMarriageID() const;													// 获得配偶的ID      
	unsigned short	GetRelationCount( unsigned short ustRelation );							// 获得某种关系的数量
	unsigned short	GetStudentCount() const;												// 当前收徒的数量 
	unsigned short	GetBrotherCount() const;												// 当前兄弟的数量
	int				GetMaxFriendlyLevel();													// 获得好友里面最大的好友度等级 
	RelationDataToServer* GetRelationData( unsigned int dwPlayerID );						// 获得与该玩家的关系

    // 判断
    bool			HaveRelation( unsigned int dwPlayerID );								// 判断与某玩家是否有关系
    bool			HaveRelation( unsigned int dwPlayerID, unsigned short ustRelation );    // 判断与某玩家是否有某种关系 
    unsigned short	CheckCanAddRelation( unsigned int dwPlayerID, unsigned short stRelation );// 判断是否能添加某种关系
    bool			IsHaveTeacher() const;													// 是否有师傅       
    bool			IsHaveMarriage() const;													// 是否有配偶
    
    // 发送
    void	SendRelationListToClient( unsigned int nAppointID = RelationDefine::InitID );	// 发送关系列表到服务器
	void	SendOutLineMessage();															// 通知好友下线
	void	SendOnLineMessage();															// 通知好友上线
	void	SendRelationMessage(Msg* pMsg); // 不是很清楚***
	void	UpdateRelationToClient( T* pPlayer );											// 更新在线信息给客户端 

	// 处理玩家上线前
	void ProcessPreDataLogin();
    // 处理玩家上线
    void ProcessEnterWorld();           

    // 处理玩家下线
    void ProcessExitWorld();              

   

    // 更新好友度 没用
    void UpdateFriendly( unsigned int dwPlayerID, unsigned char uchType, unsigned int nFriendly );   

    // 清空赠送好友度时间
    void ClearAddFriendlyTime();

    // 获得赠送好友度的个数
    unsigned short GetAddFriendlyTimeCount() { return static_cast< unsigned short >( m_setAddFriendly.size() ); }
   
    // 发送赠送好友度时间列表
    void SendAddFriendlyTimeList();     

    // 更新赠送好友度时间
    void UpdateAddFriendlyTime( unsigned int dwPlayerID, bool bClear ); 

    // 判断是否有赠送好友度时间限制
    bool HaveAddFriendlyTime( unsigned int dwPlayerID, bool &bClear );  

    // 发送更新赠送好友度时间消息
    void SendAddFriendlyTimeMessage( unsigned int dwPlayerID, bool bClear );    

    // 清空接受好友任务时间
    void ClearReceiveQuestTime();

    // 获得接受好友任务时间
    unsigned short GetReceiveQuestTimeCount() { return static_cast< unsigned short >( m_setReceiveQuest.size() ); }

    // 发送好友一起做任务的时间列表
    void SendReceiveQuestTimeList();        

    // 更新好友任务时间
    void UpdateReceiveQuestTime( unsigned int dwPlayerID, bool bClear );

    // 是否有好友任务时间限制
    bool HaveReceiveQuestTime( unsigned int dwPlayerID, bool &bClear );

    // 发送好友任务时间列表
    void SendReceiveQuestTimeMessage( unsigned int dwPlayerID, bool bClear );

    // GameServer
    // 发送添加属性消息
    void SendAddAttributeMessage();           

    // 发送更新属性消息
    void SendUpdateAttributeReqMessage( unsigned char uchType, unsigned int nValue );
    void SendUpdateAttributeReqMessage( unsigned char uchType, const char* szValue );

	void SendUpdatePersonalInfoReqMsg( const PersonalInfo& xValue );

    // 更新属性
    void UpdateRelationAttribute( unsigned char uchType, __int64 n64Value );
    void UpdateRelationAttribute( unsigned char uchType, const char* szValue );

	// 更新个人资料
	void UpdatePersonalInfo( const PersonalInfo& xValue );

    // 发送请求改变好友关系属性
    void SendUpdateRelationDataReqMessage( unsigned int nPlayerID, unsigned char uchType, unsigned int nValue );
    void SendUpdateRelationDataReqMessage( unsigned int nPlayerID, unsigned char uchType, const char* szValue );

    // 处理更新好友关系属性
    void UpdateRelationData( unsigned int nPlayerID, unsigned char uchType, unsigned int nValue );
    void UpdateRelationData( unsigned int nPlayerID, unsigned char uchType, const char* szValue );

    // 添加一个与我有关系的列表
    void AddRelationToMe( unsigned int nPlayerID, unsigned short ustRelation ); 

    // 删除一个与我有关系的列表
    void RemoveRelationToMe( unsigned int nPlayerID );

    //CenterServer

    // 发送添加属性消息到Database
    void SendAddAttributeToDatabase();     

    // 检查仇人的个数
    bool CheckVendettaRelationCount();      

    // 发送查询结果到客户端
    void SendQueryAttributeResultToClient( unsigned int* pAttributeID, int nCount );    

    // 处理徒弟升级
    void ProcessStudentLevelUp( unsigned int nPlayerID, int nLevel );   

    // 判断是否能添加组
    unsigned char CheckCanAddGroup( const char* szValue );

    // 发送名字改变请求到CenterServer
    void SendGroupNameChangeReqMessage( unsigned char uchGroupID, const char* szValue );

    // 处理分组名字信息改变
    void ProcessRelationGroupNameChange( unsigned char uchGroupID, const char* szValue );
protected:              // 方法

    // 添加一个关系
    bool AddRelation( RelationDataToServer& xRelation,RelationDataToServer& oldRelation); 
       
    // 添加一个兄弟
    void AddBrother( unsigned int dwPlayerID );     

    // 添加一个徒弟
    void AddStudent( unsigned int dwPlayerID );     

    // 删除一个兄弟
    void RemoveBrother( unsigned int dwPlayerID );  

    // 删除一个徒弟
    void RemoveStudent( unsigned int dwPlayerID );  

    // 是否能加临时好友
    unsigned short IsCanAddTempFriend( unsigned int dwPlayerID );         

    // 是否能加好友
    unsigned short IsCanAddFriend( unsigned int dwPlayerID );            

    // 是否能结婚
    unsigned short IsCanAddMarriage( unsigned int dwPlayerID );             

    // 是否能拜师
    unsigned short IsCanAddTeacher( unsigned int dwPlayerID );           

    // 是否能收徒
    unsigned short IsCanAddStudent( unsigned int dwPlayerID );            

    // 是否能结拜
    unsigned short IsCanAddBrother( unsigned int dwPlayerID );          

    // 是否能加黑名单
    unsigned short IsCanAddBlackList( unsigned int dwPlayerID );            

    // 是否能加仇人
    unsigned short IsCanAddVendetta( unsigned int dwPlayerID );             

    // 是否能添加徒弟
    unsigned short CheckCanAddStudent( unsigned int dwPlayerID );    

    // 是否能添加师傅
    unsigned short CheckCanAddTeacher( unsigned int dwPlayerID );    

    // 检查兄弟数量
    bool CheckBrotherCount();                                        
  
    // 发送添加好友消息
    void ProcessAddRelation( RelationDataToServer& xRelation, unsigned char uchOperate ,RelationDataToServer& xOldRelation);   

    // 发送删除好友消息
    void ProcessRemoveRelation( unsigned int dwPlayerID, unsigned short stRelation );       

    // 发送添加关系到GameServer或者Client
    void SendAddRelationToClient( RelationDataToServer& xData );        

    // 发送删除关系到GameServer或者Client
    void SendRemoveRelationToClient( unsigned int nPlayerID, unsigned short stRelation );   

    // CenterServer
    // 发送属性改变消息
    void SendUpdateAttributeMessage( unsigned char uchType, __int64 n64Value );
    void SendUpdateAttributeMessage( unsigned char uchType, const char* szValue );

	void SendUpdatePersonalInfo( const PersonalInfo& xValue );

    // 发送好友关系改变消息
    void SendUpdateRelationDataMessage( unsigned int nPlayerID, unsigned char uchType, unsigned int nValue );
    void SendUpdateRelationDataMessage( unsigned int nPlayerID, unsigned char uchType, const char* szValue );

    // 发送添加关系消息到Database
    void SendAddRelationToDatabase( RelationDataToServer& xData );      

    // 发送更新关系消息到Database
    void SendUpdateRelationToDatabase( unsigned int nPlayerID, unsigned char uchType, unsigned int nValue );   
    void SendUpdateRelationToDatabase( unsigned int nPlayerID, unsigned char uchType, const char* szValue );   

    // 处理添加高级关系
    void ProcessAddHigherRelathion( RelationDataToServer& xData ); 

    // 处理删除高级关系
    void ProcessRemoveHigherRelation( unsigned int nPlayerID, unsigned short stRelation ); 

    // GameServer
    // 通知对方加好友消息
    void TellAddRelationMessage( unsigned int nPlayerID, unsigned short ustRelation );  

    // 添加处理加了我为好友的关系
    void ProcessAddRelationToMe( unsigned int nPlayerID );  

    // 删除处理加了我为好友的关系
    void ProcessRemoveRelationToMe( unsigned int nPlayerID, RelationDataToServer* pData );  

    // 发送分组名字改变消息
    void SendRelationGroupNameChangeMessage( unsigned char uchGroupID, const char* szValue );

private:                // 变量
    RelationMap m_mapRelation;          // DBID 关联关系
    RelationToMeMap m_mapRelationToMe;  // 保存所有加了我为好友 或者仇人的列表
   
    IDVector m_vecStudentID;            // 所有徒弟的ID
    unsigned int m_dwTeacherID;         // 师傅的ID
    unsigned int m_dwMarriageID;        // 伴侣的ID
    IDVector m_vecBrotherID;            // 兄弟的ID
        
    unsigned int m_dwAddFriendlyTime;
    AddFriendlyTime m_setAddFriendly;   // 好友之间赠送好友度的时间

    unsigned int m_dwReceiveQuestTime;  
    ReceiveQuestTime m_setReceiveQuest; // 好友之间组队做任务的时间
};

template< class T >
RelationInfo< T >::RelationInfo() : m_dwTeacherID( RelationDefine::InitID ), m_dwMarriageID( RelationDefine::InitID ), m_dwAddFriendlyTime( 0 ),
m_dwReceiveQuestTime( 0 )
{
    m_mapRelation.clear();
    m_mapRelationToMe.clear();
    m_vecStudentID.clear();
    m_vecBrotherID.clear();
    m_setAddFriendly.clear();
    m_setReceiveQuest.clear();

    xGroup[0].SetName( RelationDefine::s_szDefaultGroup );
}

template< class T >
RelationInfo< T >::~RelationInfo()
{
    m_mapRelation.clear();
    m_mapRelationToMe.clear();
    m_vecStudentID.clear();
    m_vecBrotherID.clear();
    m_setAddFriendly.clear();
    m_setReceiveQuest.clear();
}

template< class T >
inline bool RelationInfo< T >::IsHaveTeacher() const
{
    return m_dwTeacherID != RelationDefine::InitID;
}

template< class T >
inline bool RelationInfo< T >::IsHaveMarriage() const
{
    return m_dwMarriageID != RelationDefine::InitID;
}

template< class T >
inline unsigned int RelationInfo< T >::GetTeacherID() const
{ 
    return m_dwTeacherID; 
}

template< class T >
inline unsigned int RelationInfo< T >::GetMarriageID() const
{ 
    return m_dwMarriageID; 
}

template< class T > // 当前收徒的数量
inline unsigned short RelationInfo< T >::GetStudentCount() const
{
    return static_cast< unsigned short >( m_vecStudentID.size() ); 
}    

template< class T > // 当前兄弟的数量
inline unsigned short RelationInfo< T >::GetBrotherCount() const
{ 
    return static_cast< unsigned short >( m_vecBrotherID.size() ); 
}     

template< class T >
bool RelationInfo< T >::AddRelation( RelationDataToServer& xRelation, unsigned char uchOperate )
{
    unsigned short ustHigherRelation = xRelation.GetHigherRelation();
    switch ( ustHigherRelation )    // 获得2级关系
    {
    case RelationDefine::Brother:  // 兄弟关系
        AddBrother( xRelation.GetID() );
        break;
    case RelationDefine::Marriage:  // 夫妻关系
        m_dwMarriageID = xRelation.GetID();
		xRelation.AddRelation( RelationDefine::Marriage );
        break;
    case RelationDefine::Teacher:   // 师傅
        m_dwTeacherID = xRelation.GetID();
        xRelation.AddRelation( RelationDefine::Friend );
        break;
    case RelationDefine::Student:   // 徒弟
        AddStudent( xRelation.GetID() );
        xRelation.AddRelation( RelationDefine::Friend );
        break;
    case RelationDefine::Master:    // 出师后
        m_dwTeacherID = RelationDefine::InitID;
        break;
    case RelationDefine::Prentice:  // 出师后
        RemoveStudent( xRelation.GetID() );
        break;
    default:
        break;
    }
	RelationDataToServer xOld;
	AddRelation( xRelation,xOld);
	ProcessAddRelation( xRelation, uchOperate ,xOld);        // 发送添加好友消息
    return true;
}

template< class T >
bool RelationInfo< T >::RemoveRelation( unsigned int dwPlayerID, unsigned short stRelation )
{
    RelationMapIter iter = m_mapRelation.find( dwPlayerID );
    if ( iter == m_mapRelation.end() )
    { return false; }

    switch ( stRelation )
    {
    case RelationDefine::Brother:  // 兄弟关系
        RemoveBrother( dwPlayerID );
        break;
    case RelationDefine::Marriage:  // 夫妻关系
        m_dwMarriageID = RelationDefine::InitID;
        break;
    case RelationDefine::Teacher:   // 师傅
        m_dwTeacherID = RelationDefine::InitID;
        break;
    case RelationDefine::Student:   // 徒弟
        RemoveStudent( dwPlayerID );
        break;
    default:
        break;
    }

    // 删除ID关联中的关系
    iter->second.RemoveRelation( stRelation );
    if ( !iter->second.HaveRelation() )       // 如果两个人没有关系了删除
    {
        m_mapRelation.erase( iter );
    }

    ProcessRemoveRelation( dwPlayerID, stRelation );
    return true;
}

template< class T >
bool RelationInfo< T >::AddRelation( RelationDataToServer& xRelation ,RelationDataToServer& oldRelation)
{
    RelationMapIter iter = m_mapRelation.find( xRelation.GetID() );
    if ( iter != m_mapRelation.end() )
    {
		//lyh++ 修复从黑名单加到好友
		if(iter->second.HaveRelation(RelationDefine::BlackList))
		{
			iter->second.SetGroupID(xRelation.GetGroupID()); 
		}
		oldRelation = xRelation;
		oldRelation.SetRelation( xRelation.GetRelation() ^ iter->second.GetRelation());
        iter->second.AddRelation( xRelation.GetRelation() );
		xRelation.SetRelation(iter->second.GetRelation());
		
    }
    else
    {
        m_mapRelation.insert( std::make_pair( xRelation.GetID(), xRelation ) );
		oldRelation = xRelation;
    }

    return true;
}

template< class T >
void RelationInfo< T >::AddBrother( unsigned int dwPlayerID )
{
    IDVectorIter iter = std::find( m_vecBrotherID.begin(), m_vecBrotherID.end(), dwPlayerID );
    if ( iter != m_vecBrotherID.end() )
    { return; }

    m_vecBrotherID.push_back( dwPlayerID );
}

template< class T >
void RelationInfo< T >::RemoveBrother( unsigned int dwPlayerID )
{
    IDVectorIter iter = std::find( m_vecBrotherID.begin(), m_vecBrotherID.end(), dwPlayerID );
    if ( iter == m_vecBrotherID.end() )
    { return; }

    m_vecBrotherID.erase( iter );
}

template< class T >
void RelationInfo< T >::AddStudent( unsigned int dwPlayerID )
{
    IDVectorIter iter = std::find( m_vecStudentID.begin(), m_vecStudentID.end(), dwPlayerID );
    if ( iter != m_vecStudentID.end() )
    { return; }

    m_vecStudentID.push_back( dwPlayerID );
}

template< class T >
void RelationInfo< T >::RemoveStudent( unsigned int dwPlayerID )
{
    IDVectorIter iter = std::find( m_vecStudentID.begin(), m_vecStudentID.end(), dwPlayerID );
    if ( iter == m_vecStudentID.end() )
    { return; }

    m_vecStudentID.erase( iter );
}

template< class T >     // 通过ID查找玩家关系
RelationDataToServer* RelationInfo< T >::GetRelationData( unsigned int dwPlayerID )
{
    RelationMapIter iter = m_mapRelation.find( dwPlayerID );
    if ( iter == m_mapRelation.end() )
    { return NULL; }

    return &( iter->second );
}

template< class T >     // 和该玩家是否有某种关系
bool RelationInfo< T >::HaveRelation( unsigned int dwPlayerID, unsigned short ustRelation )
{
    RelationDataToServer* pData = GetRelationData( dwPlayerID );
    if ( pData == NULL )
    { return false; }

    return pData->HaveRelation( ustRelation );
}


template< class T >     // 和该玩家是否有关系
bool RelationInfo< T >::HaveRelation( unsigned int dwPlayerID )
{
    RelationDataToServer* pData = GetRelationData( dwPlayerID );
    if ( pData == NULL )
    { return false; }

    return pData->HaveRelation();
}

template< class T >
unsigned short RelationInfo< T >::CheckCanAddRelation( unsigned int dwPlayerID, unsigned short stRelation )
{
    if ( dwPlayerID == RelationDefine::InitID || stRelation == RelationDefine::InitRelation )
    { return RelationDefine::CanNotAddRelation; }

    switch ( stRelation )
    {
    case RelationDefine::TempFriend:
        return IsCanAddTempFriend( dwPlayerID );
        break;
    case RelationDefine::Friend:
        return IsCanAddFriend( dwPlayerID );
        break;
    case RelationDefine::Vendetta:
        return IsCanAddVendetta( dwPlayerID );
        break;
    case RelationDefine::BlackList:
        return IsCanAddBlackList( dwPlayerID );
        break;
    case RelationDefine::Brother:
        return IsCanAddBrother( dwPlayerID );
        break;;
    case RelationDefine::Marriage:
        return IsCanAddMarriage( dwPlayerID );
        break;
    case RelationDefine::Teacher:
        return IsCanAddTeacher( dwPlayerID );
        break;
    case RelationDefine::Student:
        return IsCanAddStudent( dwPlayerID );
        break;
    case RelationDefine::Master:
    case RelationDefine::Prentice:
        return true;
    default:
        break;
    }

    return RelationDefine::CanNotAddRelation;
}

template< class T >
unsigned short RelationInfo< T >::IsCanAddTempFriend( unsigned int dwPlayerID )
{
    if ( GetRelationCount( RelationDefine::TempFriend ) >= theRelationConfig.GetMaxTempFriendCount() )
    { return RelationDefine::RelationFull; }

    RelationDataToServer* pRelation = GetRelationData( dwPlayerID );
    if ( pRelation == NULL )
    { return RelationDefine::CanAddRelation; }        

    return RelationDefine::CanNotAddRelation;
}

template< class T >
unsigned short RelationInfo< T >::IsCanAddFriend( unsigned int dwPlayerID )
{
    // 判断数量
    if ( GetRelationCount( RelationDefine::Friend ) >= theRelationConfig.GetMaxFriendCount() )
    { return RelationDefine::RelationFull; }

    RelationDataToServer* pData = GetRelationData( dwPlayerID );
    if ( pData == NULL )
    { return RelationDefine::CanAddRelation; }

    if ( pData->HaveRelation( RelationDefine::Friend ) )
    { return RelationDefine::AlreadyHaveRelation; }

    return RelationDefine::CanAddRelation;
}

template< class T >
unsigned short RelationInfo< T >::IsCanAddVendetta( unsigned int dwPlayerID )
{
    RelationDataToServer* pData = GetRelationData( dwPlayerID );
    if ( pData == NULL )
    { return RelationDefine::CanAddRelation; }        

    if ( pData->HaveRelation( RelationDefine::Vendetta ) )
    { return RelationDefine::AlreadyHaveRelation; }

   /* if ( pData->HaveRelation( RelationDefine::Friend ) )
    { return RelationDefine::CanNotAddRelation; }*/

    return RelationDefine::CanAddRelation;
}

template< class T >
unsigned short RelationInfo< T >::IsCanAddBlackList( unsigned int dwPlayerID )
{
    if ( GetRelationCount( RelationDefine::BlackList ) >= theRelationConfig.GetMaxBlackListCount() )
    { return RelationDefine::RelationFull; }

    RelationDataToServer* pData = GetRelationData( dwPlayerID );
    if ( pData == NULL )
    { return RelationDefine::CanAddRelation; }

    if ( pData->HaveRelation( RelationDefine::BlackList ) )
    { return RelationDefine::AlreadyHaveRelation; }

    if ( pData->HaveHigherRelation() )
    { return RelationDefine::CanNotAddRelation; }   // 如果有高级关系

    return RelationDefine::CanAddRelation;
}

template< class T >
unsigned short RelationInfo< T >::IsCanAddMarriage( unsigned int dwPlayerID )
{
    RelationDataToServer* pData = GetRelationData( dwPlayerID );
    if ( pData == NULL || !pData->HaveRelation( RelationDefine::Friend ) )
    { return RelationDefine::MustBeFriendRelation; }       

    // 是否存在2级关系, 否则不能结婚
    if ( pData->HaveHigherRelation() )
    { return RelationDefine::CanNotAddRelation; }

    if ( IsHaveMarriage() ) // 已经有夫妻了
    { return RelationDefine::AlreadyHaveRelation; }

    return RelationDefine::CanAddRelation;
}

template< class T >
unsigned short RelationInfo< T >::IsCanAddTeacher( unsigned int dwPlayerID )
{
    RelationDataToServer* pData = GetRelationData( dwPlayerID );
    if ( pData != NULL && pData->HaveHigherRelation() )
    { return RelationDefine::CanNotAddRelation; }

    if ( IsHaveTeacher() )
    { return RelationDefine::AlreadyHaveRelation; }

    return CheckCanAddTeacher( dwPlayerID );
}

template< class T >
unsigned short RelationInfo< T >::IsCanAddStudent( unsigned int dwPlayerID )
{
    return CheckCanAddStudent( dwPlayerID );
}

template< class T >
unsigned short RelationInfo< T >::IsCanAddBrother( unsigned int dwPlayerID )
{
    // 结拜应该也有个数限制, ( 这个暂时不知道属性防在哪里, 所以这里先不判断 )
    RelationDataToServer* pData = GetRelationData( dwPlayerID );
    if ( pData == NULL || !pData->HaveRelation( RelationDefine::Friend ) )
    { return RelationDefine::MustBeFriendRelation; }   

    if ( pData->HaveHigherRelation() )  // 如果有高级关系
    { return RelationDefine::CanNotAddRelation; }   

    if ( !CheckBrotherCount() )
    { return RelationDefine::CanNotAddRelation; }


    return RelationDefine::CanAddRelation;
}

template< class T >
unsigned short RelationInfo< T >::GetRelationCount( unsigned short ustRelation )
{
    unsigned short ustCount = 0;
    for ( RelationMapIter iter = m_mapRelation.begin(); iter != m_mapRelation.end(); ++iter )
    {
        if ( iter->second.HaveRelation( ustRelation ) )
        {
            ++ustCount;
        }
    }

    return ustCount;
}

template< class T >
int RelationInfo< T >::GetMaxFriendlyLevel()
{
    unsigned int nMaxFriendly = 0;
    for ( RelationMapIter iter = m_mapRelation.begin(); iter != m_mapRelation.end(); ++iter )
    {
        if ( !iter->second.HaveRelation( RelationDefine::Friend ) )
        { continue; }

        if ( iter->second.GetFriendly() > nMaxFriendly )
        { nMaxFriendly = iter->second.GetFriendly(); }
    }

    return theRelationConfig.GetFriendLevel( nMaxFriendly );
}

template< class T >
void RelationInfo< T >::UpdateReceiveQuestTime( unsigned int dwPlayerID, bool bClear )
{
    if ( bClear )
    { m_setReceiveQuest.clear(); }

    if ( dwPlayerID == RelationDefine::InitID )
    { return; }

    m_setReceiveQuest.insert( dwPlayerID );
}

template< class T >
void RelationInfo< T >::UpdateAddFriendlyTime( unsigned int dwPlayerID, bool bClear )
{
    if ( bClear )
    { 
        RecordTime::SaveRecordTime( m_dwAddFriendlyTime );
        m_setAddFriendly.clear();
    }

    m_setAddFriendly.insert( dwPlayerID );
}


template< class T >
void RelationInfo< T >::UpdateRelationAttribute( unsigned char uchType, __int64 n64Value )
{
    switch ( uchType )
    {
    case RelationDefine::UpdateLevel:
        SetLevel( static_cast< unsigned short >( n64Value ) );
        break;
    case RelationDefine::UpdateHeadPic:
        SetHeadPic( static_cast< unsigned short >( n64Value ) );
        break;
    case RelationDefine::UpdateProfession:
        SetProfession( static_cast< unsigned char >( n64Value ) );
        break;
    case RelationDefine::UpdateSex:
        SetSex( static_cast< unsigned char >( n64Value ) );
        break;
    case RelationDefine::UpdateCountry:
        SetCountry( static_cast< unsigned char >( n64Value ) );
        break;
    case RelationDefine::UpdateGuild:
        SetGuildID( static_cast< unsigned int >( n64Value ) );
        break;
    case RelationDefine::UpdatePosition:
        SetPosition( static_cast< unsigned char >( n64Value ) );
        break;
	case RelationDefine::UpdateFamily:
		SetFamilyID( static_cast< unsigned int >( n64Value ) );
		break;
    case RelationDefine::UpdateMasterLevel:
        SetMasterLevel( static_cast< unsigned char >( n64Value ) );
        break;
    case RelationDefine::UpdateMessageRefuse:
        SetMessageRefuse( static_cast< unsigned short >( n64Value ) );
        break;
    case RelationDefine::UpdateRewardExp:
        SetRewardExp( static_cast< unsigned int >( n64Value ) );
        break;
    case RelationDefine::UpdateRewardPrestige:
        SetRewardPrestige( static_cast< unsigned int >( n64Value ) );
        break;
    case RelationDefine::UpdateLastStudentTime:
        SetLastAddStudentTime( n64Value );
        break;
    case RelationDefine::UpdateLastTeacherTime:
        SetLastAddTeacherTime( n64Value );
        break;
    case RelationDefine::UpdateTitle:
        SetTitleID( static_cast< unsigned int >( n64Value ) );
        break;
    case RelationDefine::UpdateMapID:
        SetMapID( static_cast< unsigned int >( n64Value ) );
        break;
    default:
        return;
        break;
    }

    // 发送消息改变消息
    SendUpdateAttributeMessage( uchType, n64Value );
}

template< class T >
void RelationInfo< T >::UpdateRelationAttribute( unsigned char uchType, const char* szValue )
{
    switch ( uchType )
    {
    case RelationDefine::UpdateName:
        SetName( szValue );
        break;
    case RelationDefine::UpdateSignature:
        SetSignature( szValue );
        break;
    case RelationDefine::UpdateIp:
        SetIp( szValue );
        break;
    default:
        return;
        break;
    }

    // 发送消息改变消息
    SendUpdateAttributeMessage( uchType, szValue );
}

template< class T >
void RelationInfo< T >::UpdatePersonalInfo( const PersonalInfo& xValue )
{
	GetPersonalInfo().SetInfo( xValue );

	SendUpdatePersonalInfo( xValue );
}

template< class T >
unsigned char RelationInfo< T >::CheckCanAddGroup( const char* szValue )
{
    unsigned char uchGroupID = 0;
    for ( int i = 1; i < RelationDefine::GroupCount; ++i )
    {
        if ( xGroup[i].IsEmpty() && uchGroupID == 0 )
        { uchGroupID = i; }

        // 不能有相同的组
        if ( strcmp( xGroup[i].GetName(), szValue ) == 0 )
        {
            uchGroupID = 0;
            break;
        }
    }

    return uchGroupID;
}

template< class T >
void RelationInfo< T >::ProcessRelationGroupNameChange( unsigned char uchGroupID, const char* szValue )
{
    if ( uchGroupID >= RelationDefine::GroupCount )
    { return; }

    xGroup[uchGroupID].SetName( szValue );

    if ( szValue[0] == 0 )  // 如果是删除分组, 将该分组的所有玩家放入默认分组
    {
        for ( RelationMapIter iter = m_mapRelation.begin(); iter != m_mapRelation.end(); ++iter )
        {
            if ( iter->second.GetGroupID() == uchGroupID )
            { iter->second.SetGroupID( 0 ); }
        }
    }

    SendRelationGroupNameChangeMessage( uchGroupID, szValue );
}

template< class T >
void RelationInfo< T >::UpdateRelationData( unsigned int nPlayerID, unsigned char uchType, unsigned int nValue )
{
    RelationDataToServer* pData = GetRelationData( nPlayerID );
    if ( pData == NULL )
    { return; }

    switch ( uchType )
    {
    case RelationDefine::UpdateGroupID:
        if ( !pData->HaveRelation( RelationDefine::Friend ) )
        { return; }

        pData->SetGroupID( static_cast< unsigned char >( nValue ) );
        break;
    case RelationDefine::UpdateLocked:
        pData->SetLocked( nValue == 1 ? true : false );
        break;
    case RelationDefine::UpdateSetFriendly:
        pData->SetFriendly( nValue );
        break;
    case RelationDefine::UpdateAddFriendly:
        {
            unsigned int nCanAdd = theRelationConfig.GetMaxFriendly() - pData->GetFriendly();
            if ( nValue > nCanAdd )
            { nValue = nCanAdd; }
            if ( nValue == 0 )
            { return; }

            pData->AddFriendly( nValue );

            uchType = RelationDefine::UpdateSetFriendly;
            nValue  = pData->GetFriendly();
        }
        break;
    case RelationDefine::UpdateSubFriendly:
        pData->SubFriendly( nValue );
        uchType = RelationDefine::UpdateSetFriendly;
        nValue  = pData->GetFriendly();
        break;
    default:
        return;
        break;
    }

    SendUpdateRelationDataMessage( nPlayerID, uchType, nValue );
}

template< class T >
void RelationInfo< T >::UpdateRelationData( unsigned int nPlayerID, unsigned char uchType, const char* szValue )
{
    RelationDataToServer* pData = GetRelationData( nPlayerID );
    if ( pData == NULL )
    { return; }

    switch ( uchType )
    {
    case RelationDefine::UpdateRemark:
        pData->SetRemark( szValue );
        break;
    default:
        return;
        break;
    }

    SendUpdateRelationDataMessage( nPlayerID, uchType, szValue );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

class GamePlayer;
typedef RelationInfo< GamePlayer > GameRelation;

class ClientPeer;
typedef RelationInfo< ClientPeer > CenterRelation;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif