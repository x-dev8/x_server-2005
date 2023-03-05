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
#include "RapidXml/MeRapidXml.h"
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
#include "Rename.h"
#include "Shopping_InputBox.h"
#include "Announce.h"
#include "UiTitle.h"
#include "core/Name.h"
//#include "GraphicCodeCheck.h"
#include "winuser.h"
#include "Shopping_MessageBox.h" 
#include "NpcChatDialogBox.h"
#include "SelectBox.h"
#include "AddFriend.h"
#include "SeekPet.h"
// #include "Guild_Exp_Allot.h"

#include "ChatMessageMgr.h"
#include "Message_Chat.h"
#include "ChatInfoBox.h"
#include "Guild_Create.h"
#include "AddMember.h"
#include "Compound.h"
#include "MiniChat.h"
#include "ui/NpcTaskDialogBox.h"
#include "ui/customShortcutKey.h"
#include "UI/TaskTip.h"
#include "ShowScreenText.h"
#include "Cfg.h"
#include "MeTerrain/stdafx.h"
#include "CrossMapPF.h"
#include "BatchShop.h"
#include "ShopChangePoint.h"
#include "EditPrice.h"
#include "Speaker.h"
#include "chatcheck.h"
#include "ChatSet.h"
#include "PrivateShop.h"
//#include "WebAward.h"
#include "ChatHistory.h"

#include "SuperPassword.h"
#include "SuperPasswordReset.h"
#include "SuperPasswordRegister.h"
#include "MailMain.h"
#include "CountryInput.h"					//added by zhuomeng.hu		[8/27/2010]
#include "CountryBroadcast.h"				//added by ZhuoMeng.Hu		[8/30/2010]
#include "GoldTradeTransfer.h"
#include "ExitTip.h"
#include "ReclaimPriceInput.h"
#include "Gut.h"
#include "SeeSuAnimal.h"
#include "GuildApply.h"

using namespace Common;

extern GAME_STATE g_GameState;
extern int  MAX_CHAT_COUNT		=	110;

const int OFFSET_VALUE	= 300;

#include "MeUi/ExpressionManager.h"
#include "ui/AllNpcList.h"
//#define XML_COLDTIME_PATH	"..\\Data\\Config\\Chat.config"


extern BOOL DebugCommand( const char* pszCommand );

bool CommonChatFrame::isChatColdTimeXmlLoad = false;
//---从xml读取的 策划填写的 各个频道的冷却时间
clock_t CommonChatFrame::_tmNormalColdTime = 0;
clock_t CommonChatFrame::_tmGuildColdTime = 0;
clock_t CommonChatFrame::_tmTeamColdTime = 0;
clock_t CommonChatFrame::_tmPrivateColdTime = 0;
clock_t CommonChatFrame::_tmMessageColdTime = 0;
clock_t CommonChatFrame::_tmShoutColdTime = 0;		//大喊 9宫格
clock_t CommonChatFrame::_tmHighShoutColdTime = 0;	//高喊
clock_t CommonChatFrame::_tmLeagueColdTime = 0;	//高喊
clock_t CommonChatFrame::_tmZhenYingColdTime = 0;	//阵营
clock_t CommonChatFrame::_tmCountryColdTime = 0;	//国家
std::vector<std::string> CommonChatFrame::m_vecHelpInfo;
std::string		CommonChatFrame::_strNormalError;	
std::string		CommonChatFrame::_strGuildError;	
std::string		CommonChatFrame::_strTeamError;			//error 描述信息
std::string		CommonChatFrame::_strPrivateError;	
std::string		CommonChatFrame::_strMessageError;	
std::string		CommonChatFrame::_strShoutError;	
std::string		CommonChatFrame::_strHighShoutError;	
std::string		CommonChatFrame::_strLeagueError;	
std::string		CommonChatFrame::_strZhenYingError;	
std::string		CommonChatFrame::_strCountryError;	
int CommonChatFrame::_iNormalLevel;
int CommonChatFrame::_iGuildLevel;
int CommonChatFrame::_iTeamLevel;
int CommonChatFrame::_iPrivateLevel;
int CommonChatFrame::_iMessageLevel;
int CommonChatFrame::_iShoutLevel;
int CommonChatFrame::_iHighShoutLevel;
int CommonChatFrame::_iLeagueLevel;
int CommonChatFrame::_iZhenYingLevel;
int CommonChatFrame::_iCountryLevel;


struct SItemCallbackData : public UiCallbackDataBase
{
	SItemCallbackData(void* pData){			memcpy_s(&mItem, sizeof(mItem), pData, sizeof(mItem));}
	~SItemCallbackData(){}
	SCharItem mItem;
	virtual	void*		GetData() {return &mItem;}
	virtual int			GetType() {return eItem_UI_Callback;}
};

struct SMountCallbackData : public UiCallbackDataBase
{
	SMountCallbackData(void* pData){			memcpy_s(&mItem, sizeof(mItem), pData, sizeof(mItem));}
	~SMountCallbackData(){}
	SMountItem mItem;
	virtual	void*		GetData() {return &mItem;}
	virtual int			GetType() {return eMount_UI_Callback;}
};

struct SSkillCallBackData : public UiCallbackDataBase
{
	SSkillCallBackData( int id, int level ){ mId = id; mLevel = level; }
	~SSkillCallBackData(){}
	int mId;
	int mLevel;
	virtual	void*		GetData() {return NULL;}
	virtual int			GetType() {return eSkill_UI_Callback;}
};

struct STaskCallBackData : public UiCallbackDataBase
{
	STaskCallBackData( int id, int state ){ mId = id; mState = state; }
	~STaskCallBackData(){}
	int mId;
	int mState;
	virtual	void*		GetData() {return NULL;}
	virtual int			GetType() {return eTask_UI_Callback;}
};

struct SPetCallBackData : public UiCallbackDataBase
{
	SPetCallBackData( void* pData){ memcpy_s(&mItem,sizeof(mItem),pData,sizeof(mItem)); }
	~SPetCallBackData(){}
	SPetItem mItem;
	virtual void* GetData(){return &mItem;}
	virtual int   GetType(){return ePet_UI_Callback;}
};

//FreeTip	CommonChatFrame::m_FreeTip;
FreeTip	CommonChatFrame::m_AllFreeTip[MAX_FREETIP_COUNT];
FreeTip	CommonChatFrame::m_FreeTip;
int		CommonChatFrame::m_NoteSort[MAX_FREETIP_COUNT] = { -1, -1, -1 };
int		CommonChatFrame::m_RenderSort[MAX_FREETIP_COUNT] = { -1, -1, -1 };
int		CommonChatFrame::m_OptFreeTipId = -1;


void CommonChatFrame::CommonChatFrame_EditOnLButtonDown(ControlObject* pSender, const char* szData)
{
// 	if (pSender!= CommonChatFrame::GetActiveChatFrame()->m_pID_EDIT_INPUT)
// 	{
// 		return;
// 	}
	SetActiveChatFrameByEdit((ControlEdit*)pSender);
	ImmAssociateContext( g_hWnd, s_CUI_ID_FRAME_CREATE.GetImeInstance() );
	CommonChatFrame::GetActiveChatFrame()->ChangeImmPos();
}

CommonChatFrame::CommonChatFrame()
{
	// Member
	_Initialize();

}



void CommonChatFrame::addText( const char* text )
{
	if( NULL == text )
		return;
	m_pID_EDIT_INPUT->addText( text );
	Begin2Input();
	SetEditFocus();
	theUiManager.ToTop( m_pChatInfoBox );
// 	theUiManager.SetJumpNextLButtonUp(true);
}

void CommonChatFrame::addHyberText( const char* text, __int64 onlyId /* = 0 */, int itemid /* = 0 */, int nType /* = 0 */ )
{	
	if( NULL == text )
		return;

	if(IsSetPet)
	{
		//ShowTextInChatList( theXmlString.GetString(eText_Char_PetInfo),0xFFAA0000 );
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_FamilyEx,theXmlString.GetString(eText_Char_PetInfo));
		return;
	}

	if ( ItemHyberCnt > 0 )
	{
		if ( _nBagType != nType ||  _HyberType[0] != MsgChat::HYBERTYPE_ITEM )
		{
			//ShowTextInChatList( theXmlString.GetString(eText_AddInfo_BagTypeErr),0xFFAA0000 );
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_FamilyEx,theXmlString.GetString(eText_AddInfo_BagTypeErr));
			return;
		}
	}

	if( ItemHyberCnt >= ITEM_HYBER_MAX_CNT )
	{
		std::string strEdit = m_pID_EDIT_INPUT->GetText();
		std::string::size_type nLeftPos = strEdit.find('[');
		std::string::size_type nRightPos = strEdit.find(']');

		if ((nLeftPos != std::string::npos) && (nRightPos != std::string::npos) && (nRightPos > nLeftPos + 1))
		{
			//ShowTextInChatList( theXmlString.GetString(eClient_AddInfo_2slk_5),0xFFAA0000 );
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_FamilyEx,theXmlString.GetString(eClient_AddInfo_2slk_5));
			return;
		}
		else
		{
			ItemHyberCnt = 0;
			IsSetPet = false;
		}
	}

	//for( int i=0; i<ITEM_HYBER_MAX_CNT; i++)
	//{
	//	if( strcmp(_saveItemHyber[i].c_str(), text) == 0 )
	//	{
	//		ShowTextInChatList( theXmlString.GetString(eClient_AddInfo_2slk_6) );
	//		return;
	//	}
	//}

	std::string strAddText = text;
	strAddText.insert(0, "[");
	strAddText.insert(strAddText.length(), "]");
	m_pID_EDIT_INPUT->addText( strAddText.c_str() );
	Begin2Input();
	SetEditFocus();
// 	theUiManager.SetJumpNextLButtonUp(true);

	if( onlyId != 0 )
	{
		_HyberType[ItemHyberCnt] = MsgChat::HYBERTYPE_ITEM;
		_HyberItemInfo[ItemHyberCnt] = onlyId;
		_HyberItemId[ItemHyberCnt] = itemid;
		_saveItemHyber[ItemHyberCnt] = text;
		_nBagType = nType;

		++ItemHyberCnt;
	}

	RefreshHyberCnt();
}

void CommonChatFrame::EditDataChange( OUT ControlObject* pSender, OUT const char *szData )
{
	CommonChatFrame::GetActiveChatFrame()->RefreshHyberCnt();
}

void CommonChatFrame::RefreshHyberCnt()
{
	if ( ItemHyberCnt <= 0 || !m_pID_EDIT_INPUT )
		return;

	std::string str = m_pID_EDIT_INPUT->GetText();
	if ( str.length() <= 0 )
	{
		ClearHyberLinks();
		_nBagType = 0;
		return;
	}

	struct SHyber 
	{
		SHyber()
		{
			bUsed = false;
		}
		std::string strName;
		bool bUsed;
	};

	SHyber sHyber[ITEM_HYBER_MAX_CNT];

	size_t npos1 = str.find( '[' );
	size_t npos2 = str.find( ']', npos1 );

	int nIndex = 0;
	while ( npos1 != std::string::npos && npos2 != std::string::npos && nIndex < ITEM_HYBER_MAX_CNT )
	{
		sHyber[nIndex].strName = str.substr( npos1 + 1, npos2 - npos1 - 1 );
		npos1 = str.find( '[', npos2 + 1 );
		npos2 = str.find( ']', npos1 );
		nIndex++;
	}

	for ( int i = 0; i < ITEM_HYBER_MAX_CNT; i++ )
	{
		std::string strText = _saveItemHyber[i];

		if ( strText.length() > 0 )
		{
			bool bFind = false;
			for ( int j = 0; j < ITEM_HYBER_MAX_CNT; j++ )
			{
				if ( strcmp( strText.c_str(), sHyber[j].strName.c_str() ) == 0 && !sHyber[j].bUsed )
				{
					sHyber[j].bUsed = true;
					bFind = true;
					break;
				}
			}

			if (!bFind)
			{
				_HyberType[i] = 0;
				_HyberItemInfo[i] = 0;
				_HyberItemId[i] = 0;
				_saveItemHyber[i].clear();

				ItemHyberCnt--;
			}
		}
	}

	if ( ItemHyberCnt <= 0 )
	{
		ClearHyberLinks();
		_nBagType = 0;
		return;
	}

	for ( int i = 0; i < ITEM_HYBER_MAX_CNT - 1; i++ )
	{
		for ( int j = i + 1; j < ITEM_HYBER_MAX_CNT; j++ )
		{
			if ( _HyberItemId[i] == 0 && _HyberItemId[j] != 0 )
			{
				_HyberType[i] = _HyberType[j];
				_HyberType[j] = 0;

				_HyberItemInfo[i] = _HyberItemInfo[j];
				_HyberItemInfo[j] = 0;

				_HyberItemId[i] = _HyberItemId[j];
				_HyberItemId[j] = 0;

				_saveItemHyber[i] = _saveItemHyber[j];
				_saveItemHyber[j].clear();
			}
		}
	}

	for ( int i = 0; i < ITEM_HYBER_MAX_CNT - 1; i++ )
	{
		if ( strcmp( sHyber[i].strName.c_str(), _saveItemHyber[i].c_str() ) != 0 )
		{
			for ( int j = i; j < ITEM_HYBER_MAX_CNT; j++ )
			{
				if ( strcmp( sHyber[i].strName.c_str(), _saveItemHyber[j].c_str() ) == 0 )
				{
					uint8 nType = _HyberType[i];
					__int64 nOnlyId = _HyberItemInfo[i];
					int nItemId = _HyberItemId[i];
					std::string strName = _saveItemHyber[i];

					_HyberType[i] = _HyberType[j];
					_HyberItemInfo[i] = _HyberItemInfo[j];
					_HyberItemId[i] = _HyberItemId[j];
					_saveItemHyber[i] = _saveItemHyber[j];

					_HyberType[j] = nType;
					_HyberItemInfo[j] = nOnlyId;
					_HyberItemId[j] = nItemId;
					_saveItemHyber[j] = strName;

					break;
				}
			}
		}
	}
}

void CommonChatFrame::addHyberTextEx( const char* text, uint8 hyberType, int id, int level )
{
	if( NULL == text )
		return;

	if(IsSetPet)
	{
		//ShowTextInChatList( theXmlString.GetString(eText_Char_PetInfo),0xFFAA0000 );
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_FamilyEx,theXmlString.GetString(eText_Char_PetInfo));
		return;
	}

	if ( ItemHyberCnt > 0 )
	{
		if ( _HyberType[0] != hyberType )
		{
			//ShowTextInChatList( theXmlString.GetString(eText_AddInfo_BagTypeErr),0xFFAA0000 );
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_FamilyEx,theXmlString.GetString(eText_AddInfo_BagTypeErr));
			return;
		}
	}

	if( ItemHyberCnt >= ITEM_HYBER_MAX_CNT )
	{
		std::string strEdit = m_pID_EDIT_INPUT->GetText();
		std::string::size_type nLeftPos = strEdit.find('[');
		std::string::size_type nRightPos = strEdit.find(']');

		if ((nLeftPos != std::string::npos) && (nRightPos != std::string::npos) && (nRightPos > nLeftPos + 1))
		{
			//ShowTextInChatList( theXmlString.GetString(eClient_AddInfo_2slk_5),0xFFAA0000 );
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_FamilyEx,theXmlString.GetString(eClient_AddInfo_2slk_5));
			return;
		}
		else
		{
			ItemHyberCnt = 0;
			IsSetPet = false;
		}
	}

	std::string strAddText = text;
	strAddText.insert(0, "[");
	strAddText.insert(strAddText.length(), "]");
	m_pID_EDIT_INPUT->addText( strAddText.c_str() );
	Begin2Input();
	SetEditFocus();


	_HyberType[ItemHyberCnt] = hyberType;
	_HyberItemInfo[ItemHyberCnt] = id;
	_HyberItemId[ItemHyberCnt] = level;
	_saveItemHyber[ItemHyberCnt] = text;

	++ItemHyberCnt;

	RefreshHyberCnt();
}


