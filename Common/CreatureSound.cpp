#include "CreatureSound.h"
#include "slkreader.h"
#include "Helper.h"
#include "FuncPerformanceLog.h"

CCreatureSound theCreatureSound;

char * m_szCreatureSounds[ CCreatureSound::CreatureSound_Max ] =
{
	"idle"
	,"attack"
	,"behit"
	,"dead"
};

CCreatureSound::CCreatureSound(void)
{

	guardfunc;
	OutputDebugStr("CCreatureSound");
	unguard;
}

CCreatureSound::~CCreatureSound(void)
{
	guardfunc;
	unguard;
}

bool CCreatureSound::LoadFromSlk( char *slkFile )
{
	guardfunc;
	return true;
	unguard;
}

CCreatureSound::HCREATURESOUND CCreatureSound::GetCreatureSoundByName( char *szCreatureName )
{
	guardfunc;
    return GettheItemDetail().GetCreatureSoundItr(szCreatureName);
	unguard;
}

CCreatureSound::HCREATURESOUND CCreatureSound::GetNull( void )
{
	guardfunc;
	static CCreatureSound::HCREATURESOUND end = GettheItemDetail().GetCreatureSoundItr("HCREATURESOUND.End");
	return end;
	unguard;
}

//返回一个文件like:
//Wolf_Attack0.wav
extern const char* GetRootPath();
bool CCreatureSound::GetSoundFile( HCREATURESOUND hCreatureSound,enumCreatureSound sound ,char*szWaveFile )
{	
	guardfunc;
	if( hCreatureSound == GetNull() )
		return false;

	ItemDefine::SCreatureSound *pCreature = hCreatureSound->second;
	if( pCreature->SoundNum[ sound ] <= 0 )
		return false;

	sprintf( szWaveFile,"%s\\data\\audio\\monster\\%s\\%s_%s%d.wav"
		,GetRootPath()
		,pCreature->GetName()
		,pCreature->GetName(),m_szCreatureSounds[ sound ],
		rand() % pCreature->SoundNum[ sound ] );

	return true;
	unguard;
}