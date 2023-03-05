/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\yang.xu\桌面\SuAnimalMenu.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "SuAnimalMenu.h"
#include "SuAnimal.h"
#include "ItemDetail.h"
#include "Player.h"
#include "PlayerMgr.h"
#include "GlobalDef.h"
#include "MessageDefine.h"
#include "NetworkInput.h"
#include "SeeSuAnimal.h"
#include "SelfRbtnMenu.h"
#include "RbtnMenu.h"
#include "PetRbtnMenu.h"
#include "FriendDlgRight.h"

CUI_ID_FRAME_SuAnimalMenu s_CUI_ID_FRAME_SuAnimalMenu;
MAP_FRAME_RUN( s_CUI_ID_FRAME_SuAnimalMenu, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_SuAnimalMenu, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimalMenu, ID_BUTTON_LookOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimalMenu, ID_BUTTON_XiuXiOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimalMenu, ID_BUTTON_CureOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_SuAnimalMenu, ID_BUTTON_FeedOnButtonClick )
CUI_ID_FRAME_SuAnimalMenu::CUI_ID_FRAME_SuAnimalMenu()
{
	// Member
	m_pID_FRAME_SuAnimalMenu = NULL;
	m_pID_BUTTON_Look = NULL;
	m_pID_BUTTON_XiuXi = NULL;
	m_pID_BUTTON_Cure = NULL;
	m_pID_BUTTON_Feed = NULL;
	m_IsLookOtherPet = false;

}
// Frame
bool CUI_ID_FRAME_SuAnimalMenu::OnFrameRun()
{
	//每帧界面逻辑更新，需要先判断界面是否可见，把下面代码打开
	//if( IsVisable() )
	//{
	//}
	return true;
}
bool CUI_ID_FRAME_SuAnimalMenu::OnFrameRender()
{
	return true;
}
// Button
bool CUI_ID_FRAME_SuAnimalMenu::ID_BUTTON_LookOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_SuAnimalMenu )
		return false;
	if (m_IsLookOtherPet)
	{
			MsgViewActivePet pMsg;
			pMsg.masterId = GetPlayerID();
			GettheNetworkInput().SendMsg(&pMsg);
// 		s_CUI_ID_FRAME_SeeSuAnimal._SetVisable(true);
// 		s_CUI_ID_FRAME_SeeSuAnimal.SetPetItem(*thePlayerRole.GetActivedPet());//测试代码
	}
	else
	{
		s_CUI_ID_FRAME_SuAnimal.SetVisable(true);
		s_CUI_ID_FRAME_SuAnimal.LookPet(GetCurrentPetIndex());
	}
	s_CUI_ID_FRAME_SuAnimalMenu.SetVisable(false);
	return true;
}
// Button
bool CUI_ID_FRAME_SuAnimalMenu::ID_BUTTON_XiuXiOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_SuAnimalMenu )
		return false;
	//UseItem(ItemDefine::EPetFunc_AddLife);
	if (thePlayerRole.GetActivedPet() != NULL)
		s_CUI_ID_FRAME_SuAnimal.ActivePet(*(thePlayerRole.GetActivedPet()),thePlayerRole.GetActivedPetIndex());
	s_CUI_ID_FRAME_SuAnimalMenu.SetVisable(false);
	return true;
}
// Button
bool CUI_ID_FRAME_SuAnimalMenu::ID_BUTTON_CureOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_SuAnimalMenu )
		return false;
	UseItem(ItemDefine::EPetFunc_RestoreHP);
	s_CUI_ID_FRAME_SuAnimalMenu.SetVisable(false);
	return true;
}
// Button
bool CUI_ID_FRAME_SuAnimalMenu::ID_BUTTON_FeedOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_SuAnimalMenu )
		return false;
	UseItem(ItemDefine::EPetFunc_AddLoyalty);
	s_CUI_ID_FRAME_SuAnimalMenu.SetVisable(false);
	return true;
}