void CommonChatFrame::SendMsgChatNormal(const char* chat)
{
	std::string strChat = chat;
	//strChat = CChatCheck::getInstance()->CheckStringInLowMark((char*)chat, '*');

	MsgChat msg( MsgChat::CHAT_TYPE_NORMAL );
	msg.type = BT_All;
	strncpy( msg.chatHeader.szToName, thePlayerRole.GetName(), MAX_NAME_STRING-1 );
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


BOOL CommonChatFrame::EditInputIsVisable()
{
	if( m_pID_EDIT_INPUT )
	{
		bool bRet = (theUiManager.GetFocus() ==m_pID_EDIT_INPUT);
		if (bRet && this == &s_CUI_ChatInfoBox)
		{
			g_bMessageChat = false;
		}
		return bRet;

	}
	return FALSE;
}

void CommonChatFrame::Begin2Input()
{
	ImmAssociateContext( g_hWnd, s_CUI_ID_FRAME_CREATE.GetImeInstance() );

	static ControlObject *pLastObject = NULL;
	if ( theUiManager.GetFocus() == m_pID_EDIT_INPUT )
	{
		if(m_bEdtActive)
			m_bEdtActive = !m_bEdtActive;
	}
	else
	{
// 		pLastObject = theUiManager.ToTop( m_pChatInfoBox );
		m_pID_EDIT_INPUT->SetActivate(true);
		if( !m_bEdtActive)
			m_bEdtActive = !m_bEdtActive;
	}
}


void CommonChatFrame::ChangeImmPos()
{
	static bool set = true;
	if (!set)
		return;

	POINT pt;
	pt.x = 100;
	pt.y = 100;
	RECT rt;
	m_pID_EDIT_INPUT->GetRealRect(&rt);
	pt.x = rt.left + 10 * ControlObject::GetSCALE(m_pID_EDIT_INPUT);
	pt.y = rt.bottom + 10 * ControlObject::GetSCALE(m_pID_EDIT_INPUT);

	RECT rcClient;
	::GetClientRect(g_hWnd, &rcClient);

	RECT rcWin;
	::GetWindowRect(g_hWnd, &rcWin);

	pt.x += rcWin.left + (rcWin.right - rcWin.left) - (rcClient.right - rcClient.left);
	pt.y += rcWin.top + (rcWin.bottom - rcWin.top) - (rcClient.bottom - rcClient.top);

	ImmSetStatusWindowPos( s_CUI_ID_FRAME_CREATE.GetImeInstance(), &pt );
}



bool CommonChatFrame::ChatMsgProc( UINT msg, WPARAM wParam, LPARAM lParam, bool bMsgUsed,ControlObject* pSender )
{
	if (CommonChatFrame::GetActiveChatFrame() && pSender == CommonChatFrame::GetActiveChatFrame()->m_pChatInfoBox)
	{
		return CommonChatFrame::GetActiveChatFrame()->MsgProc(msg, wParam, lParam, bMsgUsed,pSender);
	}
	return false;
}

bool CommonChatFrame::MsgProc( UINT msg, WPARAM wParam, LPARAM lParam, bool bMsgUsed ,ControlObject* pSender)
{
	if ( (bMsgUsed == true && WM_MOUSEMOVE != msg) || g_GameState != G_MAIN )
		return false;	

	switch( msg ) 
	{
	case WM_LBUTTONDOWN:
		{		
		/*	if( m_FreeTip.PtInCloseBtn( theUiManager.m_ptMoust.x, theUiManager.m_ptMoust.y ) )
			{
				return true;
			}*/

			//=======================================================
			// newAdd
			if ( PtInAllFreeTipBtn( theUiManager.m_ptMoust.x, theUiManager.m_ptMoust.y ) > -1 )
			{
				return true;
			}

			//// 如果在框内，截断消息
			//if ( PtInAllFreeTip( theUiManager.m_ptMoust.x, theUiManager.m_ptMoust.y ) > -1 )
			//{
			//	return true;
			//}

			bool ret = FreeTipMoveBeginProc( theUiManager.m_ptMoust.x, theUiManager.m_ptMoust.y );
			if ( ret == true )
			{
				return true;
			}

			break;
		}
	case WM_LBUTTONUP:
		{			

			//=======================================================
			// newAdd
			//int idx = PtInAllFreeTipBtn( theUiManager.m_ptMoust.x, theUiManager.m_ptMoust.y );
			//if ( idx > -1 )
			//{
			//	m_AllFreeTip[idx].ShowItemTip( false );

			//	// 清理下记录的ID号(中，左，右用的)
			//	ClearNoteId( idx );
			//	// 清理下记录的显示排序ID
			//	FreeTipEraseStack( idx );

			//	return true;
			//}

			bool ret = FreeTipMoveEndProc( theUiManager.m_ptMoust.x, theUiManager.m_ptMoust.y );

			if ( ret == true )
			{
				return true;
			}

			break;
		}
	case WM_MOUSEMOVE:
		{
			POINT pt = {0};
			pt.x = LOWORD( lParam );
			pt.y = HIWORD( lParam );
			m_ptMouseMove = pt;

			bool ret = FreeTipMoveProc( theUiManager.m_ptMoust.x, theUiManager.m_ptMoust.y );

			if ( ret == true )
			{
				return true;
			}
			
			//{
			//	TRACKMOUSEEVENT tme;
			//	tme.cbSize = sizeof(tme);				
			//	tme.dwFlags = TME_LEAVE;
			//             tme.hwndTrack = g_hWnd;
			//    _TrackMouseEvent(&tme);
			//}
			break;
		}
	case WM_KEYDOWN:
		{			
			switch( wParam ) 
			{
			case VK_UP:
				{
					if (++currChatHistoryIndex_ < chatHistories_.size())
					{
						const ChatHistory& chis = chatHistories_[currChatHistoryIndex_];
						*m_pID_EDIT_INPUT = chis.chatInfo;
						ItemHyberCnt = chis.hyberItemIds.size();
						for (int i = 0; i < ItemHyberCnt; ++i)
						{
							_HyberItemInfo[i] = chis.hyberItemInfos[i];
							_HyberItemId[i] = chis.hyberItemIds[i];
						}
						nAddressHyberCnt = chis.nAddressHyberCnt;
					}
					else
						currChatHistoryIndex_ = chatHistories_.size() - 1;

				}
				break;
			case VK_DOWN:
				{
					if (--currChatHistoryIndex_ >= 0)
					{
						const ChatHistory& chis = chatHistories_[currChatHistoryIndex_];
						*m_pID_EDIT_INPUT = chis.chatInfo;
						ItemHyberCnt = chis.hyberItemIds.size();
						for (int i = 0; i < ItemHyberCnt; ++i)
						{
							_HyberItemInfo[i] = chis.hyberItemInfos[i];
							_HyberItemId[i] = chis.hyberItemIds[i];
						}
						nAddressHyberCnt = chis.nAddressHyberCnt;
					}
					else
						currChatHistoryIndex_ = -1;
				}
				break;
			}

			if( wParam == VK_RETURN)
			{
				if( 
 					s_CUI_InputBox.IsVisable() ||	
 					s_CUI_ID_FRAME_MessageBox.IsVisable() || 
					s_CUI_ID_FRAME_ChatHistory.IsVisable() ||
 					s_CUI_ID_FRAME_Rename.IsVisable() ||
					s_CUI_ID_FRAME_ADD_MEMBER.IsVisable() ||
					 s_CUI_ID_FRAME_Announce.IsVisable()||
					s_CUI_ID_FRAME_GUILD_CREATE.IsVisable() || 
					s_CUI_ID_FRAME_custom.IsVisable() ||
					s_CUI_ID_FRAME_EditPrice.IsVisable() ||
					s_CUI_ID_FRAME_ShopChangePoint.IsVisable() ||
					s_CUI_ID_FRAME_BatchShop.IsVisable() ||
					s_CUI_ID_FRAME_ChatSet.IsVisable() ||
					//s_CUI_ID_FRAME_WebAward.IsVisable() ||
					s_CUI_ID_FRAME_SuperPassword.IsVisable() ||
					s_CUI_ID_FRAME_SuperPasswordReset.IsVisable() ||
					s_CUI_ID_FRAME_SuperPasswordRegister.IsVisable()||
                    s_CUI_ID_FRAME_MailMain.IsHaveFocus()/*IsVisable()*/ ||
					s_CUI_ID_FRAME_GoldTradeDeposit.IsVisable()||
					s_CUI_ID_FRAME_CountryInput.IsVisable()||					//added by zhuomeng.hu		[8/27/2010]
					s_CUI_ID_FRAME_CountryBroadcast.IsVisable()||					//added by ZhuoMeng.Hu		[8/30/2010]
					s_CUI_ID_FRAME_ExitTip.IsVisable()||
					s_CUI_ID_FRAME_AddFriend.IsVisable()||
                    s_CUI_ID_FRAME_Reclaim.IsVisable() ||
					s_CUI_ID_FRAME_Gut.IsVisable() ||
					s_CUI_ID_FRAME_Title.IsVisable() ||
					s_CUI_ID_FRAME_GuildApply.IsVisable()
                    )
				{
					bool isFocus = theUiManager.GetFocus() == m_pID_EDIT_INPUT;
					if (!isFocus)
						return false;
				}

				if (s_CUI_ID_FRAME_Compound.IsUILoad() && theUiManager.GetFocus() == s_CUI_ID_FRAME_Compound.GetEditNumber() )
					return false;

// 				if ( theUiManager.GetFocus() != m_pID_EDIT_INPUT && s_CUI_ID_FRAME_CodeCheck.IsVisable() )
// 				{
// 					return false;
// 				}

				if ( theUiManager.GetFocus() == m_pID_EDIT_INPUT )
				{
					_bActiveInput = true;

					return false;
				}
				else
				{
					_bActiveInput = false;

					Begin2Input();

					if(!m_bEdtActive)
					{
						m_pID_EDIT_INPUT->SetActivate( false );
						if (!g_bMessageChat)
						{
							m_pChatInfoBox->SetVisable(false);
						}
						s_CUI_ID_FRAME_FACE.SetVisable( false );
						ImmAssociateContext( g_hWnd, NULL );
					}
					else
					{
						m_pID_EDIT_INPUT->SetActivate(true);
						if (!g_bMessageChat)
							m_pChatInfoBox->SetVisable(true);

						ImmAssociateContext( g_hWnd, s_CUI_ID_FRAME_CREATE.GetImeInstance() );
						ChangeImmPos();

						if( strlen(m_pID_EDIT_INPUT->GetText()) > 0 )
							return true;
						InializeChatByChannel();
					}

					return true;
				}
			}
			else if (wParam == VK_TAB)
			{
				if (this == &s_CUI_ChatInfoBox)
				{
					int i = 0;
				}
			}
		}
		break;
	case WM_KEYUP:
		{	
			switch( wParam )
			{
			case VK_ESCAPE:
				{
					if ( IsShow() )
					{
						_bActiveInput = true;
						ID_EDIT_INPUTOnEditEnter( m_pID_EDIT_INPUT, "" );
						_bActiveInput = false;
						if (this != &s_CUI_ChatInfoBox && this != &s_CUI_ID_FRAME_Speaker)
						{
							g_bMessageChat = false;
							s_CUI_ID_FRAME_MiniChat.AddMiniPlayerListName(m_szPrivateToName.c_str());
							SetShow( false );
						}
						return true;
					}
				}
				break;
			case VK_RETURN:
				{
					if( IsShow() )
					{
						if( theUiManager.GetFocus() != m_pID_EDIT_INPUT )//正在输入框
						{
							// 发送出去
							_bActiveInput = true;
							ID_EDIT_INPUTOnEditEnter( m_pID_EDIT_INPUT, m_pID_EDIT_INPUT->GetText() ); 							
							_bActiveInput = false;
							
						}
					}

					if (m_bSendMsg)
					{
						m_bSendMsg = false;
						return true;
					}
				}
				break;
			}
			
			
		}break;
	}
	return false;
}


extern short GetKeyboardInput( int iKey );
#include "Dxsdk/dinput.h"
void CommonChatFrame::HyberRBtnDown( ControlObject* pSender, const char* szName  ,int eHyberType)
{	
	// 判断是否带(VIP)字样
	char szCorrectName[256] = {0};
	char szTemp[256] = {0};
	strncpy( szCorrectName, szName, sizeof(szCorrectName)-1 );
	strncpy( szTemp, szName, sizeof(szTemp)-1 );
	char *p = strstr( szTemp, "(VIP)" );
	if( p != NULL )
	{
		*p = 0;
		if( theHeroGame.GetPlayerMgr() && theHeroGame.GetPlayerMgr()->IsVipPlayer(szTemp) )
		{
			strncpy( szCorrectName, szTemp, sizeof(szCorrectName)-1 );
		}
	}

	if (eHyberType & (eKeyAddress|eKeyNpc))
	{
		if( GetKeyboardInput(DIK_LSHIFT) || GetKeyboardInput(DIK_RSHIFT) )
		{
			char cContent[256] = {0};
			strncpy(cContent, szCorrectName, sizeof(cContent)-1);
			int nLength = strlen(cContent);
			for (int i = 0; i < nLength; ++i )
			{
				if (cContent[i] == '(' || cContent[i] == ',' ||cContent[i] == ')')
				{
					cContent[i] = ' ';
				}
			}
			char cMapName[256] = {0};
			int MapX,MapY;

			sscanf(cContent,"%s %d %d",cMapName,&MapX,&MapY);

			short nMeCountry = -1;
			CPlayer* pMe = theHeroGame.GetPlayerMgr()->GetMe();
			if (pMe)
			{
				nMeCountry = pMe->GetRealCountry();
			}
			CWorldTile* pTile = SwGlobal::GetWorld()->GetWorldBuffer()->GetTileFromTileName(cMapName,nMeCountry);
			if (NULL == pTile)
			{
				return ;
			}
			if ((MapX < 0.f )|| (MapX > pTile->GetWidth() - 1) || (MapY < 0.f) || (MapY > pTile->GetDepth() - 1))
			{
				return;
			}
			s_CUI_ID_FRAME_AllNpcList.ShowTile(pTile,MapX,MapY);
			return;
		}
	}
	else
	{
		if( strcmp(thePlayerRole.GetName(), szCorrectName) == 0 )
			return;
//HEROONLINE-609
// 		if( NpcCoord::getInstance()->hasName(szCorrectName) )
// 			return;

		int x,y;
		x = theUiManager.m_ptMoust.x;
		y = theUiManager.m_ptMoust.y;

		CPlayer* pPlayer = theHeroGame.GetPlayerMgr()->FindByName( szCorrectName );
		if( pPlayer )
		{
			s_CUI_ID_FRAME_Target.SetPlayer( pPlayer->GetID() );
			// 		s_CUI_ID_FRAME_RBTNMENU.SetPlayerID(pPlayer->GetID());
		}
		else
		{
			s_CUI_ID_FRAME_Target.SetPlayer( -1 );
			// 		s_CUI_ID_FRAME_RBTNMENU.SetPlayerID(-1);
		}

		s_CUI_ID_FRAME_RBTNMENU.SetPrivateName( szCorrectName );
		s_CUI_ID_FRAME_RBTNMENU.SetVisable( true);
		s_CUI_ID_FRAME_RBTNMENU.SetPos( x, y );
		if( s_CUI_ID_FRAME_RBTNMENU.GetFrame() )
			theUiManager.ToTop( s_CUI_ID_FRAME_RBTNMENU.GetFrame() );
		theUiManager.Compositor();

	}
}

void CommonChatFrame::HyberMountClick( ControlObject* pSender, void* pData )
{
	SMountCallbackData* pMountData = (SMountCallbackData*)pData;
	if ( !pMountData )
		return;

	SMountItem sMountItem;
	memcpy_s(&sMountItem,sizeof(SMountItem),pMountData->GetData(),sizeof(SMountItem));
	s_CUI_ID_FRAME_SeekPet.SetVisable(true);
	s_CUI_ID_FRAME_SeekPet.SetMount( sMountItem );
}

void CommonChatFrame::HyberItemClick( ControlObject* pSender, unsigned char* pItem)
{
// 	if (pSender != CommonChatFrame::GetActiveChatFrame()->m_pChatInfoText)
// 	{
// 	}

	// 同时只显示一个Tip
	//if( NULL == pItem )
	{
		//GetActiveChatFrame()->m_FreeTip.ShowItemTip( false );

		// 如果出错所有tip消失，照抄原来的逻辑
		GetActiveChatFrame()->HideAllFreeTip();
		//return;	
	}
	SCharItem stItem;
	memcpy_s( &stItem, sizeof( stItem ), pItem, sizeof( stItem ) );
	//if( GetActiveChatFrame()->m_mapReceivedMount.find( stItem.itembaseinfo.nOnlyInt ) != 
	//	GetActiveChatFrame()->m_mapReceivedMount.end() )// found, it's mount
	//{
	//	SMountItem* pMount = &GetActiveChatFrame()->m_mapReceivedMount[stItem.itembaseinfo.nOnlyInt];
	//	if( !pMount )
	//		return;
	//	s_CUI_ID_FRAME_SeekPet.SetVisable(true);
	//	s_CUI_ID_FRAME_SeekPet.SetMount( *pMount );
	//}
	//else
	{
		ItemDefine::SItemCommon* pCommon = (ItemDefine::SItemCommon*)GettheItemDetail().GetItemByID( stItem.itembaseinfo.ustItemID );
		if( !pCommon )
			return;
		//GetActiveChatFrame()->m_FreeTip.SetData( &stItem, theUiManager.m_ptMoust.x, theUiManager.m_ptMoust.y, true );

		//=======================================================
		// newAdd

		// 没有空的位置就不显示新的
		int freePosId = GetActiveChatFrame()->FindFreeTipPosId();

		if ( freePosId == POS_INVALID )
		{
			return ;
		}

		int x = 0;
		int y = 0;

		int freeTipId = GetActiveChatFrame()->FindFreeTipId();
		freeTipId = ( freeTipId == -1 ) ? 0 : freeTipId;
		GetActiveChatFrame()->m_AllFreeTip[freeTipId].SetData( &stItem, theUiManager.m_ptMoust.x, theUiManager.m_ptMoust.y, false );

		int width = GetActiveChatFrame()->m_AllFreeTip[freeTipId].GetFreeTipW();

		// 根本位置ID，算出FreeTip出现的位置
		switch ( freePosId )
		{
		case POS_MID:
			{
				x = SCREEN_WIDTH / 2 - width / 2;
				y = 2 * SCREEN_HEIGHT / 5;
			}
			break;
		case POS_RIGHT:
			{
				x = SCREEN_WIDTH / 2 + OFFSET_VALUE - width / 2;
				y = 2 * SCREEN_HEIGHT / 5;
			}
			break;
		case POS_LEFT:
			{
				x = SCREEN_WIDTH / 2 - OFFSET_VALUE - width / 2;
				y = 2 * SCREEN_HEIGHT / 5;
			}
			break;
		}

		GetActiveChatFrame()->m_AllFreeTip[freeTipId].SetTipPos( x, y );

		// 相互记录下ID号
		GetActiveChatFrame()->m_AllFreeTip[freeTipId].SetPosId( (FreeTipPos)freePosId );
		m_NoteSort[freePosId] = freeTipId;
		GetActiveChatFrame()->FreeTipPushStack( freeTipId );

	}
}

void CommonChatFrame::HyberSkillClick( ControlObject* pSender, void* pData )
{
	SSkillCallBackData* pSkillData = (SSkillCallBackData*)pData;
	if ( !pSkillData )
		return;
	//SCharSkill *pCharSkill = thePlayerRole.m_SkillBag.GetSkillByID(pSkillData->mId);
	//if(NULL == pCharSkill /*|| !IsValidXinFaSkill(pCharSkill)*/)
	//{
	//	return;
	//}

	//ItemDefine::SItemSkill* pItemSKill = GettheItemDetail().GetSkillByID( pCharSkill->ustSkillID, pCharSkill->stSkillLevel );
	//if ( pItemSKill == NULL )
	//{
	//	return;
	//}

	// 没有空的位置就不显示新的
	int freePosId = GetActiveChatFrame()->FindFreeTipPosId();

	if ( freePosId == POS_INVALID )
	{
		return ;
	}

	int x = 0;
	int y = 0;

	int freeTipId = GetActiveChatFrame()->FindFreeTipId();
	freeTipId = ( freeTipId == -1 ) ? 0 : freeTipId;
	GetActiveChatFrame()->m_AllFreeTip[freeTipId].SetSkillData( pSkillData->mId, pSkillData->mLevel, theUiManager.m_ptMoust.x, theUiManager.m_ptMoust.y, false );

	int width = GetActiveChatFrame()->m_AllFreeTip[freeTipId].GetFreeTipW();

	// 根本位置ID，算出FreeTip出现的位置
	switch ( freePosId )
	{
	case POS_MID:
		{
			x = SCREEN_WIDTH / 2 - width / 2;
			y = 2 * SCREEN_HEIGHT / 5;
		}
		break;
	case POS_RIGHT:
		{
			x = SCREEN_WIDTH / 2 + OFFSET_VALUE - width / 2;
			y = 2 * SCREEN_HEIGHT / 5;
		}
		break;
	case POS_LEFT:
		{
			x = SCREEN_WIDTH / 2 - OFFSET_VALUE - width / 2;
			y = 2 * SCREEN_HEIGHT / 5;
		}
		break;
	}

	GetActiveChatFrame()->m_AllFreeTip[freeTipId].SetTipPos( x, y );

	// 相互记录下ID号
	GetActiveChatFrame()->m_AllFreeTip[freeTipId].SetPosId( (FreeTipPos)freePosId );
	m_NoteSort[freePosId] = freeTipId;
	GetActiveChatFrame()->FreeTipPushStack( freeTipId );

}

void CommonChatFrame::HyberTaskClick( ControlObject* pSender, void* pData )
{
	STaskCallBackData* pTaskData = (STaskCallBackData*)pData;
	if ( !pTaskData )
		return;

	s_CUI_ID_FRAME_TaskTip.SetVisable(true);
	s_CUI_ID_FRAME_TaskTip.UITask_ShowInfo( pTaskData->mId );
}

void CommonChatFrame::HyberPetClick( ControlObject* pSender, void* pData )
{
	SPetCallBackData* pPetData = (SPetCallBackData*)pData;
	if ( !pPetData )
		return;

	SPetItem pPetItem;
	memcpy_s(&pPetItem,sizeof(SPetItem),pPetData->GetData(),sizeof(SPetItem));
	s_CUI_ID_FRAME_SeeSuAnimal.SetVisable(true);
	s_CUI_ID_FRAME_SeeSuAnimal.SetPetItem(pPetItem);
}

void CommonChatFrame::HyberItemEnter( ControlObject* pSender, unsigned char* pItem )
{
	if( NULL == pItem )
	{
		m_FreeTip.ShowItemTip( false );
		return;	
	}
	SCharItem stItem;
	memcpy_s( &stItem, sizeof( stItem ), pItem, sizeof( stItem ) );
	if( GetActiveChatFrame()->m_mapReceivedMount.find( stItem.itembaseinfo.nOnlyInt ) != 
		GetActiveChatFrame()->m_mapReceivedMount.end() )// found, it's mount
	{
		SMountItem* pMount = &GetActiveChatFrame()->m_mapReceivedMount[stItem.itembaseinfo.nOnlyInt];
		if( !pMount )
			return;
		s_CUI_ID_FRAME_SeekPet.SetVisable(true);
		s_CUI_ID_FRAME_SeekPet.SetMount( *pMount );
	}
	else
	{
		ItemDefine::SItemCommon* pCommon = (ItemDefine::SItemCommon*)GettheItemDetail().GetItemByID( stItem.itembaseinfo.ustItemID );
		if( !pCommon )
			return;

		GetActiveChatFrame()->m_FreeTip.SetData( &stItem, theUiManager.m_ptMoust.x, theUiManager.m_ptMoust.y, false, false );
	}
}

void CommonChatFrame::HyberItemLevel(ControlObject* pSender, unsigned char* pItem )
{
	m_FreeTip.ShowItemTip( false );
}

void CommonChatFrame::SetEdtActive( bool bFlag )
{
	//m_FreeTip.ShowItemTip( false );
	//======================================

	// addNew ,抄原逻辑
	HideAllFreeTip();
	if (m_bEdtActive != bFlag)
	{
		m_pID_EDIT_INPUT->SetActivate(bFlag);
		m_bEdtActive = bFlag;
	}

}


void CommonChatFrame::ShowTextInChatList(const std::string& str, const D3DCOLOR col,int nConver , char *szToName , 
										 char* itemData ,int useHyberCnt, int nBagType, MsgChat* msg /*= NULL*/ )
{
	if ( str.size() > 0 && m_pChatInfoText )
	{

// 		bool bMoveDown = m_pChatInfoText->GetScrollBar()->GetValue() == m_pChatInfoText->GetScrollBar()->GetMaxValue();

		ControlList::S_List	stItem;
		stItem.UseSelColor = false;

		if( m_pChatInfoText->GetFontSize() == 0 )
			return;

		UiCallbackDataArr callBackDataArr;
		void* pItemHyber = itemData;
		for (int nIndex = 0; nIndex < useHyberCnt; ++nIndex)
		{
			if ( msg == NULL || msg->ehyberType[nIndex] == MsgChat::HYBERTYPE_ITEM )
			{
				if (nBagType == BT_MountBag)
				{
					pItemHyber = itemData + sizeof(SMountItem)*nIndex;
					SCharItem stTempItem;
					SMountItem* pDrome = (SMountItem*)pItemHyber;
					stTempItem.itembaseinfo.ustItemID = pDrome->baseInfo.id;				
					stTempItem.itembaseinfo.nOnlyInt = pDrome->baseInfo.guid;
					m_mapReceivedMount[pDrome->baseInfo.guid] = *pDrome;
					callBackDataArr.push_back(MeNew /*SItemCallbackData(&stTempItem)*/SMountCallbackData(pDrome)) ;
				}
				else if(nBagType == BT_PetBag)
				{
					pItemHyber = itemData + sizeof(SPetItem) * nIndex;
					SPetItem *pPetItem = (SPetItem*)pItemHyber;
					callBackDataArr.push_back(MeNew SPetCallBackData(pPetItem));
				}
				else
				{
					pItemHyber = itemData +  sizeof(SCharItem)*nIndex;
					callBackDataArr.push_back(MeNew SItemCallbackData(pItemHyber));
				}
			}
			else if ( msg->ehyberType[nIndex] == MsgChat::HYBERTYPE_SKILL )
			{
				callBackDataArr.push_back(MeNew SSkillCallBackData( msg->onlyId[nIndex], msg->itemId[nIndex] ));
			}
			else if ( msg->ehyberType[nIndex] == MsgChat::HYBERTYPE_TASK )
			{
				callBackDataArr.push_back(MeNew STaskCallBackData( msg->onlyId[nIndex], msg->itemId[nIndex] ));
			}

		}

		//std::string finalStr = str;
		//NpcCoord::getInstance()->addNpcHyberForText(finalStr,NpcCoord::eMapId, -1/*CURRENTTILE->GetMapId()*/,&callBackDataArr);

		std::wstring strWide = Common::_tstring::toWideString(str.c_str());
		m_pChatInfoText->AddNewLine(strWide.c_str(),col,&callBackDataArr);

		if (m_bNeedMoveDown && m_pChatInfoText->IsScrollBarVisable())
		{
			m_bNeedMoveDown = false;
			m_pChatInfoText->ScrollToTheLast();
		}

		if (this == &s_CUI_ChatInfoBox)
		{
			if (m_pChatInfoText->IsScrollBarVisable() )
			{
				ControlScrollBar* pScrollBar = m_pChatInfoText->GetScrollBar();
				if (pScrollBar->GetValue() == pScrollBar->GetMaxValue())
				{
					s_CUI_ID_FRAME_chatInfoList.ShowLowButtonEffect(false);
				}
				else
				{
					s_CUI_ID_FRAME_chatInfoList.ShowLowButtonEffect(true);
				}
				
			}
		}
// 		int startCP = 0;
// 		int endCP = strWide.length();
// 		int width = ControlHelper::Get().GetTextWidth(strWide,
// 			m_pChatInfoText->GetFontHDC(),
// 			startCP, endCP,m_pChatInfoText, m_pChatInfoText->GetFontIndex() );
// 		int listWidth = m_pChatInfoText->GetWidth();
// 		while (width > listWidth)
// 		{
// 			--endCP;
// 			width = ControlHelper::Get().GetTextWidth(strWide,
// 				m_pChatInfoText->GetFontHDC(),
// 				startCP, endCP,m_pChatInfoText, m_pChatInfoText->GetFontIndex());
// 		}


// 		int nWidthByte = endCP;
// 
// 		if ( (int)strWide.size() > 	nWidthByte )
// 		{
// 			Hyber_Type eItemHyberType = hyber_init_none;
// 
// 			int nHyberBeg = 0;
// 			int nHyberEnd = 0;
// 
// 			int nSecondHyberBeg = 0;
// 			int nSecondHyberEnd = 0;
// 
// 			int nThreeHyberBeg = 0;
// 			int nThreeHyberEnd = 0;
// 
// 			// 这里要进行相应的分析 分析物品连接是否添加的第二行了
// 			if( useHyberCnt > 0 )
// 			{
// 
// 				guard(add_2_1);
// 
// 				nHyberBeg = strWide.find( L"[" );
// 				nHyberEnd = strWide.find( L"]", nHyberBeg );
// 				int swapsign = strWide.find( L"[", nHyberBeg + 1);
// 				int willisHyberBeg = 0;
// 				while( swapsign != -1 && swapsign < nHyberEnd )
// 				{
// 					//这样抛弃第一个"["
// 					willisHyberBeg = swapsign;
// 					swapsign = strWide.find( L"[", swapsign + 1 );
// 
// 					if( swapsign == -1 || swapsign > nHyberEnd )
// 					{
// 						nHyberBeg = willisHyberBeg;
// 						break;
// 					}
// 				}
// 
// 				unguard;
// 
// 				switch( useHyberCnt )
// 				{//最多三个物品链接
// 				case 1:
// 					{
// 						std::wstring ItemName;
// 
// 						guard(add_2_2);
// 
// 						if( nHyberBeg == -1 || nHyberEnd == -1 )
// 							break;
// 
// 						if( nHyberEnd <= nHyberBeg )
// 						{
// 							break;
// 						}
// 						guard(discredit0);
// 						//这里需要进行名字分析了 确定玩家那个是自己在edit上输入进去的 还是用物品右键粘贴上去的
// 						ItemName = strWide.substr( nHyberBeg + 1, nHyberEnd - nHyberBeg - 1 );
// 						unguard;
// 
// 						unguard;
// 						if( nBagType == BT_MountBag )
// 						{
// 							SMountItem* itemHyber = (SMountItem*)itemData;							
// 
// 							if( itemHyber->baseInfo.id == InvalidLogicNumber )
// 								break;						
// 
// 							
// 							if( _tstring::toNarrowString(ItemName.c_str()) != itemHyber->baseInfo.szName )
// 							{
// 								int nTempBeg = 0;
// 								int nTempEnd = 0;
// 
// 								bool bNoFoundHyber = false;
// 
// 								guard(add_2_3);
// 
// 								while( strWide.find( L"[", nHyberEnd) != std::wstring::npos )
// 								{
// 									nTempBeg = strWide.find( L"[", nHyberEnd + 1);
// 									nTempEnd = strWide.find( L"]", nHyberEnd + 1);
// 
// 									if( nTempBeg == std::wstring::npos || nTempEnd == std::wstring::npos )
// 										break;
// 
// 									int willisHyberBeg = 0;
// 
// 									guard(add_2_4);
// 
// 									while( nTempBeg != -1 && nTempBeg < nTempEnd )
// 									{
// 										//这样抛弃第一个"["
// 										willisHyberBeg = nTempBeg;
// 										nTempBeg = strWide.find( L"[", nTempBeg + 1 );
// 
// 										if( nTempBeg == -1 || nTempBeg > nTempEnd )
// 										{
// 											nTempBeg = willisHyberBeg;
// 											break;
// 										}
// 									}
// 
// 									unguard;
// 
// 									if( nTempEnd <= nTempBeg )
// 									{
// 										break;
// 									}
// 									guard(discredit1);
// 									ItemName = strWide.substr( nTempBeg + 1, nTempEnd - nTempBeg - 1 );
// 									unguard;
// 
// 									nHyberBeg = nTempBeg;
// 									nHyberEnd = nTempEnd;
// 
// 									if( _tstring::toNarrowString(ItemName.c_str()) == itemHyber->baseInfo.szName )
// 									{
// 										bNoFoundHyber = true;
// 										break;
// 									}
// 								}
// 								unguard;
// 
// 
// 								if( bNoFoundHyber == false )
// 								{
// 									//没有找到符合链接条件的
// 									break;
// 								}
// 							}
// 
// 
// 							guard(add_itemHyber2);
// 
// 							if( nHyberBeg < nWidthByte && nHyberEnd <= nWidthByte )
// 							{
// 								eItemHyberType = hyber_one_firstline;
// 							}
// 							else if( nHyberBeg < nWidthByte && nHyberEnd > nWidthByte )
// 							{
// 								eItemHyberType = hyber_one_firstandsecondline;
// 							}
// 							else if( nHyberBeg >= nWidthByte && nHyberEnd > nWidthByte )
// 							{
// 								eItemHyberType = hyber_one_secondline;
// 							}
// 							unguard;
// 						}
// 						else
// 						{
// 							SCharItem* itemHyber = (SCharItem*)itemData;
// 
// 							guard(add_itemHyber1);
// 
// 							if( itemHyber->itembaseinfo.ustItemID == InvalidLogicNumber )
// 								break;
// 
// 							unguard;
// 
// 							ItemDefine::SItemCommon *pDetail = GettheItemDetail().GetItemByID( itemHyber->itembaseinfo.ustItemID );
// 							if( NULL == pDetail )
// 								break;
// 
// 							Common::_tstring tstrName( pDetail->GetItemName() );					
// 							S_IconInfoHero::ReplaceSpecifiedName( pDetail->ustLevel, tstrName );
// 							if( _tstring::toNarrowString(ItemName.c_str()) != tstrName )
// 							{
// 								int nTempBeg = 0;
// 								int nTempEnd = 0;
// 
// 								bool bNoFoundHyber = false;
// 
// 								guard(add_2_3);
// 
// 								while( strWide.find( L"[", nHyberEnd) != std::wstring::npos )
// 								{
// 									nTempBeg = strWide.find( L"[", nHyberEnd + 1);
// 									nTempEnd = strWide.find( L"]", nHyberEnd + 1);
// 
// 									if( nTempBeg == std::wstring::npos || nTempEnd == std::wstring::npos )
// 										break;
// 
// 									int willisHyberBeg = 0;
// 
// 									guard(add_2_4);
// 
// 									while( nTempBeg != -1 && nTempBeg < nTempEnd )
// 									{
// 										//这样抛弃第一个"["
// 										willisHyberBeg = nTempBeg;
// 										nTempBeg = strWide.find( L"[", nTempBeg + 1 );
// 
// 										if( nTempBeg == -1 || nTempBeg > nTempEnd )
// 										{
// 											nTempBeg = willisHyberBeg;
// 											break;
// 										}
// 									}
// 
// 									unguard;
// 
// 									if( nTempEnd <= nTempBeg )
// 									{
// 										break;
// 									}
// 									guard(discredit1);
// 									ItemName = strWide.substr( nTempBeg + 1, nTempEnd - nTempBeg - 1 );
// 									unguard;
// 
// 									nHyberBeg = nTempBeg;
// 									nHyberEnd = nTempEnd;
// 
// 									if( _tstring::toNarrowString(ItemName.c_str()) == pDetail->GetItemName() )
// 									{
// 										bNoFoundHyber = true;
// 										break;
// 									}
// 								}
// 								unguard;
// 
// 
// 								if( bNoFoundHyber == false )
// 								{
// 									//没有找到符合链接条件的
// 									break;
// 								}
// 							}
// 
// 
// 							guard(add_itemHyber2);
// 
// 							if( nHyberBeg < nWidthByte && nHyberEnd <= nWidthByte )
// 							{
// 								eItemHyberType = hyber_one_firstline;
// 							}
// 							else if( nHyberBeg < nWidthByte && nHyberEnd > nWidthByte )
// 							{
// 								eItemHyberType = hyber_one_firstandsecondline;
// 							}
// 							else if( nHyberBeg >= nWidthByte && nHyberEnd > nWidthByte )
// 							{
// 								eItemHyberType = hyber_one_secondline;
// 							}
// 							unguard;
// 
// 						}
// 
// 					}
// 					break;
// 				case 2:
// 					{
// 						if( nHyberBeg == -1 || nHyberEnd == -1 )
// 							break;
// 
// 						std::wstring ItemName;
// 
// 						guard(add_2_5);
// 
// 						//这里需要进行名字分析了 确定玩家那个是自己在edit上输入进去的 还是用物品右键粘贴上去的
// 						if( nHyberEnd <= nHyberBeg )
// 						{
// 							break;
// 						}
// 						guard(discredit2);
// 						ItemName = strWide.substr( nHyberBeg + 1, nHyberEnd - nHyberBeg - 1 );
// 						unguard;
// 
// 
// 						unguard;
// 
// 						SCharItem* itemHyber = (SCharItem*)itemData;
// 
// 						guard(add_itemHyber3);
// 
// 						if( itemHyber->itembaseinfo.ustItemID == InvalidLogicNumber )
// 							break;
// 
// 						unguard;
// 
// 						ItemDefine::SItemCommon *pDetail = GettheItemDetail().GetItemByID( itemHyber->itembaseinfo.ustItemID );
// 						if( NULL == pDetail )
// 							break;
// 
// 						if( _tstring::toNarrowString(ItemName.c_str()) != pDetail->GetItemName() )
// 						{
// 							int nTempBeg = 0;
// 							int nTempEnd = 0;
// 
// 							bool bNoFoundHyber = false;
// 
// 							guard(add_2_6);
// 
// 							while( strWide.find( L"[", nHyberEnd) != -1 )
// 							{
// 								nTempBeg = strWide.find( L"[", nHyberEnd + 1);
// 								nTempEnd = strWide.find( L"]", nHyberEnd + 1);
// 
// 								if( nTempBeg == std::string::npos || nTempEnd == std::string::npos )
// 									break;
// 
// 								int willisHyberBeg = 0;
// 
// 								guard(add_2_7);
// 
// 								while( nTempBeg != -1 && nTempBeg < nTempEnd )
// 								{
// 									//这样抛弃第一个"["
// 									willisHyberBeg = nTempBeg;
// 									nTempBeg = strWide.find( L"[", nTempBeg + 1 );
// 
// 									if( nTempBeg == -1 || nTempBeg > nTempEnd )
// 									{
// 										nTempBeg = willisHyberBeg;
// 										break;
// 									}
// 								}
// 
// 								unguard;
// 
// 								if( nTempEnd <= nTempBeg )
// 								{
// 									break;
// 								}
// 								guard(discredit3);
// 								ItemName = strWide.substr( nTempBeg + 1, nTempEnd - nTempBeg - 1 );
// 								unguard;
// 
// 								nHyberBeg = nTempBeg;
// 								nHyberEnd = nTempEnd;
// 
// 								if( _tstring::toNarrowString(ItemName.c_str()) == pDetail->GetItemName() )
// 								{
// 									bNoFoundHyber = true;
// 									break;
// 								}
// 							}
// 
// 							unguard;
// 
// 							if( bNoFoundHyber == false )
// 							{
// 								//没有找到符合链接条件的
// 								nHyberBeg = nHyberEnd = -1;
// 								//break;
// 							}
// 
// 						}
// 
// 						guard(add_2_8);
// 
// 						itemHyber = (SCharItem*)( itemData + sizeof(SCharItem) );
// 
// 						if( itemHyber->itembaseinfo.ustItemID == InvalidLogicNumber )
// 							break;
// 
// 						pDetail = GettheItemDetail().GetItemByID( itemHyber->itembaseinfo.ustItemID );
// 						if( NULL == pDetail )
// 							break;
// 
// 						nSecondHyberBeg = strWide.find( L"[", nHyberEnd + 1);
// 						nSecondHyberEnd = strWide.find( L"]", nSecondHyberBeg + 1);
// 
// 						if( nSecondHyberBeg == -1 || nSecondHyberEnd == -1 )
// 						{
// 							nSecondHyberBeg = nSecondHyberEnd = -1;
// 							//break;
// 						}
// 
// 						unguard;
// 
// 						int swapsign = strWide.find( L"[", nSecondHyberBeg + 1);
// 						int willisHyberBeg = 0;
// 
// 						guard(add_2_9);
// 
// 						while( swapsign != -1 && swapsign < nSecondHyberEnd )
// 						{
// 							//这样抛弃第一个L"["
// 							willisHyberBeg = swapsign;
// 							swapsign = strWide.find( L"[", swapsign + 1 );
// 
// 							if( swapsign == -1 || swapsign > nSecondHyberEnd )
// 							{
// 								nSecondHyberBeg = willisHyberBeg;
// 								break;
// 							}
// 						}
// 
// 						unguard;
// 
// 						if( nSecondHyberEnd <= nSecondHyberBeg )
// 						{
// 							break;
// 						}
// 						guard(discredit4);
// 						ItemName = strWide.substr( nSecondHyberBeg + 1, nSecondHyberEnd - nSecondHyberBeg - 1 );
// 						unguard;
// 
// 						if( _tstring::toNarrowString(ItemName.c_str()) != pDetail->GetItemName() )
// 						{
// 							int nTempBeg = 0;
// 							int nTempEnd = 0;
// 
// 							bool bNoFoundHyber = false;
// 
// 							guard(add_2_10);
// 
// 							while( strWide.find( L"[", nSecondHyberEnd) != -1 )
// 							{
// 								nTempBeg = strWide.find( L"[", nSecondHyberEnd + 1);
// 								nTempEnd = strWide.find( L"]", nSecondHyberEnd + 1);
// 
// 								if( nTempBeg == std::string::npos || nTempEnd == std::string::npos )
// 									break;
// 
// 								int willisHyberBeg = 0;
// 
// 								guard(add_2_11);
// 
// 								while( nTempBeg != -1 && nTempBeg < nTempEnd )
// 								{
// 									//这样抛弃第一个L"["
// 									willisHyberBeg = nTempBeg;
// 									nTempBeg = strWide.find( L"[", nTempBeg + 1 );
// 
// 									if( nTempBeg == -1 || nTempBeg > nTempEnd )
// 									{
// 										nTempBeg = willisHyberBeg;
// 										break;
// 									}
// 								}
// 
// 								unguard;
// 								if( nTempEnd <= nTempBeg )
// 								{
// 									break;
// 								}
// 								guard(discredit5);
// 								ItemName = strWide.substr( nTempBeg + 1, nTempEnd - nTempBeg - 1 );
// 								unguard;
// 
// 								nSecondHyberBeg = nTempBeg;
// 								nSecondHyberEnd = nTempEnd;
// 
// 								if( _tstring::toNarrowString(ItemName.c_str()) == pDetail->GetItemName() )
// 								{
// 									bNoFoundHyber = true;
// 									break;
// 								}
// 							}
// 
// 							if( bNoFoundHyber == false )
// 							{
// 								//没有找到符合链接条件的
// 								nSecondHyberBeg = nSecondHyberEnd = -1;
// 								//break;
// 							}
// 
// 							unguard;
// 						}
// 
// 						if( nSecondHyberBeg < nWidthByte && nSecondHyberEnd <= nWidthByte 
// 							&& nSecondHyberBeg != -1 && nSecondHyberEnd != -1 )
// 						{
// 							eItemHyberType = hyber_two_all_firstline;
// 						}
// 						else if( nSecondHyberBeg < nWidthByte && nSecondHyberEnd > nWidthByte
// 							&& nSecondHyberBeg != -1 && nSecondHyberEnd != -1 )
// 						{
// 							eItemHyberType = hyber_two_two_firstandsecondline;
// 						}
// 						else if( nHyberEnd <= nWidthByte && nSecondHyberBeg >= nWidthByte 
// 							&& nHyberEnd != -1 && nSecondHyberBeg != -1 )
// 						{
// 							eItemHyberType = hyber_two_two_secondline;
// 						}
// 						else if( nHyberBeg < nWidthByte && nHyberEnd > nWidthByte )
// 						{
// 							eItemHyberType = hyber_two_first_firstandsecondline;
// 						}
// 						else if( nHyberBeg >= nWidthByte )
// 						{
// 							eItemHyberType = hyber_two_all_secondline;
// 						}
// 
// 					}
// 					break;
// 				case 3:
// 					{
// 						if( nHyberBeg == -1 || nHyberEnd == -1 )
// 							break;
// 
// 						std::wstring ItemName;
// 
// 						guard(add_2_12);
// 
// 						//这里需要进行名字分析了 确定玩家那个是自己在edit上输入进去的 还是用物品右键粘贴上去的
// 						if( nHyberEnd <= nHyberBeg )
// 						{
// 							break;
// 						}
// 						guard(discredit6);
// 						ItemName = strWide.substr( nHyberBeg + 1, nHyberEnd - nHyberBeg - 1 );
// 						unguard;
// 
// 
// 						unguard;
// 
// 						SCharItem* itemHyber = (SCharItem*)itemData;
// 
// 						guard(add_itemHyber4);
// 
// 						if( itemHyber->itembaseinfo.ustItemID == InvalidLogicNumber )
// 							break;
// 
// 						unguard;
// 
// 						ItemDefine::SItemCommon *pDetail = GettheItemDetail().GetItemByID( itemHyber->itembaseinfo.ustItemID );
// 						if( NULL == pDetail )
// 							break;
// 
// 						if( _tstring::toNarrowString(ItemName.c_str()) != pDetail->GetItemName() )
// 						{
// 							int nTempBeg = 0;
// 							int nTempEnd = 0;
// 
// 							bool bNoFoundHyber = false;
// 
// 							guard(add_2_13);
// 
// 							while( strWide.find( L"[", nHyberEnd) != -1 )
// 							{
// 								nTempBeg = strWide.find( L"[", nHyberEnd + 1);
// 								nTempEnd = strWide.find( L"]", nHyberEnd + 1);
// 
// 								if( nTempBeg == std::string::npos || nTempEnd == std::string::npos )
// 									break;
// 
// 								int willisHyberBeg = 0;
// 
// 								guard(add_2_14);
// 
// 								while( nTempBeg != -1 && nTempBeg < nTempEnd )
// 								{
// 									//这样抛弃第一个L"["
// 									willisHyberBeg = nTempBeg;
// 									nTempBeg = strWide.find( L"[", nTempBeg + 1 );
// 
// 									if( nTempBeg == -1 || nTempBeg > nTempEnd )
// 									{
// 										nTempBeg = willisHyberBeg;
// 										break;
// 									}
// 								}
// 
// 								unguard;
// 								if( nTempEnd <= nTempBeg )
// 								{
// 									break;
// 								}
// 								guard(discredit7);
// 								ItemName = strWide.substr( nTempBeg + 1, nTempEnd - nTempBeg - 1 );
// 								unguard;
// 
// 								nHyberBeg = nTempBeg;
// 								nHyberEnd = nTempEnd;
// 
// 								if( _tstring::toNarrowString(ItemName.c_str()) == pDetail->GetItemName() )
// 								{
// 									bNoFoundHyber = true;
// 									break;
// 								}
// 							}
// 
// 							unguard;
// 							if( bNoFoundHyber == false )
// 							{
// 								//没有找到符合链接条件的
// 								nHyberBeg = nHyberEnd = -1;
// 							}
// 
// 						}
// 
// 						guard(add_2_15);
// 
// 						itemHyber = (SCharItem*)( itemData + sizeof(SCharItem) );
// 
// 						if( itemHyber->itembaseinfo.ustItemID == InvalidLogicNumber )
// 							break;
// 
// 						pDetail = GettheItemDetail().GetItemByID( itemHyber->itembaseinfo.ustItemID );
// 						if( NULL == pDetail )
// 							break;
// 
// 						nSecondHyberBeg = strWide.find( L"[", nHyberEnd + 1);
// 						nSecondHyberEnd = strWide.find( L"]", nSecondHyberBeg + 1);
// 
// 						if( nSecondHyberBeg == -1 || nSecondHyberEnd == -1 )
// 						{
// 							break;
// 						}
// 
// 						unguard;
// 
// 						int swapsign = strWide.find( L"[", nSecondHyberBeg + 1);
// 						int willisHyberBeg = 0;
// 
// 						guard(add_2_16);
// 
// 						while( swapsign != -1 && swapsign < nSecondHyberEnd )
// 						{
// 							//这样抛弃第一个L"["
// 							willisHyberBeg = swapsign;
// 							swapsign = strWide.find( L"[", swapsign + 1 );
// 
// 							if( swapsign == -1 || swapsign > nSecondHyberEnd )
// 							{
// 								nSecondHyberBeg = willisHyberBeg;
// 								break;
// 							}
// 						}
// 
// 						unguard;
// 
// 						if( nSecondHyberEnd <= nSecondHyberBeg )
// 						{
// 							break;
// 						}
// 						guard(discredit8);
// 						ItemName = strWide.substr( nSecondHyberBeg + 1, nSecondHyberEnd - nSecondHyberBeg - 1 );
// 						unguard;
// 
// 						if( _tstring::toNarrowString(ItemName.c_str()) != pDetail->GetItemName() )
// 						{
// 							int nTempBeg = 0;
// 							int nTempEnd = 0;
// 
// 							bool bNoFoundHyber = false;
// 
// 							guard(add_2_17);
// 
// 							while( strWide.find( L"[", nSecondHyberEnd) != -1 )
// 							{
// 								nTempBeg = strWide.find( L"[", nSecondHyberEnd + 1);
// 								nTempEnd = strWide.find( L"]", nSecondHyberEnd + 1);
// 
// 								if( nTempBeg == std::string::npos || nTempEnd == std::string::npos )
// 									break;
// 
// 								int willisHyberBeg = 0;
// 
// 								guard(add_2_18);
// 
// 								while( nTempBeg != -1 && nTempBeg < nTempEnd )
// 								{
// 									//这样抛弃第一个L"["
// 									willisHyberBeg = nTempBeg;
// 									nTempBeg = strWide.find( L"[", nTempBeg + 1 );
// 
// 									if( nTempBeg == -1 || nTempBeg > nTempEnd )
// 									{
// 										nTempBeg = willisHyberBeg;
// 										break;
// 									}
// 								}
// 
// 								unguard;
// 
// 								if( nTempEnd <= nTempBeg )
// 								{
// 									break;
// 								}
// 								guard(discredit9);
// 								ItemName = strWide.substr( nTempBeg + 1, nTempEnd - nTempBeg - 1 );
// 								unguard;
// 
// 								nSecondHyberBeg = nTempBeg;
// 								nSecondHyberEnd = nTempEnd;
// 
// 								if( _tstring::toNarrowString(ItemName.c_str()) == pDetail->GetItemName() )
// 								{
// 									bNoFoundHyber = true;
// 									break;
// 								}
// 							}
// 
// 							unguard;
// 
// 							if( bNoFoundHyber == false )
// 							{
// 								//没有找到符合链接条件的
// 								nSecondHyberBeg = nSecondHyberEnd = -1;
// 							}
// 
// 						}
// 
// 						guard(add_2_19);
// 
// 						itemHyber = (SCharItem*)( itemData + sizeof(SCharItem)*2 );
// 
// 						if( itemHyber->itembaseinfo.ustItemID == InvalidLogicNumber )
// 							break;
// 
// 						pDetail = GettheItemDetail().GetItemByID( itemHyber->itembaseinfo.ustItemID );
// 						if( NULL == pDetail )
// 							break;
// 
// 						nThreeHyberBeg = strWide.find( L"[", nSecondHyberEnd + 1);
// 						nThreeHyberEnd = strWide.find( L"]", nThreeHyberBeg + 1);
// 
// 						if( nThreeHyberBeg == -1 || nThreeHyberEnd == -1)
// 						{
// 							nThreeHyberBeg = nThreeHyberEnd = -1;
// 							//break;
// 						}
// 
// 						unguard;
// 
// 						swapsign = strWide.find( L"[", nThreeHyberBeg + 1);
// 						willisHyberBeg = 0;
// 
// 						guard(add_2_20);
// 
// 						while( swapsign != -1 && swapsign < nThreeHyberEnd )
// 						{
// 							//这样抛弃第一个L"["
// 							willisHyberBeg = swapsign;
// 							swapsign = strWide.find( L"[", swapsign + 1 );
// 
// 							if( swapsign == -1 || swapsign > nThreeHyberEnd )
// 							{
// 								nThreeHyberBeg = willisHyberBeg;
// 								break;
// 							}
// 						}
// 
// 						unguard;
// 
// 						if( nThreeHyberEnd <= nThreeHyberBeg )
// 						{
// 							break;
// 						}
// 						guard(discredit10);
// 						ItemName = strWide.substr( nThreeHyberBeg + 1, nThreeHyberEnd - nThreeHyberBeg - 1 );
// 						unguard;
// 
// 						Common::_tstring tstrName( pDetail->GetItemName() );					
// 						S_IconInfoHero::ReplaceSpecifiedName( pDetail->ustLevel, tstrName );
// 						if( _tstring::toNarrowString(ItemName.c_str()) != tstrName )
// 						{
// 							int nTempBeg = 0;
// 							int nTempEnd = 0;
// 
// 							bool bNoFoundHyber = false;
// 
// 							guard(add_2_21);
// 
// 							while( strWide.find( L"[", nThreeHyberEnd) != -1 )
// 							{
// 								nTempBeg = strWide.find( L"[", nThreeHyberEnd + 1);
// 								nTempEnd = strWide.find( L"]", nThreeHyberEnd + 1);
// 
// 								if( nTempBeg == std::string::npos || nTempEnd == std::string::npos )
// 									break;
// 
// 								int willisHyberBeg = 0;
// 
// 								guard(add_2_22);
// 
// 								while( nTempBeg != -1 && nTempBeg < nTempEnd )
// 								{
// 									//这样抛弃第一个L"["
// 									willisHyberBeg = nTempBeg;
// 									nTempBeg = strWide.find( L"[", nTempBeg + 1 );
// 
// 									if( nTempBeg == -1 || nTempBeg > nTempEnd )
// 									{
// 										nTempBeg = willisHyberBeg;
// 										break;
// 									}
// 								}
// 
// 								unguard;
// 
// 								if( nTempEnd <= nTempBeg )
// 								{
// 									break;
// 								}
// 								guard(discredit11);
// 								ItemName = strWide.substr( nTempBeg + 1, nTempEnd - nTempBeg - 1 );
// 								unguard;
// 
// 								nThreeHyberBeg = nTempBeg;
// 								nThreeHyberEnd = nTempEnd;
// 
// 								Common::_tstring tstrName( pDetail->GetItemName() );					
// 								S_IconInfoHero::ReplaceSpecifiedName( pDetail->ustLevel, tstrName );
// 								if( _tstring::toNarrowString(ItemName.c_str()) == tstrName )
// 								{
// 									bNoFoundHyber = true;
// 									break;
// 								}
// 							}
// 
// 							unguard;
// 
// 							if( bNoFoundHyber == false )
// 							{
// 								//没有找到符合链接条件的
// 								nThreeHyberBeg = nThreeHyberEnd = -1;
// 							}
// 
// 						}
// 
// 						if( nThreeHyberBeg < nWidthByte && nThreeHyberEnd <= nWidthByte 
// 							&& nThreeHyberBeg != -1 && nThreeHyberEnd != -1 )
// 						{
// 							eItemHyberType = hyber_three_all_firstline;
// 						}
// 						else if( nThreeHyberBeg < nWidthByte && nThreeHyberEnd > nWidthByte 
// 							&& nThreeHyberBeg != -1 && nThreeHyberEnd != -1 )
// 						{
// 							eItemHyberType = hyber_three_three_firstandsecondline;
// 						}
// 						else if( nSecondHyberEnd <= nWidthByte && nThreeHyberBeg >= nWidthByte 
// 							&& nSecondHyberEnd != -1 && nThreeHyberBeg != -1 )
// 						{
// 							eItemHyberType = hyber_three_three_secondline;
// 						}
// 						else if( nSecondHyberBeg < nWidthByte && nSecondHyberEnd > nWidthByte )
// 						{
// 							eItemHyberType = hyber_three_two_firstandsecondline;
// 						}
// 						else if( nHyberEnd <= nWidthByte && nSecondHyberBeg >= nWidthByte )
// 						{
// 							eItemHyberType = hyber_three_two_secondline;
// 						}
// 						else if( nHyberBeg < nWidthByte && nHyberEnd > nWidthByte )
// 						{
// 							eItemHyberType = hyber_three_first_firstandsecondline;
// 						}
// 						else if( nHyberBeg >= nWidthByte )
// 						{
// 							eItemHyberType = hyber_three_all_secondline;
// 						}
// 					}
// 					break;
// 				}
// 			}//----------------------------------------------------------------------------
// 
// 			guard(add_2_23);
// 
// 			//-----------通过上面的字符分析 确定相应的 nWidthByte
// 			if( useHyberCnt > 0 )
// 			{
// 				switch( eItemHyberType )
// 				{
// 				case hyber_one_firstline:
// 				case hyber_one_secondline:
// 					break;
// 				case hyber_one_firstandsecondline:
// 					{
// 						if( nHyberBeg == -1 || nHyberEnd == -1 )
// 							break;
// 
// 						nWidthByte = nHyberBeg;
// 					}
// 					break;
// 				case hyber_two_all_firstline:
// 				case hyber_two_two_secondline:
// 				case hyber_two_all_secondline:
// 					break;
// 				case hyber_two_two_firstandsecondline:
// 					{
// 						if( nSecondHyberBeg == -1 || nHyberEnd == -1 )
// 							break;
// 
// 						nWidthByte = nSecondHyberBeg;
// 					}
// 					break;
// 				case hyber_two_first_firstandsecondline:
// 					{
// 						if( nHyberBeg == -1 || nHyberEnd == -1 )
// 							break;
// 
// 						nWidthByte = nHyberBeg;
// 					}
// 					break;
// 				case hyber_three_all_firstline:
// 				case hyber_three_three_secondline:
// 				case hyber_three_two_secondline:
// 				case hyber_three_all_secondline:
// 					break;
// 				case hyber_three_three_firstandsecondline:
// 					{
// 						if( nThreeHyberBeg == -1 || nThreeHyberEnd == -1 )
// 							break;
// 
// 						nWidthByte = nThreeHyberBeg;
// 					}
// 					break;
// 				case hyber_three_two_firstandsecondline:
// 					{
// 						if( nSecondHyberBeg == -1 || nHyberEnd == -1 )
// 							break;
// 
// 						nWidthByte = nSecondHyberBeg;
// 					}
// 					break;
// 				case hyber_three_first_firstandsecondline:
// 					{
// 						if( nHyberBeg == -1 || nHyberEnd == -1 )
// 							break;
// 
// 						nWidthByte = nHyberBeg;
// 					}
// 					break;
// 				}
// 			}
// 
// 			unguard;

			//----------------------------------------------------

			//-----------------------------------------------------------------

// 			guard(add_2_25);
// 
// 			std::string line = _tstring::toNarrowString(strWide.substr(0, nWidthByte).c_str());
// 			int nPreFix = line.rfind("{");
// 			int nPostFix = line.rfind("}");
// 			if (nPreFix > nPostFix)//表情发生了错行
// 			{
// 				std::wstring nextline = &strWide[nWidthByte];
// 				nPostFix = nextline.find(L"}");
// 				if (nPostFix != -1 && nPreFix != 0)
// 				{
// 					line = line.substr(0,nPreFix);
// 					nWidthByte = _tstring::toWideString(line.c_str()).length();
// 				}
// 			}
// 			line = _tstring::toNarrowString(strWide.substr(0, nWidthByte).c_str());
// 			nPreFix = line.rfind("<");
// 			nPostFix = line.rfind(">");
// 			if (nPreFix > nPostFix)//地址发生了错行
// 			{
// 				std::wstring nextline = &strWide[nWidthByte];
// 				nPostFix = nextline.find(L">");
// 				if (nPostFix != -1&& nPreFix != 0)
// 				{
// 					line = line.substr(0,nPreFix);
// 					nWidthByte = _tstring::toWideString(line.c_str()).length();
// 				}
// 			}
// 			line = _tstring::toNarrowString(strWide.substr(0, nWidthByte).c_str());
// 			nPreFix = line.rfind('~');
// 			nPostFix = line.rfind('_');
// 			if (nPreFix > nPostFix)//人名发生了错行
// 			{
// 				std::wstring nextline = &strWide[nWidthByte];
// 				nPostFix = nextline.find(L"_");
// 				if (nPostFix != -1&& nPreFix != 0)
// 				{
// 					line = line.substr(0,nPreFix);
// 					nWidthByte = _tstring::toWideString(line.c_str()).length();
// 				}
// 			}
			//-------------------这里真正添加数据 和 调用递归-----------------
// 			SCharItem stTempItem;
// 			if( nBagType == BT_MountBag )
// 			{
// 				SMountItem* pDrome = (SMountItem*)itemData;
// 				stTempItem.itembaseinfo.ustItemID = pDrome->baseInfo.id;				
// 				stTempItem.itembaseinfo.nOnlyInt = pDrome->baseInfo.guid;
// 				m_mapReceivedMount[pDrome->baseInfo.guid] = *pDrome;
// 				itemData = (char*)&stTempItem;
// 			}
// 			switch( eItemHyberType )
// 			{
// 			case hyber_init_none:
// 				{
// 					stItem.SetData( line.c_str() , nConver, NULL, col, szToName );
// 					if( m_pChatInfoText )
// 					{
// 						ControlList::S_List* pAdd = m_pChatInfoText->AddItem( &stItem, bMoveDown );
// 					}
// 
// 					ShowTextInChatList( _tstring::toNarrowString(&strWide[nWidthByte]),col, MsgChat::CHAT_TYPE_NORMAL, szToName,NULL,0);
// 				}
// 				break;
// 			case hyber_one_firstline:
// 				{
// 					stItem.SetData( line.c_str() , nConver, NULL, col, szToName, itemData, useHyberCnt, sizeof( SCharItem ) );
// 					if( m_pChatInfoText )
// 					{
// 						ControlList::S_List* pAdd = m_pChatInfoText->AddItem( &stItem, bMoveDown );
// 					}
// 					ShowTextInChatList( _tstring::toNarrowString(&strWide[nWidthByte]), col, MsgChat::CHAT_TYPE_NORMAL, szToName,NULL,0);
// 				}
// 				break;
// 			case hyber_one_firstandsecondline:
// 			case hyber_one_secondline:
// 				{
// 					stItem.SetData( line.c_str() , nConver, NULL, col, szToName );
// 					if( m_pChatInfoText )
// 					{
// 						ControlList::S_List* pAdd = m_pChatInfoText->AddItem( &stItem, bMoveDown );
// 					}
// 					ShowTextInChatList( _tstring::toNarrowString(&strWide[nWidthByte]), col, MsgChat::CHAT_TYPE_NORMAL, szToName, itemData, useHyberCnt, nBagType);
// 				}
// 				break;
// 			case hyber_two_all_firstline:
// 				{
// 					stItem.SetData( line.c_str() , nConver, NULL, col, szToName, itemData, useHyberCnt, sizeof( SCharItem ) );
// 					if( m_pChatInfoText )
// 					{
// 						ControlList::S_List* pAdd = m_pChatInfoText->AddItem( &stItem, bMoveDown );
// 					}
// 					ShowTextInChatList( _tstring::toNarrowString(&strWide[nWidthByte]), col, MsgChat::CHAT_TYPE_NORMAL, szToName,NULL,0);
// 				}
// 				break;
// 			case hyber_two_two_firstandsecondline:
// 			case hyber_two_two_secondline:
// 				{
// 					stItem.SetData( line.c_str() , nConver, NULL, col, szToName, itemData, 1 );
// 					if( m_pChatInfoText )
// 					{
// 						ControlList::S_List* pAdd = m_pChatInfoText->AddItem( &stItem, bMoveDown );
// 					}
// 					ShowTextInChatList( _tstring::toNarrowString(&strWide[nWidthByte]), col, MsgChat::CHAT_TYPE_NORMAL, szToName,itemData+sizeof(SCharItem), 1);
// 				}
// 				break;
// 			case hyber_two_first_firstandsecondline:
// 			case hyber_two_all_secondline:
// 				{
// 					stItem.SetData( line.c_str() , nConver, NULL, col, szToName );
// 					if( m_pChatInfoText )
// 					{
// 						ControlList::S_List* pAdd = m_pChatInfoText->AddItem( &stItem, bMoveDown );
// 					}
// 					ShowTextInChatList( _tstring::toNarrowString(&strWide[nWidthByte]), col, MsgChat::CHAT_TYPE_NORMAL, szToName, itemData, useHyberCnt, nBagType);
// 				}
// 				break;
// 			case hyber_three_all_firstline:
// 				{
// 					stItem.SetData( line.c_str() , nConver, NULL, col, szToName, itemData, useHyberCnt, sizeof( SCharItem ) );
// 					if( m_pChatInfoText )
// 					{
// 						ControlList::S_List* pAdd = m_pChatInfoText->AddItem( &stItem, bMoveDown );
// 					}
// 					ShowTextInChatList( _tstring::toNarrowString(&strWide[nWidthByte]), col, MsgChat::CHAT_TYPE_NORMAL, szToName,NULL,0);
// 				}
// 				break;
// 			case hyber_three_three_firstandsecondline:
// 			case hyber_three_three_secondline:
// 				{
// 					stItem.SetData( line.c_str() , nConver, NULL, col, szToName, itemData, 2 );
// 					if( m_pChatInfoText )
// 					{
// 						ControlList::S_List* pAdd = m_pChatInfoText->AddItem( &stItem, bMoveDown );
// 					}
// 					ShowTextInChatList( _tstring::toNarrowString(&strWide[nWidthByte]), col, MsgChat::CHAT_TYPE_NORMAL, szToName,itemData+sizeof(SCharItem)*2, 1, nBagType);
// 				}
// 				break;
// 			case hyber_three_two_firstandsecondline:
// 			case hyber_three_two_secondline:
// 				{
// 					stItem.SetData( line.c_str() , nConver, NULL, col, szToName, itemData, 1 );
// 					if( m_pChatInfoText )
// 					{
// 						ControlList::S_List* pAdd = m_pChatInfoText->AddItem( &stItem, bMoveDown );
// 					}
// 					ShowTextInChatList( _tstring::toNarrowString(&strWide[nWidthByte]), col, MsgChat::CHAT_TYPE_NORMAL, szToName,itemData+sizeof(SCharItem), 2, nBagType);
// 				}
// 				break;
// 			case hyber_three_first_firstandsecondline:
// 			case hyber_three_all_secondline:
// 				{
// 					stItem.SetData( line.c_str() , nConver, NULL, col, szToName );
// 					if( m_pChatInfoText )
// 					{
// 						ControlList::S_List* pAdd = m_pChatInfoText->AddItem( &stItem, bMoveDown );
// 					}
// 					ShowTextInChatList( _tstring::toNarrowString(&strWide[nWidthByte]), col, MsgChat::CHAT_TYPE_NORMAL, szToName, itemData, useHyberCnt, nBagType);
// 				}
// 				break;
// 			}
// 			//------------------------------------------------------------------
// 
// 			unguard;
// 
// 		}
// 		else
// 		{
// 			guard(add_2_26);
// 
// 			SCharItem stTempItem;
// 			if( nBagType == BT_MountBag )
// 			{
// 				SMountItem* pDrome = (SMountItem*)itemData;
// 				stTempItem.itembaseinfo.ustItemID = pDrome->baseInfo.id;	
// 				stTempItem.itembaseinfo.nOnlyInt = pDrome->baseInfo.guid;
// 				m_mapReceivedMount[pDrome->baseInfo.guid] = *pDrome;
// 				itemData = (char*)&stTempItem;
// 			}
// 
// 			if( useHyberCnt > 0 )
// 			{
// 				stItem.SetData( str.c_str() , nConver, NULL, col, szToName, itemData, useHyberCnt, sizeof( SCharItem ));
// 			}
// 			else
// 			{
// 				stItem.SetData( str.c_str() , nConver, NULL, col, szToName );
// 			}
// 
// 			if( m_pChatInfoText )
// 			{
// 				ControlList::S_List* pAdd = m_pChatInfoText->AddItem( &stItem, bMoveDown );
// 			}
// 			unguard;
// 
// 		}


// 		guard(add_2_27);
// 
// 		if( m_pChatInfoText && m_pChatInfoText->GetListItemCnt() > m_pChatInfoText->GetItemShowCount() )
// 		{
// 			ControlScrollBar* pScrollBar = m_pChatInfoText->GetScrollBar();
// 			if( pScrollBar )
// 			{
// 				pScrollBar->SetMaxValue( m_pChatInfoText->GetListItemCnt() - m_pChatInfoText->GetItemShowCount() );
// 				pScrollBar->SetStepValue( 1 );
// 			}
// 		}
// 
// 		unguard;

	}

}

void CommonChatFrame::SetActiveChatFrameByEdit( ControlEdit* pID_EDIT_INPUT )
{
	if (s_CUI_ID_FRAME_Speaker.m_pID_EDIT_INPUT == pID_EDIT_INPUT)
	{

	}
	else if (s_CUI_ChatInfoBox.m_pID_EDIT_INPUT == pID_EDIT_INPUT)
	{
		g_bMessageChat = false;
	}
	else
	{
		chatMessageManage.SetActiveChatFrameByEdit(pID_EDIT_INPUT);
	}
}

CommonChatFrame* CommonChatFrame::GetActiveChatFrame()
{
	if (s_CUI_ID_FRAME_Speaker.IsVisable())
		return &s_CUI_ID_FRAME_Speaker;

	CommonChatFrame* pFrame = 0;
	if(!g_bMessageChat)
	{
		pFrame = &s_CUI_ChatInfoBox;
	}
	else
	{
		pFrame = chatMessageManage.GetActiveMessageFrame();
	}
	if (!pFrame)
		pFrame = &s_CUI_ChatInfoBox;

	return pFrame;
}
extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;

bool CommonChatFrame::ID_BUTTON_faceOnButtonClick( ControlObject* pSender )
{
	if (this == &s_CUI_ChatInfoBox)
	{
		g_bMessageChat = false;
	}
	else
		g_bMessageChat = true;
	s_CUI_ID_FRAME_FACE.SetVisable( !s_CUI_ID_FRAME_FACE.IsVisable() );
	if (s_CUI_ID_FRAME_FACE.IsVisable())
	{
		// 		Begin2Input();
		// 		SetEditFocus();
		CalFaceRect();
		s_CUI_ID_FRAME_FACE.SetPos(faceRect.left,faceRect.top);
	}
	return true;

}

bool CommonChatFrame::OnFrameRender()
{
	/*GetActiveChatFrame()->m_FreeTip.Render( GetActiveChatFrame()->m_pChatInfoBox->GetFontIndex(), 
		GetActiveChatFrame()->m_pChatInfoBox->GetFontSize() * ControlObject::GetREAL_SCALE(GetActiveChatFrame()->m_pChatInfoBox),
		GetActiveChatFrame()->m_pChatInfoBox->GetFontColor() );*/

	//=======================================
	// addNew 
	RenderAllFreeTip();

	return true;
}

void CommonChatFrame::HideAllFreeTip()
{
	// 清理可移动的FreeTip
	for ( int idx = 0; idx < MAX_FREETIP_COUNT; ++idx )
	{
		// 清理数据
		m_AllFreeTip[idx].ShowItemTip( false );
		m_AllFreeTip[idx].SetPosId( POS_INVALID );
		m_NoteSort[idx] = -1;
		m_RenderSort[idx] = -1;
	}

	// 清理不可移动的FreeTip
	m_FreeTip.ShowItemTip( false );
}

int CommonChatFrame::PtInAllFreeTipBtn( int x, int y )
{
	for ( int idx = 0; idx < MAX_FREETIP_COUNT; ++idx )
	{
		int renderId = m_RenderSort[idx];

		if ( renderId == -1 )
		{
			continue;
		}

		if ( m_AllFreeTip[renderId].PtInCloseBtn( x, y ) )
		{
			return renderId;
		}
	}

	return -1;
}

int CommonChatFrame::PtInAllFreeTip( int x, int y )
{
	for ( int idx = 0; idx < MAX_FREETIP_COUNT; ++idx )
	{
		int renderId = m_RenderSort[idx];

		if ( renderId == -1 )
		{
			continue;
		}

		if ( m_AllFreeTip[renderId].IsPtInArea( x, y ) )
		{
			return renderId;
		}
	}

	return -1;
}

void CommonChatFrame::RenderAllFreeTip( )
{
	for ( int idx = MAX_FREETIP_COUNT - 1; idx >= 0 ; --idx )
	{
		int renderId = m_RenderSort[idx];

		if ( renderId != -1 )
		{
			m_AllFreeTip[renderId].Render( GetActiveChatFrame()->GetFontIndex(), 
				GetActiveChatFrame()->GetFontSize() * ControlObject::GetREAL_SCALE( GetActiveChatInfoBox() ),
				GetActiveChatFrame()->GetFontColor() );
		}
	}

	m_FreeTip.Render( GetActiveChatFrame()->GetFontIndex(), 
						GetActiveChatFrame()->GetFontSize() * ControlObject::GetREAL_SCALE( GetActiveChatInfoBox() ),
						GetActiveChatFrame()->GetFontColor() );
}

void CommonChatFrame::ResetAllFreeTip()
{
	HideAllFreeTip();
	m_OptFreeTipId = -1;
}

int CommonChatFrame::GetFreeTipState( FreeTipState state )
{
	for ( int i = 0; i < MAX_CHAT_COUNT; i++ )
	{
		if ( m_AllFreeTip[i].GetState() == state )
		{
			return i;
		}
	}
	return -1;
}

bool CommonChatFrame::FreeTipMoveBeginProc( int x, int y )
{
	int idx = PtInAllFreeTip( x, y );

	if ( idx > -1 )
	{
		FreeTipState state = m_AllFreeTip[idx].GetState();

		//if ( state == FS_INVALID )
		if ( m_OptFreeTipId == -1 )
		{
			// 设置的操作FreeTip的id
			//m_AllFreeTip[idx].SetState( FS_LBUTTON_DOWN );
			m_AllFreeTip[idx].MoveBeginProc( x, y );
			m_OptFreeTipId = idx;
			FreeTipSetTop( m_OptFreeTipId );
		}
		return true;
	}

	return false;
}

bool CommonChatFrame::FreeTipMoveProc( int x, int y )
{
	if ( m_OptFreeTipId > -1 )
	{
		//if ( m_AllFreeTip[m_OptFreeTipId].GetState() == FS_LBUTTON_DOWN )
		{
			m_AllFreeTip[m_OptFreeTipId].MoveProc( x, y );
			return true;
		}
	}

	return false;
}

bool CommonChatFrame::FreeTipMoveEndProc( int x, int y )
{
	if ( m_OptFreeTipId > -1 )
	{
		//if ( m_AllFreeTip[m_OptFreeTipId].GetState() == FS_LBUTTON_DOWN )
		if ( m_OptFreeTipId != -1 )
		{
			// 最后一个设置位置移动完成，清理操作ID，还原操作Tip的状态
			m_AllFreeTip[m_OptFreeTipId].MoveEndProc( x, y );
			//m_AllFreeTip[m_OptFreeTipId].SetState( FS_INVALID );
			FreeTipSetTop( m_OptFreeTipId );
			m_OptFreeTipId = -1;

			return true;
		}
	}

	return false;
}

bool CommonChatFrame::FreeTipPushStack( int tipId )
{
	if ( m_RenderSort[MAX_FREETIP_COUNT-1] != -1 )
	{
		// 说明FreeTip满了，不能在入栈了
		return false;
	}

	for ( int idx = MAX_FREETIP_COUNT - 1; idx > 0; --idx )
	{
		m_RenderSort[idx] = m_RenderSort[idx-1];
	}

	m_RenderSort[0] = tipId;

	return true;
}

int CommonChatFrame::FreeTipPopStack()
{
	int ret = m_RenderSort[0];

	for ( int idx = 0; idx < MAX_FREETIP_COUNT - 1; idx++ )
	{
		m_RenderSort[idx] = m_RenderSort[idx + 1];
	}

	m_RenderSort[MAX_FREETIP_COUNT - 1] = -1;

	return ret;
}

void CommonChatFrame::FreeTipEraseStack( int tipId )
{
	// 先找到清理那个
	int findId = -1;

	for ( int idx = 0; idx < MAX_FREETIP_COUNT; ++idx )
	{
		if ( m_RenderSort[idx] == tipId )
		{
			findId = idx;
			break;
		}
	}

	// 然后清理，移动记录数组
	if ( findId != -1 )
	{
		for ( int idx = findId; idx < MAX_FREETIP_COUNT - 1; ++idx )
		{
			m_RenderSort[idx] = m_RenderSort[idx + 1];
		}

		m_RenderSort[MAX_FREETIP_COUNT - 1] = -1;
	}
}

void CommonChatFrame::FreeTipSetTop( int tipId )
{
	int findId = -1;

	for ( int idx = 0; idx < MAX_FREETIP_COUNT; ++idx )
	{
		if ( m_RenderSort[idx] == tipId )
		{
			findId = idx;
			break;
		}
	}

	if ( findId != -1 )
	{
		int data = m_RenderSort[findId];
		for ( int idx = findId; idx > 0; --idx )
		{
			m_RenderSort[idx] = m_RenderSort[idx - 1];
		}

		m_RenderSort[0] = data;
	}
}

bool CommonChatFrame::EscCloseFreeTip()
{
	int tipId = FreeTipPopStack();
	
	if ( tipId != -1 )
	{
		m_AllFreeTip[tipId].ShowItemTip( false );
		ClearNoteId( tipId );
		return true;
	}

	return false;
}

bool CommonChatFrame::OnFrameRun()
{
	return true;
}


void CommonChatFrame::InitialCommonChat()
{
	SetShow(false);
	m_pChatInfoBox->SetMsgProcFun2(ChatMsgProc);
	//m_pChatInfoBox->SetMsgHoldup(true);

	if( m_pChatInfoText )
	{
		m_pChatInfoText->SetMsgHoldup(false);	//不接受消息
// 		m_pChatInfoText->SetItemMaxCount( 200 );
// 		m_pChatInfoText->HaveSelBar( false );	//没有绿色cur选中地图
 		m_pChatInfoText->SetHyberRBtnDown( HyberRBtnDown );
// 		m_pChatInfoText->SetHyberItemClick( HyberItemClick );
// 		m_pChatInfoText->SetCurSelIndex(-1);
// 		m_pChatInfoText->SetAutoSetCurIndex( false );
// 		m_pChatInfoText->SetHyberOtherClick(Task_HyberOtherClick);

// 		ControlScrollBar* pScrollBar = m_pChatInfoText->GetScrollBar();
// 		if( pScrollBar )
// 		{
// 			pScrollBar->SetMaxValue( 1 );
// 			pScrollBar->SetStepValue( 1 );
// 		}
		m_pChatInfoText->SetMaxTextHeight(3000);
		m_pChatInfoText->RemoveSyntaxFlag(eKeyNpc);
	}

	if (m_pID_EDIT_INPUT)
	{
		m_pID_EDIT_INPUT->SetMaxCnt(MAX_CHAT_COUNT);
		m_pID_EDIT_INPUT->SetLBtnDownFun(CommonChatFrame_EditOnLButtonDown);
		m_pID_EDIT_INPUT->SetTextChangedFun( CommonChatFrame::EditDataChange );
		m_pID_EDIT_INPUT->SetHyberLimit();
	}

	SetPrivateName("");
	m_bNeedMoveDown = true;
}

static bool HighShoutVIPCallback(char bPressYesButton, void *pData)
{
	if (bPressYesButton)
	{
		MsgChat* pMsg = (MsgChat*)pData;
		GettheNetworkInput().SendMsg( pMsg );
	}
	return true;
}

extern bool bOpenDebugInfo;
void CommonChatFrame::SendChatMessage( int nDefaultChannel, const char* szData )
{
    // 判断是否被禁言
    DWORD dwBanSpeakEndingTime = thePlayerRole.GetBanSpeakEndingTime();
    if( dwBanSpeakEndingTime > HQ_TimeGetTime() )
    {
        char str[MAX_PATH] = {0};
        int iRemainTime = (int)ceil((dwBanSpeakEndingTime - HQ_TimeGetTime()) * 1.f / 60000);   // 计算成分钟
        sprintf(str, theXmlString.GetString(eText_BanSpeak), iRemainTime);
        s_CUI_ChatInfoBox.AddInfo( str, Color_Config.getColor( CC_SystemPromp ) );
        return;
    }
	{
// 		int nTopIndex = 0;
// 		int nRet = 1;

        // 判断是否/roll，不区分大小写
        bool bRoll = false;
        if( szData[0] == '/' 
            && (szData[1] == 'r' || szData[1] == 'R')
            && (szData[2] == 'o' || szData[2] == 'O')
            && (szData[3] == 'l' || szData[3] == 'L')
            && (szData[4] == 'l' || szData[4] == 'L'))
            bRoll = true;

        std::string text = szData;
        // 支持快捷聊天     added by ZhuoMeng.Hu		[10/20/2010]
        int nNewChannel = nDefaultChannel;
        if( text.find( "/s " ) == 0 )
        {
            nNewChannel = MsgChat::CHAT_TYPE_NORMAL;
            text = text.substr( 3 );
        }
        else if( text.find( "/t " ) == 0 )
        {
            nNewChannel = MsgChat::CHAT_TYPE_TERM;
            text = text.substr( 3 );
        }
        else if( text.find( "/g " ) == 0 )
        {
            nNewChannel = MsgChat::CHAT_TYPE_GUILD;
            text = text.substr( 3 );
        }
        else if( text.find( "/c " ) == 0 )
        {
            nNewChannel = MsgChat::CHAT_TYPE_COUNTRY;
            text = text.substr( 3 );
        }
        else if( text.find( "/w " ) == 0 )
        {
            nNewChannel = MsgChat::CHAT_TYPE_HIGHSHOUT;
            text = text.substr( 3 );
        }
        else if( text.find( "/p " ) == 0 )
        {
            nNewChannel = MsgChat::CHAT_TYPE_PRIVATE;
            text = text.substr( 3 );
        }
		else if( text.find( "/y " ) == 0 )
		{
			nNewChannel = MsgChat::CHAT_TYPE_COUNTRYOFFICIAL;
			text = text.substr( 3 );
		}

		//这里按照策划需求更改 记录每次不同聊天频道的时间 这次时间 - 上次这个聊天频道的时间 小于策划给定的一定数值情况下不可以聊天
		if( szData[0] != 0 && (szData[0] != '/' || bRoll) )
		{
			clock_t* pcoldtime = 0;
			clock_t* plisttime = 0;
			std::string err;
			switch (nNewChannel)
			{
			case MsgChat::CHAT_TYPE_GUILD:
				{
					pcoldtime = &_tmGuildColdTime;
					plisttime = &_tmGuildLastTime;
					err = _strGuildError;
				}break;
			case MsgChat::CHAT_TYPE_TERM:
				{
					pcoldtime = &_tmTeamColdTime;
					plisttime = &_tmTeamLastTime;
					err = _strTeamError;
				}break;
			case MsgChat::CHAT_TYPE_SHOUT:	
				{
					pcoldtime = &_tmShoutColdTime;
					plisttime = &_tmShoutLastTime;
					err = _strShoutError;
				}break;
			case MsgChat::CHAT_TYPE_HIGHSHOUT:
				{
					pcoldtime = &_tmHighShoutColdTime;
					plisttime = &_tmHighShoutLastTime;
					err = _strHighShoutError;
				}break;
			case MsgChat::CHAT_TYPE_PRIVATE:
				{
					pcoldtime = &_tmPrivateColdTime;
					plisttime = &_tmPrivateLastTime;
					err = _strPrivateError;
				}break;
			case MsgChat::CHAT_TYPE_MS:
				{
					pcoldtime = &_tmMessageColdTime;
					plisttime = &_tmMessageLastTime;
					err = _strMessageError;
				}break;
            case MsgChat::CHAT_TYPE_LEAGUE:
                {
                    pcoldtime = &_tmLeagueColdTime;
                    plisttime = &_tmLeagueLastTime;
                    err = _strLeagueError;
                }break;
			case MsgChat::CHAT_TYPE_BATTLE:
				{
					pcoldtime = &_tmZhenYingColdTime;
					plisttime = &_tmZhenYingLastTime;
					err = _strZhenYingError;
				}
                break;
			case MsgChat::CHAT_TYPE_COUNTRY:
				{
					pcoldtime = &_tmCountryColdTime;
					plisttime = &_tmCountryLastTime;
					err = _strCountryError;
				}
				break; //lyh++
			case MsgChat::CHAT_TYPE_COUNTRYOFFICIAL:
				{
					pcoldtime = &_tmNormalColdTime;
					plisttime = &_tmNormalLastTime;
					err = _strNormalError;
				}
				break;

			default:
				pcoldtime = &_tmNormalColdTime;
				plisttime = &_tmNormalLastTime;
				err = _strNormalError;
				break;
			}

			clock_t tmNow = clock();
            //if( !bOpenDebugInfo )
				if( *plisttime != 0 && tmNow - *plisttime >= 0 && tmNow - *plisttime < *pcoldtime )
			    {
					SCharItem item;
					if (thePlayerRole.m_bag.GetItemByItemID(6108, &item) && nDefaultChannel == MsgChat::CHAT_TYPE_HIGHSHOUT)
					{
						std::string strChat = szData;
						//strChat = CChatCheck::getInstance()->CheckStringInLowMark((char*)szData, '*');

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

						AddMyChatHistories(szData);

						currChatHistoryIndex_ = -1;

						*m_pID_EDIT_INPUT = "";

						m_pID_EDIT_INPUT->SetActivate( false );
						s_CUI_ID_FRAME_FACE.SetVisable( false );
						// Disable IME (input method editor) 
						ImmAssociateContext( g_hWnd, NULL );

						memset( _HyberItemInfo, 0, sizeof(_HyberItemInfo) );
						memset( _HyberItemId, 0, sizeof(_HyberItemId) );
						memset( _HyberType, 0, sizeof(_HyberType) );
						ItemHyberCnt = 0;
						IsSetPet = false;
						nAddressHyberCnt = 0;
						for(int i=0; i<ITEM_HYBER_MAX_CNT; ++i)
						{
							_saveItemHyber[i].clear();
						}

						char text[MAX_PATH] = {0};
						int remiantime = (int)((int)(*pcoldtime + *plisttime - tmNow) / 1000);
						if( remiantime == 0 )
							remiantime = 1;
						sprintf(text, theXmlString.GetString(eText_IfUseLaBa), remiantime);

						s_CUI_ID_FRAME_MessageBox.Show( text, "", CUI_ID_FRAME_MessageBox::eTypeYesNo,
							false, HighShoutVIPCallback, &msg, sizeof(MsgChat) );
						CUI_ID_FRAME_MessageBox::S_MessageBox* pMsg = &s_CUI_ID_FRAME_MessageBox.m_ltMessagBox.front();
						pMsg->useHotKeyCount = 1;
					}
					else
					{				   
                        if( nDefaultChannel == MsgChat::CHAT_TYPE_PRIVATE )
                        {
                            // 判断密聊内容是否为空
                            if( szData && strlen(szData) > 0 )
                            {
                                int len = strlen(szData);
                                char *pContent = strchr((char*)szData,' ');
                                if( pContent && pContent - szData == len-1 )
                                {
                                    return;
                                }
                            }
                        }
						//ShowTextInChatList( err.c_str() );
						char msg[MAX_PATH] = {0};
						int remiantime = (int)((int)(*pcoldtime + *plisttime - tmNow) / 1000);
						if( remiantime == 0 )
							remiantime = 1;
						sprintf(msg, err.c_str(), remiantime);
						CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Chat_ChannelTip, msg );

						m_pID_EDIT_INPUT->SetActivate( false );
						s_CUI_ID_FRAME_FACE.SetVisable( false );
						// Disable IME (input method editor) 
						ImmAssociateContext( g_hWnd, NULL );
					}

				    return;
			    }

            //*plisttime = tmNow;
        }

		if ( szData[0] != 0 )
		{
			//LuaScript *pScript = (LuaScript*)g_GetScript(LUA_UICHAT);
			//if( pScript )
			//{
			//	std::string text = szData;
			//	switch (nDefaultChannel)
			//	{
			//	case MsgChat::CHAT_TYPE_GUILD:		text = "/g ";	text += szData; break;
			//	case MsgChat::CHAT_TYPE_TERM:		text = "/p ";	text += szData; break;
			//	case MsgChat::CHAT_TYPE_SHOUT:		text = "/h ";	text += szData; break;
			//	case MsgChat::CHAT_TYPE_HIGHSHOUT:	text = "/sh ";	text += szData; break;
			//	case MsgChat::CHAT_TYPE_PRIVATE:		text = "/w ";	text += szData; break;
			//	case MsgChat::CHAT_TYPE_GM:			text = "/gm ";	text += szData; break;
			//	case MsgChat::CHAT_TYPE_MS:			text = "/ms ";	text += szData; break;
			//	}
			//	pScript->GetGlobalFun(LUAEVENT_ON_ChatSend)(text.c_str());
			//}

            switch (nNewChannel)
            {
            case MsgChat::CHAT_TYPE_GUILD:
                {
                    CGangMgr* theGuild = thePlayerRole.GetGangMgr();
                    if(theGuild == NULL || theGuild->GetGuildID() == GuildDefine::InitID)
                    {
                        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Chat_ChannelTip, theXmlString.GetString( eClient_AddInfo_2slk_9 ) );
                        return;
                    }
                    text = "/g " + text;
                    CommandChat(text.substr(1).c_str()); 
                }break;
            case MsgChat::CHAT_TYPE_LEAGUE:
                {
                    CGangMgr* theGuild = thePlayerRole.GetGangMgr();
                    if(theGuild == NULL || theGuild->GetGuildID() == GuildDefine::InitID)
                    {
                        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Chat_ChannelTip, theXmlString.GetString( eClient_AddInfo_2slk_9 ) );
                        return;
                    }
                    text = "/l " + text;
                    CommandChat(text.substr(1).c_str()); 
                }break;
            case MsgChat::CHAT_TYPE_TERM:
                {
					if(thePlayerRole.GetTeamMemberNum() <= 0)
					{
                        CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Chat_ChannelTip, theXmlString.GetString( eText_Team_NoTeam ) );
						return;
					}

                    text = "/p " + text;
                    CommandChat(text.substr(1).c_str()); 
                }break;
            case MsgChat::CHAT_TYPE_SHOUT:	
                {
                    text = "/h " + text;
                    CommandChat(text.substr(1).c_str()); 
                }break;
            case MsgChat::CHAT_TYPE_HIGHSHOUT:
                {
                    text = "/sh " + text;
                    CommandChat(text.substr(1).c_str()); 
                }break;
            case MsgChat::CHAT_TYPE_PRIVATE:
                {
                    text = "/w " + text;
                    CommandChat(text.substr(1).c_str()); 
                }break;
            case MsgChat::CHAT_TYPE_GM:
                {
                    text = "/gm " + text;
                    CommandChat(text.substr(1).c_str()); 
                }break;
            case MsgChat::CHAT_TYPE_MS:
                {
                    text = "/ms " + text;
                    CommandChat(text.substr(1).c_str()); 
                }break;
            case MsgChat::CHAT_TYPE_BATTLE:
                {
                    // 是否在战场里
                    // 					if( !thePlayerRole.IsCampBattleInMap() )
                    // 					{
                    // 						GetShowScreenText() ->AddInfo( theXmlString.GetString( eText_ZhenYingChat_NotInBattle ), Color_Config.getColor( CC_Center_WarningErrorInfo ), 0, FIGHTHINTMESSAGEROW );
                    // 						s_CUI_ChatInfoBox.AddInfo( theXmlString.GetString(eText_ZhenYingChat_NotInBattle), Color_Config.getColor( CC_SystemPromp ) );
                    // 						return;
                    // 					}
                    // 					text = "/b ";	text += szData;
                    // 					CommandChat(text.substr(1).c_str()); 
                }break;
            case MsgChat::CHAT_TYPE_COUNTRY:
                {
                    text = "/c " + text;
                    CommandChat(text.substr(1).c_str()); 
                }break;
				//lyh++
			case MsgChat::CHAT_TYPE_COUNTRYOFFICIAL:
				{
					text = "/y " + text;
					CommandChat(text.substr(1).c_str()); 
				}break;

			case MsgChat::CHAT_TYPE_FAMILY:
				{
					text = "/f " + text;
					CommandChat(text.substr(1).c_str()); 
				}
				break;
            default:
                SendMsgChatNormal(text.c_str());
                break;
            }
			if (szData[0] == '/')
			{
				std::string strCommand = szData;
				DebugCommand(strCommand.substr(1).c_str());
			}

			//SendMsgChatNormal(szData);
		}

		AddMyChatHistories(szData);

		currChatHistoryIndex_ = -1;

		*m_pID_EDIT_INPUT = "";

		m_pID_EDIT_INPUT->SetActivate( false );
		s_CUI_ID_FRAME_FACE.SetVisable( false );
		// Disable IME (input method editor) 
		ImmAssociateContext( g_hWnd, NULL );

		memset( _HyberItemInfo, 0, sizeof(_HyberItemInfo) );
		memset( _HyberItemId, 0, sizeof(_HyberItemId) );
		ItemHyberCnt = 0;
		IsSetPet = false;
		nAddressHyberCnt = 0;
		for(int i=0; i<ITEM_HYBER_MAX_CNT; ++i)
		{
			_saveItemHyber[i].clear();
		}
	}
}

