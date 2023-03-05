#ifndef __RELATION_H__
#define __RELATION_H__

/************************************************************************
                   ��ϵϵͳ 
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
// ˭�Ĺ�ϵ��Ϣ
template< class T >
class RelationInfo : public RelationAttributeToServer, INHERIT_POOL( RelationInfo< T > )
{
public:     // ���ݽṹ
    // ����ID���ϵ�Ĺ���
    typedef std::map< unsigned int, RelationDataToServer > RelationMap;             
    typedef typename RelationMap::iterator RelationMapIter;

    // ����ID������
    typedef std::vector< unsigned int > IDVector;
    typedef typename IDVector::iterator IDVectorIter;
   
    // �������֮������ͺ��Ѷȵ�ʱ��
    typedef std::set< unsigned int > AddFriendlyTime;
    typedef typename AddFriendlyTime::iterator AddFriendlyTimeIter;

    // �������֮��һ���������ʱ��
    typedef std::set< unsigned int > ReceiveQuestTime;
    typedef typename ReceiveQuestTime::iterator ReceiveQuestTimeIter;

    // ���������������й�ϵ����ҵ�ID �͹�ϵ
    typedef std::map< unsigned int, unsigned short > RelationToMeMap;
    typedef RelationToMeMap::iterator RelationToMeMapIter;

public:     // ����
    static RelationInfo* CreateRelationInfo() { return CNewWithDebug< RelationInfo< T > >::Alloc( 1, "RelationInfo�д���RelationInfoʵ��" ); }
    virtual void Release() { CNewWithDebug< RelationInfo< T > >::Free( this ); }
    
    RelationInfo();
    ~RelationInfo();

    bool		AddRelation( RelationDataToServer& xRelation, unsigned char uchOperate );	// ����������ӹ�ϵ   
    bool		RemoveRelation( unsigned int dwPlayerID, unsigned short stRelation );		// ɾ����ϵ
    

	static T*		GetPlayer( unsigned int dwPlayerID );									// ��ù����Ľ�ɫ��Ϣ            
	unsigned int	GetTeacherID() const;													// ���ʦ����ID
	unsigned int	GetMarriageID() const;													// �����ż��ID      
	unsigned short	GetRelationCount( unsigned short ustRelation );							// ���ĳ�ֹ�ϵ������
	unsigned short	GetStudentCount() const;												// ��ǰ��ͽ������ 
	unsigned short	GetBrotherCount() const;												// ��ǰ�ֵܵ�����
	int				GetMaxFriendlyLevel();													// ��ú����������ĺ��Ѷȵȼ� 
	RelationDataToServer* GetRelationData( unsigned int dwPlayerID );						// ��������ҵĹ�ϵ

    // �ж�
    bool			HaveRelation( unsigned int dwPlayerID );								// �ж���ĳ����Ƿ��й�ϵ
    bool			HaveRelation( unsigned int dwPlayerID, unsigned short ustRelation );    // �ж���ĳ����Ƿ���ĳ�ֹ�ϵ 
    unsigned short	CheckCanAddRelation( unsigned int dwPlayerID, unsigned short stRelation );// �ж��Ƿ������ĳ�ֹ�ϵ
    bool			IsHaveTeacher() const;													// �Ƿ���ʦ��       
    bool			IsHaveMarriage() const;													// �Ƿ�����ż
    
    // ����
    void	SendRelationListToClient( unsigned int nAppointID = RelationDefine::InitID );	// ���͹�ϵ�б�������
	void	SendOutLineMessage();															// ֪ͨ��������
	void	SendOnLineMessage();															// ֪ͨ��������
	void	SendRelationMessage(Msg* pMsg); // ���Ǻ����***
	void	UpdateRelationToClient( T* pPlayer );											// ����������Ϣ���ͻ��� 

	// �����������ǰ
	void ProcessPreDataLogin();
    // �����������
    void ProcessEnterWorld();           

    // �����������
    void ProcessExitWorld();              

   

    // ���º��Ѷ� û��
    void UpdateFriendly( unsigned int dwPlayerID, unsigned char uchType, unsigned int nFriendly );   

    // ������ͺ��Ѷ�ʱ��
    void ClearAddFriendlyTime();

    // ������ͺ��Ѷȵĸ���
    unsigned short GetAddFriendlyTimeCount() { return static_cast< unsigned short >( m_setAddFriendly.size() ); }
   
    // �������ͺ��Ѷ�ʱ���б�
    void SendAddFriendlyTimeList();     

    // �������ͺ��Ѷ�ʱ��
    void UpdateAddFriendlyTime( unsigned int dwPlayerID, bool bClear ); 

    // �ж��Ƿ������ͺ��Ѷ�ʱ������
    bool HaveAddFriendlyTime( unsigned int dwPlayerID, bool &bClear );  

    // ���͸������ͺ��Ѷ�ʱ����Ϣ
    void SendAddFriendlyTimeMessage( unsigned int dwPlayerID, bool bClear );    

    // ��ս��ܺ�������ʱ��
    void ClearReceiveQuestTime();

    // ��ý��ܺ�������ʱ��
    unsigned short GetReceiveQuestTimeCount() { return static_cast< unsigned short >( m_setReceiveQuest.size() ); }

    // ���ͺ���һ���������ʱ���б�
    void SendReceiveQuestTimeList();        

    // ���º�������ʱ��
    void UpdateReceiveQuestTime( unsigned int dwPlayerID, bool bClear );

    // �Ƿ��к�������ʱ������
    bool HaveReceiveQuestTime( unsigned int dwPlayerID, bool &bClear );

    // ���ͺ�������ʱ���б�
    void SendReceiveQuestTimeMessage( unsigned int dwPlayerID, bool bClear );

    // GameServer
    // �������������Ϣ
    void SendAddAttributeMessage();           

    // ���͸���������Ϣ
    void SendUpdateAttributeReqMessage( unsigned char uchType, unsigned int nValue );
    void SendUpdateAttributeReqMessage( unsigned char uchType, const char* szValue );

	void SendUpdatePersonalInfoReqMsg( const PersonalInfo& xValue );

    // ��������
    void UpdateRelationAttribute( unsigned char uchType, __int64 n64Value );
    void UpdateRelationAttribute( unsigned char uchType, const char* szValue );

	// ���¸�������
	void UpdatePersonalInfo( const PersonalInfo& xValue );

    // ��������ı���ѹ�ϵ����
    void SendUpdateRelationDataReqMessage( unsigned int nPlayerID, unsigned char uchType, unsigned int nValue );
    void SendUpdateRelationDataReqMessage( unsigned int nPlayerID, unsigned char uchType, const char* szValue );

    // ������º��ѹ�ϵ����
    void UpdateRelationData( unsigned int nPlayerID, unsigned char uchType, unsigned int nValue );
    void UpdateRelationData( unsigned int nPlayerID, unsigned char uchType, const char* szValue );

    // ���һ�������й�ϵ���б�
    void AddRelationToMe( unsigned int nPlayerID, unsigned short ustRelation ); 

    // ɾ��һ�������й�ϵ���б�
    void RemoveRelationToMe( unsigned int nPlayerID );

    //CenterServer

    // �������������Ϣ��Database
    void SendAddAttributeToDatabase();     

    // �����˵ĸ���
    bool CheckVendettaRelationCount();      

    // ���Ͳ�ѯ������ͻ���
    void SendQueryAttributeResultToClient( unsigned int* pAttributeID, int nCount );    

    // ����ͽ������
    void ProcessStudentLevelUp( unsigned int nPlayerID, int nLevel );   

    // �ж��Ƿ��������
    unsigned char CheckCanAddGroup( const char* szValue );

    // �������ָı�����CenterServer
    void SendGroupNameChangeReqMessage( unsigned char uchGroupID, const char* szValue );

    // �������������Ϣ�ı�
    void ProcessRelationGroupNameChange( unsigned char uchGroupID, const char* szValue );
protected:              // ����

    // ���һ����ϵ
    bool AddRelation( RelationDataToServer& xRelation,RelationDataToServer& oldRelation); 
       
    // ���һ���ֵ�
    void AddBrother( unsigned int dwPlayerID );     

    // ���һ��ͽ��
    void AddStudent( unsigned int dwPlayerID );     

    // ɾ��һ���ֵ�
    void RemoveBrother( unsigned int dwPlayerID );  

    // ɾ��һ��ͽ��
    void RemoveStudent( unsigned int dwPlayerID );  

    // �Ƿ��ܼ���ʱ����
    unsigned short IsCanAddTempFriend( unsigned int dwPlayerID );         

    // �Ƿ��ܼӺ���
    unsigned short IsCanAddFriend( unsigned int dwPlayerID );            

    // �Ƿ��ܽ��
    unsigned short IsCanAddMarriage( unsigned int dwPlayerID );             

    // �Ƿ��ܰ�ʦ
    unsigned short IsCanAddTeacher( unsigned int dwPlayerID );           

    // �Ƿ�����ͽ
    unsigned short IsCanAddStudent( unsigned int dwPlayerID );            

    // �Ƿ��ܽ��
    unsigned short IsCanAddBrother( unsigned int dwPlayerID );          

    // �Ƿ��ܼӺ�����
    unsigned short IsCanAddBlackList( unsigned int dwPlayerID );            

    // �Ƿ��ܼӳ���
    unsigned short IsCanAddVendetta( unsigned int dwPlayerID );             

    // �Ƿ������ͽ��
    unsigned short CheckCanAddStudent( unsigned int dwPlayerID );    

    // �Ƿ������ʦ��
    unsigned short CheckCanAddTeacher( unsigned int dwPlayerID );    

    // ����ֵ�����
    bool CheckBrotherCount();                                        
  
    // ������Ӻ�����Ϣ
    void ProcessAddRelation( RelationDataToServer& xRelation, unsigned char uchOperate ,RelationDataToServer& xOldRelation);   

    // ����ɾ��������Ϣ
    void ProcessRemoveRelation( unsigned int dwPlayerID, unsigned short stRelation );       

    // ������ӹ�ϵ��GameServer����Client
    void SendAddRelationToClient( RelationDataToServer& xData );        

    // ����ɾ����ϵ��GameServer����Client
    void SendRemoveRelationToClient( unsigned int nPlayerID, unsigned short stRelation );   

    // CenterServer
    // �������Ըı���Ϣ
    void SendUpdateAttributeMessage( unsigned char uchType, __int64 n64Value );
    void SendUpdateAttributeMessage( unsigned char uchType, const char* szValue );

	void SendUpdatePersonalInfo( const PersonalInfo& xValue );

    // ���ͺ��ѹ�ϵ�ı���Ϣ
    void SendUpdateRelationDataMessage( unsigned int nPlayerID, unsigned char uchType, unsigned int nValue );
    void SendUpdateRelationDataMessage( unsigned int nPlayerID, unsigned char uchType, const char* szValue );

    // ������ӹ�ϵ��Ϣ��Database
    void SendAddRelationToDatabase( RelationDataToServer& xData );      

    // ���͸��¹�ϵ��Ϣ��Database
    void SendUpdateRelationToDatabase( unsigned int nPlayerID, unsigned char uchType, unsigned int nValue );   
    void SendUpdateRelationToDatabase( unsigned int nPlayerID, unsigned char uchType, const char* szValue );   

    // ������Ӹ߼���ϵ
    void ProcessAddHigherRelathion( RelationDataToServer& xData ); 

    // ����ɾ���߼���ϵ
    void ProcessRemoveHigherRelation( unsigned int nPlayerID, unsigned short stRelation ); 

    // GameServer
    // ֪ͨ�Է��Ӻ�����Ϣ
    void TellAddRelationMessage( unsigned int nPlayerID, unsigned short ustRelation );  

    // ��Ӵ��������Ϊ���ѵĹ�ϵ
    void ProcessAddRelationToMe( unsigned int nPlayerID );  

    // ɾ�����������Ϊ���ѵĹ�ϵ
    void ProcessRemoveRelationToMe( unsigned int nPlayerID, RelationDataToServer* pData );  

    // ���ͷ������ָı���Ϣ
    void SendRelationGroupNameChangeMessage( unsigned char uchGroupID, const char* szValue );

private:                // ����
    RelationMap m_mapRelation;          // DBID ������ϵ
    RelationToMeMap m_mapRelationToMe;  // �������м�����Ϊ���� ���߳��˵��б�
   
    IDVector m_vecStudentID;            // ����ͽ�ܵ�ID
    unsigned int m_dwTeacherID;         // ʦ����ID
    unsigned int m_dwMarriageID;        // ���µ�ID
    IDVector m_vecBrotherID;            // �ֵܵ�ID
        
    unsigned int m_dwAddFriendlyTime;
    AddFriendlyTime m_setAddFriendly;   // ����֮�����ͺ��Ѷȵ�ʱ��

    unsigned int m_dwReceiveQuestTime;  
    ReceiveQuestTime m_setReceiveQuest; // ����֮������������ʱ��
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

template< class T > // ��ǰ��ͽ������
inline unsigned short RelationInfo< T >::GetStudentCount() const
{
    return static_cast< unsigned short >( m_vecStudentID.size() ); 
}    

template< class T > // ��ǰ�ֵܵ�����
inline unsigned short RelationInfo< T >::GetBrotherCount() const
{ 
    return static_cast< unsigned short >( m_vecBrotherID.size() ); 
}     

template< class T >
bool RelationInfo< T >::AddRelation( RelationDataToServer& xRelation, unsigned char uchOperate )
{
    unsigned short ustHigherRelation = xRelation.GetHigherRelation();
    switch ( ustHigherRelation )    // ���2����ϵ
    {
    case RelationDefine::Brother:  // �ֵܹ�ϵ
        AddBrother( xRelation.GetID() );
        break;
    case RelationDefine::Marriage:  // ���޹�ϵ
        m_dwMarriageID = xRelation.GetID();
		xRelation.AddRelation( RelationDefine::Marriage );
        break;
    case RelationDefine::Teacher:   // ʦ��
        m_dwTeacherID = xRelation.GetID();
        xRelation.AddRelation( RelationDefine::Friend );
        break;
    case RelationDefine::Student:   // ͽ��
        AddStudent( xRelation.GetID() );
        xRelation.AddRelation( RelationDefine::Friend );
        break;
    case RelationDefine::Master:    // ��ʦ��
        m_dwTeacherID = RelationDefine::InitID;
        break;
    case RelationDefine::Prentice:  // ��ʦ��
        RemoveStudent( xRelation.GetID() );
        break;
    default:
        break;
    }
	RelationDataToServer xOld;
	AddRelation( xRelation,xOld);
	ProcessAddRelation( xRelation, uchOperate ,xOld);        // ������Ӻ�����Ϣ
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
    case RelationDefine::Brother:  // �ֵܹ�ϵ
        RemoveBrother( dwPlayerID );
        break;
    case RelationDefine::Marriage:  // ���޹�ϵ
        m_dwMarriageID = RelationDefine::InitID;
        break;
    case RelationDefine::Teacher:   // ʦ��
        m_dwTeacherID = RelationDefine::InitID;
        break;
    case RelationDefine::Student:   // ͽ��
        RemoveStudent( dwPlayerID );
        break;
    default:
        break;
    }

    // ɾ��ID�����еĹ�ϵ
    iter->second.RemoveRelation( stRelation );
    if ( !iter->second.HaveRelation() )       // ���������û�й�ϵ��ɾ��
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
		//lyh++ �޸��Ӻ������ӵ�����
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

template< class T >     // ͨ��ID������ҹ�ϵ
RelationDataToServer* RelationInfo< T >::GetRelationData( unsigned int dwPlayerID )
{
    RelationMapIter iter = m_mapRelation.find( dwPlayerID );
    if ( iter == m_mapRelation.end() )
    { return NULL; }

    return &( iter->second );
}

template< class T >     // �͸�����Ƿ���ĳ�ֹ�ϵ
bool RelationInfo< T >::HaveRelation( unsigned int dwPlayerID, unsigned short ustRelation )
{
    RelationDataToServer* pData = GetRelationData( dwPlayerID );
    if ( pData == NULL )
    { return false; }

    return pData->HaveRelation( ustRelation );
}


template< class T >     // �͸�����Ƿ��й�ϵ
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
    // �ж�����
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
    { return RelationDefine::CanNotAddRelation; }   // ����и߼���ϵ

    return RelationDefine::CanAddRelation;
}

template< class T >
unsigned short RelationInfo< T >::IsCanAddMarriage( unsigned int dwPlayerID )
{
    RelationDataToServer* pData = GetRelationData( dwPlayerID );
    if ( pData == NULL || !pData->HaveRelation( RelationDefine::Friend ) )
    { return RelationDefine::MustBeFriendRelation; }       

    // �Ƿ����2����ϵ, �����ܽ��
    if ( pData->HaveHigherRelation() )
    { return RelationDefine::CanNotAddRelation; }

    if ( IsHaveMarriage() ) // �Ѿ��з�����
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
    // ���Ӧ��Ҳ�и�������, ( �����ʱ��֪�����Է�������, ���������Ȳ��ж� )
    RelationDataToServer* pData = GetRelationData( dwPlayerID );
    if ( pData == NULL || !pData->HaveRelation( RelationDefine::Friend ) )
    { return RelationDefine::MustBeFriendRelation; }   

    if ( pData->HaveHigherRelation() )  // ����и߼���ϵ
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

    // ������Ϣ�ı���Ϣ
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

    // ������Ϣ�ı���Ϣ
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

        // ��������ͬ����
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

    if ( szValue[0] == 0 )  // �����ɾ������, ���÷����������ҷ���Ĭ�Ϸ���
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