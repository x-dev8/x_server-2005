
#include "UIMgr.h"
#include "ErrorLog.h"
#include "FuncPerformanceLog.h"
#include "pack.h"
#include "UIStorage.h"
#include "Select.h"
#include "Login.h"
#include "Create.h"
#include "MessageBox.h"
#include "InputBox.h"
#include "NpcTaskDialogBox.h"
#include "Progress.h"
#include "ChatInfoBox.h"
#include "FaceDlg1.h"
#include "Shop.h"
#include "Main.h"
#include "Skill.h"
#include "Property.h"
#include "LoadMap.h"
#include "Target.h"
#include "ExitGame.h"
#include "Group.h"
#include "NpcChatDialogBox.h"
#include "ui/MiniMapUI.h"
#include "PrivateShop.h"
#include "PlayerPrivateShop.h"
#include "LotteryAwardExplainUI.h"
#include "IconManagerClient.h"
#include "Compound.h"
#include "Bargaining.h"
#include "Task.h"
#include "EscDlg.h"
#include "ActionUI.h"
#include "tips.h"
#include "target.h"
#include "baseProperty.h"
#include "rbtnMenu.h"
#include "PetRbtnMenu.h" 
#include "Group_Me.h"
#include "ui/GoldPlating.h"
#include "LotteryGameUI.h"
#include "FriendDlg.h"
#include "Rename.h"
#include "topinfo.h"
#include "Group_StateUI.h"
#include "Guild_Create.h"
#include "AddMember.h"
#include "exmain.h"
#include "SelectAssignMode.h"
#include "Task_Track.h"
#include "Pack_Ex.h"
#include "AllNpcList.h"
#include "customShortcutKey.h"
#include "SoftKeyboard.h"
#include "chat_particular.h"
#include "chat_list.h"
#include "ui/UiTitle.h"
#include "ui/BillBoard.h"
#include "Group_DeBuffUI.h"
#include "SeekEquip.h"
#include "ui/ExMenu.h"
#include "ui/FiveXing.h" 
#include "MeUi/UiLua.h"
#include "NpcTaskDialogBox.h"
#include "MeTerrain/SwGlobal.h"
#include "MiniChat.h"
#include "ChatMessageMgr.h"
#include "ChatHistory.h"
#include "ui/GameSettingUI.h"
#include "ui/GameSettingUIBase.h"
#include "ui/SystemSettingUI.h"
#include "EditPrice.h"
#include "ui/BatchShop.h"
#include "ui/Star.h"
#include "ui/BullSystem.h"
#include "WorldMap.h"
#include "SelfRbtnMenu.h"
#include "ui/MainMenu.h"
#include "ui/Experience.h"
#include "ui/SeekPet.h"
#include "ui/Pet.h"
#include "ui/PickUp.h"
#include "ui/SaveMoney.h"
#include "ui/ActivityList.h"
#include "ui/ActivityTrack.h"
#include "ui/RightMainMenu.h"
#include "ui/RankList.h"
#include "ui/PopIntro.h"
#include "ui/NewSkillMain.h"
#include "ui/ShopCenter.h"
#include "UserData.h"
#include "ui/GameSetting.h"
#include "ui/LuckGameUI.h"
#include "ui/Speaker.h"
#include "ui/Decompound.h"
#include "ui/Trade.h"
#include "AutoAttackSet.h"
#include "ui/EspecialTask.h"
#include "ui/MoveStar.h"
//#include "ui/WebAward.h"
#include "ChangeEquip.h"
#include "FiveXingChange.h"
#include "FiveXingUpdate.h"
#include "ui/SpecialRepair.h"
#include "ui/EquipUpgrade.h"
#include "ui/SkillEquipUpdate.h"
#include "ui/SkillEquipChange.h"
#include "ui/EspecialTask2.h"
#include "ui/ShowScriptGif.h"
#include "OnlineAward.h"
#include "OnlineAward2.h"
#include "ui/ActivityMonthList.h"
#include "ui/JoinFight.h"
#include "PlayerRename.h"
#include "ui/Fcm.h"
#include "SuperPassword.h"
#include "SuperPasswordReset.h"
#include "SuperPasswordRegister.h"
#include "MailMain.h"
#include "PointShop.h"
#include "MoveStarUpgrade.h"
#include "StarMaterialUpgrade.h"
#include "GoldTrade.h"
#include "GoldTradeRegiste.h"
#include "GoldTradeTransfer.h"
#include "GoldTradeSelect.h"
#include "TeamBattleRequest.h"
#include "TeamBattleState.h"
#include "TeamBattleResult.h"
#include "FiveXingDisplace.h"
#include "GivePresent.h"
#include "Action.h"
#include "TeamBattleRule.h"
#include "TeamBattleShowTeamInfo.h"
#include "IntensifyStar.h"
#include "Country.h"
#include "InfoTips.h"
#include "InfoList.h"
#include "UiParseFunction.h"
#include "OnlineAward3.h"
#include "OnlineAward4.h"
#include "DeleteCase.h"
#include "../shortcutkey_configure.h"
#include "SystemSetting.h"
#include "FriendDlg.h"
#include "Gang.h"
#include "Achivement.h"
#include "Epic.h"
#include "SuAnimal.h"
#include "ui/ActivityDay.h"
#include "ui/Team.h"
#include "ui/Family.h"
#include "ui/SuAnimalCardList.h"
#include "ui/BasePropertyBGFrame.h"
#include "GamMenu.h"
#include "Protect.h"
#include "ProduceLearn.h"
#include "SuAnimalMore.h"
#include "TimeLimitTask.h"
#include "UIBase.h"
#include "CountryBaseInfo.h"
#include "ui/GuildBaseInfo.h"
#include "Card.h"
#include "WebActive.h"

LuaStateOwner state;

#define FIRST_LUA_FILENAME "CONFIG\\UI\\willbe2.lua"
#define UI_Mgr_File "CONFIG\\UI\\UIMgr.lua"
IScript *GetLuaScript()
{
	guardfunc;
	static LuaScript sLuaScript;
	return &sLuaScript;
	unguard;
}

CUIMgr *GetUIScriptMgr()
{
	guardfunc;
	return CUIMgr::Instance();
	unguard;
}

// void CUIMgr::AddUI( UI_OBJECT_TYPE eType, CUIBase *pObj )
// {
// 	guardfunc;
// 	m_UIMgr[eType] = pObj;
// 	return;
// 	unguard;
// }

void CUIMgr::AddUI( CUIBase *pObj )
{
	UIBaseList& UiList = GetUIList(pObj);
	for(UIBaseIter iter = UiList.begin(); iter!=UiList.end();++iter)
	{
		if (*iter == pObj)
		{
			return;
		}
	}
	UiList.push_back(pObj);
}
// void CUIMgr::DelUI( UI_OBJECT_TYPE eType )
// {
// 	guardfunc;
// 	UIMgr::iterator itUIMgr;
// 	std::vector<UIMgr::iterator> vtEraseUI;
// 	for( itUIMgr = m_UIMgr.begin() ; itUIMgr != m_UIMgr.end() ; ++itUIMgr  )
// 	{
// 		if( itUIMgr->first == eType  )
// 		{
// 			vtEraseUI.push_back( itUIMgr );
// 		}
// 	}
// 	for( int i=0; i < vtEraseUI.size(); i++ )
// 		m_UIMgr.erase( vtEraseUI[i] );
// 	return;
// 
// 	unguard;
// }

