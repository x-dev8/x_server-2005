/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\yang.xu\桌面\功能菜单\ExMenu.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "ExMenu.h"
//#include "ui/ActivityList.h"
#include "ui\ActivityDay.h"
#include "ui/UiTitle.h"
#include "ui/Protect.h"
#include "RankList.h"
#include "ShopCenter.h"
#include "AutoAttackSet.h"
#include "ChangeEquip.h"
#include "Action.h"
#include "Achivement.h"
#include "CharacterExp.h"
#include "Epic.h"
#include "shortcutkey_configure.h"
#include "XmlStringLanguage.h"
#include "ui/SuAnimalCardList.h"
#include "MainMenu.h"
#include "Achivement.h"
#include "Card.h"

CUI_ID_FRAME_ExMenu s_CUI_ID_FRAME_ExMenu;
MAP_FRAME_RUN( s_CUI_ID_FRAME_ExMenu, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_ExMenu, OnFrameRender )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ExMenu, ID_BUTTON_ActivityDayOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ExMenu, ID_BUTTON_TaxisOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ExMenu, ID_BUTTON_ChangeEquipOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ExMenu, ID_BUTTON_ActionOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ExMenu, ID_BUTTON_ProtectOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ExMenu, ID_BUTTON_ShopOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ExMenu, ID_BUTTON_CardOnButtonClick )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_ExMenu, ID_BUTTON_AchievementOnButtonClick)

extern void SetTipAndHotKey(ControlButton* pCtl, const char* szText, AN_Configure_ShortcutKey::ShortCutKey_Configure key);
extern void SetTipAndHotKey(ControlButton* pCtl, AN_Configure_ShortcutKey::ShortCutKey_Configure key);
CUI_ID_FRAME_ExMenu::CUI_ID_FRAME_ExMenu()
{
	// Member
	m_pID_FRAME_ExMenu = NULL;
	m_pID_BUTTON_ActivityDay = NULL;
	m_pID_BUTTON_Taxis = NULL;
	m_pID_BUTTON_ChangeEquip = NULL;
	m_pID_BUTTON_Action = NULL;
	m_pID_BUTTON_Protect = NULL;
	m_pID_BUTTON_Shop = NULL;
	m_pID_BUTTON_Card = NULL;
	m_pID_BUTTON_Achievement = NULL;
	

	m_pID_TEXT_Shop = NULL;
	m_pID_TEXT_Action = NULL;
	m_pID_TEXT_ActivityDay1 = NULL;
	m_pID_TEXT_Taxis = NULL;
	m_pID_TEXT_Protect = NULL;
	m_pID_TEXT_Card = NULL;
	m_pID_TEXT_Achievement = NULL;

}
// Frame
bool CUI_ID_FRAME_ExMenu::OnFrameRun()
{
	//每帧界面逻辑更新，需要先判断界面是否可见，把下面代码打开
	//if( IsVisable() )
	//{
	//}
	return true;
}
bool CUI_ID_FRAME_ExMenu::OnFrameRender()
{
	return true;
}
// Button
bool CUI_ID_FRAME_ExMenu::ID_BUTTON_ActivityDayOnButtonClick( ControlObject* pSender )
{
		if(!m_pID_FRAME_ExMenu)
	{
		assert(false&&"ui error");
		return false;
	}

	s_CUI_ID_FRAME_ActivityList.SetVisable( !s_CUI_ID_FRAME_ActivityList.IsVisable() );

	SetActivityDay1HighLight();

	return true;
}



// Button
bool CUI_ID_FRAME_ExMenu::ID_BUTTON_TaxisOnButtonClick( ControlObject* pSender )
{
	if( !m_pID_FRAME_ExMenu )
		return false;

	s_CUI_ID_FRAME_RankList.SetVisable( !s_CUI_ID_FRAME_RankList.IsVisable() );
	SetTaxisHighLight();
	return true;
}
// Button
bool CUI_ID_FRAME_ExMenu::ID_BUTTON_ChangeEquipOnButtonClick( ControlObject* pSender )
{
	if(!m_pID_FRAME_ExMenu)
    {
        assert(false&&"ui error");
        return false;
    }
    s_CUI_ID_FRAME_ChangeEquip.SetVisable(!s_CUI_ID_FRAME_ChangeEquip.IsVisable());
    s_CUI_ID_FRAME_ChangeEquip.SaveSuit(false);
    return true;
}
// Button
bool CUI_ID_FRAME_ExMenu::ID_BUTTON_ActionOnButtonClick( ControlObject* pSender )
{
 if(!m_pID_FRAME_ExMenu)
    {
        assert(false&&"ui error");
        return false;
    }
	//s_CUI_ID_FRAME_ActivityList.SetVisable( !s_CUI_ID_FRAME_ActivityList.IsVisable() );

	s_CUI_ID_FRAME_Action.SetVisable( !s_CUI_ID_FRAME_Action.IsVisable() );
	SetActionHighLight();

	return true;
}
// Button
bool CUI_ID_FRAME_ExMenu::ID_BUTTON_ProtectOnButtonClick( ControlObject* pSender )
{
    if(!m_pID_FRAME_ExMenu)
    {
        assert(false&&"ui error");
        return false;
    }
    s_CUI_ID_FRAME_Protect.SetVisable( !s_CUI_ID_FRAME_Protect.IsVisable() );
	SetProtectHighLight();
	return true;
}

