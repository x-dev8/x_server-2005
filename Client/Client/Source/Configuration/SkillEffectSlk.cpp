#include <assert.h>
#include "slkreader.h"
#include "skilleffectslk.h"
#include "FuncPerformanceLog.h"
CSkillEffectSlk g_skillEffectSlk;

CSkillEffectSlk::CSkillEffectSlk(void)
{

	guardfunc;
	OutputDebugStr("CSkillEffectSlk");
	unguard;
}

CSkillEffectSlk::~CSkillEffectSlk(void)
{
	guardfunc;
	Clear();
	unguard;
}

BOOL CSkillEffectSlk::LoadFromSlk( const char* pszFilename )
{
	guardfunc;
	CSlkReader reader;
	if( !reader.ReadFromFile( (char*)pszFilename ) )
	{
		assert(false);
		return FALSE;
	}
	int iRow = 2;
	int iCol = 0;
	int iRet = 0;

	int iValue;
	float fValue;
	std::string strTemp;


	Record record;
	while ( CSlkReader::ret_readover != ( iRet = reader.GotoNextLine( iRow++ ) ) ) 
	{
		if( CSlkReader::ret_nothisline == iRet )
			continue;

		CSlkReader::SField* field = NULL;

		if( !reader.GetIntFieldByName(      "ID",       iValue ) )
			continue;
		DWORD dwId = iValue;

		if( !reader.GetIntFieldByName(      "ModelID",       iValue ) )
			continue;

		DWORD dwModelId = iValue;

		if( !reader.GetStringFieldByName(      "AttachPart",   strTemp ) )
			continue;
		
		char szAttachPart[MAX_PATH] = {0};
		strcpy( szAttachPart, strTemp.c_str() );

		if( !reader.GetStringFieldByName(      "CastType",   strTemp ) )
			continue;
		char szCastType[MAX_PATH] = {0};
		strcpy( szCastType, strTemp.c_str() );

		if( !reader.GetStringFieldByName(      "PlayMode",   strTemp ) )
			continue;
		char szPlayMode[MAX_PATH] = {0};
		strcpy( szPlayMode, strTemp.c_str() );

		if( !reader.GetStringFieldByName(      "casttarget",   strTemp ) )
			continue;

		char szCastTargetType[MAX_PATH] = {0};
		strcpy( szCastTargetType, strTemp.c_str() );

		reader.GetStringFieldByName(      "castsound",   strTemp );
		record.strCastSound = strTemp;

		reader.GetStringFieldByName(      "hitsound",   strTemp );
		record.strHitSound = strTemp;

		if( !reader.GetIntFieldByName(      "lattereffect",   iValue ) )
			record.iHitEffect = -1;
		else
			record.iHitEffect = iValue;
			
		//
		if( reader.GetFloatFieldByName(      "FlySpeed",   fValue ) )
			record.fFlySpeed = fValue;

		//////////////////////////////////////////////////////////////////////////
		
		record.dwId = dwId;
		record.dwModelId = dwModelId;

		if( _stricmp( szAttachPart, "AttachBody" ) == 0 )
			record.dwAttachPart = AttachBody;
		else if( _stricmp( szAttachPart, "AttachRightHand" ) == 0 )
			record.dwAttachPart = AttachRightHand;
		else if( _stricmp( szAttachPart, "AttachLeftHand" ) == 0 )
			record.dwAttachPart = AttachLeftHand;
		else if( _stricmp( szAttachPart, "AttachTwoHand" ) == 0 )
			record.dwAttachPart = AttachTwoHand;
		else if( _stricmp( szAttachPart, "AttachFoot" ) == 0 )
			record.dwAttachPart = AttachFoot;

		if( _stricmp( szCastType, "CastFollow" ) == 0 )
			record.dwCastType = CastFollow;
		else if( _stricmp( szCastType, "CastExplode" ) == 0 )
			record.dwCastType = CastExplode;
		else if( _stricmp( szCastType, "CastLaser" ) == 0 )
			record.dwCastType = CastLaser;
		else if( _stricmp( szCastType, "CastMissile" ) == 0 )
			record.dwCastType = CastMissile;
		else if( _stricmp( szCastType, "CastAttach" ) == 0 )
			record.dwCastType = CastAttach;

		if( _stricmp( szPlayMode, "PlayOneTime" ) == 0 )
			record.dwPlayMode = PlayOneTime;
		else if( _stricmp( szPlayMode, "PlayLoop" ) == 0 )
			record.dwPlayMode = PlayLoop;

		//·¢ÉäÊôÐÔ
		if( 0 == _stricmp( szCastTargetType,"casttarget_onlyone") )
		{
			record.stCastTargetType = casttarget_onlyone;
		}
		else
		if( 0 == _stricmp( szCastTargetType,"casttarget_oneforone") )
		{
			record.stCastTargetType = casttarget_oneforone;
		}
		else
			record.stCastTargetType = casttarget_onlyone;

		Record *pRecord = MeNew Record;
		*pRecord = record;
		m_mapRecord.insert( mapRecord::value_type( record.dwId,pRecord ) );
	}

	m_recordDefault.stCastTargetType = casttarget_onlyone;

	return TRUE;
	unguard;
}

void CSkillEffectSlk::Clear( void )
{
	guardfunc;
	mapRecord::iterator it;
	for( it = m_mapRecord.begin() ; it != m_mapRecord.end() ; it ++ )
	{
		delete it->second;
	}
	m_mapRecord.clear();
	unguard;
}

CSkillEffectSlk::Record* CSkillEffectSlk::GetRecord( DWORD dwId )
{
	guardfunc;
	mapRecord::iterator it;
	it = m_mapRecord.find( dwId );
	if( m_mapRecord.end() == it )
	{
		m_recordDefault.dwModelId = dwId;
		return &m_recordDefault;
	}
	return it->second;
	unguard;
}
