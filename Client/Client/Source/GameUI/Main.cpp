/********************************************************************
Created by UIEditor.exe
FileName: E:\Code\RunTime\CLIENT\Data\UI\Main.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "Main.h"
#include "Skill.h"
#include "Pack.h"
#include "Property.h"
#include "PrivateShop.h"
#include "FriendDlg.h"
#include "GameMain.h"
#include "ExpStage.h"
#include "../Player.h"
#include "PlayerRole.h"
#include "PlayerMgr.h"
#include "MiniMap.h"
#include "ChatInfoBox.h"
#include "Rename.h"
#include "Task.h"
#include "ExitGame.h"
#include "MeUi/ControlIconDragManager.h"
#include "EscDlg.h"
#include "ActionUI.h"
#include "baseProperty.h"
#include "Me3d/Config.h"
#include "Compound.h"
#include "Target.h"
#include "LuaFuns.h"
#include "SortLuaScript.h"
#include "Bargaining.h"
#include "MessageBox.h"
#include "color_config.h"
#include "XmlStringLanguage.h"
#include "Gang.h"
#include "exmain.h"
#include "Select.h"
#include "Login.h"
#include "../Effect.h"
#include "exmain.h"
#include "Group_Me.h"
#include "../Cfg.h"
#include "Pack_Ex.h"
#include "..\MotionBillBoard.h"
#include "../shortcutkey_configure.h"
#include "FaceDlg1.h"
#include "GameSettingUI.h"
#include "MainMenu.h"
#include "CharacterExp.h"
#include "AllNpcList.h"
#include "Dxsdk/dinput.h"
#include "PetMain.h"
#include "Pet.h"
#include "NewSkillMain.h"
#include "AutoAttackSet.h"
#include "bag/SkillBag.h"
#include "wsCamera.h"
#include "Action.h"
#include "ExpressionAction.h"
#include "GameSetting.h"
#include "SkillProduce.h"
#include "ScreenInfoManager.h"
#include "Target.h"
#include "Team.h"
#include "SuAnimal.h"
#include "SuAnimalMain.h"
#include "PetSettingConfig.h"
#include "SuAnimalCardList.h"
#include "CarryMain.h"
#include "zhujiangbianshen.h"
#include "TaiPingHuanJing.h"
#include "TPHJManger.h"
#include "ManualLevelUp.h"
#include "MeTerrain/NiColor.h"
#include "MeTerrain/SwType.h"
#include "MeTerrain/HashTable.h"
#include "MeTerrain/MapFile.h"
#include "MeTerrain/MapUtil.h"
#include "MeTerrain/SwGlobal.h"
#include "MeTerrain/World.h"
#include "MeTerrain/WorldBuffer.h"
#include "MeTerrain/WorldTile.h"
#include "MeTerrain/WorldChunk.h"
#include "MeTerrain/NdlWorldPickerBase.h"
#include "Me3d\PostProcess\PostProcess.h"
#include "Me3d\PostProcess\PostProcessManager.h"
#include "customShortcutKey.h"
#include "Ui/chat_list.h"
#include "Ui/InfoList.h"
#include "SelectChannel.h"

#define RIGHT_ROW_COUNT 6

extern CHeroGame* theApp;
extern GAME_STATE	g_GameState;
extern BOOL g_bMouseMoveMode; //鼠标移动模式
extern short GetKeyboardInput(int iKey);

static bool s_bShowExpandColumn = false;
static bool s_bBeingDragItem = false;
static bool s_bShowExpand2Column = false;

CUI_ID_FRAME_MAIN s_CUI_ID_FRAME_MAIN;

MAP_FRAME_RUN( s_CUI_ID_FRAME_MAIN, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_MAIN, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_MAIN, ID_BUTTON_FunctionOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_MAIN, ID_BUTTON_FightStateOnButtonClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_MAIN, ID_LISTIMG_HotkeyOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_MAIN, ID_LISTIMG_HotkeyOnIconRButtonUp )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_MAIN, ID_LISTIMG_HotkeyOnIconDragOn )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_MAIN, ID_BUTTON_MapOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_MAIN, ID_BUTTON_turnHotkeyUpOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_MAIN, ID_BUTTON_turnHotkeyDownOnButtonClick )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_MAIN, ID_CHECKBOX_AngleOnClick)
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_MAIN, ID_CHECKBOX_IsKeybordOnClick)
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_MAIN, ID_CHECKBOX_showbotkeyOnClick) 
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_MAIN, ID_BUTTON_ShowExmainOnButtonClick )
MAP_ICON_DRAG_DISABLE_ON_CALLBACK( s_CUI_ID_FRAME_MAIN, ID_LISTIMG_HotkyeOnIconDisableDragOn )
MAP_ICON_DRAG_DISABLE_OUT_CALLBACK( s_CUI_ID_FRAME_MAIN, ID_LISTIMG_HotkyeOnIconDisableDragOut )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_MAIN, ID_BUTTON_EnterOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_MAIN, ID_BUTTON_LevelUpOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_MAIN, ID_TEXT_LevelUpOnButtonClick )

MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_MAIN, ID_CHECKBOX_HideChatListOnClick)

static void OnDragItemBegin(ControlIconDrag* pList, ControlIconDrag::S_ListImg* pItem)
{
	if (pItem)
	{     
		s_bShowExpandColumn = s_CUI_ID_FRAME_Exmain.GetOnlyShowItemIcon1();
        s_bShowExpand2Column = s_CUI_ID_FRAME_Exmain.GetOnlyShowItemIcon2();
		s_CUI_ID_FRAME_Exmain.SetOnlyShowItemIcon1(false);
        s_CUI_ID_FRAME_Exmain.SetOnlyShowItemIcon2(false);
		s_bBeingDragItem = true;
	}
}

static void OnDragItemEnd(ControlIconDrag* pDstList, ControlIconDrag* pSrcList, ControlIconDrag::S_ListImg* pSrcListItem)
{
	if (pSrcListItem && s_bBeingDragItem)
    {
		s_CUI_ID_FRAME_Exmain.SetOnlyShowItemIcon1(s_bShowExpandColumn);
        s_CUI_ID_FRAME_Exmain.SetOnlyShowItemIcon2(s_bShowExpand2Column);
    }
	s_bBeingDragItem = false;
}

static bool UIMain_RButtonUp(int x, int y)
{
	if (s_CUI_ID_FRAME_PACK.GetDestroyItem())
	{
		s_CUI_ID_FRAME_PACK.SetDestroyItem(false);
		s_CUI_ID_FRAME_PACK.SetCancelOperator(true);
		return true;
	}
	else if (s_CUI_ID_FRAME_PACK.GetSplitItem())
	{
		s_CUI_ID_FRAME_PACK.SetSplitItem(false);
		s_CUI_ID_FRAME_PACK.SetCancelOperator(true);
		return true;
	}
	else if (s_CUI_ID_FRAME_SHOP.GetRepair())
	{
		s_CUI_ID_FRAME_SHOP.SetRepair(false);
		s_CUI_ID_FRAME_PACK.SetCancelOperator(true);
		return true;
	}
	else if (s_CUI_ID_FRAME_PACK.GetLockItem())
	{
		s_CUI_ID_FRAME_PACK.SetLockItem(false);
		s_CUI_ID_FRAME_PACK.SetCancelOperator(true);
		return true;
	}
	else if (s_CUI_ID_FRAME_PACK.GetUnLockItem())
	{
		s_CUI_ID_FRAME_PACK.SetUnLockItem(false);
		s_CUI_ID_FRAME_PACK.SetCancelOperator(true);
		return true;
	}
	else if (s_CUI_ID_FRAME_PACK.IsDecomposeItem())
	{
		s_CUI_ID_FRAME_PACK.DecomposeItem(true);
		return true;
	}
	return false;
}

bool UIMain_MsgProc( UINT msg, WPARAM wParam, LPARAM lParam, bool bMsgUsed )
{
	guardfunc;
	if ( bMsgUsed == true || g_GameState != G_MAIN  )
		return false;

	switch( msg ) 
	{
	case WM_LBUTTONDOWN:
		{
			if ( !theIconDragManager.m_pLastSelItem || !theIconDragManager.GetRemoveIcon() )
				return false;

			int nIndex = -1;
			int nWhere = -1;	//0:main  1:exmain 2:selectskill
			if( s_CUI_ID_FRAME_MAIN.IsHotKeyVisable() )
				nIndex = s_CUI_ID_FRAME_MAIN.GetHotKeyListImageIndex(theIconDragManager.m_pLastSelItem);

			if( nIndex != -1)
				nWhere = 0;
			if ( nIndex == -1 )
			{
                //如果挂机界面可见
                if(s_CUI_ID_FRAME_AutoAttackSet.IsVisable())
                {
                    //清空情况
                    ControlIconDrag::S_ListImg charItemImg;
                    
                    //攻击技能
					if( s_CUI_ID_FRAME_AutoAttackSet.GetListImage_SkillAttack() )
					{
						nIndex = s_CUI_ID_FRAME_AutoAttackSet.GetListImage_SkillAttack()->GetItemIndex(theIconDragManager.m_pLastSelItem);
						if(nIndex != -1)
						{
							s_CUI_ID_FRAME_AutoAttackSet.GetListImage_SkillAttack()->SetItem(&charItemImg,nIndex);
							s_CUI_ID_FRAME_AutoAttackSet.GetAutoFight().SetAttackSkill(NULL,nIndex);
							s_CUI_ID_FRAME_AutoAttackSet.SetSave(true);
							return true;
						}
					}

                    //辅助技能
					if( s_CUI_ID_FRAME_AutoAttackSet.GetListImage_SkillBuff() )
					{
						nIndex = s_CUI_ID_FRAME_AutoAttackSet.GetListImage_SkillBuff()->GetItemIndex(theIconDragManager.m_pLastSelItem);
						if(nIndex != -1)
						{
							s_CUI_ID_FRAME_AutoAttackSet.GetListImage_SkillBuff()->SetItem(&charItemImg,nIndex);
							s_CUI_ID_FRAME_AutoAttackSet.GetAutoFight().SetBufSkill(NULL,nIndex);
							s_CUI_ID_FRAME_AutoAttackSet.SetSave(true);
							return true;
						}
					}
					//回血技能
					if(s_CUI_ID_FRAME_AutoAttackSet.GetListImage_SkillHp())
					{
						nIndex = s_CUI_ID_FRAME_AutoAttackSet.GetListImage_SkillHp()->GetItemIndex(theIconDragManager.m_pLastSelItem);
						if(nIndex != -1)
						{
							s_CUI_ID_FRAME_AutoAttackSet.GetListImage_SkillHp()->SetItem(&charItemImg,nIndex);
							s_CUI_ID_FRAME_AutoAttackSet.GetAutoFight().SetRecSkill(NULL,nIndex,0);
							s_CUI_ID_FRAME_AutoAttackSet.SetSave(true);
							return true;
						}
					}
					//队伍回血技能
					if(s_CUI_ID_FRAME_AutoAttackSet.GetListImage_SkillHpTeam())
					{
						nIndex = s_CUI_ID_FRAME_AutoAttackSet.GetListImage_SkillHpTeam()->GetItemIndex(theIconDragManager.m_pLastSelItem);
						if(nIndex != -1)
						{
							s_CUI_ID_FRAME_AutoAttackSet.GetListImage_SkillHpTeam()->SetItem(&charItemImg,nIndex);
							s_CUI_ID_FRAME_AutoAttackSet.GetAutoFight().SetRecTeamSkill(NULL,nIndex,s_CUI_ID_FRAME_AutoAttackSet.GetAutoFight().GetRecHpTeamPer());
							s_CUI_ID_FRAME_AutoAttackSet.SetSave(true);
							return true;
						}
					}
					//lyh++ 清空操作的listImg
					//回血item
					if(s_CUI_ID_FRAME_AutoAttackSet.GetListImage_Hp())
					{
						nIndex = s_CUI_ID_FRAME_AutoAttackSet.GetListImage_Hp()->GetItemIndex(theIconDragManager.m_pLastSelItem);
						if(nIndex != -1)
						{
							s_CUI_ID_FRAME_AutoAttackSet.GetListImage_Hp()->SetItem(&charItemImg,nIndex);
							s_CUI_ID_FRAME_AutoAttackSet.GetAutoFight().m_HpItemId = 0;
							s_CUI_ID_FRAME_AutoAttackSet.SetSave(true);
							return true;
						}
					}

					//回蓝item
					if(s_CUI_ID_FRAME_AutoAttackSet.GetListImage_Mp())
					{
						nIndex = s_CUI_ID_FRAME_AutoAttackSet.GetListImage_Mp()->GetItemIndex(theIconDragManager.m_pLastSelItem);
						if(nIndex != -1)
						{
							s_CUI_ID_FRAME_AutoAttackSet.GetListImage_Mp()->SetItem(&charItemImg,nIndex);
							s_CUI_ID_FRAME_AutoAttackSet.GetAutoFight().m_MpItemId = 0;
							s_CUI_ID_FRAME_AutoAttackSet.SetSave(true);
							return true;
						}
					}

                }

				nIndex = s_CUI_ID_FRAME_Exmain.GetItemIndex1( theIconDragManager.m_pLastSelItem );
				if( nIndex == -1 )
				{
                    if(s_CUI_ID_FRAME_Exmain.IsListImgExmain2Visable())
                    {
                        nIndex = s_CUI_ID_FRAME_Exmain.GetItemIndex2( theIconDragManager.m_pLastSelItem );
                        if(nIndex != -1)
                           nWhere = 5;
                    }
				}
				else 
					nWhere = 1;
			}

			if (nWhere == -1)
				return false;

			//-- 这里清空鼠标当前拖动的icon
			theIconDragManager.ClearDrag();
			theIconDragManager.m_pLastSelItem = NULL;
			theIconDragManager.SetRemoveIcon(false);
			//---- 每次鼠标拖动没有ui接受的话 都要做这样清空处理。

			if( nWhere == 0 )
            {
                thePlayerRole.m_pHotKeyBag[nIndex+More_exMainUIMax+s_CUI_ID_FRAME_MAIN.GetHotKey()/*nIndexHotKey*/*More_ainUIMaxOnly].ItemData.itembaseinfo.ustItemID = InvalidLogicNumber;
                thePlayerRole.m_pHotKeyBag[nIndex+More_exMainUIMax+s_CUI_ID_FRAME_MAIN.GetHotKey()/*nIndexHotKey*/*More_ainUIMaxOnly].ShortCut.BagIndex = ErrorUnsignedShortID;
            }
            else if( nWhere == 1 )
            {
                thePlayerRole.m_pHotKeyBag[nIndex].ItemData.itembaseinfo.ustItemID = InvalidLogicNumber;
                thePlayerRole.m_pHotKeyBag[nIndex].ShortCut.BagIndex = ErrorUnsignedShortID;
            }
			else if( nWhere == 2 )
            {
                thePlayerRole.m_pHotKeyBag[More_rightSkill].ItemData.itembaseinfo.ustItemID = InvalidLogicNumber;
                thePlayerRole.m_pHotKeyBag[More_rightSkill].ShortCut.BagIndex = ErrorUnsignedShortID;
            }
            else if( nWhere == 3 )
            {
				thePlayerRole.m_pHotKeyBag[More_rightShortcutBegin+nIndex].ItemData.itembaseinfo.ustItemID = InvalidLogicNumber;
                thePlayerRole.m_pHotKeyBag[More_rightShortcutBegin+nIndex].ShortCut.BagIndex = ErrorUnsignedShortID;
            }
            else if( nWhere == 4 )
			{
				thePlayerRole.m_pHotKeyBag[More_skillEducate].ItemData.itembaseinfo.ustItemID = InvalidLogicNumber;
				thePlayerRole.m_pHotKeyBag[More_skillEducate].ShortCut.BagIndex = ErrorUnsignedShortID;
			}
            else if(nWhere == 5)
            {
                int nOffset = s_CUI_ID_FRAME_Exmain.GetItemCnt1();
                thePlayerRole.m_pHotKeyBag[nIndex + nOffset].ItemData.itembaseinfo.ustItemID = InvalidLogicNumber;
                thePlayerRole.m_pHotKeyBag[nIndex + nOffset].ShortCut.BagIndex = ErrorUnsignedShortID;
            }

			s_CUI_ID_FRAME_MAIN.RefeashHotKey();
			s_CUI_ID_FRAME_Exmain.RefeashHotNumber();

			// 更新快捷键给服务器
			thePlayerRole.SendHotKeyToServer();

			return true;
		}
		break;
	case WM_MBUTTONDOWN:
		{
			s_CUI_ID_FRAME_MAIN.useSkill( More_rightSkill, true );
		}
		break;
	case WM_KEYUP:
	case WM_SYSKEYDOWN:
		{
			if( theUiManager.GetFocus() )
			{//输入框获得焦点的话。
				if(theUiManager.GetFocus()->GetControlType() == Type_Edit
					|| s_CUI_ID_FRAME_custom.GetSelectedKey() != -1 )
				{
					break;
				}
			}
			if ( s_CUI_ID_FRAME_SelectChannel.IsVisable() )
				break;

			CUIMgr::Instance()->OnKeyUp(wParam, lParam);

			if ( wParam == g_shortcutKey_configure.getValueCharWin32(AN_Configure_ShortcutKey::AN_SCKC_uiHideOrSystem) ||
				wParam == VK_RETURN ||
				wParam == g_shortcutKey_configure.getValueCharWin32(AN_Configure_ShortcutKey::AN_SCKC_jump) )
				return false;

			s_CUI_ID_FRAME_MAIN.SetHotKeyPressIndex(-1);
			s_CUI_ID_FRAME_Exmain.SetPressItemIndex1(-1);

			int nKeyIndex = -1;
			bool bIsMain = false;

			//使快捷和GameSet同步

			for (int i = AN_Configure_ShortcutKey::AN_SCKC_skillExLeft1; i <= AN_Configure_ShortcutKey::AN_SCKC_skillExLeft24; ++i)
			{
				if (g_shortcutKey_configure.hasKey(wParam, (AN_Configure_ShortcutKey::ShortCutKey_Configure)i))
				{
					nKeyIndex = i - AN_Configure_ShortcutKey::AN_SCKC_skillExLeft1;
					break;
				}
			}

			if (nKeyIndex == -1 && 
				g_shortcutKey_configure.hasKey(wParam, AN_Configure_ShortcutKey::AN_SCKC_changeModeName))
			{
				if( Config::GetShowInfoLvl()+1 >= eMax_NameLvl )
				{
					Config::SetShowPlayerInfo( eAllPlayer_NameLvl );
					s_CUI_ID_FRAME_GameSetup.SetShowNpcName(false);
					s_CUI_ID_FRAME_GameSetup.SetShowPlayerName(true);			
					
				}
				else 
				{
					int infotemp = Config::GetShowInfoLvl()+1;
					Config::SetShowPlayerInfo( infotemp );
					switch(infotemp)
					{
					case eAllPlayer_NameLvl:
						s_CUI_ID_FRAME_GameSetup.SetShowNpcName(false);
						s_CUI_ID_FRAME_GameSetup.SetShowPlayerName(true);
						break;
					case eAllNpcMonster_NameLvl:
						s_CUI_ID_FRAME_GameSetup.SetShowNpcName(true);
						s_CUI_ID_FRAME_GameSetup.SetShowPlayerName(false);
	                    break;
					case eALL_NameLvl:
						s_CUI_ID_FRAME_GameSetup.SetShowNpcName(true);
						s_CUI_ID_FRAME_GameSetup.SetShowPlayerName(true);
						break;
					case eClose_NameLvl:
						s_CUI_ID_FRAME_GameSetup.SetShowNpcName(false);
						s_CUI_ID_FRAME_GameSetup.SetShowPlayerName(false);
						break;
					default:
						s_CUI_ID_FRAME_GameSetup.SetShowNpcName(false);
						s_CUI_ID_FRAME_GameSetup.SetShowPlayerName(true);
						break;
					}
				}
				s_CUI_ID_FRAME_GameSetup.RefreshUI();
				return true;
			}
			else if (nKeyIndex == -1)
			{	
				for (int i = AN_Configure_ShortcutKey::AN_SCKC_skillLeft1; i <= AN_Configure_ShortcutKey::AN_SCKC_skillLeft10; ++i)
				{
					if (g_shortcutKey_configure.hasKey(wParam, (AN_Configure_ShortcutKey::ShortCutKey_Configure)i))
					{
						bIsMain = true;
						nKeyIndex = i - AN_Configure_ShortcutKey::AN_SCKC_skillLeft1;
						if(!s_CUI_ID_FRAME_CarryMain.IsVisable())
						    nKeyIndex = More_exMainUIMax + nKeyIndex + s_CUI_ID_FRAME_MAIN.GetHotKey()*More_ainUIMaxOnly;

						break;
					}
				}
			}

			if (nKeyIndex != -1)
			{
				if(s_CUI_ID_FRAME_CarryMain.IsVisable())
					s_CUI_ID_FRAME_CarryMain.ClickHotkey(nKeyIndex);
				else
				    s_CUI_ID_FRAME_MAIN.ClickHotkey(nKeyIndex);
				GSound.PlaySound(UiManager::m_strIconDragSound.c_str(),NULL,false);
				return true;
			}
			else
			{
				for (int i = AN_Configure_ShortcutKey::AN_SCKC_PetSkill1; i <= AN_Configure_ShortcutKey::AN_SCKC_PetSkill10; ++i)
				{
					if (g_shortcutKey_configure.hasKey(wParam, (AN_Configure_ShortcutKey::ShortCutKey_Configure)i))
					{
						nKeyIndex = i - AN_Configure_ShortcutKey::AN_SCKC_PetSkill1;
						return true;
					}
				}
			}
		}
		break;
	case WM_KEYDOWN:
		{
            if( theUiManager.GetFocus() )
            {   //输入框获得焦点的话。
                if(theUiManager.GetFocus()->GetControlType() == Type_Edit)
                {
                    // 判断是否按下LCtrl+Enter
                    bool bSendMessage = false;
                    if( wParam == VK_RETURN && (GetKeyboardInput(DIK_LCONTROL) || GetKeyboardInput(DIK_RCONTROL)) )
                        bSendMessage = true;

                    if (bSendMessage || g_shortcutKey_configure.hasKey(wParam, AN_Configure_ShortcutKey::AN_SCKC_uiBeginChat))
                    {
						if (theUiManager.GetFocus() == CommonChatFrame::GetActiveEditInput())
                        {
                            bool old = CommonChatFrame::GetActiveChatFrame()->_bActiveInput;
                            CommonChatFrame::GetActiveChatFrame()->_bActiveInput = true;
                            CommonChatFrame::GetActiveChatFrame()->ID_EDIT_INPUTOnEditEnter(
                                CommonChatFrame::GetActiveEditInput(),
                                CommonChatFrame::GetActiveEditInput()->GetText());
                            CommonChatFrame::GetActiveChatFrame()->_bActiveInput = old;
                       }
                    }
                    break;
                }
			}

			if (CUIMgr::Instance()->OnKeyDown(wParam, lParam))
				return true;

			int nKeyIndex = -1;
			for (int i = AN_Configure_ShortcutKey::AN_SCKC_skillExLeft1; i <= AN_Configure_ShortcutKey::AN_SCKC_skillExLeft24; ++i)
			{
				if (g_shortcutKey_configure.hasKey(wParam, (AN_Configure_ShortcutKey::ShortCutKey_Configure)i))
				{
					nKeyIndex = i - AN_Configure_ShortcutKey::AN_SCKC_skillExLeft1;
					s_CUI_ID_FRAME_Exmain.SetPressItemIndex1(nKeyIndex);
					return true;
				}
			}

			for (int i = AN_Configure_ShortcutKey::AN_SCKC_skillLeft1; i <= AN_Configure_ShortcutKey::AN_SCKC_skillLeft10; ++i)
			{
				if (g_shortcutKey_configure.hasKey(wParam, (AN_Configure_ShortcutKey::ShortCutKey_Configure)i))
				{
					nKeyIndex = i - AN_Configure_ShortcutKey::AN_SCKC_skillLeft1;
					s_CUI_ID_FRAME_MAIN.SetHotKeyPressIndex(nKeyIndex);
					return true;
				}
			}

			for (int i = AN_Configure_ShortcutKey::AN_SCKC_PetSkill1; i <= AN_Configure_ShortcutKey::AN_SCKC_PetSkill10; ++i)
			{
				if (g_shortcutKey_configure.hasKey(wParam, (AN_Configure_ShortcutKey::ShortCutKey_Configure)i))
				{
					nKeyIndex = i - AN_Configure_ShortcutKey::AN_SCKC_PetSkill1;
					s_CUI_ID_FRAME_SuAnimalMain.SetHotkeyPressIndex(nKeyIndex);
					return true;
				}
			}
		}
		break;
	}
	return false;
	unguard;
}

