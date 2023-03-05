/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\liuchuanpeng\桌面\PopIntro4.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "PopIntro4.h"
#include "XmlStringLanguage.h"
#include "GameSetting.h"
#include "MessageBox.h"
#include "SettingGame.h"

CUI_ID_FRAME_PopIntro4 s_CUI_ID_FRAME_PopIntro4;
MAP_FRAME_RUN( s_CUI_ID_FRAME_PopIntro4, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_PopIntro4, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_PopIntro4, ID_BUTTON_CLOSEOnButtonClick )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_PopIntro4, ID_CHECKBOX_CloseOnCheckBoxCheck )
CUI_ID_FRAME_PopIntro4::CUI_ID_FRAME_PopIntro4()
{
	// Member
	m_pID_FRAME_PopIntro4 = NULL;
	m_pID_TEXT_Info = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_TEXT_Title = NULL;
	m_pID_CHECKBOX_Close = NULL;
	m_pID_TEXT_GuideGif = NULL;
}

// Frame
bool CUI_ID_FRAME_PopIntro4::OnFrameRun()
{
	return true;
}

bool CUI_ID_FRAME_PopIntro4::OnFrameRender()
{
	return true;
}

// Button
bool CUI_ID_FRAME_PopIntro4::ID_BUTTON_CLOSEOnButtonClick( ControlObject* pSender )
{
	return true;
}

// CheckBox
void CUI_ID_FRAME_PopIntro4::ID_CHECKBOX_CloseOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if ( !m_pID_FRAME_PopIntro4 )
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
bool CUI_ID_FRAME_PopIntro4::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\PopIntro4.MEUI" );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\PopIntro4.MEUI]失败")
			return false;
	}
	return DoControlConnect();
}

// 关连控件
bool CUI_ID_FRAME_PopIntro4::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_PopIntro4, s_CUI_ID_FRAME_PopIntro4OnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_PopIntro4, s_CUI_ID_FRAME_PopIntro4OnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_PopIntro4, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_PopIntro4ID_BUTTON_CLOSEOnButtonClick );
	theUiManager.OnCheckBoxCheck( ID_FRAME_PopIntro4, ID_CHECKBOX_Close, s_CUI_ID_FRAME_PopIntro4ID_CHECKBOX_CloseOnCheckBoxCheck );

	m_pID_FRAME_PopIntro4 = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_PopIntro4 );
	m_pID_TEXT_Info = (ControlText*)theUiManager.FindControl( ID_FRAME_PopIntro4, ID_TEXT_Info );
	m_pID_BUTTON_CLOSE = (ControlButton*)theUiManager.FindControl( ID_FRAME_PopIntro4, ID_BUTTON_CLOSE );
	m_pID_TEXT_Title = (ControlText*)theUiManager.FindControl( ID_FRAME_PopIntro4, ID_TEXT_Title );
	m_pID_CHECKBOX_Close = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_PopIntro4, ID_CHECKBOX_Close );
	m_pID_TEXT_GuideGif = (ControlText*)theUiManager.FindControl( ID_FRAME_PopIntro4, ID_TEXT_GuideGif );

	assert( m_pID_FRAME_PopIntro4 );
	assert( m_pID_TEXT_Info );
	assert( m_pID_BUTTON_CLOSE );
	assert( m_pID_TEXT_Title );
	assert( m_pID_CHECKBOX_Close );
	assert( m_pID_TEXT_GuideGif );
	return true;
}

// 卸载UI
bool CUI_ID_FRAME_PopIntro4::_UnLoadUI()
{
	m_pID_FRAME_PopIntro4 = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\PopIntro4.MEUI" );
}

// 是否可视
bool CUI_ID_FRAME_PopIntro4::_IsVisable()
{
	if(!m_pID_FRAME_PopIntro4)
		return false;

	return m_pID_FRAME_PopIntro4->IsVisable();
}

// 设置是否可视
void CUI_ID_FRAME_PopIntro4::_SetVisable( const bool bVisable )
{
	if(!m_pID_FRAME_PopIntro4)
		return;

	m_pID_FRAME_PopIntro4->SetVisable( bVisable );
}

void CUI_ID_FRAME_PopIntro4::ShowInfo(int nTitleId,int nStrindId)
{
	std::string strPic = theXmlString.GetString(nTitleId);
	std::string strInfo = theXmlString.GetString(nStrindId);
	if(strInfo.length() <= 0 || strPic.length() <= 0)
		return;

	m_pID_TEXT_GuideGif->SetText(strPic.c_str());
	m_pID_TEXT_Info->SetText(strInfo.c_str());
}
