/********************************************************************
Created by UIEditor.exe
FileName: D:\My Documents\桌面\gamesetting\GameSettingFunction.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "GameSettingFunction.h"
#include "GameSetting.h"
#include "ui/MiniMapUI.h"
#include "ui/exmain.h"
#include "PopIntro.h"
#include "ChangeEquip.h"
#include "GameSettingUIBase.h"
CUI_ID_FRAME_GameSettingFunction s_CUI_ID_FRAME_GameSettingFunction;
MAP_FRAME_RUN( s_CUI_ID_FRAME_GameSettingFunction, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_GameSettingFunction, OnFrameRender )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSettingFunction, ID_CHECKBOX_WeisuiOnCheckBoxCheck )
MAP_SCROLL_BAREX_UPDATE_POS_CALLBACK( s_CUI_ID_FRAME_GameSettingFunction, ID_SCROLLBAREX_ScreenPlayerNumberOnScrollBarExUpdatePos )
MAP_SCROLL_BAREX_UPDATE_POS_CALLBACK( s_CUI_ID_FRAME_GameSettingFunction, ID_SCROLLBAREX_FovOnScrollBarExUpdatePos )
MAP_SCROLL_BAREX_UPDATE_POS_CALLBACK( s_CUI_ID_FRAME_GameSettingFunction, ID_SCROLLBAREX_CameraMaxDistanceOnScrollBarExUpdatePos )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSettingFunction, ID_CHECKBOX_VerticleViewOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSettingFunction, ID_CHECKBOX_ShowHelmetOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSettingFunction, ID_CHECKBOX_Suo45OnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSettingFunction, ID_CHECKBOX_HelpOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSettingFunction, ID_CHECKBOX_ChangeEquipOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSettingFunction, ID_CHECKBOX_LockMainOnCheckBoxCheck )
CUI_ID_FRAME_GameSettingFunction::CUI_ID_FRAME_GameSettingFunction()
{
	// Member
	m_pID_FRAME_GameSettingFunction = NULL;
	m_pID_TEXT_ScreenPlayerNumber = NULL;
	m_pID_TEXT_Fov = NULL;
	m_pID_TEXT_CameraMaxDistance = NULL;
	m_pID_TEXT_Weisui = NULL;
	m_pID_CHECKBOX_Weisui = NULL;
	m_pID_SCROLLBAREX_ScreenPlayerNumber = NULL;
	m_pID_SCROLLBAREX_Fov = NULL;
	m_pID_SCROLLBAREX_CameraMaxDistance = NULL;
	m_pID_TEXT_VerticleView = NULL;
	m_pID_TEXT_ShowHelmet = NULL;
	m_pID_TEXT_Suo45 = NULL;
	m_pID_CHECKBOX_VerticleView = NULL;
	m_pID_CHECKBOX_ShowHelmet = NULL;
	m_pID_CHECKBOX_Suo45 = NULL;
	m_pID_TEXT_Help = NULL;
	m_pID_CHECKBOX_Help = NULL;
	m_pID_TEXT_LockMain = NULL;
	m_pID_CHECKBOX_LockMain = NULL;

}
// Frame
bool CUI_ID_FRAME_GameSettingFunction::OnFrameRun()
{
	return true;
}
bool CUI_ID_FRAME_GameSettingFunction::OnFrameRender()
{
	return true;
}
// CheckBox
void CUI_ID_FRAME_GameSettingFunction::ID_CHECKBOX_WeisuiOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	GameSetting::Instance()->SetLevel( GameSetting::eGSC_FOLLOWCAMERA, *pbChecked );
	if( *pbChecked )
	{
		GameSetting::Instance()->SetLevel( GameSetting::eGSC_45CAMERA, false );
		GameSetting::Instance()->SetLevel( GameSetting::eGSC_VERTICLEVIEW,  false );
	}		
	GameSetting::Instance()->CommitChanges();
	RefreshUI();
}
// ScrollBarEx
void CUI_ID_FRAME_GameSettingFunction::ID_SCROLLBAREX_ScreenPlayerNumberOnScrollBarExUpdatePos( ControlObject* pSender, int n )
{
	GameSetting::Instance()->SetLevel( GameSetting::eGSC_SHOWPLAYERNUMBER, n );
	GameSetting::Instance()->CommitChanges();
	n = n / 4 + 20;//[20 - 270]
	m_pID_SCROLLBAREX_ScreenPlayerNumber->SetCustomValue( n );
	s_CUI_ID_FRAME_MiniMap.SetButtonToCustom();
}
// ScrollBarEx
void CUI_ID_FRAME_GameSettingFunction::ID_SCROLLBAREX_FovOnScrollBarExUpdatePos( ControlObject* pSender, int n )
{
	GameSetting::Instance()->SetLevel( GameSetting::eGSC_FOV, n );
	GameSetting::Instance()->CommitChanges();
}
// ScrollBarEx
void CUI_ID_FRAME_GameSettingFunction::ID_SCROLLBAREX_CameraMaxDistanceOnScrollBarExUpdatePos( ControlObject* pSender, int n )
{
	GameSetting::Instance()->SetLevel( GameSetting::eGSC_MAXCAMERADISTANCE,  n );
	GameSetting::Instance()->CommitChanges();
}
// CheckBox
void CUI_ID_FRAME_GameSettingFunction::ID_CHECKBOX_VerticleViewOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	GameSetting::Instance()->SetLevel( GameSetting::eGSC_VERTICLEVIEW, *pbChecked );
	if( *pbChecked )
	{
		GameSetting::Instance()->SetLevel( GameSetting::eGSC_45CAMERA, false );
		GameSetting::Instance()->SetLevel( GameSetting::eGSC_FOLLOWCAMERA,  false );
	}		
	GameSetting::Instance()->CommitChanges();
	RefreshUI();
}
// CheckBox
void CUI_ID_FRAME_GameSettingFunction::ID_CHECKBOX_ShowHelmetOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	GameSetting::Instance()->SetLevel( GameSetting::eGSC_SHOWHELMET, *pbChecked );
	GameSetting::Instance()->CommitChanges();
}
// CheckBox
void CUI_ID_FRAME_GameSettingFunction::ID_CHECKBOX_Suo45OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	GameSetting::Instance()->SetLevel( GameSetting::eGSC_45CAMERA, *pbChecked );
	if( *pbChecked )
	{
		GameSetting::Instance()->SetLevel( GameSetting::eGSC_FOLLOWCAMERA, false );
		GameSetting::Instance()->SetLevel( GameSetting::eGSC_VERTICLEVIEW,  false );
	}		
	GameSetting::Instance()->CommitChanges();
	RefreshUI();
}

// CheckBox
void CUI_ID_FRAME_GameSettingFunction::ID_CHECKBOX_ChangeEquipOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
    s_CUI_ID_FRAME_ChangeEquip.SetVisable(*pbChecked);
}

// CheckBox
void CUI_ID_FRAME_GameSettingFunction::ID_CHECKBOX_LockMainOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	//第一个参数没有使用
//	s_CUI_ID_FRAME_Exmain.ID_CHECKBOX_LockOnCheckBoxCheck(NULL,pbChecked);
	s_CUI_ID_FRAME_Exmain.SetCheckBoxLock(*pbChecked);
}

// 装载UI
bool CUI_ID_FRAME_GameSettingFunction::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\GameSettingFunction.MEUI" );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\GameSettingFunction.MEUI]失败")
			return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_GameSettingFunction::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_GameSettingFunction, s_CUI_ID_FRAME_GameSettingFunctionOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_GameSettingFunction, s_CUI_ID_FRAME_GameSettingFunctionOnFrameRender );
	theUiManager.OnCheckBoxCheck( ID_FRAME_GameSettingFunction, ID_CHECKBOX_Weisui, s_CUI_ID_FRAME_GameSettingFunctionID_CHECKBOX_WeisuiOnCheckBoxCheck );
	theUiManager.OnScrollBarExUpdatePos( ID_FRAME_GameSettingFunction, ID_SCROLLBAREX_ScreenPlayerNumber, s_CUI_ID_FRAME_GameSettingFunctionID_SCROLLBAREX_ScreenPlayerNumberOnScrollBarExUpdatePos );
	theUiManager.OnScrollBarExUpdatePos( ID_FRAME_GameSettingFunction, ID_SCROLLBAREX_Fov, s_CUI_ID_FRAME_GameSettingFunctionID_SCROLLBAREX_FovOnScrollBarExUpdatePos );
	theUiManager.OnScrollBarExUpdatePos( ID_FRAME_GameSettingFunction, ID_SCROLLBAREX_CameraMaxDistance, s_CUI_ID_FRAME_GameSettingFunctionID_SCROLLBAREX_CameraMaxDistanceOnScrollBarExUpdatePos );
	theUiManager.OnCheckBoxCheck( ID_FRAME_GameSettingFunction, ID_CHECKBOX_VerticleView, s_CUI_ID_FRAME_GameSettingFunctionID_CHECKBOX_VerticleViewOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_GameSettingFunction, ID_CHECKBOX_ShowHelmet, s_CUI_ID_FRAME_GameSettingFunctionID_CHECKBOX_ShowHelmetOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_GameSettingFunction, ID_CHECKBOX_Suo45, s_CUI_ID_FRAME_GameSettingFunctionID_CHECKBOX_Suo45OnCheckBoxCheck );
    theUiManager.OnCheckBoxCheck( ID_FRAME_GameSettingFunction, ID_CHECKBOX_Help, s_CUI_ID_FRAME_GameSettingFunctionID_CHECKBOX_HelpOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_GameSettingFunction, ID_CHECKBOX_LockMain, s_CUI_ID_FRAME_GameSettingFunctionID_CHECKBOX_LockMainOnCheckBoxCheck );

	m_pID_FRAME_GameSettingFunction = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_GameSettingFunction );
	m_pID_TEXT_ScreenPlayerNumber = (ControlText*)theUiManager.FindControl( ID_FRAME_GameSettingFunction, ID_TEXT_ScreenPlayerNumber );
	m_pID_TEXT_Fov = (ControlText*)theUiManager.FindControl( ID_FRAME_GameSettingFunction, ID_TEXT_Fov );
	m_pID_TEXT_CameraMaxDistance = (ControlText*)theUiManager.FindControl( ID_FRAME_GameSettingFunction, ID_TEXT_CameraMaxDistance );
	m_pID_TEXT_Weisui = (ControlText*)theUiManager.FindControl( ID_FRAME_GameSettingFunction, ID_TEXT_Weisui );
	m_pID_CHECKBOX_Weisui = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSettingFunction, ID_CHECKBOX_Weisui );
	m_pID_SCROLLBAREX_ScreenPlayerNumber = (ControlScrollBarEx*)theUiManager.FindControl( ID_FRAME_GameSettingFunction, ID_SCROLLBAREX_ScreenPlayerNumber );
	m_pID_SCROLLBAREX_Fov = (ControlScrollBarEx*)theUiManager.FindControl( ID_FRAME_GameSettingFunction, ID_SCROLLBAREX_Fov );
	m_pID_SCROLLBAREX_CameraMaxDistance = (ControlScrollBarEx*)theUiManager.FindControl( ID_FRAME_GameSettingFunction, ID_SCROLLBAREX_CameraMaxDistance );
	m_pID_TEXT_VerticleView = (ControlText*)theUiManager.FindControl( ID_FRAME_GameSettingFunction, ID_TEXT_VerticleView );
	m_pID_TEXT_ShowHelmet = (ControlText*)theUiManager.FindControl( ID_FRAME_GameSettingFunction, ID_TEXT_ShowHelmet );
	m_pID_TEXT_Suo45 = (ControlText*)theUiManager.FindControl( ID_FRAME_GameSettingFunction, ID_TEXT_Suo45 );
	m_pID_CHECKBOX_VerticleView = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSettingFunction, ID_CHECKBOX_VerticleView );
	m_pID_CHECKBOX_ShowHelmet = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSettingFunction, ID_CHECKBOX_ShowHelmet );
	m_pID_CHECKBOX_Suo45 = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSettingFunction, ID_CHECKBOX_Suo45 );
	m_pID_TEXT_Help = (ControlText*)theUiManager.FindControl( ID_FRAME_GameSettingFunction, ID_TEXT_Help );
	m_pID_CHECKBOX_Help = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSettingFunction, ID_CHECKBOX_Help );
	m_pID_TEXT_LockMain = (ControlText*)theUiManager.FindControl( ID_FRAME_GameSettingFunction, ID_TEXT_LockMain );
	m_pID_CHECKBOX_LockMain = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSettingFunction, ID_CHECKBOX_LockMain );
	assert( m_pID_FRAME_GameSettingFunction );
	assert( m_pID_TEXT_ScreenPlayerNumber );
	assert( m_pID_TEXT_Fov );
	assert( m_pID_TEXT_CameraMaxDistance );
	assert( m_pID_TEXT_Weisui );
	assert( m_pID_CHECKBOX_Weisui );
	assert( m_pID_SCROLLBAREX_ScreenPlayerNumber );
	assert( m_pID_SCROLLBAREX_Fov );
	assert( m_pID_SCROLLBAREX_CameraMaxDistance );
	assert( m_pID_TEXT_VerticleView );
	assert( m_pID_TEXT_ShowHelmet );
	assert( m_pID_TEXT_Suo45 );
	assert( m_pID_CHECKBOX_VerticleView );
	assert( m_pID_CHECKBOX_ShowHelmet );
	assert( m_pID_CHECKBOX_Suo45 );
	assert( m_pID_TEXT_Help );
	assert( m_pID_CHECKBOX_Help );
	assert( m_pID_TEXT_LockMain );
	assert( m_pID_CHECKBOX_LockMain );
	m_pID_FRAME_GameSettingFunction->SetMsgHoldup(false);	
	m_pID_SCROLLBAREX_ScreenPlayerNumber->SetDrawValueText( true );
	m_pID_SCROLLBAREX_ScreenPlayerNumber->SetDrawInCustom( true );
	GetFrame()->SetFather(s_CUI_ID_FRAME_GameSettingUIBase.GetFrame());
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_GameSettingFunction::_UnLoadUI()
{
	m_pID_FRAME_GameSettingFunction = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\GameSettingFunction.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_GameSettingFunction::_IsVisable()
{
	if( !m_pID_FRAME_GameSettingFunction )
		return false;
	return m_pID_FRAME_GameSettingFunction->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_GameSettingFunction::_SetVisable( const bool bVisable )
{
	if( !m_pID_FRAME_GameSettingFunction )
		return;
	m_pID_FRAME_GameSettingFunction->SetVisable( bVisable );
	if (bVisable)
	{
		RefreshUI();
	}
}
void CUI_ID_FRAME_GameSettingFunction::RefreshUI()
{
    if(!m_pID_FRAME_GameSettingFunction)
        return;

	for( int i = 0 ; i < GameSetting::eGSC_TOTAL ; ++ i )
	{
		int nValue = (int)GameSetting::Instance()->GetLevel( (GameSetting::eGameSettingCategory)i );
		switch( i )
		{	
	
		case GameSetting::eGSC_SHOWHELMET:
			m_pID_CHECKBOX_ShowHelmet->SetCheck( nValue );
			break;
		case GameSetting::eGSC_VERTICLEVIEW:
			m_pID_CHECKBOX_VerticleView->SetCheck( nValue );
			break;
		
		case GameSetting::eGSC_SHOWPLAYERNUMBER:
			m_pID_SCROLLBAREX_ScreenPlayerNumber->SetValue( nValue );
			break;
		case GameSetting::eGSC_FOV:
			m_pID_SCROLLBAREX_Fov->SetValue( nValue );
			break;
		case GameSetting::eGSC_MAXCAMERADISTANCE:
			m_pID_SCROLLBAREX_CameraMaxDistance->SetValue( nValue );
			break;		
		case GameSetting::eGSC_45CAMERA:
			m_pID_CHECKBOX_Suo45->SetCheck( nValue );
			break;
		case GameSetting::eGSC_FOLLOWCAMERA:
			m_pID_CHECKBOX_Weisui->SetCheck( nValue );
			break;
		case GameSetting::eGSC_IntroductionEnable:
			m_pID_CHECKBOX_Help->SetCheck( nValue );
			break;
		case GameSetting::eSSC_SKILLLOCK2:
			m_pID_CHECKBOX_LockMain->SetCheck( !nValue );
			break;
		default:
			break;
		}
	}
}

void CUI_ID_FRAME_GameSettingFunction::ID_CHECKBOX_HelpOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	GameSetting::Instance()->SetLevel( GameSetting::eGSC_IntroductionEnable, (unsigned int)*pbChecked );
	GameSetting::Instance()->CommitChanges();

	s_CUI_ID_FRAME_POPINTRO.CheckBoxClose_SetCheck(!(*pbChecked));
}