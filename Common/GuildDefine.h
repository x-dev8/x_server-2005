#ifndef __GUILDEFINE_H__
#define __GUILDEFINE_H__

/************************************************************************
                ����ṹ����
                MaintenanceMan Mail: lori227@live.cn
************************************************************************/
namespace GuildDefine
{
    enum EConstDefine
    {
        // ���ɵĸ���Ȩ��....
        Right_None     = 0,
        Right_View     = 0x1,       // �鿴Ȩ
        Right_Donate   = 0x2,       // �������Ȩ
        Right_Collect  = 0x4,       // ļ��Ȩ       
        Right_Build    = 0x8,       // �ﹱ����
        Right_Leave    = 0x10,      // �뿪����
        Right_Delate   = 0x20,      // ����Ȩ
        Right_Invite   = 0x40,      // ����Ȩ
        Right_Transfer = 0x80,      // ����ְλ
        Right_Assign   = 0x100,     // ����ְλ
        Right_Resign   = 0x200,     // ��ȥְλ
        Right_Notice   = 0x400,     // �޸Ĺ���
        Right_Kick     = 0x800,     // �߳�����
        Right_League   = 0x1000,    // ��������
        Right_Family   = 0x2000,    // ����Ȩ��( ���� �������.��һϵ�� )
        Right_LevelUp  = 0x4000,    // ��������
        Right_Release  = 0x8000,    // ���񷢲�Ȩ
        Right_Shop     = 0x10000,   // �����̵�Ȩ��
        Right_Convene  = 0x20000,   // �����ټ�Ȩ
		Right_InFamily = 0x40000,	// ת�����
		Right_OutFamily = 0x80000,	// ���ó�Աת������
		Right_OutFamilyOther = 0x100000,	// �Ǳ��ó�Աת������
		Right_Aim	   = 0x200000,	// �޸���ּ

        // ��ͨ����Ȩ��
        Right_Member = Right_View | Right_Collect | Right_Build | Right_Delate | Right_Leave,
        // ���峤Ȩ��
        Right_FamilyMaster = Right_View | Right_Collect | Right_Build | Right_Delate | Right_Transfer | Right_Resign | Right_InFamily | Right_OutFamily,
        // ������Ȩ��
        Right_ViceMaster = Right_View | Right_Collect | Right_Build | Right_Delate | Right_Invite /*| Right_Transfer*/ | Right_Resign | Right_Convene | Right_Kick | Right_InFamily | Right_OutFamily | Right_OutFamilyOther,
        // ������Ȩ��
        Right_Master = Right_View | Right_Donate | Right_Collect | Right_Build | Right_Invite | Right_Transfer | Right_Notice | Right_Kick | Right_League | Right_Assign | Right_Family | Right_LevelUp | Right_Release | Right_Shop | Right_Convene | Right_InFamily | Right_OutFamily | Right_OutFamilyOther | Right_Aim,

        // ���ɵ�ְλ����
        Position_None = 0,         // 
        Position_Member,           // ��ͨ����
        Position_FamilyMaster,     // ���峤
        Position_ViceMaster,       // ������
        Position_Master,           // ����

        ///////////////////////////////////////////////////////////////////
        MaxCreateLength = 17,      // �����������󳤶�
        MaxNameLength = 33,        // ������󳤶�
        MaxNoticeLength = 61,      // ������󳤶�
		MaxAimLength = 61,		   // ��ּ��󳤶�
        MaxFamilyLength = 17,      // ����������󳤶�
        MaxFamilyCount  = 5,       // ���������
        MaxGuildVarCount = 500,    // �����������ĸ���
        InitID = 0,                // ��ʼID

