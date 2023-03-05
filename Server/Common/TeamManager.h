#ifndef __TEAMMANAGER_H__
#define __TEAMMANAGER_H__

/************************************************************************
                ����ģ��
                �þ�������CenterServer CenterTeamManager.cpp
                �߼���GameServer GameTeamManager.cpp

                MaintenanceMan Mail: lori227@live.cn
************************************************************************/
#include "Memory_pool.h"
#include <string>
#include <list>
#include <map>
#include <vector>
#include "RelationConfig.h"
namespace TeamDefine
{
    enum ETeamConstDefine
    {
        ErrorID           = 0,			// �����ID
        TeamUpdateTime    = 2000,       // 2�����һ�ζ�����Ϣ
        MaxTimeOut        = 300000,     // ���黺�汣��5����
        NoneSessionID     = 0,          // û�ж���ID
        InitSessionID     = 10000,      // �������ʼSessionID
        EndSessionID      = 10000000,   // ����Ľ���SeesionID
                                              
        // ɾ������Ľ��             
        DoNothing         = 0,          // ɶ������ 
        ChangeHeader      = 1,          // �����ӳ�
        DeleteTeam        = 2,          // ɾ������
                                      
        // ������²���               
        NotSendToGame     = 0,          // �����͸�GameServer
        SendToAllGame     = 1,          // ���͸�����GameServer
        SendToSomeGame    = 2,          // ���͸�ָ����ĳЩGameServer
        NotSendToCenter   = 0,          // �����͸�CenterServer��ת
        SendToCenter      = 1,          // ���͸�CenterServer��ת
        NotSendToClient   = 0,
        SendToClient      = 1,

        // ����Ĵ����, ����Ϣ�ﶨ�����һ���� ���Կ�������Ƚ���
        CanJoinTeam       = 0,          // �ܼ������
        AlreadyInTeam     = 0,          // �Ѿ��ڶ�����
        TeamFull          = 3,          // �����Ѿ�����
        JoinSuccess       = 9,          // �������ɹ�
        NotTeamHeader     = 8,          // �Լ����Ƕӳ�
        InMyBlackList     = 16,         // ���Լ��������� 
        InTargetBlackList = 13,         // �ڶԷ��������� 


        // С��buff����
        Buffer_Team       = 0,          // �������鸽�ӵ�Buffer
        Buffer_Friend,                  // ���Ѷ�  ����Buffer
		Buffer_Guild,					// ����    ����buffer
        Buffer_Max,        

        // С�Ӽ����жϽ��
        SkillCanUse		  = 0,			// С�Ӽ��ܿ�ʹ��
        SkillCanNotUse,					// С�Ӽ��ܲ���ʹ��
        SkillCoolDown,					// С�Ӽ�������CD
    };

    // �����������������ļ�¼��Ϣ
    struct TeamInvite
    {
        enum EConstDefine
        {
            ECD_Invite = 0,          // ����
            ECD_Request = 1,         // ����

            ECD_TimeOut = 60000,     // ��ʱʱ��
            ECD_NameLength = 41,
        };

        char szAckName[ECD_NameLength];       // ������������
        unsigned int dwReqID;                 // �����ߵ�id
        char szReqName[ECD_NameLength];       // ����������
        int nHp;                              // �������ʱ��HP
        int nMp;                              // �������ʱ��MP 
        int nHpMax;                           // �������ʱ�����HP
        int nMpMax;                           // �������ʱ�����MP
        short stLevel;                        // �������ʱ�ĵȼ�
        unsigned char chProfession;           // ְҵ 
        unsigned char chSex;                  // �Ա�
        int nFaceId;                          // Ԥ��������Id
        int nHairId;                          // ͷ��ID
        int nHeadPicId;                       // ͷ��ID

        unsigned char AssignMode;			  // �������ģʽ
        unsigned char AssignItemLevel;        // ������Ʒ�ķ���ȼ�

        unsigned int dwTimeOut;               // ����ʱ
        unsigned char chInviteType;           // ��������
    };
}

// ���������Ա��Ϣ
class BaseTeamMember
{
public:
	BaseTeamMember() : dwID( TeamDefine::ErrorID ), dwTimeOut( 0 ), stManipleID( 0 ), bManipleHeader( false )
    {
        strName.clear();
		nTeamFollowMemberID = 0;
    }

    virtual ~BaseTeamMember(){ strName.clear(); }

    BaseTeamMember( const BaseTeamMember& xMember )
    {
        *this = xMember;
    }

    BaseTeamMember& operator = ( const BaseTeamMember& xMember )
    {
        if ( this != &xMember )
        {
            strName        = xMember.GetName();
            dwID           = xMember.GetID();
            dwTimeOut      = xMember.GetTimeOut();
            stManipleID    = xMember.GetManipleID();
            bManipleHeader = xMember.GetManipleHeader();
        }

        return *this;
    }

    bool operator == ( unsigned int nValue ) { return dwID == nValue; }
    bool operator == ( const char* pszName ) { return strName == pszName; }

    bool IsErrorMember() { return ( dwID == TeamDefine::ErrorID || strName.empty() ); }     // �ж��Ƿ���Ч�Ķ����Ա

    void SetName( const char* pszName )    { if ( *pszName != NULL ) { strName = pszName; } }
    void SetID( unsigned int nValue )      { dwID = nValue;			  }
    void SetTimeOut( unsigned int nValue ) { dwTimeOut = nValue;	  }
    void SetManipleID( short stValue )     { stManipleID = stValue;	  }
    void SetManipleHeader( bool bValue )   { bManipleHeader = bValue; }

