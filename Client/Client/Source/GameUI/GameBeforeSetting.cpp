/********************************************************************
	Created by UIEditor.exe
	FileName: E:\3Guo_Client_04.22\Data\Ui\GameBeforeSetting.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "GameBeforeSetting.h"
#include "XmlStringLanguage.h"
#include "Common.h"
#include "GameMain.h"
extern CHeroGame theHeroGame;

#define  USERSTTINGPATH ".\\UserData\\SystemSetting.config"

CUI_ID_FRAME_GameBeforeSetting s_CUI_ID_FRAME_GameBeforeSetting;
MAP_FRAME_RUN( s_CUI_ID_FRAME_GameBeforeSetting, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_GameBeforeSetting, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GameBeforeSetting, ID_BUTTON_DefaultOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GameBeforeSetting, ID_BUTTON_SetHighOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GameBeforeSetting, ID_BUTTON_SetMiddleOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GameBeforeSetting, ID_BUTTON_SetLowOnButtonClick )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameBeforeSetting, ID_CHECKBOX_WindowOnCheckBoxCheck )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GameBeforeSetting, ID_BUTTON_CustomOnButtonClick )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_GameBeforeSetting, ID_LIST_23209OnListSelectChange )
MAP_SCROLL_BAREX_UPDATE_POS_CALLBACK( s_CUI_ID_FRAME_GameBeforeSetting, ID_SCROLLBAREX_SoundEffectOnScrollBarExUpdatePos )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GameBeforeSetting, ID_BUTTON_OKOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GameBeforeSetting, ID_BUTTON_CancelOnButtonClick )
MAP_SCROLL_BAREX_UPDATE_POS_CALLBACK( s_CUI_ID_FRAME_GameBeforeSetting, ID_SCROLLBAREX_MusicOnScrollBarExUpdatePos )
MAP_SCROLL_BAREX_UPDATE_POS_CALLBACK( s_CUI_ID_FRAME_GameBeforeSetting, ID_SCROLLBAREX_GuangJiaoOnScrollBarExUpdatePos )
MAP_SCROLL_BAREX_UPDATE_POS_CALLBACK( s_CUI_ID_FRAME_GameBeforeSetting, ID_SCROLLBAREX_JingTouOnScrollBarExUpdatePos )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameBeforeSetting, ID_CHECKBOX_FullScreenOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameBeforeSetting, ID_CHECKBOX_NoMusicOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameBeforeSetting, ID_CHECKBOX_NoSoundEffectOnCheckBoxCheck )
MAP_SCROLL_BAREX_UPDATE_POS_CALLBACK( s_CUI_ID_FRAME_GameBeforeSetting, ID_SCROLLBAREX_TongPingOnScrollBarExUpdatePos )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameBeforeSetting, ID_CHECKBOX_CAMERA_SHAKEOnCheckBoxCheck )
MAP_COMBO_BOX_CHANGE_CALLBACK( s_CUI_ID_FRAME_GameBeforeSetting, ID_COMBOBOX_MSOnComboBoxChange )

MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameBeforeSetting, ID_CHECKBOX_LightLowOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameBeforeSetting, ID_CHECKBOX_LightHighOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameBeforeSetting, ID_CHECKBOX_GrassLowOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameBeforeSetting, ID_CHECKBOX_GrassHighOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameBeforeSetting, ID_CHECKBOX_GroundLowOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameBeforeSetting, ID_CHECKBOX_GroundHighOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameBeforeSetting, ID_CHECKBOX_HdrOffOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameBeforeSetting, ID_CHECKBOX_HdrOnOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameBeforeSetting, ID_CHECKBOX_TextureLowOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameBeforeSetting, ID_CHECKBOX_TextureHighOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameBeforeSetting, ID_CHECKBOX_TerrainAOTUOffOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameBeforeSetting, ID_CHECKBOX_TerrainAOTUOnOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameBeforeSetting, ID_CHECKBOX_ActionLowOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameBeforeSetting, ID_CHECKBOX_ActionHighOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameBeforeSetting, ID_CHECKBOX_EffectLowOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameBeforeSetting, ID_CHECKBOX_EffecMiddleOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameBeforeSetting, ID_CHECKBOX_EffectHighOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameBeforeSetting, ID_CHECKBOX_ShadowLowOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameBeforeSetting, ID_CHECKBOX_ShadowMiddleOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameBeforeSetting, ID_CHECKBOX_ShadowHighOnCheckBoxCheck )

CUI_ID_FRAME_GameBeforeSetting::CUI_ID_FRAME_GameBeforeSetting()
{
	// Member
	m_pID_FRAME_GameBeforeSetting = NULL;
	m_pID_BUTTON_Default = NULL;
	m_pID_BUTTON_SetHigh = NULL;
	m_pID_BUTTON_SetMiddle = NULL;
	m_pID_BUTTON_SetLow = NULL;
	m_pID_CHECKBOX_Window = NULL;
	m_pID_BUTTON_Custom = NULL;
	m_pID_LIST_23209 = NULL;
	m_pID_SCROLLBAREX_SoundEffect = NULL;
	m_pID_BUTTON_OK = NULL;
	m_pID_BUTTON_Cancel = NULL;
	m_pID_SCROLLBAREX_Music = NULL;
	m_pID_SCROLLBAREX_GuangJiao = NULL;
	m_pID_SCROLLBAREX_JingTou = NULL;
	m_pID_CHECKBOX_FullScreen = NULL;
	m_pID_CHECKBOX_NoMusic = NULL;
	m_pID_CHECKBOX_NoSoundEffect = NULL;
	m_pID_TEXT_Mode = NULL;
	m_pID_SCROLLBAREX_TongPing = NULL;
	m_pID_CHECKBOX_CAMERA_SHAKE = NULL;
	m_pID_COMBOBOX_MS = NULL;

	m_pID_CHECKBOX_LightLow = NULL;
	m_pID_CHECKBOX_LightHigh = NULL;
	m_pID_CHECKBOX_GrassLow = NULL;
	m_pID_CHECKBOX_GrassHigh = NULL;
	m_pID_CHECKBOX_GroundLow = NULL;
	m_pID_CHECKBOX_GroundHigh = NULL;
	m_pID_CHECKBOX_HdrOff = NULL;
	m_pID_CHECKBOX_HdrOn = NULL;
	m_pID_CHECKBOX_TextureLow = NULL;
	m_pID_CHECKBOX_TextureHigh = NULL;
	m_pID_CHECKBOX_TerrainAOTUOff = NULL;
	m_pID_CHECKBOX_TerrainAOTUOn = NULL;
	m_pID_CHECKBOX_ActionLow = NULL;
	m_pID_CHECKBOX_ActionHigh = NULL;
	m_pID_CHECKBOX_EffectLow = NULL;
	m_pID_CHECKBOX_EffecMiddle = NULL;
	m_pID_CHECKBOX_EffectHigh = NULL;
	m_pID_CHECKBOX_ShadowLow = NULL;
	m_pID_CHECKBOX_ShadowMiddle = NULL;
	m_pID_CHECKBOX_ShadowHigh = NULL;


	memset(m_Settings,0,sizeof(m_Settings));
	memset(m_LastSettings,0,sizeof(m_LastSettings));
	
	

}
	// Frame  等会要写一个当前的配置列表 ，用来取消用。
	bool CUI_ID_FRAME_GameBeforeSetting::OnFrameRun()
	{
		return true;
	}
	bool CUI_ID_FRAME_GameBeforeSetting::OnFrameRender()
	{
		return true;
	}
	// Button 默认设置按钮
	bool CUI_ID_FRAME_GameBeforeSetting::ID_BUTTON_DefaultOnButtonClick( ControlObject* pSender )
	{
		SystemSetting::Instance()->LoadSetting();

		
		SystemSetting::Instance()->CommitChanges();
        theHeroGame.SetSlowCPU(1);
		

		for (int i = 0 ; i < SystemSetting::eSSC_TOTAL ; i++)
		{
			m_Settings[i] = SystemSetting::Instance()->GetSetings()[i];
			m_LastSettings[i] = SystemSetting::Instance()->GetSetings()[i];
		}

		Refresh();

		SystemSetting::Instance()->SaveSetting(USERSTTINGPATH);

		return true;
	}

	// Button  确定按钮
	bool CUI_ID_FRAME_GameBeforeSetting::ID_BUTTON_OKOnButtonClick( ControlObject* pSender )
	{
		SetVisable(false);
		SystemSetting::Instance()->bCanSet = false; //游戏前不能设置的一些相关设置。

		//设置确定后当前选择的 游戏配置。提交给 SystemSetting
		for (int i = 0 ; i < SystemSetting::eSSC_TOTAL ; i++)
		{

			SystemSetting::eSystemSettingCategory _t = (SystemSetting::eSystemSettingCategory)i;

			SystemSetting::Instance()->SetLevel(_t,m_Settings[i]);
		}
		

		SystemSetting::Instance()->CommitChanges();

		memcpy(m_LastSettings,m_Settings,sizeof(m_LastSettings));

		Refresh();
		SystemSetting::Instance()->SaveSetting(USERSTTINGPATH);
		SystemSetting::Instance()->bCanSet = true;
		return true;
	}

	// Button
	bool CUI_ID_FRAME_GameBeforeSetting::ID_BUTTON_CancelOnButtonClick( ControlObject* pSender )
	{
		SetVisable(false);
		memcpy(m_Settings,m_LastSettings,sizeof(m_LastSettings));
		Refresh();
		return true;
	}


	// CheckBox 窗口选项 ====================================================================================================================
	void CUI_ID_FRAME_GameBeforeSetting::ID_CHECKBOX_WindowOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
	{
	
		SetLevel(SystemSetting::eSSC_WINDOWMODE,1); //设置窗口模式为0
        Refresh();
		
	}

	//全屏选项
	void CUI_ID_FRAME_GameBeforeSetting::ID_CHECKBOX_FullScreenOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
	{
		SetLevel(SystemSetting::eSSC_WINDOWMODE,0); //设置窗口模式为0
		Refresh();
	}


	// Button ================================================================================================================================
	// 品质按钮相关
	bool CUI_ID_FRAME_GameBeforeSetting::ID_BUTTON_SetHighOnButtonClick( ControlObject* pSender )
	{
		LoadQuilityConfig(eQuility_High);\
		theHeroGame.SetSlowCPU(0);
		return true;
	}
	// Button
	bool CUI_ID_FRAME_GameBeforeSetting::ID_BUTTON_SetMiddleOnButtonClick( ControlObject* pSender )
	{
		LoadQuilityConfig(eQuility_Middle);
		theHeroGame.SetSlowCPU(1);
		return true;
	}
	// Button
	bool CUI_ID_FRAME_GameBeforeSetting::ID_BUTTON_SetLowOnButtonClick( ControlObject* pSender )
	{
		LoadQuilityConfig(eQuility_Low);
		theHeroGame.SetSlowCPU(1);
		return true;
	}
	// Button
	bool CUI_ID_FRAME_GameBeforeSetting::ID_BUTTON_CustomOnButtonClick( ControlObject* pSender )
	{
		LoadQuilityConfig(eQuility_Custom);
		return true;
	}

	
	// List 分辨率列表
	void CUI_ID_FRAME_GameBeforeSetting::ID_LIST_23209OnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
	{
	}

	


	void CUI_ID_FRAME_GameBeforeSetting::ID_CHECKBOX_CAMERA_SHAKEOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
	{
		SetLevel(SystemSetting::eSSC_CameraShake, !m_Settings[SystemSetting::eSSC_CameraShake]);
	}

	// ComboBox
	void CUI_ID_FRAME_GameBeforeSetting::ID_COMBOBOX_MSOnComboBoxChange( ControlObject* pSender, const char* szData )
	{
		//抗锯齿。

		if (strstr(szData, "关闭") != NULL)
		{
			SetLevel(SystemSetting::eSSC_MSAA, 0);
		}
		else
		{
			int sample = 2;
			sscanf(szData, "%dx", &sample);
			SetLevel(SystemSetting::eSSC_MSAA, sample);
		}

		Refresh();

	}
	//===================================================================================================================

	// ScrollBarEx
	void CUI_ID_FRAME_GameBeforeSetting::ID_SCROLLBAREX_SoundEffectOnScrollBarExUpdatePos( ControlObject* pSender, int n )
	{
	}


	// ScrollBarEx
	void CUI_ID_FRAME_GameBeforeSetting::ID_SCROLLBAREX_MusicOnScrollBarExUpdatePos( ControlObject* pSender, int n )
	{
	}
	// ScrollBarEx
	void CUI_ID_FRAME_GameBeforeSetting::ID_SCROLLBAREX_GuangJiaoOnScrollBarExUpdatePos( ControlObject* pSender, int n )
	{
	}
	// ScrollBarEx
	void CUI_ID_FRAME_GameBeforeSetting::ID_SCROLLBAREX_JingTouOnScrollBarExUpdatePos( ControlObject* pSender, int n )
	{
	}
	// CheckBox

	// CheckBox
	void CUI_ID_FRAME_GameBeforeSetting::ID_CHECKBOX_NoMusicOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
	{
	}
	// CheckBox
	void CUI_ID_FRAME_GameBeforeSetting::ID_CHECKBOX_NoSoundEffectOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
	{
	}
	// ScrollBarEx
	void CUI_ID_FRAME_GameBeforeSetting::ID_SCROLLBAREX_TongPingOnScrollBarExUpdatePos( ControlObject* pSender, int n )
	{
	}

void ID_LIST_SELECTOnListDBClick( ControlObject* pSender, ControlList::S_List* pItem )
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
		
		s_CUI_ID_FRAME_GameBeforeSetting.SetLevel(SystemSetting::eSSC_RESOLUTION,nValue);
	}


	// 装载UI
bool CUI_ID_FRAME_GameBeforeSetting::_LoadUI() //在加载login.meui 处执行加载该ui
	{
		DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\GameBeforeSetting.MEUI" );
		if ( dwResult == 0 )
		{
			MESSAGE_BOX("读取文件[Data\\UI\\GameBeforeSetting.MEUI]失败")
			return false;
		}
		return DoControlConnect();
	}
	// 关连控件
	bool CUI_ID_FRAME_GameBeforeSetting::DoControlConnect()
	{
		theUiManager.OnFrameRun( ID_FRAME_GameBeforeSetting, s_CUI_ID_FRAME_GameBeforeSettingOnFrameRun );
		theUiManager.OnFrameRender( ID_FRAME_GameBeforeSetting, s_CUI_ID_FRAME_GameBeforeSettingOnFrameRender );
theUiManager.OnButtonClick( ID_FRAME_GameBeforeSetting, ID_BUTTON_Default, s_CUI_ID_FRAME_GameBeforeSettingID_BUTTON_DefaultOnButtonClick );
theUiManager.OnButtonClick( ID_FRAME_GameBeforeSetting, ID_BUTTON_SetHigh, s_CUI_ID_FRAME_GameBeforeSettingID_BUTTON_SetHighOnButtonClick );
theUiManager.OnButtonClick( ID_FRAME_GameBeforeSetting, ID_BUTTON_SetMiddle, s_CUI_ID_FRAME_GameBeforeSettingID_BUTTON_SetMiddleOnButtonClick );
theUiManager.OnButtonClick( ID_FRAME_GameBeforeSetting, ID_BUTTON_SetLow, s_CUI_ID_FRAME_GameBeforeSettingID_BUTTON_SetLowOnButtonClick );
theUiManager.OnCheckBoxCheck( ID_FRAME_GameBeforeSetting, ID_CHECKBOX_Window, s_CUI_ID_FRAME_GameBeforeSettingID_CHECKBOX_WindowOnCheckBoxCheck );
theUiManager.OnButtonClick( ID_FRAME_GameBeforeSetting, ID_BUTTON_Custom, s_CUI_ID_FRAME_GameBeforeSettingID_BUTTON_CustomOnButtonClick );
theUiManager.OnListSelectChange( ID_FRAME_GameBeforeSetting, ID_LIST_23209, s_CUI_ID_FRAME_GameBeforeSettingID_LIST_23209OnListSelectChange );
theUiManager.OnScrollBarExUpdatePos( ID_FRAME_GameBeforeSetting, ID_SCROLLBAREX_SoundEffect, s_CUI_ID_FRAME_GameBeforeSettingID_SCROLLBAREX_SoundEffectOnScrollBarExUpdatePos );
theUiManager.OnButtonClick( ID_FRAME_GameBeforeSetting, ID_BUTTON_OK, s_CUI_ID_FRAME_GameBeforeSettingID_BUTTON_OKOnButtonClick );
theUiManager.OnButtonClick( ID_FRAME_GameBeforeSetting, ID_BUTTON_Cancel, s_CUI_ID_FRAME_GameBeforeSettingID_BUTTON_CancelOnButtonClick );
theUiManager.OnScrollBarExUpdatePos( ID_FRAME_GameBeforeSetting, ID_SCROLLBAREX_Music, s_CUI_ID_FRAME_GameBeforeSettingID_SCROLLBAREX_MusicOnScrollBarExUpdatePos );
theUiManager.OnScrollBarExUpdatePos( ID_FRAME_GameBeforeSetting, ID_SCROLLBAREX_GuangJiao, s_CUI_ID_FRAME_GameBeforeSettingID_SCROLLBAREX_GuangJiaoOnScrollBarExUpdatePos );
theUiManager.OnScrollBarExUpdatePos( ID_FRAME_GameBeforeSetting, ID_SCROLLBAREX_JingTou, s_CUI_ID_FRAME_GameBeforeSettingID_SCROLLBAREX_JingTouOnScrollBarExUpdatePos );
theUiManager.OnCheckBoxCheck( ID_FRAME_GameBeforeSetting, ID_CHECKBOX_FullScreen, s_CUI_ID_FRAME_GameBeforeSettingID_CHECKBOX_FullScreenOnCheckBoxCheck );
theUiManager.OnCheckBoxCheck( ID_FRAME_GameBeforeSetting, ID_CHECKBOX_NoMusic, s_CUI_ID_FRAME_GameBeforeSettingID_CHECKBOX_NoMusicOnCheckBoxCheck );
theUiManager.OnCheckBoxCheck( ID_FRAME_GameBeforeSetting, ID_CHECKBOX_NoSoundEffect, s_CUI_ID_FRAME_GameBeforeSettingID_CHECKBOX_NoSoundEffectOnCheckBoxCheck );
theUiManager.OnScrollBarExUpdatePos( ID_FRAME_GameBeforeSetting, ID_SCROLLBAREX_TongPing, s_CUI_ID_FRAME_GameBeforeSettingID_SCROLLBAREX_TongPingOnScrollBarExUpdatePos );
theUiManager.OnCheckBoxCheck( ID_FRAME_GameBeforeSetting, ID_CHECKBOX_CAMERA_SHAKE, s_CUI_ID_FRAME_GameBeforeSettingID_CHECKBOX_CAMERA_SHAKEOnCheckBoxCheck );
theUiManager.OnComboBoxChange( ID_FRAME_GameBeforeSetting, ID_COMBOBOX_MS, s_CUI_ID_FRAME_GameBeforeSettingID_COMBOBOX_MSOnComboBoxChange );

theUiManager.OnCheckBoxCheck( ID_FRAME_GameBeforeSetting, ID_CHECKBOX_LightLow, s_CUI_ID_FRAME_GameBeforeSettingID_CHECKBOX_LightLowOnCheckBoxCheck );
theUiManager.OnCheckBoxCheck( ID_FRAME_GameBeforeSetting, ID_CHECKBOX_LightHigh, s_CUI_ID_FRAME_GameBeforeSettingID_CHECKBOX_LightHighOnCheckBoxCheck );
theUiManager.OnCheckBoxCheck( ID_FRAME_GameBeforeSetting, ID_CHECKBOX_GrassLow, s_CUI_ID_FRAME_GameBeforeSettingID_CHECKBOX_GrassLowOnCheckBoxCheck );
theUiManager.OnCheckBoxCheck( ID_FRAME_GameBeforeSetting, ID_CHECKBOX_GrassHigh, s_CUI_ID_FRAME_GameBeforeSettingID_CHECKBOX_GrassHighOnCheckBoxCheck );
theUiManager.OnCheckBoxCheck( ID_FRAME_GameBeforeSetting, ID_CHECKBOX_GroundLow, s_CUI_ID_FRAME_GameBeforeSettingID_CHECKBOX_GroundLowOnCheckBoxCheck );
theUiManager.OnCheckBoxCheck( ID_FRAME_GameBeforeSetting, ID_CHECKBOX_GroundHigh, s_CUI_ID_FRAME_GameBeforeSettingID_CHECKBOX_GroundHighOnCheckBoxCheck );
theUiManager.OnCheckBoxCheck( ID_FRAME_GameBeforeSetting, ID_CHECKBOX_HdrOff, s_CUI_ID_FRAME_GameBeforeSettingID_CHECKBOX_HdrOffOnCheckBoxCheck );
theUiManager.OnCheckBoxCheck( ID_FRAME_GameBeforeSetting, ID_CHECKBOX_HdrOn, s_CUI_ID_FRAME_GameBeforeSettingID_CHECKBOX_HdrOnOnCheckBoxCheck );
theUiManager.OnCheckBoxCheck( ID_FRAME_GameBeforeSetting, ID_CHECKBOX_TextureLow, s_CUI_ID_FRAME_GameBeforeSettingID_CHECKBOX_TextureLowOnCheckBoxCheck );
theUiManager.OnCheckBoxCheck( ID_FRAME_GameBeforeSetting, ID_CHECKBOX_TextureHigh, s_CUI_ID_FRAME_GameBeforeSettingID_CHECKBOX_TextureHighOnCheckBoxCheck );
theUiManager.OnCheckBoxCheck( ID_FRAME_GameBeforeSetting, ID_CHECKBOX_TerrainAOTUOff, s_CUI_ID_FRAME_GameBeforeSettingID_CHECKBOX_TerrainAOTUOffOnCheckBoxCheck );
theUiManager.OnCheckBoxCheck( ID_FRAME_GameBeforeSetting, ID_CHECKBOX_TerrainAOTUOn, s_CUI_ID_FRAME_GameBeforeSettingID_CHECKBOX_TerrainAOTUOnOnCheckBoxCheck );
theUiManager.OnCheckBoxCheck( ID_FRAME_GameBeforeSetting, ID_CHECKBOX_ActionLow, s_CUI_ID_FRAME_GameBeforeSettingID_CHECKBOX_ActionLowOnCheckBoxCheck );
theUiManager.OnCheckBoxCheck( ID_FRAME_GameBeforeSetting, ID_CHECKBOX_ActionHigh, s_CUI_ID_FRAME_GameBeforeSettingID_CHECKBOX_ActionHighOnCheckBoxCheck );
theUiManager.OnCheckBoxCheck( ID_FRAME_GameBeforeSetting, ID_CHECKBOX_EffectLow, s_CUI_ID_FRAME_GameBeforeSettingID_CHECKBOX_EffectLowOnCheckBoxCheck );
theUiManager.OnCheckBoxCheck( ID_FRAME_GameBeforeSetting, ID_CHECKBOX_EffecMiddle, s_CUI_ID_FRAME_GameBeforeSettingID_CHECKBOX_EffecMiddleOnCheckBoxCheck );
theUiManager.OnCheckBoxCheck( ID_FRAME_GameBeforeSetting, ID_CHECKBOX_EffectHigh, s_CUI_ID_FRAME_GameBeforeSettingID_CHECKBOX_EffectHighOnCheckBoxCheck );
theUiManager.OnCheckBoxCheck( ID_FRAME_GameBeforeSetting, ID_CHECKBOX_ShadowLow, s_CUI_ID_FRAME_GameBeforeSettingID_CHECKBOX_ShadowLowOnCheckBoxCheck );
theUiManager.OnCheckBoxCheck( ID_FRAME_GameBeforeSetting, ID_CHECKBOX_ShadowMiddle, s_CUI_ID_FRAME_GameBeforeSettingID_CHECKBOX_ShadowMiddleOnCheckBoxCheck );
theUiManager.OnCheckBoxCheck( ID_FRAME_GameBeforeSetting, ID_CHECKBOX_ShadowHigh, s_CUI_ID_FRAME_GameBeforeSettingID_CHECKBOX_ShadowHighOnCheckBoxCheck );


		m_pID_FRAME_GameBeforeSetting = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_GameBeforeSetting );
		m_pID_BUTTON_Default = (ControlButton*)theUiManager.FindControl( ID_FRAME_GameBeforeSetting, ID_BUTTON_Default );
		m_pID_BUTTON_SetHigh = (ControlButton*)theUiManager.FindControl( ID_FRAME_GameBeforeSetting, ID_BUTTON_SetHigh );
		m_pID_BUTTON_SetMiddle = (ControlButton*)theUiManager.FindControl( ID_FRAME_GameBeforeSetting, ID_BUTTON_SetMiddle );
		m_pID_BUTTON_SetLow = (ControlButton*)theUiManager.FindControl( ID_FRAME_GameBeforeSetting, ID_BUTTON_SetLow );
		m_pID_CHECKBOX_Window = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameBeforeSetting, ID_CHECKBOX_Window );
		m_pID_BUTTON_Custom = (ControlButton*)theUiManager.FindControl( ID_FRAME_GameBeforeSetting, ID_BUTTON_Custom );
		m_pID_LIST_23209 = (ControlList*)theUiManager.FindControl( ID_FRAME_GameBeforeSetting, ID_LIST_23209 );
		m_pID_SCROLLBAREX_SoundEffect = (ControlScrollBarEx*)theUiManager.FindControl( ID_FRAME_GameBeforeSetting, ID_SCROLLBAREX_SoundEffect );
		m_pID_BUTTON_OK = (ControlButton*)theUiManager.FindControl( ID_FRAME_GameBeforeSetting, ID_BUTTON_OK );
		m_pID_BUTTON_Cancel = (ControlButton*)theUiManager.FindControl( ID_FRAME_GameBeforeSetting, ID_BUTTON_Cancel );
		m_pID_SCROLLBAREX_Music = (ControlScrollBarEx*)theUiManager.FindControl( ID_FRAME_GameBeforeSetting, ID_SCROLLBAREX_Music );
		m_pID_SCROLLBAREX_GuangJiao = (ControlScrollBarEx*)theUiManager.FindControl( ID_FRAME_GameBeforeSetting, ID_SCROLLBAREX_GuangJiao );
		m_pID_SCROLLBAREX_JingTou = (ControlScrollBarEx*)theUiManager.FindControl( ID_FRAME_GameBeforeSetting, ID_SCROLLBAREX_JingTou );
		m_pID_CHECKBOX_FullScreen = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameBeforeSetting, ID_CHECKBOX_FullScreen );
		m_pID_CHECKBOX_NoMusic = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameBeforeSetting, ID_CHECKBOX_NoMusic );
		m_pID_CHECKBOX_NoSoundEffect = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameBeforeSetting, ID_CHECKBOX_NoSoundEffect );
		m_pID_TEXT_Mode = (ControlText*)theUiManager.FindControl( ID_FRAME_GameBeforeSetting, ID_TEXT_Mode );
		m_pID_SCROLLBAREX_TongPing = (ControlScrollBarEx*)theUiManager.FindControl( ID_FRAME_GameBeforeSetting, ID_SCROLLBAREX_TongPing );
		m_pID_CHECKBOX_CAMERA_SHAKE = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameBeforeSetting, ID_CHECKBOX_CAMERA_SHAKE );
		m_pID_COMBOBOX_MS = (ControlComboBox*)theUiManager.FindControl( ID_FRAME_GameBeforeSetting, ID_COMBOBOX_MS );


		m_pID_CHECKBOX_LightLow = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameBeforeSetting, ID_CHECKBOX_LightLow );
		m_pID_CHECKBOX_LightHigh = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameBeforeSetting, ID_CHECKBOX_LightHigh );
		m_pID_CHECKBOX_GrassLow = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameBeforeSetting, ID_CHECKBOX_GrassLow );
		m_pID_CHECKBOX_GrassHigh = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameBeforeSetting, ID_CHECKBOX_GrassHigh );
		m_pID_CHECKBOX_GroundLow = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameBeforeSetting, ID_CHECKBOX_GroundLow );
		m_pID_CHECKBOX_GroundHigh = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameBeforeSetting, ID_CHECKBOX_GroundHigh );
		m_pID_CHECKBOX_HdrOff = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameBeforeSetting, ID_CHECKBOX_HdrOff );
		m_pID_CHECKBOX_HdrOn = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameBeforeSetting, ID_CHECKBOX_HdrOn );
		m_pID_CHECKBOX_TextureLow = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameBeforeSetting, ID_CHECKBOX_TextureLow );
		m_pID_CHECKBOX_TextureHigh = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameBeforeSetting, ID_CHECKBOX_TextureHigh );
		m_pID_CHECKBOX_TerrainAOTUOff = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameBeforeSetting, ID_CHECKBOX_TerrainAOTUOff );
		m_pID_CHECKBOX_TerrainAOTUOn = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameBeforeSetting, ID_CHECKBOX_TerrainAOTUOn );
		m_pID_CHECKBOX_ActionLow = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameBeforeSetting, ID_CHECKBOX_ActionLow );
		m_pID_CHECKBOX_ActionHigh = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameBeforeSetting, ID_CHECKBOX_ActionHigh );
		m_pID_CHECKBOX_EffectLow = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameBeforeSetting, ID_CHECKBOX_EffectLow );
		m_pID_CHECKBOX_EffecMiddle = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameBeforeSetting, ID_CHECKBOX_EffecMiddle );
		m_pID_CHECKBOX_EffectHigh = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameBeforeSetting, ID_CHECKBOX_EffectHigh );
		m_pID_CHECKBOX_ShadowLow = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameBeforeSetting, ID_CHECKBOX_ShadowLow );
		m_pID_CHECKBOX_ShadowMiddle = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameBeforeSetting, ID_CHECKBOX_ShadowMiddle );
		m_pID_CHECKBOX_ShadowHigh = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameBeforeSetting, ID_CHECKBOX_ShadowHigh );


		assert( m_pID_FRAME_GameBeforeSetting );
		assert( m_pID_BUTTON_Default );
		assert( m_pID_BUTTON_SetHigh );
		assert( m_pID_BUTTON_SetMiddle );
		assert( m_pID_BUTTON_SetLow );
		assert( m_pID_CHECKBOX_Window );
		assert( m_pID_BUTTON_Custom );
		assert( m_pID_LIST_23209 );
		assert( m_pID_SCROLLBAREX_SoundEffect );
		assert( m_pID_BUTTON_OK );
		assert( m_pID_BUTTON_Cancel );
		assert( m_pID_SCROLLBAREX_Music );
		assert( m_pID_SCROLLBAREX_GuangJiao );
		assert( m_pID_SCROLLBAREX_JingTou );
		assert( m_pID_CHECKBOX_FullScreen );
		assert( m_pID_CHECKBOX_NoMusic );
		assert( m_pID_CHECKBOX_NoSoundEffect );
		assert( m_pID_TEXT_Mode );
		assert( m_pID_SCROLLBAREX_TongPing );
		assert( m_pID_CHECKBOX_CAMERA_SHAKE );
		assert( m_pID_COMBOBOX_MS );

		assert( m_pID_CHECKBOX_LightLow );
		assert( m_pID_CHECKBOX_LightHigh );
		assert( m_pID_CHECKBOX_GrassLow );
		assert( m_pID_CHECKBOX_GrassHigh );
		assert( m_pID_CHECKBOX_GroundLow );
		assert( m_pID_CHECKBOX_GroundHigh );
		assert( m_pID_CHECKBOX_HdrOff );
		assert( m_pID_CHECKBOX_HdrOn );
		assert( m_pID_CHECKBOX_TextureLow );
		assert( m_pID_CHECKBOX_TextureHigh );
		assert( m_pID_CHECKBOX_TerrainAOTUOff );
		assert( m_pID_CHECKBOX_TerrainAOTUOn );
		assert( m_pID_CHECKBOX_ActionLow );
		assert( m_pID_CHECKBOX_ActionHigh );
		assert( m_pID_CHECKBOX_EffectLow );
		assert( m_pID_CHECKBOX_EffecMiddle );
		assert( m_pID_CHECKBOX_EffectHigh );
		assert( m_pID_CHECKBOX_ShadowLow );
		assert( m_pID_CHECKBOX_ShadowMiddle );
		assert( m_pID_CHECKBOX_ShadowHigh );


		m_pID_FRAME_GameBeforeSetting->SetVisable(false); //加载时候设置不可见。
		m_pID_LIST_23209->SetLBtnDownFun(ID_LIST_SELECTOnListDBClick);

		CreateDirectory("UserData",NULL); //创建userData 目录。
		LoadGameSetting();
		


		return true;
	}
	// 卸载UI
bool CUI_ID_FRAME_GameBeforeSetting::_UnLoadUI()
	{
		m_pID_FRAME_GameBeforeSetting = NULL;
		return theUiManager.RemoveFrame( "Data\\UI\\GameBeforeSetting.MEUI" );
	}
	// 是否可视
	bool CUI_ID_FRAME_GameBeforeSetting::_IsVisable()
	{
		return m_pID_FRAME_GameBeforeSetting->IsVisable();
	}
	// 设置是否可视
	void CUI_ID_FRAME_GameBeforeSetting::SetVisable( const bool bVisable )
	{
		m_pID_FRAME_GameBeforeSetting->SetVisable( bVisable );
	}


	bool CUI_ID_FRAME_GameBeforeSetting::LoadGameSetting()
	{

		SystemSetting::Instance()->LoadSetting(USERSTTINGPATH);

		for (int i = 0 ; i < SystemSetting::eSSC_TOTAL ; i++)
		{
			m_Settings[i] = SystemSetting::Instance()->GetSetings()[i];
			m_LastSettings[i] = SystemSetting::Instance()->GetSetings()[i];
		}

SystemSetting::Instance()->CommitChanges();
		Refresh();
		
		

		return false;
	}
	bool CUI_ID_FRAME_GameBeforeSetting::SaveGameSetting()
	{

		SystemSetting::Instance()->SaveSetting(USERSTTINGPATH);

		return false;
	}

	bool CUI_ID_FRAME_GameBeforeSetting::SetLevel(SystemSetting::eSystemSettingCategory _Type, unsigned int uiValue)
	{
		m_Settings[_Type] = uiValue;
			return false;
	}

	//添加分辨率
	void CUI_ID_FRAME_GameBeforeSetting::AddResolutionString( const char* pszReslution )
	{
		ControlList::S_List stItem;
		stItem.SetData(pszReslution);
		m_pID_LIST_23209->AddItem(&stItem);
	}

	//设置品质 这里改变控件显示。
	void CUI_ID_FRAME_GameBeforeSetting::LoadQuilityConfig(eQuility eValue)
	{
		switch(eValue)
		{
		case eQuility_High: //高品质
			{
				m_pID_TEXT_Mode->SetText(theXmlString.GetString(eText_GameSettingHigh));//高品质
				SystemSetting::Instance()->LoadSetting(SystemSetting::eSSL_MEDIUM );
				//SystemSetting::Instance()->CommitChanges();

				SystemSetting::Instance()->SetLevel( SystemSetting::eSSC_GLOBAL_LEVEL, 2 );
			}
			break;
		case eQuility_Middle: //中品质
			{
				m_pID_TEXT_Mode->SetText(theXmlString.GetString(eText_GameSettingMiddle));//中品质
				SystemSetting::Instance()->LoadSetting(SystemSetting::eSSL_LOW_MEDIUM );
				//SystemSetting::Instance()->CommitChanges();

				SystemSetting::Instance()->SetLevel( SystemSetting::eSSC_GLOBAL_LEVEL, 1 );
			}
			break;
		case eQuility_Low:    //低品质
			{
				m_pID_TEXT_Mode->SetText(theXmlString.GetString(eText_GameSettingLow));//低品质
				SystemSetting::Instance()->LoadSetting(SystemSetting::eSSL_LOW );
				//SystemSetting::Instance()->CommitChanges();

				SystemSetting::Instance()->SetLevel( SystemSetting::eSSC_GLOBAL_LEVEL, 0 );
			}
			break;
		case eQuility_Custom:  //自定义
			{
				m_pID_TEXT_Mode->SetText(theXmlString.GetString(eText_GameSettingCustom));//自定义
				//s_CUI_ID_FRAME_SettingCustom.SetVisable(true);

				SystemSetting::Instance()->SetLevel( SystemSetting::eSSC_GLOBAL_LEVEL, 5 );
			}
			break;
		default:
			break;
		}
		//设置ui属性
		for (int i = 0 ; i < SystemSetting::eSSC_TOTAL ; i++)
		{
			m_Settings[i] = SystemSetting::Instance()->GetSetings()[i];
		}

          Refresh();
		
	}


	//只刷新界面的显示 其他什么都不做。 
	void CUI_ID_FRAME_GameBeforeSetting::Refresh(bool bResolution)
	{
	       
			for (int i = 0 ; i < SystemSetting::eSSC_TOTAL ; i++)
			{
				int _value = m_Settings[i];
				int _value2 = m_LastSettings[i];

				//if(_value == _value2) //如果当前设置 和上一次设置的值是一样的 跳过
				//	continue;

				switch (i)
				{
				case SystemSetting::eSSC_CameraShake:	 //镜头抖动
					{

						SetLevel(SystemSetting::eSSC_CameraShake, _value);
					}
					break;
				case SystemSetting::eSSC_GLOBAL_LEVEL:	 //全局设置,0-4共五级,5时为自定义
					{
					if(_value == 0)
						m_pID_TEXT_Mode->SetText(theXmlString.GetString(eText_GameSettingLow));
					else if(_value == 1)
						m_pID_TEXT_Mode->SetText(theXmlString.GetString(eText_GameSettingMiddle));
					else if(_value == 2)
						m_pID_TEXT_Mode->SetText(theXmlString.GetString(eText_GameSettingHigh));
					else if(_value == 5)
						m_pID_TEXT_Mode->SetText(theXmlString.GetString(eText_GameSettingCustom));
					}
					break;
				case SystemSetting::eSSC_MSAA:			 //抗锯齿
					{
						if (m_pID_COMBOBOX_MS != NULL)
						{
							m_pID_COMBOBOX_MS->GetEditInput().SetReadOnly(true);
							ControlList &listbox = m_pID_COMBOBOX_MS->GetListBox();
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
							GetItemTextByMSAALevel(_value, szItemText);
							m_pID_COMBOBOX_MS->GetEditInput().SetText(szItemText);
						}
					}
					break;
				case SystemSetting::eSSC_WINDOWMODE:	 //窗口模式
					{
						 if (_value)
						 {
							 m_pID_CHECKBOX_Window->SetCheck(true);
							 m_pID_CHECKBOX_FullScreen->SetCheck(false);
						 }else
						 {
							 m_pID_CHECKBOX_Window->SetCheck(false);
							 m_pID_CHECKBOX_FullScreen->SetCheck(true);
						 }
					}
					break;
				case SystemSetting::eSSC_RESOLUTION:	 //分辨率
					{
						int nWidth = 1024;
						int nHeight = 768 ;
						bool bFound = false;
						if (_value > 1000)
						{
							nWidth = ((_value) >> 16) & 0x0000FFFF;
							nHeight = _value & 0x0000FFFF;
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

						if( bFound )
							MeSprintf_s( szResolution, sizeof(szResolution)/sizeof(char) - 1, "%d * %d", nWidth, nHeight );
						else
							m_pID_LIST_23209->SetCurSelIndex(vList.size());
					}
					break;
				case SystemSetting::eSSC_Light:          //光照精度
					{
						if (_value)
						{
							m_pID_CHECKBOX_LightLow->SetCheck(false);
							m_pID_CHECKBOX_LightHigh->SetCheck(true);

						}else
						{
							m_pID_CHECKBOX_LightLow->SetCheck(true);
							m_pID_CHECKBOX_LightHigh->SetCheck(false);
						}
						
					}
					break;
				case SystemSetting::eSSC_Effect:         //特效精度
					{
						m_pID_CHECKBOX_EffectLow->SetCheck(false);
						m_pID_CHECKBOX_EffecMiddle->SetCheck(false);
						m_pID_CHECKBOX_EffectHigh->SetCheck(false);

						if (_value == 0)
							m_pID_CHECKBOX_EffectLow->SetCheck(true);
						if(_value == 1)
							m_pID_CHECKBOX_EffecMiddle->SetCheck(true);
						if(_value == 2)
							m_pID_CHECKBOX_EffectHigh->SetCheck(true);
						

					}
					break;
				case SystemSetting::eSSC_AnimTimeSetp:	 //动画精度
					{
							m_pID_CHECKBOX_ActionLow->SetCheck(false);
							m_pID_CHECKBOX_ActionHigh->SetCheck(false);

							if (_value == 0)
								m_pID_CHECKBOX_ActionLow->SetCheck(true);
							else
                                m_pID_CHECKBOX_ActionHigh->SetCheck(true);
					}
					break;
				case SystemSetting::eSSC_HDR:                //hdr
					{
							m_pID_CHECKBOX_HdrOff->SetCheck(false);
							m_pID_CHECKBOX_HdrOn->SetCheck(false);

							if (_value == 0)
								m_pID_CHECKBOX_HdrOff->SetCheck(true);
							else
								m_pID_CHECKBOX_HdrOn->SetCheck(true);

					}
					break;
				case SystemSetting::eSSC_TERRAINAOTUTEXTURE:  //地形凹凸纹理映射
					{
							m_pID_CHECKBOX_TerrainAOTUOff->SetCheck(false);
							m_pID_CHECKBOX_TerrainAOTUOn->SetCheck(false);

							if (_value == 0)
							m_pID_CHECKBOX_TerrainAOTUOff->SetCheck(true);
							else
							m_pID_CHECKBOX_TerrainAOTUOn->SetCheck(true);
					}
					break;
				case SystemSetting::eSSC_TEXTURE_MIPMAP: //贴图精度
					{
						m_pID_CHECKBOX_TextureLow->SetCheck(false);
							m_pID_CHECKBOX_TextureHigh->SetCheck(false);

							if(_value == 0)
							m_pID_CHECKBOX_TextureLow->SetCheck(true);
							else
							m_pID_CHECKBOX_TextureHigh->SetCheck(true);
					}
					break;

				case SystemSetting::eSSC_SHADOW:		 //阴影效果
					{
							m_pID_CHECKBOX_ShadowLow->SetCheck(false);
							m_pID_CHECKBOX_ShadowMiddle->SetCheck(false);
							m_pID_CHECKBOX_ShadowHigh->SetCheck(false);

							if(_value == 0)
							m_pID_CHECKBOX_ShadowLow->SetCheck(true);
							if(_value == 1)
							m_pID_CHECKBOX_ShadowMiddle->SetCheck(true);
							if(_value == 2)
							m_pID_CHECKBOX_ShadowHigh->SetCheck(true);
					}
					break;
				case SystemSetting::eSSC_TERRAIN_DETAIL: //地形混合细节
					{
							
							m_pID_CHECKBOX_GroundLow->SetCheck(false);
							m_pID_CHECKBOX_GroundHigh->SetCheck(false);

							if(_value == 0)
							m_pID_CHECKBOX_GroundLow->SetCheck(true);
							else
							m_pID_CHECKBOX_GroundHigh->SetCheck(true);
					}
					break;

				case SystemSetting::eSSC_GRASS:			 //草地
					{
							m_pID_CHECKBOX_GrassLow->SetCheck(false);
							m_pID_CHECKBOX_GrassHigh->SetCheck(false);

							if(_value == 0)
							m_pID_CHECKBOX_GrassLow->SetCheck(true);
							else
							m_pID_CHECKBOX_GrassHigh->SetCheck(true);
					}
					break;


//以下几种 程序都没有用到，都在一些屏蔽的ui中 能用的只能充默认配置文件中开启 建议关闭，以免发生未知错误。

					//case SystemSetting::eSSC_SKELETON:		 //骨骼动画
					//	break;
					//case SystemSetting::eSSC_DOF:			 //景深
					//	break;
					//	case SystemSetting::eSSC_BLOOM:			 //全屏泛光
					//	break;
					//case SystemSetting::eSSC_LIGHTSHAFT:	 //体积光
					//	break;
					//case SystemSetting::eSSC_VERTICLESYNC:	 //垂直同步
					//	break;
					//case SystemSetting::eSSC_FONT_SHADOW:	 //字体质量
					//	break;
					//	case SystemSetting::eSSC_WATER:			 //水面效果
					//		break;
					//	case SystemSetting::eSSC_SKY:			 //天气效果
					//		break;
					//	case SystemSetting::eSSC_BRIGHT:		 //亮度
					//		break;
					//	case SystemSetting::eSSC_LOWFPS:		 //节能模式
					//		break;
					//	case SystemSetting::eSSC_RENDER_DISTANCE://绘制距离
					//		break;
					//case SystemSetting::eSSC_ADVANCE:		 //高级效果
					//	break;
				}
				
			}
	
	}


	void CUI_ID_FRAME_GameBeforeSetting::GetItemTextByMSAALevel(int msaaLevel, char *szItemText)
	{
		if (msaaLevel == 0)
			strcpy(szItemText, "关闭");
		else
			sprintf(szItemText, "%dx", msaaLevel);
	}


	void CUI_ID_FRAME_GameBeforeSetting::ID_CHECKBOX_LightLowOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
	{
		SetLevel(SystemSetting::eSSC_Light,0);
		Refresh();
	}
	// CheckBox
	void CUI_ID_FRAME_GameBeforeSetting::ID_CHECKBOX_LightHighOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
	{
		SetLevel(SystemSetting::eSSC_Light, 1);
		Refresh();
	}
	// CheckBox
	void CUI_ID_FRAME_GameBeforeSetting::ID_CHECKBOX_GrassLowOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
	{
		SetLevel(SystemSetting::eSSC_GRASS, 0);
		Refresh();
	}
	// CheckBox
	void CUI_ID_FRAME_GameBeforeSetting::ID_CHECKBOX_GrassHighOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
	{
		SetLevel(SystemSetting::eSSC_GRASS, 1);
		Refresh();
	}
	// CheckBox
	void CUI_ID_FRAME_GameBeforeSetting::ID_CHECKBOX_GroundLowOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
	{
		SetLevel(SystemSetting::eSSC_TERRAIN_DETAIL,0);
		Refresh();
	}
	// CheckBox
	void CUI_ID_FRAME_GameBeforeSetting::ID_CHECKBOX_GroundHighOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
	{
		SetLevel(SystemSetting::eSSC_TERRAIN_DETAIL,1);
		Refresh();
	}
	// CheckBox
	void CUI_ID_FRAME_GameBeforeSetting::ID_CHECKBOX_HdrOffOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
	{
		SetLevel(SystemSetting::eSSC_HDR,0);
		Refresh();
	}
	// CheckBox
	void CUI_ID_FRAME_GameBeforeSetting::ID_CHECKBOX_HdrOnOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
	{
		SetLevel(SystemSetting::eSSC_HDR,1);
		Refresh();
	}
	// CheckBox
	void CUI_ID_FRAME_GameBeforeSetting::ID_CHECKBOX_TextureLowOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
	{
		SetLevel(SystemSetting::eSSC_TEXTURE_MIPMAP, 0);
		Refresh();
	}
	// CheckBox
	void CUI_ID_FRAME_GameBeforeSetting::ID_CHECKBOX_TextureHighOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
	{
		SetLevel(SystemSetting::eSSC_TEXTURE_MIPMAP, 1);
		Refresh();
	}
	// CheckBox
	void CUI_ID_FRAME_GameBeforeSetting::ID_CHECKBOX_TerrainAOTUOffOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
	{
		SetLevel(SystemSetting::eSSC_TERRAINAOTUTEXTURE,0);
		Refresh();
	}
	// CheckBox
	void CUI_ID_FRAME_GameBeforeSetting::ID_CHECKBOX_TerrainAOTUOnOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
	{
		SetLevel(SystemSetting::eSSC_TERRAINAOTUTEXTURE,1);
		Refresh();
	}
	// CheckBox
	void CUI_ID_FRAME_GameBeforeSetting::ID_CHECKBOX_ActionLowOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
	{
		SetLevel(SystemSetting::eSSC_AnimTimeSetp, 0);
		Refresh();
	}
	// CheckBox
	void CUI_ID_FRAME_GameBeforeSetting::ID_CHECKBOX_ActionHighOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
	{
		SetLevel(SystemSetting::eSSC_AnimTimeSetp, 1);
		Refresh();
	}
	// CheckBox
	void CUI_ID_FRAME_GameBeforeSetting::ID_CHECKBOX_EffectLowOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
	{
		SetLevel(SystemSetting::eSSC_Effect, 0 );
		Refresh();
	}
	// CheckBox
	void CUI_ID_FRAME_GameBeforeSetting::ID_CHECKBOX_EffecMiddleOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
	{
		SetLevel(SystemSetting::eSSC_Effect, 1 );
		Refresh();
	}
	// CheckBox
	void CUI_ID_FRAME_GameBeforeSetting::ID_CHECKBOX_EffectHighOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
	{
		SetLevel(SystemSetting::eSSC_Effect, 2);
		Refresh();
	}
	// CheckBox
	void CUI_ID_FRAME_GameBeforeSetting::ID_CHECKBOX_ShadowLowOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
	{
		SetLevel(SystemSetting::eSSC_SHADOW, 0);
		Refresh();
	}
	// CheckBox
	void CUI_ID_FRAME_GameBeforeSetting::ID_CHECKBOX_ShadowMiddleOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
	{
		SetLevel(SystemSetting::eSSC_SHADOW, 1);
		Refresh();
	}
	// CheckBox
	void CUI_ID_FRAME_GameBeforeSetting::ID_CHECKBOX_ShadowHighOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
	{
		SetLevel(SystemSetting::eSSC_SHADOW, 2);
		Refresh();
	}

	/*
	 目前游戏设置能通过手动设置的只有以下选项


	 GlobalLevel
	 TextureMipMap
	 Shadow
	 TerrainDetail
	 Grass
	 MSAA
	 WindowMode
	 Resolution
	 Light
	 Effect
	 AnimTimeStep
	 CameraShake
	 Hdr
	 TerrainBump
	
	

	m_SettingNames[eSSC_GLOBAL_LEVEL]	 = "GlobalLevel";	 //全局设置,0-4共五级,5时为自定义
	m_SettingNames[eSSC_ADVANCE]		 = "Advance";		 //高级效果
	m_SettingNames[eSSC_TEXTURE_MIPMAP]  = "TextureMipMap";  //贴图精度
	m_SettingNames[eSSC_BRIGHT]			 = "Bright";         //亮度
	m_SettingNames[eSSC_LOWFPS]			 = "LowFPS";		 //节能模式
	m_SettingNames[eSSC_RENDER_DISTANCE] = "RenderDistance"; //绘制距离
	m_SettingNames[eSSC_SHADOW]			 = "Shadow";		 //阴影效果
	m_SettingNames[eSSC_TERRAIN_DETAIL]	 = "TerrainDetail";  //地形混合细节
	m_SettingNames[eSSC_FONT_SHADOW]	 = "FontShadow";	 //字体质量
	m_SettingNames[eSSC_WATER]			 = "Water";			 //水面效果
	m_SettingNames[eSSC_SKY]			 = "Sky";			 //天气效果
	m_SettingNames[eSSC_GRASS]			 = "Grass";			 //草地
	m_SettingNames[eSSC_DOF]			 = "Dof";			 //景深
	m_SettingNames[eSSC_BLOOM]			 = "Bloom";			 //全屏泛光
	m_SettingNames[eSSC_LIGHTSHAFT]		 = "LightShaft";	 //体积光
	m_SettingNames[eSSC_VERTICLESYNC]	 = "VerticleSync";	 //垂直同步
	m_SettingNames[eSSC_MSAA]			 = "MSAA";			 //抗锯齿
	m_SettingNames[eSSC_WINDOWMODE]		 = "WindowMode";	 //窗口模式
	m_SettingNames[eSSC_RESOLUTION]		 = "Resolution";	 //分辨率
	m_SettingNames[eSSC_SKELETON]		 = "SkeletonShader"; //骨骼动画 
	m_SettingNames[eSSC_Light]           = "Light";          //灯光精度
	m_SettingNames[eSSC_Effect]          = "Effect";         //特效精度
	m_SettingNames[eSSC_AnimTimeSetp]	 = "AnimTimeStep";	 //动画精度
	m_SettingNames[eSSC_CameraShake]	 = "CameraShake";	 //镜头抖动

	m_SettingNames[eSSC_HDR]	             = "Hdr";	 //镜头抖动
	m_SettingNames[eSSC_TERRAINAOTUTEXTURE]	 = "TerrainBump";	 //镜头抖动


*/