        UpdateSpaceTime = 10000,   // 10�����һ��
        SaveSpaveTime   = 300000,  // 10�������ݱ���һ��
        InviteKeepTime  = 90000,   // ���������ı���ʱ��
        LoadSpaceTime   = 1200000, // 20��������һ��
        DelateKeepTime  = 180000,  // ����3��������Ч
        DonateKeepTime  = 300000,  // ����5��������Ч
        ReleaseKeepTime = 7200000, // ���񷢲�����ʱ�� 2Сʱ
        ConveneKeepTime = 300000,  // �����ټ�5��������Ч
        //////////////////////////////////////////////////////////////
        UpdateNormal = 1,   // 
        UpdateDiaband,      // ��ɢ
        ////////////////////////////////////////////////////////////////
        // ��Ա��Ϣ���±�־
        UpdateMemberOnLine = 1,     // ��������
        UpdateMemberLevel,          // ���µȼ�
        UpdateMemberPosition,       // ����ְλ
        UpdateMemberFamily,         // ���¼���
        UpdateMemberActivity,       // ���»�Ծ��
        UpdateMemberOffer,          // ���°ﹱ
        UpdateMemberProfession,     // ����ְҵ
        UpdateMemberExp,            // ������Ҿ���( �ͻ��˲��ô��� )
		UpdateMemberCampBattleValue,// ������ҵ�ս��Ȩ��

        // ������Ϣ���±�� 
        UpdateGuildLevel = 1,       // ���°��ɵȼ�
        UpdateGuildMoney,           // ���°��ɽ�Ǯ
        UpdateGuildExp,             // ���°��ɾ���
        UpdateGuildMission,         // ���°���ʹ����
        UpdateGuildMaster,          // ���°��ɰ���
        UpdateGuildVar,             // ���°��ɼ�������
        UpdateGuildDonate,          // ���°��ɾ��׵Ľ�Ǯ( �ͻ��˲��ô��� )
        UpdateGuildShopLevel,       // ���°����̵�ȼ�
        UpdateGuildDisbandTime,     // ���°��ɽ�ɢʱ��
        UpdateGuildSalary,          // ���°��ɽ���
		UpdateGuildMissionCount,	// ���°���
		UpdateGuildBattleSum,		//
		UpdateGuildChangeName,		//
		UpdateGuildCampBattlePoint, // ���°���ս������

        ////////////////////////////////////////////////////////////////
        OperateAdd = 1,             // +
        OperateSub,                 // -
        OperateSet,                 // =
        ////////////////////////////////////////////////////////////////

        DecodeFieldBufferSize = 1024 * 10,
        UnZipTempBufferSize   = 1024 * 20,
        ZipTempBufferSize     = 1024 * 40,
        EncodeFieldBufferSize = 1024 * 10,
		PlayerLvIsThirty = 30,		// ��ҵ���30����֪ͨ�����а��ɵİ���
		MissionFirst	 = 1,		// ʹ���㲻�㣬��һ��
		MissionSecond	 = 2,		// ʹ���㲻�㣬�ڶ���
		MissionThird	 = 3,		// ʹ���㲻�㣬������

		CampBattleCountry  = 1,
		CampBattleGuild    = 2,
		CampBattleGuildUnion = 4,
		GameBattleGuildGeneral = 8,
    };

    static unsigned int GetRightByPositon( unsigned char uchPositon )
    {
        unsigned int nRight = Position_None;
        switch ( uchPositon )
        {
        case Position_Member:
            nRight = Right_Member;
        	break;
        case Position_FamilyMaster:
            nRight = Right_FamilyMaster;
            break;
        case Position_ViceMaster:
            nRight = Right_ViceMaster;
            break;
        case Position_Master:
            nRight = Right_Master;
            break;
        default:
            break;
        }

        return nRight;
    }
}

// ������Ϣ( ���������һ�� )
class FamilyData
{
public:
    FamilyData()
    {
        memset( m_szName, 0, sizeof( m_szName ) );
    }

    const char* GetName() const { return m_szName; }
    void SetName( const char* szValue ) { strncpy_s( m_szName, sizeof( m_szName ), szValue, sizeof( m_szName ) - 1 ); }

    bool IsEmpty() const { return m_szName[0] == 0; }

protected:
    char m_szName[ GuildDefine::MaxFamilyLength ];      // ��������
};