void CUIMgr::DelUI( CUIBase *pObj )
{
	if (pObj)
	{
		UIBaseList& UiList = GetUIList(pObj);
		for(UIBaseIter iter = UiList.begin(); iter!=UiList.end();++iter)
		{
			if (*iter == pObj)
			{
				pObj->UnLoadUI();
				UiList.erase(iter);
				return;
			}
		}
	}
}
void CUIMgr::Init()
{
	guardfunc;
	S_IconInfoBase::SetCreateIconInfoFunc( CreateIconInfo );
	S_IconInfoBase::SetRetrieveTimeString( RetriveTimeString );
	CIconInfoMouseTip::SetRetrieveSpareTimeString(RetriveSpareTimeString);
	ControlIconDrag::SetGlobalOnMouseMove( IconDragGlobalOnMouseMove );
	S_IconInfoBase::ms_pfGetReplacedName = S_IconInfoHero::ReplaceSpecifiedName;
	S_IconInfoBase::ms_pfGetItemLevel = S_IconInfoHero::GetItemLevel;
	S_IconInfoBase::ms_pfGetItemName = S_IconInfoHero::GetItemName;
// 	ControlList::ms_pfGlobalParseText = S_IconInfoHero::GlobalParseText;
	/*ControlText::SetShowUnderLine(true);
	ControlList::SetShowUnderLine(true);*/
	SetAllParseFuntion(); 
// 	ControlList::ms_pfFindHyperPlayer = FindPlayerHyper;
	m_UILifeTime = 300000;
	unguard;
}

// CUIBase *CUIMgr::GetUIObject( UI_OBJECT_TYPE eType )
// {
// 	guardfunc;
// 	UIMgr::iterator itUIMgr;
// 	for( itUIMgr = m_UIMgr.begin() ; itUIMgr != m_UIMgr.end() ; itUIMgr ++ )
// 	{
// 		if( itUIMgr->first == eType  )
// 		{
// 			return itUIMgr->second;
// 		}
// 	}
// 	return NULL;
// 	unguard;
// }

//这里添加得到Object的类型
// UI_OBJECT_TYPE CUIMgr::GetUIType( CUIBase* pObject)
// {
// 	guardfunc
// 	UIMgr::iterator iter = m_UIMgr.begin();
// 	for( ; iter != m_UIMgr.end(); ++iter )
// 	{
// 		if( iter->second == pObject)
// 			return iter->first;
// 	}
// 
// 	return (UI_OBJECT_TYPE)(eUI_OBJECT_Max + 1);
// 	unguard;
// }

extern int g_nTheRoleProfession;

void CUIMgr::loadUIs()
{
	guardfunc;
    
    // 加载常驻内存的UI，其他的为动态加载
    for( UIBaseIter it = m_UIList.begin(); it != m_UIList.end(); ++it )
    {
        if( ( *it )->IsHoldInMemory() )
            ( *it )->LoadUI();
    }

#ifdef _DEBUG
	try
	{
		state->DoFile( FIRST_LUA_FILENAME );
	}
	catch (LuaPlus::LuaException &e)
	{
		char szErr[256] = {0};
		_snprintf(szErr, sizeof(szErr)-1, "加载初始lua文件%s出错%s", FIRST_LUA_FILENAME, e.GetErrorMessage());
		print_error( szErr );
	}

	try
	{
		LuaObject table1Obj2 = state->GetGlobal( "willbe2" );

		if( table1Obj2.IsTable() )
		{
			LuaFunction<void> function_( table1Obj2["LoadUI"] );
			function_();
		}
	}
	catch (LuaPlus::LuaException &e)
	{
		char szErr[256] = {0};
		_snprintf(szErr, sizeof(szErr)-1, "%s.lua[%s函数调用出错]: %s", "willbe2","LoadUI", e.GetErrorMessage());
		print_error( szErr );
	}

#endif
	unguard;
}

void CUIMgr::clearUIs()
{
	guardfunc;

    theIconDragManager.ClearDrag();
	chatMessageManage.Hide();
	s_CUI_ID_FRAME_MessageBox.ClearMessageCache();
	for(UIBaseIter iter = m_HoldInMemoryList.begin(); iter != m_HoldInMemoryList.end();++iter)
	{
		CUIBase* pUI = *iter;
// 		if (pUI->IsUILoad())
// 		{
// 			pUI->UnLoadUI();
// 		}
		pUI->SetVisable(false);
	}

	for(UIBaseIter iter = m_OtherList.begin(); iter != m_OtherList.end();++iter)
	{
		CUIBase* pUI = *iter;
		if (pUI->IsUILoad())
		{
			pUI->UnLoadUI();
		}
	}
	m_OtherList.clear();
	s_CUI_ChatInfoBox.ClearChat();
	s_CUI_ChatInfoBox.ResetAllFreeTip();

	s_CUI_ID_FRAME_Speaker.ClearChat();
	s_CUI_ID_FRAME_InfoList.ClearChat();
#ifdef _DEBUG
	try
	{
		LuaObject table1Obj2 = state->GetGlobal( "willbe2" );

		if( table1Obj2.IsTable() )
		{
			LuaFunction<void> function_( table1Obj2["UnLoadUI"] );
			function_();
		}
	}
	catch (LuaPlus::LuaException &e)
	{
		char szErr[256] = {0};
		_snprintf(szErr, sizeof(szErr)-1, "%s.lua[%s函数调用出错]: %s", "willbe2","UnLoadUI", e.GetErrorMessage());
		print_error( szErr );
	}
#endif
	unguard;
}

void CUIMgr::ShowUIInTimeOfLoadMap(bool bVisible)
{
	s_CUI_ID_FRAME_MainMenu.SetVisable(bVisible);
	s_CUI_ID_FRAME_Group_Me.SetVisable(bVisible);
	s_CUI_ID_FRAME_chatInfoList.SetVisable(/*bVisible*/!s_CUI_ID_FRAME_MiniMap.IsHideChatListChecked());
// 	s_CUI_ID_FRAME_ChatSystem.SetVisable(bVisible);
	s_CUI_ID_FRAME_MiniMap.SetVisable(bVisible);
	s_CUI_ID_FRAME_TRACK.SetVisable(bVisible);
	s_CUI_ID_FRAME_ActivityTrack.SetVisable(bVisible);
	s_CUI_ID_FRAME_MAIN.SetVisable(bVisible);
	s_CUI_ID_FRAME_ExMenu.SetVisable(false);
//	s_CUI_ID_FRAME_WebActive.SetVisable(bVisible);

	s_CUI_ID_FRAME_TimeLimitTask._SetVisable(false);
}

