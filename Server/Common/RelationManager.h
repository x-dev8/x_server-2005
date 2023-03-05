#ifndef __RELATIONMANAGER_H__
#define __RELATIONMANAGER_H__

/************************************************************************
                   ��ϵϵͳ 
                   Filename:    RelationManager.h
                   MaintenanceMan Mail: lori227@live.cn
************************************************************************/
#include <string>
#include "GameTimer.h"
#include "RunStatus.h"
#include "Relation.h"
#include "Singleton.h"

// ������ӹ�ϵ�ļ�¼��Ϣ
class RelationInvite
{
public:
    RelationInvite() : dwTargetID( RelationDefine::InitID ), stRelation( 0 ) {}

    unsigned int dwTargetID;          // ���������
    unsigned short stRelation;        // ����Ĺ�ϵ
    GameTimerEx xTimer;               // ��ʱ��
    
    bool operator == ( unsigned int dwID ) { return dwTargetID == dwID; }
    bool IsError() const { return dwTargetID == RelationDefine::InitID || stRelation == 0; }

    void StartTimer( unsigned int nCurrentTime ) { xTimer.StartTimer( nCurrentTime, RelationDefine::RelationInviteTimeOunt ); }
    bool DoneTimer( unsigned int nCurrentTime ) { return xTimer.DoneTimer( nCurrentTime ); }
};


template< class T >
class RelationManager : public ISingletion< RelationManager< T > >
{
protected:
    typedef std::map< unsigned int, T* > RelationMap;
    typedef typename RelationMap::iterator RelationMapIter;

    typedef std::map< std::string, unsigned int > NameIDMap;
    typedef typename NameIDMap::iterator NameIDMapIter;

    typedef std::vector< RelationInvite > InviteVector;
    typedef InviteVector::iterator InviteVectorIter;

    typedef std::map< unsigned int, InviteVector > MapInvite;
    typedef MapInvite::iterator MapInviteIter;

    typedef std::set< unsigned int > IDSet;
    typedef IDSet::iterator IDSetIter;

public:
    RelationManager();
    ~RelationManager();

	void StartLoadTimer();
	void StopLoadTimer();
	//bool GetLoadTimerStart() const;

	bool GetLoadSuccess() const;
	void SetLoadSuccess( bool bValue );

	// init
	void InitRelationsAttribute( RelationAttributeToServer* pAttribute, int nCount );    // ��ʼ����ϵ����center
	void InitRelationsData( RelationDataToDatabase* pData, int nCount );         // ��ʼ��ĳ�˵Ĺ�ϵ��Ϣ
	void SendRelationList2Client( unsigned int nAppointID );	//���͹�ϵ�б�game  ��������ʱ��ʹ��

	//����
    void RunUpdate( unsigned int dwCurrentTime );           // ִ�и���

    T* GetPlayerRelation( unsigned int dwPlayerID, bool bInsert = false );        // ���ҹ�ϵ��Ϣ �õڶ���������ʱ��һ��ҪС��
    T* GetPlayerRelation( const char* szName );             // ���ҹ�ϵ��Ϣ

	bool AddPlayerNameID( T* pRelation );					// ��� ���ֺ�DBID ����
    void RemovePlayerRelation( unsigned int dwPlayerID );   // ɾ����ϵ��Ϣ

    void ProcessEnterWorld( unsigned int nPlayerID );
    void ProcessExitWorld( unsigned int dwPlayerID );

    void ProcessRelationToMe( T* pRelation );

    void SendQueryAttributeResultToClient( unsigned int nPlayerID, unsigned int* pAttributeID, int nCount );
    ///////////////////////////////////////////////////////////////////////////////////////////////////////
    void AddRelationInvite( unsigned int dwInviterID, const RelationInvite& xInvite );    // ���һ������
    void RemoveRelationInvite( unsigned int dwInviterID, unsigned int dwTargetID ); // ɾ��һ������
    RelationInvite* GetRelationInvite( unsigned int dwInviterID, unsigned int dwTargetID ); // ���һ��������Ϣ

