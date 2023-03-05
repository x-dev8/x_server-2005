#ifndef __RELATIONDEFINE_H__
#define __RELATIONDEFINE_H__

/************************************************************************
                ��ϵ�ṹ����
                MaintenanceMan Mail: lori227@live.cn
************************************************************************/
namespace RelationDefine
{
    enum EConstDefine
    {
        // 1����ϵ, (ֻ����һ��)
        InitRelation = 0,         // ��Чֵ
        TempFriend = 0x1,       // ��ʱ����
        Friend     = 0x2,       // ����
        Vendetta   = 0x4,       // ����
        BlackList  = 0x8,       // ������( ���������Ժͳ��˲��� )


        // 2����ϵ( ֻ���ں��ѵĻ����Ͻ���, ɾ��2����ϵ,���ѹ�ϵ��Ȼ���ڵ� )
        Marriage   = 0x100,     // ����
        Teacher    = 0x200,     // ʦ��( ��ʦǰ )
        Student    = 0x400,     // ͽ��( ��ʦǰ )
        Brother    = 0x800,     // ���

        // ��ʦ�Ժ�, ��Щ�����õĹ�ϵ
        Master     = 0x1000,    // ͽ�ܳ�ʦ�Ժ� ʦ���Ĺ�ϵ
        Prentice   = 0x2000,    // ͽ�ܳ�ʦ�Ժ� ͽ�ܵĹ�ϵ

        MaxRelation = 0xFFFF,

        ///////////////////////////////////////////////////////////////////
        UpdateLevel = 1,        // ���µȼ�
        UpdateHeadPic,          // ����ͷ��
        UpdateCountry,
        UpdateProfession,
        UpdateSex,
        UpdateName,
        UpdateGuild,
        UpdatePosition,
		UpdateFamily,
        UpdateMasterLevel,
        UpdateMessageRefuse,
        UpdateRewardExp,
        UpdateRewardPrestige,
        UpdateLastStudentTime,
        UpdateLastTeacherTime,
        UpdateSignature,           // ����ǩ��
        UpdateTitle,
        UpdateMapID,
        UpdateIp,
        ///////////////////////////////////////////////////////////////////
        UpdateAddFriendly = 1,
        UpdateSubFriendly,
        UpdateSetFriendly,
        UpdateRelation,
        UpdateLocked,
        UpdateGroupID,
        UpdateRemark,
        ///////////////////////////////////////////////////////////////////dd

        MaxIpLength         = 16,
		ProvinceLength		= 17,
		CityLength			= 9,
		ProfessionLength	= 17,
		QQLength			= 20,
		MSNLength			= 30,
		IntructionLength	= 85,   

        MaxNameLength   = 33,   // ��󳤶�
        MaxSignLength   = 21,   // ǩ����󳤶�
        ReMarkLength    = 21,   // ��ұ�ע�ĳ���
        GroupLength     = 17,   // ����ĳ���
        GroupCount      = 6,    // ����ĸ���
        InitID          = 0,    // ��Ч��ID
        NotSendToClient = 0,    // ��������Ϣ
        SendToClient    = 1,    // ������Ϣ���ͻ���

        // �ܾ�������Ϣ����
        Refuse_None = 0,
        Refuse_Stranger,     // �ܾ�İ����
        Refuse_AllPlayer,    // �ܾ�������

