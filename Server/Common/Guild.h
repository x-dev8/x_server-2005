#ifndef __GUILD_H__
#define __GUILD_H__
/************************************************************************
            ���������Զ���
            FileName : Guild.h
            MaintenanceMan Mail: lori227@live.cn
************************************************************************/
#include <string>
#include <map>
#include "GuildDefine.h"
#include "memory_pool.h"
#include "GameTimer.h"
#include "GuildConfig.h"
#include "LogEventService.h"
struct Msg;

// �������
class GuildDelateInfo
{
public:
    GuildDelateInfo() : m_nDelateMemberID( GuildDefine::InitID ), m_nSendMemberCount( 0 )
    {
    }

    unsigned int GetID() const { return m_nDelateMemberID; }
    unsigned int GetTotalCount() const { return m_nSendMemberCount; }
    unsigned int GetAgreeCount() const { return static_cast< unsigned int >( m_setAgreeMember.size() ); }

    void SetID( unsigned int nValue ) { m_nDelateMemberID = nValue; }
    void SetTotalCount( unsigned int nValue ) { m_nSendMemberCount = nValue; }

    void ClearAgreeCount(){ m_setAgreeMember.clear(); }
    void AddAgreeMember( unsigned int nValue ) { m_setAgreeMember.insert( nValue ); }

    void StartTimer( unsigned int nCurrentTime, unsigned int nKeepTime )
    { m_xDelateTimer.StartTimer( nCurrentTime, nKeepTime ); }

    bool DoneTimer() { return m_xDelateTimer.DoneTimer(); }

    void Reset()
    {
        m_nDelateMemberID = GuildDefine::InitID;
        m_setAgreeMember.clear(); 
        m_nSendMemberCount = 0;
    }
protected:

    typedef std::set< unsigned int > AgreeMemberSet;

    unsigned int m_nDelateMemberID;       // �������ĳ�ԱID
    unsigned int m_nSendMemberCount;      // �ܹ����͵ĸ���
    AgreeMemberSet m_setAgreeMember;      // ͬ��ĳ�Ա
    GameTimerEx m_xDelateTimer;           // ������ʱ��
};

template< class T >
class GuildInfo : public GuildDataToServer, INHERIT_POOL_PARAM( GuildInfo< T >, 50 )
{
public:
    GuildInfo();
    static GuildInfo* CreateGuild() { return CNewWithDebug< GuildInfo< T > >::Alloc( 1, "����GuildInfoʵ��" ); }
    virtual void Release() { CNewWithDebug< GuildInfo< T > >::Free( this ); }

    // ��ӳ�Ա
    bool AddMember( const GuildMember& xMember );    

    // ɾ����Ա
    bool RemoveMember( unsigned int nPlayerID );   

    // ���ҳ�Ա
    GuildMember* GetMember( unsigned int nPlayerID );     

    // ��ó�Ա����
    unsigned int MemberCount() const;       

    // ��ø�����
    GuildMember* GetViceMaster();     

    // ���ĳ������峤 
    GuildMember* GetFamilyMaster( unsigned char uchFamilyID );  

    // �Ƿ��ǰ���
    bool IsMaster( unsigned int nPlayerID ) const;            

    // �Ƿ���ĳ��Ȩ��
    bool HaveRight( unsigned int nPlayerID, unsigned int nRight );   

    // �ж�ְλ��С
    bool CheckPosition( unsigned int nPlayerID, unsigned int nTargetID );  

    // ��ð��ɳ�Ա�б�
    int GetMemberList( GuildMember* pMember, int nCount );   

    // �����Ա����
    void ProcessMemberJoinGuild( const GuildMember& xMember );    

    // �����Ա�뿪
    void ProcessMemberLeaveGuild( unsigned int nPlayerID );    

    // ������ɽ�ɢ
    void ProcessDisbandGuild();                   

    // ��Ա����
    void ProcessEnterWorld( unsigned int nPlayerID );     

    // ��Ա����
    void ProcessExitWorld( unsigned int nPlayerID );     

    // �����Ա���ݸ���
    void ProcessMemberDataUpdate( unsigned int nPlayerID, unsigned char uchType, unsigned int nValue ); 
    void ProcessMemberDataUpdate( GuildMember* pMember, unsigned char uchType, unsigned int nValue ); 

    // ����������ݸ���
    void ProcessGuildDataUpdate( unsigned char uchType, __int64 nValue );    

    // ������ɹ���ı�
    void ProcessGuildNoticeChange( const char* szNotice );   