S_IconInfoBase* CUIMgr::CreateIconInfo()
{
	return MeNew S_IconInfoHero;
}
bool CUIMgr::IconDragGlobalOnMouseMove( ControlIconDrag::S_ListImg* pItem, bool bEnableCompare, const RECT& rcItem, ControlIconDrag* pThis )
{
	bool ret = false;
	bool bHaveCompare = false;
	ControlIconDrag::S_ListImg* pCompareItem = 0;
	ControlIconDrag::S_ListImg* pSecondCompareItem = NULL;
	if( pItem )
	{
		if( bEnableCompare && pItem->m_pkIconInfo )
		{
			ItemDefine :: SItemCommon* pItemDetail = GettheItemDetail().GetItemByID( pItem->m_pkIconInfo->GetItemId() );
			pCompareItem = pThis->GetCompareItem();
			if( pItemDetail 
				&& 
				( pItemDetail->ucItemType == ItemDefine::ITEMTYPE_WEAPON 
				|| pItemDetail->ucItemType == ItemDefine::ITEMTYPE_ARMOUR
				)
				)
			{
				ItemDefine::SItemCanEquip *pEquip = (ItemDefine::SItemCanEquip *)pItemDetail;
				{	
					BOOL bContinue = FALSE;
					std::vector<int> setPart;
					setPart.clear();
					for( int i=0; i< EEquipPartType_MaxEquitPart; i++ )
						if ( pEquip->arrayCanEquip[i] == 1 )
							setPart.push_back(i);
					
					if(!setPart.empty())
					{
						// 判断时装
						bool bFashion = pEquip->bFashion;
						const SCharItem* pCompareEquipItem = &thePlayerRole.m_pVisual->GetVisual( (int)bFashion )[setPart[0]];
						if( pCompareEquipItem&&pCompareEquipItem->itembaseinfo.ustItemID != 0)
						{
							pCompareItem->SetData( (void*)pCompareEquipItem, eIcon_Enable, eTipFlag_Normal, true, theHeroGame.GetPlayerMgr()->GetMyID() );
							bHaveCompare = true;
						}

						//主要用于戒指手镯
						if(setPart.size() > 1)
						{
							const SCharItem *pSecCompareEquipItem = &thePlayerRole.m_pVisual->GetVisual((int)bFashion)[setPart[1]];
							if(pSecCompareEquipItem&&pSecCompareEquipItem->itembaseinfo.ustItemID != 0)
							{
								//如果第一个位置有东西显示
								if(bHaveCompare)
								{
								   pSecondCompareItem = pThis->GetSecondCompareItem();
								   pSecondCompareItem->SetData((void*)pSecCompareEquipItem,eIcon_Enable,eTipFlag_Normal,true,theHeroGame.GetPlayerMgr()->GetMyID());
								}
								else
								{
									//如果第一个位置没有
									pCompareItem->SetData( (void*)pSecCompareEquipItem, eIcon_Enable, eTipFlag_Normal, true, theHeroGame.GetPlayerMgr()->GetMyID() );
									bHaveCompare = true;
								}
							}
						}


					}

				}
			}
		}

		if( bHaveCompare )
		{
			theIconInfoMouseTip.SetDisplayInfo( pItem->m_pkIconInfo,
				rcItem.left, rcItem.top, pThis->GetIsShop(),
				pThis->GetFontIndex(), pThis->GetData()->m_nFontSize * ControlObject::GetREAL_SCALE(NULL),
				pThis->GetData()->m_colFont,
				pThis->GetShowAllInfo(), pCompareItem->m_pkIconInfo, HQ_TimeGetTime(), pThis->GetDelayTime(),false,(pSecondCompareItem == NULL)?NULL:pSecondCompareItem->m_pkIconInfo );
			ret = true;
		}
		else
		{
			if (pItem->m_pkIconInfo->Id() != InvalidLogicNumber)
			{
				theIconInfoMouseTip.SetDisplayInfo( pItem->m_pkIconInfo,
					rcItem.left, rcItem.top, pThis->GetIsShop(),
					pThis->GetFontIndex(), pThis->GetData()->m_nFontSize * ControlObject::GetREAL_SCALE(NULL),
					pThis->GetData()->m_colFont,
					pThis->GetShowAllInfo(), 0, HQ_TimeGetTime(), pThis->GetDelayTime() );
				ret = true;
			}
			else
			{
				if (strlen(pThis->GetData()->m_szCaption) > 0)
				{
					theIconInfoMouseTip.SetDisplayInfo( pThis->GetTipInfo(),
						rcItem.left, rcItem.top, false,
						pThis->GetFontIndex(), pThis->GetFontSize(),
						pThis->GetData()->m_colFont,
						true );
					ret = true;
				}
			}
		}
	}
	return ret;
}

// bool CUIMgr::FindPlayerHyper(const std::wstring& wstrParse, std::wstring& wstrPlayer)
// {
// 	std::wstring szChatChanel;
// 	int nOffBeg = 0;
// 	int nOffEnd = 0;
// 
// 	std::wstring player;
// 
// 	//---玩家名字连接...------------------------------------------------------
// 	std::wstring szCompartLeft = Common::_tstring::toWideString( theXmlString.GetString(eClient_Chat_function_5) );
// 	std::wstring szCompartRight = Common::_tstring::toWideString( theXmlString.GetString(eClient_Chat_function_6) );
// 	int nLeftLength = szCompartLeft.size();
// 	int nRightLength = szCompartRight.size();
// 
// 	int nOffBegChat = -1;
// 
// 	if( (nOffBeg = wstrParse.find(szCompartLeft)) != -1 )
// 	{
// 		if( (nOffEnd = wstrParse.find(szCompartRight,nOffBeg)) != -1 )
// 		{
// 			szChatChanel = wstrParse.substr( nOffBeg, nOffEnd - nOffBeg + nRightLength);
// 			if( szChatChanel == Common::_tstring::toWideString( theXmlString.GetString(eText_Chat_0) ) )
// 			{
// 				if( ((nOffBegChat = wstrParse.find( Common::_tstring::toWideString( theXmlString.GetString(eClient_Chat_Begin) ), nOffBeg)) != -1) )
// 				{
// 					int privateNameBeg = -1;
// 					std::wstring szPrivateToYou = Common::_tstring::toWideString( theXmlString.GetString(eClient_Chat_DuiNiShuo) );
// 					std::wstring szYouPrivateOther = Common::_tstring::toWideString( theXmlString.GetString(eClient_Chat_NiDui) );
// 					std::wstring szPrivateSpeek =Common::_tstring::toWideString( theXmlString.GetString(eClient_Chat_Shuo) );
// 					player = wstrParse.substr( nOffEnd + nRightLength, nOffBegChat - nOffEnd - nRightLength );
// 
// 					int nLenDiscription = Common::_tstring::toWideString( theXmlString.GetString(eText_Chat_0) ).length();
// 					if( (privateNameBeg = player.find(szPrivateToYou)) == (nOffBegChat - szPrivateToYou.length() - nLenDiscription) )
// 					{
// 						player = player.substr( 0, privateNameBeg );
// 					}
// 					else if( (privateNameBeg = player.find(szYouPrivateOther)) == 0 )
// 					{
// 						int privateNameSpeak = -1;
// 						if( (privateNameSpeak = player.find(szPrivateSpeek)) == (nOffBegChat - szPrivateSpeek.length() - nLenDiscription) )
// 						{
// 							player = player.substr( szYouPrivateOther.length(), privateNameSpeak - szYouPrivateOther.length() );
// 						}
// 					}
// 
// 					wstrPlayer = player;
// 
// 					return true;
// 				}
// 			}
// 			else if( szChatChanel == Common::_tstring::toWideString( theXmlString.GetString(eText_Chat_Alignment)) )
// 			{
// 				if( ((nOffBegChat = wstrParse.find( Common::_tstring::toWideString( theXmlString.GetString(eClient_Chat_Begin) ), nOffBeg)) != -1) )
// 				{
// 					nOffEnd = wstrParse.rfind(szCompartRight,nOffBegChat);
// 					player = wstrParse.substr( nOffEnd + nRightLength, nOffBegChat - nOffEnd - nRightLength );
// 					wstrPlayer = player;
// 					return true;
// 				}
// 			}
// 			else if( szChatChanel == Common::_tstring::toWideString( theXmlString.GetString(eText_SystemBull)) )
// 			{
// 				return false;
// 			}
// 			else
// 			{
// 				if( ((nOffBegChat = wstrParse.find( Common::_tstring::toWideString( theXmlString.GetString(eClient_Chat_Begin) ), nOffBeg)) != -1) )
// 				{
// 					player = wstrParse.substr( nOffEnd + nRightLength, nOffBegChat - nOffEnd - nRightLength );//fixed it back[2008.7.29]
// 					wstrPlayer = player;
// 					return true;
// 				}
// 			}
// 		}
// 	}//-----------------------------------------------------------------end of player hyber
// 
// 
// 	return false;
// }