    const char*		   GetName() const           { return strName.c_str(); }
    const unsigned int GetID() const			 { return dwID;			   }
    const unsigned int GetTimeOut() const		 { return dwTimeOut;	   }
    const short		   GetManipleID() const      { return stManipleID;	   }
    const bool		   GetManipleHeader() const  { return bManipleHeader;  }

	unsigned int GetTeamFollowMemberID() const						{ return nTeamFollowMemberID; }
	void		 SetTeamFollowMemberID( unsigned int nMemberID )	{ nTeamFollowMemberID = nMemberID; }
private:
    std::string strName;        // ��Ա����
    unsigned int dwID;          // ��ԱID
    unsigned int dwTimeOut;     // �쳣���߳�ʱʱ��

    short stManipleID;          // С�ӵ�ID( �Ժ�����汾 )
    bool bManipleHeader;        // �Ƿ�С�Ӷӳ�

	unsigned int nTeamFollowMemberID;	// ���������ѵ�DBID
};

// CenterServer�ϵĶ����Ա��Ϣ
class CenterTeamMember : public BaseTeamMember
{
public:
    CenterTeamMember() : BaseTeamMember()
    {

    }

    CenterTeamMember( const CenterTeamMember& xMember )
    {
        *this = xMember;
    }

    CenterTeamMember& operator = ( const CenterTeamMember& xMember )
    {
        if ( this != &xMember )
        {
            BaseTeamMember::operator = ( xMember );
        }
       
        return *this;
    }

    ~CenterTeamMember() {}
};

// GameServer�ϵĶ����Ա��Ϣ
class GameTeamMember : public BaseTeamMember
{
public:
    GameTeamMember() : BaseTeamMember(), nHp( 0 ), nMp( 0 ), nHpMax( 0 ), nMpMax( 0 ), 
		stLevel( 1 ), stSex( 0 ), nFaceId( 0 ), nHairId( 0 ), chProfession( 0 ) {}
    ~GameTeamMember() {}

    GameTeamMember( const GameTeamMember& xMember )
    {
        *this = xMember;
    }

    GameTeamMember& operator = ( const GameTeamMember& xMember )
    {
        if ( this != &xMember )
        {
            BaseTeamMember::operator = ( xMember );

            nHp          = xMember.GetHP();
            nMp          = xMember.GetMP();
            nHpMax       = xMember.GetHPMax();
            nMpMax       = xMember.GetMPMax();
            stLevel      = xMember.GetLevel();
            stSex        = xMember.GetSex();
            chProfession = xMember.GetProfession();
            nFaceId      = xMember.GetFaceID();
            nHairId      = xMember.GetHairID();
            nHeadPicId   = xMember.GetHeadPicID();
        }

        return *this;
    }

    void SetHP( int nValue )                    { nHp = nValue; }
    void SetHPMax( int nValue )                 { nHpMax = nValue; }
    void SetMP( int nValue )                    { nMp = nValue; }
    void SetMPMax( int nValue )                 { nMpMax = nValue; }
    void SetLevel( short stValue )              { stLevel = stValue; }
    void SetProfession( unsigned char chValue ) { chProfession = chValue; }
    void SetFaceID( int nValue )                { nFaceId = nValue; }
    void SetHairID( int nValue )                { nHairId = nValue; }
    void SetHeadPicID( int nValue )             { nHeadPicId = nValue; }
    void SetSex( short stValue )                { stSex = stValue; }

    void AddTeamBuffer( unsigned char uchType, const TeamBuffer& xBuffer )
    {
        if ( uchType >= TeamDefine::Buffer_Max )
        { return; }

        xTeamBuffer[ uchType ] = xBuffer;
    }

    const int    GetHP() const                 { return nHp; }
    const int    GetHPMax() const              { return nHpMax; }
    const int    GetMP() const                 { return nMp; }
    const int    GetMPMax() const              { return nMpMax; }
    const short  GetLevel() const              { return stLevel; }
    const unsigned char  GetProfession() const { return chProfession; }
    const int    GetFaceID() const             { return nFaceId; }
    const int    GetHairID() const             { return nHairId; }
    const int    GetHeadPicID() const          { return nHeadPicId; }
    const short  GetSex() const                { return stSex; }
    
    TeamBuffer* GetTeamBuffer( unsigned char uchType )
    {
        if ( uchType >= TeamDefine::Buffer_Max )
        { return NULL; }
    
        return &( xTeamBuffer[uchType] );
    }

private:
    int nHp;                           // ���HP
    int nMp;                           // ���MP 
    int nHpMax;                        // ������HP
    int nMpMax;                        // ������MP
    short stLevel;                     // ��ҵȼ�
    short stSex;                       // �Ա� 
    int nFaceId;                       // ����ID
    int nHairId;                       // ͷ��ID
    int nHeadPicId;                    // ͷ��ID
    unsigned char chProfession;        // ְҵ 

    TeamBuffer xTeamBuffer[ TeamDefine::Buffer_Max ];       // ���ӵĶ���Buffer
};

struct Msg;
class GameStage;
template< class T > class TeamManager;

typedef std::pair< unsigned long, unsigned long > CDTIME;