void CUI_ID_FRAME_MAIN::useSkill( int index, bool bMouse, bool bIconEnable )
{
	guardfunc;

	SMouseItem *pHotkey = NULL;
	pHotkey = &thePlayerRole.m_pHotKeyBag[index];

	if ( !pHotkey || pHotkey->ItemData.itembaseinfo.ustItemID == InvalidLogicNumber   )
		return;

	ItemDefine::SItemCommon *pItemCommon = GettheItemDetail().GetItemByID(pHotkey->ItemData.itembaseinfo.ustItemID);
	if (!pItemCommon)
	{
		return;
	}
	
	switch( pHotkey->ShortCut.BagType )
	{
	case BagTypeSkill:
		{
			UINT nSkillIndex = pHotkey->ShortCut.BagIndex;
			SCharSkill *pSkill = NULL;
			pSkill = thePlayerRole.m_SkillBag.GetSkillByIndex( nSkillIndex );
			if ( !pSkill )
			{
				return;
			}

            // 是否为生产技能       modified by zhuomeng.hu		[11/9/2010]
            if( IsRecipeSkill( pSkill->ustSkillID ) )
            {
                if( !bIconEnable )
                {
                    CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed,
                        theXmlString.GetString( eText_SkillFailed_UnableOperateInCurrentState ) );
                    return;
                }

                s_CUI_ID_FRAME_SkillProduce.ShowRecipeById( pSkill->ustSkillID );
				if (pSkill->ustSkillID == ItemDefine::eCSI_CatchPet)//捕捉技能
				{
					int nMaxCount = thePetSettingConfig.GetPlayerPetLimit(thePlayerRole.GetLevel());
					if (thePlayerRole.GetPetCount() >= nMaxCount)
					{
						CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_PetInfo,theXmlString.GetString(eText_PetEnough) );
						return ;
					}
					GameObjectId m_nCharID = theHeroGame.GetPlayerMgr()->GetLockPlayerID();
					CPlayer *pPlayer = theHeroGame.GetPlayerMgr()->FindByID( m_nCharID );
					if ( pPlayer == NULL ||  !pPlayer->IsMonster() )		
					{
						return;
					} 
					ItemDefine::SMonster* m_pMonsterConfig  =GettheItemDetail().GetMonsterById( pPlayer->GetMonsterID() );
					if (m_pMonsterConfig  == NULL || m_pMonsterConfig->nCatchPetID ==0)
					{//不能捕捉
						CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_PetInfo,theXmlString.GetString(eText_PetCannotCatch) );
						return;
					}

					ItemDefine::SPetMonster* m_pPetMonsterConfig =  GettheItemDetail().GetPetById( m_pMonsterConfig->nCatchPetID );
					if (m_pPetMonsterConfig != NULL &&  pSkill->stSkillLevel < m_pPetMonsterConfig->catchLevel)
					{//捕捉等级不够
						char temp[64];
						MeSprintf_s(temp,sizeof(temp),theXmlString.GetString(eText_MonsterCatchLevelNotEnough),m_pPetMonsterConfig->catchLevel,pSkill->stSkillLevel);
						CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_PetInfo,temp);
						return;
					}
 					if (m_pPetMonsterConfig == NULL ||( m_pPetMonsterConfig != NULL && s_CUI_ID_FRAME_SuAnimalCardList.GetSIdentifyData(m_pPetMonsterConfig->petType) == NULL))
 					{
 						CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_PetInfo,theXmlString.GetString(eText_HaveNonePetCard));
 						return;
 					}
 				//	MsgReqSkillAttack msg;
					//msg.bCharTarget = true;
					//msg.isAction = false;
					//msg.chSkillCount = 1;
					//msg.stSkill = pSkill->ustSkillID;
					//msg.stSkillLevel = pSkill->stSkillLevel;
					//msg.stWho = m_nCharID;
					//GettheNetworkInput().SendMsg(&msg);
				}
                //return;
            }
            else if( IsCollectSkill( pSkill->ustSkillID ) )
            {
                // 如果策划有使用快捷栏采集的需求，则此处无需返回
                return;
            }
			theHeroGame.GetPlayerMgr()->SetCurUseSkill( pSkill->ustSkillID,
				pSkill->stSkillLevel );

			thePlayerRole.UpdateUI();
			

			//add by zmy	判断普通攻击就刷新cd
		
		
			if ( IsNormalAttack(pSkill->ustSkillID) && pSkill->bAvailable == true )
			{

				//lyh++ 武器损坏不能使用 攻击
				SCharItem* pAttriEquips = thePlayerRole.m_charinfo.visual.GetVisualArray();
				if (pAttriEquips)
				{
					if(	pAttriEquips[EEquipPartType::EEquipPartType_Weapon].itembaseinfo.ustItemID 
						!= InvalidLogicNumber &&
						pAttriEquips[EEquipPartType::EEquipPartType_Weapon].equipdata.usHP == 0 )
					{
							CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, theXmlString.GetString( eText_WeopenHpWhithZero ));
							return ;
					}
				}



				CPlayer* pPlayerMe = theHeroGame.GetPlayerMgr()->GetMe();
				if (pPlayerMe&&pPlayerMe->IsMounting() 
					&& pPlayerMe->GetAutoDismount()&&!pPlayerMe->IsGoudaOperaMode())
				{
					//pPlayerMe->DisMount();
					//theHeroGame.GetPlayerMgr()->DisDrome();
				}
               
			CPlayer* pTarget = theHeroGame.GetPlayerMgr()->FindByID(theHeroGame.GetPlayerMgr()->GetLockPlayerID())	;
			if (pTarget && pTarget->IsPlayer() && pTarget != pPlayerMe) //对玩家释放普通攻击的时候 安全区的判断
			{
			
				//CWorldTile* pTile = CURRENTTILE;  //lyh++  地图是否能pk 的判断
				if (CheckMapCanPk(theHeroGame.GetPlayerMgr()->GetMe(),pTarget) || thePlayerRole.GetDuelTarget() == pTarget->GetID()) //切磋也是可以进行普通攻击的
				{
					//thePlayerRole.m_SkillBag.StartSkillCoolDown( pSkill->ustSkillID,
					//	pSkill->stSkillLevel,
					//	pSkill->nColdTime );
					//s_CUI_ID_FRAME_MAIN.RefeashHotKey();
					MsgAttackLockTarget msg;
					msg.cAttack = MsgAttackLockTarget::AT_Attack;
					GettheNetworkInput().SendMsg(&msg);		
				}else
				{

				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, theXmlString.GetString( eText_SkillFailed_NotCorrectTarget ) );
				}
			}else  
			{

				 if( theHeroGame.GetPlayerMgr()->GetMe()
					 &&theHeroGame.GetPlayerMgr()->GetMe()->m_cFightStatus.IsCanBePhyAttack() 
					 && !theHeroGame.GetPlayerMgr()->GetMe()->IsYabiaoState())
				 {
					 //thePlayerRole.m_SkillBag.StartSkillCoolDown( pSkill->ustSkillID,//这里不cd 让服务器发过来动作消息的时候在cd 普通攻击cd
					 //	pSkill->stSkillLevel,
					 //	pSkill->nColdTime );
					 //s_CUI_ID_FRAME_MAIN.RefeashHotKey();
					 MsgAttackLockTarget msg;
					 msg.cAttack = MsgAttackLockTarget::AT_Attack;
					 GettheNetworkInput().SendMsg(&msg);		
				 }

			}
					
			}
			else
			{
				theHeroGame.GetPlayerMgr()->OnSkill( bMouse );
			}
		}
		break;
	case BagTypeMountSkill:
		{
			UINT nSkillIndex = pHotkey->ShortCut.BagIndex;
			SCharSkill *pSkill = NULL;
			pSkill = thePlayerRole.m_MountSkillBag.GetSkillByIndex( nSkillIndex );
			if ( !pSkill )
			{
				return;
			}
			ItemDefine::SItemSkill* pMountSkill = GettheItemDetail().GetSkillByID( pSkill->ustSkillID, pSkill->stSkillLevel );
			// 职业限制     
			int nProfession = thePlayerRole.GetProfession();
			if( !pMountSkill->arrayProfessionReq[nProfession] )
			{
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, theXmlString.GetString( eText_SkillUse_ProfessionLimit ) );
				return ;
			}
			theHeroGame.GetPlayerMgr()->SetCurUseSkill( pSkill->ustSkillID,
				pSkill->stSkillLevel );

			thePlayerRole.UpdateUI();
			theHeroGame.GetPlayerMgr()->OnSkill( bMouse );
		}
		break;
	case BagTypePetSkill:
		{
			UINT nSkillIndex = pHotkey->ShortCut.BagIndex;
			SCharSkill *pSkill = NULL;
			pSkill = thePlayerRole.m_PetSkillBag.GetSkillByIndex( nSkillIndex );
			if ( !pSkill )
			{
				return;
			}
			ItemDefine::SItemSkill* pMountSkill = GettheItemDetail().GetSkillByID( pSkill->ustSkillID, pSkill->stSkillLevel );
			// 职业限制     
			int nProfession = thePlayerRole.GetProfession();
			if( !pMountSkill->arrayProfessionReq[nProfession] )
			{
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, theXmlString.GetString( eText_SkillUse_ProfessionLimit ) );
				return ;
			}
			theHeroGame.GetPlayerMgr()->SetCurUseSkill( pSkill->ustSkillID, pSkill->stSkillLevel );

			thePlayerRole.UpdateUI();
			theHeroGame.GetPlayerMgr()->OnSkill( bMouse );
		}
		break;
	case BagTypePack:
		{
			s_CUI_ID_FRAME_PACK.UseItem( pHotkey->ItemData.itembaseinfo.ustItemID,
										pHotkey->ShortCut.BagIndex );
		}
		break;
	case BagTypeActionUI:
		{			
 			s_CUI_ID_FRAME_ActionUI.SetCurFunction( pHotkey->ItemData.itembaseinfo.ustItemID );
 			s_CUI_ID_FRAME_ActionUI.UseFunction();
		}
		break;
	case BagTypeExpressionAction:
		{
			ExpAction::ESex sex = (thePlayerRole.GetSex() == Sex_Male) ? ExpAction::Male : ExpAction::Female;
			CExpressionAction::Instance().CheckAndDoExpressionActionByItemId(pHotkey->ItemData.itembaseinfo.ustItemID, sex);
		}
		break;
	/**********************************************************************
	author:liaojie
	date:2012/08/13
	Desc:主将技能背包
	**********************************************************************/
	case BagTypeHeroSkill:
		{
			UINT nSkillIndex = pHotkey->ShortCut.BagIndex;
			SCharSkill *pSkill = NULL;
			pSkill = thePlayerRole.m_HeroSkillBag.GetSkillByIndex( nSkillIndex );
			if ( !pSkill )
			{
				return;
			}

			ItemDefine::SItemSkill* pHeroSkill = GettheItemDetail().GetSkillByID( pSkill->ustSkillID, pSkill->stSkillLevel );
			// 职业限制     
			int nProfession = thePlayerRole.GetProfession();
			if( !pHeroSkill->arrayProfessionReq[nProfession] )
			{
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Operate_Failed, theXmlString.GetString( eText_SkillUse_ProfessionLimit ) );
				return ;
			}
			theHeroGame.GetPlayerMgr()->SetCurUseSkill( pSkill->ustSkillID,
				pSkill->stSkillLevel );

			thePlayerRole.UpdateUI();
			theHeroGame.GetPlayerMgr()->OnSkill( bMouse );

		}
		break;
	default:
		break;
	}
	unguard;
}
CUI_ID_FRAME_MAIN::CUI_ID_FRAME_MAIN()
// :CUIBase(eUI_OBJECT_Main)
{
	guardfunc;
	// SGuildMember
	m_pID_FRAME_MAIN = NULL;
	m_pID_BUTTON_Function = NULL;
	m_pID_PROGRESS_Exp = NULL;
	m_pID_LISTIMG_Hotkey = NULL;
	m_pID_BUTTON_OUT = NULL;
	m_pID_BUTTON_IN = NULL;
	m_pID_PICTURE_BG = NULL;
	m_pID_BUTTON_Map = NULL;
	m_pID_TEXT_Num = NULL;
	m_pID_CHECKBOX_Angle	= NULL;
	m_pID_CHECKBOX_IsKeyboard	= NULL;
	m_pID_CHECKBOX_showhotkey = NULL;
	m_pID_BUTTON_turnHotkeyUp = NULL;
	m_pID_BUTTON_turnHotkeyDown = NULL;
	m_pID_TEXT_EXP = NULL;
	m_pID_BUTTON_Enter = NULL;
	m_pID_BUTTON_LevelUp = NULL;
	m_pID_TEXT_LevelUp = NULL;
	nIndexHotKey = 0;
    m_pID_CHECKBOX_HideChatList = NULL;
	bFullScreen = false;

	unguard;

}
// Frame
bool CUI_ID_FRAME_MAIN::OnFrameRun()
{
	UpdateIconInfo();
	return true;
}
bool CUI_ID_FRAME_MAIN::OnFrameRender()
{
	return true;
}
void CUI_ID_FRAME_MAIN::RefeashHotKey()
{
	guardfunc;

    if(!m_pID_FRAME_MAIN)
        return;

	if( !m_pID_LISTIMG_Hotkey )
		return;

	s_CUI_ID_FRAME_Pet.RefreshMountSkill();

	m_pID_LISTIMG_Hotkey->Clear();
	SMouseItem *pHotkey = NULL;
	int nOffSet = More_exMainUIMax;
	int key = 0;
	for(int i = nOffSet+nIndexHotKey*More_ainUIMaxOnly; i<nOffSet+(nIndexHotKey+1)*More_ainUIMaxOnly;  i++, key++)
	{
		ControlIconDrag::S_ListImg stItem;
        pHotkey = &thePlayerRole.m_pHotKeyBag[i];
		if ( pHotkey->ShortCut.BagIndex >= 0 && pHotkey->ShortCut.BagIndex < ITEM_BAGMAX )
		{
			pHotkey->ItemData.itembaseinfo.value2 = thePlayerRole.m_bag.m_pPackItem[pHotkey->ShortCut.BagIndex].itembaseinfo.value2;
		
            if (pHotkey->ShortCut.BagType == BagTypePack &&
				thePlayerRole.m_bag.m_pPackItem[pHotkey->ShortCut.BagIndex].itembaseinfo.ustItemID ==
                InvalidLogicNumber)
            {
                pHotkey->ShortCut.BagIndex = ErrorUnsignedShortID;
                for (int i  = 0; i < thePlayerRole.m_bag.GetNowBagSize(); ++i)
                {
                    if (thePlayerRole.m_bag.m_pPackItem[i].itembaseinfo.ustItemID ==
                        pHotkey->ItemData.itembaseinfo.ustItemID)
                    {
                        pHotkey->ShortCut.BagIndex = i;
                        break;
                    }
                }

                if (pHotkey->ShortCut.BagIndex == ErrorUnsignedShortID)
                    pHotkey->ItemData.itembaseinfo.ustItemID = InvalidLogicNumber;
            }
        }
		//*******************************
		bool bNullItem = false;
		if ( pHotkey->ItemData.itembaseinfo.ustItemID != InvalidLogicNumber )
		{
			switch( pHotkey->ShortCut.BagType )
			{
			case BagTypeSkill:
				{
					int nSkillIndex = pHotkey->ShortCut.BagIndex;
					SCharSkill *pSkill;
					pSkill = thePlayerRole.m_SkillBag.GetSkillByIndex( nSkillIndex );
					if ( !pSkill ||
						pSkill->ustSkillID == InvalidLogicNumber ||
						pHotkey->ItemData.itembaseinfo.ustItemID != pSkill->ustSkillID)
					{
						pHotkey->ItemData.itembaseinfo.ustItemID = InvalidLogicNumber;
						pHotkey->ShortCut.BagIndex = ErrorUnsignedShortID;
						bNullItem = true;
						break;
					}

					SUIIconSet::SIconSet* iconSet = g_UISkillMgr.GetSkillIconSet(pSkill->ustSkillID);
					if (iconSet)
						stItem.m_pkIconInfo->SetIconImageInfo(iconSet->image, iconSet->iconSize, iconSet->row, iconSet->column);

					//stItem.SetData( pSkill->ustSkillID, pSkill->stSkillLevel, pSkill->bAvailable? eIcon_Enable: eIcon_Disable, true, eTipFlag_SkillNoNextLevel );
					// 根据策划要求, 技能图标永远是亮的状态
					stItem.SetData( pSkill->ustSkillID, pSkill->stSkillLevel, eIcon_Enable, true, eTipFlag_SkillNoNextLevel );

					AN_Configure_ShortcutKey::ShortCutKey_Configure eKey =
						(AN_Configure_ShortcutKey::ShortCutKey_Configure)(AN_Configure_ShortcutKey::AN_SCKC_skillLeft1 + key);
					stItem.m_pkIconInfo->m_strHotKey = g_shortcutKey_configure.getValueString(eKey);

					SkillBag::SColdTime *pTime = NULL;
					pTime = thePlayerRole.m_SkillBag.GetColdTimeByIndex( nSkillIndex );
					if ( pTime )
					{
						stItem.SetTime( pTime->dwColdStartTime, pTime->dwColdTime );
					}

					m_pID_LISTIMG_Hotkey->SetItem( &stItem, i-nOffSet-nIndexHotKey*More_ainUIMaxOnly );
					GetBillBoard()->SetTipCounts(FRIST_SKILL);
				}
				break;
			case BagTypeMountSkill:
				{
					int nSkillIndex = pHotkey->ShortCut.BagIndex;
					SCharSkill *pSkill;
					pSkill = thePlayerRole.m_MountSkillBag.GetSkillByIndex( nSkillIndex );
					if ( !pSkill ||
						pSkill->ustSkillID == InvalidLogicNumber ||
						pHotkey->ItemData.itembaseinfo.ustItemID != pSkill->ustSkillID)
					{
						pHotkey->ItemData.itembaseinfo.ustItemID = InvalidLogicNumber;
						pHotkey->ShortCut.BagIndex = ErrorUnsignedShortID;
						bNullItem = true;
						break;
					}

					SUIIconSet::SIconSet* iconSet = g_UISkillMgr.GetSkillIconSet(pSkill->ustSkillID);
					if (iconSet)
						stItem.m_pkIconInfo->SetIconImageInfo(iconSet->image, iconSet->iconSize, iconSet->row, iconSet->column);

					stItem.SetData( pSkill->ustSkillID, pSkill->stSkillLevel, pSkill->bAvailable? eIcon_Enable: eIcon_Disable, true, eTipFlag_SkillNoNextLevel );

					AN_Configure_ShortcutKey::ShortCutKey_Configure eKey =
						(AN_Configure_ShortcutKey::ShortCutKey_Configure)(AN_Configure_ShortcutKey::AN_SCKC_skillLeft1 + key);
					stItem.m_pkIconInfo->m_strHotKey = g_shortcutKey_configure.getValueString(eKey);

					SkillBag::SColdTime *pTime = NULL;
					pTime = thePlayerRole.m_MountSkillBag.GetColdTimeById( pSkill->ustSkillID );
					if ( pTime )
					{
						stItem.SetTime( pTime->dwColdStartTime, pTime->dwColdTime );
					}

					m_pID_LISTIMG_Hotkey->SetItem( &stItem, i-nOffSet-nIndexHotKey*More_ainUIMaxOnly );
					GetBillBoard()->SetTipCounts(FRIST_SKILL);
				}
				break;
			case BagTypePetSkill:
				{
					int nSkillIndex = pHotkey->ShortCut.BagIndex;
					SCharSkill *pSkill;
					pSkill = thePlayerRole.m_PetSkillBag.GetSkillByIndex( nSkillIndex );
					if ( !pSkill ||
						pSkill->ustSkillID == InvalidLogicNumber ||
						pHotkey->ItemData.itembaseinfo.ustItemID != pSkill->ustSkillID)
					{
						pHotkey->ItemData.itembaseinfo.ustItemID = InvalidLogicNumber;
						pHotkey->ShortCut.BagIndex = ErrorUnsignedShortID;
						bNullItem = true;
						break;
					}

					SUIIconSet::SIconSet* iconSet = g_UISkillMgr.GetSkillIconSet(pSkill->ustSkillID);
					if (iconSet)
						stItem.m_pkIconInfo->SetIconImageInfo(iconSet->image, iconSet->iconSize, iconSet->row, iconSet->column);

					stItem.SetData( pSkill->ustSkillID, pSkill->stSkillLevel, pSkill->bAvailable? eIcon_Enable: eIcon_Disable, true, eTipFlag_SkillNoNextLevel );

					AN_Configure_ShortcutKey::ShortCutKey_Configure eKey =
						(AN_Configure_ShortcutKey::ShortCutKey_Configure)(AN_Configure_ShortcutKey::AN_SCKC_skillLeft1 + key);
					stItem.m_pkIconInfo->m_strHotKey = g_shortcutKey_configure.getValueString(eKey);

					SkillBag::SColdTime *pTime = NULL;
					pTime = thePlayerRole.m_PetSkillBag.GetColdTimeById( pSkill->ustSkillID );
					if ( pTime )
					{
						stItem.SetTime( pTime->dwColdStartTime, pTime->dwColdTime );
					}

					m_pID_LISTIMG_Hotkey->SetItem( &stItem, i-nOffSet-nIndexHotKey*More_ainUIMaxOnly );
					GetBillBoard()->SetTipCounts(FRIST_SKILL);
				}
				break;
			case BagTypePack:
				{
					int nItemID = pHotkey->ItemData.itembaseinfo.ustItemID;
					ItemDefine::SItemCommon *pItem = GettheItemDetail().GetItemByID( nItemID );
					if ( !pItem )
					{
						bNullItem = true;
						break;
					}
					if( pItem->ucItemType == ItemDefine::ITEMTYPE_WEAPON || pItem->ucItemType == ItemDefine::ITEMTYPE_ARMOUR )
					{
						bNullItem = true;
						break;
                    }

                    bool autoUseItem = false;
                    if ( pItem->ucItemType == ItemDefine::ITEMTYPE_RESTORE )
                    {
                        ItemDefine::SItemRestore* itemRestore = static_cast<ItemDefine::SItemRestore*>(pItem);
                        autoUseItem = itemRestore->bHPAuto || itemRestore->bMPAuto || itemRestore->bAutoRelive;
                    }

                    if ( pItem->IsExclusive() && !autoUseItem )
					{
						int nIndex = thePlayerRole.m_bag.GetItemIndex( &pHotkey->ItemData );
						if ( nIndex != -1 )
						{
							pHotkey->ShortCut.BagIndex = nIndex;
							stItem.SetData( &pHotkey->ItemData );

							AN_Configure_ShortcutKey::ShortCutKey_Configure eKey =
								(AN_Configure_ShortcutKey::ShortCutKey_Configure)(AN_Configure_ShortcutKey::AN_SCKC_skillLeft1 + key);
							stItem.m_pkIconInfo->m_strHotKey = g_shortcutKey_configure.getValueString(eKey);

							//
							RestoreColdDown* pRestoreCoolDown = NULL;
							pRestoreCoolDown = thePlayerRole.GetRestoreCoolDown();
							DWORD dwStartTiem,dwPeriod;
							if( pRestoreCoolDown->GetTime( pHotkey->ItemData.itembaseinfo.ustItemID,
								&dwStartTiem, &dwPeriod ) == true )
							{
								stItem.SetTime( dwStartTiem,dwPeriod );
							}
							//

							m_pID_LISTIMG_Hotkey->SetItem( &stItem, i-nOffSet-nIndexHotKey*More_ainUIMaxOnly );
						}
					}
					else
					{
						int nCount = thePlayerRole.m_bag.GetItemCount( pHotkey->ItemData.itembaseinfo.ustItemID );
						int nIndex = thePlayerRole.m_bag.GetItemIndexById( pHotkey->ItemData.itembaseinfo.ustItemID );
						if ( nCount > 0 )
						{
							pHotkey->ShortCut.BagIndex = nIndex;
							pHotkey->ItemData.itembaseinfo.ustItemCount = nCount;
							pHotkey->ItemData.itembaseinfo.useType = thePlayerRole.m_bag.m_pPackItem[pHotkey->ShortCut.BagIndex].itembaseinfo.useType;
							stItem.SetData( &pHotkey->ItemData );
							//
							RestoreColdDown* pRestoreCoolDown = NULL;
							pRestoreCoolDown = thePlayerRole.GetRestoreCoolDown();
							DWORD dwStartTiem,dwPeriod;
							if( pRestoreCoolDown->GetTime( pHotkey->ItemData.itembaseinfo.ustItemID,
								&dwStartTiem, &dwPeriod ) == true )
							{
								stItem.SetTime( dwStartTiem,dwPeriod );
							}
							//

							AN_Configure_ShortcutKey::ShortCutKey_Configure eKey =
								(AN_Configure_ShortcutKey::ShortCutKey_Configure)(AN_Configure_ShortcutKey::AN_SCKC_skillLeft1 + key);
							stItem.m_pkIconInfo->m_strHotKey = g_shortcutKey_configure.getValueString(eKey);

							m_pID_LISTIMG_Hotkey->SetItem( &stItem, i-nOffSet-nIndexHotKey*More_ainUIMaxOnly );
						}
					}
				}
				break;
			case BagTypeFunction:
				{
					stItem.SetData( &pHotkey->ItemData );

					AN_Configure_ShortcutKey::ShortCutKey_Configure eKey =
						(AN_Configure_ShortcutKey::ShortCutKey_Configure)(AN_Configure_ShortcutKey::AN_SCKC_skillLeft1 + key);
					stItem.m_pkIconInfo->m_strHotKey = g_shortcutKey_configure.getValueString(eKey);

					m_pID_LISTIMG_Hotkey->SetItem( &stItem, i-nOffSet-nIndexHotKey*More_ainUIMaxOnly );
				}
				break;
			case BagTypeActionUI:
				{
					SUIIconSet::SIconSet* iconSet = g_UISkillMgr.GetSkillIconSet(pHotkey->ItemData.itembaseinfo.ustItemID);
					if (iconSet)
						stItem.m_pkIconInfo->SetIconImageInfo(iconSet->image, iconSet->iconSize, iconSet->row, iconSet->column);

					eIconDrawState eEnable = eIcon_Enable;
                    BOOL bInWater = FALSE;
                    if( theHeroGame.GetPlayerMgr()->GetMe() && theHeroGame.GetPlayerMgr()->GetMe()->IsInWater() )
                        bInWater = TRUE;
					//战斗状态骑马的技能显示高亮
					if ((CUI_ID_FRAME_BaseProperty::TYPE_SITDWON_ACTION == pHotkey->ItemData.itembaseinfo.ustItemID 
						/*|| CUI_ID_FRAME_BaseProperty::TYPE_MOUNT == pHotkey->ItemData.itembaseinfo.ustItemID*/)
                        &&
						(thePlayerRole.IsFighting() || bInWater) )
						eEnable = eIcon_Disable;

					if ( CUI_ID_FRAME_BaseProperty::TYPE_MOUNT == pHotkey->ItemData.itembaseinfo.ustItemID &&
						(!s_CUI_ID_FRAME_Pet.IsActivedPet() || bInWater) )
						eEnable = eIcon_Disable;

					if (pHotkey->ItemData.itembaseinfo.ustItemID >= CUI_ID_FRAME_BaseProperty::TYPE_PETATTACK &&
						pHotkey->ItemData.itembaseinfo.ustItemID <= CUI_ID_FRAME_BaseProperty::TYPE_PETAICOMMAND &&
						theHeroGame.GetPlayerMgr()->GetMe() &&
						!theHeroGame.GetPlayerMgr()->GetMe()->HavePet())
					{
						eEnable = eIcon_Disable;
					}

					if (pHotkey->ItemData.itembaseinfo.ustItemID > 1000)
					{
						SCharSkill *pSkill = 0;
						pSkill = thePlayerRole.m_SkillBag.GetSkillByID( pHotkey->ItemData.itembaseinfo.ustItemID );
						if ( !pSkill ||
							pSkill->ustSkillID == InvalidLogicNumber ||
							pHotkey->ItemData.itembaseinfo.ustItemID != pSkill->ustSkillID)
						{
							pHotkey->ItemData.itembaseinfo.ustItemID = InvalidLogicNumber;
							pHotkey->ShortCut.BagIndex = ErrorUnsignedShortID;
							bNullItem = true;
							break;
						}

						stItem.SetData( pSkill->ustSkillID, pSkill->stSkillLevel, pSkill->bAvailable? eIcon_Enable: eIcon_Disable, true, eTipFlag_SkillNoNextLevel );
						stItem.m_pkIconInfo->SetColorFrameType(eColorFrame_None);

						SkillBag::SColdTime *pTime = NULL;
						pTime = thePlayerRole.m_SkillBag.GetColdTimeById( pSkill->ustSkillID );
						if ( pTime )
						{
							stItem.SetTime( pTime->dwColdStartTime, pTime->dwColdTime );
						}
					}
					else
					{
						stItem.SetData( &pHotkey->ItemData, eEnable );
						stItem.m_pkIconInfo->SetColorFrameType(eColorFrame_None);
					}

					if (pHotkey->ItemData.itembaseinfo.ustItemID == CUI_ID_FRAME_BaseProperty::TYPE_GOBACK)
					{
						SkillBag::SColdTime *pTime = NULL;
						pTime = thePlayerRole.m_SkillBag.GetColdTimeById( CUI_ID_FRAME_BaseProperty::TYPE_GOBACK_SKILL_ID );
						if ( pTime )
							stItem.SetTime( pTime->dwColdStartTime, pTime->dwColdTime );
					}
					else if (pHotkey->ItemData.itembaseinfo.ustItemID == CUI_ID_FRAME_BaseProperty::TYPE_GOBACK2)
					{
						SkillBag::SColdTime *pTime = NULL;
						pTime = thePlayerRole.m_SkillBag.GetColdTimeById( CUI_ID_FRAME_BaseProperty::TYPE_GOBACK_SKILL_ID2 );
						if ( pTime )
							stItem.SetTime( pTime->dwColdStartTime, pTime->dwColdTime );
						continue; //lyh-- 防卡回城
					}
					else if (pHotkey->ItemData.itembaseinfo.ustItemID == CUI_ID_FRAME_BaseProperty::TYPE_MOUNT)
					{
						SkillBag::SColdTime *pTime = NULL;
						pTime = thePlayerRole.m_SkillBag.GetColdTimeById( CUI_ID_FRAME_BaseProperty::TYPE_MOUNT_SKILL_ID );
						if ( pTime )
							stItem.SetTime( pTime->dwColdStartTime, pTime->dwColdTime );

						if (theHeroGame.GetPlayerMgr()->GetMe() && theHeroGame.GetPlayerMgr()->GetMe()->IsMounting())
							stItem.m_pkIconInfo->SetColorFrameType(eColorFrame_Active);
					}

					if (s_CUI_ID_FRAME_BaseProperty.GetPetAIType() == pHotkey->ItemData.itembaseinfo.ustItemID)
					{
						stItem.m_pkIconInfo->SetColorFrameType(eColorFrame_Active);
					}

					AN_Configure_ShortcutKey::ShortCutKey_Configure eKey =
						(AN_Configure_ShortcutKey::ShortCutKey_Configure)(AN_Configure_ShortcutKey::AN_SCKC_skillLeft1 + key);
					stItem.m_pkIconInfo->m_strHotKey = g_shortcutKey_configure.getValueString(eKey);

					m_pID_LISTIMG_Hotkey->SetItem( &stItem, i-nOffSet-nIndexHotKey*More_ainUIMaxOnly );

					break;
				}
			case BagTypeExpressionAction:
				{
					stItem.SetData( &pHotkey->ItemData );

					AN_Configure_ShortcutKey::ShortCutKey_Configure eKey =
						(AN_Configure_ShortcutKey::ShortCutKey_Configure)(AN_Configure_ShortcutKey::AN_SCKC_skillLeft1 + key);
					stItem.m_pkIconInfo->m_strHotKey = g_shortcutKey_configure.getValueString(eKey);

					m_pID_LISTIMG_Hotkey->SetItem( &stItem, i-nOffSet-nIndexHotKey*More_ainUIMaxOnly );
				}
				break;
			/**********************************************************************
			author:liaojie
			date:2012/08/13
			Desc:主将技能背包
			**********************************************************************/
			case BagTypeHeroSkill:
				{
					int nSkillIndex = pHotkey->ShortCut.BagIndex;
					SCharSkill *pSkill;
					pSkill = thePlayerRole.m_HeroSkillBag.GetSkillByIndex( nSkillIndex );
					if ( !pSkill ||
						pSkill->ustSkillID == InvalidLogicNumber ||
						pHotkey->ItemData.itembaseinfo.ustItemID != pSkill->ustSkillID)
					{
						pHotkey->ItemData.itembaseinfo.ustItemID = InvalidLogicNumber;
						pHotkey->ShortCut.BagIndex = ErrorUnsignedShortID;
						bNullItem = true;
						break;
					}

					SUIIconSet::SIconSet* iconSet = g_UISkillMgr.GetSkillIconSet(pSkill->ustSkillID);
					if (iconSet)
						stItem.m_pkIconInfo->SetIconImageInfo(iconSet->image, iconSet->iconSize, iconSet->row, iconSet->column);

					stItem.SetData( pSkill->ustSkillID, pSkill->stSkillLevel, pSkill->bAvailable? eIcon_Enable: eIcon_Disable, true, eTipFlag_SkillNoNextLevel );

					AN_Configure_ShortcutKey::ShortCutKey_Configure eKey =
						(AN_Configure_ShortcutKey::ShortCutKey_Configure)(AN_Configure_ShortcutKey::AN_SCKC_skillLeft1 + key);
					stItem.m_pkIconInfo->m_strHotKey = g_shortcutKey_configure.getValueString(eKey);

					SkillBag::SColdTime *pTime = NULL;
					pTime = thePlayerRole.m_HeroSkillBag.GetColdTimeByIndex( nSkillIndex );
					if ( pTime )
					{
						stItem.SetTime( pTime->dwColdStartTime, pTime->dwColdTime );
					}

					m_pID_LISTIMG_Hotkey->SetItem( &stItem, i-nOffSet-nIndexHotKey*More_ainUIMaxOnly );
					GetBillBoard()->SetTipCounts(FRIST_SKILL);
				}
				break;
			default:
				bNullItem = true;
				break;
			}
		}
		else
			bNullItem = true;

		if (pHotkey->ItemData.itembaseinfo.ustItemID == ErrorUnsignedShortID)
		{
			bNullItem = true;
		}

		if( bNullItem )
		{
			stItem.Clear();

			AN_Configure_ShortcutKey::ShortCutKey_Configure eKey =
				(AN_Configure_ShortcutKey::ShortCutKey_Configure)(AN_Configure_ShortcutKey::AN_SCKC_skillLeft1 + key);
			stItem.m_pkIconInfo->m_strHotKey = g_shortcutKey_configure.getValueString(eKey);

			m_pID_LISTIMG_Hotkey->SetItem( &stItem, i-nOffSet-nIndexHotKey*More_ainUIMaxOnly );
		}
	}	
	
	if (m_pID_BUTTON_Enter)
	{
		char szContent[256] = {0};
		CTPHJManger::STPHJ* TPHJRank = theTPHJManager.FindTPHJRankByRankID(thePlayerRole.GetTPHJRank());
		if (TPHJRank)
		{
			MeSprintf_s(szContent, sizeof(szContent)/sizeof(char) - 1, "%s",TPHJRank->tip.c_str());
		}
		else
		{
			MeSprintf_s(szContent, sizeof(szContent)/sizeof(char) - 1, "%s",theTPHJManager.GetDefaultTip().c_str());
		}
		m_pID_BUTTON_Enter->setTip(szContent);
		m_pID_BUTTON_Enter->SetShowTip(true);
	}
	
	POINT pos;
	GetCursorPos(&pos);
	SetCursorPos(pos.x, pos.y);
	
	unguard;
}

