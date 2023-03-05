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
		eBanner,				// 旗帜
		//sbw_add
		eBackAttck,			//背击
		eDefence,				//抵抗
		eWard,					//招架
		eResist,
		eCruelHit,				//
		eDeathHit,
		eAddExp,
		eAddBangGong,	// 帮贡
		eAddMingWang,	// 名望
		eAddGongXun,	// 功勋
		eAddAreaReputation, //地区声望
		eAddRongYu,		// 荣誉

		eNumber2,
        eNumber3,
        eNumber4,
        eAddSkillExp, //技能经验

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