template< class T, class U > // T:�����Ա���� U:��Ա��������
class Team : public Common::TObject_pool< Team< T, U > >
{
protected:
    typedef std::list< T > MemberList;
    typedef typename MemberList::iterator MemberListIter;

    typedef std::map< short, unsigned short > ManipleCountMap;  // ����С��������map
    typedef ManipleCountMap::iterator ManipleCountMapIter;
    
    typedef T TeamMemberType;

public:
    Team() : m_bCrops( false ), m_dwTeamSessionID( 0 ), m_dwTeamHeaderID( TeamDefine::ErrorID ), m_nModeType( 0 ),
		m_chAssignItemLevel( 2 ), m_stAssignIndex( 0 ), m_dwLastUpdateFrienlyTime( HQ_TimeGetTime() ), 
		m_dwStartCoolDownTime( 0 ), m_dwCoolDownTime( 0 ),m_IsTransnationalTeam(false)
    {
        m_listTeamMember.clear();

        for ( int i = 0; i < TeamMaxManipleCount; ++i )       // 4��С����
        {
            m_mapManipleCount.insert( std::make_pair( i, 0 ) );
        }
    }

    ~Team() 
    { 
        m_dwTeamSessionID = TeamDefine::NoneSessionID;
        m_dwTeamHeaderID = TeamDefine::ErrorID;
        m_stAssignIndex = 0;
        m_listTeamMember.clear(); 
    }

    static Team* CreateTeam() { return CNewWithDebug< Team< T, U > >::Alloc( 1, "Team::CreateTeam�д���Teamʵ��" ); }
    virtual void Release() { CNewWithDebug< Team< T,U > >::Free( this ); }

    

    void		SetTeamCrops( bool bCrops )							{ m_bCrops = bCrops; }       // ���ö����Ƿ�Ϊ��
	void		SetTeamAssignModeType( unsigned char nModeType )	{ m_nModeType = nModeType; } // ���ö������ģʽ
	void		SetTeamAssignItemLevel( unsigned char chItemLevel ) { m_chAssignItemLevel = chItemLevel; }// ���ö�����Ʒ����ȼ�
    void 		SetID( unsigned int dwSessionID )					{ m_dwTeamSessionID = dwSessionID; }  // ���ö���
	void 		SetTeamHeaderID( unsigned int dwID )				{ m_dwTeamHeaderID = dwID; }          // ���öӳ�ID
	void		SetStartCoolDownTime( unsigned int dwTime )			{ m_dwStartCoolDownTime = dwTime; }
	void		SetCoolDownTime( unsigned int dwTime )				{ m_dwCoolDownTime = dwTime; }
	void		SetLastTeamFollowMember( unsigned int nMemberID )	{ m_dwLastTeamFollowMember = nMemberID; }
	void		SetIsTransnationalTeam(bool Result)					{ m_IsTransnationalTeam = Result;}

	bool				GetTeamCrops()					{ return m_bCrops; }           
    const unsigned char GetTeamAssignModeType() const	{ return m_nModeType; }			
    const unsigned char GetTeamAssignItemLevel() const	{ return m_chAssignItemLevel; }
    const unsigned int  GetID() const					{ return m_dwTeamSessionID; }
    const unsigned int  GetTeamHeaderID() const			{ return m_dwTeamHeaderID; }
	unsigned int		GetLastTeamFollowMember()		{ return m_dwLastTeamFollowMember; }
	bool				GetIsTransnationalTeam()		{ return m_IsTransnationalTeam;}

	// ��
	int		AddTeamMember( T& xMember, TeamManager< Team >& xTeamManager, TeamDefine::TeamInvite* pRecord );// ��Ӷ�Ա
	// ɾ
	int		RemoveTeamMember( unsigned int dwMemberID, TeamManager< Team >& xTeamManager );					// ɾ����Ա
	void	RemoveTeamMemberAndReleaseTeam( unsigned int dwMemeberID, TeamManager< Team >& xTeamManager );	// ɾ����Ա,��������ɢ,�ͷ���Դ
	void	DisbandTeam( TeamManager< Team >& xTeamManager );												// ��ɢ����

	bool	ClearTeamBuffer( U* pTeamMember, unsigned char uchBufferType, unsigned char uchSendMessage = TeamDefine::SendToClient );
	
