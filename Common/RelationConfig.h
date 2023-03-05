#ifndef __FRIENDLYCONFIG_H__
#define __FRIENDLYCONFIG_H__

#include <vector>
#include <map>

// 好友等级属性
class LevelInfo
{
public:
    LevelInfo() : m_nFriendly( 0 ), m_nStringID( 0 ) {}
    void SetFriendly( unsigned int ustValue ) { m_nFriendly = ustValue; }
    void SetStringID( unsigned int nValue ) { m_nStringID = nValue; }

    unsigned int GetFriendly() const { return m_nFriendly; }
    unsigned int GetStringID() const { return m_nStringID; }

private:
    unsigned int m_nFriendly;		// 好友度
    unsigned  int m_nStringID;      // 好友度对应的显示字串ID
};

// 队伍间buffer
class TeamBuffer
{
public:
    TeamBuffer() : m_nBufferID( 0 ), m_uchLevel( 0 ){}

    void Clear()
    {
        m_nBufferID = 0;
        m_uchLevel  = 0;
    }

    bool IsEmpty() { return m_nBufferID == 0 || m_uchLevel == 0; }

    void SetBufferID( unsigned int nValue ) { m_nBufferID = nValue; }
    void SetBufferLevel( unsigned char uchLevel ) { m_uchLevel = uchLevel; }

    unsigned int GetBufferID() const { return m_nBufferID; }
    unsigned char GetBufferLevel() const { return m_uchLevel; }

private:
    unsigned int m_nBufferID;
    unsigned char m_uchLevel;
};

// 小队技能
class TeamSkill
{
public:
    TeamSkill() : m_nSkillID( 0 ), m_uchLevel( 0 ){}

    void Clear()
    {
        m_nSkillID = 0;
        m_uchLevel = 0;
    }

    bool IsEmpty() { return m_nSkillID == 0 || m_uchLevel == 0; }

    void SetSkillID( unsigned int nValue ) { m_nSkillID = nValue; }
    void SetSkillLevel( unsigned char uchLevel ) { m_uchLevel = uchLevel; }

    unsigned int GetSkillID() const { return m_nSkillID; }
    unsigned char GetSkillLevel() const { return m_uchLevel; }

private:
    unsigned int m_nSkillID;
    unsigned char m_uchLevel;
};

// 师门配置
class MasterInfo
{
public:
    unsigned short GetRecruitCount() const { return m_ustRecruitCount; }
    unsigned int GetNeedMasterValue() const { return m_dwNeedMasterValue; }
    unsigned int GetMaxMasterValue() const { return m_dwMaxMasterValue; }
    unsigned int GetMasterTitleID() const { return m_ustTitleID; } 
                                                                   
    void SetRecruitCount( unsigned short ustValue )  { m_ustRecruitCount = ustValue; }
    void SetNeedMasterValue( unsigned int dwValue )  { m_dwNeedMasterValue = dwValue; }
    void SetMaxMasterValue( unsigned int dwValue )   { m_dwMaxMasterValue = dwValue; }
    void SetMasterTitleID( unsigned short ustValue ) { m_ustTitleID = ustValue; }
private:
    unsigned short m_ustRecruitCount;       // 招收徒弟最大数量
    unsigned int m_dwNeedMasterValue;       // 需要多少威望值
    unsigned int m_dwMaxMasterValue;        // 可以最大的声望值
    unsigned short m_ustTitleID;            // 对应的TitleID
};

class ReportInfo
{
public:
    unsigned int GetMasterValue() const { return m_dwMasterValue; }
    unsigned int GetExpValue() const { return m_dwExpValue; }
    unsigned int GetModulusValue() const { return m_nModulusValue; }

    void SetMasterValue( unsigned int dwValue ) { m_dwMasterValue = dwValue; }
    void SetExpValue( unsigned int dwValue ) { m_dwExpValue = dwValue; }
    void SetModulusValue( unsigned int dwValue ) { m_nModulusValue = dwValue; }
private:
    unsigned int m_dwMasterValue;       // 升级添加的威望值系数值
    unsigned int m_dwExpValue;          // 升级添加的经验值系数值
    unsigned int m_nModulusValue;       // 师傅的师傅的比例值
};