//Button
bool CUI_ID_FRAME_ExMenu::ID_BUTTON_AchievementOnButtonClick(ControlObject* pSender)
{
	if(!m_pID_FRAME_ExMenu)
	{
		assert(false&&"ui error");
		return false;
	}

	s_CUI_ID_FRAME_Achivement.SetVisable(!s_CUI_ID_FRAME_Achivement.IsVisable());
	SetAchievementHighLight();
	return true;
}

// Button
bool CUI_ID_FRAME_ExMenu::ID_BUTTON_ShopOnButtonClick( ControlObject* pSender )
{
    if(!m_pID_FRAME_ExMenu)
    {
        assert(false&&"ui error");
        return false;
    }
	s_CUI_ID_FRAME_ShopCenter.SetVisable( !s_CUI_ID_FRAME_ShopCenter.IsVisable() );
	SetShopHighLight();
	return true;
}
// Button
bool CUI_ID_FRAME_ExMenu::ID_BUTTON_CardOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_ExMenu )
		return false;

	//s_CUI_ID_FRAME_SuAnimalCardList.SetVisable(!s_CUI_ID_FRAME_SuAnimalCardList.IsVisable());
	s_CUI_ID_FRAME_CARD.SetVisable( !s_CUI_ID_FRAME_CARD.IsVisable() );
	SetCardHighLight();
	return true;
}