void CommonChatFrame::loadXmlChatColdTime()
{
    MeXmlDocument GlobalConfigXMLDocument;
    bool bRet = GlobalConfigXMLDocument.LoadFile( XML_GLOBALCONFIG_FILENAME );
    assert( bRet && "无法读取全局配置文件,将读取默认设置" );
    if( !bRet )
        return;

    MeXmlElement* pRoot = GlobalConfigXMLDocument.FirstChildElement( XML_GLOBALCONFIG_ROOT_NAME );
    assert( pRoot && "读取全局配置文件根节点失败" );

	//MeXmlDocument	m_MeXmlDoc;
	//if( !m_MeXmlDoc.LoadFile(XML_COLDTIME_PATH) )
	//{
	//	//assert(false && "Login.cpp::LoadConfigXml 读取文件不错");
	//	OutputDebugString( "CUI_ChatInfoBox" );
	//	return;
	//}
	//MeXmlElement*	pRoot = m_MeXmlDoc.FirstChildElement( "Project" );
    int nName = -1;
    int nColdTime = 0;
    int iLevel = 0;
	if( !pRoot )
	    return;
	MeXmlElement*	pChatSetting = pRoot->FirstChildElement("ChatCoolDownSetting");
    if( !pChatSetting )
        return;

    MeXmlElement*	pChat = pChatSetting->FirstChildElement("chat");
	while( pChat )
	{
		pChat->Attribute("name", &nName);
		pChat->Attribute("coldtime", &nColdTime);
        pChat->Attribute("level", &iLevel);
		const char* desc = pChat->Attribute("descirptError");

		std::string szValue;
		if (desc)
			szValue = _tstring::toNarrowString(_tstring::UTF8towcs(desc).c_str());

		if( nName > -1 && nColdTime > 0)
		{
			switch(nName)
			{
			case MsgChat::CHAT_TYPE_NORMAL:
				_tmNormalColdTime = nColdTime;
				_strNormalError = szValue;
                _iNormalLevel = iLevel;
				break;
			case MsgChat::CHAT_TYPE_GUILD:
				_tmGuildColdTime = nColdTime;
				_strGuildError = szValue;
                _iGuildLevel = iLevel;
				break;
			case MsgChat::CHAT_TYPE_LEAGUE:
				_tmLeagueColdTime = nColdTime;
				_strLeagueError = szValue;
                _iLeagueLevel = iLevel;
				break;
			case MsgChat::CHAT_TYPE_TERM:
				_tmTeamColdTime = nColdTime;
				_strTeamError = szValue;
                _iTeamLevel = iLevel;
				break;
			case MsgChat::CHAT_TYPE_PRIVATE:
				_tmPrivateColdTime = nColdTime;
				_strPrivateError = szValue;
                _iPrivateLevel = iLevel;
				break;
			case MsgChat::CHAT_TYPE_MS:
				_tmMessageColdTime = nColdTime;
				_strMessageError = szValue;
				_iMessageLevel = iLevel;
				break;
			case MsgChat::CHAT_TYPE_SHOUT:
				_tmShoutColdTime = nColdTime;
				_strShoutError = szValue;
                _iShoutLevel = iLevel;
				break;
			case MsgChat::CHAT_TYPE_HIGHSHOUT:
				_tmHighShoutColdTime = nColdTime;
				_strHighShoutError = szValue;
                _iHighShoutLevel = iLevel;
				break;
			case MsgChat::CHAT_TYPE_BATTLE:
				_tmZhenYingColdTime = nColdTime;
				_strZhenYingError = szValue;
				_iZhenYingLevel = iLevel;
				break;
			case MsgChat::CHAT_TYPE_COUNTRY:
				_tmCountryColdTime = nColdTime;
				_strCountryError = szValue;
				_iCountryLevel = iLevel;
				break;
			}
		}

		pChat = pChat->NextSiblingElement();
	}
}

