#include "Guild.h"
#include "MeUi/UiManager.h"
#include "Gang.h"
#include "AddMember.h"
#include "Guild_Create.h"
#include "Announce.h"
#include "PlayerRole.h"
#include "SystemConfig.h"
#include "FuncPerformanceLog.h"
#include "NetworkInput.h"
#include "XmlStringLanguage.h"
#include "../color_config.h"
//#include "Alignment.h"
#include "DroitList.h"
extern int g_nCharacterDBID;

CUI_Guild s_CUI_Guild;
CUI_Guild::CUI_Guild()
{
    m_bNeedRefresh = true;
	//m_bNeedRefreshAlignment = true;
}
void CUI_Guild::LoadUI()
{
	guardfunc;
	s_CUI_ID_FRAME_Gang.LoadUI();
	s_CUI_ID_FRAME_Gang.SetVisable( false );
    s_CUI_ID_FRAME_ADD_MEMBER.LoadUI();
    s_CUI_ID_FRAME_ADD_MEMBER.SetVisable( false );
    s_CUI_ID_FRAME_Announce.LoadUI();
    s_CUI_ID_FRAME_Announce.SetVisable(false);
	s_CUI_ID_FRAME_GUILD_CREATE.LoadUI();
	s_CUI_ID_FRAME_GUILD_CREATE.SetVisable(false);
	//s_CUI_ID_FRAME_Alignment.LoadUI();
	//s_CUI_ID_FRAME_Alignment.SetVisable(false);
	s_CUI_ID_FRAME_DroitList.LoadUI();
	s_CUI_ID_FRAME_DroitList.SetVisable(false);
	unguard;
}

void CUI_Guild::UnLoadUI()
{
    guardfunc;
	//s_CUI_ID_FRAME_Alignment.UnLoadUI();
    s_CUI_ID_FRAME_Gang.UnLoadUI();
    s_CUI_ID_FRAME_ADD_MEMBER.UnLoadUI();
    s_CUI_ID_FRAME_Announce.UnLoadUI();
	s_CUI_ID_FRAME_GUILD_CREATE.UnLoadUI();
	s_CUI_ID_FRAME_DroitList.UnLoadUI();

    CGangMgr* theGuild = thePlayerRole.GetGangMgr();
    if(theGuild == NULL)
    {
        return;
    }
    theGuild->Clear();
    unguard;
}

void CUI_Guild::Refeash()
{
    m_bNeedRefresh = true;
	//m_bNeedRefreshAlignment = true;
}