bool CUIMgr::OnKeyDown( WPARAM wParam, LPARAM lParam )
{
	guardfunc;
	if (s_CUI_ID_FRAME_custom.IsVisable())
		return false;

	//判断是否有messagebox的独占UI的存在 有的话 我们屏蔽掉
	if(s_CUI_ID_FRAME_MessageBox.HasModaleMessageBox())
		return false;
	if( g_shortcutKey_configure.hasKey(wParam, AN_Configure_ShortcutKey::AN_SCKC_uiBaseProperty) )
	{
		setVisableUI(&s_CUI_ID_FRAME_BasePropertyBGFrame);
		s_CUI_ID_FRAME_MainMenu.SetBasePropertyHighLight();
		//s_CUI_ID_FRAME_MainMenu.SetButStatePressPic();
		return s_CUI_ID_FRAME_MainMenu.SetBtnPicture(AN_Configure_ShortcutKey::AN_SCKC_uiBaseProperty,false);
		//return true;
	}
	else if( g_shortcutKey_configure.hasKey(wParam, AN_Configure_ShortcutKey::AN_SCKC_uiPack) )//背包 B 快捷键
	{
		setVisableUI(&s_CUI_ID_FRAME_PACK);
		s_CUI_ID_FRAME_MainMenu.SetPackHighLight();
		//s_CUI_ID_FRAME_MainMenu.SetButPackPressPic();
		return s_CUI_ID_FRAME_MainMenu.SetBtnPicture(AN_Configure_ShortcutKey::AN_SCKC_uiPack,false);
		//return true;
	}

	else if( g_shortcutKey_configure.hasKey(wParam, AN_Configure_ShortcutKey::AN_SCKC_uiTask) )
	{
		setVisableUI(&s_CUI_ID_FRAME_Task);
		s_CUI_ID_FRAME_MainMenu.SetTaskHighLight();
		//s_CUI_ID_FRAME_MainMenu.SetButTaskPressPic();
		return s_CUI_ID_FRAME_MainMenu.SetBtnPicture(AN_Configure_ShortcutKey::AN_SCKC_uiTask,false);
		//return true;
	}
	else if( g_shortcutKey_configure.hasKey(wParam, AN_Configure_ShortcutKey::AN_SCKC_uiSkill) )
	{
		s_CUI_ID_FRAME_SKILL.SetVisableWherefore(!s_CUI_ID_FRAME_SKILL.IsVisable(),CUI_ID_FRAME_SKILL::EWherefore_SkillBagLearn);
		//setVisableUI(&s_CUI_ID_FRAME_SKILL);
		s_CUI_ID_FRAME_MainMenu.SetSkillHighLight( false );
		//s_CUI_ID_FRAME_MainMenu.SetButSkillPressPic();
		return s_CUI_ID_FRAME_MainMenu.SetBtnPicture(AN_Configure_ShortcutKey::AN_SCKC_uiSkill,false);
		//return true;
	}

    // 组队    added by zhuomeng.hu		[11/8/2010]
     else if( g_shortcutKey_configure.hasKey(wParam, AN_Configure_ShortcutKey::AN_SCKC_uiGroup) )
     {
          setVisableUI(&s_CUI_ID_FRAME_Team);
		  s_CUI_ID_FRAME_GamMenu.SetZuDuiHighLight();
		  s_CUI_ID_FRAME_GamMenu.SetTeamBtnState(false);
          //s_CUI_ID_FRAME_MainMenu.SetButGroupPressPic();
 		 //return s_CUI_ID_FRAME_MainMenu.SetBtnPicture(AN_Configure_ShortcutKey::AN_SCKC_uiGroup,true);
         return true;
     }
	 //家族
 	else if( g_shortcutKey_configure.hasKey(wParam, AN_Configure_ShortcutKey::AN_SCKC_uiFamily) )
 	{
 		setVisableUI(&s_CUI_ID_FRAME_Family);
		s_CUI_ID_FRAME_GamMenu.SetFamilyHighLight();
		s_CUI_ID_FRAME_GamMenu.SetFamilyBtnState(false);
 		//s_CUI_ID_FRAME_MainMenu.SetButGroupPressPic();
 		//return s_CUI_ID_FRAME_MainMenu.SetBtnPicture(AN_Configure_ShortcutKey::AN_SCKC_uiFamily,true);
 		return true;
 	}
 	else if( g_shortcutKey_configure.hasKey(wParam, AN_Configure_ShortcutKey::AN_SCKC_uiGuild) )
 	{
 		//setVisableUI(&s_CUI_ID_FRAME_Gang);
		setVisableUI(&s_CUI_ID_FRAME_GuildBaseInfo);
		s_CUI_ID_FRAME_GamMenu.SetGuildHighLight();
		s_CUI_ID_FRAME_GamMenu.SetGuildBtnState(false);
 		//s_CUI_ID_FRAME_MainMenu.SetButGuildPressPic();
 		//return s_CUI_ID_FRAME_MainMenu.SetBtnPicture(AN_Configure_ShortcutKey::AN_SCKC_uiGuild,true);
 		return true;
 	}
 	else if( g_shortcutKey_configure.hasKey(wParam, AN_Configure_ShortcutKey::AN_SCKC_uiFriend) )
 	{
 		setVisableUI(&s_CUI_ID_FRAME_Friend);
		s_CUI_ID_FRAME_GamMenu.SetFriendHighLight();
		s_CUI_ID_FRAME_GamMenu.SetFriendBtnState(false);
 		//s_CUI_ID_FRAME_MainMenu.SetButFriendPressPic();
 		//return s_CUI_ID_FRAME_MainMenu.SetBtnPicture(AN_Configure_ShortcutKey::AN_SCKC_uiFriend,true);
 		return true;
 	}
	else if( g_shortcutKey_configure.hasKey(wParam, AN_Configure_ShortcutKey::AN_SCKC_uiOther) )
	{
		return true;
	}
	else if( g_shortcutKey_configure.hasKey(wParam, AN_Configure_ShortcutKey::AN_SCKC_uiCompound) )
	{
		setVisableUI(&s_CUI_ID_FRAME_Compound);
		//s_CUI_ID_FRAME_MainMenu.SetButCompoundPressPic();
		return s_CUI_ID_FRAME_MainMenu.SetBtnPicture(AN_Configure_ShortcutKey::AN_SCKC_uiCompound,false);
		//return true;
	}
	else if( g_shortcutKey_configure.hasKey(wParam, AN_Configure_ShortcutKey::AN_SCKC_openTitle) )
	{
		setVisableUI(&s_CUI_ID_FRAME_Title);
// 		s_CUI_ID_FRAME_ExMenu.SetTitlePressPic();
		return true;
	}
	
	else if( g_shortcutKey_configure.hasKey(wParam, AN_Configure_ShortcutKey::AN_SCKC_switchOperateMode) )
	{
		theHeroGame.OnChangeControlType(true);
		return true;
	}
	else if( g_shortcutKey_configure.hasKey(wParam, AN_Configure_ShortcutKey::AN_SCKC_switchCameraMode) )
	{
		theHeroGame.OnChangeControlType(false);
		return true;
	}
	
	else if( g_shortcutKey_configure.hasKey(wParam, AN_Configure_ShortcutKey::AN_SCKC_uiChangeSuit) )//zhuxincong 8.6 注释掉了成就 因为我要看学习生活技能的面板
	{
		s_CUI_ID_FRAME_Achivement.SetVisable(!s_CUI_ID_FRAME_Achivement.IsVisable());
		return true;
	}
	
	else if( g_shortcutKey_configure.hasKey(wParam, AN_Configure_ShortcutKey::AN_SCKC_uiTrack) )
	{
		s_CUI_ID_FRAME_TRACK.SetVisable(!s_CUI_ID_FRAME_TRACK.IsVisable());
		return true;
	}
	else if (g_shortcutKey_configure.hasKey(wParam, AN_Configure_ShortcutKey::AN_SCKC_uiHideOrSystem) )
	{
		//s_CUI_ID_FRAME_MainMenu.SetButSysPressPic();
		return s_CUI_ID_FRAME_MainMenu.SetBtnPicture(AN_Configure_ShortcutKey::AN_SCKC_uiHideOrSystem,false);
		//return true;
	}
	else if (g_shortcutKey_configure.hasKey(wParam, AN_Configure_ShortcutKey::AN_SCKC_uiRank) )
	{
		s_CUI_ID_FRAME_RankList.SetVisable(!s_CUI_ID_FRAME_RankList.IsVisable());
 		s_CUI_ID_FRAME_ExMenu.SetTaxisPressPic();
		s_CUI_ID_FRAME_ExMenu.SetTaxisHighLight();
		return true;
	}
	else if (g_shortcutKey_configure.hasKey(wParam, AN_Configure_ShortcutKey::AN_SCKC_uiShopCenter) )
	{
		s_CUI_ID_FRAME_ShopCenter.SetVisable(!s_CUI_ID_FRAME_ShopCenter.IsVisable());
		s_CUI_ID_FRAME_ExMenu.SetShopHighLight();
 		s_CUI_ID_FRAME_ExMenu.SetShopPressPic();
		return true;
	}
	else if(g_shortcutKey_configure.hasKey(wParam, AN_Configure_ShortcutKey::AN_SCKC_uiAutoAttack) )
	{
		//s_CUI_ID_FRAME_AutoAttackSet.SetVisable(!s_CUI_ID_FRAME_AutoAttackSet.IsVisable());
// 		s_CUI_ID_FRAME_ExMenu.SetAutoAttackPressPic();
		/*
		 *	Author 2012-9-15 zhuxincong
		 *	DESC: 一键挂机 shif+v
		 */
		
		//DESC:这里的情况是 在没有显示UI之前按快捷键是无法开启自动大概的，原因是因为没有载入UI，SetVisable(false)也是无法载入UI的
		//必须显示过下UI


		if (!s_CUI_ID_FRAME_AutoAttackSet.IsUILoad())
		{
			s_CUI_ID_FRAME_AutoAttackSet.SetVisable(true);
			s_CUI_ID_FRAME_AutoAttackSet.SetVisable(false);
	
		}

		if (s_CUI_ID_FRAME_AutoAttackSet.GetAutoFight().IsAutoFight())
		{
			s_CUI_ID_FRAME_AutoAttackSet.EndAutoAttack();
		}
		else
		{
			s_CUI_ID_FRAME_AutoAttackSet.BeginAutoAttack();

		}
		return true;
	}
	else if(g_shortcutKey_configure.hasKey(wParam,AN_Configure_ShortcutKey::AN_SCKC_uiChangeSuit))
	{
		s_CUI_ID_FRAME_ChangeEquip.SetVisable(!s_CUI_ID_FRAME_ChangeEquip.IsVisable());
// 		s_CUI_ID_FRAME_ExMenu.SetChangeEquipPressPic();
		return true;
	}
	else if(g_shortcutKey_configure.hasKey(wParam,AN_Configure_ShortcutKey::AN_SCKC_uiExpressionAction))
	{
		s_CUI_ID_FRAME_Action.SetVisable(!s_CUI_ID_FRAME_Action.IsVisable());
 		s_CUI_ID_FRAME_ExMenu.SetActionPressPic();
		return true;
	}
	else if(g_shortcutKey_configure.hasKey(wParam,AN_Configure_ShortcutKey::AN_SCKC_uiSuAnimal))
	{//宠物
		s_CUI_ID_FRAME_SuAnimal.SetVisable(!s_CUI_ID_FRAME_SuAnimal.IsVisable());
	/*	s_CUI_ID_FRAME_MainMenu.SetSuAnimalHighLight();
		s_CUI_ID_FRAME_MainMenu.SetSuanimalState(false);*/
		return true;
	}
	else if (g_shortcutKey_configure.hasKey(wParam,AN_Configure_ShortcutKey::AN_SCK_SuAnimalCard))
	{
		//s_CUI_ID_FRAME_SuAnimalCardList.SetVisable(!s_CUI_ID_FRAME_SuAnimalCardList.IsVisable());
		s_CUI_ID_FRAME_CARD.SetVisable( !s_CUI_ID_FRAME_CARD.IsVisable() );
		s_CUI_ID_FRAME_ExMenu.SetCardHighLight();
		s_CUI_ID_FRAME_ExMenu.SetCartState(false);
		return true;
	}
	else if (g_shortcutKey_configure.hasKey(wParam, AN_Configure_ShortcutKey::AN_SCKC_uiWealthProtect))
	{
		s_CUI_ID_FRAME_Protect.SetVisable( !s_CUI_ID_FRAME_Protect.IsVisable() );
		s_CUI_ID_FRAME_ExMenu.SetProtectHighLight();
		s_CUI_ID_FRAME_ExMenu.SetProtectPressPic();
		return true;
	}

	else if( g_shortcutKey_configure.hasKey(wParam, AN_Configure_ShortcutKey::AN_SCKC_uiPet) )//zhuxincong 7.2 快捷键H
	{
		s_CUI_ID_FRAME_Pet.SetVisable( !s_CUI_ID_FRAME_Pet.IsVisable() );
		return true;
	}


	else if (g_shortcutKey_configure.hasKey(wParam, AN_Configure_ShortcutKey::AN_SCKC_uiEpic))//zhuxincong 9.6 快捷键O 副将
	{
		s_CUI_ID_FRAME_SuAnimal.SetVisable(!s_CUI_ID_FRAME_SuAnimal.IsVisable());
		return true;
	}

	else if (g_shortcutKey_configure.hasKey(wParam, AN_Configure_ShortcutKey::AN_SCKC_uiChangeSuit))//zhuxincong 9.26 成就呼出UI I
	{
		s_CUI_ID_FRAME_Achivement.SetVisable(!s_CUI_ID_FRAME_Achivement.IsVisable());
		return true;
	}

	// zhuxincong 9.27 国家
	else if( g_shortcutKey_configure.hasKey(wParam, AN_Configure_ShortcutKey::AN_SCKC_uiCountry) )
	{
		s_CUI_ID_FRAME_BaseInfo.SetVisable(!s_CUI_ID_FRAME_BaseInfo.IsVisable());
		//s_CUI_ID_FRAME_Country.SetVisable(!s_CUI_ID_FRAME_Country.IsVisable());
		return true;
	}

	else if ( g_shortcutKey_configure.hasKey(wParam, AN_Configure_ShortcutKey::AN_SCKC_uiAchivement))//zhuxincong 8.6 快捷键V 改成了 挂机
	{
		s_CUI_ID_FRAME_AutoAttackSet.SetVisable(!s_CUI_ID_FRAME_AutoAttackSet.IsVisable());
		s_CUI_ID_FRAME_ExMenu.SetProtectHighLight();
		s_CUI_ID_FRAME_ExMenu.SetProtectPressPic();
		return true;

	}
	else if( g_shortcutKey_configure.hasKey(wParam, AN_Configure_ShortcutKey::AN_SCKC_openEvent) )
	{
		//setVisableUI(&s_CUI_ID_FRAME_ActivityList);
		s_CUI_ID_FRAME_ActivityList.SetVisable(!s_CUI_ID_FRAME_ActivityList.IsVisable());
		s_CUI_ID_FRAME_ExMenu.SetProtectHighLight();
		s_CUI_ID_FRAME_ExMenu.SetProtectPressPic();
		/*s_CUI_ID_FRAME_ExMenu.SetActivityPressPic();
		s_CUI_ID_FRAME_ExMenu.SetActivityDay1HighLight();*/

		return true;
	}
	return false;
	unguard;

}

