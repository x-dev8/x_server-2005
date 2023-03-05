/********************************************************************
Created by UIEditor.exe
FileName: D:\My Documents\桌面\游戏设置UI\systemset.cpp
*********************************************************************/
#include <assert.h>
#include "meui/UiManager.h"
#include "systemsettingui.h"
#include "SystemSetting.h"
#include "UIBase.h"
#include "UserData.h"
#include "GameMain.h"
#include "ui/MiniMapUI.h"
#include "core/Name.h"
#include "XmlStringLanguage.h"
#include "Common.h"
#include "GameSettingUIBase.h"
#include "Me3d/ShaderMgr.h"

static const char* s_pszClose = "关闭";
extern CHeroGame theHeroGame;
extern bool g_DynamicMapLoadOpenEvent;

CUI_ID_FRAME_Systemset s_CUI_ID_FRAME_Systemset;
MAP_FRAME_RUN( s_CUI_ID_FRAME_Systemset, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_Systemset, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Systemset, ID_BUTTON_AOTOSETOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Systemset, ID_BUTTON_morenOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Systemset, ID_BUTTON_querenOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Systemset, ID_BUTTON_quxiaoOnButtonClick )
MAP_SCROLL_BAREX_UPDATE_POS_CALLBACK( s_CUI_ID_FRAME_Systemset, ID_SCROLLBAREX_allsetOnScrollBarExUpdatePos )
MAP_SCROLL_BAREX_UPDATE_POS_CALLBACK( s_CUI_ID_FRAME_Systemset, ID_SCROLLBAREX_liangduOnScrollBarExUpdatePos )
MAP_SCROLL_BAREX_UPDATE_POS_CALLBACK( s_CUI_ID_FRAME_Systemset, ID_SCROLLBAREX_huizhiOnScrollBarExUpdatePos )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_Systemset, ID_CHECKBOX_YinyingOnCheckBoxCheck )
MAP_SCROLL_BAREX_UPDATE_POS_CALLBACK( s_CUI_ID_FRAME_Systemset, ID_SCROLLBAREX_dibiaoOnScrollBarExUpdatePos )
MAP_SCROLL_BAREX_UPDATE_POS_CALLBACK( s_CUI_ID_FRAME_Systemset, ID_SCROLLBAREX_zitiOnScrollBarExUpdatePos )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Systemset, ID_BUTTON_closeOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Systemset, ID_BUTTON_helpOnButtonClick )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_Systemset, ID_CHECKBOX_jienengOnCheckBoxCheck )
MAP_SCROLL_BAREX_UPDATE_POS_CALLBACK( s_CUI_ID_FRAME_Systemset, ID_SCROLLBAREX_tietuOnScrollBarExUpdatePos )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_Systemset, ID_CHECKBOX_shuimianOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_Systemset, ID_CHECKBOX_tianqiOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_Systemset, ID_CHECKBOX_caodiOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_Systemset, ID_CHECKBOX_jingshenOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_Systemset, ID_CHECKBOX_guangmangOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_Systemset, ID_CHECKBOX_chuangkouOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_Systemset, ID_CHECKBOX_chuizhiOnCheckBoxCheck )
MAP_COMBO_BOX_CHANGE_CALLBACK( s_CUI_ID_FRAME_Systemset, ID_COMBOBOX_fenbianluOnComboBoxChange )
MAP_COMBO_BOX_CHANGE_CALLBACK( s_CUI_ID_FRAME_Systemset, ID_COMBOBOX_juchiOnComboBoxChange )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_Systemset, ID_CHECKBOX_bloomOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_Systemset, ID_CHECKBOX_AdvanceOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_Systemset, ID_CHECKBOX_juchiOnCheckBoxCheck )
CUI_ID_FRAME_Systemset::CUI_ID_FRAME_Systemset()
{
	// SGuildMember
	ResetMembers();
}

