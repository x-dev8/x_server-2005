#include "WealthProtect.h"
#include "MeRTLibs.h"
#include "ScreenInfoManager.h"
#include "XmlStringLanguage.h"
#include "Color_config.h"
#include "core/Name.h"

CWealthProtect::CWealthProtect( void )
{
	m_shProtectTime = 1;
	m_dwProtectEndingTime = 0;
	m_bFirstEnterMap = FALSE;
}

void CWealthProtect::InitProtectEndingTime( unsigned int curTime )
{
	m_dwProtectEndingTime = curTime + m_shProtectTime * 60 * 1000;
}

bool CWealthProtect::IsInProtectTime( bool bShowMsg /*= true*/ )
{
	if( HQ_TimeGetTime() < m_dwProtectEndingTime)
	{
		if( bShowMsg )
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Wealth_Protect, theXmlString.GetString( eText_OperateFailInProtectTime ) );
		return true;
	}
	return false;
}