	void ProcessGuildNameChange(const char * Name);

	// ���������ּ�ı�
	void ProcessGuildAimChange( const char* szAim, __int64 nTime = 0 );

    // ������ɼ�����Ϣ�ı�
    void ProcessFamilyChange( unsigned int nPlayerID, unsigned char uchFamilyID, const char* szName );       

    // �������ͼ���������ʽ����һ������
    static unsigned int SetFormatGuildVar( unsigned short nIndex, short nValue );

    // ��������еļ������������ͱ���ֵ
    static void GetFormatGuildVar( unsigned int nValue, unsigned short &nIndex, short &nVar );

    // ���õ������ID
    void SetDelateMemberID( unsigned int nValue );

    // ��õ�����Ϣ
    GuildDelateInfo& GetDelateInfo();

    // �������׶�ʱ��
    void StartDonateTimer();

    // ֹͣ���׶�ʱ��
    void StopDonateTimer();

    // �Ƿ��ھ���ʱ����
    bool CheckDonateTimer();

    // ���þ��׵��ܽ�Ǯ
    void SetDonateMoney( unsigned int nValue );

    // ��þ��׵��ܽ�Ǯ
    unsigned int GetDonateMoney() const;

    // ����������񷢲�
    void ProcessQuestRelease( unsigned int nQuestType, __int64 n64Time );

    // ��������������г�Ա�Ļ�Ծ��
    void ProcessClearMemberActivity();

    // ������ɵ�������
    void ProcessGuildDelateRequest( unsigned int nPlayerID );

    // ��������ټ�����
    void ProcessGuildConveneReq( unsigned int nPlayerID, unsigned int nMapID, float fPosX, float fPosY, float fDir, unsigned char uchLevel );

    // ��������ټ���ʱ
    void ProcessGuildConveneTimeOut();
    //////////////////////////////////////////////////////////////////    GameServer
    // ������ָ��
    static T* GetPlayer( unsigned int nPlayerID );

    // ���Ͱ������ݵ��ͻ��� or GameServer
    void SendGuildDataToClient( unsigned int nAppiontID );    

    // ������Ϣ�����а��ɳ�Ա
    void SendMessageToGuild( Msg* pMessage, unsigned int nExceptID = GuildDefine::InitID, unsigned short ustLevel = 0, bool bSendToCenter = false );

    // ���Ͱ������ݸı�����CenterServer
    void SendGuildDataChangeReqMessage( unsigned char uchChangeType, unsigned char uchOperateType, unsigned int nValue );   

    // ���ͳ�Ա���ݸı�����CenterServer
    void SendMemberDataChangeReqMessage( unsigned int nPlayerID, unsigned char uchChangeType, unsigned char uchOperatetype, unsigned int nValue );  

    // ������ʵ��
    unsigned int GetGuildStrength();

    // ��ӹ��ҳƺ�
    void SetCountryTitle( unsigned char uchMemberTitle, unsigned char uchMasterTitle );

    // ������ҳƺ�
    void ClearCountryTitle();

    // ��������ټ�����
    void ProcessGuildConveneAck( T* pPlayer );
    //////////////////////////////////////////////////////////////////    CenterServer
    // �����Զ�����
    unsigned short RunUpdate( unsigned int nCurrentTime );   

    // ����������ݵ����ݿ�
    void SaveGuildDataToDatabase();     

    // ���������Ϣ�����ݿ�
    void SaveMemberDataToDatabase();   

    // ��������ϵʱ, Ҫ������������
    void SaveGuildAndMemberData();   

    // �������ɽ�Ǯ
    void OperateGuildMoney( unsigned char uchType, unsigned int nValue );   

    // �������ɾ���
    void OperateGuildExp( unsigned char uchType, unsigned int nValue );   

    // ��������ʹ����
    void OperateGuildMission( unsigned char uchType, unsigned int nValue );   

    // �������ɽ���
    void OperateGuildSalary( unsigned char uchType, unsigned int nValue );

    // �������ɼ�������
    void OperateGuildVar( unsigned char uchType, unsigned int nIndex, unsigned int nValue );   

    // ���������̵�
    void OperateGuildShopLevel( unsigned char uchType, unsigned int nValue );

    // ������Ա�ﹱ
    void OperateMemberOffer( unsigned int nPlayerID, unsigned char uchType, unsigned int nValue );
    void OperateMemberOffer( GuildMember* pMember, unsigned char uchType, unsigned int nValue );

