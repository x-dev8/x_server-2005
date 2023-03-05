#include <assert.h>
#include "MeUi/UiManager.h"
#include "SettingEffect.h"
#include "SettingCustom.h"
#include "SystemSetting.h"
#include "GameSetting.h"
#include "Common.h"
#include "XmlStringLanguage.h"
#include "Me3d\Global.h"
#include "UserData.h"
#include "GameSettingUI.h"
#include "customShortcutKey.h"
#include "MiniMapUI.h"
#include "GameSettingBgFrame.h"
#include "GameMain.h"

extern CHeroGame theHeroGame;

int CUI_ID_FRAME_SettingEffect::m_ScreenValue = 0;

CUI_ID_FRAME_SettingEffect s_CUI_ID_FRAME_SettingEffect;

MAP_FRAME_RUN( s_CUI_ID_FRAME_SettingEffect, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_SettingEffect, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SettingEffect, ID_BUTTON_OKOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SettingEffect, ID_BUTTON_CancelOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SettingEffect, ID_BUTTON_DefaultOnButtonClick )
MAP_SCROLL_BAREX_UPDATE_POS_CALLBACK( s_CUI_ID_FRAME_SettingEffect, ID_SCROLLBAREX_MusicOnScrollBarExUpdatePos )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SettingEffect, ID_BUTTON_SetHighOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SettingEffect, ID_BUTTON_SetMiddleOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SettingEffect, ID_BUTTON_SetLowOnButtonClick )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_SettingEffect, ID_CHECKBOX_WindowOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_SettingEffect, ID_CHECKBOX_FullScreenOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_SettingEffect, ID_CHECKBOX_NoMusicOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_SettingEffect, ID_CHECKBOX_NoSoundEffectOnCheckBoxCheck )
// MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SettingEffect, ID_BUTTON_CLOSEOnButtonClick )
// MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SettingEffect, ID_BUTTON_HELPOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SettingEffect, ID_BUTTON_CustomOnButtonClick )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_SettingEffect, ID_LIST_23209OnListSelectChange )
MAP_SCROLL_BAREX_UPDATE_POS_CALLBACK( s_CUI_ID_FRAME_SettingEffect, ID_SCROLLBAREX_SoundEffectOnScrollBarExUpdatePos )
MAP_SCROLL_BAREX_UPDATE_POS_CALLBACK( s_CUI_ID_FRAME_SettingEffect, ID_SCROLLBAREX_TongPingOnScrollBarExUpdatePos )
MAP_SCROLL_BAREX_UPDATE_POS_CALLBACK( s_CUI_ID_FRAME_SettingEffect, ID_SCROLLBAREX_GuangJiaoOnScrollBarExUpdatePos )
MAP_SCROLL_BAREX_UPDATE_POS_CALLBACK( s_CUI_ID_FRAME_SettingEffect, ID_SCROLLBAREX_JingTouOnScrollBarExUpdatePos )
// MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_SettingEffect, ID_CHECKBOX_EffectOnCheckBoxCheck )
// MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_SettingEffect, ID_CHECKBOX_GamePlayOnCheckBoxCheck )
// MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_SettingEffect, ID_CHECKBOX_ShortcutKeyOnCheckBoxCheck )
MAP_COMBO_BOX_CHANGE_CALLBACK( s_CUI_ID_FRAME_SettingEffect, ID_COMBOBOX_MSOnComboboxChange)
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_SettingEffect, ID_CHECKBOX_CameraShakeOnCheckBoxCheck )