	// ��
	void	ProcessManipleInfo( T& xMember );																// ����С����Ϣ
	void	UpdateTeamTransnationalStates(bool IsAdd,unsigned int ID);										// ���¶���״̬(�����Ա���Ҵ�����)
	bool	UpgradeTeamHeader( unsigned int dwMemberID );													// �����ӳ�
	int		RunTeamUpdate( unsigned char chOperate );														// ִ��Team Update
	void	MemberOutLine( unsigned int dwMemberID );														// ���ö�Ա����
	void	MemberOnLine( unsigned int dwMemberID );														// ��Ա����, ���״̬
	bool	UpdateTeamFriendly( U* pMemberPlayer, unsigned int nFriendly );									// ���º��Ѷ�
	void	UpdateTeamBuffer( unsigned int dwExceptMemberID = TeamDefine::ErrorID , bool bLeaveTeam = false );// ���¶���Buffer  dwExceptMemberIDΪ�����в�������˵ĺ��ѹ�ϵ( ��ɾ������ʱ��ʹ�� )
	void	UpdateTeamBuffer( T* pTeamMember, unsigned char uchCount = TeamMaxManipleMember, unsigned int dwExceptMemberID = TeamDefine::ErrorID );
	CDTIME		StartTeamSkillCoolDown( unsigned short ustSkillID, unsigned char uchLevel, unsigned int dwCoolDownTime );
	// ��
	// ��ö�������
	unsigned short 	TeamMemberCount() { return static_cast< unsigned short >( m_listTeamMember.size() ); }	
	unsigned int   	GetMemberIDByIndex( short nIndex );				  							// ͨ�������Ҷ�ԱID
	T*			   	GetTeamMemberByID( unsigned int dwMemberID );	  							// ͨ��ID�Ҷ�Ա
	T*			   	GetTeamMemberByIndex( short nIndex );             							// ͨ�������Ҷ�Ա
	U*				GetMemberPlayer( unsigned int dwMemberID, bool bIncludeNotInStage = false );// ��ö�Ա�Ĺ����Ľ�ɫ����
	unsigned char  	GetHeaderFriendCount( unsigned int dwExceptMemberID = TeamDefine::ErrorID );// �õ��ӳ��ڶ���������ѵ�����
	bool 			IsTeamHeader( unsigned int dwMemberID ) { return ( dwMemberID == m_dwTeamHeaderID ); }  // �Ƿ��Ƕӳ�
	bool 			IsInTeam( unsigned int dwMemberID );            							// �Ƿ��ڶ�����
	bool 			IsTeamFull();                                   							// �ж϶����Ƿ�����
	bool 			IsAllTeamMemberGreaterLevel( int nLevel );      							// �Ƿ�������Ҷ����ڸõȼ�
	int  			IsCanInviteJoinInTeam( unsigned int dwHeaderID, unsigned int dwNewAddID );  // �ж��ܷ�������
	int  			IsCanRequestJoinInTeam( unsigned int dwNewAddID );							// �ж��ܷ����
	unsigned int 	GetCurrentAssignTeamMemberID();												// ��õ�ǰ������Ʒ�Ķ�Ա��ID
	unsigned int 	GetTeamMemberNotHaveQuest( int nQuestID );									// �ҵ������е�һ��û�и���������
	unsigned char   CheckTeamSkillCanUse( U* pPlayer, unsigned short ustSkillID, unsigned char uchSkillLevel );
	// ����ڷ�Χ�ڵ����ж�ԱID
	void			GetTeamMemberInMapArea( unsigned int nMapID, float fX, float fY, std::vector< unsigned int >& vecTeamMemberID );   
	unsigned int	GetTeamMemberCountInMap( unsigned int nMapID, float fX, float fY );			// ĳ����ͼ�ڵĶ�Ա����
	// ��ö����ܵȼ���������С�ȼ���
	unsigned int	GetTeamMemberLevelDistance( unsigned int nMapID, float fX, float fY, int& nMinLevel, int& nMaxLevel ); 
	float			GetTeamExpPercent( unsigned int nTeamCount, bool bIsEcType );							// ��ö��龭��ٷֱ�
	

    // �߼�����
    void SendMessageToTeamClient( Msg* pMessage, unsigned int nExceptID, unsigned char chOperate ); // ������Ϣ���������г�Ա
    bool CallAllTeamPlayerFlyToMapReq( unsigned int nMapID, float fX, float fY, float fDir = 0.0f );
    //bool TeamChangeStage( GameStage* pGameStage, int nTileX, int nTileY, float dir );

    // �¼ӵ�ʱ�亯�� �ű����
    unsigned long	IsTeamTimeVarPassOneDay( int nVarID );
    void			RecordNowTeamTimeVar( int nVarID );
    void			ClearTeamTimeVar( int nVarID, int nClearVarID );
	void			ClearTeamExpiredVar( int nVarId, int keyHour, int keyMinute, int minDuration, int nClearVarId );//�ű����
	bool			RecordTeamTime( int nVarId );																	//�ű����
    unsigned long   IsTeamExpired( int nVarId, int keyHour, int keyMinute, int minDuration );	// �ű����

protected:
    void UpdateTeamMemberInfo( Msg* pMessage );
    bool ProcessUpgradeTeamHeader( T* pMember );				// ���Ͷӳ��ı���Ϣ
    void ProcessAddTeamMember( T& xMember, TeamDefine::TeamInvite* pRecord ); // ������Ӷ�Ա��Ϣ
    void ProcessRemoveTeamMember( unsigned int dwMemberID );    // ����ɾ����Ա��Ϣ
    void MemberOutLine( T* pTeamMember );                       // ���ö�Ա����
    void MemberOnLine( T* pTeamMember );                        // �ս�����Ϸʱ, ���¶�Ա��Ϣ�����

    void AddManipleCount( short stManipleID );              // ���С������
    void SubManipleCount( short stManipleID );              // ����С������

    void UpdateTeamFriendly();                              // ���º��Ѷ�
    void ClearTeamBuffer( U* pMemberPlayer );               // ���С��Buffer
                             
    bool UpdateTeamBuffer( T* pTeamMember, U* pPlayer, unsigned char uchType, const TeamBuffer* pTeamBuffer );
    void ChangeTeamHeaderToOnLineMember();                  // �ӳ����ߺ���һ�����ߵĵ��ӳ�

    unsigned int GetMemberMinFriendly();					// ���ݶӳ������С���Ѷ�

private:
    Team( const Team< T, U >& );
    Team< T, U >& operator = ( const Team< T, U >& );

private:
    MemberList m_listTeamMember;            // �����Ա�б�
	
