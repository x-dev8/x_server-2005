/********************************************************************
Created by UIEditor.exe
FileName: E:\Code\RunTime\CLIENT\Data\UI\SelectBox.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "SelectBox.h"
#include "FuncPerformanceLog.h"
#include "UIBase.h"
#include <string>
#include "NpcChatDialogBox.h"
#include "../color_config.h"
#include "PlayerMgr.h"
#include "PlayerRole.h"
#include "ui/Target.h"
#include "GameMain.h"
#include "Player.h"

extern CHeroGame theHeroGame;

#define SET_QUEST_FLAG(index)												\
	if (theQuestManager.IsQuestDone(pSelectBox->m_questState[i  ]))				\
	m_vecY_Wenhao[index]->SetVisable(true);								\
	else if (theQuestManager.IsQuestActive(pSelectBox->m_questState[i ]))		\
	m_vecW_Wenhao[index]->SetVisable(true);								\
	else																	\
	m_vecY_Gantanhao[index]->SetVisable(true);

CUI_SelectBox s_CUI_ID_FRAME_SelectBox;
MAP_FRAME_RUN( s_CUI_ID_FRAME_SelectBox, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_SelectBox, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SelectBox, ID_BUTTON_OKOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SelectBox, ID_BUTTON_CloseOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SelectBox, ID_BUTTON_CancelOnButtonClick )
MAP_LIST_SELECT_CHANGE_CALLBACK( s_CUI_ID_FRAME_SelectBox, ID_LIST_SELECTOnListDBClick )
MAP_TEXT_HYBER_CLICKBACK( s_CUI_ID_FRAME_SelectBox, ID_TEXT_HyberClick )
CUI_SelectBox::CUI_SelectBox()
{
	// SGuildMember
	m_pID_SelectBox = NULL;
	m_pID_TEXT_CAPTION = NULL;
	m_pID_LIST_SELECT = NULL;
	m_pID_BUTTON_OK = NULL;
	m_pID_BUTTON_CLOSE = NULL;

	m_pID_TEXT_Info = NULL;

	m_pID_PICTURE_Y_Gantanhao1 = NULL;
	m_pID_PICTURE_Y_Gantanhao2 = NULL;
	m_pID_PICTURE_Y_Gantanhao3 = NULL;
	m_pID_PICTURE_Y_Gantanhao4 = NULL;
	m_pID_PICTURE_Y_Gantanhao5 = NULL;
	m_pID_PICTURE_Y_Wenhao1 = NULL;
	m_pID_PICTURE_Y_Wenhao2 = NULL;
	m_pID_PICTURE_Y_Wenhao3 = NULL;
	m_pID_PICTURE_Y_Wenhao4 = NULL;
	m_pID_PICTURE_Y_Wenhao5 = NULL;
	m_pID_PICTURE_W_Gantanhao1 = NULL;
	m_pID_PICTURE_W_Gantanhao2 = NULL;
	m_pID_PICTURE_W_Gantanhao3 = NULL;
	m_pID_PICTURE_W_Gantanhao4 = NULL;
	m_pID_PICTURE_W_Gantanhao5 = NULL;
	m_pID_PICTURE_W_Wenhao1 = NULL;
	m_pID_PICTURE_W_Wenhao2 = NULL;
	m_pID_PICTURE_W_Wenhao3 = NULL;
	m_pID_PICTURE_W_Wenhao4 = NULL;
	m_pID_PICTURE_W_Wenhao5 = NULL;
	m_bCancelScript = true;
	m_pID_PICTURE_NpcHead = NULL;
}

void CUI_SelectBox::TextInfo_HyberClick( ControlObject* pSender, const char* szData )
{
	if( szData )
		NpcCoord::getInstance()->clickHyberToMiniMap(szData);
}
// Frame
bool CUI_SelectBox::OnFrameRun()
{
	guardfunc;
	return true;
	unguard;
}
bool CUI_SelectBox::OnFrameRender()
{
	guardfunc;
	return true;
	unguard;
}
// List
void CUI_SelectBox::ID_LIST_SELECTOnListDBClick( ControlObject* pSender, ControlList::S_List* pItem )
{
	guardfunc;
	if( !m_pID_SelectBox )
		return;

	ID_BUTTON_OKOnButtonClick( pSender );
	unguard;
}

bool CUI_SelectBox::PopSelectBox()
{
	if ( m_vtSelectBox.size() <= 0 )
		return false;
	m_vtSelectBox.erase( m_vtSelectBox.begin() );
	return true;
}
bool CUI_SelectBox::ID_BUTTON_CloseOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_SelectBox )
		return false;
	m_bCancelScript = true;
	SetVisable(false);
// 	s_CUI_ID_FRAME_NpcChatDialogBox.CancelScript();
	return true;
}
 bool CUI_SelectBox::ID_BUTTON_CancelOnButtonClick( ControlObject* pSender )
 {
 	if( !m_pID_SelectBox )
 		return false;
	m_bCancelScript = true;
	SetVisable(false);
//  	s_CUI_ID_FRAME_NpcChatDialogBox.CancelScript();
 	return true;
 }
//text hyber click
void CUI_SelectBox::ID_TEXT_HyberClick(ControlObject* pSender, const char* szData)
{
	guardfunc;
	if( !m_pID_SelectBox )
		return;
	//目前超链接 只用于小地图有处理 别的还没有 以后增加功能再说 这里只是小地图npc指引的处理  。。。
	NpcCoord::getInstance()->clickHyberToMiniMap(szData);
	unguard;
}
// Button
bool CUI_SelectBox::ID_BUTTON_OKOnButtonClick( ControlObject* pSender )
{
	guardfunc;
	if( !m_pID_SelectBox )
		return false;
	if( !m_pID_SelectBox )
		return true;

	if ( m_pCurCallbackFun )
	{
		// 判断是否操作成功，不成功则不关闭界面
		bool bCanClose = true;
		bCanClose = m_pCurCallbackFun( m_pID_LIST_SELECT->GetCurSelIndex(), m_pID_LIST_SELECT->GetCurSelItem() );
		if( !bCanClose )
			return true;
	}
// 	PopSelectBox();

	bool oldRet = s_CUI_ID_FRAME_NpcChatDialogBox.GetScriptCanceled();
	s_CUI_ID_FRAME_NpcChatDialogBox.SetScriptCanceled(true);
	m_bCancelScript = false;
	SetVisable(false);
	Refeash();
	m_bCancelScript = true;
	s_CUI_ID_FRAME_NpcChatDialogBox.SetScriptCanceled(oldRet);
	return true;
	unguard;
}

// 装载UI
bool CUI_SelectBox::_LoadUI()
{
	guardfunc;
	DWORD dwResult = theUiManager.AddFrame( "data\\ui\\SelectBox.meui", false, UI_Render_LayerThree);
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[UI\\SelectBox.UI]失败")
			return false;
	}
	return DoControlConnect();
	unguard;
}

void CUI_SelectBox::ID_SelectBox_onVisibleChanged( ControlObject* pObject )
{
	if( !s_CUI_ID_FRAME_SelectBox.GetFrame() )
		return;

	if ( !pObject->IsVisable() )
	{
// 		if ( !s_CUI_ID_FRAME_NpcChatDialogBox.GetScriptCanceled() )
		if(s_CUI_ID_FRAME_SelectBox.m_bCancelScript || !s_CUI_ID_FRAME_NpcChatDialogBox.GetScriptCanceled())
			s_CUI_ID_FRAME_NpcChatDialogBox.CancelScript();
		s_CUI_ID_FRAME_SelectBox.PopSelectBox();
	}
	else
	{
		s_CUI_ID_FRAME_SelectBox.RetrieveNpcPic();
	}
}

// 关连控件
bool CUI_SelectBox::DoControlConnect()
{
	guardfunc;
	theUiManager.OnFrameRun( ID_SelectBox, s_CUI_ID_FRAME_SelectBoxOnFrameRun );
	theUiManager.OnFrameRender( ID_SelectBox, s_CUI_ID_FRAME_SelectBoxOnFrameRender );
	theUiManager.OnListLDBClick( ID_SelectBox, ID_LIST_SELECT, s_CUI_ID_FRAME_SelectBoxID_LIST_SELECTOnListDBClick );
	theUiManager.OnButtonClick( ID_SelectBox, ID_BUTTON_OK, s_CUI_ID_FRAME_SelectBoxID_BUTTON_OKOnButtonClick );
	theUiManager.OnButtonClick( ID_SelectBox, ID_BUTTON_CLOSE, s_CUI_ID_FRAME_SelectBoxID_BUTTON_CloseOnButtonClick );
	theUiManager.OnButtonClick( ID_SelectBox, ID_BUTTON_Cancel, s_CUI_ID_FRAME_SelectBoxID_BUTTON_CancelOnButtonClick );
	theUiManager.OnTextHyberClick( ID_SelectBox, ID_TEXT_Info, s_CUI_ID_FRAME_SelectBoxID_TEXT_HyberClick);

	m_pID_SelectBox = (ControlFrame*)theUiManager.FindFrame( ID_SelectBox );
	m_pID_TEXT_CAPTION = (ControlText*)theUiManager.FindControl( ID_SelectBox, ID_TEXT_CAPTION );
	m_pID_LIST_SELECT = (ControlList*)theUiManager.FindControl( ID_SelectBox, ID_LIST_SELECT );
	m_pID_BUTTON_OK = (ControlButton*)theUiManager.FindControl( ID_SelectBox, ID_BUTTON_OK );
	m_pID_BUTTON_CLOSE= (ControlButton*)theUiManager.FindControl( ID_SelectBox, ID_BUTTON_CLOSE );
	m_pID_TEXT_Info = (ControlText*)theUiManager.FindControl( ID_SelectBox, ID_TEXT_Info );
	m_pID_PICTURE_Y_Gantanhao1 = (ControlPicture*)theUiManager.FindControl( ID_SelectBox, ID_PICTURE_Y_Gantanhao1 );
	m_pID_PICTURE_Y_Gantanhao2 = (ControlPicture*)theUiManager.FindControl( ID_SelectBox, ID_PICTURE_Y_Gantanhao2 );
	m_pID_PICTURE_Y_Gantanhao3 = (ControlPicture*)theUiManager.FindControl( ID_SelectBox, ID_PICTURE_Y_Gantanhao3 );
	m_pID_PICTURE_Y_Gantanhao4 = (ControlPicture*)theUiManager.FindControl( ID_SelectBox, ID_PICTURE_Y_Gantanhao4 );
	m_pID_PICTURE_Y_Gantanhao5 = (ControlPicture*)theUiManager.FindControl( ID_SelectBox, ID_PICTURE_Y_Gantanhao5 );
	m_pID_PICTURE_Y_Wenhao1 = (ControlPicture*)theUiManager.FindControl( ID_SelectBox, ID_PICTURE_Y_Wenhao1 );
	m_pID_PICTURE_Y_Wenhao2 = (ControlPicture*)theUiManager.FindControl( ID_SelectBox, ID_PICTURE_Y_Wenhao2 );
	m_pID_PICTURE_Y_Wenhao3 = (ControlPicture*)theUiManager.FindControl( ID_SelectBox, ID_PICTURE_Y_Wenhao3 );
	m_pID_PICTURE_Y_Wenhao4 = (ControlPicture*)theUiManager.FindControl( ID_SelectBox, ID_PICTURE_Y_Wenhao4 );
	m_pID_PICTURE_Y_Wenhao5 = (ControlPicture*)theUiManager.FindControl( ID_SelectBox, ID_PICTURE_Y_Wenhao5 );
	m_pID_PICTURE_W_Gantanhao1 = (ControlPicture*)theUiManager.FindControl( ID_SelectBox, ID_PICTURE_W_Gantanhao1 );
	m_pID_PICTURE_W_Gantanhao2 = (ControlPicture*)theUiManager.FindControl( ID_SelectBox, ID_PICTURE_W_Gantanhao2 );
	m_pID_PICTURE_W_Gantanhao3 = (ControlPicture*)theUiManager.FindControl( ID_SelectBox, ID_PICTURE_W_Gantanhao3 );
	m_pID_PICTURE_W_Gantanhao4 = (ControlPicture*)theUiManager.FindControl( ID_SelectBox, ID_PICTURE_W_Gantanhao4 );
	m_pID_PICTURE_W_Gantanhao5 = (ControlPicture*)theUiManager.FindControl( ID_SelectBox, ID_PICTURE_W_Gantanhao5 );
	m_pID_PICTURE_W_Wenhao1 = (ControlPicture*)theUiManager.FindControl( ID_SelectBox, ID_PICTURE_W_Wenhao1 );
	m_pID_PICTURE_W_Wenhao2 = (ControlPicture*)theUiManager.FindControl( ID_SelectBox, ID_PICTURE_W_Wenhao2 );
	m_pID_PICTURE_W_Wenhao3 = (ControlPicture*)theUiManager.FindControl( ID_SelectBox, ID_PICTURE_W_Wenhao3 );
	m_pID_PICTURE_W_Wenhao4 = (ControlPicture*)theUiManager.FindControl( ID_SelectBox, ID_PICTURE_W_Wenhao4 );
	m_pID_PICTURE_W_Wenhao5 = (ControlPicture*)theUiManager.FindControl( ID_SelectBox, ID_PICTURE_W_Wenhao5 );
	m_pID_PICTURE_NpcHead = (ControlPicture*)theUiManager.FindControl( ID_SelectBox, ID_PICTURE_NpcHead );

	m_flagGroup.AddControl(m_pID_PICTURE_Y_Gantanhao1);
	m_flagGroup.AddControl(m_pID_PICTURE_Y_Gantanhao2);
	m_flagGroup.AddControl(m_pID_PICTURE_Y_Gantanhao3);
	m_flagGroup.AddControl(m_pID_PICTURE_Y_Gantanhao4);
	m_flagGroup.AddControl(m_pID_PICTURE_Y_Gantanhao5);
	m_flagGroup.AddControl(m_pID_PICTURE_Y_Wenhao1);
	m_flagGroup.AddControl(m_pID_PICTURE_Y_Wenhao2);
	m_flagGroup.AddControl(m_pID_PICTURE_Y_Wenhao3);
	m_flagGroup.AddControl(m_pID_PICTURE_Y_Wenhao4);
	m_flagGroup.AddControl(m_pID_PICTURE_Y_Wenhao5);
	m_flagGroup.AddControl(m_pID_PICTURE_W_Gantanhao1);
	m_flagGroup.AddControl(m_pID_PICTURE_W_Gantanhao2);
	m_flagGroup.AddControl(m_pID_PICTURE_W_Gantanhao3);
	m_flagGroup.AddControl(m_pID_PICTURE_W_Gantanhao4);
	m_flagGroup.AddControl(m_pID_PICTURE_W_Gantanhao5);
	m_flagGroup.AddControl(m_pID_PICTURE_W_Wenhao1);
	m_flagGroup.AddControl(m_pID_PICTURE_W_Wenhao2);
	m_flagGroup.AddControl(m_pID_PICTURE_W_Wenhao3);
	m_flagGroup.AddControl(m_pID_PICTURE_W_Wenhao4);
	m_flagGroup.AddControl(m_pID_PICTURE_W_Wenhao5);
	m_flagGroup.SetVisible(false);

	assert( m_pID_SelectBox );
	m_pID_SelectBox->SetVisable(false);
	m_pID_SelectBox->SetMsgProcFun( frame_BackmsgClick );//zjj add[10.23]
	m_pID_SelectBox->SetOnVisibleChangedFun( CUI_SelectBox::ID_SelectBox_onVisibleChanged );
	assert( m_pID_TEXT_CAPTION );
	assert( m_pID_LIST_SELECT );
	assert( m_pID_BUTTON_OK );
	assert( m_pID_BUTTON_CLOSE );
	assert( m_pID_TEXT_Info );

	m_vecY_Gantanhao.clear();
	m_vecY_Wenhao.clear();
	m_vecW_Gantanhao.clear();
	m_vecW_Wenhao.clear();

	m_pID_TEXT_Info->SetColUrl(Color_Config.getColor((ColorConfigure)(CC_PathFindLinker)));
	m_pID_TEXT_Info->setShowTip(true);
// 	m_pID_TEXT_Info->SetHyberClickFun(TextInfo_HyberClick);

	char buf[64];
	int index = 1;
	sprintf(buf, "ID_PICTURE_Y_Gantanhao%d", index);
	ControlPicture* pPic = (ControlPicture*)theUiManager.FindControl( ID_SelectBox, buf );
	while (pPic)
	{
		m_vecY_Gantanhao.push_back(pPic);

		sprintf(buf, "ID_PICTURE_Y_Wenhao%d", index);
		pPic = (ControlPicture*)theUiManager.FindControl( ID_SelectBox, buf );
		m_vecY_Wenhao.push_back(pPic);

		sprintf(buf, "ID_PICTURE_W_Gantanhao%d", index);
		pPic = (ControlPicture*)theUiManager.FindControl( ID_SelectBox, buf );
		m_vecW_Gantanhao.push_back(pPic);

		sprintf(buf, "ID_PICTURE_W_Wenhao%d", index);
		pPic = (ControlPicture*)theUiManager.FindControl( ID_SelectBox, buf );
		m_vecW_Wenhao.push_back(pPic);

		++index;
		sprintf(buf, "ID_PICTURE_Y_Gantanhao%d", index);
		pPic = (ControlPicture*)theUiManager.FindControl( ID_SelectBox, buf );
	}

	USE_SCRIPT( eUI_OBJECT_SelectBox, this );

	m_nNpcId = -1;

	return true;
	unguard;
}
void CUI_SelectBox::RetrieveNpcPic()
{
	if( !m_pID_SelectBox )
		return;

	CPlayer* pPlayer = NULL;
	if( m_nNpcId >= 0 )
		pPlayer = theHeroGame.GetPlayerMgr()->FindByID( m_nNpcId );
	if( !pPlayer )
	{
		m_pID_PICTURE_NpcHead->SetVisable(false);
		return;
	}

	MexResMgr::Record* record = GetMexResMgr()->GetRecord(pPlayer->GetModelId());
	if (record && m_pID_PICTURE_NpcHead && !pPlayer->IsPlayer())
	{
		m_pID_PICTURE_NpcHead->SetVisable(true);
		m_pID_PICTURE_NpcHead->SetPicName( record->headPicture.c_str() );
	}
	else
		m_pID_PICTURE_NpcHead->SetVisable(false);
}
// 卸载UI
bool CUI_SelectBox::_UnLoadUI()
{
	guardfunc;
	CLOSE_SCRIPT( eUI_OBJECT_SelectBox );
	m_flagGroup.Clear();
	m_pID_SelectBox = NULL;
	m_pID_TEXT_CAPTION = NULL;
	m_pID_LIST_SELECT = NULL;
	m_pID_BUTTON_OK = NULL;
	m_pID_BUTTON_CLOSE = NULL;
	m_pID_TEXT_Info = NULL;
	m_pID_PICTURE_Y_Gantanhao1 = NULL;
	m_pID_PICTURE_Y_Gantanhao2 = NULL;
	m_pID_PICTURE_Y_Gantanhao3 = NULL;
	m_pID_PICTURE_Y_Gantanhao4 = NULL;
	m_pID_PICTURE_Y_Gantanhao5 = NULL;
	m_pID_PICTURE_Y_Wenhao1 = NULL;
	m_pID_PICTURE_Y_Wenhao2 = NULL;
	m_pID_PICTURE_Y_Wenhao3 = NULL;
	m_pID_PICTURE_Y_Wenhao4 = NULL;
	m_pID_PICTURE_Y_Wenhao5 = NULL;
	m_pID_PICTURE_W_Gantanhao1 = NULL;
	m_pID_PICTURE_W_Gantanhao2 = NULL;
	m_pID_PICTURE_W_Gantanhao3 = NULL;
	m_pID_PICTURE_W_Gantanhao4 = NULL;
	m_pID_PICTURE_W_Gantanhao5 = NULL;
	m_pID_PICTURE_W_Wenhao1 = NULL;
	m_pID_PICTURE_W_Wenhao2 = NULL;
	m_pID_PICTURE_W_Wenhao3 = NULL;
	m_pID_PICTURE_W_Wenhao4 = NULL;
	m_pID_PICTURE_W_Wenhao5 = NULL;
	m_pID_PICTURE_NpcHead = NULL;
	return theUiManager.RemoveFrame( "data\\ui\\SelectBox.meui" );
	unguard;
}
// 是否可视
bool CUI_SelectBox::_IsVisable()
{
	guardfunc;
	if( !m_pID_SelectBox )
		return false;
	return m_pID_SelectBox->IsVisable();
	unguard;
}
// 设置是否可视
void CUI_SelectBox::_SetVisable( const bool bVisable)
{
	guardfunc;
	if( !m_pID_SelectBox )
		return;
	m_pID_SelectBox->SetVisable( bVisable );

	if ( bVisable == false )
	{
// 		PopSelectBox();
	}
	else
	{
		CPlayer* pNpc = theHeroGame.GetPlayerMgr()->FindByID( m_nNpcId );
		if (pNpc && pNpc->IsShowChatPaoPao())
		{
			pNpc->ClearChatPaoPao();
		}

	}
	unguard;
}

void CUI_SelectBox::Show( const char* szText, const ControlList::S_List* pItem, const int nItemCount,
						const char* szCaption, const bool bModal,
						const funCallbackFun pFun, const int nQuestCount,
						const int* questInfos )
{
	guardfunc;
	SetVisable( true );
	if( !pItem || nItemCount <= 0 || nItemCount > MAX_SELECT_ITEM )
	{
		return;
	}
	S_SelectBox stSelectBox;
	stSelectBox.m_strInfo = szText;
	stSelectBox.m_strCaption = szCaption?szCaption:"";
	stSelectBox.m_pCallbackFun = pFun;
	stSelectBox.m_bModal = bModal;
	memcpy( stSelectBox.m_stItem, pItem, sizeof(ControlList::S_List)*nItemCount );
	stSelectBox.m_nItemCount = nItemCount;
	if (nQuestCount>0 && nQuestCount <= MAX_SELECT_ITEM )
	{
		memcpy( stSelectBox.m_questState, questInfos, sizeof(int) * nQuestCount );
		stSelectBox.m_nQuestCount = nQuestCount;
	}

	m_vtSelectBox.push_back( stSelectBox );
	Refeash();
	unguard;
}

void CUI_SelectBox::Refeash()
{
	guardfunc;
	if( !m_pID_SelectBox )
		return;

	if ( m_vtSelectBox.size() > 0 )
	{
		SetVisable( true );
		S_SelectBox *pSelectBox;
		pSelectBox = &m_vtSelectBox[0];
		std::vector<UiCallbackDataBase*> CallBackDataArr;
		NpcCoord::getInstance()->addNpcHyberForText(pSelectBox->m_strInfo,NpcCoord::eMapId,-1,m_nNpcId,&CallBackDataArr);
		m_pID_TEXT_Info->SetText( pSelectBox->m_strInfo, Color_Config.getColor(CC_NPCDIALOG_INFO),&CallBackDataArr );
		*m_pID_TEXT_CAPTION = pSelectBox->m_strCaption;
		m_pCurCallbackFun = pSelectBox->m_pCallbackFun;
		m_pID_LIST_SELECT->Clear();
		m_pID_LIST_SELECT->AddArrayItem( pSelectBox->m_stItem, pSelectBox->m_nItemCount, false );
		if (pSelectBox->m_nItemCount > 0)
		{
			m_pID_LIST_SELECT->SetCurSelIndex(0);
		}

		for (int i = 0; i < m_vecW_Gantanhao.size(); ++i)
		{
			m_vecY_Gantanhao[i]->SetVisable(false);
			m_vecY_Wenhao[i]->SetVisable(false);
			m_vecW_Gantanhao[i]->SetVisable(false);
			m_vecW_Wenhao[i]->SetVisable(false);
		}

		for (int i = 0; i < pSelectBox->m_nItemCount; ++i)
		{
			if (pSelectBox->m_stItem[i].m_nID < dr_MinQuestId)
			{
				continue;
			}
			CPlayerRole::QuestInfo* pInfo = thePlayerRole.FindQuestInfoById( pSelectBox->m_stItem[i].m_nID );
			if( !pInfo )
				continue;

			SET_QUEST_FLAG(i%m_vecY_Gantanhao.size())
		}

	}
// 	else
// 	{
// 		SetVisable( false );
// 	}
	theUiManager.Compositor();
	unguard;
}
//触发ENTER的消息事件
bool CUI_SelectBox::frame_BackmsgClick( UINT msg, WPARAM wParam, LPARAM lParam, bool bMsgUsed )
{
	guardfunc;
	if(!s_CUI_ID_FRAME_SelectBox.IsVisable())
	{
		return false;
	}
	switch( msg ) 
	{
	case WM_KEYUP:
		{
			if( wParam == VK_RETURN )
			{
				s_CUI_ID_FRAME_SelectBox.ID_BUTTON_OKOnButtonClick(NULL);
				return true;
			}
		}
		break;
	}
	return false;

	unguard;
}

void CUI_SelectBox::SetNpc( int nId )
{
	m_nNpcId = nId;
}