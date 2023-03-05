/********************************************************************
Created by UIEditor.exe
FileName: C:\Documents and Settings\huwen\桌面\PetMain.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "PetMain.h"
#include "baseProperty.h"
#include "shortcutkey_configure.h"
#include "ActionUI.h"
#include "ScreenInfoManager.h"
#include "Skill.h"
#include "ItemDetail.h"

enum EPetAICommand
{
	ePetAttack			= 934,  // 命令宠物去攻击
	ePetFollow			= 935,	// 命令宠物跟随自己
	ePetDismiss			= 936,	// 解散宠物
	ePetAIAttack		= 937,	// 设置宠物的AI为主动攻击
	ePetAIDefend		= 938,	// 设置宠物的AI为主动防守
	ePetAICommand		= 939	// 设置宠物的AI为服从命令
};

CUI_ID_FRAME_PetMain s_CUI_ID_FRAME_PetMain;
MAP_FRAME_RUN( s_CUI_ID_FRAME_PetMain, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_PetMain, OnFrameRender )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_PetMain, ID_LISTIMG_PetMainOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_PetMain, ID_LISTIMG_PetMainOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_PetMain, ID_LISTIMG_PetMainOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_PetMain, ID_LISTIMG_PetMainOnIconRButtonUp )
CUI_ID_FRAME_PetMain::CUI_ID_FRAME_PetMain()
{
	// Member
	m_pID_FRAME_PetMain = NULL;
	m_pID_PICTURE_PetMain[0] = NULL;
	m_pID_PICTURE_PetMain[1] = NULL;
	m_pID_PICTURE_PetMain[2] = NULL;
	m_pID_PICTURE_PetMain[3] = NULL;
	m_pID_PICTURE_PetMain[4] = NULL;
	m_pID_PICTURE_PetMain[5] = NULL;
	m_pID_LISTIMG_PetMain[0] = NULL;
	m_pID_LISTIMG_PetMain[1] = NULL;
	m_pID_LISTIMG_PetMain[2] = NULL;
	m_pID_LISTIMG_PetMain[3] = NULL;
	m_pID_LISTIMG_PetMain[4] = NULL;
	m_pID_LISTIMG_PetMain[5] = NULL;

	m_dwPetAI = ePetAIDefend;
}
// Frame
bool CUI_ID_FRAME_PetMain::OnFrameRun()
{
	return true;
}
bool CUI_ID_FRAME_PetMain::OnFrameRender()
{
	return true;
}
// ListImg / ListEx
bool CUI_ID_FRAME_PetMain::ID_LISTIMG_PetMainOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
														  ControlIconDrag::S_ListImg* pItemDrag,
														  ControlIconDrag::S_ListImg* pItemSrc )
{
	if( !m_pID_FRAME_PetMain )
		return false;
	return false;
}
bool CUI_ID_FRAME_PetMain::ID_LISTIMG_PetMainOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_PetMain )
		return false;
	return false;
}
bool CUI_ID_FRAME_PetMain::ID_LISTIMG_PetMainOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_PetMain )
		return false;
	UseSkill(pItem);
	return false;
}
bool CUI_ID_FRAME_PetMain::ID_LISTIMG_PetMainOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	if( !m_pID_FRAME_PetMain )
		return false;
	UseSkill(pItem);
	return false;
}

// 装载UI
bool CUI_ID_FRAME_PetMain::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\PetMain.MEUI", true , UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\PetMain.MEUI]失败")
			return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_PetMain::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_PetMain, s_CUI_ID_FRAME_PetMainOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_PetMain, s_CUI_ID_FRAME_PetMainOnFrameRender );
	theUiManager.OnIconDragOn( ID_FRAME_PetMain, ID_LISTIMG_PetMain0, s_CUI_ID_FRAME_PetMainID_LISTIMG_PetMainOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_PetMain, ID_LISTIMG_PetMain0, s_CUI_ID_FRAME_PetMainID_LISTIMG_PetMainOnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_PetMain, ID_LISTIMG_PetMain0, s_CUI_ID_FRAME_PetMainID_LISTIMG_PetMainOnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_PetMain, ID_LISTIMG_PetMain0, s_CUI_ID_FRAME_PetMainID_LISTIMG_PetMainOnIconRButtonUp );
	theUiManager.OnIconDragOn( ID_FRAME_PetMain, ID_LISTIMG_PetMain1, s_CUI_ID_FRAME_PetMainID_LISTIMG_PetMainOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_PetMain, ID_LISTIMG_PetMain1, s_CUI_ID_FRAME_PetMainID_LISTIMG_PetMainOnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_PetMain, ID_LISTIMG_PetMain1, s_CUI_ID_FRAME_PetMainID_LISTIMG_PetMainOnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_PetMain, ID_LISTIMG_PetMain1, s_CUI_ID_FRAME_PetMainID_LISTIMG_PetMainOnIconRButtonUp );
	theUiManager.OnIconDragOn( ID_FRAME_PetMain, ID_LISTIMG_PetMain2, s_CUI_ID_FRAME_PetMainID_LISTIMG_PetMainOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_PetMain, ID_LISTIMG_PetMain2, s_CUI_ID_FRAME_PetMainID_LISTIMG_PetMainOnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_PetMain, ID_LISTIMG_PetMain2, s_CUI_ID_FRAME_PetMainID_LISTIMG_PetMainOnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_PetMain, ID_LISTIMG_PetMain2, s_CUI_ID_FRAME_PetMainID_LISTIMG_PetMainOnIconRButtonUp );
	theUiManager.OnIconDragOn( ID_FRAME_PetMain, ID_LISTIMG_PetMain3, s_CUI_ID_FRAME_PetMainID_LISTIMG_PetMainOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_PetMain, ID_LISTIMG_PetMain3, s_CUI_ID_FRAME_PetMainID_LISTIMG_PetMainOnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_PetMain, ID_LISTIMG_PetMain3, s_CUI_ID_FRAME_PetMainID_LISTIMG_PetMainOnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_PetMain, ID_LISTIMG_PetMain3, s_CUI_ID_FRAME_PetMainID_LISTIMG_PetMainOnIconRButtonUp );
	theUiManager.OnIconDragOn( ID_FRAME_PetMain, ID_LISTIMG_PetMain4, s_CUI_ID_FRAME_PetMainID_LISTIMG_PetMainOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_PetMain, ID_LISTIMG_PetMain4, s_CUI_ID_FRAME_PetMainID_LISTIMG_PetMainOnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_PetMain, ID_LISTIMG_PetMain4, s_CUI_ID_FRAME_PetMainID_LISTIMG_PetMainOnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_PetMain, ID_LISTIMG_PetMain4, s_CUI_ID_FRAME_PetMainID_LISTIMG_PetMainOnIconRButtonUp );
	theUiManager.OnIconDragOn( ID_FRAME_PetMain, ID_LISTIMG_PetMain5, s_CUI_ID_FRAME_PetMainID_LISTIMG_PetMainOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_PetMain, ID_LISTIMG_PetMain5, s_CUI_ID_FRAME_PetMainID_LISTIMG_PetMainOnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_PetMain, ID_LISTIMG_PetMain5, s_CUI_ID_FRAME_PetMainID_LISTIMG_PetMainOnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_PetMain, ID_LISTIMG_PetMain5, s_CUI_ID_FRAME_PetMainID_LISTIMG_PetMainOnIconRButtonUp );

	m_pID_FRAME_PetMain = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_PetMain );
	m_pID_PICTURE_PetMain[0] = (ControlPicture*)theUiManager.FindControl( ID_FRAME_PetMain, ID_PICTURE_PetMain0 );
	m_pID_PICTURE_PetMain[1] = (ControlPicture*)theUiManager.FindControl( ID_FRAME_PetMain, ID_PICTURE_PetMain1 );
	m_pID_PICTURE_PetMain[2] = (ControlPicture*)theUiManager.FindControl( ID_FRAME_PetMain, ID_PICTURE_PetMain2 );
	m_pID_PICTURE_PetMain[3] = (ControlPicture*)theUiManager.FindControl( ID_FRAME_PetMain, ID_PICTURE_PetMain3 );
	m_pID_PICTURE_PetMain[4] = (ControlPicture*)theUiManager.FindControl( ID_FRAME_PetMain, ID_PICTURE_PetMain4 );
	m_pID_PICTURE_PetMain[5] = (ControlPicture*)theUiManager.FindControl( ID_FRAME_PetMain, ID_PICTURE_PetMain5 );
	m_pID_LISTIMG_PetMain[0] = (ControlListImage*)theUiManager.FindControl( ID_FRAME_PetMain, ID_LISTIMG_PetMain0 );
	m_pID_LISTIMG_PetMain[1] = (ControlListImage*)theUiManager.FindControl( ID_FRAME_PetMain, ID_LISTIMG_PetMain1 );
	m_pID_LISTIMG_PetMain[2] = (ControlListImage*)theUiManager.FindControl( ID_FRAME_PetMain, ID_LISTIMG_PetMain2 );
	m_pID_LISTIMG_PetMain[3] = (ControlListImage*)theUiManager.FindControl( ID_FRAME_PetMain, ID_LISTIMG_PetMain3 );
	m_pID_LISTIMG_PetMain[4] = (ControlListImage*)theUiManager.FindControl( ID_FRAME_PetMain, ID_LISTIMG_PetMain4 );
	m_pID_LISTIMG_PetMain[5] = (ControlListImage*)theUiManager.FindControl( ID_FRAME_PetMain, ID_LISTIMG_PetMain5 );


	for ( int i = 0; i < eMaxInitiativeSkillNumber; ++i )
	{
		m_pID_PICTURE_PetMain[i]->SetMsgHoldup(false);
		m_pID_LISTIMG_PetMain[i]->ShowPressEffect(true);
		m_pID_LISTIMG_PetMain[i]->SetShowAllInfo(true);
		m_pID_LISTIMG_PetMain[i]->SetDisableCanbePick(false);
		m_pID_LISTIMG_PetMain[i]->SetOnlyShowItemIcon(true);
		m_pID_LISTIMG_PetMain[i]->SetDelayTime(g_ControlListImageShortDelayTime);
	}
	assert( m_pID_FRAME_PetMain );
	assert( m_pID_PICTURE_PetMain[0] );
	assert( m_pID_PICTURE_PetMain[1] );
	assert( m_pID_PICTURE_PetMain[2] );
	assert( m_pID_PICTURE_PetMain[3] );
	assert( m_pID_PICTURE_PetMain[4] );
	assert( m_pID_PICTURE_PetMain[5] );
	assert( m_pID_LISTIMG_PetMain[0] );
	assert( m_pID_LISTIMG_PetMain[1] );
	assert( m_pID_LISTIMG_PetMain[2] );
	assert( m_pID_LISTIMG_PetMain[3] );
	assert( m_pID_LISTIMG_PetMain[4] );
	assert( m_pID_LISTIMG_PetMain[5] );
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_PetMain::_UnLoadUI()
{
	m_pID_FRAME_PetMain = NULL;
	m_pID_PICTURE_PetMain[0] = NULL;
	m_pID_PICTURE_PetMain[1] = NULL;
	m_pID_PICTURE_PetMain[2] = NULL;
	m_pID_PICTURE_PetMain[3] = NULL;
	m_pID_PICTURE_PetMain[4] = NULL;
	m_pID_PICTURE_PetMain[5] = NULL;
	m_pID_LISTIMG_PetMain[0] = NULL;
	m_pID_LISTIMG_PetMain[1] = NULL;
	m_pID_LISTIMG_PetMain[2] = NULL;
	m_pID_LISTIMG_PetMain[3] = NULL;
	m_pID_LISTIMG_PetMain[4] = NULL;
	m_pID_LISTIMG_PetMain[5] = NULL;

	m_dwPetAI = ePetAIDefend;
	return theUiManager.RemoveFrame( "Data\\UI\\PetMain.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_PetMain::_IsVisable()
{
	if( !m_pID_FRAME_PetMain )
		return false;
	return m_pID_FRAME_PetMain->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_PetMain::_SetVisable( const bool bVisable )
{
	if( !m_pID_FRAME_PetMain )
		return;
	if (!IsVisable())
		m_dwPetAI = ePetAIDefend;

	if ( bVisable )
	{
		Refresh();
	}

	m_pID_FRAME_PetMain->SetVisable( bVisable );
}

//void CUI_ID_FRAME_PetMain::SetPetAction(int action, int keyIndex)
//{
//	ControlIconDrag::S_ListImg stItem;
//
//	SUIIconSet::SIconSet* iconSet = g_UISkillMgr.GetSkillIconSet(
//		action);
//	if (iconSet)
//		stItem.m_pkIconInfo->SetIconImageInfo(iconSet->image, iconSet->iconSize, iconSet->row, iconSet->column);
//	stItem.SetData(action, 1);
//	stItem.SetFlags(BagTypeActionUI);
//
//	AN_Configure_ShortcutKey::ShortCutKey_Configure eKey =
//		(AN_Configure_ShortcutKey::ShortCutKey_Configure)(AN_Configure_ShortcutKey::AN_SCKC_PetSkill1 + keyIndex);
//	stItem.m_pkIconInfo->m_strHotKey = g_shortcutKey_configure.getValueString(eKey);
//
//	m_pID_LISTIMG_PetMain->SetItem(&stItem);
//}

//void CUI_ID_FRAME_PetMain::SetPetAI(int ai)
//{
//	ControlIconDrag::S_ListImg stItem;
//
//	SUIIconSet::SIconSet* iconSet = g_UISkillMgr.GetSkillIconSet(
//		ai);
//	if (iconSet)
//		stItem.m_pkIconInfo->SetIconImageInfo(iconSet->image, iconSet->iconSize, iconSet->row, iconSet->column);
//	stItem.SetData(ai, 1);
//	stItem.SetFlags(BagTypeActionUI);
//
//	AN_Configure_ShortcutKey::ShortCutKey_Configure eKey =
//		(AN_Configure_ShortcutKey::ShortCutKey_Configure)(AN_Configure_ShortcutKey::AN_SCKC_PetSkill4);
//	stItem.m_pkIconInfo->m_strHotKey = g_shortcutKey_configure.getValueString(eKey);
//
//	m_pID_LISTIMG_PetMain->SetItem(&stItem, 3);
//
//	m_dwPetAI = ai;
//}

void CUI_ID_FRAME_PetMain::InitializeAtEnterWorld()
{
	SMountItem& mount = thePlayerRole.GetMountByIndex( thePlayerRole.GetActivedMountIndex() );

	if ( mount.baseInfo.id ==  InvalidLogicNumber )
	{
		return ;
	}

	SetVisable( true );
	Refresh();
}

void CUI_ID_FRAME_PetMain::Refresh()
{
	if ( !IsVisable( ) )
	{
		return;
	}

	SMountItem& mount = thePlayerRole.GetMountByIndex( thePlayerRole.GetActivedMountIndex() );

	if ( mount.baseInfo.id ==  InvalidLogicNumber )
	{
		return ;
	}

	CUISkillTreeConfig::SkillTreePage *pSkillTree = g_UISkillMgr.m_SkillTreeConfig.GetPage(CUISkillMgr::eMountSkill);
	if (!pSkillTree)
	{
		return;
	}

	SUIIconSet* pSkillIcon = &pSkillTree->UISkillIcons;

	for ( int i = 0; i < eMaxInitiativeSkillNumber; ++i )
	{
		m_pID_LISTIMG_PetMain[i]->Clear();
		m_pID_PICTURE_PetMain[i]->SetVisable(false);
		m_pID_LISTIMG_PetMain[i]->SetVisable(false);
	}
	int skillCount = 0;

	for ( int i = 0; i < eMaxInitiativeSkillNumber; ++i )
	{
		unsigned short usSkillId = mount.skillInfo.skills[i].ustSkillID;
		if ( usSkillId == 0)
		{
			continue;
		}

		unsigned short usLevel = mount.skillInfo.skills[i].stSkillLevel;
		ItemDefine::SItemSkill* pItemSkill = GettheItemDetail().GetSkillByID(usSkillId,usLevel);

		if (!pItemSkill)
		{
			continue;
		}

		const SUIIconSet::SIconSet* pIcon = pSkillIcon->GetValue(usSkillId);
		if ( !pIcon )
		{
			continue;
		}

		AN_Configure_ShortcutKey::ShortCutKey_Configure eKey = (AN_Configure_ShortcutKey::ShortCutKey_Configure)(AN_Configure_ShortcutKey::AN_SCKC_PetSkill1 + i);
				
		ControlIconDrag::S_ListImg stItem;
		stItem.m_pkIconInfo->SetIconImageInfo(pIcon->image, pIcon->iconSize, pIcon->row, pIcon->column);
		stItem.SetData( usSkillId, usLevel, eIcon_Enable, 0, eTipFlag_SkillNoNextLevel );
		stItem.SetFlags(CUISkillMgr::eMountSkill);
		stItem.m_pkIconInfo->m_strHotKey = g_shortcutKey_configure.getValueString(eKey);

		SkillBag::SColdTime *pTime = NULL;
		pTime = thePlayerRole.m_MountSkillBag.GetColdTimeById( usSkillId );

		if ( pTime )
		{
			stItem.SetTime( pTime->dwColdStartTime, pTime->dwColdTime );
		}

		if ( pItemSkill->sSkillCategory == ItemDefine::SCT_MountMasterInitiativeControl )
		{
			m_pID_LISTIMG_PetMain[skillCount]->SetItem(&stItem);
			m_pID_LISTIMG_PetMain[skillCount]->SetVisable(true);
			m_pID_PICTURE_PetMain[skillCount]->SetVisable(true);

			++skillCount;
		}
	}

	if ( skillCount == 0 )
	{
		SetVisable( false );
	}
}

bool CUI_ID_FRAME_PetMain::IsSkillList( const ControlObject* pObject )
{
	if( !m_pID_FRAME_PetMain )
	{
		return false;
	}
	for ( int i = 0; i < eMaxInitiativeSkillNumber; ++i )
	{
		if ( pObject == m_pID_LISTIMG_PetMain[i] )
		{
			return true;
		}
	}


	return false;
}

//void CUI_ID_FRAME_PetMain::RefreshPetSkill()
//{
//	if (!IsVisable())
//		return;
//
//	/*int index = 4;*/
//
//	// 召唤兽技能
//	for ( int n=0; n<thePlayerRole.m_SkillBag.GetSkillNum(); n++ )
//	{
//		SCharSkill *pSkill = thePlayerRole.m_SkillBag.GetSkillByIndex( n );
//		if (!pSkill || pSkill->ustSkillID == InvalidLogicNumber)
//			continue;
//
//		ItemDefine::SItemSkill* pItemSkill = GettheItemDetail().GetSkillByID(pSkill->ustSkillID, pSkill->stSkillLevel);
//		if (!pItemSkill || !pItemSkill->ispettouseskill)
//			continue;
//
//		ControlIconDrag::S_ListImg stItem;
//
//		SUIIconSet::SIconSet* iconSet = g_UISkillMgr.GetSkillIconSet(pSkill->ustSkillID);
//		if (iconSet)
//			stItem.m_pkIconInfo->SetIconImageInfo(iconSet->image, iconSet->iconSize, iconSet->row, iconSet->column);
//		stItem.SetData( pSkill->ustSkillID, pSkill->stSkillLevel, eIcon_Enable, true );
//		stItem.SetFlags(BagTypeSkill);
//
//		AN_Configure_ShortcutKey::ShortCutKey_Configure eKey =
//			(AN_Configure_ShortcutKey::ShortCutKey_Configure)(AN_Configure_ShortcutKey::AN_SCKC_PetSkill1 + n);
//		stItem.m_pkIconInfo->m_strHotKey = g_shortcutKey_configure.getValueString(eKey);
//
//		SkillBag::SColdTime *pTime = thePlayerRole.m_SkillBag.GetColdTimeByIndex( n );
//		if ( pTime )
//			stItem.SetTime( pTime->dwColdStartTime, pTime->dwColdTime );
//
//		m_pID_LISTIMG_PetMain[/*index*/n]->SetItem(&stItem);
//
//		/*++index;*/
//	}
//}