	map<unsigned int,unsigned char>			m_MapCountry;//��¼��Ա�Ĺ��� ����������õ�	

    unsigned int m_dwTeamSessionID;         // �����SessionID;
    unsigned int m_dwTeamHeaderID;          // �ӳ�ID
    bool		 m_bCrops;                  // �Ƿ�����
    unsigned char m_nModeType;              // ����ģʽ
    unsigned char m_chAssignItemLevel;      // ��Ʒ����ĵȼ�
    ManipleCountMap m_mapManipleCount;      // 4��С��,ÿ��С�ӵ�����

    unsigned short m_stAssignIndex;         // �ôε�����Ʒ���䵽ĳ����Ա���� ( ��������� )
    unsigned int m_dwLastUpdateFrienlyTime; // �ϴθ��º��Ѷ�ʱ��

    unsigned int m_dwStartCoolDownTime;     // ���鼼�ܿ�ʼCoolDownʱ��
    unsigned int m_dwCoolDownTime;          // ���鼼��CDʱ��

	unsigned int m_dwLastTeamFollowMember;	// ��ǰ�����������һ�����

	bool m_IsTransnationalTeam;//�Ƿ�Ϊ������� Ĭ��Ϊfalse ����������������Ϊͬһ���ҵ� ����˵��û���� ��Ϊfalse  �����Ϊtrue
};

template< class T >
class TeamManager
{
protected:
    typedef std::map< unsigned int, unsigned int > MapID;
    typedef MapID::iterator MapIDIter;

    typedef std::map< unsigned int, TeamDefine::TeamInvite > InviteInfoMap;
    typedef InviteInfoMap::iterator InviteInfoMapIter;
    typedef std::map< std::string, InviteInfoMap > InviteRecordMap;
    typedef InviteRecordMap::iterator InviteRecordMapIter;

    typedef typename std::map< unsigned int, T* > TeamMap;
    typedef typename TeamMap::iterator TeamMapIter;
public:
    ~TeamManager()
    {
        for ( TeamMapIter iter = m_mapTeam.begin(); iter != m_mapTeam.end(); ++iter )
        {
            if ( iter->second != NULL )
            {
                iter->second->Release();
            }
        }

        m_mapTeam.clear();
    }

    static TeamManager< T >& Instance()
    {
        static TeamManager< T > s_TeamManger;
        return s_TeamManger;
    }

    unsigned int CreateTeamSessionID();                     // �����µĶ���SessionID
    T*	 GetTeam( unsigned int dwTeamSessionID );           // ���Ҷ���
    T*   CreateTeam( unsigned int dwTeamSessionID, unsigned char chAssignMode, unsigned char chAssignItemLevel );     // ��������
    T*   GetTeamByMemberID( unsigned int dwMemberID );      // ͨ����ԱID���Ҷ���
    bool ReleaseTeam( unsigned int dwSessionID );           // ɾ��һ������
    void RemoveMemberByID( unsigned int dwMemberID );       // ɾ����Ա
    void TeamMemberOutLine( unsigned int dwMemberID );      // ��������ʱ��
    void TeamMemberOnLine( unsigned int dwMemberID );       // ����������
    void SendOnLineMessage( unsigned int dwMemberID );      // ���¶�Ա��Ϣ,����ҵ�һ�ν�����Ϸ����
    void RunTeamManagerUpdate( unsigned int dwCurrentTime, unsigned char chOperate );    // ִ��Update

    ////////////////////////////////////////////////////////////////////////////
    //��ɫid �� teamsessionid �Ĺ���
    bool AddMemberSessionID( unsigned int dwMemberID, unsigned int dwTeamSessionID );     // ������dbid��session�Ĺ���
    bool RemoveMemberSessionID( unsigned int dwMemberID );                                // ɾ������
    unsigned int GetMemberSessionID( unsigned int dwMemberID );                           // ���ҹ���
    ////////////////////////////////////////////////////////////////////////////////
    void AddInviteRecord( TeamDefine::TeamInvite& xInvite );                                 // ���������Ϣ
    void RemoveInviteRecord( std::string strAckName, unsigned int dwReqID );                 // ɾ��������Ϣ
    TeamDefine::TeamInvite* GetInviteRecord( std::string strAckName, unsigned int dwReqID ); // ����������Ϣ
    //////////////////////////////////////////////////////////////////////////////////////
    void UpdateTeamBuffer( unsigned int dwReqPlayerID, unsigned int dwAckPlayerID, bool bAllTeamUpdate, bool bAddRelation );

protected:
    TeamManager() : m_dwNextTeamUpdateTime( 0 ), m_dwCreateSessionID( TeamDefine::InitSessionID )
    {
        m_mapTeam.clear();
        m_mapMemberSessionID.clear();      
        m_mapInviteRecord.clear();
    }

    bool AddTeam( T* pTeam );                                 // ���һ������
    void SendCreateTeamMessage( T* pTeam );                   // ���ʹ���������Ϣ
    void RunInviteRecordUpdate( unsigned int dwCurrentTime ); // �������������Ϣ
private:
    TeamManager( const TeamManager< T >& );
    TeamManager< T >& operator = ( const TeamManager< T >& );

private:
    TeamMap m_mapTeam;                     // �������Ĳ���
    MapID m_mapMemberSessionID;            // ���id ���� TeamSessionID
    unsigned int m_dwNextTeamUpdateTime;   // �ϴθ��¶���ʱ��
    unsigned int m_dwCreateSessionID;      // �����������TeamSessionID
    InviteRecordMap m_mapInviteRecord;     // ��ӵ������¼
};

