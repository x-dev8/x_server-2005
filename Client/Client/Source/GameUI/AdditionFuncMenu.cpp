/********************************************************************
Created by UIEditor.exe
FileName: E:\3Guo_Client_12.27\3Guo_Client_12.27\Data\Ui\AdditionFuncMenu.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "AdditionFuncMenu.h"
#include "Star.h"
#include "Gem.h"
#include "Hole.h"
#include "Shop.h"
#include "Pack.h"
#include "UIMgr.h"
#include "GemUp.h"
#include "MainMenu.h"
#include "TransferStar.h"
#include "jiebang.h"
#include "GemRemove.h"
#include "GameMain.h"
#include "PlayerMgr.h"
#include "Player.h"

CUI_ID_FRAME_AdditionFuncMenu s_CUI_ID_FRAME_AdditionFuncMenu;
extern void SetTipAndHotKey(ControlButton* pCtl, AN_Configure_ShortcutKey::ShortCutKey_Configure key);
extern CHeroGame	theHeroGame;
MAP_FRAME_RUN( s_CUI_ID_FRAME_AdditionFuncMenu, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_AdditionFuncMenu, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_AdditionFuncMenu, ID_BUTTON_StarOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_AdditionFuncMenu, ID_BUTTON_GemUpOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_AdditionFuncMenu, ID_BUTTON_GemOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_AdditionFuncMenu, ID_BUTTON_HoleOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_AdditionFuncMenu, ID_BUTTON_TransferStarOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_AdditionFuncMenu, ID_BUTTON_UNBondOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_AdditionFuncMenu, ID_BUTTON_GemRemoveOnButtonClick )
CUI_ID_FRAME_AdditionFuncMenu::CUI_ID_FRAME_AdditionFuncMenu()
{
	// Member
	m_pID_FRAME_AdditionFuncMenu = NULL;
	m_pID_BUTTON_Star = NULL;
	m_pID_BUTTON_GemUp = NULL;
	m_pID_BUTTON_Gem = NULL;
	m_pID_BUTTON_Hole = NULL;
	m_pID_BUTTON_TransferStar = NULL;
	m_pID_BUTTON_UNBond = NULL;
	m_pID_BUTTON_GemRemove = NULL;

}
// Frame
bool CUI_ID_FRAME_AdditionFuncMenu::OnFrameRun()
{
	return true;
}
bool CUI_ID_FRAME_AdditionFuncMenu::OnFrameRender()
{
	return true;
}
// Button
bool CUI_ID_FRAME_AdditionFuncMenu::ID_BUTTON_StarOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_AdditionFuncMenu )
		return false;
	s_CUI_ID_FRAME_PACK.SetVisable(true);
	s_CUI_ID_FRAME_Star.SetIsPocket(true);
	{
		if (s_CUI_ID_FRAME_Gem.IsVisable())
		{
			s_CUI_ID_FRAME_Gem.SetVisable(false);
		}
		if (s_CUI_ID_FRAME_Hole.IsVisable())
		{
			s_CUI_ID_FRAME_Hole.SetVisable(false);
		}
		if (s_CUI_ID_FRAME_SHOP.IsVisable())
		{
			s_CUI_ID_FRAME_SHOP.SetVisable(false);
		}
		if (s_CUI_ID_FRAME_GemUp.IsVisable())
		{
			s_CUI_ID_FRAME_GemUp.SetVisable(false);
		}
		if (s_CUI_ID_FRAME_TransferStar.IsVisable())
		{
			s_CUI_ID_FRAME_TransferStar.SetVisable(false);
		}
		if (s_CUI_ID_FRAME_JieBang.IsVisable())
		{
			s_CUI_ID_FRAME_JieBang.SetVisable(false);
		}
		if (s_CUI_ID_FRAME_GemRemove.IsVisable())
		{
			s_CUI_ID_FRAME_GemRemove.SetVisable(false);
		}
	}
	s_CUI_ID_FRAME_Star.SetVisable(true);
	ResetWindowPosition(s_CUI_ID_FRAME_Star.GetFrame(), s_CUI_ID_FRAME_PACK.GetFrame());
	return true;
}
// Button
bool CUI_ID_FRAME_AdditionFuncMenu::ID_BUTTON_GemUpOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_AdditionFuncMenu )
		return false;
	s_CUI_ID_FRAME_PACK.SetVisable(true);
	s_CUI_ID_FRAME_GemUp.SetIsPocket(true);
	{
		if (s_CUI_ID_FRAME_Gem.IsVisable())
		{
			s_CUI_ID_FRAME_Gem.SetVisable(false);
		}
		if (s_CUI_ID_FRAME_Star.IsVisable())
		{
			s_CUI_ID_FRAME_Star.SetVisable(false);
		}
		if (s_CUI_ID_FRAME_SHOP.IsVisable())
		{
			s_CUI_ID_FRAME_SHOP.SetVisable(false);
		}
		if (s_CUI_ID_FRAME_Hole.IsVisable())
		{
			s_CUI_ID_FRAME_Hole.SetVisable(false);
		}
		if (s_CUI_ID_FRAME_TransferStar.IsVisable())
		{
			s_CUI_ID_FRAME_TransferStar.SetVisable(false);
		}
		if (s_CUI_ID_FRAME_JieBang.IsVisable())
		{
			s_CUI_ID_FRAME_JieBang.SetVisable(false);
		}
		if (s_CUI_ID_FRAME_GemRemove.IsVisable())
		{
			s_CUI_ID_FRAME_GemRemove.SetVisable(false);
		}
	}
	s_CUI_ID_FRAME_GemUp.SetVisable(true);
	ResetWindowPosition(s_CUI_ID_FRAME_GemUp.GetFrame(), s_CUI_ID_FRAME_PACK.GetFrame());
	return true;
}
// Button
bool CUI_ID_FRAME_AdditionFuncMenu::ID_BUTTON_HoleOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_AdditionFuncMenu )
		return false;
	s_CUI_ID_FRAME_PACK.SetVisable(true);
	s_CUI_ID_FRAME_Hole.SetIsPocket(true);
	{
		if (s_CUI_ID_FRAME_Gem.IsVisable())
		{
			s_CUI_ID_FRAME_Gem.SetVisable(false);
		}
		if (s_CUI_ID_FRAME_Star.IsVisable())
		{
			s_CUI_ID_FRAME_Star.SetVisable(false);
		}
		if (s_CUI_ID_FRAME_SHOP.IsVisable())
		{
			s_CUI_ID_FRAME_SHOP.SetVisable(false);
		}
		if (s_CUI_ID_FRAME_GemUp.IsVisable())
		{
			s_CUI_ID_FRAME_GemUp.SetVisable(false);
		}
		if (s_CUI_ID_FRAME_TransferStar.IsVisable())
		{
			s_CUI_ID_FRAME_TransferStar.SetVisable(false);
		}
		if (s_CUI_ID_FRAME_JieBang.IsVisable())
		{
			s_CUI_ID_FRAME_JieBang.SetVisable(false);
		}
		if (s_CUI_ID_FRAME_GemRemove.IsVisable())
		{
			s_CUI_ID_FRAME_GemRemove.SetVisable(false);
		}
	}
	s_CUI_ID_FRAME_Hole.SetVisable(true);
	ResetWindowPosition(s_CUI_ID_FRAME_Hole.GetFrame(), s_CUI_ID_FRAME_PACK.GetFrame());
	return true;
}
bool CUI_ID_FRAME_AdditionFuncMenu::ID_BUTTON_GemOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_AdditionFuncMenu )
		return false;
	s_CUI_ID_FRAME_PACK.SetVisable(true);
	s_CUI_ID_FRAME_Gem.SetIsPocket(true);

	{
		if (s_CUI_ID_FRAME_Hole.IsVisable())
		{
			s_CUI_ID_FRAME_Hole.SetVisable(false);
		}
		if (s_CUI_ID_FRAME_Star.IsVisable())
		{
			s_CUI_ID_FRAME_Star.SetVisable(false);
		}
		if (s_CUI_ID_FRAME_SHOP.IsVisable())
		{
			s_CUI_ID_FRAME_SHOP.SetVisable(false);
		}
		if (s_CUI_ID_FRAME_GemUp.IsVisable())
		{
			s_CUI_ID_FRAME_GemUp.SetVisable(false);
		}
		if (s_CUI_ID_FRAME_TransferStar.IsVisable())
		{
			s_CUI_ID_FRAME_TransferStar.SetVisable(false);
		}
		if (s_CUI_ID_FRAME_JieBang.IsVisable())
		{
			s_CUI_ID_FRAME_JieBang.SetVisable(false);
		}
		if (s_CUI_ID_FRAME_GemRemove.IsVisable())
		{
			s_CUI_ID_FRAME_GemRemove.SetVisable(false);
		}
	}

	s_CUI_ID_FRAME_Gem.SetVisable(true);
	ResetWindowPosition(s_CUI_ID_FRAME_Gem.GetFrame(), s_CUI_ID_FRAME_PACK.GetFrame());
	return true;
}

// Button
bool CUI_ID_FRAME_AdditionFuncMenu::ID_BUTTON_TransferStarOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_AdditionFuncMenu )
		return false;
	s_CUI_ID_FRAME_PACK.SetVisable(true);

	{
		if (s_CUI_ID_FRAME_Hole.IsVisable())
		{
			s_CUI_ID_FRAME_Hole.SetVisable(false);
		}
		if (s_CUI_ID_FRAME_Star.IsVisable())
		{
			s_CUI_ID_FRAME_Star.SetVisable(false);
		}
		if (s_CUI_ID_FRAME_SHOP.IsVisable())
		{
			s_CUI_ID_FRAME_SHOP.SetVisable(false);
		}
		if (s_CUI_ID_FRAME_GemUp.IsVisable())
		{
			s_CUI_ID_FRAME_GemUp.SetVisable(false);
		}
		if (s_CUI_ID_FRAME_Gem.IsVisable())
		{
			s_CUI_ID_FRAME_Gem.SetVisable(false);
		}
		if (s_CUI_ID_FRAME_JieBang.IsVisable())
		{
			s_CUI_ID_FRAME_JieBang.SetVisable(false);
		}
		if (s_CUI_ID_FRAME_GemRemove.IsVisable())
		{
			s_CUI_ID_FRAME_GemRemove.SetVisable(false);
		}
	}

	s_CUI_ID_FRAME_TransferStar.SetVisable(true);
	ResetWindowPosition(s_CUI_ID_FRAME_TransferStar.GetFrame(), s_CUI_ID_FRAME_PACK.GetFrame());

	return true;
}
bool CUI_ID_FRAME_AdditionFuncMenu::ID_BUTTON_UNBondOnButtonClick( ControlObject* pSender )
{
	//打开或者关闭解绑UI
	if( !m_pID_FRAME_AdditionFuncMenu )
		return false;
	s_CUI_ID_FRAME_PACK.SetVisable(true);
	{
		if (s_CUI_ID_FRAME_Gem.IsVisable())
		{
			s_CUI_ID_FRAME_Gem.SetVisable(false);
		}
		if (s_CUI_ID_FRAME_Star.IsVisable())
		{
			s_CUI_ID_FRAME_Star.SetVisable(false);
		}
		if (s_CUI_ID_FRAME_SHOP.IsVisable())
		{
			s_CUI_ID_FRAME_SHOP.SetVisable(false);
		}
		if (s_CUI_ID_FRAME_GemUp.IsVisable())
		{
			s_CUI_ID_FRAME_GemUp.SetVisable(false);
		}
		if (s_CUI_ID_FRAME_TransferStar.IsVisable())
		{
			s_CUI_ID_FRAME_TransferStar.SetVisable(false);
		}
		if (s_CUI_ID_FRAME_Hole.IsVisable())
		{
			s_CUI_ID_FRAME_Hole.SetVisable(false);
		}
		if (s_CUI_ID_FRAME_GemRemove.IsVisable())
		{
			s_CUI_ID_FRAME_GemRemove.SetVisable(false);
		}
	}
	s_CUI_ID_FRAME_JieBang.SetVisable(true);
	ResetWindowPosition(s_CUI_ID_FRAME_JieBang.GetFrame(), s_CUI_ID_FRAME_PACK.GetFrame());
	return true;
}
// Button
bool CUI_ID_FRAME_AdditionFuncMenu::ID_BUTTON_GemRemoveOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_AdditionFuncMenu )
		return false;
	s_CUI_ID_FRAME_PACK.SetVisable(true);

	{
		if (s_CUI_ID_FRAME_Hole.IsVisable())
		{
			s_CUI_ID_FRAME_Hole.SetVisable(false);
		}
		if (s_CUI_ID_FRAME_Star.IsVisable())
		{
			s_CUI_ID_FRAME_Star.SetVisable(false);
		}
		if (s_CUI_ID_FRAME_SHOP.IsVisable())
		{
			s_CUI_ID_FRAME_SHOP.SetVisable(false);
		}
		if (s_CUI_ID_FRAME_GemUp.IsVisable())
		{
			s_CUI_ID_FRAME_GemUp.SetVisable(false);
		}
		if (s_CUI_ID_FRAME_Gem.IsVisable())
		{
			s_CUI_ID_FRAME_Gem.SetVisable(false);
		}
		if (s_CUI_ID_FRAME_JieBang.IsVisable())
		{
			s_CUI_ID_FRAME_JieBang.SetVisable(false);
		}
		if (s_CUI_ID_FRAME_TransferStar.IsVisable())
		{
			s_CUI_ID_FRAME_TransferStar.SetVisable(false);
		}
	}

	s_CUI_ID_FRAME_GemRemove.SetIsPocket(true);
	s_CUI_ID_FRAME_GemRemove.SetVisable(true);
	ResetWindowPosition(s_CUI_ID_FRAME_GemRemove.GetFrame(), s_CUI_ID_FRAME_PACK.GetFrame());
	/*if( theHeroGame.GetPlayerMgr()->GetMe() )
	{
		s_CUI_ID_FRAME_GemRemove.SetVisiblePosition( *(Vector*)&(theHeroGame.GetPlayerMgr()->GetMe())->GetPos() );
	}	*/	
	return true;
}