CUI_ID_FRAME_SettingEffect::CUI_ID_FRAME_SettingEffect()
{
	// Member
	m_pID_FRAME_SettingEffect = NULL;
	m_pID_BUTTON_OK = NULL;
	m_pID_BUTTON_Cancel = NULL;
	m_pID_BUTTON_Default = NULL;
	m_pID_TEXT_Mode = NULL;
	m_pID_SCROLLBAREX_Music = NULL;
	m_pID_BUTTON_SetHigh = NULL;
	m_pID_BUTTON_SetMiddle = NULL;
	m_pID_BUTTON_SetLow = NULL;
	m_pID_CHECKBOX_Window = NULL;
	m_pID_CHECKBOX_FullScreen = NULL;
	m_pID_CHECKBOX_NoMusic = NULL;
	m_pID_CHECKBOX_NoSoundEffect = NULL;
	//m_pID_BUTTON_CLOSE = NULL;
	//m_pID_BUTTON_HELP = NULL;
	m_pID_BUTTON_Custom = NULL;
	m_pID_LIST_23209 = NULL;
	m_pID_SCROLLBAREX_SoundEffect = NULL;
	m_pID_PICTURE_7314 = NULL;
	m_pID_SCROLLBAREX_TongPing = NULL;
	m_pID_SCROLLBAREX_GuangJiao = NULL;
	m_pID_SCROLLBAREX_JingTou = NULL;
// 	m_pID_CHECKBOX_Effect = NULL;
// 	m_pID_CHECKBOX_GamePlay = NULL;
// 	m_pID_CHECKBOX_ShortcutKey = NULL;
	m_pID_TEXT_23801231233 = NULL;
	m_pID_TEXT_23821312303 = NULL;
	m_pID_TEXT_212313803 = NULL;
	m_pID_TEXT_238031231 = NULL;
	m_pID_TEXT_238031233 = NULL;
	m_pID_COMBOBOX_MultiSample = NULL;
	m_pID_CHECKBOX_CameraShake = NULL;

}
// Frame
bool CUI_ID_FRAME_SettingEffect::OnFrameRun()
{
	return true;
}
bool CUI_ID_FRAME_SettingEffect::OnFrameRender()
{
	return true;
}
// Button
bool CUI_ID_FRAME_SettingEffect::ID_BUTTON_OKOnButtonClick( ControlObject* pSender )
{
	//设置窗口模式
	if (m_pID_CHECKBOX_Window != NULL &&m_pID_CHECKBOX_FullScreen != NULL)
	{
		if (m_pID_CHECKBOX_Window->IsChecked())
		{
			SystemSetting::Instance()->SetLevel( SystemSetting::eSSC_WINDOWMODE, true );
			SystemSetting::Instance()->CommitChanges();
		}
		else if (m_pID_CHECKBOX_FullScreen ->IsChecked())
		{
			SystemSetting::Instance()->SetLevel( SystemSetting::eSSC_WINDOWMODE, false );
			SystemSetting::Instance()->CommitChanges();
		}		
	}
	//设置窗口分辨率
	if (m_ScreenValue != 0)
	{
		SystemSetting::Instance()->SetLevel( SystemSetting::eSSC_RESOLUTION, m_ScreenValue );
		SystemSetting::Instance()->CommitChanges();
	}
	char szSetting[MAX_PATH] = {0};
	MeSprintf_s( szSetting, sizeof(szSetting)/sizeof(char) - 1, "%s%s", CUserData::Instance()->GetUserDataPath(), GameSetting::Instance()->GetCustomSettingDirectory() );
	GameSetting::Instance()->SaveSetting( szSetting );

	MeSprintf_s(szSetting,sizeof(szSetting)/sizeof(char) - 1, "%s/Client/UserData/%s", GetRootPath(), SystemSetting::Instance()->GetCustomSettingFile() );
	SystemSetting::Instance()->SaveSetting( szSetting );	
	SetVisable(false);
	s_CUI_ID_FRAME_GameSettingBgFrame._SetVisable(false);
	return true;
}

// Button
bool CUI_ID_FRAME_SettingEffect::ID_BUTTON_CancelOnButtonClick( ControlObject* pSender )
{
	char szSetting[MAX_PATH] = {0};
	MeSprintf_s( szSetting, sizeof(szSetting)/sizeof(char) - 1, "%s%s", CUserData::Instance()->GetUserDataPath(), GameSetting::Instance()->GetCustomSettingDirectory() );
	GameSetting::Instance()->LoadSetting( szSetting );
	GameSetting::Instance()->CommitChanges();

	MeSprintf_s(szSetting,sizeof(szSetting)/sizeof(char) - 1, "%s/Client/UserData/%s", GetRootPath(), SystemSetting::Instance()->GetCustomSettingFile() );
	SystemSetting::Instance()->LoadSetting( szSetting );	
	SystemSetting::Instance()->CommitChanges();
	SetVisable(false);
	s_CUI_ID_FRAME_GameSettingBgFrame._SetVisable(false);
	return true;
}

// Button
bool CUI_ID_FRAME_SettingEffect::ID_BUTTON_DefaultOnButtonClick( ControlObject* pSender )
{
	GameSetting::Instance()->LoadSetting();
	SystemSetting::Instance()->LoadSetting();
	GameSetting::Instance()->CommitChanges();
	SystemSetting::Instance()->CommitChanges();
	return true;
}
// ScrollBarEx
void CUI_ID_FRAME_SettingEffect::ID_SCROLLBAREX_MusicOnScrollBarExUpdatePos( ControlObject* pSender, int n )
{
	if(!m_pID_FRAME_SettingEffect)
		return;

	int nFinalValue = GameSetting::Instance()->MakeSoundValue( n, m_pID_CHECKBOX_NoMusic->IsChecked() );

	GameSetting::Instance()->SetLevel( GameSetting::eGSC_SOUND, nFinalValue );
	GameSetting::Instance()->CommitChanges();

}

// Button
bool CUI_ID_FRAME_SettingEffect::ID_BUTTON_SetHighOnButtonClick( ControlObject* pSender )
{
	LoadQuilityConfig(eQuility_High);
	theHeroGame.SetSlowCPU(0);
	return true;
}
// Button
bool CUI_ID_FRAME_SettingEffect::ID_BUTTON_SetMiddleOnButtonClick( ControlObject* pSender )
{
	LoadQuilityConfig(eQuility_Middle);
	theHeroGame.SetSlowCPU(1);
	return true;
}
// Button
bool CUI_ID_FRAME_SettingEffect::ID_BUTTON_SetLowOnButtonClick( ControlObject* pSender )
{
	LoadQuilityConfig(eQuility_Low);
	theHeroGame.SetSlowCPU(1);
	return true;
}
// CheckBox
void CUI_ID_FRAME_SettingEffect::ID_CHECKBOX_WindowOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if( !m_pID_FRAME_SettingEffect )
		return;

	m_pID_CHECKBOX_Window->SetCheck(true);
	m_pID_CHECKBOX_FullScreen->SetCheck(false);

// 	SystemSetting::Instance()->SetLevel( SystemSetting::eSSC_WINDOWMODE, true);
// 	SystemSetting::Instance()->CommitChanges()
}
// CheckBox
void CUI_ID_FRAME_SettingEffect::ID_CHECKBOX_FullScreenOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if(!m_pID_FRAME_SettingEffect)
		return;

	m_pID_CHECKBOX_FullScreen->SetCheck(true);
	m_pID_CHECKBOX_Window->SetCheck(false);

