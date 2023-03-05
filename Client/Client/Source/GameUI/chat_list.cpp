/********************************************************************
Created by UIEditor.exe
FileName: D:\Tj\Client\UI\chat_list.cpp
*********************************************************************/
#include <assert.h>
#include <WindowsX.h>
#include "MeUi/UiManager.h"
#include "chat_list.h"
#include "FuncPerformanceLog.h"
#include "ChatInfoBox.h"
#include "CommonChatFrame.h"
#include "GameSetting.h"
#include "UserData.h"
#include "ui/ChatSet.h"
#include "ChatChannelConfig.h"
#include "ChatInfoBox.h"
#include "Common.h"
#include "Action.h"
#include "ChatHistory.h"
#include "Speaker.h"
#include "InfoList.h"

#define TEXT_LIMIT_SIZE_X       SCREEN_WIDTH * 0.7
#define TEXT_LIMIT_SIZE_Y       SCREEN_HEIGHT * 0.2

static bool s_isShowBackground = true;
extern HWND g_hWnd;

void CUI_ID_FRAME_chatInfoList::ShowChildrenUI(bool bVisible)
{
	// 显示闪烁
	bool bMoveDown = s_CUI_ID_FRAME_chatInfoList.m_pID_Text_Info->GetScrollBar()->GetValue() == s_CUI_ID_FRAME_chatInfoList.m_pID_Text_Info->GetScrollBar()->GetMaxValue();
	bool bCanScrollVisiable = s_CUI_ID_FRAME_chatInfoList.m_pID_Text_Info->IsScrollBarVisable();
	if (!bMoveDown && bCanScrollVisiable)
		bVisible = true;

	//s_CUI_ID_FRAME_chatInfoList.m_pID_BUTTON_Action->SetVisable(
	//	bVisible);
	s_CUI_ID_FRAME_chatInfoList.RefreshChannelVisible( 
		bVisible);

	s_CUI_ID_FRAME_chatInfoList.m_pID_BUTTON_Low->SetVisable( 
		bVisible && bCanScrollVisiable);
}

//bool CUI_ID_FRAME_chatInfoList::ID_BUTTON_HornOnButtonClick( ControlObject* pSender )
//{
//	s_CUI_ID_FRAME_Speaker.SetVisable(true, AN_S2A_OpenUI_ChatHIGHSHOUT);
//
//	return true;
//}

// bool CUI_ID_FRAME_chatInfoList::ID_BUTTON_SaveOnButtonClick( ControlObject* pSender )
// {
// 	return true;
// }

bool CUI_ID_FRAME_chatInfoList::ID_BUTTON_HistoryOnButtonClick( ControlObject* pSender )
{
 	s_CUI_ID_FRAME_ChatHistory.ShowHistoryChat(0);
	return true;
}

bool CUI_ID_FRAME_chatInfoList::ChangeSizeToPoint( int nX, int nY, bool bByDeviceReset )
{
	// 鼠标的变化和按钮的显示
	if(s_CUI_ID_FRAME_chatInfoList.IsPtInListObject(nX,nY))
	{
		s_CUI_ID_FRAME_chatInfoList.SetButtonToudongVisable(true);

		if (s_CUI_ID_FRAME_chatInfoList.IsPtInObjectTuodong(nX, nY))
		{
			theMouseManager.SetUICursor(MouseManager::Type_LeftDrag);
			theMouseManager.SetCursor(MouseManager::Type_LeftDrag);
			theMouseManager.SetCanSetCursor(false);
		}
	}
	else
	{
		if (!s_CUI_ID_FRAME_chatInfoList.GetChangeSize())
		{
			s_CUI_ID_FRAME_chatInfoList.SetButtonToudongVisable(false);
		}
	}

	if( !bByDeviceReset )
	{
		if (!s_CUI_ID_FRAME_chatInfoList.GetChangeSize())
			return false;
	}

	theMouseManager.SetCanSetCursor(true);
	theMouseManager.SetUICursor(MouseManager::Type_LeftDrag);
	theMouseManager.SetCursor(MouseManager::Type_LeftDrag);
	theMouseManager.SetCanSetCursor(false);

	// 移动前坐标
	INT nOffsetX = nX - s_CUI_ID_FRAME_chatInfoList.GetOldMousePosX();
	INT nOffsetY = nY - s_CUI_ID_FRAME_chatInfoList.GetOldMousePosY();
	s_CUI_ID_FRAME_chatInfoList.SetOldMousePosX(nX);
	s_CUI_ID_FRAME_chatInfoList.SetOldMousePosY(nY);

	// Di控件的大小更新
	RECT rc = s_CUI_ID_FRAME_chatInfoList.GetPictureDi();
	rc.bottom -= nOffsetY;
	rc.right += nOffsetX;

	int w = rc.right - rc.left;
	int h = rc.bottom - rc.top;
	if (w < s_CUI_ID_FRAME_chatInfoList.GetMinWidth() || rc.right > SCREEN_WIDTH - 100 * ControlObject::GetSCALE(NULL))
	{
		rc.right -= nOffsetX;
		nOffsetX = 0;
	}
	if ((h < s_CUI_ID_FRAME_chatInfoList.GetMinHeight() || SCREEN_HEIGHT - rc.bottom < 100 * ControlObject::GetSCALE(NULL)) &&  !bByDeviceReset )
	{
		rc.bottom += nOffsetY;
		nOffsetY = 0;
	}

	if( !bByDeviceReset )
	{
		if ( (nX > TEXT_LIMIT_SIZE_X && nOffsetX > 0) || (nY < TEXT_LIMIT_SIZE_Y && nOffsetY < 0) )
			return true;
	}

	s_CUI_ID_FRAME_chatInfoList.SetPictureDi(&rc);

	// 更新整个Frame以及Text控件的位置
	rc = s_CUI_ID_FRAME_chatInfoList.GetChatInfoListSize();
	rc.top += nOffsetY;
	rc.right += nOffsetX;
	s_CUI_ID_FRAME_chatInfoList.SetChatInfoListSize(&rc);

	rc = s_CUI_ID_FRAME_chatInfoList.GetListInfoSize();
	rc.bottom -= nOffsetY;
	rc.right += nOffsetX;
	s_CUI_ID_FRAME_chatInfoList.SetListInfoSize(&rc);

	rc = s_CUI_ID_FRAME_chatInfoList.GetHornInfoSize();
	rc.right += 0;
	s_CUI_ID_FRAME_chatInfoList.SetHornInfoSize(&rc);
	

	rc = s_CUI_ID_FRAME_chatInfoList.GetHornProgressSize();
	rc.right += nOffsetX;
	s_CUI_ID_FRAME_chatInfoList.SetHornProgressSize(&rc);

	// 保存到配置文件
	rc = s_CUI_ID_FRAME_chatInfoList.GetPictureDi();
	GameSetting::Instance()->SetLevel( GameSetting::eGSC_ChatListWidth, (rc.right - rc.left));
	GameSetting::Instance()->SetLevel( GameSetting::eGSC_ChatListHeight, (rc.bottom - rc.top));

	s_CUI_ChatInfoBox.Refresh(s_CUI_ID_FRAME_chatInfoList.GetChannelStartIndex(s_CUI_ChatInfoBox.GetChatChannelIndex()));
	s_CUI_ID_FRAME_Speaker.Refresh(0);

	return true;
}

static bool UIChatList_MsgProc(UINT msg, WPARAM wParam, LPARAM lParam, bool bMsgUsed)
{
	switch (msg)
	{
	case WM_LBUTTONUP:
		{
			INT nX = GET_X_LPARAM(lParam);
			INT nY = GET_Y_LPARAM(lParam);
			if(s_CUI_ID_FRAME_chatInfoList.IsPtInListObject(nX,nY))
			{
				s_CUI_ID_FRAME_chatInfoList.SetChangeSize(false);
				theMouseManager.SetCanSetCursor(true);
				char szSetting[MAX_PATH] = {0};
				MeSprintf_s( szSetting, sizeof(szSetting)/sizeof(char) - 1, "%s%s", CUserData::Instance()->GetUserDataPath(),
					GameSetting::Instance()->GetCustomSettingDirectory() );
				GameSetting::Instance()->SaveSetting( szSetting );
			}			
		}
		break;
	case WM_MOUSEMOVE:
		{

			INT nX = GET_X_LPARAM(lParam);
			INT nY = GET_Y_LPARAM(lParam);
			if(!s_CUI_ID_FRAME_chatInfoList.IsPtInListObject(nX,nY) && !s_CUI_ID_FRAME_chatInfoList.IsInMaxFrame(nX,nY))
			{
				s_CUI_ID_FRAME_chatInfoList.SetChangeSize(false);
				break;
			}
         



			CUI_ID_FRAME_chatInfoList::ChangeSizeToPoint( nX, nY );
		}
		break;
	}
	return false;
}