// ��ID�Ҷ�Ա��Ϣ
template< class T, class U >
T* Team< T, U >::GetTeamMemberByID( unsigned int dwMemberID )
{
    MemberListIter iter = std::find( m_listTeamMember.begin(), m_listTeamMember.end(), dwMemberID );
    if ( iter == m_listTeamMember.end() )
    { return NULL; }

    return &( *iter );
}

// ͨ�������Ҷ�Ա��Ϣ
template< class T, class U >
T* Team< T, U >::GetTeamMemberByIndex( short nIndex )           
{
    if ( nIndex < 0 || nIndex >= TeamMemberCount() )
    { return NULL; }

    MemberListIter iter = m_listTeamMember.begin();
    advance( iter, nIndex );

    return &( *iter );
}

// �������õ���ԱID
template< class T, class U >
unsigned int Team< T, U >::GetMemberIDByIndex( short nIndex )
{
    T* pTeamMember = GetTeamMemberByIndex( nIndex );
    if ( pTeamMember == NULL )
    { return TeamDefine::ErrorID; }

    return pTeamMember->GetID();
}

// �ж϶����Ƿ�����
template< class T, class U >
bool Team< T, U >::IsTeamFull()             
{
    int nMaxTeamCount = TeamMaxManipleMember;
    if ( m_bCrops )
    { nMaxTeamCount = TeamMaxMember; }

    return TeamMemberCount() >= nMaxTeamCount;
}

// �Ƿ��ڶ�����
template< class T, class U >
bool Team< T, U >::IsInTeam( unsigned int dwMemberID )            
{
    T* pMember = GetTeamMemberByID( dwMemberID );
    return ( pMember != NULL );
}
// ��Ӷ�Ա
template< class T, class U >
int Team< T, U >::AddTeamMember( T& xMember, TeamManager< Team >& xTeamManager, TeamDefine::TeamInvite* pRecord )
{
    if ( IsInTeam( xMember.GetID() ) )
    { return TeamDefine::AlreadyInTeam; }

    if ( IsTeamFull() )
    { return TeamDefine::TeamFull; }

    // ����С����Ϣ xMember �����ĸ�С�� �Ƿ���С�ӳ�
    ProcessManipleInfo( xMember );

    //�������� ����С�ӵ���������
    AddManipleCount( xMember.GetManipleID() );
    m_listTeamMember.push_back( xMember );  // ��ӵ�����

    // ������� ��Աid <-> ����id
    xTeamManager.AddMemberSessionID( xMember.GetID(), GetID() );      //��ӹ���

    ProcessAddTeamMember( xMember, pRecord );        // ������Ϣ

	UpdateTeamTransnationalStates(true,xMember.GetID() );//���¶����״̬
    return TeamDefine::JoinSuccess;
}

// ɾ����Ա
template< class T, class U >
int Team< T, U >::RemoveTeamMember( unsigned int dwMemberID, TeamManager< Team >& xTeamManager )
{
    int nResult = TeamDefine::DoNothing;
    if ( !IsInTeam( dwMemberID ) )  //������������е�
    { return nResult; }       

    ProcessRemoveTeamMember( dwMemberID );  // ������Ϣ

    if ( TeamMemberCount() <= 1 )
    {
        for ( MemberListIter iter = m_listTeamMember.begin(); iter != m_listTeamMember.end(); ++iter )
        {
            xTeamManager.RemoveMemberSessionID( iter->GetID() );            //ɾ���������
        }

        m_listTeamMember.clear();   
        m_mapManipleCount.clear();
        nResult = TeamDefine::DeleteTeam;
    }
    else 
    {
        // ɾ���ö�Ա
        MemberListIter iter = std::find( m_listTeamMember.begin(), m_listTeamMember.end(), dwMemberID );
        if ( iter != m_listTeamMember.end() )
        { 
            SubManipleCount( iter->GetManipleID() );        // ����С������
            m_listTeamMember.erase( iter );
        }

        xTeamManager.RemoveMemberSessionID( dwMemberID );

        if ( IsTeamHeader( dwMemberID ) )      // ���ԭ���Ƕӳ�, �ҵ�һ���¶ӳ�
        {
            ChangeTeamHeaderToOnLineMember();
            nResult = TeamDefine::ChangeHeader;
        }

		UpdateTeamTransnationalStates(false,dwMemberID);
    }

    return nResult;
}

// ɾ����Ա���ͷŶ���
template< class T, class U >
void Team< T, U >::RemoveTeamMemberAndReleaseTeam( unsigned int dwMemeberID, TeamManager< Team >& xTeamManager )
{
    if ( RemoveTeamMember( dwMemeberID, xTeamManager ) == TeamDefine::DeleteTeam )
    {
        xTeamManager.ReleaseTeam( GetID() );
    }
}

// ��ɢ����
template< class T, class U >
void Team<T, U>::DisbandTeam( TeamManager< Team >& xTeamManager )
{
	for ( MemberListIter iter = m_listTeamMember.begin(); iter != m_listTeamMember.end(); ++iter )
	{
		xTeamManager.RemoveMemberSessionID( iter->GetID() );            //ɾ���������
	}

	m_listTeamMember.clear();   
	m_mapManipleCount.clear();

	xTeamManager.ReleaseTeam( GetID() );
}

