/********************************************************************
Created by UIEditor.exe
FileName: C:\Documents and Settings\huwen\桌面\ChatInfoBox.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "ChatInfoBox.h"
// #include "facedlg.h"
#include "facedlg1.h"
// #include "ChatSetDlg.h"
#include "MessageDefine.h"
#include "GameMain.h"
#include"../PlayerRole.h"
#include "PlayerMgr.h"
#include "../Player.h"
#include "main.h"
#include "LuaScript.h"
#include "LuaFuns.h"
#include "SortLuaScript.h"
#include "XmlStringLanguage.h"
#include "WordParser.h"
// #include "Tinyxml/tinyxml.h"
#include "RbtnMenu.h"
#include "create.h"
#include "chatcheck.h"
// #include "ChatSystem.h"
#include "SelfRbtnMenu.h"
#include "MessageBox.h"
#include "../color_config.h"
#include "../NpcCoord.h"
//  
#include "../shortcutkey_configure.h"
// //#include "ActionList.h"
#include "chat_particular.h"
#include "chat_list.h"
// //#include "SendGM.h"
#include "target.h"
#include "ErrorLog.h"
#include "InputBox.h"
#include "AddMember.h"
#include "Shopping_InputBox.h"
// #include "Guild_Placard.h"
#include "core/Name.h"
//#include "GraphicCodeCheck.h"
#include "winuser.h"
#include "Shopping_MessageBox.h" 
#include "NpcChatDialogBox.h"
#include "SelectBox.h"
// #include "Guild_Exp_Allot.h"
#include "ChatSet.h"
#include "ChatChannelConfig.h"
#include "ScreenInfoManager.h"

using namespace Common;

extern GAME_STATE g_GameState;

#include "MeUi/ExpressionManager.h"

#include "IntroductionManager.h"
#include "ExpressionAction.h"
#include "CountryDefine.h"
#include "SystemFamily.h"
#include "Speaker.h"

CUI_ChatInfoBox s_CUI_ChatInfoBox;
MAP_FRAME_RUN( s_CUI_ChatInfoBox, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ChatInfoBox, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ChatInfoBox, ID_BUTTON_ChatOutTypeOnButtonClick )
MAP_EDIT_ENTER_CALLBACK( s_CUI_ChatInfoBox, ID_EDIT_INPUTOnEditEnter )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ChatInfoBox, ID_BUTTON_faceOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ChatInfoBox, ID_BUTTON_PinBiOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ChatInfoBox, ID_BUTTON_HornOnButtonClick )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ChatInfoBox, ID_CHECKBOX_BPublicOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ChatInfoBox, ID_CHECKBOX_BTeamOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ChatInfoBox, ID_CHECKBOX_BGuild1OnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ChatInfoBox, ID_CHECKBOX_BHightShoutOnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ChatInfoBox, ID_CHECKBOX_BCountryOnCheckBoxCheck )
//MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ChatInfoBox, ID_CHECKBOX_BZhenying2OnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ChatInfoBox, ID_CHECKBOX_ChatPrivateOnCheckBoxCheck )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ChatInfoBox, ID_BUTTON_EnterOnButtonClick )
//MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ChatInfoBox, ID_CHECKBOX_BZhenyingOnCheckBoxCheck )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ChatInfoBox, ID_BUTTON_ChatPrivateOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ChatInfoBox, ID_BUTTON_BTeamOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ChatInfoBox, ID_BUTTON_BGuild1OnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ChatInfoBox, ID_BUTTON_BCountryOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ChatInfoBox, ID_BUTTON_BHightShoutOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ChatInfoBox, ID_BUTTON_FamilyOnButtonClick )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ChatInfoBox, ID_CHECKBOX_FamilyOnCheckBoxCheck )

MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ChatInfoBox, ID_CHECKBOX_GuanYuanOnCheckBoxCheck )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ChatInfoBox, ID_BUTTON_GuanYuanOnButtonClick )

CUI_ChatInfoBox::CUI_ChatInfoBox()
{
	// Member
	m_pChatInfoBox = NULL;
	m_pID_BUTTON_ChatOutType = NULL;
	m_pID_EDIT_INPUT = NULL;
	m_pID_BUTTON_face = NULL;
	m_pID_BUTTON_PinBi = NULL;
    m_pID_BUTTON_Horn = NULL;
	m_pID_CHECKBOX_BPublic = NULL;
	m_pID_CHECKBOX_BTeam = NULL;
	m_pID_CHECKBOX_BGuild1 = NULL;
	m_pID_CHECKBOX_BHightShout = NULL;
	//m_pID_CHECKBOX_BZhenying2 = NULL;
	m_pID_BUTTON_Enter = NULL;
	//m_pID_CHECKBOX_BZhenying = NULL;

	m_pID_BUTTON_Family = NULL;
	m_pID_CHECKBOX_Family = NULL;

   //lyh++
	m_pID_CHECKBOX_BGuanYuan = NULL;
	m_pID_BUTTON_BGuanYuan = NULL;
	

	_nDefaultChannel = MsgChat::CHAT_TYPE_NORMAL;
	_nCurrentChannel = MsgChat::CHAT_TYPE_NORMAL;


	m_bAddChatInfo = true;

	m_nChatChannelIndex = 0;

	m_pChatInfoText = NULL;
	m_nCurrChatInfoIndex = 0;
	m_vecChatCommand.clear();
}
// Button
bool CUI_ChatInfoBox::ID_BUTTON_ChatOutTypeOnButtonClick( ControlObject* pSender )
{
	return OnClickChannelButton();
}
// Edit
void CUI_ChatInfoBox::ID_EDIT_INPUTOnEditEnter( ControlObject* pSender, const char* szData )
{
	if(!m_pChatInfoBox)
	{
		assert(false&&"ui error");
		return ;
	}

	if( _bActiveInput )
	{
        //杨晓勇需求，在DefendString中的字符传，禁止发送
        if(CChatCheck::getInstance()->CheckStringInForbit(szData))
            CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Chat_ChannelTip, theXmlString.GetString(eText_FilterCharInfo) );
		else
		{
			// 判断并播表情动作
			ExpAction::ESex sex = (thePlayerRole.GetSex() == Sex_Male) ? ExpAction::Male : ExpAction::Female;
			bool bIsExpressionAction = CExpressionAction::Instance().CheckAndDoExpressionAction(szData, sex);
			if( bIsExpressionAction )
			{
				*m_pID_EDIT_INPUT = "";
				AddMyChatHistories(szData);
			}
			else
				ProcessAndSendChatMessage(_nDefaultChannel,szData);
		}

        m_pID_EDIT_INPUT->SetActivate( false );
        s_CUI_ID_FRAME_FACE.SetVisable( false );
        ImmAssociateContext( g_hWnd, NULL );
		m_pChatInfoBox->SetActivate( true );
		SetVisable( false );

		m_bSendMsg = true;
	}
	return;
}

void CUI_ChatInfoBox::ToggleNext()
{
	if(s_CUI_ID_FRAME_Speaker.IsVisable())
		return;
	bool bChecked = true;
	if(CommonChatFrame::GetActiveChatFrame())
	{
		CommonChatFrame::GetActiveChatFrame()->ClearHyberLinks();
	}

	switch( _nDefaultChannel )
	{
// 	case MsgChat::CHAT_TYPE_LEAGUE:
// 		ID_CHECKBOX_BHightShoutOnCheckBoxCheck( m_pID_CHECKBOX_BHightShout, &bChecked );
// 		break;
	case MsgChat::CHAT_TYPE_HIGHSHOUT:
		ID_CHECKBOX_BPublicOnCheckBoxCheck( m_pID_CHECKBOX_BPublic, &bChecked );
		break;
	case MsgChat::CHAT_TYPE_GUILD:
		ID_CHECKBOX_BCountryOnCheckBoxCheck( m_pID_CHECKBOX_BCountry, &bChecked );
		break;
	case MsgChat::CHAT_TYPE_TERM:
		ID_CHECKBOX_BGuild1OnCheckBoxCheck( m_pID_CHECKBOX_BGuild1, &bChecked );
		break;
	case MsgChat::CHAT_TYPE_PRIVATE:
		ID_CHECKBOX_BTeamOnCheckBoxCheck( m_pID_CHECKBOX_BTeam, &bChecked );		
		break;
	case MsgChat::CHAT_TYPE_NORMAL:
		ID_CHECKBOX_ChatPrivateOnCheckBoxCheck( m_pID_CHECKBOX_ChatPrivate, &bChecked );
// 		ID_CHECKBOX_BZhenyingOnCheckBoxCheck( m_pID_CHECKBOX_BZhenying, &bChecked );
// 		break;
// 	case MsgChat::CHAT_TYPE_BATTLE:
		/*ID_CHECKBOX_BCountryOnCheckBoxCheck( m_pID_CHECKBOX_BCountry, &bChecked );*/
		
		break;
	//case MsgChat::CHAT_TYPE_COUNTRY:
	//	ID_CHECKBOX_BHightShoutOnCheckBoxCheck( m_pID_CHECKBOX_BHightShout, &bChecked );
	//	break;
	case MsgChat::CHAT_TYPE_COUNTRY:
		ID_CHECKBOX_GuanYuanOnCheckBoxCheck( m_pID_CHECKBOX_BGuanYuan, &bChecked );
		break;
	case  MsgChat::CHAT_TYPE_COUNTRYOFFICIAL: //切换官员聊天频道 lyh++		
		ID_CHECKBOX_BHightShoutOnCheckBoxCheck( m_pID_CHECKBOX_BHightShout, &bChecked );
		break;
	}
}

// Button
bool CUI_ChatInfoBox::ID_BUTTON_PinBiOnButtonClick( ControlObject* pSender )
{
	if(!m_pChatInfoBox)
	{
		assert(false&&"ui error");
		return false;
	}
	//m_receiveRadioGroup.SetVisible(!m_receiveRadioGroup.IsVisible());
	s_CUI_ID_FRAME_ChatSet.SetVisable(!s_CUI_ID_FRAME_ChatSet.IsVisable());
	return true;
}

bool CUI_ChatInfoBox::ID_BUTTON_HornOnButtonClick( ControlObject* pSender )
{
    if( !m_pChatInfoBox )
        return false;

    s_CUI_ID_FRAME_Speaker.SetVisable( true, AN_S2A_OpenUI_ChatHIGHSHOUT );
    return true;
}


void CUI_ChatInfoBox::ID_CHECKBOX_GuanYuanOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  )
{
	if(!m_pChatInfoBox)
	{
		assert(false&&"ui error");
		return ;
	}
	ToggleChannel(pSender, MsgChat::CHAT_TYPE_COUNTRYOFFICIAL);

	SetChatOutTypeText( theXmlString.GetString(eChatType_GuanYuan) );
	SetChatColor(Color_Config.getColor(CC_Chat_ChatGuanYuan));
	SetChatOutTypeButton(pSender);

}
//lyh+=
bool CUI_ChatInfoBox::ID_BUTTON_GuanYuanOnButtonClick( ControlObject* pSender )
{

	return OnClickChannelButton();
}