void CUI_ID_FRAME_MAIN::RefreshHotKeyEnableSetting()
{
	guardfunc;
	m_pID_LISTIMG_Hotkey->Clear();
	SMouseItem *pHotkey = NULL;
	ControlIconDrag::S_ListImg stItem;
	UINT nOffSet = More_exMainUIMax;
	for(int i=nOffSet; i<More_mainUIMax;i++)
	{
		pHotkey = &thePlayerRole.m_pHotKeyBag[i];
		if ( pHotkey->ShortCut.BagIndex < 0 || pHotkey->ShortCut.BagIndex >= ITEM_BAGMAX )
			continue;
        //******************************************************************
		if ( pHotkey->ItemData.itembaseinfo.ustItemID != InvalidLogicNumber )
		{
			switch( pHotkey->ShortCut.BagType )
			{
			case BagTypeSkill:
				{
					int nSkillIndex = pHotkey->ShortCut.BagIndex;
					SCharSkill *pSkill;
					pSkill = thePlayerRole.m_SkillBag.GetSkillByIndex( nSkillIndex );
					if ( !pSkill ||
						pSkill->ustSkillID == InvalidLogicNumber )
					{
						break;
					}

					SUIIconSet::SIconSet* iconSet = g_UISkillMgr.GetSkillIconSet(pSkill->ustSkillID);
					if (iconSet)
						stItem.m_pkIconInfo->SetIconImageInfo(iconSet->image, iconSet->iconSize, iconSet->row, iconSet->column);
					stItem.SetData( pSkill->ustSkillID, pSkill->stSkillLevel, eIcon_Disable, true );

					m_pID_LISTIMG_Hotkey->SetItem( &stItem, i-nOffSet );
					break;
				}
			case BagTypeHeroSkill:
				{
					int nSkillIndex = pHotkey->ShortCut.BagIndex;
					SCharSkill *pSkill;
					pSkill = thePlayerRole.m_HeroSkillBag.GetSkillByIndex( nSkillIndex );
					if ( !pSkill ||
						pSkill->ustSkillID == InvalidLogicNumber )
					{
						break;
					}

					SUIIconSet::SIconSet* iconSet = g_UISkillMgr.GetSkillIconSet(pSkill->ustSkillID);
					if (iconSet)
						stItem.m_pkIconInfo->SetIconImageInfo(iconSet->image, iconSet->iconSize, iconSet->row, iconSet->column);
					stItem.SetData( pSkill->ustSkillID, pSkill->stSkillLevel, eIcon_Disable, true );

					m_pID_LISTIMG_Hotkey->SetItem( &stItem, i-nOffSet );
					break;
				}
			default:
				break;
			}
		}
	}	
	unguard;
}

