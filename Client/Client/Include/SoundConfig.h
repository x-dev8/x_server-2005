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
		EST_JumpM,			// 男跳跃
		EST_JumpF,			// 女跳跃
		EST_DropM,			// 男落地
		EST_DropF,			// 女落地
		EST_RunLM,			// 男跑步左脚
		EST_RunRM,			// 男跑步右脚
		EST_RunLF,			// 女跑步左脚
		EST_RunRF,			// 女跑步右脚
		EST_SwimM,			// 男游泳
		EST_SwimF,			// 女游泳
		EST_RunInWaterM,	// 男在水中跑
		EST_RunInWaterF,	// 女在水中跑
		EST_SitM,			// 男坐下
		EST_SitF,			// 女坐下
		EST_IdleM,			// 男待机
		EST_IdleF,			// 女待机
		EST_DeadM,			// 男死亡
		EST_DeadF,			// 女死亡
		EST_OpenWorldMapUI,	// 打开地图
		EST_OpenPetUI,		// 打开坐骑界面
		EST_OpenPackUI,		// 打开包裹界面
		EST_MoneyInc,		// 金钱增加
		EST_MoneyDec,		// 金钱减少
		EST_AbandonTask,	// 放弃任务
		EST_DigSuccess,		// 挖掘成功
		EST_GatherSuccess,	// 采集成功
		EST_ForgingSuccess, // 锻造成功
		EST_ForgingFailed,	// 锻造失败
		EST_StarSuccess,	// 升星成功
		EST_StarFailed,		// 升星失败
		EST_HoleSuccess,	// 打孔成功
		EST_HoleFailed,		// 打孔失败
		EST_InlaySuccess,	// 镶嵌成功
		EST_InlayFailed,	// 镶嵌失败
		EST_GoldSuccess,	// 鎏金成功
		EST_GoldFailed,		// 鎏金失败
		EST_StampSuccess,	// 铭刻成功
		EST_StampFailed,	// 铭刻失败
		EST_StartStall,		// 开始摆摊
		EST_StartFight,		// 比武开始
		EST_EndFight,		// 比武结束
		EST_FriendMsg,		// 好友信息提醒
		EST_RequestTeam,	// 组队邀请
		EST_RequestFight,	// 比武邀请
		EST_RequestTrade,	// 交易邀请
		EST_FriendOnline,	// 好友上线
		EST_LoseItem,		// 物品丢弃
		EST_CleanupItem,	// 整理物品
		EST_InCoolDown,		// 技能未冷却
		EST_EnterWorld,		// 进入游戏（点击按钮）
		EST_LoginScene,		// 登陆场景
		EST_SelectScene,	// 选人场景
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