void CUI_ID_FRAME_Systemset::ResetMembers()
{
	m_pID_FRAME_Systemset = NULL;
	m_pID_PICTURE_wallpaper = NULL;
	m_pID_PICTURE_title_wall = NULL;
	m_pID_PICTURE_title = NULL;
	m_pID_PICTURE_imagewall = NULL;
	m_pID_PICTURE_soundwall = NULL;
	m_pID_BUTTON_AOTOSET = NULL;
	m_pID_BUTTON_moren = NULL;
	m_pID_BUTTON_queren = NULL;
	m_pID_BUTTON_quxiao = NULL;
	m_pID_TEXT_1 = NULL;
	m_pID_TEXT_2 = NULL;
	m_pID_TEXT_3 = NULL;
	m_pID_TEXT_4 = NULL;
	m_pID_TEXT_5 = NULL;
	m_pID_TEXT_6 = NULL;
	m_pID_TEXT_7 = NULL;
	m_pID_TEXT_8 = NULL;
	m_pID_TEXT_9 = NULL;
	m_pID_TEXT_10 = NULL;
	m_pID_TEXT_11 = NULL;
	m_pID_TEXT_12 = NULL;
	m_pID_TEXT_13 = NULL;
	m_pID_TEXT_14 = NULL;
	m_pID_TEXT_15 = NULL;
	m_pID_TEXT_16 = NULL;
	m_pID_TEXT_17 = NULL;
	m_pID_TEXT_18 = NULL;
	m_pID_TEXT_20 = NULL;
	m_pID_TEXT_21 = NULL;
	m_pID_TEXT_22 = NULL;
	m_pID_SCROLLBAREX_allset = NULL;
	m_pID_SCROLLBAREX_liangdu = NULL;
	m_pID_SCROLLBAREX_huizhi = NULL;
	m_pID_CHECKBOX_yinying = NULL;
	m_pID_SCROLLBAREX_dibiao = NULL;
	m_pID_SCROLLBAREX_ziti = NULL;
	m_pID_BUTTON_close = NULL;
	m_pID_BUTTON_help = NULL;
	m_pID_CHECKBOX_jieneng = NULL;
	m_pID_SCROLLBAREX_tietu = NULL;
	m_pID_CHECKBOX_shuimian = NULL;
	m_pID_CHECKBOX_tianqi = NULL;
	m_pID_CHECKBOX_caodi = NULL;
	m_pID_CHECKBOX_jingshen = NULL;
	m_pID_CHECKBOX_guangmang = NULL;
	m_pID_CHECKBOX_chuangkou = NULL;
	m_pID_CHECKBOX_chuizhi = NULL;
	m_pID_COMBOBOX_fenbianlu = NULL;
	m_pID_COMBOBOX_juchi = NULL;
	m_pID_CHECKBOX_bloom = NULL;
	m_pID_CHECKBOX_Advance = NULL;
	m_pID_CHECKBOX_juchi = NULL;
	m_bRefreshUI = true;

}
// Frame
bool CUI_ID_FRAME_Systemset::OnFrameRun()
{
	return true;
}
bool CUI_ID_FRAME_Systemset::OnFrameRender()
{
	return true;
}
// Button
bool CUI_ID_FRAME_Systemset::ID_BUTTON_AOTOSETOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_Systemset )
		return false;
	return true;
}
// load default setting
bool CUI_ID_FRAME_Systemset::ID_BUTTON_morenOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_Systemset )
		return false;
	SystemSetting::Instance()->LoadSetting();
	SystemSetting::Instance()->CommitChanges();
	Refresh();
	return true;
}
// save custom setting
bool CUI_ID_FRAME_Systemset::ID_BUTTON_querenOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_Systemset )
		return false;
	char szSetting[MAX_PATH] = {0};
	MeSprintf_s(szSetting,sizeof(szSetting)/sizeof(char) - 1, "%s/Client/UserData/%s", GetRootPath(), SystemSetting::Instance()->GetCustomSettingFile() );

	SystemSetting::Instance()->SaveSetting( szSetting );		
	SetVisable( FALSE );
	return true;
}
// Button
bool CUI_ID_FRAME_Systemset::ID_BUTTON_quxiaoOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_Systemset )
		return false;
	char szSetting[MAX_PATH] = {0};
	MeSprintf_s(szSetting,sizeof(szSetting)/sizeof(char) - 1, "%s/Client/UserData/%s", GetRootPath(), SystemSetting::Instance()->GetCustomSettingFile() );

	SystemSetting::Instance()->LoadSetting( szSetting );
	SystemSetting::Instance()->CommitChanges();
	SetVisable( false );
	Refresh();
	return true;		
}
// ScrollBarEx
void CUI_ID_FRAME_Systemset::ID_SCROLLBAREX_allsetOnScrollBarExUpdatePos( ControlObject* pSender, int n )
{
	if( !m_pID_FRAME_Systemset )
		return;
	SystemSetting::Instance()->SetLevel( SystemSetting::eSSC_GLOBAL_LEVEL, n );
	if( n == 5 )//自定义设置
		m_pID_SCROLLBAREX_allset->SetDrawValueText( false );			
	else
		m_pID_SCROLLBAREX_allset->SetDrawValueText( true );

	Refresh(false);

	s_CUI_ID_FRAME_MiniMap.SetButtonToCustom();

}
// ScrollBarEx
void CUI_ID_FRAME_Systemset::ID_SCROLLBAREX_liangduOnScrollBarExUpdatePos( ControlObject* pSender, int n )
{
	if( !m_pID_FRAME_Systemset )
		return;
	SystemSetting::Instance()->SetLevel( SystemSetting::eSSC_BRIGHT, n );
	SystemSetting::Instance()->CommitChanges();
}
// 绘制距离
void CUI_ID_FRAME_Systemset::ID_SCROLLBAREX_huizhiOnScrollBarExUpdatePos( ControlObject* pSender, int n )
{		
	if( !m_pID_FRAME_Systemset )
		return;
 	SystemSetting::Instance()->SetLevel( SystemSetting::eSSC_RENDER_DISTANCE, n );
 	SystemSetting::Instance()->CommitChanges();
 	s_CUI_ID_FRAME_MiniMap.SetButtonToCustom();
}
// ScrollBarEx
void CUI_ID_FRAME_Systemset::ID_SCROLLBAREX_dibiaoOnScrollBarExUpdatePos( ControlObject* pSender, int n )
{
	if( !m_pID_FRAME_Systemset )
		return;
	SystemSetting::Instance()->SetLevel( SystemSetting::eSSC_TERRAIN_DETAIL, n );
	SystemSetting::Instance()->CommitChanges();
	s_CUI_ID_FRAME_MiniMap.SetButtonToCustom();
}
// ScrollBarEx
void CUI_ID_FRAME_Systemset::ID_SCROLLBAREX_zitiOnScrollBarExUpdatePos( ControlObject* pSender, int n )
{
	if( !m_pID_FRAME_Systemset )
		return;
	SystemSetting::Instance()->SetLevel( SystemSetting::eSSC_FONT_SHADOW, n );
	SystemSetting::Instance()->CommitChanges();	
}