void CUIMgr::setVisableUI( CUIBase *pObj )
{
	guardfunc;

	if (NULL == pObj)
	{
		return;
	}
	{
// 		GetErrorLog()->logString( "UI_SetVisable %d Exec", type );
		if (pObj == &s_CUI_ID_FRAME_Task)
		{
			s_CUI_ID_FRAME_Task.ShowUnderLine( !s_CUI_ID_FRAME_Task.IsVisable() );			
		}
		pObj->SetVisable(!pObj->IsVisable());
// 		switch(type)
// 		{
// 		case eUI_OBJECT_Task:
// 			{
// 				s_CUI_ID_FRAME_Task.ShowUnderLine( !s_CUI_ID_FRAME_Task.IsVisable() );			
// 				s_CUI_ID_FRAME_Task.SetVisable(!s_CUI_ID_FRAME_Task.IsVisable());
// 			}
// 			break;
// 		case eUI_OBJECT_Pack:
// 			{
// 				s_CUI_ID_FRAME_PACK.SetVisable( !s_CUI_ID_FRAME_PACK.IsVisable() );
// 			}
// 			break;
// 		case eUI_OBJECT_Skill:
// 			{
// 				s_CUI_ID_FRAME_SKILL.SetVisable( !s_CUI_ID_FRAME_SKILL.IsVisable() );
// 			}
// 			break;
// 		case eUI_OBJECT_FriendDlg:
// 			{
// 				s_CUI_ID_FRAME_Friend.SetVisable( !s_CUI_ID_FRAME_Friend.IsVisable() );
// 			}
// 			break;
// 		case eUI_OBJECT_DlgGang:
// 			{
// 				s_CUI_ID_FRAME_Gang.SetVisable(  !s_CUI_ID_FRAME_Gang.IsVisable() );
// 				break;
// 			}
// 		case eUI_OBJECT_BaseProperty:
// 			{
// 				s_CUI_ID_FRAME_BaseProperty.SetVisable(!s_CUI_ID_FRAME_BaseProperty.IsVisable());
// 			}
// 			break;
// 		case eUI_OBJECT_Title:
// 			{
// 				s_CUI_ID_FRAME_Title.SetVisable( !s_CUI_ID_FRAME_Title.IsVisable() );
// 			}
// 			break;
// 		case eUI_OBJECT_Event:
// 			{
// 				s_CUI_ID_FRAME_ActivityList.SetVisable( !s_CUI_ID_FRAME_ActivityList.IsVisable() );
// 			}
// 			break;
// 		default:
// 			{
// 				CUIBase* pObject = GetUIScriptMgr()->GetUIObject( (UI_OBJECT_TYPE)type );
// 				if( pObject )
// 					pObject->SetVisable( !pObject->IsVisable() );
// 			}
// 			break;
// 		}

	}
	unguard;

}