class GuildData
{
public:
    GuildData() : m_nID( GuildDefine::InitID ), m_uchCountry( 0 ), m_uchLevel( 0 ), m_nMasterID( GuildDefine::InitID ), m_nMoney( 0 ), m_nExp( 0 ), m_nMission( 0 ), m_n64CreateTime( 0 ),
                    m_ustReleaseQuest( 0 ), m_n64ReleaseTime( 0 ), m_nShopLevel( 0 ), m_nSalary( 0 ), m_nMissionCount( 0 ),m_BattleSum(0),m_ChangeName(false),m_GuildCampBattlePoint(0)
    {
        memset( m_szName, 0, sizeof( m_szName ) );
        memset( m_szNotice, 0, sizeof( m_szNotice ) );
		memset( m_szAim, 0, sizeof( m_szAim ) );
    }

    unsigned int GetID() const { return m_nID; }
    unsigned char GetLevel() const { return m_uchLevel; }
    unsigned int GetCountry() const { return m_uchCountry; }
    const char* GetName() const { return m_szName; }
    const char* GetNotice() const { return m_szNotice; }
	const char* GetAim() const { return m_szAim; }
    unsigned int GetMasterID() const { return m_nMasterID; }
    unsigned int GetShopLevel() const { return m_nShopLevel; }
    unsigned int GetMoney() const { return m_nMoney; }
    unsigned int GetExp() const { return m_nExp; }
    unsigned int GetMission() const { return m_nMission; }
    unsigned int GetSalary() const { return m_nSalary; }
	unsigned int GetMissionCount() const { return m_nMissionCount; }
    __int64 GetCreateTime() const { return m_n64CreateTime; }
    unsigned short GetReleaseQuest() const { return m_ustReleaseQuest; }
    __int64 GetReleaseTime() const { return m_n64ReleaseTime; }
	unsigned int GetStrength() const {return m_nGuildStrength;}
	unsigned int GetBattleSum() const {return m_BattleSum;}
	bool GetIsCanChangeName() const{return m_ChangeName;}
	unsigned int GetGuildCampBattlePoint() const{return m_GuildCampBattlePoint;}

    void SetID( unsigned int nValue ) { m_nID = nValue; }
    void SetLevel( unsigned char uchValue ) { m_uchLevel = uchValue; }
    void SetCountry( unsigned char uchValue ) { m_uchCountry = uchValue; }
    void SetName( const char* szValue ) { strncpy_s( m_szName, sizeof( m_szName ), szValue, sizeof( m_szName ) - 1 ); }
    void SetNotice( const char* szValue ) { strncpy_s( m_szNotice, sizeof( m_szNotice ), szValue, sizeof( m_szNotice ) - 1 ); }
	void SetAim( const char* szValue ) { strncpy_s( m_szAim, sizeof( m_szAim ), szValue, sizeof( m_szAim ) - 1 ); }
    void SetMasterID( unsigned int nValue ) { m_nMasterID = nValue; }
    void SetShopLevel( unsigned int nValue ) { m_nShopLevel = nValue; }
    void SetMoney( unsigned int nValue ) { m_nMoney = nValue; }
    void SetExp( unsigned int nValue ) { m_nExp = nValue; }
    void SetMission( unsigned int nValue ) { m_nMission = nValue; }
    void SetSalary( unsigned int nValue ) { m_nSalary = nValue; }
    void SetCreateTime( __int64 n64Value ) { m_n64CreateTime = n64Value; }
    void SetReleaseQuest( unsigned short ustValue ) { m_ustReleaseQuest = ustValue; }
    void SetReleaseTime( __int64 n64Value ) { m_n64ReleaseTime = n64Value; }
	void SetMissionCount( unsigned int nCount ) { m_nMissionCount = nCount; }
	void SetStrength(unsigned int Strength){m_nGuildStrength = Strength;}
	void SetBattleSum(unsigned int BattleSum){m_BattleSum = BattleSum;}
	void SetChangeName(bool IsCan){m_ChangeName = IsCan;}
	void SetGuildCampBattlePoint(unsigned int Point){m_GuildCampBattlePoint = Point;}