// CheckBox
void CUI_ChatInfoBox::ID_CHECKBOX_BPublicOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if(!m_pChatInfoBox)
	{
		assert(false&&"ui error");
		return ;
	}
	ToggleChannel(pSender, MsgChat::CHAT_TYPE_NORMAL);
	SetChatOutTypeText( theXmlString.GetString(eChatType_Normal) );
	SetChatColor(Color_Config.getColor(CC_CHAT_NORMAL));

	SetChatOutTypeButton(pSender);
}
// CheckBox
void CUI_ChatInfoBox::ID_CHECKBOX_BTeamOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if(!m_pChatInfoBox)
	{
		assert(false&&"ui error");
		return ;
	}
	ToggleChannel(pSender, MsgChat::CHAT_TYPE_TERM);
	SetChatOutTypeText( theXmlString.GetString(eChatType_Team) );
	SetChatColor(Color_Config.getColor(CC_CHAT_TEAM));

	SetChatOutTypeButton(pSender);
}
// CheckBox
void CUI_ChatInfoBox::ID_CHECKBOX_BGuild1OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if(!m_pChatInfoBox)
	{
		assert(false&&"ui error");
		return ;
	}
	ToggleChannel(pSender, MsgChat::CHAT_TYPE_GUILD);
	SetChatOutTypeText( theXmlString.GetString(eChatType_Guild) );
	SetChatColor(Color_Config.getColor(CC_CHAT_GUILD));

	SetChatOutTypeButton(pSender);
}
// CheckBox
void CUI_ChatInfoBox::ID_CHECKBOX_BHightShoutOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if(!m_pChatInfoBox)
	{
		assert(false&&"ui error");
		return ;
	}
	ToggleChannel(pSender, MsgChat::CHAT_TYPE_HIGHSHOUT);
	SetChatOutTypeText( theXmlString.GetString(eChatType_HightShout) );
	SetChatColor(Color_Config.getColor(CC_CHAT_HIGHSHOUT));

	SetChatOutTypeButton(pSender);
}
// CheckBox
void CUI_ChatInfoBox::ID_CHECKBOX_BCountryOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if(!m_pChatInfoBox)
	{
		assert(false&&"ui error");
		return ;
	}
	ToggleChannel(pSender, MsgChat::CHAT_TYPE_COUNTRY);
	SetChatOutTypeText( theXmlString.GetString(eChatType_CountryString) );
	SetChatColor(Color_Config.getColor(CC_CHAT_COUNTRY));

	SetChatOutTypeButton(pSender);
}
// CheckBox
// void CUI_ChatInfoBox::ID_CHECKBOX_BZhenying2OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
// {
// 	if(!m_pChatInfoBox)
// 	{
// 		assert(false&&"ui error");
// 		return ;
// 	}
// 
// 	ToggleChannel(pSender, MsgChat::CHAT_TYPE_LEAGUE);
// 	SetChatOutTypeText( theXmlString.GetString(eChatType_Alignment) );
// 	SetChatColor(Color_Config.getColor(CC_CHAT_LEAGUE));
// }
// CheckBox
void CUI_ChatInfoBox::ID_CHECKBOX_ChatPrivateOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if(!m_pChatInfoBox)
	{
		assert(false&&"ui error");
		return ;
	}

	//ToggleChannel(pSender, MsgChat::CHAT_TYPE_PRIVATE);
	//SetChatOutTypeText( theXmlString.GetString(eChatType_Private) );
	//SetChatColor(Color_Config.getColor(CC_CHAT_PERSONAL));
	Begin2Secret(m_szPrivateToName.c_str());

	SetChatOutTypeButton(pSender);
}
// CheckBox
// void CUI_ChatInfoBox::ID_CHECKBOX_BZhenyingOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
// {
// 	if(!m_pChatInfoBox)
// 	{
// 		assert(false&&"ui error");
// 		return ;
// 	}
// 
// // 	ToggleChannel(pSender, MsgChat::CHAT_TYPE_BATTLE);
// // 	SetChatOutTypeText( theXmlString.GetString(eChatType_ZhenYing) );
// // 	SetChatColor(Color_Config.getColor(CC_CHAT_ZHENYING));
// }

// Button
bool CUI_ChatInfoBox::ID_BUTTON_ChatPrivateOnButtonClick( ControlObject* pSender )
{
	return OnClickChannelButton();
}
// Button
bool CUI_ChatInfoBox::ID_BUTTON_BTeamOnButtonClick( ControlObject* pSender )
{
	return OnClickChannelButton();
}
// Button
bool CUI_ChatInfoBox::ID_BUTTON_BGuild1OnButtonClick( ControlObject* pSender )
{
	return OnClickChannelButton();
}
// Button
bool CUI_ChatInfoBox::ID_BUTTON_BCountryOnButtonClick( ControlObject* pSender )
{
	return OnClickChannelButton();
}
// Button
bool CUI_ChatInfoBox::ID_BUTTON_BHightShoutOnButtonClick( ControlObject* pSender )
{
	return OnClickChannelButton();
}

// Button
bool CUI_ChatInfoBox::ID_BUTTON_FamilyOnButtonClick( ControlObject* pSender )
{
	if ( !m_pChatInfoBox )
		return false;

	return OnClickChannelButton();
}

// CheckBox
void CUI_ChatInfoBox::ID_CHECKBOX_FamilyOnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if(!m_pChatInfoBox)
	{
		assert(false&&"ui error");
		return ;
	}
	ToggleChannel(pSender, MsgChat::CHAT_TYPE_FAMILY);
	SetChatOutTypeText( theXmlString.GetString(eChatType_CountryString) ); //***
	SetChatColor(Color_Config.getColor(CC_CHAT_FAMILY));

	SetChatOutTypeButton(pSender);

}

void CUI_ChatInfoBox::InitializeAtEnterWorld()
{
    if( !m_pChatInfoBox )
        return;
    m_channelRadioGroup.AddRadio(m_pID_CHECKBOX_BPublic);
    m_channelRadioGroup.AddRadio(m_pID_CHECKBOX_BTeam);
    m_channelRadioGroup.AddRadio(m_pID_CHECKBOX_BGuild1);
    m_channelRadioGroup.AddRadio(m_pID_CHECKBOX_BHightShout);
    m_channelRadioGroup.AddRadio(m_pID_CHECKBOX_BCountry);
	m_channelRadioGroup.AddRadio(m_pID_CHECKBOX_BGuanYuan);
    //m_channelRadioGroup.AddRadio(m_pID_CHECKBOX_BZhenying2);
    m_channelRadioGroup.AddRadio(m_pID_CHECKBOX_ChatPrivate);
    //m_channelRadioGroup.AddRadio(m_pID_CHECKBOX_BZhenying);
	m_channelRadioGroup.AddRadio(m_pID_CHECKBOX_Family);
    m_channelRadioGroup.SetVisible(true);
    m_channelRadioGroup.ToggleRadio(m_pID_CHECKBOX_BPublic);

    m_channelGroup.AddControl(m_pID_CHECKBOX_BPublic);
    m_channelGroup.AddControl(m_pID_CHECKBOX_BTeam);
    m_channelGroup.AddControl(m_pID_CHECKBOX_BGuild1);
    m_channelGroup.AddControl(m_pID_CHECKBOX_BHightShout);
    m_channelGroup.AddControl(m_pID_CHECKBOX_BCountry);
	m_channelGroup.AddControl(m_pID_CHECKBOX_BGuanYuan);
    //m_channelGroup.AddControl(m_pID_CHECKBOX_BZhenying2);
    m_channelGroup.AddControl(m_pID_CHECKBOX_ChatPrivate);
	m_channelGroup.AddControl(m_pID_CHECKBOX_Family);
    //m_channelGroup.AddControl(m_pID_CHECKBOX_BZhenying);
    m_channelGroup.SetVisible( false );
	m_pID_PICTURE_Di->SetVisable( false );

    m_receiveRadioGroup.SetVisible(false);

	

    if( !s_CUI_ID_FRAME_CREATE.GetImeInstance() )
        s_CUI_ID_FRAME_CREATE.SetImeInstance( ImmGetContext( g_hWnd ) );

    ImmReleaseContext( g_hWnd, s_CUI_ID_FRAME_CREATE.GetImeInstance()  );
    ImmAssociateContext(g_hWnd, NULL);
    ChangeImmPos();


	//--------------------------------------------------------------------------------
    InitialCommonChat(); 

    // 	if(m_pChatInfoText)
    // 	   m_pChatInfoText->SetHyberClickFun( HyberClickPrivateChat );


    m_pChatInfoText->SetMsgHoldup(true);
    SetChatOutTypeText( theXmlString.GetString(eChatType_Normal) );

    SetVisable(false);

    if (!isChatColdTimeXmlLoad)
    {
        loadXmlChatColdTime();
        isChatColdTimeXmlLoad = true;
    }

	LoadChatCommand();
}

// 装载UI
bool CUI_ChatInfoBox::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\ChatInfoBox.MEUI", true, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\ChatInfoBox.MEUI]失败")
			return false;
	}
// 	else if ( dwResult != 1/*文件版本号*/ )
// 	{
// 		MESSAGE_BOX("读取文件[Data\\UI\\ChatInfoBox.MEUI]与源代码版本不一样")
// 	}
	s_CUI_ID_FRAME_FACE.LoadUI();