// 	SystemSetting::Instance()->SetLevel( SystemSetting::eSSC_WINDOWMODE, false  );
// 	SystemSetting::Instance()->CommitChanges()
}

// CheckBox
void CUI_ID_FRAME_SettingEffect::ID_CHECKBOX_NoMusicOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if(!m_pID_FRAME_SettingEffect)
		return;

	int nFinalValue = GameSetting::Instance()->MakeSoundValue( m_pID_SCROLLBAREX_Music->GetValue(), *pbChecked );

	GameSetting::Instance()->SetLevel( GameSetting::eGSC_SOUND, nFinalValue );
	GameSetting::Instance()->CommitChanges();
	
}
// CheckBox
void CUI_ID_FRAME_SettingEffect::ID_CHECKBOX_NoSoundEffectOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if(!m_pID_FRAME_SettingEffect)
		return;

	int nFinalValue = GameSetting::Instance()->MakeSoundValue( m_pID_SCROLLBAREX_SoundEffect->GetValue(), *pbChecked );

	GameSetting::Instance()->SetLevel( GameSetting::eGSC_SOUNDEFFECT, nFinalValue );
	GameSetting::Instance()->CommitChanges();
}
// Button
// bool CUI_ID_FRAME_SettingEffect::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
// {
// 	if( !m_pID_FRAME_SettingEffect )
// 		return false;

// 	char szSetting[MAX_PATH] = {0};
// 	MeSprintf_s(szSetting,sizeof(szSetting)/sizeof(char) - 1, "%s/Client/UserData/%s", GetRootPath(), SystemSetting::Instance()->GetCustomSettingFile() );
// 
// 	SystemSetting::Instance()->LoadSetting( szSetting );
// 	SystemSetting::Instance()->CommitChanges();
// 	Refresh();
// 	SetVisable( FALSE );
// 	return true;
// }
// Button
bool CUI_ID_FRAME_SettingEffect::ID_BUTTON_CustomOnButtonClick( ControlObject* pSender )
{
	LoadQuilityConfig(eQuility_Custom);
	return true;
}
// bool CUI_ID_FRAME_SettingEffect::ID_BUTTON_HELPOnButtonClick(ControlObject* pSender)
// {
// 	return true;
// }
// List
void CUI_ID_FRAME_SettingEffect::ID_LIST_23209OnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
}
// ScrollBarEx
void CUI_ID_FRAME_SettingEffect::ID_SCROLLBAREX_SoundEffectOnScrollBarExUpdatePos( ControlObject* pSender, int n )
{
	if(!m_pID_FRAME_SettingEffect)
		return;

	int nFinalValue = GameSetting::Instance()->MakeSoundValue( n, m_pID_CHECKBOX_NoSoundEffect->IsChecked() );

	GameSetting::Instance()->SetLevel( GameSetting::eGSC_SOUNDEFFECT, nFinalValue );
	GameSetting::Instance()->CommitChanges();
}
// ScrollBarEx
void CUI_ID_FRAME_SettingEffect::ID_SCROLLBAREX_TongPingOnScrollBarExUpdatePos( ControlObject* pSender, int n )
{
	if ( !m_pID_FRAME_SettingEffect )
		return;
	//n = n / 4 + 30;//[30 - 280]
	GameSetting::Instance()->SetLevel( GameSetting::eGSC_SHOWPLAYERNUMBER, n );
	GameSetting::Instance()->CommitChanges();
	m_pID_SCROLLBAREX_TongPing->SetCustomValue( n );
	s_CUI_ID_FRAME_MiniMap.SetButtonToCustom();
}
// ScrollBarEx
void CUI_ID_FRAME_SettingEffect::ID_SCROLLBAREX_GuangJiaoOnScrollBarExUpdatePos( ControlObject* pSender, int n )
{
	if ( !m_pID_FRAME_SettingEffect )
		return;
	GameSetting::Instance()->SetLevel( GameSetting::eGSC_FOV, n );
	GameSetting::Instance()->CommitChanges();
	m_pID_SCROLLBAREX_GuangJiao->SetCustomValue(n);
}
void CUI_ID_FRAME_SettingEffect::ID_SCROLLBAREX_JingTouOnScrollBarExUpdatePos( ControlObject* pSender, int n )
{
	if ( !m_pID_FRAME_SettingEffect )
		return;
	GameSetting::Instance()->SetLevel( GameSetting::eGSC_MAXCAMERADISTANCE,  n );
	GameSetting::Instance()->CommitChanges();
	m_pID_SCROLLBAREX_JingTou->SetCustomValue(n);
}
// CheckBox
// void CUI_ID_FRAME_SettingEffect::ID_CHECKBOX_EffectOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
// {
// 	if ( !m_pID_FRAME_SettingEffect )
// 		return;
// 	s_CUI_ID_FRAME_SettingEffect.SetVisable(true);
// 	s_CUI_ID_FRAME_GameSetup.SetVisable(false);
// 	s_CUI_ID_FRAME_custom.SetVisable(false);
// }
// // CheckBox
// void CUI_ID_FRAME_SettingEffect::ID_CHECKBOX_GamePlayOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
// {
// 	if ( !m_pID_FRAME_SettingEffect )
// 		return;
// 	s_CUI_ID_FRAME_GameSetup.SetVisable(true);
// 	//s_CUI_ID_FRAME_SettingEffect.SetVisable(false);
// 	s_CUI_ID_FRAME_custom.SetVisable(false);
// }
// // CheckBox
// void CUI_ID_FRAME_SettingEffect::ID_CHECKBOX_ShortcutKeyOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
// {
// 	if ( !m_pID_FRAME_SettingEffect )
// 		return;
// 	s_CUI_ID_FRAME_custom.SetVisable(true);
// 	//s_CUI_ID_FRAME_SettingEffect.SetVisable(false);
// 	s_CUI_ID_FRAME_GameSetup.SetVisable(false);
// }