class PrenticeLimit
{
public:
    unsigned int GetMinStudentLevel() const { return m_nMinStudentLevel; }
    unsigned int GetMinTeacherLevel() const { return m_nMinTeacherLevel; }
    unsigned int GetMinLevelSpan() const    { return m_nMinLevelSpan; }
    unsigned int GetTeacherTimeSpan() const { return m_nTeacherTimeSpan; }
    unsigned int GetStudentTimeSpan() const { return m_nStudentTimeSpan; }

    void SetMinStudentLevel( unsigned int nValue ) { m_nMinStudentLevel = nValue; }
    void SetMinTeacherLevel( unsigned int nValue ) { m_nMinTeacherLevel = nValue; }
    void SetMinLevelSpan( unsigned int nValue ) { m_nMinLevelSpan = nValue; }
    void SetTeacherTimeSpan( unsigned int nValue ) { m_nTeacherTimeSpan = nValue; }
    void SetStudentTimeSpan( unsigned int nValue ) { m_nStudentTimeSpan = nValue; }

private:
    unsigned int m_nMinStudentLevel;
    unsigned int m_nMinTeacherLevel;
    unsigned int m_nMinLevelSpan;
    unsigned int m_nTeacherTimeSpan;        // 单位 : 小时
    unsigned int m_nStudentTimeSpan;        // 单位 : 小时
};

class RelationConfig
{
public:
    // 小队技能
    typedef std::vector< TeamSkill > TeamSkillVector;
    typedef TeamSkillVector::iterator TeamSkillVectorIter;
    typedef TeamSkillVector::const_iterator TeamSkillVectorConstIter;

    class StudentExpModulus
    {
    public:
        StudentExpModulus() : m_nLevelDistance( 10 ), m_fNoTeamModulus( 0.5f ), m_fHaveTeamModulus( 1.0f )
        {

        }

        int GetLevelDistance() const { return m_nLevelDistance; }
        float GetNoTeamModulus() const { return m_fNoTeamModulus; }
        float GetHaveTeamModulus() const { return m_fHaveTeamModulus; }

        void SetLevelDistance( int nValue ) { m_nLevelDistance = nValue; }
        void SetNoTeamModulus( float fValue ) { m_fNoTeamModulus = fValue; }
        void SetHaveTeamModulus( float fValue ) { m_fHaveTeamModulus = fValue; }
    private:
        int m_nLevelDistance;			// 等级差
        float m_fNoTeamModulus;         // 没队伍经验加成
        float m_fHaveTeamModulus;       // 有队伍经验加成
    };

protected:
    // 好友等级定义
    typedef std::vector< LevelInfo > LevelInfoVector;
    typedef LevelInfoVector::iterator LevelInfoVectorIter;
    typedef LevelInfoVector::const_iterator LevelInfoVectorConstIter;
    typedef LevelInfoVector::const_reverse_iterator LevelInfoVectorConstRIter;

    // 附加的额外值
    typedef std::vector< unsigned int > ExtendFriendlyVector;
    typedef ExtendFriendlyVector::iterator ExtendFriendlyVectorIter;
    typedef ExtendFriendlyVector::const_iterator ExtendFriendlyVectorConstIter;

    // 附加的buffer
    typedef std::vector< TeamBuffer > ProfessionBufferVector;
    typedef ProfessionBufferVector::iterator ProfessionBufferVectorIter;
    typedef ProfessionBufferVector::const_iterator ProfessionBufferVectorConstIter;

    typedef std::vector< ProfessionBufferVector > TeamBufferVector;
    typedef TeamBufferVector::iterator TeamBufferVectorIter;
    typedef TeamBufferVector::const_iterator TeamBufferVectorConstIter;