// 	s_CUI_ID_FRAME_ActionList.LoadUI();
	s_CUI_ID_FRAME_chatInfoList.LoadUI();
	s_CUI_ID_FRAME_ChatSet.LoadUI();
	m_pChatInfoText = s_CUI_ID_FRAME_chatInfoList.GetpIDTextInfo();
	return DoControlConnect();
}
// 关连控件
bool CUI_ChatInfoBox::DoControlConnect()
{
	theUiManager.OnFrameRun( ChatInfoBox, s_CUI_ChatInfoBoxOnFrameRun );
	theUiManager.OnFrameRender( ChatInfoBox, s_CUI_ChatInfoBoxOnFrameRender );
	theUiManager.OnButtonClick( ChatInfoBox, ID_BUTTON_ChatOutType, s_CUI_ChatInfoBoxID_BUTTON_ChatOutTypeOnButtonClick );
	theUiManager.OnEditEnter( ChatInfoBox, ID_EDIT_INPUT, s_CUI_ChatInfoBoxID_EDIT_INPUTOnEditEnter );
	theUiManager.OnButtonClick( ChatInfoBox, ID_BUTTON_face, s_CUI_ChatInfoBoxID_BUTTON_faceOnButtonClick );
	theUiManager.OnButtonClick( ChatInfoBox, ID_BUTTON_PinBi, s_CUI_ChatInfoBoxID_BUTTON_PinBiOnButtonClick );
    theUiManager.OnButtonClick( ChatInfoBox, ID_BUTTON_Horn, s_CUI_ChatInfoBoxID_BUTTON_HornOnButtonClick );
	theUiManager.OnCheckBoxCheck( ChatInfoBox, ID_CHECKBOX_BPublic, s_CUI_ChatInfoBoxID_CHECKBOX_BPublicOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ChatInfoBox, ID_CHECKBOX_BTeam, s_CUI_ChatInfoBoxID_CHECKBOX_BTeamOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ChatInfoBox, ID_CHECKBOX_BGuild1, s_CUI_ChatInfoBoxID_CHECKBOX_BGuild1OnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ChatInfoBox, ID_CHECKBOX_BHightShout, s_CUI_ChatInfoBoxID_CHECKBOX_BHightShoutOnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ChatInfoBox, ID_CHECKBOX_BCountry, s_CUI_ChatInfoBoxID_CHECKBOX_BCountryOnCheckBoxCheck );
	//theUiManager.OnCheckBoxCheck( ChatInfoBox, ID_CHECKBOX_BZhenying2, s_CUI_ChatInfoBoxID_CHECKBOX_BZhenying2OnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ChatInfoBox, ID_CHECKBOX_ChatPrivate, s_CUI_ChatInfoBoxID_CHECKBOX_ChatPrivateOnCheckBoxCheck );
	theUiManager.OnButtonClick( ChatInfoBox, ID_BUTTON_Enter, s_CUI_ChatInfoBoxID_BUTTON_EnterOnButtonClick );
	//theUiManager.OnCheckBoxCheck( ChatInfoBox, ID_CHECKBOX_BZhenying, s_CUI_ChatInfoBoxID_CHECKBOX_BZhenyingOnCheckBoxCheck );
	theUiManager.OnButtonClick( ChatInfoBox, ID_BUTTON_ChatPrivate, s_CUI_ChatInfoBoxID_BUTTON_ChatPrivateOnButtonClick );
	theUiManager.OnButtonClick( ChatInfoBox, ID_BUTTON_BTeam, s_CUI_ChatInfoBoxID_BUTTON_BTeamOnButtonClick );
	theUiManager.OnButtonClick( ChatInfoBox, ID_BUTTON_BGuild1, s_CUI_ChatInfoBoxID_BUTTON_BGuild1OnButtonClick );
	theUiManager.OnButtonClick( ChatInfoBox, ID_BUTTON_BCountry, s_CUI_ChatInfoBoxID_BUTTON_BCountryOnButtonClick );
	theUiManager.OnButtonClick( ChatInfoBox, ID_BUTTON_BHightShout, s_CUI_ChatInfoBoxID_BUTTON_BHightShoutOnButtonClick );

	theUiManager.OnButtonClick( ChatInfoBox, ID_BUTTON_Family, s_CUI_ChatInfoBoxID_BUTTON_FamilyOnButtonClick );
	theUiManager.OnCheckBoxCheck( ChatInfoBox, ID_CHECKBOX_Family, s_CUI_ChatInfoBoxID_CHECKBOX_FamilyOnCheckBoxCheck );


	theUiManager.OnButtonClick( ChatInfoBox, ID_BUTTON_GuanYuan, s_CUI_ChatInfoBoxID_BUTTON_GuanYuanOnButtonClick );
	theUiManager.OnCheckBoxCheck( ChatInfoBox, ID_CHECKBOX_GuanYuan, s_CUI_ChatInfoBoxID_CHECKBOX_GuanYuanOnCheckBoxCheck );
	

	m_pChatInfoBox = (ControlFrame*)theUiManager.FindFrame( ChatInfoBox );
	m_pID_BUTTON_ChatOutType = (ControlButton*)theUiManager.FindControl( ChatInfoBox, ID_BUTTON_ChatOutType );
	m_pID_BUTTON_ChatPrivate = (ControlButton*)theUiManager.FindControl( ChatInfoBox, ID_BUTTON_ChatPrivate );
	m_pID_BUTTON_BTeam = (ControlButton*)theUiManager.FindControl( ChatInfoBox, ID_BUTTON_BTeam );
	m_pID_BUTTON_BGuild1 = (ControlButton*)theUiManager.FindControl( ChatInfoBox, ID_BUTTON_BGuild1 );
	m_pID_BUTTON_BCountry = (ControlButton*)theUiManager.FindControl( ChatInfoBox, ID_BUTTON_BCountry );
	m_pID_BUTTON_BHightShout = (ControlButton*)theUiManager.FindControl( ChatInfoBox, ID_BUTTON_BHightShout );
	m_pID_EDIT_INPUT = (ControlEdit*)theUiManager.FindControl( ChatInfoBox, ID_EDIT_INPUT );
	m_pID_BUTTON_face = (ControlButton*)theUiManager.FindControl( ChatInfoBox, ID_BUTTON_face );
	m_pID_BUTTON_PinBi = (ControlButton*)theUiManager.FindControl( ChatInfoBox, ID_BUTTON_PinBi );
    m_pID_BUTTON_Horn = (ControlButton*)theUiManager.FindControl( ChatInfoBox, ID_BUTTON_Horn );
	m_pID_CHECKBOX_BPublic = (ControlCheckBox*)theUiManager.FindControl( ChatInfoBox, ID_CHECKBOX_BPublic );
	m_pID_CHECKBOX_BTeam = (ControlCheckBox*)theUiManager.FindControl( ChatInfoBox, ID_CHECKBOX_BTeam );
	m_pID_CHECKBOX_BGuild1 = (ControlCheckBox*)theUiManager.FindControl( ChatInfoBox, ID_CHECKBOX_BGuild1 );
	m_pID_CHECKBOX_BHightShout = (ControlCheckBox*)theUiManager.FindControl( ChatInfoBox, ID_CHECKBOX_BHightShout );
	m_pID_CHECKBOX_BCountry = (ControlCheckBox*)theUiManager.FindControl( ChatInfoBox, ID_CHECKBOX_BCountry );
	//m_pID_CHECKBOX_BZhenying2 = (ControlCheckBox*)theUiManager.FindControl( ChatInfoBox, ID_CHECKBOX_BZhenying2 );
	m_pID_CHECKBOX_ChatPrivate = (ControlCheckBox*)theUiManager.FindControl( ChatInfoBox, ID_CHECKBOX_ChatPrivate );
	m_pID_BUTTON_Enter = (ControlButton*)theUiManager.FindControl( ChatInfoBox, ID_BUTTON_Enter );
	//m_pID_CHECKBOX_BZhenying = (ControlCheckBox*)theUiManager.FindControl( ChatInfoBox, ID_CHECKBOX_BZhenying );
	m_pID_PICTURE_Di = (ControlPicture*)theUiManager.FindControl( ChatInfoBox, ID_PICTURE_Di );

	m_pID_BUTTON_Family = (ControlButton*)theUiManager.FindControl( ChatInfoBox, ID_BUTTON_Family );
	m_pID_CHECKBOX_Family = (ControlCheckBox*)theUiManager.FindControl( ChatInfoBox, ID_CHECKBOX_Family );

	//lyh++
	m_pID_BUTTON_BGuanYuan = (ControlButton*)theUiManager.FindControl( ChatInfoBox, ID_BUTTON_GuanYuan );
	m_pID_CHECKBOX_BGuanYuan = (ControlCheckBox*)theUiManager.FindControl( ChatInfoBox, ID_CHECKBOX_GuanYuan );

	assert(m_pID_BUTTON_BGuanYuan);
	assert(m_pID_CHECKBOX_BGuanYuan);

	assert( m_pChatInfoBox );
	assert( m_pID_EDIT_INPUT );
	assert( m_pID_BUTTON_face );
	assert( m_pID_BUTTON_PinBi );
    assert( m_pID_BUTTON_Horn );
	assert( m_pID_CHECKBOX_BPublic );
	assert( m_pID_CHECKBOX_BTeam );
	assert( m_pID_CHECKBOX_BGuild1 );
	assert( m_pID_CHECKBOX_BHightShout );
	//assert( m_pID_CHECKBOX_BZhenying2 );
	assert( m_pID_BUTTON_Enter );
	assert( m_pID_BUTTON_ChatOutType );
	//assert( m_pID_CHECKBOX_BZhenying );
	assert( m_pID_PICTURE_Di );
	assert( m_pID_BUTTON_Family );
	assert( m_pID_CHECKBOX_Family );

	_SetVisable( false );
    return true;
}
// 卸载UI
bool CUI_ChatInfoBox::_UnLoadUI()
{
	m_chatInfos.clear();
	m_channelRadioGroup.Clear();
	m_receiveRadioGroup.Clear();
	m_channelGroup.Clear();
	s_CUI_ID_FRAME_ChatSet.UnLoadUI();
	s_CUI_ID_FRAME_chatInfoList.UnLoadUI();
	s_CUI_ID_FRAME_FACE.UnLoadUI();
	m_pChatInfoBox = NULL;
	m_pID_BUTTON_ChatOutType = NULL;
	m_pID_EDIT_INPUT = NULL;
	m_pID_BUTTON_face = NULL;
	m_pID_BUTTON_PinBi = NULL;
    m_pID_BUTTON_Horn = NULL;
	m_pID_CHECKBOX_BPublic = NULL;
	m_pID_CHECKBOX_BTeam = NULL;
	m_pID_CHECKBOX_BGuild1 = NULL;
	m_pID_CHECKBOX_BHightShout = NULL;
	m_pID_CHECKBOX_BCountry = NULL;
	m_pID_BUTTON_Family = NULL;
	m_pID_CHECKBOX_Family = NULL;
	//m_pID_CHECKBOX_BZhenying2 = NULL;
	m_pID_BUTTON_Enter = NULL;

		m_pID_CHECKBOX_BGuanYuan = NULL;
		m_pID_BUTTON_BGuanYuan = NULL;
	//m_pID_CHECKBOX_BZhenying = NULL;
	m_pChatInfoText = 0;
// 	s_CUI_ID_FRAME_ActionList.UnLoadUI();
	m_vecChatCommand.clear();
	return theUiManager.RemoveFrame( "Data\\UI\\ChatInfoBox.MEUI" );
}

bool CUI_ChatInfoBox::_IsVisable()
{
	if( !m_pChatInfoBox )
		return false;
	return m_pChatInfoBox->IsVisable();
}

void CUI_ChatInfoBox::_SetVisable( const bool bVisable )
{
	if( !m_pChatInfoBox )
		return;
	m_pChatInfoBox->SetVisable( bVisable );
}

void CUI_ChatInfoBox::SetChatChannelIndex( int nIndex )
{	
	m_nChatChannelIndex = nIndex;	
	SetChatType( 0xffffffff );
	ChatChannelConfig::ChatChannelInfoList cciList = ChatChannelConfig::Instance()->GetChatChannelList();
	if( m_nChatChannelIndex < cciList.size() )
	{
		SetChatType( cciList[m_nChatChannelIndex].m_dwChannelType );
	}
}
void CUI_ChatInfoBox::Refresh(int nStartIndex)
{
	if (!m_pChatInfoText || !m_pChatInfoText->IsVisable())
		return;

	m_pChatInfoText->Clear();
	_Refresh(nStartIndex);
	// 	if( m_pChatInfoText && m_pChatInfoText->GetListItemCnt() > 0 )
// 		m_pChatInfoText->SetCurSelIndex( m_pChatInfoText->GetListItemCnt() - 1 );
}