static bool UIChatList_TuodongOnLButtonDown(INT nX, INT nY)
{
	if (s_CUI_ID_FRAME_chatInfoList.GetChangeSize())
		return true;

	s_CUI_ID_FRAME_chatInfoList.SetChangeSize(true);
	s_CUI_ID_FRAME_chatInfoList.SetOldMousePosX(nX);
	s_CUI_ID_FRAME_chatInfoList.SetOldMousePosY(nY);
	return true;
}

static bool UIChatList_TuodongOnLButtonUp(INT nX, INT nY)
{
	s_CUI_ID_FRAME_chatInfoList.SetChangeSize(false);
	return true;
}

CUI_ID_FRAME_chatInfoList s_CUI_ID_FRAME_chatInfoList;
MAP_FRAME_RUN( s_CUI_ID_FRAME_chatInfoList, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_chatInfoList, OnFrameRender )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_chatInfoList, ID_Text_InfoOnListSelectChange )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_chatInfoList, ID_BUTTON_ClearOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_chatInfoList, ID_BUTTON_DiaphaneityOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_chatInfoList, ID_BUTTON_ChatSetOnButtonClick )
//MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_chatInfoList, ID_BUTTON_ActionOnButtonClick )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_chatInfoList, ID_CHECKBOX_Channel1OnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_chatInfoList, ID_CHECKBOX_Channel2OnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_chatInfoList, ID_CHECKBOX_Channel3OnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_chatInfoList, ID_CHECKBOX_Channel4OnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_chatInfoList, ID_CHECKBOX_Channel5OnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_chatInfoList, ID_CHECKBOX_Channel6OnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_chatInfoList, ID_CHECKBOX_Channel7OnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_chatInfoList, ID_CHECKBOX_Channel8OnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_chatInfoList, ID_CHECKBOX_Channel9OnCheckBoxCheck )
//MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_chatInfoList, ID_BUTTON_HornOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_chatInfoList, ID_BUTTON_HistoryOnButtonClick )
//MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_chatInfoList, ID_BUTTON_SaveOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_chatInfoList, ID_BUTTON_LowOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_chatInfoList, ID_BUTTON_ShowOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_chatInfoList, ID_BUTTON_HideOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_chatInfoList, ID_BUTTON_OpenOnButtonClick )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_chatInfoList, ID_CHECKBOX_Channel10OnCheckBoxCheck )
MAP_CHECK_BOX_CHECK_CALLBACK( s_CUI_ID_FRAME_chatInfoList, ID_CHECKBOX_Channel11OnCheckBoxCheck )

CUI_ID_FRAME_chatInfoList::CUI_ID_FRAME_chatInfoList()
{
	guardfunc;
	// GuildMember
	m_pID_FRAME_chatInfoList = NULL;
	m_pID_Text_Info = NULL;
	m_pID_BUTTON_Tuodong = NULL;
	m_pID_PICTURE_Di = NULL;
	m_pID_BUTTON_Diaphaneity = NULL;
	m_pID_CHECKBOX_Channel1 = NULL;
	m_pID_CHECKBOX_Channel2 = NULL;
	m_pID_CHECKBOX_Channel3 = NULL;
    m_pID_CHECKBOX_Channel4 = NULL;
	m_pID_CHECKBOX_Channel5 = NULL;
    m_pID_CHECKBOX_Channel6 = NULL;
    m_pID_CHECKBOX_Channel7 = NULL;
    m_pID_CHECKBOX_Channel8 = NULL;
    m_pID_CHECKBOX_Channel9 = NULL;
	//m_pID_BUTTON_Action = NULL;
	m_pID_BUTTON_History = NULL;
	//m_pID_BUTTON_Horn = NULL;
	//m_pID_BUTTON_Save = NULL;
	m_pID_Text_Info = NULL;
	m_pID_Text_HornInfo = NULL;
	m_pID_BUTTON_Low = NULL;
    m_pID_BUTTON_Show = NULL;
    m_pID_BUTTON_Hide = NULL;
    m_pID_BUTTON_Open = NULL;
    m_pID_PICTURE_OpenBg = NULL;
	m_pID_PROGRESS_Low = NULL;

	m_pID_CHECKBOX_Channel10 = NULL;
	m_pID_CHECKBOX_Channel11 = NULL;
	m_pID_PICTURE_SHOUT = NULL;

	m_nOldMousePosX = 0;
	m_nOldMousePosY = 0;
	m_bChangeSize = false;
	m_nMinWidth = /*300*/250;
	m_nMinHeight = /*100*/285;
    m_bChatListChanged = false;
    m_fAlpha = 0.0f;

	memset( m_ChannelCtrl, 0, MAX_CHANNELTAB_COUNT );
	memset( m_ChannelStartIndex, 0, MAX_CHANNELTAB_COUNT );

	unguard;

}
// Frame
bool CUI_ID_FRAME_chatInfoList::OnFrameRun()
{
	/*m_pID_FRAME_chatInfoList->SetRedraw();*/
//    if( IsVisable() )
//     {
// 		theMouseManager.SetCanSetCursor(true);
// 		POINT ptMouse;
// 
// 		GetCursorPos( &ptMouse );
// 		ScreenToClient( g_hWnd, &ptMouse );
// 		int nX = (int)ptMouse.x;
// 		int nY = (int)ptMouse.y;
// 		if(s_CUI_ID_FRAME_chatInfoList.IsPtInListObject(nX,nY))
// 		{
// 			s_CUI_ID_FRAME_chatInfoList.SetButtonToudongVisable(true);
// 			// 显示界面buttons
// 			if( !s_CUI_ID_FRAME_chatInfoList.IsUILoad() )
// 				return false;
// 
// 			s_CUI_ID_FRAME_chatInfoList.VisableBtns( true );
// 			// End
// 			if( s_CUI_ID_FRAME_chatInfoList.GetRealAlpha() < 0.01f )
// 			{
// 				s_CUI_ID_FRAME_chatInfoList.SetTempAlpha( 0.20f );
// 			}
// 			if (s_CUI_ID_FRAME_chatInfoList.IsPtInObjectTuodong(nX, nY))
// 			{
// 				theMouseManager.SetUICursor(MouseManager::Type_LeftDrag);
// 				theMouseManager.SetCursor(MouseManager::Type_LeftDrag);
// 			}
// 		}
// 		else
// 		{
// 			// 隐藏界面
// 			if( !s_CUI_ID_FRAME_chatInfoList.IsUILoad() )
// 				return false;
// 
// 			s_CUI_ID_FRAME_chatInfoList.VisableBtns( false );
// 			s_CUI_ID_FRAME_chatInfoList.ShowGroupMenu(false);
// 			if( s_CUI_ID_FRAME_chatInfoList.GetRealAlpha() < 0.01f )
// 			{
// 				s_CUI_ID_FRAME_chatInfoList.SetTempAlpha( s_CUI_ID_FRAME_chatInfoList.GetRealAlpha() );
// 			}
// 			// End
// 
// 			if (!s_CUI_ID_FRAME_chatInfoList.GetChangeSize())
// 			{
// 				s_CUI_ID_FRAME_chatInfoList.SetButtonToudongVisable(false);
// 			}
// 			else
// 			{
// 				if(theMouseManager.GetCursor() == MouseManager::Type_LeftDrag)
// 				{
// 					theMouseManager.SetUICursor(MouseManager::Type_Arrow);
// 					theMouseManager.SetCursor(MouseManager::Type_Arrow);
// 				}
// 			}
// 		}
// 		if (s_CUI_ID_FRAME_chatInfoList.GetChangeSize())
// 		{
// 			theMouseManager.SetUICursor(MouseManager::Type_LeftDrag);
// 			theMouseManager.SetCursor(MouseManager::Type_LeftDrag);
// 		}
// 
// 		if( m_bChatListChanged )
//         {
//             m_bChatListChanged = false;
// 
// 
// 
// 
// //             const std::vector<UiManager::S_UI*>& vtUIs = theUiManager.getUIVec()[UI_Render_LayerThree];
// //             for ( UINT n=0; n<vtUIs.size(); n++ )
// //             {
// //                 if ( !vtUIs[n]->m_pUI )
// //                     continue;  
// //                 if (vtUIs[n]->m_pUI->IsVisable() &&
// //                     vtUIs[n]->m_pUI->IsMsgHoldup() &&
// //                     vtUIs[n]->m_pUI->PtInObject(nX, nY) )
// //                 {
// //                     return true;
// //                 }
// //             }
// 
// //             if (!s_CUI_ID_FRAME_chatInfoList.m_bChangeSize)
//             {
//                 RECT rc;
//                 s_CUI_ID_FRAME_chatInfoList.m_pID_FRAME_chatInfoList->GetRealRect( &rc );
//                 if (nX >= rc.left && nX <= rc.right &&
//                     nY >= rc.top && nY <= rc.bottom)
//                 {
//                     theMouseManager.SetCanSetCursor(true);
//                     // 鼠标在聊天框里，判断鼠标是否放在物品链接上
// 					EKeyType eType = s_CUI_ID_FRAME_chatInfoList.PtInHyberListInfo(nX, nY);
// 					// 鼠标在聊天框里，判断鼠标是否放在物品链接上
// 					if( eType == eKeyItem )
// 					{
// 						theMouseManager.SetUICursor(MouseManager::Type_ChatHyper);
// 						theMouseManager.SetCursor(MouseManager::Type_ChatHyper);
// 					}
// 					else if( eType == eKeyPlayer )
// 					{
// 						theMouseManager.SetUICursor(MouseManager::Type_ChatPlayer);
// 						theMouseManager.SetCursor(MouseManager::Type_ChatPlayer);
// 					}
//                     else
//                     {
//                         theMouseManager.SetUICursor(MouseManager::Type_Arrow);
//                         theMouseManager.SetCursor(MouseManager::Type_Arrow);
//                     }
//                 }
//             }
//         }
// 		theMouseManager.SetCanSetCursor(false);
// 		
//    }
   
	return true;
}