    // ������Ա��Ծ��
    void OperateMemberActivity( unsigned int nPlayerID, unsigned char uchType, unsigned int nValue );

    // ���һ�������¼
    void AddInvite( unsigned int nPlayerID, unsigned int nTargetID, unsigned int nInviteTime );

    // ����һ�������¼
    GuildInvite* GetInvite( unsigned int nTargetID );

    // ɾ��һ�������¼
    void RemoveInvite( unsigned int nTargetID );

    // ���һ�������¼
    void AddRequest( GuildMember& xMember, unsigned int nRequestTime );

    // ����һ�������¼
    GuildRequest* GetRequest( unsigned int nPlayerID );

    // ɾ��һ�������¼
    void RemoveRequest( unsigned int nPlayerID );

    // ������߳�Ա����
    unsigned int GetOnLineCount() const;

	// �Ƿ���Ը���ּ
	bool CanChangeAim() const;

	// ���Ͱ������񷢲�״̬��Ϣ
	void SendQuestReleaseStatusMessage();

	void SendAllRequest(uint32 PlayerID);

	unsigned int GetSumByCampBattleValue(unsigned int Value);

	void UpdateGuildMemberOnLineTime(unsigned int PlayerID,__int64 Time);
protected:
    // ������߳�Ա����
    void AddOnLineCount();      

    // �������߳�Ա����
    void SubOnLineCount();   

    // �����������ݱ��涨ʱ��
    void StartSaveTimer();   

    // ��������Զ���ɢʱ��
    void ProcessDisbandTime();   

    // ����ɾ��һ������
    void ProcessRemoveFamily( unsigned char uchFamilyID );     

    // ������Ұ���ְλ�ı�
    void ProcessGuildPositionChange( GuildMember* pMember, unsigned char uchPosition );     

    // ������Ҽ���ı�
    void ProcessMemberFamilyChange( GuildMember* pMember );       

    // ���ͳ�Ա���ݸ�����Ϣ
    void SendMemberDataUpdateMessage( unsigned int nPlayerID, unsigned char uchType, unsigned int nValue );  

    // ���Ͱ������ݸ�����Ϣ
    void SendGuildDataUpdateMessage( unsigned char uchType, __int64 nValue );  

    // ���������Ҿ���
    void ProcessUpdateMemberExp( unsigned int nPlayerID, unsigned int nValue );   

    // ���������¼
    void UpdateInivte( unsigned int nCurrentTime ); 

    // ���������¼
    void UpdateRequest( unsigned int nCurrentTime );    

    // ���������
    void ProcessGuildDelateResult();

    // ������׽���
    void ProcessGuildDonate();

    // ���һ����Ҫ����ĳ�Ա
    void AddNeedSaveMember( unsigned int nPlayerID );
   
    // ����������ɳ�Ա�Ļ�Ծ����Ϣ
    void SendClearMemberActivityMessage();

    // �������ʹ����
    unsigned short ProcessGuildMissionSettle();

    // ������ɽ���
    void ProcessClearGuildSalary();

    // ����ÿ��12����ɼ�����0
    unsigned short ProcessGuildVarClear();

	// �����޸���ּ��CD
	void SetChangeAimCD( __int64 nTime );

	// ��ȡ�޸����õ�CD
	__int64 GetChangeAimCD();

private:
    typedef typename std::map< unsigned int, GuildMember > MemberMap;
    typedef typename MemberMap::iterator MemberMapIter;

    typedef typename std::set< unsigned int > SaveSet;
    typedef typename SaveSet::iterator SaveSetIter;

    typedef typename std::map< unsigned int, GuildInvite > InviteMap;
    typedef typename InviteMap::iterator InviteMapIter;

    typedef typename std::map< unsigned int, GuildRequest > RequestMap;
    typedef typename RequestMap::iterator RequestMapIter;

    MemberMap m_mapMember;              // ��Ա�б�
    int m_nOnLineCount;                 // ������Ҹ���

    InviteMap m_mapInvite;              // ������Ϣ
    RequestMap m_mapRequest;            // �����¼
    
    SaveSet m_setSave;                  // ��Ҫ����ĳ�Ա
    GameTimerEx m_xDataSaveTimer;       // �������ݱ���Timer
    GameTimerEx m_xMemberSaveTimer;     // ���ɳ�Ա�����Timer

    GameTimerEx m_xDonateTimer;         // ������׵�Timer
    unsigned int m_nDonateMoney;        // ���׵�Ǯ
    ///////////////////////////////////////////////////////////////////
    GuildDelateInfo m_xGuildDelate;     // ������Ϣ