void CUI_ChatInfoBox::AddInfo( const std::string& str, const D3DCOLOR col, const UINT nType , char *szToName,
							  char* itemData, int cntHyber, int nBagType /*= 0*/, bool bAutoReply /*= false */, MsgChat* msg/* = NULL*/ )
{	
	guardfunc;

// 	if( !m_pChatInfoBox )
// 		return;

	int useHyberCnt = cntHyber;

	if( cntHyber > ITEM_HYBER_MAX_CNT )
	{
		useHyberCnt = 0;
	}
	guard(add_1);
	//*******************之前是右边和左边的合在一起注释掉********************
// 	if( nType == MsgChat::CHAT_TYPE_GAMEPROMPT)
// 	{
// 		int nIntroId = CIntroductionManager::Instance()->RetrieveIntroductionId(str);
// 		if (nIntroId == -1)
// 		{//现在把 系统消息另外提出一个出来 单独界面
// 			s_CUI_ID_FRAME_ChatSystem.AddInfo( str.c_str(), SYSTEM_COLOR, MsgChat::CHAT_TYPE_GAMEPROMPT, szToName, itemData, cntHyber, nBagType );
// 		}
// 		else
// 		{//新手引导
// 			CIntroductionManager::Instance()->ShowTip(nIntroId);
// 		}
// 		return;
// 	}
	//*******************之前是右边和左边的合在一起注释掉********************
// 	if( nType == MsgChat::CHAT_TYPE_BULL)
// 	{//现在把 系统消息另外提出一个出来 单独界面
// 		s_CUI_ID_FRAME_ChatSystem.AddInfo( str.c_str(), col );
// 		return;
// 	}

// 	if( nType == MsgChat::CHAT_TYPE_PROGRAM_SYSTEM )
// 	{
// 		s_CUI_ID_FRAME_ChatSystem.AddInfo( str.c_str(), col );
// 		return;
// 	}

	if (m_bAddChatInfo)
	{
		ChatInfo chatInfo;
		chatInfo.text = str;
	
		if (szToName)
			chatInfo.toName = szToName;
		chatInfo.color = col;
		chatInfo.nType = nType;
		chatInfo.nChatInfoIndex = m_nCurrChatInfoIndex++;
		chatInfo.cntHyber = useHyberCnt;
		chatInfo.nBagType = nBagType;
		if( nBagType == BT_MountBag )
			memcpy(chatInfo.mountItems, itemData, sizeof(SMountItem) * min( useHyberCnt, ITEM_HYBER_MAX_CNT ));
		else if(nBagType == BT_PetBag)
			memcpy(chatInfo.petItems,itemData,sizeof(SPetItem) * min( useHyberCnt, ITEM_HYBER_MAX_CNT ));
		else
			memcpy(chatInfo.normalItems, itemData, sizeof(SCharItem) * min( useHyberCnt, ITEM_HYBER_MAX_CNT ));
		m_chatInfos.push_back(chatInfo);
 		if (m_pChatInfoText && m_chatInfos.size() > 200)
 			m_chatInfos.pop_front();

        s_CUI_ID_FRAME_chatInfoList.SetChatListChanged();
	}
	
	// added, jiayi, [2009/11/19]
	/////////////////////////////////////////////////////
	/// 信息的过滤在这里，排除上面三种出现在右边的类型
	if( !( nType & m_dwChatType ) )
		return;
	/////////////////////////////////////////////////////
	
	int nConver = nType; 

	if (nConver == MsgChat::CHAT_TYPE_PRIVATE)
	{
		if( !str.empty() && m_bAddChatInfo )
		{
			std::wstring wstr = Common::_tstring::toWideString( str.c_str() );
			int nOff = wstr.find( Common::_tstring::toWideString( theXmlString.GetString(eClient_Chat_function_4) ) );
			int nOther = wstr.find( Common::_tstring::toWideString( theXmlString.GetString(eClient_Chat_NiDui) ) );
			int nBegin = Common::_tstring::toWideString( theXmlString.GetString(eText_Chat_0) ).length() ;
			if( nOff != -1 && nOff > 4 && nOther == -1)
			{
				if (s_CUI_ID_FRAME_ChatSet.IsAutoAck() && !bAutoReply )
				{
					MsgChat msg( MsgChat::CHAT_TYPE_PRIVATE );
					strncpy( msg.chatHeader.szToName, m_szPrivateToName.c_str(), MAX_NAME_STRING-1 );
					msg.bIsRreply = true;
					msg.SetString( s_CUI_ID_FRAME_ChatSet.GetAutoAckInfo() );

					GettheNetworkInput().SendMsg( &msg );
				}
			}
		}
	}
// 	switch ( nType )
// 	{
// 	case MsgChat::CHAT_TYPE_PROGRAM_SYSTEM:
// 		{
// 			nConver = CHAT_TYPE_PROGRAM_SYSTEM;
// 		}
// 		break;
// 	case MsgChat::CHAT_TYPE_BULL:
// 		{
// 			nConver = CHAT_TYPE_BULL;
// 		}
// 		break;
// 	case MsgChat::CHAT_TYPE_GAMEPROMPT :
// 		{
// 			nConver = CHAT_TYPE_GAMEPROMPT;
// 		}
// 		break;
// 	case MsgChat::CHAT_TYPE_NORMAL:	//普通频道
// 		{
// 			nConver = CHAT_TYPE_NORMAL;
// 		}
// 		break;
// 	case MsgChat::CHAT_TYPE_TERM:		//队伍频道
// 		{
// 			nConver = CHAT_TYPE_TERM;
// 		}
// 		break;
// 	case MsgChat::CHAT_TYPE_GUILD:	//公会频道
// 		{
// 			nConver = CHAT_TYPE_GUILD;
// 		}
// 		break;
// 	case MsgChat::CHAT_TYPE_LEAGUE:	//同盟频道
// 		{
// 			nConver = CHAT_TYPE_LEAGUE;
// 		}
// 		break;
// 	case MsgChat::CHAT_TYPE_PRIVATE:		//私聊频道
// 		{
// 			nConver = CHAT_TYPE_PRIVATE;
// 		}
// 		break;
// 	case MsgChat::CHAT_TYPE_HIGHSHOUT:
// 		{
// 
// 			nConver = CHAT_TYPE_HIGHSHOUT;
// 		}
// 		break;
// 	case MsgChat::CHAT_TYPE_BATTLE:	//同盟频道
// 		{
// 			nConver = CHAT_TYPE_BATTLE;
// 		}
// 		break;
// 	case MsgChat::CHAT_TYPE_COUNTRY:	//国家频道
// 		{
// 			nConver = CHAT_TYPE_COUNTRY;
// 		}
// 		break;
// 	case MsgChat::CHAT_TYPE_HIGHSHOUT_VIP:	//国家频道
// 		{
// 			nConver = CHAT_TYPE_HIGHSHOUT_VIP;
// 		}
// 		break;
// 	default:
// 		nConver = CHAT_TYPE_NORMAL;
// 		break;
// 	}

	unguard;

	guard(add_2);
	std::string localStr = str;
	ExpressionManager::GetInstance().AddExpressionAni(localStr,4);
	ShowTextInChatList( localStr,col,nConver,szToName,itemData,useHyberCnt, nBagType, msg );
	unguard;

	unguard;
}


void CUI_ChatInfoBox::Begin2Secret( const char* szStr)	//开始对某某某说悄悄话 szStr 为某某某的名字
{
	if( szStr)
		m_szPrivateToName = szStr;

	_nDefaultChannel = MsgChat::CHAT_TYPE_PRIVATE;

	m_channelRadioGroup.ToggleRadio(m_pID_CHECKBOX_ChatPrivate);

	SetChatOutTypeText( theXmlString.GetString(eChatType_Private) );
	m_pID_EDIT_INPUT->SetActivate( true );	
	m_pChatInfoBox->SetVisable(true);

	SetChatTypeChannel(CHAT_PRIVATE);
	if (strlen(szStr) > 0)
	{
		char szTemp[128] = {0};
		MeSprintf_s( szTemp, sizeof(szTemp)-1, "%s ", szStr);
		SetInputText(szTemp);
	}
	else
		SetInputText("");

	theUiManager.ToTop(m_pChatInfoBox);
	theUiManager.Compositor();
	SetEditFocus();

	ImmAssociateContext( g_hWnd, s_CUI_ID_FRAME_CREATE.GetImeInstance() );
	ChangeImmPos();
	m_channelGroup.SetVisible( false );
	m_pID_PICTURE_Di->SetVisable( false );

	SetChatColor(Color_Config.getColor(CC_CHAT_PERSONAL));
}
void CUI_ChatInfoBox::r_ShortcutPrivate()
{
	if( !m_szPrivateToName.empty() )
	{
		if (!theUiManager.GetFocus() || theUiManager.GetFocus()->GetControlType() != Type_Edit )
			Begin2Secret( m_szPrivateToName.c_str() );
	}
}

void CUI_ChatInfoBox::AddPrivateUser(const char *szUser)
{
	SetPrivateName(szUser);

// 	bool  bIsRepeat = false;
// 	for(vector<string>::iterator i = m_lstPrivateName.begin(); i != m_lstPrivateName.end(); ++i)
// 	{
// 		if(szUser == *i)
// 			bIsRepeat = true;
// 	}
// 
// 	if( !bIsRepeat)
// 	{//如果没有重复的
// 		if(m_lstPrivateName.size() < LAST_INFO_MAX)
// 		{
// 			m_lstPrivateName.push_back(szUser);
// 		}
// 		else
// 		{
// 			//m_lstPrivateName.pop_front();
// 			for(int i=0; i<m_lstPrivateName.size()-1; ++i)
// 			{
// 				m_lstPrivateName[i] = m_lstPrivateName[i+1];
// 			}
// 			m_lstPrivateName.pop_back();
// 			m_lstPrivateName.push_back(szUser);
// 		}
// 	}
// 
// 	for(vector<string>::iterator i = m_lstPrivateName.begin(); i != m_lstPrivateName.end(); ++i)
// 	{
// 		ControlList::S_List	stItem;
// 		stItem.SetData( (*i).c_str() );
// 	}
}
bool CUI_ChatInfoBox::MsgProc( UINT msg, WPARAM wParam, LPARAM lParam, bool bMsgUsed ,ControlObject* pSender)
{
	if ( (bMsgUsed == true && WM_MOUSEMOVE != msg) || g_GameState != G_MAIN )
		return false;	

	if( CommonChatFrame::MsgProc( msg, wParam, lParam, bMsgUsed, pSender ) )
		return true;

	switch( msg ) 
	{
	case WM_CHAR:
		{
			if (wParam == VK_TAB)
			{
				if ( theUiManager.GetFocus() == m_pID_EDIT_INPUT )
				{
					ToggleNext();
				}
			}
		}
		break;
	}
	return false;
}
void CUI_ChatInfoBox::LoadChatCommand()
{
	m_vecChatCommand.clear();

	if( ChatChannelConfig::Instance()->LoadCommandConfig() )
	{
		ChatChannelConfig::ChatCommandInfo vecCommandInfo = ChatChannelConfig::Instance()->GetChatCommandInfo();
		for( int i=0; i<vecCommandInfo.size(); ++i )
		{
			ChatCommand kChatCommand;
			bool bGetType = false;
			// 不区分大小写
			if( !stricmp(vecCommandInfo[i].strType.c_str(), "normal") )
			{
				kChatCommand.iChatType = MsgChat::CHAT_TYPE_NORMAL;
				bGetType = true;
			}
			else if( !stricmp(vecCommandInfo[i].strType.c_str(), "guild") )
			{
				kChatCommand.iChatType = MsgChat::CHAT_TYPE_GUILD;
				bGetType = true;
			}
			else if( !stricmp(vecCommandInfo[i].strType.c_str(), "league") )
			{
				kChatCommand.iChatType = MsgChat::CHAT_TYPE_LEAGUE;
				bGetType = true;
			}
			else if( !stricmp(vecCommandInfo[i].strType.c_str(), "team") )
			{
				kChatCommand.iChatType = MsgChat::CHAT_TYPE_TERM;
				bGetType = true;
			}
			else if( !stricmp(vecCommandInfo[i].strType.c_str(), "highshout") )
			{
				kChatCommand.iChatType = MsgChat::CHAT_TYPE_HIGHSHOUT;
				bGetType = true;
			}
			else if( !stricmp(vecCommandInfo[i].strType.c_str(), "private") )
			{
				kChatCommand.iChatType = MsgChat::CHAT_TYPE_PRIVATE;
				bGetType = true;
			}
			else if( !stricmp(vecCommandInfo[i].strType.c_str(), "zhenying") )
			{
				kChatCommand.iChatType = MsgChat::CHAT_TYPE_BATTLE;
				bGetType = true;
			}
			else if( !stricmp(vecCommandInfo[i].strType.c_str(), "country") )
			{
				kChatCommand.iChatType = MsgChat::CHAT_TYPE_COUNTRY;
				bGetType = true;
			}
			else if ( !stricmp( vecCommandInfo[i].strType.c_str(), "family" ) )
			{
				kChatCommand.iChatType = MsgChat::CHAT_TYPE_FAMILY;
				bGetType = true;
			}
			else if ( !stricmp( vecCommandInfo[i].strType.c_str(), "GY" ) ) //官员
			{
				kChatCommand.iChatType = MsgChat::CHAT_TYPE_COUNTRYOFFICIAL;
				bGetType = true;
			}


			if( bGetType )
			{
				if( vecCommandInfo[i].strCommandCn.length() > 0 )
				{
					kChatCommand.strCommandCn = vecCommandInfo[i].strCommandCn;
				}
				else
				{
					kChatCommand.strCommandCn = "";
				}

				if( vecCommandInfo[i].strCommandEn.length() > 0 )
				{
					kChatCommand.strCommandEn = vecCommandInfo[i].strCommandEn;
				}
				else
				{
					kChatCommand.strCommandEn = "";
				}
				m_vecChatCommand.push_back(kChatCommand);
			}
		}
	}
}