        RelationInviteTimeOunt = 100000,     // ����Ӻ�����Чʱ��1����
        AutoSaveSpaceTime = 600000,          // �Զ�����10����һ��
        UpdateSpaceTime = 10000,       // 10�����һ������������¼
        ///////////////////////////////////////////////////////////////////////////
        //������Ӻ��з��صĴ�����Ϣ
        AddRelationSuccess = 0,       // ��ӳɹ�
        CanAddRelation,               // ������ӹ�ϵ
        CanNotAddRelation,            // ������Ӵ˹�ϵ
        AlreadyHaveRelation,          // �Ѿ������ֹ�ϵ
        MustBeFriendRelation,         // �����Ǻ��ѹ�ϵ
        NameError,                    // Ҫ����ӵ���Ҳ�����
        CanNotAddSelf,                // ��������Լ�
        NotOnLine,                    // ��Ҳ�����     
        RelationFull,                 // �Լ��ù�ϵ�Ѿ��ﵽ�����
        TargetRelationFull,           // �Լ��ù�ϵ�Ѿ��ﵽ�����
        AddStudentTimeLimit,          // ����ͽ��ʱ������   3��ֻ����1��ͽ��
        TargetAddStudentTimeLimit,    // �Է�����ͽ��ʱ������
        AddTeacherTimeLimit,          // ��ʦʱ������       һ��ֻ�ܰ�ʦһ��
        TargetAddTeacherTimeLimit,    // �Է���ʦʱ������
        StudentCountLimit,            // ����ͽ����������       ��ǰͽ�������Ѿ��ﵽ���ֵ
        TargetStudentCountLimit,      // �Է�����ͽ����������
        TargetNotAgree,               // �Է���ͬ��
        AlreadyHaveTeacher,           // �Ѿ���ʦ����
        TargetAlreadyHaveTeacher,     // �Է��Ѿ���ʦ����
        CanNotReceivePrentice,        // ��û�г�ʦ, ������ͽ��
        TargetCanNotReceivePrentice,  // �Է���û�г�ʦ, ������ͽ��
        AddStudentMustInArea,         // ��ʦ ��ͽ ʱ �����ڸ���
        StudentMinLevelLimit,         // ͽ����͵ȼ�����( �ȼ���FriendlyConfig �� )
        TeacherMinLevelLimit,         // ͽ����ߵȼ�����
        StudentMinLevelSpan,          // ʦ����ͽ����С�ȼ�������
        MustSameCountry,              // ������ͬһ���Ҳſ�����Ӵ˹�ϵ

        ////////////////////////////////////////////////////////////////////////////////
		// ��ѯ��Ҳ���������
		UNLimitInit	= 0,
		UnLimitSex	= 0x1,	// �����Ա�
		UnLimitAge	= 0x2,	// ����
		UnLimitPrv	= 0x4,	// ʡ��
		UnLimitCity	= 0x8,	// ����
    };

    // Ĭ�Ϸ���
    const static char* s_szDefaultGroup = "�ҵĺ���";
}
//qq���ҵ���Ϣ
struct PersonalInfo
{
	enum ERight
	{
		ER_Open,		// ��ȫ����
		ER_Friend,		// ���ѿɼ�
		ER_Close,		// ��ȫ����
	};
	PersonalInfo()
	{ 
		memset( this, 0, sizeof(*this)); 
		uchMonth	= 1;
		uchDay		= 1;
	}

	unsigned char GetPersonalSex() const { return uchSex; }
	unsigned char GetPersonalAge() const { return uchAge; }
	unsigned char GetPersonalMonth() const { return uchMonth; }
	unsigned char GetPersonalDay() const { return uchDay; }
	unsigned char GetShengXiao() const { return uchShengXiao; }
	unsigned char GetStar() const { return uchStar; }
	unsigned char GetPersonalRight() const { return uchRight; }
	const char * GetProvince() const { return szProvince; }
	const char * GetCity() const { return szCity; }
	const char * GetProfession() const { return szProfession; }
	const char * GetQQ() const { return szQQ; }
	const char * GetMSN() const { return szMSN; }
	const char * GetIntroduction() const { return szIntroduction; }
	
	void SetPersonalSex( unsigned char uchValue ) { uchSex = uchValue; }
	void SetPersonalAge( unsigned char uchValue ) { uchAge = uchValue; }
	void SetPersonalMonth( unsigned char uchValue ) { uchMonth = uchValue; }
	void SetPersonalDay( unsigned char uchValue ) { uchDay = uchValue; }
	void SetStar( unsigned char uchValue ) { uchStar = uchValue; }
	void SetShengXiao( unsigned char uchValue ) { uchShengXiao = uchValue; }
	void SetPersonalRight( unsigned char uchValue ) { uchRight = uchValue; }
	void SetProvince( const char * szValue ) { strncpy_s( szProvince, sizeof( szProvince ), szValue, sizeof( szProvince ) - 1 ); }
	void SetCity( const char * szValue ) { strncpy_s( szCity, sizeof( szCity ), szValue, sizeof( szCity ) - 1 ); }
	void SetProfession( const char * szValue ) { strncpy_s( szProfession, sizeof( szProfession ), szValue, sizeof( szProfession ) - 1 ); }
	void SetQQ( const char * szValue ) { strncpy_s( szQQ, sizeof( szQQ ), szValue, sizeof( szQQ ) - 1 ); }
	void SetMSN( const char * szValue ) { strncpy_s( szMSN, sizeof( szMSN ), szValue, sizeof( szMSN ) - 1 ); }
	void SetIntroduction( const char * szValue ) { strncpy_s( szIntroduction, sizeof( szIntroduction ), szValue, sizeof( szIntroduction ) - 1 ); }