// ��������ӳ�
template< class T, class U >
bool Team< T, U >::UpgradeTeamHeader( unsigned int dwMemberID )
{
    if ( IsTeamHeader( dwMemberID ) )
    { return false; }

    T* pTeamMember = GetTeamMemberByID( dwMemberID );
    if ( pTeamMember == NULL )
    { return false; }

    SetTeamHeaderID( dwMemberID );      // ���öӳ�ID
    pTeamMember->SetManipleHeader( true );

    return ProcessUpgradeTeamHeader( pTeamMember );
}

template< class T, class U >
void Team< T, U >::MemberOutLine( unsigned int dwMemberID )
{
    T* pTeamMember = GetTeamMemberByID( dwMemberID );
    if ( pTeamMember == NULL )
    { return; }

    MemberOutLine( pTeamMember );
}

template< class T, class U >
void Team< T, U >::MemberOnLine( unsigned int dwMemberID )
{
    T* pTeamMember = GetTeamMemberByID( dwMemberID );
    if ( pTeamMember == NULL )
    { return; }

    MemberOnLine( pTeamMember );
}

// ���С������
template< class T, class U >
void Team< T, U >::AddManipleCount( short stManipleID )
{
    ManipleCountMapIter iter = m_mapManipleCount.find( stManipleID );
    if ( iter == m_mapManipleCount.end() )
    { return; }

    ++iter->second;
    if ( iter->second > TeamMaxManipleMember )
    { iter->second = TeamMaxManipleMember; }
}

// ����С������
template< class T, class U >
void Team< T, U >::SubManipleCount( short stManipleID )
{
    ManipleCountMapIter iter = m_mapManipleCount.find( stManipleID );
    if ( iter == m_mapManipleCount.end() )
    { return; }

    --iter->second;
    if ( iter->second < 0 )
    { iter->second = 0; }
}

