#include "Official.h"
#include "slkReader.h"
#include "Helper.h"
#include <assert.h>

COfficialMgr g_officialMgr;
COfficialMgr::COfficialMgr(void)
{
}

COfficialMgr::~COfficialMgr(void)
{
}

COfficialMgr::Record* COfficialMgr::GetRecord( int i )
{
	if( i < 0 || i >= dr_MaxOfficialLevel )
	{
		assert( false && "official get record error, out of range" );
			return NULL;
	}
	return &m_records[i];
}

BOOL COfficialMgr::LoadSettingFromSlk( const char* pszFilename )
{
	CSlkReader r;
	if( !r.ReadFromFile( (char*)pszFilename ) )
	{
		assert(false);
		return FALSE;
	}

	int nLine = 2;
	int iRet;
	int nLevel = 0;
	while( CSlkReader::ret_readover != ( iRet = r.GotoNextLine( nLine++ ) ) )
	{
		if( CSlkReader::ret_nothisline == iRet )
			continue;
		int nNeedExploit = 0;
		if( !r.GetIntField( "B", nNeedExploit ) )
		{
			assert( false );
			continue;
		}
		std::string strSanguoOffcialTitle;
		if( !r.GetStringField( "C", strSanguoOffcialTitle ) )
		{
			assert( false );
			continue;
		}
		std::string strQinOffcialTitle;
		if( !r.GetStringField( "D", strQinOffcialTitle ) )
		{
			assert( false );
			continue;
		}

		std::string strJapanOffcialTitle;
		if( !r.GetStringField( "E", strJapanOffcialTitle ) )
		{
			assert( false );
			continue;
		}
		if( nLevel <= dr_MaxOfficialLevel )
		{
			Record record;
			record.dwNeedExploit = nNeedExploit;
			HelperFunc::SafeNCpy( 
				record.szOfficialTitle[country_sanguo], 
				//pszSanguoOfficialTitle, 
				strSanguoOffcialTitle.c_str(),
				dr_MaxOfficialTitle );
			HelperFunc::SafeNCpy( 
				record.szOfficialTitle[country_qin], 
				//pszQinOfficialTitle, 
				strQinOffcialTitle.c_str(),
				dr_MaxOfficialTitle );
			HelperFunc::SafeNCpy( 
				record.szOfficialTitle[country_npc], 
				//pszJapanOfficialTitle, 
				strJapanOffcialTitle.c_str(),
				dr_MaxOfficialTitle );
			
			m_records[nLevel] = record;
			nLevel++;
		}
		else
		{
			assert( false && "official load setting error, level too much" );
			break;
		}
			
	}
	return TRUE;
}

BOOL COfficialMgr::Load()
{
	BOOL bOK = LoadSettingFromSlk( "..\\Data\\Config\\officialsetting.slk" );
	if( !bOK )
	{
		assert( false && "offcial mgr load setting error" );
		return FALSE;
	}
	return TRUE;
}