// Button
bool CUI_ID_FRAME_Systemset::ID_BUTTON_closeOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_Systemset )
		return false;
	char szSetting[MAX_PATH] = {0};
	MeSprintf_s(szSetting,sizeof(szSetting)/sizeof(char) - 1, "%s/Client/UserData/%s", GetRootPath(), SystemSetting::Instance()->GetCustomSettingFile() );

	SystemSetting::Instance()->LoadSetting( szSetting );
	SystemSetting::Instance()->CommitChanges();
	Refresh();
	SetVisable( FALSE );
	return true;
}
// Button
bool CUI_ID_FRAME_Systemset::ID_BUTTON_helpOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_Systemset )
		return false;
	return true;
}
// CheckBox
void CUI_ID_FRAME_Systemset::ID_CHECKBOX_jienengOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if( !m_pID_FRAME_Systemset )
		return;
	SystemSetting::Instance()->SetLevel( SystemSetting::eSSC_LOWFPS, *pbChecked  );
	SystemSetting::Instance()->CommitChanges();
}
// ScrollBarEx
void CUI_ID_FRAME_Systemset::ID_SCROLLBAREX_tietuOnScrollBarExUpdatePos( ControlObject* pSender, int n )
{
	if( !m_pID_FRAME_Systemset )
		return;
	SystemSetting::Instance()->SetLevel( SystemSetting::eSSC_TEXTURE_MIPMAP, n );
	SystemSetting::Instance()->CommitChanges();
}
// CheckBox
void CUI_ID_FRAME_Systemset::ID_CHECKBOX_shuimianOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if( !m_pID_FRAME_Systemset )
		return;
	SystemSetting::Instance()->SetLevel( SystemSetting::eSSC_WATER, *pbChecked  );
	SystemSetting::Instance()->CommitChanges();
	s_CUI_ID_FRAME_MiniMap.SetButtonToCustom();
}
// CheckBox
void CUI_ID_FRAME_Systemset::ID_CHECKBOX_tianqiOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if( !m_pID_FRAME_Systemset )
		return;
	SystemSetting::Instance()->SetLevel( SystemSetting::eSSC_SKY, *pbChecked  );
	SystemSetting::Instance()->CommitChanges();
	s_CUI_ID_FRAME_MiniMap.SetButtonToCustom();
}
// CheckBox
void CUI_ID_FRAME_Systemset::ID_CHECKBOX_YinyingOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if( !m_pID_FRAME_Systemset )
		return;
	SystemSetting::Instance()->SetLevel( SystemSetting::eSSC_SHADOW, *pbChecked + 1 );
	SystemSetting::Instance()->CommitChanges();
}
// CheckBox
void CUI_ID_FRAME_Systemset::ID_CHECKBOX_caodiOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if( !m_pID_FRAME_Systemset )
		return;
	SystemSetting::Instance()->SetLevel( SystemSetting::eSSC_GRASS, *pbChecked  );
	SystemSetting::Instance()->CommitChanges();
	s_CUI_ID_FRAME_MiniMap.SetButtonToCustom();
}
// CheckBox
void CUI_ID_FRAME_Systemset::ID_CHECKBOX_jingshenOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if( !m_pID_FRAME_Systemset )
		return;
	SystemSetting::Instance()->SetLevel( SystemSetting::eSSC_DOF, *pbChecked  );
	SystemSetting::Instance()->CommitChanges();
	s_CUI_ID_FRAME_MiniMap.SetButtonToCustom();
}
// CheckBox
void CUI_ID_FRAME_Systemset::ID_CHECKBOX_guangmangOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if( !m_pID_FRAME_Systemset )
		return;
	SystemSetting::Instance()->SetLevel( SystemSetting::eSSC_LIGHTSHAFT, *pbChecked  );
	SystemSetting::Instance()->CommitChanges();
	s_CUI_ID_FRAME_MiniMap.SetButtonToCustom();
}
// CheckBox
void CUI_ID_FRAME_Systemset::ID_CHECKBOX_chuangkouOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if( !m_pID_FRAME_Systemset )
		return;
	SystemSetting::Instance()->SetLevel( SystemSetting::eSSC_WINDOWMODE, *pbChecked  );
	SystemSetting::Instance()->CommitChanges();
}
// CheckBox
//这个改为字体阴影了
void CUI_ID_FRAME_Systemset::ID_CHECKBOX_chuizhiOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if( !m_pID_FRAME_Systemset )
		return;
	SystemSetting::Instance()->SetLevel( SystemSetting::eSSC_FONT_SHADOW, *pbChecked  );
	SystemSetting::Instance()->CommitChanges();
}
// ComboBox
void CUI_ID_FRAME_Systemset::ID_COMBOBOX_fenbianluOnComboBoxChange( ControlObject* pSender, const char* szData )
{
	if( !m_pID_FRAME_Systemset )
		return;
	std::string strResolution( szData );
	std::string::size_type nPos = strResolution.find( '*' );
	if( nPos == std::string::npos )
		return;
	std::string strWidth = strResolution.substr( 0, nPos );
	std::string strHeight = strResolution.substr( nPos + 1 );
	int nWidth = atoi( strWidth.c_str() );
	int nHeight = atoi( strHeight.c_str() );
	int nValue = ((nWidth << 16)&0xFFFF0000) | nHeight;
	SystemSetting::Instance()->SetLevel( SystemSetting::eSSC_RESOLUTION, nValue );
	SystemSetting::Instance()->CommitChanges();
}
// ComboBox
void CUI_ID_FRAME_Systemset::ID_COMBOBOX_juchiOnComboBoxChange( ControlObject* pSender, const char* szData )
{
	if( !m_pID_FRAME_Systemset )
		return;
	int nLevel = m_pID_COMBOBOX_juchi->GetListBox().GetCurSelIndex() * 2;
	int nWindowMode = SystemSetting::Instance()->GetLevel( SystemSetting::eSSC_WINDOWMODE );
 	theHeroGame.GetD3DPP()->MultiSampleType = (D3DMULTISAMPLE_TYPE)nLevel;
 	theHeroGame.ChangeDevice( !(bool)nWindowMode );
 	SystemSetting::Instance()->SetLevel( SystemSetting::eSSC_MSAA, nLevel );
	s_CUI_ID_FRAME_MiniMap.SetButtonToCustom();
}
// CheckBox
void CUI_ID_FRAME_Systemset::ID_CHECKBOX_bloomOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if( !m_pID_FRAME_Systemset )
		return;
	SystemSetting::Instance()->SetLevel( SystemSetting::eSSC_BLOOM, *pbChecked  );
	SystemSetting::Instance()->CommitChanges();
	s_CUI_ID_FRAME_MiniMap.SetButtonToCustom();
}
// CheckBox
void CUI_ID_FRAME_Systemset::ID_CHECKBOX_AdvanceOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if( !m_pID_FRAME_Systemset )
		return;
	if( !(*pbChecked) )
	{
		if( SystemSetting::Instance()->GetLevel( SystemSetting::eSSC_SHADOW ) == eShadow_RealTime )
			SystemSetting::Instance()->SetLevel( SystemSetting::eSSC_SHADOW, eShadow_Fake );
		SystemSetting::Instance()->SetLevel( SystemSetting::eSSC_BLOOM, 0 );
		SystemSetting::Instance()->SetLevel( SystemSetting::eSSC_LIGHTSHAFT, 0 );
	}

	SetAdvance( *pbChecked );
	s_CUI_ID_FRAME_MiniMap.SetButtonToCustom();
}