	void SetInfo( const PersonalInfo& personInfo )
	{
		SetPersonalSex( personInfo.GetPersonalSex() );
		SetPersonalAge( personInfo.GetPersonalAge() );
		SetPersonalMonth( personInfo.GetPersonalMonth() );
		SetPersonalDay( personInfo.GetPersonalDay() );
		SetStar( personInfo.GetStar() );
		SetShengXiao( personInfo.GetShengXiao() );
		SetPersonalRight( personInfo.GetPersonalRight() );
		SetProvince( personInfo.GetProvince() );
		SetCity( personInfo.GetCity() );
		SetProfession( personInfo.GetProfession() );
		SetQQ( personInfo.GetQQ() );
		SetMSN( personInfo.GetMSN() );
		SetIntroduction( personInfo.GetIntroduction() );
	}

	unsigned char	uchSex;				// �Ա� ESexType
	unsigned char	uchAge;				// ����
	unsigned char	uchMonth;			// ���� ��
	unsigned char	uchDay;				// ���� ��
	unsigned char	uchStar;			// ����
	unsigned char	uchShengXiao;		// ��Ф
	unsigned char	uchRight;			// Ȩ��
	char	szProvince[RelationDefine::ProvinceLength];			// ʡ��
	char	szCity[RelationDefine::CityLength];					// ����
	char	szProfession[RelationDefine::ProfessionLength];		// ְҵ
	char	szQQ[RelationDefine::QQLength];						// QQ
	char	szMSN[RelationDefine::MSNLength];					// MSN
	char	szIntroduction[RelationDefine::IntructionLength];	// ����˵��
};

// ��ϵ����������
class RelationAttribute
{
public:
    RelationAttribute() : uchCountry( 0 ), nGuildID( 0 ), uchPosition( 0 ), ustLevel( 0 ), nTitleID(0), bOnLine( false )
    {
        memset( szName, 0, sizeof( szName ) );
        memset( szSignature, 0, sizeof( szSignature ) );
        memset( szIp, 0, sizeof( szIp ) );
    }

    unsigned int   GetID() const { return dwDBID; }
    const char*    GetName() const { return szName; }
    unsigned short GetHeadPic() const { return uchHeadPic; }
    unsigned char  GetCountry() const { return uchCountry; }
    unsigned char  GetProfession() const { return uchProfession; }
    unsigned char  GetSex() const { return uchSex; }
    unsigned short GetLevel() const { return ustLevel; }
    unsigned int   GetGuildID() const { return nGuildID; }
    unsigned char  GetPosition() const { return uchPosition; }
    unsigned char  GetMasterLevel() const { return uchMasterLevel; }    
    const char*    GetSignature() const { return szSignature; } 
    const char*    GetIp() const { return szIp; } 
    unsigned short GetTitleID() const { return nTitleID; }
    unsigned int   GetMapID()   const { return nMapID; }
    bool           GetOnLine()  const { return bOnLine; }
	PersonalInfo&  GetPersonalInfo() { return xPersonalInfo; }
	unsigned int   GetFamilyID() const { return nFamilyID; }

