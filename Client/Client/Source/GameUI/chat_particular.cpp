/********************************************************************
Created by UIEditor.exe
FileName: D:\Tj\Client\UI\chat_particular.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "chat_particular.h"
#include "FuncPerformanceLog.h"
#include "XmlStringLanguage.h"
#include "LuaFuns.h"
#include "SortLuaScript.h"
#include "GlobalDef.h"
#include"../PlayerRole.h"
#include "chatcheck.h"
#include "NetworkInput.h"
#include "ChatInfoBox.h"
#include "../d3dapp.h"
#include "Create.h"
#include "core/Name.h"
#include "color_config.h"
#include "ScreenInfoManager.h"

#define MAX_CHAT_COUNT			50

extern BOOL DebugCommand( const char* pszCommand );

CUI_ID_FRAME_ChatParticular s_CUI_ID_FRAME_ChatParticular;
MAP_FRAME_RUN( s_CUI_ID_FRAME_ChatParticular, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_ChatParticular, OnFrameRender )
MAP_EDIT_ENTER_CALLBACK( s_CUI_ID_FRAME_ChatParticular, ID_EDIT_ChatInfoOnEditEnter )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ChatParticular, ID_BUTTON_SendOnButtonClick )
CUI_ID_FRAME_ChatParticular::CUI_ID_FRAME_ChatParticular()
{
	// SGuildMember
	m_pID_FRAME_ChatParticular = NULL;
	m_pID_TEXT_PromptInfo = NULL;
	m_pID_EDIT_ChatInfo = NULL;
	m_pID_BUTTON_Send = NULL;

	chatFlag = AN_S2A_OpenUI_NULL;
	memset( _HyberItemInfo, 0, sizeof(_HyberItemInfo) );
	memset( _HyberItemId, 0, sizeof(_HyberItemId) );
	ItemHyberCnt = 0;
	for(int i=0; i<ITEM_HYBER_MAX_CNT; ++i)
	{
		_saveItemHyber[i].clear();
	}

}
// Frame
bool CUI_ID_FRAME_ChatParticular::OnFrameRun()
{
	return true;
}
bool CUI_ID_FRAME_ChatParticular::OnFrameRender()
{
	return true;
}
// Edit
void CUI_ID_FRAME_ChatParticular::ID_EDIT_ChatInfoOnEditEnter( ControlObject* pSender, const char* szData )
{
	guardfunc;
	if ( szData[0] != 0 )
	{
		//LuaScript *pScript = (LuaScript*)g_GetScript(LUA_UICHAT);
		//if( pScript )
		//{
		//	pScript->GetGlobalFun(LUAEVENT_ON_ChatSend)(szData);
		//}

		std::string str = szData;
		if (str[0] == '/')
			DebugCommand(str.substr(1).c_str());

		SendMsgChat(szData);

		*m_pID_EDIT_ChatInfo = "";
		SetVisable( false );
		theUiManager.SetFocus( NULL );
		memset( _HyberItemInfo, 0, sizeof(_HyberItemInfo) );
		memset( _HyberItemId, 0, sizeof(_HyberItemId) );
		ItemHyberCnt = 0;
		for(int i=0; i<ITEM_HYBER_MAX_CNT; ++i)
		{
			_saveItemHyber[i].clear();
		}
	}
	unguard;
}
// Button
bool CUI_ID_FRAME_ChatParticular::ID_BUTTON_SendOnButtonClick( ControlObject* pSender )
{
	guardfunc;
	const char* chat = m_pID_EDIT_ChatInfo->GetText();
	if( chat )
	{
		ID_EDIT_ChatInfoOnEditEnter(m_pID_EDIT_ChatInfo, chat );
	}
	return true;
	unguard;
}
void CUI_ID_FRAME_ChatParticular::sendChatmsgParticular( const char* chat, AN_S2A_OpenClientUI_Flag flag )
{
	guardfunc;
	switch( flag )
	{
	case AN_S2A_OpenUI_ChatBULL:
		{
			std::string strChat;
			strChat = CChatCheck::getInstance()->CheckStringInLowMark((char*)chat, '*');

			MsgChat msg( MsgChat::CHAT_TYPE_BULL_VIP );
			strncpy( msg.chatHeader.szToName, thePlayerRole.GetName(), MAX_NAME_STRING - 1);
			msg.nHyberItemCnt = 0;
			msg.SetString( strChat.c_str() );

			GettheNetworkInput().SendMsg( &msg );
		}
		break;
	case AN_S2A_OpenUI_ChatSHOUT:
		{
			std::string strChat;
			strChat = CChatCheck::getInstance()->CheckStringInLowMark((char*)chat, '*');

			MsgChat msg( MsgChat::CHAT_TYPE_SHOUT_VIP );
			strncpy( msg.chatHeader.szToName, thePlayerRole.GetName(), MAX_NAME_STRING - 1);

			if( ItemHyberCnt <= ITEM_HYBER_MAX_CNT )
			{
				msg.nHyberItemCnt = ItemHyberCnt;

				for( int i=0; i<ItemHyberCnt; ++i )
				{
					msg.onlyId[i] = _HyberItemInfo[i];
					msg.itemId[i] = _HyberItemId[i];
				}
			}
			msg.SetString( strChat.c_str() );

			GettheNetworkInput().SendMsg( &msg );
		}
		break;
	case AN_S2A_OpenUI_ChatHIGHSHOUT:
		{
			std::string strChat;
			strChat = CChatCheck::getInstance()->CheckStringInLowMark((char*)chat, '*');

			MsgChat msg( MsgChat::CHAT_TYPE_HIGHSHOUT_VIP );
			strncpy( msg.chatHeader.szToName, thePlayerRole.GetName(), MAX_NAME_STRING-1 );
			
			if( ItemHyberCnt <= ITEM_HYBER_MAX_CNT )
			{
				msg.nHyberItemCnt = ItemHyberCnt;

				for( int i=0; i<ItemHyberCnt; ++i )
				{
					msg.onlyId[i] = _HyberItemInfo[i];
					msg.itemId[i] = _HyberItemId[i];
				}
			}
			msg.SetString( strChat.c_str() );

			GettheNetworkInput().SendMsg( &msg );
		}
		break;
	case AN_S2A_OpenUI_ChatParticular1:
		{
			std::string strChat;
			strChat = CChatCheck::getInstance()->CheckStringInLowMark((char*)chat, '*');

			MsgChat msg( MsgChat::CHAT_TYPE_PARTICAL1_VIP );
			strncpy( msg.chatHeader.szToName, thePlayerRole.GetName(), MAX_NAME_STRING-1 );
			
			if( ItemHyberCnt <= ITEM_HYBER_MAX_CNT )
			{
				msg.nHyberItemCnt = ItemHyberCnt;

				for( int i=0; i<ItemHyberCnt; ++i )
				{
					msg.onlyId[i] = _HyberItemInfo[i];
					msg.itemId[i] = _HyberItemId[i];
				}
			}
			msg.SetString( strChat.c_str() );

			GettheNetworkInput().SendMsg( &msg );
		}
		break;
	case AN_S2A_OpenUI_ChatParticular2:
		{
			std::string strChat;
			strChat = CChatCheck::getInstance()->CheckStringInLowMark((char*)chat, '*');

			MsgChat msg( MsgChat::CHAT_TYPE_PARTICAL2_VIP );
			strncpy( msg.chatHeader.szToName, thePlayerRole.GetName(), MAX_NAME_STRING-1 );
			
			if( ItemHyberCnt <= ITEM_HYBER_MAX_CNT )
			{
				msg.nHyberItemCnt = ItemHyberCnt;

				for( int i=0; i<ItemHyberCnt; ++i )
				{
					msg.onlyId[i] = _HyberItemInfo[i];
					msg.itemId[i] = _HyberItemId[i];
				}
			}
			msg.SetString( strChat.c_str() );

			GettheNetworkInput().SendMsg( &msg );
		}
		break;
	case AN_S2A_OpenUI_ChatParticular3:
		{
			std::string strChat;
			strChat = CChatCheck::getInstance()->CheckStringInLowMark((char*)chat, '*');

			MsgChat msg( MsgChat::CHAT_TYPE_PARTICAL3_VIP );
			strncpy( msg.chatHeader.szToName, thePlayerRole.GetName(), MAX_NAME_STRING-1 );
			
			if( ItemHyberCnt <= ITEM_HYBER_MAX_CNT )
			{
				msg.nHyberItemCnt = ItemHyberCnt;

				for( int i=0; i<ItemHyberCnt; ++i )
				{
					msg.onlyId[i] = _HyberItemInfo[i];
					msg.itemId[i] = _HyberItemId[i];
				}
			}
			msg.SetString( strChat.c_str() );

			GettheNetworkInput().SendMsg( &msg );
		}
		break;
	case AN_S2A_OpenUI_ChatParticular4:
		{
			std::string strChat;
			strChat = CChatCheck::getInstance()->CheckStringInLowMark((char*)chat, '*');

			MsgChat msg( MsgChat::CHAT_TYPE_PARTICAL4_VIP );
			strncpy( msg.chatHeader.szToName, thePlayerRole.GetName(), MAX_NAME_STRING-1 );
			
			if( ItemHyberCnt <= ITEM_HYBER_MAX_CNT )
			{
				msg.nHyberItemCnt = ItemHyberCnt;

				for( int i=0; i<ItemHyberCnt; ++i )
				{
					msg.onlyId[i] = _HyberItemInfo[i];
					msg.itemId[i] = _HyberItemId[i];
				}
			}
			msg.SetString( strChat.c_str() );

			GettheNetworkInput().SendMsg( &msg );
		}
		break;
	case AN_S2A_OpenUI_ChatParticular5:
		{
			std::string strChat;
			strChat = CChatCheck::getInstance()->CheckStringInLowMark((char*)chat, '*');

			MsgChat msg( MsgChat::CHAT_TYPE_PARTICAL5_VIP );
			strncpy( msg.chatHeader.szToName, thePlayerRole.GetName(), MAX_NAME_STRING-1 );
			
			if( ItemHyberCnt <= ITEM_HYBER_MAX_CNT )
			{
				msg.nHyberItemCnt = ItemHyberCnt;

				for( int i=0; i<ItemHyberCnt; ++i )
				{
					msg.onlyId[i] = _HyberItemInfo[i];
					msg.itemId[i] = _HyberItemId[i];
				}
			}
			msg.SetString( strChat.c_str() );

			GettheNetworkInput().SendMsg( &msg );
		}
		break;
	case AN_S2A_OpenUI_ChatParticular6:
		{
			std::string strChat;
			strChat = CChatCheck::getInstance()->CheckStringInLowMark((char*)chat, '*');

			MsgChat msg( MsgChat::CHAT_TYPE_PARTICAL6_VIP );
			strncpy( msg.chatHeader.szToName, thePlayerRole.GetName(), MAX_NAME_STRING-1 );
			
			if( ItemHyberCnt <= ITEM_HYBER_MAX_CNT )
			{
				msg.nHyberItemCnt = ItemHyberCnt;

				for( int i=0; i<ItemHyberCnt; ++i )
				{
					msg.onlyId[i] = _HyberItemInfo[i];
					msg.itemId[i] = _HyberItemId[i];
				}
			}
			msg.SetString( strChat.c_str() );

			GettheNetworkInput().SendMsg( &msg );
		}
		break;
	case AN_S2A_OpenUI_ChatParticular7:
		{
			std::string strChat;
			strChat = CChatCheck::getInstance()->CheckStringInLowMark((char*)chat, '*');

			MsgChat msg( MsgChat::CHAT_TYPE_PARTICAL7_VIP );
			strncpy( msg.chatHeader.szToName, thePlayerRole.GetName(), MAX_NAME_STRING-1 );
			
			if( ItemHyberCnt <= ITEM_HYBER_MAX_CNT )
			{
				msg.nHyberItemCnt = ItemHyberCnt;

				for( int i=0; i<ItemHyberCnt; ++i )
				{
					msg.onlyId[i] = _HyberItemInfo[i];
					msg.itemId[i] = _HyberItemId[i];
				}
			}
			msg.SetString( strChat.c_str() );

			GettheNetworkInput().SendMsg( &msg );
		}
		break;
	case AN_S2A_OpenUI_ChatParticular8:
		{
			std::string strChat;
			strChat = CChatCheck::getInstance()->CheckStringInLowMark((char*)chat, '*');

			MsgChat msg( MsgChat::CHAT_TYPE_PARTICAL8_VIP );
			strncpy( msg.chatHeader.szToName, thePlayerRole.GetName(), MAX_NAME_STRING-1 );
			
			if( ItemHyberCnt <= ITEM_HYBER_MAX_CNT )
			{
				msg.nHyberItemCnt = ItemHyberCnt;

				for( int i=0; i<ItemHyberCnt; ++i )
				{
					msg.onlyId[i] = _HyberItemInfo[i];
					msg.itemId[i] = _HyberItemId[i];
				}
			}
			msg.SetString( strChat.c_str() );

			GettheNetworkInput().SendMsg( &msg );
		}
		break;
	case AN_S2A_OpenUI_ChatParticular9:
		{
			std::string strChat;
			strChat = CChatCheck::getInstance()->CheckStringInLowMark((char*)chat, '*');

			MsgChat msg( MsgChat::CHAT_TYPE_PARTICAL9_VIP );
			strncpy( msg.chatHeader.szToName, thePlayerRole.GetName(), MAX_NAME_STRING-1 );
			
			if( ItemHyberCnt <= ITEM_HYBER_MAX_CNT )
			{
				msg.nHyberItemCnt = ItemHyberCnt;

				for( int i=0; i<ItemHyberCnt; ++i )
				{
					msg.onlyId[i] = _HyberItemInfo[i];
					msg.itemId[i] = _HyberItemId[i];
				}
			}
			msg.SetString( strChat.c_str() );

			GettheNetworkInput().SendMsg( &msg );
		}
		break;
	case AN_S2A_OpenUI_ChatParticular10:
		{
			std::string strChat;
			strChat = CChatCheck::getInstance()->CheckStringInLowMark((char*)chat, '*');

			MsgChat msg( MsgChat::CHAT_TYPE_PARTICAL10_VIP );
			strncpy( msg.chatHeader.szToName, thePlayerRole.GetName(), MAX_NAME_STRING-1 );
			
			if( ItemHyberCnt <= ITEM_HYBER_MAX_CNT )
			{
				msg.nHyberItemCnt = ItemHyberCnt;

				for( int i=0; i<ItemHyberCnt; ++i )
				{
					msg.onlyId[i] = _HyberItemInfo[i];
					msg.itemId[i] = _HyberItemId[i];
				}
			}
			msg.SetString( strChat.c_str() );

			GettheNetworkInput().SendMsg( &msg );
		}
		break;
	}
	unguard;
}

// 装载UI
bool CUI_ID_FRAME_ChatParticular::_LoadUI()
{
	guardfunc;
	DWORD dwResult = theUiManager.AddFrame( "data\\ui\\chat_particular.meui", true, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[UI\\chat_particular.UI]失败")
			return false;
	}
// 	else if ( dwResult != 12901/*文件版本号*/ )
// 	{
// 		MESSAGE_BOX("读取文件[UI\\chat_particular.UI]与源代码版本不一样")
// 	}
	return DoControlConnect();
	unguard;
}
// 关连控件
bool CUI_ID_FRAME_ChatParticular::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_ChatParticular, s_CUI_ID_FRAME_ChatParticularOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_ChatParticular, s_CUI_ID_FRAME_ChatParticularOnFrameRender );
	theUiManager.OnEditEnter( ID_FRAME_ChatParticular, ID_EDIT_ChatInfo, s_CUI_ID_FRAME_ChatParticularID_EDIT_ChatInfoOnEditEnter );
	theUiManager.OnButtonClick( ID_FRAME_ChatParticular, ID_BUTTON_Send, s_CUI_ID_FRAME_ChatParticularID_BUTTON_SendOnButtonClick );

	m_pID_FRAME_ChatParticular = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_ChatParticular );
	m_pID_TEXT_PromptInfo = (ControlText*)theUiManager.FindControl( ID_FRAME_ChatParticular, ID_TEXT_PromptInfo );
	m_pID_EDIT_ChatInfo = (ControlEdit*)theUiManager.FindControl( ID_FRAME_ChatParticular, ID_EDIT_ChatInfo );
	m_pID_BUTTON_Send = (ControlButton*)theUiManager.FindControl( ID_FRAME_ChatParticular, ID_BUTTON_Send );
	assert( m_pID_FRAME_ChatParticular );
	m_pID_FRAME_ChatParticular->SetVisable( false );
	assert( m_pID_TEXT_PromptInfo );
	assert( m_pID_EDIT_ChatInfo );
	m_pID_EDIT_ChatInfo->SetMaxCnt(MAX_CHAT_COUNT);
	assert( m_pID_BUTTON_Send );

	if( !s_CUI_ID_FRAME_CREATE.GetImeInstance() )
		s_CUI_ID_FRAME_CREATE.SetImeInstance( ImmGetContext( g_hWnd ) );

	ImmReleaseContext( g_hWnd, s_CUI_ID_FRAME_CREATE.GetImeInstance()  );

	//show( AN_S2A_OpenUI_ChatHIGHSHOUT );

	return true;
}
// 卸载UI
bool CUI_ID_FRAME_ChatParticular::_UnLoadUI()
{
	guardfunc;
	m_pID_FRAME_ChatParticular = NULL;
	m_pID_TEXT_PromptInfo = NULL;
	m_pID_EDIT_ChatInfo = NULL;
	m_pID_BUTTON_Send = NULL;
	return theUiManager.RemoveFrame( "data\\ui\\chat_particular.meui" );
	unguard;
}
// 是否可视
bool CUI_ID_FRAME_ChatParticular::_IsVisable()
{
	guardfunc;
	if( m_pID_FRAME_ChatParticular )
	{
		return m_pID_FRAME_ChatParticular->IsVisable();
	}
	return false;
	unguard;
}
// 设置是否可视
void CUI_ID_FRAME_ChatParticular::_SetVisable( const bool bVisable )
{
	guardfunc;
	if( m_pID_FRAME_ChatParticular )
	{
		m_pID_FRAME_ChatParticular->SetVisable( bVisable );

		if( bVisable == true)
			ImmAssociateContext( g_hWnd, s_CUI_ID_FRAME_CREATE.GetImeInstance() );
		else
			ImmAssociateContext( g_hWnd, NULL );
	}
	//zjj add inputedit focus [2008.9.3]
	if(bVisable)
	{
		theUiManager.SetFocus(m_pID_EDIT_ChatInfo);
	}
	unguard;
}
void CUI_ID_FRAME_ChatParticular::show( AN_S2A_OpenClientUI_Flag flag )
{
	guardfunc;
	//switch( flag )
	//{
	//case AN_S2A_OpenUI_ChatBULL:
	//	{
	//		if( !IsVisable() )
	//		{
	//			*m_pID_TEXT_PromptInfo = theXmlString.GetString(eClient_ChatParticular_Bull);
	//			chatFlag = AN_S2A_OpenUI_ChatBULL;
	//			SetVisable( true );
	//		}
	//		else
	//		{
	//			chatFlag = AN_S2A_OpenUI_NULL;
	//			SetVisable( false );
	//		}
	//	}
	//	break;
	//case AN_S2A_OpenUI_ChatSHOUT:
	//	{
	//		if( !IsVisable() )
	//		{
	//			*m_pID_TEXT_PromptInfo = theXmlString.GetString(eClient_ChatParticular_Shout);
	//			chatFlag = AN_S2A_OpenUI_ChatSHOUT;
	//			SetVisable( true );
	//		}
	//		else
	//		{
	//			chatFlag = AN_S2A_OpenUI_NULL;
	//			SetVisable( false );
	//		}
	//	}
	//	break;
	//case AN_S2A_OpenUI_ChatHIGHSHOUT:
	//	{
	//		if( !IsVisable() )
	//		{
	//			*m_pID_TEXT_PromptInfo = theXmlString.GetString(eClient_ChatParticular_HighShout);
	//			chatFlag = AN_S2A_OpenUI_ChatHIGHSHOUT;
	//			SetVisable( true );
	//		}
	//		else
	//		{
	//			chatFlag = AN_S2A_OpenUI_NULL;
	//			SetVisable( false );
	//		}
	//	}
	//	break;
	//case AN_S2A_OpenUI_ChatParticular1:
	//	{
	//		if( !IsVisable() )
	//		{
	//			*m_pID_TEXT_PromptInfo = theXmlString.GetString(eClient_ChatParticular_par1);
	//			chatFlag = AN_S2A_OpenUI_ChatParticular1;
	//			SetVisable( true );
	//		}
	//		else
	//		{
	//			chatFlag = AN_S2A_OpenUI_NULL;
	//			SetVisable( false );
	//		}
	//	}
	//	break;
	//case AN_S2A_OpenUI_ChatParticular2:
	//	{
	//		if( !IsVisable() )
	//		{
	//			*m_pID_TEXT_PromptInfo = theXmlString.GetString(eClient_ChatParticular_par2);
	//			chatFlag = AN_S2A_OpenUI_ChatParticular2;
	//			SetVisable( true );
	//		}
	//		else
	//		{
	//			chatFlag = AN_S2A_OpenUI_NULL;
	//			SetVisable( false );
	//		}
	//	}
	//	break;
	//case AN_S2A_OpenUI_ChatParticular3:
	//	{
	//		if( !IsVisable() )
	//		{
	//			*m_pID_TEXT_PromptInfo = theXmlString.GetString(eClient_ChatParticular_par3);
	//			chatFlag = AN_S2A_OpenUI_ChatParticular3;
	//			SetVisable( true );
	//		}
	//		else
	//		{
	//			chatFlag = AN_S2A_OpenUI_NULL;
	//			SetVisable( false );
	//		}
	//	}
	//	break;
	//case AN_S2A_OpenUI_ChatParticular4:
	//	{
	//		if( !IsVisable() )
	//		{
	//			*m_pID_TEXT_PromptInfo = theXmlString.GetString(eClient_ChatParticular_par4);
	//			chatFlag = AN_S2A_OpenUI_ChatParticular4;
	//			SetVisable( true );
	//		}
	//		else
	//		{
	//			chatFlag = AN_S2A_OpenUI_NULL;
	//			SetVisable( false );
	//		}
	//	}
	//	break;
	//case AN_S2A_OpenUI_ChatParticular5:
	//	{
	//		if( !IsVisable() )
	//		{
	//			*m_pID_TEXT_PromptInfo = theXmlString.GetString(eClient_ChatParticular_par5);
	//			chatFlag = AN_S2A_OpenUI_ChatParticular5;
	//			SetVisable( true );
	//		}
	//		else
	//		{
	//			chatFlag = AN_S2A_OpenUI_NULL;
	//			SetVisable( false );
	//		}
	//	}
	//	break;
	//case AN_S2A_OpenUI_ChatParticular6:
	//	{
	//		if( !IsVisable() )
	//		{
	//			*m_pID_TEXT_PromptInfo = theXmlString.GetString(eClient_ChatParticular_par6);
	//			chatFlag = AN_S2A_OpenUI_ChatParticular6;
	//			SetVisable( true );
	//		}
	//		else
	//		{
	//			chatFlag = AN_S2A_OpenUI_NULL;
	//			SetVisable( false );
	//		}
	//	}
	//	break;
	//case AN_S2A_OpenUI_ChatParticular7:
	//	{
	//		if( !IsVisable() )
	//		{
	//			*m_pID_TEXT_PromptInfo = theXmlString.GetString(eClient_ChatParticular_par7);
	//			chatFlag = AN_S2A_OpenUI_ChatParticular7;
	//			SetVisable( true );
	//		}
	//		else
	//		{
	//			chatFlag = AN_S2A_OpenUI_NULL;
	//			SetVisable( false );
	//		}
	//	}
	//	break;
	//case AN_S2A_OpenUI_ChatParticular8:
	//	{
	//		if( !IsVisable() )
	//		{
	//			*m_pID_TEXT_PromptInfo = theXmlString.GetString(eClient_ChatParticular_par8);
	//			chatFlag = AN_S2A_OpenUI_ChatParticular8;
	//			SetVisable( true );
	//		}
	//		else
	//		{
	//			chatFlag = AN_S2A_OpenUI_NULL;
	//			SetVisable( false );
	//		}
	//	}
	//	break;
	//case AN_S2A_OpenUI_ChatParticular9:
	//	{
	//		if( !IsVisable() )
	//		{
	//			*m_pID_TEXT_PromptInfo = theXmlString.GetString(eClient_ChatParticular_par9);
	//			chatFlag = AN_S2A_OpenUI_ChatParticular9;
	//			SetVisable( true );
	//		}
	//		else
	//		{
	//			chatFlag = AN_S2A_OpenUI_NULL;
	//			SetVisable( false );
	//		}
	//	}
	//	break;
	//case AN_S2A_OpenUI_ChatParticular10:
	//	{
	//		if( !IsVisable() )
	//		{
	//			*m_pID_TEXT_PromptInfo = theXmlString.GetString(eClient_ChatParticular_par10);
	//			chatFlag = AN_S2A_OpenUI_ChatParticular10;
	//			SetVisable( true );
	//		}
	//		else
	//		{
	//			chatFlag = AN_S2A_OpenUI_NULL;
	//			SetVisable( false );
	//		}
	//	}
	//	break;
	//}
	unguard;
}
//void CUI_ID_FRAME_ChatParticular::addHyberText( const char* text, SCharItem* iteminfo )
void CUI_ID_FRAME_ChatParticular::addHyberText( const char* text, __int64 onlyId, int itemid )
{
	guardfunc;

	//if( onlyId == 0 )
	//	return;
	//if( itemid == 0 )
	//	return;
	if( NULL == text )
		return;

	if( ItemHyberCnt >= ITEM_HYBER_MAX_CNT )
	{
		//s_CUI_ChatInfoBox.AddInfo( theXmlString.GetString(eClient_AddInfo_2slk_5), Color_Config.getColor( CC_SystemPromp ) );
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_FamilyEx,theXmlString.GetString(eClient_AddInfo_2slk_5));
		return;
	}

	//for( int i=0; i<ITEM_HYBER_MAX_CNT; i++)
	//{
	//	if( strcmp(_saveItemHyber[i].c_str(), text) == 0 )
	//	{
	//		s_CUI_ChatInfoBox.AddInfo( theXmlString.GetString(eClient_AddInfo_2slk_6) );
	//		return;
	//	}
	//}

	std::string strAddText = text;
	strAddText.insert(0, "[");
	strAddText.insert(strAddText.length(), "]");
	m_pID_EDIT_ChatInfo->addText( strAddText.c_str() );
	theUiManager.ToTop( m_pID_FRAME_ChatParticular );
	theUiManager.SetFocus(m_pID_EDIT_ChatInfo);

	if( onlyId != 0 )
	{
		_HyberItemInfo[ItemHyberCnt] = onlyId;
		_HyberItemId[ItemHyberCnt] = itemid;
		_saveItemHyber[ItemHyberCnt] = text;

		++ItemHyberCnt;
	}

	unguard;
}
void CUI_ID_FRAME_ChatParticular::SendMsgChat( const char* szData )
{
	guardfunc;
	sendChatmsgParticular( szData, chatFlag );
	unguard;
}
bool CUI_ID_FRAME_ChatParticular::EditInputIsVisable()
{
	guardfunc;
	if( m_pID_EDIT_ChatInfo )
	{
		return (theUiManager.GetFocus() == m_pID_EDIT_ChatInfo);
	}
	return FALSE;
	unguard;
}