void CUI_ID_FRAME_MAIN::Refeash()
{
	guardfunc;
    if(!m_pID_FRAME_MAIN)
        return;

	RefreshExp();

	RefeashHotKey();
	s_CUI_ID_FRAME_Exmain.RefeashHotNumber();
	unguard;
}
// Button
bool CUI_ID_FRAME_MAIN::ID_BUTTON_FunctionOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_MAIN )
		return false;
	return true;
}
// Button
bool CUI_ID_FRAME_MAIN::ID_BUTTON_FightStateOnButtonClick( ControlObject* pSender )
{
	guardfunc;
	if( !m_pID_FRAME_MAIN )
		return false;
	CPlayer *pMe = theHeroGame.GetPlayerMgr()->GetMe();
	if( pMe && !pMe->HasFightFlag(eFighting) )
	{
		MsgChangeFightState msg;
		msg.bFight = true;
		GettheNetworkInput().SendMsg( &msg );
	}
	return true;
	unguard;
}
// ListImg / ListEx
bool CUI_ID_FRAME_MAIN::ID_LISTIMG_HotkeyOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
													  ControlIconDrag::S_ListImg* pItemDrag,
													  ControlIconDrag::S_ListImg* pItemSrc )
{
	guardfunc;
	if( !m_pID_FRAME_MAIN )
		return false;
	if (!pItemSrc||!pItemDrag)
	{
		return false;
	}
	int nIndexDrag = m_pID_LISTIMG_Hotkey->GetItemIndex( pItemDrag );
	int nIndexSrc = m_pID_LISTIMG_Hotkey->GetItemIndex( pItemSrc );
    iconDargOn( nIndexDrag, nIndexSrc, pSender, pMe, pItemDrag, pItemSrc);
	return false;
	unguard;
}

