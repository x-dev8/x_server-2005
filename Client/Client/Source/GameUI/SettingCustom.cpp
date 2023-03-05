/********************************************************************
Created by UIEditor.exe
FileName: C:\Documents and Settings\liuchuanpeng\桌面\Ui\SettingCustom.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "SettingCustom.h"
#include "GameMain.h"
#include "SystemSetting.h"
#include "Me3d\Shader.h"
#include "Me3d\ShaderManager.h"
#include "Me3d/Engine/MeRenderManager.h"
#include "Me3d/Engine/MeBitSorter.h"
#include "Me3d/Engine/MeShimmerCollector.h"
#include "Me3d/Engine/MeAlphaCollector.h"
#include "Me3d\Engine\Engine.h"
#include "Common.h"

extern CHeroGame theHeroGame;
CUI_ID_FRAME_SettingCustom s_CUI_ID_FRAME_SettingCustom;
MAP_FRAME_RUN( s_CUI_ID_FRAME_SettingCustom, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_SettingCustom, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SettingCustom, ID_BUTTON_MinimizeOnButtonClick )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_SettingCustom, ID_CHECKBOX_LightLowOnCheckBoxCheck )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SettingCustom, ID_BUTTON_ClearOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SettingCustom, ID_BUTTON_CLOSEOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SettingCustom, ID_BUTTON_OkOnButtonClick )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_SettingCustom, ID_CHECKBOX_LightHighOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_SettingCustom, ID_CHECKBOX_GroundLowOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_SettingCustom, ID_CHECKBOX_TextureLowOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_SettingCustom, ID_CHECKBOX_ActionLowOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_SettingCustom, ID_CHECKBOX_WaterLowOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_SettingCustom, ID_CHECKBOX_GrassLowOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_SettingCustom, ID_CHECKBOX_GroundHighOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_SettingCustom, ID_CHECKBOX_TextureHighOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_SettingCustom, ID_CHECKBOX_ActionHighOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_SettingCustom, ID_CHECKBOX_WaterHighOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_SettingCustom, ID_CHECKBOX_GrassHighOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_SettingCustom, ID_CHECKBOX_ShadowLowOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_SettingCustom, ID_CHECKBOX_ShadowMiddleOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_SettingCustom, ID_CHECKBOX_ShadowHighOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_SettingCustom, ID_CHECKBOX_EffectLowOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_SettingCustom, ID_CHECKBOX_EffecMiddleOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_SettingCustom, ID_CHECKBOX_EffectHighOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_SettingCustom,ID_CHECKBOX_YinMiddleOnCheckBoxCheck)
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_SettingCustom,ID_CHECKBOX_YinLowOnCheckBoxCheck)
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_SettingCustom,ID_CHECKBOX_YinHighOnCheckBoxCheck)

MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_SettingCustom, ID_CHECKBOX_HdrOnOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_SettingCustom,ID_CHECKBOX_HdrOffOnCheckBoxCheck)
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_SettingCustom,ID_CHECKBOX_TerrainAOTUOnOnCheckBoxCheck)
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_SettingCustom,ID_CHECKBOX_TerrainAOTUOffOnCheckBoxCheck)

CUI_ID_FRAME_SettingCustom::CUI_ID_FRAME_SettingCustom()
{
	// Member
	m_pID_FRAME_SettingCustom = NULL;
	m_pID_PICTURE_Di = NULL;
	m_pID_BUTTON_Minimize = NULL;
	m_pID_CHECKBOX_LightLow = NULL;
	m_pID_BUTTON_Clear = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_BUTTON_Ok = NULL;
	m_pID_CHECKBOX_LightHigh = NULL;
	m_pID_CHECKBOX_GroundLow = NULL;
	m_pID_CHECKBOX_TextureLow = NULL;
	m_pID_CHECKBOX_ActionLow = NULL;
	m_pID_CHECKBOX_WaterLow = NULL;
	m_pID_CHECKBOX_GrassLow = NULL;
	m_pID_CHECKBOX_GroundHigh = NULL;
	m_pID_CHECKBOX_TextureHigh = NULL;
	m_pID_CHECKBOX_ActionHigh = NULL;
	m_pID_CHECKBOX_WaterHigh = NULL;
	m_pID_CHECKBOX_GrassHigh = NULL;
	m_pID_CHECKBOX_ShadowLow = NULL;
	m_pID_CHECKBOX_ShadowMiddle = NULL;
	m_pID_CHECKBOX_ShadowHigh = NULL;
	m_pID_CHECKBOX_EffectLow = NULL;
	m_pID_CHECKBOX_EffecMiddle = NULL;
	m_pID_CHECKBOX_EffectHigh = NULL;
	m_pID_CHECKBOX_YinMiddle = NULL;
	m_pID_CHECKBOX_YinLow = NULL;
	m_pID_CHECKBOX_YinHigh = NULL;

	m_pID_CHECKBOX_HdrOn = NULL;
	m_pID_CHECKBOX_HdrOff = NULL;
	m_pID_CHECKBOX_TerrainAOTUOff = NULL;
	m_pID_CHECKBOX_TerrainAOTUOn = NULL;


}
// Frame
bool CUI_ID_FRAME_SettingCustom::OnFrameRun()
{
	return true;
}
bool CUI_ID_FRAME_SettingCustom::OnFrameRender()
{
	return true;
}

void CUI_ID_FRAME_SettingCustom::ID_CHECKBOX_HdrOnOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  )
{


	m_pID_CHECKBOX_HdrOn->SetCheck(true);
	m_pID_CHECKBOX_HdrOff->SetCheck(false);

	SystemSetting::Instance()->SetLevel( SystemSetting::eSSC_HDR,1 );
	SystemSetting::Instance()->CommitChanges();


}
void CUI_ID_FRAME_SettingCustom::ID_CHECKBOX_HdrOffOnCheckBoxCheck(ControlObject* pSender, bool* pbChecked)
{

	m_pID_CHECKBOX_HdrOn->SetCheck(false);
	m_pID_CHECKBOX_HdrOff->SetCheck(true);

	SystemSetting::Instance()->SetLevel( SystemSetting::eSSC_HDR,0 );
	SystemSetting::Instance()->CommitChanges();

}
void CUI_ID_FRAME_SettingCustom::ID_CHECKBOX_TerrainAOTUOffOnCheckBoxCheck(ControlObject* pSender, bool* pbChecked)
{

	m_pID_CHECKBOX_TerrainAOTUOn->SetCheck(false);
	m_pID_CHECKBOX_TerrainAOTUOff->SetCheck(true);

	SystemSetting::Instance()->SetLevel( SystemSetting::eSSC_TERRAINAOTUTEXTURE,0 );
	SystemSetting::Instance()->CommitChanges();

}
void CUI_ID_FRAME_SettingCustom::ID_CHECKBOX_TerrainAOTUOnOnCheckBoxCheck(ControlObject* pSender, bool* pbChecked)
{

	m_pID_CHECKBOX_TerrainAOTUOn->SetCheck(true);
	m_pID_CHECKBOX_TerrainAOTUOff->SetCheck(false);

	SystemSetting::Instance()->SetLevel( SystemSetting::eSSC_TERRAINAOTUTEXTURE,1 );
	SystemSetting::Instance()->CommitChanges();

}
// Button
bool CUI_ID_FRAME_SettingCustom::ID_BUTTON_MinimizeOnButtonClick( ControlObject* pSender )
{
	return true;
}
// CheckBox
void CUI_ID_FRAME_SettingCustom::ID_CHECKBOX_LightLowOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	m_pID_CHECKBOX_LightHigh->SetCheck(false);
	m_pID_CHECKBOX_LightLow->SetCheck(true);

	SystemSetting::Instance()->SetLevel( SystemSetting::eSSC_Light,0 );
	SystemSetting::Instance()->CommitChanges();
}

// Button
bool CUI_ID_FRAME_SettingCustom::ID_BUTTON_ClearOnButtonClick( ControlObject* pSender )
{
	return true;
}
// Button
bool CUI_ID_FRAME_SettingCustom::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
{
	char szSetting[MAX_PATH] = {0};
	MeSprintf_s(szSetting,sizeof(szSetting)/sizeof(char) - 1, "%s/Client/UserData/%s", GetRootPath(), SystemSetting::Instance()->GetCustomSettingFile() );
	SystemSetting::Instance()->LoadSetting( szSetting );
	SystemSetting::Instance()->CommitChanges();
	SetVisable(false);
	return true;
}
// Button
bool CUI_ID_FRAME_SettingCustom::ID_BUTTON_OkOnButtonClick( ControlObject* pSender )
{
	SetVisable(false);

	char szSetting[MAX_PATH] = {0};
	MeSprintf_s(szSetting,sizeof(szSetting)/sizeof(char) - 1, "%s/Client/UserData/%s", GetRootPath(), SystemSetting::Instance()->GetCustomSettingFile() );
	SystemSetting::Instance()->SaveSetting( szSetting );	
	return true;
}
// CheckBox
void CUI_ID_FRAME_SettingCustom::ID_CHECKBOX_LightHighOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	m_pID_CHECKBOX_LightLow->SetCheck(false);
	m_pID_CHECKBOX_LightHigh->SetCheck(true);

	SystemSetting::Instance()->SetLevel( SystemSetting::eSSC_Light,1 );
	SystemSetting::Instance()->CommitChanges();
}
// CheckBox
void CUI_ID_FRAME_SettingCustom::ID_CHECKBOX_GroundLowOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{	
	m_pID_CHECKBOX_GroundHigh->SetCheck(false);
	m_pID_CHECKBOX_GroundLow->SetCheck(true);

	SystemSetting::Instance()->SetLevel( SystemSetting::eSSC_TERRAIN_DETAIL,0 );
	SystemSetting::Instance()->CommitChanges();
}

// CheckBox
void CUI_ID_FRAME_SettingCustom::ID_CHECKBOX_TextureLowOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	m_pID_CHECKBOX_TextureHigh->SetCheck(false);
	m_pID_CHECKBOX_TextureLow->SetCheck(true);

	SystemSetting::Instance()->SetLevel( SystemSetting::eSSC_TEXTURE_MIPMAP, 0);
	SystemSetting::Instance()->CommitChanges();
}
// CheckBox
void CUI_ID_FRAME_SettingCustom::ID_CHECKBOX_ActionLowOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	m_pID_CHECKBOX_ActionHigh->SetCheck(false);
	m_pID_CHECKBOX_ActionLow->SetCheck(true);

	SystemSetting::Instance()->SetLevel( SystemSetting::eSSC_AnimTimeSetp, 0 );
	SystemSetting::Instance()->CommitChanges();
}

// CheckBox
void CUI_ID_FRAME_SettingCustom::ID_CHECKBOX_WaterLowOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	m_pID_CHECKBOX_WaterHigh->SetCheck(false);
	m_pID_CHECKBOX_WaterLow->SetCheck(true);

	SystemSetting::Instance()->SetLevel( SystemSetting::eSSC_WATER, 0 );
	SystemSetting::Instance()->CommitChanges();
}

// CheckBox
void CUI_ID_FRAME_SettingCustom::ID_CHECKBOX_GrassLowOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	m_pID_CHECKBOX_GrassLow->SetCheck(true);
	m_pID_CHECKBOX_GrassHigh->SetCheck(false);

	SystemSetting::Instance()->SetLevel( SystemSetting::eSSC_GRASS, 0 );
	SystemSetting::Instance()->CommitChanges();
}

// CheckBox
void CUI_ID_FRAME_SettingCustom::ID_CHECKBOX_GroundHighOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	m_pID_CHECKBOX_GroundLow->SetCheck(false);
	m_pID_CHECKBOX_GroundHigh->SetCheck(true);

	SystemSetting::Instance()->SetLevel( SystemSetting::eSSC_TERRAIN_DETAIL, 1);
	SystemSetting::Instance()->CommitChanges();
}

// CheckBox
void CUI_ID_FRAME_SettingCustom::ID_CHECKBOX_TextureHighOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	m_pID_CHECKBOX_TextureLow->SetCheck(false);
	m_pID_CHECKBOX_TextureHigh->SetCheck(true);

	SystemSetting::Instance()->SetLevel( SystemSetting::eSSC_TEXTURE_MIPMAP,1);
	SystemSetting::Instance()->CommitChanges();
}

// CheckBox
void CUI_ID_FRAME_SettingCustom::ID_CHECKBOX_ActionHighOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	m_pID_CHECKBOX_ActionLow->SetCheck(false);
	m_pID_CHECKBOX_ActionHigh->SetCheck(true);

	SystemSetting::Instance()->SetLevel( SystemSetting::eSSC_AnimTimeSetp, 1 );
	SystemSetting::Instance()->CommitChanges();
}

// CheckBox
void CUI_ID_FRAME_SettingCustom::ID_CHECKBOX_WaterHighOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	m_pID_CHECKBOX_WaterLow->SetCheck(false);
	m_pID_CHECKBOX_WaterHigh->SetCheck(true);

	SystemSetting::Instance()->SetLevel( SystemSetting::eSSC_WATER, 1 );
	SystemSetting::Instance()->CommitChanges();
}

// CheckBox
void CUI_ID_FRAME_SettingCustom::ID_CHECKBOX_GrassHighOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	m_pID_CHECKBOX_GrassLow->SetCheck(false);
	m_pID_CHECKBOX_GrassHigh->SetCheck(true);

	SystemSetting::Instance()->SetLevel( SystemSetting::eSSC_GRASS, 1 );
	SystemSetting::Instance()->CommitChanges();
}

// CheckBox
void CUI_ID_FRAME_SettingCustom::ID_CHECKBOX_ShadowLowOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	m_pID_CHECKBOX_ShadowHigh->SetCheck(false);
	m_pID_CHECKBOX_ShadowMiddle->SetCheck(false);
	m_pID_CHECKBOX_ShadowLow->SetCheck(true);

	SystemSetting::Instance()->SetLevel( SystemSetting::eSSC_SHADOW, 0);
	SystemSetting::Instance()->CommitChanges();
}

// CheckBox
void CUI_ID_FRAME_SettingCustom::ID_CHECKBOX_ShadowMiddleOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	m_pID_CHECKBOX_ShadowLow->SetCheck(false);
	m_pID_CHECKBOX_ShadowHigh->SetCheck(false);
	m_pID_CHECKBOX_ShadowMiddle->SetCheck(true);

	SystemSetting::Instance()->SetLevel( SystemSetting::eSSC_SHADOW, 1 );
	SystemSetting::Instance()->CommitChanges();
}

// CheckBox
void CUI_ID_FRAME_SettingCustom::ID_CHECKBOX_ShadowHighOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	m_pID_CHECKBOX_ShadowMiddle->SetCheck(false);
	m_pID_CHECKBOX_ShadowLow->SetCheck(false);
	m_pID_CHECKBOX_ShadowHigh->SetCheck(true);

	SystemSetting::Instance()->SetLevel( SystemSetting::eSSC_SHADOW, 2 );
	SystemSetting::Instance()->CommitChanges();
}

// CheckBox
void CUI_ID_FRAME_SettingCustom::ID_CHECKBOX_EffectLowOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	m_pID_CHECKBOX_EffectLow->SetCheck(true);
	m_pID_CHECKBOX_EffecMiddle->SetCheck(false);
	m_pID_CHECKBOX_EffectHigh->SetCheck(false);

	SystemSetting::Instance()->SetLevel( SystemSetting::eSSC_Effect, 0 );
	SystemSetting::Instance()->CommitChanges();
}

// CheckBox
void CUI_ID_FRAME_SettingCustom::ID_CHECKBOX_EffecMiddleOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	m_pID_CHECKBOX_EffectLow->SetCheck(false);
	m_pID_CHECKBOX_EffecMiddle->SetCheck(true);
	m_pID_CHECKBOX_EffectHigh->SetCheck(false);

	SystemSetting::Instance()->SetLevel( SystemSetting::eSSC_Effect, 1 );
	SystemSetting::Instance()->CommitChanges();
}

// CheckBox
void CUI_ID_FRAME_SettingCustom::ID_CHECKBOX_EffectHighOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	m_pID_CHECKBOX_EffectLow->SetCheck(false);
	m_pID_CHECKBOX_EffecMiddle->SetCheck(false);
	m_pID_CHECKBOX_EffectHigh->SetCheck(true);

	SystemSetting::Instance()->SetLevel( SystemSetting::eSSC_Effect, 2 );
	SystemSetting::Instance()->CommitChanges();
}
void CUI_ID_FRAME_SettingCustom::ID_CHECKBOX_YinMiddleOnCheckBoxCheck(ControlObject* pSender, bool* pbChecked)
{
	m_pID_CHECKBOX_YinMiddle->SetCheck(true);
	m_pID_CHECKBOX_YinLow ->SetCheck(false);
	m_pID_CHECKBOX_YinHigh->SetCheck(false);
}
void CUI_ID_FRAME_SettingCustom::ID_CHECKBOX_YinLowOnCheckBoxCheck(ControlObject* pSender, bool* pbChecked)
{
	m_pID_CHECKBOX_YinMiddle->SetCheck(false);
	m_pID_CHECKBOX_YinLow ->SetCheck(true);
	m_pID_CHECKBOX_YinHigh->SetCheck(false);
}
void CUI_ID_FRAME_SettingCustom::ID_CHECKBOX_YinHighOnCheckBoxCheck(ControlObject* pSender, bool* pbChecked)
{
	m_pID_CHECKBOX_YinMiddle->SetCheck(false);
	m_pID_CHECKBOX_YinLow ->SetCheck(false);
	m_pID_CHECKBOX_YinHigh->SetCheck(true);
}
// 装载UI
bool CUI_ID_FRAME_SettingCustom::LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\SettingCustom.MEUI", false, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\SettingCustom.MEUI]失败")
			return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_SettingCustom::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_SettingCustom, s_CUI_ID_FRAME_SettingCustomOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_SettingCustom, s_CUI_ID_FRAME_SettingCustomOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_SettingCustom, ID_BUTTON_Minimize, s_CUI_ID_FRAME_SettingCustomID_BUTTON_MinimizeOnButtonClick );
	theUiManager.OnCheckBoxCheck( ID_FRAME_SettingCustom, ID_CHECKBOX_LightLow, s_CUI_ID_FRAME_SettingCustomID_CHECKBOX_LightLowOnCheckBoxCheck );
	theUiManager.OnButtonClick( ID_FRAME_SettingCustom, ID_BUTTON_Clear, s_CUI_ID_FRAME_SettingCustomID_BUTTON_ClearOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SettingCustom, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_SettingCustomID_BUTTON_CLOSEOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SettingCustom, ID_BUTTON_Ok, s_CUI_ID_FRAME_SettingCustomID_BUTTON_OkOnButtonClick );
	theUiManager.OnCheckBoxCheck( ID_FRAME_SettingCustom, ID_CHECKBOX_LightHigh, s_CUI_ID_FRAME_SettingCustomID_CHECKBOX_LightHighOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_SettingCustom, ID_CHECKBOX_GroundLow, s_CUI_ID_FRAME_SettingCustomID_CHECKBOX_GroundLowOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_SettingCustom, ID_CHECKBOX_TextureLow, s_CUI_ID_FRAME_SettingCustomID_CHECKBOX_TextureLowOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_SettingCustom, ID_CHECKBOX_ActionLow, s_CUI_ID_FRAME_SettingCustomID_CHECKBOX_ActionLowOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_SettingCustom, ID_CHECKBOX_WaterLow, s_CUI_ID_FRAME_SettingCustomID_CHECKBOX_WaterLowOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_SettingCustom, ID_CHECKBOX_GrassLow, s_CUI_ID_FRAME_SettingCustomID_CHECKBOX_GrassLowOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_SettingCustom, ID_CHECKBOX_GroundHigh, s_CUI_ID_FRAME_SettingCustomID_CHECKBOX_GroundHighOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_SettingCustom, ID_CHECKBOX_TextureHigh, s_CUI_ID_FRAME_SettingCustomID_CHECKBOX_TextureHighOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_SettingCustom, ID_CHECKBOX_ActionHigh, s_CUI_ID_FRAME_SettingCustomID_CHECKBOX_ActionHighOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_SettingCustom, ID_CHECKBOX_WaterHigh, s_CUI_ID_FRAME_SettingCustomID_CHECKBOX_WaterHighOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_SettingCustom, ID_CHECKBOX_GrassHigh, s_CUI_ID_FRAME_SettingCustomID_CHECKBOX_GrassHighOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_SettingCustom, ID_CHECKBOX_ShadowLow, s_CUI_ID_FRAME_SettingCustomID_CHECKBOX_ShadowLowOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_SettingCustom, ID_CHECKBOX_ShadowMiddle, s_CUI_ID_FRAME_SettingCustomID_CHECKBOX_ShadowMiddleOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_SettingCustom, ID_CHECKBOX_ShadowHigh, s_CUI_ID_FRAME_SettingCustomID_CHECKBOX_ShadowHighOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_SettingCustom, ID_CHECKBOX_EffectLow, s_CUI_ID_FRAME_SettingCustomID_CHECKBOX_EffectLowOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_SettingCustom, ID_CHECKBOX_EffecMiddle, s_CUI_ID_FRAME_SettingCustomID_CHECKBOX_EffecMiddleOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_SettingCustom, ID_CHECKBOX_EffectHigh, s_CUI_ID_FRAME_SettingCustomID_CHECKBOX_EffectHighOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_SettingCustom,  ID_CHECKBOX_YinHigh, s_CUI_ID_FRAME_SettingCustomID_CHECKBOX_YinHighOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_SettingCustom, ID_CHECKBOX_YinLow, s_CUI_ID_FRAME_SettingCustomID_CHECKBOX_YinLowOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_SettingCustom, ID_CHECKBOX_YinMiddle, s_CUI_ID_FRAME_SettingCustomID_CHECKBOX_YinMiddleOnCheckBoxCheck );


	theUiManager.OnCheckBoxCheck( ID_FRAME_SettingCustom, ID_CHECKBOX_HdrOn,          s_CUI_ID_FRAME_SettingCustomID_CHECKBOX_HdrOnOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_SettingCustom,  ID_CHECKBOX_HdrOff,        s_CUI_ID_FRAME_SettingCustomID_CHECKBOX_HdrOffOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_SettingCustom, ID_CHECKBOX_TerrainAOTUOff, s_CUI_ID_FRAME_SettingCustomID_CHECKBOX_TerrainAOTUOffOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_SettingCustom, ID_CHECKBOX_TerrainAOTUOn,  s_CUI_ID_FRAME_SettingCustomID_CHECKBOX_TerrainAOTUOnOnCheckBoxCheck );
	
	m_pID_FRAME_SettingCustom = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_SettingCustom );
	m_pID_PICTURE_Di = (ControlPicture*)theUiManager.FindControl( ID_FRAME_SettingCustom, ID_PICTURE_Di );
	m_pID_BUTTON_Minimize = (ControlButton*)theUiManager.FindControl( ID_FRAME_SettingCustom, ID_BUTTON_Minimize );
	m_pID_CHECKBOX_LightLow = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_SettingCustom, ID_CHECKBOX_LightLow );
	m_pID_BUTTON_Clear = (ControlButton*)theUiManager.FindControl( ID_FRAME_SettingCustom, ID_BUTTON_Clear );
	m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_FRAME_SettingCustom, ID_BUTTON_CLOSE );
	m_pID_BUTTON_Ok = (ControlButton*)theUiManager.FindControl( ID_FRAME_SettingCustom, ID_BUTTON_Ok );
	m_pID_CHECKBOX_LightHigh = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_SettingCustom, ID_CHECKBOX_LightHigh );
	m_pID_CHECKBOX_GroundLow = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_SettingCustom, ID_CHECKBOX_GroundLow );
	m_pID_CHECKBOX_TextureLow = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_SettingCustom, ID_CHECKBOX_TextureLow );
	m_pID_CHECKBOX_ActionLow = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_SettingCustom, ID_CHECKBOX_ActionLow );
	m_pID_CHECKBOX_WaterLow = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_SettingCustom, ID_CHECKBOX_WaterLow );
	m_pID_CHECKBOX_GrassLow = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_SettingCustom, ID_CHECKBOX_GrassLow );
	m_pID_CHECKBOX_GroundHigh = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_SettingCustom, ID_CHECKBOX_GroundHigh );
	m_pID_CHECKBOX_TextureHigh = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_SettingCustom, ID_CHECKBOX_TextureHigh );
	m_pID_CHECKBOX_ActionHigh = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_SettingCustom, ID_CHECKBOX_ActionHigh );
	m_pID_CHECKBOX_WaterHigh = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_SettingCustom, ID_CHECKBOX_WaterHigh );
	m_pID_CHECKBOX_GrassHigh = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_SettingCustom, ID_CHECKBOX_GrassHigh );
	m_pID_CHECKBOX_ShadowLow = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_SettingCustom, ID_CHECKBOX_ShadowLow );
	m_pID_CHECKBOX_ShadowMiddle = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_SettingCustom, ID_CHECKBOX_ShadowMiddle );
	m_pID_CHECKBOX_ShadowHigh = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_SettingCustom, ID_CHECKBOX_ShadowHigh );
	m_pID_CHECKBOX_EffectLow = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_SettingCustom, ID_CHECKBOX_EffectLow );
	m_pID_CHECKBOX_EffecMiddle = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_SettingCustom, ID_CHECKBOX_EffecMiddle );
	m_pID_CHECKBOX_EffectHigh = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_SettingCustom, ID_CHECKBOX_EffectHigh );
	m_pID_CHECKBOX_YinMiddle = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_SettingCustom, ID_CHECKBOX_YinMiddle );
	m_pID_CHECKBOX_YinLow       =(ControlCheckBox*)theUiManager.FindControl( ID_FRAME_SettingCustom, ID_CHECKBOX_YinLow );
	m_pID_CHECKBOX_YinHigh      =(ControlCheckBox*)theUiManager.FindControl( ID_FRAME_SettingCustom, ID_CHECKBOX_YinHigh );

	m_pID_CHECKBOX_HdrOn =             (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_SettingCustom, ID_CHECKBOX_HdrOn );
	m_pID_CHECKBOX_HdrOff =            (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_SettingCustom, ID_CHECKBOX_HdrOff );
	m_pID_CHECKBOX_TerrainAOTUOff     =(ControlCheckBox*)theUiManager.FindControl( ID_FRAME_SettingCustom, ID_CHECKBOX_TerrainAOTUOff );
	m_pID_CHECKBOX_TerrainAOTUOn      =(ControlCheckBox*)theUiManager.FindControl( ID_FRAME_SettingCustom, ID_CHECKBOX_TerrainAOTUOn );


	assert( m_pID_CHECKBOX_HdrOn );
	assert( m_pID_CHECKBOX_HdrOff );
	assert( m_pID_CHECKBOX_TerrainAOTUOff );
	assert( m_pID_CHECKBOX_TerrainAOTUOn );

	assert( m_pID_FRAME_SettingCustom );
	assert( m_pID_PICTURE_Di );
	assert( m_pID_BUTTON_Minimize );
	assert( m_pID_CHECKBOX_LightLow );
	assert( m_pID_BUTTON_Clear );
	assert( m_pID_BUTTON_CLOSE );
	assert( m_pID_BUTTON_Ok );
	assert( m_pID_CHECKBOX_LightHigh );
	assert( m_pID_CHECKBOX_GroundLow );
	assert( m_pID_CHECKBOX_TextureLow );
	assert( m_pID_CHECKBOX_ActionLow );
	assert( m_pID_CHECKBOX_WaterLow );
	assert( m_pID_CHECKBOX_GrassLow );
	assert( m_pID_CHECKBOX_GroundHigh );
	assert( m_pID_CHECKBOX_TextureHigh );
	assert( m_pID_CHECKBOX_ActionHigh );
	assert( m_pID_CHECKBOX_WaterHigh );
	assert( m_pID_CHECKBOX_GrassHigh );
	assert( m_pID_CHECKBOX_ShadowLow );
	assert( m_pID_CHECKBOX_ShadowMiddle );
	assert( m_pID_CHECKBOX_ShadowHigh );
	assert( m_pID_CHECKBOX_EffectLow );
	assert( m_pID_CHECKBOX_EffecMiddle );
	assert( m_pID_CHECKBOX_EffectHigh );
	assert(m_pID_CHECKBOX_YinMiddle );
	assert(m_pID_CHECKBOX_YinLow );
	assert(m_pID_CHECKBOX_YinHigh);
	SetVisable(false);
	return true;
}

// 卸载UI
bool CUI_ID_FRAME_SettingCustom::UnLoadUI()
{
	m_pID_FRAME_SettingCustom = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\SettingCustom.MEUI" );
}

// 是否可视
bool CUI_ID_FRAME_SettingCustom::IsVisable()
{
	if(!m_pID_FRAME_SettingCustom)
		return false;

	return m_pID_FRAME_SettingCustom->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_SettingCustom::SetVisable( const bool bVisable )
{
	if(!m_pID_FRAME_SettingCustom)
		return;

	m_pID_FRAME_SettingCustom->SetVisable( bVisable );
	if(bVisable)
		Refersh();
}

void CUI_ID_FRAME_SettingCustom::Refersh()
{
	if(!m_pID_FRAME_SettingCustom)
		return;

	for( int i = 0 ; i < SystemSetting::eSSC_TOTAL ; ++ i )
	{
		int nValue = (int)SystemSetting::Instance()->GetLevel( (SystemSetting::eSystemSettingCategory)i );
		switch( i )
		{
		case SystemSetting::eSSC_TERRAIN_DETAIL:  //地面精度
			{
				m_pID_CHECKBOX_GroundLow->SetCheck(false);
				m_pID_CHECKBOX_GroundHigh->SetCheck(false);
				if(nValue)
					m_pID_CHECKBOX_GroundHigh->SetCheck(true);
				else
					m_pID_CHECKBOX_GroundLow->SetCheck(true);
			}
			break;
		case SystemSetting::eSSC_TEXTURE_MIPMAP:  //贴图精度
			{
				m_pID_CHECKBOX_TextureHigh->SetCheck(false);
				m_pID_CHECKBOX_TextureLow->SetCheck(false);

				if(nValue)
					m_pID_CHECKBOX_TextureHigh->SetCheck(true);
				else
					m_pID_CHECKBOX_TextureLow->SetCheck(true);
			}
			break;
		case SystemSetting::eSSC_AnimTimeSetp:        //动画精度
			{
				m_pID_CHECKBOX_ActionHigh->SetCheck(false);
				m_pID_CHECKBOX_ActionLow->SetCheck(false);

				if(nValue)
					m_pID_CHECKBOX_ActionHigh->SetCheck(true);
				else
					m_pID_CHECKBOX_ActionLow->SetCheck(true);
			}
			break;
		case SystemSetting::eSSC_WATER:            //水面精度
			{
				m_pID_CHECKBOX_WaterHigh->SetCheck(false);
				m_pID_CHECKBOX_WaterLow->SetCheck(false);
				if(nValue)
					m_pID_CHECKBOX_WaterHigh->SetCheck(true);
				else
					m_pID_CHECKBOX_WaterLow->SetCheck(true);
			}
			break;
		case SystemSetting::eSSC_GRASS:            //水草细节
			{
				m_pID_CHECKBOX_GrassLow->SetCheck(false);
				m_pID_CHECKBOX_GrassHigh->SetCheck(false);
				if(nValue)
					m_pID_CHECKBOX_GrassHigh->SetCheck(true);
				else
					m_pID_CHECKBOX_GrassLow->SetCheck(true);
			}
			break;
		case SystemSetting::eSSC_SHADOW:            //阴影精度
			{
				m_pID_CHECKBOX_ShadowMiddle->SetCheck(false);
				m_pID_CHECKBOX_ShadowHigh->SetCheck(false);
				m_pID_CHECKBOX_ShadowLow->SetCheck(false);
				switch(nValue)
				{
				case 0:
					m_pID_CHECKBOX_ShadowLow->SetCheck(true);
					break;
				case  1:
					m_pID_CHECKBOX_ShadowMiddle->SetCheck(true);
					break;
				case 2:
					m_pID_CHECKBOX_ShadowHigh->SetCheck(true);
					break;
				}
			}
			break;
		case  SystemSetting::eSSC_Light:
			{
				m_pID_CHECKBOX_LightLow->SetCheck(false);
				m_pID_CHECKBOX_LightHigh->SetCheck(false);

				//光照精度
				if(graphics::ShaderManager::instance()->isUseShader())
					m_pID_CHECKBOX_LightHigh->SetCheck(true);
				else
					m_pID_CHECKBOX_LightLow->SetCheck(true);
			}
			break;
		case SystemSetting::eSSC_Effect:
			{
				//特效精度
				m_pID_CHECKBOX_EffectLow->SetCheck(false);
				m_pID_CHECKBOX_EffecMiddle->SetCheck(false);
				m_pID_CHECKBOX_EffectHigh->SetCheck(false);
				int nValue = GetEngine()->GetMaxPartNum();
				if(nValue < 5)
					m_pID_CHECKBOX_EffectLow->SetCheck(true);
				else if(nValue < 10)
					m_pID_CHECKBOX_EffecMiddle->SetCheck(true);
				else 
					m_pID_CHECKBOX_EffectHigh->SetCheck(true);
			}
			break;	
			case SystemSetting::eSSC_HDR:
				{
					m_pID_CHECKBOX_HdrOn->SetCheck(false);
					m_pID_CHECKBOX_HdrOff->SetCheck(false);
					if (nValue)
					{
					m_pID_CHECKBOX_HdrOn->SetCheck(true);
					}else
						m_pID_CHECKBOX_HdrOff->SetCheck(true);

				}

				break;

			case SystemSetting::eSSC_TERRAINAOTUTEXTURE:
				{

					LPDIRECT3DDEVICE9 RI = (LPDIRECT3DDEVICE9) (GetEngine()->GetRenderer()->GetRealDevice());
					D3DCAPS9 _caps;
					RI->GetDeviceCaps(&_caps);
						
					if( _caps.VertexShaderVersion < D3DVS_VERSION( 3, 0 ) || 
					_caps.PixelShaderVersion < D3DPS_VERSION( 3, 0 ) ) //lyh 地形凹凸纹理映射需要 3.0版本 如果显卡太老，不让这两个选项显示，玩家也就不会操作这个值
					{
								m_pID_CHECKBOX_TerrainAOTUOn->SetVisable(false);
								m_pID_CHECKBOX_TerrainAOTUOff->SetVisable(false);
								return ;
					}
						

					m_pID_CHECKBOX_TerrainAOTUOn->SetCheck(false);
					m_pID_CHECKBOX_TerrainAOTUOff->SetCheck(false);

					if (nValue)
					{
						m_pID_CHECKBOX_TerrainAOTUOn->SetCheck(true);
					}else
						m_pID_CHECKBOX_TerrainAOTUOff->SetCheck(true);

				}

					break;
		default:
			{
				m_pID_CHECKBOX_YinMiddle->SetCheck(true);
				m_pID_CHECKBOX_YinLow ->SetCheck(false);
				m_pID_CHECKBOX_YinHigh->SetCheck(false);
			}
			break;
		}
	}
}