    typedef std::vector< TeamSkillVector > ProfessionSkillVector;
    typedef ProfessionSkillVector::iterator ProfessionSkillVectorIter;
    typedef ProfessionSkillVector::const_iterator ProfessionSkillVectorConstIter;

    typedef std::vector< ProfessionSkillVector > FriendlyTeamSkillVector;
    typedef FriendlyTeamSkillVector::iterator FriendlyTeamSkillVectorIter;
    typedef FriendlyTeamSkillVector::const_iterator FriendlyTeamSkillVectorConstIter;

    typedef std::vector< MasterInfo > MasterInfoVector;
    typedef MasterInfoVector::iterator MasterInfoVectorIter;
    typedef MasterInfoVector::const_iterator MasterInfoVectorConst;


    RelationConfig() : m_nMaxFriendly( 0 ), m_uchMaxFriendLevel( 0 ), m_nMaxTempFriendCount( 100 ), m_nMaxFriendCount( 100 ), m_nMaxBlackListCout( 50 ), m_nMaxVendettaCount( 50 ), m_dwMarriageFriendly( 1000 ),
        m_ustMarriageMaleLevel( 35 ), m_ustMarriageFemaleLevel( 28 ), m_ustKillSubFriendly( 100 )
    {
        m_vecLevelInfo.clear();
        m_vecTeamBuffer.clear();
        m_vecTeamSkill.clear();
        m_vecExtendFriendly.clear();
        m_vecMasterInfo.clear();
		m_vecGuildBuffer.clear();
    }

    void SetMaxFriendly( unsigned int nValue ) { m_nMaxFriendly = nValue; }
    void SetMaxFriendLevel( unsigned char uchValue ) { m_uchMaxFriendLevel = uchValue; }

    bool AddFriendInfo( unsigned char uchLevel, const LevelInfo& xData )
    {
        if ( uchLevel >= m_vecLevelInfo.size() )
        { return false; }

        m_vecLevelInfo[ uchLevel ] = xData;
        return true;
    }

    bool AddTeamBuffer( unsigned short ustTeamCount, const TeamBuffer& xData )
    {
        if ( ustTeamCount >= m_vecTeamBuffer.size() )
        { return false; }

        m_vecTeamBuffer[ ustTeamCount ].push_back( xData );

        return true;
    }

    bool AddFriendBuffer( unsigned char uchLevel, const TeamBuffer& xData )
    {
        if ( uchLevel >= m_vecFriendBuffer.size() )
        { return false; }

        m_vecFriendBuffer[ uchLevel ].push_back( xData );

        return true;
    }

	bool AddGuildBuffer( unsigned char uchLevel, const TeamBuffer& xData )
	{
		if ( uchLevel >= m_vecGuildBuffer.size() )
		{ return false; }

		m_vecGuildBuffer[ uchLevel ].push_back( xData );

		return true;
	}
    
    bool AddTeamSkill( unsigned char uchFriendLevel, unsigned char uchProfession, const TeamSkill& xData )
    {
        if ( uchFriendLevel >= m_vecTeamSkill.size() )
        { return false; }

        ProfessionSkillVector& vecProfessionSkill = m_vecTeamSkill.at( uchFriendLevel );

        if ( uchProfession >= vecProfessionSkill.size() )
        {
            TeamSkillVector vecSkill;
            vecSkill.push_back( xData );

            vecProfessionSkill.push_back( vecSkill );
        }
        else
        {
            TeamSkillVector& vecSkill = vecProfessionSkill.at( uchProfession );
            vecSkill.push_back( xData );
        }

        return true;
    }

    bool AddMasterInfo( unsigned char uchLevel, const MasterInfo& xInfo )
    {
        if ( uchLevel >= m_vecMasterInfo.size() )
        { return false; }

        m_vecMasterInfo[ uchLevel ] = xInfo;

        return true;
    }
public:
    static RelationConfig& Instance()
    {
        static RelationConfig s_xConfig;
        return s_xConfig;
    }

    unsigned int GetMaxFriendly() const { return m_nMaxFriendly; }
    unsigned char GetMaxFriendLevel() const { return m_uchMaxFriendLevel; }

