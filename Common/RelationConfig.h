#ifndef __FRIENDLYCONFIG_H__
#define __FRIENDLYCONFIG_H__

#include <vector>
#include <map>

// ���ѵȼ�����
class LevelInfo
{
public:
    LevelInfo() : m_nFriendly( 0 ), m_nStringID( 0 ) {}
    void SetFriendly( unsigned int ustValue ) { m_nFriendly = ustValue; }
    void SetStringID( unsigned int nValue ) { m_nStringID = nValue; }

    unsigned int GetFriendly() const { return m_nFriendly; }
    unsigned int GetStringID() const { return m_nStringID; }

private:
    unsigned int m_nFriendly;		// ���Ѷ�
    unsigned  int m_nStringID;      // ���Ѷȶ�Ӧ����ʾ�ִ�ID
};

// �����buffer
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

// С�Ӽ���
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

// ʦ������
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
    unsigned short m_ustRecruitCount;       // ����ͽ���������
    unsigned int m_dwNeedMasterValue;       // ��Ҫ��������ֵ
    unsigned int m_dwMaxMasterValue;        // ������������ֵ
    unsigned short m_ustTitleID;            // ��Ӧ��TitleID
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
    unsigned int m_dwMasterValue;       // ������ӵ�����ֵϵ��ֵ
    unsigned int m_dwExpValue;          // ������ӵľ���ֵϵ��ֵ
    unsigned int m_nModulusValue;       // ʦ����ʦ���ı���ֵ
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
    unsigned int m_nTeacherTimeSpan;        // ��λ : Сʱ
    unsigned int m_nStudentTimeSpan;        // ��λ : Сʱ
};

class RelationConfig
{
public:
    // С�Ӽ���
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
        int m_nLevelDistance;			// �ȼ���
        float m_fNoTeamModulus;         // û���龭��ӳ�
        float m_fHaveTeamModulus;       // �ж��龭��ӳ�
    };

protected:
    // ���ѵȼ�����
    typedef std::vector< LevelInfo > LevelInfoVector;
    typedef LevelInfoVector::iterator LevelInfoVectorIter;
    typedef LevelInfoVector::const_iterator LevelInfoVectorConstIter;
    typedef LevelInfoVector::const_reverse_iterator LevelInfoVectorConstRIter;

    // ���ӵĶ���ֵ
    typedef std::vector< unsigned int > ExtendFriendlyVector;
    typedef ExtendFriendlyVector::iterator ExtendFriendlyVectorIter;
    typedef ExtendFriendlyVector::const_iterator ExtendFriendlyVectorConstIter;

    // ���ӵ�buffer
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

    // ͨ�����ѶȻ�õ�ǰ���ѵȼ�
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

    unsigned int m_nMaxFriendly;        // ���ĺ��Ѷ�
    unsigned char m_uchMaxFriendLevel;  // ���ĺ��ѵȼ�(���ݺ��Ѷ�)
	LevelInfoVector m_vecLevelInfo;       // ���ѵȼ���Ϣ

    ExtendFriendlyVector m_vecExtendFriendly;   // ���ӵĺ��Ѷ� ***��ע����
    
    TeamBufferVector m_vecTeamBuffer;		// ��Ӹ��ӵ�buffer��Ϣ
    TeamBufferVector m_vecFriendBuffer;		// �����ϵ����Buffer��Ϣ
	TeamBufferVector m_vecGuildBuffer;		// �������buffer

    FriendlyTeamSkillVector m_vecTeamSkill;       // С�Ӽ���  ���������� ����Ҫ�ϵ�



    // ��������
    unsigned short m_nMaxTempFriendCount;		// ��ʱ��������
    unsigned short m_nMaxFriendCount;			// ����������
    unsigned short m_nMaxBlackListCout;			// �������������
    unsigned short m_nMaxVendettaCount;			// ����������

	//<!--Level( ʦ�ŵȼ� ) NeedMasterValue( ��Ҫ������ֵ ) MaxMasterValue( �������ֵ���� ) RecruitCount( ����ͽ�ܵĸ��� TitleID( ��Ӧ�ĳƺ�ID)-->
    MasterInfoVector m_vecMasterInfo;			// ÿ���׶ε���Ϣ
    unsigned short m_nMaxMasterLevel;			// ʦ�����ĵȼ�(�׶���)

    unsigned int m_dwUpdateFriendlySpan;		// ��Ӻ��Ѷ�ʱ����(ms)
    unsigned short m_ustAddFriendly;			// ÿ����Ӷ��ٺ��Ѷ�
    unsigned short m_ustKillSubFriendly;		// ɱ�����Ѽ��ٶ��ٺ��Ѷ�

    unsigned int m_dwMarriageFriendly;			// ���������Ѷ�ֵ
    unsigned short m_ustMarriageMaleLevel;      // ���Խ�����С�ȼ�
    unsigned short m_ustMarriageFemaleLevel;    // Ů�Խ�����С�ȼ�

    unsigned int m_dwRemoveMasterCostMoney;     // ����ʦ�� ��ǮN
    unsigned int m_dwRemovePrenticeCostMoney;	// ���ʦ�� ��ǮN

	// ͽ������, ʦ����õ�ʦ������ϵ���;���ϵ�� ���ϵ����������ͽ�ܵĵȼ�
    ReportInfo m_xReportInfo;					// ͽ������ ʦ�����ʲô

	//StudentMinLevel( ͽ����С�ȼ� ) TeacherMinLevel( ʦ����С�ȼ� ) MinLevelSpan( ʦͽ��С�ȼ��� ) 
	//TeacherTimeSpan( ��ͽ��ʱ���� : Сʱ/�� ) StudentTimeSpan( ��ʦʱ������ : Сʱ/��)
    PrenticeLimit m_xPrenticeLimit;				// ��ʦ��һЩ����
    
	// ͽ�ܾ���ӳ�: LevelDistance(ʦͽ�ȼ��� **û��) NoTeamModulus������ӱ��ʣ�HaveTeamModulus������Ӿ��鱶�ʣ�
    StudentExpModulus m_xStudentExpModulus;		// ʦͽ����ӳ�
};


#define theRelationConfig RelationConfig::Instance()

#endif