bool CUI_ID_FRAME_Systemset::frame_msg( UINT msg, WPARAM wParam, LPARAM lParam, bool bMsgUsed )
{
	if( !s_CUI_ID_FRAME_Systemset.IsVisable() )
		return false;
	switch( msg ) 
	{		
	case WM_LBUTTONDOWN:
		{
			if( bMsgUsed )
				s_CUI_ID_FRAME_Systemset.m_pID_SCROLLBAREX_allset->SetValue( 5 );
		}
		break;
	}

	return false;

}
void CUI_ID_FRAME_Systemset::ID_CHECKBOX_juchiOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if( !m_pID_FRAME_Systemset )
		return;
	int nLevel = (int)( *pbChecked ) * 2;
	int nWindowMode = SystemSetting::Instance()->GetLevel( SystemSetting::eSSC_WINDOWMODE );
	theHeroGame.GetD3DPP()->MultiSampleType = (D3DMULTISAMPLE_TYPE)nLevel;
	theHeroGame.ChangeDevice( !(bool)nWindowMode );
	SystemSetting::Instance()->SetLevel( SystemSetting::eSSC_MSAA, nLevel );
	SystemSetting::Instance()->CommitChanges();
	s_CUI_ID_FRAME_MiniMap.SetButtonToCustom();
}