    // �������ID ( 1- 5 )
    FamilyData* GetFamily( unsigned char uchID );
    // ��ü�������
    const char* GetFamilyName( unsigned char uchID );
    // ���ü�������
    void SetFamilyName( unsigned char uchID, const char* szName );
    // ���һ������, ����ID
    unsigned char AddFamily( const char* szName );
    // ��ü���ID
    unsigned char GetFamilyID( const char* szName ) const;
    // ��ü������
    unsigned char GetFamliyCount() const;
    // ���һ���յļ���
    unsigned char GetEmptyFamilyID() const;
    // �Ƿ��м���
    bool HaveFamily( unsigned char uchID );

    // ���ð�������
    void SetGuildData( GuildData& xData );

    // ��ð�������
    void GetGuildData( GuildData& xData ) const;

    // �����̵�ȼ�����״̬
    void SetShopActive( unsigned char uchLevel );

    // �ж��̵�ȼ��Ƿ񼤻�
    bool CheckShopActive( unsigned char uchLevel ) const;

protected:
    unsigned int m_nID;                                 // ����ID
    unsigned char m_uchLevel;                           // ���ɵȼ�
    unsigned char m_uchCountry;                         // ����
    char m_szName[ GuildDefine::MaxNameLength ];        // ��������
    char m_szNotice[ GuildDefine::MaxNoticeLength ];    // ���ɹ���
	char m_szAim[ GuildDefine::MaxAimLength ];			// ������ּ
    unsigned int m_nMasterID;                           // ����ID
    unsigned int m_nShopLevel;                          // �����̵�ȼ�
    unsigned int m_nMoney;                              // �����ʽ�
    unsigned int m_nExp;                                // ���ɾ���
    unsigned int m_nMission;                            // ����ʹ����
	unsigned int m_nMissionCount;						// ����ʹ���㲻�� ���� luo.qin 4.21
    unsigned int m_nSalary;                             // ���ɽ���
    __int64 m_n64CreateTime;                            // ����ʱ��
    FamilyData xFamily[ GuildDefine::MaxFamilyCount ];  // ������Ϣ
    unsigned short m_ustReleaseQuest;                   // ����������
    __int64 m_n64ReleaseTime;                           // ���������ʱ��
	unsigned int m_nGuildStrength;						// ֻ���������浽���ݿ���
	unsigned int m_BattleSum;							// ��������ս��������
	bool		 m_ChangeName;							// �Ƿ���Ը���
	unsigned int m_GuildCampBattlePoint;				// Ѫսɳ���ĵ���
    // �������..
};

// ������ʹ��
class GuildDataToServer : public GuildData
{
public:
    GuildDataToServer() : GuildData(), m_n64DisbandTime( 0 ), m_nDonateMoney( 0 )
    {
        memset( m_stGuildVars, 0 , sizeof( m_stGuildVars ) );
    }

    __int64 GetDisbandTime() const { return m_n64DisbandTime; }
    unsigned int GetDonateMoney() const { return m_nDonateMoney; }
    
    void SetDisbandTime( __int64 n64Value ) { m_n64DisbandTime = n64Value; }
    void SetDonateMoney( unsigned int nValue ) { m_nDonateMoney = nValue; }

    short* GetVarAddress() { return m_stGuildVars; }
    void InitGuildVar( short* stValue, int nCount );
    short GetGuildVar( unsigned short ustIndex ) const;
    void SetGuildVar( unsigned short ustIndex, short stValue );

    // ���ð�������
    void SetGuildDataToServer( GuildDataToServer& xData );
    // ��ð�������
    void GetGuildDataToServer( GuildDataToServer& xData );

protected:
    short m_stGuildVars[ GuildDefine::MaxGuildVarCount ]; // �����������
    __int64 m_n64DisbandTime;                             // �����ɢ������ʱ��( == 0 û������ʱ�� ) 

    unsigned int m_nDonateMoney;                          // �ۼƾ��׵İ���Ǯ
};

// ����Ա����
class GuildMember
{
public:
    GuildMember() : m_nID( GuildDefine::InitID ), m_ustLevel( 0 ), m_uchProfession( 0 ), m_nOffer( 0 ), m_ustActivity( 0 ), m_nGuildID( 0 ), m_uchPosition( 0 ), m_uchFamilyID( 0 ), m_bOnLine( false ),
                    m_ustLastActivity( 0 ),m_CampBattleValue(0),LastOnLineTime(0)
    {
        memset( m_szName, 0, sizeof( m_szName ) );
    }