    GameTimerEx m_xReleaseTimer;        // ���񷢲���ʱ��
    GameTimerEx m_xUpdateActivityTimer; // ��Ծ�ȶ�ʱ��
    GameTimerEx m_xUpdateSalaryTimer;   // ���ɽ�����ʱ��
    GameTimerEx m_xUpdateMissionTimer;  // ʹ���㶨ʱ��

    // �����ټ�
    GameTimerEx m_xConveneTimer;        // �����ټ���ʱ��
    unsigned char m_uchConveneLevel;    // �ټ��ĵȼ�����
    unsigned int m_nConveneMapID;       // �ټ��ĵ�ͼ
    float m_fConvenePosX;               // �ټ�X����
    float m_fConvenePosY;               // �ټ�Y����
    float m_fConveneDir;                // �ټ�����

    unsigned int m_nVarClearTime;       // ����ʱ�������12����0

	__int64 m_nChangeAimCD;				// �޸���ּ��CD
};

/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////
template< class T >
GuildInfo< T >::GuildInfo() : m_nOnLineCount( 0 ) , m_nDonateMoney( 0 ), m_nConveneMapID( 0 ), m_nVarClearTime( 0 ), m_nChangeAimCD( 0 )
{
    m_mapMember.clear();
    m_setSave.clear();
    m_xMemberSaveTimer.StartTimer( 1, GuildDefine::SaveSpaveTime );
}

template< class T >
inline bool GuildInfo< T >::IsMaster( unsigned int nPlayerID  ) const
{
    return GetMasterID() == nPlayerID;
}
template< class T >
unsigned int GuildInfo< T >::GetSumByCampBattleValue(unsigned int Value)
{
	unsigned int Sum = 0;
	for ( MemberMapIter iter = m_mapMember.begin(); iter != m_mapMember.end(); ++iter )
    {
        if ( iter->second.GetCampBattleValue() & Value )
			++Sum;
    }
	return Sum;
}
template< class T >
bool GuildInfo< T >::HaveRight( unsigned int nPlayerID, unsigned int nRight )
{
    GuildMember* pMember = GetMember( nPlayerID );
    if ( pMember == NULL )
    { return false; }

    unsigned int nMemberRight = GuildDefine::GetRightByPositon( pMember->GetPosition() );
    return ( nMemberRight & nRight ) != 0;
}

template< class T >
bool GuildInfo< T >::CheckPosition( unsigned int nPlayerID, unsigned int nTargetID )
{
    GuildMember* pMember = GetMember( nPlayerID );
    if ( pMember == NULL )
    { return false; }

    GuildMember* pTarget = GetMember( nTargetID );
    if ( pTarget == NULL )
    { return false; }

    return pMember->GetPosition() > pTarget->GetPosition();
}

template< class T >
inline unsigned int GuildInfo< T >::MemberCount() const
{
    return static_cast< unsigned int >( m_mapMember.size() );
}

template< class T >
inline bool GuildInfo< T >::AddMember( const GuildMember& xMember )
{
    if ( xMember.GetOnLine() )
    { AddOnLineCount(); }

    return m_mapMember.insert( std::make_pair( xMember.GetID(), xMember ) ).second;
}

template< class T >
bool GuildInfo< T >::RemoveMember( unsigned int nPlayerID )
{
    MemberMapIter iter = m_mapMember.find( nPlayerID );
    if ( iter == m_mapMember.end() )
    { return false; }

    if ( iter->second.GetOnLine() )
    { SubOnLineCount(); }

    m_mapMember.erase( iter );

    return true;
}

template< class T >
GuildMember* GuildInfo< T >::GetMember( unsigned int nPlayerID )
{
    MemberMapIter iter = m_mapMember.find( nPlayerID );
    if ( iter == m_mapMember.end() )
    { return NULL; }

    return &( iter->second );
}

template< class T >
GuildMember* GuildInfo< T >::GetViceMaster()
{
    for ( MemberMapIter iter = m_mapMember.begin(); iter != m_mapMember.end(); ++iter )
    {
        if ( iter->second.GetPosition() != GuildDefine::Position_ViceMaster )
        { continue; }

        return &( iter->second );
    }

    return NULL;
}

template< class T >
GuildMember* GuildInfo< T >::GetFamilyMaster( unsigned char uchFamilyID )
{
    for ( MemberMapIter iter = m_mapMember.begin(); iter != m_mapMember.end(); ++iter )
    {
        if ( iter->second.GetPosition() != GuildDefine::Position_FamilyMaster )
        { continue; }

        if ( iter->second.GetFamilyID() != uchFamilyID )
        { continue; }

        return &( iter->second );
    }

    return NULL;
}