void CUI_ID_FRAME_chatInfoList::RenderTip()
{
	if (CommonChatFrame::GetActiveChatFrame())
	{
		/*CommonChatFrame::GetActiveChatFrame()->m_FreeTip.Render( CommonChatFrame::GetActiveChatFrame()->GetFontIndex(), 
			CommonChatFrame::GetActiveChatFrame()->GetFontSize() * ControlObject::GetREAL_SCALE(CommonChatFrame::GetActiveChatInfoBox()),
			CommonChatFrame::GetActiveChatFrame()->GetFontColor() );*/

		//=====================================================================
		// 所有的FreeTip 的显示
		CommonChatFrame::GetActiveChatFrame()->RenderAllFreeTip();
	}
}

bool CUI_ID_FRAME_chatInfoList::OnFrameRender()
{
	if( IsVisable() )
	{
		// 显示界面buttons
		if( !s_CUI_ID_FRAME_chatInfoList.IsUILoad() )
			return false;

		theMouseManager.SetCanSetCursor(true);
		POINT ptMouse;

		GetCursorPos( &ptMouse );
		ScreenToClient( g_hWnd, &ptMouse );
		int nX = (int)ptMouse.x;
		int nY = (int)ptMouse.y;
		if(s_CUI_ID_FRAME_chatInfoList.IsPtInListObject(nX,nY))
		{
			s_CUI_ID_FRAME_chatInfoList.SetButtonToudongVisable(true);

			s_CUI_ID_FRAME_chatInfoList.VisableBtns( true );
			// End
			if( s_CUI_ID_FRAME_chatInfoList.GetRealAlpha() < 0.01f )
			{
				s_CUI_ID_FRAME_chatInfoList.SetTempAlpha( 0.20f );
			}
			if (s_CUI_ID_FRAME_chatInfoList.IsPtInObjectTuodong(nX, nY))
			{
				theMouseManager.SetUICursor(MouseManager::Type_LeftDrag);
				theMouseManager.SetCursor(MouseManager::Type_LeftDrag);
			}
			m_pID_Text_Info->Run();
			m_pID_Text_HornInfo->Run();
		}
		else
		{
			s_CUI_ID_FRAME_chatInfoList.VisableBtns( false );
			s_CUI_ID_FRAME_chatInfoList.ShowGroupMenu(false);
			if( s_CUI_ID_FRAME_chatInfoList.GetRealAlpha() < 0.01f )
			{
				s_CUI_ID_FRAME_chatInfoList.SetTempAlpha( s_CUI_ID_FRAME_chatInfoList.GetRealAlpha() );
			}
			// End

			if (!s_CUI_ID_FRAME_chatInfoList.GetChangeSize())
			{
				s_CUI_ID_FRAME_chatInfoList.SetButtonToudongVisable(false);
			}
			else
			{
				if(theMouseManager.GetCursor() == MouseManager::Type_LeftDrag)
				{
					theMouseManager.SetUICursor(MouseManager::Type_Arrow);
					theMouseManager.SetCursor(MouseManager::Type_Arrow);
				}
			}
		}
		if (s_CUI_ID_FRAME_chatInfoList.GetChangeSize())
		{
			theMouseManager.SetUICursor(MouseManager::Type_LeftDrag);
			theMouseManager.SetCursor(MouseManager::Type_LeftDrag);
		}


		if( m_bChatListChanged )
		{
			m_bChatListChanged = false;




			//             const std::vector<UiManager::S_UI*>& vtUIs = theUiManager.getUIVec()[UI_Render_LayerThree];
			//             for ( UINT n=0; n<vtUIs.size(); n++ )
			//             {
			//                 if ( !vtUIs[n]->m_pUI )
			//                     continue;  
			//                 if (vtUIs[n]->m_pUI->IsVisable() &&
			//                     vtUIs[n]->m_pUI->IsMsgHoldup() &&
			//                     vtUIs[n]->m_pUI->PtInObject(nX, nY) )
			//                 {
			//                     return true;
			//                 }
			//             }

			//             if (!s_CUI_ID_FRAME_chatInfoList.m_bChangeSize)
			{
				RECT rc;
				s_CUI_ID_FRAME_chatInfoList.m_pID_FRAME_chatInfoList->GetRealRect( &rc );
				if (nX >= rc.left && nX <= rc.right &&
					nY >= rc.top && nY <= rc.bottom)
				{
					theMouseManager.SetCanSetCursor(true);
					// 鼠标在聊天框里，判断鼠标是否放在物品链接上
					EKeyType eType = s_CUI_ID_FRAME_chatInfoList.PtInHyberListInfo(nX, nY);
					// 鼠标在聊天框里，判断鼠标是否放在物品链接上
					if( eType == eKeyItem )
					{
						theMouseManager.SetUICursor(MouseManager::Type_ChatHyper);
						theMouseManager.SetCursor(MouseManager::Type_ChatHyper);
					}
					else if( eType == eKeyPlayer )
					{
						theMouseManager.SetUICursor(MouseManager::Type_ChatPlayer);
						theMouseManager.SetCursor(MouseManager::Type_ChatPlayer);
					}
					else
					{
						theMouseManager.SetUICursor(MouseManager::Type_Arrow);
						theMouseManager.SetCursor(MouseManager::Type_Arrow);
					}
				}
			}
		}
		theMouseManager.SetCanSetCursor(false);

	}

	if( m_groupAll.IsVisible() && m_pID_Text_Info->IsScrollBarVisable() )
	{
		m_pID_BUTTON_Low->SetVisable( true );
		ControlScrollBar* pScrollBar = m_pID_Text_Info->GetScrollBar();
		if (pScrollBar->GetValue() == pScrollBar->GetMaxValue())
		{
			ShowLowButtonEffect(false);
		}
	}
	else
		m_pID_BUTTON_Low->SetVisable( false );

	s_CUI_ID_FRAME_Speaker.RenderEffect();

	return true;
}
// List
void CUI_ID_FRAME_chatInfoList::ID_Text_InfoOnListSelectChange( ControlObject* pSender, ControlList::S_List* pItem )
{
}
// Button
bool CUI_ID_FRAME_chatInfoList::ID_BUTTON_ClearOnButtonClick( ControlObject* pSender )
{
	m_ChannelStartIndex[s_CUI_ChatInfoBox.GetChatChannelIndex()] = s_CUI_ChatInfoBox.GetCurrChatInfoIndex(); 
	s_CUI_ChatInfoBox.ClearChatShow();
	m_groupSet.SetVisible( true );
	return true;
}

// Button
bool CUI_ID_FRAME_chatInfoList::ID_BUTTON_ChatSetOnButtonClick( ControlObject* pSender )
{
	s_CUI_ID_FRAME_ChatSet.SetVisable( !s_CUI_ID_FRAME_ChatSet.IsVisable() );
	m_groupSet.SetVisible( true );
	return true;
}

//add by yanli  2010-9-19
// Button
//bool CUI_ID_FRAME_chatInfoList::ID_BUTTON_ActionOnButtonClick( ControlObject* pSender )
//{
//	s_CUI_ID_FRAME_Action.SetVisable( true );
//	m_groupSet.SetVisible( true );
//	return true;
//}

