#pragma  once

#include "MyString.h"
#include <map>


class CWeaponSound
{
	enum enumConst
	{
		const_iMaxName = 32
	};	
	
public:
	enum enumCreatureSound
	{
		WeaponSound_HitLeather			= 0
		,WeaponSound_HitMetal
		,WeaponSound_PrepareBow
		,WeaponSound_ReleaseBow
		,WeaponSound_ArrowFly
		,WeaponSound_Max
	};
private:

	struct SWeaponSound
	{
		char	szWeaponName[ const_iMaxName ];
		int		iSoundNum[ WeaponSound_Max ];
	};

	static char *m_szCreatureSounds[WeaponSound_Max];

	typedef std::map< CMyString,SWeaponSound* > WeaponSoundMap;

	WeaponSoundMap		m_mapWeaponSound;
public:
	typedef SWeaponSound*		HCREATURESOUND;

	CCreatureSound(void);
	~CCreatureSound(void);

	bool					LoadFromSlk( char *slkFile );
	HCREATURESOUND			GetCreatureSoundByName( char *szCreatureName );
	bool					GetSoundFile( HCREATURESOUND hCreatureSound,enumCreatureSound sound ,char*szWaveFile );
	HCREATURESOUND			GetNull( void );
};
extern CCreatureSound theCreatureSound;