    void SetID( unsigned int nValue ) { dwDBID = nValue; }
    void SetName( const char* szValue ) { strncpy_s( szName, sizeof( szName ), szValue, sizeof( szName ) - 1 ); }
    void SetHeadPic( unsigned short ustValue ) { uchHeadPic = ustValue; }
    void SetCountry( unsigned char uchValue ) { uchCountry = uchValue; }
    void SetProfession( unsigned char uchValue ) { uchProfession = uchValue; }
    void SetSex( unsigned char uchValue ) { uchSex = uchValue; }
    void SetLevel( unsigned short ustValue ) { ustLevel = ustValue; }
    void SetGuildID( unsigned int nValue ) { nGuildID = nValue; }
    void SetPosition( unsigned char uchValue ) { uchPosition = uchValue; }
    void SetMasterLevel( unsigned char uchValue ) { uchMasterLevel = uchValue; }
    void SetTitleID( unsigned short ustValue ) { nTitleID = ustValue; }
    void SetSignature( const char* szValue ) { strncpy_s( szSignature, sizeof( szSignature ), szValue, sizeof( szSignature ) - 1 ); }
    void SetIp( const char* szValue ) { strncpy_s( szIp, sizeof( szIp ), szValue, sizeof( szIp ) - 1 ); }
    void SetMapID( unsigned int nValue ) { nMapID = nValue; }
    void SetOnLine( bool bValue ) { bOnLine = bValue; }
	void SetFamilyID( unsigned int nValue ) { nFamilyID = nValue; }

    void SetRelationAttribute( RelationAttribute& xAttribute )
    {
        SetID( xAttribute.GetID() );
        SetName( xAttribute.GetName() );
        SetHeadPic( xAttribute.GetHeadPic() );
        SetCountry( xAttribute.GetCountry() );
        SetProfession( xAttribute.GetProfession() );
        SetSex( xAttribute.GetSex() );
        SetLevel( xAttribute.GetLevel() );
        SetGuildID( xAttribute.GetGuildID() );
        SetPosition( xAttribute.GetPosition() );
        SetMasterLevel( xAttribute.GetMasterLevel() );
        SetTitleID( xAttribute.GetTitleID() );
        SetSignature( xAttribute.GetSignature() );
        SetOnLine( xAttribute.GetOnLine() );
        SetIp( xAttribute.GetIp() );
        SetMapID( xAttribute.GetMapID() );
		SetFamilyID( xAttribute.GetFamilyID() );
		xPersonalInfo.SetInfo( xAttribute.xPersonalInfo );
    }

    
protected:
    unsigned int dwDBID;            // ���DBID
    char szName[RelationDefine::MaxNameLength];    // ����
    unsigned short uchHeadPic;      // ͷ��ID
    unsigned char  uchCountry;      // ����
    unsigned char  uchProfession;   // ְҵ
    unsigned char  uchSex;          // �Ա�
    unsigned short ustLevel;        // �ȼ�
    unsigned int   nGuildID;        // ��ǰ���ڵĹ���ID
    unsigned char  uchPosition;     // ����ְλ( ������CountryDefine.h��title��
	unsigned int   nFamilyID;		// ��ǰ���ڵļ���ID
    unsigned char  uchMasterLevel;  // ʦ�������ȼ�
    unsigned short nTitleID;        // �ƺ�
    char szSignature[ RelationDefine::MaxSignLength ];  // ����ǩ��

    bool bOnLine;                   // �Ƿ����� ( ���������� )
    unsigned int   nMapID;          // ��ǰ��ͼ ( ���������� )
    char szIp[RelationDefine::MaxIpLength];         // IP��ַ   ( ���������� )

	// ��������
	PersonalInfo xPersonalInfo;
};

// ��ϵ�Ĺ�ϵ����
class RelationData 
{
public:
	RelationData()
	{
		stRelation = 0;
		nFriendly  = 0;
        bLocked    = false;
        uchGroupID = 0;

        memset( szRemark, 0, sizeof( szRemark ) );
    }

    unsigned short GetRelation() const { return stRelation; }
    unsigned int   GetFriendly() const { return nFriendly; }    
    bool           GetLocked() const   { return bLocked; }
    unsigned char  GetGroupID() const  { return uchGroupID; }
    const char*    GetRemark() const   { return szRemark; }

