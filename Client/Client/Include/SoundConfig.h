#pragma once
#include <MeRTLibs.h>
#include <Singleton.h>
#include <MeAudio/MeAudio.h>
/**
* @brief Sound configuration.
*/
class SoundConfig : public Singleton< SoundConfig >
{
// Enumeration & Structures.
public:
	/// Sound types.
	enum ESoundType
	{
		EST_JumpM,			// ����Ծ
		EST_JumpF,			// Ů��Ծ
		EST_DropM,			// �����
		EST_DropF,			// Ů���
		EST_RunLM,			// ���ܲ����
		EST_RunRM,			// ���ܲ��ҽ�
		EST_RunLF,			// Ů�ܲ����
		EST_RunRF,			// Ů�ܲ��ҽ�
		EST_SwimM,			// ����Ӿ
		EST_SwimF,			// Ů��Ӿ
		EST_RunInWaterM,	// ����ˮ����
		EST_RunInWaterF,	// Ů��ˮ����
		EST_SitM,			// ������
		EST_SitF,			// Ů����
		EST_IdleM,			// �д���
		EST_IdleF,			// Ů����
		EST_DeadM,			// ������
		EST_DeadF,			// Ů����
		EST_OpenWorldMapUI,	// �򿪵�ͼ
		EST_OpenPetUI,		// ���������
		EST_OpenPackUI,		// �򿪰�������
		EST_MoneyInc,		// ��Ǯ����
		EST_MoneyDec,		// ��Ǯ����
		EST_AbandonTask,	// ��������
		EST_DigSuccess,		// �ھ�ɹ�
		EST_GatherSuccess,	// �ɼ��ɹ�
		EST_ForgingSuccess, // ����ɹ�
		EST_ForgingFailed,	// ����ʧ��
		EST_StarSuccess,	// ���ǳɹ�
		EST_StarFailed,		// ����ʧ��
		EST_HoleSuccess,	// ��׳ɹ�
		EST_HoleFailed,		// ���ʧ��
		EST_InlaySuccess,	// ��Ƕ�ɹ�
		EST_InlayFailed,	// ��Ƕʧ��
		EST_GoldSuccess,	// �̽�ɹ�
		EST_GoldFailed,		// �̽�ʧ��
		EST_StampSuccess,	// ���̳ɹ�
		EST_StampFailed,	// ����ʧ��
		EST_StartStall,		// ��ʼ��̯
		EST_StartFight,		// ���俪ʼ
		EST_EndFight,		// �������
		EST_FriendMsg,		// ������Ϣ����
		EST_RequestTeam,	// �������
		EST_RequestFight,	// ��������
		EST_RequestTrade,	// ��������
		EST_FriendOnline,	// ��������
		EST_LoseItem,		// ��Ʒ����
		EST_CleanupItem,	// ������Ʒ
		EST_InCoolDown,		// ����δ��ȴ
		EST_EnterWorld,		// ������Ϸ�������ť��
		EST_LoginScene,		// ��½����
		EST_SelectScene,	// ѡ�˳���
		EST_Count
	};

	/// Sound item.
	struct SoundItem
	{
		ESoundType m_eType;		// Sound type.
		std::string m_strFile;	// File name.
	};

// Construction.
private:
	/// To singleton visible.
	friend class Singleton< SoundConfig >;

	/// Constructor.
	SoundConfig(){}
	
	/// Destructor.
	~SoundConfig(){}

// Overload operator.
private:
	/// Disable copy constructor.
	SoundConfig( const SoundConfig& kClass ){}

	/// Disable assignment operator.
	const SoundConfig& operator=( const SoundConfig& kClass ){ return *this; }

// Methods.
public:
	/// Load config file.
	bool LoadSoundConfig( const char* pcFilename );

	/// Get a specified sound file by its type. The probability is
	/// calculated inside.
	const std::string& GetSoundFile( SoundConfig::ESoundType eType ) const;

// Members.
protected:
	/// Sound items storage.
	typedef std::map< ESoundType, SoundItem > SoundItems;
	typedef SoundItems::iterator SoundItemsIter;
	typedef SoundItems::const_iterator SoundItemConstIter;
	SoundItems m_SoundItems;
};

extern char* GetFullFileName(const char* filename);

#define theSoundConfig (*SoundConfig::Instance())
#define PlaySoundConfig( type ) \
	std::string strFile = theSoundConfig.GetSoundFile( type ); \
	GSound.PlaySound( GetFullFileName( strFile.c_str() ), false, NULL );

#define PlaySoundConfigPos( type, pos )\
	std::string strFile = theSoundConfig.GetSoundFile( type ); \
	GSound.PlaySound( GetFullFileName( strFile.c_str() ), false, pos );

#define PlaySoundConfigLoop( type, loop )\
	std::string strFile = theSoundConfig.GetSoundFile( type ); \
	GSound.PlaySound( GetFullFileName( strFile.c_str() ), loop,  NULL );