static bool CompareCommand(std::string& strMessage, const std::string& strCommand)
{
	int nPos = strMessage.find(strCommand);
	if( nPos != std::string::npos && nPos == 0 )
	{
		std::string strTemp = strMessage;
		strMessage = strTemp.substr(strCommand.length(), strTemp.length() - strCommand.length());
		return true;
	}
	return false;
}

#define CHAT_SPACE " "
#define CHAT_FULL_SPACE "　"
void CUI_ChatInfoBox::ProcessAndSendChatMessage(int nDefaultChannel, const char* szData)
{
	if( !szData || szData[0] == '\0' )
		return;

	bool bFind = false;
	std::string strChatMessage = szData;
	if( szData[0] == '/' )
	{
		for( int i=0; i<m_vecChatCommand.size(); ++i )
		{
			if( m_vecChatCommand[i].strCommandCn.length() > 0 )
			{
				// 判断命令行
				if( strChatMessage == m_vecChatCommand[i].strCommandCn )
				{
					bFind = true;
					strChatMessage = "";
					nDefaultChannel = m_vecChatCommand[i].iChatType;
					break;
				}
				else
				{
					// 判断命令行+半角空格
					std::string command = m_vecChatCommand[i].strCommandCn;
					command += CHAT_SPACE;
					bFind = CompareCommand(strChatMessage, command);
					if( bFind )
					{
						nDefaultChannel = m_vecChatCommand[i].iChatType;
						break;
					}

					// 判断命令行+全角空格
					command = m_vecChatCommand[i].strCommandCn;
					command += CHAT_FULL_SPACE;
					bFind = CompareCommand(strChatMessage, command);
					if( bFind )
					{
						nDefaultChannel = m_vecChatCommand[i].iChatType;
						break;
					}
				}
			}

			if( m_vecChatCommand[i].strCommandEn.length() > 0 )
			{
				// 判断命令行
				if( strChatMessage == m_vecChatCommand[i].strCommandEn )
				{
					bFind = true;
					strChatMessage = "";
					nDefaultChannel = m_vecChatCommand[i].iChatType;
					break;
				}
				else
				{
					// 判断命令行+半角空格
					std::string command = m_vecChatCommand[i].strCommandEn;
					command += CHAT_SPACE;
					bFind = CompareCommand(strChatMessage, command);
					if( bFind )
					{
						nDefaultChannel = m_vecChatCommand[i].iChatType;
						break;
					}

					// 判断命令行+全角空格
					command = m_vecChatCommand[i].strCommandEn;
					command += CHAT_FULL_SPACE;
					bFind = CompareCommand(strChatMessage, command);
					if( bFind )
					{
						nDefaultChannel = m_vecChatCommand[i].iChatType;
						break;
					}
				}
			}
		}
	}
	if( bFind )
	{
		_nDefaultChannel = nDefaultChannel;

		ControlCheckBox*	pSender = NULL;
		switch( _nDefaultChannel )
		{
		case MsgChat::CHAT_TYPE_NORMAL:
			pSender = m_pID_CHECKBOX_BPublic;
			SetChatColor(Color_Config.getColor(CC_CHAT_NORMAL));
			break;
		case MsgChat::CHAT_TYPE_GUILD:
			pSender = m_pID_CHECKBOX_BGuild1;
			SetChatColor(Color_Config.getColor(CC_CHAT_GUILD));
			break;
		case MsgChat::CHAT_TYPE_TERM:
			pSender = m_pID_CHECKBOX_BTeam;
			SetChatColor(Color_Config.getColor(CC_CHAT_TEAM));
			break;
		case MsgChat::CHAT_TYPE_PRIVATE:
			pSender = m_pID_CHECKBOX_ChatPrivate;
			SetChatColor(Color_Config.getColor(CC_CHAT_PERSONAL));
			break;
		case MsgChat::CHAT_TYPE_HIGHSHOUT:
			pSender = m_pID_CHECKBOX_BHightShout;
			SetChatColor(Color_Config.getColor(CC_CHAT_HIGHSHOUT));
			break;
		//case MsgChat::CHAT_TYPE_LEAGUE:
		//	pSender = m_pID_CHECKBOX_BZhenying2;
		//	SetChatColor(Color_Config.getColor(CC_CHAT_LEAGUE));
		//	break;
		//case MsgChat::CHAT_TYPE_BATTLE:
		//	pSender = m_pID_CHECKBOX_BZhenying;
		//	SetChatColor(Color_Config.getColor(CC_CHAT_ZHENYING));
		//	break;
		case MsgChat::CHAT_TYPE_COUNTRY:
			pSender = m_pID_CHECKBOX_BCountry;
			SetChatColor(Color_Config.getColor(CC_CHAT_COUNTRY));
			break;
		case MsgChat::CHAT_TYPE_FAMILY:
			pSender = m_pID_CHECKBOX_Family;
			SetChatColor(Color_Config.getColor(CC_CHAT_FAMILY));
			break;
		case MsgChat::CHAT_TYPE_COUNTRYOFFICIAL:
			pSender = m_pID_CHECKBOX_BGuanYuan;
			SetChatColor(Color_Config.getColor(CC_Chat_ChatGuanYuan));
			break;
		default:
			break;
		}
		if( pSender )
		{
			m_channelRadioGroup.ToggleRadio(pSender);
			SetChatOutTypeButton(pSender);
		}	
		m_channelRadioGroup.SetVisible(false);
	}
	SendChatMessage(nDefaultChannel,strChatMessage.c_str());
}

void CUI_ChatInfoBox::SetChatColor( D3DCOLOR color )
{
	m_pID_EDIT_INPUT->setDefaultColor(color);
	m_pID_EDIT_INPUT->GetData()->m_colFont = color;
}

void CUI_ChatInfoBox::_Refresh(int nStartIndex)
{
	m_bAddChatInfo = false;

	std::list<ChatInfo>::iterator it, end = m_chatInfos.end();
	for (it = m_chatInfos.begin(); it != end; ++it)
	{
		ChatInfo& info = *it;
		if (info.nChatInfoIndex < nStartIndex)
		{
			continue;
		}
		if( info.nBagType == BT_MountBag )
			AddInfo(info.text, info.color, info.nType, const_cast<char*>(info.toName.c_str()), (char*)info.mountItems, info.cntHyber, BT_MountBag);
		else if(info.nBagType == BT_PetBag )
			AddInfo(info.text,info.color, info.nType, const_cast<char*>(info.toName.c_str()),(char*)info.petItems,info.cntHyber,BT_PetBag);
		else
			AddInfo(info.text, info.color, info.nType, const_cast<char*>(info.toName.c_str()), (char*)info.normalItems, info.cntHyber);
	}
	m_bAddChatInfo = true;
}

bool CommonChatFrame::CommandChat(const char *szCommand)
{
	guardfunc;
	if(szCommand == NULL)
		return false;
	if(szCommand[0] == 0)
		return false;

	WordParser words;
	if( words.Parse( szCommand ) == 0 )
		return FALSE;
	if( words.Compare(0, "help") )
	{
		for( int i=0; i<m_vecHelpInfo.size(); ++i)
		{
			ShowTextInChatList( m_vecHelpInfo[i].c_str() );
		}
	}
	else if( words.Compare(0, "sh") && words.GetWordCount() >= 2)
	{
		if( thePlayerRole.GetLevel() < _iHighShoutLevel )
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Chat_ChannelTip, theXmlString.GetString( eText_CannotShout_LevelNotMatch ) );
			m_pID_EDIT_INPUT->SetActivate( false );
			s_CUI_ID_FRAME_FACE.SetVisable( false );
			ImmAssociateContext( g_hWnd, NULL );
			return false;
		}
		SCharBaseInfo *pCharBaseInfo = &thePlayerRole.m_charinfo.baseinfo;
		uint16 nCountryTitle = pCharBaseInfo->liveinfo.nCountryTitle;
		//if(CountryDefine::Right_None == CountryDefine::GetCountryRightByTitle(nCountryTitle))
		//{
		//	DWORD dwMoney = thePlayerRole.GetData( CPlayerRole::TYPE_MONEY );
		//	DWORD dwJiaoZi = thePlayerRole.GetData( CPlayerRole::TYPE_JiaoZi );
		//	if (dwMoney + dwJiaoZi< 100)//少于一个银币不能世界喊话
		//	{
		//		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Chat_ChannelTip, theXmlString.GetString( eText_NoMoneyForWorldChat ) );
		//		m_pID_EDIT_INPUT->SetActivate( false );
		//		s_CUI_ID_FRAME_FACE.SetVisable( false );
		//		ImmAssociateContext( g_hWnd, NULL );
		//		return false;
		//	}
		//}
		std::string szStr = szCommand;
		int nLen = strlen(szCommand);
		std::string szNewCommand = szStr.substr( 1 + 2, nLen - 3);

		std::string strChat = szNewCommand.c_str();
		//strChat = CChatCheck::getInstance()->CheckStringInLowMark((char*)szNewCommand.c_str(), '*');

		clock_t tmNow = clock();
		//if( tmNow - _tmHighShoutLastTime < _tmHighShoutColdTime)
		//{
		//	AddInfo( _strHighShoutError.c_str() );
		//	return false;
		//}
		_tmHighShoutLastTime = tmNow;

		MsgChat msg( MsgChat::CHAT_TYPE_HIGHSHOUT);
		strncpy( msg.chatHeader.szToName, thePlayerRole.GetName(), MAX_NAME_STRING - 1);
		if( ItemHyberCnt <= ITEM_HYBER_MAX_CNT && ItemHyberCnt > 0)
		{
			msg.nHyberItemCnt = ItemHyberCnt;

			for( int i=0; i<ItemHyberCnt; ++i )
			{
				msg.ehyberType[i] = _HyberType[i];
				msg.onlyId[i] = _HyberItemInfo[i];
				msg.itemId[i] = _HyberItemId[i];
				msg.type = _nBagType;
			}
		}
		msg.SetString( strChat.c_str() );

		GettheNetworkInput().SendMsg( &msg );
	}
	if( words.Compare(0, "h") && words.GetWordCount() >= 2)
	{
		std::string szStr = szCommand;
		int nLen = strlen(szCommand);
		std::string szNewCommand = szStr.substr( 1 + 1, nLen - 2);

		std::string strChat = szNewCommand.c_str();
		//strChat = CChatCheck::getInstance()->CheckStringInLowMark((char*)szNewCommand.c_str(), '*');

		clock_t tmNow = clock();
		//if( tmNow - _tmShoutLastTime < _tmShoutColdTime)
		//{
		//	AddInfo( _strShoutError.c_str() );
		//	return false;
		//}
		_tmShoutLastTime = tmNow;

		MsgChat msg( MsgChat::CHAT_TYPE_SHOUT );
		strncpy( msg.chatHeader.szToName, thePlayerRole.GetName(), MAX_NAME_STRING-1 );
		if( ItemHyberCnt <= ITEM_HYBER_MAX_CNT && ItemHyberCnt > 0)
		{
			msg.nHyberItemCnt = ItemHyberCnt;

			for( int i=0; i<ItemHyberCnt; ++i )
			{
				msg.onlyId[i] = _HyberItemInfo[i];
				msg.itemId[i] = _HyberItemId[i];
				msg.type = _nBagType;
			}
		}
		msg.SetString( strChat.c_str() );

		GettheNetworkInput().SendMsg( &msg );
		//}
	}
	if( words.Compare(0, "w") && words.GetWordCount() >= 3)
	{
		if( thePlayerRole.GetLevel() < _iPrivateLevel )
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Chat_ChannelTip, theXmlString.GetString( eWarning_CanNotPrivateChatBefore15 ) );
			m_pID_EDIT_INPUT->SetActivate( false );
			s_CUI_ID_FRAME_FACE.SetVisable( false );
			ImmAssociateContext( g_hWnd, NULL );
			return false;
		}
		std::wstring wstrChat = Common::_tstring::toWideString(szCommand);
		size_t nameStartPos = wstrChat.find(L' ') + 1;
		size_t contentStartPos = wstrChat.find(L' ', nameStartPos) + 1;

		std::wstring wstrName = wstrChat.substr(nameStartPos, contentStartPos - nameStartPos - 1);
		std::wstring wstrContent = wstrChat.substr(contentStartPos);

		std::string strName = Common::_tstring::toNarrowString(wstrName.c_str());
		std::string strContent = Common::_tstring::toNarrowString(wstrContent.c_str());

		s_CUI_ChatInfoBox.SetCurrentChannel(MsgChat::CHAT_TYPE_PRIVATE);
		SetPrivateName( strName.c_str() );

		//Lua_SendMsgChat( MsgChat::CHAT_TYPE_PRIVATE, szNewCommand );

		//-- 这里判断自己不能和自己聊天
		if(strcmp(m_szPrivateToName.c_str(), thePlayerRole.GetName()) == 0)
		{
			//AddInfo( theXmlString.GetString(eClient_AddInfo_2slk_7) );
			return true;
		}
		//--

 		clock_t tmNow = clock();