// 装载UI
bool CUI_ID_FRAME_Systemset::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\systemset.MEUI", false, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\systemset.MEUI]失败")
			return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_Systemset::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_Systemset, s_CUI_ID_FRAME_SystemsetOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_Systemset, s_CUI_ID_FRAME_SystemsetOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_Systemset, ID_BUTTON_AOTOSET, s_CUI_ID_FRAME_SystemsetID_BUTTON_AOTOSETOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Systemset, ID_BUTTON_moren, s_CUI_ID_FRAME_SystemsetID_BUTTON_morenOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Systemset, ID_BUTTON_queren, s_CUI_ID_FRAME_SystemsetID_BUTTON_querenOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Systemset, ID_BUTTON_quxiao, s_CUI_ID_FRAME_SystemsetID_BUTTON_quxiaoOnButtonClick );
	theUiManager.OnScrollBarExUpdatePos( ID_FRAME_Systemset, ID_SCROLLBAREX_allset, s_CUI_ID_FRAME_SystemsetID_SCROLLBAREX_allsetOnScrollBarExUpdatePos );
	theUiManager.OnScrollBarExUpdatePos( ID_FRAME_Systemset, ID_SCROLLBAREX_liangdu, s_CUI_ID_FRAME_SystemsetID_SCROLLBAREX_liangduOnScrollBarExUpdatePos );
	theUiManager.OnScrollBarExUpdatePos( ID_FRAME_Systemset, ID_SCROLLBAREX_huizhi, s_CUI_ID_FRAME_SystemsetID_SCROLLBAREX_huizhiOnScrollBarExUpdatePos );
	theUiManager.OnCheckBoxCheck( ID_FRAME_Systemset, ID_CHECKBOX_yinying, s_CUI_ID_FRAME_SystemsetID_CHECKBOX_YinyingOnCheckBoxCheck );
	theUiManager.OnScrollBarExUpdatePos( ID_FRAME_Systemset, ID_SCROLLBAREX_dibiao, s_CUI_ID_FRAME_SystemsetID_SCROLLBAREX_dibiaoOnScrollBarExUpdatePos );
	theUiManager.OnScrollBarExUpdatePos( ID_FRAME_Systemset, ID_SCROLLBAREX_ziti, s_CUI_ID_FRAME_SystemsetID_SCROLLBAREX_zitiOnScrollBarExUpdatePos );
	theUiManager.OnButtonClick( ID_FRAME_Systemset, ID_BUTTON_close, s_CUI_ID_FRAME_SystemsetID_BUTTON_closeOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Systemset, ID_BUTTON_help, s_CUI_ID_FRAME_SystemsetID_BUTTON_helpOnButtonClick );
	theUiManager.OnCheckBoxCheck( ID_FRAME_Systemset, ID_CHECKBOX_jieneng, s_CUI_ID_FRAME_SystemsetID_CHECKBOX_jienengOnCheckBoxCheck );
	theUiManager.OnScrollBarExUpdatePos( ID_FRAME_Systemset, ID_SCROLLBAREX_tietu, s_CUI_ID_FRAME_SystemsetID_SCROLLBAREX_tietuOnScrollBarExUpdatePos );
	theUiManager.OnCheckBoxCheck( ID_FRAME_Systemset, ID_CHECKBOX_shuimian, s_CUI_ID_FRAME_SystemsetID_CHECKBOX_shuimianOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_Systemset, ID_CHECKBOX_tianqi, s_CUI_ID_FRAME_SystemsetID_CHECKBOX_tianqiOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_Systemset, ID_CHECKBOX_caodi, s_CUI_ID_FRAME_SystemsetID_CHECKBOX_caodiOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_Systemset, ID_CHECKBOX_jingshen, s_CUI_ID_FRAME_SystemsetID_CHECKBOX_jingshenOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_Systemset, ID_CHECKBOX_guangmang, s_CUI_ID_FRAME_SystemsetID_CHECKBOX_guangmangOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_Systemset, ID_CHECKBOX_chuangkou, s_CUI_ID_FRAME_SystemsetID_CHECKBOX_chuangkouOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_Systemset, ID_CHECKBOX_chuizhi, s_CUI_ID_FRAME_SystemsetID_CHECKBOX_chuizhiOnCheckBoxCheck );
	theUiManager.OnComboBoxChange( ID_FRAME_Systemset, ID_COMBOBOX_fenbianlu, s_CUI_ID_FRAME_SystemsetID_COMBOBOX_fenbianluOnComboBoxChange );
	theUiManager.OnComboBoxChange( ID_FRAME_Systemset, ID_COMBOBOX_juchi, s_CUI_ID_FRAME_SystemsetID_COMBOBOX_juchiOnComboBoxChange );
	theUiManager.OnCheckBoxCheck( ID_FRAME_Systemset, ID_CHECKBOX_bloom, s_CUI_ID_FRAME_SystemsetID_CHECKBOX_bloomOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_Systemset, ID_CHECKBOX_Advance, s_CUI_ID_FRAME_SystemsetID_CHECKBOX_AdvanceOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_Systemset, ID_CHECKBOX_juchi, s_CUI_ID_FRAME_SystemsetID_CHECKBOX_juchiOnCheckBoxCheck );

	m_pID_FRAME_Systemset = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_Systemset );
	m_pID_PICTURE_wallpaper = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Systemset, ID_PICTURE_wallpaper );
	m_pID_PICTURE_title_wall = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Systemset, ID_PICTURE_title_wall );
	m_pID_PICTURE_title = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Systemset, ID_PICTURE_title );
	m_pID_PICTURE_imagewall = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Systemset, ID_PICTURE_imagewall );
	m_pID_PICTURE_soundwall = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Systemset, ID_PICTURE_soundwall );
	m_pID_BUTTON_AOTOSET = (ControlButton*)theUiManager.FindControl( ID_FRAME_Systemset, ID_BUTTON_AOTOSET );
	m_pID_BUTTON_moren = (ControlButton*)theUiManager.FindControl( ID_FRAME_Systemset, ID_BUTTON_moren );
	m_pID_BUTTON_queren = (ControlButton*)theUiManager.FindControl( ID_FRAME_Systemset, ID_BUTTON_queren );
	m_pID_BUTTON_quxiao = (ControlButton*)theUiManager.FindControl( ID_FRAME_Systemset, ID_BUTTON_quxiao );
	m_pID_TEXT_1 = (ControlText*)theUiManager.FindControl( ID_FRAME_Systemset, ID_TEXT_1 );
	m_pID_TEXT_2 = (ControlText*)theUiManager.FindControl( ID_FRAME_Systemset, ID_TEXT_2 );
	m_pID_TEXT_3 = (ControlText*)theUiManager.FindControl( ID_FRAME_Systemset, ID_TEXT_3 );
	m_pID_TEXT_4 = (ControlText*)theUiManager.FindControl( ID_FRAME_Systemset, ID_TEXT_4 );
	m_pID_TEXT_5 = (ControlText*)theUiManager.FindControl( ID_FRAME_Systemset, ID_TEXT_5 );
	m_pID_TEXT_6 = (ControlText*)theUiManager.FindControl( ID_FRAME_Systemset, ID_TEXT_6 );
	m_pID_TEXT_7 = (ControlText*)theUiManager.FindControl( ID_FRAME_Systemset, ID_TEXT_7 );
	m_pID_TEXT_8 = (ControlText*)theUiManager.FindControl( ID_FRAME_Systemset, ID_TEXT_8 );
	m_pID_TEXT_9 = (ControlText*)theUiManager.FindControl( ID_FRAME_Systemset, ID_TEXT_9 );
	m_pID_TEXT_10 = (ControlText*)theUiManager.FindControl( ID_FRAME_Systemset, ID_TEXT_10 );
	m_pID_TEXT_11 = (ControlText*)theUiManager.FindControl( ID_FRAME_Systemset, ID_TEXT_11 );
	m_pID_TEXT_12 = (ControlText*)theUiManager.FindControl( ID_FRAME_Systemset, ID_TEXT_12 );
	m_pID_TEXT_13 = (ControlText*)theUiManager.FindControl( ID_FRAME_Systemset, ID_TEXT_13 );
	m_pID_TEXT_14 = (ControlText*)theUiManager.FindControl( ID_FRAME_Systemset, ID_TEXT_14 );
	m_pID_TEXT_15 = (ControlText*)theUiManager.FindControl( ID_FRAME_Systemset, ID_TEXT_15 );
	m_pID_TEXT_16 = (ControlText*)theUiManager.FindControl( ID_FRAME_Systemset, ID_TEXT_16 );
	m_pID_TEXT_17 = (ControlText*)theUiManager.FindControl( ID_FRAME_Systemset, ID_TEXT_17 );
	m_pID_TEXT_18 = (ControlText*)theUiManager.FindControl( ID_FRAME_Systemset, ID_TEXT_18 );
	m_pID_TEXT_20 = (ControlText*)theUiManager.FindControl( ID_FRAME_Systemset, ID_TEXT_20 );
	m_pID_TEXT_21 = (ControlText*)theUiManager.FindControl( ID_FRAME_Systemset, ID_TEXT_21 );
	m_pID_TEXT_22 = (ControlText*)theUiManager.FindControl( ID_FRAME_Systemset, ID_TEXT_22 );
	m_pID_CHECKBOX_juchi = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_Systemset, ID_CHECKBOX_juchi );
	m_pID_SCROLLBAREX_allset = (ControlScrollBarEx*)theUiManager.FindControl( ID_FRAME_Systemset, ID_SCROLLBAREX_allset );
	m_pID_SCROLLBAREX_allset->SetMaxValue( 5 );	
	m_pID_SCROLLBAREX_allset->SetStepValue( 1 );
	m_pID_SCROLLBAREX_liangdu = (ControlScrollBarEx*)theUiManager.FindControl( ID_FRAME_Systemset, ID_SCROLLBAREX_liangdu );
	m_pID_SCROLLBAREX_huizhi = (ControlScrollBarEx*)theUiManager.FindControl( ID_FRAME_Systemset, ID_SCROLLBAREX_huizhi );
	m_pID_SCROLLBAREX_huizhi->SetMaxValue( 600 );
	m_pID_CHECKBOX_yinying = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_Systemset, ID_CHECKBOX_yinying );		
	m_pID_SCROLLBAREX_dibiao = (ControlScrollBarEx*)theUiManager.FindControl( ID_FRAME_Systemset, ID_SCROLLBAREX_dibiao );
	m_pID_SCROLLBAREX_dibiao->SetMaxValue( 1 );
	m_pID_SCROLLBAREX_ziti = (ControlScrollBarEx*)theUiManager.FindControl( ID_FRAME_Systemset, ID_SCROLLBAREX_ziti );
	m_pID_SCROLLBAREX_ziti->SetMaxValue( 1 );
	m_pID_BUTTON_close = (ControlButton*)theUiManager.FindControl( ID_FRAME_Systemset, ID_BUTTON_close );
	m_pID_BUTTON_help = (ControlButton*)theUiManager.FindControl( ID_FRAME_Systemset, ID_BUTTON_help );
	m_pID_CHECKBOX_jieneng = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_Systemset, ID_CHECKBOX_jieneng );
	m_pID_CHECKBOX_Advance = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_Systemset, ID_CHECKBOX_Advance );		

	m_pID_SCROLLBAREX_tietu = (ControlScrollBarEx*)theUiManager.FindControl( ID_FRAME_Systemset, ID_SCROLLBAREX_tietu );
	m_pID_CHECKBOX_shuimian = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_Systemset, ID_CHECKBOX_shuimian );		
	m_pID_CHECKBOX_tianqi = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_Systemset, ID_CHECKBOX_tianqi );
	m_pID_CHECKBOX_caodi = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_Systemset, ID_CHECKBOX_caodi );
	m_pID_CHECKBOX_jingshen = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_Systemset, ID_CHECKBOX_jingshen );
	m_pID_CHECKBOX_guangmang = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_Systemset, ID_CHECKBOX_guangmang );
	m_pID_CHECKBOX_chuangkou = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_Systemset, ID_CHECKBOX_chuangkou );
	m_pID_CHECKBOX_chuizhi = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_Systemset, ID_CHECKBOX_chuizhi );
	m_pID_COMBOBOX_fenbianlu = (ControlComboBox*)theUiManager.FindControl( ID_FRAME_Systemset, ID_COMBOBOX_fenbianlu );
	m_pID_COMBOBOX_juchi = (ControlComboBox*)theUiManager.FindControl( ID_FRAME_Systemset, ID_COMBOBOX_juchi );
	m_pID_CHECKBOX_bloom = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_Systemset, ID_CHECKBOX_bloom );

	m_pID_FRAME_Systemset->SetMsgProcFun( frame_msg );
	m_pID_FRAME_Systemset->SetOnVisibleChangedFun(OnVisibleChanged);