void CommonChatFrame::SetEditFocus()
{
	if (this == &s_CUI_ChatInfoBox)
	{
		g_bMessageChat = false;
		s_CUI_ChatInfoBox._bActiveInput = true;
		s_CUI_ChatInfoBox.SetVisable( true );
	}
	if (this == &s_CUI_ID_FRAME_Speaker)
		g_bMessageChat = false;
// 	else
// 		g_bMessageChat = true;

	theUiManager.SetFocus(m_pID_EDIT_INPUT);
	theUiManager.ToTop(m_pChatInfoBox);
}

void CommonChatFrame::AddMyChatHistories( const char* szData )
{
	if (szData != NULL && szData[0] != '\0')
	{
		ChatHistory chis;
		chis.chatInfo = szData;
		for(int i = 0; i < ItemHyberCnt; ++i)
		{
			chis.hyberItemInfos.push_back(_HyberItemInfo[i]);
			chis.hyberItemIds.push_back(_HyberItemId[i]);
		}
		chis.nAddressHyberCnt = nAddressHyberCnt;
		chatHistories_.push_front(chis);

		if (chatHistories_.size() > LAST_INFO_MAX)
			chatHistories_.pop_back();
	}
}

void CommonChatFrame::CalFaceRect()
{
	if(m_pChatInfoBox)
	{
		m_pChatInfoBox->GetRealRect(&faceRect);
		faceRect.left += (faceRect.right - faceRect.left) + 10;
		faceRect.top  = faceRect.bottom - 120 ;//(faceRect.bottom - faceRect.top)/2;
	}

}