// CheckBox
void CUI_ID_FRAME_chatInfoList::ID_CHECKBOX_Channel1OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	m_tabGroup.TogglePage( m_pID_CHECKBOX_Channel1 );
	s_CUI_ChatInfoBox.SetChatChannelIndex( 0 );
	s_CUI_ChatInfoBox.Refresh(m_ChannelStartIndex[0]);
}
// CheckBox
void CUI_ID_FRAME_chatInfoList::ID_CHECKBOX_Channel2OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	m_tabGroup.TogglePage( m_pID_CHECKBOX_Channel2 );
	s_CUI_ChatInfoBox.SetChatChannelIndex( 1 );
	s_CUI_ChatInfoBox.Refresh(m_ChannelStartIndex[1]);
}
// CheckBox
void CUI_ID_FRAME_chatInfoList::ID_CHECKBOX_Channel3OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	m_tabGroup.TogglePage( m_pID_CHECKBOX_Channel3 );
	s_CUI_ChatInfoBox.SetChatChannelIndex( 2 );//根据调试信息显示战斗信息的索引是:7
	s_CUI_ChatInfoBox.Refresh(m_ChannelStartIndex[2]);
}
// CheckBox
void CUI_ID_FRAME_chatInfoList::ID_CHECKBOX_Channel4OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	m_tabGroup.TogglePage( m_pID_CHECKBOX_Channel4 );
	s_CUI_ChatInfoBox.SetChatChannelIndex( 3 );
	s_CUI_ChatInfoBox.Refresh(m_ChannelStartIndex[3]);
}
// CheckBox
void CUI_ID_FRAME_chatInfoList::ID_CHECKBOX_Channel5OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	m_tabGroup.TogglePage( m_pID_CHECKBOX_Channel5 );
	s_CUI_ChatInfoBox.SetChatChannelIndex( 4 );
	s_CUI_ChatInfoBox.Refresh(m_ChannelStartIndex[4]);
}
// CheckBox
void CUI_ID_FRAME_chatInfoList::ID_CHECKBOX_Channel6OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
    m_tabGroup.TogglePage( m_pID_CHECKBOX_Channel6 );
    s_CUI_ChatInfoBox.SetChatChannelIndex( 5 );
    s_CUI_ChatInfoBox.Refresh(m_ChannelStartIndex[5]);
}

void CUI_ID_FRAME_chatInfoList::ID_CHECKBOX_Channel7OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
    m_tabGroup.TogglePage( m_pID_CHECKBOX_Channel7 );
    s_CUI_ChatInfoBox.SetChatChannelIndex( 6 );
    s_CUI_ChatInfoBox.Refresh(m_ChannelStartIndex[6]);
}

void CUI_ID_FRAME_chatInfoList::ID_CHECKBOX_Channel8OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
    m_tabGroup.TogglePage( m_pID_CHECKBOX_Channel8 );
    s_CUI_ChatInfoBox.SetChatChannelIndex( 7 );
    s_CUI_ChatInfoBox.Refresh(m_ChannelStartIndex[7]);
}

void CUI_ID_FRAME_chatInfoList::ID_CHECKBOX_Channel9OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
    m_tabGroup.TogglePage( m_pID_CHECKBOX_Channel9 );
    s_CUI_ChatInfoBox.SetChatChannelIndex( 9 );  //9对应的是usersting。config中的 第九个聊天频道 要一一对应起来 ，改聊天频道的时候要注意 lyh
    s_CUI_ChatInfoBox.Refresh(m_ChannelStartIndex[9]);
}

//lyh ++官员聊天频道
void CUI_ID_FRAME_chatInfoList::ID_CHECKBOX_Channel11OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked  )
{
	m_tabGroup.TogglePage( m_pID_CHECKBOX_Channel11 );
	s_CUI_ChatInfoBox.SetChatChannelIndex( 8 );
	s_CUI_ChatInfoBox.Refresh(m_ChannelStartIndex[8]);
}

// Button
bool CUI_ID_FRAME_chatInfoList::ID_BUTTON_LowOnButtonClick( ControlObject* pSender )
{
	m_pID_Text_Info->ScrollToTheLast();
	ShowLowButtonEffect(false);
	return true;
}

bool CUI_ID_FRAME_chatInfoList::ID_BUTTON_ShowOnButtonClick( ControlObject* pSender )
{
    if( !IsUILoad() )
        return false;

    ShowAll( true );
    m_pID_BUTTON_Show->SetVisable( false );
    m_pID_BUTTON_Hide->SetVisable( true );
    return true;
}

bool CUI_ID_FRAME_chatInfoList::ID_BUTTON_HideOnButtonClick( ControlObject* pSender )
{
    if( !IsUILoad() )
        return false;

    ShowAll( false );
    m_pID_BUTTON_Show->SetVisable( true );
    m_pID_BUTTON_Hide->SetVisable( false );
    return true;
}

bool CUI_ID_FRAME_chatInfoList::ID_BUTTON_OpenOnButtonClick( ControlObject* pSender )
{
    if( !IsUILoad() )
        return false;

    m_groupMenu.SetVisible( !m_groupMenu.IsVisible() );
    return true;
}

bool CUI_ID_FRAME_chatInfoList::ID_BUTTON_DiaphaneityOnButtonClick( ControlObject* pSender )
{
    if( !IsUILoad() )
        return false;

    if( m_fAlphaSet == 0.0f )
        m_fAlphaSet = 0.20f;
    else if( m_fAlphaSet == 0.20f )
        m_fAlphaSet = 0.35f;
    else if( m_fAlphaSet == 0.35f )
        m_fAlphaSet = 0.50f;
    else if( m_fAlphaSet == 0.50f )
        m_fAlphaSet = 0.70f;
    else if( m_fAlphaSet == 0.70f )
        m_fAlphaSet = 0.0f;

    SetRealAlpha( m_fAlphaSet );
    s_CUI_ID_FRAME_InfoList.SetRealAlpha( m_fAlphaSet );
    return true;
}

// CheckBox
void CUI_ID_FRAME_chatInfoList::ID_CHECKBOX_Channel10OnCheckBoxCheck( ControlObject* pSender, bool* pbChecked )
{
	if ( !m_pID_FRAME_chatInfoList )
		return;
	m_tabGroup.TogglePage( m_pID_CHECKBOX_Channel10 );
	s_CUI_ChatInfoBox.SetChatChannelIndex( 9 );
	s_CUI_ChatInfoBox.Refresh(m_ChannelStartIndex[9]);
}