void CUI_ID_FRAME_SettingEffect::ID_COMBOBOX_MSOnComboboxChange(ControlObject* pSender, const char* szData)
{
	if (strstr(szData, "关闭") != NULL)
	{
		SystemSetting::Instance()->SetLevel(SystemSetting::eSSC_MSAA, 0);
	}
	else
	{
		int sample = 2;
		sscanf(szData, "%dx", &sample);
		SystemSetting::Instance()->SetLevel(SystemSetting::eSSC_MSAA, sample);
	}
	SystemSetting::Instance()->CommitChanges();
}

void CUI_ID_FRAME_SettingEffect::ID_CHECKBOX_CameraShakeOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if (m_pID_CHECKBOX_CameraShake->IsChecked())
		SystemSetting::Instance()->SetLevel(SystemSetting::eSSC_CameraShake, 1);
	else
		SystemSetting::Instance()->SetLevel(SystemSetting::eSSC_CameraShake, 0);
}

void CUI_ID_FRAME_SettingEffect::GetItemTextByMSAALevel(int msaaLevel, char *szItemText)
{
	if (msaaLevel == 0)
		strcpy(szItemText, "关闭");
	else
		sprintf(szItemText, "%dx", msaaLevel);
}

// 装载UI
bool CUI_ID_FRAME_SettingEffect::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\SettingEffect.MEUI", false, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\SettingEffect.MEUI]失败")
			return false;
	}
	s_CUI_ID_FRAME_SettingCustom.LoadUI();
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_SettingEffect::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_SettingEffect, s_CUI_ID_FRAME_SettingEffectOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_SettingEffect, s_CUI_ID_FRAME_SettingEffectOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_SettingEffect, ID_BUTTON_OK, s_CUI_ID_FRAME_SettingEffectID_BUTTON_OKOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SettingEffect, ID_BUTTON_Cancel, s_CUI_ID_FRAME_SettingEffectID_BUTTON_CancelOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SettingEffect, ID_BUTTON_Default, s_CUI_ID_FRAME_SettingEffectID_BUTTON_DefaultOnButtonClick );
	theUiManager.OnScrollBarExUpdatePos( ID_FRAME_SettingEffect, ID_SCROLLBAREX_Music, s_CUI_ID_FRAME_SettingEffectID_SCROLLBAREX_MusicOnScrollBarExUpdatePos );
	theUiManager.OnButtonClick( ID_FRAME_SettingEffect, ID_BUTTON_SetHigh, s_CUI_ID_FRAME_SettingEffectID_BUTTON_SetHighOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SettingEffect, ID_BUTTON_SetMiddle, s_CUI_ID_FRAME_SettingEffectID_BUTTON_SetMiddleOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SettingEffect, ID_BUTTON_SetLow, s_CUI_ID_FRAME_SettingEffectID_BUTTON_SetLowOnButtonClick );
	theUiManager.OnCheckBoxCheck( ID_FRAME_SettingEffect, ID_CHECKBOX_Window, s_CUI_ID_FRAME_SettingEffectID_CHECKBOX_WindowOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_SettingEffect, ID_CHECKBOX_FullScreen, s_CUI_ID_FRAME_SettingEffectID_CHECKBOX_FullScreenOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_SettingEffect, ID_CHECKBOX_NoMusic, s_CUI_ID_FRAME_SettingEffectID_CHECKBOX_NoMusicOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_SettingEffect, ID_CHECKBOX_NoSoundEffect, s_CUI_ID_FRAME_SettingEffectID_CHECKBOX_NoSoundEffectOnCheckBoxCheck );
/*	theUiManager.OnButtonClick( ID_FRAME_SettingEffect, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_SettingEffectID_BUTTON_CLOSEOnButtonClick );*/
	theUiManager.OnButtonClick( ID_FRAME_SettingEffect, ID_BUTTON_Custom, s_CUI_ID_FRAME_SettingEffectID_BUTTON_CustomOnButtonClick );
	theUiManager.OnListSelectChange( ID_FRAME_SettingEffect, ID_LIST_23209, s_CUI_ID_FRAME_SettingEffectID_LIST_23209OnListSelectChange );
	theUiManager.OnScrollBarExUpdatePos( ID_FRAME_SettingEffect, ID_SCROLLBAREX_SoundEffect, s_CUI_ID_FRAME_SettingEffectID_SCROLLBAREX_SoundEffectOnScrollBarExUpdatePos );
	theUiManager.OnScrollBarExUpdatePos( ID_FRAME_SettingEffect, ID_SCROLLBAREX_TongPing, s_CUI_ID_FRAME_SettingEffectID_SCROLLBAREX_TongPingOnScrollBarExUpdatePos );
	theUiManager.OnScrollBarExUpdatePos( ID_FRAME_SettingEffect, ID_SCROLLBAREX_GuangJiao, s_CUI_ID_FRAME_SettingEffectID_SCROLLBAREX_GuangJiaoOnScrollBarExUpdatePos );
	theUiManager.OnScrollBarExUpdatePos( ID_FRAME_SettingEffect, ID_SCROLLBAREX_JingTou, s_CUI_ID_FRAME_SettingEffectID_SCROLLBAREX_JingTouOnScrollBarExUpdatePos );