void CommonChatFrame::Task_HyberOtherClick( ControlObject* pSender, const std::string& content ,int nId )
{
	char cContent[256];
	strcpy(cContent,content.c_str());
	int nLength = strlen(cContent);
	for (int i = 0; i < nLength; ++i )
	{
		if (cContent[i] == '(' || cContent[i] == ',' ||cContent[i] == ')')
		{
			cContent[i] = ' ';
		}
	}
	char cMapName[256];
	int MapX,MapY;

	sscanf(cContent,"%s %d %d",cMapName,&MapX,&MapY);

	//==================================
	//先查找是否本张地图 ，如果本张地图 这直接寻路过去
	CWorldTile* _pTile = SwGlobal::GetWorld()->GetWorldBuffer()->GetTileFromTileName(cMapName);

	if (_pTile)
	{
		if ((MapX < 0.f )|| (MapX > _pTile->GetWidth() - 1) || (MapY < 0.f) || (MapY > _pTile->GetDepth() - 1))
		{
			return;
		}

       CWorldTile* _pCurrTile = CURRENTTILE;
	   if (_pTile == _pCurrTile)
	   {
		   theHeroGame.GetPlayerMgr()->MoveRoleTo(MapX,MapY,true,false);
		   return;
	   }
	}
		

	//===================================
	
	short nMeCountry = -1;
	CPlayer* pMe = theHeroGame.GetPlayerMgr()->GetMe();
	if (pMe)
	{
		nMeCountry = pMe->GetRealCountry();
	}
	CWorldTile* pTile = SwGlobal::GetWorld()->GetWorldBuffer()->GetTileFromTileName(cMapName,nMeCountry);
	if (NULL == pTile)
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Map_FindPathFailed, theXmlString.GetString(eText_CannotCrossMapPathFindAddress) );
		return ;
	}
	if ((MapX < 0.f )|| (MapX > pTile->GetWidth() - 1) || (MapY < 0.f) || (MapY > pTile->GetDepth() - 1))
	{
		CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Map_FindPathFailed, theXmlString.GetString(eText_CannotCrossMapPathFindAddress) );
		return;
	}
	CWorldTile* pCurrTile = CURRENTTILE;
	assert(pCurrTile);
	if (pCurrTile == pTile)
	{
		theHeroGame.GetPlayerMgr()->MoveRoleTo(MapX,MapY,true,false);
	}
	else if( theHeroGame.GetPlayerMgr()->GetMe() )
	{//跨地图寻路
		float x,y;
		theHeroGame.GetPlayerMgr()->GetMe()->GetPos(&x,&y,NULL);
		bool bRet = CrossMapPF::Instance()->CrossMapFindPath(pCurrTile->GetMapId(),x,y,pTile->GetMapId(),MapX,MapY);
		if (!bRet)
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Map_FindPathFailed, theXmlString.GetString(eText_CannotCrossMapPathFindAddress) );
		}
	}

}
 