// 装载UI
bool CUI_ID_FRAME_SuAnimalMenu::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\SuAnimalMenu.MEUI" ,true,UI_Render_LayerThree);
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\SuAnimalMenu.MEUI]失败")
		return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_SuAnimalMenu::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_SuAnimalMenu, s_CUI_ID_FRAME_SuAnimalMenuOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_SuAnimalMenu, s_CUI_ID_FRAME_SuAnimalMenuOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_SuAnimalMenu, ID_BUTTON_Look, s_CUI_ID_FRAME_SuAnimalMenuID_BUTTON_LookOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SuAnimalMenu, ID_BUTTON_XiuXi, s_CUI_ID_FRAME_SuAnimalMenuID_BUTTON_XiuXiOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SuAnimalMenu, ID_BUTTON_Cure, s_CUI_ID_FRAME_SuAnimalMenuID_BUTTON_CureOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_SuAnimalMenu, ID_BUTTON_Feed, s_CUI_ID_FRAME_SuAnimalMenuID_BUTTON_FeedOnButtonClick );

	m_pID_FRAME_SuAnimalMenu = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_SuAnimalMenu );
	m_pID_BUTTON_Look = (ControlButton*)theUiManager.FindControl( ID_FRAME_SuAnimalMenu, ID_BUTTON_Look );
	m_pID_BUTTON_XiuXi = (ControlButton*)theUiManager.FindControl( ID_FRAME_SuAnimalMenu, ID_BUTTON_XiuXi );
	m_pID_BUTTON_Cure = (ControlButton*)theUiManager.FindControl( ID_FRAME_SuAnimalMenu, ID_BUTTON_Cure );
	m_pID_BUTTON_Feed = (ControlButton*)theUiManager.FindControl( ID_FRAME_SuAnimalMenu, ID_BUTTON_Feed );

	assert( m_pID_FRAME_SuAnimalMenu );
	assert( m_pID_BUTTON_Look );
	assert( m_pID_BUTTON_XiuXi );
	assert( m_pID_BUTTON_Cure );
	assert( m_pID_BUTTON_Feed );

	_SetVisable(false);
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_SuAnimalMenu::_UnLoadUI()
{
	m_pID_FRAME_SuAnimalMenu = NULL;
	m_pID_BUTTON_Look = NULL;
	m_pID_BUTTON_XiuXi = NULL;
	m_pID_BUTTON_Cure = NULL;
	m_pID_BUTTON_Feed = NULL;
	m_IsLookOtherPet = false;
	return theUiManager.RemoveFrame( "Data\\UI\\SuAnimalMenu.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_SuAnimalMenu::_IsVisable()
{
	if ( !m_pID_FRAME_SuAnimalMenu )
		return false;
	return m_pID_FRAME_SuAnimalMenu->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_SuAnimalMenu::_SetVisable( const bool bVisable )
{
	if ( !m_pID_FRAME_SuAnimalMenu )
		return ;
	m_pID_FRAME_SuAnimalMenu->SetVisable( bVisable );
	if (m_pID_FRAME_SuAnimalMenu->IsVisable())
	{
		s_CUI_ID_FRAME_SelfRBMenu.SetVisable(false);
		s_CUI_ID_FRAME_RBTNMENU.SetVisable(false);
		s_CUI_ID_FRAME_PetRBMenu.SetVisable(false);
		s_CUI_ID_FRAME_FriendDlgRight.SetVisable(false);

		int x,y;
		x = theUiManager.m_ptMoust.x;
		y = theUiManager.m_ptMoust.y;
		m_pID_FRAME_SuAnimalMenu->SetPos(x,y);
	}
	if (s_CUI_ID_FRAME_SuAnimalMenu.m_pID_FRAME_SuAnimalMenu)
		theUiManager.ToTop(s_CUI_ID_FRAME_SuAnimalMenu.m_pID_FRAME_SuAnimalMenu);
	
}

void CUI_ID_FRAME_SuAnimalMenu::UseItem(unsigned char ucValue)
{
	int nCount = thePlayerRole.m_bag.GetItemCount();
	for (int i = 0;i < nCount;++i)
	{
		SCharItem sItem;
		if(!thePlayerRole.m_bag.GetItem(i,&sItem))
			continue;

		ItemDefine::SItemCommon * pItemCommon = GettheItemDetail().GetItemByID(sItem.itembaseinfo.ustItemID);
		if(!pItemCommon)
			continue;

		if(pItemCommon->byUserTarget != ItemDefine::eTargetPet)
			continue;

		if(pItemCommon->ucItemType != ItemDefine::ITEMTYPE_RESTORE)
			continue;

		ItemDefine::SItemRestore *pRestore = (ItemDefine::SItemRestore*)pItemCommon;
		if(pRestore->specialFunction != ucValue)
			continue;

		MsgUseGoodsToPet msg;
		msg.nPetIndex = GetCurrentPetIndex();
		if(msg.nPetIndex != -1)
		{
			msg.nGuid = sItem.itembaseinfo.nOnlyInt;
			msg.ustItemIndex = i;
			msg.stItemCount = 1;
			msg.stSrcChar = 0;
			msg.stDstChar = 0;
			msg.ucItemBagType = BT_NormalItemBag;
			GettheNetworkInput().SendMsg( &msg );
		}
		break;
	}
	m_pID_FRAME_SuAnimalMenu->SetVisable(!m_pID_FRAME_SuAnimalMenu->IsVisable());
}

void CUI_ID_FRAME_SuAnimalMenu::SetCurrentPetIndex(const char *m_name)
{
	m_CurrentPetIndex = thePlayerRole.GetPetIndexByName(m_name);
}

ControlButton *CUI_ID_FRAME_SuAnimalMenu::GetXiuXiBtn()
{
	if(m_pID_FRAME_SuAnimalMenu != NULL)
		return m_pID_BUTTON_XiuXi;
	return NULL;
}
ControlButton *CUI_ID_FRAME_SuAnimalMenu::GetCureBtn()
{
	if(m_pID_FRAME_SuAnimalMenu != NULL)
		return m_pID_BUTTON_Cure;
	return NULL;
}
ControlButton *CUI_ID_FRAME_SuAnimalMenu::GetFeedBtn()
{
	if(m_pID_FRAME_SuAnimalMenu != NULL)
		return m_pID_BUTTON_Feed;
	return NULL;
}

void CUI_ID_FRAME_SuAnimalMenu::SetPlayerID(GameObjectId m_playerID)
{
	m_IsLookOtherPet = true;
	m_OtherPlayerID = m_playerID;
}