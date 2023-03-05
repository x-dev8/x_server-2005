/********************************************************************
	Created by UIEditor.exe
	FileName: E:\Document\请求拒绝\GameSettingRefuse.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "GameSettingRefuse.h"
#include "GameSetting.h"
#include "GameSettingUIBase.h"

CUI_ID_FRAME_GameSettingRefuse s_CUI_ID_FRAME_GameSettingRefuse;
MAP_FRAME_RUN( s_CUI_ID_FRAME_GameSettingRefuse, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_GameSettingRefuse, OnFrameRender )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSettingRefuse, ID_CHECKBOX_FightAddFriendOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSettingRefuse, ID_CHECKBOX_FightAddTeamOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSettingRefuse, ID_CHECKBOX_FightAddGangOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSettingRefuse, ID_CHECKBOX_FightPkOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSettingRefuse, ID_CHECKBOX_FightBargainingOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSettingRefuse, ID_CHECKBOX_FightHugOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSettingRefuse, ID_CHECKBOX_AddFriendOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSettingRefuse, ID_CHECKBOX_AddTeamOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSettingRefuse, ID_CHECKBOX_AddGangOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSettingRefuse, ID_CHECKBOX_PkOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSettingRefuse, ID_CHECKBOX_BargainingOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSettingRefuse, ID_CHECKBOX_HugOnCheckBoxCheck )
// MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSettingRefuse, ID_CHECKBOX_FightAllOnCheckBoxCheck )
// MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_GameSettingRefuse, ID_CHECKBOX_RestAllOnCheckBoxCheck )
CUI_ID_FRAME_GameSettingRefuse::CUI_ID_FRAME_GameSettingRefuse()
{
	// Member
	m_pID_FRAME_GameSettingRefuse = NULL;
	m_pID_PICTURE_Wall1 = NULL;
	m_pID_TEXT_Fight = NULL;
	m_pID_TEXT_FightAddTeam = NULL;
	m_pID_TEXT_FightAddFriend = NULL;
	m_pID_TEXT_FightAddGang = NULL;
	m_pID_TEXT_FightPk = NULL;
	m_pID_TEXT_FightBargaining = NULL;
	m_pID_TEXT_FightHug = NULL;
	m_pID_CHECKBOX_FightAddFriend = NULL;
	m_pID_CHECKBOX_FightAddTeam = NULL;
	m_pID_CHECKBOX_FightAddGang = NULL;
	m_pID_CHECKBOX_FightPk = NULL;
	m_pID_CHECKBOX_FightBargaining = NULL;
	m_pID_CHECKBOX_FightHug = NULL;
	m_pID_PICTURE_Wall2 = NULL;
	m_pID_TEXT_Rest = NULL;
	m_pID_TEXT_AddTeam = NULL;
	m_pID_TEXT_AddFriend = NULL;
	m_pID_TEXT_AddGang = NULL;
	m_pID_TEXT_Pk = NULL;
	m_pID_TEXT_Bargaining = NULL;
	m_pID_TEXT_Hug = NULL;
	m_pID_CHECKBOX_AddFriend = NULL;
	m_pID_CHECKBOX_AddTeam = NULL;
	m_pID_CHECKBOX_AddGang = NULL;
	m_pID_CHECKBOX_Pk = NULL;
	m_pID_CHECKBOX_Bargaining = NULL;
	m_pID_CHECKBOX_Hug = NULL;
// 	m_pID_CHECKBOX_FightAll = NULL;
// 	m_pID_CHECKBOX_RestAll = NULL;

}
	// Frame
	bool CUI_ID_FRAME_GameSettingRefuse::OnFrameRun()
	{
		return true;
	}
	bool CUI_ID_FRAME_GameSettingRefuse::OnFrameRender()
	{
		return true;
	}
	// CheckBox
	void CUI_ID_FRAME_GameSettingRefuse::ID_CHECKBOX_FightAddFriendOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
	{
        GameSetting::Instance()->SetLevel( GameSetting::eGSC_RefuseAddFriendInFight, (unsigned int)*pbChecked );
        GameSetting::Instance()->CommitChanges();
        if( pSender )
            CheckAllInFight();
	}
	// CheckBox
	void CUI_ID_FRAME_GameSettingRefuse::ID_CHECKBOX_FightAddTeamOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
	{
        GameSetting::Instance()->SetLevel( GameSetting::eGSC_RefuseAddTeamInFight, (unsigned int)*pbChecked );
        GameSetting::Instance()->CommitChanges();
        if( pSender )
            CheckAllInFight();
	}
	// CheckBox
	void CUI_ID_FRAME_GameSettingRefuse::ID_CHECKBOX_FightAddGangOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
	{
        GameSetting::Instance()->SetLevel( GameSetting::eGSC_RefuseAddGangInFight, (unsigned int)*pbChecked );
        GameSetting::Instance()->CommitChanges();
        if( pSender )
            CheckAllInFight();
	}
	// CheckBox
	void CUI_ID_FRAME_GameSettingRefuse::ID_CHECKBOX_FightPkOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
	{
        GameSetting::Instance()->SetLevel( GameSetting::eGSC_RefuseDuelInFight, (unsigned int)*pbChecked );
        GameSetting::Instance()->CommitChanges();
        if( pSender )
            CheckAllInFight();
	}
	// CheckBox
	void CUI_ID_FRAME_GameSettingRefuse::ID_CHECKBOX_FightBargainingOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
	{
        GameSetting::Instance()->SetLevel( GameSetting::eGSC_RefuseBargainInFight, (unsigned int)*pbChecked );
        GameSetting::Instance()->CommitChanges();
        if( pSender )
            CheckAllInFight();
	}
	// CheckBox
	void CUI_ID_FRAME_GameSettingRefuse::ID_CHECKBOX_FightHugOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
	{
        GameSetting::Instance()->SetLevel( GameSetting::eGSC_RefuseHugInFight, (unsigned int)*pbChecked );
        GameSetting::Instance()->CommitChanges();
        if( pSender )
            CheckAllInFight();
	}
	// CheckBox
	void CUI_ID_FRAME_GameSettingRefuse::ID_CHECKBOX_AddFriendOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
	{
        GameSetting::Instance()->SetLevel( GameSetting::eGSC_RefuseAddFriend, (unsigned int)*pbChecked );
        GameSetting::Instance()->CommitChanges();
        if( pSender )
            CheckAllInRest();
	}
	// CheckBox
	void CUI_ID_FRAME_GameSettingRefuse::ID_CHECKBOX_AddTeamOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
	{
        GameSetting::Instance()->SetLevel( GameSetting::eGSC_RefuseAddTeam, (unsigned int)*pbChecked );
        GameSetting::Instance()->CommitChanges();
        if( pSender )
            CheckAllInRest();
	}
	// CheckBox
	void CUI_ID_FRAME_GameSettingRefuse::ID_CHECKBOX_AddGangOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
	{
        GameSetting::Instance()->SetLevel( GameSetting::eGSC_RefuseAddGang, (unsigned int)*pbChecked );
        GameSetting::Instance()->CommitChanges();
        if( pSender )
            CheckAllInRest();
	}
	// CheckBox
	void CUI_ID_FRAME_GameSettingRefuse::ID_CHECKBOX_PkOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
	{
        GameSetting::Instance()->SetLevel( GameSetting::eGSC_RefuseDuel, (unsigned int)*pbChecked );
        GameSetting::Instance()->CommitChanges();
        if( pSender )
            CheckAllInRest();
	}
	// CheckBox
	void CUI_ID_FRAME_GameSettingRefuse::ID_CHECKBOX_BargainingOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
	{
        GameSetting::Instance()->SetLevel( GameSetting::eGSC_RefuseBargain, (unsigned int)*pbChecked );
        GameSetting::Instance()->CommitChanges();
        if( pSender )
            CheckAllInRest();
	}
	// CheckBox
	void CUI_ID_FRAME_GameSettingRefuse::ID_CHECKBOX_HugOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
	{
        GameSetting::Instance()->SetLevel( GameSetting::eGSC_RefuseHug, (unsigned int)*pbChecked );
        GameSetting::Instance()->CommitChanges();
        if( pSender )
            CheckAllInRest();
    }
	// CheckBox
	//void CUI_ID_FRAME_GameSettingRefuse::ID_CHECKBOX_FightAllOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
	//{
 //       ID_CHECKBOX_FightAddFriendOnCheckBoxCheck( NULL, pbChecked );
 //       ID_CHECKBOX_FightAddTeamOnCheckBoxCheck( NULL, pbChecked );
 //       ID_CHECKBOX_FightAddGangOnCheckBoxCheck( NULL, pbChecked );
 //       ID_CHECKBOX_FightPkOnCheckBoxCheck( NULL, pbChecked );
 //       ID_CHECKBOX_FightBargainingOnCheckBoxCheck( NULL, pbChecked );
 //       ID_CHECKBOX_FightHugOnCheckBoxCheck( NULL, pbChecked );
 //       m_pID_CHECKBOX_FightAddFriend->SetCheck( *pbChecked );
 //       m_pID_CHECKBOX_FightAddTeam->SetCheck( *pbChecked );
 //       m_pID_CHECKBOX_FightAddGang->SetCheck( *pbChecked );
 //       m_pID_CHECKBOX_FightPk->SetCheck( *pbChecked );
 //       m_pID_CHECKBOX_FightBargaining->SetCheck( *pbChecked );
 //       m_pID_CHECKBOX_FightHug->SetCheck( *pbChecked );
	//}
	//// CheckBox
	//void CUI_ID_FRAME_GameSettingRefuse::ID_CHECKBOX_RestAllOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
	//{
 //       ID_CHECKBOX_AddFriendOnCheckBoxCheck( NULL, pbChecked );
 //       ID_CHECKBOX_AddTeamOnCheckBoxCheck( NULL, pbChecked );
 //       ID_CHECKBOX_AddGangOnCheckBoxCheck( NULL, pbChecked );
 //       ID_CHECKBOX_PkOnCheckBoxCheck( NULL, pbChecked );
 //       ID_CHECKBOX_BargainingOnCheckBoxCheck( NULL, pbChecked );
 //       ID_CHECKBOX_HugOnCheckBoxCheck( NULL, pbChecked );
 //       m_pID_CHECKBOX_AddFriend->SetCheck( *pbChecked );
 //       m_pID_CHECKBOX_AddTeam->SetCheck( *pbChecked );
 //       m_pID_CHECKBOX_AddGang->SetCheck( *pbChecked );
 //       m_pID_CHECKBOX_Pk->SetCheck( *pbChecked );
 //       m_pID_CHECKBOX_Bargaining->SetCheck( *pbChecked );
 //       m_pID_CHECKBOX_Hug->SetCheck( *pbChecked );
	//}

	// 装载UI
bool CUI_ID_FRAME_GameSettingRefuse::_LoadUI()
	{
		DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\GameSettingRefuse.MEUI" );
		if ( dwResult == 0 )
		{
			MESSAGE_BOX("读取文件[Data\\UI\\GameSettingRefuse.MEUI]失败")
			return false;
		}
		return DoControlConnect();
	}
	// 关连控件
	bool CUI_ID_FRAME_GameSettingRefuse::DoControlConnect()
	{
		theUiManager.OnFrameRun( ID_FRAME_GameSettingRefuse, s_CUI_ID_FRAME_GameSettingRefuseOnFrameRun );
		theUiManager.OnFrameRender( ID_FRAME_GameSettingRefuse, s_CUI_ID_FRAME_GameSettingRefuseOnFrameRender );
        theUiManager.OnCheckBoxCheck( ID_FRAME_GameSettingRefuse, ID_CHECKBOX_FightAddFriend, s_CUI_ID_FRAME_GameSettingRefuseID_CHECKBOX_FightAddFriendOnCheckBoxCheck );
        theUiManager.OnCheckBoxCheck( ID_FRAME_GameSettingRefuse, ID_CHECKBOX_FightAddTeam, s_CUI_ID_FRAME_GameSettingRefuseID_CHECKBOX_FightAddTeamOnCheckBoxCheck );
        theUiManager.OnCheckBoxCheck( ID_FRAME_GameSettingRefuse, ID_CHECKBOX_FightAddGang, s_CUI_ID_FRAME_GameSettingRefuseID_CHECKBOX_FightAddGangOnCheckBoxCheck );
        theUiManager.OnCheckBoxCheck( ID_FRAME_GameSettingRefuse, ID_CHECKBOX_FightPk, s_CUI_ID_FRAME_GameSettingRefuseID_CHECKBOX_FightPkOnCheckBoxCheck );
        theUiManager.OnCheckBoxCheck( ID_FRAME_GameSettingRefuse, ID_CHECKBOX_FightBargaining, s_CUI_ID_FRAME_GameSettingRefuseID_CHECKBOX_FightBargainingOnCheckBoxCheck );
        theUiManager.OnCheckBoxCheck( ID_FRAME_GameSettingRefuse, ID_CHECKBOX_FightHug, s_CUI_ID_FRAME_GameSettingRefuseID_CHECKBOX_FightHugOnCheckBoxCheck );
        theUiManager.OnCheckBoxCheck( ID_FRAME_GameSettingRefuse, ID_CHECKBOX_AddFriend, s_CUI_ID_FRAME_GameSettingRefuseID_CHECKBOX_AddFriendOnCheckBoxCheck );
        theUiManager.OnCheckBoxCheck( ID_FRAME_GameSettingRefuse, ID_CHECKBOX_AddTeam, s_CUI_ID_FRAME_GameSettingRefuseID_CHECKBOX_AddTeamOnCheckBoxCheck );
        theUiManager.OnCheckBoxCheck( ID_FRAME_GameSettingRefuse, ID_CHECKBOX_AddGang, s_CUI_ID_FRAME_GameSettingRefuseID_CHECKBOX_AddGangOnCheckBoxCheck );
        theUiManager.OnCheckBoxCheck( ID_FRAME_GameSettingRefuse, ID_CHECKBOX_Pk, s_CUI_ID_FRAME_GameSettingRefuseID_CHECKBOX_PkOnCheckBoxCheck );
        theUiManager.OnCheckBoxCheck( ID_FRAME_GameSettingRefuse, ID_CHECKBOX_Bargaining, s_CUI_ID_FRAME_GameSettingRefuseID_CHECKBOX_BargainingOnCheckBoxCheck );
        theUiManager.OnCheckBoxCheck( ID_FRAME_GameSettingRefuse, ID_CHECKBOX_Hug, s_CUI_ID_FRAME_GameSettingRefuseID_CHECKBOX_HugOnCheckBoxCheck );
//         theUiManager.OnCheckBoxCheck( ID_FRAME_GameSettingRefuse, ID_CHECKBOX_FightAll, s_CUI_ID_FRAME_GameSettingRefuseID_CHECKBOX_FightAllOnCheckBoxCheck );
//         theUiManager.OnCheckBoxCheck( ID_FRAME_GameSettingRefuse, ID_CHECKBOX_RestAll, s_CUI_ID_FRAME_GameSettingRefuseID_CHECKBOX_RestAllOnCheckBoxCheck );

		m_pID_FRAME_GameSettingRefuse = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_GameSettingRefuse );
		m_pID_PICTURE_Wall1 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_GameSettingRefuse, ID_PICTURE_Wall1 );
		m_pID_TEXT_Fight = (ControlText*)theUiManager.FindControl( ID_FRAME_GameSettingRefuse, ID_TEXT_Fight );
		m_pID_TEXT_FightAddTeam = (ControlText*)theUiManager.FindControl( ID_FRAME_GameSettingRefuse, ID_TEXT_FightAddTeam );
		m_pID_TEXT_FightAddFriend = (ControlText*)theUiManager.FindControl( ID_FRAME_GameSettingRefuse, ID_TEXT_FightAddFriend );
		m_pID_TEXT_FightAddGang = (ControlText*)theUiManager.FindControl( ID_FRAME_GameSettingRefuse, ID_TEXT_FightAddGang );
		m_pID_TEXT_FightPk = (ControlText*)theUiManager.FindControl( ID_FRAME_GameSettingRefuse, ID_TEXT_FightPk );
		m_pID_TEXT_FightBargaining = (ControlText*)theUiManager.FindControl( ID_FRAME_GameSettingRefuse, ID_TEXT_FightBargaining );
		m_pID_TEXT_FightHug = (ControlText*)theUiManager.FindControl( ID_FRAME_GameSettingRefuse, ID_TEXT_FightHug );
		m_pID_CHECKBOX_FightAddFriend = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSettingRefuse, ID_CHECKBOX_FightAddFriend );
		m_pID_CHECKBOX_FightAddTeam = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSettingRefuse, ID_CHECKBOX_FightAddTeam );
		m_pID_CHECKBOX_FightAddGang = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSettingRefuse, ID_CHECKBOX_FightAddGang );
		m_pID_CHECKBOX_FightPk = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSettingRefuse, ID_CHECKBOX_FightPk );
		m_pID_CHECKBOX_FightBargaining = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSettingRefuse, ID_CHECKBOX_FightBargaining );
		m_pID_CHECKBOX_FightHug = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSettingRefuse, ID_CHECKBOX_FightHug );
		m_pID_PICTURE_Wall2 = (ControlPicture*)theUiManager.FindControl( ID_FRAME_GameSettingRefuse, ID_PICTURE_Wall2 );
		m_pID_TEXT_Rest = (ControlText*)theUiManager.FindControl( ID_FRAME_GameSettingRefuse, ID_TEXT_Rest );
		m_pID_TEXT_AddTeam = (ControlText*)theUiManager.FindControl( ID_FRAME_GameSettingRefuse, ID_TEXT_AddTeam );
		m_pID_TEXT_AddFriend = (ControlText*)theUiManager.FindControl( ID_FRAME_GameSettingRefuse, ID_TEXT_AddFriend );
		m_pID_TEXT_AddGang = (ControlText*)theUiManager.FindControl( ID_FRAME_GameSettingRefuse, ID_TEXT_AddGang );
		m_pID_TEXT_Pk = (ControlText*)theUiManager.FindControl( ID_FRAME_GameSettingRefuse, ID_TEXT_Pk );
		m_pID_TEXT_Bargaining = (ControlText*)theUiManager.FindControl( ID_FRAME_GameSettingRefuse, ID_TEXT_Bargaining );
		m_pID_TEXT_Hug = (ControlText*)theUiManager.FindControl( ID_FRAME_GameSettingRefuse, ID_TEXT_Hug );
		m_pID_CHECKBOX_AddFriend = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSettingRefuse, ID_CHECKBOX_AddFriend );
		m_pID_CHECKBOX_AddTeam = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSettingRefuse, ID_CHECKBOX_AddTeam );
		m_pID_CHECKBOX_AddGang = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSettingRefuse, ID_CHECKBOX_AddGang );
		m_pID_CHECKBOX_Pk = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSettingRefuse, ID_CHECKBOX_Pk );
		m_pID_CHECKBOX_Bargaining = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSettingRefuse, ID_CHECKBOX_Bargaining );
		m_pID_CHECKBOX_Hug = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSettingRefuse, ID_CHECKBOX_Hug );
// 		m_pID_CHECKBOX_FightAll = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSettingRefuse, ID_CHECKBOX_FightAll );
// 		m_pID_CHECKBOX_RestAll = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_GameSettingRefuse, ID_CHECKBOX_RestAll );
		assert( m_pID_FRAME_GameSettingRefuse );
		assert( m_pID_PICTURE_Wall1 );
		assert( m_pID_TEXT_Fight );
		assert( m_pID_TEXT_FightAddTeam );
		assert( m_pID_TEXT_FightAddFriend );
		assert( m_pID_TEXT_FightAddGang );
		assert( m_pID_TEXT_FightPk );
		assert( m_pID_TEXT_FightBargaining );
		assert( m_pID_TEXT_FightHug );
		assert( m_pID_CHECKBOX_FightAddFriend );
		assert( m_pID_CHECKBOX_FightAddTeam );
		assert( m_pID_CHECKBOX_FightAddGang );
		assert( m_pID_CHECKBOX_FightPk );
		assert( m_pID_CHECKBOX_FightBargaining );
		assert( m_pID_CHECKBOX_FightHug );
		assert( m_pID_PICTURE_Wall2 );
		assert( m_pID_TEXT_Rest );
		assert( m_pID_TEXT_AddTeam );
		assert( m_pID_TEXT_AddFriend );
		assert( m_pID_TEXT_AddGang );
		assert( m_pID_TEXT_Pk );
		assert( m_pID_TEXT_Bargaining );
		assert( m_pID_TEXT_Hug );
		assert( m_pID_CHECKBOX_AddFriend );
		assert( m_pID_CHECKBOX_AddTeam );
		assert( m_pID_CHECKBOX_AddGang );
		assert( m_pID_CHECKBOX_Pk );
		assert( m_pID_CHECKBOX_Bargaining );
		assert( m_pID_CHECKBOX_Hug );
// 		assert( m_pID_CHECKBOX_FightAll );
// 		assert( m_pID_CHECKBOX_RestAll );
        m_pID_FRAME_GameSettingRefuse->SetMsgHoldup(false);
		GetFrame()->SetFather(s_CUI_ID_FRAME_GameSettingUIBase.GetFrame());
		return true;
	}
	// 卸载UI
bool CUI_ID_FRAME_GameSettingRefuse::_UnLoadUI()
	{
		m_pID_FRAME_GameSettingRefuse = NULL;
		return theUiManager.RemoveFrame( "Data\\UI\\GameSettingRefuse.MEUI" );
	}
	// 是否可视
	bool CUI_ID_FRAME_GameSettingRefuse::_IsVisable()
	{
		if( !m_pID_FRAME_GameSettingRefuse )
			return false;
		return m_pID_FRAME_GameSettingRefuse->IsVisable();
	}
	// 设置是否可视
	void CUI_ID_FRAME_GameSettingRefuse::_SetVisable( const bool bVisable )
	{
		if( !m_pID_FRAME_GameSettingRefuse )
			return;
		m_pID_FRAME_GameSettingRefuse->SetVisable( bVisable );
		if (bVisable)
		{
			RefreshUI();
		}
	}

    void CUI_ID_FRAME_GameSettingRefuse::RefreshUI()
    {
		if (!IsUILoad())
		{
			return;
		}
        for( int i = 0 ; i < GameSetting::eGSC_TOTAL ; ++ i )
        {
            bool bValue = ( bool )GameSetting::Instance()->GetLevel( (GameSetting::eGameSettingCategory)i );
            switch( i )
            {
            case GameSetting::eGSC_RefuseAddFriendInFight:
                m_pID_CHECKBOX_FightAddFriend->SetCheck( bValue );
                break;
            case GameSetting::eGSC_RefuseAddTeamInFight:
                m_pID_CHECKBOX_FightAddTeam->SetCheck( bValue );
                break;
            case GameSetting::eGSC_RefuseAddGangInFight:
                m_pID_CHECKBOX_FightAddGang->SetCheck( bValue );
                break;
            case GameSetting::eGSC_RefuseDuelInFight:
                m_pID_CHECKBOX_FightPk->SetCheck( bValue );
                break;
            case GameSetting::eGSC_RefuseBargainInFight:
                m_pID_CHECKBOX_FightBargaining->SetCheck( bValue );
                break;
            case GameSetting::eGSC_RefuseHugInFight:
                m_pID_CHECKBOX_FightHug->SetCheck( bValue );
                break;
            case GameSetting::eGSC_RefuseAddFriend:
                m_pID_CHECKBOX_AddFriend->SetCheck( bValue );
                break;
            case GameSetting::eGSC_RefuseAddTeam:
                m_pID_CHECKBOX_AddTeam->SetCheck( bValue );
                break;
            case GameSetting::eGSC_RefuseAddGang:
                m_pID_CHECKBOX_AddGang->SetCheck( bValue );
                break;
            case GameSetting::eGSC_RefuseDuel:
                m_pID_CHECKBOX_Pk->SetCheck( bValue );
                break;
            case GameSetting::eGSC_RefuseBargain:
                m_pID_CHECKBOX_Bargaining->SetCheck( bValue );
                break;
            case GameSetting::eGSC_RefuseHug:
                m_pID_CHECKBOX_Hug->SetCheck( bValue );
                break;
            default:
                break;
            }
        }
        CheckAllInFight();
        CheckAllInRest();
    }

    void CUI_ID_FRAME_GameSettingRefuse::CheckAllInFight()
    {
        // UI都改成允许，所以所有都没勾上时，m_pID_CHECKBOX_FightAll才设成没勾上
//         if( !m_pID_CHECKBOX_FightAddFriend->IsChecked()
//             && !m_pID_CHECKBOX_FightAddTeam->IsChecked()
//             && !m_pID_CHECKBOX_FightAddGang->IsChecked()
//             && !m_pID_CHECKBOX_FightPk->IsChecked()
//             && !m_pID_CHECKBOX_FightBargaining->IsChecked()
//             && !m_pID_CHECKBOX_FightHug->IsChecked() )
//             m_pID_CHECKBOX_FightAll->SetCheck(false);
//         else
//             m_pID_CHECKBOX_FightAll->SetCheck(true);
    }

    void CUI_ID_FRAME_GameSettingRefuse::CheckAllInRest()
    {
        // UI都改成允许，所以所有都没勾上时，m_pID_CHECKBOX_RestAll才设成没勾上
//         if( !m_pID_CHECKBOX_AddFriend->IsChecked()
//             && !m_pID_CHECKBOX_AddTeam->IsChecked()
//             && !m_pID_CHECKBOX_AddGang->IsChecked()
//             && !m_pID_CHECKBOX_Pk->IsChecked()
//             && !m_pID_CHECKBOX_Bargaining->IsChecked()
//             && !m_pID_CHECKBOX_Hug->IsChecked() )
//             m_pID_CHECKBOX_RestAll->SetCheck(false);
//         else
//             m_pID_CHECKBOX_RestAll->SetCheck(true);
    }