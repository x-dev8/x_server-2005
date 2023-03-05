#ifndef __GUILDMANAGER_H__
#define __GUILDMANAGER_H__
/************************************************************************
            ���������Զ���
            MaintenanceMan Mail: lori227@live.cn
************************************************************************/
#include "Singleton.h"
#include "Guild.h"
#include "RunStatus.h"
#include "IBAA_RandAlgorithm.h"
#include "GuildCampBattleConfig.h"
#include "ResourcePath.h"
template< class T >
class GuildManager : public ISingletion< GuildManager< T > >
{
public:
    GuildManager();
    ~GuildManager();

    // ���һ������
    bool AddGuild( T* pGuild );           

    // ɾ��һ������
    bool RemoveGuild( unsigned int nGuildID );     

     // ��ð�����Ϣ
    T* GetGuild( unsigned int nGuildID );      

	T* GetGuildByName( const char* szName );      

    // ���DBID��ð�����Ϣ
    T* GetGuildByPlayerID( unsigned int nPlayerID );   

    // ����Ƿ������ͬ���ֵİ���
    bool CheckGuildName( const char* szName );   

    // ִ���Զ�����
    void RunUpdate( unsigned int nCurrentTime );     

    // ����һ���µĹ���ID
    unsigned int MakeGuildID();                                 

    // �������а�����Ϣ����� or ���з�����
    void SendGuildListToClient( unsigned int nID );  

    // ���Ͱ�����Ϣ����
    void SendGuildListSuccess( unsigned int nID );

	// ���������30������Ϣ�������а��ɵİ��� luo.qin 4.20
	void SendPlayerLvUpToMaster( unsigned int nID, unsigned int nLv, char * szSpeakName );

    // ���������������Ϣ
    void SaveGuildInfo();        

    // �����������ݶ�ʱ��
    void StartLoadTimer();

    // ֹͣ�������ݶ�ʱ��
    void StopLoadTimer();

    // �Ƿ�������
    bool GetLoadSuccess() const;

    // �����Ƿ�������
    void SetLoadSuccess( bool bValue );

    // ��ʼ�������б�
    void InitGuild( GuildDataToServer* pList, int nCount );

    // ��ʼ�����ɳ�Ա�б�
    void InitGuildMember( GuildMember* pList, int nCount );

    // ���һ���뿪����ʱ��
    void AddLeaveGuild( unsigned int nPlayerID );

    // �ж��Ƿ�����뿪��������ʱ��
    bool CheckLeaveGuild( unsigned int nPlayerID, unsigned int nPassTime );

	map< unsigned int, T* >& GetAllGuild();

	//���ָ��������ָ��Ȩ�޵�����
	unsigned int GetSumByCampBattleValue(unsigned int GuildID,unsigned int Value);

	GuildCampBattleConfig* GetCampBattleConfig() {return &m_CampBattleConfig;}
protected:
    typedef typename std::map< unsigned int, T* > GuildMap;
    typedef typename GuildMap::iterator GuildMapIter;

    typedef typename std::map< std::string, unsigned int> GuildNameMap;
    typedef typename GuildNameMap::iterator GuildNameMapIter;

    typedef std::map< unsigned int, TimeEx > LeaveGuildMap;
    typedef LeaveGuildMap::iterator LeaveGuildMapIter;

    // ���һ���������ֹ���
    void AddGuildName( T* pGuild );

    // ɾ��һ���������ֹ���
    void RemoveGuildName( T* pGuild );

    // ���ͼ��ع�����Ϣ����
    void ProcessLoadGuildData( unsigned int nCurrentTime );

private:
    GuildMap m_mapGuild;
    GuildNameMap m_mapGuildName;
    GameTimerEx m_xUpdateTimer;

    // ��¼�뿪���ɵ�ʱ��
    LeaveGuildMap m_mapLeaveGuild;

    bool m_bLoadSuccess;        // �Ƿ���سɹ�
    bool m_bLoadTimerStart;     // �Ƿ��������ض�ʱ��
    GameTimerEx m_xLoadTimer;   // ���ض�ʱ��

	GuildCampBattleConfig m_CampBattleConfig;
};
////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
template< class T >
unsigned int GuildManager< T >::GetSumByCampBattleValue(unsigned int GuildID,unsigned int Value)
{
	 GuildMapIter iter =m_mapGuild.find(GuildID);
	 if(iter == m_mapGuild.end())
		 return 0xFFFFFFFF;
	 else
	 {
		return iter->second->GetSumByCampBattleValue(Value);
	 }
}
template< class T >
GuildManager< T >::GuildManager() : m_bLoadTimerStart( false ), m_bLoadSuccess( false )
{
    m_mapGuild.clear();
    m_mapGuildName.clear();

    m_xUpdateTimer.StartTimer( 1, GuildDefine::UpdateSpaceTime );

	m_CampBattleConfig.OnLoadFilePath(GUILDCAMPBATTLE_FILEPATH);
}

template< class T >
GuildManager< T >::~GuildManager()
{
    for ( GuildMapIter iter = m_mapGuild.begin(); iter != m_mapGuild.end(); ++iter )
    {
        iter->second->Release();
    }
}

template< class T >
bool GuildManager< T >::AddGuild( T* pGuild )
{
    if ( pGuild == NULL )
    { return false; }

    // ������ֹ���
    AddGuildName( pGuild );

    return m_mapGuild.insert( std::make_pair( pGuild->GetID(), pGuild ) ).second;
}

