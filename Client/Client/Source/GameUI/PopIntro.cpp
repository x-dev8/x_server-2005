/********************************************************************
Created by UIEditor.exe
FileName: E:\work\Hero\Program\trunk\Client\Bin\Data\Ui\PopIntro.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "PopIntro.h"
#include "ui/UIMgr.h"
#include "NpcCoord.h"
#include "GameSetting.h"
#include "MessageBox.h"
#include "XmlStringLanguage.h"
#include "color_config.h"
#include "SettingGame.h"

CUI_ID_FRAME_POPINTRO s_CUI_ID_FRAME_POPINTRO;
MAP_FRAME_RUN( s_CUI_ID_FRAME_POPINTRO, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_POPINTRO, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_POPINTRO, ID_BUTTON_COMFIRMOnButtonClick )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_POPINTRO, ID_CHECKBOX_CloseOnCheckBoxCheck )

CUI_ID_FRAME_POPINTRO::CUI_ID_FRAME_POPINTRO()
{
	// Member
	m_pID_FRAME_POPINTRO = NULL;
// 	m_pID_PICTURE_Info = NULL;
	m_pID_BUTTON_COMFIRM = NULL;
	m_pID_TEXT_Info = NULL;
	m_pID_TEXT_Title = NULL;
	m_pID_CHECKBOX_Close = NULL;
// 	m_pID_TEXT_Close = NULL;

}
// Frame
bool CUI_ID_FRAME_POPINTRO::OnFrameRun()
{
	return true;
}
bool CUI_ID_FRAME_POPINTRO::OnFrameRender()
{
	return true;
}
// Button
bool CUI_ID_FRAME_POPINTRO::ID_BUTTON_COMFIRMOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_POPINTRO )
		return false;
	_SetVisable(false,NULL,NULL);
	return true;
}
// CheckBox
void CUI_ID_FRAME_POPINTRO::ID_CHECKBOX_CloseOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if( !m_pID_FRAME_POPINTRO )
		return;
	bool bEnable = !(*pbChecked);
	GameSetting::Instance()->SetLevel( GameSetting::eGSC_IntroductionEnable, bEnable );
	GameSetting::Instance()->CommitChanges();

    s_CUI_ID_FRAME_GameSet.RefreshUI();

	if (!bEnable)
	{
		s_CUI_ID_FRAME_MessageBox.Show(theXmlString.GetString(eText_ReStartIntroduction),"",CUI_ID_FRAME_MessageBox::eTypeConfirm,false);
	}
	
}

// 装载UI
bool CUI_ID_FRAME_POPINTRO::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\PopIntro.MEUI", false, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\PopIntro.MEUI]失败")
		return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_POPINTRO::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_POPINTRO, s_CUI_ID_FRAME_POPINTROOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_POPINTRO, s_CUI_ID_FRAME_POPINTROOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_POPINTRO, ID_BUTTON_COMFIRM, s_CUI_ID_FRAME_POPINTROID_BUTTON_COMFIRMOnButtonClick );
	theUiManager.OnCheckBoxCheck( ID_FRAME_POPINTRO, ID_CHECKBOX_Close, s_CUI_ID_FRAME_POPINTROID_CHECKBOX_CloseOnCheckBoxCheck );

	m_pID_FRAME_POPINTRO = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_POPINTRO );
// 	m_pID_PICTURE_Info = (ControlPicture*)theUiManager.FindControl( ID_FRAME_POPINTRO, ID_PICTURE_Info );
	m_pID_BUTTON_COMFIRM = (ControlButton*)theUiManager.FindControl( ID_FRAME_POPINTRO, ID_BUTTON_COMFIRM );
	m_pID_TEXT_Info = (ControlText*)theUiManager.FindControl( ID_FRAME_POPINTRO, ID_TEXT_Info );
	m_pID_TEXT_Title = (ControlText*)theUiManager.FindControl( ID_FRAME_POPINTRO, ID_TEXT_Title );
	m_pID_CHECKBOX_Close = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_POPINTRO, ID_CHECKBOX_Close );
// 	m_pID_TEXT_Close = (ControlText*)theUiManager.FindControl( ID_FRAME_POPINTRO, ID_TEXT_Close );
	assert( m_pID_FRAME_POPINTRO );
// 	assert( m_pID_PICTURE_Info );
	assert( m_pID_BUTTON_COMFIRM );
	assert( m_pID_TEXT_Info );
	assert( m_pID_TEXT_Title );
	assert( m_pID_CHECKBOX_Close );
// 	assert( m_pID_TEXT_Close );

// 	m_pID_TEXT_Info->SetHyberClickFun(HyberClickIntro);
	m_pID_TEXT_Info->SetColUrl(Color_Config.getColor((ColorConfigure)(CC_PathFindLinker)));

	_SetVisable(false,NULL,NULL);

	return true;
}
// 卸载UI
bool CUI_ID_FRAME_POPINTRO::_UnLoadUI()
{
	m_pID_FRAME_POPINTRO = NULL;
// 	m_pID_PICTURE_Info = NULL;
	m_pID_BUTTON_COMFIRM = NULL;
	m_pID_TEXT_Info = NULL;
	m_pID_TEXT_Title = NULL;
	m_pID_CHECKBOX_Close = NULL;
// 	m_pID_TEXT_Close = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\PopIntro.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_POPINTRO::_IsVisable()
{
	if( !m_pID_FRAME_POPINTRO )
		return false;
	return m_pID_FRAME_POPINTRO->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_POPINTRO::_SetVisable( const bool bVisable ,const char* pTitle,const char* pString)
{
	if( !m_pID_FRAME_POPINTRO )
		return;
	if (bVisable)
	{
		m_pID_FRAME_POPINTRO->SetVisable( true );
		if (pTitle)
		{
			m_pID_TEXT_Title->SetText(pTitle);
		}
		if (pString)
		{
			m_pID_TEXT_Info->SetText(pString);
		}
		m_pID_CHECKBOX_Close->SetCheck(false);
	}
	else
	{
		m_pID_FRAME_POPINTRO->SetVisable( false );
	}

}

void CUI_ID_FRAME_POPINTRO::HyberClickIntro( ControlObject* pSender, const char* szName )
{
	if (szName)
	{
		NpcCoord::getInstance()->clickHyberToMiniMap(szName);
	}		
}

void CUI_ID_FRAME_POPINTRO::CheckBoxClose_SetCheck( bool bCheck )
{
	if( !m_pID_FRAME_POPINTRO )
		return;
	m_pID_CHECKBOX_Close->SetCheck(bCheck);
}

void CUI_ID_FRAME_POPINTRO::SetVisable( const bool bVisable ,const char* pTitle,const char* pString )
{
	if (bVisable && (bool)GameSetting::Instance()->GetLevel( GameSetting::eGSC_IntroductionEnable ))
	{
		CUIBase::SetVisable(bVisable);
		if (m_bUILoad)
		{
			_SetVisable(bVisable,pTitle,pString);
		}	

	}
	else
	{
		if( m_pID_FRAME_POPINTRO )
			m_pID_FRAME_POPINTRO->SetVisable( false );
	}

}