#ifndef __CAMPDEFINE_H__
#define __CAMPDEFINE_H__

namespace CampDefine
{
    enum EConstDefine
    {
        // ս������
        BattleTypeNone = 0,
        BattleTypeGuild,     // ��������ս
        BattleTypeKing,      // ��������ս
        BattleTypeDragon,    // ��������ս
        BattleTypeRosefinch, // ��ȸ����ս
		BattleTypeGuildUnion,//��������վ
        BattleTypeMax,       // ���ֵ

        ////////////////////////////////////////////////////////////////////
        // ������Ӫ�����ֿ�, Ϊ���ڲ�ͬ����Ӫս��������
        NoneCamp     = 0,       // ����Ӫ
        BaseCampRed  = 1,       // �����췽��Ӫ
        BaseCampBlue = 2,       // ����������Ӫ

        // ��������ս��Ӫ
        GuildCampRed,       // �췽
        GuildCampBlue,      // ����

        // ��������ս
        KingCampRed,       // �췽
        KingCampBlue,      // ����

        // ��������ս
        DragonCampRed,       // �췽
        DragonCampBlue,      // ����

        // ��ȸ����ս
        RosefinchCampRed,       // �췽
        RosefinchCampBlue,      // ����

		GuildUnionRed,
		GuildUnionBlue,

        ////////////////////////////////////////////////////////////////
        NameLength = 33,            // ������ֳ���
        ReleaseSapceTime = 60000,   // 1���Ӻ�ս������
        UpdateSpaceTime = 5000,     // 5��ˢ��һ��

        DefaultReliveIndex = 0,     // Ĭ��������
        RedReliveIndex = 2,         // �췽�����
        BlueReliveIndex = 3,        // ���������
        ////////////////////////////////////////////////////////////////
        // ս��״̬
        StatusInit = 0,     // ��ʼ״̬
        StatusSignUp,       // ����״̬
        StatusPrepare,      // ׼��״̬
        StatusEnter,        // ����ս��״̬
        StatusFight,        // ս��ս��״̬
        StatusEnd,          // ����״̬
        StatusRelease,      // ս������, �ͷ���Դ( ������ʹ�� )
        ////////////////////////////////////////////////////////////////////
        // �����������
        SignUp_Success = 0,         // �ɹ�
        SignUp_NotSignUpStatus,     // ���Ǳ���ʱ��
        SignUp_MustGuildMaster,     // �����ǰ���
        SignUp_GuildMemberLess,     // ���ɳ�Ա����
        SignUp_AlreadySignUp,       // �Ѿ������� �����ظ�����
        SignUp_CanNotSignUp,        // ��İ��ɲ��ܱ�����ս��
        SignUp_GuildLevelLess,      // ���ɵȼ�����
        SignUp_NotEnoughGuildMoney, // û���㹻�İ��ɽ�Ǯ
        SignUp_GuildStrengthLess,   // ����ʵ������, �޷������ѱ������ɱ���
		SignUp_GuildUnionBattleSumError,//��ǰ���������Ա���
		SignUp_GuildUnionBattleNone,//��ǰս������Ҫ���� ��ʼ�����ֱ�Ӳ���
		SignUp_GuildBattleFull,
        /////////////////////////////////////////////////////////////////////
        // ����ս���������
        Enter_NotEnterStatus = 1,   // ���ǽ���ս���׶�
        Enter_MustSignUpGuild,      // �����Ǳ������ɲ��ܽ���
        Enter_LevelLess,            // �ȼ�����, �޷�����
        Enter_MaxCount,             // ս��������������
		Enter_BattleSumError,		//����ָ��ʤ������
    };

    // ��û�����Ӫ��Ϣ
    static unsigned char GetBaseFightCamp( unsigned char uchFightCamp )
    {
        // �ж���Ӫ( �췽��Ӫ��Ϊ����, ������Ϊż�� )
        if ( uchFightCamp == NoneCamp )
        { return NoneCamp; }

        if ( uchFightCamp % 2 == BaseCampRed )
        { return BaseCampRed; }

        return BaseCampBlue;
    }

