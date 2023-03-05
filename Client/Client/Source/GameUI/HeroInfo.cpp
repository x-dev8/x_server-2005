/********************************************************************
Created by UIEditor.exe
FileName: F:\sanguo\Data\Ui\HeroInfo.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "HeroInfo.h"
#include "BasePropertyBGFrame.h"
#include "ItemHero.h"
#include "PlayerRole.h"
#include "PlayerInfoMgr.h"

#define MAX_HEROSKILL 3
CUI_ID_FRAME_HeroInfo s_CUI_ID_FRAME_HeroInfo;
MAP_FRAME_RUN( s_CUI_ID_FRAME_HeroInfo, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_HeroInfo, OnFrameRender )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_HeroInfo, ID_LISTIMG_skillOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_HeroInfo, ID_LISTIMG_skillOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_HeroInfo, ID_LISTIMG_skillOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_HeroInfo, ID_LISTIMG_skillOnIconRButtonUp )
CUI_ID_FRAME_HeroInfo::CUI_ID_FRAME_HeroInfo()
{
	// Member
	m_pID_FRAME_HeroInfo = NULL;
	m_pID_PICTURE_touxiang = NULL;
	m_pID_PICTURE_ability = NULL;
	m_pID_TEXT_introduce = NULL;
	m_pID_PICTURE_warability = NULL;
	m_pID_LISTIMG_skill = NULL;

}
// Frame
bool CUI_ID_FRAME_HeroInfo::OnFrameRun()
{
	return true;
}
bool CUI_ID_FRAME_HeroInfo::OnFrameRender()
{
	return true;
}
// ListImg / ListEx
bool CUI_ID_FRAME_HeroInfo::ID_LISTIMG_skillOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
														 ControlIconDrag::S_ListImg* pItemDrag,
														 ControlIconDrag::S_ListImg* pItemSrc )
{
	return false;
}
bool CUI_ID_FRAME_HeroInfo::ID_LISTIMG_skillOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_HeroInfo::ID_LISTIMG_skillOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_HeroInfo::ID_LISTIMG_skillOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}

// 装载UI
bool CUI_ID_FRAME_HeroInfo::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\HeroInfo.MEUI" );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\HeroInfo.MEUI]失败")
			return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_HeroInfo::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_HeroInfo, s_CUI_ID_FRAME_HeroInfoOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_HeroInfo, s_CUI_ID_FRAME_HeroInfoOnFrameRender );
	theUiManager.OnIconDragOn( ID_FRAME_HeroInfo, ID_LISTIMG_skill, s_CUI_ID_FRAME_HeroInfoID_LISTIMG_skillOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_HeroInfo, ID_LISTIMG_skill, s_CUI_ID_FRAME_HeroInfoID_LISTIMG_skillOnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_HeroInfo, ID_LISTIMG_skill, s_CUI_ID_FRAME_HeroInfoID_LISTIMG_skillOnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_HeroInfo, ID_LISTIMG_skill, s_CUI_ID_FRAME_HeroInfoID_LISTIMG_skillOnIconRButtonUp );

	m_pID_FRAME_HeroInfo = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_HeroInfo );
	m_pID_PICTURE_touxiang = (ControlPicture*)theUiManager.FindControl( ID_FRAME_HeroInfo, ID_PICTURE_touxiang );
	m_pID_PICTURE_ability = (ControlPicture*)theUiManager.FindControl( ID_FRAME_HeroInfo, ID_PICTURE_ability );
	m_pID_TEXT_introduce = (ControlText*)theUiManager.FindControl( ID_FRAME_HeroInfo, ID_TEXT_introduce );
	m_pID_PICTURE_warability = (ControlPicture*)theUiManager.FindControl( ID_FRAME_HeroInfo, ID_PICTURE_warability );
	m_pID_LISTIMG_skill = (ControlListImage*)theUiManager.FindControl( ID_FRAME_HeroInfo, ID_LISTIMG_skill );
	assert( m_pID_FRAME_HeroInfo );
	assert( m_pID_PICTURE_touxiang );
	assert( m_pID_PICTURE_ability );
	assert( m_pID_TEXT_introduce );
	assert( m_pID_PICTURE_warability );
	assert( m_pID_LISTIMG_skill );
	//m_pID_FRAME_HeroInfo->SetFather(s_CUI_ID_FRAME_BasePropertyBGFrame.GetFrame());
	return true;
}

void CUI_ID_FRAME_HeroInfo::InitializeAtEnterWorld()
{
	if( !m_pID_FRAME_HeroInfo )
		return;

	//ClearSlotSpark();
	_SetVisable( false );
}
// 卸载UI
bool CUI_ID_FRAME_HeroInfo::_UnLoadUI()
{
	m_pID_FRAME_HeroInfo = NULL;
	m_pID_PICTURE_touxiang = NULL;
	m_pID_PICTURE_ability = NULL;
	m_pID_TEXT_introduce = NULL;
	m_pID_PICTURE_warability = NULL;
	m_pID_LISTIMG_skill = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\HeroInfo.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_HeroInfo::_IsVisable()
{
	if (!m_pID_FRAME_HeroInfo)
	{
		return false;
	}
	
	return m_pID_FRAME_HeroInfo->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_HeroInfo::_SetVisable( const bool bVisable )
{
	if (!m_pID_FRAME_HeroInfo)
	{
		return;
	}
	m_pID_FRAME_HeroInfo->SetVisable( bVisable );
	if (bVisable)
	{
		Refresh();
	}
	
}

void CUI_ID_FRAME_HeroInfo::Clear()
{
	m_pID_TEXT_introduce->Clear();
	m_pID_LISTIMG_skill->Clear();
}

void CUI_ID_FRAME_HeroInfo::Refresh()
{
	CItemHero::SItemHero* pHero = theItemHero.FindHeroByHeroID(thePlayerRole.GetCharInfo2().baseinfo.liveinfo.hero_id);
	if (!pHero)
	{
		Clear();
		return;
	}
	m_pID_PICTURE_touxiang->SetPicName(PlayerInfoMgr::Instance()->GetPlayerHeadPic(pHero));
	m_pID_PICTURE_ability->SetPicName(pHero->icon_addr.c_str());
	m_pID_TEXT_introduce->SetText(pHero->explain_hero);
	m_pID_PICTURE_warability->SetPicName(pHero->property_hero.c_str());
	int skillArray[MAX_HEROSKILL] = {pHero->hero_skill1,pHero->hero_skill2,pHero->hero_skill3};
	int skillLevel[MAX_HEROSKILL] = {pHero->skill1_lv,pHero->skill2_lv,pHero->skill3_lv};
	for (int i=0;i<MAX_HEROSKILL;i++)
	{
		if (0==skillArray[i] || 0xffffffff== skillArray[i])
		{
			continue;
		}
		ControlIconDrag::S_ListImg stListItem;
		bool bEnable = eIcon_Enable/*CPackItemEnableManager::Instance()->IsPackItemEnable( pBag, n )*/;
		stListItem.SetData( skillArray[i],skillLevel[i], ( bEnable ? eIcon_Enable : eIcon_Disable ));
		stListItem.SetSparkEnable( false );
		m_pID_LISTIMG_skill->SetItem( &stListItem, i );	
	}

}