bool CUIMgr::OnKeyUp( WPARAM wParam, LPARAM lParam )
{
	if( g_shortcutKey_configure.hasKey(wParam, AN_Configure_ShortcutKey::AN_SCKC_uiBaseProperty) )
	{
		s_CUI_ID_FRAME_MainMenu.SetBtnPicture(AN_Configure_ShortcutKey::AN_SCKC_uiBaseProperty,true);
	}
	else if( g_shortcutKey_configure.hasKey(wParam, AN_Configure_ShortcutKey::AN_SCKC_uiPack) )
	{
		s_CUI_ID_FRAME_MainMenu.SetBtnPicture(AN_Configure_ShortcutKey::AN_SCKC_uiPack,true);
	}
	
	/*else if (g_shortcutKey_configure.hasKey(wParam, AN_Configure_ShortcutKey::AN_SCKC_uiPet))
	{
		s_CUI_ID_FRAME_MainMenu.SetBtnPicture(AN_Configure_ShortcutKey::AN_SCKC_uiPet,true);
	}*/
	else if( g_shortcutKey_configure.hasKey(wParam, AN_Configure_ShortcutKey::AN_SCKC_uiTask) )
	{
		s_CUI_ID_FRAME_MainMenu.SetBtnPicture(AN_Configure_ShortcutKey::AN_SCKC_uiTask,true);
	}
	else if( g_shortcutKey_configure.hasKey(wParam, AN_Configure_ShortcutKey::AN_SCKC_uiSkill) )
	{
		s_CUI_ID_FRAME_MainMenu.SetBtnPicture(AN_Configure_ShortcutKey::AN_SCKC_uiSkill,true);
	}
    // 组队         added by zhuomeng.hu		[11/8/2010]
    else if( g_shortcutKey_configure.hasKey(wParam, AN_Configure_ShortcutKey::AN_SCKC_uiGroup) )
    {
//         s_CUI_ID_FRAME_MainMenu.SetButGroupNormalPic();
		s_CUI_ID_FRAME_GamMenu.SetTeamBtnState(true);
    }
 	else if( g_shortcutKey_configure.hasKey(wParam, AN_Configure_ShortcutKey::AN_SCKC_uiFamily) )
	{
		s_CUI_ID_FRAME_GamMenu.SetFamilyBtnState(true);
	}
	else if( g_shortcutKey_configure.hasKey(wParam, AN_Configure_ShortcutKey::AN_SCKC_uiGuild) )
	{
		//s_CUI_ID_FRAME_MainMenu.SetBtnPicture(AN_Configure_ShortcutKey::AN_SCKC_uiGuild,true);
		s_CUI_ID_FRAME_GamMenu.SetGuildBtnState(true);
	}
	else if( g_shortcutKey_configure.hasKey(wParam, AN_Configure_ShortcutKey::AN_SCKC_uiFriend) )
	{
		//s_CUI_ID_FRAME_MainMenu.SetBtnPicture(AN_Configure_ShortcutKey::AN_SCKC_uiFriend,true);
		s_CUI_ID_FRAME_GamMenu.SetFriendBtnState(true);
	}
	else if( g_shortcutKey_configure.hasKey(wParam, AN_Configure_ShortcutKey::AN_SCKC_uiCompound) )
	{
		s_CUI_ID_FRAME_MainMenu.SetBtnPicture(AN_Configure_ShortcutKey::AN_SCKC_uiCompound,true);
	}
	else if( g_shortcutKey_configure.hasKey(wParam, AN_Configure_ShortcutKey::AN_SCKC_openTitle) )
	{
// 		s_CUI_ID_FRAME_ExMenu.SetTitleNormalPic();
	}
	
//else if( g_shortcutKey_configure.hasKey(wParam, AN_Configure_ShortcutKey::AN_SCKC_uiAchivement) )zhuxincong 8.6 注释掉了成就 因为我要看学习生活技能的面板
//	{
//// 		s_CUI_ID_FRAME_ExMenu.SetachievementNormalPic();
//	}
	else if (g_shortcutKey_configure.hasKey(wParam, AN_Configure_ShortcutKey::AN_SCKC_uiHideOrSystem) )
	{
		//s_CUI_ID_FRAME_MainMenu.SetButSysNormalPic();
		s_CUI_ID_FRAME_MainMenu.SetBtnPicture(AN_Configure_ShortcutKey::AN_SCKC_uiHideOrSystem,true);
	}
	else if (g_shortcutKey_configure.hasKey(wParam, AN_Configure_ShortcutKey::AN_SCKC_uiRank) )
	{
 		s_CUI_ID_FRAME_ExMenu.SetTaxisNormalPic();
	}
	else if ( g_shortcutKey_configure.hasKey(wParam, AN_Configure_ShortcutKey::AN_SCKC_CallPrivteChat) )
	{
		s_CUI_ChatInfoBox.r_ShortcutPrivate();
		return true;
	}
	else if ( g_shortcutKey_configure.hasKey(wParam, AN_Configure_ShortcutKey::AN_SCKC_uiShopCenter) )
	{
 		s_CUI_ID_FRAME_ExMenu.SetShopNormalPic();
		return true;
	}
	else if(g_shortcutKey_configure.hasKey(wParam, AN_Configure_ShortcutKey::AN_SCKC_uiAutoAttack) )
	{
// 		s_CUI_ID_FRAME_ExMenu.SetAutoNormalPic();
		return true;
	}
	else if(g_shortcutKey_configure.hasKey(wParam,AN_Configure_ShortcutKey::AN_SCKC_uiChangeSuit))
	{
// 		s_CUI_ID_FRAME_ExMenu.SetChangeEquipNormalPic();
		return true;
	}
	else if(g_shortcutKey_configure.hasKey(wParam,AN_Configure_ShortcutKey::AN_SCKC_uiExpressionAction))
	{
 		s_CUI_ID_FRAME_ExMenu.SetActionNormalPic();
		return true;
	}
	else if(g_shortcutKey_configure.hasKey(wParam,AN_Configure_ShortcutKey::AN_SCKC_uiSuAnimal))
	{//宠物
		s_CUI_ID_FRAME_MainMenu.SetBtnPicture(AN_Configure_ShortcutKey::AN_SCKC_uiSuAnimal,true);
		return true;
	}
	else if (g_shortcutKey_configure.hasKey(wParam,AN_Configure_ShortcutKey::AN_SCK_SuAnimalCard))
	{
		s_CUI_ID_FRAME_ExMenu.SetCartState(true);
		return true;
	}
	else if (g_shortcutKey_configure.hasKey(wParam, AN_Configure_ShortcutKey::AN_SCKC_uiWealthProtect))
	{
		s_CUI_ID_FRAME_ExMenu.SetProtectNormalPic();
		return true;
	}
	else if( g_shortcutKey_configure.hasKey(wParam, AN_Configure_ShortcutKey::AN_SCKC_uiPet) )//zhuxincong 快捷键H
	{
		//s_CUI_ID_FRAME_MainMenu.SetButVehicleNormalPic();
		s_CUI_ID_FRAME_MainMenu.SetBtnPicture(AN_Configure_ShortcutKey::AN_SCKC_uiPet,true);
	}
	
	else if (g_shortcutKey_configure.hasKey(wParam, AN_Configure_ShortcutKey::AN_SCKC_uiEpic))//zhuxincong 9.6 快捷键O 副将
	{
		s_CUI_ID_FRAME_MainMenu.SetBtnPicture(AN_Configure_ShortcutKey::AN_SCKC_uiEpic,true);
	}

	else if (g_shortcutKey_configure.hasKey(wParam, AN_Configure_ShortcutKey::AN_SCKC_uiAchivement))//zhuxincong 快捷键V
	{
		s_CUI_ID_FRAME_MainMenu.SetBtnPicture(AN_Configure_ShortcutKey::AN_SCKC_uiAchivement,true);
	}
	else if( g_shortcutKey_configure.hasKey(wParam, AN_Configure_ShortcutKey::AN_SCKC_openEvent) )
	{
		s_CUI_ID_FRAME_MainMenu.SetBtnPicture(AN_Configure_ShortcutKey::AN_SCKC_uiAchivement,true);
	}
	return false;

}

