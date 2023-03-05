/********************************************************************
Created by UIEditor.exe
FileName: F:\3Guo Client\Data\Ui\zhujiangtujian.cpp
*********************************************************************/
#include <assert.h>
#include "MeUi/UiManager.h"
#include "zhujiangtujian.h"
#include "ItemHero.h"
#include "PlayerInfoMgr.h"
#include "Player.h"
#include "Ui/Skill.h"

CUI_ID_FRAME_zhujiangtujian s_CUI_ID_FRAME_zhujiangtujian;
MAP_FRAME_RUN( s_CUI_ID_FRAME_zhujiangtujian, OnFrameRun )
MAP_FRAME_RENDER( s_CUI_ID_FRAME_zhujiangtujian, OnFrameRender )
MAP_ICON_DRAG_ON_CALLBACK( s_CUI_ID_FRAME_zhujiangtujian, ID_LISTIMG_skillOnIconDragOn )
MAP_ICON_LDB_CLICK_CALLBACK( s_CUI_ID_FRAME_zhujiangtujian, ID_LISTIMG_skillOnIconLDBClick )
MAP_ICON_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_zhujiangtujian, ID_LISTIMG_skillOnIconButtonClick )
MAP_ICON_RBUTTON_UP_CALLBACK( s_CUI_ID_FRAME_zhujiangtujian, ID_LISTIMG_skillOnIconRButtonUp )
MAP_BUTTON_CLICK_CALLBACK( s_CUI_ID_FRAME_zhujiangtujian, ID_BUTTON_closeOnButtonClick )
CUI_ID_FRAME_zhujiangtujian::CUI_ID_FRAME_zhujiangtujian()
{
	// Member
	m_pID_FRAME_zhujiangtujian = NULL;
	m_pID_PICTURE_zhujiangtouxiang = NULL;
	m_pID_PICTURE_nameLV = NULL;
	m_pID_TEXT_jieshao = NULL;
	m_pID_PICTURE_ability = NULL;
	m_pID_LISTIMG_skill = NULL;
	m_pID_PICTURE_warability = NULL;
	m_pID_BUTTON_close = NULL;
}
// Frame
bool CUI_ID_FRAME_zhujiangtujian::OnFrameRun()
{
	return true;
}
bool CUI_ID_FRAME_zhujiangtujian::OnFrameRender()
{
	return true;
}
// ListImg / ListEx
bool CUI_ID_FRAME_zhujiangtujian::ID_LISTIMG_skillOnIconDragOn( ControlObject* pSender, ControlObject* pMe,
															   ControlIconDrag::S_ListImg* pItemDrag,
															   ControlIconDrag::S_ListImg* pItemSrc )
{
	return false;
}
bool CUI_ID_FRAME_zhujiangtujian::ID_LISTIMG_skillOnIconLDBClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_zhujiangtujian::ID_LISTIMG_skillOnIconButtonClick( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
bool CUI_ID_FRAME_zhujiangtujian::ID_LISTIMG_skillOnIconRButtonUp( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem )
{
	return false;
}
// Button
bool CUI_ID_FRAME_zhujiangtujian::ID_BUTTON_closeOnButtonClick( ControlObject* pSender )
{
	_SetVisable(false);
	return true;
}

// 装载UI
bool CUI_ID_FRAME_zhujiangtujian::_LoadUI()
{
	DWORD dwResult = theUiManager.AddFrame( "Data\\UI\\zhujiangtujian.MEUI", false, UI_Render_LayerThree );
	if ( dwResult == 0 )
	{
		MESSAGE_BOX("读取文件[Data\\UI\\zhujiangtujian.MEUI]失败")
			return false;
	}
	return DoControlConnect();
}
// 关连控件
bool CUI_ID_FRAME_zhujiangtujian::DoControlConnect()
{
	theUiManager.OnFrameRun( ID_FRAME_zhujiangtujian, s_CUI_ID_FRAME_zhujiangtujianOnFrameRun );
	theUiManager.OnFrameRender( ID_FRAME_zhujiangtujian, s_CUI_ID_FRAME_zhujiangtujianOnFrameRender );
	theUiManager.OnIconDragOn( ID_FRAME_zhujiangtujian, ID_LISTIMG_skill, s_CUI_ID_FRAME_zhujiangtujianID_LISTIMG_skillOnIconDragOn );
	theUiManager.OnIconLDBClick( ID_FRAME_zhujiangtujian, ID_LISTIMG_skill, s_CUI_ID_FRAME_zhujiangtujianID_LISTIMG_skillOnIconLDBClick );
	theUiManager.OnIconButtonClick( ID_FRAME_zhujiangtujian, ID_LISTIMG_skill, s_CUI_ID_FRAME_zhujiangtujianID_LISTIMG_skillOnIconButtonClick );
	theUiManager.OnIconRButtonUp( ID_FRAME_zhujiangtujian, ID_LISTIMG_skill, s_CUI_ID_FRAME_zhujiangtujianID_LISTIMG_skillOnIconRButtonUp );
	theUiManager.OnButtonClick( ID_FRAME_zhujiangtujian, ID_BUTTON_close, s_CUI_ID_FRAME_zhujiangtujianID_BUTTON_closeOnButtonClick );

	m_pID_FRAME_zhujiangtujian = (ControlFrame*)theUiManager.FindFrame( ID_FRAME_zhujiangtujian );
	m_pID_PICTURE_zhujiangtouxiang = (ControlPicture*)theUiManager.FindControl( ID_FRAME_zhujiangtujian, ID_PICTURE_zhujiangtouxiang );
	m_pID_PICTURE_nameLV = (ControlPicture*)theUiManager.FindControl( ID_FRAME_zhujiangtujian, ID_PICTURE_nameLV );
	m_pID_TEXT_jieshao = (ControlText*)theUiManager.FindControl( ID_FRAME_zhujiangtujian, ID_TEXT_jieshao );
	m_pID_PICTURE_ability = (ControlPicture*)theUiManager.FindControl( ID_FRAME_zhujiangtujian, ID_PICTURE_ability );
	m_pID_LISTIMG_skill = (ControlListImage*)theUiManager.FindControl( ID_FRAME_zhujiangtujian, ID_LISTIMG_skill );
	m_pID_PICTURE_warability = (ControlPicture*)theUiManager.FindControl( ID_FRAME_zhujiangtujian, ID_PICTURE_warability );
	m_pID_BUTTON_close = (ControlButton*)theUiManager.FindControl( ID_FRAME_zhujiangtujian, ID_BUTTON_close );
	assert( m_pID_FRAME_zhujiangtujian );
	assert( m_pID_PICTURE_zhujiangtouxiang );
	assert( m_pID_PICTURE_nameLV );
	assert( m_pID_TEXT_jieshao );
	assert( m_pID_PICTURE_ability );
	assert( m_pID_LISTIMG_skill );
	assert( m_pID_PICTURE_warability );
	assert( m_pID_BUTTON_close );

	SetVisable(false);
	return true;
}
// 卸载UI
bool CUI_ID_FRAME_zhujiangtujian::_UnLoadUI()
{
	m_pID_FRAME_zhujiangtujian = NULL;
	return theUiManager.RemoveFrame( "Data\\UI\\zhujiangtujian.MEUI" );
}
// 是否可视
bool CUI_ID_FRAME_zhujiangtujian::_IsVisable()
{
	return m_pID_FRAME_zhujiangtujian->IsVisable();
}
// 设置是否可视
void CUI_ID_FRAME_zhujiangtujian::_SetVisable( const bool bVisable )
{
	if (bVisable)
	{
		Refresh();
	}
	m_pID_FRAME_zhujiangtujian->SetVisable( bVisable );
}
void CUI_ID_FRAME_zhujiangtujian::InitializeAtEnterWorld()
{
	if( !m_pID_FRAME_zhujiangtujian )
		return;

	//ClearSlotSpark();
	_SetVisable( false );
}

bool CUI_ID_FRAME_zhujiangtujian::clear()
{
	m_pID_LISTIMG_skill->Clear();
	m_pID_TEXT_jieshao->Clear();
	return true;
}

void CUI_ID_FRAME_zhujiangtujian::Refresh()
{
	clear();

	if(item_id == INVALID_HERO_ID)
	{
		return;
	}

	CItemHero::SItemHero* pHero = theItemHero.FindHeroByItemID(item_id);
	if (!pHero)
	{
		return;
	}

	m_pID_PICTURE_nameLV->SetPicName(pHero->namePicAddr.c_str());
	m_pID_PICTURE_zhujiangtouxiang->SetPicName(pHero->Pic_TuJianUI.c_str());
	//m_pID_PICTURE_zhujiangtouxiang->SetPicName(PlayerInfoMgr::Instance()->GetPlayerHeadPic(pHero));	//portrait
	m_pID_PICTURE_ability->SetPicName(pHero->icon_addr.c_str());			//ability

	int skillArray[3] = {pHero->hero_skill1,pHero->hero_skill2,pHero->hero_skill3};
	int skillLevel[3] = {pHero->skill1_lv,pHero->skill2_lv,pHero->skill3_lv};
	for(int i=0;i<sizeof(skillArray)/sizeof(int);i++)
	{
		if(skillArray[i]==0)
		{
			continue;
		}
		ControlIconDrag::S_ListImg stListItem;
		SUIIconSet::SIconSet* iconSet = g_UISkillMgr.GetSkillIconSet(skillArray[i]);
		if (iconSet)
			stListItem.m_pkIconInfo->SetIconImageInfo(iconSet->image, iconSet->iconSize, iconSet->row, iconSet->column);
		bool bEnable = eIcon_Enable/*CPackItemEnableManager::Instance()->IsPackItemEnable( pBag, n )*/;
		stListItem.SetData( skillArray[i], skillLevel[i], bEnable? eIcon_Enable: eIcon_Disable, true, eTipFlag_SkillNoNextLevel );
		//stListItem.SetData( skillArray[i],skillLevel[i], ( bEnable ? eIcon_Enable : eIcon_Disable ));
		stListItem.SetSparkEnable( false );
		m_pID_LISTIMG_skill->SetItem( &stListItem, i );							//skill
	}

	m_pID_TEXT_jieshao->SetText(pHero->explain_hero);						//intro
	m_pID_PICTURE_warability->SetPicName(pHero->proPicAddr.c_str());		//war ability
}