    // ����ע�ᱨ��Ҫ�� ʦ�� or ͽ�ܵ��б�
    void AddRegisterID( unsigned int nPlayerID, unsigned int ustRelation );
    void RemoveRegisterID( unsigned short ustRelation, unsigned int nPlayerID );
    bool IsRegisterID( unsigned int nPlayerID, unsigned int ustRelation );
    void SendRegisterRelation( unsigned int nPlayerID, unsigned int ustRelation );	// ָ����ע����Ϣ�����û�

	// �����Ѿ����͵�GS��set��¼
	void AddSendedRelationId( unsigned int nPlayerID );
	bool HaveSendedRelationId( unsigned int nPlayerID );
protected:
    // �����������
    void ProcessLoadRelationData( unsigned int nCurrentTime );	//�Ӹ���
	void UpdateRelationInvite( unsigned int dwCurrentTime );	//�Ӹ���

    T* GetRelation( unsigned int dwPlayerID );	//DBID
    bool AddPlayerRelation( T* pRelation );		// ��Ӹ��˹�ϵ��Ϣ
    
	// tell the server �б������
    void SendRelationListSuccess( unsigned int nAppointID );

private:
    RelationMap m_mapRelations;  // ������ҵĹ�ϵ
    NameIDMap m_mapNameID;      // ���ֶ�ӦDBID��MAP
    MapInvite m_mapInvite;      // �����б�
    bool m_bLoadSuccess;        // �Ƿ���سɹ�
    bool m_bLoadTimerStart;     // �Ƿ��������ض�ʱ��

    IDSet m_setTeacherID;       // ����Ҫ��ʦ�����б�
    IDSet m_setStudentID;       // ����Ҫ��ͽ�ܵ��б�

    GameTimerEx m_xLoadTimer;	// ���ض�ʱ��
    GameTimerEx m_xUpdateTimer; // ���¶�ʱ��

	IDSet m_setSendedRelationId;// �Ѿ����͵Ĺ�ϵdbid
};

template< class T >
RelationManager< T >::RelationManager() : m_bLoadTimerStart( false ), m_bLoadSuccess( false )
{
    m_mapRelations.clear();
    m_mapInvite.clear();

    m_setTeacherID.clear();
    m_setStudentID.clear();

    m_xUpdateTimer.StartTimer( 1, RelationDefine::UpdateSpaceTime );
}

template< class T >
RelationManager< T >::~RelationManager()
{
    for ( RelationMapIter iter = m_mapRelations.begin(); iter != m_mapRelations.end(); ++iter )
    {
        iter->second->Release();
    }

    m_mapRelations.clear();
}

template< class T >
void RelationManager< T >::StartLoadTimer()
{
    if ( m_bLoadTimerStart )
    { return; }

    m_bLoadTimerStart = true;
    m_xLoadTimer.StartTimer( 1, RelationDefine::AutoSaveSpaceTime );
}

template< class T >
void RelationManager< T >::StopLoadTimer()
{
    m_xLoadTimer.StopTimer();
}

template< class T >
bool RelationManager< T >::GetLoadSuccess() const
{
    return m_bLoadSuccess;
}

template< class T >
void RelationManager< T >::SetLoadSuccess( bool bValue )
{
    m_bLoadSuccess = bValue;
	if (bValue)
	{
		theRunStatus.SetLoadSuccess(RunStatusDefine::LoadRelationSuccess);
	}
}

template< class T >
T* RelationManager< T >::GetPlayerRelation( unsigned int dwPlayerID, bool bInsert )
{
    if ( dwPlayerID == RelationDefine::InitID )
    {  return NULL; }

    T* pRelation = GetRelation( dwPlayerID );
    if ( pRelation == NULL )
    {
        if ( bInsert )      // �����Ҫ����
        {
            pRelation = T::CreateRelationInfo();
            if ( pRelation == NULL )
            { return NULL; }

            pRelation->SetID( dwPlayerID );
            AddPlayerRelation( pRelation );
        }
    }

    return pRelation;
}

template< class T >
T* RelationManager< T >::GetPlayerRelation( const char* szName )
{
    if ( szName == NULL || szName[0] == 0 )
    { return NULL; }

    NameIDMapIter iter = m_mapNameID.find( szName );
    if ( iter == m_mapNameID.end() )
    { return NULL; }

    return GetRelation( iter->second );
}