    const LevelInfo* GetLevelInfo( unsigned char uchLevel ) const
    {
        if ( uchLevel >= m_vecLevelInfo.size() )
        { return NULL; }

        return &( m_vecLevelInfo.at( uchLevel ) ); 
    }

    // 通过好友度获得当前好友等级
    const unsigned char GetFriendLevel( unsigned int nFriendly ) const
    {
        unsigned char uchLevel = 1;
        for ( LevelInfoVectorConstRIter iter = m_vecLevelInfo.rbegin(); iter != m_vecLevelInfo.rend(); ++iter )
        {
            if ( nFriendly >= iter->GetFriendly() )
            {
                uchLevel = static_cast< unsigned char >( distance( m_vecLevelInfo.begin(), iter.base() ) ) - 1;
                break;
            }
        }

        return ( uchLevel == 0 ? 1 : uchLevel );
    }

    const unsigned int GetExtendFriendly( unsigned char uchType ) const
    {
        if ( uchType >= m_vecExtendFriendly.size() )
        { return NULL; }

        return m_vecExtendFriendly.at( uchType );
    }

    const TeamBuffer* GetTeamBuffer( unsigned short ustTeamCount, unsigned char uchProfession ) const
    {
        if ( ustTeamCount >= m_vecTeamBuffer.size() )
        { return NULL; }

        const ProfessionBufferVector& vecProfession = m_vecTeamBuffer.at( ustTeamCount );

        if ( uchProfession >= vecProfession.size() )
        { return NULL; }

        return &( vecProfession.at( uchProfession ) );
    }

    const TeamBuffer* GetFriendBuffer( unsigned char uchLevel, unsigned char uchProfession ) const
    {
        if ( uchLevel >= m_vecFriendBuffer.size() )
        { return NULL; }

        const ProfessionBufferVector& vecProfession = m_vecFriendBuffer.at( uchLevel );

        if ( uchProfession >= vecProfession.size() )
        { return NULL; }

        return &( vecProfession.at( uchProfession ) );
    }

	const TeamBuffer* GetGuildBuffer( unsigned char uchLevel, unsigned char uchProfession ) const
	{
		if ( uchLevel >= m_vecGuildBuffer.size() )
		{ return NULL; }

		const ProfessionBufferVector& vecProfession = m_vecGuildBuffer.at( uchLevel );

		if ( uchProfession >= vecProfession.size() )
		{ return NULL; }

		return &( vecProfession.at( uchProfession ) );
	}

    const TeamSkillVector* GetTeamSkill( unsigned char uchFriendLevel, unsigned char uchProfession ) const
    {
        if ( uchFriendLevel >= m_vecTeamSkill.size() )
        { return NULL; }
    
        const ProfessionSkillVector& vecProfessionSkill = m_vecTeamSkill.at( uchFriendLevel );

        if ( uchProfession >= vecProfessionSkill.size() )
        { return NULL; }

        return &( vecProfessionSkill.at( uchProfession ) );
    }

    const unsigned short GetMaxTempFriendCount() const { return m_nMaxTempFriendCount; }
    const unsigned short GetMaxFriendCount() const { return m_nMaxFriendCount; }
    const unsigned short GetMaxBlackListCount() const { return m_nMaxBlackListCout; }
    const unsigned short GetMaxVendettaCount() const { return m_nMaxVendettaCount; }
    const MasterInfo* GetMasterInfo( unsigned char uchLevel ) const
    {
        if ( uchLevel >= m_vecMasterInfo.size() )
        { return NULL; }

        return &( m_vecMasterInfo.at( uchLevel ) );
    }

    const unsigned int GetUpdateFriendlyTimeSpan() const { return m_dwUpdateFriendlySpan; }
    const unsigned short GetUpdateFriendlyValue() const { return m_ustAddFriendly; }