// 装载UI
bool CUI_ID_FRAME_ExMenu::	_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\ExMenu.MEUI",true, UI_Render_LayerThree);
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\ExMenu.MEUI]失败")
		return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_ExMenu::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_ExMenu, s_CUI_ID_FRAME_ExMenuOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_ExMenu, s_CUI_ID_FRAME_ExMenuOnFrameRender );
	theUiManager.OnButtonClick( ID_FRAME_ExMenu, ID_BUTTON_ActivityDay, s_CUI_ID_FRAME_ExMenuID_BUTTON_ActivityDayOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_ExMenu, ID_BUTTON_Taxis, s_CUI_ID_FRAME_ExMenuID_BUTTON_TaxisOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_ExMenu, ID_BUTTON_ChangeEquip, s_CUI_ID_FRAME_ExMenuID_BUTTON_ChangeEquipOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_ExMenu, ID_BUTTON_Action, s_CUI_ID_FRAME_ExMenuID_BUTTON_ActionOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_ExMenu, ID_BUTTON_Protect, s_CUI_ID_FRAME_ExMenuID_BUTTON_ProtectOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_ExMenu, ID_BUTTON_Shop, s_CUI_ID_FRAME_ExMenuID_BUTTON_ShopOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_ExMenu, ID_BUTTON_Card, s_CUI_ID_FRAME_ExMenuID_BUTTON_CardOnButtonClick );
	theUiManager.OnButtonClick( ID_FRAME_ExMenu, ID_BUTTON_Achievement, s_CUI_ID_FRAME_ExMenuID_BUTTON_AchievementOnButtonClick);
	

	m_pID_FRAME_ExMenu = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_ExMenu );
	m_pID_BUTTON_ActivityDay = (ControlButton*)theUiManager.FindControl( ID_FRAME_ExMenu, ID_BUTTON_ActivityDay );
	m_pID_BUTTON_Taxis = (ControlButton*)theUiManager.FindControl( ID_FRAME_ExMenu, ID_BUTTON_Taxis );
	m_pID_BUTTON_ChangeEquip = (ControlButton*)theUiManager.FindControl( ID_FRAME_ExMenu, ID_BUTTON_ChangeEquip );
	m_pID_BUTTON_Action = (ControlButton*)theUiManager.FindControl( ID_FRAME_ExMenu, ID_BUTTON_Action );
	m_pID_BUTTON_Protect = (ControlButton*)theUiManager.FindControl( ID_FRAME_ExMenu, ID_BUTTON_Protect );
	m_pID_BUTTON_Shop = (ControlButton*)theUiManager.FindControl( ID_FRAME_ExMenu, ID_BUTTON_Shop );
	m_pID_BUTTON_Card = (ControlButton*)theUiManager.FindControl( ID_FRAME_ExMenu, ID_BUTTON_Card );

	m_pID_BUTTON_Achievement = (ControlButton*)theUiManager.FindControl(ID_FRAME_ExMenu, ID_BUTTON_Achievement);
	m_pID_TEXT_Achievement = (ControlText*)theUiManager.FindControl(ID_FRAME_ExMenu, ID_TEXT_Achievement );
	
	m_pID_TEXT_Shop = (ControlText*)theUiManager.FindControl( ID_FRAME_ExMenu, ID_TEXT_Shop );
	m_pID_TEXT_Action = (ControlText*)theUiManager.FindControl( ID_FRAME_ExMenu, ID_TEXT_Action );
	m_pID_TEXT_ActivityDay1 = (ControlText*)theUiManager.FindControl( ID_FRAME_ExMenu, ID_TEXT_ActivityDay1 );
	m_pID_TEXT_Taxis = (ControlText*)theUiManager.FindControl( ID_FRAME_ExMenu, ID_TEXT_Taxis );
	m_pID_TEXT_Protect = (ControlText*)theUiManager.FindControl( ID_FRAME_ExMenu, ID_TEXT_Protect );
	m_pID_TEXT_Card = (ControlText*)theUiManager.FindControl( ID_FRAME_ExMenu, ID_TEXT_Card );
	

	assert( m_pID_FRAME_ExMenu );
	assert( m_pID_BUTTON_ActivityDay );
	assert( m_pID_BUTTON_Taxis );
	assert( m_pID_BUTTON_ChangeEquip );
	assert( m_pID_BUTTON_Action );
	assert( m_pID_BUTTON_Protect );
	assert( m_pID_BUTTON_Shop );
	assert( m_pID_BUTTON_Card );
	assert( m_pID_BUTTON_Achievement);

	assert(	m_pID_TEXT_Achievement);
	assert( m_pID_TEXT_Shop );
	assert( m_pID_TEXT_Action );
	assert( m_pID_TEXT_ActivityDay1 );
	assert( m_pID_TEXT_Taxis );
	assert( m_pID_TEXT_Protect );
	assert( m_pID_TEXT_Card );
	

	_SetVisable(false);
	m_pID_FRAME_ExMenu->SetFadeInorFadeOut(true);

	m_pID_TEXT_Shop->SetEnable(false);
	m_pID_TEXT_Shop->SetVisable(false);
	m_pID_TEXT_Action->SetEnable(false);
	m_pID_TEXT_Action->SetVisable(false);
	m_pID_TEXT_ActivityDay1->SetEnable(false);
	m_pID_TEXT_ActivityDay1->SetVisable(false);
	m_pID_TEXT_Taxis->SetEnable(false);
	m_pID_TEXT_Taxis->SetVisable(false);
	m_pID_TEXT_Protect->SetEnable(false);
	m_pID_TEXT_Protect->SetVisable(false);
	m_pID_TEXT_Card->SetEnable(false);
	m_pID_TEXT_Card->SetVisable(false);
	m_pID_TEXT_Achievement->SetEnable(false);
	m_pID_TEXT_Achievement->SetVisable(false);
	

	return true;
}
// 卸载UI
bool CUI_ID_FRAME_ExMenu::_UnLoadUI()
{
	m_pID_FRAME_ExMenu = NULL;
	m_pID_BUTTON_ActivityDay = NULL;
	m_pID_BUTTON_Taxis = NULL;
	m_pID_BUTTON_ChangeEquip = NULL;
	m_pID_BUTTON_Action = NULL;
	m_pID_BUTTON_Protect = NULL;
	m_pID_BUTTON_Shop = NULL;
	m_pID_BUTTON_Card = NULL;
	m_pID_BUTTON_Achievement = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\ExMenu.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_ExMenu::_IsVisable()
{
	if ( !m_pID_FRAME_ExMenu )
		return false;
	return m_pID_FRAME_ExMenu->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_ExMenu::_SetVisable( const bool bVisable )
{
	if ( !m_pID_FRAME_ExMenu )
		return ;
	m_pID_FRAME_ExMenu->SetVisable( bVisable );

	if(bVisable)
		RefreshHotKey();
}

ControlButton*	CUI_ID_FRAME_ExMenu::GetpIDButtonTaxis()
{
	if(m_pID_BUTTON_Taxis)
		return m_pID_BUTTON_Taxis;
	else
		assert(false&&"ui error");

	return NULL;
}

ControlButton*	CUI_ID_FRAME_ExMenu::GetpIDButtonProtect()
{
	if(m_pID_BUTTON_Protect)
		return m_pID_BUTTON_Protect;
	else
		assert(false&&"ui error");

	return NULL;
}

ControlButton* CUI_ID_FRAME_ExMenu::GetpIDButtonAchievement()
{
	if (m_pID_BUTTON_Achievement)
	{
		return m_pID_BUTTON_Achievement;
	}
	else
	{
		assert(false&&"ui error");
	}
	return NULL;
}

ControlButton*	CUI_ID_FRAME_ExMenu::GetpIDButtonShop()
{
	if(m_pID_BUTTON_Shop)
		return m_pID_BUTTON_Shop;
	else
		assert(false&&"ui error");

	return NULL;
}

ControlButton*	CUI_ID_FRAME_ExMenu::GetpIDButtonChangeEquip()
{
	if(m_pID_BUTTON_ChangeEquip)
		return m_pID_BUTTON_ChangeEquip;
	else
		assert(false&&"ui error");

	return NULL;
}

ControlButton*	CUI_ID_FRAME_ExMenu::GetpIDButtonAction()
{
	if(m_pID_BUTTON_Action)
		return m_pID_BUTTON_Action;
	else
		assert(false&&"ui error");

	return NULL;
}


void CUI_ID_FRAME_ExMenu::SetTaxisPressPic()
{
	if(m_pID_BUTTON_Taxis)
		m_pID_BUTTON_Taxis->SetPressPic();
	else
		assert(false&&"ui error");
}
void CUI_ID_FRAME_ExMenu::SetProtectPressPic()
{
	/*if(m_pID_BUTTON_Protect)
		m_pID_BUTTON_Protect->SetPressPic();
	else
		assert(false&&"ui error");*/
}
void CUI_ID_FRAME_ExMenu::SetShopPressPic()
{
	if(m_pID_BUTTON_Shop)
		m_pID_BUTTON_Shop->SetPressPic();
	else
		assert(false&&"ui error");
}

void CUI_ID_FRAME_ExMenu::SetAchievementPressPic()
{
	if(m_pID_BUTTON_Achievement)
	{
		m_pID_BUTTON_Achievement->SetPressPic();
	}
	else
	{
		assert(false&&"ui error");
	}
}

void CUI_ID_FRAME_ExMenu::SetChangeEquipPressPic()
{
	if(m_pID_BUTTON_ChangeEquip)
		m_pID_BUTTON_ChangeEquip->SetPressPic();
	else
		assert(false&&"ui error");
}


void CUI_ID_FRAME_ExMenu::SetActivityPressPic()
{
	if(m_pID_BUTTON_ActivityDay)
		m_pID_BUTTON_ActivityDay->SetPressPic();
	else
		assert(false&&"ui error");
}

void CUI_ID_FRAME_ExMenu::SetActivityNormalPic()
{
	if(m_pID_BUTTON_ActivityDay)
		m_pID_BUTTON_ActivityDay->SetNormalPic();
	else
		assert(false&&"ui error");
}





void CUI_ID_FRAME_ExMenu::SetTaxisNormalPic()
{
	if(m_pID_BUTTON_Taxis)
		m_pID_BUTTON_Taxis->SetNormalPic();
	else
		assert(false&&"ui error");
}
void CUI_ID_FRAME_ExMenu::SetProtectNormalPic()
{
	if(m_pID_BUTTON_Protect)
		m_pID_BUTTON_Protect->SetNormalPic();
	else
		assert(false&&"ui error");
}
void CUI_ID_FRAME_ExMenu::SetShopNormalPic()
{
	if(m_pID_BUTTON_Shop)
		m_pID_BUTTON_Shop->SetNormalPic();
	else
		assert(false&&"ui error");
}

void CUI_ID_FRAME_ExMenu::SetAchievementNormalPic()
{
	if(m_pID_BUTTON_Achievement)
	{
		m_pID_BUTTON_Achievement->SetNormalPic();
	}
	else
	{
		assert(false&&"ui error");
	}
};

void CUI_ID_FRAME_ExMenu::SetChangeEquipNormalPic()
{
	if(m_pID_BUTTON_ChangeEquip)
		m_pID_BUTTON_ChangeEquip->SetNormalPic();
	else
		assert(false&&"ui error");
}

void CUI_ID_FRAME_ExMenu::SetActionPressPic()
{
	if( m_pID_BUTTON_Action )
		m_pID_BUTTON_Action->SetPressPic();
	else
		assert(false&&"ui error");
}

void CUI_ID_FRAME_ExMenu::SetActionNormalPic()
{
	if( m_pID_BUTTON_Action )
		m_pID_BUTTON_Action->SetNormalPic();
	else
		assert(false&&"ui error");
}

void CUI_ID_FRAME_ExMenu::SetCartState(bool bValue)
{
	if(!m_pID_FRAME_ExMenu)
		return;

	m_pID_BUTTON_Card->SetBtnPicture(bValue);
}

void CUI_ID_FRAME_ExMenu::SetShopHighLight()
{
	if(!m_pID_FRAME_ExMenu)
		return;

	s_CUI_ID_FRAME_MainMenu.SetOtherHighLight();
	m_pID_TEXT_Shop->SetVisable(false);
}

void CUI_ID_FRAME_ExMenu::SetAchievementHighLight()
{
	if (!m_pID_FRAME_ExMenu)
	{
		return;
	}
	s_CUI_ID_FRAME_MainMenu.SetOtherHighLight();
	m_pID_TEXT_Achievement->SetVisable(false);
}

void CUI_ID_FRAME_ExMenu::SetActionHighLight()
{
	if(!m_pID_FRAME_ExMenu)
		return;

	s_CUI_ID_FRAME_MainMenu.SetOtherHighLight();
	m_pID_TEXT_Action->SetVisable(false);
}

void CUI_ID_FRAME_ExMenu::SetActivityDay1HighLight()
{
	if(!m_pID_FRAME_ExMenu)
		return;

	s_CUI_ID_FRAME_MainMenu.SetOtherHighLight();
	m_pID_TEXT_ActivityDay1->SetVisable(false);
}



void CUI_ID_FRAME_ExMenu::SetTaxisHighLight()
{
	if(!m_pID_FRAME_ExMenu)
		return;

	s_CUI_ID_FRAME_MainMenu.SetOtherHighLight();
	m_pID_TEXT_Taxis->SetVisable(false);
}

void CUI_ID_FRAME_ExMenu::SetProtectHighLight()
{
	if(!m_pID_FRAME_ExMenu)
		return;

	s_CUI_ID_FRAME_MainMenu.SetOtherHighLight();
	m_pID_TEXT_Protect->SetVisable(false);
}

void CUI_ID_FRAME_ExMenu::SetCardHighLight()
{
	if(!m_pID_FRAME_ExMenu)
		return;

	s_CUI_ID_FRAME_MainMenu.SetOtherHighLight();
	m_pID_TEXT_Card->SetVisable(false);
}

void CUI_ID_FRAME_ExMenu::RefreshHotKey()
{
	if( !m_pID_FRAME_ExMenu )
		return;

	SetTipAndHotKey(m_pID_BUTTON_Action, AN_Configure_ShortcutKey::AN_SCKC_uiExpressionAction);
	SetTipAndHotKey(m_pID_BUTTON_Taxis, AN_Configure_ShortcutKey::AN_SCKC_uiRank);
	SetTipAndHotKey(m_pID_BUTTON_Protect, AN_Configure_ShortcutKey::AN_SCKC_uiWealthProtect);
	SetTipAndHotKey(m_pID_BUTTON_ActivityDay, AN_Configure_ShortcutKey::AN_SCKC_openEvent);
	SetTipAndHotKey(m_pID_BUTTON_Shop, AN_Configure_ShortcutKey::AN_SCKC_uiShopCenter);
	SetTipAndHotKey(m_pID_BUTTON_Card,AN_Configure_ShortcutKey::AN_SCK_SuAnimalCard);
	SetTipAndHotKey(m_pID_BUTTON_Achievement,AN_Configure_ShortcutKey::AN_SCKC_uiChangeSuit);
	
}
