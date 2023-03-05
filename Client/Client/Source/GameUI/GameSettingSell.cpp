/********************************************************************
Created by UIEditor.exe
FileName: C:\Documents and Settings\huwen\桌面\GameSettingSell.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "GameSettingSell.h"
#include "GameSetting.h"
#include "GameSettingUIBase.h"

CUI_ID_FRAME_GameSettingSell s_CUI_ID_FRAME_GameSettingSell;
MAP_FRAME_RUN( s_CUI_ID_FRAME_GameSettingSell, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_GameSettingSell, OnFrameRender )
//MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSettingSell, ID_CHECKBOX_Quality0OnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSettingSell, ID_CHECKBOX_Quality1OnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSettingSell, ID_CHECKBOX_Quality2OnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSettingSell, ID_CHECKBOX_Quality3OnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSettingSell, ID_CHECKBOX_Quality4OnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSettingSell, ID_CHECKBOX_Quality5OnCheckBoxCheck )
//MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSettingSell, ID_CHECKBOX_QualityAllOnCheckBoxCheck )
CUI_ID_FRAME_GameSettingSell::CUI_ID_FRAME_GameSettingSell()
{
	// Member
	m_pID_FRAME_GameSettingSell = NULL;
	m_pID_PICTURE_Wall1 = NULL;
	m_pID_TEXT_SellInfo = NULL;
	//m_pID_TEXT_Quality0 = NULL;
	m_pID_TEXT_Quality4 = NULL;
	m_pID_TEXT_Quality1 = NULL;
	m_pID_TEXT_Quality3 = NULL;
	m_pID_TEXT_Quality2 = NULL;
	//m_pID_CHECKBOX_Quality0 = NULL;
	m_pID_CHECKBOX_Quality1 = NULL;
	m_pID_CHECKBOX_Quality2 = NULL;
	m_pID_CHECKBOX_Quality3 = NULL;
	m_pID_CHECKBOX_Quality4 = NULL;
	m_pID_TEXT_Quality5 = NULL;
	m_pID_CHECKBOX_Quality5 = NULL;
	//m_pID_CHECKBOX_QualityAll = NULL;

}
// Frame
bool CUI_ID_FRAME_GameSettingSell::OnFrameRun()
{
	return true;
}
bool CUI_ID_FRAME_GameSettingSell::OnFrameRender()
{
	return true;
}
// CheckBox
// void CUI_ID_FRAME_GameSettingSell::ID_CHECKBOX_Quality0OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
// {
// 	GameSetting::Instance()->SetLevel( GameSetting::eGSC_SellPrompt1, (unsigned int)*pbChecked );
// 	GameSetting::Instance()->CommitChanges();
// 
// 	RefreshUI();
// }
// CheckBox
void CUI_ID_FRAME_GameSettingSell::ID_CHECKBOX_Quality1OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	GameSetting::Instance()->SetLevel( GameSetting::eGSC_SellPrompt2, (unsigned int)*pbChecked );
	GameSetting::Instance()->CommitChanges();

	RefreshUI();
}
// CheckBox
void CUI_ID_FRAME_GameSettingSell::ID_CHECKBOX_Quality2OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	GameSetting::Instance()->SetLevel( GameSetting::eGSC_SellPrompt3, (unsigned int)*pbChecked );
	GameSetting::Instance()->CommitChanges();

	RefreshUI();
}
// CheckBox
void CUI_ID_FRAME_GameSettingSell::ID_CHECKBOX_Quality3OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	GameSetting::Instance()->SetLevel( GameSetting::eGSC_SellPrompt4, (unsigned int)*pbChecked );
	GameSetting::Instance()->CommitChanges();

	RefreshUI();
}
// CheckBox
void CUI_ID_FRAME_GameSettingSell::ID_CHECKBOX_Quality4OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	GameSetting::Instance()->SetLevel( GameSetting::eGSC_SellPrompt5, (unsigned int)*pbChecked );
	GameSetting::Instance()->CommitChanges();

	RefreshUI();
}
// CheckBox
void CUI_ID_FRAME_GameSettingSell::ID_CHECKBOX_Quality5OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	GameSetting::Instance()->SetLevel( GameSetting::eGSC_SellPrompt6, (unsigned int)*pbChecked );
	GameSetting::Instance()->CommitChanges();

	RefreshUI();
}
// CheckBox
//void CUI_ID_FRAME_GameSettingSell::ID_CHECKBOX_QualityAllOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
//{
//	bool bValue = *pbChecked;
//	for( int i = GameSetting::eGSC_SellPrompt1 ; i <= GameSetting::eGSC_SellPrompt6 ; ++ i )
//	{
//		GameSetting::Instance()->SetLevel( (GameSetting::eGameSettingCategory)i, bValue );
//		switch( i )
//		{			
//		case GameSetting::eGSC_SellPrompt1:
//			m_pID_CHECKBOX_Quality0->SetCheck( bValue );
//			break;
//		case GameSetting::eGSC_SellPrompt2:
//			m_pID_CHECKBOX_Quality1->SetCheck( bValue );
//			break;
//		case GameSetting::eGSC_SellPrompt3:	
//			m_pID_CHECKBOX_Quality2->SetCheck( bValue );
//			break;
//		case GameSetting::eGSC_SellPrompt4:
//			m_pID_CHECKBOX_Quality3->SetCheck( bValue );
//			break;
//		case GameSetting::eGSC_SellPrompt5:	
//			m_pID_CHECKBOX_Quality4->SetCheck( bValue );
//			break;
//		case GameSetting::eGSC_SellPrompt6:	
//			m_pID_CHECKBOX_Quality5->SetCheck( bValue );
//			break;
//		default:
//			break;
//		}
//	}
//	GameSetting::Instance()->CommitChanges();
//}

// 装载UI
bool CUI_ID_FRAME_GameSettingSell::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\GameSettingSell.MEUI" );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\GameSettingSell.MEUI]失败")
			return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_GameSettingSell::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_GameSettingSell, s_CUI_ID_FRAME_GameSettingSellOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_GameSettingSell, s_CUI_ID_FRAME_GameSettingSellOnFrameRender );
	//theUiManager.OnCheckBoxCheck( ID_FRAME_GameSettingSell, ID_CHECKBOX_Quality0, s_CUI_ID_FRAME_GameSettingSellID_CHECKBOX_Quality0OnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_GameSettingSell, ID_CHECKBOX_Quality1, s_CUI_ID_FRAME_GameSettingSellID_CHECKBOX_Quality1OnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_GameSettingSell, ID_CHECKBOX_Quality2, s_CUI_ID_FRAME_GameSettingSellID_CHECKBOX_Quality2OnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_GameSettingSell, ID_CHECKBOX_Quality3, s_CUI_ID_FRAME_GameSettingSellID_CHECKBOX_Quality3OnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_GameSettingSell, ID_CHECKBOX_Quality4, s_CUI_ID_FRAME_GameSettingSellID_CHECKBOX_Quality4OnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_GameSettingSell, ID_CHECKBOX_Quality5, s_CUI_ID_FRAME_GameSettingSellID_CHECKBOX_Quality5OnCheckBoxCheck );
	//theUiManager.OnCheckBoxCheck( ID_FRAME_GameSettingSell, ID_CHECKBOX_QualityAll, s_CUI_ID_FRAME_GameSettingSellID_CHECKBOX_QualityAllOnCheckBoxCheck );

	m_pID_FRAME_GameSettingSell = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_GameSettingSell );
	m_pID_PICTURE_Wall1 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_GameSettingSell, ID_PICTURE_Wall1 );
	m_pID_TEXT_SellInfo = (ControlText*)theUiManager.FindControl( ID_FRAME_GameSettingSell, ID_TEXT_SellInfo );
	//m_pID_TEXT_Quality0 = (ControlText*)theUiManager.FindControl( ID_FRAME_GameSettingSell, ID_TEXT_Quality0 );
	m_pID_TEXT_Quality4 = (ControlText*)theUiManager.FindControl( ID_FRAME_GameSettingSell, ID_TEXT_Quality4 );
	m_pID_TEXT_Quality1 = (ControlText*)theUiManager.FindControl( ID_FRAME_GameSettingSell, ID_TEXT_Quality1 );
	m_pID_TEXT_Quality3 = (ControlText*)theUiManager.FindControl( ID_FRAME_GameSettingSell, ID_TEXT_Quality3 );
	m_pID_TEXT_Quality2 = (ControlText*)theUiManager.FindControl( ID_FRAME_GameSettingSell, ID_TEXT_Quality2 );
	//m_pID_CHECKBOX_Quality0 = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSettingSell, ID_CHECKBOX_Quality0 );
	m_pID_CHECKBOX_Quality1 = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSettingSell, ID_CHECKBOX_Quality1 );
	m_pID_CHECKBOX_Quality2 = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSettingSell, ID_CHECKBOX_Quality2 );
	m_pID_CHECKBOX_Quality3 = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSettingSell, ID_CHECKBOX_Quality3 );
	m_pID_CHECKBOX_Quality4 = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSettingSell, ID_CHECKBOX_Quality4 );
	m_pID_TEXT_Quality5 = (ControlText*)theUiManager.FindControl( ID_FRAME_GameSettingSell, ID_TEXT_Quality5 );
	m_pID_CHECKBOX_Quality5 = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSettingSell, ID_CHECKBOX_Quality5 );
	//m_pID_CHECKBOX_QualityAll = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSettingSell, ID_CHECKBOX_QualityAll );
	assert( m_pID_FRAME_GameSettingSell );
	assert( m_pID_PICTURE_Wall1 );
	assert( m_pID_TEXT_SellInfo );
//	assert( m_pID_TEXT_Quality0 );
	assert( m_pID_TEXT_Quality4 );
	assert( m_pID_TEXT_Quality1 );
	assert( m_pID_TEXT_Quality3 );
	assert( m_pID_TEXT_Quality2 );
	//assert( m_pID_CHECKBOX_Quality0 );
	assert( m_pID_CHECKBOX_Quality1 );
	assert( m_pID_CHECKBOX_Quality2 );
	assert( m_pID_CHECKBOX_Quality3 );
	assert( m_pID_CHECKBOX_Quality4 );
	assert( m_pID_TEXT_Quality5 );
	assert( m_pID_CHECKBOX_Quality5 );

	m_pID_FRAME_GameSettingSell->SetMsgHoldup(false);
	GetFrame()->SetFather(s_CUI_ID_FRAME_GameSettingUIBase.GetFrame());
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_GameSettingSell::_UnLoadUI()
{
	m_pID_FRAME_GameSettingSell = NULL;
	m_pID_PICTURE_Wall1 = NULL;
	m_pID_TEXT_SellInfo = NULL;
	//m_pID_TEXT_Quality0 = NULL;
	m_pID_TEXT_Quality4 = NULL;
	m_pID_TEXT_Quality1 = NULL;
	m_pID_TEXT_Quality3 = NULL;
	m_pID_TEXT_Quality2 = NULL;
	//m_pID_CHECKBOX_Quality0 = NULL;
	m_pID_CHECKBOX_Quality1 = NULL;
	m_pID_CHECKBOX_Quality2 = NULL;
	m_pID_CHECKBOX_Quality3 = NULL;
	m_pID_CHECKBOX_Quality4 = NULL;
	m_pID_TEXT_Quality5 = NULL;
	m_pID_CHECKBOX_Quality5 = NULL;
	//m_pID_CHECKBOX_QualityAll = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\GameSettingSell.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_GameSettingSell::_IsVisable()
{
	if( !m_pID_FRAME_GameSettingSell ) 
		return false;
	return m_pID_FRAME_GameSettingSell->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_GameSettingSell::_SetVisable( const bool bVisable )
{
	if( !m_pID_FRAME_GameSettingSell )
		return;
	m_pID_FRAME_GameSettingSell->SetVisable( bVisable );
	if (bVisable)
	{
		RefreshUI();
	}
}

void CUI_ID_FRAME_GameSettingSell::RefreshUI()
{
    if(!m_pID_FRAME_GameSettingSell)
        return;

	bool bAllCheck = true;
	for( int i = GameSetting::eGSC_SellPrompt1 ; i <= GameSetting::eGSC_SellPrompt6 ; ++ i )
	{
		bool bValue = ( bool )GameSetting::Instance()->GetLevel( (GameSetting::eGameSettingCategory)i );
		if (!bValue)
			bAllCheck = false;

		switch( i )
		{			
		case GameSetting::eGSC_SellPrompt1:
			//m_pID_CHECKBOX_Quality0->SetCheck( bValue );
			break;
		case GameSetting::eGSC_SellPrompt2:
			m_pID_CHECKBOX_Quality1->SetCheck( bValue );
			break;
		case GameSetting::eGSC_SellPrompt3:	
			m_pID_CHECKBOX_Quality2->SetCheck( bValue );
			break;
		case GameSetting::eGSC_SellPrompt4:
			m_pID_CHECKBOX_Quality3->SetCheck( bValue );
			break;
		case GameSetting::eGSC_SellPrompt5:	
			m_pID_CHECKBOX_Quality4->SetCheck( bValue );
			break;
		case GameSetting::eGSC_SellPrompt6:	
			m_pID_CHECKBOX_Quality5->SetCheck( bValue );
			break;
		default:
			break;
		}
	}

	//m_pID_CHECKBOX_QualityAll->SetCheck(bAllCheck); 
}