    void SetRelation( unsigned short stValue ) { stRelation = stValue; }
    void SetFriendly( unsigned int nValue ) { nFriendly = nValue; }
    void SetLocked( bool bValue ) { bLocked = bValue; }
    void SetGroupID( unsigned char uchValue ) { uchGroupID = uchValue; }
    void SetRemark( const char* szValue ) { strncpy_s( szRemark, sizeof( szRemark ), szValue, sizeof( szRemark ) - 1 ); }
    void AddFriendly( unsigned int nValue ) { nFriendly += nValue; }
    void SubFriendly( unsigned int nValue )   // ���ٺ��Ѷ�  
    { 
        if ( nValue > GetFriendly() )
        { nValue = GetFriendly(); }

        nFriendly -= nValue;
    }  

    void AddRelation( unsigned short stValue );                                                     // ���ĳ�ֹ�ϵ
    void RemoveRelation( unsigned short stValue ) { stRelation &= ~stValue; }                       // ɾ��ĳ����ϵ
    bool HaveRelation() const { return ( stRelation & 0xFFFF ) != RelationDefine::InitRelation; }   // �Ƿ���ڹ�ϵ
    bool HaveRelation( unsigned short stValue ) { return (stRelation & stValue) != 0; }             // �Ƿ���ĳ����ϵ
    unsigned short GetHigherRelation() const { return ( stRelation & 0xFFF0 ); }                    // ���2����ϵ
    bool HaveHigherRelation() { return GetHigherRelation() != RelationDefine::InitRelation; }       // �Ƿ���2����ϵ

    static bool HaveRelation( unsigned short stValue, unsigned short stRelation ) { return ( stValue & stRelation ) != 0; } // stValue��ϵ���Ƿ����stRelaiton��ϵ
    static bool IsHigherRelation( unsigned short stRelation ); // �жϴ˹�ϵ�Ƿ���2����ϵ

    void InitRelationData( RelationData& xData )
    {
        SetRelation( xData.GetRelation() );
        SetFriendly( xData.GetFriendly() );
        SetGroupID( xData.GetGroupID() );
        SetLocked( xData.GetLocked() );
        SetRemark( xData.GetRemark() );
    }
    
protected:
    unsigned short stRelation;                     // ��ϵ
    unsigned int nFriendly;                        // ���Ѷ�
    bool bLocked;                                  // �Ƿ����������
    unsigned char uchGroupID;                      // ���ѷ���ID ( 0 ����Ĭ�Ϸ��� )
    char szRemark[ RelationDefine::ReMarkLength ]; // ���ѱ�ע
};

inline void RelationData::AddRelation( unsigned short stValue )
{
    RemoveRelation( RelationDefine::TempFriend );   // ���������ʱ��ϵ

    switch ( stValue )
    {
    case RelationDefine::Master:       // ��ʦ���ʦ��
        RemoveRelation( RelationDefine::Teacher );
        break;
    case RelationDefine::Prentice:     // ��ʦ���ͽ��
        RemoveRelation( RelationDefine::Student );
        break;
    case RelationDefine::Friend:        // ����
        RemoveRelation( RelationDefine::BlackList );
		RemoveRelation( RelationDefine::Vendetta );
        break;
    case RelationDefine::BlackList:     // ������
        RemoveRelation( RelationDefine::Friend );
	case RelationDefine::Vendetta:		// ����
		RemoveRelation( RelationDefine::Friend );
        break;
    default:
        break;
    }
    
    stRelation |= stValue;
}

inline bool RelationData::IsHigherRelation( unsigned short stRelation )
{
    switch ( stRelation )
    {
        case RelationDefine::Marriage:
        case RelationDefine::Brother:
        case RelationDefine::Teacher:
        case RelationDefine::Student:
            return true;
        default:
            break;
    }

    return false;
}

// ���͸��ͻ��˵���Ϣ
class RelationDataToClient : public RelationAttribute, public RelationData
{
public:
    RelationDataToClient() : RelationData(), RelationAttribute()
    {
    }
};


// ����˽ṹ����
class RelationDataToServer : public RelationData
{
public:
    RelationDataToServer() : RelationData() {}

    unsigned int GetID() const { return dwDBID; }
    void SetID( unsigned int nValue ) { dwDBID = nValue; }

protected:
    unsigned int dwDBID;
};

