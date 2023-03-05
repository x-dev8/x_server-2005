/********************************************************************
Created by UIEditor.exe
FileName: D:\My Documents\桌面\gamesetting\GameSettingSelf.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "GameSettingSelf.h"
#include "GameSetting.h"
#include "GameSettingUIBase.h"

CUI_ID_FRAME_GameSettingSelf s_CUI_ID_FRAME_GameSettingSelf;
MAP_FRAME_RUN( s_CUI_ID_FRAME_GameSettingSelf, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_GameSettingSelf, OnFrameRender )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSettingSelf, ID_CHECKBOX_NameOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSettingSelf, ID_CHECKBOX_TeamHpOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSettingSelf, ID_CHECKBOX_MpOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSettingSelf, ID_CHECKBOX_GuildOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSettingSelf, ID_CHECKBOX_TongOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSettingSelf, ID_CHECKBOX_TitleOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSettingSelf, ID_CHECKBOX_EffectOnCheckBoxCheck )
//MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSettingSelf, ID_CHECKBOX_SelfControlOnCheckBoxCheck )
CUI_ID_FRAME_GameSettingSelf::CUI_ID_FRAME_GameSettingSelf()
{
	// Member
	m_pID_FRAME_GameSettingSelf = NULL;
	m_pID_PICTURE_Wall1 = NULL;
	//m_pID_PICTURE_Wall2 = NULL;
	m_pID_TEXT_TeamInfo = NULL;
	m_pID_TEXT_Name = NULL;
	m_pID_TEXT_Tong = NULL;
	m_pID_TEXT_Hp = NULL;
	m_pID_TEXT_Guild = NULL;
	m_pID_TEXT_Mp = NULL;
	m_pID_TEXT_Title = NULL;
	m_pID_CHECKBOX_Name = NULL;
	m_pID_CHECKBOX_TeamHp = NULL;
	m_pID_CHECKBOX_Mp = NULL;
	m_pID_CHECKBOX_Guild = NULL;
	m_pID_CHECKBOX_Tong = NULL;
	m_pID_CHECKBOX_Title = NULL;
	m_pID_TEXT_Effect = NULL;
	m_pID_CHECKBOX_Effect = NULL;
	//m_pID_CHECKBOX_SelfControl = NULL;

}
// Frame
bool CUI_ID_FRAME_GameSettingSelf::OnFrameRun()
{
	return true;
}
bool CUI_ID_FRAME_GameSettingSelf::OnFrameRender()
{
	return true;
}
// CheckBox
void CUI_ID_FRAME_GameSettingSelf::ID_CHECKBOX_NameOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	GameSetting::Instance()->SetLevel( GameSetting::eGSC_SelfName, (unsigned int)*pbChecked );
    GameSetting::Instance()->SetLevel( GameSetting::eGSC_SelfPetName, (unsigned int)*pbChecked );
	GameSetting::Instance()->CommitChanges();
    if( pSender )
        CheckSelfControl();
}
// CheckBox
void CUI_ID_FRAME_GameSettingSelf::ID_CHECKBOX_TeamHpOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	GameSetting::Instance()->SetLevel( GameSetting::eGSC_SelfHp, (unsigned int)*pbChecked );
    GameSetting::Instance()->SetLevel( GameSetting::eGSC_SelfPetHp, (unsigned int)*pbChecked );
	GameSetting::Instance()->CommitChanges();
    if( pSender )
        CheckSelfControl();
    //if( s_CUI_ID_FRAME_PkSet.IsVisable() )
    //    s_CUI_ID_FRAME_PkSet.RefreshHpMpUI();
}
// CheckBox
void CUI_ID_FRAME_GameSettingSelf::ID_CHECKBOX_MpOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	GameSetting::Instance()->SetLevel( GameSetting::eGSC_SelfMp, (unsigned int)*pbChecked );
	GameSetting::Instance()->CommitChanges();
    if( pSender )
        CheckSelfControl();
    //if( s_CUI_ID_FRAME_PkSet.IsVisable() )
    //    s_CUI_ID_FRAME_PkSet.RefreshHpMpUI();
}
// CheckBox
void CUI_ID_FRAME_GameSettingSelf::ID_CHECKBOX_GuildOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	GameSetting::Instance()->SetLevel( GameSetting::eGSC_SelfGuild, (unsigned int)*pbChecked );
	GameSetting::Instance()->CommitChanges();
    if( pSender )
        CheckSelfControl();
}
// CheckBox
void CUI_ID_FRAME_GameSettingSelf::ID_CHECKBOX_TongOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	GameSetting::Instance()->SetLevel( GameSetting::eGSC_SelfTong, (unsigned int)*pbChecked );
	GameSetting::Instance()->CommitChanges();
    if( pSender )
        CheckSelfControl();
}
// CheckBox
void CUI_ID_FRAME_GameSettingSelf::ID_CHECKBOX_TitleOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	GameSetting::Instance()->SetLevel( GameSetting::eGSC_SelfTitle, (unsigned int)*pbChecked );
    GameSetting::Instance()->SetLevel( GameSetting::eGSC_SelfPetTitle, (unsigned int)*pbChecked );
	GameSetting::Instance()->CommitChanges();
    if( pSender )
        CheckSelfControl();
}
// CheckBox
void CUI_ID_FRAME_GameSettingSelf::ID_CHECKBOX_EffectOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
    GameSetting::Instance()->SetLevel( GameSetting::eGSC_SelfEffect, (unsigned int)*pbChecked );
    GameSetting::Instance()->CommitChanges();
    if( pSender )
        CheckSelfControl();
}
// CheckBox
//void CUI_ID_FRAME_GameSettingSelf::ID_CHECKBOX_SelfControlOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
//{
//    ID_CHECKBOX_NameOnCheckBoxCheck(NULL, pbChecked);
//    ID_CHECKBOX_TeamHpOnCheckBoxCheck(NULL, pbChecked);
//    ID_CHECKBOX_MpOnCheckBoxCheck(NULL, pbChecked);
//    ID_CHECKBOX_GuildOnCheckBoxCheck(NULL, pbChecked);
//    ID_CHECKBOX_TongOnCheckBoxCheck(NULL, pbChecked);
//    ID_CHECKBOX_TitleOnCheckBoxCheck(NULL, pbChecked);
//    m_pID_CHECKBOX_Name->SetCheck( *pbChecked );
//    m_pID_CHECKBOX_TeamHp->SetCheck( *pbChecked );
//    m_pID_CHECKBOX_Mp->SetCheck( *pbChecked );
//    m_pID_CHECKBOX_Guild->SetCheck( *pbChecked );
//    m_pID_CHECKBOX_Tong->SetCheck( *pbChecked );
//    m_pID_CHECKBOX_Title->SetCheck( *pbChecked );
//}
// 装载UI
bool CUI_ID_FRAME_GameSettingSelf::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\GameSettingSelf.MEUI" );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\GameSettingSelf.MEUI]失败")
			return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_GameSettingSelf::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_GameSettingSelf, s_CUI_ID_FRAME_GameSettingSelfOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_GameSettingSelf, s_CUI_ID_FRAME_GameSettingSelfOnFrameRender );
	theUiManager.OnCheckBoxCheck( ID_FRAME_GameSettingSelf, ID_CHECKBOX_Name, s_CUI_ID_FRAME_GameSettingSelfID_CHECKBOX_NameOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_GameSettingSelf, ID_CHECKBOX_TeamHp, s_CUI_ID_FRAME_GameSettingSelfID_CHECKBOX_TeamHpOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_GameSettingSelf, ID_CHECKBOX_Mp, s_CUI_ID_FRAME_GameSettingSelfID_CHECKBOX_MpOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_GameSettingSelf, ID_CHECKBOX_Guild, s_CUI_ID_FRAME_GameSettingSelfID_CHECKBOX_GuildOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_GameSettingSelf, ID_CHECKBOX_Tong, s_CUI_ID_FRAME_GameSettingSelfID_CHECKBOX_TongOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_GameSettingSelf, ID_CHECKBOX_Title, s_CUI_ID_FRAME_GameSettingSelfID_CHECKBOX_TitleOnCheckBoxCheck );
    theUiManager.OnCheckBoxCheck( ID_FRAME_GameSettingSelf, ID_CHECKBOX_Effect, s_CUI_ID_FRAME_GameSettingSelfID_CHECKBOX_EffectOnCheckBoxCheck );
    //theUiManager.OnCheckBoxCheck( ID_FRAME_GameSettingSelf, ID_CHECKBOX_SelfControl, s_CUI_ID_FRAME_GameSettingSelfID_CHECKBOX_SelfControlOnCheckBoxCheck );

	m_pID_FRAME_GameSettingSelf = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_GameSettingSelf );
	m_pID_PICTURE_Wall1 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_GameSettingSelf, ID_PICTURE_Wall1 );
	//m_pID_PICTURE_Wall2 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_GameSettingSelf, ID_PICTURE_Wall2 );
	m_pID_TEXT_TeamInfo = (ControlText*)theUiManager.FindControl( ID_FRAME_GameSettingSelf, ID_TEXT_TeamInfo );
	m_pID_TEXT_Name = (ControlText*)theUiManager.FindControl( ID_FRAME_GameSettingSelf, ID_TEXT_Name );
	m_pID_TEXT_Tong = (ControlText*)theUiManager.FindControl( ID_FRAME_GameSettingSelf, ID_TEXT_Tong );
	m_pID_TEXT_Hp = (ControlText*)theUiManager.FindControl( ID_FRAME_GameSettingSelf, ID_TEXT_Hp );
	m_pID_TEXT_Guild = (ControlText*)theUiManager.FindControl( ID_FRAME_GameSettingSelf, ID_TEXT_Guild );
	m_pID_TEXT_Mp = (ControlText*)theUiManager.FindControl( ID_FRAME_GameSettingSelf, ID_TEXT_Mp );
	m_pID_TEXT_Title = (ControlText*)theUiManager.FindControl( ID_FRAME_GameSettingSelf, ID_TEXT_Title );
	m_pID_CHECKBOX_Name = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSettingSelf, ID_CHECKBOX_Name );
	m_pID_CHECKBOX_TeamHp = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSettingSelf, ID_CHECKBOX_TeamHp );
	m_pID_CHECKBOX_Mp = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSettingSelf, ID_CHECKBOX_Mp );
	m_pID_CHECKBOX_Guild = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSettingSelf, ID_CHECKBOX_Guild );
	m_pID_CHECKBOX_Tong = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSettingSelf, ID_CHECKBOX_Tong );
	m_pID_CHECKBOX_Title = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSettingSelf, ID_CHECKBOX_Title );
	m_pID_TEXT_Effect = (ControlText*)theUiManager.FindControl( ID_FRAME_GameSettingSelf, ID_TEXT_Effect );
	m_pID_CHECKBOX_Effect = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSettingSelf, ID_CHECKBOX_Effect );
	//m_pID_CHECKBOX_SelfControl = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSettingSelf, ID_CHECKBOX_SelfControl );
	
    assert( m_pID_FRAME_GameSettingSelf );
	assert( m_pID_PICTURE_Wall1 );
	//assert( m_pID_PICTURE_Wall2 );
	assert( m_pID_TEXT_TeamInfo );
	assert( m_pID_TEXT_Name );
	assert( m_pID_TEXT_Tong );
	assert( m_pID_TEXT_Hp );
	assert( m_pID_TEXT_Guild );
	assert( m_pID_TEXT_Mp );
	assert( m_pID_TEXT_Title );
	assert( m_pID_CHECKBOX_Name );
	assert( m_pID_CHECKBOX_TeamHp );
	assert( m_pID_CHECKBOX_Mp );
	assert( m_pID_CHECKBOX_Guild );
	assert( m_pID_CHECKBOX_Tong );
	assert( m_pID_CHECKBOX_Title );
	assert( m_pID_TEXT_Effect );
	assert( m_pID_CHECKBOX_Effect );
	//assert( m_pID_CHECKBOX_SelfControl );
	
    m_pID_FRAME_GameSettingSelf->SetMsgHoldup(false);
	GetFrame()->SetFather(s_CUI_ID_FRAME_GameSettingUIBase.GetFrame());

	return true;
}
// 卸载UI
bool CUI_ID_FRAME_GameSettingSelf::_UnLoadUI()
{
	m_pID_FRAME_GameSettingSelf = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\GameSettingSelf.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_GameSettingSelf::_IsVisable()
{
	if( !m_pID_FRAME_GameSettingSelf )
		return false;
	return m_pID_FRAME_GameSettingSelf->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_GameSettingSelf::_SetVisable( const bool bVisable )
{
	if( !m_pID_FRAME_GameSettingSelf )
		return;
	m_pID_FRAME_GameSettingSelf->SetVisable( bVisable );
	if (bVisable)
	{
		RefreshUI();
	}
}
void CUI_ID_FRAME_GameSettingSelf::RefreshUI()
{
    if(!m_pID_FRAME_GameSettingSelf)
        return;

	for( int i = 0 ; i < GameSetting::eGSC_TOTAL ; ++ i )
	{
		bool bValue = ( bool )GameSetting::Instance()->GetLevel( (GameSetting::eGameSettingCategory)i );
		switch( i )
		{			
		case GameSetting::eGSC_SelfName:
			m_pID_CHECKBOX_Name->SetCheck( bValue );
			break;
		case GameSetting::eGSC_SelfHp:
			m_pID_CHECKBOX_TeamHp->SetCheck( bValue );
			break;
		case GameSetting::eGSC_SelfMp:
			m_pID_CHECKBOX_Mp->SetCheck( bValue );
			break;
		case GameSetting::eGSC_SelfTitle:
			m_pID_CHECKBOX_Title->SetCheck( bValue );
			break;
		case GameSetting::eGSC_SelfGuild:
			m_pID_CHECKBOX_Guild->SetCheck( bValue );
			break;
		case GameSetting::eGSC_SelfTong:
			m_pID_CHECKBOX_Tong->SetCheck( bValue );
			break;
        case GameSetting::eGSC_SelfEffect:
            m_pID_CHECKBOX_Effect->SetCheck( bValue );
            break;
		default:
			break;
		}
	}
    CheckSelfControl();
}

void CUI_ID_FRAME_GameSettingSelf::CheckSelfControl()
{
    if(!m_pID_FRAME_GameSettingSelf)
        return;

//     if( m_pID_CHECKBOX_Name->IsChecked()
//         && m_pID_CHECKBOX_TeamHp->IsChecked()
//         && m_pID_CHECKBOX_Mp->IsChecked()
//         && m_pID_CHECKBOX_Guild->IsChecked()
//         && m_pID_CHECKBOX_Tong->IsChecked()
//         && m_pID_CHECKBOX_Title->IsChecked() )
//         m_pID_CHECKBOX_SelfControl->SetCheck(true);
//     else
//         m_pID_CHECKBOX_SelfControl->SetCheck(false);
}