template< class T > 
bool RelationManager< T >::AddPlayerRelation( T* pRelation )
{
    if ( pRelation == NULL )
    { return false; }

    return m_mapRelations.insert( std::make_pair( pRelation->GetID(), pRelation ) ).second;
}

template< class T >
void RelationManager< T >::RemovePlayerRelation( unsigned int dwPlayerID )
{
    RelationMapIter iter = m_mapRelation.find( dwPlayerID );
    if ( iter == m_mapRelation.end() )
    { return; }

    iter->second->Release();
    m_mapRelation.erase( iter );
}

template< class T >
T* RelationManager< T >::GetRelation( unsigned int dwPlayerID )
{
    RelationMapIter iter = m_mapRelations.find( dwPlayerID );
    if ( iter == m_mapRelations.end() )
    { return NULL; }

    return iter->second;
}

template< class T >
bool RelationManager< T >::AddPlayerNameID( T* pRelation )
{
    if ( pRelation == NULL )
    { return false; }

    const char* szName = pRelation->GetName();
    if ( szName[0] == 0 )
    { return false; }

    m_mapNameID[ szName ] = pRelation->GetID();
    return true;
}

template< class T >
void RelationManager< T >::InitRelationsAttribute( RelationAttributeToServer* pAttribute, int nCount )
{
    if ( pAttribute == NULL || GetLoadSuccess() )
    { return; }

    for ( int i = 0; i < nCount; ++i )
    {
        T* pRelation = GetPlayerRelation( pAttribute[i].GetID(), true );
        if ( pRelation == NULL )
        { continue; }

        pRelation->SetRelationAttributeToServer( pAttribute[i] );
        AddPlayerNameID( pRelation );
    }

    StopLoadTimer();
}

template< class T >
void RelationManager< T >::InitRelationsData( RelationDataToDatabase* pData, int nCount )
{
    if ( pData == NULL || nCount == 0 )
    { return; }

    for ( int i = 0; i < nCount; ++i )
    {
        T* pRelation = GetPlayerRelation( pData[i].nPlayerID );
        if ( pRelation == NULL )
        { continue; }

        pRelation->AddRelation( pData[i].xDataToServer, RelationDefine::NotSendToClient );
    }
}

template< class T >
void RelationManager< T >::ProcessEnterWorld( unsigned int nPlayerID )
{
    T* pRelation = GetPlayerRelation( nPlayerID );
    if ( pRelation == NULL )
    { return; }

    pRelation->ProcessEnterWorld();
}

template< class T >
void RelationManager< T >::AddRelationInvite( unsigned int dwInviterID, const RelationInvite& xInvite )
{
    if ( xInvite.IsError() )
    { return; }

    MapInviteIter iter = m_mapInvite.find( dwInviterID );
    if ( iter != m_mapInvite.end() )
    {
        InviteVectorIter viter = find( iter->second.begin(), iter->second.end(), xInvite.dwTargetID );
        if ( viter == iter->second.end() )
        {
            iter->second.push_back( xInvite );
        }
        else
        {
            *viter = xInvite;
        }
    }
    else
    {
        InviteVector vecRelationInvite;
        vecRelationInvite.push_back( xInvite );

        m_mapInvite.insert( std::make_pair( dwInviterID, vecRelationInvite ) );
    }
}

template< class T >
void RelationManager< T >::RemoveRelationInvite( unsigned int dwInviterID, unsigned int dwTargetID )
{
    MapInviteIter iter = m_mapInvite.find( dwInviterID );
    if ( iter != m_mapInvite.end() )
    {
        InviteVectorIter viter = find( iter->second.begin(), iter->second.end(), dwTargetID );
        if ( viter != iter->second.end() )
        {
            iter->second.erase( viter );
        }

        if ( iter->second.empty() )
        {
            m_mapInvite.erase( iter );
        }
    }
}