bool CUI_ID_FRAME_MAIN::ID_LISTIMG_HotkyeOnIconDisableDragOn( ControlObject* pSender, ControlObject* pMe,
													  ControlIconDrag::S_ListImg* pItemDrag,
													  ControlIconDrag::S_ListImg* pItemSrc )
{
	guardfunc;
	if( !m_pID_FRAME_MAIN )
		return false;

	CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Main_Display, theXmlString.GetString(eText_DragLockWarning) );

	return true;
	unguard;
}

bool CUI_ID_FRAME_MAIN::ID_LISTIMG_HotkyeOnIconDisableDragOut( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	guardfunc;
	if( !m_pID_FRAME_MAIN )
		return false;
	return true;
	unguard;
}

//呼出太平幻境UI
bool CUI_ID_FRAME_MAIN::ID_BUTTON_EnterOnButtonClick(ControlObject* pSender)
{
	if (s_CUI_ID_FRAME_TaiPingHuanJing._IsVisable())
	{
		s_CUI_ID_FRAME_TaiPingHuanJing._SetVisable(false);
	}
	else
	{
		s_CUI_ID_FRAME_TaiPingHuanJing._SetVisable(true);
	}
	return true;
}

bool CUI_ID_FRAME_MAIN::ID_BUTTON_LevelUpOnButtonClick(ControlObject* pSender)
{
	//手动升级
	s_CUI_ID_FRAME_ManualLevelUp._SetVisable(!s_CUI_ID_FRAME_ManualLevelUp._IsVisable());
	return true;
}

bool CUI_ID_FRAME_MAIN::ID_TEXT_LevelUpOnButtonClick( ControlObject* pSender )
{
	s_CUI_ID_FRAME_ManualLevelUp._SetVisable(!s_CUI_ID_FRAME_ManualLevelUp._IsVisable());
	return true;
}

