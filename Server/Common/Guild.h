#ifndef __GUILD_H__
#define __GUILD_H__
/************************************************************************
            帮派类属性定义
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

// 弹劾相关
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

    unsigned int m_nDelateMemberID;       // 发起弹劾的成员ID
    unsigned int m_nSendMemberCount;      // 总共发送的个数
    AgreeMemberSet m_setAgreeMember;      // 同意的成员
    GameTimerEx m_xDelateTimer;           // 弹劾定时器
};

template< class T >
class GuildInfo : public GuildDataToServer, INHERIT_POOL_PARAM( GuildInfo< T >, 50 )
{
public:
    GuildInfo();
    static GuildInfo* CreateGuild() { return CNewWithDebug< GuildInfo< T > >::Alloc( 1, "创建GuildInfo实例" ); }
    virtual void Release() { CNewWithDebug< GuildInfo< T > >::Free( this ); }

    // 添加成员
    bool AddMember( const GuildMember& xMember );    

    // 删除成员
    bool RemoveMember( unsigned int nPlayerID );   

    // 查找成员
    GuildMember* GetMember( unsigned int nPlayerID );     

    // 获得成员个数
    unsigned int MemberCount() const;       

    // 获得副帮主
    GuildMember* GetViceMaster();     

    // 获得某家族家族长 
    GuildMember* GetFamilyMaster( unsigned char uchFamilyID );  

    // 是否是帮主
    bool IsMaster( unsigned int nPlayerID ) const;            

    // 是否有某种权限
    bool HaveRight( unsigned int nPlayerID, unsigned int nRight );   

    // 判断职位大小
    bool CheckPosition( unsigned int nPlayerID, unsigned int nTargetID );  

    // 获得帮派成员列表
    int GetMemberList( GuildMember* pMember, int nCount );   

    // 处理成员加入
    void ProcessMemberJoinGuild( const GuildMember& xMember );    

    // 处理成员离开
    void ProcessMemberLeaveGuild( unsigned int nPlayerID );    

    // 处理帮派解散
    void ProcessDisbandGuild();                   

    // 成员上线
    void ProcessEnterWorld( unsigned int nPlayerID );     

    // 成员下线
    void ProcessExitWorld( unsigned int nPlayerID );     

    // 处理成员数据更新
    void ProcessMemberDataUpdate( unsigned int nPlayerID, unsigned char uchType, unsigned int nValue ); 
    void ProcessMemberDataUpdate( GuildMember* pMember, unsigned char uchType, unsigned int nValue ); 

    // 处理帮派数据更新
    void ProcessGuildDataUpdate( unsigned char uchType, __int64 nValue );    

    // 处理帮派公告改变
    void ProcessGuildNoticeChange( const char* szNotice );   

	void ProcessGuildNameChange(const char * Name);

	// 处理帮派宗旨改变
	void ProcessGuildAimChange( const char* szAim, __int64 nTime = 0 );

    // 处理帮派家族信息改变
    void ProcessFamilyChange( unsigned int nPlayerID, unsigned char uchFamilyID, const char* szName );       

    // 将索引和记数变量格式化成一个整型
    static unsigned int SetFormatGuildVar( unsigned short nIndex, short nValue );

    // 获得整型中的记数变量索引和变量值
    static void GetFormatGuildVar( unsigned int nValue, unsigned short &nIndex, short &nVar );

    // 设置弹劾玩家ID
    void SetDelateMemberID( unsigned int nValue );

    // 获得弹劾信息
    GuildDelateInfo& GetDelateInfo();

    // 启动捐献定时器
    void StartDonateTimer();

    // 停止捐献定时器
    void StopDonateTimer();

    // 是否在捐献时间内
    bool CheckDonateTimer();

    // 设置捐献的总金钱
    void SetDonateMoney( unsigned int nValue );

    // 获得捐献的总金钱
    unsigned int GetDonateMoney() const;

    // 处理帮派任务发布
    void ProcessQuestRelease( unsigned int nQuestType, __int64 n64Time );

    // 处理清除帮派所有成员的活跃度
    void ProcessClearMemberActivity();

    // 处理帮派弹劾申请
    void ProcessGuildDelateRequest( unsigned int nPlayerID );

    // 处理帮派召集申请
    void ProcessGuildConveneReq( unsigned int nPlayerID, unsigned int nMapID, float fPosX, float fPosY, float fDir, unsigned char uchLevel );

    // 处理帮派召集超时
    void ProcessGuildConveneTimeOut();
    //////////////////////////////////////////////////////////////////    GameServer
    // 获得玩家指针
    static T* GetPlayer( unsigned int nPlayerID );

    // 发送帮派数据到客户端 or GameServer
    void SendGuildDataToClient( unsigned int nAppiontID );    

    // 发送消息给所有帮派成员
    void SendMessageToGuild( Msg* pMessage, unsigned int nExceptID = GuildDefine::InitID, unsigned short ustLevel = 0, bool bSendToCenter = false );

    // 发送帮派数据改变请求到CenterServer
    void SendGuildDataChangeReqMessage( unsigned char uchChangeType, unsigned char uchOperateType, unsigned int nValue );   

    // 发送成员数据改变请求到CenterServer
    void SendMemberDataChangeReqMessage( unsigned int nPlayerID, unsigned char uchChangeType, unsigned char uchOperatetype, unsigned int nValue );  

    // 计算帮会实力
    unsigned int GetGuildStrength();

    // 添加国家称号
    void SetCountryTitle( unsigned char uchMemberTitle, unsigned char uchMasterTitle );

    // 清除国家称号
    void ClearCountryTitle();

    // 处理帮派召集回馈
    void ProcessGuildConveneAck( T* pPlayer );
    //////////////////////////////////////////////////////////////////    CenterServer
    // 帮派自动更新
    unsigned short RunUpdate( unsigned int nCurrentTime );   

    // 保存基本数据到数据库
    void SaveGuildDataToDatabase();     

    // 保存玩家信息到数据库
    void SaveMemberDataToDatabase();   

    // 服务器关系时, 要保存所有数据
    void SaveGuildAndMemberData();   

    // 操作帮派金钱
    void OperateGuildMoney( unsigned char uchType, unsigned int nValue );   

    // 操作帮派经验
    void OperateGuildExp( unsigned char uchType, unsigned int nValue );   

    // 操作帮派使命点
    void OperateGuildMission( unsigned char uchType, unsigned int nValue );   

    // 操作帮派津贴
    void OperateGuildSalary( unsigned char uchType, unsigned int nValue );

    // 操作帮派记数变量
    void OperateGuildVar( unsigned char uchType, unsigned int nIndex, unsigned int nValue );   

    // 操作帮派商店
    void OperateGuildShopLevel( unsigned char uchType, unsigned int nValue );

    // 操作成员帮贡
    void OperateMemberOffer( unsigned int nPlayerID, unsigned char uchType, unsigned int nValue );
    void OperateMemberOffer( GuildMember* pMember, unsigned char uchType, unsigned int nValue );

    // 操作成员活跃度
    void OperateMemberActivity( unsigned int nPlayerID, unsigned char uchType, unsigned int nValue );

    // 添加一个邀请记录
    void AddInvite( unsigned int nPlayerID, unsigned int nTargetID, unsigned int nInviteTime );

    // 查找一个邀请记录
    GuildInvite* GetInvite( unsigned int nTargetID );

    // 删除一个邀请记录
    void RemoveInvite( unsigned int nTargetID );

    // 添加一个申请记录
    void AddRequest( GuildMember& xMember, unsigned int nRequestTime );

    // 查找一个申请记录
    GuildRequest* GetRequest( unsigned int nPlayerID );

    // 删除一个申请记录
    void RemoveRequest( unsigned int nPlayerID );

    // 获得在线成员个数
    unsigned int GetOnLineCount() const;

	// 是否可以改宗旨
	bool CanChangeAim() const;

	// 发送帮派任务发布状态消息
	void SendQuestReleaseStatusMessage();

	void SendAllRequest(uint32 PlayerID);

	unsigned int GetSumByCampBattleValue(unsigned int Value);

	void UpdateGuildMemberOnLineTime(unsigned int PlayerID,__int64 Time);
protected:
    // 添加在线成员人数
    void AddOnLineCount();      

    // 减少在线成员人数
    void SubOnLineCount();   

    // 开启帮派数据保存定时器
    void StartSaveTimer();   

    // 处理帮派自动解散时间
    void ProcessDisbandTime();   

    // 处理删除一个家族
    void ProcessRemoveFamily( unsigned char uchFamilyID );     

    // 处理玩家帮派职位改变
    void ProcessGuildPositionChange( GuildMember* pMember, unsigned char uchPosition );     

    // 处理玩家家族改变
    void ProcessMemberFamilyChange( GuildMember* pMember );       

    // 发送成员数据更新消息
    void SendMemberDataUpdateMessage( unsigned int nPlayerID, unsigned char uchType, unsigned int nValue );  

    // 发送帮派数据更新消息
    void SendGuildDataUpdateMessage( unsigned char uchType, __int64 nValue );  

    // 处理更新玩家经验
    void ProcessUpdateMemberExp( unsigned int nPlayerID, unsigned int nValue );   

    // 更新邀请记录
    void UpdateInivte( unsigned int nCurrentTime ); 

    // 更新申请记录
    void UpdateRequest( unsigned int nCurrentTime );    

    // 处理弹劾结果
    void ProcessGuildDelateResult();

    // 处理捐献结束
    void ProcessGuildDonate();

    // 添加一个需要保存的成员
    void AddNeedSaveMember( unsigned int nPlayerID );
   
    // 发送清除帮派成员的活跃度消息
    void SendClearMemberActivityMessage();

    // 结算帮派使命点
    unsigned short ProcessGuildMissionSettle();

    // 清理帮派津贴
    void ProcessClearGuildSalary();

    // 处理每天12点帮派记数请0
    unsigned short ProcessGuildVarClear();

	// 设置修改宗旨的CD
	void SetChangeAimCD( __int64 nTime );

	// 获取修改总置的CD
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

    MemberMap m_mapMember;              // 成员列表
    int m_nOnLineCount;                 // 在线玩家个数

    InviteMap m_mapInvite;              // 邀请信息
    RequestMap m_mapRequest;            // 申请记录
    
    SaveSet m_setSave;                  // 需要保存的成员
    GameTimerEx m_xDataSaveTimer;       // 帮派数据保存Timer
    GameTimerEx m_xMemberSaveTimer;     // 帮派成员保存的Timer

    GameTimerEx m_xDonateTimer;         // 发起捐献的Timer
    unsigned int m_nDonateMoney;        // 捐献的钱
    ///////////////////////////////////////////////////////////////////
    GuildDelateInfo m_xGuildDelate;     // 弹劾信息

    GameTimerEx m_xReleaseTimer;        // 任务发布定时器
    GameTimerEx m_xUpdateActivityTimer; // 活跃度定时器
    GameTimerEx m_xUpdateSalaryTimer;   // 帮派津贴定时器
    GameTimerEx m_xUpdateMissionTimer;  // 使命点定时器

    // 帮派召集
    GameTimerEx m_xConveneTimer;        // 帮派召集定时器
    unsigned char m_uchConveneLevel;    // 召集的等级限制
    unsigned int m_nConveneMapID;       // 召集的地图
    float m_fConvenePosX;               // 召集X坐标
    float m_fConvenePosY;               // 召集Y坐标
    float m_fConveneDir;                // 召集朝向

    unsigned int m_nVarClearTime;       // 帮派时间记数过12点清0

	__int64 m_nChangeAimCD;				// 修改宗旨的CD
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
    case GuildDefine::UpdateMemberOnLine:   // 更新在线
        pMember->SetOnLine( nValue == 1 ? true : false );
        break;
    case GuildDefine::UpdateMemberLevel:    // 更新等级
        pMember->SetLevel( nValue );
        break;
	case GuildDefine::UpdateMemberCampBattleValue:
		pMember->SetCampBattleValue(nValue);
		break;
    case GuildDefine::UpdateMemberPosition: // 更新职位
        pMember->SetPosition( nValue );
        ProcessGuildPositionChange( pMember, nValue );    // 处理帮派职位改变
        break;
    case GuildDefine::UpdateMemberFamily:   // 更新家族
        pMember->SetFamilyID( nValue );
        ProcessMemberFamilyChange( pMember );
        break;
    case GuildDefine::UpdateMemberActivity: // 更新活跃度
        pMember->SetActivity( nValue );
        break;
    case GuildDefine::UpdateMemberOffer:    // 更新帮贡
        pMember->SetOffer( nValue );
        break;
    case GuildDefine::UpdateMemberProfession:  // 更新职业
        pMember->SetProfession( nValue );
        break;
    case GuildDefine::UpdateMemberExp:      // 更新成员经验
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
    case GuildDefine::UpdateGuildLevel:     // 更新帮派等级
        SetLevel( static_cast< unsigned int >( n64Value ) );
        break;
    case GuildDefine::UpdateGuildMoney:     // 更新帮派金钱
		{
        SetMoney( static_cast< unsigned int >( n64Value ) );
		}
		//theLogEventService.LogGuildDetail(0,0,GetID(),n64Value,0,0);
        break;
    case GuildDefine::UpdateGuildExp:       // 更新帮派经验
		{
        SetExp( static_cast< unsigned int >( n64Value ) );
		//theLogEventService.LogGuildDetail(0,0,GetID(),0,n64Value,0);
		}
        break;
    case GuildDefine::UpdateGuildMission:   // 更新帮派使命点
        SetMission( static_cast< unsigned int >( n64Value ) );
        break;
    case GuildDefine::UpdateGuildMaster:    // 更新帮派帮主
        SetMasterID( static_cast< unsigned int >( n64Value ) );
        break;
    case GuildDefine::UpdateGuildVar:       // 更新帮派记数
        {
            unsigned short nIndex = 0;
            short nVar = 0;
            GetFormatGuildVar( static_cast< unsigned int >( n64Value ), nIndex, nVar );
            SetGuildVar( nIndex, nVar );
        }
        break;
    case GuildDefine::UpdateGuildDonate:    // 更新帮派捐献的最大金钱
        SetDonateMoney( static_cast< unsigned int >( n64Value ) );
        break;
    case GuildDefine::UpdateGuildShopLevel: // 更新帮派商店等级
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
        nValue += GetMission(); // 使命点可以无限加
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
        nValue += GetSalary(); // 使命点可以无限加
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

    //（帮会总人数等级和/帮会最大人数）*（0+帮会等级*系数）
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

// 获得整型中的记数变量索引和变量值
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
        iter->second.SetLastActivity( iter->second.GetActivity() ); // 将本周的放入上周
        iter->second.SetActivity( 0 );  // 清除本周
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