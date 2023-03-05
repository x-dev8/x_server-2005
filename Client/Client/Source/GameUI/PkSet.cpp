/********************************************************************
	Created by UIEditor.exe
	FileName: E:\Document\保护设置\PkSet.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "PkSet.h"
#include "Group_Me.h"
#include "MessageDefine.h"
#include "NetworkInput.h"
#include "GameSetting.h"
#include "GameSettingUI.h"
#include "UserData.h"
#include "Player.h"
#include "GameMain.h"
#include "PlayerMgr.h"
#include "GameSettingSelf.h"
#include "GameSettingPlayer.h"
#include "Common.h"

CUI_ID_FRAME_PkSet s_CUI_ID_FRAME_PkSet;
MAP_FRAME_RUN( s_CUI_ID_FRAME_PkSet, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_PkSet, OnFrameRender )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_PkSet, ID_CHECKBOX_SwornOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_PkSet, ID_CHECKBOX_GuildOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_PkSet, ID_CHECKBOX_LeagueOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_PkSet, ID_CHECKBOX_AllOnCheckBoxCheck )
MAP_SCROLL_BAREX_UPDATE_POS_CALLBACK( s_CUI_ID_FRAME_PkSet, ID_SCROLLBAREX_LvlOnScrollBarExUpdatePos )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_PkSet, ID_CHECKBOX_HpOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_PkSet, ID_CHECKBOX_MpOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_PkSet, ID_CHECKBOX_DanderOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_PkSet, ID_CHECKBOX_RedOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_PkSet, ID_CHECKBOX_WhiteOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_PkSet, ID_CHECKBOX_BlueOnCheckBoxCheck )
CUI_ID_FRAME_PkSet::CUI_ID_FRAME_PkSet()
{
	// Member
	ResetMembers();
}

void CUI_ID_FRAME_PkSet::ResetMembers()
{
	m_pID_FRAME_PkSet = NULL;
	m_pID_PICTURE_ImageWall = NULL;
	m_pID_TEXT_Sworn = NULL;
	m_pID_TEXT_Guild = NULL;
	m_pID_TEXT_All = NULL;
	m_pID_TEXT_League = NULL;
	m_pID_CHECKBOX_Sworn = NULL;
	m_pID_CHECKBOX_Guild = NULL;
	m_pID_CHECKBOX_League = NULL;
	m_pID_CHECKBOX_All = NULL;
	m_pID_PICTURE_30013 = NULL;
	m_pID_PICTURE_13560 = NULL;
	m_pID_PICTURE_25141 = NULL;
	m_pID_PICTURE_32481 = NULL;
	m_pID_TEXT_Lvl = NULL;
	m_pID_SCROLLBAREX_Lvl = NULL;
	m_pID_CHECKBOX_Hp = NULL;
	m_pID_CHECKBOX_Mp = NULL;
	m_pID_CHECKBOX_Dander = NULL;
	m_pID_TEXT_Hp = NULL;
	m_pID_TEXT_Mp = NULL;
	m_pID_TEXT_Dander = NULL;
	m_pID_CHECKBOX_Red = NULL;
	m_pID_CHECKBOX_White = NULL;
	m_pID_CHECKBOX_Blue = NULL;
	m_pID_TEXT_Red = NULL;
	m_pID_TEXT_White = NULL;
	m_pID_TEXT_Blue = NULL;

	m_nPkLevel = PK_AllProtect;
	stPkTrueLevel = PK_AllProtect;
	m_nPkOldLevel = m_nPkLevel;
}
// Frame
bool CUI_ID_FRAME_PkSet::OnFrameRun()
{
	return true;
}
bool CUI_ID_FRAME_PkSet::OnFrameRender()
{
	return true;
}
// Button
bool CUI_ID_FRAME_PkSet::OnOkButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_PkSet )
		return false;
    GameSetting::Instance()->SetLevel( GameSetting::eGSC_SelfHp, m_pID_CHECKBOX_Hp->IsChecked() );
    GameSetting::Instance()->SetLevel( GameSetting::eGSC_TeamPlayerHp, m_pID_CHECKBOX_Hp->IsChecked() );
    GameSetting::Instance()->SetLevel( GameSetting::eGSC_OtherPlayerHp, m_pID_CHECKBOX_Hp->IsChecked() );
    GameSetting::Instance()->SetLevel( GameSetting::eGSC_SelfMp, m_pID_CHECKBOX_Mp->IsChecked() );
    GameSetting::Instance()->CommitChanges();
    // 更新游戏设置界面
    s_CUI_ID_FRAME_GameSettingPlayer.RefreshUI();
    s_CUI_ID_FRAME_GameSettingSelf.RefreshUI();

    char szSetting[MAX_PATH] = {0};
    MeSprintf_s( szSetting, sizeof(szSetting)/sizeof(char) - 1, "%s%s", CUserData::Instance()->GetUserDataPath(), GameSetting::Instance()->GetCustomSettingDirectory() );
    GameSetting::Instance()->SaveSetting( szSetting );

    m_nPkOldLevel = m_nPkLevel;
    SetVisable(false);
    SendMessage();
    s_CUI_ID_FRAME_Group_Me.RefreshPKShowPicture(m_nPkOldLevel);
	return true;
}
// Button
bool CUI_ID_FRAME_PkSet::OnCancelButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_PkSet )
		return false;
    SetVisable(false);
	return true;
}
// CheckBox
void CUI_ID_FRAME_PkSet::ID_CHECKBOX_SwornOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if( !m_pID_FRAME_PkSet )
		return;
    assert(0);
    if (pbChecked && (*pbChecked == true))
    {
	    m_nPkLevel = PK_TeamProtect;
    }
    else
    {
	    --m_nPkLevel;
    }

    RefreshUI();
}
// CheckBox
void CUI_ID_FRAME_PkSet::ID_CHECKBOX_GuildOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if( !m_pID_FRAME_PkSet )
		return;
	if (pbChecked && (*pbChecked == true))
	{
		m_nPkLevel = PK_GuildProtect;
	}
	else
	{
		--m_nPkLevel;
	}

	RefreshUI();
}
// CheckBox
void CUI_ID_FRAME_PkSet::ID_CHECKBOX_LeagueOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if( !m_pID_FRAME_PkSet )
		return;
    if (pbChecked && (*pbChecked == true))
    {
	    m_nPkLevel = PK_LeagueProtect;
    }
    else
    {
	    --m_nPkLevel;
    }

    RefreshUI();
}
// CheckBox
void CUI_ID_FRAME_PkSet::ID_CHECKBOX_AllOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if( !m_pID_FRAME_PkSet )
		return;
    if (pbChecked && (*pbChecked == true))
    {
	    m_nPkLevel = PK_AllProtect;
    }
    else
    {
	    --m_nPkLevel;
    }

    RefreshUI();
}
// ScrollBarEx
void CUI_ID_FRAME_PkSet::ID_SCROLLBAREX_LvlOnScrollBarExUpdatePos( ControlObject* pSender, int n )
{
	if( !m_pID_FRAME_PkSet )
		return;
	m_nPkLevel = n;
	RefreshUI();
}
// CheckBox
void CUI_ID_FRAME_PkSet::ID_CHECKBOX_HpOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if( !m_pID_FRAME_PkSet )
		return;
    GameSetting::Instance()->SetLevel( GameSetting::eGSC_SelfHp, m_pID_CHECKBOX_Hp->IsChecked() );
    GameSetting::Instance()->SetLevel( GameSetting::eGSC_TeamPlayerHp, m_pID_CHECKBOX_Hp->IsChecked() );
    GameSetting::Instance()->SetLevel( GameSetting::eGSC_OtherPlayerHp, m_pID_CHECKBOX_Hp->IsChecked() );
    GameSetting::Instance()->CommitChanges();
    // 更新游戏设置界面
    s_CUI_ID_FRAME_GameSettingPlayer.RefreshUI();
    s_CUI_ID_FRAME_GameSettingSelf.RefreshUI();
}
// CheckBox
void CUI_ID_FRAME_PkSet::ID_CHECKBOX_MpOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if( !m_pID_FRAME_PkSet )
		return;
    GameSetting::Instance()->SetLevel( GameSetting::eGSC_SelfMp, m_pID_CHECKBOX_Mp->IsChecked() );	
    GameSetting::Instance()->CommitChanges();
    // 更新游戏设置界面
    s_CUI_ID_FRAME_GameSettingSelf.RefreshUI();
}
// CheckBox
void CUI_ID_FRAME_PkSet::ID_CHECKBOX_DanderOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if( !m_pID_FRAME_PkSet )
		return;
}

	// 装载UI
bool CUI_ID_FRAME_PkSet::_LoadUI()
{
// 	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\PkSet.MEUI", false, UI_Render_LayerThree );
// 	if ( dwResult == 0 )
// 	{
// 		MESSAGE_BOX("读取文件[Data\\UI\\PkSet.MEUI]失败")
// 		return false;
// 	}
// 	return DoControlConnect();
	return true;
}
// 关连控件
bool CUI_ID_FRAME_PkSet::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_PkSet, s_CUI_ID_FRAME_PkSetOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_PkSet, s_CUI_ID_FRAME_PkSetOnFrameRender );
    theUiManager.OnCheckBoxCheck( ID_FRAME_PkSet, ID_CHECKBOX_Sworn, s_CUI_ID_FRAME_PkSetID_CHECKBOX_SwornOnCheckBoxCheck );
    theUiManager.OnCheckBoxCheck( ID_FRAME_PkSet, ID_CHECKBOX_Guild, s_CUI_ID_FRAME_PkSetID_CHECKBOX_GuildOnCheckBoxCheck );
    theUiManager.OnCheckBoxCheck( ID_FRAME_PkSet, ID_CHECKBOX_League, s_CUI_ID_FRAME_PkSetID_CHECKBOX_LeagueOnCheckBoxCheck );
    theUiManager.OnCheckBoxCheck( ID_FRAME_PkSet, ID_CHECKBOX_All, s_CUI_ID_FRAME_PkSetID_CHECKBOX_AllOnCheckBoxCheck );
    theUiManager.OnScrollBarExUpdatePos( ID_FRAME_PkSet, ID_SCROLLBAREX_Lvl, s_CUI_ID_FRAME_PkSetID_SCROLLBAREX_LvlOnScrollBarExUpdatePos );
    theUiManager.OnCheckBoxCheck( ID_FRAME_PkSet, ID_CHECKBOX_Hp, s_CUI_ID_FRAME_PkSetID_CHECKBOX_HpOnCheckBoxCheck );
    theUiManager.OnCheckBoxCheck( ID_FRAME_PkSet, ID_CHECKBOX_Mp, s_CUI_ID_FRAME_PkSetID_CHECKBOX_MpOnCheckBoxCheck );
    theUiManager.OnCheckBoxCheck( ID_FRAME_PkSet, ID_CHECKBOX_Dander, s_CUI_ID_FRAME_PkSetID_CHECKBOX_DanderOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_PkSet, ID_CHECKBOX_Red, s_CUI_ID_FRAME_PkSetID_CHECKBOX_RedOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_PkSet, ID_CHECKBOX_White, s_CUI_ID_FRAME_PkSetID_CHECKBOX_WhiteOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_PkSet, ID_CHECKBOX_Blue, s_CUI_ID_FRAME_PkSetID_CHECKBOX_BlueOnCheckBoxCheck );

	m_pID_FRAME_PkSet = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_PkSet );
	m_pID_PICTURE_ImageWall = (ControlPicture*)theUiManager.FindControl( ID_FRAME_PkSet, ID_PICTURE_ImageWall );
	m_pID_TEXT_Sworn = (ControlText*)theUiManager.FindControl( ID_FRAME_PkSet, ID_TEXT_Sworn );
	m_pID_TEXT_Guild = (ControlText*)theUiManager.FindControl( ID_FRAME_PkSet, ID_TEXT_Guild );
	m_pID_TEXT_All = (ControlText*)theUiManager.FindControl( ID_FRAME_PkSet, ID_TEXT_All );
	m_pID_TEXT_League = (ControlText*)theUiManager.FindControl( ID_FRAME_PkSet, ID_TEXT_League );
	m_pID_CHECKBOX_Sworn = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_PkSet, ID_CHECKBOX_Sworn );
	m_pID_CHECKBOX_Guild = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_PkSet, ID_CHECKBOX_Guild );
	m_pID_CHECKBOX_League = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_PkSet, ID_CHECKBOX_League );
	m_pID_CHECKBOX_All = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_PkSet, ID_CHECKBOX_All );
	m_pID_PICTURE_30013 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_PkSet, ID_PICTURE_30013 );
	m_pID_PICTURE_13560 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_PkSet, ID_PICTURE_13560 );
	m_pID_PICTURE_25141 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_PkSet, ID_PICTURE_25141 );
	m_pID_PICTURE_32481 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_PkSet, ID_PICTURE_32481 );
	m_pID_TEXT_Lvl = (ControlText*)theUiManager.FindControl( ID_FRAME_PkSet, ID_TEXT_Lvl );
	m_pID_SCROLLBAREX_Lvl = (ControlScrollBarEx*)theUiManager.FindControl( ID_FRAME_PkSet, ID_SCROLLBAREX_Lvl );
	m_pID_CHECKBOX_Hp = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_PkSet, ID_CHECKBOX_Hp );
	m_pID_CHECKBOX_Mp = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_PkSet, ID_CHECKBOX_Mp );
	m_pID_CHECKBOX_Dander = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_PkSet, ID_CHECKBOX_Dander );
	m_pID_TEXT_Hp = (ControlText*)theUiManager.FindControl( ID_FRAME_PkSet, ID_TEXT_Hp );
	m_pID_TEXT_Mp = (ControlText*)theUiManager.FindControl( ID_FRAME_PkSet, ID_TEXT_Mp );
	m_pID_TEXT_Dander = (ControlText*)theUiManager.FindControl( ID_FRAME_PkSet, ID_TEXT_Dander );
	m_pID_CHECKBOX_Red = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_PkSet, ID_CHECKBOX_Red );
	m_pID_CHECKBOX_White = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_PkSet, ID_CHECKBOX_White );
	m_pID_CHECKBOX_Blue = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_PkSet, ID_CHECKBOX_Blue );
	m_pID_TEXT_Red = (ControlText*)theUiManager.FindControl( ID_FRAME_PkSet, ID_TEXT_Red );
	m_pID_TEXT_White = (ControlText*)theUiManager.FindControl( ID_FRAME_PkSet, ID_TEXT_White );
	m_pID_TEXT_Blue = (ControlText*)theUiManager.FindControl( ID_FRAME_PkSet, ID_TEXT_Blue );
	assert( m_pID_FRAME_PkSet );
	assert( m_pID_PICTURE_ImageWall );
	assert( m_pID_TEXT_Sworn );
	assert( m_pID_TEXT_Guild );
	assert( m_pID_TEXT_All );
	assert( m_pID_TEXT_League );
	assert( m_pID_CHECKBOX_Sworn );
	assert( m_pID_CHECKBOX_Guild );
	assert( m_pID_CHECKBOX_League );
	assert( m_pID_CHECKBOX_All );
	assert( m_pID_PICTURE_30013 );
	assert( m_pID_PICTURE_13560 );
	assert( m_pID_PICTURE_25141 );
	assert( m_pID_PICTURE_32481 );
	assert( m_pID_TEXT_Lvl );
	assert( m_pID_SCROLLBAREX_Lvl );
	assert( m_pID_CHECKBOX_Hp );
	assert( m_pID_CHECKBOX_Mp );
	assert( m_pID_CHECKBOX_Dander );
	assert( m_pID_TEXT_Hp );
	assert( m_pID_TEXT_Mp );
	assert( m_pID_TEXT_Dander );
	assert( m_pID_CHECKBOX_Red );
	assert( m_pID_CHECKBOX_White );
	assert( m_pID_CHECKBOX_Blue );
	assert( m_pID_TEXT_Red );
	assert( m_pID_TEXT_White );
	assert( m_pID_TEXT_Blue );
	pCheck[PK_TeamProtect] = m_pID_CHECKBOX_Sworn;
	m_pID_CHECKBOX_Sworn->SetCheck(true);
	m_pID_CHECKBOX_Sworn->SetEnable(false);
	pCheck[PK_GuildProtect] = m_pID_CHECKBOX_Guild;
	pCheck[PK_LeagueProtect] = m_pID_CHECKBOX_League;
	pCheck[PK_AllProtect] = m_pID_CHECKBOX_All;

    m_pID_SCROLLBAREX_Lvl->SetMaxValue(PK_AllProtect);
    m_pID_SCROLLBAREX_Lvl->SetStepValue(1);

    m_pID_FRAME_PkSet->SetMsgHoldup(false);  // 不接收消息

    SetVisable(false);
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_PkSet::_UnLoadUI()
{
// 	ResetMembers();
// 	return theUiManager.RemoveFrame( "Data\\UI\\PkSet.MEUI" );
	return true;
}
// 是否可视
bool CUI_ID_FRAME_PkSet::_IsVisable()
{
	if( !m_pID_FRAME_PkSet )
		return false;
	return m_pID_FRAME_PkSet->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_PkSet::_SetVisable( const bool bVisable )
{
	if( !m_pID_FRAME_PkSet )
		return;
    m_pID_FRAME_PkSet->SetVisable( bVisable );
	if (bVisable)
	{
		CPlayer* pMe = theHeroGame.GetPlayerMgr()->GetMe();
		if( !pMe )
			return;
		stPkTrueLevel = pMe->GetPKType();
		m_nPkLevel = stPkTrueLevel&0x0F;
		RefreshUI();
        RefreshHpMpUI();
	}

}
void CUI_ID_FRAME_PkSet::RefreshUI()
{
	for (int i = PK_GuildProtect;i < m_nPkLevel; ++i)
	{
		pCheck[i]->SetCheck(true);
		pCheck[i]->SetEnable(false);
	}
	if (pCheck[m_nPkLevel] && m_nPkLevel != PK_TeamProtect)
	{
		pCheck[m_nPkLevel]->SetCheck(true);
		pCheck[m_nPkLevel]->SetEnable(true);
	}		
	for (int i = m_nPkLevel + 1;i < PK_Protect_Total; ++i)
	{
		pCheck[i]->SetCheck(false);
		pCheck[i]->SetEnable(true);
	}
	if (m_pID_SCROLLBAREX_Lvl->GetValue() != m_nPkLevel)
	{
		m_pID_SCROLLBAREX_Lvl->SetValue(m_nPkLevel);
	}

	if (m_nPkLevel == PK_AllProtect)
	{
		m_pID_CHECKBOX_Red->SetEnable(false);
		m_pID_CHECKBOX_White->SetEnable(false);
		m_pID_CHECKBOX_Blue->SetEnable(false);
	}
	else
	{
		m_pID_CHECKBOX_Red->SetEnable(true);
		m_pID_CHECKBOX_White->SetEnable(true);
		m_pID_CHECKBOX_Blue->SetEnable(true);
		m_pID_CHECKBOX_Red->SetCheck(stPkTrueLevel & PK_RedProtect);
		m_pID_CHECKBOX_White->SetCheck(stPkTrueLevel & PK_WhiteProtect);
		m_pID_CHECKBOX_Blue->SetCheck(stPkTrueLevel & PK_BlueProtect);	
	}
}

void CUI_ID_FRAME_PkSet::SendMessage()
{
	MsgChangePKFlag flag;
	stPkTrueLevel = m_nPkLevel;
	if (m_pID_CHECKBOX_Red->IsChecked())
	{
		stPkTrueLevel |= PK_RedProtect;
	}
	if (m_pID_CHECKBOX_White->IsChecked())
	{
		stPkTrueLevel |= PK_WhiteProtect;
	}
	if (m_pID_CHECKBOX_Blue->IsChecked())
	{
		stPkTrueLevel |= PK_BlueProtect;
	}
	flag.shFlag = stPkTrueLevel;
	
	GettheNetworkInput().SendMsg( &flag );

}

void CUI_ID_FRAME_PkSet::ID_CHECKBOX_RedOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if (*pbChecked)
	{
		stPkTrueLevel |= PK_RedProtect;
	}
	else
	{
		stPkTrueLevel &= ~PK_RedProtect;
	}
	

}

void CUI_ID_FRAME_PkSet::ID_CHECKBOX_WhiteOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if (*pbChecked)
	{
		stPkTrueLevel |= PK_WhiteProtect;
	}
	else
	{
		stPkTrueLevel &= ~PK_WhiteProtect;
	}

}

void CUI_ID_FRAME_PkSet::ID_CHECKBOX_BlueOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if (*pbChecked)
	{
		stPkTrueLevel |= PK_BlueProtect;
	}
	else
	{
		stPkTrueLevel &= ~PK_BlueProtect;
	}

}

void CUI_ID_FRAME_PkSet::RefreshHpMpUI()
{
	if( !m_pID_FRAME_PkSet )
		return;
    if( GameSetting::Instance()->GetLevel( GameSetting::eGSC_SelfHp )
        && GameSetting::Instance()->GetLevel( GameSetting::eGSC_TeamPlayerHp )
        && GameSetting::Instance()->GetLevel( GameSetting::eGSC_OtherPlayerHp ) )
        m_pID_CHECKBOX_Hp->SetCheck( true );
    else
        m_pID_CHECKBOX_Hp->SetCheck( false );

    m_pID_CHECKBOX_Mp->SetCheck( GameSetting::Instance()->GetLevel( GameSetting::eGSC_SelfMp ) );
}

bool CUI_ID_FRAME_PkSet::SetFrameFather( ControlObject* pFather )
{
	if( !m_pID_FRAME_PkSet || !pFather )
		return false;
	m_pID_FRAME_PkSet->SetFather(pFather);
	return true;
}