// 		if( tmNow - _tmPrivateLastTime < _tmPrivateColdTime)
// 		{
// 			AddInfo( _strPrivateError.c_str() );
// 			return false;
// 		}
// 
 		_tmPrivateLastTime = tmNow;

		MsgChat msg( MsgChat::CHAT_TYPE_PRIVATE );
		strncpy( msg.chatHeader.szToName, m_szPrivateToName.c_str(), MAX_NAME_STRING-1 );
		if( ItemHyberCnt <= ITEM_HYBER_MAX_CNT && ItemHyberCnt > 0)
		{
			msg.nHyberItemCnt = ItemHyberCnt;

			for( int i=0; i<ItemHyberCnt; ++i )
			{
				msg.onlyId[i] = _HyberItemInfo[i];
				msg.itemId[i] = _HyberItemId[i];
				msg.type = _nBagType;
			}
		}
		msg.SetString( strContent.c_str() );

		GettheNetworkInput().SendMsg( &msg );
	}
	if( words.Compare(0, "ms") && words.GetWordCount() >= 3)
	{
		if( thePlayerRole.GetLevel() < _iMessageLevel )
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Chat_ChannelTip, theXmlString.GetString( eWarning_CanNotMessageChatBefore15 ) );
			m_pID_EDIT_INPUT->SetActivate( false );
			s_CUI_ID_FRAME_FACE.SetVisable( false );
			ImmAssociateContext( g_hWnd, NULL );
			return false;
		}
		std::wstring wstrChat = Common::_tstring::toWideString(szCommand);
		size_t nameStartPos = wstrChat.find(L' ') + 1;
		size_t contentStartPos = wstrChat.find(L' ', nameStartPos) + 1;

		std::wstring wstrName = wstrChat.substr(nameStartPos, contentStartPos - nameStartPos - 1);
		std::wstring wstrContent = wstrChat.substr(contentStartPos);

		std::string strName = Common::_tstring::toNarrowString(wstrName.c_str());
		std::string strContent = Common::_tstring::toNarrowString(wstrContent.c_str());

		//Lua_SendMsgChat( MsgChat::CHAT_TYPE_PRIVATE, szNewCommand );

		//-- 这里判断自己不能和自己聊天
		if(strcmp(m_szPrivateToName.c_str(), thePlayerRole.GetName()) == 0)
		{
			//AddInfo( theXmlString.GetString(eClient_AddInfo_2slk_7) );
			return true;
		}
		//--

 		clock_t tmNow = clock();