bool CommonChatFrame::addAddressText( int nMapId, int nMapX,int nMapY )
{	
	if( nAddressHyberCnt >= 1 )
	{
		std::string strEdit = m_pID_EDIT_INPUT->GetText();
		std::string::size_type nLeftPos = strEdit.find('<');
		std::string::size_type nRightPos = strEdit.find('>');

		if ((nLeftPos != std::string::npos) && (nRightPos != std::string::npos) && (nRightPos > nLeftPos + 1))
		{
			ShowTextInChatList( theXmlString.GetString(eClient_AddInfo_Address),0xFFAA0000 );
			return false;
		}
		else
		{
			nAddressHyberCnt = 0;
		}
	}
	CWorldTile* pTile = SwGlobal::GetWorld()->GetWorldBuffer()->GetTileFromMapId(nMapId);
	if (NULL == pTile)
	{
		return false;
	}
	if (nMapX < 0 || nMapX > pTile->GetWidth() || nMapY < 0 || nMapY > pTile->GetDepth())
	{
		return false;
	}
	char cAddText[256];
	const NpcCoordInfo* pInfo = NpcCoord::getInstance()->getNpcCoord(nMapId,nMapX,nMapY);
	if (pInfo)
	{
		sprintf(cAddText,"%s-<%s(%d,%d)>",Common::_tstring::toNarrowString(pInfo->_szName.c_str()).c_str(),pTile->GetTileName(),nMapX,nMapY);
	}
	else
	{
		sprintf(cAddText,"<%s(%d,%d)>",pTile->GetTileName(),nMapX,nMapY);
	}
	m_pID_EDIT_INPUT->addText( cAddText);
	nAddressHyberCnt++;
	Begin2Input();
	SetEditFocus();
// 	theUiManager.SetJumpNextLButtonUp(true);
	return true;
}