void CUI_ID_FRAME_MAIN::iconDargOn( int nIndexDrag, int nIndexSrc, ControlObject* pSender, ControlObject* pMe,
								   ControlIconDrag::S_ListImg* pItemDrag,
								   ControlIconDrag::S_ListImg* pItemSrc )
{
	guardfunc;

	if ( pItemDrag->IsNull() )
		return;

	UINT nHotkeyIndex = nIndexSrc;
	if ( nHotkeyIndex >= More_ainUIMaxOnly )
		return;

	ItemDefine::SItemCommon *pItem = GettheItemDetail().GetItemByID( pItemDrag->m_pkIconInfo->Id() );
	if ( !pItem )
		return;
	if( pItem->ucItemType == ItemDefine::ITEMTYPE_WEAPON || pItem->ucItemType == ItemDefine::ITEMTYPE_ARMOUR )
	{
		return;
	}

	// 自己
	if ( pSender == pMe )
	{
		UINT nSrcIndex = nIndexDrag;
		SMouseItem stTemp = thePlayerRole.m_pHotKeyBag[nHotkeyIndex+More_exMainUIMax+nIndexHotKey*More_ainUIMaxOnly];											//sbw_add
		thePlayerRole.m_pHotKeyBag[nHotkeyIndex+More_exMainUIMax+nIndexHotKey*More_ainUIMaxOnly] = thePlayerRole.m_pHotKeyBag[nSrcIndex+More_exMainUIMax+nIndexHotKey*More_ainUIMaxOnly];
		thePlayerRole.m_pHotKeyBag[nSrcIndex+More_exMainUIMax+nIndexHotKey*More_ainUIMaxOnly] = stTemp;
	}
	else if( pSender == s_CUI_ID_FRAME_Exmain.GetpIDListImageExmain1() )
	{
		UINT nSrcIndex = s_CUI_ID_FRAME_Exmain.GetItemIndex1( pItemDrag );
		SMouseItem stTemp = thePlayerRole.m_pHotKeyBag[nHotkeyIndex+More_exMainUIMax+nIndexHotKey*More_ainUIMaxOnly];											//sbw_add
		thePlayerRole.m_pHotKeyBag[nHotkeyIndex+More_exMainUIMax+nIndexHotKey*More_ainUIMaxOnly] = thePlayerRole.m_pHotKeyBag[nSrcIndex];
		thePlayerRole.m_pHotKeyBag[nSrcIndex] = stTemp;
	}
    else if(pSender == s_CUI_ID_FRAME_Exmain.GetpIDListImageExmain2())
    {
         int nSrcIndex = s_CUI_ID_FRAME_Exmain.GetItemIndex2(pItemDrag);
         int nOffset   = s_CUI_ID_FRAME_Exmain.GetItemCnt1();
         SMouseItem stTemp = thePlayerRole.m_pHotKeyBag[nSrcIndex + nOffset];

         thePlayerRole.m_pHotKeyBag[nSrcIndex + nOffset] = thePlayerRole.m_pHotKeyBag[nHotkeyIndex+More_exMainUIMax+nIndexHotKey*More_ainUIMaxOnly];
         thePlayerRole.m_pHotKeyBag[nHotkeyIndex+More_exMainUIMax+nIndexHotKey*More_ainUIMaxOnly] = stTemp;
    }
    else if( s_CUI_ID_FRAME_SkillProduce.IsRecipeSkillList( pSender ) ) // 生活技能
    {
        ItemDefine::SItemSkill* pSkill = NULL; 
        pSkill = GettheItemDetail().GetSkillByID( pItemDrag->m_pkIconInfo->Id(), 1);
        if( !pSkill || pSkill->sSkillCategory == ItemDefine::SCT_Passive )
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Item_UseFailed, theXmlString.GetString(eText_SkillCanNotDrag));
            return;
		}
		int nSkillIndex = -1;
        nSkillIndex = thePlayerRole.m_SkillBag.GetSkillIndexById( pItemDrag->m_pkIconInfo->Id() );
        if ( nSkillIndex == -1 )
            return;

        SMouseItem *pHotkey = &thePlayerRole.m_pHotKeyBag[nHotkeyIndex + More_exMainUIMax + nIndexHotKey * More_ainUIMaxOnly];
        pHotkey->ShortCut.BagType = BagTypeSkill;
        pHotkey->ShortCut.BagIndex = nSkillIndex;
        pHotkey->ItemData.itembaseinfo.ustItemID = pItemDrag->m_pkIconInfo->Id();
        s_CUI_ID_FRAME_SkillProduce.Refresh();
    }
	else if (pSender == s_CUI_ID_FRAME_NewSkillMain.GetListImage())
	{
		// 如果是被动技能
		ItemDefine::SItemSkill* pSkill = NULL; 
		pSkill = GettheItemDetail().GetSkillByID( pItemDrag->m_pkIconInfo->Id(), 1);
		if( !pSkill || pSkill->sSkillCategory == ItemDefine::SCT_Passive || pSkill->sSkillCategory == ItemDefine::SCT_HeroPassive )
		{
			CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Item_UseFailed, theXmlString.GetString(eText_SkillCanNotDrag));
			return;
		}
		int nSkillIndex = -1;
		bool bHeroSkill = false;

		nSkillIndex = thePlayerRole.m_SkillBag.GetSkillIndexById( pItemDrag->m_pkIconInfo->Id() );
		if ( nSkillIndex == -1 )
		{
			nSkillIndex = thePlayerRole.m_HeroSkillBag.GetSkillIndexById( pItemDrag->m_pkIconInfo->Id() );
			if ( nSkillIndex == -1 )
				return;

			bHeroSkill = true;
		}

		SMouseItem *pHotkey = &thePlayerRole.m_pHotKeyBag[nHotkeyIndex+More_exMainUIMax+nIndexHotKey*More_ainUIMaxOnly];
		pHotkey->ShortCut.BagType = BagTypeSkill;
		if ( bHeroSkill )
			pHotkey->ShortCut.BagType = BagTypeHeroSkill;
		pHotkey->ShortCut.BagIndex = nSkillIndex;
		pHotkey->ItemData.itembaseinfo.ustItemID = pItemDrag->m_pkIconInfo->Id();

		int nIndexDrag = s_CUI_ID_FRAME_NewSkillMain.GetListImageIndex(pItemDrag);
		s_CUI_ID_FRAME_NewSkillMain.RemoveSkill(nIndexDrag);
	}
	else if ( s_CUI_ID_FRAME_SKILL.IsSkillList( pSender )) // 如果是技能栏的东东
	{
		switch (pItemDrag->m_dwFlags)
		{
		case CUISkillMgr::eProfession:
		case CUISkillMgr::eXpSkill:
			{
				// 如果是被动技能
				ItemDefine::SItemSkill* pSkill = NULL; 
				pSkill = GettheItemDetail().GetSkillByID( pItemDrag->m_pkIconInfo->Id(), 1);
				if( !pSkill || pSkill->sSkillCategory == ItemDefine::SCT_Passive )
				{
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Item_UseFailed, theXmlString.GetString(eText_SkillCanNotDrag));
					return;
				}
				int nSkillIndex = -1;
				nSkillIndex = thePlayerRole.m_SkillBag.GetSkillIndexById( pItemDrag->m_pkIconInfo->Id() );
				if ( nSkillIndex == -1 )
					return;

				SMouseItem *pHotkey = &thePlayerRole.m_pHotKeyBag[nHotkeyIndex+More_exMainUIMax+nIndexHotKey*More_ainUIMaxOnly];
				pHotkey->ShortCut.BagType = BagTypeSkill;
				pHotkey->ShortCut.BagIndex = nSkillIndex;
				pHotkey->ItemData.itembaseinfo.ustItemID = pItemDrag->m_pkIconInfo->Id();

			}break;
		case CUISkillMgr::eMountSkill:
			{
				// 如果是被动技能
				ItemDefine::SItemSkill* pSkill = NULL; 
				pSkill = GettheItemDetail().GetSkillByID( pItemDrag->m_pkIconInfo->Id(), 1);
				if( !pSkill || pSkill->sSkillCategory != ItemDefine::SCT_MountMasterInitiativeControl )
					return;
				int nSkillIndex = -1;
				nSkillIndex = thePlayerRole.m_MountSkillBag.GetSkillIndexById( pItemDrag->m_pkIconInfo->Id() );
				if ( nSkillIndex == -1 )
				{
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Main_Display, theXmlString.GetString( eText_Mount_NotActived ) );
					return;
				}

				SMouseItem *pHotkey = &thePlayerRole.m_pHotKeyBag[nHotkeyIndex+More_exMainUIMax+nIndexHotKey*More_ainUIMaxOnly];
				pHotkey->ShortCut.BagType = BagTypeMountSkill;
				pHotkey->ShortCut.BagIndex = nSkillIndex;
				pHotkey->ItemData.itembaseinfo.ustItemID = pItemDrag->m_pkIconInfo->Id();
			}break;
		case CUISkillMgr::ePetSkill:
			{
				// 如果是被动技能
				ItemDefine::SItemSkill* pSkill = NULL; 
				pSkill = GettheItemDetail().GetSkillByID( pItemDrag->m_pkIconInfo->Id(), 1);
				if( !pSkill || pSkill->sSkillCategory != ItemDefine::SCT_MountMasterInitiativeControl )
					return;
				int nSkillIndex = -1;
				nSkillIndex = thePlayerRole.m_PetSkillBag.GetSkillIndexById( pItemDrag->m_pkIconInfo->Id() );
				if ( nSkillIndex == -1 )
				{
					CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Main_Display, theXmlString.GetString( eText_Mount_NotActived ) );
					return;
				}

				SMouseItem *pHotkey = &thePlayerRole.m_pHotKeyBag[nHotkeyIndex+More_exMainUIMax+nIndexHotKey*More_ainUIMaxOnly];
				pHotkey->ShortCut.BagType = BagTypePetSkill;
				pHotkey->ShortCut.BagIndex = nSkillIndex;
				pHotkey->ItemData.itembaseinfo.ustItemID = pItemDrag->m_pkIconInfo->Id();
			}
			break;
		case CUISkillMgr::eCommon:
			{
				SMouseItem *pHotkey = &thePlayerRole.m_pHotKeyBag[nHotkeyIndex+More_exMainUIMax+nIndexHotKey*More_ainUIMaxOnly];
				pHotkey->ShortCut.BagType = BagTypeActionUI;
				pHotkey->ShortCut.BagIndex = pItemDrag->m_pkIconInfo->Id();
				pHotkey->ItemData.itembaseinfo.ustItemID = pItemDrag->m_pkIconInfo->Id();
                s_CUI_ID_FRAME_SKILL.RefreshCommon();
			}break;
		}
	}
	else if ( s_CUI_ID_FRAME_PACK.IsListImageByBagType(BT_NormalItemBag, pSender) ) // 背包
	{
		UINT nPackIndex = s_CUI_ID_FRAME_PACK.GetIndexByItem( BT_NormalItemBag, pItemDrag );
		if ( nPackIndex == -1 || nPackIndex >= thePlayerRole.m_bag.GetNowBagSize() )
			return;
		//物品加锁后禁止拖拉
		SCharItem stItems;
		thePlayerRole.m_bag.GetItem( nPackIndex, &stItems );
		if(stItems.storageinfo.bIsLocked)
		{
			s_CUI_ID_FRAME_MessageBox.Show(  theXmlString.GetString(eText_ItemHaveBeenLocked) );
			return;
		}

		SMouseItem *pHotkey = &thePlayerRole.m_pHotKeyBag[nHotkeyIndex+More_exMainUIMax+nIndexHotKey*More_ainUIMaxOnly];
		pHotkey->ShortCut.BagType = BagTypePack;
		pHotkey->ShortCut.BagIndex = nPackIndex;
		pHotkey->ItemData.itembaseinfo.ustItemID = pItemDrag->m_pkIconInfo->Id();
		pHotkey->ItemData.itembaseinfo.useType = stItems.itembaseinfo.useType;
		pHotkey->ItemData.itembaseinfo.nOnlyInt = stItems.itembaseinfo.nOnlyInt;	
	}
	else if( s_CUI_ID_FRAME_Action.IsActionList( pSender ) ) // 表情动作
	{
		SMouseItem *pHotkey = &thePlayerRole.m_pHotKeyBag[nHotkeyIndex+More_exMainUIMax+nIndexHotKey*More_ainUIMaxOnly];
		pHotkey->ShortCut.BagType = BagTypeExpressionAction;
		pHotkey->ShortCut.BagIndex = pItemDrag->m_pkIconInfo->Id();
		pHotkey->ItemData.itembaseinfo.ustItemID = pItemDrag->m_pkIconInfo->Id();
	}
	else if (s_CUI_ID_FRAME_zhujiangbianshen.IsSkillList(pSender) || s_CUI_ID_FRAME_BaseProperty.IsHeroSkillList(pSender)) // 主将技能
	{
		ItemDefine::SItemSkill* pSkill = NULL; 
		pSkill = GettheItemDetail().GetSkillByID( pItemDrag->m_pkIconInfo->Id(), 1);
		if( !pSkill)
		{
			return;
		}
		int nSkillIndex = -1;
		nSkillIndex = thePlayerRole.m_HeroSkillBag.GetSkillIndexById( pItemDrag->m_pkIconInfo->Id() );
		if ( nSkillIndex == -1 )
			return;

		SMouseItem *pHotkey = &thePlayerRole.m_pHotKeyBag[nHotkeyIndex+More_exMainUIMax+nIndexHotKey*More_ainUIMaxOnly];
		pHotkey->ShortCut.BagType = BagTypeHeroSkill;
		pHotkey->ShortCut.BagIndex = nSkillIndex;
		pHotkey->ItemData.itembaseinfo.ustItemID = pItemDrag->m_pkIconInfo->Id();
	}
	else if (pSender == s_CUI_ID_FRAME_SuAnimal.GetZhuDongListImage()
		|| s_CUI_ID_FRAME_SuAnimalMain.IsSubControlInFrame(pSender)) // 副将界面 或者 副将技能栏
	{
		// 如果是被动技能
		ItemDefine::SItemSkill *pSkill = GettheItemDetail().GetSkillByID(pItemDrag->m_pkIconInfo->Id(), 1);
		if (pSkill == NULL || pSkill->sSkillCategory != ItemDefine::SCT_PetMasterManualControl)
			return;

		int nSkillIndex = thePlayerRole.m_PetSkillBag.GetSkillIndexById(pItemDrag->m_pkIconInfo->Id());
		if (nSkillIndex == -1)
		{
			// 副将未出战
			CScreenInfoManager::Instance()->ShowInfoByType(CScreenInfoManager::eType_Main_Display, theXmlString.GetString(eText_Mount_NotActived));
			return;
		}

		SMouseItem *pHotkey = &thePlayerRole.m_pHotKeyBag[nHotkeyIndex + More_exMainUIMax + nIndexHotKey * More_ainUIMaxOnly];
		pHotkey->ShortCut.BagType = BagTypePetSkill;
		pHotkey->ShortCut.BagIndex = nSkillIndex;
		pHotkey->ItemData.itembaseinfo.ustItemID = pItemDrag->m_pkIconInfo->Id();
	}
	s_CUI_ID_FRAME_Target.ForceUpdate();
	//s_CUI_ID_FRAME_Exmain.RefeashHotNumber();
    //RefeashHotKey();

	// 更新快捷键给服务器
	thePlayerRole.SendHotKeyToServer();

	return;
	unguard;
}

bool CUI_ID_FRAME_MAIN::ID_LISTIMG_HotkeyOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	guardfunc;
	if( !m_pID_FRAME_MAIN )
		return false;
	unsigned int nIndex = m_pID_LISTIMG_Hotkey->GetItemIndex( pItem );
	if ( nIndex > More_ainUIMaxOnly || nIndex < 0 )
		return false;

	int nKeyIndex = More_exMainUIMax+nIndex+s_CUI_ID_FRAME_MAIN.nIndexHotKey*More_ainUIMaxOnly;
	ClickHotkey(nKeyIndex);
	return false;
	unguard;
}

bool CUI_ID_FRAME_MAIN::ID_LISTIMG_HotkeyOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	guardfunc;
	if( !m_pID_FRAME_MAIN )
		return false;
	unsigned int nIndex = m_pID_LISTIMG_Hotkey->GetItemIndex( pItem );
	if ( nIndex > More_ainUIMaxOnly || nIndex < 0 )
		return false;

	int nKeyIndex = More_exMainUIMax+nIndex+s_CUI_ID_FRAME_MAIN.nIndexHotKey*More_ainUIMaxOnly;
	ClickHotkey(nKeyIndex);

	return false;
	unguard;
}
// Button
bool CUI_ID_FRAME_MAIN::ID_BUTTON_OUTOnButtonClick( ControlObject* pSender )
{
	guardfunc;
	if( !m_pID_FRAME_MAIN )
		return false;
	FunctionBtnOutIn(TRUE);
	return true;
	unguard;
}

// Button
bool CUI_ID_FRAME_MAIN::ID_BUTTON_INOnButtonClick( ControlObject* pSender )
{
	guardfunc;
	if( !m_pID_FRAME_MAIN )
		return false;
	FunctionBtnOutIn(FALSE);
	return true;
	unguard;
}