void CUI_ID_FRAME_chatInfoList::InitializeAtEnterWorld()
{
    if( !m_pID_FRAME_chatInfoList )
        return;

    m_pID_BUTTON_Clear->SetShowTip( true );
    m_pID_BUTTON_Clear->setTip( m_pID_BUTTON_Clear->GetData()->m_szCaption );
	m_pID_BUTTON_Diaphaneity->SetShowTip(true);
	m_pID_BUTTON_Diaphaneity->setTip( m_pID_BUTTON_Diaphaneity->GetData()->m_szCaption );
    //	m_pID_BUTTON_Clear->SetVisable( false );
    m_pID_BUTTON_History->SetShowTip( true );
    m_pID_BUTTON_History->setTip( m_pID_BUTTON_History->GetData()->m_szCaption );
    //m_pID_BUTTON_Horn->SetShowTip( true );
    //m_pID_BUTTON_Horn->setTip( m_pID_BUTTON_Horn->GetData()->m_szCaption );
    // 	m_pID_BUTTON_Save->SetShowTip( true );
    // 	m_pID_BUTTON_Save->setTip( m_pID_BUTTON_Save->GetData()->m_szCaption );
    //m_pID_BUTTON_Action->SetShowTip( true );
    //m_pID_BUTTON_Action->setTip( m_pID_BUTTON_Action->GetData()->m_szCaption );
    m_pID_BUTTON_ChatSet->SetShowTip( true );
    m_pID_BUTTON_ChatSet->setTip( m_pID_BUTTON_ChatSet->GetData()->m_szCaption );
    m_pID_BUTTON_Open->SetShowTip( true );
    m_pID_BUTTON_Open->setTip( m_pID_BUTTON_Open->GetData()->m_szCaption );

    // 	m_pID_Text_Info->SetLeftScrollBar(true);
    // 	m_pID_Text_Info->HaveSelBar(false);
    // 	m_pID_FRAME_chatInfoList->SetMsgHoldup(false);
    //m_pID_Text_Info->SetScrollVisable( true );
    //m_pID_Text_Info->ShowScrollBar( true );

    // 	m_groupSet.AddControl( m_pID_BUTTON_HideWall );
    // 	m_groupSet.AddControl( m_pID_BUTTON_ChatSet );
    // 	m_groupSet.AddControl( m_pID_BUTTON_Action );
    // 	m_groupSet.AddControl( m_pID_BUTTON_Clear );
    // 	m_groupSet.AddControl( m_pID_PICTURE_ListSet );
    // 	m_groupSet.SetVisible( false );
    //m_pID_Text_Info->ShowScrollBar(true);

    m_listGroup.Clear();
    m_tabGroup.Clear();
    m_groupAll.Clear();
    m_groupAll.AddControl( m_pID_BUTTON_Tuodong );
    m_groupAll.AddControl( m_pID_PICTURE_Di );
    m_groupAll.AddControl( m_pID_BUTTON_ChatSet );
    m_groupAll.AddControl( m_pID_CHECKBOX_Channel1 );
    m_groupAll.AddControl( m_pID_CHECKBOX_Channel2 );
    m_groupAll.AddControl( m_pID_CHECKBOX_Channel3 );
    m_groupAll.AddControl( m_pID_CHECKBOX_Channel4 );
    m_groupAll.AddControl( m_pID_CHECKBOX_Channel5 );
    m_groupAll.AddControl( m_pID_CHECKBOX_Channel6 );
    m_groupAll.AddControl( m_pID_CHECKBOX_Channel7 );
    m_groupAll.AddControl( m_pID_CHECKBOX_Channel8 );
    m_groupAll.AddControl( m_pID_CHECKBOX_Channel9 );

	 m_groupAll.AddControl( m_pID_CHECKBOX_Channel10 ); //这个之前没加 怕数据对不上号 这里先加上
	 m_groupAll.AddControl( m_pID_CHECKBOX_Channel11 ); //lyh++

    m_groupAll.AddControl( m_pID_BUTTON_Clear );
    //m_groupAll.AddControl( m_pID_BUTTON_Action );
    m_groupAll.AddControl( m_pID_BUTTON_History );
    //m_groupAll.AddControl( m_pID_BUTTON_Horn );
    //m_groupAll.AddControl( m_pID_BUTTON_Save );
    m_groupAll.AddControl( m_pID_Text_Info );
    m_groupAll.AddControl( m_pID_Text_HornInfo );
    m_groupAll.AddControl( m_pID_BUTTON_Open );
    m_groupAll.SetVisible( true );
    
    m_groupMenu.Clear();
    m_groupMenu.AddControl( m_pID_BUTTON_Clear );
    m_groupMenu.AddControl( m_pID_BUTTON_History );
    m_groupMenu.AddControl( m_pID_BUTTON_ChatSet );
    m_groupMenu.AddControl( m_pID_PICTURE_OpenBg );
	m_groupMenu.AddControl( m_pID_BUTTON_Diaphaneity );
    m_groupMenu.SetVisible( false );

    m_listGroup.AddControl( m_pID_Text_Info );
    m_tabGroup.AddPage( m_pID_CHECKBOX_Channel1, &m_listGroup );
    m_tabGroup.AddPage( m_pID_CHECKBOX_Channel2, &m_listGroup );
    m_tabGroup.AddPage( m_pID_CHECKBOX_Channel3, &m_listGroup );
    m_tabGroup.AddPage( m_pID_CHECKBOX_Channel4, &m_listGroup );
    m_tabGroup.AddPage( m_pID_CHECKBOX_Channel5, &m_listGroup );
    m_tabGroup.AddPage( m_pID_CHECKBOX_Channel6, &m_listGroup );
    m_tabGroup.AddPage( m_pID_CHECKBOX_Channel7, &m_listGroup );
    m_tabGroup.AddPage( m_pID_CHECKBOX_Channel8, &m_listGroup );
    m_tabGroup.AddPage( m_pID_CHECKBOX_Channel9, &m_listGroup );
	m_tabGroup.AddPage( m_pID_CHECKBOX_Channel10, &m_listGroup );
	m_tabGroup.AddPage( m_pID_CHECKBOX_Channel11, &m_listGroup ); //lyh++
    m_tabGroup.TogglePage( m_pID_CHECKBOX_Channel1 );

    m_ChannelCtrl[0] = m_pID_CHECKBOX_Channel1;
    m_ChannelCtrl[1] = m_pID_CHECKBOX_Channel2;
    m_ChannelCtrl[2] = m_pID_CHECKBOX_Channel3;
    m_ChannelCtrl[3] = m_pID_CHECKBOX_Channel4;
    m_ChannelCtrl[4] = m_pID_CHECKBOX_Channel5;
    m_ChannelCtrl[5] = m_pID_CHECKBOX_Channel6;
    m_ChannelCtrl[6] = m_pID_CHECKBOX_Channel7;
    m_ChannelCtrl[7] = m_pID_CHECKBOX_Channel8;
    m_ChannelCtrl[8] = m_pID_CHECKBOX_Channel9;

	//lyh++ 下两行 10貌似没功能 
	m_ChannelCtrl[9] = m_pID_CHECKBOX_Channel10;
	m_ChannelCtrl[10] = m_pID_CHECKBOX_Channel11;

    m_pID_FRAME_chatInfoList->SetMsgProcFun(UIChatList_MsgProc);
    m_pID_FRAME_chatInfoList->SetMouseMoveOn( CUI_ID_FRAME_chatInfoList::FrameMouseEnter );
    m_pID_FRAME_chatInfoList->SetMouseMoveLevel( CUI_ID_FRAME_chatInfoList::FrameMouseLeave );

    m_pID_BUTTON_Tuodong->SetLButtonDownFun(UIChatList_TuodongOnLButtonDown);
    m_pID_BUTTON_Tuodong->SetLButtonUpFun(UIChatList_TuodongOnLButtonUp);
    m_pID_BUTTON_Tuodong->SetVisable(false);
    // 	m_pID_BUTTON_Clear->SetVisable(false);

    //m_nMinWidth = m_pID_PICTURE_Di->GetWidth() / ControlObject::GetSCALE(NULL);
    //m_nMinHeight = m_pID_PICTURE_Di->GetHeight() / ControlObject::GetSCALE(NULL);

    // 	m_pID_BUTTON_Low->SetVisable(false);

    s_CUI_ID_FRAME_chatInfoList.RefreshChannelVisible( false );

    SetVisable(false);
    m_pID_PICTURE_Di->SetVisable( true );

    RECT rcInfo,rcDi,rcFrame,rcHorn;

    rcDi = m_pID_PICTURE_Di->GetData()->m_rcRealSize;
    int nRecordX = GameSetting::Instance()->GetLevel( GameSetting::eGSC_ChatListWidth);
    //nRecordX += (rand()%3) *24;
    int nRecordY = GameSetting::Instance()->GetLevel( GameSetting::eGSC_ChatListHeight); 
    if (nRecordX > SCREEN_WIDTH * 0.7)
    {
        nRecordX = SCREEN_WIDTH * 0.7 - 1;
    }
    if (nRecordX < m_nMinWidth)
    {
        nRecordX = m_nMinWidth + 1;
    }
    if (nRecordY > SCREEN_HEIGHT * 0.7)
    {
        nRecordY = SCREEN_HEIGHT * 0.7 -1;
    }
    // 	if (nRecordY < m_nMinHeight)
    // 	{
    // 		nRecordY = m_nMinHeight + 1;
    // 	}
    int nDeltaX = nRecordX - (rcDi.right - rcDi.left);
    int nDeltaY = nRecordY - (rcDi.bottom - rcDi.top);

    rcInfo = m_pID_Text_Info->GetData()->m_rcRealSize;
    rcFrame = m_pID_FRAME_chatInfoList->GetData()->m_rcRealSize;
    rcHorn = m_pID_Text_HornInfo->GetData()->m_rcRealSize;

    {
        rcInfo.right += nDeltaX;
        rcDi.right += nDeltaX;
        rcFrame.right += nDeltaX;
        rcHorn.right += nDeltaX;
    }
    {
        rcInfo.bottom += nDeltaY;
        rcDi.bottom += nDeltaY;
        rcFrame.top -= nDeltaY;
    }
    int nDiHeight = rcDi.bottom - rcDi.top;
    int nDiWidth = rcDi.right - rcDi.left;
    if ((nDiHeight >= m_nMinHeight) && (nDiWidth >= m_nMinWidth))
    {
        m_pID_Text_Info->SetRealRect(&rcInfo);
        m_pID_FRAME_chatInfoList->SetRealRect(&rcFrame);
        m_pID_PICTURE_Di->SetRealRect(&rcDi);
        m_pID_Text_HornInfo->SetRealRect(&rcHorn);
    }
	m_pID_Text_HornInfo->SetMsgHoldup(false);
    m_bChatListChanged = false;

    s_CUI_ID_FRAME_ChatSet.LoadChannelConfig();

    SetRealAlpha( m_fAlpha );
    m_fAlphaSet = m_fAlpha;
    VisableBtns( false );
}

// 装载UI
bool CUI_ID_FRAME_chatInfoList::_LoadUI()
{
	guardfunc;
	DWORD dwResult = theUiManager.AddFrame( "data\\ui\\chat_list.meui", true,UI_Render_LayerSecond );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[UI\\chat_list.UI]失败")
			return false;
	}	
