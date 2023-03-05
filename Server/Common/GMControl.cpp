#include "gm_control.h"
#include "GamePlayer.h"
#include "ShareData.h"
#include "WordParser.h"
#include "GameWorld.h"

GmControl::GmControl()
{
}

long GmControl::gameWorldGmCommand( GamePlayer* pGameGm, const char* szCommand )
{
    // ¼ì²éÈ¨Àû·¶Î§
    return RC_SUCCESS;
}

long GmControl::gameServerGmCommand( const char* szCommand )
{
    if ( NULL==szCommand )
        return RC_PARAM_ERROR;

    return RC_SUCCESS;
}

long GmControl::_changeGameWorldGmPermission( const std::string& strName, unsigned int uiPermission )
{
    GamePlayer* pChar = theRunTimeData.GetGamePlayerByName( strName );
    if ( NULL == pChar )
        return RC_NOT_FIND_CHAR;

    pChar->m_nGMLevel = uiPermission;
    return RC_SUCCESS;
}