// 	CUILayout::GetInstance()->AddFrame( m_pID_FRAME_Systemset );
	m_pID_FRAME_Systemset->SetMsgHoldup( false );

	char szSetting[MAX_PATH] = {0};
	MeSprintf_s(szSetting, sizeof(szSetting)/sizeof(char) - 1,"%s/Client/UserData/%s", GetRootPath(), SystemSetting::Instance()->GetCustomSettingFile() );

	if( SystemSetting::Instance()->IsLowLevelCard() )
	{			
		SystemSetting::Instance()->LoadSetting( SystemSetting::eSSL_LOW );
		SetAdvance( false );
		m_pID_CHECKBOX_Advance->SetEnable( false );
	}

	int nValue = (int)SystemSetting::Instance()->GetLevel( SystemSetting::eSSC_GLOBAL_LEVEL );
	m_pID_SCROLLBAREX_allset->SetValue( nValue );
	GetFrame()->SetFather(s_CUI_ID_FRAME_GameSettingUIBase.GetFrame());
	s_CUI_ID_FRAME_GameSettingUIBase.AddGroupSystemSetting(GetFrame());
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_Systemset::_UnLoadUI()
{
	ResetMembers();
	m_pID_FRAME_Systemset = NULL; //在这里必须设置为空指针,否则当再次加载的时候，在frame_msg中可能当机
	return theUiManager.RemoveFrame( "Data\\UI\\systemset.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_Systemset::_IsVisable()
{
	if( !m_pID_FRAME_Systemset )
		return false;
	return m_pID_FRAME_Systemset->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_Systemset::_SetVisable( const bool bVisable )
{
	if( !m_pID_FRAME_Systemset )
		return;
	m_pID_FRAME_Systemset->SetVisable( bVisable );
	g_DynamicMapLoadOpenEvent = bVisable;
	if (bVisable)
	{
		Refresh();
	}
}

void CUI_ID_FRAME_Systemset::Refresh(bool bResolution)
{
	if( !m_pID_FRAME_Systemset )
		return;

	for( int i = 0 ; i < SystemSetting::eSSC_TOTAL ; ++ i )
	{
		int nValue = (int)SystemSetting::Instance()->GetLevel( (SystemSetting::eSystemSettingCategory)i );
		switch( i )
		{
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
			break;
		case SystemSetting::eSSC_WINDOWMODE:
			m_pID_CHECKBOX_chuangkou->SetCheck( (bool)nValue );
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
				m_pID_COMBOBOX_fenbianlu->GetListBox().Clear(false);
				std::vector<D3DDISPLAYMODE>& vList = SystemSetting::Instance()->GetDisplayModeList();
				char szResolution[50];
				for( int i = 0 ; i < vList.size() ; ++ i )
				{
					MeSprintf_s( szResolution, sizeof(szResolution)/sizeof(char) - 1, "%d * %d", vList[i].Width, vList[i].Height );
					AddResolutionString( szResolution );
					if( vList[i].Width == nWidth && vList[i].Height == nHeight )
						bFound =true;
				}
				MeSprintf_s( szResolution, sizeof(szResolution)/sizeof(char) - 1, "%s", theXmlString.GetString( eText_Custom ));
				AddResolutionString( szResolution );

				if( bFound )
					MeSprintf_s( szResolution, sizeof(szResolution)/sizeof(char) - 1, "%d * %d", nWidth, nHeight );
				else
					m_pID_COMBOBOX_fenbianlu->GetListBox().SetCurSelIndex( vList.size() );

				m_pID_COMBOBOX_fenbianlu->GetEditInput().SetText( szResolution );
			}
			break;
		case SystemSetting::eSSC_ADVANCE:
			{
				m_pID_CHECKBOX_Advance->SetCheck( (bool)nValue );
				ID_CHECKBOX_AdvanceOnCheckBoxCheck( 0, (bool*)&nValue );
			}

			break;
		default:
			break;
		}
	}
}

void CUI_ID_FRAME_Systemset::AddResolutionString( const char* pszReslution )
{
	ControlList::S_List stList;
	stList.SetData( pszReslution );
	m_pID_COMBOBOX_fenbianlu->GetListBox().AddItem( &stList,NULL, false);
}

void CUI_ID_FRAME_Systemset::AddFSAAString( const char* pszFSAA )
{
	ControlList::S_List stList;
	stList.SetData( pszFSAA );
	m_pID_COMBOBOX_juchi->GetListBox().AddItem( &stList );
}

void CUI_ID_FRAME_Systemset::SetAdvance( bool bAdvance )
{
	if( !m_pID_FRAME_Systemset )
		return;
	SystemSetting::Instance()->SetLevel( SystemSetting::eSSC_ADVANCE, bAdvance  );
	m_pID_CHECKBOX_bloom->SetEnable( bAdvance);
	m_pID_TEXT_11->SetEnable( bAdvance );
	m_pID_CHECKBOX_yinying->SetEnable( bAdvance );
	m_pID_CHECKBOX_guangmang->SetEnable( bAdvance );
	m_pID_CHECKBOX_jingshen->SetEnable( bAdvance );

	SystemSetting::Instance()->CommitChanges();
}

void CUI_ID_FRAME_Systemset::RefreshFSAAUI()
{
	if( !m_pID_FRAME_Systemset )
		return;
	if( !m_pID_COMBOBOX_juchi )
		return;
	//refresh fsaa list
	m_pID_COMBOBOX_juchi->GetListBox().Clear();		

	std::vector<int> vFSAAList = SystemSetting::Instance()->GetFSAATypeList();

	int nValue = (int)SystemSetting::Instance()->GetLevel( SystemSetting::eSSC_MSAA );
	char szFSAA[50];
	for( int i = 0 ; i < vFSAAList.size() ; ++ i )
	{
		if( vFSAAList[i] == 0)// close fsaa
			MeSprintf_s( szFSAA, sizeof(szFSAA)/sizeof(char) - 1, "%s", s_pszClose );
		else
			MeSprintf_s( szFSAA, sizeof(szFSAA)/sizeof(char) - 1, "%dX", vFSAAList[i] );
		AddFSAAString( szFSAA );
	}

	if( nValue == 0)// close fsaa
		MeSprintf_s( szFSAA, sizeof(szFSAA)/sizeof(char) - 1, "%s", s_pszClose );
	else
		MeSprintf_s( szFSAA, sizeof(szFSAA)/sizeof(char) - 1, "%dX", nValue );
	m_pID_COMBOBOX_juchi->GetEditInput().SetText( szFSAA );
}

void CUI_ID_FRAME_Systemset::OnVisibleChanged( ControlObject* pSender )
{
	g_DynamicMapLoadOpenEvent = pSender->IsVisable();

}

void CUI_ID_FRAME_Systemset::SCROLLBAREX_allset_SetValue( int value )
{
	if( !m_pID_FRAME_Systemset )
		return;
	m_pID_SCROLLBAREX_allset->SetValue(value);
}