template< class T >
inline void GuildInfo< T >::AddOnLineCount()
{
    ++m_nOnLineCount;
}

template< class T >
inline void GuildInfo< T >::SubOnLineCount()
{
    --m_nOnLineCount;
    if ( m_nOnLineCount < 0 )
    { m_nOnLineCount = 0; }
}

template< class T >
inline unsigned int GuildInfo< T >::GetOnLineCount() const
{
    return m_nOnLineCount;
}


template< class T >
inline void GuildInfo< T >::AddNeedSaveMember( unsigned int nPlayerID )
{
    m_setSave.insert( nPlayerID );
}

template< class T >
int GuildInfo< T >::GetMemberList( GuildMember* pMember, int nCount )
{
    if ( pMember == NULL || nCount == 0 )
    { return 0; }

    int nIndex = 0;
    for ( MemberMapIter iter = m_mapMember.begin(); iter != m_mapMember.end(); ++iter )
    {
        pMember[nIndex] = iter->second;
        ++nIndex;
    }

    return nIndex;
}

template< class T >
void GuildInfo< T >::AddInvite( unsigned int nPlayerID, unsigned int nTargetID, unsigned int nInviteTime )
{
    GuildInvite xInvite;
    xInvite.SetPlayerID( nPlayerID );
    xInvite.SetTargetID( nTargetID );
    xInvite.SetInviteTime( nInviteTime );

    m_mapInvite[ nTargetID ] = xInvite;
}

template< class T >
GuildInvite* GuildInfo< T >::GetInvite( unsigned int nTargetID )
{
    InviteMapIter iter = m_mapInvite.find( nTargetID );
    if ( iter == m_mapInvite.end() )
    { return NULL; }

    return &( iter->second );
}

template< class T >
void GuildInfo< T >::RemoveInvite( unsigned int nTargetID )
{
    InviteMapIter iter = m_mapInvite.find( nTargetID );
    if ( iter == m_mapInvite.end() )
    { return; }

    m_mapInvite.erase( iter );
}

template< class T >
void GuildInfo< T >::AddRequest( GuildMember& xMember, unsigned int nRequestTime )
{
    GuildRequest xRequest;
    xRequest.SetMember( xMember );
    xRequest.SetRequestTime( nRequestTime );

    m_mapRequest[ xMember.GetID() ] = xRequest;
}

template< class T >
GuildRequest* GuildInfo< T >::GetRequest( unsigned int nPlayerID )
{
    RequestMapIter iter = m_mapRequest.find( nPlayerID );
    if ( iter == m_mapRequest.end() )
    { return NULL; }

    return &( iter->second );
}

template< class T >
void GuildInfo< T >::RemoveRequest( unsigned int nPlayerID )
{
    RequestMapIter iter = m_mapRequest.find( nPlayerID );
    if ( iter == m_mapRequest.end() )
    { return; }

    m_mapRequest.erase( iter );
}

template< class T >
inline void GuildInfo< T >::StartSaveTimer()
{
    m_xDataSaveTimer.StartTimer( HQ_TimeGetTime(), GuildDefine::SaveSpaveTime );
}

template< class T >
void GuildInfo< T >::ProcessMemberDataUpdate( unsigned int nPlayerID, unsigned char uchType, unsigned int nValue )
{
    GuildMember* pMember = GetMember( nPlayerID );
    if ( pMember == NULL )
    { return; }

    ProcessMemberDataUpdate( pMember, uchType, nValue );
}

template< class T >
void GuildInfo< T >::ProcessMemberDataUpdate( GuildMember* pMember, unsigned char uchType, unsigned int nValue )
{
    if ( pMember == NULL )
    { return; }

    switch ( uchType )
    {
    case GuildDefine::UpdateMemberOnLine:   // ��������
        pMember->SetOnLine( nValue == 1 ? true : false );
        break;
    case GuildDefine::UpdateMemberLevel:    // ���µȼ�
        pMember->SetLevel( nValue );
        break;
	case GuildDefine::UpdateMemberCampBattleValue:
		pMember->SetCampBattleValue(nValue);
		break;
    case GuildDefine::UpdateMemberPosition: // ����ְλ
        pMember->SetPosition( nValue );
        ProcessGuildPositionChange( pMember, nValue );    // �������ְλ�ı�
        break;
    case GuildDefine::UpdateMemberFamily:   // ���¼���
        pMember->SetFamilyID( nValue );
        ProcessMemberFamilyChange( pMember );
        break;
    case GuildDefine::UpdateMemberActivity: // ���»�Ծ��
        pMember->SetActivity( nValue );
        break;
    case GuildDefine::UpdateMemberOffer:    // ���°ﹱ
        pMember->SetOffer( nValue );
        break;
    case GuildDefine::UpdateMemberProfession:  // ����ְҵ
        pMember->SetProfession( nValue );
        break;
    case GuildDefine::UpdateMemberExp:      // ���³�Ա����
        break;
    default:
        return;
    }

    SendMemberDataUpdateMessage( pMember->GetID(), uchType, nValue );
}