const char* CommonChatFrame::GetEditText()
{
	return m_pID_EDIT_INPUT->GetText();
}

int CommonChatFrame::GetFontIndex()
{
	if(m_pChatInfoBox)
		return m_pChatInfoBox->GetFontIndex();
	else
		assert(false&&"ui error");

	return 0;
}

RECT CommonChatFrame::GetRealRect()
{
	RECT rect;
	if(m_pChatInfoBox)
		m_pChatInfoBox->GetRealRect(&rect); 
	else 
		assert(false&&"ui error");

	return rect;
}

void CommonChatFrame::SetPos(int x,int y)
{
	if(m_pChatInfoBox)
		m_pChatInfoBox->SetPos(x,y);
	else
		assert(false&&"ui error");
}

ControlEdit* CommonChatFrame::GetActiveEditInput()
{
	if(!GetActiveChatFrame()->m_pID_EDIT_INPUT)
		assert(false&&"ui error");

	return GetActiveChatFrame()->m_pID_EDIT_INPUT;
}

ControlEdit* CommonChatFrame::GetEditInput()
{
	if(!m_pID_EDIT_INPUT)
		assert(false&&"ui error");

	return m_pID_EDIT_INPUT;
}

int CommonChatFrame::GetFontSize()
{
	if(m_pChatInfoBox)
		return m_pChatInfoBox->GetFontSize();
	else
		assert(false&&"ui error");

	return 0;
}