// 	else if ( dwResult != 1044/*文件版本号*/ )
// 	{
// 		MESSAGE_BOX("读取文件[UI\\chat_list.UI]与源代码版本不一样")
// 	}
	return DoControlConnect();
	unguard;
}
// 关连控件
bool CUI_ID_FRAME_chatInfoList::DoControlConnect()
{
	guardfunc;
	theUiManager.OnFrameRun( ID_FRAME_chatInfoList, s_CUI_ID_FRAME_chatInfoListOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_chatInfoList, s_CUI_ID_FRAME_chatInfoListOnFrameRender /*, true*/);
	theUiManager.OnListSelectChange( ID_FRAME_chatInfoList, ID_Text_Info, s_CUI_ID_FRAME_chatInfoListID_Text_InfoOnListSelectChange );
	theUiManager.OnButtonClick( ID_FRAME_chatInfoList, ID_BUTTON_Clear, s_CUI_ID_FRAME_chatInfoListID_BUTTON_ClearOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_chatInfoList, ID_BUTTON_Diaphaneity, s_CUI_ID_FRAME_chatInfoListID_BUTTON_DiaphaneityOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_chatInfoList, ID_BUTTON_ChatSet, s_CUI_ID_FRAME_chatInfoListID_BUTTON_ChatSetOnButtonClick );
    theUiManager.OnCheckBoxCheck( ID_FRAME_chatInfoList, ID_CHECKBOX_Channel1, s_CUI_ID_FRAME_chatInfoListID_CHECKBOX_Channel1OnCheckBoxCheck );
    theUiManager.OnCheckBoxCheck( ID_FRAME_chatInfoList, ID_CHECKBOX_Channel2, s_CUI_ID_FRAME_chatInfoListID_CHECKBOX_Channel2OnCheckBoxCheck );
    theUiManager.OnCheckBoxCheck( ID_FRAME_chatInfoList, ID_CHECKBOX_Channel3, s_CUI_ID_FRAME_chatInfoListID_CHECKBOX_Channel3OnCheckBoxCheck );
    theUiManager.OnCheckBoxCheck( ID_FRAME_chatInfoList, ID_CHECKBOX_Channel4, s_CUI_ID_FRAME_chatInfoListID_CHECKBOX_Channel4OnCheckBoxCheck );
    theUiManager.OnCheckBoxCheck( ID_FRAME_chatInfoList, ID_CHECKBOX_Channel5, s_CUI_ID_FRAME_chatInfoListID_CHECKBOX_Channel5OnCheckBoxCheck );
    theUiManager.OnCheckBoxCheck( ID_FRAME_chatInfoList, ID_CHECKBOX_Channel6, s_CUI_ID_FRAME_chatInfoListID_CHECKBOX_Channel6OnCheckBoxCheck );
    theUiManager.OnCheckBoxCheck( ID_FRAME_chatInfoList, ID_CHECKBOX_Channel7, s_CUI_ID_FRAME_chatInfoListID_CHECKBOX_Channel7OnCheckBoxCheck );
    theUiManager.OnCheckBoxCheck( ID_FRAME_chatInfoList, ID_CHECKBOX_Channel8, s_CUI_ID_FRAME_chatInfoListID_CHECKBOX_Channel8OnCheckBoxCheck );
    theUiManager.OnCheckBoxCheck( ID_FRAME_chatInfoList, ID_CHECKBOX_Channel9, s_CUI_ID_FRAME_chatInfoListID_CHECKBOX_Channel9OnCheckBoxCheck );
    //theUiManager.OnButtonClick( ID_FRAME_chatInfoList, ID_BUTTON_Action, s_CUI_ID_FRAME_chatInfoListID_BUTTON_ActionOnButtonClick );
    //theUiManager.OnButtonClick( ID_FRAME_chatInfoList, ID_BUTTON_Horn, s_CUI_ID_FRAME_chatInfoListID_BUTTON_HornOnButtonClick );
    theUiManager.OnButtonClick( ID_FRAME_chatInfoList, ID_BUTTON_History, s_CUI_ID_FRAME_chatInfoListID_BUTTON_HistoryOnButtonClick );
    //theUiManager.OnButtonClick( ID_FRAME_chatInfoList, ID_BUTTON_Save, s_CUI_ID_FRAME_chatInfoListID_BUTTON_SaveOnButtonClick );
    theUiManager.OnButtonClick( ID_FRAME_chatInfoList, ID_BUTTON_Low, s_CUI_ID_FRAME_chatInfoListID_BUTTON_LowOnButtonClick );
    theUiManager.OnButtonClick( ID_FRAME_chatInfoList, ID_BUTTON_Show, s_CUI_ID_FRAME_chatInfoListID_BUTTON_ShowOnButtonClick );
    theUiManager.OnButtonClick( ID_FRAME_chatInfoList, ID_BUTTON_Hide, s_CUI_ID_FRAME_chatInfoListID_BUTTON_HideOnButtonClick );
    theUiManager.OnButtonClick( ID_FRAME_chatInfoList, ID_BUTTON_Open, s_CUI_ID_FRAME_chatInfoListID_BUTTON_OpenOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_chatInfoList, ID_BUTTON_Low, s_CUI_ID_FRAME_chatInfoListID_BUTTON_LowOnButtonClick );
	theUiManager.OnCheckBoxCheck( ID_FRAME_chatInfoList, ID_CHECKBOX_Channel10, s_CUI_ID_FRAME_chatInfoListID_CHECKBOX_Channel10OnCheckBoxCheck );
	theUiManager.OnCheckBoxCheck( ID_FRAME_chatInfoList, ID_CHECKBOX_Channel11, s_CUI_ID_FRAME_chatInfoListID_CHECKBOX_Channel11OnCheckBoxCheck );

	m_pID_FRAME_chatInfoList = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_chatInfoList );
	m_pID_Text_Info = (ControlText*)theUiManager.FindControl( ID_FRAME_chatInfoList, ID_Text_Info );
	m_pID_BUTTON_Tuodong = (ControlButton*)theUiManager.FindControl( ID_FRAME_chatInfoList, ID_BUTTON_Tuodong );
	m_pID_PICTURE_Di = (ControlPicture*)theUiManager.FindControl( ID_FRAME_chatInfoList, ID_PICTURE_Di );
	m_pID_BUTTON_Clear = (ControlButton*)theUiManager.FindControl( ID_FRAME_chatInfoList, ID_BUTTON_Clear );
	m_pID_BUTTON_Diaphaneity = (ControlButton*)theUiManager.FindControl( ID_FRAME_chatInfoList, ID_BUTTON_Diaphaneity);
    m_pID_BUTTON_ChatSet = (ControlButton*)theUiManager.FindControl( ID_FRAME_chatInfoList, ID_BUTTON_ChatSet );
    m_pID_CHECKBOX_Channel1 = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_chatInfoList, ID_CHECKBOX_Channel1 );
    m_pID_CHECKBOX_Channel2 = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_chatInfoList, ID_CHECKBOX_Channel2 );
    m_pID_CHECKBOX_Channel3 = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_chatInfoList, ID_CHECKBOX_Channel3 );
    m_pID_CHECKBOX_Channel4 = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_chatInfoList, ID_CHECKBOX_Channel4 );
    m_pID_CHECKBOX_Channel5 = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_chatInfoList, ID_CHECKBOX_Channel5 );
    m_pID_CHECKBOX_Channel6 = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_chatInfoList, ID_CHECKBOX_Channel6 );
    m_pID_CHECKBOX_Channel7 = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_chatInfoList, ID_CHECKBOX_Channel7 );
    m_pID_CHECKBOX_Channel8 = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_chatInfoList, ID_CHECKBOX_Channel8 );
    m_pID_CHECKBOX_Channel9 = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_chatInfoList, ID_CHECKBOX_Channel9 );
	m_pID_CHECKBOX_Channel10 = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_chatInfoList, ID_CHECKBOX_Channel10 );
	m_pID_CHECKBOX_Channel11 = (ControlCheckBox*)theUiManager.FindControl( ID_FRAME_chatInfoList, ID_CHECKBOX_Channel11 );

    //m_pID_BUTTON_Action = (ControlButton*)theUiManager.FindControl( ID_FRAME_chatInfoList, ID_BUTTON_Action );
    m_pID_BUTTON_History = (ControlButton*)theUiManager.FindControl( ID_FRAME_chatInfoList, ID_BUTTON_History );
    //m_pID_BUTTON_Horn = (ControlButton*)theUiManager.FindControl( ID_FRAME_chatInfoList, ID_BUTTON_Horn );
    //m_pID_BUTTON_Save = (ControlButton*)theUiManager.FindControl( ID_FRAME_chatInfoList, ID_BUTTON_Save );
    m_pID_Text_Info = (ControlText*)theUiManager.FindControl( ID_FRAME_chatInfoList, ID_Text_Info );
    m_pID_Text_HornInfo = (ControlText*)theUiManager.FindControl( ID_FRAME_chatInfoList, ID_Text_HornInfo );
    m_pID_BUTTON_Low = (ControlButton*)theUiManager.FindControl( ID_FRAME_chatInfoList, ID_BUTTON_Low );
    m_pID_BUTTON_Show = (ControlButton*)theUiManager.FindControl( ID_FRAME_chatInfoList, ID_BUTTON_Show );
    m_pID_BUTTON_Hide = (ControlButton*)theUiManager.FindControl( ID_FRAME_chatInfoList, ID_BUTTON_Hide );
    m_pID_BUTTON_Open = (ControlButton*)theUiManager.FindControl( ID_FRAME_chatInfoList, ID_BUTTON_Open );
    m_pID_PICTURE_OpenBg = (ControlPicture*)theUiManager.FindControl( ID_FRAME_chatInfoList, ID_PICTURE_OpenBg );
	m_pID_PROGRESS_Low = (ControlProgress*)theUiManager.FindControl( ID_FRAME_chatInfoList, ID_PROGRESS_Low );
	m_pID_PROGRESS_Horn = (ControlProgress*)theUiManager.FindControl( ID_FRAME_chatInfoList, ID_PROGRESS_Horn);
	m_pID_PICTURE_SHOUT = (ControlPicture*)theUiManager.FindControl( ID_FRAME_chatInfoList, ID_PICTURE_SHOUT );

	assert(m_pID_CHECKBOX_Channel11);

    assert( m_pID_FRAME_chatInfoList );
    assert( m_pID_Text_Info );
	assert( m_pID_BUTTON_ChatSet );
	assert( m_pID_CHECKBOX_Channel1 );
	assert( m_pID_CHECKBOX_Channel2 );
	assert( m_pID_CHECKBOX_Channel3 );
	assert( m_pID_CHECKBOX_Channel4 );
	assert( m_pID_CHECKBOX_Channel5 );
    assert( m_pID_CHECKBOX_Channel6 );
    assert( m_pID_CHECKBOX_Channel7 );
    assert( m_pID_CHECKBOX_Channel8 );
    assert( m_pID_CHECKBOX_Channel9 );
    assert( m_pID_BUTTON_Show );
    assert( m_pID_BUTTON_Hide );
    assert( m_pID_BUTTON_Open );
    assert( m_pID_PICTURE_OpenBg );
	assert( m_pID_PROGRESS_Low );
	assert( m_pID_PROGRESS_Horn);
	assert( m_pID_CHECKBOX_Channel10 );
	assert( m_pID_PICTURE_SHOUT );

    m_pID_BUTTON_Show->SetVisable( false );
	m_pID_PROGRESS_Low->SetVisable( false );

	m_pID_FRAME_chatInfoList->SetMsgHoldup( false );

    _SetVisable( false );
	return true;
	unguard;
}