// ���ݿ���Ϣ�ṹ����
class RelationDataToDatabase
{
public:
    unsigned int nPlayerID;
    RelationDataToServer xDataToServer;
};

class RelationGroup
{
public:
    RelationGroup()
    {
        memset( szName, 0, sizeof( szName ) );
    }
    
    const char* GetName() const { return szName; }
    void SetName( const char* szValue ) { strncpy_s( szName, sizeof( szName ), szValue, sizeof( szName ) - 1 ); }
    
    bool IsEmpty() const { return szName[0] == 0; }
    void ClearGroup() { memset( szName, 0, sizeof( szName ) ); }

protected:
    char szName[ RelationDefine::GroupLength ];
};

// ���ݿ���Ϣ�ṹ����
class RelationAttributeToServer : public RelationAttribute
{
public:
    RelationAttributeToServer() : RelationAttribute(), ustMessageRefuse( 0 ), nRewardExp( 0 ), nRewardPrestige( 0 ), n64LastAddStudentTime( 0 ), n64LastAddTeacherTime( 0 )
    {
    }

    unsigned short GetMessageRefuse() const { return ustMessageRefuse; }
    unsigned int GetRewardExp() const { return nRewardExp; }
    unsigned int GetRewardPrestige() const { return nRewardPrestige; }
    __int64 GetLastAddStudentTime() const { return n64LastAddStudentTime; }
    __int64 GetLastAddTeacherTime() const { return n64LastAddTeacherTime; }	
	
    void SetMessageRefuse( unsigned short ustValue ) { ustMessageRefuse = ustValue; }
    void SetRewardExp( unsigned int nValue ) { nRewardExp = nValue; }
    void SetRewardPrestige( unsigned int nValue ) { nRewardPrestige = nValue; }
    void SetLastAddStudentTime( __int64 n64Value ) { n64LastAddStudentTime = n64Value; }
    void SetLastAddTeacherTime( __int64 n64Value ) { n64LastAddTeacherTime = n64Value; }
	    
    const char* GetGroupName( unsigned int uchGroupID )
    {
        if ( uchGroupID >= RelationDefine::GroupCount )
        { return ""; }

        return xGroup[uchGroupID].GetName();
    }

    void SetGroupName( unsigned int uchGroupID, const char* szValue )
    {
        if ( uchGroupID >= RelationDefine::GroupCount )
        { return; }

        xGroup[uchGroupID].SetName( szValue );
    }

    bool IsEmptyGroup( unsigned char uchGroupID )
    {
        if ( uchGroupID >= RelationDefine::GroupCount )
        { return true; }

        return xGroup[ uchGroupID ].IsEmpty();
    }
	// ��RelationAttributeToServer��ʼ�������ϵ��Ϣ��
    void SetRelationAttributeToServer( RelationAttributeToServer& xAttribute )
    {
        SetRelationAttribute( xAttribute );

        SetMessageRefuse( xAttribute.GetMessageRefuse() );
        SetRewardExp( xAttribute.GetRewardExp() );
        SetRewardPrestige( xAttribute.GetRewardPrestige() );
        SetLastAddStudentTime( xAttribute.GetLastAddStudentTime() );
        SetLastAddTeacherTime( xAttribute.GetLastAddTeacherTime() );
        memcpy_s( xGroup, sizeof( xGroup ), xAttribute.xGroup, sizeof( xAttribute.xGroup ) );
    }

protected:
    unsigned short ustMessageRefuse;      // �ܾ�������Ϣ����
    unsigned int nRewardExp;              // ͽ��, �Լ�ͽ�ܵ�ͽ������, �����ľ��� ( ������ʱ, �������ݿ� )
    unsigned int nRewardPrestige;         // ͽ��, �Լ�ͽ�ܵ�ͽ������, ���������� ( ������ʱ, �������ݿ� ) 
    __int64 n64LastAddStudentTime;        // ���һ����ͽ�ܵ�ʱ��
    __int64 n64LastAddTeacherTime;        // ���һ�ΰ�ʦ����ʱ��
    RelationGroup xGroup[ RelationDefine::GroupCount ]; // ���ѵķ�����Ϣ
};

#endif