COLORREF CommonChatFrame::GetFontColor()
{
	COLORREF color(0);

	if(m_pChatInfoBox)
		return m_pChatInfoBox->GetFontColor();
	else
		assert(false&&"ui error");

	return color;
}

ControlFrame* CommonChatFrame::GetActiveChatInfoBox()
{
	if(!GetActiveChatFrame()->m_pChatInfoBox)
		assert(false&&"ui error");

	return GetActiveChatFrame()->m_pChatInfoBox;
}

void CommonChatFrame::_Initialize()
{
	m_pChatInfoBox = NULL;
	m_pID_EDIT_INPUT = NULL;
	m_pID_BUTTON_face = NULL;
	m_pChatInfoText = NULL;

	m_bEdtActive  = false;
	_bActiveInput = false;
	_nBagType = 0;
	m_dwChatType = 0xffffffff;//all channel


	memset( _HyberItemInfo, 0, sizeof(_HyberItemInfo) );
	memset( _HyberItemId, 0, sizeof(_HyberItemId) );
	ItemHyberCnt = 0;
	IsSetPet = false;
	nAddressHyberCnt = 0;
	for(int i=0; i<ITEM_HYBER_MAX_CNT; ++i)
	{
		_saveItemHyber[i].clear();
	}

	currChatHistoryIndex_ = -1;

	_tmNormalLastTime = 1000;
	_tmGuildLastTime = 2000;
	_tmTeamLastTime = 2000;
	_tmPrivateLastTime = 2000;
	_tmMessageLastTime = 2000;
	_tmShoutLastTime = 0;		//大喊 9宫格
	_tmHighShoutLastTime = 0;	//高喊	

	faceRect.top = 0;
	faceRect.left = 0;

	m_bSendMsg = false;
}

void CommonChatFrame::ClearHyberLinks()
{
	memset( _HyberItemInfo, 0, sizeof(_HyberItemInfo) );
	memset( _HyberItemId, 0, sizeof(_HyberItemId) );
	memset( _HyberType, 0, sizeof(_HyberType) );
	ItemHyberCnt = 0;
	IsSetPet = false;
	nAddressHyberCnt = 0;
	for(int i=0; i<ITEM_HYBER_MAX_CNT; ++i)
	{
		_saveItemHyber[i].clear();
	}
}