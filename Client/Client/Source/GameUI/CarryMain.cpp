/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\liuchuanpeng\桌面\载具\载具\CarryMain.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "CarryMain.h"
#include "Skill.h"
#include "GameMain.h"
#include "PlayerMgr.h"
#include "PlayerRole.h"
#include "shortcutkey_configure.h"

CUI_ID_FRAME_CarryMain s_CUI_ID_FRAME_CarryMain;
MAP_FRAME_RUN( s_CUI_ID_FRAME_CarryMain, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_CarryMain, OnFrameRender )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_CarryMain, ID_LISTIMG_HotkeyOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_CarryMain, ID_LISTIMG_HotkeyOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_CarryMain, ID_LISTIMG_HotkeyOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_CarryMain, ID_LISTIMG_HotkeyOnIconRButtonUp )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_CarryMain, ID_BUTTON_LiveOnButtonClick )
CUI_ID_FRAME_CarryMain::CUI_ID_FRAME_CarryMain()
{
	// Member
	m_pID_FRAME_CarryMain = NULL;
	m_pID_LISTIMG_Hotkey = NULL;
	m_pID_PROGRESS_EXP = NULL;
	m_pID_BUTTON_Live = NULL;

	m_nMountID = -1;
}

// Frame
bool CUI_ID_FRAME_CarryMain::OnFrameRun()
{
	//每帧界面逻辑更新，需要先判断界面是否可见，把下面代码打开
	//if( IsVisable() )
	//{
	//}
	return true;
}

bool CUI_ID_FRAME_CarryMain::OnFrameRender()
{
	return true;
}

// ListImg / ListEx
bool CUI_ID_FRAME_CarryMain::ID_LISTIMG_HotkeyOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
											ControlIconDrag::S_ListImg* pItemDrag,
											ControlIconDrag::S_ListImg* pItemSrc )
{
	if ( !m_pID_FRAME_CarryMain )
		return false;
	return false;
}

bool CUI_ID_FRAME_CarryMain::ID_LISTIMG_HotkeyOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( !m_pID_FRAME_CarryMain )
		return false;
	return false;
}

bool CUI_ID_FRAME_CarryMain::ID_LISTIMG_HotkeyOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( !m_pID_FRAME_CarryMain )
		return false;

	UseSkill(pItem);
	return false;
}

bool CUI_ID_FRAME_CarryMain::ID_LISTIMG_HotkeyOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if ( !m_pID_FRAME_CarryMain )
		return false;

	UseSkill(pItem);
	return false;
}

// Button
bool CUI_ID_FRAME_CarryMain::ID_BUTTON_LiveOnButtonClick( ControlObject* pSender )
{
	if ( !m_pID_FRAME_CarryMain )
		return false;

	theHeroGame.GetPlayerMgr()->DisDrome();
	return true;
}

// 装载UI
bool CUI_ID_FRAME_CarryMain::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\CarryMain.MEUI", false, UI_Render_LayerSecond  );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\CarryMain.MEUI]失败")
		return false;
	}
	return DoControlConnect();
}

// 关连控件
bool CUI_ID_FRAME_CarryMain::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_CarryMain, s_CUI_ID_FRAME_CarryMainOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_CarryMain, s_CUI_ID_FRAME_CarryMainOnFrameRender );
	theUiManager.OnIconDragOn( ID_FRAME_CarryMain, ID_LISTIMG_Hotkey, s_CUI_ID_FRAME_CarryMainID_LISTIMG_HotkeyOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_CarryMain, ID_LISTIMG_Hotkey, s_CUI_ID_FRAME_CarryMainID_LISTIMG_HotkeyOnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_CarryMain, ID_LISTIMG_Hotkey, s_CUI_ID_FRAME_CarryMainID_LISTIMG_HotkeyOnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_CarryMain, ID_LISTIMG_Hotkey, s_CUI_ID_FRAME_CarryMainID_LISTIMG_HotkeyOnIconRButtonUp );
	theUiManager.OnButtonClick( ID_FRAME_CarryMain, ID_BUTTON_Live, s_CUI_ID_FRAME_CarryMainID_BUTTON_LiveOnButtonClick );

	m_pID_FRAME_CarryMain = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_CarryMain );
	m_pID_LISTIMG_Hotkey = (ControlListImage*)theUiManager.FindControl( ID_FRAME_CarryMain, ID_LISTIMG_Hotkey );
	m_pID_PROGRESS_EXP = (ControlProgress*)theUiManager.FindControl( ID_FRAME_CarryMain, ID_PROGRESS_EXP );
	m_pID_BUTTON_Live = (ControlButton*)theUiManager.FindControl( ID_FRAME_CarryMain, ID_BUTTON_Live );

	assert( m_pID_FRAME_CarryMain );
	assert( m_pID_LISTIMG_Hotkey );
	assert( m_pID_PROGRESS_EXP );
	assert( m_pID_BUTTON_Live );

	m_pID_FRAME_CarryMain->enableEscKey( false );
	m_pID_FRAME_CarryMain->SetOnEscResponseType( ControlFrame::EscResponse_SkipMe );

	SetVisable(false);
	return true;
}