bool CUI_ID_FRAME_MAIN::ID_BUTTON_MapOnButtonClick( ControlObject* pSender )
{
	guardfunc;
	if( !m_pID_FRAME_MAIN )
		return false;
	s_CUI_ID_FRAME_AllNpcList.SetVisable( !s_CUI_ID_FRAME_AllNpcList.IsVisable() );
	s_CUI_ID_FRAME_AllNpcList.init();
	return true;
	unguard;
}
// Button
bool CUI_ID_FRAME_MAIN::ID_BUTTON_ShowExmainOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_MAIN )
		return false;
	s_CUI_ID_FRAME_Exmain.SetOnlyShowItemIcon1(
		!s_CUI_ID_FRAME_Exmain.GetOnlyShowItemIcon1());
	return true;
}

void CUI_ID_FRAME_MAIN::InitializeAtEnterWorld()
{
    if( !m_pID_FRAME_MAIN )
        return;

    m_pID_CHECKBOX_Angle->SetShowTip();
    m_pID_CHECKBOX_IsKeyboard->SetShowTip();
    m_pID_CHECKBOX_Angle->SetCheck(getwsCamera()->GetLockCameraMode());
    m_pID_CHECKBOX_IsKeyboard->SetCheck(!g_bMouseMoveMode);
    m_pID_CHECKBOX_showhotkey->SetCheck( true );
    m_pID_FRAME_MAIN->SetMsgProcFun( UIMain_MsgProc );
    m_pID_LISTIMG_Hotkey->ShowPressEffect(true);
    m_pID_LISTIMG_Hotkey->SetShowAllInfo( true );
    m_pID_LISTIMG_Hotkey->SetDisableCanbePick( true );
    m_pID_LISTIMG_Hotkey->SetVisable(true);
    m_pID_LISTIMG_Hotkey->SetDelayTime( g_ControlListImageShortDelayTime );

    if( m_pID_TEXT_Num )
    {
        m_pID_TEXT_Num->SetText("1");
    }
    theUiManager.SetRButtonUp(UIMain_RButtonUp);
    theIconDragManager.SetOnDragBeginFun(OnDragItemBegin);
    theIconDragManager.SetOnDragEndFun(OnDragItemEnd);
	bool bLock = static_cast<bool>(GameSetting::Instance()->GetLevel(GameSetting::eSSC_SKILLLOCK));
	m_pID_LISTIMG_Hotkey->SetEnableDrag( !bLock );

	m_pID_TEXT_LevelUp->SetMsgHoldup(false);
	m_pID_TEXT_LevelUp->SetVisable(false);
}

// 装载UI
bool CUI_ID_FRAME_MAIN::_LoadUI()
{
	guardfunc;

	s_CUI_ID_FRAME_MainMenu.LoadUI();

	DWORD dwResult = theUiManager.AddFrame( "data\\ui\\Main.meui", true,UI_Render_LayerSecond);
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[UI\\Main.UI]失败")
			return false;
	}
	return DoControlConnect();
	unguard;
}
// 关连控件
bool CUI_ID_FRAME_MAIN::DoControlConnect()
{
	guardfunc;
	theUiManager.OnFrameRun( ID_FRAME_MAIN, s_CUI_ID_FRAME_MAINOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_MAIN, s_CUI_ID_FRAME_MAINOnFrameRender );
	theUiManager.OnIconDragOn( ID_FRAME_MAIN, ID_LISTIMG_Hotkey, s_CUI_ID_FRAME_MAINID_LISTIMG_HotkeyOnIconDragOn );
	theUiManager.OnIconButtonClick( ID_FRAME_MAIN, ID_LISTIMG_Hotkey, s_CUI_ID_FRAME_MAINID_LISTIMG_HotkeyOnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_MAIN, ID_LISTIMG_Hotkey, s_CUI_ID_FRAME_MAINID_LISTIMG_HotkeyOnIconRButtonUp );
	theUiManager.OnButtonClick( ID_FRAME_MAIN, ID_BUTTON_Map, s_CUI_ID_FRAME_MAINID_BUTTON_MapOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_MAIN, ID_BUTTON_turnHotkeyUp, s_CUI_ID_FRAME_MAINID_BUTTON_turnHotkeyUpOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_MAIN, ID_BUTTON_turnHotkeyDown, s_CUI_ID_FRAME_MAINID_BUTTON_turnHotkeyDownOnButtonClick );
	theUiManager.OnCheckBoxCheck( ID_FRAME_MAIN, ID_CHECKBOX_IsKeybord, s_CUI_ID_FRAME_MAINID_CHECKBOX_IsKeybordOnClick );
	theUiManager.OnCheckBoxCheck( ID_FRAME_MAIN, ID_CHECKBOX_Angle, s_CUI_ID_FRAME_MAINID_CHECKBOX_AngleOnClick);
	theUiManager.OnCheckBoxCheck( ID_FRAME_MAIN, ID_CHECKBOX_showhotkey, s_CUI_ID_FRAME_MAINID_CHECKBOX_showbotkeyOnClick);
	theUiManager.OnButtonClick( ID_FRAME_MAIN, ID_BUTTON_ShowExmain, s_CUI_ID_FRAME_MAINID_BUTTON_ShowExmainOnButtonClick );
	theUiManager.OnIconDisableDragOn( ID_FRAME_MAIN, ID_LISTIMG_Hotkey, s_CUI_ID_FRAME_MAINID_LISTIMG_HotkyeOnIconDisableDragOn );
	theUiManager.OnIconDisableDragOut( ID_FRAME_MAIN, ID_LISTIMG_Hotkey, s_CUI_ID_FRAME_MAINID_LISTIMG_HotkyeOnIconDisableDragOut );
	theUiManager.OnButtonClick( ID_FRAME_MAIN, ID_BUTTON_Enter, s_CUI_ID_FRAME_MAINID_BUTTON_EnterOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_MAIN, ID_BUTTON_LevelUp, s_CUI_ID_FRAME_MAINID_BUTTON_LevelUpOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_MAIN, ID_TEXT_LevelUp, s_CUI_ID_FRAME_MAINID_TEXT_LevelUpOnButtonClick );

	theUiManager.OnCheckBoxCheck( ID_FRAME_MAIN, ID_CHECKBOX_HideChatList, s_CUI_ID_FRAME_MAINID_CHECKBOX_HideChatListOnClick);

	m_pID_FRAME_MAIN = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_MAIN );
	m_pID_PROGRESS_Exp = (ControlProgress*)theUiManager.FindControl( ID_FRAME_MAIN, ID_PROGRESS_EXP );
	m_pID_LISTIMG_Hotkey = (ControlListImage*)theUiManager.FindControl( ID_FRAME_MAIN, ID_LISTIMG_Hotkey );
	m_pID_PICTURE_BG = (ControlPicture*)theUiManager.FindControl( ID_FRAME_MAIN, ID_PICTURE_BG );
	m_pID_BUTTON_Map = (ControlButton*)theUiManager.FindControl( ID_FRAME_MAIN, ID_BUTTON_Map );
	m_pID_TEXT_Num = (ControlText*)theUiManager.FindControl( ID_FRAME_MAIN, ID_TEXT_Num );
	m_pID_CHECKBOX_Angle = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_MAIN, ID_CHECKBOX_Angle);
	m_pID_CHECKBOX_IsKeyboard = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_MAIN, ID_CHECKBOX_IsKeybord);
    m_pID_CHECKBOX_showhotkey = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_MAIN, ID_CHECKBOX_showhotkey);
    m_pID_BUTTON_turnHotkeyUp = (ControlButton*)theUiManager.FindControl( ID_FRAME_MAIN, ID_BUTTON_turnHotkeyUp );
    m_pID_BUTTON_turnHotkeyDown = (ControlButton*)theUiManager.FindControl( ID_FRAME_MAIN, ID_BUTTON_turnHotkeyDown );
	m_pID_TEXT_EXP = (ControlText*)theUiManager.FindControl( ID_FRAME_MAIN, ID_TEXT_EXP );
	m_pID_BUTTON_Enter = (ControlButton*)theUiManager.FindControl( ID_FRAME_MAIN, ID_BUTTON_Enter );
	m_pID_BUTTON_LevelUp = (ControlButton*)theUiManager.FindControl( ID_FRAME_MAIN, ID_BUTTON_LevelUp );
	m_pID_TEXT_LevelUp = (ControlText*)theUiManager.FindControl( ID_FRAME_MAIN, ID_TEXT_LevelUp );
	m_pID_CHECKBOX_HideChatList = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_MAIN, ID_CHECKBOX_HideChatList);
	assert( m_pID_CHECKBOX_Angle );
	assert( m_pID_CHECKBOX_IsKeyboard );
	assert( m_pID_CHECKBOX_showhotkey );
	assert(m_pID_BUTTON_turnHotkeyUp);
	assert(m_pID_BUTTON_turnHotkeyDown);
    assert( m_pID_FRAME_MAIN );
    assert( m_pID_LISTIMG_Hotkey );
    assert( m_pID_BUTTON_Map );
	assert( m_pID_TEXT_EXP );
	assert( m_pID_BUTTON_LevelUp );
	assert( m_pID_TEXT_LevelUp );
	assert (m_pID_CHECKBOX_HideChatList);
	m_pID_LISTIMG_Hotkey->SetShiftLBClickFun( IconOnShiftLBClick );

    _SetVisable( false );



	return true;
	unguard;
}

BOOL CUI_ID_FRAME_MAIN::FunctionBtnOutIn( bool bVis )
{
	guardfunc;
	if( bVis )
	{
		m_pID_BUTTON_OUT->SetVisable( false );
		m_pID_BUTTON_IN->SetVisable( true );
	}
	else
	{
		m_pID_BUTTON_OUT->SetVisable( true );
		m_pID_BUTTON_IN->SetVisable( false );
	}

	return true;
	unguard;
}

// 卸载UI
bool CUI_ID_FRAME_MAIN::_UnLoadUI()
{
	guardfunc;
	CLOSE_SCRIPT( eUI_OBJECT_Main );
	s_CUI_ID_FRAME_MainMenu.UnLoadUI();

	m_pID_FRAME_MAIN = NULL;
	m_pID_BUTTON_Function = NULL;
	m_pID_PROGRESS_Exp = NULL;
	m_pID_LISTIMG_Hotkey = NULL;
	m_pID_BUTTON_OUT = NULL;
	m_pID_BUTTON_IN = NULL;
	m_pID_PICTURE_BG = NULL;
	m_pID_BUTTON_Map = NULL;
	m_pID_TEXT_Num = NULL;
	m_pID_CHECKBOX_Angle	= NULL;
	m_pID_CHECKBOX_IsKeyboard	= NULL;
	m_pID_CHECKBOX_showhotkey = NULL;
	m_pID_BUTTON_turnHotkeyUp = NULL;
	m_pID_BUTTON_turnHotkeyDown = NULL;
	m_pID_TEXT_EXP = NULL;
	return theUiManager.RemoveFrame( "data\\ui\\Main.meui" );
	unguard;
}
// 是否可视
bool CUI_ID_FRAME_MAIN::_IsVisable()
{
	guardfunc;
    if(!m_pID_FRAME_MAIN)
        return false;

	return m_pID_FRAME_MAIN->IsVisable();
	unguard;
}
// 设置是否可视
void CUI_ID_FRAME_MAIN::_SetVisable( const bool bVisable )
{
	guardfunc;
    if(!m_pID_FRAME_MAIN)
        return;

	m_pID_FRAME_MAIN->SetVisable( bVisable );
	s_CUI_ID_FRAME_Exmain.SetVisable(bVisable);
	unguard;
}

void CUI_ID_FRAME_MAIN::SetHotkey(Msg* pMsg)
{
	guardfunc;
	MsgScriptSetHotkey* pMsgSetHotkey = (MsgScriptSetHotkey*)pMsg;
	if ( pMsgSetHotkey->ustIndex >= More_iHotkey )
		return;
	ItemDefine::SItemCommon *pItemCommon;
	pItemCommon = GettheItemDetail().GetItemByID( pMsgSetHotkey->nID );
	if ( !pItemCommon )
		return;
	SMouseItem *pHotkey;
	pHotkey = &thePlayerRole.m_pHotKeyBag[pMsgSetHotkey->ustIndex];
	switch( pItemCommon->ucItemType )
	{
	case ItemDefine::ITEMTYPE_ACTION:
		{
			pHotkey->ShortCut.BagType = BagTypeActionUI;
			pHotkey->ShortCut.BagIndex = pMsgSetHotkey->nID;
			pHotkey->ItemData.itembaseinfo.ustItemID = pMsgSetHotkey->nID;
		}
		break;
	case ItemDefine::ITEMTYPE_SKILL:
		{
			int nSkillIndex = -1;
			nSkillIndex = thePlayerRole.m_SkillBag.GetSkillIndexById( pMsgSetHotkey->nID );
			if ( nSkillIndex == -1 )
			{
				nSkillIndex = thePlayerRole.m_HeroSkillBag.GetSkillIndexById( pMsgSetHotkey->nID );
				if (nSkillIndex == -1 )
				{
					return;
				}
				pHotkey->ShortCut.BagType = BagTypeHeroSkill;
			}
			else
			{
				pHotkey->ShortCut.BagType = BagTypeSkill;
			}
			pHotkey->ShortCut.BagIndex = nSkillIndex;
			pHotkey->ItemData.itembaseinfo.ustItemID = pMsgSetHotkey->nID;
		}
		break;
	default:
		return;
	}

	RefeashHotKey();

	unguard;
}

// 被签入 暂时这样些. 不签了改过去
void CUI_ID_FRAME_MAIN::RefeashHotNumber()
{
	guardfunc;
	s_CUI_ID_FRAME_Exmain.RefeashHotNumber();
	unguard;
}