// 装载UI
bool CUI_ID_FRAME_AdditionFuncMenu::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\AdditionFuncMenu.MEUI",true, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\AdditionFuncMenu.MEUI]失败")
			return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_AdditionFuncMenu::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_AdditionFuncMenu, s_CUI_ID_FRAME_AdditionFuncMenuOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_AdditionFuncMenu, s_CUI_ID_FRAME_AdditionFuncMenuOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_AdditionFuncMenu, ID_BUTTON_Star, s_CUI_ID_FRAME_AdditionFuncMenuID_BUTTON_StarOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_AdditionFuncMenu, ID_BUTTON_GemUp, s_CUI_ID_FRAME_AdditionFuncMenuID_BUTTON_GemUpOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_AdditionFuncMenu, ID_BUTTON_Gem, s_CUI_ID_FRAME_AdditionFuncMenuID_BUTTON_GemOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_AdditionFuncMenu, ID_BUTTON_Hole, s_CUI_ID_FRAME_AdditionFuncMenuID_BUTTON_HoleOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_AdditionFuncMenu, ID_BUTTON_TransferStar, s_CUI_ID_FRAME_AdditionFuncMenuID_BUTTON_TransferStarOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_AdditionFuncMenu, ID_BUTTON_UNBond, s_CUI_ID_FRAME_AdditionFuncMenuID_BUTTON_UNBondOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_AdditionFuncMenu, ID_BUTTON_GemRemove, s_CUI_ID_FRAME_AdditionFuncMenuID_BUTTON_GemRemoveOnButtonClick );

	m_pID_FRAME_AdditionFuncMenu = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_AdditionFuncMenu );
	m_pID_BUTTON_Star = (ControlButton*)theUiManager.FindControl( ID_FRAME_AdditionFuncMenu, ID_BUTTON_Star );
	m_pID_BUTTON_GemUp = (ControlButton*)theUiManager.FindControl( ID_FRAME_AdditionFuncMenu, ID_BUTTON_GemUp );
	m_pID_BUTTON_Gem = (ControlButton*)theUiManager.FindControl( ID_FRAME_AdditionFuncMenu, ID_BUTTON_Gem );
	m_pID_BUTTON_Hole = (ControlButton*)theUiManager.FindControl( ID_FRAME_AdditionFuncMenu, ID_BUTTON_Hole );
	m_pID_BUTTON_TransferStar = (ControlButton*)theUiManager.FindControl( ID_FRAME_AdditionFuncMenu, ID_BUTTON_TransferStar );
	m_pID_BUTTON_UNBond = (ControlButton*)theUiManager.FindControl( ID_FRAME_AdditionFuncMenu, ID_BUTTON_UNBond );
	m_pID_BUTTON_GemRemove = (ControlButton*)theUiManager.FindControl( ID_FRAME_AdditionFuncMenu, ID_BUTTON_GemRemove );

	assert( m_pID_BUTTON_Hole );
	assert( m_pID_FRAME_AdditionFuncMenu );
	assert( m_pID_BUTTON_Star );
	assert( m_pID_BUTTON_GemUp );
	assert( m_pID_BUTTON_Gem );
	assert( m_pID_BUTTON_TransferStar );
	assert( m_pID_BUTTON_UNBond );
	assert( m_pID_BUTTON_GemRemove );

	SetTipAndHotKey(m_pID_BUTTON_Hole, AN_Configure_ShortcutKey::AN_SCK_SuAnimalHole);
	SetTipAndHotKey(m_pID_BUTTON_Star, AN_Configure_ShortcutKey::AN_SCK_SuAnimalStar);
	SetTipAndHotKey(m_pID_BUTTON_GemUp, AN_Configure_ShortcutKey::AN_SCK_SuAnimalGemUp);
	SetTipAndHotKey(m_pID_BUTTON_Gem, AN_Configure_ShortcutKey::AN_SCK_SuAnimalGem);
	SetTipAndHotKey(m_pID_BUTTON_TransferStar, AN_Configure_ShortcutKey::AN_SCK_SuAnimalTransferStar);
	SetTipAndHotKey(m_pID_BUTTON_UNBond, AN_Configure_ShortcutKey::AN_SCK_UNBIND);
	SetTipAndHotKey(m_pID_BUTTON_GemRemove, AN_Configure_ShortcutKey::AN_SCK_SuAnimalGemRemove);
	//m_pID_BUTTON_Hole->setTip(m_pID_BUTTON_Hole->GetRealCaption());
	//m_pID_BUTTON_Hole->SetShowTip(true);
	//m_pID_BUTTON_Star->setTip(m_pID_BUTTON_Star->GetRealCaption());
	//m_pID_BUTTON_Star->SetShowTip(true);
	//m_pID_BUTTON_GemUp->setTip(m_pID_BUTTON_GemUp->GetRealCaption());
	//m_pID_BUTTON_GemUp->SetShowTip(true);
	//m_pID_BUTTON_Gem->setTip(m_pID_BUTTON_Gem->GetRealCaption());
	//m_pID_BUTTON_Gem->SetShowTip(true);
	m_pID_FRAME_AdditionFuncMenu->SetFadeInorFadeOut(true);
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_AdditionFuncMenu::_UnLoadUI()
{
	m_pID_FRAME_AdditionFuncMenu = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\AdditionFuncMenu.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_AdditionFuncMenu::_IsVisable()
{
	if( !m_pID_FRAME_AdditionFuncMenu )
		return false;
	return m_pID_FRAME_AdditionFuncMenu->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_AdditionFuncMenu::_SetVisable( const bool bVisable )
{
	if (!m_pID_FRAME_AdditionFuncMenu)
	{
		return;
	}
	
	m_pID_FRAME_AdditionFuncMenu->SetVisable( bVisable );
	
}