// 		if( tmNow - _tmPrivateLastTime < _tmPrivateColdTime)
// 		{
// 			AddInfo( _strPrivateError.c_str() );
// 			return false;
// 		}
// 
		_tmMessageLastTime = tmNow;

		MsgChat msg( MsgChat::CHAT_TYPE_MS );
		strncpy( msg.chatHeader.szToName, strName.c_str(), MAX_NAME_STRING-1 );
		if( ItemHyberCnt <= ITEM_HYBER_MAX_CNT && ItemHyberCnt > 0)
		{
			msg.nHyberItemCnt = ItemHyberCnt;

			for( int i=0; i<ItemHyberCnt; ++i )
			{
				msg.onlyId[i] = _HyberItemInfo[i];
				msg.itemId[i] = _HyberItemId[i];
				msg.type = _nBagType;
			}
		}
		msg.SetString( strContent.c_str() );

		GettheNetworkInput().SendMsg( &msg );
	}
	else if(words.Compare(0, "g") && words.GetWordCount() >= 2)
	{
		s_CUI_ChatInfoBox.SetCurrentChannel(MsgChat::CHAT_TYPE_GUILD);
		std::string szStr = szCommand;
		int nLen = strlen(szCommand);
		std::string szNewCommand = szStr.substr( 1 + 1, nLen - 2);

		std::string strChat = szNewCommand.c_str();
		//strChat = CChatCheck::getInstance()->CheckStringInLowMark((char*)szNewCommand.c_str(), '*');

 		clock_t tmNow = clock();
// 		if( tmNow - _tmGuildLastTime < _tmGuildLastTime)
// 		{
// 			AddInfo( _strGuildError.c_str() );
// 			return false;
// 		}
// 
 		_tmGuildLastTime = tmNow;

		MsgChat msg( MsgChat::CHAT_TYPE_GUILD );	
		strncpy( msg.chatHeader.szToName, thePlayerRole.GetName(), MAX_NAME_STRING-1 );
		if( ItemHyberCnt <= ITEM_HYBER_MAX_CNT && ItemHyberCnt > 0)
		{
			msg.nHyberItemCnt = ItemHyberCnt;

			for( int i=0; i<ItemHyberCnt; ++i )
			{
				msg.onlyId[i] = _HyberItemInfo[i];
				msg.itemId[i] = _HyberItemId[i];
				msg.type = _nBagType;
			}
		}
		msg.SetString( strChat.c_str() );

		GettheNetworkInput().SendMsg( &msg );
	}
	else if(words.Compare(0, "l") && words.GetWordCount() >= 2)
	{
		s_CUI_ChatInfoBox.SetCurrentChannel(MsgChat::CHAT_TYPE_LEAGUE);
		std::string szStr = szCommand;
		int nLen = strlen(szCommand);
		std::string szNewCommand = szStr.substr( 1 + 1, nLen - 2);

		std::string strChat = szNewCommand.c_str();
		//strChat = CChatCheck::getInstance()->CheckStringInLowMark((char*)szNewCommand.c_str(), '*');

 		clock_t tmNow = clock();
// 		if( tmNow - _tmGuildLastTime < _tmGuildLastTime)
// 		{
// 			AddInfo( _strGuildError.c_str() );
// 			return false;
// 		}
// 
 		_tmLeagueLastTime = tmNow;

		MsgChat msg( MsgChat::CHAT_TYPE_LEAGUE );	
		strncpy( msg.chatHeader.szToName, thePlayerRole.GetName(), MAX_NAME_STRING-1 );
		if( ItemHyberCnt <= ITEM_HYBER_MAX_CNT && ItemHyberCnt > 0)
		{
			msg.nHyberItemCnt = ItemHyberCnt;

			for( int i=0; i<ItemHyberCnt; ++i )
			{
				msg.onlyId[i] = _HyberItemInfo[i];
				msg.itemId[i] = _HyberItemId[i];
				msg.type = _nBagType;
			}
		}
		msg.SetString( strChat.c_str() );

		GettheNetworkInput().SendMsg( &msg );
	}
	else if(words.Compare(0, "p") && words.GetWordCount() >= 2)
	{
		s_CUI_ChatInfoBox.SetCurrentChannel(MsgChat::CHAT_TYPE_TERM);
		std::string szStr = szCommand;
		int nLen = strlen(szCommand);
		std::string szNewCommand = szStr.substr( 1 + 1, nLen - 2);
		//Lua_SendMsgChat( MsgChat::CHAT_TYPE_TERM, szNewCommand );

		std::string strChat = szNewCommand.c_str();
		//strChat = CChatCheck::getInstance()->CheckStringInLowMark((char*)szNewCommand.c_str(), '*');

 		clock_t tmNow = clock();
// 		if( tmNow - _tmGuildLastTime < _tmGuildColdTime)
// 		{
// 			AddInfo( _strTeamError.c_str() );
// 			return false;
// 		}
// 
 		_tmTeamLastTime = tmNow;

		if( thePlayerRole.GetTeamMemberNum() == 0 )
		{
			//s_CUI_ChatInfoBox.AddInfo( theXmlString.GetString(eText_Server_Chat_noTeam) );
			return false;
		}

		MsgChat msg( MsgChat::CHAT_TYPE_TERM );
		strncpy( msg.chatHeader.szToName, thePlayerRole.GetName(), MAX_NAME_STRING-1 );

		if( ItemHyberCnt <= ITEM_HYBER_MAX_CNT && ItemHyberCnt > 0)
		{
			msg.nHyberItemCnt = ItemHyberCnt;

			for( int i=0; i<ItemHyberCnt; ++i )
			{
				msg.onlyId[i] = _HyberItemInfo[i];
				msg.itemId[i] = _HyberItemId[i];
				msg.type = _nBagType;
			}
		}
		msg.SetString( strChat.c_str() );

		GettheNetworkInput().SendMsg( &msg );
	}
	else if(words.Compare(0, "b") && words.GetWordCount() >= 2)
	{
		s_CUI_ChatInfoBox.SetCurrentChannel(MsgChat::CHAT_TYPE_BATTLE);
		std::string szStr = szCommand;
		int nLen = strlen(szCommand);
		std::string szNewCommand = szStr.substr( 1 + 1, nLen - 2);

		std::string strChat = szNewCommand.c_str();
		//strChat = CChatCheck::getInstance()->CheckStringInLowMark((char*)szNewCommand.c_str(), '*');

		clock_t tmNow = clock();
		// 		if( tmNow - _tmGuildLastTime < _tmGuildLastTime)
		// 		{
		// 			AddInfo( _strGuildError.c_str() );
		// 			return false;
		// 		}
		// 
		_tmLeagueLastTime = tmNow;

		MsgChat msg( MsgChat::CHAT_TYPE_BATTLE );	
		strncpy( msg.chatHeader.szToName, thePlayerRole.GetName(), MAX_NAME_STRING-1 );
		if( ItemHyberCnt <= ITEM_HYBER_MAX_CNT && ItemHyberCnt > 0)
		{
			msg.nHyberItemCnt = ItemHyberCnt;

			for( int i=0; i<ItemHyberCnt; ++i )
			{
				msg.onlyId[i] = _HyberItemInfo[i];
				msg.itemId[i] = _HyberItemId[i];
				msg.type = _nBagType;
			}
		}
		msg.SetString( strChat.c_str() );

		GettheNetworkInput().SendMsg( &msg );
	}
	else if(words.Compare(0, "c") && words.GetWordCount() >= 2)
	{
		if( thePlayerRole.GetLevel() < _iCountryLevel )
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Chat_ChannelTip, theXmlString.GetString( eWarning_CanNotCountryChatBefore20 ) );
			m_pID_EDIT_INPUT->SetActivate( false );
			s_CUI_ID_FRAME_FACE.SetVisable( false );
			ImmAssociateContext( g_hWnd, NULL );
			return false;
		}
	//lyh++ 没有国家的人不能使用国家频道进行聊天
			if (thePlayerRole.GetCountry() == 0)
			{
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Chat_ChannelTip, theXmlString.GetString( eWarning_CanNotCountryChatNoCountry ) );
				m_pID_EDIT_INPUT->SetActivate( false );
				s_CUI_ID_FRAME_FACE.SetVisable( false );
				ImmAssociateContext( g_hWnd, NULL );
				return false;
			}


		s_CUI_ChatInfoBox.SetCurrentChannel(MsgChat::CHAT_TYPE_COUNTRY);
		std::string szStr = szCommand;
		int nLen = strlen(szCommand);
		std::string szNewCommand = szStr.substr( 1 + 1, nLen - 2);

		std::string strChat = szNewCommand.c_str();

		clock_t tmNow = clock();
		_tmCountryLastTime = tmNow;

		MsgChat msg( MsgChat::CHAT_TYPE_COUNTRY );	
		strncpy( msg.chatHeader.szToName, thePlayerRole.GetName(), MAX_NAME_STRING-1 );
		if( ItemHyberCnt <= ITEM_HYBER_MAX_CNT && ItemHyberCnt > 0)
		{
			msg.nHyberItemCnt = ItemHyberCnt;

			for( int i=0; i<ItemHyberCnt; ++i )
			{
				msg.onlyId[i] = _HyberItemInfo[i];
				msg.itemId[i] = _HyberItemId[i];
				msg.type = _nBagType;
			}
		}
		msg.SetString( strChat.c_str() );

		GettheNetworkInput().SendMsg( &msg );
	} //lyh++ 官员聊天频道
	else if(words.Compare(0, "y") && words.GetWordCount() >= 2)
	{
		if( thePlayerRole.GetLevel() < _iCountryLevel )
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Chat_ChannelTip, theXmlString.GetString( eWarning_CanNotCountryChatBefore20 ) );
			m_pID_EDIT_INPUT->SetActivate( false );
			s_CUI_ID_FRAME_FACE.SetVisable( false );
			ImmAssociateContext( g_hWnd, NULL );
			return false;
		}
		//lyh++ 没有国家的人不能使用国家频道进行聊天
		if (thePlayerRole.GetCountry() == 0)
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Chat_ChannelTip, theXmlString.GetString( eWarning_CanNotCountryChatNoCountry ) );
			m_pID_EDIT_INPUT->SetActivate( false );
			s_CUI_ID_FRAME_FACE.SetVisable( false );
			ImmAssociateContext( g_hWnd, NULL );
			return false;
		}

		//if (thePlayerRole.getco() == 0) //获取玩家 国家职位
		//{
		//	CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Chat_ChannelTip, theXmlString.GetString( eWarning_CanNotCountryChatNoCountry ) );
		//	m_pID_EDIT_INPUT->SetActivate( false );
		//	s_CUI_ID_FRAME_FACE.SetVisable( false );
		//	ImmAssociateContext( g_hWnd, NULL );
		//	return false;
		//}
		if(thePlayerRole.GetCharInfo2().baseinfo.liveinfo.uchPosition <= CountryDefine::Position_None ||
			thePlayerRole.GetCharInfo2().baseinfo.liveinfo.uchPosition>= CountryDefine::Position_Max)
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Chat_ChannelTip, theXmlString.GetString( eWarning_CanNotCountryGYChat ) );
			m_pID_EDIT_INPUT->SetActivate( false );
			s_CUI_ID_FRAME_FACE.SetVisable( false );
			ImmAssociateContext( g_hWnd, NULL );

			return false;
		}
		


		s_CUI_ChatInfoBox.SetCurrentChannel(MsgChat::CHAT_TYPE_COUNTRYOFFICIAL);
		std::string szStr = szCommand;
		int nLen = strlen(szCommand);
		std::string szNewCommand = szStr.substr( 1 + 1, nLen - 2);

		std::string strChat = szNewCommand.c_str();

		clock_t tmNow = clock();
		_tmCountryLastTime = tmNow;

		MsgChat msg( MsgChat::CHAT_TYPE_COUNTRYOFFICIAL );	
		strncpy( msg.chatHeader.szToName, thePlayerRole.GetName(), MAX_NAME_STRING-1 );
		if( ItemHyberCnt <= ITEM_HYBER_MAX_CNT && ItemHyberCnt > 0)
		{
			msg.nHyberItemCnt = ItemHyberCnt;

			for( int i=0; i<ItemHyberCnt; ++i )
			{
				msg.onlyId[i] = _HyberItemInfo[i];
				msg.itemId[i] = _HyberItemId[i];
				msg.type = _nBagType;
			}
		}
		msg.SetString( strChat.c_str() );

		GettheNetworkInput().SendMsg( &msg );
	}
	else if(words.Compare(0, "f") && words.GetWordCount() >= 2)
	{
		if( CSystemFamily::Instance()->IsMeHaveFamily() == false )
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Chat_ChannelTip, theXmlString.GetString(eText_FamilyCantChat) );
			m_pID_EDIT_INPUT->SetActivate( false );
			s_CUI_ID_FRAME_FACE.SetVisable( false );
			ImmAssociateContext( g_hWnd, NULL );
			return false;
		}
		s_CUI_ChatInfoBox.SetCurrentChannel(MsgChat::CHAT_TYPE_FAMILY);
		std::string szStr = szCommand;
		int nLen = strlen(szCommand);
		std::string szNewCommand = szStr.substr( 1 + 1, nLen - 2);

		std::string strChat = szNewCommand.c_str();

		clock_t tmNow = clock();
		_tmCountryLastTime = tmNow;

		MsgChat msg( MsgChat::CHAT_TYPE_FAMILY );	
		strncpy( msg.chatHeader.szToName, thePlayerRole.GetName(), MAX_NAME_STRING-1 );
		if( ItemHyberCnt <= ITEM_HYBER_MAX_CNT && ItemHyberCnt > 0)
		{
			msg.nHyberItemCnt = ItemHyberCnt;

			for( int i=0; i<ItemHyberCnt; ++i )
			{
				msg.onlyId[i] = _HyberItemInfo[i];
				msg.itemId[i] = _HyberItemId[i];
				msg.type = _nBagType;
			}
		}
		msg.SetString( strChat.c_str() );

		GettheNetworkInput().SendMsg( &msg );
	}


	//----------下面用于 读取 保存
	else if( words.Compare(0, "s") && words.GetWordCount() == 3)
	{
		//这里保存 快捷信息
		//SaveShortcutInfo( atoi(words.GetWord(1)), words.GetWord(2));
	}
	else if(words.Compare(0, "保存") && words.GetWordCount() == 3)
	{
		//这里保存 快捷信息
		//SaveShortcutInfo( atoi(words.GetWord(1)), words.GetWord(2));
	}
	else if(words.Compare(0, "l") && words.GetWordCount() == 2)
	{
		//这里读取 快捷信息
		//std::string charInfo = GetShortcutInfo( atoi(words.GetWord(1)) );
		//ID_EDIT_INPUTOnEditEnter(NULL, charInfo.c_str());
		//m_pID_EDIT_INPUT->SetText(charInfo);
	}
	else if(words.Compare(0, "读取") && words.GetWordCount() == 2)
	{
		//这里读取 快捷信息
		//std::string charInfo = GetShortcutInfo( atoi(words.GetWord(1)) );
		//ID_EDIT_INPUTOnEditEnter(NULL, charInfo.c_str());
		//m_pID_EDIT_INPUT->SetText(charInfo);
	}
	else if(words.Compare(0, "离队") )
	{
		//s_CUI_ID_FRAME_RBTNMENU.ID_BUTTON_EXITTERMOnButtonClick(NULL);
		s_CUI_ID_FRAME_SelfRBMenu.GetoutOnButtonClick(NULL);

	}
	else if(words.Compare(0, "leave"))
	{
		s_CUI_ID_FRAME_SelfRBMenu.GetoutOnButtonClick(NULL);
	}
	else if( words.Compare(0, "addui") )
	{
		const char* szValue = words.GetWord(1);
		if( szValue )
		{
			theUiManager.AddFrame( szValue );
			//theUiManager.FindFrame( "ID_FRAME_22569" )->SetVisable(true);
		}
	}
	else if(words.Compare(0, "sendgm") && words.GetWordCount() >= 2)
	{
		////SetPrivateName("gm");
		////ID_EDIT_INPUTOnEditEnter(NULL, words.GetWord(1));

		//std::string szStr = szCommand;
		//int nLen = strlen(szCommand);
		//std::string szNewCommand = szStr.substr( 1 + 6, nLen - 7);

		////Message()
		////UI_MessageBox::Show( szNewCommand.c_str() );

		//MsgChat msg( MsgChat::CHAT_TYPE_GM );
		//msg.SetString( szNewCommand.c_str());
		//GettheNetworkInput().SendMsg( &msg );
		//AddInfo( theXmlString.GetString( eClient_send2GMUI_ChatSystem2Player ) );
	}
	else if(words.Compare(0, "time") )
	{
		//显示天际厉
	}
	else if(words.IsNumber(0) && words.GetWordCount() == 1 )
	{
		MsgChat msg(MsgChat::CHAT_TYPE_NORMAL);//(m_enChatType);
		const char* nIndex = words.GetWord( 0 );
		short nID = 100 + atoi(nIndex);

		if( nID > 131 )
			return false;

		msg.SetExpressionId( nID );
		msg.SetString( "" ); 
		GettheNetworkInput().SendMsg( &msg );
	}
	//sbw_add
	else 
	{
		for (int i = 1; i < 11 + 1; i++)
		{
			char buff[5] = {0};
			sprintf(buff,"a%d",i);
			if (words.Compare(0,buff))
			{
				MsgReqSkillAttack msg;
				msg.chSkillCount = 1;
				msg.stSkill = 2319+i;
				msg.stSkillLevel = 1;
				SCharSkill* pCharSkill = thePlayerRole.m_SkillBag.GetSkillByID(msg.stSkill);
				if (pCharSkill && pCharSkill->bAvailable)
				{
					if( -1 == GettheNetworkInput().SendMsg( &msg ) )
					{
						//MESSAGE_BOX( "Disconnectted!" );
					}
				}

				std::string szStr = szCommand;
				int nLen = strlen(buff);
				std::string szNewCommand = szStr.substr( nLen, szStr.size() );
				//Lua_SendMsgChat( MsgChat::CHAT_TYPE_GUILD, szNewCommand );
				if (!szNewCommand.empty())
				{
					std::string strChat = szNewCommand.c_str();
					//strChat = CChatCheck::getInstance()->CheckStringInLowMark((char*)szNewCommand.c_str(), '*');
					SendMsgChatNormal(strChat.c_str());
				}
				break;
			}
		}
	}

	return true;
	unguard;
}