template< class T >
void GuildInfo< T >::ProcessGuildDataUpdate( unsigned char uchType, __int64 n64Value )
{
    switch ( uchType )
    {
    case GuildDefine::UpdateGuildLevel:     // ���°��ɵȼ�
        SetLevel( static_cast< unsigned int >( n64Value ) );
        break;
    case GuildDefine::UpdateGuildMoney:     // ���°��ɽ�Ǯ
		{
        SetMoney( static_cast< unsigned int >( n64Value ) );
		}
		//theLogEventService.LogGuildDetail(0,0,GetID(),n64Value,0,0);
        break;
    case GuildDefine::UpdateGuildExp:       // ���°��ɾ���
		{
        SetExp( static_cast< unsigned int >( n64Value ) );
		//theLogEventService.LogGuildDetail(0,0,GetID(),0,n64Value,0);
		}
        break;
    case GuildDefine::UpdateGuildMission:   // ���°���ʹ����
        SetMission( static_cast< unsigned int >( n64Value ) );
        break;
    case GuildDefine::UpdateGuildMaster:    // ���°��ɰ���
        SetMasterID( static_cast< unsigned int >( n64Value ) );
        break;
    case GuildDefine::UpdateGuildVar:       // ���°��ɼ���
        {
            unsigned short nIndex = 0;
            short nVar = 0;
            GetFormatGuildVar( static_cast< unsigned int >( n64Value ), nIndex, nVar );
            SetGuildVar( nIndex, nVar );
        }
        break;
    case GuildDefine::UpdateGuildDonate:    // ���°��ɾ��׵�����Ǯ
        SetDonateMoney( static_cast< unsigned int >( n64Value ) );
        break;
    case GuildDefine::UpdateGuildShopLevel: // ���°����̵�ȼ�
        SetShopLevel( static_cast< unsigned int >( n64Value ) );
        break;
    case GuildDefine::UpdateGuildDisbandTime:
        SetDisbandTime( n64Value );
        break;
    case GuildDefine::UpdateGuildSalary:
        SetSalary( static_cast< unsigned int >( n64Value ) );
        break;
	case  GuildDefine::UpdateGuildMissionCount:
		SetMissionCount( static_cast< unsigned int >( n64Value ) );
		break;
	case GuildDefine::UpdateGuildBattleSum:
		SetBattleSum(static_cast< unsigned int >( n64Value));
		break;
	case GuildDefine::UpdateGuildChangeName:
		SetChangeName(n64Value!=0?true:false); 
		break;
	case GuildDefine::UpdateGuildCampBattlePoint:
		SetGuildCampBattlePoint(static_cast<unsigned int>(n64Value));
		break;
    default:
        return;
    }

    SendGuildDataUpdateMessage( uchType, n64Value );
}

template< class T >
void GuildInfo< T >::OperateGuildMoney( unsigned char uchType, unsigned int nValue  )
{
    switch ( uchType )
    {
    case GuildDefine::OperateSet:
        break;
    case GuildDefine::OperateAdd:
        {
            const GuildConfig::LevelSetting* pSetting = theGuildConfig.GetLevelSetting( GetLevel() );
            if ( pSetting == NULL )
            { return; }

            nValue += GetMoney();
            if ( nValue > pSetting->GetMaxMoney() )
            { nValue = pSetting->GetMaxMoney(); }
        }
        break;
    case GuildDefine::OperateSub:
        if ( GetMoney() < nValue )
        { 
            nValue = 0; 
        }
        else
        {
            nValue = GetMoney() - nValue;
        }
        break;
    default:
        return;
    }

    ProcessGuildDataUpdate( GuildDefine::UpdateGuildMoney, nValue );
}

