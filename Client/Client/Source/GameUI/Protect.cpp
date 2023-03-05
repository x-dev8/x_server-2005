/********************************************************************
	Created by UIEditor.exe
	FileName: E:\Document\保护设置\Protect.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "Protect.h"
#include "UIMgr.h"
#include "Cfg.h"
#include "PlayerRole.h"
#include "ScreenInfoManager.h"
#include "color_config.h"
#include "XmlStringLanguage.h"
#include "MessageDefine.h"
#include "NetworkInput.h"
#include "WealthProtect.h"

CUI_ID_FRAME_Protect s_CUI_ID_FRAME_Protect;
MAP_FRAME_RUN( s_CUI_ID_FRAME_Protect, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_Protect, OnFrameRender )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_Protect, ID_CHECKBOX_ProtectSetOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_Protect, ID_CHECKBOX_PkSetOnCheckBoxCheck )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Protect, ID_BUTTON_OkOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Protect, ID_BUTTON_CancelOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Protect, ID_BUTTON_CloseOnButtonClick )
//MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Protect, ID_BUTTON_HelpOnButtonClick )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_Protect, ID_LIST_ProtectInfoOnListSelectChange )
MAP_EDIT_ENTER_CALLBACK( s_CUI_ID_FRAME_Protect, ID_EDIT_TimeOnEditEnter )
CUI_ID_FRAME_Protect::CUI_ID_FRAME_Protect()
{
	// Member
	ResetMembers();
}
void CUI_ID_FRAME_Protect::ResetMembers()
{
	m_pID_FRAME_Protect = NULL;
	m_pID_CHECKBOX_ProtectSet = NULL;
	m_pID_CHECKBOX_PkSet = NULL;
	m_pID_PICTURE_Wall = NULL;
	m_pID_BUTTON_Ok = NULL;
	m_pID_BUTTON_Cancel = NULL;
	m_pID_TEXT_All = NULL;

//	m_pID_BUTTON_Close = NULL;
	m_pID_PICTURE_18290 = NULL;
	m_pID_LIST_ProtectInfo = NULL;
	m_pID_PICTURE_Wall3 = NULL;
	m_pID_EDIT_Time = NULL;
	m_pID_TEXT_Min = NULL;
	m_pID_TEXT_TimeWord = NULL;
	m_pID_TEXT_Time = NULL;
	m_shProtectTime = 1;
}
// Frame
bool CUI_ID_FRAME_Protect::OnFrameRun()
{
	UpdateProtectTimeCountDown();
	return true;
}
bool CUI_ID_FRAME_Protect::OnFrameRender()
{
	UpdateProtectTimeCountDown();
	return true;
}
// CheckBox
void CUI_ID_FRAME_Protect::ID_CHECKBOX_ProtectSetOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if( !m_pID_FRAME_Protect )
		return;
	ToggleProtectSet();
}
// CheckBox
void CUI_ID_FRAME_Protect::ID_CHECKBOX_PkSetOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if( !m_pID_FRAME_Protect )
		return;
	if( thePlayerRole.GetLevel() < gCfg.m_ucPKLevelLimit )
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Wealth_Protect, theXmlString.GetString(eText_NotChangePKMode) );
		m_SettingTypeRadioGroup.ToggleRadio(m_pID_CHECKBOX_ProtectSet);
	}
	else
		TogglePkSet();
}
// Button
bool CUI_ID_FRAME_Protect::ID_BUTTON_OkOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_Protect )
		return false;
	char szTime[MAX_PATH] = {0};
	int nTime = 0;
	strncpy(szTime, m_pID_EDIT_Time->GetText(), sizeof(szTime)-1);
	nTime = atoi(szTime);
	if( nTime != m_shProtectTime )
	{
		DWORD dwEndTime = CWealthProtect::Instance().GetProtectEndingTime();
		if( dwEndTime > HQ_TimeGetTime() )
		{
			// 安全保护时间内无法修改安全保护时间
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Wealth_Protect, theXmlString.GetString(eText_OperateFailInProtectTime) );
		}
		else if( nTime < gCfg.m_shProtectTimeAtLeast )
		{
			char text[MAX_PATH] = {0};
			sprintf(text, theXmlString.GetString(eText_ProtectTimeAtLeast), gCfg.m_shProtectTimeAtLeast);
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Wealth_Protect, text );
		}
		else
		{
			// 发送服务器
			MsgChangeProtectLockTimeReq kMsg;
			kMsg.chTime = nTime;
			GettheNetworkInput().SendMsg(&kMsg);

			m_shChangeTime = nTime;
		}
	}

	SetVisable(false);

	return true;
}
// Button
bool CUI_ID_FRAME_Protect::ID_BUTTON_CancelOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_Protect )
	{
		return false;
	}
	
	SetVisable(false);

	return true;
}
// Button
bool CUI_ID_FRAME_Protect::ID_BUTTON_CloseOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_Protect )
	{
		return false;
	}

	SetVisable(false);
	return true;
}

// List
void CUI_ID_FRAME_Protect::ID_LIST_ProtectInfoOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
	if( !m_pID_FRAME_Protect )
		return;
}
// Edit
void CUI_ID_FRAME_Protect::ID_EDIT_TimeOnEditEnter( ControlObject* pSender, const char* szData )
{
	if( !m_pID_FRAME_Protect )
		return;
}

// 装载UI
bool CUI_ID_FRAME_Protect::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\Protect.MEUI", false, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\Protect.MEUI]失败")
			return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_Protect::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_Protect, s_CUI_ID_FRAME_ProtectOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_Protect, s_CUI_ID_FRAME_ProtectOnFrameRender );
	theUiManager.OnCheckBoxCheck( ID_FRAME_Protect, ID_CHECKBOX_ProtectSet, s_CUI_ID_FRAME_ProtectID_CHECKBOX_ProtectSetOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_Protect, ID_CHECKBOX_PkSet, s_CUI_ID_FRAME_ProtectID_CHECKBOX_PkSetOnCheckBoxCheck );
	theUiManager.OnButtonClick( ID_FRAME_Protect, ID_BUTTON_Ok, s_CUI_ID_FRAME_ProtectID_BUTTON_OkOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Protect, ID_BUTTON_Cancel, s_CUI_ID_FRAME_ProtectID_BUTTON_CancelOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Protect, ID_BUTTON_Close, s_CUI_ID_FRAME_ProtectID_BUTTON_CloseOnButtonClick );

	theUiManager.OnListSelectChange( ID_FRAME_Protect, ID_LIST_ProtectInfo, s_CUI_ID_FRAME_ProtectID_LIST_ProtectInfoOnListSelectChange );
	theUiManager.OnEditEnter( ID_FRAME_Protect, ID_EDIT_Time, s_CUI_ID_FRAME_ProtectID_EDIT_TimeOnEditEnter );

	m_pID_FRAME_Protect = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_Protect );
	m_pID_CHECKBOX_ProtectSet = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_Protect, ID_CHECKBOX_ProtectSet );
	m_pID_CHECKBOX_PkSet = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_Protect, ID_CHECKBOX_PkSet );
	m_pID_PICTURE_Wall = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Protect, ID_PICTURE_Wall );
	m_pID_BUTTON_Ok = (ControlButton*)theUiManager.FindControl( ID_FRAME_Protect, ID_BUTTON_Ok );
	m_pID_BUTTON_Cancel = (ControlButton*)theUiManager.FindControl( ID_FRAME_Protect, ID_BUTTON_Cancel );
	m_pID_TEXT_All = (ControlText*)theUiManager.FindControl( ID_FRAME_Protect, ID_TEXT_All );
	m_pID_PICTURE_18290 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Protect, ID_PICTURE_18290 );
	m_pID_LIST_ProtectInfo = (ControlList*)theUiManager.FindControl( ID_FRAME_Protect, ID_LIST_ProtectInfo );
	m_pID_PICTURE_Wall3 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Protect, ID_PICTURE_Wall3 );
	m_pID_EDIT_Time = (ControlEdit*)theUiManager.FindControl( ID_FRAME_Protect, ID_EDIT_Time );
	m_pID_TEXT_Min = (ControlText*)theUiManager.FindControl( ID_FRAME_Protect, ID_TEXT_Min );
	m_pID_TEXT_TimeWord = (ControlText*)theUiManager.FindControl( ID_FRAME_Protect, ID_TEXT_TimeWord );
	m_pID_TEXT_Time = (ControlText*)theUiManager.FindControl( ID_FRAME_Protect, ID_TEXT_Time );
	assert( m_pID_FRAME_Protect );
	assert( m_pID_CHECKBOX_ProtectSet );
	assert( m_pID_CHECKBOX_PkSet );
	assert( m_pID_PICTURE_Wall );
	assert( m_pID_BUTTON_Ok );
	assert( m_pID_BUTTON_Cancel );
	assert( m_pID_TEXT_All );

	assert( m_pID_PICTURE_18290 );
	assert( m_pID_LIST_ProtectInfo );
	assert( m_pID_PICTURE_Wall3 );
	assert( m_pID_EDIT_Time );
	assert( m_pID_TEXT_Min );
	assert( m_pID_TEXT_TimeWord );
	assert( m_pID_TEXT_Time );

	m_SettingTypeRadioGroup.AddRadio(m_pID_CHECKBOX_ProtectSet);
	m_SettingTypeRadioGroup.AddRadio(m_pID_CHECKBOX_PkSet);
	m_SettingTypeRadioGroup.ToggleRadio(m_pID_CHECKBOX_PkSet);

	m_ProtectSetGroup.Clear();
	m_ProtectSetGroup.AddControl(m_pID_LIST_ProtectInfo);
	m_ProtectSetGroup.AddControl(m_pID_TEXT_All);
	m_ProtectSetGroup.AddControl(m_pID_EDIT_Time);
	m_ProtectSetGroup.AddControl(m_pID_TEXT_Min);
	m_ProtectSetGroup.AddControl(m_pID_TEXT_TimeWord);
	m_ProtectSetGroup.AddControl(m_pID_TEXT_Time);
	m_ProtectSetGroup.AddControl(m_pID_PICTURE_18290);
	m_ProtectSetGroup.AddControl(m_pID_PICTURE_Wall3);

	m_ProtectSetGroup.SetVisible( true );

	m_pID_EDIT_Time->SetIsNumber(true);
	m_pID_EDIT_Time->SetMaxLength(2);

	m_shChangeTime = -1;

	InitProtectInfoList();
	SetVisable(false);
	USE_SCRIPT( eUI_OBJECT_Protect, this );

	return true;
}
// 卸载UI
bool CUI_ID_FRAME_Protect::_UnLoadUI()
{
	CLOSE_SCRIPT( eUI_OBJECT_Protect );
	m_SettingTypeRadioGroup.Clear();
	m_ProtectSetGroup.Clear();

	ResetMembers();
	return theUiManager.RemoveFrame( "Data\\UI\\Protect.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_Protect::_IsVisable()
{
	if( !m_pID_FRAME_Protect )
		return false;
	return m_pID_FRAME_Protect->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_Protect::_SetVisable( const bool bVisable )
{
	if( !m_pID_FRAME_Protect )
	{
		return;
	}

	m_pID_FRAME_Protect->SetVisable( bVisable );

	if( bVisable )
	{
		m_shProtectTime = CWealthProtect::Instance().GetProtectTime();
		m_pID_EDIT_Time->SetText((int)m_shProtectTime);
	}
}

void CUI_ID_FRAME_Protect::ToggleProtectSet()
{
	m_ProtectSetGroup.SetVisible(true);
	DWORD dwEndTime = CWealthProtect::Instance().GetProtectEndingTime();
	if( dwEndTime < HQ_TimeGetTime() )
		m_pID_TEXT_TimeWord->SetVisable(false);
	m_SettingTypeRadioGroup.ToggleRadio(m_pID_CHECKBOX_ProtectSet);
}

void CUI_ID_FRAME_Protect::TogglePkSet()
{
	m_ProtectSetGroup.SetVisible(false);
	m_SettingTypeRadioGroup.ToggleRadio(m_pID_CHECKBOX_PkSet);
}

void CUI_ID_FRAME_Protect::InitProtectInfoList()
{
	m_pID_LIST_ProtectInfo->HaveSelBar( false );	//没有绿色cur选中地图

	ControlList::S_List	stItem;
	m_pID_LIST_ProtectInfo->Clear();
	for(int i=0; i<gCfg.m_vctStrProtectSetting.size(); i++)
	{
		stItem.SetData(gCfg.m_vctStrProtectSetting[i].c_str());
		m_pID_LIST_ProtectInfo->AddItem(&stItem);
	}
	m_pID_LIST_ProtectInfo->SetShowStartHeight(0);
	m_pID_LIST_ProtectInfo->SetScrollValue(0);
}

void CUI_ID_FRAME_Protect::UpdateProtectTimeCountDown()
{
	if( !s_CUI_ID_FRAME_Protect.IsVisable() )
		return;

	DWORD dwEndTime = CWealthProtect::Instance().GetProtectEndingTime();
	if( dwEndTime > HQ_TimeGetTime() )
	{
		m_pID_TEXT_TimeWord->SetVisable(true);
		DWORD dwRemainTime = dwEndTime - HQ_TimeGetTime();
		int iRemainSecond = (int)ceil(dwRemainTime*1.f / 1000);
		if( iRemainSecond > 0 )
		{
			int iRemainMinute = iRemainSecond / 60;
			iRemainSecond -= iRemainMinute * 60;
			char szText[MAX_PATH] = {0};
			sprintf( szText, "%02d:%02d", iRemainMinute, iRemainSecond );
			s_CUI_ID_FRAME_Protect.m_pID_TEXT_Time->SetText(szText);
		}
		else
		{
			// 小于1秒，显示1秒
			s_CUI_ID_FRAME_Protect.m_pID_TEXT_Time->SetText("00:01");
		}
	}
	else
	{
		s_CUI_ID_FRAME_Protect. m_pID_TEXT_Time->SetText("");
	}
}