// 	theUiManager.OnCheckBoxCheck( ID_FRAME_SettingEffect, ID_CHECKBOX_Effect, s_CUI_ID_FRAME_SettingEffectID_CHECKBOX_EffectOnCheckBoxCheck );
// 	theUiManager.OnCheckBoxCheck( ID_FRAME_SettingEffect, ID_CHECKBOX_GamePlay, s_CUI_ID_FRAME_SettingEffectID_CHECKBOX_GamePlayOnCheckBoxCheck );
// 	theUiManager.OnCheckBoxCheck( ID_FRAME_SettingEffect, ID_CHECKBOX_ShortcutKey, s_CUI_ID_FRAME_SettingEffectID_CHECKBOX_ShortcutKeyOnCheckBoxCheck );
	theUiManager.OnComboBoxChange( ID_FRAME_SettingEffect, ID_COMBOBOX_MS, s_CUI_ID_FRAME_SettingEffectID_COMBOBOX_MSOnComboboxChange );
	theUiManager.OnCheckBoxCheck( ID_FRAME_SettingEffect, ID_CHECKBOX_CAMERA_SHAKE, s_CUI_ID_FRAME_SettingEffectID_CHECKBOX_CameraShakeOnCheckBoxCheck );

	m_pID_FRAME_SettingEffect = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_SettingEffect );
	m_pID_BUTTON_OK = (ControlButton*)theUiManager.FindControl( ID_FRAME_SettingEffect, ID_BUTTON_OK );
	m_pID_BUTTON_Cancel = (ControlButton*)theUiManager.FindControl( ID_FRAME_SettingEffect, ID_BUTTON_Cancel );
	m_pID_BUTTON_Default = (ControlButton*)theUiManager.FindControl( ID_FRAME_SettingEffect, ID_BUTTON_Default );
	m_pID_TEXT_Mode = (ControlText*)theUiManager.FindControl( ID_FRAME_SettingEffect, ID_TEXT_Mode );
	m_pID_SCROLLBAREX_Music = (ControlScrollBarEx*)theUiManager.FindControl( ID_FRAME_SettingEffect, ID_SCROLLBAREX_Music );
	m_pID_BUTTON_SetHigh = (ControlButton*)theUiManager.FindControl( ID_FRAME_SettingEffect, ID_BUTTON_SetHigh );
	m_pID_BUTTON_SetMiddle = (ControlButton*)theUiManager.FindControl( ID_FRAME_SettingEffect, ID_BUTTON_SetMiddle );
	m_pID_BUTTON_SetLow = (ControlButton*)theUiManager.FindControl( ID_FRAME_SettingEffect, ID_BUTTON_SetLow );
	m_pID_CHECKBOX_Window = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_SettingEffect, ID_CHECKBOX_Window );
	m_pID_CHECKBOX_FullScreen = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_SettingEffect, ID_CHECKBOX_FullScreen );
	m_pID_CHECKBOX_NoMusic = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_SettingEffect, ID_CHECKBOX_NoMusic );
	m_pID_CHECKBOX_NoSoundEffect = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_SettingEffect, ID_CHECKBOX_NoSoundEffect );
	//m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_FRAME_SettingEffect, ID_BUTTON_CLOSE );
	//m_pID_BUTTON_HELP = (ControlButton*)theUiManager.FindControl( ID_FRAME_SettingEffect, ID_BUTTON_HELP );
	m_pID_BUTTON_Custom = (ControlButton*)theUiManager.FindControl( ID_FRAME_SettingEffect, ID_BUTTON_Custom );
	m_pID_LIST_23209 = (ControlList*)theUiManager.FindControl( ID_FRAME_SettingEffect, ID_LIST_23209 );
	m_pID_SCROLLBAREX_SoundEffect = (ControlScrollBarEx*)theUiManager.FindControl( ID_FRAME_SettingEffect, ID_SCROLLBAREX_SoundEffect );
	m_pID_SCROLLBAREX_TongPing = (ControlScrollBarEx*)theUiManager.FindControl( ID_FRAME_SettingEffect, ID_SCROLLBAREX_TongPing );
	m_pID_SCROLLBAREX_GuangJiao = (ControlScrollBarEx*)theUiManager.FindControl( ID_FRAME_SettingEffect, ID_SCROLLBAREX_GuangJiao );
	m_pID_SCROLLBAREX_JingTou = (ControlScrollBarEx*)theUiManager.FindControl( ID_FRAME_SettingEffect, ID_SCROLLBAREX_JingTou );