// ��õ�ǰ����Ķ�ԱID
template< class T, class U >
unsigned int Team< T, U >::GetCurrentAssignTeamMemberID()
{
    if ( m_stAssignIndex < 0 || m_stAssignIndex >= TeamMemberCount() )
    { m_stAssignIndex = 0; }

    return GetMemberIDByIndex( m_stAssignIndex++ );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���������SessionID
template< class T >
unsigned int TeamManager< T >::CreateTeamSessionID()
{
    if(  m_dwCreateSessionID > TeamDefine::EndSessionID || m_dwCreateSessionID < TeamDefine::InitSessionID )
    { m_dwCreateSessionID = TeamDefine::InitSessionID; }

    return m_dwCreateSessionID++;
}

template< class T >
T* TeamManager< T >::CreateTeam( unsigned int dwTeamSessionID, unsigned char chAssignMode, unsigned char chAssignItemLevel )
{
    if ( dwTeamSessionID == TeamDefine::NoneSessionID )
    { return NULL; }

    T* pTeam = T::CreateTeam();
    if( pTeam == NULL )    // ����ʧ��
    { return NULL; }

    pTeam->SetID( dwTeamSessionID );
    pTeam->SetTeamAssignModeType( chAssignMode );
    pTeam->SetTeamAssignItemLevel( chAssignItemLevel );

    if ( !AddTeam( pTeam ) )
    {
        pTeam->Release();
        return NULL;
    }

    SendCreateTeamMessage( pTeam );        // ���ʹ���������Ϣ
    return pTeam;
}

template< class T >
T* TeamManager< T >::GetTeamByMemberID( unsigned int dwMemberID )
{
    unsigned int dwTeamSessionID = GetMemberSessionID( dwMemberID );
    if ( dwTeamSessionID == TeamDefine::NoneSessionID )
    { return NULL; }

    T* pTeam = GetTeam( dwTeamSessionID );
    if ( pTeam == NULL || !pTeam->IsInTeam( dwMemberID ) )        // û�ж��� 
    {
        RemoveMemberSessionID( dwMemberID );
        return NULL;
    }

    return pTeam;
}

template< class T >
void TeamManager< T >::RemoveMemberByID( unsigned int dwMemberID )
{
    T* pTeam = GetTeamByMemberID( dwMemberID );
    if ( pTeam != NULL )
    {
        if ( pTeam->RemoveTeamMember( dwMemberID, *this ) == TeamDefine::DeleteTeam )
        {
            ReleaseTeam( pTeam->GetID() );
        }
    }
}

template< class T >
T* TeamManager< T >::GetTeam( unsigned int dwTeamSessionID )
{
    TeamMapIter iter = m_mapTeam.find( dwTeamSessionID );
    if ( iter == m_mapTeam.end() )
    { return NULL; }

    return iter->second;
}

template< class T >
bool TeamManager< T >::AddTeam( T* pTeam )
{
    if ( pTeam == NULL || pTeam->GetID() == TeamDefine::NoneSessionID )
    { return false; }

    TeamMapIter iter = m_mapTeam.find( pTeam->GetID() );
    if ( iter != m_mapTeam.end() )
    { return false; }

    return m_mapTeam.insert( std::make_pair( pTeam->GetID(), pTeam ) ).second;
}

template< class T >
bool TeamManager< T >::ReleaseTeam( unsigned int dwSessionID )
{
    TeamMapIter iter = m_mapTeam.find( dwSessionID );
    if ( iter == m_mapTeam.end() )
    { return false; }

    if ( iter->second != NULL )
    {
        iter->second->Release();
    }
    
    iter->second = NULL;
    m_mapTeam.erase( iter );
    return true;
}

template< class T >
bool TeamManager< T >::AddMemberSessionID( unsigned int dwMemberID, unsigned int dwTeamSessionID )
{
    if ( dwMemberID == TeamDefine::ErrorID || dwTeamSessionID == TeamDefine::NoneSessionID )
    { return false; }

    m_mapMemberSessionID[ dwMemberID ] = dwTeamSessionID;
    return true;
}

template< class T >
bool TeamManager< T >::RemoveMemberSessionID( unsigned int dwMemberID )
{
    MapIDIter iter = m_mapMemberSessionID.find( dwMemberID );
    if ( iter == m_mapMemberSessionID.end() )
    { return false; }

    m_mapMemberSessionID.erase( iter );
    return true;
}

template< class T >
unsigned int TeamManager< T >::GetMemberSessionID( unsigned int dwMemberID )
{
    MapIDIter iter = m_mapMemberSessionID.find( dwMemberID );
    if ( iter == m_mapMemberSessionID.end() )
    { return TeamDefine::NoneSessionID; }

    return iter->second;
}

template< class T >
void TeamManager< T >::TeamMemberOutLine( unsigned int dwMemberID )
{
    T* pTeam = GetTeamByMemberID( dwMemberID );
    if ( pTeam != NULL )
    {
        pTeam->MemberOutLine( dwMemberID );     
    }
}

template< class T >
void TeamManager< T >::TeamMemberOnLine( unsigned int dwMemberID )
{
    T* pTeam = GetTeamByMemberID( dwMemberID );
    if ( pTeam != NULL )
    {
        pTeam->MemberOnLine( dwMemberID );
    }
}

template< class T >
void TeamManager< T >::AddInviteRecord( TeamDefine::TeamInvite& xInvite )
{
    if ( xInvite.szAckName[0] == 0 || xInvite.dwReqID == TeamDefine::ErrorID )
    { return; }

    InviteRecordMapIter iter = m_mapInviteRecord.find( xInvite.szAckName );
    if ( iter == m_mapInviteRecord.end() )
    {
        InviteInfoMap mapInviteInfo;
        mapInviteInfo.insert( make_pair( xInvite.dwReqID, xInvite ) );

        m_mapInviteRecord.insert( make_pair( xInvite.szAckName, mapInviteInfo ) );
    }
    else
    {
        InviteInfoMapIter miter = iter->second.find( xInvite.dwReqID );
        if ( miter == iter->second.end() )
        {
            iter->second.insert( make_pair( xInvite.dwReqID, xInvite ) );
        }
        else
        {
            miter->second = xInvite;
        }
    }
}

template< class T >
void TeamManager< T >::RemoveInviteRecord( std::string strAckName, unsigned int dwReqID )
{
    if ( strAckName.empty() || dwReqID == TeamDefine::ErrorID )
    { return; }

    InviteRecordMapIter iter = m_mapInviteRecord.find( strAckName );
    if ( iter == m_mapInviteRecord.end() )
    { return; }

    InviteInfoMapIter miter = iter->second.find( dwReqID );
    if ( miter == iter->second.end() )
    { return; }

    iter->second.erase( miter );
    if ( iter->second.empty() )
    {
        m_mapInviteRecord.erase( iter );
    }
}

template< class T >
TeamDefine::TeamInvite* TeamManager< T >::GetInviteRecord( std::string strAckName, unsigned int dwReqID )
{
    if ( strAckName.empty() || dwReqID == TeamDefine::ErrorID )
    { return NULL; }

    InviteRecordMapIter iter = m_mapInviteRecord.find( strAckName );
    if ( iter == m_mapInviteRecord.end() )
    { return NULL; }

    InviteInfoMapIter miter = iter->second.find( dwReqID );
    if ( miter == iter->second.end() )
    { return NULL; }

    return &( miter->second );
}

template< class T >
void TeamManager< T >::RunTeamManagerUpdate( unsigned int dwCurrentTime, unsigned char chOperate )
{
    // ��鳬ʱ
    RunInviteRecordUpdate( dwCurrentTime );

    if ( !GameTime::IsPassCurrentTime( dwCurrentTime, m_dwNextTeamUpdateTime, TeamDefine::TeamUpdateTime ) )
    { return; }

    for( TeamMapIter iter = m_mapTeam.begin(); iter != m_mapTeam.end(); )
    {
        if ( iter->second == NULL )
        {
            iter = m_mapTeam.erase( iter );
            continue;
        }   

        if ( iter->second->RunTeamUpdate( chOperate ) == TeamDefine::DeleteTeam )
        {
            iter->second->Release();
            iter = m_mapTeam.erase( iter );
        }
        else
        {
            ++iter;
        }
    }

    m_dwNextTeamUpdateTime = dwCurrentTime;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////

class ClientPeer;
typedef Team< CenterTeamMember, ClientPeer > CenterTeam;
typedef TeamManager< CenterTeam > CenterTeamManager;
#define theCenterTeamManager CenterTeamManager::Instance()  // CenterServer TeamManager

class GamePlayer;
typedef Team< GameTeamMember, GamePlayer > GameTeam;
typedef TeamManager< GameTeam > GameTeamManager;
#define theGameTeamManager GameTeamManager::Instance()    // GameServer TeamManager

#endif