    unsigned int GetID() const { return m_nID; }
    const char* GetName() const { return m_szName; }
    unsigned short GetLevel() const { return m_ustLevel; }
    unsigned char GetProfession() const { return m_uchProfession; }
    unsigned int GetOffer() const { return m_nOffer; }
    unsigned short GetActivity() const { return m_ustActivity; }
    unsigned short GetLastActivity() const { return m_ustLastActivity; }
    unsigned int GetGuildID() const { return m_nGuildID; }
    unsigned char GetPosition() const { return m_uchPosition; }
    unsigned char GetFamilyID() const { return m_uchFamilyID; }
    bool GetOnLine() const { return m_bOnLine; }
	unsigned int GetCampBattleValue() const {return m_CampBattleValue;}
	__int64 GetOnLineTime() const {return LastOnLineTime;}

    void SetID( unsigned int nValue ) { m_nID = nValue; }
    void SetName( const char* szValue ) { strncpy_s( m_szName, sizeof( m_szName ), szValue, sizeof( m_szName ) - 1 ); }
    void SetLevel( unsigned short ustValue ) { m_ustLevel = ustValue; }
    void SetProfession( unsigned char uchValue ) { m_uchProfession = uchValue; }
    void SetOffer( unsigned int nValue ) { m_nOffer = nValue; }
    void SetActivity( unsigned short ustValue ) { m_ustActivity = ustValue; }
    void SetLastActivity( unsigned short ustValue ) { m_ustLastActivity = ustValue; }
    void SetGuildID( unsigned int nValue ) { m_nGuildID = nValue; }
    void SetPosition( unsigned char uchValue ) { m_uchPosition = uchValue; }
    void SetFamilyID( unsigned char uchValue ) { m_uchFamilyID = uchValue; }
    void SetOnLine( bool bValue ) { m_bOnLine = bValue; }
	void SetCampBattleValue(unsigned int Value){m_CampBattleValue = Value;}
	void SetOnLineTime(__int64 Time){LastOnLineTime = Time;}
protected:
    unsigned int m_nID;                             // ID
    char m_szName[ GuildDefine::MaxNameLength ];    // ����
    unsigned short m_ustLevel;                      // �ȼ�
    unsigned char m_uchProfession;                  // ְҵ  
    unsigned int m_nOffer;                          // �ﹱ
    unsigned short m_ustActivity;                   // ��Ծ��( ���� )
    unsigned short m_ustLastActivity;               // ��Ծ��( ���� )
    unsigned int m_nGuildID;                        // ����ID
    unsigned char m_uchPosition;                    // ����ְλ
    unsigned char m_uchFamilyID;                    // ����ID
    bool m_bOnLine;                                 // �Ƿ�����
	unsigned int m_CampBattleValue;					// ս����ֵ ����ڹ������ս����ʱ���Ա���Խ�����Щս��
	__int64 LastOnLineTime;							// �������ʱ�� ��¼����ϴ����ߵ�ʱ��
};

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
inline FamilyData* GuildData::GetFamily( unsigned char uchID )
{
    if ( uchID == GuildDefine::InitID || uchID > GuildDefine::MaxFamilyCount )
    { return NULL; }

    return &( xFamily[ uchID - 1 ] );
}

inline const char* GuildData::GetFamilyName( unsigned char uchID )
{
    FamilyData* pFamily = GetFamily( uchID );
    if ( pFamily == NULL )
    { return ""; }

    return pFamily->GetName();
}

inline void GuildData::SetFamilyName( unsigned char uchID, const char* szName )
{
    FamilyData* pFamily = GetFamily( uchID );
    if ( pFamily == NULL )
    { return; }

    pFamily->SetName( szName );
}