template< class T >
void GuildInfo< T >::OperateGuildExp( unsigned char uchType, unsigned int nValue  )
{
    switch ( uchType )
    {
    case GuildDefine::OperateSet:
        break;
    case GuildDefine::OperateAdd:
        {
           const GuildConfig::LevelSetting* pSetting = theGuildConfig.GetLevelSetting( GetLevel() );
            if ( pSetting == NULL )
            { return; }

            nValue += GetExp();
            if ( nValue > pSetting->GetMaxExp() )
            { nValue = pSetting->GetMaxExp(); }
        }
        break;
    case GuildDefine::OperateSub:
        {
            if ( GetExp() < nValue )
            { nValue = 0; }
            else
            { nValue = GetExp() - nValue; }
        }
        break;
    default:
        return;
    }

    ProcessGuildDataUpdate( GuildDefine::UpdateGuildExp, nValue );
}

template< class T >
void GuildInfo< T >::OperateGuildMission( unsigned char uchType, unsigned int nValue  )
{
    switch ( uchType )
    {
    case GuildDefine::OperateSet:
        break;
    case GuildDefine::OperateAdd:
        nValue += GetMission(); // ʹ����������޼�
        break;
    case GuildDefine::OperateSub:
        {
            if ( GetMission() < nValue )
            { nValue = 0; }
            else
            { nValue = GetMission() - nValue; }
        }
        break;
    default:
        return;
    }

    ProcessGuildDataUpdate( GuildDefine::UpdateGuildMission, nValue );
}

template< class T >
void GuildInfo< T >::OperateGuildSalary( unsigned char uchType, unsigned int nValue  )
{
    switch ( uchType )
    {
    case GuildDefine::OperateSet:
        break;
    case GuildDefine::OperateAdd:
        nValue += GetSalary(); // ʹ����������޼�
        break;
    case GuildDefine::OperateSub:
        {
            if ( GetSalary() < nValue )
            { nValue = 0; }
            else
            { nValue = GetSalary() - nValue; }
        }
        break;
    default:
        return;
    }

    ProcessGuildDataUpdate( GuildDefine::UpdateGuildSalary, nValue );
}

template< class T >
void GuildInfo< T >::OperateGuildVar( unsigned char uchType, unsigned int nIndex, unsigned int nValue  )
{
    switch ( uchType )
    {
    case GuildDefine::OperateSet:
        break;
    case GuildDefine::OperateAdd:
        nValue += GetGuildVar( nIndex ); 
        break;
    case GuildDefine::OperateSub:
        nValue = GetGuildVar( nIndex ) - nValue;
        break;
    default:
        return;
    }

    unsigned int nFormatVar = SetFormatGuildVar( nIndex, nValue );
    ProcessGuildDataUpdate( GuildDefine::UpdateGuildVar, nFormatVar );
}

template< class T >
void GuildInfo< T >::OperateGuildShopLevel( unsigned char uchType, unsigned int nValue  )
{
    switch ( uchType )
    {
    case GuildDefine::OperateSet:
        SetShopLevel( nValue );
        break;
    case GuildDefine::OperateAdd:
        SetShopActive( nValue );
        break;
    default:
        return;
    }

    ProcessGuildDataUpdate( GuildDefine::UpdateGuildShopLevel, GetShopLevel() );
}

template< class T >
void GuildInfo< T >::OperateMemberOffer( unsigned int nPlayerID, unsigned char uchType, unsigned int nValue  )
{
    GuildMember* pMember = GetMember( nPlayerID );
    OperateMemberOffer( pMember, uchType, nValue );
}

template< class T >
void GuildInfo< T >::OperateMemberOffer( GuildMember* pMember, unsigned char uchType, unsigned int nValue  )
{
    if ( pMember == NULL )
    { return; }

    switch ( uchType )
    {
    case GuildDefine::OperateSet:
        break;
    case GuildDefine::OperateAdd:
        nValue += pMember->GetOffer();
        break;
    case GuildDefine::OperateSub:
        {
            if ( nValue > pMember->GetOffer() )
            { nValue = pMember->GetOffer(); }

            nValue = pMember->GetOffer() - nValue;
        }
        break;
    default:
        return;
    }

    ProcessMemberDataUpdate( pMember, GuildDefine::UpdateMemberOffer, nValue );
}