bool CUI_ID_FRAME_PetMain::UseSkill(ControlIconDrag::S_ListImg* pItem)
{
	if( !pItem )
	{
		return false;
	}

	switch (pItem->m_dwFlags)
	{
	case CUISkillMgr::eMountSkill:
		{
			SCharSkill *pSkill = NULL;
			pSkill = thePlayerRole.m_MountSkillBag.GetSkillByID( pItem->m_pkIconInfo->Id() );
			if ( !pSkill )
			{
				CScreenInfoManager::Instance()->ShowInfoByType( CScreenInfoManager::eType_Horse_Tip, theXmlString.GetString( eText_Mount_NotActived ) );
				return true;
			}

			theHeroGame.GetPlayerMgr()->SetCurUseSkill( pSkill->ustSkillID,
				pSkill->stSkillLevel );

			thePlayerRole.UpdateUI();
			theHeroGame.GetPlayerMgr()->OnSkill( FALSE );
		}
		break;
	case CUISkillMgr::eCommon:
		{
			s_CUI_ID_FRAME_ActionUI.SetCurFunction( pItem->m_pkIconInfo->Id() );
			s_CUI_ID_FRAME_ActionUI.UseFunction();
		}
		break;
	}

	return true;
}

void CUI_ID_FRAME_PetMain::SetHotkeyPressIndex(int nIndex)
{
	if(!m_pID_FRAME_PetMain)
		return;

	m_nSkillIndex = nIndex;
	if (m_nSkillIndex < 0 || m_nSkillIndex >= eMaxInitiativeSkillNumber)
	{
		return;
	}

	if (m_pID_LISTIMG_PetMain[m_nSkillIndex]->IsVisable())
	{
		ControlIconDrag::S_ListImg* pItem = m_pID_LISTIMG_PetMain[m_nSkillIndex]->GetItemByIndex(0);
		if (pItem)
		{
			UseSkill(pItem);
		}
	}
}