// 	m_pID_CHECKBOX_Effect = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_SettingEffect, ID_CHECKBOX_Effect );
// 	m_pID_CHECKBOX_GamePlay = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_SettingEffect, ID_CHECKBOX_GamePlay );
// 	m_pID_CHECKBOX_ShortcutKey = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_SettingEffect, ID_CHECKBOX_ShortcutKey );
	m_pID_COMBOBOX_MultiSample = (ControlComboBox*)theUiManager.FindControl( ID_FRAME_SettingEffect, ID_COMBOBOX_MS );
	m_pID_CHECKBOX_CameraShake = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_SettingEffect, ID_CHECKBOX_CAMERA_SHAKE );
	
	assert( m_pID_FRAME_SettingEffect );
	assert( m_pID_BUTTON_OK );
	assert( m_pID_BUTTON_Cancel );
	assert( m_pID_BUTTON_Default );
	assert( m_pID_TEXT_Mode );
	assert( m_pID_SCROLLBAREX_Music );
	assert( m_pID_BUTTON_SetHigh );
	assert( m_pID_BUTTON_SetMiddle );
	assert( m_pID_BUTTON_SetLow );
	assert( m_pID_CHECKBOX_Window );
	assert( m_pID_CHECKBOX_FullScreen );
	assert( m_pID_CHECKBOX_NoMusic );
	assert( m_pID_CHECKBOX_NoSoundEffect );
// 	assert( m_pID_BUTTON_CLOSE );
// 	assert( m_pID_BUTTON_HELP );
	assert( m_pID_BUTTON_Custom );
	assert( m_pID_LIST_23209 );
	assert( m_pID_SCROLLBAREX_SoundEffect );
	assert( m_pID_SCROLLBAREX_TongPing );
	assert( m_pID_SCROLLBAREX_GuangJiao );
	assert( m_pID_SCROLLBAREX_JingTou );
// 	assert( m_pID_CHECKBOX_Effect );
// 	assert( m_pID_CHECKBOX_GamePlay );
// 	assert( m_pID_CHECKBOX_ShortcutKey );
	assert(m_pID_COMBOBOX_MultiSample);
	assert(m_pID_CHECKBOX_CameraShake);

	m_pID_LIST_23209->SetLBtnDownFun(ID_LIST_SELECTOnListDBClick);

	m_pID_FRAME_SettingEffect->SetFather(s_CUI_ID_FRAME_GameSettingBgFrame.GetFrame());
	return true;
}

// 卸载UI
bool CUI_ID_FRAME_SettingEffect::_UnLoadUI()
{
	m_pID_FRAME_SettingEffect = NULL;
	m_pID_BUTTON_Default = NULL;
	m_pID_TEXT_Mode = NULL;
	m_pID_BUTTON_SetHigh = NULL;
	m_pID_BUTTON_SetMiddle = NULL;
	m_pID_BUTTON_SetLow = NULL;
	m_pID_CHECKBOX_Window = NULL;
	m_pID_CHECKBOX_NoMusic = NULL;
	m_pID_CHECKBOX_NoSoundEffect = NULL;
// 	m_pID_BUTTON_CLOSE = NULL;
// 	m_pID_BUTTON_HELP = NULL;
	m_pID_BUTTON_Custom = NULL;
	m_pID_LIST_23209 = NULL;
	m_pID_SCROLLBAREX_SoundEffect = NULL;
	m_pID_CHECKBOX_FullScreen = NULL;
	m_pID_BUTTON_OK = NULL;
	m_pID_BUTTON_Cancel = NULL;
	m_pID_PICTURE_7314 = NULL;
	m_pID_SCROLLBAREX_Music = NULL;
	m_pID_SCROLLBAREX_TongPing = NULL;
	m_pID_SCROLLBAREX_GuangJiao = NULL;
	m_pID_SCROLLBAREX_JingTou = NULL;
// 	m_pID_CHECKBOX_Effect = NULL;
// 	m_pID_CHECKBOX_GamePlay = NULL;
// 	m_pID_CHECKBOX_ShortcutKey = NULL;
	m_pID_TEXT_23801231233 = NULL;
	m_pID_TEXT_23821312303 = NULL;
	m_pID_TEXT_212313803 = NULL;
	m_pID_TEXT_238031231 = NULL;
	m_pID_TEXT_238031233 = NULL;
	m_pID_COMBOBOX_MultiSample = NULL;
	m_pID_CHECKBOX_CameraShake = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\SettingEffect.MEUI" );
}

// 是否可视
bool CUI_ID_FRAME_SettingEffect::_IsVisable()
{
	if(!m_pID_FRAME_SettingEffect)
		return false;

	return m_pID_FRAME_SettingEffect->IsVisable();
}

// 设置是否可视
void CUI_ID_FRAME_SettingEffect::_SetVisable( const bool bVisable )
{
	if(!m_pID_FRAME_SettingEffect)
		return;
	m_ScreenValue = 0;
	m_pID_FRAME_SettingEffect->SetVisable( bVisable );
	if(bVisable)
		Refresh();
}