void CUI_ChatInfoBox::HyberClickPrivateChat( ControlObject* pSender, const char* szName )
{

	if( strcmp(thePlayerRole.GetName(), szName) == 0 )
		return;
//HEROONLINE-609
// 	if( NpcCoord::getInstance()->hasName(szName) )
// 		return;

	// 判断是否带(VIP)字样
	char szCorrectName[256];
	strncpy( szCorrectName, szName, 255 );
	char *p = strstr( szCorrectName, "(VIP)" );
	bool bVIP = false;
	if( p != NULL )
	{
		*p = 0;
		if( theHeroGame.GetPlayerMgr() && theHeroGame.GetPlayerMgr()->IsVipPlayer(szCorrectName) )
		{
			bVIP = true;
		}
	}
	if( !bVIP )
		s_CUI_ChatInfoBox.Begin2Secret( szName );
	else
		s_CUI_ChatInfoBox.Begin2Secret( szCorrectName );
}

void CUI_ChatInfoBox::ToggleChannel(ControlObject* pSender, int type)
{
	m_channelRadioGroup.ToggleRadio((ControlCheckBox*)pSender);

	//普通聊天 -- 设计 每一个这样控制输入频道聊天 改变 _nDefaultChannel 频道
	_nDefaultChannel = type;	//默认频道为普通 即下次回车输入框显示的时候为普通模式

	m_pID_EDIT_INPUT->SetActivate( true );	
	m_pChatInfoBox->SetVisable(true);
	SetInputText("");
	theUiManager.ToTop(m_pChatInfoBox);
	SetEditFocus();
	theUiManager.Compositor();

	ImmAssociateContext( g_hWnd, s_CUI_ID_FRAME_CREATE.GetImeInstance() );
	ChangeImmPos();
	m_channelGroup.SetVisible( false );
	m_pID_PICTURE_Di->SetVisable( false );
}


void CUI_ChatInfoBox::InializeChatByChannel()
{
	switch( _nDefaultChannel )
	{
	case MsgChat::CHAT_TYPE_NORMAL:
		{
			SetChatOutTypeText( theXmlString.GetString(eChatType_Normal) );
			SetInputText("");
		}
		break;
	case MsgChat::CHAT_TYPE_GUILD:
		{
			SetChatOutTypeText( theXmlString.GetString(eChatType_Guild) );
			SetInputText("");
		}
		break;
	case MsgChat::CHAT_TYPE_LEAGUE:
		{
			SetChatOutTypeText( theXmlString.GetString(eChatType_Alignment) );
			SetInputText("");
		}
		break;
	case  MsgChat::CHAT_TYPE_TERM:
		{
			SetChatOutTypeText( theXmlString.GetString(eChatType_Team) );
			SetInputText("");
		}
		break;
	case MsgChat::CHAT_TYPE_SHOUT:
		{
			SetChatOutTypeText( theXmlString.GetString(eChatType_Shout ));
			SetInputText("");
		}
		break;
	case MsgChat::CHAT_TYPE_HIGHSHOUT:
		{
			SetChatOutTypeText( theXmlString.GetString(eChatType_HightShout) );
			SetInputText("");
		}
		break;
	case MsgChat::CHAT_TYPE_PRIVATE:
		{
			SetChatOutTypeText( theXmlString.GetString(eChatType_Private) );
			if( m_szPrivateToName.length() > 0)
			{
				char szTemp[128] = {0};
				sprintf( szTemp, "%s ", m_szPrivateToName.c_str());
				SetInputText(szTemp);
			}
			else
				SetInputText("");
		}
		break;
	case MsgChat::CHAT_TYPE_BATTLE:
		{
			SetChatOutTypeText( theXmlString.GetString(eChatType_ZhenYing) );
			SetInputText("");
		}
		break;
	case MsgChat::CHAT_TYPE_COUNTRY:
		{
			SetChatOutTypeText( theXmlString.GetString(eChatType_CountryString) );
			SetInputText("");
		}
		break;
	case MsgChat::CHAT_TYPE_GM:
		{
	// 		SetChatOutTypeText( theXmlString.GetString(eChatType_GM) );
	// 		SetInputText("");
		}
		break;
	default:
		break;
	}
}

bool CUI_ChatInfoBox::ID_BUTTON_EnterOnButtonClick( ControlObject* pSender )
{
	//if( _bActiveInput )
	{
		ProcessAndSendChatMessage(_nDefaultChannel,m_pID_EDIT_INPUT->GetText());		
		m_pChatInfoBox->SetVisable(false);
	}
	
	return true;
}

void CUI_ChatInfoBox::CalFaceRect()
{
	if( m_pChatInfoBox )
		m_pChatInfoBox->GetRealRect(&faceRect);
	faceRect.left += (faceRect.right - faceRect.left) + 100;
	faceRect.top -= 168;

}

void CUI_ChatInfoBox::ClearChatShow()
{
	m_bNeedMoveDown = true;
	if( m_pChatInfoText )
		m_pChatInfoText->Clear();
}

void CUI_ChatInfoBox::ClearChat()
{
	m_chatInfos.clear();
	m_nCurrChatInfoIndex = 0;

	ClearChatShow();
}

bool CUI_ChatInfoBox::OnClickChannelButton(void)
{
	if(!m_pChatInfoBox)
	{
		assert(false&&"ui error");
		return false;
	}

	m_channelGroup.SetVisible( !m_channelGroup.IsVisible() );
	m_pID_PICTURE_Di->SetVisable( m_channelGroup.IsVisible() );
	return true;
}

void CUI_ChatInfoBox::SetChatOutTypeButton(ControlObject *pSender_)
{
	if(m_pID_BUTTON_ChatOutType)
		m_pID_BUTTON_ChatOutType->SetVisable(false);
	if(m_pID_BUTTON_ChatPrivate)
		m_pID_BUTTON_ChatPrivate->SetVisable(false);
	if(m_pID_BUTTON_BTeam)
		m_pID_BUTTON_BTeam->SetVisable(false);
	if(m_pID_BUTTON_BGuild1)
		m_pID_BUTTON_BGuild1->SetVisable(false);
	if(m_pID_BUTTON_BCountry)
		m_pID_BUTTON_BCountry->SetVisable(false);
	if(m_pID_BUTTON_BHightShout)
		m_pID_BUTTON_BHightShout->SetVisable(false);

	if ( m_pID_BUTTON_Family )
	{
		m_pID_BUTTON_Family->SetVisable(false);
	}

	//lyh++
	if ( m_pID_BUTTON_BGuanYuan )
	{
		m_pID_BUTTON_BGuanYuan->SetVisable(false);
	}

	if((ControlCheckBox *)pSender_ == m_pID_CHECKBOX_BPublic)
	{
		if(m_pID_BUTTON_ChatOutType)
			m_pID_BUTTON_ChatOutType->SetVisable(true);
	}
	else if((ControlCheckBox *)pSender_ == m_pID_CHECKBOX_ChatPrivate)
	{
		if(m_pID_BUTTON_ChatPrivate)
			m_pID_BUTTON_ChatPrivate->SetVisable(true);
	}
	else if((ControlCheckBox *)pSender_ == m_pID_CHECKBOX_BTeam)
	{
		if(m_pID_BUTTON_BTeam)
			m_pID_BUTTON_BTeam->SetVisable(true);
	}
	else if((ControlCheckBox *)pSender_ == m_pID_CHECKBOX_BGuild1)
	{
		if(m_pID_BUTTON_BGuild1)
			m_pID_BUTTON_BGuild1->SetVisable(true);
	}
	else if((ControlCheckBox *)pSender_ == m_pID_CHECKBOX_BCountry)
	{
		if(m_pID_BUTTON_BCountry)
			m_pID_BUTTON_BCountry->SetVisable(true);
	}
	else if((ControlCheckBox *)pSender_ == m_pID_CHECKBOX_BHightShout)
	{
		if(m_pID_BUTTON_BHightShout)
			m_pID_BUTTON_BHightShout->SetVisable(true);
	}
	else if ( (ControlCheckBox*)pSender_ == m_pID_CHECKBOX_Family  )
	{
		if(m_pID_BUTTON_Family)
			m_pID_BUTTON_Family->SetVisable(true);
	}
  //lyh++
	else if ( (ControlCheckBox*)pSender_ == m_pID_CHECKBOX_BGuanYuan  )
	{
		if(m_pID_BUTTON_BGuanYuan)
			m_pID_BUTTON_BGuanYuan->SetVisable(true);
	}

	if(CommonChatFrame::GetActiveChatFrame())
	{
		CommonChatFrame::GetActiveChatFrame()->ClearHyberLinks();
	}
}

void CUI_ChatInfoBox::SetChatTypeChannel(unsigned int type)
{
	if(m_pID_BUTTON_ChatOutType)
		m_pID_BUTTON_ChatOutType->SetVisable(false);
	if(m_pID_BUTTON_ChatPrivate)
		m_pID_BUTTON_ChatPrivate->SetVisable(false);
	if(m_pID_BUTTON_BTeam)
		m_pID_BUTTON_BTeam->SetVisable(false);
	if(m_pID_BUTTON_BGuild1)
		m_pID_BUTTON_BGuild1->SetVisable(false);
	if(m_pID_BUTTON_BCountry)
		m_pID_BUTTON_BCountry->SetVisable(false);
	if(m_pID_BUTTON_BHightShout)
		m_pID_BUTTON_BHightShout->SetVisable(false);

	if ( m_pID_BUTTON_Family )
	{
		m_pID_BUTTON_Family->SetVisable(false);
	}

	if ( m_pID_BUTTON_BGuanYuan )
	{
		m_pID_BUTTON_BGuanYuan->SetVisable(false);
	}


	switch(type)
	{
	case CHAT_TEAM:
		m_pID_BUTTON_BTeam->SetVisable(true);
		break;
	case CHAT_GUILD:
		m_pID_BUTTON_BGuild1->SetVisable(true);
		break;
	case CHAT_COUNTRY:
		m_pID_BUTTON_BCountry->SetVisable(true);
		break;
	case CHAT_PUBLIC:
		m_pID_BUTTON_ChatOutType->SetVisable(true);
		break;
	case CHAT_PRIVATE:
		m_pID_BUTTON_ChatPrivate->SetVisable(true);
		break;
	case CHAT_FAMILY:
		m_pID_BUTTON_Family->SetVisable(true);
		break;
	case CHAT_GY:
		m_pID_BUTTON_BGuanYuan->SetVisable(true);

	default:
		break;
	}
}