    const unsigned short GetMarriageFriendly() const { return m_dwMarriageFriendly; }
    const unsigned short GetMarriageMaleLevel() const{ return m_ustMarriageMaleLevel; }
    const unsigned short GetMarriageFemaleLevel() const { return m_ustMarriageFemaleLevel; }
    const unsigned short GetMaxMasterLevel() const { return m_nMaxMasterLevel; }

    const unsigned int GetRemoveMasterCostMoney() const { return m_dwRemoveMasterCostMoney; }
    const unsigned int GetRemovePrenticeCostMoney() const { return m_dwRemovePrenticeCostMoney; }

    const PrenticeLimit& GetPrenticeLimit() const { return m_xPrenticeLimit; }
    const ReportInfo& GetReportInfo() const { return m_xReportInfo; }

    const StudentExpModulus& GetStudentExpModulus() const { return m_xStudentExpModulus; }

    unsigned short GetKillSubFriendly() const { return m_ustKillSubFriendly; }

    bool LoadRelationConfig( const char* szFile );

private:

    unsigned int m_nMaxFriendly;        // 最大的好友度
    unsigned char m_uchMaxFriendLevel;  // 最大的好友等级(根据好友度)
	LevelInfoVector m_vecLevelInfo;       // 好友等级信息

    ExtendFriendlyVector m_vecExtendFriendly;   // 附加的好友度 ***被注释了
    
    TeamBufferVector m_vecTeamBuffer;		// 组队附加的buffer信息
    TeamBufferVector m_vecFriendBuffer;		// 队伍关系好友Buffer信息
	TeamBufferVector m_vecGuildBuffer;		// 队伍军团buffer

    FriendlyTeamSkillVector m_vecTeamSkill;       // 小队技能  画蛇添足了 将来要废掉



    // 数量限制
    unsigned short m_nMaxTempFriendCount;		// 临时好友数量
    unsigned short m_nMaxFriendCount;			// 最大好友数量
    unsigned short m_nMaxBlackListCout;			// 黑名单最大数量
    unsigned short m_nMaxVendettaCount;			// 仇人最大个数

	//<!--Level( 师门等级 ) NeedMasterValue( 需要的威望值 ) MaxMasterValue( 最大威望值上限 ) RecruitCount( 接受徒弟的个数 TitleID( 对应的称号ID)-->
    MasterInfoVector m_vecMasterInfo;			// 每个阶段的信息
    unsigned short m_nMaxMasterLevel;			// 师门最大的等级(阶段数)

    unsigned int m_dwUpdateFriendlySpan;		// 添加好友度时间间隔(ms)
    unsigned short m_ustAddFriendly;			// 每次添加多少好友度
    unsigned short m_ustKillSubFriendly;		// 杀死好友减少多少好友度

    unsigned int m_dwMarriageFriendly;			// 结婚所需好友度值
    unsigned short m_ustMarriageMaleLevel;      // 男性结婚的最小等级
    unsigned short m_ustMarriageFemaleLevel;    // 女性结婚的最小等级

    unsigned int m_dwRemoveMasterCostMoney;     // 叛离师门 扣钱N
    unsigned int m_dwRemovePrenticeCostMoney;	// 逐出师门 扣钱N

	// 徒弟升级, 师傅获得的师门威望系数和经验系数 这个系数的因数是徒弟的等级
    ReportInfo m_xReportInfo;					// 徒弟升级 师傅获得什么

	//StudentMinLevel( 徒弟最小等级 ) TeacherMinLevel( 师傅最小等级 ) MinLevelSpan( 师徒最小等级差 ) 
	//TeacherTimeSpan( 收徒弟时间间隔 : 小时/次 ) StudentTimeSpan( 拜师时间限制 : 小时/次)
    PrenticeLimit m_xPrenticeLimit;				// 拜师的一些限制
    
	// 徒弟经验加成: LevelDistance(师徒等级差 **没用) NoTeamModulus（无组队倍率）HaveTeamModulus（有组队经验倍率）
    StudentExpModulus m_xStudentExpModulus;		// 师徒经验加成
};


#define theRelationConfig RelationConfig::Instance()

#endif