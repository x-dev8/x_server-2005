#include "Player.h"
#include "MeUi/ControlText.h"
#include "GameMain.h"
#include "PlayerMgr.h"

extern CHeroGame* theApp;

bool CPlayer::IsPtInPrivateShopInfo( int x, int y )
{
	if ( !IsPlayer() )
	{
		return false;
	}
	if ( !m_bPrivateShopOpen )
	{
		return false;
	}

	if(  m_pPrivateShopInfo->PtInObject( x, y ) ) // 就是这个
	{
		return true;
	}

	return false;
}