template< class T >
bool GuildManager< T >::RemoveGuild( unsigned int nGuildID )
{
    GuildMapIter iter = m_mapGuild.find( nGuildID );
    if ( iter == m_mapGuild.end() )
    { return false; }

    RemoveGuildName( iter->second );

    iter->second->Release();
    m_mapGuild.erase( iter );
    return true;
}

template< class T >
T* GuildManager< T >::GetGuild( unsigned int nGuildID )
{
    if ( nGuildID == GuildDefine::InitID )
    { return NULL; }

    GuildMapIter iter = m_mapGuild.find( nGuildID );
    if ( iter == m_mapGuild.end() )
    { return NULL; }

    return iter->second;
}

template< class T >
T* GuildManager< T >::GetGuildByPlayerID( unsigned int nPlayerID )
{

    for ( GuildMapIter iter = m_mapGuild.begin(); iter != m_mapGuild.end(); ++iter )
    {
        GuildMember* pMember = iter->second->GetMember( nPlayerID );
        if ( pMember != NULL )
        {
            return iter->second;
        }
    }

    return NULL;
}

template< class T >
void GuildManager< T >::AddGuildName( T* pGuild )
{
    if ( pGuild == NULL )
    { return; }

    m_mapGuildName[ pGuild->GetName() ] = pGuild->GetID();
}

template< class T >
void GuildManager< T >::RemoveGuildName( T* pGuild )
{
    if ( pGuild == NULL )
    { return; }

    GuildNameMapIter iter = m_mapGuildName.find( pGuild->GetName() );
    if ( iter == m_mapGuildName.end() )
    { return; }

    m_mapGuildName.erase( iter );
}
template< class T >
T* GuildManager< T >::GetGuildByName( const char* szName )
{
    GuildNameMapIter iter = m_mapGuildName.find( szName );
    if ( iter == m_mapGuildName.end() )
    { return NULL; }

	return GetGuild(iter->second);
}
template< class T >
bool GuildManager< T >::CheckGuildName( const char* szName )
{
    GuildNameMapIter iter = m_mapGuildName.find( szName );
    return iter != m_mapGuildName.end();
}


template< class T >
unsigned int GuildManager< T >::MakeGuildID()
{
    unsigned int nGuildID = theRand.rand32() % 1000000 + 1000000;
    while( GetGuild( nGuildID ) != NULL )
    { 
        nGuildID = rand() % 1000000 + 1000000;
    }

    return nGuildID;
}

template< class T >     // ���������������Ϣ
void GuildManager< T >::SaveGuildInfo()
{
    for ( GuildMapIter iter = m_mapGuild.begin(); iter != m_mapGuild.end(); ++iter )
    {
        iter->second->SaveGuildAndMemberData();
    }
}

template< class T >
void GuildManager< T >::StartLoadTimer()
{
    if ( m_bLoadTimerStart )
    { return; }     // �Ѿ�����

    m_bLoadTimerStart = true;
    m_xLoadTimer.StartTimer( 1, GuildDefine::LoadSpaceTime );
}

template< class T >
void GuildManager< T >::StopLoadTimer()
{
    m_xLoadTimer.StopTimer();
}

template< class T >
void GuildManager< T >::InitGuild( GuildDataToServer* pList, int nCount )
{
    if ( pList == NULL || GetLoadSuccess() )
    { return; }

    StopLoadTimer();

    for ( int i = 0; i < nCount; ++i )
    {
        T* pGuild = T::CreateGuild();
        if ( pGuild == NULL )
        { continue; }
        
        pGuild->SetGuildDataToServer( pList[i] );
        AddGuild( pGuild );
    }
}

template< class T >
void GuildManager< T >::InitGuildMember( GuildMember* pList, int nCount )
{
    if ( pList == NULL || nCount == 0 )
    { return; }

    for ( int i = 0; i < nCount; ++i )
    {
        T* pGuild = GetGuild( pList[i].GetGuildID() );
        if ( pGuild == NULL )
        { continue; }

        pGuild->AddMember( pList[i] );
    }
}

template< class T >
inline bool GuildManager< T >::GetLoadSuccess() const
{
    return m_bLoadSuccess;
}


template< class T >
inline void GuildManager< T >::SetLoadSuccess( bool bValue )
{
    m_bLoadSuccess = bValue;
	if (bValue)
	{
		theRunStatus.SetLoadSuccess(RunStatusDefine::LoadGuildSuccess);
	}
}

template< class T >
inline void GuildManager< T >::AddLeaveGuild( unsigned int nPlayerID )
{
    m_mapLeaveGuild[ nPlayerID ] = TimeEx::GetCurrentTime();
}


template< class T >
bool GuildManager< T >::CheckLeaveGuild( unsigned int nPlayerID, unsigned int nPassTime )
{
    LeaveGuildMapIter iter = m_mapLeaveGuild.find( nPlayerID );
    if ( iter == m_mapLeaveGuild.end() )
    { return true; }

    return TimeEx::IsPassCurrentTime( iter->second.GetTime(), nPassTime );
}

////////////////////////////////////////////////////////////////////////////

#define theGameGuildManager GuildManager< GameGuild >::Instance()
#define theCenterGuildManager GuildManager< CenterGuild >::Instance()
////////////////////////////////////////////////////////////////////////////
#endif