CUIMgr::UIBaseList & CUIMgr::GetUIList( CUIBase* pUi )
{
	if (pUi->IsHoldInMemory())
	{
		return m_HoldInMemoryList;
	}
	return m_OtherList;

}

void CUIMgr::ClearHideUI()
{
	DWORD nCurrtime = HQ_TimeGetTime();
	UIBaseIter iter = m_OtherList.begin();
	while(iter != m_OtherList.end())
	{
		CUIBase* pUI = *iter;
		if (pUI->IsUILoad())
		{
			if (!pUI->IsVisable())
			{
				if (nCurrtime - pUI->GetLastVisibleTime() > m_UILifeTime)
				{
					pUI->UnLoadUI();
					iter = m_OtherList.erase(iter);
					continue;
				}
			}
			else
			{
				pUI->SetLastVisibleTime(nCurrtime);
			}
		}
		else
		{
			iter = m_OtherList.erase(iter);
			continue;
		}
		++iter;
	}
}

void CUIMgr::Destory()
{
	for(UIBaseIter iter = m_HoldInMemoryList.begin(); iter != m_HoldInMemoryList.end();++iter)
	{
		CUIBase* pUI = *iter;
		pUI->UnLoadUI();
	}
	m_HoldInMemoryList.clear();
	
	for(UIBaseIter iter = m_UIList.begin(); iter != m_UIList.end();++iter)
	{
		CUIBase* pUI = *iter;
		if (pUI)
		{
			pUI->UnLoadUI();
		}
	}
	m_UIList.clear();
}

void CUIMgr::InitAtEnterWorld()
{
    char szSetting[MAX_PATH] = {0};
    MeSprintf_s( szSetting, sizeof(szSetting)/sizeof(char) - 1, "%s%s", CUserData::Instance()->GetUserDataPath(),
        GameSetting::Instance()->GetCustomSettingDirectory() );
    GameSetting::Instance()->LoadSetting( szSetting );
	//LYH进入游戏的时候默认特效 和 玩家都显示
	GameSetting::Instance()->SetLevel( GameSetting::eGSC_OtherPlayerEffect,1 );
	GameSetting::Instance()->SetLevel( GameSetting::eGSC_OtherPlayerModel, 1 );
    GameSetting::Instance()->CommitChanges();
    SystemSetting::Instance()->CommitChanges();

    /*for( UIBaseIter it = m_UIList.begin(); it != m_UIList.end(); ++it )
    {
        if( ( *it )->IsHoldInMemory() )
            ( *it )->SetVisable( true );
    }*/

    BOOL bNeedPetAction = FALSE;
    if( g_nTheRoleProfession == EArmType_Mage )
    {
        bNeedPetAction = TRUE;
    }
    if( g_nTheRoleProfession == EArmType_Hunter )
    {
        bNeedPetAction = TRUE;
    }

    // 每次登陆需要调用的逻辑       added by ZhuoMeng.Hu		[10/18/2010]
    for( UIBaseIter iter = m_UIList.begin(); iter != m_UIList.end(); ++iter )
    {
        ( *iter )->InitializeAtEnterWorld();
    }
    s_CUI_ID_FRAME_MainMenu.refreshHotKey();
}

//-------------------------------------------------------------------------------------------------------------------------
const int OffsetX = 10;
inline void SetContainRect(IN OUT RECT& lhs, IN RECT& rhs)
{
	if (lhs.left > rhs.left)
	{
		lhs.left = rhs.left;
	}
	if (lhs.right < rhs.right)
	{
		lhs.right = rhs.right;
	}
}

RECT GetBigRect(ControlFrame* pFrame)
{
	RECT rect = { 0, 0, 0, 0}, rectTemp;
	if (!pFrame)
	{
		return rect;
	}

	pFrame->GetRealRect(&rect);
	const std::vector<ControlFrame*> frameVector = pFrame->m_vtChildFrame;
	for (std::vector<ControlFrame*>::const_iterator iter = frameVector.begin(); iter != frameVector.end(); ++iter)
	{
		if (!(*iter))
		{
			continue;
		}
		(*iter)->GetRealRect(&rectTemp);
		SetContainRect(rect, rectTemp);
	}
	return rect;
}

void ResetWindowPosition(ControlFrame* pLeft, ControlFrame* pRight)
{
	if (!pLeft || !pRight)
	{
		return;
	}

	RECT leftRect = GetBigRect(pLeft);
	RECT rightRect = GetBigRect(pRight);

	RECT scrLeftRect;
	pLeft->GetRealRect(&scrLeftRect);
	int leftOffsetX = leftRect.left - scrLeftRect.left;

	RECT scrRightRect;
	pRight->GetRealRect(&scrRightRect);
	int rightOffsetX = rightRect.left - scrRightRect.left;

	int rightWidth = rightRect.right - rightRect.left;
	int leftWidth = leftRect.right - leftRect.left;
	if (leftRect.right + rightWidth + OffsetX> SCREEN_WIDTH)
	{
		rightRect.right = SCREEN_WIDTH;
		rightRect.left = rightRect.right - rightWidth;
		leftRect.right = rightRect.left - OffsetX;
		leftRect.left = leftRect.right - leftWidth;
	}
	else
	{
		rightRect.left = leftRect.right + OffsetX;
	}

	scrLeftRect.left = leftRect.left - leftOffsetX;
	scrRightRect.left = rightRect.left - rightOffsetX;

	pLeft->MoveTo(scrLeftRect.left, scrLeftRect.top);
	pRight->MoveTo(scrRightRect.left, scrLeftRect.top);
}