template< class T >
void GuildInfo< T >::OperateMemberActivity( unsigned int nPlayerID, unsigned char uchType, unsigned int nValue  )
{
    GuildMember* pMember = GetMember( nPlayerID );
    if ( pMember == NULL )
    { return; }

    switch ( uchType )
    {
    case GuildDefine::OperateSet:
        break;
    case GuildDefine::OperateAdd:
        nValue += pMember->GetActivity();
        break;
    case GuildDefine::OperateSub:
        {
            if ( nValue > pMember->GetActivity() )
            { nValue = pMember->GetActivity(); }

            nValue = pMember->GetActivity() - nValue;
        }
        break;
    default:
        return;
    }

    ProcessMemberDataUpdate( pMember, GuildDefine::UpdateMemberActivity, nValue );
}

template< class T >
unsigned int GuildInfo< T >::GetGuildStrength()
{
    const GuildConfig::LevelSetting* pSetting = theGuildConfig.GetLevelSetting( GetLevel() );
    if ( pSetting == NULL || pSetting->GetMaxCount() == 0 )
    { return 0; }

    //������������ȼ���/������������*��0+���ȼ�*ϵ����
    unsigned int nTotalLevel = 0;
    for ( MemberMapIter iter = m_mapMember.begin(); iter != m_mapMember.end(); ++iter )
    {
        nTotalLevel += iter->second.GetLevel();
    }

    const GuildConfig::StrengthSetting& xSetting = theGuildConfig.GetStrengthSetting();
    float fStrength = ( static_cast< float >( nTotalLevel ) / pSetting->GetMaxCount() ) * ( xSetting.GetBaseModulus() + static_cast< float >( GetLevel() ) * xSetting.GetExtendModulus() );

    return static_cast< unsigned int >( fStrength );
}

template< class T >
inline unsigned int GuildInfo< T >::SetFormatGuildVar( unsigned short nIndex, short nValue )
{
    unsigned int nFormatValue = nValue;
    nFormatValue <<= 16;
    nFormatValue += nIndex;

    return nFormatValue;
}

// ��������еļ������������ͱ���ֵ
template< class T >
inline void GuildInfo< T >::GetFormatGuildVar( unsigned int nValue, unsigned short &nIndex, short &nVar )
{
    nIndex = nValue & 0xFFFF;
    nVar = nValue >> 16;
}

template< class T >
inline GuildDelateInfo& GuildInfo< T >::GetDelateInfo()
{
    return m_xGuildDelate;
}

template< class T >
inline void GuildInfo< T >::StartDonateTimer()
{
    m_xDonateTimer.StartTimer( HQ_TimeGetTime(), GuildDefine::DonateKeepTime );
}

template< class T >
inline void GuildInfo< T >::StopDonateTimer()
{
    m_xDonateTimer.StopTimer();
}

template< class T >
inline bool GuildInfo< T >::CheckDonateTimer()
{
    return m_xDonateTimer.IsStart();
}

template< class T >
void GuildInfo< T >::SetDonateMoney( unsigned int nValue )
{
    m_nDonateMoney = nValue;
}

template< class T >
unsigned int GuildInfo< T >::GetDonateMoney() const
{
    return m_nDonateMoney;
}

template< class T >
void GuildInfo< T >::ProcessQuestRelease( unsigned int nQuestType, __int64 n64Time )
{
    SetReleaseQuest( nQuestType );
    SetReleaseTime( n64Time );

    SendQuestReleaseStatusMessage();
}

template< class T >
void GuildInfo< T >::ProcessClearMemberActivity()
{
    for ( MemberMapIter iter = m_mapMember.begin(); iter != m_mapMember.end(); ++iter )
    {
        iter->second.SetLastActivity( iter->second.GetActivity() ); // �����ܵķ�������
        iter->second.SetActivity( 0 );  // �������
    }

    SendClearMemberActivityMessage();
}

template< class T >
bool GuildInfo<T>::CanChangeAim() const
{
	return ( m_nChangeAimCD == 0 || TimeEx::IsPassCurrentTime( m_nChangeAimCD, theGuildConfig.GetChangeAimSetting().GetChangeAimCD() * 1000 ) );
}

template< class T >
void GuildInfo<T>::SetChangeAimCD( __int64 nTime )
{
	m_nChangeAimCD = nTime;
}

template< class T >
__int64 GuildInfo<T>::GetChangeAimCD()
{
	return m_nChangeAimCD;
}

////////////////////////////////////////////////////////////////////////////

class GamePlayer;
typedef GuildInfo< GamePlayer > GameGuild;

class ClientPeer;
typedef GuildInfo< ClientPeer > CenterGuild;
////////////////////////////////////////////////////////////////////////////
#endif