// 卸载UI
bool CUI_ID_FRAME_chatInfoList::_UnLoadUI()
{
	guardfunc;
	m_pID_FRAME_chatInfoList = NULL;
	m_pID_Text_Info = NULL;
	s_CUI_ChatInfoBox.ClearChatInfoList();
	m_pID_BUTTON_Tuodong = NULL;
	m_pID_PICTURE_Di = NULL;
	m_pID_BUTTON_Clear = NULL;
	m_pID_BUTTON_Diaphaneity = NULL;
	m_pID_CHECKBOX_Channel1 = NULL;
	m_pID_CHECKBOX_Channel2 = NULL;
	m_pID_CHECKBOX_Channel3 = NULL;
	m_pID_CHECKBOX_Channel4 = NULL;
	m_pID_CHECKBOX_Channel5 = NULL;
    m_pID_CHECKBOX_Channel6 = NULL;
    m_pID_CHECKBOX_Channel7 = NULL;
    m_pID_CHECKBOX_Channel8 = NULL;
    m_pID_CHECKBOX_Channel9 = NULL;
	m_pID_BUTTON_Low = NULL;
    m_pID_BUTTON_Show = NULL;
    m_pID_BUTTON_Hide = NULL;
    m_pID_BUTTON_Open = NULL;
    m_pID_PICTURE_OpenBg = NULL;
	m_pID_PROGRESS_Low = NULL;
	m_pID_CHECKBOX_Channel10 = NULL;
	m_pID_CHECKBOX_Channel11 = NULL;

	m_groupSet.Clear();
	return theUiManager.RemoveFrame( "data\\ui\\chat_list.meui" );
	unguard;
}
// 是否可视
bool CUI_ID_FRAME_chatInfoList::_IsVisable()
{
	guardfunc;
	if(!m_pID_FRAME_chatInfoList)
		return false;

	return m_pID_FRAME_chatInfoList->IsVisable();
	unguard;
}
// 设置是否可视
void CUI_ID_FRAME_chatInfoList::_SetVisable( const bool bVisable )
{
	guardfunc;
	if(!m_pID_FRAME_chatInfoList)
		return ;

	m_pID_FRAME_chatInfoList->SetVisable( bVisable );

	if (bVisable)
	{
		s_isShowBackground = GameSetting::Instance()->IsShowChatBackground();
		m_pID_PICTURE_Di->SetVisable(s_isShowBackground);
	}

	unguard;
}
void CUI_ID_FRAME_chatInfoList::RefreshChannelVisible( bool bVisible )
{
// 	for( int i = 0 ; i < MAX_CHANNELTAB_COUNT; ++ i )
// 	{
// 		if( m_ChannelCtrl[i] )
// 			m_ChannelCtrl[i]->SetVisable( false );
// 	}
	if( bVisible )
	{
		ChatChannelConfig::ChatChannelInfoList cciList = ChatChannelConfig::Instance()->GetChatChannelList();	
		for( int i = 0 ; i < cciList.size(); ++ i )
		{
			if( m_ChannelCtrl[i] )
			{
				m_ChannelCtrl[i]->SetVisable( true );
			}
		}
	}
}
void CUI_ID_FRAME_chatInfoList::RefreshChannel()
{
	if(!m_pID_FRAME_chatInfoList)
		return;

// 	for( int i = 0 ; i < MAX_CHANNELTAB_COUNT; ++ i )
// 	{
// 		if( m_ChannelCtrl[i] )
// 			m_ChannelCtrl[i]->SetVisable( false );
// 	}
	bool bSet = false;
	ChatChannelConfig::ChatChannelInfoList cciList = ChatChannelConfig::Instance()->GetChatChannelList();	
	for( int i = 0 ; i < cciList.size(); ++ i )
	{
		if( m_ChannelCtrl[i] )
		{
			m_ChannelCtrl[i]->SetVisable( true );
			// name 这里暂时去除，以后可能再添加
//			m_ChannelCtrl[i]->SetCaption( cciList[i].m_strChannelName.c_str() );
			// set type
			if( m_ChannelCtrl[i]->IsChecked() )
			{
				bSet = true;
				s_CUI_ChatInfoBox.SetChatChannelIndex( i );
				s_CUI_ChatInfoBox.Refresh(GetChannelStartIndex(i));
			}
		}
	}
	if( !bSet )
	{
		m_tabGroup.TogglePage( m_pID_CHECKBOX_Channel1 );
		s_CUI_ChatInfoBox.SetChatChannelIndex( 0 );
		s_CUI_ChatInfoBox.Refresh(GetChannelStartIndex(0));
	}

}

void CUI_ID_FRAME_chatInfoList::SetRealAlpha( float fAlpha )
{
    if( !IsUILoad() )
        return;

    if( m_pID_FRAME_chatInfoList )
    {
        fAlpha = fAlpha > 1.0f ? 1.0f : fAlpha;
        fAlpha = fAlpha < 0.0f ? 0.0f : fAlpha;
        m_fAlpha = fAlpha;
        SetTempAlpha( fAlpha );
    }
}

float CUI_ID_FRAME_chatInfoList::GetRealAlpha()
{
    return m_fAlpha;
}

void CUI_ID_FRAME_chatInfoList::SetTempAlpha( float fAlpha )
{
    if( !IsUILoad() )
        return;

    if( m_pID_FRAME_chatInfoList )
    {
        fAlpha = fAlpha > 1.0f ? 1.0f : fAlpha;
        fAlpha = fAlpha < 0.0f ? 0.0f : fAlpha;
        m_pID_Text_Info->SetAlpha( fAlpha );
		m_pID_FRAME_chatInfoList->SetAlpha( fAlpha );
		if (m_pID_PICTURE_SHOUT)
		{
			if ( fAlpha > 0.000001f)
				m_pID_PICTURE_SHOUT->SetAlpha( 0.8f );
			else
				m_pID_PICTURE_SHOUT->SetAlpha( fAlpha );
		}
    }
}

void CUI_ID_FRAME_chatInfoList::ShowAll( bool bShow )
{
    if( !IsUILoad() )
        return;

    m_groupAll.SetVisible( bShow );
    m_groupMenu.SetVisible( false );
    if( bShow )
    {
        //m_pID_FRAME_chatInfoList->SetMsgHoldup( true );
        if( m_pID_Text_Info->IsScrollBarVisable() )
            m_pID_BUTTON_Low->SetVisable( true );
        else
            m_pID_BUTTON_Low->SetVisable( false );
        m_pID_FRAME_chatInfoList->SetAlpha( 1.0f );

		if (m_pID_PICTURE_SHOUT)
			m_pID_PICTURE_SHOUT->SetAlpha( 1.0f );
    }
    else
    {
        m_pID_FRAME_chatInfoList->SetMsgHoldup( false );
        m_pID_BUTTON_Low->SetVisable( false );
        m_pID_FRAME_chatInfoList->SetAlpha( 0.0f );

		if (m_pID_PICTURE_SHOUT)
			m_pID_PICTURE_SHOUT->SetAlpha( 0.0f );
    }
}

void CUI_ID_FRAME_chatInfoList::SetButtonToudongVisable( bool b )
{
	if(m_pID_BUTTON_Tuodong)
		m_pID_BUTTON_Tuodong->SetVisable( b );
	else
		assert(false&&"ui error");
}

bool CUI_ID_FRAME_chatInfoList::IsButtonToudongVisable()
{
	if(m_pID_BUTTON_Tuodong)
		return m_pID_BUTTON_Tuodong->IsVisable();
	else
		assert(false&&"ui error");

	return false;
}