void ResetWindowPositionEx(ControlFrame* pLeft, ControlFrame* pMiddle, ControlFrame* pRight)
{
	if (!pLeft || !pMiddle || !pRight)
		return;

	RECT leftRect = GetBigRect(pLeft);
	RECT middleRect = GetBigRect(pMiddle);
	RECT rightRect = GetBigRect(pRight);

	RECT scrLeftRect;
	pLeft->GetRealRect(&scrLeftRect);
	int leftOffsetX = leftRect.left - scrLeftRect.left;

	RECT scrMiddleRect;
	pMiddle->GetRealRect(&scrMiddleRect);
	int middleOffsetX = middleRect.left - scrMiddleRect.left;

	RECT scrRightRect;
	pRight->GetRealRect(&scrRightRect);
	int rightOffsetX = rightRect.left - scrRightRect.left;

	int rightWidth = rightRect.right - rightRect.left;
	int middleWidth = middleRect.right - middleRect.left;
	int leftWidth = leftRect.right - leftRect.left;

	if (leftRect.right + middleWidth + rightWidth + 2 * OffsetX> SCREEN_WIDTH)
	{
		rightRect.right = SCREEN_WIDTH;
		rightRect.left = rightRect.right - rightWidth;
		middleRect.right = rightRect.left - OffsetX;
		middleRect.left = middleRect.right - middleWidth;
		leftRect.right = middleRect.left - OffsetX;
		leftRect.left = leftRect.right - leftWidth;
	}
	else
	{
		middleRect.left = leftRect.right + OffsetX;
		rightRect.left = middleRect.right + OffsetX;
	}

	scrLeftRect.left = leftRect.left - leftOffsetX;
	scrMiddleRect.left = middleRect.left - middleOffsetX;
	scrRightRect.left = rightRect.left - rightOffsetX;

	pLeft->MoveTo(scrLeftRect.left, scrLeftRect.top);
	pMiddle->MoveTo(scrMiddleRect.left, scrMiddleRect.top);
	pRight->MoveTo(scrRightRect.left, scrLeftRect.top);
}

void CUIMgr::ResetDevice()
{
	for(UIBaseIter iter = m_HoldInMemoryList.begin(); iter != m_HoldInMemoryList.end();++iter)
	{
		CUIBase* pUI = *iter;
		pUI->ResetDevice();
	}

	for(UIBaseIter iter = m_OtherList.begin(); iter != m_OtherList.end();++iter)
	{
		CUIBase* pUI = *iter;
		if (pUI->IsUILoad())
		{
			pUI->ResetDevice();
		}
	}

}

void CUIMgr::RefreshByItemChange()
{
	for( UIBaseIter it = m_UIList.begin(); it != m_UIList.end(); ++it )
	{
		if( ( *it )->IsVisable() )
			( *it )->RefreshByItemChange();
	}

}

void CUIMgr::RefreshByMoneyChange()
{
	for( UIBaseIter it = m_UIList.begin(); it != m_UIList.end(); ++it )
	{
		if( ( *it )->IsVisable() )
			( *it )->RefreshByMoneyChange();
	}
}

void CUIMgr::RetriveSpareTimeString( S_IconInfoBase* pTip )
{	
	DWORD dwSpareTime = pTip->GetSpareTime();
	if( pTip && pTip->SpareTime() == MAX_SPARETIME )//约定，最大时间的时候为无限时间N/A
	{
		char szResult[ MAX_PATH ] = {0};	
		pTip->ClearOtherInfo();		
		sprintf_s( szResult, MAX_PATH, "%s%s%s", "<#ffe3ffff=", theXmlString.GetString( eText_Title_LeftTime ), "N/A" );
		pTip->SetOtherInfo( szResult, DT_LEFT );
	}
	else if( pTip && dwSpareTime > 0 && dwSpareTime < MAX_SPARETIME )
	{
		pTip->ClearOtherInfo();
		char szBufferT[ MAX_PATH ] = {0};		
		char szBufferS[ MAX_PATH ] = {0};
		char szBufferF[ MAX_PATH ] = {0};
		char szBufferM[ MAX_PATH ] = {0};
		char szResult[ MAX_PATH ] = {0};		
		int nSecond = dwSpareTime / 1000;		
		int nDay = nSecond / ( 24 * 60 * 60 ) ;	
		int nLeft = nSecond % ( 24 * 60 * 60 );
		int nHour = nLeft / ( 60 * 60 );
		nLeft = nLeft % ( 60 * 60 );
		int nMinute = nLeft / 60;
		nLeft = nLeft % 60;

		if( nDay > 0 )
			MeSprintf_s( szBufferT, MAX_PATH, "%d%s", nDay ,theXmlString.GetString( eText_Day ) );			

		if( nHour > 0 )
			MeSprintf_s( szBufferS, MAX_PATH, "%s%d%s", szBufferT, nHour ,theXmlString.GetString( eTimeUnit_Hour ) );			

		if( nMinute != 0 )
			MeSprintf_s( szBufferF, MAX_PATH, "%s%d%s", szBufferS, nMinute ,theXmlString.GetString( eTimeUnit_Minute ) );			

		MeSprintf_s( szBufferM, MAX_PATH, "%s%d%s", szBufferF, nLeft + 1 ,theXmlString.GetString( eTimeUnit_Second ) );

		// 颜色
		if( nSecond <= 60 )
		{
			MeSprintf_s( szResult, MAX_PATH, "%s%s%s", "<#ffff0000=", theXmlString.GetString( eText_Title_LeftTime ), szBufferM );			
		}
		else
		{
			MeSprintf_s( szResult, MAX_PATH, "%s%s%s", "<#ffe3ffff=", theXmlString.GetString( eText_Title_LeftTime ), szBufferM );
		}
		pTip->SetOtherInfo( szResult, DT_LEFT );
	}
}

void CUIMgr::RetriveTimeString( char* szBuffer, COLORREF& colTime, int nDay, int nHour, int nMinute, int nSecond )
{
	if( nDay > 0 )
	{
		sprintf( szBuffer, "%d%s", nDay ,theXmlString.GetString( eText_Day ) );
		colTime = 0xffe3ffff;
	}
	else if( nHour > 0 )
	{
		sprintf( szBuffer, "%d%s", nHour ,theXmlString.GetString( eTimeUnit_Hour ) );
		colTime = 0xffe3ffff;
	}
	else if( nMinute != 0 )
	{
		sprintf( szBuffer, "%d%s", nMinute ,theXmlString.GetString( eTimeUnit_Minute ) );
		colTime = 0xffe3ffff;
	}
	else
	{
		sprintf( szBuffer, "%d%s", nSecond+1 ,theXmlString.GetString( eTimeUnit_Second ) );
		colTime = 0xffff0000;
	}
}

void  CUIMgr::ProcessUiShowOrHide(bool bValue,CUIBase *pObject /*= NULL*/)
{
	for( UIBaseIter it = m_UIList.begin(); it != m_UIList.end(); ++it )
	{
		if(!(*it)->IsUILoad())
			continue;

		if(pObject&&(*it) == pObject)
			continue;

		if(bValue)
		{
			if((*it)->IsLastUiVisable())
				(*it)->SetVisable(true);
			else
				(*it)->SetVisable(false);
		}
		else
		{
			(*it)->SetLastUiVisable((*it)->IsVisable());
			(*it)->SetVisable(false);
		}
	}
}