inline unsigned char GuildData::AddFamily( const char* szName )
{
    if ( szName == NULL || szName[0] == 0 )
    { return GuildDefine::InitID; }

    unsigned char uchIndex = GuildDefine::InitID;
    for ( int i = 0; i < GuildDefine::MaxFamilyCount; ++i )
    {
        if ( !xFamily[i].IsEmpty() )
        { continue; }

        xFamily[i].SetName( szName );
        uchIndex = i + 1;
        break;
    }

    return uchIndex;
}

inline unsigned char GuildData::GetFamilyID( const char* szName ) const
{
    if ( szName == NULL || szName[0] == 0 )
    { return GuildDefine::InitID; }

    unsigned char uchIndex = GuildDefine::InitID;

    for ( int i = 0; i < GuildDefine::MaxFamilyCount; ++i )
    {
        if ( xFamily[i].IsEmpty() )
        { continue; }

        if ( strcmp( xFamily[i].GetName(), szName ) != 0 )
        { continue; }

        uchIndex = i + 1;
        break;
    }

    return uchIndex;
}

inline unsigned char GuildData::GetFamliyCount() const
{
    unsigned char uchCount = 0;
    for ( int i = 0; i < GuildDefine::MaxFamilyCount; ++i )
    {
        if ( xFamily[i].IsEmpty() )
        { continue; }
        
        ++uchCount;
    }

    return uchCount;
}

inline unsigned char GuildData::GetEmptyFamilyID() const
{
    for ( int i = 0; i < GuildDefine::MaxFamilyCount; ++i )
    {
        if ( xFamily[i].IsEmpty() )
        { 
            return i + 1;
        }
    }

    return GuildDefine::InitID;
}

inline bool GuildData::HaveFamily( unsigned char uchID )
{
    FamilyData* pFamily = GetFamily( uchID );
    if ( pFamily == NULL )
    { return false; }

    return !pFamily->IsEmpty();
}

inline void GuildDataToServer::InitGuildVar( short* stValue, int nCount )
{
    memcpy_s( m_stGuildVars, sizeof( m_stGuildVars ), stValue, nCount * sizeof( short ) );
}

inline short GuildDataToServer::GetGuildVar( unsigned short ustIndex ) const
{
    if ( ustIndex >= GuildDefine::MaxGuildVarCount )
    { return 0; }

    return m_stGuildVars[ustIndex];
}

inline void GuildDataToServer::SetGuildVar( unsigned short ustIndex, short stValue )
{
    if ( ustIndex >= GuildDefine::MaxGuildVarCount )
    { return; }

    m_stGuildVars[ustIndex] = stValue;
}


inline void GuildData::SetGuildData( GuildData& xData )
{
    SetID( xData.GetID() );
    SetLevel( xData.GetLevel() );
    SetName( xData.GetName() );
    SetCountry( xData.GetCountry() );
    SetNotice( xData.GetNotice() );
    SetMasterID( xData.GetMasterID() );
    SetShopLevel( xData.GetShopLevel() );
    SetMoney( xData.GetMoney() );
    SetExp( xData.GetExp() );
    SetMission( xData.GetMission() );
    SetSalary( xData.GetSalary() );
    SetCreateTime( xData.GetCreateTime() );
	SetBattleSum(xData.GetBattleSum());
	SetChangeName(xData.GetIsCanChangeName());
    memcpy_s( xFamily, sizeof( xFamily ), xData.xFamily, sizeof( xFamily ) );
    SetReleaseQuest( xData.GetReleaseQuest() );
    SetReleaseTime( xData.GetReleaseTime() );
	SetGuildCampBattlePoint(xData.GetGuildCampBattlePoint());
}

inline void GuildData::GetGuildData( GuildData& xData ) const
{
    xData.SetID( GetID() );
    xData.SetLevel( GetLevel() );
    xData.SetCountry( GetCountry() );
    xData.SetName( GetName() );
    xData.SetNotice( GetNotice() );
    xData.SetMasterID( GetMasterID() );
    xData.SetShopLevel( GetShopLevel() );
    xData.SetMoney( GetMoney() );
    xData.SetExp( GetExp() );
    xData.SetMission( GetMission() );
    xData.SetSalary( GetSalary() );
    xData.SetCreateTime( GetCreateTime() );
	xData.SetBattleSum(GetBattleSum());
	xData.SetChangeName(GetIsCanChangeName());
    memcpy_s( xData.xFamily, sizeof( xFamily ), xFamily, sizeof( xFamily ) );
    xData.SetReleaseQuest( GetReleaseQuest() );
    xData.SetReleaseTime( GetReleaseTime() );
	xData.SetGuildCampBattlePoint(GetGuildCampBattlePoint());
}


