#pragma once
#include <MeRTLibs.h>
#include <MeFoundation/MeFoundationBaseDefines.h>
#include <MeFoundation/MeAllocatedObject.h>
//效果结构
//技能表中的效果ID
class CSkillEffectSlk
{
public:
	enum AttachPart
	{
		AttachPartUnknown,
		AttachBody,				// 附着在身体
		AttachRightHand,		// 附着在右手
		AttachLeftHand,			// 附着在左手
		AttachTwoHand,			// 附着在双手
		AttachFoot,				// 附着在脚下，魔法阵
	};
	enum CastType			
	{
		CastTypeUnknown,
		CastFollow,				// 跟随
		CastExplode,			// 爆炸
		CastLaser,				// 激光
		CastMissile,			// 导弹，有弹道
		CastAttach				// 绑定效果，
	};
	enum PlayMode
	{
		PlayModeUnknown,
		PlayOneTime,			// 播放一次
		PlayLoop,				// 循环播放，显式停止
	};
	enum enumCastTargetType
	{
		//只产生一个特效
		casttarget_onlyone
		//每个目标一个特效
		,casttarget_oneforone
	};
	struct Record : public MeCommonAllocObj<CSkillEffectSlk::Record>
	{
		DWORD	dwId;
		DWORD	dwModelId;
		DWORD	dwAttachPart;
		DWORD	dwCastType;
		DWORD	dwPlayMode;		
		short	stCastTargetType;

		//发射音效
		//命中音效
		std::string strCastSound,strHitSound;
		//发射效果，命中时在目标位置创建一个特效
		int 	iHitEffect;
		// 发射型特效飞行速度， 
		float	fFlySpeed;

		Record():		dwId(0xffffffff),
						dwModelId(0xffffffff),
						dwAttachPart(AttachPartUnknown),		
						dwCastType(CastTypeUnknown),
						dwPlayMode(PlayModeUnknown),
						stCastTargetType(casttarget_onlyone	),
						fFlySpeed(0.0f)
		{
		}
	};
public:
	CSkillEffectSlk(void);
	~CSkillEffectSlk(void);

	BOOL		LoadFromSlk( const char* pszFilename );
	void		Clear( void );

	Record*		GetRecord( DWORD dwId );
	
protected:
	typedef std::map< DWORD,Record* > mapRecord;
	mapRecord	m_mapRecord;
	std::vector<Record> m_vectorRecord;
	Record		m_recordDefault;
};

extern CSkillEffectSlk g_skillEffectSlk;
