#pragma  once

#include "MyString.h"
#include <map>
#include "ItemDetail.h"

class CCreatureSound
{
	enum enumConst
	{
		const_iMaxName = 32
	};
	
	
public:
	enum enumCreatureSound
	{
		CreatureSound_Idle			= 0
		,CreatureSound_Attack
		,CreatureSound_BeHit
		,CreatureSound_Dead
		,CreatureSound_Max
	};

public:
    typedef CItemDetail::ItrCreatureSoundContainer		HCREATURESOUND;

	CCreatureSound(void);
	~CCreatureSound(void);

	bool					LoadFromSlk( char *slkFile );
	HCREATURESOUND			GetCreatureSoundByName( char *szCreatureName );
	bool					GetSoundFile( HCREATURESOUND hCreatureSound,enumCreatureSound sound ,char*szWaveFile );
	HCREATURESOUND			GetNull( void );
};
extern CCreatureSound theCreatureSound;