/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\zhuomeng.hu\桌面\GuideTip.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "GuideTip.h"
#include "meui/ExpressionManager.h"
#include "GameSetting.h"
#include "MessageBox.h"
#include "XmlStringLanguage.h"
#include "color_config.h"
#include "SettingGame.h"

CUI_ID_FRAME_GuideTip s_CUI_ID_FRAME_GuideTip;
MAP_FRAME_RUN( s_CUI_ID_FRAME_GuideTip, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_GuideTip, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_GuideTip, ID_BUTTON_CLOSEOnButtonClick )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GuideTip, ID_CHECKBOX_ShowAgainOnCheckBoxCheck )

CUI_ID_FRAME_GuideTip::CUI_ID_FRAME_GuideTip()
{
	ResetMembers();
}

void CUI_ID_FRAME_GuideTip::ResetMembers()
{
    m_pID_FRAME_GuideTip = NULL;
    m_pID_TEXT_Info = NULL;
    m_pID_BUTTON_CLOSE = NULL;
    m_pID_CHECKBOX_ShowAgain = NULL;
}

bool CUI_ID_FRAME_GuideTip::OnFrameRun()
{
	return true;
}

bool CUI_ID_FRAME_GuideTip::OnFrameRender()
{
	return true;
}

bool CUI_ID_FRAME_GuideTip::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_GuideTip )
		return false;
	return true;
}

void CUI_ID_FRAME_GuideTip::ID_CHECKBOX_ShowAgainOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if ( !m_pID_FRAME_GuideTip )
		return;

    bool bEnable = !( *pbChecked );
    GameSetting::Instance()->SetLevel( GameSetting::eGSC_IntroductionEnable, bEnable );
    GameSetting::Instance()->CommitChanges();

    s_CUI_ID_FRAME_GameSet.RefreshUI();

    if( !bEnable )
    {
        s_CUI_ID_FRAME_MessageBox.Show( theXmlString.GetString( eText_ReStartIntroduction ), "", CUI_ID_FRAME_MessageBox::eTypeConfirm, false );
    }
}

// 装载UI
bool CUI_ID_FRAME_GuideTip::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\GuideTip.MEUI", false, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\GuideTip.MEUI]失败")
		return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_GuideTip::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_GuideTip, s_CUI_ID_FRAME_GuideTipOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_GuideTip, s_CUI_ID_FRAME_GuideTipOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_GuideTip, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_GuideTipID_BUTTON_CLOSEOnButtonClick );
	theUiManager.OnCheckBoxCheck( ID_FRAME_GuideTip, ID_CHECKBOX_ShowAgain, s_CUI_ID_FRAME_GuideTipID_CHECKBOX_ShowAgainOnCheckBoxCheck );

	m_pID_FRAME_GuideTip = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_GuideTip );
	m_pID_TEXT_Info = (ControlText*)theUiManager.FindControl( ID_FRAME_GuideTip, ID_TEXT_Info );
	m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_FRAME_GuideTip, ID_BUTTON_CLOSE );
	m_pID_CHECKBOX_ShowAgain = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GuideTip, ID_CHECKBOX_ShowAgain );

	assert( m_pID_FRAME_GuideTip );
	assert( m_pID_TEXT_Info );
	assert( m_pID_BUTTON_CLOSE );
	assert( m_pID_CHECKBOX_ShowAgain );

    m_pID_TEXT_Info->SetColUrl( Color_Config.getColor( ( ColorConfigure )CC_PathFindLinker ) );
	m_pID_FRAME_GuideTip->SetMsgHoldup(false);//LYH++ 新手帮助不接受鼠标消息

	_SetVisable( false );
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_GuideTip::_UnLoadUI()
{
    ResetMembers();
    return theUiManager.RemoveFrame( "Data\\UI\\GuideTip.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_GuideTip::_IsVisable()
{
	if ( !m_pID_FRAME_GuideTip )
		return false;
	return m_pID_FRAME_GuideTip->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_GuideTip::_SetVisable( const bool bVisable )
{
	if ( !m_pID_FRAME_GuideTip )
		return;
	m_pID_FRAME_GuideTip->SetVisable( bVisable );
}

void CUI_ID_FRAME_GuideTip::ShowPopInfo( int iStringId )
{
    if( !GameSetting::Instance()->GetLevel( GameSetting::eGSC_IntroductionEnable ) )
        return;

    SetVisable( true );

    m_pID_CHECKBOX_ShowAgain->SetCheck( false );
    std::string strTemp = theXmlString.GetString( iStringId );
    ExpressionManager::GetInstance().AddExpressionAni( strTemp );
    m_pID_TEXT_Info->SetText( strTemp );
}