void CUI_ID_FRAME_MAIN::ID_CHECKBOX_HideChatListOnClick(ControlObject* pSender, bool* pbChecked)
{
 
	guardfunc;
	if( !m_pID_FRAME_MAIN )
		return;
	if(m_pID_CHECKBOX_HideChatList->IsChecked())
	{//视角旋转
		//getwsCamera()->SetLockCameraMode( TRUE );
		m_pID_CHECKBOX_HideChatList->SetCheck(true);
		s_CUI_ID_FRAME_chatInfoList.SetVisable(false);
		s_CUI_ID_FRAME_InfoList.SetVisable(false);
	}
	else
	{//视角固定
		//getwsCamera()->SetLockCameraMode( FALSE );
		m_pID_CHECKBOX_HideChatList->SetCheck(false);
		s_CUI_ID_FRAME_chatInfoList.SetVisable(true);
		s_CUI_ID_FRAME_InfoList.SetVisable(true);
	}

}
void CUI_ID_FRAME_MAIN::ID_CHECKBOX_AngleOnClick(ControlObject* pSender, bool* pbChecked)
{//这里处理 视角旋转 
	guardfunc;
	if( !m_pID_FRAME_MAIN )
		return;
	if(m_pID_CHECKBOX_Angle->IsChecked())
	{//视角旋转
		getwsCamera()->SetLockCameraMode( TRUE );
	}
	else
	{//视角固定
		getwsCamera()->SetLockCameraMode( FALSE );
	}
	unguard;
}
void CUI_ID_FRAME_MAIN::ID_CHECKBOX_IsKeybordOnClick(ControlObject* pSender, bool* pbChecked)
{
	guardfunc;
	if( !m_pID_FRAME_MAIN )
		return;
	unguard;
}
void CUI_ID_FRAME_MAIN::ID_CHECKBOX_showbotkeyOnClick(ControlObject* pSender, bool* pbChecked)
{
	guardfunc;
	if( !m_pID_FRAME_MAIN )
		return;

	if( s_CUI_ID_FRAME_Exmain.IsVisable())
	{
		s_CUI_ID_FRAME_Exmain.SetVisable( false );

		s_CUI_ID_FRAME_GameSetup.SetShowHotKey(false);
	}

	else 
	{
		s_CUI_ID_FRAME_Exmain.SetVisable( true );

		s_CUI_ID_FRAME_Exmain.SetPos( s_CUI_ID_FRAME_Exmain._rc.left, s_CUI_ID_FRAME_Exmain._rc.top );

		s_CUI_ID_FRAME_GameSetup.SetShowHotKey(true);
	}
	unguard;
}
bool CUI_ID_FRAME_MAIN::ID_BUTTON_turnHotkeyUpOnButtonClick( ControlObject* pSender )
{
	guardfunc;
	if( !m_pID_FRAME_MAIN )
		return false;
	if( nIndexHotKey == 1 )
	{	
		nIndexHotKey = 0;
		m_pID_TEXT_Num->SetText("1");
	}
	else if( nIndexHotKey == 2 )
	{
		nIndexHotKey = 1;
		m_pID_TEXT_Num->SetText("2");
	}
	else if (nIndexHotKey == 0)
	{
		nIndexHotKey = 2;
		m_pID_TEXT_Num->SetText("3");
	}
	RefeashHotKey();

	return false;
	unguard;
}
void CUI_ID_FRAME_MAIN::setIconIndex( int index )
{
	guardfunc;
	if( index < 1 || index > 3 )
		return ;

	nIndexHotKey = index;
	switch( index )
	{
	case 1:
		m_pID_TEXT_Num->SetText("1");
		break;
	case 2:
		m_pID_TEXT_Num->SetText("2");
		break;
	case 3:
		m_pID_TEXT_Num->SetText("3");
		break;
	}
	RefeashHotKey();
	unguard;
}
bool CUI_ID_FRAME_MAIN::ID_BUTTON_turnHotkeyDownOnButtonClick( ControlObject* pSender )
{
	guardfunc;
	if( !m_pID_FRAME_MAIN )
		return false;
	if( nIndexHotKey == 0 )
	{
		nIndexHotKey = 1;
		m_pID_TEXT_Num->SetText("2");
	}
	else if( nIndexHotKey == 1 )
	{
		nIndexHotKey = 2;
		m_pID_TEXT_Num->SetText("3");
	}
	else if( nIndexHotKey == 2 )
	{
		nIndexHotKey = 0;
		m_pID_TEXT_Num->SetText("1");
	}
	RefeashHotKey();
	return false;
	unguard;
}
void CUI_ID_FRAME_MAIN::setAngleChecked()
{
	guardfunc;
    if(!m_pID_FRAME_MAIN)
        return;

	m_pID_CHECKBOX_Angle->SetCheck( !m_pID_CHECKBOX_Angle->IsChecked() );
	ID_CHECKBOX_AngleOnClick(NULL, (bool*)m_pID_CHECKBOX_Angle->IsChecked());
	unguard;
}
void CUI_ID_FRAME_MAIN::setKeyboardChecked()
{
	guardfunc;
    if(!m_pID_FRAME_MAIN)
        return;

	m_pID_CHECKBOX_IsKeyboard->SetCheck( !m_pID_CHECKBOX_IsKeyboard->IsChecked() );
	ID_CHECKBOX_IsKeybordOnClick( NULL, (bool*)m_pID_CHECKBOX_IsKeyboard->IsChecked() );

	unguard;
}

// modified by zhuomeng.hu		[10/9/2010]
void CUI_ID_FRAME_MAIN::RefreshExp()
{
	if(!m_pID_FRAME_MAIN)
		return;

    // 经验条   
    int64 nCurExp = thePlayerRole.GetExpNotUsed();
    int64 nNeedExp = theExpStage.GetExpDistance( thePlayerRole.GetLevel() );
    if( nCurExp < 0 )
        nCurExp = 0;
    __int64 nExpPercent = nCurExp * 1000 / nNeedExp;
    s_CUI_ID_FRAME_CharacterExp.SetExpValue( nExpPercent );
    char szExp[64] = {0};
    MeSprintf_s( szExp, sizeof( szExp ) / sizeof( char ) - 1, "%I64u / %I64u" , nCurExp, nNeedExp );
    s_CUI_ID_FRAME_CharacterExp.SetTextExp( szExp );

    // 装备界面经验显示
    s_CUI_ID_FRAME_BaseProperty.Refresh();

	m_pID_PROGRESS_Exp->SetValue(nExpPercent);
	m_pID_TEXT_EXP->SetText(szExp);

	if (thePlayerRole.GetLevel() < manual_levelup)
	{
		m_pID_BUTTON_LevelUp->SetVisable(false);
	}
	else
		m_pID_BUTTON_LevelUp->SetVisable(true);

	if (thePlayerRole.GetLevel() >= manual_levelup)
	{
		if (nCurExp < nNeedExp)
			m_pID_TEXT_LevelUp->SetVisable(false);
		else
			m_pID_TEXT_LevelUp->SetVisable(true);
	}

}

bool CUI_ID_FRAME_MAIN::ClickHotkey( int nKeyIndex, bool bIconEnable )
{
	if ( s_CUI_ID_FRAME_Team.GetTeamFollowID() >= 0 )
	{
		return false;
	}
	if ( nKeyIndex == -1 )
		return false;

	GetBillBoard()->SetTipCounts(FRIST_FIGHT_SKILLLINK);
	s_CUI_ID_FRAME_MAIN.useSkill( nKeyIndex, false, bIconEnable );
	return true;
}

void CUI_ID_FRAME_MAIN::IconOnShiftLBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	assert(pItem != NULL);

	SCharSkill *pCharSkill = thePlayerRole.m_SkillBag.GetSkillByID(pItem->m_pkIconInfo->Id());
	//assert(IsValidXinFaSkill(pCharSkill));
	if(NULL == pCharSkill )
	{
		pCharSkill = thePlayerRole.m_HeroSkillBag.GetSkillByID(pItem->m_pkIconInfo->Id());
		if (NULL == pCharSkill)
		{
			return;
		}
	}

	ItemDefine::SItemSkill* pItemSKill = GettheItemDetail().GetSkillByID( pCharSkill->ustSkillID, pCharSkill->stSkillLevel );
	if ( pItemSKill == NULL )
	{
		return;
	}

	CommonChatFrame::GetActiveChatFrame()->addHyberTextEx( pItemSKill->GetItemName(), MsgChat::HYBERTYPE_SKILL,  pCharSkill->ustSkillID, pCharSkill->stSkillLevel );
}

void CUI_ID_FRAME_MAIN::UpdateIconInfo()
{
	POINT pos;
	RECT rect;
	GetCursorPos(&pos);
	GetWindowRect(g_hWnd, &rect);

	if(!theApp->IsFullScreen())
	{
		pos.x-=(rect.left + GetSystemMetrics(SM_CXBORDER));
		pos.y-=(rect.top + GetSystemMetrics(SM_CYCAPTION) + GetSystemMetrics(SM_CXBORDER));
	}

	POINT ptMouseOnSel;
	if ( m_pID_LISTIMG_Hotkey->GetTilePt( pos.x, pos.y, &ptMouseOnSel ) == true )
	{
		// 这里tip的位置取当前item的左边界
		// 这样就可以固定tip位置
		RECT rcItem;
		m_pID_LISTIMG_Hotkey->GetItemRect( pos.x, pos.y, rcItem );	
		// 偏移到中间
		rcItem.left += m_pID_LISTIMG_Hotkey->GetItemWidth() / 2;
		rcItem.top += m_pID_LISTIMG_Hotkey->GetItemHeight() / 2;
		
		bool bHaveCompare = false;
		ControlIconDrag::S_ListImg *pItem = m_pID_LISTIMG_Hotkey->GetItem( ptMouseOnSel.x, ptMouseOnSel.y );
		if( !pItem )
		{
			assert(false);
			return;
		}

		int nSrcIndex = m_pID_LISTIMG_Hotkey->GetItemIndex( pItem );

		CItemBag2* pBag = NULL;
		/*switch( thePlayerRole.m_pHotKeyBag[nSrcIndex + More_exMainUIMax].ShortCut.BagType )
		{
		case BT_NormalItemBag:
			pBag = &thePlayerRole.m_bag;
			break;
		case BT_MaterialBag:
			pBag = &thePlayerRole.m_bagMaterial;
			break;
		case BT_TaskBag:
			pBag = &thePlayerRole.m_bagTask;
			break;
		}*/

		if(pBag)
		{
			//更新图标信息
			SCharItem bagItem;
			if(pBag->GetItem( thePlayerRole.m_pHotKeyBag[nSrcIndex + More_exMainUIMax].ShortCut.BagIndex , &bagItem ))
			{
				ItemDefine::SItemCommon *pItemCommon = GettheItemDetail().GetItemByID( bagItem.itembaseinfo.ustItemID );
				if ( !pItemCommon )
					return;
				if( pItemCommon->ucItemType == ItemDefine::ITEMTYPE_WEAPON || pItemCommon->ucItemType == ItemDefine::ITEMTYPE_ARMOUR )
				{
					return;
                }

				int nCount = thePlayerRole.m_bag.GetItemCount( bagItem.itembaseinfo.ustItemID );

				bagItem.itembaseinfo.ustItemCount = nCount;

				pItem->SetData(&bagItem);

				AN_Configure_ShortcutKey::ShortCutKey_Configure eKey =
								(AN_Configure_ShortcutKey::ShortCutKey_Configure)(AN_Configure_ShortcutKey::AN_SCKC_skillLeft1 + nSrcIndex);

				pItem->m_pkIconInfo->m_strHotKey = g_shortcutKey_configure.getValueString(eKey);

				m_pID_LISTIMG_Hotkey->SetItem( pItem, nSrcIndex );
			}
		}
	}
}

ControlListImage* CUI_ID_FRAME_MAIN::GetHotKeyListImage()
{
    if(!m_pID_FRAME_MAIN)
        return NULL;

    return m_pID_LISTIMG_Hotkey;
}

int CUI_ID_FRAME_MAIN::GetHotKeyListImageIndex(ControlIconDrag::S_ListImg* pImg)
{
    if(!m_pID_FRAME_MAIN) 
        return -1;

    return m_pID_LISTIMG_Hotkey->GetItemIndex(pImg);
}

int  CUI_ID_FRAME_MAIN::GetHotKeyItemSize()
{
    if(!m_pID_FRAME_MAIN)
        return 0;

    return m_pID_LISTIMG_Hotkey->GetItemCnt();
}

ControlIconDrag::S_ListImg* CUI_ID_FRAME_MAIN::GetHotKeyItemByIndex(int nIndex)
{
    if(!m_pID_FRAME_MAIN)
        return NULL;

    return m_pID_LISTIMG_Hotkey->GetItemByIndex( nIndex );
}

void CUI_ID_FRAME_MAIN::SetFullSceenValue(bool bVaule)
{
    bFullScreen = bVaule;
}

void CUI_ID_FRAME_MAIN::SetHotKeyPressIndex(int nIndex)
{
    if(!m_pID_FRAME_MAIN)
        return ;

    m_pID_LISTIMG_Hotkey->SetPressItemIndex(nIndex);

}


bool CUI_ID_FRAME_MAIN::IsHotKeyVisable()
{
    if(!m_pID_FRAME_MAIN)
        return NULL;

    return m_pID_LISTIMG_Hotkey->IsVisable();
}

void  CUI_ID_FRAME_MAIN::SetHotKeyListImageDrag(bool bEnable)
{
    if(!m_pID_FRAME_MAIN)
        return;

    m_pID_LISTIMG_Hotkey->SetEnableDrag( bEnable );
}

bool CUI_ID_FRAME_MAIN::SetSkillAutoToListImage(SCharSkill* pSkill_)
{
	if (!pSkill_)
	{
		return false;
	}

	int nNullPlace = m_pID_LISTIMG_Hotkey->GetNullItem();
	if (nNullPlace == -1)
	{
		return false;
	}
	
	ItemDefine::SItemSkill* pSkill = GettheItemDetail().GetSkillByID(pSkill_->ustSkillID, pSkill_->stSkillLevel);	
	if (!pSkill || pSkill->sSkillCategory == ItemDefine::SCT_Passive)
	{
		return false;
	}

	int nSkillIndex = thePlayerRole.m_SkillBag.GetSkillIndexById(pSkill->ustItemID);
	if (nSkillIndex == -1)
	{
		return false;
	}

	SMouseItem *pHotkey = &thePlayerRole.m_pHotKeyBag[nNullPlace + More_exMainUIMax];
	pHotkey->ShortCut.BagType = BagTypeSkill;
	pHotkey->ShortCut.BagIndex = nSkillIndex;
	pHotkey->ItemData.itembaseinfo.ustItemID = pSkill->ustItemID;

	RefeashHotKey();
	thePlayerRole.SendHotKeyToServer();
	
	return true;
}