RECT CUI_ID_FRAME_chatInfoList::GetChatInfoListSize()
{
	if(m_pID_FRAME_chatInfoList)
		return m_pID_FRAME_chatInfoList->GetData()->m_rcRealSize;
	else
		assert(false&&"ui error");

	return RECT();
}

void CUI_ID_FRAME_chatInfoList::SetChatInfoListSize( RECT* rect )
{
	if(m_pID_FRAME_chatInfoList)
		m_pID_FRAME_chatInfoList->SetRealRect( rect );
	else
		assert(false&&"ui error");
}

bool CUI_ID_FRAME_chatInfoList::IsPtInObjectTuodong( INT x,INT y )
{
	if(m_pID_BUTTON_Tuodong)
		return m_pID_BUTTON_Tuodong->PtInObject(x, y);
	else
		assert(false&&"ui error");

	return false;
}

void CUI_ID_FRAME_chatInfoList::ListInfoClear()
{
	if(m_pID_Text_Info)
		m_pID_Text_Info->Clear();
// 	else
// 		assert(false&&"ui error");
}

void CUI_ID_FRAME_chatInfoList::HornInfoClear()
{
	if(m_pID_Text_HornInfo)
		m_pID_Text_HornInfo->Clear();
// 	else
// 		assert(false&&"ui error");
}


bool CUI_ID_FRAME_chatInfoList::IsListInfoVisable()
{
	if(m_pID_Text_Info)
		return m_pID_Text_Info->IsVisable();
	else
		assert(false&&"ui error");

	return false;
}

EKeyType CUI_ID_FRAME_chatInfoList::PtInHyberListInfo( INT x,INT y )
{
	EKeyType eRet = eKeyNormal;
	if(m_pID_Text_Info)
		eRet = m_pID_Text_Info->PtInHyber(x, y);

	if (eRet == eKeyNormal && m_pID_Text_HornInfo)
	{
		eRet = m_pID_Text_HornInfo->PtInHyber(x, y);
	}
	return eRet;
}

bool CUI_ID_FRAME_chatInfoList::IsPtInListObject( INT x,INT y )
{
	bool bRet = false;
	if(m_pID_FRAME_chatInfoList)
		bRet = m_pID_FRAME_chatInfoList->PtInObject(x, y, false);

// 	if (bRet == false && m_pID_Text_HornInfo)
// 	{
// 		bRet = m_pID_Text_HornInfo->PtInObject(x, y, false);
// 	}
	return bRet;

}

bool CUI_ID_FRAME_chatInfoList::IsInMaxFrame(int x, int y)
{
	RECT rc;
	bool bRet = false;
	m_pID_FRAME_chatInfoList->GetRealRect(&rc);

	int w = SCREEN_WIDTH * 0.7 - 1;
    int h = SCREEN_HEIGHT * 0.7 - 1;

	rc.right = rc.left + w + 20;
	rc.top = rc.bottom - h - 20;
	
	if ( (x >= rc.left && x <= rc.right && y >= rc.top && y <= rc.bottom)&& y > TEXT_LIMIT_SIZE_Y)
	{
		bRet = true;
	}

	//theMouseManager.SetCursor(MouseManager::Type_LeftDrag);
	/*if (theMouseManager.GetCursor() == MouseManager::Type_LeftDrag)
	{
		bRet = true;
	}*/
  return bRet;
}

RECT CUI_ID_FRAME_chatInfoList::GetPictureDi()
{
	if(m_pID_PICTURE_Di)
		return m_pID_PICTURE_Di->GetData()->m_rcRealSize;
	else
		assert(false&&"ui error");

	return RECT();
}

void CUI_ID_FRAME_chatInfoList::SetPictureDi( RECT* rect )
{
	if(m_pID_PICTURE_Di)
		m_pID_PICTURE_Di->SetRealRect(rect);
	else
		assert(false&&"ui error");

}

RECT CUI_ID_FRAME_chatInfoList::GetListInfoSize()
{
	if(m_pID_Text_Info)
		return m_pID_Text_Info->GetData()->m_rcRealSize;
	else
		assert(false&&"ui error");

	return RECT();
}
void CUI_ID_FRAME_chatInfoList::SetListInfoSize( RECT* rect )
{
	if(m_pID_Text_Info)
	{
		m_pID_Text_Info->SetRealRect(rect);
		ControlScrollBar* bar = m_pID_Text_Info->GetScrollBar();
		if ( bar )
		{
			RECT rc = bar->GetData()->m_rcRealSize;
			//rc.bottom -= 15;
			bar->SetRealRect(&rc);
		}
	}
	else
		assert(false&&"ui error");
}

RECT CUI_ID_FRAME_chatInfoList::GetHornInfoSize()
{
	if(m_pID_Text_HornInfo)
		return m_pID_Text_HornInfo->GetData()->m_rcRealSize;
	else
		assert(false&&"ui error");

	return RECT();

}

void CUI_ID_FRAME_chatInfoList::SetHornInfoSize( RECT* rect )
{
	if(m_pID_Text_HornInfo)
	{
		m_pID_Text_HornInfo->SetRealRect(rect);
	}
	else
		assert(false&&"ui error");
}

RECT CUI_ID_FRAME_chatInfoList::GetHornProgressSize()
{
	if(m_pID_PROGRESS_Horn)
		return m_pID_PROGRESS_Horn->GetData()->m_rcRealSize;
	else
		assert(false&&"ui error");

	return RECT();
}

void CUI_ID_FRAME_chatInfoList::SetHornProgressSize( RECT* rect )
{
	if(m_pID_PROGRESS_Horn)
		m_pID_PROGRESS_Horn->SetRealRect(rect);
	else
		assert(false&&"ui error");
}

void CUI_ID_FRAME_chatInfoList::FrameMouseEnter( ControlObject* pSender )
{
//     if( !s_CUI_ID_FRAME_chatInfoList.IsUILoad() )
//         return;
// 
//     s_CUI_ID_FRAME_chatInfoList.VisableBtns( true );
//     if( s_CUI_ID_FRAME_chatInfoList.GetRealAlpha() < 0.01f )
//     {
//         s_CUI_ID_FRAME_chatInfoList.SetTempAlpha( 0.20f );
//     }
}

void CUI_ID_FRAME_chatInfoList::FrameMouseLeave( ControlObject* pSender )
{
//     if( !s_CUI_ID_FRAME_chatInfoList.IsUILoad() )
//         return;
// 
//     s_CUI_ID_FRAME_chatInfoList.VisableBtns( false );
// 	s_CUI_ID_FRAME_chatInfoList.ShowGroupMenu(false);
//     if( s_CUI_ID_FRAME_chatInfoList.GetRealAlpha() < 0.01f )
//     {
//         s_CUI_ID_FRAME_chatInfoList.SetTempAlpha( s_CUI_ID_FRAME_chatInfoList.GetRealAlpha() );
//     }
}

void CUI_ID_FRAME_chatInfoList::VisableBtns( bool bVisable )
{
    if( !IsUILoad() )
        return;

    m_pID_BUTTON_Open->SetVisable( bVisable );
    m_pID_CHECKBOX_Channel1->SetVisable( bVisable );
    m_pID_CHECKBOX_Channel2->SetVisable( bVisable );
    m_pID_CHECKBOX_Channel3->SetVisable( bVisable );
    m_pID_CHECKBOX_Channel4->SetVisable( bVisable );
    m_pID_CHECKBOX_Channel5->SetVisable( bVisable );
    m_pID_CHECKBOX_Channel6->SetVisable( bVisable );
    m_pID_CHECKBOX_Channel7->SetVisable( bVisable );
    m_pID_CHECKBOX_Channel8->SetVisable( bVisable );
    m_pID_CHECKBOX_Channel9->SetVisable( bVisable );
	m_pID_CHECKBOX_Channel10->SetVisable( bVisable );
	m_pID_CHECKBOX_Channel11->SetVisable(bVisable); // lyh++
}

void CUI_ID_FRAME_chatInfoList::ResetDevice()
{
	if( !IsUILoad() )
		return;

	RECT rc;
	m_pID_Text_Info->GetRealRect( &rc );
	s_CUI_ID_FRAME_chatInfoList.SetOldMousePosX( rc.right );
	s_CUI_ID_FRAME_chatInfoList.SetOldMousePosY( rc.top );

	RECT rcMin = s_CUI_ID_FRAME_chatInfoList.GetPictureDi();

	// 宽度重置
	if( rc.right < rcMin.left + GetMinWidth() )
	{
		rc.right = rcMin.left + GetMinWidth();
	}
	else if( rc.right > TEXT_LIMIT_SIZE_X )
	{
		rc.right = TEXT_LIMIT_SIZE_X;
	}

	// 高度重置
	if( rc.bottom < rcMin.top + GetMinHeight() )
	{
		rc.top = rcMin.top + GetMinHeight();
	}
	else if( rc.top < TEXT_LIMIT_SIZE_Y )
	{
		rc.top = TEXT_LIMIT_SIZE_Y;
	}

	CUI_ID_FRAME_chatInfoList::ChangeSizeToPoint( rc.right, rc.top, true );
}