// 卸载UI
bool CUI_ID_FRAME_CarryMain::_UnLoadUI()
{
	m_pID_FRAME_CarryMain = NULL;
	m_pID_LISTIMG_Hotkey = NULL;
	m_pID_PROGRESS_EXP = NULL;
	m_pID_BUTTON_Live = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\CarryMain.MEUI" );
}

// 是否可视
bool CUI_ID_FRAME_CarryMain::_IsVisable()
{
	if ( !m_pID_FRAME_CarryMain )
		return false;
	return m_pID_FRAME_CarryMain->IsVisable();
}

// 设置是否可视
void CUI_ID_FRAME_CarryMain::_SetVisable( const bool bVisable )
{
	if ( !m_pID_FRAME_CarryMain )
		return;

	m_pID_FRAME_CarryMain->SetVisable( bVisable );
	if(!bVisable)
		m_nMountID = -1;
}

bool CUI_ID_FRAME_CarryMain::UseSkill(ControlIconDrag::S_ListImg* pItem)
{
	if( !pItem )
		return false;

	theHeroGame.GetPlayerMgr()->SetCurUseSkill(pItem->m_pkIconInfo->Id(),1);
	thePlayerRole.UpdateUI();
	theHeroGame.GetPlayerMgr()->OnSkill(FALSE);
	return true;
}

void CUI_ID_FRAME_CarryMain::UpdateCD()
{
	if(!m_pID_FRAME_CarryMain)
		return;

	if(m_nMountID == -1)
		return;

	ItemDefine::SDrome* pDrome = GettheItemDetail().GetDromeByID( m_nMountID );
	if(!pDrome)
		return;

	m_pID_LISTIMG_Hotkey->Clear();
	for (int n = 0;n < ItemDefine::SDrome::DCD_MASTERUSESKILLCOUNT;++n)
	{
		unsigned short usSkillID = pDrome->masterUseSKillId[n];
		if( usSkillID != 0)
		{
			ItemDefine::SItemSkill *pItemSkill = GettheItemDetail().GetSkillByID(usSkillID,1);
			if(!pItemSkill || pItemSkill->sSkillCategory == ItemDefine::SCT_Passive)
				continue;

			ControlIconDrag::S_ListImg stItem;
			SUIIconSet::SIconSet* pIconSet = g_UISkillMgr.GetSkillIconSet(usSkillID);
			if(pIconSet)
				stItem.m_pkIconInfo->SetIconImageInfo(pIconSet->image, pIconSet->iconSize, pIconSet->row, pIconSet->column);

			stItem.SetData( usSkillID, 1, eIcon_Enable, true, eTipFlag_SkillNoNextLevel );

			AN_Configure_ShortcutKey::ShortCutKey_Configure eKey =
				(AN_Configure_ShortcutKey::ShortCutKey_Configure)(AN_Configure_ShortcutKey::AN_SCKC_skillLeft1 + n);
			stItem.m_pkIconInfo->m_strHotKey = g_shortcutKey_configure.getValueString(eKey);

			SkillBag::SColdTime *pTime = NULL;
			pTime = thePlayerRole.m_MountSkillBag.GetColdTimeById( usSkillID );
			if ( pTime )
				stItem.SetTime( pTime->dwColdStartTime, pTime->dwColdTime );

			m_pID_LISTIMG_Hotkey->SetItem(&stItem);
		}
	}
}

bool CUI_ID_FRAME_CarryMain::ClickHotkey( int nKeyIndex)
{
	if(nKeyIndex < 0 )
		return false;

	if(!m_pID_FRAME_CarryMain)
		return false;

	ControlListImage::S_ListImg *pImg = m_pID_LISTIMG_Hotkey->GetItemByIndex(nKeyIndex);
	if(!pImg)
		return false;

	UseSkill(pImg);
	return true;
}