inline void GuildData::SetShopActive( unsigned char uchLevel )
{
    m_nShopLevel |= ( 1 << uchLevel );
}

inline bool GuildData::CheckShopActive( unsigned char uchLevel ) const
{
    return ( m_nShopLevel & ( 1 << uchLevel ) ) != 0;
}

inline void GuildDataToServer::SetGuildDataToServer( GuildDataToServer& xData )
{
    SetGuildData( xData );

    SetDisbandTime( xData.GetDisbandTime() );
    memcpy_s( m_stGuildVars, sizeof( m_stGuildVars ), xData.m_stGuildVars, sizeof( m_stGuildVars ) );
}

inline void GuildDataToServer::GetGuildDataToServer( GuildDataToServer& xData )
{
    GetGuildData( xData );

    xData.SetDisbandTime( GetDisbandTime() );
    memcpy_s( xData.m_stGuildVars, sizeof( m_stGuildVars ), m_stGuildVars, sizeof( m_stGuildVars ) );
}

class GuildInvite
{
public:
    GuildInvite() : m_nPlayerID( 0 ), m_nTargetID( 0 ), m_nInviteTime( 0 ) {}

    unsigned int GetPlayerID() const { return m_nPlayerID; }
    unsigned int GetTargetID() const { return m_nTargetID; }
    unsigned int GetInviteTime() const { return m_nInviteTime; }

    void SetPlayerID( unsigned int nValue ) { m_nPlayerID = nValue; }
    void SetTargetID( unsigned int nValue ) { m_nTargetID = nValue; }
    void SetInviteTime( unsigned int nValue ) { m_nInviteTime = nValue; }

protected:
    unsigned int m_nPlayerID;     // ������
    unsigned int m_nTargetID;     // Ҫ������ɵ�Ŀ��
    unsigned int m_nInviteTime;   // ����ʱ��
};

class GuildRequest
{
public:
    const GuildMember& GetMember() const { return m_xMember; }
    unsigned int GetRequestTime() const { return m_nRequestTime; }

    void SetMember( GuildMember& xMember ) { m_xMember = xMember; }
    void SetRequestTime( unsigned int nValue ){ m_nRequestTime = nValue; }

protected:
    GuildMember m_xMember;         // ��������
    unsigned int m_nRequestTime;   // ����ʱ��
};

// �ͻ��˰����б���Ϣ
class GuildListInfo
{
public:
    unsigned int GetID() const { return nGuildID; }
	unsigned int GetMemberNum() const { return nMemberNum; }
    unsigned char GetCountry() const { return uchCountry; }
    unsigned char GetLevel() const { return uchLevel; }
    const char* GetName() const { return szName; }
	const char* GetMasterName() const { return szMasterName; }

    void SetID( unsigned int nValue ) { nGuildID = nValue; }
	void SetMemberNum( unsigned int nMemNum ) { nMemberNum = nMemNum; }
    void SetCountry( unsigned char uchValue ) { uchCountry = uchValue; }
    void SetLevel( unsigned char uchValue ) { uchLevel = uchValue; }
    void SetName( const char* szValue ) { strncpy_s( szName, sizeof( szName ), szValue, sizeof( szName ) - 1 ); }
	void SetMasterName (const char* szValue ) { strncpy_s( szMasterName, sizeof( szMasterName ), szValue, sizeof( szMasterName) - 1 );}

protected:
    unsigned char uchCountry;
    unsigned char uchLevel;
    unsigned int nGuildID;
	unsigned int nMemberNum;
	char szMasterName[GuildDefine::MaxNameLength];
    char szName[ GuildDefine::MaxNameLength ];
};

#endif