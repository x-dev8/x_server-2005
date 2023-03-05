/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\li.yan\桌面\刘小兵\GuildAttribute.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "GuildAttribute.h"
#include "PlayerRole.h"
#include "Common.h"
#include "Gang.h"
#include "GuildConfig.h"

CUI_ID_FRAME_GuildAttribute s_CUI_ID_FRAME_GuildAttribute;
MAP_FRAME_RUN( s_CUI_ID_FRAME_GuildAttribute, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_GuildAttribute, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GuildAttribute, ID_BUTTON_CLOSEOnButtonClick )
CUI_ID_FRAME_GuildAttribute::CUI_ID_FRAME_GuildAttribute()
{
	// Member
	m_pID_FRAME_GuildAttribute = NULL;
	m_pID_TEXT_Name = NULL;
	m_pID_TEXT_LeaderName = NULL;
	m_pID_TEXT_Level = NULL;
	m_pID_TEXT_Exp = NULL;
	m_pID_TEXT_Person = NULL;
	m_pID_TEXT_Money = NULL;
	m_pID_TEXT_Duty = NULL;
	//m_pID_BUTTON_CLOSE = NULL;

}
// Frame
bool CUI_ID_FRAME_GuildAttribute::OnFrameRun()
{
	//每帧界面逻辑更新，需要先判断界面是否可见，把下面代码打开
	//if( IsVisable() )
	//{
	//}
	return true;
}
bool CUI_ID_FRAME_GuildAttribute::OnFrameRender()
{
	return true;
}
// Button
bool CUI_ID_FRAME_GuildAttribute::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_GuildAttribute )
		return false;
	return true;
}

// 装载UI
bool CUI_ID_FRAME_GuildAttribute::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\GuildAttribute.MEUI" );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\GuildAttribute.MEUI]失败")
		return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_GuildAttribute::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_GuildAttribute, s_CUI_ID_FRAME_GuildAttributeOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_GuildAttribute, s_CUI_ID_FRAME_GuildAttributeOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_GuildAttribute, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_GuildAttributeID_BUTTON_CLOSEOnButtonClick );

	m_pID_FRAME_GuildAttribute = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_GuildAttribute );
	m_pID_TEXT_Name = (ControlText*)theUiManager.FindControl( ID_FRAME_GuildAttribute, ID_TEXT_Name );
	m_pID_TEXT_LeaderName = (ControlText*)theUiManager.FindControl( ID_FRAME_GuildAttribute, ID_TEXT_LeaderName );
	m_pID_TEXT_Level = (ControlText*)theUiManager.FindControl( ID_FRAME_GuildAttribute, ID_TEXT_Level );
	m_pID_TEXT_Exp = (ControlText*)theUiManager.FindControl( ID_FRAME_GuildAttribute, ID_TEXT_Exp );
	m_pID_TEXT_Person = (ControlText*)theUiManager.FindControl( ID_FRAME_GuildAttribute, ID_TEXT_Person );
	m_pID_TEXT_Money = (ControlText*)theUiManager.FindControl( ID_FRAME_GuildAttribute, ID_TEXT_Money );
	m_pID_TEXT_Duty = (ControlText*)theUiManager.FindControl( ID_FRAME_GuildAttribute, ID_TEXT_Duty );
	//m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_FRAME_GuildAttribute, ID_BUTTON_CLOSE );

	assert( m_pID_FRAME_GuildAttribute );
	assert( m_pID_TEXT_Name );
	assert( m_pID_TEXT_LeaderName );
	assert( m_pID_TEXT_Level );
	assert( m_pID_TEXT_Exp );
	assert( m_pID_TEXT_Person );
	assert( m_pID_TEXT_Money );
	assert( m_pID_TEXT_Duty );
	//assert( m_pID_BUTTON_CLOSE );

	SetVisable(false);
	m_pID_FRAME_GuildAttribute->SetArrayMode(ArrayMode_Top);
	m_pID_FRAME_GuildAttribute->SetFather(s_CUI_ID_FRAME_Gang.GetFrame());
	return true;
}

// 卸载UI
bool CUI_ID_FRAME_GuildAttribute::_UnLoadUI()
{
	m_pID_FRAME_GuildAttribute = NULL;
	m_pID_TEXT_Name = NULL;
	m_pID_TEXT_LeaderName = NULL;
	m_pID_TEXT_Level = NULL;
	m_pID_TEXT_Exp = NULL;
	m_pID_TEXT_Person = NULL;
	m_pID_TEXT_Money = NULL;
	m_pID_TEXT_Duty = NULL;
	//m_pID_BUTTON_CLOSE = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\GuildAttribute.MEUI" );
}

// 是否可视
bool CUI_ID_FRAME_GuildAttribute::_IsVisable()
{
	if ( !m_pID_FRAME_GuildAttribute )
		return false;
	return m_pID_FRAME_GuildAttribute->IsVisable();
}

// 设置是否可视
void CUI_ID_FRAME_GuildAttribute::_SetVisable( const bool bVisable )
{
	if ( !m_pID_FRAME_GuildAttribute )
		return;
	if (bVisable)
	{
		SetAttribute();
	}
	
	m_pID_FRAME_GuildAttribute->SetVisable( bVisable );
}

void CUI_ID_FRAME_GuildAttribute::SetAttribute()
{
	CGangMgr* pGuild = thePlayerRole.GetGangMgr();
	if(pGuild == NULL || pGuild->GetGuildID() == GuildDefine::InitID)
	{
		return;
	}

	m_pID_TEXT_Name->SetText(pGuild->GetGuildName());
	m_pID_TEXT_LeaderName->SetText(pGuild->GetGuildMasterName());
	m_pID_TEXT_Level->SetText(pGuild->GetGuildLevel());

	char szText[128] = {0};
	MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1, "%d/%d", pGuild->GetMemberOnlineCount(), pGuild->GetMemberCount());

	m_pID_TEXT_Person->SetText(szText);

	const GuildConfig::LevelSetting* pGuildLevelSetting = theGuildConfig.GetLevelSetting(pGuild->GetGuildLevel());
	if (!pGuildLevelSetting)
	{
		return;
	}

	memset(szText, 0, sizeof(szText));
	MeSprintf_s(szText, sizeof(szText) / sizeof(char) - 1, "%d / %d", pGuild->GetGuildExp(), pGuildLevelSetting->GetMaxExp());
	m_pID_TEXT_Exp->SetText(szText);
		
	memset(szText, 0, sizeof(szText));
	MeSprintf_s(szText, sizeof(szText)/sizeof(char) - 1, "%d / %d", pGuild->GetGuildMission(), pGuildLevelSetting->GetMaxMission());
	m_pID_TEXT_Duty->SetText(szText);

	std::string strMoney;
	thePlayerRole.GetGSCStringFromMoney(pGuild->GetGuildMoney(), strMoney);
	m_pID_TEXT_Money->SetText(strMoney.c_str());
}