void CUI_ID_FRAME_SettingEffect::Refresh(bool bResolution /*= true*/)
{
	if( !m_pID_FRAME_SettingEffect )
		return;

	for( int i = 0 ; i < SystemSetting::eSSC_TOTAL ; ++ i )
	{
		int nValue = (int)SystemSetting::Instance()->GetLevel( (SystemSetting::eSystemSettingCategory)i );
		switch( i )
		{
		case GameSetting::eGSC_FOV:
			nValue = (int)GameSetting::Instance()->GetLevel(GameSetting::eGSC_FOV );
			m_pID_SCROLLBAREX_GuangJiao->SetValue(nValue);
			break;
		case GameSetting::eGSC_SHOWPLAYERNUMBER:
			nValue = (int)GameSetting::Instance()->GetLevel(GameSetting::eGSC_SHOWPLAYERNUMBER);
			m_pID_SCROLLBAREX_TongPing->SetValue(nValue);
			break;
		case GameSetting::eGSC_MAXCAMERADISTANCE:
			nValue = (int)GameSetting::Instance()->GetLevel(GameSetting::eGSC_MAXCAMERADISTANCE );
			m_pID_SCROLLBAREX_JingTou->SetValue(nValue);
			break;
			/*
		case SystemSetting::eSSC_TEXTURE_MIPMAP:
			m_pID_SCROLLBAREX_tietu->SetValue( nValue );
			break;
		case SystemSetting::eSSC_BRIGHT:
			m_pID_SCROLLBAREX_liangdu->SetValue( nValue );
			break;
		case SystemSetting::eSSC_LOWFPS:
			m_pID_CHECKBOX_jieneng->SetCheck( (bool)nValue );
			break;
		case SystemSetting::eSSC_RENDER_DISTANCE:
			m_pID_SCROLLBAREX_huizhi->SetValue( nValue );
			break;
		case SystemSetting::eSSC_SHADOW:
			m_pID_CHECKBOX_yinying->SetCheck( (bool)( nValue - 1 ) );
			break;
		case SystemSetting::eSSC_TERRAIN_DETAIL:
			m_pID_SCROLLBAREX_dibiao->SetValue( nValue );
			break;
		case SystemSetting::eSSC_FONT_SHADOW:
			m_pID_CHECKBOX_chuizhi->SetCheck( (bool)nValue );
			break;
		case SystemSetting::eSSC_WATER:
			m_pID_CHECKBOX_shuimian->SetCheck( (bool)nValue );
			break;
		case SystemSetting::eSSC_SKY:
			m_pID_CHECKBOX_tianqi->SetCheck( (bool)nValue );
			break;
		case SystemSetting::eSSC_GRASS:
			m_pID_CHECKBOX_caodi->SetCheck( (bool)nValue );
			break;
		case SystemSetting::eSSC_DOF:
			m_pID_CHECKBOX_jingshen->SetCheck( (bool)nValue );
			break;
		case SystemSetting::eSSC_VERTICLESYNC:
			break;
		case SystemSetting::eSSC_LIGHTSHAFT:
			m_pID_CHECKBOX_guangmang->SetCheck( (bool)nValue );
			break;
		case SystemSetting::eSSC_BLOOM:
			m_pID_CHECKBOX_bloom->SetCheck( (bool)nValue );
			break;
		case SystemSetting::eSSC_MSAA:
			{
				m_pID_CHECKBOX_juchi->SetCheck( (bool)nValue );
			}				
			break;*/
		case SystemSetting::eSSC_WINDOWMODE:
			{
				m_pID_CHECKBOX_Window->SetCheck(false); 
		        m_pID_CHECKBOX_FullScreen->SetCheck(false);
				if((bool)nValue)
				    m_pID_CHECKBOX_Window->SetCheck(true);
				else
				    m_pID_CHECKBOX_FullScreen->SetCheck(true);
			}
			break;
		case SystemSetting::eSSC_RESOLUTION:
			{
				if(!bResolution)
					break;

				int nWidth = 1024;
				int nHeight = 768 ;
				bool bFound = false;
				if (nValue > 1000)
				{
					nWidth = ((nValue) >> 16) & 0x0000FFFF;
					nHeight = nValue & 0x0000FFFF;
				}
				//refresh resolution list
				m_pID_LIST_23209->Clear();
				std::vector<D3DDISPLAYMODE>& vList = SystemSetting::Instance()->GetDisplayModeList();
				char szResolution[50];
				for( int i = 0 ; i < vList.size() ; ++ i )
				{
					MeSprintf_s( szResolution, sizeof(szResolution)/sizeof(char) - 1, "%d * %d", vList[i].Width, vList[i].Height );
					AddResolutionString( szResolution );
					if( vList[i].Width == nWidth && vList[i].Height == nHeight )
						bFound =true;
				}
				//MeSprintf_s( szResolution, sizeof(szResolution)/sizeof(char) - 1, "%s", theXmlString.GetString( eText_Custom ));
				//AddResolutionString( szResolution );

				if( bFound )
					MeSprintf_s( szResolution, sizeof(szResolution)/sizeof(char) - 1, "%d * %d", nWidth, nHeight );
				else
					m_pID_LIST_23209->SetCurSelIndex(vList.size());
			}
			break;

		case SystemSetting::eSSC_MSAA:
			{
				if (m_pID_COMBOBOX_MultiSample != NULL)
				{
					m_pID_COMBOBOX_MultiSample->GetEditInput().SetReadOnly(true);
					ControlList &listbox = m_pID_COMBOBOX_MultiSample->GetListBox();
					listbox.Clear();

					ControlList::S_List item;
					item.clear();
					item.SetAlignMode(ControlList::S_List::LIST_ALIGNMODE_MIDDLE);
					item.SetMargin(5);

					const std::vector<int> &supportedFASSs = SystemSetting::Instance()->GetFSAATypeList();
					char szItemText[16] = {0};
					for (int i = 0; i < supportedFASSs.size(); ++i)
					{
						int level = supportedFASSs[i];
						GetItemTextByMSAALevel(level, szItemText);
						item.SetData(szItemText, i);
						listbox.AddItem(&item);
					}

					int massLevel = SystemSetting::Instance()->GetLevel(SystemSetting::eSSC_MSAA);
					GetItemTextByMSAALevel(massLevel, szItemText);
					m_pID_COMBOBOX_MultiSample->GetEditInput().SetText(szItemText);
				}
			}
			break;

		case SystemSetting::eSSC_CameraShake:
			{
				if (m_pID_CHECKBOX_CameraShake != NULL)
				{
					int bCameraShake = SystemSetting::Instance()->GetLevel(SystemSetting::eSSC_CameraShake);
					m_pID_CHECKBOX_CameraShake->SetCheck(bCameraShake);
				}
			}
			break;

		default:
			break;
		}
	}


	unsigned int usValue = 0;
	usValue = GameSetting::Instance()->GetLevel( GameSetting::eGSC_SOUND);          //声音大小
	int nActValue = 0;
	bool bSilence = false;
	GameSetting::Instance()->GetSoundValue( usValue, nActValue, bSilence ); //lyh修改静音选项的调用顺序，防止关闭了音乐但是顺序反了导致音乐又播放出来。。
	//if(usValue > 0)
		m_pID_CHECKBOX_NoMusic->SetCheck(bSilence);
		m_pID_SCROLLBAREX_Music->SetValue(nActValue);

	usValue = GameSetting::Instance()->GetLevel( GameSetting::eGSC_SOUNDEFFECT);    //环境音效
	GameSetting::Instance()->GetSoundValue( usValue, nActValue, bSilence );
	//if(usValue > 0)
		m_pID_CHECKBOX_NoSoundEffect->SetCheck(bSilence);
		m_pID_SCROLLBAREX_SoundEffect->SetValue(nActValue);

	usValue = SystemSetting::Instance()->GetLevel(SystemSetting::eSSC_GLOBAL_LEVEL);
	if(usValue == 0)
		m_pID_TEXT_Mode->SetText(theXmlString.GetString(eText_GameSettingLow));
	else if(usValue == 1)
	   m_pID_TEXT_Mode->SetText(theXmlString.GetString(eText_GameSettingMiddle));
	else if(usValue == 2)
	   m_pID_TEXT_Mode->SetText(theXmlString.GetString(eText_GameSettingHigh));
	else if(usValue == 5)
	   m_pID_TEXT_Mode->SetText(theXmlString.GetString(eText_GameSettingCustom));
}