template< class T >
RelationInvite* RelationManager< T >::GetRelationInvite( unsigned int dwInviterID, unsigned int dwTargetID )
{
    MapInviteIter iter = m_mapInvite.find( dwInviterID );
    if ( iter != m_mapInvite.end() )
    {
        InviteVectorIter viter = find( iter->second.begin(), iter->second.end(), dwTargetID );
        if ( viter != iter->second.end() )
        {
            return &( *viter );
        }
    }

    return NULL;
}

template< class T >
void RelationManager< T >::UpdateRelationInvite( unsigned int dwCurrentTime )
{
    for ( MapInviteIter iter = m_mapInvite.begin(); iter != m_mapInvite.end(); )
    {
        for ( InviteVectorIter viter = iter->second.begin(); viter != iter->second.end(); )
        {
            if ( viter->DoneTimer( dwCurrentTime ) )
            {
                viter = iter->second.erase( viter );
            }
            else
            {
                ++viter;
            }
        }

        if ( iter->second.empty() )
        {
            iter = m_mapInvite.erase( iter );
        }
        else
        {
            ++iter;
        }
    }
}

template< class T >
void RelationManager< T >::ProcessExitWorld( unsigned int dwPlayerID )
{
    T* pRelation = GetPlayerRelation( dwPlayerID );
    if ( pRelation == NULL )
    { return; }

    pRelation->ProcessExitWorld();
}

template< class T >
void RelationManager< T >::ProcessRelationToMe( T* pRelation )
{
    if ( pRelation == NULL )
    { return; }

    for ( RelationMapIter iter = m_mapRelations.begin(); iter != m_mapRelations.end(); ++iter )
    {
        if ( iter->first == pRelation->GetID() )
        { continue; }   // �Լ�������Ŷ
        
        RelationDataToServer* pData = iter->second->GetRelationData( pRelation->GetID() );
        if ( pData == NULL )
        { continue; }

        pRelation->AddRelationToMe( iter->first, pData->GetRelation() );
    }
}

template< class T >
void RelationManager< T >::SendQueryAttributeResultToClient( unsigned int nPlayerID, unsigned int* pAttributeID, int nCount )
{
    CenterRelation* pRelation = GetPlayerRelation( nPlayerID );
    if ( pRelation == NULL )
    { return; }

    pRelation->SendQueryAttributeResultToClient( pAttributeID, nCount );
}

template< class T >
void RelationManager< T >::AddRegisterID( unsigned int nPlayerID, unsigned int ustRelation )
{
    switch ( ustRelation )
    {
    case RelationDefine::Teacher:
        m_setTeacherID.insert( nPlayerID );
        break;
    case RelationDefine::Student:
        m_setStudentID.insert( nPlayerID );
        break;
    }
}

template< class T >
void RelationManager< T >::RemoveRegisterID( unsigned short ustRelation , unsigned int nPlayerID )
{
    switch( ustRelation )
    {
    case RelationDefine::Teacher:
        m_setTeacherID.erase( nPlayerID );
        break;
    case RelationDefine::Student:
        m_setStudentID.erase( nPlayerID );
        break;
    default:
        m_setTeacherID.erase( nPlayerID );
        m_setStudentID.erase( nPlayerID );
        break;
    }
}

template< class T >
bool RelationManager< T >::IsRegisterID( unsigned int nPlayerID, unsigned int ustRelation )
{
    switch ( ustRelation )
    {
    case RelationDefine::Teacher:
        return m_setTeacherID.find( nPlayerID ) != m_setTeacherID.end();
        break;
    case RelationDefine::Student:
        return m_setStudentID.find( nPlayerID ) != m_setStudentID.end();
        break;
    }

    return false;
}
template< class T >
void RelationManager< T >::AddSendedRelationId( unsigned int nPlayerID )
{
	m_setSendedRelationId.insert( nPlayerID );
}
template< class T >
bool RelationManager< T >::HaveSendedRelationId( unsigned int nPlayerID )
{
	return m_setSendedRelationId.find( nPlayerID ) != m_setSendedRelationId.end();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define theGameRelationManager RelationManager< GameRelation >::Instance()
#define theCenterRelationManager RelationManager< CenterRelation >::Instance()
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif