#ifndef _globalvars_h
#define _globalvars_h
#include <windows.h>
namespace GlobalTexture
{
	enum enumTexture
	{
		eFootprint,
		eSmoke,
		eShadow,
		eHitFlash,
		eElectric,
		eRock,
		eWaterCircle,
		eRedCircle,
		eIce,
		eDodge,
		eMiss,
		eNumberRed,
		eNumberGreen,
		eRune,
		eYellowGanTanHao,
		eWhiteGanTanHao,
		eYellowWenHao,
		eWhiteWenHao,
		//
		//eCursorIdle,
		//eCursorAttack,
		//eCursorPick,
		//eCursorTalk,
		//
		eBanner,				// ����
		//sbw_add
		eBackAttck,			//����
		eDefence,				//�ֿ�
		eWard,					//�м�
		eResist,
		eCruelHit,				//
		eDeathHit,
		eAddExp,
		eAddBangGong,	// �ﹱ
		eAddMingWang,	// ����
		eAddGongXun,	// ��ѫ
		eAddAreaReputation, //��������
		eAddRongYu,		// ����

		eNumber2,
        eNumber3,
        eNumber4,
        eAddSkillExp, //���ܾ���

		eMaxTexture
	};
	extern BOOL m_bLoaded;
	BOOL LoadFromSlk( const char* pszFilename );
	BOOL UnLoad();
	int	GetTexture( enumTexture id );
	int GetMedalTexture( int nId );
	int	GetCountryTexture( int nId );
};

namespace GlobalControl
{
	enum enumHitPointType
	{
		eNormal,
		eMagicStartShoot,
		eEffectNpc,
	};
};

#endif