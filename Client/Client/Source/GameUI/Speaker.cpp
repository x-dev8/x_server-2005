/********************************************************************
Created by UIEditor.exe
FileName: C:\Documents and Settings\huwen\桌面\Speaker.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "Speaker.h"
#include "DataCenter.h"
#include "chatcheck.h"
#include "PlayerRole.h"
#include "NetworkInput.h"
#include "chat_list.h"
#include "Create.h"
#include "ChatInfoBox.h"
#include "Pack.h"
#include "MeUi/ExpressionManager.h"
#include "color_config.h"
#include "Cfg.h"
#include "ScreenInfoManager.h"
#include "PlayerRole.h"
#include "core/Name.h"
#include "XmlStringLanguage.h"
#include "Common.h"
#include "Me3d/Global.h"
#include "PackItemEnableManager.h"

#define MAX_XIAOLABA_MSG 2  //小喇叭最多显示的条数

extern HWND g_hWnd;

CUI_ID_FRAME_Speaker s_CUI_ID_FRAME_Speaker;
MAP_FRAME_RUN( s_CUI_ID_FRAME_Speaker, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_Speaker, OnFrameRender )
MAP_EDIT_ENTER_CALLBACK( s_CUI_ID_FRAME_Speaker, ID_EDIT_INPUTOnEditEnter )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Speaker, ID_BUTTON_CancelOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Speaker, ID_BUTTON_OkOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_Speaker, ID_BUTTON_FaceOnButtonClick )
CUI_ID_FRAME_Speaker::CUI_ID_FRAME_Speaker()
{
	// Member
	m_pChatInfoBox = NULL;
	m_pID_PICTURE_EditWall = NULL;
	m_pID_EDIT_INPUT = NULL;
	m_pID_BUTTON_Cancel = NULL;
	m_pID_BUTTON_Ok = NULL;
	m_pID_TEXT_Msg = NULL;
	m_pID_BUTTON_Face = NULL;

	m_dwStartTime = 0;
	m_pHornEffect = NULL;
}
// Frame
bool CUI_ID_FRAME_Speaker::OnFrameRun()
{
	return true;
}
bool CUI_ID_FRAME_Speaker::OnFrameRender()
{
	
	return true;
}
// Edit
void CUI_ID_FRAME_Speaker::ID_EDIT_INPUTOnEditEnter( ControlObject* pSender, const char* szData )
{
	if (!m_pChatInfoBox)
		return;
	if (szData && strlen(szData) == 0)
		return;

	ID_BUTTON_OkOnButtonClick( m_pID_BUTTON_Ok );

	m_bSendMsg = true;
}
// Button
bool CUI_ID_FRAME_Speaker::ID_BUTTON_CancelOnButtonClick( ControlObject* pSender )
{
	if (!m_pChatInfoBox)
		return false;
	SetVisable(false);
	return true;
}
// Button
bool CUI_ID_FRAME_Speaker::ID_BUTTON_OkOnButtonClick( ControlObject* pSender )
{
	if (!m_pChatInfoBox)
		return false;

	std::string strChat;
	strChat = CChatCheck::getInstance()->CheckStringInLowMark((char*)m_pID_EDIT_INPUT->GetText(), '*');

	if (strChat.empty())
		return true;

	switch( m_flag )
	{
	case AN_S2A_OpenUI_ChatBULL:
		{
			MsgChat msg( MsgChat::CHAT_TYPE_BULL_VIP );
			strncpy( msg.chatHeader.szToName, thePlayerRole.GetName(), MAX_NAME_STRING - 1);

			if( ItemHyberCnt <= ITEM_HYBER_MAX_CNT )
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
		break;
	case AN_S2A_OpenUI_ChatSHOUT:
		{
			MsgChat msg( MsgChat::CHAT_TYPE_SHOUT_VIP );
			strncpy( msg.chatHeader.szToName, thePlayerRole.GetName(), MAX_NAME_STRING - 1);

			if( ItemHyberCnt <= ITEM_HYBER_MAX_CNT )
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
		break;
	case AN_S2A_OpenUI_ChatHIGHSHOUT:
		{
			SCharItem item;
			//这物品ID怎么配置的到处都是 itemsymbol.config ID=1的
			/*if (!thePlayerRole.m_bag.GetItemByItemID(gCfg.m_nXiaoLaBaItemId,&item))
			{
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_SmallHorn, theXmlString.GetString( eText_NoXiaoLaBaForShout ) );
				return false;
			}*/
			MsgChat msg( MsgChat::CHAT_TYPE_HIGHSHOUT_VIP );
			strncpy( msg.chatHeader.szToName, thePlayerRole.GetName(), MAX_NAME_STRING-1 );

			if( ItemHyberCnt <= ITEM_HYBER_MAX_CNT )
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

			// 清空内容
			ClearHyberLinks();
		}
		break;
	case AN_S2A_OpenUI_ChatParticular1:
		{
			MsgChat msg( MsgChat::CHAT_TYPE_PARTICAL1_VIP );
			strncpy( msg.chatHeader.szToName, thePlayerRole.GetName(), MAX_NAME_STRING-1 );

			if( ItemHyberCnt <= ITEM_HYBER_MAX_CNT )
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
		break;
	case AN_S2A_OpenUI_ChatParticular2:
		{
			MsgChat msg( MsgChat::CHAT_TYPE_PARTICAL2_VIP );
			strncpy( msg.chatHeader.szToName, thePlayerRole.GetName(), MAX_NAME_STRING-1 );

			if( ItemHyberCnt <= ITEM_HYBER_MAX_CNT )
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
		break;
	case AN_S2A_OpenUI_ChatParticular3:
		{
			MsgChat msg( MsgChat::CHAT_TYPE_PARTICAL3_VIP );
			strncpy( msg.chatHeader.szToName, thePlayerRole.GetName(), MAX_NAME_STRING-1 );

			if( ItemHyberCnt <= ITEM_HYBER_MAX_CNT )
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
		break;
	case AN_S2A_OpenUI_ChatParticular4:
		{
			MsgChat msg( MsgChat::CHAT_TYPE_PARTICAL4_VIP );
			strncpy( msg.chatHeader.szToName, thePlayerRole.GetName(), MAX_NAME_STRING-1 );

			if( ItemHyberCnt <= ITEM_HYBER_MAX_CNT )
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
		break;
	case AN_S2A_OpenUI_ChatParticular5:
		{
			MsgChat msg( MsgChat::CHAT_TYPE_PARTICAL5_VIP );
			strncpy( msg.chatHeader.szToName, thePlayerRole.GetName(), MAX_NAME_STRING-1 );

			if( ItemHyberCnt <= ITEM_HYBER_MAX_CNT )
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
		break;
	case AN_S2A_OpenUI_ChatParticular6:
		{
			MsgChat msg( MsgChat::CHAT_TYPE_PARTICAL6_VIP );
			strncpy( msg.chatHeader.szToName, thePlayerRole.GetName(), MAX_NAME_STRING-1 );

			if( ItemHyberCnt <= ITEM_HYBER_MAX_CNT )
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
		break;
	case AN_S2A_OpenUI_ChatParticular7:
		{
			MsgChat msg( MsgChat::CHAT_TYPE_PARTICAL7_VIP );
			strncpy( msg.chatHeader.szToName, thePlayerRole.GetName(), MAX_NAME_STRING-1 );

			if( ItemHyberCnt <= ITEM_HYBER_MAX_CNT )
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
		break;
	case AN_S2A_OpenUI_ChatParticular8:
		{
			MsgChat msg( MsgChat::CHAT_TYPE_PARTICAL8_VIP );
			strncpy( msg.chatHeader.szToName, thePlayerRole.GetName(), MAX_NAME_STRING-1 );

			if( ItemHyberCnt <= ITEM_HYBER_MAX_CNT )
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
		break;
	case AN_S2A_OpenUI_ChatParticular9:
		{
			MsgChat msg( MsgChat::CHAT_TYPE_PARTICAL9_VIP );
			strncpy( msg.chatHeader.szToName, thePlayerRole.GetName(), MAX_NAME_STRING-1 );

			if( ItemHyberCnt <= ITEM_HYBER_MAX_CNT )
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
		break;
	case AN_S2A_OpenUI_ChatParticular10:
		{
			MsgChat msg( MsgChat::CHAT_TYPE_PARTICAL10_VIP );
			strncpy( msg.chatHeader.szToName, thePlayerRole.GetName(), MAX_NAME_STRING-1 );

			if( ItemHyberCnt <= ITEM_HYBER_MAX_CNT )
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
		break;
	}

	//ImmAssociateContext( g_hWnd, NULL );
	SetVisable(false);
	return true;
}
// Button
bool CUI_ID_FRAME_Speaker::ID_BUTTON_FaceOnButtonClick( ControlObject* pSender )
{
	if (!m_pChatInfoBox)
		return false;
	s_CUI_ID_FRAME_FACE.SetVisable( !s_CUI_ID_FRAME_FACE.IsVisable() );
	if (s_CUI_ID_FRAME_FACE.IsVisable())
	{
		RECT rc;
		m_pChatInfoBox->GetRealRect(&rc);

		int nOldAlignMode = s_CUI_ID_FRAME_FACE.GetAlignMode();
		s_CUI_ID_FRAME_FACE.SetAlignMode( AlignMode_LeftTop );
		s_CUI_ID_FRAME_FACE.SetScreenPos(rc.left, rc.bottom);
		s_CUI_ID_FRAME_FACE.SetAlignMode( nOldAlignMode );
	}
	return true;
}

// 装载UI
bool CUI_ID_FRAME_Speaker::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\Speaker.MEUI", false, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\Speaker.MEUI]失败")
			return false;
	}
	return DoControlConnect();
}

static void UISpeaker_VisableChanged(ControlObject* pObject)
{
	if (!s_CUI_ID_FRAME_Speaker.IsVisable() && s_CUI_ID_FRAME_Speaker.GetListImage())
	{
		if (s_CUI_ID_FRAME_Speaker.GetItemImgIndex() != -1)
		{
			if( s_CUI_ID_FRAME_Speaker.GetListImage() )
			{
				ControlIconDrag::S_ListImg* pListImg = s_CUI_ID_FRAME_Speaker.GetListImage()->GetItemByIndex(
					s_CUI_ID_FRAME_Speaker.GetItemImgIndex());
				if (pListImg)
					pListImg->m_eEnable = eIcon_Enable;
			}

            // 刷背包物品 Enable态统一流程     modified by zhuomeng.hu		[12/30/2010]
            CPackItemEnableManager::Instance()->RefreshBagItemEnable( &thePlayerRole.m_bag, s_CUI_ID_FRAME_Speaker.GetItemImgIndex(), true );
		}

		s_CUI_ID_FRAME_Speaker.SetListImage(NULL);
		s_CUI_ID_FRAME_Speaker.SetItemImgIndex(-1);
		s_CUI_ID_FRAME_Speaker.SetItemId(InvalidLogicNumber);

		/*memset( s_CUI_ID_FRAME_Speaker._HyberItemInfo, 0, sizeof(s_CUI_ID_FRAME_Speaker._HyberItemInfo) );
		memset( s_CUI_ID_FRAME_Speaker._HyberItemId, 0, sizeof(s_CUI_ID_FRAME_Speaker._HyberItemId) );
		s_CUI_ID_FRAME_Speaker.ItemHyberCnt = 0;*/

		//ImmAssociateContext( g_hWnd, NULL );

		s_CUI_ID_FRAME_FACE.SetVisable(false);
	}

	
	s_CUI_ID_FRAME_Speaker.ClearHyberLinks();
	s_CUI_ID_FRAME_Speaker._nBagType = 0;

	ImmAssociateContext( g_hWnd, NULL );
}

// 关连控件
bool CUI_ID_FRAME_Speaker::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_Speaker, s_CUI_ID_FRAME_SpeakerOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_Speaker, s_CUI_ID_FRAME_SpeakerOnFrameRender );
	theUiManager.OnEditEnter( ID_FRAME_Speaker, ID_EDIT_Info, s_CUI_ID_FRAME_SpeakerID_EDIT_INPUTOnEditEnter );
	theUiManager.OnButtonClick( ID_FRAME_Speaker, ID_BUTTON_Cancel, s_CUI_ID_FRAME_SpeakerID_BUTTON_CancelOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Speaker, ID_BUTTON_Ok, s_CUI_ID_FRAME_SpeakerID_BUTTON_OkOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_Speaker, ID_BUTTON_Face, s_CUI_ID_FRAME_SpeakerID_BUTTON_FaceOnButtonClick );

	m_pChatInfoBox = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_Speaker );
	m_pID_PICTURE_EditWall = (ControlPicture*)theUiManager.FindControl( ID_FRAME_Speaker, ID_PICTURE_EditWall );
	m_pID_EDIT_INPUT = (ControlEdit*)theUiManager.FindControl( ID_FRAME_Speaker, ID_EDIT_Info );
	m_pID_BUTTON_Cancel = (ControlButton*)theUiManager.FindControl( ID_FRAME_Speaker, ID_BUTTON_Cancel );
	m_pID_BUTTON_Ok = (ControlButton*)theUiManager.FindControl( ID_FRAME_Speaker, ID_BUTTON_Ok );
	m_pID_TEXT_Msg = (ControlText*)theUiManager.FindControl( ID_FRAME_Speaker, ID_TEXT_Msg );
	m_pID_BUTTON_Face = (ControlButton*)theUiManager.FindControl( ID_FRAME_Speaker, ID_BUTTON_Face );
	assert( m_pChatInfoBox );
	assert( m_pID_PICTURE_EditWall );
	assert( m_pID_EDIT_INPUT );
	assert( m_pID_BUTTON_Cancel );
	assert( m_pID_BUTTON_Ok );
	assert( m_pID_TEXT_Msg );
	assert( m_pID_BUTTON_Face );

	m_nItemId = InvalidLogicNumber;
	m_nItemImgIndex = -1;
	m_pListImage = NULL;

	InitialCommonChat();

	_SetVisable( false );
	m_pID_EDIT_INPUT->SetMaxLength(CUI_ID_FRAME_chatInfoList::MaxHornTextLength);

	m_pChatInfoBox->SetOnVisibleChangedFun(UISpeaker_VisableChanged);

	InitMember();
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_Speaker::_UnLoadUI()
{
	m_pChatInfoBox = NULL;
	m_pID_PICTURE_EditWall = NULL;
	m_pID_EDIT_INPUT = NULL;
	m_pID_BUTTON_Cancel = NULL;
	m_pID_BUTTON_Ok = NULL;
	m_pID_TEXT_Msg = NULL;
	m_pID_BUTTON_Face = NULL;
	m_pHornEffect = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\Speaker.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_Speaker::_IsVisable()
{
	if (m_pChatInfoBox)
		return m_pChatInfoBox->IsVisable();
	return false;
}
// 设置是否可视
void CUI_ID_FRAME_Speaker::_SetVisable( const bool bVisable, AN_S2A_OpenClientUI_Flag flag )
{
	if (!m_pChatInfoBox)
		return;

	ImmAssociateContext( g_hWnd, NULL );
	m_pChatInfoBox->SetVisable( bVisable );
	s_CUI_ID_FRAME_FACE.SetVisable( false );

	if (bVisable)
	{
		s_CUI_ChatInfoBox.SetVisable(false);

		if (m_pListImage && m_nItemImgIndex != -1)
		{
			ControlIconDrag::S_ListImg* pListImg = m_pListImage->GetItemByIndex(
				m_nItemImgIndex);
			if (pListImg)
				pListImg->m_eEnable = eIcon_Disable;

            // 刷背包物品 Enable态统一流程     modified by zhuomeng.hu		[12/30/2010]
            CPackItemEnableManager::Instance()->RefreshBagItemEnable( &thePlayerRole.m_bag, m_nItemImgIndex, true );
		}

		*m_pID_EDIT_INPUT = "";
		m_pID_EDIT_INPUT->SetActivate( true );

		theUiManager.SetFocus(m_pID_EDIT_INPUT);
		theUiManager.ToTop(m_pChatInfoBox);

		ImmAssociateContext( g_hWnd, s_CUI_ID_FRAME_CREATE.GetImeInstance() );
		ChangeImmPos();
		m_pID_EDIT_INPUT->setDefaultColor(Color_Config.getColor(CC_CHAT_XIAOLABA));

		m_flag = flag;
	}
}

ControlListImage* CUI_ID_FRAME_Speaker::GetListImage()
{
	if (!m_pChatInfoBox)
		return NULL;
	return m_pListImage;
}

void CUI_ID_FRAME_Speaker::SetVisable( const bool bVisable, AN_S2A_OpenClientUI_Flag flag /*= AN_S2A_OpenUI_ChatBULL */ )
{
	CUIBase::SetVisable(bVisable);
	if (m_bUILoad)
		_SetVisable(bVisable,flag);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------
void CUI_ID_FRAME_Speaker::AddInfo( const std::string& str, const D3DCOLOR col, const UINT nType , char *szToName,
							  char* itemData, int cntHyber, int nBagType /*= 0*/, bool bAutoReply /*= false */ )
{	
	ChatInfo chatInfo;
	chatInfo.text = str;

	if (szToName)
		chatInfo.toName = szToName;

	chatInfo.color = col;
	chatInfo.nType = nType;
	chatInfo.nChatInfoIndex = m_nCurrChatInfoIndex++;
	chatInfo.cntHyber = cntHyber;
	chatInfo.nBagType = nBagType;
	if( nBagType == BT_MountBag )
		memcpy(chatInfo.mountItems, itemData, sizeof(SMountItem) * min( cntHyber, ITEM_HYBER_MAX_CNT ));
	else if(nBagType == BT_PetBag)
		memcpy(chatInfo.petItems,itemData,sizeof(SPetItem) * min( cntHyber, ITEM_HYBER_MAX_CNT ));
	else
		memcpy(chatInfo.normalItems, itemData, sizeof(SCharItem) * min( cntHyber, ITEM_HYBER_MAX_CNT ));

	m_TempChatInfos.push_back(chatInfo);
	
	if (m_TempChatInfos.size() == 1)
	{
		m_dwStartTime = HQ_TimeGetTime();
		RenderStarEffect();
		RefreshCharInfo();
	}
	else
	{
		while(m_TempChatInfos.size() > MAX_XIAOLABA_MSG)
		{
			m_TempChatInfos.pop_front();
		}
		m_dwStartTime = HQ_TimeGetTime();
		RenderStarEffect();
		RefreshCharInfo();
	}
}


bool CUI_ID_FRAME_Speaker::RefreshCharInfo()
{
	if (!m_pChatInfoText)
	{
		InitMember();
	}

	if (m_pChatInfoText)
	{
		m_pChatInfoText->Clear();
		if (m_TempChatInfos.size() > 0)
		{
			int num = 0;
			std::list<ChatInfo>::iterator itr = m_TempChatInfos.begin();
			while(itr != m_TempChatInfos.end())
			{
				if(num >= MAX_XIAOLABA_MSG)
				{
					break;
				}
				ChatInfo TempInfo1 = *itr;
				if (TempInfo1.text.size() > 0)
				{
					std::string str = TempInfo1.text;
					ExpressionManager::GetInstance().AddExpressionAni(str, 4);
					char * ItemData = NULL;
					if( TempInfo1.nBagType == BT_MountBag )
						ItemData = (char *)&TempInfo1.mountItems[0];
					else if(TempInfo1.nBagType == BT_PetBag)
						ItemData = (char *)&TempInfo1.petItems[0];
					else
						ItemData = (char *)&TempInfo1.normalItems[0];
					char ToName[500];
					strcpy_s(ToName,500,TempInfo1.toName.c_str());
					ShowTextInChatList(str, Color_Config.getColor(CC_CHAT_XIAOLABA),
						TempInfo1.nType,ToName,ItemData,TempInfo1.cntHyber,TempInfo1.nBagType);
					num++;
				}
				itr++;
			}
			//ChatInfo TempInfo = m_TempChatInfos.front();
			//if (TempInfo.text.size() > 0)
			//{
			//	std::string str = TempInfo.text;
			//	ExpressionManager::GetInstance().AddExpressionAni(str, 4);
			//	ShowTextInChatList(str, Color_Config.getColor(CC_CHAT_XIAOLABA));
			//	return true;
			//}
		}
	}
	return false;
}

void CUI_ID_FRAME_Speaker::RenderStarEffect()
{
	if (!m_pHornEffect)
	{	
		return;
	}

	m_pHornEffect->RestartAnimation();
}

void CUI_ID_FRAME_Speaker::CheckNeedStopHornEffect()
{
	DWORD dwCurrentTime = HQ_TimeGetTime();
	if (dwCurrentTime - m_dwStartTime >= gCfg.m_HornSetting.m_nEffectShowTime)
	{
		if (m_pHornEffect)
		{
			m_pHornEffect->StopAnimation();
		}
	}
}

void CUI_ID_FRAME_Speaker::CheckNeedRestartHornEffect()
{
	DWORD dwCurrentTime = HQ_TimeGetTime();
	if (dwCurrentTime - m_dwStartTime >= gCfg.m_HornSetting.m_nHornShowTime)
	{
		m_TempChatInfos.pop_front();

		if (RefreshCharInfo())
		{
			m_dwStartTime = dwCurrentTime;
			RenderStarEffect();
		}
	}
}

void CUI_ID_FRAME_Speaker::RenderEffect()
{
	if (!m_pHornEffect)
	{
		InitMember();
	}

	if (m_TempChatInfos.empty())
	{
		CheckNeedStopHornEffect();
		return;
	}

	CheckNeedStopHornEffect();

	CheckNeedRestartHornEffect();

}

void CUI_ID_FRAME_Speaker::Refresh(int nStartIndex)
{
	if (!m_pChatInfoText || !m_pChatInfoText->IsVisable())
		return;

	RefreshCharInfo();
}

void CUI_ID_FRAME_Speaker::InitMember()
{
	m_pChatInfoText = s_CUI_ID_FRAME_chatInfoList.GetpIDTextHorn();
	m_pHornEffect = s_CUI_ID_FRAME_chatInfoList.GetpHornProgress();
}