void CUI_ID_FRAME_SettingEffect::AddResolutionString( const char* pszReslution )
{
	ControlList::S_List stItem;
	stItem.SetData(pszReslution);
	m_pID_LIST_23209->AddItem(&stItem);
}

void CUI_ID_FRAME_SettingEffect::LoadQuilityConfig(eQuility eValue)
{
	if(!m_pID_FRAME_SettingEffect)
		return;

	switch(eValue)
	{
	case eQuility_High: //高品质
		{
			m_pID_TEXT_Mode->SetText(theXmlString.GetString(eText_GameSettingHigh));//高品质
			SystemSetting::Instance()->LoadSetting(SystemSetting::eSSL_MEDIUM );
	        SystemSetting::Instance()->CommitChanges();

			SystemSetting::Instance()->SetLevel( SystemSetting::eSSC_GLOBAL_LEVEL, 2 );
		}
		break;
	case eQuility_Middle: //中品质
		{
			m_pID_TEXT_Mode->SetText(theXmlString.GetString(eText_GameSettingMiddle));//中品质
			SystemSetting::Instance()->LoadSetting(SystemSetting::eSSL_LOW_MEDIUM );
	        SystemSetting::Instance()->CommitChanges();

			SystemSetting::Instance()->SetLevel( SystemSetting::eSSC_GLOBAL_LEVEL, 1 );
		}
		break;
	case eQuility_Low:    //低品质
		{
			m_pID_TEXT_Mode->SetText(theXmlString.GetString(eText_GameSettingLow));//低品质
			SystemSetting::Instance()->LoadSetting(SystemSetting::eSSL_LOW );
	        SystemSetting::Instance()->CommitChanges();

			SystemSetting::Instance()->SetLevel( SystemSetting::eSSC_GLOBAL_LEVEL, 0 );
		}
		break;
	case eQuility_Custom:  //自定义
		{
			m_pID_TEXT_Mode->SetText(theXmlString.GetString(eText_GameSettingCustom));//自定义
			s_CUI_ID_FRAME_SettingCustom.SetVisable(true);

			SystemSetting::Instance()->SetLevel( SystemSetting::eSSC_GLOBAL_LEVEL, 5 );
		}
		break;
	default:
		break;
	}
}

void CUI_ID_FRAME_SettingEffect::ID_LIST_SELECTOnListDBClick( ControlObject* pSender, ControlList::S_List* pItem )
{
	if( !pItem )
		return;

	std::string strResolution(pItem->m_szText);
	std::string::size_type nPos = strResolution.find( '*' );
	if( nPos == std::string::npos )
		return;
	std::string strWidth = strResolution.substr( 0, nPos );
	std::string strHeight = strResolution.substr( nPos + 1 );
	int nWidth = atoi( strWidth.c_str() );
	int nHeight = atoi( strHeight.c_str() );
	int nValue = ((nWidth << 16)&0xFFFF0000) | nHeight;
	m_ScreenValue = nValue;
	//SystemSetting::Instance()->SetLevel( SystemSetting::eSSC_RESOLUTION, nValue );
	//SystemSetting::Instance()->CommitChanges();
}

void CUI_ID_FRAME_SettingEffect::SetScrollBarFov(int nValue)
{
	if(!m_pID_FRAME_SettingEffect)
		return;
	m_pID_SCROLLBAREX_GuangJiao->SetValue(nValue);
}