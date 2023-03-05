#pragma once
#include <string.h>
namespace GameBattleDefine
{
	enum EConstDefine
    {
		//ս���ĳ�������
		GameBattle_None = 0,
		GameBattle_Red = 1,//�췢
		GameBattle_Blue = 2,//����
		GameBattle_Three = 3,//������ ������ֵ�۲췽 Ŀǰû�� 

		GameBattle_Type_Init = 0,
		GameBattle_Type_GuildGeneral = 1,//����Լս��ս������
		GameBattle_Type_Max,

		GameBattle_Control_UpdateSpace = 5000,//Control�ĸ��¼��


		// ս��״̬
        StatusInit = 0,     // ��ʼ״̬
        StatusSignUp,       // ����״̬
        StatusPrepare,      // ׼��״̬
        StatusEnter,        // ����ս��״̬
        StatusFight,        // ս��ս��״̬
        StatusEnd,          // ����״̬
        StatusRelease,      // ս������, �ͷ���Դ( ������ʹ�� )

		DefaultReliveIndex = 0,     // Ĭ��������
        RedReliveIndex = 2,         // �췽�����
        BlueReliveIndex = 3,        // ���������

		ReleaseSapceTime = 60000,   // 1���Ӻ�ս������
        UpdateSpaceTime = 5000,     // 5��ˢ��һ��
		NameLength = 33,            // ������ֳ���

		Enter_NotEnterStatus = 1,   // ���ǽ���ս���׶�
        Enter_MustSignUpGuild,      // �����Ǳ������ɲ��ܽ���
        Enter_LevelLess,            // �ȼ�����, �޷�����
        Enter_MaxCount,             // ս��������������
		Enter_BattleSumError,		//����ָ��ʤ������

		MaxGameGuildGeneralBattleInfoLength = 256,
		//WaitBattleTime = 10*60,//��λ��
		WaiteAddMsgBattleTime = 30*60,//��λ��
		//CampBattleMaxLastTime  = 4 *60*60,//ս��Լս�����ʱ��
	};
	class BattlePlayer
	{
	public:
		BattlePlayer() : m_uchFight( GameBattle_None ), m_nResource( 0 ), m_nTotalKillCount( 0 ), m_nTotalDeathCount( 0 ), m_nKeepKillCount ( 0 )
		{
			memset( m_szName, 0 , sizeof( m_szName ) );
		}

		// ��Ӫ
		unsigned char GetFight() const { return m_uchFight; } 
		void SetFight( unsigned char uchValue ) { m_uchFight = uchValue; }

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
		unsigned char m_uchFight;

		// �������
		char m_szName[ NameLength ];

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
	struct GuildCampBattle
	{
		unsigned int ID;
		unsigned int MapID;
		unsigned int SrcGuildID;
		unsigned int DestGuildID;
		unsigned int MoneySum;
		unsigned int GuildMoneySum;
		unsigned int GuildMissionSum;
		__int64 BeginTime;
		bool IsWrite;
		bool IsChange(GuildCampBattle& other)
		{
			if(SrcGuildID != other.SrcGuildID || DestGuildID != other.DestGuildID || MoneySum != other.MoneySum || GuildMoneySum != other.GuildMoneySum 
				|| GuildMissionSum != other.GuildMissionSum)
				return true;
			else
				return false;
		}
	};
};