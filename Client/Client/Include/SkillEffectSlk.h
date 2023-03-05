#pragma once
#include <MeRTLibs.h>
#include <MeFoundation/MeFoundationBaseDefines.h>
#include <MeFoundation/MeAllocatedObject.h>
//Ч���ṹ
//���ܱ��е�Ч��ID
class CSkillEffectSlk
{
public:
	enum AttachPart
	{
		AttachPartUnknown,
		AttachBody,				// ����������
		AttachRightHand,		// ����������
		AttachLeftHand,			// ����������
		AttachTwoHand,			// ������˫��
		AttachFoot,				// �����ڽ��£�ħ����
	};
	enum CastType			
	{
		CastTypeUnknown,
		CastFollow,				// ����
		CastExplode,			// ��ը
		CastLaser,				// ����
		CastMissile,			// �������е���
		CastAttach				// ��Ч����
	};
	enum PlayMode
	{
		PlayModeUnknown,
		PlayOneTime,			// ����һ��
		PlayLoop,				// ѭ�����ţ���ʽֹͣ
	};
	enum enumCastTargetType
	{
		//ֻ����һ����Ч
		casttarget_onlyone
		//ÿ��Ŀ��һ����Ч
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

		//������Ч
		//������Ч
		std::string strCastSound,strHitSound;
		//����Ч��������ʱ��Ŀ��λ�ô���һ����Ч
		int 	iHitEffect;
		// ��������Ч�����ٶȣ� 
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