    // ��Ӫ���ս������
    static unsigned char GetBattleTypeByCamp( unsigned char uchFightCamp )
    {
        switch ( uchFightCamp )
        {
        case GuildCampRed:
        case GuildCampBlue:
            return BattleTypeGuild;
            break;
        case KingCampRed:
        case KingCampBlue:
            return BattleTypeKing;
            break;
        case DragonCampRed:
        case DragonCampBlue:
            return BattleTypeDragon;
            break;
        case RosefinchCampRed:
        case RosefinchCampBlue:
            return BattleTypeRosefinch;
            break;
		case GuildUnionRed:
		case GuildUnionBlue:
			return BattleTypeGuildUnion;
			break;
        default:
            break;
        }

        return BattleTypeNone;
    }
}

// ս���е���ҵ���Ϣ
class BattlePlayer
{
public:
    BattlePlayer() : m_uchFightCamp( CampDefine::NoneCamp ), m_nResource( 0 ), m_nTotalKillCount( 0 ), m_nTotalDeathCount( 0 ), m_nKeepKillCount ( 0 )
    {
        memset( m_szName, 0 , sizeof( m_szName ) );
    }

    // ��Ӫ
    unsigned char GetFightCamp() const { return m_uchFightCamp; } 
    void SetFightCamp( unsigned char uchValue ) { m_uchFightCamp = uchValue; }

    // ����
    const char* GetName() const { return m_szName; }
    void SetName( const char* szValue ) { strncpy_s( m_szName, sizeof( m_szName ), szValue, sizeof( m_szName ) - 1 ); }

    // ְҵ
    unsigned char GetProfession() const { return m_uchProfession; }
    void SetProfession( unsigned char uchValue ) { m_uchProfession = uchValue; }

    // �ȼ�
    unsigned char GetLevel() const { return m_uchLevel; }
    void SetLevel( unsigned char uchValue ) { m_uchLevel = uchValue; }

    // ����
    unsigned int GetResource() const { return m_nResource; }
    void SetResource( unsigned int nValue ) { m_nResource = nValue; }
    void AddResource( unsigned int nValue ) { m_nResource += nValue; }

    // ɱ������
    unsigned int GetTotalKillCount() const { return m_nTotalKillCount; }
    void SetTotalKillCount( unsigned int nValue ) { m_nTotalKillCount = nValue; }
    void AddTotalKillCount( unsigned int nValue ) { m_nTotalKillCount += nValue; }

    // ��������
    unsigned int GetTotalDeathCount() const { return m_nTotalDeathCount; }
    void SetTotalDeathCount( unsigned int nValue ) { m_nTotalDeathCount = nValue; }
    void AddTotalDeathCount( unsigned int nValue ) { m_nTotalDeathCount += nValue; }

    // ��ǰ��ɱ��
    unsigned int GetKeepKillCount() const { return m_nKeepKillCount; }
    void SetKeepKillCount( unsigned int nValue ) {  m_nKeepKillCount = nValue; }
    void AddKeepKillCount( unsigned int nValue ) { m_nKeepKillCount += nValue; }

    // �ж��Ƿ���Ч��ս�����( ʲô��¼��û��, ������Ч����� )
    bool CheckValid() const { return m_nResource != 0 || m_nTotalDeathCount != 0 || m_nTotalKillCount != 0; }

private:
    // ��Ӫ
    unsigned char m_uchFightCamp;

    // �������
    char m_szName[ CampDefine::NameLength ];

    // ְҵ
    unsigned char m_uchProfession;

    // �ȼ�
    unsigned char m_uchLevel;

    // ��õĻ���
    unsigned int m_nResource;

    // ��ҵ�ɱ������
    unsigned int m_nTotalKillCount;

    // �����������
    unsigned int m_nTotalDeathCount;

    // ��ǰ��ɱ����
    unsigned int m_nKeepKillCount;
};


#endif